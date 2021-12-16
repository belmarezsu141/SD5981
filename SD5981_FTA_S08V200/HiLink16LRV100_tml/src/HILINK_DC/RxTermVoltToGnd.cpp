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
class RxTermVoltToGnd: public TestClass {

public:
	STRING 				mHiLink16_MacroList;
	STRING 				mPinList;
	STRING 				mRxCapBypass;
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
		add_param("Couple_Mode","string",&mRxCapBypass)
					 .set_comment("0 is AC couple ,1 is DC couple");
					 //.set_options("0[AC_Couple]:1[DC_Couple]");
		add_param("PrintLvl[0~15]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 10000(16)"
							     "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYE_PLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.set_options("0:1:3:4:7:9")
					 .set_default("3");
	}

	void RxVoltMeas(const MACRO_LANE_SEL MacroLane_Sel, string Pins, double iForce_uA, LANE_DOUBLE & vRxPosMeasVoltage, LANE_DOUBLE & vRxNegMeasVoltage)
	{

		STRING mPinList;
		STRING mPinList_P;
		STRING mPinList_N;

		vRxPosMeasVoltage.init(0);
		vRxNegMeasVoltage.init(0);


		string disconnecPatBurstName = "Disconnect_TX_RX_DZ";
		cout<<"run pattern :"<<disconnecPatBurstName <<endl;
		TheInst.Digital().Pattern().Start(disconnecPatBurstName);
		TheInst.Wait(30 *ms);

		double irange = 50e-6;
		double vExpect = 1.5;
		int sampleSize = 64;
		double waittime = 3e-3;
//		string Pins = "gHILINK_RxP,gHILINK_RxN";
		PinArrayDouble RxSigMeasVoltage = PPMU_FIMV_measure(Pins,iForce_uA,irange,vExpect,waittime,sampleSize);
	//    if(PrintDebugEn)  RxSigMeasVoltage.ShowPinArrayData();

		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++){
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++){
					UINT LaneID = vLane[laneIndex];
					vRxPosMeasVoltage[SiteID][MacroID][LaneID] = RxSigMeasVoltage.GetData(LANE_INFO[MacroID][LaneID].RX_P,SiteID)*1000;
					vRxNegMeasVoltage[SiteID][MacroID][LaneID] = RxSigMeasVoltage.GetData(LANE_INFO[MacroID][LaneID].RX_N,SiteID)*1000;
				}
			}
		FOREACH_ACTIVESITE_END

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

		static	LANE_DOUBLE  		RxPosMeasVoltage;
		static	LANE_DOUBLE  		RxNegMeasVoltage;

			//=============================================
			// Variables and MacroLane initialization
			//=============================================
			GET_SYSTEM_FLAG	("offline",iOffline);
			GET_TESTSUITE_NAME(sTestsuiteName);
			hout.setLevel(iPrintLvl);
			hout.printsuitename(sTestsuiteName);
			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

			GetRxPinList(MacroLane_Sel, sPinList_P, sPinList_N, sPinList);
			INT	iRxCapBypass = mRxCapBypass[0] - '0';
			//=============================================
			// Device Setup
			//=============================================
//			D2S_FRAMEWORK;

			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_DS_RXTermVoltToGnd_Setup",Global_D2S_Mode);

				selectMacro_MB(MacroLane_Sel);
				DS.Broadcast();

				if (iRxCapBypass == 0) {
					/*AC Coupling Mode*/
					DS.rxRegs.setrxcapbypass(0x0)
							 .setctlepassgn(0)
							 .Write2DUT(0);
					DS.rxRegs.setrxterm_floating_sel(1).Write2DUT(8);
					DS.rxRegs.setrxterm_floating_en(0).Write2DUT(27);
				} else if (iRxCapBypass == 1) {
					/*AC Coupling Mode*/
					DS.rxRegs.setrxcapbypass(0x1)
							 .setctlepassgn(1)
							 .Write2DUT(0);
					DS.rxRegs.setrxterm_floating_sel(1).Write2DUT(8);
					DS.rxRegs.setrxterm_floating_en(1).Write2DUT(27);
				} else {
					hout(RELEASE) << "Error: Rx Coupling mode only can be set to 0 or 1!!!!!!" << endl;
					_exit(0);
				}

			d2s::d2s_LABEL_END();

			DOUBLE 	miForce = 1;
			//=============================================
			// Measurement
			//=============================================
			RxPosMeasVoltage.init(0);
			RxNegMeasVoltage.init(0);

			RxVoltMeas(MacroLane_Sel, sPinList, miForce, RxPosMeasVoltage, RxNegMeasVoltage);

			if (iOffline) {
				FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
					for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
					{
						UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
						const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

						for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
						{
							UINT LaneID = vLane[laneIndex];
							if (iRxCapBypass == 0) {
								RxPosMeasVoltage[SiteID][MacroID][LaneID] = 0;
								RxNegMeasVoltage[SiteID][MacroID][LaneID] = 0;
							} else if (iRxCapBypass == 1) {
								RxPosMeasVoltage[SiteID][MacroID][LaneID] = 680;
								RxNegMeasVoltage[SiteID][MacroID][LaneID] = 680;
							} else {
								hout(RELEASE) << "Error: Rx Coupling mode only can be set to 0 or 1!!!!!!" << endl;
								_exit(0);
							}
						}
					}
				FOREACH_ACTIVESITE_END
			}


		//=============================================
		// Datalog
		//=============================================
		HiLink_PerLane_Judge(MacroLane_Sel, "RxTermVoltToGnd_P", 0.0, RxPosMeasVoltage, 0.0, PIN_RXP);
		HiLink_PerLane_Judge(MacroLane_Sel, "RxTermVoltToGnd_N", 0.0, RxNegMeasVoltage, 0.0, PIN_RXN);


	}
	//========================Hi1213========================



	//========================93K========================
//	void RxVoltMeas(const MACRO_LANE_SEL MacroLane_Sel, STRING& sPinList, DOUBLE iForce_uA, LANE_DOUBLE & RxPosMeasVoltage, LANE_DOUBLE & RxNegMeasVoltage)
//	{
//		PPMU_SETTING ppmu_set;
//		PPMU_RELAY   Rly_PPMU_ON,Rly_AC_ON;
//		PPMU_CLAMP   Clamp_on, Clamp_off;
//		PPMU_MEASURE Meas;
//		TASK_LIST    Task;
//
//		ppmu_set.pin(sPinList).iForce(iForce_uA uA).iRange(5 uA).min(0 V).max(2 V);
//		Rly_PPMU_ON.pin(sPinList).status("PPMU_ON");
//		Rly_PPMU_ON.wait(1.3 ms);
//		Rly_AC_ON.pin(sPinList).status("AC_ON");
//		Rly_AC_ON.wait(0.3 ms);
//		Clamp_on.pin(sPinList).status("CLAMP_ON").low(-2.0 V).high(2.0 V);
//		Clamp_off.pin(sPinList).status("CLAMP_OFF");
//		Meas.pin(sPinList).execMode(TM::OVAL);
//		Task.add(ppmu_set).add(Clamp_on).add(Rly_PPMU_ON).add(Clamp_off).add(Meas).add(Rly_AC_ON);
//		Task.execute();
//
//		FOR_EACH_SITE_BEGIN();
//			INT SiteID = CURRENT_SITE_NUMBER() - 1;
//			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
//			{
//				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//
//				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
//				{
//					UINT LaneID = vLane[laneIndex];
//					RxPosMeasVoltage[SiteID][MacroID][LaneID] = Meas.getValue(LANE_INFO[MacroID][LaneID].RX_P) / (1 mV);
//					RxNegMeasVoltage[SiteID][MacroID][LaneID] = Meas.getValue(LANE_INFO[MacroID][LaneID].RX_N) / (1 mV);
//
//					hout(DETAIL) << "Pin: " << LANE_INFO[MacroID][LaneID].RX_P << ": " << RxPosMeasVoltage[SiteID][MacroID][LaneID] << " mV" << endl;
//					hout(DETAIL) << "Pin: " << LANE_INFO[MacroID][LaneID].RX_N << ": " << RxNegMeasVoltage[SiteID][MacroID][LaneID] << " mV" << endl;
//				}
//			}
//		FOR_EACH_SITE_END();
//	}
	///////////////////////macroIndex/////////////////////////////////////////////////////////
	// TM Purpose:                                                                //
	// This TM is for voltage measurement by using PPMU, it is to measure         //
	// Rx term voltage either in AC coupling mode or in DC coupling mode.         //
	//																			  //
	// Parameters:																  //
	// 1. PinList: pin list to be tested										  //
	// 2. ForceCurr: force current												  //
	// 3. RXCAPBYPASS: Rx coupling mode, 0=AC coupling mode, 1=DC coupling mode   //
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
//		static	LANE_DOUBLE  		RxPosMeasVoltage;
//		static	LANE_DOUBLE  		RxNegMeasVoltage;
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
//			INT					iRxCapBypass = mRxCapBypass[0] - '0';
//			//=============================================
//			// Device Setup
//			//=============================================
//			D2S_FRAMEWORK;
//
//			fr.d2s_LABEL_BEGIN("H16LRTV100_MPB_DS_RXTermVoltToGnd_Setup",d2sFrameWorkModeType::Enum(d2s_mode));
//
//				selectMacro_MB(MacroLane_Sel);
//				DS.Broadcast();
//
//				if (iRxCapBypass == 0) {
//					/*AC Coupling Mode*/
//					DS.rxRegs.setrxcapbypass(0x0)
//							 .setctlepassgn(0)
//							 .Write2DUT(0);
//					DS.rxRegs.setrxterm_floating_sel(1).Write2DUT(8);
//					DS.rxRegs.setrxterm_floating_en(0).Write2DUT(27);
//				} else if (iRxCapBypass == 1) {
//					/*AC Coupling Mode*/
//					DS.rxRegs.setrxcapbypass(0x1)
//							 .setctlepassgn(1)
//							 .Write2DUT(0);
//					DS.rxRegs.setrxterm_floating_sel(1).Write2DUT(8);
//					DS.rxRegs.setrxterm_floating_en(1).Write2DUT(27);
//				} else {
//					hout(RELEASE) << "Error: Rx Coupling mode only can be set to 0 or 1!!!!!!" << endl;
//					_exit(0);
//				}
//
//			fr.d2s_LABEL_END();
//
//			DOUBLE 				miForce = 1;
//			//=============================================
//			// Measurement
//			//=============================================
//			RxPosMeasVoltage.init(0);
//			RxNegMeasVoltage.init(0);
//			RxVoltMeas(MacroLane_Sel, sPinList, miForce, RxPosMeasVoltage, RxNegMeasVoltage);
//
//			if (iOffline) {
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
//							if (iRxCapBypass == 0) {
//								RxPosMeasVoltage[SiteID][MacroID][LaneID] = 0;
//								RxNegMeasVoltage[SiteID][MacroID][LaneID] = 0;
//							} else if (iRxCapBypass == 1) {
//								RxPosMeasVoltage[SiteID][MacroID][LaneID] = 680;
//								RxNegMeasVoltage[SiteID][MacroID][LaneID] = 680;
//							} else {
//								hout(RELEASE) << "Error: Rx Coupling mode only can be set to 0 or 1!!!!!!" << endl;
//								_exit(0);
//							}
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
//		HiLink_PerLane_Judge(MacroLane_Sel, "RxTermVoltToGnd_P", RxPosMeasVoltage, PIN_RXP);
//		HiLink_PerLane_Judge(MacroLane_Sel, "RxTermVoltToGnd_N", RxNegMeasVoltage, PIN_RXN);
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
REGISTER_TESTCLASS("RxTermVoltToGnd", RxTermVoltToGnd);
