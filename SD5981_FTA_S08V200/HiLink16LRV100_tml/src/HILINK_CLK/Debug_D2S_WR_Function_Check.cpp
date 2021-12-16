//for test method API interfaces
//#include "sstream"
//#include "mapi.hpp"
//using namespace std;
//using namespace V93kLimits;

#include <HILINK_PUG/HiLink16_PUG.h>

class Debug_D2S_WR_Function_Check: public TestClass {
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

    void execute(){
		//=============================================
		// Common definition of TM for offline flag,
		// d2s mode, debug mode, test suite name, etc.
		//=============================================
		static	STRING          	sTestsuiteName;
		static	INT					iOffline;
		static  MACRO_LANE_SEL 		MacroLane_Sel;


			//=============================================
			// Variables and MacroLane initialization
			//=============================================
			iOffline = 0;
			sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();

			hout.setLevel(iPrintLvl);
			hout.printsuitename(sTestsuiteName);
			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

			d2s_JTAG& jtag = d2s_JTAG::Instance();

			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_Serilized_Write_SETUP",Global_D2S_Mode);
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				selectMacro(MacroID);
				CS.clkRegs.MacroID(MacroID).SliceID(mCSSlice).Broadcast(0);
				CS.clkRegs.Write2DUT(1,0x5a5b);
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

			//Get Back result:
			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					ostringstream ID_Reading;
					ID_Reading << "SerilizedReading_M" << MacroID;
					INT	readback = jtag.getReadValue(ID_Reading.str())[SiteID];

					hout(DETAIL) << "*************************** CSR read back *****************************" << endl;
					hout(DETAIL) << "Macro: " << dec << MacroID << ":  " << hex << readback << endl;
					hout(DETAIL) << "*************************** CSR read back *****************************" << endl;
				}
			FOREACH_ACTIVESITE_END

		return;
    }

};
REGISTER_TESTCLASS("Debug_D2S_WR_Function_Check", Debug_D2S_WR_Function_Check);


