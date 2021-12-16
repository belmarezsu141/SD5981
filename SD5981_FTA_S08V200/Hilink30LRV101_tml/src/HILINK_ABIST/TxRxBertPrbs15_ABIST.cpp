//for test method API interfaces
//#include "mapi.hpp"
//using namespace std;
//using namespace V93kLimits;

#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"


using namespace std;

class TxRxBertPrbs15_ABIST: public TestClass
{
public:

	STRING 				mHiLink30_MacroList;
	STRING 				mPinList;
	INT                 iDataWidth;
	INT                 iRateMode;
	INT	 				iTxMain;
	INT					iTxPre1st;
	INT					iTxPost1st;
	INT                 iTxPre2nd;
	INT                 iTxPost2nd;
	INT 				iCTLEACTGN1;
	INT 				iCTLEACTGN2;
	INT 				iCTLEACTGN3;
	INT                 iCTLEACTGN4;
	INT					iCTLEBST1;
	INT					iCTLEBST2;
	INT					iCTLEBST3;
	DOUBLE 				mPPMOffset;
	STRING              sLoopBackMode;
	STRING 				mUseFixCTLE;
	INT					iPrintLvl;
	void init()
	{

		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
							.set_comment("HiLink30 Macro List for test")
							//.setOptions("0,1:0:1:FromPinList")
							.set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
		add_param("LoopBackMode","string",&sLoopBackMode)
					//.setOptions("PreDriver:Bump:External")
					.set_default("Bump");
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
		add_param("RateMode","int",&iRateMode)
					.set_default("0");
		add_param("DataWidth","int",&iDataWidth)
					.set_default("0");
		add_param("FreqOffset_PPM","double",&mPPMOffset)
					.set_default("100");
		add_param("UseFixCTLE","string",&mUseFixCTLE)
					//.setOptions("YES:NO")
					.set_default("NO");
//		add_param("UseFixCTLE.CTLEACTGN1","int",&iCTLEACTGN1)
//					.set_default("7");
//		add_param("UseFixCTLE.CTLEACTGN2","int",&iCTLEACTGN2)
//					.set_default("7");
//		add_param("UseFixCTLE.CTLEACTGN3","int",&iCTLEACTGN3)
//					.set_default("7");
//		add_param("UseFixCTLE.CTLEBST1","int",&iCTLEBST1)
//					.set_default("0");
//		add_param("UseFixCTLE.CTLEBST2","int",&iCTLEBST2)
//					.set_default("0");
//		add_param("UseFixCTLE.CTLEBST3","int",&iCTLEBST3)
//					.set_default("0");
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
		static LANE_DOUBLE vTXErrorCount;
		static LANE_DOUBLE vRXErrorCount;
		static INT iCSR_check;
//		static STRING          	sTestsuiteName;
		static MACRO_LANE_SEL MacroLane_Sel;
		vector<ARRAY_D> FindFlag;
		INT iDebugAnalog;
		static bool CSRVerifyResult;

		int iCTLEACTGN1;
		int iCTLEACTGN2;
		int iCTLEACTGN3;
		int iCTLEACTGN4;
		int iCTLEBST1;
		int iCTLEBST2;
		int iCTLEBST3;

//		ON_FIRST_INVOCATION_BEGIN();

		//=============================================
		// Variables definition and initialization
		//=============================================
//		GET_TESTSUITE_NAME	(sTestsuiteName);
//		GET_TESTFLOW_FLAG	("debug_analog",&iDebugAnalog);
//		GET_USER_FLAG		("CSR_atomic_operation",&iCSR_check);

//		static STRING mPinList = "";
//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);

		// stTxRxBertPrbs15_ABIST& TxRxBertPrbs15_ABIST=SSbandGap_SSBandGap;
		stTxRxBertPrbs15_ABIST TxRxBertPrbs15_ABIST;
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();


		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel,mHiLink30_MacroList, mPinList);

//		FlexRelayCtrl();

		Stress_Setting Stress_Set;
		CUSTPARA Custpara;

		Custpara.TxFIR_USER.iTxMain = iTxMain;
		Custpara.TxFIR_USER.iTxPre1st = iTxPre1st;
		Custpara.TxFIR_USER.iTxPost1st = iTxPost1st;
		Custpara.TxFIR_USER.iTxPre2nd = iTxPre2nd;
		Custpara.TxFIR_USER.iTxPost2nd = iTxPost2nd;
		Custpara.RxCTLE_USER.Gain[0] = iCTLEACTGN1;
		Custpara.RxCTLE_USER.Gain[1] = iCTLEACTGN2;
		Custpara.RxCTLE_USER.Gain[2] = iCTLEACTGN3;
		Custpara.RxCTLE_USER.Gain[3] = iCTLEACTGN4;
		Custpara.RxCTLE_USER.Boost[0] = iCTLEBST1;
		Custpara.RxCTLE_USER.Boost[1] = iCTLEBST2;
		Custpara.RxCTLE_USER.Boost[2] = iCTLEBST3;

		//=============================================
		// Device Setup
		//=============================================
//		D2S_FRAMEWORK;
//		GET_TEST_INFO;
		d2s_JTAG& the_jtag = d2s_JTAG::Instance();

//		LoopBack_Setting(api,sLoopBackMode,MacroLane_Sel,Custpara);

		d2s::d2s_LABEL_BEGIN( "MPB_TXRXBERTPRBS15_SETUP1_",
				Global_D2S_Mode);
		selectMacro_MB(MacroLane_Sel);

		DS.rxRegs.SliceID(0).Broadcast(1);
		DS.txRegs.SliceID(0).Broadcast(1);
		DS.rxExtRegs.SliceID(0).Broadcast(1);
		DS.clkRegs.SliceID(0).Broadcast(1);

		//add for ttr
		DS.txRegs.settxrxserlpbken(0x0).Write2DUT(35);
		//end

		EnableTxPrbsGen("PRBS15");
//                EnableTxPrbsGen(api,"CUSTOMER_PATTERN");

		/******************Rx Setup*************/

//		DS.rxRegs.setrxratemode(iRateMode)
//				 .setrxdwidth(iDataWidth)
//				 .Write2DUT(12);
		if (mUseFixCTLE == "YES")
		{
			DS.rxRegs.setctleactgn1(iCTLEACTGN1).Write2DUT(1);
			DS.rxRegs.setctleactgn2(iCTLEACTGN2).Write2DUT(2);
			DS.rxRegs.setctleactgn3(iCTLEACTGN3).Write2DUT(3);
			DS.rxRegs.setctleboostc1(iCTLEBST1).Write2DUT(1);
			DS.rxRegs.setctleboostc2(iCTLEBST2).Write2DUT(2);
			DS.rxRegs.setctleboostc3(iCTLEBST3).Write2DUT(3);
		}
		DS.rxRegs.setcdrfreeze(0x0).Write2DUT(12);
		the_jtag.wait(0.0001);
		DS.rxRegs.setcdrfreeze(0x1).Write2DUT(12);
		the_jtag.wait(0.0001);
		EnableRxPrbsCheck("PRBS7");

		d2s::d2s_LABEL_END();

//                //.......................................................... print txrx bert bertprbes15 begining..........................................//
//                d2s_JTAG& jtag = d2s_JTAG::Instance();
//
//                d2s::d2s_LABEL_BEGIN( "Read_vTXVerifyResult", Global_D2S_Mode);       //D2S LEARANING
//
//                for (uint iMacroIndex=0;iMacroIndex<MacroLane_Sel.size();iMacroIndex++)                   //Macrolane_sel total = 24
//		{
//			selectMacro(MacroLane_Sel[iMacroIndex].MacroID);                                  // select macrolane
//			for (uint iLaneIndex=0;iLaneIndex<MacroLane_Sel[iMacroIndex].vLane.size();iLaneIndex++)                     //lane for loop
//			{
//				DS.rxRegs.MacroID(MacroLane_Sel[iMacroIndex].MacroID).SliceID(MacroLane_Sel[iMacroIndex].vLane[iLaneIndex]).Broadcast(0);   // register write for broadcast
//				DS.txRegs.MacroID(MacroLane_Sel[iMacroIndex].MacroID).SliceID(MacroLane_Sel[iMacroIndex].vLane[iLaneIndex]).Broadcast(0);   // register write for broadcast
////                                DS.rxRegs.ExpectValue(20,0x0000,0x0000);
//                                char IDstring0[128] = "";  
//                                char IDstring1[128] = "";  //id define
//                                sprintf (IDstring0,"dprbsgenen_csr0_onMacro%ionLane%i",MacroLane_Sel[iMacroIndex].MacroID,MacroLane_Sel[iMacroIndex].vLane[iLaneIndex]);
//                                DS.txRegs.Read2IDString(4,IDstring0);   
//                                sprintf (IDstring1,"dTXVerifyResult_csr0_onMacro%ionLane%i",MacroLane_Sel[iMacroIndex].MacroID,MacroLane_Sel[iMacroIndex].vLane[iLaneIndex]);
//                                DS.rxRegs.Read2IDString(20,IDstring1);   //read DS.rxregs
////                                jtag.read(0x1fffe>>1,IDstring);
//			}
//		}
//                d2s::d2s_LABEL_END();
//                
//                
//
//                LANE_DOUBLE dTXVerifyResult;   
//                LANE_DOUBLE dprbsgenen; 
//                FOREACH_ACTIVE_SITE(api) {
//                   unsigned int SiteID = api->Get_active_site();    
//                    for (uint iMacroIndex=0;iMacroIndex<MacroLane_Sel.size();iMacroIndex++)  //MacroLane_Sel.size();
//                    {
//                        UINT MacroID = MacroLane_Sel[iMacroIndex].MacroID;
//                        for (uint iLaneIndex=0;iLaneIndex<MacroLane_Sel[iMacroIndex].vLane.size();iLaneIndex++)   //iLaneIndex<MacroLane_Sel[iMacroIndex].vLane.size()
//                        {
//                            UINT LaneID = MacroLane_Sel[iMacroIndex].vLane[iLaneIndex];   //LaneID
//                            char IDstring0[128] = "";  
//                            char IDstring1[128] = "";  //id define
//                            sprintf (IDstring0,"dprbsgenen_csr0_onMacro%ionLane%i",MacroLane_Sel[iMacroIndex].MacroID,MacroLane_Sel[iMacroIndex].vLane[iLaneIndex]);
//                            sprintf (IDstring1,"dTXVerifyResult_csr0_onMacro%ionLane%i",MacroLane_Sel[iMacroIndex].MacroID,MacroLane_Sel[iMacroIndex].vLane[iLaneIndex]);
//                            
//                            uint val0 = (UINT)jtag.getReadValue(IDstring0);   //val cap data 
//                            uint val1 = (UINT)jtag.getReadValue(IDstring1);   //val cap data
//                            dprbsgenen[SiteID][MacroID][LaneID]=HILINK_Regs_Base::get_bits(val0,DS.txRegs.REG_INFO.prbsgenen());   // print result
//                            dTXVerifyResult[SiteID][MacroID][LaneID]=HILINK_Regs_Base::get_bits(val1,DS.rxRegs.REG_INFO.prbserr());   // print result
//                            api->Info_message("dTXVerifyResult[%d][%d][%d]= %f",SiteID,MacroID,LaneID,dTXVerifyResult[SiteID][MacroID][LaneID]);
//                            api->Info_message("dprbsgenen[%d][%d][%d]= %f",SiteID,MacroID,LaneID,dprbsgenen[SiteID][MacroID][LaneID]);
//                            api->Info_message("prbsgenen_val= %u",val0);
//                            api->Info_message("TXVerifyResult_val= %u",val1);
//                        }
//                   }                
//                }
//                
//                //.......................................................... print txrx bert bertprbes15 ending..........................................//

		//=============================================
		//Verify TX Bert
		//=============================================

		LANE_DOUBLE vTXVerifyResult;

		hout(DETAIL)<< "=================TX FoolProofReadBert Begin=================="<< endl;
		if(PrintDebugEn) cout<< "=================TX FoolProofReadBert Begin=================="<< endl;

		Read_Bert(MacroLane_Sel, vTXVerifyResult, "ABIST", true, "", 0,0.001);   //for test TX, send15 to get7, so must have error


		hout(DETAIL)<< "=================TX FoolProofReadBert End=================="<< endl;
		if(PrintDebugEn) cout<< "=================TX FoolProofReadBert End=================="<< endl;

//		sprintf(label,"MPB_TXRXBERTPRBS15_SETUP2_%f_%f",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN( "MPB_TXRXBERTPRBS15_SETUP2_",	Global_D2S_Mode);


		selectMacro_MB(MacroLane_Sel);
		DS.rxRegs.SliceID(0).Broadcast(1);

		EnableRxPrbsCheck("PRBS15");
//                        EnableRxPrbsCheck(api,"CUSTOMER_PATTERN");
//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();

		//.......................................................... ReadBackRegister ..........................................//
//                 api ->sleep(1);
//                 ALL_CSR_ReadBack_TO_FILE_Debug(api,MacroLane_Sel,"After_TXBertResult");
		//.......................................................... ReadBackRegister..........................................//

		//=============================================
		//measurement
		//=============================================
		hout(DETAIL) << "=================TX ReadBert Begin=================="<< endl;
		if(PrintDebugEn) cout<<"=================TX ReadBert Begin=================="<< endl;
		Read_Bert( MacroLane_Sel, vTXErrorCount, "ABIST", false, "", 0,0.01); //Bertwait 10 ms   //for test TX,  send15 to get15, so must have no error

		hout(DETAIL) << "=================TX ReadBert End=================="<< endl;
		if(PrintDebugEn) cout<<"=================TX ReadBert End=================="<< endl;
//		FOR_EACH_SITE_BEGIN();
//			INT SiteID = CURRENT_SITE_NUMBER() - 1;
//		FOREACH_ACTIVE_SITE(api)
//		{
//			unsigned int SiteID = api->Get_active_site();
			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size();
					macroIndex++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++)
				{
					UINT LaneID = vLane[laneIndex];
					if (vTXVerifyResult[SiteID][MacroID][LaneID] == 0)
					{
						vTXErrorCount[SiteID][MacroID][LaneID] = -1;
					}
				}
			}
			FOREACH_ACTIVESITE_END

		/***************************Tx Bert Finish***************************/
		/***************************Rx Bert Begin****************************/

//		sprintf(label,"MPB_TXRXBERTPRBS15_PPMSETUP_%f_%f",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN( "MPB_TXRXBERTPRBS15_PPMSETUP_",
				Global_D2S_Mode);
		selectMacro_MB(MacroLane_Sel);
		DS.rxRegs.SliceID(0).Broadcast(1);
		DS.txRegs.SliceID(0).Broadcast(1);
		DS.clkRegs.SliceID(0).Broadcast(1);

		//*******************************************************
		// Keep CDR unfreeze and insert ~100 PPM frequecy offset;
		//*******************************************************
		int iPpmgen = FreqOffset(mPPMOffset);

		Stress_Set.jitcontrol = 0;			//Normal mode
		Stress_Set.ppmgen = iPpmgen;
		Stress_Set.jitFreq = 0;
		Stress_Set.jitamp = 0;

		SetTxBistPpmJitter( Stress_Set);
//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();

		//=============================================
		//Verify RX Bert
		//=============================================

		LANE_DOUBLE vRXVerifyResult;
		hout(DETAIL)<< "=================Rx FoolProofReadBert Begin=================="<< endl;
		//cout<< "=================Rx FoolProofReadBert Begin=================="<< endl;

		Read_Bert( MacroLane_Sel, vRXVerifyResult, "ABIST", true, "", 0,0.001);//for test RX, change CDR state  send15 to get15, so must have no error

		hout(DETAIL)<< "=================Rx FoolProofReadBert End=================="<< endl;
		//cout<< "=================Rx FoolProofReadBert End=================="<< endl;

//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN( "MPB_TXRXBERTPRBS15_PPMSETUP_",
				Global_D2S_Mode);
		selectMacro_MB(MacroLane_Sel);
		DS.rxRegs.SliceID(0).Broadcast(1);
		DS.rxRegs.setcdrfreeze(0x0).Write2DUT(12);
		the_jtag.wait(0.0001);
//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();
		//=============================================
		//measurement
		//=============================================

		hout(DETAIL) << "=================Rx ReadBert Begin=================="<< endl;

		Read_Bert( MacroLane_Sel, vRXErrorCount, "ABIST", false, "", 0, 0.01);

		hout(DETAIL) << "=================Rx ReadBert End=================="<< endl;

//		FOR_EACH_SITE_BEGIN();
//			INT SiteID = CURRENT_SITE_NUMBER() - 1;
//		FOREACH_ACTIVE_SITE(api)
//		{
//			unsigned int SiteID = api->Get_active_site();
			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size();
					macroIndex++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++)
				{
					UINT LaneID = vLane[laneIndex];
					if (vRXVerifyResult[SiteID][MacroID][LaneID] == 0)
					{
						vRXErrorCount[SiteID][MacroID][LaneID] = -1;
					}
				}
			}
			FOREACH_ACTIVESITE_END

//		sprintf(label,"MPB_TXRXBERTPRBS15_PPMRESTORE_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN("MPB_TXRXBERTPRBS15_PPMRESTORE_", Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);
		DS.txRegs.SliceID(0).Broadcast(1);

		//*******************************************************
		//Rstore all setting;
		//*******************************************************
		//INT ppmgen = FreqOffset(iRateMode, iDataWidth, mPPMOffset);
		DS.txRegs.settxalignmode(3).Write2DUT(2);
		DS.txRegs.setkfactor(0).setjitppmctrl(0) //Normal mode;
		.setppmgen(0).setjitfreq(0).setjitamp(0).Write2DUT(3);
//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();

//		ON_FIRST_INVOCATION_END();
		//=============================================
		// Datalog
		//=============================================
		double LimitL = 0;
		double LimitH = 0;
		HiLink_PerLane_Judge( MacroLane_Sel, "Tx_Err_Cnt", LimitL,
				vTXErrorCount, LimitH);
		HiLink_PerLane_Judge( MacroLane_Sel, "Rx_Err_Cnt", LimitL,
				vRXErrorCount, LimitH);

		SetTestBin ();
	}

};
REGISTER_TESTCLASS("TxRxBertPrbs15_ABIST", TxRxBertPrbs15_ABIST)

