/*
 * UserConfig.h
 *
 *  Created on: Aug 19, 2016
 *      Author: yanfen.fang
 */

#ifndef USERCONFIG_H_
#define USERCONFIG_H_

//* User need to configure the UserConfigFlag

#include <HILINK_DRIVE/HiLink_Common_Types.h>


/*******************************************************************************************************/
/**********************     User's customization for a new project begin     ***************************/
/*******************************************************************************************************/
const bool		GLOBAL_CSR_SYNC_FLAG = 0;
const STRING	DynamicDC_TX = "pHilink16_TX";
const STRING	DynamicDC_TX_d2s_wait_template = "d2s_Hilink16_TX_wait_template";
const STRING	RxRortName = "pHilink16_RX";
const INT 		FOCUS_SITE_NUMBER = 1;

const INT  FOCUS_SITE_NUM = 1;

const uint HILINK_SITE_NUMBER=1;
const uint HILINK_MACRO_NUM=2;
const uint HILINK_LANE_NUM=2;


const uint JTAG_PORT_COUNT = 1;
const uint DEFAULT_JTAG_PORT = 0;

#undef AHB_MODE
#undef AUTO_HWPRBS

const T_JTAG_DEFINITION JTAG_PORT_CONFIG[JTAG_PORT_COUNT]={
		{"pJTAG","JTAG_TDI","JTAG_TDO","JTAG_TMS","JTAG_TCK","JTAG_TRSTN",
				{"WTB x1_pJTAG_STD", "WTB x1_pJTAG_FASTDIFF"},
				16,20,16,
				{
				"d2s_JTAG_writeDR2_template"
				,"d2s_JTAG_writeDR1_template"
				,"d2s_JTAG_writeDR0_template"
				,"d2s_JTAG_writeIR2_template"
				,"d2s_JTAG_writeIR1_template"
				,"d2s_JTAG_writeIR0_template"
				,"d2s_JTAG_read_template"
				,"d2s_JTAG_wait_template"
				,"d2s_JTAG_writeDR_template"
				,"d2s_JTAG_writeIR_template"
				}
		}
};
//* HILINK_INFO[] access Macro Info
//* LANE_INFO[MacroID][] access Lane Info
HILINK_INFO_BEGIN();
		//redefine your IP type
		const static sT_HILINK_INFO _HILINK_INFO[] = {
		/*Macro10*/	{10, {CSL, CSL, 1, HiLink16LRTV100, 0xA1, 0x000001, 0x9D, 0x0000, 0xA0},
						{
				/*Lane0*/	{LANE_BOTH,"PIE_TX_P0", "PIE_TX_N0", "", "PIE_RX_P0", "PIE_RX_N0", ""}
						}
					},
		/*Macro11*/	{11, {CSL, CSL, 2, HiLink16LRTV100, 0xA1, 0x000002, 0x9D, 0x0001, 0xA0},
						{
				/*Lane0*/	{LANE_BOTH,"PCIE_TX_P0", "PCIE_TX_N0", "", "PCIE_RX_P0", "PCIE_RX_N0", ""},
				/*Lane1*/	{LANE_BOTH,"PCIE_TX_P1", "PCIE_TX_N1", "", "PCIE_RX_P1", "PCIE_RX_N1", ""}
						}
					}
		};
HILINK_INFO_END();

/********************************* Device version Info **************************************************/
const DOUBLE	Ip_Drop_Version = 4.5;
/*************************************** CP/FT Program **************************************************/
const STRING	CP_FT_Program = "FT";
/*************************************** Tx relay control() *********************************************/
const STRING 	TXUTI = "K1,K4,K6,K39";
/*************************************** DEFAULT INIT VECTOR ********************************************/
const STRING 	HILINK_FIRMWARE_LABEL = "HiLink_Ctle_Dfe_EyeMetric_3.0.0_0106_1519.hex.bin_WRITE";
const LONG 	 	HILINK_FIRMWARE_CYCLE = 753664;

#define _PUG2p4_

const STRING 	DEFAULT_HILINK_POWERUPCTRL_VECTOR = "";
/*************************************** DEFAULT INIT VECTOR ********************************************/
const STRING 	DEFAULT_HILINK_INIT_VECTOR = "";

/*************************************** HSI Prbs Pattern LENGTH ****************************************/
const STRING 	ATE_MODE_RX_FASTDIFF_PATTERN_LABEL = "PRBS15_x16_pHilink15_RX_RPT_FASTDIFF";
const LONG 	 	ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE = 32767 * 60;


const RxCTLE_SETTING RxCTLE_DEFAULT = {
//				{10,10,10},/*CTLE GAIN*/
				{12,12,12},/*CTLE GAIN*/
				{0,0,0},/*CTLE BOOST*/
				{0,0,0},/*CTLE CMBand*/
				{0,0,0},/*CTLE RMBand*/
				{0,0,0},/*CTLE ZA*/
				{0,0,0} /*CTLE SQH*/
};
const TxFIR_SETTING TxFIR_DEFAULT = {0, 0, 63, 0, 0};/*iTxPre2nd, iTxPre1st, iTxMain, iTxPost1st, iTxPost2nd*/


/****************************************Used for TTR****************************************************/
//const TTR_OPTIMIZE_CYCLE OPTIMIZE_CYCLE = {
//		4560,	/*****INT ALOS_OOB_ExpectValue;*****/
//		1344,	/*****INT ALOS_OOB_ReadPerLane;*****/
//};

/********************************************************************************************************/
/************************      User's customization for a new project end      **************************/
/********************************************************************************************************/


#endif /* USERCONFIG_H_ */
