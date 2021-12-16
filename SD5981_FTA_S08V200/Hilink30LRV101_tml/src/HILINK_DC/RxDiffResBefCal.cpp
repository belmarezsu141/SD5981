//for test method API interfaces

#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"

/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */

class RxDiffResBefCal_VFIM: public TestClass {
public:
	STRING 				mHiLink30_MacroList;
	STRING 				mPinList;
	DOUBLE 				mRange_vol;
	DOUBLE 				mStep_vol;
	STRING 				mPinList_P;
	STRING 				mPinList_N;
	DOUBLE              mForceV;
	INT 				iPrintLvl;

	void init() {
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					 .set_comment("HiLink30 Macro List for test")
					 //.setOptions("0,1:0:1:FromPinList")
					 .set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
		add_param("ForceV[mV]","double",&mForceV)
					 .set_comment("ForceV on RxPinsP")
					 .set_comment("Unit mV")
					 .set_default("500");
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
		INT iDebugAnalog;
		INT iOffline;
		static INT iCSR_check;
		static MACRO_LANE_SEL MacroLane_Sel;
		static LANE_DOUBLE vRxPosMeasCurrent;
		static LANE_DOUBLE vRxNegMeasCurrent;
		static LANE_DOUBLE vRxPosMeasRes;
		static LANE_DOUBLE vRxNegMeasRes;
		static LANE_DOUBLE vRxDiffMeasRes;
		static bool CSRVerifyResult;
//		STRING mPinList_P;
//		STRING mPinList_N;

//		static STRING mPinList = "";
		stRxDiffResBefCal_VFIM& RxDiffResBefCal_VFIM =
				H30_RxdiffResBefCal_VDDN_RxDiffResBefCal_VFIM;
//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);

//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

	    hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel,mHiLink30_MacroList, mPinList);

		get_pinlists( MacroLane_Sel, mPinList_P, mPinList_N, mPinList);

		//=============================================
		// Device Setup
		//=============================================

		d2s::d2s_LABEL_BEGIN(  "MPB_DS_RX_RES_AFT_CAL_",Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);
		DS.rxRegs.SliceID(0).Broadcast(1);
		DS.rxRegs.setrxtermfloating(1).Write2DUT(32);
//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();

		//=============================================
		// Variables definition and initialization
		//=============================================
		vRxPosMeasCurrent.init(0);
		vRxNegMeasCurrent.init(0);
		vRxPosMeasRes.init(0);
		vRxNegMeasRes.init(0);
		vRxDiffMeasRes.init(0);

		double *data1;
		double resource[48] = { 0 };

		double mForceV = -0.25;
//		api->Execute_test("H30LR_Rx_setupN");
		H30LR_Rx_setupN();


//		api->Execute_test("H30LR_RxDiffBefCAL_ForceP");
		PinArrayDouble H30LR_RxDiffBefCAL_ForceP_result =H30LR_RxDiffBefCAL_ForceP();
		if(PrintDebugEn)  H30LR_RxDiffBefCAL_ForceP_result.ShowPinArrayData();
		data1 = resource;		/////初始化指针


		vector<string> PinList_P = {"RX_SDS0_P","RX_SDS1_P","RX_SDS2_P","RX_SDS3_P"};
		vector<string> PinList_N = {"RX_SDS0_N","RX_SDS1_N","RX_SDS2_N","RX_SDS3_N"};

		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

		for(int signalIndx = 0 ;signalIndx <PinList_P.size();signalIndx++)
		{
			data1[signalIndx]= H30LR_RxDiffBefCAL_ForceP_result.GetData(PinList_P[signalIndx],SiteID);
//			data2[signalIndx]= H30LR_TxTermVolt_MForce_I_0mA_result.GetData(PinList_N[signalIndx],SiteID);
		}
		FOREACH_ACTIVESITE_END

//		FOREACH_ACTIVE_SITE(api)
//		{
//			unsigned int SiteID = api->Get_active_site();
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

//			api->Get_dctest_values("H30LR_RxDiffResBefCal_MforceV_MI_RX_250mV_group","gSDS_H30LR_RX_P", 0, THE_MEASURE, &data1, THE_END);//modify by tony 20210525 add "_group"

			int iSginal;
			iSginal = 0;

			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size();
					macroIndex++) {
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

				for (UINT laneIndex = 0; laneIndex < vLane.size();
						laneIndex++) {
					UINT LaneID = vLane[laneIndex];

					vRxPosMeasCurrent[SiteID][MacroID][LaneID] = data1[iSginal];
					iSginal = iSginal + 1;

					vRxDiffMeasRes[SiteID][MacroID][LaneID] = mForceV
							/ vRxPosMeasCurrent[SiteID][MacroID][LaneID];// advice "- 10" as offset

				}

			}
			FOREACH_ACTIVESITE_END

		//=============================================
		// Datalog
		//=============================================

		double LimitL = 89;
		double LimitH = 137.2;
		HiLink_PerLane_Judge( MacroLane_Sel, "H30_RxDiffRes", LimitL,vRxDiffMeasRes, LimitH);

		SetTestBin ();
	}

};
REGISTER_TESTCLASS("RxDiffResBefCal_VFIM", RxDiffResBefCal_VFIM)

