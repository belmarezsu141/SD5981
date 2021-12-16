//#include "mapi.hpp"

#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"

using namespace std;

class SSBandGap: public TestClass
{
public:

	STRING 				mPinList;
	INT					iPrintLvl;
	void init()
	{
		add_param("PinList","PinString",&mPinList);
		add_param("PrintLvl[0~8]","int",&iPrintLvl)
					.set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
					"0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					//.setOptions("0:1:3:4:7:8")
					.set_default("3");
	}
	void execute()
	{

		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
		H30_FailBin_Flag.init(0);
		static INT iCSR_check;
		static MACRO_LANE_SEL MacroLane_Sel;
		static MACRO_DOUBLE SSBandGapVolt;
		INT iDebugAnalog;
		static bool CSRVerifyResult;

		//=============================================
		// Variables and MacroLane initialization
		//=============================================

		stSSBandGap SSBandGap = SSbandGap_SSBandGap;

//		static STRING mPinList = "";
//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);

		Select_Macro_Lane(MacroLane_Sel, SSMacroIDList, mPinList);

		//=============================================
		// Device Setup
		//=============================================
//		D2S_FRAMEWORK;
//		GET_TEST_INFO;

		/***********************************
		 STEP1. Startup Macro with SS (startup SS & CS only, DO NOT startup DS)
		 Do this Step in testflow
		 ************************************/

		/***********************************
		 STEP2. Config CSR to measure BandGap voltage
		 ************************************/
//		sprintf(label,"SSBandGap_SETUP_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN( "SSBandGap_SETUP_", Global_D2S_Mode);
		selectMacro_MB(MacroLane_Sel);
		CS.clkRegs.SliceID(0).Broadcast(1);
		CS.clkRegs.setdpmfinetuneen(0).Write2DUT(58);
		CS.clkRegs.setbiasmstratbsel(0x30).setssatbsel(0x2).Write2DUT(46);
		CS.clkRegs.setssadcinputsel(0x5).Write2DUT(39);
		//fr.d2s_LABEL_END();

		d2s::d2s_LABEL_END();

		/***********************************
		 STEP3. Get SS ADC data
		 ************************************/
		uint adcFreq = 4; // 0=25KHz, 1=50KHz, 2=100KHz, 3=200KHz, 4=400KHz,5=800KHz, 6=1.6Mhz, 7=3.2MHz
		uint useVbgAsRef = 0; // indicate which reference voltage select, 0=hvcc(1200mV), 1=bandgap(800mV).
		uint decmFactor = 2; //decimation Factor slect, 0=256, 1=512, 2=1024, 3=2048.
		uint refVoltage = 1200; // accurate reference voltage in mV.
		uint avgTime = 1;
		uint returnType = 0; //return type select, 0=return volatge value in mV, 1=return dfdata.
		uint adcinputsel = 5;
		SsGetAdcData(MacroLane_Sel, SSBandGapVolt, adcFreq, useVbgAsRef,
				decmFactor, refVoltage, avgTime, returnType, adcinputsel);

		/***********************************
		 STEP4. Restore CSR
		 ************************************/
//		sprintf(label,"SSBandGap_restore_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN( "SSBandGap_restore_",Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);
		CS.clkRegs.SliceID(0).Broadcast(1);
		CS.clkRegs.setbiasmstratbsel(0).Write2DUT(46);
		CS.clkRegs.setssatbsel(0).Write2DUT(46);
		CS.clkRegs.setssadcinputsel(0).Write2DUT(39);
		CS.clkRegs.setdpmfinetuneen(1).Write2DUT(58);
		CS.clkRegs.setcstopfsm_cal_start(1).Write2DUT(58);
//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();

		//=============================================
		// Datalog
		//=============================================
		double LimitL = 760;
		double LimitH = 840;
		HiLink_PerMacro_Judge(MacroLane_Sel, "SSBandGap_Voltage", LimitL,
				SSBandGapVolt, LimitH);

		SetTestBin();

	}

};
REGISTER_TESTCLASS("SSBandGap", SSBandGap)

