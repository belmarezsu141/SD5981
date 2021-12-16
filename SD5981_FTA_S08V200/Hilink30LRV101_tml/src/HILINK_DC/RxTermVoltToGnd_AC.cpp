//for test method API interfaces

#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"


using namespace std;



	void RxVoltMeas(const MACRO_LANE_SEL MacroLane_Sel, double iForce_uA, LANE_DOUBLE & vRxPosMeasVoltage, LANE_DOUBLE & vRxNegMeasVoltage)
	{
            
                STRING mPinList;
                STRING mPinList_P;
                STRING mPinList_N;
                
		get_pinlists(MacroLane_Sel,mPinList_P,mPinList_N,mPinList,"RX");

		vRxPosMeasVoltage.init(0);
		vRxNegMeasVoltage.init(0);

                double data1[48] = {0};
                double data2[48] = {0};
//                double resource[48] = {0};
                double VRX_N_0mA;
                double VRX_P_0mA;
//                api->Execute_test("H30LR_RxTermVoltToGnd_AC_FIMV_0mA");
                PinArrayDouble H30LR_RxTermVoltToGnd_AC_FIMV_0mA_result = H30LR_RxTermVoltToGnd_AC_FIMV_0mA();
                if(PrintDebugEn)  H30LR_RxTermVoltToGnd_AC_FIMV_0mA_result.ShowPinArrayData();
//                Sleep(0.003);
//                data1 = resource;/////初始化指针
//                data2 = resource;/////初始化指针

        		vector<string> PinList_P = {"RX_SDS0_P","RX_SDS1_P","RX_SDS2_P","RX_SDS3_P"};
        		vector<string> PinList_N = {"RX_SDS0_N","RX_SDS1_N","RX_SDS2_N","RX_SDS3_N"};

        		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        		for(int signalIndx = 0 ;signalIndx <PinList_P.size();signalIndx++)
        		{
        			data1[signalIndx]= H30LR_RxTermVoltToGnd_AC_FIMV_0mA_result.GetData(PinList_P[signalIndx],SiteID);
        			data2[signalIndx]= H30LR_RxTermVoltToGnd_AC_FIMV_0mA_result.GetData(PinList_N[signalIndx],SiteID);
        		}
        		FOREACH_ACTIVESITE_END

                
//                FOREACH_ACTIVE_SITE(api) {
//                            unsigned int SiteID = api->Get_active_site();
                            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

//                            api->Get_dctest_values("H30LR_RxTermVoltToGnd_AC_MForce_I_0mA_group", "gSDS_H30LR_RX_P", 0, THE_MEASURE, &data1, THE_END);//modify by tony 20210525 add "_group"
//                            api->Get_dctest_values("H30LR_RxTermVoltToGnd_AC_MForce_I_0mA_group", "gSDS_H30LR_RX_N", 0, THE_MEASURE, &data2, THE_END);
                            int iSginal;
                            iSginal = 0;   
                            
                            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
                            {
                                    UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
                                    const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

                                    for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
                                    {
                                            UINT LaneID = vLane[laneIndex];
                                            
                                            vRxPosMeasVoltage[SiteID][MacroID][LaneID] = data1[iSginal]*1000;//mV

                                            vRxNegMeasVoltage[SiteID][MacroID][LaneID] = data2[iSginal]*1000;//mV
                                            iSginal = iSginal + 1;

                                            hout(DETAIL) << "Pin: " << LANE_INFO[MacroID][LaneID].RX_P << ": " << vRxPosMeasVoltage[SiteID][MacroID][LaneID] << " mV" << endl;
                                            hout(DETAIL) << "Pin: " << LANE_INFO[MacroID][LaneID].RX_N << ": " << vRxNegMeasVoltage[SiteID][MacroID][LaneID] << " mV" << endl;

                                    }
                            }
                            FOREACH_ACTIVESITE_END

	}
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

class RxTermVoltToGnd_AC: public TestClass{
public:

	STRING 				mHiLink30_MacroList;
	STRING 				mPinList;
	STRING 				mPinList_P;
	STRING 				mPinList_N;
	STRING              mPattern;
	DOUBLE 				miForce;
	INT  				mRXCAPBYPASS;
	INT					iPrintLvl;

	void init(){
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					 .set_comment("HiLink30 Macro List for test")
					 //.setOptions("0,1:FromPinList")
					 .set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
		add_param("Pattern","string",&mPattern);
					 //.setOptions("ALL0:ALL1");
		add_param("ForceCurr","double",&miForce)
					 .set_default("-0.1");
		add_param("PrintLvl[0~8]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
					 "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.setOptions("0:1:3:4:7:8")
					 .set_default("3");
	}
	void execute(){


		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
                H30_FailBin_Flag.init(0);
		static	INT					iOffline;
		static	INT 				iCSR_check;
		static  MACRO_LANE_SEL 		MacroLane_Sel;
		INT							iDebugAnalog;

		static LANE_DOUBLE 			vRxPosMeasVoltage;
		static LANE_DOUBLE			vRxNegMeasVoltage;
		static bool                 CSRVerifyResult;

//		ON_FIRST_INVOCATION_BEGIN();
//
//		GET_SYSTEM_FLAG		("offline",&iOffline);
//		GET_TESTSUITE_NAME	(sTestsuiteName);
//		GET_TESTFLOW_FLAG	("debug_analog",&iDebugAnalog);
//		GET_USER_FLAG		("CSR_atomic_operation",&iCSR_check);


		//=============================================
		// Device Setup
		//=============================================
//		D2S_FRAMEWORK;
//		GET_TEST_INFO;
                
                stRxTermVoltToGnd_AC& RxTermVoltToGnd_AC=H30_RxTermVoltToGnd_AC_RxTermVoltToGnd_AC; 
                
//                static STRING mPinList="";
//                const char * sTestsuiteName = api->Get_current_test_name();
                string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
                string strTestsuiteName = sTestsuiteName;
//                api->Get_test_values(strTestsuiteName.data(),THE_TESTNUMBER,&m_TestNumber,THE_END);
//        	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
        		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
        		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
        		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

        	    hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel,mHiLink30_MacroList,mPinList);

//		sprintf(label,"MPB_DS_RX_RES_TermVolt_%f_%f_",Vcoef,Temp);
                d2s::d2s_LABEL_BEGIN( "MPB_DS_RX_RES_TermVolt_", Global_D2S_Mode);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
			selectMacro_MB(MacroLane_Sel);
			DS.txRegs.SliceID(0).Broadcast(1);
			DS.rxRegs.SliceID(0).Broadcast(1);
			if(mPattern == "ALL0")
				EnableTxPrbsGen("CUSTOMER_PATTERN",0x0000);
			else if (mPattern == "ALL1")
				EnableTxPrbsGen("CUSTOMER_PATTERN",0xFFFF);
			DS.rxRegs.setrxtermfloating(0).Write2DUT(32);
		d2s::d2s_LABEL_END();

		//=============================================
		// Measurement
		//=============================================
		RxVoltMeas(MacroLane_Sel, miForce, vRxPosMeasVoltage, vRxNegMeasVoltage);

//		ON_FIRST_INVOCATION_END();

		//=============================================
		// Datalog
		//=============================================
                double LimitL=-10;
                double LimitH=10;
                HiLink_PerLane_Judge(MacroLane_Sel, "RxTermVoltToGnd_P", LimitL,vRxPosMeasVoltage,LimitH, PIN_RXP);
                HiLink_PerLane_Judge(MacroLane_Sel, "RxTermVoltToGnd_N", LimitL,vRxNegMeasVoltage,LimitH, PIN_RXN);
                
                SetTestBin();
	}

};

REGISTER_TESTCLASS("RxTermVoltToGnd_AC",RxTermVoltToGnd_AC)


