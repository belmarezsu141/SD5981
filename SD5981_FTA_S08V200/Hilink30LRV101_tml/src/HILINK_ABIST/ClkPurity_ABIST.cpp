
#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"

class ClkPurity_ABIST: public TestClass
{
public:
	STRING 				sHiLink30_MacroList;
	STRING 				sPinList;
	INT	 				iTxMain;
	INT                 iDataWidth;
	INT                 iRateMode;
	INT					iTxPre1st;
	INT					iTxPost1st;
	INT					iTxPre2nd;
	INT					iTxPost2nd;
	DOUBLE 				dDataRate;
	STRING 				sEyeScope;
    STRING              sLoopBackMode;
    INT 				iCTLEACTGN1;
    INT 				iCTLEACTGN2;
    INT 				iCTLEACTGN3;
    INT					iCTLEBST1;
    INT					iCTLEBST2;
    INT					iCTLEBST3;
    STRING				mUseFixCTLE;
    DOUBLE				dRefCLK_MHz;
    DOUBLE				dRefCLK_MHz2;
    INT					iPrintLvl;
    INT					iTxFIR;
	void init()
	{
		  add_param("HiLink30_MacroList","string",&sHiLink30_MacroList)
					  .set_comment("HiLink30 Macro List for test")
					  //.set_options("0,1:FromPinList")
					  .set_default("0,1");
		  add_param("LoopBackMode","string",&sLoopBackMode)
					  //.set_options("PreDriver:Bump:External:Nothing")
					  .set_default("Bump");
		  add_param("RefCLK_MHz","double",&dRefCLK_MHz)
					  .set_comment("RefCLK_MHz")
					  //.set_options("100:156.25")
					  .set_default("156.25");
		  add_param("RefCLK_MHz2","double",&dRefCLK_MHz2)
					  .set_comment("RefCLK_MHz")
					  //.set_options("100:156.25")
					  .set_default("156.25");
		  add_param("TxFIR.TxMain","int",&iTxMain)
		  	  	  	  .set_default("57");
		  add_param("TxFIR.TxPre1st","int",&iTxPre1st)
		  	  	  	  .set_default("-6");
		  add_param("TxFIR.TxPost1st","int",&iTxPost1st)
		  	  	  	  .set_default("0");
		  add_param("TxFIR.TxPre2nd","int",&iTxPre2nd)
		  	  	  	  .set_default("0");
		  add_param("TxFIR.TxPost2nd","int",&iTxPost2nd)
		  	  	  	  .set_default("0");
		  add_param("DataRate[Gbps]","double",&dDataRate)
					  //.set_options("6.25:9.8304:10.1376:10.3125:12.5:15")
					  .set_default("15");
		  add_param("RateMode","int",&iRateMode)
		  	  	  	  .set_default("0");
		  add_param("UseFixCTLE","string",&mUseFixCTLE)
					  //.set_options("NO:YES")
					  .set_default("YES");
		  add_param("UseFixCTLE.CTLEACTGN1","int",&iCTLEACTGN1)
		  	  	  	  .set_default("7");
		  add_param("UseFixCTLE.CTLEACTGN2","int",&iCTLEACTGN2)
		  	  	  	  .set_default("7");
		  add_param("UseFixCTLE.CTLEACTGN3","int",&iCTLEACTGN3)
		  	  	  	  .set_default("7");
		  add_param("UseFixCTLE.CTLEBST1","int",&iCTLEBST1)
		  	  	  	  .set_default("0");
		  add_param("UseFixCTLE.CTLEBST2","int",&iCTLEBST2)
		  	  	  	  .set_default("0");
		  add_param("UseFixCTLE.CTLEBST3","int",&iCTLEBST3)
		  	  	  	  .set_default("0");
		  add_param("PrintLvl[0~8]","int",&iPrintLvl)
					  .set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
					  "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					  //.set_options("0:1:3:4:7:8")
					  .set_default("3");

	}
	void execute()
	{
		//Add your test code here.
		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
		H30_FailBin_Flag.init(0);
		INT iDebugAnalog;
		static INT iOffline;
		static INT iCSR_check;

		static LANE_DOUBLE PhaseDiviation, MaxJitter;
		static LANE_DOUBLE MinEyeWidth, MaxEyeWidth;

		static LANE_UINT EyeWidthMin;
		static LANE_UINT EyeWidthMax;

		static LANE_DOUBLE dEyeWidthMin;
		static LANE_DOUBLE dEyeWidthMax;
		static bool CSRVerifyResult;

		static STRING mPinList = "";
//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();
		static stClkPurity_ABIST ClkPurity;

		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);

//		static STRING sPinList = "";
		static MACRO_LANE_SEL MacroLane_Sel;
		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel, sHiLink30_MacroList,sPinList);

		/***Open AC relay to ensure cal trim value is correct***/
		//	  FlexRelayCtrl();
		//=============================================
		// Variables definition and initialization
		//=============================================
		//=============================================
		// Device Setup
		//=============================================
		static CUSTPARA Custpara = default_CUSTPARA;

		Custpara.TxFIR_USER.iTxMain = iTxMain;
		Custpara.TxFIR_USER.iTxPre1st = iTxPre1st;
		Custpara.TxFIR_USER.iTxPost1st = iTxPost1st;
		Custpara.TxFIR_USER.iTxPre2nd = iTxPre2nd;
		Custpara.TxFIR_USER.iTxPost2nd = iTxPost2nd;

		//	  D2S_FRAMEWORK;
		//	  GET_TEST_INFO;

		SetTxFir(MacroLane_Sel, Custpara);
		LoopBack_Setting(sLoopBackMode, MacroLane_Sel, Custpara);

		//	  sprintf(label,"MPB_CLKPURITY_SETUP_%f_%f_",Vcoef,Temp);
		//	  fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s_JTAG& the_jtag = d2s_JTAG::Instance();
		d2s::d2s_LABEL_BEGIN("MPB_CLKPURITY_SETUP_",Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);

		DS.rxRegs.SliceID(0).Broadcast(1);
		DS.txRegs.SliceID(0).Broadcast(1);

		//Enable PRBS generation with 1010
		EnableTxPrbsGen("CUSTOMER_PATTERN", 0xAAAA);

		if (mUseFixCTLE == "YES")
		{
			DS.rxRegs.setctleactgn1(iCTLEACTGN1).Write2DUT(1);
			DS.rxRegs.setctleactgn2(iCTLEACTGN2).Write2DUT(2);
			DS.rxRegs.setctleactgn3(iCTLEACTGN3).Write2DUT(3);
			DS.rxRegs.setctleboostc1(iCTLEBST1).Write2DUT(1);
			DS.rxRegs.setctleboostc2(iCTLEBST2).Write2DUT(2);
			DS.rxRegs.setctleboostc3(iCTLEBST3).Write2DUT(3);
		}

		//Tx Setting
		DS.txRegs.settxalignmode(3).Write2DUT(2);
		//Rx Setting
		DS.rxRegs.setcdrfreeze(0).Write2DUT(12);
		the_jtag.wait(0.0001);
		DS.rxRegs.setcdrfreeze(1).Write2DUT(12);
		the_jtag.wait(0.0001);

		d2s::d2s_LABEL_END();
//		Sleep(2);
		//=============================================
		// Measurement
		//=============================================

		DOUBLE uiSize = 0.0;

		dEyeWidthMin.init(0);
		dEyeWidthMax.init(0);

		switch (iRateMode)
		{
		case 0:
			uiSize = 32;
			break;
		case 1:
			uiSize = 64;
			break;
		case 2:
			uiSize = 128;
			break;
		case 3:
			uiSize = 256;
			break;
		default:
			uiSize = 32;
			break;
		}

		AteFwEyeWidthScan(MacroLane_Sel, dRefCLK_MHz,dRefCLK_MHz2, EyeWidthMin, EyeWidthMax);


		//	  FOR_EACH_SITE_BEGIN();
		//		INT SiteID = CURRENT_SITE_NUMBER() - 1;
//		FOREACH_ACTIVE_SITE(api)
//		{
//			unsigned int SiteID = api->Get_active_site();
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT iMacroIndex = 0; iMacroIndex < MacroLane_Sel.size();
					iMacroIndex++)
			{
				UINT MacroID = MacroLane_Sel[iMacroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[iMacroIndex].vLane;

				for (UINT iLaneIndex = 0; iLaneIndex < vLane.size();
						iLaneIndex++)
				{
					UINT LaneID = MacroLane_Sel[iMacroIndex].vLane[iLaneIndex];
					dEyeWidthMin[SiteID][MacroID][LaneID] =
							EyeWidthMin[SiteID][MacroID][LaneID] / uiSize;
					dEyeWidthMax[SiteID][MacroID][LaneID] =
							EyeWidthMax[SiteID][MacroID][LaneID] / uiSize;

	                //add by tony 20210822
//	                printf("FourEyeDiagramFWClkPurity_Read dEyeWidthMin = %d\n", dEyeWidthMin[SiteID][MacroID][LaneID]);
//	                printf("FourEyeDiagramFWClkPurity_Read dEyeWidthMax = %d\n", dEyeWidthMax[SiteID][MacroID][LaneID]);
				}
			}
		FOREACH_ACTIVESITE_END

		INT PhaseNum;
		switch (iRateMode)
		{
		case 0:
			PhaseNum = 32;
			break;
		case 1:
			PhaseNum = 64;
			break;
		case 2:
			PhaseNum = 128;
			break;
		case 3:
			PhaseNum = 256;
			break;
		default:
			PhaseNum = 32;
			break;
		}

		DOUBLE eyeUI_ps = 1000.0 / dDataRate;

		//	  FOR_EACH_SITE_BEGIN();
		//		INT SiteID = CURRENT_SITE_NUMBER() - 1;
//		FOREACH_ACTIVE_SITE(api)
//		{
//			unsigned int SiteID = api->Get_active_site();
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT iMacroIndex = 0; iMacroIndex < MacroLane_Sel.size();
					iMacroIndex++)
			{
				const vector<UINT>& vLane = MacroLane_Sel[iMacroIndex].vLane;
				UINT MacroID = MacroLane_Sel[iMacroIndex].MacroID;
				for (UINT iLaneIndex = 0; iLaneIndex < vLane.size();
						iLaneIndex++)
				{
					UINT LaneID = MacroLane_Sel[iMacroIndex].vLane[iLaneIndex];

					MinEyeWidth[SiteID][MacroID][LaneID] =
							dEyeWidthMin[SiteID][MacroID][LaneID] * eyeUI_ps;
					MaxEyeWidth[SiteID][MacroID][LaneID] =
							dEyeWidthMax[SiteID][MacroID][LaneID] * eyeUI_ps;
					PhaseDiviation[SiteID][MacroID][LaneID] =
							(dEyeWidthMax[SiteID][MacroID][LaneID]
									- dEyeWidthMin[SiteID][MacroID][LaneID])
									* PhaseNum;
					MaxJitter[SiteID][MacroID][LaneID] = eyeUI_ps
							- MinEyeWidth[SiteID][MacroID][LaneID];

	                //add by tony 20210822
//	                printf("FourEyeDiagramFWClkPurity_Read MinEyeWidth = %d\n", MinEyeWidth[SiteID][MacroID][LaneID]);
//	                printf("FourEyeDiagramFWClkPurity_Read MaxEyeWidth = %d\n", MaxEyeWidth[SiteID][MacroID][LaneID]);
//	                printf("FourEyeDiagramFWClkPurity_Read PhaseDiviation = %d\n", PhaseDiviation[SiteID][MacroID][LaneID]);
//	                printf("FourEyeDiagramFWClkPurity_Read MaxJitter = %d\n", MaxJitter[SiteID][MacroID][LaneID]);
				}
			}

			if (iOffline)
			{
				for (UINT iMacroIndex = 0; iMacroIndex < MacroLane_Sel.size();
						iMacroIndex++)
				{
					const vector<UINT>& vLane = MacroLane_Sel[iMacroIndex].vLane;
					UINT MacroID = MacroLane_Sel[iMacroIndex].MacroID;
					for (UINT iLaneIndex = 0; iLaneIndex < vLane.size();
							iLaneIndex++)
					{
						UINT LaneID =
								MacroLane_Sel[iMacroIndex].vLane[iLaneIndex];
						MaxJitter[SiteID][MacroID][LaneID] = 1;
						PhaseDiviation[SiteID][MacroID][LaneID] = 0;
					}
				}
			}

		FOREACH_ACTIVESITE_END


		//=============================================
		// Datalog
		//=============================================
		//	  HiLink_PerLane_Judge(MacroLane_Sel, "EyePhaseDivPt", PhaseDiviation);
		//	  HiLink_PerLane_Judge(MacroLane_Sel, "MaxJitterpt", MaxJitter);
		double LimitL = 0;
		double LimitH = 5;
		HiLink_PerLane_Judge(MacroLane_Sel, "EyePhaseDivPt", LimitL,PhaseDiviation, LimitH);

		LimitL = 0;
		LimitH = 25;
		HiLink_PerLane_Judge(MacroLane_Sel, "MaxJitterpt", LimitL, MaxJitter,LimitH);


		SetTestBin();
	}

};

REGISTER_TESTCLASS("ClkPurity_ABIST", ClkPurity_ABIST)
