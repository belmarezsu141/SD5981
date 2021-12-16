
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
class SSC_BertPrbs15_ABIST: public TestClass {

public:
	STRING                          mHiLink16_MacroList;
	STRING 							mPinList;
	STRING							mLoopbackMode;
	INT								iPrintLvl;

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
	////////////////////////////////////////////////////////////////////////////////
	// TM Purpose:                                                                //
	// This TM is to check whether there is error count in different setup of     //
	// PRBS15 pattern under internal loopback mode. The test is performed with    //
	// the setups include different data rate and different bit width. And before //
	// do error check, it should verify internal PRBS checker first.              //
	//																			  //
	// Parameters:																  //
	// 1. Tx_main: setup Tx FIR main value										  //
	// 2. RateMode: setup Tx data rate mode, including FULL, HALF, QUAD and OCT   //
	// 3. DataWidth: setup Tx data width, including 16 bit, 20 bit, 32 bit and    //
	//               40 bit.                                                      //
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

		static	LANE_DOUBLE			ErrorCount;


			//=============================================
			// Variables and MacroLane initialization
			//=============================================
			iOffline = 0;
			sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
			hout.setLevel(iPrintLvl);
			hout.printsuitename(sTestsuiteName);
			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

			d2s_JTAG& jtag = d2s_JTAG::Instance();
			//=============================================
			// Device Setup
			//=============================================

			INT 				iDataWidth = DS.txRegs.gettxdwidth();
			INT 				iRateMode = DS.txRegs.gettxratemode();
			sprintf(label,"H16LRTV100_MPB_SSCBERTPRBS15_SETUP_RateMode%d_DataWidth%d",iRateMode,iDataWidth);
			d2s::d2s_LABEL_BEGIN(label, Global_D2S_Mode);

				selectMacro_MB(MacroLane_Sel);
				DS.Broadcast();

				if (mLoopbackMode == "External" ) {
					DisableTxToRxSerLpbk();
				} else {
					EnableTxToRxSerLpbk(mLoopbackMode);
				}

				EnableTxPrbsGen(PRBS15,true);

				DS.rxRegs.setcdrfreeze(0)
						 .Write2DUT(10);
				jtag.wait(20 *0.000001);

			d2s::d2s_LABEL_END();

			LANE_DOUBLE 		VerifyErrorCount;
			/*====================TX Bert Verify=========================*/
			AntiFool_ExpectValue(MacroLane_Sel, PRBS7, VerifyErrorCount);

			/*====================TX Bert Check==========================*/
			ReadBert_ExpectValue(MacroLane_Sel, PRBS15, ErrorCount, "ABIST", 10);

			if (hout.IsEyePlotEn()) {
				GetEyeDiagram(MacroLane_Sel, CUSTpara.Data_Rate);
			}

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						if (VerifyErrorCount[SiteID][MacroID][LaneID] == 0)
						{
							ErrorCount[SiteID][MacroID][LaneID] = -1;
						}
					}
				}
			FOREACH_ACTIVESITE_END



			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						if (iOffline) {
							ErrorCount[SiteID][MacroID][LaneID] = 0;
						}
					}
				}

			FOREACH_ACTIVESITE_END

		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "SSCBERT_ErrCnt", ErrorCount);

		return;
	}

};
REGISTER_TESTCLASS("SSC_BertPrbs15_ABIST", SSC_BertPrbs15_ABIST);
