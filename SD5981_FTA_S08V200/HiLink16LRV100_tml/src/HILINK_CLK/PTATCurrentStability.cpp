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

class PTATCurrentStability: public TestClass {
public:
	STRING 						mHiLink16_MacroList;
	STRING 						mPinList;
	INT					   		iPrintLvl;

	/**
	 *Initialize the parameter interface to the testflow.
	 *This method is called just once after a testsuite is created.
	 */
	void init()
	{
		add_param("H16LR_MacroList","string",&mHiLink16_MacroList)
					 .set_comment("Only Macro with SS need to be test")
					 //.set_options("0,1:FromPinList")
					 .set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
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

		static	LANE_DOUBLE 		LLD_DIFF_PD;
		static	LANE_DOUBLE 		DiffNtoPU;

			//=============================================
			// Variables and MacroLane initialization
			//=============================================
			iOffline = 0;
			sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
			hout.setLevel(iPrintLvl);
			hout.printsuitename(sTestsuiteName);
			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

			//=============================================
			// Device Setup
			//=============================================
			d2s_JTAG& jtag = d2s_JTAG::Instance();

			LANE_DOUBLE 			LLD_DIFF_N;
			LANE_DOUBLE 			LLD_DIFF_PU;

			LLD_DIFF_N.init(0);
			DiffNtoPU.init(0);
			LLD_DIFF_PD.init(0);
			DiffNtoPU.init(0);

			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_ILOFreqStability_SETUP",Global_D2S_Mode);

				selectMacro_MB(MacroLane_Sel);
				DS.Broadcast();
				DS.clkRegs.setautotune(0x4).Write2DUT(9);
				DS.clkRegs.setinjen(0x0).Write2DUT(1);

			d2s::d2s_LABEL_END();

			hout(GENERAL) << "Normal bandgap" << endl;

			SEGMENT_READ(MacroLane_Sel, DS.clkRegs.REG_INFO.dsclk_lld_diff_freq(),LLD_DIFF_N);

			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_ILOFreqStability_PowerDown",Global_D2S_Mode);

				selectMacro_MB(MacroLane_Sel);
				CS.clkRegs.SliceID(CUSTpara.CSslice).Broadcast(0);
				CS.clkRegs.setbgpaten(0x0).Write2DUT(17);

			d2s::d2s_LABEL_END();

//			WAIT_TIME(500 us);
			TheInst.Wait(0.000001*500);

			hout(GENERAL) << "Power Down PTAT bandgap" << endl;

			SEGMENT_READ(MacroLane_Sel, DS.clkRegs.REG_INFO.dsclk_lld_diff_freq(),LLD_DIFF_PD);

			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_ILOFreqStability_PowerUp",Global_D2S_Mode);

			selectMacro_MB(MacroLane_Sel);
			CS.clkRegs.SliceID(CUSTpara.CSslice).Broadcast(0);
			CS.clkRegs.setbgpaten(0x1).Write2DUT(17);

			d2s::d2s_LABEL_END();

//			WAIT_TIME(500 us);
			TheInst.Wait(0.000001*500);

			hout(GENERAL) << "Power Up PTAT bandgap" << endl;

			SEGMENT_READ(MacroLane_Sel, DS.clkRegs.REG_INFO.dsclk_lld_diff_freq(),LLD_DIFF_PU);

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						if (LLD_DIFF_PU[SiteID][MacroID][LaneID] == LLD_DIFF_N[SiteID][MacroID][LaneID] && LLD_DIFF_PD[SiteID][MacroID][LaneID] == LLD_DIFF_N[SiteID][MacroID][LaneID] && LLD_DIFF_PU[SiteID][MacroID][LaneID] == LLD_DIFF_PD[SiteID][MacroID][LaneID]){
							hout(GENERAL) << "LLD_DIFF_N == LLD_DIFF_PD == LLD_DIFF_PU, Please check hilink status!!!!!!" << endl;
						} else {
							DiffNtoPU[SiteID][MacroID][LaneID] = abs(LLD_DIFF_N[SiteID][MacroID][LaneID] - LLD_DIFF_PU[SiteID][MacroID][LaneID]);
						}
						hout(DETAIL) << "MacroID = " << MacroID << "\tLaneID = " << LaneID << "\tDiffNtoPU = " << DiffNtoPU[SiteID][MacroID][LaneID] << endl;
					}
				}
			FOREACH_ACTIVESITE_END


		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "LLD_DIFF_NtoPU", DiffNtoPU);
//		HiLink_PerLane_DummyJudge(MacroLane_Sel, "LLD_DIFF_PD", LLD_DIFF_PD);

		return;
		}

};
REGISTER_TESTCLASS("PTATCurrentStability", PTATCurrentStability);

