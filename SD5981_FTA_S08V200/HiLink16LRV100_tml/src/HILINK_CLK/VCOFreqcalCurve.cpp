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

class VCOFreqcalCurve: public TestClass {
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

	void execute()
	{
		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
		static	STRING          	sTestsuiteName;
		static	INT					iOffline;
		static  MACRO_LANE_SEL 		MacroLane_Sel;

		static	MACRO_DOUBLE				OpenLoopLLDDIFF;
		static	vector<MACRO_DOUBLE> 		CurveLength_Min;
		static	vector<MACRO_DOUBLE> 		CurveLength_Max;


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


			ARRAY_D				CurveLength;
			CurveLength.resize(MacroLane_Sel.size());
			CurveLength.init(0.0);

			OpenLoopLLDDIFF.init(0.0);
			for (INT iBand = 0; iBand <= 3; iBand ++) {
				MACRO_DOUBLE	tmp;
				tmp.init(0.0);
				CurveLength_Min.push_back(tmp);
				CurveLength_Max.push_back(tmp);
			}

			INT			iFreqcal_min;
			INT			iFreqcal_max;

			if (CUSTpara.CSslice == 0) {
				if (HILINK_INFO[MacroLane_Sel[0].MacroID].CS0_Type == CSL) {
					iFreqcal_max = 0x0;
					iFreqcal_min = 0xF;
				} else if (HILINK_INFO[MacroLane_Sel[0].MacroID].CS0_Type == CSH) {
					iFreqcal_max = 0x0;
					iFreqcal_min = 0x13;
				}
			} else {
				if (HILINK_INFO[MacroLane_Sel[0].MacroID].CS1_Type == CSL) {
					iFreqcal_max = 0x0;
					iFreqcal_min = 0xF;
				} else if (HILINK_INFO[MacroLane_Sel[0].MacroID].CS1_Type == CSH) {
					iFreqcal_max = 0x0;
					iFreqcal_min = 0x13;
				}
			}

			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_VCOFreqcalCurve_SETUP",Global_D2S_Mode);

				CS.clkRegs.addSkipCheckCSR(13);

				selectMacro_MB(MacroLane_Sel);
				CS.clkRegs.SliceID(CUSTpara.CSslice).Broadcast(0);

				CS.clkRegs.setlcvcocalmode(0x1).Write2DUT(13);
				CS.clkRegs.setcalrstb(0x1).Write2DUT(12);
				CS.clkRegs.setlcvcoitank(0xE).Write2DUT(7);

			d2s::d2s_LABEL_END();

			for (INT iBand = 0; iBand <= 3; iBand ++)
			{
				hout(DETAIL) << "ClockSlice = " << CUSTpara.CSslice << "\tBand = " << iBand << endl;
				d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_VCOFreqcalCurve_BAND_MAX_SETUP",Global_D2S_Mode);

					selectMacro_MB(MacroLane_Sel);
					CS.clkRegs.SliceID(CUSTpara.CSslice).Broadcast(0);

					CS.clkRegs.setlcvcobandsel(iBand)
							  .setlcvcofreqcal(iFreqcal_max)
							  .Write2DUT(7);

				d2s::d2s_LABEL_END();

				hout(DETAIL) << "Lcvcofreqcal_min = " << iFreqcal_max << endl;

				ReadAndCalcVCOFreqcalCurveLength(MacroLane_Sel, CUSTpara.CSslice, CurveLength_Max[iBand]);

				LogDiffFreqOpenLoop(MacroLane_Sel, CUSTpara.CSslice, OpenLoopLLDDIFF);/* todo if necessary*/

				sprintf(label,"H16LRTV100_MPB_VCOFreqcalCurve_BAND_MIN_SETUP_Band%d",iBand);
				d2s::d2s_LABEL_BEGIN(label, Global_D2S_Mode);

					selectMacro_MB(MacroLane_Sel);
					CS.clkRegs.SliceID(CUSTpara.CSslice).Broadcast(0);

					CS.clkRegs.setlcvcofreqcal(iFreqcal_min)
							  .Write2DUT(7);

				d2s::d2s_LABEL_END();

				hout(DETAIL) << "Lcvcofreqcal_max = " << iFreqcal_min << endl;

				ReadAndCalcVCOFreqcalCurveLength(MacroLane_Sel, CUSTpara.CSslice, CurveLength_Min[iBand]);

				LogDiffFreqOpenLoop(MacroLane_Sel, CUSTpara.CSslice, OpenLoopLLDDIFF);/* todo if necessary*/
			}

			if (iOffline) {
				CurveLength_Min.clear();
				CurveLength_Max.clear();
				for (INT iBand = 0; iBand <= 3; iBand ++) {
					MACRO_DOUBLE	tmp;
					tmp.init(200.0);
					CurveLength_Min.push_back(tmp);
					CurveLength_Max.push_back(tmp);
				}
			}


		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerMacro_Judge(MacroLane_Sel, "Band0_Freqcalmin", CurveLength_Min[0]);
//		HiLink_PerMacro_Judge(MacroLane_Sel, "Band0_Freqcalmax", CurveLength_Max[0]);
//		HiLink_PerMacro_Judge(MacroLane_Sel, "Band1_Freqcalmin", CurveLength_Min[1]);
//		HiLink_PerMacro_Judge(MacroLane_Sel, "Band1_Freqcalmax", CurveLength_Max[1]);
//		HiLink_PerMacro_Judge(MacroLane_Sel, "Band2_Freqcalmin", CurveLength_Min[2]);
//		HiLink_PerMacro_Judge(MacroLane_Sel, "Band2_Freqcalmax", CurveLength_Max[2]);
//		HiLink_PerMacro_Judge(MacroLane_Sel, "Band3_Freqcalmin", CurveLength_Min[3]);
//		HiLink_PerMacro_Judge(MacroLane_Sel, "Band3_Freqcalmax", CurveLength_Max[3]);
//		HiLink_PerMacro_DummyJudge(MacroLane_Sel, "OpenLoop", OpenLoopLLDDIFF);

		return;
		}
};
REGISTER_TESTCLASS("VCOFreqcalCurve", VCOFreqcalCurve);

