//for test method API interfaces
//#include "mapi.hpp"

#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"


using namespace std;
class VcoLockRange: public TestClass
{
public:
	STRING                          mHiLink30_MacroList;
	STRING                          sRefCLK_MHz;
	INT                             iPll_Select;
	STRING                          sKa;
	STRING                          sKb;
	STRING                          sNa;
	STRING                          sNb;
	INT                             iMDiv;
    INT                             iSdivder;
	INT                         	iRateMode;
	INT                             iDataWidth;
	INT                             iHsClkDistClkSpare_Bit2;
	INT                             iJ_40b;
	INT                             iJ_32b;
	STRING                          sDataRate;
	STRING 				            sHSCLK_GHz;
	STRING                          TestMode;
	STRING                          mCalibrationType;
	INT                             iRefclkBus;
	INT   							mSSC_Generator;
	STRING							mSSCRunMode;
	INT 							mXPON_Mode;
	INT 							mSSC_CDR;
	STRING							sScenario;
	STRING 							mProtocol;
	INT								mSIGDET_ENABLE;
	STRING 							sTXDRV_RESSEL;
	STRING 							sRXCAPBYPASS;
	INT 							iCTLEACTGN1;
	INT 							iCTLEACTGN2;
	INT 							iCTLEACTGN3;
	INT								iCTLEBST1;
	INT								iCTLEBST2;
	INT								iCTLEBST3;
	STRING							mUseFixCTLE;
    STRING                          sPllMclkPreDiv;
    STRING                          sP;
    STRING                          sS;
    INT								iPrintLvl;
	void init()
	{
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					.set_comment("HiLin30 Macro List for test")
					//.setOptions("0,1")
					.set_default("0,1");
		add_param("Pll_Select","int",&iPll_Select)
					.set_comment("iPll_Select")
					//.setOptions("0:1:-1")
					.set_default("0");
		add_param("RefclkBus","int",&iRefclkBus)
					//.setOptions("0:1:-1")
					.set_default("-1");
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
		STRING sRefCLK_MHz;
		STRING sKa;
		STRING sKb;
		STRING sNa;
		STRING sNb;
		INT iMDiv;
		INT iSdivder;
		INT iRateMode;
		INT iDataWidth;
		INT iHsClkDistClkSpare_Bit2;
		INT iJ_40b;
		INT iJ_32b;
		STRING sDataRate;
		STRING sHSCLK_GHz;
		STRING TestMode;
		STRING mCalibrationType;
		//	INT                             iRefclkBus;
		INT mSSC_Generator;
		STRING mSSCRunMode;
		INT mXPON_Mode;
		INT mSSC_CDR;
		STRING sScenario;
		STRING mProtocol;
		INT mSIGDET_ENABLE;
		STRING sTXDRV_RESSEL;
		STRING sRXCAPBYPASS;
		INT iCTLEACTGN1;
		INT iCTLEACTGN2;
		INT iCTLEACTGN3;
		INT iCTLEBST1;
		INT iCTLEBST2;
		INT iCTLEBST3;
		STRING mUseFixCTLE;
		STRING sPllMclkPreDiv;
		STRING sP;
		STRING sS;
		//    INT								iPrintLvl;

		INT iDebugAnalog;

//		static	STRING          	sTestsuiteName;
		static INT iCSR_check;
		static MACRO_LANE_SEL MacroLane_Sel;

		static vector<UINT> vPllId;
		static map<UINT, map<UINT, MACRO_INT> > mResultPerIndex;
		static map<UINT, MACRO_DOUBLE> mHoleNum;
		static map<UINT, MACRO_DOUBLE> mMinVCO;
		static map<UINT, MACRO_DOUBLE> mMaxVCO;

//		ON_FIRST_INVOCATION_BEGIN();

		//=============================================
		// Variables definition and initialization
		//=============================================

//		GET_TESTSUITE_NAME	(sTestsuiteName);
//		GET_TESTFLOW_FLAG	("debug_analog",&iDebugAnalog);
//		GET_USER_FLAG		("CSR_atomic_operation",&iCSR_check);

		static STRING mPinList = "";
//		const char * sTestsuiteName = api->Get_current_test_name();
		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
		string strTestsuiteName = sTestsuiteName;
//		api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER,&m_TestNumber, THE_END);
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

		static stVcoLockRange sVcoLockRange;


		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList);
		UINT macroNum = MacroLane_Sel.size();

//		FlexRelayCtrl();

		DOUBLE_VECTOR vKa;
		INT_VECTOR vKb;
		INT_VECTOR vNb;
		INT_VECTOR vP;
		INT_VECTOR vS;
		INT_VECTOR vNa;
		INT_VECTOR vJ32_b;
		INT_VECTOR vJ40_b;
		INT_VECTOR vPll_Select;
		DOUBLE_VECTOR vHSCLK_GHz;
		DOUBLE_VECTOR vRefCLK_MHz;
		DOUBLE_VECTOR vDataRate;
		INT_VECTOR vRefclkBus;
		INT_VECTOR vPllMclkPreDiv;

		sDataRate =
				"21.875,23.125,24.375,25.625,27.5,28.125,29.375,30.625,31.875,15,15.625,10.9375,32.5,32.5";
		sKa = "1,1,1,1,1,1,1,1,1,1.5,2,2,1,1";
		sKb = "1,1,1,1,1,1,1,1,1,1,1,1,1,1";
		sHSCLK_GHz =
				"10.9375,11.5625,12.1875,12.8125,13.75,14.0625,14.6875,15.3125,15.9375,7.5,7.8125,5.46875,16.25,16.25";
		sRefCLK_MHz =
				"156.25,156.25,156.25,156.25,156.25,156.25,156.25,156.25,156.25,156.25,156.25,156.25,156.25,156.25";
		sNb = "35,37,39,41,44,45,47,49,51,24,25,35,52,104";
		sNa = "2,2,2,2,2,2,2,2,2,2,2,1,2,1";
		sP = "6,7,7,7,8,8,9,9,9,4,4,6,10,21";
		sS = "5,3,5,7,6,7,5,7,9,2,3,5,6,14";

		iSdivder = 1;
		iMDiv = 1;
		iRateMode = 0;
		iDataWidth = 0;
		iHsClkDistClkSpare_Bit2 = 0;
		iJ_40b = 0;
		iJ_32b = 0;
		mCalibrationType = "SS+CS";

		parseListOfDouble(sRefCLK_MHz, vRefCLK_MHz, ',');
		parseListOfDouble(sKa, vKa, ',');
		parseListOfInt(sKb, vKb, ',');
		parseListOfDouble(sHSCLK_GHz, vHSCLK_GHz, ',');
		parseListOfDouble(sDataRate, vDataRate, ',');
		parseListOfInt(sNb, vNb, ',');
		parseListOfInt(sNa, vNa, ',');
		parseListOfInt(sP, vP, ',');
		parseListOfInt(sS, vS, ',');

		//PllMclkPreDivm, J_32b and J_40b should be default value is lockrange test
		vPllMclkPreDiv.resize(macroNum, 1); //Register default value
		vJ40_b.resize(macroNum, 0); //Register default value
		vJ32_b.resize(macroNum, 0); //Register default value
		vPll_Select.resize(macroNum, iPll_Select);
		vRefclkBus.resize(macroNum, iRefclkBus);

		INT refCLKNum = vRefCLK_MHz.size();
		ARRAY_I VcoLockResult;

		// INIT VCOResult and ILOResult

		// vPllId init.
		vPllId.clear();
		switch (iPll_Select)
		{
		case 0: // Pll0
			vPllId.push_back(0);
			break;
		case 1: // Pll1
			vPllId.push_back(1);
			break;
		case -1: // Pll0&1
			vPllId.push_back(0);
			vPllId.push_back(1);
			break;
		default:
//			cout<<"ERROR: Incorrect Pllsel set!!! Please Check this parameter!!!"<<endl;
//			api->Info_message("ERROR: Incorrect Pllsel set!!! Please Check this parameter!!!");

			cout <<"ERROR: Incorrect Pllsel set!!! Please Check this parameter!!!"<<endl;
//			ERROR_EXIT(TM::ABORT_FLOW);
//			return;
		}

		TxFIR_SETTING TxFIR_USER =
		{ 0, 0, 63, 0, 0 };
		RxCTLE_SETTING RxCTLE_USER =
		{
		{ iCTLEACTGN1, iCTLEACTGN2, iCTLEACTGN3 },
		{ iCTLEBST1, iCTLEBST2, iCTLEBST3 }, };

		// judge value init
		for (UINT iPllIdIndex = 0; iPllIdIndex < vPllId.size(); iPllIdIndex++)
		{

			for (int idx = 0; idx < refCLKNum; idx++)
			{
				mResultPerIndex[vPllId[iPllIdIndex]][idx].init(0);
			}

			mHoleNum[vPllId[iPllIdIndex]].init(0);
			mMinVCO[vPllId[iPllIdIndex]].init(999);
			mMaxVCO[vPllId[iPllIdIndex]].init(0);
		}

		STRING mPort1 = "pCLK_HL30";
		STRING mSpec = "Frefclk";
		STRING sSpecName1, sSpecSetName1;

		//=============================================
		// Device Setup
		//=============================================

		for (INT refIndex = 0; refIndex < refCLKNum; refIndex++)
		{

			hout(DETAIL) << "Current ref freq= " << dec << vRefCLK_MHz[refIndex]
					<< "MHz" << endl;

//			D2S_FRAMEWORK;
			//READ_ALL_CSR;

			MACRO_INT mCS_Cal_MacroResult;
			MACRO_INT mCsCalVcoLockPerMacro;
			MACRO_INT mDS_Cal_MacroResult;

			mCS_Cal_MacroResult.init(0);
			mCsCalVcoLockPerMacro.init(0);
			mDS_Cal_MacroResult.init(0);

			//New testmethod begin

			CUSTPARA CUSTpara;
			CUSTpara.Data_Rate = vDataRate[refIndex];
			CUSTpara.RateMode = iRateMode;
			CUSTpara.DataWidth = iDataWidth;
			CUSTpara.PllSel = iPll_Select;
			CUSTpara.TxFIR_USER = TxFIR_USER;
			CUSTpara.RxCTLE_USER = RxCTLE_USER;
			CUSTpara.Coreclk_sel = "disable";
			CUSTpara.GB_Enable = 1;
			SSPARA SSpara;
			SSpara.RefclkBus = iRefclkBus;
			SSpara.SDiv = iSdivder;
			SSpara.RefclkMHz = vRefCLK_MHz[refIndex];
			SSpara.RefclkMHz2 = vRefCLK_MHz[refIndex];

			CSPARA CSpara;
			CSpara.KaDiv = vKa[refIndex];
			CSpara.KbDiv = vKb[refIndex];
			CSpara.NaDiv = vNa[refIndex];
			CSpara.NbDiv = vNb[refIndex];
			CSpara.Pvalue = vP[refIndex];
			CSpara.Svalue = vS[refIndex];
			CSpara.Mdiv = iMDiv;
			CSpara.PllMclkPreDiv = 0; //For lockrange this is fixed
			CSpara.HSCLK = vHSCLK_GHz[refIndex];
			CSpara.J32bdiv = iJ_40b; //default value
			CSpara.J40bdiv = iJ_32b; //default value
			CSpara.HsClkDistClkSpare_Bit2 = iHsClkDistClkSpare_Bit2;

			if (iDebugAnalog)
			{
				hout(DETAIL) << "Dump info Check Begin" << endl;

				hout(DETAIL) << "SSpara.RefclkMHz = " << dec << SSpara.RefclkMHz
						<< endl;
				hout(DETAIL) << "CUSTpara.PllSel = " << dec << CUSTpara.PllSel
						<< endl;
				hout(DETAIL) << "SSpara.SDiv = " << dec << SSpara.SDiv << endl;
				hout(DETAIL) << "CSpara.Mdiv = " << dec << CSpara.Mdiv << endl;
				hout(DETAIL) << "CUSTpara.RateMode = " << dec
						<< CUSTpara.RateMode << endl;
				hout(DETAIL) << "CUSTpara.DataWidth = " << dec
						<< CUSTpara.DataWidth << endl;
				hout(DETAIL) << "CSpara.KaDiv = " << dec << CSpara.KaDiv
						<< endl;
				hout(DETAIL) << "CSpara.KbDiv = " << dec << CSpara.KbDiv
						<< endl;
				hout(DETAIL) << "CSpara.HSCLK =" << dec << CSpara.HSCLK << endl;
				hout(DETAIL) << "CSpara.NaDiv = " << dec << CSpara.NaDiv
						<< endl;
				hout(DETAIL) << "CSpara.NbDiv = " << dec << CSpara.NbDiv
						<< endl;
				hout(DETAIL) << "CSpara.Pvalue = " << dec << CSpara.Pvalue
						<< endl;
				hout(DETAIL) << "CSpara.Svalue = " << dec << CSpara.Svalue
						<< endl;

				hout(DETAIL) << "Dump info Check end" << endl << endl;
			}
			//New testmethod end

			if (refIndex == 0)
			{
				HiLink30_FW_CAL(MacroLane_Sel, CUSTpara, SSpara, CSpara,
						mCS_Cal_MacroResult, mCsCalVcoLockPerMacro,
						mDS_Cal_MacroResult, mCalibrationType,
						FullCalPara.BypassCal, 1);
			}
			else
			{
				HiLink30_FW_CAL(MacroLane_Sel, CUSTpara, SSpara, CSpara,
						mCS_Cal_MacroResult, mCsCalVcoLockPerMacro,
						mDS_Cal_MacroResult, mCalibrationType,
						FullCalPara.BypassCal, 0);
			}
			DOUBLE dCurrentVCO = vRefCLK_MHz[refIndex] * vNa[refIndex]
					* vNb[refIndex] * vKa[refIndex] / iMDiv / 1000;

//			FOREACH_ACTIVE_SITE(api)
//			{
//				unsigned int SiteID = api->Get_active_site();
				FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

				for (UINT iPllIdIndex = 0; iPllIdIndex < vPllId.size();
						iPllIdIndex++)
				{
					UINT PllID = vPllId[iPllIdIndex];
					for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size();
							macroIndex++)
					{
						UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

						if (mCS_Cal_MacroResult[SiteID][MacroID] == 1)
						{
							if ((PllID == 0 && (mCsCalVcoLockPerMacro[SiteID][MacroID] == 1 || mCsCalVcoLockPerMacro[SiteID][MacroID] == 2))
									|| (PllID == 1 && (mCsCalVcoLockPerMacro[SiteID][MacroID] == 1
													|| mCsCalVcoLockPerMacro[SiteID][MacroID] == 3)))
								mResultPerIndex[PllID][refIndex][SiteID][MacroID] = 1;
							else
								;
						}

						if (mResultPerIndex[PllID][refIndex][SiteID][MacroID] == 1)
						{
							if (dCurrentVCO <= mMinVCO[PllID][SiteID][MacroID])
							{
								mMinVCO[PllID][SiteID][MacroID] = dCurrentVCO;
							}
							if (dCurrentVCO > mMaxVCO[PllID][SiteID][MacroID])
							{
								mMaxVCO[PllID][SiteID][MacroID] = dCurrentVCO;
							}
						}
					}
				}
				FOREACH_ACTIVESITE_END
		}

		// HoleNum Cal
//		FOREACH_ACTIVE_SITE(api)
//		{
//			unsigned int SiteID = api->Get_active_site();
			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

			for (UINT iPllIdIndex = 0; iPllIdIndex < vPllId.size();
					iPllIdIndex++)
			{
				UINT PllID = vPllId[iPllIdIndex];
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size();
						macroIndex++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					for (INT refIndex = 0; refIndex < refCLKNum; refIndex++)
					{
						DOUBLE dCurrentVCO = vRefCLK_MHz[refIndex]
								* vNa[refIndex] * vNb[refIndex] * vKa[refIndex]
								/ iMDiv / 1000;

						if ((mResultPerIndex[PllID][refIndex][SiteID][MacroID]
								== 0)
								&& (dCurrentVCO
										>= mMinVCO[PllID][SiteID][MacroID])
								&& (dCurrentVCO
										<= mMaxVCO[PllID][SiteID][MacroID]))
						{
							mHoleNum[PllID][SiteID][MacroID]++;
						}
					}
				}

				ostringstream plot_refclk_lock;
				plot_refclk_lock << "========Site" << SiteID
						<< "_VCOclkLockRange_hole_Pll" << PllID
						<< "_plot========";
				for (UINT macroIndex = 0; macroIndex < macroNum; macroIndex++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					plot_refclk_lock << "\nMacro_" << MacroID
							<< " REFCLK_LOCK_point:\t";
					for (INT refIndex = 0; refIndex < refCLKNum; refIndex++)
					{
						if (mResultPerIndex[PllID][refIndex][SiteID][MacroID])
							plot_refclk_lock << "L ";
						else
							plot_refclk_lock << "X ";
					}
				}
				plot_refclk_lock << endl;
//			PUT_DATALOG (plot_refclk_lock.str());
			}
			FOREACH_ACTIVESITE_END

//		ON_FIRST_INVOCATION_END();
		//=============================================
		// Judgement
		//=============================================

		for (UINT iPllIdIndex = 0; iPllIdIndex < vPllId.size(); iPllIdIndex++)
		{
			UINT PllID = vPllId[iPllIdIndex];

			ostringstream sPllID;
			sPllID << PllID;
			double LimitL_MinFreq = 0;
			double LimitH_MinFreq = 10.9375;
			double LimitL_MaxFreq = 16.25;
			double LimitH_MaxFreq = 100;
			double LimitL = 0;
			double LimitH = 0;
			HiLink_PerMacro_Judge(MacroLane_Sel,
					"VCO_MinFreqPll" + sPllID.str(), LimitL_MinFreq,
					mMinVCO[PllID], LimitH_MinFreq);
			HiLink_PerMacro_Judge(MacroLane_Sel,
					"VCO_MaxFreqPll" + sPllID.str(), LimitL_MaxFreq,
					mMaxVCO[PllID], LimitH_MaxFreq);
			HiLink_PerMacro_Judge(MacroLane_Sel,
					"VCO_HoleNumPll" + sPllID.str(), LimitL, mHoleNum[PllID],
					LimitH);
		}

		SetTestBin ();

	}

};
REGISTER_TESTCLASS("VcoLockRange", VcoLockRange)

