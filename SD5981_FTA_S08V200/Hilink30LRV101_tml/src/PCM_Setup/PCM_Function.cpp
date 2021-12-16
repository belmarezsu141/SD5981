//
// Created by f.he on 2021/6/18.
//

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include <synchapi.h>

using namespace PinTool;
using namespace PhxAPI;

#define I2C_DELAY 		5

class PCM_Function: public TestClass{
public:


    void init(){

    }

    void execute(){

    	string TName = TheSoft.Flow().Test().GetCurrentTestName();
    	PHXSYS_LOGSTR_TRACE("-------------------------------------------");
    	PHXSYS_LOGSTR_TRACE("------!!!Hello PCM_Function!!!------");
    	PHXSYS_LOG_TRACE("The Current Test is : %s", TName.c_str());



		TheInst.DCVI().Power().Apply();
		TheInst.Digital().Level().Apply();
		TheInst.Digital().Timing().Apply();

    	TheInst.Util().SetUserPower(E_USERPW_P5V,E_UTIL_STATE_ON);


    	Sleep(5);

		int i = -1;
		int ubit[12] = {10,19,28,37,46,55,119,110,101,92,83,74};
		for(uint32_t j=0;j<12;j++)
		{
			TheInst.Util().SetRelayState(ubit[j], 1); //bihe-0,duankai-1
			Sleep(I2C_DELAY);
			i = TheInst.Util().GetRelayState(ubit[j]);
			if (i==1)
			{
				printf("\n***********duankai Relay-  %d error**************\n",j);
			}


			Sleep(I2C_DELAY);

		}

		TheInst.Digital().PatEng().SetFailMode(PhxAPI::E_SET_HIL_MODE);
		TheInst.Digital().Pattern().Start(); //Ã¦â€°Â§Ã¨Â¡Å’patternÃ¯Â¼Å’Ã¥Â¹Â¶Ã¥Ë†Â¤Ã¥Â®Å¡bin Ã¤Â¿Â¡Ã¦ï¿½Â¯

		//		TheInst.Wait(30);
		PHXSYS_LOGSTR_TRACE("-------------------------------------------");
		PHXSYS_LOGSTR_TRACE("------------------TEST END-----------------");
		PHXSYS_LOGSTR_TRACE("-------------------------------------------");


    }

};
REGISTER_TESTCLASS("PCM_Function",PCM_Function)

