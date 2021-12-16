/*
 * HiLinkPatternHelper.h
 *
 *  Created on: Nov 30, 2016
 *      Author: yanfen.fang
 */

#ifndef HILINKPATTERNHELPER_H_
#define HILINKPATTERNHELPER_H_

//#include "mapi.hpp"
#include <SRC_d2s/PatternCreate.h>

const uint JTAG_DR2_ADDR_LENGTH=17;
const uint JTAG_DR2_DATA_LENGTH=16;
const uint JTAG_DR2_ENTRY_DUMMY_CYCLE=3;
const uint JTAG_IRx_DR0_DR1_ENTRY_DUMMY_CYCLE=4;
const uint JTAG_CAPUTRE_SHIFT_CYCLE=4;
const uint JTAG_UPDATE_CYCLE=1;
const uint JTAG_EXIT_DUMMY_CYCLE=2;




const uint JTAG_READ_PATTERN_CYCLE=96;
const uint JTAG_READ_ADDR_LSB_CYCLE=24;
const uint JTAG_READ_ADDR_MSB_CYCLE=40;
const uint JTAG_READ_DATA_LSB_CYCLE=56;
const uint JTAG_READ_DATA_MSB_CYCLE=71;
const uint JTAG_READ_DATA_BITS=16;

const uint JTAG_EXPECT_PATTERN_CYCLE=96;
const uint JTAG_EXPECT_ADDR_LSB_CYCLE=24;
const uint JTAG_EXPECT_ADDR_MSB_CYCLE=40;
const uint JTAG_EXPECT_DATA_LSB_CYCLE=56;
const uint JTAG_EXPECT_DATA_MSB_CYCLE=71;
const uint JTAG_EXPECT_DATA_BITS=16;

////
//const uint JTAG_READ_PATTERN_CYCLE=112;
//const uint JTAG_READ_ADDR_LSB_CYCLE=24;
//const uint JTAG_READ_ADDR_MSB_CYCLE=40;
//const uint JTAG_READ_DATA_LSB_CYCLE=72;
//const uint JTAG_READ_DATA_MSB_CYCLE=87;
//const uint JTAG_READ_DATA_BITS=16;





const char JTAG_INPUT_LOW  = 0;
const char JTAG_INPUT_HIGH = 1;
const char JTAG_INPUT_CLK  = 1;

const char JTAG_OUTPUT_LOW  = 0;
const char JTAG_OUTPUT_HIGH = 1;
const char JTAG_OUTPUT_MASK  = 3;
const char JTAG_OUTPUT_CAPTURE  = 4;

const uint AHB_WRITE_PATTERN_CYCLE=48;
const uint AHB_WRITE_ADDR_LSB_CYCLE=19;
const uint AHB_WRITE_ADDR_MSB_CYCLE=35;
const uint AHB_WRITE_DATA_LSB_CYCLE=3;
const uint AHB_WRITE_DATA_MSB_CYCLE=18;

const uint AHB_WRITE_SHIFT_LOW_START0=0;
const uint AHB_WRITE_SHIFT_LOW_CYCLE0=3;

const uint AHB_WRITE_SHIFT_LOW_START1=37;
const uint AHB_WRITE_UPDATE=37;

const uint AHB_READ_PATTERN_CYCLE=96;
const uint AHB_READ_ADDR_LSB_CYCLE=19;
const uint AHB_READ_ADDR_MSB_CYCLE=35;
const uint AHB_READ_DUMMY_CYCLE=10;
const uint AHB_READ_DATA_LSB_CYCLE=41+AHB_READ_DUMMY_CYCLE;
const uint AHB_READ_DATA_MSB_CYCLE=56+AHB_READ_DUMMY_CYCLE;
const uint AHB_READ_DATA_BITS=16;

const uint AHB_READ_UPDATE0=37;
const uint AHB_READ_UPDATE1=75+AHB_READ_DUMMY_CYCLE;

const uint AHB_READ_SHIFT_LOW_START0=0;
const uint AHB_READ_SHIFT_LOW_CYCLE0=3;

const uint AHB_READ_SHIFT_LOW_START1=37;
const uint AHB_READ_SHIFT_LOW_CYCLE1=4+AHB_READ_DUMMY_CYCLE;

const uint AHB_READ_SHIFT_LOW_START2=75+AHB_READ_DUMMY_CYCLE;

const char AHB_INPUT_LOW  = 0;
const char AHB_INPUT_HIGH = 1;
const char AHB_INPUT_CLK  = 3;
const char AHB_INPUT_BYPASS  = 3;

const char AHB_OUTPUT_LOW  = 0;
const char AHB_OUTPUT_HIGH = 1;
const char AHB_OUTPUT_MASK  = 2;
const char AHB_OUTPUT_CAPTURE  = 4;

typedef struct{
	string& vec_tck;
	string& vec_tdi;
	string& vec_tdo;
	string& vec_tms;
	string& vec_trstn;
} T_JTAG_VEC_DATA;

typedef struct{
	string& vec_tdi;
	string& vec_tap_clk;
	string& vec_intercept_macro0;
	string& vec_intercept_macro1;
	string& vec_shift_dr;
	string& vec_tdo_macro0;
	string& vec_tdo_macro1;
	string& vec_update_dr;
} T_AHB_VEC_DATA;


uint getJtagPatternCycleByTDILength(uint len,int entery_cycle=JTAG_IRx_DR0_DR1_ENTRY_DUMMY_CYCLE);
int create_JTAG_WRITE_Pattern(bool is_JTAG_IR,int entery_cycle,T_JTAG_VEC_DATA& vec_data,int len,unsigned long long data_0,unsigned long long data_1=0);
void create_JTAG_DR2_READ_Pattern(uint addr,T_JTAG_VEC_DATA& vec_data,uint except_data=0,uint mask=0);

void create_AHB_WRITE_Pattern(uint addr,uint data,T_AHB_VEC_DATA& vec_data);
void create_AHB_READ_Pattern(uint addr,int macroid,T_AHB_VEC_DATA& vec_data,uint except_data=0,uint mask=0);

void create_JTAG_DR2_CAPTURE_Pattern(uint addr,T_JTAG_VEC_DATA& vec_data);
void create_AHB_CAPTURE_Pattern(uint addr,int macroid,T_AHB_VEC_DATA& vec_data);
#endif /* HILINKPATTERNHELPER_H_ */
