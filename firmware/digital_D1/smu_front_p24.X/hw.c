#include <xc.h>
#include "hw.h"

//PIC hardware config bytes setting
// FOSCSEL
#pragma config FNOSC = PRIPLL           // Oscillator Mode (Primary Oscillator (XT, HS, EC) w/ PLL)
#pragma config IESO = OFF               // Two-speed Oscillator Start-Up Enable (Start up with user-selected oscillator)
// FOSC
#pragma config POSCMD = HS              // Primary Oscillator Source (HS Oscillator Mode)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function (OSC2 pin has clock out function)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)
// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler (1:32,768)
#pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)
// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)
// FICD
#pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)


//slighly altered from https://github.com/dmadison/LED-Segment-ASCII
const unsigned int ASCII[96] = {
	0b000000000000000, /* (space) */
	0b100000000000110, /* ! */
	0b000001000000010, /* " */
	0b001001011001110, /* # */
	0b001001011101101, /* $ */
	0b011111111100100, /* % */
	0b010001101011001, /* & */
	0b000001000000000, /* ' */
	0b010010000000000, /* ( */
	0b000100100000000, /* ) */
	0b011111111000000, /* * */
	0b001001011000000, /* + */
	0b000100000000000, /* , */
	0b000000011000000, /* - */
	0b100000000000000, /* . */
	0b000110000000000, /* / */
	0b000110000111111, /* 0 */
	0b000010000000110, /* 1 */
	0b000000011011011, /* 2 */
	0b000010010001101, /* 3 */
	0b000000011100110, /* 4 */
	0b010000001101001, /* 5 */
	0b000000011111101, /* 6 */
	0b000000000000111, /* 7 */
	0b000000011111111, /* 8 */
	0b000000011101111, /* 9 */
	0b001001000000000, /* : */
	0b000101000000000, /* ; */
	0b010010001000000, /* < */
	0b000000011001000, /* = */
	0b000100110000000, /* > */
	0b101000010000011, /* ? */
	0b000001010111011, /* @ */
	0b000000011110111, /* A */
	0b001001010001111, /* B */
	0b000000000111001, /* C */
	0b001001000001111, /* D */
	0b000000001111001, /* E */
	0b000000001110001, /* F */
	0b000000010111101, /* G */
	0b000000011110110, /* H */
	0b001001000001001, /* I */
	0b000000000011110, /* J */
	0b010010001110000, /* K */
	0b000000000111000, /* L */
	0b000010100110110, /* M */
	0b010000100110110, /* N */
	0b000000000111111, /* O */
	0b000000011110011, /* P */
	0b010000000111111, /* Q */
	0b010000011110011, /* R */
	0b000000011101101, /* S */
	0b001001000000001, /* T */
	0b000000000111110, /* U */
	0b000110000110000, /* V */
	0b010100000110110, /* W */
	0b010110100000000, /* X */
	0b000000011101110, /* Y */
	0b000110000001001, /* Z */
	0b000000000111001, /* [ */
	0b010000100000000, /* \ */
	0b000000000001111, /* ] */
	0b010100000000000, /* ^ */
	0b000000000001000, /* _ */
	0b000000100000000, /* ` */
	0b001000001011000, /* a */
	0b010000001111000, /* b */
	0b000000011011000, /* c */
	0b000100010001110, /* d */
	0b000100001011000, /* e */
	0b001010011000000, /* f */
	0b000010010001110, /* g */
	0b001000001110000, /* h */
	0b001000000000000, /* i */
	0b000101000010000, /* j */
	0b011011000000000, /* k */
	0b000000000110000, /* l */
	0b001000011010100, /* m */
	0b001000001010000, /* n */
	0b000000011011100, /* o */
	0b000000101110000, /* p */
	0b000010010000110, /* q */
	0b000000001010000, /* r */
	0b010000010001000, /* s */
	0b000000001111000, /* t */
	0b000000000011100, /* u */
	0b000100000010000, /* v */
	0b010100000010100, /* w */
	0b010110100000000, /* x */
	0b000001010001110, /* y */
	0b000100001001000, /* z */
	0b000100101001001, /* { */
	0b001001000000000, /* | */
	0b010010010001001, /* } */
	0b000110011000000, /* ~ */
	0b000000000000000, /* (del) */
};

//uart functions, to transmit single byte or null terminated string
void uart1_tx (unsigned char data)
	{
	U1TXREG = data;
	while (U1STAbits.TRMT==0);
	}

void uart1_txs (char * data)
	{
	while (*data!=0) uart1_tx(*data++);
	}

void uart2_tx (unsigned char data)
	{
	U2TXREG = data;
	while (U2STAbits.TRMT==0);
	}

void uart2_txs (char * data)
	{
	while (*data!=0) uart2_tx(*data++);
	}

//shift out data to serial register with LEDs on it
void sr_shiftout (unsigned int data)
    {
    unsigned char i;
    for (i=0;i<16;i++)
        {
        if (data&0x8000)
            BS(SR_DI_P,SR_DI_B);
        else
            BC(SR_DI_P,SR_DI_B);
		delay_us(1);
        BS(SR_CLK_P,SR_CLK_B);
		delay_us(1);
        data = data<<1;
        BC(SR_CLK_P,SR_CLK_B);
		delay_us(1);
        }
    }

//select proper display multiplex, or anode
void d_anode (unsigned char data)
	{
	if (data&0x01)  BS(AS0_P,AS0_B);
		else        BC(AS0_P,AS0_B);
	if (data&0x02)  BS(AS1_P,AS1_B);
		else        BC(AS1_P,AS1_B);
	if (data&0x04)  BS(AS2_P,AS2_B);
		else        BC(AS2_P,AS2_B);
	}


//map messy segment order to something more palatable, to be compatible with ASCII table above
unsigned int segment_order (unsigned int in)
	{
	unsigned int out=0;
	if (in&(1<<0)) out|=(1<<0);
	if (in&(1<<1)) out|=(1<<1);
	if (in&(1<<2)) out|=(1<<2);
	if (in&(1<<3)) out|=(1<<3);
	if (in&(1<<4)) out|=(1<<4);
	if (in&(1<<5)) out|=(1<<5);
	if (in&(1<<6)) out|=(1<<12);
	if (in&(1<<7)) out|=(1<<8);
	if (in&(1<<8)) out|=(1<<13);
	if (in&(1<<9)) out|=(1<<6);
	if (in&(1<<10)) out|=(1<<7);
	if (in&(1<<11)) out|=(1<<11);
	if (in&(1<<12)) out|=(1<<10);
	if (in&(1<<13)) out|=(1<<9);
	if (in&(1<<14)) out|=(1<<14);
	return out;
	}

//transmit SPI byte to SPI expander, this code has known bug - the bit order is wrong, but in this case it
//doesn't matter much. Keys are correctly mapped to this, so I'm not going to change it unless needed
unsigned char spi_trf (unsigned char data)
	{
	unsigned char i,ret=0;
	for (i=0;i<8;i++)
		{
		if (data&0x80)
			BS(EX_MOSI_P,EX_MOSI_B);
		else
			BC(EX_MOSI_P,EX_MOSI_B);
		delay_us(1);
		data = data << 1;
		BS(EX_SCK_P,EX_SCK_B);
		ret = ret >> 1;
		delay_us(1);
		if (BV(EX_MISO_P,EX_MISO_B))
			ret|=0x80;
		delay_us(1);
		BC(EX_SCK_P,EX_SCK_B);
		}
		return ret;
	}

//read and write SPI IO expander
void exp_write (unsigned char addr, unsigned char data)
	{
	BC(EX_CS_P,EX_CS_B);
	spi_trf(0x40);
	spi_trf(addr);
	spi_trf(data);
	BS(EX_CS_P,EX_CS_B);
	}

unsigned char exp_read (unsigned char addr)
	{
	unsigned char retval;
	BC(EX_CS_P,EX_CS_B);
	spi_trf(0x41);
	spi_trf(addr);
	retval = spi_trf(0);
	BS(EX_CS_P,EX_CS_B);
	return retval;
	}

//map keys to proper order (first key is the one on lewer left)
unsigned int map_keys (unsigned int input)
	{
	unsigned int retval = 0;
	if (input&0x0010) retval|=0x0001;
	if (input&0x0008) retval|=0x0002;
	if (input&0x0002) retval|=0x0004;
	if (input&0x0004) retval|=0x0008;
	if (input&0x0200) retval|=0x0010;
	if (input&0x0001) retval|=0x0020;
	if (input&0x0080) retval|=0x0040;
	if (input&0x0100) retval|=0x0080;
	if (input&0x0020) retval|=0x0100;
	if (input&0x0040) retval|=0x0200;
	if (input&0x2000) retval|=0x0400;
	if (input&0x4000) retval|=0x0800;
	if (input&0x0800) retval|=0x1000;
	if (input&0x1000) retval|=0x2000;
	return retval;
	}

//map LEDs so that first is lower left
unsigned int map_leds (unsigned int input)
	{
	unsigned int retval = 0;
	if (input&0x0001) retval|=0x0100;
	if (input&0x0002) retval|=0x0400;
	if (input&0x0004) retval|=0x0200;
	if (input&0x0008) retval|=0x1000;
	if (input&0x0010) retval|=0x0800;
	if (input&0x0020) retval|=0x0004;
	if (input&0x0040) retval|=0x0002;
	if (input&0x0080) retval|=0x0010;
	if (input&0x0100) retval|=0x0008;
	return retval;
	}

//another bitbanged SPI function, this time with proper bit order, as it matters for EEPROM
unsigned char ee_spi_trf (unsigned char data)
	{
	unsigned char i,ret=0;
	for (i=0;i<8;i++)
		{
		if (data&0x80)
			BS(EE_MOSI_P,EE_MOSI_B);
		else
			BC(EE_MOSI_P,EE_MOSI_B);
		delay_us(1);
		data = data << 1;
		BS(EE_SCK_P,EE_SCK_B);
		ret = ret << 1;
		delay_us(1);
		if (BV(EE_MISO_P,EE_MISO_B))
			ret|=0x01;
		delay_us(1);
		BC(EE_SCK_P,EE_SCK_B);
		}
	return ret;
	}

//ee functions below are mostly implementation of various EEPROM work modes, as per datasheet; nothing to see here
void ee_wren (void)
	{
	BC(EE_CS_P,EE_CS_B);
	ee_spi_trf(0x06);
	BS(EE_CS_P,EE_CS_B);
	}

void ee_wrdi (void)
	{
	BC(EE_CS_P,EE_CS_B);
	ee_spi_trf(0x04);
	BS(EE_CS_P,EE_CS_B);
	}

unsigned char ee_rdsr (void)
	{
	unsigned char retval;
	BC(EE_CS_P,EE_CS_B);
	ee_spi_trf(0x05);
	retval = ee_spi_trf(0);
	BS(EE_CS_P,EE_CS_B);
	return retval;
	}


unsigned char ee_read_byte (unsigned int addr)
	{
	unsigned char retval;
	BC(EE_CS_P,EE_CS_B);
	ee_spi_trf(0x03);
	ee_spi_trf((addr>>8)&0xFF);
	ee_spi_trf((addr>>0)&0xFF);
	retval = ee_spi_trf(0);
	BS(EE_CS_P,EE_CS_B);
	return retval;
	}

unsigned char ee_write_byte (unsigned int addr, unsigned char data)
	{
	unsigned int to_count;
	ee_wren();
	BC(EE_CS_P,EE_CS_B);
	ee_spi_trf(0x02);
	ee_spi_trf((addr>>8)&0xFF);
	ee_spi_trf((addr>>0)&0xFF);
	ee_spi_trf(data);
	BS(EE_CS_P,EE_CS_B);
	while (1)
		{
		if ((ee_rdsr()&0x01)==0) return 0;
		else delay_us(100);
		to_count++;
		if (to_count>100) break;
		}
	return 1;
	}

unsigned char ee_write_page (unsigned int addr, unsigned char * data, unsigned char pagesize)
	{
	unsigned int to_count;
	unsigned char i;
	ee_wren();
	BC(EE_CS_P,EE_CS_B);
	ee_spi_trf(0x02);
	ee_spi_trf((addr>>8)&0xFF);
	ee_spi_trf((addr>>0)&0xFF);
	for (i=0;i<pagesize;i++) ee_spi_trf(*data++);
	BS(EE_CS_P,EE_CS_B);
	while (1)
		{
		if ((ee_rdsr()&0x01)==0) return 0;
		else delay_us(100);
		to_count++;
		if (to_count>100) break;
		}
	return 1;
	}

void ee_read_page (unsigned int addr, unsigned char * data, unsigned char pagesize)
	{
	unsigned char i;
	BC(EE_CS_P,EE_CS_B);
	ee_spi_trf(0x03);
	ee_spi_trf((addr>>8)&0xFF);
	ee_spi_trf((addr>>0)&0xFF);
	for (i=0;i<pagesize;i++) *data++ = ee_spi_trf(0);
	BS(EE_CS_P,EE_CS_B);
	}

//read from EERPROM one 4-byte page as single long number
long ee_read_long (unsigned int laddr)
	{
	long retval;
	unsigned char *p = (unsigned char*)&retval;
	ee_read_page(laddr*4,p,4);
	return retval;
	}

//write to EEPROM one 4-byte page as single long number
unsigned char ee_write_long (unsigned int laddr, long value)
	{
	unsigned char *p = (unsigned char*)&value;
	return ee_write_page(laddr*4,p,4);
	}

//get MCU internal ADC result on given channel
unsigned int get_adc (unsigned char chnl)
	{
	AD1CHS0 = chnl;
	AD1CON1bits.SAMP = 1;
	while (AD1CON1bits.DONE==0);
	return ADC1BUF0;
	}

//set fan speed level to two (+off) possible values
void set_fan_speed (unsigned char val)
	{
	if (val==1)	
		{
		BS(FAN_ON_P,FAN_ON_B);
		BS(FAN_SP_P,FAN_SP_B);
		return;
		}
	if (val==2)	
		{
		BS(FAN_ON_P,FAN_ON_B);
		BC(FAN_SP_P,FAN_SP_B);
		return;
		}
	BC(FAN_ON_P,FAN_ON_B);
	BC(FAN_SP_P,FAN_SP_B);
	}

//return state of pin indicating the main board is in compliance state
unsigned char get_compliance_pin_state (void)
	{
	if (BV(ATN2_P,ATN2_B)==0) return 1;
	else return 0;
	}

//init hardware to be used later
void hw_init (void)
	{
	CLKDIVbits.PLLPRE = 0;
	PLLFBD = 64-2;
	CLKDIVbits.PLLPOST = 0;
	TRISG = 0;
	TRISC = 0;
	TRISD = 0x0001;
	TRISB = 0xC0CE;
	AD1PCFGH = 0xFFFF;
	AD1PCFGL = 0xBFFF;

	U1BRG = (FCY / 16 / UART_1_BAUD) - 1;
	U1MODEbits.UARTEN = 1;
	_U1RXIE = 1;
	U1STAbits.UTXEN = 1;

	U2BRG = (FCY / 16 / UART_2_BAUD) - 1;
	U2MODEbits.UARTEN = 1;
	_U2RXIE = 1;
	U2STAbits.UTXEN = 1;

	PR1 = (FCY / 8 / 1000)*1;
	T1CONbits.TCKPS0 = 1;
	IEC0bits.T1IE = 1;
	T1CONbits.TON = 1;
	
	PR3 = (FCY / 8 / 1000)/2;
	T3CONbits.TCKPS0 = 1;
	IEC0bits.T3IE = 1;
	T3CONbits.TON = 1;
	BS(EX_CS_P,EX_CS_B);
	
	AD1CON1 = 0x04E0;
	AD1CON2 = 0;
	AD1CON3 = 0x8F00;
	AD1CON4 = 0;
	AD1CON1bits.ADON = 1;
	BS(EE_CS_P,EE_CS_B);
	
	exp_write(0x00,0);
	exp_write(0x00,0);
	exp_write(0x01,0xF8);
	exp_write(0x0D,0xF8);
	}
