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
class CONTROL_RELAY: public TestClass {
public:
	STRING 				sTxRelayState;
	INT					iPrintLvl;

	/**
	 *Initialize the parameter interface to the testflow.
	 *This method is called just once after a testsuite is created.
	 *
	 *Note: Test Method API should not be used in this method.
	 */
	void init()
	{
		add_param("TxRly_State","string",&sTxRelayState)
					 //.set_options("TESTER:ONBOARD_TERM")
					 .set_default("TESTER");
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
	// This TM is to control DUT Board Relay and channel AC/DC relay for test mode //
	//                                                                             //
	// Parameters:																   //
	// 1. TestMode: TESTER,ONBOARD_TERM 				  						   //
	/////////////////////////////////////////////////////////////////////////////////
	void execute()
	{
		STRING          	sTestsuiteName;
		sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();

		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);

		if (TXUTI != "" && CP_FT_Program == "FT") {
			Relay_Control(sTxRelayState);
		} else {
			hout(GENERAL) << "No relay to switch on/off, check if it is CP program or TXUTI == \"\"" << endl;
		}

		return;
	}

};
REGISTER_TESTCLASS("CONTROL_RELAY", CONTROL_RELAY);
