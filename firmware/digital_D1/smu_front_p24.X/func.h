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
uint16_t INT;
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
uint16_t INT;
}led_var;


typedef struct cal_single 
{
   int32_t offset;
   int32_t gain;
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
	
	
uint8_t mainboard_msg_enqueue (char * msg);
uint8_t mainboard_msg_qlen (void);
uint8_t mainboard_msg_dequeue (char * msg);
uint8_t mainboard_comms (uint8_t mb_state);
uint8_t mainboard_rv_enqueue (uint8_t range);
uint8_t mainboard_ri_enqueue (uint8_t range);
uint8_t mainboard_dac_enqueue (uint8_t dac, uint16_t value);
uint16_t get_dac_volt (int32_t volt_val);
uint16_t get_dac_curr (int32_t curr_val);
uint16_t get_dac_cvolt (int32_t volt_val);
uint16_t get_dac_ccurr (int32_t curr_val);
void enc_set_long (int32_t * var_long, int enc_count, uint8_t num_ptr, int32_t limit_low, int32_t limit_up);
void enc_inc_int (int * var_int, int enc_count);
int32_t get_volt_from_adc (uint32_t adcval);
int32_t get_curr_from_adc (uint32_t adcval);
int conv_adc_temp (uint16_t adcval);
int32_t adjust_long_offset_gain (int32_t offset, int32_t gain, int32_t value);
int32_t get_cal_const_num (uint8_t num, cal_type * cal_con);
void set_cal_const_num (uint8_t num, cal_type * cal_con, int32_t value);
uint8_t ee_write_cal_consts (uint8_t set, cal_type * cal_con);
uint8_t ee_read_cal_consts (unsigned char set, cal_type * cal_con);
float conv_setcurr_fval (int32_t scurr, uint8_t srange);
float conv_setvolt_fval (int32_t svolt, uint8_t srange);
void conv_fval_setcurr (float val_out, float val_range, int32_t * scurr, uint8_t * srange, uint8_t arange);
void conv_fval_setvolt (float val_out, float val_range, int32_t * svolt, uint8_t * srange, uint8_t arange);
