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
class SSC_RxJitterTol_ATE: public TestClass {

public:
	STRING 				mHiLink16_MacroList;
	STRING 				mPinList;
	STRING 				sPinList;
	STRING 				sPinList_P;
	STRING 				sPinList_N;
	DOUBLE 				SineJitter_Freq_MHz;
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

	////////////////////////////////////////////////////////////////////////////////
	// TM Purpose:                                                                //
	// This TM is to record the maximum Tx jitter injection value, with which     //
	// there is no error count by reading register in internal loopback mode.     //
	// The Tx jitter injection by setting JITFREQ and JITAMPL register step by    //
	// step.
	//																			  //
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
//		static	LANE_DOUBLE 		MaxJitterAmp;
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
//			/***************************************************************
//			 * Step 1: Search Jitter
//			 ***************************************************************/
//
//			DOUBLE 					Amp_Start_UI = 0.3;
//			DOUBLE 					Amp_Stop_UI = 1;
//			DOUBLE 					Amp_Step_UI = 0.1;
//			JITTER_INJECTION_SET 	jitterinject_sine("Sine");
//			LANE_DOUBLE 			ErrorCount;
//			LANE_INT 				FindFlag;
//			MaxJitterAmp.init(0);
//			FindFlag.init(0);
//			DOUBLE 					SineJitter_Amp_UI = Amp_Start_UI;
//			INT 					iFind_All = 0;
//			while (SineJitter_Amp_UI <= Amp_Stop_UI && ((iFind_All == 0) || (d2s_mode == 1)))
//			{
//				//todo:call d2s_begin_end_block template and setup for each step
//				SineJitter_Freq_MHz = CUSTpara.Data_Rate * 1000 / 1667;
//				setJitterInjection(SineJitter_Amp_UI * 1000 / (CUSTpara.Data_Rate * 2) ps, SineJitter_Freq_MHz MHz, sPinList_P);
//				//todo:print spec value for each step
//				hout(DETAIL) << "========== SineJitter_Amp_UI = " << dec << SineJitter_Amp_UI << " ==========" << endl;
//
//				//todo:call sub func ReadBert_ExpectValue()
//				ReadBert_ExpectValue(MacroLane_Sel, PRBS15, ErrorCount, "ATE");
//
//				//todo:Other method for debugging delete this todo bolck if not use
//				if (hout.IsEyePlotEn()) {
//					GetEyeDiagram(MacroLane_Sel, CUSTpara.Data_Rate, "ATE");
//				}
//
//				//call sub func Update_LaneData_InTolerance()
//				iFind_All = Update_LaneData_InTolerance(MacroLane_Sel, SineJitter_Amp_UI, ErrorCount, MaxJitterAmp, FindFlag);
//
//				//todo:update spec here
//				SineJitter_Amp_UI += Amp_Step_UI;
//			}
//
//			//=============================================
//			//restore
//			//=============================================
//			JITTER_INJECTION_SET::deselectGlobally();
//			JITTER_INJECTION_SET::removeAll();
//			JITTER_INJECTION_SET::resetJitterModulator(sPinList_P);
//
//		ON_FIRST_INVOCATION_END();
//
//		/*=======================*
//		 * Judgement and datalog *
//		 *=======================*/
//
//		HiLink_PerLane_Judge(MacroLane_Sel, "MAX_JitterTol", MaxJitterAmp);
//
//		return;
//	}

	/**
	 *This function will be invoked once the specified parameter's value is changed.
	 *@param parameterIdentifier
	 */
//	virtual void postParameterChange(const string& parameterIdentifier)
//	{
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
REGISTER_TESTCLASS("SSC_RxJitterTol_ATE", SSC_RxJitterTol_ATE);
