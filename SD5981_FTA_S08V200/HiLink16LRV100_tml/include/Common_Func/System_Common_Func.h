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
#include <cstdio>
#include <cmath>
#include <sstream>
#include <TestClass.h>
#include <UserAPI.h>
#include <unistd.h>
#include <stdlib.h>
#include <HILINK_DRIVE/HiLink_Types.h>

using namespace std;

std::string trim(const std::string& str);
void parseListOfString(const std::string& originalString, std::vector<std::string>& stringVec, char delimiter = ',', bool isParenthesesSupported = false);
void parseListOfDouble(const std::string& originalString, std::vector<double>& doubleVec, char delimiter = ',');
void parseListOfInt(const std::string& originalString, std::vector<int>& intVec, char delimiter = ',');



/* create dummy stream which just dumps all output
 * this is what we use if the DebugLevel is higher than the message importance
 * this stream sets a failbit and hence won't attempt to process it's input
 */
static ostream nullstream(NULL);

/* definition of possible debug levels */
enum DebugLevelType	{
	RELEASE,
	GENERAL,
	DETAIL,
	EYEPLOT,
	REG_ACCESS,
};

class HILINK_Debug_Output
{
  public:
	HILINK_Debug_Output ();
    ~HILINK_Debug_Output();
    ostream& operator()(const DebugLevelType& LevelType);

    void 	setLevel(const INT& iLevel);
    STRING 	rankLevel(const INT& iLevel);
    STRING 	printLevel();
    void 	printsuitename(const STRING& sTestsuiteName);
    INT		getLevel();
    bool	IsEyePlotEn();
    bool	IsRegAccessEn();
    bool	IsDetailEn();
    bool	IsGeneralEn();

  private :
    INT  itsLevel;  				//!< holds the loglevel that currently is set
    bool bLogToFile;         		//!< flag indicating whether log redirection to file is enabled (TRUE) or disabled (FALSE)
    bool bLogMCD;             		//!< flag indicating whether MCD logging is enabled (TRUE) or disabled (FALSE)
    ofstream ofsLogFile;      		//!< output file stream in case log redirection to file is enabled
    std::streambuf *pClogBuffer; 	//!< stream buffer for the logging - easily can be redirected to nullstream if no logging is desired

};

extern HILINK_Debug_Output hout;


class MyTimer
{
private:
	static map<string, timespec> timerMap;

public:
	static void start(const string& name);
	static double stop(const string& name);
	static double stop_no_print(const string& name);
};




#endif /* SYSTEM_COMMON_FUNC_H_ */
