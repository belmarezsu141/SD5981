//for test method API interfaces

#include <Common_Func/HiLink30_Common_Func.h>
//#include "FWABIST_AdcStability.h"

using namespace std;

class FWABIST_DLOS: public TestClass
{
public:
	STRING 				mHiLink30_MacroList;
	STRING 				mPinList;
	DOUBLE              dRefCLK_MHz;
	DOUBLE              dRefCLK2_MHz;
	INT					iPrintLvl;
	STRING              sJudgementType;
	void init()
	{
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					.set_comment("HiLink30 Macro List for test")
					//.set_options("0,1:0:1:FromPinList")
					.set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
		add_param("JudgementType","string",&sJudgementType)
					//.set_options("UseExternalSpec_FW_Judge:BothMethod")
					.set_default("UseExternalSpec_FW_Judge");
		add_param("RefCLK_MHz","double",&dRefCLK_MHz)
					.set_comment("RefCLK_MHz")
					//.set_options("100:156.25")
					.set_default("156.25");
		add_param("RefCLK2_MHz","double",&dRefCLK2_MHz)
					.set_comment("RefCLK2_MHz")
					//.set_options("100:156.25")
					.set_default("156.25");
		add_param("PrintLvl[0~8]","int",&iPrintLvl)
					.set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
					"0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					//.set_options("0:1:3:4:7:8")
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
		static MACRO_DOUBLE DLOS_Result;
		static LANE_DOUBLE DS_ErrorMessage;
		static MACRO_DOUBLE CS_ErrorMessage;
		static LANE_DOUBLE DS_Dlos_status;

		static bool PreJudge_Result;

		int iLifeclk2dig_sel_pin_api;

		//=============================================
		// Variables and MacroLane initialization
		//=============================================
		INT iDebugAnalog;

//		GET_SYSTEM_FLAG		("offline",&iOffline);
//		GET_TESTSUITE_NAME	(sTestsuiteName);
//		GET_USER_FLAG		("CSR_atomic_operation",&iCSR_check);
//		GET_TESTFLOW_FLAG	("debug_analog",&iDebugAnalog);
		stFWABIST_DLOS sFWABIST_DLOS = H30_DLOS_FWABIST_DLOS;
//		static STRING mPinList = "";
//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);

//         stFWABIST_DLOS H30_DLOS_FWABIST_DLOS       
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList,mPinList);


//		ON_FIRST_INVOCATION_BEGIN();

		uint iRefclk0_freqm100 = uint(dRefCLK_MHz * 100);
		uint iRefclk1_freqm100 = uint(dRefCLK2_MHz * 100);

//		D2S_FRAMEWORK;
//		GET_TEST_INFO;
		/**************Clear API and CSConfigBeforeCal***set proper API depending on applications and Release MCU*********/

		//Step1 and Step2: PowerUp and Reset && Config Ctle and do calibration, this step has been done before this test suite
		//Step3: Load Abist test firmware: H30V101_ABIST_Dlos_SRAM.bin
		LoadFirmwareToSram(MacroLane_Sel, DLOS_Bin, DLOS_Cycles);

		//Step4: If let FW do the judgement, Set the spec //fw fix spec
		if ((sJudgementType == "UseExternalSpec_FW_Judge")
				|| (sJudgementType == "BothMethod"))
		{
			//WriteSingleSpecToSram(MacroLane_Sel,0x1F860, 20.5, 0x1F862, 1.2, 1000); //the DLOS FW DC Test not support limit external
		}

		//Step4: Config DLOS test API.
//		sprintf(label,"H30V101LR_Config_DLOS_testAPI_%s_%f_%f_",TestSuiteName.c_str(),Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN( "H30V101LR_Config_DLOS_testAPI_",
				Global_D2S_Mode);
		selectMacro_MB(MacroLane_Sel);
		//Config refclk and core clk same as
		//		Config_RefClk_CoreClk(iRefclk0_freqm100, iRefclk1_freqm100);

		SRAM.CSAPIRegs.setrefclk0_freqm100_api(iRefclk0_freqm100).Write2DUT(1);
		SRAM.CSAPIRegs.setrefclk1_freqm100_api(iRefclk1_freqm100).Write2DUT(2);
		//Configure core_clk select
		SRAM.CSAPIRegs.setcore_clk_selext_pin_api(giCore_clk_selext_pin_api).Write2DUT(0);	//CSR Broadcast Bug

		SRAM.CSAPIRegs.setcore_clk_sel_pin_api(giCore_clk_sel_pin_api).Write2DUT(0);

		SRAM.CSAPIRegs.setcoreclk_sel_en_api(0x1).Write2DUT(4);
//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();

//		sprintf(label,"H30V101LR_Config2_DLOS_testAPI_%s_%f_%f_",TestSuiteName.c_str(),Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));

		d2s::d2s_LABEL_BEGIN("H30V101LR_Config2_DLOS_testAPI_",	Global_D2S_Mode);

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
		SRAM.ABISTAPIRegs.setdlos_abist_api(0x1).Write2DUT(1);
		DS.rxRegs.SliceID(0).Broadcast(1); //set ctle as predriver
		//	if(sLoopBackMode == "PreDriver"){
		DS.rxRegs.setctleactgn1(7).Write2DUT(1);
		DS.rxRegs.setctleactgn2(7).Write2DUT(2);
		DS.rxRegs.setctleactgn3(7).Write2DUT(3);
//		DS.rxRegs.setctleboostc1(7).Write2DUT(1);
//		DS.rxRegs.setctleboostc2(7).Write2DUT(2);
//		DS.rxRegs.setctleboostc3(0).Write2DUT(3);
		DS.rxRegs.setctleboostc1(0).Write2DUT(1);
		DS.rxRegs.setctleboostc2(0).Write2DUT(2);
		DS.rxRegs.setctleboostc3(0).Write2DUT(3);
		DS.rxRegs.setctleza1(0).Write2DUT(1);
		DS.rxRegs.setctleza2(0).Write2DUT(2);
		DS.rxRegs.setctleza3(0).Write2DUT(3);
//		DS.rxRegs.setctlesqh1(1).Write2DUT(1);
//		DS.rxRegs.setctlesqh2(1).Write2DUT(2);
//		DS.rxRegs.setctlesqh3(1).Write2DUT(3);
		DS.rxRegs.setctlesqh1(2).Write2DUT(1);
		DS.rxRegs.setctlesqh2(2).Write2DUT(2);
		DS.rxRegs.setctlesqh3(2).Write2DUT(3);
		DS.rxRegs.setctlermband1(2).Write2DUT(1);
		DS.rxRegs.setctlermband2(1).Write2DUT(2);
		DS.rxRegs.setctlermband3(1).Write2DUT(3);
		DS.rxRegs.setctlecmband1(2).Write2DUT(1);
		DS.rxRegs.setctlecmband2(1).Write2DUT(2);
		DS.rxRegs.setctlecmband3(1).Write2DUT(3);
		DS.rxRegs.setctlehfzen1(0).Write2DUT(1);
		DS.rxRegs.setctlehfzen2(0).Write2DUT(2);
		DS.rxRegs.setctlehfzen3(0).Write2DUT(3);
		//}

//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();
		//Step5: Release MCU
		ReleaseMCU(MacroLane_Sel);

		//Step6: Wait TOP_FSM_DONE_API
		EXPECT_RESULT Top_Fsm_Result;
		WaitDoneMacro(MacroLane_Sel, SRAM.TOPAPIRegs.REG_INFO.top_fsm_done_api(), 1, 100, 1, Top_Fsm_Result);

		//After MCU Done, read all regs
		//READ_ALL_CSR;

		// Step7: hold MCU in reset mode
		ResetMCU(MacroLane_Sel);

		//Step9:Clear ATB test API

		d2s::d2s_LABEL_BEGIN("H30V101LR_Clear_DLOS_testAPI_",Global_D2S_Mode);

//        sprintf(label,"H30V101LR_Clear_DLOS_testAPI_%s_%f_%f_",TestSuiteName.c_str(),Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		selectMacro_MB(MacroLane_Sel);
		SRAM.ABISTAPIRegs.setdlos_abist_api(0x0).Write2DUT(1);
		SRAM.ABISTAPIRegs.settest_mode_abist_api(0x0).Write2DUT(2);
//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();
		//Step10: Read SRAM results
		SEGMENT_READ_MACRO(MacroLane_Sel,
				SRAM.ABISTAPIRegs.REG_INFO.dlos_status_abist_api(),
				DLOS_Result);
		//The following code are for detail result dataloging
		FWAbist_PreJudge(MacroLane_Sel, DLOS_Result, PreJudge_Result);

		FW_ABIST_READ_ErrorMessage(MacroLane_Sel, 0x1FCFA, 0x1, 0x1FD02,
				CS_ErrorMessage, DS_ErrorMessage);

		//Step10: Read SRAM Results
		if ((PreJudge_Result == false)
				|| (sJudgementType == "BothMethod")
				|| (Global_D2S_Mode == 0))
		{

			FW_ABIST_READ_LANEDOUBLE(MacroLane_Sel, 0x1FCE8, 2, DS_Dlos_status);

//			for(uint macroIndex=0; macroIndex < MacroLane_Sel.size();macroIndex++)
//			{
//				//Readback Sram result for EVB Corrlation purpose
//				ostringstream  TestDatalogBegin, TestDatalogEnd;
//				TestDatalogBegin<<"\n"<<"==========H30V101LR_DLOS_FWTest_Start==========";
////				PUT_DATALOG(TestDatalogBegin.str());
//
//				ostringstream  TestDatalog;
//				FWAbistHeader(MacroLane_Sel, macroIndex, HILINK_FIRMWARE_LABEL_DEFAULT, DLOS_Bin, "DLOS_LR", TestDatalog);
//
//				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FCE8, 0x1FCF7, TestDatalog); //DS Results
//				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FCF8, 0x1FD15, TestDatalog); //Results State and Common Information
//				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FDB6, 0x1FDC1, TestDatalog); //ABIST API
//				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FEDE, 0x1FEE1, TestDatalog); //DS7 API state
//				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FF02, 0x1FF05, TestDatalog); //DS6 API state
//				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FF26, 0x1FF29, TestDatalog); //DS5 API state
//				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FF4A, 0x1FF4D, TestDatalog); //DS4 API state
//				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FF6E, 0x1FF71, TestDatalog); //DS3 API state
//				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FF92, 0x1FF95, TestDatalog); //DS2 API state
//				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FFB6, 0x1FFB9, TestDatalog); //DS1 API state
//				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FFDA, 0x1FFDD, TestDatalog); //DS0 API state
//				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FFFE, 0x1FFFF, TestDatalog); //TOP API state
//
//				PrinfToEdf_FWAbist(TestDatalog);
//
//				TestDatalogEnd<<"\n"<<"==========H30V101LR_DLOS_FWTest_End=========="<<endl;
////				PUT_DATALOG(TestDatalogEnd.str());
//			}

		}

//       if(sJudgementType == "BothMethod")
//        {
//    		//debug info to compare with EVB output
//    		ostringstream SramDataLog;
//    		for(UINT MacroIndex= 0; MacroIndex<MacroLane_Sel.size(); MacroIndex++)
//    		{
//        		UINT MacroID = MacroLane_Sel[MacroIndex].MacroID;
//    		 //  SRAM_READ(MacroID, 0x1F860, 0x1F864,SramDataLog, true);
//    		}
//        }

//		ON_FIRST_INVOCATION_END();
		//=============================================
		// Datalog
		//=============================================
		double limitl_conclusion = 1;
		double limith_conclusion = 1;
		double limitl_err_message = 0;
		double limith_err_message = 0;
		HiLink_PerMacro_Judge(MacroLane_Sel, "DLOS_Test_Conclusion",
				limitl_conclusion, DLOS_Result, limith_conclusion);
		HiLink_PerMacro_Judge(MacroLane_Sel, "CS_ErrorMessage",
				limitl_err_message, CS_ErrorMessage, limith_err_message);
		HiLink_PerLane_Judge(MacroLane_Sel, "DS_ErrorMessage",
				limitl_err_message, DS_ErrorMessage, limith_err_message);
		if ((sJudgementType == "BothMethod")
				|| (PreJudge_Result == false))
		{
			double limitl_ds_dlos_status = 10921;
			double limith_ds_dlos_status = 10921;
			HiLink_PerLane_Judge(MacroLane_Sel, "DS_Dlos_status",
					limitl_ds_dlos_status, DS_Dlos_status,
					limith_ds_dlos_status);
		}

//                SetTestBin(api);
	}
};
REGISTER_TESTCLASS("FWABIST_DLOS", FWABIST_DLOS)

