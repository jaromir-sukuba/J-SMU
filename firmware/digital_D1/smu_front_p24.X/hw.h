#define FCY 40000000	    //running at 40 MIPS
#include <libpic30.h>


#define	delay_us __delay_us
#define	delay_ms __delay_ms

#define SCPI_IDN1 "JS"
#define SCPI_IDN2 "JSMU"
#define SCPI_IDN3 NULL
#define SCPI_IDN4 "01-02"
#define SCPI_ERROR_QUEUE_SIZE 17
#define SCPI_INPUT_BUFFER_LENGTH 256
#define SMALL_BUFFER_LEN 50

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



void uart1_tx (uint8_t data);
void uart1_txs (char * data);
void uart2_tx (uint8_t data);
void uart2_txs (char * data);
void sr_shiftout (uint16_t data);
void d_anode (uint8_t data);
uint16_t segment_order (uint16_t in);
uint8_t spi_trf (uint8_t data);
void exp_write (uint8_t addr, uint8_t data);
uint8_t exp_read (uint8_t addr);
uint16_t map_keys (uint16_t input);
uint16_t map_leds (uint16_t input);
void hw_init (void);
uint8_t ee_spi_trf (uint8_t data);
void ee_wren (void);
void ee_wrdi (void);
uint8_t ee_rdsr (void);
uint8_t ee_read_byte (uint16_t addr);
uint8_t ee_write_byte (uint16_t addr, uint8_t data);
uint8_t ee_write_page (uint16_t addr, uint8_t * data, uint8_t pagesize);
void ee_read_page (uint16_t addr, uint8_t * data, uint8_t pagesize);
long ee_read_long (uint16_t laddr);
uint8_t ee_write_long (uint16_t laddr, int32_t value);
uint16_t get_adc (uint8_t chnl);
void set_fan_speed (uint8_t val);
uint8_t get_compliance_pin_state (void);



