//for test method API interfaces

#include <HILINK_ABIST/FWABIST_AdcStability.h>

#include <Common_Func/HiLink30_Common_Func.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TM Purpose:                                                                                                                //
//                                                                                                                            //
//                                    The following code are all sub functions                                                //
//																		                                                  	  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getSSMacro(MACRO_LANE_SEL& MacroLane_Sel, map<UINT, bool>& mSSMacroID,
		STRING &sSSMacroList)
{
	//map<UINT, bool> mSSMacroID;
	//STRING sSSMacroList = "";
	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++)
	{
		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
		UINT SSMacroID = HILINK_INFO[MacroID].SS_MacroID; //map_MacroID_SSMacroID[MacroID];
		if (mSSMacroID.find(SSMacroID) == mSSMacroID.end())
		{
			mSSMacroID[SSMacroID] = true;
			ostringstream tmp;
			tmp << SSMacroID << flush;
			if (sSSMacroList != "")
				sSSMacroList += ",";

			sSSMacroList += tmp.str();
			hout(DETAIL) << "+++++++++++++++SSMacroList:" << sSSMacroList
					<< endl;
		}
	}
}

class FWABIST_AdcStability: public TestClass
{
public:
	STRING				mHiLink30_MacroList;
	STRING				mPinList;
	DOUBLE				dRefCLK_MHz;
	DOUBLE				dRefCLK2_MHz;
	INT					iPrintLvl;
	STRING              sJudgementType;

	void init()
	{
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					.set_comment("HiLink30 Macro List for test")
					//.setOptions("0,1:0:1:FromPinList")
					.set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
		add_param("JudgementType","string",&sJudgementType)
					//.setOptions("UseExternalSpec_FW_Judge:BothMethod")
					.set_default("UseExternalSpec_FW_Judge");
		add_param("RefCLK_MHz","double",&dRefCLK_MHz)
					.set_comment("RefCLK_MHz")
					//.setOptions("100:156.25")
					.set_default("156.25");
		add_param("RefCLK2_MHz","double",&dRefCLK2_MHz)
					.set_comment("RefCLK2_MHz")
					//.setOptions("100:156.25")
					.set_default("156.25");
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
		static INT iOffline;
		static INT iCSR_check;
		static MACRO_LANE_SEL MacroLane_Sel;
		static MACRO_LANE_SEL vProcessMacroSS;
		static MACRO_DOUBLE AdcStability_Result;

		static MACRO_ARRAY_D SS_REG_RESULT;
		static MACRO_ARRAY_D CS_REG_RESULT;
		static LANE_ARRAY_D DS_REG_RESULT;

		static MACRO_ARRAY_MAP SS_REG_Node_Value;
		static MACRO_ARRAY_MAP CS_REG_Node_Value;
		static LANE_ARRAY_MAP DS_REG_Node_Value;

		static MACRO_ARRAY_D SS_Calculate_Output;
		static MACRO_ARRAY_D CS_Calculate_Output;
		static LANE_ARRAY_D DS_Calculate_Output;

		static LANE_DOUBLE DS_ErrorMessage;
		static MACRO_DOUBLE CS_ErrorMessage;

		static bool PreJudge_Result;

		int iLifeclk2dig_sel_pin_api;

		//=============================================
		// Variables and MacroLane initialization
		//=============================================
		INT iDebugAnalog;

		stFWABIST_AdcStability sFWABIST_AdcStability =
				H30_ADCstability_FWABIST_AdcStability;
//		static STRING mPinList = "";
//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;

//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);

//                stFWABIST_AdcStability H30_ADCstability_FWABIST_AdcStability
		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel,mHiLink30_MacroList, mPinList);


		AdcStability_TABLE_DEFINE& FWABIST_AdcStability =
				AdcStability_TABLE_DEFINE::getInstance();

//		ON_FIRST_INVOCATION_BEGIN();

		UINT iRefclk0_freqm100 = uint(dRefCLK_MHz * 100);
		UINT iRefclk1_freqm100 = uint(dRefCLK2_MHz * 100);

//		D2S_FRAMEWORK;
//		GET_TEST_INFO;
		map<UINT, bool> mSSMacroID;
		//get the ss marco
		STRING sSSMacroList = SSMacroIDList;
//		getSSMacro(MacroLane_Sel,mSSMacroID,sSSMacroList);
		Select_Macro_Lane(vProcessMacroSS, sSSMacroList);

		/**************Clear API and CSConfigBeforeCal***set proper API depending on applications and Release MCU*********/

		//Step1: Ctle Pre Setting, set before this test suite
		//Step3: LoadFirmware to Sram
		LoadFirmwareToSram(MacroLane_Sel, AdcStability_Bin,AdcStability_Cycles);


		//Step4: FW judge, write spec value fist
		if ((sJudgementType == "UseExternalSpec_FW_Judge")
				|| (sJudgementType == "BothMethod"))
		{
			WritePerMacroSpecToSram(MacroLane_Sel, FWABIST_AdcStability);
			WritePerLaneSpecToSram(MacroLane_Sel, FWABIST_AdcStability);
		}

		//READ_ALL_CSR;

		//Step5/6/7/8/9/10: Config AdcStability test API.
//		sprintf(label,"H30V101LR_Config_FWABIST_testAPI_%s_%f_%f_",TestSuiteName.c_str(),Vcoef,Temp);
//			fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN( "H30V101LR_Config_FWABIST_testAPI_",Global_D2S_Mode);


		selectMacro_MB(MacroLane_Sel);
		//Config refclk and core clk same as
		//		Config_RefClk_CoreClk(iRefclk0_freqm100, iRefclk1_freqm100);

		SRAM.CSAPIRegs.setrefclk0_freqm100_api(iRefclk0_freqm100).Write2DUT(1);
		SRAM.CSAPIRegs.setrefclk1_freqm100_api(iRefclk1_freqm100).Write2DUT(2);
		//Configure core_clk select
		SRAM.CSAPIRegs.setcore_clk_selext_pin_api(giCore_clk_selext_pin_api).Write2DUT(
				0);
		SRAM.CSAPIRegs.setcore_clk_sel_pin_api(giCore_clk_sel_pin_api).Write2DUT(
				0);
		SRAM.CSAPIRegs.setcoreclk_sel_en_api(0x1).Write2DUT(4);
		//Config refclk and core clk same as
//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();
//		sprintf(label,"H30V101LR_Config_FWABIST_testAPI2_%s_%f_%f_",TestSuiteName.c_str(),Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN("H30V101LR_Config_FWABIST_testAPI2_",Global_D2S_Mode);

		for (size_t macroIndex = 0; macroIndex < MacroLane_Sel.size();
				macroIndex++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			selectMacro(MacroID);

			if (GlobalInitPattern.find("_Case01") != string::npos)
				iLifeclk2dig_sel_pin_api =
						HILINK_INFO[MacroID].life2digChoose[0];
			else if (GlobalInitPattern.find("_Case02") != string::npos)
				iLifeclk2dig_sel_pin_api =
						HILINK_INFO[MacroID].life2digChoose[1];
			else if (GlobalInitPattern.find("_Case03") != string::npos)
				iLifeclk2dig_sel_pin_api =
						HILINK_INFO[MacroID].life2digChoose[2];
			else
			{
//					cout << "Can't find valid init pattern !!! Please check pattern name!" << endl;
//				api->info_message("Can't find valid init pattern !!! Please check pattern name!");
				cout <<"Can't find valid init pattern !!! Please check pattern name!"<<endl;
//					ERROR_EXIT(TM::ABORT_FLOW);
			}
			if (iLifeclk2dig_sel_pin_api != 1 && iLifeclk2dig_sel_pin_api != 0
					&& iLifeclk2dig_sel_pin_api != -1)
			{
//					cout << "Invalid macro has been choose !!! Please check macro ID!" << endl;
//				api->info_message("Invalid macro has been choose !!! Please check macro ID!");
				cout <<"Invalid macro has been choose !!! Please check macro ID!"<<endl;
//					ERROR_EXIT(TM::ABORT_FLOW);
			}

			SRAM.CSAPIRegs.setlifeclk2dig_sel_pin_api(iLifeclk2dig_sel_pin_api).Write2DUT(
					0, false);
		}

		selectMacro_MB(MacroLane_Sel);
		//Config FWAbist test API
		SRAM.ABISTAPIRegs.setadc_stability_ss_adc_bypass_api(0x0).Write2DUT(2);
		SRAM.ABISTAPIRegs.setadc_stability_cs_adc_bypass_api(0x0).Write2DUT(2);
		SRAM.ABISTAPIRegs.setadc_stability_ds_adc_bypass_api(0x0).Write2DUT(2);
		SRAM.ABISTAPIRegs.setadc_stability_adc_loop_cnt_api(0x2).Write2DUT(2);
		SRAM.ABISTAPIRegs.setadc_stability_ref_vol_mode_api(0x2).Write2DUT(2);
		SRAM.ABISTAPIRegs.setadc_stability_abist_api(0x1).Write2DUT(1);
		SRAM.ABISTAPIRegs.settest_mode_abist_api(0x1).Write2DUT(2);

//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();

		//Step11: Release MCU
		ReleaseMCU(MacroLane_Sel);

		//Step12: Wait TOP_FSM_DONE_API =1
		EXPECT_RESULT Top_Fsm_Result;
		WaitDoneMacro(MacroLane_Sel, SRAM.TOPAPIRegs.REG_INFO.top_fsm_done_api(), 1, 200, 4, Top_Fsm_Result);

		TheInst.Wait(0.005);// learning mode , d2s pattern run one by one , just get the M1 result , do not know M0 result .
		//After MCU Done, read all regs
		//READ_ALL_CSR;

		// Step13: hold MCU in reset mode
		ResetMCU(MacroLane_Sel);

		//Step14:	Clear AdcStability test API. Simple-Mode set AdcStability_ABIST_API (ABISTAPI CSR0 Bit[3]) = 0 and TEST_MODE_ABIST_API (ABISTAPI CSR2[15:14]) = 0.
//		sprintf(label,"H30V101LR_Clear_FWABIST_testAPI_%s_%f_%f_",TestSuiteName.c_str(),Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN("H30V101LR_Clear_FWABIST_testAPI_",
				Global_D2S_Mode);
		selectMacro_MB(MacroLane_Sel);
		SRAM.ABISTAPIRegs.setadc_stability_abist_api(0x0).Write2DUT(1);
		SRAM.ABISTAPIRegs.setadc_stability_adc_loop_cnt_api(0x0).Write2DUT(2);
		SRAM.ABISTAPIRegs.setadc_stability_ref_vol_mode_api(0x0).Write2DUT(2);
		SRAM.ABISTAPIRegs.settest_mode_abist_api(0x0).Write2DUT(2);
//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();

		SEGMENT_READ_MACRO(MacroLane_Sel,
				SRAM.ABISTAPIRegs.REG_INFO.adc_stability_status_abist_api(),
				AdcStability_Result);

		ALL_CSR_ReadBack_TO_FILE_Debug(MacroLane_Sel,"adc_stability_status_abist_api");
		//The following code are for detail result dataloging
		FWAbist_PreJudge(MacroLane_Sel, AdcStability_Result, PreJudge_Result);

		FW_ABIST_READ_ErrorMessage(MacroLane_Sel, 0x1FCFA, 0x1, 0x1FD02,
				CS_ErrorMessage, DS_ErrorMessage);

		//Step15: Read SRAM Results
		if ((PreJudge_Result == false)
				|| (sJudgementType == "BothMethod")
				|| (Global_D2S_Mode == 0))
		{

			//Read back table 2-10 in AdcStability userguide //todo
			FWABIST_AdcStability.FWABIST_Registers_Map_Init(MacroLane_Sel,
					SS_REG_RESULT, SS_REG_Node_Value, CS_REG_RESULT,
					CS_REG_Node_Value, DS_REG_RESULT, DS_REG_Node_Value);

			//Process table 2-11 in AdcStability user guide
			FWAbist_Calculate_Table_Processing(MacroLane_Sel,
					FWABIST_AdcStability, SS_Calculate_Output,
					CS_Calculate_Output, DS_Calculate_Output, SS_REG_Node_Value,
					CS_REG_Node_Value, DS_REG_Node_Value);

			//Readback Sram result for EVB Corrlation purpose Table 2-4

//				for(uint macroIndex=0; macroIndex < MacroLane_Sel.size();macroIndex++)
//				{
//					ostringstream  TestDatalogBegin, TestDatalogEnd;
//					TestDatalogBegin<<"\n"<<"==========H30V101LR_AdcStability_FWTest_Start==========";
////					PUT_DATALOG(TestDatalogBegin.str());
//
//					    ostringstream  TestDatalog;
//						FWAbistHeader(MacroLane_Sel, macroIndex, HILINK_FIRMWARE_LABEL_DEFAULT, AdcStability_Bin, "AdcStability_LR", TestDatalog);
//
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1F370, 0x1F3A1, TestDatalog);//SS hvcc test results
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1F3D4, 0x1F405, TestDatalog);//SS bandgap test results
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1F438, 0x1F469, TestDatalog);//CS hvcc test results
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1F488, 0x1F4B9, TestDatalog);//CS bandgap test results
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1F4D8, 0x1F4FF, TestDatalog);//DS0 hvcc test results
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1F55A, 0x1F59F, TestDatalog);//DS0 bandgap test results
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1F5DC, 0x1F603, TestDatalog);//DS1 hvcc test results
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1F65E, 0x1F6A3, TestDatalog);//DS1 bandgap test results
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1F6E0, 0x1F707, TestDatalog);//DS2 hvcc test results
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1F762, 0x1F7A7, TestDatalog);//DS2 bandgap test results
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1F7E4, 0x1F80B, TestDatalog);//DS3 hvcc test results
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1F866, 0x1F8AB, TestDatalog);//DS3 bandgap test results
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1F8E8, 0x1F90F, TestDatalog);//DS4 hvcc test results
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1F96A, 0x1F9AF, TestDatalog);//DS4 bandgap test results
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1F9EC, 0x1FA13, TestDatalog);//DS5 hvcc test results
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FA6E, 0x1FAB3, TestDatalog);//DS5 bandgap test results
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FAF0, 0x1FB17, TestDatalog);//DS6 hvcc test results
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FB72, 0x1FBB7, TestDatalog);//DS6 bandgap test results
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FBF4, 0x1FC1B, TestDatalog);//DS7 hvcc test results
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FC76, 0x1FCBB, TestDatalog);//DS7 bandgap test results
//
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FCF8, 0x1FD15, TestDatalog); //Test Reuslt
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FDB6, 0x1FDC1, TestDatalog); //AdcStability ABIST API
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FEDE, 0x1FEE1, TestDatalog); //DS7 API state
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FF02, 0x1FF05, TestDatalog); //DS6 API state
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FF26, 0x1FF29, TestDatalog); //DS5 API state
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FF4A, 0x1FF4D, TestDatalog); //DS4 API state
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FF6E, 0x1FF71, TestDatalog); //DS3 API state
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FF92, 0x1FF95, TestDatalog); //DS2 API state
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FFB6, 0x1FFB9, TestDatalog); //DS1 API state
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FFDA, 0x1FFDD, TestDatalog); //DS0 API state
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FFFE, 0x1FFFF, TestDatalog); //TOP API state
//						PrinfToEdf_FWAbist(TestDatalog);
//
//					TestDatalogEnd<<"\n"<<"==========H30V101LR_AdcStability_LR_FWTest_End=========="<<endl;
////					PUT_DATALOG(TestDatalogEnd.str());
//				}
		}

		//Debug info to compare with EVB limit setting
//        if(sJudgementType == "BothMethod")
//        {
//    		ostringstream SramDataLog;
//
//    		for(UINT MacroIndex= 0; MacroIndex<MacroLane_Sel.size(); MacroIndex++)
//    		{
//        		UINT MacroID = MacroLane_Sel[MacroIndex].MacroID;
//        		//Read back table 2-10,2-11(LR) in AdcStability userguide
//        		SRAM_READ(MacroID, 0x1F180, 0x1F36C, SramDataLog, true);
//    		}
//
//        }
//		ON_FIRST_INVOCATION_END();
		//=============================================
		// Datalog
		//=============================================
		//Judge global pass/fail
		double limitl_conclusion = 1;
		double limith_conclusion = 1;
		double limitl_err_message = 0;
		double limith_err_message = 0;
		HiLink_PerMacro_Judge(MacroLane_Sel, "AdcStability_Test_Conclusion",
				limitl_conclusion, AdcStability_Result, limith_conclusion);
		HiLink_PerMacro_Judge(MacroLane_Sel, "CS_ErrorMessage",
				limitl_err_message, CS_ErrorMessage, limith_err_message);
		HiLink_PerLane_Judge(MacroLane_Sel, "DS_ErrorMessage",
				limitl_err_message, DS_ErrorMessage, limith_err_message);

		if ((sJudgementType == "BothMethod")
				|| (PreJudge_Result == false))
		{

			//Judge table 2-10 according to AdcStability user guide
			HiLink_PerMacroSSArrayD_Judge(vProcessMacroSS, FWABIST_AdcStability,
					SS_REG_RESULT);
			HiLink_PerMacroCSArrayD_Judge(MacroLane_Sel, FWABIST_AdcStability,
					CS_REG_RESULT);
			HiLink_PerLaneArrayD_Judge(MacroLane_Sel, FWABIST_AdcStability,
					DS_REG_RESULT);

			//Judge table 2-11 according to AdcStability user guide
			HiLink_PerMacroSSCalArrayD_Judge(vProcessMacroSS,
					FWABIST_AdcStability, SS_Calculate_Output);
			HiLink_PerMacroCSCalArrayD_Judge(MacroLane_Sel,
					FWABIST_AdcStability, CS_Calculate_Output);
			HiLink_PerLaneCalArrayD_Judge(MacroLane_Sel, FWABIST_AdcStability,
					DS_Calculate_Output);

		}

//                SetTestBin(api);
	}
};
REGISTER_TESTCLASS("FWABIST_AdcStability", FWABIST_AdcStability)

