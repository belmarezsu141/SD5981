/*
 * Execute_functions.cpp
 *
 *  Created on: 2021年7月30日
 *      Author: KF106
 */


#include <HILINK_DC/Execute_functions.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include "TestClass.h"
#include <UserAPI.h>

#include <HILINK_DRIVE/d2s_IP_JTAG.h>

using namespace PhxAPI;

int HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1()
{
	string powerBlockName = "Hilink_General_Power_FP_H";
	string levelBlcokName = "HILINK_LVL_FUN_H";
	string timingBlockName = "TIM_HiLink30LR";
	string patternName = "HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1";


	TheSoft.Flow().Power().SetPower(powerBlockName);
	TheSoft.Flow().Level().SetLevel(levelBlcokName);
	TheInst.DCVI().Power().Apply();
	TheInst.Digital().Level().Apply();

	TheInst.Wait(0.005);
	if(PrintDebugEn) cout<<"in HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1  apply/level  power_FP"<<endl;


//	TheInst.Digital().Timing().Apply();

	TheInst.Digital().PatEng().SetFailMode(E_SET_PF_MODE);
	TheInst.Digital().Pattern().Start(patternName);

 	map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
 	for(auto it = result.begin(); it != result.end(); it++)
	{
 		if(PrintDebugEn) cout<<"================== HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1 passfail :"<< it->second<<endl;
	}


	return 0;
}
int PowerUpCtrl_test1()
{
	string powerBlockName = "Hilink_General_Power_FP";
	string levelBlcokName = "HILINK_LVL_FUN";
	string timingBlockName = "TIM_HiLink30LR";
	string patternName = "HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1";

//	TheInst.DCVI().Power().Apply();
//	TheInst.Digital().Level().Apply();
//	TheInst.Digital().Timing().Apply();

	TheInst.Digital().PatEng().SetFailMode(E_SET_PF_MODE);
	TheInst.Digital().Pattern().Start(patternName);

	TheInst.Wait(0.003);
 	map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
 	for(auto it = result.begin(); it != result.end(); it++)
	{
 		if(PrintDebugEn)cout<<"================== PowerUpCtrl_test1 passfail :"<< it->second<<endl;
	}
	return 0;
}

int Init_test1()
{
	string powerBlockName = "Hilink_General_Power";
	string levelBlcokName = "HILINK_LVL_FUN";
	string timingBlockName = "TIM_HiLink30LR";
	string patternName = "HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02";

//	TheInst.DCVI().Power().Apply();
//	TheInst.Digital().Level().Apply();
//	TheInst.Digital().Timing().Apply();


	TheInst.Digital().Pattern().Start(patternName);
	TheInst.Wait(0.003);
 	map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
 	for(auto it = result.begin(); it != result.end(); it++)
	{
 		if(PrintDebugEn) cout<<"================== HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02 passfail :"<< it->second<<endl;
	}
	return 0;
}

int Init_test2()
{
	string powerBlockName = "Hilink_General_Power";
	string levelBlcokName = "HILINK_LVL_FUN";
	string timingBlockName = "TIM_HiLink30LR";
	string patternName = "HILINK_R01_HI6871V110A_INIT_ALL_REF2_Case02";

//	TheInst.DCVI().Power().Apply();
//	TheInst.Digital().Level().Apply();
//	TheInst.Digital().Timing().Apply();


	TheInst.Digital().Pattern().Start(patternName);
	TheInst.Wait(0.003);
 	map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
 	for(auto it = result.begin(); it != result.end(); it++)
	{
 		cout<<"================== HILINK_R01_HI6871V110A_INIT_ALL_REF2_Case02 passfail :"<< it->second<<endl;
	}
	return 0;
}

int  H30_Disconnect_TX_RX_DZ()
{
	string powerBlockName = "Hilink_General_Power";
	string levelBlcokName = "HILINK_LVL_FUN";
	string timingBlockName = "TIM_HiLink30LR";
	string patternName = "H30_Disconnect_TX_RX_DZ";

//	TheInst.DCVI().Power().Apply();
//	TheInst.Digital().Level().Apply();
//	TheInst.Digital().Timing().Apply();

	TheInst.Digital().Pattern().Start(patternName);
	TheInst.Wait(0.005);
 	map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
 	for(auto it = result.begin(); it != result.end(); it++)
	{
 		cout<<"================== H30_Disconnect_TX_RX_DZ passfail :"<< it->second<<endl;
	}
	return 0;
}
int  H30LR_Rx_setupN() //recheck OK 20210823
{
	string powerBlockName = "Hilink_General_Power";
	string levelBlcokName = "HILINK_LVL_FUN";
	string timingBlockName = "TIM_HiLink30LR";
	string patternName = "H30_Disconnect_TX_RX_DZ";

//	TheInst.DCVI().Power().Apply();
//	TheInst.Digital().Level().Apply();
//	TheInst.Digital().Timing().Apply();


	TheInst.Digital().Pattern().Start(patternName);
	TheInst.Wait(0.003);
 	map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
 	for(auto it = result.begin(); it != result.end(); it++)
	{
 		cout<<"================== H30LR_Rx_setupN passfail :"<< it->second<<endl;
	}
	return 0;
}

PinArrayDouble H30LR_RxDiffBefCAL_ForceP()
{
	double vforce = -250e-3; //250mV
	double irange = 5e-3;//5mA  check 20210903
	int sampleSize =128;
	double waittime =5e-3; //3ms

	string Pins_N = "RX_SDS0_N,RX_SDS1_N,RX_SDS2_N,RX_SDS3_N";

	TheInst.PPMU().Pins(Pins_N).SetClear();
	TheInst.PPMU().Pins(Pins_N).SetMeasureType(E_MEASURE);
	TheInst.PPMU().Pins(Pins_N).SetIClampH(0.95*irange);
	TheInst.PPMU().Pins(Pins_N).SetIClampL(-0.95*irange);
	TheInst.PPMU().Pins(Pins_N).SetIRange(irange);
	TheInst.PPMU().Pins(Pins_N).SetVForce(0.0);
	TheInst.PPMU().Pins(Pins_N).SetMeasureMode(E_DC_FV_MI);
	TheInst.PPMU().Pins(Pins_N).Connect(1);
	TheInst.PPMU().Pins(Pins_N).SetSampleSize(sampleSize);
	TheInst.PPMU().Pins(Pins_N).Apply();

	string Pins = "RX_SDS0_P,RX_SDS1_P,RX_SDS2_P,RX_SDS3_P";

	TheInst.PPMU().Pins(Pins).SetClear();
	TheInst.PPMU().Pins(Pins).SetMeasureType(E_MEASURE);
	TheInst.PPMU().Pins(Pins).SetIClampH(0.95*irange);
	TheInst.PPMU().Pins(Pins).SetIClampL(-0.95*irange);
	TheInst.PPMU().Pins(Pins).SetIRange(irange);
	TheInst.PPMU().Pins(Pins).SetVForce(vforce)	;
	TheInst.PPMU().Pins(Pins).SetMeasureMode(E_DC_FV_MI);
	TheInst.PPMU().Pins(Pins).Connect(1);
	TheInst.PPMU().Pins(Pins).SetSampleSize(sampleSize);
	TheInst.PPMU().Pins(Pins).SetWaitTime(waittime);
	TheInst.PPMU().Pins(Pins).Measure();

	PinArrayDouble result = TheInst.PPMU().Pins(Pins).GetMeasureResults();

	TheInst.PPMU().Pins(Pins).Connect(0);
	TheInst.PPMU().Pins(Pins).SetVForce(0.0);
//	TheInst.PPMU().Pins(Pins).Apply();
//	TheInst.PPMU().Pins(Pins).Measure();
	return result;
}


PinArrayDouble H30LR_RxDiffAftCAL_ForceP()
{
	double vforce = 250e-3; //250mV
	double irange = 5e-3;//5mA
	int sampleSize =128;
	double waittime =5 * ms; //3ms

	string Pins_N = "RX_SDS0_N,RX_SDS1_N,RX_SDS2_N,RX_SDS3_N";

	TheInst.PPMU().Pins(Pins_N).SetClear();
	TheInst.PPMU().Pins(Pins_N).SetMeasureType(E_MEASURE);
	TheInst.PPMU().Pins(Pins_N).SetIClampH(0.95*irange);
	TheInst.PPMU().Pins(Pins_N).SetIClampL(-0.95*irange);
	TheInst.PPMU().Pins(Pins_N).SetIRange(irange);
	TheInst.PPMU().Pins(Pins_N).SetVForce(0.0);
	TheInst.PPMU().Pins(Pins_N).SetMeasureMode(E_DC_FV_MI);
	TheInst.PPMU().Pins(Pins_N).Connect(1);
	TheInst.PPMU().Pins(Pins_N).SetSampleSize(sampleSize);
	TheInst.PPMU().Pins(Pins_N).Apply();

	string Pins = "RX_SDS0_P,RX_SDS1_P,RX_SDS2_P,RX_SDS3_P";
	TheInst.PPMU().Pins(Pins).SetClear();
	TheInst.PPMU().Pins(Pins).SetMeasureType(E_MEASURE)	;
	TheInst.PPMU().Pins(Pins).SetIClampH(0.95*irange);
	TheInst.PPMU().Pins(Pins).SetIClampL(-0.95*irange);
	TheInst.PPMU().Pins(Pins).SetIRange(irange);
	TheInst.PPMU().Pins(Pins).SetVForce(vforce)	;
	TheInst.PPMU().Pins(Pins).SetMeasureMode(E_DC_FV_MI);
	TheInst.PPMU().Pins(Pins).Connect(1);
	TheInst.PPMU().Pins(Pins).SetSampleSize(sampleSize);
	TheInst.PPMU().Pins(Pins).SetWaitTime(waittime);
	TheInst.PPMU().Pins(Pins).Measure();

	PinArrayDouble result = TheInst.PPMU().Pins(Pins).GetMeasureResults();

	TheInst.PPMU().Pins(Pins).Connect(0);
	TheInst.PPMU().Pins(Pins).SetVForce(0.0);
//	TheInst.PPMU().Pins(Pins).Measure();
//	TheInst.PPMU().Pins(Pins).Apply();

	return result;
}


PinArrayDouble H30LR_RxdiffResBefCal_FVMI()
{
	string Pins = "RX_SDS0_P,RX_SDS1_P,RX_SDS2_P,RX_SDS3_P";
	double vforce = -250e-3; //250mV
	double irange =50e-3;//5mA
	int sampleSize =64;
	double waittime =3e-3; //3ms
	TheInst.PPMU().Pins(Pins).SetClear();
	TheInst.PPMU().Pins(Pins).SetMeasureType(E_MEASURE);
	TheInst.PPMU().Pins(Pins).SetIClampH(0.95*irange);
	TheInst.PPMU().Pins(Pins).SetIClampL(-0.95*irange);
	TheInst.PPMU().Pins(Pins).SetIRange(irange);
	TheInst.PPMU().Pins(Pins).SetVForce(vforce)	;
	TheInst.PPMU().Pins(Pins).SetMeasureMode(E_DC_FV_MI);
	TheInst.PPMU().Pins(Pins).Connect(1);
	TheInst.PPMU().Pins(Pins).SetSampleSize(sampleSize);
	TheInst.PPMU().Pins(Pins).SetWaitTime(waittime);
	TheInst.PPMU().Pins(Pins).Measure();

	PinArrayDouble result = TheInst.PPMU().Pins(Pins).GetMeasureResults();

	TheInst.PPMU().Pins(Pins).Connect(0);
	TheInst.PPMU().Pins(Pins).SetVForce(0.0);
//	TheInst.PPMU().Pins(Pins).Apply();
	TheInst.PPMU().Pins(Pins).Measure();
	return result;
}



PinArrayDouble H30LR_RxdiffResBefCal_FVMI_0V()
{
	string Pins = "TX_SDS0_N,TX_SDS1_N,TX_SDS2_N,TX_SDS3_N,TX_SDS0_P,TX_SDS1_P,TX_SDS2_P,TX_SDS3_P";
	double vforce = 0; //250mV
	double irange =50e-3;//5mA
	int sampleSize =64;
	double waittime =3e-3; //3ms
	TheInst.PPMU().Pins(Pins).SetClear();
	TheInst.PPMU().Pins(Pins).SetMeasureType(E_MEASURE);
	TheInst.PPMU().Pins(Pins).SetIClampH(0.95*irange);
	TheInst.PPMU().Pins(Pins).SetIClampL(-0.95*irange);
	TheInst.PPMU().Pins(Pins).SetIRange(irange);
	TheInst.PPMU().Pins(Pins).SetVForce(vforce);
	TheInst.PPMU().Pins(Pins).SetMeasureMode(E_DC_FV_MI);
	TheInst.PPMU().Pins(Pins).Connect(1);
	TheInst.PPMU().Pins(Pins).SetSampleSize(sampleSize);
	TheInst.PPMU().Pins(Pins).SetWaitTime(waittime);
	TheInst.PPMU().Pins(Pins).Measure();

	PinArrayDouble result = TheInst.PPMU().Pins(Pins).GetMeasureResults();
//	result.ShowPinArrayData();
	TheInst.PPMU().Pins(Pins).Connect(0);
	TheInst.PPMU().Pins(Pins).SetVForce(0.0);
//	TheInst.PPMU().Pins(Pins).Apply();
//	TheInst.PPMU().Pins(Pins).Measure();
	return result;
}


PinArrayDouble H30LR_RxDiffResBefCal_MforceV_MI_RX()
{
	string Pins = "RX_SDS0_N,RX_SDS1_N,RX_SDS2_N,RX_SDS3_N,RX_SDS0_P,RX_SDS1_P,RX_SDS2_P,RX_SDS3_P";
	double vforce = 0; //0mV
	double irange =1e-3;//1mA
	int sampleSize =64;
	double waittime =3e-3; //3ms
	TheInst.PPMU().Pins(Pins).SetClear();
	TheInst.PPMU().Pins(Pins).SetMeasureType(E_MEASURE);
	TheInst.PPMU().Pins(Pins).SetIClampH(0.95*irange);
	TheInst.PPMU().Pins(Pins).SetIClampL(-0.95*irange);
	TheInst.PPMU().Pins(Pins).SetIRange(irange);
	TheInst.PPMU().Pins(Pins).SetVForce(vforce)	;
	TheInst.PPMU().Pins(Pins).SetMeasureMode(E_DC_FV_MI);
	TheInst.PPMU().Pins(Pins).Connect(1);
	TheInst.PPMU().Pins(Pins).SetSampleSize(sampleSize);
	TheInst.PPMU().Pins(Pins).SetWaitTime(waittime);
	TheInst.PPMU().Pins(Pins).Measure();

	PinArrayDouble result = TheInst.PPMU().Pins(Pins).GetMeasureResults();
//	result.ShowPinArrayData();
	TheInst.PPMU().Pins(Pins).Connect(0);
	TheInst.PPMU().Pins(Pins).SetVForce(0.0);
//	TheInst.PPMU().Pins(Pins).Apply();
//	TheInst.PPMU().Pins(Pins).Measure();
	return result;
}



PinArrayDouble H30LR_RxSigAftCAL_ForceAll()
{
	string Pins = "RX_SDS0_N,RX_SDS1_N,RX_SDS2_N,RX_SDS3_N,RX_SDS0_P,RX_SDS1_P,RX_SDS2_P,RX_SDS3_P";
	double vforce = 0.250; //0mV
	double irange =50e-3;//1mA
	int sampleSize =128;
	double waittime =5 *ms; //3ms
	TheInst.PPMU().Pins(Pins).SetClear();
	TheInst.PPMU().Pins(Pins).SetMeasureType(E_MEASURE)	;
	TheInst.PPMU().Pins(Pins).SetIClampH(0.95*irange);
	TheInst.PPMU().Pins(Pins).SetIClampL(-0.95*irange);
	TheInst.PPMU().Pins(Pins).SetIRange(irange);
	TheInst.PPMU().Pins(Pins).SetVForce(vforce)	;
	TheInst.PPMU().Pins(Pins).SetMeasureMode(E_DC_FV_MI);
	TheInst.PPMU().Pins(Pins).Connect(1);
	TheInst.PPMU().Pins(Pins).SetSampleSize(sampleSize);
	TheInst.PPMU().Pins(Pins).SetWaitTime(waittime);
	TheInst.PPMU().Pins(Pins).Measure();

	PinArrayDouble result = TheInst.PPMU().Pins(Pins).GetMeasureResults();

	TheInst.PPMU().Pins(Pins).Connect(0);
	TheInst.PPMU().Pins(Pins).SetVForce(0.0);
//	TheInst.PPMU().Pins(Pins).Measure();
//	TheInst.PPMU().Pins(Pins).Apply();

	return result;
}



PinArrayDouble H30LR_RxSigResBefCal_FIMV_1mA()
{
	string Pins = "RX_SDS0_N,RX_SDS1_N,RX_SDS2_N,RX_SDS3_N,RX_SDS0_P,RX_SDS1_P,RX_SDS2_P,RX_SDS3_P";
	double iforce = -1e-3; //1mA
//	double irange = 5e-3;//5mA
	double vExpect = 1;//1V
	int sampleSize =64;
	double waittime =3e-3; //3ms
	TheInst.PPMU().Pins(Pins).SetClear();
	TheInst.PPMU().Pins(Pins).SetVClampH((1.25*vExpect)<6.5?(1.25*vExpect):6.5);
//	TheInst.PPMU().Pins(Pins).SetVClampL((-1.25*vExpect)>-2?(-1.25*vExpect):-2);
	TheInst.PPMU().Pins(Pins).SetVClampL(-0.5);
	TheInst.PPMU().Pins(Pins).SetIRange(fabs(iforce*1.2));
	TheInst.PPMU().Pins(Pins).SetMeasureType(E_MEASURE);
	TheInst.PPMU().Pins(Pins).SetMeasureMode(E_DC_FI_MV);
	TheInst.PPMU().Pins(Pins).Connect(1);
	TheInst.PPMU().Pins(Pins).SetIForce(iforce);
	TheInst.PPMU().Pins(Pins).SetSampleSize(sampleSize);
	TheInst.PPMU().Pins(Pins).SetWaitTime(waittime);
	TheInst.PPMU().Pins(Pins).Measure();

	PinArrayDouble result = TheInst.PPMU().Pins(Pins).GetMeasureResults();
//	result.ShowPinArrayData();
	TheInst.PPMU().Pins(Pins).SetIForce(0.0);
	TheInst.PPMU().Pins(Pins).Connect(0);
//	TheInst.PPMU().Pins(Pins).Apply();
//	TheInst.PPMU().Pins(Pins).Measure();
	return result;
}



PinArrayDouble H30LR_RxSigResBefCal_FIMV_5mA()
{
	string Pins = "RX_SDS0_N,RX_SDS1_N,RX_SDS2_N,RX_SDS3_N,RX_SDS0_P,RX_SDS1_P,RX_SDS2_P,RX_SDS3_P";
	double iforce = -5e-3; //5mA
//	double irange = 5e-3;//5mA
	double vExpect = 1.5;//1V
	int sampleSize =64;
	double waittime =3e-3; //3ms
	TheInst.PPMU().Pins(Pins).SetClear();
	TheInst.PPMU().Pins(Pins).SetVClampH((1.25*vExpect)<6.5?(1.25*vExpect):6.5);
//	TheInst.PPMU().Pins(Pins).SetVClampL((-1.25*vExpect)>-2?(-1.25*vExpect):-2);
	TheInst.PPMU().Pins(Pins).SetVClampL(-0.5);
	TheInst.PPMU().Pins(Pins).SetIRange(fabs(iforce*1.2));
	TheInst.PPMU().Pins(Pins).SetMeasureType(E_MEASURE)	;
	TheInst.PPMU().Pins(Pins).SetMeasureMode(E_DC_FI_MV);
	TheInst.PPMU().Pins(Pins).Connect(1);
	TheInst.PPMU().Pins(Pins).SetIForce(iforce);
	TheInst.PPMU().Pins(Pins).SetSampleSize(sampleSize);
	TheInst.PPMU().Pins(Pins).SetWaitTime(waittime);
	TheInst.PPMU().Pins(Pins).Measure();

	PinArrayDouble result = TheInst.PPMU().Pins(Pins).GetMeasureResults();

	TheInst.PPMU().Pins(Pins).SetIForce(0.0);
	TheInst.PPMU().Pins(Pins).Connect(0);
//	TheInst.PPMU().Pins(Pins).Apply();
//	TheInst.PPMU().Pins(Pins).Measure();
	return result;
}

PinArrayDouble H30LR_RxTermVoltToGnd_AC_FIMV_0mA()
{
	string Pins = "RX_SDS0_N,RX_SDS1_N,RX_SDS2_N,RX_SDS3_N,RX_SDS0_P,RX_SDS1_P,RX_SDS2_P,RX_SDS3_P";
	double iforce = -0e-3; //5mA
//	double irange = 5e-3;//5mA
	double vExpect = 0.05;//spec less than +- 10mV
	int sampleSize = 128;
	double waittime =10 *ms; //3ms
	TheInst.PPMU().Pins(Pins).SetClear();
	TheInst.PPMU().Pins(Pins).SetVClampH((1.25*vExpect)<6.5?(1.25*vExpect):6.5);
//	TheInst.PPMU().Pins(Pins).SetVClampL((-1.25*vExpect)>-2?(-1.25*vExpect):-2);
	TheInst.PPMU().Pins(Pins).SetVClampL(-0.5);
	TheInst.PPMU().Pins(Pins).SetIRange(5e-6); //5uA  , min current range
	TheInst.PPMU().Pins(Pins).SetMeasureType(E_MEASURE)	;
	TheInst.PPMU().Pins(Pins).SetMeasureMode(E_DC_FI_MV);
	TheInst.PPMU().Pins(Pins).Connect(1);
	TheInst.PPMU().Pins(Pins).SetIForce(iforce);
	TheInst.PPMU().Pins(Pins).SetSampleSize(sampleSize);
	TheInst.PPMU().Pins(Pins).SetWaitTime(waittime);
	TheInst.PPMU().Pins(Pins).Measure();

	PinArrayDouble result = TheInst.PPMU().Pins(Pins).GetMeasureResults();

	TheInst.PPMU().Pins(Pins).SetIForce(0.0);
	TheInst.PPMU().Pins(Pins).Connect(0);
//	TheInst.PPMU().Pins(Pins).Apply();
//	TheInst.PPMU().Pins(Pins).Measure();
	return result;
}


PinArrayDouble H30LR_TxResAftCal_FIMV_3mA()
{
	string Pins = "TX_SDS0_N,TX_SDS1_N,TX_SDS2_N,TX_SDS3_N,TX_SDS0_P,TX_SDS1_P,TX_SDS2_P,TX_SDS3_P";
	double iforce = -3e-3; //-3mA
//	double irange = 5e-3;//5mA
	double vExpect = 1.5;//1V
	int sampleSize =128;
	double waittime =5e-3; //3ms
	TheInst.PPMU().Pins(Pins).SetClear();
	TheInst.PPMU().Pins(Pins).SetVClampH((1.25*vExpect)<6.5?(1.25*vExpect):6.5);
//	TheInst.PPMU().Pins(Pins).SetVClampL((-1.25*vExpect)>-2?(-1.25*vExpect):-2);
	TheInst.PPMU().Pins(Pins).SetVClampL(-0.5);
	TheInst.PPMU().Pins(Pins).SetIRange(fabs(iforce*1.2));
	TheInst.PPMU().Pins(Pins).SetMeasureType(E_MEASURE);
	TheInst.PPMU().Pins(Pins).SetMeasureMode(E_DC_FI_MV);
	TheInst.PPMU().Pins(Pins).Connect(1);
	TheInst.PPMU().Pins(Pins).SetIForce(iforce);
	TheInst.PPMU().Pins(Pins).SetSampleSize(sampleSize);
	TheInst.PPMU().Pins(Pins).SetWaitTime(waittime);
	TheInst.PPMU().Pins(Pins).Measure();

	PinArrayDouble result = TheInst.PPMU().Pins(Pins).GetMeasureResults();


	TheInst.PPMU().Pins(Pins).SetIForce(0.0);
	TheInst.PPMU().Pins(Pins).Connect(0);
//	TheInst.PPMU().Pins(Pins).Apply();
//	TheInst.PPMU().Pins(Pins).Measure();
	return result;
}


PinArrayDouble H30LR_TxResAftCal_FIMV_4mA()  //recheck OK 20210823
{
	string Pins = "TX_SDS0_N,TX_SDS1_N,TX_SDS2_N,TX_SDS3_N,TX_SDS0_P,TX_SDS1_P,TX_SDS2_P,TX_SDS3_P";
	double iforce = -4e-3; //-3mA
//	double irange = 5e-3;//5mA
	double vExpect = 1.5;//1V
	int sampleSize =128;
	double waittime =5e-3; //3ms
	TheInst.PPMU().Pins(Pins).SetClear();
	TheInst.PPMU().Pins(Pins).SetVClampH((1.25*vExpect)<6.5?(1.25*vExpect):6.5);
	TheInst.PPMU().Pins(Pins).SetVClampL((-1.25*vExpect)>-2?(-1.25*vExpect):-2);
	TheInst.PPMU().Pins(Pins).SetIRange(fabs(iforce*1.2));
	TheInst.PPMU().Pins(Pins).SetMeasureType(E_MEASURE)	;
	TheInst.PPMU().Pins(Pins).SetMeasureMode(E_DC_FI_MV);
	TheInst.PPMU().Pins(Pins).Connect(1);
	TheInst.PPMU().Pins(Pins).SetIForce(iforce);
	TheInst.PPMU().Pins(Pins).SetSampleSize(sampleSize);
	TheInst.PPMU().Pins(Pins).SetWaitTime(waittime);
	TheInst.PPMU().Pins(Pins).Measure();

	PinArrayDouble result = TheInst.PPMU().Pins(Pins).GetMeasureResults();

	TheInst.PPMU().Pins(Pins).SetIForce(0.0);
	TheInst.PPMU().Pins(Pins).Connect(0);
//	TheInst.PPMU().Pins(Pins).Apply();
//	TheInst.PPMU().Pins(Pins).Measure();
	return result;
}



PinArrayDouble H30LR_TxTermVolt_MForce_I_0mA()
{
	string Pins = "TX_SDS0_N,TX_SDS1_N,TX_SDS2_N,TX_SDS3_N,TX_SDS0_P,TX_SDS1_P,TX_SDS2_P,TX_SDS3_P";
	double iforce = -100e-9; //-100nA
//	double irange = 5e-3;//5mA
	double vExpect = 1.2;//1V
	int sampleSize =128;
	double waittime =5e-3; //3ms
	TheInst.PPMU().Pins(Pins).SetClear();
	TheInst.PPMU().Pins(Pins).SetVClampH((1.25*vExpect)<6.5?(1.25*vExpect):6.5);
//	TheInst.PPMU().Pins(Pins).SetVClampL((-1.25*vExpect)>-2?(-1.25*vExpect):-2);
	TheInst.PPMU().Pins(Pins).SetVClampL(-0.5);
//	TheInst.PPMU().Pins(Pins).SetIRange(fabs(iforce*1.2));
	TheInst.PPMU().Pins(Pins).SetIRange(5e-6);	//5uA	// V100 5mA
	TheInst.PPMU().Pins(Pins).SetMeasureType(E_MEASURE)	;
	TheInst.PPMU().Pins(Pins).SetMeasureMode(E_DC_FI_MV);
	TheInst.PPMU().Pins(Pins).Connect(1);
	TheInst.PPMU().Pins(Pins).SetIForce(iforce);
	TheInst.PPMU().Pins(Pins).SetSampleSize(sampleSize);
	TheInst.PPMU().Pins(Pins).SetWaitTime(waittime);
	TheInst.PPMU().Pins(Pins).Measure();

	PinArrayDouble result = TheInst.PPMU().Pins(Pins).GetMeasureResults();


	TheInst.PPMU().Pins(Pins).SetIForce(0.0);
	TheInst.PPMU().Pins(Pins).Connect(0);
//	TheInst.PPMU().Pins(Pins).Apply();
//	TheInst.PPMU().Pins(Pins).Measure();
	return result;
}

PinArrayDouble H30LR_FIR_MForce_I_N0P1UA() //rechek 20210823  ok
{
	string Pins = "RX_SDS0_N,RX_SDS1_N,RX_SDS2_N,RX_SDS3_N,RX_SDS0_P,RX_SDS1_P,RX_SDS2_P,RX_SDS3_P";
	double iforce = -9e-3; //-9mA
//	double irange = 5e-3;//5mA
	double vExpect = 1.5;//1V
	int sampleSize =64;
	double waittime =3e-3; //3ms
	TheInst.PPMU().Pins(Pins).SetClear();
	TheInst.PPMU().Pins(Pins).SetVClampH((1.25*vExpect)<6.5?(1.25*vExpect):6.5);
//	TheInst.PPMU().Pins(Pins).SetVClampL((-1.25*vExpect)>-2?(-1.25*vExpect):-2);
	TheInst.PPMU().Pins(Pins).SetVClampL(-0.5);
	TheInst.PPMU().Pins(Pins).SetIRange(fabs(iforce*1.2));
	TheInst.PPMU().Pins(Pins).SetMeasureType(E_MEASURE)	;
	TheInst.PPMU().Pins(Pins).SetMeasureMode(E_DC_FI_MV);
	TheInst.PPMU().Pins(Pins).Connect(1);
	TheInst.PPMU().Pins(Pins).SetIForce(iforce);
	TheInst.PPMU().Pins(Pins).SetSampleSize(sampleSize);
	TheInst.PPMU().Pins(Pins).SetWaitTime(waittime);
	TheInst.PPMU().Pins(Pins).Measure();

	PinArrayDouble result = TheInst.PPMU().Pins(Pins).GetMeasureResults();

	TheInst.PPMU().Pins(Pins).SetIForce(0.0);
	TheInst.PPMU().Pins(Pins).Connect(0);
//	TheInst.PPMU().Pins(Pins).Apply();
//	TheInst.PPMU().Pins(Pins).Measure();
	return result;
}




PinArrayDouble H30_PWR_DC()
{
//	string timingBlockName = "TIM_HiLink30LR";
//	string patternName = "H30_Disconnect_TX_RX_DZ";

 	string powerBlockName = "Hilink_General_Power_H";
	string levelBlcokName = "HILINK_LVL_FUN_H";
	TheSoft.Flow().Power().SetPower(powerBlockName);
	TheSoft.Flow().Level().SetLevel(levelBlcokName);
	TheInst.DCVI().Power().Apply();
	TheInst.Digital().Level().Apply();
	if(PrintDebugEn) cout<<"in H30_PWR_DC  apply/level  power H"<<endl;

//	if(PrintDebugEn) cout<<"==checking== "<<"power apply at here"<<endl;
//	TheInst.Digital().LevelTiming(levelBlcokName,timingBlockName);
//	TheInst.Digital().Apply();
//	TheInst.Digital().Pattern().Start(patternName);
	string Pins = "LVCC08,HVCC12,VDD08";//
	double vforceLVCC08 = 0.8; //V
	double vforceHVCC12 = 1.2; //V
	double irange = 5e-3;//5mA
//	double vExpect = 1;//1V
	int sampleSize = 64;
	double waittime =10e-3; //10ms

	TheInst.DCVI().Pins(Pins).SetIClampL(-0.05);
	TheInst.DCVI().Pins(Pins).SetIClampH(irange*0.98);
	TheInst.DCVI().Pins(Pins).SetMeasureMode(E_DC_MODE_MI);
	TheInst.DCVI().Pins(Pins).SetMeasureMethod(E_DC_METHOD_STATIC);
	TheInst.DCVI().Pins(Pins).SetMeasureOrder(E_DC_ORDER_GROUP);
	TheInst.DCVI().Pins(Pins).SetReadMode(E_DC_MODE_MEASURE);  //must have this code, note by tony 20210830  38A not done
	TheInst.DCVI().Pins(Pins).SetIRange(E_POWER_R1A); //E_POWER_R500MA
	TheInst.DCVI().Pins(Pins).SetVForceMode(E_POWER_FV);
	TheInst.DCVI().Pins(Pins).SetVForceState(E_PW_ON);
	TheInst.DCVI().Pins("VDD08").SetVForce(vforceLVCC08);
	TheInst.DCVI().Pins("LVCC08").SetVForce(vforceLVCC08);
	TheInst.DCVI().Pins("HVCC12").SetVForce(vforceHVCC12);
	TheInst.DCVI().Pins(Pins).Connect();
	TheInst.DCVI().Pins(Pins).SetSampleSize(sampleSize);
	TheInst.DCVI().Pins(Pins).SetWaitTime(waittime);
	TheInst.DCVI().Pins(Pins).Measure();

	PinArrayDouble result = TheInst.DCVI().Pins(Pins).GetMeasureResults();

	return result;
}

