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
/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class RxSigResAftCal: public TestClass {

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

		static	LANE_DOUBLE 		MinRes_Pos;
		static	LANE_DOUBLE 		MinRes_Neg;
		static	LANE_DOUBLE 		MaxRes_Pos;
		static	LANE_DOUBLE 		MaxRes_Neg;

		/**********************************************
		 * Variables and MacroLane initialization
		 **********************************************/

		GET_SYSTEM_FLAG	("offline",iOffline);
		GET_TESTSUITE_NAME	(sTestsuiteName);
		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);
		GetRxPinList(MacroLane_Sel, sPinList_P, sPinList_N, sPinList);
//			D2S_FRAMEWORK;

		/**********************************************
		 * atomic operation: csr check before write
		 **********************************************/

		/***************************************************************
		 * Step 1: Config device to AC couple mode (in calibration)
		 *         Config device rx_term_floating = 0
		 ***************************************************************/

		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_RxSigResAftCal_setup",Global_D2S_Mode);

			selectMacro_MB(MacroLane_Sel);
			DS.Broadcast();

			DS.rxRegs.setrxcapbypass(0).Write2DUT(0); /*AC Coupling Mode*/

			DS.rxRegs.setrxterm_floating_en(0).Write2DUT(27);/*floating_en = 0  Sig*/
			DS.rxRegs.setrxterm_floating_sel(1).Write2DUT(8);

		d2s::d2s_LABEL_END();

		/***************************************************************
		 * Step 2: veriable defination
		 ***************************************************************/

		LANE_DOUBLE 		RxSigMeasCurrent_Pos;
		LANE_DOUBLE 		RxSigMeasCurrent_Neg;
		LANE_DOUBLE			RxSigMeasRes_Pos;
		LANE_DOUBLE			RxSigMeasRes_Neg;
		LANE_DOUBLE			RxSigMeasCurrent_PrevStep_Pos;
		LANE_DOUBLE			RxSigMeasCurrent_PrevStep_Neg;

		RxSigMeasCurrent_Pos.init(0);
		RxSigMeasCurrent_Neg.init(0);
		RxSigMeasRes_Pos.init(0);
		RxSigMeasRes_Neg.init(0);
		MinRes_Pos.init(1e9);
		MinRes_Neg.init(1e9);
		MaxRes_Pos.init(0);
		MaxRes_Neg.init(0);
		RxSigMeasCurrent_PrevStep_Pos.init(0);
		RxSigMeasCurrent_PrevStep_Neg.init(0);

		/***************************************************************
		 * Step 3: PPMU SETUP and do measurement
		 ***************************************************************/

		DOUBLE 				mRange_vol = 500;
		DOUBLE 				mStep_vol = 50;
		PinArrayDouble RxMeasureRlt_Pos;
		PinArrayDouble RxMeasureRlt_Neg;
		for (UINT step = 0; step <= mRange_vol / mStep_vol; step ++) {
			RxMeasureRlt_Pos = PPMU_FVMI_measure(sPinList_P,mStep_vol * step*mV,10*mA,0.003,4,true);

			hout(DETAIL) << "Currently force Voltage = " << mStep_vol * step << "mV" << endl;

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
						UINT LaneID = vLane[laneIndex];
						RxSigMeasCurrent_Pos[SiteID][MacroID][LaneID] = RxMeasureRlt_Pos.GetData(LANE_INFO[MacroID][LaneID].RX_P,SiteID);
						RxSigMeasRes_Pos[SiteID][MacroID][LaneID] = mStep_vol / (RxSigMeasCurrent_Pos[SiteID][MacroID][LaneID] - RxSigMeasCurrent_PrevStep_Pos[SiteID][MacroID][LaneID]);

						if(step != 0) {
							if(RxSigMeasRes_Pos[SiteID][MacroID][LaneID] > MaxRes_Pos[SiteID][MacroID][LaneID]) {
								MaxRes_Pos[SiteID][MacroID][LaneID] = RxSigMeasRes_Pos[SiteID][MacroID][LaneID];
							}
							if(RxSigMeasRes_Pos[SiteID][MacroID][LaneID] < MinRes_Pos[SiteID][MacroID][LaneID]) {
								MinRes_Pos[SiteID][MacroID][LaneID] = RxSigMeasRes_Pos[SiteID][MacroID][LaneID];
							}
							hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_P
										 << ":Current  = " << RxSigMeasCurrent_Pos[SiteID][MacroID][LaneID] << " [mA]" << endl;
							hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_P
										 << ":Previous = " << RxSigMeasCurrent_PrevStep_Pos[SiteID][MacroID][LaneID]
										 << " [mA], Res= " << RxSigMeasRes_Pos[SiteID][MacroID][LaneID] << " [Ohm]" << endl;
						}
						RxSigMeasCurrent_PrevStep_Pos[SiteID][MacroID][LaneID] = RxSigMeasCurrent_Pos[SiteID][MacroID][LaneID];
					}
				}
			FOREACH_ACTIVESITE_END
		}

		for (UINT step = 0; step <= mRange_vol / mStep_vol; step ++) {
			RxMeasureRlt_Neg = PPMU_FVMI_measure(sPinList_N,mStep_vol * step*mV,10*mA,0.003,6,true);
			hout(DETAIL) << "Currently force Voltage = " << mStep_vol * step << "mV" << endl;

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
						UINT LaneID = vLane[laneIndex];
						RxSigMeasCurrent_Neg[SiteID][MacroID][LaneID] = RxMeasureRlt_Neg.GetData(LANE_INFO[MacroID][LaneID].RX_N,SiteID);
						RxSigMeasRes_Neg[SiteID][MacroID][LaneID] = mStep_vol / (RxSigMeasCurrent_Neg[SiteID][MacroID][LaneID] - RxSigMeasCurrent_PrevStep_Neg[SiteID][MacroID][LaneID]);

						if(step != 0) {
							if(RxSigMeasRes_Neg[SiteID][MacroID][LaneID] > MaxRes_Neg[SiteID][MacroID][LaneID]) {
								MaxRes_Neg[SiteID][MacroID][LaneID] = RxSigMeasRes_Neg[SiteID][MacroID][LaneID];
							}
							if(RxSigMeasRes_Neg[SiteID][MacroID][LaneID] < MinRes_Neg[SiteID][MacroID][LaneID]) {
								MinRes_Neg[SiteID][MacroID][LaneID] = RxSigMeasRes_Neg[SiteID][MacroID][LaneID];
							}
							hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_N
										 << ":Current  = " << RxSigMeasCurrent_Neg[SiteID][MacroID][LaneID] << " [mA]" << endl;
							hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_N
										 << ":Previous = " << RxSigMeasCurrent_PrevStep_Neg[SiteID][MacroID][LaneID]
										 << " [mA], Res= " << RxSigMeasRes_Neg[SiteID][MacroID][LaneID] << " [Ohm]" << endl;
						}
						RxSigMeasCurrent_PrevStep_Neg[SiteID][MacroID][LaneID] = RxSigMeasCurrent_Neg[SiteID][MacroID][LaneID];
					}
				}
			FOREACH_ACTIVESITE_END
		}

		if (iOffline) {
			MaxRes_Pos.init(70);
			MinRes_Pos.init(70);
			MaxRes_Neg.init(70);
			MinRes_Neg.init(70);
		}

		/**********************************************
		 * Judgement and datalog
		 **********************************************/
		HiLink_PerLane_Judge(MacroLane_Sel,"RxSigResAftCal_Pos_Min",0.0,MinRes_Pos,0.0, PIN_RXP);
		HiLink_PerLane_Judge(MacroLane_Sel,"RxSigResAftCal_Pos_Max",0.0,MaxRes_Pos,0.0, PIN_RXP);
		HiLink_PerLane_Judge(MacroLane_Sel,"RxSigResAftCal_Neg_Min",0.0,MinRes_Neg,0.0, PIN_RXN);
		HiLink_PerLane_Judge(MacroLane_Sel,"RxSigResAftCal_Neg_Max",0.0,MaxRes_Neg,0.0, PIN_RXN);


	}
	////////////////////////////////////////////////////////////////////////////////
	// TM Purpose:                                                                //
	// This TM is for resistor measurement by using PPMU, it is to measure        //
	// current step by step (range is as defined [0,Range_vol], and step of vol   //
	// is as defined Step_vol), to calculate res=delta(voltage)/delta(current).   //
	//																			  //
	// Parameters:																  //
	// 1. PinList: Pin list to be tested                                          //
	// 2. Range_vol: range of voltage, in mV                                      //
	// 3. Step_vol: step value of voltage, in mV                                  //
	////////////////////////////////////////////////////////////////////////////////
	/**
	 *This test is invoked per site.
	 */
//	virtual void run()
//	{
//
//		/**********************************************
//		 * Common definition of TM for offline flag,
//		 * test suite name, MacroLane Info etc.
//		 **********************************************/
//
//		static	STRING          	sTestsuiteName;
//		static	INT					iOffline;
//		static  MACRO_LANE_SEL 		MacroLane_Sel;
//
//		static	LANE_DOUBLE 		MinRes_Pos;
//		static	LANE_DOUBLE 		MinRes_Neg;
//		static	LANE_DOUBLE 		MaxRes_Pos;
//		static	LANE_DOUBLE 		MaxRes_Neg;
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
//			 * Step 1: Config device to AC couple mode (in calibration)
//			 *         Config device rx_term_floating = 0
//			 ***************************************************************/
//
//			fr.d2s_LABEL_BEGIN("H16LRTV100_MPB_RxSigResAftCal_setup",d2sFrameWorkModeType::Enum(d2s_mode));
//
//				selectMacro_MB(MacroLane_Sel);
//				DS.Broadcast();
//
//				DS.rxRegs.setrxcapbypass(0).Write2DUT(0); /*AC Coupling Mode*/
//
//				DS.rxRegs.setrxterm_floating_en(0).Write2DUT(27);/*floating_en = 0  Sig*/
//				DS.rxRegs.setrxterm_floating_sel(1).Write2DUT(8);
//
//
//			fr.d2s_LABEL_END();
//
//			/***************************************************************
//			 * Step 2: veriable defination
//			 ***************************************************************/
//
//			LANE_DOUBLE 		RxSigMeasCurrent_Pos;
//			LANE_DOUBLE 		RxSigMeasCurrent_Neg;
//			LANE_DOUBLE			RxSigMeasRes_Pos;
//			LANE_DOUBLE			RxSigMeasRes_Neg;
//			LANE_DOUBLE			RxSigMeasCurrent_PrevStep_Pos;
//			LANE_DOUBLE			RxSigMeasCurrent_PrevStep_Neg;
//
//			RxSigMeasCurrent_Pos.init(0);
//			RxSigMeasCurrent_Neg.init(0);
//			RxSigMeasRes_Pos.init(0);
//			RxSigMeasRes_Neg.init(0);
//			MinRes_Pos.init(1e9);
//			MinRes_Neg.init(1e9);
//			MaxRes_Pos.init(0);
//			MaxRes_Neg.init(0);
//			RxSigMeasCurrent_PrevStep_Pos.init(0);
//			RxSigMeasCurrent_PrevStep_Neg.init(0);
//
//			/***************************************************************
//			 * Step 3: PPMU SETUP and do measurement
//			 ***************************************************************/
//
//			PPMU_SETTING 				Set_P,Set_N;
//			PPMU_RELAY   				Rly_PPMU_ON_P,Rly_PPMU_ON_N,Rly_AC_ON;
//			PPMU_CLAMP   				Clamp_on_P,Clamp_on_N,Clamp_off_P,Clamp_off_N;
//			PPMU_MEASURE 				Meas_P,Meas_N;
//			TASK_LIST    				Task_P,Task_N,TaskSetup_P,TaskSetup_N,TaskClean;
//			Rly_PPMU_ON_P.pin(sPinList_P).status("PPMU_ON");
//			Rly_PPMU_ON_P.pin(sPinList_N).status("ALL_OFF");
//			Rly_PPMU_ON_P.wait(1.3 ms);
//			Rly_PPMU_ON_N.pin(sPinList_N).status("PPMU_ON");
//			Rly_PPMU_ON_N.pin(sPinList_P).status("ALL_OFF");
//			Rly_PPMU_ON_N.wait(1.3 ms);
//			Clamp_on_P.pin(sPinList_P).status("CLAMP_ON").low(-0.8 V).high(0.8 V);
//			Clamp_on_N.pin(sPinList_N).status("CLAMP_ON").low(-0.8 V).high(0.8 V);
//			Clamp_off_P.pin(sPinList_P).status("CLAMP_OFF");
//			Clamp_off_N.pin(sPinList_N).status("CLAMP_OFF");
//			Rly_AC_ON.pin(sPinList).status("AC_ON");
//			Rly_AC_ON.wait(0.3 ms);
//			Meas_P.pin(sPinList_P).execMode(TM::OVAL);
//			Meas_N.pin(sPinList_N).execMode(TM::OVAL);
//			TaskSetup_P.add(Clamp_on_P).add(Rly_PPMU_ON_P).add(Clamp_off_P).setup();
//			TaskSetup_N.add(Clamp_on_N).add(Rly_PPMU_ON_N).add(Clamp_off_N).setup();
//			Task_P.add(Set_P).add(Meas_P).setup();
//			Task_N.add(Set_N).add(Meas_N).setup();
//			TaskClean.add(Rly_AC_ON).setup();
//
//			TaskSetup_P.execute();
//
//			DOUBLE 				mRange_vol = 500;
//			DOUBLE 				mStep_vol = 50;
//			for (UINT step = 0; step <= mRange_vol / mStep_vol; step ++) {
//				Set_P.pin(sPinList_P).vForce(mStep_vol * step mV).iRange(10 mA).min(0 uA).max(10 mA);
//				Task_P.execute();
//				hout(DETAIL) << "Currently force Voltage = " << mStep_vol * step << "mV" << endl;
//
//				FOR_EACH_SITE_BEGIN();
//					INT SiteID = CURRENT_SITE_NUMBER() - 1;
//					for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
//						UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//						const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//						for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
//							UINT LaneID = vLane[laneIndex];
//							RxSigMeasCurrent_Pos[SiteID][MacroID][LaneID] = Meas_P.getValue(LANE_INFO[MacroID][LaneID].RX_P) / (1 mA);
//							RxSigMeasRes_Pos[SiteID][MacroID][LaneID] = mStep_vol / (RxSigMeasCurrent_Pos[SiteID][MacroID][LaneID] - RxSigMeasCurrent_PrevStep_Pos[SiteID][MacroID][LaneID]);
//
//							if(step != 0) {
//								if(RxSigMeasRes_Pos[SiteID][MacroID][LaneID] > MaxRes_Pos[SiteID][MacroID][LaneID]) {
//									MaxRes_Pos[SiteID][MacroID][LaneID] = RxSigMeasRes_Pos[SiteID][MacroID][LaneID];
//								}
//								if(RxSigMeasRes_Pos[SiteID][MacroID][LaneID] < MinRes_Pos[SiteID][MacroID][LaneID]) {
//									MinRes_Pos[SiteID][MacroID][LaneID] = RxSigMeasRes_Pos[SiteID][MacroID][LaneID];
//								}
//								hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_P
//											 << ":Current  = " << RxSigMeasCurrent_Pos[SiteID][MacroID][LaneID] << " [mA]" << endl;
//								hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_P
//											 << ":Previous = " << RxSigMeasCurrent_PrevStep_Pos[SiteID][MacroID][LaneID]
//											 << " [mA], Res= " << RxSigMeasRes_Pos[SiteID][MacroID][LaneID] << " [Ohm]" << endl;
//							}
//							RxSigMeasCurrent_PrevStep_Pos[SiteID][MacroID][LaneID] = RxSigMeasCurrent_Pos[SiteID][MacroID][LaneID];
//						}
//					}
//				FOR_EACH_SITE_END();
//			}
//
//			TaskSetup_N.execute();
//
//			for (UINT step = 0; step <= mRange_vol / mStep_vol; step ++) {
//				Set_N.pin(sPinList_N).vForce(mStep_vol * step mV).iRange(10 mA).min(0 uA).max(10 mA);
//				Task_N.execute();
//				hout(DETAIL) << "Currently force Voltage = " << mStep_vol * step << "mV" << endl;
//
//				FOR_EACH_SITE_BEGIN();
//					INT SiteID = CURRENT_SITE_NUMBER() - 1;
//					for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
//						UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//						const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//						for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
//							UINT LaneID = vLane[laneIndex];
//							RxSigMeasCurrent_Neg[SiteID][MacroID][LaneID] = Meas_N.getValue(LANE_INFO[MacroID][LaneID].RX_N) / (1 mA);
//							RxSigMeasRes_Neg[SiteID][MacroID][LaneID] = mStep_vol / (RxSigMeasCurrent_Neg[SiteID][MacroID][LaneID] - RxSigMeasCurrent_PrevStep_Neg[SiteID][MacroID][LaneID]);
//
//							if(step != 0) {
//								if(RxSigMeasRes_Neg[SiteID][MacroID][LaneID] > MaxRes_Neg[SiteID][MacroID][LaneID]) {
//									MaxRes_Neg[SiteID][MacroID][LaneID] = RxSigMeasRes_Neg[SiteID][MacroID][LaneID];
//								}
//								if(RxSigMeasRes_Neg[SiteID][MacroID][LaneID] < MinRes_Neg[SiteID][MacroID][LaneID]) {
//									MinRes_Neg[SiteID][MacroID][LaneID] = RxSigMeasRes_Neg[SiteID][MacroID][LaneID];
//								}
//								hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_N
//											 << ":Current  = " << RxSigMeasCurrent_Neg[SiteID][MacroID][LaneID] << " [mA]" << endl;
//								hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_N
//											 << ":Previous = " << RxSigMeasCurrent_PrevStep_Neg[SiteID][MacroID][LaneID]
//											 << " [mA], Res= " << RxSigMeasRes_Neg[SiteID][MacroID][LaneID] << " [Ohm]" << endl;
//							}
//							RxSigMeasCurrent_PrevStep_Neg[SiteID][MacroID][LaneID] = RxSigMeasCurrent_Neg[SiteID][MacroID][LaneID];
//						}
//					}
//				FOR_EACH_SITE_END();
//			}
//
//			TaskClean.execute();
//
//			if (iOffline) {
//				MaxRes_Pos.init(70);
//				MinRes_Pos.init(70);
//				MaxRes_Neg.init(70);
//				MinRes_Neg.init(70);
//			}
//
//		ON_FIRST_INVOCATION_END();
//
//		/**********************************************
//		 * Judgement and datalog
//		 **********************************************/
//
//		HiLink_PerLane_Judge(MacroLane_Sel,"RxSigResAftCal_Pos_Min",MinRes_Pos, PIN_RXP);
//		HiLink_PerLane_Judge(MacroLane_Sel,"RxSigResAftCal_Pos_Max",MaxRes_Pos, PIN_RXP);
//		HiLink_PerLane_Judge(MacroLane_Sel,"RxSigResAftCal_Neg_Min",MinRes_Neg, PIN_RXN);
//		HiLink_PerLane_Judge(MacroLane_Sel,"RxSigResAftCal_Neg_Max",MaxRes_Neg, PIN_RXN);
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
REGISTER_TESTCLASS("RxSigResAftCal", RxSigResAftCal);
