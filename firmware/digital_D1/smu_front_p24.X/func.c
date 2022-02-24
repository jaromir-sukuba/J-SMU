#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "func.h"
#include "hw.h"

uint8_t msg_in_queue[(QLEN*QMSG_LEN)+25],msg_queue_ptr=0,rb_adc_arr_ptr=0;
char mb_msg_in_buf[INOUT_MSG_LEN],mb_msg_in_wait=0;
char mb_msg_out_buf[INOUT_MSG_LEN],mb_msg_out_rdy=0;
int32_t rb_adc_arr_1[MAX_AVG_LEN],rb_adc_arr_2[MAX_AVG_LEN];

extern volatile uint8_t rx2_rcvd_flag;
extern volatile char rx2_rcvd_str[UART_RX_BUF_LEN];
extern int32_t rb_adc_val_1, rb_adc_val_2;
extern uint8_t rb_adc_arr_len,avg_enabled;

//this one is hint for calibration, so you know what parameter N may be
const char cal_val_desc[CAL_CONST_NUM][30]= 
	{
	"fvmi.volt_read[0].offset",
	"fvmi.volt_read[0].gain",
	"fvmi.volt_read[1].offset",
	"fvmi.volt_read[1].gain",
	"fvmi.volt_read[2].offset",
	"fvmi.volt_read[2].gain",
	"fvmi.volt_set[0].offset",
	"fvmi.volt_set[0].gain",
	"fvmi.volt_set[1].offset",
	"fvmi.volt_set[1].gain",
	"fvmi.volt_set[2].offset",
	"fvmi.volt_set[2].gain",
	"fvmi.curr_read[0].offset",
	"fvmi.curr_read[0].gain",
	"fvmi.curr_read[1].offset",
	"fvmi.curr_read[1].gain",
	"fvmi.curr_read[2].offset",
	"fvmi.curr_read[2].gain",
	"fvmi.curr_read[3].offset",
	"fvmi.curr_read[3].gain",
	"fvmi.curr_read[4].offset",
	"fvmi.curr_read[4].gain",
	"fvmi.curr_read[5].offset",
	"fvmi.curr_read[5].gain",
	"fimv.curr_read[0].offset",
	"fimv.curr_read[0].gain",
	"fimv.curr_read[1].offset",
	"fimv.curr_read[1].gain",
	"fimv.curr_read[2].offset",
	"fimv.curr_read[2].gain",
	"fimv.curr_read[3].offset",
	"fimv.curr_read[3].gain",
	"fimv.curr_read[4].offset",
	"fimv.curr_read[4].gain",
	"fimv.curr_read[5].offset",
	"fimv.curr_read[5].gain",
	"fimv.curr_set[0].offset",
	"fimv.curr_set[0].gain",
	"fimv.curr_set[1].offset",
	"fimv.curr_set[1].gain",
	"fimv.curr_set[2].offset",
	"fimv.curr_set[2].gain",
	"fimv.curr_set[3].offset",
	"fimv.curr_set[3].gain",
	"fimv.curr_set[4].offset",
	"fimv.curr_set[4].gain",
	"fimv.curr_set[5].offset",
	"fimv.curr_set[5].gain",
	"fimv.volt_read[0].offset",
	"fimv.volt_read[0].gain",
	"fimv.volt_read[1].offset",
	"fimv.volt_read[1].gain",
	"fimv.volt_read[2].offset",
	"fimv.volt_read[2].gain",
	};


//three functions below, to put something into queue, take out of it and examine its length
uint8_t mainboard_msg_enqueue (char * msg)
	{
	uint8_t r;
	uint16_t i;
	if (msg_queue_ptr<QLEN)
		{
//		memmove(msg_in_queue+QMSG_LEN,msg_in_queue,QMSG_LEN*(QLEN-1));
		for (r=QMSG_LEN*(QLEN-1);r>0;r--) msg_in_queue[r+QMSG_LEN-1] = msg_in_queue[r-1];
//		memset(msg_in_queue,0,QMSG_LEN);		
		for (i=QMSG_LEN;i>0;i--) msg_in_queue[i-1] = 0;
		//strncpy(msg_in_queue,msg,QMSG_LEN);
		for (i=0;i<QMSG_LEN;i++) msg_in_queue[i] = msg[i];
		msg_queue_ptr++;
		return 0;
		}
	else
		return 1;
	}

uint8_t mainboard_msg_dequeue (char * msg)
	{
	uint16_t i;
	if (msg_queue_ptr>0)
		{
		//strncpy(msg,msg_in_queue+QMSG_LEN*(msg_queue_ptr-1),QMSG_LEN);
		for (i=0;i<QMSG_LEN;i++) msg[i] = msg_in_queue[i+(QMSG_LEN*(msg_queue_ptr-1))];
		//memset(msg_in_queue+QMSG_LEN*(msg_queue_ptr-1),0,QMSG_LEN);
		for (i=QMSG_LEN;i>0;i--) msg_in_queue[QMSG_LEN*(msg_queue_ptr-1)+i-1] = 0;	
		msg_queue_ptr--;
		return 0;
		}
	else
		return 1;
	}

uint8_t mainboard_msg_qlen (void)
	{
	return msg_queue_ptr;
	}


uint8_t mainboard_comms (uint8_t mb_state)
	{
	static int16_t to_cnt;
	uint16_t i;
	char *eptr;
	to_cnt++;

	//something new to transmit? if yes, do so
	if (mainboard_msg_qlen()>0)
		{
		if (mb_msg_in_wait==0)
			{
			mainboard_msg_dequeue(mb_msg_in_buf);
			mb_msg_in_wait=1;
			}
		}	
	if (mb_state==0)
		{
		to_cnt = 0;
		if (mb_msg_in_wait==1)
			{
			rx2_rcvd_flag = 0;
			uart2_txs((char *)mb_msg_in_buf);
			uart2_txs("\n");
			mb_state=1;		
			}
		}
	if (mb_state==1)
		{
		if (to_cnt>50) mb_state=4;
		if (rx2_rcvd_flag)
			{
			rx2_rcvd_flag = 0;		
			if (strncmp((char *) rx2_rcvd_str,"OK",2)==0) 
				{
				strncpy(mb_msg_out_buf,(char *)rx2_rcvd_str+3,30);
				mb_state=5;
				}
			else
				mb_state=3;
			}
		}
	//BS received - this should be handled in some way
	if (mb_state==3)
		{
		mb_state=0;
		}

	//timeout - this should be handled in some way
	if (mb_state==4)
		{
		mb_state=0;
		}

	//looks like we received something correct
	if (mb_state==5)
		{
		mb_state=0;
		mb_msg_in_wait=0;
		if (mb_msg_in_buf[0]=='a')
			{
			rb_adc_val_1 = strtol(mb_msg_out_buf,&eptr,10);
			rb_adc_val_2 = strtol(eptr,&eptr,10);
			rb_adc_arr_1[rb_adc_arr_ptr] = rb_adc_val_1;
			rb_adc_arr_2[rb_adc_arr_ptr] = rb_adc_val_2;
			rb_adc_arr_ptr++;
			if (rb_adc_arr_ptr>=rb_adc_arr_len) rb_adc_arr_ptr=0;

			if ((rb_adc_arr_len!=1)&(avg_enabled==1))
				{
				rb_adc_val_1 = 0;
				rb_adc_val_2 = 0;
				for (i=0;i<rb_adc_arr_len;i++) 
					{
					rb_adc_val_1 = rb_adc_val_1 + rb_adc_arr_1[i];
					rb_adc_val_2 = rb_adc_val_2 + rb_adc_arr_2[i];
					}
				rb_adc_val_1 = rb_adc_val_1 / rb_adc_arr_len;
				rb_adc_val_2 = rb_adc_val_2 / rb_adc_arr_len;
				}
			}
		}
		
	return mb_state;
	}

//enqueue proper messages depending on new voltage range to be selected
uint8_t mainboard_rv_enqueue (uint8_t range)
	{
	if (range==0)
		{
		mainboard_msg_enqueue("sb1");
		return mainboard_msg_enqueue("sa0");
		}
	if (range==1)
		{
		mainboard_msg_enqueue("sb0");
		return mainboard_msg_enqueue("sa0");
		}
	if (range==2)
		{
		mainboard_msg_enqueue("sb0");
		return mainboard_msg_enqueue("sa1");
		}
	return 0;
	}

//enqueue proper messages depending on new current range to be selected
uint8_t mainboard_ri_enqueue (uint8_t range)
	{
	if (range==0) return mainboard_msg_enqueue("ri0");
	if (range==1) return mainboard_msg_enqueue("ri1");
	if (range==2) return mainboard_msg_enqueue("ri2");
	if (range==3) return mainboard_msg_enqueue("ri3");
	if (range==4) return mainboard_msg_enqueue("ri4");
	if (range==5) return mainboard_msg_enqueue("ri5");
	return 1;
	}

//formulate and enqueue DAC messages
uint8_t mainboard_dac_enqueue (uint8_t dac, uint16_t value)
	{
	char dac_str[10];
	if (dac>2) return 1;
	sprintf (dac_str,"d%c%u",'a'+dac,value);
	return mainboard_msg_enqueue(dac_str);
	}

//uncalibrated, set up DAC range to voltage set
uint16_t get_dac_volt (int32_t volt_val)
	{
	int32_t tmp;
	uint16_t retval;
	tmp = -volt_val;
	tmp = tmp * 2074;
	tmp = tmp / 1000;
	tmp = 32767-tmp;
	retval = tmp;	
	return retval;
	}

//uncalibrated, set up DAC range to current set
uint16_t get_dac_curr (int32_t curr_val)
	{
	int32_t tmp;
	uint16_t retval;
	tmp = -curr_val;
	tmp = tmp * 3169;
	tmp = tmp / 10000;
	tmp = 32767-tmp;
	retval = tmp;	
	return retval;
	}

//uncalibrated, set up clamp DAC range to voltage set
uint16_t get_dac_cvolt (int32_t volt_val)
	{
	int32_t tmp;
	uint16_t retval;
	tmp = volt_val;
	tmp = tmp * 1977;
	tmp = tmp / 1000;
	//tmp = 32767-tmp;
	retval = tmp;	
	return retval;
	}

//uncalibrated, set up clamp DAC range to current set
uint16_t get_dac_ccurr (int32_t curr_val)
	{
	int32_t tmp;
	uint16_t retval;
	tmp = curr_val;
	tmp = tmp * 3021;
	tmp = tmp / 10000;
	//tmp = 32767-tmp;
	retval = tmp;	
	return retval;
	}

//adjust generic long variable at specific digit (viewed from human-centric decadic point of view)
void enc_set_long (int32_t * var_long, int16_t enc_count, uint8_t num_ptr, int32_t limit_low, int32_t limit_up)
	{
	int32_t tmp;
	tmp = *var_long;
	if (num_ptr==5) tmp += (enc_count*1);
	if (num_ptr==4) tmp += (enc_count*10);
	if (num_ptr==3) tmp += (enc_count*100);
	if (num_ptr==2) tmp += (enc_count*1000);
	if (num_ptr==1) tmp += (enc_count*10000);	
	if (tmp>limit_up) tmp = limit_up;
	if (tmp<limit_low) tmp = limit_low;
	*var_long = tmp;
	}

//something similar to int variables
void enc_inc_int (int16_t* var_int, int16_t enc_count)
	{
	int32_t tmp;
	tmp = *var_int;
	tmp += enc_count;
	*var_int = tmp;
	}

//extract uncalibrated voltage from ADC
int32_t get_volt_from_adc (uint32_t adcval)
	{
	int32_t temp;
	temp = 8388608 - (adcval);
	temp = temp * -100;
	temp = temp / 5042;
	return -temp;
	}

//extract uncalibrated current from ADC
int32_t get_curr_from_adc (uint32_t adcval)
	{
	int32_t temp;
	temp = 8388608 - (adcval);
	temp = temp * -100;
	temp = temp / 780;
	return -temp;
	}

//get adc counts to temperature, in tenths of degC, ex.: 234 is 23,4dC
int16_t conv_adc_temp (uint16_t adcval)
	{
	uint16_t temp;	
	int16_t retval;
	if (adcval<1800) return 1000;
	if (adcval>2400) return 1000;
	temp = adcval;
	temp = temp * 13;
	temp = temp / 10;
	temp = temp - 2283;
	retval = temp;
	return retval;
	}

//adjust long variable with offset and gain
int32_t adjust_long_offset_gain (int32_t offset, int32_t gain, int32_t value)
	{
	long long temp;
	int32_t retval;
	temp = value + offset;
	temp = temp * gain;
	temp = temp / 1000000L;
	retval = temp;
	return retval;
	}

//get calibration constant from calibration structure by number
int32_t get_cal_const_num (uint8_t num, cal_type * cal_con)
	{
	int32_t retval;
	uint32_t *p = (uint32_t*)&(cal_con->fvmi.volt_read[0].offset);
	p = p + num;
	retval = *p;
	return retval;
	}

//set calibration constant in calibration structure by number
void set_cal_const_num (uint8_t num, cal_type * cal_con, int32_t value)
	{
	uint32_t *p = (uint32_t*)&(cal_con->fvmi.volt_read[0].offset);
	p = p + num;
	*p = value;
	}

//write down calibration constants to EEPROM. We can have more than one set of cal constants
uint8_t ee_write_cal_consts (uint8_t set, cal_type * cal_con)
	{
	uint16_t laddr = ((uint16_t)(set)) * 128;
	uint16_t i;
	int32_t val;
	for (i=0;i<CAL_CONST_NUM;i++)
		{
		val = get_cal_const_num(i,cal_con);
		ee_write_long(laddr+i,val);
		}
	return 0;
	}

//read calibration constants from EEPROM
uint8_t ee_read_cal_consts (uint8_t set, cal_type * cal_con)
	{
	uint16_t laddr = set * 128;
	uint16_t i;
	int32_t val;
	for (i=0;i<CAL_CONST_NUM;i++)
		{
		val = ee_read_long(laddr+i);
		set_cal_const_num(i,cal_con,val);
		}
	return 0;
	}


float conv_setcurr_fval (int32_t scurr, uint8_t srange)
	{
	if (srange==0) return ((float)(scurr))/1E11;
	if (srange==1) return ((float)(scurr))/1E10;
	if (srange==2) return ((float)(scurr))/1E9;
	if (srange==3) return ((float)(scurr))/1E8;
	if (srange==4) return ((float)(scurr))/1E7;
	if (srange==5) return ((float)(scurr))/1E6;
	return 0.0;
	}

//magic numbers here, should be cleaned up
float conv_setvolt_fval (int32_t svolt, uint8_t srange)
	{
	if (srange==0) return ((float)(svolt))/10000;
	if (srange==1) return ((float)(svolt))/1000;
	if (srange==2) return ((float)(svolt))/100;
	return 0.0;
	}

//quite a bit of magic woowoo here, should be cleaned up
void conv_fval_setcurr (float val_out, float val_range, int32_t * scurr, uint8_t * srange, uint8_t arange)
	{
	float vtemp=0.0;
	vtemp = val_range;
	if (val_range<0.0) vtemp = -val_range;
	if (vtemp<1E-6) *srange = 0;
	else if (vtemp<1E-5) *srange = 1;
	else if (vtemp<1E-4) *srange = 2;
	else if (vtemp<1E-3) *srange = 3;
	else if (vtemp<1E-2) *srange = 4;
	else if (vtemp<1E-1) *srange = 5;
	else *srange = 1;
	if (*srange==0) vtemp = val_out*1E11;
	else if (*srange==1) vtemp = val_out*1E10;
	else if (*srange==2) vtemp = val_out*1E9;
	else if (*srange==3) vtemp = val_out*1E8;
	else if (*srange==4) vtemp = val_out*1E7;
	else if (*srange==5) vtemp = val_out*1E6;
	if (vtemp>99999.0) vtemp = 99999.0;
	if (vtemp<-99999.0) vtemp = -99999.0;
	*scurr = (int32_t)(vtemp);
	}

//quite a bit of specific magic numbers here, should be cleaned up
void conv_fval_setvolt (float val_out, float val_range, int32_t * svolt, uint8_t * srange, uint8_t arange)
	{
	float vtemp=0.0;
	if (arange==1) val_range = val_out;
	*srange = 1;
	if (abs(val_range)<12) *srange = 1;
	else if (abs(val_range)<120) *srange = 2;
	if (*srange==1) vtemp = val_out*1000;
	else if (*srange==2) vtemp = val_out*100;
	if (vtemp>11999.0) vtemp = 11999.0;
	if (vtemp<-11999.0) vtemp = -11999.0;
	*svolt = (int32_t)(vtemp);
	}
