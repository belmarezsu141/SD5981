/*
 * FWABIST_DFEIDAC.h
 *
 *  Created on: Apr 13, 2017
 *      Author: zhenghe
 */

#ifndef FWABIST_DFEIDAC_H_
#define FWABIST_DFEIDAC_H_


#include <HILINK_DRIVE/FWABIST_REGISTER_Base.h>


#define DFEIDAC_TABLE_COUNT 96
#define DFEIDAC_TABLE_Calculate_COUNT 36
class DFEIDAC_TABLE_DEFINE:public FWABIST_REGISTER_Base{
private:
	DFEIDAC_TABLE_DEFINE(){}
public:
	static DFEIDAC_TABLE_DEFINE& getInstance(){
		static DFEIDAC_TABLE_DEFINE inst;
		return inst;
	}

	uint map_DS_Addr(uint DS0_addr,uint LaneID){
		return DS0_addr+ 192*LaneID; //TODO: confirm address mapping of DS
	}

	uint get_FWABIST_TABLE_count(){return DFEIDAC_TABLE_COUNT;}
	uint get_FWABIST_Calculate_count(){return DFEIDAC_TABLE_Calculate_COUNT;}


	//Table 2-10
	const T_FWABIST_REG_INFO& get_FWABIST_TABLE_ITEM(uint idx){
		assert(idx<DFEIDAC_TABLE_COUNT);
		const static T_FWABIST_REG_INFO DFEIDAC_TABLE[]={

			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP2_n63", 0x1D5D8, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP2_n63", 0x1D5DA, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP2_n63", 0x1D5DC, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP2_n63", 0x1D5DE, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP2_n63", 0x1D5E0, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP2_n63", 0x1D5E2, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP2_n63", 0x1D5E4, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP2_n63", 0x1D5E6, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP2_0", 0x1D5E8, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP2_0", 0x1D5EA, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP2_0", 0x1D5EC, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP2_0", 0x1D5EE, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP2_0", 0x1D5F0, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP2_0", 0x1D5F2, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP2_0", 0x1D5F4, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP2_0", 0x1D5F6, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP2_63", 0x1D5F8, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP2_63", 0x1D5FA, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP2_63", 0x1D5FC, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP2_63", 0x1D5FE, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP2_63", 0x1D600, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP2_63", 0x1D602, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP2_63", 0x1D604, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP2_63", 0x1D606, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP3_n31", 0x1D608, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP3_n31", 0x1D60A, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP3_n31", 0x1D60C, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP3_n31", 0x1D60E, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP3_n31", 0x1D610, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP3_n31", 0x1D612, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP3_n31", 0x1D614, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP3_n31", 0x1D616, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP3_0", 0x1D618, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP3_0", 0x1D61A, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP3_0", 0x1D61C, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP3_0", 0x1D61E, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP3_0", 0x1D620, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP3_0", 0x1D622, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP3_0", 0x1D624, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP3_0", 0x1D626, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP3_31", 0x1D628, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP3_31", 0x1D62A, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP3_31", 0x1D62C, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP3_31", 0x1D62E, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP3_31", 0x1D630, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP3_31", 0x1D632, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP3_31", 0x1D634, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP3_31", 0x1D636, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP4_n31", 0x1D638, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP4_n31", 0x1D63A, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP4_n31", 0x1D63C, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP4_n31", 0x1D63E, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP4_n31", 0x1D640, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP4_n31", 0x1D642, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP4_n31", 0x1D644, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP4_n31", 0x1D646, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP4_0", 0x1D648, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP4_0", 0x1D64A, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP4_0", 0x1D64C, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP4_0", 0x1D64E, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP4_0", 0x1D650, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP4_0", 0x1D652, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP4_0", 0x1D654, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP4_0", 0x1D656, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP4_31", 0x1D658, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP4_31", 0x1D65A, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP4_31", 0x1D65C, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP4_31", 0x1D65E, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP4_31", 0x1D660, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP4_31", 0x1D662, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP4_31", 0x1D664, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP4_31", 0x1D666, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP5_n31", 0x1D668, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP5_n31", 0x1D66A, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP5_n31", 0x1D66C, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP5_n31", 0x1D66E, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP5_n31", 0x1D670, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP5_n31", 0x1D672, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP5_n31", 0x1D674, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP5_n31", 0x1D676, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP5_0", 0x1D678, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP5_0", 0x1D67A, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP5_0", 0x1D67C, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP5_0", 0x1D67E, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP5_0", 0x1D680, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP5_0", 0x1D682, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP5_0", 0x1D684, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP5_0", 0x1D686, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP5_31", 0x1D688, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP5_31", 0x1D68A, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP5_31", 0x1D68C, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP5_31", 0x1D68E, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP5_31", 0x1D690, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP5_31", 0x1D692, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP5_31", 0x1D694, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP5_31", 0x1D696, 0, 0, 0, 0, 0}

		};
		assert(sizeof(DFEIDAC_TABLE)/sizeof(T_FWABIST_REG_INFO)==DFEIDAC_TABLE_COUNT);
		return DFEIDAC_TABLE[idx];
	}

	//Table 2-11
	const T_FWABIST_CALCULATE_INFO& get_FWABIST_CALCULATE_ITEM(uint idx){
		assert(idx<DFEIDAC_TABLE_Calculate_COUNT);
		const static T_FWABIST_CALCULATE_INFO DFEIDAC_CALCULATOR_TABLE[]={

		{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUT_DFEFXTAP2_0", "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP2_0", "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP2_0", "", "","Sub",0x1D5CC, 150,0x1D5CE,-150, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUT_DFEFXTAP2_0", "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP2_0", "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP2_0", "", "","Sub",0x1D5CC, 150,0x1D5CE,-150, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUT_DFEFXTAP2_0", "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP2_0", "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP2_0", "", "","Sub",0x1D5CC, 150,0x1D5CE,-150, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUT_DFEFXTAP2_0", "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP2_0", "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP2_0", "", "","Sub",0x1D5CC, 150,0x1D5CE,-150, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUT_DFEFXTAP2_n63", "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP2_n63", "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP2_n63", "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP2_0", "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP2_0", "AbsDiff", 0x1D5D0, 9999,0x1d5d2, 40, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUT_DFEFXTAP2_n63", "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP2_n63", "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP2_n63", "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP2_0", "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP2_0", "AbsDiff", 0x1D5D0, 9999,0x1d5d2, 40, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUT_DFEFXTAP2_n63", "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP2_n63", "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP2_n63", "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP2_0", "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP2_0", "AbsDiff", 0x1D5D0, 9999,0x1d5d2, 40, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUT_DFEFXTAP2_n63", "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP2_n63", "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP2_n63", "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP2_0", "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP2_0", "AbsDiff", 0x1D5D0, 9999,0x1d5d2, 40, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUT_DFEFXTAP2_63", "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP2_63", "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP2_63", "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP2_0", "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP2_0", "AbsDiff", 0x1D5D0, 9999,0x1d5d2, 40, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUT_DFEFXTAP2_63", "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP2_63", "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP2_63", "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP2_0", "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP2_0", "AbsDiff", 0x1D5D0, 9999,0x1d5d2, 40, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUT_DFEFXTAP2_63", "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP2_63", "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP2_63", "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP2_0", "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP2_0", "AbsDiff", 0x1D5D0, 9999,0x1d5d2, 40, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUT_DFEFXTAP2_63", "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP2_63", "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP2_63", "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP2_0", "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP2_0", "AbsDiff", 0x1D5D0, 9999,0x1d5d2, 40, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUT_DFEFXTAP3_n31", "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP3_n31", "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP3_n31", "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP3_0", "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP3_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUT_DFEFXTAP3_n31", "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP3_n31", "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP3_n31", "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP3_0", "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP3_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUT_DFEFXTAP3_n31", "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP3_n31", "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP3_n31", "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP3_0", "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP3_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUT_DFEFXTAP3_n31", "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP3_n31", "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP3_n31", "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP3_0", "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP3_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUT_DFEFXTAP3_31", "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP3_31", "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP3_31", "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP3_0", "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP3_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUT_DFEFXTAP3_31", "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP3_31", "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP3_31", "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP3_0", "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP3_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUT_DFEFXTAP3_31", "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP3_31", "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP3_31", "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP3_0", "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP3_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUT_DFEFXTAP3_31", "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP3_31", "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP3_31", "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP3_0", "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP3_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUT_DFEFXTAP4_n31", "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP4_n31", "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP4_n31", "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP4_0", "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP4_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUT_DFEFXTAP4_n31", "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP4_n31", "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP4_n31", "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP4_0", "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP4_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUT_DFEFXTAP4_n31", "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP4_n31", "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP4_n31", "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP4_0", "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP4_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUT_DFEFXTAP4_n31", "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP4_n31", "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP4_n31", "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP4_0", "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP4_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUT_DFEFXTAP4_31", "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP4_31", "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP4_31", "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP4_0", "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP4_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUT_DFEFXTAP4_31", "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP4_31", "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP4_31", "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP4_0", "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP4_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUT_DFEFXTAP4_31", "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP4_31", "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP4_31", "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP4_0", "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP4_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUT_DFEFXTAP4_31", "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP4_31", "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP4_31", "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP4_0", "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP4_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUT_DFEFXTAP5_n31", "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP5_n31", "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP5_n31", "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP5_0", "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP5_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUT_DFEFXTAP5_n31", "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP5_n31", "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP5_n31", "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP5_0", "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP5_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUT_DFEFXTAP5_n31", "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP5_n31", "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP5_n31", "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP5_0", "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP5_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUT_DFEFXTAP5_n31", "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP5_n31", "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP5_n31", "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP5_0", "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP5_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_SUMMER_OUT_DFEFXTAP5_31", "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP5_31", "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP5_31", "DFE_I_EVEN_SUMMER_OUTP_DFEFXTAP5_0", "DFE_I_EVEN_SUMMER_OUTM_DFEFXTAP5_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_SUMMER_OUT_DFEFXTAP5_31", "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP5_31", "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP5_31", "DFE_Q_EVEN_SUMMER_OUTP_DFEFXTAP5_0", "DFE_Q_EVEN_SUMMER_OUTM_DFEFXTAP5_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_SUMMER_OUT_DFEFXTAP5_31", "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP5_31", "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP5_31", "DFE_I_ODD_SUMMER_OUTP_DFEFXTAP5_0", "DFE_I_ODD_SUMMER_OUTM_DFEFXTAP5_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},
		{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_SUMMER_OUT_DFEFXTAP5_31", "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP5_31", "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP5_31", "DFE_Q_ODD_SUMMER_OUTP_DFEFXTAP5_0", "DFE_Q_ODD_SUMMER_OUTM_DFEFXTAP5_0", "AbsDiff", 0x1D5D4, 9999,0x1d5d6, 20, 1},


		};
		assert(sizeof(DFEIDAC_CALCULATOR_TABLE)/sizeof(T_FWABIST_CALCULATE_INFO)==DFEIDAC_TABLE_Calculate_COUNT);
		return DFEIDAC_CALCULATOR_TABLE[idx];
	}



};



#endif /* FWABIST_DFEIDAC_H_ */
