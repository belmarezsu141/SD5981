//for test method API interfaces
//#include "mapi.hpp"
//using namespace std;
//using namespace V93kLimits;

#include <Common_Func/HiLink_Common_Func.h>
/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class SSC_RxStressAll_ATE: public TestClass {

public:
	STRING 				mHiLink16_MacroList;
	STRING 				mPinList;
	STRING 				sPinList;
	STRING 				sPinList_P;
	STRING 				sPinList_N;
	INT 				mPPM_Neg;
	INT 				mPPM_Pos;
	DOUBLE 				mSineJitterAmp_UI;
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
		add_param("PinList","PinString",&mPinList);
		add_param("FreqOffset_NEG_PPM","int",&mPPM_Neg);
		add_param("FreqOffset_POS_PPM","int",&mPPM_Pos);
		add_param("Jitter_UI","double",&mSineJitterAmp_UI)
					 .set_default("0.25");
		add_param("PrintLvl[0~15]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 10000(16)"
							     "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYE_PLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.set_options("0:1:3:4:7:9")
					 .set_default("3");
	}
	void execute()
		{

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
//		static	LANE_DOUBLE			ErrorCount_PosPPM;
//		static	LANE_DOUBLE 		Jitter_PosPPM;
//		static	LANE_DOUBLE 		Eyeheight_PosPPM;
//		static	LANE_DOUBLE			ErrorCount_NegPPM;
//		static	LANE_DOUBLE 		Jitter_NegPPM;
//		static	LANE_DOUBLE 		Eyeheight_NegPPM;
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
//			GetRxPinList(MacroLane_Sel, sPinList_P, sPinList_N, sPinList);
//
//			STRING 				mSpec = "FrequencyOffset";
//			DOUBLE 				dOrgVal = Primary.getSpecification().getSpecValue(mSpec);
//
//			/*** Connect PSSL AC Relay to DUT ****/
//			if (CP_FT_Program == "FT") {
//				FLEX_RELAY frelay;
//				frelay.pin("pHilink16_TX,pHilink16_RX").set("AC","OFF");
//				frelay.execute();
//				frelay.wait(0.3 ms);
//			}
//
//			D2S_FRAMEWORK;
//			//=============================================
//			// Device Setup
//			//=============================================
//
//			/************ inject  Jitter **************/
//			DOUBLE SineJitter_Amp_UI = mSineJitterAmp_UI;
//			DOUBLE SineJitter_Freq_MHz = CUSTpara.Data_Rate * 1000 / 1667;
//			setJitterInjection(SineJitter_Amp_UI * 1000 / (CUSTpara.Data_Rate * 2) ps, SineJitter_Freq_MHz MHz, sPinList_P);
//			hout(DETAIL) << "Current value of Jitter is: " <<  SineJitter_Amp_UI << "UI, " << SineJitter_Freq_MHz << "MHz" << endl;
//
//
//			/****************** Neg PPM Test begin *********************/
//			hout(GENERAL) << "**** Insert Neg PPM to datastream of PSSL ****" << endl;
//			DOUBLE 				dChangeVal = mPPM_Neg;
//			try {
//				Primary.getSpecification().change(mSpec,dChangeVal);
//				FLUSH(TM::APRM);
//			} catch(Error &error) {
//				Primary.getSpecification().change(mSpec,dOrgVal);
//				FLUSH(TM::APRM);
//				ERROR_EXIT(TM::RETURN_TO_FLOW);
//			}
//
//			fr.d2s_LABEL_BEGIN("H16LRTV100_MPB_SSC_RxStrsAll_reset_CDR",d2sFrameWorkModeType::Enum(d2s_mode));
//
//				selectMacro_MB(MacroLane_Sel);
//				DS.Broadcast();
//				DS.rxRegs.setcdrrstb(0).Write2DUT(11);
//				DS.rxRegs.setcdrrstb(1).Write2DUT(11);
//
//				jtag.wait(20 us);
//
//			fr.d2s_LABEL_END();
//
//			ReadBert_ExpectValue(MacroLane_Sel, PRBS15, ErrorCount_NegPPM, "ATE");
//
//			LANE_EYEDATA			eyeData_NegPPM;
//			/********New Four Point EyeDiagram*********/
//			GetFourPointEyeDiagram(MacroLane_Sel, CUSTpara.Data_Rate, eyeData_NegPPM, true, "ATE");
//
//			if (hout.IsEyePlotEn()) {
//				GetEyeDiagram(MacroLane_Sel, CUSTpara.Data_Rate, "ATE");
//			}
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
//						ostringstream	plot_eyeData;
//						plot_eyeData << "NegPPM:\tSiteID = " << SiteID << "\tMacroID = " << dec << MacroID <<"\tLaneID = " << dec << LaneID
//									 << "\tLeft = " << eyeData_NegPPM[SiteID][MacroID][LaneID].leftValue << "\tRight = " << eyeData_NegPPM[SiteID][MacroID][LaneID].rightValue;
//						PUT_DATALOG(plot_eyeData.str());
//					}
//				}
//			FOR_EACH_SITE_END();
//
//
//			/****************** Pos PPM Test begin *********************/
//			hout(GENERAL) << "**** Insert Pos PPM to datastream of PSSL ****" << endl;
//			dChangeVal = mPPM_Pos;
//			try {
//				Primary.getSpecification().change(mSpec,dChangeVal);
//				FLUSH(TM::APRM);
//			} catch(Error &error) {
//				Primary.getSpecification().change(mSpec,dOrgVal);
//				FLUSH(TM::APRM);
//				ERROR_EXIT(TM::RETURN_TO_FLOW);
//			}
//
//			fr.d2s_LABEL_BEGIN("H16LRTV100_MPB_SSC_RxStrsAll_reset_CDR",d2sFrameWorkModeType::Enum(d2s_mode));
//
//				selectMacro_MB(MacroLane_Sel);
//				DS.Broadcast();
//				DS.rxRegs.setcdrrstb(0).Write2DUT(11);
//				DS.rxRegs.setcdrrstb(1).Write2DUT(11);
//
//				jtag.wait(20 us);
//
//			fr.d2s_LABEL_END();
//
//			ReadBert_ExpectValue(MacroLane_Sel, PRBS15, ErrorCount_PosPPM, "ATE");
//
//			LANE_EYEDATA			eyeData_PosPPM;
//			/********New Four Point EyeDiagram*********/
//			GetFourPointEyeDiagram(MacroLane_Sel, CUSTpara.Data_Rate, eyeData_PosPPM, true, "ATE");
//
//			if (hout.IsEyePlotEn()) {
//				GetEyeDiagram(MacroLane_Sel, CUSTpara.Data_Rate, "ATE");
//			}
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
//						ostringstream	plot_eyeData;
//						plot_eyeData << "PosPPM:\tSiteID = " << SiteID << "\tMacroID = " << dec << MacroID <<"\tLaneID = " << dec << LaneID
//									 << "\tLeft = " << eyeData_PosPPM[SiteID][MacroID][LaneID].leftValue << "\tRight = " << eyeData_PosPPM[SiteID][MacroID][LaneID].rightValue;
//						PUT_DATALOG(plot_eyeData.str());
//					}
//				}
//			FOR_EACH_SITE_END();
//
//			//=============================================
//			// Restore
//			//=============================================
//			Primary.getSpecification().change(mSpec,dOrgVal);
//			FLUSH(TM::APRM);
//
//			JITTER_INJECTION_SET::deselectGlobally();
//			JITTER_INJECTION_SET::removeAll();
//			JITTER_INJECTION_SET::resetJitterModulator(sPinList_P);
//
//			Jitter_PosPPM.init(0);
//			Eyeheight_PosPPM.init(0);
//			Jitter_NegPPM.init(0);
//			Eyeheight_NegPPM.init(0);
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
//						Jitter_PosPPM[SiteID][MacroID][LaneID] = 1 - eyeData_PosPPM[SiteID][MacroID][LaneID].eyeWidth;
//						Eyeheight_PosPPM[SiteID][MacroID][LaneID] = eyeData_PosPPM[SiteID][MacroID][LaneID].eyeHeight;
//						Jitter_NegPPM[SiteID][MacroID][LaneID] = 1 - eyeData_NegPPM[SiteID][MacroID][LaneID].eyeWidth;
//						Eyeheight_NegPPM[SiteID][MacroID][LaneID] = eyeData_NegPPM[SiteID][MacroID][LaneID].eyeHeight;
//						if (iOffline) {
//							Jitter_PosPPM[SiteID][MacroID][LaneID] = 0.1;
//							Eyeheight_PosPPM[SiteID][MacroID][LaneID] = 100;
//							Jitter_NegPPM[SiteID][MacroID][LaneID] = 0.1;
//							Eyeheight_NegPPM[SiteID][MacroID][LaneID] = 100;
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
//		HiLink_PerLane_Judge(MacroLane_Sel, "SSC_StrsAll_ErrCnt_Pos", ErrorCount_PosPPM);
//		HiLink_PerLane_Judge(MacroLane_Sel, "SSC_StrsAll_Jitter_Pos", Jitter_PosPPM);
//		HiLink_PerLane_Judge(MacroLane_Sel, "SSC_StrsAll_EyeHeight_Pos", Eyeheight_PosPPM);
//		HiLink_PerLane_Judge(MacroLane_Sel, "SSC_StrsAll_ErrCnt_Neg", ErrorCount_NegPPM);
//		HiLink_PerLane_Judge(MacroLane_Sel, "SSC_StrsAll_Jitter_Neg", Jitter_NegPPM);
//		HiLink_PerLane_Judge(MacroLane_Sel, "SSC_StrsAll_EyeHeight_Neg", Eyeheight_NegPPM);
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
REGISTER_TESTCLASS("SSC_RxStressAll_ATE", SSC_RxStressAll_ATE);
