
#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"



void searchFreqOffset( MACRO_LANE_SEL MacroLane_Sel,
		INT iRateMode, INT iDataWidth, bool isPos, LANE_DOUBLE& PPMResult) {
	INT iDebugAnalog;
//		GET_TESTFLOW_FLAG	("debug_analog",&iDebugAnalog);

	INT iFindAll = 0;
	UINT Index = 0;
	INT macroNum = MacroLane_Sel.size();

	LANE_DOUBLE vErrorCount;
	LANE_INT iLaneDone;

	PPMResult.init(9999);
	iLaneDone.init(0);

	DOUBLE UIsize = 32;
	DOUBLE EffectiveBusWidth = 40;

	typedef map<int, double>::value_type valType;

	map<int, double> mapPPM;
	INT jitppmctrl = 0; //Normal mode
	if (jitppmctrl == 0) {
		mapPPM.insert(
				valType(0, 1000000.0 / (UIsize * EffectiveBusWidth * 16)));
		mapPPM.insert(
				valType(1, 1000000.0 / (UIsize * EffectiveBusWidth * 12)));
		mapPPM.insert(
				valType(2, 1000000.0 / (UIsize * EffectiveBusWidth * 10)));
		mapPPM.insert(valType(3, 1000000.0 / (UIsize * EffectiveBusWidth * 8)));
		mapPPM.insert(valType(4, 1000000.0 / (UIsize * EffectiveBusWidth * 6)));
		mapPPM.insert(valType(5, 1000000.0 / (UIsize * EffectiveBusWidth * 4)));
		mapPPM.insert(valType(6, 1000000.0 / (UIsize * EffectiveBusWidth * 3)));
		mapPPM.insert(valType(7, 1000000.0 / (UIsize * EffectiveBusWidth * 2)));
	} else if (jitppmctrl == 1) {
		mapPPM.insert(
				valType(0, 1000000.0 / (UIsize * EffectiveBusWidth * 64)));
		mapPPM.insert(
				valType(1, 1000000.0 / (UIsize * EffectiveBusWidth * 48)));
		mapPPM.insert(
				valType(2, 1000000.0 / (UIsize * EffectiveBusWidth * 40)));
		mapPPM.insert(
				valType(3, 1000000.0 / (UIsize * EffectiveBusWidth * 32)));
		mapPPM.insert(
				valType(4, 1000000.0 / (UIsize * EffectiveBusWidth * 24)));
		mapPPM.insert(
				valType(5, 1000000.0 / (UIsize * EffectiveBusWidth * 20)));
		mapPPM.insert(
				valType(6, 1000000.0 / (UIsize * EffectiveBusWidth * 16)));
		mapPPM.insert(
				valType(7, 1000000.0 / (UIsize * EffectiveBusWidth * 12)));
		mapPPM.insert(
				valType(8, 1000000.0 / (UIsize * EffectiveBusWidth * 10)));
		mapPPM.insert(valType(9, 1000000.0 / (UIsize * EffectiveBusWidth * 8)));
		mapPPM.insert(
				valType(10, 1000000.0 / (UIsize * EffectiveBusWidth * 6)));
		mapPPM.insert(
				valType(11, 1000000.0 / (UIsize * EffectiveBusWidth * 5)));
		mapPPM.insert(
				valType(12, 1000000.0 / (UIsize * EffectiveBusWidth * 4)));
		mapPPM.insert(
				valType(13, 1000000.0 / (UIsize * EffectiveBusWidth * 3)));
		mapPPM.insert(
				valType(14, 1000000.0 / (UIsize * EffectiveBusWidth * 2)));
	}

	map<int, double>::iterator itPPM;

	Stress_Setting Stress_SET;
	Stress_SET.jitcontrol = jitppmctrl;
	Stress_SET.jitamp = 0;
	Stress_SET.jitFreq = 0; //change 7 to 0 to close JITTER INJECT

//		D2S_FRAMEWORK;

	while (Index < mapPPM.size() && (iFindAll == 0 || Global_D2S_Mode == 0)) {

		itPPM = mapPPM.find(Index);
		if (itPPM != mapPPM.end()) {
			Stress_SET.ppmgen =
					(isPos ?
							FreqOffset( itPPM->second, jitppmctrl) :
							FreqOffset( itPPM->second, jitppmctrl) + 0x10);
		}

		//			sprintf (label,"MPB_FREQOFFSET_PPM_%d_%s", Stress_SET.ppmgen, jtag.Context.c_str());
		//			fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN( "MPB_FREQOFFSET_PPM_",
				Global_D2S_Mode);
		selectMacro_MB(MacroLane_Sel);
		DS.txRegs.SliceID(0).Broadcast(1);
		DS.txRegs.settxalignmode(3).Write2DUT(2);
		DS.txRegs.setjitppmctrl(Stress_SET.jitcontrol).setjitfreq(
				Stress_SET.jitFreq).setjitamp(Stress_SET.jitamp).setppmgen(
				Stress_SET.ppmgen).Write2DUT(3);
		DS.txRegs.settxalignmode(4).Write2DUT(2);
		//			fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();

		//			WAIT_TIME(10 ms);

//		Sleep(0.01);

		Read_Bert( MacroLane_Sel, vErrorCount, "ABIST", false, "", 0, 0.001);

		iFindAll = Update_LaneData_InTolerance( MacroLane_Sel,
				itPPM->second * (isPos ? 1.0 : -1.0), vErrorCount, PPMResult,
				iLaneDone);

		Index++;
	}
}

class RxFreqOffsetTol_ABIST: public TestClass {
public:
	STRING 				mHiLink30_MacroList;
	STRING 				mPinList;
	INT                 iDataWidth;
	INT                 iRateMode;
	INT	 				iTxMain;
	INT					iTxPre1st;
	INT					iTxPost1st;
	INT                 iTXDRVTAPXMODSEL;
	INT                 iTxPre2nd;
	INT                 iTxPost2nd;
    STRING              sLoopBackMode;
	INT 				iCTLEACTGN1;
	INT 				iCTLEACTGN2;
	INT 				iCTLEACTGN3;
	INT					iCTLEBST1;
	INT					iCTLEBST2;
	INT					iCTLEBST3;
	STRING				mUseFixCTLE;
	INT					iPrintLvl;

	void init() {
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					.set_comment("HiLink30 Macro List for test")
					//.set_options("0,1:FromPinList")
					.set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
		add_param("LoopBackMode","string",&sLoopBackMode)
					.set_default("Bump");
					//.set_options("PreDriver:Bump:External:Nothing");
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
		add_param("RateMode","int",&iRateMode)
					.set_default("0");
		add_param("DataWidth","int",&iDataWidth)
					.set_default("0");
		add_param("UseFixCTLE","string",&mUseFixCTLE)
					//.set_options("NO:YES")
					.set_default("NO");
//		add_param("UseFixCTLE.CTLEACTGN1","int",&iCTLEACTGN1)
//					.set_default("7");
//		add_param("UseFixCTLE.CTLEACTGN2","int",&iCTLEACTGN2)
//					.set_default("7");
//		add_param("UseFixCTLE.CTLEACTGN3","int",&iCTLEACTGN3)
//					.set_default("7");
//		add_param("UseFixCTLE.CTLEBST1","int",&iCTLEBST1)
//					.set_default("0");
//		add_param("UseFixCTLE.CTLEBST2","int",&iCTLEBST2)
//					.set_default("0");
//		add_param("UseFixCTLE.CTLEBST3","int",&iCTLEBST3)
//					.set_default("0");
		add_param("PrintLvl[0~8]","int",&iPrintLvl)
					.set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
					"0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					//.set_options("0:1:3:4:7:8")
					.set_default("3");
	}
	void execute() {

		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
		H30_FailBin_Flag.init(0);
		INT iCTLEACTGN1;
		INT iCTLEACTGN2;
		INT iCTLEACTGN3;
		INT iCTLEBST1;
		INT iCTLEBST2;
		INT iCTLEBST3;
//		static	STRING          	sTestsuiteName;
		static INT iOffline;
		static INT iCSR_check;
		static MACRO_LANE_SEL MacroLane_Sel;

		static LANE_DOUBLE vMaxPPM_P;
		static LANE_DOUBLE vMaxPPM_N;
		static bool CSRVerifyResult;

		INT iDebugAnalog;

//		ON_FIRST_INVOCATION_BEGIN();
		//=============================================
		// Variables and MacroLane initialization
		//=============================================
//		GET_TESTSUITE_NAME	(sTestsuiteName);
//		GET_TESTFLOW_FLAG	("debug_analog",&iDebugAnalog);
//		GET_USER_FLAG		("CSR_atomic_operation",&iCSR_check);

//                stRxFreqOffsetTol_ABIST RxFreqOffsetTol_ABIST=H30_RxFreqOffsetTol_30G_ABIST_RxFreqOffsetTol_ABIST;  //5875
		stRxFreqOffsetTol_ABIST RxFreqOffsetTol_ABIST =
				H30_RxFreqOffsetTol_24G33024_ABIST_RxFreqOffsetTol_ABIST;//4.29
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

//		FlexRelayCtrl();
		//=============================================
		// Device Setup
		//=============================================
//		D2S_FRAMEWORK;
//		GET_TEST_INFO;

		d2s_JTAG& jtag = d2s_JTAG::Instance();
		INT iDataWidth = DS.txRegs.gettxdwidth();
		INT iRateMode = DS.txRegs.gettxratemode();
		//=============================================
		// Device Setup
		//=============================================
		CUSTPARA Custpara = default_CUSTPARA;
		Custpara.TxFIR_USER.iTxMain = iTxMain;
		Custpara.TxFIR_USER.iTxPre1st = iTxPre1st;
		Custpara.TxFIR_USER.iTxPost1st = iTxPost1st;
		Custpara.TxFIR_USER.iTxPre2nd = iTxPre2nd;
		Custpara.TxFIR_USER.iTxPost2nd = iTxPost2nd;

		SetTxFir( MacroLane_Sel, Custpara);
		/***********************************
		 STEP2. Select loopback mode
		 ************************************/
		LoopBack_Setting( sLoopBackMode,
				MacroLane_Sel, Custpara);

//		sprintf(label,"MPB_RxFrequencyOffset_SETUP_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN( "MPB_RxFrequencyOffset_SETUP_",Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);
		DS.txRegs.SliceID(0).Broadcast(1);
		DS.rxRegs.SliceID(0).Broadcast(1);

		/***********************************
		 STEP3. Enable PRBS generator with PRBS15
		 ************************************/
		EnableTxPrbsGen( "PRBS15");

		DS.rxRegs.setcdrfreeze(0x0).Write2DUT(12);
//			jtag.wait(100 us);
		jtag.wait(0.0001);
		EnableRxPrbsCheck( "PRBS15");
		DS.txRegs.settxcpddlcal(0x0).Write2DUT(10);

		/****************** RxCTLE Setup *************/
		if (mUseFixCTLE == "YES") {
			DS.txRegs.SliceID(0).Broadcast(1);
			DS.rxRegs.setctleactgn1(iCTLEACTGN1).Write2DUT(1);
			DS.rxRegs.setctleactgn2(iCTLEACTGN2).Write2DUT(2);
			DS.rxRegs.setctleactgn3(iCTLEACTGN3).Write2DUT(3);
			DS.rxRegs.setctleboostc1(iCTLEBST1).Write2DUT(1);
			DS.rxRegs.setctleboostc2(iCTLEBST2).Write2DUT(2);
			DS.rxRegs.setctleboostc3(iCTLEBST3).Write2DUT(3);
		}
//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();

		//=============================================
		//measurement
		//=============================================

		searchFreqOffset( MacroLane_Sel, iRateMode, iDataWidth, true,
				vMaxPPM_P);
		searchFreqOffset( MacroLane_Sel, iRateMode, iDataWidth, false,
				vMaxPPM_N);

		/***********************************
		 STEP10. Restore setting as initial status
		 ************************************/
//		sprintf(label,"MPB_RxFreqOffset_Restore_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN( "MPB_RxFreqOffset_Restore_",
				Global_D2S_Mode);
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

//		ON_FIRST_INVOCATION_END();

		//=============================================
		// Datalog
		//=============================================

		double LimitL_Pos = 200;
		double LimitH_Pos = 400;
		double LimitL_Neg = -400;
		double LimitH_Neg = -200;
		HiLink_PerLane_Judge( MacroLane_Sel, "FreqOffset_Pos", LimitL_Pos,
				vMaxPPM_P, LimitH_Pos);
		HiLink_PerLane_Judge( MacroLane_Sel, "FreqOffset_Neg", LimitL_Neg,
				vMaxPPM_N, LimitH_Neg);

		SetTestBin ();

	}

};
REGISTER_TESTCLASS("RxFreqOffsetTol_ABIST", RxFreqOffsetTol_ABIST)

