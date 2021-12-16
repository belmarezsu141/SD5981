#ifndef USERCONFIG_H_
#define USERCONFIG_H_

 #undef TestChip
//* User need to configure the UserConfigFlag
#define HIGGS_PRIVATE 0
#include <HILINK_DRIVE/HiLink_Common_Types.h>
//#include "JAM_Setup/JAM_Common_Types.h"
//#include "PCM_Setup/PCM_Common_Types.h"
using namespace std;

const string	MACRO_SS = "0";

const INT		FwTypeAdaptNoApi=2;
const INT		FwTypeCalNoApi=1;
const INT		FwTypeCalAll=0;

const INT		FOCUS_SITE = 1;

const uint JTAG_PORT_COUNT = 1;
const uint DEFAULT_JTAG_PORT = 0;
const bool GLOBAL_CSR_SYNC_FLAG=true;
const INT		HilinkIRLength = 8;
const INT		HilinkDR0Length = 2;//tony 20210512:diff 5875
const INT		HilinkDR1Length = 16;

#if TestChip
const DOUBLE    vdvdd_Low=0.72;
const DOUBLE    vdvdd_Mid=0.8;
const DOUBLE    vdvdd_High=0.928;
#else
const DOUBLE    vdvdd_Low=0.72;
const DOUBLE    vdvdd_Mid=0.8;
const DOUBLE    vdvdd_High=0.88;
#endif

const string vdvdd_spec = "DVDD08_AVS";

#ifdef TestChip
#define READ_WAIT 10
const string AHB_MACRO0_NAME="LR";//AHB
const string AHB_MACRO1_NAME="SR";
const string AHB_MACRO0_TDO="HLK_TDO_LR";
const string AHB_MACRO1_TDO="HLK_TDO_SR";
const string AHB_MACRO0_SEL="d2s_AHB_select_LR";
const string AHB_MACRO1_SEL="d2s_AHB_select_SR";
const string AHB_MACROALL_SEL="d2s_AHB_select_LR_And_SR";
const string AHB_MACRO0_INTERCEPT="TAP_INTERCEPT_LR";
const string AHB_MACRO1_INTERCEPT="TAP_INTERCEPT_SR";
const string AHB_SHIFT_DR="TAP_SHIFTDR";
const string AHB_UPDATE_DR="TAP_UPDATEDR";

#endif

typedef map<uint,T_HILINK_INFO> Map_HILINK_INFO;

typedef struct {
	DOUBLE			Data_Rate;   /*Gbps*/
	INT			PllSel;
	INT				RateMode;
	INT				DataWidth;
	TxFIR_SETTING	TxFIR_USER;
	RxCTLE_SETTING 	RxCTLE_USER;
	DFE_SETTING     DFE_USER;
	STRING          Coreclk_sel;
	INT             GB_Enable;
} CUSTPARA;

typedef struct {
	DOUBLE 	RefclkMHz;		 /*Mhz*/
	DOUBLE 	RefclkMHz2;		 /*Mhz*/
	INT		RefclkBus;
	INT		SDiv;
} SSPARA;

typedef struct {
	DOUBLE	KaDiv;
	INT 	KbDiv;
	DOUBLE	HSCLK;		/*Ghz*/
	INT 	NaDiv;
	INT 	NbDiv;
	INT     Pvalue;
	INT     Svalue;
	INT		Mdiv;		/*REFCLKDIV*/
	INT     PllMclkPreDiv;
	INT		J32bdiv;		/*REFCLKDIV*/
	INT		J40bdiv;		/*REFCLKDIV*/
	INT     HsClkDistClkSpare_Bit2;
} CSPARA;

/*******************************************************************************************************/
/**********************     User's customization for a new project begin     ***************************/
/*******************************************************************************************************/




#if TestChip
const T_JTAG_DEFINITION JTAG_PORT_CONFIG[JTAG_PORT_COUNT]={
		{"pJTAG","JTAG_TDI","JTAG_TDO","JTAG_TMS",
				{HilinkIRLength},{HilinkDR0Length},{HilinkDR1Length},
				{
				 "d2s_JTAG_write_template"
				,"d2s_JTAG_write_template"
				,"d2s_JTAG_write_template"
				,"d2s_JTAG_write_template"
				,"d2s_JTAG_write_template"
				,"d2s_JTAG_write_template"
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
////5875		/*Macro0*/	{ 0 , { PLL0,4, HILINK_IP, H30_LR, 0x26, 0x01, 0x22, 0x0000, 0x25 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
		/*Macro0*/	{ 0 , { PLL0,2, HILINK_IP, H30_LR, 0x23, 0x0000001, 0x1F, 0x0000, 0x22 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
////5875				/*Lane0*/	{LANE_BOTH,"H30LR_M0L0","","SERDES_TX3_P", "SERDES_TX3_N","", "SERDES_RX3_P", "SERDES_RX3_N",},
////5875				/*Lane1*/	{LANE_BOTH,"H30LR_M0L1","","SERDES_TX2_P", "SERDES_TX2_N","", "SERDES_RX2_P", "SERDES_RX2_N",},
////5875				/*Lane2*/	{LANE_BOTH,"H30LR_M0L2","","SERDES_TX1_P", "SERDES_TX1_N","", "SERDES_RX1_P", "SERDES_RX1_N",},
////5875				/*Lane3*/	{LANE_BOTH,"H30LR_M0L3","","SERDES_TX0_P", "SERDES_TX0_N","", "SERDES_RX0_P", "SERDES_RX0_N",}
				/*Lane0*/	{LANE_BOTH,"H30LR_M0L0","","TX_SDS0_P", "TX_SDS0_N","", "RX_SDS0_P", "RX_SDS0_N",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M0L1","","TX_SDS1_P", "TX_SDS1_N","", "RX_SDS1_P", "RX_SDS1_N",}
						}
					} 
////5875		/*Macro1*/	{ 1 , { PLL0,4, HILINK_IP, H30_LR, 0x26, 0x02, 0x22, 0x0001, 0x25 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
		/*Macro1*/	{ 1 , { PLL0,2, HILINK_IP, H30_LR, 0x23, 0x0000002, 0x1F, 0x0001, 0x22 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
////5875				/*Lane0*/	{LANE_BOTH,"H30LR_M1L0","","SERDES_TX4_P", "SERDES_TX4_N","", "SERDES_RX4_P", "SERDES_RX4_N",},
////5875				/*Lane1*/	{LANE_BOTH,"H30LR_M1L1","","SERDES_TX5_P", "SERDES_TX5_N","", "SERDES_RX5_P", "SERDES_RX5_N",},
////5875				/*Lane2*/	{LANE_BOTH,"H30LR_M1L2","","SERDES_TX6_P", "SERDES_TX6_N","", "SERDES_RX6_P", "SERDES_RX6_N",},
////5875				/*Lane3*/	{LANE_BOTH,"H30LR_M1L3","","SERDES_TX7_P", "SERDES_TX7_N","", "SERDES_RX7_P", "SERDES_RX7_N",}
				/*Lane0*/	{LANE_BOTH,"H30LR_M1L0","","TX_SDS2_P", "TX_SDS2_N","", "RX_SDS2_P", "RX_SDS2_N",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M1L1","","TX_SDS3_P", "TX_SDS3_N","", "RX_SDS3_P", "RX_SDS3_N",}
						}
					} 
//		/*Macro2*/	{ 2 , { PLL0,4, HILINK_IP, H30_LR, 0x26, 0x04, 0x22, 0x0002, 0x25 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
//						{
//				/*Lane0*/	{LANE_BOTH,"H30LR_M2L0","","SERDES_TX8_P", "SERDES_TX8_N","", "SERDES_RX8_P", "SERDES_RX8_N",},
//				/*Lane1*/	{LANE_BOTH,"H30LR_M2L1","","SERDES_TX9_P", "SERDES_TX9_N","", "SERDES_RX9_P", "SERDES_RX9_N",},
//				/*Lane2*/	{LANE_BOTH,"H30LR_M2L2","","SERDES_TX10_P", "SERDES_TX10_N","", "SERDES_RX10_P", "SERDES_RX10_N",},
//				/*Lane3*/	{LANE_BOTH,"H30LR_M2L3","","SERDES_TX11_P", "SERDES_TX11_N","", "SERDES_RX11_P", "SERDES_RX11_N",}
//						}
//					} 
//		/*Macro3*/	{ 3 , { PLL0,4, HILINK_IP, H30_LR, 0x26, 0x08, 0x22, 0x0003, 0x25 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
//						{
//				/*Lane0*/	{LANE_BOTH,"H30LR_M3L0","","SERDES_TX12_P", "SERDES_TX12_N","", "SERDES_RX12_P", "SERDES_RX12_N",},
//				/*Lane1*/	{LANE_BOTH,"H30LR_M3L1","","SERDES_TX13_P", "SERDES_TX13_N","", "SERDES_RX13_P", "SERDES_RX13_N",},
//				/*Lane2*/	{LANE_BOTH,"H30LR_M3L2","","SERDES_TX14_P", "SERDES_TX14_N","", "SERDES_RX14_P", "SERDES_RX14_N",},
//				/*Lane3*/	{LANE_BOTH,"H30LR_M3L3","","SERDES_TX15_P", "SERDES_TX15_N","", "SERDES_RX15_P", "SERDES_RX15_N",}
//						}
//					} 
//		/*Macro4*/	{ 4 , { PLL0,4, HILINK_IP, H30_LR, 0x26, 0x10, 0x22, 0x0004, 0x25 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
//						{
//				/*Lane0*/	{LANE_BOTH,"H30LR_M4L0","","SERDES_TX16_P", "SERDES_TX16_N","", "SERDES_RX16_P", "SERDES_RX16_N",},
//				/*Lane1*/	{LANE_BOTH,"H30LR_M4L1","","SERDES_TX17_P", "SERDES_TX17_N","", "SERDES_RX17_P", "SERDES_RX17_N",},
//				/*Lane2*/	{LANE_BOTH,"H30LR_M4L2","","SERDES_TX18_P", "SERDES_TX18_N","", "SERDES_RX18_P", "SERDES_RX18_N",},
//				/*Lane3*/	{LANE_BOTH,"H30LR_M4L3","","SERDES_TX19_P", "SERDES_TX19_N","", "SERDES_RX19_P", "SERDES_RX19_N",}
//						}
//					} 
//		/*Macro5*/	{ 5 , { PLL0,4, HILINK_IP, H30_LR, 0x26, 0x20, 0x22, 0x0005, 0x25 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
//						{
//				/*Lane0*/	{LANE_BOTH,"H30LR_M5L0","","SERDES_TX20_P", "SERDES_TX20_N","", "SERDES_RX20_P", "SERDES_RX20_N",},
//				/*Lane1*/	{LANE_BOTH,"H30LR_M5L1","","SERDES_TX21_P", "SERDES_TX21_N","", "SERDES_RX21_P", "SERDES_RX21_N",},
//				/*Lane2*/	{LANE_BOTH,"H30LR_M5L2","","SERDES_TX22_P", "SERDES_TX22_N","", "SERDES_RX22_P", "SERDES_RX22_N",},
//				/*Lane3*/	{LANE_BOTH,"H30LR_M5L3","","SERDES_TX23_P", "SERDES_TX23_N","", "SERDES_RX23_P", "SERDES_RX23_N",}
//						}
//					} 
		};
HILINK_INFO_END();

 #else
const T_JTAG_DEFINITION JTAG_PORT_CONFIG[JTAG_PORT_COUNT]={
		{"pJTAG","JTAG_TDI","JTAG_TDO","JTAG_TMS","JTAG_TCK","JTAG_TRSTN",
				{"WTB x1_pJTAG_STD","WTB_x1_JTAG_FASTDIFF"},
				HilinkIRLength,HilinkDR0Length,HilinkDR1Length,
				{
				    "d2s_JTAG_write_template"
					,"d2s_JTAG_write_template"
					,"d2s_JTAG_write_template"
					,"d2s_JTAG_write_template"
					,"d2s_JTAG_write_template"
					,"d2s_JTAG_write_template"
					,"d2s_JTAG_read_template"
					,"d2s_JTAG_wait_template"
					,"d2s_JTAG_writeDR_template"
					,"d2s_JTAG_writeIR_template"
				}
		}
};
const string SSMacroIDList = "0";
const string SSMacroIDList_Refclk1 = "0";

extern string GlobalInitPattern;

//* HILINK_INFO[] access Macro Info
//* LANE_INFO[MacroID][] access Lane Info
HILINK_INFO_BEGIN();
		//redefine your IP type
		const static sT_HILINK_INFO _HILINK_INFO[] = {
////5875		/*Macro0*/	{ 0 , { PLL0,4, H30_IP, H30_LR, 0, 0x26, 0x01, 0x22, 0x0000, 0x25 ,{0,1,2,3},{3,2,1,0},{1,1,1,1},{1,0},{1,0}},"0,1,2,3" ,"3,2,1,0",
		/*Macro0*/	{ 0 , { PLL0,2, H30_IP, H30_LR, 0, 0x23, 0x0000001, 0x1F, 0x0000, 0x22 ,{0,1},{1,0},{1,1},{1,0},{1,0}},"0,1" ,"1,0",
						{
////5875				/*Lane0*/	{LANE_BOTH,"H30LR_M0L0","SERDES_TX0","SERDES_TX0_P", "SERDES_TX0_N","SERDES_RX0", "SERDES_RX0_P", "SERDES_RX0_N",},
////5875				/*Lane1*/	{LANE_BOTH,"H30LR_M0L1","SERDES_TX1","SERDES_TX1_P", "SERDES_TX1_N","SERDES_RX1", "SERDES_RX1_P", "SERDES_RX1_N",},
////5875				/*Lane2*/	{LANE_BOTH,"H30LR_M0L2","SERDES_TX2","SERDES_TX2_P", "SERDES_TX2_N","SERDES_RX2", "SERDES_RX2_P", "SERDES_RX2_N",},
////5875				/*Lane3*/	{LANE_BOTH,"H30LR_M0L3","SERDES_TX3","SERDES_TX3_P", "SERDES_TX3_N","SERDES_RX3", "SERDES_RX3_P", "SERDES_RX3_N",}
				/*Lane0*/	{LANE_BOTH,"H30LR_M0L0","","TX_SDS0_P", "TX_SDS0_N","", "RX_SDS0_P", "RX_SDS0_N",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M0L1","","TX_SDS1_P", "TX_SDS1_N","", "RX_SDS1_P", "RX_SDS1_N",}
						}
					},
////5875		/*Macro1*/	{ 1 , { PLL0,4, H30_IP, H30_LR, 0, 0x26, 0x02, 0x22, 0x0001, 0x25 ,{0,1,2,3},{3,2,1,0},{1,1,1,1},{1,0},{1,0}},"0,1,2,3" ,"3,2,1,0",
		/*Macro1*/	{ 1 , { PLL0,2, H30_IP, H30_LR, 0, 0x23, 0x0000002, 0x1F, 0x0001, 0x22 ,{0,1},{1,0},{1,1},{1,0},{1,0}},"0,1" ,"1,0",
						{
////5875				/*Lane0*/	{LANE_BOTH,"H30LR_M1L0","SERDES_TX4","SERDES_TX4_P", "SERDES_TX4_N","SERDES_RX4", "SERDES_RX4_P", "SERDES_RX4_N",},
////5875				/*Lane1*/	{LANE_BOTH,"H30LR_M1L1","SERDES_TX5","SERDES_TX5_P", "SERDES_TX5_N","SERDES_RX5", "SERDES_RX5_P", "SERDES_RX5_N",},
////5875				/*Lane2*/	{LANE_BOTH,"H30LR_M1L2","SERDES_TX6","SERDES_TX6_P", "SERDES_TX6_N","SERDES_RX6", "SERDES_RX6_P", "SERDES_RX6_N",},
////5875				/*Lane3*/	{LANE_BOTH,"H30LR_M1L3","SERDES_TX7","SERDES_TX7_P", "SERDES_TX7_N","SERDES_RX7", "SERDES_RX7_P", "SERDES_RX7_N",}
				/*Lane0*/	{LANE_BOTH,"H30LR_M1L0","","TX_SDS2_P", "TX_SDS2_N","", "RX_SDS2_P", "RX_SDS2_N",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M1L1","","TX_SDS3_P", "TX_SDS3_N","", "RX_SDS3_P", "RX_SDS3_N",}
						}
					}//note "," tony 
//		/*Macro2*/	{ 2 , { PLL0,4, H30_IP, H30_LR, 0, 0x26, 0x04, 0x22, 0x0002, 0x25 ,{0,1,2,3},{3,2,1,0},{1,1,1,1},{1,0},{1,0}},"0,1,2,3" ,"3,2,1,0",
//						{
//				/*Lane0*/	{LANE_BOTH,"H30LR_M2L0","SERDES_TX8","SERDES_TX8_P", "SERDES_TX8_N","SERDES_RX8", "SERDES_RX8_P", "SERDES_RX8_N",},
//				/*Lane1*/	{LANE_BOTH,"H30LR_M2L1","SERDES_TX9","SERDES_TX9_P", "SERDES_TX9_N","SERDES_RX9", "SERDES_RX9_P", "SERDES_RX9_N",},
//				/*Lane2*/	{LANE_BOTH,"H30LR_M2L2","SERDES_TX10","SERDES_TX10_P", "SERDES_TX10_N","SERDES_RX10", "SERDES_RX10_P", "SERDES_RX10_N",},
//				/*Lane3*/	{LANE_BOTH,"H30LR_M2L3","SERDES_TX11","SERDES_TX11_P", "SERDES_TX11_N","SERDES_RX11", "SERDES_RX11_P", "SERDES_RX11_N",}
//						}
//					},
//		/*Macro3*/	{ 3 , { PLL0,4, H30_IP, H30_LR, 0, 0x26, 0x08, 0x22, 0x0003, 0x25 ,{0,1,2,3},{3,2,1,0},{1,1,1,1},{1,0},{1,0}},"0,1,2,3" ,"3,2,1,0",
//						{
//				/*Lane0*/	{LANE_BOTH,"H30LR_M3L0","SERDES_TX12","SERDES_TX12_P", "SERDES_TX12_N","SERDES_RX12", "SERDES_RX12_P", "SERDES_RX12_N",},
//				/*Lane1*/	{LANE_BOTH,"H30LR_M3L1","SERDES_TX13","SERDES_TX13_P", "SERDES_TX13_N","SERDES_RX13", "SERDES_RX13_P", "SERDES_RX13_N",},
//				/*Lane2*/	{LANE_BOTH,"H30LR_M3L2","SERDES_TX14","SERDES_TX14_P", "SERDES_TX14_N","SERDES_RX14", "SERDES_RX14_P", "SERDES_RX14_N",},
//				/*Lane3*/	{LANE_BOTH,"H30LR_M3L3","SERDES_TX15","SERDES_TX15_P", "SERDES_TX15_N","SERDES_RX15", "SERDES_RX15_P", "SERDES_RX15_N",}
//						}
//					},
//		/*Macro4*/	{ 4 , { PLL0,4, H30_IP, H30_LR, 0, 0x26, 0x10, 0x22, 0x0004, 0x25 ,{0,1,2,3},{3,2,1,0},{1,1,1,1},{1,0},{1,0}},"0,1,2,3" ,"3,2,1,0",
//						{
//				/*Lane0*/	{LANE_BOTH,"H30LR_M4L0","SERDES_TX16","SERDES_TX16_P", "SERDES_TX16_N","SERDES_RX16", "SERDES_RX16_P", "SERDES_RX16_N",},
//				/*Lane1*/	{LANE_BOTH,"H30LR_M4L1","SERDES_TX17","SERDES_TX17_P", "SERDES_TX17_N","SERDES_RX17", "SERDES_RX17_P", "SERDES_RX17_N",},
//				/*Lane2*/	{LANE_BOTH,"H30LR_M4L2","SERDES_TX18","SERDES_TX18_P", "SERDES_TX18_N","SERDES_RX18", "SERDES_RX18_P", "SERDES_RX18_N",},
//				/*Lane3*/	{LANE_BOTH,"H30LR_M4L3","SERDES_TX19","SERDES_TX19_P", "SERDES_TX19_N","SERDES_RX19", "SERDES_RX19_P", "SERDES_RX19_N",}
//						}
//					},
//		/*Macro5*/	{ 5 , { PLL0,4, H30_IP, H30_LR, 0, 0x26, 0x20, 0x22, 0x0005, 0x25 ,{0,1,2,3},{3,2,1,0},{1,1,1,1},{1,0},{1,0}},"0,1,2,3" ,"3,2,1,0",
//						{
//				/*Lane0*/	{LANE_BOTH,"H30LR_M5L0","SERDES_TX20","SERDES_TX20_P", "SERDES_TX20_N","SERDES_RX20", "SERDES_RX20_P", "SERDES_RX20_N",},
//				/*Lane1*/	{LANE_BOTH,"H30LR_M5L1","SERDES_TX21","SERDES_TX21_P", "SERDES_TX21_N","SERDES_RX21", "SERDES_RX21_P", "SERDES_RX21_N",},
//				/*Lane2*/	{LANE_BOTH,"H30LR_M5L2","SERDES_TX22","SERDES_TX22_P", "SERDES_TX22_N","SERDES_RX22", "SERDES_RX22_P", "SERDES_RX22_N",},
//				/*Lane3*/	{LANE_BOTH,"H30LR_M5L3","SERDES_TX23","SERDES_TX23_P", "SERDES_TX23_N","SERDES_RX23", "SERDES_RX23_P", "SERDES_RX23_N",}
//						}
//					} 
		};
HILINK_INFO_END();
  #endif




/*************************************** CP/FT Program **************************************************/
const STRING	CP_FT_Program = "FT";

/*************************************** DEFAULT INIT VECTOR ********************************************/

/*************************************** DEFAULT Firmware  ********************************************/

const STRING    HILINK_FIRMWARE_LABEL_DEFAULT  = "HiLink30LRV101_Calib_ATE_SRAM_1.2.6_0131_1203.hex.bin_WRITE";//check ok

const STRING    HILINK_CAL_NOAPI_FIRMWARE_LABEL_DEFAULT  = "HiLink30LRV101_Calib_ATE_SRAM_1.2.6_0131_1203_noapi.hex.bin_WRITE";//check ok


const STRING    HILINK_ADPT_NOAPI_FIRMWARE_LABEL_DEFAULT  = "HiLink30LRV101_Ate_Adapt_SRAM_1.1.2_0315_1138_noapi.hex.bin_WRITE";//check ok

const STRING    HILINK_DPM_Bin  = "HiLink30V101_ABIST_Dpm_SRAM_1.0.9_0325_1137.hex.bin_WRITE"; //check ok

const STRING 	HILINK_FIRMWARE_LABEL_FASTDIFF = HILINK_FIRMWARE_LABEL_DEFAULT + "_FASTDIFF";
const STRING 	HILINK_CAL_NOAPI_FIRMWARE_LABEL_FASTDIFF = HILINK_CAL_NOAPI_FIRMWARE_LABEL_DEFAULT + "_FASTDIFF";
const STRING 	HILINK_ADPT_NOAPI_FIRMWARE_LABEL_FASTDIFF = HILINK_ADPT_NOAPI_FIRMWARE_LABEL_DEFAULT + "_FASTDIFF";

const LONG 	 	HILINK_FIRMWARE_CYCLE_DEFAULT = 753664;
const LONG 	 	HILINK_CAL_NOAPI_FIRMWARE_CYCLE_DEFAULT = 565248;
const LONG 	 	HILINK_ADPT_NOAPI_FIRMWARE_CYCLE_DEFAULT = 716956;
const LONG		HILINK_DPM_Bin_CYCLE = 753664;

const LONG 	 	HILINK_FIRMWARE_CYCLE_FASTDIFF =753664;
const LONG 	 	HILINK_CAL_NOAPI_FIRMWARE_CYCLE_FASTDIFF =565247;
const LONG 	 	HILINK_ADPT_NOAPI_FIRMWARE_CYCLE_FASTDIFF =716956;


/*************************************** UDI PATTERN  ********************************************/
const string ATE_MODE_RX_FASTDIFF_PATTERN_LABEL_PRBS15_SHORT =  "PRBS15_1e7_SHFRXDATA_x12_RPT_SHORT";
const long ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE_PRBS15_SHORT = 65534*100;

const string ATE_MODE_RX_FASTDIFF_PATTERN_LABEL_PRBS15 =  "PRBS15_1e7_SHFRXDATA_x12_RPT";
const long ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE_PRBS15 = 65534*100;

const string ATE_MODE_RX_FASTDIFF_PATTERN_LABEL_PRBS15_STRESS =  "PRBS15_1e7_SHFRXDATA_x12_RPT_STRESS";
const long ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE_PRBS15_STRESS = 65534*250;

const string ATE_MODE_RX_FASTDIFF_PATTERN_LABEL_PRBS15_STRESS_EYESCAN =  "PRBS15_1e7_SHFRXDATA_x12_RPT_STRESS_EYESCAN";
const long ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE_PRBS15_STRESS_EYESCAN = 65534*5000;

const string ATE_MODE_RX_FASTDIFF_PATTERN_LABEL_PRBS15_LONG =  "PRBS15_1e7_SHFRXDATA_x12_RPT_LONG";
const long ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE_PRBS15_LONG = 65534*5000;

const string ATE_MODE_RX_FASTDIFF_PATTERN_LABEL_PRBS15_LONG2 =  "PRBS15_1e7_SHFRXDATA_x12_RPT_LONG2";
const long ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE_PRBS15_LONG2 = 65534*8000;

const string ATE_MODE_RX_FASTDIFF_PATTERN_LABEL_PRBS15_LONG3 =  "PRBS15_1e7_SHFRXDATA_x12_RPT_LONG3";
const long ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE_PRBS15_LONG3 = 65534*10000;

const string ATE_MODE_RX_FASTDIFF_PATTERN_LABEL_PRBS15_EYE =  "PRBS15_1e7_SHFRXDATA_x12_RPT_EYE";
const long ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE_PRBS15_EYE = 65534*6000;

const string ATE_MODE_RX_FASTDIFF_PATTERN_LABEL_PRBS7 =  "PRBS7_1e7_SHFRXDATA_x12_RPT";
const long ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE_PRBS7 = 127*30000;

const string ATE_MODE_RX_FASTDIFF_PATTERN_LABEL_CLK =  "x1Clock_x12_pUDIRXDATA_RPT";
const long ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE_CLK = 100*20000;

/************************* FWABIST OperationType *************************/
enum OperationType	{
	EQUAL_TYPE,									// a
	ADD_ARB_TYPE,								// a + b + c + ...
	SUB_ARB_TYPE,								// a - b - c - ...
	MUL_ARB_TYPE,								// a * b * c * ...
	DIV_ARB_TYPE,								// 1.0 * a / b / c / ...
	AVE_ARB_TYPE,								// (a + b + c + ...) / size(a,b,c,...)
	EQUAL_ABS_TYPE,
	ADD_ARB_ABS_TYPE,
	SUB_ARB_ABS_TYPE,
	MUL_ARB_ABS_TYPE,
	DIV_ARB_ABS_TYPE,
	AVE_ARB_ABS_TYPE,

	MIX_MULx_DIVy_1_TYPE,						// a*x/y									// x = arg1  y = arg2
	MIX_MIN_MIN_MIN_MULx_DIVy_4_TYPE,			// ( (a-b)-(c-d) )*x/y 						// x = arg1  y = arg2
	MIX_MIN_MIN_ADD_4_TYPE,						// (a-b)+(c-d)
	MIX_ADD_AVE_MIN_3_TYPE,						// (a+b)/2 - c
	MIX_MIN_MIN_DIV_LOG_8_TYPE,					// 20log( ((a-b)-(c-d)) / ((e-f)-(g-h)) )
	MIX_MIN_MIN_MIN_MULx_DIVy_4_ABS_TYPE,		// abs( ( (a-b)-(c-d) )*x/y )				// x = arg1  y = arg2
	MIX_SUB_MULx_2_TYPE,						// (a-b)*x 									// x = arg1
	MIX_MIN_MIN_MIN_DIVx_3_ABS_TYPE,			// abs( (a-b-c) / x ) 						// x = arg1

	MIX_lld2Freq_1_TYPE,						// (a < 4096) ? (96 * 156.25 * (1 + a * 1.0 / (4096 - a)) / x) : (96 * 156.25 * (1 - (a - 4096) * 1.0 / 4096) / x)		// x = arg1
	MIX_IF_MULx_DIVy_1_TYPE,

	MIX_COMPLEMENT_1_TYPE,						// exp: FFFA => -6    7FFA => 32762

	NULL_TYPE,
	UT_TEST_TYPE,
};


/*************************************** FIRMWARE ABIST BEGIN  **************************************/
const string FW_Alphagen_Bin =  "HiLink30V101_ABIST_Alphagen_SRAM.hex.bin_WRITE";
const long   FW_Alphagen_Cycles = 753664;

const string Atb_Lr_Bin =  "HiLink30LRV101_ABIST_Atb_LR_SRAM.hex.bin_WRITE";
const long   Atb_Lr_Cycles = 753664;

const string DcGain_Bin = "HiLink30V101_ABIST_DcGain_SRAM_1.1.0_0322_2259.hex.bin_WRITE";
const long   DcGain_Cycles = 753664;

//const string DfeIdac_Bin =  "HiLink30V101_ABIST_DfeIdac_SRAM_1.1.0_0322_2257.hex.bin_WRITE";
const string DfeIdac_Bin =  "HiLink30V101_ABIST_DfeIdac_SRAM_1.1.1_0706_2157.hex.bin_WRITE";
const long   DfeIdac_Cycles = 753664;

const string Regulator_Bin =  "HiLink30V101_ABIST_Regulator_SRAM.hex.bin_WRITE";
//const string Regulator_Bin =  "HiLink30V101_ABIST_Regulator_SRAM_rev1.1.1_20170612.hex.bin_WRITE";//5875
const long   Regulator_Cycles = 753664;

const string Regulator_Search_Bin =  "HiLink30V101_ABIST_Regulator_SRAM_rev1.1.1_20170612.hex.bin_WRITE";
const long   Regulator_Search_Cycles = 753664;

const string LatchOffset_Bin =   "HiLink30LRV101_ABIST_LatchOffset_LR_SRAM.hex.bin_WRITE";
const long   LatchOffset_Cycles = 753664;

const string AdcStability_Bin =   "HiLink30V101_ABIST_AdcStability_SRAM_1.0.0_0612_1025.hex.bin_WRITE";
const long   AdcStability_Cycles = 753664;

const string DLOS_Bin =   "HiLink30V101_ABIST_DLos_SRAM_1.0.0_0612_0843.hex.bin_WRITE";
const long   DLOS_Cycles = 753664;

const string Comparator_Bin =   "HiLink30V101_ABIST_Comparator_SRAM_1.0.0_0612_2259.hex.bin_WRITE";
const long   Comparator_Cycles = 753664;

//const string VCOTuningRange_Bin =   "HiLink30V101_ABIST_VCO_SRAM.hex.bin_WRITE";
const string VCOTuningRange_Bin =   "HiLink30V101_ABIST_VCO_SRAM_1.1.6_0706_2154.hex.bin_WRITE";
const long   VCOTuningRange_Cycles = 753664;
 /*************************************** FIRMWARE ABIST END  *****************************************/

/****************************************Used for TTR****************************************************/
const TTR_OPTIMIZE_CYCLE OPTIMIZE_CYCLE = {
		38400,	/*****INT ALOS_ExpectValue;*****/
		9800,	/*****INT ALOS_ReadPerLane;*****/
};

 const RxCTLE_SETTING RxCTLE_DEFAULT = {
				{7,7,7},/*CTLE GAIN*/
				{0,0,0},/*CTLE BOOST*/
				{0,0,0},/*CTLE Za*/
				{0,0,0},/*CTLE Sqh*/
				{0,0,0},/*CTLE Rmband*/
				{0,0,0},/*CTLE Cmband*/
				{0,0,0},/*CTLE Hfzen*/

};
/************************************Used for mLaneIdNorthCs*********************************************/

/*******************************Used for Configure core_clk select****************************************/
const int giCore_clk_selext_pin_api = 0;
const int giCore_clk_sel_pin_api = 0;
const int giLifeclk2dig_sel_pin_api = 0;
const int giCoreclk_sel_en_api = 1;

const TxFIR_SETTING default_TxFIR_SETTING={0,0,0,0,0};
const RxCTLE_SETTING default_RxCTLE_SETTING={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
const DFE_SETTING default_DFE_SETTING={{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0}};

const CUSTPARA default_CUSTPARA={0,0,0,0,default_TxFIR_SETTING,default_RxCTLE_SETTING,default_DFE_SETTING,"",1};
const SSPARA default_SSPARA={0,0,0,1};
const CSPARA default_CSPARA={
			0,//DOUBLE	KaDiv;
			0,//INT 	KbDiv;
			0,//DOUBLE	HSCLK;		/*Ghz*/
			0,//INT 	NaDiv;
			0,//INT 	NbDiv;
			0,//INT     Pvalue;
			0,//INT     Svalue;
			0,//INT		Mdiv;		/*REFCLKDIV*/
			0,//INT     PllMclkPreDiv;
			0,//INT		J32bdiv;		/*REFCLKDIV*/
			0,//INT		J40bdiv;		/*REFCLKDIV*/
			0//INT     mck2dig_div1_pwrdb;
			};
// #define AUTO_HWPRBS
#undef AUTO_HWPRBS
#ifdef AUTO_HWPRBS
const string HWPRBS_GROUP="RX_DATA,TX_DATA";
const string HWPRBS_RX_PORT="pUDIRXDATA";
const string HWPRBS_TX_PORT="pUDITXDATA";
const string HWPRBS_RX_LABEL="PRBS_ENGINE_SHFRXDATA";
const string HWPRBS_TX_LABEL="PRBS_ENGINE_SHFTXDATA";



#endif
/********************************************************************************************************/
/************************      User's customization for a new project end      **************************/
/********************************************************************************************************/


const CSAPI default_CSAPI[7]={
		{0,	0, 0, 0, 0,	0, 0, 0, 0,	0, 0, 0, 0,	0},//case1
		{1,	1, 1, 1, 1,	1, 1, 1, 1,	1, 1, 0, 0,	0},//case2
		{0,	0, 0, 0, 0,	0, 0, 0, 0,	0, 0, 1, 1,	1},//case3
		{1,	1, 1, 1, 1,	1, 1, 1, 1,	0, 1, 1, 1,	1},//case4
		{1,	1, 1, 1, 0,	1, 1, 1, 1,	1, 1, 1, 1,	1},//case5
		{1,	1, 1, 1, 0,	1, 1, 1, 1,	0, 1, 1, 1,	1},//case6
		{1,	1, 1, 1, 1,	1, 1, 1, 1,	1, 1, 1, 1,	1} //case7
};


const DSAPI default_DSAPI[8]={
		{0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	1,	0,	0	},//case1: H30LRV101 full calibration
		{0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	1,	0,	0	},//case2: H30VSRV101 full calibration
		{1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	0,	0	},//case3: Centering phase aligner and bump DCD calibration
		{1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	0	},//case4: Centering phase aligner only
		{1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	0	},//case5: Bump DCD calibration only
		{1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	0,	0	},//case6: Predriver loopback DCD calibration only
		{1,	0,	1,	1,	1,	0,	0,	1,	1,	1,	1,	1,	0,	0,	1,	0,	1,	1,	1,	0,	1	},//case7: Bypass calibration for ATE
		{1,	0,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	0,	1	}//case8:
};

const DSAPI_Adaptation default_DSAPI_Adaptation[5]={
		{1,	1,	0,	1,	0,	1,	1,	1,	2,	1,	0},//case1: H30LRV101 ATE CTLE Adaptation
		{0,	0,	0,	1,	0,	0,	1,	0,	6,	1,	0},//case2: H30VSRV101 ATE CTLE Adaptation
		{1,	1,	0,	1,	0,	1,	1,	1,	2,	1,	0},//case3: H30LRV101 ATE Pre-driver Loopback CTLE Adaptation
		{0,	0,	0,	1,	0,	0,	1,	0,	2,	1,	1},//case4: H30VSRV101 ATE Pre-driver Loopback TLE Adaptation
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0}//case5: reset
};






const int JAM_COUNT = 6;
const int DEFAULT_SPI_PORT_ID = 0;
//const T_JAM_DEFINITION JAM_CONFIG[JAM_COUNT] = {
//	{"pSPI1","SDI_JTR1","SDO_JTR1","d2s_SPI1_WaitPLLLocked_template","d2s_SPI1_CheckPLLLocked_template",64,"X1",
//		{
//			 "d2s_SPI1_write_template",
//			 "d2s_SPI1_read_template",
//			 "d2s_SPI1_idle_template"
//		}
//	},
//	{"pSPI2","SDI_JTR2","SDO_JTR2","d2s_SPI2_WaitPLLLocked_template","d2s_SPI2_CheckPLLLocked_template",64,"X2",
//		{
//			 "d2s_SPI2_write_template",
//			 "d2s_SPI2_read_template",
//			 "d2s_SPI2_idle_template"
//		}
//	},
//	{"pSPI3","SDI_JTR3","SDO_JTR3","d2s_SPI3_WaitPLLLocked_template","d2s_SPI3_CheckPLLLocked_template",64,"X3",
//		{
//			 "d2s_SPI3_write_template",
//			 "d2s_SPI3_read_template",
//			 "d2s_SPI3_idle_template"
//		}
//	},
//	{"pSPI4","SDI_JTR4","SDO_JTR4","d2s_SPI4_WaitPLLLocked_template","d2s_SPI4_CheckPLLLocked_template",64,"X4",
//		{
//			 "d2s_SPI4_write_template",
//			 "d2s_SPI4_read_template",
//			 "d2s_SPI4_idle_template"
//		}
//	},
//	{"pSPI5","SDI_JTR5","SDO_JTR5","d2s_SPI5_WaitPLLLocked_template","d2s_SPI5_CheckPLLLocked_template",64,"X5",
//		{
//			 "d2s_SPI5_write_template",
//			 "d2s_SPI5_read_template",
//			 "d2s_SPI5_idle_template"
//		}
//	},
//	{"pSPI6","SDI_JTR6","SDO_JTR6","d2s_SPI6_WaitPLLLocked_template","d2s_SPI6_CheckPLLLocked_template",64,"X6",
//		{
//			 "d2s_SPI6_write_template",
//			 "d2s_SPI6_read_template",
//			 "d2s_SPI6_idle_template"
//		}
//	}
//};

const double JAM_RELAY_WAITTIME_SEC=0.01;
const string JAM_KEEPALIVE_FWTASK_ABIST = "FTCG SKPR,OFF,(@@);APRM FRC;FTCG SKPR,ON,(pCLKIn1,pCLKIn2,pCLKIn3,pCLKIn4,pCLKIn5,pCLKIn6)";
const string JAM_KEEPALIVE_FWTASK_ATE = "FTCG SKPR,OFF,(@@);APRM FRC;FTCG SKPR,ON,(pDUMMYCLOCK,pCLKIn1,pCLKIn2,pCLKIn3,pCLKIn4,pCLKIn5,pCLKIn6)";
const string JAM_CSVFILE_PATH_UNDER_DEVPATH="protocols/scripts";

const string KEEPALIVE_FWTASK_TC = "FTCG SKPR,ON,(pHilink_CLK)";
const string KEEPALIVE_FWTASK_PRODUCT = "FTCG SKPR,ON,(pCLKIn1,pCLKIn2,pCLKIn3,pCLKIn4,pCLKIn5,pCLKIn6)";

const string CLKPORT_PRODUCT="pCLKIn1,pCLKIn2,pCLKIn3,pCLKIn4,pCLKIn5,pCLKIn6";
const string CLKPORT_TC="pCLK_HL30,pCLKIn";

#endif /* USERCONFIG_H_ */
