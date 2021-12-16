/*
 * PatternCreate.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: yanfen.fang
 */

#include <SRC_d2s/PatternCreate.h>

#include <Common_Func/System_Common_Func.h>

void create_wait_pattern(const string& label,uint cycle,const T_MAIN_PATTERN_DATA& patinfo){
//	fwout<<"SQLB? \""<<label<<"\",MAIN,("<<patinfo.port<<")"<<endl;
//	if(fwresult.size()>0){
//		return;
//	}
//	fwout<<"DMAS? MFRE, SM ,(@)"<<endl;
//	int free_mem=fwresult[0].getIntParam(2);
//	if(free_mem<8+32){
//		cerr<<"Error: no enough memory to create pattern!"<<endl;
//		//ERROR_EXIT(TM::ABORT_FLOW);
//	}
//
//	fwout<<"SAOF APP"<<endl;
//	fwout<<"DMAS PARA,SM,8,("<<patinfo.port<<")"<<endl;
//	fwout<<"DMAS SQPG,SM,4,("<<patinfo.port<<")"<<endl;
//	fwout<<"SQLB \""<<label<<"\",MAIN,0,3,\""<<patinfo.wavetable<<"\",("<<patinfo.port<<")"<<endl;
//	fwout<<"SQLA LBL,\""<<label<<"\",\"PARA_MEM=SM,PARA_MCTX="<<patinfo.context<<"\",("<<patinfo.port<<")"<<endl;
//	fwout<<"SQPG 0,STVA,0,,,("<<patinfo.port<<")"<<endl;
//	fwout<<"SQPG 1,STSA,,,,("<<patinfo.port<<")"<<endl;
//	fwout<<"SQPG 2,RPTV,1,"<<cycle<<",,("<<patinfo.port<<")"<<endl;
//	fwout<<"SQPG 3,STOP,,,,("<<patinfo.port<<")"<<endl;
//	for(map<string,string>::const_iterator itr=patinfo.pattern_data.begin();itr!=patinfo.pattern_data.end();itr++){
//		string the_pin=itr->first;
//		string the_vec;
//		the_vec.clear();
//		if(itr->second.length()<1){
//			cerr<<"Error: pattern data is invalid during create main pattern \""<<label<<"\" on pin \""<<the_pin<<"\"!"<<endl;
//			the_vec.resize(8,'\0');
//		}
//		the_vec.resize(8,itr->second[0]);
//		fwout<<"VECD PARA,SM,0,8,("<<the_pin<<"),"<<"#18"<<the_vec<<endl;
//	}
//	fwout<<"SAOF ZERO"<<endl;
}

void create_all_nop_pattern(const string& label,const T_MAIN_PATTERN_DATA& patinfo){
//	fwout<<"sqlb? \""<<label<<"\",MAIN,("<<patinfo.port<<")"<<endl;
//	if(fwresult.size()>0){
//		return;
//	}
//	fwout<<"DMAS? MFRE, SM ,(@)"<<endl;
//	int free_mem=fwresult[0].getIntParam(2);
//	if(free_mem<patinfo.size+32){
//		cerr<<"Error: no enough memory to create pattern!"<<endl;
//		//ERROR_EXIT(TM::ABORT_FLOW);
//	}
//	ostringstream vecd_head;
//	vecd_head<<"#9"<<setfill('0')<<setw(9)<<patinfo.size;
//	fwout<<"SAOF APP"<<endl;
//	fwout<<"DMAS PARA,SM,"<<patinfo.size<<",("<<patinfo.port<<")"<<endl;
//	fwout<<"DMAS SQPG,SM,4,("<<patinfo.port<<")"<<endl;
//	fwout<<"SQLB \""<<label<<"\",MAIN,0,3,\""<<patinfo.wavetable<<"\",("<<patinfo.port<<")"<<endl;
//	fwout<<"SQLA LBL,\""<<label<<"\",\"PARA_MEM=SM,PARA_MCTX="<<patinfo.context<<"\",("<<patinfo.port<<")"<<endl;
//	fwout<<"SQPG 0,STVA,0,,,("<<patinfo.port<<")"<<endl;
//	fwout<<"SQPG 1,STSA,,,,("<<patinfo.port<<")"<<endl;
//	fwout<<"SQPG 2,GENV,"<<patinfo.size<<",,,("<<patinfo.port<<")"<<endl;
//	fwout<<"SQPG 3,STOP,,,,("<<patinfo.port<<")"<<endl;
//	for(map<string,string>::const_iterator itr=patinfo.pattern_data.begin();itr!=patinfo.pattern_data.end();itr++){
//		string the_pin=itr->first;
//		string the_vec=itr->second;
//		if(the_vec.length()!=patinfo.size){
//			cerr<<"Error: pattern data is invalid during create main pattern \""<<label<<"\" on pin \""<<the_pin<<"\"!"<<endl;
//			the_vec.clear();
//			the_vec.append(patinfo.size,'\0');
//		}
//		fwout<<"VECD PARA,SM,0,"<<patinfo.size<<",("<<the_pin<<"),"<<vecd_head.str()<<the_vec<<endl;
//	}
//	fwout<<"SAOF ZERO"<<endl;
}
