/*
 * FWABIST_AdcStability.h
 *
 *  Created on: June 26, 2017
 *      Author: Shaoxue
 */

#ifndef FWABIST_AdcStability_H_
#define FWABIST_AdcStability_H_


#include <HILINK_DRIVE/FWABIST_REGISTER_Base.h>


#define AdcStability_TABLE_COUNT 62
#define AdcStability_TABLE_Calculate_COUNT 31
class AdcStability_TABLE_DEFINE:public FWABIST_REGISTER_Base{
private:
	AdcStability_TABLE_DEFINE(){}
public:
	static AdcStability_TABLE_DEFINE& getInstance(){
		static AdcStability_TABLE_DEFINE inst;
		return inst;
	}

	uint map_DS_Addr(uint DS0_addr,uint LaneID){
		return DS0_addr+260*LaneID; //TODO: confirm address mapping of DS
	}

	uint get_FWABIST_TABLE_count(){return AdcStability_TABLE_COUNT;}
	uint get_FWABIST_Calculate_count(){return AdcStability_TABLE_Calculate_COUNT;}


	//Table 2-10
	const T_FWABIST_REG_INFO& get_FWABIST_TABLE_ITEM(uint idx){
		assert(idx<AdcStability_TABLE_COUNT);
		const static T_FWABIST_REG_INFO AdcStability_TABLE[]={
			{HILINK_SS_FWABIST_REG,"COMPARATOR_VREF_0_k_max_hvcc_data_k",0x1F372,0x1F180,1024,0x1F182,0,1},
			{HILINK_SS_FWABIST_REG,"COMPARATOR_VREF_0_k_min_hvcc_data_k",0x1F374,0x1F180,1024,0x1F182,0,1},
			{HILINK_SS_FWABIST_REG,"COMPARATOR_VREF_3_k_max_hvcc_data_k",0x1F37C,0x1F18C,1024,0x1F18E,0,1},
			{HILINK_SS_FWABIST_REG,"COMPARATOR_VREF_3_k_min_hvcc_data_k",0x1F37E,0x1F18C,1024,0x1F18E,0,1},
			{HILINK_SS_FWABIST_REG,"COMPARATOR_VREF_5_k_max_hvcc_data_k",0x1F386,0x1F194,1024,0x1F196,0,1},
			{HILINK_SS_FWABIST_REG,"COMPARATOR_VREF_5_k_min_hvcc_data_k",0x1F388,0x1F194,1024,0x1F196,0,1},
			{HILINK_SS_FWABIST_REG,"hvcc/2_k_max_hvcc_data_k",0x1F390,0x1F198,526,0x1F19A,498,1},
			{HILINK_SS_FWABIST_REG,"hvcc/2_k_min_hvcc_data_k",0x1F392,0x1F198,526,0x1F19A,498,1},
			{HILINK_SS_FWABIST_REG,"BIAS_MASTER_HV_VREF_BG_k_max_hvcc_data_k",0x1F39A,0x1F1A0,1024,0x1F1A2,0,1},
			{HILINK_SS_FWABIST_REG,"BIAS_MASTER_HV_VREF_BG_k_min_hvcc_data_k",0x1F39C,0x1F1A0,1024,0x1F1A2,0,1},
			{HILINK_SS_FWABIST_REG,"COMPARATOR_VREF_0_k_max_bandgap_data_k",0x1F3D6,0x1F1A8,1024,0x1F1AA,0,1},
			{HILINK_SS_FWABIST_REG,"COMPARATOR_VREF_0_k_min_bandgap_data_k",0x1F3D8,0x1F1A8,1024,0x1F1AA,0,1},
			{HILINK_SS_FWABIST_REG,"COMPARATOR_VREF_3_k_max_bandgap_data_k",0x1F3E0,0x1F1B4,1024,0x1F1B6,0,1},
			{HILINK_SS_FWABIST_REG,"COMPARATOR_VREF_3_k_min_bandgap_data_k",0x1F3E2,0x1F1B4,1024,0x1F1B6,0,1},
			{HILINK_SS_FWABIST_REG,"COMPARATOR_VREF_5_k_max_bandgap_data_k",0x1F3EA,0x1F1BC,1024,0x1F1BE,0,1},
			{HILINK_SS_FWABIST_REG,"COMPARATOR_VREF_5_k_min_bandgap_data_k",0x1F3EC,0x1F1BC,1024,0x1F1BE,0,1},
			{HILINK_SS_FWABIST_REG,"hvcc/2_k_max_bandgap_data_k",0x1F3F4,0x1F1C0,1024,0x1F1C2,0,1},
			{HILINK_SS_FWABIST_REG,"hvcc/2_k_min_bandgap_data_k",0x1F3F6,0x1F1C0,1024,0x1F1C2,0,1},
			{HILINK_SS_FWABIST_REG,"BIAS_MASTER_HV_VREF_BG_k_max_bandgap_data_k",0x1F3FE,0x1F1C8,1024,0x1F1CA,1004,1},
			{HILINK_SS_FWABIST_REG,"BIAS_MASTER_HV_VREF_BG_k_min_bandgap_data_k",0x1F400,0x1F1C8,1024,0x1F1CA,1004,1},
			{HILINK_CS_FWABIST_REG,"VREGPLL_LBIAS_k_max_hvcc_data_k",0x1F43A,0x1F1D0,270,0x1F1D2,242,1},
			{HILINK_CS_FWABIST_REG,"VREGPLL_LBIAS_k_min_hvcc_data_k",0x1F43C,0x1F1D0,270,0x1F1D2,242,1},
			{HILINK_CS_FWABIST_REG,"LVCC_VCOCORE_ATB_k_max_hvcc_data_k",0x1F444,0x1F1D4,1024,0x1F1D6,0,1},
			{HILINK_CS_FWABIST_REG,"LVCC_VCOCORE_ATB_k_min_hvcc_data_k",0x1F446,0x1F1D4,1024,0x1F1D6,0,1},
			{HILINK_CS_FWABIST_REG,"COMP_VREF_0_k_max_hvcc_data_k",0x1F44E,0x1F1E0,1024,0x1F1E2,0,1},
			{HILINK_CS_FWABIST_REG,"COMP_VREF_0_k_min_hvcc_data_k",0x1F450,0x1F1E0,1024,0x1F1E2,0,1},
			{HILINK_CS_FWABIST_REG,"COMP_VREF_3_k_max_hvcc_data_k",0x1F458,0x1F1EC,1024,0x1F1EE,0,1},
			{HILINK_CS_FWABIST_REG,"COMP_VREF_3_k_min_hvcc_data_k",0x1F45A,0x1F1EC,1024,0x1F1EE,0,1},
			{HILINK_CS_FWABIST_REG,"COMP_VREF_5_k_max_hvcc_data_k",0x1F462,0x1F1F4,1024,0x1F1F6,0,1},
			{HILINK_CS_FWABIST_REG,"COMP_VREF_5_k_min_hvcc_data_k",0x1F464,0x1F1F4,1024,0x1F1F6,0,1},
			{HILINK_CS_FWABIST_REG,"VREGPLL_LBIAS_k_max_bandgap_data_k",0x1F48A,0x1F1D8,1024,0x1F1DA,0,1},
			{HILINK_CS_FWABIST_REG,"VREGPLL_LBIAS_k_min_bandgap_data_k",0x1F48C,0x1F1D8,1024,0x1F1DA,0,1},
			{HILINK_CS_FWABIST_REG,"LVCC_VCOCORE_ATB_k_max_bandgap_data_k",0x1F494,0x1F1DC,1024,0x1F1DE,0,1},
			{HILINK_CS_FWABIST_REG,"LVCC_VCOCORE_ATB_k_min_bandgap_data_k",0x1F496,0x1F1DC,1024,0x1F1DE,0,1},
			{HILINK_CS_FWABIST_REG,"COMP_VREF_0_k_max_bandgap_data_k",0x1F49E,0x1F1F8,1024,0x1F1FA,0,1},
			{HILINK_CS_FWABIST_REG,"COMP_VREF_0_k_min_bandgap_data_k",0x1F4A0,0x1F1F8,1024,0x1F1FA,0,1},
			{HILINK_CS_FWABIST_REG,"COMP_VREF_3_k_max_bandgap_data_k",0x1F4A8,0x1F204,1024,0x1F206,0,1},
			{HILINK_CS_FWABIST_REG,"COMP_VREF_3_k_min_bandgap_data_k",0x1F4AA,0x1F204,1024,0x1F206,0,1},
			{HILINK_CS_FWABIST_REG,"COMP_VREF_5_k_max_bandgap_data_k",0x1F4B2,0x1F20C,1024,0x1F20E,0,1},
			{HILINK_CS_FWABIST_REG,"COMP_VREF_5_k_min_bandgap_data_k",0x1F4B4,0x1F20C,1024,0x1F20E,0,1},
			{HILINK_DS_FWABIST_REG,"VREG_LBIAS_k_max_hvcc_data_k",0x1F4DA,0x1F2B8,270,0x1F2BA,242,1},
			{HILINK_DS_FWABIST_REG,"VREG_LBIAS_k_min_hvcc_data_k",0x1F4DC,0x1F2B8,270,0x1F2BA,242,1},
			{HILINK_DS_FWABIST_REG,"VREG_VMID_k_max_hvcc_data_k",0x1F4E4,0x1F2BC,526,0x1F2BE,498,1},
			{HILINK_DS_FWABIST_REG,"VREG_VMID_k_min_hvcc_data_k",0x1F4E6,0x1F2BC,526,0x1F2BE,498,1},
			{HILINK_DS_FWABIST_REG,"DSTOP_HVCC_k_max_hvcc_data_k",0x1F4EE,0x1F2CC,1024,0x1F2CE,1010,1},
			{HILINK_DS_FWABIST_REG,"DSTOP_HVCC_k_min_hvcc_data_k",0x1F4F0,0x1F2CC,1024,0x1F2CE,1010,1},
			{HILINK_DS_FWABIST_REG,"DSTOP_VSS_k_max_hvcc_data_k",0x1F4F8,0x1F2D4,1024,0x1F2D6,0,1},
			{HILINK_DS_FWABIST_REG,"DSTOP_VSS_k_min_hvcc_data_k",0x1F4FA,0x1F2D4,1024,0x1F2D6,0,1},
			{HILINK_DS_FWABIST_REG,"TXDRV_REF_M_k_max_bandgap_data_k",0x1F55C,0x1F2B4,1024,0x1F2B6,0,1},
			{HILINK_DS_FWABIST_REG,"TXDRV_REF_M_k_min_bandgap_data_k",0x1F55E,0x1F2B4,1024,0x1F2B6,0,1},
			{HILINK_DS_FWABIST_REG,"VREG_LBIAS_k_max_bandgap_data_k",0x1F566,0x1F2C0,1024,0x1F2C2,0,1},
			{HILINK_DS_FWABIST_REG,"VREG_LBIAS_k_min_bandgap_data_k",0x1F568,0x1F2C0,1024,0x1F2C2,0,1},
			{HILINK_DS_FWABIST_REG,"VREG_VMID_k_max_bandgap_data_k",0x1F570,0x1F2C4,1024,0x1F2C6,0,1},
			{HILINK_DS_FWABIST_REG,"VREG_VMID_k_min_bandgap_data_k",0x1F572,0x1F2C4,1024,0x1F2C6,0,1},
			{HILINK_DS_FWABIST_REG,"DSCALCOMP_VREF_2_k_max_bandgap_data_k",0x1F57A,0x1F2F0,1024,0x1F2F2,0,1},
			{HILINK_DS_FWABIST_REG,"DSCALCOMP_VREF_2_k_min_bandgap_data_k",0x1F57C,0x1F2F0,1024,0x1F2F2,0,1},
			{HILINK_DS_FWABIST_REG,"DSTOP_VSS_k_max_bandgap_data_k",0x1F584,0x1F2F4,1024,0x1F2F6,0,1},
			{HILINK_DS_FWABIST_REG,"DSTOP_VSS_k_min_bandgap_data_k",0x1F586,0x1F2F4,1024,0x1F2F6,0,1},
			{HILINK_DS_FWABIST_REG,"DSCALCOMP_VREF_5_k_max_bandgap_data_k",0x1F58E,0x1F300,1024,0x1F302,0,1},
			{HILINK_DS_FWABIST_REG,"DSCALCOMP_VREF_5_k_min_bandgap_data_k",0x1F590,0x1F300,1024,0x1F302,0,1},
			{HILINK_DS_FWABIST_REG,"DSCALCOMP_VREF_6_k_max_bandgap_data_k",0x1F598,0x1F304,1024,0x1F306,0,1},
			{HILINK_DS_FWABIST_REG,"DSCALCOMP_VREF_6_k_min_bandgap_data_k",0x1F59A,0x1F304,1024,0x1F306,0,1}
		};
		assert(sizeof(AdcStability_TABLE)/sizeof(T_FWABIST_REG_INFO)==AdcStability_TABLE_COUNT);
		return AdcStability_TABLE[idx];
	}

	//Table 2-11
	const T_FWABIST_CALCULATE_INFO& get_FWABIST_CALCULATE_ITEM(uint idx){
		assert(idx<AdcStability_TABLE_Calculate_COUNT);
		const static T_FWABIST_CALCULATE_INFO AdcStability_CALCULATOR_TABLE[]={
			{HILINK_SS_FWABIST_REG,"COMPARATOR_VREF_0_k_drift_hvcc_data_k","COMPARATOR_VREF_0_k_max_hvcc_data_k","COMPARATOR_VREF_0_k_min_hvcc_data_k","","","Sub",0x1F210,25,0x1F212,0,1},
			{HILINK_SS_FWABIST_REG,"COMPARATOR_VREF_3_k_drift_hvcc_data_k","COMPARATOR_VREF_3_k_max_hvcc_data_k","COMPARATOR_VREF_3_k_min_hvcc_data_k","","","Sub",0x1F21C,25,0x1F21E,0,1},
			{HILINK_SS_FWABIST_REG,"COMPARATOR_VREF_5_k_drift_hvcc_data_k","COMPARATOR_VREF_5_k_max_hvcc_data_k","COMPARATOR_VREF_5_k_min_hvcc_data_k","","","Sub",0x1F224,25,0x1F226,0,1},
			{HILINK_SS_FWABIST_REG,"hvcc/2_k_drift_hvcc_data_k","hvcc/2_k_max_hvcc_data_k","hvcc/2_k_min_hvcc_data_k","","","Sub",0x1F228,25,0x1F22A,0,1},
			{HILINK_SS_FWABIST_REG,"BIAS_MASTER_HV_VREF_BG_k_drift_hvcc_data_k","BIAS_MASTER_HV_VREF_BG_k_max_hvcc_data_k","BIAS_MASTER_HV_VREF_BG_k_min_hvcc_data_k","","","Sub",0x1F230,25,0x1F232,0,1},
			{HILINK_SS_FWABIST_REG,"COMPARATOR_VREF_0_k_drift_bandgap_data_k","COMPARATOR_VREF_0_k_max_bandgap_data_k","COMPARATOR_VREF_0_k_min_bandgap_data_k","","","Sub",0x1F238,25,0x1F23A,0,1},
			{HILINK_SS_FWABIST_REG,"COMPARATOR_VREF_3_k_drift_bandgap_data_k","COMPARATOR_VREF_3_k_max_bandgap_data_k","COMPARATOR_VREF_3_k_min_bandgap_data_k","","","Sub",0x1F244,25,0x1F246,0,1},
			{HILINK_SS_FWABIST_REG,"COMPARATOR_VREF_5_k_drift_bandgap_data_k","COMPARATOR_VREF_5_k_max_bandgap_data_k","COMPARATOR_VREF_5_k_min_bandgap_data_k","","","Sub",0x1F24C,25,0x1F24E,0,1},
			{HILINK_SS_FWABIST_REG,"hvcc/2_k_drift_bandgap_data_k","hvcc/2_k_max_bandgap_data_k","hvcc/2_k_min_bandgap_data_k","","","Sub",0x1F250,25,0x1F252,0,1},
			{HILINK_SS_FWABIST_REG,"BIAS_MASTER_HV_VREF_BG_k_drift_bandgap_data_k","BIAS_MASTER_HV_VREF_BG_k_max_bandgap_data_k","BIAS_MASTER_HV_VREF_BG_k_min_bandgap_data_k","","","Sub",0x1F258,25,0x1F25A,0,1},
			{HILINK_CS_FWABIST_REG,"VREGPLL_LBIAS_k_drift_hvcc_data_k","VREGPLL_LBIAS_k_max_hvcc_data_k","VREGPLL_LBIAS_k_min_hvcc_data_k","","","Sub",0x1F260,25,0x1F262,0,1},
			{HILINK_CS_FWABIST_REG,"LVCC_VCOCORE_ATB_k_drift_hvcc_data_k","LVCC_VCOCORE_ATB_k_max_hvcc_data_k","LVCC_VCOCORE_ATB_k_min_hvcc_data_k","","","Sub",0x1F264,25,0x1F266,0,1},
			{HILINK_CS_FWABIST_REG,"COMP_VREF_0_k_drift_hvcc_data_k","COMP_VREF_0_k_max_hvcc_data_k","COMP_VREF_0_k_min_hvcc_data_k","","","Sub",0x1F268,25,0x1F26A,0,1},
			{HILINK_CS_FWABIST_REG,"COMP_VREF_3_k_drift_hvcc_data_k","COMP_VREF_3_k_max_hvcc_data_k","COMP_VREF_3_k_min_hvcc_data_k","","","Sub",0x1F274,25,0x1F276,0,1},
			{HILINK_CS_FWABIST_REG,"COMP_VREF_5_k_drift_hvcc_data_k","COMP_VREF_5_k_max_hvcc_data_k","COMP_VREF_5_k_min_hvcc_data_k","","","Sub",0x1F27C,25,0x1F27E,0,1},
			{HILINK_CS_FWABIST_REG,"VREGPLL_LBIAS_k_drift_bandgap_data_k","VREGPLL_LBIAS_k_max_bandgap_data_k","VREGPLL_LBIAS_k_min_bandgap_data_k","","","Sub",0x1F280,25,0x1F282,0,1},
			{HILINK_CS_FWABIST_REG,"LVCC_VCOCORE_ATB_k_drift_bandgap_data_k","LVCC_VCOCORE_ATB_k_max_bandgap_data_k","LVCC_VCOCORE_ATB_k_min_bandgap_data_k","","","Sub",0x1F284,25,0x1F286,0,1},
			{HILINK_CS_FWABIST_REG,"COMP_VREF_0_k_drift_bandgap_data_k","COMP_VREF_0_k_max_bandgap_data_k","COMP_VREF_0_k_min_bandgap_data_k","","","Sub",0x1F288,25,0x1F28A,0,1},
			{HILINK_CS_FWABIST_REG,"COMP_VREF_3_k_drift_bandgap_data_k","COMP_VREF_3_k_max_bandgap_data_k","COMP_VREF_3_k_min_bandgap_data_k","","","Sub",0x1F294,25,0x1F296,0,1},
			{HILINK_CS_FWABIST_REG,"COMP_VREF_5_k_drift_bandgap_data_k","COMP_VREF_5_k_max_bandgap_data_k","COMP_VREF_5_k_min_bandgap_data_k","","","Sub",0x1F29C,25,0x1F29E,0,1},
			{HILINK_DS_FWABIST_REG,"VREG_LBIAS_k_drift_hvcc_data_k","VREG_LBIAS_k_max_hvcc_data_k","VREG_LBIAS_k_min_hvcc_data_k","","","Sub",0x1F314,25,0x1F316,0,1},
			{HILINK_DS_FWABIST_REG,"VREG_VMID_k_drift_hvcc_data_k","VREG_VMID_k_max_hvcc_data_k","VREG_VMID_k_min_hvcc_data_k","","","Sub",0x1F318,25,0x1F31A,0,1},
			{HILINK_DS_FWABIST_REG,"DSTOP_HVCC_k_drift_hvcc_data_k","DSTOP_HVCC_k_max_hvcc_data_k","DSTOP_HVCC_k_min_hvcc_data_k","","","Sub",0x1F320,25,0x1F322,0,1},
			{HILINK_DS_FWABIST_REG,"DSTOP_VSS_k_drift_hvcc_data_k","DSTOP_VSS_k_max_hvcc_data_k","DSTOP_VSS_k_min_hvcc_data_k","","","Sub",0x1F328,25,0x1F32A,0,1},
			{HILINK_DS_FWABIST_REG,"TXDRV_REF_M_k_drift_bandgap_data_k","TXDRV_REF_M_k_max_bandgap_data_k","TXDRV_REF_M_k_min_bandgap_data_k","","","Sub",0x1F344,25,0x1F346,0,1},
			{HILINK_DS_FWABIST_REG,"VREG_LBIAS_k_drift_bandgap_data_k","VREG_LBIAS_k_max_bandgap_data_k","VREG_LBIAS_k_min_bandgap_data_k","","","Sub",0x1F348,25,0x1F34A,0,1},
			{HILINK_DS_FWABIST_REG,"VREG_VMID_k_drift_bandgap_data_k","VREG_VMID_k_max_bandgap_data_k","VREG_VMID_k_min_bandgap_data_k","","","Sub",0x1F34C,25,0x1F34E,0,1},
			{HILINK_DS_FWABIST_REG,"DSCALCOMP_VREF_2_k_drift_bandgap_data_k","DSCALCOMP_VREF_2_k_max_bandgap_data_k","DSCALCOMP_VREF_2_k_min_bandgap_data_k","","","Sub",0x1F358,25,0x1F35A,0,1},
			{HILINK_DS_FWABIST_REG,"DSTOP_VSS_k_drift_bandgap_data_k","DSTOP_VSS_k_max_bandgap_data_k","DSTOP_VSS_k_min_bandgap_data_k","","","Sub",0x1F35C,25,0x1F35E,0,1},
			{HILINK_DS_FWABIST_REG,"DSCALCOMP_VREF_5_k_drift_bandgap_data_k","DSCALCOMP_VREF_5_k_max_bandgap_data_k","DSCALCOMP_VREF_5_k_min_bandgap_data_k","","","Sub",0x1F368,25,0x1F36A,0,1},
			{HILINK_DS_FWABIST_REG,"DSCALCOMP_VREF_6_k_drift_bandgap_data_k","DSCALCOMP_VREF_6_k_max_bandgap_data_k","DSCALCOMP_VREF_6_k_min_bandgap_data_k","","","Sub",0x1F36C,25,0x1F36E,0,1}
			
		};
		assert(sizeof(AdcStability_CALCULATOR_TABLE)/sizeof(T_FWABIST_CALCULATE_INFO)==AdcStability_TABLE_Calculate_COUNT);
		return AdcStability_CALCULATOR_TABLE[idx];
	}



};



#endif /* FWABIST_ATB_H_ */
