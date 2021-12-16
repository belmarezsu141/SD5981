//for test method API interfaces

#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"


using namespace std;
class HILINK_FW_ADAPTATION: public TestClass{
public:
	STRING                          mHiLink30_MacroList;
	STRING							iFull_Cal_en;
	STRING							iFullAdaptaionEn;
	STRING              			sLoopBackMode;
	DOUBLE                          dRefCLK_MHz;
	DOUBLE                          dRefCLK_MHz2;
	INT                             iPll_Select;
	INT                             iRefclkBus;
	INT                             iSdivder;
	DOUBLE                          dKa;
	INT                             iKb;
	INT                             iNa;
	INT                             iNb;
	INT                             iP;
	INT                             iS;
	INT                             iMDiv;
	INT                             mLDiv;
	INT                             mWDiv;
	INT                             mVDiv;
	INT                             mJDiv;
	STRING                       	sRateMode;
	STRING                          sDataWidth;
	INT 				            iMclkdiv_input_sel;
	INT 				            iJ_40b;
	INT 				            iJ_32b;
	DOUBLE 				            dHSCLK_GHz;
	STRING                          sCalibrationType;
	INT                             iPllMclkPreDiv;
	STRING                          sFIR_setting;
	INT                             iMck2dig_div1_pwrdb;
	INT					    		iPrintLvl;

    void init(){
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					 .set_comment("HiLink30 Macro List for test")
					 //.setOptions("0,1:0:1")
					 .set_default("0,1");
		add_param("CalibrationSection","string",&sCalibrationType)
					 .set_comment("For some case cal need to ended with less loop")
					 //.setOptions("SS+CS+DS")
					 .set_default("SS+CS+DS");
		add_param("Full_Cal_Enable","string",&iFull_Cal_en)
					 //.setOptions("BypassCal:FullCal")
					 .set_default("1");
		add_param("Full Adaptation Enable","string",&iFullAdaptaionEn)
					 //.setOptions("BypassAdpt:FullAdpt:NoAdpt")
					 .set_default("NoAdpt");
		add_param("LoopBackMode","string",&sLoopBackMode)
					 //.setOptions("PreDriver:Bump:External:")
					 .set_default("External");
		add_param("Pll_Select","int",&iPll_Select)
					 .set_comment("iPll_Select")
					 //.setOptions("0:1:-1")
					 .set_default("-1");
		add_param("RefCLK_MHz","double",&dRefCLK_MHz)
					 .set_comment("RefCLK_MHz")
					 //.setOptions("100:156.25")
					 .set_default("156.25");
		add_param("RefCLK_MHz2","double",&dRefCLK_MHz2)
					 .set_comment("RefCLK_MHz2")
					 //.setOptions("100:156.25")
					 .set_default("156.25");
		add_param("RefclkBus","int",&iRefclkBus)
					 //.setOptions("0:1:-1")
					 .set_default("-1");
		add_param("PrintLvl[0~8]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
					 "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.setOptions("0:1:3:4:7:8")
					 .set_default("3");
    }
    void execute(){

        H30_FailBin_Flag.init(0);
        static MACRO_LANE_SEL MacroLane_Sel;
        static INT iDebugAnalog;
        static INT macroNum;
        static MACRO_DOUBLE CS_CAL_Result;
        static MACRO_DOUBLE DS_CAL_Result;
        static MACRO_DOUBLE Adaptation_CAL_Result;
        STRING sFIR_setting;
        //		ON_FIRST_INVOCATION_BEGIN();

        CS_CAL_Result.init(0);
        DS_CAL_Result.init(0);
        Adaptation_CAL_Result.init(0);

        //		GET_TESTSUITE_NAME	(sTestsuiteName);
        //		GET_TESTFLOW_FLAG	("debug_analog",&iDebugAnalog);
        //extern stHILINK_FW_ADAPTATION H30_FW_ADPT_156M25_30G_1196full40_Refclk1_PLL0_PLL1_108_1_1_9_6_V1_VDDN_HILINK_FW_ADAPTATION;
        stHILINK_FW_ADAPTATION HILINK_FW_ADAPTATION;



        static STRING mPinList = "";
//        const char * sTestsuiteName = api->Get_current_test_name();
        string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
        string strTestsuiteName = sTestsuiteName;
//        api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER, &m_TestNumber, THE_END);

//        cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();


        hout.setLevel(iPrintLvl);
        hout.printsuitename(sTestsuiteName);
        Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList);
        macroNum = MacroLane_Sel.size();

        //in future ratemode may become 0 [Full]
        //		INT					iRateMode = sRateMode[0]-'0';
        //		INT					iDataWidth = sDataWidth[0]-'0';

        //use switch
        //		int temp_iJ_32b = 0;
        //		if(iJ_32b == 8){
        //			temp_iJ_32b = 0;
        //		}else if(iJ_32b == 16){
        //			temp_iJ_32b = 1;
        //		}else if(iJ_32b == 10){
        //			temp_iJ_32b = 2;
        //		}else if(iJ_32b == 20){
        //			temp_iJ_32b = 3;
        //		}
        //		int temp_iJ_40b = 0;
        //		if(iJ_40b == 10){
        //			temp_iJ_40b = 0;
        //		}else if(iJ_40b == 20){
        //			temp_iJ_40b = 1;
        //		}else if(iJ_40b == 8){
        //			temp_iJ_40b = 2;
        //		}else if(iJ_40b == 16){
        //			temp_iJ_40b = 3;
        //		}

        TxFIR_SETTING TxFIR_USER = {0, -6, 57, 0, 0}; //20170217 shaoxue
        INT_VECTOR FIRTAP;
        parseListOfInt(sFIR_setting, FIRTAP, ',');

        CUSTPARA CUSTpara = default_CUSTPARA;
        CUSTpara.PllSel = iPll_Select;
        //		CUSTpara.RateMode = iRateMode;
        //		CUSTpara.DataWidth = iDataWidth;
        CUSTpara.TxFIR_USER = TxFIR_USER;

        SSPARA SSpara = default_SSPARA;
        SSpara.RefclkMHz = dRefCLK_MHz;
        SSpara.RefclkMHz2 = dRefCLK_MHz2;
        SSpara.RefclkBus = iRefclkBus;
        //		SSpara.SDiv = iSdivder;

        CSPARA CSpara = default_CSPARA;
        //		CSpara.Mdiv          = iMDiv;
        //		//CSpara.PllMclkPreDiv = iPllMclkPreDiv;
        //		CSpara.KaDiv         = dKa;
        //		CSpara.KbDiv         = iKb;
        //		CSpara.HSCLK         = dHSCLK_GHz;
        //		CSpara.NaDiv         = iNa;
        //		CSpara.NbDiv         = iNb;
        //		CSpara.Pvalue        = iP;
        //		CSpara.Svalue        = iS;
        //		CSpara.J32bdiv       = temp_iJ_32b;
        //		CSpara.J40bdiv       = temp_iJ_40b;
        //		CSpara.mck2dig_div1_pwrdb = iMck2dig_div1_pwrdb;


        //		FlexRelayCtrl();

        MACRO_INT mCS_Cal_MacroResult;
        MACRO_INT mCsCalVcoLockPerMacro;
        MACRO_INT mDS_Cal_MacroResult;
        mCS_Cal_MacroResult.init(0);
        mCsCalVcoLockPerMacro.init(0);
        mDS_Cal_MacroResult.init(0);
        //=============================================
        // Full and bypass calibration
        //=============================================
        MACRO_INT mDS_Cal_MacroResult_Adaptation;
        mDS_Cal_MacroResult_Adaptation.init(0);


        if (sCalibrationType == "SS+CS+DS") {
            if (iFullAdaptaionEn == AdptPara.FullAdpt) {
                ATE_CTLE_Adaptation( MacroLane_Sel, CUSTpara, dRefCLK_MHz, dRefCLK_MHz2, mDS_Cal_MacroResult_Adaptation, sLoopBackMode);
            } else if (iFullAdaptaionEn == AdptPara.BypassAdpt) {
                ATE_CTLE_Bypass_Adaptation( MacroLane_Sel, CUSTpara, dRefCLK_MHz, dRefCLK_MHz2, mDS_Cal_MacroResult_Adaptation, sLoopBackMode);
            } else {
                //				cout << "ONLY SUPPORT FULL ADAPTATION AND BYPASS ADAPTATION!!!" << endl;
                cout<<"ONLY SUPPORT FULL ADAPTATION AND BYPASS ADAPTATION!!!"<<endl;
                //			    ERROR_EXIT(TM::ABORT_FLOW);
            }
        }

        if (sCalibrationType != "SS") {

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
        	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
                for (INT macroIndex = 0; macroIndex < macroNum; macroIndex++) {
                    UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
                    //
                    //					if (1 == mCS_Cal_MacroResult[SiteID][MacroID] && 1 == mCsCalVcoLockPerMacro[SiteID][MacroID])
                    //					{
                    //						CS_CAL_Result[SiteID][MacroID] = 1;
                    //					}
                    //					DS_CAL_Result[SiteID][MacroID] = mDS_Cal_MacroResult[SiteID][MacroID];
                    //
                    if (iFullAdaptaionEn == AdptPara.BypassAdpt || iFullAdaptaionEn == AdptPara.FullAdpt) {
                        Adaptation_CAL_Result[SiteID][MacroID] = mDS_Cal_MacroResult_Adaptation[SiteID][MacroID];

                        if(PrintDebugEn) cout<<"Adaptation_CAL_Result[siteID"<<SiteID <<"][MacroID"<<MacroID<<"]="<< Adaptation_CAL_Result[SiteID][MacroID]<<endl;
                    }
                }
                FOREACH_ACTIVESITE_END
        }
//          ALL_CSR_ReadBack_TO_FILE_Debug(MacroLane_Sel,"After_Adaptation");
        //		else
        //		{
        //			FOR_EACH_SITE_BEGIN();
        //			INT SiteID = CURRENT_SITE_NUMBER() - 1;
        //			for (INT macroIndex = 0; macroIndex < macroNum; macroIndex ++)
        //			{
        //				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        //				CS_CAL_Result[SiteID][MacroID]=mCS_Cal_MacroResult[SiteID][MacroID];
        //
        //			}
        //
        //			FOR_EACH_SITE_END();
        //		}
        //	ON_FIRST_INVOCATION_END();

        //=============================================
        // Judgement
        //=============================================

        /*************** New Judge For Optimize STDF***************/

        //		if(sCalibrationType == "SS")HiLink_PerMacro_Judge(MacroLane_Sel,"CS_Cal_Done",CS_CAL_Result,PIN_RXP);
        //
        //		else if (sCalibrationType == "SS+CS")HiLink_PerMacro_Judge(MacroLane_Sel,"CS_Cal_Done",CS_CAL_Result,PIN_RXP);
        //
        //		else if(sCalibrationType == "SS+CS+DS")
        //		{
        //			HiLink_PerMacro_Judge(MacroLane_Sel,"CS_Cal_Done",CS_CAL_Result,PIN_RXP);
        //			HiLink_PerMacro_Judge(MacroLane_Sel,"DS_Cal_Done",DS_CAL_Result,PIN_RXP);

        //                ALL_CSR_ReadBack_TO_FILE_Debug(MacroLane_Sel,"afterAdaptation");
        double LimitL = 1;
        double LimitH = 1;
        if (iFullAdaptaionEn == AdptPara.BypassAdpt || iFullAdaptaionEn == AdptPara.FullAdpt) {
            HiLink_PerMacro_Judge( MacroLane_Sel, "Adaptation_DS_Cal_Done", LimitL, Adaptation_CAL_Result, LimitH, PIN_RXP);
        }

        SetTestBin();
    }
};

REGISTER_TESTCLASS("HILINK_FW_ADAPTATION",HILINK_FW_ADAPTATION)

