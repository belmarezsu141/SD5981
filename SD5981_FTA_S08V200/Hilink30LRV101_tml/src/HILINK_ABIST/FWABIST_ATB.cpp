//for test method API interfaces

#include <HILINK_ABIST/FWABIST_ATB.h>

#include <Common_Func/HiLink30_Common_Func.h>

using namespace std;

class FWABIST_ATB: public TestClass
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
		static INT iCSR_check;
		static MACRO_LANE_SEL MacroLane_Sel;
		static MACRO_DOUBLE Atb_Result;

		static MACRO_ARRAY_D SS_REG_RESULT;
		static MACRO_ARRAY_D CS_REG_RESULT;
		static LANE_ARRAY_D DS_REG_RESULT;

		static MACRO_ARRAY_MAP SS_REG_Node_Value;
		static MACRO_ARRAY_MAP CS_REG_Node_Value;
		static LANE_ARRAY_MAP DS_REG_Node_Value;

		static MACRO_ARRAY_D SS_Calculate_Output;
		static MACRO_ARRAY_D CS_Calculate_Output;
		static LANE_ARRAY_D DS_Calculate_Output;

		static LANE_DOUBLE Half_HVCC_Part1;
		static LANE_DOUBLE Half_HVCC_Public;
		static LANE_DOUBLE DS_ErrorMessage;
		static MACRO_DOUBLE CS_ErrorMessage;
		static MACRO_DOUBLE Quarter_CS_HVCC_Part1;
		static MACRO_DOUBLE Quarter_CS_HVCC_Public;
		static MACRO_DOUBLE Part1_Enable_Mask;
		static MACRO_DOUBLE Part2_Enable_Mask;

		static bool PreJudge_Result;
//		STRING mPinList;

		int iLifeclk2dig_sel_pin_api;
		//=============================================
		// Variables and MacroLane initialization
		//=============================================
//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);

//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

	    static stFWABIST_ATB FwAbist_Atb = H30_Atb_VDDL_FWABIST_ATB;

		Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList,mPinList);


		ATB_TABLE_DEFINE& FWABIST_ATB = ATB_TABLE_DEFINE::getInstance();

		Atb_Result.init(0);

		UINT iRefclk0_freqm100 = uint(dRefCLK_MHz * 100);
		UINT iRefclk1_freqm100 = uint(dRefCLK2_MHz * 100);
		//Disconnect TX RX
//		api->Execute_test("H30_Disconnect_TX_RX_DZ");
		H30_Disconnect_TX_RX_DZ();

		/**************Clear API and CSConfigBeforeCal***set proper API depending on applications and Release MCU*********/

		//Step1: Ctle Pre Setting, set before this test suite
		//Step2: LoadFirmware to Sram
		LoadFirmwareToSram(MacroLane_Sel, Atb_Lr_Bin, Atb_Lr_Cycles);

		//Step3: FW judge, write spec value fist
		if ((sJudgementType == "UseExternalSpec_FW_Judge")
				|| (sJudgementType == "BothMethod"))
		{
			WritePerMacroSpecToSram(MacroLane_Sel, FWABIST_ATB);

			WritePerLaneSpecToSram(MacroLane_Sel, FWABIST_ATB, "NO");

		}

		//READ_ALL_CSR;

		//Step4: Config ATB test API.
		d2s::d2s_LABEL_BEGIN("H30V101_Config_FWABIST_testAPI_",Global_D2S_Mode);		//Global_D2S_Mode


		selectMacro_MB(MacroLane_Sel);
		//Config refclk and core clk same as
		//		Config_RefClk_CoreClk(iRefclk0_freqm100, iRefclk1_freqm100);

		SRAM.CSAPIRegs.setrefclk0_freqm100_api(iRefclk0_freqm100).Write2DUT(1);
		SRAM.CSAPIRegs.setrefclk1_freqm100_api(iRefclk1_freqm100).Write2DUT(2);
		//Configure core_clk select
		SRAM.CSAPIRegs.setcore_clk_selext_pin_api(giCore_clk_selext_pin_api).Write2DUT(0);

		SRAM.CSAPIRegs.setcore_clk_sel_pin_api(giCore_clk_sel_pin_api).Write2DUT(0);

		SRAM.CSAPIRegs.setcoreclk_sel_en_api(0x1).Write2DUT(4);
		d2s::d2s_LABEL_END();

		d2s::d2s_LABEL_BEGIN("H30V101_Config2_FWABIST_testAPI_",Global_D2S_Mode);	//Global_D2S_Mode

		if(PrintDebugEn) cout<< "GlobalInitPattern ="<<GlobalInitPattern<< endl;
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
//			api->info_message("Can't find valid init pattern !!! Please check pattern name!");
				cout
						<< "Can't find valid init pattern !!! Please check pattern name!"
						<< endl;
//					ERROR_EXIT(TM::ABORT_FLOW);
			}
			if (iLifeclk2dig_sel_pin_api != 1 && iLifeclk2dig_sel_pin_api != 0
					&& iLifeclk2dig_sel_pin_api != -1)
			{
//					cout << "Invalid macro has been choose !!! Please check macro ID!" << endl;
//			api->info_message("Invalid macro has been choose !!! Please check macro ID!");
				cout
						<< "Invalid macro has been choose !!! Please check macro ID!"
						<< endl;
//					ERROR_EXIT(TM::ABORT_FLOW);
			}

			SRAM.CSAPIRegs.setlifeclk2dig_sel_pin_api(iLifeclk2dig_sel_pin_api).Write2DUT(	0, false);

		}

		selectMacro_MB(MacroLane_Sel);
		//Config FWAbist test API
		SRAM.ABISTAPIRegs.setatb_abist_api(0x1).Write2DUT(0);
		SRAM.ABISTAPIRegs.settest_mode_abist_api(0x1).Write2DUT(2);

		d2s::d2s_LABEL_END();

		//Step5:	Start Part1 Test(TX\DSMISC), Use PUG Function EnableTxPrbsGen() to send 1010 Parttern in all DS Slices.
		//Step6:	Enable TX(SUB0_FSM_ABIST_API(Bit3))\DSMISC(SUB0_FSM_ABIST_API(Bit5)) test Mask API and Enable First Parts Test(SUB0_FSM_ABIST_API(Bit0)): set SUB0_FSM_ABIST_API (ABISTAPI CSR6 Bit[7:0]) = 0x29.

		d2s::d2s_LABEL_BEGIN("H30V101_EableTxPrbsGen_", Global_D2S_Mode);//Global_D2S_Mode

		selectMacro_MB(MacroLane_Sel);
		DS.txRegs.SliceID(0).Broadcast(1);
		EnableTxPrbsGen("CUSTOMER_PATTERN");

		SRAM.ABISTAPIRegs.setsub0_fsm_abist_api(0x29).Write2DUT(6);

		d2s::d2s_LABEL_END();

		//Step7: Release MCU
		ReleaseMCU(MacroLane_Sel);

		//Step8: Wait TOP_FSM_DONE_API =1
		EXPECT_RESULT Top_Fsm_Result;
		WaitDoneMacro(MacroLane_Sel,SRAM.TOPAPIRegs.REG_INFO.top_fsm_done_api(), 1, 100, 1,Top_Fsm_Result);



		//After MCU Done, read all regs
		//READ_ALL_CSR;

		// Step9: hold MCU in reset mode
		ResetMCU(MacroLane_Sel);

		//Step10:	Stop Part1 Test(TX\DSMISC), Use PUG Function DisableTxPrbsGen() to stop sending Parttern in all DS Slices.
		//Step11:	Start Part2 Test(CS\RX\DsClk), config TXPWRDB(TX CSR0[15]) = 0 in all DS Slices.
		//Step12:	Enable CS(SUB0_FSM_ABIST_API(Bit1)) \ RX(SUB0_FSM_ABIST_API(Bit2)) \ DsClk(SUB0_FSM_ABIST_API(Bit4)) test Mask API: set SUB0_FSM_ABIST_API (ABISTAPI CSR6 Bit[7:0]) = 0x16.

		d2s::d2s_LABEL_BEGIN("H30V101_DisableTxPrbsGen_StartPart2_",Global_D2S_Mode);		//Global_D2S_Mode


		selectMacro_MB(MacroLane_Sel);
		DS.txRegs.SliceID(0).Broadcast(1);
		DisableTxPrbsGen();
		DS.txRegs.settxpwrdb(0).Write2DUT(0);
		SRAM.ABISTAPIRegs.setsub0_fsm_abist_api(0x16).Write2DUT(6);
		d2s::d2s_LABEL_END();

		//Step13:	Release MCU Reset.
		ReleaseMCU(MacroLane_Sel);

		//Step13:	Wait TOP_FSM_DONE_API(TOPAPI CSR0 bit[15]) = 1.
		WaitDoneMacro(MacroLane_Sel,SRAM.TOPAPIRegs.REG_INFO.top_fsm_done_api(), 1, 100, 1,Top_Fsm_Result);



		//After MCU Done, read all regs
		//READ_ALL_CSR;

		//Step15:	Remove MCU Reset.
		//Step16:	Stop Part2 Test(CS\RX\DsClk), config TXPWRDB(TX CSR0[15]) = 1 in all DS Slices.

		d2s::d2s_LABEL_BEGIN("H30V101_HoldMCU_Reset_", Global_D2S_Mode);//Global_D2S_Mode

		selectMacro_MB(MacroLane_Sel);
		DS.txRegs.SliceID(0).Broadcast(1);
		SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8);
		DS.txRegs.settxpwrdb(1).Write2DUT(0);
		d2s::d2s_LABEL_END();

		//Step17:	Clear ATB test API. Simple-Mode set ATB_ABIST_API (ABISTAPI CSR0 Bit[3]) = 0 and TEST_MODE_ABIST_API (ABISTAPI CSR2[15:14]) = 0.
		d2s::d2s_LABEL_BEGIN("H30V101_Clear_FWABIST_testAPI_", Global_D2S_Mode);//Global_D2S_Mode

		selectMacro_MB(MacroLane_Sel);
		SRAM.ABISTAPIRegs.setatb_abist_api(0x0).Write2DUT(0);
		SRAM.ABISTAPIRegs.settest_mode_abist_api(0x0).Write2DUT(2);
		d2s::d2s_LABEL_END();

		SEGMENT_READ_MACRO(MacroLane_Sel,
				SRAM.ABISTAPIRegs.REG_INFO.atb_status_abist_api(), Atb_Result);

		//The following code are for detail result dataloging
		FWAbist_PreJudge(MacroLane_Sel, Atb_Result, PreJudge_Result);

		FW_ABIST_READ_ErrorMessage(MacroLane_Sel, 0x1FCFA, 0x1, 0x1FD02,
				CS_ErrorMessage, DS_ErrorMessage);

		//Step18: Read SRAM Results
		if ((PreJudge_Result == false)
				|| (sJudgementType == "BothMethod")
				|| (Global_D2S_Mode == 0))
		{
			//Read back table 2-9 in ATB userguide
			FW_ABIST_READ_HVCC(MacroLane_Sel, 0x1FCC8, 0x2, 0x1FCD8,
					Quarter_CS_HVCC_Part1, Half_HVCC_Part1);

			FW_ABIST_READ_HVCC(MacroLane_Sel, 0x1FD04, 0x2, 0x1FD14,
					Quarter_CS_HVCC_Public, Half_HVCC_Public);

			FW_ABIST_RESULT_READ(MacroLane_Sel, 0x1FCDA, Part1_Enable_Mask);

			FW_ABIST_RESULT_READ(MacroLane_Sel, 0x1FCDC, Part2_Enable_Mask);

			//Read back table 2-10 in ATB userguide
			FWABIST_ATB.FWABIST_Registers_Map_Init(MacroLane_Sel, SS_REG_RESULT,
					SS_REG_Node_Value, CS_REG_RESULT, CS_REG_Node_Value,
					DS_REG_RESULT, DS_REG_Node_Value, Half_HVCC_Part1,
					Half_HVCC_Public, Quarter_CS_HVCC_Part1,
					Quarter_CS_HVCC_Public);

			//Process table 2-11 in ATB user guide
			FWAbist_Calculate_Table_Processing(MacroLane_Sel, FWABIST_ATB,
					SS_Calculate_Output, CS_Calculate_Output,
					DS_Calculate_Output, SS_REG_Node_Value, CS_REG_Node_Value,
					DS_REG_Node_Value);

			//Readback Sram result for EVB Corrlation purpose

//				for(uint macroIndex=0; macroIndex < MacroLane_Sel.size();macroIndex++)
//				{
//					ostringstream  TestDatalogBegin, TestDatalogEnd;
//					TestDatalogBegin<<"\n"<<"==========H30V101_Atb_LR_FWTest_Start==========";
////					PUT_DATALOG(TestDatalogBegin.str());
//
//					    ostringstream  TestDatalog;
//						FWAbistHeaderMacroLane_Sel, macroIndex, HILINK_FIRMWARE_LABEL_DEFAULT, Atb_Lr_Bin, "Atb_LR", TestDatalog);
//
//						SRAM_READMacroLane_Sel[macroIndex].MacroID, 0x1F6D0, 0x1F981, TestDatalog); //CS and 8 DS
//						SRAM_READMacroLane_Sel[macroIndex].MacroID, 0x1FCB6, 0x1FD15, TestDatalog); //Test Condition
//						SRAM_READMacroLane_Sel[macroIndex].MacroID, 0x1FDB6, 0x1FDC1, TestDatalog); //ATB ABIST API
//						SRAM_READMacroLane_Sel[macroIndex].MacroID, 0x1FEDE, 0x1FEE1, TestDatalog); //DS7 API state
//						SRAM_READMacroLane_Sel[macroIndex].MacroID, 0x1FF02, 0x1FF05, TestDatalog); //DS6 API state
//						SRAM_READMacroLane_Sel[macroIndex].MacroID, 0x1FF26, 0x1FF29, TestDatalog); //DS5 API state
//						SRAM_READMacroLane_Sel[macroIndex].MacroID, 0x1FF4A, 0x1FF4D, TestDatalog); //DS4 API state
//						SRAM_READMacroLane_Sel[macroIndex].MacroID, 0x1FF6E, 0x1FF71, TestDatalog); //DS3 API state
//						SRAM_READMacroLane_Sel[macroIndex].MacroID, 0x1FF92, 0x1FF95, TestDatalog); //DS2 API state
//						SRAM_READMacroLane_Sel[macroIndex].MacroID, 0x1FFB6, 0x1FFB9, TestDatalog); //DS1 API state
//						SRAM_READMacroLane_Sel[macroIndex].MacroID, 0x1FFDA, 0x1FFDD, TestDatalog); //DS0 API state
//						SRAM_READMacroLane_Sel[macroIndex].MacroID, 0x1FFFE, 0x1FFFF, TestDatalog); //TOP API state
//						PrinfToEdf_FWAbistTestDatalog);
//
//					TestDatalogEnd<<"\n"<<"==========H30V101_Atb_LR_FWTest_End=========="<<endl;
//					PUT_DATALOG(TestDatalogEnd.str());
//				}
		}

//		//Debug info to compare with EVB limit setting
//                if(sJudgementType == "BothMethod")
//                {
//                        ostringstream SramDataLog;
//
//                        for(UINT MacroIndex= 0; MacroIndex<MacroLane_Sel.size(); MacroIndex++)
//                        {
//                                UINT MacroID = MacroLane_Sel[MacroIndex].MacroID;
//                                //Read back table 2-10(LR) or 2-12(VSR) in ATB userguide
//                                SRAM_READMacroID, 0x1F424, 0x1F6C8, SramDataLog, true);
//                        }
//
//                }

//=============================================
// Datalog
//=============================================
//Judge global pass/fail
		double limitl_conclusion = 1;
		double limith_conclusion = 1;
		HiLink_PerMacro_Judge(MacroLane_Sel, "ATB_Test_Conclusion",
				limitl_conclusion, Atb_Result, limith_conclusion);

		double limitl_cs_errormessage = 0;
		double limith_cs_errormessage = 0;
		HiLink_PerMacro_Judge(MacroLane_Sel, "CS_ErrorMessage",
				limitl_cs_errormessage, CS_ErrorMessage,
				limith_cs_errormessage);

		double limitl_ds_errormessage = 0;
		double limith_ds_errormessage = 0;
		HiLink_PerLane_Judge(MacroLane_Sel, "DS_ErrorMessage",
				limitl_ds_errormessage, DS_ErrorMessage,
				limith_ds_errormessage);

		if ((sJudgementType == "BothMethod")
				|| (PreJudge_Result == false))
		{
			//Judge table 2-9
			double limitl_quarter_cs_hvcc_part1 = -32767;
			double limith_quarter_cs_hvcc_part1 = 32768;
			HiLink_PerMacro_Judge(MacroLane_Sel, "Quarter_CS_HVCC_Part1",
					limitl_quarter_cs_hvcc_part1, Quarter_CS_HVCC_Part1,
					limith_quarter_cs_hvcc_part1);

			double limitl_part1_enable_mask = 41;
			double limith_part1_enable_mask = 41;
			HiLink_PerMacro_Judge(MacroLane_Sel, "Part1_Enable_Mask",
					limitl_part1_enable_mask, Part1_Enable_Mask,
					limith_part1_enable_mask);

			double limitl_part2_enable_mask = 22;
			double limith_part2_enable_mask = 22;
			HiLink_PerMacro_Judge(MacroLane_Sel, "Part2_Enable_Mask",
					limitl_part2_enable_mask, Part2_Enable_Mask,
					limith_part2_enable_mask);

			double limitl_half_hvcc_part1 = -32767;
			double limith_half_hvcc_part1 = 32768;
			HiLink_PerLane_Judge(MacroLane_Sel, "Half_HVCC_Part1",
					limitl_half_hvcc_part1, Half_HVCC_Part1,
					limith_half_hvcc_part1);

			double limitl_quarter_cs_hvcc_public = -32767;
			double limith_quarter_cs_hvcc_public = 32768;
			HiLink_PerMacro_Judge(MacroLane_Sel, "Quarter_CS_HVCC_Public",
					limitl_quarter_cs_hvcc_public, Quarter_CS_HVCC_Public,
					limith_quarter_cs_hvcc_public);

			double limitl_half_hvcc_public = -32767;
			double limith_half_hvcc_public = 32768;
			HiLink_PerLane_Judge(MacroLane_Sel, "Half_HVCC_Public",
					limitl_half_hvcc_public, Half_HVCC_Public,
					limith_half_hvcc_public);

			//Judge table 2-10 according to ATB user guide
			HiLink_PerMacroCSArrayD_Judge(MacroLane_Sel, FWABIST_ATB,
					CS_REG_RESULT);

			HiLink_PerLaneArrayD_Judge(MacroLane_Sel, FWABIST_ATB,
					DS_REG_RESULT);

			//Judge table 2-11 according to ATB user guide
			HiLink_PerMacroCSCalArrayD_Judge(MacroLane_Sel, FWABIST_ATB,
					CS_Calculate_Output);

			HiLink_PerLaneCalArrayD_Judge(MacroLane_Sel, FWABIST_ATB,
					DS_Calculate_Output);

		}

//                SetTestBin(api);
	}
};

REGISTER_TESTCLASS("FWABIST_ATB", FWABIST_ATB)

