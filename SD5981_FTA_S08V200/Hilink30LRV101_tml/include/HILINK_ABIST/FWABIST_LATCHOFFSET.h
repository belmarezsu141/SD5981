/*
 * FWABIST_ATB.h
 *
 *  Created on: Apr 13, 2017
 *      Author: zhenghe
 */

#ifndef FWABIST_LATCHOFFSET_H_
#define FWABIST_LATCHOFFSET_H_


#include <HILINK_DRIVE/FWABIST_REGISTER_Base.h>


#define LATCHOFFSET_TABLE_COUNT 40 //Take dsHvccCode for specical processing
#define LATCHOFFSET_TABLE_Calculate_COUNT 20
class LATCHOFFSET_TABLE_DEFINE:public FWABIST_REGISTER_Base{
private:
	LATCHOFFSET_TABLE_DEFINE(){}
public:
	static LATCHOFFSET_TABLE_DEFINE& getInstance(){
		static LATCHOFFSET_TABLE_DEFINE inst;
		return inst;
	}

	uint map_DS_Addr(uint DS0_addr,uint LaneID){
		return DS0_addr+162*LaneID; //TODO: confirm address mapping of DS
	}

	uint get_FWABIST_TABLE_count(){return LATCHOFFSET_TABLE_COUNT;}
	uint get_FWABIST_Calculate_count(){return LATCHOFFSET_TABLE_Calculate_COUNT;}


	//Table 2-10
	const T_FWABIST_REG_INFO& get_FWABIST_TABLE_ITEM(uint idx){
		assert(idx<LATCHOFFSET_TABLE_COUNT);
		const static T_FWABIST_REG_INFO LATCHOFFSET_TABLE[]={
//{ HILINK_DS_FWABIST_REG, "dsHvccCode", 0x1F024, 0, 0, 0, 0, 0},

			{ HILINK_DS_FWABIST_REG, "pNodeVol_1", 0x1F036, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_1", 0x1F038, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "pNodeVol_2", 0x1F03C, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_2", 0x1F03E, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "pNodeVol_3", 0x1F042, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_3", 0x1F044, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "pNodeVol_4", 0x1F048, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_4", 0x1F04A, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "pNodeVol_5", 0x1F04E, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_5", 0x1F050, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "pNodeVol_6", 0x1F054, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_6", 0x1F056, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "pNodeVol_7", 0x1F05A, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_7", 0x1F05C, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "pNodeVol_8", 0x1F060, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_8", 0x1F062, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "pNodeVol_9", 0x1F066, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_9", 0x1F068, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "pNodeVol_10", 0x1F06C, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_10", 0x1F06E, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "pNodeVol_11", 0x1F072, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_11", 0x1F074, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "pNodeVol_12", 0x1F078, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_12", 0x1F07A, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "pNodeVol_13", 0x1F07E, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_13", 0x1F080, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "pNodeVol_14", 0x1F084, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_14", 0x1F086, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "pNodeVol_15", 0x1F08A, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_15", 0x1F08C, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "pNodeVol_16", 0x1F090, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_16", 0x1F092, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "pNodeVol_17", 0x1F096, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_17", 0x1F098, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "pNodeVol_18", 0x1F09C, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_18", 0x1F09E, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "pNodeVol_19", 0x1F0A2, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_19", 0x1F0A4, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "pNodeVol_20", 0x1F0A8, 0, 0, 0, 0, 0},
			{ HILINK_DS_FWABIST_REG, "mNodeVol_20", 0x1F0AA, 0, 0, 0, 0, 0}
		};
		assert(sizeof(LATCHOFFSET_TABLE)/sizeof(T_FWABIST_REG_INFO)==LATCHOFFSET_TABLE_COUNT);
		return LATCHOFFSET_TABLE[idx];
	}

	//Table 2-11
	const T_FWABIST_CALCULATE_INFO& get_FWABIST_CALCULATE_ITEM(uint idx){
		assert(idx<LATCHOFFSET_TABLE_Calculate_COUNT);
		const static T_FWABIST_CALCULATE_INFO LATCHOFFSET_CALCULATOR_TABLE[]={
			{HILINK_DS_FWABIST_REG, "c0_p_rsd_ofst", "pNodeVol_1", "mNodeVol_1", "", "", "Sub", 0, 15, 0, -15, 1},
			{HILINK_DS_FWABIST_REG, "c0_m_rsd_ofst", "pNodeVol_2", "mNodeVol_2", "", "", "Sub", 0, 15, 0, -15, 1},
			{HILINK_DS_FWABIST_REG, "c90_p_rsd_ofst", "pNodeVol_3", "mNodeVol_3", "", "", "Sub", 0, 15, 0, -15, 1},
			{HILINK_DS_FWABIST_REG, "c90_m_rsd_ofst", "pNodeVol_4", "mNodeVol_4", "", "", "Sub", 0, 15, 0, -15, 1},
			{HILINK_DS_FWABIST_REG, "c180_p_rsd_ofst", "pNodeVol_5", "mNodeVol_5", "", "", "Sub", 0, 15, 0, -15, 1},
			{HILINK_DS_FWABIST_REG, "c180_m_rsd_ofst", "pNodeVol_6", "mNodeVol_6", "", "", "Sub", 0, 15, 0, -15, 1},
			{HILINK_DS_FWABIST_REG, "c270_p_rsd_ofst", "pNodeVol_7", "mNodeVol_7", "", "", "Sub", 0, 15, 0, -15, 1},
			{HILINK_DS_FWABIST_REG, "c270_m_rsd_ofst", "pNodeVol_8", "mNodeVol_8", "", "", "Sub", 0, 15, 0, -15, 1},
			{HILINK_DS_FWABIST_REG, "e0_p_rsd_ofst", "pNodeVol_9", "mNodeVol_9", "", "", "Sub", 0, 15, 0, -15, 1},
			{HILINK_DS_FWABIST_REG, "e0_m_rsd_ofst", "pNodeVol_10", "mNodeVol_10", "", "", "Sub", 0, 15, 0, -15, 1},
			{HILINK_DS_FWABIST_REG, "e90_p_rsd_ofst", "pNodeVol_11", "mNodeVol_11", "", "", "Sub", 0, 15, 0, -15, 1},
			{HILINK_DS_FWABIST_REG, "e90_m_rsd_ofst", "pNodeVol_12", "mNodeVol_12", "", "", "Sub", 0, 15, 0, -15, 1},
			{HILINK_DS_FWABIST_REG, "e180_p_rsd_ofst", "pNodeVol_13", "mNodeVol_13", "", "", "Sub", 0, 15, 0, -15, 1},
			{HILINK_DS_FWABIST_REG, "e180_m_rsd_ofst", "pNodeVol_14", "mNodeVol_14", "", "", "Sub", 0, 15, 0, -15, 1},
			{HILINK_DS_FWABIST_REG, "e270_p_rsd_ofst", "pNodeVol_15", "mNodeVol_15", "", "", "Sub", 0, 15, 0, -15, 1},
			{HILINK_DS_FWABIST_REG, "e270_m_rsd_ofst", "pNodeVol_16", "mNodeVol_16", "", "", "Sub", 0, 15, 0, -15, 1},
			{HILINK_DS_FWABIST_REG, "m0_rsd_ofst", "pNodeVol_17", "mNodeVol_17", "", "", "Sub", 0, 15, 0, -15, 1},
			{HILINK_DS_FWABIST_REG, "m90_rsd_ofst", "pNodeVol_18", "mNodeVol_18", "", "", "Sub", 0, 15, 0, -15, 1},
			{HILINK_DS_FWABIST_REG, "m180_rsd_ofst", "pNodeVol_19", "mNodeVol_19", "", "", "Sub", 0, 15, 0, -15, 1},
			{HILINK_DS_FWABIST_REG, "m270_rsd_ofst", "pNodeVol_20", "mNodeVol_20", "", "", "Sub", 0, 15, 0, -15, 1}



		};
		assert(sizeof(LATCHOFFSET_CALCULATOR_TABLE)/sizeof(T_FWABIST_CALCULATE_INFO)==LATCHOFFSET_TABLE_Calculate_COUNT);
		return LATCHOFFSET_CALCULATOR_TABLE[idx];
	}



};



#endif /* FWABIST_LATCHOFFSET_H_ */
