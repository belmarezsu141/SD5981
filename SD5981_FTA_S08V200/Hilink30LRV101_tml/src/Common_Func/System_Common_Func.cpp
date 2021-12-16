/*
 * System_Common_Func.h
 *
 *  Created on: Sep 1, 2016
 *      Author: yanfen.fang
 */

#include <Common_Func/System_Common_Func.h>

std::string trim(const std::string& str) {
    int iStart = 0;
    int iStop = 0;
    int i = 0;
    int length = static_cast<int> (str.length());

    for (i = 0; i < length; i++) {
        if (str[i] != ' ') {
            iStart = i;
            break;
        }
    }

    for (i = length - 1; i >= 0; i--) {
        if (str[i] != ' ') {
            iStop = i + 1;
            break;
        }
    }

    return str.substr(iStart, iStop - iStart);
}

UINT get_focus_site() {

    //	INT             	iDebugAnalog;
    //	GET_TESTFLOW_FLAG	("debug_analog",&iDebugAnalog);
    //
    //	ARRAY_I active_sites;
    //	INT		num_of_sites;
    //	bool    is_actived = false;
    //	num_of_sites = GET_ACTIVE_SITES(active_sites);
    //	for(int i=0; i<num_of_sites; ++i){
    //		if(active_sites[i] == FOCUS_SITE) is_actived = true;
    //	}
    //
    //	  if(is_actived){
    //	//	  if(iDebugAnalog) cout << "Site " << FOCUS_SITE << " is selected as focus site!" << endl;
    //		  return FOCUS_SITE;
    //	  }
    //	  else{
    //		  cout << "Error: selected focus site " <<FOCUS_SITE<< " is not actived!    ";
    //		  cout << "site " << active_sites[0] <<"will be focus site !" << endl;
    //		  return active_sites[0];
    //	  }
    return 0;
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
        char delimiter,
        bool isParenthesesSupported) {
    stringVec.clear();
    if (originalString.empty()) {
        stringVec.clear();
        return;
    }
    bool isWithinParentheses = false;
    bool isLeftParenthesesExist = false;
    std::string word;
    const char* str = originalString.c_str();

    for (int i = 0; *(str + i) != 0; ++i) {
        char ch = str[i];

        if (ch == delimiter) {
            if (isWithinParentheses && isParenthesesSupported) {
                word += ch;
            } else {
                stringVec.push_back(trim(word));
                word = "";
            }
        } else if (isParenthesesSupported && ch == '(') {
            isWithinParentheses = true;
            isLeftParenthesesExist = true;
        } else if (isParenthesesSupported && ch == ')') {
            isWithinParentheses = false;
            if (!isLeftParenthesesExist) {
                //				throw Error("ContinuityTestUtil::parseListOfString",
                //						"the parentheses mismatch.The correct format is like:()",
                //						"ContinuityTestUtil::parseListOfString");
            }
            isLeftParenthesesExist = false;
        } else {
            word += ch;
        }
    }

    if (isLeftParenthesesExist) {
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
        char delimiter) {
    doubleVec.clear();
    if (originalString.empty()) {
        doubleVec.clear();
        return;
    }

    std::string word;
    double tempValue;
    const char* str = originalString.c_str();

    for (int i = 0; *(str + i) != 0; ++i) {
        char ch = str[i];
        if (ch == delimiter) {
            std::string tempString = trim(word);
            if (tempString.empty()) {
                doubleVec.push_back(0.0);
            } else {
                std::istringstream stream(word);
                stream >> tempValue;
                doubleVec.push_back(tempValue);
            }
            word = "";
        } else {
            word += ch;
        }
    }

    std::string tempString = trim(word);
    if (tempString.empty()) {
        doubleVec.push_back(0.0);
    } else {
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
        char delimiter) {
    intVec.clear();
    if (originalString.empty()) {
        intVec.clear();
        return;
    }

    std::string word;
    int tempValue;
    const char* str = originalString.c_str();

    for (int i = 0; *(str + i) != 0; ++i) {
        char ch = str[i];
        if (ch == delimiter) {
            std::string tempString = trim(word);
            if (tempString.empty()) {
                intVec.push_back(0);
            } else {
                std::istringstream stream(word);
                stream >> tempValue;
                intVec.push_back(tempValue);
            }
            word = "";
        } else {
            word += ch;
        }
    }

    std::string tempString = trim(word);
    if (tempString.empty()) {
        intVec.push_back(0);
    } else {
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

void parseSiteDataFromLaneInt( map<int, long long>& val, LANE_INT& lane_data, uint MacroID, uint LaneID) {
    val.clear();
    //    FOR_EACH_SITE_BEGIN();
    //    uint SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        int SiteID = api->Get_active_site();
//        val[SiteID] = lane_data[SiteID][MacroID][LaneID];
//        //   FOR_EACH_SITE_END();
//    }
    FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

    	val[SiteID] = lane_data[SiteID][MacroID][LaneID];
	FOREACH_ACTIVESITE_END
}

void parseSiteDataFromMacroInt(map<int, long long>& val, MACRO_INT& macro_data, uint MacroID) {
    	val.clear();
//        FOREACH_ACTIVE_SITE(api) {
//            int SiteID = api->Get_active_site();
//    		val[SiteID] = macro_data[SiteID][MacroID];
//        }
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        val[SiteID] = macro_data[SiteID][MacroID];
    	FOREACH_ACTIVESITE_END
}

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
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    sTimeDate = asctime(timeinfo);
    sTimeDate.erase(sTimeDate.end() - 1);

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
//                        clog << "attaching log output to file " << sLogFileName << endl;
                pClogBuffer = clog.rdbuf(ofsLogFile.rdbuf());
//                clog << BANNER << endl;
//                clog << "LOG START : " << sTimeDate << endl;
//                clog << BANNER << endl;
      }
      else
//        clog << "ERROR : cannot open logfile " << endl;
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
            if (1 == (itsLevel & 0x1)) {
                //				clog << setw(10)  << "INFO_GENERAL (Site" << setw(4) << setfill('0') << CURRENT_SITE_NUMBER() << ") : " << setw(0) << setfill(' ');
                break;
            } else {
                return nullstream; /* a stream with no output, very quick */
            }
        case DETAIL:
            if (1 == ((itsLevel >> 1)&0x1)) {
                //				clog << setw(10)  << "INFO_DETAIL  (Site" << setw(4) << setfill('0') << CURRENT_SITE_NUMBER() << ") : " << setw(0) << setfill(' ');
                break;
            } else {
                return nullstream; /* a stream with no output, very quick */
            }
        case EYEPLOT:
            if (1 == ((itsLevel >> 2)&0x1)) {
                //				clog << setw(10)  << "EYEPLOT      (Site" << setw(4) << setfill('0') << CURRENT_SITE_NUMBER() << ") : " << setw(0) << setfill(' ');
                break;
            } else {
                return nullstream; /* a stream with no output, very quick */
            }
        case REG_ACCESS:
            if (1 == ((itsLevel >> 3)&0x1)) {
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
    STRING tmpstr;
    if (iLevel >= 0 && iLevel <= 0xff) {
        if (0 == iLevel) {
            tmpstr = "RELEASE(0000)";
        } else {
            if (1 == (iLevel & 0x1)) {
                tmpstr += "INFO_GENERAL(0001)";
            }
            if (1 == ((iLevel >> 1)&0x1)) {
                if (1 == (iLevel & 0x1)) {
                    tmpstr += "&";
                }
                tmpstr += "INFO_DETAIL(0010)";
            }
            if (1 == ((iLevel >> 2)&0x1)) {
                if ((1 == (iLevel & 0x1)) || (1 == ((iLevel >> 1)&0x1))) {
                    tmpstr += "&";
                }
                tmpstr += "EYEPLOT(0100)";
            }
            if (1 == (iLevel >> 3)&0x1) {
                if ((1 == (iLevel & 0x1)) || (1 == ((iLevel >> 1)&0x1)) || (1 == ((iLevel >> 2)&0x1))) {
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
    STRING tmpstr;
    if (itsLevel >= 0 && itsLevel <= 0xf) {
        if (0 == itsLevel) {
            tmpstr = "RELEASE(0000)";
        } else {
            if (1 == (itsLevel & 0x1)) {
                tmpstr += "INFO_GENERAL(0001)";
            }
            if (1 == ((itsLevel >> 1)&0x1)) {
                if (1 == (itsLevel & 0x1)) {
                    tmpstr += "&";
                }
                tmpstr += "INFO_DETAIL(0010)";
            }
            if (1 == ((itsLevel >> 2)&0x1)) {
                if ((1 == (itsLevel & 0x1)) || (1 == ((itsLevel >> 1)&0x1))) {
                    tmpstr += "&";
                }
                tmpstr += "EYEPLOT(0100)";
            }
            if (1 == (itsLevel >> 3)&0x1) {
                if ((1 == (itsLevel & 0x1)) || (1 == ((itsLevel >> 1)&0x1)) || (1 == ((itsLevel >> 2)&0x1))) {
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

    INT iDebugLevel;
    //	GET_USER_FLAG		("DebugLevel",&iDebugLevel);
    if (iDebugLevel != 0x10) {
        if (iDebugLevel != itsLevel) {
            if ((iDebugLevel >= 0) && (iDebugLevel <= 0xff)) {
                itsLevel = iDebugLevel;
            } else {
                /*Unknown Level, Please enter level value between [0~0x10]!*/
//                clog << "INFO: Unknown Level! Please enter DebugLevel value between [0~0x10] in FlowVal! DebugLevel auto set to 0!" << endl;
                itsLevel = 0;
            }
        }
        if (iDebugLevel != 0) {
//            clog << "INFO: DebugLevel set to: " << rankLevel(iDebugLevel) << " By FlowVar" << endl;
        }
    } else {
        if (iLevel != itsLevel) {
            if ((iLevel >= 0) && (iLevel <= 0xff)) {
                itsLevel = iLevel;
            } else {
                /*Unknown Level, Please enter level value between [0~f]!*/
//                clog << "INFO: Unknown Level! Please enter PrintLvl value between [0~f] in SuitePar! PrintLvl auto set to 0!" << endl;
                itsLevel = 0;
            }
        }
        if (iLevel != 0) {
//            clog << "INFO: DebugLevel set to: " << rankLevel(iLevel) << " By SuitePar" << endl;
        }
    }
}

INT HILINK_Debug_Output::getLevel() {
    return itsLevel;
}

bool HILINK_Debug_Output::IsEyePlotEn() {
    if (1 == ((itsLevel >> 2)&0x1)) {
        return true;
    } else {
        return false;
    }
}

bool HILINK_Debug_Output::IsRegAccessEn() {
    if (1 == ((itsLevel >> 3)&0x1)) {
        return true;
    } else {
        return false;
    }
}

void HILINK_Debug_Output::printsuitename(const STRING& sTestsuiteName) {
    //hout(GENERAL) << "===============================================================================================" << endl;
    //hout(GENERAL) << "\tTest Suite Name: " << sTestsuiteName << endl;
    //hout(GENERAL) << "===============================================================================================" << endl;
}

string int2str(const int n) {
    stringstream str;
    str << n;
    return str.str();
}

string double2str(const double n) {
    stringstream str;
    str << n;
    return str.str();
}

string float2str(const double n) {
    stringstream str;
    str << n;
    return str.str();
}

void replace_str(string& str, const string sb, const string sa) {
    string::size_type n, nb = 0;

    while ((n = str.find(sb, nb)) != string::npos) {
        str.replace(n, sb.size(), sa);
        nb = n + sa.size();
    }
}

double get_spec_val(const string& sType, const string& sSpecName) {

    double dVal;

    //    if(sType == "TIM") fwout << "SVLR? TIM,PRM,,\"" << sSpecName << "\"" << endl;
    //    else               fwout << "SVLR? LEV,PRM,,\"" << sSpecName << "\"" << endl;
    //
    //    dVal = atof(fwresult[0][4].c_str());

    return dVal;
}

double GET_VECTOR_CAPTURE_PERIOD_NS(string& pinlist) {
    double VectorCapturePeriod = 0;
    string str_FW_commmand = "";
    string str_FW_Answer = "";
    STRING_VECTOR STV_FW_Answer;
    str_FW_commmand = "PCLK? PRM,PRM,(" + pinlist + ")\n";
    //	FW_TASK(str_FW_commmand,str_FW_Answer);
    if (str_FW_Answer.empty() == true) {
        //	throw Error("Error", "PCLK? firmware command return empty");
    }
    STV_FW_Answer.clear();
    parseListOfString(str_FW_Answer, STV_FW_Answer, ',');
    VectorCapturePeriod = string2double(STV_FW_Answer[3]);

    return VectorCapturePeriod;
}

int GET_DigitalCapture_XMode(string& PinName) //Get X-mode of C in wavetable for Digital Capture
{
    int WFDS_INDEX = 0;
    //	if(Primary.isTimingPortBased() == true)
    //	{
    //		WFDS_INDEX = 4;
    //	}
    //	else
    //	{
    //		WFDS_INDEX = 2;
    //	}
    int XmodeDigitalCapture = 0;
    string str_FW_commmand = "";
    string str_FW_Answer = "";
    STRING_VECTOR STV_FW_Answer;
    STRING_VECTOR STV_STV_FW_Answer;

    str_FW_commmand = " WFDS? PRM,ALL,,(" + PinName + ")\n";
    //	FW_TASK(str_FW_commmand,str_FW_Answer);
    parseListOfString(str_FW_Answer, STV_FW_Answer, '\n');


    for (unsigned int index = 0; index < STV_FW_Answer.size(); index++) {
        STV_STV_FW_Answer.clear();
        parseListOfString(STV_FW_Answer[index], STV_STV_FW_Answer, '"');
        int pos = 0;
        int xmode = 0;
        while (STV_STV_FW_Answer[WFDS_INDEX].find(":C", pos) != string::npos) {
            xmode++;
            pos = STV_STV_FW_Answer[WFDS_INDEX].find(":C", pos) + 1;
        }

        if ((XmodeDigitalCapture == 0) && (xmode != 0)) {
            XmodeDigitalCapture = xmode;
        } else if ((XmodeDigitalCapture != 0) && (xmode != 0)) {
            if (XmodeDigitalCapture != xmode) {
//                cout << "**** __FILE__:" << __FILE__ << endl;
//                cout << "**** __LINE__:" << __LINE__ << endl;
                //				throw Error("ERROR","The C and D in Wavetable definde error");
            }
        }

    }

    if (XmodeDigitalCapture == 0) {
        //		throw Error("ERROR","No C Find in pin("+PinName+")");
    }

    return XmodeDigitalCapture;
}

DOUBLE string2double(const string& input) {

    DOUBLE result;
    char* pEnd;

    size_t foundx = input.find("x");
    size_t foundX = input.find("X");
    size_t foundo = input.find("o");
    size_t foundO = input.find("O");

    if ((foundx != string::npos) || (foundX != string::npos)) {
        result = strtol(input.c_str(), &pEnd, 16);
    } else if ((foundo != string::npos) || (foundO != string::npos)) {
        string ostr;
        if (foundo != string::npos) {
            ostr = input.substr(foundo + 1);
        } else {
            ostr = input.substr(foundO + 1);
        }

        result = strtol(ostr.c_str(), &pEnd, 8);
    } else {
        result = strtod(input.c_str(), &pEnd);
    }

    if ((result == 0 && atof(input.c_str()) != 0)
            || pEnd[0] != '\0') {
        STRING api = "Convert parameter[] :" + input + " to DOUBLE fail";
        STRING msg = "it is not a double!";
        //		throw Error("Error",api.c_str());
    }

    return result;

}


//MultiSite
bool is_allPass(const string& label){
	bool all_pass=true;
	d2s_JTAG& jtag=d2s_JTAG::Instance();
////	FOR_EACH_SITE_BEGIN();
//        FOREACH_ACTIVE_SITE(api) {
////            if(!jtag.hasPassed(label)){
//                    all_pass=false;
////            }
//        }

        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        all_pass=false;
    	FOREACH_ACTIVESITE_END
//	FOR_EACH_SITE_END();
	return all_pass;
}

bool is_allPass(const string& label,SITE_INT& result){
	bool all_pass=true;
	d2s_JTAG& jtag=d2s_JTAG::Instance();
//	FOR_EACH_SITE_BEGIN();
//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int SiteID = api->Get_active_site();
//
//            result[SiteID]=1;
////            if(!jtag.hasPassed(label)){
//                    all_pass=false;
//                    result[SiteID]=0;
////            }
//        }
//	FOR_EACH_SITE_END();
	//	result[0]=all_pass;

        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

				result[SiteID]=1;
				all_pass=false;
				result[SiteID]=0;
    	FOREACH_ACTIVESITE_END



	return all_pass;
}


bool is_allFail(const string& label){
	bool all_fail=true;
	d2s_JTAG& jtag=d2s_JTAG::Instance();

        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        	all_fail=false;
    	FOREACH_ACTIVESITE_END
	return all_fail;
}

bool is_allFail(const string& label,SITE_INT& result){
	bool all_fail=true;
	d2s_JTAG& jtag=d2s_JTAG::Instance();

        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        result[SiteID]=0;
                all_fail=false;
                result[SiteID]=1;
    	FOREACH_ACTIVESITE_END

	return all_fail;
}


bool is_atLeastOneFail(const string& label){
	bool atLeastOneFail=false;
	d2s_JTAG& jtag=d2s_JTAG::Instance();

        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        	atLeastOneFail=true;
    	FOREACH_ACTIVESITE_END

	return atLeastOneFail;
}

bool is_atLeastOneFail(const string& label,SITE_INT& result){
	bool atLeastOneFail=false;
	d2s_JTAG& jtag=d2s_JTAG::Instance();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

			result[SiteID]=1;
			atLeastOneFail=true;
			result[SiteID]=0;
    	FOREACH_ACTIVESITE_END

	return atLeastOneFail;
}

void Update_CSReg_ForDynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, MACRO_INT& Segmentvalue, MACRO_INT& CSRvalue)
{
//	CSRvalue.init(0);
	HILINK_Regs_Base& reg = reg_info_ex.parent;
	UINT csrIndex = reg_info_ex.reg_info.csr;

        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

			CS.clkRegs.csr[csrIndex] = reg.fill_bits(CS.clkRegs.csr[csrIndex], reg_info_ex, Segmentvalue[SiteID][MacroID]);
			CSRvalue[SiteID][MacroID] = CS.clkRegs.csr[csrIndex];                  
                        
		}
       FOREACH_ACTIVESITE_END

}

void Update_DSReg_ForDynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,LANE_INT& Segmentvalue,LANE_INT& CSRvalue)
{
	CSRvalue.init(0);
	HILINK_Regs_Base& reg = reg_info_ex.parent;
	UINT csrIndex = reg_info_ex.reg_info.csr;

        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				if (reg.getName() == "DS_CLK") {
					DS.clkRegs.csr[csrIndex] = reg.fill_bits(DS.clkRegs.csr[csrIndex], reg_info_ex, Segmentvalue[SiteID][MacroID][LaneID]);
					CSRvalue[SiteID][MacroID][LaneID] = DS.clkRegs.csr[csrIndex];
				} else if (reg.getName() == "DS_TX") {
					DS.txRegs.csr[csrIndex] = reg.fill_bits(DS.txRegs.csr[csrIndex], reg_info_ex, Segmentvalue[SiteID][MacroID][LaneID]);
					CSRvalue[SiteID][MacroID][LaneID] = DS.txRegs.csr[csrIndex];
				} else if (reg.getName() == "DS_RX") {
					DS.rxRegs.csr[csrIndex] = reg.fill_bits(DS.rxRegs.csr[csrIndex], reg_info_ex, Segmentvalue[SiteID][MacroID][LaneID]);
					CSRvalue[SiteID][MacroID][LaneID] = DS.rxRegs.csr[csrIndex];
				} else {
					hout(RELEASE) << "Error: can not find related CSR Type " << endl;
					_exit(0);
				}
			}
		}
     FOREACH_ACTIVESITE_END

}

void Update_DSReg_ForDynamicWrite_2BIT(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex1, const T_REG_INFO_EX& reg_info_ex2,LANE_INT& Segmentvalue1, LANE_INT& Segmentvalue2,LANE_INT& CSRvalue)
{
//	CSRvalue.init(0);
	HILINK_Regs_Base& reg = reg_info_ex1.parent;
	UINT csrIndex = reg_info_ex1.reg_info.csr;


//	FOR_EACH_SITE_BEGIN();
//		INT SiteID = CURRENT_SITE_NUMBER() - 1;
//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				if (reg.getName() == "DS_CLK") {
					DS.clkRegs.csr[csrIndex] = reg.fill_bits(DS.clkRegs.csr[csrIndex], reg_info_ex1, Segmentvalue1[SiteID][MacroID][LaneID]);
					DS.clkRegs.csr[csrIndex] = reg.fill_bits(DS.clkRegs.csr[csrIndex], reg_info_ex2, Segmentvalue2[SiteID][MacroID][LaneID]);
					CSRvalue[SiteID][MacroID][LaneID] = DS.clkRegs.csr[csrIndex];
				} else if (reg.getName() == "DS_TX") {
					DS.txRegs.csr[csrIndex] = reg.fill_bits(DS.txRegs.csr[csrIndex], reg_info_ex1, Segmentvalue1[SiteID][MacroID][LaneID]);
					CSRvalue[SiteID][MacroID][LaneID] = DS.txRegs.csr[csrIndex];
				} else if (reg.getName() == "DS_RX") {
					DS.rxRegs.csr[csrIndex] = reg.fill_bits(DS.rxRegs.csr[csrIndex], reg_info_ex1, Segmentvalue1[SiteID][MacroID][LaneID]);
					CSRvalue[SiteID][MacroID][LaneID] = DS.rxRegs.csr[csrIndex];
				} else {
					hout(RELEASE) << "Error: can not find related CSR Type " << endl;
					_exit(0);
				}
			}
		}
        FOREACH_ACTIVESITE_END

}
void parseSiteDataIntFromMacroDouble(map<int, long long>& val, MACRO_DOUBLE& macro_data, uint MacroID) {
    	val.clear();
//
//        FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
                FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

//    		uint SiteID = CURRENT_SITE_NUMBER() - 1;
    		val[SiteID] = (long long)macro_data[SiteID][MacroID];
                FOREACH_ACTIVESITE_END
}
