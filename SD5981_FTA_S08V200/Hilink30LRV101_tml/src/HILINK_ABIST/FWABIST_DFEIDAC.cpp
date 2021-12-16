//for test method API interfaces

#include <HILINK_ABIST/FWABIST_DFEIDAC.h>

#include <Common_Func/HiLink30_Common_Func.h>

//using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TM Purpose:                                                                                                                //
//                                                                                                                            //
//                                    The following code are all sub functions                                                //
//																		                                                  	  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void WriteCalculatePerLaneSpecToSram(const MACRO_LANE_SEL& MacroLane_Sel,
		FWABIST_REGISTER_Base& FWABIST_REG_BASE)
{
//		D2S_FRAMEWORK;
//		GET_TEST_INFO;
	d2s_JTAG& jtag = d2s_JTAG::Instance();
//		sprintf(label,"WritePerlaneSpecToSram_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
	d2s::d2s_LABEL_BEGIN( "WritePerlaneSpecToSram_",Global_D2S_Mode);

	selectMacro_MB(MacroLane_Sel);

	//All lane write same spec to same address, so here NO need to write lane loop
	for (uint RegIndex = 0;
			RegIndex < FWABIST_REG_BASE.get_DS_FWABIST_Calculate_REG_count();
			RegIndex++)
	{

		uint temp_SpecHigh_Address = FWABIST_REG_BASE.get_DS_Calculate_REG(
				RegIndex).SpecHigh_Address;
		uint temp_SpecHigh_Value =
				FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).SpecHigh_Value
						* FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Spec_Wrttern_Rate;
		temp_SpecHigh_Value = (((INT) temp_SpecHigh_Value & 0xff00) >> 8)
				| (((INT) temp_SpecHigh_Value & 0x00ff) << 8); //big edian

		uint temp_SpecLow_Address = FWABIST_REG_BASE.get_DS_Calculate_REG(
				RegIndex).SpecLow_Address;
		uint temp_SpecLow_Value =
				FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).SpecLow_Value
						* FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Spec_Wrttern_Rate;
		temp_SpecLow_Value = (((INT) temp_SpecLow_Value & 0xff00) >> 8)
				| (((INT) temp_SpecLow_Value & 0x00ff) << 8); //big edian

		jtag.write(temp_SpecHigh_Address >> 1, temp_SpecHigh_Value);
		jtag.write(temp_SpecLow_Address >> 1, temp_SpecLow_Value);

		hout(DETAIL) << "Write DS Calculate SpecHigh: " << hex << "0x "
				<< temp_SpecHigh_Address << " Value: " << dec
				<< temp_SpecHigh_Value << endl;
		hout(DETAIL) << "Write DS Calculate SpecLow: " << hex << "0x "
				<< temp_SpecLow_Address << " Value: " << dec
				<< temp_SpecLow_Value << endl;

	}

	d2s::d2s_LABEL_END();

}

class FWABIST_DFEIDAC: public TestClass
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
		add_param("JudgementType","string",&sJudgementType)
					//.set_options("UseExternalSpec_FW_Judge:BothMethod")
					.set_default("UseExternalSpec_FW_Judge");
		add_param("RefCLK_MHz","double",&dRefCLK_MHz)
					.set_comment("RefCLK_MHz")
					//.set_options("100:156.25")
					.set_default("156.25");
		add_param("RefCLK2_MHz","double",&dRefCLK2_MHz)
					.set_comment("RefCL2_MHz")
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
		static MACRO_DOUBLE DfeIdac_Result;

		static MACRO_ARRAY_D SS_REG_RESULT;
		static MACRO_ARRAY_D CS_REG_RESULT;
		static LANE_ARRAY_D DS_REG_RESULT;

		static MACRO_ARRAY_MAP SS_REG_Node_Value;
		static MACRO_ARRAY_MAP CS_REG_Node_Value;
		static LANE_ARRAY_MAP DS_REG_Node_Value;

		static LANE_ARRAY_D PerLane_Input1;
		static LANE_ARRAY_D PerLane_Input2;
		static MACRO_ARRAY_D PerMacro_Input1;
		static MACRO_ARRAY_D PerMacro_Input2;
		static MACRO_ARRAY_D SS_Calculate_Output;
		static MACRO_ARRAY_D CS_Calculate_Output;
		static LANE_ARRAY_D DS_Calculate_Output;

		static LANE_DOUBLE Half_HVCC_Part1;
		static LANE_DOUBLE Half_HVCC_Public;
		static LANE_DOUBLE DS_ErrorMessage;
		static MACRO_DOUBLE CS_ErrorMessage;
		static MACRO_DOUBLE Quarter_CS_HVCC_Part1;
		static MACRO_DOUBLE Quarter_CS_HVCC_Public;

		static bool PreJudge_Result;

		int iLifeclk2dig_sel_pin_api;
		//=============================================
		// Variables and MacroLane initialization
		//=============================================
		INT iDebugAnalog;

		stFWABIST_DFEIDAC sFWABIST_DFEIDAC = H30_DFEIDAC_VDDL_FWABIST_DFEIDAC;
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
		Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList,mPinList);

		DFEIDAC_TABLE_DEFINE& FWABIST_DFEIDAC =
				DFEIDAC_TABLE_DEFINE::getInstance();

//		ON_FIRST_INVOCATION_BEGIN();

		uint iRefclk0_freqm100 = uint(dRefCLK_MHz * 100);
		uint iRefclk1_freqm100 = uint(dRefCLK2_MHz * 100);

//		D2S_FRAMEWORK;
//		GET_TEST_INFO;
		/**************Clear API and CSConfigBeforeCal***set proper API depending on applications and Release MCU*********/
		//Step1 Step2 and Step3: PowerUp and Reset && Config Ctle and do calibration, this step has been done before this test suite
		//Step4: Load Abist test firmware: H30V101_ABIST_DfeIdac.bin
		LoadFirmwareToSram(MacroLane_Sel, DfeIdac_Bin, DfeIdac_Cycles);

		//Step 4: Set Spec
		if ((sJudgementType == "UseExternalSpec_FW_Judge")
				|| (sJudgementType == "BothMethod"))
		{
			WriteCalculatePerLaneSpecToSram(MacroLane_Sel, FWABIST_DFEIDAC);
		}

		//Step5: Config DfeIdac test API.
		d2s::d2s_LABEL_BEGIN( "H30V101_Config_DfeIdac_testAPI_",Global_D2S_Mode);

//		sprintf(label,"H30V101_Config_DfeIdac_testAPI_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		selectMacro_MB(MacroLane_Sel);

		//		Config_RefClk_CoreClk(iRefclk0_freqm100, iRefclk1_freqm100);

		SRAM.CSAPIRegs.setrefclk0_freqm100_api(iRefclk0_freqm100).Write2DUT(1);
		SRAM.CSAPIRegs.setrefclk1_freqm100_api(iRefclk1_freqm100).Write2DUT(2);
		//Configure core_clk select
		SRAM.CSAPIRegs.setcore_clk_selext_pin_api(giCore_clk_selext_pin_api).Write2DUT(
				0);		//CSR Broadcast Bug
		SRAM.CSAPIRegs.setcore_clk_sel_pin_api(giCore_clk_sel_pin_api).Write2DUT(
				0);
		SRAM.CSAPIRegs.setcoreclk_sel_en_api(0x1).Write2DUT(4);

//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();
//		sprintf(label,"H30V101_Config2_DfeIdac_testAPI_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN("H30V101_Config2_DfeIdac_testAPI_",Global_D2S_Mode);

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
				cout <<"Can't find valid init pattern !!! Please check pattern name!C"<<endl;
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
		SRAM.ABISTAPIRegs.setdfe_idac_sweep_abist_api(0x1).Write2DUT(1);
		SRAM.ABISTAPIRegs.settest_mode_abist_api(0x1).Write2DUT(2);

		d2s::d2s_LABEL_END();
//		fr.d2s_LABEL_END();

		//Step6: Release MCU
		ReleaseMCU(MacroLane_Sel);

		//Step7: Wait TOP_FSM_DONE_API
		EXPECT_RESULT Top_Fsm_Result;
		WaitDoneMacro(MacroLane_Sel, SRAM.TOPAPIRegs.REG_INFO.top_fsm_done_api(), 1, 100, 2, Top_Fsm_Result);
		//After MCU Done, read all regs
		//READ_ALL_CSR;

		// Step8: hold MCU in reset mode
		ResetMCU(MacroLane_Sel);

		//Step9:Clear DfeIdac test API
		d2s::d2s_LABEL_BEGIN( "H30V101_Clear_ATB_testAPI_",
				Global_D2S_Mode);
//        sprintf(label,"H30V101_Clear_ATB_testAPI_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		selectMacro_MB(MacroLane_Sel);
		SRAM.ABISTAPIRegs.setdfe_idac_sweep_abist_api(0x0).Write2DUT(1);
		SRAM.ABISTAPIRegs.settest_mode_abist_api(0x0).Write2DUT(2);
//        fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();

		//Step10: Read SRAM Results
		SEGMENT_READ_MACRO(MacroLane_Sel,
				SRAM.ABISTAPIRegs.REG_INFO.dfe_idac_sweep_status_abist_api(),
				DfeIdac_Result);
		//The following code are for detail result dataloging
		FWAbist_PreJudge(MacroLane_Sel, DfeIdac_Result, PreJudge_Result);

		FW_ABIST_READ_ErrorMessage(MacroLane_Sel, 0x1FCFA, 0x1, 0x1FD02,
				CS_ErrorMessage, DS_ErrorMessage);
		if ((PreJudge_Result == false)
				|| (sJudgementType == "BothMethod")
				|| (Global_D2S_Mode == 0))
		{
			//Read back table 2-6 in userguide

			FW_ABIST_READ_HVCC(MacroLane_Sel, 0x1FD04, 0x2, 0x1FD14,
					Quarter_CS_HVCC_Public, Half_HVCC_Public);

			FWABIST_DFEIDAC.FWABIST_Registers_Map_Init(MacroLane_Sel,
					SS_REG_RESULT, SS_REG_Node_Value, CS_REG_RESULT,
					CS_REG_Node_Value, DS_REG_RESULT, DS_REG_Node_Value,
					Half_HVCC_Part1, Half_HVCC_Public, Quarter_CS_HVCC_Part1,
					Quarter_CS_HVCC_Public);
			FWAbist_Calculate_Table_Processing(MacroLane_Sel, FWABIST_DFEIDAC,
					SS_Calculate_Output, CS_Calculate_Output,
					DS_Calculate_Output, SS_REG_Node_Value, CS_REG_Node_Value,
					DS_REG_Node_Value);

//			for(uint macroIndex=0; macroIndex < MacroLane_Sel.size();macroIndex++)
//			{
//				//Readback Sram result for EVB Corrlation purpose
//				ostringstream  TestDatalogBegin, TestDatalogEnd;
//				TestDatalogBegin<<"\n"<<"==========H30V101_DfeIdac_FWTest_Start==========";
////				PUT_DATALOG(TestDatalogBegin.str());
//
//				ostringstream  TestDatalog;
//				FWAbistHeader(MacroLane_Sel, macroIndex, HILINK_FIRMWARE_LABEL_DEFAULT, DfeIdac_Bin, "DfeIdac", TestDatalog);
//
//				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1D5D8, 0x1D8D7, TestDatalog); //DS Results
//				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1D8D8, 0x1DBD7, TestDatalog); //DS Results
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
//				TestDatalogEnd<<"\n"<<"==========H30V101_DfeIdac_FWTest_End=========="<<endl;
////				PUT_DATALOG(TestDatalogEnd.str());
//
//			}

		}

//        if(sJudgementType == "BothMethod")
//        {
//    		ostringstream SramDataLog;
//    		for(UINT MacroIndex= 0; MacroIndex<MacroLane_Sel.size(); MacroIndex++)
//    		{
//        		UINT MacroID = MacroLane_Sel[MacroIndex].MacroID;
//        		SRAM_READ(MacroID, 0x1D5CC, 0x1D5D4,SramDataLog, true);
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
		HiLink_PerMacro_Judge(MacroLane_Sel, "DfeIdac_Test_Conclusion",
				limitl_conclusion, DfeIdac_Result, limith_conclusion);
		HiLink_PerMacro_Judge(MacroLane_Sel, "CS_ErrorMessage",
				limitl_err_message, CS_ErrorMessage, limith_err_message);
		HiLink_PerLane_Judge(MacroLane_Sel, "DS_ErrorMessage",
				limitl_err_message, DS_ErrorMessage, limith_err_message);

		if ((sJudgementType == "BothMethod")
				|| (PreJudge_Result == false))
		{
			double limitl_quarter_hvcc = -32767;
			double limith_quarter_hvcc = 32768;
			double limitl_half_hvcc = -32767;
			double limith_half_hvcc = 32768;
			//Judge table  2-6
			HiLink_PerLane_Judge(MacroLane_Sel, "Half_HVCC_Public",
					limitl_half_hvcc, Half_HVCC_Public, limith_half_hvcc);
			HiLink_PerMacro_Judge(MacroLane_Sel, "Quarter_CS_HVCC_Public",
					limitl_quarter_hvcc, Quarter_CS_HVCC_Public,
					limith_quarter_hvcc);

			//Judge table 2-8 according to ATB user guide
			HiLink_PerMacroCSCalArrayD_Judge(MacroLane_Sel, FWABIST_DFEIDAC,
					CS_Calculate_Output);
			HiLink_PerLaneCalArrayD_Judge(MacroLane_Sel, FWABIST_DFEIDAC,
					DS_Calculate_Output);
		}

//                SetTestBin(api);
	}
};

REGISTER_TESTCLASS("FWABIST_DFEIDAC", FWABIST_DFEIDAC)
