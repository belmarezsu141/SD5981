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
class VCOILOLockRange: public TestClass {


public:

	STRING                          mHiLink16_MacroList;
	STRING 							mPinList;
	INT                             iCSSlice;
	INT                             iKa;
	INT                             iKb;
	INT                             iNDiv_start;
	INT                             iNDiv_stop;
	INT                             iRefclkBus;
	INT                             iWDiv;
	INT								iPrintLvl;

	/**
	 *Initialize the parameter interface to the testflow.
	 *This method is called just once after a testsuite is created.
	 */
	void init()
	{
		add_param("H16LR_MacroList","string",&mHiLink16_MacroList)
					 .set_comment("HiLink16 Macro List for test")
					 .set_default("0");
//		add_param("PinList","PinString",&mPinList);
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
		add_param("N_Min","int",&iNDiv_start)
					 //.set_options("48:46")
					 .set_default("48");
		add_param("N_Max","int",&iNDiv_stop)
					 //.set_options("48:46")
					 .set_default("48");
		add_param("W_Div","int",&iWDiv)
					 //.set_options("1:2")
					 .set_default("1");
		add_param("PrintLvl[0~15]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 10000(16)"
							     "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYE_PLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.set_options("0:1:3:4:7:9")
					 .set_default("3");
	}
	////////////////////////////////////////////////////////////////////////////////
	// TM Purpose:                                                                //
	// This TM is go through defined N divider value to measure the VCO and ILO   //
	// lock range at these points, and if there is hole in the lock range, it     //
	// also log out.                                                              //
	//                                                                            //
	// Parameters:																  //
	// 1. Ka: Define Ka divider value, either 2 or 3					          //
	// 2. N_start: start value of N divider for N sweep operation                 //
	// 3. N_stop: stop value of N divider for N sweep operation                   //
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

		static	MACRO_DOUBLE 		Fmin_VCO, Fmax_VCO, VCO_los_hole_num;
		static	LANE_DOUBLE 		Fmin_ILO, Fmax_ILO, ILO_los_hole_num;


		//=============================================
		// Variables and MacroLane initialization
		//=============================================
		iOffline = 0;
		sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

		CUSTpara.initial();
		CUSTpara.CSslice = iCSSlice;
		CUSTpara.SSCGen_EN = false;
		CUSTpara.RateMode = 0;
		CUSTpara.DataWidth = 1;
		CUSTpara.FIR_setting = "DEFAULT_SETTING";
		CUSTpara.CTLE_setting = "DEFAULT_SETTING";
		CUSTpara.TxDrvResSel = 2;							/***********TXTDRVRES: 1 == 50 ohm; 2 == 45 ohm **************/
		CUSTpara.RxTermResSel = 1;							/***********RXTERMRES: 0 == 50 ohm; 1 == 45 ohm **************/
		CUSTpara.TxRegDrvLvl = 3;
		CUSTpara.RxCapBypass = 0; 							/*****0 = AC   1 = DC*******/
		CUSTpara.SSCDR_EN = false;
		CUSTpara.Protocol = "COMMON";

		SSpara.initial();
		SSpara.Refclk = 156.25;
		SSpara.RefclkBus = iRefclkBus;
		SSpara.SDiv = 1;

		CSpara.initial();
		CSpara.Mdiv = 1;
		CSpara.KaDiv = iKa;
		CSpara.KbDiv = iKb;
		CSpara.WDiv = iWDiv;
		if (2 == CSpara.KbDiv) {
			CSpara.JDiv = 20;
		} else {
			CSpara.JDiv = 10;
		}

		//=============================================
		// Variables definition and initialization
		//=============================================
		/********************init variable for calc result*******************/
		MACRO_ARRAY_D 				VCOResult;
		LANE_ARRAY_D 				ILOResult;
		INT 						NDivNum = iNDiv_stop - iNDiv_start + 1;
		VCOResult.init(NDivNum,0);
		ILOResult.init(NDivNum,0);

		//=============================================
		// Loop VCO configuration at certain Ka
		//=============================================
		for (INT NDivIndex = 0; NDivIndex < NDivNum; NDivIndex ++)
		{
			CSpara.NDiv = iNDiv_start + NDivIndex;
			hout(GENERAL) << dec << "NDivIndex = " << NDivIndex << " N = "<< CSpara.NDiv << endl;
			if (!CUSTpara.SSCGen_EN){
				if (CSpara.NDiv < 48){
					if (CSpara.NDiv % 3 == 0){
						CSpara.PDiv = (INT)((CSpara.NDiv - 3) / 3);
					}else{
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


			SITE_PASSFAIL_RESULT	CalResult;
			INT 					count = 0;
			const INT 				count_limit = 1;
			MACRO_INT 				CS_Cal_MacroResult;
			MACRO_INT 				DS_Cal_MacroResult;
			LANE_INT 				DS_Cal_LaneResult;
			STRING					sCalibrationType = "VCOILO";

			while (count < count_limit && (false == CalResult.isAllSitePassed())) {
				CalResult = HiLink16_FW_CAL(MacroLane_Sel, CUSTpara, SSpara, CSpara, CS_Cal_MacroResult, DS_Cal_MacroResult, DS_Cal_LaneResult, sCalibrationType);
				count ++;
			}
			//=============================================
			// check Result
			//=============================================

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					VCOResult[SiteID][MacroID][NDivIndex] = (double)CS_Cal_MacroResult[SiteID][MacroID];
					hout(DETAIL) << "Macro = " << MacroID << " NDivIndex = " << dec << NDivIndex << " VCOResult = " << VCOResult[SiteID][MacroID][NDivIndex] << endl;
					if (sCalibrationType == "VCOILO") {
						for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
							UINT LaneID = vLane[laneIndex];
							ILOResult[SiteID][MacroID][LaneID][NDivIndex] = DS_Cal_LaneResult[SiteID][MacroID][LaneID];
							hout(DETAIL) << "Macro = " << MacroID << " Lane " << LaneID << " NDivIndex = " << NDivIndex << " ILOResult = " << ILOResult[SiteID][MacroID][LaneID][NDivIndex] << endl;
						}
					}
				}
			FOREACH_ACTIVESITE_END
		}


		Fmin_VCO.init(9999);
		Fmax_VCO.init(-1);
		VCO_los_hole_num.init(9999);

		Fmin_ILO.init(9999);
		Fmax_ILO.init(-1);
		ILO_los_hole_num.init(9999);


		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

				ostringstream 			plot_VCO_hole;
				plot_VCO_hole << "======== " << sTestsuiteName << " VCO_ILO_hole_plot ========\n";
				INT 					ivco_first_lock = -1, ivco_last_lock = -1;

				for (INT NDivIndex = 0; NDivIndex < NDivNum; NDivIndex ++) {
					if (VCOResult[SiteID][MacroID][NDivIndex] == 1 && ivco_first_lock == -1) {
						ivco_first_lock = NDivIndex;
					}
					if (VCOResult[SiteID][MacroID][NDivIndex] == 1 && (NDivIndex > ivco_last_lock)) {
						ivco_last_lock = NDivIndex;
					}
				}

				if (ivco_first_lock == -1) {
					Fmin_VCO[SiteID][MacroID] = -999;
				} else {
					Fmin_VCO[SiteID][MacroID] = calculate_clocks(iKa,iKb,10,1,iNDiv_start + ivco_first_lock,156.25) / 1000;
				}
				if (ivco_last_lock == -1) {
					Fmax_VCO[SiteID][MacroID] = 999;
				} else {
					Fmax_VCO[SiteID][MacroID] = calculate_clocks(iKa,iKb,10,1,iNDiv_start + ivco_last_lock,156.25) / 1000;
				}


				hout(GENERAL) << "Macro[" << MacroID
							 << "], [Fmin_VCO,Fmax_VCO] = [" << Fmin_VCO[SiteID][MacroID] << "," << Fmax_VCO[SiteID][MacroID]
							 << "]MHz, N range = [" << iNDiv_start + ivco_first_lock  << "," << iNDiv_start + ivco_last_lock << "]" << endl;


				plot_VCO_hole << "VCO_LOCK_point: Macro_" << MacroID << " Frist_lock_N = " << iNDiv_start + ivco_first_lock << " Last_lock_N = "
							  << iNDiv_start + ivco_last_lock << "\t";
				VCO_los_hole_num[SiteID][MacroID] = 0;


				for (INT NDivIndex = 0; NDivIndex < NDivNum; NDivIndex ++) {
					if (VCOResult[SiteID][MacroID][NDivIndex] == 0) {
						if (NDivIndex > ivco_first_lock && NDivIndex < ivco_last_lock) {
							VCO_los_hole_num[SiteID][MacroID] ++;
						}
						plot_VCO_hole << "X ";
					} else
						plot_VCO_hole << "L ";
				}

//				PUT_DATALOG(plot_VCO_hole.str());

				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
					UINT LaneID = vLane[laneIndex];
					ostringstream 			plot_ILO_hole;
					plot_ILO_hole << "======== " << sTestsuiteName << " VCO_ILO_hole_plot ========\n";
					INT 					iilo_first_lock = -1, iilo_last_lock = -1;

					for (INT NDivIndex = 0; NDivIndex < NDivNum; NDivIndex ++) {
						if (ILOResult[SiteID][MacroID][LaneID][NDivIndex] == 1 && iilo_first_lock == -1) {
							iilo_first_lock = NDivIndex;
						}
						if (ILOResult[SiteID][MacroID][LaneID][NDivIndex] == 1 && (NDivIndex > iilo_last_lock)) {
							iilo_last_lock = NDivIndex;
						}
					}
					if (iilo_first_lock == -1) {
						Fmin_ILO[SiteID][MacroID][LaneID] = -999;
					} else {
						Fmin_ILO[SiteID][MacroID][LaneID] = calculate_clocks(iKa,iKb,10,1,iNDiv_start + iilo_first_lock,156.25) / 1000 / iKa / iKb;
					}
					if (iilo_last_lock == -1) {
						Fmax_ILO[SiteID][MacroID][LaneID] = 999;
					} else {
						Fmax_ILO[SiteID][MacroID][LaneID] = calculate_clocks(iKa,iKb,10,1,iNDiv_start + iilo_last_lock,156.25) / 1000 / iKa / iKb;
					}

					hout(GENERAL) << "Macro " << MacroID << " Lane " << laneIndex
								  << ", [Fmin_ILO,Fmax_ILO] = [" << Fmin_ILO[SiteID][MacroID][LaneID]
								  << "," << Fmax_ILO[SiteID][MacroID][LaneID]
								  << "]MHz, N range = [" << iNDiv_start + iilo_first_lock << "," << iNDiv_start + iilo_last_lock << "]" << endl;

					//calculate hole
					plot_ILO_hole << "ILO_LOCK_point: Macro_" << MacroID << "_Lane_" << laneIndex << " First_lock_N = "
								  << iNDiv_start + iilo_first_lock << " Last_lock_N = " << iNDiv_start + iilo_last_lock << "\t";
					ILO_los_hole_num[SiteID][MacroID][LaneID] = 0;

					for (INT NDivIndex = 0; NDivIndex < NDivNum; NDivIndex ++) {
						if (ILOResult[SiteID][MacroID][LaneID][NDivIndex] == 0) {
							if (NDivIndex > iilo_first_lock && NDivIndex < iilo_last_lock)  {
								ILO_los_hole_num[SiteID][MacroID][LaneID] ++;
							}
							plot_ILO_hole << "X ";
						} else {
							plot_ILO_hole << "L ";
						}
					}

//					PUT_DATALOG(plot_ILO_hole.str());
				}
			}
		FOREACH_ACTIVESITE_END


		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerMacro_Judge(MacroLane_Sel, "VCO_Fmin", Fmin_VCO);
//		HiLink_PerMacro_Judge(MacroLane_Sel, "VCO_Fmax", Fmax_VCO);
//		HiLink_PerMacro_Judge(MacroLane_Sel, "VCO_Los_Hole_Num", VCO_los_hole_num);
//		HiLink_PerLane_Judge(MacroLane_Sel,  "ILO_Fmin", Fmin_ILO);
//		HiLink_PerLane_Judge(MacroLane_Sel,  "ILO_Fmax", Fmax_ILO);
//		HiLink_PerLane_Judge(MacroLane_Sel,  "ILO_Los_Hole_Num", ILO_los_hole_num);

		return;
	}

};
REGISTER_TESTCLASS("VCOILOLockRange", VCOILOLockRange);
