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

class ILOFreqStability: public TestClass {
public:
	STRING 						mHiLink16_MacroList;
	STRING 						mPinList;
	STRING 						mHVCC;
	INT							iPrintLvl;


	/**
	 *Initialize the parameter interface to the testflow.
	 *This method is called just once after a testsuite is created.
	 */
	void init()
	{
		add_param("H16LR_MacroList","string",&mHiLink16_MacroList)
					 //.set_options("0,1:FromPinList")
					 .set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
		add_param("HVCC_PinName","PinString",&mHVCC);
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

		static	LANE_DOUBLE 		DiffNtoH;
		static	LANE_DOUBLE 		DiffNtoL;


			//=============================================
			// Variables and MacroLane initialization
			//=============================================
			iOffline = 0;
			sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
			hout.setLevel(iPrintLvl);
			hout.printsuitename(sTestsuiteName);
			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

			STRING_VECTOR 			vDPSPins_HVCC;
			parseListOfString(mHVCC,vDPSPins_HVCC,',');

			//=============================================
			// Device Setup
			//=============================================
			d2s_JTAG& jtag = d2s_JTAG::Instance();

			LANE_INT 			LLD_DIFF_N;
			LANE_INT 			LLD_DIFF_L;
			LANE_INT 			LLD_DIFF_H;

			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_ILOFreqStability_SETUP",Global_D2S_Mode);

				selectMacro_MB(MacroLane_Sel);
				DS.Broadcast();
				DS.clkRegs.setautotune(0x4).Write2DUT(9);
				DS.clkRegs.setinjen(0x0).Write2DUT(1);

			d2s::d2s_LABEL_END();

			DOUBLE 		HVCC_ORI = 1.8;
			DOUBLE		dOrgVal;

			if (vDPSPins_HVCC.size() > 0) {
				for (UINT i = 0; i < vDPSPins_HVCC.size(); i ++) {
//					dOrgVal = Primary.getLevelSpec().getSpecValue(vDPSPins_HVCC[i]);
					dOrgVal = TheSoft.Specs().GetValue("level_spec.spec", vDPSPins_HVCC[i]);
					hout(GENERAL) << "HVCC pin " << vDPSPins_HVCC[i] << "= " << dOrgVal << "V" << endl;
				}
			}

			SEGMENT_READ(MacroLane_Sel, DS.clkRegs.REG_INFO.dsclk_lld_diff_freq(),LLD_DIFF_N);

			if (vDPSPins_HVCC.size() > 0) {
//				try {
					for (UINT i = 0; i < vDPSPins_HVCC.size(); i ++) {
//						Primary.getLevelSpec().change(vDPSPins_HVCC[i], HVCC_ORI * 1.03);
						TheSoft.Specs().SetValue("level_spec.spec", vDPSPins_HVCC[i], HVCC_ORI * 1.03);
					}
//					FLUSH(TM::APRM);
					if(isDPS128)
						TheInst.DCVI().Power().DynamicApply();
					else
						TheInst.DCVS().Power().DynamicApply();
//				} catch (Error &error) {
//					for (UINT i = 0; i < vDPSPins_HVCC.size(); i ++) {
//						Primary.getLevelSpec().change(vDPSPins_HVCC[i], dOrgVal);
//					}
//					FLUSH(TM::APRM);
//					ERROR_EXIT(TM::RETURN_TO_FLOW);
//				}
				for (UINT i = 0; i < vDPSPins_HVCC.size(); i ++) {
					hout(GENERAL) << "HVCC pin " << vDPSPins_HVCC[i] << "= " << HVCC_ORI * 1.03 << "V" << endl;
				}
			}
//			WAIT_TIME(100 ms);
			SEGMENT_READ(MacroLane_Sel, DS.clkRegs.REG_INFO.dsclk_lld_diff_freq(),LLD_DIFF_H);

			if (vDPSPins_HVCC.size() > 0) {
//				try {
					for (UINT i = 0; i < vDPSPins_HVCC.size(); i ++) {
//						Primary.getLevelSpec().change(vDPSPins_HVCC[i], HVCC_ORI * 0.97);
						TheSoft.Specs().SetValue("level_spec.spec", vDPSPins_HVCC[i], HVCC_ORI * 0.97);
					}
//					FLUSH(TM::APRM);
					if(isDPS128)
						TheInst.DCVI().Power().DynamicApply();
					else
						TheInst.DCVS().Power().DynamicApply();
//				} catch (Error &error) {
//					for (UINT i = 0; i < vDPSPins_HVCC.size(); i ++) {
//						Primary.getLevelSpec().change(vDPSPins_HVCC[i], dOrgVal);
//					}
//					FLUSH(TM::APRM);
//					ERROR_EXIT(TM::RETURN_TO_FLOW);
//				}
				for (UINT i = 0; i < vDPSPins_HVCC.size(); i ++) {
					hout(GENERAL) << "HVCC pin " << vDPSPins_HVCC[i] << "= " << HVCC_ORI * 0.97 << "V" << endl;
				}
			}
//			WAIT_TIME(100 ms);
			SEGMENT_READ(MacroLane_Sel, DS.clkRegs.REG_INFO.dsclk_lld_diff_freq(),LLD_DIFF_L);

			DiffNtoH.init(999);
			DiffNtoL.init(999);

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
//						if (LLD_DIFF_H[SiteID][MacroID][LaneID] != LLD_DIFF_L[SiteID][MacroID][LaneID]) {
						DiffNtoH[SiteID][MacroID][LaneID] = abs(LLD_DIFF_N[SiteID][MacroID][LaneID] - LLD_DIFF_H[SiteID][MacroID][LaneID]);
						DiffNtoL[SiteID][MacroID][LaneID] = abs(LLD_DIFF_N[SiteID][MacroID][LaneID] - LLD_DIFF_L[SiteID][MacroID][LaneID]);
//						}
						if (iOffline) {
							DiffNtoH.init(8);
							DiffNtoL.init(8);
						}
						hout(GENERAL) << "MacroID = " << MacroID << "\tLaneID = " << LaneID << "\tDiffNtoH = " << DiffNtoH[SiteID][MacroID][LaneID]
																							<< "\tDiffNtoL = " << DiffNtoL[SiteID][MacroID][LaneID] << endl;
					}
				}
			FOREACH_ACTIVESITE_END

			/************restore HVCC***********/
			if (vDPSPins_HVCC.size() > 0) {
				for (UINT i = 0; i < vDPSPins_HVCC.size(); i ++) {
//					Primary.getLevelSpec().change(vDPSPins_HVCC[i], dOrgVal);
					TheSoft.Specs().SetValue("level_spec.spec", vDPSPins_HVCC[i], dOrgVal);
				}
//				FLUSH(TM::APRM);
				if(isDPS128)
					TheInst.DCVI().Power().DynamicApply();
				else
					TheInst.DCVS().Power().DynamicApply();
			}


		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "LLD_DIFF_NtoH", DiffNtoH);
//		HiLink_PerLane_Judge(MacroLane_Sel, "LLD_DIFF_NtoL", DiffNtoL);

		return;
		}

};
REGISTER_TESTCLASS("ILOFreqStability", ILOFreqStability);

