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
class TxResAftCal: public TestClass{

public:
	STRING 				mHiLink16_MacroList;
	STRING 				mPinList;
	STRING 				mData_Type;
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
		add_param("Data_Type","string",&mData_Type)
					 .set_default("All0");
					 //.set_options("All0:All1");
		add_param("PrintLvl[0~15]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 10000(16)"
							     "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYE_PLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.set_options("0:1:3:4:7:9")
					 .set_default("3");
	}

	//=========================Hi1213=====================
	void TxResMeas(const MACRO_LANE_SEL& MacroLane_Sel, const DOUBLE& mCurrentSink1_mA, const DOUBLE& mCurrentSink2_mA, LANE_DOUBLE& TxPosMeasRes, LANE_DOUBLE& TxNegMeasRes)
	{
		INT					iOffline;
		GET_SYSTEM_FLAG("offline",iOffline);

		LANE_DOUBLE					TxPosMeasVoltage1;
		LANE_DOUBLE 				TxNegMeasVoltage1;
		LANE_DOUBLE 				TxPosMeasVoltage2;
		LANE_DOUBLE 				TxNegMeasVoltage2;

		TxPosMeasVoltage1.init(0);
		TxNegMeasVoltage1.init(0);
		TxPosMeasVoltage2.init(0);
		TxNegMeasVoltage2.init(0);
		PinArrayDouble Meas_pos;
		PinArrayDouble Meas_neg;
		//=============================================
		// Measurement
		//=============================================
		double vExpect = 1.5;
		int sampleSize = 64;
		double waittime =3e-3;
		string sPinList_P = "gHILINK_TxP";
		string sPinList_N = "gHILINK_TxN";
//		Set_pos.pin(sPinList_P).iForce(-mCurrentSink1_mA mA).iRange(mCurrentSink1_mA mA).min(0 V).max(2 V);
//		Set_pos.pin(sPinList_N).iForce( mCurrentSink1_mA mA).iRange(mCurrentSink1_mA mA).min(0 V).max(2 V);
		PPMU_FI_Waitmeasure(sPinList_P,-mCurrentSink1_mA *mA,vExpect,waittime,sampleSize);
		PPMU_FI_Waitmeasure(sPinList_N,mCurrentSink1_mA *mA,vExpect,waittime,sampleSize);

		string sPinList = "gHILINK_TxP,gHILINK_TxN";

		TheInst.PPMU().Pins(sPinList).Measure();
		Meas_pos = TheInst.PPMU().Pins(sPinList).GetMeasureResults();



		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
				{
					UINT LaneID = vLane[laneIndex];
					TxPosMeasVoltage1[SiteID][MacroID][LaneID] = Meas_pos.GetData(LANE_INFO[MacroID][LaneID].TX_P,SiteID) / (1 *mA);
					TxNegMeasVoltage1[SiteID][MacroID][LaneID] = Meas_pos.GetData(LANE_INFO[MacroID][LaneID].TX_N,SiteID) / (1 *mA);
//					cout << "Pin " << LANE_INFO[MacroID][LaneID].TX_P << " Force "<<   mCurrentSink1_mA <<" [mA] = "  << TxPosMeasVoltage1[SiteID][MacroID][LaneID] << " mV" << endl;
//					cout << "Pin " << LANE_INFO[MacroID][LaneID].TX_N << " Force "<<  -mCurrentSink1_mA <<" [mA] = "  << TxNegMeasVoltage1[SiteID][MacroID][LaneID] << " mV" << endl;
				}
			}
			FOREACH_ACTIVESITE_END

//		Set_pos.pin(sPinList_P).iForce(-mCurrentSink2_mA mA).iRange(mCurrentSink2_mA mA).min(0 V).max(2 V);
//		Set_pos.pin(sPinList_N).iForce(mCurrentSink2_mA mA).iRange(mCurrentSink2_mA mA).min(0 V).max(2 V);
			PPMU_FI_Waitmeasure(sPinList_P,-mCurrentSink2_mA *mA,vExpect,waittime,sampleSize);
			PPMU_FI_Waitmeasure(sPinList_N,mCurrentSink2_mA *mA,vExpect,waittime,sampleSize);

			TheInst.PPMU().Pins(sPinList).Measure();
			Meas_pos = TheInst.PPMU().Pins(sPinList).GetMeasureResults();


			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
				{
					UINT LaneID = vLane[laneIndex];
					TxPosMeasVoltage2[SiteID][MacroID][LaneID] = Meas_pos.GetData(LANE_INFO[MacroID][LaneID].TX_P,SiteID) / (1 *mA);
					TxNegMeasVoltage2[SiteID][MacroID][LaneID] = Meas_pos.GetData(LANE_INFO[MacroID][LaneID].TX_N,SiteID) / (1 *mA);
//					cout << "Pin " << LANE_INFO[MacroID][LaneID].TX_P << " Force "<<   mCurrentSink2_mA <<" [mA] = "  << TxPosMeasVoltage2[SiteID][MacroID][LaneID] << " mV" << endl;
//					cout << "Pin " << LANE_INFO[MacroID][LaneID].TX_N << " Force "<<  -mCurrentSink2_mA <<" [mA] = "  << TxNegMeasVoltage2[SiteID][MacroID][LaneID] << " mV" << endl;
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
					TxPosMeasRes[SiteID][MacroID][LaneID] = (TxPosMeasVoltage2[SiteID][MacroID][LaneID] - TxPosMeasVoltage1[SiteID][MacroID][LaneID]) / (mCurrentSink1_mA - mCurrentSink2_mA);
					TxNegMeasRes[SiteID][MacroID][LaneID] = (TxNegMeasVoltage1[SiteID][MacroID][LaneID] - TxNegMeasVoltage2[SiteID][MacroID][LaneID]) / (mCurrentSink1_mA - mCurrentSink2_mA);
//					if (iOffline)
//					{
//						TxPosMeasRes[SiteID][MacroID][LaneID] = 50;
//						TxNegMeasRes[SiteID][MacroID][LaneID] = 50;
//					}

//					cout << "Pin " << LANE_INFO[MacroID][LaneID].TX_P << " Result = " << TxPosMeasRes[SiteID][MacroID][LaneID] << " Ohm" << endl;
//					cout << "Pin " << LANE_INFO[MacroID][LaneID].TX_N << " Result = " << TxNegMeasRes[SiteID][MacroID][LaneID] << " Ohm" << endl;

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

		static	LANE_DOUBLE			TxPosMeasRes;
		static	LANE_DOUBLE 		TxNegMeasRes;

		//=============================================
		// Variables and MacroLane initialization
		//=============================================
		GET_SYSTEM_FLAG	("offline",iOffline);
		GET_TESTSUITE_NAME(sTestsuiteName);
		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

		GetTxPinList(MacroLane_Sel, sPinList_P, sPinList_N, sPinList);

		//=============================================
		// Device Setup
		//=============================================
		DOUBLE 				mCurrentSink1_mA = 5;
		DOUBLE 				mCurrentSink2_mA = 1;

//		D2S_FRAMEWORK;

		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_DS_RX_RES_AfterCal",Global_D2S_Mode);
			selectMacro_MB(MacroLane_Sel);
			DS.Broadcast();
			if (mData_Type == "All0") {
				EnableTxPrbsGen(Custom_ALL0);
			} else if (mData_Type=="All1") {
				EnableTxPrbsGen(Custom_ALL1);
			}

		d2s::d2s_LABEL_END();

		TxPosMeasRes.init(0);
		TxNegMeasRes.init(0);

		if (mData_Type == "All0") {
			TxResMeas(MacroLane_Sel, -mCurrentSink1_mA, -mCurrentSink2_mA, TxPosMeasRes, TxNegMeasRes);
		} else if (mData_Type=="All1") {
			TxResMeas(MacroLane_Sel, mCurrentSink1_mA, mCurrentSink2_mA, TxPosMeasRes, TxNegMeasRes);
		}

		//=============================================
		// Datalog
		//=============================================
		HiLink_PerLane_Judge(MacroLane_Sel, "TxPos", 0.0, TxPosMeasRes, 0.0, PIN_TXP);
		HiLink_PerLane_Judge(MacroLane_Sel, "TxNeg", 0.0, TxNegMeasRes, 0.0, PIN_TXN);



	}




//============================93K=====================
//	void TxResMeas(const MACRO_LANE_SEL& MacroLane_Sel, const DOUBLE& mCurrentSink1_mA, const DOUBLE& mCurrentSink2_mA, LANE_DOUBLE& TxPosMeasRes, LANE_DOUBLE& TxNegMeasRes)
//	{
//		INT					iOffline;
//		GET_SYSTEM_FLAG		("offline",&iOffline);
//		//=============================================
//		// Measurement
//		//=============================================
//		PPMU_SETTING Set_pos,Set_neg;
//		PPMU_RELAY   Rly_PPMU_ON,Rly_AC_ON;
//		PPMU_CLAMP   Clamp_on, Clamp_off;
//		PPMU_MEASURE Meas_pos;
//		TASK_LIST    Task;
//
//		//set PPMU to sink 5mA at under tested pins
//		Set_pos.pin(sPinList_P).iForce(-mCurrentSink1_mA mA).iRange(mCurrentSink1_mA mA).min(0 V).max(2 V);
//		Set_pos.pin(sPinList_N).iForce( mCurrentSink1_mA mA).iRange(mCurrentSink1_mA mA).min(0 V).max(2 V);
//
//		Rly_PPMU_ON.pin(sPinList).status("PPMU_ON");
//		Rly_PPMU_ON.wait(1.3 ms);
//		Clamp_on.pin(sPinList).status("CLAMP_ON").low(-0.8 V).high(0.8 V);
//		Clamp_off.pin(sPinList).status("CLAMP_OFF");
//		Rly_AC_ON.pin(sPinList).status("AC_ON");
//		Rly_AC_ON.wait(0.3 ms);
//		Meas_pos.pin(sPinList).execMode(TM::OVAL);
//		Task.add(Set_pos).add(Clamp_on).add(Rly_PPMU_ON).add(Clamp_off).add(Meas_pos);
//		Task.execute();
//
//		LANE_DOUBLE					TxPosMeasVoltage1;
//		LANE_DOUBLE 				TxNegMeasVoltage1;
//		LANE_DOUBLE 				TxPosMeasVoltage2;
//		LANE_DOUBLE 				TxNegMeasVoltage2;
//
//		TxPosMeasVoltage1.init(0);
//		TxNegMeasVoltage1.init(0);
//		TxPosMeasVoltage2.init(0);
//		TxNegMeasVoltage2.init(0);
//
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
//					TxPosMeasVoltage1[SiteID][MacroID][LaneID] = Meas_pos.getValue(LANE_INFO[MacroID][LaneID].TX_P) / (1 mA);
//					TxNegMeasVoltage1[SiteID][MacroID][LaneID] = Meas_pos.getValue(LANE_INFO[MacroID][LaneID].TX_N) / (1 mA);
//
//					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_P << " Force "<<   mCurrentSink1_mA <<" [mA] = "  << TxPosMeasVoltage1[SiteID][MacroID][LaneID] << " mV" << endl;
//					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_N << " Force "<<  -mCurrentSink1_mA <<" [mA] = "  << TxNegMeasVoltage1[SiteID][MacroID][LaneID] << " mV" << endl;
//
//				}
//			}
//		FOR_EACH_SITE_END();
//
//
//
//		//set PPMU to sink 1mA at under tested pins
//		Set_pos.pin(sPinList_P).iForce(-mCurrentSink2_mA mA).iRange(mCurrentSink2_mA mA).min(0 V).max(2 V);
//		Set_pos.pin(sPinList_N).iForce(mCurrentSink2_mA mA).iRange(mCurrentSink2_mA mA).min(0 V).max(2 V);
//		Task.add(Set_pos).add(Meas_pos).add(Rly_AC_ON);
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
//					TxPosMeasVoltage2[SiteID][MacroID][LaneID] = Meas_pos.getValue(LANE_INFO[MacroID][LaneID].TX_P) / (1 mA);
//					TxNegMeasVoltage2[SiteID][MacroID][LaneID] = Meas_pos.getValue(LANE_INFO[MacroID][LaneID].TX_N) / (1 mA);
//
//					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_P << " Force "<<   mCurrentSink2_mA <<" [mA] = "  << TxPosMeasVoltage2[SiteID][MacroID][LaneID] << " mV" << endl;
//					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_N << " Force "<<  -mCurrentSink2_mA <<" [mA] = "  << TxNegMeasVoltage2[SiteID][MacroID][LaneID] << " mV" << endl;
//
//				}
//			}
//		FOR_EACH_SITE_END();
//
//		//calculate Res
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
//					TxPosMeasRes[SiteID][MacroID][LaneID] = (TxPosMeasVoltage2[SiteID][MacroID][LaneID] - TxPosMeasVoltage1[SiteID][MacroID][LaneID]) / (mCurrentSink1_mA - mCurrentSink2_mA);
//					TxNegMeasRes[SiteID][MacroID][LaneID] = (TxNegMeasVoltage1[SiteID][MacroID][LaneID] - TxNegMeasVoltage2[SiteID][MacroID][LaneID]) / (mCurrentSink1_mA - mCurrentSink2_mA);
//					if (iOffline)
//					{
//						TxPosMeasRes[SiteID][MacroID][LaneID] = 50;
//						TxNegMeasRes[SiteID][MacroID][LaneID] = 50;
//
//					}
//
//					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_P << " Result = " << TxPosMeasRes[SiteID][MacroID][LaneID] << " Ohm" << endl;
//					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_N << " Result = " << TxNegMeasRes[SiteID][MacroID][LaneID] << " Ohm" << endl;
//
//				}
//			}
//		FOR_EACH_SITE_END();
//	}
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
	//																			  //
	//	ALL0: measure TxPos pull-down resistance and TxNeg pull-up resistance	  //
	//  ALL1: measure TxPos pull-up resistance and TxNeg pull-down resistance     //
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
//		static	LANE_DOUBLE			TxPosMeasRes;
//		static	LANE_DOUBLE 		TxNegMeasRes;
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
//			GetTxPinList(MacroLane_Sel, sPinList_P, sPinList_N, sPinList);
//
//			//=============================================
//			// Device Setup
//			//=============================================
//			DOUBLE 				mCurrentSink1_mA = 5;
//			DOUBLE 				mCurrentSink2_mA = 1;
//
//			D2S_FRAMEWORK;
//
//			fr.d2s_LABEL_BEGIN("H16LRTV100_MPB_DS_RX_RES_AfterCal",d2sFrameWorkModeType::Enum(d2s_mode));
//
//				selectMacro_MB(MacroLane_Sel);
//				DS.Broadcast();
//				if (mData_Type == "All0") {
//					EnableTxPrbsGen(Custom_ALL0);
//				} else if (mData_Type=="All1") {
//					EnableTxPrbsGen(Custom_ALL1);
//				}
//
//			fr.d2s_LABEL_END();
//
//			TxPosMeasRes.init(0);
//			TxNegMeasRes.init(0);
//
//			if (mData_Type == "All0") {
//				TxResMeas(MacroLane_Sel, -mCurrentSink1_mA, -mCurrentSink2_mA, TxPosMeasRes, TxNegMeasRes);
//			} else if (mData_Type=="All1") {
//				TxResMeas(MacroLane_Sel, mCurrentSink1_mA, mCurrentSink2_mA, TxPosMeasRes, TxNegMeasRes);
//			}
//
//		ON_FIRST_INVOCATION_END();
//
//		//=============================================
//		// Datalog
//		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "TxPos", TxPosMeasRes, PIN_TXP);
//		HiLink_PerLane_Judge(MacroLane_Sel, "TxNeg", TxNegMeasRes, PIN_TXN);
//
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
REGISTER_TESTCLASS("TxResAftCal", TxResAftCal);
