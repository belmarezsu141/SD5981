
#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"



class DumpSramData: public TestClass
{
public:

	  long  				mSramAddr;
	  string  				mDumpType;
	  long  				mCount;
	  STRING 				mHiLink30_MacroList;
	  INT					iPrintLvl;



	void init()
	{
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					.set_comment("HiLink30 Macro List for test")
					//.set_options("0,1:FromPinList")
					.set_default("0,1");
	    add_param("sramAddr","long",&mSramAddr)
					.set_comment("sram start address ")
					//.set_options("0:0x18000")
					.set_default("0x18000");
	    add_param("DumpType","string",&mDumpType)
					.set_comment("Dump Type ")
					//.set_options("ByAddr:Full")
					.set_default("ByAddr");
	    add_param("count","long",&mCount);
		add_param("PrintLvl[0~8]","int",&iPrintLvl)
					.set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
					"0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					//.set_options("0:1:3:4:7:8")
					.set_default("3");

	}
	void execute()
	{
		//Add your test code here.

		long mSramAddr;
		string mDumpType;
		long mCount;
//		STRING mHiLink30_MacroList;//20211124
		INT iPrintLvl;
		static MACRO_LANE_SEL MacroLane_Sel;
		INT iDebugAnalog;
		//		static	STRING          	sTestsuiteName;
		static INT iOffline;
		static INT iCSR_check;
		//=============================================
		// Variables and MacroLane initialization
		//=============================================
		//		ON_FIRST_INVOCATION_BEGIN();
		//
		//		GET_SYSTEM_FLAG		("offline",&iOffline);
		//		GET_USER_FLAG		("CSR_atomic_operation",&iCSR_check);
		//		GET_TESTFLOW_FLAG	("debug_analog",&iDebugAnalog);
		//                stSSBandGap& SSBandGap=SSbandGap_SSBandGap;

		static STRING mPinList = "";
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

		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList);

		if (mDumpType == "Full")
			Dump_SRAM_ByWord( MacroLane_Sel);
		if (mDumpType == "ByAddr")
		{
			MACRO_DOUBLE sramData;
			for (int i = 0; i < mCount; i++)
			{
				SRAM_READ_BY_WORD( MacroLane_Sel, mSramAddr, sramData, 1,0);

				mSramAddr = mSramAddr + 2;
			}
		}
		//		INT MacroID;
		//		MacroID=MacroLane_Sel[0].MacroID;
		//		Dump_SRAM(MacroID);
		//		ON_FIRST_INVOCATION_END();

	}
};
REGISTER_TESTCLASS("DumpSramData", DumpSramData)
