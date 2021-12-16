
#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"


class DPM_TEST_BY_FW: public TestClass
{
public:
	STRING 				mHiLink30_MacroList;
	STRING 				mPinList;
	DOUBLE              dRefCLK_MHz;
    DOUBLE				dRefCLK_MHz2;
	INT					iPrintLvl;
	STRING              sJudgementType;
	void init()
	{
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					.set_comment("HiLink30 Macro List for test")
					//.setOptions("0,1:FromPinList")
					.set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
		add_param("JudgementType","string",&sJudgementType)
		////.setOptions("UseExternalSpec_FW_Judge:ReadBack_InternalSpec_TMJudge:BothMethod")
					//.setOptions("ReadBack_InternalSpec_TMJudge")
					.set_default("ReadBack_InternalSpec_TMJudge");
		add_param("RefCLK_MHz","double",&dRefCLK_MHz)
					.set_comment("RefCLK_MHz")
					//.setOptions("100:156.25")
					.set_default("156.25");
		add_param("RefCLK_MHz2","double",&dRefCLK_MHz2)
					.set_comment("RefCLK_MHz")
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
		INT iDebugAnalog;
		static INT iOffline;
		static INT iCSR_check;
		static MACRO_LANE_SEL MacroLane_Sel;

		static MACRO_DOUBLE SSulvt_ottwa_pmos_Corner_volt_Code;
		static MACRO_DOUBLE SSulvt_ottwa_nmos_Corner_volt_Code;
		static MACRO_DOUBLE SSulvt_ottwa_pmos_Corner_Code;
		static MACRO_DOUBLE SSulvt_ottwa_nmos_Corner_Code;
		static MACRO_DOUBLE SSulvt_ottwa_pmos_corner_sigma;
		static MACRO_DOUBLE SSulvt_ottwa_nmos_corner_sigma;
		static MACRO_DOUBLE CSulvt_ottwa_pmos_Corner_volt_Code;
		static MACRO_DOUBLE CSulvt_ottwa_nmos_Corner_volt_Code;
		static MACRO_DOUBLE CSulvt_ottwa_pmos_Corner_Code;
		static MACRO_DOUBLE CSulvt_ottwa_nmos_Corner_Code;
		static MACRO_DOUBLE CSulvt_ottwa_pmos_corner_sigma;
		static MACRO_DOUBLE CSulvt_ottwa_nmos_corner_sigma;
		static bool CSRVerifyResult;

		static MACRO_DOUBLE mTemp;
		SSulvt_ottwa_pmos_Corner_volt_Code.init(0);
		SSulvt_ottwa_nmos_Corner_volt_Code.init(0);
		SSulvt_ottwa_pmos_Corner_Code.init(0);
		SSulvt_ottwa_nmos_Corner_Code.init(0);
		SSulvt_ottwa_pmos_corner_sigma.init(0);
		SSulvt_ottwa_nmos_corner_sigma.init(0);
		CSulvt_ottwa_pmos_Corner_volt_Code.init(0);
		CSulvt_ottwa_nmos_Corner_volt_Code.init(0);
		CSulvt_ottwa_pmos_Corner_Code.init(0);
		CSulvt_ottwa_nmos_Corner_Code.init(0);
		CSulvt_ottwa_pmos_corner_sigma.init(0);
		CSulvt_ottwa_nmos_corner_sigma.init(0);
		mTemp.init(0);

		map<UINT, bool> mSSMacroID;
		STRING sSSMacroList = "";
		MACRO_LANE_SEL vProcessMacroSS;

		//		ON_FIRST_INVOCATION_BEGIN();
		//		=============================================
		// Variables and MacroLane initialization
		//=============================================
		//		GET_SYSTEM_FLAG		("offline",&iOffline);
		//		GET_USER_FLAG		("CSR_atomic_operation",&iCSR_check);
		//		GET_TESTFLOW_FLAG	("debug_analog",&iDebugAnalog);
//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();
		//=============================================
		// Device Setup
		//=============================================
		//		D2S_FRAMEWORK;
		//		GET_TEST_INFO;

//		static STRING mPinList = "";
		stDPM_TEST_BY_FW& DPM_TEST_BY_FW = H30_DPM_TEST_BY_FW_DPM_TEST_BY_FW;
		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList,mPinList);

		uint iRefclk0_freqm100 = uint(dRefCLK_MHz * 100);
		uint iRefclk1_freqm100 = uint(dRefCLK_MHz2 * 100);

		/***********************************
		 STEP1. Startup all Macro (startup SS & CS only, DO NOT startup DS)
		 ************************************/
		// TODO
		/***********************************
		 STEP3.  Load Abist test firmware: DPM Firmware
		 ************************************/
		LoadFirmwareToSram(MacroLane_Sel, HILINK_DPM_Bin, HILINK_DPM_Bin_CYCLE);
		/************************************/
		//Step4: If let FW do the judgement, Set the spec
		/************************************/
		if ((sJudgementType == "UseExternalSpec_FW_Judge")|| (sJudgementType == "BothMethod"))
		{
			//			WriteSingleSpecToSram(MacroLane_Sel,0x1F860, 20.5, 0x1F862, 1.2, 1000);
		}

		/********************/
		//Step5: read temp and set temp
		//Get ss macro
		/********************/
		sSSMacroList = SSMacroIDList;
		Select_Macro_Lane(vProcessMacroSS, sSSMacroList);
		DPM_Run(vProcessMacroSS, iRefclk0_freqm100, iRefclk1_freqm100);
		/**************************/
		//read temp
		/*************************/
		SRAM_READ_BY_WORD(MacroLane_Sel, 0x1FCD2, mTemp, 0, 0);
		/**************************/
		//Set the temp of macro without ss
		/******************************/
		//		FOR_EACH_SITE_BEGIN();
		//			INT SiteID = CURRENT_SITE_NUMBER() - 1;
//		FOREACH_ACTIVE_SITE(api)
//		{
//			unsigned int SiteID = api->Get_active_site();
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size();
					macroIndex++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				UINT SSMacroID = vProcessMacroSS[0].MacroID;
				if (mSSMacroID.find(MacroID) == mSSMacroID.end()) //if the macro is not have SS ,then set temp of SS marco to CS macro
				{
					mTemp[SiteID][MacroID] = mTemp[SiteID][SSMacroID];
				}
			}
		FOREACH_ACTIVESITE_END

		/**************************/
		//dynamic write back  the temp value
		/******************************/
		//		//for debug dynamic write
		//		mTemp[0][0]=5;
		//		mTemp[0][1]=10;
		//		mTemp[1][0]=25;//for multi site check
		//		mTemp[1][1]=50;
		//		//for debug verify dynamic write
		//		MACRO_DOUBLE mDebug;
		//		mDebug.init(0);
		//		SRAM_READ_BY_WORD(MacroLane_Sel, 0x1FCD2,  mDebug,0);
		//		cout<<"*************DEBUG***************"<<endl;
		//		cout<<"Macro 0 mTemp data="<<mTemp[0][0]<<endl;
		//		cout<<"Macro 1 mTemp data="<<mTemp[0][1]<<endl;
		//		cout<<"Macro 0 data="<<mDebug[0][0]<<endl;
		//		cout<<"Macro 1 data="<<mDebug[0][1]<<endl;
		//		//end debug
		d2s_JTAG& jtag = d2s_JTAG::Instance();
		uint regAddress_offset1 = 0x1FCD2;
		//		sprintf(label, "H30V101_DPM_Write_Temp_Dynamic_%f_%f_", Vcoef, Temp);
		//		fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN("H30V101_DPM_Write_Temp_Dynamic_",	Global_D2S_Mode);

		for (UINT iMacroIndex = 0; iMacroIndex < MacroLane_Sel.size();iMacroIndex++)

		{
			UINT MacroID = MacroLane_Sel[iMacroIndex].MacroID;
			selectMacro(MacroID);
			ostringstream idtemp;
			idtemp << "TEMPAddr_" << "_M" << MacroID << jtag.Context;
			map<int, long long> tmp;
			parseSiteDataIntFromMacroDouble(tmp, mTemp, MacroID);
			jtag.writeDynamicPerSite(regAddress_offset1 >> 1, tmp,idtemp.str());

		}
		//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();

		//		//for debug verify dynamic write
		//	//	MACRO_DOUBLE mDebug;
		//		mDebug.init(0);
		//		SRAM_READ_BY_WORD(MacroLane_Sel, 0x1FCD2,  mDebug,0);
		//		cout<<"*************DEBUG***************"<<endl;
		//		cout<<"Macro 0 mTemp data="<<mTemp[0][0]<<endl;
		//		cout<<"Macro 1 mTemp data="<<mTemp[0][1]<<endl;
		//		cout<<"Macro 0 data="<<mDebug[0][0]<<endl;
		//		cout<<"Macro 1 data="<<mDebug[0][1]<<endl;
		//		//end debug
		/*********************************/
		//Step6/Step7/Step8/Step9/Step10 set DPM API and run
		/**********************************/
		DPM_Run(MacroLane_Sel, iRefclk0_freqm100, iRefclk1_freqm100);

		/**************************/
		//Read data
		/************************/
		//Step10: Read SRAM results
		if ((sJudgementType == "ReadBack_InternalSpec_TMJudge")
				|| (sJudgementType == "BothMethod"))
		{

			SRAM_READ_BY_WORD(MacroLane_Sel, 0x1FCD4,
					SSulvt_ottwa_pmos_Corner_volt_Code, 1, 0);
			SRAM_READ_BY_WORD(MacroLane_Sel, 0x1FCD6,
					SSulvt_ottwa_nmos_Corner_volt_Code, 1, 0);
			SRAM_READ_BY_WORD(MacroLane_Sel, 0x1FCD8,
					SSulvt_ottwa_pmos_corner_sigma, 1, 1);
			SRAM_READ_BY_WORD(MacroLane_Sel, 0x1FCDA,
					SSulvt_ottwa_nmos_corner_sigma, 1, 1);
			SRAM_READ_BY_WORD(MacroLane_Sel, 0x1FCEC,
					CSulvt_ottwa_pmos_Corner_volt_Code, 1, 0);
			SRAM_READ_BY_WORD(MacroLane_Sel, 0x1FCEE,
					CSulvt_ottwa_nmos_Corner_volt_Code, 1, 0);
			SRAM_READ_BY_WORD(MacroLane_Sel, 0x1FCF0,
					CSulvt_ottwa_pmos_corner_sigma, 1, 1);
			SRAM_READ_BY_WORD(MacroLane_Sel, 0x1FCF2,
					CSulvt_ottwa_nmos_corner_sigma, 1, 1);
			SRAM_READ_BY_WORD(MacroLane_Sel, 0x1FCD2, mTemp, 1, 0);

			//			FOR_EACH_SITE_BEGIN();
			//				INT SiteID = CURRENT_SITE_NUMBER() - 1;
//			FOREACH_ACTIVE_SITE(api)
//			{
//				unsigned int SiteID = api->Get_active_site();
			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size();
						macroIndex++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					if (mTemp[SiteID][MacroID] > 32768)
					{
						mTemp[SiteID][MacroID] = mTemp[SiteID][MacroID] - 65536;
					}
				}
			FOREACH_ACTIVESITE_END

//			FOREACH_ACTIVE_SITE(api)
//			{
//				unsigned int SiteID = api->Get_active_site();
			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			//DS information
				for (uint midx = 0; midx < vProcessMacroSS.size(); midx++)
				{
					uint MacroID = vProcessMacroSS[midx].MacroID;
					SSulvt_ottwa_pmos_Corner_Code[SiteID][MacroID] =
							SSulvt_ottwa_pmos_Corner_volt_Code[SiteID][MacroID]
									+ 0.454 * (mTemp[SiteID][MacroID] + 40);
					SSulvt_ottwa_nmos_Corner_Code[SiteID][MacroID] =
							SSulvt_ottwa_nmos_Corner_volt_Code[SiteID][MacroID]
									+ 0.393 * (mTemp[SiteID][MacroID] + 40);
					SSulvt_ottwa_pmos_corner_sigma[SiteID][MacroID] =
							(SSulvt_ottwa_pmos_corner_sigma[SiteID][MacroID])
									/ 1000;
					SSulvt_ottwa_nmos_corner_sigma[SiteID][MacroID] =
							(SSulvt_ottwa_nmos_corner_sigma[SiteID][MacroID])
									/ 1000;
				}
				for (uint midx = 0; midx < MacroLane_Sel.size(); midx++)
				{
					uint MacroID = MacroLane_Sel[midx].MacroID;
					CSulvt_ottwa_pmos_Corner_Code[SiteID][MacroID] =
							CSulvt_ottwa_pmos_Corner_volt_Code[SiteID][MacroID]
									+ 0.454 * (mTemp[SiteID][MacroID] + 40);
					CSulvt_ottwa_nmos_Corner_Code[SiteID][MacroID] =
							CSulvt_ottwa_nmos_Corner_volt_Code[SiteID][MacroID]
									+ 0.393 * (mTemp[SiteID][MacroID] + 40);
					CSulvt_ottwa_pmos_corner_sigma[SiteID][MacroID] =
							CSulvt_ottwa_pmos_corner_sigma[SiteID][MacroID]
									/ 1000;
					CSulvt_ottwa_nmos_corner_sigma[SiteID][MacroID] =
							CSulvt_ottwa_nmos_corner_sigma[SiteID][MacroID]
									/ 1000;
				}
			FOREACH_ACTIVESITE_END

		}

		//Step10: Read SRAM Results
		if ((sJudgementType == "UseExternalSpec_FW_Judge")
				|| (sJudgementType == "BothMethod"))
		{
			////			SEGMENT_READ_MACRO(MacroLane_Sel,SRAM.ABISTAPIRegs.REG_INFO.ctle_dc_gain_status_abist_api(),DcGain_Result);
			//
			//			for(uint macroIndex=0; macroIndex < MacroLane_Sel.size();macroIndex++)
			//			{
			//				//Readback Sram result for EVB Corrlation purpose
			//				ostringstream  TestDatalogBegin, TestDatalogEnd;
			//				TestDatalogBegin<<"\n"<<"==========H30LRV101_DPM_FWTest_Start==========";
			//				PUT_DATALOG(TestDatalogBegin.str());
			//				ostringstream  TestDatalog;
			//				//FWAbistHeader(MacroLane_Sel, macroIndex, HILINK_FIRMWARE_LABEL_DEFAULT, DPM_Bin, "DPM_LR", TestDatalog);
			//				//PrinfToEdf_FWAbist(TestDatalog);
			//				TestDatalogEnd<<"\n"<<"==========H30LRV101_DPM_FWTest_End=========="<<endl;
			//				PUT_DATALOG(TestDatalogEnd.str());
			//			}

		}

		//		ON_FIRST_INVOCATION_END();
		//=============================================
		// Datalog
		//=============================================
		double LimitL = -32767;
		double LimitH = 32768;
		HiLink_PerMacro_Judge(vProcessMacroSS, "Temperature", LimitL, mTemp,
				LimitH);
		HiLink_PerMacro_Judge(vProcessMacroSS, "SSulvt_ottwa_pmos_Corner_Code",
				LimitL, SSulvt_ottwa_pmos_Corner_Code, LimitH);
		HiLink_PerMacro_Judge(vProcessMacroSS, "SSulvt_ottwa_nmos_Corner_Code",
				LimitL, SSulvt_ottwa_nmos_Corner_Code, LimitH);
		HiLink_PerMacro_Judge(vProcessMacroSS, "SSulvt_ottwa_pmos_corner_sigma",
				LimitL, SSulvt_ottwa_pmos_corner_sigma, LimitH);
		HiLink_PerMacro_Judge(vProcessMacroSS, "SSulvt_ottwa_nmos_corner_sigma",
				LimitL, SSulvt_ottwa_nmos_corner_sigma, LimitH);
		HiLink_PerMacro_Judge(MacroLane_Sel, "CSulvt_ottwa_pmos_Corner_Code",
				LimitL, CSulvt_ottwa_pmos_Corner_Code, LimitH);
		HiLink_PerMacro_Judge(MacroLane_Sel, "CSulvt_ottwa_nmos_Corner_Code",
				LimitL, CSulvt_ottwa_nmos_Corner_Code, LimitH);
		HiLink_PerMacro_Judge(MacroLane_Sel, "CSulvt_ottwa_pmos_corner_sigma",
				LimitL, CSulvt_ottwa_pmos_corner_sigma, LimitH);
		HiLink_PerMacro_Judge(MacroLane_Sel, "CSulvt_ottwa_nmos_corner_sigma",
				LimitL, CSulvt_ottwa_nmos_corner_sigma, LimitH);

		//                SetTestBin();//masked by tony 20210707

	}
};


REGISTER_TESTCLASS("DPM_TEST_BY_FW", DPM_TEST_BY_FW)
