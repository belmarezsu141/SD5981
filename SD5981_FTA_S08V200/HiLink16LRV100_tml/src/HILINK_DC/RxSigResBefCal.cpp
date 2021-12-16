//for test method API interfaces
//#include "mapi.hpp"
//using namespace std;
//using namespace V93kLimits;

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include "TestClass.h"
//#include "CCTimer.h"
#include <UserAPI.h>
#include "type.h"
#include "HILINK_DRIVE/HiLink_Types.h"
#include <cmath>
#include <HILINK_PUG/HiLink16_PUG.h>

using namespace std;
using namespace PhxAPI;
/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class RxSigResBefCal: public TestClass {

public:
	STRING 				mHiLink16_MacroList;
	STRING 				mPinList;
	STRING 				sPinList;
	STRING 				sPinList_P;
	STRING 				sPinList_N;
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
		add_param("PrintLvl[0~15]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 10000(16)"
							     "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYE_PLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.set_options("0:1:3:4:7:9")
					 .set_default("3");

	}
	void execute()
	{

		m_TestName = TheSoft.Flow().Test().GetCurrentTestName();
		m_TestNumber  = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin  = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin  = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

		static	STRING          	sTestsuiteName;
		static	INT					iOffline;
		static  MACRO_LANE_SEL 		MacroLane_Sel;

		static 	LANE_DOUBLE 		RxSigRes_Pos;
		static 	LANE_DOUBLE 		RxSigRes_Neg;

		/**********************************************
		 * Variables and MacroLane initialization
		 **********************************************/

		GET_SYSTEM_FLAG	("offline",iOffline);
		GET_TESTSUITE_NAME(sTestsuiteName);
		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);
		GetRxPinList(MacroLane_Sel, sPinList_P, sPinList_N, sPinList);
//		D2S_FRAMEWORK;

		/**********************************************
		 * atomic operation: csr check before write
		 **********************************************/

		/***************************************************************
		 * Step 1: Config device to AC couple mode
		 *         Config device rx_term_floating = 0
		 ***************************************************************/

		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_RxSigResBefCal_setup",Global_D2S_Mode);

			selectMacro_MB(MacroLane_Sel);
			DS.Broadcast();

			DS.rxRegs.setrxcapbypass(0).Write2DUT(0); /*AC Coupling Mode*/
			DS.rxRegs.setrxterm_floating_sel(1).Write2DUT(8);
			DS.rxRegs.setrxterm_floating_en(0).Write2DUT(27); /*Sig*/

		d2s::d2s_LABEL_END();


		/***************************************************************
		 * Step 2: veriable defination
		 ***************************************************************/

		LANE_DOUBLE 		RxSigMeasVoltage1_Pos;
		LANE_DOUBLE 		RxSigMeasVoltage2_Pos;
		LANE_DOUBLE 		RxSigMeasVoltage1_Neg;
		LANE_DOUBLE 		RxSigMeasVoltage2_Neg;

		RxSigMeasVoltage1_Pos.init(0);
		RxSigMeasVoltage2_Pos.init(0);
		RxSigMeasVoltage1_Neg.init(0);
		RxSigMeasVoltage2_Neg.init(0);
		RxSigRes_Pos.init(0);
		RxSigRes_Neg.init(0);
		/***************************************************************
		 * Step 3: PPMU SETUP and do 1st measurement
		 ***************************************************************/

		DOUBLE 	mCurrentSink1_mA = 2;
		DOUBLE 	mCurrentSink2_mA = -2;

		PinArrayDouble RxSigMeasVoltage_Pos1 = PPMU_FIMV_measure(sPinList_P,mCurrentSink1_mA*mA,2,0.003,6);
		PinArrayDouble RxSigMeasVoltage_Neg1 = PPMU_FIMV_measure(sPinList_N,mCurrentSink1_mA*mA,2,0.003,6);

		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
					UINT LaneID = vLane[laneIndex];
					RxSigMeasVoltage1_Pos[SiteID][MacroID][LaneID] = RxSigMeasVoltage_Pos1.GetData(LANE_INFO[MacroID][LaneID].RX_P,SiteID);
					RxSigMeasVoltage1_Neg[SiteID][MacroID][LaneID] = RxSigMeasVoltage_Neg1.GetData(LANE_INFO[MacroID][LaneID].RX_N,SiteID);
				}
			}
		FOREACH_ACTIVESITE_END

		/***************************************************************
		 * Step 4: PPMU SETUP and do 2nd measurement
		 ***************************************************************/
		PinArrayDouble RxSigMeasVoltage_Pos2 = PPMU_FIMV_measure(sPinList_P,mCurrentSink2_mA*mA,2,0.003,6);
		PinArrayDouble RxSigMeasVoltage_Neg2 = PPMU_FIMV_measure(sPinList_N,mCurrentSink2_mA*mA,2,0.003,6);

		Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
					UINT LaneID = vLane[laneIndex];
					RxSigMeasVoltage2_Pos[SiteID][MacroID][LaneID] = RxSigMeasVoltage_Pos2.GetData(LANE_INFO[MacroID][LaneID].RX_P,SiteID);
					RxSigRes_Pos[SiteID][MacroID][LaneID] = (RxSigMeasVoltage1_Pos[SiteID][MacroID][LaneID] - RxSigMeasVoltage2_Pos[SiteID][MacroID][LaneID]) / (mCurrentSink1_mA - mCurrentSink2_mA);
					RxSigMeasVoltage2_Neg[SiteID][MacroID][LaneID] = RxSigMeasVoltage_Neg2.GetData(LANE_INFO[MacroID][LaneID].RX_N,SiteID);
					RxSigRes_Neg[SiteID][MacroID][LaneID] = (RxSigMeasVoltage1_Neg[SiteID][MacroID][LaneID] - RxSigMeasVoltage2_Neg[SiteID][MacroID][LaneID]) / (mCurrentSink1_mA - mCurrentSink2_mA);

					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_P << ": " << "Voltage at " <<  mCurrentSink1_mA <<" [mA] = " <<  RxSigMeasVoltage1_Pos[SiteID][MacroID][LaneID] << " mV" << endl;
					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_P << ": " << "Voltage at " <<  mCurrentSink2_mA <<" [mA] = " <<  RxSigMeasVoltage2_Pos[SiteID][MacroID][LaneID] << " mV" << endl;
					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_P << ": " << "Resistor = "  << RxSigRes_Pos[SiteID][MacroID][LaneID] << " Ohm" << endl;
					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_N << ": " << "Voltage at " <<  mCurrentSink1_mA <<" [mA] = " <<  RxSigMeasVoltage1_Neg[SiteID][MacroID][LaneID] << " mV" << endl;
					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_N << ": " << "Voltage at " <<  mCurrentSink2_mA <<" [mA] = " <<  RxSigMeasVoltage2_Neg[SiteID][MacroID][LaneID] << " mV" << endl;
					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_N << ": " << "Resistor = "  << RxSigRes_Neg[SiteID][MacroID][LaneID] << " Ohm" << endl;
				}
			}
		FOREACH_ACTIVESITE_END

		if (iOffline) {
			RxSigRes_Pos.init(70);
			RxSigRes_Neg.init(70);
		}

		/**********************************************
		 * Judgement and datalog
		 **********************************************/

		HiLink_PerLane_Judge(MacroLane_Sel, "RxSigResBefCal_Pos", 0.0, RxSigRes_Pos, 0.0, PIN_RXP);
		HiLink_PerLane_Judge(MacroLane_Sel, "RxSigResBefCal_Neg", 0.0, RxSigRes_Neg, 0.0, PIN_RXN);

	}
	////////////////////////////////////////////////////////////////////////////////
	// TM Purpose:                                                                //
	// This TM is for resistor measurement by using PPMU, it is to measure        //
	// voltage at tested pins twice, fist sink 5 mA and second sink 1 mA,         //
	// and calculate resistor in equation Res=(Volt1-Volt2)/(SinkCurr1-SinkCurr2).//
	//																			  //
	// Parameters:																  //
	// 1. PinList: Pin list to be tested                                          //
	// 2. currentSink1_mA: First sink current, in mA                              //
	// 3. curerntSink2_mA: Second sink current, in mA                             //
	////////////////////////////////////////////////////////////////////////////////
	/**
	 *This test is invoked per site.
	 */
//	virtual void run()
//	{
//		/**********************************************
//		 * Common definition of TM for offline flag,
//		 * test suite name, MacroLane Info etc.
//		 **********************************************/
//
//		static	STRING          	sTestsuiteName;
//		static	INT					iOffline;
//		static  MACRO_LANE_SEL 		MacroLane_Sel;
//
//		static 	LANE_DOUBLE 		RxSigRes_Pos;
//		static 	LANE_DOUBLE 		RxSigRes_Neg;
//
//		ON_FIRST_INVOCATION_BEGIN();
//
//			/**********************************************
//			 * Variables and MacroLane initialization
//			 **********************************************/
//
//			GET_SYSTEM_FLAG		("offline",&iOffline);
//			GET_TESTSUITE_NAME	(sTestsuiteName);
//			hout.setLevel(iPrintLvl);
//			hout.printsuitename(sTestsuiteName);
//			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);
//			GetRxPinList(MacroLane_Sel, sPinList_P, sPinList_N, sPinList);
//			D2S_FRAMEWORK;
//
//			/**********************************************
//			 * atomic operation: csr check before write
//			 **********************************************/
//
//			/***************************************************************
//			 * Step 1: Config device to AC couple mode
//			 *         Config device rx_term_floating = 0
//			 ***************************************************************/
//
//			fr.d2s_LABEL_BEGIN("H16LRTV100_MPB_RxSigResBefCal_setup",d2sFrameWorkModeType::Enum(d2s_mode));
//
//				selectMacro_MB(MacroLane_Sel);
//				DS.Broadcast();
//
//				DS.rxRegs.setrxcapbypass(0).Write2DUT(0); /*AC Coupling Mode*/
//				DS.rxRegs.setrxterm_floating_sel(1).Write2DUT(8);
//				DS.rxRegs.setrxterm_floating_en(0).Write2DUT(27); /*Sig*/
//
//			fr.d2s_LABEL_END();
//
//
//			/***************************************************************
//			 * Step 2: veriable defination
//			 ***************************************************************/
//
//			LANE_DOUBLE 		RxSigMeasVoltage1_Pos;
//			LANE_DOUBLE 		RxSigMeasVoltage2_Pos;
//			LANE_DOUBLE 		RxSigMeasVoltage1_Neg;
//			LANE_DOUBLE 		RxSigMeasVoltage2_Neg;
//
//			RxSigMeasVoltage1_Pos.init(0);
//			RxSigMeasVoltage2_Pos.init(0);
//			RxSigMeasVoltage1_Neg.init(0);
//			RxSigMeasVoltage2_Neg.init(0);
//			RxSigRes_Pos.init(0);
//			RxSigRes_Neg.init(0);
//			/***************************************************************
//			 * Step 3: PPMU SETUP and do 1st measurement
//			 ***************************************************************/
//
//			DOUBLE 						mCurrentSink1_mA = 2;
//			DOUBLE 						mCurrentSink2_mA = -2;
//			PPMU_SETTING 				Set_P,Set_N;
//			PPMU_RELAY   				Rly_PPMU_ON_P,Rly_PPMU_ON_N,Rly_AC_ON;
//			PPMU_CLAMP   				Clamp_on_P,Clamp_on_N,Clamp_off_P,Clamp_off_N;
//			PPMU_MEASURE 				Meas_P,Meas_N;
//			TASK_LIST    				Task_P,Task_N,TaskSetup_P,TaskSetup_N,TaskClean;
//			Rly_PPMU_ON_P.pin(sPinList_P).status("PPMU_ON");
//			Rly_PPMU_ON_P.pin(sPinList_N).status("ALL_OFF");
//			Rly_PPMU_ON_P.wait(1.3 ms);
//			Rly_PPMU_ON_P.wait(1.3 ms);
//			Rly_PPMU_ON_N.pin(sPinList_N).status("PPMU_ON");
//			Rly_PPMU_ON_N.pin(sPinList_P).status("ALL_OFF");
//			Rly_PPMU_ON_N.wait(1.3 ms);
//			Clamp_on_P.pin(sPinList_P).status("CLAMP_ON").low(-0.8 V).high(0.8 V);
//			Clamp_off_P.pin(sPinList_P).status("CLAMP_OFF");
//			Clamp_on_N.pin(sPinList_P).status("CLAMP_ON").low(-0.8 V).high(0.8 V);
//			Clamp_off_N.pin(sPinList_P).status("CLAMP_OFF");
//			Rly_AC_ON.pin(sPinList).status("AC_ON");
//			Rly_AC_ON.wait(1.3 ms);
//			Set_P.pin(sPinList_P).iForce(mCurrentSink1_mA mA).iRange(mCurrentSink1_mA mA).min(0 V).max(2 V);
//			Set_N.pin(sPinList_N).iForce(mCurrentSink1_mA mA).iRange(mCurrentSink1_mA mA).min(0 V).max(2 V);
//			Meas_P.pin(sPinList_P).execMode(TM::OVAL);
//			Meas_N.pin(sPinList_N).execMode(TM::OVAL);
//			TaskSetup_P.add(Clamp_on_P).add(Rly_PPMU_ON_P).add(Clamp_off_P).setup();
//			TaskSetup_N.add(Clamp_on_N).add(Rly_PPMU_ON_N).add(Clamp_off_N).setup();
//			Task_P.add(Set_P).add(Meas_P).setup();
//			Task_N.add(Set_N).add(Meas_N).setup();
//			TaskClean.add(Rly_AC_ON).setup();
//
//			TaskSetup_P.execute();
//			Task_P.execute();
//
//			TaskSetup_N.execute();
//			Task_N.execute();
//
//			FOR_EACH_SITE_BEGIN();
//				INT SiteID = CURRENT_SITE_NUMBER() - 1;
//				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
//					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
//						UINT LaneID = vLane[laneIndex];
//						RxSigMeasVoltage1_Pos[SiteID][MacroID][LaneID] = Meas_P.getValue(LANE_INFO[MacroID][LaneID].RX_P) / (1 mV);
//						RxSigMeasVoltage1_Neg[SiteID][MacroID][LaneID] = Meas_N.getValue(LANE_INFO[MacroID][LaneID].RX_N) / (1 mV);
//					}
//				}
//			FOR_EACH_SITE_END();
//
//			/***************************************************************
//			 * Step 4: PPMU SETUP and do 2nd measurement
//			 ***************************************************************/
//
//			Set_P.pin(sPinList_P).iForce(mCurrentSink2_mA mA).iRange(mCurrentSink2_mA mA).min(0 V).max(2 V);
//			Set_N.pin(sPinList_N).iForce(mCurrentSink2_mA mA).iRange(mCurrentSink2_mA mA).min(0 V).max(2 V);
//			TaskSetup_P.execute();			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);
//			Task_P.execute();
//
//			TaskSetup_N.execute();
//			Task_N.execute();
//
//			FOR_EACH_SITE_BEGIN();
//				INT SiteID = CURRENT_SITE_NUMBER() - 1;
//				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
//					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
//						UINT LaneID = vLane[laneIndex];
//						RxSigMeasVoltage2_Pos[SiteID][MacroID][LaneID] = Meas_P.getValue(LANE_INFO[MacroID][LaneID].RX_P) / (1 mV);
//						RxSigRes_Pos[SiteID][MacroID][LaneID] = (RxSigMeasVoltage1_Pos[SiteID][MacroID][LaneID] - RxSigMeasVoltage2_Pos[SiteID][MacroID][LaneID]) / (mCurrentSink1_mA - mCurrentSink2_mA);
//						RxSigMeasVoltage2_Neg[SiteID][MacroID][LaneID] = Meas_N.getValue(LANE_INFO[MacroID][LaneID].RX_N) / (1 mV);
//						RxSigRes_Neg[SiteID][MacroID][LaneID] = (RxSigMeasVoltage1_Neg[SiteID][MacroID][LaneID] - RxSigMeasVoltage2_Neg[SiteID][MacroID][LaneID]) / (mCurrentSink1_mA - mCurrentSink2_mA);
//
//						hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_P << ": " << "Voltage at " <<  mCurrentSink1_mA <<" [mA] = " <<  RxSigMeasVoltage1_Pos[SiteID][MacroID][LaneID] << " mV" << endl;
//						hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_P << ": " << "Voltage at " <<  mCurrentSink2_mA <<" [mA] = " <<  RxSigMeasVoltage2_Pos[SiteID][MacroID][LaneID] << " mV" << endl;
//						hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_P << ": " << "Resistor = "  << RxSigRes_Pos[SiteID][MacroID][LaneID] << " Ohm" << endl;
//						hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_N << ": " << "Voltage at " <<  mCurrentSink1_mA <<" [mA] = " <<  RxSigMeasVoltage1_Neg[SiteID][MacroID][LaneID] << " mV" << endl;
//						hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_N << ": " << "Voltage at " <<  mCurrentSink2_mA <<" [mA] = " <<  RxSigMeasVoltage2_Neg[SiteID][MacroID][LaneID] << " mV" << endl;
//						hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_N << ": " << "Resistor = "  << RxSigRes_Neg[SiteID][MacroID][LaneID] << " Ohm" << endl;
//					}
//				}
//			FOR_EACH_SITE_END();
//
//			if (iOffline) {
//				RxSigRes_Pos.init(70);
//				RxSigRes_Neg.init(70);
//			}
//
//			TaskClean.execute();
//
//		ON_FIRST_INVOCATION_END();
//
//		/**********************************************
//		 * Judgement and datalog
//		 **********************************************/
//
//		HiLink_PerLane_Judge(MacroLane_Sel, "RxSigResBefCal_Pos", RxSigRes_Pos, PIN_RXP);
//		HiLink_PerLane_Judge(MacroLane_Sel, "RxSigResBefCal_Neg", RxSigRes_Neg, PIN_RXN);
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
REGISTER_TESTCLASS("RxSigResBefCal", RxSigResBefCal);
