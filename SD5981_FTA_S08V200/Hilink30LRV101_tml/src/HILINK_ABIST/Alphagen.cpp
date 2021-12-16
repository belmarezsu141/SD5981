//for test method API interfaces

#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"

using namespace std;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TM Purpose:                                                                                                                //
//                                                                                                                            //
//                                    The following code are all sub functions                                                //
//																		                                                  	  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Alphagen_CALCULATION(const MACRO_LANE_SEL& MacroLane_Sel, LANE_DOUBLE& Input1, LANE_DOUBLE& Input2, LANE_DOUBLE& Input3, LANE_DOUBLE& Input4, INT DivideRatio, LANE_DOUBLE& CalCulate_Result, INT SPEC_WRITTEN_RATE) {

    //			D2S_FRAMEWORK;

    LANE_DOUBLE tmp_part1;
    LANE_DOUBLE tmp_part2;

    FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
        //DS information
        for (uint midx = 0; midx < MacroLane_Sel.size(); midx++) {
            uint MacroID = MacroLane_Sel[midx].MacroID;
            const vector<uint>& vLane = MacroLane_Sel[midx].vLane;
            for (uint lidx = 0; lidx < vLane.size(); lidx++) {
                uint LaneID = vLane[lidx];
                tmp_part1[SiteID][MacroID][LaneID] = (Input1[SiteID][MacroID][LaneID] - Input2[SiteID][MacroID][LaneID]);
                tmp_part2[SiteID][MacroID][LaneID] = (Input3[SiteID][MacroID][LaneID] - Input4[SiteID][MacroID][LaneID]);
                CalCulate_Result[SiteID][MacroID][LaneID] = ((tmp_part1[SiteID][MacroID][LaneID] - tmp_part2[SiteID][MacroID][LaneID]) / DivideRatio) * SPEC_WRITTEN_RATE;
            }
        }
       FOREACH_ACTIVESITE_END

}

void Alphagen_CALCULATION(const MACRO_LANE_SEL& MacroLane_Sel, LANE_DOUBLE& Input1, LANE_DOUBLE& Input2, LANE_DOUBLE& CalCulate_Result, INT SPEC_WRITTEN_RATE) {

    //			D2S_FRAMEWORK;

	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//        unsigned int SiteID = api->Get_active_site();
        //DS information
        for (uint midx = 0; midx < MacroLane_Sel.size(); midx++) {
            uint MacroID = MacroLane_Sel[midx].MacroID;
            const vector<uint>& vLane = MacroLane_Sel[midx].vLane;
            for (uint lidx = 0; lidx < vLane.size(); lidx++) {
                uint LaneID = vLane[lidx];
                CalCulate_Result[SiteID][MacroID][LaneID] = (Input1[SiteID][MacroID][LaneID] - Input2[SiteID][MacroID][LaneID]) * SPEC_WRITTEN_RATE;
            }
        }
	FOREACH_ACTIVESITE_END
}


class Alphagen: public TestClass{
public:
		STRING 				mHiLink30_MacroList;
		STRING 				mPinList;
		DOUBLE              dRefCLK_MHz;
		DOUBLE              dRefCLK2_MHz;
		INT					iPrintLvl;
		STRING              sJudgementType;
    void init(){
    	add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
    						.set_comment("HiLink30 Macro List for test")
    	//					.set_options("0,1:0:1:FromPinList")
    						.set_default("0,1");
//    			add_param("PinList",		"PinString",&mPinList);
    			add_param("JudgementType","string",&sJudgementType)
    	//					.set_options("UseExternalSpec_FW_Judge:BothMethod")
    						.set_default("UseExternalSpec_FW_Judge");
    			add_param("RefCLK_MHz","double",&dRefCLK_MHz)
    						.set_comment("RefCLK_MHz")
    	//					.set_options("100:156.25")
    						.set_default("156.25");
    			add_param("RefCLK2_MHz","double",&dRefCLK2_MHz)
    						.set_comment("RefCLK2_MHz")
    	//					.set_options("100:156.25")
    						.set_default("156.25");
    			add_param("PrintLvl[0~8]","int",&iPrintLvl)
    						.set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
    						"0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
    	//					.set_options("0:1:3:4:7:8")
    						.set_default("3");

    }

    void execute(){

    	    //=============================================
    	    // Common definition of TM for offline flag,
    	    // d2s mode, debug mode, test suite name, etc.
    	    //=============================================
    	    H30_FailBin_Flag.init(0);
    	    static INT iOffline;
    	    static INT iCSR_check;
    	    static MACRO_LANE_SEL MacroLane_Sel;
    	    static MACRO_DOUBLE Alphagen_Result;
    	    static MACRO_DOUBLE FWAbist_Result;

    	    static LANE_DOUBLE Half_HVCC_Public;
    	    static LANE_DOUBLE DS_ErrorMessage;
    	    static MACRO_DOUBLE CS_ErrorMessage;
    	    static MACRO_DOUBLE Quarter_CS_HVCC_Public;

    	    //FIX NODE
    	    static LANE_DOUBLE CENTER_CHANNEL_POSITIVE_OUTPUT_n128;
    	    static LANE_DOUBLE CENTER_CHANNEL_POSITIVE_OUTPUT_127;
    	    static LANE_DOUBLE CENTER_CHANNEL_POSITIVE_OUTPUT_0;
    	    static LANE_DOUBLE CENTER_CHANNEL_NEGATIVE_OUTPUT_n128;
    	    static LANE_DOUBLE CENTER_CHANNEL_NEGATIVE_OUTPUT_127;
    	    static LANE_DOUBLE CENTER_CHANNEL_NEGATIVE_OUTPUT_0;
    	    static LANE_DOUBLE EDGE_CHANNEL_POSITIVE_OUTPUT_n128;
    	    static LANE_DOUBLE EDGE_CHANNEL_POSITIVE_OUTPUT_127;
    	    static LANE_DOUBLE EDGE_CHANNEL_POSITIVE_OUTPUT_0;
    	    static LANE_DOUBLE EDGE_CHANNEL_NEGATIVE_OUTPUT_n128;
    	    static LANE_DOUBLE EDGE_CHANNEL_NEGATIVE_OUTPUT_127;
    	    static LANE_DOUBLE EDGE_CHANNEL_NEGATIVE_OUTPUT_0;
    	    static LANE_DOUBLE MONITOR_CHANNEL_POSITIVE_OUTPUT_n159;
    	    static LANE_DOUBLE MONITOR_CHANNEL_POSITIVE_OUTPUT_159;
    	    static LANE_DOUBLE MONITOR_CHANNEL_POSITIVE_OUTPUT_0;
    	    static LANE_DOUBLE MONITOR_CHANNEL_NEGATIVE_OUTPUT_n159;
    	    static LANE_DOUBLE MONITOR_CHANNEL_NEGATIVE_OUTPUT_159;
    	    static LANE_DOUBLE MONITOR_CHANNEL_NEGATIVE_OUTPUT_0;

    	    //CALCULATE NODE
    	    static LANE_DOUBLE DSRX_RXDFE_CENTER_VTH_0;
    	    static LANE_DOUBLE DSRX_RXDFE_EDGE_VTH_0;
    	    static LANE_DOUBLE DSRX_RXDFE_MONITOR_VTH_0;
    	    static LANE_DOUBLE DSRX_RXDFE_CENTER_LSB_BF;
    	    static LANE_DOUBLE DSRX_RXDFE_EDGE_LSB_BF;
    	    static LANE_DOUBLE DSRX_RXDFE_MONITOR_LSB_BF;

    	    static bool PreJudge_Result;

    	    int iLifeclk2dig_sel_pin_api;

    	    //=============================================
    	    // Variables and MacroLane initialization
    	    //=============================================
    	    INT iDebugAnalog;
    	    stAlphagen sAlphagen = H30_Alphagen_Alphagen;

//    	    static STRING mPinList = "";
//    	    const char * sTestsuiteName = api->Get_current_test_name();
    	    string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
    		//CTheSoft.Flow.Test.GetCurrentTestName()
    	    string strTestsuiteName = sTestsuiteName;
//    	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
//    	    api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER, &m_TestNumber, THE_END);
    		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
    		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
    		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();
    	    //
    	    //		GET_SYSTEM_FLAG		("offline",&iOffline);
    	    //		GET_TESTSUITE_NAME	(sTestsuiteName);
    	    //		GET_USER_FLAG		("CSR_atomic_operation",&iCSR_check);
    	    //		GET_TESTFLOW_FLAG	("debug_analog",&iDebugAnalog);
    	    //		DOUBLE Temp;
    	    //		GET_USER_DOUBLE		("Ttemp",&Temp);
    	    hout.setLevel(iPrintLvl);
    	    hout.printsuitename(sTestsuiteName);
    	    Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList, mPinList);


    	    //		ON_FIRST_INVOCATION_BEGIN();

    	    uint iRefclk0_freqm100 = uint(dRefCLK_MHz * 100);
    	    uint iRefclk1_freqm100 = uint(dRefCLK2_MHz * 100);

    	    //		D2S_FRAMEWORK;
    	    //		GET_TEST_INFO;

    	    /**************Clear API and CSConfigBeforeCal***set proper API depending on applications and Release MCU*********/

    	    //Step1 and Step2: PowerUp and Reset && Config Ctle and do calibration, this step has been done before this test suite
    	    //Step3: Load Abist test firmware: H30V101_ABIST_Alphagen.bin
    	    LoadFirmwareToSram( MacroLane_Sel, FW_Alphagen_Bin, FW_Alphagen_Cycles);

    	    //Step4: Do FW judge, write Spec to SRAM first
    	    if ((sJudgementType == "UseExternalSpec_FW_Judge") || (sJudgementType == "BothMethod")) {

    	        WriteSingleSpecToSram( MacroLane_Sel, 0x1EF88, 15, 0x1EF8A, -15, 1);
    	        WriteSingleSpecToSram( MacroLane_Sel, 0x1EF8C, 4, 0x1EF8E, 1.45, 1000);
    	        WriteSingleSpecToSram( MacroLane_Sel, 0x1EF90, 4, 0x1EF92, 1.45, 1000);

    	    }

    	    //Step5: Config Alphagen test API.
    	    //		sprintf(label,"H30V101_Config_Alphagen_testAPI_%f_%f_",Vcoef,Temp);
    	    d2s::d2s_LABEL_BEGIN("H30V101_Config_Alphagen_testAPI_", Global_D2S_Mode);
    	    //		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    	    selectMacro_MB(MacroLane_Sel);
    	    //Configure refclk frequency, users can get the information at frequency plan
    	    //Config refclk and core clk same as
    	    //Config_RefClk_CoreClk(iRefclk0_freqm100, iRefclk1_freqm100);

    	    //Configure refclk frequency, users can get the information at frequency plan
    	    SRAM.CSAPIRegs.setrefclk0_freqm100_api(iRefclk0_freqm100).Write2DUT(1);
    	    SRAM.CSAPIRegs.setrefclk1_freqm100_api(iRefclk1_freqm100).Write2DUT(2);
    	    //Configure core_clk select
    	    SRAM.CSAPIRegs.setcore_clk_selext_pin_api(giCore_clk_selext_pin_api).Write2DUT(0);
    	    SRAM.CSAPIRegs.setcore_clk_sel_pin_api(giCore_clk_sel_pin_api).Write2DUT(0);
    	    SRAM.CSAPIRegs.setcoreclk_sel_en_api(0x1).Write2DUT(4);
    	    //		fr.d2s_LABEL_END();
    	    d2s::d2s_LABEL_END();

    	    //		sprintf(label,"H30V101_Config2_Alphagen_testAPI_%f_%f_",Vcoef,Temp);
    	    //		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    	    d2s::d2s_LABEL_BEGIN("H30V101_Config2_Alphagen_testAPI_", Global_D2S_Mode);
    	    for (size_t macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
    	        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
    	        selectMacro(MacroID);

    	        if (GlobalInitPattern.find("_Case01") != string::npos)
    	            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[0];
    	        else if (GlobalInitPattern.find("_Case02") != string::npos)
    	            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[1];
    	        else if (GlobalInitPattern.find("_Case03") != string::npos)
    	            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[2];
    	        else {
    	            //				cout << "Can't find valid init pattern !!! Please check pattern name!" << endl;
//    	            api->info_message("Can't find valid init pattern !!! Please check pattern name!");
    	            cout <<"Can't find valid init pattern !!! Please check pattern name!"<<endl;
    	            //				ERROR_EXIT(TM::ABORT_FLOW);
    	        }
    	        if (iLifeclk2dig_sel_pin_api != 1 && iLifeclk2dig_sel_pin_api != 0 && iLifeclk2dig_sel_pin_api != -1) {
    	            //				cout << "Invalid macro has been choose !!! Please check macro ID!" << endl;
//    	            api->info_message("Invalid macro has been choose !!! Please check macro ID!");
    	            cout <<"Invalid macro has been choose !!! Please check macro ID!"<<endl;
    	            //				ERROR_EXIT(TM::ABORT_FLOW);
    	        }

    	        SRAM.CSAPIRegs.setlifeclk2dig_sel_pin_api(iLifeclk2dig_sel_pin_api).Write2DUT(0, false);
    	    }

    	    selectMacro_MB(MacroLane_Sel);
    	    SRAM.ABISTAPIRegs.setalphagen_sweep_abist_api(0x1).Write2DUT(1);
    	    SRAM.ABISTAPIRegs.settest_mode_abist_api(1).Write2DUT(2);
    	    d2s::d2s_LABEL_END();
    	    //		fr.d2s_LABEL_END();

    	    //Step6.1: Release MCU
    	    ReleaseMCU( MacroLane_Sel);

    	    //Step6.2: Wait TOP_FSM_DONE_API
    	    EXPECT_RESULT Top_Fsm_Result;
    	    WaitDoneMacro( MacroLane_Sel, SRAM.TOPAPIRegs.REG_INFO.top_fsm_done_api(), 1, 100, 1, Top_Fsm_Result);

    	    //After MCU Done, read all regs
    	    //READ_ALL_CSR;

    	    // Step6.3: hold MCU in reset mode
    	    ResetMCU( MacroLane_Sel);

    	    //Step7:Clear Alphagen test API
    	    //        sprintf(label,"H30V101_Clear_Alphagen_testAPI_%f_%f_",Vcoef,Temp);
    	    //		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    	    d2s::d2s_LABEL_BEGIN( "H30V101_Clear_Alphagen_testAPI_", Global_D2S_Mode);
    	    selectMacro_MB(MacroLane_Sel);
    	    SRAM.ABISTAPIRegs.setalphagen_sweep_abist_api(0).Write2DUT(1);
    	    SRAM.ABISTAPIRegs.settest_mode_abist_api(0).Write2DUT(2);
    	    d2s::d2s_LABEL_END();
    	    //		fr.d2s_LABEL_END();

    	    //Step8: Read SRAM Results
    	    SEGMENT_READ_MACRO( MacroLane_Sel, SRAM.ABISTAPIRegs.REG_INFO.alphagen_sweep_status_abist_api(), Alphagen_Result);
    	    FW_ABIST_RESULT_READ( MacroLane_Sel, 0x1FCF8, FWAbist_Result);

    	    //The following code are for detail result dataloging
    	    FWAbist_PreJudge( MacroLane_Sel, Alphagen_Result, PreJudge_Result);

    	    FW_ABIST_READ_ErrorMessage( MacroLane_Sel, 0x1FCFA, 0x1, 0x1FD02, CS_ErrorMessage, DS_ErrorMessage);

    	    if ((PreJudge_Result == false) || (sJudgementType == "BothMethod") || (Global_D2S_Mode == 0)) {
    	        //Read back table 2-9 of userguide

    	        FW_ABIST_READ_HVCC( MacroLane_Sel, 0x1FD04, 0x2, 0x1FD14, Quarter_CS_HVCC_Public, Half_HVCC_Public);

    	        //Read back table 2-10 of userguide
    	        FW_ABIST_READ_LANEDOUBLE( MacroLane_Sel, 0x1EF94, 36, CENTER_CHANNEL_POSITIVE_OUTPUT_n128, Half_HVCC_Public);
    	        FW_ABIST_READ_LANEDOUBLE( MacroLane_Sel, 0x1EF96, 36, CENTER_CHANNEL_POSITIVE_OUTPUT_127, Half_HVCC_Public);
    	        FW_ABIST_READ_LANEDOUBLE( MacroLane_Sel, 0x1EF98, 36, CENTER_CHANNEL_POSITIVE_OUTPUT_0, Half_HVCC_Public);
    	        FW_ABIST_READ_LANEDOUBLE( MacroLane_Sel, 0x1EF9A, 36, CENTER_CHANNEL_NEGATIVE_OUTPUT_n128, Half_HVCC_Public);
    	        FW_ABIST_READ_LANEDOUBLE( MacroLane_Sel, 0x1EF9C, 36, CENTER_CHANNEL_NEGATIVE_OUTPUT_127, Half_HVCC_Public);
    	        FW_ABIST_READ_LANEDOUBLE( MacroLane_Sel, 0x1EF9E, 36, CENTER_CHANNEL_NEGATIVE_OUTPUT_0, Half_HVCC_Public);
    	        FW_ABIST_READ_LANEDOUBLE( MacroLane_Sel, 0x1EFA0, 36, EDGE_CHANNEL_POSITIVE_OUTPUT_n128, Half_HVCC_Public);
    	        FW_ABIST_READ_LANEDOUBLE( MacroLane_Sel, 0x1EFA2, 36, EDGE_CHANNEL_POSITIVE_OUTPUT_127, Half_HVCC_Public);
    	        FW_ABIST_READ_LANEDOUBLE( MacroLane_Sel, 0x1EFA4, 36, EDGE_CHANNEL_POSITIVE_OUTPUT_0, Half_HVCC_Public);
    	        FW_ABIST_READ_LANEDOUBLE( MacroLane_Sel, 0x1EFA6, 36, EDGE_CHANNEL_NEGATIVE_OUTPUT_n128, Half_HVCC_Public);
    	        FW_ABIST_READ_LANEDOUBLE( MacroLane_Sel, 0x1EFA8, 36, EDGE_CHANNEL_NEGATIVE_OUTPUT_127, Half_HVCC_Public);
    	        FW_ABIST_READ_LANEDOUBLE( MacroLane_Sel, 0x1EFAA, 36, EDGE_CHANNEL_NEGATIVE_OUTPUT_0, Half_HVCC_Public);
    	        FW_ABIST_READ_LANEDOUBLE( MacroLane_Sel, 0x1EFAC, 36, MONITOR_CHANNEL_POSITIVE_OUTPUT_n159, Half_HVCC_Public);
    	        FW_ABIST_READ_LANEDOUBLE( MacroLane_Sel, 0x1EFAE, 36, MONITOR_CHANNEL_POSITIVE_OUTPUT_159, Half_HVCC_Public);
    	        FW_ABIST_READ_LANEDOUBLE( MacroLane_Sel, 0x1EFB0, 36, MONITOR_CHANNEL_POSITIVE_OUTPUT_0, Half_HVCC_Public);
    	        FW_ABIST_READ_LANEDOUBLE( MacroLane_Sel, 0x1EFB2, 36, MONITOR_CHANNEL_NEGATIVE_OUTPUT_n159, Half_HVCC_Public);
    	        FW_ABIST_READ_LANEDOUBLE( MacroLane_Sel, 0x1EFB4, 36, MONITOR_CHANNEL_NEGATIVE_OUTPUT_159, Half_HVCC_Public);
    	        FW_ABIST_READ_LANEDOUBLE( MacroLane_Sel, 0x1EFB6, 36, MONITOR_CHANNEL_NEGATIVE_OUTPUT_0, Half_HVCC_Public);

    	        //Read back table 2-11 of userguide
    	        Alphagen_CALCULATION( MacroLane_Sel, CENTER_CHANNEL_POSITIVE_OUTPUT_0, CENTER_CHANNEL_NEGATIVE_OUTPUT_0, DSRX_RXDFE_CENTER_VTH_0, 1);
    	        Alphagen_CALCULATION( MacroLane_Sel, EDGE_CHANNEL_POSITIVE_OUTPUT_0, EDGE_CHANNEL_NEGATIVE_OUTPUT_0, DSRX_RXDFE_EDGE_VTH_0, 1);
    	        Alphagen_CALCULATION( MacroLane_Sel, MONITOR_CHANNEL_POSITIVE_OUTPUT_0, MONITOR_CHANNEL_NEGATIVE_OUTPUT_0, DSRX_RXDFE_MONITOR_VTH_0, 1);
    	        Alphagen_CALCULATION( MacroLane_Sel, CENTER_CHANNEL_POSITIVE_OUTPUT_127, CENTER_CHANNEL_NEGATIVE_OUTPUT_127, CENTER_CHANNEL_POSITIVE_OUTPUT_n128, CENTER_CHANNEL_NEGATIVE_OUTPUT_n128, 255, DSRX_RXDFE_CENTER_LSB_BF, 1000);
    	        Alphagen_CALCULATION( MacroLane_Sel, EDGE_CHANNEL_POSITIVE_OUTPUT_127, EDGE_CHANNEL_NEGATIVE_OUTPUT_127, EDGE_CHANNEL_POSITIVE_OUTPUT_n128, EDGE_CHANNEL_NEGATIVE_OUTPUT_n128, 255, DSRX_RXDFE_EDGE_LSB_BF, 1000);
    	        Alphagen_CALCULATION( MacroLane_Sel, MONITOR_CHANNEL_POSITIVE_OUTPUT_159, MONITOR_CHANNEL_NEGATIVE_OUTPUT_159, MONITOR_CHANNEL_POSITIVE_OUTPUT_n159, MONITOR_CHANNEL_NEGATIVE_OUTPUT_n159, 318, DSRX_RXDFE_MONITOR_LSB_BF, 1000);



    	        //			for(uint macroIndex=0; macroIndex < MacroLane_Sel.size();macroIndex++)
    	        //			{
    	        //				//Readback Sram result for EVB Corrlation purpose
    	        //				ostringstream  TestDatalogBegin, TestDatalogEnd;
    	        //				TestDatalogBegin<<"\n"<<"==========H30V101_Alphagen_FWTest_Start==========";
    	        ////				PUT_DATALOG(TestDatalogBegin.str());
    	        //
    	        //				ostringstream  TestDatalog;
    	        //				FWAbistHeader(MacroLane_Sel, macroIndex, HILINK_FIRMWARE_LABEL_DEFAULT, FW_Alphagen_Bin, "Alphagen", TestDatalog);
    	        //
    	        //				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1EF94, 0x1F0B3, TestDatalog); //DS Results
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
    	        //				TestDatalogEnd<<"\n"<<"==========H30V101_Alphagen_FWTest_End=========="<<endl;
    	        ////				PUT_DATALOG(TestDatalogEnd.str());
    	        //			}

    	    }

    	    //Debug info to compare with EVB limit setting SRAM value
    	    //        if(sJudgementType == "BothMethod")
    	    //        {
    	    //    		ostringstream SramDataLog;
    	    //    		for(UINT MacroIndex= 0; MacroIndex<MacroLane_Sel.size(); MacroIndex++)
    	    //    		{
    	    //        		UINT MacroID = MacroLane_Sel[MacroIndex].MacroID;
    	    //        		SRAM_READ(MacroID, 0x1EF88, 0x1EF90,SramDataLog, true);
    	    //    		}
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
    	    HiLink_PerMacro_Judge( MacroLane_Sel, "Alphagen_Test_Conclusion", limitl_conclusion, Alphagen_Result, limith_conclusion);
    	    HiLink_PerMacro_Judge( MacroLane_Sel, "CS_ErrorMessage", limitl_err_message, CS_ErrorMessage, limith_err_message);
    	    HiLink_PerLane_Judge( MacroLane_Sel, "DS_ErrorMessage", limitl_err_message, DS_ErrorMessage, limith_err_message);
    	    if ((sJudgementType == "BothMethod") || (PreJudge_Result == false)) {
    	        double limitl_quarter_cs_hvcc_public = -32767;
    	        double limith_quarter_cs_hvcc_public = 32768;
    	        double limitl_half_hvcc_public = -32767;
    	        double limith_half_hvcc_public = 32768;
    	        HiLink_PerMacro_Judge( MacroLane_Sel, "Quarter_CS_HVCC_Public", limitl_quarter_cs_hvcc_public, Quarter_CS_HVCC_Public, limith_quarter_cs_hvcc_public);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "Half_HVCC_Public", limitl_half_hvcc_public, Half_HVCC_Public, limith_half_hvcc_public);
    	        //			HiLink_PerMacro_Judge(MacroLane_Sel,"CS_ErrorMessage",CS_ErrorMessage);
    	        //			HiLink_PerLane_Judge(MacroLane_Sel, "DS_ErrorMessage", DS_ErrorMessage);

    	        // all node voltage
    	        double limitl_center_channel = -32767;
    	        double limith_center_channel = 32768;
    	        double limitl_edge_channel = -32767;
    	        double limith_edge_channel = 32768;
    	        double limitl_monitor_channel = -32767;
    	        double limith_monitor_channel = 32768;
    	        HiLink_PerLane_Judge( MacroLane_Sel, "CENTER_CHANNEL_POSITIVE_OUTPUT_n128", limitl_center_channel, CENTER_CHANNEL_POSITIVE_OUTPUT_n128, limith_center_channel);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "CENTER_CHANNEL_POSITIVE_OUTPUT_127", limitl_center_channel, CENTER_CHANNEL_POSITIVE_OUTPUT_127, limith_center_channel);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "CENTER_CHANNEL_POSITIVE_OUTPUT_0", limitl_center_channel, CENTER_CHANNEL_POSITIVE_OUTPUT_0, limith_center_channel);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "CENTER_CHANNEL_NEGATIVE_OUTPUT_n128", limitl_center_channel, CENTER_CHANNEL_NEGATIVE_OUTPUT_n128, limith_center_channel);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "CENTER_CHANNEL_NEGATIVE_OUTPUT_0", limitl_center_channel, CENTER_CHANNEL_NEGATIVE_OUTPUT_0, limith_center_channel);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "EDGE_CHANNEL_POSITIVE_OUTPUT_n128", limitl_edge_channel, EDGE_CHANNEL_POSITIVE_OUTPUT_n128, limith_edge_channel);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "EDGE_CHANNEL_POSITIVE_OUTPUT_127", limitl_edge_channel, EDGE_CHANNEL_POSITIVE_OUTPUT_127, limith_edge_channel);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "EDGE_CHANNEL_POSITIVE_OUTPUT_0", limitl_edge_channel, EDGE_CHANNEL_POSITIVE_OUTPUT_0, limith_edge_channel);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "EDGE_CHANNEL_NEGATIVE_OUTPUT_n128", limitl_edge_channel, EDGE_CHANNEL_NEGATIVE_OUTPUT_n128, limith_edge_channel);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "EDGE_CHANNEL_NEGATIVE_OUTPUT_127", limitl_edge_channel, EDGE_CHANNEL_NEGATIVE_OUTPUT_127, limith_edge_channel);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "EDGE_CHANNEL_NEGATIVE_OUTPUT_0", limitl_edge_channel, EDGE_CHANNEL_NEGATIVE_OUTPUT_0, limith_edge_channel);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "MONITOR_CHANNEL_POSITIVE_OUTPUT_n159", limitl_monitor_channel, MONITOR_CHANNEL_POSITIVE_OUTPUT_n159, limith_monitor_channel);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "MONITOR_CHANNEL_POSITIVE_OUTPUT_159", limitl_monitor_channel, MONITOR_CHANNEL_POSITIVE_OUTPUT_159, limith_monitor_channel);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "MONITOR_CHANNEL_POSITIVE_OUTPUT_0", limitl_monitor_channel, MONITOR_CHANNEL_POSITIVE_OUTPUT_0, limith_monitor_channel);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "MONITOR_CHANNEL_NEGATIVE_OUTPUT_n159", limitl_monitor_channel, MONITOR_CHANNEL_NEGATIVE_OUTPUT_n159, limith_monitor_channel);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "MONITOR_CHANNEL_NEGATIVE_OUTPUT_159", limitl_monitor_channel, MONITOR_CHANNEL_NEGATIVE_OUTPUT_159, limith_monitor_channel);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "MONITOR_CHANNEL_NEGATIVE_OUTPUT_0", limitl_monitor_channel, MONITOR_CHANNEL_NEGATIVE_OUTPUT_0, limith_monitor_channel);

    	        //all calbrate voltage
    	        double limitl_dsrx_rxdfe_vth = -15;
    	        double limith_dsrx_rxdfe_vth = 15;
    	        double limitl_dsrx_rxdfe_other = 1450;
    	        double limith_dsrx_rxdfe_other = 3000;
    	        HiLink_PerLane_Judge( MacroLane_Sel, "DSRX_RXDFE_CENTER_VTH_0", limitl_dsrx_rxdfe_vth, DSRX_RXDFE_CENTER_VTH_0, limith_dsrx_rxdfe_vth);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "DSRX_RXDFE_EDGE_VTH_0", limitl_dsrx_rxdfe_vth, DSRX_RXDFE_EDGE_VTH_0, limith_dsrx_rxdfe_vth);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "DSRX_RXDFE_MONITOR_VTH_0", limitl_dsrx_rxdfe_vth, DSRX_RXDFE_MONITOR_VTH_0, limith_dsrx_rxdfe_vth);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "DSRX_RXDFE_CENTER_LSB_BF", limitl_dsrx_rxdfe_other, DSRX_RXDFE_CENTER_LSB_BF, limith_dsrx_rxdfe_other);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "DSRX_RXDFE_EDGE_LSB_BF", limitl_dsrx_rxdfe_other, DSRX_RXDFE_EDGE_LSB_BF, limith_dsrx_rxdfe_other);
    	        HiLink_PerLane_Judge( MacroLane_Sel, "DSRX_RXDFE_MONITOR_LSB_BF", limitl_dsrx_rxdfe_other, DSRX_RXDFE_MONITOR_LSB_BF, limith_dsrx_rxdfe_other);
    	    }

    	    SetTestBin();
    }


};
REGISTER_TESTCLASS("Alphagen",Alphagen)


