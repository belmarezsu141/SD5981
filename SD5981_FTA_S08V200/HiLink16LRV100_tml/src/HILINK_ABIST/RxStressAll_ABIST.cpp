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
class RxStressAll_ABIST: public TestClass {

public:
	STRING 				mHiLink16_MacroList;
	STRING 				mPinList;
	STRING				mLoopbackMode;
	DOUBLE 				mJitterAmp;
	DOUBLE 				mFreqOffset;
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
		add_param("FreqOffset_PPM","double",&mFreqOffset)
					 .set_default("350");
		add_param("Jitter_UI","double",&mJitterAmp)
					 .set_default("0.25");
		add_param("PrintLvl[0~15]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 10000(16)"
							     "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYE_PLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.set_options("0:1:3:4:7:9")
					 .set_default("3");
	}
	////////////////////////////////////////////////////////////////////////////////
	// TM Purpose:                                                                //
	// This TM is to check whether there is error count by reading register       //
	// in internal loopback mode, under condition of inject certain jitter and    //
	// frequency take certain offset, Tx FIR main=40, Tx FIR pre1st/post1st=5,    //
	// Rx CTLE gain=765, CTLE boost=762, CTLE midb=222, DFE fxtap=06200,          //
	// DFE mvtap=000000.                                                          //
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

		static	LANE_DOUBLE  		Jitter;
		static	LANE_DOUBLE  		Eyeheight;
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

			INT 				iDataWidth = DS.txRegs.gettxdwidth();
			INT 				iRateMode = DS.txRegs.gettxratemode();
			sprintf(label,"H16LRTV100_MPB_RXSTRESSALL_ABIST_SETUP_RateMode%d_DataWidth%d",iRateMode,iDataWidth);
			d2s::d2s_LABEL_BEGIN(label,Global_D2S_Mode);

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
				DS.txRegs.settxalignmode(4).Write2DUT(2);

				INT ppmgen = FreqOffset(iDataWidth, iRateMode, mFreqOffset);
				JI 	JITINDEX;
				JITINDEX = JitterInjection(iDataWidth, iRateMode, CUSTpara.Data_Rate, mJitterAmp);

				DS.txRegs.setjitppmctrl(1)
						 .setppmgen(ppmgen)
						 .setjitamp(JITINDEX.AMPINDEX)
						 .setjitfreq(JITINDEX.FREQINDEX)
						 .Write2DUT(3);
/*
				if (iRateMode == 2)
				{
					DS.rxRegs.setcphsofst(0x35)
							 .Write2DUT(12);
				}
*/
				DS.rxRegs.setcdrfreeze(0)
						 .Write2DUT(10);
				jtag.wait(20 *0.000001);

			d2s::d2s_LABEL_END();


			Jitter.init(0);
			Eyeheight.init(0);
			LANE_EYEDATA					eyeData;
			DOUBLE 							eyeUI_ps = 1000.0 / CUSTpara.Data_Rate;

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
						if (iOffline) {
							Jitter[SiteID][MacroID][LaneID] = 0.1;
							Eyeheight[SiteID][MacroID][LaneID] = 100;
						}
					}
				}
			FOREACH_ACTIVESITE_END


		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "Err_Cnt", ErrorCount);
//		HiLink_PerLane_Judge(MacroLane_Sel, "Jitter_Pk-Pk_UI", Jitter);
//		HiLink_PerLane_Judge(MacroLane_Sel, "EyeHeight_PT", Eyeheight);

		return;
		}

};
REGISTER_TESTCLASS("RxStressAll_ABIST", RxStressAll_ABIST);
