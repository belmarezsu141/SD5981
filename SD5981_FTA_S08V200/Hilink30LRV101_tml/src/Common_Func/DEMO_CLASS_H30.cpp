/*
 * HiLink_Common_Func.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: yanfen.fang
 */

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include <map>
#include <synchapi.h>

#define I2C_DELAY 		5

using namespace std;
using namespace std;
using namespace PhxAPI;


class PCMV200_Setup_Config: public TestClass {
public:

	void init() {


	}

	void execute() {

		TheInst.DCVI().Power().Apply();
		TheInst.Digital().Level().Apply();
		TheInst.Digital().PatEng().SetupMCFData();
		TheInst.Digital().Timing().Apply();
		TheInst.Digital().Pattern(). Run();
//		TheInst.Wait(30);

	 	map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
	 	for(auto it = result.begin(); it != result.end(); it++)
		{
	 		cout<<"passfail :"<< it->second<<endl;
		}

//	 	map<uint32_t, vector<uint32_t>> mapFailData;
//		mapFailData = TheInst.Digital().PatEng().GetFailCycles(0);
//		cout<<"Fail Size : "<< mapFailData.size() << endl;
//		if(mapFailData.size() > 0)
//		{
//			for(auto it = mapFailData.begin(); it != mapFailData.end(); it++)
//			{
//				cout<<"\n\n\nSite Number : " << it->first<<endl;
//				cout<<"Fail Cycle Size : "<< it->second.size() << endl;
//				cout<<"Fail Cycle :"<<endl;
//				for(uint32_t uiI = 0U; uiI < it->second.size(); uiI++)
//				{
//					if(((uiI % 10U) == 0U) && (uiI > 0U))
//					{
//						cout<<endl;
//					}
//					cout<< dec << (uint32_t)it->second[uiI] <<" ";
//				}
//				cout<<endl;
//			}
//		}
//		else
//		{
//			cout<<"Don't Have Fail Cycle!!!"<<endl;
//		}

	}
};

REGISTER_TESTCLASS("PCMV200_Setup_Config", PCMV200_Setup_Config)

class SetUtilityLines: public TestClass {
public:

	void init() {


	}

	void execute() {
		TheInst.Util().SetUserPower(E_USERPW_P5V,E_UTIL_STATE_ON);


		Sleep(5);

		int i = -1;
		int ubit[12] = {10,19,28,37,46,55,119,110,101,92,83,74};

		for(uint32_t j=0;j<12;j++)
		{
			TheInst.Util().SetRelayState(ubit[j],1); //bihe-0,duankai-1
			Sleep(I2C_DELAY);
			i = TheInst.Util().GetRelayState(ubit[j]);
			if (i==1)
			{

				printf("\n***********duankai Relay-  %d error**************\n",j);
			}

			Sleep(I2C_DELAY);

		}


	}
};

REGISTER_TESTCLASS("SetUtilityLines", SetUtilityLines)


class Disconnect: public TestClass{
public:
    std::string ALL_DIGITAL_PINS;

    void init(){

    }

    void execute(){


    	ALL_DIGITAL_PINS = "g_ALL_DIGITAL_PINS";
    	TheInst.PPMU().Pins("g_ALL_DIGITAL_PINS").SetClear();
		TheInst.PPMU().Pins("g_ALL_DIGITAL_PINS").SetMeasureType(E_MEASURE)
											  .SetIClampH(5*mA)
											  .SetIClampL(-5*mA)
											  .SetIRange(5*mA) // enable force .Gate(1)
											  .SetVForce(0*V)
											  .SetMeasureMode(E_DC_FV_MV)
											  .SetWaitTime(5*ms)
											  .SetSampleSize(16)
											  .Connect(1)
											  .Apply();

		TheInst.PPMU().Pins("g_ALL_DIGITAL_PINS").Connect(0)
											 .Apply();
		PinArrayDouble result = TheInst.PPMU().Pins("g_ALL_DIGITAL_PINS").GetMeasureResults();


//		PinTool::ShowPinArrayData(result);


	    string strPinName = "DVDD08,AVDD12_HSS,AVDD08_HSS,VDD08_DDR,VDDIO12_DDR,AVDD18_PLL_DDR,DVDD18_IO,DVDD18_EFUSE,DVDD08_EFUSE,AVDD18_PCIE,AVDD08_PCIE,AVDD08_CPPI ,AVDD18_SCPLL,AVDD08_SCPLL,AVDD18_TS_0,AVDD18_TS_1";

    	TheInst.DCVI().Pins(strPinName).SetMeasureMode(E_DC_MODE_MI)
								       .SetMeasureMethod(E_DC_METHOD_STATIC)
								       .SetReadMode(E_DC_MODE_MEASURE)
//								       .SetMeasureOrder(E_DC_ORDER_GROUP)
								       .SetIRange(E_POWER_BEST_FIT)
								       .SetVForce(0.0)
								       .SetIClampL(-0.5)
								       .SetIClampH(0.5);
		TheInst.DCVI().SetWaitTime(0.05);

		TheInst.DCVI().Pins(strPinName).Measure();
		TheInst.DCVI().Power().Apply();
		TheInst.DCVI().SetWaitTime(0.05);
    }

};
REGISTER_TESTCLASS("Disconnect",Disconnect)
