//for test method API interfaces
//#include "mapi.hpp"
//using namespace std;
//using namespace V93kLimits;

#include <Common_Func/HiLink_Common_Func.h>

/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class SSC_RxFreqOffsetTol_ATE: public TestClass {

public:
	STRING 				mHiLink16_MacroList;
	STRING 				mPinList;
	STRING 				sPinList;
	STRING 				sPinList_P;
	STRING 				sPinList_N;
	INT 				iPPM_Neg;
	INT 				iPPM_Pos;
	INT					iPrintLvl;

	/**
	 *Initialize the parameter interface to the testflow.
	 *This method is called just once after a testsuite is created.
	 */
	void init()
	{
		add_param("H16LR_MacroList","string",&mHiLink16_MacroList)
					 .set_comment("HiLink16 Macro List for test")
					 //.set_options("0,1:FromPinList")
					 .set_default("0,1");
		add_param("PinList","PinString",&mPinList);
		add_param("PrintLvl[0~15]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 10000(16)"
							     "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYE_PLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.set_options("0:1:3:4:7:9")
					 .set_default("3");
	}
	void execute()
		{

		}
	////////////////////////////////////////////////////////////////////////////////
	// TM Purpose:                                                                //
	// This TM is to record the maximum Rx port data frequency offset with keeping//
	// Tx port data frequency, with which there is no error count by reading      //
	// register in mission mode.                                                  //
	//																			  //
	// Parameters:																  //
	// 1. SpecName: spec name of data frequency	to be changed         			  //
	// 2. PortName: port name of data pins to perform data frequency offset 	  //
	// 3. ppm: data frequency shift ppm							                  //
	////////////////////////////////////////////////////////////////////////////////
	/**
	 *This test is invoked per site.
	 */
//	virtual void run()
//	{
//		/*===========================================*
//		 * Common definition of TM for offline flag, *
//		 * test suite name, MacroLane Info etc.		 *
//		 *===========================================*/
//
//		static	STRING          	sTestsuiteName;
//		static	INT					iOffline;
//		static  MACRO_LANE_SEL 		MacroLane_Sel;
//
//		static	LANE_DOUBLE 		ErrorCount_Neg;
//		static	LANE_DOUBLE 		ErrorCount_Pos;
//
//		ON_FIRST_INVOCATION_BEGIN();
//
//		/*========================================*
//		 * Variables and MacroLane initialization *
//		 *========================================*/
//
//			GET_SYSTEM_FLAG		("offline",&iOffline);
//			GET_TESTSUITE_NAME	(sTestsuiteName);
//			hout.setLevel(iPrintLvl);
//			hout.printsuitename(sTestsuiteName);
//			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);
//
//			GetRxPinList(MacroLane_Sel, sPinList_P, sPinList_N, sPinList);
//
//			/*** Connect PSSL AC Relay to DUT ****/
//			if (CP_FT_Program == "FT") {
//				FLEX_RELAY frelay;
//				frelay.pin("pHilink16_TX,pHilink16_RX").set("AC","OFF");
//				frelay.wait(0.3 ms);
//				frelay.execute();
//			}
//
//			//=============================================
//			// Device Setup
//			//=============================================
//			D2S_FRAMEWORK;
//
//			/*==========================================*
//			 * atomic operation: csr check before write *
//			 *==========================================*/
//
//			if (CUSTpara.Protocol == "SAS" && ((CUSTpara.Data_Rate == 1.5) || (CUSTpara.Data_Rate == 3) || (CUSTpara.Data_Rate == 6))) {
//				iPPM_Neg = -3700;
//				iPPM_Pos = 3700;
//			} else if (CUSTpara.Protocol == "PCIE" && ((CUSTpara.Data_Rate == 2.5) || (CUSTpara.Data_Rate == 5) || (CUSTpara.Data_Rate == 8) || (CUSTpara.Data_Rate == 16))) {
//				iPPM_Neg = -6000;
//				iPPM_Pos = 1000;
//			} else if (CUSTpara.Protocol == "SAS" && CUSTpara.Data_Rate == 12) {
//				iPPM_Neg = -2000;
//				iPPM_Pos = 2000;
//			} else if (CUSTpara.Protocol == "SATA" && ((CUSTpara.Data_Rate == 1.5) || (CUSTpara.Data_Rate == 3) || (CUSTpara.Data_Rate == 6))) {
//				iPPM_Neg = -6000;
//				iPPM_Pos = 1000;
//			} else {
//				hout(RELEASE) << "Protocol " << CUSTpara.Protocol << " DataRate " << CUSTpara.Data_Rate << " is not a valid option for PCIE/SATA/SAS protocol!!" << endl;
//				_exit(0);
//			}
//
//			/***************************************************************
//			 * Step 1: Insert Neg PPM to PSSL data stream
//			 ***************************************************************/
//
//			DOUBLE 				dOrgVal;
//			STRING 				sSpecName = "FrequencyOffset";
//			dOrgVal = Primary.getSpecification().getSpecValue(sSpecName);
//
//			INT 				signedFreqOffset_neg = iPPM_Neg;
//			hout(DETAIL) << "FreqOffset: " << dec << signedFreqOffset_neg << " [PPM]" << endl;
//
//			try {
//				Primary.getSpecification().change(sSpecName, signedFreqOffset_neg);
//				FLUSH(TM::APRM);
//			} catch (Error &error) {
//				Primary.getSpecification().change(sSpecName, dOrgVal);
//				FLUSH(TM::APRM);
//				ERROR_EXIT(TM::RETURN_TO_FLOW);
//			}
//	/*
//			string ans;
//			FW_TASK("PCLK? \"mpb_Hilink15_12G_FASTDIFF_spec\",1,(@@)",ans);
//			cout<<ans<<endl;
//			FW_TASK("evck? \"mpb_Hilink15_12G_FASTDIFF_spec\",(@@)",ans);
//			cout<<ans<<endl;
//			FW_TASK("svlr? tim,prm,all,all",ans);
//			cout<<ans<<endl;
//	*/
//
//			/***************************************************************
//			 * Step 2: Reset CDR and do bert
//			 ***************************************************************/
//
//			fr.d2s_LABEL_BEGIN("H16LRV100_MPB_SSC_FreqOffsetTol_reset_CDR_Pos",d2sFrameWorkModeType::Enum(d2s_mode));
//
//				selectMacro_MB(MacroLane_Sel);
//				DS.Broadcast();
//				DS.rxRegs.setcdrrstb(0).Write2DUT(11);
//				DS.rxRegs.setcdrrstb(1).Write2DUT(11);
//
//				jtag.wait(20 us);
//
//			fr.d2s_LABEL_END();
//
//			ReadBert_ExpectValue(MacroLane_Sel,PRBS15,ErrorCount_Neg,"ATE");
//
//			if (hout.IsEyePlotEn()) {
//				GetEyeDiagram(MacroLane_Sel, CUSTpara.Data_Rate, "ATE");
//			}
//
//			/***************************************************************
//			 * Step 3: Insert Pos PPM to PSSL data stream
//			 ***************************************************************/
//
//
//			INT 				signedFreqOffset_pos = iPPM_Pos;
//			hout(DETAIL) << "FreqOffset: " << dec << signedFreqOffset_pos << " [PPM]" << endl;
//
//			try {
//				Primary.getSpecification().change(sSpecName, signedFreqOffset_pos);
//				FLUSH(TM::APRM);
//			} catch (Error &error) {
//				Primary.getSpecification().change(sSpecName, dOrgVal);
//				FLUSH(TM::APRM);
//				ERROR_EXIT(TM::RETURN_TO_FLOW);
//			}
//
//
//			/***************************************************************
//			 * Step 4: Reset CDR and do bert
//			 ***************************************************************/
//
//			fr.d2s_LABEL_BEGIN("H16LRV100_MPB_SSC_RxFreqOffsetTol_reset_CDR_Neg",d2sFrameWorkModeType::Enum(d2s_mode));
//
//				selectMacro_MB(MacroLane_Sel);
//				DS.Broadcast();
//				DS.rxRegs.setcdrrstb(0).Write2DUT(11);
//				DS.rxRegs.setcdrrstb(1).Write2DUT(11);
//
//				jtag.wait(20 us);
//
//			fr.d2s_LABEL_END();
//
//			ReadBert_ExpectValue(MacroLane_Sel,PRBS15,ErrorCount_Pos,"ATE");
//
//			if (hout.IsEyePlotEn()) {
//				GetEyeDiagram(MacroLane_Sel, CUSTpara.Data_Rate, "ATE");
//			}
//
//			//=============================================
//			//restore
//			//=============================================
//			Primary.getSpecification().change(sSpecName, dOrgVal);
//			FLUSH(TM::APRM);
//
//		ON_FIRST_INVOCATION_END();
//
//		/*=======================*
//		 * Judgement and datalog *
//		 *=======================*/
//
//		HiLink_PerLane_Judge(MacroLane_Sel, "SSC_FreqOffset_ErrCnt_Neg", ErrorCount_Neg);
//		HiLink_PerLane_Judge(MacroLane_Sel, "SSC_FreqOffset_ErrCnt_Pos", ErrorCount_Pos);
//
//		return;
//	}

	/**
	 *This function will be invoked once the specified parameter's value is changed.
	 *@param parameterIdentifier
	 */
//	virtual void postParameterChange(const string& parameterIdentifier) {
//		//Add your code
//		//Note: Test Method API should not be used in this method!
//		bool visible = (mHiLink16_MacroList == "FromPinList");
//		getParameter("PinList").setVisible(visible);
//
//
//		return;
//	}
//
//	/**
//	 *This function will be invoked once the Select Test Method Dialog is opened.
//	 */
//	virtual const string getComment() const {
//		string comment = " please add your comment for this method.";
//		return comment;
//	}
};
REGISTER_TESTCLASS("SSC_RxFreqOffsetTol_ATE", SSC_RxFreqOffsetTol_ATE);
