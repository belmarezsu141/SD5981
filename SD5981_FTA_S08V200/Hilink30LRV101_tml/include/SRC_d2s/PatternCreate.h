/*
 * PatternCreate.h
 *
 *  Created on: Nov 22, 2016
 *      Author: yanfen.fang
 */

#ifndef PATTERNCREATE_H_
#define PATTERNCREATE_H_
//#include "mapi.hpp"
#include <string>

#include <map>

#include <SRC_d2s/PatternManager.h>
#include <type.h>

using namespace std;
typedef struct{
	string port;
	string context;
	string wavetable;
	uint size;
	map<string,string> pattern_data;
}T_MAIN_PATTERN_DATA;

void create_wait_pattern(const string& label,uint cycle,const T_MAIN_PATTERN_DATA& patinfo);
void create_all_nop_pattern(const string& label,const T_MAIN_PATTERN_DATA& patinfo);

#endif /* PATTERNCREATE_H_ */
