#define FCY 40000000	    //running at 40 MIPS
#include <libpic30.h>


#define	delay_us __delay_us
#define	delay_ms __delay_ms

#define	QMSG_LEN	10
#define	QLEN		10
#define	MAX_AVG_LEN	17
#define	INOUT_MSG_LEN	30
#define	UART_RX_BUF_LEN	30
#define	UART_TX_BUF_LEN	50

#define	FAN_TEMP_LEVEL1	380	//fan control threshols 1 - in tenths of degree Celsius
#define	FAN_TEMP_LEVEL2	450	//fan control threshols 2
#define	FAN_TEMP_HYST	20	//fan control hystersis

#define	UART_1_BAUD	19200	    //this one talks to world via USB/serial converter
#define	UART_2_BAUD	19200	    //this one communicates with main analog board


#define ENC_A_P	PORTB
#define ENC_A_B	1
#define ENC_B_P	PORTB
#define ENC_B_B	2
#define BS(number,bit) (number|=(1<<bit))		
#define BC(number,bit) (number&=(~(1<<bit)))
#define BT(number,bit) (number ^=(1<<bit))
#define BV(number,bit) (number &(1<<bit))

#define SR_CLK_P   LATB
#define SR_CLK_B   11
#define SR_OE_P    LATB
#define SR_OE_B    10
#define SR_LE_P    LATB
#define SR_LE_B    9
#define SR_DI_P    LATB
#define SR_DI_B    8

#define	ATN2_P	PORTF
#define	ATN2_B	6


#define AS0_P   LATB
#define AS0_B   0
#define AS1_P   LATB
#define AS1_B   12
#define AS2_P   LATB
#define AS2_B   13



#define	EX_CS_P		LATC
#define	EX_CS_B		2
#define	EX_MISO_P	PORTB
#define	EX_MISO_B	3
#define	EX_MOSI_P	LATB
#define	EX_MOSI_B	4
#define	EX_SCK_P	LATB
#define	EX_SCK_B	5

#define	FAN_ON_P	LATD
#define	FAN_ON_B	8
#define	FAN_SP_P	LATD
#define	FAN_SP_B	9

#define EE_MISO_P   PORTD
#define EE_MISO_B   0
#define EE_MOSI_P   LATD
#define EE_MOSI_B   11
#define EE_SCK_P    LATD
#define EE_SCK_B    10
#define EE_CS_P	    LATC
#define EE_CS_B	    13

#define	ADC_CHNL_TEMPER	14	//temperature sensor is connected to this ADC channel



void uart1_tx (unsigned char data);
void uart1_txs (char * data);
void uart2_tx (unsigned char data);
void uart2_txs (char * data);
void sr_shiftout (unsigned int data);
void d_anode (unsigned char data);
unsigned int segment_order (unsigned int in);
unsigned char spi_trf (unsigned char data);
void exp_write (unsigned char addr, unsigned char data);
unsigned char exp_read (unsigned char addr);
unsigned int map_keys (unsigned int input);
unsigned int map_leds (unsigned int input);
void hw_init (void);
unsigned char ee_spi_trf (unsigned char data);
void ee_wren (void);
void ee_wrdi (void);
unsigned char ee_rdsr (void);
unsigned char ee_read_byte (unsigned int addr);
unsigned char ee_write_byte (unsigned int addr, unsigned char data);
unsigned char ee_write_page (unsigned int addr, unsigned char * data, unsigned char pagesize);
void ee_read_page (unsigned int addr, unsigned char * data, unsigned char pagesize);
long ee_read_long (unsigned int laddr);
unsigned char ee_write_long (unsigned int laddr, long value);
unsigned int get_adc (unsigned char chnl);
void set_fan_speed (unsigned char val);
unsigned char get_compliance_pin_state (void);
