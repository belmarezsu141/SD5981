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




class ILOLockMargin: public TestClass {
public:
	STRING 						mHiLink16_MacroList;
	STRING 						mPinList;
	STRING						sFWTest_EN;
	INT							iPrintLvl;


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
		add_param("FWTest_EN","string",&sFWTest_EN)
					 .set_comment("Registor or API")
					 //.set_options("YES:NO")
					 .set_default("NO");
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

		static	LANE_DOUBLE			Margin;
		static	LANE_DOUBLE			Band;
		static	LANE_DOUBLE			IOSCDAC_NOR;
		static	LANE_DOUBLE			IOSCDAC_MAX;

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

			IOSCDAC_NOR.init(-2);
			IOSCDAC_MAX.init(-2);
			Band.init(-2);
			Margin.init(999);

			if ("YES" == sFWTest_EN) {
				d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_ILOLockMargin_API_1FE34_1FE32",Global_D2S_Mode);

					for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
					{
						INT				nor_addr = 0x1FE34;
						INT				max_addr = 0x1FE32;
						UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
						selectMacro(MacroID);

						const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
						for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
						{
							UINT LaneID = vLane[laneIndex];
							ostringstream idnor;
							ostringstream idmax;
							idnor << "ILOLockMargin_API_0x1FE34_" << "M" << MacroID << "_L" << LaneID << jtag.Context;
							idmax << "ILOLockMargin_API_0x1FE32_" << "M" << MacroID << "_L" << LaneID << jtag.Context;
							jtag.read(nor_addr>>1,idnor.str());
							jtag.read(max_addr>>1,idmax.str());
							nor_addr += 0x6;
							max_addr += 0x6;
						}
					}

				d2s::d2s_LABEL_END();

				FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

					for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
					{
						UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
						const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

						for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
						{
							UINT LaneID = vLane[laneIndex];
							ostringstream idnor;
							ostringstream idmax;
							idnor << "ILOLockMargin_API_0x1FE34_" << "M" << MacroID << "_L" << LaneID << jtag.Context;
							idmax << "ILOLockMargin_API_0x1FE32_" << "M" << MacroID << "_L" << LaneID << jtag.Context;

							IOSCDAC_NOR[SiteID][MacroID][LaneID] = (INT)jtag.getReadValue(idnor.str())[SiteID];
							IOSCDAC_MAX[SiteID][MacroID][LaneID] = (INT)jtag.getReadValue(idmax.str())[SiteID];

							IOSCDAC_NOR[SiteID][MacroID][LaneID] = ((INT)IOSCDAC_NOR[SiteID][MacroID][LaneID])>>8;
							IOSCDAC_MAX[SiteID][MacroID][LaneID] = ((INT)IOSCDAC_MAX[SiteID][MacroID][LaneID])>>8;
						}
					}
				FOREACH_ACTIVESITE_END
			} else if ("NO" == sFWTest_EN) {

				LANE_INT	CSR27value;
				CSR_READ(MacroLane_Sel, DS.clkRegs, 27,CSR27value);

				FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

					for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
						UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
						const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
						for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++){
							UINT LaneID = vLane[laneIndex];
							Band[SiteID][MacroID][LaneID] = DS.clkRegs.get_bits(CSR27value[SiteID][MacroID][LaneID], DS.clkRegs.REG_INFO.dsclk_calib_voscref());
							IOSCDAC_NOR[SiteID][MacroID][LaneID] = DS.clkRegs.get_bits(CSR27value[SiteID][MacroID][LaneID], DS.clkRegs.REG_INFO.dsclk_calib_ioscdaccal());
						}
					}
				FOREACH_ACTIVESITE_END

				/***************Relevant Reg Config*******************/
				DSCLK_Setup(MacroLane_Sel,Band);

				d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_Autotune_setup",Global_D2S_Mode);
						selectMacro_MB(MacroLane_Sel);
						DS.Broadcast();
						DS.clkRegs.setautotune(4).Write2DUT(9);
				d2s::d2s_LABEL_END();

				LANE_INT	CSR5value;
				CSR_READ(MacroLane_Sel, DS.clkRegs, 5, CSR5value);

				LANE_INT			IOSCDAC_TMP;

				FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

					for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
						UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
						const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
						for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++){
							UINT LaneID = vLane[laneIndex];
							IOSCDAC_TMP[SiteID][MacroID][LaneID] = (INT)IOSCDAC_NOR[SiteID][MacroID][LaneID];
						}
					}
				FOREACH_ACTIVESITE_END

				LANE_INT 			FindFlag;
				LANE_INT   			RingVcoOutofLock;
				FindFlag.init(0);
				INT iFind_All = 0;
				INT	ScanDoneFlag = 0;
				while ((ScanDoneFlag == 0) && ((iFind_All == 0) || (Global_D2S_Mode == LearningMode)))
				{
					//todo:call d2s_begin_end_block template and setup for each step
					PrintLaneSegInfo(MacroLane_Sel, DS.clkRegs.REG_INFO.ioscdaccal(), IOSCDAC_TMP);

			        Update_ForDynamicWrite(MacroLane_Sel, DS.clkRegs.REG_INFO.ioscdaccal(), IOSCDAC_TMP, CSR5value);

					d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_ILOLockMargin_Registor",Global_D2S_Mode);

						for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
						{
							UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
							selectMacro(MacroID);
							const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

							for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
							{
								UINT LaneID = vLane[laneIndex];

								DS.clkRegs.SliceID(LaneID).Broadcast(0);

                                ostringstream id5;
                                id5 << "DSCLK_CSR5_" << "_M" << MacroID << "_L" << LaneID << jtag.Context;
                                map<int,long long> tmp;
                                parseSiteDataFromLaneInt(tmp,CSR5value,MacroID,LaneID);
								DS.clkRegs.Write2DUT_DYN(5,tmp,id5.str());
							}
						}

					d2s::d2s_LABEL_END();

					//todo:print spec value for each step
					//todo:call sub func ReadBert_ExpectValue()
//					****************************************************************************/

					SEGMENT_READ(MacroLane_Sel, DS.clkRegs.REG_INFO.ringvcooutoflock(), RingVcoOutofLock);
					if (hout.IsDetailEn()) {
						PrintLaneSegInfo(MacroLane_Sel, DS.clkRegs.REG_INFO.ringvcooutoflock(), RingVcoOutofLock);
					}

					//todo:Other method for debugging delete this todo bolck if not use
					//call sub func Update_LaneData_InTolerance()

					iFind_All = 1;
					FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

						for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
							UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
							const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
							for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
								UINT LaneID = vLane[laneIndex];
								if (RingVcoOutofLock[SiteID][MacroID][LaneID] == 0 && FindFlag[SiteID][MacroID][LaneID] == 0) {
									IOSCDAC_MAX[SiteID][MacroID][LaneID] = IOSCDAC_TMP[SiteID][MacroID][LaneID];
									iFind_All = 0;
								} else {
									FindFlag[SiteID][MacroID][LaneID] = 1;
								}
							}
						}
					FOREACH_ACTIVESITE_END

					//todo:update spec here
					ScanDoneFlag = 1;
					FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

						for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
							UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
							const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
							for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
								UINT LaneID = vLane[laneIndex];
								IOSCDAC_TMP[SiteID][MacroID][LaneID] += 2;
								if (IOSCDAC_TMP[SiteID][MacroID][LaneID] > 0xff) {
									IOSCDAC_TMP[SiteID][MacroID][LaneID] = 0xff;
								} else {
									ScanDoneFlag = 0;
								}
							}
						}
					FOREACH_ACTIVESITE_END
				}
			} else {
				hout(RELEASE) << "Please select TestMode: API or Registor!" << endl;
				_exit(0);
			}


			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
						UINT LaneID = vLane[laneIndex];
						Margin[SiteID][MacroID][LaneID] = IOSCDAC_MAX[SiteID][MacroID][LaneID] - IOSCDAC_NOR[SiteID][MacroID][LaneID];
						hout(GENERAL) << "MacroID = " <<  MacroID << "\tLaneID = " << LaneID << "\tIOSCDAC_NOR = " << dec << IOSCDAC_NOR[SiteID][MacroID][LaneID]
									  << "\t" << "IOSCDAC_MAX = " << dec << IOSCDAC_MAX[SiteID][MacroID][LaneID]
									  << "\t" << "Margin = " << Margin[SiteID][MacroID][LaneID] << endl;
						if (iOffline) {
							Band[SiteID][MacroID][LaneID] = 4;
							Margin[SiteID][MacroID][LaneID] = 20;
						}
					}
				}
			FOREACH_ACTIVESITE_END


		//=============================================
		// Datalog
		//=============================================
//
//		HiLink_PerLane_DummyJudge(MacroLane_Sel, "Band", Band);
//		HiLink_PerLane_DummyJudge(MacroLane_Sel, "IOSCDAC_NOR", IOSCDAC_NOR);
//
//		INT SiteID = CURRENT_SITE_NUMBER() - 1;
//		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
//			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
//				UINT LaneID = vLane[laneIndex];
//				STRING	sJudgePin = LANE_INFO[MacroID][LaneID].RX_P;
//				STRING	sTestName = "";
//				if (Band[SiteID][MacroID][LaneID] >= 4 && Band[SiteID][MacroID][LaneID] <= 7) {
//					if (IOSCDAC_NOR[SiteID][MacroID][LaneID] >= 0 && IOSCDAC_NOR[SiteID][MacroID][LaneID] <= 15) {
//						sTestName = "Margin_band4_7_nor0_15";
//					} else if (IOSCDAC_NOR[SiteID][MacroID][LaneID] >= 16 && IOSCDAC_NOR[SiteID][MacroID][LaneID] <= 40) {
//						sTestName = "Margin_band4_7_nor16_40";
//					} else if (IOSCDAC_NOR[SiteID][MacroID][LaneID] >= 41 && IOSCDAC_NOR[SiteID][MacroID][LaneID] <= 255) {
//						sTestName = "Margin_band4_7_nor41_255";
//					} else
//						cerr << "No judge for this pin!!!!!!!!" << endl;
//				} else if (Band[SiteID][MacroID][LaneID] >= 8 && Band[SiteID][MacroID][LaneID] <= 9) {
//					if (IOSCDAC_NOR[SiteID][MacroID][LaneID] >= 0 && IOSCDAC_NOR[SiteID][MacroID][LaneID] <= 15) {
//						sTestName = "Margin_band8_9_nor0_15";
//					} else if (IOSCDAC_NOR[SiteID][MacroID][LaneID] >= 16 && IOSCDAC_NOR[SiteID][MacroID][LaneID] <= 40) {
//						sTestName = "Margin_band8_9_nor16_40";
//					} else if (IOSCDAC_NOR[SiteID][MacroID][LaneID] >= 41 && IOSCDAC_NOR[SiteID][MacroID][LaneID] <= 255) {
//						sTestName = "Margin_band8_9_nor41_255";
//					} else
//						cerr << "No judge for this pin!!!!!!!!" << endl;
//				} else if (Band[SiteID][MacroID][LaneID] >= 10 && Band[SiteID][MacroID][LaneID] <= 12) {
//					if (IOSCDAC_NOR[SiteID][MacroID][LaneID] >= 0 && IOSCDAC_NOR[SiteID][MacroID][LaneID] <= 15) {
//						sTestName = "Margin_band10_12_nor0_15";
//					} else if (IOSCDAC_NOR[SiteID][MacroID][LaneID] >= 16 && IOSCDAC_NOR[SiteID][MacroID][LaneID] <= 40) {
//						sTestName = "Margin_band10_12_nor16_40";
//					} else if (IOSCDAC_NOR[SiteID][MacroID][LaneID] >= 41 && IOSCDAC_NOR[SiteID][MacroID][LaneID] <= 255) {
//						sTestName = "Margin_band10_12_nor41_255";
//					} else
//						cerr << "No judge for this pin!!!!!!!!" << endl;
//				} else if (Band[SiteID][MacroID][LaneID] >= 13 && Band[SiteID][MacroID][LaneID] <= 15) {
//					if (IOSCDAC_NOR[SiteID][MacroID][LaneID] >= 0 && IOSCDAC_NOR[SiteID][MacroID][LaneID] <= 15) {
//						sTestName = "Margin_band13_15_nor0_15";
//					} else if (IOSCDAC_NOR[SiteID][MacroID][LaneID] >= 16 && IOSCDAC_NOR[SiteID][MacroID][LaneID] <= 40) {
//						sTestName = "Margin_band13_15_nor16_40";
//					} else if (IOSCDAC_NOR[SiteID][MacroID][LaneID] >= 41 && IOSCDAC_NOR[SiteID][MacroID][LaneID] <= 255) {
//						sTestName = "Margin_band13_15_nor41_255";
//					} else
//						cerr << "No judge for this pin!!!!!!!!" << endl;
//				} else
//					sTestName = "Margin_band_fail";
//					cerr << "No judge for this pin!!!!!!!!" << endl;
//
//				TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(sJudgePin, sTestName, tmLimits, Margin[SiteID][MacroID][LaneID]);
//			}
//		}
//

		return;
		}

};
REGISTER_TESTCLASS("ILOLockMargin", ILOLockMargin);

