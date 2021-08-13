#define F_CPU 7372800UL

#define USART_BAUDRATE 19200
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#include <avr/io.h>
#include <util/delay.h>
#include<avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#define BIT_SET(a,b) ((a) |= (1ULL<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b))))		// '!!' to make sure this returns 0 or 1

#define	 I1A_H		BIT_SET(PORTA,0)
#define	 I1A_L		BIT_CLEAR(PORTA,0)
#define	 I100MA_H	BIT_SET(PORTA,1)
#define	 I100MA_L	BIT_CLEAR(PORTA,1)
#define	 CSDAC_H	BIT_SET(PORTA,2)
#define	 CSDAC_L	BIT_CLEAR(PORTA,2)
#define	 MISO_V		BIT_CHECK(PINA,3)
#define	 MOSI_H		BIT_SET(PORTA,4)
#define	 MOSI_L		BIT_CLEAR(PORTA,4)
#define	 CSADC_H	BIT_SET(PORTA,5)
#define	 CSADC_L	BIT_CLEAR(PORTA,5)
#define	 SCK_H		BIT_SET(PORTA,6)
#define	 SCK_L		BIT_CLEAR(PORTA,6)
#define	 FDACLO_H	BIT_SET(PORTA,7)
#define	 FDACLO_L	BIT_CLEAR(PORTA,7)

#define	 LT10MA_H	BIT_SET(PORTB,0)
#define	 LT10MA_L	BIT_CLEAR(PORTB,0)
#define	 I10MA_H	BIT_SET(PORTB,1)
#define	 I10MA_L	BIT_CLEAR(PORTB,1)
#define	 I1MA_H		BIT_SET(PORTB,2)
#define	 I1MA_L		BIT_CLEAR(PORTB,2)
#define	 I100UA_H	BIT_SET(PORTB,3)
#define	 I100UA_L	BIT_CLEAR(PORTB,3)
#define	 I10UA_H	BIT_SET(PORTB,4)
#define	 I10UA_L	BIT_CLEAR(PORTB,4)

#define	 OUT_ON_H	BIT_SET(PORTC,1)
#define	 OUT_ON_L	BIT_CLEAR(PORTC,1)
#define	 REMOTE_H	BIT_SET(PORTC,2)
#define	 REMOTE_L	BIT_CLEAR(PORTC,2)
#define	 CLAMP_V	BIT_CHECK(PINC,3)
#define	 IMODE_H	BIT_SET(PORTC,4)
#define	 IMODE_L	BIT_CLEAR(PORTC,4)
#define	 VMODE_H	BIT_SET(PORTC,5)
#define	 VMODE_L	BIT_CLEAR(PORTC,5)
#define	 LED_H		BIT_SET(PORTC,6)
#define	 LED_L		BIT_CLEAR(PORTC,6)
#define	 VRANGEL_H	BIT_SET(PORTC,7)
#define	 VRANGEL_L	BIT_CLEAR(PORTC,7)

#define	 PA_CTRL_A_H	BIT_SET(PORTD,2)
#define	 PA_CTRL_A_L	BIT_CLEAR(PORTD,2)
#define	 PA_CTRL_B_H	BIT_SET(PORTD,3)
#define	 PA_CTRL_B_L	BIT_CLEAR(PORTD,3)


volatile unsigned char rcvd_ptr,rcvd_flag,rcvd_str[20];
char cmd_buf[20];
unsigned char cmd_valid;
uint8_t mode,dac_update,dac_enabled,clamp_state;
uint16_t x;
uint32_t y;
uint32_t adc_res[3];
uint16_t dac_val[4];
char tx_str[30];
uint16_t out;
int range_i,range_v;



// timer0 overflow
ISR(TIMER0_OVF_vect) 
	{
	TCNT0=220;
	}

ISR (TIMER1_OVF_vect)	// Timer1 ISR
	{
	TCNT1 = 65488;
	}

ISR(UART_RX_vect)
	{
	char temp;
	temp = UDR; // Fetch the received byte value into the variable "ByteReceived"
	if (temp<0x20)
		{
		if (rcvd_ptr>0)
			{
			rcvd_str[rcvd_ptr] = 0;
			rcvd_flag = 1;
			rcvd_ptr = 0;
			}
		}
	else
		{	
		rcvd_str[rcvd_ptr++] = temp;
		}
	if (rcvd_ptr==sizeof(rcvd_str)) rcvd_ptr = 0;
	}


void uart_tx (uint8_t data)
	{
	while ((USR & (1 << UDRE)) == 0) {};
	UDR = data;
	}

void uart_txs (char * data)
	{
	while (*data) uart_tx(*data++);
	}

uint8_t uart_rx_rdy (void)
	{
	if (USR & (1 << RXC))
		return 1;
	else 
		return 0;
	}

uint8_t uart_rx_read (void)
	{
	return UDR;
	}

uint8_t spi_trf (uint8_t data)
	{
	uint8_t i,retval=0;
	for (i=0;i<8;i++)
		{
		if (data&0x80)
			{
			MOSI_H;
			}
		else
			{
			MOSI_L;
			}
		_delay_us(3);
		SCK_L;
		retval = retval << 1;
		data = data << 1;
		SCK_H;
		if (MISO_V) 
			{
			retval = retval | 0x01;
			}
		}
	return retval;
	}

void adc_write_8(uint8_t addr, uint8_t data)
	{
	CSADC_L;
	spi_trf(addr&0x3F);
	spi_trf(data);
	CSADC_H;
	}

void adc_write_16(uint8_t addr, uint16_t data)
	{
	CSADC_L;
	spi_trf(addr&0x3F);
	spi_trf((data>>8)&0xFF);
	spi_trf((data>>0)&0xFF);
	CSADC_H;
	}

void adc_write_24(uint8_t addr, uint32_t data)
	{
	CSADC_L;
	spi_trf(addr&0x3F);
	spi_trf((data>>16)&0xFF);
	spi_trf((data>>8)&0xFF);
	spi_trf((data>>0)&0xFF);
	CSADC_H;
	}

uint8_t adc_read_8(uint8_t addr)
	{
	uint8_t r1;
	CSADC_L;
	spi_trf(0x40|(addr&0x3F));
	r1 = spi_trf(0);
	CSADC_H;
	return r1;
	}

uint16_t adc_read_16(uint8_t addr)
	{
	uint8_t r1,r2;
	uint16_t retval=0;
	CSADC_L;
	spi_trf(0x40|(addr&0x3F));
	r1 = spi_trf(0);
	r2 = spi_trf(0);
	CSADC_H;
	retval = (((uint16_t)(r1))<<8)|(((uint16_t)(r2))<<0);
	return retval;
	}

uint32_t adc_read_24(uint8_t addr)
	{
	uint8_t r1,r2,r3;
	uint32_t retval=0;
	CSADC_L;
	spi_trf(0x40|(addr&0x3F));
	r1 = spi_trf(0);
	r2 = spi_trf(0);
	r3 = spi_trf(0);
	CSADC_H;
	retval = (((uint32_t)(r1))<<16)|(((uint32_t)(r2))<<8)|(((uint32_t)(r3))<<0);
	return retval;
	}

uint32_t adc_read_32(uint8_t addr)
	{
	uint8_t r1,r2,r3,r4;
	uint32_t retval=0;
	CSADC_L;
	spi_trf(0x40|(addr&0x3F));
	r1 = spi_trf(0);
	r2 = spi_trf(0);
	r3 = spi_trf(0);
	r4 = spi_trf(0);
	CSADC_H;
	retval = (((uint32_t)(r1))<<24)|(((uint32_t)(r2))<<16)|(((uint32_t)(r3))<<8)|(((uint32_t)(r4))<<0);
	return retval;
	}

uint32_t adc_ss (void)
	{
	uint8_t r1,r2,r3;
	uint32_t retval=0;
	CSADC_L;
	spi_trf(0x01);
	spi_trf(0x80);
	spi_trf(0x10);
	while (MISO_V!=0);
	spi_trf(0x44);
	r1 = spi_trf(0);
	r2 = spi_trf(0);
	r3 = spi_trf(0);
	CSADC_H;
	retval = (((uint32_t)(r1))<<16)|(((uint32_t)(r2))<<8)|(((uint32_t)(r3))<<0);
	return retval;
	}

void dac_write(uint8_t addr, uint16_t data)
	{
	CSDAC_L;
	spi_trf(addr);
	spi_trf((data>>8)&0xFF);
	spi_trf((data>>0)&0xFF);
	CSDAC_H;
	}
	
void tx_var_16(uint16_t data, uint8_t eol)
	{
	char tx_out[10];
	itoa(data,tx_out,10);
	uart_txs(tx_out);
	if (eol) uart_txs("\n");		
	}
void tx_var_32(uint32_t data, uint8_t eol)
	{
	char tx_out[10];
	ltoa(data,tx_out,10);
	uart_txs(tx_out);
	if (eol) uart_txs("\n");		
	}
	
	/*
	ziadny - 0.3mA
	iba 2 - 3,3mA
	iba 1 - 31mA
	oba  - max
	* 
	* a = 2
	* b = 1
	* PA_CTRL_A_H
	*/
	
void set_pa_ctrl (uint8_t range)	
	{
	PA_CTRL_A_L;
	PA_CTRL_B_L;
	if (range==1) 
		{
		PA_CTRL_A_H;
		PA_CTRL_B_L;
		}
	if (range==2) 
		{
		PA_CTRL_A_L;
		PA_CTRL_B_H;
		}
	if (range==3) 
		{
		PA_CTRL_A_H;
		PA_CTRL_B_H;
		}
	}
	
	
void set_current_shunt (uint8_t range)
	{
	set_pa_ctrl(1);
	I1A_H;
	I100MA_H;
	LT10MA_H;
	I10MA_H;
	I1MA_H;
	I100UA_H;
	I10UA_H;
	if (range==0) {}
	if (range==1) (I10UA_L);
	if (range==2) (I100UA_L);
	if (range==3) (I1MA_L);
	if (range==4) (I10MA_L);
	if (range==5) (I100MA_L);
	if (range==6) (I1A_L);
	if (range<5) (LT10MA_L);

	if (range==4) set_pa_ctrl(2);
	if (range==5) set_pa_ctrl(3);
	}
	
	
void serial_tasks (void)
	{
	BIT_CLEAR(UCR,RXCIE);
	if (rcvd_flag == 1)
		{
		rcvd_flag = 0;
		cmd_valid = 1;
		strcpy((char *)cmd_buf,(char *)rcvd_str);
		}
	BIT_SET(UCR,RXCIE);
	if (cmd_valid == 1)
		{
		strcpy(tx_str,"?");
		cmd_valid = 0;
		if (cmd_buf[0]=='m')
			{
			if (cmd_buf[1]=='v')
				{
				mode = 0;
				VMODE_L;
				IMODE_H;
				}
			if (cmd_buf[1]=='i')
				{
				mode = 1;
				VMODE_H;
				IMODE_L;
				}
			strcpy(tx_str,"OK");
			}
		if (cmd_buf[0]=='r')
			{
			if (cmd_buf[1]=='i')
				{
				range_i = atoi(cmd_buf+2);
				set_current_shunt(range_i);
				}
			if (cmd_buf[1]=='v')
				{
				range_v = atoi(cmd_buf+2);
				//set voltage range
				}
				strcpy(tx_str,"OK");
			}
		if (cmd_buf[0]=='d')
			{
			if (cmd_buf[1]=='a')
				{
				dac_val[0] = atoi(cmd_buf+2);
				dac_update = 1;
				strcpy(tx_str,"OK");
				}
			if (cmd_buf[1]=='b')
				{
				dac_val[1] = atoi(cmd_buf+2);
				dac_update = 1;
				strcpy(tx_str,"OK");
				}
			if (cmd_buf[1]=='c')
				{
				dac_val[2] = atoi(cmd_buf+2);
				dac_update = 1;
				strcpy(tx_str,"OK");
				}
			}
		if (cmd_buf[0]=='a')
			{
			strcpy(tx_str,"OK ");
			uart_txs(tx_str);
			tx_var_32(adc_res[0],0);
			uart_txs(" ");
			tx_var_32(adc_res[1],0);
			uart_txs(" ");
			tx_var_16(clamp_state,0);
			strcpy(tx_str," ");
			}
		if (cmd_buf[0]=='g')
			{
			tx_var_16(range_i,1);
			tx_var_16(range_v,1);
			tx_var_16(mode,1);
			tx_var_32(adc_res[0],1);
			tx_var_32(adc_res[1],1);
			tx_var_16(dac_val[0],1);
			tx_var_16(dac_val[1],1);
			tx_var_16(dac_val[2],1);
			strcpy(tx_str,"OK");
			}
		if (cmd_buf[0]=='r')
			{
			if (cmd_buf[1]=='o')
				{
				if (cmd_buf[2]=='1') OUT_ON_H;
				else OUT_ON_L;
				}
			if (cmd_buf[1]=='r')
				{
				if (cmd_buf[2]=='1') REMOTE_H;
				else REMOTE_L;
				}
			strcpy(tx_str,"OK");
			}
		if (cmd_buf[0]=='s')
			{
			if (cmd_buf[1]=='a')
				{
				if (cmd_buf[2]=='1') VRANGEL_H;
				else VRANGEL_L;
				}
			if (cmd_buf[1]=='b')
				{
				if (cmd_buf[2]=='1') FDACLO_H;
				else FDACLO_L;
				}
			strcpy(tx_str,"OK");
			}
		uart_txs(tx_str);
		uart_txs("\n");
		}
	}
void adc_tasks	(void)
	{
	uint8_t adc_status;
	adc_status = adc_read_8(0x00);
	if ((adc_status&0x80)==0) adc_res[adc_status&0x01] = adc_read_24(0x04);
	}

void dac_tasks (void)	
	{
	if (dac_update==1)
		{
		dac_write(0x38,dac_val[0]);	//FDACN - CHANNEL D
		dac_write(0x34,dac_val[1]);	//CL+ - CHANNEL C
		dac_write(0x31,dac_val[2]); //CL- - CHANNEL A
		dac_update = 0;
		}
	}

void io_tasks (void)
	{
	clamp_state = CLAMP_V;
	}

int main (void)
{
//	uint8_t i;
	DDRA = 0xF7; 
	DDRB = 0xFF; 
	DDRC = 0xF7; 
	DDRD = 0xFC; 
   	UCR = (1 << RXEN) | (1 << TXEN);   	// Turn on the transmission and reception circuitry
	UCR	 |= (1 << RXCIE);
   	UBRR = BAUD_PRESCALE; 				// Load lower 8-bits of the baud rate value into the low byte of the UBRR register
	TCNT1 = 63974;
	TCCR1A = 0x00;
	TCCR1B = (1<<CS10) | (1<<CS11);
	TCNT0=0x00;
	TCCR0 = (1<<CS02) | (1<<CS00);
	TIMSK=(1<<TOIE0) | (1<<TOIE1);
	sei();
	VMODE_H;
	IMODE_H;	
	CSADC_H;
	CSDAC_H;
	SCK_H;
	_delay_ms(200);
	dac_write(0x70,0x0000);
	dac_write(0x4F,0x0000);
	_delay_us(50);
	dac_write(0x60,0x0001);
	_delay_us(50);
	adc_write_16(0x10,0x8000 | (0x00<<5) | (0x15<<0));
	adc_write_16(0x11,0x8000 | (0x02<<5) | (0x15<<0));
//	adc_write_16(0x12,0x8000 | (0x15<<5) | (0x16<<0));
//	adc_write_16(0x13,0x8000 | (0x13<<5) | (0x14<<0));
	adc_write_16(0x20,0x1300);
	adc_write_16(0x28,0x0514);
	dac_val[0] = 32767;
	dac_val[1] = 32767;
	dac_val[2] = 32767;

	while (1)
		{
		serial_tasks();
		adc_tasks();
		dac_tasks();
		io_tasks();
		}

	while(1) 
		{
		//dac_write(0x3F,out);
		out = out + 0x1000;
		uart_txs("S");
		x = adc_read_8(0x00);
		itoa(x,tx_str,16);
		uart_txs(tx_str);
		uart_txs(" ");		
		if ((x&0x80)==0)
			{
			y = adc_read_24(0x04);
			ltoa(y,tx_str,16);
			uart_txs(tx_str);
			}
		uart_txs("\r\n");
   		BIT_SET(PORTC,6);
		_delay_ms(5);
   		BIT_CLEAR(PORTC,6);
		_delay_ms(100);
		}
}
