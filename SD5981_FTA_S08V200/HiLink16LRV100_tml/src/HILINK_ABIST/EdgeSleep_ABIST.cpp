//#include "testmethod.hpp"

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
class RxEdgeSleep_ABIST: public TestClass {
public:
  string  				mHiLink16_MacroList;
  string  				mPinList;
  string  				mLoopbackMode;
  DOUBLE 				mJitterAmp;
  DOUBLE 				mFreqOffset;
  INT  					iPrintLvl;


  /**
   *Initialize the parameter interface to the testflow.
   *This method is called just once after a testsuite is created.
   */
	void init()
  {
    //Add your initialization code here
    //Note: Test Method API should not be used in this method!
    add_param("H16LR_MacroList", "string",  &mHiLink16_MacroList)
			  .set_default("0,1")
			  //.set_options("0:1:0,1:FromPinList")
			  .set_comment("HiLink16 Macro List for test");
    add_param("PinList","PinString", &mPinList);
    add_param("Loopback_Mode", "string",  &mLoopbackMode)
			  .set_default("Bump");
			  //.set_options("Bump:PreDriver:External");
    add_param("FreqOffset_PPM","double",&mFreqOffset)
    		  .set_default("350");
    add_param("Jitter_UI","double",&mJitterAmp)
    		  .set_default("0.25");
    add_param("PrintLvl[0~15]", "int", &iPrintLvl)
			  .set_default("3")
			  //.set_options("0:1:3:4:7:9")
			  .set_comment("Enable this flag when FlowVariable DebugLevel = 10000(16)");
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

		static	LANE_DOUBLE 		Jitter;
		static	LANE_DOUBLE 		Eyeheight;
		static	LANE_DOUBLE 		Eyewidth;
		static	LANE_DOUBLE			ErrorCount;

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

			sprintf(label,"H16LRTV100_MPB_EdgeSleep_SETUP_RateMode%d_DataWidth%d",CUSTpara.RateMode,CUSTpara.DataWidth);
			d2s::d2s_LABEL_BEGIN(label, Global_D2S_Mode);

				selectMacro_MB(MacroLane_Sel);
				DS.Broadcast();

				if (mLoopbackMode == "External" ) {
					DisableTxToRxSerLpbk();
				} else {
					EnableTxToRxSerLpbk(mLoopbackMode);
				}

				EnableTxPrbsGen(PRBS15);

				//*******************************************************
				// Insert frequecy offset and JItter;
				//*******************************************************
				JI 	JITINDEX;
				JITINDEX = JitterInjection(CUSTpara.DataWidth, CUSTpara.RateMode, CUSTpara.Data_Rate, mJitterAmp);
				INT ppmgen = FreqOffset(CUSTpara.DataWidth, CUSTpara.RateMode, mFreqOffset);

				DS.txRegs.settxalignmode(4)
						 .Write2DUT(2);

				DS.txRegs.setkfactor(0)
						 .setjitppmctrl(1)
						 .setjitfreq(JITINDEX.FREQINDEX)
						 .setjitamp(JITINDEX.AMPINDEX)
						 .setppmgen(ppmgen)
						 .Write2DUT(3);

				DS.rxRegs.setedgesleep(1)
						 .Write2DUT(45);

				DS.rxRegs.setcdrfreeze(0)
						 .Write2DUT(10);

				jtag.wait(20 *0.000001);
//				DS.rxRegs.setcdrfreeze(1)                			//freeze CDR, 0=Normal operation,1=freeze CDR
//						 .Write2DUT(10);

			d2s::d2s_LABEL_END();

			Jitter.init(0);
			Eyeheight.init(0);
			Eyewidth.init(0);
			LANE_EYEDATA					eyeData;

			ReadBert_ExpectValue(MacroLane_Sel, PRBS15, ErrorCount);

			GetFourPointEyeDiagram(MacroLane_Sel, CUSTpara.Data_Rate, eyeData);

			if (hout.IsEyePlotEn()) {
				GetEyeDiagram(MacroLane_Sel, CUSTpara.Data_Rate);
			}
			//=============================================
			// Datalog
			//=============================================
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
						Eyewidth[SiteID][MacroID][LaneID] = eyeData[SiteID][MacroID][LaneID].eyeWidth;
//						if (iOffline) {
//							Jitter[SiteID][MacroID][LaneID] = 0.1;
//							Eyeheight[SiteID][MacroID][LaneID] = 100;
//						}
					}
				}
			FOREACH_ACTIVESITE_END

		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "EdgeSleep_ErrCnt", ErrorCount);
//		HiLink_PerLane_Judge(MacroLane_Sel, "EdgeSleep_Jitter", Jitter);
//		HiLink_PerLane_Judge(MacroLane_Sel, "EdgeSleep_EyeHeight", Eyeheight);

    return;
	}

};
REGISTER_TESTCLASS("RxEdgeSleep_ABIST", RxEdgeSleep_ABIST);
