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
class KEEP_ALIVE: public TestClass {
public:
	STRING 				TestMode;
	INT					iPrintLvl;


	/**
	 *Initialize the parameter interface to the testflow.
	 *This method is called just once after a testsuite is created.
	 *
	 *Note: Test Method API should not be used in this method.
	 */
	void init()
	{
		add_param("TestMode", "string", &TestMode)
					 .set_comment("the pins the test will be configured for")
					 //.set_options("CLK_KEEP_ALIVE:DISABLE_ALIVE:LPN")
					 .set_default("CLK_KEEP_ALIVE");
		add_param("PrintLvl[0~15]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 10000(16)"
							     "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYE_PLOT; 1000 = REG_ACCESS; Can be Assembled")
								 //.set_options("0:1:3:4:7:9")
					 .set_default("3");
	}
	/**
	 *This test is invoked per site.
	 */
	/////////////////////////////////////////////////////////////////////////////////
	// TM Purpose:                                                                 //
	// This TM is to control CLK port keep alive with FTCG FW Command and          //
	// also use for setup LPN                                                      //
	//                                                                             //
	// Parameters:																   //
	// 1. TestMode: CLK_KEEP_ALIVE,DISABLE_ALIVE,LPN							   //
	/////////////////////////////////////////////////////////////////////////////////
	void execute()
	{
		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
		static	STRING          	sTestsuiteName;

			//=============================================
			// Variables and MacroLane initialization
			//=============================================
			sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
			hout.setLevel(iPrintLvl);
			hout.printsuitename(sTestsuiteName);


//			if (TestMode == "CLK_KEEP_ALIVE") {
//				hout(GENERAL) << "Test Mode = " << TestMode << endl;
//				FW_TASK("APRM CNL;");
//				FW_TASK("FTCG SKPR,ON,(pHilink_CLK)");
////				FW_TASK("FTCG SKPR,ON,(pCLKIn)");
//			} else if (TestMode == "DISABLE_ALIVE") {
//				hout(GENERAL) << "Test Mode = " << TestMode << endl;
//				FW_TASK("FTCG SKPR,OFF,(@@)");
//			}

		return;
	}
};
REGISTER_TESTCLASS("KEEP_ALIVE",KEEP_ALIVE);
