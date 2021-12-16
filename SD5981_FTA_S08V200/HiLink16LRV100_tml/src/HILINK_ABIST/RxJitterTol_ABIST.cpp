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
class RxJitterTol_ABIST: public TestClass {

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
	////////////////////////////////////////////////////////////////////////////////
	// TM Purpose:                                                                //
	// This TM is to record the maximum Tx jitter injection value, with which     //
	// there is no error count by reading register in internal loopback mode.     //
	// The Tx jitter injection by setting JITFREQ and JITAMPL register step by    //
	// step.
	//																			  //
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

		LANE_DOUBLE 				MaxJitterAmp;

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

			sprintf(label,"H16LRTV100_MPB_RXJITTERTOL_ABIST_SETUP_RateMode%d_DataWidth%d",CUSTpara.RateMode,CUSTpara.DataWidth);
			d2s::d2s_LABEL_BEGIN(label,Global_D2S_Mode);

				selectMacro_MB(MacroLane_Sel);
				DS.Broadcast();

				if (mLoopbackMode == "External" ) {
					DisableTxToRxSerLpbk();
				} else {
					EnableTxToRxSerLpbk(mLoopbackMode);
				}

				EnableTxPrbsGen(PRBS15);

				DS.rxRegs.setcdrfreeze(0)
						 .Write2DUT(10);
				jtag.wait(20 *0.000001);

			d2s::d2s_LABEL_END();

			//=============================================
			//measurement
			//=============================================
			LANE_DOUBLE 			ErrorCount;
			LANE_INT				FindFlag;
			MaxJitterAmp.init(0);
			FindFlag.init(0);

			/***************Inject Jitter*******************/
			DOUBLE 			UIsize = 64.0;
			/*set UIsize = 64 is for value in mapJITAMP will be 2X,4X,8X in half,quarter,oct ratemode*/

			typedef map <int, double>::value_type  valType;

			map <int, double> mapJitterInject; /*****<jitterPoint, JitterAmpRequired>******/
			mapJitterInject.insert(valType (0, 3  / UIsize));
			mapJitterInject.insert(valType (1, 4  / UIsize));
			mapJitterInject.insert(valType (2, 5  / UIsize));
			mapJitterInject.insert(valType (3, 6  / UIsize));
			mapJitterInject.insert(valType (4, 8  / UIsize));
			mapJitterInject.insert(valType (5, 10 / UIsize));
			mapJitterInject.insert(valType (6, 12 / UIsize));
			mapJitterInject.insert(valType (7, 16 / UIsize));
			mapJitterInject.insert(valType (8, 20 / UIsize));
			mapJitterInject.insert(valType (9, 24 / UIsize));
			mapJitterInject.insert(valType (10,32 / UIsize));
			mapJitterInject.insert(valType (11,40 / UIsize));
			mapJitterInject.insert(valType (12,48 / UIsize));
			mapJitterInject.insert(valType (13,64 / UIsize));
			mapJitterInject.insert(valType (14,80 / UIsize));
			mapJitterInject.insert(valType (15,96 / UIsize));

			map <int,double>::iterator it;

			INT 			Index = 7;
			JI 				JIIndex;
			INT 			iFind_All = 0;
			//todo:CBB owner must make sure the condition of while is right, no infinite loop;
			//todo:add verify code here;
			while (Index <= 13 && ((iFind_All == 0) || (Global_D2S_Mode == LearningMode))) {
				//todo:call d2s_begin_end_block template and setup for each step
				it = mapJitterInject.find (Index);
				sprintf(label,"H16LRTV100_MPB_RXJITTERTOL_RateMode%d_DataWidth%d",CUSTpara.RateMode,CUSTpara.DataWidth);
				d2s::d2s_LABEL_BEGIN(label,Global_D2S_Mode);

					selectMacro_MB(MacroLane_Sel);

					DS.txRegs.SliceID(0).Broadcast(1);
					DS.txRegs.settxalignmode(4).Write2DUT(2);

					hout(DETAIL) << "======= Jitter Inject index = " << dec << Index << " =======" << endl;

					if (it != mapJitterInject.end()) {
						JIIndex = JitterInjection(CUSTpara.DataWidth, CUSTpara.RateMode, CUSTpara.Data_Rate, it -> second);
					}

					DS.txRegs.setjitppmctrl(1)
							 .setjitfreq(JIIndex.FREQINDEX)
							 .setjitamp(JIIndex.AMPINDEX)
							 .setppmgen(0)			/******been confirmed that 0 means no PPM inserted******/
							 .Write2DUT(3);

				d2s::d2s_LABEL_END();
				//todo:print spec value for each step
				//demo:hout(DETAIL) << "========== main = " << dec << FIR.iTxMain << " ==========" << endl;

				//todo:call sub func ReadBert_ExpectValue()
				ReadBert_ExpectValue(MacroLane_Sel,PRBS15,ErrorCount);

				//todo:Other method for debugging delete this todo bolck if not use
				if (hout.IsEyePlotEn()) {
					hout(DETAIL) << "========= DataRate = " << dec << CUSTpara.Data_Rate << " ==========" << endl;
					GetEyeDiagram(MacroLane_Sel, CUSTpara.Data_Rate);
				}

				//call sub func Update_LaneData_InTolerance()
				iFind_All = Update_LaneData_InTolerance(MacroLane_Sel, it -> second, ErrorCount, MaxJitterAmp, FindFlag);

				//todo:update spec here
				Index ++;
			}

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						hout(DETAIL) << "Macro: " << MacroID << "\tLane: " << LaneID
									 << "\tMaxJitterAmp: " << MaxJitterAmp[SiteID][MacroID][LaneID] << endl;
						if (iOffline) {
							MaxJitterAmp[SiteID][MacroID][LaneID] = 1.0;
						}
					}
				}
			FOREACH_ACTIVESITE_END

		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "Jitter_Amp_UI", MaxJitterAmp);

		return;
	}

};
REGISTER_TESTCLASS("RxJitterTol_ABIST", RxJitterTol_ABIST);
