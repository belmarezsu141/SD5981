/*
 * System_Common_Func.h
 *
 *  Created on: Sep 1, 2016
 *      Author: yanfen.fang
 */

#include <Common_Func/System_Common_Func.h>

std::string trim(const std::string& str)
{
	int iStart = 0;
	int iStop = 0;
	int i = 0;
	int length =static_cast<int>( str.length());

	for(i=0;i< length;i++)
	{
		if(str[i] != ' ')
		{
			iStart = i;
			break;
		}
	}

	for(i=length-1;i>=0;i--)
	{
		if(str[i] != ' ')
		{
			iStop = i+1;
			break;
		}
	}

	return str.substr(iStart,iStop-iStart);
}

/*
 *----------------------------------------------------------------------*
 * Routine: parseListOfString
 *
 * Purpose: parse one string to a string vector
 *
 *----------------------------------------------------------------------*
 * Description:
 *    e.g.    the original string is:
 *                "pin1,(pin2,pin3),pin4"
 *            and the delimiter char is: ','
 *    yields the following string vector results:
 *                "pin1", "pin2,pin3", "pin4"
 *
 *
 *----------------------------------------------------------------------*
 */
void parseListOfString(const std::string& originalString,
		std::vector<std::string>& stringVec,
		char delimiter ,
		bool isParenthesesSupported)
{
	stringVec.clear();
	if(originalString.empty())
	{
		stringVec.clear();
		return;
	}
	bool isWithinParentheses = false;
	bool isLeftParenthesesExist = false;
	std::string word;
	const char* str = originalString.c_str();

	for ( int i = 0 ; *(str+i) != 0 ; ++i )
	{
		char ch = str[i];

		if( ch == delimiter )
		{
			if ( isWithinParentheses && isParenthesesSupported )
			{
				word += ch;
			}
			else
			{
				stringVec.push_back(trim(word));
				word = "";
			}
		}
		else if (isParenthesesSupported && ch == '(')
		{
			isWithinParentheses = true;
			isLeftParenthesesExist = true;
		}
		else if (isParenthesesSupported && ch == ')')
		{
			isWithinParentheses = false;
			if(!isLeftParenthesesExist)
			{
//				throw Error("ContinuityTestUtil::parseListOfString",
//						"the parentheses mismatch.The correct format is like:()",
//						"ContinuityTestUtil::parseListOfString");
			}
			isLeftParenthesesExist = false;
		}
		else
		{
			word += ch;
		}
	}

	if(isLeftParenthesesExist)
	{
//		throw Error("ContinuityTestUtil::parseListOfString",
//				"the parentheses mismatch.The correct format is like:()",
//				"ContinuityTestUtil::parseListOfString");
	}
	stringVec.push_back(trim(word));

	return;
}

/*
 *----------------------------------------------------------------------*
 * Routine: parseListOfDouble
 *
 * Purpose: parse one string to a double vector
 *
 *----------------------------------------------------------------------*
 * Description:
 *    e.g.    the original string is:
 *                "1.5,2.8,5.6"
 *            and the delimiter char is: ','
 *    yields the following double vector results:
 *                "1.5", "2.8", "5.6"
 *
 *
 *----------------------------------------------------------------------*
 */
void parseListOfDouble(const std::string& originalString,
		std::vector<double>& doubleVec,
		char delimiter)
{
	doubleVec.clear();
	if(originalString.empty())
	{
		doubleVec.clear();
		return;
	}

	std::string word;
	double tempValue;
	const char* str = originalString.c_str();

	for ( int i = 0 ; *(str+i) != 0 ; ++i )
	{
		char ch = str[i];
		if( ch == delimiter )
		{
			std::string tempString = trim(word);
			if(tempString.empty())
			{
				doubleVec.push_back(0.0);
			}
			else
			{
				std::istringstream stream(word);
				stream >> tempValue;
				doubleVec.push_back(tempValue);
			}
			word = "";
		}
		else
		{
			word += ch;
		}
	}

	std::string tempString = trim(word);
	if(tempString.empty())
	{
		doubleVec.push_back(0.0);
	}
	else
	{
		std::istringstream stream(word);
		stream >> tempValue;
		doubleVec.push_back(tempValue);
	}
	return;
}

/*
 *----------------------------------------------------------------------*
 * Routine: parseListOfInt
 *
 * Purpose: parse one string to a Int vector
 *
 *----------------------------------------------------------------------*
 * Description:
 *    e.g.    the original string is:
 *                "1.5,2.8,5.6"
 *            and the delimiter char is: ','
 *    yields the following double vector results:
 *                "1.5", "2.8", "5.6"
 *
 *
 *----------------------------------------------------------------------*
 */
void parseListOfInt(const std::string& originalString,
		std::vector<int>& intVec,
		char delimiter)
{
	intVec.clear();
	if(originalString.empty())
	{
		intVec.clear();
		return;
	}

	std::string word;
	int tempValue;
	const char* str = originalString.c_str();

	for ( int i = 0 ; *(str+i) != 0 ; ++i )
	{
		char ch = str[i];
		if( ch == delimiter )
		{
			std::string tempString = trim(word);
			if(tempString.empty())
			{
				intVec.push_back(0);
			}
			else
			{
				std::istringstream stream(word);
				stream >> tempValue;
				intVec.push_back(tempValue);
			}
			word = "";
		}
		else
		{
			word += ch;
		}
	}

	std::string tempString = trim(word);
	if(tempString.empty())
	{
		intVec.push_back(0);
	}
	else
	{
		std::istringstream stream(word);
		stream >> tempValue;
		intVec.push_back(tempValue);
	}
	return;
}



//std::map<string, timespec> MyTimer::timerMap = std::map<string, timespec>();
//
//void MyTimer::start(const string& name) {
//	timespec ts1;
//	clock_gettime(CLOCK_REALTIME, &ts1);
//	timerMap[name] = ts1;
//}
//
//double MyTimer::stop(const string& name) {
//	timespec ts1 = timerMap[name];
//	timespec ts2;
//	clock_gettime(CLOCK_REALTIME, &ts2);
//	double interval = (ts2.tv_sec - ts1.tv_sec)*1e3 + (ts2.tv_nsec - ts1.tv_nsec)/1e6;
//
//	int isDebugAnalogOn;
//	GET_TESTFLOW_FLAG("debug_analog",&isDebugAnalogOn);
//
//	if (isDebugAnalogOn) {
//		std::cout << "DEBUG: timer " << name << " = " << interval << " ms" << std::endl;
//	}
//
//	return interval;
//}
//
//double MyTimer::stop_no_print(const string& name) {
//	timespec ts1 = timerMap[name];
//	timespec ts2;
//	clock_gettime(CLOCK_REALTIME, &ts2);
//	double interval = (ts2.tv_sec - ts1.tv_sec)*1e3 + (ts2.tv_nsec - ts1.tv_nsec)/1e6;
//	return interval;
//}

/*
 * Print Level Control
 * Updated in 2017 Jan 1 by Li-xin
 * 1.Optimize func logic of this class
 * 2.Add full eye diagram plot used for HiLink in this class, expand printLevel from [0x0~0x7] to [0x0~0xf]
 */
HILINK_Debug_Output hout;

HILINK_Debug_Output::HILINK_Debug_Output() {
    string sDebugEnvironment;
    time_t rawtime;
    struct tm * timeinfo;
    string sTimeDate;

    // get timestamp
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    sTimeDate = asctime(timeinfo);
    sTimeDate.erase(sTimeDate.end()-1);

    //handling MCD log settings
    bLogMCD = false;

    /*handling MCD log settings
    if (bLogMCD) {
        BEGIN_EXTENSION();
          FW_TASK("DIAG 2");
        END_EXTENSION();
    }
    */

    //handling file log settings, log to file instead of Report Window
    bLogToFile = false;

    /*if debug logging redirection to file is enabled, detrmine logfile location and open output file stream for logfile
    if (bLogToFile) {
		STRING sLogFileName;
		STRING sDevicePath;
		char cDevicePath[512];
		GetDevPath(cDevicePath);
		sDevicePath = cDevicePath;
		sLogFileName = sDevicePath + "/waste/" + "HILINK_LOG";

		ofsLogFile.open(sLogFileName.c_str(),ios_base::out | ios_base::app);

		if (ofsLogFile) {
			clog << "attaching log output to file " << sLogFileName << endl;
		pClogBuffer = clog.rdbuf(ofsLogFile.rdbuf());
		clog << BANNER << endl;
		clog << "LOG START : " << sTimeDate << endl;
		clog << BANNER << endl;
      }
      else
        clog << "ERROR : cannot open logfile " << endl;
    }
    */
}

HILINK_Debug_Output::~HILINK_Debug_Output() {
    /*handling file log settings
    if (bLogToFile) {
      ofsLogFile.close();
      clog.rdbuf(pClogBuffer);
    }
    */

    /*if MCD logging was enabled switch off MCD logging
    if (bLogMCD) {
        BEGIN_EXTENSION();
          FW_TASK("DIAG -2");
        END_EXTENSION();
    }
    */
}

ostream& HILINK_Debug_Output::operator() (const DebugLevelType& LevelType) {
	/* RELEASE: 		Error info, Important Warning info, etc.  Could not be ignored in production
	 * GENERAL:			Testsuite name, value to be judged, hardware action, etc.
	 * DETAIL:			calc values, each pin's measured values, each lane's error count, etc.
	 * EYEPLOT:			plot full eye diagram in most Bert and tolerance(each step) related testsuite
	 * REG_ACCESS:		all read write action of registors
	 */
	switch (LevelType) {
		case RELEASE:
//				clog << setw(10)  << "INFO_RELEASE (Site" << setw(4) << setfill('0') << CURRENT_SITE_NUMBER() << ") : " << setw(0) << setfill(' ');
	            break;
		case GENERAL:
			if (1 == (itsLevel&0x1)) {
//				clog << setw(10)  << "INFO_GENERAL (Site" << setw(4) << setfill('0') << CURRENT_SITE_NUMBER() << ") : " << setw(0) << setfill(' ');
				break;
			} else {
				return nullstream; /* a stream with no output, very quick */
			}
		case DETAIL:
			if (1 == ((itsLevel>>1)&0x1)) {
//				clog << setw(10)  << "INFO_DETAIL  (Site" << setw(4) << setfill('0') << CURRENT_SITE_NUMBER() << ") : " << setw(0) << setfill(' ');
				break;
			} else {
				return nullstream; /* a stream with no output, very quick */
			}
		case EYEPLOT:
			if (1 == ((itsLevel>>2)&0x1)) {
//				clog << setw(10)  << "EYEPLOT      (Site" << setw(4) << setfill('0') << CURRENT_SITE_NUMBER() << ") : " << setw(0) << setfill(' ');
				break;
			} else {
				return nullstream; /* a stream with no output, very quick */
			}
		case REG_ACCESS:
			if (1 == ((itsLevel>>3)&0x1)) {
//				clog << setw(10)  << "REG_ACCESS   (Site" << setw(4) << setfill('0') << CURRENT_SITE_NUMBER() << ") : " << setw(0) << setfill(' ');
				break;
			} else {
				return nullstream; /* a stream with no output, very quick */
			}
		default:
			break;
	}

	return clog;
}

STRING HILINK_Debug_Output::rankLevel(const INT& iLevel) {
	STRING   tmpstr;
	if (iLevel >= 0 && iLevel <= 0xff) {
		if (0 == iLevel) {
			tmpstr = "RELEASE(0000)";
		} else {
			if (1 == (iLevel&0x1)) {
				tmpstr += "INFO_GENERAL(0001)";
			}
			if (1 == ((iLevel>>1)&0x1)) {
				if (1 == (iLevel&0x1)) {
					tmpstr += "&";
				}
				tmpstr += "INFO_DETAIL(0010)";
			}
			if (1 == ((iLevel>>2)&0x1)) {
				if ((1 == (iLevel&0x1)) || (1 == ((iLevel>>1)&0x1))) {
					tmpstr += "&";
				}
				tmpstr += "EYEPLOT(0100)";
			}
			if (1 == (iLevel>>3)&0x1) {
				if ((1 == (iLevel&0x1)) || (1 == ((iLevel>>1)&0x1)) || (1 == ((iLevel>>2)&0x1))) {
					tmpstr += "&";
				}
				tmpstr += "REG_ACCESS(1000)";
			}
		}
	} else {
		tmpstr = "UNKNOWN LEVEL";
	}
	return tmpstr;
}

STRING HILINK_Debug_Output::printLevel() {
	STRING   tmpstr;
	if (itsLevel >= 0 && itsLevel <= 0xf) {
		if (0 == itsLevel) {
			tmpstr = "RELEASE(0000)";
		} else {
			if (1 == (itsLevel&0x1)) {
				tmpstr += "INFO_GENERAL(0001)";
			}
			if (1 == ((itsLevel>>1)&0x1)) {
				if (1 == (itsLevel&0x1)) {
					tmpstr += "&";
				}
				tmpstr += "INFO_DETAIL(0010)";
			}
			if (1 == ((itsLevel>>2)&0x1)) {
				if ((1 == (itsLevel&0x1)) || (1 == ((itsLevel>>1)&0x1))) {
					tmpstr += "&";
				}
				tmpstr += "EYEPLOT(0100)";
			}
			if (1 == (itsLevel>>3)&0x1) {
				if ((1 == (itsLevel&0x1)) || (1 == ((itsLevel>>1)&0x1)) || (1 == ((itsLevel>>2)&0x1))) {
					tmpstr += "&";
				}
				tmpstr += "REG_ACCESS(1000)";
			}
		}
	} else {
		tmpstr = "UNKNOWN LEVEL";
	}
	return tmpstr;
}

void HILINK_Debug_Output::setLevel(const INT& iLevel) {

	INT					iDebugLevel;
//	GET_USER_FLAG		("DebugLevel",&iDebugLevel);
	if (iDebugLevel != 0x10) {
		if (iDebugLevel != itsLevel) {
			if ((iDebugLevel >= 0) && (iDebugLevel <= 0xff)) {
				itsLevel = iDebugLevel;
			} else {
				/*Unknown Level, Please enter level value between [0~0x10]!*/
				clog << "INFO: Unknown Level! Please enter DebugLevel value between [0~0x10] in FlowVal! DebugLevel auto set to 0!" << endl;
				itsLevel = 0;
			}
		}
		if (iDebugLevel != 0) {
			clog << "INFO: DebugLevel set to: " << rankLevel(iDebugLevel) << " By FlowVar" << endl;
		}
	}
	else
	{
		if (iLevel != itsLevel)
		{
			if ((iLevel >= 0) && (iLevel <= 0xff)) {
				itsLevel = iLevel;
			} else {
				/*Unknown Level, Please enter level value between [0~f]!*/
				clog << "INFO: Unknown Level! Please enter PrintLvl value between [0~f] in SuitePar! PrintLvl auto set to 0!" << endl;
				itsLevel = 0;
			}
		}
		if (iLevel != 0) {
			clog << "INFO: DebugLevel set to: " << rankLevel(iLevel) << " By SuitePar" << endl;
		}
	}
}

INT HILINK_Debug_Output::getLevel() {
	return itsLevel;
}

bool HILINK_Debug_Output::IsEyePlotEn() {
	if (1 == ((itsLevel>>2)&0x1)) {
		return true;
	} else {
		return false;
	}
}

bool HILINK_Debug_Output::IsRegAccessEn() {
	if (1 == ((itsLevel>>3)&0x1)) {
		return true;
	} else {
		return false;
	}
}

bool HILINK_Debug_Output::IsDetailEn() {
	if (1 == ((itsLevel>>1)&0x1)) {
		return true;
	} else {
		return false;
	}
}

bool HILINK_Debug_Output::IsGeneralEn() {
	if (1 == ((itsLevel>>0)&0x1)) {
		return true;
	} else {
		return false;
	}
}
void HILINK_Debug_Output::printsuitename(const STRING& sTestsuiteName) {
	hout(GENERAL) << "===============================================================================================" << endl;
	hout(GENERAL) << "\tTest Suite Name: " << sTestsuiteName << endl;
	hout(GENERAL) << "===============================================================================================" << endl;
}
