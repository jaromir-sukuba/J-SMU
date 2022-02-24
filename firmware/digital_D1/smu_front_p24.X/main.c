#include <xc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hw.h"
#include "func.h"
#include "scpi/scpi.h"

//I'm not proud of this amount of global variables, also I'm not fan of useless interfaces for sake of interfacing
//it works for now, will be reworked once it gets too much
volatile uint16_t d_pixelmap[DISPLAY_LEN],d_blink_cnt,blink_mask,led_state_int;
volatile uint8_t d_blink,d_blink_mask_cnt,d_blink_mask_cnt2,display_compliance;
volatile uint8_t keymap[3],rx1_rcvd_ptr,rx1_rcvd_flag,rx2_rcvd_ptr,rx2_rcvd_flag;
volatile char rx1_rcvd_str[UART_RX_BUF_LEN], rx2_rcvd_str[UART_RX_BUF_LEN],disp_msg[DISPLAY_LEN+12];
volatile int16_t enc_var;
extern const uint16_t ASCII[96];
extern const char cal_val_desc[CAL_CONST_NUM][30];

uint8_t out_state=0,out_update=0,out_mode=0,range_curr=0,range_volt=1,edit_ptr=5,sup_force=0,sup_meas=1,sense_remote=0;
uint8_t disp_state,menu_ptr,avg_enabled,sup_enabled,sup_sample_now,rb_adc_arr_len=1,remote_mode=0,cal_locked=1;
uint8_t rmt_out_mode,rmt_src_volt_autorange,rmt_src_curr_autorange;
int16_t temper_hs;
int32_t set_volt,set_curr,clamp_volt,clamp_curr,meas_volt, meas_cur,rb_adc_val_1, rb_adc_val_2;
cal_type cal_const;
key_var keys,keys_new,keys_old;
led_var led_state;
float rmt_set_volt,rmt_set_curr,rmt_set_cvolt,rmt_set_ccurr,rmt_range_volt,rmt_range_curr,rmt_range_cvolt,rmt_range_ccurr;

int16_t menu_items_val[MENU_ITEMS] = {0,0,0,0};
const char menu_items_text[MENU_ITEMS][DISPLAY_LEN] = {"AVERAGE COUNT  ","SENSE REMOTE   ","NULL FORCE     ","NULL MEASURE   "};
const int16_t menu_items_limit_max[MENU_ITEMS] = {16,1,1,1};
const int16_t menu_items_limit_min[MENU_ITEMS] = {1,0,0,0};

scpi_t scpi_context;
static char scpi_input_buffer[SCPI_INPUT_BUFFER_LENGTH];
char smbuffer[SMALL_BUFFER_LEN];
scpi_error_t scpi_error_queue_data[SCPI_ERROR_QUEUE_SIZE];

/*******************************************************************************************************************************/
// SCPI callbacks
// thouse would feel home in separate .c file, but since many of the variables are
// in the large global section, here you go. There is path in exposing the desired variables
// into another file via extern (ouch) or properly via appropriate functions, but for sake
// of simplicity I kept it this way.
static scpi_result_t EXT_QCalList(scpi_t * context)
	{
	char out_str[50];
	uint8_t i;
	int32_t cal_val;
	for (i=0;i<CAL_CONST_NUM;i++)
		{
		cal_val = get_cal_const_num(i,&cal_const);
		sprintf(out_str," %d %ld    %s\n",i,cal_val,cal_val_desc[i]);
		uart1_txs(out_str);
		}
	return SCPI_RES_OK;
	}

static scpi_result_t EXT_QCalDump(scpi_t * context)
	{
	uint8_t i;
	int32_t cal_val;
	for (i=0;i<CAL_CONST_NUM;i++)
		{
		cal_val = get_cal_const_num(i,&cal_const);
		SCPI_ResultInt32(context,cal_val);
		}
	
	return SCPI_RES_OK;
	}

static scpi_result_t SCPI_QRepsGreet (scpi_t * context)
	{
	SCPI_ResultMnemonic(context, "MOIN\n");
	return SCPI_RES_OK;
	}

static scpi_result_t EXT_QSensVoltProt(scpi_t * context)
	{
	SCPI_ResultDouble(context, rmt_set_cvolt);	
	return SCPI_RES_OK;
	}

static scpi_result_t EXT_QSensCurrProt(scpi_t * context)
	{
	SCPI_ResultDouble(context, rmt_set_ccurr);	
	return SCPI_RES_OK;
	}

static scpi_result_t EXT_QSensVoltRange(scpi_t * context)
	{
	SCPI_ResultDouble(context, rmt_range_cvolt);	
	return SCPI_RES_OK;
	}

static scpi_result_t EXT_QSensCurrRange(scpi_t * context)
	{
	SCPI_ResultDouble(context, rmt_range_ccurr);	
	return SCPI_RES_OK;
	}

static scpi_result_t EXT_QSourceVoltLevel(scpi_t * context)
	{
	SCPI_ResultDouble(context, rmt_set_volt);	
	return SCPI_RES_OK;
	}

static scpi_result_t EXT_QSourceCurrLevel(scpi_t * context)
	{
	SCPI_ResultDouble(context, rmt_set_curr);	
	return SCPI_RES_OK;
	}

static scpi_result_t EXT_QSourceVoltRange(scpi_t * context)
	{
    SCPI_ResultDouble(context, range_volt);	
	return SCPI_RES_OK;
	}

static scpi_result_t EXT_QSourceCurrRange(scpi_t * context)
	{
    SCPI_ResultDouble(context, range_curr);	
	return SCPI_RES_OK;
	}

static scpi_result_t EXT_QSourceFunction(scpi_t * context)
	{
    SCPI_ResultDouble(context, out_mode);
	return SCPI_RES_OK;
	}

static scpi_result_t EXT_QMeasVolt(scpi_t * context)
	{
    SCPI_ResultFloat(context, conv_setvolt_fval(meas_volt,range_volt)/10.0);	
	return SCPI_RES_OK;
	}
static scpi_result_t EXT_QMeasCurr(scpi_t * context)
	{
    SCPI_ResultFloat(context, conv_setcurr_fval(meas_cur,range_curr)/10.0);	
	return SCPI_RES_OK;
	}
	
scpi_choice_def_t source_mode[] = {
	{"CURRent", 0},
    {"VOLT", 1},
    SCPI_CHOICE_LIST_END /* termination of option list */
};

static scpi_result_t EXT_SourceFunction(scpi_t * context) 
	{
    int32_t param;
    const char * name;
    if (!SCPI_ParamChoice(context, source_mode, &param, TRUE)) {
        return SCPI_RES_ERR;
    }
    SCPI_ChoiceToName(source_mode, param, &name);
	rmt_out_mode = param;
    return SCPI_RES_OK;
	}

static scpi_result_t EXT_SourceVoltRange(scpi_t * context)
	{
	scpi_number_t param1;
    if (!SCPI_ParamNumber(context, scpi_special_numbers_def, &param1, FALSE)) {
    }
	rmt_range_volt = param1.content.value;
//	conv_fval_setvolt(conv_setvolt_fval(set_volt,range_volt),param1.content.value,&set_volt,&range_volt,src_volt_autorange,0);
	return SCPI_RES_OK;
	}

static scpi_result_t EXT_SourceCurrRange(scpi_t * context)
	{
	scpi_number_t param1;
    if (!SCPI_ParamNumber(context, scpi_special_numbers_def, &param1, FALSE)) {
    }
	rmt_range_curr = param1.content.value;
	//conv_fval_setcurr(conv_setcurr_fval(set_curr,range_curr),param1.content.value,&set_curr,&range_curr,src_curr_autorange,0);
	return SCPI_RES_OK;
	}
static scpi_result_t EXT_SourceVoltLevel(scpi_t * context)
	{
	scpi_number_t param1;
    if (!SCPI_ParamNumber(context, scpi_special_numbers_def, &param1, FALSE)) {
    }
	//conv_fval_setvolt(param1.content.value,param1.content.value,&set_volt,&range_volt,src_volt_autorange,1);
	rmt_set_volt = param1.content.value;
	conv_fval_setvolt(rmt_set_volt,rmt_range_volt,&set_volt,&range_volt,rmt_src_volt_autorange);
	if (out_state==1) out_update=1;
	return SCPI_RES_OK;
	}

static scpi_result_t EXT_SourceCurrLevel(scpi_t * context)
	{
	scpi_number_t param1;
    if (!SCPI_ParamNumber(context, scpi_special_numbers_def, &param1, FALSE)) {
    }
	//conv_fval_setcurr(param1.content.value,param1.content.value,&set_curr,&range_curr,src_curr_autorange,1);
	rmt_set_curr = param1.content.value;
	conv_fval_setcurr(rmt_set_curr,rmt_range_curr,&set_curr,&range_curr,rmt_src_curr_autorange);
	if (out_state==1) out_update=1;
	return SCPI_RES_OK;
	}

static scpi_result_t EXT_SensVoltProt(scpi_t * context)
	{
	scpi_number_t param1;
    if (!SCPI_ParamNumber(context, scpi_special_numbers_def, &param1, FALSE)) {
    }
	rmt_set_cvolt = param1.content.value;
	conv_fval_setvolt(rmt_set_cvolt,rmt_range_cvolt,&clamp_volt,&range_volt,rmt_src_volt_autorange);
	if (out_state==1) out_update=1;
	return SCPI_RES_OK;
	}

static scpi_result_t EXT_SensCurrProt(scpi_t * context)
	{
	scpi_number_t param1;
    if (!SCPI_ParamNumber(context, scpi_special_numbers_def, &param1, FALSE)) {
    }
	rmt_set_ccurr = param1.content.value;
	conv_fval_setcurr(rmt_set_ccurr,rmt_range_ccurr,&clamp_curr,&range_curr,rmt_src_curr_autorange);
	if (out_state==1) out_update=1;
	return SCPI_RES_OK;
	}

static scpi_result_t EXT_SensVoltRange(scpi_t * context)
	{
	scpi_number_t param1;
    if (!SCPI_ParamNumber(context, scpi_special_numbers_def, &param1, FALSE)) {
    }
	rmt_range_cvolt = param1.content.value;
	return SCPI_RES_OK;
	}

static scpi_result_t EXT_SensCurrRange(scpi_t * context)
	{
	scpi_number_t param1;
    if (!SCPI_ParamNumber(context, scpi_special_numbers_def, &param1, FALSE)) {
    }
	rmt_range_ccurr = param1.content.value;
	return SCPI_RES_OK;
	}

scpi_choice_def_t ext_onoff_mode[] = {
    {"OFF", 0},
    {"ON", 1},
    SCPI_CHOICE_LIST_END /* termination of option list */
};

static scpi_result_t EXT_Outp(scpi_t * context)
	{
    int32_t param;
    const char * name;
    if (!SCPI_ParamChoice(context, ext_onoff_mode, &param, TRUE)) {
        return SCPI_RES_ERR;
    }
    SCPI_ChoiceToName(ext_onoff_mode, param, &name);
	if (param==1)
		{
		out_mode = rmt_out_mode;
		out_state=1;
		out_update=1;
		}
	if (param==0)
		{
		out_state=0;
		out_update=1;
		}
    return SCPI_RES_OK;
	}

static scpi_result_t EXT_SourceVoltRangeAuto(scpi_t * context)
	{
    int32_t param;
    const char * name;
    if (!SCPI_ParamChoice(context, ext_onoff_mode, &param, TRUE)) {
        return SCPI_RES_ERR;
    }
    SCPI_ChoiceToName(ext_onoff_mode, param, &name);
	rmt_src_volt_autorange = param;
    return SCPI_RES_OK;
	}

static scpi_result_t EXT_SourceCurrRangeAuto(scpi_t * context)
	{
    int32_t param;
    const char * name;
    if (!SCPI_ParamChoice(context, ext_onoff_mode, &param, TRUE)) {
        return SCPI_RES_ERR;
    }
    SCPI_ChoiceToName(ext_onoff_mode, param, &name);
	rmt_src_curr_autorange = param;
    return SCPI_RES_OK;
	}


static scpi_result_t EXT_CalCon(scpi_t * context)
	{
	int32_t param1, param2;

	if (!SCPI_ParamInt32(context, &param1, TRUE)) {
         return SCPI_RES_ERR;
     }
	if (!SCPI_ParamInt32(context, &param2, TRUE)) {
         return SCPI_RES_ERR;
     }
	set_cal_const_num(param1,&cal_const, param2);
    return SCPI_RES_OK;
	}

static scpi_result_t EXT_CalUnlock(scpi_t * context)
	{
    int32_t param;
    const char * name;
    if (!SCPI_ParamChoice(context, ext_onoff_mode, &param, TRUE)) {
        return SCPI_RES_ERR;
    }
    SCPI_ChoiceToName(ext_onoff_mode, param, &name);
	if (param==1) cal_locked = 0;
	else cal_locked = 1;
    return SCPI_RES_OK;
	}

static scpi_result_t EXT_CalSave(scpi_t * context)
	{
	int32_t param1;

	if (!SCPI_ParamInt32(context, &param1, TRUE)) {
         return SCPI_RES_ERR;
		}
	if (cal_locked==0) ee_write_cal_consts(((uint8_t)(param1)),&cal_const);
	return SCPI_RES_OK;
	}

static scpi_result_t EXT_CalLoad(scpi_t * context)
	{
	int32_t param1;
	if (!SCPI_ParamInt32(context, &param1, TRUE)) {
         return SCPI_RES_ERR;
		}
	ee_read_cal_consts(((uint8_t)(param1)),&cal_const);
	return SCPI_RES_OK;
	}

/*******************************************************************************************************************************/
//SPCI helper functions
size_t SCPIWrite(scpi_t * context, const char * data, size_t len) 
	{
	char out_str[UART_TX_BUF_LEN];
    (void) context;
	strncpy(out_str,data,len);
	out_str[len]=0;
	uart1_txs(out_str);		//this could be less specific
    return len;
	}

void serial_tasks (void)
	{
	if (rx1_rcvd_flag)
		{
		rx1_rcvd_flag = 0;
		if (SCPI_Input(&scpi_context, rx1_rcvd_str, strlen(rx1_rcvd_str))==TRUE)
			{
			if (remote_mode==0) remote_mode = 1;
			}
		}	
	}

/*******************************************************************************************************************************/
//first of three part [display - keys - other front panel] functions, making interface beteen user and machine in default mode
//that is mode default after power up, where you set and read out voltages/currents
//majority of this function operates directly above pixelmap - which is 1:1 bitmap of segments to be on/off
void display_main_values (void)
	{
	uint16_t i;
	if (out_mode==OUT_MODE_FVMI)
		{
		if (out_state==OUTPUT_OFF)
			{
			if (display_compliance==0)
				sprintf((char *)disp_msg,"%+5.5ld V  STBY  mA",set_volt);
			else
				sprintf((char *)disp_msg,"CPL CURR %+5.5ld mA",clamp_curr);
			}
		else
			sprintf((char *)disp_msg,"%+6.6ldV %+6.6ldmA",meas_volt,meas_cur);
		if (range_curr==0) disp_msg[16] = 'n';
		if ((range_curr==1)|(range_curr==2)|(range_curr==3)) disp_msg[16] = 'u';
		for (i=0;i<DISPLAY_LEN;i++) d_pixelmap[i] = segment_order(ASCII[disp_msg[i]-32]);
		if (display_compliance==0)
			{
			if ((range_curr==0)|(range_curr==3)) d_pixelmap[12] |= segment_order(ASCII['.'-32]);
			if ((range_curr==1)|(range_curr==4)) d_pixelmap[10] |= segment_order(ASCII['.'-32]);
			if ((range_curr==2)|(range_curr==5)) d_pixelmap[11] |= segment_order(ASCII['.'-32]);
			if (range_volt==0) d_pixelmap[1] |= segment_order(ASCII['.'-32]);
			if (range_volt==1) d_pixelmap[2] |= segment_order(ASCII['.'-32]);
			if (range_volt==2) d_pixelmap[3] |= segment_order(ASCII['.'-32]);
			}
		else
			{
			if ((range_curr==1)|(range_curr==4)) d_pixelmap[10] |= segment_order(ASCII['.'-32]);
			if ((range_curr==2)|(range_curr==5)) d_pixelmap[11] |= segment_order(ASCII['.'-32]);
			if ((range_curr==0)|(range_curr==3)) d_pixelmap[12] |= segment_order(ASCII['.'-32]);
			}
		}
	else
		{
		if (out_state==OUTPUT_OFF)
			{
			if (display_compliance==0)
				{
				sprintf((char *)disp_msg,"%+5.5ld mA STBY   V",set_curr);
				if (range_curr==0) disp_msg[7] = 'n';
				if ((range_curr==1)|(range_curr==2)|(range_curr==3)) disp_msg[7] = 'u';
				}
			else
				sprintf((char *)disp_msg,"CPL VOLT %+5.5ld V ",clamp_volt);
			}
		else
			{
			sprintf((char *)disp_msg,"%+6.6ldmA %+6.6ldV",meas_cur,meas_volt);
			if (range_curr==0) disp_msg[7] = 'n';
			if ((range_curr==1)|(range_curr==2)|(range_curr==3)) disp_msg[7] = 'u';
			}
		for (i=0;i<DISPLAY_LEN;i++) d_pixelmap[i] = segment_order(ASCII[disp_msg[i]-32]);
		if (display_compliance==0)
			{
			if ((range_curr==1)|(range_curr==4)) d_pixelmap[1] |= segment_order(ASCII['.'-32]);
			if ((range_curr==2)|(range_curr==5)) d_pixelmap[2] |= segment_order(ASCII['.'-32]);
			if ((range_curr==0)|(range_curr==3)) d_pixelmap[3] |= segment_order(ASCII['.'-32]);
			if (range_volt==0) d_pixelmap[11] |= segment_order(ASCII['.'-32]);
			if (range_volt==1) d_pixelmap[12] |= segment_order(ASCII['.'-32]);
			if (range_volt==2) d_pixelmap[13] |= segment_order(ASCII['.'-32]);
			}
		else
			{
			if (range_volt==0) d_pixelmap[10] |= segment_order(ASCII['.'-32]);
			if (range_volt==1) d_pixelmap[11] |= segment_order(ASCII['.'-32]);
			if (range_volt==2) d_pixelmap[12] |= segment_order(ASCII['.'-32]);
			}
		}	
	}

//checks for keys pressed by user and do appropriate actions
//mostly chasing key bits and small variables adjusting things here and there in the SMU
void key_handling_def (void)
	{
	if (remote_mode)
		{
		if (keys.k4)
			{		
			keys.k4 = 0;
			remote_mode = 0;
			keys.INT=0;
			}
		return;
		}
	if (keys.k1)
		{		
		keys.k1 = 0;
		out_update=1;
		if (out_state==0) out_state = 1;
		else out_state = 0;
		}
	if (keys.k2)
		{
		keys.k2 = 0;
		if (out_state==OUTPUT_OFF)
			{
			if (out_mode==OUT_MODE_FIMV) out_mode = OUT_MODE_FVMI;
			else out_mode = OUT_MODE_FIMV;
			}
		}
	if (keys.k3)
		{		
		keys.k3 = 0;
		if (display_compliance==0) display_compliance = 1;
		else display_compliance = 0;
		}
	if (keys.k5)
		{		
		keys.k5 = 0;
		if (sup_enabled == 0) 
			{
			sup_enabled = 1;
			sup_sample_now = 1;
			}
		else sup_enabled = 0;
		}
	if (keys.k6)
		{		
		keys.k6 = 0;
		if (avg_enabled == 0) avg_enabled = 1;
		else avg_enabled = 0;
		}

	if (keys.k7)
		{		
		keys.k7 = 0;
		disp_state=DISP_STATE_MENU;
		menu_ptr = 0;
		}
		
	if (keys.k10)
		{		//			mainboard_ri_enqueue(range_curr);
		keys.k10 = 0;
		if (out_mode==OUT_MODE_FIMV)
			{
			if (display_compliance==0)
				{
				if (range_curr>RANGE_CURR_MIN) range_curr--;
				}
			else
				{
				if (range_volt>RANGE_VOLT_MIN) range_volt--;
				}
			}
		else
			{
			if (display_compliance==1)
				{
				if (range_curr>RANGE_CURR_MIN) range_curr--;
				}
			else
				{
				if (range_volt>RANGE_VOLT_MIN) range_volt--;
				}
			}
		}
	if (keys.k9)
		{		
		keys.k9 = 0;
		if (out_mode==OUT_MODE_FIMV)
			{
			if (display_compliance==0)
				{
				if (range_curr<RANGE_CURR_MAX) range_curr++;
				}
			else
				{
				if (range_volt<RANGE_VOLT_MAX) range_volt++;
				}
			}
		else
			{
			if (display_compliance==1)
				{
				if (range_curr<RANGE_CURR_MAX) range_curr++;
				}
			else
				{
				if (range_volt<RANGE_VOLT_MAX) range_volt++;
				}
			}
		}
	if (keys.k12)
		{		
		keys.k12 = 0;
		if (edit_ptr>0) edit_ptr--;
		}
	if (keys.k14)
		{		
		keys.k14 = 0;
		if (edit_ptr<5) edit_ptr++;
		}	
	}

//turn LEDs on and off as needed, and take care of rotary encoder
//some magic numbers here, to be cleaned up
void front_panel_def (void)
	{
	if (out_state==OUTPUT_OFF)
		{
		if (display_compliance==1)  led_state.led4 = 1;	
		else led_state.led4 = 0;	
		}
	else 
		{
		if (get_compliance_pin_state()) led_state.led4 = 1;
		else led_state.led4 = 0;
		}
	led_state.led1 = out_state;
	led_state.led2 = out_mode;
	led_state.led3 = ~led_state.led2;
	led_state.led5 = ~remote_mode;
	led_state.led6 = sup_enabled;
	led_state.led7 = avg_enabled;
	led_state.led8 = 0;
	led_state.led9 = 0;
	if (remote_mode) return;
	if (enc_var!=0)
		{
		if (out_mode==OUT_MODE_FVMI)
			{
			if (display_compliance==0) enc_set_long(&set_volt,enc_var,edit_ptr,-11999,11999);
			else enc_set_long(&clamp_curr,enc_var,edit_ptr,-99999,99999);
			}
		else
			{
			if (display_compliance==0) enc_set_long(&set_curr,enc_var,edit_ptr,-99999,99999);
			else enc_set_long(&clamp_volt,enc_var,edit_ptr,-11999,11999);
			}			
		enc_var = 0;
		}
	if (out_state==OUTPUT_OFF)
		{
		if (display_compliance==0) d_blink = edit_ptr+0;
		else d_blink = edit_ptr+9;
		}
	else
		d_blink = 255;

	}

/*******************************************************************************************************************************/
//first of three part [display - keys - other front panel] functions, making interface beteen user and machine when displaying menu
//unlike default mode, where is a lot of deciding what do display and when, this one is fairly simple
void display_menu (void)
	{
	uint16_t i;
	sprintf((char *)disp_msg,"%s %d    ",menu_items_text[menu_ptr],menu_items_val[menu_ptr]);
	for (i=0;i<DISPLAY_LEN;i++) d_pixelmap[i] = segment_order(ASCII[disp_msg[i]-32]);
	}

//decide what to do with keys in menu mode
void key_handling_menu (void)
	{
	if (remote_mode)
		{
		if (keys.k4)
			{		
			keys.k4 = 0;
			remote_mode = 0;
			}
		return;
		}
	if (keys.k1)
		{		
		keys.k1 = 0;
		}
	if (keys.k7)
		{		
		keys.k7=0;
		disp_state=DISP_STATE_DEFAULT;
		keys.INT = 0;
		rb_adc_arr_len = menu_items_val[0];
		sup_force = menu_items_val[2];
		sup_meas = menu_items_val[3];
		}
	if (keys.k12)
		{		
		keys.k12 = 0;
		if (menu_ptr>0) menu_ptr--;
		}
	if (keys.k14)
		{		
		keys.k14 = 0;
		if (menu_ptr<(MENU_ITEMS-1)) menu_ptr++;
		}	
	}

//do things with LEDs and rotary encoder when displaying menu
void front_panel_menu (void)
	{
	led_state.INT = 0;
	led_state.led8 = 1;
	if (remote_mode) return;
	if (enc_var!=0)
		{
		enc_inc_int(&menu_items_val[menu_ptr],enc_var);
		enc_var = 0;
		}
	//jar zredukovat na handlovanie min man ako ma long, cdpc je d_blink = edit_ptr+0; a
	if (menu_items_val[menu_ptr]<menu_items_limit_min[menu_ptr]) menu_items_val[menu_ptr]=menu_items_limit_min[menu_ptr];
	if (menu_items_val[menu_ptr]>menu_items_limit_max[menu_ptr]) menu_items_val[menu_ptr]=menu_items_limit_max[menu_ptr];
	d_blink = edit_ptr+0;
	d_blink = 255;
	}

/*******************************************************************************************************************************/
/*******************************************************************************************************************************/
/*******************************************************************************************************************************/
//oh here we go, everyone's favorite topic - interrupts. too entangled with main menu to be separated out and too hardware-ish
//to let it in main.c I decided to go lazy and leave it in main.c
void __attribute__((interrupt, auto_psv)) _U1RXInterrupt(void)
	{
	volatile uint8_t temp;
	IFS0bits.U1RXIF=0;
	temp = U1RXREG;
	if (temp<0x20)
		{
		if (rx1_rcvd_ptr>0)
			{
			rx1_rcvd_str[rx1_rcvd_ptr] = '\n';
			rx1_rcvd_str[rx1_rcvd_ptr+1] = 0;
			rx1_rcvd_flag = 1;
			rx1_rcvd_ptr = 0;
			}
		}
	else rx1_rcvd_str[rx1_rcvd_ptr++] = temp;
	if (rx1_rcvd_ptr>=sizeof(rx1_rcvd_str)) rx1_rcvd_ptr--;
	}

void __attribute__((interrupt, auto_psv)) _U2RXInterrupt(void)
	{
	volatile uint8_t temp;
	IFS1bits.U2RXIF=0;
	temp = U2RXREG;
	if (temp<0x20)
		{
		if (rx2_rcvd_ptr>0)
			{
			rx2_rcvd_str[rx2_rcvd_ptr] = 0;
			rx2_rcvd_flag = 1;
			rx2_rcvd_ptr = 0;
			}
		}
	else rx2_rcvd_str[rx2_rcvd_ptr++] = temp;
	if (rx2_rcvd_ptr>=sizeof(rx2_rcvd_str)) rx2_rcvd_ptr--;
	}

//this timer, ticking eery milisecond, takes care of display multiplex refresh
//it's quite messy, because hardware was designed the simple way. It's cheaper
//to get verbose in software than in hardware
void __attribute__((interrupt, auto_psv)) _T1Interrupt (void)
	{
	static char anode,keyrow;
	_T1IF = 0;
	BS(SR_OE_P,SR_OE_B);
	if ((17-anode)==d_blink) sr_shiftout(blink_mask&d_pixelmap[17-anode]);
	else sr_shiftout(d_pixelmap[17-anode]);

	if ((11-anode)==d_blink) sr_shiftout(blink_mask&d_pixelmap[11-anode]);
	else sr_shiftout(d_pixelmap[11-anode]);

    if ((5-anode)==d_blink) sr_shiftout(blink_mask&d_pixelmap[5-anode]);
	else sr_shiftout(d_pixelmap[5-anode]);    

    BS(SR_LE_P,SR_LE_B);
    BC(SR_LE_P,SR_LE_B);
    BS(SR_LE_P,SR_LE_B);
    d_anode(anode);
    anode++;
	BC(SR_OE_P,SR_OE_B);
	//not sure how to rewrite this to be readable; without using ton of single-use defines; what isn't stategy for readibility in first place
	if ((anode&0x01)==0)
		{
		exp_write(0x14,(((led_state_int>>0)&0x1F))|0x40);	
		if (keyrow==0) exp_write(0x15,0xFE);
		if (keyrow==1) exp_write(0x15,0xFD);
		if (keyrow==2) exp_write(0x15,0xFB);
		}
	else
		{
		exp_write(0x14,(((led_state_int>>8)&0x1F))|0x20);	
		if (keyrow==0) keymap[0] = (~exp_read(0x13))&0x1F;
		if (keyrow==1) keymap[1] = (~exp_read(0x13))&0x1F;
		if (keyrow==2) keymap[2] = (~exp_read(0x13))&0x1F;
		keyrow++;
		if (keyrow>2) keyrow=0;
		} 
    if (anode>5) 
		{
		anode = 0;
		d_blink_mask_cnt++;
		d_blink_mask_cnt2++;
		if (d_blink_mask_cnt>2) d_blink_mask_cnt=0;			//oh, blinking handling
		if ((d_blink_mask_cnt!=0)&((d_blink_mask_cnt2&0x40)==0)) blink_mask = 0x0;
		else blink_mask = 0xFFFF;//it's very likely I understood this code last week
		}
	}

//every 500us, taking care of rotary encoder
void __attribute__((interrupt, auto_psv)) _T3Interrupt (void)
	{
	static volatile uint8_t enc_deb_a, enc_deb_b, enc_stat,enc_prev;
	_T3IF = 0;
	enc_deb_a = enc_deb_a << 1;					//debouncing queues
	enc_deb_b = enc_deb_b << 1;
	if (BV(ENC_A_P,ENC_A_B)==0) enc_deb_a|=1;
	if (BV(ENC_B_P,ENC_B_B)==0) enc_deb_b|=1;
	enc_prev = enc_stat;
	enc_stat=0;
	if (enc_deb_a&0x07) enc_stat|=0x01;			//if enough bits in queue is right, call it proper signal
	if (enc_deb_b&0x07) enc_stat|=0x02;
	if ((enc_stat==0x02)&(enc_prev==0)) enc_var++;
	if ((enc_stat==0x01)&(enc_prev==0)) enc_var--;
	}


/*******************************************************************************************************************************/
///SCPI command definitions
scpi_command_t scpi_commands[] = {
	{ .pattern = "*IDN?", .callback = SCPI_CoreIdnQ,},
	{ .pattern = "*RST", .callback = SCPI_CoreRst,},
	{ .pattern = "*CLS", .callback = SCPI_CoreCls,},
    { .pattern = "SYSTem:ERRor[:NEXT]?", .callback = SCPI_SystemErrorNextQ,},
    { .pattern = "SYSTem:ERRor:COUNt?", .callback = SCPI_SystemErrorCountQ,},
    { .pattern = "SYSTem:VERSion?", .callback = SCPI_SystemVersionQ,},
	{ .pattern = "REPS:GREET?", .callback = SCPI_QRepsGreet,},
	{ .pattern = "SOURce:FUNCtion", .callback = EXT_SourceFunction,},
	{ .pattern = "SOURce:FUNCtion?", .callback = EXT_QSourceFunction,},
	{ .pattern = "SOURce:VOLTage:RANGe", .callback = EXT_SourceVoltRange,},
	{ .pattern = "SOURce:VOLTage:RANGe:AUTO", .callback = EXT_SourceVoltRangeAuto,},
	{ .pattern = "SOURce:VOLTage:RANGe?", .callback = EXT_QSourceVoltRange,},
	{ .pattern = "SOURce:CURRent:RANGe", .callback = EXT_SourceCurrRange,},
	{ .pattern = "SOURce:CURRent:RANGe:AUTO", .callback = EXT_SourceCurrRangeAuto,},
	{ .pattern = "SOURce:CURRent:RANGe?", .callback = EXT_QSourceCurrRange,},
	{ .pattern = "SOURce:VOLTage:LEVel", .callback = EXT_SourceVoltLevel,},
	{ .pattern = "SOURce:VOLTage:LEVel?", .callback = EXT_QSourceVoltLevel,},
	{ .pattern = "SOURce:CURRent:LEVel", .callback = EXT_SourceCurrLevel,},
	{ .pattern = "SOURce:CURRent:LEVel?", .callback = EXT_QSourceCurrLevel,},
	{ .pattern = "SENSe:VOLTage:PROTection", .callback = EXT_SensVoltProt,},
	{ .pattern = "SENSe:VOLTage:PROTection?", .callback = EXT_QSensVoltProt,},
	{ .pattern = "SENSe:CURRent:PROTection", .callback = EXT_SensCurrProt,},
	{ .pattern = "SENSe:CURRent:PROTection?", .callback = EXT_QSensCurrProt,},
	{ .pattern = "SENSe:VOLTage:RANGe", .callback = EXT_SensVoltRange,},
	{ .pattern = "SENSe:VOLTage:RANGe?", .callback = EXT_QSensVoltRange,},
	{ .pattern = "SENSe:CURRent:RANGe", .callback = EXT_SensCurrRange,},
	{ .pattern = "SENSe:CURRent:RANGe?", .callback = EXT_QSensCurrRange,},
	{ .pattern = "MEASure:VOLTage?", .callback = EXT_QMeasVolt,},
	{ .pattern = "MEASure:CURRent?", .callback = EXT_QMeasCurr,},
	{ .pattern = "OUTPut", .callback = EXT_Outp,},	
	{ .pattern = "CALibration:CONstant", .callback = EXT_CalCon,},
	{ .pattern = "CALibration:UNLock", .callback = EXT_CalUnlock,},
	{ .pattern = "CALibration:DUMP?", .callback = EXT_QCalDump,},
	{ .pattern = "CALibration:LIST?", .callback = EXT_QCalList,},
	{ .pattern = "CALibration:SAVE", .callback = EXT_CalSave,},
	{ .pattern = "CALibration:LOAD", .callback = EXT_CalLoad,},
	SCPI_CMD_LIST_END
};

/*******************************************************************************************************************************/
//SCPI interface
int16_t SCPI_Error(scpi_t * context, int_fast16_t err) {
    (void) context;
	char errmsg[40];
    sprintf(errmsg, "**ERROR: %d, \"%s\"\r\n", (int16_t) err, SCPI_ErrorTranslate(err));
	uart1_txs(errmsg);
    return 0;
}

scpi_interface_t scpi_interface = {
	.write = SCPIWrite,
	.error = SCPI_Error,
	.reset = NULL,
//	.srq = NULL,
};

//set or update output as needed
void output_handling (void)
	{
	int32_t sv_temp;
	if (out_update!=0)
		{
		out_update=0;
		if (out_state==OUTPUT_ON)
			{
			display_compliance=0;
			mainboard_msg_enqueue("da32768");
			if (out_mode==OUT_MODE_FIMV) 
				{
				mainboard_msg_enqueue("mi");
				mainboard_rv_enqueue(range_volt);
				mainboard_ri_enqueue(range_curr);
				mainboard_msg_enqueue("ro1");
				sv_temp = adjust_long_offset_gain (cal_const.fimv.curr_set[range_curr].offset,cal_const.fimv.curr_set[range_curr].gain,set_curr);
				mainboard_dac_enqueue(0,get_dac_curr(sv_temp));
				mainboard_dac_enqueue(1,32768-get_dac_cvolt(clamp_volt));
				mainboard_dac_enqueue(2,32767+get_dac_cvolt(clamp_volt));
				}
			else 
				{
				mainboard_msg_enqueue("mv");
				mainboard_rv_enqueue(range_volt);
				mainboard_ri_enqueue(range_curr);
				mainboard_msg_enqueue("ro1");
				sv_temp = adjust_long_offset_gain (cal_const.fvmi.volt_set[range_volt].offset,cal_const.fvmi.volt_set[range_volt].gain,set_volt);
				mainboard_dac_enqueue(0,get_dac_volt(sv_temp));
				mainboard_dac_enqueue(1,32768-get_dac_ccurr(clamp_curr));
				mainboard_dac_enqueue(2,32767+get_dac_ccurr(clamp_curr));
				}
			}
		else
			{
			mainboard_msg_enqueue("ro0");
			mainboard_msg_enqueue("da32768");
			}
		}
	}

// obviously, the main loop
int main(void)
	{
	uint8_t mb_state=1,meas_cnt,fan_state=0;
	uint16_t i;
	int16_t adc_res=0,adc_res_old=0;
	int32_t sup_val_volt, sup_val_curr;
	SCPI_Init(&scpi_context,
		scpi_commands,
		&scpi_interface,
		scpi_units_def,
		SCPI_IDN1, SCPI_IDN2, SCPI_IDN3, SCPI_IDN4,
		scpi_input_buffer, SCPI_INPUT_BUFFER_LENGTH,
		scpi_error_queue_data, SCPI_ERROR_QUEUE_SIZE);
	hw_init();
	sprintf((char *)disp_msg,"   %s %s       ", SCPI_IDN2, SCPI_IDN4);
	for (i=0;i<DISPLAY_LEN;i++) d_pixelmap[i] = segment_order(ASCII[disp_msg[i]-32]);
	delay_ms(1000);
	d_blink = 255;
	out_state=OUTPUT_OFF;
	keys.INT = 0;
	keys_old.INT = 0;
	out_mode = OUT_MODE_FVMI;
	range_curr = RANGE_CURR_MIN+3;
	mainboard_msg_enqueue("ro0");		//put analog processor into known state
	mainboard_msg_enqueue("mv");
	mainboard_msg_enqueue("da32767");
	mainboard_msg_enqueue("db0");
	mainboard_msg_enqueue("dc65000");
	mainboard_msg_enqueue("sb0");
	mainboard_msg_enqueue("sa1");
	set_volt = 0;
	set_curr = 0;
	clamp_curr = 10000;
	clamp_volt = 1000;
	display_compliance = 0;
	rb_adc_arr_len = 1;
	temper_hs = conv_adc_temp(adc_res);
	disp_state = DISP_STATE_DEFAULT;
	ee_read_cal_consts(0,&cal_const);		//read calibration constants
	menu_items_val[0] = rb_adc_arr_len;		//populate menu items
	menu_items_val[1] = sense_remote;
	menu_items_val[2] = sup_force;
	menu_items_val[3] = sup_meas;
	while (1)
		{
		delay_ms(10);						//set rough tick of main loop, doesn't need to be very precise, everything precise is done in interrupts anyway
		meas_cnt++;
		if (meas_cnt>=20)
			{
			meas_cnt=0;	
			mainboard_msg_enqueue("a");		//roughly 5 times per second initiate measurement of voltage and current; the response is then processed 
											//in mainboard_comms function state machine and exports rb_adc_val_1 and rb_adc_val_2 (channel 1 and 2 measurement)
			adc_res = get_adc(ADC_CHNL_TEMPER);							//also, read the temperature
			adc_res_old = adc_res_old + ((adc_res - adc_res_old)/4);	//and run it via exponential filter to smooth out noise
			adc_res = adc_res_old;
			temper_hs = conv_adc_temp(adc_res_old);
			if (fan_state==FAN_STATE_OFF)								//take care of the fan accordingly to the temperature
				{														//run it either at full level, or lazy or none at all
				if (temper_hs>FAN_TEMP_LEVEL1) fan_state=FAN_STATE_MID;
				set_fan_speed(0);
				}
			if (fan_state==FAN_STATE_MID)
				{
				if (temper_hs<(FAN_TEMP_LEVEL1-FAN_TEMP_HYST)) fan_state=FAN_STATE_OFF;
				if (temper_hs>FAN_TEMP_LEVEL2) fan_state=FAN_STATE_FULL;
				set_fan_speed(1);
				}
			if (fan_state==FAN_STATE_FULL)
				{
				if (temper_hs<(FAN_TEMP_LEVEL2-FAN_TEMP_HYST)) fan_state=FAN_STATE_MID;
				set_fan_speed(2);
				}
			}

		mb_state = mainboard_comms(mb_state);							//here is where the communication with main analog board takes place
		meas_volt = get_volt_from_adc(rb_adc_val_1);				//roughly scale the ADC results into proper voltage and current readings
		meas_cur = get_curr_from_adc(rb_adc_val_2);
		if (out_mode==OUT_MODE_FVMI)									//and calibrate the readings with proper calibration constants 
			{
			meas_volt = adjust_long_offset_gain (cal_const.fvmi.volt_read[range_volt].offset,cal_const.fvmi.volt_read[range_volt].gain,meas_volt);
			meas_cur =  adjust_long_offset_gain (cal_const.fvmi.curr_read[range_curr].offset,cal_const.fvmi.curr_read[range_curr].gain,meas_cur);
			}
		else															//constants are not the same for FVMI and FIMV modes
			{
			meas_volt = adjust_long_offset_gain (cal_const.fimv.volt_read[range_volt].offset,cal_const.fimv.volt_read[range_volt].gain,meas_volt);
			meas_cur =  adjust_long_offset_gain (cal_const.fimv.curr_read[range_curr].offset,cal_const.fimv.curr_read[range_curr].gain,meas_cur);
			}

		if (sup_sample_now==1)											//if tasked to perform suppress function, take a sample first
			{
			sup_sample_now=0;
			sup_val_volt = meas_volt;
			sup_val_curr = meas_cur;
			}
		if (sup_enabled)												//and subsequently remove either current or voltage or both, depending on menu setting
			{
			if (out_mode==OUT_MODE_FVMI)
				{
				if (sup_force==1) meas_volt = meas_volt - sup_val_volt;
				if (sup_meas==1) meas_cur = meas_cur - sup_val_curr;
				}
			else
				{
				if (sup_meas==1) meas_volt = meas_volt - sup_val_volt;
				if (sup_force==1) meas_cur = meas_cur - sup_val_curr;
				}				
			}
		serial_tasks ();							//take care of serial port
		//handle keys; reading the serial expander connected to keys is done in interrupts, here we are just reading the results
		keys_new.INT = map_keys ((((uint16_t)(keymap[2]))<<10)|(((uint16_t)(keymap[1]))<<5)|(((uint16_t)(keymap[0]))<<0));
		keys.INT = keys.INT|((keys_new.INT^keys_old.INT)&keys_new.INT);	//set 1 when user pressed button; three logic functions in single line, I'm proud of this
		keys_old.INT = keys_new.INT;
		led_state_int = map_leds(led_state.INT);	//and setup interrupt variable to light LEDs on or off as needed
		output_handling();							//take care of setting the SMU output - on/off/update
		if (disp_state==DISP_STATE_MENU)			//decide if default set is needed to be displayed, with appropriate front panel handling functions
			{
			display_menu();
			key_handling_menu();
			front_panel_menu();
			}
		if (disp_state==DISP_STATE_DEFAULT)			//or menu is to be displayed, with appropriate support functions
			{
			front_panel_def();
			key_handling_def();
			display_main_values();
			}
		}
	}

