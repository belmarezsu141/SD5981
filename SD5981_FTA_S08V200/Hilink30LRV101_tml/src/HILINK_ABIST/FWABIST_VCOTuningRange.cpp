//for test method API interfaces

#include <HILINK_ABIST/FWABIST_VCOTuningRange.h>

#include <Common_Func/HiLink30_Common_Func.h>

using namespace std;
class FWABIST_VCOTuningRange: public TestClass{
public:
	STRING				mHiLink30_MacroList;
	STRING				mPinList;
	DOUBLE				dRefCLK_MHz;
	DOUBLE				dRefCLK2_MHz;
	INT                 iRefclkBus;
	INT					iPrintLvl;
	STRING              sJudgementType;
    void init(){
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
		add_param("RefclkBus","int",&iRefclkBus)
					//.set_options("0:1:-1")
					.set_default("-1");
		add_param("PrintLvl[0~8]","int",&iPrintLvl)
					.set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
					"0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					//.set_options("0:1:3:4:7:8")
					.set_default("3");
    }
    void execute(){

		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
                H30_FailBin_Flag.init(0);
		static	INT			iOffline;
		static	INT 			iCSR_check;
		static  MACRO_LANE_SEL 		MacroLane_Sel;
		static  MACRO_DOUBLE	   	VCOTuningRange_Result;

		static MACRO_ARRAY_D            SS_REG_RESULT;
		static MACRO_ARRAY_D            CS_REG_RESULT;
		static LANE_ARRAY_D             DS_REG_RESULT;

		static MACRO_ARRAY_MAP          SS_REG_Node_Value;
		static MACRO_ARRAY_MAP          CS_REG_Node_Value;
		static LANE_ARRAY_MAP           DS_REG_Node_Value;

		static MACRO_ARRAY_D            SS_Calculate_Output;
		static MACRO_ARRAY_D            CS_Calculate_Output;
		static LANE_ARRAY_D             DS_Calculate_Output;

		static bool                     PreJudge_Result;


		//=============================================
		// Variables and MacroLane initialization
		//=============================================
		INT                   iDebugAnalog;
//		GET_SYSTEM_FLAG		("offline",&iOffline);
//		GET_TESTSUITE_NAME	(sTestsuiteName);
//		GET_USER_FLAG		("CSR_atomic_operation",&iCSR_check);
                    stFWABIST_VCOTuningRange sFWABIST_VCOTuningRange=H30_VCOTuningRange_FWABIST_VCOTuningRange; 
//                static STRING mPinList="";
//                const char * sTestsuiteName = api->Get_current_test_name();
                string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
                string strTestsuiteName = sTestsuiteName;
//                api->Get_test_values(strTestsuiteName.data(),THE_TESTNUMBER,&m_TestNumber,THE_END);
//     stFWABIST_VCOTuningRange H30_VCOTuningRange_FWABIST_VCOTuningRange           
//        	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
        		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
        		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
        		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel,mHiLink30_MacroList,mPinList);

		VCOTuningRange_TABLE_DEFINE& FWABIST_VCOTuningRange=VCOTuningRange_TABLE_DEFINE::getInstance();

		//todo need to optimize
		CUSTPARA			CUSTpara=default_CUSTPARA;
		CUSTpara.PllSel = -1;
		CUSTpara.Coreclk_sel=="disable";
		CUSTpara.GB_Enable = 0;

		SSPARA				SSpara=default_SSPARA;
		SSpara.RefclkMHz = dRefCLK_MHz;
		SSpara.RefclkMHz2 = dRefCLK2_MHz;
		SSpara.RefclkBus = iRefclkBus;
		SSpara.SDiv = 1;

		CSPARA	             CSpara=default_CSPARA;

//		ON_FIRST_INVOCATION_BEGIN();

		//UINT iRefclk0_freqm100 		    = uint(dRefCLK_MHz * 100);
		//UINT iRefclk1_freqm100 		    = uint(dRefCLK2_MHz * 100);

//		D2S_FRAMEWORK;
//		GET_TEST_INFO;

		/**************Cal SS using the Cal FW*********/

		//step1: Cal SS
		MACRO_INT 			mCS_Cal_MacroResult;
		MACRO_INT      		mCsCalVcoLockPerMacro;
		MACRO_INT 	 		mDS_Cal_MacroResult;

		mCS_Cal_MacroResult.init(0);
		mCsCalVcoLockPerMacro.init(0);
		mDS_Cal_MacroResult.init(0);
		STRING sCalibrationType="SS";
		string iFull_Cal_en=FullCalPara.FullCal;
		//=============================================
		// Full and bypass calibration
		//=============================================
		HiLink30_FW_CAL(MacroLane_Sel, CUSTpara, SSpara, CSpara, mCS_Cal_MacroResult, mCsCalVcoLockPerMacro ,mDS_Cal_MacroResult,sCalibrationType,iFull_Cal_en);
   
		//Step1: Ctle Pre Setting, set before this test suite
		//Step2: LoadFirmware to Sram
		LoadFirmwareToSram(MacroLane_Sel, VCOTuningRange_Bin,VCOTuningRange_Cycles);

#ifdef TestChip
			  FW_TASK("DCRT RAM,(pAHB)");
#else
//			  FW_TASK("DCRT RAM,(pJTAG)");
#endif
		//Step3: FW judge, write spec value fist
		if((sJudgementType == "UseExternalSpec_FW_Judge") || (sJudgementType == "BothMethod"))
		{
			WritePerMacroSpecToSram(MacroLane_Sel,FWABIST_VCOTuningRange);
			WriteSingleSpecToSram(MacroLane_Sel,0x1D04E, 200, 0x1D050,    0, 1);//high spec have 4 byte,the writePerMacro canot supprot,use the single spec write,by shaoxue 20170630
			WriteSingleSpecToSram(MacroLane_Sel,0x1D052, 167, 0x1D054, 2000, 1);
			WriteSingleSpecToSram(MacroLane_Sel,0x1D056, 109, 0x1D058, 3750, 1);
			WriteSingleSpecToSram(MacroLane_Sel,0x1D05A,   0, 0x1D05C,    0, 1);
			WriteSingleSpecToSram(MacroLane_Sel,0x1D08E, 200, 0x1D090,    0, 1);
			WriteSingleSpecToSram(MacroLane_Sel,0x1D092, 162, 0x1D094,    0,1);
			WriteSingleSpecToSram(MacroLane_Sel,0x1D096, 107, 0x1D098, 8125, 1);
			WriteSingleSpecToSram(MacroLane_Sel,0x1D09A,   0, 0x1D09C,    0, 1);
		}

		//READ_ALL_CSR;

		//Step5:set CS API to enable CS calibration(CS Config) //todo

		//Step6: Config VCOTuningRange test API.
		//step7: set pll0/pll1 divider
//		sprintf(label,"H30V101_Config_testAPI_%s_%f_%f_",TestSuiteName.c_str(),Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN("H30V101_Config_testAPI_", Global_D2S_Mode);

                if (SSpara.RefclkBus == -1)
		{
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

				selectMacro(MacroID);
				CS.clkRegs.SliceID(0).Broadcast(1);

				if(GlobalInitPattern.find("_Case01") != string::npos)
					SSpara.RefclkBus = HILINK_INFO[MacroID].RefclockChoose[0];
				else if(GlobalInitPattern.find("_Case02") != string::npos)
					SSpara.RefclkBus = HILINK_INFO[MacroID].RefclockChoose[1];
				else if(GlobalInitPattern.find("_Case03") != string::npos)
					SSpara.RefclkBus = HILINK_INFO[MacroID].RefclockChoose[2];
				else
					{
//						cout << "Can't find valid init pattern !!! Please check pattern name!" << endl;
                                                std::cout<<"Can't find valid init pattern !!! Please check pattern name!"<<std::endl;
//						ERROR_EXIT(TM::ABORT_FLOW);
					}
				if(SSpara.RefclkBus !=1 && SSpara.RefclkBus !=0 && SSpara.RefclkBus !=-1 )
					{
//						cout << "Invalid macro has been choose !!! Please check macro ID!" << endl;
                                                std::cout<<"Invalid macro has been choose !!! Please check macro ID!"<<std::endl;
//						ERROR_EXIT(TM::ABORT_FLOW);
					}
				SRAM.ABISTAPIRegs.setvco_band_freq_range_abist_api(0x1).Write2DUT(0);
				SRAM.ABISTAPIRegs.setsub0_fsm_abist_api(0x3).Write2DUT(6);

				CS.clkRegs.setpll1refclksel(SSpara.RefclkBus).Write2DUT(3);//Select reference clock source

				CS.clkRegs.setpll1vcodivna(0x1).Write2DUT(3);//PLL1 Na divider setting
				CS.clkRegs.setpll1vcodivka(0x0).Write2DUT(3);//PLL1 Ka divider setting
				CS.clkRegs.setpll1fbdivp(0x9).Write2DUT(3); //Part of PLL1 Nb divider setting
				CS.clkRegs.setpll1fbdivs(0x6).Write2DUT(3); //Part of PLL1 Nb divider setting
				CS.clkRegs.setpll1hsclkdiv(0x0).Write2DUT(4); //PLL1 Kb divider setting
				CS.clkRegs.setpll1refclkdiv(0x0).Write2DUT(3);//PLL1 M divider setting

				CS.clkRegs.setpll0refclksel(SSpara.RefclkBus).Write2DUT(0);//Select reference clock source
				CS.clkRegs.setpll0vcodivna(0x1).Write2DUT(0);//PLL0 Na divider setting
				CS.clkRegs.setpll0vcodivka(0x0).Write2DUT(0);//PLL0 Ka divider setting
				CS.clkRegs.setpll0fbdivp(0x9).Write2DUT(0); //Part of PLL0 Nb divider setting
				CS.clkRegs.setpll0fbdivs(0x6).Write2DUT(0); //Part of PLL0 Nb divider setting
				CS.clkRegs.setpll0hsclkdiv(0x0).Write2DUT(1); //PLL0 Kb divider setting
				CS.clkRegs.setpll0refclkdiv(0x0).Write2DUT(1);//PLL0 M divider setting
			}
		}
		else if (SSpara.RefclkBus == 0 or SSpara.RefclkBus == 1)
		{
			selectMacro_MB(MacroLane_Sel);

			SRAM.ABISTAPIRegs.setvco_band_freq_range_abist_api(0x1).Write2DUT(0);
			SRAM.ABISTAPIRegs.setsub0_fsm_abist_api(0x3).Write2DUT(6);

			CS.clkRegs.setpll1refclksel(SSpara.RefclkBus).Write2DUT(3);//Select reference clock source

			CS.clkRegs.setpll1vcodivna(0x1).Write2DUT(3);//PLL1 Na divider setting
			CS.clkRegs.setpll1vcodivka(0x0).Write2DUT(3);//PLL1 Ka divider setting
			CS.clkRegs.setpll1fbdivp(0x9).Write2DUT(3); //Part of PLL1 Nb divider setting
			CS.clkRegs.setpll1fbdivs(0x6).Write2DUT(3); //Part of PLL1 Nb divider setting
			CS.clkRegs.setpll1hsclkdiv(0x0).Write2DUT(4); //PLL1 Kb divider setting
			CS.clkRegs.setpll1refclkdiv(0x0).Write2DUT(3);//PLL1 M divider setting

			CS.clkRegs.setpll0refclksel(SSpara.RefclkBus).Write2DUT(0);//Select reference clock source
			CS.clkRegs.setpll0vcodivna(0x1).Write2DUT(0);//PLL0 Na divider setting
			CS.clkRegs.setpll0vcodivka(0x0).Write2DUT(0);//PLL0 Ka divider setting
			CS.clkRegs.setpll0fbdivp(0x9).Write2DUT(0); //Part of PLL0 Nb divider setting
			CS.clkRegs.setpll0fbdivs(0x6).Write2DUT(0); //Part of PLL0 Nb divider setting
			CS.clkRegs.setpll0hsclkdiv(0x0).Write2DUT(1); //PLL0 Kb divider setting
			CS.clkRegs.setpll0refclkdiv(0x0).Write2DUT(1);//PLL0 M divider setting
		}
		else
		{
//			cout<<"ERROR: RefClkBus SEL is Out of Range or Empty!"<<endl;
                        std::cout<<"ERROR: RefClkBus SEL is Out of Range or Empty!"<<std::endl;
//			ERROR_EXIT(TM::ABORT_FLOW);
		}


//		fr.d2s_LABEL_END();
                d2s::d2s_LABEL_END(); 

		CsFwCalibration(MacroLane_Sel, CUSTpara, SSpara, CSpara, mCS_Cal_MacroResult, mCsCalVcoLockPerMacro, iFull_Cal_en, 0);
		//CsFwCalibration read vco lock statues.

//		//Step8: Release MCU
//		ReleaseMCU(MacroLane_Sel);

//		//Step9: Wait TOP_FSM_DONE_API =1
//		EXPECT_RESULT  Top_Fsm_Result;
//		WaitDoneMacro(MacroLane_Sel,SRAM.TOPAPIRegs.REG_INFO.top_fsm_done_api(),1, 50, 100, Top_Fsm_Result);
//
//		//After MCU Done, read all regs
//		READ_ALL_CSR;
//
//		// Step10: hold MCU in reset mode
//        ResetMCU(MacroLane_Sel);

		//Step11:	Clear VCO TUNING test API. Simple-Mode
//		sprintf(label,"H30V101_Clear_FWABIST_testAPI_%s_%f_%f_",TestSuiteName.c_str(),Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
                d2s::d2s_LABEL_BEGIN("H30V101_Clear_FWABIST_testAPI_", Global_D2S_Mode);
		selectMacro_MB(MacroLane_Sel);
		SRAM.ABISTAPIRegs.setvco_band_freq_range_abist_api(0x0).Write2DUT(0);
		SRAM.ABISTAPIRegs.setsub0_fsm_abist_api(0x0).Write2DUT(6);
//		fr.d2s_LABEL_END();
                  d2s::d2s_LABEL_END(); 

		SEGMENT_READ_MACRO(MacroLane_Sel,SRAM.ABISTAPIRegs.REG_INFO.vco_band_freq_range_status_abist_api(),VCOTuningRange_Result); //todo,need get the fw judge result bit
		//The following code are for detail result dataloging
		FWAbist_PreJudge(MacroLane_Sel,VCOTuningRange_Result, PreJudge_Result);

        //Step12: Read SRAM Results
		if((PreJudge_Result == false) || (sJudgementType == "BothMethod") || (Global_D2S_Mode ==0))
			{

				//Read back table 2-10 in VCOTuningRange userguide
				FWABIST_VCOTuningRange.FWABIST_Registers_Map_Init(MacroLane_Sel,CS_REG_RESULT, CS_REG_Node_Value);

				//Process table 2-11 in VCOTuningRange user guide
				FWAbist_Calculate_Table_Processing(MacroLane_Sel,FWABIST_VCOTuningRange,SS_Calculate_Output, CS_Calculate_Output,DS_Calculate_Output,SS_REG_Node_Value, CS_REG_Node_Value, DS_REG_Node_Value);


				//Readback Sram result for EVB Correlation purpose

//				for(uint macroIndex=0; macroIndex < MacroLane_Sel.size();macroIndex++)
//				{
//					ostringstream  TestDatalogBegin, TestDatalogEnd;
//					TestDatalogBegin<<"\n"<<"==========H30V101LR_VCOTuningRange_FWTest_Start==========";
////					PUT_DATALOG(TestDatalogBegin.str());
//
//					    ostringstream  TestDatalog;
//						FWAbistHeader(MacroLane_Sel, macroIndex, HILINK_FIRMWARE_LABEL_DEFAULT, VCOTuningRange_Bin, "VCOTuningRange_LR", TestDatalog);
//
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1D0F0, 0x1D8EF, TestDatalog); //Tuning range test reuslt
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FCF8, 0x1FCF8, TestDatalog); //Error message
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FCFA, 0x1FD03, TestDatalog); //Error message
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FD04, 0x1FD15, TestDatalog); //CS and 8 DS,HVCC
//						SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1FDB6, 0x1FDC1, TestDatalog); //ABIST API
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
//					TestDatalogEnd<<"\n"<<"==========H30V101LR_VCOTuningRange_FWTest_End=========="<<endl;
////					PUT_DATALOG(TestDatalogEnd.str());
//				}
			}


#ifdef TestChip
			FW_TASK("DCRT TP,(pAHB)");
#else
//			FW_TASK("DCRT TP,(pJTAG)");
#endif


		//Debug info to compare with EVB limit setting
//        if(sJudgementType == "BothMethod")
//        {
//    		ostringstream SramDataLog;
//
//    		for(UINT MacroIndex= 0; MacroIndex<MacroLane_Sel.size(); MacroIndex++)
//    		{
//        		UINT MacroID = MacroLane_Sel[MacroIndex].MacroID;
//        		//Read back table 2-5 in VCO TUNING userguide
//        		SRAM_READ(MacroID, 0x1CE6E, 0x1D0AE, SramDataLog, true);
//    		}
//
//        }

//		ON_FIRST_INVOCATION_END();
		//=============================================
		// Datalog
		//=============================================
                double limitl_conclusion=1;
                double limith_conclusion=1;
		HiLink_PerMacro_Judge(MacroLane_Sel,"VCOTuningRange_Test_Conclusion",limitl_conclusion,VCOTuningRange_Result,limith_conclusion);

                if(sJudgementType == "BothMethod" || (PreJudge_Result == false))
		{
			//Judge table 2-5 according to VCOTuningRange user guide
			HiLink_PerMacroCSCalArrayD_Judge(MacroLane_Sel, FWABIST_VCOTuningRange, CS_Calculate_Output);
		}

                SetTestBin();

    }
};

REGISTER_TESTCLASS("FWABIST_VCOTuningRange",FWABIST_VCOTuningRange)

