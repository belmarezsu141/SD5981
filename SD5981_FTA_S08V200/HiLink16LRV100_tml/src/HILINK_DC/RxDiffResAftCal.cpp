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
class RxDiffResAftCal: public TestClass {

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

		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
		static	STRING          	sTestsuiteName;
		static	INT					iOffline;
		static  MACRO_LANE_SEL 		MacroLane_Sel;

		static	LANE_DOUBLE 		RxDiffMeasCurrent;
		static	LANE_DOUBLE			RxDiffMeasRes;
		static	LANE_DOUBLE 		MinRes;
		static	LANE_DOUBLE 		MaxRes;
		static	LANE_DOUBLE			RxDiffMeasCurrent_PrevStep;

		//=============================================
		// Variables and MacroLane initialization
		//=============================================
		GET_SYSTEM_FLAG("offline",iOffline); iOffline = 0;
		GET_TESTSUITE_NAME(sTestsuiteName);
		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

		GetRxPinList(MacroLane_Sel, sPinList_P, sPinList_N, sPinList);

//		D2S_FRAMEWORK;
		//=============================================
		// Device Setup
		//=============================================

		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_RxResAftCal_setup",Global_D2S_Mode);
			selectMacro_MB(MacroLane_Sel);
			DS.Broadcast();
//				DS.rxRegs.setrxterm_floating_en(1).Write2DUT(27);
			DS.rxRegs.setrxcapbypass(0).Write2DUT(0); /*AC Coupling Mode*/
			DS.rxRegs.setrxterm_floating_sel(1).Write2DUT(8);
			DS.rxRegs.setrxterm_floating_en(1).Write2DUT(27);

		d2s::d2s_LABEL_END();

		//=============================================
		// Variables definition and initialization
		//=============================================
		RxDiffMeasCurrent.init(0);
		RxDiffMeasRes.init(0);
		MinRes.init(1e9);
		MaxRes.init(0);
		RxDiffMeasCurrent_PrevStep.init(0);

		//=============================================
		// Loop to measure resistor under different voltage
		//=============================================
		DOUBLE 				mRange_vol = 500;
		DOUBLE 				mStep_vol = 50;

		PinArrayDouble RxMeasureRlt_Pos;

		for (UINT step = 0; step <= mRange_vol / mStep_vol; step ++)
		{
			RxMeasureRlt_Pos = PPMU_FVMI_measure("gHILINK_RxP",mStep_vol * step*mV,10*mA,0.003,6,true);
			hout(DETAIL) << "Currently force Voltage = " << mStep_vol * step << "mV" << endl;

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						RxDiffMeasCurrent[SiteID][MacroID][LaneID] = RxMeasureRlt_Pos.GetData(LANE_INFO[MacroID][LaneID].RX_P,SiteID);

						RxDiffMeasRes[SiteID][MacroID][LaneID] = mStep_vol / (RxDiffMeasCurrent[SiteID][MacroID][LaneID] - RxDiffMeasCurrent_PrevStep[SiteID][MacroID][LaneID]);

						if(step != 0) {
							//get Max Res
							if(RxDiffMeasRes[SiteID][MacroID][LaneID] > MaxRes[SiteID][MacroID][LaneID]) {
								MaxRes[SiteID][MacroID][LaneID] = RxDiffMeasRes[SiteID][MacroID][LaneID];
							}
							//get Min Res
							if(RxDiffMeasRes[SiteID][MacroID][LaneID] < MinRes[SiteID][MacroID][LaneID]) {
								MinRes[SiteID][MacroID][LaneID] = RxDiffMeasRes[SiteID][MacroID][LaneID];
							}

							hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_P
										 << ":Current  = " << RxDiffMeasCurrent[SiteID][MacroID][LaneID] << " [mA]" << endl;
							hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_P
										 << ":Previous = " << RxDiffMeasCurrent_PrevStep[SiteID][MacroID][LaneID]
										 << " [mA], Res= " << RxDiffMeasRes[SiteID][MacroID][LaneID] << " [Ohm]" << endl;
						}

						//store previou step result
						RxDiffMeasCurrent_PrevStep[SiteID][MacroID][LaneID] = RxDiffMeasCurrent[SiteID][MacroID][LaneID];
					}
				}
			FOREACH_ACTIVESITE_END
		}

		if (iOffline)
		{
			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						MaxRes[SiteID][MacroID][LaneID] = 100;
						MinRes[SiteID][MacroID][LaneID] = 100;
					}
				}
			FOREACH_ACTIVESITE_END
		}


		//=============================================
		// Datalog
		//=============================================
		HiLink_PerLane_Judge(MacroLane_Sel,"RxDiffResAftCal_Min",0.0,MinRes,0.0,NONE);
		HiLink_PerLane_Judge(MacroLane_Sel,"RxDiffResAftCal_Max",0.0,MaxRes,0.0,NONE);

		return;
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
//		//=============================================
//		// Common definition of TM for offline flag,
//		// d2s mode, debug mode, test suite name, etc.
//		//=============================================
//		static	STRING          	sTestsuiteName;
//		static	INT					iOffline;
//		static  MACRO_LANE_SEL 		MacroLane_Sel;
//
//		static	LANE_DOUBLE 		RxDiffMeasCurrent;
//		static	LANE_DOUBLE			RxDiffMeasRes;
//		static	LANE_DOUBLE 		MinRes;
//		static	LANE_DOUBLE 		MaxRes;
//		static	LANE_DOUBLE			RxDiffMeasCurrent_PrevStep;
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
//			D2S_FRAMEWORK;
//			//=============================================
//			// Device Setup
//			//=============================================
//
//			fr.d2s_LABEL_BEGIN("H16LRTV100_MPB_RxResAftCal_setup",d2sFrameWorkModeType::Enum(d2s_mode));
//
//				selectMacro_MB(MacroLane_Sel);
//
//				DS.Broadcast();
////				DS.rxRegs.setrxterm_floating_en(1).Write2DUT(27);
//
//				DS.rxRegs.setrxcapbypass(0).Write2DUT(0); /*AC Coupling Mode*/
//				DS.rxRegs.setrxterm_floating_sel(1).Write2DUT(8);
//				DS.rxRegs.setrxterm_floating_en(1).Write2DUT(27);
//
//			fr.d2s_LABEL_END();
//
//			//=============================================
//			// Variables definition and initialization
//			//=============================================
//			RxDiffMeasCurrent.init(0);
//			RxDiffMeasRes.init(0);
//			MinRes.init(1e9);
//			MaxRes.init(0);
//			RxDiffMeasCurrent_PrevStep.init(0);
//
//			//=============================================
//			// PPMU Setup
//			//=============================================
//			PPMU_SETTING 				Set;
//			PPMU_RELAY   				Rly_PPMU_ON,Rly_AC_ON;
//			PPMU_CLAMP   				Clamp_on,Clamp_off;
//			PPMU_MEASURE 				Meas;
//			TASK_LIST    				Task, TaskSetup, TaskClean;
//			Set.pin(sPinList_P).vForce(0 mV).iRange(10 mA).min(0 uA).max(10 mA);
//			Set.pin(sPinList_N).vForce(0 mV).iRange(10 mA).min(0 uA).max(10 mA);
//			Rly_PPMU_ON.pin(sPinList).status("PPMU_ON");
//			Rly_PPMU_ON.wait(1.3 ms);
//			Clamp_on.pin(sPinList).status("CLAMP_ON").low(-0.8 V).high(0.8 V);
//			Clamp_off.pin(sPinList).status("CLAMP_OFF");
//			Rly_AC_ON.pin(sPinList).status("AC_ON");
//			Rly_AC_ON.wait(0.3 ms);
//			Meas.pin(sPinList).execMode(TM::OVAL);
//			TaskSetup.add(Clamp_on).add(Rly_PPMU_ON).add(Clamp_off).setup();
//			Task.add(Set).add(Meas).setup();
//			TaskClean.add(Rly_AC_ON).setup();
//			TaskSetup.execute();
//
//			//=============================================
//			// Loop to measure resistor under different voltage
//			//=============================================
//			DOUBLE 				mRange_vol = 500;
//			DOUBLE 				mStep_vol = 50;
//
//			for (UINT step = 0; step <= mRange_vol / mStep_vol; step ++)
//			{
//				Set.pin(sPinList_P).vForce(mStep_vol * step mV).iRange(10 mA).min(0 uA).max(10 mA);
//				Task.execute();
//				hout(DETAIL) << "Currently force Voltage = " << mStep_vol * step << "mV" << endl;
//
//				FOR_EACH_SITE_BEGIN();
//					INT SiteID = CURRENT_SITE_NUMBER() - 1;
//					for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
//					{
//						UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//						const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//
//						for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
//						{
//							UINT LaneID = vLane[laneIndex];
//							RxDiffMeasCurrent[SiteID][MacroID][LaneID] = Meas.getValue(LANE_INFO[MacroID][LaneID].RX_P) / (1 mA);	//mA
//
//							RxDiffMeasRes[SiteID][MacroID][LaneID] = mStep_vol / (RxDiffMeasCurrent[SiteID][MacroID][LaneID] - RxDiffMeasCurrent_PrevStep[SiteID][MacroID][LaneID]);
//
//							if(step != 0) {
//								//get Max Res
//								if(RxDiffMeasRes[SiteID][MacroID][LaneID] > MaxRes[SiteID][MacroID][LaneID]) {
//									MaxRes[SiteID][MacroID][LaneID] = RxDiffMeasRes[SiteID][MacroID][LaneID];
//								}
//								//get Min Res
//								if(RxDiffMeasRes[SiteID][MacroID][LaneID] < MinRes[SiteID][MacroID][LaneID]) {
//									MinRes[SiteID][MacroID][LaneID] = RxDiffMeasRes[SiteID][MacroID][LaneID];
//								}
//
//								hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_P
//											 << ":Current  = " << RxDiffMeasCurrent[SiteID][MacroID][LaneID] << " [mA]" << endl;
//								hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].RX_P
//											 << ":Previous = " << RxDiffMeasCurrent_PrevStep[SiteID][MacroID][LaneID]
//											 << " [mA], Res= " << RxDiffMeasRes[SiteID][MacroID][LaneID] << " [Ohm]" << endl;
//							}
//
//							//store previou step result
//							RxDiffMeasCurrent_PrevStep[SiteID][MacroID][LaneID] = RxDiffMeasCurrent[SiteID][MacroID][LaneID];
//						}
//					}
//				FOR_EACH_SITE_END();
//			}
//			TaskClean.execute();
//
//			if (iOffline)
//			{
//				FOR_EACH_SITE_BEGIN();
//					INT SiteID = CURRENT_SITE_NUMBER() - 1;
//					for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
//					{
//						UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//						const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//
//						for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
//						{
//							UINT LaneID = vLane[laneIndex];
//							MaxRes[SiteID][MacroID][LaneID] = 100;
//							MinRes[SiteID][MacroID][LaneID] = 100;
//						}
//					}
//				FOR_EACH_SITE_END();
//			}
//
//		ON_FIRST_INVOCATION_END();
//
//		//=============================================
//		// Datalog
//		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel,"RxDiffResAftCal_Min",MinRes);
//		HiLink_PerLane_Judge(MacroLane_Sel,"RxDiffResAftCal_Max",MaxRes);
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
REGISTER_TESTCLASS("RxDiffResAftCal", RxDiffResAftCal);
