
#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"

using namespace std;

class Ext_2K_Resistor_Check: public TestClass
{
public:
	STRING 				mPinList;
	INT					iPrintLvl;
	void init()
	{
		add_param("PinList","PinString",&mPinList);
		add_param("PrintLvl[0~8]","int",&iPrintLvl)
					.set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
					"0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					//.setOptions("0:1:3:4:7:8")
					.set_default("3");
	}
	void execute()
	{

		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
		H30_FailBin_Flag.init(0);
		static INT iOffline;
		static INT iCSR_check;
		static MACRO_LANE_SEL MacroLane_Sel;

		static MACRO_DOUBLE ResistorCalBits;
//		static STRING mPinList = "";

		//=============================================
		// Variables and MacroLane initialization
		//=============================================

//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

		stExt_2K_Resistor_Check& Ext_2K_Resistor_Check =External_2K_Ext_2K_Resistor_Check;


		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel, SSMacroIDList, mPinList);

		//=============================================
		// Device Setup
		//=============================================
//		D2S_FRAMEWORK;
//		GET_TEST_INFO;

		/***********************************
		 STEP1. Startup Macro with SS (startup SS & CS only, DO NOT startup DS)
		 ************************************/
		// TODO
		/***********************************
		 STEP2. Get CSR code of rpolydetcsrxtermcal for SS macro
		 ************************************/
		char IDstring[128];
		ResistorCalBits.init(0);
		d2s_JTAG& jtag = d2s_JTAG::Instance();

//		sprintf(label,"ResistorCalBits_Read_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN( "ResistorCalBits_Read_",Global_D2S_Mode);

		for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size();
				macroIndex++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			selectMacro(MacroID);
			CS.clkRegs.MacroID(MacroID).SliceID(0).Broadcast(0);

			sprintf(IDstring, "ResistorCalBits_onMacro%i", MacroID);
			CS.clkRegs.Read2IDString(44, IDstring);
		}
//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();

//		FOREACH_ACTIVE_SITE(api)
//		{
//			unsigned int SiteID = api->Get_active_site();
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size();
					macroIndex++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

				sprintf(IDstring, "ResistorCalBits_onMacro%i", MacroID);
				uint val = (UINT) jtag.getReadValue(IDstring)[SiteID];
				ResistorCalBits[SiteID][MacroID] = HILINK_Regs_Base::get_bits(
						val, CS.clkRegs.REG_INFO.rpolydetcsrxtermcal());

				if(PrintDebugEn) cout << "ResistorCalBits: Site" << SiteID << "MacroID: "
						<< MacroID << " = " << hex << "0x"
						<< ResistorCalBits[SiteID][MacroID] << endl;

			}
		FOREACH_ACTIVESITE_END

		//=============================================
		// Datalog
		//=============================================
		double LimitL = 1;
		double LimitH = 14;
		HiLink_PerMacro_Judge(MacroLane_Sel, "ResistorCalBits", LimitL,ResistorCalBits, LimitH);


	}
};
REGISTER_TESTCLASS("Ext_2K_Resistor_Check", Ext_2K_Resistor_Check)

