
#include <Common_Func/HiLink30_Common_Func.h>
//#include "LimitTable_Manager.h"

  
using namespace std;
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // TM Purpose:                                                                                                                //
  //                                                                                                                            //
  //                                    The following code are all sub functions                                                //
  //																		                                                  	  //
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void RxJitterTolSearch(MACRO_LANE_SEL& MacroLane_Sel, LANE_DOUBLE& vMaxJitterAmp);
  


  	////////////////////////////////////////////////////////////////////////////////
  	// TM Purpose:                                                                //
  	// This TM is to record the maximum Tx jitter injection value, with which     //
  	// there is no error count by reading register in internal loopback mode.     //
  	// The Tx jitter injection by setting JITFREQ and JITAMPL register step by    //
  	// step.
  	//																			  //
  	////////////////////////////////////////////////////////////////////////////////
  	/**
  	 *This test is invoked per site.
  	 */
//  	virtual void run()

class RxJitterTol_ABIST: public TestClass{
public:
	  	STRING 				mHiLink30_MacroList;
	  	STRING 				mPinList;

	  	INT	 				iTxMain;
	  	INT					iTxPre1st;
	  	INT					iTxPost1st;
	  	INT                 iTXDRVTAPXMODSEL;
	  	INT                 iTxPre2nd;
	  	INT                 iTxPost2nd;
	    STRING              sLoopBackMode;
	    DOUBLE   			mDataRate;
		INT 				iCTLEACTGN1;
		INT 				iCTLEACTGN2;
		INT 				iCTLEACTGN3;;
		INT					iCTLEBST1;
		INT					iCTLEBST2;
		INT					iCTLEBST3;
		STRING			    mUseFixCTLE;
	  	INT					iPrintLvl;
	void init(){
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					.set_comment("HiLink30 Macro List for test")
					//.set_options("0,1:FromPinList")
					.set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
		add_param("LoopBackMode","string",&sLoopBackMode)
					.set_default("Bump");
					//.set_options("PreDriver:Bump:External:Nothing");
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
		add_param("DataRate","double",&mDataRate)
					.set_default("30");
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
	void execute(){

  		//=============================================
  		// Common definition of TM for offline flag,
  		// d2s mode, debug mode, test suite name, etc.
  		//=============================================
                H30_FailBin_Flag.init(0);
  		static	INT			iOffline;
  		static	INT 			iCSR_check;
  		static  MACRO_LANE_SEL 		MacroLane_Sel;

  		static	LANE_DOUBLE		vMaxJitterAmpValue;
  		static  bool                    CSRVerifyResult;
                
                INT 				iCTLEACTGN1;
                INT 				iCTLEACTGN2;
                INT 				iCTLEACTGN3;;
                INT				iCTLEBST1;
                INT				iCTLEBST2;
                INT				iCTLEBST3;
                

//  		ON_FIRST_INVOCATION_BEGIN();
  		//=============================================
  		// Variables and MacroLane initialization
  		//=============================================

//  		GET_SYSTEM_FLAG		("offline",&iOffline);
//  		GET_TESTSUITE_NAME	(sTestsuiteName);
//  		GET_USER_FLAG		("CSR_atomic_operation",&iCSR_check);
//                
                
                stRxJitterTol_ABIST RxJitterTol_ABIST=H30_RxJitterTol_30G_ABIST_RxJitterTol_ABIST; 
                
//                static STRING mPinList="";
//                const char * sTestsuiteName = "";//TheSoft.Get_current_test_name();
        		string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
                string strTestsuiteName = sTestsuiteName;
//                api->Get_test_values(strTestsuiteName.data(),THE_TESTNUMBER,&m_TestNumber,THE_END);

//        	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
        		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
        		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
        		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

  		hout.setLevel(iPrintLvl);
  		hout.printsuitename(sTestsuiteName);
  		Select_Macro_Lane(MacroLane_Sel,mHiLink30_MacroList,mPinList);

//  		FlexRelayCtrl();
//
//  		D2S_FRAMEWORK;
//  		GET_TEST_INFO;

                d2s_JTAG& jtag = d2s_JTAG::Instance();  
  		//=============================================
  		// Device Setup
  		//=============================================
  		CUSTPARA Custpara = default_CUSTPARA;
		Custpara.TxFIR_USER.iTxMain=iTxMain;
		Custpara.TxFIR_USER.iTxPre1st=iTxPre1st;
		Custpara.TxFIR_USER.iTxPost1st=iTxPost1st;
		Custpara.TxFIR_USER.iTxPre2nd=iTxPre2nd;
		Custpara.TxFIR_USER.iTxPost2nd=iTxPost2nd;
		Custpara.RxCTLE_USER.Gain[0]=iCTLEACTGN1;
		Custpara.RxCTLE_USER.Gain[1]=iCTLEACTGN2;
		Custpara.RxCTLE_USER.Gain[2]=iCTLEACTGN3;
		Custpara.RxCTLE_USER.Boost[0]=iCTLEBST1;
		Custpara.RxCTLE_USER.Boost[1]=iCTLEBST2;
		Custpara.RxCTLE_USER.Boost[2]=iCTLEBST3;

		SetTxFir(MacroLane_Sel,Custpara);
		LoopBack_Setting(sLoopBackMode,MacroLane_Sel,Custpara);
//		sprintf(label,"MPB_RxJitterTol_SETUP_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
                d2s::d2s_LABEL_BEGIN( "MPB_RxJitterTol_SETUP_", Global_D2S_Mode);
			selectMacro_MB(MacroLane_Sel);
			DS.rxRegs.SliceID(0).Broadcast(1);
			DS.txRegs.SliceID(0).Broadcast(1);

			EnableTxPrbsGen("PRBS15");
			DS.rxRegs.setcdrfreeze(0).Write2DUT(12);
//			jtag.wait(100 uS);
                        jtag.wait(0.0001);
			EnableRxPrbsCheck("PRBS15");

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
			DS.txRegs.settxrstb(1).Write2DUT(2);// add by shaoxue 20470216 clear dcd
//		fr.d2s_LABEL_END();
                d2s::d2s_LABEL_END();

//		WAIT_TIME(1 ms);//follow test plan, add 1ms wait for stability
//                Sleep(0.001);
  		//=============================================
  		//measurement
  		//=============================================
  		RxJitterTolSearch(MacroLane_Sel, vMaxJitterAmpValue);

//  		sprintf(label,"MPB_RxJitterTol_Restore_%f_%f_",Vcoef,Temp);
//		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
                d2s::d2s_LABEL_BEGIN( "MPB_RxJitterTol_Restore_", Global_D2S_Mode);
                    selectMacro_MB(MacroLane_Sel);
                    DS.txRegs.SliceID(0).Broadcast(1);
                    DS.txRegs.setkfactor(0x0).Write2DUT(3);
                    DS.txRegs.setjitppmctrl(0x0).Write2DUT(3);
                    DS.txRegs.setjitfreq(0x0).Write2DUT(3);
                    DS.txRegs.setjitamp(0x0).Write2DUT(3);
                    DS.txRegs.setppmgen(0x0).Write2DUT(3);
                    DS.txRegs.settxalignmode(0x3).Write2DUT(2);
//		fr.d2s_LABEL_END();
                d2s::d2s_LABEL_END();

//		ON_FIRST_INVOCATION_END();

  		//=============================================
  		// Datalog
  		//=============================================
                
                double LimitL=0.1;
                double LimitH=0.9;

		HiLink_PerLane_Judge(MacroLane_Sel, "AmpUI",LimitL, vMaxJitterAmpValue,LimitH);

                SetTestBin();
	}

};
REGISTER_TESTCLASS("RxJitterTol_ABIST",RxJitterTol_ABIST)








  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // TM Purpose:                                                                                                                //
  //                                                                                                                            //
  //                                    The following code are all sub functions                                                //
  //																		                                                  	  //
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void RxJitterTolSearch(MACRO_LANE_SEL& MacroLane_Sel, LANE_DOUBLE& vMaxJitterAmp)
  {
//  	D2S_FRAMEWORK;
//  	GET_TEST_INFO;

	LANE_DOUBLE 	vErrorCount;
	LANE_INT	iLaneDone;
        
//        stRxJitterTol_ABIST RxJitterTol_ABIST=H30_RxJitterTol_30G_ABIST_RxJitterTol_ABIST; //5875
        stRxJitterTol_ABIST RxJitterTol_ABIST=H30_RxJitterTol_24G33024_ABIST_RxJitterTol_ABIST;////modify tony 20210519

	vMaxJitterAmp.init(0);
	iLaneDone.init(0);

  	/***************Inject Jitter*******************/
  	DOUBLE 			UIsize = 32;

  	typedef map <int, double>::value_type  valType;

  	map <int, double> mapJitterInject; /*****<jitterPoint, JitterAmpRequired>******/

  	int JitControl=1;

  	if(JitControl == 1)
	{
		mapJitterInject.insert(valType (0, 3  / UIsize));
		mapJitterInject.insert(valType (1, 4  / UIsize));
		mapJitterInject.insert(valType (2, 5  / UIsize));
		mapJitterInject.insert(valType (3, 6  / UIsize));
		mapJitterInject.insert(valType (4, 8  / UIsize));
		mapJitterInject.insert(valType (5, 10 / UIsize));
		mapJitterInject.insert(valType (6, 12 / UIsize));
		mapJitterInject.insert(valType (7, 16 / UIsize));
		mapJitterInject.insert(valType (8, 20 / UIsize));
		mapJitterInject.insert(valType (9, 24 / UIsize));
		mapJitterInject.insert(valType (10,32 / UIsize));
//		mapJitterInject.insert(valType (11,40 / UIsize));
//		mapJitterInject.insert(valType (12,48 / UIsize));
//		mapJitterInject.insert(valType (13,64 / UIsize));
//		mapJitterInject.insert(valType (14,80 / UIsize));
//		mapJitterInject.insert(valType (15,96 / UIsize));

	}
	else if(JitControl == 0)
	{
		mapJitterInject.insert(valType (0, 12 / UIsize));
		mapJitterInject.insert(valType (1, 16 / UIsize));
		mapJitterInject.insert(valType (2, 24 / UIsize));
		mapJitterInject.insert(valType (3, 32 / UIsize));
		mapJitterInject.insert(valType (4, 48 / UIsize));
		mapJitterInject.insert(valType (5, 64 / UIsize));
		mapJitterInject.insert(valType (6, 96 / UIsize));
		mapJitterInject.insert(valType (7,128 / UIsize));

	}

  	map <int,double>::iterator it;

  	UINT 			Index = 0;
  	INT 			iFindAll = 0;
  	struct JI 		JIIndex;
  	DOUBLE   			mDataRate;//20211124

  	while (Index < mapJitterInject.size() && (iFindAll == 0 || (Global_D2S_Mode == 0)))
  	{
  		it = mapJitterInject.find (Index);
  		if (it != mapJitterInject.end())
		{
			JIIndex = JitterInjection(mDataRate, it -> second,JitControl);

		}

  		Stress_Setting Stress_SET;
		Stress_SET.jitcontrol=JitControl; //JITER MODE =1,NORMAL MODE=0;
		Stress_SET.jitamp=JIIndex.AMPINDEX;
		Stress_SET.jitFreq=JIIndex.FREQINDEX;
		Stress_SET.ppmgen=0;

//		sprintf(label,"MPB_RxJitterTolSearch_%f_%f_",Vcoef,Temp);
//  		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
                d2s::d2s_LABEL_BEGIN( "MPB_RxJitterTolSearch_", Global_D2S_Mode);
  			selectMacro_MB(MacroLane_Sel);
  			DS.txRegs.SliceID(0).Broadcast(1);
  			SetTxBistPpmJitter(Stress_SET);
//  		fr.d2s_LABEL_END();
                d2s::d2s_LABEL_END();
//  		WAIT_TIME(5 ms);
//                Sleep(0.005);
  		Read_Bert(MacroLane_Sel, vErrorCount,"ABIST",false,"", 0, 0.001);

  		iFindAll = Update_LaneData_InTolerance(MacroLane_Sel,it -> second,vErrorCount,vMaxJitterAmp,iLaneDone);

  		Index ++;
  	}
  }

