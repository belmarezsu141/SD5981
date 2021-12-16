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
class RxSquelchEye_ABIST: public TestClass {

public:
	STRING 				mHiLink16_MacroList;
	STRING 				mPinList;
	STRING				mLoopbackMode;
	INT					iPrintLvl;

	/**
	 *Initialize the parameter interface to the testflow.
	 *This method is called just once after a testsuite is created.
	 *This
	 */
	void init()
	{
		add_param("H16LR_MacroList","string",&mHiLink16_MacroList)
					 .set_comment("HiLink16 Macro List for test")
					 //.set_options("0,1:FromPinList")
					 .set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
		add_param("LoopbackMode","string",&mLoopbackMode)
					 //.set_options("Bump:PreDriver:External")
					 .set_default("Bump");
		add_param("PrintLvl[0~15]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 10000(16)"
							     "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYE_PLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.set_options("0:1:3:4:7:9")
					 .set_default("3");
	}
	////////////////////////////////////////////////////////////////////////////////
	// TM Purpose:                                                                //
	// This TM is to check whether there is error count by reading register       //
	// in external loopback mode, under condition of inject certain jitter and    //
	// frequency take certain offset, Tx FIR main=40, Tx FIR pre1st/post1st=5,    //
	// Rx CTLE gain=765, CTLE boost=762, CTLE midb=222, DFE fxtap=06200,          //
	// DFE mvtap=000000.                                                          //
	// 																			  //
	// Parameters:																  //
	// 1. SetupPins: pin list to be tested										  //
	// 2. ResultPins: result pin list      										  //
	////////////////////////////////////////////////////////////////////////////////
	/**
	 *This test is invoked per site.
	 */
	void execute()
	{
		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
		static	STRING          	sTestsuiteName;
		static	INT					iOffline;
		static  MACRO_LANE_SEL 		MacroLane_Sel;

		static	LANE_DOUBLE 		Jitter;
		static	LANE_DOUBLE 		Eyeheight;

			//=============================================
			// Variables and MacroLane initialization
			//=============================================
			iOffline = 0;
			sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();

			hout.setLevel(iPrintLvl);
			hout.printsuitename(sTestsuiteName);
			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

			d2s_JTAG& jtag = d2s_JTAG::Instance();
			//=============================================
			// Device Setup
			//=============================================

			INT 				iDataWidth = DS.txRegs.gettxdwidth();
			INT 				iRateMode = DS.txRegs.gettxratemode();
			sprintf(label,"H16LRTV100_MPB_RxSquelchRBS15_SETUP_RateMode%d_DataWidth%d",iRateMode,iDataWidth);
			d2s::d2s_LABEL_BEGIN(label, Global_D2S_Mode);

				selectMacro_MB(MacroLane_Sel);
				DS.Broadcast();

				if (mLoopbackMode == "External" ) {
					DisableTxToRxSerLpbk();
				} else {
					EnableTxToRxSerLpbk(mLoopbackMode);
				}

				EnableTxPrbsGen(PRBS15);
				DS.rxRegs.setcdrfreeze(0)
						 .Write2DUT(10);
				jtag.wait(20 *0.000001);
				DS.rxRegs.setcdrfreeze(1)                			//freeze CDR, 0=Normal operation,1=freeze CDR
						 .Write2DUT(10);

			d2s::d2s_LABEL_END();


			//=============================================
			// Measurement
			//=============================================
			LANE_EYEDATA			eyeData;
			/********New Four Point EyeDiagram*********/
			GetFourPointEyeDiagram(MacroLane_Sel, CUSTpara.Data_Rate, eyeData, true);

			if (hout.IsEyePlotEn()) {
				GetEyeDiagram(MacroLane_Sel, CUSTpara.Data_Rate);
			}

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						ostringstream	plot_eyeData;
						plot_eyeData << "SiteID = " << SiteID << "\tMacroID = " << dec << MacroID <<"\tLaneID = " << dec << LaneID
									 << "\tLeft = " << eyeData[SiteID][MacroID][LaneID].leftValue << "\tRight = " << eyeData[SiteID][MacroID][LaneID].rightValue;
//						PUT_DATALOG(plot_eyeData.str());
					}
				}
			FOREACH_ACTIVESITE_END

			Jitter.init(0);
			Eyeheight.init(0);
			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						Jitter[SiteID][MacroID][LaneID] = 1 - eyeData[SiteID][MacroID][LaneID].eyeWidth;
						Eyeheight[SiteID][MacroID][LaneID] = eyeData[SiteID][MacroID][LaneID].eyeHeight;
						if (iOffline) {
							Jitter[SiteID][MacroID][LaneID] = 0.2;
							Eyeheight[SiteID][MacroID][LaneID] = 100;
						}
					}
				}
			FOREACH_ACTIVESITE_END


		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "SqhEye_Jitter", Jitter);
//		HiLink_PerLane_Judge(MacroLane_Sel, "SqhEye_EyeHeight", Eyeheight);

		return;
	}

};
REGISTER_TESTCLASS("RxSquelchEye_ABIST", RxSquelchEye_ABIST);
