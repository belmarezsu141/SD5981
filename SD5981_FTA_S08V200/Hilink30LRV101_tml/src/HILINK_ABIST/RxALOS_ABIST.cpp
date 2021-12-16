//for test method API interfaces

#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"


//#include "mapi.hpp"
//#include "../Common_Func/HiLink30_Common_Func.h"
using namespace std;
class RxALOS_ABIST: public TestClass {
public:
	STRING 				mHiLink30_MacroList;
	STRING 				mPinList;
	INT					iPrintLvl;
	INT  				mSwing_H;
	INT  				mSwing_L;
	INT  				mStep;
	INT 				iCTLEACTGN1;
	INT 				iCTLEACTGN2;
	INT 				iCTLEACTGN3;
	INT					iCTLEBST1;
	INT					iCTLEBST2;
	INT					iCTLEBST3;
    STRING              sLoopBackMode;
	STRING				mUseFixCTLE;

	void init() {
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					.set_comment("HiLink30 Macro List for test")
					//.set_options("0,1:FromPinList")
					.set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
		add_param("LoopBackMode","string",&sLoopBackMode)
					//.set_options("PreDriver:Bump:External:Nothing")
					.set_default("External");
		add_param("TxMain_H","int",	&mSwing_H)
					.set_comment("in unit mV")
					.set_default("150");
		add_param("TxMain_L", "int",&mSwing_L)
					.set_comment("in unit mV")
					.set_default("10");
		add_param("UseFixCTLE","string",&mUseFixCTLE)
					//.set_options("NO:YES")
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
					//.set_options("0:1:3:4:7:8")
					.set_default("3");
	}
	void execute() {

		H30_FailBin_Flag.init(0);
		INT iCTLEACTGN1;
		INT iCTLEACTGN2;
		INT iCTLEACTGN3;
		INT iCTLEBST1;
		INT iCTLEBST2;
		INT iCTLEBST3;

//=============================================
// Common definition of TM for offline flag,
// d2s mode, debug mode, test suite name, etc.
//=============================================
//		static	STRING          	sTestsuiteName;
		static INT iOffline;
		static INT iCSR_check;
		static MACRO_LANE_SEL MacroLane_Sel;

		static LANE_DOUBLE Sigdet_LOS_ALL0;
		static LANE_DOUBLE Sigdet_LOS_ALL1;
		static LANE_DOUBLE MinSwing_all0_min;
		static LANE_DOUBLE MinSwing_all1_max;
		static bool CSRVerifyResult;

//		ON_FIRST_INVOCATION_BEGIN();
//=============================================
// Variables and MacroLane initialization
//=============================================
//		GET_SYSTEM_FLAG		("offline",&iOffline);
//		GET_TESTSUITE_NAME	(sTestsuiteName);
//		GET_USER_FLAG		("CSR_atomic_operation",&iCSR_check);
		d2s_JTAG& jtag = d2s_JTAG::Instance();
		// stRxALOS_ABIST& RxALOS_ABIST=H30_RxALOS_30G_ABIST_RxALOS_ABIST;  //5875
		stRxALOS_ABIST& RxALOS_ABIST = H30_RxALOS_24G33024_ABIST_RxALOS_ABIST; //by thy 2021.4.29
//		static STRING mPinList = "";
//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,	&m_TestNumber, THE_END);

//                extern stRxALOS_ABIST H30_RxALOS_30G_ABIST_RxALOS_ABIST; 
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList,mPinList);


//		FlexRelayCtrl();                
//		api->Execute_test("H30_Disconnect_TX_RX_DZ");
		H30_Disconnect_TX_RX_DZ();
//=============================================
// Device Setup
//=============================================
//		D2S_FRAMEWORK;
//		GET_TEST_INFO;

		CUSTPARA Custpara = default_CUSTPARA;
		Custpara.TxFIR_USER.iTxMain = 57; //fix 57 ,need to align fw cal later
		Custpara.TxFIR_USER.iTxPre1st = 0;
		Custpara.TxFIR_USER.iTxPre2nd = 0;
		Custpara.TxFIR_USER.iTxPost1st = 0;
		Custpara.TxFIR_USER.iTxPost2nd = 0;

		/***********************************
		 STEP*. Select loopback mode
		 ************************************/
		LoopBack_Setting(sLoopBackMode, MacroLane_Sel, Custpara);
//		sprintf(label,"RxALOS_SETUP_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
//                
		d2s::d2s_LABEL_BEGIN( "RxALOS_SETUP_", Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);

		DS.rxRegs.SliceID(0).Broadcast(1);
		DS.txRegs.SliceID(0).Broadcast(1);

		EnableTxPrbsGen("PRBS15");

		//EnableAlos(jtag.Context);

		DS.txRegs.settxdrvampctrl(3).Write2DUT(13);

		/****************** RxCTLE Setup *************/ //TODO:
		if (mUseFixCTLE == "YES") {
			DS.rxRegs.setctleactgn1(iCTLEACTGN1).Write2DUT(1);
			DS.rxRegs.setctleactgn2(iCTLEACTGN2).Write2DUT(2);
			DS.rxRegs.setctleactgn3(iCTLEACTGN3).Write2DUT(3);
			DS.rxRegs.setctleboostc1(iCTLEBST1).Write2DUT(1);
			DS.rxRegs.setctleboostc2(iCTLEBST2).Write2DUT(2);
			DS.rxRegs.setctleboostc3(iCTLEBST3).Write2DUT(3);
		}

//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();


		EnableAlos(MacroLane_Sel, jtag.Context);

//=============================================
// Variables definition and initialization
//=============================================

		MinSwing_all0_min.init(-99);
		MinSwing_all1_max.init(-99);

		Custpara.TxFIR_USER.iTxMain = mSwing_H;
//		sprintf(label,"RxALOS_setFIR_ALL0_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));

		d2s::d2s_LABEL_BEGIN( "RxALOS_setFIR_ALL0_",
				Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);
		SetTxFir(Custpara);
//		fr.d2s_LABEL_END();
		d2s::d2s_LABEL_END();


		sigdet_los_check(MacroLane_Sel, Sigdet_LOS_ALL0, "ABIST", "ALL0_CHECK");

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size();
				macroIndex++) {
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
				UINT LaneID = vLane[laneIndex];
//				FOR_EACH_SITE_BEGIN();
//				int site = CURRENT_SITE_NUMBER()-1;
//				FOREACH_ACTIVE_SITE(api)
//				{
//					unsigned int site = api->Get_active_site();
					FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
					if (Sigdet_LOS_ALL0[SiteID][MacroID][LaneID] == 0) //No los detect. PASS
							{
						MinSwing_all0_min[SiteID][MacroID][LaneID] = 1; //1 = PASS
					} else {
						MinSwing_all0_min[SiteID][MacroID][LaneID] = -1; // -1 = FAIL
					}
					FOREACH_ACTIVESITE_END
//				FOR_EACH_SITE_END();
			}
		}


		Custpara.TxFIR_USER.iTxMain = mSwing_L;
//		sprintf(label,"RxALOS_setFIR_ALL1_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		d2s::d2s_LABEL_BEGIN( "RxALOS_setFIR_ALL1_",
				Global_D2S_Mode);
		selectMacro_MB(MacroLane_Sel);
		SetTxFir(Custpara);
		d2s::d2s_LABEL_END();
//		fr.d2s_LABEL_END();
//		TheInst.Wait(0.05);


		sigdet_los_check(MacroLane_Sel, Sigdet_LOS_ALL1, "ABIST", "ALL1_CHECK");


		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size();
				macroIndex++) {
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
				UINT LaneID = vLane[laneIndex];
//				FOR_EACH_SITE_BEGIN();
//				int site = CURRENT_SITE_NUMBER()-1;
//				FOREACH_ACTIVE_SITE(api)
//				{
//					unsigned int site = api->Get_active_site();
				FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				if (Sigdet_LOS_ALL1[SiteID][MacroID][LaneID] == 1) //los detect. PASS
							{
						MinSwing_all1_max[SiteID][MacroID][LaneID] = 1; // 1 = PASS
					} else {
						MinSwing_all1_max[SiteID][MacroID][LaneID] = -1; // -1 = FAIL
					}
					FOREACH_ACTIVESITE_END
//				FOR_EACH_SITE_END();
			}
		}


//		sprintf(label,"RxALOS_DISABLE_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));

		d2s::d2s_LABEL_BEGIN( "RxALOS_DISABLE_", Global_D2S_Mode);
		selectMacro_MB(MacroLane_Sel);
		DS.rxRegs.SliceID(0).Broadcast(1);
		DisableAlos();
		d2s::d2s_LABEL_END();
#if 0
		for(spec_val = mSwing_H; spec_val >= mSwing_L; spec_val -= mStep)
		{
			CUSTPARA custpara = default_CUSTPARA;
			custpara.TxFIR_USER.iTxMain = spec_val;
			custpara.TxFIR_USER.iTxPre1st = 0;
			custpara.TxFIR_USER.iTxPre2nd = 0;
			custpara.TxFIR_USER.iTxPost1st = 0;
			custpara.TxFIR_USER.iTxPost2nd = 0;
			Antiproof_SumFIR(custpara);

			sprintf(label,"RxALOS_setFIR_%f_%f_",Vcoef,Temp);
			fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
			selectMacro_MB(MacroLane_Sel);
			SetTxFir(custpara);
			fr.d2s_LABEL_END();

			//Check whether first step already all LOS
			if (isCheckAll1)
			{
				size_t read_cont = 100;
				sprintf(label,"RxALOS_CheckAll1_%f_%f_",Vcoef,Temp);
				fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));

				jtag.enablePassFailCheckForNextExecution();

				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					selectMacro(MacroID);
					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
						for(size_t read_index = 0; read_index < read_cont; read_index ++)
						{
							DS.rxRegs.ExpectValue(40, 0, 0xBFFF); // getrxsigdetlos() { return (uint)((csr[40] & 0x4000) >> 14); }
						}
					}
				}

				fr.d2s_LABEL_END();

				if (!jtag.hasAllSitesPassed(label))
				{
					isCheckAll1 = false;
				}
			}

			if (!isCheckAll1)
			{
				sigdet_los_check(MacroLane_Sel, Sigdet_LOS_ALL1, Sigdet_LOS_ALL0, "ABIST");

				allfound_all1 = 1;
				allfound_all0 = 1;

				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						FOR_EACH_SITE_BEGIN();
						int site = CURRENT_SITE_NUMBER()-1;
						if ((Sigdet_LOS_ALL1[site][MacroID][LaneID] == 1) && (found_lane_all1[site][MacroID][LaneID] == 0))
						{
							found_lane_all1[site][MacroID][LaneID] = 1;
							MinSwing_all1_max[site][MacroID][LaneID] = spec_val;
						}
						else if (Sigdet_LOS_ALL1[site][MacroID][LaneID] == 0)
						{
							allfound_all1 = 0;
						}

						if ((Sigdet_LOS_ALL0[site][MacroID][LaneID] == 0) && (found_lane_all0[site][MacroID][LaneID] == 0))
						{
							found_lane_all0[site][MacroID][LaneID] = 1;
							if (!isFirstStep)
							{
								MinSwing_all0_min[site][MacroID][LaneID] = spec_val + mStep;
							}
						}
						else if (Sigdet_LOS_ALL0[site][MacroID][LaneID] == 1)
						{
							allfound_all0 = 0;
						}

						MinSwing_Gap[site][MacroID][LaneID] = MinSwing_all0_min[site][MacroID][LaneID] - MinSwing_all1_max[site][MacroID][LaneID];
						FOR_EACH_SITE_END();
					}
				}

				if (allfound_all1 and allfound_all0 and d2s_mode != 1) break;
			}
			isFirstStep = false;
		}
#endif
//		ON_FIRST_INVOCATION_END();
//=============================================
// Datalog
//=============================================
		double LimitL = 1;
		double LimitH = 1;
		HiLink_PerLane_Judge(MacroLane_Sel, "Alos_all0_det", LimitL,
				MinSwing_all0_min, LimitH);
		HiLink_PerLane_Judge(MacroLane_Sel, "Alos_all1_det", LimitL,
				MinSwing_all1_max, LimitH);

		SetTestBin();
	}

};
REGISTER_TESTCLASS("RxALOS_ABIST", RxALOS_ABIST)

