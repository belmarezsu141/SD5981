/*
 * FWABIST_ATB.h
 *
 *  Created on: Apr 13, 2017
 *      Author: zhenghe
 */

#ifndef FWABIST_ATB_H_
#define FWABIST_ATB_H_

using namespace std;
#include <HILINK_DRIVE/FWABIST_REGISTER_Base.h>


#define ATB_TABLE_COUNT 58
#define ATB_TABLE_Calculate_COUNT 20
class ATB_TABLE_DEFINE:public FWABIST_REGISTER_Base{
private:
	ATB_TABLE_DEFINE(){}
public:
	static ATB_TABLE_DEFINE& getInstance(){
		static ATB_TABLE_DEFINE inst;
		return inst;
	}

	uint map_DS_Addr(uint DS0_addr,uint LaneID){
		return DS0_addr+82*LaneID; //TODO: confirm address mapping of DS
	}

	uint get_FWABIST_TABLE_count(){return ATB_TABLE_COUNT;}
	uint get_FWABIST_Calculate_count(){return ATB_TABLE_Calculate_COUNT;}


	//Table 2-10
	const T_FWABIST_REG_INFO& get_FWABIST_TABLE_ITEM(uint idx){
		assert(idx<ATB_TABLE_COUNT);
		const static T_FWABIST_REG_INFO ATB_TABLE[]={
				{ HILINK_CS_FWABIST_REG, "PLL0_VREGPLL_VREGHALF", 0x1F6D0, 0x1F424, 540,0x1f426,460, 1 },
				{ HILINK_CS_FWABIST_REG, "PLL0_VREGDLF_VREGHALF", 0x1F6D2, 0x1F430, 540,0x1f432,460, 1 },
				{ HILINK_CS_FWABIST_REG, "PLL0_VREGVCODIV_VREGHALF", 0x1F6D4, 0x1F43C, 540,0x1f43e,460, 1 },
				{ HILINK_CS_FWABIST_REG, "PLL0_DLF_VREF_0P525_IO", 0x1F6D6, 0x1F448, 560,0x1f44a,440, 1 },
				{ HILINK_CS_FWABIST_REG, "PLL0_DLF_SAMPP_O", 0x1F6D8, 0x1F454, 900,0x1f456,100, 1 },
				{ HILINK_CS_FWABIST_REG, "PLL0_DLF_SAMPM_O", 0x1F6DA, 0x1F458, 900,0x1f45a,100, 1 },
				{ HILINK_CS_FWABIST_REG, "PLL0_LVCC_VCOCORE_ATB", 0x1F6DC, 0x1F45C, 1050,0x1f45e,880, 1 },
				{ HILINK_CS_FWABIST_REG, "PLL0_LVCC_VCOCORE_HALF_ADC", 0x1F6DE, 0x1F468, 575,0x1f46a,430, 1 },
				{ HILINK_CS_FWABIST_REG, "PLL1_VREGPLL_VREGHALF", 0x1F6E0, 0x1F474, 540,0x1f476,460, 1 },
				{ HILINK_CS_FWABIST_REG, "PLL1_VREGDLF_VREGHALF", 0x1F6E2, 0x1F480, 540,0x1f482,460, 1 },
				{ HILINK_CS_FWABIST_REG, "PLL1_VREGVCODIV_VREGHALF", 0x1F6E4, 0x1F48C, 540,0x1f48e,460, 1 },
				{ HILINK_CS_FWABIST_REG, "PLL1_DLF_VREF_0P525_IO", 0x1F6E6, 0x1F498, 560,0x1f49a,440, 1 },
				{ HILINK_CS_FWABIST_REG, "PLL1_DLF_SAMPP_O", 0x1F6E8, 0x1F4A4, 900,0x1f4a6,100, 1 },
				{ HILINK_CS_FWABIST_REG, "PLL1_DLF_SAMPM_O", 0x1F6EA, 0x1F4A8, 900,0x1f4aa,100, 1 },
				{ HILINK_CS_FWABIST_REG, "PLL1_LVCC_VCOCORE_ATB", 0x1F6EC, 0x1F4AC, 1050,0x1f4ae,880, 1 },
				{ HILINK_CS_FWABIST_REG, "PLL1_LVCC_VCOCORE_HALF_ADC", 0x1F6EE, 0x1F4B8, 575,0x1f4ba,430, 1 },
				{ HILINK_CS_FWABIST_REG, "COMP_VREF", 0x1F6F0, 0x1F4C8, 500,0x1f4ca,350, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_CTLE_LOAD_REPLICA_OFFSET_NEGATIVE", 0x1F6F2, 0x1F530, 900,0x1f532,650, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_CTLE_LOAD_REPLICA_OFFSET_POSITIVE", 0x1F6F4, 0x1F534, 900,0x1f536,650, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_CTLE_VREG_VOUT", 0x1F6F6, 0x1F538, 1100,0x1f53a,900, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_CTLE_EQ_STAGE1_OFFSET_POSITIVE", 0x1F6F8, 0x1F544, 900,0x1f546,650, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_CTLE_EQ_STAGE1_OFFSET_NEGATIVE", 0x1F6FA, 0x1F548, 900,0x1f54a,650, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_CTLE_GN_STAGE1_OFFSET_POSITIVE", 0x1F6FC, 0x1F54C, 900,0x1f54e,650, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_CTLE_GN_STAGE1_OFFSET_NEGATIVE", 0x1F6FE, 0x1F550, 900,0x1f552,650, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_CTLE_EQ_STAGE2_OFFSET_POSITIVE", 0x1F700, 0x1F554, 900,0x1f556,650, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_CTLE_EQ_STAGE2_OFFSET_NEGATIVE", 0x1F702, 0x1F558, 900,0x1f55a,650, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_CTLE_GN_STAGE2_OFFSET_POSITIVE", 0x1F704, 0x1F55C, 900,0x1f55e,650, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_CTLE_GN_STAGE2_OFFSET_NEGATIVE", 0x1F706, 0x1F560, 900,0x1f562,650, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_CTLE_EQ_STAGE3_OFFSET_POSITIVE", 0x1F708, 0x1F564, 900,0x1f566,650, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_CTLE_EQ_STAGE3_OFFSET_NEGATIVE", 0x1F70A, 0x1F568, 900,0x1f56a,650, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_CTLE_GN_STAGE3_OFFSET_POSITIVE", 0x1F70C, 0x1F56C, 900,0x1f56e,650, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_CTLE_GN_STAGE3_OFFSET_NEGATIVE", 0x1F70E, 0x1F570, 900,0x1f572,650, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_DFE_I_EVEN_PATH_SUMMER_OFFSET_POSITIVE", 0x1F710, 0x1F578, 950,0x1f57a,630, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_DFE_I_EVEN_PATH_SUMMER_OFFSET_NEGATIVE", 0x1F712, 0x1F57C, 950,0x1f57e,630, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_DFE_Q_EVEN_PATH_SUMMER_OFFSET_POSITIVE", 0x1F714, 0x1F580, 950,0x1f582,630, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_DFE_Q_EVEN_PATH_SUMMER_OFFSET_NEGATIVE", 0x1F716, 0x1F584, 950,0x1f586,630, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_DFE_I_ODD_PATH_SUMMER_OFFSET_POSITIVE", 0x1F718, 0x1F588, 950,0x1f58a,630, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_DFE_I_ODD_PATH_SUMMER_OFFSET_NEGATIVE", 0x1F71A, 0x1F58C, 950,0x1f58e,630, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_DFE_Q_ODD_PATH_SUMMER_OFFSET_POSITIVE", 0x1F71C, 0x1F590, 950,0x1f592,630, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_DFE_Q_ODD_PATH_SUMMER_OFFSET_NEGATIVE", 0x1F71E, 0x1F594, 950,0x1f596,630, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_CENTER_CHANNEL_POSITIVE_OUTPUT", 0x1F720, 0x1F5A0, 950,0x1f5a2,630, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_CENTER_CHANNEL_NEGATIVE_OUTPUT", 0x1F722, 0x1F5A4, 950,0x1f5a6,630, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_EDGE_CHANNEL_POSITIVE_OUTPUT", 0x1F724, 0x1F5A8, 950,0x1f5aa,630, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_EDGE_CHANNEL_NEGATIVE_OUTPUT", 0x1F726, 0x1F5AC, 950,0x1f5ae,630, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_MONITOR_CHANNEL_POSITIVE_OUTPUT", 0x1F728, 0x1F5B0, 950,0x1f5b2,630, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_MONITOR_CHANNEL_NEGATIVE_OUTPUT", 0x1F72A, 0x1F5B4, 950,0x1f5b6,630, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_VREF_STB_OUT", 0x1F72C, 0x1F5C4, 950,0x1f5c6,630, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_VREGCLK_VREG_2_3", 0x1F72E, 0x1F5D4, 607,0x1f5d6,557, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_VREGDATA_VREG_2_3", 0x1F730, 0x1F5E4, 687,0x1f5e6,615, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_SIGDET_COMP_OUTP", 0x1F732, 0x1F5E8, 1050,0x1f5ea,750, 1 },
				{ HILINK_DS_FWABIST_REG, "DSRX_SIGDET_COMP_OUTM", 0x1F734, 0x1F5EC, 1050,0x1f5ee,750, 1 },
				{ HILINK_DS_FWABIST_REG, "DSTX_TXVREG_PREDRV_2_3", 0x1F736, 0x1F660, 665,0x1f662,615, 1 },
				{ HILINK_DS_FWABIST_REG, "DSTX_TXVREG_DRV_2_3", 0x1F738, 0x1F664, 665,0x1f666,615, 1 },
				{ HILINK_DS_FWABIST_REG, "DSTX_TXDRV_SENSE_P_N", 0x1F73A, 0x1F684, 750,0x1f686,250, 1 },
				{ HILINK_DS_FWABIST_REG, "DSTX_TXDRV_SENSE_M_N", 0x1F73C, 0x1F688, 750,0x1f68a,250, 1 },
				{ HILINK_DS_FWABIST_REG, "DSCLK_VREG_VREG_2_3", 0x1F73E, 0x1F6A8, 680,0x1f6aa,610, 1 },
				{ HILINK_DS_FWABIST_REG, "DSMISC_DSCALCOMP_VREF_1", 0x1F740, 0x1F6C0, 660,0x1f6c2,620, 1 },
				{ HILINK_DS_FWABIST_REG, "DSMISC_DSCALCOMP_VREF_2", 0x1F742, 0x1F6C8, 500,0x1f6ca,350, 1 }
		};
		assert(sizeof(ATB_TABLE)/sizeof(T_FWABIST_REG_INFO)==ATB_TABLE_COUNT);
		return ATB_TABLE[idx];
	}

	//Table 2-11
	const T_FWABIST_CALCULATE_INFO& get_FWABIST_CALCULATE_ITEM(uint idx){
		assert(idx<ATB_TABLE_Calculate_COUNT);
		const static T_FWABIST_CALCULATE_INFO ATB_CALCULATOR_TABLE[]={
			{ HILINK_CS_FWABIST_REG, "k_PLL0_DLF_SAMPP_O+PLL0_DLF_SAMPM_O_k_/2", "PLL0_DLF_SAMPP_O", "PLL0_DLF_SAMPM_O", "", "", "Average",0x1F4BC, 560,0x1f4be,440, 2 },
			{ HILINK_CS_FWABIST_REG, "k_PLL1_DLF_SAMPP_O+PLL1_DLF_SAMPM_O_k_/2", "PLL1_DLF_SAMPP_O", "PLL1_DLF_SAMPM_O", "", "","Average",0x1F4C0, 560,0x1f4c2,440, 2 },
			{ HILINK_DS_FWABIST_REG, "CTLE_LOAD_REPLICA_OFFSET_DIFF", "DSRX_CTLE_LOAD_REPLICA_OFFSET_POSITIVE", "DSRX_CTLE_LOAD_REPLICA_OFFSET_NEGATIVE", "", "","Sub",0x1F5FC, 25,0x1f5fe,-25, 1 },
			{ HILINK_DS_FWABIST_REG, "CTLE_EQ_STAGE1_VCM", "DSRX_CTLE_EQ_STAGE1_OFFSET_POSITIVE", "DSRX_CTLE_EQ_STAGE1_OFFSET_NEGATIVE", "", "","Average",0x1F600, 900,0x1f602,650, 2 },
			{ HILINK_DS_FWABIST_REG, "CTLE_GN_STAGE1_VCM", "DSRX_CTLE_GN_STAGE1_OFFSET_POSITIVE", "DSRX_CTLE_GN_STAGE1_OFFSET_NEGATIVE", "", "","Average",0x1F604, 900,0x1f606,650, 2 },
			{ HILINK_DS_FWABIST_REG, "CTLE_EQ_STAGE1_OFFSET_DIFF", "DSRX_CTLE_EQ_STAGE1_OFFSET_POSITIVE", "DSRX_CTLE_EQ_STAGE1_OFFSET_NEGATIVE", "", "","Sub",0x1F608, 15,0x1f60a,-15, 1 },
			{ HILINK_DS_FWABIST_REG, "CTLE_GN_STAGE1_OFFSET_DIFF", "DSRX_CTLE_GN_STAGE1_OFFSET_POSITIVE", "DSRX_CTLE_GN_STAGE1_OFFSET_NEGATIVE", "", "","Sub",0x1F60C, 15,0x1f60e,-15, 1 },
			{ HILINK_DS_FWABIST_REG, "CTLE_EQ_STAGE2_OFFSET_DIFF", "DSRX_CTLE_EQ_STAGE2_OFFSET_POSITIVE", "DSRX_CTLE_EQ_STAGE2_OFFSET_NEGATIVE", "", "","Sub",0x1F610, 15,0x1f612,-15, 1 },
			{ HILINK_DS_FWABIST_REG, "CTLE_GN_STAGE2_OFFSET_DIFF", "DSRX_CTLE_GN_STAGE2_OFFSET_POSITIVE", "DSRX_CTLE_GN_STAGE2_OFFSET_NEGATIVE", "", "","Sub",0x1F614, 15,0x1f616,-15, 1 },
			{ HILINK_DS_FWABIST_REG, "CTLE_EQ_STAGE3_OFFSET_DIFF", "DSRX_CTLE_EQ_STAGE3_OFFSET_POSITIVE", "DSRX_CTLE_EQ_STAGE3_OFFSET_NEGATIVE", "", "","Sub",0x1F618, 15,0x1f61a,-15, 1 },
			{ HILINK_DS_FWABIST_REG, "CTLE_GN_STAGE3_OFFSET_DIFF", "DSRX_CTLE_GN_STAGE3_OFFSET_POSITIVE", "DSRX_CTLE_GN_STAGE3_OFFSET_NEGATIVE", "", "","Sub",0x1F61C, 15,0x1f61e,-15, 1 },
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_PATH_SUMMER_VCM", "DSRX_DFE_I_EVEN_PATH_SUMMER_OFFSET_POSITIVE", "DSRX_DFE_I_EVEN_PATH_SUMMER_OFFSET_NEGATIVE", "", "","Average",0x1F620, 955,0x1f622,680, 2 },
			{ HILINK_DS_FWABIST_REG, "DFE_I_EVEN_PATH_SUMMER_OFFSET_DIFF", "DSRX_DFE_I_EVEN_PATH_SUMMER_OFFSET_POSITIVE", "DSRX_DFE_I_EVEN_PATH_SUMMER_OFFSET_NEGATIVE", "", "","Sub",0x1F624, 15,0x1f626,-15, 1 },
			{ HILINK_DS_FWABIST_REG, "DFE_Q_EVEN_PATH_SUMMER_OFFSET_DIFF", "DSRX_DFE_Q_EVEN_PATH_SUMMER_OFFSET_POSITIVE", "DSRX_DFE_Q_EVEN_PATH_SUMMER_OFFSET_NEGATIVE", "", "","Sub",0x1F628, 15,0x1f62a,-15, 1 },
			{ HILINK_DS_FWABIST_REG, "DFE_I_ODD_PATH_SUMMER_OFFSET_DIFF", "DSRX_DFE_I_ODD_PATH_SUMMER_OFFSET_POSITIVE", "DSRX_DFE_I_ODD_PATH_SUMMER_OFFSET_NEGATIVE", "", "","Sub",0x1F62C, 15,0x1f62e,-15, 1 },
			{ HILINK_DS_FWABIST_REG, "DFE_Q_ODD_PATH_SUMMER_OFFSET_DIFF", "DSRX_DFE_Q_ODD_PATH_SUMMER_OFFSET_POSITIVE", "DSRX_DFE_Q_ODD_PATH_SUMMER_OFFSET_NEGATIVE", "", "","Sub",0x1F630, 15,0x1f632,-15, 1 },
			{ HILINK_DS_FWABIST_REG, "CENTER_CHANNEL_DIFF", "DSRX_CENTER_CHANNEL_POSITIVE_OUTPUT", "DSRX_CENTER_CHANNEL_NEGATIVE_OUTPUT", "", "","Sub",0x1F634, 15,0x1f636,-15, 1 },
			{ HILINK_DS_FWABIST_REG, "EDGE_CHANNEL_DIFF", "DSRX_EDGE_CHANNEL_POSITIVE_OUTPUT", "DSRX_EDGE_CHANNEL_NEGATIVE_OUTPUT", "", "","Sub",0x1F638, 15,0x1f63a,-15, 1 },
			{ HILINK_DS_FWABIST_REG, "MONITOR_CHANNEL_DIFF", "DSRX_MONITOR_CHANNEL_POSITIVE_OUTPUT", "DSRX_MONITOR_CHANNEL_NEGATIVE_OUTPUT", "", "","Sub",0x1F63C, 15,0x1f63e,-15, 1 },
			{ HILINK_DS_FWABIST_REG, "TXDRV_SENSE_DIFF", "DSTX_TXDRV_SENSE_P_N", "DSTX_TXDRV_SENSE_M_N", "", "","Sub",0x1F68C, 20,0x1f68e,-20, 1 }

		};
		assert(sizeof(ATB_CALCULATOR_TABLE)/sizeof(T_FWABIST_CALCULATE_INFO)==ATB_TABLE_Calculate_COUNT);
		return ATB_CALCULATOR_TABLE[idx];
	}



};



#endif /* FWABIST_ATB_H_ */
