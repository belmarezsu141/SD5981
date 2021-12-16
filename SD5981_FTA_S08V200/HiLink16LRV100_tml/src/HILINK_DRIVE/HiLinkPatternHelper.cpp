/*
 * HiLinkPatternHelper.cpp
 *
 *  Created on: Nov 30, 2016
 *      Author: yanfen.fang
 */

#include <HILINK_DRIVE/HiLinkPatternHelper.h>

#include <assert.h>
uint getJtagPatternCycleByTDILength(uint len,int entery_cycle){
	len=entery_cycle+JTAG_CAPUTRE_SHIFT_CYCLE+len+JTAG_UPDATE_CYCLE+JTAG_EXIT_DUMMY_CYCLE;
	if(len % 8){
		len = len + 8 - (len %8);
	}
	return len;
}

int create_JTAG_WRITE_Pattern(bool is_JTAG_IR,int entery_cycle,T_JTAG_VEC_DATA& vec_data,int len,unsigned long long data_0,unsigned long long data_1){
	assert(len<=128);

	vec_data.vec_tdi.clear();
	vec_data.vec_tms.clear();

	vec_data.vec_tdi.append(entery_cycle,JTAG_INPUT_LOW);
	vec_data.vec_tms.append(entery_cycle,JTAG_INPUT_LOW);

	vec_data.vec_tdi.append(JTAG_CAPUTRE_SHIFT_CYCLE,JTAG_INPUT_LOW);
	if(is_JTAG_IR){
		vec_data.vec_tms.append(1,JTAG_INPUT_HIGH);
		vec_data.vec_tms.append(1,JTAG_INPUT_HIGH);
		vec_data.vec_tms.append(1,JTAG_INPUT_LOW);
		vec_data.vec_tms.append(1,JTAG_INPUT_LOW);
	}
	else{
		vec_data.vec_tms.append(1,JTAG_INPUT_LOW);
		vec_data.vec_tms.append(1,JTAG_INPUT_HIGH);
		vec_data.vec_tms.append(1,JTAG_INPUT_LOW);
		vec_data.vec_tms.append(1,JTAG_INPUT_LOW);
	}

	for(int i=0;i<64 && i<len;i++){
		if(data_0 & 0x1){
			vec_data.vec_tdi.append(1,JTAG_INPUT_HIGH);
		}
		else{
			vec_data.vec_tdi.append(1,JTAG_INPUT_LOW);
		}
		data_0>>=1;
	}

	for(int i=0;i<64 && i<len-64;i++){
		if(data_1 & 0x1){
			vec_data.vec_tdi.append(1,JTAG_INPUT_HIGH);
		}
		else{
			vec_data.vec_tdi.append(1,JTAG_INPUT_LOW);
		}
		data_1>>=1;
	}

	vec_data.vec_tms.append(len-1,JTAG_INPUT_LOW);

	vec_data.vec_tdi.append(JTAG_UPDATE_CYCLE,JTAG_INPUT_LOW);
	vec_data.vec_tms.append(JTAG_UPDATE_CYCLE+1,JTAG_INPUT_HIGH);

	vec_data.vec_tdi.append(JTAG_EXIT_DUMMY_CYCLE,JTAG_INPUT_LOW);
	vec_data.vec_tms.append(JTAG_EXIT_DUMMY_CYCLE,JTAG_INPUT_LOW);

	len=vec_data.vec_tdi.length();

	int fit=(len % 8)?(8-(len%8)):0;

	if(fit){
		vec_data.vec_tdi.append(fit,JTAG_INPUT_LOW);
		vec_data.vec_tms.append(fit,JTAG_INPUT_LOW);
	}

	len=vec_data.vec_tdi.length();
	vec_data.vec_tck.clear();
	vec_data.vec_tck.append(len,JTAG_INPUT_CLK);
	vec_data.vec_trstn.clear();
	vec_data.vec_trstn.append(len,JTAG_INPUT_HIGH);
	vec_data.vec_tdo.clear();
	vec_data.vec_tdo.append(len,JTAG_OUTPUT_MASK);

	return len;

}

void create_JTAG_DR2_READ_Pattern(uint addr,T_JTAG_VEC_DATA& vec_data,uint except_data,uint mask){

	vec_data.vec_tck.clear();
	vec_data.vec_tdi.clear();
	vec_data.vec_tdo.clear();
	vec_data.vec_tms.clear();
	vec_data.vec_trstn.clear();

	vec_data.vec_tck.append(JTAG_READ_PATTERN_CYCLE,JTAG_INPUT_CLK);
	vec_data.vec_tdi.append(JTAG_READ_PATTERN_CYCLE,JTAG_INPUT_LOW);
	vec_data.vec_tdo.append(JTAG_READ_PATTERN_CYCLE,JTAG_OUTPUT_MASK);
	vec_data.vec_tms.append(JTAG_READ_PATTERN_CYCLE,JTAG_INPUT_LOW);
	vec_data.vec_trstn.append(JTAG_READ_PATTERN_CYCLE,JTAG_INPUT_HIGH);

	uint select_dr_cycle=JTAG_DR2_ENTRY_DUMMY_CYCLE+1;
	vec_data.vec_tms[select_dr_cycle]=JTAG_INPUT_HIGH;
	uint exit_dr_cycle=JTAG_DR2_ENTRY_DUMMY_CYCLE+JTAG_CAPUTRE_SHIFT_CYCLE+1+JTAG_DR2_DATA_LENGTH+JTAG_DR2_ADDR_LENGTH;
	vec_data.vec_tms[exit_dr_cycle]=JTAG_INPUT_HIGH;
	uint update_dr_cycle=exit_dr_cycle+1;
	vec_data.vec_tms[update_dr_cycle]=JTAG_INPUT_HIGH;

	//JTAG_READ_DATA_LSB_CYCLE-->dummy 1bit-->shift dr-->capture dr-->select dr;
	uint select_read_dr_cycle=JTAG_READ_DATA_LSB_CYCLE-1-1-1-1;
	vec_data.vec_tms[select_read_dr_cycle]=JTAG_INPUT_HIGH;
	uint exit_read_dr_cycle=JTAG_READ_DATA_LSB_CYCLE+JTAG_DR2_DATA_LENGTH+JTAG_DR2_ADDR_LENGTH;
	vec_data.vec_tms[exit_read_dr_cycle]=JTAG_INPUT_HIGH;
	uint update_read_dr_cycle=exit_read_dr_cycle+1;
	vec_data.vec_tms[update_read_dr_cycle]=JTAG_INPUT_HIGH;

	for(uint i=0;i<17;i++){
		vec_data.vec_tdi[i+JTAG_READ_ADDR_LSB_CYCLE]=(addr&0x01)?JTAG_INPUT_HIGH:JTAG_INPUT_LOW;
		addr>>=1;
	}

	for(uint i=0;i<16;i++){
		vec_data.vec_tdo[i+JTAG_READ_DATA_LSB_CYCLE]	=	(mask&0x01)?JTAG_OUTPUT_MASK:
															(except_data&0x01)?JTAG_OUTPUT_HIGH:JTAG_OUTPUT_LOW;
		except_data>>=1;
		mask>>=1;
	}
}

void create_JTAG_DR2_CAPTURE_Pattern(uint addr,T_JTAG_VEC_DATA& vec_data){

	vec_data.vec_tck.clear();
	vec_data.vec_tdi.clear();
	vec_data.vec_tdo.clear();
	vec_data.vec_tms.clear();
	vec_data.vec_trstn.clear();

	vec_data.vec_tck.append(JTAG_READ_PATTERN_CYCLE,JTAG_INPUT_CLK);
	vec_data.vec_tdi.append(JTAG_READ_PATTERN_CYCLE,JTAG_INPUT_LOW);
	vec_data.vec_tdo.append(JTAG_READ_PATTERN_CYCLE,JTAG_OUTPUT_MASK);
	vec_data.vec_tms.append(JTAG_READ_PATTERN_CYCLE,JTAG_INPUT_LOW);
	vec_data.vec_trstn.append(JTAG_READ_PATTERN_CYCLE,JTAG_INPUT_HIGH);

	uint select_dr_cycle=JTAG_DR2_ENTRY_DUMMY_CYCLE+1;
	vec_data.vec_tms[select_dr_cycle]=JTAG_INPUT_HIGH;
	uint exit_dr_cycle=JTAG_DR2_ENTRY_DUMMY_CYCLE+JTAG_CAPUTRE_SHIFT_CYCLE+1+JTAG_DR2_DATA_LENGTH+JTAG_DR2_ADDR_LENGTH;
	vec_data.vec_tms[exit_dr_cycle]=JTAG_INPUT_HIGH;
	uint update_dr_cycle=exit_dr_cycle+1;
	vec_data.vec_tms[update_dr_cycle]=JTAG_INPUT_HIGH;

	//JTAG_READ_DATA_LSB_CYCLE-->dummy 1bit-->shift dr-->capture dr-->select dr;
	uint select_read_dr_cycle=JTAG_READ_DATA_LSB_CYCLE-1-1-1-1;
	vec_data.vec_tms[select_read_dr_cycle]=JTAG_INPUT_HIGH;
	uint exit_read_dr_cycle=JTAG_READ_DATA_LSB_CYCLE+JTAG_DR2_DATA_LENGTH+JTAG_DR2_ADDR_LENGTH;
	vec_data.vec_tms[exit_read_dr_cycle]=JTAG_INPUT_HIGH;
	uint update_read_dr_cycle=exit_read_dr_cycle+1;
	vec_data.vec_tms[update_read_dr_cycle]=JTAG_INPUT_HIGH;

	for(uint i=0;i<17;i++){
		vec_data.vec_tdi[i+JTAG_READ_ADDR_LSB_CYCLE]=(addr&0x01)?JTAG_INPUT_HIGH:JTAG_INPUT_LOW;
		addr>>=1;
	}

	for(uint i=0;i<16;i++){
		vec_data.vec_tdo[i+JTAG_READ_DATA_LSB_CYCLE]	=	JTAG_OUTPUT_CAPTURE;
	}
}

void create_AHB_WRITE_Pattern(uint addr,uint data,T_AHB_VEC_DATA& vec_data){
	vec_data.vec_tdi.clear();
	vec_data.vec_tap_clk.clear();
	vec_data.vec_intercept_macro0.clear();
	vec_data.vec_intercept_macro1.clear();
	vec_data.vec_shift_dr.clear();
	vec_data.vec_tdo_macro0.clear();
	vec_data.vec_tdo_macro1.clear();
	vec_data.vec_update_dr.clear();

	vec_data.vec_tdi.append(AHB_WRITE_PATTERN_CYCLE,AHB_INPUT_LOW);
	vec_data.vec_tap_clk.append(AHB_WRITE_PATTERN_CYCLE,AHB_INPUT_CLK);
	vec_data.vec_intercept_macro0.append(AHB_WRITE_PATTERN_CYCLE,AHB_INPUT_BYPASS);
	vec_data.vec_intercept_macro1.append(AHB_WRITE_PATTERN_CYCLE,AHB_INPUT_BYPASS);
	vec_data.vec_shift_dr.append(AHB_WRITE_PATTERN_CYCLE,AHB_INPUT_HIGH);
	vec_data.vec_tdo_macro0.append(AHB_WRITE_PATTERN_CYCLE,AHB_OUTPUT_MASK);
	vec_data.vec_tdo_macro1.append(AHB_WRITE_PATTERN_CYCLE,AHB_OUTPUT_MASK);
	vec_data.vec_update_dr.append(AHB_WRITE_PATTERN_CYCLE,AHB_INPUT_LOW);

	for(uint i=0;i<AHB_WRITE_SHIFT_LOW_CYCLE0;i++){
		vec_data.vec_shift_dr[i+AHB_WRITE_SHIFT_LOW_START0]=AHB_INPUT_LOW;
	}

	for(uint i=AHB_WRITE_SHIFT_LOW_START1;i<AHB_WRITE_PATTERN_CYCLE;i++){
		vec_data.vec_shift_dr[i]=AHB_INPUT_LOW;
	}

	vec_data.vec_update_dr[AHB_WRITE_UPDATE]=AHB_INPUT_HIGH;

	for(uint i=0;i<17;i++){
		vec_data.vec_tdi[i+AHB_WRITE_ADDR_LSB_CYCLE]=(addr&0x01)?AHB_INPUT_HIGH:AHB_INPUT_LOW;
		addr>>=1;
	}

	for(uint i=0;i<16;i++){
		vec_data.vec_tdi[i+AHB_WRITE_DATA_LSB_CYCLE]=(data&0x01)?AHB_INPUT_HIGH:AHB_INPUT_LOW;
		data>>=1;
	}
	vec_data.vec_tdi[36]=AHB_INPUT_HIGH;

}

void create_AHB_READ_Pattern(uint addr,int macroid,T_AHB_VEC_DATA& vec_data,uint except_data,uint mask){
	vec_data.vec_tdi.clear();
	vec_data.vec_tap_clk.clear();
	vec_data.vec_intercept_macro0.clear();
	vec_data.vec_intercept_macro1.clear();
	vec_data.vec_shift_dr.clear();
	vec_data.vec_tdo_macro0.clear();
	vec_data.vec_tdo_macro1.clear();
	vec_data.vec_update_dr.clear();

	vec_data.vec_tdi.append(AHB_READ_PATTERN_CYCLE,AHB_INPUT_LOW);
	vec_data.vec_tap_clk.append(AHB_READ_PATTERN_CYCLE,AHB_INPUT_CLK);
	vec_data.vec_intercept_macro0.append(AHB_READ_PATTERN_CYCLE,AHB_INPUT_BYPASS);
	vec_data.vec_intercept_macro1.append(AHB_READ_PATTERN_CYCLE,AHB_INPUT_BYPASS);
	vec_data.vec_shift_dr.append(AHB_READ_PATTERN_CYCLE,AHB_INPUT_HIGH);
	vec_data.vec_tdo_macro0.append(AHB_READ_PATTERN_CYCLE,AHB_OUTPUT_MASK);
	vec_data.vec_tdo_macro1.append(AHB_READ_PATTERN_CYCLE,AHB_OUTPUT_MASK);
	vec_data.vec_update_dr.append(AHB_READ_PATTERN_CYCLE,AHB_INPUT_LOW);

	for(uint i=0;i<AHB_READ_SHIFT_LOW_CYCLE0;i++){
		vec_data.vec_shift_dr[i+AHB_READ_SHIFT_LOW_START0]=AHB_INPUT_LOW;
	}

	for(uint i=0;i<AHB_READ_SHIFT_LOW_CYCLE1;i++){
		vec_data.vec_shift_dr[i+AHB_READ_SHIFT_LOW_START1]=AHB_INPUT_LOW;
	}

	for(uint i=AHB_READ_SHIFT_LOW_START2;i<AHB_READ_PATTERN_CYCLE;i++){
		vec_data.vec_shift_dr[i]=AHB_INPUT_LOW;
	}
	vec_data.vec_update_dr[AHB_READ_UPDATE0]=AHB_INPUT_HIGH;
	vec_data.vec_update_dr[AHB_READ_UPDATE1]=AHB_INPUT_HIGH;

	for(uint i=0;i<17;i++){
		vec_data.vec_tdi[i+AHB_READ_ADDR_LSB_CYCLE]=(addr&0x01)?AHB_INPUT_HIGH:AHB_INPUT_LOW;
		addr>>=1;
	}

	string tdo;
	tdo.clear();
	tdo.append(AHB_READ_PATTERN_CYCLE,AHB_OUTPUT_MASK);
	for(uint i=0;i<16;i++){
		tdo[i+AHB_READ_DATA_LSB_CYCLE]	=	(mask&0x01)?AHB_OUTPUT_MASK:
											(except_data&0x01)?AHB_OUTPUT_HIGH:AHB_OUTPUT_LOW;
		except_data>>=1;
		mask>>=1;
	}

	if(macroid==0){
		vec_data.vec_tdo_macro0=tdo;
	}
	else{
		vec_data.vec_tdo_macro1=tdo;
	}

}

void create_AHB_CAPTURE_Pattern(uint addr,int macroid,T_AHB_VEC_DATA& vec_data){
	vec_data.vec_tdi.clear();
	vec_data.vec_tap_clk.clear();
	vec_data.vec_intercept_macro0.clear();
	vec_data.vec_intercept_macro1.clear();
	vec_data.vec_shift_dr.clear();
	vec_data.vec_tdo_macro0.clear();
	vec_data.vec_tdo_macro1.clear();
	vec_data.vec_update_dr.clear();

	vec_data.vec_tdi.append(AHB_READ_PATTERN_CYCLE,AHB_INPUT_LOW);
	vec_data.vec_tap_clk.append(AHB_READ_PATTERN_CYCLE,AHB_INPUT_CLK);
	vec_data.vec_intercept_macro0.append(AHB_READ_PATTERN_CYCLE,AHB_INPUT_BYPASS);
	vec_data.vec_intercept_macro1.append(AHB_READ_PATTERN_CYCLE,AHB_INPUT_BYPASS);
	vec_data.vec_shift_dr.append(AHB_READ_PATTERN_CYCLE,AHB_INPUT_HIGH);
	vec_data.vec_tdo_macro0.append(AHB_READ_PATTERN_CYCLE,AHB_OUTPUT_MASK);
	vec_data.vec_tdo_macro1.append(AHB_READ_PATTERN_CYCLE,AHB_OUTPUT_MASK);
	vec_data.vec_update_dr.append(AHB_READ_PATTERN_CYCLE,AHB_INPUT_LOW);

	for(uint i=0;i<AHB_READ_SHIFT_LOW_CYCLE0;i++){
		vec_data.vec_shift_dr[i+AHB_READ_SHIFT_LOW_START0]=AHB_INPUT_LOW;
	}

	for(uint i=0;i<AHB_READ_SHIFT_LOW_CYCLE1;i++){
		vec_data.vec_shift_dr[i+AHB_READ_SHIFT_LOW_START1]=AHB_INPUT_LOW;
	}

	for(uint i=AHB_READ_SHIFT_LOW_START2;i<AHB_READ_PATTERN_CYCLE;i++){
		vec_data.vec_shift_dr[i]=AHB_INPUT_LOW;
	}
	vec_data.vec_update_dr[AHB_READ_UPDATE0]=AHB_INPUT_HIGH;
	vec_data.vec_update_dr[AHB_READ_UPDATE1]=AHB_INPUT_HIGH;

	for(uint i=0;i<17;i++){
		vec_data.vec_tdi[i+AHB_READ_ADDR_LSB_CYCLE]=(addr&0x01)?AHB_INPUT_HIGH:AHB_INPUT_LOW;
		addr>>=1;
	}

	string tdo;
	tdo.clear();
	tdo.append(AHB_READ_PATTERN_CYCLE,AHB_OUTPUT_MASK);
	for(uint i=0;i<16;i++){
		tdo[i+AHB_READ_DATA_LSB_CYCLE]	=	AHB_OUTPUT_CAPTURE;
	}

	if(macroid==0){
		vec_data.vec_tdo_macro0=tdo;
	}
	else{
		vec_data.vec_tdo_macro1=tdo;
	}

}

