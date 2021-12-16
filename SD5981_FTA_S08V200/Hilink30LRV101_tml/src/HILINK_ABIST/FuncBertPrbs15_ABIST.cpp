//for test method API interfaces

#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"
using namespace std;

class FuncBertPrbs15_ABIST: public TestClass
{
public:
	STRING 				mHiLink30_MacroList;
	STRING 				mPinList;
	INT					iPrintLvl;

	INT	 				iTxMain;
	INT					iTxPre1st;
	INT					iTxPost1st;
	INT					iTxPre2nd;
	INT					iTxPost2nd;
	DOUBLE 				mDataRate;
	STRING 				mEyeScope;
    STRING              sLoopBackMode;
	DOUBLE 				JitterAmpRequired;
	DOUBLE 				mFreqOffset;
	INT                 iDataWidth;
	INT                 iRateMode;
	STRING				mUseFixCTLE;
	DOUBLE				dRefCLK_MHz;
	STRING				sEyeDiagMethod;

	void init()
	{
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
							.set_comment("HiLink30 Macro List for test")
							//.set_options("0,1:FromPinList")
							.set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
		add_param("LoopBackMode","string",&sLoopBackMode)
					//.set_options("PreDriver:Bump:External:Nothing")
					.set_default("PreDriver");
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

		static LANE_DOUBLE RxErrorCount;
		static bool CSRVerifyResult;

//		ON_FIRST_INVOCATION_BEGIN();
//		//=============================================
//		// Variables and MacroLane initialization
//		//=============================================
//		GET_SYSTEM_FLAG		("offline",&iOffline);
//		GET_TESTSUITE_NAME	(sTestsuiteName);
//		GET_USER_FLAG		("CSR_atomic_operation",&iCSR_check);

//		static STRING mPinList = "";
//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);

//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

		stFuncBertPrbs15_ABIST FuncBertPrbs15_ABIST;


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

		CUSTPARA Custpara = default_CUSTPARA;
		Custpara.TxFIR_USER.iTxMain = iTxMain;
		Custpara.TxFIR_USER.iTxPre1st = iTxPre1st;
		Custpara.TxFIR_USER.iTxPre2nd = iTxPre2nd;
		Custpara.TxFIR_USER.iTxPost1st = iTxPost1st;
		Custpara.TxFIR_USER.iTxPost2nd = iTxPost2nd;

		/***********************************
		 STEP2. Select loopback mode
		 ************************************/
		LoopBack_Setting(sLoopBackMode, MacroLane_Sel,Custpara);


//		sprintf(label,"H30_FuncBertPrbs15_SETUP_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN( "H30_FuncBertPrbs15_SETUP_",Global_D2S_Mode);


		selectMacro_MB(MacroLane_Sel);

		DS.rxRegs.SliceID(0).Broadcast(1);
		DS.txRegs.SliceID(0).Broadcast(1);

		/****************** RxCTLE and TxFIR Setup *************/ //TODO:
		if (sLoopBackMode == "PreDriver")
		{
			DS.rxRegs.setctleactgn1(7).Write2DUT(1);
			DS.rxRegs.setctleactgn2(7).Write2DUT(2);
			DS.rxRegs.setctleactgn3(7).Write2DUT(3);
			DS.rxRegs.setctleboostc1(7).Write2DUT(1);
			DS.rxRegs.setctleboostc2(7).Write2DUT(2);
			DS.rxRegs.setctleboostc3(0).Write2DUT(3);
			DS.rxRegs.setctleza1(0).Write2DUT(1);
			DS.rxRegs.setctleza2(0).Write2DUT(2);
			DS.rxRegs.setctleza3(0).Write2DUT(3);
			DS.rxRegs.setctlesqh1(1).Write2DUT(1);
			DS.rxRegs.setctlesqh2(1).Write2DUT(2);
			DS.rxRegs.setctlesqh3(1).Write2DUT(3);
			DS.rxRegs.setctlermband1(2).Write2DUT(1);
			DS.rxRegs.setctlermband2(1).Write2DUT(2);
			DS.rxRegs.setctlermband3(1).Write2DUT(3);
			DS.rxRegs.setctlecmband1(2).Write2DUT(1);
			DS.rxRegs.setctlecmband2(1).Write2DUT(2);
			DS.rxRegs.setctlecmband3(1).Write2DUT(3);
			DS.rxRegs.setctlehfzen1(0).Write2DUT(1);
			DS.rxRegs.setctlehfzen2(0).Write2DUT(2);
			DS.rxRegs.setctlehfzen3(0).Write2DUT(3);
		}
		else if (sLoopBackMode == "Bump")
		{
			DS.rxRegs.setctleactgn1(7).Write2DUT(1);
			DS.rxRegs.setctleactgn2(7).Write2DUT(2);
			DS.rxRegs.setctleactgn3(7).Write2DUT(3);
			DS.rxRegs.setctleboostc1(0).Write2DUT(1);
			DS.rxRegs.setctleboostc2(0).Write2DUT(2);
			DS.rxRegs.setctleboostc3(0).Write2DUT(3);
			DS.rxRegs.setctleza1(0).Write2DUT(1);
			DS.rxRegs.setctleza2(0).Write2DUT(2);
			DS.rxRegs.setctleza3(0).Write2DUT(3);
			DS.rxRegs.setctlesqh1(2).Write2DUT(1);
			DS.rxRegs.setctlesqh2(2).Write2DUT(2);
			DS.rxRegs.setctlesqh3(2).Write2DUT(3);
			DS.rxRegs.setctlermband1(2).Write2DUT(1);
			DS.rxRegs.setctlermband2(1).Write2DUT(2);
			DS.rxRegs.setctlermband3(1).Write2DUT(3);
			DS.rxRegs.setctlecmband1(2).Write2DUT(1);
			DS.rxRegs.setctlecmband2(1).Write2DUT(2);
			DS.rxRegs.setctlecmband3(1).Write2DUT(3);
			DS.rxRegs.setctlehfzen1(0).Write2DUT(1);
			DS.rxRegs.setctlehfzen2(0).Write2DUT(2);
			DS.rxRegs.setctlehfzen3(0).Write2DUT(3);
		}
		else
		{
//				ERROR_EXIT(TM::ABORT_FLOW);
//				cout << "ERROR:: This testmethod only support Predriver and Bump!!" << endl;
//			api->info_message("ERROR:: This testmethod only support Predriver and Bump!!");
			cout <<"ERROR:: This testmethod only support Predriver and Bump!!"<<endl;
		}

		/***********************************
		 STEP3. Enable PRBS generator with PRBS15
		 ************************************/
		EnableTxPrbsGen("PRBS15");

		/***********************************
		 STEP4. Unfreeze CDR
		 ************************************/
		DS.rxRegs.setcdrfreeze(1).Write2DUT(12); //todo: debug solution
		//jtag.wait(100 us);
		jtag.wait(0.0001);
		DS.rxRegs.setcdrfreeze(0).Write2DUT(12);
		//jtag.wait(100 us);
		jtag.wait(0.0001);

		/***********************************
		 STEP5. Enable PRBS checker with PRBS15
		 ************************************/
		EnableRxPrbsCheck("PRBS15");

//		SetTxFir(Custpara);

		d2s::d2s_LABEL_END();

		/***********************************
		 STEP6. Read BERT result after test 10ms
		 ************************************/
		Read_Bert(MacroLane_Sel, RxErrorCount, "ABIST", false, "", 0, 0.01);

//		ON_FIRST_INVOCATION_END();
		//=============================================
		// Datalog
		//=============================================
		double LimitL = 0;
		double LimitH = 0;

		HiLink_PerLane_Judge(MacroLane_Sel, "Rx_Err_Cnt", LimitL, RxErrorCount,LimitH);


//                SetTestBin(api); //masked by tony 20210707
	}
};
REGISTER_TESTCLASS("FuncBertPrbs15_ABIST", FuncBertPrbs15_ABIST)

