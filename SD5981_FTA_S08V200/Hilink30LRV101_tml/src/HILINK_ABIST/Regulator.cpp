//for test method API interfaces

#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"

using namespace std;

//	virtual void run()
	 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	  // TM Purpose:                                                                                                                //
	  //                                                                                                                            //
	  //                                    The following code are all sub functions                                                //
	  //																		                                                  	  //
	  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//Only Values read from ADC need to be calculat with Quarter_CS_HVCC_Public factor
	void FW_ABIST_RESULT_READ_REGULATOR(const MACRO_LANE_SEL& MacroLane_Sel, INT Address, MACRO_DOUBLE& FWAbist_Result, MACRO_DOUBLE Quarter_CS_HVCC_Public)
	{
            d2s_JTAG& jtag = d2s_JTAG::Instance();

//		D2S_FRAMEWORK;
//        GET_TEST_INFO;

//		sprintf(label,"H30V101_SRAM_read_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
                d2s::d2s_LABEL_BEGIN( "H30V101_SRAM_read_", Global_D2S_Mode);
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			selectMacro(MacroID);

			ostringstream str;
			str <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<Address;
			jtag.read(Address>>1,str.str());

		}
		d2s::d2s_LABEL_END();

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

			ostringstream str;
			str <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<Address;
			hout(DETAIL)<<"Address: 0x"<<hex<<Address<<"   "<<"Data: 0x"<<hex<<(INT)jtag.getReadValue(str.str())[SiteID]<<endl;
			FWAbist_Result[SiteID][MacroID] =  (INT)jtag.getReadValue(str.str())[SiteID];
			FWAbist_Result[SiteID][MacroID] = (((INT)FWAbist_Result[SiteID][MacroID]& 0xff00)>>8) |(((INT)FWAbist_Result[SiteID][MacroID]& 0x00ff)<<8); //big edian
			FWAbist_Result[SiteID][MacroID] = FWAbist_Result[SiteID][MacroID] * Quarter_CS_HVCC_Public[SiteID][MacroID] * 4/1024.0;
		}
		FOREACH_ACTIVESITE_END
	}

	//For reg values NO need to be calculat with Quarter_CS_HVCC_Public factor
	void FW_ABIST_RESULT_READ_REGULATOR_No_Factor(const MACRO_LANE_SEL& MacroLane_Sel, INT Address, MACRO_DOUBLE& FWAbist_Result)
	{

             d2s_JTAG& jtag = d2s_JTAG::Instance();
//		D2S_FRAMEWORK;
//		GET_TEST_INFO;

            d2s::d2s_LABEL_BEGIN( "H30V101_SRAM_read_", Global_D2S_Mode);

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			selectMacro(MacroID);

			ostringstream str;
			str <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<Address;
			jtag.read(Address>>1,str.str());

		}
		d2s::d2s_LABEL_END();


//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

			ostringstream str;
			str <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<Address;
			hout(DETAIL)<<"Address: 0x"<<hex<<Address<<"   "<<"Data: 0x"<<hex<<(INT)jtag.getReadValue(str.str())[SiteID]<<endl;
			FWAbist_Result[SiteID][MacroID] =  (INT)jtag.getReadValue(str.str())[SiteID];
			FWAbist_Result[SiteID][MacroID] = (((INT)FWAbist_Result[SiteID][MacroID]& 0xff00)>>8) |(((INT)FWAbist_Result[SiteID][MacroID]& 0x00ff)<<8); //big edian
		}
		FOREACH_ACTIVESITE_END
	}


	//If CS node code Fail, then judge whether node voltage pass, if voltage PASS, then CS_code should be judge as pass, so hard_codeing 9.99999  for CS mode
	//If CS node code Fail  and node voltage fail, then this test fail

//	void FW_ABIST_RESULT_READ_REGULATOR_No_Factor_Result_Convert(const MACRO_LANE_SEL& MacroLane_Sel,MACRO_DOUBLE& NodeCode, MACRO_DOUBLE& NodeVolt, string sJudgeNameInTable_NodeCode, string sJudgeNameInTable_NodeVolt)
//	{
//
//	     STRING sTestsuiteName;
//	     GET_TESTSUITE_NAME(sTestsuiteName);
//
//	     TMLimits::LimitInfo strLimitInfo_NodeCode;
//	     strLimitInfo_NodeCode = tmLimits.getLimit(sTestsuiteName,sJudgeNameInTable_NodeCode);
//
//	     TMLimits::LimitInfo strLimitInfo_NodeVolt;
//	     strLimitInfo_NodeVolt = tmLimits.getLimit(sTestsuiteName,sJudgeNameInTable_NodeVolt);
//
//	     string OPL_NodeCode, OPH_NodeCode, sTestName_NodeCode, sLimitUnit_NodeCode;
//	     double LowLimit_NodeCode, HiLimit_NodeCode;
//	     LowLimit_NodeCode =strLimitInfo_NodeCode.Lsl;
//	     HiLimit_NodeCode =strLimitInfo_NodeCode.Usl;
//	     OPL_NodeCode =strLimitInfo_NodeCode.LslTyp;
//	     OPH_NodeCode =strLimitInfo_NodeCode.UslTyp;
//	     sTestName_NodeCode =strLimitInfo_NodeCode.TestName;
//	     sLimitUnit_NodeCode =strLimitInfo_NodeCode.Units;
//
//	     string OPL_NodeVolt, OPH_NodeVolt, sTestName_NodeVolt, sLimitUnit_NodeVolt;
//	     double LowLimit_NodeVolt, HiLimit_NodeVolt;
//	     LowLimit_NodeVolt =strLimitInfo_NodeVolt.Lsl;
//	     HiLimit_NodeVolt =strLimitInfo_NodeVolt.Usl;
//	     OPL_NodeVolt =strLimitInfo_NodeVolt.LslTyp;
//	     OPH_NodeVolt =strLimitInfo_NodeVolt.UslTyp;
//	     sTestName_NodeVolt =strLimitInfo_NodeVolt.TestName;
//	     sLimitUnit_NodeVolt =strLimitInfo_NodeVolt.Units;
//
//
//
//	    FOREACH_ACTIVE_SITE(api) {
//            unsigned int SiteID = api->Get_active_site();
//
//		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
//		{
//			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//			string sLocalLimitCompareResult_NodeCode= LocalLimitCompare(OPL_NodeCode,LowLimit_NodeCode,OPH_NodeCode,HiLimit_NodeCode,NodeCode[SiteID][MacroID]);
//			string sLocalLimitCompareResult_NodeVolt= LocalLimitCompare(OPL_NodeVolt,LowLimit_NodeVolt,OPH_NodeVolt,HiLimit_NodeVolt,NodeVolt[SiteID][MacroID]);
//
//            if ((sLocalLimitCompareResult_NodeCode=="FAILED") && (sLocalLimitCompareResult_NodeVolt=="PASSED"))
//            {
//       	       NodeCode[SiteID][MacroID] = 9.999999;
//            }
//		 }
//
//
//                    }
//
//
//	}

	//For reg values NO need to be calculat with Half_HVCC_Public factor
	void FW_ABIST_READ_LANEDOUBLE_REGULATOR(const MACRO_LANE_SEL& MacroLane_Sel, INT DSStartAddress, INT DSIncreaseStep, LANE_DOUBLE& DsInfo)
	{
                  d2s_JTAG& jtag = d2s_JTAG::Instance();

//		D2S_FRAMEWORK;
//		GET_TEST_INFO;

//		sprintf(label,"READ_DS_LANEDOUBLE_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
                d2s::d2s_LABEL_BEGIN( "READ_DS_LANEDOUBLE_", Global_D2S_Mode);
		for(uint midx=0;midx<MacroLane_Sel.size();midx++){
			uint MacroID=MacroLane_Sel[midx].MacroID;
			const vector<uint>& vLane=MacroLane_Sel[midx].vLane;
			ostringstream str;
			str<<"_M"<<MacroID;

			selectMacro(MacroID);

			for(uint lidx=0;lidx<vLane.size();lidx++){
				uint LaneID=vLane[lidx];
				ostringstream str;
				uint addr= DSStartAddress + LaneID*DSIncreaseStep;
				str<<"ReadDS_LANE_DOUBLE_M"<<MacroID<<"_L"<<LaneID<<"_Address_0x" <<hex<<addr;

				jtag.read(addr>>1,str.str());
			}
		}
		d2s::d2s_LABEL_END();


		for(uint midx=0;midx<MacroLane_Sel.size();midx++){
			uint MacroID=MacroLane_Sel[midx].MacroID;
			const vector<uint>& vLane=MacroLane_Sel[midx].vLane;
			ostringstream str;
			str<<"_M"<<MacroID;

			for(uint lidx=0;lidx<vLane.size();lidx++){
				uint LaneID=vLane[lidx];
				ostringstream str;
				uint addr= DSStartAddress + LaneID*DSIncreaseStep;
				str<<"ReadDS_LANE_DOUBLE_M"<<MacroID<<"_L"<<LaneID<<"_Address_0x" <<hex<<addr;

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
				FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

				DsInfo[SiteID][MacroID][LaneID]=jtag.getReadValue(str.str())[SiteID];
				DsInfo[SiteID][MacroID][LaneID] = (((INT)DsInfo[SiteID][MacroID][LaneID]& 0xff00)>>8) | (((INT)DsInfo[SiteID][MacroID][LaneID]& 0x00ff)<<8) ; //big edian
				hout(DETAIL)<<"Read_DS_Lane_Double: Macro: "<<MacroID<<" LaneID: "<<LaneID<<" Value: "<< DsInfo[SiteID][MacroID][LaneID]<<endl;
				FOREACH_ACTIVESITE_END
			}
		}
	}

	void FW_ABIST_READ_LANEDOUBLE_REGULATOR_VOLTAGE(const MACRO_LANE_SEL& MacroLane_Sel, INT DSStartAddress, INT DSIncreaseStep, LANE_DOUBLE& DsInfo,LANE_DOUBLE Half_HVCC_Public)
	{
        d2s_JTAG& jtag = d2s_JTAG::Instance();
//		D2S_FRAMEWORK;
//		GET_TEST_INFO;

//		sprintf(label,"READ_DS_LANEDOUBLE_%s_%f_%f_",TestSuiteName.c_str(),Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
                d2s::d2s_LABEL_BEGIN( "READ_DS_LANEDOUBLE_", Global_D2S_Mode);
		for(uint midx=0;midx<MacroLane_Sel.size();midx++){
			uint MacroID=MacroLane_Sel[midx].MacroID;
			const vector<uint>& vLane=MacroLane_Sel[midx].vLane;
			ostringstream str;
			str<<"_M"<<MacroID;

			selectMacro(MacroID);

			for(uint lidx=0;lidx<vLane.size();lidx++){
				uint LaneID=vLane[lidx];
				ostringstream str;
				uint addr= DSStartAddress + LaneID*DSIncreaseStep;
				str<<"ReadDS_LANE_DOUBLE_M"<<MacroID<<"_L"<<LaneID<<"_Address_0x" <<hex<<addr;

				jtag.read(addr>>1,str.str());
			}
		}

		d2s::d2s_LABEL_END();

		for(uint midx=0;midx<MacroLane_Sel.size();midx++){
			uint MacroID=MacroLane_Sel[midx].MacroID;
			const vector<uint>& vLane=MacroLane_Sel[midx].vLane;
			ostringstream str;
			str<<"_M"<<MacroID;

			for(uint lidx=0;lidx<vLane.size();lidx++){
				uint LaneID=vLane[lidx];
				ostringstream str;
				uint addr= DSStartAddress + LaneID*DSIncreaseStep;
				str<<"ReadDS_LANE_DOUBLE_M"<<MacroID<<"_L"<<LaneID<<"_Address_0x" <<hex<<addr;

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
				FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

				DsInfo[SiteID][MacroID][LaneID]=jtag.getReadValue(str.str())[SiteID];
				DsInfo[SiteID][MacroID][LaneID] = (((INT)DsInfo[SiteID][MacroID][LaneID]& 0xff00)>>8) | (((INT)DsInfo[SiteID][MacroID][LaneID]& 0x00ff)<<8) ; //big edian
				if(0x1E046==DSStartAddress)//for regulator guide v 0.1.0//todo
				{
					DsInfo[SiteID][MacroID][LaneID] = 1.0 * DsInfo[SiteID][MacroID][LaneID] * Half_HVCC_Public[SiteID][MacroID][LaneID]* 2/1024.0;
				}
				else
				{
					DsInfo[SiteID][MacroID][LaneID] = (double)((uint)(1.5 * DsInfo[SiteID][MacroID][LaneID] ))* Half_HVCC_Public[SiteID][MacroID][LaneID]* 2/1024.0;
				}
				hout(DETAIL)<<"Read_DS_Lane_Double: Macro: "<<MacroID<<" LaneID: "<<LaneID<<" Value: "<< DsInfo[SiteID][MacroID][LaneID]<<endl;
				FOREACH_ACTIVESITE_END
			}
		}
	}

class Regulator: public TestClass{
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
		void execute(){

		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
                H30_FailBin_Flag.init(0);
		static	INT			iOffline;
		static	INT 			iCSR_check;
		static  MACRO_LANE_SEL          MacroLane_Sel;
		static  MACRO_DOUBLE            Regulator_Result;
		static LANE_DOUBLE              Half_HVCC_Public;
		static LANE_DOUBLE              DS_ErrorMessage;
		static MACRO_DOUBLE             CS_ErrorMessage;
		static MACRO_DOUBLE             Quarter_CS_HVCC_Public;

		static MACRO_DOUBLE             PLL0VREGPLLSEL;
		static MACRO_DOUBLE             PLL0VREGDLFSEL;
		static MACRO_DOUBLE             PLL0VREGVCODIVSEL;
		static MACRO_DOUBLE             PLL0VREGPLL_VREGHALF;
		static MACRO_DOUBLE             PLL0VREGDLF_VREGHALF;
		static MACRO_DOUBLE             PLL0VREGVCODIV_VREGHALF;
		static MACRO_DOUBLE             PLL1VREGPLLSEL;
		static MACRO_DOUBLE             PLL1VREGDLFSEL;
		static MACRO_DOUBLE             PLL1VREGVCODIVSEL;
		static MACRO_DOUBLE             PLL1VREGPLL_VREGHALF;
		static MACRO_DOUBLE             PLL1VREGDLF_VREGHALF;
		static MACRO_DOUBLE             PLL1VREGVCODIV_VREGHALF;
		static LANE_DOUBLE              VREGCLKLVL_CODE;
		static LANE_DOUBLE              VREGDATALVL_CODE;
		static LANE_DOUBLE              TXPREDRVREGLVL_CODE;
		static LANE_DOUBLE              TXDRVREGLVL_CODE;
		static LANE_DOUBLE              VREGLVL_CODE;
		static LANE_DOUBLE              CTLEVREGVREFSEL_CODE;
		static LANE_DOUBLE              VREGDATA_VREG_2_3;
		static LANE_DOUBLE              VREGCLK_VREG_2_3_3;
		static LANE_DOUBLE              VREG_PREDRV_2_3;
		static LANE_DOUBLE              VREG_DRV_2_3;
		static LANE_DOUBLE              VREG_VREG_2_3;
		static LANE_DOUBLE              CTLE_VREG_VOUT_1_7;
		static bool                     PreJudge_Result;

		INT iLifeclk2dig_sel_pin_api;
		//=============================================
		// Variables and MacroLane initialization
		//=============================================
		INT                   iDebugAnalog;
//		GET_SYSTEM_FLAG		("offline",&iOffline);
//		GET_TESTSUITE_NAME	(sTestsuiteName);
//		GET_USER_FLAG		("CSR_atomic_operation",&iCSR_check);
//		GET_TESTFLOW_FLAG	("debug_analog",&iDebugAnalog);
//extern stRegulator H30_Regulator_Regulator; 
                 stRegulator sRegulator=H30_Regulator_Regulator; 
                
//                static STRING mPinList="";
//                const char * sTestsuiteName = api->Get_current_test_name();
                string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
                string strTestsuiteName = sTestsuiteName;
//                api->Get_test_values(strTestsuiteName.data(),THE_TESTNUMBER,&m_TestNumber,THE_END);
                
//        	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
        		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
        		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
        		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

        	    hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel,mHiLink30_MacroList,mPinList);


//		ON_FIRST_INVOCATION_BEGIN();

		uint iRefclk0_freqm100 		    = uint(dRefCLK_MHz * 100);
		uint iRefclk1_freqm100 		    = uint(dRefCLK2_MHz * 100);

//		D2S_FRAMEWORK;
//		GET_TEST_INFO;
		/**************Clear API and CSConfigBeforeCal***set proper API depending on applications and Release MCU*********/
		//Step1 and Step2: PowerUp and Reset && Config Ctle and do calibration, this step has been done before this test suite
		//Step3: Load Abist test firmware: H30V101_ABIST_Regulator.bin
		LoadFirmwareToSram(MacroLane_Sel, Regulator_Bin,Regulator_Cycles);

		//Step4: FW Judge, Write Spec to Sram first
		if((sJudgementType == "UseExternalSpec_FW_Judge") || (sJudgementType == "BothMethod"))
		{

			WriteSingleSpecToSram(MacroLane_Sel,0x1DFF4, 900, 0x1DFF6, 475, 1);
			WriteSingleSpecToSram(MacroLane_Sel,0x1DFF0, 30, 0x1DFF2, 0, 1);
			WriteSingleSpecToSram(MacroLane_Sel,0x1DFF8, 30, 0x1DFFA, 0, 1);
			WriteSingleSpecToSram(MacroLane_Sel,0x1DFFC, 6, 0x1DFFE, 0, 1);
			WriteSingleSpecToSram(MacroLane_Sel,0x1E000, 1200, 0x1E002, 1200, 1);
			WriteSingleSpecToSram(MacroLane_Sel,0x1E004, 1200, 0x1E006, 1200, 1);
			WriteSingleSpecToSram(MacroLane_Sel,0x1E008, 1200, 0x1E00A, 1200, 1);
			WriteSingleSpecToSram(MacroLane_Sel,0x1E00C, 1200, 0x1E00E, 1200, 1);
			WriteSingleSpecToSram(MacroLane_Sel,0x1E010, 1200, 0x1E012, 1200, 1);
			WriteSingleSpecToSram(MacroLane_Sel,0x1E014, 1100, 0x1E016, 950, 1);//20211207
		}

		//Step5: Config Regulator test API.
//		sprintf(label,"H30V101_Config_Regulator_testAPI_%f_%f_",Vcoef,Temp);
                d2s::d2s_LABEL_BEGIN( "H30V101_Config_Regulator_testAPI_", Global_D2S_Mode);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
			selectMacro_MB(MacroLane_Sel);
			//Configure refclk frequency, users can get the information at frequency plan
			//Configure core_clk select
	//		Config_RefClk_CoreClk(iRefclk0_freqm100, iRefclk1_freqm100);
			SRAM.CSAPIRegs.setrefclk0_freqm100_api(iRefclk0_freqm100).Write2DUT(1);
			SRAM.CSAPIRegs.setrefclk1_freqm100_api(iRefclk1_freqm100).Write2DUT(2);
			//Configure core_clk select
			SRAM.CSAPIRegs.setcore_clk_selext_pin_api(giCore_clk_selext_pin_api).Write2DUT(0);//CSR Broadcast Bug
			SRAM.CSAPIRegs.setcore_clk_sel_pin_api(giCore_clk_sel_pin_api).Write2DUT(0);
			SRAM.CSAPIRegs.setcoreclk_sel_en_api(0x1).Write2DUT(4);

		d2s::d2s_LABEL_END();

//		sprintf(label,"H30V101_Config2_Regulator_testAPI_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
                d2s::d2s_LABEL_BEGIN( "H30V101_Config2_Regulator_testAPI_", Global_D2S_Mode);
			for (size_t macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				selectMacro(MacroID);

				if(GlobalInitPattern.find("_Case01") != string::npos)
					iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[0];
				else if(GlobalInitPattern.find("_Case02") != string::npos)
					iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[1];
				else if(GlobalInitPattern.find("_Case03") != string::npos)
					iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[2];
				else
				{
//					cout << "Can't find valid init pattern !!! Please check pattern name!" << endl;
					cout <<"Can't find valid init pattern !!! Please check pattern name!"<<endl;
//                                        api->info_message("Can't find valid init pattern !!! Please check pattern name!");
//					ERROR_EXIT(TM::ABORT_FLOW);
				}
				if(iLifeclk2dig_sel_pin_api !=1 && iLifeclk2dig_sel_pin_api !=0 && iLifeclk2dig_sel_pin_api != -1)
				{
//					cout << "Invalid macro has been choose !!! Please check macro ID!" << endl;
					cout <<"Invalid macro has been choose !!! Please check macro ID!"<<endl;
//                                        api->info_message("Invalid macro has been choose !!! Please check macro ID!");
//					ERROR_EXIT(TM::ABORT_FLOW);
				}

				SRAM.CSAPIRegs.setlifeclk2dig_sel_pin_api(iLifeclk2dig_sel_pin_api).Write2DUT(0,false);
			}

			selectMacro_MB(MacroLane_Sel);
			SRAM.ABISTAPIRegs.setregulator_sweep_abist_api(0x1).Write2DUT(1);
			SRAM.ABISTAPIRegs.settest_mode_abist_api(1).Write2DUT(2);

		d2s::d2s_LABEL_END();

		//Step6.1: Release MCU
		ReleaseMCU(MacroLane_Sel);

		//Step6.2: Wait TOP_FSM_DONE_API
		EXPECT_RESULT  Top_Fsm_Result;

		WaitDoneMacro(MacroLane_Sel,SRAM.TOPAPIRegs.REG_INFO.top_fsm_done_api(),1, 100, 1, Top_Fsm_Result);

        //After MCU Done, read all regs
		//READ_ALL_CSR;

		// Step6.3: hold MCU in reset mode
                ResetMCU(MacroLane_Sel);

		//Step7:Clear Regulator test API

                d2s::d2s_LABEL_BEGIN( "H30V101_Clear_Regulator_testAPI_", Global_D2S_Mode);
			selectMacro_MB(MacroLane_Sel);
			SRAM.ABISTAPIRegs.setregulator_sweep_abist_api(0).Write2DUT(1);
			SRAM.ABISTAPIRegs.settest_mode_abist_api(0).Write2DUT(2);
		d2s::d2s_LABEL_END();

		//Step8: Read SRAM Results
		SEGMENT_READ_MACRO(MacroLane_Sel,SRAM.ABISTAPIRegs.REG_INFO.regulator_sweep_status_abist_api(),Regulator_Result);
		//The following code are for detail result dataloging
                FWAbist_PreJudge(MacroLane_Sel,Regulator_Result, PreJudge_Result);
                
                FW_ABIST_READ_ErrorMessage(MacroLane_Sel, 0x1FCFA, 0x1, 0x1FD02, CS_ErrorMessage, DS_ErrorMessage);
                
        if((sJudgementType == "BothMethod") || (PreJudge_Result == false) ||(Global_D2S_Mode ==0))
		{
			//Read back table 2-9 in  user guide

			FW_ABIST_READ_HVCC(MacroLane_Sel, 0x1FD04, 0x2, 0x1FD14, Quarter_CS_HVCC_Public, Half_HVCC_Public);

			FW_ABIST_RESULT_READ_REGULATOR_No_Factor(MacroLane_Sel,0x1E018, PLL0VREGPLLSEL);
			FW_ABIST_RESULT_READ_REGULATOR_No_Factor(MacroLane_Sel,0x1E01A, PLL0VREGDLFSEL);
			FW_ABIST_RESULT_READ_REGULATOR_No_Factor(MacroLane_Sel,0x1E01C, PLL0VREGVCODIVSEL);

			FW_ABIST_RESULT_READ_REGULATOR(MacroLane_Sel,0x1E024, PLL0VREGPLL_VREGHALF, Quarter_CS_HVCC_Public);
			FW_ABIST_RESULT_READ_REGULATOR(MacroLane_Sel,0x1E026, PLL0VREGDLF_VREGHALF, Quarter_CS_HVCC_Public);
			FW_ABIST_RESULT_READ_REGULATOR(MacroLane_Sel,0x1E028, PLL0VREGVCODIV_VREGHALF, Quarter_CS_HVCC_Public);

			FW_ABIST_RESULT_READ_REGULATOR_No_Factor(MacroLane_Sel,0x1E01E, PLL1VREGPLLSEL);
			FW_ABIST_RESULT_READ_REGULATOR_No_Factor(MacroLane_Sel,0x1E020, PLL1VREGDLFSEL);
			FW_ABIST_RESULT_READ_REGULATOR_No_Factor(MacroLane_Sel,0x1E022, PLL1VREGVCODIVSEL);

			FW_ABIST_RESULT_READ_REGULATOR(MacroLane_Sel,0x1E02A, PLL1VREGPLL_VREGHALF, Quarter_CS_HVCC_Public);
			FW_ABIST_RESULT_READ_REGULATOR(MacroLane_Sel,0x1E02C, PLL1VREGDLF_VREGHALF, Quarter_CS_HVCC_Public);
			FW_ABIST_RESULT_READ_REGULATOR(MacroLane_Sel,0x1E02E, PLL1VREGVCODIV_VREGHALF, Quarter_CS_HVCC_Public);

			FW_ABIST_READ_LANEDOUBLE_REGULATOR(MacroLane_Sel, 0x1E030, 24, VREGDATALVL_CODE);
			FW_ABIST_READ_LANEDOUBLE_REGULATOR(MacroLane_Sel, 0x1E032, 24, VREGCLKLVL_CODE);
			FW_ABIST_READ_LANEDOUBLE_REGULATOR(MacroLane_Sel, 0x1E034, 24, TXPREDRVREGLVL_CODE);
			FW_ABIST_READ_LANEDOUBLE_REGULATOR(MacroLane_Sel, 0x1E036, 24, TXDRVREGLVL_CODE);
			FW_ABIST_READ_LANEDOUBLE_REGULATOR(MacroLane_Sel, 0x1E038, 24, VREGLVL_CODE);
			FW_ABIST_READ_LANEDOUBLE_REGULATOR(MacroLane_Sel, 0x1E03A, 24, CTLEVREGVREFSEL_CODE);
					
			FW_ABIST_READ_LANEDOUBLE_REGULATOR_VOLTAGE(MacroLane_Sel, 0x1E03C, 24, VREGDATA_VREG_2_3,Half_HVCC_Public);
			FW_ABIST_READ_LANEDOUBLE_REGULATOR_VOLTAGE(MacroLane_Sel, 0x1E03E, 24, VREGCLK_VREG_2_3_3,Half_HVCC_Public);
			FW_ABIST_READ_LANEDOUBLE_REGULATOR_VOLTAGE(MacroLane_Sel, 0x1E040, 24, VREG_PREDRV_2_3,Half_HVCC_Public);
			FW_ABIST_READ_LANEDOUBLE_REGULATOR_VOLTAGE(MacroLane_Sel, 0x1E042, 24, VREG_DRV_2_3,Half_HVCC_Public);
			FW_ABIST_READ_LANEDOUBLE_REGULATOR_VOLTAGE(MacroLane_Sel, 0x1E044, 24, VREG_VREG_2_3,Half_HVCC_Public);
			FW_ABIST_READ_LANEDOUBLE_REGULATOR_VOLTAGE(MacroLane_Sel, 0x1E046, 24, CTLE_VREG_VOUT_1_7,Half_HVCC_Public);
			
//			for(uint macroIndex=0; macroIndex < MacroLane_Sel.size();macroIndex++)
//			{
//				//Readback Sram result for EVB Corrlation purpose
//				ostringstream  TestDatalogBegin, TestDatalogEnd;
//				TestDatalogBegin<<"\n"<<"==========H30V101_Regulator_FWTest_Start==========";
////				PUT_DATALOG(TestDatalogBegin.str());
//
//				ostringstream  TestDatalog;
//				FWAbistHeader(MacroLane_Sel, macroIndex, HILINK_FIRMWARE_LABEL_DEFAULT, Regulator_Bin, "Regulator", TestDatalog);
//
//				SRAM_READ(MacroLane_Sel[macroIndex].MacroID, 0x1E018, 0x1E0EF, TestDatalog); //DS Results
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
//				TestDatalogEnd<<"\n"<<"==========H30V101_Regulator_FWTest_End=========="<<endl;
////				PUT_DATALOG(TestDatalogEnd.str());
//
//			}

		}

//        if(sJudgementType == "BothMethod")
//        {
//    		//debug info to compare with EVB output
//        	//table 2-7
//    		ostringstream SramDataLog;
//
//    		for(UINT MacroIndex= 0; MacroIndex<MacroLane_Sel.size(); MacroIndex++)
//    		{
//        		UINT MacroID = MacroLane_Sel[MacroIndex].MacroID;
//        		SRAM_READ(MacroID, 0x1DFF0, 0x1E016,SramDataLog, true);
//    		}
//        }
//		ON_FIRST_INVOCATION_END();
		//=============================================
		// Datalog
		//=============================================
                double limitl_conclusion=1;
                double limith_conclusion=1;
                double limitl_err_message=0;
                double limith_err_message=0;
                
		HiLink_PerMacro_Judge(MacroLane_Sel,"Regulator_Test_Conclusion",limitl_conclusion,Regulator_Result,limith_conclusion);
                HiLink_PerMacro_Judge(MacroLane_Sel,"CS_ErrorMessage",limitl_err_message,CS_ErrorMessage,limith_err_message);
	        HiLink_PerLane_Judge(MacroLane_Sel, "DS_ErrorMessage",limitl_err_message,DS_ErrorMessage,limith_err_message);
                
                if((sJudgementType == "BothMethod") || (PreJudge_Result == false))
		{
//			HiLink_PerMacro_Judge(MacroLane_Sel,"CS_ErrorMessage",LimitL,CS_ErrorMessage,LimitH);
//			HiLink_PerLane_Judge(MacroLane_Sel, "DS_ErrorMessage",LimitL, DS_ErrorMessage,LimitH);
                    
                        double limitl_half_hvcc_public=-32767;
                        double limith_half_hvcc_public=32768;
                        double limitl_quarter_cs_hvcc_public=-32767;
                        double limith_quarter_cs_hvcc_public=32768; 
			HiLink_PerLane_Judge(MacroLane_Sel, "Half_HVCC_Public", limitl_half_hvcc_public,Half_HVCC_Public,limith_half_hvcc_public);
			HiLink_PerMacro_Judge(MacroLane_Sel,"Quarter_CS_HVCC_Public",limitl_quarter_cs_hvcc_public,Quarter_CS_HVCC_Public,limith_quarter_cs_hvcc_public);

                        //For CS, only under condition that BOTH code and voltage all FAIL, then test item Fail, otherwise Pass.
			HiLink_PerMacro_Judge_Regulator(MacroLane_Sel,PLL0VREGPLLSEL, PLL0VREGPLL_VREGHALF, "PLL0VREGPLLSEL", "PLL0VREGPLL_VREGHALF");
			HiLink_PerMacro_Judge_Regulator(MacroLane_Sel,PLL0VREGDLFSEL, PLL0VREGDLF_VREGHALF, "PLL0VREGDLFSEL", "PLL0VREGDLF_VREGHALF");
			HiLink_PerMacro_Judge_Regulator(MacroLane_Sel,PLL0VREGVCODIVSEL, PLL0VREGVCODIV_VREGHALF, "PLL0VREGVCODIVSEL", "PLL0VREGVCODIV_VREGHALF");

			HiLink_PerMacro_Judge_Regulator(MacroLane_Sel,PLL1VREGPLLSEL, PLL1VREGPLL_VREGHALF, "PLL1VREGPLLSEL", "PLL1VREGPLL_VREGHALF");
			HiLink_PerMacro_Judge_Regulator(MacroLane_Sel,PLL1VREGDLFSEL, PLL1VREGDLF_VREGHALF, "PLL1VREGDLFSEL", "PLL1VREGDLF_VREGHALF");
			HiLink_PerMacro_Judge_Regulator(MacroLane_Sel,PLL1VREGVCODIVSEL, PLL1VREGVCODIV_VREGHALF, "PLL1VREGVCODIVSEL", "PLL1VREGVCODIV_VREGHALF");

			HiLink_PerLane_Judge_Regulator(MacroLane_Sel, VREGDATALVL_CODE,VREGDATA_VREG_2_3,"VREGDATALVL_CODE", "VREGDATA_VREG_2_3");
			HiLink_PerLane_Judge_Regulator(MacroLane_Sel, VREGCLKLVL_CODE,VREGCLK_VREG_2_3_3,"VREGCLKLVL_CODE","VREGCLK_VREG_2_3_3" );
			HiLink_PerLane_Judge_Regulator(MacroLane_Sel, TXPREDRVREGLVL_CODE,VREG_PREDRV_2_3,"TXPREDRVREGLVL_CODE","VREG_PREDRV_2_3" );
			HiLink_PerLane_Judge_Regulator(MacroLane_Sel, TXDRVREGLVL_CODE,VREG_DRV_2_3,"TXDRVREGLVL_CODE", "VREG_DRV_2_3");
			HiLink_PerLane_Judge_Regulator(MacroLane_Sel, VREGLVL_CODE,VREG_VREG_2_3,"VREGLVL_CODE", "VREG_VREG_2_3");
			HiLink_PerLane_Judge_Regulator(MacroLane_Sel, CTLEVREGVREFSEL_CODE,CTLE_VREG_VOUT_1_7,"CTLEVREGVREFSEL_CODE", "CTLE_VREG_VOUT_1_7");
		}
                
                SetTestBin();
	}

};
REGISTER_TESTCLASS("Regulator",Regulator)



