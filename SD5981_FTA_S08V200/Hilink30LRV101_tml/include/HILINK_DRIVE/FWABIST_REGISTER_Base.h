/*
 * FwAbist_Register_Base.h
 *
 *  Created on: Apr 13, 2017
 *      Author: zhenghe
 */

#ifndef FWABIST_REGISTER_BASE_H_
#define FWABIST_REGISTER_BASE_H_

#include <HILINK_DRIVE/HiLink_Drive.h>


typedef enum{
	HILINK_SS_FWABIST_REG,
	HILINK_CS_FWABIST_REG,
	HILINK_DS_FWABIST_REG
} E_FWABIST_REG_TYPE;

typedef struct{
	E_FWABIST_REG_TYPE type;
	string name;
	uint   addr;
	uint   SpecHigh_Address;
	int   SpecHigh_Value;
	uint   SpecLow_Address;
	int   SpecLow_Value;
	uint   Spec_Wrttern_Rate;
} T_FWABIST_REG_INFO;

typedef struct{
	E_FWABIST_REG_TYPE type;
	string NODE_NAME;
	string Input1;
	string Input2;
	string Input3;
	string Input4;
	string Formula;
	uint   SpecHigh_Address;
	int   SpecHigh_Value;
	uint   SpecLow_Address;
	int   SpecLow_Value;
	uint   Spec_Wrttern_Rate;
} T_FWABIST_CALCULATE_INFO;

class FWABIST_REGISTER_Base{
protected:
	uint shift_bytes(uint data);
	uint SS_REG_count;
	uint CS_REG_count;
	uint DS_REG_count;
	uint SS_Calculate_REG_count;
	uint CS_Calculate_REG_count;
	uint DS_Calculate_REG_count;
	vector<uint> SS_REG_map;
	vector<uint> DS_REG_map;
	vector<uint> CS_REG_map;
	vector<uint> SS_Calculate_map;
	vector<uint> DS_Calculate_map;
	vector<uint> CS_Calculate_map;
	void init_FWABIST_REG_TABLE();
	void init_FWABIST_Calculate_REG_TABLE();
	bool isInit;
	bool isInit_Calculate;
public:
	FWABIST_REGISTER_Base();
	virtual ~FWABIST_REGISTER_Base();
	void ReadAll_FWABIST_Registers(const MACRO_LANE_SEL& MacroLane_Sel,
								MACRO_ARRAY_D& SS_REG_RESULT,
								MACRO_ARRAY_D& CS_REG_RESULT,
								LANE_ARRAY_D& DS_REG_RESULT);

	void FWABIST_Registers_Map_Init(const MACRO_LANE_SEL& MacroLane_Sel,
								   MACRO_ARRAY_D& SS_REG_RESULT,
								   MACRO_ARRAY_MAP& MAP_SS_NODE_VALUE,
								   MACRO_ARRAY_D& CS_REG_RESULT,
								   MACRO_ARRAY_MAP& MAP_CS_NODE_VALUE,
								   LANE_ARRAY_D& DS_REG_RESULT,
								   LANE_ARRAY_MAP& MAP_DS_NODE_VALUE,
								   LANE_DOUBLE& Half_HVCC_Part1_Volt,
								   LANE_DOUBLE& Half_HVCC_Public_Volt,
								   MACRO_DOUBLE& Quarter_CS_HVCC_Part1_Volt,
								   MACRO_DOUBLE& Quarter_CS_HVCC_Public_Volt);

	void FWABIST_Registers_Map_Init(const MACRO_LANE_SEL& MacroLane_Sel,
								   LANE_ARRAY_D& DS_REG_RESULT,
								   LANE_ARRAY_MAP& MAP_DS_NODE_VALUE,
								   LANE_DOUBLE& HVCC);

	void FWABIST_Registers_Map_Init(const MACRO_LANE_SEL& MacroLane_Sel,
								   MACRO_ARRAY_D& SS_REG_RESULT,
								   MACRO_ARRAY_MAP& MAP_SS_NODE_VALUE,
								   MACRO_ARRAY_D& CS_REG_RESULT,
								   MACRO_ARRAY_MAP& MAP_CS_NODE_VALUE,
								   LANE_ARRAY_D& DS_REG_RESULT,
								   LANE_ARRAY_MAP& MAP_DS_NODE_VALUE);


	const T_FWABIST_REG_INFO& get_SS_FWABIST_REG(uint idx);
	const T_FWABIST_REG_INFO& get_CS_FWABIST_REG(uint idx);
	const T_FWABIST_REG_INFO& get_DS_FWABIST_REG(uint idx);

	const T_FWABIST_CALCULATE_INFO& get_SS_Calculate_REG(uint idx);
	const T_FWABIST_CALCULATE_INFO& get_CS_Calculate_REG(uint idx);
	const T_FWABIST_CALCULATE_INFO& get_DS_Calculate_REG(uint idx);

	uint get_SS_FWABIST_REG_count();
	uint get_CS_FWABIST_REG_count();
	uint get_DS_FWABIST_REG_count();

	uint get_SS_FWABIST_Calculate_REG_count();
	uint get_CS_FWABIST_Calculate_REG_count();
	uint get_DS_FWABIST_Calculate_REG_count();


	virtual uint map_DS_Addr(uint DS0_addr,uint LaneID)=0;
	virtual uint get_FWABIST_TABLE_count()=0;
	virtual uint get_FWABIST_Calculate_count()=0;
	virtual const T_FWABIST_REG_INFO& get_FWABIST_TABLE_ITEM(uint idx)=0;
	virtual const T_FWABIST_CALCULATE_INFO& get_FWABIST_CALCULATE_ITEM(uint idx)=0;
};


#endif /* FWABIST_REGISTER_BASE_H_ */
