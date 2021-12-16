/*
 * System_Common_Func.h
 *
 *  Created on: Sep 1, 2016
 *      Author: yanfen.fang
 */

#ifndef SYSTEM_COMMON_FUNC_H_
#define SYSTEM_COMMON_FUNC_H_

#include <string>
#include <ctime>
#include <map>
#include <vector>
#include <sys/time.h>
#include <iostream>
#include <fstream>
//#include <windows.h>
#include <cstdio>
#include <cmath>
#include <sstream>
#include <TestClass.h>
#include <UserAPI.h>
#include <unistd.h>
#include <stdlib.h>
#include <HILINK_DRIVE/HiLink_Types.h>
#include <HILINK_DRIVE/HiLink_Drive.h>

using namespace std;

extern SITE_INT CSR_CHECK_JUDGE_RESULT;
bool is_allPass(const string& label);
bool is_allPass(const string& label,SITE_INT& result);

bool is_allFail(const string& label);
bool is_allFail(const string& label,SITE_INT& result);

bool is_atLeastOneFail(const string& label);
bool is_atLeastOneFail(const string& label,SITE_INT& result);

std::string trim(const std::string& str);
void parseListOfString(const std::string& originalString, std::vector<std::string>& stringVec, char delimiter = ',', bool isParenthesesSupported = false);
void parseListOfDouble(const std::string& originalString, std::vector<double>& doubleVec, char delimiter = ',');
void parseListOfInt(const std::string& originalString, std::vector<int>& intVec, char delimiter = ',');

/***************used for dynamic write***********/
void parseSiteDataFromLaneInt( map<int, long long>& val, LANE_INT& lane_data, uint MacroID, uint LaneID);
void parseSiteDataFromMacroInt(map<int, long long>& val, MACRO_INT& macro_data, uint MacroID);

void Update_DSReg_ForDynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,LANE_INT& Segmentvalue,LANE_INT& CSRvalue);
void Update_CSReg_ForDynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, MACRO_INT& Segmentvalue, MACRO_INT& CSRvalue);
void Update_DSReg_ForDynamicWrite_2BIT(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex1, const T_REG_INFO_EX& reg_info_ex2,LANE_INT& Segmentvalue1, LANE_INT& Segmentvalue2,LANE_INT& CSRvalue);


int get_first_active_site();
ARRAY_I get_active_sites();
UINT get_focus_site();
/* create dummy stream which just dumps all output
 * this is what we use if the DebugLevel is higher than the message importance
 * this stream sets a failbit and hence won't attempt to process it's input
 */
static ostream nullstream(NULL);

/* definition of possible debug levels */
enum DebugLevelType {
    RELEASE,
    GENERAL,
    DETAIL,
    EYEPLOT,
    REG_ACCESS,
};

class HILINK_Debug_Output {
public:
    HILINK_Debug_Output();
    ~HILINK_Debug_Output();
    ostream& operator()(const DebugLevelType& LevelType);

    void setLevel(const INT& iLevel);
    STRING rankLevel(const INT& iLevel);
    STRING printLevel();
    void printsuitename(const STRING& sTestsuiteName);
    INT getLevel();
    bool IsEyePlotEn();
    bool IsRegAccessEn();

private:
    INT itsLevel; //!< holds the loglevel that currently is set
    bool bLogToFile; //!< flag indicating whether log redirection to file is enabled (TRUE) or disabled (FALSE)
    bool bLogMCD; //!< flag indicating whether MCD logging is enabled (TRUE) or disabled (FALSE)
    ofstream ofsLogFile; //!< output file stream in case log redirection to file is enabled
    std::streambuf *pClogBuffer; //!< stream buffer for the logging - easily can be redirected to nullstream if no logging is desired

};

extern HILINK_Debug_Output hout;

//
//
//class MyTimer
//{
//private:
//	static map<string, timespec> timerMap;
//
//public:
//	static void start(const string& name);
//	static double stop(const string& name);
//	static double stop_no_print(const string& name);
//};

//------------Add Ares------------//
string int2str(const int n);
string double2str(const double n);
string float2str(const double n);
void replace_str(string& str, const string sb, const string sa);
double get_spec_val(const string& sType, const string& sSpecName);
double GET_VECTOR_CAPTURE_PERIOD_NS(string& pinlist);
int GET_DigitalCapture_XMode(string& PinName);
DOUBLE string2double(const string& input);
#endif /* SYSTEM_COMMON_FUNC_H_ */

void parseSiteDataIntFromMacroDouble(map<int, long long>& val, MACRO_DOUBLE& macro_data, uint MacroID);
