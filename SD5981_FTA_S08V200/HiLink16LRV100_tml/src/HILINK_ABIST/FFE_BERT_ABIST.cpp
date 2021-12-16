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
class FFE_BERT_ABIST: public TestClass {
public:
	STRING 				mHiLink16_MacroList;
	STRING 				mPinList;
	STRING				mFirTap;
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
		add_param("FIR_Tap","string",&mFirTap);
					 //.set_options("Pre1st:Post1st");
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

		static	LANE_DOUBLE			ErrorCount;


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


			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_FFE_BERT_SETUP",Global_D2S_Mode);

				selectMacro_MB(MacroLane_Sel);
				DS.Broadcast();

				if (mLoopbackMode == "External" ) {
					DisableTxToRxSerLpbk();
				} else {
					EnableTxToRxSerLpbk(mLoopbackMode);
				}

				EnableTxPrbsGen(PRBS15);

				if (mFirTap == "Post1st") {
					DS.txRegs.settxfirpre2(0xf)
							 .settxfirpre1(0)
							 .Write2DUT(0);
					DS.txRegs.settxfirmain(0)
							 .settxfirpost1(0xf)
							 .settxfirpost2(0)
							 .Write2DUT(1);
				} else if (mFirTap == "Pre1st") {
					DS.txRegs.settxfirpre2(0)
							 .settxfirpre1(0xf)
							 .Write2DUT(0);
					DS.txRegs.settxfirmain(0)
							 .settxfirpost1(0)
							 .settxfirpost2(0xf)
							 .Write2DUT(1);
				} else {
					hout(RELEASE) << "Please select FirTap : Pre1st or Post1st!" << endl;
					_exit(0);
				}
				DS.txRegs.settxdrvf1sel(1).Write2DUT(12);
				DS.txRegs.settxdrvf2sel(1).Write2DUT(12);
				DS.txRegs.settxtappwrdb(0xFF).Write2DUT(10);

				DS.rxRegs.setcdrfreeze(0)
						 .Write2DUT(10);
				jtag.wait(20 *0.000001);

			d2s::d2s_LABEL_END();

			//=============================================
			//measurement
			//=============================================

			ReadBert_ExpectValue(MacroLane_Sel,PRBS15,ErrorCount);

			if (hout.IsEyePlotEn()) {
				GetEyeDiagram(MacroLane_Sel, CUSTpara.Data_Rate);
			}
			//=============================================
			//measurement
			//=============================================

		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "TxFFE_BERT_ErrCnt",ErrorCount);

		return;
	}

};
REGISTER_TESTCLASS("FFE_BERT_ABIST", FFE_BERT_ABIST);
