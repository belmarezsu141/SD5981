//for test method API interfaces

#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"

using namespace std;

class RefclkLockRange: public TestClass{
#define PCM_COUNT 6
public:
	STRING                          mHiLink30_MacroList;
	STRING                          sRefCLK_MHz;
	STRING                          sRefCLK_MHz2;
	STRING                          sSpecifcation;
	INT                             iPll_Select;
	STRING                          sDataRate;
	STRING                          sKa;
	STRING                          sKb;
	STRING                          sNa;
	STRING                          sNb;
	STRING                          sMDiv;
    STRING                          sSdivder;
	STRING                         	sRateMode;
	INT                             iDataWidth;
	INT                             iHsClkDistClkSpare_Bit2;
	INT                             iJ_40b;
	INT                             iJ_32b;
	STRING 				            sHSCLK_GHz;
	STRING                          mCalibrationType;
	INT                             iRefclkBus;
	STRING 							sTXDRV_RESSEL;
	STRING 							sRXCAPBYPASS;

    STRING						    mClockSpec[PCM_COUNT];
	STRING 				            sCoupleMode;
    INT                             iPllMclkPreDiv;
    STRING                          sP;
    STRING                          sS;
    INT 							iPrintLvl;

	STRING                        	mPowerUpControlPattern;
	STRING                  		mInitPattern;
	STRING							mChronusPattern;
	void init(){
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					 .set_comment("HiLink30 Macro List for test")
					 //.set_options("0,1")
					 .set_default("0,1");
		add_param("Pll_Select","int",&iPll_Select)
					 .set_comment("iPll_Select")
					 //.set_options("0:1:-1")
					 .set_default("0");
		add_param("RefclkBus","int",&iRefclkBus)
					 //.set_options("0:1:-1")
					 .set_default("-1");
		add_param("PowerUpControlPattern","string",&mPowerUpControlPattern)
					 //.set_options("")
					 .set_default("");
		add_param("InitPattern","string",&mInitPattern)
					 //.set_options("")
					 .set_default("");

		 for(int i=0;i<PCM_COUNT;i++){
			ostringstream str;
			str<<"ClockSpec"<<i;
			add_param(str.str(),"string",&mClockSpec[i])
					//.set_options("Frequency@pCLKIn1:Frefclk@pHilink_CLK:Frefclk@pCLKIn:BYPASS")
				    .set_default("Frequency@pCLKIn1")
				    .set_comment("SpecName = Spec + \"@\" + Port;");
		 }

			add_param("PrintLvl","int",&iPrintLvl)
			.set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
					"0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					//.set_options("0:1:3:4:7:8")
					.set_default("3");
	}
	void execute(){

	    H30_FailBin_Flag.init(0);
	    //=============================================
	    // Common definition of TM for offline flag,
	    // d2s mode, debug mode, test suite name, etc.
	    //=============================================
	    INT iDebugAnalog;

	    static MACRO_LANE_SEL MacroLane_Sel;
	    static INT iCSR_check;

	    static std::vector<UINT> vPllId;
	    static map<UINT, MACRO_DOUBLE> Res_perMacro;
//	    STRING mChronusPattern;
//
//	    STRING sRefCLK_MHz;
//	    STRING sRefCLK_MHz2;
//	    STRING sSpecifcation;
//
//	    STRING sDataRate;
//	    STRING sKa;
//	    STRING sKb;
//	    STRING sNa;
//	    STRING sNb;
//	    STRING sMDiv;
//	    STRING sSdivder;
//	    STRING sRateMode;
//	    INT iDataWidth;
//	    INT iHsClkDistClkSpare_Bit2;
//	    INT iJ_40b;
//	    INT iJ_32b;
//	    STRING sHSCLK_GHz;
//	    STRING mCalibrationType;
//	    INT iRefclkBus;
//	    STRING sTXDRV_RESSEL;
//	    STRING sRXCAPBYPASS;
//	    STRING sCoupleMode;
//	    INT iPllMclkPreDiv;
//	    STRING sP;
//	    STRING sS;


	    //=============================================
	    // Variables definition and initialization
	    //=============================================
//	    const char * sTestsuiteName = api->Get_current_test_name();
	    string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
	    string strTestsuiteName = sTestsuiteName;
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();
//	    api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER, &m_TestNumber, THE_END);
	    //static stRefclkLockRange sRefclkLockRange = H30_RefclkLockRange_Refclk1_PLL_0_RefclkLockRange; //5875
	    static stRefclkLockRange sRefclkLockRange = H30LR_RefclkLockRange_PLL0_PLL1_Refclk0_M0x3_VDDN;
	    hout.printsuitename(sTestsuiteName);
	    Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList);
	    UINT macroNum = MacroLane_Sel.size();

	    DOUBLE_VECTOR vKa;
	    INT_VECTOR vKb;
	    INT_VECTOR vNa;
	    INT_VECTOR vNb;
	    INT_VECTOR vMDiv;
	    INT_VECTOR vSdivder;
	    INT_VECTOR vRateMode;
	    INT_VECTOR vDataWidth;
	    INT_VECTOR vJ32_b;
	    INT_VECTOR vJ40_b;
	    INT_VECTOR vPll_Select;
	    DOUBLE_VECTOR vHSCLK_GHz;
	    DOUBLE_VECTOR vRefCLK_MHz;
	    DOUBLE_VECTOR vRefCLK_MHz2;
	    DOUBLE_VECTOR vDataRate;
	    INT_VECTOR vRefclkBus;
	    INT_VECTOR vPllMclkPreDiv;
	    INT_VECTOR vP;
	    INT_VECTOR vS;
	    STRING_VECTOR vSpecifcation;


	    sDataRate = "10.5,31.5,31.5,31.5,21.408,21.56";
	    sKa = "1,1,1,1,1,1.5";
	    sKb = "3,1,1,1,1,1";
	    sHSCLK_GHz = "5.25,15.75,15.75,15.75,10.704,10.78";

	    sRefCLK_MHz = "75,350,350,350,107.04,107.8";
	    sRefCLK_MHz2 = "75,350,350,350,107.04,107.8";

	    sNb = "70,45,90,135,50,50";
	    sNa = "3,1,1,1,2,2";
	    sP = "13,8,18,29,9,9";
	    sS = "12,7,12,13,8,8";
	    sSdivder = "1,1,1,1,1,1";
	    sRateMode = "0,0,0,0,0,0";
	    sMDiv = "1,1,2,3,1,1";

	    sSpecifcation = "75M,350M,350M,350M,107M04,107M8";
	    parseListOfString(sSpecifcation, vSpecifcation, ',');

	    mCalibrationType = "SS+CS";

	    iHsClkDistClkSpare_Bit2 = 0;
	    iJ_40b = 10;
	    iJ_32b = 8;


	    parseListOfDouble(sRefCLK_MHz, vRefCLK_MHz, ',');
	    parseListOfDouble(sRefCLK_MHz2, vRefCLK_MHz2, ',');
	    parseListOfDouble(sKa, vKa, ',');
	    parseListOfDouble(sHSCLK_GHz, vHSCLK_GHz, ',');
	    parseListOfDouble(sDataRate, vDataRate, ',');

	    parseListOfInt(sKb, vKb, ',');
	    parseListOfInt(sNa, vNa, ',');
	    parseListOfInt(sNb, vNb, ',');
	    parseListOfInt(sMDiv, vMDiv, ',');
	    parseListOfInt(sSdivder, vSdivder, ',');
	    parseListOfInt(sP, vP, ',');
	    parseListOfInt(sS, vS, ',');

	    INT refCLKNum = vRefCLK_MHz.size();

	    //	   SITE      ClkIndex  MacroID   PllId Result
	    map<UINT, map<UINT, map<UINT, map<UINT, INT> > > > mResult_PerIndex;

	    vPllId.clear();

	    // vPllId init
	    switch (iPll_Select) {
	        case 0: // Pll0
	            vPllId.push_back(0);
	            break;
	        case 1: // Pll1
	            vPllId.push_back(1);
	            break;
	        case -1:// Pll0&1
	            vPllId.push_back(0);
	            vPllId.push_back(1);
	            break;
	        default:
//	            api ->info_message("ERROR: Incorrect Pllsel set!!! Please Check this parameter!!!");
	            cout <<"ERROR: Incorrect Pllsel set!!! Please Check this parameter!!!"<<endl;
	            //			ERROR_EXIT(TM::ABORT_FLOW);
	            break;
	    }

//	    FOREACH_ACTIVE_SITE(api) {
//	        unsigned int SiteID = api->Get_active_site();
	    FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

	    for (int idxRefClk = 0; idxRefClk < refCLKNum; idxRefClk++) {
	            for (UINT macroIndex = 0; macroIndex < macroNum; macroIndex++) {
	                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
	                for (UINT iPllIdIndex = 0; iPllIdIndex < vPllId.size(); iPllIdIndex++) {
	                    UINT PllID = vPllId[iPllIdIndex];
	                    mResult_PerIndex[SiteID][idxRefClk][MacroID][PllID] = 0;
	                }
	            }
	        }
	        FOREACH_ACTIVESITE_END
	    //		FlexRelayCtrl();
	    //=============================================
	    // Device Setup
	    //=============================================
	    // masked by tony 20210520 put into usercode.h
	    // #define SITES 4
	    // unsigned int current_sites[SITES];// = {0,1,2,3};
	    // unsigned int active_sites_size;

	    for (INT refIndex = 0; refIndex < refCLKNum; refIndex++) {
//	        active_sites_size = api->Get_active_sites(current_sites);

	        // change Timing
	        if (vRefCLK_MHz[refIndex] == 75) {
//	            api->Execute_test("PCM_75M_HILINK");
	            TheInst.Digital().Pattern().Start("HILINK_PCM_75M");
//	            Sleep(0.005);
	        } else if (vRefCLK_MHz[refIndex] == 350) {
//	            api->Execute_test("PCM_350M_HILINK");
	            TheInst.Digital().Pattern().Start("HILINK_PCM_350M");
//	            sleep(0.005);
	        } else if (vRefCLK_MHz[refIndex] == 107.04) {
//	            api->Execute_test("PCM_107M04_HILINK");
	            TheInst.Digital().Pattern().Start("HILINK_PCM_170M4");
//	            Sleep(0.005);
	        } else if (vRefCLK_MHz[refIndex] == 107.8) {
//	            api->Execute_test("PCM_107M8_HILINK");
	            TheInst.Digital().Pattern().Start("HILINK_PCM_170M8");
//	            Sleep(0.005);
	        } else {
	        	cout <<"ERROR: Incorrect Refclksel set!!! Please Check this parameter!!!"<<endl;
//	            api ->info_message("ERROR: Incorrect Refclksel set!!! Please Check this parameter!!!");
//	        	cout<<"ERROR: Incorrect Refclksel set!!! Please Check this parameter!!!";
	        }

//	        api->Set_active_sites(current_sites, active_sites_size);//mask by tony 20210810
	        GlobalInitPattern = mInitPattern;
	        mChronusPattern = ""; //Don't need ChronusPattern;

	#ifdef TestChip
	        //				FW_TASK("APRM CNL;");
	        //				FW_TASK(KEEPALIVE_FWTASK_TC);
	        MacroPowerUp( MacroLane_Sel, mPowerUpControlPattern, mInitPattern, "PowerUp+Init");
	#else				//FW_TASK("FTCG SKPR,ON,(pHilink_CLK)");//
	        //				FW_TASK("APRM CNL;");
	        //				FW_TASK(KEEPALIVE_FWTASK_PRODUCT);
	        MacroPowerUp( MacroLane_Sel, mPowerUpControlPattern, mInitPattern, "PowerUp+Init");
	#endif

	        //use switch
	        int temp_iJ_32b = 0;
	        if (iJ_32b == 8) {
	            temp_iJ_32b = 0;
	        } else if (iJ_32b == 16) {
	            temp_iJ_32b = 1;
	        } else if (iJ_32b == 10) {
	            temp_iJ_32b = 2;
	        } else if (iJ_32b == 20) {
	            temp_iJ_32b = 3;
	        }
	        int temp_iJ_40b = 0;
	        if (iJ_40b == 10) {
	            temp_iJ_40b = 0;
	        } else if (iJ_40b == 20) {
	            temp_iJ_40b = 1;
	        } else if (iJ_40b == 8) {
	            temp_iJ_40b = 2;
	        } else if (iJ_40b == 16) {
	            temp_iJ_40b = 3;
	        }

	        MACRO_INT mCS_Cal_MacroResult;
	        MACRO_INT mCsCalVcoLockPerMacro;
	        MACRO_INT mDS_Cal_MacroResult;
	        mCS_Cal_MacroResult.init(0);
	        mCsCalVcoLockPerMacro.init(0);
	        mDS_Cal_MacroResult.init(0);
	        CUSTPARA CUSTpara;
	        CUSTpara.Data_Rate = vDataRate[refIndex];
	        CUSTpara.PllSel = iPll_Select;
	        CUSTpara.GB_Enable = 0;

	        SSPARA SSpara;
	        SSpara.RefclkBus = iRefclkBus;
	        SSpara.SDiv = vSdivder[refIndex];
	        SSpara.RefclkMHz = vRefCLK_MHz[refIndex];
	        SSpara.RefclkMHz2 = vRefCLK_MHz2[refIndex];

	        CSPARA CSpara;
	        CSpara.KaDiv = vKa[refIndex];
	        CSpara.KbDiv = vKb[refIndex];
	        CSpara.NaDiv = vNa[refIndex];
	        CSpara.NbDiv = vNb[refIndex];
	        CSpara.Pvalue = vP[refIndex];
	        CSpara.Svalue = vS[refIndex];
	        CSpara.Mdiv = vMDiv[refIndex];
	        CSpara.PllMclkPreDiv = 1; //For lockrange this is fixed
	        CSpara.HSCLK = vHSCLK_GHz[refIndex];
	        CSpara.J32bdiv = temp_iJ_32b; //default value
	        CSpara.J40bdiv = temp_iJ_40b; //default value
	        CSpara.HsClkDistClkSpare_Bit2 = iHsClkDistClkSpare_Bit2;
	        CUSTpara.RateMode = 0;
	        CUSTpara.DataWidth = 0;
	        hout(DETAIL) << "Dump info Check Begin" << endl;

	        hout(DETAIL) << "SSpara.RefclkMHz = " << dec << SSpara.RefclkMHz << endl;
	        hout(DETAIL) << "CUSTpara.PllSel = " << dec << CUSTpara.PllSel << endl;
	        hout(DETAIL) << "SSpara.SDiv = " << dec << SSpara.SDiv << endl;
	        hout(DETAIL) << "CSpara.Mdiv = " << dec << CSpara.Mdiv << endl;
	        hout(DETAIL) << "CUSTpara.RateMode = " << dec << CUSTpara.RateMode << endl;
	        hout(DETAIL) << "CUSTpara.DataWidth = " << dec << CUSTpara.DataWidth << endl;
	        hout(DETAIL) << "CSpara.KaDiv = " << dec << CSpara.KaDiv << endl;
	        hout(DETAIL) << "CSpara.KbDiv = " << dec << CSpara.KbDiv << endl;
	        hout(DETAIL) << "CSpara.HSCLK =" << dec << CSpara.HSCLK << endl;
	        hout(DETAIL) << "CSpara.NaDiv = " << dec << CSpara.NaDiv << endl;
	        hout(DETAIL) << "CSpara.NbDiv = " << dec << CSpara.NbDiv << endl;

	        hout(DETAIL) << "Dump info Check end" << endl << endl;


	        //		READ_ALL_CSR;
	        //full_cal_en change to 3
	        HiLink30_FW_CAL( MacroLane_Sel, CUSTpara, SSpara, CSpara, mCS_Cal_MacroResult, mCsCalVcoLockPerMacro, mDS_Cal_MacroResult, mCalibrationType, FullCalPara.REFLOCKRANGE_USE, 1);

//	        FOREACH_ACTIVE_SITE(api) {
//	            unsigned int SiteID = api->Get_active_site();
	        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

	        for (UINT macroIndex = 0; macroIndex < macroNum; macroIndex++) {
	                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

	                hout(DETAIL) << "Macro:" << MacroID << "Cal result : " << mCS_Cal_MacroResult[SiteID][MacroID] << endl;
	                hout(DETAIL) << "Macro:" << MacroID << "VCOLOCK result : " << mCsCalVcoLockPerMacro[SiteID][MacroID] << endl;

	                for (UINT iPllIdIndex = 0; iPllIdIndex < vPllId.size(); iPllIdIndex++) {
	                    UINT PllID = vPllId[iPllIdIndex];
	                    if ((PllID == 0 && (mCsCalVcoLockPerMacro[SiteID][MacroID] == 1 || mCsCalVcoLockPerMacro[SiteID][MacroID] == 2)) ||
	                            (PllID == 1 && (mCsCalVcoLockPerMacro[SiteID][MacroID] == 1 || mCsCalVcoLockPerMacro[SiteID][MacroID] == 3)))
	                        mResult_PerIndex[SiteID][refIndex][MacroID][PllID] = 1;
	                    else
	                        mResult_PerIndex[SiteID][refIndex][MacroID][PllID] = 0;
	                }
	            }
	            FOREACH_ACTIVESITE_END
	        //			FW_TASK("FTCG SKPR,OFF,(@@)");
	    }

	    //=============================================
	    // Restore
	    //=============================================
	    //		Primary.getSpecification().restore();
	    //		FLUSH(TM::APRM);
//	    Sleep(0.001);
	    //=============================================
	    // Datalog
	    //=============================================

//	    FOREACH_ACTIVE_SITE(api) {
//	        unsigned int SiteID = api->Get_active_site();
	        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

	        ostringstream plot_refclk_lock;
	        for (UINT iPllIdIndex = 0; iPllIdIndex < vPllId.size(); iPllIdIndex++) {
	            UINT PllID = vPllId[iPllIdIndex];
	            plot_refclk_lock << "========RefClkLockRange_hole_Pll" << vPllId[iPllIdIndex] << "_plot========";
	            for (UINT macroIndex = 0; macroIndex < macroNum; macroIndex++) {
	                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
	                plot_refclk_lock << "\nMacro_" << MacroID << " REFCLK_LOCK_point:\t";
	                for (INT refIndex = 0; refIndex < refCLKNum; refIndex++) {
	                    if (mResult_PerIndex[SiteID][refIndex][MacroID][PllID])
	                        plot_refclk_lock << "L ";
	                    else
	                        plot_refclk_lock << "X ";
	                }
	            }
	            plot_refclk_lock << endl;
	            //				PUT_DATALOG (plot_refclk_lock.str());

	            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
	                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

	                for (INT refIndex = 0; refIndex < refCLKNum; refIndex++) {
	                    if (refIndex == 0)
	                        Res_perMacro[PllID][SiteID][MacroID] = 0;
	                    Res_perMacro[PllID][SiteID][MacroID] += mResult_PerIndex[SiteID][refIndex][MacroID][PllID] * pow(10.0, refIndex);
	                }
	            }
	        }
	        FOREACH_ACTIVESITE_END

	    //		ON_FIRST_INVOCATION_END();
	    //=============================================
	    // Datalog
	    //=============================================

	    for (UINT iPllIdIndex = 0; iPllIdIndex < vPllId.size(); iPllIdIndex++) {
	        UINT PllID = vPllId[iPllIdIndex];

	        ostringstream sPllID;
	        sPllID << PllID;
	        double LimitL = 111111;
	        double LimitH = 111111;
	        HiLink_PerMacro_Judge( MacroLane_Sel, "RefclkLockRange_AllSlides_Pll" + sPllID.str(), LimitL, Res_perMacro[PllID], LimitH);
	    }

	    SetTestBin();
	}

};


REGISTER_TESTCLASS("RefclkLockRange",RefclkLockRange)
















