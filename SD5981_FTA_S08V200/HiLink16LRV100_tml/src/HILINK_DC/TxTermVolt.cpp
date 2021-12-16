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
class TxTermVolt: public TestClass {

public:
	STRING 				mHiLink16_MacroList;
	STRING 				mPinList;
	STRING 				sPinList;
	STRING 				sPinList_P;
	STRING 				sPinList_N;
	INT  				iPolarity;
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
		add_param("Polarity","int",&iPolarity);
					 //.set_options("0:1");
		add_param("PrintLvl[0~15]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 10000(16)"
							     "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYE_PLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.set_options("0:1:3:4:7:9")
					 .set_default("3");
	}

	//================Hi1213=================
	void TxVoltMeas(const MACRO_LANE_SEL MacroLane_Sel,STRING& sPinList, LANE_DOUBLE &TxPosMeasVoltage,LANE_DOUBLE &TxNegMeasVoltage)
	{
		double irange = 5e-3;
		double vExpect = 1.5;
		int sampleSize =64;
		double waittime =3e-3;

		////=====================
		///// measure Pos & Neg
		////=====================

		string Pins = "gHILINK_TxP,gHILINK_TxN";
		PinArrayDouble Meas = PPMU_FIMV_measure(Pins,-0.01 *uA,vExpect,waittime,sampleSize);

		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
				{
					UINT LaneID = vLane[laneIndex];
					TxPosMeasVoltage[SiteID][MacroID][LaneID] = Meas.GetData(LANE_INFO[MacroID][LaneID].TX_P,SiteID) / (1 *mV);
					TxNegMeasVoltage[SiteID][MacroID][LaneID] = Meas.GetData(LANE_INFO[MacroID][LaneID].TX_N,SiteID) / (1 *mV);

					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_P <<  " Voltage = "  << TxPosMeasVoltage[SiteID][MacroID][LaneID] << " mV" << endl;
					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_N <<  " Voltage = "  << TxNegMeasVoltage[SiteID][MacroID][LaneID] << " mV" << endl;
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

		static	LANE_DOUBLE 		TxPosMeasVoltage;
		static	LANE_DOUBLE 		TxNegMeasVoltage;

		//=============================================
		// Variables and MacroLane initialization
		//=============================================
		GET_SYSTEM_FLAG	("offline",iOffline); iOffline =0;
		GET_TESTSUITE_NAME	(sTestsuiteName);
		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

		GetTxPinList(MacroLane_Sel, sPinList_P, sPinList_N, sPinList);
		//=============================================
		// Device Setup
		//=============================================
//		D2S_FRAMEWORK;

		INT iTxRegRefLvl = DS.txRegs.gettxregdrvlvl();
//		sprintf(label,"H16LRTV100_MPB_TxTermVolt_Setup_TxRegDrvLvl%d",CUSTpara.TxRegDrvLvl);
		sprintf(label,"H16LRTV100_MPB_TxTermVolt_Setup_TxRegDrvLvl%d",iTxRegRefLvl);
		d2s::d2s_LABEL_BEGIN(label,Global_D2S_Mode);
			selectMacro_MB(MacroLane_Sel);
			DS.Broadcast();

			EnableTxPrbsGen(Custom_ALL0);

			if (iPolarity == 0) {
				DS.txRegs.settxpolarity(0).Write2DUT(2);
			} else if (iPolarity == 1) {
				DS.txRegs.settxpolarity(1).Write2DUT(2);
			} else {
				hout (RELEASE) << "Please Select correct polarity 0 or 1 !!!!" << endl;
				_exit(0);
			}

		d2s::d2s_LABEL_END();

		//=============================================
		// Measurement
		//=============================================
		TxPosMeasVoltage.init(0);
		TxNegMeasVoltage.init(0);

		TxVoltMeas(MacroLane_Sel,sPinList,TxPosMeasVoltage,TxNegMeasVoltage);

		if (iOffline) {
			if (iTxRegRefLvl == 0) {
				if (iPolarity == 0) {
					FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
						for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
						{
							UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
							const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

							for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
							{
								UINT LaneID = vLane[laneIndex];
								TxPosMeasVoltage[SiteID][MacroID][LaneID] = 0;
								TxNegMeasVoltage[SiteID][MacroID][LaneID] = 460;
							}
						}
					FOREACH_ACTIVESITE_END
				} else {
					FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
						for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
						{
							UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
							const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

							for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
							{
								UINT LaneID = vLane[laneIndex];
								TxPosMeasVoltage[SiteID][MacroID][LaneID] = 460;
								TxNegMeasVoltage[SiteID][MacroID][LaneID] = 0;							}
						}
					FOREACH_ACTIVESITE_END
				}
			} else {
				if (iPolarity == 0) {
					FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
						for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
						{
							UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
							const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

							for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
							{
								UINT LaneID = vLane[laneIndex];
								TxPosMeasVoltage[SiteID][MacroID][LaneID] = 0;
								TxNegMeasVoltage[SiteID][MacroID][LaneID] = 595;
							}
						}
					FOREACH_ACTIVESITE_END
				} else {
					FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
						for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
						{
							UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
							const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

							for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
							{
								UINT LaneID = vLane[laneIndex];
								TxPosMeasVoltage[SiteID][MacroID][LaneID] = 595;
								TxNegMeasVoltage[SiteID][MacroID][LaneID] = 0;
							}
						}
					FOREACH_ACTIVESITE_END
				}
			}
		}

		//=============================================
		// Datalog
		//=============================================
		HiLink_PerLane_Judge(MacroLane_Sel, "TxTermVolt_POS", 0.0, TxPosMeasVoltage, 0.0, PIN_TXP);
		HiLink_PerLane_Judge(MacroLane_Sel, "TxTermVolt_NEG", 0.0, TxNegMeasVoltage, 0.0, PIN_TXN);

	}

//===================================93K=====================
//
//	void TxVoltMeas(const MACRO_LANE_SEL MacroLane_Sel,STRING& sPinList, LANE_DOUBLE &TxPosMeasVoltage,LANE_DOUBLE &TxNegMeasVoltage)
//	{
//		PPMU_SETTING ppmu_set;
//		PPMU_RELAY   Rly_acpm,Rly_ac;
//		PPMU_MEASURE Meas;
//		TASK_LIST    taskList;
//		PPMU_CLAMP   ppmu_clamp_enable, ppmu_clamp_disable;
//
//		ppmu_set.pin(sPinList).iForce(0.0 uA).iRange(10 uA).min(0 V).max(2 V);
//		ppmu_clamp_enable.pin(sPinList).status("CLAMP_ON").low(-800 mV).high(800 mV);
//		Rly_acpm.pin(sPinList).status("ACPM_ON");
//		Rly_acpm.wait(1.3 ms);
//		Rly_ac.pin(sPinList).status("AC_ON");
//		Rly_ac.wait(0.3 ms);
//		ppmu_clamp_disable.pin(sPinList).status("CLAMP_OFF");
//		ppmu_clamp_disable.wait(0.3 ms);
//		Meas.pin(sPinList).execMode(TM::OVAL);
//		taskList.add(ppmu_set).add(ppmu_clamp_enable).add(Rly_acpm).add(ppmu_clamp_disable).add(Meas).add(Rly_ac).setup();
//		taskList.execute();
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
//					TxPosMeasVoltage[SiteID][MacroID][LaneID] = Meas.getValue(LANE_INFO[MacroID][LaneID].TX_P) / (1 mV);
//					TxNegMeasVoltage[SiteID][MacroID][LaneID] = Meas.getValue(LANE_INFO[MacroID][LaneID].TX_N) / (1 mV);
//
//					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_P <<  " Voltage = "  << TxPosMeasVoltage[SiteID][MacroID][LaneID] << " mV" << endl;
//					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_N <<  " Voltage = "  << TxNegMeasVoltage[SiteID][MacroID][LaneID] << " mV" << endl;
//				}
//			}
//		FOR_EACH_SITE_END();
//	}
	////////////////////////////////////////////////////////////////////////////////
	// TM Purpose:                                                                //
	// This TM is for voltage measurement by using BADC, in different conditions: //
	// all0 pattern or all1 pattern, Tx FIR amp as 0 or 7.                        //
	//                                                                            //
	// Parameters:                                                                //
	// 1. PinList_P: positive pin list to be tested                               //
	// 2. PinList_N: negative pin list to be tested                               //
	// 3. Pattern: Define pattern, all 0 pattern or all 1 pattern                 //
	// 4. Amp: Setup Tx FIR amplitude value, option 0 or 7                        //
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
//		static	LANE_DOUBLE 		TxPosMeasVoltage;
//		static	LANE_DOUBLE 		TxNegMeasVoltage;
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
//			//=============================================
//			// Device Setup
//			//=============================================
//			D2S_FRAMEWORK;
//
//			sprintf(label,"H16LRTV100_MPB_TxTermVolt_Setup_TxRegDrvLvl%d",CUSTpara.TxRegDrvLvl);
//			fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
//
//				selectMacro_MB(MacroLane_Sel);
//				DS.Broadcast();
//
//				EnableTxPrbsGen(Custom_ALL0);
//
//				if (iPolarity == 0) {
//					DS.txRegs.settxpolarity(0).Write2DUT(2);
//				} else if (iPolarity == 1) {
//					DS.txRegs.settxpolarity(1).Write2DUT(2);
//				} else {
//					hout (RELEASE) << "Please Select correct polarity 0 or 1 !!!!" << endl;
//					_exit(0);
//				}
//
//			fr.d2s_LABEL_END();
//
//			//=============================================
//			// Measurement
//			//=============================================
//			TxPosMeasVoltage.init(0);
//			TxNegMeasVoltage.init(0);
//
//			TxVoltMeas(MacroLane_Sel,sPinList,TxPosMeasVoltage,TxNegMeasVoltage);
//
//			if (iOffline) {
//				if (CUSTpara.TxRegDrvLvl == 0) {
//					if (iPolarity == 0) {
//						FOR_EACH_SITE_BEGIN();
//							INT SiteID = CURRENT_SITE_NUMBER() - 1;
//							for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
//							{
//								UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//								const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//
//								for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
//								{
//									UINT LaneID = vLane[laneIndex];
//									TxPosMeasVoltage[SiteID][MacroID][LaneID] = 0;
//									TxNegMeasVoltage[SiteID][MacroID][LaneID] = 460;
//								}
//							}
//						FOR_EACH_SITE_END();
//					} else {
//						FOR_EACH_SITE_BEGIN();
//							INT SiteID = CURRENT_SITE_NUMBER() - 1;
//							for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
//							{
//								UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//								const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//
//								for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
//								{
//									UINT LaneID = vLane[laneIndex];
//									TxPosMeasVoltage[SiteID][MacroID][LaneID] = 460;
//									TxNegMeasVoltage[SiteID][MacroID][LaneID] = 0;							}
//							}
//						FOR_EACH_SITE_END();
//					}
//				} else {
//					if (iPolarity == 0) {
//						FOR_EACH_SITE_BEGIN();
//							INT SiteID = CURRENT_SITE_NUMBER() - 1;
//							for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
//							{
//								UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//								const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//
//								for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
//								{
//									UINT LaneID = vLane[laneIndex];
//									TxPosMeasVoltage[SiteID][MacroID][LaneID] = 0;
//									TxNegMeasVoltage[SiteID][MacroID][LaneID] = 595;
//								}
//							}
//						FOR_EACH_SITE_END();
//					} else {
//						FOR_EACH_SITE_BEGIN();
//							INT SiteID = CURRENT_SITE_NUMBER() - 1;
//							for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
//							{
//								UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//								const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//
//								for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
//								{
//									UINT LaneID = vLane[laneIndex];
//									TxPosMeasVoltage[SiteID][MacroID][LaneID] = 595;
//									TxNegMeasVoltage[SiteID][MacroID][LaneID] = 0;
//								}
//							}
//						FOR_EACH_SITE_END();
//					}
//				}
//			}
//
//		ON_FIRST_INVOCATION_END();
//
//		//=============================================
//		// Datalog
//		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "TxTermVolt_POS", TxPosMeasVoltage, PIN_TXP);
//		HiLink_PerLane_Judge(MacroLane_Sel, "TxTermVolt_NEG", TxNegMeasVoltage, PIN_TXN);
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
REGISTER_TESTCLASS("TxTermVolt", TxTermVolt);
