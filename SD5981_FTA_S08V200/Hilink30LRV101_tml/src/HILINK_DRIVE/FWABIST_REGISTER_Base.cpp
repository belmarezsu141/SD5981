/*
 * FWABIST_REGISTER_BASE.cpp
 *
 *  Created on: Apr 13, 2017
 *      Author: zhenghe
 */


#include <HILINK_DRIVE/FWABIST_REGISTER_Base.h>

uint
FWABIST_REGISTER_Base::shift_bytes(uint data){
	uint hi_byte = (data & 0xff00)>>8;
	uint lo_byte = (data & 0x00ff)<<8;
	return hi_byte|lo_byte;
}

FWABIST_REGISTER_Base::FWABIST_REGISTER_Base(){
	isInit=false;
	SS_REG_count=0;
	CS_REG_count=0;
	DS_REG_count=0;

	SS_REG_map.clear();
	CS_REG_map.clear();
	DS_REG_map.clear();

}

void
FWABIST_REGISTER_Base::init_FWABIST_REG_TABLE(){
	if(isInit){
		return;
	}
	isInit=true;
	SS_REG_count=0;
	CS_REG_count=0;
	DS_REG_count=0;

	SS_REG_map.clear();
	CS_REG_map.clear();
	DS_REG_map.clear();

	for(uint i=0;i<get_FWABIST_TABLE_count();i++){
		switch(get_FWABIST_TABLE_ITEM(i).type){
			case HILINK_SS_FWABIST_REG:
				SS_REG_map.push_back(i);
				break;
			case HILINK_CS_FWABIST_REG:
				CS_REG_map.push_back(i);
				break;
			case HILINK_DS_FWABIST_REG:
				DS_REG_map.push_back(i);
				break;
			default:
				break;
		}
	}
	SS_REG_count=SS_REG_map.size();
	CS_REG_count=CS_REG_map.size();
	DS_REG_count=DS_REG_map.size();

}

FWABIST_REGISTER_Base::~FWABIST_REGISTER_Base(){

}




void
FWABIST_REGISTER_Base::init_FWABIST_Calculate_REG_TABLE(){
	if(isInit_Calculate){
		return;
	}
	isInit_Calculate=true;
	SS_Calculate_REG_count=0;
	CS_Calculate_REG_count=0;
	DS_Calculate_REG_count=0;

	SS_Calculate_map.clear();
	CS_Calculate_map.clear();
	DS_Calculate_map.clear();

	for(uint i=0;i<get_FWABIST_Calculate_count();i++){
		switch(get_FWABIST_CALCULATE_ITEM(i).type){
			case HILINK_SS_FWABIST_REG:
				SS_Calculate_map.push_back(i);
				break;
			case HILINK_CS_FWABIST_REG:
				CS_Calculate_map.push_back(i);
				break;
			case HILINK_DS_FWABIST_REG:
				DS_Calculate_map.push_back(i);
				break;
			default:
				break;
		}
	}
	SS_Calculate_REG_count=SS_Calculate_map.size();
	CS_Calculate_REG_count=CS_Calculate_map.size();
	DS_Calculate_REG_count=DS_Calculate_map.size();

}



void
FWABIST_REGISTER_Base::ReadAll_FWABIST_Registers(const MACRO_LANE_SEL& MacroLane_Sel,MACRO_ARRAY_D& SS_REG_RESULT,MACRO_ARRAY_D& CS_REG_RESULT,LANE_ARRAY_D& DS_REG_RESULT){

	init_FWABIST_REG_TABLE();
        d2s_JTAG& jtag = d2s_JTAG::Instance();
//	D2S_FRAMEWORK;
	SS_REG_RESULT.init(SS_REG_count,0);
	CS_REG_RESULT.init(CS_REG_count,0);
	DS_REG_RESULT.init(DS_REG_count,0);
	string read_id;
	for(uint midx=0;midx<MacroLane_Sel.size();midx++){
		  uint MacroID=MacroLane_Sel[midx].MacroID;
		  const vector<uint>& vLane=MacroLane_Sel[midx].vLane;
		  ostringstream str;
		  str<<"_M"<<MacroID;

//		  fr.d2s_LABEL_BEGIN("READ_FWABIST_SS",d2sFrameWorkModeType::Enum(d2s_mode));
            d2s::d2s_LABEL_BEGIN("READ_FWABIST_SS_", Global_D2S_Mode);
		  	  selectMacro(MacroID);
			  for(uint i=0;i<SS_REG_count;i++){
				  const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(SS_REG_map[i]);
				  jtag.read(FWABIST_reg.addr>>1,FWABIST_reg.name+str.str());
			  }
        d2s::d2s_LABEL_END();

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			  for(uint i=0;i<SS_REG_count;i++){
				  const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(SS_REG_map[i]);
				  SS_REG_RESULT[SiteID][MacroID][i]=shift_bytes(jtag.getReadValue(FWABIST_reg.name+str.str())[SiteID]);
			  }
        FOREACH_ACTIVESITE_END

//		  fr.d2s_LABEL_BEGIN("READ_FWABIST_CS",d2sFrameWorkModeType::Enum(d2s_mode));
                  d2s::d2s_LABEL_BEGIN("READ_FWABIST_CS_", Global_D2S_Mode);
		  	  	  selectMacro(MacroID);
				  for(uint i=0;i<CS_REG_count;i++){
					  const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(CS_REG_map[i]);
					  jtag.read(FWABIST_reg.addr>>1,FWABIST_reg.name+str.str());
				  }
//	      fr.d2s_LABEL_END();
        d2s::d2s_LABEL_END();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			  for(uint i=0;i<CS_REG_count;i++){
				  const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(CS_REG_map[i]);
				  CS_REG_RESULT[SiteID][MacroID][i]=shift_bytes(jtag.getReadValue(FWABIST_reg.name+str.str())[SiteID]);
			  }
        FOREACH_ACTIVESITE_END


//		fr.d2s_LABEL_BEGIN("READ_FWABIST_DS",d2sFrameWorkModeType::Enum(d2s_mode));
                d2s::d2s_LABEL_BEGIN("READ_FWABIST_DS_", Global_D2S_Mode);
		for(uint lidx=0;lidx<vLane.size();lidx++){
			uint LaneID=vLane[lidx];
			ostringstream str;
			str<<"_M"<<MacroID<<"_L"<<LaneID;

			selectMacro(MacroID);
			for(uint i=0;i<DS_REG_count;i++){
				const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(DS_REG_map[i]);
				uint addr=map_DS_Addr(FWABIST_reg.addr,LaneID);
				jtag.read(addr>>1,FWABIST_reg.name+str.str());
			}
		}
//		fr.d2s_LABEL_END();
                        d2s::d2s_LABEL_END();

		for(uint lidx=0;lidx<vLane.size();lidx++){
			uint LaneID=vLane[lidx];
			ostringstream str;
			str<<"_M"<<MacroID<<"_L"<<LaneID;
//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
	        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for(uint i=0;i<DS_REG_count;i++){
				const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(DS_REG_map[i]);
				DS_REG_RESULT[SiteID][MacroID][LaneID][i]=shift_bytes(jtag.getReadValue(FWABIST_reg.name+str.str())[SiteID]);

				  }
	        FOREACH_ACTIVESITE_END
		  }
	}

}




void
FWABIST_REGISTER_Base::FWABIST_Registers_Map_Init(const MACRO_LANE_SEL& MacroLane_Sel,
							   MACRO_ARRAY_D& SS_REG_RESULT,
							   MACRO_ARRAY_MAP& MAP_SS_NODE_VALUE,
							   MACRO_ARRAY_D& CS_REG_RESULT,
							   MACRO_ARRAY_MAP& MAP_CS_NODE_VALUE,
							   LANE_ARRAY_D& DS_REG_RESULT,
							   LANE_ARRAY_MAP& MAP_DS_NODE_VALUE,
							   LANE_DOUBLE& Half_HVCC_Part1_Volt,
							   LANE_DOUBLE& Half_HVCC_Public_Volt,
							   MACRO_DOUBLE& Quarter_CS_HVCC_Part1_Volt,
							   MACRO_DOUBLE& Quarter_CS_HVCC_Public_Volt){

	init_FWABIST_REG_TABLE();
        d2s_JTAG& jtag = d2s_JTAG::Instance();

	SS_REG_RESULT.init(SS_REG_count,0);
	CS_REG_RESULT.init(CS_REG_count,0);
	DS_REG_RESULT.init(DS_REG_count,0);
	string read_id;
	for(uint midx=0;midx<MacroLane_Sel.size();midx++){
            uint MacroID=MacroLane_Sel[midx].MacroID;
            const vector<uint>& vLane=MacroLane_Sel[midx].vLane;
            ostringstream str;
            str<<"_M"<<MacroID;


            d2s::d2s_LABEL_BEGIN("READ_FWABIST_SS_", Global_D2S_Mode);
                    selectMacro(MacroID);
                    for(uint i=0;i<SS_REG_count;i++){
                            const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(SS_REG_map[i]);
                            jtag.read(FWABIST_reg.addr>>1,FWABIST_reg.name+str.str());
                    }

            d2s::d2s_LABEL_END();

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			  for(uint i=0;i<SS_REG_count;i++){
				  const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(SS_REG_map[i]);
				  SS_REG_RESULT[SiteID][MacroID][i]=shift_bytes(jtag.getReadValue(FWABIST_reg.name+str.str())[SiteID])*1200.0/1024;
				  MAP_SS_NODE_VALUE[SiteID][MacroID][FWABIST_reg.name] = SS_REG_RESULT[SiteID][MacroID][i];
			  }
            FOREACH_ACTIVESITE_END

            d2s::d2s_LABEL_BEGIN("READ_FWABIST_CS_", Global_D2S_Mode);
                            selectMacro(MacroID);
                            for(uint i=0;i<CS_REG_count;i++){
                                    const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(CS_REG_map[i]);
                                    jtag.read(FWABIST_reg.addr>>1,FWABIST_reg.name+str.str());
                            }
            d2s::d2s_LABEL_END();

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			  for(uint i=0;i<CS_REG_count;i++){
				  const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(CS_REG_map[i]);
				  CS_REG_RESULT[SiteID][MacroID][i]=shift_bytes(jtag.getReadValue(FWABIST_reg.name+str.str())[SiteID]) * Quarter_CS_HVCC_Public_Volt[SiteID][MacroID] * 4 /1024 ;
				  MAP_CS_NODE_VALUE[SiteID][MacroID][FWABIST_reg.name] = CS_REG_RESULT[SiteID][MacroID][i];
				  //cout <<"Macro: "<<MacroID<<"  CSNode: testname: "<<FWABIST_reg.name<< "Value: "<< CS_REG_RESULT[SiteID][MacroID][i] <<"Quarter_HVCC_Puclic_Volt: "<<Quarter_CS_HVCC_Public_Volt[SiteID][MacroID]<<endl;
			  }
            FOREACH_ACTIVESITE_END

            d2s::d2s_LABEL_BEGIN("READ_FWABIST_DS_", Global_D2S_Mode);
            for(uint lidx=0;lidx<vLane.size();lidx++){
                    uint LaneID=vLane[lidx];
                    ostringstream str;
                    str<<"_M"<<MacroID<<"_L"<<LaneID;
                    selectMacro(MacroID);
                    for(uint i=0;i<DS_REG_count;i++){
                            const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(DS_REG_map[i]);
                            uint addr=map_DS_Addr(FWABIST_reg.addr,LaneID);

                            hout(GENERAL) <<"Current Address: 0x"<<hex<<addr<<" DS Name: "<<get_FWABIST_TABLE_ITEM(DS_REG_map[i]).name<<endl;
                            jtag.read(addr>>1,FWABIST_reg.name+str.str());
                    }
            }
            d2s::d2s_LABEL_END();

            for(uint lidx=0;lidx<vLane.size();lidx++){
                    uint LaneID=vLane[lidx];
                    ostringstream str;
                    str<<"_M"<<MacroID<<"_L"<<LaneID;

//                    FOREACH_ACTIVE_SITE(api) {
//                        unsigned int SiteID = api->Get_active_site();
                    FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
                        for(uint i=0;i<DS_REG_count;i++){
                                const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(DS_REG_map[i]);
                                if((FWABIST_reg.name == "DSTX_TXVREG_PREDRV_2_3") || (FWABIST_reg.name == "DSTX_TXVREG_DRV_2_3") ||(FWABIST_reg.name == "DSTX_TXDRV_SENSE_P_N") ||(FWABIST_reg.name == "DSTX_TXDRV_SENSE_M_N") || (FWABIST_reg.name == "DSMISC_DSCALCOMP_VREF_1") ||(FWABIST_reg.name == "DSMISC_DSCALCOMP_VREF_2")){
                                DS_REG_RESULT[SiteID][MacroID][LaneID][i]=shift_bytes(jtag.getReadValue(FWABIST_reg.name+str.str())[SiteID]) * Half_HVCC_Part1_Volt[SiteID][MacroID][LaneID]*2/1024;
                                MAP_DS_NODE_VALUE[SiteID][MacroID][LaneID][FWABIST_reg.name] = DS_REG_RESULT[SiteID][MacroID][LaneID][i];
                                hout(GENERAL) <<"xxxSiteID:"<<SiteID<<"Macro: "<<MacroID<<" LaneID: "<<LaneID<<" DSNode: testname: "<<FWABIST_reg.name<< "Value: "<< DS_REG_RESULT[SiteID][MacroID][LaneID][i] <<"Half_HVCC_Part1_Volt: "<<Half_HVCC_Part1_Volt[SiteID][MacroID][LaneID]<<endl;}
                                else{
                                        DS_REG_RESULT[SiteID][MacroID][LaneID][i]=shift_bytes(jtag.getReadValue(FWABIST_reg.name+str.str())[SiteID])*Half_HVCC_Public_Volt[SiteID][MacroID][LaneID]*2/1024;

                                        MAP_DS_NODE_VALUE[SiteID][MacroID][LaneID][FWABIST_reg.name] = DS_REG_RESULT[SiteID][MacroID][LaneID][i];
                                        hout(GENERAL) <<"xxxSiteID:"<<SiteID<<"Macro: "<<MacroID<<" LaneID: "<<LaneID<<" DSNode: testname: "<<FWABIST_reg.name<< "Value: "<< DS_REG_RESULT[SiteID][MacroID][LaneID][i]<<"Half_HVCC_Public_Volt: "<<Half_HVCC_Public_Volt[SiteID][MacroID][LaneID]<<endl;}
                          }
                    FOREACH_ACTIVESITE_END
                }
            }
	}

void
FWABIST_REGISTER_Base::FWABIST_Registers_Map_Init(const MACRO_LANE_SEL& MacroLane_Sel,LANE_ARRAY_D& DS_REG_RESULT,LANE_ARRAY_MAP& MAP_DS_NODE_VALUE, LANE_DOUBLE& HVCC)
{
	init_FWABIST_REG_TABLE();
//	D2S_FRAMEWORK;
         d2s_JTAG& jtag = d2s_JTAG::Instance();
	DS_REG_RESULT.init(DS_REG_count,0);
	string read_id;

//	fr.d2s_LABEL_BEGIN("READ_FWABIST_DS",d2sFrameWorkModeType::Enum(d2s_mode));
        d2s::d2s_LABEL_BEGIN("READ_FWABIST_DS_", Global_D2S_Mode);
	for(uint midx=0;midx<MacroLane_Sel.size();midx++)
	{
		uint MacroID=MacroLane_Sel[midx].MacroID;
		const vector<uint>& vLane=MacroLane_Sel[midx].vLane;
		ostringstream str;
		str<<"_M"<<MacroID;
		selectMacro(MacroID);

		for(uint lidx=0;lidx<vLane.size();lidx++)
		{
			uint LaneID=vLane[lidx];
			ostringstream str;
			str<<"_M"<<MacroID<<"_L"<<LaneID;

			for(uint i=0;i<DS_REG_count;i++){
				const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(DS_REG_map[i]);
				uint addr=map_DS_Addr(FWABIST_reg.addr,LaneID);
				jtag.read(addr>>1,FWABIST_reg.name+str.str());
			}
		}
	}
//	fr.d2s_LABEL_END();
                d2s::d2s_LABEL_END();
	for(uint midx=0;midx<MacroLane_Sel.size();midx++)
	{
		  uint MacroID=MacroLane_Sel[midx].MacroID;
		  const vector<uint>& vLane=MacroLane_Sel[midx].vLane;
		  ostringstream str;
		  str<<"_M"<<MacroID;

		for(uint lidx=0;lidx<vLane.size();lidx++)
		{
			uint LaneID=vLane[lidx];
			ostringstream str;
			str<<"_M"<<MacroID<<"_L"<<LaneID;

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for(uint i=0;i<DS_REG_count;i++)
			{
				const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(DS_REG_map[i]);
				DS_REG_RESULT[SiteID][MacroID][LaneID][i]=shift_bytes(jtag.getReadValue(FWABIST_reg.name+str.str())[SiteID])*2*HVCC[SiteID][MacroID][LaneID]/1024;
				MAP_DS_NODE_VALUE[SiteID][MacroID][LaneID][FWABIST_reg.name] = DS_REG_RESULT[SiteID][MacroID][LaneID][i];
				hout(GENERAL) <<"Macro: "<<MacroID<<" LaneID: "<<LaneID<<" DSNode: testname: "<<FWABIST_reg.name<< "Value: "<< DS_REG_RESULT[SiteID][MacroID][LaneID][i]<<"HVCC_Vlot: "<<HVCC[SiteID][MacroID][LaneID]<<endl;
			}
			FOREACH_ACTIVESITE_END
		}
	}
	hout(GENERAL) <<endl<<endl;
}

const T_FWABIST_REG_INFO&
FWABIST_REGISTER_Base::get_SS_FWABIST_REG(uint idx){
	init_FWABIST_REG_TABLE();
	if(idx<SS_REG_count){
		return get_FWABIST_TABLE_ITEM(SS_REG_map[idx]);
	}
	else{
//		cerr<<"Error: "<<idx<<" is outrange of SS_FWABIST_REG_COUNT: "<<SS_REG_count<<endl;
		// ERROR_EXIT(TM::ABORT_FLOW);
	}
	return get_FWABIST_TABLE_ITEM(0);
}
const T_FWABIST_REG_INFO&
FWABIST_REGISTER_Base::get_CS_FWABIST_REG(uint idx){
	init_FWABIST_REG_TABLE();
	if(idx<CS_REG_count){
		return get_FWABIST_TABLE_ITEM(CS_REG_map[idx]);
	}
	else{
//		cerr<<"Error: "<<idx<<" is outrange of CS_FWABIST_REG_COUNT: "<<CS_REG_count<<endl;
		// ERROR_EXIT(TM::ABORT_FLOW);
	}
	return get_FWABIST_TABLE_ITEM(0);

}
const T_FWABIST_REG_INFO&
FWABIST_REGISTER_Base::get_DS_FWABIST_REG(uint idx){
	init_FWABIST_REG_TABLE();
	if(idx<DS_REG_count){
		return get_FWABIST_TABLE_ITEM(DS_REG_map[idx]);
	}
	else{
//		cerr<<"Error: "<<idx<<" is outrange of DS_FWABIST_REG_COUNT: "<<DS_REG_count<<endl;
		// ERROR_EXIT(TM::ABORT_FLOW);
	}
	return get_FWABIST_TABLE_ITEM(0);

}


const T_FWABIST_CALCULATE_INFO&
FWABIST_REGISTER_Base::get_SS_Calculate_REG(uint idx){
	init_FWABIST_Calculate_REG_TABLE();
	if(idx<SS_Calculate_REG_count){
		return get_FWABIST_CALCULATE_ITEM(SS_Calculate_map[idx]);
	}
	else{
//		cerr<<"Error: "<<idx<<" is outrange of SS_FWABIST_REG_COUNT: "<<SS_Calculate_REG_count<<endl;
		// ERROR_EXIT(TM::ABORT_FLOW);
	}
	return get_FWABIST_CALCULATE_ITEM(0);
}
const T_FWABIST_CALCULATE_INFO&
FWABIST_REGISTER_Base::get_CS_Calculate_REG(uint idx){
	init_FWABIST_Calculate_REG_TABLE();
	if(idx<CS_Calculate_REG_count){
		return get_FWABIST_CALCULATE_ITEM(CS_Calculate_map[idx]);
	}
	else{
//		cerr<<"Error: "<<idx<<" is outrange of CS_Calculate_REG_count: "<<CS_Calculate_REG_count<<endl;
		// ERROR_EXIT(TM::ABORT_FLOW);
	}
	return get_FWABIST_CALCULATE_ITEM(0);

}
const T_FWABIST_CALCULATE_INFO&
FWABIST_REGISTER_Base::get_DS_Calculate_REG(uint idx){
	init_FWABIST_REG_TABLE();
	if(idx<DS_Calculate_REG_count){
		return get_FWABIST_CALCULATE_ITEM(DS_Calculate_map[idx]);
	}
	else{
//		cerr<<"Error: "<<idx<<" is outrange of DS_Calculate_REG_count: "<<DS_Calculate_REG_count<<endl;
//		// ERROR_EXIT(TM::ABORT_FLOW);
	}
	return get_FWABIST_CALCULATE_ITEM(0);

}

uint
FWABIST_REGISTER_Base::get_SS_FWABIST_REG_count(){
	init_FWABIST_REG_TABLE();
	return SS_REG_count;
}
uint
FWABIST_REGISTER_Base::get_CS_FWABIST_REG_count(){
	init_FWABIST_REG_TABLE();
	return CS_REG_count;
}
uint
FWABIST_REGISTER_Base::get_DS_FWABIST_REG_count(){
	init_FWABIST_REG_TABLE();
	return DS_REG_count;
}

uint
FWABIST_REGISTER_Base::get_SS_FWABIST_Calculate_REG_count(){
	init_FWABIST_Calculate_REG_TABLE();
	return 	SS_Calculate_REG_count;

}
uint
FWABIST_REGISTER_Base::get_CS_FWABIST_Calculate_REG_count(){
	init_FWABIST_Calculate_REG_TABLE();
	return CS_Calculate_REG_count;
}
uint
FWABIST_REGISTER_Base::get_DS_FWABIST_Calculate_REG_count(){
	init_FWABIST_Calculate_REG_TABLE();
	return DS_Calculate_REG_count;
}


void
FWABIST_REGISTER_Base::FWABIST_Registers_Map_Init(const MACRO_LANE_SEL& MacroLane_Sel,
							   MACRO_ARRAY_D& SS_REG_RESULT,
							   MACRO_ARRAY_MAP& MAP_SS_NODE_VALUE,
							   MACRO_ARRAY_D& CS_REG_RESULT,
							   MACRO_ARRAY_MAP& MAP_CS_NODE_VALUE,
							   LANE_ARRAY_D& DS_REG_RESULT,
							   LANE_ARRAY_MAP& MAP_DS_NODE_VALUE){

	init_FWABIST_REG_TABLE();
        d2s_JTAG& jtag = d2s_JTAG::Instance();

//	D2S_FRAMEWORK;
	SS_REG_RESULT.init(SS_REG_count,0);
	CS_REG_RESULT.init(CS_REG_count,0);
	DS_REG_RESULT.init(DS_REG_count,0);
	string read_id;
	for(uint midx=0;midx<MacroLane_Sel.size();midx++){
		  uint MacroID=MacroLane_Sel[midx].MacroID;
		  const vector<uint>& vLane=MacroLane_Sel[midx].vLane;
		  ostringstream str;
		  str<<"_M"<<MacroID;
                   d2s::d2s_LABEL_BEGIN("READ_FWABIST_SS_", Global_D2S_Mode);
//		  fr.d2s_LABEL_BEGIN("READ_FWABIST_SS",d2sFrameWorkModeType::Enum(d2s_mode));
		  	  selectMacro(MacroID);
			  for(uint i=0;i<SS_REG_count;i++){
				  const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(SS_REG_map[i]);
				  jtag.read(FWABIST_reg.addr>>1,FWABIST_reg.name+str.str());
			  }
//		  fr.d2s_LABEL_END();
                        d2s::d2s_LABEL_END();

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
              FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			  for(uint i=0;i<SS_REG_count;i++){
				  const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(SS_REG_map[i]);
				  SS_REG_RESULT[SiteID][MacroID][i]=shift_bytes(jtag.getReadValue(FWABIST_reg.name+str.str())[SiteID]);
				  MAP_SS_NODE_VALUE[SiteID][MacroID][FWABIST_reg.name] = SS_REG_RESULT[SiteID][MacroID][i];
				  hout(GENERAL) <<"Macro: "<<MacroID<<"  SSNode: testname: "<<FWABIST_reg.name<< "Value: "<< SS_REG_RESULT[SiteID][MacroID][i] <<endl;
			  }
             FOREACH_ACTIVESITE_END
//		  fr.d2s_LABEL_BEGIN("READ_FWABIST_CS",d2sFrameWorkModeType::Enum(d2s_mode));
                  d2s::d2s_LABEL_BEGIN("READ_FWABIST_CS_", Global_D2S_Mode);
		  	  	  selectMacro(MacroID);
				  for(uint i=0;i<CS_REG_count;i++){
					  const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(CS_REG_map[i]);
					  jtag.read(FWABIST_reg.addr>>1,FWABIST_reg.name+str.str());
				  }
//	      fr.d2s_LABEL_END();
                      d2s::d2s_LABEL_END();

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
             FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			  for(uint i=0;i<CS_REG_count;i++){
				  const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(CS_REG_map[i]);
				  CS_REG_RESULT[SiteID][MacroID][i]=shift_bytes(jtag.getReadValue(FWABIST_reg.name+str.str())[SiteID]) ;
				  MAP_CS_NODE_VALUE[SiteID][MacroID][FWABIST_reg.name] = CS_REG_RESULT[SiteID][MacroID][i];
				  hout(GENERAL) <<"Macro: "<<MacroID<<"  CSNode: testname: "<<FWABIST_reg.name<< "Value: "<< CS_REG_RESULT[SiteID][MacroID][i] <<endl;
			  }
             FOREACH_ACTIVESITE_END

//		fr.d2s_LABEL_BEGIN("READ_FWABIST_DS",d2sFrameWorkModeType::Enum(d2s_mode));
                d2s::d2s_LABEL_BEGIN("READ_FWABIST_DS_", Global_D2S_Mode);
		for(uint lidx=0;lidx<vLane.size();lidx++){
			uint LaneID=vLane[lidx];
			ostringstream str;
			str<<"_M"<<MacroID<<"_L"<<LaneID;
			selectMacro(MacroID);
			for(uint i=0;i<DS_REG_count;i++){
				const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(DS_REG_map[i]);
				uint addr=map_DS_Addr(FWABIST_reg.addr,LaneID);

				hout(GENERAL) <<"Current Address: 0x"<<hex<<addr<<" DS Name: "<<get_FWABIST_TABLE_ITEM(DS_REG_map[i]).name<<endl;
				jtag.read(addr>>1,FWABIST_reg.name+str.str());
			}

		}
//		fr.d2s_LABEL_END();
        d2s::d2s_LABEL_END();
        
		for(uint lidx=0;lidx<vLane.size();lidx++){
			uint LaneID=vLane[lidx];
			ostringstream str;
			str<<"_M"<<MacroID<<"_L"<<LaneID;

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				  for(uint i=0;i<DS_REG_count;i++){
					  const T_FWABIST_REG_INFO& FWABIST_reg=get_FWABIST_TABLE_ITEM(DS_REG_map[i]);
					  DS_REG_RESULT[SiteID][MacroID][LaneID][i]=shift_bytes(jtag.getReadValue(FWABIST_reg.name+str.str())[SiteID]); //note tony 20210802  getReadValue return map<int,long long>
					  MAP_DS_NODE_VALUE[SiteID][MacroID][LaneID][FWABIST_reg.name] = DS_REG_RESULT[SiteID][MacroID][LaneID][i];
					  //cout <<"Macro: "<<MacroID<<" LaneID: "<<LaneID<<" DSNode: testname: "<<FWABIST_reg.name<< "Value: "<< DS_REG_RESULT[SiteID][MacroID][LaneID][i]<<endl;
					 }
			FOREACH_ACTIVESITE_END

		  }
	}
}
