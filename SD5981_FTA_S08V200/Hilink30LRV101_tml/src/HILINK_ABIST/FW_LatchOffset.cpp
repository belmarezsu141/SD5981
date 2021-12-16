//for test method API interfaces

#include <Common_Func/HiLink30_Common_Func.h>
#include <HILINK_ABIST/FWABIST_LATCHOFFSET.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TM Purpose:                                                                                                                //
//                                                                                                                            //
//                                    The following code are all sub functions                                                //
//																		                                                  	  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FW_ABIST_READ_DS_HVCC(const MACRO_LANE_SEL& MacroLane_Sel,
		INT DSStartAddress, INT DSIncreaseStep, LANE_DOUBLE& DsInfo)
{

//		D2S_FRAMEWORK;
//		GET_TEST_INFO;
//
//		sprintf(label,"READ_DS_HVCC_ErrorMessage_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
	d2s_JTAG& jtag = d2s_JTAG::Instance();
	d2s::d2s_LABEL_BEGIN("READ_DS_HVCC_ErrorMessage_",Global_D2S_Mode);

	for (uint midx = 0; midx < MacroLane_Sel.size(); midx++)
	{
		uint MacroID = MacroLane_Sel[midx].MacroID;
		const vector<uint>& vLane = MacroLane_Sel[midx].vLane;
		ostringstream str;
		str << "_M" << MacroID;

		selectMacro(MacroID);

		for (uint lidx = 0; lidx < vLane.size(); lidx++)
		{
			uint LaneID = vLane[lidx];
			ostringstream str;
			uint addr = DSStartAddress + LaneID * DSIncreaseStep;
			str << "ReadDSHVCC_ERROR_Message_M" << MacroID << "_L" << LaneID
					<< "_Address_0x" << hex << addr;

			jtag.read(addr >> 1, str.str());
		}
	}
//		fr.d2s_LABEL_END();
	d2s::d2s_LABEL_END();

	for (uint midx = 0; midx < MacroLane_Sel.size(); midx++)
	{
		uint MacroID = MacroLane_Sel[midx].MacroID;
		const vector<uint>& vLane = MacroLane_Sel[midx].vLane;
		ostringstream str;
		str << "_M" << MacroID;

		for (uint lidx = 0; lidx < vLane.size(); lidx++)
		{
			uint LaneID = vLane[lidx];
			ostringstream str;
			uint addr = DSStartAddress + LaneID * DSIncreaseStep;
			str << "ReadDSHVCC_ERROR_Message_M" << MacroID << "_L" << LaneID<< "_Address_0x" << hex << addr;


//			FOREACH_ACTIVE_SITE(api)
//			{
//				unsigned int SiteID = api->Get_active_site();
			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				DsInfo[SiteID][MacroID][LaneID] = jtag.getReadValue(str.str())[SiteID];
				DsInfo[SiteID][MacroID][LaneID] =
						((((INT) DsInfo[SiteID][MacroID][LaneID] & 0xff00) >> 8)
								| (((INT) DsInfo[SiteID][MacroID][LaneID]
										& 0x00ff) << 8)) * 800.0 / 1024; //big edian
				hout(DETAIL) << "DS HVCC: Macro: " << MacroID << " LaneID: "
						<< LaneID << " Value: "
						<< DsInfo[SiteID][MacroID][LaneID] << endl;
			FOREACH_ACTIVESITE_END
			}

	}
}

void LatchOffset_Calculate_Table_Processing(const MACRO_LANE_SEL& MacroLane_Sel,
		FWABIST_REGISTER_Base& FWABIST_REG_BASE,
		LANE_ARRAY_D& DS_Calculate_Output, LANE_ARRAY_MAP& DS_REG_Node_Value)
{

//	FOREACH_ACTIVE_SITE(api)
//	{
//		unsigned int SiteID = api->Get_active_site();
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		uint DSCalCount = FWABIST_REG_BASE.get_DS_FWABIST_Calculate_REG_count();

		LANE_ARRAY_D PerLane_Input1, PerLane_Input2;
		PerLane_Input1.init(DSCalCount, 0);
		PerLane_Input2.init(DSCalCount, 0);

		DS_Calculate_Output.init(DSCalCount, 0);

		for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size();
				macroIndex++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
			for (UINT LaneIndex = 0; LaneIndex < vLane.size(); LaneIndex++)
			{
				UINT LaneID = vLane[LaneIndex];

				for (uint RegIndex = 0;
						RegIndex
								< FWABIST_REG_BASE.get_DS_FWABIST_Calculate_REG_count();
						RegIndex++)
				{
					map<string, double>::iterator DSNode_Input1 =
							DS_REG_Node_Value[SiteID][MacroID][LaneID].find(
									FWABIST_REG_BASE.get_DS_Calculate_REG(
											RegIndex).Input1);
					if (DSNode_Input1
							!= DS_REG_Node_Value[SiteID][MacroID][LaneID].end())
					{
						PerLane_Input1[SiteID][MacroID][LaneID][RegIndex] =
								DSNode_Input1->second;
						hout(GENERAL) << "Macro: " << MacroID << " Lane: "
								<< LaneID << " Key: "
								<< FWABIST_REG_BASE.get_DS_Calculate_REG(
										RegIndex).Input1 << "Value: "
								<< PerLane_Input1[SiteID][MacroID][LaneID][RegIndex]
								<< endl;
					}
					else
						hout(RELEASE) << "Macro: " << MacroID << " Lane: "
								<< LaneID << " Key: "
								<< FWABIST_REG_BASE.get_DS_Calculate_REG(
										RegIndex).Input1 << " Not found"
								<< endl;

					map<string, double>::iterator DSNode_Input2 =
							DS_REG_Node_Value[SiteID][MacroID][LaneID].find(
									FWABIST_REG_BASE.get_DS_Calculate_REG(
											RegIndex).Input2);
					if (DSNode_Input2
							!= DS_REG_Node_Value[SiteID][MacroID][LaneID].end())
					{
						PerLane_Input2[SiteID][MacroID][LaneID][RegIndex] =
								DSNode_Input2->second;
						hout(GENERAL) << "Macro: " << MacroID << " Lane: "
								<< LaneID << " Key: "
								<< FWABIST_REG_BASE.get_DS_Calculate_REG(
										RegIndex).Input2 << "Value: "
								<< PerLane_Input2[SiteID][MacroID][LaneID][RegIndex]
								<< endl;
					}
					else
						hout(RELEASE) << "Macro: " << MacroID << " Lane: "
								<< LaneID << " Key: "
								<< FWABIST_REG_BASE.get_DS_Calculate_REG(
										RegIndex).Input2 << " Not found"
								<< endl;

					if (FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Formula
							== "Average")
					{
						DS_Calculate_Output[SiteID][MacroID][LaneID][RegIndex] =
								(PerLane_Input1[SiteID][MacroID][LaneID][RegIndex]
										+ PerLane_Input2[SiteID][MacroID][LaneID][RegIndex])
										/ 2;
						hout(RELEASE) << "Macro: " << MacroID << " Lane: "
								<< LaneID << " Key: "
								<< FWABIST_REG_BASE.get_DS_Calculate_REG(
										RegIndex).NODE_NAME << " Value: "
								<< DS_Calculate_Output[SiteID][MacroID][LaneID][RegIndex]
								<< endl;
					}

					else if (FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Formula
							== "Sub")
					{
						DS_Calculate_Output[SiteID][MacroID][LaneID][RegIndex] =
								PerLane_Input1[SiteID][MacroID][LaneID][RegIndex]
										- PerLane_Input2[SiteID][MacroID][LaneID][RegIndex];
						hout(RELEASE) << "Macro: " << MacroID << " Lane: "
								<< LaneID << " Key: "
								<< FWABIST_REG_BASE.get_DS_Calculate_REG(
										RegIndex).NODE_NAME << " Value: "
								<< DS_Calculate_Output[SiteID][MacroID][LaneID][RegIndex]
								<< endl;
					}
					else if (FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Formula
							== "AbsDiff")
					{
						DS_Calculate_Output[SiteID][MacroID][LaneID][RegIndex] =
								abs(
										(PerLane_Input1[SiteID][MacroID][LaneID][RegIndex]
												- PerLane_Input2[SiteID][MacroID][LaneID][RegIndex]));
						hout(RELEASE) << "Macro: " << MacroID << " Lane: "
								<< LaneID << " Key: "
								<< FWABIST_REG_BASE.get_DS_Calculate_REG(
										RegIndex).NODE_NAME << " Value: "
								<< DS_Calculate_Output[SiteID][MacroID][LaneID][RegIndex]
								<< endl;
					}
					else
					{
						hout(RELEASE) << " Fomula is NOT Supported!! " << endl;
					}
				}

			}
		}
		FOREACH_ACTIVESITE_END
}

class LatchOffset: public TestClass
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
		static MACRO_DOUBLE LatchOffset_Result;
		static LANE_DOUBLE HVCC_Public;
		static LANE_DOUBLE DS_ErrorMessage;
		static MACRO_DOUBLE CS_ErrorMessage;

		static LANE_ARRAY_D DS_REG_RESULT;
		static LANE_ARRAY_MAP DS_REG_Node_Value;
		static LANE_ARRAY_D DS_Calculate_Output;
		static LANE_DOUBLE Half_HVCC_Public;
		static MACRO_DOUBLE Quarter_CS_HVCC_Public;
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
		stLatchOffset sLatchOffset;
//		static STRING mPinList = "";
//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;

		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

		TheInst.DCVI().Power().Apply();
		TheInst.Digital().Level().Apply();

		if(PrintDebugEn) cout<<"power level apply at here"<<endl;

		if (strTestsuiteName == "H30_LatchOffset_VDDL_to_VDDL")
		{
			sLatchOffset = H30_LatchOffset_VDDL_to_VDDL_LatchOffset;
		}
		else if (strTestsuiteName == "H30_LatchOffset_VDDL_to_VDDH")
		{
			sLatchOffset = H30_LatchOffset_VDDL_to_VDDH_LatchOffset;
		}
		else if (strTestsuiteName == "H30_LatchOffset_VDDH_to_VDDL")
		{
			sLatchOffset = H30_LatchOffset_VDDH_to_VDDL_LatchOffset;
		}

		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList,mPinList);


		LATCHOFFSET_TABLE_DEFINE& FWABIST_LATCHOFFSET =
				LATCHOFFSET_TABLE_DEFINE::getInstance();

		uint DSCalCount =
				FWABIST_LATCHOFFSET.get_DS_FWABIST_Calculate_REG_count();
//		cout << "DSCalCount = " << DSCalCount << endl;

//		ON_FIRST_INVOCATION_BEGIN();

		uint iRefclk0_freqm100 = uint(dRefCLK_MHz * 100);
		uint iRefclk1_freqm100 = uint(dRefCLK2_MHz * 100);

//		D2S_FRAMEWORK;
//		GET_TEST_INFO;

		/**************Clear API and CSConfigBeforeCal***set proper API depending on applications and Release MCU*********/

		//Step1 Step2: PowerUp and Reset && Config Ctle and do calibration, this step has been done before this test suite
		//Step3: Load Abist test firmware: H30V101_ABIST_LatchOffset.bin
		LoadFirmwareToSram(MacroLane_Sel, LatchOffset_Bin, LatchOffset_Cycles);

		//Step4:Use FW judge, write Spec first
		if ((sJudgementType == "UseExternalSpec_FW_Judge")
				|| (sJudgementType == "BothMethod"))
		{
			WriteSingleSpecToSram(MacroLane_Sel, 0x1F002, 15, 0x1F004, -15, 1);
			//20211207
			WriteSingleSpecToSram(MacroLane_Sel, 0x1EFFE, 15, 0x1F000, -15, 1);
			WriteSingleSpecToSram(MacroLane_Sel, 0x1EFFA, 15, 0x1EFFC, -15, 1);
		}

		//Step5: Config latchoffset test API.
//		sprintf(label,"H30V101_Config_LatchOffset_testAPI1_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN("H30V101_Config_LatchOffset_testAPI1_", Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);

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
//		sprintf(label,"H30V101_Config2_LatchOffset_testAPI_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN("H30V101_Config2_LatchOffset_testAPI_", Global_D2S_Mode);


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

			SRAM.CSAPIRegs.setlifeclk2dig_sel_pin_api(iLifeclk2dig_sel_pin_api).Write2DUT(0, false);

		}

		selectMacro_MB(MacroLane_Sel);
		SRAM.ABISTAPIRegs.setlatch_ofst_abist_api(0x1).Write2DUT(0);
		SRAM.DSAPIRegs.setctle_tap_en_api(0x0).Write2DUT(4);
		SRAM.ABISTAPIRegs.settest_mode_abist_api(0x1).Write2DUT(2);

//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();

		//Step6: Release MCU
		ReleaseMCU(MacroLane_Sel);

		//Step7: Wait TOP_FSM_DONE_API
		EXPECT_RESULT Top_Fsm_Result;
		WaitDoneMacro(MacroLane_Sel, SRAM.TOPAPIRegs.REG_INFO.top_fsm_done_api(), 1, 200, 2, Top_Fsm_Result);

		//After MCU Done, read all regs
		//READ_ALL_CSR;

		// Step8: hold MCU in reset mode
		ResetMCU(MacroLane_Sel);

		//Step 9:Clear latchoffset test API
//        sprintf(label,"H30V101_Clear_LatchOffset_testAPI_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN( "H30V101_Clear_LatchOffset_testAPI_",Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);

		SRAM.ABISTAPIRegs.setlatch_ofst_abist_api(0x0).Write2DUT(0);
		SRAM.DSAPIRegs.setctle_tap_en_api(0x0).Write2DUT(4);
		SRAM.ABISTAPIRegs.settest_mode_abist_api(0x0).Write2DUT(2);
		d2s::d2s_LABEL_END();
//		fr.d2s_LABEL_END();

		SEGMENT_READ_MACRO(MacroLane_Sel,
				SRAM.ABISTAPIRegs.REG_INFO.latch_ofst_status_abist_api(),
				LatchOffset_Result);
		//The following code are for detail result dataloging
		FWAbist_PreJudge(MacroLane_Sel, LatchOffset_Result, PreJudge_Result);
		FW_ABIST_READ_ErrorMessage(MacroLane_Sel, 0x1FCFA, 0x1, 0x1FD02,
				CS_ErrorMessage, DS_ErrorMessage);
		//Step 18: Read Sram
		if ((PreJudge_Result == false)
				|| (sJudgementType == "BothMethod")
				|| (Global_D2S_Mode == 0))
		{
			//Read back error message

			FW_ABIST_READ_DS_HVCC(MacroLane_Sel, 0x1F024, 162, HVCC_Public);
			FW_ABIST_READ_HVCC(MacroLane_Sel, 0x1FD04, 0x2, 0x1FD14,
					Quarter_CS_HVCC_Public, Half_HVCC_Public);

			//Setup key <-> value mapping
			FWABIST_LATCHOFFSET.FWABIST_Registers_Map_Init(MacroLane_Sel,
					DS_REG_RESULT, DS_REG_Node_Value, HVCC_Public);

			//Processing all nodes
			LatchOffset_Calculate_Table_Processing(MacroLane_Sel,
					FWABIST_LATCHOFFSET, DS_Calculate_Output,
					DS_REG_Node_Value);

//			for(uint macroIndex=0; macroIndex < MacroLane_Sel.size();macroIndex++)
//			{
//				//Readback Sram result for EVB Corrlation purpose
//				ostringstream  TestDatalogBegin, TestDatalogEnd;
//				TestDatalogBegin<<"\n"<<"==========H30V101_LatchOffset_LR_FWTest_Start=========="<<endl;
////				PUT_DATALOG(TestDatalogBegin.str());
//
//				ostringstream  TestDatalog;
//				FWAbistHeader(MacroLane_Sel, macroIndex, HILINK_FIRMWARE_LABEL_DEFAULT, LatchOffset_Bin, "LatchOffset_LR", TestDatalog);
//
//				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1F00A, 0x1F519, TestDatalog); //DS Results
//				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FCFA, 0x1FD15, TestDatalog); //Results State and Common Information
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
//				TestDatalogEnd<<"\n"<<"==========H30V101_LatchOffset_LR_FWTest_End=========="<<endl;
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
//        		SRAM_READ(MacroID, 0x1F002, 0x1F002,SramDataLog, true);
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
		HiLink_PerMacro_Judge(MacroLane_Sel, "LatchOffset_Test_Conclusion",
				limitl_conclusion, LatchOffset_Result, limith_conclusion);
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
			double limitl_hvcc_public = -32767;
			double limith_hvcc_public = 32768;

			HiLink_PerMacro_Judge(MacroLane_Sel, "Quarter_CS_HVCC_Public",
					limitl_quarter_hvcc, Quarter_CS_HVCC_Public,
					limith_quarter_hvcc);
			HiLink_PerLane_Judge(MacroLane_Sel, "Half_HVCC_Public",
					limitl_half_hvcc, Half_HVCC_Public, limith_half_hvcc);
			HiLink_PerLane_Judge(MacroLane_Sel, "HVCC_Public",
					limitl_hvcc_public, HVCC_Public, limith_hvcc_public);
//			HiLink_PerMacro_Judge(MacroLane_Sel,"CS_ErrorMessage",CS_ErrorMessage);
//			HiLink_PerLane_Judge(MacroLane_Sel, "DS_ErrorMessage", DS_ErrorMessage);

			//Judge table 2-11 according to ATB user guide
			HiLink_PerLaneCalArrayD_Judge(MacroLane_Sel, FWABIST_LATCHOFFSET,
					DS_Calculate_Output);
		}

//        SetTestBin(api); //masked by tony 20210707
	}
};
REGISTER_TESTCLASS("LatchOffset", LatchOffset)

