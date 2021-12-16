
#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"


using namespace std;

/**
 *This test is invoked per site.
 */
void AVS_Verify_Search(MACRO_LANE_SEL& MacroLane_Sel, LANE_DOUBLE &vDVDDSearchResult, STRING sSpecName, STRING sPatternType, DOUBLE DVDD_Search_Stop, DOUBLE DVDD_Search_Step)
{
	if(DVDD_Search_Step == 0)
	{
		hout(DETAIL) << "ERROR: Voltage search step is ZERO, please confirm with the input parameter." << endl;
//		  ERROR_EXIT(TM::ABORT_FLOW);
	}

	LANE_INT iFindFlag;
	LANE_INT iLaneDone;
	LANE_DOUBLE vErrorCount;
//	  DOUBLE dChangeVal = Primary.getLevelSpec().getSpecValue(sSpecName);
	double dChangeVal,dVcore;
//	FOREACH_ACTIVE_SITE(api)
//	{
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//	api->Get_variable_values("Vcore", THE_VALUE,&dVcore, THE_END);
	FOREACH_ACTIVESITE_END

	dChangeVal=dVcore;
	iFindFlag.init(0);
	iLaneDone.init(0);
	vErrorCount.init(999);
	vDVDDSearchResult.init(0);

	bool iFindAll = false;

	while (!iFindAll)
	{

//		  hout(DETAIL) << "VDD = " << Primary.getLevelSpec().getSpecValue(sSpecName) << endl;
		Read_Bert(MacroLane_Sel, vErrorCount,"ABIST",false,"", 0, 0.001);
		iFindAll = true;
//		FOREACH_ACTIVE_SITE(api)
//		{
//			unsigned int SiteID = api->Get_active_site();
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT uiMacroIndex = 0; uiMacroIndex < MacroLane_Sel.size(); uiMacroIndex ++)
			{
				UINT MacroID = MacroLane_Sel[uiMacroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[uiMacroIndex].vLane;
				for (UINT uiLaneIndex = 0; uiLaneIndex < vLane.size(); uiLaneIndex ++)
				{
					UINT LaneID = vLane[uiLaneIndex];
					if (iFindFlag[SiteID][MacroID][LaneID] == 0)
					{
						if (vErrorCount[SiteID][MacroID][LaneID] == 0)
						{
							vDVDDSearchResult[SiteID][MacroID][LaneID] = dChangeVal;
							iFindAll = false;
						}
						else
						{
							iFindFlag[SiteID][MacroID][LaneID] = 1;
						}
					}
				}
			}
		FOREACH_ACTIVESITE_END

		if (abs(dChangeVal - DVDD_Search_Stop) <= DVDD_Search_Step)
		{
			break;
		}

		if (dChangeVal > DVDD_Search_Stop)
		{
			dChangeVal -= DVDD_Search_Step;
		}
		else
		{
			dChangeVal += DVDD_Search_Step;
		}
//		FOREACH_ACTIVE_SITE(api)
//		{
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//		api->Set_variable_values("Vcore",THE_VALUE,dChangeVal,THE_END);
		FOREACH_ACTIVESITE_END
//		  Primary.getLevelSpec().change(sSpecName, dChangeVal);
//		  FLUSH(TM::APRM);
//		  WAIT_TIME(1 ms);
//		Sleep(0.001);
	}
//	FOREACH_ACTIVE_SITE(api)
//	{
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//	api->Set_variable_values("Vcore",THE_VALUE,dVcore,THE_END);
	FOREACH_ACTIVESITE_END
}

class AVS_Verify_ABIST: public TestClass
{
public:
	STRING 				sDPSPinList;
	STRING 				sPinList;
	STRING 				sHiLink30_MacroList;
	INT                 iDataWidth;
	INT                 iRateMode;
	INT	 				iTxMain;
	INT					iTxPre1st;
	INT					iTxPost1st;
	INT                 iTXDRVTAPXMODSEL;
	INT                 iTxPre2nd;
	INT                 iTxPost2nd;
	STRING              sLoopBackMode;
	STRING              sSearch_Direction;
	INT 				iCTLEACTGN1;
	INT 				iCTLEACTGN2;
	INT 				iCTLEACTGN3;
	INT					iCTLEBST1;
	INT					iCTLEBST2;
	INT					iCTLEBST3;
	STRING				mUseFixCTLE;
	DOUBLE              dSearchLow;
	DOUBLE              dSearchHigh;
	DOUBLE              dSearchStep;
	INT					iPrintLvl;


void init()
{
	 add_param("DPSPinList","PinString",&sDPSPinList)
					   .set_comment("Hilink30 DVDD PINS for AVS");
					  // .set_default("VDD");
	  add_param("LoopBackMode","string",&sLoopBackMode)
				   //.set_options("PreDriver:Bump:External:Nothing")
				   .set_default("Bump");
	  add_param("HiLink30_MacroList","string",&sHiLink30_MacroList)
				   .set_comment("Hilink30 Macro List for test")
				   //.set_options("0,1:0:1:FromPinList")
				   .set_default("0,1");
//	  add_param("PinList","PinString",&sPinList);
	  add_param("Search Direction","string",&sSearch_Direction)
				   .set_comment("Search_Direction")
				   //.set_options("Low2High:High2Low")
				   .set_default("Low2High");
	  add_param("TxFIR.TxMain","int",&iTxMain)
				   .set_default("57");
	  add_param("TxFIR.TxPre1st","int",&iTxPre1st)
				   .set_default("-6");
	  add_param("TxFIR.TxPost1st","int",&iTxPost1st)
				   .set_default("0");
	  add_param("TxFIR.TxPre2nd","int",&iTxPre2nd)
				   .set_default("0");
	  add_param("TxFIR.TxPost2nd","int",&iTxPost2nd)
				   .set_default("0");
	  add_param("UseFixCTLE","string",	&mUseFixCTLE)
				   //.set_options("NO:YES")
				   .set_default("NO");
//	  add_param("UseFixCTLE.CTLEACTGN1","int",&iCTLEACTGN1)
//				   .set_default("7");
//	  add_param("UseFixCTLE.CTLEACTGN2","int",&iCTLEACTGN2)
//				   .set_default("7");
//	  add_param("UseFixCTLE.CTLEACTGN3","int",&iCTLEACTGN3)
//				   .set_default("7");
//	  add_param("UseFixCTLE.CTLEBST1","int",&iCTLEBST1)
//				   .set_default("0");
//	  add_param("UseFixCTLE.CTLEBST2","int",&iCTLEBST2)
//				   .set_default("0");
//	  add_param("UseFixCTLE.CTLEBST3","int",&iCTLEBST3)
//				   .set_default("0");
	  add_param("Search_Low","double",	&dSearchLow)
				   .set_default("0.715");
	  add_param("Search_High","double",	&dSearchHigh)
				   .set_default("0.933");
	  add_param("Search_Step","double",	&dSearchStep)
				   .set_default("0.00625");
	  add_param("PrintLvl[0~8]","int",&iPrintLvl)
				   .set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
				   "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
				   //.set_options("0:1:3:4:7:8")
				   .set_default("3");

}
	void execute()
	{

		//********************** Get Test Condition ****************
		H30_FailBin_Flag.init(0);
		static LANE_DOUBLE vDVDDLowResult;
		static LANE_DOUBLE vDVDDHighResult;
		static MACRO_LANE_SEL MacroLane_Sel;

		static INT iCSR_check;
		static bool CSRVerifyResult;

		INT iCTLEACTGN1;
		INT iCTLEACTGN2;
		INT iCTLEACTGN3;
		INT iCTLEBST1;
		INT iCTLEBST2;
		INT iCTLEBST3;

		stAVS_Verify_ABIST AVS_Verify_ABIST;

//		static STRING mPinList = "";
//	                const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);

//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel, sHiLink30_MacroList,sPinList);

		//=============================================
		// Device Setup
		//=============================================

		d2s_JTAG& jtag = d2s_JTAG::Instance();

		CUSTPARA Custpara = default_CUSTPARA;

		Custpara.TxFIR_USER.iTxMain = iTxMain;
		Custpara.TxFIR_USER.iTxPre1st = iTxPre1st;
		Custpara.TxFIR_USER.iTxPost1st = iTxPost1st;
		Custpara.TxFIR_USER.iTxPre2nd = iTxPre2nd;
		Custpara.TxFIR_USER.iTxPost2nd = iTxPost2nd;

		//=============================================
		// Device Setup
		//=============================================
		SetTxFir(MacroLane_Sel, Custpara);
		LoopBack_Setting(sLoopBackMode, MacroLane_Sel,
				Custpara);

		d2s::d2s_LABEL_BEGIN("MPB_AVS_Verify_ABIST_SetUp_",Global_D2S_Mode);


		selectMacro_MB(MacroLane_Sel);
		DS.rxRegs.SliceID(0).Broadcast(1);
		DS.txRegs.SliceID(0).Broadcast(1);

		/**********Tx Setup*****************/

		EnableTxPrbsGen("PRBS15");
		DS.rxRegs.setcdrfreeze(0x0).Write2DUT(12);
		//				jtag.wait(100 uS);
		jtag.wait(0.0001);
		if (mUseFixCTLE == "YES")
		{
			DS.rxRegs.setctleactgn1(iCTLEACTGN1).Write2DUT(1);
			DS.rxRegs.setctleactgn2(iCTLEACTGN2).Write2DUT(2);
			DS.rxRegs.setctleactgn3(iCTLEACTGN3).Write2DUT(3);
			DS.rxRegs.setctleboostc1(iCTLEBST1).Write2DUT(1);
			DS.rxRegs.setctleboostc2(iCTLEBST2).Write2DUT(2);
			DS.rxRegs.setctleboostc3(iCTLEBST3).Write2DUT(3);
		}
		EnableRxPrbsCheck("PRBS15");

		d2s::d2s_LABEL_END();

		DOUBLE DVDD_Search_Low = dSearchLow;
		DOUBLE DVDD_Search_High = dSearchHigh;
		DOUBLE DVDD_Search_Step = dSearchStep;

		STRING sSpecName = sDPSPinList;

		if (sSearch_Direction == "High2Low")
			AVS_Verify_Search(MacroLane_Sel, vDVDDLowResult, sSpecName,
					"PRBS15", DVDD_Search_Low, DVDD_Search_Step);
		else if (sSearch_Direction == "Low2High")
			AVS_Verify_Search(MacroLane_Sel, vDVDDHighResult, sSpecName,
					"PRBS15", DVDD_Search_High, DVDD_Search_Step);
		else
		{
			//                        cout << "ERROR: incorrect search direction !!!!" << endl;
//			api->info_message("ERROR: incorrect search direction !!!!");
			cout <<"ERROR: incorrect search direction !!!!"<<endl;
			//	  			ERROR_EXIT(TM::EXIT_FLOW);
		}

		//	  		Primary.getLevelSpec().restore();
		//	  		FLUSH(TM::APRM);

		//	  	 ON_FIRST_INVOCATION_END();

		//=============================================
		// JUDGEMENT
		//=============================================
		double High2LowVolt_LimitL = 0.875;
		double High2LowVolt_LimitH = 0.9;
		double Low2HighVolt_LimitL = 1.1;
		double Low2HighVolt_LimitH = 1.10625;
		if (sSearch_Direction == "High2Low")
			HiLink_PerLane_Judge(MacroLane_Sel, "High2LowVolt",
					High2LowVolt_LimitL, vDVDDLowResult, High2LowVolt_LimitH);
		else if (sSearch_Direction == "Low2High")
			HiLink_PerLane_Judge(MacroLane_Sel, "Low2HighVolt",
					Low2HighVolt_LimitL, vDVDDHighResult, Low2HighVolt_LimitH);

		SetTestBin();
	}

};
REGISTER_TESTCLASS("AVS_Verify_ABIST", AVS_Verify_ABIST)

