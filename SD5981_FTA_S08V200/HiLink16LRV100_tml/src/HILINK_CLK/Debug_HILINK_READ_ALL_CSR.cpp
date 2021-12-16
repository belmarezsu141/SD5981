//for test method API interfaces
//#include "mapi.hpp"
//using namespace std;
//using namespace V93kLimits;

#include <HILINK_PUG/HiLink16_PUG.h>
/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class Debug_HILINK_READ_ALL_CSR: public TestClass {

public:
	STRING 				mHiLink16_MacroList;
	STRING				mPinList;
	STRING 				mTotalCsNum;
	INT					iPrintLvl;
	/**
	*Initialize the parameter interface to the testflow.
	*This method is called just once after a testsuite is created.
	*/

	void init()
	{
		add_param("H16LR_MacroList","string",&mHiLink16_MacroList)
					 .set_comment("HiLink16 Macro List for test")
					 //.set_options("0,1:FromPinList")
					 .set_default("0,1");
		add_param("PinList","PinString",&mPinList);
		add_param("CsNumToReadCsr","string",&mTotalCsNum)
					 .set_comment("The Max number of CS whose csr will be read")
					 //.set_options("1,1,1,1,1,1,1:2,2,2,2,1,2,2")
					 .set_default("2,2,2,2,1,2,2");
		add_param("PrintLvl[0~15]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 10000(16)"
							     "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYE_PLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.set_options("0:1:3:4:7:9")
					 .set_default("3");
	}

	void execute()
		{
		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
		static	STRING          	sTestsuiteName;
		static	INT					iOffline;
		static  MACRO_LANE_SEL 		MacroLane_Sel;

			//=============================================
			// Variables and MacroLane initialization
			//=============================================
			iOffline = 0;
			sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();

			hout.setLevel(iPrintLvl);
			hout.printsuitename(sTestsuiteName);
			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

			FWreadDefaultRegisters2CSR(MacroLane_Sel);

		}

};
REGISTER_TESTCLASS("Debug_HILINK_READ_ALL_CSR", Debug_HILINK_READ_ALL_CSR);



