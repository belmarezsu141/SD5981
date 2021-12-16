//for test method API interfaces
//#include "mapi.hpp"
//using namespace std;
//using namespace V93kLimits;

#include <HILINK_PUG/HiLink16_PUG.h>

/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class AnalogLos_Detection_PCIE_ATE: public TestClass {
public:
	STRING 				mHiLink16_MacroList;
	STRING 				mPinList;
	STRING 				sPinList;
	STRING 				sPinList_P;
	STRING 				sPinList_N;
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
		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
		static	STRING          	sTestsuiteName;
		static	INT					iOffline;
		static  MACRO_LANE_SEL 		MacroLane_Sel;

		static LANE_DOUBLE			All0_MinSwing;
		static LANE_DOUBLE			All1_MaxSwing;


			//=============================================
			// Variables and MacroLane initialization
			//=============================================
			iOffline = 0;
			sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
			hout.setLevel(iPrintLvl);
			hout.printsuitename(sTestsuiteName);
			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

			GetRxPinList(MacroLane_Sel, sPinList_P, sPinList_N, sPinList);

			/*** Connect PSSL AC Relay to DUT ****/
			if (CP_FT_Program == "FT") {
//				FLEX_RELAY frelay;
//				frelay.pin("pHilink16_TX,pHilink16_RX").set("AC","OFF");
//				frelay.execute();
//				frelay.wait(0.3 ms);
			}

			//=============================================
			// Device Setup
			//=============================================
			d2s_JTAG& jtag = d2s_JTAG::Instance();

			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_ANALOG_LOS_DET_PCIE_ATE_SETUP",Global_D2S_Mode);

				DS.rxRegs.addSkipCheckCSR(31);
				DS.rxRegs.addSkipCheckCSR(40);

				selectMacro_MB(MacroLane_Sel);
				DS.Broadcast();
				SetpmaMode();
				SetsigdetMode();

			d2s::d2s_LABEL_END();


			INT  				mSwing_H = 200;
			INT  				mSwing_L = 20;
			INT  				mStep = 10;
			STRING 				Analog_pattern_model = "ALOS_TS1_x16_pHilink16_RX_FASTDIFF";
			LONG 				Analog_pattern_cycle = 130000;
			DOUBLE 				org_spec_val, spec_val;

//			TransactionPort pRX("pHilink16_RX");
//			d2s::registerTransactionPort(pRX);
			//=============================================
			//measurement
			//=============================================
			LANE_INT	 		SigdetLosStat;
			SigdetLosStat.init(-99);
			All0_MinSwing.init(-99);
			All1_MaxSwing.init(-99);
			const INT 			ReadCnt = 10;
			LANE_INT 			Find_MinAll0_PerLane;
			LANE_INT 			Find_MaxAll1_PerLane;
			Find_MinAll0_PerLane.init(0);
			Find_MaxAll1_PerLane.init(0);
//			org_spec_val = Primary.getLevelSpec().getSpecValue("Vpp_se");
			org_spec_val = TheSoft.Specs().GetValue("level_spec.spec", "Vpp_se");
			bool isAll0Flag = true;
			spec_val = (mSwing_H / 2);

			INT iFind_All = 0;
			while (spec_val >= (mSwing_L / 2) && ((iFind_All == 0) || (Global_D2S_Mode == LearningMode)))
			{
//				try {
//					Primary.getLevelSpec().change("Vpp_se", spec_val, sPinList);
					TheSoft.Specs().SetValue("level_spec.spec", "Vpp_se", spec_val);
					if(isDPS128)
						TheInst.DCVI().Power().DynamicApply();
					else
						TheInst.DCVS().Power().DynamicApply();
//				} catch (Error &error) {
////					Primary.getLevelSpec().change("Vpp_se", org_spec_val, sPinList);
//					TheSoft.Specs().SetValue("level_spec.spec", "Vpp_se", org_spec_val);
//					FLUSH(TM::APRM);
//					ERROR_EXIT(TM::RETURN_TO_FLOW);
//				}

				//todo:print spec value for each step
				hout(DETAIL) << "========== Current value of spec = " << dec << spec_val << " ==========" << endl;

				if (isAll0Flag) {
					d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_ANALOG_LOS_PCIE_CheckAll0",Global_D2S_Mode);

						jtag.enablePassFailCheckForNextExecution();

//						pRX.execLabel(Analog_pattern_model, Analog_pattern_cycle);

						for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
						{
							UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
							const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

							selectMacro(MacroID);

							for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
							{
								UINT LaneID = vLane[laneIndex];
								DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
								for(INT ReadIdx = 0; ReadIdx < ReadCnt; ReadIdx ++)
								{
									DS.rxRegs.ExpectValue(61, 0, 0x7fff);
								}
							}
						}

					d2s::d2s_LABEL_END();

//					if (jtag.hasAllSitesPassed("H16LRTV100_MPB_ANALOG_LOS_PCIE_CheckAll0")) {
					if (hasAllSitesPassed()) {
						SigdetLosStat.init(ALL0);
					} else {
						isAll0Flag = false;
					}
				} else {
					AnalogLosCheck(MacroLane_Sel,ReadCnt,SigdetLosStat,Analog_pattern_model,Analog_pattern_cycle);
				}

				//todo:Other method for debugging delete this todo bolck if not use
				//call sub func Update_LaneData_InTolerance()
				//demo:iFind_All = Update_LaneData_InTolerance(MacroLane_Sel, FIR.iTxMain, ErrorCount, MinAmp, FindFlag);
				iFind_All = 1;

				FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
					for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
					{
						UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
						const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

						for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
						{
							UINT LaneID = vLane[laneIndex];
							/****************Log last All0 point**************/
							if (SigdetLosStat[SiteID][MacroID][LaneID] != ALL0) {
								if (0 == Find_MinAll0_PerLane[SiteID][MacroID][LaneID]) {
									All0_MinSwing[SiteID][MacroID][LaneID] = spec_val + (mStep / 2);
									Find_MinAll0_PerLane[SiteID][MacroID][LaneID] = 1;
								}
							}
							/****************Log first All1 point**************/
							if (SigdetLosStat[SiteID][MacroID][LaneID] == ALL1) {
								if (0 == Find_MaxAll1_PerLane[SiteID][MacroID][LaneID]) {
									All1_MaxSwing[SiteID][MacroID][LaneID] = spec_val;
									Find_MaxAll1_PerLane[SiteID][MacroID][LaneID] = 1;
								}
							} else {
								iFind_All = 0;
							}
						}
					}
				FOREACH_ACTIVESITE_END

				//todo:update spec here
				spec_val -= (mStep / 2);
			}

			//=============================================
			//restore
			//=============================================
//			Primary.getLevelSpec().change("Vpp_se", org_spec_val, sPinList);
			TheSoft.Specs().SetValue("level_spec.spec", "Vpp_se", org_spec_val);
//			FLUSH(TM::APRM);
			if(isDPS128)
				TheInst.DCVI().Power().DynamicApply();
			else
				TheInst.DCVS().Power().DynamicApply();

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						All0_MinSwing[SiteID][MacroID][LaneID] *= 2;
						All1_MaxSwing[SiteID][MacroID][LaneID] *= 2;
						if (iOffline) {
							All0_MinSwing[SiteID][MacroID][LaneID] = 50;
							All1_MaxSwing[SiteID][MacroID][LaneID] = 50;
						}
					}
				}
			FOREACH_ACTIVESITE_END

		//=============================================
		// Datalog
		//=============================================
//		HiLink_PerLane_Judge(MacroLane_Sel, "VppdSIG", All0_MinSwing);
//		HiLink_PerLane_Judge(MacroLane_Sel, "VppdLOS", All1_MaxSwing);

		return;
	}

	/**
	*This test is invoked per site.
	*/
//	virtual void run()
//	{

//	}

  /**
   *This function will be invoked once the specified parameter's value is changed.
   *@param parameterIdentifier
   */
//  virtual void postParameterChange(const string& parameterIdentifier)
//  {
//		//Add your code
//		//Note: Test Method API should not be used in this method!
//		bool visible = (mHiLink16_MacroList == "FromPinList");
//		getParameter("PinList").setVisible(visible);
//
//
//		return;
//  }
//
//  /**
//   *This function will be invoked once the Select Test Method Dialog is opened.
//   */
//  virtual const string getComment() const
//  {
//		string comment = " please add your comment for this method.";
//		return comment;
//  }
};
REGISTER_TESTCLASS("AnalogLos_Detection_PCIE_ATE", AnalogLos_Detection_PCIE_ATE);
