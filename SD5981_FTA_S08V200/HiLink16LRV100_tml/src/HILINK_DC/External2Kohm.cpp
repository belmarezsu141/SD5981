//for test method API interfaces
//#include "mapi.hpp"
//using namespace std;
//using namespace V93kLimits;
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include "TestClass.h"
//#include "CCTimer.h"
#include <UserAPI.h>
#include "type.h"
#include "HILINK_DRIVE/HiLink_Types.h"
#include <cmath>
#include <HILINK_PUG/HiLink16_PUG.h>

using namespace std;
using namespace PhxAPI;
/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class External2Kohm: public TestClass {

public:
	STRING 				mHiLink16_MacroList;
	STRING 				mPinList;
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
//		add_param("PinList","PinString",&mPinList);
		add_param("PrintLvl[0~15]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 10000(16)"
							     "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYE_PLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.set_options("0:1:3:4:7:9")
					 .set_default("3");
	}
	////////////////////////////////////////////////////////////////////////////////
	// TM Purpose:                                                                //
	// This TM is for resistor measurement by using PPMU, it is to measure        //
	// current step by step (range is as defined [0,Range_vol], and step of vol   //
	// is as defined Step_vol), to calculate res=delta(voltage)/delta(current).   //
	//																			  //
	// Parameters:																  //
	// 1. PinList: Pin list to be tested                                          //
	// 2. Range_vol: range of voltage, in mV                                      //
	// 3. Step_vol: step value of voltage, in mV                                  //
	////////////////////////////////////////////////////////////////////////////////
	/**
	 *This test is invoked per site.
	 */
	void execute()
	{

		m_TestName = TheSoft.Flow().Test().GetCurrentTestName();
		m_TestNumber  = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin  = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin  = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
		static	STRING          	sTestsuiteName;
		static	INT					iOffline;
		static  MACRO_LANE_SEL 		MacroLane_Sel;

		static	LANE_DOUBLE			TxDrvncaldn;
		static	LANE_DOUBLE			TxDrvncalup;
		static	LANE_DOUBLE			TxDrvncaldiff;

			//=============================================
			// Variables and MacroLane initialization
			//=============================================
			iOffline = 0;
			sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
			hout.setLevel(iPrintLvl);
			hout.printsuitename(sTestsuiteName);
			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

			d2s_JTAG& jtag = d2s_JTAG::Instance();

			SEGMENT_READ(MacroLane_Sel, DS.txRegs.REG_INFO.txdrvncaldn(), TxDrvncaldn);
			SEGMENT_READ(MacroLane_Sel, DS.txRegs.REG_INFO.txdrvncalup(), TxDrvncalup);

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						TxDrvncaldiff[SiteID][MacroID][LaneID] = abs(TxDrvncaldn[SiteID][MacroID][LaneID] - TxDrvncalup[SiteID][MacroID][LaneID]);
					}
				}
			FOREACH_ACTIVESITE_END

			if (iOffline){
				TxDrvncaldn.init(0x1a);
				TxDrvncalup.init(0x1a);
				TxDrvncaldiff.init(6);
			}


		//=============================================
		// Datalog
		//=============================================
		HiLink_PerLane_Judge(MacroLane_Sel,"External2Kohm_down",0.0,TxDrvncaldn,0.0,NONE);
		HiLink_PerLane_Judge(MacroLane_Sel,"External2Kohm_up",0.0,TxDrvncalup,0.0,NONE);
		HiLink_PerLane_Judge(MacroLane_Sel,"External2Kohm_diff",0.0,TxDrvncaldiff,0.0,NONE);

//		return;
	}

};
REGISTER_TESTCLASS("External2Kohm", External2Kohm);
