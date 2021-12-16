//for test method API interfaces
//#include "mapi.hpp"

#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"

using namespace std;

class RxSigResBefCal_IFVM: public TestClass
{
public:
	STRING 				mHiLink30_MacroList;
	STRING 				mPinList;
	DOUBLE 				mCurrentSource1_mA;
	DOUBLE 				mCurrentSource2_mA;
	STRING 				mPinList_P;
	STRING 				mPinList_N;
	INT 				iPrintLvl;


	void init()
	{
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					 .set_comment("HiLink30 Macro List for test")
					 //.setOptions("0,1:0:1:FromPinList")
					 .set_default("0,1");
		add_param("CurrentSource1_mA","double",&mCurrentSource1_mA)
					 .set_default("-5")
					 .set_comment("first Source current");
		add_param("CurrentSource2_mA","double",&mCurrentSource2_mA)
					 .set_default("-1")
					 .set_comment("second Source current");
		add_param("PrintLvl[0~8]","int",&iPrintLvl)
					.set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
					"0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					//.setOptions("0:1:3:4:7:8")
					.set_default("3");
	}
	void execute()
	{

		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
		H30_FailBin_Flag.init(0);
		INT iDebugAnalog;
		INT iOffline;
		static INT iCSR_check;
		static MACRO_LANE_SEL MacroLane_Sel;
		static LANE_DOUBLE vRxPosMeasVoltage1;
		static LANE_DOUBLE vRxNegMeasVoltage1;
		static LANE_DOUBLE vRxPosMeasVoltage2;
		static LANE_DOUBLE vRxNegMeasVoltage2;
		static LANE_DOUBLE vRxSigPosMeasRes;
		static LANE_DOUBLE vRxSigNegMeasRes;
		static bool CSRVerifyResult;

//		STRING mPinList_P;
//		STRING mPinList_N;

//		static STRING mPinList = "";
		stRxSigResBefCal_IFVM& RxSigResBefCal_IFVM =
				H30_RxSigResBefCal_VDDN_RxSigResBefCal_IFVM;
//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

		hout.setLevel(iPrintLvl);

		hout(DETAIL) << "\n\n============" << "Test Suite Name: "
				<< sTestsuiteName << "============" << endl;

		Select_Macro_Lane(MacroLane_Sel,mHiLink30_MacroList, mPinList);
		get_pinlists(MacroLane_Sel, mPinList_P, mPinList_N, mPinList);

		//=============================================
		// Device Setup
		//=============================================

		d2s::d2s_LABEL_BEGIN( "MPB_DS_RX_RES_BEF_CAL_",Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);
		DS.rxRegs.SliceID(0).Broadcast(1);
		DS.rxRegs.setrxtermfloating(0).Write2DUT(32);
		d2s::d2s_LABEL_END();

//		WAIT_TIME(1 ms);
//		Sleep(0.001);
		//=============================================
		// Variables definition and initialization
		//=============================================

		vRxPosMeasVoltage1.init(0);
		vRxNegMeasVoltage1.init(0);

		vRxPosMeasVoltage2.init(0);
		vRxNegMeasVoltage2.init(0);
		vRxSigPosMeasRes.init(0);
		vRxSigNegMeasRes.init(0);

		double data1[48] = {0};
		double data2[48] = {0};
		double data3[48] = {0};
		double data4[48] = {0};
//		double resource[48] ={ 0 };


//		api->Execute_test("H30LR_RxSigResBefCal_FIMV_5mA");
		PinArrayDouble H30LR_RxSigResBefCal_FIMV_5mA_result = H30LR_RxSigResBefCal_FIMV_5mA();
		if(PrintDebugEn)  H30LR_RxSigResBefCal_FIMV_5mA_result.ShowPinArrayData();
//		api->Execute_test("H30LR_RxSigResBefCal_FIMV_1mA");
		PinArrayDouble H30LR_RxSigResBefCal_FIMV_1mA_result = H30LR_RxSigResBefCal_FIMV_1mA();
		if(PrintDebugEn)  H30LR_RxSigResBefCal_FIMV_1mA_result.ShowPinArrayData();
//		Sleep(3000);
//                double mCurrentSource1_mA = mCurrentSource1_mA;
//                double mCurrentSource2_mA = mCurrentSource2_mA;

//		data1 = resource;		/////初始化指针
//		data2 = resource;		/////初始化指针
//		data3 = resource;		/////初始化指针
//		data4 = resource;		/////初始化指针

		vector<string> PinList_P = {"RX_SDS0_P","RX_SDS1_P","RX_SDS2_P","RX_SDS3_P"};
		vector<string> PinList_N = {"RX_SDS0_N","RX_SDS1_N","RX_SDS2_N","RX_SDS3_N"};


//		if(PrintDebugEn) cout<<"PinList_P.size() = "<<PinList_P.size()<<endl;
//
//		if(PrintDebugEn) cout<<"mCurrentSource1_mA= "<<mCurrentSource1_mA<<endl;
//		if(PrintDebugEn) cout<<"mCurrentSource2_mA=  "<<mCurrentSource2_mA<<endl;


		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

		for(int signalIndx = 0 ;signalIndx <PinList_P.size();signalIndx++)
		{
			data1[signalIndx]= H30LR_RxSigResBefCal_FIMV_5mA_result.GetData(PinList_P[signalIndx],SiteID)* 1000;
			data2[signalIndx]= H30LR_RxSigResBefCal_FIMV_5mA_result.GetData(PinList_N[signalIndx],SiteID)* 1000;
			data3[signalIndx]= H30LR_RxSigResBefCal_FIMV_1mA_result.GetData(PinList_P[signalIndx],SiteID)* 1000;
			data4[signalIndx]= H30LR_RxSigResBefCal_FIMV_1mA_result.GetData(PinList_N[signalIndx],SiteID)* 1000;

//			if(PrintDebugEn) cout<<"5mA P "<<"data1["<<PinList_P[signalIndx]<<"]="<< data1[signalIndx]<<endl;
//			if(PrintDebugEn) cout<<" 5mA N "<<"data2["<<PinList_N[signalIndx]<<"]="<< data2[signalIndx]<<endl;
//			if(PrintDebugEn) cout<<" 1mA P "<<"data3["<<PinList_P[signalIndx]<<"]="<< data3[signalIndx]<<endl;
//			if(PrintDebugEn) cout<<" 1mA N "<<"data4["<<PinList_N[signalIndx]<<"]="<< data4[signalIndx]<<endl;
		}
		FOREACH_ACTIVESITE_END



//		FOREACH_ACTIVE_SITE(api)
//		{
//			unsigned int SiteID = api->Get_active_site();
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)


//			api->Get_dctest_values("H30LR_RxSigResBefCal_MForce_I_5mA_group","gSDS_H30LR_RX_P", 0, THE_MEASURE, &data1, THE_END); //modify by tony 20210525 add "_group"
//
//			api->Get_dctest_values("H30LR_RxSigResBefCal_MForce_I_5mA_group","gSDS_H30LR_RX_N", 0, THE_MEASURE, &data2, THE_END);
//
//			api->Get_dctest_values("H30LR_RxSigResBefCal_MForce_I_1mA_group","gSDS_H30LR_RX_P", 0, THE_MEASURE, &data3, THE_END);
//
//			api->Get_dctest_values("H30LR_RxSigResBefCal_MForce_I_1mA_group","gSDS_H30LR_RX_N", 0, THE_MEASURE, &data4, THE_END);

			int iSginal;
			iSginal = 0;
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size();
					macroIndex++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++)
				{
					UINT LaneID = vLane[laneIndex];
//                                        const char * RxPos_Pin = LANE_INFO[MacroID][LaneID].RX_P.c_str();
//                                        const char * RxNeg_Pin = LANE_INFO[MacroID][LaneID].RX_P.c_str();
//                                        api->Get_dctest_values("H30LR_RxSigResBefCal_MForce_I_5mA", RxPos_Pin, 0, THE_MEASURE, &data1, THE_END);
//                                        api->Get_dctest_values("H30LR_RxSigResBefCal_MForce_I_5mA", RxNeg_Pin, 0, THE_MEASURE, &data2, THE_END);
//                                        api->Get_dctest_values("H30LR_RxSigResBefCal_MForce_I_1mA", RxPos_Pin, 0, THE_MEASURE, &data3, THE_END);
//                                        api->Get_dctest_values("H30LR_RxSigResBefCal_MForce_I_1mA", RxNeg_Pin, 0, THE_MEASURE, &data4, THE_END);

					vRxPosMeasVoltage1[SiteID][MacroID][LaneID] = data1[iSginal]; //mV


					vRxNegMeasVoltage1[SiteID][MacroID][LaneID] = data2[iSginal]; //mV


					vRxPosMeasVoltage2[SiteID][MacroID][LaneID] = data3[iSginal];  //mV


					vRxNegMeasVoltage2[SiteID][MacroID][LaneID] = data4[iSginal]; //mV

					iSginal = iSginal + 1;

					//calculate Res
					vRxSigPosMeasRes[SiteID][MacroID][LaneID] =
							(vRxPosMeasVoltage1[SiteID][MacroID][LaneID]
									- vRxPosMeasVoltage2[SiteID][MacroID][LaneID])
									/ (mCurrentSource1_mA
											- mCurrentSource2_mA);
					vRxSigNegMeasRes[SiteID][MacroID][LaneID] =
							(vRxNegMeasVoltage1[SiteID][MacroID][LaneID]
									- vRxNegMeasVoltage2[SiteID][MacroID][LaneID])
									/ (mCurrentSource1_mA
											- mCurrentSource2_mA);
				}
			}
			FOREACH_ACTIVESITE_END
		//=============================================
		// Datalog
		//=============================================
		double LimitL = 50;// 6221 low  spec = 50
		double LimitH = 74;// 6221 high spec = 95
		HiLink_PerLane_Judge(MacroLane_Sel, "H30_RxSigRes_P", LimitL,
				vRxSigPosMeasRes, LimitH, PIN_RXP);

		HiLink_PerLane_Judge(MacroLane_Sel, "H30_RxSigRes_N", LimitL,
				vRxSigNegMeasRes, LimitH, PIN_RXN);

		SetTestBin();

	}

};
REGISTER_TESTCLASS("RxSigResBefCal_IFVM", RxSigResBefCal_IFVM)

