/*
 * FWABIST_ATB.h
 *
 *  Created on: Apr 13, 2017
 *      Author: zhenghe
 */

#ifndef FWABIST_VCOTuningRange_H_
#define FWABIST_VCOTuningRange_H_

#include <api.h>

#include <HILINK_DRIVE/FWABIST_REGISTER_Base.h>


#define VCOTuningRange_TABLE_COUNT 257
#define VCOTuningRange_TABLE_Calculate_COUNT 116
class VCOTuningRange_TABLE_DEFINE:public FWABIST_REGISTER_Base{
private:
	VCOTuningRange_TABLE_DEFINE(){}
public:
	static VCOTuningRange_TABLE_DEFINE& getInstance(){
		static VCOTuningRange_TABLE_DEFINE inst;
		return inst;
	}

	uint map_DS_Addr(uint DS0_addr,uint LaneID){
		return DS0_addr+82*LaneID; //TODO: confirm address mapping of DS
	}

	uint get_FWABIST_TABLE_count(){return VCOTuningRange_TABLE_COUNT;}
	uint get_FWABIST_Calculate_count(){return VCOTuningRange_TABLE_Calculate_COUNT;}

	void
	FWABIST_Registers_Map_Init(const MACRO_LANE_SEL& MacroLane_Sel,
								   MACRO_ARRAY_D& CS_REG_RESULT,
								   MACRO_ARRAY_MAP& MAP_CS_NODE_VALUE);

	//Table 2-10
	const T_FWABIST_REG_INFO& get_FWABIST_TABLE_ITEM(uint idx){
		assert(idx<VCOTuningRange_TABLE_COUNT);
		const static T_FWABIST_REG_INFO VCOTuningRange_TABLE[]={
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F0Q0_atb_vcocore",0x1D4F0,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F0Q0_force_down_freq",0x1D4F2,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F0Q0_force_center_freq",0x1D4F4,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F0Q0_force_up_freq",0x1D4F6,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F0Q0_atb_vcocore",0x1D4F8,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F0Q0_force_down_freq",0x1D4FA,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F0Q0_force_center_freq",0x1D4FC,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F0Q0_force_up_freq",0x1D4FE,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F0Q2_atb_vcocore",0x1D500,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F0Q2_force_down_freq",0x1D502,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F0Q2_force_center_freq",0x1D504,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F0Q2_force_up_freq",0x1D506,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F0Q2_atb_vcocore",0x1D508,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F0Q2_force_down_freq",0x1D50A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F0Q2_force_center_freq",0x1D50C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F0Q2_force_up_freq",0x1D50E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F1Q0_atb_vcocore",0x1D510,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F1Q0_force_down_freq",0x1D512,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F1Q0_force_center_freq",0x1D514,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F1Q0_force_up_freq",0x1D516,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F1Q0_atb_vcocore",0x1D518,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F1Q0_force_down_freq",0x1D51A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F1Q0_force_center_freq",0x1D51C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F1Q0_force_up_freq",0x1D51E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F1Q2_atb_vcocore",0x1D520,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F1Q2_force_down_freq",0x1D522,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F1Q2_force_center_freq",0x1D524,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F1Q2_force_up_freq",0x1D526,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F1Q2_atb_vcocore",0x1D528,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F1Q2_force_down_freq",0x1D52A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F1Q2_force_center_freq",0x1D52C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F1Q2_force_up_freq",0x1D52E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F30Q0_atb_vcocore",0x1D530,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F30Q0_force_down_freq",0x1D532,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F30Q0_force_center_freq",0x1D534,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F30Q0_force_up_freq",0x1D536,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F30Q0_atb_vcocore",0x1D538,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F30Q0_force_down_freq",0x1D53A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F30Q0_force_center_freq",0x1D53C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F30Q0_force_up_freq",0x1D53E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F30Q2_atb_vcocore",0x1D540,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F30Q2_force_down_freq",0x1D542,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F30Q2_force_center_freq",0x1D544,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F30Q2_force_up_freq",0x1D546,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F30Q2_atb_vcocore",0x1D548,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F30Q2_force_down_freq",0x1D54A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F30Q2_force_center_freq",0x1D54C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F30Q2_force_up_freq",0x1D54E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F31Q0_atb_vcocore",0x1D550,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F31Q0_force_down_freq",0x1D552,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F31Q0_force_center_freq",0x1D554,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F31Q0_force_up_freq",0x1D556,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F31Q0_atb_vcocore",0x1D558,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F31Q0_force_down_freq",0x1D55A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F31Q0_force_center_freq",0x1D55C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F31Q0_force_up_freq",0x1D55E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F31Q2_atb_vcocore",0x1D560,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F31Q2_force_down_freq",0x1D562,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F31Q2_force_center_freq",0x1D564,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B0F31Q2_force_up_freq",0x1D566,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F31Q2_atb_vcocore",0x1D568,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F31Q2_force_down_freq",0x1D56A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F31Q2_force_center_freq",0x1D56C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B0F31Q2_force_up_freq",0x1D56E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F0Q0_atb_vcocore",0x1D570,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F0Q0_force_down_freq",0x1D572,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F0Q0_force_center_freq",0x1D574,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F0Q0_force_up_freq",0x1D576,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F0Q0_atb_vcocore",0x1D578,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F0Q0_force_down_freq",0x1D57A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F0Q0_force_center_freq",0x1D57C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F0Q0_force_up_freq",0x1D57E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F0Q2_atb_vcocore",0x1D580,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F0Q2_force_down_freq",0x1D582,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F0Q2_force_center_freq",0x1D584,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F0Q2_force_up_freq",0x1D586,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F0Q2_atb_vcocore",0x1D588,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F0Q2_force_down_freq",0x1D58A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F0Q2_force_center_freq",0x1D58C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F0Q2_force_up_freq",0x1D58E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F1Q0_atb_vcocore",0x1D590,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F1Q0_force_down_freq",0x1D592,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F1Q0_force_center_freq",0x1D594,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F1Q0_force_up_freq",0x1D596,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F1Q0_atb_vcocore",0x1D598,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F1Q0_force_down_freq",0x1D59A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F1Q0_force_center_freq",0x1D59C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F1Q0_force_up_freq",0x1D59E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F1Q2_atb_vcocore",0x1D5A0,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F1Q2_force_down_freq",0x1D5A2,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F1Q2_force_center_freq",0x1D5A4,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F1Q2_force_up_freq",0x1D5A6,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F1Q2_atb_vcocore",0x1D5A8,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F1Q2_force_down_freq",0x1D5AA,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F1Q2_force_center_freq",0x1D5AC,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F1Q2_force_up_freq",0x1D5AE,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F30Q0_atb_vcocore",0x1D5B0,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F30Q0_force_down_freq",0x1D5B2,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F30Q0_force_center_freq",0x1D5B4,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F30Q0_force_up_freq",0x1D5B6,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F30Q0_atb_vcocore",0x1D5B8,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F30Q0_force_down_freq",0x1D5BA,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F30Q0_force_center_freq",0x1D5BC,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F30Q0_force_up_freq",0x1D5BE,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F30Q2_atb_vcocore",0x1D5C0,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F30Q2_force_down_freq",0x1D5C2,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F30Q2_force_center_freq",0x1D5C4,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F30Q2_force_up_freq",0x1D5C6,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F30Q2_atb_vcocore",0x1D5C8,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F30Q2_force_down_freq",0x1D5CA,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F30Q2_force_center_freq",0x1D5CC,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F30Q2_force_up_freq",0x1D5CE,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F31Q0_atb_vcocore",0x1D5D0,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F31Q0_force_down_freq",0x1D5D2,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F31Q0_force_center_freq",0x1D5D4,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F31Q0_force_up_freq",0x1D5D6,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F31Q0_atb_vcocore",0x1D5D8,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F31Q0_force_down_freq",0x1D5DA,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F31Q0_force_center_freq",0x1D5DC,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F31Q0_force_up_freq",0x1D5DE,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F31Q2_atb_vcocore",0x1D5E0,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F31Q2_force_down_freq",0x1D5E2,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F31Q2_force_center_freq",0x1D5E4,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B1F31Q2_force_up_freq",0x1D5E6,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F31Q2_atb_vcocore",0x1D5E8,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F31Q2_force_down_freq",0x1D5EA,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F31Q2_force_center_freq",0x1D5EC,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B1F31Q2_force_up_freq",0x1D5EE,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F0Q0_atb_vcocore",0x1D5F0,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F0Q0_force_down_freq",0x1D5F2,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F0Q0_force_center_freq",0x1D5F4,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F0Q0_force_up_freq",0x1D5F6,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F0Q0_atb_vcocore",0x1D5F8,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F0Q0_force_down_freq",0x1D5FA,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F0Q0_force_center_freq",0x1D5FC,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F0Q0_force_up_freq",0x1D5FE,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F0Q2_atb_vcocore",0x1D600,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F0Q2_force_down_freq",0x1D602,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F0Q2_force_center_freq",0x1D604,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F0Q2_force_up_freq",0x1D606,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F0Q2_atb_vcocore",0x1D608,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F0Q2_force_down_freq",0x1D60A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F0Q2_force_center_freq",0x1D60C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F0Q2_force_up_freq",0x1D60E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F1Q0_atb_vcocore",0x1D610,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F1Q0_force_down_freq",0x1D612,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F1Q0_force_center_freq",0x1D614,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F1Q0_force_up_freq",0x1D616,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F1Q0_atb_vcocore",0x1D618,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F1Q0_force_down_freq",0x1D61A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F1Q0_force_center_freq",0x1D61C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F1Q0_force_up_freq",0x1D61E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F1Q2_atb_vcocore",0x1D620,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F1Q2_force_down_freq",0x1D622,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F1Q2_force_center_freq",0x1D624,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F1Q2_force_up_freq",0x1D626,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F1Q2_atb_vcocore",0x1D628,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F1Q2_force_down_freq",0x1D62A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F1Q2_force_center_freq",0x1D62C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F1Q2_force_up_freq",0x1D62E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F30Q0_atb_vcocore",0x1D630,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F30Q0_force_down_freq",0x1D632,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F30Q0_force_center_freq",0x1D634,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F30Q0_force_up_freq",0x1D636,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F30Q0_atb_vcocore",0x1D638,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F30Q0_force_down_freq",0x1D63A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F30Q0_force_center_freq",0x1D63C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F30Q0_force_up_freq",0x1D63E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F30Q2_atb_vcocore",0x1D640,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F30Q2_force_down_freq",0x1D642,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F30Q2_force_center_freq",0x1D644,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F30Q2_force_up_freq",0x1D646,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F30Q2_atb_vcocore",0x1D648,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F30Q2_force_down_freq",0x1D64A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F30Q2_force_center_freq",0x1D64C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F30Q2_force_up_freq",0x1D64E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F31Q0_atb_vcocore",0x1D650,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F31Q0_force_down_freq",0x1D652,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F31Q0_force_center_freq",0x1D654,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F31Q0_force_up_freq",0x1D656,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F31Q0_atb_vcocore",0x1D658,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F31Q0_force_down_freq",0x1D65A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F31Q0_force_center_freq",0x1D65C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F31Q0_force_up_freq",0x1D65E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F31Q2_atb_vcocore",0x1D660,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F31Q2_force_down_freq",0x1D662,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F31Q2_force_center_freq",0x1D664,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B2F31Q2_force_up_freq",0x1D666,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F31Q2_atb_vcocore",0x1D668,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F31Q2_force_down_freq",0x1D66A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F31Q2_force_center_freq",0x1D66C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B2F31Q2_force_up_freq",0x1D66E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F0Q0_atb_vcocore",0x1D670,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F0Q0_force_down_freq",0x1D672,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F0Q0_force_center_freq",0x1D674,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F0Q0_force_up_freq",0x1D676,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F0Q0_atb_vcocore",0x1D678,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F0Q0_force_down_freq",0x1D67A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F0Q0_force_center_freq",0x1D67C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F0Q0_force_up_freq",0x1D67E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F0Q2_atb_vcocore",0x1D680,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F0Q2_force_down_freq",0x1D682,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F0Q2_force_center_freq",0x1D684,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F0Q2_force_up_freq",0x1D686,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F0Q2_atb_vcocore",0x1D688,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F0Q2_force_down_freq",0x1D68A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F0Q2_force_center_freq",0x1D68C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F0Q2_force_up_freq",0x1D68E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F1Q0_atb_vcocore",0x1D690,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F1Q0_force_down_freq",0x1D692,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F1Q0_force_center_freq",0x1D694,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F1Q0_force_up_freq",0x1D696,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F1Q0_atb_vcocore",0x1D698,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F1Q0_force_down_freq",0x1D69A,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F1Q0_force_center_freq",0x1D69C,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F1Q0_force_up_freq",0x1D69E,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F1Q2_atb_vcocore",0x1D6A0,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F1Q2_force_down_freq",0x1D6A2,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F1Q2_force_center_freq",0x1D6A4,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F1Q2_force_up_freq",0x1D6A6,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F1Q2_atb_vcocore",0x1D6A8,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F1Q2_force_down_freq",0x1D6AA,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F1Q2_force_center_freq",0x1D6AC,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F1Q2_force_up_freq",0x1D6AE,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F30Q0_atb_vcocore",0x1D6B0,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F30Q0_force_down_freq",0x1D6B2,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F30Q0_force_center_freq",0x1D6B4,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F30Q0_force_up_freq",0x1D6B6,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F30Q0_atb_vcocore",0x1D6B8,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F30Q0_force_down_freq",0x1D6BA,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F30Q0_force_center_freq",0x1D6BC,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F30Q0_force_up_freq",0x1D6BE,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F30Q2_atb_vcocore",0x1D6C0,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F30Q2_force_down_freq",0x1D6C2,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F30Q2_force_center_freq",0x1D6C4,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F30Q2_force_up_freq",0x1D6C6,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F30Q2_atb_vcocore",0x1D6C8,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F30Q2_force_down_freq",0x1D6CA,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F30Q2_force_center_freq",0x1D6CC,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F30Q2_force_up_freq",0x1D6CE,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F31Q0_atb_vcocore",0x1D6D0,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F31Q0_force_down_freq",0x1D6D2,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F31Q0_force_center_freq",0x1D6D4,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F31Q0_force_up_freq",0x1D6D6,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F31Q0_atb_vcocore",0x1D6D8,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F31Q0_force_down_freq",0x1D6DA,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F31Q0_force_center_freq",0x1D6DC,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F31Q0_force_up_freq",0x1D6DE,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F31Q2_atb_vcocore",0x1D6E0,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F31Q2_force_down_freq",0x1D6E2,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F31Q2_force_center_freq",0x1D6E4,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL0_B3F31Q2_force_up_freq",0x1D6E6,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F31Q2_atb_vcocore",0x1D6E8,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F31Q2_force_down_freq",0x1D6EA,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F31Q2_force_center_freq",0x1D6EC,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"Itank25_PLL1_B3F31Q2_force_up_freq",0x1D6EE,0,0,0,0,1},
			{HILINK_CS_FWABIST_REG,"TestResult",0x1FCF8,0,0,0,0,1}
		};
		assert(sizeof(VCOTuningRange_TABLE)/sizeof(T_FWABIST_REG_INFO)==VCOTuningRange_TABLE_COUNT);
		return VCOTuningRange_TABLE[idx];
	}

	//Table 2-11
	const T_FWABIST_CALCULATE_INFO& get_FWABIST_CALCULATE_ITEM(uint idx){
		assert(idx<VCOTuningRange_TABLE_Calculate_COUNT);
		const static T_FWABIST_CALCULATE_INFO VCOTuningRange_CALCULATOR_TABLE[]={
			{HILINK_CS_FWABIST_REG,"PLL0_B0F0Q0I25_Freqlength","Itank25_PLL0_B0F0Q0_force_up_freq","Itank25_PLL0_B0F0Q0_force_down_freq","","","Sub",0x1CE6E,3000,0x1CE70,550,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B0F0Q2I25_Freqlength","Itank25_PLL0_B0F0Q2_force_up_freq","Itank25_PLL0_B0F0Q2_force_down_freq","","","Sub",0x1CE72,3000,0x1CE74,545,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B0F1Q0I25_Freqlength","Itank25_PLL0_B0F1Q0_force_up_freq","Itank25_PLL0_B0F1Q0_force_down_freq","","","Sub",0x1CE76,3000,0x1CE78,542,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B0F1Q2I25_Freqlength","Itank25_PLL0_B0F1Q2_force_up_freq","Itank25_PLL0_B0F1Q2_force_down_freq","","","Sub",0x1CE7A,3000,0x1CE7C,533,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B0F30Q0I25_Freqlength","Itank25_PLL0_B0F30Q0_force_up_freq","Itank25_PLL0_B0F30Q0_force_down_freq","","","Sub",0x1CE7E,3000,0x1CE80,326,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B0F30Q2I25_Freqlength","Itank25_PLL0_B0F30Q2_force_up_freq","Itank25_PLL0_B0F30Q2_force_down_freq","","","Sub",0x1CE82,3000,0x1CE84,323,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B0F31Q0I25_Freqlength","Itank25_PLL0_B0F31Q0_force_up_freq","Itank25_PLL0_B0F31Q0_force_down_freq","","","Sub",0x1CE86,3000,0x1CE88,323,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B0F31Q2I25_Freqlength","Itank25_PLL0_B0F31Q2_force_up_freq","Itank25_PLL0_B0F31Q2_force_down_freq","","","Sub",0x1CE8A,3000,0x1CE8C,319,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B1F0Q0I25_Freqlength","Itank25_PLL0_B1F0Q0_force_up_freq","Itank25_PLL0_B1F0Q0_force_down_freq","","","Sub",0x1CE8E,3000,0x1CE90,457,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B1F0Q2I25_Freqlength","Itank25_PLL0_B1F0Q2_force_up_freq","Itank25_PLL0_B1F0Q2_force_down_freq","","","Sub",0x1CE92,3000,0x1CE94,458,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B1F1Q0I25_Freqlength","Itank25_PLL0_B1F1Q0_force_up_freq","Itank25_PLL0_B1F1Q0_force_down_freq","","","Sub",0x1CE96,3000,0x1CE98,454,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B1F1Q2I25_Freqlength","Itank25_PLL0_B1F1Q2_force_up_freq","Itank25_PLL0_B1F1Q2_force_down_freq","","","Sub",0x1CE9A,3000,0x1CE9C,446,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B1F30Q0I25_Freqlength","Itank25_PLL0_B1F30Q0_force_up_freq","Itank25_PLL0_B1F30Q0_force_down_freq","","","Sub",0x1CE9E,3000,0x1CEA0,313,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B1F30Q2I25_Freqlength","Itank25_PLL0_B1F30Q2_force_up_freq","Itank25_PLL0_B1F30Q2_force_down_freq","","","Sub",0x1CEA2,3000,0x1CEA4,309,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B1F31Q0I25_Freqlength","Itank25_PLL0_B1F31Q0_force_up_freq","Itank25_PLL0_B1F31Q0_force_down_freq","","","Sub",0x1CEA6,3000,0x1CEA8,310,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B1F31Q2I25_Freqlength","Itank25_PLL0_B1F31Q2_force_up_freq","Itank25_PLL0_B1F31Q2_force_down_freq","","","Sub",0x1CEAA,3000,0x1CEAC,310,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B2F0Q0I25_Freqlength","Itank25_PLL0_B2F0Q0_force_up_freq","Itank25_PLL0_B2F0Q0_force_down_freq","","","Sub",0x1CEAE,3000,0x1CEB0,421,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B2F0Q2I25_Freqlength","Itank25_PLL0_B2F0Q2_force_up_freq","Itank25_PLL0_B2F0Q2_force_down_freq","","","Sub",0x1CEB2,3000,0x1CEB4,417,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B2F1Q0I25_Freqlength","Itank25_PLL0_B2F1Q0_force_up_freq","Itank25_PLL0_B2F1Q0_force_down_freq","","","Sub",0x1CEB6,3000,0x1CEB8,418,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B2F1Q2I25_Freqlength","Itank25_PLL0_B2F1Q2_force_up_freq","Itank25_PLL0_B2F1Q2_force_down_freq","","","Sub",0x1CEBA,3000,0x1CEBC,414,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B2F30Q0I25_Freqlength","Itank25_PLL0_B2F30Q0_force_up_freq","Itank25_PLL0_B2F30Q0_force_down_freq","","","Sub",0x1CEBE,3000,0x1CEC0,306,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B2F30Q2I25_Freqlength","Itank25_PLL0_B2F30Q2_force_up_freq","Itank25_PLL0_B2F30Q2_force_down_freq","","","Sub",0x1CEC2,3000,0x1CEC4,302,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B2F31Q0I25_Freqlength","Itank25_PLL0_B2F31Q0_force_up_freq","Itank25_PLL0_B2F31Q0_force_down_freq","","","Sub",0x1CEC6,3000,0x1CEC8,302,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B2F31Q2I25_Freqlength","Itank25_PLL0_B2F31Q2_force_up_freq","Itank25_PLL0_B2F31Q2_force_down_freq","","","Sub",0x1CECA,3000,0x1CECC,298,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B3F0Q0I25_Freqlength","Itank25_PLL0_B3F0Q0_force_up_freq","Itank25_PLL0_B3F0Q0_force_down_freq","","","Sub",0x1CECE,3000,0x1CED0,316,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B3F0Q2I25_Freqlength","Itank25_PLL0_B3F0Q2_force_up_freq","Itank25_PLL0_B3F0Q2_force_down_freq","","","Sub",0x1CED2,3000,0x1CED4,317,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B3F1Q0I25_Freqlength","Itank25_PLL0_B3F1Q0_force_up_freq","Itank25_PLL0_B3F1Q0_force_down_freq","","","Sub",0x1CED6,3000,0x1CED8,313,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B3F1Q2I25_Freqlength","Itank25_PLL0_B3F1Q2_force_up_freq","Itank25_PLL0_B3F1Q2_force_down_freq","","","Sub",0x1CEDA,3000,0x1CEDC,313,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B3F30Q0I25_Freqlength","Itank25_PLL0_B3F30Q0_force_up_freq","Itank25_PLL0_B3F30Q0_force_down_freq","","","Sub",0x1CEDE,3000,0x1CEE0,243,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B3F30Q2I25_Freqlength","Itank25_PLL0_B3F30Q2_force_up_freq","Itank25_PLL0_B3F30Q2_force_down_freq","","","Sub",0x1CEE2,3000,0x1CEE4,239,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B3F31Q0I25_Freqlength","Itank25_PLL0_B3F31Q0_force_up_freq","Itank25_PLL0_B3F31Q0_force_down_freq","","","Sub",0x1CEE6,3000,0x1CEE8,243,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B3F31Q2I25_Freqlength","Itank25_PLL0_B3F31Q2_force_up_freq","Itank25_PLL0_B3F31Q2_force_down_freq","","","Sub",0x1CEEA,3000,0x1CEEC,239,1},
			{HILINK_CS_FWABIST_REG,"PLL0_I25B0__k_F0Q0->F0Q1_k","Itank25_PLL0_B0F0Q0_force_center_freq","Itank25_PLL0_B0F0Q2_force_center_freq","","","Sub",0x1CEEE,1150,0x1CEF0,0,1},
			{HILINK_CS_FWABIST_REG,"PLL0_I25B0__k_F0Q1->F1Q0_k","Itank25_PLL0_B0F0Q2_force_center_freq","Itank25_PLL0_B0F1Q0_force_center_freq","","","Sub",0x1CEF2,1100,0x1CEF4,0,1},//20211207
			{HILINK_CS_FWABIST_REG,"PLL0_I25B0__k_F1Q0->F1Q1_k","Itank25_PLL0_B0F1Q0_force_center_freq","Itank25_PLL0_B0F1Q2_force_center_freq","","","Sub",0x1CEF6,1119,0x1CEF8,0,1},
			{HILINK_CS_FWABIST_REG,"PLL0_I25B0__k_F30Q0->F30Q1_k","Itank25_PLL0_B0F30Q0_force_center_freq","Itank25_PLL0_B0F30Q2_force_center_freq","","","Sub",0x1CEFA,589,0x1CEFC,0,1},
			{HILINK_CS_FWABIST_REG,"PLL0_I25B0__k_F30Q1->F31Q0_k","Itank25_PLL0_B0F30Q2_force_center_freq","Itank25_PLL0_B0F31Q0_force_center_freq","","","Sub",0x1CEFE,578,0x1CF00,0,1},//20211207
			{HILINK_CS_FWABIST_REG,"PLL0_I25B0__k_F31Q0->F31Q1_k","Itank25_PLL0_B0F31Q0_force_center_freq","Itank25_PLL0_B0F31Q2_force_center_freq","","","Sub",0x1CF02,589,0x1CF04,0,1},
			{HILINK_CS_FWABIST_REG,"PLL0_I25B1__k_F0Q0->F0Q1_k","Itank25_PLL0_B1F0Q0_force_center_freq","Itank25_PLL0_B1F0Q2_force_center_freq","","","Sub",0x1CF06,589,0x1CF08,0,1},
			{HILINK_CS_FWABIST_REG,"PLL0_I25B1__k_F0Q1->F1Q0_k","Itank25_PLL0_B1F0Q2_force_center_freq","Itank25_PLL0_B1F1Q0_force_center_freq","","","Sub",0x1CF0A,578,0x1CF0C,0,1},//20211207
			{HILINK_CS_FWABIST_REG,"PLL0_I25B1__k_F1Q0->F1Q1_k","Itank25_PLL0_B1F1Q0_force_center_freq","Itank25_PLL0_B1F1Q2_force_center_freq","","","Sub",0x1CF0E,589,0x1CF10,0,1},
			{HILINK_CS_FWABIST_REG,"PLL0_I25B1__k_F30Q0->F30Q1_k","Itank25_PLL0_B1F30Q0_force_center_freq","Itank25_PLL0_B1F30Q2_force_center_freq","","","Sub",0x1CF12,424,0x1CF14,0,1},
			{HILINK_CS_FWABIST_REG,"PLL0_I25B1__k_F30Q1->F31Q0_k","Itank25_PLL0_B1F30Q2_force_center_freq","Itank25_PLL0_B1F31Q0_force_center_freq","","","Sub",0x1CF16,420,0x1CF18,0,1},//20211207
			{HILINK_CS_FWABIST_REG,"PLL0_I25B1__k_F31Q0->F31Q1_k","Itank25_PLL0_B1F31Q0_force_center_freq","Itank25_PLL0_B1F31Q2_force_center_freq","","","Sub",0x1CF1A,424,0x1CF1C,0,1},
			{HILINK_CS_FWABIST_REG,"PLL0_I25B2__k_F0Q0->F0Q1_k","Itank25_PLL0_B2F0Q0_force_center_freq","Itank25_PLL0_B2F0Q2_force_center_freq","","","Sub",0x1CF1E,512,0x1CF20,0,1},
			{HILINK_CS_FWABIST_REG,"PLL0_I25B2__k_F0Q1->F1Q0_k","Itank25_PLL0_B2F0Q2_force_center_freq","Itank25_PLL0_B2F1Q0_force_center_freq","","","Sub",0x1CF22,450,0x1CF24,0,1},//20211207
			{HILINK_CS_FWABIST_REG,"PLL0_I25B2__k_F1Q0->F1Q1_k","Itank25_PLL0_B2F1Q0_force_center_freq","Itank25_PLL0_B2F1Q2_force_center_freq","","","Sub",0x1CF26,512,0x1CF28,0,1},
			{HILINK_CS_FWABIST_REG,"PLL0_I25B2__k_F30Q0->F30Q1_k","Itank25_PLL0_B2F30Q0_force_center_freq","Itank25_PLL0_B2F30Q2_force_center_freq","","","Sub",0x1CF2A,391,0x1CF2C,0,1},
			{HILINK_CS_FWABIST_REG,"PLL0_I25B2__k_F30Q1->F31Q0_k","Itank25_PLL0_B2F30Q2_force_center_freq","Itank25_PLL0_B2F31Q0_force_center_freq","","","Sub",0x1CF2E,350,0x1CF30,0,1},//20211207
			{HILINK_CS_FWABIST_REG,"PLL0_I25B2__k_F31Q0->F31Q1_k","Itank25_PLL0_B2F31Q0_force_center_freq","Itank25_PLL0_B2F31Q2_force_center_freq","","","Sub",0x1CF32,391,0x1CF34,0,1},
			{HILINK_CS_FWABIST_REG,"PLL0_I25B3__k_F0Q0->F0Q1_k","Itank25_PLL0_B3F0Q0_force_center_freq","Itank25_PLL0_B3F0Q2_force_center_freq","","","Sub",0x1CF36,380,0x1CF38,0,1},
			{HILINK_CS_FWABIST_REG,"PLL0_I25B3__k_F0Q1->F1Q0_k","Itank25_PLL0_B3F0Q2_force_center_freq","Itank25_PLL0_B3F1Q0_force_center_freq","","","Sub",0x1CF3A,370,0x1CF3C,0,1},//20211207
			{HILINK_CS_FWABIST_REG,"PLL0_I25B3__k_F1Q0->F1Q1_k","Itank25_PLL0_B3F1Q0_force_center_freq","Itank25_PLL0_B3F1Q2_force_center_freq","","","Sub",0x1CF3E,380,0x1CF40,0,1},
			{HILINK_CS_FWABIST_REG,"PLL0_I25B3__k_F30Q0->F30Q1_k","Itank25_PLL0_B3F30Q0_force_center_freq","Itank25_PLL0_B3F30Q2_force_center_freq","","","Sub",0x1CF42,303,0x1CF44,0,1},
			{HILINK_CS_FWABIST_REG,"PLL0_I25B3__k_F30Q1->F31Q0_k","Itank25_PLL0_B3F30Q2_force_center_freq","Itank25_PLL0_B3F31Q0_force_center_freq","","","Sub",0x1CF46,295,0x1CF48,0,1},//20211207
			{HILINK_CS_FWABIST_REG,"PLL0_I25B3__k_F31Q0->F31Q1_k","Itank25_PLL0_B3F31Q0_force_center_freq","Itank25_PLL0_B3F31Q2_force_center_freq","","","Sub",0x1CF4A,303,0x1CF4C,0,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B0F0Q0I25_Freqlength","Itank25_PLL1_B0F0Q0_force_up_freq","Itank25_PLL1_B0F0Q0_force_down_freq","","","Sub",0x1CF4E,3000,0x1CF50,519,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B0F0Q2I25_Freqlength","Itank25_PLL1_B0F0Q2_force_up_freq","Itank25_PLL1_B0F0Q2_force_down_freq","","","Sub",0x1CF52,3000,0x1CF54,515,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B0F1Q0I25_Freqlength","Itank25_PLL1_B0F1Q0_force_up_freq","Itank25_PLL1_B0F1Q0_force_down_freq","","","Sub",0x1CF56,3000,0x1CF58,512,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B0F1Q2I25_Freqlength","Itank25_PLL1_B0F1Q2_force_up_freq","Itank25_PLL1_B0F1Q2_force_down_freq","","","Sub",0x1CF5A,3000,0x1CF5C,503,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B0F30Q0I25_Freqlength","Itank25_PLL1_B0F30Q0_force_up_freq","Itank25_PLL1_B0F30Q0_force_down_freq","","","Sub",0x1CF5E,3000,0x1CF60,307,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B0F30Q2I25_Freqlength","Itank25_PLL1_B0F30Q2_force_up_freq","Itank25_PLL1_B0F30Q2_force_down_freq","","","Sub",0x1CF62,3000,0x1CF64,304,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B0F31Q0I25_Freqlength","Itank25_PLL1_B0F31Q0_force_up_freq","Itank25_PLL1_B0F31Q0_force_down_freq","","","Sub",0x1CF66,3000,0x1CF68,304,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B0F31Q2I25_Freqlength","Itank25_PLL1_B0F31Q2_force_up_freq","Itank25_PLL1_B0F31Q2_force_down_freq","","","Sub",0x1CF6A,3000,0x1CF6C,305,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B1F0Q0I25_Freqlength","Itank25_PLL1_B1F0Q0_force_up_freq","Itank25_PLL1_B1F0Q0_force_down_freq","","","Sub",0x1CF6E,3000,0x1CF70,435,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B1F0Q2I25_Freqlength","Itank25_PLL1_B1F0Q2_force_up_freq","Itank25_PLL1_B1F0Q2_force_down_freq","","","Sub",0x1CF72,3000,0x1CF74,431,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B1F1Q0I25_Freqlength","Itank25_PLL1_B1F1Q0_force_up_freq","Itank25_PLL1_B1F1Q0_force_down_freq","","","Sub",0x1CF76,3000,0x1CF78,427,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B1F1Q2I25_Freqlength","Itank25_PLL1_B1F1Q2_force_up_freq","Itank25_PLL1_B1F1Q2_force_down_freq","","","Sub",0x1CF7A,3000,0x1CF7C,424,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B1F30Q0I25_Freqlength","Itank25_PLL1_B1F30Q0_force_up_freq","Itank25_PLL1_B1F30Q0_force_down_freq","","","Sub",0x1CF7E,3000,0x1CF80,298,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B1F30Q2I25_Freqlength","Itank25_PLL1_B1F30Q2_force_up_freq","Itank25_PLL1_B1F30Q2_force_down_freq","","","Sub",0x1CF82,3000,0x1CF84,294,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B1F31Q0I25_Freqlength","Itank25_PLL1_B1F31Q0_force_up_freq","Itank25_PLL1_B1F31Q0_force_down_freq","","","Sub",0x1CF86,3000,0x1CF88,294,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B1F31Q2I25_Freqlength","Itank25_PLL1_B1F31Q2_force_up_freq","Itank25_PLL1_B1F31Q2_force_down_freq","","","Sub",0x1CF8A,3000,0x1CF8C,295,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B2F0Q0I25_Freqlength","Itank25_PLL1_B2F0Q0_force_up_freq","Itank25_PLL1_B2F0Q0_force_down_freq","","","Sub",0x1CF8E,3000,0x1CF90,402,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B2F0Q2I25_Freqlength","Itank25_PLL1_B2F0Q2_force_up_freq","Itank25_PLL1_B2F0Q2_force_down_freq","","","Sub",0x1CF92,3000,0x1CF94,398,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B2F1Q0I25_Freqlength","Itank25_PLL1_B2F1Q0_force_up_freq","Itank25_PLL1_B2F1Q0_force_down_freq","","","Sub",0x1CF96,3000,0x1CF98,395,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B2F1Q2I25_Freqlength","Itank25_PLL1_B2F1Q2_force_up_freq","Itank25_PLL1_B2F1Q2_force_down_freq","","","Sub",0x1CF9A,3000,0x1CF9C,395,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B2F30Q0I25_Freqlength","Itank25_PLL1_B2F30Q0_force_up_freq","Itank25_PLL1_B2F30Q0_force_down_freq","","","Sub",0x1CF9E,3000,0x1CFA0,290,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B2F30Q2I25_Freqlength","Itank25_PLL1_B2F30Q2_force_up_freq","Itank25_PLL1_B2F30Q2_force_down_freq","","","Sub",0x1CFA2,3000,0x1CFA4,291,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B2F31Q0I25_Freqlength","Itank25_PLL1_B2F31Q0_force_up_freq","Itank25_PLL1_B2F31Q0_force_down_freq","","","Sub",0x1CFA6,3000,0x1CFA8,291,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B2F31Q2I25_Freqlength","Itank25_PLL1_B2F31Q2_force_up_freq","Itank25_PLL1_B2F31Q2_force_down_freq","","","Sub",0x1CFAA,3000,0x1CFAC,287,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B3F0Q0I25_Freqlength","Itank25_PLL1_B3F0Q0_force_up_freq","Itank25_PLL1_B3F0Q0_force_down_freq","","","Sub",0x1CFAE,3000,0x1CFB0,301,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B3F0Q2I25_Freqlength","Itank25_PLL1_B3F0Q2_force_up_freq","Itank25_PLL1_B3F0Q2_force_down_freq","","","Sub",0x1CFB2,3000,0x1CFB4,301,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B3F1Q0I25_Freqlength","Itank25_PLL1_B3F1Q0_force_up_freq","Itank25_PLL1_B3F1Q0_force_down_freq","","","Sub",0x1CFB6,3000,0x1CFB8,297,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B3F1Q2I25_Freqlength","Itank25_PLL1_B3F1Q2_force_up_freq","Itank25_PLL1_B3F1Q2_force_down_freq","","","Sub",0x1CFBA,3000,0x1CFBC,298,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B3F30Q0I25_Freqlength","Itank25_PLL1_B3F30Q0_force_up_freq","Itank25_PLL1_B3F30Q0_force_down_freq","","","Sub",0x1CFBE,3000,0x1CFC0,236,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B3F30Q2I25_Freqlength","Itank25_PLL1_B3F30Q2_force_up_freq","Itank25_PLL1_B3F30Q2_force_down_freq","","","Sub",0x1CFC2,3000,0x1CFC4,231,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B3F31Q0I25_Freqlength","Itank25_PLL1_B3F31Q0_force_up_freq","Itank25_PLL1_B3F31Q0_force_down_freq","","","Sub",0x1CFC6,3000,0x1CFC8,232,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B3F31Q2I25_Freqlength","Itank25_PLL1_B3F31Q2_force_up_freq","Itank25_PLL1_B3F31Q2_force_down_freq","","","Sub",0x1CFCA,3000,0x1CFCC,228,1},
			{HILINK_CS_FWABIST_REG,"PLL1_I25B0__k_F0Q0->F0Q1_k","Itank25_PLL1_B0F0Q0_force_center_freq","Itank25_PLL1_B0F0Q2_force_center_freq","","","Sub",0x1CFCE,1129,0x1CFD0,0,1},
			{HILINK_CS_FWABIST_REG,"PLL1_I25B0__k_F0Q1->F1Q0_k","Itank25_PLL1_B0F0Q2_force_center_freq","Itank25_PLL1_B0F1Q0_force_center_freq","","","Sub",0x1CFD2,1100,0x1CFD4,0,1},//20211207
			{HILINK_CS_FWABIST_REG,"PLL1_I25B0__k_F1Q0->F1Q1_k","Itank25_PLL1_B0F1Q0_force_center_freq","Itank25_PLL1_B0F1Q2_force_center_freq","","","Sub",0x1CFD6,1068,0x1CFD8,0,1},
			{HILINK_CS_FWABIST_REG,"PLL1_I25B0__k_F30Q0->F30Q1_k","Itank25_PLL1_B0F30Q0_force_center_freq","Itank25_PLL1_B0F30Q2_force_center_freq","","","Sub",0x1CFDA,589,0x1CFDC,0,1},
			{HILINK_CS_FWABIST_REG,"PLL1_I25B0__k_F30Q1->F31Q0_k","Itank25_PLL1_B0F30Q2_force_center_freq","Itank25_PLL1_B0F31Q0_force_center_freq","","","Sub",0x1CFDE,550,0x1CFE0,0,1},//20211207
			{HILINK_CS_FWABIST_REG,"PLL1_I25B0__k_F31Q0->F31Q1_k","Itank25_PLL1_B0F31Q0_force_center_freq","Itank25_PLL1_B0F31Q2_force_center_freq","","","Sub",0x1CFE2,589,0x1CFE4,0,1},
			{HILINK_CS_FWABIST_REG,"PLL1_I25B1__k_F0Q0->F0Q1_k","Itank25_PLL1_B1F0Q0_force_center_freq","Itank25_PLL1_B1F0Q2_force_center_freq","","","Sub",0x1CFE6,589,0x1CFE8,0,1},
			{HILINK_CS_FWABIST_REG,"PLL1_I25B1__k_F0Q1->F1Q0_k","Itank25_PLL1_B1F0Q2_force_center_freq","Itank25_PLL1_B1F1Q0_force_center_freq","","","Sub",0x1CFEA,600,0x1CFEC,0,1},//20211207
			{HILINK_CS_FWABIST_REG,"PLL1_I25B1__k_F1Q0->F1Q1_k","Itank25_PLL1_B1F1Q0_force_center_freq","Itank25_PLL1_B1F1Q2_force_center_freq","","","Sub",0x1CFEE,589,0x1CFF0,0,1},
			{HILINK_CS_FWABIST_REG,"PLL1_I25B1__k_F30Q0->F30Q1_k","Itank25_PLL1_B1F30Q0_force_center_freq","Itank25_PLL1_B1F30Q2_force_center_freq","","","Sub",0x1CFF2,424,0x1CFF4,0,1},
			{HILINK_CS_FWABIST_REG,"PLL1_I25B1__k_F30Q1->F31Q0_k","Itank25_PLL1_B1F30Q2_force_center_freq","Itank25_PLL1_B1F31Q0_force_center_freq","","","Sub",0x1CFF6,430,0x1CFF8,0,1},//20211207
			{HILINK_CS_FWABIST_REG,"PLL1_I25B1__k_F31Q0->F31Q1_k","Itank25_PLL1_B1F31Q0_force_center_freq","Itank25_PLL1_B1F31Q2_force_center_freq","","","Sub",0x1CFFA,424,0x1CFFC,0,1},
			{HILINK_CS_FWABIST_REG,"PLL1_I25B2__k_F0Q0->F0Q1_k","Itank25_PLL1_B2F0Q0_force_center_freq","Itank25_PLL1_B2F0Q2_force_center_freq","","","Sub",0x1CFFE,512,0x1D000,0,1},
			{HILINK_CS_FWABIST_REG,"PLL1_I25B2__k_F0Q1->F1Q0_k","Itank25_PLL1_B2F0Q2_force_center_freq","Itank25_PLL1_B2F1Q0_force_center_freq","","","Sub",0x1D002,450,0x1D004,0,1},//20211207
			{HILINK_CS_FWABIST_REG,"PLL1_I25B2__k_F1Q0->F1Q1_k","Itank25_PLL1_B2F1Q0_force_center_freq","Itank25_PLL1_B2F1Q2_force_center_freq","","","Sub",0x1D006,457,0x1D008,0,1},
			{HILINK_CS_FWABIST_REG,"PLL1_I25B2__k_F30Q0->F30Q1_k","Itank25_PLL1_B2F30Q0_force_center_freq","Itank25_PLL1_B2F30Q2_force_center_freq","","","Sub",0x1D00A,350,0x1D00C,0,1},
			{HILINK_CS_FWABIST_REG,"PLL1_I25B2__k_F30Q1->F31Q0_k","Itank25_PLL1_B2F30Q2_force_center_freq","Itank25_PLL1_B2F31Q0_force_center_freq","","","Sub",0x1D00E,350,0x1D010,0,1},//20211207
			{HILINK_CS_FWABIST_REG,"PLL1_I25B2__k_F31Q0->F31Q1_k","Itank25_PLL1_B2F31Q0_force_center_freq","Itank25_PLL1_B2F31Q2_force_center_freq","","","Sub",0x1D012,350,0x1D014,0,1},
			{HILINK_CS_FWABIST_REG,"PLL1_I25B3__k_F0Q0->F0Q1_k","Itank25_PLL1_B3F0Q0_force_center_freq","Itank25_PLL1_B3F0Q2_force_center_freq","","","Sub",0x1D016,380,0x1D018,0,1},
			{HILINK_CS_FWABIST_REG,"PLL1_I25B3__k_F0Q1->F1Q0_k","Itank25_PLL1_B3F0Q2_force_center_freq","Itank25_PLL1_B3F1Q0_force_center_freq","","","Sub",0x1D01A,400,0x1D01C,0,1},//20211207
			{HILINK_CS_FWABIST_REG,"PLL1_I25B3__k_F1Q0->F1Q1_k","Itank25_PLL1_B3F1Q0_force_center_freq","Itank25_PLL1_B3F1Q2_force_center_freq","","","Sub",0x1D01E,380,0x1D020,0,1},
			{HILINK_CS_FWABIST_REG,"PLL1_I25B3__k_F30Q0->F30Q1_k","Itank25_PLL1_B3F30Q0_force_center_freq","Itank25_PLL1_B3F30Q2_force_center_freq","","","Sub",0x1D022,303,0x1D024,0,1},
			{HILINK_CS_FWABIST_REG,"PLL1_I25B3__k_F30Q1->F31Q0_k","Itank25_PLL1_B3F30Q2_force_center_freq","Itank25_PLL1_B3F31Q0_force_center_freq","","","Sub",0x1D026,295,0x1D028,0,1},//20211207
			{HILINK_CS_FWABIST_REG,"PLL1_I25B3__k_F31Q0->F31Q1_k","Itank25_PLL1_B3F31Q0_force_center_freq","Itank25_PLL1_B3F31Q2_force_center_freq","","","Sub",0x1D02A,303,0x1D02C,0,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B0F0Q0I25_hForceCenter","Itank25_PLL0_B0F0Q0_force_center_freq","","","","Get",0x1D04E,2000000,0x1D054,1672000,1},
			{HILINK_CS_FWABIST_REG,"PLL0_B3F30Q2I25_lForceCenter","Itank25_PLL0_B3F30Q2_force_center_freq","","","","Get",0x1D056,1093750,0x1D05C,0,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B0F0Q0I25_hForceCenter","Itank25_PLL1_B0F0Q0_force_center_freq","","","","Get",0x1D08E,2000000,0x1D094,1620000,1},
			{HILINK_CS_FWABIST_REG,"PLL1_B3F30Q2I25_lForceCenter","Itank25_PLL1_B3F30Q2_force_center_freq","","","","Get",0x1D096,1078125,0x1D09C,0,1}
//			{HILINK_CS_FWABIST_REG,"TestResult","TestResult","","","","Get",0,0xF0F1,0,0xF0F1,1}
		};
		assert(sizeof(VCOTuningRange_CALCULATOR_TABLE)/sizeof(T_FWABIST_CALCULATE_INFO)==VCOTuningRange_TABLE_Calculate_COUNT);
		return VCOTuningRange_CALCULATOR_TABLE[idx];
	}



};

void VCOTuningRange_TABLE_DEFINE::FWABIST_Registers_Map_Init(const MACRO_LANE_SEL& MacroLane_Sel,
							   MACRO_ARRAY_D& CS_REG_RESULT,
							   MACRO_ARRAY_MAP& MAP_CS_NODE_VALUE){

        d2s_JTAG& jtag = d2s_JTAG::Instance();
	init_FWABIST_REG_TABLE();

//	D2S_FRAMEWORK;

	CS_REG_RESULT.init(CS_REG_count,0);
	//MAP_CS_NODE_VALUE.init(CS_REG_count,0);

	string read_id;
	for(uint midx=0;midx<MacroLane_Sel.size();midx++){
		  uint MacroID=MacroLane_Sel[midx].MacroID;
		  const vector<uint>& vLane=MacroLane_Sel[midx].vLane;
		  ostringstream str;
		  str<<"_M"<<MacroID;

//		  fr.d2s_LABEL_BEGIN("READ_FWABIST_CS",d2sFrameWorkModeType::Enum(d2s_mode));
                  d2s::d2s_LABEL_BEGIN("READ_FWABIST_CS_", Global_D2S_Mode); 
		  	  	  selectMacro(MacroID);
				  for(uint i=0;i<CS_REG_count;i++){
					  const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(CS_REG_map[i]);
					  jtag.read(FWABIST_reg.addr>>1,FWABIST_reg.name+str.str());
				  }
//	      fr.d2s_LABEL_END();
             d2s::d2s_LABEL_END(); 
             // FOREACH_ACTIVE_SITE(api) {
              //  unsigned int SiteID = api->Get_active_site();
                
			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

			  for(uint i=0;i<CS_REG_count;i++){
				  const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(CS_REG_map[i]);
				  CS_REG_RESULT[SiteID][MacroID][i]=shift_bytes(jtag.getReadValue(FWABIST_reg.name+str.str())[SiteID]);
				  if((int)FWABIST_reg.name.find("force_down_freq")>0)
				  {
				  	double force_down_buffer= CS_REG_RESULT[SiteID][MacroID][i];
					MAP_CS_NODE_VALUE[SiteID][MacroID][FWABIST_reg.name] = (force_down_buffer < 4096) ? (96 * 156.25 * (1 + force_down_buffer / (4096 - force_down_buffer)) ) : (96 * 156.25 * (1 - (force_down_buffer - 4096) / 4096) );
				  }
				  else if((int)FWABIST_reg.name.find("force_center_freq")>0)
				  {
				  	double force_center_buffer= CS_REG_RESULT[SiteID][MacroID][i];
					MAP_CS_NODE_VALUE[SiteID][MacroID][FWABIST_reg.name] = (force_center_buffer < 4096) ? (96 * 156.25 * (1 + force_center_buffer / (4096 - force_center_buffer))*10 ) : (96 * 156.25 * (1 - (force_center_buffer - 4096) / 4096)*10 );
				  }
				  else if((int)FWABIST_reg.name.find("force_up_freq")>0)
				  {
				  	double force_up_buffer= CS_REG_RESULT[SiteID][MacroID][i];
					MAP_CS_NODE_VALUE[SiteID][MacroID][FWABIST_reg.name] = (force_up_buffer < 4096) ? (96 * 156.25 * (1 + force_up_buffer / (4096 - force_up_buffer)) ) : (96 * 156.25 * (1 - (force_up_buffer - 4096) / 4096) );
				  }
				  else
				  {
					double other= CS_REG_RESULT[SiteID][MacroID][i];
					MAP_CS_NODE_VALUE[SiteID][MacroID][FWABIST_reg.name] = other;
				  }
				  hout(RELEASE) <<"Macro: "<<MacroID<<"  CSNodeName: : "<<FWABIST_reg.name<< "Register Value: "<< CS_REG_RESULT[SiteID][MacroID][i];
				  hout(RELEASE) <<"Node Value(after calc): "<<MAP_CS_NODE_VALUE[SiteID][MacroID][FWABIST_reg.name] << endl;
//				  hout(RELEASE) <<"Macro: "<<MacroID<<"  CSNodeName: : "<<FWABIST_reg.name<< "Node Value(after calc): "<< MAP_CS_NODE_VALUE[SiteID][MacroID][i] <<endl;
			  }
             // }
		  FOREACH_ACTIVESITE_END
		  }
	}




#endif /* FWABIST_VCOTuningRange_H_ */
