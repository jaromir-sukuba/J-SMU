#define	CAL_CONST_NUM	54	//this much calibration constants
#define	MENU_ITEMS	4	

#define	OUT_MODE_FVMI	1
#define	OUT_MODE_FIMV	0

#define	FAN_STATE_OFF	0
#define	FAN_STATE_MID	1
#define	FAN_STATE_FULL	2

#define	DISP_STATE_DEFAULT  0
#define	DISP_STATE_MENU	    1

#define	OUTPUT_ON   1
#define	OUTPUT_OFF  0

#define	RANGE_VOLT_MIN	1
#define	RANGE_VOLT_MAX	2
#define	RANGE_CURR_MIN	0
#define	RANGE_CURR_MAX	5

#define	DISPLAY_LEN	18


#define		VER_STRING	"V 1-0"

typedef union
{
struct
 {
    unsigned k1:1;
    unsigned k2:1;
    unsigned k3:1;
    unsigned k4:1;
    unsigned k5:1;
    unsigned k6:1;
    unsigned k7:1;
 	unsigned k8:1;
	unsigned k9:1;
    unsigned k10:1;
    unsigned k11:1;
    unsigned k12:1;
 	unsigned k13:1;
	unsigned k14:1;
	unsigned k15:1;
	unsigned kx:1;
 };
unsigned int INT;
}key_var;

typedef union
{
struct
 {
    unsigned led1:1;
    unsigned led2:1;
    unsigned led3:1;
    unsigned led4:1;
    unsigned led5:1;
    unsigned led6:1;
    unsigned led7:1;
 	unsigned led8:1;
	unsigned led9:1;
	unsigned ledx:7;
 };
unsigned int INT;
}led_var;


typedef struct cal_single 
{
   long offset;
   long gain;
} cal_single;

typedef struct c_fvmi
	{
	cal_single volt_read[3];
	cal_single volt_set[3];
	cal_single curr_read[6];
	} c_fvmi;

typedef struct c_fimv
	{
	cal_single curr_read[6];
	cal_single curr_set[6];
	cal_single volt_read[3];
	} c_fimv;

typedef struct cal_type
	{
	c_fvmi fvmi;
	c_fimv fimv;
	} cal_type;
	
	
unsigned char mainboard_msg_enqueue (char * msg);
unsigned char mainboard_msg_qlen (void);
unsigned char mainboard_msg_dequeue (char * msg);
unsigned char mainboard_comms (unsigned char mb_state);
unsigned char mainboard_rv_enqueue (unsigned char range);
unsigned char mainboard_ri_enqueue (unsigned char range);
unsigned char mainboard_dac_enqueue (unsigned char dac, unsigned int value);
unsigned int get_dac_volt (long volt_val);
unsigned int get_dac_curr (long curr_val);
unsigned int get_dac_cvolt (long volt_val);
unsigned int get_dac_ccurr (long curr_val);
void enc_set_long (long * var_long, int enc_count, unsigned char num_ptr, long limit_low, long limit_up);
void enc_inc_int (int * var_int, int enc_count);
long get_volt_from_adc (unsigned long adcval);
long get_curr_from_adc (unsigned long adcval);
int conv_adc_temp (unsigned int adcval);
long adjust_long_offset_gain (long offset, long gain, long value);
long get_cal_const_num (unsigned char num, cal_type * cal_con);
void set_cal_const_num (unsigned char num, cal_type * cal_con, long value);
unsigned char ee_write_cal_consts (unsigned char set, cal_type * cal_con);
unsigned char ee_read_cal_consts (unsigned char set, cal_type * cal_con);
