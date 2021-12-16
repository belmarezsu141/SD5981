//for test method API interfaces

#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"


class MAX_PWR: public TestClass{
public:
	STRING              TestMode;
	STRING 				mHVCC_Pin;
	STRING 				mLVCC_Pin;

	STRING 				mHVCC_Spec;
	STRING 				mLVCC_Spec;

	STRING 				mHiLink30_MacroList;
	STRING 				mPinList;
	STRING 				mPowerUpControlPattern;

	INT                 iTXDRVTAPXMODSEL;
    STRING              sLoopBackMode;
    INT                 iPll_Select;
    INT 				iPrintLvl;
	void init(){
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					.set_comment("HiLink30 Macro List for test")
					//.setOptions("0,1:0:1:FromPinList")
					.set_default("0,1");
		add_param("Pll_Select","int",&iPll_Select)
					.set_comment("iPll_Select")
					//.setOptions("0:1")
					.set_default("0");
		add_param("TestMode","string",&TestMode)
					//.setOptions("MIN_PWR:MAX_PWR")
					.set_default("MIN_PWR");
//		add_param("PinList","PinString",&mPinList);
		add_param("HVCC_Pin","PinString",&mHVCC_Pin);
		add_param("LVCC_Pin","PinString",&mLVCC_Pin);
		add_param("HVCC_Spec","string",&mHVCC_Spec);
		add_param("LVCC_Spec","string",&mLVCC_Spec);
		add_param("LoopBackMode","string",&sLoopBackMode)
					//.setOptions("PreDriver:Bump:External:Nothing")
					.set_default("Bump");
		add_param("PowerUpControlPattern","string",&mPowerUpControlPattern)
					 //.setOptions("")
					 .set_default("");
		add_param("PrintLvl[0~8]","int",&iPrintLvl)
					.set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
					"0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					//.setOptions("0:1:3:4:7:8")
					.set_default("3");
	}
	void execute(){

		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
		H30_FailBin_Flag.init(0);
		static INT iDebugAnalog;
		static INT iCSR_check;
		static DOUBLE dVcoef;
		static MACRO_LANE_SEL MacroLane_Sel;
		static SITE_DOUBLE dPower_HVCC;
		static SITE_DOUBLE dPower_LVCC;
		static SITE_DOUBLE dPower_VDD08;

		static SITE_DOUBLE dPower_Total;
		static DOUBLE HVCCtmpVoltage;
		static DOUBLE LVCCtmpVoltage;
		static bool CSRVerifyResult;

	//		ON_FIRST_INVOCATION_BEGIN();
	//
	//		GET_TESTSUITE_NAME	(sTestsuiteName);
	//		GET_TESTFLOW_FLAG	("debug_analog",&iDebugAnalog);
	//		GET_USER_FLAG		("CSR_atomic_operation",&iCSR_check);

		stMIN_MAX_PWR MIN_MAX_PWR;
//		static STRING mPinList = "";

//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER, &m_TestNumber,THE_END);

//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();
		if (strTestsuiteName == "H30_MIN_PWR_VDDH")		////PLL0_1G  1
				{
			MIN_MAX_PWR = H30_MIN_PWR_VDDH_MIN_MAX_PWR;
		} else if (strTestsuiteName == "H30_MAX_PWR_VDDH") {
			MIN_MAX_PWR = H30_MAX_PWR_VDDH_MIN_MAX_PWR;

		}

		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList, mPinList);

		//=============================================
		// Variables definition and initialization
		//=============================================
	//		DPS_TASK 				dps_task;

		STRING_VECTOR vDPSPins_HVCC;
		STRING_VECTOR vDPSPins_LVCC;
		STRING_VECTOR vDPSPinsSpec_HVCC;
		STRING_VECTOR vDPSPinsSpec_LVCC;

		if (mHVCC_Pin == "" || mLVCC_Pin == ""
				|| mHVCC_Spec == "") {
	//			cout << "ERROR: please specify the DPS pin name and spec" << endl;
//			api->info_message("ERROR: please specify the DPS pin name and spec");

			cout <<"ERROR: please specify the DPS pin name and spec"<<endl;
			//	ERROR_EXIT(TM::EXIT_FLOW);
		}

		parseListOfString(mHVCC_Pin, vDPSPins_HVCC, ',');
		parseListOfString(mLVCC_Pin, vDPSPins_LVCC, ',');
		parseListOfString(mHVCC_Spec, vDPSPinsSpec_HVCC, ',');
		parseListOfString(mLVCC_Spec, vDPSPinsSpec_LVCC, ',');

		dPower_HVCC.init(0);
		dPower_LVCC.init(0);
		dPower_VDD08.init(0);
		dPower_Total.init(0);

	//
		ARRAY_D aMeas_HVCC;
		ARRAY_D aMeas_LVCC;
		aMeas_HVCC.resize(vDPSPins_HVCC.size());
		aMeas_LVCC.resize(vDPSPins_LVCC.size());

		STRING_VECTOR vHVCC_pin, vLVCC_pin;

		//=============================================
		// Measurement
		//=============================================

		if (TestMode == "MIN_PWR") {
			MacroPowerDown( MacroLane_Sel, mPowerUpControlPattern);

		} else if (TestMode == "MAX_PWR") {
			/***********EQN setting Begin***********/
			INT iTXMAIN = 63;
			INT iTXPRE1ST = 0;
			INT iTXPOST1ST = 0;
			INT iTXPRE2ND = 0;
			INT iTXPOST2ND = 0;

			CUSTPARA Custpara;

			Custpara.TxFIR_USER.iTxMain = iTXMAIN;
			Custpara.TxFIR_USER.iTxPre1st = iTXPRE1ST;
			Custpara.TxFIR_USER.iTxPost1st = iTXPOST1ST;
			Custpara.TxFIR_USER.iTxPre2nd = iTXPRE2ND;
			Custpara.TxFIR_USER.iTxPost2nd = iTXPOST2ND;

			Custpara.PllSel = iPll_Select;

			/***********EQN setting End***********/

			//step1
			//step2
	#ifdef TestChip
			if(MacroLane_Sel.size() > 1) {
	//					cout << "ERROR: Incorret MACRO index! This test suite only support one MACRO at one time" << endl;
				std::cout<<"ERROR: Incorret MACRO index! This test suite only support one MACRO at one time"<<std::endl;
				ERROR_EXIT(TM::ABORT_FLOW);
			}
			//Only for test chip to power down the macro which is not used
			if(MacroLane_Sel[0].MacroID == 0)//BP
			{
				MacroPowerDown(1,mPowerUpControlPattern);
			}
			else if(MacroLane_Sel[0].MacroID == 1)		//C2C
			{
				MacroPowerDown(0,mPowerUpControlPattern);
			}

	#endif
			//step4
	//			D2S_FRAMEWORK;
	//			GET_TEST_INFO;

			LoopBack_Setting( sLoopBackMode, MacroLane_Sel,Custpara);

	//			sprintf(label,"MPB_MAX_Power_SETUP_%f_%f_",Vcoef,Temp);
	//			fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
			d2s::d2s_LABEL_BEGIN("MPB_MAX_Power_SETUP_",Global_D2S_Mode);

			selectMacro_MB(MacroLane_Sel);
			DS.txRegs.SliceID(0).Broadcast(1);
			DS.rxRegs.SliceID(0).Broadcast(1);

			DS.rxRegs.setrxctleibiastune(0x7).Write2DUT(36);
			DS.rxRegs.setdfepwrdb(0x1).Write2DUT(5);
			DS.rxRegs.setdfefxtappwrdb(0x1FF).Write2DUT(5);
			DS.rxRegs.setdfemvtappwrdb(0x1).Write2DUT(5);

			DS.rxRegs.setdfefxtap1cen(0x7F).Write2DUT(51);
			DS.rxRegs.setdfefxtap1edg(0x7F).Write2DUT(51);

			DS.rxRegs.setdfefxtap2(0x3F).Write2DUT(6);

			DS.rxRegs.setdfefxtap3(0x1F).Write2DUT(7);
			DS.rxRegs.setdfefxtap4(0x1F).Write2DUT(7);

			DS.rxRegs.setdfefxtap5(0x1F).Write2DUT(8);
			DS.rxRegs.setdfefxtap6(0xF).Write2DUT(8);
			DS.rxRegs.setdfefxtap7(0xF).Write2DUT(8);

			DS.rxRegs.setdfefxtap8(0xF).Write2DUT(9);
			DS.rxRegs.setdfefxtap9(0xF).Write2DUT(9);

			DS.rxRegs.setdfemvtap1(0xF).Write2DUT(10);
			DS.rxRegs.setdfemvtap2(0xF).Write2DUT(10);
			DS.rxRegs.setdfemvtap3(0xF).Write2DUT(10);

			DS.rxRegs.setdfemvtap4(0xF).Write2DUT(11);
			DS.rxRegs.setdfemvtap5(0xF).Write2DUT(11);
			DS.rxRegs.setdfemvtap6(0xF).Write2DUT(11);

			SetTxFir( Custpara);
			EnableTxPrbsGen( "PRBS15");
			d2s::d2s_LABEL_END();
	//		fr.d2s_LABEL_END();
		} else {
			hout(DETAIL)
					<< "ERROR: Incorret test mode !! Only choose MIN_PWR or MAX_PWR"
					<< endl;
	//			ERROR_EXIT(TM::ABORT_FLOW);
		}

		//
		/* the spec name in level must be same as the pin name, so this method could get the corrrect voltage value*/
	//		dps_task.samples(20);

//		api->Execute_test("H30_PWR_DC");
		PinArrayDouble H30LR_MINMAXPWR_Measure_result = H30_PWR_DC();
		if(PrintDebugEn) H30LR_MINMAXPWR_Measure_result.ShowPinArrayData();

		double data1[10]= { 0 };
		double data2[10]= { 0 };
		double data3[10]= { 0 };
//		double resource[10] = { 0 };
//		data1 = resource;		/////初始化指针
//		data2 = resource;		/////初始化指针
//		string Pins = "LVCC08,HVCC12";
		vector<string> PinList = {"HVCC12","LVCC08","VDD08"};


//		FOREACH_ACTIVE_SITE(api)
//		{
//			int SiteID = api->Get_active_site();

		int tempTestNumber=0;
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		tempTestNumber=0;

		data1[0] =  H30LR_MINMAXPWR_Measure_result.GetData(PinList[0],SiteID);
		data2[0] =  H30LR_MINMAXPWR_Measure_result.GetData(PinList[1],SiteID);
		data3[0] =  H30LR_MINMAXPWR_Measure_result.GetData(PinList[2],SiteID);

		if(PrintDebugEn) cout<<PinList[0] <<" HVCC12  data1[0]= "  <<data1[0] <<endl;
		if(PrintDebugEn) cout<<PinList[1] <<" LVCC08  data2[0]= "  <<data2[0] <<endl;
		if(PrintDebugEn) cout<<PinList[1] <<" VDD08   data3[0]= "  <<data3[0] <<endl;

			if (vDPSPins_HVCC.size() > 0) {
				parseListOfString(mHVCC_Pin, vHVCC_pin, ',');
				for (uint dpsIndex = 0; dpsIndex < vHVCC_pin.size(); dpsIndex++) {
	//            			FW_TASK("PSLV?PRM,(" + vHVCC_pin[dpsIndex] + ")",sCurrent_Limit);
	//            			parseListOfString(sCurrent_Limit,vCurrent_Limit,',');
	//            			iCurrent_Limit = atoi(vCurrent_Limit[2].c_str());
	//            			dps_task.pin(vHVCC_pin[dpsIndex]).measurementMode(TM::MEASURE_CURRENT).min(0 uA).max(iCurrent_Limit A);
					const char * HVCC_pin;
					HVCC_pin = vHVCC_pin[dpsIndex].c_str();
//					api->Get_dctest_values("H30LR_MINMAXPWR_Measure", HVCC_pin, 0,THE_MEASURE, &data1, THE_END);

					aMeas_HVCC[dpsIndex] = data1[0]; //V100 replaced
//					aMeas_HVCC[dpsIndex] = H30LR_MINMAXPWR_Measure_result.GetData(PinList[0],SiteID);
				}
			}

			if (vDPSPins_LVCC.size() > 0) {
				parseListOfString(mLVCC_Pin, vLVCC_pin, ',');
				for (uint dpsIndex = 0; dpsIndex < vLVCC_pin.size(); dpsIndex++) {
	//            			FW_TASK("PSLV?PRM,(" + vLVCC_pin[dpsIndex] + ")",sCurrent_Limit);
	//            			parseListOfString(sCurrent_Limit,vCurrent_Limit,',');
	//            			iCurrent_Limit = atoi(vCurrent_Limit[2].c_str());
	//            			dps_task.pin(vLVCC_pin[dpsIndex]).measurementMode(TM::MEASURE_CURRENT).min(0 uA).max(iCurrent_Limit A);
					const char * LVCC_pin;
					LVCC_pin = vLVCC_pin[dpsIndex].c_str();
//					api->Get_dctest_values("H30LR_MINMAXPWR_Measure", LVCC_pin, 0,THE_MEASURE, &data2, THE_END);

					aMeas_LVCC[dpsIndex] = data2[0];
//					aMeas_LVCC[dpsIndex] = H30LR_MINMAXPWR_Measure_result.GetData(PinList[1],SiteID);
				}
			}

			for (UINT i = 0; i < vDPSPins_HVCC.size(); i++) {

				HVCCtmpVoltage = 1.2; //V
				dPower_HVCC[SiteID] = dPower_HVCC[SiteID]
						+ aMeas_HVCC[i] * HVCCtmpVoltage; //W
			}
			for (UINT i = 0; i < vDPSPins_LVCC.size(); i++) {
				LVCCtmpVoltage = 0.8; //V
				dPower_LVCC[SiteID] = dPower_LVCC[SiteID]
						+ aMeas_LVCC[i] * LVCCtmpVoltage; //W
			}
			dPower_VDD08[SiteID] = data3[0] * 0.8;
//			dPower_Total[SiteID] = dPower_HVCC[SiteID] + dPower_LVCC[SiteID]; //W
			dPower_Total[SiteID] = dPower_HVCC[SiteID] + dPower_LVCC[SiteID] + dPower_VDD08[SiteID]; //W
			hout(DETAIL) << "dPower_HVCC[" << SiteID << "] = "
					<< dPower_HVCC[SiteID] << endl;
			hout(DETAIL) << "dPower_LVCC[" << SiteID << "] = "
					<< dPower_LVCC[SiteID] << endl;

//			if (strTestsuiteName == "H30_MIN_PWR_VDDH") {
//				judgeAndLog_ParametricTest( SiteID, "MIN_POWER_Totol", "PWR", 0,dPower_Total[SiteID], 0.5,m_TestNumber + tempTestNumber); tempTestNumber++;
//
//				judgeAndLog_ParametricTest( SiteID, "MIN_POWER_HVCC", "PWR", 0,dPower_HVCC[SiteID], 0.5,m_TestNumber + tempTestNumber); tempTestNumber++;
//
//				judgeAndLog_ParametricTest( SiteID, "MIN_POWER_LVCC", "PWR", 0,dPower_LVCC[SiteID], 0.5,m_TestNumber + tempTestNumber); tempTestNumber++;
//
//				judgeAndLog_ParametricTest( SiteID, "MIN_POWER_VDD08", "PWR", 0,dPower_VDD08[SiteID], 0.5,m_TestNumber + tempTestNumber); tempTestNumber++;

//			} else if (strTestsuiteName == "H30_MAX_PWR_VDDH") {
				judgeAndLog_ParametricTest( SiteID, "MAX_POWER_Total", "PWR", 0,dPower_Total[SiteID], 10,m_TestNumber + tempTestNumber); tempTestNumber++;

				judgeAndLog_ParametricTest( SiteID, "MAX_POWER_HVCC", "PWR", 0,dPower_HVCC[SiteID], 10,m_TestNumber + tempTestNumber); tempTestNumber++;

				judgeAndLog_ParametricTest( SiteID, "MAX_POWER_LVCC", "PWR", 0,dPower_LVCC[SiteID], 10, m_TestNumber + tempTestNumber); tempTestNumber++;

				judgeAndLog_ParametricTest( SiteID, "MAX_POWER_VDD08", "PWR", 0,dPower_VDD08[SiteID], 10, m_TestNumber + tempTestNumber); tempTestNumber++;

//			}
			FOREACH_ACTIVESITE_END
			m_TestNumber = m_TestNumber + tempTestNumber;


		SetTestBin();
	}

};

REGISTER_TESTCLASS("MAX_PWR",MAX_PWR)


