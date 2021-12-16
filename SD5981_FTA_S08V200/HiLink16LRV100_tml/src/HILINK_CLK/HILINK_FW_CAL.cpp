//for test method API interfaces
//#include "sstream"
//#include "mapi.hpp"
//using namespace std;
#include <HILINK_PUG/HiLink16_PUG.h>

/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class HILINK_FW_CAL: public TestClass {

public:
	STRING                          mHiLink16_MacroList;
	STRING 							mPinList;
	DOUBLE                          dRefCLK_MHz;
	INT                             iRefclkBus;;
	INT                             iCSSlice;
	INT                             iKa;
	INT                             iKb;
	INT                             iPDiv;
	INT                             iSDiv;
	INT                             iWDiv;
	INT                             iJDiv;
	INT                             iMDiv;
	INT                             iSDiv_SS;
	INT   							iSSCGen_EN;
	STRING                       	sRateMode;
	STRING                          sDataWidth;
	STRING 							sTxDrvResSel;
	STRING 							sRxTermResSel;
	INT   							iTxRegDrvLvl;
	STRING							sFIR_setting;
	STRING							sFIRTAP;
	STRING							sCTLE_setting;
	STRING							sCTLEGAIN;
	STRING							sCTLEBOOST;
	STRING							sCTLECMBAND;
	STRING							sCTLERMBAND;
	STRING							sCTLEZA;
	STRING							sCTLESQH;
	STRING 							sRxCapBypass;
	INT   							iSSCDR_EN;
	STRING 							sProtocol;
	STRING                          sTxRelayState;
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
//		add_param("PinList","PinString",&mPinList);
		add_param("Refclk_MHz","double",&dRefCLK_MHz)
					 .set_comment("RefCLK_MHz")
					 //.set_options("100:156.25")
					 .set_default("100");
		add_param("RefclkBus","int",&iRefclkBus)
					 //.set_options("0:1")
					 .set_default("0");
		add_param("CS_Number","int",&iCSSlice)
					 .set_comment("mCSSlice")
					 //.set_options("0:1")
					 .set_default("0");
		add_param("Ka","int",&iKa)
					 //.set_options("2:3")
					 .set_default("2");
		add_param("Kb","int",&iKb)
					 //.set_options("1:2")
					 .set_default("1");
		add_param("FBDIV_P","int",&iPDiv)
					 //.set_options("13:14:16:17:21:22")
					 .set_default("21");
		add_param("FBDIV_S","int",&iSDiv)
					 //.set_options("9:11:13:15")
					 .set_default("15");
		add_param("W_Div","int",&iWDiv)
					 //.set_options("1:2")
					 .set_default("1");
		add_param("J_Div","int",&iJDiv)
					 //.set_options("20:10:16:8")
					 .set_default("10");
		add_param("M_Div","int",&iMDiv)
					 //.set_options("1:2")
					 .set_default("1");
		add_param("S_Div","int",&iSDiv_SS)
					 //.set_options("1:2")
					 .set_default("1");
		add_param("SSCGen_EN","int",&iSSCGen_EN)
					 //.set_options("0:1")
					 .set_default("0");
		add_param("DataWidth","string",&sDataWidth)
					 //.set_options("0[16bit]:1[20bit]:2[32bit]:3[40bit]")
					 .set_default("0[16bit]");
		add_param("RateMode","string",&sRateMode)
					 //.set_options("0[Full]:1[Half]:2[Quarter]:3[Octal]")
					 .set_default("0[Full]");
		add_param("TXDRV_RESSEL","string",&sTxDrvResSel)
					 //.set_options("1[50ohm]:3[45ohm]")
					 .set_default("2[45ohm]");
		add_param("RXTERM_RESSEL","string",&sRxTermResSel)
					 //.set_options("0[50ohm]:1[45ohm]")
					 .set_default("1[45ohm]");
		add_param("TXREGDRVLVL","int",&iTxRegDrvLvl)
					 //.set_options("0:1:2:3:4:5:6:7")
					 .set_default("3");
		add_param("FIR_setting","string",&sFIR_setting)
					 //.set_options("DEFAULT_SETTING:USER_SETTING")
					 .set_default("DEFAULT_SETTING");
//		add_param("FIR_Tap","string",&sFIRTAP)
//					 .set_options("0,0,63,0,0")
//					 .set_default("0,0,63,0,0");
		add_param("CTLE_setting","string",&sCTLE_setting)
					 //.set_options("DEFAULT_SETTING:USER_SETTING")
					 .set_default("DEFAULT_SETTING");
//		add_param("CTLEGAIN[0~7]","string",&sCTLEGAIN)
//					 //.set_options("3,3,3:4,4,4:5,5,5:7,7,7")
//					 .set_default("5,5,5");
//		add_param("CTLEBOOST[0~7]","string",&sCTLEBOOST)
//					 //.set_options("0,0,0:1,1,1:2,2,2")
//					 .set_default("0,0,0");
//		add_param("CTLECMBAND[0~2]","string",&sCTLECMBAND)
//					 //.set_options("0,0,0:1,1,1:2,2,2")
//					 .set_default("0,0,0");
//		add_param("CTLERMBAND[0~2]","string",&sCTLERMBAND)
//					 //.set_options("0,0,0:1,1,1:2,2,2")
//					 .set_default("0,0,0");
//		add_param("CTLEZA[0~2]","string",&sCTLEZA)
//					 //.set_options("0,0,0:1,1,1:2,2,2")
//					 .set_default("0,0,0");
//		add_param("CTLESQH[0~2]","string",&sCTLESQH)
//					 //.set_options("0,0,0:1,1,1:2,2,2")
//					 .set_default("0,0,0");
		add_param("Couple_Mode","string",&sRxCapBypass)
					 .set_comment("0 is AC couple ,1 is DC couple")
					 //.set_options("0[AC_Couple]:1[DC_Couple]")
					 .set_default("1[DC_Couple]");
		add_param("SSCDR_EN","int",&iSSCDR_EN)
					 //.set_options("0:1")
					 .set_default("0");
		add_param("Protocol_Mode","string",&sProtocol)
					 .set_comment("the Protocol mode of Firmware calibration in the DsConfigurationAfterCalibration")
					 //.set_options("PCIE:SATA:SAS:COMMON")
					 .set_default("COMMON");
//		add_param("TxRly_State","string",&sTxRelayState)
					 //.set_options("TESTER:ONBOARD_TERM")
//					 .set_default("ONBOARD_TERM");
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

		static	MACRO_DOUBLE 		CS_Result;
		static	MACRO_DOUBLE 		DS_Result;


			//=============================================
			// Variables and MacroLane initialization
			//=============================================
			iOffline = 0;
			sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
			hout.setLevel(iPrintLvl);
			hout.printsuitename(sTestsuiteName);
			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);


			INT					iRateMode = sRateMode[0] - '0';
			INT					iDataWidth = sDataWidth[0] - '0';
			INT					iTxDrvResSel = sTxDrvResSel[0] - '0';
			INT					iRxTermResSel = sRxTermResSel[0] - '0';
			INT					iRxCapBypass = sRxCapBypass[0] - '0';

			TxFIR_SETTING 		TxFIR_USER = {0,0,63,0,0};
			INT_VECTOR			FIRTAP;
			if (sFIR_setting == "USER_SETTING") {
				parseListOfInt(sFIRTAP, FIRTAP, ',');
				TxFIR_USER.iTxPre2nd = FIRTAP[0];
				TxFIR_USER.iTxPre1st = FIRTAP[1];
				TxFIR_USER.iTxMain = FIRTAP[2];
				TxFIR_USER.iTxPost1st = FIRTAP[3];
				TxFIR_USER.iTxPost2nd = FIRTAP[4];
				/**************** sum of FIR value should not > 63 ***************/
				if ((abs(TxFIR_USER.iTxPre2nd) + abs(TxFIR_USER.iTxPre1st) + abs(TxFIR_USER.iTxMain)
				  + abs(TxFIR_USER.iTxPost1st) + abs(TxFIR_USER.iTxPost2nd)) > 63) {
					hout(RELEASE) << "Error: Sum of Five Taps abs value should not > 63, please enter again!!!!!!" << endl;
					_exit(0);
				}
			}

			INT_VECTOR			CTLEGAIN, CTLEBOOST ,CTLECMBAND, CTLERMBAND, CTLEZA, CTLESQH;
			RxCTLE_SETTING		RxCTLE_USER = {
					{5,5,5},
					{0,0,0},
					{0,0,0},
					{0,0,0},
					{0,0,0},
					{0,0,0}
			};
			if (sCTLE_setting == "USER_SETTING") {
				parseListOfInt(sCTLEGAIN, CTLEGAIN, ',');
				parseListOfInt(sCTLEBOOST, CTLEBOOST, ',');
				parseListOfInt(sCTLECMBAND, CTLECMBAND, ',');
				parseListOfInt(sCTLERMBAND, CTLERMBAND, ',');
				parseListOfInt(sCTLEZA, CTLEZA, ',');
				parseListOfInt(sCTLESQH, CTLESQH, ',');
				for (INT i = 0; i < 3; i ++) {
					RxCTLE_USER.Gain[i] = CTLEGAIN[i];
					RxCTLE_USER.Boost[i] = CTLEBOOST[i];
					RxCTLE_USER.CMBand[i] = CTLECMBAND[i];
					RxCTLE_USER.RMBand[i] = CTLERMBAND[i];
					RxCTLE_USER.ZA[i] = CTLEZA[i];
					RxCTLE_USER.SQH[i] = CTLESQH[i];
				}
			}

			CUSTpara.initial();
			CUSTpara.CSslice = iCSSlice;
			CUSTpara.SSCGen_EN = iSSCGen_EN;
			CUSTpara.RateMode = iRateMode;
			CUSTpara.DataWidth = iDataWidth;
			CUSTpara.TxDrvResSel = iTxDrvResSel;				/***********TXTDRVRES: 1 == 50 ohm; 2 == 45 ohm **************/
			CUSTpara.RxTermResSel = iRxTermResSel;				/***********RXTERMRES: 0 == 50 ohm; 1 == 45 ohm **************/
			CUSTpara.TxRegDrvLvl = iTxRegDrvLvl;
			CUSTpara.FIR_setting = sFIR_setting;
			CUSTpara.TxFIR_USER = TxFIR_USER;
			CUSTpara.CTLE_setting = sCTLE_setting;
			CUSTpara.RxCTLE_USER = RxCTLE_USER;
			CUSTpara.RxCapBypass = iRxCapBypass; 				/*****0 = AC   1 = DC*******/
			CUSTpara.Protocol = sProtocol;
			CUSTpara.SSCDR_EN = iSSCDR_EN;

			SSpara.initial();
			SSpara.Refclk = dRefCLK_MHz;
			SSpara.RefclkBus = iRefclkBus;
			SSpara.SDiv = iSDiv_SS;									/****If Refclk >350MHz, SDiv = 1******/

			CSpara.initial();
			CSpara.Mdiv = iMDiv;
			CSpara.KaDiv = iKa;
			CSpara.KbDiv = iKb;
			CSpara.PDiv = iPDiv;
			CSpara.SDiv = iSDiv;
			CSpara.WDiv = iWDiv;
			CSpara.JDiv = iJDiv;
			CSpara.NDiv = CSpara.SDiv + 3 + 2 * CSpara.PDiv;
			/*************Calc P&S by N**************
			if (!CUSTpara.SSCGen_EN){
				if (CSpara.NDiv < 48){
					if (CSpara.NDiv % 3 == 0){
						CSpara.PDiv = (INT)((CSpara.NDiv - 3) / 3);
					}else{Standardd_inedx
						CSpara.PDiv = (INT)((CSpara.NDiv - 3) / 3) + 1;
					}
				}else{
					if (CSpara.NDiv % 2 == 1){
						CSpara.PDiv = (CSpara.NDiv - 14 -3) / 2;
					}else{
						CSpara.PDiv = (CSpara.NDiv - 15 -3) / 2;
					}
				}
			}else{
				if (CSpara.NDiv < 48){
					if (CSpara.NDiv % 3 == 0){
						CSpara.PDiv = (INT)((CSpara.NDiv - 3) / 3) + 1;
					}else{
						CSpara.PDiv = (INT)((CSpara.NDiv - 3) / 3) + 2;
					}
				}else{
					if (CSpara.NDiv % 2 == 1){
						CSpara.PDiv = (CSpara.NDiv - 12 -3) / 2;
					}else{
						CSpara.PDiv = (CSpara.NDiv - 13 -3) / 2;
					}
				}
			}
			CSpara.SDiv = CSpara.NDiv - 3 - 2 * CSpara.PDiv;
			*************************************************/

			if (CP_FT_Program == "FT") {
				/***connect To Board Term to ensure Tx cal trim value is correct***/
				if (TXUTI != "") {
					Relay_Control("ONBOARD_TERM");
				}
				/***Open AC relay to ensure Rx cal trim value is correct***/
//				FLEX_RELAY 			frelay;
//				frelay.pin("pHilink16_TX,pHilink16_RX").set("IDLE","OFF");
//				frelay.execute();
//				frelay.wait(0.3 ms);
			}

			SITE_PASSFAIL_RESULT 	CalResult;
			INT 					count = 0;
			const INT 				count_limit = 1;
			MACRO_INT 				CS_Cal_MacroResult;
			MACRO_INT 				DS_Cal_MacroResult;
			LANE_INT 				DS_Cal_LaneResult;

			FWreadDefaultRegisters2CSR_RefCLKLockRange(MacroLane_Sel, iCSSlice);

			while (count < count_limit && (false == CalResult.isAllSitePassed())) {
				CalResult = HiLink16_FW_CAL(MacroLane_Sel, CUSTpara, SSpara, CSpara, CS_Cal_MacroResult, DS_Cal_MacroResult, DS_Cal_LaneResult);
				count ++;
			}

			if (TXUTI != "" && CP_FT_Program == "FT") {
				Relay_Control(sTxRelayState);
			}

			/*************** New Judge For Optimize STDF***************/
			CS_Result.init(0);
			DS_Result.init(0);

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					INT 				laneSize = HILINK_INFO[MacroID].Lane_Num;
					INT  				HiLink_Macro_CsNum;

					if (HILINK_INFO[MacroID].CS0_Type != NOTEXIST && HILINK_INFO[MacroID].CS1_Type != NOTEXIST) {
						HiLink_Macro_CsNum = 2;
					} else {
						HiLink_Macro_CsNum = 1;
					}

					if (CS_Cal_MacroResult[SiteID][MacroID]) {
						CS_Result[SiteID][MacroID] = iCSSlice ? 1 : 10;
					}
					CS_Result[SiteID][MacroID] = CS_Cal_MacroResult[SiteID][MacroID] * 100000 + HiLink_Macro_CsNum * 10000 + MacroID + CS_Result[SiteID][MacroID] / 100;


					DOUBLE	ShiftIndex1 = 1.0;
					DOUBLE	ShiftIndex2 = 1.0;
					if ((laneSize >= 1) && (laneSize <= 3)) {
						ShiftIndex1 = 10;
						ShiftIndex2 = 10000;
					} else if ((laneSize >= 4) && (laneSize <= 6)) {
						ShiftIndex1 = 100;
						ShiftIndex2 = 10000;
					} else if ((laneSize >= 7) && (laneSize <= 9)) {
						ShiftIndex1 = 1000;
						ShiftIndex2 = 10000;
					} else if ((laneSize >= 10) && (laneSize <= 13)) {
						ShiftIndex1 = 10000;
						ShiftIndex2 = 100000;
					} else {
						ShiftIndex1 = 100000;
						ShiftIndex2 = 100000;
					}

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						DS_Result[SiteID][MacroID] = DS_Result[SiteID][MacroID] + DS_Cal_LaneResult[SiteID][MacroID][LaneID] * pow(2.0, (INT)LaneID);
					}

					DS_Result[SiteID][MacroID] = DS_Cal_MacroResult[SiteID][MacroID] * 100000 + laneSize * ShiftIndex2 + DS_Result[SiteID][MacroID] / ShiftIndex1 + MacroID;
				}
			FOREACH_ACTIVESITE_END


		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerMacro_Judge(MacroLane_Sel, "CS_Cal_Done_PerMacro", CS_Result);
//		HiLink_PerMacro_Judge(MacroLane_Sel, "DS_Cal_Done_PerMacro", DS_Result);

		return;
		}

};
REGISTER_TESTCLASS("HILINK_FW_CAL", HILINK_FW_CAL);
