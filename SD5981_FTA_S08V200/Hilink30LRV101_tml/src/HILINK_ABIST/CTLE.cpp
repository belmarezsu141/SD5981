
#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"

using namespace std;

class CTLE: public TestClass
{
public:

	STRING 				mHiLink30_MacroList;
	STRING 				mPinList;
	INT					iPrintLvl;

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
	INT					iCTLEBYPASS;
	STRING				mUseFixCTLE;

	void init()
	{
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					.set_comment("HiLink30 Macro List for test")
					//.set_options("0,1:FromPinList")
					.set_default("0,1");
		add_param("UseFixCTLE","string",&mUseFixCTLE)
					//.set_options("NO:YES")
					.set_default("YES");
		add_param("UseFixCTLEACTGN1","int",&iCTLEACTGN1)
					.set_default("7");
		add_param("UseFixCTLEACTGN2","int",&iCTLEACTGN2)
					.set_default("7");
		add_param("UseFixCTLEACTGN3","int",&iCTLEACTGN3)
					.set_default("7");
		add_param("UseFixCTLEBST1","int",&iCTLEBST1)
					.set_default("7");
		add_param("UseFixCTLEBST2","int",&iCTLEBST2)
					.set_default("7");
		add_param("UseFixCTLEBST3","int",&iCTLEBST3)
					.set_default("7");
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

		static INT iOffline;
		static INT iCSR_check;
		static MACRO_LANE_SEL MacroLane_Sel;

		stCTLE CTLE = CTLE_A_CTLE;

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
		Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList, mPinList);

		//=============================================
		// CTLE Setup
		//=============================================

		d2s::d2s_LABEL_BEGIN("H30V101_CTLE_SETUP_",Global_D2S_Mode);


		selectMacro_MB(MacroLane_Sel);
		DS.rxRegs.SliceID(0).Broadcast(1);
		if (mUseFixCTLE == "YES")
		{
			DS.rxRegs.setctleactgn1(iCTLEACTGN1).Write2DUT(1);
			DS.rxRegs.setctleactgn2(iCTLEACTGN2).Write2DUT(2);
			DS.rxRegs.setctleactgn3(iCTLEACTGN3).Write2DUT(3);
			DS.rxRegs.setctleboostc1(iCTLEBST1).Write2DUT(1);
			DS.rxRegs.setctleboostc2(iCTLEBST2).Write2DUT(2);
			DS.rxRegs.setctleboostc3(iCTLEBST3).Write2DUT(3);
		}
		DS.rxRegs.setrxctleibiastune(6).Write2DUT(36);
		d2s::d2s_LABEL_END();
	}

};
REGISTER_TESTCLASS("CTLE", CTLE)
