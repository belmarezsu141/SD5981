
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
class TxReceiver_Detection_ATE: public TestClass {

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
//
//		static	LANE_DOUBLE			Tx_rxdet_result;
//		static	LANE_DOUBLE			Tx_rxnodet_result;
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
//			/*** Connect PSSL AC Relay to DUT ****/
//			if (CP_FT_Program == "FT") {
//				FLEX_RELAY frelay;
//				frelay.pin("pHilink16_TX,pHilink16_RX").set("AC","OFF");
//				frelay.execute();
//				frelay.wait(0.3 ms);
//			}
//
//			//=============================================
//			// Device Setup
//			//=============================================
//			D2S_FRAMEWORK;
//
//			fr.d2s_LABEL_BEGIN("H16LRTV100_MPB_TXRECEIVER_DET_SETUP",d2sFrameWorkModeType::Enum(d2s_mode));
//
//				DS.rxRegs.addSkipCheckCSR(40);
//				DS.rxRegs.addSkipCheckCSR(31);
//
//				selectMacro_MB(MacroLane_Sel);
//				DS.Broadcast();
//				SetpmaMode();
//				SetsigdetMode();
//
//				DS.txRegs.settx_rxdet_en(1).Write2DUT(34);
//
//			fr.d2s_LABEL_END();
//
//			Tx_RxDET_Detect(MacroLane_Sel, Tx_rxdet_result);
//
//			hout(DETAIL) << "=======   NODET Start   =======" << endl;
//
//			if (CP_FT_Program == "FT")
//			{
//				if (TXUTI != "")
//				{
//					Relay_Control("TESTER");
//				}
//				/***Open AC relay to ensure cal trim value is correct***/
//				FLEX_RELAY 			frelay;
//				frelay.pin("pHilink16_TX,pHilink16_RX").set("IDLE","OFF");
//				frelay.execute();
//				frelay.wait(0.3 ms);
//				hout (GENERAL) << "********** " << "Open AC Relay" << " **********" << endl;
//			}
//
//			fr.d2s_LABEL_BEGIN("H16LRTV100_MPB_TXRECEIVER_NODET_SETUP",d2sFrameWorkModeType::Enum(d2s_mode));
//
//				selectMacro_MB(MacroLane_Sel);
//				DS.Broadcast();
//
//				DS.txRegs.settx_rxdet_en(0).Write2DUT(34);
//				DS.txRegs.settx_rxdet_en(1).Write2DUT(34);
//
//			fr.d2s_LABEL_END();
//
//			Tx_RxDET_Detect(MacroLane_Sel, Tx_rxnodet_result);
//
//			fr.d2s_LABEL_BEGIN("H16LRTV100_MPB_TXRECEIVER_DET_DISABLE",d2sFrameWorkModeType::Enum(d2s_mode));
//
//				selectMacro_MB(MacroLane_Sel);
//				DS.Broadcast();
//
//				DS.txRegs.settx_rxdet_en(0).Write2DUT(34);
//
//			fr.d2s_LABEL_END();
//
//			FOR_EACH_SITE_BEGIN();
//				INT SiteID = CURRENT_SITE_NUMBER() - 1;
//				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
//				{
//					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//
//					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
//					{
//						UINT LaneID = vLane[laneIndex];
//						if (iOffline) {
//							Tx_rxdet_result[SiteID][MacroID][LaneID] = 1;
//							Tx_rxnodet_result[SiteID][MacroID][LaneID] = 0;
//						}
//					}
//				}
//			FOR_EACH_SITE_END();
//
//		ON_FIRST_INVOCATION_END();
//
//		//=============================================
//		// Datalog
//		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "TX_RXDET_OUT", Tx_rxdet_result);
//		HiLink_PerLane_Judge(MacroLane_Sel, "TX_RXNODET_OUT", Tx_rxnodet_result);
//
//		return;
//	}

	/**
	 *This function will be invoked once the specified parameter's value is changed.
	 *@param parameterIdentifier
	 */
//	virtual void postParameterChange(const string& parameterIdentifier)
//	{
//		//Add your code
//		//Note: Test Method API should not be used in this method!
//		bool visible = (mHiLink16_MacroList == "FromPinList");
//		getParameter("PinList").setVisible(visible);
//
//
//		return;
//	}
//
//	/**
//	 *This function will be invoked once the Select Test Method Dialog is opened.
//	 */
//	virtual const string getComment() const
//	{
//		string comment = " please add your comment for this method.";
//		return comment;
//	}
};
REGISTER_TESTCLASS("TxReceiver_Detection_ATE", TxReceiver_Detection_ATE);
