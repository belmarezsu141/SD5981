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
class RefclkLockRange: public TestClass {

public:
        STRING                          mHiLink16_MacroList;
    	STRING 							mPinList;
        STRING                          sRefCLK_MHz;
        INT                             iCSSlice;
        STRING                          sNDiv;
        INT                             iRefclkBus;
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
		add_param("RefclkBus","int",&iRefclkBus)
					 //.set_options("0:1")
					 .set_default("0");
		add_param("CS_Number","int",&iCSSlice)
					 .set_comment("mCSSlice")
					 //.set_options("0:1")
					 .set_default("0");
		add_param("PrintLvl[0~15]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 10000(16)"
							     "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYE_PLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.set_options("0:1:3:4:7:9")
					 .set_default("3");

	}
	////////////////////////////////////////////////////////////////////////////////
	// TM Purpose:                                                                //
	// This TM is test pre-defined refclk points, whether the VCO can lock at     //
	// certain refclk.                                                            //
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

	static	MACRO_ARRAY_I       		VCOResult;
	static	SITE_DOUBLE					Res;
	static	MACRO_DOUBLE				ResPerMacro;


		//=============================================
		// Variables and MacroLane initialization
		//=============================================
		iOffline = 0;
		sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

		/******  Global Calibration variable initial ************/
		CUSTpara.initial();
		CUSTpara.CSslice = iCSSlice;
		CUSTpara.SSCGen_EN = false;
		CUSTpara.RateMode = 0;

		SSpara.initial();
		SSpara.RefclkBus = iRefclkBus;
		SSpara.SDiv = 1;

		CSpara.initial();
		CSpara.KaDiv = 3;
		CSpara.KbDiv = 1;
		CSpara.WDiv = 1;
		if (2 == CSpara.KbDiv) {
			CSpara.JDiv = 20;
		} else {
			CSpara.JDiv = 10;
		}

		sRefCLK_MHz = "75,100,125,156.25";
//			sRefCLK_MHz = "75,100,125,156.25,250,312.5";
//			sRefCLK_MHz = "75";
		UINT MacroID = MacroLane_Sel[0].MacroID;
		if (0 == CUSTpara.CSslice) {
			if (CSL == HILINK_INFO[MacroID].CS0_Type) {
				sNDiv = "56,42,34,27,17,13";
//					sNDiv = "56";
			} else if (CSH == HILINK_INFO[MacroID].CS0_Type) {
				sNDiv = "71,53,42,34,21,17";
			} else {
				_exit(0);
				hout (RELEASE) << "CS0 not exist!! please input correct CS_Number!!" << endl;
			}
		} else if (1 == CUSTpara.CSslice) {
			if (CSL == HILINK_INFO[MacroID].CS1_Type) {
				sNDiv = "56,42,34,27,17,13";
			} else if (CSH == HILINK_INFO[MacroID].CS1_Type) {
				sNDiv = "71,53,42,34,21,17";
			} else {
				_exit(0);
				hout (RELEASE) << "CS1 not exist!! please input correct CS_Number!!" << endl;
			}
		} else {
			_exit(0);
			hout (RELEASE) << "please input correct CS_Number!!" << endl;
		}
		DOUBLE_VECTOR 					vRefCLK_MHz;
		INT_VECTOR                      vNDiv;
		parseListOfDouble(sRefCLK_MHz,vRefCLK_MHz,',');
		parseListOfInt(sNDiv,vNDiv,',');
		INT								refCLKNum = vRefCLK_MHz.size();

		vector<SITE_PASSFAIL_RESULT>		vResult_PerIndex;
		for (INT refIndex = 0; refIndex < refCLKNum; refIndex++) {
			SITE_PASSFAIL_RESULT	tmp;
			vResult_PerIndex.push_back(tmp);
		}

		VCOResult.init(refCLKNum,0);

		STRING 			mPort = "pPCM_BYPASS_REF";
		STRING 			mSpec = "Frefclk";
		DOUBLE 			dOrgVal;
		STRING 			sSpecName, sSpecSetName;
		sSpecName = mSpec + "@" + mPort;
//		dOrgVal = Primary.getSpecification().getSpecValue(sSpecName);
//		sSpecSetName = Primary.getSpecification().getName();

		d2s_JTAG& jtag = d2s_JTAG::Instance();
		//=============================================
		// Device Setup
		//=============================================

		for (INT refIndex = 0; refIndex < refCLKNum; refIndex++) {
//			try {
//				Primary.getSpecification().change(sSpecName,vRefCLK_MHz[refIndex]);
////					Primary.getSpecification().change("Frequency@pCLKIn",vRefCLK_MHz[refIndex]);
//				FLUSH(TM::APRM);
//			} catch (Error &error) {
//				Primary.getSpecification().change(sSpecName, dOrgVal);
//				FLUSH(TM::APRM);
//				ERROR_EXIT(TM::RETURN_TO_FLOW);
//			}
//
	        // change Timing
	        if (vRefCLK_MHz[refIndex] == 75) {

	            TheInst.Digital().Pattern().Start("HILINK_PCM_75M");

	        } else if (vRefCLK_MHz[refIndex] == 100) {

	            TheInst.Digital().Pattern().Start("HILINK_PCM_100M");

	        } else if (vRefCLK_MHz[refIndex] == 125) {

	            TheInst.Digital().Pattern().Start("HILINK_PCM_125M");

	        } else if (vRefCLK_MHz[refIndex] == 156.25) {

	            TheInst.Digital().Pattern().Start("HILINK_PCM_156M25");

	        } else {
	        	cout <<"ERROR: Incorrect Refclksel set!!! Please Check this parameter!!!"<<endl;
	        }

//			FW_TASK("APRM CNL;");
//			FW_TASK("FTCG SKPR,ON,(pPCM_BYPASS_REF)");

			SSpara.Refclk = vRefCLK_MHz[refIndex];
			if (SSpara.Refclk == 250 || SSpara.Refclk == 312.5)
			{
				CSpara.NDiv = 2 * vNDiv[refIndex];
				CSpara.Mdiv = 2;
			}
			else
			{
				CSpara.NDiv = vNDiv[refIndex];
				CSpara.Mdiv = 1;
			}

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

			hout(GENERAL) << "Current ref freq = " << dec << SSpara.Refclk << "MHz\tN = " << CSpara.NDiv << "\tM = " << CSpara.Mdiv << endl;

			HiLinkResetAndInit(DEFAULT_HILINK_INIT_VECTOR);

			d2s_JTAG& jtag = d2s_JTAG::Instance();

			if (Global_D2S_Mode == LearningMode){
				FWreadDefaultRegisters2CSR_RefCLKLockRange(MacroLane_Sel, iCSSlice);
			}

			INT 				count = 0;
			const INT 			count_limit = 1;
			MACRO_INT 			CS_Cal_MacroResult;
			MACRO_INT 			DS_Cal_MacroResult;
			LANE_INT 			DS_Cal_LaneResult;

			while (count < count_limit && (false == vResult_PerIndex[refIndex].isAllSitePassed())) {
				vResult_PerIndex[refIndex] = HiLink16_FW_CAL(MacroLane_Sel, CUSTpara, SSpara, CSpara, CS_Cal_MacroResult, DS_Cal_MacroResult, DS_Cal_LaneResult, "VCO");
				count ++;
			}

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					hout(DETAIL) << "Macro:" << MacroID << "\tCal result : " << CS_Cal_MacroResult[SiteID][MacroID] << endl;
					VCOResult[SiteID][MacroID][refIndex] = CS_Cal_MacroResult[SiteID][MacroID];
					if (VCOResult[SiteID][MacroID][refIndex])
						hout(DETAIL) << "PLL OUT OF LOCK!" << endl;
					else
						hout(DETAIL) << "PLL LOCKED!" << endl;
				}
			FOREACH_ACTIVESITE_END

//			FW_TASK("FTCG SKPR,OFF,(@@)");

		}

		//=============================================
		// Restore
		//=============================================
//		Primary.getSpecification().change(sSpecName,dOrgVal);
//		FLUSH();

		//=============================================
		// Datalog
		//=============================================

		ResPerMacro.init(0);
		Res.init(1);

		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				ResPerMacro[SiteID][MacroID] = 0.0;
				for (INT refIndex = 0; refIndex < refCLKNum; refIndex ++)
				{
					ResPerMacro[SiteID][MacroID] = ResPerMacro[SiteID][MacroID] + (double)VCOResult[SiteID][MacroID][refIndex] * pow(0.1,(refIndex + 1));
				}
				ResPerMacro[SiteID][MacroID] = ResPerMacro[SiteID][MacroID] + MacroID;
			}
		FOREACH_ACTIVESITE_END

		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (INT refIndex = 0; refIndex < refCLKNum; refIndex ++) {
				if (false == vResult_PerIndex[refIndex][SiteID]) {
					Res[SiteID] = 0;
				}
			}
		FOREACH_ACTIVESITE_END

	//=============================================
	// Datalog
	//=============================================
//	HiLink_PerSite_Judge(MacroLane_Sel, "RefclkLockRange_AllSlides", Res);
//	HiLink_PerMacro_DummyJudge(MacroLane_Sel, "RefclkLockRange_PerMacro", ResPerMacro);
	return;
	}

};
REGISTER_TESTCLASS("RefclkLockRange", RefclkLockRange);

















