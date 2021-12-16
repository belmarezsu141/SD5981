//for test method API interfaces
//#include "mapi.hpp"

#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"


class RxStressAll_ABIST: public TestClass{
public:
	STRING 				mHiLink30_MacroList;
	STRING 				mPinList;
	INT	 				iTxMain;
	INT					iTxPre1st;
	INT					iTxPost1st;
	INT					iTxPre2nd;
	INT					iTxPost2nd;
	DOUBLE 				mDataRate;
	STRING 				mEyeScope;
    STRING              sLoopBackMode;
	DOUBLE 				JitterAmpRequired;
	DOUBLE 				mFreqOffset;
	INT                 iDataWidth;
	INT                 iRateMode;
	INT 				iCTLEACTGN1;
	INT 				iCTLEACTGN2;
	INT 				iCTLEACTGN3;
	INT					iCTLEBST1;
	INT					iCTLEBST2;
	INT					iCTLEBST3;
	STRING				mUseFixCTLE;
	DOUBLE				dRefCLK_MHz;
	DOUBLE				dRefCLK_MHz2;
	STRING				sEyeDiagMethod;
	INT					iPrintLvl;
	void init(){
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					 .set_comment("HiLink30 Macro List for test")
					 //.set_options("0,1:FromPinList")
					 .set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
		add_param("LoopBackMode","string",&sLoopBackMode)
					//.set_options("PreDriver:Bump:External:Nothing")
					.set_default("External");
		add_param("RefCLK_MHz","double",&dRefCLK_MHz)
					.set_comment("RefCLK_MHz")
					//.set_options("100:156.25")
					.set_default("156.25");
		add_param("RefCLK_MHz2","double",&dRefCLK_MHz2)
					.set_comment("RefCLK_MHz")
					//.set_options("100:156.25")
					.set_default("156.25");
		add_param("TxFIR.TxMain","int",&iTxMain)
					 .set_default("35");
		add_param("TxFIR.TxPre1st","int",&iTxPre1st)
					 .set_default("-6");
		add_param("TxFIR.TxPost1st","int",&iTxPost1st)
					 .set_default("0");
		add_param("TxFIR.TxPre2nd","int",&iTxPre2nd)
					 .set_default("0");
		add_param("TxFIR.TxPost2nd","int",&iTxPost2nd)
					 .set_default("0");
		add_param("DataRate[Gbps]","double",&mDataRate)
					 //.set_options("6.25:9.8304:10.1376:10.3125:12.5:15")
					 .set_default("15");
		add_param("FULL_EYE","string",&mEyeScope)
					 //.set_options("YES:NO")
					 .set_default("NO");
		add_param("FreqOffset[PPM]","double",&mFreqOffset)
					 .set_default("100");
		add_param("JIAmp[UI]","double",&JitterAmpRequired)
					 //.set_options("0.09375:0.125:0.15625:0.1875:0.25:0.3125:0.375:0.5:0.625:0.75:1:1.25:1.5:2:2.5:3")
					 .set_default("0.09375");
		add_param("RateMode","int",&iRateMode)
					 .set_default("0");
		add_param("DataWidth","int",&iDataWidth)
					 .set_default("0");
		add_param("UseFixCTLE","string",	&mUseFixCTLE)
					 //.set_options("NO:YES")
					 .set_default("NO");
//		add_param("UseFixCTLE.CTLEACTGN1","int",&iCTLEACTGN1)
//					 .set_default("7");
//		add_param("UseFixCTLE.CTLEACTGN2","int",&iCTLEACTGN2)
//					 .set_default("7");
//		add_param("UseFixCTLE.CTLEACTGN3","int",&iCTLEACTGN3)
//					 .set_default("7");
//		add_param("UseFixCTLE.CTLEBST1","int",&iCTLEBST1)
//					 .set_default("0");
//		add_param("UseFixCTLE.CTLEBST2","int",&iCTLEBST2)
//					 .set_default("0");
//		add_param("UseFixCTLE.CTLEBST3","int",&iCTLEBST3)
//					 .set_default("0");
		add_param("EyeDiagram Method","string",&sEyeDiagMethod)
					 //.set_options("FW:HW")
					 .set_default("FW");
		add_param("PrintLvl[0~8]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
				     "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.set_options("0:1:3:4:7:8")
					 .set_default("3");
	}

    void execute(){
		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
                H30_FailBin_Flag.init(0);
		INT             		iDebugAnalog;
		static	INT 			iCSR_check;
		static  MACRO_LANE_SEL 		MacroLane_Sel;

		static	LANE_DOUBLE		RxErrorCount;
		static	LANE_UINT  		EyeWidth1;
		static	LANE_UINT  		EyeHeight1;
		static	LANE_UINT	  	EyeWidth2;
		static	LANE_UINT  		EyeHeight2;

		static	LANE_DOUBLE  		Jitter1;
		static	LANE_DOUBLE  		Jitter2;
		static	LANE_DOUBLE  		Jitter1_UI;
		static	LANE_DOUBLE  		Jitter2_UI;                

		static  bool                    CSRVerifyResult;
		int                             iCTLEACTGN1;
		int                             iCTLEACTGN2;
		int                             iCTLEACTGN3;
		int                             iCTLEACTGN4;
		int                             iCTLEBST1;
		int                             iCTLEBST2;
		int                             iCTLEBST3;

//		ON_FIRST_INVOCATION_BEGIN();

		//=============================================
		// Variables definition and initialization
		//=============================================

//		GET_TESTSUITE_NAME	(sTestsuiteName);
//		GET_TESTFLOW_FLAG	("debug_analog",&iDebugAnalog);
//		GET_USER_FLAG		("CSR_atomic_operation",&iCSR_check);
                
//                static STRING mPinList="";
//                const char * sTestsuiteName = api->Get_current_test_name();
                string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
                string strTestsuiteName = sTestsuiteName;
//                api->Get_test_values(strTestsuiteName.data(),THE_TESTNUMBER,&m_TestNumber,THE_END);
                stRxStressAll_ABIST RxStressAll_ABIST;
//        	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
        		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
        		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
        		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

		hout.setLevel(iPrintLvl);
		hout.printsuitename(sTestsuiteName);
		Select_Macro_Lane(MacroLane_Sel,mHiLink30_MacroList,mPinList);
//		FlexRelayCtrl();

		RxErrorCount.init(999);
		Jitter1.init(0);
                Jitter1_UI.init(0);
		EyeHeight1.init(0);
		EyeWidth1.init(0);
		Jitter2.init(0);
                Jitter2_UI.init(0);
		EyeHeight2.init(0);
		EyeWidth2.init(0);

		//=============================================
		// Device Setup
		//=============================================
//		D2S_FRAMEWORK;
//		GET_TEST_INFO;

                d2s_JTAG& jtag = d2s_JTAG::Instance();

		CUSTPARA Custpara = default_CUSTPARA;
		Custpara.TxFIR_USER.iTxMain = iTxMain;
		Custpara.TxFIR_USER.iTxPre1st = iTxPre1st;
		Custpara.TxFIR_USER.iTxPre2nd = iTxPre2nd;
		Custpara.TxFIR_USER.iTxPost1st = iTxPost1st;
		Custpara.TxFIR_USER.iTxPost2nd = iTxPost2nd;
		Stress_Setting stress_setting;

		LoopBack_Setting(sLoopBackMode,MacroLane_Sel,Custpara);
//		sprintf(label,"MPB_RxStressAll_SETUP_Vcoef_%f_%f",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
                d2s::d2s_LABEL_BEGIN( "MPB_RxStressAll_SETUP_Vcoef_", Global_D2S_Mode);
			selectMacro_MB(MacroLane_Sel);

			DS.rxRegs.SliceID(0).Broadcast(1);
			DS.txRegs.SliceID(0).Broadcast(1);
			DS.clkRegs.SliceID(0).Broadcast(1);

			EnableTxPrbsGen("PRBS15");
//                        EnableTxPrbsGen("CUSTOMER_PATTERN",0xAAAA);
			DS.rxRegs.setcdrfreeze(0).Write2DUT(12);
			jtag.wait(0.0001);
			EnableRxPrbsCheck("PRBS15");
//                        EnableRxPrbsCheck("CUSTOMER_PATTERN");

			if(mUseFixCTLE == "YES"){
				  DS.rxRegs.setctleactgn1(iCTLEACTGN1).Write2DUT(1);
				  DS.rxRegs.setctleactgn2(iCTLEACTGN2).Write2DUT(2);
				  DS.rxRegs.setctleactgn3(iCTLEACTGN3).Write2DUT(3);
				  DS.rxRegs.setctleboostc1(iCTLEBST1).Write2DUT(1);
				  DS.rxRegs.setctleboostc2(iCTLEBST2).Write2DUT(2);
				  DS.rxRegs.setctleboostc3(iCTLEBST3).Write2DUT(3);
			  }
    		DS.txRegs.settxcpddlcal(0).Write2DUT(10);
    		DS.txRegs.settxrstb(0).Write2DUT(2);
    		DS.txRegs.settxrstb(1).Write2DUT(2);
    		jtag.wait(0.0001); //add by shaoxue 20170216 clear dcd   modify from 0.001 to 0.0001 by tony 20210915
		d2s::d2s_LABEL_END();
		SetTxFir(MacroLane_Sel,Custpara);

		int iPpmgen = FreqOffset(mFreqOffset);

		JI JITINDEX;

		JITINDEX = JitterInjection(mDataRate,JitterAmpRequired,1);

		stress_setting.jitcontrol = 1;
		stress_setting.ppmgen = iPpmgen;
		stress_setting.jitFreq = JITINDEX.FREQINDEX;
		stress_setting.jitamp = JITINDEX.AMPINDEX;

//		sprintf(label,"MPB_RxStressAll_SETUP_setPPM_%f_%f_",Vcoef,Temp);
		d2s::d2s_LABEL_BEGIN( "MPB_RxStressAll_SETUP_setPPM_", Global_D2S_Mode);
		//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
		//SetTxBistPpmJitter(stress_setting);
		selectMacro_MB(MacroLane_Sel);
		DS.txRegs.SliceID(0).Broadcast(1);
		DS.txRegs.settxalignmode(3).Write2DUT(2);
		DS.txRegs.setjitppmctrl(stress_setting.jitcontrol)
			.setjitfreq(stress_setting.jitFreq)
			.setjitamp(stress_setting.jitamp)
			.setppmgen(stress_setting.ppmgen)
			.Write2DUT(3);
		DS.txRegs.settxrstb(0x0).Write2DUT(2);
		DS.txRegs.settxrstb(0x1).Write2DUT(2);
		DS.txRegs.settxalignmode(4).Write2DUT(2);
		d2s::d2s_LABEL_END();

		//=============================================
		// Measurement
		//=============================================
		Read_Bert(MacroLane_Sel,  RxErrorCount, "ABIST", false, "", 0, 0.001);

		uint iShowInner = 0;//inner eye scan
		uint iEyeScanWin = 15; // vertical inner eye scan
		uint iMonSlcSel = 0; // 0 = I
        uint iEyeScanMode=1;//vetical inner eye scan
		uint itap1Inside=1;//eye diagram with tap1
		uint itap1Type =2;//plot the composite tap1 eye

		switch (iRateMode)
		{
		case 0: iMonSlcSel = 0;	    break; //full rate, I eye
		case 1: iMonSlcSel = 3;       break; //half rate,Qb eye
		case 2: iMonSlcSel = 1;       break; //quart rate, Q eye
		}

		if(sEyeDiagMethod == "FW"){
			AteFwFourPointEyeScan(MacroLane_Sel,dRefCLK_MHz,dRefCLK_MHz2,mDataRate,EyeWidth1,EyeHeight1,EyeWidth2,EyeHeight2);
		}
		else if(sEyeDiagMethod == "HW"){
			GetFourPointEyeDiagram(MacroLane_Sel, iShowInner, iEyeScanWin,iMonSlcSel, 1, 0, EyeWidth1, EyeHeight1);
			GetFourPointEyeDiagram(MacroLane_Sel, iShowInner, iEyeScanWin,iMonSlcSel, 1, 1, EyeWidth2, EyeHeight2);
		}
		else{
//			cout<<"ERROR: FourPointEyeDiagram only support FW or HW method."<<endl;
          std::cout<<"ERROR: FourPointEyeDiagram only support FW or HW method."<<std::endl;
//			ERROR_EXIT(TM::ABORT_FLOW);
		}

		if(mEyeScope=="YES"||(hout.getLevel()== 4)){
			GetEyeDiagram(MacroLane_Sel,iEyeScanMode,iEyeScanWin,iMonSlcSel,itap1Inside,itap1Type);
		}
		stress_setting.jitcontrol = 0;
		stress_setting.ppmgen = 0;
		stress_setting.jitFreq = 0;
		stress_setting.jitamp = 0;

//		sprintf(label,"MPB_RxStressAll_SETUP_restorePPM_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
             d2s::d2s_LABEL_BEGIN( "MPB_RxStressAll_SETUP_restorePPM_", Global_D2S_Mode);
			selectMacro_MB(MacroLane_Sel);
			DS.txRegs.SliceID(0).Broadcast(1);
			DS.txRegs.setkfactor(0x0).Write2DUT(3);
			DS.txRegs.setjitppmctrl(0x0).Write2DUT(3);
			DS.txRegs.setjitfreq(0x0).Write2DUT(3);
			DS.txRegs.setjitamp(0x0).Write2DUT(3);
			DS.txRegs.setppmgen(0x0).Write2DUT(3);
			DS.txRegs.settxalignmode(0x3).Write2DUT(2);
            d2s::d2s_LABEL_END();

		//=============================================
		// Datalog
		//=============================================

		DOUBLE uiSize = 0.0;
		DOUBLE eyeUI_ps = 1000.0/ mDataRate;

		switch (iRateMode)
		{
		case 0: uiSize = 32;	    break;
		case 1: uiSize = 64;       break;
		case 2: uiSize = 128;       break;
		case 3: uiSize = 256;       break;
		default: uiSize = 32;       break;
		}

                
//                FOREACH_ACTIVE_SITE(api) {
//                    unsigned int SiteID = api->Get_active_site();
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
				{
						UINT LaneID = vLane[laneIndex];

						Jitter1[SiteID][MacroID][LaneID] = eyeUI_ps * (1 - EyeWidth1[SiteID][MacroID][LaneID]/uiSize);
						Jitter2[SiteID][MacroID][LaneID] = eyeUI_ps * (1 - EyeWidth2[SiteID][MacroID][LaneID]/uiSize);
						Jitter1_UI[SiteID][MacroID][LaneID] = 1 - EyeWidth1[SiteID][MacroID][LaneID]/uiSize;
						Jitter2_UI[SiteID][MacroID][LaneID] = 1 - EyeWidth2[SiteID][MacroID][LaneID]/uiSize;

						hout(DETAIL) << "Site" << SiteID << " Macro" << MacroID << " Lane" << LaneID << " Width1 = " << EyeWidth1[SiteID][MacroID][LaneID] << endl;
						hout(DETAIL) << "Site" << SiteID << " Macro" << MacroID << " Lane" << LaneID << " Width2 = " << EyeWidth2[SiteID][MacroID][LaneID] << endl;

				}
		}
        FOREACH_ACTIVESITE_END

		double LimitL_ErrCnt=0;
		double LimitH_ErrCnt=0;
		double LimitL_Jitter=0.09375;
		double LimitH_Jitter=0.9;
		double LimitL_EyeHight=20;
		double LimitH_EyeHight=318;
		HiLink_PerLane_Judge(MacroLane_Sel, "Rx_Err_Cnt",LimitL_ErrCnt,RxErrorCount,LimitH_ErrCnt);
		HiLink_PerLane_Judge(MacroLane_Sel, "Jitter1_Pk-Pk",LimitL_Jitter,Jitter1_UI,LimitH_Jitter);
		HiLink_PerLane_Judge(MacroLane_Sel, "EyeHeight1_pt",LimitL_EyeHight,EyeHeight1,LimitH_EyeHight);   //why  ivanwu
		HiLink_PerLane_Judge(MacroLane_Sel, "Jitter2_Pk-Pk",LimitL_Jitter,Jitter2_UI,LimitH_Jitter);
		HiLink_PerLane_Judge(MacroLane_Sel, "EyeHeight2_pt",LimitL_EyeHight,EyeHeight2,LimitH_EyeHight);   //why  ivanwu
                
//                SetTestBin();

    }
};

REGISTER_TESTCLASS("RxStressAll_ABIST",RxStressAll_ABIST)


