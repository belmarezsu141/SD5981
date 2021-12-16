
//for test method API interfaces
//#include "mapi.hpp"
//using namespace std;


#include <Common_Func/HiLink_Common_Func.h>

/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class SSC_CLK_Setup: public TestClass {
public:
	STRING 				mHiLink16_MacroList;
	STRING 				mPinList;
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
		add_param("PrintLvl[0~15]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 10000(16)"
							     "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYE_PLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.set_options("0:1:3:4:7:9")
					 .set_default("3");
	}
	void execute()
		{

		}
	/**
	*This test is invoked per site.
	*/
//	virtual void run()
//	{
//		//=============================================
//		// Common definition of TM for offline flag,
//		// d2s mode, debug mode, test suite name, etc.
//		//=============================================
//		static	STRING          	sTestsuiteName;
//		static	INT					iOffline;
//		static  MACRO_LANE_SEL 		MacroLane_Sel;
//
//		ON_FIRST_INVOCATION_BEGIN();
//
//			//=============================================
//			// Variables and MacroLane initialization
//			//=============================================
//			GET_SYSTEM_FLAG		("offline",&iOffline);
//			GET_TESTSUITE_NAME	(sTestsuiteName);
//			hout.setLevel(iPrintLvl);
//			hout.printsuitename(sTestsuiteName);
//			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);
//
//
//			/*** Connect PSSL AC Relay to DUT ****/
//			if (CP_FT_Program == "FT") {
//				FLEX_RELAY frelay;
//				frelay.pin("pHilink16_TX,pHilink16_RX").set("AC","OFF");
//				frelay.wait(0.3 ms);
//				frelay.execute();
//			}
//
//			//=============================================
//			// Device Setup
//			//=============================================
//			D2S_FRAMEWORK;
//
//			sprintf(label,"H16LRTV100_MPB_SSC_CLK_SETUP_RateMode%d_DataWidth%d",CUSTpara.RateMode,CUSTpara.DataWidth);
//			fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
//
//				selectMacro_MB(MacroLane_Sel);
//				DS.Broadcast();
//
//				EnableTxPrbsGen(Custom_CLK,true);
//
//			fr.d2s_LABEL_END();
//
//		ON_FIRST_INVOCATION_END();
//		return;
//	}

  /**
   *This function will be invoked once the specified parameter's value is changed.
   *@param parameterIdentifier
   */
//  virtual void postParameterChange(const string& parameterIdentifier)
//  {
//    //Add your code
//    //Note: Test Method API should not be used in this method!
//	bool visible = (mHiLink16_MacroList == "FromPinList");
//	getParameter("PinList").setVisible(visible);
//
//
//    return;
//  }
//
//  /**
//   *This function will be invoked once the Select Test Method Dialog is opened.
//   */
//  virtual const string getComment() const
//  {
//    string comment = " please add your comment for this method.";
//    return comment;
//  }
};
REGISTER_TESTCLASS("SSC_CLK_Setup", SSC_CLK_Setup);
