/*
 * d2s_status.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: yanfen.fang
 */

#include <SRC_d2s/d2s_status.h>

#include <Common_Func/System_Common_Func.h>
#include <SRC_d2s/md5_pack.h>

namespace std {


d2s_status::d2s_status() {
	// TODO Auto-generated constructor stub

}

d2s_status::~d2s_status() {
	// TODO Auto-generated destructor stub
}


map<string,string> d2s_status::status;
string d2s_status::last_suitename="";

void
d2s_status::check_suite_change(){
	string suitename;
//	GET_TESTSUITE_NAME(suitename);
	if(suitename != last_suitename){
		status.clear();
		string answer;
		string Context;
//		FW_TASK("GCTX? CURR,",answer);
		Context = answer.substr(12,answer.size()-14);
		status["CTX"]=Context;
	}
	last_suitename = suitename;
}
void
d2s_status::set_status(const string& id,const string& val){
	check_suite_change();
	status[id]=val;
}

void
d2s_status::delete_status(const string& id){
	if(status.find(id)!=status.end()){
		status.erase(id);
	}
}

string
d2s_status::get_status(){
	check_suite_change();
	string rtn="";
	for(map<string,string>::iterator it=status.begin();it!=status.end();it++){
		rtn+="~"+it->first+":"+it->second;
	}
	if(hout.getLevel()&0x80){
		//hout(GENERAL)<<"d2s status: "<<rtn<<endl;
	}
	if(rtn.length()>64){
		rtn="_"+get_MD5(rtn);
	}
	return rtn;
}
bool
d2s_status::isStatusAvailable(const string& id,string& result){
	check_suite_change();
	result="";
	if(status.find(id)!=status.end()){
		result=status.find(id)->second;
		return true;
	}
	return false;
}
} /* namespace std */
