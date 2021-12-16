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
class RxFreqOffsetTol_ABIST: public TestClass {

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
	// This TM is to record the maximum Tx frequency offset PPM value, with which //
	// there is no error count by reading register in internal loopback mode.     //
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

		static	LANE_DOUBLE 		MaxPPM_N;
		static	LANE_DOUBLE 		MaxPPM_P;


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

			sprintf(label,"H16LRTV100_MPB_RXFREQOFFSETTOL_ABIST_RateMode%d_DataWidth%d",CUSTpara.RateMode,CUSTpara.DataWidth);
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
			MaxPPM_N.init(0);
			MaxPPM_P.init(0);

			searchFreqOffset(MacroLane_Sel, CUSTpara.RateMode,CUSTpara.DataWidth, true, MaxPPM_P);
			searchFreqOffset(MacroLane_Sel, CUSTpara.RateMode,CUSTpara.DataWidth, false, MaxPPM_N);


		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "FreqOffset_Pos", MaxPPM_P);
//		HiLink_PerLane_Judge(MacroLane_Sel, "FreqOffset_Neg", MaxPPM_N);

		return;
	}

	//======================================Hi1213================================
	virtual void searchFreqOffset(const MACRO_LANE_SEL MacroLane_Sel, const INT& iRateMode, const INT& iDataWidth, bool isPos, LANE_DOUBLE& PPMResult)
		{


			INT					Index = 9;
			INT 				PPMIndex;
			hout(GENERAL) << "&&&&&&&&&&   slew rate direction = " << isPos << "   &&&&&&&&&&" << endl;
			LANE_DOUBLE 		ErrorCount;
			LANE_INT 			FindFlag;
			ErrorCount.init(0);
			FindFlag.init(0);

			/*************GUI CODE BEGIN***********/
			DOUBLE 			UIsize = 64;
			DOUBLE 			WORDWIDTH;

			switch (iDataWidth)
			{
				case 0: WORDWIDTH = 16; break;
				case 1: WORDWIDTH = 20; break;
				case 2: WORDWIDTH = 16; break;
				case 3: WORDWIDTH = 20; break;
				default: WORDWIDTH = 20; break;
			}

			switch (iRateMode)
			{
				case 0: WORDWIDTH /= 1; UIsize = 64; break;
				case 1: WORDWIDTH /= 2; UIsize = 128; break;
				case 2: WORDWIDTH /= 4; UIsize = 256; break;
				case 3: WORDWIDTH /= 8; UIsize = 512; break;
				default: WORDWIDTH /= 1; UIsize = 64; break;
			}

			/*************GUI CODE END***********/

			typedef map <int, double>::value_type  valType;

			map <int, double> mapPPMTol;
			mapPPMTol.insert(valType (0, 1000000.0 / (UIsize * WORDWIDTH * 64)));
			mapPPMTol.insert(valType (1, 1000000.0 / (UIsize * WORDWIDTH * 48)));
			mapPPMTol.insert(valType (2, 1000000.0 / (UIsize * WORDWIDTH * 40)));
			mapPPMTol.insert(valType (3, 1000000.0 / (UIsize * WORDWIDTH * 32)));
			mapPPMTol.insert(valType (4, 1000000.0 / (UIsize * WORDWIDTH * 24)));
			mapPPMTol.insert(valType (5, 1000000.0 / (UIsize * WORDWIDTH * 20)));
			mapPPMTol.insert(valType (6, 1000000.0 / (UIsize * WORDWIDTH * 16)));
			mapPPMTol.insert(valType (7, 1000000.0 / (UIsize * WORDWIDTH * 12)));
			mapPPMTol.insert(valType (8, 1000000.0 / (UIsize * WORDWIDTH * 10)));
			mapPPMTol.insert(valType (9, 1000000.0 / (UIsize * WORDWIDTH * 8)));
			mapPPMTol.insert(valType (10,1000000.0 / (UIsize * WORDWIDTH * 6)));
			mapPPMTol.insert(valType (11,1000000.0 / (UIsize * WORDWIDTH * 5)));
			mapPPMTol.insert(valType (12,1000000.0 / (UIsize * WORDWIDTH * 4)));
			mapPPMTol.insert(valType (13,1000000.0 / (UIsize * WORDWIDTH * 3)));
			mapPPMTol.insert(valType (14,1000000.0 / (UIsize * WORDWIDTH * 2)));
	//		mapPPMTol.insert(valType (15,1000000.0 / (UIsize * WORDWIDTH * 0))); /*****Infinite words******/

			map <int,double>::iterator itPPM;


	//		char label[200];
	//		memset(label,'\0',sizeof(label));
			INT iFind_All = 0;
			//todo:CBB owner must make sure the condition of while is right, no infinite loop;
			//todo:add verify code here;
			while (Index < 15 && ((iFind_All == 0) || (Global_D2S_Mode == LearningMode)))
			{
				//todo:call d2s_begin_end_block template and setup for each step
				sprintf(label,"H15BP_MPB_FREQOFFSET_ABIST_RateMode%d_DataWidth%d",iRateMode,iDataWidth);
				d2s::d2s_LABEL_BEGIN(label,Global_D2S_Mode);

					selectMacro_MB(MacroLane_Sel);
					DS.txRegs.SliceID(0).Broadcast(1);

					DS.txRegs.settxalignmode(4).Write2DUT(2);

					itPPM = mapPPMTol.find (Index);
					if (itPPM != mapPPMTol.end())
					{
						PPMIndex = FreqOffset(iDataWidth, iRateMode, itPPM -> second);
					}

					DS.txRegs.setjitppmctrl(1)
							 .setppmgen(isPos ? PPMIndex : (PPMIndex + 0x10))
							 .setjitamp(0)
							 .setjitfreq(7) /*****Min JitterFreq by set 7*****/
							 .Write2DUT(3);

				d2s::d2s_LABEL_END();
				//todo:print spec value for each step

				//todo:call sub func ReadBert_ExpectValue()
				ReadBert_ExpectValue(MacroLane_Sel,PRBS15,ErrorCount);

				//todo:Other method for debugging delete this todo bolck if not use

				if (hout.IsEyePlotEn()) {
					hout(DETAIL) << "========= DataRate = " << dec << CUSTpara.Data_Rate << " ==========" << endl;
					GetEyeDiagram(MacroLane_Sel, CUSTpara.Data_Rate);
				}

				//call sub func Update_LaneData_InTolerance()
				iFind_All = Update_LaneData_InTolerance(MacroLane_Sel, itPPM -> second * (isPos ? 1.0 : -1.0), ErrorCount, PPMResult, FindFlag);

				//todo:update spec here
				Index ++;
			}


			cout << "*********** PPMResult ************" << endl;
			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						cout << " Macro : " << MacroID << "\tLane : " << LaneID << "\t" << PPMResult[SiteID][MacroID][LaneID] << endl;
					}
				}
			FOREACH_ACTIVESITE_END
		}

};
REGISTER_TESTCLASS("RxFreqOffsetTol_ABIST", RxFreqOffsetTol_ABIST);
