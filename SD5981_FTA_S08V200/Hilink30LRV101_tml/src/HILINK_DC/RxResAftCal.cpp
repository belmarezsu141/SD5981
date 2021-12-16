
#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"

using namespace std;

class RxResAftCal_VFIM: public TestClass {
public:

	STRING 				mHiLink30_MacroList;
	STRING 				mPinList;
	STRING              mTXPinList;
	DOUBLE 				mRange_vol;
	DOUBLE 				mStep_vol;
	STRING 				mPinList_P;
	STRING 				mPinList_N;
	STRING              mTXPinList_P;
	STRING              mTXPinList_N;
	STRING				mMeasureMode;
	INT					iPrintLvl;
	void init() {
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					 .set_comment("HiLink30 Macro List for test")
					 //.setOptions("0,1:0:1:FromPinList")
					 .set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
		add_param("Range_vol","double",&mRange_vol)
					 .set_comment("in unit mV")
		 	 	 	 .set_default("500");
		add_param("Step_vol","double",&mStep_vol)
					 .set_comment("in unit mV")
					 .set_default("50");
		add_param("Test_Mode","string",&mMeasureMode)
					 .set_comment("Choose Sig or Diff Mode")
					 //.setOptions("Sig:Diff")
					 .set_default("Sig");
		add_param("PrintLvl[0~8]","int",&iPrintLvl)
					.set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
					"0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					//.setOptions("0:1:3:4:7:8")
					.set_default("3");
	}
	void execute() {

		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
		H30_FailBin_Flag.init(0);
		STRING mTXPinList;
		DOUBLE mRange_vol;
		DOUBLE mStep_vol;
//		STRING mPinList_P;
//		STRING mPinList_N;
		STRING mTXPinList_P;
		STRING mTXPinList_N;
		STRING mMeasureMode;

		INT iDebugAnalog;
//  		STRING          			sTestsuiteName;
		INT iOffline;
		static INT iCSR_check;
		static MACRO_LANE_SEL MacroLane_Sel;
		static LANE_DOUBLE vRxPosMeasCurrent;
		static LANE_DOUBLE vRxNegMeasCurrent;
		static LANE_DOUBLE vRxPosMeasRes;
		static LANE_DOUBLE vRxNegMeasRes;
		static LANE_DOUBLE vRxDiffMeasRes;
		static LANE_DOUBLE vMinPosRes;
		static LANE_DOUBLE vMaxPosRes;
		static LANE_DOUBLE vMinNegRes;
		static LANE_DOUBLE vMaxNegRes;
		static LANE_DOUBLE vMaxDiffRes;
		static LANE_DOUBLE vMinDiffRes;
		static LANE_DOUBLE vRxPosMeasCurrent_PrevStep;
		static LANE_DOUBLE vRxNegMeasCurrent_PrevStep;
		static LANE_DOUBLE vRxDiffMeasCurrent_PrevStep;
		static bool CSRVerifyResult;

//		STRING mPinList;
//		ON_FIRST_INVOCATION_BEGIN();
//
//		GET_SYSTEM_FLAG		("offline",&iOffline);
//		GET_TESTSUITE_NAME	(sTestsuiteName);
//		GET_TESTFLOW_FLAG	("debug_analog",&iDebugAnalog);
//		GET_USER_FLAG		("CSR_atomic_operation",&iCSR_check);

		stRxResAftCal_VFIM RxResAftCal_VFIM;		//=SSbandGap_SSBandGap;

//                static STRING mPinList="";
//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);

//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

		if (strTestsuiteName == "H30_RxSigResAftCal_VDDN")		////PLL0_1G  1
				{
			RxResAftCal_VFIM = H30_RxSigResAftCal_VDDN_RxResAftCal_VFIM;
		} else if (strTestsuiteName == "H30_RxDiffResAftCal_VDDN") {
			RxResAftCal_VFIM = H30_RxDiffResAftCal_VDDN_RxResAftCal_VFIM;

		}

		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList,mPinList);


		get_pinlists( MacroLane_Sel, mPinList_P, mPinList_N, mPinList,"RX");


		//=============================================
		// Device Setup
		//=============================================
//		D2S_FRAMEWORK;
//		GET_TEST_INFO;

//		sprintf(label,"MPB_DS_RX_RES_AFT_CAL_PRBS_ALL0_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN("MPB_DS_RX_RES_AFT_CAL_PRBS_ALL0_", Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);
		DS.txRegs.SliceID(0).Broadcast(1);
		DS.rxRegs.SliceID(0).Broadcast(1);
		EnableTxPrbsGen( "CUSTOMER_PATTERN", 0x0000);
		if (mMeasureMode == "Sig") {
			DS.rxRegs.setrxtermfloating(0).Write2DUT(32);
		} else if (mMeasureMode == "Diff") {
			DS.rxRegs.setrxtermfloating(1).Write2DUT(32);
		}

//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();

		vRxPosMeasCurrent.init(0);
		vRxNegMeasCurrent.init(0);
		vRxPosMeasRes.init(0);
		vRxNegMeasRes.init(0);
		vRxDiffMeasRes.init(0);

		double data1[48]={ 0 };
		double data2[48]={ 0 };
//		double resource[48] = { 0 };
//		double resource[48] = { 0 };

		double mForceV = 0.25;
		PinArrayDouble result_P;
		PinArrayDouble result_All;
//		data1 = resource;		/////初始化指针
//		data2 = resource;		/////初始化指针

		vector<string> PinList_P = {"RX_SDS0_P","RX_SDS1_P","RX_SDS2_P","RX_SDS3_P"};
		vector<string> PinList_N = {"RX_SDS0_N","RX_SDS1_N","RX_SDS2_N","RX_SDS3_N"};

		if (mMeasureMode == "Diff") {
//			api->Execute_test("H30LR_Rx_setupN");
//			api->Execute_test("H30LR_RxDiffAftCAL_ForceP");
			H30LR_Rx_setupN();
			PinArrayDouble result_P = H30LR_RxDiffAftCAL_ForceP();

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

			for(int signalIndx = 0 ;signalIndx <PinList_P.size();signalIndx++)
			{
				data1[signalIndx]= result_P.GetData(PinList_P[signalIndx],SiteID);
//				data2[signalIndx]= H30LR_TxTermVolt_MForce_I_0mA_result.GetData(PinList_N[signalIndx],SiteID);
			}
			FOREACH_ACTIVESITE_END


		} else if (mMeasureMode == "Sig") {
//			api->Execute_test("H30LR_Rx_setupN");
//			api->Execute_test("H30LR_RxSigAftCAL_ForceAll");
			H30LR_Rx_setupN();
			PinArrayDouble result_All= H30LR_RxSigAftCAL_ForceAll();
			if(PrintDebugEn)  result_All.ShowPinArrayData();

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

			for(int signalIndx = 0 ;signalIndx <PinList_P.size();signalIndx++)
			{
				data1[signalIndx]= result_All.GetData(PinList_P[signalIndx],SiteID);
				data2[signalIndx]= result_All.GetData(PinList_N[signalIndx],SiteID);

//				cout<<"==data1["<<PinList_P[signalIndx]<<"="<< data1[signalIndx]<<endl;
//				cout<<"==data2["<<PinList_N[signalIndx]<<"="<< data2[signalIndx]<<endl;
			}
			FOREACH_ACTIVESITE_END
		}


//		FOREACH_ACTIVE_SITE(api)
//		{
//			unsigned int SiteID = api->Get_active_site();
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

//		if (mMeasureMode == "Diff") {
////				api->Get_dctest_values("H30LR_RxDiffResAftCal_MforceV_MI_RX_250mV_group","gSDS_H30LR_RX_P", 0, THE_MEASURE, &data1, THE_END);//modify by tony 20210525 add "_group"
//				for(int i =0 ;i<PinLists_RX_P.size();i++)
//					data1[i] =  result_P.GetData(PinLists_RX_P[i],SiteID);
//
//
//			} else if (mMeasureMode == "Sig") {
//				for(int i =0 ;i<PinLists_RX_P.size();i++)
//					data1[i] =  result_All.GetData(PinLists_RX_P[i],SiteID);
//				for(int i =0 ;i<PinLists_RX_N.size();i++)
//					data2[i] =  result_All.GetData(PinLists_RX_N[i],SiteID);
////				api->Get_dctest_values("H30LR_RxSigResAftCal_MforceV_MI_RX_250mV_group","gSDS_H30LR_RX_P", 0, THE_MEASURE, &data1, THE_END);
////				api->Get_dctest_values("H30LR_RxSigResAftCal_MforceV_MI_RX_250mV_group","gSDS_H30LR_RX_N", 0, THE_MEASURE, &data2, THE_END);
//			}
			int iSginal;
			iSginal = 0;

			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size();
					macroIndex++) {
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

				for (UINT laneIndex = 0; laneIndex < vLane.size();
						laneIndex++) {
					UINT LaneID = vLane[laneIndex];
					if (mMeasureMode == "Diff") {
						vRxPosMeasCurrent[SiteID][MacroID][LaneID] =
								data1[iSginal];	//mA

					} else if (mMeasureMode == "Sig") {
						vRxPosMeasCurrent[SiteID][MacroID][LaneID] =
								data1[iSginal];	//mA
						vRxNegMeasCurrent[SiteID][MacroID][LaneID] =
								data2[iSginal];	//mA
					}

					iSginal = iSginal + 1;

//					cout<<"=data1=vRxPosMeasCurrent[SiteID][MacroID][LaneID]="<< vRxPosMeasCurrent[SiteID][MacroID][LaneID]<<endl;
//					cout<<"=data2=vRxPosMeasCurrent[SiteID][MacroID][LaneID]="<< vRxNegMeasCurrent[SiteID][MacroID][LaneID]<<endl;

					if (mMeasureMode == "Diff") {
						vRxDiffMeasRes[SiteID][MacroID][LaneID] = mForceV
								/ vRxPosMeasCurrent[SiteID][MacroID][LaneID];
//								- 50;
					} else if (mMeasureMode == "Sig") {
						vRxPosMeasRes[SiteID][MacroID][LaneID] = mForceV
								/ vRxPosMeasCurrent[SiteID][MacroID][LaneID];
						vRxNegMeasRes[SiteID][MacroID][LaneID] = mForceV
								/ vRxNegMeasCurrent[SiteID][MacroID][LaneID];
					}

				}

			}
			FOREACH_ACTIVESITE_END

		//=============================================
		// Datalog
		//=============================================

		if (mMeasureMode == "Diff") {
			double LimitL = 89;
			double LimitH =  137.2;
			HiLink_PerLane_Judge( MacroLane_Sel, "H30_RxDiffRes", LimitL,
					vRxDiffMeasRes, LimitH);
		} else if (mMeasureMode == "Sig") {
			double LimitL = 50;
			double LimitH = 74;
			HiLink_PerLane_Judge( MacroLane_Sel, "H30_RxSigRes_P", LimitL,
					vRxPosMeasRes, LimitH, PIN_RXP);
			HiLink_PerLane_Judge( MacroLane_Sel, "H30_RxSigRes_N", LimitL,
					vRxNegMeasRes, LimitH, PIN_RXN);
		}

		SetTestBin ();
	}

};
REGISTER_TESTCLASS("RxResAftCal_VFIM", RxResAftCal_VFIM)

