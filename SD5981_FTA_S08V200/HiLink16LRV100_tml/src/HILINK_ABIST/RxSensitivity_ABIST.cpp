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
class RxSensitivity_ABIST: public TestClass {

public:
	STRING  			mHiLink16_MacroList;
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
	// This TM is to record the maximum Tx FIR main value, with which there is    //
	// no error count by reading register in internal loopback mode. The Tx FIR   //
	// main can reduce step by step.                                              //
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

		static	LANE_DOUBLE 		MinAmp;


			//=============================================
			// Variables and MacroLane initialization
			//=============================================
			iOffline = 0;
			sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();

			hout.setLevel(iPrintLvl);
			hout.printsuitename(sTestsuiteName);
			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

			TxFIR_SETTING 		FIR_ORI, FIR;
			GetTxFIR(FIR_ORI);
			INT					iTxMainStart = 16;
			INT					iTxMainStep = 2;
			//=============================================
			// Device Setup
			//=============================================
			d2s_JTAG& jtag = d2s_JTAG::Instance();

			INT 				iDataWidth = DS.txRegs.gettxdwidth();
			INT 				iRateMode = DS.txRegs.gettxratemode();
			sprintf(label,"H16LRTV100_MPB_RXSWINGTOL_ABIST_SETUP_RateMode%d_DataWidth%d",iRateMode,iDataWidth);
			d2s::d2s_LABEL_BEGIN(label, Global_D2S_Mode);

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
			LANE_DOUBLE				ErrorCount;
			LANE_INT 				FindFlag;
			MinAmp.init(iTxMainStart);
			ErrorCount.init(9999);
			FindFlag.init(0);

			FIR.iTxMain = iTxMainStart;
			FIR.iTxPost1st = 0;
			FIR.iTxPost2nd = 0;
			FIR.iTxPre1st = 0;
			FIR.iTxPre2nd = 0;

			INT iFind_All = 0;
			while (FIR.iTxMain >= 0 && ((iFind_All == 0) || (Global_D2S_Mode == LearningMode)))
			{
				//todo:call d2s_begin_end_block template and setup for each step
				d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_RXSWINGTOL_ABIST", Global_D2S_Mode);

					selectMacro_MB(MacroLane_Sel);
					DS.Broadcast();

					SetTxFir(FIR);
					jtag.wait(40 *0.000001);

				d2s::d2s_LABEL_END();

				//todo:print spec value for each step
				hout(DETAIL) << "========== main = " << dec << FIR.iTxMain << " ==========" << endl;

				//todo:call sub func ReadBert_ExpectValue()
				ReadBert_ExpectValue(MacroLane_Sel, PRBS15, ErrorCount);

				//todo:Other method for debugging delete this todo bolck if not use
				if (hout.IsEyePlotEn()) {
					hout(DETAIL) << "========= DataRate = " << dec << CUSTpara.Data_Rate << " ==========" << endl;
					GetEyeDiagram(MacroLane_Sel, CUSTpara.Data_Rate);
				}

				//call sub func Update_LaneData_InTolerance()
				iFind_All = Update_LaneData_InTolerance(MacroLane_Sel, FIR.iTxMain, ErrorCount, MinAmp, FindFlag);

				//todo:update spec here
				FIR.iTxMain = FIR.iTxMain - iTxMainStep;
			}

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						hout(DETAIL) << "M" << MacroID << "_L" << LaneID << ", The min amp: " << dec << MinAmp[SiteID][MacroID][LaneID] << endl;
						if (iOffline){
							MinAmp[SiteID][MacroID][LaneID] = 20;
						}
					}
				}
			FOREACH_ACTIVESITE_END

			/****restore FIR************/
			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_RXSWINGTOL_ABIST_RESTORE", Global_D2S_Mode);

				selectMacro_MB(MacroLane_Sel);
				DS.Broadcast();

				SetTxFir(FIR_ORI);
				jtag.wait(40 *0.000001);

			d2s::d2s_LABEL_END();


		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "MinSwing", MinAmp);

		return;
		}

};
REGISTER_TESTCLASS("RxSensitivity_ABIST", RxSensitivity_ABIST);
