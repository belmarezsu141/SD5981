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

class IO_N_M3_Vtl_HT: public TestClass {
public:
	STRING 				mHiLink16_MacroList;
	STRING 				mPinList;
	STRING 				sHVCCSPEC;
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
		add_param("HVCC_SpecName","string",&sHVCCSPEC)
					 .set_comment("Each Spec is one-to-one correspondence to each HVCC_Pin, support ARRAY");
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

			hout(GENERAL) << "####### PowerDown HVCC to monitor IO_N m3 Vtl voltage #######" << endl;
			STRING_VECTOR 			vDPSSpec_HVCC;
			ARRAY_D					aOrgVal;
			parseListOfString(sHVCCSPEC,vDPSSpec_HVCC,',');
			aOrgVal.resize(vDPSSpec_HVCC.size());

			if (vDPSSpec_HVCC.size() > 0) {
				for (UINT i = 0; i < vDPSSpec_HVCC.size(); i ++) {
//					aOrgVal[i] = Primary.getLevelSpec().getSpecValue(vDPSSpec_HVCC[i]);
					aOrgVal[i] = TheSoft.Specs().GetValue("level_spec.spec", vDPSSpec_HVCC[i]);
//					Primary.getLevelSpec().change(vDPSSpec_HVCC[i], 0);
					TheSoft.Specs().SetValue("level_spec.spec", vDPSSpec_HVCC[i], 0);
				}
			}
//			FLUSH(TM::APRM);
			if(isDPS128)
				TheInst.DCVI().Power().DynamicApply();
			else
				TheInst.DCVS().Power().DynamicApply();


            double tmp = 4/0.3;
//            Primary.getLevelSpec().change("var1",(tmp));
            TheSoft.Specs().SetValue("level_spec.spec", "var1", tmp);
//            Primary.getLevelSpec().change("var2",4);
            TheSoft.Specs().SetValue("level_spec.spec", "var2", 4);
//            Primary.getLevelSpec().change("HVCC18_H16_1V8",0.3);
            TheSoft.Specs().SetValue("level_spec.spec", "HVCC18_H16_1V8", 0.3);
//            FLUSH(TM::APRM);
			if(isDPS128)
				TheInst.DCVI().Power().DynamicApply();
			else
				TheInst.DCVS().Power().DynamicApply();


//            WAIT_TIME(20 ms);
            TheInst.Wait(0.001*20);
            tmp = 4/1.14;
//            Primary.getLevelSpec().change("var1",tmp);
            TheSoft.Specs().SetValue("level_spec.spec", "var1", tmp);
//            Primary.getLevelSpec().change("var2",4);
            TheSoft.Specs().SetValue("level_spec.spec", "var2", 4);
//            Primary.getLevelSpec().change("HVCC18_H16_1V8",1.44);
            TheSoft.Specs().SetValue("level_spec.spec", "HVCC18_H16_1V8", 1.44);
//            FLUSH(TM::APRM);
			if(isDPS128)
				TheInst.DCVI().Power().DynamicApply();
			else
				TheInst.DCVS().Power().DynamicApply();


//            WAIT_TIME(11 ms);
            TheInst.Wait(0.001*11);


			if (Global_D2S_Mode == LearningMode) {
				hout(REG_ACCESS) << "***************  Just After Initial Hilink ***************" << endl;
				FWreadDefaultRegisters2CSR(MacroLane_Sel);
			}

		return;
		}

};
REGISTER_TESTCLASS("IO_N_M3_Vtl_HT", IO_N_M3_Vtl_HT);

