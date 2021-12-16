
#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"

using namespace std;

class RxSensitivity_ABIST: public TestClass {
public:
    STRING  			sHiLink30_MacroList;
	STRING 				sPinList;
	INT	 				iTxMain;
	INT					iTxPre1st;
	INT					iTxPost1st;
	INT                 iTxPre2nd;
	INT                 iTxPost2nd;
    STRING              sLoopBackMode;

	INT 				iCTLEACTGN1;
	INT 				iCTLEACTGN2;
	INT 				iCTLEACTGN3;
	INT					iCTLEBST1;
	INT					iCTLEBST2;
	INT					iCTLEBST3;
	INT                 iMAINSTOP;
	INT 				iMAINSTEP;
	STRING				mUseFixCTLE;
	INT					iPrintLvl;
	void init() {
		  add_param("HiLink30_MacroList","string",&sHiLink30_MacroList)
					  .set_comment("HiLink30 Macro List for test")
					  //.set_options("0,1:FromPinList")
					  .set_default("0,1");
		  add_param("LoopBackMode","string",&sLoopBackMode)
					  .set_default("Bump");
					  //.set_options("PreDriver:Bump:External:Nothing");
//		  add_param("PinList","PinString",&sPinList);
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
//		  add_param("UseFixCTLE.CTLEACTGN1","int",&iCTLEACTGN1)
//		  	  	  	  .set_default("7");
//		  add_param("UseFixCTLE.CTLEACTGN2","int",&iCTLEACTGN2)
//		  	  	  	  .set_default("7");
//		  add_param("UseFixCTLE.CTLEACTGN3","int",&iCTLEACTGN3)
//		  	  	  	  .set_default("7");
//		  add_param("UseFixCTLE.CTLEBST1","int",&iCTLEBST1)
//		  	  	  	  .set_default("0");
//		  add_param("UseFixCTLE.CTLEBST2","int",&iCTLEBST2)
//		  	  	  	  .set_default("0");
//		  add_param("UseFixCTLE.CTLEBST3","int",&iCTLEBST3)
//		  	  	  	  .set_default("0");
		  add_param("MAIN_STOP","int",	&iMAINSTOP)
		  	  	  	  .set_default("0");
		  add_param("MAIN_STEP","int",	&iMAINSTEP)
		  	  	  	  .set_default("3");
			add_param("PrintLvl[0~8]","int",&iPrintLvl)
					  .set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
					  "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					  //.set_options("0:1:3:4:7:8")
					  .set_default("3");
	}
	void execute() {

		//Add your test code here.
		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================

		H30_FailBin_Flag.init(0);
		INT iDebugAnalog;
		static INT iCSR_check;
		static MACRO_LANE_SEL MacroLane_Sel;

		static LANE_DOUBLE vMinAmp;
		static bool CSRVerifyResult;
		INT iCTLEACTGN1;
		INT iCTLEACTGN2;
		INT iCTLEACTGN3;
		INT iCTLEBST1;
		INT iCTLEBST2;
		INT iCTLEBST3;

		//	  ON_FIRST_INVOCATION_BEGIN();

		//	  GET_TESTFLOW_FLAG	("debug_analog",&iDebugAnalog);
		//	  GET_USER_FLAG		("CSR_atomic_operation",&iCSR_check);

//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

		//         stRxSensitivity_ABIST RxSensitivity_ABIST=H30_RxSensitivity_30G_ABIST_RxSensitivity_ABIST;  //5875
		stRxSensitivity_ABIST RxSensitivity_ABIST =
				H30_RxSensitivity_24G33024_ABIST_RxSensitivity_ABIST;//modify tony 20210519
		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel,sHiLink30_MacroList);

		//	  FlexRelayCtrl();

		//=============================================
		// Device Setup
		//=============================================
		CUSTPARA Custpara = default_CUSTPARA;

		Custpara.TxFIR_USER.iTxMain = iTxMain;
		Custpara.TxFIR_USER.iTxPre1st = iTxPre1st;
		Custpara.TxFIR_USER.iTxPost1st = iTxPost1st;
		Custpara.TxFIR_USER.iTxPre2nd = iTxPre2nd;
		Custpara.TxFIR_USER.iTxPost2nd = iTxPost2nd;

		Custpara.RxCTLE_USER.Gain[0] = iCTLEACTGN1;
		Custpara.RxCTLE_USER.Gain[1] = iCTLEACTGN2;
		Custpara.RxCTLE_USER.Gain[2] = iCTLEACTGN3;
		Custpara.RxCTLE_USER.Boost[0] = iCTLEBST1;
		Custpara.RxCTLE_USER.Boost[1] = iCTLEBST2;
		Custpara.RxCTLE_USER.Boost[2] = iCTLEBST3;

		//	  D2S_FRAMEWORK;
		//	  GET_TEST_INFO;

		LoopBack_Setting(sLoopBackMode, MacroLane_Sel,
				Custpara);
		d2s_JTAG& jtag = d2s_JTAG::Instance();
		//	  sprintf(label,"MPB_RxSensitivity_ABIST_SETUP_%f_%f_",Vcoef,Temp);
		//	  fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN( "MPB_RxSensitivity_ABIST_SETUP_",
				Global_D2S_Mode);
		selectMacro_MB(MacroLane_Sel);

		DS.rxRegs.SliceID(0).Broadcast(1);
		DS.txRegs.SliceID(0).Broadcast(1);

		//Tx Setting
		//Enable PRBS generation with PRBS15
		EnableTxPrbsGen("PRBS15");

		DS.rxRegs.setcdrfreeze(0x0).Write2DUT(12);
		//                  jtag.wait(100 uS);
		jtag.wait(0.0001);

		if (mUseFixCTLE == "YES") {
			DS.rxRegs.setctleactgn1(iCTLEACTGN1).Write2DUT(1);
			DS.rxRegs.setctleactgn2(iCTLEACTGN2).Write2DUT(2);
			DS.rxRegs.setctleactgn3(iCTLEACTGN3).Write2DUT(3);
			DS.rxRegs.setctleboostc1(iCTLEBST1).Write2DUT(1);
			DS.rxRegs.setctleboostc2(iCTLEBST2).Write2DUT(2);
			DS.rxRegs.setctleboostc3(iCTLEBST3).Write2DUT(3);
		}
		EnableRxPrbsCheck("PRBS15");
		//	  fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();

		//=============================================
		//measurement
		//=============================================
		LANE_DOUBLE vErrorCount;
		LANE_INT vFindFlag;
		vErrorCount.init(0);
		vFindFlag.init(0);
		vMinAmp.init(iTxMain);

		INT find_all = 0;
		while (Custpara.TxFIR_USER.iTxMain >= iMAINSTOP
				&& ((find_all == 0) || (Global_D2S_Mode == 0))) {
			SetTxFir(MacroLane_Sel, Custpara);
			//		  WAIT_TIME(2 ms);

			hout(DETAIL) << "\n========== main = " << dec << Custpara.TxFIR_USER.iTxMain << " ==========" << endl;
			//cout << "\n========== main = " << dec << Custpara.TxFIR_USER.iTxMain << " ==========" << endl;

			Read_Bert(MacroLane_Sel, vErrorCount, "ABIST", false, "", 0, 0.001);

			find_all = 1;
//
//			FOREACH_ACTIVE_SITE(api)
//			{
//				unsigned int SiteID = api->Get_active_site();
			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

			for (UINT uiMacroIndex = 0; uiMacroIndex < MacroLane_Sel.size();
						uiMacroIndex++) {
					const vector<UINT>& vLane =
							MacroLane_Sel[uiMacroIndex].vLane;
					UINT MacroID = MacroLane_Sel[uiMacroIndex].MacroID;
					for (UINT uiLaneIndex = 0; uiLaneIndex < vLane.size();
							uiLaneIndex++) {
						UINT LaneID = vLane[uiLaneIndex];
						if (vErrorCount[SiteID][MacroID][LaneID] == 0
								&& vFindFlag[SiteID][MacroID][LaneID] == 0) {
							vMinAmp[SiteID][MacroID][LaneID] =
									Custpara.TxFIR_USER.iTxMain;
							find_all = 0;
						} else {
							vFindFlag[SiteID][MacroID][LaneID] = 1;
						}
					}
				}
				FOREACH_ACTIVESITE_END

			Custpara.TxFIR_USER.iTxMain = Custpara.TxFIR_USER.iTxMain
					- iMAINSTEP;
		}

		Custpara.TxFIR_USER.iTxMain = iTxMain;
		Custpara.TxFIR_USER.iTxPre1st = iTxPre1st;
		Custpara.TxFIR_USER.iTxPost1st = iTxPost1st;
		Custpara.TxFIR_USER.iTxPre2nd = iTxPre2nd;
		Custpara.TxFIR_USER.iTxPost2nd = iTxPost2nd;

		SetTxFir(MacroLane_Sel, Custpara);

		//	  ON_FIRST_INVOCATION_END();

		//=============================================
		// Datalog
		//=============================================
		double LimitL = 1;
		double LimitH = 35;
		HiLink_PerLane_Judge(MacroLane_Sel, "MinSwing", LimitL, vMinAmp,LimitH);


		SetTestBin();
	}

};
REGISTER_TESTCLASS("RxSensitivity_ABIST", RxSensitivity_ABIST)

