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
class RxCTLETol_ABIST: public TestClass {

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
	// This TM is to record the maximum Tx FIR pre1st/post1st value, with which   //
	// there is no error count by reading register in internal loopback mode.     //
	// The Tx FIR pre1st/post1st increase step by step from 0 to 15.              //
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

		static	LANE_DOUBLE 		MinCTLE;


			//=============================================
			// Variables and MacroLane initialization
			//=============================================
			iOffline = 0;
			sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
			hout.setLevel(iPrintLvl);
			hout.printsuitename(sTestsuiteName);
			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);


			TxFIR_SETTING 		FIR_ORI;
			GetTxFIR(FIR_ORI);

			TxFIR_SETTING		FIR = {0,0,45,0,0};

			//=============================================
			// Device Setup
			//=============================================
			d2s_JTAG& jtag = d2s_JTAG::Instance();

			sprintf(label,"H16LRTV100_MPB_CTLETOL_ABIST_SETUP_RateMode%d_DataWidth%d",CUSTpara.RateMode,CUSTpara.DataWidth);
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
			LANE_INT 				FindFlag;
			MinCTLE.init(9999);
			FindFlag.init(0);

			INT 					pre1_post1 = -3;
			INT iFind_All = 0;
			while (pre1_post1 <= 15 && ((iFind_All == 0) || (Global_D2S_Mode == LearningMode)))
			{
				//todo:call d2s_begin_end_block template and setup for each step
				FIR.iTxMain = 40;
				FIR.iTxPre1st = pre1_post1;
				FIR.iTxPost1st = pre1_post1;
				if ((abs(FIR.iTxPre2nd) + abs(FIR.iTxPre1st) + abs(FIR.iTxMain)
				  + abs(FIR.iTxPost1st) + abs(FIR.iTxPost2nd)) > 63) {
					FIR.iTxMain = 63 - abs(FIR.iTxPre1st) - abs(FIR.iTxPost1st);
				}
				d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_CTLETOL",Global_D2S_Mode);

					selectMacro_MB(MacroLane_Sel);
					DS.Broadcast();

					SetTxFir(FIR);
					jtag.wait(40 *0.000001);

				d2s::d2s_LABEL_END();
				//todo:print spec value for each step
				hout(DETAIL) << "========== pre1st/post1st = " << dec << pre1_post1 << " ==========" << endl;

				//todo:call sub func ReadBert_ExpectValue()
				ReadBert_ExpectValue(MacroLane_Sel, PRBS15, ErrorCount);

				//todo:Other method for debugging delete this todo bolck if not use
				//demo:
				if (hout.IsEyePlotEn()) {
					hout(DETAIL) << "========= DataRate = " << dec << CUSTpara.Data_Rate << " ==========" << endl;
					GetEyeDiagram(MacroLane_Sel, CUSTpara.Data_Rate);
				}

				//todo:call sub func Update_LaneData_InTolerance()
				iFind_All = Update_LaneData_InTolerance(MacroLane_Sel, pre1_post1, ErrorCount, MinCTLE, FindFlag);

				//todo:update spec here
				pre1_post1 += 3;
			}

			/****restore FIR************/
			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_RXSWINGTOL_ABIST_RESTORE",Global_D2S_Mode);

				selectMacro_MB(MacroLane_Sel);
				DS.Broadcast();

				SetTxFir(FIR_ORI);
				jtag.wait(40 *0.000001);

			d2s::d2s_LABEL_END();


		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "EQI", MinCTLE);

		return;
	}

};
REGISTER_TESTCLASS("RxCTLETol_ABIST", RxCTLETol_ABIST);
