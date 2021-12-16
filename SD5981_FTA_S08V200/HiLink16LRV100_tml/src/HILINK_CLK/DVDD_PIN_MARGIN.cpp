//for test method API interfaces
//#include "sstream"
//#include "mapi.hpp"
//using namespace std;
//using namespace V93kLimits;

#include <HILINK_PUG/HiLink16_PUG.h>


class DVDD_PIN_MARGIN: public TestClass {
//NOTE: Program is using HEX 20141229 PUG 2.0.

public:

	STRING 				mHiLink16_MacroList;
	STRING				mPinList;
	INT                 mCSSlice;
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
		add_param("CSSlice","int",&mCSSlice)
					 .set_comment("mCSSlice")
					 //.set_options("0:1")
					 .set_default("0");
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
		static	MACRO_ARRAY_I		RW_Flag;


			//=============================================
			// Variables and MacroLane initialization
			//=============================================
			iOffline = 0;
			sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
			hout.setLevel(iPrintLvl);
			hout.printsuitename(sTestsuiteName);
			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

			d2s_JTAG& jtag = d2s_JTAG::Instance();

			RW_Flag.init(31, 0);

			DOUBLE	DVDDvalue = 0.8;
			for (INT	Index = 0; Index < 31; Index ++) {
//				try {
//					Primary.getLevelSpec().change("DVDD", DVDDvalue);
//					FLUSH(TM::APRM);
					TheSoft.Specs().SetValue("level_spec.spec", "DVDD", DVDDvalue);
					if(isDPS128)
						TheInst.DCVI().Power().DynamicApply();
					else
						TheInst.DCVS().Power().DynamicApply();

//				} catch (Error &error) {
////					Primary.getLevelSpec().change("DVDD", DVDDvalue);
////					FLUSH(TM::APRM);
//					TheSoft.Specs().SetValue("level_spec.spec", "DVDD", DVDDvalue);
//					if(isDPS128)
//						TheInst.DCVI().Power().DynamicApply();
//					else
//						TheInst.DCVS().Power().DynamicApply();
////					ERROR_EXIT(TM::RETURN_TO_FLOW);
//				}

				hout (DETAIL) << "Current DVDD value = " << DVDDvalue << endl;

				d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_Serilized_Write_SETUP",Global_D2S_Mode);
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					selectMacro(MacroID);
					CS.clkRegs.MacroID(MacroID).SliceID(mCSSlice).Broadcast(0);
					CS.clkRegs.Write2DUT(1,0x5a5a);
				}

				d2s::d2s_LABEL_END();

				d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_Serilized_Read_SETUP",Global_D2S_Mode);
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					selectMacro(MacroID);
					CS.clkRegs.MacroID(MacroID).SliceID(mCSSlice).Broadcast(0);

					ostringstream ID_Reading;
					ID_Reading << "SerilizedReading_M" << MacroID;
					CS.clkRegs.Read2IDString(1,ID_Reading.str());
				}

				d2s::d2s_LABEL_END();

				MACRO_INT			ReadBack;
				ReadBack.init(0);
				FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

					for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
					{
						UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
						ostringstream ID_Reading;
						ID_Reading << "SerilizedReading_M" << MacroID;
						ReadBack[SiteID][MacroID] = jtag.getReadValue(ID_Reading.str())[SiteID];

						if (0x5a5a == ReadBack[SiteID][MacroID]) {
							RW_Flag[SiteID][MacroID][Index] = 1;
						}
						hout(DETAIL) << "*************************** CSR read back *****************************" << endl;
						hout(DETAIL) << "Macro: " << dec << MacroID << ":  " << hex << ReadBack[SiteID][MacroID] << endl;
						hout(DETAIL) << "*************************** CSR read back *****************************" << endl;
					}
				FOREACH_ACTIVESITE_END

				DVDDvalue -= 0.01;
			}



			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					ostringstream 			plot_DVDD_hole;
					ostringstream 			plot_DVDD;
					for (INT	Index = 0; Index < 31; Index ++) {
						plot_DVDD << 0.8 - Index * 0.01 << " ";
						if (1 == RW_Flag[SiteID][MacroID][Index]) {
							plot_DVDD_hole << " * ";
						} else {
							plot_DVDD_hole << " . ";
						}
					}
					hout (RELEASE) << plot_DVDD.str() << endl;
					hout (RELEASE) << plot_DVDD_hole.str() << endl;
				}
			FOREACH_ACTIVESITE_END

		return;
		}

};
REGISTER_TESTCLASS("DVDD_PIN_MARGIN", DVDD_PIN_MARGIN);


