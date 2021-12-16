
#include <Common_Func/HiLink30_Common_Func.h>
#include <HILINK_DC/Execute_functions.h>



void TxVoltMeas(const MACRO_LANE_SEL MacroLane_Sel, double miForce,
		LANE_DOUBLE &vTxPosMeasVoltage, LANE_DOUBLE &vTxNegMeasVoltage,
		LANE_DOUBLE &vTxDiffMeasVoltage, LANE_DOUBLE &vTxCommMeasVoltage)
{
	STRING mPinList;
	STRING mPinList_P;
	STRING mPinList_N;

	get_pinlists(MacroLane_Sel, mPinList_P, mPinList_N, mPinList, "TX");

	vTxPosMeasVoltage.init(0);
	vTxNegMeasVoltage.init(0);
	vTxDiffMeasVoltage.init(0);
	vTxCommMeasVoltage.init(0);

	double data1[48] =	{ 0 };
	double data2[48] =	{ 0 };
//	double resource[48] =	{ 0 };

	double VRX_N_0mA;
	double VRX_P_0mA;
//                api->Execute_test("H30LR_Rx_setupN");
//	api->Execute_test("H30LR_TxTermVolt_MForce_I_0mA");
	PinArrayDouble H30LR_TxTermVolt_MForce_I_0mA_result  = H30LR_TxTermVolt_MForce_I_0mA();
//	Sleep(0.03);
	if(PrintDebugEn)  H30LR_TxTermVolt_MForce_I_0mA_result.ShowPinArrayData();
//	data1 = resource; /////初始化指针
//	data2 = resource; /////初始化指针

		vector<string> PinList_P = {"TX_SDS0_P","TX_SDS1_P","TX_SDS2_P","TX_SDS3_P"};
		vector<string> PinList_N = {"TX_SDS0_N","TX_SDS1_N","TX_SDS2_N","TX_SDS3_N"};

		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

		for(int signalIndx = 0 ;signalIndx <PinList_P.size();signalIndx++)
		{
			data1[signalIndx]= H30LR_TxTermVolt_MForce_I_0mA_result.GetData(PinList_P[signalIndx],SiteID);
		}
		for(int signalIndx = 0 ;signalIndx <PinList_N.size();signalIndx++)
		{
			data2[signalIndx]= H30LR_TxTermVolt_MForce_I_0mA_result.GetData(PinList_N[signalIndx],SiteID);
			//cout<<PinList_N[signalIndx]<<" data2[signalIndx]="<<data2[signalIndx]<<endl;
		}
		FOREACH_ACTIVESITE_END

		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

//		api->Get_dctest_values("H30LR_TxTermVolt_MForce_I_0mA_group","gSDS_H30LR_TX_P", 0, THE_MEASURE, &data1, THE_END); //modify by tony 20210525 add "_group"
//		api->Get_dctest_values("H30LR_TxTermVolt_MForce_I_0mA_group","gSDS_H30LR_TX_N", 0, THE_MEASURE, &data2, THE_END);

		////tony add note:
		//// 	result Pins sequence= "RX_SDS0_N,RX_SDS1_N,RX_SDS2_N,RX_SDS3_N,RX_SDS0_P,RX_SDS1_P,RX_SDS2_P,RX_SDS3_P";

//		H30LR_TxTermVolt_MForce_I_0mA_result.GetData();

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

				vTxPosMeasVoltage[SiteID][MacroID][LaneID] = data1[iSginal]* 1000; //mV     H30LR_TxTermVolt_MForce_I_0mA_result.GetData(pinName,SiteID);


				vTxNegMeasVoltage[SiteID][MacroID][LaneID] = data2[iSginal]* 1000; //mV


				iSginal = iSginal + 1;

				vTxDiffMeasVoltage[SiteID][MacroID][LaneID] =
						(vTxPosMeasVoltage[SiteID][MacroID][LaneID]
								- vTxNegMeasVoltage[SiteID][MacroID][LaneID]);
				vTxCommMeasVoltage[SiteID][MacroID][LaneID] =
						(vTxPosMeasVoltage[SiteID][MacroID][LaneID]
								+ vTxNegMeasVoltage[SiteID][MacroID][LaneID])
								/ 2.0;

				hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_P
						<< " Voltage = "
						<< vTxPosMeasVoltage[SiteID][MacroID][LaneID] << " mV"
						<< endl;
				hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_N
						<< " Voltage = "
						<< vTxNegMeasVoltage[SiteID][MacroID][LaneID] << " mV"
						<< endl;
//				cout << "Pin " << LANE_INFO[MacroID][LaneID].TX_P
//						<< " Voltage = "
//						<< vTxPosMeasVoltage[SiteID][MacroID][LaneID] << " mV"
//						<< endl;
//				cout << "Pin " << LANE_INFO[MacroID][LaneID].TX_N
//						<< " Voltage = "
//						<< vTxNegMeasVoltage[SiteID][MacroID][LaneID] << " mV"
//						<< endl;
			}
		}
		FOREACH_ACTIVESITE_END
}


class TxTermVolt: public TestClass{
public:

	STRING 				mHiLink30_MacroList;
	STRING 				mPinList;
	STRING 				mPinList_P;
	STRING 				mPinList_N;
	STRING 				mPattern;
	DOUBLE              miForce;
    INT                 iPolarity;
    STRING              mLoopBackMode;
	INT					iPrintLvl;
	void init()
	{
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					 .set_comment("HiLink30 Macro List for test")
					 //.setOptions("0,1:FromPinList")
					 .set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
		add_param("LoopBackMode","string",&mLoopBackMode)
					//.setOptions("PreDriver:Bump:External:Nothing")
					.set_default("External");
		add_param("Pattern","string",&mPattern)
					 //.setOptions("ALL0:ALL1")
		             .set_default("ALL0");
		add_param("Polarity","int",&iPolarity)
					 //.setOptions("0:1")
					 .set_default("0");
		add_param("ForceCurr","double",&miForce)
					 .set_default("-0.1");
		add_param("PrintLvl[0~8]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
					 "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.setOptions("0:1:3:4:7:8")
					 .set_default("3");
	}
	void execute()//ClkPurity_ABIST_
	{
		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
		H30_FailBin_Flag.init(0);
//		STRING mPinList;
//		STRING mPinList_P;
//		STRING mPinList_N;
		INT iDebugAnalog;
		//		static	STRING          	sTestsuiteName;
		static MACRO_LANE_SEL MacroLane_Sel;

		static LANE_DOUBLE vTxPosMeasVoltage;
		static LANE_DOUBLE vTxNegMeasVoltage;
		static LANE_DOUBLE vTxDiffMeasVoltage;
		static LANE_DOUBLE vTxCommMeasVoltage;
		static bool CSRVerifyResult;

		//		ON_FIRST_INVOCATION_BEGIN();
		//
		//		GET_TESTSUITE_NAME	(sTestsuiteName);
		//		GET_TESTFLOW_FLAG	("debug_analog",&iDebugAnalog);
		stTxTermVolt TxTermVolt;		//=SSbandGap_SSBandGap;

		//                const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
		//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

		if (strTestsuiteName == "H30_TxTermVolt_All0_VDDN")		////PLL0_1G  1
		{
			TxTermVolt = H30_TxTermVolt_All0_VDDN_TxTermVolt;
		}
		else if (strTestsuiteName == "H30_TxTermVolt_All1_VDDN")
		{
			TxTermVolt = H30_TxTermVolt_All1_VDDN_TxTermVolt;

		}

		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);

		Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList,mPinList);

		//=============================================
		// Variables definition and initialization
		//=============================================
		CUSTPARA Custpara;		//shaoxue 20170216
		Custpara.TxFIR_USER.iTxMain = 63;
		Custpara.TxFIR_USER.iTxPost1st = 0;
		Custpara.TxFIR_USER.iTxPost2nd = 0;
		Custpara.TxFIR_USER.iTxPre1st = 0;
		Custpara.TxFIR_USER.iTxPre2nd = 0;
		//=============================================
		// Device Setup
		//=============================================
		//		D2S_FRAMEWORK;
		//		GET_TEST_INFO;

		LoopBack_Setting(mLoopBackMode, MacroLane_Sel, Custpara);
		//		sprintf(label,"MPB_TXTERM_VOLT_SETUP_%f_%f_",Vcoef,Temp);
		//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN("MPB_TXTERM_VOLT_SETUP_", Global_D2S_Mode);
		selectMacro_MB(MacroLane_Sel);
		SetTxFir(Custpara); //add by shaoxue 20170216

		DS.rxRegs.SliceID(0).Broadcast(1);
		DS.txRegs.SliceID(0).Broadcast(1);

		if (mPattern == "ALL0")
			EnableTxPrbsGen("CUSTOMER_PATTERN", 0x0000);
		else if (mPattern == "ALL1")
			EnableTxPrbsGen("CUSTOMER_PATTERN", 0xFFFF);

		DS.txRegs.settxpolarity(iPolarity).Write2DUT(2);
		//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();

		//=============================================
		// Measurement
		//=============================================
		vTxPosMeasVoltage.init(0);
		vTxNegMeasVoltage.init(0);
		vTxDiffMeasVoltage.init(0);
		vTxCommMeasVoltage.init(0);

		TxVoltMeas(MacroLane_Sel, miForce, vTxPosMeasVoltage,vTxNegMeasVoltage, vTxDiffMeasVoltage, vTxCommMeasVoltage);


		//		ON_FIRST_INVOCATION_END();
		//=============================================
		// Datalog
		//=============================================
		double LimitL_P = -20;
		double LimitH_P = 20;

		double LimitL_N = 760;
		double LimitH_N = 1160;

		if (strTestsuiteName == "H30_TxTermVolt_All0_VDDN")		////PLL0_1G  1
		{
			HiLink_PerLane_Judge(MacroLane_Sel, "H30_TxTermVolt_All0_VDDN_POS",
					LimitL_P, vTxPosMeasVoltage, LimitH_P, PIN_TXP);
			HiLink_PerLane_Judge(MacroLane_Sel, "H30_TxTermVolt_All0_VDDN_NEG",
					LimitL_N, vTxNegMeasVoltage, LimitH_N, PIN_TXN);
		}
		else if (strTestsuiteName == "H30_TxTermVolt_All1_VDDN")
		{
			HiLink_PerLane_Judge(MacroLane_Sel, "H30_TxTermVolt_All1_VDDN_POS",
					LimitL_N, vTxPosMeasVoltage, LimitH_N, PIN_TXP);
			HiLink_PerLane_Judge(MacroLane_Sel, "H30_TxTermVolt_All1_VDDN_NEG",
					LimitL_P, vTxNegMeasVoltage, LimitH_P, PIN_TXN);

		}
	}

};

REGISTER_TESTCLASS("TxTermVolt", TxTermVolt)


