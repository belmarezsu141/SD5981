//for test method API interfaces
//#include "mapi.hpp"
//#include "tpi_c.h"
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
#include <HILINK_DRIVE/d2s_Dynamic_pHilink_TX.h>
using namespace std;
using namespace PhxAPI;
/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */

typedef struct {
	DOUBLE  dmax;
	DOUBLE  dmin;
	DOUBLE  damax;
	DOUBLE  imax;
        DOUBLE  imin;
        DOUBLE  iamax;
        INT     dmax_index;
        INT     dmin_index;
        INT     damax_index;
        INT     imax_index;
        INT     imin_index;
        INT     iamax_index;
} LINEARtype;

typedef enum {
    MIN_RMS_LSB
} ILEtype;

void DSP_LINEAR(ARRAY_D& src, LINEARtype *result, ARRAY_D& dle, ARRAY_D& ile, ILEtype ile_type) {

    int n;
	n= src.size();

	DOUBLE A1 = 0;
	DOUBLE B = 0;
    DOUBLE sum;
    DOUBLE DeviceLSB;
    DOUBLE Vref;

    for (int i = 0; i < n; i++) {   //masked by tony 20210811
    	A1 += double(src[i] * 1.0*i);
        B += double(src[i]);
    }

    switch (ile_type) {
        case MIN_RMS_LSB:
            DeviceLSB = (n * A1 - (B * n * (n - 1) / 2)) / (n * n * (n - 1) * (2 * n - 1) / 6 - ((n - 1) * n / 2) * ((n - 1) * n / 2));
            Vref = (B - DeviceLSB * n * (n - 1) / 2) / n;
            break;

    }
    for (int i = 0; i < (n - 1); i++) {
        switch (ile_type) {
            case MIN_RMS_LSB:
                dle[i] = (src[i + 1] - src[i]) / DeviceLSB - 1;
                ile[i] = (src[i] - (DeviceLSB * i + Vref)) / DeviceLSB;
                break;
        }
    }

    result->dmax = dle[0];
    result->dmin = dle[0];
    result->damax = abs(dle[0]);
    result->imax = ile[0];
    result->imin = ile[0];
    result->iamax = abs(ile[0]);
    result->dmax_index = 0;
    result->dmin_index = 0;
    result->damax_index = 0;
    result->imax_index = 0;
    result->imin_index = 0;
    result->iamax_index = 0;
    for (int i = 0; i < (n - 1); i++) {
        if (result->dmax < dle[i]) {
            result->dmax = dle[i];
            result->dmax_index = i;
        }
        if (result->dmin > dle[i]) {
            result->dmin = dle[i];
            result->dmin_index = i;
        }
        if (result->damax < dle[i]) {
            result->damax = abs(dle[i]);
            result->damax_index = i;
        }
        if (result->imax < ile[i]) {
            result->imax = ile[i];
            result->imax_index = i;
        }
        if (result->imin > ile[i]) {
            result->imin = ile[i];
            result->imin_index = i;
        }
        if (result->iamax < ile[i]) {
            result->iamax = abs(ile[i]);
            result->iamax_index = i;
        }
    }
}

class TxFIR_DC_Dynamic: public TestClass {
public:
	STRING 	mHiLink16_MacroList;
	STRING 	mPinList;
	STRING 	mFIR_SCAN;
	STRING 	sPinList;
	STRING 	sPinList_P;
	STRING 	sPinList_N;
	INT 	mPolarity;
	INT		iPrintLvl;

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
		add_param("FIR_Tap","string",&mFIR_SCAN)
					 .set_default("MAIN");
					 //.set_options("MAIN:PRE1ST:PRE2ND:POST1ST:POST2ND");
		add_param("Polarity","int",&mPolarity)
					 .set_default("0");
					 //.set_options("0:1");
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

		static	LANE_DOUBLE	INL;
		static	LANE_DOUBLE	DNL;
		static	LANE_DOUBLE	Gain;
		static	LANE_DOUBLE	Offset;
//		TxFIR_SETTING 		FIR;
//		PATTERN_CONTROLLER 	Controller;

		//=============================================
		// Variables and MacroLane initialization
		//=============================================
		GET_SYSTEM_FLAG	("offline",iOffline); iOffline =0;
		GET_TESTSUITE_NAME	(sTestsuiteName);
		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

		GetTxPinList(MacroLane_Sel, sPinList_P, sPinList_N, sPinList);

		TxFIR_SETTING 	FIR;
		//=============================================
		// Variables definition and initialization
		//=============================================
//			PPMU_SETTING 	Set;
//			PPMU_RELAY   	Rly1,Rly2;
//			PPMU_CLAMP   	Clamp_on, Clamp_off;
//			PPMU_MEASURE 	Meas;
//			TASK_LIST    	Task, TaskSetup, TaskClean;
//
//			DC_RESULT_ACCESSOR 	Result;
//
//			Set.pin(sPinList).iForce(0.001 uA).iRange(10 uA).min(-1 V).max(2 V);
//			Rly1.pin(sPinList).status("ACPM_ON");
//			Rly1.wait(1.3 ms);
//			Rly2.pin(sPinList).status("AC_ON");
//			Rly2.wait(0.3 ms);
//			Clamp_on.pin(sPinList).status("CLAMP_ON").low(-0.8 V).high(0.8 V);
//			Clamp_off.pin(sPinList).status("CLAMP_OFF");
//			Meas.pin(sPinList).measurementType(TM::VMUM);
//
//			Controller.label("TxFIR_DynamicDC_sub","pHilink16_TX").add(Meas);
//			Controller.setup();
//
//			TaskSetup.add(Set).add(Clamp_on).add(Rly1).add(Clamp_off).setup();
//			TaskClean.add(Rly2).setup();
//
//			TaskSetup.execute();

		INT SCAN_start, SCAN_stop, SCAN_points;
		INT MainPole, Pre1st, Pre2nd, Post1st, Post2nd;
		INT dMainPole, dPre1st, dPre2nd, dPost1st, dPost2nd;

		if (mFIR_SCAN == "MAIN") {
			SCAN_start 	= 0;
			SCAN_stop 	= 63;
			SCAN_points = 64;

			MainPole 	= 0;
			Pre1st 		= 0;
			Pre2nd 		= 0;
			Post1st 	= 0;
			Post2nd 	= 0;

			dMainPole 	= 1;
			dPre1st 	= 0;
			dPre2nd 	= 0;
			dPost1st 	= 0;
			dPost2nd 	= 0;
		} else if (mFIR_SCAN == "PRE1ST") {
			SCAN_start 	= -15;
			SCAN_stop 	= 15;
			SCAN_points = 31;

			MainPole 	= 0;
			Pre1st 		= -15;
			Pre2nd 		= 0;
			Post1st 	= 0;
			Post2nd 	= 0;

			dMainPole 	= 0;
			dPre1st 	= 1;
			dPre2nd 	= 0;
			dPost1st 	= 0;
			dPost2nd 	= 0;

		} else if (mFIR_SCAN == "PRE2ND") {
			SCAN_start 	= -15;
			SCAN_stop 	= 15;
			SCAN_points = 31;

			MainPole 	= 0;
			Pre1st 		= 0;
			Pre2nd 		= -15;
			Post1st 	= 0;
			Post2nd 	= 0;

			dMainPole 	= 0;
			dPre1st 	= 0;
			dPre2nd 	= 1;
			dPost1st 	= 0;
			dPost2nd 	= 0;
		} else if (mFIR_SCAN == "POST1ST") {
			SCAN_start 	= -15;
			SCAN_stop 	= 15;
			SCAN_points = 31;

			MainPole 	= 0;
			Pre1st 		= 0;
			Pre2nd 		= 0;
			Post1st 	= -15;
			Post2nd 	= 0;

			dMainPole 	= 0;
			dPre1st 	= 0;
			dPre2nd 	= 0;
			dPost1st 	= 1;
			dPost2nd 	= 0;
		} else if (mFIR_SCAN == "POST2ND") {
			SCAN_start 	= -15;
			SCAN_stop 	= 15;
			SCAN_points = 31;

			MainPole 	= 0;
			Pre1st 		= 0;
			Pre2nd 		= 0;
			Post1st 	= 0;
			Post2nd 	= -15;

			dMainPole 	= 0;
			dPre1st 	= 0;
			dPre2nd 	= 0;
			dPost1st 	= 0;
			dPost2nd 	= 1;
		}

		//=============================================
		// Device Setup
		//=============================================

//			D2S_FRAMEWORK;
//			d2s_Dynamic_pHilink_TX & hilink16_tx = d2s_Dynamic_pHilink_TX::Instance();
//			hilink16_tx.getContext();
//			fr.registerTransactionPort(hilink16_tx);

		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_DS_TX_FIR_DYNAMIC_DC_SCAN",Global_D2S_Mode);

			selectMacro_MB(MacroLane_Sel);
			DS.Broadcast();

			EnableTxPrbsGen(Custom_ALL0);

			if (mPolarity == 0) {
				DS.txRegs.settxpolarity(0)
						 .Write2DUT(2);
			} else if (mPolarity == 1) {
				DS.txRegs.settxpolarity(1)
						 .Write2DUT(2);
			}
		d2s::d2s_LABEL_END();

		vector<PinArrayDouble> TxSigMeasVoltage_SCAN;
		PinArrayDouble TxSigMeasVoltage;
		TxSigMeasVoltage_SCAN.resize(SCAN_points);

		d2s_JTAG& jtag = d2s_JTAG::Instance();
		for (INT i = 0 ; i < SCAN_points; i++) {
			FIR.iTxPre2nd = Pre2nd;
			FIR.iTxPre1st = Pre1st;
			FIR.iTxMain = MainPole;
			FIR.iTxPost1st = Post1st;
			FIR.iTxPost2nd = Post2nd;

			sprintf (label, "H15BP_MPB_DS_TX_FIR_DYNAMIC_DC_SCAN_Pt%d", i);
			d2s::d2s_LABEL_BEGIN(label,Global_D2S_Mode);
				SetTxFir(FIR);
				jtag.wait(40 *us);
			d2s::d2s_LABEL_END();
			TxSigMeasVoltage = PPMU_FIMV_measure(sPinList,0.001*uA,2,0.003,4);
			TxSigMeasVoltage_SCAN[i]= TxSigMeasVoltage;
//					fr.synchronizePorts(jtag,hilink16_tx);
//
//					hilink16_tx.execLabel("TxFIR_DynamicDC_pHilink16_TX_STD", 15000);
//
//					fr.synchronizePorts(jtag,hilink16_tx);

			MainPole 	+= dMainPole;
			Pre1st 		+= dPre1st;
			Pre2nd 		+= dPre2nd;
			Post1st 	+= dPost1st;
			Post2nd 	+= dPost2nd;
		}



//			TM::RESULT_RANGE resultRange = Result.getRangeOfAvailableResults(sPinList, TM::RESULT_INDEX);

//			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
//				{
//					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//
//					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
//					{
//						UINT LaneID = vLane[laneIndex];
//						Result.uploadResult(LANE_INFO[MacroID][LaneID].TX_P, resultRange);
//						Result.uploadResult(LANE_INFO[MacroID][LaneID].TX_N, resultRange);
//					}
//				}
//			FOREACH_ACTIVESITE_END


			/*****************[MacroID][LaneID][ScanPoint]************/
			LANE_ARRAY_D	TxPosMeasVoltage;
			LANE_ARRAY_D	TxNegMeasVoltage;
			LANE_ARRAY_D	TxDiffMeasVoltage;

			TxPosMeasVoltage.init(SCAN_points,0);
			TxNegMeasVoltage.init(SCAN_points,0);
			TxDiffMeasVoltage.init(SCAN_points,0);

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];



						for (INT i = 0 ; i < SCAN_points; i++) {
							if (!iOffline) {
								TxPosMeasVoltage[SiteID][MacroID][LaneID] = TxSigMeasVoltage_SCAN[i].GetData(LANE_INFO[MacroID][LaneID].TX_P,SiteID) * 1e3;
								TxNegMeasVoltage[SiteID][MacroID][LaneID] = TxSigMeasVoltage_SCAN[i].GetData(LANE_INFO[MacroID][LaneID].TX_N,SiteID) * 1e3;
							}
							TxDiffMeasVoltage[SiteID][MacroID][LaneID][i] = TxPosMeasVoltage[SiteID][MacroID][LaneID][i] - TxNegMeasVoltage[SiteID][MacroID][LaneID][i];
							if (iOffline) {
								TxDiffMeasVoltage[SiteID][MacroID][LaneID][i] = i / 10;
							}
						}

						/*
						hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_P
									 << " Pos Voltage = " << TxPosMeasVoltage[SiteID][MacroID][LaneID] << " [mV]" << endl;
						hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_N
									 << " Neg Voltage = " << TxNegMeasVoltage[SiteID][MacroID][LaneID] << " [mV]" << endl;
						*/
//						hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_P
//									 << " DiffVoltage = " << TxDiffMeasVoltage[SiteID][MacroID][LaneID] << " [mV]" << endl;
					}
				}
			FOREACH_ACTIVESITE_END

			//=============================================
			// measured data process
			//=============================================

			INL.init(0);
			DNL.init(0);
			Gain.init(0);
			Offset.init(0);

			ARRAY_D dnla_main,inla_main;
			LINEARtype  linRes_main;

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						if (hout.getLevel() != 0) {
//							PUT_DEBUG(LANE_INFO[MacroID][LaneID].TX_P,mFIR_SCAN,TxDiffMeasVoltage[SiteID][MacroID][LaneID]);
						}

						//calculate
						if (TxDiffMeasVoltage[SiteID][MacroID][LaneID][SCAN_points - 1] != 0.0) {
							DSP_LINEAR(TxDiffMeasVoltage[SiteID][MacroID][LaneID], &linRes_main, dnla_main, inla_main, MIN_RMS_LSB);
							INL[SiteID][MacroID][LaneID] = linRes_main.iamax;
							DNL[SiteID][MacroID][LaneID] = linRes_main.damax;
							Offset[SiteID][MacroID][LaneID] = TxDiffMeasVoltage[SiteID][MacroID][LaneID][0];	//mV
							Gain[SiteID][MacroID][LaneID] = TxDiffMeasVoltage[SiteID][MacroID][LaneID][SCAN_points - 1];	//mV
						} else {
							hout(RELEASE) << "PPMU ERROR" << endl;
							_exit(0);
						}

						hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_P
									 << "\t" << mFIR_SCAN
									 << "\tINL = " << INL[SiteID][MacroID][LaneID]
									 << "\tDNL = " << DNL[SiteID][MacroID][LaneID]
									 << "\tOffset = " << Offset[SiteID][MacroID][LaneID]
									 << "\tGain = " << Gain[SiteID][MacroID][LaneID]
									 << endl;
					}
				}
			FOREACH_ACTIVESITE_END

			if (iOffline){
				FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
					for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
					{
						UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
						const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

						for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
						{
							UINT LaneID = vLane[laneIndex];
							INL[SiteID][MacroID][LaneID] = 2;
							DNL[SiteID][MacroID][LaneID] = 2;
							if (mFIR_SCAN == "MAIN") {
								if (mPolarity == 0) {
									Gain[SiteID][MacroID][LaneID] = -440;
									Offset[SiteID][MacroID][LaneID] = 0;
								} else {
									Gain[SiteID][MacroID][LaneID] = 440;
									Offset[SiteID][MacroID][LaneID] = 0;
								}
							} else if (mFIR_SCAN == "PRE1ST") {
								if (mPolarity == 0) {
									Gain[SiteID][MacroID][LaneID] = -440;
									Offset[SiteID][MacroID][LaneID] = -230;
								} else {
									Gain[SiteID][MacroID][LaneID] = 440;
									Offset[SiteID][MacroID][LaneID] = 230;
								}
							} else if (mFIR_SCAN == "PRE2ND") {
								if (mPolarity == 0) {
									Gain[SiteID][MacroID][LaneID] = -440;
									Offset[SiteID][MacroID][LaneID] = -230;
								} else {
									Gain[SiteID][MacroID][LaneID] = 440;
									Offset[SiteID][MacroID][LaneID] = 230;
								}
							} else if (mFIR_SCAN == "POST1ST") {
								if (mPolarity == 0) {
									Gain[SiteID][MacroID][LaneID] = -440;
									Offset[SiteID][MacroID][LaneID] = -230;
								} else {
									Gain[SiteID][MacroID][LaneID] = 440;
									Offset[SiteID][MacroID][LaneID] = 230;
								}
							} else if (mFIR_SCAN == "POST2ND") {
								if (mPolarity == 0) {
									Gain[SiteID][MacroID][LaneID] = -440;
									Offset[SiteID][MacroID][LaneID] = -230;
								} else {
									Gain[SiteID][MacroID][LaneID] = 440;
									Offset[SiteID][MacroID][LaneID] = 230;
								}
							}
						}
					}
				FOREACH_ACTIVESITE_END
			}

			if (Global_D2S_Mode == 2) {PatternManager::saveLabel("TxFIR_DynamicDC_sub");}

		//=============================================
		// Judgement&Datalog
		//=============================================
		HiLink_PerLane_Judge(MacroLane_Sel, "INL", 0.0, INL, 0.0, PIN_TXP);
		HiLink_PerLane_Judge(MacroLane_Sel, "DNL", 0.0, DNL, 0.0, PIN_TXP);
		HiLink_PerLane_Judge(MacroLane_Sel, "GAIN", 0.0, Gain, 0.0, PIN_TXP);
		HiLink_PerLane_Judge(MacroLane_Sel, "OFFSET", 0.0, Offset, 0.0, PIN_TXP);

	}
	////////////////////////////////////////////////////////////////////////////////
	// TM Purpose:                                                                //
	// This TM is go through all Tx FIR main values (0~63) and measure Tx         //
	// voltage. It is to check whether the linearity fo Tx FIR main is good.      //
	// It is tested in two patterns, all0 and all1.								  //
	//                                                                            //
	// Parameters:	                                                              //
	// 1. PinList_P: positive pin list to be tested                               //
	// 2. PinList_N: negative pin list to be tested                               //
	// 3. Data: Define Tx pattern generator output patter, all 0 pattern or       //
	//          all 1 pattern.	                                                  //
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
//		static	LANE_DOUBLE					INL;
//		static	LANE_DOUBLE					DNL;
//		static	LANE_DOUBLE					Gain;
//		static	LANE_DOUBLE					Offset;
//		PATTERN_CONTROLLER 					Controller;
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
//			TxFIR_SETTING 		FIR;
//			//=============================================
//			// Variables definition and initialization
//			//=============================================
//			PPMU_SETTING 		Set;
//			PPMU_RELAY   		Rly1,Rly2;
//			PPMU_CLAMP   		Clamp_on, Clamp_off;
//			PPMU_MEASURE 		Meas;
//			TASK_LIST    		Task, TaskSetup, TaskClean;
//
//			DC_RESULT_ACCESSOR 	Result;
//
//			Set.pin(sPinList).iForce(0.001 uA).iRange(10 uA).min(-1 V).max(2 V);
//			Rly1.pin(sPinList).status("ACPM_ON");
//			Rly1.wait(1.3 ms);
//			Rly2.pin(sPinList).status("AC_ON");
//			Rly2.wait(0.3 ms);
//			Clamp_on.pin(sPinList).status("CLAMP_ON").low(-0.8 V).high(0.8 V);
//			Clamp_off.pin(sPinList).status("CLAMP_OFF");
//			Meas.pin(sPinList).measurementType(TM::VMUM);
//
//			Controller.label("TxFIR_DynamicDC_sub","pHilink16_TX").add(Meas);
//			Controller.setup();
//
//			TaskSetup.add(Set).add(Clamp_on).add(Rly1).add(Clamp_off).setup();
//			TaskClean.add(Rly2).setup();
//
//			TaskSetup.execute();
//
//			INT 				SCAN_start, SCAN_stop, SCAN_points;
//			INT 				MainPole, Pre1st, Pre2nd, Post1st, Post2nd;
//			INT 				dMainPole, dPre1st, dPre2nd, dPost1st, dPost2nd;
//
//			if (mFIR_SCAN == "MAIN") {
//				SCAN_start 	= 0;
//				SCAN_stop 	= 63;
//				SCAN_points = 64;
//
//				MainPole 	= 0;
//				Pre1st 		= 0;
//				Pre2nd 		= 0;
//				Post1st 	= 0;
//				Post2nd 	= 0;
//
//				dMainPole 	= 1;
//				dPre1st 	= 0;
//				dPre2nd 	= 0;
//				dPost1st 	= 0;
//				dPost2nd 	= 0;
//			} else if (mFIR_SCAN == "PRE1ST") {
//				SCAN_start 	= -15;
//				SCAN_stop 	= 15;
//				SCAN_points = 31;
//
//				MainPole 	= 0;
//				Pre1st 		= -15;
//				Pre2nd 		= 0;
//				Post1st 	= 0;
//				Post2nd 	= 0;
//
//				dMainPole 	= 0;
//				dPre1st 	= 1;
//				dPre2nd 	= 0;
//				dPost1st 	= 0;
//				dPost2nd 	= 0;
//
//			} else if (mFIR_SCAN == "PRE2ND") {
//				SCAN_start 	= -15;
//				SCAN_stop 	= 15;
//				SCAN_points = 31;
//
//				MainPole 	= 0;
//				Pre1st 		= 0;
//				Pre2nd 		= -15;
//				Post1st 	= 0;
//				Post2nd 	= 0;
//
//				dMainPole 	= 0;
//				dPre1st 	= 0;
//				dPre2nd 	= 1;
//				dPost1st 	= 0;
//				dPost2nd 	= 0;
//			} else if (mFIR_SCAN == "POST1ST") {
//				SCAN_start 	= -15;
//				SCAN_stop 	= 15;
//				SCAN_points = 31;
//
//				MainPole 	= 0;
//				Pre1st 		= 0;
//				Pre2nd 		= 0;
//				Post1st 	= -15;
//				Post2nd 	= 0;
//
//				dMainPole 	= 0;
//				dPre1st 	= 0;
//				dPre2nd 	= 0;
//				dPost1st 	= 1;
//				dPost2nd 	= 0;
//			} else if (mFIR_SCAN == "POST2ND") {
//				SCAN_start 	= -15;
//				SCAN_stop 	= 15;
//				SCAN_points = 31;
//
//				MainPole 	= 0;
//				Pre1st 		= 0;
//				Pre2nd 		= 0;
//				Post1st 	= 0;
//				Post2nd 	= -15;
//
//				dMainPole 	= 0;
//				dPre1st 	= 0;
//				dPre2nd 	= 0;
//				dPost1st 	= 0;
//				dPost2nd 	= 1;
//			}
//
//			//=============================================
//			// Device Setup
//			//=============================================
//
//			D2S_FRAMEWORK;
//			d2s_Dynamic_pHilink_TX & hilink16_tx = d2s_Dynamic_pHilink_TX::Instance();
//			hilink16_tx.getContext();
//			fr.registerTransactionPort(hilink16_tx);
//
//
//			fr.d2s_LABEL_BEGIN("H16LRTV100_MPB_DS_TX_FIR_DYNAMIC_DC_SCAN",d2sFrameWorkModeType::Enum(d2s_mode));
//
//				selectMacro_MB(MacroLane_Sel);
//				DS.Broadcast();
//
//				EnableTxPrbsGen(Custom_ALL0);
//
//				if (mPolarity == 0) {
//					DS.txRegs.settxpolarity(0)
//							 .Write2DUT(2);
//				} else if (mPolarity == 1) {
//					DS.txRegs.settxpolarity(1)
//							 .Write2DUT(2);
//				}
//
//				for (INT i = 0 ; i < SCAN_points; i++) {
//					FIR.iTxPre2nd = Pre2nd;
//					FIR.iTxPre1st = Pre1st;
//					FIR.iTxMain = MainPole;
//					FIR.iTxPost1st = Post1st;
//					FIR.iTxPost2nd = Post2nd;
//
//					SetTxFir(FIR);
//					jtag.wait(40 us);
//
//					fr.synchronizePorts(jtag,hilink16_tx);
//
//					hilink16_tx.execLabel("TxFIR_DynamicDC_pHilink16_TX_STD", 15000);
//
//					fr.synchronizePorts(jtag,hilink16_tx);
//
//					MainPole 	+= dMainPole;
//					Pre1st 		+= dPre1st;
//					Pre2nd 		+= dPre2nd;
//					Post1st 	+= dPost1st;
//					Post2nd 	+= dPost2nd;
//				}
//
//			fr.d2s_LABEL_END();
//
//			TM::RESULT_RANGE resultRange = Result.getRangeOfAvailableResults(sPinList, TM::RESULT_INDEX);
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
//						Result.uploadResult(LANE_INFO[MacroID][LaneID].TX_P, resultRange);
//						Result.uploadResult(LANE_INFO[MacroID][LaneID].TX_N, resultRange);
//					}
//				}
//			FOR_EACH_SITE_END();
//
//
//			/*****************[MacroID][LaneID][ScanPoint]************/
//			LANE_ARRAY_D 							TxPosMeasVoltage;
//			LANE_ARRAY_D 							TxNegMeasVoltage;
//			LANE_ARRAY_D 							TxDiffMeasVoltage;
//
//			TxPosMeasVoltage.init(SCAN_points,0);
//			TxNegMeasVoltage.init(SCAN_points,0);
//			TxDiffMeasVoltage.init(SCAN_points,0);
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
//						if (!iOffline) {
//							TxPosMeasVoltage[SiteID][MacroID][LaneID] = Result.getValues(LANE_INFO[MacroID][LaneID].TX_P) * 1e3;
//							TxNegMeasVoltage[SiteID][MacroID][LaneID] = Result.getValues(LANE_INFO[MacroID][LaneID].TX_N) * 1e3;
//						}
//
//						for (INT i = 0 ; i < SCAN_points; i++) {
//							TxDiffMeasVoltage[SiteID][MacroID][LaneID][i] = TxPosMeasVoltage[SiteID][MacroID][LaneID][i] - TxNegMeasVoltage[SiteID][MacroID][LaneID][i];
//							if (iOffline) {
//								TxDiffMeasVoltage[SiteID][MacroID][LaneID][i] = i / 10;
//							}
//						}
//
//						/*
//						hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_P
//									 << " Pos Voltage = " << TxPosMeasVoltage[SiteID][MacroID][LaneID] << " [mV]" << endl;
//						hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_N
//									 << " Neg Voltage = " << TxNegMeasVoltage[SiteID][MacroID][LaneID] << " [mV]" << endl;
//						*/
//						hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_P
//									 << " DiffVoltage = " << TxDiffMeasVoltage[SiteID][MacroID][LaneID] << " [mV]" << endl;
//					}
//				}
//			FOR_EACH_SITE_END();
//
//			TaskClean.execute();
//
//			//=============================================
//			// measured data process
//			//=============================================
//
//			INL.init(0);
//			DNL.init(0);
//			Gain.init(0);
//			Offset.init(0);
//
//			ARRAY_D 					dnla_main,inla_main;
//			LINEARtype  				linRes_main;
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
//						if (hout.getLevel() != 0) {
//							PUT_DEBUG(LANE_INFO[MacroID][LaneID].TX_P,mFIR_SCAN,TxDiffMeasVoltage[SiteID][MacroID][LaneID]);
//						}
//
//						//calculate
//						if (TxDiffMeasVoltage[SiteID][MacroID][LaneID][SCAN_points - 1] != 0.0) {
//							DSP_LINEAR(TxDiffMeasVoltage[SiteID][MacroID][LaneID], &linRes_main, dnla_main, inla_main, MIN_RMS_LSB);
//							INL[SiteID][MacroID][LaneID] = linRes_main.iamax;
//							DNL[SiteID][MacroID][LaneID] = linRes_main.damax;
//							Offset[SiteID][MacroID][LaneID] = TxDiffMeasVoltage[SiteID][MacroID][LaneID][0];	//mV
//							Gain[SiteID][MacroID][LaneID] = TxDiffMeasVoltage[SiteID][MacroID][LaneID][SCAN_points - 1];	//mV
//						} else {
//							hout(RELEASE) << "PPMU ERROR" << endl;
//							_exit(0);
//						}
//
//						hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_P
//									 << "\t" << mFIR_SCAN
//									 << "\tINL = " << INL[SiteID][MacroID][LaneID]
//									 << "\tDNL = " << DNL[SiteID][MacroID][LaneID]
//									 << "\tOffset = " << Offset[SiteID][MacroID][LaneID]
//									 << "\tGain = " << Gain[SiteID][MacroID][LaneID]
//									 << endl;
//					}
//				}
//			FOR_EACH_SITE_END();
//
//
//			if (iOffline){
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
//							INL[SiteID][MacroID][LaneID] = 2;
//							DNL[SiteID][MacroID][LaneID] = 2;
//							if (mFIR_SCAN == "MAIN") {
//								if (mPolarity == 0) {
//									Gain[SiteID][MacroID][LaneID] = -440;
//									Offset[SiteID][MacroID][LaneID] = 0;
//								} else {
//									Gain[SiteID][MacroID][LaneID] = 440;
//									Offset[SiteID][MacroID][LaneID] = 0;
//								}
//							} else if (mFIR_SCAN == "PRE1ST") {
//								if (mPolarity == 0) {
//									Gain[SiteID][MacroID][LaneID] = -440;
//									Offset[SiteID][MacroID][LaneID] = -230;
//								} else {
//									Gain[SiteID][MacroID][LaneID] = 440;
//									Offset[SiteID][MacroID][LaneID] = 230;
//								}
//							} else if (mFIR_SCAN == "PRE2ND") {
//								if (mPolarity == 0) {
//									Gain[SiteID][MacroID][LaneID] = -440;
//									Offset[SiteID][MacroID][LaneID] = -230;
//								} else {
//									Gain[SiteID][MacroID][LaneID] = 440;
//									Offset[SiteID][MacroID][LaneID] = 230;
//								}
//							} else if (mFIR_SCAN == "POST1ST") {
//								if (mPolarity == 0) {
//									Gain[SiteID][MacroID][LaneID] = -440;
//									Offset[SiteID][MacroID][LaneID] = -230;
//								} else {
//									Gain[SiteID][MacroID][LaneID] = 440;
//									Offset[SiteID][MacroID][LaneID] = 230;
//								}
//							} else if (mFIR_SCAN == "POST2ND") {
//								if (mPolarity == 0) {
//									Gain[SiteID][MacroID][LaneID] = -440;
//									Offset[SiteID][MacroID][LaneID] = -230;
//								} else {
//									Gain[SiteID][MacroID][LaneID] = 440;
//									Offset[SiteID][MacroID][LaneID] = 230;
//								}
//							}
//						}
//					}
//				FOR_EACH_SITE_END();
//			}
//
//			if (d2s_mode == 2) {PatternManager::saveLabel("TxFIR_DynamicDC_sub");}
//
//			ON_FIRST_INVOCATION_END();
//		//=============================================
//		// Judgement&Datalog
//		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "INL", INL, PIN_TXP);
//		HiLink_PerLane_Judge(MacroLane_Sel, "DNL", DNL, PIN_TXP);
//		HiLink_PerLane_Judge(MacroLane_Sel, "GAIN", Gain, PIN_TXP);
//		HiLink_PerLane_Judge(MacroLane_Sel, "OFFSET", Offset, PIN_TXP);
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
REGISTER_TESTCLASS("TxFIR_DC_Dynamic", TxFIR_DC_Dynamic);
