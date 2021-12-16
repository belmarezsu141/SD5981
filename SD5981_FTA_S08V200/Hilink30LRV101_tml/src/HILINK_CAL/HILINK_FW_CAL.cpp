//for test method API interfaces
#include <Common_Func/HiLink30_Common_Func.h>

using namespace std;

/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class HILINK_FW_CAL: public TestClass{
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
	INT                             iHsClkDistClkSpare_Bit2;
	INT					    		iPrintLvl;
    void init(){
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					 .set_comment("HiLink30 Macro List for test")
					 //.setOptions("0,1:0:1")
					 .set_default("0,1");
		add_param("CalibrationSection","string",&sCalibrationType)
					 .set_comment("For some case cal need to ended with less loop")
					 //.setOptions("SS:SS+CS:SS+CS+DS:CS+DS")
					 .set_default("SS+CS+DS");
		add_param("Full_Cal_Enable","string",&iFull_Cal_en)
					 //.setOptions("BypassCal:FullCal:FullCal_FWABIST_USE:REFLOCKRANGE_USE")
					 .set_default("FullCal");
		add_param("Full Adaptation Enable","string",&iFullAdaptaionEn)
					 //.setOptions("BypassAdpt:FullAdpt:NoAdpt")
					 .set_default("BypassAdpt");
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
		add_param("Sdivder","int",&iSdivder)
					 //.setOptions("1:2")
					 .set_default("1");
		add_param("MDiv","int",&iMDiv)
		 	 	 	 .set_default("0");
		add_param("RateMode","string",&sRateMode)
					 //.setOptions("0[Full]:1[Half]:2[Quarter]:3[Oct]")
					 .set_default("0[Full]");
		add_param("Ka","double",&dKa)
					 //.setOptions("2:3")
					 .set_default("2");
		add_param("Kb","int",&iKb)
					 //.setOptions("1:2")
					 .set_default("1");
		add_param("HSCLK_GHz","double",&dHSCLK_GHz)
					 .set_comment("HSCLK_GHz")
					 .set_default("12.890625");
		add_param("Na","int",&iNa)
					 //.setOptions("1:2:3")
					 .set_default("2");
		add_param("Nb","int",&iNb)
					 //.setOptions("5:66")
					 .set_default("33");
		add_param("P","int",&iP)
		 	 	 	 .set_default("0");
		add_param("S","int",&iS)
		 	 	 	 .set_default("0");
		add_param("HsClkDistClkSpare_Bit2","int",&iHsClkDistClkSpare_Bit2)
					 //.setOptions("0:1")
					 .set_default("0");
		add_param("J_40b","int",&iJ_40b)
					 //.setOptions("0:1:2:3")
					 .set_default("0");
		add_param("J_32b","int",&iJ_32b)
					 //.setOptions("0:1:2:3")
					 .set_default("0");
		add_param("DataWidth","string",&sDataWidth)
					 //.setOptions("0[1x]:1[2x]:2[4x]")
					 .set_default("0[1x]");
		add_param("PrintLvl[0~8]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
					 "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.setOptions("0:1:3:4:7:8")
					 .set_default("3");
    }
    void execute(){

        H30_FailBin_Flag.init(0);
        static MACRO_LANE_SEL MacroLane_Sel;
        static MACRO_LANE_SEL vProcessMacroSS;
        static INT macroNum;
        static MACRO_DOUBLE SS_CAL_Result;
        static MACRO_DOUBLE CS_CAL_Result;
        static MACRO_DOUBLE DS_CAL_Result;
        static MACRO_DOUBLE Adaptation_CAL_Result;

        static map<UINT, bool> mSSMacroID;
        static STRING sSSMacroList = "";

        SS_CAL_Result.init(0);
        CS_CAL_Result.init(0);
        DS_CAL_Result.init(0);
        Adaptation_CAL_Result.init(0);

//        const char * sTestsuiteName = api->Get_current_test_name();
        string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
        stHILINK_FW_CAL HILINK_FW_CAL;

        string strTestsuiteName = sTestsuiteName;
//        api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER, &m_TestNumber, THE_END);
//        cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();
		if(mHiLink30_MacroList.find("a")!=string::npos){
					mHiLink30_MacroList = "0,1,2,3,4,5,6,7"; }
		else if(mHiLink30_MacroList.find("b")!=string::npos){
				mHiLink30_MacroList = "0,1,2,3,4,5,6,7,12,13,14,15,16,17,18,19";}
		else if(mHiLink30_MacroList.find("c")!=string::npos){
				mHiLink30_MacroList = "0,1,2,3,4,5,6,7,8,9,12,13,14,15,16,17,18,19";}
		else if(mHiLink30_MacroList.find("d")!=string::npos){
				mHiLink30_MacroList = "12,13,14,15,16,17,18,19";}
		else if(mHiLink30_MacroList.find("e")!=string::npos){
				mHiLink30_MacroList = "12,13,14,15,17,18,19,8,9,16,0,1,2,3,4,5,6,7";}
		else if(mHiLink30_MacroList.find("f")!=string::npos){
				mHiLink30_MacroList = "8,9,12,13,14,15,16,17,18,19";}
		else if(mHiLink30_MacroList.find("g")!=string::npos){
				mHiLink30_MacroList = "8,9";}
		else{
			cout<<"!!!!!!!! please check your parameter mHiLink30_MacroList"<<endl;
		}



        Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList);

        macroNum = MacroLane_Sel.size();

        if (sCalibrationType == "SS") {
            if (iRefclkBus == 0) {
                STRING sSSMacroList = SSMacroIDList_Refclk1;
                Select_Macro_Lane(vProcessMacroSS, sSSMacroList);
            } else {
                STRING sSSMacroList = SSMacroIDList;
                Select_Macro_Lane(vProcessMacroSS, sSSMacroList);
            }
        }
        //in future ratemode may become 0 [Full]
        INT iRateMode = sRateMode[0] - '0';
        INT iDataWidth = sDataWidth[0] - '0';

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

        TxFIR_SETTING TxFIR_USER = {0, -6, 57, 0, 0};

        CUSTPARA CUSTpara = default_CUSTPARA;
        CUSTpara.PllSel = iPll_Select;
        CUSTpara.RateMode = iRateMode;
        CUSTpara.DataWidth = iDataWidth;
        CUSTpara.TxFIR_USER = TxFIR_USER;

        if (iFull_Cal_en == FullCalPara.FullCal_FWABIST_USE or iFull_Cal_en == FullCalPara.REFLOCKRANGE_USE)//mode 2 is used to FWABIST test//mode3 is used to ReflockRange
            CUSTpara.GB_Enable = 0; //for FWABIST test, don't enable GB
        else if (iFull_Cal_en == FullCalPara.BypassCal or iFull_Cal_en == FullCalPara.FullCal)
            CUSTpara.GB_Enable = 1;
        else {
            //                        cout << "Can't find valid Full_cal_en parameter !!! Please check Full_cal_en parameter!" << endl;
//            api->info_message("Can't find valid Full_cal_en parameter !!! Please check Full_cal_en parameter!");
            cout <<"Can't find valid Full_cal_en parameter !!! Please check Full_cal_en parameter!"<<endl;
        }

        SSPARA SSpara = default_SSPARA;
        SSpara.RefclkMHz = dRefCLK_MHz;
        SSpara.RefclkMHz2 = dRefCLK_MHz2;
        SSpara.RefclkBus = iRefclkBus;
        SSpara.SDiv = iSdivder;

        CSPARA CSpara = default_CSPARA;
        CSpara.Mdiv = iMDiv;

        CSpara.KaDiv = dKa;
        CSpara.KbDiv = iKb;
        CSpara.HSCLK = dHSCLK_GHz;
        CSpara.NaDiv = iNa;
        CSpara.NbDiv = iNb;
        CSpara.Pvalue = iP;
        CSpara.Svalue = iS;
        CSpara.J32bdiv = iJ_32b;
        CSpara.J40bdiv = iJ_40b;
        CSpara.HsClkDistClkSpare_Bit2 = iHsClkDistClkSpare_Bit2;

        MACRO_INT mCS_Cal_MacroResult;
        MACRO_INT mCsCalVcoLockPerMacro;
        MACRO_INT mDS_Cal_MacroResult;
        mCS_Cal_MacroResult.init(0);
        mCsCalVcoLockPerMacro.init(0);
        mDS_Cal_MacroResult.init(0);

        HiLink30_FW_CAL(MacroLane_Sel, CUSTpara, SSpara, CSpara, mCS_Cal_MacroResult, mCsCalVcoLockPerMacro, mDS_Cal_MacroResult, sCalibrationType, iFull_Cal_en);

        MACRO_INT mDS_Cal_MacroResult_Adaptation;
        mDS_Cal_MacroResult_Adaptation.init(0);

        if (sCalibrationType.find("DS") != string::npos) {
            if (iFullAdaptaionEn == AdptPara.FullAdpt) {
                ATE_CTLE_Adaptation(MacroLane_Sel, CUSTpara, dRefCLK_MHz, dRefCLK_MHz2, mDS_Cal_MacroResult_Adaptation, sLoopBackMode);
            } else if (iFullAdaptaionEn == AdptPara.BypassAdpt) {
                ATE_CTLE_Bypass_Adaptation(MacroLane_Sel, CUSTpara, dRefCLK_MHz, dRefCLK_MHz2, mDS_Cal_MacroResult_Adaptation, sLoopBackMode);
            }

        }



        if (sCalibrationType != "SS") {

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
        	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
                for (UINT macroIndex = 0; macroIndex < macroNum; macroIndex++) {
                    UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
    //                 api->Info_message("=========== mCS_Cal_MacroResult[%d][%d]= %d", SiteID, MacroID, mCS_Cal_MacroResult[SiteID][MacroID]);
    //                 api->Info_message("=========== mCsCalVcoLockPerMacro[%d][%d]= %d", SiteID, MacroID, mCsCalVcoLockPerMacro[SiteID][MacroID]);
                    if (1 == mCS_Cal_MacroResult[SiteID][MacroID] && 1 == mCsCalVcoLockPerMacro[SiteID][MacroID]) {
                        CS_CAL_Result[SiteID][MacroID] = 1;
                    }
                    DS_CAL_Result[SiteID][MacroID] = mDS_Cal_MacroResult[SiteID][MacroID];

                    if (iFullAdaptaionEn == AdptPara.BypassAdpt || iFullAdaptaionEn == AdptPara.FullAdpt) {
                        Adaptation_CAL_Result[SiteID][MacroID] = mDS_Cal_MacroResult_Adaptation[SiteID][MacroID];
                    }
                }
        	FOREACH_ACTIVESITE_END
        } else {

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
        	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
        			for (UINT macroIndex = 0; macroIndex < vProcessMacroSS.size(); macroIndex++) {
                    UINT MacroID = vProcessMacroSS[macroIndex].MacroID;
                    SS_CAL_Result[SiteID][MacroID] = mCS_Cal_MacroResult[SiteID][MacroID];
                }
        	FOREACH_ACTIVESITE_END
        }


        double LimitL = 1;
        double LimitH = 1;
        if (sCalibrationType == "SS")HiLink_PerMacro_Judge(vProcessMacroSS, "CS_Cal_Done", LimitL, SS_CAL_Result, LimitH, PIN_RXP);
        else if (sCalibrationType == "SS+CS")HiLink_PerMacro_Judge(MacroLane_Sel, "CS_Cal_Done", LimitL, CS_CAL_Result, LimitH, PIN_RXP);

        else if ((sCalibrationType == "SS+CS+DS") || (sCalibrationType == "CS+DS")) {
            HiLink_PerMacro_Judge(MacroLane_Sel, "CS_Cal_Done", LimitL, CS_CAL_Result, LimitH, PIN_RXP);
            HiLink_PerMacro_Judge(MacroLane_Sel, "DS_Cal_Done", LimitL, DS_CAL_Result, LimitH, PIN_RXP);
            //		if(iFullAdaptaionEn == 0 || iFullAdaptaionEn == 1)
            if (iFullAdaptaionEn == AdptPara.BypassAdpt || iFullAdaptaionEn == AdptPara.FullAdpt) {
                HiLink_PerMacro_Judge(MacroLane_Sel, "Adaptation_DS_Cal_Done", LimitL, Adaptation_CAL_Result, LimitH, PIN_RXP);
            }
        }

        SetTestBin();
    }
};
REGISTER_TESTCLASS("HILINK_FW_CAL",HILINK_FW_CAL)


