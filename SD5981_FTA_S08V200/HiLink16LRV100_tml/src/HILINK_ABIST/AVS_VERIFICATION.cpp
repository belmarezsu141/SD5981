//for test method API interfaces
//#include "mapi.hpp"
//using namespace std;
//using namespace V93kLimits;

#include <HILINK_PUG/HiLink16_PUG.h>

using namespace PhxAPI;
/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class AVS_VERIFICATION: public TestClass {
public:
	STRING 				sDVDDSPEC;
	STRING 				mHiLink16_MacroList;
	STRING 				mPinList;
	STRING				mLoopbackMode;
	INT					iPrintLvl;


	/**
	*Initialize the parameter interface to the testflow.
	*This method is called just once after a testsuite is created.
	*/
	void init()
	{
		add_param("DVDD_SpecName","string",&sDVDDSPEC)
					 .set_comment("Each Spec is one-to-one correspondence to each DVDD_Pin, support ARRAY");
		add_param("H16LR_MacroList","string",&mHiLink16_MacroList)
					 .set_comment("HiLink16 Macro List for test")
					 //.set_options("0,1:FromPinList")
					 .set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
		add_param("Loopback_Mode","string",&mLoopbackMode)
					 //.set_options("Bump:PreDriver:External")
					 .set_default("Bump");
		add_param("PrintLvl[0~15]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 10000(16)"
							     "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYE_PLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.set_options("0:1:3:4:7:9")
					 .set_default("3");
	}

	void execute()
		{
		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
		static	STRING          	sTestsuiteName;
		static	INT					iOffline;
		static  MACRO_LANE_SEL 		MacroLane_Sel;

		static	LANE_DOUBLE 		DVDDBottomResult_uV;
		static	LANE_DOUBLE 		DVDDUpResult_uV;

			//=============================================
			// Variables and MacroLane initialization
			//=============================================
			iOffline = 0;
			sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
			hout.setLevel(iPrintLvl);
			hout.printsuitename(sTestsuiteName);
			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

			//=============================================
			// Device Setup
			//=============================================
			d2s_JTAG& jtag = d2s_JTAG::Instance();

			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_AVS_Verify_SETUP",Global_D2S_Mode);

				selectMacro_MB(MacroLane_Sel);
				DS.Broadcast();

				if (mLoopbackMode == "External" ) {
					DisableTxToRxSerLpbk();
				} else {
					EnableTxToRxSerLpbk(mLoopbackMode);
				}

				EnableTxPrbsGen(PRBS15);

				DS.rxRegs.setcdrfreeze(0)
						 .Write2DUT(10);
				jtag.wait(20 *0.000001);

			d2s::d2s_LABEL_END();

			//=============================================
			//Verify Bert
			//=============================================

			LANE_DOUBLE 		DVDDBottomResult;
			LANE_DOUBLE 		DVDDUpResult;

			DOUBLE				DVDD_Search_Low = 0.70625;
			DOUBLE				DVDD_Search_Up  = 0.8875;
			DOUBLE				DVDD_Search_Step = 0.00625;

			STRING_VECTOR 			vDPSSpec_DVDD;
			ARRAY_D					aOrgVal;
			parseListOfString(sDVDDSPEC,vDPSSpec_DVDD,',');
			aOrgVal.resize(vDPSSpec_DVDD.size());

			if (vDPSSpec_DVDD.size() > 0) {
				for (UINT i = 0; i < vDPSSpec_DVDD.size(); i ++) {
//					aOrgVal[i] = Primary.getLevelSpec().getSpecValue(vDPSSpec_DVDD[i]);
					aOrgVal[i] = TheSoft.Specs().GetValue("level_spec.spec", vDPSSpec_DVDD[i]);
				}
			} else {
				hout(GENERAL) << "!!!!!!!!!!!! No DVDD Level Spec found, Please check input !!!!!!!!!!!!!" << endl;
				_exit(0);
			}

			AVS_Verify_Search(MacroLane_Sel, DVDDBottomResult, vDPSSpec_DVDD, PRBS15, DVDD_Search_Low, DVDD_Search_Step);

			if (vDPSSpec_DVDD.size() > 0) {
				for (UINT i = 0; i < vDPSSpec_DVDD.size(); i ++) {
//					Primary.getLevelSpec().change(vDPSSpec_DVDD[i], aOrgVal[i]);
					TheSoft.Specs().SetValue("level_spec.spec", vDPSSpec_DVDD[i], aOrgVal[i]);
				}
//				FLUSH(TM::APRM);
				if(isDPS128)
					TheInst.DCVI().Power().DynamicApply();
				else
					TheInst.DCVS().Power().DynamicApply();
			}

			AVS_Verify_Search(MacroLane_Sel, DVDDUpResult, vDPSSpec_DVDD, PRBS15, DVDD_Search_Up, DVDD_Search_Step);

			if (vDPSSpec_DVDD.size() > 0) {
				for (UINT i = 0; i < vDPSSpec_DVDD.size(); i ++) {
//					Primary.getLevelSpec().change(vDPSSpec_DVDD[i], aOrgVal[i]);
					TheSoft.Specs().SetValue("level_spec.spec", vDPSSpec_DVDD[i], aOrgVal[i]);
				}
//				FLUSH(TM::APRM);
				if(isDPS128)
					TheInst.DCVI().Power().DynamicApply();
				else
					TheInst.DCVS().Power().DynamicApply();
			}


			DVDDBottomResult_uV.init(0);
			DVDDUpResult_uV.init(0);

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						DVDDBottomResult_uV[SiteID][MacroID][LaneID] = (INT)(DVDDBottomResult[SiteID][MacroID][LaneID] * 1000000 + 0.1);
						DVDDUpResult_uV[SiteID][MacroID][LaneID] = (INT)(DVDDUpResult[SiteID][MacroID][LaneID] * 1000000 + 0.1);
					}
				}
			FOREACH_ACTIVESITE_END

		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "DVDD_Max", DVDDUpResult_uV);
//		HiLink_PerLane_Judge(MacroLane_Sel, "DVDD_Min", DVDDBottomResult_uV);

		return;
		}
	//========================Hi1213

	void AVS_Verify_Search(MACRO_LANE_SEL& MacroLane_Sel, LANE_DOUBLE& DVDDSearchResult, STRING_VECTOR vDPSSpec_DVDD, PRBS_Pattern mPRBS, DOUBLE DVDD_Search_Stop, DOUBLE DVDD_Search_Step)
		{

			LANE_INT 				FindFlag;
			LANE_DOUBLE	 			ErrorCount;

			FindFlag.init(0);
			ErrorCount.init(0);
			DVDDSearchResult.init(0);

			ARRAY_D					aChangeVal;
			DOUBLE					dChangeVal;
			aChangeVal.resize(vDPSSpec_DVDD.size());
			if (vDPSSpec_DVDD.size() > 0) {
				for (UINT i = 0; i < vDPSSpec_DVDD.size(); i ++) {
	//				aChangeVal[i] = Primary.getLevelSpec().getSpecValue(vDPSSpec_DVDD[i]);
					aChangeVal[i] = TheSoft.Specs().GetValue("level_spec.spec", vDPSSpec_DVDD[i]);
				}
			}

			dChangeVal = aChangeVal[0];
			cout<<" =================== VDD spec  init value = "<<dChangeVal<<endl;

			if (vDPSSpec_DVDD.size() > 0) { //for mutil pins check all pin force same voltage
				for (UINT i = 0; i < vDPSSpec_DVDD.size(); i ++) {
					if (abs(aChangeVal[i] - dChangeVal) >= 1e-5) {
						hout(GENERAL) << vDPSSpec_DVDD[i] << " value is not consistent with" << vDPSSpec_DVDD[0] << "value" << endl;
					}
				}
			}

			if (dChangeVal > DVDD_Search_Stop){
				DVDD_Search_Stop -= DVDD_Search_Step;
			} else {
				DVDD_Search_Stop += DVDD_Search_Step;
			}



			INT iFind_All = 0;
			//todo:CBB owner must make sure the condition of while is right, no infinite loop;
			//todo:add verify code here;
			double judgeWhile =   1e-5; // note DVDD_Search_Step must less than judgeWhile;
			//		while ((abs(dChangeVal - DVDD_Search_Stop) > 0.035) && ((iFind_All == 0) || (d2s_mode == LearningMode))) //tony debug
			while ((abs(dChangeVal - DVDD_Search_Stop) > judgeWhile) && ((iFind_All == 0) || (Global_D2S_Mode == LearningMode)))
			{

				//todo:call d2s_begin_end_block template and setup for each step
				cout << "========== VDD = " << dec << dChangeVal << " ==========" << endl;
				ReadBert_ExpectValue(MacroLane_Sel, mPRBS, ErrorCount);

				if (hout.IsEyePlotEn()) {
				    hout(DETAIL) << "========= DataRate = " << dec << CUSTpara.Data_Rate << " ==========" << endl;
				    GetEyeDiagram(MacroLane_Sel, CUSTpara.Data_Rate);
				}

				iFind_All = Update_LaneData_InTolerance(MacroLane_Sel, dChangeVal, ErrorCount, DVDDSearchResult, FindFlag);
				cout << "========== iFind_All = " << dec << iFind_All << " ==========" << endl;

				//todo:update spec here
				if (dChangeVal > DVDD_Search_Stop){
					dChangeVal -= DVDD_Search_Step;
				} else {
					dChangeVal += DVDD_Search_Step;
				}

				if (vDPSSpec_DVDD.size() > 0) {
					cout<<"============ DVDD_Search_Stop = "<<DVDD_Search_Stop<<"  dChangeVal ="<<dChangeVal <<endl;

					for (UINT i = 0; i < vDPSSpec_DVDD.size(); i ++) {
						TheSoft.Specs().SetValue("level_spec.spec", vDPSSpec_DVDD[i], dChangeVal);
					}
					if(isDPS128)
						TheInst.DCVI().Power().DynamicApply();
					else
						TheInst.DCVS().Power().DynamicApply();
				}
				else{
					cout<<"============= error vDPSSpec_DVDD.size()"<<endl;
				}
			}
		}

};
REGISTER_TESTCLASS("AVS_VERIFICATION", AVS_VERIFICATION);
