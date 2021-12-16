
//for test method API interfaces
//#include "mapi.hpp"
//using namespace std;

#include <HILINK_PUG/HiLink16_PUG.h>
/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class TxReceiver_Detection_ABIST: public TestClass {

public:
	STRING 				mHiLink16_MacroList;
	STRING 				mPinList;
	STRING				mLoopbackMode;
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
//		add_param("PinList","PinString",&mPinList);
		add_param("Loopback_Mode","string",&mLoopbackMode)
					 //.set_options("Bump:PreDriver:External")
					 .set_default("Bump");
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


		static	LANE_DOUBLE			Tx_rxdet_result;
		static	LANE_DOUBLE			Tx_rxnodet_result;

			//=============================================
			// Variables and MacroLane initialization
			//=============================================
			iOffline = 0;
			sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
			hout.setLevel(iPrintLvl);
			hout.printsuitename(sTestsuiteName);
			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

			//=============================================
			// Device Setup
			//=============================================
			d2s_JTAG& jtag = d2s_JTAG::Instance();

			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_TXRECEIVER_DET_SETUP",Global_D2S_Mode);

				DS.rxRegs.addSkipCheckCSR(40);

				selectMacro_MB(MacroLane_Sel);
				DS.Broadcast();

				if (mLoopbackMode == "External" ) {
					DisableTxToRxSerLpbk();
				} else {
					EnableTxToRxSerLpbk(mLoopbackMode);
				}

				SetpmaMode();

				DS.txRegs.settx_rxdet_en(1).Write2DUT(34);

			d2s::d2s_LABEL_END();

			Tx_RxDET_Detect(MacroLane_Sel, Tx_rxdet_result);

			hout(DETAIL) << "=======   NODET Start   =======" << endl;



			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_TXRECEIVER_NODET_SETUP",Global_D2S_Mode);

				selectMacro_MB(MacroLane_Sel);
				DS.Broadcast();

				DS.rxRegs.setrxterm_floating_sel(1).Write2DUT(8);
				DS.rxRegs.setrxterm_floating_en(1).Write2DUT(27);

				DS.txRegs.settx_rxdet_en(0).Write2DUT(34);
				DS.txRegs.settx_rxdet_en(1).Write2DUT(34);


			d2s::d2s_LABEL_END();

			Tx_RxDET_Detect(MacroLane_Sel, Tx_rxnodet_result);

			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_TXRECEIVER_DET_DISABLE",Global_D2S_Mode);

				selectMacro_MB(MacroLane_Sel);
				DS.Broadcast();

				DS.txRegs.settx_rxdet_en(0).Write2DUT(34);

			d2s::d2s_LABEL_END();

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						if (iOffline) {
							Tx_rxdet_result[SiteID][MacroID][LaneID] = 1;
							Tx_rxnodet_result[SiteID][MacroID][LaneID] = 0;
						}
					}
				}
			FOREACH_ACTIVESITE_END


		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "TX_RXDET_OUT", Tx_rxdet_result);
//		HiLink_PerLane_Judge(MacroLane_Sel, "TX_RXNODET_OUT", Tx_rxnodet_result);

		return;
	}

};
REGISTER_TESTCLASS("TxReceiver_Detection_ABIST", TxReceiver_Detection_ABIST);
