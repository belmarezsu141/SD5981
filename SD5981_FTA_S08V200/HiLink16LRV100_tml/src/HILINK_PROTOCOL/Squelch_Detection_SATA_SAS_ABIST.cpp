
//for test method API interfaces
//#include "mapi.hpp"
//using namespace std;
#include <HILINK_PUG/HiLink16_PUG.h>

/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class Squelch_Detection_SATA_SAS_ABIST: public TestClass{
public:
	STRING				mHiLink16_MacroList;
	STRING 				mPinList;
	STRING				mLoopbackMode;
	INT					iPrintLvl;





  /**
   *Initialize the parameter interface to the testflow.
   *This method is called just once after a testsuite is created.
   */
	void init()
  {
		//Add your initialization code here
		//Note: Test Method API should not be used in this method!
		add_param("H16LR_MacroList","string",&mHiLink16_MacroList)
					 .set_comment("HiLink16 Macro List for test")
					 //.set_options("0,1:FromPinList")
					 .set_default("0,1");
		add_param("PinList","PinString",&mPinList);
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

		static LANE_DOUBLE			All0_MinSwing;
		static LANE_DOUBLE			All1_MaxSwing;


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
			INT					iTxMainStart = 30;
			INT					iTxMainStop = 0;
			INT					iTxMainStep = 3;

			//=============================================
			// Device Setup
			//=============================================
			d2s_JTAG& jtag = d2s_JTAG::Instance();

			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_SQUELCH_DET_SATA_SAS_ABIST_SETUP",Global_D2S_Mode);

				DS.rxRegs.addSkipCheckCSR(31);
				DS.rxRegs.addSkipCheckCSR(40);
				DS.rxRegs.addSkipCheckCSR(44);
				DS.rxRegs.addSkipCheckCSR(37);

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

				DS.txRegs.setprbsgenpatsel(8).Write2DUT(4);

				DS.txRegs.settxcuspat1(0x5555).Write2DUT(5);
				DS.txRegs.settxcuspat2(0x5333).Write2DUT(6);
				DS.txRegs.settxcuspat3(0x33C1).Write2DUT(7);
				DS.txRegs.settxcuspat4(0x4FAD).Write2DUT(8);
				DS.txRegs.settxcuspat5(0x8C9C).Write2DUT(9);

				DS.txRegs.settxdatasel(2)					/*Select Tx data from PRBS generator*/
					     .settxalignmode(3)					/*Set Tx align mode to Freeze mode*/
					     .Write2DUT(2);

				DS.txRegs.setprbsgenen(1)					/*Enable Tx PRBS generator*/
					     .Write2DUT(4);

			d2s::d2s_LABEL_END();

			//=============================================
			//measurement
			//=============================================

			LANE_INT	 		SquelchStat;
			SquelchStat.init(-99);
			All0_MinSwing.init(-99);
			All1_MaxSwing.init(-99);
			const INT 			ReadCnt = 10;
			LANE_INT 			Find_MinAll0_PerLane;
			LANE_INT 			Find_MaxAll1_PerLane;
			Find_MinAll0_PerLane.init(0);
			Find_MaxAll1_PerLane.init(0);
			bool isAll0Flag = true;
			INT iFind_All = 0;

			FIR.iTxMain = iTxMainStart;
			FIR.iTxPost1st = 0;
			FIR.iTxPost2nd = 0;
			FIR.iTxPre1st = 0;
			FIR.iTxPre2nd = 0;


			while ((FIR.iTxMain >= iTxMainStop) && ((iFind_All == 0) || (Global_D2S_Mode == LearningMode)))
			{
				//todo:print spec value for each step
				sprintf(label,"H16LRTV100_MPB_SQUELCH_DET_SATA_SAS_ABIST_RateMode%d_DataWidth%d",CUSTpara.RateMode,CUSTpara.DataWidth);
				d2s::d2s_LABEL_BEGIN(label, Global_D2S_Mode);

					selectMacro_MB(MacroLane_Sel);
					DS.Broadcast();

					SetTxFir(FIR);
					jtag.wait(40 *0.000001);

				d2s::d2s_LABEL_END();

				hout(DETAIL) << "========== Current value of spec = " << dec << FIR.iTxMain << " ==========" << endl;

				if (isAll0Flag) {
					d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_SQUELCH_DET_SATA_SAS_CheckAll0",Global_D2S_Mode);

//						jtag.enablePassFailCheckForNextExecution();

						for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
							UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
							const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
							selectMacro(MacroID);
							for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
								UINT LaneID = vLane[laneIndex];
								DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
								for(INT ReadIdx = 0; ReadIdx < ReadCnt; ReadIdx ++) {
									DS.rxRegs.ExpectValue(61, 0, 0x7fff);
								}
							}
						}

					d2s::d2s_LABEL_END();

//					if (jtag.hasAllSitesPassed("H16LRTV100_MPB_SQUELCH_DET_SATA_SAS_CheckAll0")) {
					if (hasAllSitesPassed()) {
						SquelchStat.init(ALL0);
					} else {
						isAll0Flag = false;
					}
				} else {
					Squelch_check(MacroLane_Sel,ReadCnt,SquelchStat);
				}

				//todo:Other method for debugging delete this todo bolck if not use
				//call sub func Update_LaneData_InTolerance()
				//demo:iFind_All = Update_LaneData_InTolerance(MacroLane_Sel, FIR.iTxMain, ErrorCount, MinAmp, FindFlag);
				iFind_All = 1;

				FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
					for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
					{
						UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
						const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

						for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
						{
							UINT LaneID = vLane[laneIndex];
							/****************Log last All0 point**************/
							if (SquelchStat[SiteID][MacroID][LaneID] != ALL0) {
								if (0 == Find_MinAll0_PerLane[SiteID][MacroID][LaneID]) {
									All0_MinSwing[SiteID][MacroID][LaneID] = FIR.iTxMain + iTxMainStep;
									Find_MinAll0_PerLane[SiteID][MacroID][LaneID] = 1;
								}
							}
							/****************Log first All1 point**************/
							if (SquelchStat[SiteID][MacroID][LaneID] == ALL1) {
								if (0 == Find_MaxAll1_PerLane[SiteID][MacroID][LaneID]) {
									All1_MaxSwing[SiteID][MacroID][LaneID] = FIR.iTxMain;
									Find_MaxAll1_PerLane[SiteID][MacroID][LaneID] = 1;
								}
							} else {
								iFind_All = 0;
							}
						}
					}
				FOREACH_ACTIVESITE_END

				//todo:update spec here
				FIR.iTxMain -= iTxMainStep;
			}

			//=============================================
			//restore
			//=============================================
			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_SQUELCH_DET_SATA_SAS_ABIST_RESTORE", Global_D2S_Mode);

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
							All0_MinSwing[SiteID][MacroID][LaneID] = 12;
							All1_MaxSwing[SiteID][MacroID][LaneID] = 12;
						}
					}
				}
			FOREACH_ACTIVESITE_END

		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "VppdDET", All0_MinSwing);
//		HiLink_PerLane_Judge(MacroLane_Sel, "VppdIDLE", All1_MaxSwing);

		return;
	}

};
REGISTER_TESTCLASS("Squelch_Detection_SATA_SAS_ABIST", Squelch_Detection_SATA_SAS_ABIST);
