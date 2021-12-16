/*
 * CBB_Function.cpp
 *
 *  Created on: 2021年8月16日
 *      Author: KF106
 */

#include <iostream>
#include <string>
#include <math.h>
#include <synchapi.h>
#include "TestClass.h"
#include <UserAPI.h>

#include <HILINK_DRIVE/d2s_IP_JTAG.h>
#include <SRC_d2s/d2sProtocolTemplate.h>

using namespace PhxAPI;

class checkMutilSite: public TestClass{
public:
    string  powercase;
    void init(){
		add_param( "powercase",  "string", &powercase).set_default("NOR").set_options("NOR:LOW:HIGH");
    }

    void execute(){

        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
        cout<<"siteID = " <<SiteID <<endl;

        FOREACH_ACTIVESITE_END
    }

};
REGISTER_TESTCLASS("checkMutilSite",checkMutilSite)



class HLK_SetPower: public TestClass{
public:
    string  powercase;
    void init(){
		add_param( "powercase",  "string", &powercase).set_default("NOR").set_options("NOR:LOW:HIGH");
    }

    void execute(){
    	if(powercase == "NOR")
    	{
        	TheInst.DCVI().Pins("AVDD08_HSS").ForceV(0.8);
        	TheInst.DCVI().Pins("AVDD12_HSS").ForceV(1.2);
    	}else if(powercase == "LOW"){
        	TheInst.DCVI().Pins("AVDD08_HSS").ForceV(0.776);
        	TheInst.DCVI().Pins("AVDD12_HSS").ForceV(1.164);
    	}else if(powercase == "HIGH"){
        	TheInst.DCVI().Pins("AVDD08_HSS").ForceV(0.824);
        	TheInst.DCVI().Pins("AVDD12_HSS").ForceV(1.236);
    	}
    	else
    	{
        	TheInst.DCVI().Pins("AVDD08_HSS").ForceV(0.824);
        	TheInst.DCVI().Pins("AVDD12_HSS").ForceV(1.236);
    	}
    }

};
REGISTER_TESTCLASS("HLK_SetPower",HLK_SetPower)


class initial_test: public TestClass{
public:

    void init(){}
    void execute(){
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;

    	cout <<"do power on relay 5V"<<endl;
		TheInst.Util().SetUserPower(E_USERPW_P5V, 0);
		/*
	    	int i = -1;
	    	for(uint32_t j=0;j<256;j++)
	    	{
	    		TheInst.Util().SetRelayState(j, 0); //bihe-0,duankai-1
	    		Sleep(5);
	    		i = TheInst.Util().GetRelayState(j);
				printf("Relay %d, state %d  -- 0 open, 1 close\n ",j,i);
	    		Sleep(5);
	    	}
		*/
    }

};
REGISTER_TESTCLASS("initial_test",initial_test)


class powerZero: public TestClass{
public:

    void init(){}
    void execute(){
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
	    cout<<"do power force V =0 by apply power block"<<endl;
		TheInst.DCVI().Power().Apply();
	    cout<<"do level 0"<<endl;
		TheInst.Digital().Level().Apply();
    }

};
REGISTER_TESTCLASS("powerZero",powerZero)
class powerOFF: public TestClass{
public:

    void init(){}
    void execute(){


//		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
//		string strTestsuiteName = sTestsuiteName;
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
//    	cout<<"do all relay off"<<endl;
//
//		printf("GetRelayState =0 pass -- 0 open 1 close -- UxxSy xx=relay y=state \n ");
//		for(uint32_t j=0;j<256;j++)
//		{
//			TheInst.Util().SetRelayState(j, 1); //bihe-0,duankai-1
//			Sleep(5);
//			int i = TheInst.Util().GetRelayState(j);
//			printf("U%dS%d ",j,i);
//			if(j%16 ==0 && j>0)
//				cout<<endl;
//		}
//		cout<<endl;
//
//    	cout<<"do power off relay 5V"<<endl;
//		TheInst.Util().SetUserPower(E_USERPW_P5V, 0);
//
//		cout<<"do dps power pins off"<<endl;
//    	TheInst.DCVI().Power().Apply();


       	TheInst.Util().SetUserPower(E_USERPW_P5V,E_UTIL_STATE_OFF);

        	string ALL_DIGITAL_PINS = "g_ALL_DIGITAL_PINS";
        	TheInst.PPMU().Pins("g_ALL_DIGITAL_PINS").SetClear();
			TheInst.PPMU().Pins("g_ALL_DIGITAL_PINS").SetIClampH(2e-3);
			TheInst.PPMU().Pins("g_ALL_DIGITAL_PINS").SetIClampL(-0.5e-3);
    		TheInst.PPMU().Pins("g_ALL_DIGITAL_PINS").SetMeasureType(E_MEASURE);
			TheInst.PPMU().Pins("g_ALL_DIGITAL_PINS").SetMeasureMode(E_DC_FV_MV);
			TheInst.PPMU().Pins("g_ALL_DIGITAL_PINS").SetIRange(5e-3);
			TheInst.PPMU().Pins("g_ALL_DIGITAL_PINS").SetVForce(0);
			TheInst.PPMU().Pins("g_ALL_DIGITAL_PINS").Connect(1);
//			TheInst.PPMU().Pins("g_ALL_DIGITAL_PINS").Measure();
    		TheInst.PPMU().Pins("g_ALL_DIGITAL_PINS").Apply();

//    		PinArrayDouble result = TheInst.PPMU().Pins("g_ALL_DIGITAL_PINS").GetMeasureResults();
//    		result.ShowPinArrayData();

    	    string strPinName = "AVDD08_DAC_TX,AVDD08_CKI_CKO_SA,AVDD18_DAC_TX,AVDD18_DCO_ISO_SA,AVDD18_FB,CVDD08_DAC_TX,DVDD18,EFUSE18_VQPS,LVCC08,VDD08_LVDS,VDD18_LVDS,VDDHV18,VDDLV08,AVDD18_TS,TEST_FB,HVCC12,VDD08";
    	    TheInst.DCVI().Power().Apply();
    	    cout<<"do power force off by apply power block"<<endl;
			TheInst.DCVI().Pins(strPinName).SetIClampL(-0.5);
			TheInst.DCVI().Pins(strPinName).SetIClampH(0.5);
        	TheInst.DCVI().Pins(strPinName).SetMeasureMode(E_DC_MODE_MI);
			TheInst.DCVI().Pins(strPinName).SetMeasureMethod(E_DC_METHOD_STATIC);
			TheInst.DCVI().Pins(strPinName).SetReadMode(E_DC_MODE_MEASURE);
			TheInst.DCVI().Pins(strPinName).SetIRange(E_POWER_BEST_FIT);
			TheInst.DCVI().Pins(strPinName).SetVForce(0.0);
			TheInst.DCVI().Pins(strPinName).Connect();
			TheInst.DCVI().SetWaitTime(0.005);
			TheInst.DCVI().Pins(strPinName).Apply();
//    		TheInst.DCVI().Pins(strPinName).Measure();
    }

};
REGISTER_TESTCLASS("powerOFF",powerOFF)


class Ubit_control: public TestClass{
public:

    void init(){}
    void execute(){

		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;

			TheInst.Util().SetUserPower(E_USERPW_P5V, 0);
	    	int i = -1;
//	    	for(uint32_t j=0;j<256;j++)
//	    	{
//	    		TheInst.Util().SetRelayState(j, 0); //bihe-0,duankai-1
//	    		TheInst.Wait(0.002);
//	    		i = TheInst.Util().GetRelayState(j);
//				printf("Relay %d, state %d  -- 0 open, 1 close\n ",j,i);
//				TheInst.Wait(0.002);
//	    	}

    }

};
//
REGISTER_TESTCLASS("Ubit_control",Ubit_control)
//class power_osd: public TestClass{
//public:
//    std::string powerpinlist;
//
//    void init(){
//    	add_param( "powerpinlist",  "PinString", &powerpinlist);
//
//    }
//
//    void execute(){
//		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
//		string strTestsuiteName = sTestsuiteName;
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
//
//    	TheInst.DCVI().Power().Apply();
//    	std::string pin = "AVDD18_FB,CVDD08_DAC_TX,AVDD08_DAC_TX,VDD08,AVDD08_CKI_CKO_SA,AVDD18_DAC_TX,AVDD18_DCO_ISO_SA,DVDD18,EFUSE18_VQPS,LVCC08,VDD08_LVDS,VDD18_LVDS,VDDHV18,VDDLV08,AVDD18_TS,HVCC12";
//    	PinArrayUInt result = TheInst.DCVI().Pins(pin).OpenKelDetect(0.5,0.5);
//    	result.ShowPinArrayData();
//
//    }
//
//};




//
//REGISTER_TESTCLASS("power_osd",power_osd)
//
//class Basic_00_PowerShort: public TestClass{
//public:
//    std::string powerpinlist;
//    double VForce;
//	double LIClamp;
//	double HIClamp;
//	double Clampdelay;
//	double waittime;
//    int SampleSize;
//
//    void init(){
//        add_param( "powerpinlist",  "PinString", &powerpinlist)
//                .set_default("DCVI,DCVI_NOFB")
//                .set_options("DCVI,DCVI_NOFB");
//        add_param("VForce","double",&VForce).set_default("0.1");
//        add_param("LIClamp","double",&LIClamp).set_default("-0.025");
//        add_param("HIClamp","double",&HIClamp).set_default("0.025");
//        add_param("Clampdelay","double",&Clampdelay).set_default("0.0");
//        add_param("waittime","double",&waittime).set_default("5000");
//
//        add_param("SampleSize","int",&SampleSize).set_default("16");;
//    }
//
//    void execute(){
//
//		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
//		string strTestsuiteName = sTestsuiteName;
//
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
//
//    	TheInst.DCVI().Power().Apply();
//
//    	if(PrintDebugEn) cout<<" power apply at here"<<endl;
//    	string pinG1 = "AVDD08_DAC_TX,AVDD08_CKI_CKO_SA,AVDD18_DAC_TX,AVDD18_DCO_ISO_SA,AVDD18_FB,CVDD08_DAC_TX,DVDD18,EFUSE18_VQPS,LVCC08,VDD08_LVDS,VDD18_LVDS,VDDHV18,VDDLV08,AVDD18_TS,TEST_FB,HVCC12,VDD08";
//    	TheInst.PPMU().Pins(pinG1).SetClear();
//		TheInst.DCVI().Pins(pinG1).SetIClampL(LIClamp);
//		TheInst.DCVI().Pins(pinG1).SetIClampH(HIClamp);
//    	TheInst.DCVI().Pins(pinG1).SetMeasureMode(E_DC_MODE_MI);
//		TheInst.DCVI().Pins(pinG1).SetMeasureMethod(E_DC_METHOD_STATIC);
//		TheInst.DCVI().Pins(pinG1).SetReadMode(E_DC_MODE_MEASURE);
////		TheInst.DCVI().Pins(pinG1).SetMeasureOrder(E_DC_ORDER_GROUP);
//		TheInst.DCVI().Pins(pinG1).SetIRange(E_POWER_BEST_FIT);
//		TheInst.DCVI().Pins(pinG1).SetVForce(VForce);
//		TheInst.DCVI().Pins(pinG1).Connect();
////		TheInst.DCVI().Pins(pinG1).SetClampAlarmDelay(Clampdelay)
//		TheInst.DCVI().Pins(pinG1).SetSampleSize(16);
//		TheInst.DCVI().Pins(pinG1).SetWaitTime(0.005);
//		TheInst.DCVI().Pins(pinG1).Measure();
//
//    	PinArrayDouble result = TheInst.DCVI().Pins(pinG1).GetMeasureResults();
//    	result.ShowPinArrayData();
//
//    }
//};
//
//REGISTER_TESTCLASS("Basic_00_PowerShort",Basic_00_PowerShort)


////===================================================================================================

class HLK_Functional: public TestClass {
public:
//	bool isFirst;
	void init() {
//        add_param( "isFirst",  "bool", &isFirst)
//                .set_default("false")
//                .set_options("true,false");
	}

	void execute() {
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;

//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;

//	    if(isFirst)
//	    {
//			TheInst.Util().SetUserPower(E_USERPW_P5V, E_UTIL_STATE_ON);
//			Sleep(2000);
//			int i = -1;
//			printf("GetRelayState =0 pass -- 0 open 1 close -- UxxSy xx=relay y=state \n ");
//			for(uint32_t j=0;j<256;j++)
//			{
//				TheInst.Util().SetRelayState(j, 1); //bihe-0,duankai-1      1  for PCM , 0 for tester
//				Sleep(5);
//				i = TheInst.Util().GetRelayState(j);
//				printf("U%dS%d ",j,i);
//				if(j%16 ==0 && j>0)
//					cout<<endl;
//			}
//			cout<<endl;
//	    }
		TheInst.DCVI().Power().Apply();
		TheInst.Digital().Level().Apply();
		TheInst.Digital().Timing().Apply();

		if(PrintDebugEn)
			cout<<"power level timing apply() at here"<<endl;

		//sleep(2000); 
//		TheInst.Digital().PatEng().SetFailMode(PhxAPI::E_SET_SEQ_PF_MODE);
		TheInst.Digital().PatEng().SetFailMode(E_SET_PF_MODE);
		TheInst.Digital().Pattern().Start(); 
//		TheInst.Wait(30);

	 	map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
	 	for(auto it = result.begin(); it != result.end(); it++)
		{
	 		cout<<"passfail : "<< it->second<<endl;
		}
//	 	uint64_t executedcount=TheInst.Digital().PatEng().GetExecutedCyclesCount();
//
//	 	map<uint32_t, vector<uint32_t>> mapFailData;
//	 	std::string strPinList = "JTAG_TDO";
//
//		mapFailData = TheInst.Digital().PatEng().GetFailCycles(0,strPinList);
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



REGISTER_TESTCLASS("HLK_Functional", HLK_Functional)



class PCM_ON: public TestClass {
public:
	int isFirst;
	void init() {
        add_param( "isFirst",  "int", &isFirst)
                .set_default("0")
                .set_options("0:1");
	}

	void execute() {
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;

//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;

	    if(isFirst)
	    {
			TheInst.Util().SetUserPower(E_USERPW_P5V, E_UTIL_STATE_ON);
			TheInst.Wait(0.002);
//			int i = -1;
//			printf("GetRelayState =0 pass -- 0 open 1 close -- UxxSy xx=relay y=state \n ");
//			for(uint32_t j=0;j<256;j++)
//			{
//				TheInst.Util().SetRelayState(j, 1); //bihe-0,duankai-1      1  for PCM , 0 for tester
//				Sleep(5);
//				i = TheInst.Util().GetRelayState(j);
//				printf("U%dS%d ",j,i);
//				if(j%16 ==0 && j>0)
//					cout<<endl;
//			}
//			cout<<endl;
			int i = -1;
					int ubit[12] = {10,19,28,37,46,55,119,110,101,92,83,74};
					for(uint32_t j=0;j<12;j++)
					{
						TheInst.Util().SetRelayState(ubit[j], 1); //bihe-0,duankai-1
						Sleep(5);
						i = TheInst.Util().GetRelayState(ubit[j]);
						if (i==1)
						{
							printf("\n***********duankai Relay-  %d error**************\n",j);
						}
						Sleep(5);

					}
	    }
		TheInst.DCVI().Power().Apply();
		TheInst.Digital().Level().Apply();
		TheInst.Digital().Timing().Apply();

		if(PrintDebugEn) cout<<"power level timing apply() at here"<<endl;

		//sleep(2000);
//		TheInst.Digital().PatEng().SetFailMode(PhxAPI::E_SET_SEQ_PF_MODE);
		TheInst.Digital().PatEng().SetFailMode(E_SET_PF_MODE);
		TheInst.Digital().Pattern().Start();
//		TheInst.Wait(30);

	 	map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
	 	for(auto it = result.begin(); it != result.end(); it++)
		{
	 		cout<<"passfail : "<< it->second<<endl;
		}
//	 	uint64_t executedcount=TheInst.Digital().PatEng().GetExecutedCyclesCount();
//
//	 	map<uint32_t, vector<uint32_t>> mapFailData;
//	 	std::string strPinList = "JTAG_TDO";
//
//		mapFailData = TheInst.Digital().PatEng().GetFailCycles(0,strPinList);
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


REGISTER_TESTCLASS("PCM_ON", PCM_ON)

//
//class Basic_02_OS_VDD_PPMU: public TestClass{
//public:
//    std::string vddpinlist;
//    double iforce;
//	double vclampl;
//	double vclamph;
//	double waittime;
//	int sampleSize;
//
//    void init(){
//        add_param( "VDD_pinlist",  "PinString", &vddpinlist);
//        add_param("IForce","double",&iforce).set_default("0.0002");
//        add_param("LVClamp","double",&vclampl).set_default("0");
//        add_param("HVClamp","double",&vclamph).set_default("1");
//        add_param("Waittime","double",&waittime).set_default("0.002");
//        add_param("SampleSize","int",&sampleSize).set_default("16");
//    }
//
//    void execute(){
//		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
//		string strTestsuiteName = sTestsuiteName;
//
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
//
//		TheInst.DCVI().Power().Apply();
//	    if(PrintDebugEn) cout<<"==checking power apply at here"<<endl;
//		std::string strPinList = "gSDS_H30LR_SDS_DC,OS_NORMAL";
////        std::string strPinList ="TX_SDS0_P,TX_SDS1_P,TX_SDS2_P,TX_SDS3_P,TX_SDS0_N,TX_SDS1_N,TX_SDS2_N,TX_SDS3_N,RX_SDS0_P,RX_SDS1_P,RX_SDS2_P,RX_SDS3_P,RX_SDS0_N,RX_SDS1_N,RX_SDS2_N,RX_SDS3_N+AIR_10MS,JTAG_CSN,JTAG_TCK,JTAG_TDI,JTAG_TDO,JTAG_TMS,JTAG_TRSTN,LVC_SYSREF,POR_N,ROC_FB_BD0_SW0,ROC_FB_BD0_SW1,ROC_FB_BD1_SW0,ROC_FB_BD1_SW1,ROC_INT0,ROC_SPIA_CSN,ROC_SPIA_SCLK,ROC_SPIA_SDI,ROC_SPIA_SDIO,ROC_SPIB_CSN,ROC_SPIB_SCLK,ROC_SPIB_SDI,ROC_SPIB_SDIO,ROC_SYNC0_DA,ROC_SYNC0_FBAD,ROC_SYNC1_DA,ROC_SYNC1_FBAD,ROC_TXLO_LD0,ROC_TX_TDD_SW0,ROC_TX_TDD_SW1,RX_VGA_SW1,TX_VGA_SW1";
//		TheInst.PPMU().Pins(strPinList).SetClear();
//		TheInst.PPMU().Pins(strPinList).SetVClampH(0.5);
//		TheInst.PPMU().Pins(strPinList).SetVClampL(-1.5);
//		TheInst.PPMU().Pins(strPinList).SetMeasureType(E_MEASURE);
//		TheInst.PPMU().Pins(strPinList).SetMeasureMode(E_DC_FI_MV);
//		TheInst.PPMU().Pins(strPinList).SetIRange(500e-6);
//		TheInst.PPMU().Pins(strPinList).Connect(1);
//		TheInst.PPMU().Pins(strPinList).SetIForce(-200e-6);
//		TheInst.PPMU().Pins(strPinList).SetSampleSize(16);
//		TheInst.PPMU().Pins(strPinList).SetWaitTime(0.005);
//
//		TheInst.PPMU().Pins(strPinList).Measure();
//		PinArrayDouble Result = TheInst.PPMU().Pins(strPinList).GetMeasureResults();
//		Result.ShowPinArrayData();
//    }
//
//};
//REGISTER_TESTCLASS("Basic_02_OS_VDD_PPMU",Basic_02_OS_VDD_PPMU)
//
//
//
//class Basic_02_OS_VSS_PPMU: public TestClass{
//public:
//    std::string IO_VSSpinlist;
//    double IForce;
//	double LVClamp;
//	double HVClamp;
//	double waittime;
//	int SampleSize;
//
//    void init(){
//        add_param( "IO_VSSpinlist",  "PinString", &IO_VSSpinlist)
//                .set_default("OS_NORMAL")
//                .set_options("OS_NORMAL:gSDS_H30LR_SDS_DC");
//        add_param("IForce","double",&IForce).set_default("-0.0002");
//        add_param("LVClamp","double",&LVClamp).set_default("-1");
//        add_param("HVClamp","double",&HVClamp).set_default("0");
//        add_param("waittime","double",&waittime).set_default("0.002");
//        add_param("SampleSize","int",&SampleSize).set_default("16");
//    }
//
//
//    void execute(){
//		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
//		string strTestsuiteName = sTestsuiteName;
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
//
//		std::string strPinList = "OS_NORMAL";
//
//		TheInst.PPMU().Pins(strPinList).SetClear();
//		TheInst.PPMU().Pins(strPinList).SetVClampH(HVClamp);
//		TheInst.PPMU().Pins(strPinList).SetVClampL(LVClamp);
//		TheInst.PPMU().Pins(strPinList).SetMeasureMode(E_DC_FI_MV);
//		TheInst.PPMU().Pins(strPinList).SetMeasureType(E_MEASURE);
//		TheInst.PPMU().Pins(strPinList).SetIRange(2);
//		TheInst.PPMU().Pins(strPinList).Connect(1);
//		TheInst.PPMU().Pins(strPinList).SetIForce(IForce);
//		TheInst.PPMU().Pins(strPinList).SetSampleSize(16);
//		TheInst.PPMU().Pins(strPinList).SetWaitTime(0.005);
//
//		TheInst.PPMU().Pins(strPinList).Measure();
//		TheInst.PPMU().Pins(strPinList).SetIForce(0.0);
//		TheInst.PPMU().Pins(strPinList).Connect(0);
//
//		PinArrayDouble Result = TheInst.PPMU().Pins(strPinList).GetMeasureResults();
//		Result.ShowPinArrayData();
//
//		cout<<"======== please note, clamp Low is -1 ,maybe there is not device in socket ========";
//
//    }
//
//};
//
//
//REGISTER_TESTCLASS("Basic_02_OS_VSS_PPMU",Basic_02_OS_VSS_PPMU)
//
//
//
//class Basic_03_DC_Leakage: public TestClass{
//public:
//    std::string leakagepinlist;
//    string VForce;
//	double LIClamp;
//	double HIClamp;
//	double waittime;
//
//	int SampleSize;
//
//    void init(){
//        add_param( "IOpinlist",  "PinString", &leakagepinlist)
//                .set_default("IIHL")
//                .set_options("IIHL:IIHL_PU");
//        add_param("VForce","VString",&VForce).set_default("0");
//        add_param("LIClamp","double",&LIClamp).set_default("-2");
//        add_param("HIClamp","double",&HIClamp).set_default("2");
//        add_param("waittime","double",&waittime).set_default("0.005");
//        add_param("SampleSize","int",&SampleSize).set_default("16");
//    }
//
//    void execute(){
//
//		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
//		string strTestsuiteName = sTestsuiteName;
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
//
//		TheInst.DCVI().Power().Apply();
//		TheInst.Digital().Level().Apply();
//		TheInst.Digital().Timing().Apply();
//		TheInst.Digital().Pattern().Start();
//
//		map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
//		for(auto it = result.begin(); it != result.end(); it++)
//		{
//			cout<<"passfail :"<< it->second<<endl;
//		}
//
//		PinArrayDouble Result;
//		PinArrayDouble Result1;
//		leakagepinlist = "IIHL";
//		TheInst.PPMU().Pins(leakagepinlist).SetClear();
//		TheInst.PPMU().Pins(leakagepinlist).SetIClampH(2e-6);
//		TheInst.PPMU().Pins(leakagepinlist).SetIClampL(-2e-6);
//		TheInst.PPMU().Pins(leakagepinlist).SetMeasureMode(E_DC_FV_MI);
//		TheInst.PPMU().Pins(leakagepinlist).SetMeasureType(E_MEASURE);
//		TheInst.PPMU().Pins(leakagepinlist).SetIRange(5e-6);
//		TheInst.PPMU().Pins(leakagepinlist).SetVForce(1.89);
//		TheInst.PPMU().Pins(leakagepinlist).Connect(1);
//		TheInst.PPMU().Pins(leakagepinlist).SetSampleSize(16);
//		TheInst.PPMU().Pins(leakagepinlist).SetWaitTime(0.005);
//		TheInst.PPMU().Pins(leakagepinlist).Measure();
//
//
//		printf("**************111111111111111");
//		//Sleep(200);
//		TheInst.PPMU().Pins(leakagepinlist).Measure();
//		TheInst.PPMU().Pins(leakagepinlist).SetVForce(0.0);
//		TheInst.PPMU().Pins(leakagepinlist).Connect(0);
//
//		Result = TheInst.PPMU().Pins(leakagepinlist).GetMeasureResults();
//
//
//		TheInst.PPMU().Pins(leakagepinlist).SetClear();
//		TheInst.PPMU().Pins(leakagepinlist).SetIClampH(2e-6);
//		TheInst.PPMU().Pins(leakagepinlist).SetIClampL(-2e-6);
//		TheInst.PPMU().Pins(leakagepinlist).SetMeasureMode(E_DC_FV_MI);
//		TheInst.PPMU().Pins(leakagepinlist).SetMeasureType(E_MEASURE);
//		TheInst.PPMU().Pins(leakagepinlist).SetIRange(5e-6); //5 uA
//		TheInst.PPMU().Pins(leakagepinlist).SetVForce(0);
//		TheInst.PPMU().Pins(leakagepinlist).Connect(1);
//		TheInst.PPMU().Pins(leakagepinlist).SetSampleSize(32);
//		TheInst.PPMU().Pins(leakagepinlist).SetWaitTime(0.005);
//		TheInst.PPMU().Pins(leakagepinlist).Measure();
//
//		Result1 = TheInst.PPMU().Pins(leakagepinlist).GetMeasureResults();
//		TheInst.PPMU().Pins(leakagepinlist).Connect(0);
//
//		cout<<"**************Force 1.89V"<<endl;
//		Result.ShowPinArrayData();
//		cout<<"**************Force 0V"<<endl;
//		Result1.ShowPinArrayData();
//
//		}
//
//    //}
//
//};
//
//REGISTER_TESTCLASS("Basic_03_DC_Leakage",Basic_03_DC_Leakage)
//
//
//class Basic_04_DC_IDDQ_Measure: public TestClass{
//public:
//    std::string measurepin;
//    double vforce;
//    double iclamph;
//    double iclampl;
//
//	void init(){
//		add_param( "MeasurePin",  "PinString", &measurepin);
//		add_param( "Vforce",  "double", &vforce);
//		add_param( "IClampH",  "double", &iclamph);
//		add_param( "IClampL",  "double", &iclampl);
//	}
//    void execute(){
//    	//    	cout << "!!!Hello Basic_04_DC_IDDQ_Measure!!!" << endl;
//    	//    	TheSoft.Message().InfoMessage("Basic_04_DC_IDDQ_Measure");
//
//
//		TheInst.DCVI().Power().Apply();
//		TheInst.Digital().Level().Apply();
//		TheInst.Digital().Timing().Apply();
//
//    	TheInst.DCVI().Pins("measurepin").SetMeasureMode(E_DC_MODE_MI);
//		TheInst.DCVI().Pins("measurepin").SetMeasureMethod(E_DC_METHOD_TRIGGER);
//		TheInst.DCVI().Pins("measurepin").SetReadMode(E_DC_MODE_MEASURE);
//		TheInst.DCVI().Pins("measurepin").SetVForce(vforce);
//		TheInst.DCVI().Pins("measurepin").SetIRange(E_POWER_BEST_FIT);
//		TheInst.DCVI().Pins("measurepin").SetIClampH(iclamph);
//		TheInst.DCVI().Pins("measurepin").SetIClampL(iclampl);
//		TheInst.DCVI().Pins("measurepin").SetSampleSize(16);
//		TheInst.DCVI().Pins("measurepin").SetWaitTime(0.005);	//unit:us
//		TheInst.DCVI().Pins("measurepin").Measure();
//
//    	TheInst.Digital().Pattern().Start();
//
//    	vector<PinArrayDouble> iddq_result = TheInst.DCVI().Pins("measurepin").GetTrigResults();
//
//    	for(int i =0; i <iddq_result.size(); i++)
//		{
//			iddq_result[i].ShowPinArrayData();
//			//TheSoft.Flow().TestLimit(iddq_result[i]);
//			//TheSoft.Datalog().DatalogMultiParametricTest(iddq_result[i],"DC_IDDQ");
//		}
//    }
//
//};
//REGISTER_TESTCLASS("Basic_04_DC_IDDQ_Measure",Basic_04_DC_IDDQ_Measure)
//
//
//#define I2C_DELAY 		4
//
//class Basic_07_TSensor_Read: public TestClass{
//public:
//	std::string CapPin;
//	std::string DieID_TSR_Read;
//	std::string DieID_TSR_Ref;
//	double T_A;
//	double T_B;
//	int Cnt;
//	int Delta_Temp;
//	int Temp_Ref;
//	int N_sample;
//
//    void init(){
//    	add_param( "TSensor_CapPin",  "PinString", &CapPin).set_default("JTAG_TDO");
//    	add_param( "TSersor_DieID_TSR_Read",  "String", &DieID_TSR_Read).set_default("TSR1");
//    	add_param( "TSersor_DieID_TSR_Ref",  "String", &DieID_TSR_Ref).set_default("TSR_REF");
//		add_param("TSensor_T_A","double",&T_A).set_default("116");
//		add_param("TSensor_T_B","double",&T_B).set_default("922");
//		add_param("TSersor_Cnt","int",&Cnt).set_default("1");
//		add_param("TSersor_Delta_Temp","int",&Delta_Temp).set_default("0");
//		add_param("TSersor_Temp_Ref","int",&Temp_Ref).set_default("25");
//		add_param("TSensor_N_sample","int",&N_sample).set_default("16");
//
//    }
//
//    void execute(){
//
////		    	cout << "!!!Hello Basic_07_TSensor_Read!!!" << endl;
////		    	TheSoft.Message().InfoMessage("Basic_07_TSensor_Read");
//
//
//		TheInst.DCVI().Power().Apply();
//		TheInst.Digital().Level().Apply();
//		TheInst.Digital().Timing().Apply();
//		TheInst.Digital().Pattern().Start();
//
//	    int num =Cnt*N_sample*10;
//	    int cap_data_re[num];
//	    double TSensor_Temp[Cnt][N_sample];
//	    double SUM_Temp[Cnt];
//	    double TsensorAvg_SDBL[Cnt];
//
//	    map<uint32_t, map<string, vector< uint8_t > > > CAP_Data = TheInst.Digital().PatEng().GetCaptureRawData("JTAG_TDO");
//	    //map<uint32_t, map<string, vector< uint8_t > > > CAP_Data = TheInst.Digital().PatEng().GetCapturewRawData("JTAG_TDO");//1.0.3.6
//		map<string, vector<uint8_t>> capFailData;
//		vector<uint8_t> data;
//
//		if(CAP_Data.size() > 0U)
//		{
//			for(auto it = CAP_Data.begin(); it != CAP_Data.end(); it++)
//			{
//				cout<<"\n\nSite Number : " << dec << it->first<<endl;
//					capFailData = it->second;
//
//				for(auto pit = capFailData.begin(); pit != capFailData.end(); pit++)
//				{
//					cout<<"\nPin Name : " <<  (pit->first)<<endl;
//					data = (pit->second);
//					cout<<"Cap result : bit 0 ~ 19"<<endl;
//				}
//				cout<<endl;
//			}
//			cout<< "cature size: " << data.size() <<endl;
//			for(int i = 0; i < data.size(); i++)
//			{
//				cap_data_re[i] = (int)(data[i])>>2;
//				cout<<"\ncapture data1111111 is : " << cap_data_re[i] <<endl;
//			}
//		}
//		else
//		{
//			cout<<"\n\nThere's no capture data !"<<endl;
//		}
//
//
//		for(int Count=0; Count<Cnt; Count++){ //Cnt =1
//			SUM_Temp[Count]=0.0;
//
//			for(int i=Count*16; i<N_sample*(Count+1); i++){
//				TSensor_Temp[Count][i]={0};
//				int data123[10]={0};
//				for(int j=0; j<10; j++){
//					data123[j]=cap_data_re[i*10+j];
//					TSensor_Temp[Count][i]=TSensor_Temp[Count][i]+data123[j]*pow(2,j);
//				}
//
//				cout<<"\TSensor_Temp data is : " << TSensor_Temp[Count][i] << " temp result ="<<((TSensor_Temp[Count][i] - T_A)/(T_B-T_A) * (125 + 40) -40) <<endl;
//
//				SUM_Temp[Count] = SUM_Temp[Count] + TSensor_Temp[Count][i];
//			}
//			cout<<"\n*********** SUM_Temp data is : " << SUM_Temp[Count] <<" ";
//			TsensorAvg_SDBL[Count]=((SUM_Temp[Count]/N_sample) - T_A)/(T_B-T_A) * (125 + 40) -40;
//			printf("TsensorAvg_SDBL is %lf **************\n",TsensorAvg_SDBL[Count]);
//		}
//
//    }
//
//};
//REGISTER_TESTCLASS("Basic_07_TSensor_Read",Basic_07_TSensor_Read)
//
//
//d2sWorkModeType mode1 = LearningMode;    //ProductionMode    LearningMode
//class SPI_CHECK: public TestClass{
//public:
//	d2sSPI ds;
//    void init(){
//
//    }
//
//    void execute(){
//    	cout<<" =========================== "<<endl;
//    	cout<<" ======Enter  SPI_CHECK === "<<endl;
//    	cout<<" =========================== "<<endl;
////    	//xixi
//		TheInst.Util().SetUserPower(E_USERPW_P5V, E_UTIL_STATE_ON);
//		Sleep(1000*1.5);
//    	int i = -1;
//    	for(uint32_t j=0;j<256;j++)
//    	{
//
//    		TheInst.Util().SetRelayState(j, 0); //bihe-0,duankai-1
//    		Sleep(I2C_DELAY);
//    		i = TheInst.Util().GetRelayState(j);
//			printf("Relay %d, state %d  -- 0 open, 1 close\n ",j,i);
//    		Sleep(I2C_DELAY);
//    	}
//
//    	/* step1:  apply current power,level,timing,pattern*/
//		TheInst.DCVI().Power().Apply();
//		TheInst.Digital().Level().Apply();
//		TheInst.Digital().Timing().Apply();
//////		TheInst.Wait(5000);
//    	//xixi
//
//		ds.d2s_LABEL_BEGIN("SPI_Read_dbg",mode1);   //ProductionMode  LearningMode
//		ds.read(0x141000F0,"REG1");
//		ds.d2s_LABEL_END();
//
//		// xixi
//		map<int, long long> data_multi = ds.getReadValue("REG1");
//		long long data;
//		for(auto it = data_multi.begin(); it != data_multi.end(); it++)
//		{
//			data = it->second;
//		}
//		printf("spi check result =0x%x\n",data);
//
//
//		FOREACH_ACTIVESITE_BEGIN(siteID,bInterrupt)
//		printf("check foreach activesite , site %d, spi check result =0x%x\n",siteID,data_multi[siteID]);
//		FOREACH_ACTIVESITE_END
//
//		if(data == 0x6871a110)
//			printf("test is pass\n");
//		else
//			printf("test is error\n");
//
//
//
//    }
//
//
//
//};
//
//
//REGISTER_TESTCLASS("SPI_CHECK",SPI_CHECK)
