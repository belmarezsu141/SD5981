#ifndef USERCONFIG_H_
#define USERCONFIG_H_
 #undef TestChip
//* User need to configure the UserConfigFlag
#define HIGGS_PRIVATE 0

#include "mapi.hpp"
#include "HILINK_DRIVE/HiLink_Common_Types.h"
#include "JAM_Setup/JAM_Common_Types.h"
using namespace std;

const INT		FwTypeAdaptNoApi=2;
const INT		FwTypeCalNoApi=1;
const INT		FwTypeCalAll=0;

const INT		FOCUS_SITE = 1;

const uint JTAG_PORT_COUNT = 1;
const uint DEFAULT_JTAG_PORT = 0;
const bool GLOBAL_CSR_SYNC_FLAG=true;
const INT		HilinkIRLength = 16;
const INT		HilinkDR0Length = 20;
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
		/*Macro0*/	{ 0 , { PLL0,8, HILINK_IP, H30_LR, 0x00A1, 0x01000, 0x009D, 0x000C, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M0L0","","LMAG_TX_P0", "LMAG_TX_N0","", "LMAG_RX_P0", "LMAG_RX_N0",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M0L1","","LMAG_TX_P1", "LMAG_TX_N1","", "LMAG_RX_P1", "LMAG_RX_N1",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M0L2","","LMAG_TX_P2", "LMAG_TX_N2","", "LMAG_RX_P2", "LMAG_RX_N2",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M0L3","","LMAG_TX_P3", "LMAG_TX_N3","", "LMAG_RX_P3", "LMAG_RX_N3",},
				/*Lane4*/	{LANE_BOTH,"H30LR_M0L4","","LMAG_TX_P4", "LMAG_TX_N4","", "LMAG_RX_P4", "LMAG_RX_N4",},
				/*Lane5*/	{LANE_BOTH,"H30LR_M0L5","","LMAG_TX_P5", "LMAG_TX_N5","", "LMAG_RX_P5", "LMAG_RX_N5",},
				/*Lane6*/	{LANE_BOTH,"H30LR_M0L6","","LMAG_TX_P6", "LMAG_TX_N6","", "LMAG_RX_P6", "LMAG_RX_N6",},
				/*Lane7*/	{LANE_BOTH,"H30LR_M0L7","","LMAG_TX_P7", "LMAG_TX_N7","", "LMAG_RX_P7", "LMAG_RX_N7",}
						}
					} 
		/*Macro1*/	{ 1 , { PLL0,8, HILINK_IP, H30_LR, 0x00A1, 0x02000, 0x009D, 0x000D, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M1L0","","LMAG_TX_P8", "LMAG_TX_N8","", "LMAG_RX_P8", "LMAG_RX_N8",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M1L1","","LMAG_TX_P9", "LMAG_TX_N9","", "LMAG_RX_P9", "LMAG_RX_N9",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M1L2","","LMAG_TX_P10", "LMAG_TX_N10","", "LMAG_RX_P10", "LMAG_RX_N10",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M1L3","","LMAG_TX_P11", "LMAG_TX_N11","", "LMAG_RX_P11", "LMAG_RX_N11",},
				/*Lane4*/	{LANE_BOTH,"H30LR_M1L4","","LMAG_TX_P12", "LMAG_TX_N12","", "LMAG_RX_P12", "LMAG_RX_N12",},
				/*Lane5*/	{LANE_BOTH,"H30LR_M1L5","","LMAG_TX_P13", "LMAG_TX_N13","", "LMAG_RX_P13", "LMAG_RX_N13",},
				/*Lane6*/	{LANE_BOTH,"H30LR_M1L6","","LMAG_TX_P14", "LMAG_TX_N14","", "LMAG_RX_P14", "LMAG_RX_N14",},
				/*Lane7*/	{LANE_BOTH,"H30LR_M1L7","","LMAG_TX_P15", "LMAG_TX_N15","", "LMAG_RX_P15", "LMAG_RX_N15",}
						}
					} 
		/*Macro12*/	{ 12 , { PLL0,8, HILINK_IP, H30_LR, 0x00A1, 0x00004, 0x009D, 0x0002, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M12L0","","FMAG_TX_P40", "FMAG_TX_N40","", "FMAG_RX_P40", "FMAG_RX_N40",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M12L1","","FMAG_TX_P41", "FMAG_TX_N41","", "FMAG_RX_P41", "FMAG_RX_N41",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M12L2","","FMAG_TX_P42", "FMAG_TX_N42","", "FMAG_RX_P42", "FMAG_RX_N42",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M12L3","","FMAG_TX_P43", "FMAG_TX_N43","", "FMAG_RX_P43", "FMAG_RX_N43",},
				/*Lane4*/	{LANE_BOTH,"H30LR_M12L4","","FMAG_TX_P44", "FMAG_TX_N44","", "FMAG_RX_P44", "FMAG_RX_N44",},
				/*Lane5*/	{LANE_BOTH,"H30LR_M12L5","","FMAG_TX_P45", "FMAG_TX_N45","", "FMAG_RX_P45", "FMAG_RX_N45",},
				/*Lane6*/	{LANE_BOTH,"H30LR_M12L6","","FMAG_TX_P46", "FMAG_TX_N46","", "FMAG_RX_P46", "FMAG_RX_N46",},
				/*Lane7*/	{LANE_BOTH,"H30LR_M12L7","","FMAG_TX_P47", "FMAG_TX_N47","", "FMAG_RX_P47", "FMAG_RX_N47",}
						}
					} 
		/*Macro13*/	{ 13 , { PLL0,8, HILINK_IP, H30_LR, 0x00A1, 0x00008, 0x009D, 0x0003, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M13L0","","FMAG_TX_P24", "FMAG_TX_N24","", "FMAG_RX_P24", "FMAG_RX_N24",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M13L1","","FMAG_TX_P25", "FMAG_TX_N25","", "FMAG_RX_P25", "FMAG_RX_N25",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M13L2","","FMAG_TX_P26", "FMAG_TX_N26","", "FMAG_RX_P26", "FMAG_RX_N26",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M13L3","","FMAG_TX_P27", "FMAG_TX_N27","", "FMAG_RX_P27", "FMAG_RX_N27",},
				/*Lane4*/	{LANE_BOTH,"H30LR_M13L4","","FMAG_TX_P28", "FMAG_TX_N28","", "FMAG_RX_P28", "FMAG_RX_N28",},
				/*Lane5*/	{LANE_BOTH,"H30LR_M13L5","","FMAG_TX_P29", "FMAG_TX_N29","", "FMAG_RX_P29", "FMAG_RX_N29",},
				/*Lane6*/	{LANE_BOTH,"H30LR_M13L6","","FMAG_TX_P30", "FMAG_TX_N30","", "FMAG_RX_P30", "FMAG_RX_N30",},
				/*Lane7*/	{LANE_BOTH,"H30LR_M13L7","","FMAG_TX_P31", "FMAG_TX_N31","", "FMAG_RX_P31", "FMAG_RX_N31",}
						}
					} 
		/*Macro14*/	{ 14 , { PLL0,8, HILINK_IP, H30_LR, 0x00A1, 0x00010, 0x009D, 0x0004, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M14L0","","FMAG_TX_P32", "FMAG_TX_N32","", "FMAG_RX_P32", "FMAG_RX_N32",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M14L1","","FMAG_TX_P33", "FMAG_TX_N33","", "FMAG_RX_P33", "FMAG_RX_N33",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M14L2","","FMAG_TX_P34", "FMAG_TX_N34","", "FMAG_RX_P34", "FMAG_RX_N34",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M14L3","","FMAG_TX_P35", "FMAG_TX_N35","", "FMAG_RX_P35", "FMAG_RX_N35",},
				/*Lane4*/	{LANE_BOTH,"H30LR_M14L4","","FMAG_TX_P36", "FMAG_TX_N36","", "FMAG_RX_P36", "FMAG_RX_N36",},
				/*Lane5*/	{LANE_BOTH,"H30LR_M14L5","","FMAG_TX_P37", "FMAG_TX_N37","", "FMAG_RX_P37", "FMAG_RX_N37",},
				/*Lane6*/	{LANE_BOTH,"H30LR_M14L6","","FMAG_TX_P38", "FMAG_TX_N38","", "FMAG_RX_P38", "FMAG_RX_N38",},
				/*Lane7*/	{LANE_BOTH,"H30LR_M14L7","","FMAG_TX_P39", "FMAG_TX_N39","", "FMAG_RX_P39", "FMAG_RX_N39",}
						}
					} 
		/*Macro15*/	{ 15 , { PLL0,8, HILINK_IP, H30_LR, 0x00A1, 0x00020, 0x009D, 0x0005, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M15L0","","FMAG_TX_P8", "FMAG_TX_N8","", "FMAG_RX_P8", "FMAG_RX_N8",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M15L1","","FMAG_TX_P9", "FMAG_TX_N9","", "FMAG_RX_P9", "FMAG_RX_N9",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M15L2","","FMAG_TX_P10", "FMAG_TX_N10","", "FMAG_RX_P10", "FMAG_RX_N10",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M15L3","","FMAG_TX_P11", "FMAG_TX_N11","", "FMAG_RX_P11", "FMAG_RX_N11",},
				/*Lane4*/	{LANE_BOTH,"H30LR_M15L4","","FMAG_TX_P20", "FMAG_TX_N20","", "FMAG_RX_P20", "FMAG_RX_N20",},
				/*Lane5*/	{LANE_BOTH,"H30LR_M15L5","","FMAG_TX_P21", "FMAG_TX_N21","", "FMAG_RX_P21", "FMAG_RX_N21",},
				/*Lane6*/	{LANE_BOTH,"H30LR_M15L6","","FMAG_TX_P22", "FMAG_TX_N22","", "FMAG_RX_P22", "FMAG_RX_N22",},
				/*Lane7*/	{LANE_BOTH,"H30LR_M15L7","","FMAG_TX_P23", "FMAG_TX_N23","", "FMAG_RX_P23", "FMAG_RX_N23",}
						}
					} 
		/*Macro16*/	{ 16 , { PLL0,4, HILINK_IP, H30_LR, 0x00A1, 0x00800, 0x009D, 0x000B, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M16L0","","FMAG_TX_P12", "FMAG_TX_N12","", "FMAG_RX_P12", "FMAG_RX_N12",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M16L1","","FMAG_TX_P13", "FMAG_TX_N13","", "FMAG_RX_P13", "FMAG_RX_N13",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M16L2","","FMAG_TX_P14", "FMAG_TX_N14","", "FMAG_RX_P14", "FMAG_RX_N14",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M16L3","","FMAG_TX_P15", "FMAG_TX_N15","", "FMAG_RX_P15", "FMAG_RX_N15",}
						}
					} 
		/*Macro17*/	{ 17 , { PLL0,4, HILINK_IP, H30_LR, 0x00A1, 0x00040, 0x009D, 0x0006, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M17L0","","FMAG_TX_P19", "FMAG_TX_N19","", "FMAG_RX_P19", "FMAG_RX_N19",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M17L1","","FMAG_TX_P18", "FMAG_TX_N18","", "FMAG_RX_P18", "FMAG_RX_N18",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M17L2","","FMAG_TX_P17", "FMAG_TX_N17","", "FMAG_RX_P17", "FMAG_RX_N17",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M17L3","","FMAG_TX_P16", "FMAG_TX_N16","", "FMAG_RX_P16", "FMAG_RX_N16",}
						}
					} 
		/*Macro18*/	{ 18 , { PLL0,4, HILINK_IP, H30_LR, 0x00A1, 0x00080, 0x009D, 0x0007, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M18L0","","FMAG_TX_P4", "FMAG_TX_N4","", "FMAG_RX_P4", "FMAG_RX_N4",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M18L1","","FMAG_TX_P5", "FMAG_TX_N5","", "FMAG_RX_P5", "FMAG_RX_N5",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M18L2","","FMAG_TX_P6", "FMAG_TX_N6","", "FMAG_RX_P6", "FMAG_RX_N6",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M18L3","","FMAG_TX_P7", "FMAG_TX_N7","", "FMAG_RX_P7", "FMAG_RX_N7",}
						}
					} 
		/*Macro19*/	{ 19 , { PLL0,4, HILINK_IP, H30_LR, 0x00A1, 0x00100, 0x009D, 0x0008, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M19L0","","FMAG_TX_P3", "FMAG_TX_N3","", "FMAG_RX_P3", "FMAG_RX_N3",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M19L1","","FMAG_TX_P2", "FMAG_TX_N2","", "FMAG_RX_P2", "FMAG_RX_N2",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M19L2","","FMAG_TX_P1", "FMAG_TX_N1","", "FMAG_RX_P1", "FMAG_RX_N1",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M19L3","","FMAG_TX_P0", "FMAG_TX_N0","", "FMAG_RX_P0", "FMAG_RX_N0",}
						}
					} 
		/*Macro2*/	{ 2 , { PLL0,8, HILINK_IP, H30_LR, 0x00A1, 0x04000, 0x009D, 0x000E, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M2L0","","LMAG_TX_P16", "LMAG_TX_N16","", "LMAG_RX_P16", "LMAG_RX_N16",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M2L1","","LMAG_TX_P17", "LMAG_TX_N17","", "LMAG_RX_P17", "LMAG_RX_N17",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M2L2","","LMAG_TX_P18", "LMAG_TX_N18","", "LMAG_RX_P18", "LMAG_RX_N18",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M2L3","","LMAG_TX_P19", "LMAG_TX_N19","", "LMAG_RX_P19", "LMAG_RX_N19",},
				/*Lane4*/	{LANE_BOTH,"H30LR_M2L4","","LMAG_TX_P20", "LMAG_TX_N20","", "LMAG_RX_P20", "LMAG_RX_N20",},
				/*Lane5*/	{LANE_BOTH,"H30LR_M2L5","","LMAG_TX_P21", "LMAG_TX_N21","", "LMAG_RX_P21", "LMAG_RX_N21",},
				/*Lane6*/	{LANE_BOTH,"H30LR_M2L6","","LMAG_TX_P22", "LMAG_TX_N22","", "LMAG_RX_P22", "LMAG_RX_N22",},
				/*Lane7*/	{LANE_BOTH,"H30LR_M2L7","","LMAG_TX_P23", "LMAG_TX_N23","", "LMAG_RX_P23", "LMAG_RX_N23",}
						}
					} 
		/*Macro3*/	{ 3 , { PLL0,8, HILINK_IP, H30_LR, 0x00A1, 0x08000, 0x009D, 0x000F, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M3L0","","LMAG_TX_P24", "LMAG_TX_N24","", "LMAG_RX_P24", "LMAG_RX_N24",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M3L1","","LMAG_TX_P25", "LMAG_TX_N25","", "LMAG_RX_P25", "LMAG_RX_N25",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M3L2","","LMAG_TX_P26", "LMAG_TX_N26","", "LMAG_RX_P26", "LMAG_RX_N26",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M3L3","","LMAG_TX_P27", "LMAG_TX_N27","", "LMAG_RX_P27", "LMAG_RX_N27",},
				/*Lane4*/	{LANE_BOTH,"H30LR_M3L4","","LMAG_TX_P28", "LMAG_TX_N28","", "LMAG_RX_P28", "LMAG_RX_N28",},
				/*Lane5*/	{LANE_BOTH,"H30LR_M3L5","","LMAG_TX_P29", "LMAG_TX_N29","", "LMAG_RX_P29", "LMAG_RX_N29",},
				/*Lane6*/	{LANE_BOTH,"H30LR_M3L6","","LMAG_TX_P30", "LMAG_TX_N30","", "LMAG_RX_P30", "LMAG_RX_N30",},
				/*Lane7*/	{LANE_BOTH,"H30LR_M3L7","","LMAG_TX_P31", "LMAG_TX_N31","", "LMAG_RX_P31", "LMAG_RX_N31",}
						}
					} 
		/*Macro4*/	{ 4 , { PLL0,4, HILINK_IP, H30_LR, 0x00A1, 0x10000, 0x009D, 0x0010, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M4L0","","LMAG_TX_P35", "LMAG_TX_N35","", "LMAG_RX_P35", "LMAG_RX_N35",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M4L1","","LMAG_TX_P34", "LMAG_TX_N34","", "LMAG_RX_P34", "LMAG_RX_N34",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M4L2","","LMAG_TX_P33", "LMAG_TX_N33","", "LMAG_RX_P33", "LMAG_RX_N33",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M4L3","","LMAG_TX_P32", "LMAG_TX_N32","", "LMAG_RX_P32", "LMAG_RX_N32",}
						}
					} 
		/*Macro5*/	{ 5 , { PLL0,4, HILINK_IP, H30_LR, 0x00A1, 0x20000, 0x009D, 0x0011, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M5L0","","LMAG_TX_P36", "LMAG_TX_N36","", "LMAG_RX_P36", "LMAG_RX_N36",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M5L1","","LMAG_TX_P37", "LMAG_TX_N37","", "LMAG_RX_P37", "LMAG_RX_N37",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M5L2","","LMAG_TX_P38", "LMAG_TX_N38","", "LMAG_RX_P38", "LMAG_RX_N38",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M5L3","","LMAG_TX_P39", "LMAG_TX_N39","", "LMAG_RX_P39", "LMAG_RX_N39",}
						}
					} 
		/*Macro6*/	{ 6 , { PLL0,4, HILINK_IP, H30_LR, 0x00A1, 0x40000, 0x009D, 0x0012, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M6L0","","LMAG_TX_P43", "LMAG_TX_N43","", "LMAG_RX_P43", "LMAG_RX_N43",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M6L1","","LMAG_TX_P42", "LMAG_TX_N42","", "LMAG_RX_P42", "LMAG_RX_N42",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M6L2","","LMAG_TX_P41", "LMAG_TX_N41","", "LMAG_RX_P41", "LMAG_RX_N41",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M6L3","","LMAG_TX_P40", "LMAG_TX_N40","", "LMAG_RX_P40", "LMAG_RX_N40",}
						}
					} 
		/*Macro7*/	{ 7 , { PLL0,4, HILINK_IP, H30_LR, 0x00A1, 0x80000, 0x009D, 0x0013, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M7L0","","LMAG_TX_P44", "LMAG_TX_N44","", "LMAG_RX_P44", "LMAG_RX_N44",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M7L1","","LMAG_TX_P45", "LMAG_TX_N45","", "LMAG_RX_P45", "LMAG_RX_N45",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M7L2","","LMAG_TX_P46", "LMAG_TX_N46","", "LMAG_RX_P46", "LMAG_RX_N46",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M7L3","","LMAG_TX_P47", "LMAG_TX_N47","", "LMAG_RX_P47", "LMAG_RX_N47",}
						}
					} 
		/*Macro8*/	{ 8 , { PLL0,4, HILINK_IP, H30_LR, 0x00A1, 0x00200, 0x009D, 0x0009, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M8L0","","ILA_TX_P3", "ILA_TX_N3","", "ILA_RX_P3", "ILA_RX_N3",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M8L1","","ILA_TX_P2", "ILA_TX_N2","", "ILA_RX_P2", "ILA_RX_N2",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M8L2","","ILA_TX_P1", "ILA_TX_N1","", "ILA_RX_P1", "ILA_RX_N1",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M8L3","","ILA_TX_P0", "ILA_TX_N0","", "ILA_RX_P0", "ILA_RX_N0",}
						}
					} 
		/*Macro9*/	{ 9 , { PLL0,4, HILINK_IP, H30_LR, 0x00A1, 0x00400, 0x009D, 0x000A, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose} },"PowerUpSeq" ,"PowerDnSeq" ,
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M9L0","","ILA_TX_P4", "ILA_TX_N4","", "ILA_RX_P4", "ILA_RX_N4",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M9L1","","ILA_TX_P5", "ILA_TX_N5","", "ILA_RX_P5", "ILA_RX_N5",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M9L2","","ILA_TX_P6", "ILA_TX_N6","", "ILA_RX_P6", "ILA_RX_N6",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M9L3","","ILA_TX_P7", "ILA_TX_N7","", "ILA_RX_P7", "ILA_RX_N7",}
						}
					} 
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

const string SSMacroIDList = "16,4";

extern string GlobalInitPattern;

//* HILINK_INFO[] access Macro Info
//* LANE_INFO[MacroID][] access Lane Info
HILINK_INFO_BEGIN();
		//redefine your IP type
		const static sT_HILINK_INFO _HILINK_INFO[] = {
		/*Macro0*/	{ 0 , { PLL0,8, H30_IP, H30_LR, 0, 0x00A1, 0x01000, 0x009D, 0x000C, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose}},"PowerUpSeq" ,"PowerDnSeq",
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M0L0","","LMAG_TX_P0", "LMAG_TX_N0","", "LMAG_RX_P0", "LMAG_RX_N0",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M0L1","","LMAG_TX_P1", "LMAG_TX_N1","", "LMAG_RX_P1", "LMAG_RX_N1",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M0L2","","LMAG_TX_P2", "LMAG_TX_N2","", "LMAG_RX_P2", "LMAG_RX_N2",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M0L3","","LMAG_TX_P3", "LMAG_TX_N3","", "LMAG_RX_P3", "LMAG_RX_N3",},
				/*Lane4*/	{LANE_BOTH,"H30LR_M0L4","","LMAG_TX_P4", "LMAG_TX_N4","", "LMAG_RX_P4", "LMAG_RX_N4",},
				/*Lane5*/	{LANE_BOTH,"H30LR_M0L5","","LMAG_TX_P5", "LMAG_TX_N5","", "LMAG_RX_P5", "LMAG_RX_N5",},
				/*Lane6*/	{LANE_BOTH,"H30LR_M0L6","","LMAG_TX_P6", "LMAG_TX_N6","", "LMAG_RX_P6", "LMAG_RX_N6",},
				/*Lane7*/	{LANE_BOTH,"H30LR_M0L7","","LMAG_TX_P7", "LMAG_TX_N7","", "LMAG_RX_P7", "LMAG_RX_N7",}
						}
					} 
		/*Macro1*/	{ 1 , { PLL0,8, H30_IP, H30_LR, 0, 0x00A1, 0x02000, 0x009D, 0x000D, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose}},"PowerUpSeq" ,"PowerDnSeq",
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M1L0","","LMAG_TX_P8", "LMAG_TX_N8","", "LMAG_RX_P8", "LMAG_RX_N8",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M1L1","","LMAG_TX_P9", "LMAG_TX_N9","", "LMAG_RX_P9", "LMAG_RX_N9",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M1L2","","LMAG_TX_P10", "LMAG_TX_N10","", "LMAG_RX_P10", "LMAG_RX_N10",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M1L3","","LMAG_TX_P11", "LMAG_TX_N11","", "LMAG_RX_P11", "LMAG_RX_N11",},
				/*Lane4*/	{LANE_BOTH,"H30LR_M1L4","","LMAG_TX_P12", "LMAG_TX_N12","", "LMAG_RX_P12", "LMAG_RX_N12",},
				/*Lane5*/	{LANE_BOTH,"H30LR_M1L5","","LMAG_TX_P13", "LMAG_TX_N13","", "LMAG_RX_P13", "LMAG_RX_N13",},
				/*Lane6*/	{LANE_BOTH,"H30LR_M1L6","","LMAG_TX_P14", "LMAG_TX_N14","", "LMAG_RX_P14", "LMAG_RX_N14",},
				/*Lane7*/	{LANE_BOTH,"H30LR_M1L7","","LMAG_TX_P15", "LMAG_TX_N15","", "LMAG_RX_P15", "LMAG_RX_N15",}
						}
					} 
		/*Macro12*/	{ 12 , { PLL0,8, H30_IP, H30_LR, 0, 0x00A1, 0x00004, 0x009D, 0x0002, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose}},"PowerUpSeq" ,"PowerDnSeq",
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M12L0","","FMAG_TX_P40", "FMAG_TX_N40","", "FMAG_RX_P40", "FMAG_RX_N40",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M12L1","","FMAG_TX_P41", "FMAG_TX_N41","", "FMAG_RX_P41", "FMAG_RX_N41",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M12L2","","FMAG_TX_P42", "FMAG_TX_N42","", "FMAG_RX_P42", "FMAG_RX_N42",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M12L3","","FMAG_TX_P43", "FMAG_TX_N43","", "FMAG_RX_P43", "FMAG_RX_N43",},
				/*Lane4*/	{LANE_BOTH,"H30LR_M12L4","","FMAG_TX_P44", "FMAG_TX_N44","", "FMAG_RX_P44", "FMAG_RX_N44",},
				/*Lane5*/	{LANE_BOTH,"H30LR_M12L5","","FMAG_TX_P45", "FMAG_TX_N45","", "FMAG_RX_P45", "FMAG_RX_N45",},
				/*Lane6*/	{LANE_BOTH,"H30LR_M12L6","","FMAG_TX_P46", "FMAG_TX_N46","", "FMAG_RX_P46", "FMAG_RX_N46",},
				/*Lane7*/	{LANE_BOTH,"H30LR_M12L7","","FMAG_TX_P47", "FMAG_TX_N47","", "FMAG_RX_P47", "FMAG_RX_N47",}
						}
					} 
		/*Macro13*/	{ 13 , { PLL0,8, H30_IP, H30_LR, 0, 0x00A1, 0x00008, 0x009D, 0x0003, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose}},"PowerUpSeq" ,"PowerDnSeq",
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M13L0","","FMAG_TX_P24", "FMAG_TX_N24","", "FMAG_RX_P24", "FMAG_RX_N24",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M13L1","","FMAG_TX_P25", "FMAG_TX_N25","", "FMAG_RX_P25", "FMAG_RX_N25",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M13L2","","FMAG_TX_P26", "FMAG_TX_N26","", "FMAG_RX_P26", "FMAG_RX_N26",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M13L3","","FMAG_TX_P27", "FMAG_TX_N27","", "FMAG_RX_P27", "FMAG_RX_N27",},
				/*Lane4*/	{LANE_BOTH,"H30LR_M13L4","","FMAG_TX_P28", "FMAG_TX_N28","", "FMAG_RX_P28", "FMAG_RX_N28",},
				/*Lane5*/	{LANE_BOTH,"H30LR_M13L5","","FMAG_TX_P29", "FMAG_TX_N29","", "FMAG_RX_P29", "FMAG_RX_N29",},
				/*Lane6*/	{LANE_BOTH,"H30LR_M13L6","","FMAG_TX_P30", "FMAG_TX_N30","", "FMAG_RX_P30", "FMAG_RX_N30",},
				/*Lane7*/	{LANE_BOTH,"H30LR_M13L7","","FMAG_TX_P31", "FMAG_TX_N31","", "FMAG_RX_P31", "FMAG_RX_N31",}
						}
					} 
		/*Macro14*/	{ 14 , { PLL0,8, H30_IP, H30_LR, 0, 0x00A1, 0x00010, 0x009D, 0x0004, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose}},"PowerUpSeq" ,"PowerDnSeq",
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M14L0","","FMAG_TX_P32", "FMAG_TX_N32","", "FMAG_RX_P32", "FMAG_RX_N32",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M14L1","","FMAG_TX_P33", "FMAG_TX_N33","", "FMAG_RX_P33", "FMAG_RX_N33",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M14L2","","FMAG_TX_P34", "FMAG_TX_N34","", "FMAG_RX_P34", "FMAG_RX_N34",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M14L3","","FMAG_TX_P35", "FMAG_TX_N35","", "FMAG_RX_P35", "FMAG_RX_N35",},
				/*Lane4*/	{LANE_BOTH,"H30LR_M14L4","","FMAG_TX_P36", "FMAG_TX_N36","", "FMAG_RX_P36", "FMAG_RX_N36",},
				/*Lane5*/	{LANE_BOTH,"H30LR_M14L5","","FMAG_TX_P37", "FMAG_TX_N37","", "FMAG_RX_P37", "FMAG_RX_N37",},
				/*Lane6*/	{LANE_BOTH,"H30LR_M14L6","","FMAG_TX_P38", "FMAG_TX_N38","", "FMAG_RX_P38", "FMAG_RX_N38",},
				/*Lane7*/	{LANE_BOTH,"H30LR_M14L7","","FMAG_TX_P39", "FMAG_TX_N39","", "FMAG_RX_P39", "FMAG_RX_N39",}
						}
					} 
		/*Macro15*/	{ 15 , { PLL0,8, H30_IP, H30_LR, 0, 0x00A1, 0x00020, 0x009D, 0x0005, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose}},"PowerUpSeq" ,"PowerDnSeq",
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M15L0","","FMAG_TX_P8", "FMAG_TX_N8","", "FMAG_RX_P8", "FMAG_RX_N8",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M15L1","","FMAG_TX_P9", "FMAG_TX_N9","", "FMAG_RX_P9", "FMAG_RX_N9",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M15L2","","FMAG_TX_P10", "FMAG_TX_N10","", "FMAG_RX_P10", "FMAG_RX_N10",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M15L3","","FMAG_TX_P11", "FMAG_TX_N11","", "FMAG_RX_P11", "FMAG_RX_N11",},
				/*Lane4*/	{LANE_BOTH,"H30LR_M15L4","","FMAG_TX_P20", "FMAG_TX_N20","", "FMAG_RX_P20", "FMAG_RX_N20",},
				/*Lane5*/	{LANE_BOTH,"H30LR_M15L5","","FMAG_TX_P21", "FMAG_TX_N21","", "FMAG_RX_P21", "FMAG_RX_N21",},
				/*Lane6*/	{LANE_BOTH,"H30LR_M15L6","","FMAG_TX_P22", "FMAG_TX_N22","", "FMAG_RX_P22", "FMAG_RX_N22",},
				/*Lane7*/	{LANE_BOTH,"H30LR_M15L7","","FMAG_TX_P23", "FMAG_TX_N23","", "FMAG_RX_P23", "FMAG_RX_N23",}
						}
					} 
		/*Macro16*/	{ 16 , { PLL0,4, H30_IP, H30_LR, 0, 0x00A1, 0x00800, 0x009D, 0x000B, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose}},"PowerUpSeq" ,"PowerDnSeq",
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M16L0","","FMAG_TX_P12", "FMAG_TX_N12","", "FMAG_RX_P12", "FMAG_RX_N12",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M16L1","","FMAG_TX_P13", "FMAG_TX_N13","", "FMAG_RX_P13", "FMAG_RX_N13",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M16L2","","FMAG_TX_P14", "FMAG_TX_N14","", "FMAG_RX_P14", "FMAG_RX_N14",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M16L3","","FMAG_TX_P15", "FMAG_TX_N15","", "FMAG_RX_P15", "FMAG_RX_N15",}
						}
					} 
		/*Macro17*/	{ 17 , { PLL0,4, H30_IP, H30_LR, 0, 0x00A1, 0x00040, 0x009D, 0x0006, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose}},"PowerUpSeq" ,"PowerDnSeq",
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M17L0","","FMAG_TX_P19", "FMAG_TX_N19","", "FMAG_RX_P19", "FMAG_RX_N19",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M17L1","","FMAG_TX_P18", "FMAG_TX_N18","", "FMAG_RX_P18", "FMAG_RX_N18",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M17L2","","FMAG_TX_P17", "FMAG_TX_N17","", "FMAG_RX_P17", "FMAG_RX_N17",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M17L3","","FMAG_TX_P16", "FMAG_TX_N16","", "FMAG_RX_P16", "FMAG_RX_N16",}
						}
					} 
		/*Macro18*/	{ 18 , { PLL0,4, H30_IP, H30_LR, 0, 0x00A1, 0x00080, 0x009D, 0x0007, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose}},"PowerUpSeq" ,"PowerDnSeq",
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M18L0","","FMAG_TX_P4", "FMAG_TX_N4","", "FMAG_RX_P4", "FMAG_RX_N4",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M18L1","","FMAG_TX_P5", "FMAG_TX_N5","", "FMAG_RX_P5", "FMAG_RX_N5",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M18L2","","FMAG_TX_P6", "FMAG_TX_N6","", "FMAG_RX_P6", "FMAG_RX_N6",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M18L3","","FMAG_TX_P7", "FMAG_TX_N7","", "FMAG_RX_P7", "FMAG_RX_N7",}
						}
					} 
		/*Macro19*/	{ 19 , { PLL0,4, H30_IP, H30_LR, 0, 0x00A1, 0x00100, 0x009D, 0x0008, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose}},"PowerUpSeq" ,"PowerDnSeq",
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M19L0","","FMAG_TX_P3", "FMAG_TX_N3","", "FMAG_RX_P3", "FMAG_RX_N3",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M19L1","","FMAG_TX_P2", "FMAG_TX_N2","", "FMAG_RX_P2", "FMAG_RX_N2",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M19L2","","FMAG_TX_P1", "FMAG_TX_N1","", "FMAG_RX_P1", "FMAG_RX_N1",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M19L3","","FMAG_TX_P0", "FMAG_TX_N0","", "FMAG_RX_P0", "FMAG_RX_N0",}
						}
					} 
		/*Macro2*/	{ 2 , { PLL0,8, H30_IP, H30_LR, 0, 0x00A1, 0x04000, 0x009D, 0x000E, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose}},"PowerUpSeq" ,"PowerDnSeq",
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M2L0","","LMAG_TX_P16", "LMAG_TX_N16","", "LMAG_RX_P16", "LMAG_RX_N16",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M2L1","","LMAG_TX_P17", "LMAG_TX_N17","", "LMAG_RX_P17", "LMAG_RX_N17",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M2L2","","LMAG_TX_P18", "LMAG_TX_N18","", "LMAG_RX_P18", "LMAG_RX_N18",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M2L3","","LMAG_TX_P19", "LMAG_TX_N19","", "LMAG_RX_P19", "LMAG_RX_N19",},
				/*Lane4*/	{LANE_BOTH,"H30LR_M2L4","","LMAG_TX_P20", "LMAG_TX_N20","", "LMAG_RX_P20", "LMAG_RX_N20",},
				/*Lane5*/	{LANE_BOTH,"H30LR_M2L5","","LMAG_TX_P21", "LMAG_TX_N21","", "LMAG_RX_P21", "LMAG_RX_N21",},
				/*Lane6*/	{LANE_BOTH,"H30LR_M2L6","","LMAG_TX_P22", "LMAG_TX_N22","", "LMAG_RX_P22", "LMAG_RX_N22",},
				/*Lane7*/	{LANE_BOTH,"H30LR_M2L7","","LMAG_TX_P23", "LMAG_TX_N23","", "LMAG_RX_P23", "LMAG_RX_N23",}
						}
					} 
		/*Macro3*/	{ 3 , { PLL0,8, H30_IP, H30_LR, 0, 0x00A1, 0x08000, 0x009D, 0x000F, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose}},"PowerUpSeq" ,"PowerDnSeq",
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M3L0","","LMAG_TX_P24", "LMAG_TX_N24","", "LMAG_RX_P24", "LMAG_RX_N24",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M3L1","","LMAG_TX_P25", "LMAG_TX_N25","", "LMAG_RX_P25", "LMAG_RX_N25",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M3L2","","LMAG_TX_P26", "LMAG_TX_N26","", "LMAG_RX_P26", "LMAG_RX_N26",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M3L3","","LMAG_TX_P27", "LMAG_TX_N27","", "LMAG_RX_P27", "LMAG_RX_N27",},
				/*Lane4*/	{LANE_BOTH,"H30LR_M3L4","","LMAG_TX_P28", "LMAG_TX_N28","", "LMAG_RX_P28", "LMAG_RX_N28",},
				/*Lane5*/	{LANE_BOTH,"H30LR_M3L5","","LMAG_TX_P29", "LMAG_TX_N29","", "LMAG_RX_P29", "LMAG_RX_N29",},
				/*Lane6*/	{LANE_BOTH,"H30LR_M3L6","","LMAG_TX_P30", "LMAG_TX_N30","", "LMAG_RX_P30", "LMAG_RX_N30",},
				/*Lane7*/	{LANE_BOTH,"H30LR_M3L7","","LMAG_TX_P31", "LMAG_TX_N31","", "LMAG_RX_P31", "LMAG_RX_N31",}
						}
					} 
		/*Macro4*/	{ 4 , { PLL0,4, H30_IP, H30_LR, 0, 0x00A1, 0x10000, 0x009D, 0x0010, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose}},"PowerUpSeq" ,"PowerDnSeq",
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M4L0","","LMAG_TX_P35", "LMAG_TX_N35","", "LMAG_RX_P35", "LMAG_RX_N35",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M4L1","","LMAG_TX_P34", "LMAG_TX_N34","", "LMAG_RX_P34", "LMAG_RX_N34",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M4L2","","LMAG_TX_P33", "LMAG_TX_N33","", "LMAG_RX_P33", "LMAG_RX_N33",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M4L3","","LMAG_TX_P32", "LMAG_TX_N32","", "LMAG_RX_P32", "LMAG_RX_N32",}
						}
					} 
		/*Macro5*/	{ 5 , { PLL0,4, H30_IP, H30_LR, 0, 0x00A1, 0x20000, 0x009D, 0x0011, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose}},"PowerUpSeq" ,"PowerDnSeq",
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M5L0","","LMAG_TX_P36", "LMAG_TX_N36","", "LMAG_RX_P36", "LMAG_RX_N36",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M5L1","","LMAG_TX_P37", "LMAG_TX_N37","", "LMAG_RX_P37", "LMAG_RX_N37",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M5L2","","LMAG_TX_P38", "LMAG_TX_N38","", "LMAG_RX_P38", "LMAG_RX_N38",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M5L3","","LMAG_TX_P39", "LMAG_TX_N39","", "LMAG_RX_P39", "LMAG_RX_N39",}
						}
					} 
		/*Macro6*/	{ 6 , { PLL0,4, H30_IP, H30_LR, 0, 0x00A1, 0x40000, 0x009D, 0x0012, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose}},"PowerUpSeq" ,"PowerDnSeq",
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M6L0","","LMAG_TX_P43", "LMAG_TX_N43","", "LMAG_RX_P43", "LMAG_RX_N43",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M6L1","","LMAG_TX_P42", "LMAG_TX_N42","", "LMAG_RX_P42", "LMAG_RX_N42",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M6L2","","LMAG_TX_P41", "LMAG_TX_N41","", "LMAG_RX_P41", "LMAG_RX_N41",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M6L3","","LMAG_TX_P40", "LMAG_TX_N40","", "LMAG_RX_P40", "LMAG_RX_N40",}
						}
					} 
		/*Macro7*/	{ 7 , { PLL0,4, H30_IP, H30_LR, 0, 0x00A1, 0x80000, 0x009D, 0x0013, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose}},"PowerUpSeq" ,"PowerDnSeq",
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M7L0","","LMAG_TX_P44", "LMAG_TX_N44","", "LMAG_RX_P44", "LMAG_RX_N44",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M7L1","","LMAG_TX_P45", "LMAG_TX_N45","", "LMAG_RX_P45", "LMAG_RX_N45",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M7L2","","LMAG_TX_P46", "LMAG_TX_N46","", "LMAG_RX_P46", "LMAG_RX_N46",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M7L3","","LMAG_TX_P47", "LMAG_TX_N47","", "LMAG_RX_P47", "LMAG_RX_N47",}
						}
					} 
		/*Macro8*/	{ 8 , { PLL0,4, H30_IP, H30_LR, 0, 0x00A1, 0x00200, 0x009D, 0x0009, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose}},"PowerUpSeq" ,"PowerDnSeq",
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M8L0","","ILA_TX_P3", "ILA_TX_N3","", "ILA_RX_P3", "ILA_RX_N3",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M8L1","","ILA_TX_P2", "ILA_TX_N2","", "ILA_RX_P2", "ILA_RX_N2",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M8L2","","ILA_TX_P1", "ILA_TX_N1","", "ILA_RX_P1", "ILA_RX_N1",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M8L3","","ILA_TX_P0", "ILA_TX_N0","", "ILA_RX_P0", "ILA_RX_N0",}
						}
					} 
		/*Macro9*/	{ 9 , { PLL0,4, H30_IP, H30_LR, 0, 0x00A1, 0x00400, 0x009D, 0x000A, 0x00A0 ,{DS_powerup_sequence},{DS_powerdown_sequence},{Datalog_EN},{RefclockChose},{life2digChose}},"PowerUpSeq" ,"PowerDnSeq",
						{
				/*Lane0*/	{LANE_BOTH,"H30LR_M9L0","","ILA_TX_P4", "ILA_TX_N4","", "ILA_RX_P4", "ILA_RX_N4",},
				/*Lane1*/	{LANE_BOTH,"H30LR_M9L1","","ILA_TX_P5", "ILA_TX_N5","", "ILA_RX_P5", "ILA_RX_N5",},
				/*Lane2*/	{LANE_BOTH,"H30LR_M9L2","","ILA_TX_P6", "ILA_TX_N6","", "ILA_RX_P6", "ILA_RX_N6",},
				/*Lane3*/	{LANE_BOTH,"H30LR_M9L3","","ILA_TX_P7", "ILA_TX_N7","", "ILA_RX_P7", "ILA_RX_N7",}
						}
					} 
		};
HILINK_INFO_END();
  #endif




/*************************************** CP/FT Program **************************************************/
const STRING	CP_FT_Program = "FT";

/*************************************** DEFAULT INIT VECTOR ********************************************/

/*************************************** DEFAULT Firmware  ********************************************/

const STRING    HILINK_FIRMWARE_LABEL_DEFAULT  = "HiLink30LRV101_Calib_ATE_SRAM_1.2.6_0131_1203.hex.bin_WRITE";

const STRING    HILINK_CAL_NOAPI_FIRMWARE_LABEL_DEFAULT  = "HiLink30LRV101_Calib_ATE_SRAM_1.2.6_0131_1203_noapi.hex.bin_WRITE";


const STRING    HILINK_ADPT_NOAPI_FIRMWARE_LABEL_DEFAULT  = "HiLink30LRV101_Ate_Adapt_SRAM_1.1.2_0315_1138_noapi.hex.bin_WRITE";

const STRING    HILINK_DPM_Bin  = "HiLink30V101_ABIST_Dpm_SRAM_1.0.9_0325_1137.hex.bin_WRITE";

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
//#define AUTO_HWPRBS
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





//
//const int JAM_COUNT = 6;
//const int DEFAULT_SPI_PORT_ID = 0;
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
