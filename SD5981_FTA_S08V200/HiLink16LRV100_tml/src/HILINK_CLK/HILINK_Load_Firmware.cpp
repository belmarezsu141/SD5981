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
class HILINK_Load_Firmware: public TestClass {

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


			//=============================================
			// Variables and MacroLane initialization
			//=============================================
			iOffline = 0;
			sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
			hout.setLevel(iPrintLvl);
			hout.printsuitename(sTestsuiteName);
			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);

			d2s_JTAG& jtag = d2s_JTAG::Instance();

			MACRO_INT    mcupwrdb;
//			SEGMENT_READ(MacroLane_Sel, 0, MCU.mcuRegs.REG_INFO.mcupwrdb(), mcupwrdb);

//			fr.d2s_LABEL_BEGIN("H16LRTV100_MPB_LoadFirmWare_TestMB",d2sFrameWorkModeType::Enum(d2s_mode));
//
////				selectMacro_MB(MacroLane_Sel);
////				selectMacro(1);
////				DS.Broadcast();
//
////				DS.rxRegs.setcdrfreeze(1).Write2DUT(10);
//
//			fr.d2s_LABEL_END();

//			LANE_INT    cdrfreeze;
//			SEGMENT_READ(MacroLane_Sel, DS.rxRegs.REG_INFO.cdrfreeze(), cdrfreeze);

			Load_FirmWare(MacroLane_Sel);

			ReadFirmWareRevAndPrint(MacroLane_Sel);

			SEGMENT_READ(MacroLane_Sel, 0, MCU.mcuRegs.REG_INFO.mcupwrdb(), mcupwrdb);

		}

};
REGISTER_TESTCLASS("HILINK_Load_Firmware", HILINK_Load_Firmware);






















