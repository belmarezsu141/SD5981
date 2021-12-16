//for test method API interfaces
//#include "mapi.hpp"

#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// TM Purpose:                                                                //
// This TM is to measure pk-pk jitter and eye width in different setup of     //
// PRBS15 pattern under internal loopback mode. The test is performed with    //
// the setups include different data rate and different bit width.            //
//																			  //
// Parameters:																  //
// 1. Tx_main: setup Tx FIR main value										  //
// 2. RateMode: setup Tx data rate mode, including FULL, HALF, QUAD and OCT   //
// 3. DataWidth: setup Tx data width, including 16 bit, 20 bit, 32 bit and    //
//               40 bit.                                                      //
// 4. DataRate: setup device working data rate, such as 12.5Gbps, 10.3125Gbps.//
////////////////////////////////////////////////////////////////////////////////
/**
 *This test is invoked per siiRateModete.
 */
class TxEScopePrbs15_ABIST: public TestClass
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
		add_param("DataRate[Gbps]","double",&mDataRate)
					//.set_options("6.25:9.8304:10.1376:10.3125:12.5:15")
					.set_default("15");
		add_param("UseFixCTLE","string",&mUseFixCTLE)
					//.set_options("NO:YES")
					.set_default("NO");
//		add_param("UseFixCTLE.CTLEACTGN1","int",&iCTLEACTGN1)
//			        .set_default("7");
//		add_param("UseFixCTLE.CTLEACTGN2","int",&iCTLEACTGN2)
//			        .set_default("7");
//		add_param("UseFixCTLE.CTLEACTGN3","int",&iCTLEACTGN3)
//			        .set_default("7");
//		add_param("UseFixCTLE.CTLEBST1","int",&iCTLEBST1)
//			  	    .set_default("0");
//		add_param("UseFixCTLE.CTLEBST2","int",&iCTLEBST2)
//			      	.set_default("0");
//		add_param("UseFixCTLE.CTLEBST3","int",&iCTLEBST3)
//			        .set_default("0");
		add_param("FULL_EYE","string",&mEyeScope)
					//.set_options("YES:NO")
					.set_default("NO");
		add_param("PRBSMode","string",&mPRBSMode)
					//.set_options("PRBS15:CUSTOMER_PATTERN")
					.set_default("PRBS15");
		add_param("EyeDiagram Method","string",&sEyeDiagMethod)
					//.set_options("FW:HW")
					.set_default("FW");
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
		static bool CSRVerifyResult;

		static LANE_UINT EyeWidth1;
		static LANE_UINT EyeHeight1;
		static LANE_UINT EyeWidth2;
		static LANE_UINT EyeHeight2;

		static LANE_DOUBLE Jitter1;
		static LANE_DOUBLE Jitter2;
		INT iCTLEACTGN1;
		INT iCTLEACTGN2;
		INT iCTLEACTGN3;
		INT iCTLEBST1;
		INT iCTLEBST2;
		INT iCTLEBST3;

//		static STRING mPinList = "";
//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

	    //stTxEScopePrbs15_ABIST TxEScopePrbs15_ABIST=H30_TxEScopePrbs15_30G_ABIST_TxEScopePrbs15_ABIST;  //5875
		stTxEScopePrbs15_ABIST TxEScopePrbs15_ABIST =
				H30_TxEScopePrbs15_24G33024_ABIST_TxEScopePrbs15_ABIST;	//modify tony 20210519

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

		d2s_JTAG& jtag = d2s_JTAG::Instance();
		SetTxFir(MacroLane_Sel, Custpara);
		LoopBack_Setting(sLoopBackMode, MacroLane_Sel,
				Custpara);

//		sprintf(label,"MPB_TXESCOPEPRBS15_SETUP_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));

		d2s::d2s_LABEL_BEGIN( "MPB_TXESCOPEPRBS15_SETUP_",Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);

		DS.rxRegs.SliceID(0).Broadcast(1);
		DS.txRegs.SliceID(0).Broadcast(1);
		DS.clkRegs.SliceID(0).Broadcast(1);

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
		jtag.wait(0.0001);
		DS.rxRegs.setcdrfreeze(1).Write2DUT(12);
		jtag.wait(0.0001);
//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();

		//=============================================
		// Measurement
		//=============================================

		uint iShowInner = 0;		//inner eye scan
		uint iEyeScanWin = 15; // vertical inner eye scan
		uint iMonSlcSel = 0; // 0 = I
		uint iEyeScanMode = 1; //vetical inner eye scan
		uint itap1Inside = 1; //eye diagram with tap1
		uint itap1Type = 2; //plot the composite tap1 eye

		switch (iRateMode)
		{
		case 0:
			iMonSlcSel = 0;
			break; //full rate, I eye
		case 1:
			iMonSlcSel = 3;
			break; //half rate,Qb eye
		case 2:
			iMonSlcSel = 1;
			break; //quart rate, Q eye
		}

		if (sEyeDiagMethod == "FW")
		{
			AteFwFourPointEyeScan(MacroLane_Sel,
					dRefCLK_MHz,
					dRefCLK_MHz2,
					mDataRate, EyeWidth1, EyeHeight1,
					EyeWidth2, EyeHeight2);
		}
		else if (sEyeDiagMethod == "HW")
		{
			GetFourPointEyeDiagram(MacroLane_Sel, iShowInner, iEyeScanWin,
					iMonSlcSel, 1, 0, EyeWidth1, EyeHeight1);
			GetFourPointEyeDiagram(MacroLane_Sel, iShowInner, iEyeScanWin,
					iMonSlcSel, 1, 1, EyeWidth2, EyeHeight2);
		}
		else
		{
//	    	cout<<"ERROR: FourPointEyeDiagram only support FW or HW method."<<endl;
//			api->info_message("ERROR: FourPointEyeDiagram only support FW or HW method.");
			cout <<"ERROR: FourPointEyeDiagram only support FW or HW method."<<endl;
//	    	ERROR_EXIT(TM::ABORT_FLOW);
		}

//		if(mEyeScope=="YES"||(hout.getLevel()== 4)){
		if (mEyeScope == "YES")
		{
			GetEyeDiagram(MacroLane_Sel, iEyeScanMode, iEyeScanWin,
					iMonSlcSel, itap1Inside, itap1Type);
		}

//		sprintf(label,"MPB_TxEScope_Restore_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN("H30_DsPowerUpWiClkDis_SetUp_Part1_", Global_D2S_Mode);
		selectMacro_MB(MacroLane_Sel);
		DS.txRegs.SliceID(0).Broadcast(1);
		DS.txRegs.setkfactor(0x0).Write2DUT(3);
		DS.txRegs.setjitppmctrl(0x0).Write2DUT(3);
		DS.txRegs.setjitfreq(0x0).Write2DUT(3);
		DS.txRegs.setjitamp(0x0).Write2DUT(3);
		DS.txRegs.setppmgen(0x0).Write2DUT(3);
		DS.txRegs.settxalignmode(0x3).Write2DUT(2);
//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();

		//=============================================
		// Datalog
		//=============================================

		DOUBLE uiSize = 0.0;
		DOUBLE eyeUI_ps = 1000.0 / mDataRate;

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

//		ON_FIRST_INVOCATION_END();
		//=============================================
		// Datalog
		//=============================================
		double LimitL_Jitter = 1;
		double LimitH_Jitter = 25;
		double LimitL_EyeHeight = 40;
		double LimitH_EyeHeight = 318;
		HiLink_PerLane_Judge(MacroLane_Sel, "Tap1pol1=0_Jitter_Pk-Pk",
				LimitL_Jitter, Jitter1, LimitH_Jitter);
		HiLink_PerLane_Judge(MacroLane_Sel, "Tap1pol1=0_EyeHeight_pt",
				LimitL_EyeHeight, EyeHeight1, LimitH_EyeHeight);
		HiLink_PerLane_Judge(MacroLane_Sel, "Tap1pol1=1_Jitter_Pk-Pk",
				LimitL_Jitter, Jitter2, LimitH_Jitter);
		HiLink_PerLane_Judge(MacroLane_Sel, "Tap1pol1=1_EyeHeight_pt",
				LimitL_EyeHeight, EyeHeight2, LimitH_EyeHeight);

		SetTestBin ();

	}

};
REGISTER_TESTCLASS("TxEScopePrbs15_ABIST", TxEScopePrbs15_ABIST)

