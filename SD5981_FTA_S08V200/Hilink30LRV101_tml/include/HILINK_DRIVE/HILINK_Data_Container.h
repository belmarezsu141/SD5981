/*
 * HILINK_Data_Container.h
 *
 *  Created on: Oct 19, 2016
 *      Author: yanfen.fang
 */

#ifndef HILINK_DATA_CONTAINER_H_
#define HILINK_DATA_CONTAINER_H_
//using namespace V93kLimits;
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>

#include <HILINK_DRIVE/HiLink_Regs_Base.h>

template<class T> class HILINK_LANE_DATA_CONTAINER{
public:
	class HILINK_EACH_LANE_DATA_CONTAINER{
		private:
			T buffer[HILINK_LANE_NUM];
		public:
			T& operator[](uint id){
				if(id>=HILINK_LANE_NUM){
//					cerr<<"Error: Lane ID: "<<dec<<id<<" is invalid!"<<endl;
///					ERROR_EXIT(TM::ABORT_FLOW);
				}
				return buffer[id];
			}
			void init(const T& val){
				for(uint i=0;i<HILINK_LANE_NUM;i++){
					buffer[i]=val;
				}
			}
			void init(uint size,int val){
				for(uint i=0;i<HILINK_LANE_NUM;i++){
					buffer[i].resize(size);
//					buffer[i].init(val);
				}
			}
			void init(uint size,double val){
				for(uint i=0;i<HILINK_LANE_NUM;i++){
					buffer[i].resize(size);
					buffer[i].init(val);
				}
			}
			void operator=(const T& val){
				init(val);
			}
	};
	typedef HILINK_EACH_LANE_DATA_CONTAINER LANE_DATA_ON_MACRO;
private:
	LANE_DATA_ON_MACRO lane_on_macro[HILINK_MACRO_NUM];
public:
	LANE_DATA_ON_MACRO& operator[](uint MacroID){
		MacroID=HILINK_INFO.get_Macro_Store_ID(MacroID);
		return lane_on_macro[MacroID];
	}
	void init(const T& val){
		for(uint i=0;i<HILINK_MACRO_NUM;i++){
			lane_on_macro[i].init(val);
		}
	}
	void init(uint size,int val){
		for(uint i=0;i<HILINK_MACRO_NUM;i++){
			lane_on_macro[i].init(size,val);
		}
	}
	void init(uint size,double val){
		for(uint i=0;i<HILINK_MACRO_NUM;i++){
			lane_on_macro[i].init(size,val);
		}
	}
	void operator=(const T& val){
		init(val);
	}
	string toString(const MACRO_LANE_SEL& MacroLane_Sel){
		ostringstream str;
		for(uint midx=0;midx<MacroLane_Sel.size();midx++){
			uint MacroID=MacroLane_Sel[midx].MacroID;
			const vector<uint>& vLane=MacroLane_Sel[midx].vLane;
			str<<"Macro("<<MacroID<<"):"<<endl;
			uint macrostoreid=HILINK_INFO.get_Macro_Store_ID(MacroID);
			for(uint lidx=0;lidx<vLane.size();lidx++){
				uint LaneID=vLane[lidx];
				str<<"\tLane("<<LaneID<<"): "<<lane_on_macro[macrostoreid][LaneID]<<endl;
			}
		}
		return str.str();
	}
};


template<class T> class HILINK_MACRO_DATA_CONTAINER{
private:
	T buffer[HILINK_MACRO_NUM];
public:
	T& operator[](uint MacroID){
		MacroID=HILINK_INFO.get_Macro_Store_ID(MacroID);
		return buffer[MacroID];
	}
	void operator=(const T& val){
		init(val);
	}
	void init(const T& val){
		for(uint i=0;i<HILINK_MACRO_NUM;i++){
			buffer[i]=val;
		}
	}
	void init(uint size,int val){
		for(uint i=0;i<HILINK_MACRO_NUM;i++){
			buffer[i].resize(size);
//			buffer[i].init(val);
		}
	}
	void init(uint size,double val){
		for(uint i=0;i<HILINK_MACRO_NUM;i++){
			buffer[i].resize(size);
			buffer[i].init(val);
		}
	}
	string toString(const MACRO_LANE_SEL& MacroLane_Sel){
		ostringstream str;
		for(uint midx=0;midx<MacroLane_Sel.size();midx++){
			uint MacroID=MacroLane_Sel[midx].MacroID;
			uint macrostoreid=HILINK_INFO.get_Macro_Store_ID(MacroID);
			str<<"Macro("<<MacroID<<"): "<<buffer[macrostoreid]<<endl;
		}
		return str.str();
	}
};

template<class T> class HILINK_SITE_DATA_CONTAINER{
private:
	T buffer[HILINK_SITE_NUMBER];
public:
	T& operator[](uint id){
		if(id>=HILINK_SITE_NUMBER){
//			cerr<<"Error: Site Number: "<<dec<<(id+1)<<" is invalid!"<<endl;
//			ERROR_EXIT(TM::ABORT_FLOW);
		}
		//id=HILINK_INFO.get_Macro_Store_ID(id);
		return buffer[id];
	}
//	T& operator()(uint id){
//		if(id>HILINK_SITE_NUMBER){
//			cerr<<"Error: Site Number: "<<dec<<id<<" is invalid!"<<endl;
//			ERROR_EXIT(TM::ABORT_FLOW);
//		}
//		//id=HILINK_INFO.get_Macro_Store_ID(id);
//		id--;
//		return buffer[id];
//	}
	void init(const T& val){//* used to int/double
		for(uint i=0;i<HILINK_SITE_NUMBER;i++){
			buffer[i]=val;
		}
	}
	void init(uint size,int val){//* used to ARRAY_I
		for(uint i=0;i<HILINK_SITE_NUMBER;i++){
			buffer[i].resize(size);
			buffer[i].init(val);
		}
	}
	void init(uint size,double val){//* used to ARRAY_D
		for(uint i=0;i<HILINK_SITE_NUMBER;i++){
			buffer[i].resize(size);
			buffer[i].init(val);
		}
	}
	void operator=(const T& val){
		init(val);
	}
	void judge(const MACRO_LANE_SEL& MacroLane_Sel,JUDGE_PIN judge_pin,const string& testname){
		//  uint site_id=CURRENT_SITE_NUMBER()-1;
		//if(MacroLane_Sel.size()<1){
		//	cerr<<"Error: at least 1 Macro 1Lane should be tested!"<<endl;
		  //	ERROR_EXIT(TM::ABORT_FLOW);
		//}
//		uint MacroID=MacroLane_Sel[0].MacroID;
//		uint LaneID=MacroLane_Sel[0].vLane[0];
//		string JudgePin;
//		switch(judge_pin){
//			case PIN_RXP:
//				JudgePin=LANE_INFO[MacroID][LaneID].RX_P;
//				break;
//			case PIN_RXN:
//				JudgePin=LANE_INFO[MacroID][LaneID].RX_N;
//				break;
//			case PIN_TXP:
//				JudgePin=LANE_INFO[MacroID][LaneID].TX_P;
//				break;
//			case PIN_TXN:
//				JudgePin=LANE_INFO[MacroID][LaneID].TX_N;
//				break;
//			default:
//				JudgePin="";
//				break;
//		}
//		TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePin, testname, tmLimits, buffer[site_id]);
	}
//TODO: 转长川API
	string toString(){
		string str;
		//FOR_EACH_SITE_BEGIN();
			//uint site_id=CURRENT_SITE_NUMBER()-1;
			//str<<"Site("<<(site_id+1)<<"): "<<buffer[site_id]<<endl;
		///FOR_EACH_SITE_END();
		return str;//"string";/str.str();
	}
};

template<class T> class HILINK_SITE_MACRO_DATA_CONTAINER{
private:
	HILINK_MACRO_DATA_CONTAINER<T> buffer[HILINK_SITE_NUMBER];
public:
	HILINK_MACRO_DATA_CONTAINER<T>& operator[](uint id){
		if(id>=HILINK_SITE_NUMBER){
//			cerr<<"Error: Site Number: "<<dec<<(id+1)<<" is invalid!"<<endl;
//			ERROR_EXIT(TM::ABORT_FLOW);
		}
		//id=HILINK_INFO.get_Macro_Store_ID(id);
		return buffer[id];
	}
	void init(const T& val){
		for(uint i=0;i<HILINK_SITE_NUMBER;i++){
			buffer[i].init(val);
		}
	}
	void init(uint size,int val){
		for(uint i=0;i<HILINK_SITE_NUMBER;i++){
			buffer[i].init(size,val);
		}
	}
	void init(uint size,double val){
		for(uint i=0;i<HILINK_SITE_NUMBER;i++){
			buffer[i].init(size,val);
		}
	}
	void operator=(const T& val){
		init(val);
	}
        //TODO: 转长川API
	void assign_ReadBack(const MACRO_LANE_SEL& MacroLane_Sel,const T_REG_INFO_EX& reg,uint csrindex,const string& prefix_id=""){
		//FOR_EACH_SITE_BEGIN();
		//	uint site_id=CURRENT_SITE_NUMBER()-1;
//			for(uint i=0;i<MacroLane_Sel.size();i++){
//				uint MacroID=MacroLane_Sel[i].MacroID;
//				uint SliceID=MacroLane_Sel[i].SliceID;
//				ostringstream str;
//				str<<prefix_id<<"_"<<reg.parent.getName()<<"_CSR"<<csrindex<<"_M"<<dec<<MacroID<<dec<<"_L"<<dec<<SliceID;
//				d2s_JTAG & jtag = d2s_JTAG::Instance();
//				buffer[site_id][MacroID]=HILINK_Regs_Base::get_bits((uint)jtag.getReadValue(str.str()),reg);
//			}
		//FOR_EACH_SITE_END();
	}
	void assign_ReadBack(const MACRO_LANE_SEL& MacroLane_Sel,const HILINK_Regs_Base& reg,uint csrindex,const string& prefix_id=""){
		//FOR_EACH_SITE_BEGIN();
		//	uint site_id=CURRENT_SITE_NUMBER()-1;
		//	for(uint i=0;i<MacroLane_Sel.size();i++){
		//		uint MacroID=MacroLane_Sel[i].MacroID;
		//		uint SliceID=MacroLane_Sel[i].SliceID;
		//		ostringstream str;
		//		str<<prefix_id<<"_"<<reg.getName()<<"_CSR"<<csrindex<<"_M"<<dec<<MacroID<<dec<<"_L"<<dec<<SliceID;
		//		d2s_JTAG & jtag = d2s_JTAG::Instance();
		//		buffer[site_id][MacroID]=(uint)jtag.getReadValue(str.str());
		//	}
		//FOR_EACH_SITE_END();
	}
	void judge(const MACRO_LANE_SEL& MacroLane_Sel,JUDGE_PIN judge_pin,const string& testname){
		//uint site_id=CURRENT_SITE_NUMBER()-1;
		//ARRAY_D tmp;
		//vector<string> JudgePins;
		//tmp.resize(MacroLane_Sel.size());
		//if(MacroLane_Sel.size()<1){
		//	cerr<<"Error: at least 1 Macro 1Lane should be tested!"<<endl;
		//	ERROR_EXIT(TM::ABORT_FLOW);
		//}
//		for(uint i=0;i<MacroLane_Sel.size();i++){
//			uint MacroID=MacroLane_Sel[i].MacroID;
//			uint LaneID=MacroLane_Sel[i].vLane[0];
//			JudgePins.clear();
//
//			tmp[i]=buffer[site_id][MacroID];
//			switch(judge_pin){
//				case PIN_RXP:
//					JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_P);
//					break;
//				case PIN_RXN:
//					JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_N);
//					break;
//				case PIN_TXP:
//					JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);
//					break;
//				case PIN_TXN:
//					JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_N);
//					break;
//				default:
//					JudgePins.push_back("");
//					break;
//			}
//		}
		//TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, testname, tmLimits, tmp);
	}
	string toString(const MACRO_LANE_SEL& MacroLane_Sel){
		//ostringstream str;
		//FOR_EACH_SITE_BEGIN();
		//	uint site_id=CURRENT_SITE_NUMBER()-1;
		//	str<<"Site("<<(site_id+1)<<"):"<<endl;
//			for(uint midx=0;midx<MacroLane_Sel.size();midx++){
//				uint MacroID=MacroLane_Sel[midx].MacroID;
//				str<<"\tMacro("<<MacroID<<"): "<<buffer[site_id][MacroID]<<endl;
//			}
		//FOR_EACH_SITE_END();
//		return str.str();
		return "";
	}

};

template<class T> class HILINK_SITE_LANE_DATA_CONTAINER{
private:
	HILINK_LANE_DATA_CONTAINER<T> buffer[HILINK_SITE_NUMBER];
public:
	HILINK_LANE_DATA_CONTAINER<T>& operator[](uint id){
		if(id>=HILINK_SITE_NUMBER){
//			cerr<<"Error: Site Number: "<<dec<<(id+1)<<" is invalid!"<<endl;
		//	ERROR_EXIT(TM::ABORT_FLOW);
		}
		//id=HILINK_INFO.get_Macro_Store_ID(id);
		return buffer[id];
	}
	void init(const T& val){
		for(uint i=0;i<HILINK_SITE_NUMBER;i++){
			buffer[i].init(val);
		}
	}
	void init(uint size,int val){
		for(uint i=0;i<HILINK_SITE_NUMBER;i++){
			buffer[i].init(size,val);
		}
	}
	void init(uint size,double val){
		for(uint i=0;i<HILINK_SITE_NUMBER;i++){
			buffer[i].init(size,val);
		}
	}
	void operator=(const T& val){
		init(val);
	}
	void assign_ReadBack(const MACRO_LANE_SEL& MacroLane_Sel,const HILINK_Regs_Base& reg,uint csrindex,const string& prefix_id=""){
		//FOR_EACH_SITE_BEGIN();
		//	uint site_id=CURRENT_SITE_NUMBER()-1;
//			for(uint i=0;i<MacroLane_Sel.size();i++){
//				uint MacroID=MacroLane_Sel[i].MacroID;
//				const vector<uint>& vLane=MacroLane_Sel[i].vLane;
//				for(uint j=0;j<vLane.size();j++){
//					uint LaneID=vLane[j];
//					ostringstream str;
//					str<<prefix_id<<"_"<<reg.getName()<<"_CSR"<<csrindex<<"_M"<<dec<<MacroID<<dec<<"_L"<<dec<<LaneID;
//					d2s_JTAG & jtag = d2s_JTAG::Instance();
//					buffer[site_id][MacroID][LaneID]=(uint)jtag.getReadValue(str.str());
//				}
//			}
		//FOR_EACH_SITE_END();
	}
	void assign_ReadBack(const MACRO_LANE_SEL& MacroLane_Sel,const T_REG_INFO_EX& reg,uint csrindex,const string& prefix_id=""){
		//FOR_EACH_SITE_BEGIN();
		//	uint site_id=CURRENT_SITE_NUMBER()-1;
//			for(uint i=0;i<MacroLane_Sel.size();i++){
//				uint MacroID=MacroLane_Sel[i].MacroID;
//				const vector<uint>& vLane=MacroLane_Sel[i].vLane;
//				for(uint j=0;j<vLane.size();j++){
//					uint LaneID=vLane[j];
//					ostringstream str;
//					str<<prefix_id<<"_"<<reg.parent.getName()<<"_CSR"<<csrindex<<"_M"<<dec<<MacroID<<dec<<"_L"<<dec<<LaneID;
//					d2s_JTAG & jtag = d2s_JTAG::Instance();
//					buffer[site_id][MacroID][LaneID]=HILINK_Regs_Base::get_bits((uint)jtag.getReadValue(str.str()),reg);
//				}
//			}
		//FOR_EACH_SITE_END();
	}
	void judge(const MACRO_LANE_SEL& MacroLane_Sel,JUDGE_PIN judge_pin,const string& testname){
		//uint site_id=CURRENT_SITE_NUMBER()-1;
		//ARRAY_D tmp;
//               vector<double> tmp;
//		vector<string> JudgePins;
//		if(MacroLane_Sel.size()<1){
//			cerr<<"Error: at least 1 Macro 1Lane should be tested!"<<endl;
//			//ERROR_EXIT(TM::ABORT_FLOW);
//		}
//		for(uint i=0;i<MacroLane_Sel.size();i++){
//			uint MacroID=MacroLane_Sel[i].MacroID;
//			const vector<uint>& vLane=MacroLane_Sel[i].vLane;
//			tmp.resize(vLane.size());
//			JudgePins.clear();
//			for(uint j=0;j<vLane.size();j++){
//				uint LaneID=vLane[j];
//				tmp[j]=buffer[site_id][MacroID][LaneID];
//				switch(judge_pin){
//					case PIN_RXP:
//						JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_P);
//						break;
//					case PIN_RXN:
//						JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_N);
//						break;
//					case PIN_TXP:
//						JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);
//						break;
//					case PIN_TXN:
//						JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_N);
//						break;
//					default:
//						JudgePins.push_back("");
//						break;
//				}
//			}
//			TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, testname, tmLimits, tmp);
//		}
	}
	string toString(const MACRO_LANE_SEL& MacroLane_Sel){
		//ostringstream str1;
//		FOR_EACH_SITE_BEGIN();
//			uint site_id=CURRENT_SITE_NUMBER()-1;
//			str<<"Site("<<(site_id+1)<<"):"<<endl;
//			for(uint midx=0;midx<MacroLane_Sel.size();midx++){
//				uint MacroID=MacroLane_Sel[midx].MacroID;
//				const vector<uint>& vLane=MacroLane_Sel[midx].vLane;
//				str<<"\tMacro("<<MacroID<<"):"<<endl;
//				for(uint lidx=0;lidx<vLane.size();lidx++){
//					uint LaneID=vLane[lidx];
//					str<<"\t\tLane("<<LaneID<<"): "<<buffer[site_id][MacroID][LaneID]<<endl;
//				}
//			}
//		FOR_EACH_SITE_END();
		//return str1.str();
	}
};

#endif /* HILINK_DATA_CONTAINER_H_ */
