
#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"

using namespace std;

void DCGAIN_CALCULATION(const MACRO_LANE_SEL& MacroLane_Sel,
		LANE_DOUBLE& Input1, LANE_DOUBLE& Input2, LANE_DOUBLE& Input3,
		LANE_DOUBLE& Input4, LANE_DOUBLE& Input5, LANE_DOUBLE& Input6,
		LANE_DOUBLE& Input7, LANE_DOUBLE& Input8, LANE_DOUBLE& CalCulate_Result)
{

//		D2S_FRAMEWORK;

	LANE_DOUBLE tmp_part1;
	LANE_DOUBLE tmp_part2;

//		FOR_EACH_SITE_BEGIN();
//	    uint  SiteID = CURRENT_SITE_NUMBER()-1;
//	FOREACH_ACTIVE_SITE()
//	{
//		unsigned int SiteID = api->Get_active_site();
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		//DS information
		for (uint midx = 0; midx < MacroLane_Sel.size(); midx++)
		{
			uint MacroID = MacroLane_Sel[midx].MacroID;
			const vector<uint>& vLane = MacroLane_Sel[midx].vLane;
			for (uint lidx = 0; lidx < vLane.size(); lidx++)
			{
				uint LaneID = vLane[lidx];
				tmp_part1[SiteID][MacroID][LaneID] =
						(Input1[SiteID][MacroID][LaneID]
								- Input2[SiteID][MacroID][LaneID])
								- (Input3[SiteID][MacroID][LaneID]
										- Input4[SiteID][MacroID][LaneID]);
				tmp_part2[SiteID][MacroID][LaneID] =
						(Input5[SiteID][MacroID][LaneID]
								- Input6[SiteID][MacroID][LaneID])
								- (Input7[SiteID][MacroID][LaneID]
										- Input8[SiteID][MacroID][LaneID]);
				CalCulate_Result[SiteID][MacroID][LaneID] = 20
						* log10(
								tmp_part1[SiteID][MacroID][LaneID]
										/ tmp_part2[SiteID][MacroID][LaneID]);

//                                    cout << "CalCulate_Result Macro"<<  MacroID << "Lane" << LaneID << CalCulate_Result[SiteID][MacroID][LaneID] << endl;
			}
		}
	FOREACH_ACTIVESITE_END

}

class DcGain: public TestClass
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
//	add_param("PinList","PinString",&mPinList);
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
		static MACRO_DOUBLE DcGain_Result;
		static LANE_DOUBLE DS_ErrorMessage;
		static MACRO_DOUBLE CS_ErrorMessage;
		static LANE_DOUBLE Half_HVCC_Public;
		static MACRO_DOUBLE Quarter_CS_HVCC_Public;
		static LANE_DOUBLE pos_CTLE_EQ_STAGE1_OFFSET_POSITIVE;
		static LANE_DOUBLE pos_CTLE_EQ_STAGE1_OFFSET_NEGATIVE;
		static LANE_DOUBLE pos_CTLE_GN_STAGE3_OFFSET_POSITIVE;
		static LANE_DOUBLE pos_CTLE_GN_STAGE3_OFFSET_NEGATIVE;
		static LANE_DOUBLE neg_CTLE_EQ_STAGE1_OFFSET_POSITIVE;
		static LANE_DOUBLE neg_CTLE_EQ_STAGE1_OFFSET_NEGATIVE;
		static LANE_DOUBLE neg_CTLE_GN_STAGE3_OFFSET_POSITIVE;
		static LANE_DOUBLE neg_CTLE_GN_STAGE3_OFFSET_NEGATIVE;
		static LANE_DOUBLE Temperature_code;
		static LANE_DOUBLE CalCulate_Result;

		static bool PreJudge_Result;

		int iLifeclk2dig_sel_pin_api;

		//=============================================
		// Variables and MacroLane initialization
		//=============================================
		INT iDebugAnalog;

		stDcGain sDcGain = H30_DcGain_DcGain;

//		static STRING mPinList = "";
//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);

//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

//		TheSoft.Flow().Power().SetPower("Hilink_General_Power_H");
//		TheSoft.Flow().Level().SetLevel("HILINK_LVL_FUN_L");
//
//		TheInst.DCVS().Power().Apply();
//		TheInst.Digital().Level().Apply();
//		if(PrintDebugEn) cout<<"power level timing apply() at here"<<endl;


//          extern stDcGain H30_DcGain_DcGain;       
		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList, mPinList);

//                GlobalInitPattern = "HILINK_R04_SD5875V100_INIT_ALL_3_V2_Case01";
//		ON_FIRST_INVOCATION_BEGIN();

		uint iRefclk0_freqm100 = uint(dRefCLK_MHz * 100);
		uint iRefclk1_freqm100 = uint(dRefCLK2_MHz * 100);

//		D2S_FRAMEWORK;
//		GET_TEST_INFO;
		/**************Clear API and CSConfigBeforeCal***set proper API depending on applications and Release MCU*********/

		//Step1 and Step2: PowerUp and Reset && Config Ctle and do calibration, this step has been done before this test suite
		//Step3: Load Abist test firmware: H30V101_ABIST_DcGain.bin
		LoadFirmwareToSram(MacroLane_Sel, DcGain_Bin, DcGain_Cycles);

		//Step4: If let FW do the judgement, Set the spec
		if ((sJudgementType == "UseExternalSpec_FW_Judge")
				|| (sJudgementType == "BothMethod"))
		{
//			WriteSingleSpecToSram(MacroLane_Sel, 0x1F860, 23.5, 0x1F862, 1.2,1000);// initial 23.5  , change to 25.5 by tony 20210918

			WriteSingleSpecToSram(MacroLane_Sel, 0x1F860, 23.5, 0x1F862, 1.2,1000);// initial 23.5  , change to 25.5 by tony 20210918

			WriteSingleSpecToSram(MacroLane_Sel, 0x1F864, -4.5, 0x1F866, 1.2,1000);

		}

		//Step5: Config DCGain test API.
//		sprintf(label,"H30V101_Config_DCGain_testAPI_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN("H30V101_Config_DCGain_testAPI_",	Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);
		//		Config_RefClk_CoreClk(iRefclk0_freqm100, iRefclk1_freqm100);

		SRAM.CSAPIRegs.setrefclk0_freqm100_api(iRefclk0_freqm100).Write2DUT(1);
		SRAM.CSAPIRegs.setrefclk1_freqm100_api(iRefclk1_freqm100).Write2DUT(2);
		//Configure core_clk select
		SRAM.CSAPIRegs.setcore_clk_selext_pin_api(giCore_clk_selext_pin_api).Write2DUT(0);

		SRAM.CSAPIRegs.setcore_clk_sel_pin_api(giCore_clk_sel_pin_api).Write2DUT(0);

		SRAM.CSAPIRegs.setcoreclk_sel_en_api(0x1).Write2DUT(4);
//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();
		//TheInst.Wait(0.050);// tony think this wait time is necesary


//		sprintf(label,"H30V101_Config2_DCGain_testAPI_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN("H30V101_Config2_DCGain_testAPI_",Global_D2S_Mode);
		cout<<"DcGain GlobalInitPattern = "<<GlobalInitPattern<<endl;
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
		SRAM.ABISTAPIRegs.setctle_dc_gain_abist_api(0x1).Write2DUT(0);

//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();


		//Step6: Release MCU
//		sprintf(label,"H30V101_ReleaseMCU_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN( "H30V101_ReleaseMCU_",Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);
		SRAM.CPAPIRegs.setmcurstb(0x1).Write2DUT(8);
		d2s::d2s_LABEL_END();


		//Step7: Wait TOP_FSM_DONE_API
		EXPECT_RESULT Top_Fsm_Result;
		WaitDoneMacro(MacroLane_Sel,SRAM.TOPAPIRegs.REG_INFO.top_fsm_done_api(), 1, 100, 1.0,Top_Fsm_Result);

		//After MCU Done, read all regs
		//READ_ALL_CSR;
		//TheInst.Wait(0.005);//add by tony
		// Step8: hold MCU in reset mode

		ResetMCU(MacroLane_Sel);
		//TheInst.Wait(0.005);//add by tony
		//Step9:Clear ATB test API
//			sprintf(label,"H30V101_Clear_DcGain_testAPI_%f_%f_",Vcoef,Temp);
//			fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN( "H30V101_Clear_DcGain_testAPI_",
				Global_D2S_Mode);
		selectMacro_MB(MacroLane_Sel);
		SRAM.ABISTAPIRegs.setctle_dc_gain_abist_api(0x0).Write2DUT(0);
		SRAM.ABISTAPIRegs.settest_mode_abist_api(0x0).Write2DUT(2);
//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();


		//Step10: Read SRAM results
		SEGMENT_READ_MACRO(MacroLane_Sel,
				SRAM.ABISTAPIRegs.REG_INFO.ctle_dc_gain_status_abist_api(),
				DcGain_Result);

		//The following code are for detail result dataloging
		FWAbist_PreJudge(MacroLane_Sel, DcGain_Result, PreJudge_Result);

		FW_ABIST_READ_ErrorMessage(MacroLane_Sel, 0x1FCFA, 0x1, 0x1FD02,
				CS_ErrorMessage, DS_ErrorMessage);

		//Step10: Read SRAM Results
		if ((sJudgementType == "BothMethod")
				|| (PreJudge_Result == false) || (Global_D2S_Mode == 0))
		{

			FW_ABIST_READ_HVCC(MacroLane_Sel, 0x1FD04, 0x2, 0x1FD14,
					Quarter_CS_HVCC_Public, Half_HVCC_Public);

			FW_ABIST_READ_LANEDOUBLE(MacroLane_Sel, 0x1F8A8, 146,
					pos_CTLE_EQ_STAGE1_OFFSET_POSITIVE, Half_HVCC_Public);
			FW_ABIST_READ_LANEDOUBLE(MacroLane_Sel, 0x1F8AA, 146,
					pos_CTLE_EQ_STAGE1_OFFSET_NEGATIVE, Half_HVCC_Public);
			FW_ABIST_READ_LANEDOUBLE(MacroLane_Sel, 0x1F8BC, 146,
					pos_CTLE_GN_STAGE3_OFFSET_POSITIVE, Half_HVCC_Public);
			FW_ABIST_READ_LANEDOUBLE(MacroLane_Sel, 0x1F8BE, 146,
					pos_CTLE_GN_STAGE3_OFFSET_NEGATIVE, Half_HVCC_Public);
			FW_ABIST_READ_LANEDOUBLE(MacroLane_Sel, 0x1F8D0, 146,
					neg_CTLE_EQ_STAGE1_OFFSET_POSITIVE, Half_HVCC_Public);
			FW_ABIST_READ_LANEDOUBLE(MacroLane_Sel, 0x1F8D2, 146,
					neg_CTLE_EQ_STAGE1_OFFSET_NEGATIVE, Half_HVCC_Public);
			FW_ABIST_READ_LANEDOUBLE(MacroLane_Sel, 0x1F8E4, 146,
					neg_CTLE_GN_STAGE3_OFFSET_POSITIVE, Half_HVCC_Public);
			FW_ABIST_READ_LANEDOUBLE(MacroLane_Sel, 0x1F8E6, 146,
					neg_CTLE_GN_STAGE3_OFFSET_NEGATIVE, Half_HVCC_Public);
			FW_ABIST_READ_LANEDOUBLE(MacroLane_Sel, 0x1F8F8, 146,
					Temperature_code);

			DCGAIN_CALCULATION(MacroLane_Sel,
					pos_CTLE_GN_STAGE3_OFFSET_POSITIVE,
					pos_CTLE_GN_STAGE3_OFFSET_NEGATIVE,
					neg_CTLE_GN_STAGE3_OFFSET_POSITIVE,
					neg_CTLE_GN_STAGE3_OFFSET_NEGATIVE,
					pos_CTLE_EQ_STAGE1_OFFSET_POSITIVE,
					pos_CTLE_EQ_STAGE1_OFFSET_NEGATIVE,
					neg_CTLE_EQ_STAGE1_OFFSET_POSITIVE,
					neg_CTLE_EQ_STAGE1_OFFSET_NEGATIVE, CalCulate_Result);

////			for(uint macroIndex=0; macroIndex < MacroLane_Sel.size();macroIndex++)
////			{
////				//Readback Sram result for EVB Corrlation purpose
////				ostringstream  TestDatalogBegin, TestDatalogEnd;
////				TestDatalogBegin<<"\n"<<"==========H30V101_DcGain_LR_FWTest_Start==========";
//////				PUT_DATALOG(TestDatalogBegin.str());
////
////				ostringstream  TestDatalog;
////				FWAbistHeader(MacroLane_Sel, macroIndex, HILINK_FIRMWARE_LABEL_DEFAULT, DcGain_Bin, "DcGain_LR", TestDatalog);
////
////				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1F868, 0x1FCF7, TestDatalog); //DS Results
////				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FCF8, 0x1FD15, TestDatalog); //Results State and Common Information
////				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FDB6, 0x1FDC1, TestDatalog); //ABIST API
////				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FEDE, 0x1FEE1, TestDatalog); //DS7 API state
////				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FF02, 0x1FF05, TestDatalog); //DS6 API state
////				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FF26, 0x1FF29, TestDatalog); //DS5 API state
////				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FF4A, 0x1FF4D, TestDatalog); //DS4 API state
////				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FF6E, 0x1FF71, TestDatalog); //DS3 API state
////				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FF92, 0x1FF95, TestDatalog); //DS2 API state
////				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FFB6, 0x1FFB9, TestDatalog); //DS1 API state
////				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FFDA, 0x1FFDD, TestDatalog); //DS0 API state
////				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FFFE, 0x1FFFF, TestDatalog); //TOP API state
////
////				PrinfToEdf_FWAbist(TestDatalog);
////
////				TestDatalogEnd<<"\n"<<"==========H30V101_DcGain_LR_FWTest_End=========="<<endl;
//////				PUT_DATALOG(TestDatalogEnd.str());
////			}
		}

//       if(sJudgementType == "BothMethod")
//        {
//    		//debug info to compare with EVB output
//    		ostringstream SramDataLog;
//    		for(UINT MacroIndex= 0; MacroIndex<MacroLane_Sel.size(); MacroIndex++)
//    		{
//        		UINT MacroID = MacroLane_Sel[MacroIndex].MacroID;
//    		    SRAM_READ(MacroID, 0x1F860, 0x1F864,SramDataLog, true);
//    		}
//        }

		//=============================================
		// Datalog
		//=============================================
		double limitl_conclusion = 1;
		double limith_conclusion = 1;
		HiLink_PerMacro_Judge(MacroLane_Sel, "DcGain_Test_Conclusion",
				limitl_conclusion, DcGain_Result, limith_conclusion);

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
			double limitl_half_hvcc_public = -32767;
			double limith_half_hvcc_public = 32768;
			HiLink_PerLane_Judge(MacroLane_Sel, "Half_HVCC_Public",
					limitl_half_hvcc_public, Half_HVCC_Public,
					limith_half_hvcc_public);

			double limitl_offset_positive = 0;
			double limith_offset_positive = 1200;

			double limitl_offset_negative = 0;
			double limith_offset_negative = 1200;

			HiLink_PerLane_Judge(MacroLane_Sel,
					"pos_CTLE_EQ_STAGE1_OFFSET_POSITIVE",
					limitl_offset_positive, pos_CTLE_EQ_STAGE1_OFFSET_POSITIVE,
					limith_offset_positive);
			HiLink_PerLane_Judge(MacroLane_Sel,
					"pos_CTLE_EQ_STAGE1_OFFSET_NEGATIVE",
					limitl_offset_negative, pos_CTLE_EQ_STAGE1_OFFSET_NEGATIVE,
					limith_offset_negative);
			HiLink_PerLane_Judge(MacroLane_Sel,
					"pos_CTLE_GN_STAGE3_OFFSET_POSITIVE",
					limitl_offset_positive, pos_CTLE_GN_STAGE3_OFFSET_POSITIVE,
					limith_offset_positive);
			HiLink_PerLane_Judge(MacroLane_Sel,
					"pos_CTLE_GN_STAGE3_OFFSET_NEGATIVE",
					limitl_offset_negative, pos_CTLE_GN_STAGE3_OFFSET_NEGATIVE,
					limith_offset_negative);
			HiLink_PerLane_Judge(MacroLane_Sel,
					"neg_CTLE_EQ_STAGE1_OFFSET_POSITIVE",
					limitl_offset_positive, neg_CTLE_EQ_STAGE1_OFFSET_POSITIVE,
					limith_offset_positive);
			HiLink_PerLane_Judge(MacroLane_Sel,
					"neg_CTLE_EQ_STAGE1_OFFSET_NEGATIVE",
					limitl_offset_negative, neg_CTLE_EQ_STAGE1_OFFSET_NEGATIVE,
					limith_offset_negative);
			HiLink_PerLane_Judge(MacroLane_Sel,
					"neg_CTLE_GN_STAGE3_OFFSET_POSITIVE",
					limitl_offset_positive, neg_CTLE_GN_STAGE3_OFFSET_POSITIVE,
					limith_offset_positive);
			HiLink_PerLane_Judge(MacroLane_Sel,
					"neg_CTLE_GN_STAGE3_OFFSET_NEGATIVE",
					limitl_offset_negative, neg_CTLE_GN_STAGE3_OFFSET_NEGATIVE,
					limith_offset_negative);

			double limitl_temperature_code = -32767;
			double limith_temperature_code = 32768;
			HiLink_PerLane_Judge(MacroLane_Sel, "Temperature_code",
					limitl_temperature_code, Temperature_code,
					limith_temperature_code);

			HiLink_PerLane_Judge_DcGain(MacroLane_Sel, "DcGain_Calculate",
					CalCulate_Result, Temperature_code);
		}

//        SetTestBin(); //masked by tony 20210707

	}
};

REGISTER_TESTCLASS("DcGain", DcGain)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TM Purpose:                                                                                                                //
//                                                                                                                            //
//                                    The following code are all sub functions                                                //
//																		                                                  	  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

