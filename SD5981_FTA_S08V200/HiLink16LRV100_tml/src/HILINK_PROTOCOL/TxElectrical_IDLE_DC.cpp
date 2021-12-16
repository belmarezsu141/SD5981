
//for test method API interfaces
//#include "mapi.hpp"
//using namespace std;
//using namespace V93kLimits;

#include <HILINK_PUG/HiLink16_PUG.h>

/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class TxElectrical_IDLE_DC: public TestClass {
public:
	STRING 				mHiLink16_MacroList;
	STRING 				mPinList;
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
		add_param("PrintLvl[0~15]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 10000(16)"
							     "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYE_PLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.set_options("0:1:3:4:7:9")
					 .set_default("3");
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
	void execute()
	{
		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
		static	STRING          	sTestsuiteName;
		static	INT					iOffline;
		static  MACRO_LANE_SEL 		MacroLane_Sel;

		static	LANE_DOUBLE 		TxDiffMeasVoltageIDLE;
		static	LANE_DOUBLE 		TxCommdiff;


		//=============================================
		// Variables and MacroLane initialization
		//=============================================
		iOffline = 0;
		sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

		GetTxPinList(MacroLane_Sel, sPinList_P, sPinList_N, sPinList);

		//=============================================
		// Device Setup
		//=============================================
		d2s_JTAG& jtag = d2s_JTAG::Instance();

		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PCIE_IDLE_DC_NORM_SETUP",Global_D2S_Mode);

			DS.rxRegs.addSkipCheckCSR(40);

			selectMacro_MB(MacroLane_Sel);
			DS.Broadcast();

			SetpmaMode();

			EnableTxPrbsGen(Custom_ALL1,true);

//			DS.txRegs.settx_idle_hiz_sw_crg(0).Write2DUT(25);
			DS.txRegs.settxdrv_idle_en(0).Write2DUT(33);
			DS.txRegs.settxdrv_idle_bypass(0).Write2DUT(34);

		d2s::d2s_LABEL_END();


		//=============================================
		// Measurement on Normal mode
		//=============================================
		LANE_DOUBLE 					TxPosMeasVoltageNORM;
		LANE_DOUBLE 					TxNegMeasVoltageNORM;
		LANE_DOUBLE 					TxDiffMeasVoltageNORM;
		LANE_DOUBLE 					TxCommMeasVoltageNORM;

		hout(DETAIL) << "============= TxElectrical IDLE DC NORM =============" << endl;

		TxVoltMeasHiz(MacroLane_Sel,TxPosMeasVoltageNORM,TxNegMeasVoltageNORM,TxDiffMeasVoltageNORM,TxCommMeasVoltageNORM);

		//=============================================
		// Setup PCIE IDLE mode
		//=============================================

		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PCIE_IDLE_DC_IDLE_SETUP",Global_D2S_Mode);

			selectMacro_MB(MacroLane_Sel);

			DS.Broadcast();
			//set IP to idle state;
			DS.txRegs.settxdrv_idle_en(1).Write2DUT(33);
			DS.txRegs.settx_rxdet_en(0x1).Write2DUT(34);
//			DS.txRegs.setpcie_sas_rxtx_status_rdy(0x0).Write2DUT(48);
//			DS.txRegs.setpcie_sas_rxtx_status_rdy(0x1).Write2DUT(48);

//			DS.txRegs.settx_idle_hiz_sw_crg(1).Write2DUT(25);
				//enable idle state

		d2s::d2s_LABEL_END();

		//=============================================
		// Measurement on PCIE IDLE mode
		//=============================================
		LANE_DOUBLE 					TxPosMeasVoltageIDLE;
		LANE_DOUBLE 					TxNegMeasVoltageIDLE;
		LANE_DOUBLE 					TxCommMeasVoltageIDLE;

		hout(DETAIL) << "============= TxElectrical IDLE DC IDLE =============" << endl;

		TxVoltMeasHiz(MacroLane_Sel,TxPosMeasVoltageIDLE,TxNegMeasVoltageIDLE,TxDiffMeasVoltageIDLE,TxCommMeasVoltageIDLE);


		TxCommdiff.init(0);

		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
				{
					UINT LaneID = vLane[laneIndex];
					TxCommdiff[SiteID][MacroID][LaneID] = abs(TxCommMeasVoltageNORM[SiteID][MacroID][LaneID] - TxCommMeasVoltageIDLE[SiteID][MacroID][LaneID]);
				}
			}
		FOREACH_ACTIVESITE_END


		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "VdiffIDLE", TxDiffMeasVoltageIDLE, PIN_TXP);
//		HiLink_PerLane_Judge(MacroLane_Sel, "Vcommdiff", TxCommdiff, PIN_TXP);

		return;
	}
	//=================================Hi1213=================
	void TxVoltMeasHiz(const MACRO_LANE_SEL MacroLane_Sel,LANE_DOUBLE &TxPosMeasVoltage,LANE_DOUBLE &TxNegMeasVoltage, LANE_DOUBLE &TxDiffMeasVoltage,LANE_DOUBLE &TxCommMeasVoltage)
	{
		TxPosMeasVoltage.init(0);
		TxNegMeasVoltage.init(0);
		TxDiffMeasVoltage.init(0);
		TxCommMeasVoltage.init(0);

		string Pins = "gHILINK_TxP,gHILINK_TxN";
		double iForce = 0.0 *uA;
		double vExpect = 1.2;
		int sampleSize = 64;
		double waitTime = 3 *ms;
		PinArrayDouble  result = PPMU_FIMV_measure(Pins,iForce,vExpect,waitTime,sampleSize,true);

		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
				{
					UINT LaneID = vLane[laneIndex];
					TxPosMeasVoltage[SiteID][MacroID][LaneID] = result.GetData(LANE_INFO[MacroID][LaneID].TX_P,SiteID) / (1 *mV);
					TxNegMeasVoltage[SiteID][MacroID][LaneID] = result.GetData(LANE_INFO[MacroID][LaneID].TX_N,SiteID) / (1 *mV);

					TxDiffMeasVoltage[SiteID][MacroID][LaneID]  = abs(TxPosMeasVoltage[SiteID][MacroID][LaneID] - TxNegMeasVoltage[SiteID][MacroID][LaneID]);
					TxCommMeasVoltage[SiteID][MacroID][LaneID]  = abs(TxPosMeasVoltage[SiteID][MacroID][LaneID] + TxNegMeasVoltage[SiteID][MacroID][LaneID]) / 2.0;

					cout << "Pin " << LANE_INFO[MacroID][LaneID].TX_P <<  " Voltage = "  << TxPosMeasVoltage[SiteID][MacroID][LaneID] << " mV" << endl;
					cout << "Pin " << LANE_INFO[MacroID][LaneID].TX_N <<  " Voltage = "  << TxNegMeasVoltage[SiteID][MacroID][LaneID] << " mV" << endl;
				}
			}
		FOREACH_ACTIVESITE_END
	}

};
REGISTER_TESTCLASS("TxElectrical_IDLE_DC", TxElectrical_IDLE_DC);
