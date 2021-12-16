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
class AnalogLos_Detection_Common_Gonogo_ABIST: public TestClass {
public:
	STRING 				mHiLink16_MacroList;
	STRING 				mPinList;
	STRING				mLoopbackMode;
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
		add_param("Loopback_Mode","string",&mLoopbackMode)
					 //.set_options("Bump:PreDriver:External")
					 .set_default("Bump");
		add_param("PrintLvl[0~15]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 10000(16)"
							     "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYE_PLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.set_options("0:1:3:4:7:9")
					 .set_default("3");
	}
	void execute()
			{
		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
		static	STRING          	sTestsuiteName;
		static	INT					iOffline;
		static  MACRO_LANE_SEL 		MacroLane_Sel;


		static LANE_DOUBLE			TxFir_Main_High_IsNoAlos;
		static LANE_DOUBLE			TxFir_Main_Low_IsAlos;


			//=============================================
			// Variables and MacroLane initialization
			//=============================================
			iOffline = 0;
			sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
			hout.setLevel(iPrintLvl);
			hout.printsuitename(sTestsuiteName);
			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

			/********* common mode ***********/
			TxFIR_SETTING 		FIR_ORI, FIR;
			GetTxFIR(FIR_ORI);
			INT					iTxMainStart = 24;
			INT					iTxMainStop = 0;
//			INT					iTxMainStep = 3;

			//=============================================
			// Device Setup
			//=============================================
			d2s_JTAG& jtag = d2s_JTAG::Instance();

			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_ANALOG_LOS_DET_COMMON_ABIST_SETUP",Global_D2S_Mode);

				DS.rxRegs.addSkipCheckCSR(31);
				DS.rxRegs.addSkipCheckCSR(40);

				selectMacro_MB(MacroLane_Sel);
				DS.Broadcast();

				if (mLoopbackMode == "External" ) {
					DisableTxToRxSerLpbk();
				} else {
					EnableTxToRxSerLpbk(mLoopbackMode);
				}

				SetpmaMode();
				/**add sigdet_manual & sigdet_thrs_sel_man setup while PUG does not have**/

				SetsigdetMode();

				EnableTxPrbsGen(PRBS15);

			d2s::d2s_LABEL_END();

			//=============================================
			//measurement
			//=============================================
			const INT 			ReadCnt = 10;




			/********************* ALOS COMMON GONOGO HIGH *********************/
			FIR.iTxMain = iTxMainStart;
			FIR.iTxPost1st = 0;
			FIR.iTxPost2nd = 0;
			FIR.iTxPre1st = 0;
			FIR.iTxPre2nd = 0;

			hout(DETAIL) << "The current TxFIR Main = " << FIR.iTxMain << endl;
			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_RXALOS_ABIST_HIGH", Global_D2S_Mode);

				selectMacro_MB(MacroLane_Sel);
				DS.Broadcast();

				SetTxFir(FIR);
				jtag.wait(40 *0.000001);

			d2s::d2s_LABEL_END();

			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_ANALOG_LOS_COMMON_CheckHIGH",Global_D2S_Mode);

				jtag.enablePassFailCheckForNextExecution();

				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					selectMacro(MacroID);

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
						for(INT ReadIdx = 0; ReadIdx < ReadCnt; ReadIdx ++)
						{
							DS.rxRegs.ExpectValue(61, 0, 0x7fff);
						}
					}
				}

			d2s::d2s_LABEL_END();

			TxFir_Main_High_IsNoAlos.init(0);
//			if (jtag.hasAllSitesPassed("H16LRTV100_MPB_ANALOG_LOS_COMMON_CheckHIGH")) {
			if (hasAllSitesPassed()) {
				TxFir_Main_High_IsNoAlos.init(1);
				hout(DETAIL) << "indicate No LOS on HIGH!" << endl;
			} else {
				hout(DETAIL) << "ALOS is unstable on HIGH!" << endl;
			}


			/********************* ALOS COMMON GONOGO LOW *********************/
			FIR.iTxMain = iTxMainStop;
			FIR.iTxPost1st = 0;
			FIR.iTxPost2nd = 0;
			FIR.iTxPre1st = 0;
			FIR.iTxPre2nd = 0;

			hout(DETAIL) << "The current TxFIR Main = " << FIR.iTxMain << endl;
			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_RXALOS_ABIST_LOW", Global_D2S_Mode);

				selectMacro_MB(MacroLane_Sel);
				DS.Broadcast();

				SetTxFir(FIR);
				jtag.wait(40 *0.000001);

			d2s::d2s_LABEL_END();

			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_ANALOG_LOS_COMMON_CheckLOW",Global_D2S_Mode);

				jtag.enablePassFailCheckForNextExecution();

				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					selectMacro(MacroID);

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
						for(INT ReadIdx = 0; ReadIdx < ReadCnt; ReadIdx ++)
						{
							DS.rxRegs.ExpectValue(61, 1<<15, 0x7fff);
						}
					}
				}

			d2s::d2s_LABEL_END();

			TxFir_Main_Low_IsAlos.init(0);
//			if (jtag.hasAllSitesPassed("H16LRTV100_MPB_ANALOG_LOS_COMMON_CheckLOW")) {
			if (hasAllSitesPassed()) {
				TxFir_Main_Low_IsAlos.init(1);
				hout(DETAIL) << "indicate LOS on LOW!" << endl;
			} else {
				hout(DETAIL) << "ALOS is unstable on LOW!" << endl;
			}


			//=============================================
			//restore
			//=============================================
			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_RXALOS_ABIST_RESTORE", Global_D2S_Mode);

				selectMacro_MB(MacroLane_Sel);
				DS.Broadcast();

				SetTxFir(FIR_ORI);
				jtag.wait(40 *0.000001);

			d2s::d2s_LABEL_END();

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						if (iOffline) {
							TxFir_Main_High_IsNoAlos[SiteID][MacroID][LaneID] = 1;
							TxFir_Main_Low_IsAlos[SiteID][MacroID][LaneID] = 1;
						}
					}
				}
			FOREACH_ACTIVESITE_END

		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "High_IsNoAlos", TxFir_Main_High_IsNoAlos);
//		HiLink_PerLane_Judge(MacroLane_Sel, "Low_IsAlos", TxFir_Main_Low_IsAlos);

		return;
			}

};
REGISTER_TESTCLASS("AnalogLos_Detection_Common_Gonogo_ABIST", AnalogLos_Detection_Common_Gonogo_ABIST);
