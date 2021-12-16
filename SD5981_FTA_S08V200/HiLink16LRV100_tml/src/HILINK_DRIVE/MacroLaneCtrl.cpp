/*
 * MacroLaneCtrl.cpp
 *
 *  Created on: Aug 19, 2016
 *      Author: yanfen.fang
 */
#include <HILINK_DRIVE/MacroLaneCtrl.h>
#include <Common_Func/System_Common_Func.h>

#undef __debug__

const This_HILINK_INFO& HILINK_INFO=This_HILINK_INFO::getInstance();
const C_LANE_INFO& LANE_INFO=C_LANE_INFO::getInstance();

C_HILINK_INFO::C_HILINK_INFO(){
	macroid_hilink_info_map.clear();
	macroid_storeid_map.clear();
	macroid_lane_info_map.clear();
	all_macroid.clear();
	macroid_PowerUpSeq_map.clear();
}

C_HILINK_INFO::~C_HILINK_INFO(){

}

void
C_HILINK_INFO::initial_info() const{
	static bool isInit=false;
	vector<int> power_up_seq;
	vector<int> power_dn_seq;
	string PowerUpSeq;
	string PowerDnSeq;
	if(!isInit){
		macroid_hilink_info_map.clear();
		macroid_storeid_map.clear();
		macroid_lane_info_map.clear();
		all_macroid.clear();
		macroid_PowerUpSeq_map.clear();
		macroid_PowerDnSeq_map.clear();

		for (INT midx = 0; midx < HILINK_MACRO_NUM; ++ midx)
		{
			power_up_seq.clear();
			power_dn_seq.clear();
			uint MacroID;
			T_HILINK_INFO Info;
			vector<T_LANE_INFO> lane_info;
			get_info(midx,MacroID,Info,PowerUpSeq,PowerDnSeq,lane_info);
			if(Info.Lane_Num <= 0 || Info.Lane_Num > HILINK_LANE_NUM || HILINK_LANE_NUM > 16){
//				cerr<<"Error: Lane Number on Macro"<<MacroID<<" is invalid! Check your UserConfig!"<<endl;
//				ERROR_EXIT(TM::ABORT_FLOW);
			}
			macroid_hilink_info_map.insert(pair<uint,T_HILINK_INFO>(MacroID,Info));
			macroid_storeid_map.insert(pair<uint,uint>(MacroID,midx));
			macroid_lane_info_map.insert(pair<uint,vector<T_LANE_INFO> >(MacroID,lane_info));
			all_macroid.push_back(MacroID);
			if(!PowerUpSeq.empty()){
				parseListOfInt(PowerUpSeq,power_up_seq);
				if(power_up_seq.size()>HILINK_LANE_NUM || power_up_seq.size()<Info.Lane_Num){
//					cerr<<"Error: Number on PowerUpSeq is invalid! Check your UserConfig!"<<endl;
//					ERROR_EXIT(TM::ABORT_FLOW);
				}
				for(uint i=0;i<power_up_seq.size();i++){
					if(power_up_seq[i]<0||power_up_seq[i]>=HILINK_LANE_NUM){
//						cerr<<"Error: Lane ID:"<<power_up_seq[i]<<" in PowerUpSeq is invalid! Check your UserConfig!"<<endl;
//						ERROR_EXIT(TM::ABORT_FLOW);
					}
				}
			}
			else{
				for(uint i=0;i<Info.Lane_Num;i++){
					power_up_seq.push_back(i);
				}
			}
			macroid_PowerUpSeq_map.insert(pair<uint,vector<int> >(MacroID,power_up_seq));

			if(!PowerDnSeq.empty()){
				parseListOfInt(PowerDnSeq,power_dn_seq);
				if(power_dn_seq.size()>HILINK_LANE_NUM || power_dn_seq.size()<Info.Lane_Num){
//					cerr<<"Error: Number on PowerUpSeq is invalid! Check your UserConfig!"<<endl;
//					ERROR_EXIT(TM::ABORT_FLOW);
				}
				for(uint i=0;i<power_dn_seq.size();i++){
					if(power_dn_seq[i]<0||power_dn_seq[i]>=HILINK_LANE_NUM){
//						cerr<<"Error: Lane ID:"<<power_dn_seq[i]<<" in PowerUpSeq is invalid! Check your UserConfig!"<<endl;
//						ERROR_EXIT(TM::ABORT_FLOW);
					}
				}
			}
			else{
				for(uint i=0;i<Info.Lane_Num;i++){
					power_dn_seq.push_back(Info.Lane_Num-i-1);
				}
			}
			macroid_PowerDnSeq_map.insert(pair<uint,vector<int> >(MacroID,power_dn_seq));
		}
		isInit=true;
	}
}


const T_HILINK_INFO&
C_HILINK_INFO::operator[](uint MacroID) const{
	return getHiLinkInfo(MacroID);
}

const T_HILINK_INFO&
C_HILINK_INFO::getHiLinkInfo(uint MacroID) const{//* id is MacroID
	const static T_HILINK_INFO dummy={CSL, CSL, 0, INVAILD_IP, 0, 0, 0, 0, 0};

	initial_info();
	if(macroid_hilink_info_map.find(MacroID) != macroid_hilink_info_map.end() && !macroid_hilink_info_map.empty()){
		return macroid_hilink_info_map.find(MacroID)->second;
	}
	else{
//		cerr<<"Error: MacroID: "<<MacroID<<" is invalid!"<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	return dummy;
}

const vector<int>&
C_HILINK_INFO::get_PowerUpSeq(uint MacroID) const{
	const static vector<int> dummy;
	initial_info();
	if(macroid_PowerUpSeq_map.find(MacroID) != macroid_PowerUpSeq_map.end() && !macroid_PowerUpSeq_map.empty()){
		return macroid_PowerUpSeq_map.find(MacroID)->second;
	}
	else{
//		cerr<<"Error: MacroID: "<<MacroID<<" is invalid!"<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	return dummy;
}

const vector<int>&
C_HILINK_INFO::get_PowerDnSeq(uint MacroID) const{
	const static vector<int> dummy;
	initial_info();
	if(macroid_PowerDnSeq_map.find(MacroID) != macroid_PowerDnSeq_map.end() && !macroid_PowerDnSeq_map.empty()){
		return macroid_PowerDnSeq_map.find(MacroID)->second;
	}
	else{
//		cerr<<"Error: MacroID: "<<MacroID<<" is invalid!"<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	return dummy;
}

const T_LANE_INFO&
C_HILINK_INFO::get_lane_info(uint MacroID,uint LaneID) const{//* id is SliceID
	const static T_LANE_INFO dummy={LANE_DISABLE,"","","","","",""};
	initial_info();
	if( macroid_lane_info_map.find(MacroID) != macroid_lane_info_map.end() &&
		!macroid_lane_info_map.empty() &&
		LaneID<HILINK_LANE_NUM)
	{
		return macroid_lane_info_map.find(MacroID)->second[LaneID];
	}
	else{
//		cerr<<"Error: MacroID: "<<MacroID<<" LaneID: "<<LaneID<<" is invalid!"<<endl;

//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	return dummy;
}


uint
C_HILINK_INFO::get_Macro_Store_ID(uint MacroID) const{
	initial_info();
	if(macroid_storeid_map.find(MacroID) != macroid_storeid_map.end() && !macroid_storeid_map.empty()){
		return macroid_storeid_map.find(MacroID)->second;
	}
	else{
//		cerr<<"Error: MacroID: "<<MacroID<<" is invalid!"<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	return 0xFFFF;
}

void
C_HILINK_INFO::get_AllMacroList(vector<uint>& list) const{
	list.clear();
	initial_info();
	list=all_macroid;
}

uint
C_HILINK_INFO::getFirstMacroID() const{
	initial_info();
	return all_macroid[0];
}

const T_MacroLaneID
C_LANE_INFO::get_MacroLaneID(const string& pin) const{
	T_MacroLaneID tmp={0xffffff,0xffffff};
	static bool isinit=false;
	static map<string,T_MacroLaneID> pin_map;
	if(!isinit){
		pin_map.clear();
		vector<uint> allmacrolist;
		HILINK_INFO.get_AllMacroList(allmacrolist);

		for (INT midx = 0; midx < allmacrolist.size(); ++ midx){
			uint MacroID=allmacrolist[midx];
			for (UINT LaneID = 0; LaneID < HILINK_INFO[MacroID].Lane_Num; ++ LaneID)
			{
				tmp.MacroID = MacroID;
				tmp.LaneID = LaneID;

				switch(LANE_INFO[MacroID][LaneID].type){
					case LANE_DISABLE:
						break;
					case LANE_RX_ONLY:
						if(!LANE_INFO[MacroID][LaneID].RX_N.empty() and !LANE_INFO[MacroID][LaneID].RX_P.empty()){
							pin_map[LANE_INFO[MacroID][LaneID].RX_N] = tmp;
							pin_map[LANE_INFO[MacroID][LaneID].RX_P] = tmp;
						}
						break;
					case LANE_TX_ONLY:
						if(!LANE_INFO[MacroID][LaneID].TX_N.empty() and !LANE_INFO[MacroID][LaneID].TX_P.empty()){
							pin_map[LANE_INFO[MacroID][LaneID].TX_N] = tmp;
							pin_map[LANE_INFO[MacroID][LaneID].TX_P] = tmp;
						}
						break;
					case LANE_BOTH:
						if(!LANE_INFO[MacroID][LaneID].RX_N.empty() and !LANE_INFO[MacroID][LaneID].RX_P.empty()){
							pin_map[LANE_INFO[MacroID][LaneID].RX_N] = tmp;
							pin_map[LANE_INFO[MacroID][LaneID].RX_P] = tmp;
						}
						if(!LANE_INFO[MacroID][LaneID].TX_N.empty() and !LANE_INFO[MacroID][LaneID].TX_P.empty()){
							pin_map[LANE_INFO[MacroID][LaneID].TX_N] = tmp;
							pin_map[LANE_INFO[MacroID][LaneID].TX_P] = tmp;
						}
						break;
					default:
						break;
				}
			}
		}
		isinit=true;
	}
	if(pin_map.find(pin) != pin_map.end() && !pin_map.empty()){
		return pin_map.find(pin)->second;
	}
	else{
//		cerr<<"Error: Can not find a Lane named "<<pin<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	tmp.MacroID=tmp.LaneID=0xffff;
	return tmp;
}

C_LANE_INFO::C_LANE_INFO(){

}

const C_LANE_INFO&
C_LANE_INFO::getInstance(){
	static C_LANE_INFO inst;
	return inst;
}
const C_LANE_INFO::LANE_INFO_ON_MACRO&
C_LANE_INFO::operator[](uint MacroID) const{
	lane_info_each_macro.MacroID=MacroID;
	return lane_info_each_macro;
}

C_LANE_INFO::LANE_INFO_ON_MACRO::LANE_INFO_ON_MACRO()
{
	MacroID=0xfffffff;
}

const T_LANE_INFO&
C_LANE_INFO::LANE_INFO_ON_MACRO::operator[](uint laneid) const{
	return HILINK_INFO.get_lane_info(MacroID,laneid);
}

void do_selectMacro_JTAG(d2s_IP_JTAG& the_jtag,unsigned long long DR0, unsigned long long DR1){
	const static unsigned long long IR0=HILINK_INFO[HILINK_INFO.getFirstMacroID()].IR0;
	const static unsigned long long IR1=HILINK_INFO[HILINK_INFO.getFirstMacroID()].IR1;
	const static unsigned long long IR2=HILINK_INFO[HILINK_INFO.getFirstMacroID()].IR2;


#ifdef __debug__
//	cout<<the_jtag.get_d2s_type()<<" DR0 = 0x"<<hex<<DR0<<" DR1 = 0x"<<DR1<<dec<<endl;
#endif
//	cout<<dec<<"do_selectMacro_JTAG #####################  IR0 ="<<IR0<<" DR0 ="<<DR0<<" IR1 ="<<IR1<<" DR1 ="<< DR1<<" IR2 ="<<IR2<<endl;

	the_jtag.setJtagMode("writeIR0");  //Jtag mode decide pattern cycle
	the_jtag.write_IRxDR0DR1(IR0);
	the_jtag.setJtagMode("writeDR0");
	the_jtag.write_IRxDR0DR1(DR0);

	the_jtag.setJtagMode("writeIR1");
	the_jtag.write_IRxDR0DR1(IR1);

	the_jtag.setJtagMode("writeDR1");
	the_jtag.write_IRxDR0DR1(DR1);

	the_jtag.setJtagMode("writeIR2");
	the_jtag.write_IRxDR0DR1(IR2);

	the_jtag.setJtagMode("writeDR2"); //tony check with V100 ,result is same like this ; 20210818
}

void do_selectMacro_AHB(d2s_IP_JTAG& the_jtag,uint MacroID,bool select_all){
#ifdef AHB_MODE
	the_jtag.getContext();

	string macro_select_label;
	if(select_all){
		macro_select_label=AHB_MACROALL_SEL;
	}
	else{
		if(MacroID==0){
			macro_select_label=AHB_MACRO0_SEL;
		}
		else if(MacroID==1){
			macro_select_label=AHB_MACRO1_SEL;
		}
		else{
//			cerr<<"Error: incorrect MacroID: "<<MacroID<<endl;
//			ERROR_EXIT(TM::ABORT_FLOW);
		}
	}

#ifdef __debug__
//	cout<<the_jtag.get_d2s_type()<<" execute label: "<<macro_select_label<<endl;
#endif

	the_jtag.setmacroid(MacroID);

	if (the_jtag.Context == "DEFAULT")
	{
		the_jtag.execLabel(macro_select_label+"_STD",3,false);
	}
	else if (the_jtag.Context == "FASTDIFF")
	{
		the_jtag.execLabel(macro_select_label+"_FASTDIFF",3,false);
	}

	the_jtag.setJtagMode("writeDR2");
#endif
}

#ifndef AHB_MODE
void selectMacro(INT macroid){
	if(HILINK_INFO[macroid].Lane_Num<=0){
//		ERROR_EXIT(TM::ABORT_FLOW);
	};//TODO
//	d2s_IP_JTAG::pre_d2s_Instance().set_address_synchronized_flag("MACRO_SELECTED",0);
	HILINK_Regs_Base::setAutoReadbackMacroLane(macroid,0);
	do_selectMacro_JTAG(d2s_JTAG::Instance(),HILINK_INFO[macroid].DR0,HILINK_INFO[macroid].DR1);

}

void selectMacro_MB(const MACRO_LANE_SEL& MacroLane_Sel){
	uint macroid;
	//cout<<MacroLane_Sel.size()<<endl;
	if(MacroLane_Sel.size()<1){
//		cerr<<"Error: No Macro is selected!"<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	for(uint i=0;i<MacroLane_Sel.size();i++){//TODO
		macroid=MacroLane_Sel[i].MacroID;

		if(HILINK_INFO[macroid].Lane_Num<=0){
//			ERROR_EXIT(TM::ABORT_FLOW);
		};//TODO
	}
//	d2s_IP_JTAG::pre_d2s_Instance().set_address_synchronized_flag("MACRO_SELECTED",0);
	HILINK_Regs_Base::setAutoReadbackMacroLane(MacroLane_Sel);

	unsigned long long DR0=0;
	uint MacroID;
	for(uint i=0;i<MacroLane_Sel.size();i++){
		MacroID=MacroLane_Sel[i].MacroID;
		DR0|=HILINK_INFO[MacroID].DR0;
	}

	uint first_macroid=MacroLane_Sel[0].MacroID;
	do_selectMacro_JTAG(d2s_JTAG::Instance(),DR0,HILINK_INFO[first_macroid].DR1);
}
#else
void selectMacro(INT macroid){

	if(HILINK_INFO[macroid].Lane_Num<=0){
//		ERROR_EXIT(TM::ABORT_FLOW);
	};//TODO
	d2s_IP_JTAG::pre_d2s_Instance().set_address_synchronized_flag("MACRO_SELECTED",0);
	HILINK_Regs_Base::setAutoReadbackMacroLane(macroid,0);
	do_selectMacro_AHB(d2s_JTAG::Instance(),macroid,false);

}

void selectMacro_MB(const MACRO_LANE_SEL& MacroLane_Sel){
	uint macroid;
	//cout<<MacroLane_Sel.size()<<endl;
	if(MacroLane_Sel.size()<1){
//		cerr<<"Error: No Macro is selected!"<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	for(uint i=0;i<MacroLane_Sel.size();i++){//TODO
		macroid=MacroLane_Sel[i].MacroID;

		if(HILINK_INFO[macroid].Lane_Num<=0){
//			ERROR_EXIT(TM::ABORT_FLOW);
		};//TODO
	}
	d2s_IP_JTAG::pre_d2s_Instance().set_address_synchronized_flag("MACRO_SELECTED",0);
	HILINK_Regs_Base::setAutoReadbackMacroLane(MacroLane_Sel);
	do_selectMacro_AHB(d2s_JTAG::Instance(),MacroLane_Sel[0].MacroID,MacroLane_Sel.size()>1);
}
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef AHB_MODE
void pred2s_selectMacro(INT macroid){
	do_selectMacro_JTAG(d2s_JTAG::pre_d2s_Instance(),HILINK_INFO[macroid].DR0,HILINK_INFO[macroid].DR1);
}

void pred2s_selectMacro_MB(const MACRO_LANE_SEL& MacroLane_Sel){
	if(MacroLane_Sel.size()<1){
//		cerr<<"Error: No Macro is selected!"<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	unsigned long long DR0=0;
	uint MacroID;
	for(uint i=0;i<MacroLane_Sel.size();i++){
		MacroID=MacroLane_Sel[i].MacroID;
		DR0|=HILINK_INFO[MacroID].DR0;
	}

	uint first_macroid=MacroLane_Sel[0].MacroID;
	do_selectMacro_JTAG(d2s_JTAG::pre_d2s_Instance(),DR0,HILINK_INFO[first_macroid].DR1);
}
#else
void pred2s_selectMacro(INT macroid){
	do_selectMacro_AHB(d2s_JTAG::pre_d2s_Instance(),macroid,false);
}

void pred2s_selectMacro_MB(const MACRO_LANE_SEL& MacroLane_Sel){
	if(MacroLane_Sel.size()<1){
//		cerr<<"Error: No Macro is selected!"<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	do_selectMacro_AHB(d2s_JTAG::pre_d2s_Instance(),MacroLane_Sel[0].MacroID,MacroLane_Sel.size()>1);
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef AHB_MODE
void csr_check_selectMacro(INT macroid){
	do_selectMacro_JTAG(d2s_JTAG::Instance(),HILINK_INFO[macroid].DR0,HILINK_INFO[macroid].DR1);
}

void sync_CSR_selectMacro_MB(const MACRO_LANE_SEL& MacroLane_Sel) {
	if(MacroLane_Sel.size()<1){
//		cerr<<"Error: No Macro is selected!"<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	unsigned long long DR0=0;
	uint MacroID;
	for(uint i=0;i<MacroLane_Sel.size();i++){
		MacroID=MacroLane_Sel[i].MacroID;
		DR0|=HILINK_INFO[MacroID].DR0;
	}

	uint first_macroid=MacroLane_Sel[0].MacroID;
	do_selectMacro_JTAG(d2s_JTAG::pre_d2s_Instance(),DR0,HILINK_INFO[first_macroid].DR1);
}


void csr_check_selectMacro_MB(const MACRO_LANE_SEL& MacroLane_Sel){
	if(MacroLane_Sel.size()<1){
//		cerr<<"Error: No Macro is selected!"<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	unsigned long long DR0=0;
	uint MacroID;
	for(uint i=0;i<MacroLane_Sel.size();i++){
		MacroID=MacroLane_Sel[i].MacroID;
		DR0|=HILINK_INFO[MacroID].DR0;
	}

	uint first_macroid=MacroLane_Sel[0].MacroID;
	do_selectMacro_JTAG(d2s_JTAG::Instance(),DR0,HILINK_INFO[first_macroid].DR1);
}
#else
void csr_check_selectMacro(INT macroid){
	do_selectMacro_AHB(d2s_JTAG::Instance(),macroid,false);
}

void csr_check_selectMacro_MB(const MACRO_LANE_SEL& MacroLane_Sel){
	if(MacroLane_Sel.size()<1){
//		cerr<<"Error: No Macro is selected!"<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	do_selectMacro_AHB(d2s_JTAG::Instance(),MacroLane_Sel[0].MacroID,MacroLane_Sel.size()>1);
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void selectMacro_Now(INT macroid){
    d2s::d2s_LABEL_BEGIN( "MPB_SEL_MACRO", Global_D2S_Mode);
            selectMacro(macroid);
    d2s::d2s_LABEL_END();
}

void selectMacro_Now_MB(const MACRO_LANE_SEL& MacroLane_Sel){
//	D2S_FRAMEWORK;
//	fr.d2s_LABEL_BEGIN("MPB_SEL_MACROs",d2sFrameWorkModeType::Enum(d2s_mode));
//		selectMacro_MB(MacroLane_Sel);
//	fr.d2s_LABEL_END();
}

void Select_Macro_Lane(MACRO_LANE_SEL& sel,const STRING& macrolist,const STRING& pinlist){

	sel.clear();

	map<uint,uint> sel_flg;//<MacroID, SliceID(bit0~15)>
	sel_flg.clear();

	vector<uint> allmacrolist;
	HILINK_INFO.get_AllMacroList(allmacrolist);

	for (uint i = 0; i < allmacrolist.size(); i++)
	{
		uint MacroID=allmacrolist[i];
		sel_flg[MacroID]=0;//* SliceID initial to 0x0000
	}

	set<uint> macrolistset;
	INT_VECTOR	keeporder_MacroList;

	INT macro,lane;
	if (macrolist == "FromPinList")
	{
		STRING_VECTOR 		pinNameList;
//		pinNameList = PinUtility.getDigitalPinNamesFromPinList(pinlist, TM::ALL_DIGITAL, TRUE,TRUE);
		T_MacroLaneID tmp;
		for (UINT i = 0; i < pinNameList.size(); ++ i)
		{
			tmp=LANE_INFO.get_MacroLaneID(pinNameList[i]);
			sel_flg[tmp.MacroID] |= (1<<tmp.LaneID);
			if(macrolistset.find(tmp.MacroID) == macrolistset.end()){
				macrolistset.insert(tmp.MacroID);
				keeporder_MacroList.push_back(tmp.MacroID);
			}
		}
	}
	else
	{
		INT_VECTOR			vMacroList;
		parseListOfInt(macrolist,vMacroList,',');//* string transfer to int vector

		for (UINT i = 0; i < vMacroList.size(); ++ i)
		{
			uint MacroID=vMacroList[i];
			if(macrolistset.find(MacroID) == macrolistset.end()){
				macrolistset.insert(MacroID);
				keeporder_MacroList.push_back(MacroID);
			}
			for(int j=0;j<HILINK_INFO[MacroID].Lane_Num;++j)
			{
				if(LANE_INFO[MacroID][j].type!=LANE_DISABLE){
					sel_flg[MacroID] |= (1<<j);
				}
			}
			sel_flg[MacroID] |= 0x10000;
		}
	}
	//cout<<"MACROLANESEL"<<endl;
	T_MACRO_LANE_SEL 	sel_item;
	for (uint i=0;i<keeporder_MacroList.size();i++){
		map<uint,uint>::iterator itr=sel_flg.find(keeporder_MacroList[i]);
		if(itr->second & 0x1FFFF){
			sel_item.MacroID = itr->first;
			sel_item.SliceID=0;
			sel_item.vLane.clear();
			for (UINT j = 0; j < HILINK_INFO[itr->first].Lane_Num; ++ j)
			{
				if (itr->second & (1<<j))
				{
					sel_item.vLane.push_back(j);
				}
			}
			//cout<<"\t"<<itr->first<<endl;
			sel.push_back(sel_item);//* store each Macro and correspond enabledSliceID
		}
	}

	if (sel.size() == 0)
	{
//		cout << "!!!No valid MacroID has been selected. Please reconfirm it!!!" << endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
}

void Select_Macro_Lane(MACRO_LANE_SEL& sel,const vector<string>& list){
	sel.clear();
	sel.clear();

	map<uint,uint> sel_flg;//<MacroID, SliceID(bit0~15)>
	sel_flg.clear();

	vector<uint> allmacrolist;
	HILINK_INFO.get_AllMacroList(allmacrolist);


	for (uint i = 0; i < allmacrolist.size(); i++)
	{
		uint MacroID=allmacrolist[i];
		sel_flg[MacroID]=0;//* SliceID initial to 0x0000
	}

	set<uint> macrolistset;
	INT_VECTOR	keeporder_MacroList;
//        vector<INT> keeporder_MacroList;
        
	INT macro,lane;
	T_MacroLaneID tmp;
	for (UINT i = 0; i < list.size(); ++ i)
	{
		tmp=LANE_INFO.get_MacroLaneID(list[i]);
		sel_flg[tmp.MacroID] |= (1<<tmp.LaneID);
		if(macrolistset.find(tmp.MacroID) == macrolistset.end()){
			macrolistset.insert(tmp.MacroID);
			keeporder_MacroList.push_back(tmp.MacroID);
		}
	}

	T_MACRO_LANE_SEL 	sel_item;
	for (uint i=0;i<keeporder_MacroList.size();i++){
		map<uint,uint>::iterator itr=sel_flg.find(keeporder_MacroList[i]);
		if(itr->second & 0x1FFFF){
			sel_item.MacroID = itr->first;
			sel_item.SliceID=0;
			sel_item.vLane.clear();
			for (UINT j = 0; j < HILINK_INFO[itr->first].Lane_Num; ++ j)
			{
				if (itr->second & (1<<j))
				{
					sel_item.vLane.push_back(j);
				}
			}
			sel.push_back(sel_item);//* store each Macro and correspond enabledSliceID
		}
	}

	if (sel.size() == 0)
	{
//		cout << "!!!No valid MacroID has been selected. Please reconfirm it!!!" << endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
}

