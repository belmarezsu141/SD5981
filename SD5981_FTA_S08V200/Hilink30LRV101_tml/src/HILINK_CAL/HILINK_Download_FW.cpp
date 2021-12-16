//for test method API interfaces

#include <Common_Func/HiLink30_Common_Func.h>

using namespace std;
/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class HILINK_Download_FW: public TestClass{
public:
	STRING 				mHiLink30_MacroList;
	STRING 				mPinList;
	INT                 mPRBSMODE;
	INT					iPrintLvl;
	INT                 mFwType;
    void init(){
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					 .set_comment("HiLink30 Macro List for test")
					 //.setOptions("0,1:FromPinList:0:1")
					 .set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
		add_param("PRBSMODE","int",&mPRBSMODE)
					 .set_comment("PRBS MODE: ON = 1, PRBS MODE: OFF = 0")
					 //.setOptions("1:0")
					 .set_default("0");
		add_param("FwType","int",&mFwType)
					 .set_comment("0:cal full fw,1:cal noapi fw,2:adpt noapi fw")
					 //.setOptions("2:1:0")
					 .set_default("0");
		add_param("PrintLvl[0~8]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
					 "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.setOptions("0:1:3:4:7:8")
					 .set_default("3");
    }
    void execute(){

        stHILINK_Download_FW HILINK_Download_FW;

//        const char * sTestsuiteName = api->Get_current_test_name();
        string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
        string strTestsuiteName = sTestsuiteName;
//        api->Get_test_values(strTestsuiteName.data(),THE_TESTNUMBER,&m_TestNumber,THE_END);
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();




        static MACRO_LANE_SEL MacroLane_Sel;
        Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList.c_str());

        //=============================================
        // FW DownLoad
        //=============================================
        LoadFirmwareToSram( MacroLane_Sel, mPRBSMODE, mFwType);
    //    ALL_CSR_ReadBack_TO_FILE_Debug(api,MacroLane_Sel,"LoadFirmwareToSram");
    }
};

REGISTER_TESTCLASS("HILINK_Download_FW",HILINK_Download_FW)



















