//for test method API interfaces
#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"

using namespace std;

/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
        /**
	 *This test is invoked per site.
	 */
class HiLink30_PowerUp_Reset: public TestClass{
public:
	STRING                   mHiLink30_MacroList;
	STRING					 mDPSLEVEL;
	STRING                   mPowerUpControlPattern;
	STRING                   mInitPattern;
	STRING                   mChronusPattern;
	STRING					 mWorkingMode;
	INT                      mPRBSMODE;
	INT 					 mEqnNum;
	INT					     iPrintLvl;
	int isFirst;
	void init() {
//        add_param( "isFirst",  "int", &isFirst)
//                .set_default("0")
//                .set_options("0:1");


		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					 .set_comment("HiLink30 Macro List for test")
					 //.setOptions("0,1:0:1:0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18")
					 .set_default("0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18");
		add_param("WorkingMode","string",&mWorkingMode)
					//.setOptions("PowerUp+ChangeLevel+Init:PowerUp+Init:Init")
					.set_default("PowerUp+Init");
		add_param("EQNNUM","int",&mEqnNum)
					 .set_default("201");
		add_param("PRBSMODE","int",&mPRBSMODE)
					 .set_comment("PRBS MODE: ON = 1, PRBS MODE: OFF = 0")
					 //.setOptions("1:0")
					 .set_default("0");
		add_param("PowerUpControlPattern","string",&mPowerUpControlPattern)
					 //.setOptions("HILINK_R01_K33277V100_PowerUpSeqCtrl_ALL_X1_M_40ns_V1_burst")
					 .set_default("HILINK_R01_K33277V100_PowerUpSeqCtrl_ALL_X1_M_40ns_V1_burst");
		add_param("InitPattern","string",&mInitPattern)
					 //.setOptions("")
					 .set_default("");
		add_param("ChronusPattern","string",&mChronusPattern)
					 //.setOptions("")
					 .set_default("");
		add_param("PrintLvl[0~8]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
					 "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.setOptions("0:1:3:4:7:8")
					 .set_default("3");
	}
    void execute(){

    string  powercase;
    
    stHiLink30_PowerUp_Reset HiLink30_PowerUp_Reset;

    string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
    string strTestsuiteName = sTestsuiteName;
//    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
	m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
	m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
	m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

	TheInst.DCVI().Power().Apply();
	TheInst.Digital().Level().Apply();
	TheInst.Digital().Timing().Apply();
	if(PrintDebugEn) cout<<"power level timing apply() at here"<<endl;
//
//    TheSoft.Flow().Power().SetPower("Hilink_General_Power");
//    TheSoft.Flow().Level().SetLevel("HILINK_LVL_FUN");
//    TheSoft.Flow().Timing().SetTiming("TIM_HiLink30LR");
////    TheSoft.Flow().Pattern().SetPattern("H32_Disconnect_TX_RX_DZ");
//    TheInst.DCVI().Power().Apply();
//    TheInst.Digital().Level().Apply();
//    TheInst.Digital().Timing().Apply();
////    TheInst.Digital().Pattern().Start();
//    TheInst.Wait(5);//TIME
//
//    if(strTestsuiteName.find("VDDN")!=string::npos)  powercase ="NOR";
//    else if (strTestsuiteName.find("VDDH")!=string::npos)  powercase ="HIGH";
//    else if (strTestsuiteName.find("VDDL")!=string::npos)  powercase ="LOW";
//    else powercase ="NOR";
//
//	if(powercase == "NOR"){
//    	TheInst.DCVI().Pins("LVCC08").ForceV(0.8);
//    	TheInst.DCVI().Pins("HVCC12").ForceV(1.2);
//	}else if(powercase == "LOW"){
//    	TheInst.DCVI().Pins("LVCC08").ForceV(0.776);
//    	TheInst.DCVI().Pins("HVCC12").ForceV(1.164);
//	}else if(powercase == "HIGH"){
//    	TheInst.DCVI().Pins("LVCC08").ForceV(0.824);
//    	TheInst.DCVI().Pins("HVCC12").ForceV(1.236);
//	}
//	else{
//    	TheInst.DCVI().Pins("LVCC08").ForceV(0.824);
//    	TheInst.DCVI().Pins("HVCC12").ForceV(1.236);
//	}





    static MACRO_LANE_SEL MacroLane_Sel;
    Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList.c_str());
  
    if(mWorkingMode == "PowerUp+ChangeLevel+Init" )
    {         
        H30_Disconnect_TX_RX_DZ();
    }
    
    GlobalInitPattern= mInitPattern;
    
    MacroPowerUp(MacroLane_Sel,mPowerUpControlPattern,mInitPattern,mWorkingMode);
    
//    ALL_CSR_ReadBack_TO_FILE_Debug(MacroLane_Sel,"afterpowerup");


    }
};
REGISTER_TESTCLASS("HiLink30_PowerUp_Reset",HiLink30_PowerUp_Reset)



void H30_set_spec_Vcoef103() {
//    FOREACH_ACTIVE_SITE(api) {
    	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        double Vcoef_Value;
//        api->Get_variable_values("Vcoef_HiLink", THE_VALUE,&Vcoef_Value, THE_END);
//        if(Vcoef_Value != 1.03){
//            api->Set_variable_values("Vcoef_HiLink",THE_VALUE,1.03,THE_END);
//            api->Set_variable_values("Vcore",THE_VALUE,1.03,THE_END);
//        }
        FOREACH_ACTIVESITE_END

}


void H30_set_spec_Vcoef100() {
//    FOREACH_ACTIVE_SITE(api) {
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

//        unsigned void SiteID = api->Get_active_site();
//        double Vcoef_Value;
//        api->Get_variable_values("Vcoef_HiLink", THE_VALUE,&Vcoef_Value, THE_END);
//        if(Vcoef_Value != 1){
//            api->Set_variable_values("Vcoef_HiLink",THE_VALUE,1.0,THE_END);
//            api->Set_variable_values("Vcore",THE_VALUE,1.0,THE_END);
//        }
        FOREACH_ACTIVESITE_END

}


void H30_set_spec_Vcoef097() {
//    FOREACH_ACTIVE_SITE(api) {
    	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

//        double Vcoef_Value;
//        api->Get_variable_values("Vcoef_HiLink", THE_VALUE,&Vcoef_Value, THE_END);
//        if(Vcoef_Value != 0.97){
//            api->Set_variable_values("Vcoef_HiLink",THE_VALUE,0.97,THE_END);
//            api->Set_variable_values("Vcore",THE_VALUE,0.97,THE_END);
//        }
        FOREACH_ACTIVESITE_END
}
