//for test method API interfaces

#include <Common_Func/HiLink30_Common_Func.h>
#include <HILINK_DC/Execute_functions.h>
using namespace std;

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
class TxResAftCal: public TestClass
{
public:

	STRING 				mHiLink30_MacroList;
	STRING 				mPinList;
	DOUBLE 				mCurrent1_mA;
	DOUBLE 				mCurrent2_mA;
	STRING 				mPinList_P;
	STRING 				mPinList_N;
	STRING              sPatternType;
	INT					iPrintLvl;
	void init()
	{
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					 .set_comment("HiLink30 Macro List for test")
					 //.setOptions("0,1:0:1:FromPinList")
					 .set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
		add_param("PatternType","string",&sPatternType)
					 .set_default("ALL0")
					 //.setOptions("ALL0:ALL1:CheckBoard")
					 .set_comment("second sink current");
		add_param("current1_mA","double",&mCurrent1_mA)
					 .set_default("2e-3")
					 .set_comment("first sink current");
		add_param("current2_mA","double",&mCurrent2_mA)
					 .set_default("3e-3")
					 .set_comment("second sink current");
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
//		STRING mHiLink30_MacroList;
//		DOUBLE mCurrent1_mA;
//		DOUBLE mCurrent2_mA;
//		STRING mPinList_P;
//		STRING mPinList_N;

		static INT iOffline;
		static MACRO_LANE_SEL MacroLane_Sel;
		static INT iDebugAnalog;

		static LANE_DOUBLE vTxPosMeasVoltage1;
		static LANE_DOUBLE vTxNegMeasVoltage1;
		static LANE_DOUBLE vTxPosMeasVoltage2;
		static LANE_DOUBLE vTxNegMeasVoltage2;
		static LANE_DOUBLE vTxPosMeasRes;
		static LANE_DOUBLE vTxNegMeasRes;
		static bool CSRVerifyResult;

		stTxResAftCal TxResAftCal;

//		static STRING mPinList = "";
//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

		if (strTestsuiteName == "H30_TxSigResAftCal_All0_VDDN")	////PLL0_1G  1
		{
			TxResAftCal = H30_TxSigResAftCal_All0_VDDN_TxResAftCal;
		}
		else if (strTestsuiteName == "H30_TxSigResAftCal_All1_VDDN")
		{
			TxResAftCal = H30_TxSigResAftCal_All1_VDDN_TxResAftCal;

		}

		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		//=============================================
		// Variables definition and initialization
		//=============================================

		Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList,mPinList);
		get_pinlists(MacroLane_Sel, mPinList_P, mPinList_N, mPinList, "TX");

		hout(DETAIL) << "Pinlist : " << mPinList << endl;
		hout(DETAIL) << "PosPin : " << mPinList_P << endl;
		hout(DETAIL) << "NegPin : " << mPinList_N << endl;

		//=============================================
		// Device Setup
		//=============================================

		d2s::d2s_LABEL_BEGIN("MPB_DS_TX_RES_AFT_CAL_",
				Global_D2S_Mode);
		selectMacro_MB(MacroLane_Sel);
		DS.rxRegs.SliceID(0).Broadcast(1);
		DS.txRegs.SliceID(0).Broadcast(1);

		CUSTPARA CUSTpara;
		CUSTpara.TxFIR_USER.iTxMain = 63;
		CUSTpara.TxFIR_USER.iTxPre1st = 0;
		CUSTpara.TxFIR_USER.iTxPre2nd = 0;
		CUSTpara.TxFIR_USER.iTxPost1st = 0;
		CUSTpara.TxFIR_USER.iTxPost2nd = 0;
		SetTxFir(CUSTpara);

		if (sPatternType == "ALL0")
		{
			EnableTxPrbsGen("CUSTOMER_PATTERN", 0x0000);
		}
		else if (sPatternType == "ALL1")
		{
			EnableTxPrbsGen("CUSTOMER_PATTERN", 0xFFFF);
		}
		else
		{
//				cout << "ERROR: Only support ALL0 and ALL1 mode!!!" << endl;
			cout <<"ERROR: Only support ALL0 and ALL1 mode!!!"<<endl;
//			api->info_message("ERROR: Only support ALL0 and ALL1 mode!!!");
//				ERROR_EXIT(TM::ABORT_FLOW);
		}
		d2s::d2s_LABEL_END();

		//=============================================
		// Measurement
		//=============================================

		vTxPosMeasVoltage1.init(0);
		vTxNegMeasVoltage1.init(0);
		vTxPosMeasVoltage2.init(0);
		vTxNegMeasVoltage2.init(0);
		vTxPosMeasRes.init(0);
		vTxNegMeasRes.init(0);

		double data1[48]= {0};
		double data2[48]= {0};
		double data3[48]= {0};
		double data4[48]= {0};
//		*data2, *data3, *data4;
//		double resource[48] =
//		{ 0 };
//
//		data1 = resource;		/////初始化指针
//		data2 = resource;		/////初始化指针
//		data3 = resource;		/////初始化指针
//		data4 = resource;		/////初始化指针

//		api->Execute_test("H30LR_TxResAftCal_FIMV_3mA");
		PinArrayDouble H30LR_TxResAftCal_FIMV_3mA_result = H30LR_TxResAftCal_FIMV_3mA();
//		Sleep(0.003);
		if(PrintDebugEn)  H30LR_TxResAftCal_FIMV_3mA_result.ShowPinArrayData();
//		api->Execute_test("H30LR_TxResAftCal_FIMV_4mA");
		PinArrayDouble H30LR_TxResAftCal_FIMV_4mA_result = H30LR_TxResAftCal_FIMV_4mA();
//		Sleep(0.003);
		if(PrintDebugEn)  H30LR_TxResAftCal_FIMV_4mA_result.ShowPinArrayData();

		vector<string> PinList_P = {"TX_SDS0_P","TX_SDS1_P","TX_SDS2_P","TX_SDS3_P"};
		vector<string> PinList_N = {"TX_SDS0_N","TX_SDS1_N","TX_SDS2_N","TX_SDS3_N"};

		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

		for(int signalIndx = 0 ;signalIndx <PinList_P.size();signalIndx++)
		{
			data1[signalIndx]= H30LR_TxResAftCal_FIMV_3mA_result.GetData(PinList_P[signalIndx],SiteID);
			data2[signalIndx]= H30LR_TxResAftCal_FIMV_3mA_result.GetData(PinList_N[signalIndx],SiteID);
			data3[signalIndx]= H30LR_TxResAftCal_FIMV_4mA_result.GetData(PinList_P[signalIndx],SiteID);
			data4[signalIndx]= H30LR_TxResAftCal_FIMV_4mA_result.GetData(PinList_N[signalIndx],SiteID);
		}
		FOREACH_ACTIVESITE_END


//		FOREACH_ACTIVE_SITE(api)
//		{
//			unsigned int SiteID = api->Get_active_site();
			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

//			api->Get_dctest_values("H30LR_TxSigResAftCalMForce_I_3mA_TX_group",
//					"gSDS_H30LR_TX_P", 0, THE_MEASURE, &data1, THE_END);//modify by tony 20210525 add "_group"
//			api->Get_dctest_values("H30LR_TxSigResAftCalMForce_I_3mA_TX_group",
//					"gSDS_H30LR_TX_N", 0, THE_MEASURE, &data2, THE_END);
//			api->Get_dctest_values("H30LR_TxSigResAftCalMForce_I_4mA_TX_group",
//					"gSDS_H30LR_TX_P", 0, THE_MEASURE, &data3, THE_END);
//			api->Get_dctest_values("H30LR_TxSigResAftCalMForce_I_4mA_TX_group",
//					"gSDS_H30LR_TX_N", 0, THE_MEASURE, &data4, THE_END);
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
					vTxPosMeasVoltage1[SiteID][MacroID][LaneID] =
							data1[iSginal];

					vTxNegMeasVoltage1[SiteID][MacroID][LaneID] =
							data2[iSginal];

					vTxPosMeasVoltage2[SiteID][MacroID][LaneID] =
							data3[iSginal];

					vTxNegMeasVoltage2[SiteID][MacroID][LaneID] =
							data4[iSginal];

					iSginal = iSginal + 1;

					vTxPosMeasRes[SiteID][MacroID][LaneID] =
							(vTxPosMeasVoltage2[SiteID][MacroID][LaneID]
									- vTxPosMeasVoltage1[SiteID][MacroID][LaneID])
									/ (mCurrent2_mA
											- mCurrent1_mA) * 1000;
					vTxNegMeasRes[SiteID][MacroID][LaneID] =
							(vTxNegMeasVoltage2[SiteID][MacroID][LaneID]
									- vTxNegMeasVoltage1[SiteID][MacroID][LaneID])
									/ (mCurrent2_mA
											- mCurrent1_mA) * 1000;

					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_P
							<< " Force " << -mCurrent1_mA << " [mA] = "
							<< vTxPosMeasVoltage1[SiteID][MacroID][LaneID]
							<< " mV" << endl;
					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_N
							<< " Force " << -mCurrent1_mA << " [mA] = "
							<< vTxNegMeasVoltage1[SiteID][MacroID][LaneID]
							<< " mV" << endl;

					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_P
							<< " Force " << -mCurrent2_mA << " [mA] = "
							<< vTxPosMeasVoltage2[SiteID][MacroID][LaneID]
							<< " mV" << endl;
					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_N
							<< " Force " << -mCurrent2_mA << " [mA] = "
							<< vTxNegMeasVoltage2[SiteID][MacroID][LaneID]
							<< " mV" << endl;
					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_P
							<< " Result = "
							<< vTxPosMeasRes[SiteID][MacroID][LaneID] << " Ohm"
							<< endl;
					hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_N
							<< " Result = "
							<< vTxNegMeasRes[SiteID][MacroID][LaneID] << " Ohm"
							<< endl;



//					cout << "Pin " << LANE_INFO[MacroID][LaneID].TX_P
//							<< " Force " << -mCurrent1_mA << " [mA] = "
//							<< vTxPosMeasVoltage1[SiteID][MacroID][LaneID]
//							<< " mV" << endl;
//					cout << "Pin " << LANE_INFO[MacroID][LaneID].TX_N
//							<< " Force " << -mCurrent1_mA << " [mA] = "
//							<< vTxNegMeasVoltage1[SiteID][MacroID][LaneID]
//							<< " mV" << endl;
//
//					cout << "Pin " << LANE_INFO[MacroID][LaneID].TX_P
//							<< " Force " << -mCurrent2_mA << " [mA] = "
//							<< vTxPosMeasVoltage2[SiteID][MacroID][LaneID]
//							<< " mV" << endl;
//					cout << "Pin " << LANE_INFO[MacroID][LaneID].TX_N
//							<< " Force " << -mCurrent2_mA << " [mA] = "
//							<< vTxNegMeasVoltage2[SiteID][MacroID][LaneID]
//							<< " mV" << endl;
//					cout << "Pin " << LANE_INFO[MacroID][LaneID].TX_P
//							<< " Result = "
//							<< vTxPosMeasRes[SiteID][MacroID][LaneID] << " Ohm"
//							<< endl;
//					cout << "Pin " << LANE_INFO[MacroID][LaneID].TX_N
//							<< " Result = "
//							<< vTxNegMeasRes[SiteID][MacroID][LaneID] << " Ohm"
//							<< endl;
				}
			}
			FOREACH_ACTIVESITE_END

		//=============================================
		// Datalog
		//=============================================

		double LimitL = 35;
		double LimitH = 55;
		HiLink_PerLane_Judge(MacroLane_Sel, "TxSigResAftCal_P", LimitL,
				vTxPosMeasRes, LimitH, PIN_TXP);
		HiLink_PerLane_Judge(MacroLane_Sel, "TxSigResAftCal_N", LimitL,
				vTxNegMeasRes, LimitH, PIN_TXN);

		SetTestBin();
	}

};

REGISTER_TESTCLASS("TxResAftCal", TxResAftCal)

