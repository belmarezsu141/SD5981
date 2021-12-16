//for test method API interfaces

#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"

using namespace std;
class EyeMonitorCheckPrbs31_ABIST: public TestClass
{
public:
	STRING 				mHiLink30_MacroList;
	STRING 				mPinList;
	INT	 				iTxMain;
	INT					iTxPre1st;
	INT					iTxPost1st;
	INT					iTxPre2nd;
	INT					iTxPost2nd;
	DOUBLE 				mDataRate;
	STRING 				mEyeScope;
    STRING              sLoopBackMode;
    STRING              mPRBSMode;
    STRING              mRateMode;
	INT 				iCTLEACTGN1;
	INT 				iCTLEACTGN2;
	INT 				iCTLEACTGN3;
	INT					iCTLEBST1;
	INT					iCTLEBST2;
	INT					iCTLEBST3;
    STRING				mUseFixCTLE;
    DOUBLE				dRefCLK_MHz;
    DOUBLE				dRefCLK_MHz2;
    STRING				sEyeDiagMethod;
    INT					iPrintLvl;

	void init()
	{
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					 .set_comment("HiLink30 Macro List for test")
					 //.set_options("0,1:FromPinList")
					 .set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
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
		add_param("DataRate","double",&mDataRate)
					.set_comment("DataRate")
					.set_default("30");
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
		add_param("UseFixCTLE","string",	&mUseFixCTLE)
					 //.set_options("NO:YES")
					 .set_default("NO");
//		add_param("UseFixCTLE.CTLEACTGN1","int",&iCTLEACTGN1)
//		   	   	   	 .set_default("7");
//		add_param("UseFixCTLE.CTLEACTGN2","int",&iCTLEACTGN2)
//					.set_default("7");
//		add_param("UseFixCTLE.CTLEACTGN3","int",&iCTLEACTGN3)
//					.set_default("7");
//		add_param("UseFixCTLE.CTLEBST1","int",&iCTLEBST1)
//		  			.set_default("0");
//		add_param("UseFixCTLE.CTLEBST2","int",&iCTLEBST2)
//		  			.set_default("0");
//		add_param("UseFixCTLE.CTLEBST3","int",&iCTLEBST3)
//		  			.set_default("0");
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
		INT iDebugAnalog;
		static INT iCSR_check;
		static MACRO_LANE_SEL MacroLane_Sel;

		static LANE_UINT EyeWidth1;
		static LANE_UINT EyeHeight1;
		static LANE_UINT EyeWidth2;
		static LANE_UINT EyeHeight2;

		static LANE_DOUBLE Jitter1;
		static LANE_DOUBLE Jitter2;
		STRING mPRBSMode;
		INT iCTLEACTGN1;
		INT iCTLEACTGN2;
		INT iCTLEACTGN3;
		INT iCTLEBST1;
		INT iCTLEBST2;
		INT iCTLEBST3;

		static bool CSRVerifyResult;

		stEyeMonitorCheckPrbs31_ABIST EyeMonitorCheckPrbs31_ABIST;

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
		Select_Macro_Lane(MacroLane_Sel,mHiLink30_MacroList, mPinList);


		Jitter1.init(0);
		EyeHeight1.init(0);
		EyeWidth1.init(0);
		Jitter2.init(0);
		EyeHeight2.init(0);
		EyeWidth2.init(0);

//		FlexRelayCtrl();
		//=============================================
		// Device Setup
		//=============================================
//		D2S_FRAMEWORK;
//		GET_TEST_INFO;

		INT iRateMode = DS.txRegs.gettxratemode();

		CUSTPARA Custpara;
		Custpara.TxFIR_USER.iTxMain = iTxMain;
		Custpara.TxFIR_USER.iTxPre1st = iTxPre1st;
		Custpara.TxFIR_USER.iTxPre2nd = iTxPre2nd;
		Custpara.TxFIR_USER.iTxPost1st = iTxPost1st;
		Custpara.TxFIR_USER.iTxPost2nd = iTxPost2nd;

		SetTxFir(MacroLane_Sel, Custpara);

		LoopBack_Setting(sLoopBackMode,
				MacroLane_Sel, Custpara);

		d2s::d2s_LABEL_BEGIN("EYEMONPRBS31_SETUP_Rate",Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);

		DS.rxRegs.SliceID(0).Broadcast(1);
		DS.txRegs.SliceID(0).Broadcast(1);

		mPRBSMode = "PRBS31";
		EnableTxPrbsGen(mPRBSMode);

		if (mUseFixCTLE == "YES")
		{
			DS.rxRegs.setctleactgn1(iCTLEACTGN1).Write2DUT(1);
			DS.rxRegs.setctleactgn2(iCTLEACTGN2).Write2DUT(2);
			DS.rxRegs.setctleactgn3(iCTLEACTGN3).Write2DUT(3);
			DS.rxRegs.setctleboostc1(iCTLEBST1).Write2DUT(1);
			DS.rxRegs.setctleboostc2(iCTLEBST2).Write2DUT(2);
			DS.rxRegs.setctleboostc3(iCTLEBST3).Write2DUT(3);
		}
		DS.rxRegs.setcdrfreeze(0).Write2DUT(12);

		d2s::d2s_LABEL_END();

		//=============================================
		// Measurement
		//=============================================
		AteFwFourPointEyeScan(MacroLane_Sel,
				dRefCLK_MHz,
				dRefCLK_MHz2,
				mDataRate, EyeWidth1, EyeHeight1,
				EyeWidth2, EyeHeight2);

		//=============================================
		// Datalog
		//=============================================

		DOUBLE uiSize = 0.0;

		DOUBLE eyeUI_ps = 1000.0 / mDataRate;

		switch (iRateMode)
		//todo
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

//		FOREACH_ACTIVE_SITE(api)
//		{
//			unsigned int SiteID = api->Get_active_site();
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size();
					macroIndex++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++)
				{
					UINT LaneID = vLane[laneIndex];

					Jitter1[SiteID][MacroID][LaneID] = eyeUI_ps
							* (1 - EyeWidth1[SiteID][MacroID][LaneID] / uiSize);
					Jitter2[SiteID][MacroID][LaneID] = eyeUI_ps
							* (1 - EyeWidth2[SiteID][MacroID][LaneID] / uiSize);

				}
			}
		FOREACH_ACTIVESITE_END

		//=============================================
		// Datalog
		//=============================================
		double LimitL = 1;
		double LimitH = 1;
		HiLink_PerLane_Judge(MacroLane_Sel, "Jitter1_Pk-Pk", LimitL, Jitter1,LimitH);
		HiLink_PerLane_Judge(MacroLane_Sel, "Jitter2_Pk-Pk", LimitL, Jitter2,LimitH);
//                SetTestBin(api);//masked by tony 20210707
	}
};
REGISTER_TESTCLASS("EyeMonitorCheckPrbs31_ABIST", EyeMonitorCheckPrbs31_ABIST)

