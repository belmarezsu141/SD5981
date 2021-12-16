////////////////////////////////////////////////////////////////////////////////
// Description:                                                               //
// This c++ file is instance of Hilink15 realated API, it contains Calibration//
// ,Read Bert and EyeDiagram's code. link with PUG							  //
////////////////////////////////////////////////////////////////////////////////

#include <Common_Func/HiLink30_Common_Func.h>
//#include "Nautilus.h"
//#include "api.h"
//using namespace MuTest;

using namespace PhxAPI;

string GlobalInitPattern = " ";
//Define global variables

vector<vector<CtleResultPerLane> > vCtleResultPerMacroPerLane;
vector<vector<DFEResultPerLane> > vDfeResultPerMacroPerLane;
//Write by jz Start

//HiLink StartUp




//HiLinkReset and PowerUp/down
//====================================================================================
// Function: MacroPowerUp
// - This function is used for macro power up and grstb sequence setting.
// - DsNum: Total DS number in current macro.
// - DsIdNorthCs: The ID of DS on the north side of CS.
// - Don not power up multi-macro at the same time, otherwise may cause power integrity issue.
// - The return value can be 0/1, 0 means power up timeout, user need to double check the refclk and power supply, etc.
//====================================================================================

bool MacroPowerUp(MACRO_LANE_SEL& MacroLane_Sel, const STRING& PowerUpPattern, const STRING& InitPattern, const string workingmode) {
    d2s_IP_JTAG & jtag = d2s_IP_JTAG::Instance();

    const char * PowerUpCtrl_test = PowerUpPattern.c_str();
    const char * Init_test = InitPattern.c_str();
    /**************Clear API and CSConfigBeforeCal***set proper API depending on applications and Release MCU*********/
    if (workingmode == "PowerUp+ChangeLevel+Init" || workingmode == "PowerUp+Init") {
        //PowerUp
        PowerUpCtrl_test1();
//        api->sleep(0.01);
//        TheInst.Wait(0.01);
    	TheInst.Wait(0.01);

        //Init
       Init_test1();
//        api->sleep(0.01);
//       TheInst.Wait(0.01);
   	TheInst.Wait(0.01);
    } else if (workingmode == "Init") {
        //Init
       Init_test1();
//        api->sleep(0.01);
//       TheInst.Wait(0.01);
   	TheInst.Wait(0.01);
    }

    //        ALL_CSR_ReadBack_TO_FILE_Debug(MacroLane_Sel,"Before_MacroDsPowerUp");

    d2s::d2s_LABEL_BEGIN("MacroPowerUp_SetUp_", Global_D2S_Mode); //Global_D2S_Mode
    selectMacro_MB(MacroLane_Sel);
    CS.clkRegs.MacroID(MacroLane_Sel[0].MacroID).SliceID(0).Broadcast(0);
    CS.clkRegs.setpll0vregpllbleedb(0x1).setpll0vregdlfbleedb(0x1).Write2DUT(14);
    CS.clkRegs.setpll0vregvcodivbleedb(0x1).Write2DUT(15);
    CS.clkRegs.setpll1vregpllbleedb(0x1).setpll1vregdlfbleedb(0x1).Write2DUT(23);
    CS.clkRegs.setpll1vregvcodivbleedb(0x1).Write2DUT(24);
    jtag.wait(0.0001);

    for (uint iMacroIndex = 0; iMacroIndex < MacroLane_Sel.size(); iMacroIndex++) {
        UINT MacroID = MacroLane_Sel[iMacroIndex].MacroID;
        selectMacro(MacroID);
        for (uint iLaneIndex = 0; iLaneIndex < HILINK_INFO[MacroID].Lane_Num; iLaneIndex++)//SongXin: all DS should be power up
        {
            int power_lane = HILINK_INFO[MacroID].DS_powerup_sequence[iLaneIndex];
            if (power_lane < 0) break;
            DsPowerUpWiClkDis(MacroID, power_lane);
            jtag.wait(0.0001);
        }
    }

    d2s::d2s_LABEL_END();

    //        api->sleep(0.001);
    //        
    //        MacroDsPowerUp (MacroLane_Sel);

    //time debug
    //        LARGE_INTEGER litmp;
    //        double dfFreq;
    //        QueryPerformanceFrequency(&litmp);
    //        dfFreq = (double)litmp.QuadPart;
    //        LONGLONG T_ST=0,T_SP=0;
    //    
    //        QueryPerformanceCounter(&litmp);
    //        T_SP=litmp.QuadPart;
    //        double Excute_time = (T_SP-T_ST)/dfFreq*1e3;
    //        T_ST = T_SP;
    //
    //        QueryPerformanceCounter(&litmp);
    //        T_SP=litmp.QuadPart;
    //        Excute_time = (T_SP-T_ST)/dfFreq*1e3;
    //        T_ST = T_SP;
    //        printf("##Execution Time_d2srunpattern = %f",Excute_time);
    return true;
}


//====================================================================================
// Function: MacroPowerDown
// - This function is used for macro power down sequence setting.
//====================================================================================

void MacroPowerDown(MACRO_LANE_SEL& vMacroLane_Sel, const STRING& PowerUpPattern) {  //this func just be used in MIN_MAX_PWR
    STRING sInitPatLable;
    //if (TestChip == 1){
#ifdef TestChip
    if (vMacroLane_Sel.size() > 1) {
        sInitPatLable = "mpb_POWER_DOWN_ALL_pLS";
    } else if (vMacroLane_Sel[0].MacroID == 0) {
        sInitPatLable = "mpb_POWER_DOWN_BP_pLS";
    } else if (vMacroLane_Sel[0].MacroID == 1) {
        sInitPatLable = "mpb_POWER_DOWN_C2C_pLS";
    }
    //	}
#else
    //	if (TestChip == 0){
    ///		sInitPatLable=PowerUpPattern;
    //	}
#endif
    ///		Primary.label(sInitPatLable);
    ///		FUNCTIONAL_TEST();
//    api->Execute_test("HILINK_R01_SD5875V100_PowerUpSeqCtrl_ALL_3_X1_SM_V2");//tony ,wait for modify 
    HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1();
    
}
//====================================================================================
// Function: MacroPowerDown
// - This function is used for macro power down sequence setting.
//====================================================================================

void MacroPowerDown(UINT iMacroIndex, const STRING& PowerUpPattern) {
    STRING sInitPatLable;
#ifdef TestChip
    if (iMacroIndex == 2)//BP&C2C
    {
        sInitPatLable = "mpb_POWER_DOWN_ALL_pLS";
    } else if (iMacroIndex == 0) {
        sInitPatLable = "mpb_POWER_DOWN_BP_pLS";
    } else if (iMacroIndex == 1) {
        sInitPatLable = "mpb_POWER_DOWN_C2C_pLS";
    }
#else
    //		sInitPatLable=PowerUpPattern;
#endif

    //	Primary.label(sInitPatLable);
    //	FUNCTIONAL_TEST();
}

//====================================================================================
// Function: MacroPowerDown
// - This function is used for power up all DS in the macro
// - The return value can be 0/1, 0 means power up timeout, uesr need to double check the refclk and power supply,etc
//====================================================================================

bool MacroDsPowerUp(MACRO_LANE_SEL& vMacroLane_Sel) {
    d2s_IP_JTAG & jtag = d2s_IP_JTAG::Instance();
    d2s::d2s_LABEL_BEGIN("H30_DsPowerUpWiClkDis_SetUp_Part1_", Global_D2S_Mode);
    for (uint iMacroIndex = 0; iMacroIndex < vMacroLane_Sel.size(); iMacroIndex++) {
        UINT MacroID = vMacroLane_Sel[iMacroIndex].MacroID;
        selectMacro(MacroID);
        for (uint iLaneIndex = 0; iLaneIndex < HILINK_INFO[MacroID].Lane_Num; iLaneIndex++)//SongXin: all DS should be power up
        {
            int power_lane = HILINK_INFO[MacroID].DS_powerup_sequence[iLaneIndex];
            if (power_lane < 0) break;
            DsPowerUpWiClkDis(MacroID, power_lane);
            jtag.wait(0.0001);
        }
    }
    d2s::d2s_LABEL_END();
    return true;
}

//=============================================================================
// Function: MacroDsPowerDown
// - This function is used for power down all DS in the macro.
// - The return value can be 0/1, 0 means power down timeout, user need to double check the refclk and power supply, etc.
//=============================================================================

bool MacroDsPowerDown(MACRO_LANE_SEL& vMacroLane_Sel) {
    for (uint iMacroIndex = 0; iMacroIndex < vMacroLane_Sel.size(); iMacroIndex++) {
        UINT MacroID = vMacroLane_Sel[iMacroIndex].MacroID;

        for (uint iLaneIndex = 0; iLaneIndex < HILINK_INFO[MacroID].Lane_Num; iLaneIndex++)//SongXin: all DS should be power down
        {
            int power_lane = HILINK_INFO[MacroID].DS_powerdown_sequence[iLaneIndex];
            if (power_lane < 0) break;
            DsPowerUpWiClkDis(MacroID, power_lane);
        }
    }
    return true;
}

//==============================================================================
// Function: RxPowerUpDown
// - This function is used for power up/down RX.
// - powerType: 0=power down; 1=power up.
//==============================================================================

bool RxPowerUpDown(uint iMacroID, uint iLaneIndex, uint iPowerType) {

    //    D2S_FRAMEWORK;
    //    //GET_TEST_INFO;
    d2s_JTAG& jtag = d2s_JTAG::Instance();
    uint Rxpwrdb;

    //    sprintf(label,"RxPowerUpDown_RXPWRDB_Read_%f_%f_",Vcoef,Temp);
    d2s::d2s_LABEL_BEGIN("RxPowerUpDown_RXPWRDB_Read_", Global_D2S_Mode);
    //fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    selectMacro(iMacroID);
    DS.rxRegs.MacroID(iMacroID).SliceID(iLaneIndex).Broadcast(0);
    DS.rxRegs.Read2IDString(0, "id_RxPowerUpDown");
    //fr.d2s_LABEL_END();

    d2s::d2s_LABEL_END();

    ARRAY_I org_active_sites;
    //	GET_TEST_FOCUS(org_active_sites);
    //	SET_TEST_FOCUS(get_focus_site());

    //FOR_EACH_SITE_BEGIN();

//    FOREACH_ACTIVE_SITE(api) {
    	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
        uint val = (UINT) jtag.getReadValue("id_RxPowerUpDown")[SiteID];
        Rxpwrdb = HILINK_Regs_Base::get_bits(val, DS.rxRegs.REG_INFO.rxpwrdb());
        FOREACH_ACTIVESITE_END
    //	SET_TEST_FOCUS(org_active_sites);

    //	sprintf(label,"RxPowerUpDown_RXPWRDB_Set_%f_%f_",Vcoef,Temp);
    //fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("RxPowerUpDown_RXPWRDB_Set_", Global_D2S_Mode);
    selectMacro(iMacroID);
    DS.rxRegs.MacroID(iMacroID).SliceID(iLaneIndex).Broadcast(0);
    if (iPowerType != Rxpwrdb) {
        if (0x0 == iPowerType) {
            // Enable Rx CTLE/DFE/CLOCK/DATA regulator bleed current
            DS.rxRegs.setvregclkbleedb(0x0).setvregdatableedb(0x0).Write2DUT(53, false);
        }
        DS.rxRegs.setrxpwrdb((uint) iPowerType).Write2DUT(0, false);
        jtag.wait(50);
//        api->sleep(0.00005);
        if (0x1 == iPowerType) {
            // Disable Rx CTLE/DFE/CLOCK/DATA regulator bleed current
            DS.rxRegs.setvregclkbleedb(0x1).setvregdatableedb(0x1).Write2DUT(53, false);
        }
    }
    //fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();

    return true;
}


//==============================================================================
// Function: TxPowerUpDown
// - This function is used for power up/down TX.
// - powerType: 0=power down; 1=power up.
//==============================================================================

bool TxPowerUpDown(uint iMacroID, uint iLaneIndex, uint iPowerType) {
    //    D2S_FRAMEWORK;
    //    //GET_TEST_INFO;
    d2s_JTAG& jtag = d2s_JTAG::Instance();
    uint Txpwrdb;
    //    sprintf(label,"TxPowerUpDown_TXPWRDB_Read_%f_%f_",Vcoef,Temp);
    //fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("TxPowerUpDown_TXPWRDB_Read_", Global_D2S_Mode);
    selectMacro(iMacroID);
    DS.txRegs.MacroID(iMacroID).SliceID(iLaneIndex).Broadcast(0);
    DS.txRegs.Read2IDString(0, "id_TxPowerUpDown");
    //fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();

    ARRAY_I org_active_sites;
    //	GET_TEST_FOCUS(org_active_sites);
    //	SET_TEST_FOCUS(get_focus_site());

    //FOR_EACH_SITE_BEGIN();

//    FOREACH_ACTIVE_SITE(api) {
    	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
        uint val = (UINT) jtag.getReadValue("id_TxPowerUpDown")[SiteID];
        Txpwrdb = HILINK_Regs_Base::get_bits(val, DS.txRegs.REG_INFO.txpwrdb());
        FOREACH_ACTIVESITE_END

    //	SET_TEST_FOCUS(org_active_sites);

    //	sprintf(label,"TxPowerUpDown_TXPWRDB_Set_%f_%f_",Vcoef,Temp);
    d2s::d2s_LABEL_BEGIN("TxPowerUpDown_TXPWRDB_Set_", Global_D2S_Mode);
    //fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    if (iPowerType != Txpwrdb) {
        if (0x0 == iPowerType) {
            // Enable Tx Drv and Clk regulator bleed current
            DS.txRegs.settxdrvregbleedb(0x0).Write2DUT(12, false);
        }
        DS.txRegs.settxpwrdb((uint) iPowerType).Write2DUT(0, false);
        jtag.wait(50);
//        api->sleep(0.00005);
//        TheInst.Wait(50);
        if (0x1 == iPowerType) {
            // Disable Tx Drv and Clk regulator bleed current
            DS.txRegs.settxdrvregbleedb(0x1).Write2DUT(12, false);
        }
    }
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    return true;
}

//==============================================================================
// Function: DsPowerUpWiClkDis
// - This function is used for power up whole DS include high speed clock distribution
// - iLaneIndex: the ID of current DS
// - Do not power up multi-DS as the same time, and the DS closer to CS should be powered up first, ohterwise may
//   cause power integrity issue
// - The return value can be 0/1, 0 means power up timeout, user need to double check the refclk and power supply, etc
//==============================================================================

bool DsPowerUpWiClkDis(uint uiMacroID, int iLaneIndex) {
    /**************Clear API and CSConfigBeforeCal***set proper API depending on applications and Release MCU*********/


    d2s_IP_JTAG & jtag = d2s_IP_JTAG::Instance();
    DS.clkRegs.MacroID(uiMacroID).SliceID(iLaneIndex).Broadcast(0);
    DS.rxRegs.MacroID(uiMacroID).SliceID(iLaneIndex).Broadcast(0);
    DS.txRegs.MacroID(uiMacroID).SliceID(iLaneIndex).Broadcast(0);
    // Enable DSCLK regulator bleed current
    DS.clkRegs.setvregbleedb(0x0).Write2DUT(1, false);
    // Enable Rx CTLE/DFE/CLOCK/DATA regulator bleed current
    DS.rxRegs.setvregclkbleedb(0x0).setvregdatableedb(0x0).Write2DUT(53, false);
    // Enable Tx Drv and Clk regulator bleed current
    DS.txRegs.settxdrvregbleedb(0x0).Write2DUT(12, false);
    // Start DS power up squence
    DS.clkRegs.setdspwrdb(0x1).Write2DUT(0, false);
    jtag.wait(0.00005);
    // Disable DSCLK regulator bleed current
    DS.clkRegs.setvregbleedb(0x1).Write2DUT(1, false);
    // Disable Rx CTLE/DFE/CLOCK/DATA regulator bleed current
    DS.rxRegs.setvregclkbleedb(0x1).setvregdatableedb(0x1).Write2DUT(53, false);
    // Disable Tx Drv and Clk regulator bleed current
    DS.txRegs.settxdrvregbleedb(0x1).Write2DUT(12, false);

    return EXIT_SUCCESS;
}

//==============================================================================
// Function: DsPowerDownWoClkDis
// - This function is used for power down whole DS without high speed clock distribution.
// - dsIndex: The ID of current DS.
// - This function can only used when DSCLK/RX/TX are all have been powered on.
// - Don not power down multi-DS at the same time, otherwise may cause power integrity issue.
// - The return value can be 0/1, 0 means power down timeout, user need to double check the refclk and power sdownply, etc.
//==============================================================================

bool DsPowerDownWoClkDis(MACRO_LANE_SEL& vMacroLane_Sel) {
    //D2S_FRAMEWORK;
    //GET_TEST_INFO;
    // Power down RX & TX.

    for (uint iMacroIndex = 0; iMacroIndex < vMacroLane_Sel.size(); iMacroIndex++) {
        UINT MacroID = vMacroLane_Sel[iMacroIndex].MacroID;

        for (uint iLaneIndex = 0; iLaneIndex < HILINK_INFO[MacroID].Lane_Num; iLaneIndex++)//SongXin: all DS should be power down
        {
            int power_lane = HILINK_INFO[MacroID].DS_powerdown_sequence[iLaneIndex];
            if (power_lane < 0) break;

            RxPowerUpDown(MacroID, power_lane, 0);
        }
    }

    for (uint iMacroIndex = 0; iMacroIndex < vMacroLane_Sel.size(); iMacroIndex++) {
        UINT MacroID = vMacroLane_Sel[iMacroIndex].MacroID;

        for (uint iLaneIndex = 0; iLaneIndex < HILINK_INFO[MacroID].Lane_Num; iLaneIndex++)//SongXin: all DS should be power down
        {
            int power_lane = HILINK_INFO[MacroID].DS_powerdown_sequence[iLaneIndex];
            if (power_lane < 0) break;

            TxPowerUpDown(MacroID, power_lane, 0);
        }
    }

    //	sprintf(label,"DsPowerDownWoClkDis_QDIV2PWRDB_Set_%f_%f_",Vcoef,Temp);
    // fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("DsPowerDownWoClkDis_QDIV2PWRDB_Set_", Global_D2S_Mode);
    for (uint MacroIndex = 0; MacroIndex < vMacroLane_Sel.size(); MacroIndex++) {
        UINT MacroID = vMacroLane_Sel[MacroIndex].MacroID;
        selectMacro(MacroID);
        for (uint LaneIndex = 0; LaneIndex < HILINK_INFO[MacroID].Lane_Num; LaneIndex++) {
            DS.clkRegs.MacroID(MacroID).SliceID(HILINK_INFO[MacroID].DS_powerdown_sequence[LaneIndex]).Broadcast(0);
            DS.clkRegs.setqdiv2pwrdb(0x0).Write2DUT(1, false);
        }
    }
    //   fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //   WAIT_TIME(50 uS);
//    api->sleep(0.000005);
//    TheInst.Wait(50); //masked by tony 20210910
    sleep(0.05);
    return true;
}

//====================================================================================
// Function: DsPowerDownWiClkDis
// - This function is used for power down whole DS include high speed clock distribution.
// - dsIndex: The ID of current DS.
// - Don not power down multi-DS at the same time, and the DS farther from CS should be powered down first, otherwise may
//    cause power integrity issue.
// - The return value can be 0/1, 0 means power down timeout, user need to double check the refclk and power sdownply, etc.
//====================================================================================

bool DsPowerDownWiClkDis(int MacroID, int LaneIndex) {
    //	D2S_FRAMEWORK;
    //	//GET_TEST_INFO;
	d2s_JTAG& jtag = d2s_JTAG::Instance();

    //	sprintf(label,"DsPowerDownWiClkDis_DSPWRDB_set_%f_%f_",Vcoef,Temp);
    //fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("DsPowerDownWiClkDis_DSPWRDB_set_", Global_D2S_Mode);
    selectMacro(MacroID);
    DS.clkRegs.MacroID(MacroID).SliceID(LaneIndex).Broadcast(0);
    DS.rxRegs.MacroID(MacroID).SliceID(LaneIndex).Broadcast(0);
    DS.txRegs.MacroID(MacroID).SliceID(LaneIndex).Broadcast(0);

    DS.clkRegs.setvregbleedb(0x0).Write2DUT(1, false);
    DS.rxRegs.setvregclkbleedb(0x0).Write2DUT(53, false);
    DS.rxRegs.setvregdatableedb(0x0).Write2DUT(53, false);
    DS.txRegs.settxdrvregbleedb(0x0).Write2DUT(12, false);
    DS.clkRegs.setdspwrdb(0x0).Write2DUT(0, false);
//    api->sleep(0.00005);
    jtag.wait(50);

    DS.clkRegs.setvregbleedb(0x1).Write2DUT(1, false);
    DS.rxRegs.setvregclkbleedb(0x1).Write2DUT(53, false);
    DS.rxRegs.setvregdatableedb(0x1).Write2DUT(53, false);
    DS.txRegs.settxdrvregbleedb(0x1).Write2DUT(12, false);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();

    return true;

}

//Clockslice Configuration before Calibration
//====================================================================================
// Function: CsPllPowerUp
// - This function is used for power up PLL in CS.
// - pllIndex: The index of PLL to be powered up, 0 for power up both PLL0 only, 1 for power up both PLL0 and PLL1.
// - PLL1 can be powered up only when PLL0 have been powered up.
// - The return value can be 0/1, 0 means power up timeout, user need to double check the refclk and power supply, etc.
//====================================================================================

bool CsPllPowerup(MACRO_LANE_SEL& MacroLane_Sel, INT pllIndex) {
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    d2s::d2s_LABEL_BEGIN("CSConfig_BeforeCal_CsPllPowerUp_Enable_pll0_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    CS.clkRegs.SliceID(0).Broadcast(0);

    //Enable bleed current control
    CS.clkRegs.setpll0vregpllbleedb(0x0).Write2DUT(14);
    CS.clkRegs.setpll0vregdlfbleedb(0x0).Write2DUT(14);
    CS.clkRegs.setpll0vregvcodivbleedb(0x0).Write2DUT(15);
    CS.clkRegs.setpll0pwrdb(0x1).Write2DUT(8); //Power up PLL0

    if (0x1 == pllIndex) {
        //Enable bleed current control
        CS.clkRegs.setpll1vregpllbleedb(0x0).Write2DUT(23);
        CS.clkRegs.setpll1vregdlfbleedb(0x0).Write2DUT(23);
        CS.clkRegs.setpll1vregvcodivbleedb(0x0).Write2DUT(24);

        CS.clkRegs.setpll1pwrdb(0x1).Write2DUT(17);
    }

    jtag.wait(0.00005);

    //Disable bleed current control
    CS.clkRegs.setpll0vregpllbleedb(0x1).Write2DUT(14);
    CS.clkRegs.setpll0vregdlfbleedb(0x1).Write2DUT(14);
    CS.clkRegs.setpll0vregvcodivbleedb(0x1).Write2DUT(15);

    if (0x1 == pllIndex) {
        //Disable bleed current control
        CS.clkRegs.setpll1vregpllbleedb(0x1).Write2DUT(23);
        CS.clkRegs.setpll1vregdlfbleedb(0x1).Write2DUT(23);
        CS.clkRegs.setpll1vregvcodivbleedb(0x1).Write2DUT(24);
    }

    // Power on buffer of DS on the north and south side of CS, the DS physically close to CS should be powered dowm first.
    for (uint MacroIndex = 0; MacroIndex < MacroLane_Sel.size(); MacroIndex++) {
        UINT MacroID = MacroLane_Sel[MacroIndex].MacroID;
        selectMacro(MacroID);

        for (uint i = 0; i < HILINK_INFO[MacroID].Lane_Num; i++) {
            int power_lane = HILINK_INFO[MacroID].DS_powerup_sequence[i];
            DS.clkRegs.MacroID(MacroID).SliceID(power_lane).Broadcast(0);
            DS.clkRegs.setbuf0pwrdb(0x1).setbuf1pwrdb(pllIndex)
                    .Write2DUT(0, false);
        }
    }
    d2s::d2s_LABEL_END();

    return true;
}
//====================================================================================
//Function: CsPllPowerDown
// - This function is used for power down PLL in CS
// - pllIndex: The index of PLL to be powered down, 0 for power down both PLL0 and PLL1, 1 for power down PLL1 only.
// - PLL0 can be powered down only when PLL1 have been powered down.
//====================================================================================

bool CsPllPowerDown(MACRO_LANE_SEL& MacroLane_Sel, INT pllIndex) {
    //	D2S_FRAMEWORK;
    //	//GET_TEST_INFO;
    d2s_IP_JTAG & jtag = d2s_IP_JTAG::Instance();
    //	sprintf(label,"CSConfig_BeforeCal_CsPllPowerDown_%f_%f_",Vcoef,Temp);
    //fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("CSConfig_BeforeCal_CsPllPowerDown_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    CS.clkRegs.MacroID(MacroLane_Sel[0].MacroID).SliceID(0).Broadcast(0);
    CS.clkRegs.setcoreclksel(0).Write2DUT(6);
    // Power down buffer of DS on the north and south side of CS, the DS physically close to CS should be powered dowm first.
    for (uint uiMacroIndex = 0; uiMacroIndex < MacroLane_Sel.size(); uiMacroIndex++) {
        UINT MacroID = MacroLane_Sel[uiMacroIndex].MacroID;
        selectMacro(MacroID);
        for (uint i = 0; i < HILINK_INFO[MacroID].Lane_Num; i++) {
            int power_lane = HILINK_INFO[MacroID].DS_powerdown_sequence[i];
            DS.clkRegs.MacroID(MacroID).SliceID(power_lane).Broadcast(0);
            DS.clkRegs.setbuf0pwrdb(pllIndex).setbuf1pwrdb(0x0).Write2DUT(0, false);
        }
    }

    selectMacro_MB(MacroLane_Sel);
    //Enable bleed current control
    CS.clkRegs.setpll1vregpllbleedb(0x0).Write2DUT(23);
    CS.clkRegs.setpll1vregdlfbleedb(0x0).Write2DUT(23);
    CS.clkRegs.setpll1vregvcodivbleedb(0x0).Write2DUT(24);

    CS.clkRegs.setpll1pwrdb(0x0).Write2DUT(17); //Power down PLL1

    if (0x0 == pllIndex) {
        //Enable bleed current control
        CS.clkRegs.setpll0vregpllbleedb(0x0).Write2DUT(14);
        CS.clkRegs.setpll0vregdlfbleedb(0x0).Write2DUT(14);
        CS.clkRegs.setpll0vregvcodivbleedb(0x0).Write2DUT(15);

        CS.clkRegs.setpll0pwrdb(0x0).Write2DUT(8); //Power down PLL0
    }
    jtag.wait(0.00005);

    //Disable bleed current control
    CS.clkRegs.setpll1vregpllbleedb(0x1).Write2DUT(23);
    CS.clkRegs.setpll1vregdlfbleedb(0x1).Write2DUT(23);
    CS.clkRegs.setpll1vregvcodivbleedb(0x1).Write2DUT(24);

    if (0x0 == pllIndex) {
        //Disable bleed current control
        CS.clkRegs.setpll0vregpllbleedb(0x1).Write2DUT(14);
        CS.clkRegs.setpll0vregdlfbleedb(0x1).Write2DUT(14);
        CS.clkRegs.setpll0vregvcodivbleedb(0x1).Write2DUT(15);
    }
    //fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    return true;
}

//====================================================================================
// Function: CsConfigurationBeforeCalibration
// - This function is for CS general settings before calibration.
// - For all "User Setting" parameters, please refer to H30's frequency plan.
//====================================================================================

void CSConfigurationBeforeCalibration_SSConfig(MACRO_LANE_SEL& MacroLane_Sel, CUSTPARA &CUSTpara, SSPARA &SSpara) {

    /**************Clear API and CSConfigBeforeCal***set proper API depending on applications and Release MCU*********/
    hout(DETAIL) << "\n&&&&&&&&&&&&& CS calibration START! &&&&&&&&&&&&&&&\n" << endl;

    //-------------------- User Define Settings(PUG Don't have these settings) Begin -------------------------
    INT iSsrefclk0div2sel = SSpara.SDiv - 1; //frequency plan for 1,2 but regist for 0,1.so need -1
    INT iSsrefclk1div2sel = SSpara.SDiv - 1;
    // -------------------- User Define Settings(PUG Don't have these settings) End -------------------------

    d2s::d2s_LABEL_BEGIN("CSConfig_BeforeCal_Setrefclk_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    CS.clkRegs.MacroID(MacroLane_Sel[0].MacroID).SliceID(0).Broadcast(0); //only one CS in one macro
    //Select correct clock source for Serviceslice if this macro coutains
    //Serviceslice
    CS.clkRegs.setssrefclk0div2sel(iSsrefclk0div2sel).Write2DUT(34);
    CS.clkRegs.setssrefclk1div2sel(iSsrefclk1div2sel).Write2DUT(34);

    if (iSsrefclk0div2sel == 0x1) // div by 2
    {
        CS.clkRegs.setssrefclk0cmldivpwrdb(0x1).Write2DUT(34); //Power up refclk cml divider
    } else {
        CS.clkRegs.setssrefclk0cmldivpwrdb(0x0).Write2DUT(34);
    }
    if (iSsrefclk1div2sel == 0x1) // div by 2
    {
        CS.clkRegs.setssrefclk1cmldivpwrdb(0x1).Write2DUT(34);
    } else {
        CS.clkRegs.setssrefclk1cmldivpwrdb(0x0).Write2DUT(34);
    }
    d2s::d2s_LABEL_END();
}


// Clear CS DS API
//====================================================================================
// Function: CsCalibrationBypassConfig
// - This function used to set CS calibration bypass APIs.
// - Please refer to the API register doc to get API detail description.
//====================================================================================

void Clear_CS_API() {
    UINT csr_num = SRAM.CSAPIRegs.getCSRCount();
    for (UINT csrIndex = 0; csrIndex < csr_num; csrIndex++) {
        SRAM.CSAPIRegs.Write2DUT(csrIndex, 0);
    }
}

void Clear_DS_API(MACRO_LANE_SEL& MacroLane_Sel) {
    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        selectMacro(MacroID);
        UINT csr_num = SRAM.DSAPIRegs.getCSRCount();
        for (UINT laneIndex = 0; laneIndex < HILINK_INFO[MacroID].Lane_Num; laneIndex++) {
            SRAM.DSAPIRegs.MacroID(MacroID).SliceID(laneIndex).Broadcast(0);
            for (UINT csrIndex = 0; csrIndex < csr_num; csrIndex++) {
                SRAM.DSAPIRegs.Write2DUT(csrIndex, 0);
            }
        }
    }
}


//Clockslice Calibration
//====================================================================================
// Function: CsFwCalibration
// - This function used to calibration SS/CS by using FW.
// - Please refer to the API register doc to get API detail description.
// - The return value can be 0/1, 0 means calibration failed, 1 means calibration success.
//====================================================================================

void CsFwCalibration(MACRO_LANE_SEL& MacroLane_Sel, CUSTPARA &CUSTpara, SSPARA &SSpara, CSPARA &CSpara, MACRO_INT &mCS_Cal_MacroResult, MACRO_INT &mCsCalVcoLockPerMacro, const string full_cal_en, const bool ss_cal_only_en) {
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    // ***************  User Define Begin ********************

    //added user setting variable

    uint iRefclk0_freqm100 = uint(SSpara.RefclkMHz * 100);
    uint iRefclk1_freqm100 = uint(SSpara.RefclkMHz2 * 100);
    ; // refclk1 have a 25MHz offset with refclk0
    int iCore_clk_selext_pin_api = giCore_clk_selext_pin_api;
    int iCore_clk_sel_pin_api = giCore_clk_sel_pin_api;
    int iLifeclk2dig_sel_pin_api = giLifeclk2dig_sel_pin_api;
    int iCoreclk_sel_en_api;
    if (CUSTpara.Coreclk_sel == "disable")iCoreclk_sel_en_api = 0;
    else iCoreclk_sel_en_api = giCoreclk_sel_en_api;
    CSAPI CSAPI_SET;


    if (ss_cal_only_en == true) //SS
    {
        if (full_cal_en == FullCalPara.FullCal or full_cal_en == FullCalPara.FullCal_FWABIST_USE or full_cal_en == FullCalPara.REFLOCKRANGE_USE) {
            CSAPI_SET = default_CSAPI[1]; //CASE2
        } else if (full_cal_en == FullCalPara.BypassCal) {
            CSAPI_SET = default_CSAPI[6]; //CASE7
        } else {
            //			cout << "Can't find valid Full_cal_en parameter !!! Please check Full_cal_en parameter!" << endl;
            printf("Can't find valid Full_cal_en parameter !!! Please check Full_cal_en parameter!\n");
        }
    } else {
        if (full_cal_en == FullCalPara.FullCal or full_cal_en == FullCalPara.FullCal_FWABIST_USE or full_cal_en == FullCalPara.REFLOCKRANGE_USE) {

            if (CUSTpara.PllSel != -1) {
                hout(GENERAL) << "ERROR:Pll Sel must be '-1' when doing full cal!!!" << endl;
            }
            CSAPI_SET = default_CSAPI[2]; //CASE3
        } else if (full_cal_en == FullCalPara.BypassCal) {

            if ((CUSTpara.PllSel != 0) && (CUSTpara.PllSel != 1) && (CUSTpara.PllSel != -1)) {
                hout(GENERAL) << "ERROR:Pll Sel is Out of Range or Empty" << endl;
            }

            if (CUSTpara.PllSel == 0)
                CSAPI_SET = default_CSAPI[3]; //CASE4
            if (CUSTpara.PllSel == 1)
                CSAPI_SET = default_CSAPI[4]; //CASE5
            if (CUSTpara.PllSel == -1)
                CSAPI_SET = default_CSAPI[5]; //CASE6
        } else {
            //			cout << "Can't find valid Full_cal_en parameter !!! Please check Full_cal_en parameter!" << endl;
            printf("Can't find valid Full_cal_en parameter !!! Please check Full_cal_en parameter!\n");
        }
    }


    d2s::d2s_LABEL_BEGIN("Configure_CS_Cal_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    SRAM.CPAPIRegs.SliceID(0).Broadcast(1);
    SRAM.CSAPIRegs.SliceID(0).Broadcast(1);
    //Step1: hold MCU in reset mode
    //SRAM.CPAPIRegs.setmcurstb(0x0).setcsmasterifmode(0x2).setmcupwrdb(0x1).Write2DUT(8);
    SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8);
    // Step2: load binary file to 32k byte size SRAM
    // If SRAM have been loaded, this step can bypass
    // Run pattern

    //Configure refclk frequency, users can get the information at frequency plan
    SRAM.CSAPIRegs.setrefclk0_freqm100_api(iRefclk0_freqm100).Write2DUT(1);
    SRAM.CSAPIRegs.setrefclk1_freqm100_api(iRefclk1_freqm100).Write2DUT(2);

    //Configure core_clk select
    SRAM.CSAPIRegs.setcore_clk_selext_pin_api(iCore_clk_selext_pin_api).Write2DUT(0);
    SRAM.CSAPIRegs.setcore_clk_sel_pin_api(iCore_clk_sel_pin_api).Write2DUT(0);

    SRAM.CSAPIRegs.setcoreclk_sel_en_api(iCoreclk_sel_en_api).Write2DUT(4);

    //GB setup
    /***************/
    //only CS
    if (ss_cal_only_en == false) {
        SRAM.CSAPIRegs.setpll0dlfvreg_ofst_api(0x4)
                .setpll0pllvreg_ofst_api(0x4)
                .setpll0vcodivvreg_ofst_api(0x4)
                .setpll0itankvreg_ofst_api(0x0).Write2DUT(5);
        SRAM.CSAPIRegs.setpll1dlfvreg_ofst_api(0x4)
                .setpll1pllvreg_ofst_api(0x4)
                .setpll1vcodivvreg_ofst_api(0x4)
                .setpll1itankvreg_ofst_api(0x0).Write2DUT(6);
        if (CUSTpara.GB_Enable == 1)
            SRAM.CSAPIRegs.setregulator_offset_en_api(0x1).Write2DUT(7);
        else
            SRAM.CSAPIRegs.setregulator_offset_en_api(0x0).Write2DUT(7);
    }

    //calibration bypass control.  0:not bypass   1:bypass
    CsCalibrationBypassConfig(CSAPI_SET);

    //enable CS calibration
    SRAM.CSAPIRegs.setcs_calib_en_api(0x1).Write2DUT(0);

    if (full_cal_en == FullCalPara.BypassCal or full_cal_en == FullCalPara.REFLOCKRANGE_USE) {
        SRAM.CSAPIRegs.setcs_write_back_ctrl_api(0x1).Write2DUT(0); //bypass cal
    } else if (full_cal_en == FullCalPara.FullCal or full_cal_en == FullCalPara.FullCal_FWABIST_USE) {
        SRAM.CSAPIRegs.setcs_write_back_ctrl_api(0x0).Write2DUT(0); //full cal
    } else {
        //                cout << "Can't find valid Full_cal_en parameter !!! Please check Full_cal_en parameter!" << endl;
        printf("Can't find valid Full_cal_en parameter !!! Please check Full_cal_en parameter!\n");
    }
    //        d2s::d2s_LABEL_END();
    //
    //        d2s::d2s_LABEL_BEGIN("Configure_CS_Cal2_", Global_D2S_Mode);
    if(PrintDebugEn) cout<<"GlobalInitPattern = " <<GlobalInitPattern<<endl;
    for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        selectMacro(MacroID); //FW cal 2nd shantui 20210826 , 1st not shantui
        SRAM.CSAPIRegs.MacroID(MacroID).SliceID(0).Broadcast(0);
        if (GlobalInitPattern.find("_Case01") != string::npos)
            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[0];
        else if (GlobalInitPattern.find("_Case02") != string::npos)
            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[1]; //2nd shantui at MacroID =1 20210826  , 1st not shantui
        else if (GlobalInitPattern.find("_Case03") != string::npos)
            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[2];
        else {
            //                        cout << "Can't find valid init pattern !!! Please check pattern name!" << endl;
            printf("Can't find valid init pattern !!! Please check pattern name!\n");
        }
        if (iLifeclk2dig_sel_pin_api != 1 && iLifeclk2dig_sel_pin_api != 0 && iLifeclk2dig_sel_pin_api != -1) {
            //                        cout << "Invalid macro has been choose !!! Please check macro ID!" << endl;
            printf("Invalid macro has been choose !!! Please check macro ID!\n");
        }
        SRAM.CSAPIRegs.setlifeclk2dig_sel_pin_api(iLifeclk2dig_sel_pin_api).Write2DUT(0, false);
    }
    selectMacro_MB(MacroLane_Sel);
    SRAM.CPAPIRegs.SliceID(0).Broadcast(1);
    SRAM.CPAPIRegs.setmcurstb(0x1).Write2DUT(8);
    d2s::d2s_LABEL_END();

    //Step5: monitor TOP_FSM_DONE until calibration finished
    //Wait for calibration to complete by checking status of TOP_FSM_DONE
    INT iCheckCount = 0;
    INT iMaxTimeout = 200;
    if(PrintDebugEn) cout<<"doing CsFwCalibration, iMaxTimeout = "<<dec<<iMaxTimeout<<endl;
    INT WAITDONERESULT = 1;
    EXPECT_RESULT Top_Fsm_Result;
    do {
        iCheckCount++;
        hout(DETAIL) << "count " << iCheckCount << endl;
//        api->sleep(0.01);
        TheInst.Wait(0.002);
        Check_Top_Fsm_Done(MacroLane_Sel, Top_Fsm_Result); //for get each macro result 20170613 hi7100 review

    } while (Top_Fsm_Result.allpass != true && iCheckCount < iMaxTimeout);
    if(PrintDebugEn) cout<<"doing CsFwCalibration, final iCheckCount = "<<dec<<iCheckCount<<endl;

    for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int SiteID = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
            mCS_Cal_MacroResult[SiteID][MacroID] = Top_Fsm_Result.eachsite[SiteID];
            if (mCS_Cal_MacroResult[SiteID][MacroID] == 0) {
                WAITDONERESULT = 0;
            }
            hout(GENERAL) << "Site" << SiteID << "TopApi =" << Top_Fsm_Result.eachsite[SiteID] << endl;
            if(PrintDebugEn) cout<< "Site" << SiteID << "TopApi =" << Top_Fsm_Result.eachsite[SiteID] << endl;
            if(PrintDebugEn) printf("mCS_Cal_MacroResult[%d][%d]= %d\n", SiteID, MacroID, mCS_Cal_MacroResult[SiteID][MacroID]);

            if (iCheckCount >= iMaxTimeout) {
                if (ss_cal_only_en == true)
                {    hout(GENERAL) << "Site" << SiteID << " SS calibration TimeOut !!!!!!!!!" << endl;
                if(PrintDebugEn) printf("Site %d  SS calibration TimeOut !!!!!!!!!\n",SiteID);
                }
                else
                {
                    hout(GENERAL) << "Site" << SiteID << " CS calibration TimeOut !!!!!!!!!" << endl;
                    if(PrintDebugEn) printf("Site %d  CS calibration TimeOut !!!!!!!!!\n",SiteID);
                }
            } else {
                if (ss_cal_only_en)
                {
                    hout(GENERAL) << "Site" << SiteID << " SS calibration Done !!!!!!!!!" << endl;
                    if(PrintDebugEn) printf("Site %d  SS calibration Done !!!!!!!!!\n",SiteID);
                }
                else
                {
                    hout(DETAIL) << "Site" << SiteID << " CS calibration Done !!!!!!!!!" << endl;
                    if(PrintDebugEn)  printf("Site %d  CS calibration Done !!!!!!!!!\n",SiteID);
                }
            }
            FOREACH_ACTIVESITE_END

    }

    iMaxTimeout = 1;
    if ((WAITDONERESULT == 0) || (Global_D2S_Mode == 0)) { //learning mode  or wait for done result enter this loop, by using read pattern to get the TOP_API result
        for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            iCheckCount = 0;
            do {
                iCheckCount++;
                if(PrintDebugEn) cout<<"doing WAITDONERESULT=0 or learning mode CsFwCalibration, now iCheckCount = "<<dec<<iCheckCount<<endl;
                hout(DETAIL) << "count " << iCheckCount << endl;
                Check_Top_Fsm_Done(MacroID, Top_Fsm_Result); //for get each macro result 20170613 hi7100 review
            } while (Top_Fsm_Result.allpass != true && iCheckCount < iMaxTimeout); //Ares

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
                FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
                mCS_Cal_MacroResult[SiteID][MacroID] = Top_Fsm_Result.eachsite[SiteID];
                hout(GENERAL) << "Site" << SiteID << "TopApi" << Top_Fsm_Result.eachsite[SiteID] << endl;
                if(PrintDebugEn) printf("mCS_Cal_MacroResult[%d][%d]= %d\n", SiteID, MacroID, mCS_Cal_MacroResult[SiteID][MacroID]);

                if (iCheckCount >= iMaxTimeout) {
                    if (ss_cal_only_en == true)
                        hout(GENERAL) << "Site" << SiteID << " SS calibration TimeOut !!!!!!!!!" << endl;
                    else
                        hout(GENERAL) << "Site" << SiteID << " CS calibration TimeOut !!!!!!!!!" << endl;
                } else {
                    if (ss_cal_only_en)
                        hout(GENERAL) << "Site" << SiteID << " SS calibration Done on MACRO" << MacroID << " !!!!!!!!!" << endl;
                    else
                        hout(DETAIL) << "Site" << SiteID << " CS calibration Done on MACRO" << MacroID << " !!!!!!!!!" << endl;
                }
                FOREACH_ACTIVESITE_END
        }
    }

    if (ss_cal_only_en == false) {
        char IDstring0[128] = "";
        char IDstring1[128] = "";
        int expectfail = 0;

        EXPECT_RESULT Check_VCO_Result;

//        unsigned int sites[MAX_SITES];
        int ConfiguredSitesNum = TheSoft.Sites().Existing().GetExistedSiteCount();//   MAX_SITES;//api->Get_active_sites(sites);
        ARRAY_I tmp;
        tmp.resize(ConfiguredSitesNum);
        //tmp.init(0);
        Check_VCO_Result.allpass = true;
        Check_VCO_Result.allfail = true;
        Check_VCO_Result.eachsite = tmp;


//        Global_D2S_Mode =    ProductionMode;//LearningMode      
        
        d2s::d2s_LABEL_BEGIN("CheckVCOLockStatus_Pll_func", Global_D2S_Mode);
        jtag.enablePassFailCheckForNextExecution();
        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            selectMacro(MacroID);
            CS.clkRegs.MacroID(MacroID).MacroID(MacroID).SliceID(0).Broadcast(0);
            if (CUSTpara.PllSel == 0) {
                //				CS.clkRegs.ExpectValue(2,0x12C,0xf000);
                CS.clkRegs.ExpectValue(2, 0x12C, 0x000f);
            } else if (CUSTpara.PllSel == 1) {
                //				CS.clkRegs.ExpectValue(5,0x12C,0xf000);
                CS.clkRegs.ExpectValue(5, 0x12C, 0x000f);
            } else if (CUSTpara.PllSel == -1) {
                //				CS.clkRegs.ExpectValue(2,0x12C,0xf000);
                CS.clkRegs.ExpectValue(2, 0x12C, 0x000f);
                //				CS.clkRegs.ExpectValue(5,0x12C,0xf000);
                CS.clkRegs.ExpectValue(5, 0x12C, 0x000f);
            }
        }
        d2s::d2s_LABEL_END();
        
        map<uint32_t, bool> map_pass_fail_result = TheInst.Digital().PatEng().GetPassFail();
//	 	for(auto it = map_pass_fail_result.begin(); it != map_pass_fail_result.end(); it++)
//		{
//	 		if(PrintDebugEn) cout<<"CheckVCOLockStatus_Pll_func passfail :"<< it->second<<endl;
//		}

//        FOREACH_ACTIVE_SITE(api) {
        	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
            bool size_pass = map_pass_fail_result[SiteID];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
        	if(PrintDebugEn) cout<<"map_pass_fail_result["<<SiteID<<"] = "<<map_pass_fail_result[SiteID]<<endl;

            Check_VCO_Result.allpass = (Check_VCO_Result.allpass && size_pass);
            Check_VCO_Result.allfail = (Check_VCO_Result.allfail && !size_pass);
            Check_VCO_Result.eachsite[SiteID] = size_pass;
            FOREACH_ACTIVESITE_END

//        FOREACH_ACTIVE_SITE(api) {
            	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//                int SiteID = api->Get_active_site();
                if (Check_VCO_Result.eachsite[SiteID] == 1) {
                    mCsCalVcoLockPerMacro[SiteID][MacroID] = 1;
                } else {
                    mCsCalVcoLockPerMacro[SiteID][MacroID] = 0;
                    expectfail = 1;
                }
               // printf("****************  mCsCalVcoLockPerMacro[%d][%d]= %d", SiteID, MacroID, mCsCalVcoLockPerMacro[SiteID][MacroID]);
            }
            	FOREACH_ACTIVESITE_END
        
        if ((expectfail == 1) || (Global_D2S_Mode == 0)) { //learning mode or expect result is fail, enter this loop for reading then show tail infomation for each macro
            d2s::d2s_LABEL_BEGIN("CheckVCOLockStatus_Pll", Global_D2S_Mode);
            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
                selectMacro(MacroID);
                CS.clkRegs.MacroID(MacroID).SliceID(0).Broadcast(0);

                if (CUSTpara.PllSel == 0) {
                    sprintf(IDstring0, "Pll%d_VCOLOCK_Status_onMacro%i", 0, MacroID);
                    CS.clkRegs.Read2IDString(2, IDstring0);
                } else if (CUSTpara.PllSel == 1) {
                    sprintf(IDstring1, "Pll%d_VCOLOCK_Status_onMacro%i", 1, MacroID);
                    CS.clkRegs.Read2IDString(5, IDstring1);
                } else if (CUSTpara.PllSel == -1) {
                    sprintf(IDstring0, "Pll%d_VCOLOCK_Status_onMacro%i", 0, MacroID);
                    CS.clkRegs.Read2IDString(2, IDstring0);
                    sprintf(IDstring1, "Pll%d_VCOLOCK_Status_onMacro%i", 1, MacroID);
                    CS.clkRegs.Read2IDString(5, IDstring1);
                    ;
                }
            }
            d2s::d2s_LABEL_END();

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)  // production shantui at here 20210826  chen bo debuging .... wait result
                for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                    UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

                    if (CUSTpara.PllSel == 0) {
                        sprintf(IDstring0, "Pll%d_VCOLOCK_Status_onMacro%i", 0, MacroID);
                        long long  result0  = jtag.getReadValue(IDstring0)[SiteID];
                        printf("========== Pll0_VCOLOCK_Status_onMacro result  = %d\n",result0);
                        if (jtag.getReadValue(IDstring0)[SiteID] == 0x12C)//0x12C   //modify by tony 20210607
                        {
                            hout(DETAIL) << "Site" << SiteID << " : Macro" << dec << MacroID << " VCOLOCK on pll0 !!!" << endl;
                            if(PrintDebugEn) cout<< "Site" << SiteID << " : Macro" << dec << MacroID << " VCOLOCK on pll0 !!!" << endl;
                            mCsCalVcoLockPerMacro[SiteID][MacroID] = 1;
                        } else {
                            hout(DETAIL) << "jtag.getReadValue(IDstring0): " << hex << IDstring0 << " " << jtag.getReadValue(IDstring0)[SiteID] << endl;
                            hout(DETAIL) << "Site" << SiteID << " : Macro" << dec << MacroID << " VCO UNLOCK on pll0 !!!" << endl;
                            if(PrintDebugEn) cout<< "jtag.getReadValue(IDstring0): " << hex << IDstring0 << " " << jtag.getReadValue(IDstring0)[SiteID] << endl;
                            if(PrintDebugEn) cout<< "Site" << SiteID << " : Macro" << dec << MacroID << " VCO UNLOCK on pll0 !!!" << endl;
                            mCsCalVcoLockPerMacro[SiteID][MacroID] = 0;
                        }
                    } else if (CUSTpara.PllSel == 1) {
                        sprintf(IDstring1, "Pll%d_VCOLOCK_Status_onMacro%i", 1, MacroID);
                        if (jtag.getReadValue(IDstring1)[SiteID] == 0x12C)//0x12C
                        {
                            hout(DETAIL) << "Site" << SiteID << " : Macro" << dec << MacroID << " VCOLOCK on pll1 !!!" << endl;
                            if(PrintDebugEn) cout<< "Site" << SiteID << " : Macro" << dec << MacroID << " VCOLOCK on pll1 !!!" << endl;
                            mCsCalVcoLockPerMacro[SiteID][MacroID] = 1;
                        } else {
                            hout(DETAIL) << "jtag.getReadValue(IDstring1): " << hex << IDstring1 << " " << jtag.getReadValue(IDstring1)[SiteID] << endl;
                            hout(DETAIL) << "Site" << SiteID << " : Macro" << dec << MacroID << " VCO UNLOCK on pll1 !!!" << endl;
                            if(PrintDebugEn) cout<< "jtag.getReadValue(IDstring1): " << hex << IDstring1 << " " << jtag.getReadValue(IDstring1)[SiteID] << endl;
                            if(PrintDebugEn) cout<< "Site" << SiteID << " : Macro" << dec << MacroID << " VCO UNLOCK on pll1 !!!" << endl;
                            mCsCalVcoLockPerMacro[SiteID][MacroID] = 0;
                        }
                    } else if (CUSTpara.PllSel == -1) {
                        sprintf(IDstring0, "Pll%d_VCOLOCK_Status_onMacro%i", 0, MacroID);
                        sprintf(IDstring1, "Pll%d_VCOLOCK_Status_onMacro%i", 1, MacroID);
                        long long  result0  = jtag.getReadValue(IDstring0)[SiteID];
                        long long  result1  = jtag.getReadValue(IDstring1)[SiteID];
                        if ( 0 == Global_D2S_Mode) {
                            printf("========== Pll0_VCOLOCK_Status_onMacro result  = %d\n",result0);
                            printf("========== Pll1_VCOLOCK_Status_onMacro result  = %d\n",result1);
                        }
                        if (jtag.getReadValue(IDstring0)[SiteID] == 0x12C && jtag.getReadValue(IDstring1)[SiteID] == 0x12C)//0x12C
                        {
                            hout(DETAIL) << "Site" << SiteID << " : Macro" << dec << MacroID << " VCOLOCK on pll0 !!!" << endl;
                            hout(DETAIL) << "Site" << SiteID << " : Macro" << dec << MacroID << " VCOLOCK on pll1 !!!" << endl;
                            mCsCalVcoLockPerMacro[SiteID][MacroID] = 1;
                        } else if (jtag.getReadValue(IDstring0)[SiteID] == 0x12C && jtag.getReadValue(IDstring1)[SiteID] != 0x12C) {
                            mCsCalVcoLockPerMacro[SiteID][MacroID] = 2; //PLL0 lock
                            hout(DETAIL) << "Site" << SiteID << " : Macro" << dec << MacroID << " VCOLOCK on pll0 !!!" << endl;
                            hout(DETAIL) << "Site" << SiteID << " : Macro" << dec << MacroID << " VCOUNLOCK on pll1 !!!" << endl;
                        } else if (jtag.getReadValue(IDstring0)[SiteID] != 0x12C && jtag.getReadValue(IDstring1)[SiteID] == 0x12C) {
                            mCsCalVcoLockPerMacro[SiteID][MacroID] = 3; //PLL1 lock
                            hout(DETAIL) << "Site" << SiteID << " : Macro" << dec << MacroID << " VCOLOCK on pll1 !!!" << endl;
                            hout(DETAIL) << "Site" << SiteID << " : Macro" << dec << MacroID << " VCOUNLOCK on pll0 !!!" << endl;
                        } else { //add by tony 20210607
                            mCsCalVcoLockPerMacro[SiteID][MacroID] = 0; //PLL1 lock
                            hout(DETAIL) << "Site" << SiteID << " : Macro" << dec << MacroID << " VCOUNLOCK on pll1 !!!" << endl;
                            hout(DETAIL) << "Site" << SiteID << " : Macro" << dec << MacroID << " VCOUNLOCK on pll0 !!!" << endl;
                        }
                        
                    }
                }
                FOREACH_ACTIVESITE_END
        }
    }
    if ( 0 == Global_D2S_Mode) { //if  Global_D2S_Mode as learning mode ,print the result
//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int SiteID = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

                printf("=============  mCsCalVcoLockPerMacro[%d][%d]= %d\n", SiteID, MacroID, mCsCalVcoLockPerMacro[SiteID][MacroID]);
            }
            FOREACH_ACTIVESITE_END
    }
    

//    ALL_CSR_ReadBack_TO_FILE_Debug(MacroLane_Sel,"After_CsFwCalibration");


    d2s::d2s_LABEL_BEGIN("CsFwCalibration_Disable_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8);
    Clear_CS_API();
    Clear_DS_API(MacroLane_Sel);
    d2s::d2s_LABEL_END();
}

void Check_Top_Fsm_Done(INT MacroID, EXPECT_RESULT &result) {
    d2s_JTAG& jtag = d2s_JTAG::Instance();
//    unsigned int sites[MAX_SITES];
    INT ConfiguredSitesNum = TheSoft.Sites().Existing().GetExistedSiteCount();// api->Get_active_sites(sites);
    ARRAY_I tmp;
    tmp.resize(ConfiguredSitesNum);
    //	tmp.init(0);
    result.allpass = true;
    result.allfail = true;
    result.eachsite = tmp;

    d2s::d2s_LABEL_BEGIN("MPB_Check_Top_Fsm_Done2_", Global_D2S_Mode);
    jtag.enablePassFailCheckForNextExecution();
    selectMacro(MacroID);
    //		SRAM.TOPAPIRegs.ExpectValue(0,0x8804,0xfff0);//Compare 0b0010 on TOP_FSM_API[3:0]
    SRAM.TOPAPIRegs.ExpectValue(0, 0x8804, 0x000f); //Compare 0b0010 on TOP_FSM_API[3:0]

    d2s::d2s_LABEL_END();

    map<uint32_t, bool> map_pass_fail_result = TheInst.Digital().PatEng().GetPassFail();
// 	for(auto it = map_pass_fail_result.begin(); it != map_pass_fail_result.end(); it++)
//	{
// 		if(PrintDebugEn) cout<<"siteID "<<it->first <<" passfail :"<< it->second<<endl;
//	}
//    FOREACH_ACTIVE_SITE(api) {
    	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
        bool size_pass = map_pass_fail_result[SiteID];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
    	if(PrintDebugEn) cout<<"map_pass_fail_result["<<SiteID<<"] = "<<map_pass_fail_result[SiteID]<<endl;
        result.allpass = (result.allpass && size_pass);
        result.allfail = (result.allfail && !size_pass);
        result.eachsite[SiteID] = size_pass;
        FOREACH_ACTIVESITE_END
    return;
}

void Check_Top_Fsm_Done(MACRO_LANE_SEL& MacroLane_Sel, EXPECT_RESULT &result) {
    //	D2S_FRAMEWORK;

    //    //GET_TEST_INFO;
    d2s_JTAG& jtag = d2s_JTAG::Instance();
//    unsigned int sites[MAX_SITES];
    INT ConfiguredSitesNum = TheSoft.Sites().Existing().GetExistedSiteCount();// api->Get_active_sites(sites);
    ARRAY_I tmp;
    tmp.resize(ConfiguredSitesNum);
    //	tmp.init(0);
    result.allpass = true;
    result.allfail = true;
    result.eachsite = tmp;

    //    sprintf(label,"MPB_Check_Top_Fsm_Done");
    d2s::d2s_LABEL_BEGIN("MPB_Check_Top_Fsm_Done", Global_D2S_Mode);
    //fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    jtag.enablePassFailCheckForNextExecution();
    for (UINT iMacroIndex = 0; iMacroIndex < MacroLane_Sel.size(); iMacroIndex++) {
        UINT MacroID = MacroLane_Sel[iMacroIndex].MacroID;
        selectMacro(MacroID);
        SRAM.TOPAPIRegs.MacroID(MacroID);
        //                         SRAM.TOPAPIRegs.ExpectValue(0,0x8804,0xfff0);//Compare 0b0010 on TOP_FSM_API[3:0]
        SRAM.TOPAPIRegs.ExpectValue(0, 0x8804, 0x000f); //Compare 0b0010 on TOP_FSM_API[3:0]

    }
    //fr.d2s_LABEL_END(); 
    d2s::d2s_LABEL_END();

    //	jtag.hasPassed(label,result.allpass,result.allfail,result.eachsite);

    map<uint32_t, bool> map_pass_fail_result = TheInst.Digital().PatEng().GetPassFail();
// 	for(auto it = map_pass_fail_result.begin(); it != map_pass_fail_result.end(); it++)
//	{
// 		if(PrintDebugEn) cout<<"siteID "<<it->first <<" passfail :"<< it->second<<endl;
//	}

//    FOREACH_ACTIVE_SITE(api) {
    	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
        bool size_pass = map_pass_fail_result[SiteID];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
		if(PrintDebugEn) cout<<"map_pass_fail_result["<<SiteID<<"] = "<<map_pass_fail_result[SiteID]<<endl;
        result.allpass = (result.allpass && size_pass);
        result.allfail = (result.allfail && !size_pass);
        result.eachsite[SiteID] = size_pass;
        FOREACH_ACTIVESITE_END


//// for debug by read back the top_api result .......................................................... print topapi begining..........................................//
	if ( 0 == Global_D2S_Mode) {

				MACRO_DOUBLE dTop_fsm_api;
		//        d2s_JTAG& jtag = d2s_JTAG::Instance();
				d2s::d2s_LABEL_BEGIN("Read_Top_Fsm_Api", Global_D2S_Mode);

				 for (UINT iMacroIndex = 0; iMacroIndex < MacroLane_Sel.size(); iMacroIndex ++)
				 {
						 UINT MacroID = MacroLane_Sel[iMacroIndex].MacroID;
						 selectMacro(MacroID);
						 SRAM.TOPAPIRegs.MacroID(MacroID);

						 char IDstring[128] = "";
						 sprintf (IDstring,"sramtopapi_csr0_onMacro%i",MacroID);
					   SRAM.TOPAPIRegs.Read2IDString(0,IDstring);
		//                 jtag.read(0x1fffe>>1,IDstring);

				}
				d2s::d2s_LABEL_END();

				MACRO_DOUBLE top_fsm_api;
	//            FOREACH_ACTIVE_SITE(api) {
	//               unsigned int SiteID = api->Get_active_site();
				   FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				   for (UINT iMacroIndex = 0; iMacroIndex < MacroLane_Sel.size(); iMacroIndex ++)
				   {
						   UINT MacroID = MacroLane_Sel[iMacroIndex].MacroID;
						   char IDstring[128] = "";
						   sprintf (IDstring, "sramtopapi_csr0_onMacro%i",MacroID);

						   uint val = (UINT)jtag.getReadValue(IDstring)[SiteID];//modify by tony 20210827  "+1"
						   top_fsm_api[SiteID][MacroID]=HILINK_Regs_Base::get_bits(val,SRAM.TOPAPIRegs.REG_INFO.top_fsm_api());
						   if(PrintDebugEn) printf("top_fsm_api[%d][%d]= %f\n",SiteID,MacroID,top_fsm_api[SiteID][MacroID]);
//						   printf("val= %u\n",val);

				   }
				   FOREACH_ACTIVESITE_END


		}
//.......................................................... print topapi end..........................................//


    //	if(1)//Add for debug if too much macro fail
    //	{
    //		FOR_EACH_SITE_BEGIN();
    //		INT SiteID = CURRENT_SITE_NUMBER() - 1;
    //		for (UINT iMacroIndex = 0; iMacroIndex < MacroLane_Sel.size(); iMacroIndex ++)
    //		{
    //		  UINT MacroID = MacroLane_Sel[iMacroIndex].MacroID;
    //		  selectMacro_Now(MacroID);
    //		  SRAM.TOPAPIRegs.MacroID(MacroID);
    //		  hout(DETAIL)<<"SITE:"<<SiteID<<"\tMacro:"<<MacroID<<"\t TOPAPI"<<"\t CSR0:"<<hex<<SRAM.TOPAPIRegs.Read2CSR(0)<<endl;
    //
    //		}
    //		FOR_EACH_SITE_END();
    //	}

    return;
}//Ares Add


//Clockslice Configuration after Calibration

void CSConfigurationAfterCalibration(MACRO_LANE_SEL& MacroLane_Sel) {
    //For future extension
    return;
}


//Dataslice Configuration before Calibration
//====================================================================================
// Function: DsConfigurationBeforeCalibration
// - This function is for DS general settings before calibration, include
//   DS power up sequence and data rate configurations.
//====================================================================================

void DsConfigurationBeforeCalibration(MACRO_LANE_SEL& vMacroLane_Sel, CSPARA& CSpara, SSPARA& SSpara, CUSTPARA& CUSTpara, const string full_cal_en) {
    int rxbitorder = 0x0;
    int rxpolarity = 0x0;
    int rxtermfloating = 0x0; //AC couple mode : 0, other : 1
    int ctlerefsel = 0x3;
    int txbitorder = 0x0;
    int txpolarity = 0x0;
    int txclksel = 0x2;
    int txalignmode = 0x3;

//    int ctleactgn1 = 0x3;
//    int ctleactgn2 = 0x3;
//    int ctleactgn3 = 0x4;
	int ctleactgn1;
	int ctleactgn2;
	int ctleactgn3;

if (CP_FT_Program == "FT"){
    ctleactgn1 = 0x4;
    ctleactgn2 = 0x4;
    ctleactgn3 = 0x4;
}else{
    ctleactgn1 = 0x7;
    ctleactgn2 = 0x7;
    ctleactgn3 = 0x4;
}


    int ctleboostc1 = 0x7;
    int ctleboostc2 = 0x1;
    int ctleboostc3 = 0x0;

    int ctleza1;
    int ctleza2;
    int ctleza3;

    double H30DataRate = CSpara.HSCLK * 2;
    if (H30DataRate <= 32 and H30DataRate > 25) {
        ctleza1 = 0x5;
        ctleza2 = 0x1;
        ctleza3 = 0x0;
    } else if (H30DataRate <= 25 and H30DataRate > 20) {
        ctleza1 = 0x5;
        ctleza2 = 0x2;
        ctleza3 = 0x0;
    } else if (H30DataRate <= 20 and H30DataRate > 15) {
        ctleza1 = 0x5;
        ctleza2 = 0x5;
        ctleza3 = 0x2;
    } else if (H30DataRate <= 15 and H30DataRate > 1) {
        ctleza1 = 0x5;
        ctleza2 = 0x5;
        ctleza3 = 0x5;
    }

	int ctlesqh1;
	int ctlesqh2;
	int ctlesqh3;
    if (CP_FT_Program == "FT"){
		ctlesqh1 = 0x2;
		ctlesqh2 = 0x2;
		ctlesqh3 = 0x2;
    }else{
		ctlesqh1 = 0x2;
		ctlesqh2 = 0x2;
		ctlesqh3 = 0x0;
    }

    int ctlermband1 = 0x2;
    int ctlermband2 = 0x1;
    int ctlermband3 = 0x1;

    int ctlecmband1 = 0x2;
    int ctlecmband2 = 0x1;
    int ctlecmband3 = 0x1;

    int ctlehfzen1 = 0x0;
    int ctlehfzen2 = 0x0;
    int ctlehfzen3 = 0x0;

    int rxctleibiastune = 0x6;

#if 0
    int dfefxtap2 = 0x0;
    int dfefxtap3 = 0x0;
    int dfefxtap4 = 0x0;
    int dfefxtap5 = 0x0;
    int dfefxtap6 = 0x0;
    int dfefxtap7 = 0x0;
    int dfefxtap8 = 0x0;
    int dfefxtap9 = 0x0;
    int dfemvtap1 = 0x0;
    int dfemvtap2 = 0x0;
    int dfemvtap3 = 0x0;
    int dfemvtap4 = 0x0;
    int dfemvtap5 = 0x0;
    int dfemvtap6 = 0x0;
#endif

    CUSTpara.TxFIR_USER.iTxMain = 57;
    CUSTpara.TxFIR_USER.iTxPost1st = 0;
    CUSTpara.TxFIR_USER.iTxPost2nd = 0;
    CUSTpara.TxFIR_USER.iTxPre1st = -6;
    CUSTpara.TxFIR_USER.iTxPre2nd = 0;

    // Step1: DSCLK configuration.

    /**************Clear API and CSConfigBeforeCal***set proper API depending on applications and Release MCU*********/

    d2s::d2s_LABEL_BEGIN("DSBeforeCal_Set_", Global_D2S_Mode);
    selectMacro_MB(vMacroLane_Sel);
    DS.clkRegs.SliceID(0).Broadcast(1);
    DS.rxRegs.SliceID(0).Broadcast(1);
    DS.txRegs.SliceID(0).Broadcast(1);
    // Select spine clock source, 0: select clock spine0; 1: select clock spine1

    DS.clkRegs.setclkspinesel((CUSTpara.PllSel < 0 ? 0 : CUSTpara.PllSel)).Write2DUT(0); //Ares modify -1 can be write


    //RX configuration
    DS.rxRegs.setrxbitorder(rxbitorder).setrxpolarity(rxpolarity).setrxratemode(CUSTpara.RateMode).setrxdwidth(CUSTpara.DataWidth).Write2DUT(12);
    DS.rxRegs.setrxtermfloating(rxtermfloating).Write2DUT(32);

    //CTLE configuration
    //DS.rxRegs.setctlerefsel(ctlerefsel)
    //		.Write2DUT(44);
    if (full_cal_en == FullCalPara.BypassCal or full_cal_en == FullCalPara.FullCal or full_cal_en == FullCalPara.REFLOCKRANGE_USE) {
        DS.rxRegs.setctlehfzen1(ctlehfzen1).setctleboostc1(ctleboostc1)
                .setctlecmband1(ctlecmband1).setctlermband1(ctlermband1)
                .setctleza1(ctleza1).setctlesqh1(ctlesqh1).setctleactgn1(ctleactgn1)
                .Write2DUT(1);
        DS.rxRegs.setctlehfzen2(ctlehfzen2).setctleboostc2(ctleboostc2)
                .setctlecmband2(ctlecmband2).setctlermband2(ctlermband2)
                .setctleza2(ctleza2).setctlesqh2(ctlesqh2).setctleactgn2(ctleactgn2)
                .Write2DUT(2);
        DS.rxRegs.setctlehfzen3(ctlehfzen3).setctleboostc3(ctleboostc3)
                .setctlecmband3(ctlecmband3).setctlermband3(ctlermband3)
                .setctleza3(ctleza3).setctlesqh3(ctlesqh3).setctleactgn3(ctleactgn3)
                .Write2DUT(3);
        DS.rxRegs.setrxctleibiastune(rxctleibiastune)
                .Write2DUT(36);
    } else if (full_cal_en == FullCalPara.FullCal_FWABIST_USE) {
        ctleza1 = 0x0; //refer to fwdc guide v0.1.0
        ctleza2 = 0x0;
        ctleza3 = 0x0;

        DS.rxRegs.setctlehfzen1(ctlehfzen1)
                .setctlecmband1(ctlecmband1).setctlermband1(ctlermband1)
                .setctleza1(ctleza1).setctlesqh1(ctlesqh1)
                .Write2DUT(1);
        DS.rxRegs.setctlehfzen2(ctlehfzen2)
                .setctlecmband2(ctlecmband2).setctlermband2(ctlermband2)
                .setctleza2(ctleza2).setctlesqh2(ctlesqh2)
                .Write2DUT(2);
        DS.rxRegs.setctlehfzen3(ctlehfzen3)
                .setctlecmband3(ctlecmband3).setctlermband3(ctlermband3)
                .setctleza3(ctleza3).setctlesqh3(ctlesqh3)
                .Write2DUT(3);
    } else {
        //			cout << "Can't find valid Full_cal_en parameter !!! Please check Full_cal_en parameter!" << endl;
        printf("Can't find valid Full_cal_en parameter !!! Please check Full_cal_en parameter!\n");
    }

    //TX configuration
    DS.txRegs.settxbitorder(txbitorder).settxpolarity(txpolarity).settxratemode(CUSTpara.RateMode)
            .settxdwidth(CUSTpara.DataWidth).settxclksel(txclksel).settxalignmode(txalignmode).Write2DUT(2);

    //TX FIR parameter setting
    SetTxFir(CUSTpara);

#if 0
    DS.rxRegs.setdfefxtap2(dfefxtap2).Write2DUT(6);
    DS.rxRegs.setdfefxtap3(dfefxtap3).Write2DUT(7);
    DS.rxRegs.setdfefxtap4(dfefxtap4).Write2DUT(7);
    DS.rxRegs.setdfefxtap5(dfefxtap5).Write2DUT(8);
    DS.rxRegs.setdfefxtap6(dfefxtap6).Write2DUT(8);
    DS.rxRegs.setdfefxtap7(dfefxtap7).Write2DUT(8);
    DS.rxRegs.setdfefxtap8(dfefxtap8).Write2DUT(9);
    DS.rxRegs.setdfefxtap9(dfefxtap9).Write2DUT(9);
    DS.rxRegs.setdfemvtap1(dfemvtap1).Write2DUT(10);
    DS.rxRegs.setdfemvtap2(dfemvtap2).Write2DUT(10);
    DS.rxRegs.setdfemvtap3(dfemvtap3).Write2DUT(10);
    DS.rxRegs.setdfemvtap4(dfemvtap4).Write2DUT(11);
    DS.rxRegs.setdfemvtap5(dfemvtap5).Write2DUT(11);
    DS.rxRegs.setdfemvtap6(dfemvtap6).Write2DUT(11);
#endif

    /*************************SETCTLE_DFE END*************************/
    d2s::d2s_LABEL_END();
}
//====================================================================================
// Function: SetTxFir
// - firpre2: the pre-cursor 2 of the TX driver FIR, -15 to 15 is valid
// - firpre1: the pre-cursor 1 of the TX driver FIR, -15 to 15 is valid
// - firpost1: the post-cursor 1 of the TX driver FIR, -30 to 30 is valid
// - firmain: the main-cursor of the TX driver FIR, 0 to 63 is valid
//====================================================================================

void SetTxFir(MACRO_LANE_SEL& vMacroLane_Sel, CUSTPARA& CUSTpara) {
    d2s_JTAG& jtag = d2s_JTAG::Instance();
    int iTmpVal0, iTmpVal1, csrTxTapPwrdb;
    csrTxTapPwrdb = 0xF0;
    //D2S_FRAMEWORK;
    //GET_TEST_INFO;

    Antiproof_SumFIR(CUSTpara);

    //	sprintf(label,"SetTxFir_SetUp_%f_%f_",Vcoef,Temp);
    d2s::d2s_LABEL_BEGIN("SetTxFir_SetUp_", Global_D2S_Mode);
    //fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    selectMacro_MB(vMacroLane_Sel);
    DS.txRegs.SliceID(0).Broadcast(1);
    DS.txRegs.settxtermcalmode(0x2).Write2DUT(15);
    if (CUSTpara.TxFIR_USER.iTxPre2nd < 0) {
        iTmpVal0 = 0x10 - CUSTpara.TxFIR_USER.iTxPre2nd;
    } else {
        iTmpVal0 = CUSTpara.TxFIR_USER.iTxPre2nd;
    }
    DS.txRegs.settxfirpre2(iTmpVal0).Write2DUT(0);
    if (0x0 != iTmpVal0) {
        csrTxTapPwrdb = csrTxTapPwrdb | 0x2;
    }
    if (CUSTpara.TxFIR_USER.iTxPre1st < 0) {
        iTmpVal0 = 0x10 - CUSTpara.TxFIR_USER.iTxPre1st;
    } else {
        iTmpVal0 = CUSTpara.TxFIR_USER.iTxPre1st;
    }
    DS.txRegs.settxfirpre1(iTmpVal0).Write2DUT(0);
    if (0x0 != iTmpVal0) {
        csrTxTapPwrdb = csrTxTapPwrdb | 0x1;
    }

    if (CUSTpara.TxFIR_USER.iTxPost1st<-15) {
        iTmpVal0 = 0x1F;
        iTmpVal1 = (1 - CUSTpara.TxFIR_USER.iTxPost1st);
    } else if (CUSTpara.TxFIR_USER.iTxPost1st < 0) {
        iTmpVal0 = (0x10 - CUSTpara.TxFIR_USER.iTxPost1st);
        iTmpVal1 = 0;
    } else if (CUSTpara.TxFIR_USER.iTxPost1st < 15) {
        iTmpVal0 = CUSTpara.TxFIR_USER.iTxPost1st;
        iTmpVal1 = 0;
    } else {
        iTmpVal0 = 0xF;
        iTmpVal1 = CUSTpara.TxFIR_USER.iTxPost1st - 15;
    }

    DS.txRegs.settxfirpost1(iTmpVal0).settxfirpost1x(iTmpVal1).Write2DUT(1);
    if (0x0 != iTmpVal0) {
        csrTxTapPwrdb = csrTxTapPwrdb | 0x4;
    }
    if (0x0 != iTmpVal1) {
        csrTxTapPwrdb = csrTxTapPwrdb | 0x8;
    }
    DS.txRegs.settxtappwrdb(csrTxTapPwrdb).Write2DUT(11);

    DS.txRegs.settxfirmain(CUSTpara.TxFIR_USER.iTxMain).Write2DUT(1);
    DS.txRegs.settxdrvswctrl(0x0).Write2DUT(13);
    DS.txRegs.settxdrvswctrl(0x1).Write2DUT(13);
    jtag.wait(0.00005);
    //fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
}

void SetTxFir(CUSTPARA& CUSTpara) {
    Antiproof_SumFIR(CUSTpara);
    d2s_IP_JTAG & jtag = d2s_IP_JTAG::Instance();
    int iTmpVal0, iTmpVal1, csrTxTapPwrdb;
    csrTxTapPwrdb = 0xF0;

    DS.txRegs.SliceID(0).Broadcast(1);
    DS.txRegs.settxtermcalmode(0x2).Write2DUT(15);
    if (CUSTpara.TxFIR_USER.iTxPre2nd < 0) {
        iTmpVal0 = 0x10 - CUSTpara.TxFIR_USER.iTxPre2nd;
    } else {
        iTmpVal0 = CUSTpara.TxFIR_USER.iTxPre2nd;
    }
    DS.txRegs.settxfirpre2(iTmpVal0).Write2DUT(0);
    if (0x0 != iTmpVal0) {
        csrTxTapPwrdb = csrTxTapPwrdb | 0x2;
    }
    if (CUSTpara.TxFIR_USER.iTxPre1st < 0) {
        iTmpVal0 = 0x10 - CUSTpara.TxFIR_USER.iTxPre1st;
    } else {
        iTmpVal0 = CUSTpara.TxFIR_USER.iTxPre1st;
    }
    DS.txRegs.settxfirpre1(iTmpVal0).Write2DUT(0);
    if (0x0 != iTmpVal0) {
        csrTxTapPwrdb = csrTxTapPwrdb | 0x1;
    }

    if (CUSTpara.TxFIR_USER.iTxPost1st<-15) {
        iTmpVal0 = 0x1F;
        iTmpVal1 = (1 - CUSTpara.TxFIR_USER.iTxPost1st);
    } else if (CUSTpara.TxFIR_USER.iTxPost1st < 0) {
        iTmpVal0 = (0x10 - CUSTpara.TxFIR_USER.iTxPost1st);
        iTmpVal1 = 0;
    } else if (CUSTpara.TxFIR_USER.iTxPost1st < 15) {
        iTmpVal0 = CUSTpara.TxFIR_USER.iTxPost1st;
        iTmpVal1 = 0;
    } else {
        iTmpVal0 = 0xF;
        iTmpVal1 = CUSTpara.TxFIR_USER.iTxPost1st - 15;
    }

    DS.txRegs.settxfirpost1(iTmpVal0).settxfirpost1x(iTmpVal1).Write2DUT(1);
    if (0x0 != iTmpVal0) {
        csrTxTapPwrdb = csrTxTapPwrdb | 0x4;
    }
    if (0x0 != iTmpVal1) {
        csrTxTapPwrdb = csrTxTapPwrdb | 0x8;
    }
    DS.txRegs.settxtappwrdb(csrTxTapPwrdb).Write2DUT(11);
    DS.txRegs.settxfirmain(CUSTpara.TxFIR_USER.iTxMain).Write2DUT(1);
    DS.txRegs.settxdrvswctrl(0x0).Write2DUT(13);
    DS.txRegs.settxdrvswctrl(0x1).Write2DUT(13);
    jtag.wait(0.0001);
}


//Dataslice Calibration
//================================================================================
// Function: DsFwCalibration
// - This function used to calibration DS by using FW.
// - Please refer to the API register doc to get API detail description.
// - The return value can be 0/1, 0 means calibration failed, 1 means calibration success.
//================================================================================

void DsFwCalibration(MACRO_LANE_SEL& MacroLane_Sel, CUSTPARA &CUSTpara, SSPARA &SSpara, CSPARA &CSpara, MACRO_INT &mDS_Cal_MacroResult, const string full_cal_en) {
    // ***************  User Define Begin ********************
    int iCore_clk_selext_pin_api = giCore_clk_selext_pin_api;
    int iCore_clk_sel_pin_api = giCore_clk_sel_pin_api;
    int iLifeclk2dig_sel_pin_api = giLifeclk2dig_sel_pin_api;
    int iCoreclk_sel_en_api = giCoreclk_sel_en_api;
    INT iRefclk0_freqm100 = INT(SSpara.RefclkMHz * 100);
    INT iRefclk1_freqm100 = INT(SSpara.RefclkMHz2 * 100); // refclk1 have a 25MHz offset with refclk0
    DOUBLE dHsclk_GHz = CSpara.HSCLK;
    DSAPI DSAPI_SET;

    if (full_cal_en == FullCalPara.FullCal or full_cal_en == FullCalPara.FullCal_FWABIST_USE or full_cal_en == FullCalPara.REFLOCKRANGE_USE) {
        DSAPI_SET = default_DSAPI[0]; //CASE1
    } else if (full_cal_en == FullCalPara.BypassCal) {
        DSAPI_SET = default_DSAPI[6]; //CASE7
    } else {
        //	cout << "Can't find valid Full_cal_en parameter !!! Please check Full_cal_en parameter!" << endl;
        printf("Can't find valid Full_cal_en parameter !!! Please check Full_cal_en parameter!\n");
    }

    // ***************  User Define End   *********************

    // Step3: DS API configuration
    d2s::d2s_LABEL_BEGIN("DS_API_Conf_CS_core_clk1_", Global_D2S_Mode);

    selectMacro_MB(MacroLane_Sel);
    // Step1: hold mcu in reset mode
    SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8);

    // Step2: load binary file to 32k byte size sram
    // Run pattern

    //Configure refclk frequency, users can get the information at frequency plan
    SRAM.CSAPIRegs.setrefclk0_freqm100_api(iRefclk0_freqm100).Write2DUT(1);
    SRAM.CSAPIRegs.setrefclk1_freqm100_api(iRefclk1_freqm100).Write2DUT(2);

    //Configure core_clk select
    SRAM.CSAPIRegs.setcore_clk_selext_pin_api(iCore_clk_selext_pin_api).Write2DUT(0); //CSR Broadcast Bug
    SRAM.CSAPIRegs.setcore_clk_sel_pin_api(iCore_clk_sel_pin_api).Write2DUT(0);

    SRAM.CSAPIRegs.setcoreclk_sel_en_api(iCoreclk_sel_en_api).Write2DUT(4);

    //GB setup
    /***************/
    SRAM.CSAPIRegs.setdsclkvreg_ofst_api(0x6)
            .settxpredrvreg_ofst_api(0x4)
            .setrxdatavreg_ofst_api(0x1)
            .Write2DUT(7);
    if (CUSTpara.GB_Enable == 1)
        SRAM.CSAPIRegs.setregulator_offset_en_api(0x1).Write2DUT(7);
    else
        SRAM.CSAPIRegs.setregulator_offset_en_api(0x0).Write2DUT(7);

    //                d2s::d2s_LABEL_END();
    //
    //                d2s::d2s_LABEL_BEGIN("DS_API_Conf_CS_core_clk2_", Global_D2S_Mode);
    for (size_t macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        INT MacroID = MacroLane_Sel[macroIndex].MacroID;
        selectMacro(MacroID);

        if (GlobalInitPattern.find("_Case01") != string::npos)
            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[0];
        else if (GlobalInitPattern.find("_Case02") != string::npos)
            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[1];
        else if (GlobalInitPattern.find("_Case03") != string::npos)
            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[2];
        else {
            //				cout << "Can't find valid init pattern !!! Please check pattern name!" << endl;
            printf("Can't find valid init pattern !!! Please check pattern name!\n");
        }
        if (iLifeclk2dig_sel_pin_api != 1 && iLifeclk2dig_sel_pin_api != 0 && iLifeclk2dig_sel_pin_api != -1) {
            //				cout << "Invalid macro has been choose !!! Please check macro ID!" << endl;
            printf("Invalid macro has been choose !!! Please check macro ID!\n");
        }

        SRAM.CSAPIRegs.setlifeclk2dig_sel_pin_api(iLifeclk2dig_sel_pin_api).Write2DUT(0, false);
        //Configure the index number of dataslice on the north side of clockslice.
        SRAM.CSAPIRegs.setds_index_north_cs_api(HILINK_INFO[MacroID].DS_powerup_sequence[0]).Write2DUT(0, false);


        //for(UINT laneIndex=0; laneIndex < MacroLane_Sel[macroIndex].vLane.size();laneIndex++)//SongXin: change for new data structure
        for (UINT laneIndex = 0; laneIndex < HILINK_INFO[MacroID].Lane_Num; laneIndex++) {
            //Configure DS calibration by pass enable
            SRAM.DSAPIRegs.MacroID(MacroID).SliceID(laneIndex).Broadcast(0);

            DsCalibrationBypassConfig(DSAPI_SET);

            if (full_cal_en == FullCalPara.FullCal_FWABIST_USE) {
                SRAM.DSAPIRegs.setds_power_mode_api(0x3).Write2DUT(0, false); //LR set 3
                SRAM.DSAPIRegs.setrxctlerefminthbypass_api(0x1).Write2DUT(3, false);
            } else if (full_cal_en == FullCalPara.BypassCal or full_cal_en == FullCalPara.FullCal or full_cal_en == FullCalPara.REFLOCKRANGE_USE) {
                if (dHsclk_GHz * 2 > 30) {
                    SRAM.DSAPIRegs.setds_power_mode_api(0x0).Write2DUT(0, false);
                } else {
                    SRAM.DSAPIRegs.setds_power_mode_api(0x3).Write2DUT(0, false);
                }
            } else {
                //					cout << "Can't find valid Full_cal_en parameter !!! Please check Full_cal_en parameter!" << endl;
                printf("Can't find valid Full_cal_en parameter !!! Please check Full_cal_en parameter!\n");
            }

            //				if(dHsclk_GHz*2>=25 && full_cal_en ==0) //fullcal not do dcd cal, add bushaoxue 20170516, align to uflx
            if (dHsclk_GHz * 2 >= 0) //work arond, default setting do dcd calibraiton, user should detemine whether do DCD Cal
            {
                SRAM.DSAPIRegs.settxdcdcalibbypass_api(0x0).Write2DUT(3, false);
            } else {
                SRAM.DSAPIRegs.settxdcdcalibbypass_api(0x1).Write2DUT(3, false);
            }

            if (full_cal_en == FullCalPara.BypassCal)
                SRAM.DSAPIRegs.setds_write_back_ctrl_api(0x1).Write2DUT(3, false); //bypass cal

            //Enable DS calibration
            SRAM.DSAPIRegs.setds_calib_en_api(0x1).Write2DUT(0, false);
        }
    }
    selectMacro_MB(MacroLane_Sel);
    SRAM.CPAPIRegs.setmcurstb(0x1).Write2DUT(8);
    d2s::d2s_LABEL_END();
    // Step4: monitor TOP_FSM_DONE until calibration finished
    // Wait for calibration to complete by checking status of TOP_FSM_DONE
    INT iCheckCount = 0;
    INT iMaxTimeout = 100; //SongXin: Put MaxTimeout out of for-loop to reduce test time, because check done is parallel for all sites.
    INT WAITDONERESULT = 1;


    EXPECT_RESULT Top_Fsm_Result;
    do {
        iCheckCount++;
//        api->sleep(0.01);
    	TheInst.Wait(0.010);
        hout(DETAIL) << "iCheckCount : " << iCheckCount << endl;
        Check_Top_Fsm_Done(MacroLane_Sel, Top_Fsm_Result);
    } while (Top_Fsm_Result.allpass != true && iCheckCount < iMaxTimeout);



    for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        INT MacroID = MacroLane_Sel[macroIndex].MacroID;

//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int SiteID = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
            mDS_Cal_MacroResult[SiteID][MacroID] = Top_Fsm_Result.eachsite[SiteID];
            if (mDS_Cal_MacroResult[SiteID][MacroID] == 0) {
                WAITDONERESULT = 0;
            }
            if (iCheckCount >= iMaxTimeout) {
                hout(DETAIL) << "Site" << SiteID << " Dataslice calibration TimeOut !!!!!!!!!" << endl;
            } else {
                hout(DETAIL) << "Site" << SiteID << " Dataslice calibration success on MACRO" << MacroID << " !!!!!!!!!" << endl;
            }
            FOREACH_ACTIVESITE_END
    }


    if ((WAITDONERESULT == 0) || (Global_D2S_Mode == 0)) {
        iMaxTimeout = 1;
        for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            INT MacroID = MacroLane_Sel[macroIndex].MacroID;
            iCheckCount = 0;
            do {
                iCheckCount++;
                hout(DETAIL) << "iCheckCount : " << iCheckCount << endl;
                Check_Top_Fsm_Done(MacroID, Top_Fsm_Result);
            } while (Top_Fsm_Result.allpass != true && iCheckCount < iMaxTimeout);

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
                FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
                mDS_Cal_MacroResult[SiteID][MacroID] = Top_Fsm_Result.eachsite[SiteID];
                //printf("mDS_Cal_MacroResult[%d][%d]= %d\n", SiteID, MacroID, mDS_Cal_MacroResult[SiteID][MacroID]);
                if (iCheckCount >= iMaxTimeout) {
                    hout(DETAIL) << "Site" << SiteID << " Dataslice calibration TimeOut !!!!!!!!!" << endl;
                } else {
                    hout(DETAIL) << "Site" << SiteID << " Dataslice calibration success on MACRO" << MacroID << " !!!!!!!!!" << endl;
                }
                FOREACH_ACTIVESITE_END
        }
    }
    //        ALL_CSR_ReadBack_TO_FILE_Debug(MacroLane_Sel,"DsFwCalibration");



    //Step5: DisableDScalibration
    d2s::d2s_LABEL_BEGIN("DsFwCalibration_DisableCSandDScalibration_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8);
    Clear_CS_API();
    Clear_DS_API(MacroLane_Sel);

    d2s::d2s_LABEL_END();

}



//Dataslice Configuration after Calibration

void DsConfigurationAfterCalibration() {

}




//Calibration

void HiLink30_FW_CAL(MACRO_LANE_SEL& MacroLane_Sel, CUSTPARA& CUSTpara, SSPARA& SSpara, CSPARA& CSpara, MACRO_INT &mCS_Cal_MacroResult, MACRO_INT &mCsCalVcoLockPerMacro, MACRO_INT &mDS_Cal_MacroResult, STRING sCalibrationType, const string full_cal_en, INT iSSCalOnce) {
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    MACRO_INT mSS_Cal_Result;
    MACRO_INT iCsCalVcoLockPerMacro;
    iCsCalVcoLockPerMacro.init(0);
    mSS_Cal_Result.init(0);

    MACRO_LANE_SEL vProcessMacroSS;

    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    //CS Calibration Begin
    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

    if (SSpara.RefclkBus == 0) {
        STRING sSSMacroList = SSMacroIDList_Refclk1;
        Select_Macro_Lane(vProcessMacroSS, sSSMacroList);
    } else {
        STRING sSSMacroList = SSMacroIDList;
        Select_Macro_Lane(vProcessMacroSS, sSSMacroList);
    }

    hout(DETAIL) << "\n@@@@@@@@@@  SS cal start  @@@@@@@@@@@@\n" << endl;
    if (sCalibrationType == "CS+DS") {
        iSSCalOnce = 0;
    }
    if (iSSCalOnce == 1) {

        CSConfigurationBeforeCalibration_SSConfig(vProcessMacroSS, CUSTpara, SSpara);
        CsFwCalibration(vProcessMacroSS, CUSTpara, SSpara, CSpara, mSS_Cal_Result, mCsCalVcoLockPerMacro, full_cal_en, 1);// mCsCalVcoLockPerMacro =0  error note by tony 20210609
//      ALL_CSR_ReadBack_TO_FILE_Debug(MacroLane_Sel,"After_SsFwCalibration");

    }

    if (sCalibrationType == "SS") {

//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int SiteID = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
            for (UINT macroIndex = 0; macroIndex < vProcessMacroSS.size(); macroIndex++) {
                UINT MacroID = vProcessMacroSS[macroIndex].MacroID;
                mCS_Cal_MacroResult[SiteID][MacroID] = mSS_Cal_Result[SiteID][MacroID];
            }
            FOREACH_ACTIVESITE_END

        return;
    }

    hout(DETAIL) << "\n@@@@@@@@@@  SS cal end  @@@@@@@@@@@@\n" << endl;
    hout(DETAIL) << "\n@@@@@@@@@@  CS cal start  @@@@@@@@@@@@\n" << endl;

    //PLL calibration
    CSConfigurationBeforeCalibration_PLLConfig(MacroLane_Sel, CUSTpara, SSpara, CSpara);

    CsFwCalibration(MacroLane_Sel, CUSTpara, SSpara, CSpara, mCS_Cal_MacroResult, mCsCalVcoLockPerMacro, full_cal_en, 0);

//            ALL_CSR_ReadBack_TO_FILE_Debug(MacroLane_Sel,"After_CsFwCalibration");

            //.......................................................... print topapi begining..........................................//
            d2s::d2s_LABEL_BEGIN("CS_LOCK_CHECK", Global_D2S_Mode);
             for (UINT iMacroIndex = 0; iMacroIndex < MacroLane_Sel.size(); iMacroIndex ++)
             {
                     UINT MacroID = MacroLane_Sel[iMacroIndex].MacroID;
                     selectMacro(MacroID);
                     CS.clkRegs.MacroID(MacroID);

                     char IDstring[128] = "";
                     sprintf (IDstring,"csclk_csr2_onMacro%i",MacroID);
                     CS.clkRegs.Read2IDString(2,IDstring);

            }
            d2s::d2s_LABEL_END();


         MACRO_DOUBLE CS_LOCK;
         FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
            for (UINT iMacroIndex = 0; iMacroIndex < MacroLane_Sel.size(); iMacroIndex ++)
            {
                    UINT MacroID = MacroLane_Sel[iMacroIndex].MacroID;
                    char IDstring[128] = "";
                    sprintf (IDstring, "csclk_csr2_onMacro%i",MacroID);

                    uint val = (UINT)jtag.getReadValue(IDstring)[SiteID];

                    if(PrintDebugEn) printf("val_before= %u\n",val);
                    CS_LOCK[SiteID][MacroID]=HILINK_Regs_Base::get_bits(val,CS.clkRegs.REG_INFO.pll0outoflock());
                    if(PrintDebugEn) printf("CS_LOCK[%d][%d]= %f\n",SiteID,MacroID,CS_LOCK[SiteID][MacroID]);
                    if(PrintDebugEn) printf("val_after= %u\n",val);

            }
            FOREACH_ACTIVESITE_END
         //.......................................................... print topapi end..........................................//
    CSConfigurationAfterCalibration(MacroLane_Sel);

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//            printf("****************  mCsCalVcoLockPerMacro[%d][%d]= %d", SiteID, MacroID, mCsCalVcoLockPerMacro[SiteID][MacroID]);
            for (UINT ssMacroIndex = 0; ssMacroIndex < vProcessMacroSS.size(); ssMacroIndex++) {
                if (mSS_Cal_Result[SiteID][vProcessMacroSS[ssMacroIndex].MacroID] == 0 && iSSCalOnce == 1) {
                    mCsCalVcoLockPerMacro[SiteID][MacroID] = 0;
                    mCS_Cal_MacroResult[SiteID][MacroID] = 0;
                }
            }
        }
        FOREACH_ACTIVESITE_END

    hout(DETAIL) << "&&&&&&& ReadALLRegistors After CS Cal &&&&&&&&&" << endl;

    if (sCalibrationType == "SS+CS") {
        return;
    }

    hout(DETAIL) << "\n@@@@@@@@@@  DS cal start  @@@@@@@@@@@@\n" << endl;

    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    //DS Calibration Begin
    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

    DsConfigurationBeforeCalibration(MacroLane_Sel, CSpara, SSpara, CUSTpara, full_cal_en);

    DsFwCalibration(MacroLane_Sel, CUSTpara, SSpara, CSpara, mDS_Cal_MacroResult, full_cal_en);

    if ( 1 == Global_D2S_Mode) {
            //.......................................................... print topapi begining..........................................//
            MACRO_DOUBLE dTop_fsm_api;
    //        d2s_JTAG& jtag = d2s_JTAG::Instance();

            d2s::d2s_LABEL_BEGIN("Read_Top_Fsm_Api", Global_D2S_Mode);

             for (UINT iMacroIndex = 0; iMacroIndex < MacroLane_Sel.size(); iMacroIndex ++)
             {
                     UINT MacroID = MacroLane_Sel[iMacroIndex].MacroID;
                     selectMacro(MacroID);
                     SRAM.TOPAPIRegs.MacroID(MacroID);

                     char IDstring[128] = "";
                     sprintf (IDstring,"sramtopapi_csr0_onMacro%i",MacroID);
                   SRAM.TOPAPIRegs.Read2IDString(0,IDstring);
    //                 jtag.read(0x1fffe>>1,IDstring);

            }
            d2s::d2s_LABEL_END();

            MACRO_DOUBLE top_fsm_api;
//            FOREACH_ACTIVE_SITE(api) {
//               unsigned int SiteID = api->Get_active_site();
               FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
               for (UINT iMacroIndex = 0; iMacroIndex < MacroLane_Sel.size(); iMacroIndex ++)
               {
                       UINT MacroID = MacroLane_Sel[iMacroIndex].MacroID;
                       char IDstring[128] = "";
                       sprintf (IDstring, "sramtopapi_csr0_onMacro%i",MacroID);

                       uint val = (UINT)jtag.getReadValue(IDstring)[SiteID];
                       top_fsm_api[SiteID][MacroID]=HILINK_Regs_Base::get_bits(val,SRAM.TOPAPIRegs.REG_INFO.top_fsm_api());
                       if(PrintDebugEn) printf("top_fsm_api[%d][%d]= %f\n",SiteID,MacroID,top_fsm_api[SiteID][MacroID]);
//                       printf("val= %u\n",val);

               }
               FOREACH_ACTIVESITE_END

            //.......................................................... print topapi end..........................................//
    }
    DsConfigurationAfterCalibration();

    //	hout(DETAIL) << "&&&&&&& ReadALLRegistors After DS Cal &&&&&&&&&" << endl;

    if (sCalibrationType == "SS+CS+DS") {
        return;
    }
    if (sCalibrationType == "CS+DS") {
        return;
    }
    return;
}

void FWreadDefaultRegisters2CSR(MACRO_LANE_SEL& MacroLane_Sel) {
    INT iDebugAnalog;
    INT HiLink_Macro_CsNum = 1;
    //	GET_TESTFLOW_FLAG	("debug_analog",&iDebugAnalog);

    UINT site = get_focus_site();

    //	hout(DETAIL) << "site "<< site <<"'s CSR will be readback as default value!" << endl;

    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        selectMacro_Now(MacroID);

        //		hout(DETAIL) << "Macro = "<< MacroID << endl;

        for (INT csIndex = 0; csIndex < HiLink_Macro_CsNum; csIndex++) {
            //			hout(DETAIL) << "=========CS_READ==========" << endl;
            //			hout(DETAIL) << "CS Slice = "<< csIndex << endl;

            CS.clkRegs.MacroID(MacroID).SliceID(0).Broadcast(0);
            CS.clkRegs.ReadAll2CSR();
            CS.clkdebug.MacroID(MacroID).SliceID(0).Broadcast(0);
            CS.clkdebug.ReadAll2CSR();
        }
    }
    /*******Only read macro[0], for There is only one local DS file ***********/
    //	selectMacro_Now(MacroLane_Sel[0].MacroID);
    //
    //	hout(DETAIL) << "Macro = "<< MacroLane_Sel[0].MacroID << endl;
    //	hout(DETAIL) << "=========DS_READ==========" << endl;
    //
    //	//SongXin: add to avoid no lane0
    //	UINT MacroID = MacroLane_Sel[0].MacroID;
    //	const vector<UINT>& vLane = MacroLane_Sel[0].vLane;
    //	UINT LaneID = vLane[0];
    //
    //	DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
    //	DS.txRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
    //	DS.clkRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
    //	DS.rxExtRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
    //	SRAM.CPAPIRegs.MacroID(MacroID);
    //	SRAM.CSAPIRegs.MacroID(MacroID);
    //	SRAM.DSAPIRegs.MacroID(MacroID);
    //	SRAM.TOPAPIRegs.MacroID(MacroID);
    //	SRAM.ABISTAPIRegs.MacroID(MacroID);
    //
    //	DS.rxRegs.ReadAll2CSR();
    //	DS.rxExtRegs.ReadAll2CSR();
    //	DS.txRegs.ReadAll2CSR();
    //	DS.clkRegs.ReadAll2CSR();
    //
    //	SRAM.CPAPIRegs.ReadAll2CSR();
    //	SRAM.CSAPIRegs.ReadAll2CSR();
    //	SRAM.DSAPIRegs.ReadAll2CSR();
    //	SRAM.TOPAPIRegs.ReadAll2CSR();
    //    SRAM.ABISTAPIRegs.ReadAll2CSR();
}




//Running Adaptation Firmware

void ATE_CTLE_Adaptation(MACRO_LANE_SEL& MacroLane_Sel, CUSTPARA& Custpara, DOUBLE dRefclkMHz, DOUBLE dRefclkMHz2, MACRO_INT &mDS_Cal_MacroResult, STRING& sLoopBackMode) {

    d2s_JTAG& jtag = d2s_JTAG::Instance();

    uint iRefclk0_freqm100 = uint(dRefclkMHz * 100);
    uint iRefclk1_freqm100 = uint(dRefclkMHz2 * 100); // refclk1 have a 25MHz offset with refclk0
    int iCore_clk_selext_pin_api = giCore_clk_selext_pin_api;
    int iCore_clk_sel_pin_api = giCore_clk_sel_pin_api;
    int iLifeclk2dig_sel_pin_api = giLifeclk2dig_sel_pin_api;
    int iCoreclk_sel_en_api = giCoreclk_sel_en_api;

    DSAPI_Adaptation DSapi_Adaptation;

    INT ictleactgn1 = 3;
    INT ictleactgn2 = 3;
    INT ictleactgn3 = 7;
    INT ctleboostc1 = 5;
    INT ctleboostc2 = 3;
    INT ctleboostc3 = 3;

    INT ctleza1 = 0;
    INT ctleza2 = 0;
    INT ctleza3 = 0;
    INT ctlesqh1 = 2;
    INT ctlesqh2 = 2;
    INT ctlesqh3 = 2;

    INT ctlecmband1 = 2;
    INT ctlecmband2 = 1;
    INT ctlecmband3 = 1;
    INT ctlermband1 = 2;
    INT ctlermband2 = 1;
    INT ctlermband3 = 1;
    INT ctlehfzen1 = 0;
    INT ctlehfzen2 = 0;
    INT ctlehfzen3 = 0;



    //READ_ALL_CSR;

    /**************Clear API and CSConfigBeforeCal***set proper API depending on applications and Release MCU*********/
    //#if HIGGS_PRIVATE
    //	if (jtag.Context == "DEFAULT")
    //	{
    //		ctleza1		= 4;
    //		ctleza2		= 1;
    //		ctleza3 	= 1;
    //		ctlesqh1 	= 1;
    //		ctlesqh2 	= 1;
    //		ctlesqh3 	= 1;
    //		//new add by shaoxue 20170216,set fir txmain to get ctle adpt,tmp solution for higgs abist lb.
    //		Custpara.TxFIR_USER.iTxMain=12; //12
    //		Custpara.TxFIR_USER.iTxPost1st=0;
    //		Custpara.TxFIR_USER.iTxPost2nd=0;
    //		Custpara.TxFIR_USER.iTxPre1st=0; //0
    //		Custpara.TxFIR_USER.iTxPre2nd=0;
    //		//add end 20170216
    //	}
    //#endif

    //Select loopBack mode
    //		if (jtag.Context == "DEFAULT"){
    LoopBack_Setting(sLoopBackMode, MacroLane_Sel, Custpara);
    //		}
    d2s::d2s_LABEL_BEGIN("Adaptation_Set_DScal_Step2_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);

    DS.rxRegs.SliceID(0).Broadcast(1);
    DS.txRegs.SliceID(0).Broadcast(1);
    DS.clkRegs.SliceID(0).Broadcast(1);
    DS.rxExtRegs.SliceID(0).Broadcast(1);

    //#if HIGGS_PRIVATE
    //			if (jtag.Context == "DEFAULT"){
    //				SetTxFir(Custpara); //add by shaoxue 20170216
    //			}
    //#endif
    //Set Fix CTLE setting for adaptation
    DS.rxRegs.setctleactgn1(ictleactgn1).Write2DUT(1);
    DS.rxRegs.setctleactgn2(ictleactgn2).Write2DUT(2);
    DS.rxRegs.setctleactgn3(ictleactgn3).Write2DUT(3);
    DS.rxRegs.setctleboostc1(ctleboostc1).Write2DUT(1);
    DS.rxRegs.setctleboostc2(ctleboostc2).Write2DUT(2);
    DS.rxRegs.setctleboostc3(ctleboostc3).Write2DUT(3);
    DS.rxRegs.setctleza1(ctleza1).Write2DUT(1);
    DS.rxRegs.setctleza2(ctleza2).Write2DUT(2);
    DS.rxRegs.setctleza3(ctleza3).Write2DUT(3);
    DS.rxRegs.setctlesqh1(ctlesqh1).Write2DUT(1);
    DS.rxRegs.setctlesqh2(ctlesqh2).Write2DUT(2);
    DS.rxRegs.setctlesqh3(ctlesqh3).Write2DUT(3);
    DS.rxRegs.setctlecmband1(ctlecmband1).Write2DUT(1);
    DS.rxRegs.setctlecmband2(ctlecmband2).Write2DUT(2);
    DS.rxRegs.setctlecmband3(ctlecmband3).Write2DUT(3);
    DS.rxRegs.setctlermband1(ctlermband1).Write2DUT(1);
    DS.rxRegs.setctlermband2(ctlermband2).Write2DUT(2);
    DS.rxRegs.setctlermband3(ctlermband3).Write2DUT(3);
    DS.rxRegs.setctlehfzen1(ctlehfzen1).Write2DUT(1);
    DS.rxRegs.setctlehfzen2(ctlehfzen2).Write2DUT(2);
    DS.rxRegs.setctlehfzen3(ctlehfzen3).Write2DUT(3);

    //			if (jtag.Context == "DEFAULT"){
    //Enable PRBS generator with PRBS15
    EnableTxPrbsGen("PRBS15");
    //			}

    //Unfreeze CDR
    DS.rxRegs.setcdrfreeze(0x1).Write2DUT(12);
    jtag.wait(0.0001);
    DS.rxRegs.setcdrfreeze(0x0).Write2DUT(12);
    jtag.wait(0.0001);


    d2s::d2s_LABEL_END();



    // RunAdaptation()-------Start------------

    STRING spRXName = "";
    if (jtag.Context == "FASTDIFF") {
        spRXName = "pUDIRXDATA"; //burst pRX Port Pattern
    } else {

#ifndef TestChip
        spRXName = "pHilink_LS"; //for element build error
#else
        spRXName = "pLS";
#endif
    }

    TransactionPort pRX(spRXName);
    //	jtag.registerTransactionPort(pRX);

    d2s::d2s_LABEL_BEGIN("Adaptation_Set_DScal_Step3_", Global_D2S_Mode);


    selectMacro_MB(MacroLane_Sel);

    SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8);

    SRAM.CSAPIRegs.setrefclk0_freqm100_api(iRefclk0_freqm100).Write2DUT(1);
    SRAM.CSAPIRegs.setrefclk1_freqm100_api(iRefclk1_freqm100).Write2DUT(2);
    //Configure core_clk select
    SRAM.CSAPIRegs.setcore_clk_selext_pin_api(iCore_clk_selext_pin_api).Write2DUT(0); //CSR Broadcast Bug
    SRAM.CSAPIRegs.setcore_clk_sel_pin_api(iCore_clk_sel_pin_api).Write2DUT(0);

    SRAM.CSAPIRegs.setcoreclk_sel_en_api(iCoreclk_sel_en_api).Write2DUT(4);

    d2s::d2s_LABEL_END();

    d2s::d2s_LABEL_BEGIN("Adaptation_Set_DScal_Step4_", Global_D2S_Mode);
    if (jtag.Context == "FASTDIFF") {
        STRING sPatternLabel;
        long lPatternCycle;
        sPatternLabel = ATE_MODE_RX_FASTDIFF_PATTERN_LABEL_PRBS15_LONG2;
        lPatternCycle = ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE_PRBS15_LONG2;
        pRX.execLabel(sPatternLabel, lPatternCycle);
    }

    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        selectMacro(MacroID);

        if(PrintDebugEn) cout<<"Adaptation_Set_DScal_Step4_  init pattern ="<<GlobalInitPattern<<endl;

        if (GlobalInitPattern.find("_Case01") != string::npos)
            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[0];
        else if (GlobalInitPattern.find("_Case02") != string::npos)
            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[1];
        else if (GlobalInitPattern.find("_Case03") != string::npos)
            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[2];
        else {
            //				cout << "Can't find valid init pattern !!! Please check pattern name!" << endl;
            printf("Can't find valid init pattern !!! Please check pattern name!\n");
        }
        if (iLifeclk2dig_sel_pin_api != 1 && iLifeclk2dig_sel_pin_api != 0 && iLifeclk2dig_sel_pin_api != -1) {
            //				cout << "Invalid macro has been choose !!! Please check macro ID!" << endl;
            printf("Invalid macro has been choose !!! Please check macro ID!\n");
        }

        SRAM.CSAPIRegs.setlifeclk2dig_sel_pin_api(iLifeclk2dig_sel_pin_api).Write2DUT(0, false);
        for (UINT laneIndex = 0; laneIndex < MacroLane_Sel[macroIndex].vLane.size(); laneIndex++) {
            UINT sliceID = MacroLane_Sel[macroIndex].vLane[laneIndex];
            SRAM.DSAPIRegs.MacroID(MacroID).SliceID(sliceID).Broadcast(0);

            DSapi_Adaptation = default_DSAPI_Adaptation[0];
            DsAdaptationBypassConfig(DSapi_Adaptation); //CASE1
            SRAM.DSAPIRegs.setds_write_back_ctrl_api(0).Write2DUT(3, false);
        }
    }

    selectMacro_MB(MacroLane_Sel);
    SRAM.CPAPIRegs.setmcurstb(0x1).Write2DUT(8);
    d2s::d2s_LABEL_END();
    // RunAdaptation()-------End------------



    // monitor TOP_FSM_DONE until calibration finished
    // Wait for calibration to complete by checking status of TOP_FSM_DONE
    INT iCheckCount = 0;
    INT iMaxTimeout = (Global_D2S_Mode == LearningMode) ? 1000 : 200;

    if(PrintDebugEn) cout<<"function ATE_CTLE_Adaptation doing Check_Top_Fsm_Done  iMaxTimeout ="<<dec << iMaxTimeout << endl;
    EXPECT_RESULT Top_Fsm_Result;

    do {
        iCheckCount++;
//        api->sleep(0.001);
    	TheInst.Wait(0.002);
        Check_Top_Fsm_Done(MacroLane_Sel, Top_Fsm_Result);
    } while (Top_Fsm_Result.allpass != true && iCheckCount < iMaxTimeout);
    if(PrintDebugEn) cout<< "doing  Check_Top_Fsm_Done ,final the check count="<<dec<<iCheckCount<< endl;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            INT MacroID = MacroLane_Sel[macroIndex].MacroID;
            mDS_Cal_MacroResult[SiteID][MacroID] = Top_Fsm_Result.eachsite[SiteID];
            if(PrintDebugEn) printf("mDS_Cal_MacroResult[%d][%d]= %d\n", SiteID, MacroID, mDS_Cal_MacroResult[SiteID][MacroID]);
            if (iCheckCount >= iMaxTimeout) {
                hout(DETAIL) << "Site" << SiteID << " CTLE Adaptation TimeOut !!!!!!!!!" << endl;
            } else {
                hout(DETAIL) << "Site" << SiteID << " CTLE Adaptation success on MACRO" << MacroID << " !!!!!!!!!" << endl;
            }
        }
        FOREACH_ACTIVESITE_END

    //#if HIGGS_PRIVATE
    //	if (jtag.Context == "DEFAULT"){
    //		//add by shaoxue 20170216,restore the FIR value to 57,-6
    //		Custpara.TxFIR_USER.iTxMain=57;
    //		Custpara.TxFIR_USER.iTxPost1st=0;
    //		Custpara.TxFIR_USER.iTxPost2nd=0;
    //		Custpara.TxFIR_USER.iTxPre1st=-6;
    //		Custpara.TxFIR_USER.iTxPre2nd=0;
    //		//add end 20170216
    //	}
    //#endif

    // DisableDScalibration
    d2s::d2s_LABEL_BEGIN("DsFwCalibration_DisableCSandDScalibration_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8);
    Clear_CS_API();
    //#if HIGGS_PRIVATE
    //	if (jtag.Context == "DEFAULT"){
    //		SetTxFir(Custpara); //add by shaoxue 20170216
    //	}
    //#endif
    Clear_DS_API(MacroLane_Sel);
    d2s::d2s_LABEL_END();
    //Read back CTLE setting
    if (Global_D2S_Mode == 0)InitCtlePerMacroPerLane(MacroLane_Sel); //todo
}

void ATE_CTLE_Bypass_Adaptation(MACRO_LANE_SEL& MacroLane_Sel, CUSTPARA& Custpara, DOUBLE dRefclkMHz, DOUBLE dRefclkMHz2, MACRO_INT &mDS_Cal_MacroResult, STRING& sLoopBackMode) {


    uint iRefclk0_freqm100 = uint(dRefclkMHz * 100);
    uint iRefclk1_freqm100 = uint(dRefclkMHz2 * 100); // refclk1 have a 25MHz offset with refclk0
    int iCore_clk_selext_pin_api = giCore_clk_selext_pin_api;
    int iCore_clk_sel_pin_api = giCore_clk_sel_pin_api;
    int iLifeclk2dig_sel_pin_api = giLifeclk2dig_sel_pin_api;
    int iCoreclk_sel_en_api = giCoreclk_sel_en_api;

    DSAPI_Adaptation DSapi_Adaptation;

    /**************Clear API and CSConfigBeforeCal***set proper API depending on applications and Release MCU*********/
    // RunAdaptation()-------Start------------

    d2s::d2s_LABEL_BEGIN("Adaptation_Set_DScal_Step3_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);

    //SRAM.CPAPIRegs.setmcurstb(0x0).setcsmasterifmode(0x2).setmcupwrdb(0x1).Write2DUT(8);
    SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8);

    SRAM.CSAPIRegs.setrefclk0_freqm100_api(iRefclk0_freqm100).Write2DUT(1);
    SRAM.CSAPIRegs.setrefclk1_freqm100_api(iRefclk1_freqm100).Write2DUT(2);
    //Configure core_clk select
    SRAM.CSAPIRegs.setcore_clk_selext_pin_api(iCore_clk_selext_pin_api).Write2DUT(0); //CSR Broadcast Bug
    SRAM.CSAPIRegs.setcore_clk_sel_pin_api(iCore_clk_sel_pin_api).Write2DUT(0);

    SRAM.CSAPIRegs.setcoreclk_sel_en_api(iCoreclk_sel_en_api).Write2DUT(4);

    d2s::d2s_LABEL_END();

    d2s::d2s_LABEL_BEGIN("Adaptation_Set_DScal_Step4_", Global_D2S_Mode);
    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        selectMacro(MacroID);
        if(PrintDebugEn) cout<<"Adaptation_Set_DScal_Step4_  GlobalInitPattern = "<<GlobalInitPattern<<endl;

        if (GlobalInitPattern.find("_Case01") != string::npos)
            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[0];
        else if (GlobalInitPattern.find("_Case02") != string::npos)
            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[1];
        else if (GlobalInitPattern.find("_Case03") != string::npos)
            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[2];
        else {
            //				cout << "Can't find valid init pattern !!! Please check pattern name!" << endl;
            printf("Can't find valid init pattern !!! Please check pattern name!\n");
        }
        if (iLifeclk2dig_sel_pin_api != 1 && iLifeclk2dig_sel_pin_api != 0 && iLifeclk2dig_sel_pin_api != -1) {
            //				cout << "Invalid macro has been choose !!! Please check macro ID!" << endl;
            printf("Invalid macro has been choose !!! Please check macro ID!\n");
        }

        SRAM.CSAPIRegs.setlifeclk2dig_sel_pin_api(iLifeclk2dig_sel_pin_api).Write2DUT(0, false);
        for (UINT laneIndex = 0; laneIndex < MacroLane_Sel[macroIndex].vLane.size(); laneIndex++) {
            UINT sliceID = MacroLane_Sel[macroIndex].vLane[laneIndex];
            SRAM.DSAPIRegs.MacroID(MacroID).SliceID(sliceID).Broadcast(0);

            SRAM.DSAPIRegs.setds_ctle_en_api(0x1).Write2DUT(0, false);
            SRAM.DSAPIRegs.setds_write_back_ctrl_api(0x1).Write2DUT(3, false);
        }
    }

    selectMacro_MB(MacroLane_Sel);
    SRAM.CPAPIRegs.setmcurstb(0x1).Write2DUT(8);
    d2s::d2s_LABEL_END();
    // RunAdaptation()-------End------------

    // monitor TOP_FSM_DONE until calibration finished
    // Wait for calibration to complete by checking status of TOP_FSM_DONE
    INT iCheckCount = 0;
    INT iMaxTimeout = (Global_D2S_Mode == LearningMode) ? 200 : 200;

    EXPECT_RESULT Top_Fsm_Result;

    do {
        iCheckCount++;
//        Sleep(0.002);
//        TheInst.Wait(2*1000);
    	TheInst.Wait(0.002);//2ms
        Check_Top_Fsm_Done(MacroLane_Sel, Top_Fsm_Result);
    } while (Top_Fsm_Result.allpass != true && iCheckCount < iMaxTimeout);

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
        for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            INT MacroID = MacroLane_Sel[macroIndex].MacroID;
            mDS_Cal_MacroResult[SiteID][MacroID] = Top_Fsm_Result.eachsite[SiteID];
            //printf("mDS_Cal_MacroResult[%d][%d]= %d\n", SiteID, MacroID, mDS_Cal_MacroResult[SiteID][MacroID]);
            if (iCheckCount >= iMaxTimeout) {
                hout(DETAIL) << "Site" << SiteID << " CTLE bypass Adaptation TimeOut !!!!!!!!!" << endl;
                if(PrintDebugEn) cout<< "Site" << SiteID << " CTLE bypass Adaptation TimeOut !!!!!!!!!" << endl;
            } else {
                hout(DETAIL) << "Site" << SiteID << " CTLE bypass Adaptation success on MACRO" << MacroID << " !!!!!!!!!" << endl;
                if(PrintDebugEn) cout<< "Site" << SiteID << " CTLE bypass Adaptation success on MACRO" << MacroID << " !!!!!!!!!" <<" iCheckCount=" <<iCheckCount <<" iMaxTimeout="<<iMaxTimeout<< endl;
            }

        }
        FOREACH_ACTIVESITE_END
    //#if HIGGS_PRIVATE
    //	if (jtag.Context == "DEFAULT"){
    //		//add by shaoxue 20170216,restore the FIR value to 57,-6
    //		Custpara.TxFIR_USER.iTxMain=57;
    //		Custpara.TxFIR_USER.iTxPost1st=0;
    //		Custpara.TxFIR_USER.iTxPost2nd=0;
    //		Custpara.TxFIR_USER.iTxPre1st=-6;
    //		Custpara.TxFIR_USER.iTxPre2nd=0;
    //		//add end 20170216
    //	}
    //#endif
    //	MyTimer::stop("AdaptationWaitdone");
    //	MyTimer::start("Adaptationdisable");
    // DisableDScalibration
    d2s::d2s_LABEL_BEGIN("DsFwCalibration_DisableCSandDScalibration_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8);
    Clear_CS_API();
    //#if HIGGS_PRIVATE
    //	if (jtag.Context == "DEFAULT"){
    //		SetTxFir(Custpara); //add by shaoxue 20170216
    //	}
    //#endif
    Clear_DS_API(MacroLane_Sel);
    d2s::d2s_LABEL_END();
    //	MyTimer::stop("Adaptationdisable");
    //Read back CTLE setting
    //if(d2s_mode==1)InitCtlePerMacroPerLane(MacroLane_Sel);//todo
}


//DFx&Utilities

//DC

void RefClkCtrl(REFCLKCTRL refclkctrl) {
    //	FLEX_RELAY frelay;

#ifndef TestChip

    //		if(refclkctrl == DISCNCT ){
    //			frelay.pin(CLKPORT_PRODUCT).set("IDLE");
    //			frelay.execute();
    //		}
    //		else if (refclkctrl == CNCT ){
    //			frelay.pin(CLKPORT_PRODUCT).set("AC");
    //			frelay.execute();
    //		}

#else
    if (refclkctrl == DISCNCT) {
        frelay.pin(CLKPORT_TC).set("IDLE");
        frelay.execute();
    } else if (refclkctrl == CNCT) {
        frelay.pin(CLKPORT_TC).set("AC");
        frelay.execute();
    }

#endif
}

//Power Up Down




//bool DsPowerUpWoClkDis(MACRO_LANE_SEL& vMacroLane_Sel)
//{
//	//D2S_FRAMEWORK;
//	//GET_TEST_INFO;
//
//	sprintf(label,"DsPowerUpWoClkDis_QDIV2PWRDB_Set_%f_%f_",Vcoef,Temp);
////	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
//        d2s::d2s_LABEL_BEGIN("DsPowerUpWoClkDis_", Global_D2S_Mode);
//	// Power up DSCLK.
//	for(uint iMacroIndex=0;iMacroIndex<vMacroLane_Sel.size();iMacroIndex++)
//	{
//		UINT MacroID= vMacroLane_Sel[iMacroIndex].MacroID;
//		const vector<UINT>& vLane = vMacroLane_Sel[iMacroIndex].vLane;
//
//		selectMacro(MacroID);
//
//		// Power on DS on the north side of CS, the DS physically closer to CS should be powered up first.
//		// Power on DS on the south side of CS, the DS physically closer to CS should be powered up first.
//		for(uint iLaneIndex = 0;iLaneIndex < HILINK_INFO[MacroID].Lane_Num;iLaneIndex++)
//		{
//			uint LaneID=HILINK_INFO[MacroID].DS_powerup_sequence[iLaneIndex];
//			DS.clkRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
//			DS.clkRegs.setqdiv2pwrdb(0x1).Write2DUT(1);
//			jtag.wait(50 us);
//			TxPowerUpDown(MacroID,LaneID,1);
//			RxPowerUpDown(MacroID,LaneID,1);
//		}
//	}
////	fr.d2s_LABEL_END();
//d2s::d2s_LABEL_END();
//	return true;
//}


//TX2RX
//==============================================================================
// Function: EnableTxToRxParLpbk
// - This function is used to enable Tx to Rx parallel loopback.
// - Please refer datasheet chapter 7.5 to find more details about loopback scheme.
//==============================================================================

void EnableTxToRxParLpbk() {
    DS.rxRegs.setcdrfreeze(0x1).Write2DUT(12);
    DS.rxRegs.settxrxparlpbken(0x1).Write2DUT(12);
}
//==============================================================================
// Function: DisableTxToRxParLpbk
// - This function is used to disable Tx to Rx parallel loopback.
// - Please refer datasheet chapter 7.5 to find more details about loopback scheme.
//==============================================================================

void DisableTxToRxParLpbk() {
    DS.rxRegs.settxrxparlpbken(0x0).Write2DUT(12);
    DS.rxRegs.setcdrfreeze(0x0).Write2DUT(12);
}
//==============================================================================
// Function: EnableTxToRxSerLpbk
// - This function is used to enable Tx to Rx serial loopback.
// - Please refer datasheet chapter 7.5 to find more details about loopback scheme.
//==============================================================================

bool EnableTxToRxSerLpbk(MACRO_LANE_SEL &MacroLane_Sel, STRING &LoopBackMode, CUSTPARA& CUSTpara, DSAPI &DSApi) {
    d2s::d2s_LABEL_BEGIN("EnableTxToRxSerLpbk_SETUP_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    DS.txRegs.SliceID(0).Broadcast(1);

    if (LoopBackMode == "PreDriver") {
        DS.txRegs.settxrxserlpbksel(0x0).Write2DUT(35); // 0 = PreDrive; 1 = Bump;
        CUSTPARA CUSTpara_PreDrv;
        CUSTpara_PreDrv.TxFIR_USER.iTxMain = 0;
        CUSTpara_PreDrv.TxFIR_USER.iTxPre1st = 0;
        CUSTpara_PreDrv.TxFIR_USER.iTxPre2nd = 0;
        CUSTpara_PreDrv.TxFIR_USER.iTxPost1st = 0;
        SetTxFir(CUSTpara_PreDrv);
        DS.txRegs.settxtappwrdb(0x80).Write2DUT(11);
    } else if (LoopBackMode == "Bump") {
        DS.txRegs.settxrxserlpbksel(0x1).Write2DUT(35); // 0 = PreDrive; 1 = Bump;
        SetTxFir(CUSTpara);
    }

    DS.txRegs.settxrxserlpbken(0x1).Write2DUT(35);
    DS.txRegs.settxrxserlpbkdpmen(0x0).Write2DUT(35);

    // set looback default gain=0
    DS.txRegs.settxrxserlpbkgn1(0x0).Write2DUT(36);
    DS.txRegs.settxrxserlpbkgn2(0x0).Write2DUT(36);

    d2s::d2s_LABEL_END();
    return true;
}
//==============================================================================
// Function: DisableTxToRxSerLpbk
// - This function is used to disable Tx to Rx serial loopback.
// - Please refer datasheet chapter 7.5 to find more details about loopback scheme.
//==============================================================================

void DisableTxToRxSerLpbk(MACRO_LANE_SEL &MacroLane_Sel, CUSTPARA& CUSTpara, DSAPI &DSApi) {
    d2s::d2s_LABEL_BEGIN("DisableTxToRxSerLpbk_SETUP_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    DS.rxRegs.SliceID(0).Broadcast(1);
    DS.txRegs.SliceID(0).Broadcast(1);
    DS.rxExtRegs.SliceID(0).Broadcast(1);
    DS.clkRegs.SliceID(0).Broadcast(1);

    //	SetTxFir(CUSTpara); //mask on 4/10, confirmed with shaoxue

    DS.txRegs.settxrxserlpbken(0x0).Write2DUT(35);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
#if 0
    if (false == DsDcdReCalib(MacroLane_Sel, DSApi)) // Bypass API case3
    {
        //		return false;
    }
#endif
}
//==============================================================================
// Function: DisableTxToRxSerLpbk
// - This function is used to disable Rx to Tx parallel loopback.
// - Please refer datasheet chapter 7.5 to find more details about loopback scheme.
//==============================================================================
//bool EnableRxToTxParLpbk(MACRO_LANE_SEL &MacroLane_Sel,DSAPI &DSApi)
//{
//
////	D2S_FRAMEWORK;
//	//GET_TEST_INFO;
//
//	sprintf(label,"EnableRxToTxParLpbk_%f_%f_",Vcoef,Temp);
//	//fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
//        d2s::d2s_LABEL_BEGIN("EnableRxToTxParLpbk_", Global_D2S_Mode);
//	selectMacro_MB(MacroLane_Sel);
//	DS.txRegs.SliceID(0).Broadcast(1);
//
//	// Enable RX to TX parallel loopback.
//	DS.txRegs.settxclksel(0x1).Write2DUT(2);
//	DS.txRegs.settxdatasel(0x1).Write2DUT(2);
//
////	fr.d2s_LABEL_END();
//        d2s::d2s_LABEL_END();
//#if 0
//	if(false==DsDcdReCalib(MacroLane_Sel,DSApi))//Bypass API case3
//	{
//		return false;
//	}
//#endif
//
//
//	return true;
//}

//==============================================================================
// Function: DisableRxToTxParLpbk
// - This function is used to disbale Rx to Tx parallel loopback.
// - Please refer datasheet chapter 7.5 to find more details about loopback scheme.
// - Tx DCD calibration is necessary after go back to mission mode.
//==============================================================================

bool DisableRxToTxParLpbk(MACRO_LANE_SEL &MacroLane_Sel, DSAPI &DSApi) {
    //	D2S_FRAMEWORK;
    //GET_TEST_INFO;

    //	sprintf(label,"DisableRxToTxParLpbk_SETUP_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("DisableRxToTxParLpbk_SETUP_", Global_D2S_Mode);

    selectMacro_MB(MacroLane_Sel);
    DS.txRegs.SliceID(0).Broadcast(1);

    //DsTxDcdCalibData txDcdCalibData
    DS.txRegs.settxclksel(0x0).Write2DUT(2);
    DS.txRegs.settxdatasel(0x0).Write2DUT(2);

    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
#if 0
    // Do DCD calibration
    if (false == DsDcdReCalib(MacroLane_Sel, DSApi)) {
        //		return false;
    }
#endif
    return true;
}

//==============================================================================
// Function: EnableTxPrbsGen
// - This function is used to enable Tx PRBS generator.
// - Don't need to set align mode and clock select because PI code will never changed after calibration.
//==============================================================================

void EnableTxPrbsGen(STRING sPRBSPatternType, INT iCustomerPattern) {
    INT iTxcuspat1 = iCustomerPattern;
    INT iTxcuspat2 = iCustomerPattern;
    INT iTxcuspat3 = iCustomerPattern;
    INT iTxcuspat4 = iCustomerPattern;
    INT iTxcuspat5 = iCustomerPattern;

    // Select Tx PRBS pattern
    if (sPRBSPatternType == "PRBS7") {
        DS.txRegs.setprbsgenpatsel(0x0).Write2DUT(4);
    } else if (sPRBSPatternType == "PRBS9") {
        DS.txRegs.setprbsgenpatsel(0x1).Write2DUT(4);
    } else if (sPRBSPatternType == "PRBS10") {
        DS.txRegs.setprbsgenpatsel(0x2).Write2DUT(4);
    } else if (sPRBSPatternType == "PRBS11") {
        DS.txRegs.setprbsgenpatsel(0x3).Write2DUT(4);
    } else if (sPRBSPatternType == "PRBS15") {
        DS.txRegs.setprbsgenpatsel(0x4).Write2DUT(4);
    } else if (sPRBSPatternType == "PRBS20") {
        DS.txRegs.setprbsgenpatsel(0x5).Write2DUT(4);
    } else if (sPRBSPatternType == "PRBS23") {
        DS.txRegs.setprbsgenpatsel(0x6).Write2DUT(4);
    } else if (sPRBSPatternType == "PRBS31") {
        DS.txRegs.setprbsgenpatsel(0x7).Write2DUT(4);
    } else if (sPRBSPatternType == "CUSTOMER_PATTERN") {
        DS.txRegs.setprbsgenpatsel(0x8).Write2DUT(4);
    } else {
        DS.txRegs.setprbsgenpatsel(0x0).Write2DUT(4);
    }

    // Edit 80bits customer pattern
    if (sPRBSPatternType == "CUSTOMER_PATTERN") {
        DS.txRegs.settxcuspat1(iTxcuspat1).Write2DUT(5);
        DS.txRegs.settxcuspat2(iTxcuspat2).Write2DUT(6);
        DS.txRegs.settxcuspat3(iTxcuspat3).Write2DUT(7);
        DS.txRegs.settxcuspat4(iTxcuspat4).Write2DUT(8);
        DS.txRegs.settxcuspat5(iTxcuspat5).Write2DUT(9);
    }

    // Select Tx data from PRBS generator
    DS.txRegs.settxdatasel(0x2).Write2DUT(2);
    // Enable Tx PRBS generator
    DS.txRegs.setprbsgenen(0x1).Write2DUT(4);
}


//==============================================================================
// Function: DisableTxPrbsGenAndSwitchToMissionMode
// - Function of disable Tx PRBS generator
// - Don't need to set align mode and clock select because PI code will never changed after calibration
//==============================================================================

void DisableTxPrbsGen() {
    //Disable Tx PRBS generator
    DS.txRegs.setprbsgenen(0x0).Write2DUT(4);
    //Set Tx data to select core data
    DS.txRegs.settxdatasel(0x0).Write2DUT(2);
}
//==============================================================================
// Function: EnableRxPrbsCheck
// - Function of enable Rx PRBS checker
//==============================================================================

void EnableRxPrbsCheck(STRING sPRBSPatternType) {
    // Select Rx PRBS pattern
    if (sPRBSPatternType == "PRBS7") {
        DS.rxRegs.setprbschkpatsel(0x0).Write2DUT(16);
    } else if (sPRBSPatternType == "PRBS9") {
        DS.rxRegs.setprbschkpatsel(0x1).Write2DUT(16);
    } else if (sPRBSPatternType == "PRBS10") {
        DS.rxRegs.setprbschkpatsel(0x2).Write2DUT(16);
    } else if (sPRBSPatternType == "PRBS11") {
        DS.rxRegs.setprbschkpatsel(0x3).Write2DUT(16);
    } else if (sPRBSPatternType == "PRBS15") {
        DS.rxRegs.setprbschkpatsel(0x4).Write2DUT(16);
    } else if (sPRBSPatternType == "PRBS20") {
        DS.rxRegs.setprbschkpatsel(0x5).Write2DUT(16);
    } else if (sPRBSPatternType == "PRBS23") {
        DS.rxRegs.setprbschkpatsel(0x6).Write2DUT(16);
    } else if (sPRBSPatternType == "PRBS31") {
        DS.rxRegs.setprbschkpatsel(0x7).Write2DUT(16);
    } else if (sPRBSPatternType == "CUSTOMER_PATTERN") {
        DS.rxRegs.setprbschkpatsel(0x8).Write2DUT(16);
    } else {
        DS.rxRegs.setprbschkpatsel(0x0).Write2DUT(16);
    }

    //Select Rx PRBS check mode, 0 is synchronous mode and 1 is free running mode
    //normally the PRBS checker should be set in synchronous mode, once the PRBS check
    //is synchronized, it can be switched to free running mode to have more accurate error count
    DS.rxRegs.setprbschkmode(0x0).Write2DUT(16);
    //Enable PRBS checker
    DS.rxRegs.setprbschken(0x1).Write2DUT(16);
}

void LoopBack_Setting(string& sLoopBackMode, MACRO_LANE_SEL &MacroLane_Sel, CUSTPARA& CUSTpara) {
    DSAPI DSApi;
    if (sLoopBackMode == "PreDriver") {
        DSApi = default_DSAPI[5];
        EnableTxToRxSerLpbk(MacroLane_Sel, sLoopBackMode, CUSTpara, DSApi);
    } else if (sLoopBackMode == "Bump") {
        DSApi = default_DSAPI[4];
        EnableTxToRxSerLpbk(MacroLane_Sel, sLoopBackMode, CUSTpara, DSApi);
    } else if (sLoopBackMode == "External") {
        DSApi = default_DSAPI[2];
        DisableTxToRxSerLpbk(MacroLane_Sel, CUSTpara, DSApi);
    } else {
        DSApi = default_DSAPI[2];
        DisableTxToRxSerLpbk(MacroLane_Sel, CUSTpara, DSApi);
    }
}

//==============================================================================
// Function: SetTxBistPpmJitter
// - This function is used to set PPM and jitter for Abist test.
//==============================================================================

void SetTxBistPpmJitter(Stress_Setting& Stress_Set) {
    //	hout(DETAIL)<<"jitcontrol:"<<Stress_Set.jitcontrol<<"\t jitFreq"<<Stress_Set.jitFreq<<"\t jitamp"<<Stress_Set.jitamp<<"\t ppmgen"<<Stress_Set.ppmgen<<endl;

    DS.txRegs.settxalignmode(3).Write2DUT(2);
    DS.txRegs.setjitppmctrl(Stress_Set.jitcontrol)
            .setjitfreq(Stress_Set.jitFreq)
            .setjitamp(Stress_Set.jitamp)
            .setppmgen(Stress_Set.ppmgen)
            .Write2DUT(3);
    DS.txRegs.settxrstb(0).Write2DUT(2);
    DS.txRegs.settxrstb(1).Write2DUT(2);
    DS.txRegs.settxalignmode(4).Write2DUT(2);
}

//Jitter

int FreqOffset(DOUBLE& FreqOffsetRequired, INT JitControl) {
    INT iDebugAnalog;
    //	GET_TESTFLOW_FLAG("debug_analog",&iDebugAnalog);

    /*	The MSB (i.e., PPMGEN[4]) defines the slew rate direction. Remaining bits,
     *	i.e., PPMGEN[3:0] define the number of words (normal/extended):
     *			0000 = steady state/steady state 1000 = steady state/12 words
     *			0001 = 2/2 words 		         1001 = steady state/16 words
     *			0010 = 3/3 words 				 1010 = steady state/20 words
     *			0011 = 4/4 words 				 1011 = steady state/24 words
     *			0100 = 6/5 words 		         1100 = steady state/32 words
     *			0101 = 8/6 words 		         1101 = steady state/40 words
     *			0110 = 12/8 words 		         1110 = steady state/48 words
     *			0111 = 16/10 words 		         1111 = steady state/64 words
     *	FrequencyOffset = 1000000 / (UIsize * WORDWIDTH * PPMGEN)*/


    typedef map <int, int>::value_type valType;

    map <int, int> mapPPM;
    UINT Index;
    //Normal Mode
    if (JitControl == 0) {
        Index = 7;
        mapPPM.insert(valType(0, 0));
        mapPPM.insert(valType(1, 2)); //390
        mapPPM.insert(valType(2, 3)); //260
        mapPPM.insert(valType(3, 4)); //195
        mapPPM.insert(valType(4, 6)); //130
        mapPPM.insert(valType(5, 8)); //97
        mapPPM.insert(valType(6, 12)); //65
        mapPPM.insert(valType(7, 16)); //48
    }        // Extended Mode
    else if (JitControl == 1) {
        Index = 15;
        mapPPM.insert(valType(0, 0));
        mapPPM.insert(valType(1, 2));
        mapPPM.insert(valType(2, 3));
        mapPPM.insert(valType(3, 4));
        mapPPM.insert(valType(4, 5));
        mapPPM.insert(valType(5, 6));
        mapPPM.insert(valType(6, 8));
        mapPPM.insert(valType(7, 10));
        mapPPM.insert(valType(8, 12));
        mapPPM.insert(valType(9, 16));
        mapPPM.insert(valType(10, 20));
        mapPPM.insert(valType(11, 24));
        mapPPM.insert(valType(12, 32));
        mapPPM.insert(valType(13, 40));
        mapPPM.insert(valType(14, 48));
        mapPPM.insert(valType(15, 64));
    }
    /***********GUI CODE BEGIN***********/
    DOUBLE UIsize = 32;
    DOUBLE EffectiveBusWidth = 40;


    /***********GUI CODE END***********/

    DOUBLE FreqOffset;
    map <int, int>::iterator it;


    do {
        Index--;
        it = mapPPM.find(Index);
        if (it != mapPPM.begin()) {
            FreqOffset = 1000000.0 / (UIsize * EffectiveBusWidth * it -> second);
        }
    } while (FreqOffset < FreqOffsetRequired && Index < (mapPPM.size() - 1));

    hout(DETAIL) << " PPMGEN_IDX = " << Index << ": FREQOFFSET = " << FreqOffset << " [PPM]" << endl;

    return Index;
}

struct JI JitterInjection(DOUBLE& DataRate, DOUBLE& JitterAmpRequired, INT JitControl) {
    INT iDebugAnalog;
    //	GET_TESTFLOW_FLAG("debug_analog",&iDebugAnalog);

    /********Find JitterAmp************/
    /*	Select jitter amplitude (normal/extended).
     *
     *  0000 = 12/3 times 	1000 = 12/20 times
     *  0001 = 16/4 times 	1001 = 12/24 times
     *  0010 = 24/5 times 	1010 = 12/32 times
     *  0011 = 32/6 times 	1011 = 12/40 times
     *  0100 = 48/8 times 	1100 = 12/48 times
     *  0101 = 64/10 times 	1101 = 12/64 times
     *  0110 = 96/12 times 	1110 = 12/80 times
     *  0111 = 128/16 times 1111 = 12/96 times
     *
     *  The number is 2X in 1/2-rate and 4X at 1/4-rate and 8X at 1/8 rate */

    typedef map <int, double>::value_type valType;

    /***********GUI CODE BEGIN***********/
    DOUBLE UIsize = 32.0;
    DOUBLE EffectiveBusWidth = 40;


    map <int, double> mapJITAMP;
    //Extended Mode
    if (JitControl == 1) {
        mapJITAMP.insert(valType(0, 3));
        mapJITAMP.insert(valType(1, 4));
        mapJITAMP.insert(valType(2, 5));
        mapJITAMP.insert(valType(3, 6));
        mapJITAMP.insert(valType(4, 8));
        mapJITAMP.insert(valType(5, 10));
        mapJITAMP.insert(valType(6, 12));
        mapJITAMP.insert(valType(7, 16));
        mapJITAMP.insert(valType(8, 20));
        mapJITAMP.insert(valType(9, 24));
        mapJITAMP.insert(valType(10, 32));
        mapJITAMP.insert(valType(11, 40));
        mapJITAMP.insert(valType(12, 48));
        mapJITAMP.insert(valType(13, 64));
        mapJITAMP.insert(valType(14, 80));
        mapJITAMP.insert(valType(15, 96));
    }        //Normal Mode
    else if (JitControl == 0) {
        mapJITAMP.insert(valType(0, 12));
        mapJITAMP.insert(valType(1, 16));
        mapJITAMP.insert(valType(2, 24));
        mapJITAMP.insert(valType(3, 32));
        mapJITAMP.insert(valType(4, 48));
        mapJITAMP.insert(valType(5, 64));
        mapJITAMP.insert(valType(6, 96));
        mapJITAMP.insert(valType(7, 128));
    }

    /***********GUI CODE END***********/
    DOUBLE JitterAmp;
    map <int, double>::iterator itAmp;
    UINT AmpIndex = -1;

    do {
        AmpIndex++;
        itAmp = mapJITAMP.find(AmpIndex);
        if (itAmp != mapJITAMP.end()) {
            JitterAmp = itAmp -> second / UIsize;
        }
    } while (JitterAmp < JitterAmpRequired && AmpIndex < (mapJITAMP.size() - 1));

    hout(DETAIL) << " JITAMP = " << AmpIndex << ": JitterAmp = " << JitterAmp << " [UI]" << endl;

    /********Find JitterFrequency************/
    DOUBLE JITAMP = itAmp -> second;
    DOUBLE UIps = 1000 / DataRate;
    //DOUBLE Kfactor = (UIsize - JITAMP) / UIsize;
    DOUBLE Kfactor = 0;
    /*	Select jitter frequency (normal/extended):
     *
     *  000 = infinite words (doesn't move)/1 word
     *  001 = 2/2 words
     *  010 = 3/3 words
     *  011 = 4/4 words
     *  100 = 6/5 words
     *  101 = 8/6 words
     *  110 = 12/7 words
     *  111 = 16/8 words
     */

    map <int, int> mapJITFREQ;
    if (JitControl == 1) {
        mapJITFREQ.insert(valType(0, 1));
        mapJITFREQ.insert(valType(1, 2));
        mapJITFREQ.insert(valType(2, 3));
        mapJITFREQ.insert(valType(3, 4));
        mapJITFREQ.insert(valType(4, 5));
        mapJITFREQ.insert(valType(5, 6));
        mapJITFREQ.insert(valType(6, 7));
        mapJITFREQ.insert(valType(7, 8));
    } else if (JitControl == 0) {
        mapJITFREQ.insert(valType(0, 0));
        mapJITFREQ.insert(valType(1, 2));
        mapJITFREQ.insert(valType(2, 3));
        mapJITFREQ.insert(valType(3, 4));
        mapJITFREQ.insert(valType(4, 6));
        mapJITFREQ.insert(valType(5, 8));
        mapJITFREQ.insert(valType(6, 12));
        mapJITFREQ.insert(valType(7, 16));
    }
    DOUBLE JitterFrequency;
    map <int, int>::iterator itFreq;
    INT FreqIndex = 0;
    DOUBLE Diff = 0;

    struct JITFREQ {
        INT Findex;
        DOUBLE JFreq;
    };

    struct JITFREQ MinDiffFreq = {0, 200.0}; /**first element is FreqIndex, second is Diff between JitterFrequency and JitterFrequencyrequared**/

    while (FreqIndex <= 7) {
        itFreq = mapJITFREQ.find(FreqIndex);
        if (itFreq != mapJITFREQ.end()) {
            JitterFrequency = 1000000 / (2 * (JITAMP + Kfactor) * itFreq -> second * EffectiveBusWidth * UIps); /**MHz**/

            //Diff = abs(JitterFrequency - 1000 * DataRate / 1300); /**MHz**/
            Diff = JitterFrequency - 1000 * DataRate / 1300; /**MHz**/ // SongXin: ABIST use 1300, ATE use 1667, according to ZhangRui's request.
            if ((Diff < MinDiffFreq.JFreq) && (Diff >= 0)) {
                MinDiffFreq.JFreq = Diff;
                MinDiffFreq.Findex = itFreq -> first;
            }
        }
        FreqIndex++;
    }

    struct JI JitterInjection = {AmpIndex, MinDiffFreq.Findex};
    return JitterInjection;
}

//set ctle

void InitCtlePerMacroPerLane(MACRO_LANE_SEL& vMacroLane_Sel) {
    //initial
    d2s_JTAG& jtag = d2s_JTAG::Instance();
    CtleResultPerLane tmp;
    tmp.uiCTLEACTGN1 = 0;
    tmp.uiCTLEACTGN2 = 0;
    tmp.uiCTLEACTGN3 = 0;
    tmp.uiCTLEBST1 = 0;
    tmp.uiCTLEBST2 = 0;
    tmp.uiCTLEBST3 = 0;
    tmp.uiCTLESQH1 = 0;
    tmp.uiCTLESQH2 = 0;
    tmp.uiCTLESQH3 = 0;
    tmp.uiCTLEZA1 = 0;
    tmp.uiCTLEZA2 = 0;
    tmp.uiCTLEZA3 = 0;
    tmp.uiCTLERMBAND1 = 0;
    tmp.uiCTLERMBAND2 = 0;
    tmp.uiCTLERMBAND3 = 0;
    tmp.uiCTLECMBAND1 = 0;
    tmp.uiCTLECMBAND2 = 0;
    tmp.uiCTLECMBAND3 = 0;
    tmp.uiCTLEHFZEN1 = 0;
    tmp.uiCTLEHFZEN2 = 0;
    tmp.uiCTLEHFZEN3 = 0;
    tmp.uiCTLEREFSEL = 0;

    DFEResultPerLane DFEtmp;
    DFEtmp.uiDFEFXTAP2 = 0;
    DFEtmp.uiDFEFXTAP3 = 0;
    DFEtmp.uiDFEFXTAP4 = 0;
    DFEtmp.uiDFEFXTAP5 = 0;
    DFEtmp.uiDFEFXTAP6 = 0;
    DFEtmp.uiDFEFXTAP7 = 0;
    DFEtmp.uiDFEFXTAP8 = 0;
    DFEtmp.uiDFEFXTAP9 = 0;
    DFEtmp.uiDFEMVTAP1 = 0;
    DFEtmp.uiDFEMVTAP2 = 0;
    DFEtmp.uiDFEMVTAP3 = 0;
    DFEtmp.uiDFEMVTAP4 = 0;
    DFEtmp.uiDFEMVTAP5 = 0;
    DFEtmp.uiDFEMVTAP6 = 0;
    DFEtmp.uiDFEFXTAP1CEN = 0;
    DFEtmp.uiDFEFXTAP1EDG = 0;

    LANE_CTLE CTLE_Readback;

    for (UINT iMacroIndex = 0; iMacroIndex < vMacroLane_Sel.size(); iMacroIndex++) {
        vector <CtleResultPerLane> tmparray;
        vector <DFEResultPerLane> DFEtmparray;
        UINT MacroID = vMacroLane_Sel[iMacroIndex].MacroID;
        for (UINT iLaneIndex = 0; iLaneIndex < HILINK_INFO[MacroID].Lane_Num; iLaneIndex++) {
            tmparray.push_back(tmp);
            DFEtmparray.push_back(DFEtmp);
        }
        vCtleResultPerMacroPerLane.push_back(tmparray);
        vDfeResultPerMacroPerLane.push_back(DFEtmparray);
    }


    d2s::d2s_LABEL_BEGIN("MPB_H30_Adaptaion_CTLE_Read_", Global_D2S_Mode);
    for (UINT macroIndex = 0; macroIndex < vMacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = vMacroLane_Sel[macroIndex].MacroID;
        const vector<UINT>& vLane = vMacroLane_Sel[macroIndex].vLane;
        selectMacro(MacroID);
        for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
            UINT LaneID = vLane[laneIndex];
            DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
            DS.txRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0); //Ares Add
            ostringstream id1, id2, id3, id44, id6, id7, id8, id9, id10, id11, id51, id36;
            id1 << "M" << MacroID << "_L" << LaneID << "_CSR1_" << jtag.Context;
            DS.rxRegs.Read2IDString(1, id1.str());
            id2 << "M" << MacroID << "_L" << LaneID << "_CSR2_" << jtag.Context;
            DS.rxRegs.Read2IDString(2, id2.str());
            id3 << "M" << MacroID << "_L" << LaneID << "_CSR3_" << jtag.Context;
            DS.rxRegs.Read2IDString(3, id3.str());
            id44 << "M" << MacroID << "_L" << LaneID << "_CSR44_" << jtag.Context;
            DS.rxRegs.Read2IDString(44, id44.str());

            id6 << "M" << MacroID << "_L" << LaneID << "_CSR6_" << jtag.Context;
            DS.rxRegs.Read2IDString(6, id6.str());

            id7 << "M" << MacroID << "_L" << LaneID << "_CSR7_" << jtag.Context;
            DS.rxRegs.Read2IDString(7, id7.str());

            id8 << "M" << MacroID << "_L" << LaneID << "_CSR8_" << jtag.Context;
            DS.rxRegs.Read2IDString(8, id8.str());

            id9 << "M" << MacroID << "_L" << LaneID << "_CSR9_" << jtag.Context;
            DS.rxRegs.Read2IDString(9, id9.str());

            id10 << "M" << MacroID << "_L" << LaneID << "_CSR10_" << jtag.Context;
            DS.rxRegs.Read2IDString(10, id10.str());

            id11 << "M" << MacroID << "_L" << LaneID << "_CSR11_" << jtag.Context;
            DS.rxRegs.Read2IDString(11, id11.str());

            id51 << "M" << MacroID << "_L" << LaneID << "_CSR51_" << jtag.Context;
            DS.rxRegs.Read2IDString(51, id51.str());

            id36 << "M" << MacroID << "_L" << LaneID << "_CSR36_" << jtag.Context;
            DS.txRegs.Read2IDString(36, id36.str());


        }
    }
    d2s::d2s_LABEL_END();
    hout(DETAIL) << "=====================CTLE Adapt Result========================" << endl;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
        for (UINT macroIndex = 0; macroIndex < vMacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = vMacroLane_Sel[macroIndex].MacroID;

            for (UINT laneIndex = 0; laneIndex < (vMacroLane_Sel[macroIndex].vLane).size(); laneIndex++) {
                UINT LaneID = (vMacroLane_Sel[macroIndex].vLane)[laneIndex];
                hout(DETAIL) << "MacroID = " << MacroID << " LaneID = " << LaneID << endl;
                DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
                ostringstream id1, id2, id3, id44, id6, id7, id8, id9, id10, id11, id51;
                id1 << "M" << MacroID << "_L" << LaneID << "_CSR1_" << jtag.Context;
                DS.rxRegs.csr[1] = jtag.getReadValue(id1.str())[SiteID];

                id2 << "M" << MacroID << "_L" << LaneID << "_CSR2_" << jtag.Context;
                DS.rxRegs.csr[2] = jtag.getReadValue(id2.str())[SiteID];

                id3 << "M" << MacroID << "_L" << LaneID << "_CSR3_" << jtag.Context;
                DS.rxRegs.csr[3] = jtag.getReadValue(id3.str())[SiteID];

                id44 << "M" << MacroID << "_L" << LaneID << "_CSR44_" << jtag.Context;
                DS.rxRegs.csr[44] = jtag.getReadValue(id44.str())[SiteID];
                id6 << "M" << MacroID << "_L" << LaneID << "_CSR6_" << jtag.Context;
                DS.rxRegs.csr[6] = jtag.getReadValue(id6.str())[SiteID];

                id7 << "M" << MacroID << "_L" << LaneID << "_CSR7_" << jtag.Context;
                DS.rxRegs.csr[7] = jtag.getReadValue(id7.str())[SiteID];

                id8 << "M" << MacroID << "_L" << LaneID << "_CSR8_" << jtag.Context;
                DS.rxRegs.csr[8] = jtag.getReadValue(id8.str())[SiteID];

                id9 << "M" << MacroID << "_L" << LaneID << "_CSR9_" << jtag.Context;
                DS.rxRegs.csr[9] = jtag.getReadValue(id9.str())[SiteID];

                id10 << "M" << MacroID << "_L" << LaneID << "_CSR10_" << jtag.Context;
                DS.rxRegs.csr[10] = jtag.getReadValue(id10.str())[SiteID];

                id11 << "M" << MacroID << "_L" << LaneID << "_CSR11_" << jtag.Context;
                DS.rxRegs.csr[11] = jtag.getReadValue(id11.str())[SiteID];

                id51 << "M" << MacroID << "_L" << LaneID << "_CSR51_" << jtag.Context;
                DS.rxRegs.csr[51] = jtag.getReadValue(id51.str())[SiteID];
                //-----------------------GET CTLE RESULT------------------------------//
                CTLE_Readback[SiteID][MacroID][LaneID].CTLEACTGN1 = DS.rxRegs.getctleactgn1();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLEACTGN2 = DS.rxRegs.getctleactgn2();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLEACTGN3 = DS.rxRegs.getctleactgn3();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLEBST1 = DS.rxRegs.getctleboostc1();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLEBST2 = DS.rxRegs.getctleboostc2();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLEBST3 = DS.rxRegs.getctleboostc3();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLESQH1 = DS.rxRegs.getctlesqh1();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLESQH2 = DS.rxRegs.getctlesqh2();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLESQH3 = DS.rxRegs.getctlesqh2();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLEZA1 = DS.rxRegs.getctleza1();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLEZA2 = DS.rxRegs.getctleza2();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLEZA3 = DS.rxRegs.getctleza3();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLERMBAND1 = DS.rxRegs.getctlermband1();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLERMBAND2 = DS.rxRegs.getctlermband2();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLERMBAND3 = DS.rxRegs.getctlermband3();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLECMBAND1 = DS.rxRegs.getctlecmband1();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLECMBAND2 = DS.rxRegs.getctlecmband2();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLECMBAND3 = DS.rxRegs.getctlecmband3();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLEHFZEN1 = DS.rxRegs.getctlehfzen1();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLEHFZEN2 = DS.rxRegs.getctlehfzen2();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLEHFZEN3 = DS.rxRegs.getctlehfzen3();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLEREFSEL = DS.rxRegs.getctlerefsel();
                CTLE_Readback[SiteID][MacroID][LaneID].CPHSOFFT = DS.rxRegs.getcphsofst();
                CTLE_Readback[SiteID][MacroID][LaneID].CTLEloadsel = DS.rxRegs.getctleloadsel();

                hout(DETAIL) << endl;
                hout(DETAIL) << "MacroID:  " << MacroID << "    LaneID:  " << LaneID << endl;
                hout(DETAIL) << "CTLEACTGN1:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLEACTGN1 << endl;
                hout(DETAIL) << "CTLEACTGN2:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLEACTGN2 << endl;
                hout(DETAIL) << "CTLEACTGN3:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLEACTGN3 << endl;
                hout(DETAIL) << "CTLEBST1:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLEBST1 << endl;
                hout(DETAIL) << "CTLEBST2:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLEBST2 << endl;
                hout(DETAIL) << "CTLEBST3:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLEBST3 << endl;
                hout(DETAIL) << "CTLESQH1:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLESQH1 << endl;
                hout(DETAIL) << "CTLESQH2:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLESQH2 << endl;
                hout(DETAIL) << "CTLESQH3:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLESQH3 << endl;
                hout(DETAIL) << "CTLEZA1:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLEZA1 << endl;
                hout(DETAIL) << "CTLEZA2:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLEZA2 << endl;
                hout(DETAIL) << "CTLEZA3:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLEZA3 << endl;
                hout(DETAIL) << "CTLERMBAND1:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLERMBAND1 << endl;
                hout(DETAIL) << "CTLERMBAND2:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLERMBAND2 << endl;
                hout(DETAIL) << "CTLERMBAND3:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLERMBAND3 << endl;
                hout(DETAIL) << "CTLECMBAND1:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLECMBAND1 << endl;
                hout(DETAIL) << "CTLECMBAND2:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLECMBAND2 << endl;
                hout(DETAIL) << "CTLECMBAND3:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLECMBAND3 << endl;
                hout(DETAIL) << "CTLEHFZEN1:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLEHFZEN1 << endl;
                hout(DETAIL) << "CTLEHFZEN2:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLEHFZEN2 << endl;
                hout(DETAIL) << "CTLEHFZEN3:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLEHFZEN3 << endl;
                hout(DETAIL) << "CTLEREFSEL:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLEREFSEL << endl;
                hout(DETAIL) << "CPHSOFFT:" << CTLE_Readback[SiteID][MacroID][LaneID].CPHSOFFT << endl;
                hout(DETAIL) << "CTLEloadsel:" << CTLE_Readback[SiteID][MacroID][LaneID].CTLEloadsel << endl;
                hout(DETAIL) << "CSR6: " << dec << DS.rxRegs.csr[6] << endl;
                hout(DETAIL) << "CSR7: " << dec << DS.rxRegs.csr[7] << endl;
                hout(DETAIL) << "CSR8: " << dec << DS.rxRegs.csr[8] << endl;
                hout(DETAIL) << "CSR9: " << dec << DS.rxRegs.csr[9] << endl;
                hout(DETAIL) << "CSR10: " << dec << DS.rxRegs.csr[10] << endl;
                hout(DETAIL) << "CSR11: " << dec << DS.rxRegs.csr[11] << endl;
                hout(DETAIL) << "CSR51: " << dec << DS.rxRegs.csr[51] << endl;

                hout(DETAIL) << "txrxserlpbkgn1: " << dec << DS.txRegs.gettxrxserlpbkgn1() << endl;
                hout(DETAIL) << "txrxserlpbkgn2: " << dec << DS.txRegs.gettxrxserlpbkgn2() << endl;
                hout(DETAIL) << "txrxserlpbkgn3: " << dec << DS.txRegs.gettxrxserlpbkgn3() << endl;
            }
        }
        FOREACH_ACTIVESITE_END
}

INT sigdet_los_check(const MACRO_LANE_SEL& MacroLane_Sel, LANE_DOUBLE& Sigdet_LOS, STRING sTestMode, const STRING sCheckMode) {
    INT read_cont = 10;
    int allMacroPass;
    d2s_JTAG& jtag = d2s_JTAG::Instance();
    Sigdet_LOS.init(999);

    string sPortName = "";
    if (sTestMode == "ATE") {
        sPortName = "pUDIRXDATA";
    } else {
        sPortName = "pHilink_LS";
    }
    //	D2S_FRAMEWORK;
    //GET_TEST_INFO;
    TransactionPort pRX(sPortName);
    //	fr.registerTransactionPort(pRX);



#ifndef TestChip
    //	FW_TASK("DCRT RAM,(pJTAG)");
#else
    FW_TASK("DCRT RAM,(pAHB)");
#endif
    if (sCheckMode == "ALL0_CHECK") {
        allMacroPass = 0;
        //ALL 0 CHECK
        //		sprintf(label,"SIGDET_LOS_ALL0_%f_%f_",Vcoef,Temp);
        //		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));   sigdet_los_check
        d2s::d2s_LABEL_BEGIN("SIGDET_LOS_ALL0_", Global_D2S_Mode);
        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
            for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
                UINT LaneID = vLane[laneIndex];

                jtag.enablePassFailCheckForNextExecution();
                if (sTestMode == "ATE") {
                    pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL_PRBS15, ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE_PRBS15);
                }
                selectMacro(MacroID);
                DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
                for (INT read_index = 0; read_index < read_cont; read_index++) {
                    //					DS.rxRegs.ExpectValue(40, 0x0000, 0xBFFF); //
                    DS.rxRegs.ExpectValue(40, 0x0000, 0x4000); //
                }
            }
        }
        //		fr.d2s_LABEL_END();
        d2s::d2s_LABEL_END();
        //		FOR_EACH_SITE_BEGIN();
        map<uint32_t, bool> map_pass_fail_result = TheInst.Digital().PatEng().GetPassFail();

//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int site = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

//            bool size_pass = map_pass_fail_result[SiteID];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
            bool size_pass = map_pass_fail_result[SiteID];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
    		if(PrintDebugEn) cout<<"map_pass_fail_result["<<SiteID<<"] = "<<map_pass_fail_result[SiteID]<<endl;

            //			int SiteID = CURRENT_SiteID_NUMBER()-1;
            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
                const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
                for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
                    UINT LaneID = vLane[laneIndex];
                    //					if (jtag.hasPassed(label))
                    if (size_pass) {
                        Sigdet_LOS[SiteID][MacroID][LaneID] = 0;
                        allMacroPass = 1;
                    } else {
                        Sigdet_LOS[SiteID][MacroID][LaneID] = 1;
                    }
                }
            }
            FOREACH_ACTIVESITE_END

        if ((allMacroPass == 0) || (Global_D2S_Mode == 0)) {
            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
                const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
                for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
                    UINT LaneID = vLane[laneIndex];

                    //ALL 0 CHECK
                    //					sprintf(label,"SIGDET_LOS_ALL0_%f_%f_",Vcoef,Temp);
                    //					fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
                    d2s::d2s_LABEL_BEGIN("SIGDET_LOS_ALL0_", Global_D2S_Mode);
                    jtag.enablePassFailCheckForNextExecution();
                    if (sTestMode == "ATE") {
                        pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL_PRBS15, ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE_PRBS15);
                    }
                    selectMacro(MacroID);
                    DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
                    for (INT read_index = 0; read_index < read_cont; read_index++) {
                        //						DS.rxRegs.ExpectValue(40, 0x0000, 0xBFFF); //
                        DS.rxRegs.ExpectValue(40, 0x0000, 0x4000); //
                    }
                    //					fr.d2s_LABEL_END();
                    d2s::d2s_LABEL_END();
                    //					FOR_EACH_SITE_BEGIN();
                    //						int site = CURRENT_SITE_NUMBER()-1;
                    map<uint32_t, bool> map_pass_fail_result = TheInst.Digital().PatEng().GetPassFail();

//                    FOREACH_ACTIVE_SITE(api) {
//                        unsigned int site = api->Get_active_site();
                        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//                        bool size_pass = map_pass_fail_result[site];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
                        bool size_pass = map_pass_fail_result[SiteID];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
                		if(PrintDebugEn) cout<<"map_pass_fail_result["<<SiteID<<"] = "<<map_pass_fail_result[SiteID]<<endl;
                        //						if (jtag.hasPassed(label))
                        if (size_pass) {
                            Sigdet_LOS[SiteID][MacroID][LaneID] = 0;
                        } else {
                            Sigdet_LOS[SiteID][MacroID][LaneID] = 1;
                        }
                        FOREACH_ACTIVESITE_END
                }
            }
        }
    }

    if (sCheckMode == "ALL1_CHECK") {

        allMacroPass = 0;

        //ALL 0 CHECK
        //		sprintf(label,"SIGDET_LOS_ALL1_%f_%f_",Vcoef,Temp);
        //		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
        d2s::d2s_LABEL_BEGIN("SIGDET_LOS_ALL1_", Global_D2S_Mode);
        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
            for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
                UINT LaneID = vLane[laneIndex];
                jtag.enablePassFailCheckForNextExecution();
                if (sTestMode == "ATE") {
                    pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL_PRBS15, ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE_PRBS15);
                }
                selectMacro(MacroID);
                DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
                for (INT read_index = 0; read_index < read_cont; read_index++) {
                    //					DS.rxRegs.ExpectValue(40, 1<<14, 0xBFFF); //
                    DS.rxRegs.ExpectValue(40, 1 << 14, 0x4000);
                }

            }
        }
        //		fr.d2s_LABEL_END();
        d2s::d2s_LABEL_END();



        //		FOR_EACH_SITE_BEGIN();
        //			int site = CURRENT_SITE_NUMBER()-1;

        map<uint32_t, bool> map_pass_fail_result = TheInst.Digital().PatEng().GetPassFail();
//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int site = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//            bool size_pass = map_pass_fail_result[site];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
            bool size_pass = map_pass_fail_result[SiteID];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
    		if(PrintDebugEn) cout<<"map_pass_fail_result["<<SiteID<<"] = "<<map_pass_fail_result[SiteID]<<endl;
            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
                const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
                for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
                    UINT LaneID = vLane[laneIndex];
                    //                                            if (jtag.hasPassed(label))
                    if (size_pass) {
                        Sigdet_LOS[SiteID][MacroID][LaneID] = 1;
                        allMacroPass = 1;
                    } else {
                        Sigdet_LOS[SiteID][MacroID][LaneID] = 0;
                    }
                }
            }
            FOREACH_ACTIVESITE_END

        if ((allMacroPass == 0) || (Global_D2S_Mode == 0)) {
            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
                const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
                for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
                    UINT LaneID = vLane[laneIndex];

                    //ALL 0 CHECK
                    //					sprintf(label,"SIGDET_LOS_ALL1_%f_%f_",Vcoef,Temp);
                    //					fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
                    d2s::d2s_LABEL_BEGIN("SIGDET_LOS_ALL1_", Global_D2S_Mode);
                    jtag.enablePassFailCheckForNextExecution();
                    if (sTestMode == "ATE") {
                        pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL_PRBS15, ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE_PRBS15);
                    }
                    selectMacro(MacroID);
                    DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
                    for (INT read_index = 0; read_index < read_cont; read_index++) {
                        //						DS.rxRegs.ExpectValue(40, 1<<14, 0xBFFF); //
                        DS.rxRegs.ExpectValue(40, 1 << 14, 0x4000); //
                    }
                    //					fr.d2s_LABEL_END();
                    d2s::d2s_LABEL_END();
                    //					FOR_EACH_SITE_BEGIN();
                    //						int site = CURRENT_SITE_NUMBER()-1;

//                    FOREACH_ACTIVE_SITE(api) {
//                        unsigned int site = api->Get_active_site();
                    map<uint32_t, bool> map_pass_fail_result = TheInst.Digital().PatEng().GetPassFail();
                        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

//                        bool size_pass = map_pass_fail_result[site];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
                        bool size_pass = map_pass_fail_result[SiteID];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
                		if(PrintDebugEn) cout<<"map_pass_fail_result["<<SiteID<<"] = "<<map_pass_fail_result[SiteID]<<endl;
                        //                                                if (jtag.hasPassed(label))
                        if (size_pass) {
                            Sigdet_LOS[SiteID][MacroID][LaneID] = 1;
                        } else {
                            Sigdet_LOS[SiteID][MacroID][LaneID] = 0;
                        }
                        FOREACH_ACTIVESITE_END
                }
            }
        }
    }


    //	if(TestChip==0) FW_TASK("DCRT TP,(pJTAG)");
    //   else if(TestChip==1) FW_TASK("DCRT TP,(pAHB)");
#ifndef TestChip
    //	FW_TASK("DCRT TP,(pJTAG)");
#else
    FW_TASK("DCRT TP,(pAHB)");
#endif
    return 0;
}

INT sigdet_los_check(const MACRO_LANE_SEL& vMacroLane_Sel, vector<ARRAY_D>& vSigdet_LOS_ALL1, vector<ARRAY_D>& vSigdet_LOS_ALL0, string sTestMode) {
    INT iDebugAnalog;
    INT read_cont = 100;
    //  GET_TESTFLOW_FLAG("debug_analog",&iDebugAnalog);

    for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
        const vector<UINT>& vLane = vMacroLane_Sel[uiMacroIndex].vLane;
        ARRAY_D tmp;
        tmp.resize(vLane.size());
        //    tmp.init(999);
        vSigdet_LOS_ALL1.push_back(tmp);
        vSigdet_LOS_ALL0.push_back(tmp);
    }

    /**************TTR**************/

    //  D2S_FRAMEWORK;
    //GET_TEST_INFO;
    string sPortName = "";
    if (sTestMode == "ATE") {
        sPortName = "pUDIRXDATA";
    } else {
        sPortName = "pHilink_LS";
    }
    TransactionPort pRX(sPortName);
    //  fr.registerTransactionPort(pRX);


#ifdef TestChip
    FW_TASK("DCRT RAM,(pAHB)");
#else
    //	  FW_TASK("DCRT RAM,(pJTAG)");
#endif


    for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
        UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
        const vector<UINT>& vLane = vMacroLane_Sel[uiMacroIndex].vLane;

        for (UINT uiLaneIndex = 0; uiLaneIndex < vLane.size(); uiLaneIndex++) {
            UINT LaneID = vLane[uiLaneIndex];
            INT sigdet_los_all0 = 0;
            INT sigdet_los_all1 = 0;

            if (vSigdet_LOS_ALL0[uiMacroIndex][uiLaneIndex] != 0) {
                //    	sprintf(label,"MPB_H30_SIGDET_LOS_ALL0_%f_%f_",Vcoef,Temp);
                //        fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
                d2s::d2s_LABEL_BEGIN("MPB_H30_SIGDET_LOS_ALL0_", Global_D2S_Mode);
                if (sTestMode == "ATE") {
                    pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL_PRBS15, ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE_PRBS15);
                }

                //        jtag.enablePassFailCheckForNextExecution();

                selectMacro(MacroID);

                DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
                for (INT read_index = 0; read_index < read_cont; read_index++) {
                    //          DS.rxRegs.ExpectValue(40, 0, 0xbfff); // getrxsigdetlos() { return (uint)((csr[3] & 0x0800) >> 11); }
                    DS.rxRegs.ExpectValue(40, 0, 0x4000); // getrxsigdetlos() { return (uint)((csr[3] & 0x0800) >> 11); }
                }

                //        fr.d2s_LABEL_END();
                d2s::d2s_LABEL_END();
                //        if (jtag.hasPassed(label))
                //        {
                //          vSigdet_LOS_ALL0[uiMacroIndex][uiLaneIndex] = 1;
                //          sigdet_los_all0 = 1;
                //        }
                //        else
                //        {
                //          vSigdet_LOS_ALL0[uiMacroIndex][uiLaneIndex] = 0;
                //          sigdet_los_all0 = 0;
                //        }
            }
            if ((vSigdet_LOS_ALL0[uiMacroIndex][uiLaneIndex] == 0) && (vSigdet_LOS_ALL1[uiMacroIndex][uiLaneIndex] != 1)) {
                //    	  sprintf(label,"MPB_H30_SIGDET_LOS_ALL1_%f_%f_",Vcoef,Temp);
                //    	  fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
                d2s::d2s_LABEL_BEGIN("MPB_H30_SIGDET_LOS_ALL1_", Global_D2S_Mode);
                if (sTestMode == "ATE") {
                    pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL_PRBS15, ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE_PRBS15);
                }

                //        jtag.enablePassFailCheckForNextExecution();

                selectMacro(MacroID);

                DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
                for (INT read_index = 0; read_index < read_cont; read_index++) {
                    //            DS.rxRegs.ExpectValue(40, 1<<14, 0xbfff); // getrxsigdetlos() { return (uint)((csr[3] & 0x0800) >> 11); }
                    DS.rxRegs.ExpectValue(40, 1 << 14, 0x4000); // getrxsigdetlos() { return (uint)((csr[3] & 0x0800) >> 11); }
                }

                //        fr.d2s_LABEL_END();
                d2s::d2s_LABEL_END();
                //        if (jtag.hasPassed(label))
                //        {
                //          vSigdet_LOS_ALL1[uiMacroIndex][uiLaneIndex] = 1;
                //          sigdet_los_all1 = 1;
                //        }
                //        else
                //        {
                //          vSigdet_LOS_ALL1[uiMacroIndex][uiLaneIndex] = 0;
                //          sigdet_los_all1 = 0;
                //        }
            }
            //      if (iDebugAnalog)
            //      {
            //        cout << "M" << MacroID << "_L" << LaneID << ": " << "\t";
            //        if (sigdet_los_all1 == 1 || vSigdet_LOS_ALL1[uiMacroIndex][uiLaneIndex] == 1)
            //        {
            //            cout <<  "Check SigDet result for "<< dec<< read_cont << " times are all 1" <<endl;
            //        }
            //        else if (sigdet_los_all0 == 1)
            //        {
            //            cout <<  "Check SigDet result for "<< dec<< read_cont << " times are all 0" <<endl;
            //        }
            //        else
            //        {
            //            cout <<  "Check SigDet result for "<< dec<< read_cont << " times, result not stabile, sometimes result is 0 and sometimes result is 1" <<endl;
            //        }
            //      }
        }
    }
#ifdef TestChip
    FW_TASK("DCRT TP,(pAHB)");
#else
    //	  FW_TASK("DCRT TP,(pJTAG)");
#endif
    return 0;
}

//Bert
//==============================================================================
// Function: ReadBert
// - Function of reading PRBS error count
// - RX CSR20 is a RC address, user must record all field value at the same time.
//==============================================================================

void Read_Bert(MACRO_LANE_SEL& vMacroLane_Sel, LANE_DOUBLE &vErrorCount, STRING sTestMode, bool AntiFool, STRING spRXLabe, LONG lCycleNum, DOUBLE dWaitTime_ms) {

    int iDebugAnalog;
    //	GET_TESTFLOW_FLAG("debug_analog",&iDebugAnalog);
    vErrorCount.init(9999);

    //	D2S_FRAMEWORK;
    //	//GET_TEST_INFO;
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    STRING spRXName = "";
    if (sTestMode == "ATE") {
        spRXName = "pUDIRXDATA"; //burst pRX Port Pattern
    } else {
#ifndef TestChip
        spRXName = "pHilink_LS"; //for element build error
#else
        spRXName = "pLS";
#endif

    }

    TransactionPort pRX(spRXName);
    //	fr.registerTransactionPort(pRX);

    //	sprintf(label,"mpb_BertCheck_ExpectValue_wait_%f",dWaitTime_ms);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("mpb_BertCheck_ExpectValue_wait_", Global_D2S_Mode);
    if (sTestMode == "ATE") {
        pRX.execLabel(spRXLabe, lCycleNum);
    }
    // clear reg
    for (uint iMacroIndex = 0; iMacroIndex < vMacroLane_Sel.size(); iMacroIndex++) {
        selectMacro(vMacroLane_Sel[iMacroIndex].MacroID);
        for (uint iLaneIndex = 0; iLaneIndex < vMacroLane_Sel[iMacroIndex].vLane.size(); iLaneIndex++) {
            DS.rxRegs.MacroID(vMacroLane_Sel[iMacroIndex].MacroID).SliceID(vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex]).Broadcast(0);
            //				DS.rxRegs.ExpectValue(20,0x0000,0xffff);
            DS.rxRegs.ExpectValue(20, 0x0000, 0x0000);
        }
    }
    //		jtag.wait(dWaitTime_ms);
    d2s::d2s_LABEL_END();

//    TheInst.Wait(dWaitTime_ms*1000*1000);
	TheInst.Wait(dWaitTime_ms);//2ms
    d2s::d2s_LABEL_BEGIN("mpb_BertCheck_ExpectValue_expect_", Global_D2S_Mode);
    //		jtag.enablePassFailCheckForNextExecution();
    if (AntiFool) {
        for (uint iMacroIndex = 0; iMacroIndex < vMacroLane_Sel.size(); iMacroIndex++) {
            selectMacro(vMacroLane_Sel[iMacroIndex].MacroID);
            for (uint iLaneIndex = 0; iLaneIndex < vMacroLane_Sel[iMacroIndex].vLane.size(); iLaneIndex++) {

                DS.rxRegs.MacroID(vMacroLane_Sel[iMacroIndex].MacroID).SliceID(vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex]).Broadcast(0);
                //					DS.rxRegs.ExpectValue(20,0x8000,0x7fff);//compare 1, all lane should be 1 when anti-proof mode is on
                DS.rxRegs.ExpectValue(20, 0x8000, 0x8000); //compare 1, all lane should be 1 when anti-proof mode is on
            }
        }
    } else {
        for (uint iMacroIndex = 0; iMacroIndex < vMacroLane_Sel.size(); iMacroIndex++) {
            selectMacro(vMacroLane_Sel[iMacroIndex].MacroID);
            for (uint iLaneIndex = 0; iLaneIndex < vMacroLane_Sel[iMacroIndex].vLane.size(); iLaneIndex++) {

                DS.rxRegs.MacroID(vMacroLane_Sel[iMacroIndex].MacroID).SliceID(vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex]).Broadcast(0);
                //					DS.rxRegs.ExpectValue(20,0x0000,0x7fff);//compare 0, all lane should be 0 when anti-proof mode is off
                DS.rxRegs.ExpectValue(20, 0x0000, 0x8000); //compare 0, all lane should be 0 when anti-proof mode is off
            }
        }
    }

    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();



    if (AntiFool) {
        EXPECT_RESULT AntiFoolBertCheck_result;
//        unsigned int sites[MAX_SITES];
        int ConfiguredSitesNum = TheSoft.Sites().Existing().GetExistedSiteCount();//masked by tony 20210817 = api->Get_active_sites(sites);
        ARRAY_I tmp;
        tmp.resize(ConfiguredSitesNum);
        //tmp.init(0);
        AntiFoolBertCheck_result.allpass = true;
        AntiFoolBertCheck_result.allfail = true;
        AntiFoolBertCheck_result.eachsite = tmp;

        //		jtag.hasPassed(label,AntiFoolBertCheck_result.allpass,AntiFoolBertCheck_result.allfail,AntiFoolBertCheck_result.eachsite);
        map<uint32_t, bool> map_pass_fail_result = TheInst.Digital().PatEng().GetPassFail();
//        FOREACH_ACTIVE_SITE(api) {
        	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//        		bool size_pass = map_pass_fail_result[SiteID];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;  masked by tony 20210817
                bool size_pass = map_pass_fail_result[SiteID];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
        		if(PrintDebugEn) cout<<"map_pass_fail_result["<<SiteID<<"] = "<<map_pass_fail_result[SiteID]<<endl;
				AntiFoolBertCheck_result.allpass = (AntiFoolBertCheck_result.allpass && size_pass);
				AntiFoolBertCheck_result.allfail = (AntiFoolBertCheck_result.allfail && !size_pass);
				AntiFoolBertCheck_result.eachsite[SiteID] = size_pass;
            FOREACH_ACTIVESITE_END


        if (AntiFoolBertCheck_result.allpass) {
            hout(DETAIL) << "+++++++++++++++AntiProof is correct+++++++++++++++" << endl;
            if(PrintDebugEn) cout << "+++++++++++++++AntiProof is correct+++++++++++++++" << endl;
            //			FOR_EACH_SITE_BEGIN();
            //			INT SiteID = CURRENT_SITE_NUMBER() - 1;

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
                FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
                for (uint iMacroIndex = 0; iMacroIndex < vMacroLane_Sel.size(); iMacroIndex++) {
                    for (uint iLaneIndex = 0; iLaneIndex < vMacroLane_Sel[iMacroIndex].vLane.size(); iLaneIndex++) {
                        vErrorCount[SiteID][vMacroLane_Sel[iMacroIndex].MacroID][vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex]] = 999;
                        hout(DETAIL) << "SITE " << SiteID << " vErrorCount[" << vMacroLane_Sel[iMacroIndex].MacroID << "][" << vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex] << "] = " << 999 << endl;
                        if(PrintDebugEn) cout << "SITE " << SiteID << " vErrorCount[" << vMacroLane_Sel[iMacroIndex].MacroID << "][" << vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex] << "] = " << 999 << endl;
                    }
                }
                FOREACH_ACTIVESITE_END
        } else {
            hout(DETAIL) << "+++++++++++++++AntiProof is incorrect+++++++++++++++" << endl;
            if(PrintDebugEn) cout << "+++++++++++++++AntiProof is incorrect+++++++++++++++" << endl;
            //			FOR_EACH_SITE_BEGIN();
            //			INT SiteID = CURRENT_SITE_NUMBER() - 1;

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
                FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
                for (uint iMacroIndex = 0; iMacroIndex < vMacroLane_Sel.size(); iMacroIndex++) {
                    for (uint iLaneIndex = 0; iLaneIndex < vMacroLane_Sel[iMacroIndex].vLane.size(); iLaneIndex++) {
                        if (AntiFoolBertCheck_result.eachsite[SiteID] == 0) {
                            vErrorCount[SiteID][vMacroLane_Sel[iMacroIndex].MacroID][vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex]] = 0;
                        } else {
                            vErrorCount[SiteID][vMacroLane_Sel[iMacroIndex].MacroID][vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex]] = 999;
                        }
                        hout(DETAIL) << "SITE " << SiteID << " vErrorCount[" << vMacroLane_Sel[iMacroIndex].MacroID << "][" << vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex] << "] = " << 0 << endl;
                        if(PrintDebugEn) cout << "SITE " << SiteID << " vErrorCount[" << vMacroLane_Sel[iMacroIndex].MacroID << "][" << vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex] << "] = " << 0 << endl;
                    }
                }
                FOREACH_ACTIVESITE_END
        }
    }
    else {
        EXPECT_RESULT BertCheck_result;
        //		jtag.hasPassed(label,BertCheck_result.allpass,BertCheck_result.allfail,BertCheck_result.eachsite);
//        unsigned int sites[MAX_SITES];
        int ConfiguredSitesNum = TheSoft.Sites().Existing().GetExistedSiteCount();// api->Get_active_sites(sites);
        ARRAY_I tmp;
        tmp.resize(ConfiguredSitesNum);
        //tmp.init(0);
        BertCheck_result.allpass = true;
        BertCheck_result.allfail = true;
        BertCheck_result.eachsite = tmp;

//        FOREACH_ACTIVE_SITE(api) {
        map<uint32_t, bool> map_pass_fail_result = TheInst.Digital().PatEng().GetPassFail();
        	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//            bool size_pass = map_pass_fail_result[SiteID];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;  masked by tony 20210817
            bool size_pass = map_pass_fail_result[SiteID];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
    		if(PrintDebugEn) cout<<"map_pass_fail_result["<<SiteID<<"] = "<<map_pass_fail_result[SiteID]<<endl;
            BertCheck_result.allpass = (BertCheck_result.allpass && size_pass);
            BertCheck_result.allfail = (BertCheck_result.allfail && !size_pass);
            BertCheck_result.eachsite[SiteID] = size_pass;
            FOREACH_ACTIVESITE_END

//        if (BertCheck_result.allpass && 1 == Global_D2S_Mode) {
            if (0) {
            hout(DETAIL) << "+++++++++++++++Normal BERT is correct+++++++++++++++" << endl;
            cout << "+++++++++++++++Normal BERT is correct+++++++++++++++" << endl;
            //			FOR_EACH_SITE_BEGIN();
            //			INT SiteID = CURRENT_SITE_NUMBER() - 1;

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
                FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
                for (uint iMacroIndex = 0; iMacroIndex < vMacroLane_Sel.size(); iMacroIndex++) {
                    for (uint iLaneIndex = 0; iLaneIndex < vMacroLane_Sel[iMacroIndex].vLane.size(); iLaneIndex++) {
                        vErrorCount[SiteID][vMacroLane_Sel[iMacroIndex].MacroID][vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex]] = 0;
                        hout(DETAIL) << "SITE " << SiteID << " vErrorCount[" << vMacroLane_Sel[iMacroIndex].MacroID << "][" << vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex] << "] = " << 0 << endl;
                        if(PrintDebugEn)  cout << "SITE " << SiteID << " vErrorCount[" << vMacroLane_Sel[iMacroIndex].MacroID << "][" << vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex] << "] = " << 0 << endl;
                    }
                }
                FOREACH_ACTIVESITE_END
            //			FOR_EACH_SITE_END();
        } else {
            hout(DETAIL) << "+++++++++++++++Normal BERT is incorrect+++++++++++++++" << endl;
            if(PrintDebugEn) cout << "+++++++++++++++Normal BERT is incorrect+++++++++++++++" << endl;
            d2s::d2s_LABEL_BEGIN("mpb_BertCheck_AfterExpectValueFail_wait_", Global_D2S_Mode);
            if (sTestMode == "ATE") {
                pRX.execLabel(spRXLabe, lCycleNum);
            }

            // clear reg
            for (uint iMacroIndex = 0; iMacroIndex < vMacroLane_Sel.size(); iMacroIndex++) {
                selectMacro(vMacroLane_Sel[iMacroIndex].MacroID);
                for (uint iLaneIndex = 0; iLaneIndex < vMacroLane_Sel[iMacroIndex].vLane.size(); iLaneIndex++) {
                    DS.rxRegs.MacroID(vMacroLane_Sel[iMacroIndex].MacroID).SliceID(vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex]).Broadcast(0);
                    //					DS.rxRegs.ExpectValue(20,0,0xffff);
                    DS.rxRegs.ExpectValue(20, 0, 0x0000);
                }
            }
            d2s::d2s_LABEL_END();

//            TheInst.Wait(dWaitTime_ms*1000*1000);
        	TheInst.Wait(dWaitTime_ms);//2ms
            d2s::d2s_LABEL_BEGIN("mpb_BertCheck_AfterExpectValueFail_read_", Global_D2S_Mode);

            for (uint iMacroIndex = 0; iMacroIndex < vMacroLane_Sel.size(); iMacroIndex++) {
                selectMacro(vMacroLane_Sel[iMacroIndex].MacroID);
                for (uint iLaneIndex = 0; iLaneIndex < vMacroLane_Sel[iMacroIndex].vLane.size(); iLaneIndex++) {
                    DS.rxRegs.MacroID(vMacroLane_Sel[iMacroIndex].MacroID).SliceID(vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex]).Broadcast(0);
                    ostringstream id20;
                    id20 << "M" << vMacroLane_Sel[iMacroIndex].MacroID << "_L" << vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex] << "_CSR20_" << jtag.Context;
                    DS.rxRegs.Read2IDString(20, id20.str());
                }
            }
            d2s::d2s_LABEL_END();

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
                for (uint iMacroIndex = 0; iMacroIndex < vMacroLane_Sel.size(); iMacroIndex++) {
                    for (uint iLaneIndex = 0; iLaneIndex < vMacroLane_Sel[iMacroIndex].vLane.size(); iLaneIndex++) {
                        uint uiPrbsErrorCount; // Total error counter
                        uint uiPrbsCntExp; // The exponent of error counter
                        uint uiPrbsCnt; // The base number of error counter
                        uint uiPrbsErr; // Error flag, 1 means error detected.
                        ostringstream id20;
                        id20 << "M" << vMacroLane_Sel[iMacroIndex].MacroID << "_L" << vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex] << "_CSR20_" << jtag.Context;
                        DS.rxRegs.csr[20] = (uint) jtag.getReadValue(id20.str())[SiteID];
                        uiPrbsErr = DS.rxRegs.getprbserr();
                        uiPrbsCntExp = DS.rxRegs.getprbscntexp();
                        uiPrbsCnt = DS.rxRegs.getprbscnt();
                        if (uiPrbsErr) {
                            if (uiPrbsCntExp == 0) {
                                uiPrbsErrorCount = uiPrbsCnt;
                            } else {
                                uiPrbsErrorCount = (0x1 << (10 + uiPrbsCntExp)) + uiPrbsCnt * (0x1 << (uiPrbsCntExp - 1));
                            }
                        } else {
                            uiPrbsErrorCount = 0;
                        }
                        vErrorCount[SiteID][vMacroLane_Sel[iMacroIndex].MacroID][vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex]] = uiPrbsErrorCount;
                        hout(DETAIL) << "SITE " << SiteID << " vErrorCount[" << vMacroLane_Sel[iMacroIndex].MacroID << "][" << vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex] << "] = " << uiPrbsErrorCount << endl;
                        if(PrintDebugEn) cout << "SITE " << SiteID << " vErrorCount[" << vMacroLane_Sel[iMacroIndex].MacroID << "][" << vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex] << "] = " << uiPrbsErrorCount << endl;
//                        cout << "SITE " << SiteID << " uiPrbsErr = " << uiPrbsErr << endl;
//                        cout << "SITE " << SiteID << " uiPrbsCntExp = " << uiPrbsCntExp << endl;
//                        cout << "SITE " << SiteID << " uiPrbsCnt = " <<uiPrbsCnt << endl;

                        //printf("vErrorCount[%d][%d] = %d\n", vMacroLane_Sel[iMacroIndex].MacroID, vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex], uiPrbsErrorCount);
                    }
                }
			FOREACH_ACTIVESITE_END
        }
    }
}


//Eye Diagram

uint Check_EMReady(int iMacroID, int iLaneID, SITE_INT& result) {
    //	D2S_FRAMEWORK;
    //	//GET_TEST_INFO;
    d2s_JTAG& jtag = d2s_JTAG::Instance();
    //	sprintf(label,"GeneralEyeScan_Check_EMReady_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("GeneralEyeScan_Check_EMReady_", Global_D2S_Mode);

    //		jtag.enablePassFailCheckForNextExecution();
    selectMacro(iMacroID);
    DS.rxRegs.MacroID(iMacroID).SliceID(iLaneID).Broadcast(0);
    //		DS.rxRegs.ExpectValue(17,0x2000,0xdfff);
    DS.rxRegs.ExpectValue(17, 0x2000, 0x2000);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	result = jtag.hasPassed(label);
    return is_allPass("GeneralEyeScan_Check_EMReady", result);
}

bool Check_EMReady(MACRO_LANE_SEL& vMacroLane_Sel, SITE_INT& result) {
    //	D2S_FRAMEWORK;
    //	//GET_TEST_INFO;
    d2s_JTAG& jtag = d2s_JTAG::Instance();
    //	sprintf(label,"GeneralEyeScan_Check_EMReady_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("GeneralEyeScan_Check_EMReady_", Global_D2S_Mode);

    jtag.enablePassFailCheckForNextExecution();
    for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
        UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
        selectMacro(MacroID);
        for (uint uiLaneIndex = 0; uiLaneIndex < vMacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
            UINT LaneID = vMacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];
            DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
            //				DS.rxRegs.ExpectValue(17,0x2000,0xdfff);
            DS.rxRegs.ExpectValue(17, 0x2000, 0x2000);
        }
    }
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    return is_allPass("GeneralEyeScan_Check_EMReady", result);
}

uint Check_EyeScanStart(int iMacroID, int iLaneID, SITE_INT& result) {
    //	D2S_FRAMEWORK;
    //GET_TEST_INFO;
    //	sprintf(label,"GeneralEyeScan_Start_%f_%f_",Vcoef,Temp);
    //fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("GeneralEyeScan_Start_", Global_D2S_Mode);
    //		jtag.enablePassFailCheckForNextExecution();
    selectMacro(iMacroID);
    DS.rxRegs.MacroID(iMacroID).SliceID(iLaneID).Broadcast(0);
    //		DS.rxRegs.ExpectValue(17,0x4000,0xbfff);
    DS.rxRegs.ExpectValue(17, 0x4000, 0x2000);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    return is_allPass("GeneralEyeScan_Start", result);
}

bool Check_EyeScanStart(MACRO_LANE_SEL& vMacroLane_Sel, SITE_INT& result) {
    //	D2S_FRAMEWORK;
    //GET_TEST_INFO;
    //	sprintf(label,"GeneralEyeScan_Start_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("GeneralEyeScan_Start_", Global_D2S_Mode);
    //		jtag.enablePassFailCheckForNextExecution();
    for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
        UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
        selectMacro(MacroID);
        for (uint uiLaneIndex = 0; uiLaneIndex < vMacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
            UINT LaneID = vMacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];
            DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
            //				DS.rxRegs.ExpectValue(17,0x0000,0xbfff);
            DS.rxRegs.ExpectValue(17, 0x0000, 0x2000);
        }
    }
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    return is_allPass("GeneralEyeScan_Start", result);
}


//==============================================================================
// Function: GeneralEyeScan
// - this function is used for basic eye scan.
// - eyeScanMode: 0=horizontal inner eye scan, 1=vertical inner eye scan
//                2=horizontal outer eye scan, 3=vertical outer eye scan
// - eyeScanWin: BER definition
//               for inner eye scan BER=1/(320*2^eyeScanWin);
//               for outer eye scan BER=eyeScanWin/40;
// - mPhsOfst: phase offset for eye scan
// - mVolOfst: voltage offset for eye scan
// - avgTime: average time, 0=1 times, 1=8 times, 2=16 times, 3=32 times
// - monSlcSel: channel select, 0=I, 1=Q, 2=Ib, 3=Qb
// - eyeCornor0: the left  or lower corner value
// - eyeCornor1: the right  or upper corner value
//==============================================================================

bool GeneralEyeScan(MACRO_LANE_SEL& vMacroLane_Sel, uint iEyeScanMode, uint iEyeScanWin, LANE_INT iPhsofst, LANE_INT iVolOfst, uint iAvgTime, uint iMonSlcSel, LANE_INT& iEyeCornor0, LANE_INT& iEyeCornor1, STRING sTestMode, STRING spRXLabel, LONG lCycleNum) {
    INT csrindex_TB_read;
    LANE_INT iAlfgenOfst;
    LANE_INT uiRatemode;

    iVolOfst.init(0);
    iEyeCornor0.init(0);
    iEyeCornor1.init(0);
    iAlfgenOfst.init(0);
    uiRatemode.init(0);

    char IDstring[128] = "";


    STRING spRXName = "";
    if (sTestMode == "ATE") {
        spRXName = "pUDIRXDATA"; //burst pRX Port Pattern
    } else {
#ifndef TestChip
        spRXName = "pHilink_LS"; //for element build error
#else
        spRXName = "pLS";
#endif
    }

    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();
    //GET_TEST_INFO;

    TransactionPort pRX(spRXName);

    //RateMode check
    //	sprintf(label,"GeneralEyeScan_ReadBack_ratemode");
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("GeneralEyeScan_ReadBack_ratemode", Global_D2S_Mode);
    for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
        UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
        selectMacro(MacroID);
        for (uint uiLaneIndex = 0; uiLaneIndex < vMacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
            UINT LaneID = vMacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];
            sprintf(IDstring, "Ratemode_%d_%d", MacroID, LaneID);
            DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
            DS.rxRegs.Read2IDString(12, IDstring);
        }
    }
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //	INT SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
        for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
            UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
            for (uint uiLaneIndex = 0; uiLaneIndex < vMacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
                UINT LaneID = vMacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];
                sprintf(IDstring, "Ratemode_%d_%d", MacroID, LaneID);
                uint val = (UINT) jtag.getReadValue(IDstring)[SiteID];
                uiRatemode[SiteID][MacroID][LaneID] = HILINK_Regs_Base::get_bits(val, DS.rxRegs.REG_INFO.rxratemode());
            }
        }

        for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
            UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
            for (uint uiLaneIndex = 0; uiLaneIndex < vMacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
                UINT LaneID = vMacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];
                if (0x1 == uiRatemode[SiteID][MacroID][LaneID]) {
                    if ((0x0 == iMonSlcSel) || (0x2 == iMonSlcSel)) {
//                        hout(GENERAL) << "ERROR: Site" << SiteID << " Macro" << MacroID << " Lane" << LaneID << " I/Ib cahnnel is not support in half rate mode!" << endl;
                        cout << "ERROR: Site" << SiteID << " Macro" << MacroID << " Lane" << LaneID << " I/Ib cahnnel is not support in half rate mode!" << endl;
//                        return false; //masked by tony 20210817
                    }
                } else if (0x2 == uiRatemode[SiteID][MacroID][LaneID]) {
                    if (0x1 != iMonSlcSel) {
                    	cout << "ERROR: Site" << SiteID << " Macro" << MacroID << " Lane" << LaneID << " I/Ib/Qb cahnnel is not support in querter rate mode!" << endl;
//                        return false;//masked by tony 20210817
                    }
                } else if (0x3 == uiRatemode[SiteID][MacroID][LaneID]) {
                    if (0x1 != iMonSlcSel) {
                    	cout << "ERROR: Site" << SiteID << " Macro" << MacroID << " Lane" << LaneID << " I/Ib/Qb cahnnel is not support in octal rate mode!" << endl;
//                        return false;//masked by tony 20210817
                    }
                } else if (0x3 < uiRatemode[SiteID][MacroID][LaneID]) {
                    cout << "ERROR: Site" << SiteID << " Macro" << MacroID << " Lane" << LaneID << " Eye monitor is not support in hex rate mode!" << endl;
//                    return false;//masked by tony 20210817
                }
            }
        }
        FOREACH_ACTIVESITE_END


    //	fr.registerTransactionPort(pRX);

    //	sprintf(label,"GeneralEyeScan_ReadBack_ratemode_%f_%f",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("GeneralEyeScan_ReadBack_ratemode_", Global_D2S_Mode);
    for (UINT iMacroIndex = 0; iMacroIndex < vMacroLane_Sel.size(); iMacroIndex++) {
        UINT iMacroID = vMacroLane_Sel[iMacroIndex].MacroID;
        const vector<UINT>& vLane = vMacroLane_Sel[iMacroIndex].vLane;
        for (UINT iLaneIndex = 0; iLaneIndex < vLane.size(); iLaneIndex++) {
            UINT iLaneID = vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex];
            selectMacro(iMacroID);
            DS.rxExtRegs.MacroID(iMacroID).SliceID(iLaneID).Broadcast(0);
            csrindex_TB_read = 46;
            sprintf(IDstring, "DSRXEXT_M%d_L%d_CSR%d", iMacroID, iLaneID, csrindex_TB_read);
            DS.rxExtRegs.Read2IDString(csrindex_TB_read, IDstring);
        }
    }
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();

    for (UINT iMacroIndex = 0; iMacroIndex < vMacroLane_Sel.size(); iMacroIndex++) {
        UINT iMacroID = vMacroLane_Sel[iMacroIndex].MacroID;
        const vector<UINT>& vLane = vMacroLane_Sel[iMacroIndex].vLane;
        for (UINT iLaneIndex = 0; iLaneIndex < vLane.size(); iLaneIndex++) {
            UINT iLaneID = vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex];
            //			FOR_EACH_SITE_BEGIN();
            //			INT iSiteID = CURRENT_SITE_NUMBER() - 1;

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int iSiteID = api->Get_active_site();
                FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
                sprintf(IDstring, "DSRXEXT_M%d_L%d_CSR%d", iMacroID, iLaneID, csrindex_TB_read);
                uint val = (UINT) jtag.getReadValue(IDstring)[SiteID];
                iAlfgenOfst[SiteID][iMacroID][iLaneID] = (HILINK_Regs_Base::get_bits(val, DS.rxExtRegs.REG_INFO.dsspare3())) & 0x1FF;

                if (0x0 != (iAlfgenOfst[SiteID][iMacroID][iLaneID] & 0x100)) {
                    iAlfgenOfst[SiteID][iMacroID][iLaneID] -= 0x200;
                }
                iVolOfst[SiteID][iMacroID][iLaneID] = iAlfgenOfst[SiteID][iMacroID][iLaneID] - iVolOfst[SiteID][iMacroID][iLaneID];
                hout(DETAIL) << "Site:" << SiteID << "\tMacor:" << iMacroID << "\tlane:" << iLaneID << "\tVolOfst:" << iVolOfst[SiteID][iMacroID][iLaneID] << endl;
                hout(DETAIL) << "Site:" << SiteID << "\tMacor:" << iMacroID << "\tlane:" << iLaneID << "\tPhsofst:" << iPhsofst[SiteID][iMacroID][iLaneID] << endl;


                FOREACH_ACTIVESITE_END
        }
    }

    LANE_INT CSRvalue_mphsofst;
    LANE_INT CSRvalue_mvolofst;

    CSR_READ(vMacroLane_Sel, DS.rxRegs, 18, CSRvalue_mphsofst);
    CSR_READ(vMacroLane_Sel, DS.rxRegs, 22, CSRvalue_mvolofst);

    Update_DSReg_ForDynamicWrite(vMacroLane_Sel, DS.rxRegs.REG_INFO.mphsofst(), iPhsofst, CSRvalue_mphsofst);
    Update_DSReg_ForDynamicWrite(vMacroLane_Sel, DS.rxRegs.REG_INFO.mvolofst(), iVolOfst, CSRvalue_mvolofst);


    //	fr.registerTransactionPort(pRX);

    //DS set eye config
    //	sprintf(label,"GeneralEyeScan_DS_SET_EYE_CONFIG0_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("GeneralEyeScan_DS_SET_EYE_CONFIG0_", Global_D2S_Mode);
    if (sTestMode == "ATE") {
        pRX.execLabel(spRXLabel, lCycleNum);
    }

    selectMacro_MB(vMacroLane_Sel);
    DS.rxRegs.SliceID(0).Broadcast(1);
    DS.rxRegs.seteyemonpwrdb(0x1).Write2DUT(17);
    DS.rxRegs.setrxmonpwrdb(0x1).Write2DUT(48);
    DS.rxRegs.seteyescanwinsel(0x0).Write2DUT(17); //normal eye scan
    DS.rxRegs.seteyescanmode(iEyeScanMode).Write2DUT(17);
    DS.rxRegs.seteyescanwin(iEyeScanWin).Write2DUT(17);

    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	sprintf(label,"GeneralEyeScan_DS_SET_EYE_CONFIG1_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("GeneralEyeScan_DS_SET_EYE_CONFIG1_", Global_D2S_Mode);
    if (sTestMode == "ATE") {
        pRX.execLabel(spRXLabel, lCycleNum);
    }

    for (UINT iMacroIndex = 0; iMacroIndex < vMacroLane_Sel.size(); iMacroIndex++) {
        UINT MacroID = vMacroLane_Sel[iMacroIndex].MacroID;
        selectMacro(MacroID);
        for (UINT iLaneIndex = 0; iLaneIndex < vMacroLane_Sel[iMacroIndex].vLane.size(); iLaneIndex++) {
            UINT LaneID = vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex];
            DS.rxRegs.MacroID(MacroID).SliceID(0).Broadcast(0);
            ostringstream id18;
            ostringstream id22;
            id18 << "CSR18_" << "_M" << MacroID << "_L" << LaneID << jtag.Context;
            id22 << "CSR22_" << "_M" << MacroID << "_L" << LaneID << jtag.Context;
            DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
            map<int, long long> tmp1;
            map<int, long long> tmp2;
            parseSiteDataFromLaneInt(tmp1, CSRvalue_mphsofst, MacroID, LaneID);
            parseSiteDataFromLaneInt(tmp2, CSRvalue_mvolofst, MacroID, LaneID);
            DS.rxRegs.Write2DUT_DYN(18, tmp1, id18.str()); //TODO to be optimized
            DS.rxRegs.Write2DUT_DYN(22, tmp2, id22.str()); //TODO to be optimized
        }
    }
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	sprintf(label,"GeneralEyeScan_DS_SET_EYE_CONFIG2_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("GeneralEyeScan_DS_SET_EYE_CONFIG2_", Global_D2S_Mode);
    if (sTestMode == "ATE") {
        pRX.execLabel(spRXLabel, lCycleNum);
    }

    selectMacro_MB(vMacroLane_Sel);
    DS.rxRegs.SliceID(0).Broadcast(1);
    DS.rxRegs.setemtaskavrg(iAvgTime).Write2DUT(27);
    DS.rxRegs.setmonslcsel(iMonSlcSel).Write2DUT(19);
    DS.rxRegs.setmcoarsealignen(0x1).Write2DUT(58); //enable center-monitor coarse align
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	WAIT_TIME(10 ms);
//    api->sleep(0.01);
//    TheInst.Wait(10*1000);
	TheInst.Wait(0.001 * 10);//10ms
    EXPECT_RESULT Check_EMReady;
    WaitDone(vMacroLane_Sel, "Lane", DS.rxRegs.REG_INFO.emready(), 1, 10, 1, Check_EMReady);
    if (true == Check_EMReady.allfail) {
        return false; /*All Site Wait Done failed*/
    }

    //	fr.registerTransactionPort(pRX);

    //Center monitor again
    //	sprintf(label,"GeneralEyeScan_SET_CENTER_MONITOR_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("GeneralEyeScan_SET_CENTER_MONITOR_", Global_D2S_Mode);
    if (sTestMode == "ATE") {
        pRX.execLabel(spRXLabel, lCycleNum);
    }

    selectMacro_MB(vMacroLane_Sel);
    DS.rxRegs.SliceID(0).Broadcast(1);
    DS.rxRegs.setmcoarsealignen(0x0).Write2DUT(58); // enable center-monitor coarse align
    DS.rxRegs.seteyescanstart(0x1).Write2DUT(17); // start the scan
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //wait for eye scan done
    EXPECT_RESULT EyeScanStart_Status;
    WaitDone(vMacroLane_Sel, "Lane", DS.rxRegs.REG_INFO.eyescanstart(), 0, 100, 10, EyeScanStart_Status);


    if (true == EyeScanStart_Status.allfail) {
        return false; /*All Site Wait Done failed*/
    }

    //	fr.registerTransactionPort(pRX);

    //	sprintf(label,"GeneralEyeScan_GET_EMRESULT0_EMRESULT1_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("GeneralEyeScan_GET_EMRESULT0_EMRESULT1_", Global_D2S_Mode);
    for (UINT iMacroIndex = 0; iMacroIndex < vMacroLane_Sel.size(); iMacroIndex++) {
        UINT MacroID = vMacroLane_Sel[iMacroIndex].MacroID;
        const vector<UINT>& vLane = vMacroLane_Sel[iMacroIndex].vLane;

        selectMacro(MacroID);
        for (UINT iLaneIndex = 0; iLaneIndex < vLane.size(); iLaneIndex++) {
            UINT LaneID = vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex];

            DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
            csrindex_TB_read = 23; //
            sprintf(IDstring, "DSRX_M%d_L%d_CSR%d", MacroID, LaneID, csrindex_TB_read);
            DS.rxRegs.Read2IDString(csrindex_TB_read, IDstring);
            csrindex_TB_read = 24;
            sprintf(IDstring, "DSRX_M%d_L%d_CSR%d", MacroID, LaneID, csrindex_TB_read);
            DS.rxRegs.Read2IDString(csrindex_TB_read, IDstring);
        }
    }
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //	UINT SiteID = CURRENT_SITE_NUMBER()-1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT iMacroIndex = 0; iMacroIndex < vMacroLane_Sel.size(); iMacroIndex++) {
            UINT iMacroID = vMacroLane_Sel[iMacroIndex].MacroID;
            const vector<UINT>& vLane = vMacroLane_Sel[iMacroIndex].vLane;

            for (UINT iLaneIndex = 0; iLaneIndex < vLane.size(); iLaneIndex++) {
                UINT iLaneID = vMacroLane_Sel[iMacroIndex].vLane[iLaneIndex];

                csrindex_TB_read = 23;
                sprintf(IDstring, "DSRX_M%d_L%d_CSR%d", iMacroID, iLaneID, csrindex_TB_read);

                uint val = (UINT) jtag.getReadValue(IDstring)[SiteID];
                int tmpCornor0 = HILINK_Regs_Base::get_bits(val, DS.rxRegs.REG_INFO.emresult0());

                if (tmpCornor0 > 0x100) {
                    tmpCornor0 -= 0x200;
                }
                csrindex_TB_read = 24;
                sprintf(IDstring, "DSRX_M%d_L%d_CSR%d", iMacroID, iLaneID, csrindex_TB_read);

                val = (UINT) jtag.getReadValue(IDstring)[SiteID];
                int tmpCornor1 = HILINK_Regs_Base::get_bits(val, DS.rxRegs.REG_INFO.emresult1());

                if (tmpCornor1 > 0x100) {
                    tmpCornor1 -= 0x200;
                }

                if (0x1 == iEyeScanMode || 0x3 == iEyeScanMode) {
                    if ((tmpCornor0 == -1) && (tmpCornor1 == 0)) {
                        iEyeCornor0[SiteID][iMacroID][iLaneID] = 0;
                        iEyeCornor1[SiteID][iMacroID][iLaneID] = 0;
                    } else {
                        iEyeCornor0[SiteID][iMacroID][iLaneID] = -1 * tmpCornor1 + iAlfgenOfst[SiteID][iMacroID][iLaneID];
                        iEyeCornor1[SiteID][iMacroID][iLaneID] = -1 * tmpCornor0 + iAlfgenOfst[SiteID][iMacroID][iLaneID];
                    }
                } else {
                    iEyeCornor0[SiteID][iMacroID][iLaneID] = tmpCornor0;
                    iEyeCornor1[SiteID][iMacroID][iLaneID] = tmpCornor1;
                }

                hout(DETAIL) << "GeneralEyeScan Debug M" << iMacroID << "_Lane" << iLaneID << " " << iEyeCornor0[SiteID][iMacroID][iLaneID] << "\t" << " " << iEyeCornor1[SiteID][iMacroID][iLaneID] << "\tdelta = " << iEyeCornor1[SiteID][iMacroID][iLaneID] - iEyeCornor0[SiteID][iMacroID][iLaneID] << endl;
            }
        }

        FOREACH_ACTIVESITE_END
    //	sprintf(label,"GeneralEyeScan_POWER_DOWN_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));//TODO
    d2s::d2s_LABEL_BEGIN("GeneralEyeScan_POWER_DOWN_", Global_D2S_Mode);
    selectMacro_MB(vMacroLane_Sel);
    DS.rxRegs.SliceID(0).Broadcast(1);
    DS.rxRegs.seteyemonpwrdb(0x0).Write2DUT(17);
    DS.rxRegs.setrxmonpwrdb(0x0).Write2DUT(48);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    return true;
}

//==============================================================================
// Function: GetEyeDiagram
// - This function is used to get full eye diagram.
// - eyeScanMode: 0=horizontal inner eye scan, 1=vertical inner eye scan
//                2=horizontal outer eye scan, 3=vertical outer eye scan
// - eyeScanWin: BER definition
//               for inner eye scan BER=1/(320*2^eyeScanWin);
//               for outer eye scan BER=eyeScanWin/40;
// - monSlcSel: channel select, 0=I, 1=Q, 2=Ib, 3=Qb
// - tap1Inside: 0=eye diagram without tap1,
//               1=eye diagram with tap1(only vertical scan is available in this mode)
// - tap1Type: 0=plot the lower side of tap1 eye; 1=plot the upper side of tap1 eye;
//              2=plot the composite tap1 eye; 3=forbidden;
// - eyeDiagram[512][2]: the eye diagram scan result.
//==============================================================================

bool GetEyeDiagram(MACRO_LANE_SEL& vMacroLane_Sel, int iEyeScanMode, int iEyeScanWin, int iMonSlcSel, uint itap1Inside, uint itap1Type, STRING sTestMode, STRING spRXLabel, LONG lCycleNum)//, int iEyeDiagram0[HILINK_MACRO_NUM][HILINK_MAX_LANE_NUM][512], int iEyeDiagram1[HILINK_MACRO_NUM][HILINK_MAX_LANE_NUM][512])
{

    LANE_INT uiRatemode;
    LANE_INT mPhsOfst, mVolOfst, tap1Ofst;
    int iMinPhsOfst;
    int iMaxPhsOfst;
    int iPhsOfst;
    int iRateMode;

    LANE_INT eyeMiddle0;
    LANE_INT eyeMiddle1;
    vector< LANE_INT> eyeDiagram_Corner0;
    vector< LANE_INT> eyeDiagram_Corner1;
    LANE_INT eyeDiagram_tmp_Corner0;
    LANE_INT eyeDiagram_tmp_Corner1;
    LANE_INT iDfefxtap1cen, iDsspare2;
    UINT index;

    mPhsOfst.init(0), mVolOfst.init(0), tap1Ofst.init(0), uiRatemode.init(0);
    eyeMiddle0.init(0), eyeMiddle1.init(0), eyeDiagram_tmp_Corner0.init(0), eyeDiagram_tmp_Corner1.init(0);
    iDfefxtap1cen.init(0), iDsspare2.init(0);
    uiRatemode.init(0);

    eyeDiagram_Corner0.resize(512);
    eyeDiagram_Corner1.resize(512);

    for (uint ii = 0; ii < 512; ii++) {
        LANE_INT tmp;
        tmp.init(0);
        eyeDiagram_Corner0.push_back(tmp);
        eyeDiagram_Corner1.push_back(tmp);
    }

    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();
    //GET_TEST_INFO;
    char IDstring[128] = "";

    //	sprintf(label,"GetEyeDiagram_EyeMonitor_Config_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("GetEyeDiagram_EyeMonitor_Config_", Global_D2S_Mode);
    selectMacro_MB(vMacroLane_Sel);
    DS.rxRegs.SliceID(0).Broadcast(1);
    DS.rxRegs.setemtaskctrl(0x0).seteyemontask(0x0).Write2DUT(25);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	sprintf(label,"GetEyeDiagram_ReadBack_ratemode_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("GetEyeDiagram_ReadBack_ratemode_", Global_D2S_Mode);
    for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
        UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
        selectMacro(MacroID);
        for (uint uiLaneIndex = 0; uiLaneIndex < vMacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
            UINT LandID = vMacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];
            sprintf(IDstring, "Ratemode_%d_%d", MacroID, LandID);
            DS.rxRegs.MacroID(MacroID).SliceID(LandID).Broadcast(0);
            DS.rxRegs.Read2IDString(12, IDstring);
        }
    }
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    iRateMode = -1;
    //	FOR_EACH_SITE_BEGIN();
    //		INT SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
            UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
            for (uint uiLaneIndex = 0; uiLaneIndex < vMacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
                UINT LaneID = vMacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];
                sprintf(IDstring, "Ratemode_%d_%d", MacroID, LaneID);
                uint val = (UINT) jtag.getReadValue(IDstring)[SiteID];
                uiRatemode[SiteID][MacroID][LaneID] = HILINK_Regs_Base::get_bits(val, DS.rxRegs.REG_INFO.rxratemode());

                if (-1 == iRateMode) {
                    iRateMode = uiRatemode[SiteID][MacroID][LaneID];
                } else {
                    if (iRateMode != uiRatemode[SiteID][MacroID][LaneID]) {
                        //						cout<<"WARNING: Ratemode is not the same on all SITE,Macro,Lane!!!"<<endl;
                        printf("WARNING: Ratemode is not the same on all SITE,Macro,Lane!!!\n");
                    }
                }
            }
        }
        FOREACH_ACTIVESITE_END
    for (INT i = -256; i < 256; i++) {
        if (iEyeScanMode == 0x1 || iEyeScanMode == 0x3) {
            iMinPhsOfst = -16 * (0x1 << iRateMode);
            iMaxPhsOfst = 16 * (0x1 << iRateMode);
            if (i >= iMinPhsOfst && i <= 0) {
                iPhsOfst = -i + iMinPhsOfst;
            } else if (i > 0 && i <= iMaxPhsOfst) {
                iPhsOfst = i;
            } else {
                continue;
            }
            index = iPhsOfst + 256;
        } else {
            iPhsOfst = 0;
            if (i >= -159 && i <= 159) {
                mVolOfst.init(i);
            } else {
                continue;
            }
            index = i + 256;
        }

        hout(DETAIL) << "Drawing EyeDiagram on PhaseOffset " << iPhsOfst << "\t..." << endl;
        mPhsOfst.init(iPhsOfst);
        if (itap1Inside == 0x1) {
            int itap1Pol = (itap1Type > 0) ? 0x1 : 0x0;
            //			sprintf(label,"GetEyeDiagram_Tap1_Config1_%f_%f_",Vcoef,Temp);
            //			fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
            d2s::d2s_LABEL_BEGIN("GetEyeDiagram_Tap1_Config1_", Global_D2S_Mode);
            selectMacro_MB(vMacroLane_Sel);
            DS.rxRegs.SliceID(0).Broadcast(1);
            DS.rxRegs.settap1en(0x1).settap1pol(itap1Pol).Write2DUT(12); //Ultra use fixed itap1p
            //			fr.d2s_LABEL_END();
            d2s::d2s_LABEL_END();
        }

        // readback
        //		sprintf(label,"GetEyeDiagram_ReadBack_DSRXCSR51_%f_%f_",Vcoef,Temp);
        //fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
        d2s::d2s_LABEL_BEGIN("GetEyeDiagram_ReadBack_DSRXCSR51_", Global_D2S_Mode);
        for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
            UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
            selectMacro(MacroID);
            for (uint uiLaneIndex = 0; uiLaneIndex < vMacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
                UINT LaneID = vMacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];
                DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
                DS.rxExtRegs.SliceID(LaneID).Broadcast(0);
                sprintf(IDstring, "DSRXCSR51_%d_%d", MacroID, LaneID);
                DS.rxRegs.Read2IDString(51, IDstring);
                sprintf(IDstring, "DSRXEXTCSR45_%d_%d", MacroID, LaneID);
                DS.rxExtRegs.Read2IDString(45, IDstring);
            }
        }
        //		fr.d2s_LABEL_END();
        d2s::d2s_LABEL_END();
        // get readback value
        //		FOR_EACH_SITE_BEGIN();
        //		int SiteID = CURRENT_SITE_NUMBER()-1;

//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int SiteID = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

            for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
                UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
                for (uint uiLaneIndex = 0; uiLaneIndex < vMacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
                    UINT LaneID = vMacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];
                    uint val;
                    sprintf(IDstring, "DSRXCSR51_%d_%d", MacroID, LaneID);
                    val = (UINT) jtag.getReadValue(IDstring)[SiteID];
                    iDfefxtap1cen[SiteID][MacroID][LaneID] = HILINK_Regs_Base::get_bits(val, DS.rxRegs.REG_INFO.dfefxtap1cen());

                    sprintf(IDstring, "DSRXEXTCSR45_%d_%d", MacroID, LaneID);
                    val = (UINT) jtag.getReadValue(IDstring)[SiteID];
                    iDsspare2[SiteID][MacroID][LaneID] = HILINK_Regs_Base::get_bits(val, DS.rxExtRegs.REG_INFO.dsspare2());

                    tap1Ofst[SiteID][MacroID][LaneID] = (iDfefxtap1cen[SiteID][MacroID][LaneID] & 0x7F);
                    if (0x0 != (iDfefxtap1cen[SiteID][MacroID][LaneID] & 0x80)) {
                        tap1Ofst[SiteID][MacroID][LaneID] = -1 * tap1Ofst[SiteID][MacroID][LaneID];
                    }

                    if (0x0 != (iDsspare2[SiteID][MacroID][LaneID] * 0x8000)) {
                        tap1Ofst[SiteID][MacroID][LaneID] += ((iDsspare2[SiteID][MacroID][LaneID] >> 8) & 0x7F);
                    } else {
                        tap1Ofst[SiteID][MacroID][LaneID] -= ((iDsspare2[SiteID][MacroID][LaneID] >> 8) & 0x7F);
                    }

                    if (iEyeScanMode == 0x1 || iEyeScanMode == 0x3)// vertical scan
                    {
                        if (iPhsOfst == 0 || iPhsOfst == 1) {
                            if (itap1Inside == 0x0) {
                                mVolOfst[SiteID][MacroID][LaneID] = 0;
                            } else if (itap1Type > 0) {
                                mVolOfst[SiteID][MacroID][LaneID] = -1 * tap1Ofst[SiteID][MacroID][LaneID];
                            } else {
                                mVolOfst[SiteID][MacroID][LaneID] = tap1Ofst[SiteID][MacroID][LaneID];
                            }
                        } else {
                            mVolOfst[SiteID][MacroID][LaneID] = eyeMiddle0[SiteID][MacroID][LaneID];
                        }
                    }
                }
            }
            FOREACH_ACTIVESITE_END
    }
    //0830: notice ABIST&ATE mode

    if (jtag.Context == "FASTDIFF") {
        if (false == GeneralEyeScan(vMacroLane_Sel, iEyeScanMode, iEyeScanWin, mPhsOfst, mVolOfst, 1, iMonSlcSel, eyeDiagram_Corner0[index], eyeDiagram_Corner1[index], "ATE", spRXLabel, lCycleNum)) {
            return false;
        }
    }
    else {
        if (false == GeneralEyeScan(vMacroLane_Sel, iEyeScanMode, iEyeScanWin, mPhsOfst, mVolOfst, 1, iMonSlcSel, eyeDiagram_Corner0[index], eyeDiagram_Corner1[index], "ABIST", spRXLabel, lCycleNum)) {
            return false;
        }
    }


    //		FOR_EACH_SITE_BEGIN();
    //		int SiteID = CURRENT_SITE_NUMBER()-1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
            UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
            for (uint uiLaneIndex = 0; uiLaneIndex < vMacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
                UINT LaneID = vMacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];
                eyeMiddle0[SiteID][MacroID][LaneID] = (eyeDiagram_Corner0[index][SiteID][MacroID][LaneID] + eyeDiagram_Corner1[index][SiteID][MacroID][LaneID]) / 2; //TODO: eyeMiddle0 is wrong in PUG, need i index
            }
        }
        FOREACH_ACTIVESITE_END
    if (itap1Inside == 0x1 && itap1Type == 0x2) {
        //			sprintf(label,"GetEyeDiagram_Tap1_Config2_%f_%f_",Vcoef,Temp);
        //			fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
        d2s::d2s_LABEL_BEGIN("GetEyeDiagram_Tap1_Config2_", Global_D2S_Mode);
        selectMacro_MB(vMacroLane_Sel);
        DS.rxRegs.SliceID(0).Broadcast(1);
        DS.rxRegs.settap1pol(0x0).Write2DUT(12);
        //			fr.d2s_LABEL_END();
        d2s::d2s_LABEL_END();
        //			FOR_EACH_SITE_BEGIN();
        //				int SiteID = CURRENT_SITE_NUMBER()-1;

//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int SiteID = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

            for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
                UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
                for (uint uiLaneIndex = 0; uiLaneIndex < vMacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
                    UINT LaneID = vMacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];
                    if (iEyeScanMode == 0x1 || iEyeScanMode == 0x3)// vertical scan
                    {
                        if (iPhsOfst == 0 || iPhsOfst == 1) {
                            mVolOfst[SiteID][MacroID][LaneID] = tap1Ofst[SiteID][MacroID][LaneID];
                        } else {
                            mVolOfst[SiteID][MacroID][LaneID] = eyeMiddle1[SiteID][MacroID][LaneID];
                        }
                    }
                }
            }
            FOREACH_ACTIVESITE_END
        //0830: notice ABIST&ATE mode

        if (jtag.Context == "FASTDIFF") {
            if (false == GeneralEyeScan(vMacroLane_Sel, iEyeScanMode, iEyeScanWin, mPhsOfst, mVolOfst, 1, iMonSlcSel, eyeDiagram_tmp_Corner0, eyeDiagram_tmp_Corner1, "ATE", spRXLabel, lCycleNum)) {
                return false;
            }
        }
        else {
            if (false == GeneralEyeScan(vMacroLane_Sel, iEyeScanMode, iEyeScanWin, mPhsOfst, mVolOfst, 1, iMonSlcSel, eyeDiagram_tmp_Corner0, eyeDiagram_tmp_Corner1, "ABIST", spRXLabel, lCycleNum)) {
                return false;
            }
        }


        //			FOR_EACH_SITE_BEGIN();
        //			int SiteID = CURRENT_SITE_NUMBER()-1;

//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int SiteID = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
            for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
                UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
                for (uint uiLaneIndex = 0; uiLaneIndex < vMacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
                    UINT LaneID = vMacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];
                    eyeMiddle1[SiteID][MacroID][LaneID] = (eyeDiagram_tmp_Corner0[SiteID][MacroID][LaneID] + eyeDiagram_tmp_Corner1[SiteID][MacroID][LaneID]) / 2; //TODO: eyeMiddle1 is wrong in PUG, need i index

                    eyeDiagram_Corner0[index][SiteID][MacroID][LaneID] += tap1Ofst[SiteID][MacroID][LaneID];
                    eyeDiagram_Corner1[index][SiteID][MacroID][LaneID] += tap1Ofst[SiteID][MacroID][LaneID];
                    eyeDiagram_tmp_Corner0[SiteID][MacroID][LaneID] -= tap1Ofst[SiteID][MacroID][LaneID];
                    eyeDiagram_tmp_Corner1[SiteID][MacroID][LaneID] -= tap1Ofst[SiteID][MacroID][LaneID];

                    if (eyeDiagram_Corner0[index][SiteID][MacroID][LaneID] < eyeDiagram_tmp_Corner0[SiteID][MacroID][LaneID]) {
                        eyeDiagram_Corner0[index][SiteID][MacroID][LaneID] = eyeDiagram_tmp_Corner0[SiteID][MacroID][LaneID];
                    }
                    if (eyeDiagram_Corner1[index][SiteID][MacroID][LaneID] > eyeDiagram_tmp_Corner1[SiteID][MacroID][LaneID]) {
                        eyeDiagram_Corner1[index][SiteID][MacroID][LaneID] = eyeDiagram_tmp_Corner1[SiteID][MacroID][LaneID];
                    }
                }
            }
            FOREACH_ACTIVESITE_END
    }
    //	sprintf(label,"GetEyeDiagram_Tap1en_Disable_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("GetEyeDiagram_Tap1en_Disable_", Global_D2S_Mode);
    selectMacro_MB(vMacroLane_Sel);
    DS.rxRegs.SliceID(0).Broadcast(1);
    DS.rxRegs.settap1en(0x0).Write2DUT(12);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //	int SiteID = CURRENT_SITE_NUMBER()-1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        ostringstream str_end_eye;
        ostringstream str_start_eye;

        str_start_eye << "\n" << "===========================Started EyePrint===========================" << endl;
        //	PUT_DATALOG(str_start_eye.str());

        for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
            UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
            for (uint uiLaneIndex = 0; uiLaneIndex < vMacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
                UINT LaneID = vMacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];

                char plot[512][512];

                if (iEyeScanMode == 0x1 || iEyeScanMode == 0x3) {
                    for (int i = iMinPhsOfst; i <= iMaxPhsOfst; i++) {
                        iPhsOfst = i;
                        index = iPhsOfst + 256;

                        for (int ii = 0; ii < 512; ii++) {
                            plot[ii][i + 256] = '*';
                        }

                        int iEyeCornor0, iEyeCornor1;
                        iEyeCornor0 = eyeDiagram_Corner0[index][SiteID][MacroID][LaneID];
                        iEyeCornor1 = eyeDiagram_Corner1[index][SiteID][MacroID][LaneID];

                        for (int ii = iEyeCornor0; ii < iEyeCornor1; ii++) {
                            plot[256 + ii][i + 256] = '.';
                        }
                    }
                } else {
                    //				cout<<"ERROR: Vertical eye scan is not ready!"<<endl;
                    printf("ERROR: Vertical eye scan is not ready!\n");
//                    return false;  //masked by tony 20210817
                }

                string sTestsuiteName;
                //			GET_TESTSUITE_NAME	(sTestsuiteName);

                ostringstream str;
                str << "\n" << "EyeSuite: " << sTestsuiteName;
                str << "\n" << "Site: " << SiteID + 1 << "\n" << "Macro: M" << MacroID << "\n" << "Lane: L" << LaneID << endl << endl;
                //			str<<"M"<<MacroID<<endl;
                //			str<<"L"<<LaneID<<endl;
                str << "          ";
                for (int i = iMinPhsOfst; i <= iMaxPhsOfst; i++) {
                    if (i < 0) {
                        str << '-';
                    }
                }
                str << endl;

                str << "          ";
                for (int i = iMinPhsOfst; i <= iMaxPhsOfst; i++) {
                    if ((abs(i) / 10) % 10) {
                        str << dec << ((abs(i) / 10) % 10);
                    } else {
                        str << ' ';
                    }
                }
                str << endl;
                str << "          ";
                for (int i = iMinPhsOfst; i <= iMaxPhsOfst; i++) {
                    str << dec << (abs(i) % 10);
                }
                str << endl;
                for (int j = 128; j >= -128; j -= 8) {
                    int idx = j + 256;
                    idx = idx >= 512 ? 511 : idx;
                    //				str<<setw(9)<<j<<"|";
                    for (int i = iMinPhsOfst; i <= iMaxPhsOfst; i++) {
                        str << plot[idx][i + 256];
                    }
                    str << endl;
                }
                //			cout<<str.str()<<endl;
                //			PUT_DATALOG(str.str());

            }
        }

        str_end_eye << "\n" << "===========================Ended EyePrint===========================" << endl;
        //	PUT_DATALOG(str_end_eye.str());


        FOREACH_ACTIVESITE_END
    return true;
}

bool AteFwFourPointEyeScan(MACRO_LANE_SEL& MacroLane_Sel, DOUBLE dRefclkMHz, DOUBLE dRefclkMHz2, DOUBLE dDataRate, LANE_UINT& EyeWidth1, LANE_UINT& EyeHeight1, LANE_UINT& EyeWidth2, LANE_UINT& EyeHeight2, STRING sTestMode, STRING spRXLabe, LONG lCycleNum) {
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    char buf_width1[128];
    char buf_height1[128];
    char buf_width2[128];
    char buf_height2[128];

    uint iRefclk0_freqm100 = uint(dRefclkMHz * 100);
    uint iRefclk1_freqm100 = uint(dRefclkMHz2 * 100);
    int iCore_clk_selext_pin_api = giCore_clk_selext_pin_api;
    int iCore_clk_sel_pin_api = giCore_clk_sel_pin_api;
    int iLifeclk2dig_sel_pin_api = giLifeclk2dig_sel_pin_api;
    int iCoreclk_sel_en_api = giCoreclk_sel_en_api;

    EyeWidth1.init(0);
    EyeHeight1.init(0);
    EyeWidth2.init(0);
    EyeHeight2.init(0);

    INT iRateMode = DS.txRegs.gettxratemode();

    STRING spRXName = "";
    if (sTestMode == "ATE") {
        spRXName = "pUDIRXDATA"; //burst pRX Port Pattern
    } else {
#ifndef TestChip
        spRXName = "pHilink_LS"; //for element build error
#else
        spRXName = "pLS";
#endif
    }

    TransactionPort pRX(spRXName);
    //	fr.registerTransactionPort(pRX);

    //	sprintf(label,"FourEyeDiagramFW_Config_%f_%f_DataRate%f",Vcoef,Temp,dDataRate);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("FourEyeDiagramFW_Config_", Global_D2S_Mode);
    //		if (sTestMode=="ATE")
    //		{
    //			pRX.execLabel(spRXLabe,lCycleNum);
    //		}

    selectMacro_MB(MacroLane_Sel);

    //configure APIs of solving width and hight of tap1 eye
    //SRAM.CPAPIRegs.setmcurstb(0x0).setcsmasterifmode(0x2).setmcupwrdb(0x1).Write2DUT(8);
    SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8);

    //Configure refclk frequency, users can get the information at frequency plan
    SRAM.CSAPIRegs.setrefclk0_freqm100_api(iRefclk0_freqm100).Write2DUT(1);
    SRAM.CSAPIRegs.setrefclk1_freqm100_api(iRefclk1_freqm100).Write2DUT(2);

    SRAM.CSAPIRegs.setcore_clk_selext_pin_api(iCore_clk_selext_pin_api).Write2DUT(0);
    SRAM.CSAPIRegs.setcore_clk_sel_pin_api(iCore_clk_sel_pin_api).Write2DUT(0);

    SRAM.CSAPIRegs.setcoreclk_sel_en_api(iCoreclk_sel_en_api).Write2DUT(4);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //		sprintf(label,"FourEyeDiagramFW_Config2_%f_%f_DataRate%f",Vcoef,Temp,dDataRate);
    //		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("FourEyeDiagramFW_Config2_", Global_D2S_Mode);
    if (sTestMode == "ATE") {
        pRX.execLabel(spRXLabe, lCycleNum);
    }


    for (size_t macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        selectMacro(MacroID);

        if (GlobalInitPattern.find("_Case01") != string::npos)
            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[0];
        else if (GlobalInitPattern.find("_Case02") != string::npos)
            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[1];
        else if (GlobalInitPattern.find("_Case03") != string::npos)
            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[2];
        else {
            //				cout << "Can't find valid init pattern !!! Please check pattern name!" << endl;
            printf("Can't find valid init pattern !!! Please check pattern name!\n");
            //				ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (iLifeclk2dig_sel_pin_api != 1 && iLifeclk2dig_sel_pin_api != 0 && iLifeclk2dig_sel_pin_api != -1) {
            //				cout << "Invalid macro has been choose !!! Please check macro ID!" << endl;
            printf("Invalid macro has been choose !!! Please check macro ID!\n");
            //				ERROR_EXIT(TM::ABORT_FLOW);
        }

        SRAM.CSAPIRegs.setlifeclk2dig_sel_pin_api(iLifeclk2dig_sel_pin_api).Write2DUT(0, false);
        for (UINT laneIndex = 0; laneIndex < MacroLane_Sel[macroIndex].vLane.size(); laneIndex++) {
            UINT sliceID = MacroLane_Sel[macroIndex].vLane[laneIndex];
            SRAM.DSAPIRegs.MacroID(MacroID).SliceID(sliceID).Broadcast(0);

            //				uint regAddress_csr8 = 0x1FFC2 - (sliceID * 0x12 * 2) + (8*2);
            //				uint regAddress_csr9 = 0x1FFC2 - (sliceID * 0x12 * 2) + (9*2);

            //				jtag.write(regAddress_csr8 >>1, 0x8 );
            //				jtag.write(regAddress_csr9 >>1, 0x8000  );

            // clear to anti-proof
            uint regAddress_width1 = 0x1FCD6 + 8 * sliceID;
            uint regAddress_height1 = 0x1FCD8 + 8 * sliceID;
            uint regAddress_width2 = 0x1FCDA + 8 * sliceID;
            uint regAddress_height2 = 0x1FCDC + 8 * sliceID;

            jtag.write(regAddress_width1 >> 1, 0x0);
            jtag.write(regAddress_height1 >> 1, 0x0);
            jtag.write(regAddress_width2 >> 1, 0x0);
            jtag.write(regAddress_height2 >> 1, 0x0);

            SRAM.DSAPIRegs.setfw_eye_start_api(0x1).Write2DUT(9, false);
            SRAM.DSAPIRegs.setfw_ate_eye_width_times_api(0x0).Write2DUT(9, false);
            SRAM.DSAPIRegs.setate_ctle_en_api(0x1).Write2DUT(8, false);

            if (iRateMode == 0)
                SRAM.DSAPIRegs.setfw_eye_type_api(0x0).Write2DUT(9, false);
            else if (iRateMode == 1)
                SRAM.DSAPIRegs.setfw_eye_type_api(0x3).Write2DUT(9, false);
            else if (iRateMode == 2)
                SRAM.DSAPIRegs.setfw_eye_type_api(0x1).Write2DUT(9, false);
            else {
                //					cout << "ERROR: INCORRECT RATE MODE!!!!" << endl;
                printf("ERROR: INCORRECT RATE MODE!!!!\n");
                //					ERROR_EXIT(TM::ABORT_FLOW);
            }//Need to be confirm wether to change data rate of TX and Rx

        }
    }

    selectMacro_MB(MacroLane_Sel);
    SRAM.CPAPIRegs.setmcurstb(0x1).Write2DUT(8);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    INT iCheckCount = 0;
    INT iMaxTimeout = 200;
    if(PrintDebugEn) cout<<"doing AteFwFourPointEyeScan ,iMaxTimeout = "<<dec<<iMaxTimeout<<endl;
    EXPECT_RESULT Top_Fsm_Result;
    do {
        iCheckCount++;
        //		WAIT_TIME(5 ms);
//        api->sleep(0.005);
    	TheInst.Wait(0.001 * 6);//2ms
        Check_Top_Fsm_Done(MacroLane_Sel, Top_Fsm_Result);
    } while (Top_Fsm_Result.allpass != true && iCheckCount < iMaxTimeout);
    if(PrintDebugEn) cout<<"doing AteFwFourPointEyeScan ,final iCheckCount = "<<dec<<iCheckCount<<endl;

    //	sprintf(label,"GetFourPointEyeDiagramFW_GET_EMRESULT0_EMRESULT1");
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("GetFourPointEyeDiagramFW_GET_EMRESULT0_EMRESULT1", Global_D2S_Mode);
    for (UINT iMacroIndex = 0; iMacroIndex < MacroLane_Sel.size(); iMacroIndex++) {
        UINT iMacroID = MacroLane_Sel[iMacroIndex].MacroID;
        const vector<UINT>& vLane = MacroLane_Sel[iMacroIndex].vLane;

        for (UINT iLaneIndex = 0; iLaneIndex < vLane.size(); iLaneIndex++) {
            UINT iLaneID = MacroLane_Sel[iMacroIndex].vLane[iLaneIndex];
            selectMacro(iMacroID);
            uint regAddress_width1 = 0x1FCD6 + 8 * iLaneID;
            uint regAddress_height1 = 0x1FCD8 + 8 * iLaneID;
            uint regAddress_width2 = 0x1FCDA + 8 * iLaneID;
            uint regAddress_height2 = 0x1FCDC + 8 * iLaneID;

            sprintf(buf_width1, "FourEyeDiagramFW_Read_M%d_L%d_%s", iMacroID, iLaneID, "Width1");
            jtag.read(regAddress_width1 >> 1, buf_width1);
            sprintf(buf_height1, "FourEyeDiagramFW_Read_M%d_L%d_%s", iMacroID, iLaneID, "Height1");
            jtag.read(regAddress_height1 >> 1, buf_height1);
            sprintf(buf_width2, "FourEyeDiagramFW_Read_M%d_L%d_%s", iMacroID, iLaneID, "Width2");
            jtag.read(regAddress_width2 >> 1, buf_width2);
            sprintf(buf_height2, "FourEyeDiagramFW_Read_M%d_L%d_%s", iMacroID, iLaneID, "Height2");
            jtag.read(regAddress_height2 >> 1, buf_height2);
        }
    }
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //	INT iSiteID = CURRENT_SITE_NUMBER()-1;
//
//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int iSiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
        for (UINT iMacroIndex = 0; iMacroIndex < MacroLane_Sel.size(); iMacroIndex++) {
            UINT iMacroID = MacroLane_Sel[iMacroIndex].MacroID;
            const vector<UINT>& vLane = MacroLane_Sel[iMacroIndex].vLane;

            for (UINT iLaneIndex = 0; iLaneIndex < vLane.size(); iLaneIndex++) {
                UINT iLaneID = MacroLane_Sel[iMacroIndex].vLane[iLaneIndex];

                sprintf(buf_width1, "FourEyeDiagramFW_Read_M%d_L%d_%s", iMacroID, iLaneID, "Width1");
                sprintf(buf_height1, "FourEyeDiagramFW_Read_M%d_L%d_%s", iMacroID, iLaneID, "Height1");
                sprintf(buf_width2, "FourEyeDiagramFW_Read_M%d_L%d_%s", iMacroID, iLaneID, "Width2");
                sprintf(buf_height2, "FourEyeDiagramFW_Read_M%d_L%d_%s", iMacroID, iLaneID, "Height2");

                long long lwidth1 = jtag.getReadValue(buf_width1)[SiteID];
                long long lheight1 = jtag.getReadValue(buf_height1)[SiteID];
                long long lwidth2 = jtag.getReadValue(buf_width2)[SiteID];
                long long lheight2 = jtag.getReadValue(buf_height2)[SiteID];

                EyeWidth1[SiteID][iMacroID][iLaneID] = ((lwidth1 & 0xFF00) >> 8) + ((lwidth1 & 0x00FF) << 8);
                EyeHeight1[SiteID][iMacroID][iLaneID] = ((lheight1 & 0xFF00) >> 8) + ((lheight1 & 0x00FF) << 8);
                EyeWidth2[SiteID][iMacroID][iLaneID] = ((lwidth2 & 0xFF00) >> 8) + ((lwidth2 & 0x00FF) << 8);
                EyeHeight2[SiteID][iMacroID][iLaneID] = ((lheight2 & 0xFF00) >> 8) + ((lheight2 & 0x00FF) << 8);

                hout(DETAIL) << buf_width1 << " = " << dec << EyeWidth1[SiteID][iMacroID][iLaneID] << endl;
                hout(DETAIL) << buf_height1 << " = " << dec << EyeHeight1[SiteID][iMacroID][iLaneID] << endl;
                hout(DETAIL) << buf_width2 << " = " << dec << EyeWidth2[SiteID][iMacroID][iLaneID] << endl;
                hout(DETAIL) << buf_height2 << " = " << dec << EyeHeight2[SiteID][iMacroID][iLaneID] << endl;
            }
        }
        FOREACH_ACTIVESITE_END
    //	sprintf(label,"GetFourPointEyeDiagramFW_Reset_%f_%f_Datarate%f",Vcoef,Temp,dDataRate);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("GetFourPointEyeDiagramFW_Reset_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8);
    Clear_CS_API();
    Clear_DS_API(MacroLane_Sel);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    return true;
}

bool AteFwEyeWidthScan(MACRO_LANE_SEL& MacroLane_Sel, DOUBLE dRefclkMHz, DOUBLE dRefclkMHz2, LANE_UINT& vEyeWidthMin, LANE_UINT& vEyeWidthMax) {

    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    //GET_TEST_INFO;

    char buf_width[128];

    uint iRefclk0_freqm100 = uint(dRefclkMHz * 100);
    uint iRefclk1_freqm100 = uint(dRefclkMHz2 * 100);
    int iCore_clk_selext_pin_api = giCore_clk_selext_pin_api;
    int iCore_clk_sel_pin_api = giCore_clk_sel_pin_api;
    int iLifeclk2dig_sel_pin_api = giLifeclk2dig_sel_pin_api;
    int iCoreclk_sel_en_api = giCoreclk_sel_en_api;

    vEyeWidthMax.init(0);
    vEyeWidthMin.init(0);

    //	sprintf(label,"FourEyeDiagramFWClkPurity_Config_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("FourEyeDiagramFWClkPurity_Config_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);

    //SRAM.CPAPIRegs.setmcurstb(0x0).setcsmasterifmode(0x2).setmcupwrdb(0x1).Write2DUT(8);
    SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8);

    //Configure refclk frequency, users can get the information at frequency plan
    SRAM.CSAPIRegs.setrefclk0_freqm100_api(iRefclk0_freqm100).Write2DUT(1);
    SRAM.CSAPIRegs.setrefclk1_freqm100_api(iRefclk1_freqm100).Write2DUT(2);

    SRAM.CSAPIRegs.setcore_clk_selext_pin_api(iCore_clk_selext_pin_api).Write2DUT(0);
    SRAM.CSAPIRegs.setcore_clk_sel_pin_api(iCore_clk_sel_pin_api).Write2DUT(0);

    SRAM.CSAPIRegs.setcoreclk_sel_en_api(iCoreclk_sel_en_api).Write2DUT(4);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	sprintf(label,"FourEyeDiagramFWClkPurity2_Config_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));

    if(PrintDebugEn) cout<<" GlobalInitPattern = "<<GlobalInitPattern<<endl;

    d2s::d2s_LABEL_BEGIN("FourEyeDiagramFWClkPurity2_Config_", Global_D2S_Mode);
    for (size_t macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        selectMacro(MacroID);

        if (GlobalInitPattern.find("_Case01") != string::npos)
            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[0];
        else if (GlobalInitPattern.find("_Case02") != string::npos)
            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[1];
        else if (GlobalInitPattern.find("_Case03") != string::npos)
            iLifeclk2dig_sel_pin_api = HILINK_INFO[MacroID].life2digChoose[2];
        else {
            //				cout << "Can't find valid init pattern !!! Please check pattern name!" << endl;
            printf("Can't find valid init pattern !!! Please check pattern name!\n");
            //				ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (iLifeclk2dig_sel_pin_api != 1 && iLifeclk2dig_sel_pin_api != 0 && iLifeclk2dig_sel_pin_api != -1) {
            //				cout << "Invalid macro has been choose !!! Please check macro ID!" << endl;
            printf("Invalid macro has been choose !!! Please check macro ID!\n");
            //				ERROR_EXIT(TM::ABORT_FLOW);
        }

        SRAM.CSAPIRegs.setlifeclk2dig_sel_pin_api(iLifeclk2dig_sel_pin_api).Write2DUT(0, false);
        for (UINT laneIndex = 0; laneIndex < MacroLane_Sel[macroIndex].vLane.size(); laneIndex++) {
            UINT sliceID = MacroLane_Sel[macroIndex].vLane[laneIndex];

            SRAM.DSAPIRegs.MacroID(MacroID).SliceID(sliceID).Broadcast(0);

            SRAM.DSAPIRegs.setfw_ate_eye_width_times_api(0x3).Write2DUT(9, false);
            SRAM.DSAPIRegs.setfw_eye_type_api(0x0).Write2DUT(9, false);
            SRAM.DSAPIRegs.setfw_eye_start_api(0x1).Write2DUT(9, false);

            uint regAddress_csr9 = 0x1FFC2 - (sliceID * 0x12 * 2) + (9 * 2);

            jtag.write(regAddress_csr9 >> 1, 0x8300);

            SRAM.DSAPIRegs.setfw_ate_min_eye_width_api(0x0).Write2DUT(16, false);
            SRAM.DSAPIRegs.setfw_ate_max_eye_width_api(0x0).Write2DUT(16, false);
        }
    }

    selectMacro_MB(MacroLane_Sel);
    SRAM.CPAPIRegs.setmcurstb(0x1).Write2DUT(8);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();

    INT iCheckCount = 0;
    INT iMaxTimeout = 200;
    if(PrintDebugEn) cout<<" doing AteFwEyeWidthScan check top done, iMaxTimeout = "<<dec<<iMaxTimeout<<endl;
    EXPECT_RESULT Top_Fsm_Result;
    do {
        iCheckCount++;
//        api->sleep(0.005);
    	TheInst.Wait(0.001 * 8);//2ms
        Check_Top_Fsm_Done(MacroLane_Sel, Top_Fsm_Result);
    } while (Top_Fsm_Result.allpass != true && iCheckCount < iMaxTimeout);
	if(PrintDebugEn) cout<<" doing AteFwEyeWidthScan check top done, final iCheckCount = "<<dec<<iCheckCount<<endl;
    
    if (0 == Global_D2S_Mode){
//          api->sleep(0.5);
//    	TheInst.Wait(5*1000);
    	TheInst.Wait(0.001 * 2);//2ms
    } 

    d2s::d2s_LABEL_BEGIN("GetFourPointEyeDiagramClkPurity_GET_EMRESULT0_EMRESULT1", Global_D2S_Mode);
    for (UINT iMacroIndex = 0; iMacroIndex < MacroLane_Sel.size(); iMacroIndex++) {
        UINT iMacroID = MacroLane_Sel[iMacroIndex].MacroID;
        selectMacro(iMacroID);
        const vector<UINT>& vLane = MacroLane_Sel[iMacroIndex].vLane;
        for (UINT iLaneIndex = 0; iLaneIndex < vLane.size(); iLaneIndex++) {
            UINT iLaneID = MacroLane_Sel[iMacroIndex].vLane[iLaneIndex];
            sprintf(buf_width, "FourEyeDiagramFWClkPurity_Read_M%d_L%d_%s", iMacroID, iLaneID, "Width");
            uint regAddress = 0x1FFC2 - (iLaneID * 0x12 * 2) + (16 * 2);
            jtag.read(regAddress >> 1, buf_width);
        }
    }
    d2s::d2s_LABEL_END();

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int iSiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
        for (UINT iMacroIndex = 0; iMacroIndex < MacroLane_Sel.size(); iMacroIndex++) {
            UINT iMacroID = MacroLane_Sel[iMacroIndex].MacroID;
            const vector<UINT>& vLane = MacroLane_Sel[iMacroIndex].vLane;

            for (UINT iLaneIndex = 0; iLaneIndex < vLane.size(); iLaneIndex++) {
                UINT iLaneID = MacroLane_Sel[iMacroIndex].vLane[iLaneIndex];
                sprintf(buf_width, "FourEyeDiagramFWClkPurity_Read_M%d_L%d_%s", iMacroID, iLaneID, "Width");
                long long lwidth = jtag.getReadValue(buf_width)[SiteID];

//                if(PrintDebugEn) cout<<"AteFwEyeWidthScan "<<"getReadValue get the lwidth="<<lwidth<<endl;
                vEyeWidthMin[SiteID][iMacroID][iLaneID] = lwidth & 0x00FF;
                vEyeWidthMax[SiteID][iMacroID][iLaneID] = ((lwidth & 0xFF00) >> 8);


            }
        }
        FOREACH_ACTIVESITE_END

    d2s::d2s_LABEL_BEGIN("GetFourPointEyeDiagramClkPurity_Reset_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8);
    Clear_CS_API();
    Clear_DS_API(MacroLane_Sel);
    d2s::d2s_LABEL_END();
    return true;
}

//==============================================================================
// Function: GetFourPointEyeDiagram
// - Function to get four points eye(inner eye height and eye width)
// - showInner: 0=inner eye scan, 1=outer eye scan
// - eyeScanWin: BER definition
//               for inner eye scan BER=1/(320*2^eyeScanWin);
//               for outer eye scan BER=eyeScanWin/40;
// - monSlcSel: channel select, 0=I, 1=Q, 2=Ib, 3=Qb
// - tap1Inside: 0=eye diagram without tap1,
//               1=eye diagram with tap1
// - tap1Type: 0=plot the lower side of tap1 eye; 1=plot the upper side of tap1 eye;
//              2=plot the composite tap1 eye; 3=forbidden;
// - eyeDiagram[4]: the four point eye diagram scan result.
//==============================================================================

bool GetFourPointEyeDiagram(MACRO_LANE_SEL& vMacroLane_Sel, uint iShowInner, uint iEyeScanWin, uint iMonSlcSel, uint itap1Inside, uint itap1Type, LANE_UINT& vEyeWidth, LANE_UINT& vEyeHeight) {
    uint iEyeScanMode;
    LANE_UINT uiRatemode;
    LANE_INT mPhsOfset, mVolOfst, tap1Ofst;
    LANE_INT pol1Bot, pol1Top, pol1Left, pol1Right;
    LANE_INT pol0Bot, pol0Top, pol0Left, pol0Right;
    LANE_UINT iDfefxtap1cen;
    LANE_UINT iDsspare2;

    uiRatemode.init(0);

    mPhsOfset.init(0);
    mVolOfst.init(0);
    tap1Ofst.init(0);

    pol1Bot.init(0);
    pol1Top.init(0);
    pol1Left.init(0);
    pol1Right.init(0);

    pol0Bot.init(0);
    pol0Top.init(0);
    pol0Left.init(0);
    pol0Right.init(0);

    iDfefxtap1cen.init(0);
    iDsspare2.init(0);

    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();
    //GET_TEST_INFO;

    char IDstring[128] = "";

    //	sprintf(label,"FourEyeDiagram_EyeMonitor_Config_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("FourEyeDiagram_EyeMonitor_Config_", Global_D2S_Mode);
    selectMacro_MB(vMacroLane_Sel);
    DS.rxRegs.SliceID(0).Broadcast(1);
    DS.rxRegs.setemtaskctrl(0x0).seteyemontask(0x0).Write2DUT(25);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();

    if (iShowInner == 0x0) {
        iEyeScanMode = 1;
    } else {
        iEyeScanMode = 3;
    }

    if (itap1Inside == 0x1) {
        int itap1Pol = (itap1Type > 0) ? 0x1 : 0x0;
        //		sprintf(label,"FourEyeDiagram_Tap1_Config1_%f_%f_",Vcoef,Temp);
        //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
        d2s::d2s_LABEL_BEGIN("FourEyeDiagram_Tap1_Config1_", Global_D2S_Mode);
        selectMacro_MB(vMacroLane_Sel);
        DS.rxRegs.SliceID(0).Broadcast(1);
        DS.rxRegs.settap1en(0x1).settap1pol(itap1Pol).Write2DUT(12);
        //		fr.d2s_LABEL_END();
        d2s::d2s_LABEL_END();
        // readback
        //		sprintf(label,"FourPointEyeDiagram_ReadBack_DSRXCSR51_%f_%f_",Vcoef,Temp);
        //		fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
        d2s::d2s_LABEL_BEGIN("FourPointEyeDiagram_ReadBack_DSRXCSR51_", Global_D2S_Mode);
        for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
            UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
            selectMacro(MacroID);
            for (uint uiLaneIndex = 0; uiLaneIndex < vMacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
                UINT LandID = vMacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];
                DS.rxRegs.MacroID(MacroID).SliceID(LandID).Broadcast(0);
                DS.rxExtRegs.SliceID(LandID).Broadcast(0);
                sprintf(IDstring, "DSRXCSR51_%d_%d", MacroID, LandID);
                DS.rxRegs.Read2IDString(51, IDstring);
                sprintf(IDstring, "DSRXEXTCSR45_%d_%d", MacroID, LandID);
                DS.rxExtRegs.Read2IDString(45, IDstring);
            }
        }
        //		fr.d2s_LABEL_END();
        d2s::d2s_LABEL_END();
        // get readback value
        //		FOR_EACH_SITE_BEGIN();
        //			INT iSiteID = CURRENT_SITE_NUMBER()-1;

//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int iSiteID = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
            for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
                UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
                for (uint uiLaneIndex = 0; uiLaneIndex < vMacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
                    UINT LaneID = vMacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];
                    uint val;
                    sprintf(IDstring, "DSRXCSR51_%d_%d", MacroID, LaneID);
                    val = (UINT) jtag.getReadValue(IDstring)[SiteID];
                    iDfefxtap1cen[SiteID][MacroID][LaneID] = HILINK_Regs_Base::get_bits(val, DS.rxRegs.REG_INFO.dfefxtap1cen());

                    sprintf(IDstring, "DSRXEXTCSR45_%d_%d", MacroID, LaneID);
                    val = (UINT) jtag.getReadValue(IDstring)[SiteID];
                    iDsspare2[SiteID][MacroID][LaneID] = HILINK_Regs_Base::get_bits(val, DS.rxExtRegs.REG_INFO.dsspare2());

                    tap1Ofst[SiteID][MacroID][LaneID] = (iDfefxtap1cen[SiteID][MacroID][LaneID] & 0x7F);
                    if (0x0 != (iDfefxtap1cen[SiteID][MacroID][LaneID] & 0x80)) {
                        tap1Ofst[SiteID][MacroID][LaneID] = -1 * tap1Ofst[SiteID][MacroID][LaneID];
                    }

                    if (0x0 != (iDsspare2[SiteID][MacroID][LaneID] * 0x8000)) {
                        tap1Ofst[SiteID][MacroID][LaneID] += ((iDsspare2[SiteID][MacroID][LaneID] >> 8) & 0x7F);
                    } else {
                        tap1Ofst[SiteID][MacroID][LaneID] -= ((iDsspare2[SiteID][MacroID][LaneID] >> 8) & 0x7F);
                    }

                    if (itap1Type > 0) {
                        mVolOfst[SiteID][MacroID][LaneID] = -1 * tap1Ofst[SiteID][MacroID][LaneID];
                    } else {
                        mVolOfst[SiteID][MacroID][LaneID] = tap1Ofst[SiteID][MacroID][LaneID];
                    }
                }
            }
            FOREACH_ACTIVESITE_END
    } else {
        mVolOfst.init(0);
    }


    if (false == GeneralEyeScan(vMacroLane_Sel, iEyeScanMode, iEyeScanWin, mPhsOfset, mVolOfst, 1, iMonSlcSel, pol1Bot, pol1Top)) {
        return false;
    }

    if (false == GeneralEyeScan(vMacroLane_Sel, iEyeScanMode - 1, iEyeScanWin, mPhsOfset, mVolOfst, 1, iMonSlcSel, pol1Left, pol1Right)) {
        return false;
    }


    if ((0x1 == itap1Inside) && (0x2 == itap1Type)) {
        //		sprintf(label,"FourEyeDiagram_Tap1_Config2_%f_%f_",Vcoef,Temp);
        //		fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
        d2s::d2s_LABEL_BEGIN("FourEyeDiagram_Tap1_Config2_", Global_D2S_Mode);
        selectMacro_MB(vMacroLane_Sel);
        DS.rxRegs.SliceID(0).Broadcast(1);
        DS.rxRegs.settap1pol(0x0).Write2DUT(12);
        //		fr.d2s_LABEL_END();
        d2s::d2s_LABEL_END();
        //		FOR_EACH_SITE_BEGIN();
        //			INT iSiteID = CURRENT_SITE_NUMBER()-1;

//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int iSiteID = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
            for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
                UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
                for (uint uiLaneIndex = 0; uiLaneIndex < vMacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
                    UINT LaneID = vMacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];
                    mVolOfst[SiteID][MacroID][LaneID] = tap1Ofst[SiteID][MacroID][LaneID];
                }
            }
            FOREACH_ACTIVESITE_END
        if (false == GeneralEyeScan(vMacroLane_Sel, iEyeScanMode, iEyeScanWin, mPhsOfset, mVolOfst, 1, iMonSlcSel, pol0Bot, pol0Top)) {
            return false;
        }


        //		FOR_EACH_SITE_BEGIN();
        //			INT iSiteID = CURRENT_SITE_NUMBER()-1;

//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int iSiteID = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

            for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
                UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
                for (uint uiLaneIndex = 0; uiLaneIndex < vMacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
                    UINT LaneID = vMacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];

                    pol1Bot[SiteID][MacroID][LaneID] += tap1Ofst[SiteID][MacroID][LaneID];
                    pol1Top[SiteID][MacroID][LaneID] += tap1Ofst[SiteID][MacroID][LaneID];

                    pol0Bot[SiteID][MacroID][LaneID] -= tap1Ofst[SiteID][MacroID][LaneID];
                    pol0Top[SiteID][MacroID][LaneID] -= tap1Ofst[SiteID][MacroID][LaneID];

                    if (pol1Bot[SiteID][MacroID][LaneID] < pol0Bot[SiteID][MacroID][LaneID]) {
                        pol1Bot[SiteID][MacroID][LaneID] = pol0Bot[SiteID][MacroID][LaneID];
                    }
                    if (pol0Top[SiteID][MacroID][LaneID] < pol1Top[SiteID][MacroID][LaneID]) {
                        pol1Top[SiteID][MacroID][LaneID] = pol0Top[SiteID][MacroID][LaneID];
                    }
                }
            }
            FOREACH_ACTIVESITE_END
        if (false == GeneralEyeScan(vMacroLane_Sel, iEyeScanMode - 1, iEyeScanWin, mPhsOfset, mVolOfst, 1, iMonSlcSel, pol0Left, pol0Right)) {
            return false;
        }

        //		FOR_EACH_SITE_BEGIN();
        //			INT iSiteID = CURRENT_SITE_NUMBER()-1;

//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int iSiteID = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
            for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
                UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
                for (uint uiLaneIndex = 0; uiLaneIndex < vMacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
                    UINT LaneID = vMacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];

                    if (pol1Left[SiteID][MacroID][LaneID] < pol0Left[SiteID][MacroID][LaneID]) {
                        pol1Left[SiteID][MacroID][LaneID] = pol0Left[SiteID][MacroID][LaneID];
                    }

                    if (pol0Right[SiteID][MacroID][LaneID] < pol1Right[SiteID][MacroID][LaneID]) {
                        pol1Right[SiteID][MacroID][LaneID] = pol0Right[SiteID][MacroID][LaneID];
                    }
                }
            }
            FOREACH_ACTIVESITE_END
    }

    //	FOR_EACH_SITE_BEGIN();
    //		INT iSiteID = CURRENT_SITE_NUMBER()-1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int iSiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT uiMacroIndex = 0; uiMacroIndex < vMacroLane_Sel.size(); uiMacroIndex++) {
            UINT MacroID = vMacroLane_Sel[uiMacroIndex].MacroID;
            for (uint uiLaneIndex = 0; uiLaneIndex < vMacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
                UINT LaneID = vMacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];

                vEyeWidth[SiteID][MacroID][LaneID] = pol1Right[SiteID][MacroID][LaneID] - pol1Left[SiteID][MacroID][LaneID];
                vEyeHeight[SiteID][MacroID][LaneID] = pol1Top[SiteID][MacroID][LaneID] - pol1Bot[SiteID][MacroID][LaneID];
            }
        }
        FOREACH_ACTIVESITE_END

    return true;
}


//Alos
//==============================================================================
// Function: EnableAlos
// - This function is used to enable signal loss detection
//==============================================================================

void EnableAlos(const STRING& JtagContext) {
    DS.rxRegs.setrxdigdetclkbufen(0x1).Write2DUT(38);
    DS.rxRegs.setrxsigdetclkdiv(0x03).Write2DUT(38);
    DS.rxRegs.setrxsigdetclkdlysel(0x0).Write2DUT(38);
    DS.rxRegs.setrxsigdethyst(0x02).Write2DUT(39);
    //	if(JtagContext == "DEFAULT")
    //		DS.rxRegs.setrxsigdetvthres(0x02).Write2DUT(39);//ABIST use 2
    //	else
    DS.rxRegs.setrxsigdetvthres(0x03).Write2DUT(39); //ATE use 3
    DS.rxRegs.setsigdetwin(0x06).Write2DUT(40);
    DS.rxRegs.setsigdetthrs3(0x20).Write2DUT(43);

    DS.rxRegs.setsigdettxrxstat(0x1).Write2DUT(40);
    DS.rxRegs.setsigdetpmamode(0x0).Write2DUT(40);
    DS.rxRegs.setsigdetmanual(0x0).Write2DUT(40);
    DS.rxRegs.setsigdetthrselman(0x0).Write2DUT(40);
    DS.rxRegs.setsigdetthrcfgsel(0x0).Write2DUT(41);
    DS.rxRegs.setrxsigdetcalpwrdb(0x1).Write2DUT(38);

    DS.rxRegs.setrxsigdetpwrdb(0x1).Write2DUT(38);
    DS.rxRegs.setsigdeten(0x1).Write2DUT(40);
}

//==============================================================================
// Function: DisableAlos
// - This function is used to disable signal loss detection.
//==============================================================================

void DisableAlos() {
    DS.rxRegs.setrxsigdetpwrdb(0).Write2DUT(38);
    DS.rxRegs.setsigdeten(0).Write2DUT(40);
}

void Rx_ATE_Setup(MACRO_LANE_SEL& MacroLane_Sel, vector<int> vCTLESetting, string& sUseFixCTLE, string& patternType) {
    //=============================================
    // Device Setup
    //=============================================
    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();
    //GET_TEST_INFO;

    //	sprintf(label,"H30_MPB_RX_ATE_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("H30_MPB_RX_ATE_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    DS.rxRegs.SliceID(0).Broadcast(1);

    DS.rxRegs.setcdrfreeze(0).Write2DUT(12);
    //		jtag.wait(100 us);
    jtag.wait(0.0001);

    if (sUseFixCTLE == "YES") {
        DS.rxRegs.setctleactgn1(vCTLESetting[0]).Write2DUT(1);
        DS.rxRegs.setctleactgn2(vCTLESetting[1]).Write2DUT(2);
        DS.rxRegs.setctleactgn3(vCTLESetting[2]).Write2DUT(3);
        DS.rxRegs.setctleboostc1(vCTLESetting[3]).Write2DUT(1);
        DS.rxRegs.setctleboostc2(vCTLESetting[4]).Write2DUT(2);
        DS.rxRegs.setctleboostc3(vCTLESetting[5]).Write2DUT(3);
    } else if (sUseFixCTLE == "NO") {
        //		SetCtle(MacroLane_Sel);//todo : use adaptation value
    } else {
        //			cout << "ERROR: Incorrect CTLE setting, please check primary set!!" << endl;
        printf("ERROR: Incorrect CTLE setting, please check primary set!!\n");
        //			ERROR_EXIT(TM::ABORT_FLOW);
    }


    EnableRxPrbsCheck(patternType);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();

}

void RxSearch_CheckClockMonitor(double dDataRate, string sPattern_Type, vector<string> vConnectedLanes) {
    //If first test fail, then it has risk of ClockMonitor issue, we need to redo cmon check
    //Check Clock Monitor again
    //	Primary.label("MPB_LaneAlign_x12");
    //	FLUSH();
    //	double dDataRate_bps = dDataRate * 1e+12;
    //	UDI().setCalibrationPoint(dDataRate_bps,sPattern_Type,"pUDIRXCLOCKS");
    //
    //	// connect lanes or pins and switch clock multiplication path
    //	for(vector<string>::iterator iter=vConnectedLanes.begin(); iter!=vConnectedLanes.end(); iter++) {
    //		if(UDI().isLane(*iter)) {
    //			UDI().lane(*iter).connect();
    //			UDI().lane(*iter).setDataRate(dDataRate_bps);
    //			UDI().lane(*iter).activateCalibrationPoint(NAUTILUS::MUXCLKOFFSET);
    //		}
    //		else if(UDI().isPin(*iter)){
    //			UDI().pin(*iter).connect();
    //			UDI().pin(*iter).setDataRate(dDataRate_bps);
    //			UDI().pin(*iter).activateCalibrationPoint(NAUTILUS::MUXCLKOFFSET);
    //		}
    //	}
}



//ADC

//==============================================================================
// Function: GetTemperature
// - This function is used to get on-die temperature.
// - This function only can be used when this macro has a ServiceSlice.
// - Return value is temperature value.
//==============================================================================

bool GetTemperature(MACRO_LANE_SEL& vMacroLane_Sel, MACRO_DOUBLE &iTemperature) {

    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();
    //GET_TEST_INFO;
    iTemperature.init(999);

    MACRO_DOUBLE iDpmfinetuneen;
    iDpmfinetuneen.init(999);

    // ************************follow UFLEX setting end**************************//
    //		sprintf(label,"GET_TEMPERATURE_%f_%f_",Vcoef,Temp);
    //		fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("GET_TEMPERATURE_", Global_D2S_Mode);
    selectMacro_MB(vMacroLane_Sel);
    CS.clkRegs.SliceID(0).Broadcast(1);
    CS.clkRegs.setssadcabsmeasen(0x1).Write2DUT(39); // 800ms is the reference
    CS.clkRegs.setdpmdettasksel(0x1).Write2DUT(26); // Select temperature detection
    CS.clkRegs.setcstopfsm_cal_task_sel(0x0).Write2DUT(58); // No MISC task is selected
    CS.clkRegs.setcstopfsm_cal_start(0x0).Write2DUT(58);
    CS.clkRegs.setcstopfsm_cal_start(0x1).Write2DUT(58); // Start CS TOP FSM

    //		fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    INT iMaxTimeout = 50;
    DOUBLE wait_interval_ms = 20;
    EXPECT_RESULT CS_TOPFSM_CAL_DONE_Result;

    WaitDone(vMacroLane_Sel, "Macro", CS.clkRegs.REG_INFO.cstopfsm_cal_done(), 1, iMaxTimeout, wait_interval_ms, CS_TOPFSM_CAL_DONE_Result);

    //	sprintf(label,"getCSDBG_CSR51_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("getCSDBG_CSR51_", Global_D2S_Mode);
    for (UINT macroIndex = 0; macroIndex < vMacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = vMacroLane_Sel[macroIndex].MacroID;
        selectMacro(MacroID);
        char IDstring[128] = "";
        sprintf(IDstring, "csdbg_csr51_onMacro%i", MacroID);
        CS.clkdebug.Read2IDString(51, IDstring);
    }
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //		INT SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (uint macroIndex = 0; macroIndex < vMacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = vMacroLane_Sel[macroIndex].MacroID;
            char IDstring[128] = "";
            sprintf(IDstring, "csdbg_csr51_onMacro%i", MacroID);

            uint val = (UINT) jtag.getReadValue(IDstring)[SiteID];
            iTemperature[SiteID][MacroID] = HILINK_Regs_Base::get_bits(val, CS.clkdebug.REG_INFO.temprd());

            hout(DETAIL) << "		temprd = " << iTemperature[SiteID][MacroID] << endl;
            iTemperature[SiteID][MacroID] = ((iTemperature[SiteID][MacroID] - 466) / 2) - 40;

            hout(DETAIL) << "		iTemperature = " << iTemperature[SiteID][MacroID] << endl;
        }
        FOREACH_ACTIVESITE_END
    //		SET_USER_DOUBLE("ReadBack_Temp", 1, iTemperature[SiteID][vMacroLane_Sel[0].MacroID]);
    //	FOR_EACH_SITE_END();
    return true;
}

//==============================================================================
// Function: SsGetAdcData
// - This function is used to read SS ATB voltage through ADC.
// - adcFreq: ADC work frequency, 0=25KHz, 1=50KHz, 2=100KHz, 3=200KHz, 4=400KHz
//                                5=800KHz, 6=1.6Mhz, 7=3.2MHz
// - useVbgAsRef: indicate which reference voltage select, 0=hvcc(1200mV), 1=bandgap(800mV).
// - decmFactor: decimation Factor slect, 0=256, 1=512, 2=1024, 3=2048.
// - refVoltage: accurate reference voltage in mV.
// - avgTime: average time for ADC reading.
// - returnType: return type select, 0=return volatge value in mV, 1=return dfdata.
//==============================================================================

void SsGetAdcData(MACRO_LANE_SEL &MacroLane_Sel, MACRO_DOUBLE &adcdataresult, uint adcFreq, uint useVbgAsRef, uint decmFactor, uint refVoltage, uint avgTime, uint returnType, uint adcinputsel) {
    MACRO_INT voltageVal;
    uint fullSteps;
    MACRO_INT dfData;
    uint checkCount;
    MACRO_INT dfDataMax, dfDataMin, dfDataCurrent;
    MACRO_INT mSsdfdataPerMacro;
    MACRO_INT SSDFRefCode;
    uint i = 0;
    uint j = 0;
    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();
    //GET_TEST_INFO;

    mSsdfdataPerMacro.init(0);
    voltageVal.init(0);
    dfData.init(0);

    //	sprintf(label,"MPB_dpmfinetuneen_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("MPB_dpmfinetuneen_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    CS.clkRegs.SliceID(0).Broadcast(1);
    CS.clkRegs.setdpmfinetuneen(0x0).Write2DUT(58);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    INT iMaxTimeout = 500;
    DOUBLE wait_interval_ms = 5;
    EXPECT_RESULT CS_DFCOMPSTATUS_Result;
    //while(0x1 == CSTOPFSM_CAL_START (CS_CSR58 bit[15])) {;}
    WaitDone(MacroLane_Sel, "Macro", CS.clkRegs.REG_INFO.cstopfsm_cal_start(), 0, iMaxTimeout, wait_interval_ms, CS_DFCOMPSTATUS_Result);

    //Configuration
    //	sprintf(label,"MPB_SsGetAdcDataSsGetAdcData_SETUP1_%d_%f_%f",adcinputsel,Vcoef,Temp);
    //fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("MPB_SsGetAdcDataSsGetAdcData_SETUP1_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    CS.clkRegs.SliceID(0).Broadcast(1);
    CS.clkRegs.setssadcpwrdb(0x1)// power up ADC
            .Write2DUT(35);
    CS.clkRegs.setssadctsten(0x0) // ADC mission mode
            .setssadcvcmctrl(0x1) // set internal common mode voltage to 550mV
            .Write2DUT(39);
    CS.clkRegs.setssdecmfactor(decmFactor)
            .setssdforder(0x0) // sync_1
            .setssadcconvmode(0x0)
            .Write2DUT(53);
    // select hvcc (1200mV) or bandgap (800mV) is ADC reference
    CS.clkRegs.setssadcabsmeasen(useVbgAsRef).Write2DUT(39);
    CS.clkRegs.setssadcclkdiv(adcFreq).Write2DUT(52);

    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    fullSteps = (0x1 << decmFactor) * 256;

    for (j = 0; j < avgTime; j++) {
        MACRO_DOUBLE compStatusPre;
        compStatusPre.init(0);

        //		sprintf(label,"MPB_ADCRSTB_Disable_%d_%f_%f_",adcinputsel,Vcoef,Temp);
        //		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
        d2s::d2s_LABEL_BEGIN("MPB_ADCRSTB_Disable_", Global_D2S_Mode);
        selectMacro_MB(MacroLane_Sel);
        CS.clkRegs.SliceID(0).Broadcast(1);
        CS.clkRegs.setssadcrstb(0x0).Write2DUT(39);
        //		fr.d2s_LABEL_END();
        d2s::d2s_LABEL_END();
        char IDstring[128] = "";

        //		sprintf(label,"SSDFCOMPSTATUS_ReadBack_CSCSR54_%f_%f_",Vcoef,Temp);
        //		fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
        d2s::d2s_LABEL_BEGIN("SSDFCOMPSTATUS_ReadBack_CSCSR54_", Global_D2S_Mode);
        for (UINT uiMacroIndex = 0; uiMacroIndex < MacroLane_Sel.size(); uiMacroIndex++) {
            UINT MacroID = MacroLane_Sel[uiMacroIndex].MacroID;
            selectMacro(MacroID);
            CS.clkRegs.MacroID(MacroID).SliceID(0).Broadcast(0);
            sprintf(IDstring, "CSCSR54_%d", MacroID);
            CS.clkRegs.Read2IDString(54, IDstring);
        }
        //		fr.d2s_LABEL_END();
        d2s::d2s_LABEL_END();
        //		FOR_EACH_SITE_BEGIN();
        //		INT SiteID = CURRENT_SITE_NUMBER() - 1;

//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int SiteID = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
                sprintf(IDstring, "CSCSR54_%d", MacroID);
                uint val = jtag.getReadValue(IDstring)[SiteID];
                compStatusPre[SiteID][MacroID] = HILINK_Regs_Base::get_bits(val, CS.clkRegs.REG_INFO.ssdfcompstatus());
                SSDFRefCode[SiteID][MacroID] = (0 == compStatusPre[SiteID][MacroID]) ? 0x0 : 0xFFF;
                hout(DETAIL) << "compStatusPre: Site" << SiteID << " Macro" << MacroID << " = " << compStatusPre[SiteID][MacroID] << endl;
            }
            FOREACH_ACTIVESITE_END
        //Dynamic Write SSDFRefCode
        MACRO_INT CSRvalue;
        CSR_READ(MacroLane_Sel, CS.clkRegs, 53, CSRvalue);
        Update_CSReg_ForDynamicWrite(MacroLane_Sel, CS.clkRegs.REG_INFO.ssdfrefcode(), SSDFRefCode, CSRvalue);

        //		sprintf(label,"MPB_SSDFREFCODE_Dynamci_Write_%f_%f_",Vcoef,Temp);
        //		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
        d2s::d2s_LABEL_BEGIN("MPB_SSDFREFCODE_Dynamci_Write_", Global_D2S_Mode);
        for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            uint MacroID = MacroLane_Sel[macroIndex].MacroID;
            selectMacro(MacroID);

            ostringstream id53;
            id53 << "CSR53_" << "_M" << MacroID << jtag.Context;
            map<int, long long> tmp;
            parseSiteDataFromMacroInt(tmp, CSRvalue, MacroID);
            CS.clkRegs.Write2DUT_DYN(53, tmp, id53.str());

        }
        //		fr.d2s_LABEL_END();
        d2s::d2s_LABEL_END();

        //		sprintf(label,"MPB_SSADCRSTB_Enable_%d_%f_%f_",adcinputsel,Vcoef,Temp);
        //		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
        d2s::d2s_LABEL_BEGIN("MPB_SSADCRSTB_Enable_", Global_D2S_Mode);
        selectMacro_MB(MacroLane_Sel);
        CS.clkRegs.SliceID(0).Broadcast(1);
        CS.clkRegs.setssadcrstb(0x1).Write2DUT(39);
        //		fr.d2s_LABEL_END();
        d2s::d2s_LABEL_END();
        // wait for CS ADC df ready
        checkCount = 0;
        iMaxTimeout = 50;
        wait_interval_ms = 2;
        EXPECT_RESULT compStatusPre_Result;

        WaitDoneMacro_Value_Update(MacroLane_Sel, CS.clkRegs.REG_INFO.ssdfcompstatus(), compStatusPre, iMaxTimeout, wait_interval_ms, compStatusPre_Result);

        //		sprintf(label,"Getssdfdata_%f_%f_",Vcoef,Temp);
        //		fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
        d2s::d2s_LABEL_BEGIN("Getssdfdata_", Global_D2S_Mode);
        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            char IDstring[128] = "";
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            selectMacro(MacroID);
            CS.clkRegs.MacroID(MacroID).SliceID(0).Broadcast(0);
            sprintf(IDstring, "SSDFDATA_onMacro%i", MacroID);
            CS.clkRegs.Read2IDString(54, IDstring);
        }
        //		fr.d2s_LABEL_END();
        d2s::d2s_LABEL_END();
        //		FOR_EACH_SITE_BEGIN();
        //		INT SiteID = CURRENT_SITE_NUMBER() - 1;

//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int SiteID = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

            for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
                char IDstring[128] = "";
                sprintf(IDstring, "SSDFDATA_onMacro%i", MacroID);
                UINT val = (UINT) jtag.getReadValue(IDstring)[SiteID];
                mSsdfdataPerMacro[SiteID][MacroID] = HILINK_Regs_Base::get_bits(val, CS.clkRegs.REG_INFO.ssdfdata());
                dfData[SiteID][MacroID] += mSsdfdataPerMacro[SiteID][MacroID];
            }
            FOREACH_ACTIVESITE_END

    }

    // Power down ADC to save power
    //	sprintf(label,"MPB_SsGetAdcDataSsGetAdcData_SETUP2_%d_%f_%f_",adcinputsel,Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("MPB_SsGetAdcDataSsGetAdcData_SETUP2_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    CS.clkRegs.SliceID(0).Broadcast(1);
    CS.clkRegs.setssadcpwrdb(0x0) // power down ADC
            .Write2DUT(35);
    CS.clkRegs.setssadcrstb(0x0) // keep ADC in reset state
            .Write2DUT(39);
    CS.clkRegs.setdpmfinetuneen(0x1)
            .setcstopfsm_cal_start(0x1)
            .Write2DUT(58);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //	INT SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            dfData[SiteID][MacroID] = dfData[SiteID][MacroID] / avgTime;
            voltageVal[SiteID][MacroID] = dfData[SiteID][MacroID] * refVoltage / fullSteps;

            if (0x0 == returnType) {
                adcdataresult[SiteID][MacroID] = voltageVal[SiteID][MacroID];
                hout(GENERAL) << "adcdataresult Site= " << SiteID << " Macro= " << MacroID << "Value= " << hex << "0x" << adcdataresult[SiteID][MacroID] << endl;
            } else {
                adcdataresult[SiteID][MacroID] = dfData[SiteID][MacroID];
                hout(GENERAL) << "adcdataresult Site= " << SiteID << " Macro= " << MacroID << "Value= " << hex << "0x" << adcdataresult[SiteID][MacroID] << endl;

            }
        }
        FOREACH_ACTIVESITE_END
}



//==============================================================================
// Function: CsGetAdcData
// - This function is used to read CS ATB voltage through ADC.
// - adcFreq: ADC work frequency, 0=25KHz, 1=50KHz, 2=100KHz, 3=200KHz, 4=400KHz
//                                5=800KHz, 6=1.6Mhz, 7=3.2MHz
// - useVbgAsRef: indicate which reference voltage select, 0=hvcc(1200mV), 1=bandgap(800mV).
// - decmFactor: decimation Factor slect, 0=256, 1=512, 2=1024, 3=2048.
// - refVoltage: accurate reference voltage in mV.
// - avgTime: average time for ADC reading.
// - returnType: return type select, 0=return volatge value in mV, 1=return dfdata.
//==============================================================================

void CsGetAdcData(MACRO_LANE_SEL &MacroLane_Sel, MACRO_DOUBLE &adcdataresult, uint adcFreq, uint useVbgAsRef, uint decmFactor, uint refVoltage, uint avgTime, uint returnType) {
    MACRO_INT voltageVal, CSDFRefCode;
    uint fullSteps;
    MACRO_INT dfData;
    uint checkCount;
    uint j;
    MACRO_INT mCsdfdataPerMacro;

    mCsdfdataPerMacro.init(0);
    voltageVal.init(0);
    dfData.init(0);

    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();
    //GET_TEST_INFO;

    //	sprintf(label,"MPB_dpmfinetuneen_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("MPB_dpmfinetuneen_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    CS.clkRegs.SliceID(0).Broadcast(1);
    CS.clkRegs.setdpmfinetuneen(0x0).Write2DUT(58);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //while(0x1 == CSTOPFSM_CAL_START (CS_CSR58 bit[15])) {;}
    INT iMaxTimeout = 30;
    DOUBLE wait_interval_ms = 10;
    EXPECT_RESULT CS_DFCOMPSTATUS_Result;
    WaitDone(MacroLane_Sel, "Macro", CS.clkRegs.REG_INFO.cstopfsm_cal_start(), 0, iMaxTimeout, wait_interval_ms, CS_DFCOMPSTATUS_Result);

    //	sprintf(label,"MPB_CsGetAdcData_SETUP1_%f_%f_",Vcoef,Temp);
    //fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("MPB_CsGetAdcData_SETUP1_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    CS.clkRegs.SliceID(0).Broadcast(1);
    // Configuration
    CS.clkRegs.setadcpwrdb(0x1) // power up ADC
            .Write2DUT(7);
    CS.clkRegs.setadctsten(0x0)// ADC mission mode
            .setadcvcmctrl(0x1)// set internal common mode voltage to 550mV
            .Write2DUT(26);
    CS.clkRegs.setcsdecmfactor(decmFactor)
            .setcsdforder(0x0)// sync_1
            .setcsadcconvmode(0x0)
            .Write2DUT(50);
    // select hvcc (1200mV) or bandgap (800mV) is ADC reference
    CS.clkRegs.setadcabsmeasen(useVbgAsRef)
            .Write2DUT(26);
    CS.clkRegs.setcsadcclkdiv(adcFreq)
            .Write2DUT(49);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    fullSteps = (0x1 << decmFactor) * 256;

    dfData.init(0);

    for (j = 0; j < avgTime; j++) {
        MACRO_DOUBLE compStatusPre;
        //		sprintf(label,"MPB_ADCRSTB_Disable_%f_%f_",Vcoef,Temp);
        //		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
        d2s::d2s_LABEL_BEGIN("MPB_ADCRSTB_Disable_", Global_D2S_Mode);
        selectMacro_MB(MacroLane_Sel);
        CS.clkRegs.SliceID(0).Broadcast(1);
        CS.clkRegs.setadcrstb(0x0).Write2DUT(26);
        //		fr.d2s_LABEL_END();
        d2s::d2s_LABEL_END();
        char IDstring[128] = "";
        //		sprintf(label,"CSDFCOMPSTATUS_ReadBack_CSCSR51_%f_%f_",Vcoef,Temp);
        //		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
        d2s::d2s_LABEL_BEGIN("CSDFCOMPSTATUS_ReadBack_CSCSR51_", Global_D2S_Mode);
        for (UINT uiMacroIndex = 0; uiMacroIndex < MacroLane_Sel.size(); uiMacroIndex++) {
            UINT MacroID = MacroLane_Sel[uiMacroIndex].MacroID;
            selectMacro(MacroID);

            CS.clkRegs.MacroID(MacroID).SliceID(0).Broadcast(0);
            sprintf(IDstring, "CSCSR51_%d", MacroID);
            CS.clkRegs.Read2IDString(51, IDstring);
        }
        //		fr.d2s_LABEL_END();
        d2s::d2s_LABEL_END();
        //		FOR_EACH_SITE_BEGIN();
        //			INT SiteID = CURRENT_SITE_NUMBER() - 1;

//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int SiteID = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
                sprintf(IDstring, "CSCSR51_%d", MacroID);
                uint val = jtag.getReadValue(IDstring)[SiteID];
                compStatusPre[SiteID][MacroID] = HILINK_Regs_Base::get_bits(val, CS.clkRegs.REG_INFO.csdfcompstatus());
                CSDFRefCode[SiteID][MacroID] = (0 == compStatusPre[SiteID][MacroID]) ? 0x0 : 0xFFF;
            }
            FOREACH_ACTIVESITE_END
        //Dynamic Write CSDFRefCode
        MACRO_INT CSRvalue;
        CSR_READ(MacroLane_Sel, CS.clkRegs, 50, CSRvalue);
        Update_CSReg_ForDynamicWrite(MacroLane_Sel, CS.clkRegs.REG_INFO.csdfrefcode(), CSDFRefCode, CSRvalue);

        //		sprintf(label,"MPB_CSDFREFCODE_Dynamci_Write_%f_%f_",Vcoef,Temp);
        //		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
        d2s::d2s_LABEL_BEGIN("MPB_CSDFREFCODE_Dynamci_Write_", Global_D2S_Mode);
        selectMacro_MB(MacroLane_Sel);
        CS.clkRegs.SliceID(0).Broadcast(1);

        char String_Dymainc[128] = "";
        for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            uint MacroID = MacroLane_Sel[macroIndex].MacroID;

            ostringstream id50;
            id50 << "CSR50_" << "_M" << MacroID << jtag.Context;
            map<int, long long> tmp;
            parseSiteDataFromMacroInt(tmp, CSRvalue, MacroID);
            CS.clkRegs.Write2DUT_DYN(50, tmp, id50.str());
        }
        //		fr.d2s_LABEL_END();
        d2s::d2s_LABEL_END();
        //		sprintf(label,"MPB_ADCRSTB_Enable_%f_%f_",Vcoef,Temp);
        //		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
        d2s::d2s_LABEL_BEGIN("MPB_ADCRSTB_Enable_", Global_D2S_Mode);
        selectMacro_MB(MacroLane_Sel);
        CS.clkRegs.SliceID(0).Broadcast(1);
        CS.clkRegs.setadcrstb(0x1).Write2DUT(26);
        //		fr.d2s_LABEL_END();
        d2s::d2s_LABEL_END();
        // wait for CS ADC df ready
        iMaxTimeout = 50;
        wait_interval_ms = 2;
        EXPECT_RESULT compStatusPre_Result;

        WaitDoneMacro_Value_Update(MacroLane_Sel, CS.clkRegs.REG_INFO.csdfcompstatus(), compStatusPre, iMaxTimeout, wait_interval_ms, compStatusPre_Result);

        //		sprintf(label,"getcsdfdata_%f_%f_",Vcoef,Temp);
        //		fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
        d2s::d2s_LABEL_BEGIN("getcsdfdata_", Global_D2S_Mode);
        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            char IDstring[128] = "";
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            selectMacro(MacroID);
            sprintf(IDstring, "CSDFDATA_onMacro%i", MacroID);
            CS.clkRegs.Read2IDString(51, IDstring);
        }
        //		fr.d2s_LABEL_END();
        d2s::d2s_LABEL_END();
        //		FOR_EACH_SITE_BEGIN();
        //		INT SiteID = CURRENT_SITE_NUMBER() - 1;

//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int SiteID = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

            for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
                char IDstring[128] = "";
                sprintf(IDstring, "CSDFDATA_onMacro%i", MacroID);
                UINT val = (UINT) jtag.getReadValue(IDstring)[SiteID];
                mCsdfdataPerMacro[SiteID][MacroID] = HILINK_Regs_Base::get_bits(val, CS.clkRegs.REG_INFO.csdfdata());
                dfData[SiteID][MacroID] += mCsdfdataPerMacro[SiteID][MacroID];
            }
            FOREACH_ACTIVESITE_END
    }

    // Power down ADC to save power
    //	sprintf(label,"MPB_CsGetAdcData_SETUP2_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("MPB_CsGetAdcData_SETUP2_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    CS.clkRegs.SliceID(0).Broadcast(1);
    CS.clkRegs.setadcrstb(0x0).Write2DUT(26); //keep ADC in reset mode
    CS.clkRegs.setadcpwrdb(0x0).Write2DUT(7); //power down ADC
    CS.clkRegs.setdpmfinetuneen(0x1).Write2DUT(58);
    CS.clkRegs.setcstopfsm_cal_start(0x1).Write2DUT(58);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    // translate result to voltage in mV
    //	FOR_EACH_SITE_BEGIN();
    //	INT SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            dfData[SiteID][MacroID] = dfData[SiteID][MacroID] / avgTime;
            voltageVal[SiteID][MacroID] = dfData[SiteID][MacroID] * refVoltage / fullSteps;

            if (0x0 == returnType) {
                adcdataresult[SiteID][MacroID] = voltageVal[SiteID][MacroID];
            } else {
                adcdataresult[SiteID][MacroID] = dfData[SiteID][MacroID];
            }
        }
        FOREACH_ACTIVESITE_END
}

bool Check_CSTopFsm_Cal_Done(INT MacroID, SITE_INT& result) {
    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();
    //GET_TEST_INFO;
    //	sprintf(label,"GET_TEMP_Check_CSTopFsm_Cal_Done_SS_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("GET_TEMP_Check_CSTopFsm_Cal_Done_SS_", Global_D2S_Mode);
    selectMacro(MacroID);
    jtag.enablePassFailCheckForNextExecution();
    CS.clkRegs.SliceID(0).Broadcast(1);
    //		CS.clkRegs.ExpectValue(51,0x4000,0xbfff);
    CS.clkRegs.ExpectValue(51, 0x4000, 0x2000);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	result = jtag.hasPassed(label);
    return is_allPass("GET_TEMP_Check_CSTopFsm_Cal_Done_SS_", result);

}

bool Check_SSTopFsm_Cal_Done(INT MacroID, SITE_INT& result) {
    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();
    //GET_TEST_INFO;
    //	sprintf(label,"GET_TEMP_Check_SSTopFsm_Cal_Done_SS_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("GET_TEMP_Check_SSTopFsm_Cal_Done_SS_", Global_D2S_Mode);
    selectMacro(MacroID);
    jtag.enablePassFailCheckForNextExecution();
    CS.clkRegs.SliceID(0).Broadcast(1);
    //		CS.clkRegs.ExpectValue(54,0x4000,0xbfff);
    CS.clkRegs.ExpectValue(54, 0x4000, 0x2000);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //                result = jtag.hasPassed(label);
    return is_allPass("GET_TEMP_Check_SSTopFsm_Cal_Done_SS_", result);

}

bool Check_SSDFCOMPSTATUS(MACRO_LANE_SEL &MacroLane_Sel, MACRO_INT compStatusPre) {
    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    //GET_TEST_INFO;
    int pass_flag = 1;
    MACRO_INT mCsdfrefcodePerMacro;
    //	sprintf(label,"Check_SSDFCOMPSTATUS_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("Check_SSDFCOMPSTATUS_", Global_D2S_Mode);
    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        selectMacro(MacroID);
        CS.clkRegs.MacroID(MacroID).SliceID(0).Broadcast(0);
        char IDstring[128] = "";
        sprintf(IDstring, "SSDFCOMPSTATUS_onMacro%i", MacroID);
        CS.clkRegs.Read2IDString(54, IDstring);
    }
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //	INT SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            char IDstring[128] = "";
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            sprintf(IDstring, "SSDFCOMPSTATUS_onMacro%i", MacroID);
            UINT val = (UINT) jtag.getReadValue(IDstring)[SiteID];
            mCsdfrefcodePerMacro[SiteID][MacroID] = HILINK_Regs_Base::get_bits(val, CS.clkRegs.REG_INFO.ssdfcompstatus());

            hout(DETAIL) << "mCsdfrefcodePerMacro = " << mCsdfrefcodePerMacro[SiteID][MacroID] << "\tcompStatusPre = " << compStatusPre[SiteID][MacroID] << endl;

            if (mCsdfrefcodePerMacro[SiteID][MacroID] != compStatusPre[SiteID][MacroID]) {
                pass_flag = 0;
            }
        }
        FOREACH_ACTIVESITE_END
    if (pass_flag) {
        return true;
    } else
        return false;
}

bool Check_CSDFCOMPSTATUS(MACRO_LANE_SEL &MacroLane_Sel, MACRO_INT compStatusPre) {
    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    //GET_TEST_INFO;
    int pass_flag = 1;
    MACRO_INT mCsdfrefcodePerMacro;

    //	sprintf(label,"Check_CSDFCOMPSTATUS_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("Check_CSDFCOMPSTATUS_", Global_D2S_Mode);
    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        selectMacro(MacroID);
        CS.clkRegs.MacroID(MacroID).SliceID(0).Broadcast(0);
        char IDstring[128] = "";
        sprintf(IDstring, "CSDFCOMPSTATUS_onMacro%i", MacroID);
        CS.clkRegs.Read2IDString(51, IDstring);
    }
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //	INT SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            char IDstring[128] = "";
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            sprintf(IDstring, "CSDFCOMPSTATUS_onMacro%i", MacroID);
            UINT val = (UINT) jtag.getReadValue(IDstring)[SiteID];
            mCsdfrefcodePerMacro[SiteID][MacroID] = HILINK_Regs_Base::get_bits(val, CS.clkRegs.REG_INFO.csdfcompstatus());
            if (mCsdfrefcodePerMacro[SiteID][MacroID] != compStatusPre[SiteID][MacroID]) {
                pass_flag = 0;
            }
        }
        FOREACH_ACTIVESITE_END
    if (pass_flag) {
        return true;
    } else
        return false;
}






//The following are for check-before-write and output format

void init_csr_check_list(T_HILINK_CSR_CHECK& check_list) {

    check_list.CP_API_CSR.clear();
    check_list.CS_API_CSR.clear();
    check_list.DS_API_CSR.clear();

    check_list.CS_CLK_CSR.clear();
    check_list.CS_CLKDBG_CSR.clear();

    check_list.DS_CLK_CSR.clear();
    check_list.DS_RXEXT_CSR.clear();
    check_list.DS_TX_CSR.clear();
    check_list.DS_RX_CSR.clear();

    check_list.MCU.clear();
    check_list.TOP_API_CSR.clear();
    check_list.ABIST_API_CSR.clear();

}

void check_csr(vector<T_CHECK_DATA>& target, int csr, int data, int mask) { //<0 meas use value in csr array
    T_CHECK_DATA rtn = {csr, data, mask};
    target.push_back(rtn);
}



//==============================================================================
// Function: GetMosCornerSw
// - This function is used for MOS corners detection by using Vth measurement
// - mosType: 0=uLVT,1=SVT
// - pmosCorner: PMOS corner
// - nmosCorner: NMOS corner
// - cmosCorner: CMOS corner
//==============================================================================

void GetMosCornerSw(MACRO_LANE_SEL &MacroLane_Sel, uint mosType, MACRO_DOUBLE &pmosCorner, MACRO_DOUBLE &nmosCorner, MACRO_DOUBLE &cmosCorner, MACRO_DOUBLE &temperature, INT BypassGetTemp) {
    MACRO_DOUBLE pmosDfCode, nmosDfCode;
    MACRO_DOUBLE tempCodePoff, tempCodeNoff;

    if (BypassGetTemp == 0)
        GetTemperature(MacroLane_Sel, temperature);

    d2s_JTAG& jtag = d2s_JTAG::Instance();

    //	D2S_FRAMEWORK;
    //GET_TEST_INFO;

    //	sprintf(label,"MPB_DPMFINETUNEEN_SETUP_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("MPB_DPMFINETUNEEN_SETUP_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    CS.clkRegs.SliceID(0).Broadcast(1);
    CS.clkRegs.setdpmfinetuneen(0x0).Write2DUT(58);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    INT iMaxTimeout = 150;
    DOUBLE wait_interval_ms = 20;
    EXPECT_RESULT CS_DFCOMPSTATUS_Result;

    //while(0x1 == CSTOPFSM_CAL_START (CS_CSR58 bit[15])) {;}
    WaitDone(MacroLane_Sel, "Macro", CS.clkRegs.REG_INFO.cstopfsm_cal_done(), 0, iMaxTimeout, wait_interval_ms, CS_DFCOMPSTATUS_Result);

    // Enable Vth sensor
    //	sprintf(label,"MPB_GetMosCornerSw_SETUP0_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("MPB_GetMosCornerSw_SETUP0_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    CS.clkRegs.SliceID(0).Broadcast(1);
    CS.clkRegs.setmosdeten(0x1).Write2DUT(41);
    CS.clkRegs.setmosdetmostypesel(mosType).Write2DUT(41);
    CS.clkRegs.setmosdetvgsatbctrl(0x2).Write2DUT(48); // Vth process detector atb selects vgsp for pch
    CS.clkRegs.setssadcinputsel(0x1).Write2DUT(39); // Vth detector Vgsp is selected

    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	pmosDfCode = SsGetAdcData(adcFreq = 4, useVbgAsRef = 1, decmFactor = 2, refVoltage = 800, avgTime = 1, returnType = 1);
    //	void SsGetAdcData(MACRO_LANE_SEL &MacroLane_Sel,MACRO_DOUBLE &adcdataresult,uint adcFreq, uint useVbgAsRef, uint decmFactor, uint refVoltage,uint avgTime, uint returnType);
    uint adcinputsel = 1;
    SsGetAdcData(MacroLane_Sel, pmosDfCode, 4, 1, 2, 800, 1, 1, adcinputsel); //modify byshaoxue 20170525

    //	sprintf(label,"MPB_GetMosCornerSw_SETUP1_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("MPB_GetMosCornerSw_SETUP1_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    CS.clkRegs.SliceID(0).Broadcast(1);
    CS.clkRegs.setmosdetvgsatbctrl(0x1).Write2DUT(48);
    CS.clkRegs.setssadcinputsel(0x2).Write2DUT(39); // Vth detector Vgsp is selected
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //    nmosDfCode = SsGetAdcData(adcFreq = 4, useVbgAsRef = 1, decmFactor = 2, refVoltage = 800, avgTime = 1, returnType = 1);
    adcinputsel = 2;
    SsGetAdcData(MacroLane_Sel, nmosDfCode, 4, 1, 2, 800, 1, 1, adcinputsel); //modify by shaoxue 20170525,add adcinputsel to avoid pattern overwrite

    // Clean up
    //	sprintf(label,"MPB_GetMosCornerSw_SETUP2_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("MPB_GetMosCornerSw_SETUP2_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    CS.clkRegs.SliceID(0).Broadcast(1);
    CS.clkRegs.setmosdeten(0x0).Write2DUT(41);
    CS.clkRegs.setmosdetmostypesel(0x0).Write2DUT(41);
    CS.clkRegs.setmosdetvgsatbctrl(0x0).Write2DUT(48);
    CS.clkRegs.setssadcinputsel(0x0).Write2DUT(39);

    //		CS.clkRegs.setdpmfinetuneen(0x1).Write2DUT(58);
    //		CS.clkRegs.setcstopfsm_cal_start(0x1).Write2DUT(58);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //	INT SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            if (0x0 == mosType) //uLvt
            {
                tempCodePoff[SiteID][MacroID] = (temperature[SiteID][MacroID] + 40) * 0.45;
                tempCodeNoff[SiteID][MacroID] = (temperature[SiteID][MacroID] + 40) * 0.40;
            } else { // SVT
                tempCodePoff[SiteID][MacroID] = (temperature[SiteID][MacroID] + 40) * 0.52;
                tempCodeNoff[SiteID][MacroID] = (temperature[SiteID][MacroID] + 40) * 0.41;
            }

            pmosDfCode[SiteID][MacroID] = pmosDfCode[SiteID][MacroID] + tempCodePoff[SiteID][MacroID];
            nmosDfCode[SiteID][MacroID] = nmosDfCode[SiteID][MacroID] + tempCodeNoff[SiteID][MacroID];

            if (0x0 == mosType) //uLvt
            {
                pmosCorner[SiteID][MacroID] = (pmosDfCode[SiteID][MacroID] - 440) / 15;
                nmosCorner[SiteID][MacroID] = (nmosDfCode[SiteID][MacroID] - 378) / 14;
            } else { // SVT
                pmosCorner[SiteID][MacroID] = (pmosDfCode[SiteID][MacroID] - 653) / 16;
                nmosCorner[SiteID][MacroID] = (nmosDfCode[SiteID][MacroID] - 570) / 16;
            }

            cmosCorner[SiteID][MacroID] = (pmosCorner[SiteID][MacroID] + nmosCorner[SiteID][MacroID]) / 2;
        }
        FOREACH_ACTIVESITE_END
}


//==============================================================================
// Function: GetCsMosCornerSw
// - This function is used for MOS corners detection by using Vth measurement
// - pmosCorner: PMOS corner
// - nmosCorner: NMOS corner
// - cmosCorner: CMOS corner
//==============================================================================

void GetCsMosCornerSw(MACRO_LANE_SEL &MacroLane_Sel, MACRO_DOUBLE &pmosCorner, MACRO_DOUBLE &nmosCorner, MACRO_DOUBLE &cmosCorner, MACRO_DOUBLE &temperature, INT BypassGetTemp) {
    MACRO_DOUBLE pmosDfCode, nmosDfCode;
    MACRO_DOUBLE tempCodePoff, tempCodeNoff;

    //Get external temperature
    if (BypassGetTemp == 0)
        GetTemperature(MacroLane_Sel, temperature);

    //	D2S_FRAMEWORK;
    //GET_TEST_INFO;

    //	sprintf(label,"MPB_DPMFINETUNEEN_SETUP_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("MPB_DPMFINETUNEEN_SETUP_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    CS.clkRegs.MacroID(MacroLane_Sel[0].MacroID).SliceID(0).Broadcast(1);
    CS.clkRegs.setdpmfinetuneen(0x0).Write2DUT(58);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    INT iMaxTimeout = 150;
    DOUBLE wait_interval_ms = 20;
    EXPECT_RESULT CS_DFCOMPSTATUS_Result;

    //while(0x1 == CSTOPFSM_CAL_START (CS_CSR58 bit[15])) {;}
    WaitDone(MacroLane_Sel, "Macro", CS.clkRegs.REG_INFO.cstopfsm_cal_start(), 0, iMaxTimeout, wait_interval_ms, CS_DFCOMPSTATUS_Result);

    // Enable Vth sensor
    //	sprintf(label,"MPB_GetCsMosCornerSw_SETUP0_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("MPB_GetCsMosCornerSw_SETUP0_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    CS.clkRegs.SliceID(0).Broadcast(1);
    CS.clkRegs.setcsatbtopsel(0x6).Write2DUT(29);
    CS.clkRegs.setmosdetcml2cmospwrdb(0x1).Write2DUT(35);
    CS.clkRegs.setmosdetoscatbctrl(0x2).Write2DUT(48);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    // 	pmosDfCode = CsGetAdcData(adcFreq = 7, useVbgAsRef = 1, decmFactor = 2, refVoltage = 800, avgTime = 1, returnType = 1);
    CsGetAdcData(MacroLane_Sel, pmosDfCode, 7, 1, 2, 800, 1, 1);

    //	sprintf(label,"MPB_GetCsMosCornerSw_SETUP1_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("MPB_GetCsMosCornerSw_SETUP1_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    CS.clkRegs.SliceID(0).Broadcast(1);
    CS.clkRegs.setmosdetoscatbctrl(0x1).Write2DUT(48);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    CsGetAdcData(MacroLane_Sel, nmosDfCode, 7, 1, 2, 800, 1, 1);

    // Clean up
    //	sprintf(label,"MPB_GetCsMosCornerSw_SETUP2_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("MPB_GetCsMosCornerSw_SETUP2_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    CS.clkRegs.SliceID(0).Broadcast(1);
    CS.clkRegs.setcsatbtopsel(0x0).Write2DUT(29);
    CS.clkRegs.setmosdetcml2cmospwrdb(0x0).Write2DUT(35);
    CS.clkRegs.setmosdetoscatbctrl(0x0).Write2DUT(48);
    CS.clkRegs.setdpmfinetuneen(0x1).Write2DUT(58);
    CS.clkRegs.setcstopfsm_cal_start(0x1).Write2DUT(58);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //		INT SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

            tempCodePoff[SiteID][MacroID] = (temperature[SiteID][MacroID] + 40) * 0.45;
            tempCodeNoff[SiteID][MacroID] = (temperature[SiteID][MacroID] + 40) * 0.40;

            pmosDfCode[SiteID][MacroID] = pmosDfCode[SiteID][MacroID] + tempCodePoff[SiteID][MacroID];
            nmosDfCode[SiteID][MacroID] = nmosDfCode[SiteID][MacroID] + tempCodeNoff[SiteID][MacroID];

            pmosCorner[SiteID][MacroID] = (pmosDfCode[SiteID][MacroID] - 440) / 15;
            nmosCorner[SiteID][MacroID] = (nmosDfCode[SiteID][MacroID] - 378) / 14;

            cmosCorner[SiteID][MacroID] = (pmosCorner[SiteID][MacroID] + nmosCorner[SiteID][MacroID]) / 2;
        }
        FOREACH_ACTIVESITE_END
}

void Antiproof_SumFIR(CUSTPARA &Custpara) {
    INT iTxMain = Custpara.TxFIR_USER.iTxMain;
    INT iTxPre1st = Custpara.TxFIR_USER.iTxPre1st;
    INT iTxPost1st = Custpara.TxFIR_USER.iTxPost1st;
    INT iTxPre2nd = Custpara.TxFIR_USER.iTxPre2nd;
    INT iTxPost2nd = Custpara.TxFIR_USER.iTxPost2nd;

    INT iSum = abs(iTxMain) + abs(iTxPre1st) + abs(iTxPost1st) + abs(iTxPre2nd) + abs(iTxPost2nd);

    if (iSum > 63) {
        //		cout << "Current FIR value = "<< abs(iTxMain) << "+"<< abs(iTxPre1st) << "+" << abs(iTxPost1st) << "+" << abs(iTxPre2nd) << "+" << abs(iTxPost2nd) << endl;
        //		cout << "ERROR: FIR sum value can't be bigger than 63 !!!!" << endl;
        printf("ERROR: FIR sum value can't be bigger than 63 !!!!\n");
        //		ERROR_EXIT(TM::ABORT_FLOW);
    }
}

void SEGMENT_EXPECT(const MACRO_LANE_SEL& MacroLane_Sel, const string& MacroOrLane, const T_REG_INFO_EX& reg_info_ex, UINT value, EXPECT_RESULT& ExpectResult) {
    /***************this sub func must in ON_FIRST_INVOCATION_BEGIN block**************/
    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    //GET_TEST_INFO;

    //	ARRAY_I sites;
//    unsigned int sites[MAX_SITES];
    //	INT	ConfiguredSitesNum = GET_CONFIGURED_SITES(sites);
    INT ConfiguredSitesNum = TheSoft.Sites().Existing().GetExistedSiteCount();// api->Get_active_sites(sites);
    ARRAY_I tmp;
    tmp.resize(ConfiguredSitesNum);
    //	tmp.init(0);
    ExpectResult.allpass = true;
    ExpectResult.allfail = true;
    ExpectResult.eachsite = tmp;

    UINT lb = reg_info_ex.reg_info.low_bit;
    UINT hb = reg_info_ex.reg_info.hi_bit;
    UINT csr = reg_info_ex.reg_info.csr;

    UINT mask = 0xFFFF;
    mask &= HI_BIT_MASK[hb];
    mask &= ~LO_BIT_MASK[lb];

    value <<= lb;
    value &= mask;

    //	mask = ~mask;

    HILINK_Regs_Base& reg = reg_info_ex.parent;

    //	sprintf(label,"Segment_Expect_%f_%f_",Vcoef,Temp);
    //    fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("Segment_Expect_", Global_D2S_Mode);
    jtag.enablePassFailCheckForNextExecution();
    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
        selectMacro(MacroID);
        if (MacroOrLane == "Lane") {
            for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
                UINT LaneID = vLane[laneIndex];
                reg.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
                reg.ExpectValue(csr, value, mask);
            }

        } else if (MacroOrLane == "Macro") {

            reg.MacroID(MacroID).SliceID(0).Broadcast(0);
            reg.ExpectValue(csr, value, mask);
        }
    }
    //    fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	jtag.hasPassed(label,ExpectResult.allpass,ExpectResult.allfail,ExpectResult.eachsite);

    map<uint32_t, bool> map_pass_fail_result = TheInst.Digital().PatEng().GetPassFail();
//    FOREACH_ACTIVE_SITE(api) {
    	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

//        bool size_pass = map_pass_fail_result[SiteID];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
        bool size_pass = map_pass_fail_result[SiteID];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
		if(PrintDebugEn) cout<<"map_pass_fail_result["<<SiteID<<"] = "<<map_pass_fail_result[SiteID]<<endl;
        ExpectResult.allpass = (ExpectResult.allpass && size_pass);
        ExpectResult.allfail = (ExpectResult.allfail && !size_pass);
        ExpectResult.eachsite[SiteID] = size_pass;
        FOREACH_ACTIVESITE_END
}

void SEGMENT_READ_MACRO(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, MACRO_DOUBLE& permacro_value) {
    /***************this sub func must in ON_FIRST_INVOCATION_BEGIN block**************/
    permacro_value.init(0);
    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    //GET_TEST_INFO;

    UINT csr = reg_info_ex.reg_info.csr;
    HILINK_Regs_Base& reg = reg_info_ex.parent;

    //	sprintf(label,"Segment_read_%f_%f_",Vcoef,Temp);
    //    fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("Segment_read_", Global_D2S_Mode);
    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

        selectMacro(MacroID);

        reg.MacroID(MacroID).SliceID(0).Broadcast(0);
        ostringstream str;
        str << reg.getName() << "_CSR_" << csr << "_M" << MacroID;
        reg.Read2IDString(csr, str.str());
    }
    //    fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //		INT SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

            ostringstream str;
            str << reg.getName() << "_CSR_" << csr << "_M" << MacroID;
            UINT val = (UINT) jtag.getReadValue(str.str())[SiteID];
            permacro_value[SiteID][MacroID] = HILINK_Regs_Base::get_bits(val, reg_info_ex);
            //cout<<"permacro_value[SiteID"<<SiteID<<"][MacroID"<<MacroID<<"]" <<permacro_value[SiteID][MacroID]<<endl;
        }
        FOREACH_ACTIVESITE_END
}

void WaitDone(const MACRO_LANE_SEL& MacroLane_Sel, const string& MacroOrLane, const T_REG_INFO_EX& reg_info_ex, UINT value, INT MaxCheckCount, DOUBLE IntervalTime_ms, EXPECT_RESULT& ExpectResult) {
    if (IntervalTime_ms < 0) {
        hout(DETAIL) << "####################### IntervalTime_ms < 0 ms, set to 1 ms  #####################" << endl;
        IntervalTime_ms = 1;
    }

    INT checkCount = 0; /*Temp local variable for time out count*/
    do {
        checkCount++;
        //		cout<<checkCount<<endl;
        //		WAIT_TIME(IntervalTime_ms);
//        api->sleep(IntervalTime_ms);
        TheInst.Wait(IntervalTime_ms*0.001);

        SEGMENT_EXPECT(MacroLane_Sel, MacroOrLane, reg_info_ex, value, ExpectResult);
        hout(DETAIL) << "WaitDone_CheckCount = " << dec << checkCount << endl;
    } while (false == ExpectResult.allpass && checkCount < MaxCheckCount);

    if (checkCount >= MaxCheckCount) {
        /**************** print wait done result ****************/
        hout(GENERAL) << "#######################  Wait Done time out #######################" << endl;
        if (ExpectResult.allfail) {
            hout(DETAIL) << "####################### All Sites Wait Done Failed!!! #####################" << endl;
        } else {

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
                FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

                hout(DETAIL) << "#######################WAIT DONE RESULT = " << ExpectResult.eachsite[SiteID] << " #########" << endl;
                //                                FOR_EACH_SITE_END();
                FOREACH_ACTIVESITE_END
        }
    }
}

void WaitDoneMacro(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, UINT value, INT MaxCheckCount, DOUBLE IntervalTime_ms, EXPECT_RESULT& ExpectResult) {
    //	if (IntervalTime_ms < 1){
    //		hout(DETAIL) << "####################### IntervalTime_ms < 1 ms, set to 1 ms  #####################" << endl;
    //		IntervalTime_ms = 1;
    //	}

    INT checkCount = 0; /*Temp local variable for time out count*/
    do {
        checkCount++;
        //		WAIT_TIME(IntervalTime_ms ms);
//        api->sleep(IntervalTime_ms);
        TheInst.Wait(IntervalTime_ms*0.001);
        SEGMENT_EXPECT_MACRO(MacroLane_Sel, reg_info_ex, value, ExpectResult);
        hout(DETAIL) << "WaitDone_CheckCount = " << dec << checkCount << endl;
    } while (false == ExpectResult.allpass && checkCount < MaxCheckCount);
    if(PrintDebugEn) cout<<"in WaitDoneMacro function , WaitDone_CheckCount final = " << dec << checkCount << " MaxCheckCount = "<<MaxCheckCount << endl;


    if (checkCount >= MaxCheckCount) {
        /**************** print wait done result ****************/
        hout(GENERAL) << "#######################  Wait Done time out #######################" << endl;
        cout << "#######################  Wait Done time out #######################" << endl;
        if (ExpectResult.allfail) {
            hout(DETAIL) << "####################### All Sites Wait Done Failed!!! #####################" << endl;
            cout << "####################### All Sites Wait Done Failed!!! #####################" << endl;
        } else {
            //			FOR_EACH_SITE_BEGIN();
            //			INT SiteID = CURRENT_SITE_NUMBER() - 1;

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
                FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

                hout(DETAIL) << "#######################WAIT DONE RESULT = " << ExpectResult.eachsite[SiteID] << " #########" << endl;
                cout << "#######################WAIT DONE RESULT = ExpectResult.eachsite[SiteID]" << ExpectResult.eachsite[SiteID] << " #########" << endl;
                //			FOR_EACH_SITE_END();
                FOREACH_ACTIVESITE_END
        }
    }
}

bool DsDcdReCalib(MACRO_LANE_SEL &MacroLane_Sel, DSAPI &DSApi) {
    //	D2S_FRAMEWORK;
    //GET_TEST_INFO;
    EXPECT_RESULT DS_Calib_Result;
    INT iMaxTimeout;
    DOUBLE wait_interval_ms;

    //	sprintf(label,"DsDcdReCalib_Conf1_%f_%f_",Vcoef,Temp);
    //fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("DsDcdReCalib_Conf1_", Global_D2S_Mode);
    for (size_t macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
        selectMacro(MacroID);
        SRAM.CPAPIRegs.SliceID(0).Broadcast(1);
        SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8, false);
        for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
            UINT LaneID = vLane[laneIndex];
            //Configure DS calibration by pass enable
            SRAM.DSAPIRegs.MacroID(MacroID).SliceID(LaneID);

            // Step1: Dataslice firmware reset.
            SRAM.DSAPIRegs.setds_soft_reset_api(0x1)
                    .setds_ctle_en_api(0x0)
                    .setds_dfe_en_api(0x0).Write2DUT(0, false);
        }
        SRAM.CPAPIRegs.setmcurstb(0x1).Write2DUT(8, false);
    }


    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    iMaxTimeout = 100;
    wait_interval_ms = 1;
    WaitDone(MacroLane_Sel, "Macro", SRAM.DSAPIRegs.REG_INFO.ds_soft_reset_status_api(), 1, iMaxTimeout, wait_interval_ms, DS_Calib_Result);

    //	sprintf(label,"DsDcdReCalib_Conf2_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("DsDcdReCalib_Conf2_", Global_D2S_Mode);
    for (size_t macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
        selectMacro(MacroID);
        SRAM.CPAPIRegs.SliceID(0).Broadcast(1);
        SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8, false);
        for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
            UINT LaneID = vLane[laneIndex];
            //Configure DS calibration by pass enable
            SRAM.DSAPIRegs.MacroID(MacroID).SliceID(LaneID);

            // Step2: Dataslice calibration bypass API setting.
            //			DSApi=default_DSAPI[caseindex]; 			// Case3/4/5
            DsCalibrationBypassConfig(DSApi);

            // Step3: Enable DS calibration
            SRAM.DSAPIRegs.setds_calib_en_api(0x1).Write2DUT(0, false);

            // Step4: Release Dataslice firmware reset.
            SRAM.DSAPIRegs.setds_soft_reset_api(0x0).Write2DUT(0, false);

        }
        SRAM.CPAPIRegs.setmcurstb(0x1).Write2DUT(8, false);
    }

    d2s::d2s_LABEL_END();

    iMaxTimeout = 100;
    wait_interval_ms = 1;
    WaitDone(MacroLane_Sel, "Macro", SRAM.DSAPIRegs.REG_INFO.ds_calib_done_status_api(), 1, iMaxTimeout, wait_interval_ms, DS_Calib_Result);

#if 0

    if ((d2s_mode == 1) || false == DS_Calib_Result.allpass) {//TODO : need to update NOAPI FW
        if (true == MemoryErrorCheck(MacroLane_Sel)) {
            // Wait for calibration to complete by checking status of TOP_FSM_DONE_API
            WaitDone(MacroLane_Sel, "Macro", SRAM.DSAPIRegs.REG_INFO.ds_calib_done_status_api(), 1, iMaxTimeout, wait_interval_ms, DS_Calib_Result);
            if (true == DS_Calib_Result.allpass) {
                hout(GENERAL) << "Dataslice calibration success!" << endl;
            } else {
                hout(GENERAL) << "Dataslice calibration fail!" << endl;
            }
        }

        ////		return false;
    }
    //////	else
    if ((1 == d2s_mode) || (true == DS_Calib_Result.allpass)) {
        sprintf(label, "DsDcdReCalib_Reset_%f_%f_", Vcoef, Temp);
        fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
        for (size_t macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
            selectMacro(MacroID);
            SRAM.CPAPIRegs.SliceID(0).Broadcast(1);
            SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8);
            for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
                UINT LaneID = vLane[laneIndex];
                SRAM.DSAPIRegs.MacroID(MacroID).SliceID(LaneID);
                // Step3: Diable DS calibration
                SRAM.DSAPIRegs.setds_calib_en_api(0x0).Write2DUT(0);
            }

        }
        fr.d2s_LABEL_END();

        hout(GENERAL) << "Dataslice calibration success!" << endl;

        //		return true;
    }
    if ((false == DS_Calib_Result.allpass)) {
        return false;
    }
    if ((true == DS_Calib_Result.allpass)) {
        return true;
    }

#endif
}


//====================================================================================
// Function: CsCalibrationBypassConfig
// - This function used to set CS calibration bypass APIs.
// - Please refer to the API register doc to get API detail description.
//====================================================================================

void CsCalibrationBypassConfig(CSAPI &CSApi) {
    //calibration bypass control.  0:not bypass   1:bypass
    SRAM.CSAPIRegs.setpll1vcodivvregcalbypass_api(CSApi.iPll1vcodivvregcalbypass_api)
            .setpll1cpvrefcalbypass_api(CSApi.iPll1cpvrefcalbypass_api)
            .setpll1dlfvregcalbypass_api(CSApi.iPll1dlfvregcalbypass_api)
            .setpll1pllvregcalbypass_api(CSApi.iPll1pllvregcalbypass_api)
            .setpll1vcocalbypass_api(CSApi.iPll1vcocalbypass_api)
            .setpll0vcodivvregcalbypass_api(CSApi.iPll0vcodivvregcalbypass_api)
            .setpll0cpvrefcalbypass_api(CSApi.iPll0cpvrefcalbypass_api)
            .setpll0dlfvregcalbypass_api(CSApi.iPll0dlfvregcalbypass_api)
            .setpll0pllvregcalbypass_api(CSApi.iPll0pllvregcalbypass_api)
            .setpll0vcocalbypass_api(CSApi.iPll0vcocalbypass_api)
            .setcsvrefgencalbypass_api(CSApi.iCsvrefgencalbypass_api)
            .setcsrxtermcalbypass_api(CSApi.iCsrxtermcalbypass_api)
            .setcsbandgapcalbypass_api(CSApi.iCsbandgapcalbypass_api)
            .setcsgetdpminfobypass_api(CSApi.iCsgetdpminfobypass_api).Write2DUT(3);



}

//====================================================================================
// Function: DsCalibrationBypassConfig
// - This function used to set DS calibration bypass APIs.
// - Please refer to the API register doc to get API detail description.
//====================================================================================

void DsCalibrationBypassConfig(DSAPI& DSApi) {
    SRAM.DSAPIRegs.setdsclkvrefgencalbypass_api(DSApi.iDsclkvrefgencalbypass_api)
            .setdsclkvregcalbypass_api(DSApi.iDsclkvregcalbypass_api)
            .setrxctlevregcalbypass_api(DSApi.iRxctlevregcalbypass_api)
            .setrxopampofstcalbypass_api(DSApi.iRxopampofstcalbypass_api)
            .setrxsumloadrescalbypass_api(DSApi.iRxsumloadrescalbypass_api)
            .setrxclkvregcalbypass_api(DSApi.iRxclkvregcalbypass_api)
            .setrxdatavregcalbypass_api(DSApi.iRxdatavregcalbypass_api)
            .setrxsigdetofstcalbypass_api(DSApi.iRxsigdetofstcalbypass_api)
            .setrxctleofstcalbypass_api(DSApi.iRxctleofstcalbypass_api)
            .setrxsumofstcalbypass_api(DSApi.iRxsumofstcalbypass_api)
            .setrxlatchofstcalbypass_api(DSApi.iRxlatchofstcalbypass_api)
            .setrxalfgenofstcalbypass_api(DSApi.iRxalfgenofstcalbypass_api)
            .settxdrvregcalbypass_api(DSApi.iTxdrvregcalbypass_api)
            .settxpredrvregcalbypass_api(DSApi.iTxpredrvregcalbypass_api)
            .settxrxserlpbkofstcalbypass_api(DSApi.iTxrxserlpbkofstcalbypass_api)
            .settxcenterpabypass_api(DSApi.iTxcenterpabypass_api).Write2DUT(2, false);

    SRAM.DSAPIRegs.settxdcdcalibbypass_api(DSApi.iTxdcdcalibbypass_api)
            .setrxctlerefcalibbypass_api(DSApi.iRxctlerefcallibbypass_api)
            .setrxctlecurrentcalibbypass_api(DSApi.iRxctlecurrentcallibbypass_api)
            .setlpbkdcdcalibbypass_api(DSApi.iLbpkdcdcallibbypass_api)
            .setrxalfgenstepsizecalibbypass_api(DSApi.iRxalfgenstepsizecalibbypass_api).Write2DUT(3, false);
}

void DsAdaptationBypassConfig(DSAPI_Adaptation& DSapi_Adaptation) {
    SRAM.DSAPIRegs.setctle_latchofst_en_api(DSapi_Adaptation.iCtle_latchofst_en_api).Write2DUT(10, false);
    SRAM.DSAPIRegs.setdfe_boost_en_api(DSapi_Adaptation.iDfe_boost_en_api).Write2DUT(6, false);
    SRAM.DSAPIRegs.setds_boost_squelch_en_api(DSapi_Adaptation.iDS_boost_squelch_en_api).Write2DUT(5, false);
    SRAM.DSAPIRegs.setds_offset_en_api(DSapi_Adaptation.iDS_offset_en_api).Write2DUT(0, false);
    SRAM.DSAPIRegs.setctle_refsel_en_api(DSapi_Adaptation.iCtle_refsel_en_api).Write2DUT(4, false);
    SRAM.DSAPIRegs.setgain_attn_en_api(DSapi_Adaptation.iGain_attn_en_api).Write2DUT(5, false);
    SRAM.DSAPIRegs.setcentering_en_api(DSapi_Adaptation.iCentering_en_api).Write2DUT(8, false);
    SRAM.DSAPIRegs.setalphagen_ofst_en_api(DSapi_Adaptation.iAlphagen_opst_en_api).Write2DUT(8, false);
    SRAM.DSAPIRegs.setdlev_target_api(DSapi_Adaptation.iDlev_target_api).Write2DUT(5, false);
    SRAM.DSAPIRegs.setds_ctle_en_api(DSapi_Adaptation.iDs_ctle_en_api).Write2DUT(0, false);
    SRAM.DSAPIRegs.setctle_dfetap1_bypass_en_api(DSapi_Adaptation.iCtle_dfetap1_bypass_en_api).Write2DUT(8, false);

}

//Loading Frimware to SRAM
//====================================================================================
// Function: LoadFirmwareToSram
// - This function is used to load firmware to sram.
// - HiLink30_FW_SRAM: The byte array that come from firmware bin document.
//====================================================================================

void LoadFirmwareToSram(MACRO_LANE_SEL& MacroLane_Sel, INT iPRBSMODE, INT iFWType) {

    d2s_JTAG& jtag = d2s_JTAG::Instance();

    /**************Clear API and CSConfigBeforeCal***set proper API depending on applications and Release MCU*********/

    //Step1: hold MCU in reset mode
    d2s::d2s_LABEL_BEGIN("LoadFirmwareToSram_holdMCUinResetMode1_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8);
    d2s::d2s_LABEL_END();
    //Step2: Load Firmware
    //Run Pattern
    string patternName;
    //        d2s::d2s_LABEL_BEGIN("LoadFirmwareToSram_DownLoadFirmWare_", Global_D2S_Mode);
    if (iFWType == FwTypeCalAll) {
//        api->Execute_test("HiLink30LRV101_Calib_ATE_SRAM_1.2.6_0131_1203.hex.bin_WRITE");
        patternName = "HiLink30LRV101_Calib_ATE_SRAM_1.2.6_0131_1203.hex.bin_WRITE"; //block check OK
        TheInst.Digital().Pattern().Start(patternName);

    }
    if (iFWType == FwTypeCalNoApi) {
//        api->Execute_test("HiLink30LRV101_Calib_ATE_SRAM_1.2.6_0131_1203_noapi.hex.bin_WRITE");
    	patternName = "HiLink30LRV101_Calib_ATE_SRAM_1.2.6_0131_1203_noapi.hex.bin_WRITE";//block check OK
    	 TheInst.Digital().Pattern().Start(patternName);

    }
    if (iFWType == FwTypeAdaptNoApi) {
//        api->Execute_test("HiLink30LRV101_Ate_Adapt_SRAM_1.1.2_0315_1138_noapi.hex.bin_WRITE");
        patternName = "HiLink30LRV101_Ate_Adapt_SRAM_1.1.2_0315_1138_noapi.hex.bin_WRITE";//block check OK
        TheInst.Digital().Pattern().Start(patternName);

    }

    if(PrintDebugEn) cout<<"load firmware pattern burst name ="<< patternName<<endl;
 	map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
 	for(auto it = result.begin(); it != result.end(); it++)
	{
 		if(PrintDebugEn) cout<<"passfail :"<< it->second<<endl;
	}

    //        d2s::d2s_LABEL_END();


    d2s::d2s_LABEL_BEGIN("LoadFirmwareToSram_holdMCUinResetMode2_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);

    //Step3: Clear ecc/pariry interrupt
    SRAM.CPAPIRegs.setrameccerr(0x0).Write2DUT(9);
    SRAM.CPAPIRegs.setromparerr(0x0).Write2DUT(9);

    //Step4: ECC/parity interrupt enable
    SRAM.CPAPIRegs.setmcuintmask(0x0C00).Write2DUT(10);

    //Ecc/parity error protection
    SRAM.CPAPIRegs.setinstromparerrmcuinhibit(0x1).Write2DUT(15);
    SRAM.CPAPIRegs.setinstrameccerrmcuinhibit(0x1).Write2DUT(15);
    SRAM.CPAPIRegs.setdatromparerrmcuinhibit(0x1).Write2DUT(15);
    SRAM.CPAPIRegs.setdatrameccerrmcuinhibit(0x1).Write2DUT(15);

    //Enable ecc function
    SRAM.CPAPIRegs.setrameccbypass(0x0).Write2DUT(15);
    d2s::d2s_LABEL_END();
}

//Shaoxue add for FW_Abist test from H30V200

void LoadFirmwareToSram(MACRO_LANE_SEL& MacroLane_Sel, STRING FW_Name, INT FW_Length) {
    /**************Clear API and CSConfigBeforeCal***set proper API depending on applications and Release MCU*********/

    d2s::d2s_LABEL_BEGIN("LoadFirmwareToSram__holdMCUinResetMode1_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    //Step1: hold MCU in reset mode
    SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8);
    d2s::d2s_LABEL_END();
    //Step2: Load Firmware

    //	jtag.execLabel(FW_Name, FW_Length);
    const char * test = FW_Name.c_str();
    string testPatternBurst = test;
    if(PrintDebugEn) cout<<" load formware pattern burst = "<< testPatternBurst <<endl;

//    api->Execute_test(test); //V100  masked by tony 20210817
    TheInst.Digital().Pattern().Start(testPatternBurst);

 	map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
 	for(auto it = result.begin(); it != result.end(); it++)
	{
 		if(PrintDebugEn) cout<<"passfail :"<< it->second<<endl;
	}
// 	uint64_t GetExecutedCyclesCount = TheInst.Digital().PatEng().GetExecutedCyclesCount();
// 	if(PrintDebugEn) cout<<"run pattern cycles count  :"<< GetExecutedCyclesCount<<endl;

    d2s::d2s_LABEL_BEGIN("LoadFirmwareToSram__holdMCUinResetMode1_step3_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    //Step3: Clear ecc/pariry interrupt
    SRAM.CPAPIRegs.setrameccerr(0x0).setromparerr(0x0).Write2DUT(9);

    //Step4: ECC/parity interrupt enable
    SRAM.CPAPIRegs.setmcuintmask(0x0C00).Write2DUT(10);

    //Ecc/parity error protection
    SRAM.CPAPIRegs.setinstromparerrmcuinhibit(0x1)
            .setinstrameccerrmcuinhibit(0x1)
            .setdatromparerrmcuinhibit(0x1)
            .setdatrameccerrmcuinhibit(0x1)
            .Write2DUT(15);

    //Enable ecc function
    SRAM.CPAPIRegs.setrameccbypass(0x0).Write2DUT(15);

    d2s::d2s_LABEL_END();

}

void SRAM_READ_BY_WORD(MACRO_LANE_SEL& MacroLane_Sel, INT Address, MACRO_DOUBLE& FWAbist_Result, UINT convertFlag, UINT sign) {

    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();


    //	fr.d2s_LABEL_BEGIN("H30V101_SRAM_read_",d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("SRAM_READ_BY_WORD_", Global_D2S_Mode);
    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        selectMacro(MacroID);

        ostringstream str;
        str << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << Address;
        jtag.read(Address >> 1, str.str());

    }
    //fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //		INT SiteID = CURRENT_SITE_NUMBER() - 1;
//
//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

            ostringstream str;
            str << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << Address;
            hout(DETAIL) << "Address: 0x" << hex << Address << "   " << "Data: 0x" << hex << (INT) jtag.getReadValue(str.str())[SiteID] << endl;
            //cout << "Address: 0x" << hex << Address << "   " << "Data: 0x" << hex << (INT) jtag.getReadValue(str.str())[SiteID] << endl;
            FWAbist_Result[SiteID][MacroID] = (INT) jtag.getReadValue(str.str())[SiteID];
            if (convertFlag == 1)//need to covert the 8bit high ->low
            {
                if (sign == 0) {
                    FWAbist_Result[SiteID][MacroID] = (((INT) FWAbist_Result[SiteID][MacroID] & 0xff00) >> 8) | (((INT) FWAbist_Result[SiteID][MacroID] & 0x00ff) << 8); //big edian
                } else {
                    if (((INT) FWAbist_Result[SiteID][MacroID] & 0x0080) != 0x80) {
                        FWAbist_Result[SiteID][MacroID] = (((INT) FWAbist_Result[SiteID][MacroID] & 0xff00) >> 8) | (((INT) FWAbist_Result[SiteID][MacroID] & 0x00ff) << 8); //big edian
                    } else {
                        FWAbist_Result[SiteID][MacroID] = (((INT) FWAbist_Result[SiteID][MacroID] & 0xff00) >> 8) | (((INT) FWAbist_Result[SiteID][MacroID] & 0x00ff) << 8) - 0x10000; //big edian
                    }
                }
            }
        }

        FOREACH_ACTIVESITE_END
}

bool DPM_Run(MACRO_LANE_SEL& MacroLane_Sel, UINT iRefclk0_freqm100, UINT iRefclk1_freqm100) {
    //	D2S_FRAMEWORK;
    //GET_TEST_INFO;

    //	sprintf(label, "H30V101_Config_DPM_testAPI_ReadTemp_%f_%f",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("H30V101_Config_DPM_testAPI_ReadTemp_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);

    //SRAM.CPAPIRegs.setmcurstb(0x0).setcsmasterifmode(0x2).setmcupwrdb(0x1).Write2DUT(8);
    SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8);

    Config_RefClk_CoreClk(iRefclk0_freqm100, iRefclk1_freqm100);
    //Configure DS calibration by pass enable
    SRAM.ABISTAPIRegs.setcorner_sensor_abist_api(0x1).Write2DUT(0);
    SRAM.ABISTAPIRegs.settest_mode_abist_api(0x1).Write2DUT(2);

    //SRAM.CPAPIRegs.setmcurstb(0x1).setcsmasterifmode(0x2).setmcupwrdb(0x1).Write2DUT(8);
    SRAM.CPAPIRegs.setmcurstb(0x1).Write2DUT(8);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    // monitor TOP_FSM_DONE until calibration finished
    // Wait for calibration to complete by checking status of TOP_FSM_DONE
    INT iCheckCount = 0;
    INT iMaxTimeout = 200; //SongXin: Put MaxTimeout out of for-loop to reduce test time, because check done is parallel for all sites.

    EXPECT_RESULT Top_Fsm_Result;

    //	do {
    //		iCheckCount++;
    ////		WAIT_TIME(10 ms);
    //                api->sleep(0.01);
    //		hout(DETAIL) << "iCheckCount : " << iCheckCount << endl;
    //		Check_Top_Fsm_Done(MacroLane_Sel, Top_Fsm_Result);
    //	} while (Top_Fsm_Result.allpass != true && iCheckCount < iMaxTimeout);
//    api->sleep(0.05);
//    TheInst.Wait(50*1000);
	TheInst.Wait(0.001 * 20);//2ms
    //todo :need to get the top fsm result

    /*************************/
    //Clear API
    /***********************/
    //	sprintf(label, "H30V101_DPM_Clear_API_%f_%f",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label, d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("H30V101_DPM_Clear_API_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8);
    SRAM.ABISTAPIRegs.setcorner_sensor_abist_api(0x0).Write2DUT(0);
    SRAM.ABISTAPIRegs.settest_mode_abist_api(0x0).Write2DUT(2);
    Clear_CS_API();
    Clear_DS_API(MacroLane_Sel);

    //fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    return true;
}

void Dump_SRAM_ByWord(MACRO_LANE_SEL& MacroLane_Sel) {
    ostringstream TestDatalog;
    INT isramAddr = 0x18000;
    MACRO_DOUBLE sramData;
    long long lsramData;
    INT MacroID = 0;
    MacroID = MacroLane_Sel[0].MacroID;

    TestDatalog << "\n" << "==========H30LRV101_SRAM_Dump_Start==========" << endl;
    for (INT i = 0; i < 32768 / 2; i++) {
        SRAM_READ_BY_WORD(MacroLane_Sel, isramAddr, sramData, 0);

        lsramData = sramData[0][MacroID];
        TestDatalog << hex << isramAddr << "=" << hex << lsramData << endl;
        //		cout<<"isramAddr:"<<hex<<isramAddr<<"  lsramData:"<<hex<<lsramData<<endl;
        isramAddr = isramAddr + 2;
    }
    TestDatalog << "\n" << "==========H30LRV101_SRAM_Dump_End==========" << endl;
    //	PUT_DATALOG(TestDatalog.str());
}

//Alos & dynamic write DS lane
//==============================================================================
// Function: EnableAlos
// - This function is used to enable signal loss detection
//==============================================================================

void EnableAlos(MACRO_LANE_SEL& MacroLane_Sel, const STRING& JtagContext) {
    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    //GET_TEST_INFO;

    //	sprintf(label,"MPB_H30V101LR_ALOS_Setup_Step1_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("MPB_H30V101LR_ALOS_Setup_Step1_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    DS.rxRegs.SliceID(0).Broadcast(1);
    DS.txRegs.SliceID(0).Broadcast(1);

    DS.rxRegs.setrxdigdetclkbufen(0x1).Write2DUT(38);
    DS.rxRegs.setrxsigdetclkdiv(0x03).Write2DUT(38);
    DS.rxRegs.setrxsigdetclkdlysel(0x0).Write2DUT(38);
    //DS.rxRegs.setrxsigdethyst(0x02).Write2DUT(39);
    //	if(JtagContext == "DEFAULT")
    //		DS.rxRegs.setrxsigdetvthres(0x02).Write2DUT(39);//ABIST use 2
    //	else
    //	DS.rxRegs.setrxsigdetvthres(0x03).Write2DUT(39);//ATE use 3
    DS.rxRegs.setsigdetwin(0x06).Write2DUT(40);
    DS.rxRegs.setsigdetthrs3(0x20).Write2DUT(43);

    DS.rxRegs.setsigdettxrxstat(0x1).Write2DUT(40);
    DS.rxRegs.setsigdetpmamode(0x0).Write2DUT(40);
    DS.rxRegs.setsigdetmanual(0x0).Write2DUT(40);
    DS.rxRegs.setsigdetthrselman(0x0).Write2DUT(40);
    DS.rxRegs.setsigdetthrcfgsel(0x0).Write2DUT(41);
    DS.rxRegs.setrxsigdetcalpwrdb(0x1).Write2DUT(38);

    DS.rxRegs.setrxsigdetpwrdb(0x1).Write2DUT(38);
    DS.rxRegs.setsigdeten(0x1).Write2DUT(40);

    //fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();


    //dynamic write CSR 39
    LANE_INT irxsigdetoffset;
    char IDstring[128] = "";
    //	sprintf(label,"H30V101LR_RXSIGDETOFFSET_ReadBack_DSCSR39");
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("H30V101LR_RXSIGDETOFFSET_ReadBack_DSCSR39", Global_D2S_Mode);
    for (UINT uiMacroIndex = 0; uiMacroIndex < MacroLane_Sel.size(); uiMacroIndex++) {
        UINT MacroID = MacroLane_Sel[uiMacroIndex].MacroID;
        selectMacro(MacroID);
        for (uint uiLaneIndex = 0; uiLaneIndex < MacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
            UINT LaneID = MacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];
            DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
            sprintf(IDstring, "DSRXCSR39_%d_%d", MacroID, LaneID);
            DS.rxRegs.Read2IDString(39, IDstring);
        }
    }

    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();

    //	FOR_EACH_SITE_BEGIN();
    //		INT SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT uiMacroIndex = 0; uiMacroIndex < MacroLane_Sel.size(); uiMacroIndex++) {
            for (uint uiLaneIndex = 0; uiLaneIndex < MacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
                UINT MacroID = MacroLane_Sel[uiMacroIndex].MacroID;
                UINT LaneID = MacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];
                sprintf(IDstring, "DSRXCSR39_%d_%d", MacroID, LaneID);
                DS.rxRegs.csr[39] = jtag.getReadValue(IDstring)[SiteID];
                irxsigdetoffset[SiteID][MacroID][LaneID] = DS.rxRegs.getrxsigdetoffset();
            }
        }
        FOREACH_ACTIVESITE_END

    //	sprintf(label,"H30V101LR_RXSIGDETOFFSET_Setup_Step2_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("H30V101LR_RXSIGDETOFFSET_Setup_Step2_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    DS.rxRegs.SliceID(0).Broadcast(1);
    DS.txRegs.SliceID(0).Broadcast(1);
    DS.rxRegs.setrxsigdetvthres(0x03).Write2DUT(39); //ATE use 3
    DS.rxRegs.setrxsigdethyst(0x02).Write2DUT(39);

    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();


    //Dynamic Write CSDFRefCode
    LANE_INT CSRvalue;
    CSR_READ(MacroLane_Sel, DS.rxRegs, 39, CSRvalue);
    Update_DSReg_ForDynamicWrite(MacroLane_Sel, DS.rxRegs.REG_INFO.rxsigdetoffset(), irxsigdetoffset, CSRvalue);

    //	sprintf(label,"MPB_H30V101LR_RXSIGDETOFFSET_Dynamic_Write_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("MPB_H30V101LR_RXSIGDETOFFSET_Dynamic_Write_", Global_D2S_Mode);
    for (uint uiMacroIndex = 0; uiMacroIndex < MacroLane_Sel.size(); uiMacroIndex++) {
        uint MacroID = MacroLane_Sel[uiMacroIndex].MacroID;
        selectMacro(MacroID);
        for (uint uiLaneIndex = 0; uiLaneIndex < MacroLane_Sel[uiMacroIndex].vLane.size(); uiLaneIndex++) {
            UINT LaneID = MacroLane_Sel[uiMacroIndex].vLane[uiLaneIndex];
            DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
            ostringstream id39;
            id39 << "CSR39_" << "_M" << MacroID << "_L" << LaneID << jtag.Context;
            map<int, long long> tmp;
            parseSiteDataFromLaneInt(tmp, CSRvalue, MacroID, LaneID);
            DS.rxRegs.Write2DUT_DYN(39, tmp, id39.str());
        }

    }
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();

//	Global_D2S_Mode= LearningMode;  ////ProductionMode//LearningMode
//	Global_D2S_Mode= ProductionMode;  ////ProductionMode//LearningMode
}

void CSConfigurationBeforeCalibration_PLLConfig(MACRO_LANE_SEL& MacroLane_Sel, CUSTPARA &CUSTpara, SSPARA &SSpara, CSPARA &CSpara) {
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    /*************Clear API and CSConfigBeforeCal***set proper API depending on applications and Release MCU********/

    hout(DETAIL) << "\n&&&&&&&&&&&&& CS calibration START! &&&&&&&&&&&&&&&\n" << endl;

    //-------------------- User Define Settings(PUG Don't have these settings) Begin -------------------------
    INT iPll0vcodiv = 0;

    /// vco divider ratio. "Ka","Na","M"
    /// [1:0]       Ka         [1:0]     Na     [1:0]   M    [1:0]   Kb
    ///   00:       1          00        1      00      1    00      1
    ///   01:       1.5        01        2      01      1    01      2
    ///   10:       2          10        3      10      2    10      3
    ///   11:       2          11        2      11      3    11      x
    uint iPllka, iPllna, iPllM, iPllkb;
    if (CSpara.KaDiv == 2) {
        iPllka = 2;
    } else if (CSpara.KaDiv == 1.5) {
        iPllka = 1;
    } else if (CSpara.KaDiv == 1) {
        iPllka = 0;
    } else {
        //        cout << "ERROR: Incorrect Ka value !!!!!!!!!" << endl;
        printf("ERROR: Incorrect Ka value !!!!!!!!!\n");
    }

    if (CSpara.NaDiv == 1) {
        iPllna = 0;
    } else if (CSpara.NaDiv == 2) {
        iPllna = 1;
    } else if (CSpara.NaDiv == 3) {
        iPllna = 2;
    }//TODO: UFLEX Na = iPllna, 93K: Na= 1, iPllna = 0
    else {
        //		cout << "ERROR: Incorrect Na value !!!!!!!!!" << endl;
        printf("ERROR: Incorrect Na value !!!!!!!!!\n");
    }

    if (CSpara.Mdiv == 1) {
        iPllM = 1;
    } else if (CSpara.Mdiv == 2) {
        iPllM = 2;
    } else if (CSpara.Mdiv == 3) {
        iPllM = 3;
    }//TODO: UFLEX M = iPllM, 93K: M= 1, iPllM = 0
    else {
        //		cout << "ERROR: Incorrect M value !!!!!!!!!" << endl;
        printf("ERROR: Incorrect M value !!!!!!!!!\n");
    }

    if (CSpara.KbDiv == 1) {
        iPllkb = 0;
    } else if (CSpara.KbDiv == 2) {
        iPllkb = 1;
    } else if (CSpara.KbDiv == 3) {
        iPllkb = 2;
    } else {
        //        cout << "ERROR: Incorrect Kb value !!!!!!!!!" << endl;
        printf("ERROR: Incorrect Kb value !!!!!!!!!\n");
    }

    iPll0vcodiv = iPllka + (iPllna << 2);

    //	INT iFbdivp = p_s[CSpara.NbDiv - 18] >> 8;  //Please refer to p_s define header file for explaination //SongXin: need to setup minus value setting
    //	INT iFbdivs = p_s[CSpara.NbDiv - 18] & 0x0F;

    INT iFbdivp = CSpara.Pvalue;
    INT iFbdivs = CSpara.Svalue;
    INT iCheckNb = 4 * iFbdivp + iFbdivs + 6;

    if (iCheckNb != CSpara.NbDiv) {
        //		cout << "ERROR: Nb( "<< CSpara.NbDiv <<  ")in test plan don't equal to caculated Nb("<< iCheckNb <<")by P and S in test plan!!!"<< endl;
        printf("ERROR: Nb(%d)in test plan don't equal to caculated Nb(%d)by P and S in test plan!!!\n", CSpara.NbDiv, iCheckNb);
    }
    //	char IDstring[128] = "";
    selectMacro_Now(MacroLane_Sel[0].MacroID);
    CS.clkRegs.MacroID(MacroLane_Sel[0].MacroID).Broadcast(0);
    CS.clkRegs.Read2CSR(1);

    //INT iSetpll1hsclkdistspare =  (CS.clkRegs.getpll0hsclkdistspare()) | (CSpara.HsClkDistClkSpare_Bit2 << 2); //bit[2] of pll1hsclkdistspare
    INT iSetpll1hsclkdistspare = 0x0 | (CSpara.HsClkDistClkSpare_Bit2 << 2); //bit[2] of pll1hsclkdistspare

    // -------------------- User Define Settings(PUG Don't have these settings) End -------------------------

    // There is a PUG bug, copy it with UFLEX to bypass this part-- Song Xin
    //At least one PLL should power up
    //Please note that PLL1 can be only powered up when PLL0 is already on



    if (CUSTpara.PllSel == 1) {
        //Power up PLL0 and PLL1
        //		CsPllPowerup(MacroLane_Sel,1);
        d2s::d2s_LABEL_BEGIN("CSConfig_Set_CS_pll1_divider_", Global_D2S_Mode);
        if (SSpara.RefclkBus == -1) {
            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

                selectMacro(MacroID);
                CS.clkRegs.SliceID(0).Broadcast(1);

                if (GlobalInitPattern.find("_Case01") != string::npos)
                    SSpara.RefclkBus = HILINK_INFO[MacroID].RefclockChoose[0];
                else if (GlobalInitPattern.find("_Case02") != string::npos)
                    SSpara.RefclkBus = HILINK_INFO[MacroID].RefclockChoose[1];
                else if (GlobalInitPattern.find("_Case03") != string::npos)
                    SSpara.RefclkBus = HILINK_INFO[MacroID].RefclockChoose[2];
                else {
                    //						cout << "Can't find valid init pattern !!! Please check pattern name!" << endl;
                    printf("Can't find valid init pattern !!! Please check pattern name!\n");
                }
                if (SSpara.RefclkBus != 1 && SSpara.RefclkBus != 0 && SSpara.RefclkBus != -1) {
                    //					cout << "Invalid macro has been choose !!! Please check macro ID!" << endl;
                    printf("Invalid macro has been choose !!! Please check macro ID!\n");
                }
                CS.clkRegs.setpll1refclksel(SSpara.RefclkBus).Write2DUT(3, false); //Select reference clock source

                //Set Clockslice PLL1 divider ratioss
                CS.clkRegs.setpll1refclkdiv(iPllM)//PLL1 M divider setting
                        .setpll1vcodivka(iPllka)//PLL1 Ka divider setting
                        .setpll1vcodivna(iPllna)//PLL1 Na divider setting
                        .setpll1fbdivp(iFbdivp) //Part of PLL1 Nb divider setting
                        .setpll1fbdivs(iFbdivs).Write2DUT(3, false); //Part of PLL1 Nb divider setting
                CS.clkRegs.setpll1hsclkdiv(iPllkb)//PLL1 Kb divider setting
                        .setpll1hsclkdistspare(iSetpll1hsclkdistspare)
                        .setpll1mclkdiv40b(CSpara.J40bdiv) // PLL1 J_40b divider setting
                        .setpll1mclkdiv32b(CSpara.J32bdiv).Write2DUT(4, false); // Pll1 J_32b divider setting

                //add for pll1 ref1 fwcal fail      ---20171027

                CS.clkRegs.setpll0refclksel(SSpara.RefclkBus).Write2DUT(0, false); //Select reference clock source

                //							CS.clkRegs.setpll0vcodivka(iPllka)//PLL0 Ka divider setting
                //									 .setpll0vcodivna(iPllna)//PLL0 Na divider setting
                //									 .setpll0fbdivp(iFbdivp)//Part of PLL0 Nb divider setting
                //									 .setpll0fbdivs(iFbdivs+1).Write2DUT(0); //Part of PLL0 Nb divider setting
                //
                //							CS.clkRegs.setpll0refclkdiv(iPllM)//PLL0 M divider setting
                //									.setpll0hsclkdiv(iPllkb)//PLL0 Kb divider setting
                //									.setpll0hsclkdistspare(iSetpll1hsclkdistspare)
                //									.setpll0mclkdiv40b(CSpara.J40bdiv)// PLL0 J_40b divider setting
                //									.setpll0mclkdiv32b(CSpara.J32bdiv).Write2DUT(1); // Pll0 J_32b divider setting
            }
        } else if (SSpara.RefclkBus == 0 or SSpara.RefclkBus == 1) {
            selectMacro_MB(MacroLane_Sel);

            CS.clkRegs.setpll1refclksel(SSpara.RefclkBus).Write2DUT(3); //Select reference clock source

            //Set Clockslice PLL1 divider ratioss
            CS.clkRegs.setpll1refclkdiv(iPllM)//PLL1 M divider setting
                    .setpll1vcodivka(iPllka)//PLL1 Ka divider setting
                    .setpll1vcodivna(iPllna)//PLL1 Na divider setting
                    .setpll1fbdivp(iFbdivp) //Part of PLL1 Nb divider setting
                    .setpll1fbdivs(iFbdivs).Write2DUT(3); //Part of PLL1 Nb divider setting
            CS.clkRegs.setpll1hsclkdiv(iPllkb)//PLL1 Kb divider setting
                    .setpll1hsclkdistspare(iSetpll1hsclkdistspare)
                    .setpll1mclkdiv40b(CSpara.J40bdiv) // PLL1 J_40b divider setting
                    .setpll1mclkdiv32b(CSpara.J32bdiv).Write2DUT(4); // Pll1 J_32b divider setting

            CS.clkRegs.setpll0refclksel(SSpara.RefclkBus).Write2DUT(0); //Select reference clock source

        } else {
            //				cout<<"ERROR: RefClkBus SEL is Out of Range or Empty!"<<endl;
            printf("ERROR: RefClkBus SEL is Out of Range or Empty!\n");
        }
        d2s::d2s_LABEL_END();
    } else if (CUSTpara.PllSel == 0) {
        //Power up PLL0 only
        CsPllPowerup(MacroLane_Sel, 0);

        d2s::d2s_LABEL_BEGIN("CSConfig_Set_CS_pll0_divider_", Global_D2S_Mode);
        if (SSpara.RefclkBus == -1) {
            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

                selectMacro(MacroID);
                CS.clkRegs.SliceID(0).Broadcast(1);

                if (GlobalInitPattern.find("_Case01") != string::npos)
                    SSpara.RefclkBus = HILINK_INFO[MacroID].RefclockChoose[0];
                else if (GlobalInitPattern.find("_Case02") != string::npos)
                    SSpara.RefclkBus = HILINK_INFO[MacroID].RefclockChoose[1];
                else if (GlobalInitPattern.find("_Case03") != string::npos)
                    SSpara.RefclkBus = HILINK_INFO[MacroID].RefclockChoose[2];
                else {
                    //						cout << "Can't find valid init pattern !!! Please check pattern name!" << endl;
                    printf("Can't find valid init pattern !!! Please check pattern name!\n");
                }
                if (SSpara.RefclkBus != 1 && SSpara.RefclkBus != 0 && SSpara.RefclkBus != -1) {
                    //						cout << "Invalid macro has been choose !!! Please check macro ID!" << endl;
                    printf("Invalid macro has been choose !!! Please check macro ID!\n");
                }
                CS.clkRegs.setpll0refclksel(SSpara.RefclkBus).Write2DUT(0, false); //Select reference clock source
                CS.clkRegs.setpll1refclksel(SSpara.RefclkBus).Write2DUT(3, false); //Select reference clock source

                //Set Clockslice PLL0 divider ratios
                CS.clkRegs.setpll0refclkdiv(iPllM)//PLL0 M divider setting
                        .setpll0hsclkdiv(iPllkb)//PLL0 Kb divider setting
                        .setpll0hsclkdistspare(iSetpll1hsclkdistspare)
                        .setpll0mclkdiv40b(CSpara.J40bdiv)// PLL0 J_40b divider setting
                        .setpll0mclkdiv32b(CSpara.J32bdiv).Write2DUT(1, false); // Pll0 J_32b divider setting
                CS.clkRegs.setpll0vcodivka(iPllka)//PLL0 Ka divider setting
                        .setpll0vcodivna(iPllna)//PLL0 Na divider setting
                        .setpll0fbdivp(iFbdivp)//Part of PLL0 Nb divider setting
                        .setpll0fbdivs(iFbdivs).Write2DUT(0, false); //Part of PLL0 Nb divider setting
            }
        } else if (SSpara.RefclkBus == 1 or SSpara.RefclkBus == 0) {
            selectMacro_MB(MacroLane_Sel);

            CS.clkRegs.setpll0refclksel(SSpara.RefclkBus).Write2DUT(0); //Select reference clock source
            CS.clkRegs.setpll1refclksel(SSpara.RefclkBus).Write2DUT(3); //Select reference clock source

            //Set Clockslice PLL0 divider ratios
            CS.clkRegs.setpll0refclkdiv(iPllM)//PLL0 M divider setting
                    .setpll0hsclkdiv(iPllkb)//PLL0 Kb divider setting
                    .setpll0hsclkdistspare(iSetpll1hsclkdistspare)
                    .setpll0mclkdiv40b(CSpara.J40bdiv)// PLL0 J_40b divider setting
                    .setpll0mclkdiv32b(CSpara.J32bdiv).Write2DUT(1); // Pll0 J_32b divider setting
            CS.clkRegs.setpll0vcodivka(iPllka)//PLL0 Ka divider setting
                    .setpll0vcodivna(iPllna)//PLL0 Na divider setting
                    .setpll0fbdivp(iFbdivp)//Part of PLL0 Nb divider setting
                    .setpll0fbdivs(iFbdivs).Write2DUT(0); //Part of PLL0 Nb divider setting
        } else {
            //				cout<<"ERROR: RefClkBus SEL is Out of Range or Empty!"<<endl;
            printf("ERROR: RefClkBus SEL is Out of Range or Empty!\n");
        }
        d2s::d2s_LABEL_END();
        //Power down PLL1
        CsPllPowerDown(MacroLane_Sel, 1);
    } else if (CUSTpara.PllSel == -1) {
        //Power up PLL0 and PLL1
        CsPllPowerup(MacroLane_Sel, 1);

        d2s::d2s_LABEL_BEGIN("CSConfig_Set_CS_pll0_pll1_divider_", Global_D2S_Mode);
        if (SSpara.RefclkBus == -1) {
            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

                selectMacro(MacroID);
                CS.clkRegs.SliceID(0).Broadcast(1);

                if (GlobalInitPattern.find("_Case01") != string::npos)
                    SSpara.RefclkBus = HILINK_INFO[MacroID].RefclockChoose[0];
                else if (GlobalInitPattern.find("_Case02") != string::npos)
                    SSpara.RefclkBus = HILINK_INFO[MacroID].RefclockChoose[1];
                else if (GlobalInitPattern.find("_Case03") != string::npos)
                    SSpara.RefclkBus = HILINK_INFO[MacroID].RefclockChoose[2];
                else {
                    //						cout << "Can't find valid init pattern !!! Please check pattern name!" << endl;
                    printf("Can't find valid init pattern !!! Please check pattern name!\n");
                }
                if (SSpara.RefclkBus != 1 && SSpara.RefclkBus != 0 && SSpara.RefclkBus != -1) {
                    //						cout << "Invalid macro has been choose !!! Please check macro ID!" << endl;
                    printf("Invalid macro has been choose !!! Please check macro ID!\n");
                }
                CS.clkRegs.setpll1refclksel(SSpara.RefclkBus).Write2DUT(3, false); //Select reference clock source
                CS.clkRegs.setpll0refclksel(SSpara.RefclkBus).Write2DUT(0, false); //Select reference clock source

                //Set Clockslice PLL1 divider ratios
                CS.clkRegs.setpll1refclkdiv(iPllM)//PLL1 M divider setting
                        .setpll1vcodivka(iPllka)//PLL1 Ka divider setting
                        .setpll1vcodivna(iPllna)//PLL1 Na divider setting
                        .setpll1fbdivp(iFbdivp)//Part of PLL1 Nb divider setting
                        .setpll1fbdivs(iFbdivs).Write2DUT(3, false); //Part of PLL1 Nb divider setting

                CS.clkRegs.setpll1hsclkdiv(iPllkb) //PLL1 Kb divider setting
                        .setpll1hsclkdistspare(iSetpll1hsclkdistspare)
                        .setpll1mclkdiv40b(CSpara.J40bdiv) // PLL1 J_40b divider setting
                        .setpll1mclkdiv32b(CSpara.J32bdiv).Write2DUT(4, false); // Pll1 J_32b divider setting

                //Set Clockslice PLL0 divider ratios
                CS.clkRegs.setpll0vcodivka(iPllka)//PLL0 Ka divider setting
                        .setpll0vcodivna(iPllna)//PLL0 Na divider setting
                        .setpll0fbdivp(iFbdivp)//Part of PLL0 Nb divider setting
                        .setpll0fbdivs(iFbdivs).Write2DUT(0, false); //Part of PLL0 Nb divider setting

                CS.clkRegs.setpll0refclkdiv(iPllM)//PLL0 M divider setting
                        .setpll0hsclkdiv(iPllkb)//PLL0 Kb divider setting
                        .setpll0hsclkdistspare(iSetpll1hsclkdistspare)
                        .setpll0mclkdiv40b(CSpara.J40bdiv)// PLL0 J_40b divider setting
                        .setpll0mclkdiv32b(CSpara.J32bdiv).Write2DUT(1, false); // Pll0 J_32b divider setting
            }
        } else if (SSpara.RefclkBus == 1 or SSpara.RefclkBus == 0) {
            selectMacro_MB(MacroLane_Sel);


            CS.clkRegs.setpll1refclksel(SSpara.RefclkBus).Write2DUT(3); //Select reference clock source
            CS.clkRegs.setpll0refclksel(SSpara.RefclkBus).Write2DUT(0); //Select reference clock source

            //Set Clockslice PLL1 divider ratios
            CS.clkRegs.setpll1refclkdiv(iPllM)//PLL1 M divider setting
                    .setpll1vcodivka(iPllka)//PLL1 Ka divider setting
                    .setpll1vcodivna(iPllna)//PLL1 Na divider setting
                    .setpll1fbdivp(iFbdivp)//Part of PLL1 Nb divider setting
                    .setpll1fbdivs(iFbdivs).Write2DUT(3); //Part of PLL1 Nb divider setting

            CS.clkRegs.setpll1hsclkdiv(iPllkb) //PLL1 Kb divider setting
                    .setpll1hsclkdistspare(iSetpll1hsclkdistspare)
                    .setpll1mclkdiv40b(CSpara.J40bdiv) // PLL1 J_40b divider setting
                    .setpll1mclkdiv32b(CSpara.J32bdiv).Write2DUT(4); // Pll1 J_32b divider setting

            //Set Clockslice PLL0 divider ratios
            CS.clkRegs.setpll0vcodivka(iPllka)//PLL0 Ka divider setting
                    .setpll0vcodivna(iPllna)//PLL0 Na divider setting
                    .setpll0fbdivp(iFbdivp)//Part of PLL0 Nb divider setting
                    .setpll0fbdivs(iFbdivs).Write2DUT(0); //Part of PLL0 Nb divider setting

            CS.clkRegs.setpll0refclkdiv(iPllM)//PLL0 M divider setting
                    .setpll0hsclkdiv(iPllkb)//PLL0 Kb divider setting
                    .setpll0hsclkdistspare(iSetpll1hsclkdistspare)
                    .setpll0mclkdiv40b(CSpara.J40bdiv)// PLL0 J_40b divider setting
                    .setpll0mclkdiv32b(CSpara.J32bdiv).Write2DUT(1); // Pll0 J_32b divider setting
        } else {
            //				cout<<"ERROR: RefClkBus SEL is Out of Range or Empty!"<<endl;
            printf("ERROR: RefClkBus SEL is Out of Range or Empty!\n");
        }
        d2s::d2s_LABEL_END();
    } else {
        //			cout<<"ERROR: PLL SEL is Out of Range or Empty!"<<endl;
        printf("ERROR: PLL SEL is Out of Range or Empty!\n");
    }

    // customer should confirm with hilink support team for extra settings
}


//zhenge add for csrverify begin






//FWABIST

void WritePerMacroSpecToSram(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE) {
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    d2s::d2s_LABEL_BEGIN("WritePerMacroSpecToSram_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_SS_FWABIST_REG_count(); RegIndex++) {

        uint temp_SpecHigh_Address = FWABIST_REG_BASE.get_SS_FWABIST_REG(RegIndex).SpecHigh_Address;
        if (temp_SpecHigh_Address > 0) {
            uint temp_SpecHigh_Value = FWABIST_REG_BASE.get_SS_FWABIST_REG(RegIndex).SpecHigh_Value * FWABIST_REG_BASE.get_SS_FWABIST_REG(RegIndex).Spec_Wrttern_Rate;
            temp_SpecHigh_Value = (((INT) temp_SpecHigh_Value & 0xff00) >> 8) | (((INT) temp_SpecHigh_Value & 0x00ff) << 8); //big edian


            uint temp_SpecLow_Address = FWABIST_REG_BASE.get_SS_FWABIST_REG(RegIndex).SpecLow_Address;
            uint temp_SpecLow_Value = FWABIST_REG_BASE.get_SS_FWABIST_REG(RegIndex).SpecLow_Value * FWABIST_REG_BASE.get_SS_FWABIST_REG(RegIndex).Spec_Wrttern_Rate;
            temp_SpecLow_Value = (((INT) temp_SpecLow_Value & 0xff00) >> 8) | (((INT) temp_SpecLow_Value & 0x00ff) << 8); //big edian


            hout(DETAIL) << "Write SpecHigh: " << hex << "0x " << temp_SpecHigh_Address << " Value: " << dec << temp_SpecHigh_Value << endl;
            hout(DETAIL) << "Write SpecLow: " << hex << "0x " << temp_SpecLow_Address << " Value: " << dec << temp_SpecLow_Value << endl;

            jtag.write(temp_SpecHigh_Address >> 1, temp_SpecHigh_Value);
            jtag.write(temp_SpecLow_Address >> 1, temp_SpecLow_Value);
        }


    }
    for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_SS_FWABIST_Calculate_REG_count(); RegIndex++) {

        uint temp_SpecHigh_Address = FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).SpecHigh_Address;
        if (temp_SpecHigh_Address > 0) {
            uint temp_SpecHigh_Value = FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).SpecHigh_Value * FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).Spec_Wrttern_Rate;
            temp_SpecHigh_Value = (((INT) temp_SpecHigh_Value & 0xff00) >> 8) | (((INT) temp_SpecHigh_Value & 0x00ff) << 8); //big edian

            uint temp_SpecLow_Address = FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).SpecLow_Address;
            uint temp_SpecLow_Value = FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).SpecLow_Value * FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).Spec_Wrttern_Rate;
            temp_SpecLow_Value = (((INT) temp_SpecLow_Value & 0xff00) >> 8) | (((INT) temp_SpecLow_Value & 0x00ff) << 8); //big edian

            hout(DETAIL) << "Write Calculate SpecHigh: " << hex << "0x " << temp_SpecHigh_Address << " Value: " << dec << temp_SpecHigh_Value << endl;
            hout(DETAIL) << "Write Calculate SpecLow: " << hex << "0x " << temp_SpecLow_Address << " Value: " << dec << temp_SpecLow_Value << endl;

            jtag.write(temp_SpecHigh_Address >> 1, temp_SpecHigh_Value);
            jtag.write(temp_SpecLow_Address >> 1, temp_SpecLow_Value);
        }

    }
    for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_CS_FWABIST_REG_count(); RegIndex++) {

        uint temp_SpecHigh_Address = FWABIST_REG_BASE.get_CS_FWABIST_REG(RegIndex).SpecHigh_Address;

        if (temp_SpecHigh_Address > 0) {
            uint temp_SpecHigh_Value = FWABIST_REG_BASE.get_CS_FWABIST_REG(RegIndex).SpecHigh_Value * FWABIST_REG_BASE.get_CS_FWABIST_REG(RegIndex).Spec_Wrttern_Rate;
            temp_SpecHigh_Value = (((INT) temp_SpecHigh_Value & 0xff00) >> 8) | (((INT) temp_SpecHigh_Value & 0x00ff) << 8); //big edian


            uint temp_SpecLow_Address = FWABIST_REG_BASE.get_CS_FWABIST_REG(RegIndex).SpecLow_Address;
            uint temp_SpecLow_Value = FWABIST_REG_BASE.get_CS_FWABIST_REG(RegIndex).SpecLow_Value * FWABIST_REG_BASE.get_CS_FWABIST_REG(RegIndex).Spec_Wrttern_Rate;
            temp_SpecLow_Value = (((INT) temp_SpecLow_Value & 0xff00) >> 8) | (((INT) temp_SpecLow_Value & 0x00ff) << 8); //big edian


            hout(DETAIL) << "Write SpecHigh: " << hex << "0x " << temp_SpecHigh_Address << " Value: " << dec << temp_SpecHigh_Value << endl;
            hout(DETAIL) << "Write SpecLow: " << hex << "0x " << temp_SpecLow_Address << " Value: " << dec << temp_SpecLow_Value << endl;

            jtag.write(temp_SpecHigh_Address >> 1, temp_SpecHigh_Value);
            jtag.write(temp_SpecLow_Address >> 1, temp_SpecLow_Value);
        }


    }

    for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_CS_FWABIST_Calculate_REG_count(); RegIndex++) {

        uint temp_SpecHigh_Address = FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).SpecHigh_Address;
        if (temp_SpecHigh_Address > 0) {
            uint temp_SpecHigh_Value = FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).SpecHigh_Value * FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).Spec_Wrttern_Rate;
            temp_SpecHigh_Value = (((INT) temp_SpecHigh_Value & 0xff00) >> 8) | (((INT) temp_SpecHigh_Value & 0x00ff) << 8); //big edian

            uint temp_SpecLow_Address = FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).SpecLow_Address;
            uint temp_SpecLow_Value = FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).SpecLow_Value * FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).Spec_Wrttern_Rate;
            temp_SpecLow_Value = (((INT) temp_SpecLow_Value & 0xff00) >> 8) | (((INT) temp_SpecLow_Value & 0x00ff) << 8); //big edian

            hout(DETAIL) << "Write Calculate SpecHigh: " << hex << "0x " << temp_SpecHigh_Address << " Value: " << dec << temp_SpecHigh_Value << endl;
            hout(DETAIL) << "Write Calculate SpecLow: " << hex << "0x " << temp_SpecLow_Address << " Value: " << dec << temp_SpecLow_Value << endl;

            jtag.write(temp_SpecHigh_Address >> 1, temp_SpecHigh_Value);
            jtag.write(temp_SpecLow_Address >> 1, temp_SpecLow_Value);
        }

    }

    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();

    if (hout.getLevel() > 1) {
        //For debug, Check whether every thing is written correctly
        FW_ABIST_CSArrayD_ReadBack(MacroLane_Sel, FWABIST_REG_BASE);
        FW_ABIST_SSArrayD_ReadBack(MacroLane_Sel, FWABIST_REG_BASE);
    }
}

void WritePerLaneSpecToSram(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE, const STRING& useExternalRAM) {
    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    //GET_TEST_INFO;

    if (useExternalRAM == "YES") {
#ifdef 	TestChip
        FW_TASK("DCRT RAM,(pAHB)");
#else
        //			FW_TASK("DCRT RAM,(pJTAG)");
#endif
    }

    //	sprintf(label,"WritePerlaneSpecToSram_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("WritePerlaneSpecToSram_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);

    //All lane write same spec to same address, so here NO need to write lane loop
    for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_DS_FWABIST_REG_count(); RegIndex++) {

        uint temp_SpecHigh_Address = FWABIST_REG_BASE.get_DS_FWABIST_REG(RegIndex).SpecHigh_Address;
        uint temp_SpecHigh_Value = FWABIST_REG_BASE.get_DS_FWABIST_REG(RegIndex).SpecHigh_Value * FWABIST_REG_BASE.get_DS_FWABIST_REG(RegIndex).Spec_Wrttern_Rate;
        temp_SpecHigh_Value = (((INT) temp_SpecHigh_Value & 0xff00) >> 8) | (((INT) temp_SpecHigh_Value & 0x00ff) << 8); //big edian

        uint temp_SpecLow_Address = FWABIST_REG_BASE.get_DS_FWABIST_REG(RegIndex).SpecLow_Address;
        uint temp_SpecLow_Value = FWABIST_REG_BASE.get_DS_FWABIST_REG(RegIndex).SpecLow_Value * FWABIST_REG_BASE.get_DS_FWABIST_REG(RegIndex).Spec_Wrttern_Rate;
        temp_SpecLow_Value = (((INT) temp_SpecLow_Value & 0xff00) >> 8) | (((INT) temp_SpecLow_Value & 0x00ff) << 8); //big edian

        jtag.write(temp_SpecHigh_Address >> 1, temp_SpecHigh_Value);
        jtag.write(temp_SpecLow_Address >> 1, temp_SpecLow_Value);

        hout(DETAIL) << "Write DS Calculate SpecHigh: " << hex << "0x " << temp_SpecHigh_Address << " Value: " << dec << temp_SpecHigh_Value << endl;
        hout(DETAIL) << "Write DS Calculate SpecLow: " << hex << "0x " << temp_SpecLow_Address << " Value: " << dec << temp_SpecLow_Value << endl;

    }

    //All lane write same spec to same address, so here NO need to write lane loop
    for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_DS_FWABIST_Calculate_REG_count(); RegIndex++) {

        uint temp_SpecHigh_Address = FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).SpecHigh_Address;
        uint temp_SpecHigh_Value = FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).SpecHigh_Value * FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Spec_Wrttern_Rate;
        temp_SpecHigh_Value = (((INT) temp_SpecHigh_Value & 0xff00) >> 8) | (((INT) temp_SpecHigh_Value & 0x00ff) << 8); //big edian

        uint temp_SpecLow_Address = FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).SpecLow_Address;
        uint temp_SpecLow_Value = FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).SpecLow_Value * FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Spec_Wrttern_Rate;
        temp_SpecLow_Value = (((INT) temp_SpecLow_Value & 0xff00) >> 8) | (((INT) temp_SpecLow_Value & 0x00ff) << 8); //big edian


        jtag.write(temp_SpecHigh_Address >> 1, temp_SpecHigh_Value);
        jtag.write(temp_SpecLow_Address >> 1, temp_SpecLow_Value);

        hout(DETAIL) << "Write DS Calculate SpecHigh: " << hex << "0x " << temp_SpecHigh_Address << " Value: " << dec << temp_SpecHigh_Value << endl;
        hout(DETAIL) << "Write DS Calculate SpecLow: " << hex << "0x " << temp_SpecLow_Address << " Value: " << dec << temp_SpecLow_Value << endl;


    }


    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();


    if (hout.getLevel() > 1) {
        //For debug, Check whether every thing is written correctly
        FW_ABIST_DSArrayD_ReadBack(MacroLane_Sel, FWABIST_REG_BASE);

    }
    if (useExternalRAM == "YES") {
#ifdef TestChip
        FW_TASK("DCRT TP,(pAHB)");
#else
        //	FW_TASK("DCRT TP,(pJTAG)");
#endif
    }

}

void WriteSingleSpecToSram(const MACRO_LANE_SEL& MacroLane_Sel, INT SpecHigh_Address, DOUBLE SpecHigh_Data, INT SpecLow_Address, DOUBLE SpecLow_Data, INT SpecWrittenRate) {
    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();
    //GET_TEST_INFO;

    //	sprintf(label,"WritePerlaneSpecToSram_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("WritePerlaneSpecToSram_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);

    //All lane write same spec to same address, so here NO need to write lane loop

    INT SpecHigh_Data_tmp = 0;
    INT SpecLow_Data_tmp = 0;
    SpecHigh_Data_tmp = (int) (SpecHigh_Data * SpecWrittenRate);
    SpecLow_Data_tmp = (int) (SpecLow_Data * SpecWrittenRate);

    SpecHigh_Data_tmp = ((SpecHigh_Data_tmp & 0xff00) >> 8) | ((SpecHigh_Data_tmp & 0x00ff) << 8); //big edian
    SpecLow_Data_tmp = ((SpecLow_Data_tmp & 0xff00) >> 8) | ((SpecLow_Data_tmp & 0x00ff) << 8); //big edian

    jtag.write(SpecHigh_Address >> 1, (int) SpecHigh_Data_tmp);
    jtag.write(SpecLow_Address >> 1, (int) SpecLow_Data_tmp);

    hout(GENERAL) << "WRITE SpecHigh ADDRESS= 0x" << hex << SpecHigh_Address << " Data= 0x" << hex << SpecHigh_Data_tmp << endl;
    hout(GENERAL) << "WRITE SpecLow  ADDRESS= 0x" << hex << SpecLow_Address << " Data= 0x" << hex << SpecLow_Data_tmp << endl;

    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();

    if (hout.getLevel() > 1) {
        //For debug, Check whether every thing is written correctly
        FW_ABIST_SingleSpec_ReadBack(MacroLane_Sel, SpecHigh_Address, SpecLow_Address);
    }
}

void Config_RefClk_CoreClk(UINT iRefclk0_freqm100, UINT iRefclk1_freqm100) {
    //Configure refclk frequency, users can get the information at frequency plan
    SRAM.CSAPIRegs.setrefclk0_freqm100_api(iRefclk0_freqm100).Write2DUT(1);
    SRAM.CSAPIRegs.setrefclk1_freqm100_api(iRefclk1_freqm100).Write2DUT(2);
    //Configure core_clk select
    SRAM.CSAPIRegs.setcore_clk_selext_pin_api(giCore_clk_selext_pin_api).Write2DUT(0);
    SRAM.CSAPIRegs.setcore_clk_sel_pin_api(giCore_clk_sel_pin_api).Write2DUT(0);
    SRAM.CSAPIRegs.setlifeclk2dig_sel_pin_api(giLifeclk2dig_sel_pin_api).Write2DUT(0);
    SRAM.CSAPIRegs.setcoreclk_sel_en_api(0x1).Write2DUT(4);
}

void ReleaseMCU(MACRO_LANE_SEL& MacroLane_Sel) {
    //	D2S_FRAMEWORK;
    //GET_TEST_INFO;

    //	sprintf(label,"H30V101_ReleaseMCU_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("H30V101_ReleaseMCU_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    SRAM.CPAPIRegs.setmcurstb(0x1).Write2DUT(8);
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
}

void ResetMCU(MACRO_LANE_SEL& MacroLane_Sel) {
    d2s::d2s_LABEL_BEGIN("H30V101_ResetMCU_", Global_D2S_Mode);
    selectMacro_MB(MacroLane_Sel);
    SRAM.CPAPIRegs.setmcurstb(0x0).Write2DUT(8);
    d2s::d2s_LABEL_END();
}

void FW_ABIST_RESULT_READ(const MACRO_LANE_SEL& MacroLane_Sel, INT Address, MACRO_DOUBLE& FWAbist_Result) {
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    d2s::d2s_LABEL_BEGIN("H30V101_SRAM_read_", Global_D2S_Mode);
    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        selectMacro(MacroID);

        ostringstream str;
        str << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << Address;
        jtag.read(Address >> 1, str.str());

    }
    d2s::d2s_LABEL_END();

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

            ostringstream str;
            str << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << Address;
            hout(DETAIL) << "Address: 0x" << hex << Address << "   " << "Data: 0x" << hex << (INT) jtag.getReadValue(str.str())[SiteID] << endl;
            FWAbist_Result[SiteID][MacroID] = (INT) jtag.getReadValue(str.str())[SiteID];
            FWAbist_Result[SiteID][MacroID] = (((INT) FWAbist_Result[SiteID][MacroID]& 0xff00) >> 8) | (((INT) FWAbist_Result[SiteID][MacroID]& 0x00ff) << 8); //big edian
        }
        FOREACH_ACTIVESITE_END
}

void PrinfToEdf_FWAbist(ostringstream& TestDatalog) {

    ostringstream PrintToDatalog_Str;
    STRING_VECTOR plot;

    parseListOfString(TestDatalog.str(), plot, ',');
    for (uint i = 0; i < plot.size(); i++) {



        PrintToDatalog_Str << plot[i];

        if (i % 5 != 0)
            PrintToDatalog_Str << "\t";


        if (i == 0) {
            for (int magic = 0; magic < 16; magic++) {
                PrintToDatalog_Str << endl;
            }
        }
        if (i % 5 == 0) //Change lines every 5 regs
        {

            PrintToDatalog_Str << endl;
        }
    }

    PrintToDatalog_Str << endl;
    //	PUT_DATALOG(PrintToDatalog_Str.str());

}

void FW_ABIST_READ_HVCC(const MACRO_LANE_SEL& MacroLane_Sel, INT DSStartAddress, INT DSIncreaseStep, INT CSStartAddress, MACRO_DOUBLE& CSInfo, LANE_DOUBLE& DsInfo) {
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    d2s::d2s_LABEL_BEGIN("H30V101_HVCC_And_ErrorMessage_read_", Global_D2S_Mode);
    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        selectMacro(MacroID);

        ostringstream str;
        str << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << CSStartAddress;
        jtag.read(CSStartAddress >> 1, str.str());

    }
    d2s::d2s_LABEL_END();

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

            ostringstream str;
            str << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << CSStartAddress;
            CSInfo[SiteID][MacroID] = (INT) jtag.getReadValue(str.str())[SiteID];
            CSInfo[SiteID][MacroID] = ((((INT) CSInfo[SiteID][MacroID]& 0xff00) >> 8) | (((INT) CSInfo[SiteID][MacroID]& 0x00ff) << 8))*800.0 / 1024; //big edian
            hout(DETAIL) << "CS HVCC: Address: 0x" << hex << CSStartAddress << "   " << "Value: " << hex << CSInfo[SiteID][MacroID] << endl;
//            cout << "CS HVCC: Address: 0x" << hex << CSStartAddress << "   " << "Value: " << hex << CSInfo[SiteID][MacroID] << endl;
        }

        FOREACH_ACTIVESITE_END

    d2s::d2s_LABEL_BEGIN("READ_DS_HVCC_ErrorMessage_", Global_D2S_Mode);
    for (uint midx = 0; midx < MacroLane_Sel.size(); midx++) {
        uint MacroID = MacroLane_Sel[midx].MacroID;
        const vector<uint>& vLane = MacroLane_Sel[midx].vLane;
        ostringstream str;
        str << "_M" << MacroID;
        selectMacro(MacroID);

        for (uint lidx = 0; lidx < vLane.size(); lidx++) {
            uint LaneID = vLane[lidx];
            ostringstream str;
            uint addr = DSStartAddress + LaneID*DSIncreaseStep;
            str << "ReadDSHVCC_ERROR_Message_M" << MacroID << "_L" << LaneID << "_Address_0x" << hex << addr;

            jtag.read(addr >> 1, str.str());
        }
    }
    d2s::d2s_LABEL_END();

    for (uint midx = 0; midx < MacroLane_Sel.size(); midx++) {
        uint MacroID = MacroLane_Sel[midx].MacroID;
        const vector<uint>& vLane = MacroLane_Sel[midx].vLane;
        ostringstream str;
        str << "_M" << MacroID;

        for (uint lidx = 0; lidx < vLane.size(); lidx++) {
            uint LaneID = vLane[lidx];
            ostringstream str;
            uint addr = DSStartAddress + LaneID*DSIncreaseStep;
            str << "ReadDSHVCC_ERROR_Message_M" << MacroID << "_L" << LaneID << "_Address_0x" << hex << addr;

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
                FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

                DsInfo[SiteID][MacroID][LaneID] = jtag.getReadValue(str.str())[SiteID];
                DsInfo[SiteID][MacroID][LaneID] = ((((INT) DsInfo[SiteID][MacroID][LaneID]& 0xff00) >> 8) | (((INT) DsInfo[SiteID][MacroID][LaneID]& 0x00ff) << 8))*800.0 / 1024; //big edian
                hout(DETAIL) << "DS HVCC: Macro: " << MacroID << " LaneID: " << LaneID << " Value: " << DsInfo[SiteID][MacroID][LaneID] << endl;
                //cout<< "DS HVCC: Macro: " << MacroID << " LaneID: " << LaneID << " Value: " << DsInfo[SiteID][MacroID][LaneID] << endl;
                FOREACH_ACTIVESITE_END
        }
    }
}

void FW_ABIST_READ_ErrorMessage(const MACRO_LANE_SEL& MacroLane_Sel, INT DSStartAddress, INT DSIncreaseStep, INT CSStartAddress, MACRO_DOUBLE& CSInfo, LANE_DOUBLE& DsInfo) {
    d2s_JTAG& jtag = d2s_JTAG::Instance();


    //CS Information

    d2s::d2s_LABEL_BEGIN("H30V101_HVCC_And_ErrorMessage_read_", Global_D2S_Mode);
    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        selectMacro(MacroID);

        ostringstream str;
        str << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << CSStartAddress;
        jtag.read(CSStartAddress >> 1, str.str());

    }

    d2s::d2s_LABEL_END();

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

            ostringstream str;
            str << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << CSStartAddress;
            hout(DETAIL) << "Address: 0x" << hex << CSStartAddress << "   " << "Data: 0x" << hex << (INT) jtag.getReadValue(str.str())[SiteID] << endl;
            CSInfo[SiteID][MacroID] = (INT) jtag.getReadValue(str.str())[SiteID];
            CSInfo[SiteID][MacroID] = (((INT) CSInfo[SiteID][MacroID]& 0xff00) >> 8) | (((INT) CSInfo[SiteID][MacroID]& 0x00ff) << 8); //big edian
        }

        FOREACH_ACTIVESITE_END

    d2s::d2s_LABEL_BEGIN("READ_DS_HVCC_ErrorMessage_", Global_D2S_Mode);
    for (uint midx = 0; midx < MacroLane_Sel.size(); midx++) {
        uint MacroID = MacroLane_Sel[midx].MacroID;
        const vector<uint>& vLane = MacroLane_Sel[midx].vLane;
        ostringstream str;
        str << "_M" << MacroID;

        selectMacro(MacroID);

        for (uint lidx = 0; lidx < vLane.size(); lidx += 2) {
            uint LaneID = vLane[lidx];
            ostringstream str;
            uint addr = DSStartAddress + LaneID*DSIncreaseStep;
            str << "ReadDSHVCC_ERROR_Message_M" << MacroID << "_L" << LaneID << "_Address_0x" << hex << addr;

            jtag.read(addr >> 1, str.str());
        }
    }

    d2s::d2s_LABEL_END();
    for (uint midx = 0; midx < MacroLane_Sel.size(); midx++) {
        uint MacroID = MacroLane_Sel[midx].MacroID;
        const vector<uint>& vLane = MacroLane_Sel[midx].vLane;
        ostringstream str;
        str << "_M" << MacroID;

        for (uint lidx = 0; lidx < vLane.size(); lidx += 2) {
            uint LaneID = vLane[lidx];
            ostringstream str;
            uint addr = DSStartAddress + LaneID*DSIncreaseStep;
            str << "ReadDSHVCC_ERROR_Message_M" << MacroID << "_L" << LaneID << "_Address_0x" << hex << addr;

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
                FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

                DsInfo[SiteID][MacroID][LaneID] = jtag.getReadValue(str.str())[SiteID];
                DsInfo[SiteID][MacroID][LaneID] = ((INT) DsInfo[SiteID][MacroID][LaneID]& 0xff00) >> 8; //big edian
                DsInfo[SiteID][MacroID][LaneID + 1] = (INT) DsInfo[SiteID][MacroID][LaneID]& 0x00ff; //big edian
                hout(DETAIL) << "Error Message: Macro: " << MacroID << " LaneID: " << LaneID << " Value: " << DsInfo[SiteID][MacroID][LaneID] << endl;
                FOREACH_ACTIVESITE_END
        }
    }
}

void FW_ABIST_READ_LANEDOUBLE(const MACRO_LANE_SEL& MacroLane_Sel, INT DSStartAddress, INT DSIncreaseStep, LANE_DOUBLE& DsInfo) {

    //	D2S_FRAMEWORK;
    //GET_TEST_INFO;
    d2s_JTAG& jtag = d2s_JTAG::Instance();


    //			sprintf(label,"READ_DS_LANEDOUBLE_%f_%f_",Vcoef,Temp);
    //			fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("READ_DS_LANEDOUBLE_", Global_D2S_Mode);
    for (uint midx = 0; midx < MacroLane_Sel.size(); midx++) {
        uint MacroID = MacroLane_Sel[midx].MacroID;
        const vector<uint>& vLane = MacroLane_Sel[midx].vLane;
        ostringstream str;
        str << "_M" << MacroID;

        selectMacro(MacroID);

        for (uint lidx = 0; lidx < vLane.size(); lidx++) {
            uint LaneID = vLane[lidx];
            ostringstream str;
            uint addr = DSStartAddress + LaneID*DSIncreaseStep;
            str << "ReadDS_LANE_DOUBLE_M" << MacroID << "_L" << LaneID << "_Address_0x" << hex << addr;

            jtag.read(addr >> 1, str.str());

        }
    }

    //			fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    for (uint midx = 0; midx < MacroLane_Sel.size(); midx++) {
        uint MacroID = MacroLane_Sel[midx].MacroID;
        const vector<uint>& vLane = MacroLane_Sel[midx].vLane;
        ostringstream str;
        str << "_M" << MacroID;

        for (uint lidx = 0; lidx < vLane.size(); lidx++) {
            uint LaneID = vLane[lidx];
            ostringstream str;
            uint addr = DSStartAddress + LaneID*DSIncreaseStep;
            str << "ReadDS_LANE_DOUBLE_M" << MacroID << "_L" << LaneID << "_Address_0x" << hex << addr;

            //					FOR_EACH_SITE_BEGIN();
            //						uint SiteID=CURRENT_SITE_NUMBER()-1;

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
                FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

                DsInfo[SiteID][MacroID][LaneID] = jtag.getReadValue(str.str())[SiteID];
                DsInfo[SiteID][MacroID][LaneID] = (((INT) DsInfo[SiteID][MacroID][LaneID]& 0xff00) >> 8) | (((INT) DsInfo[SiteID][MacroID][LaneID]& 0x00ff) << 8); //big edian
                hout(DETAIL) << "Read_DS_Lane_Double: Macro: " << MacroID << " LaneID: " << LaneID << " Value: " << DsInfo[SiteID][MacroID][LaneID] << endl;
                //					FOR_EACH_SITE_END();
                FOREACH_ACTIVESITE_END
        }
    }
}

void FW_ABIST_READ_LANEDOUBLE(const MACRO_LANE_SEL& MacroLane_Sel, INT DSStartAddress, INT DSIncreaseStep, LANE_DOUBLE& DsInfo, LANE_DOUBLE& Half_HVCC_Public_Volt) {

    //	D2S_FRAMEWORK;
    //GET_TEST_INFO;
    d2s_JTAG& jtag = d2s_JTAG::Instance();



    //			sprintf(label,"READ_DS_LANEDOUBLE_%f_%f_",Vcoef,Temp);
    //			fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("READ_DS_LANEDOUBLE_", Global_D2S_Mode);
    for (uint midx = 0; midx < MacroLane_Sel.size(); midx++) {
        uint MacroID = MacroLane_Sel[midx].MacroID;
        const vector<uint>& vLane = MacroLane_Sel[midx].vLane;
        ostringstream str;
        str << "_M" << MacroID;

        selectMacro(MacroID);

        for (uint lidx = 0; lidx < vLane.size(); lidx++) {
            uint LaneID = vLane[lidx];
            ostringstream str;
            uint addr = DSStartAddress + LaneID*DSIncreaseStep;
            str << "ReadDS_LANE_DOUBLE_M" << MacroID << "_L" << LaneID << "_Address_0x" << hex << addr;

            jtag.read(addr >> 1, str.str());
        }
    }
    //			fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    for (uint midx = 0; midx < MacroLane_Sel.size(); midx++) {
        uint MacroID = MacroLane_Sel[midx].MacroID;
        const vector<uint>& vLane = MacroLane_Sel[midx].vLane;
        ostringstream str;
        str << "_M" << MacroID;

        for (uint lidx = 0; lidx < vLane.size(); lidx++) {
            uint LaneID = vLane[lidx];
            ostringstream str;
            uint addr = DSStartAddress + LaneID*DSIncreaseStep;
            str << "ReadDS_LANE_DOUBLE_M" << MacroID << "_L" << LaneID << "_Address_0x" << hex << addr;

            //					FOR_EACH_SITE_BEGIN();
            //						uint SiteID=CURRENT_SITE_NUMBER()-1;
//
//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
                FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

                DsInfo[SiteID][MacroID][LaneID] = jtag.getReadValue(str.str())[SiteID];
                DsInfo[SiteID][MacroID][LaneID] = (((INT) DsInfo[SiteID][MacroID][LaneID]& 0xff00) >> 8) | (((INT) DsInfo[SiteID][MacroID][LaneID]& 0x00ff) << 8); //big edian
                DsInfo[SiteID][MacroID][LaneID] = DsInfo[SiteID][MacroID][LaneID] * Half_HVCC_Public_Volt[SiteID][MacroID][LaneID]*2 / 1024;
                hout(DETAIL) << "Read_DS_Lane_Double: Macro: " << MacroID << " LaneID: " << LaneID << " Voltage Value: " << DsInfo[SiteID][MacroID][LaneID] << endl;
                //					FOR_EACH_SITE_END();
                FOREACH_ACTIVESITE_END
        }
    }
}

void FWAbistHeader(const MACRO_LANE_SEL& MacroLane_Sel, uint macroIndex, STRING CalFW, STRING TestFW, STRING TestItem, ostringstream& TestDatalog) {
    double temperature = 999;
    //	GET_USER_DOUBLE("ReadBack_Temp",&temperature);
    TestDatalog.clear();
    TestDatalog << "\n\n" << "TestItems:	" << TestItem << endl;
    TestDatalog << "GuiVision:	v0.7.3.0" << endl;
    TestDatalog << "CalFwVision:	" << CalFW << endl;
    TestDatalog << "TestFwVision:	" << TestFW << endl;
    TestDatalog << "ChipType:	H30LRV101" << endl;
    TestDatalog << "TestMacro:	" << MacroLane_Sel[macroIndex].MacroID << endl;
    TestDatalog << "CurrTempName:	NT" << endl;
    TestDatalog << "CurrTemp:	" << temperature << endl; //TODO
    TestDatalog << "CurrVoltName:	" << "LV" << endl; //TODO
    TestDatalog << "ChipID:	" << "getfromefuse();" << endl; //TODO
    TestDatalog << "Pll0Rate(Gbps):	" << 30 << endl;
    TestDatalog << "Pll1Rate(Gbps):	" << 30 << endl;
    TestDatalog << "DataRate:	Full," << endl;
}

void SRAM_READ(const UINT& MacroID, INT StartAddress, INT StopAddress, ostringstream& SramDataLog, bool Dump_Spec) {

    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    //GET_TEST_INFO;

    //	sprintf(label,"H30V101_SRAM_read_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("H30V101_SRAM_read_", Global_D2S_Mode);
    selectMacro(MacroID);

    for (int i = StartAddress; i <= StopAddress; i += 0x2) {
        ostringstream str;
        str << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << i;
        jtag.read(i >> 1, str.str());
    }
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //	INT SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        int iCounter = 0;
        for (int i = StartAddress; i <= StopAddress; i += 0x2) {
            iCounter++;
            ostringstream str;
            str << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << i;
            hout(DETAIL) << "Site " << SiteID << " MacroID " << MacroID << "Address: 0x" << hex << i << "   " << "Data: 0x" << hex << (INT) jtag.getReadValue(str.str())[SiteID] << endl;
            SramDataLog << hex << (INT) jtag.getReadValue(str.str())[SiteID] << ",";
        }


        if (Dump_Spec == true) {
            //Here print same format as evb for debug
            iCounter = 0;

            hout(GENERAL) << "Debug Infor to compare EVB setting with testprogram setting" << endl << endl;
            ostringstream Spec_Setting;
            Spec_Setting.clear();
            Spec_Setting << "Spec Setting SRAM Readback Macro:" << dec << MacroID << endl;

            for (int i = StartAddress; i <= StopAddress; i += 0x2) {
                iCounter++;
                ostringstream str;
                str << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << i;
                uint tmp = (INT) jtag.getReadValue(str.str())[SiteID];

                //		CSInfo[SiteID][MacroID] = ((((INT)CSInfo[SiteID][MacroID]& 0xff00)>>8) | (((INT)CSInfo[SiteID][MacroID]& 0x00ff)<<8))*800.0/1024 ; //big edian
                uint tmp_part1 = (tmp & 0xff00) >> 8;
                uint tmp_part2 = (tmp & 0x00ff);

                if (iCounter % 2) {
                    hout(GENERAL) << hex << i << " " << tmp_part2 << " " << tmp_part1;
                    Spec_Setting << hex << i << " " << tmp_part2 << " " << tmp_part1;
                } else {
                    hout(GENERAL) << " " << tmp_part2 << " " << tmp_part1 << endl;
                    Spec_Setting << " " << tmp_part2 << " " << tmp_part1 << endl;
                }
            }

            //		PUT_DATALOG(Spec_Setting.str());
        }

        FOREACH_ACTIVESITE_END
}

void SEGMENT_EXPECT_MACRO(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, UINT value, EXPECT_RESULT& ExpectResult) {
    /***************this sub func must in ON_FIRST_INVOCATION_BEGIN block**************/
    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();
    //GET_TEST_INFO;

//    unsigned int sites[MAX_SITES];
    //	INT	ConfiguredSitesNum = GET_CONFIGURED_SITES(sites);
    int ConfiguredSitesNum = TheSoft.Sites().Existing().GetExistedSiteCount();// api->Get_active_sites(sites);
    ARRAY_I tmp;
    tmp.resize(ConfiguredSitesNum);
    //	tmp.init(0);
    ExpectResult.allpass = true;
    ExpectResult.allfail = true;
    ExpectResult.eachsite = tmp;

    UINT lb = reg_info_ex.reg_info.low_bit;
    UINT hb = reg_info_ex.reg_info.hi_bit;
    UINT csr = reg_info_ex.reg_info.csr;

    UINT mask = 0xFFFF;
    mask &= HI_BIT_MASK[hb];
    mask &= ~LO_BIT_MASK[lb];

    value <<= lb;
    value &= mask;

    //	mask = ~mask;

    HILINK_Regs_Base& reg = reg_info_ex.parent;
    //	sprintf(label,"Segment_Expect_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("Segment_Expect_", Global_D2S_Mode);
    //	jtag.enablePassFailCheckForNextExecution();
    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

        selectMacro(MacroID);

        reg.MacroID(MacroID).SliceID(0).Broadcast(0);
        reg.ExpectValue(csr, value, mask);
    }
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	jtag.hasPassed(label,ExpectResult.allpass,ExpectResult.allfail,ExpectResult.eachsite);

//    FOREACH_ACTIVE_SITE(api) {
    map<uint32_t, bool> map_pass_fail_result = TheInst.Digital().PatEng().GetPassFail();

    uint64_t GetExecutedCyclesCount = TheInst.Digital().PatEng().GetExecutedCyclesCount();

//    cout<<"SEGMENT_EXPECT_MACRO   run pattern burst GetExecutedCyclesCount = "<<dec<<GetExecutedCyclesCount<<endl;

    FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

//    	bool size_pass = map_pass_fail_result[SiteID];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
        bool size_pass = map_pass_fail_result[SiteID];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
		if(PrintDebugEn) cout<<"map_pass_fail_result["<<SiteID<<"] = "<<map_pass_fail_result[SiteID]<<endl;
        ExpectResult.allpass = (ExpectResult.allpass && size_pass);
        ExpectResult.allfail = (ExpectResult.allfail && !size_pass);
        ExpectResult.eachsite[SiteID] = size_pass;
    FOREACH_ACTIVESITE_END

//    FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//
//    	bool size_pass = map_pass_fail_result[SiteID];//map_pass_fail_result[SiteID];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
//    	cout<<"=============== SEGMENT_EXPECT_MACRO check done, when run expect pattern  , be forced the expect result = pass when learning mode!!!!!!!!!!"<<endl;
//    	if(Global_D2S_Mode == LearningMode) size_pass = true;
//
//        ExpectResult.allpass = (ExpectResult.allpass && size_pass);
//        ExpectResult.allfail = (ExpectResult.allfail && !size_pass);
//        ExpectResult.eachsite[SiteID] = size_pass;
//    FOREACH_ACTIVESITE_END

}

void FW_ABIST_CSArrayD_ReadBack(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE) {

    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    //GET_TEST_INFO;

    MACRO_ARRAY_D Spec_Upper_Value, Spec_Lower_Value;

    Spec_Upper_Value.init(9999, 0);
    Spec_Lower_Value.init(9999, 0);

    //	sprintf(label,"H30V101_SRAM_CSread_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("H30V101_SRAM_CSread_", Global_D2S_Mode);
    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        selectMacro(MacroID);


        for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_CS_FWABIST_REG_count(); RegIndex++) {
            ostringstream strHigh, strLow;
            uint SpecHigh_Address = FWABIST_REG_BASE.get_CS_FWABIST_REG(RegIndex).SpecHigh_Address;
            if (SpecHigh_Address > 0) {
                uint SpecLow_Address = FWABIST_REG_BASE.get_CS_FWABIST_REG(RegIndex).SpecLow_Address;
                strHigh << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << SpecHigh_Address << "_CSRegIndex_0x" << hex << RegIndex;
                strLow << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << SpecLow_Address << "_CSRegIndex_0x" << hex << RegIndex;
                jtag.read(SpecHigh_Address >> 1, strHigh.str());
                jtag.read(SpecLow_Address >> 1, strLow.str());
            }
        }


    }
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //	INT SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

            for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_CS_FWABIST_REG_count(); RegIndex++) {
                ostringstream strHigh, strLow;
                uint SpecHigh_Address = FWABIST_REG_BASE.get_CS_FWABIST_REG(RegIndex).SpecHigh_Address;
                if (SpecHigh_Address > 0) {
                    uint SpecLow_Address = FWABIST_REG_BASE.get_CS_FWABIST_REG(RegIndex).SpecLow_Address;

                    strHigh << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << SpecHigh_Address << "_CSRegIndex_0x" << hex << RegIndex;
                    strLow << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << SpecLow_Address << "_CSRegIndex_0x" << hex << RegIndex;


                    Spec_Upper_Value[SiteID][MacroID][RegIndex] = (INT) jtag.getReadValue(strHigh.str())[SiteID];
                    Spec_Upper_Value[SiteID][MacroID][RegIndex] = (((INT) Spec_Upper_Value[SiteID][MacroID][RegIndex]& 0xff00) >> 8) | (((INT) Spec_Upper_Value[SiteID][MacroID][RegIndex]& 0x00ff) << 8); //big edian

                    hout(DETAIL) << "READBack: SpecHigh_Address: 0x" << hex << SpecHigh_Address << "   " << "Data: " << dec << Spec_Upper_Value[SiteID][MacroID][RegIndex] << endl;
                    Spec_Lower_Value[SiteID][MacroID][RegIndex] = (INT) jtag.getReadValue(strLow.str())[SiteID];
                    Spec_Lower_Value[SiteID][MacroID][RegIndex] = (((INT) Spec_Lower_Value[SiteID][MacroID][RegIndex]& 0xff00) >> 8) | (((INT) Spec_Lower_Value[SiteID][MacroID][RegIndex]& 0x00ff) << 8); //big edian
                    hout(DETAIL) << "READBack: SpecLow_Address: 0x" << hex << SpecLow_Address << "   " << "Data: " << dec << Spec_Lower_Value[SiteID][MacroID][RegIndex] << endl;
                }
            }
        }

        FOREACH_ACTIVESITE_END

    //	sprintf(label,"H30V101_SRAM_CSread_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    //        d2s::d2s_LABEL_BEGIN("H30V101_SRAM_CSread_", Global_D2S_Mode);
    //                for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
    //                {
    //                        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
    //                        selectMacro(MacroID);
    //
    //
    //                        for(uint RegIndex =0; RegIndex <FWABIST_REG_BASE.get_CS_FWABIST_Calculate_REG_count(); RegIndex ++)
    //                        {
    //                                ostringstream strHigh,strLow;
    //                                uint SpecHigh_Address = FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).SpecHigh_Address;
    //                                if(SpecHigh_Address>0)
    //                                {
    //                                        uint SpecLow_Address = FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).SpecLow_Address;
    //                                        strHigh <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<SpecHigh_Address<<"_CSRegIndex_0x"<<hex<<RegIndex;
    //                                        strLow <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<SpecLow_Address<<"_CSRegIndex_0x"<<hex<<RegIndex;
    //                                        jtag.read(SpecHigh_Address>>1,strHigh.str());
    //                                        jtag.read(SpecLow_Address>>1,strLow.str());
    //                                }
    //                        }
    //
    //
    //                }
    //        //	fr.d2s_LABEL_END();
    //        d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //	INT SiteID = CURRENT_SITE_NUMBER() - 1;
    //            FOREACH_ACTIVE_SITE(api) {
    //                unsigned int SiteID = api->Get_active_site();
    //	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
    //	{
    //		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
    //
    //		for(uint RegIndex =0; RegIndex <FWABIST_REG_BASE.get_CS_FWABIST_Calculate_REG_count(); RegIndex ++)
    //		{
    //			ostringstream strHigh, strLow;
    //			uint SpecHigh_Address = FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).SpecHigh_Address;
    //			if(SpecHigh_Address>0){
    //				uint SpecLow_Address = FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).SpecLow_Address;
    //
    //			strHigh <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<SpecHigh_Address<<"_CSRegIndex_0x"<<hex<<RegIndex;
    //			strLow <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<SpecLow_Address<<"_CSRegIndex_0x"<<hex<<RegIndex;
    //
    //
    //			Spec_Upper_Value[SiteID][MacroID][RegIndex] =  (INT)jtag.getReadValue(strHigh.str());
    //			Spec_Upper_Value[SiteID][MacroID][RegIndex] = (((INT)Spec_Upper_Value[SiteID][MacroID][RegIndex]& 0xff00)>>8) |(((INT)Spec_Upper_Value[SiteID][MacroID][RegIndex]& 0x00ff)<<8); //big edian
    //
    //				hout(DETAIL)<<"READBack: SpecHigh_Address: 0x"<<hex<<SpecHigh_Address<<"   "<<"Data: "<<dec<<Spec_Upper_Value[SiteID][MacroID][RegIndex]<<endl;
    //				Spec_Lower_Value[SiteID][MacroID][RegIndex] =  (INT)jtag.getReadValue(strLow.str());
    //				Spec_Lower_Value[SiteID][MacroID][RegIndex] = (((INT)Spec_Lower_Value[SiteID][MacroID][RegIndex]& 0xff00)>>8) |(((INT)Spec_Lower_Value[SiteID][MacroID][RegIndex]& 0x00ff)<<8); //big edian
    //				hout(DETAIL)<<"READBack: SpecLow_Address: 0x"<<hex<<SpecLow_Address<<"   "<<"Data: "<<dec<<Spec_Lower_Value[SiteID][MacroID][RegIndex]<<endl;
    //			}
    //		}
    //	}
    //
    ////	FOR_EACH_SITE_END();
    //            }
}

void FW_ABIST_DSArrayD_ReadBack(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE) {

    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    //GET_TEST_INFO;

    MACRO_ARRAY_D Spec_Upper_Value, Spec_Lower_Value;
    Spec_Upper_Value.init(9999, 0);
    Spec_Lower_Value.init(9999, 0);

    //	sprintf(label,"H30V101_SRAM_DSread_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("H30V101_SRAM_DSread_", Global_D2S_Mode);
    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        selectMacro(MacroID);

        //All lane have same spec address and same spec data, so here NO need to do lane loop
        for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_DS_FWABIST_REG_count(); RegIndex++) {
            ostringstream strHigh, strLow;
            uint SpecHigh_Address = FWABIST_REG_BASE.get_DS_FWABIST_REG(RegIndex).SpecHigh_Address;
            uint SpecLow_Address = FWABIST_REG_BASE.get_DS_FWABIST_REG(RegIndex).SpecLow_Address;
            strHigh << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << SpecHigh_Address << "_CSRegIndex_0x" << hex << RegIndex;
            strLow << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << SpecLow_Address << "_CSRegIndex_0x" << hex << RegIndex;
            jtag.read(SpecHigh_Address >> 1, strHigh.str());
            jtag.read(SpecLow_Address >> 1, strLow.str());
        }


    }
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //	INT SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

            for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_DS_FWABIST_REG_count(); RegIndex++) {
                ostringstream strHigh, strLow;
                uint SpecHigh_Address = FWABIST_REG_BASE.get_DS_FWABIST_REG(RegIndex).SpecHigh_Address;
                uint SpecLow_Address = FWABIST_REG_BASE.get_DS_FWABIST_REG(RegIndex).SpecLow_Address;

                strHigh << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << SpecHigh_Address << "_CSRegIndex_0x" << hex << RegIndex;
                strLow << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << SpecLow_Address << "_CSRegIndex_0x" << hex << RegIndex;


                Spec_Upper_Value[SiteID][MacroID][RegIndex] = (INT) jtag.getReadValue(strHigh.str())[SiteID];
                Spec_Upper_Value[SiteID][MacroID][RegIndex] = (((INT) Spec_Upper_Value[SiteID][MacroID][RegIndex]& 0xff00) >> 8) | (((INT) Spec_Upper_Value[SiteID][MacroID][RegIndex]& 0x00ff) << 8); //big edian

                hout(DETAIL) << "READBack:All Lane's  SpecHigh_Address: 0x" << hex << SpecHigh_Address << "   " << "Data: " << dec << Spec_Upper_Value[SiteID][MacroID][RegIndex] << endl;
                Spec_Lower_Value[SiteID][MacroID][RegIndex] = (INT) jtag.getReadValue(strLow.str())[SiteID];
                Spec_Lower_Value[SiteID][MacroID][RegIndex] = (((INT) Spec_Lower_Value[SiteID][MacroID][RegIndex]& 0xff00) >> 8) | (((INT) Spec_Lower_Value[SiteID][MacroID][RegIndex]& 0x00ff) << 8); //big edian
                hout(DETAIL) << "READBack:All Lane's   SpecLow_Address: 0x" << hex << SpecLow_Address << "   " << "Data: " << dec << Spec_Lower_Value[SiteID][MacroID][RegIndex] << endl;
            }
        }
        FOREACH_ACTIVESITE_END
    //	sprintf(label,"H30V101_SRAM_DSread_Calculate_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    //        d2s::d2s_LABEL_BEGIN("H30V101_SRAM_DSread_Calculate_", Global_D2S_Mode);
    //	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
    //	{
    //		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
    //		selectMacro(MacroID);
    //
    //		//All lane have same spec address and same spec data, so here NO need to do lane loop
    //		for(uint RegIndex =0; RegIndex <FWABIST_REG_BASE.get_DS_FWABIST_Calculate_REG_count(); RegIndex ++)
    //		{
    //			ostringstream strHigh,strLow;
    //			uint SpecHigh_Address = FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).SpecHigh_Address;
    //			uint SpecLow_Address = FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).SpecLow_Address;
    //			strHigh <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<SpecHigh_Address<<"_CSRegIndex_0x"<<hex<<RegIndex;
    //			strLow <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<SpecLow_Address<<"_CSRegIndex_0x"<<hex<<RegIndex;
    //			jtag.read(SpecHigh_Address>>1,strHigh.str());
    //			jtag.read(SpecLow_Address>>1,strLow.str());
    //		}
    //
    //
    //	}
    ////	fr.d2s_LABEL_END();
    //        d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //	INT SiteID = CURRENT_SITE_NUMBER() - 1;
    //            FOREACH_ACTIVE_SITE(api) {
    //                unsigned int SiteID = api->Get_active_site();
    //	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
    //	{
    //		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
    //
    //		for(uint RegIndex =0; RegIndex <FWABIST_REG_BASE.get_DS_FWABIST_Calculate_REG_count(); RegIndex ++)
    //		{
    //			ostringstream strHigh, strLow;
    //			uint SpecHigh_Address = FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).SpecHigh_Address;
    //			uint SpecLow_Address = FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).SpecLow_Address;
    //
    //			strHigh <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<SpecHigh_Address<<"_CSRegIndex_0x"<<hex<<RegIndex;
    //			strLow <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<SpecLow_Address<<"_CSRegIndex_0x"<<hex<<RegIndex;
    //
    //
    //			Spec_Upper_Value[SiteID][MacroID][RegIndex] =  (INT)jtag.getReadValue(strHigh.str());
    //			Spec_Upper_Value[SiteID][MacroID][RegIndex] = (((INT)Spec_Upper_Value[SiteID][MacroID][RegIndex]& 0xff00)>>8) |(((INT)Spec_Upper_Value[SiteID][MacroID][RegIndex]& 0x00ff)<<8); //big edian
    //
    //			hout(DETAIL)<<"Calculate READBack:All Lane's  SpecHigh_Address: 0x"<<hex<<SpecHigh_Address<<"   "<<"Data: "<<dec<<Spec_Upper_Value[SiteID][MacroID][RegIndex]<<endl;
    //			Spec_Lower_Value[SiteID][MacroID][RegIndex] =  (INT)jtag.getReadValue(strLow.str());
    //			Spec_Lower_Value[SiteID][MacroID][RegIndex] = (((INT)Spec_Lower_Value[SiteID][MacroID][RegIndex]& 0xff00)>>8) |(((INT)Spec_Lower_Value[SiteID][MacroID][RegIndex]& 0x00ff)<<8); //big edian
    //			hout(DETAIL)<<"Calcualte READBack:All Lane's   SpecLow_Address: 0x"<<hex<<SpecLow_Address<<"   "<<"Data: "<<dec<<Spec_Lower_Value[SiteID][MacroID][RegIndex]<<endl;
    //		}
    //	}
    //
    //            }
    //	FOR_EACH_SITE_END();
}

void FW_ABIST_SingleSpec_ReadBack(const MACRO_LANE_SEL& MacroLane_Sel, UINT SpecHigh_Address, UINT SpecLow_Address) {

    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    //GET_TEST_INFO;

    MACRO_INT Spec_Upper_Value, Spec_Lower_Value;

    //	sprintf(label,"H30V101_SRAM_DSread_%f_%f_",Vcoef,Temp);
    //	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("H30V101_SRAM_DSread_", Global_D2S_Mode);
    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        selectMacro(MacroID);

        //All lane have same spec address and same spec data, so here NO need to do lane loop

        ostringstream strHigh, strLow;

        strHigh << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << SpecHigh_Address;
        strLow << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << SpecLow_Address;
        jtag.read(SpecHigh_Address >> 1, strHigh.str());
        jtag.read(SpecLow_Address >> 1, strLow.str());


    }
    //	fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //	INT SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            ostringstream strHigh, strLow;

            strHigh << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << SpecHigh_Address;
            strLow << "Macro" << "_" << MacroID << "_" << "SRAM" << "_Address_0x" << hex << SpecLow_Address;


            Spec_Upper_Value[SiteID][MacroID] = (INT) jtag.getReadValue(strHigh.str())[SiteID];
            Spec_Upper_Value[SiteID][MacroID] = ((Spec_Upper_Value[SiteID][MacroID]& 0xff00) >> 8) | ((Spec_Upper_Value[SiteID][MacroID]& 0x00ff) << 8); //big edian

            hout(DETAIL) << "Single Spec ReadBack:All Lane's  SpecHigh_Address: 0x" << hex << SpecHigh_Address << "   " << "Data: " << dec << Spec_Upper_Value[SiteID][MacroID] << endl;
            Spec_Lower_Value[SiteID][MacroID] = (INT) jtag.getReadValue(strLow.str())[SiteID];
            Spec_Lower_Value[SiteID][MacroID] = ((Spec_Lower_Value[SiteID][MacroID]& 0xff00) >> 8) | ((Spec_Lower_Value[SiteID][MacroID]& 0x00ff) << 8); //big edian
            hout(DETAIL) << "Single Spec ReadBack:All Lane's   SpecLow_Address: 0x" << hex << SpecLow_Address << "   " << "Data: " << dec << Spec_Lower_Value[SiteID][MacroID] << endl;

        }

        FOREACH_ACTIVESITE_END
}

void HiLink_PerLane_Judge_DcGain(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname, LANE_DOUBLE& TempResult, LANE_DOUBLE& TemperatureCode, JUDGE_PIN Judge_Pin) {


	int tempTestNumber =0;
    FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
	tempTestNumber =0;

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

            STRING_VECTOR JudgePins;
            JudgePins.clear();
            double UpperLimit_tmp = 0;
            double LowerLimit_tmp = 0;
            ARRAY_D ValueForJudge_tmp;
            ValueForJudge_tmp.resize(1);
            ;

            for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
                UINT LaneID = vLane[laneIndex];
                JudgePins.clear();
                switch (Judge_Pin) {
                    case 0: JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_P);
                        break;
                    case 1: JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_N);
                        break;
                    case 2: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);
                        break;
                    case 3: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_N);
                        break;
                    default: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);
                        break;
                }

//                UpperLimit_tmp = 23.5 - (1.2 * TemperatureCode[SiteID][MacroID][LaneID]);
                UpperLimit_tmp = 23.5 - (1.2 * TemperatureCode[SiteID][MacroID][LaneID]);  // initial 23.5  , change to 25.5 by tony 20210918
                LowerLimit_tmp = -4.5 - (1.2 * TemperatureCode[SiteID][MacroID][LaneID]);
                ValueForJudge_tmp[0] = TempResult[SiteID][MacroID][LaneID];

                //TEST(JudgePins[laneIndex], testname, LIMIT(TM::GE, LowerLimit_tmp,TM::LE, UpperLimit_tmp), ValueForJudge_tmp);
                //			TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, testname,  LIMIT(TM::GE, LowerLimit_tmp,TM::LE, UpperLimit_tmp), ValueForJudge_tmp);

                stringstream ss; //int 2 string
                ss << macroIndex;
                string strmacroIndex;
                ss >> strmacroIndex;

                stringstream ss1; //int 2 string
                ss1 << laneIndex;
                string strlaneIndex;
                ss1 >> strlaneIndex;
                string Macro_Lane_Name = "M" + strmacroIndex + "_L" + strlaneIndex;

                judgeAndLog_ParametricTest(SiteID, testname, Macro_Lane_Name, LowerLimit_tmp, ValueForJudge_tmp[0], UpperLimit_tmp, m_TestNumber + tempTestNumber);
                tempTestNumber++;
            }

            /***************sub func end****************/
        }
        FOREACH_ACTIVESITE_END
		m_TestNumber = m_TestNumber + tempTestNumber;



//
//		vector<vector<SiteDouble>> UpperLimit;// [marco][lane][site]
//        UpperLimit.resize(MacroLane_Sel.size());
//		vector<vector<SiteDouble>> LowerLimit;// [marco][lane][site]
//		LowerLimit.resize(MacroLane_Sel.size());
//		vector<vector<SiteDouble>> ValueForJudge;// [marco][lane][site]
//		ValueForJudge.resize(MacroLane_Sel.size());
//		int siteCount = TheSoft.Sites().Active().GetActiveSiteCount();
//
//
//	    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
//	        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//	        const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//	        UpperLimit[MacroID].resize(vLane.size());
//	        LowerLimit[MacroID].resize(vLane.size());
//	        ValueForJudge[MacroID].resize(vLane.size());
//
//	        for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
//	            UINT LaneID = vLane[laneIndex];
//	            UpperLimit[MacroID][LaneID].resize(siteCount);
//	            LowerLimit[MacroID][LaneID].resize(siteCount);
//	            ValueForJudge[MacroID][LaneID].resize(siteCount);
//
//	            stringstream ss; //int 2 string
//	            ss << macroIndex;
//	            string strmacroIndex;
//	            ss >> strmacroIndex;
//
//	            stringstream ss1; //int 2 string
//	            ss1 << laneIndex;
//	            string strlaneIndex;
//	            ss1 >> strlaneIndex;
//	            string Macro_Lane_Name = "M" + strmacroIndex + "_L" + strlaneIndex;
//
//	            //tony 20210915 still need recheck the "TestLimit" api for each site have diff low/high limit/failbin/ ...
//	            double llimit =LowerLimit[MacroID][LaneID][0];
//	            double hlimit =UpperLimit[MacroID][LaneID][0];
//	            unsigned int failhbin =6;
//	            unsigned int failsbin =6269;
//	            string unit = "";
//	            string limitname = "DcGain_Calculate_"+Macro_Lane_Name;
//	            static unsigned int testnum = 62690049;
//
//	        	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//	            unsigned int testnumtemp = testnum;
//					UpperLimit[MacroID][LaneID][SiteID] = 23.5 - (1.2 * TemperatureCode[SiteID][MacroID][LaneID]);
//					LowerLimit[MacroID][LaneID][SiteID] = -4.5 - (1.2 * TemperatureCode[SiteID][MacroID][LaneID]);
//					ValueForJudge[MacroID][LaneID][SiteID] = TempResult[SiteID][MacroID][LaneID];
//
//					TheSoft.Flow().TestLimit("",SiteID,ValueForJudge[MacroID][LaneID][SiteID],LowerLimit[MacroID][LaneID][SiteID],UpperLimit[MacroID][LaneID][SiteID],
//							failhbin,failsbin,unit,limitname,testnumtemp,E_Fail,E_LEFTCLOSE_RIGHTCLOSE);//One pin,one result(double),select one site
//
//				FOREACH_ACTIVESITE_END
//				testnum +=1;
//
////	            TheSoft.Flow().TestLimit(ValueForJudge[MacroID][LaneID],llimit,hlimit,failhbin,failsbin,
////	        					       unit,limitname,testnum++,E_Fail,E_LEFTCLOSE_RIGHTCLOSE);//judge and write PTR or MPR: single Pin -PTR, PinGroup - MPR
//	        }
//	    }

}

void HiLink_PerMacro_Judge_Regulator(const MACRO_LANE_SEL& MacroLane_Sel, MACRO_DOUBLE& NodeCode, MACRO_DOUBLE& NodeVolt, string sJudgeNameInTable_NodeCode, string sJudgeNameInTable_NodeVolt, JUDGE_PIN Judge_Pin) {

    STRING_VECTOR JudgePins;
    JudgePins.clear();

    //         STRING sTestsuiteName;
    ////	 GET_TESTSUITE_NAME(sTestsuiteName);
    //
    //	 TMLimits::LimitInfo strLimitInfo_NodeCode;
    //	 strLimitInfo_NodeCode = tmLimits.getLimit(sTestsuiteName,sJudgeNameInTable_NodeCode);
    //
    //	 TMLimits::LimitInfo strLimitInfo_NodeVolt;
    //	 strLimitInfo_NodeVolt = tmLimits.getLimit(sTestsuiteName,sJudgeNameInTable_NodeVolt);
    //
    string OPL_NodeCode, OPH_NodeCode, sTestName_NodeCode, sLimitUnit_NodeCode;
    double LowLimit_NodeCode, HiLimit_NodeCode;
    //	 LowLimit_NodeCode =strLimitInfo_NodeCode.Lsl;
    //	 HiLimit_NodeCode =strLimitInfo_NodeCode.Usl;
    //	 OPL_NodeCode =strLimitInfo_NodeCode.LslTyp;
    //	 OPH_NodeCode =strLimitInfo_NodeCode.UslTyp;
    //	 sTestName_NodeCode =strLimitInfo_NodeCode.TestName;
    //	 sLimitUnit_NodeCode =strLimitInfo_NodeCode.Units;

    string OPL_NodeVolt, OPH_NodeVolt, sTestName_NodeVolt, sLimitUnit_NodeVolt;
    double LowLimit_NodeVolt, HiLimit_NodeVolt;
    //	 LowLimit_NodeVolt =strLimitInfo_NodeVolt.Lsl;
    //	 HiLimit_NodeVolt =strLimitInfo_NodeVolt.Usl;
    //	 OPL_NodeVolt =strLimitInfo_NodeVolt.LslTyp;
    //	 OPH_NodeVolt =strLimitInfo_NodeVolt.UslTyp;
    //	 sTestName_NodeVolt =strLimitInfo_NodeVolt.TestName;
    //	 sLimitUnit_NodeVolt =strLimitInfo_NodeVolt.Units;

    if (sJudgeNameInTable_NodeCode == "PLL0VREGPLLSEL") {
        LowLimit_NodeCode = 0;
        HiLimit_NodeCode = 30;
        OPL_NodeCode = "GE";
        OPH_NodeCode = "LE";
    } else if (sJudgeNameInTable_NodeCode == "PLL0VREGDLFSEL") {
        LowLimit_NodeCode = 0;
        HiLimit_NodeCode = 30;
        OPL_NodeCode = "GE";
        OPH_NodeCode = "LE";
    } else if (sJudgeNameInTable_NodeCode == "PLL0VREGVCODIVSEL") {
        LowLimit_NodeCode = 0;
        HiLimit_NodeCode = 30;
        OPL_NodeCode = "GE";
        OPH_NodeCode = "LE";
    } else if (sJudgeNameInTable_NodeCode == "PLL1VREGPLLSEL") {
        LowLimit_NodeCode = 0;
        HiLimit_NodeCode = 30;
        OPL_NodeCode = "GE";
        OPH_NodeCode = "LE";
    } else if (sJudgeNameInTable_NodeCode == "PLL1VREGDLFSEL") {
        LowLimit_NodeCode = 0;
        HiLimit_NodeCode = 30;
        OPL_NodeCode = "GE";
        OPH_NodeCode = "LE";
    } else if (sJudgeNameInTable_NodeCode == "PLL1VREGVCODIVSEL") {
        LowLimit_NodeCode = 0;
        HiLimit_NodeCode = 30;
        OPL_NodeCode = "GE";
        OPH_NodeCode = "LE";
    }

    if (sJudgeNameInTable_NodeVolt == "PLL0VREGPLL_VREGHALF") {
        LowLimit_NodeVolt = 475;
        HiLimit_NodeVolt = 900;
        OPL_NodeVolt = "GE";
        OPH_NodeVolt = "LE";
    } else if (sJudgeNameInTable_NodeVolt == "PLL0VREGDLF_VREGHALF") {
        LowLimit_NodeVolt = 475;
        HiLimit_NodeVolt = 900;
        OPL_NodeVolt = "GE";
        OPH_NodeVolt = "LE";
    } else if (sJudgeNameInTable_NodeVolt == "PLL0VREGVCODIV_VREGHALF") {
        LowLimit_NodeVolt = 475;
        HiLimit_NodeVolt = 900;
        OPL_NodeVolt = "GE";
        OPH_NodeVolt = "LE";
    } else if (sJudgeNameInTable_NodeVolt == "PLL1VREGPLL_VREGHALF") {
        LowLimit_NodeVolt = 475;
        HiLimit_NodeVolt = 900;
        OPL_NodeVolt = "GE";
        OPH_NodeVolt = "LE";
    } else if (sJudgeNameInTable_NodeVolt == "PLL1VREGDLF_VREGHALF") {
        LowLimit_NodeVolt = 475;
        HiLimit_NodeVolt = 900;
        OPL_NodeVolt = "GE";
        OPH_NodeVolt = "LE";
    } else if (sJudgeNameInTable_NodeVolt == "PLL1VREGVCODIV_VREGHALF") {
        LowLimit_NodeVolt = 475;
        HiLimit_NodeVolt = 900;
        OPL_NodeVolt = "GE";
        OPH_NodeVolt = "LE";
    }
    //
    //	FOR_EACH_SITE_BEGIN();
    //	INT SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
	int tempTestNumber =0;
    FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
	tempTestNumber =0;

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
            UINT LaneID = vLane[0]; //the first lane,which need to test in program(higgs lr just test lane3,can't find the lane0 pin name in pin file)
            JudgePins.clear();
            switch (Judge_Pin) {
                case 0: JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_P);
                    break;
                case 1: JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_N);
                    break;
                case 2: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);
                    break;
                case 3: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_N);
                    break;
                default: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);
                    break;
            }

            string sLocalLimitCompareResult_NodeCode = LocalLimitCompare(OPL_NodeCode, LowLimit_NodeCode, OPH_NodeCode, HiLimit_NodeCode, NodeCode[SiteID][MacroID]);
            string sLocalLimitCompareResult_NodeVolt = LocalLimitCompare(OPL_NodeVolt, LowLimit_NodeVolt, OPH_NodeVolt, HiLimit_NodeVolt, NodeVolt[SiteID][MacroID]);

            ARRAY_D NodeCodeValueForJudge;
            ARRAY_D NodeVoltValueForJudge;
            NodeCodeValueForJudge.resize(1);
            NodeVoltValueForJudge.resize(1);
            NodeCodeValueForJudge[0] = NodeCode[SiteID][MacroID];
            NodeVoltValueForJudge[0] = NodeVolt[SiteID][MacroID];

            stringstream ss; //int 2 string
            ss << macroIndex;
            string strmacroIndex;
            ss >> strmacroIndex;
            string Macro_Lane_Name = "M" + strmacroIndex;

            if ((sLocalLimitCompareResult_NodeCode == "PASSED")&&(sLocalLimitCompareResult_NodeVolt == "FAILED")) {
                double LowerLimit_tmp = 0;
                double UpperLimit_tmp = 1200;
                //			TEST(JudgePins[macroIndex], sJudgeNameInTable_NodeVolt, LIMIT(TM::GE, LowerLimit_tmp,TM::LE, UpperLimit_tmp), NodeVolt[SiteID][MacroID],true);
                //			TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins[macroIndex], sJudgeNameInTable_NodeCode, tmLimits, NodeCode[SiteID][MacroID]);
                //                            TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, sJudgeNameInTable_NodeVolt, LIMIT(TM::GE, LowerLimit_tmp,TM::LE, UpperLimit_tmp), NodeVoltValueForJudge); //modify for the datalog format,if use pin as parameter,dalog show: testname@pin
                //                            TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, sJudgeNameInTable_NodeCode, tmLimits, NodeCodeValueForJudge);

                judgeAndLog_ParametricTest(SiteID, sJudgeNameInTable_NodeVolt, Macro_Lane_Name, LowerLimit_tmp, NodeVoltValueForJudge[0], UpperLimit_tmp,m_TestNumber + tempTestNumber); tempTestNumber++;
                judgeAndLog_ParametricTest(SiteID, sJudgeNameInTable_NodeCode, Macro_Lane_Name, LowLimit_NodeCode, NodeCodeValueForJudge[0], HiLimit_NodeCode,m_TestNumber + tempTestNumber); tempTestNumber++;



            } else if ((sLocalLimitCompareResult_NodeCode == "FAILED")&&(sLocalLimitCompareResult_NodeVolt == "PASSED")) {
                double LowerLimit_tmp = 0;
                double UpperLimit_tmp = 31;
                //	TEST(JudgePins[macroIndex], sJudgeNameInTable_NodeCode, LIMIT(TM::GE, LowerLimit_tmp,TM::LE, UpperLimit_tmp), NodeCode[SiteID][MacroID],true);
                //	TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins[macroIndex], sJudgeNameInTable_NodeVolt, tmLimits, NodeVolt[SiteID][MacroID]);
                //                                         TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, sJudgeNameInTable_NodeCode, LIMIT(TM::GE, LowerLimit_tmp,TM::LE, UpperLimit_tmp), NodeCodeValueForJudge);				
                //                                         TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, sJudgeNameInTable_NodeVolt, tmLimits, NodeVoltValueForJudge);

                judgeAndLog_ParametricTest(SiteID, sJudgeNameInTable_NodeVolt, Macro_Lane_Name, LowLimit_NodeVolt, NodeVoltValueForJudge[0], HiLimit_NodeVolt,m_TestNumber + tempTestNumber); tempTestNumber++;
                judgeAndLog_ParametricTest(SiteID, sJudgeNameInTable_NodeCode, Macro_Lane_Name, LowerLimit_tmp, NodeCodeValueForJudge[0], UpperLimit_tmp,m_TestNumber + tempTestNumber); tempTestNumber++;
            } else {
                //	TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins[macroIndex], sJudgeNameInTable_NodeCode, tmLimits, NodeCode[SiteID][MacroID]);
                //	TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins[macroIndex], sJudgeNameInTable_NodeVolt, tmLimits, NodeVolt[SiteID][MacroID]);
                //                                         TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, sJudgeNameInTable_NodeCode, tmLimits, NodeCodeValueForJudge);
                //                                         TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, sJudgeNameInTable_NodeVolt, tmLimits, NodeVoltValueForJudge);

                judgeAndLog_ParametricTest(SiteID, sJudgeNameInTable_NodeVolt, Macro_Lane_Name, LowLimit_NodeVolt, NodeVoltValueForJudge[0], HiLimit_NodeVolt,m_TestNumber + tempTestNumber); tempTestNumber++;
                judgeAndLog_ParametricTest(SiteID, sJudgeNameInTable_NodeCode, Macro_Lane_Name, LowLimit_NodeCode, NodeCodeValueForJudge[0], HiLimit_NodeCode,m_TestNumber + tempTestNumber); tempTestNumber++;
            }
        }
        FOREACH_ACTIVESITE_END
		m_TestNumber = m_TestNumber + tempTestNumber;
}

void HiLink_PerMacroCSCalArrayD_Judge(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE, MACRO_ARRAY_D& TempResult, JUDGE_PIN Judge_Pin) {

		int tempTestNumber =0;
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		tempTestNumber =0;
        for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_CS_FWABIST_Calculate_REG_count(); RegIndex++) {
            STRING_VECTOR JudgePins;
            JudgePins.clear();
            ARRAY_D ValueForJudge;
            ValueForJudge.resize(MacroLane_Sel.size());
            STRING testname = FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).NODE_NAME;
            //		LimitTable_Manager::InitAndUpdateLimit(testname);

            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
                switch (Judge_Pin) {
                    case 0: JudgePins.push_back(LANE_INFO[MacroID][0].RX_P);
                        break;
                    case 1: JudgePins.push_back(LANE_INFO[MacroID][0].RX_N);
                        break;
                    case 2: JudgePins.push_back(LANE_INFO[MacroID][0].TX_P);
                        break;
                    case 3: JudgePins.push_back(LANE_INFO[MacroID][0].TX_N);
                        break;
                    default: JudgePins.push_back(LANE_INFO[MacroID][0].TX_P);
                        break;
                }

                ValueForJudge[macroIndex] = TempResult[SiteID][MacroID][RegIndex];

                stringstream ss; //int 2 string
                ss << macroIndex;
                string strmacroIndex;
                ss >> strmacroIndex;
                string Macro_Lane_Name = "M" + strmacroIndex;
                judgeAndLog_ParametricTest(SiteID, testname, Macro_Lane_Name, FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).SpecLow_Value, ValueForJudge[macroIndex], FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).SpecHigh_Value,m_TestNumber + tempTestNumber);
                tempTestNumber++;

            }

            //		TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, testname, tmLimits, ValueForJudge);
        }
        FOREACH_ACTIVESITE_END
		m_TestNumber = m_TestNumber + tempTestNumber;
    /***************sub func end****************/



//	vector<vector<SiteDouble>> ValueForJudge;// [Reg][marco][site]
//	ValueForJudge.resize(FWABIST_REG_BASE.get_CS_FWABIST_Calculate_REG_count());
//
//	int siteCount = TheSoft.Sites().Active().GetActiveSiteCount();
//
//	for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_CS_FWABIST_Calculate_REG_count(); RegIndex++) {
//
//        ValueForJudge[RegIndex].resize(MacroLane_Sel.size());
//        string testname = FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).NODE_NAME;
//
//	    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
//	        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//	        ValueForJudge[RegIndex][MacroID].resize(siteCount);
//
//        	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//				ValueForJudge[RegIndex][MacroID][SiteID] = TempResult[SiteID][MacroID][RegIndex];
//			FOREACH_ACTIVESITE_END
//
//            stringstream ss; //int 2 string
//            ss << macroIndex;
//            string strmacroIndex;
//            ss >> strmacroIndex;
//
//            string Macro_Lane_Name = "M" + strmacroIndex;
//
//            TheSoft.Flow().TestLimit(ValueForJudge[RegIndex][MacroID],E_LEFTCLOSE_RIGHTCLOSE);
//
//		 }
//
//	}


}

void HiLink_PerLaneCalArrayD_Judge(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE, LANE_ARRAY_D& TempResult, JUDGE_PIN Judge_Pin) {

		int tempTestNumber=0;
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		tempTestNumber=0;

        for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_DS_FWABIST_Calculate_REG_count(); RegIndex++) {
            STRING testname = FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).NODE_NAME;
            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
                const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

                STRING_VECTOR JudgePins;
                JudgePins.clear();
                ARRAY_D ValueForJudge;
                ValueForJudge.resize(vLane.size());

                for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
                    UINT LaneID = vLane[laneIndex];
                    switch (Judge_Pin) {
                        case 0: JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_P);
                            break;
                        case 1: JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_N);
                            break;
                        case 2: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);
                            break;
                        case 3: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_N);
                            break;
                        default: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);
                            break;
                    }
                    ValueForJudge[laneIndex] = TempResult[SiteID][MacroID][LaneID][RegIndex];

                    stringstream ss; //int 2 string
                    ss << macroIndex;
                    string strmacroIndex;
                    ss >> strmacroIndex;

                    stringstream ss1; //int 2 string
                    ss1 << laneIndex;
                    string strlaneIndex;
                    ss1 >> strlaneIndex;
                    string Macro_Lane_Name = "M" + strmacroIndex + "_L" + strlaneIndex;

                    judgeAndLog_ParametricTest(SiteID, testname, Macro_Lane_Name, FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).SpecLow_Value, ValueForJudge[laneIndex], FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).SpecHigh_Value, m_TestNumber + tempTestNumber);
                    tempTestNumber++;
                }

                //			TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, testname, tmLimits, ValueForJudge);
            }
        }
        FOREACH_ACTIVESITE_END
		m_TestNumber = m_TestNumber + tempTestNumber;

//
//	vector<vector<vector<SiteDouble>>> ValueForJudge;// [Reg][marco][Lane][site]
//	ValueForJudge.resize(FWABIST_REG_BASE.get_DS_FWABIST_Calculate_REG_count());
//
//	int siteCount = TheSoft.Sites().Active().GetActiveSiteCount();
//
//	for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_DS_FWABIST_Calculate_REG_count(); RegIndex++) {
//
//        ValueForJudge[RegIndex].resize(MacroLane_Sel.size());
//        string testname = FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).NODE_NAME;
//
//	    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
//	        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//	        const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//
//	        ValueForJudge[RegIndex][MacroID].resize(vLane.size());
//
//	        for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
//				UINT LaneID = vLane[laneIndex];
//				ValueForJudge[RegIndex][MacroID][LaneID].resize(siteCount);
//
//        	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//				ValueForJudge[RegIndex][MacroID][LaneID][SiteID] = TempResult[SiteID][MacroID][LaneID][RegIndex];
//			FOREACH_ACTIVESITE_END
//
//			stringstream ss; //int 2 string
//			ss << macroIndex;
//			string strmacroIndex;
//			ss >> strmacroIndex;
//
//			stringstream ss1; //int 2 string
//			ss1 << laneIndex;
//			string strlaneIndex;
//			ss1 >> strlaneIndex;
//			string Macro_Lane_Name = "M" + strmacroIndex + "_L" + strlaneIndex;
//
//
//            TheSoft.Flow().TestLimit(ValueForJudge[RegIndex][MacroID][LaneID],E_LEFTCLOSE_RIGHTCLOSE);
//	        }
//		 }
//	}

}

void HiLink_PerMacroCSArrayD_Judge(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE, MACRO_ARRAY_D& TempResult, JUDGE_PIN Judge_Pin) {

		int tempTestNumber =0;
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		tempTestNumber =0;
        for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_CS_FWABIST_REG_count(); RegIndex++) {
            STRING_VECTOR JudgePins;
            JudgePins.clear();
            ARRAY_D ValueForJudge;
            ValueForJudge.resize(MacroLane_Sel.size());
            STRING testname = FWABIST_REG_BASE.get_CS_FWABIST_REG(RegIndex).name;
            //		LimitTable_Manager::InitAndUpdateLimit(testname);

            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
                switch (Judge_Pin) {
                    case 0: JudgePins.push_back(LANE_INFO[MacroID][0].RX_P);
                        break;
                    case 1: JudgePins.push_back(LANE_INFO[MacroID][0].RX_N);
                        break;
                    case 2: JudgePins.push_back(LANE_INFO[MacroID][0].TX_P);
                        break;
                    case 3: JudgePins.push_back(LANE_INFO[MacroID][0].TX_N);
                        break;
                    default: JudgePins.push_back(LANE_INFO[MacroID][0].TX_P);
                        break;
                }

                ValueForJudge[macroIndex] = TempResult[SiteID][MacroID][RegIndex];

                stringstream ss; //int 2 string
                ss << macroIndex;
                string strmacroIndex;
                ss >> strmacroIndex;
                string Macro_Lane_Name = "M" + strmacroIndex;
                judgeAndLog_ParametricTest(SiteID, testname, Macro_Lane_Name, FWABIST_REG_BASE.get_CS_FWABIST_REG(RegIndex).SpecLow_Value, ValueForJudge[macroIndex], FWABIST_REG_BASE.get_CS_FWABIST_REG(RegIndex).SpecHigh_Value,m_TestNumber + tempTestNumber);
                tempTestNumber++;
            }


            //		TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, testname, tmLimits, ValueForJudge);
        }
        FOREACH_ACTIVESITE_END
		m_TestNumber = m_TestNumber + tempTestNumber;

//	vector<vector<SiteDouble>> ValueForJudge;// [Reg][marco][site]
//	ValueForJudge.resize(FWABIST_REG_BASE.get_CS_FWABIST_REG_count());
//
//	int siteCount = TheSoft.Sites().Active().GetActiveSiteCount();
//
//	for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_CS_FWABIST_REG_count(); RegIndex++) {
//
//        ValueForJudge[RegIndex].resize(MacroLane_Sel.size());
//        string testname = FWABIST_REG_BASE.get_CS_FWABIST_REG(RegIndex).name;
//
//	    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
//	        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//	        ValueForJudge[RegIndex][MacroID].resize(siteCount);
//
//        	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//				ValueForJudge[RegIndex][MacroID][SiteID] = TempResult[SiteID][MacroID][RegIndex];
//			FOREACH_ACTIVESITE_END
//
//            stringstream ss; //int 2 string
//            ss << macroIndex;
//            string strmacroIndex;
//            ss >> strmacroIndex;
//
//            string Macro_Lane_Name = "M" + strmacroIndex;
//
//
//            //tony 20210915 still need recheck the "TestLimit" api for each site have diff low/high limit/failbin/ ...
////            double llimit =LowerLimit[MacroID][LaneID][0];
////            double hlimit =UpperLimit[MacroID][LaneID][0];
////            unsigned int failhbin =6;
////            unsigned int failsbin =6267;
////            string unit = "";
////            string limitname = testname+"_"+Macro_Lane_Name;
////            static unsigned int testnum = 62670025;
////            TheSoft.Flow().TestLimit(ValueForJudge[MacroID][LaneID],llimit,hlimit,failhbin,failsbin,
////        					       unit,limitname,testnum++,E_Fail,E_LEFTCLOSE_RIGHTCLOSE);//judge and write PTR or MPR: single Pin -PTR, PinGroup - MPR
//            TheSoft.Flow().TestLimit(ValueForJudge[RegIndex][MacroID],E_LEFTCLOSE_RIGHTCLOSE);
//
//		 }
//
//	}


    /***************sub func end****************/
}

void HiLink_PerLaneArrayD_Judge(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE, LANE_ARRAY_D& TempResult, JUDGE_PIN Judge_Pin) {

		int tempTestNumber=0;
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		tempTestNumber=0;

        for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_DS_FWABIST_REG_count(); RegIndex++) {
            STRING testname = FWABIST_REG_BASE.get_DS_FWABIST_REG(RegIndex).name;
            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
                const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

                STRING_VECTOR JudgePins;
                JudgePins.clear();
                ARRAY_D ValueForJudge;
                ValueForJudge.resize(vLane.size());

                for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
                    UINT LaneID = vLane[laneIndex];
                    switch (Judge_Pin) {
                        case 0: JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_P);
                            break;
                        case 1: JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_N);
                            break;
                        case 2: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);
                            break;
                        case 3: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_N);
                            break;
                        default: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);
                            break;
                    }
                    ValueForJudge[laneIndex] = TempResult[SiteID][MacroID][LaneID][RegIndex];

                    stringstream ss; //int 2 string
                    ss << macroIndex;
                    string strmacroIndex;
                    ss >> strmacroIndex;

                    stringstream ss1; //int 2 string
                    ss1 << laneIndex;
                    string strlaneIndex;
                    ss1 >> strlaneIndex;
                    string Macro_Lane_Name = "M" + strmacroIndex + "_L" + strlaneIndex;

                    judgeAndLog_ParametricTest(SiteID, testname, Macro_Lane_Name, FWABIST_REG_BASE.get_DS_FWABIST_REG(RegIndex).SpecLow_Value, ValueForJudge[laneIndex], FWABIST_REG_BASE.get_DS_FWABIST_REG(RegIndex).SpecHigh_Value,m_TestNumber + tempTestNumber);
                    tempTestNumber++;

                }

                //			TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, testname, tmLimits, ValueForJudge);
            }
        }
        FOREACH_ACTIVESITE_END
		m_TestNumber = m_TestNumber + tempTestNumber;

//		vector<vector<vector<SiteDouble>>> ValueForJudge;// [Reg][marco][Lane][site]
//		ValueForJudge.resize(FWABIST_REG_BASE.get_DS_FWABIST_REG_count());
//
//		int siteCount = TheSoft.Sites().Active().GetActiveSiteCount();
//
//		for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_DS_FWABIST_REG_count(); RegIndex++) {
//
//	        ValueForJudge[RegIndex].resize(MacroLane_Sel.size());
//	        string testname = FWABIST_REG_BASE.get_DS_FWABIST_REG(RegIndex).name;
//
//		    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
//		        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//		        const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//
//		        ValueForJudge[RegIndex][MacroID].resize(vLane.size());
//
//		        for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
//					UINT LaneID = vLane[laneIndex];
//					ValueForJudge[RegIndex][MacroID][LaneID].resize(siteCount);
//
//	        	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//					ValueForJudge[RegIndex][MacroID][LaneID][SiteID] = TempResult[SiteID][MacroID][LaneID][RegIndex];
//				FOREACH_ACTIVESITE_END
//
//				stringstream ss; //int 2 string
//				ss << macroIndex;
//				string strmacroIndex;
//				ss >> strmacroIndex;
//
//				stringstream ss1; //int 2 string
//				ss1 << laneIndex;
//				string strlaneIndex;
//				ss1 >> strlaneIndex;
//				string Macro_Lane_Name = "M" + strmacroIndex + "_L" + strlaneIndex;
//
//
//	            TheSoft.Flow().TestLimit(ValueForJudge[RegIndex][MacroID][LaneID],E_LEFTCLOSE_RIGHTCLOSE);
//		        }
//			 }
//		}



}

string LocalLimitCompare(string &OPL, double &LowLimit, string &OPH, double &HiLimit, double &Result) {

    string sComparePF = "NOTDNE";
    bool bLoLimitPF = false;
    bool bHiLimitPF = false;

    //Transfer enum to operating

    // for low limit:
    if (OPL == "GE") {

        if (Result >= LowLimit) {

            bLoLimitPF = true;

        }
    }

    if (OPL == "GT") {

        if (Result > LowLimit) {

            bLoLimitPF = true;

        }
    }

    if (OPL == "LE") {

        if (Result <= LowLimit) {

            bLoLimitPF = true;

        }
    }


    if (OPL == "LT") {

        if (Result < LowLimit) {

            bLoLimitPF = true;

        }
    }


    if (OPL == "NA") {

        if (Result >= LowLimit) {

            bLoLimitPF = true;
        }
    }

    // for high limit:

    if (OPH == "GE") {

        if (Result >= HiLimit) {

            bHiLimitPF = true;

        }
    }

    if (OPH == "GT") {

        if (Result > HiLimit) {

            bHiLimitPF = true;

        }
    }

    if (OPH == "LE") {

        if (Result <= HiLimit) {

            bHiLimitPF = true;

        }
    }


    if (OPH == "LT") {

        if (Result < HiLimit) {

            bHiLimitPF = true;

        }
    }


    if (OPH == "NA") {

        if (Result >= HiLimit) {

            bHiLimitPF = true;
        }
    }


    if (bLoLimitPF == true and bHiLimitPF == true) {

        sComparePF = "PASSED";
    } else {

        sComparePF = "FAILED";

    }

    return sComparePF;
}

void FWAbist_Calculate_Table_Processing(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE, MACRO_ARRAY_D& SS_Calculate_Output,
        MACRO_ARRAY_D& CS_Calculate_Output, LANE_ARRAY_D& DS_Calculate_Output, MACRO_ARRAY_MAP& SS_REG_Node_Value, MACRO_ARRAY_MAP& CS_REG_Node_Value,
        LANE_ARRAY_MAP& DS_REG_Node_Value) {

    uint SSCalCount = FWABIST_REG_BASE.get_SS_FWABIST_Calculate_REG_count();
    uint CSCalCount = FWABIST_REG_BASE.get_CS_FWABIST_Calculate_REG_count();
    uint DSCalCount = FWABIST_REG_BASE.get_DS_FWABIST_Calculate_REG_count();

    LANE_ARRAY_D PerLane_Input1, PerLane_Input2, PerLane_Input3, PerLane_Input4;
    PerLane_Input1.init(DSCalCount, 0);
    PerLane_Input2.init(DSCalCount, 0);
    PerLane_Input3.init(DSCalCount, 0);
    PerLane_Input4.init(DSCalCount, 0);

    MACRO_ARRAY_D PerMacro_Input1, PerMacro_Input2, PerMacro_Input3, PerMacro_Input4;
    PerMacro_Input1.init(CSCalCount, 0);
    PerMacro_Input2.init(CSCalCount, 0);
    PerMacro_Input3.init(CSCalCount, 0);
    PerMacro_Input4.init(CSCalCount, 0);

    MACRO_ARRAY_D PerMacroSS_Input1, PerMacroSS_Input2, PerMacroSS_Input3, PerMacroSS_Input4;
    PerMacroSS_Input1.init(SSCalCount, 0);
    PerMacroSS_Input2.init(SSCalCount, 0);
    PerMacroSS_Input3.init(SSCalCount, 0);
    PerMacroSS_Input4.init(SSCalCount, 0);

    SS_Calculate_Output.init(SSCalCount, 0);
    CS_Calculate_Output.init(CSCalCount, 0);
    DS_Calculate_Output.init(DSCalCount, 0);

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (uint macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

            for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_SS_FWABIST_Calculate_REG_count(); RegIndex++) {
                map<string, double> ::iterator SSNode_Input1 = SS_REG_Node_Value[SiteID][MacroID].find(FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).Input1);
                if (SSNode_Input1 != SS_REG_Node_Value[SiteID][MacroID].end()) {
                    PerMacroSS_Input1[SiteID][MacroID][RegIndex] = SSNode_Input1-> second;
                    hout(GENERAL) << "Macro: " << MacroID << " SS Key: " << FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).Input1 << "Value: " << PerMacroSS_Input1[SiteID][MacroID][RegIndex] << endl;
                } else
                    hout(GENERAL) << "Macro: " << MacroID << " SS Key: " << FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).Input1 << " Not found" << endl;

                map<string, double> ::iterator SSNode_Input2 = SS_REG_Node_Value[SiteID][MacroID].find(FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).Input2);
                if (SSNode_Input2 != SS_REG_Node_Value[SiteID][MacroID].end()) {
                    PerMacroSS_Input2[SiteID][MacroID][RegIndex] = SSNode_Input2-> second;
                    hout(GENERAL) << "SS Key: " << FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).Input2 << "Value: " << PerMacroSS_Input2[SiteID][MacroID][RegIndex] << endl;
                } else
                    hout(GENERAL) << "SS Key: " << FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).Input2 << " Not found" << endl;

                if (FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).Formula == "Average") {
                    SS_Calculate_Output[SiteID][MacroID][RegIndex] = (PerMacroSS_Input1[SiteID][MacroID][RegIndex] + PerMacroSS_Input2[SiteID][MacroID][RegIndex]) / 2;
                } else if (FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).Formula == "Sub") {
                    SS_Calculate_Output[SiteID][MacroID][RegIndex] = PerMacroSS_Input1[SiteID][MacroID][RegIndex] - PerMacroSS_Input2[SiteID][MacroID][RegIndex];
                } else
                    hout(GENERAL) << " Fomula is NOT Supported!! " << endl;

            }

            for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_CS_FWABIST_Calculate_REG_count(); RegIndex++) {
                map<string, double> ::iterator CSNode_Input1 = CS_REG_Node_Value[SiteID][MacroID].find(FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).Input1);
                if (CSNode_Input1 != CS_REG_Node_Value[SiteID][MacroID].end()) {
                    PerMacro_Input1[SiteID][MacroID][RegIndex] = CSNode_Input1-> second;
                    hout(GENERAL) << "Macro: " << MacroID << " CS Key: " << FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).Input1 << "Value: " << PerMacro_Input1[SiteID][MacroID][RegIndex] << endl;
                } else
                    hout(GENERAL) << "Macro: " << MacroID << " CS Key: " << FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).Input1 << " Not found" << endl;

                map<string, double> ::iterator CSNode_Input2 = CS_REG_Node_Value[SiteID][MacroID].find(FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).Input2);
                if (CSNode_Input2 != CS_REG_Node_Value[SiteID][MacroID].end()) {
                    PerMacro_Input2[SiteID][MacroID][RegIndex] = CSNode_Input2-> second;
                    hout(GENERAL) << "CS Key: " << FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).Input2 << "Value: " << PerMacro_Input2[SiteID][MacroID][RegIndex] << endl;
                } else
                    hout(GENERAL) << "CS Key: " << FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).Input2 << " Not found" << endl;

                if (FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).Formula == "Average") {
                    CS_Calculate_Output[SiteID][MacroID][RegIndex] = (PerMacro_Input1[SiteID][MacroID][RegIndex] + PerMacro_Input2[SiteID][MacroID][RegIndex]) / 2;
                } else if (FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).Formula == "Sub") {
                    CS_Calculate_Output[SiteID][MacroID][RegIndex] = PerMacro_Input1[SiteID][MacroID][RegIndex] - PerMacro_Input2[SiteID][MacroID][RegIndex];
                } else if (FWABIST_REG_BASE.get_CS_Calculate_REG(RegIndex).Formula == "Get") {//add for VCOTuningRange test,just copy the fix node value to calc node,for judge simple
                    CS_Calculate_Output[SiteID][MacroID][RegIndex] = PerMacro_Input1[SiteID][MacroID][RegIndex]*10;
                }//add for VCOTuningRange test,just copy the fix node value to calc node,for judge simple
                else
                    hout(GENERAL) << " Fomula is NOT Supported!! " << endl;

            }

            const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
            for (UINT LaneIndex = 0; LaneIndex < vLane.size(); LaneIndex++) {
                UINT LaneID = vLane[LaneIndex];

                for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_DS_FWABIST_Calculate_REG_count(); RegIndex++) {
                    map<string, double> ::iterator DSNode_Input1 = DS_REG_Node_Value[SiteID][MacroID][LaneID].find(FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Input1);
                    if (DSNode_Input1 != DS_REG_Node_Value[SiteID][MacroID][LaneID].end()) {
                        PerLane_Input1[SiteID][MacroID][LaneID][RegIndex] = DSNode_Input1-> second;
                        hout(GENERAL) << "Input Node1 : " << "Macro: " << MacroID << " Lane: " << LaneID << "DS Key: " << FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Input1 << "Value: " << PerLane_Input1[SiteID][MacroID][LaneID][RegIndex] << endl;
                    } else
                        hout(GENERAL) << "Input Node1 : " << "Macro: " << MacroID << " Lane: " << LaneID << "DS Key: " << FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Input1 << " Not found" << endl;

                    map<string, double> ::iterator DSNode_Input2 = DS_REG_Node_Value[SiteID][MacroID][LaneID].find(FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Input2);
                    if (DSNode_Input2 != DS_REG_Node_Value[SiteID][MacroID][LaneID].end()) {
                        PerLane_Input2[SiteID][MacroID][LaneID][RegIndex] = DSNode_Input2-> second;
                        hout(GENERAL) << "Input Node2 : " << "Macro: " << MacroID << " Lane: " << LaneID << "DS Key: " << FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Input2 << "Value: " << PerLane_Input2[SiteID][MacroID][LaneID][RegIndex] << endl;
                    } else
                        hout(GENERAL) << "Input Node2 : " << "Macro: " << MacroID << " Lane: " << LaneID << "DS Key: " << FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Input2 << " Not found" << endl;


                    map<string, double> ::iterator DSNode_Input3 = DS_REG_Node_Value[SiteID][MacroID][LaneID].find(FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Input3);
                    if (DSNode_Input3 != DS_REG_Node_Value[SiteID][MacroID][LaneID].end()) {
                        PerLane_Input3[SiteID][MacroID][LaneID][RegIndex] = DSNode_Input3-> second;
                        hout(GENERAL) << "Input Node3 : " << "Macro: " << MacroID << " Lane: " << LaneID << "DS Key: " << FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Input3 << "Value: " << PerLane_Input3[SiteID][MacroID][LaneID][RegIndex] << endl;
                    } else
                        hout(GENERAL) << "Input Node3 : " << "Macro: " << MacroID << " Lane: " << LaneID << "DS Key: " << FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Input3 << " Not found" << endl;

                    map<string, double> ::iterator DSNode_Input4 = DS_REG_Node_Value[SiteID][MacroID][LaneID].find(FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Input4);
                    if (DSNode_Input4 != DS_REG_Node_Value[SiteID][MacroID][LaneID].end()) {
                        PerLane_Input4[SiteID][MacroID][LaneID][RegIndex] = DSNode_Input4-> second;
                        hout(GENERAL) << "Input Node4 : " << "Macro: " << MacroID << " Lane: " << LaneID << "DS Key: " << FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Input4 << "Value: " << PerLane_Input4[SiteID][MacroID][LaneID][RegIndex] << endl;
                    } else
                        hout(GENERAL) << "Input Node4 : " << "Macro: " << MacroID << " Lane: " << LaneID << "DS Key: " << FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Input4 << " Not found" << endl;




                    if (FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Formula == "Average") {
                        DS_Calculate_Output[SiteID][MacroID][LaneID][RegIndex] = (PerLane_Input1[SiteID][MacroID][LaneID][RegIndex] + PerLane_Input2[SiteID][MacroID][LaneID][RegIndex]) / 2;
                        hout(GENERAL) << "Macro: " << MacroID << " Lane: " << LaneID << "DS Key: " << FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).NODE_NAME << " Value: " << DS_Calculate_Output[SiteID][MacroID][LaneID][RegIndex] << endl;
                    }
                    else if (FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Formula == "Sub") {
                        DS_Calculate_Output[SiteID][MacroID][LaneID][RegIndex] = PerLane_Input1[SiteID][MacroID][LaneID][RegIndex] - PerLane_Input2[SiteID][MacroID][LaneID][RegIndex];
                        hout(GENERAL) << "Macro: " << MacroID << " Lane: " << LaneID << "DS Key: " << FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).NODE_NAME << " Value: " << DS_Calculate_Output[SiteID][MacroID][LaneID][RegIndex] << endl;
                    } else if (FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).Formula == "AbsDiff") {
                        DS_Calculate_Output[SiteID][MacroID][LaneID][RegIndex] = abs((PerLane_Input1[SiteID][MacroID][LaneID][RegIndex] - PerLane_Input2[SiteID][MacroID][LaneID][RegIndex]) - (PerLane_Input3[SiteID][MacroID][LaneID][RegIndex] - PerLane_Input4[SiteID][MacroID][LaneID][RegIndex]));
                        hout(GENERAL) << "Macro: " << MacroID << " Lane: " << LaneID << "DS Key: " << FWABIST_REG_BASE.get_DS_Calculate_REG(RegIndex).NODE_NAME << " Value: " << DS_Calculate_Output[SiteID][MacroID][LaneID][RegIndex] << endl;
                    } else {
                        //                                            cerr <<" Fomula is NOT Supported!! "<<endl;
                        printf(" Fomula is NOT Supported!! \n");
                    }
                }

            }
        }
        FOREACH_ACTIVESITE_END
}

void WaitDoneMacro_Value_Update(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, MACRO_DOUBLE Expect_Value, INT MaxCheckCount, DOUBLE IntervalTime_ms, EXPECT_RESULT& ExpectResult) {
    //	if (IntervalTime_ms < 1){
    //		hout(DETAIL) << "####################### IntervalTime_ms < 1 ms, set to 1 ms  #####################" << endl;
    //		IntervalTime_ms = 1;
    //	}

    INT checkCount = 0; /*Temp local variable for time out count*/
    ExpectResult.allpass = true;

    do {
        ExpectResult.allpass = false;
        checkCount++;
        //		WAIT_TIME(IntervalTime_ms ms);
//        api->sleep(IntervalTime_ms);
//        TheInst.Wait(IntervalTime_ms*1000);
    	TheInst.Wait(0.001 * IntervalTime_ms);//2ms
        MACRO_DOUBLE Read_Value;
        SEGMENT_READ_MACRO(MacroLane_Sel, reg_info_ex, Read_Value);
        //		FOR_EACH_SITE_BEGIN();
        //		INT SiteID = CURRENT_SITE_NUMBER() - 1;

//        FOREACH_ACTIVE_SITE(api) {
//            unsigned int SiteID = api->Get_active_site();
            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
                const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

                if (Read_Value[SiteID][MacroID] != Expect_Value[SiteID][MacroID]) //ZH change from == to != to fix bug 0628
                {

                    ExpectResult.allpass = true;
                }

            }

            FOREACH_ACTIVESITE_END
        hout(DETAIL) << "WaitDone_CheckCount = " << dec << checkCount << endl;
    } while (true == ExpectResult.allpass && checkCount < MaxCheckCount);

    if (checkCount >= MaxCheckCount) {
        /**************** print wait done result ****************/
        hout(GENERAL) << "#######################  Wait Done time out #######################" << endl;
        if (ExpectResult.allfail) {
            hout(DETAIL) << "####################### All Sites Wait Done Failed!!! #####################" << endl;
        } else {
            //			FOR_EACH_SITE_BEGIN();
            //			INT SiteID = CURRENT_SITE_NUMBER() - 1;

//            FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
//                //			hout(DETAIL) << "#######################WAIT DONE RESULT = " << ExpectResult.eachsite[SiteID] << " #########" << endl;
//                //			FOR_EACH_SITE_END();
//            }
        }
    }
}

void HiLink_PerLane_Judge_Regulator(const MACRO_LANE_SEL& MacroLane_Sel, LANE_DOUBLE& NodeCode, LANE_DOUBLE& NodeVolt, string sJudgeNameInTable_NodeCode, string sJudgeNameInTable_NodeVolt, JUDGE_PIN Judge_Pin) {

    STRING_VECTOR JudgePins;
    JudgePins.clear();

    //     STRING sTestsuiteName;
    //	 GET_TESTSUITE_NAME(sTestsuiteName);
    //
    //	 TMLimits::LimitInfo strLimitInfo_NodeCode;
    //	 strLimitInfo_NodeCode = tmLimits.getLimit(sTestsuiteName,sJudgeNameInTable_NodeCode);
    //
    //	 TMLimits::LimitInfo strLimitInfo_NodeVolt;
    //	 strLimitInfo_NodeVolt = tmLimits.getLimit(sTestsuiteName,sJudgeNameInTable_NodeVolt);
    //
    string OPL_NodeCode, OPH_NodeCode, sTestName_NodeCode, sLimitUnit_NodeCode;
    double LowLimit_NodeCode, HiLimit_NodeCode;
    //	 LowLimit_NodeCode =strLimitInfo_NodeCode.Lsl;
    //	 HiLimit_NodeCode =strLimitInfo_NodeCode.Usl;
    //	 OPL_NodeCode =strLimitInfo_NodeCode.LslTyp;
    //	 OPH_NodeCode =strLimitInfo_NodeCode.UslTyp;
    //	 sTestName_NodeCode =strLimitInfo_NodeCode.TestName;
    //	 sLimitUnit_NodeCode =strLimitInfo_NodeCode.Units;
    //
    string OPL_NodeVolt, OPH_NodeVolt, sTestName_NodeVolt, sLimitUnit_NodeVolt;
    double LowLimit_NodeVolt, HiLimit_NodeVolt;
    //	 LowLimit_NodeVolt =strLimitInfo_NodeVolt.Lsl;
    //	 HiLimit_NodeVolt =strLimitInfo_NodeVolt.Usl;
    //	 OPL_NodeVolt =strLimitInfo_NodeVolt.LslTyp;
    //	 OPH_NodeVolt =strLimitInfo_NodeVolt.UslTyp;
    //	 sTestName_NodeVolt =strLimitInfo_NodeVolt.TestName;
    //	 sLimitUnit_NodeVolt =strLimitInfo_NodeVolt.Units;

    if (sJudgeNameInTable_NodeCode == "VREGDATALVL_CODE") {
        LowLimit_NodeCode = 0;
        HiLimit_NodeCode = 30;
        OPL_NodeCode = "GE";
        OPH_NodeCode = "LE";
    } else if (sJudgeNameInTable_NodeCode == "VREGCLKLVL_CODE") {
        LowLimit_NodeCode = 0;
        HiLimit_NodeCode = 30;
        OPL_NodeCode = "GE";
        OPH_NodeCode = "LE";
    } else if (sJudgeNameInTable_NodeCode == "TXPREDRVREGLVL_CODE") {
        LowLimit_NodeCode = 0;
        HiLimit_NodeCode = 30;
        OPL_NodeCode = "GE";
        OPH_NodeCode = "LE";
    } else if (sJudgeNameInTable_NodeCode == "TXDRVREGLVL_CODE") {
        LowLimit_NodeCode = 0;
        HiLimit_NodeCode = 30;
        OPL_NodeCode = "GE";
        OPH_NodeCode = "LE";
    } else if (sJudgeNameInTable_NodeCode == "VREGLVL_CODE") {
        LowLimit_NodeCode = 0;
        HiLimit_NodeCode = 30;
        OPL_NodeCode = "GE";
        OPH_NodeCode = "LE";
    } else if (sJudgeNameInTable_NodeCode == "CTLEVREGVREFSEL_CODE") {
        LowLimit_NodeCode = 0;
        HiLimit_NodeCode = 6;
        OPL_NodeCode = "GE";
        OPH_NodeCode = "LE";
    }

    if (sJudgeNameInTable_NodeVolt == "VREGDATA_VREG_2_3") {
        LowLimit_NodeVolt = 1200;
        HiLimit_NodeVolt = 1200;
        OPL_NodeVolt = "GE";
        OPH_NodeVolt = "LE";
    } else if (sJudgeNameInTable_NodeVolt == "VREGCLK_VREG_2_3_3") {
        LowLimit_NodeVolt = 1200;
        HiLimit_NodeVolt = 1200;
        OPL_NodeVolt = "GE";
        OPH_NodeVolt = "LE";
    } else if (sJudgeNameInTable_NodeVolt == "VREG_PREDRV_2_3") {
        LowLimit_NodeVolt = 1200;
        HiLimit_NodeVolt = 1200;
        OPL_NodeVolt = "GE";
        OPH_NodeVolt = "LE";
    } else if (sJudgeNameInTable_NodeVolt == "VREG_DRV_2_3") {
        LowLimit_NodeVolt = 1200;
        HiLimit_NodeVolt = 1200;
        OPL_NodeVolt = "GE";
        OPH_NodeVolt = "LE";
    } else if (sJudgeNameInTable_NodeVolt == "VREG_VREG_2_3") {
        LowLimit_NodeVolt = 1200;
        HiLimit_NodeVolt = 1200;
        OPL_NodeVolt = "GE";
        OPH_NodeVolt = "LE";
    } else if (sJudgeNameInTable_NodeVolt == "CTLE_VREG_VOUT_1_7") {
        LowLimit_NodeVolt = 970;
        HiLimit_NodeVolt = 1100;
        OPL_NodeVolt = "GE";
        OPH_NodeVolt = "LE";
    }


    //	FOR_EACH_SITE_BEGIN();
    //	INT SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
	int tempTestNumber=0;
    FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
	tempTestNumber=0;

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
            for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++)//per lane /per marco judge
            {
                UINT LaneID = vLane[laneIndex];
                JudgePins.clear();

                switch (Judge_Pin) {
                    case 0: JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_P);
                        break;
                    case 1: JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_N);
                        break;
                    case 2: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);
                        break;
                    case 3: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_N);
                        break;
                    default: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);
                        break;
                }

                string sLocalLimitCompareResult_NodeCode = LocalLimitCompare(OPL_NodeCode, LowLimit_NodeCode, OPH_NodeCode, HiLimit_NodeCode, NodeCode[SiteID][MacroID][LaneID]);
                string sLocalLimitCompareResult_NodeVolt = LocalLimitCompare(OPL_NodeVolt, LowLimit_NodeVolt, OPH_NodeVolt, HiLimit_NodeVolt, NodeVolt[SiteID][MacroID][LaneID]);

                ARRAY_D NodeCodeValueForJudge;
                ARRAY_D NodeVoltValueForJudge;
                NodeCodeValueForJudge.resize(1);
                NodeVoltValueForJudge.resize(1);
                NodeCodeValueForJudge[0] = NodeCode[SiteID][MacroID][LaneID];
                NodeVoltValueForJudge[0] = NodeVolt[SiteID][MacroID][LaneID];

                stringstream ss; //int 2 string
                ss << macroIndex;
                string strmacroIndex;
                ss >> strmacroIndex;

                stringstream ss1; //int 2 string
                ss1 << laneIndex;
                string strlaneIndex;
                ss1 >> strlaneIndex;
                string Macro_Lane_Name = "M" + strmacroIndex + "_L" + strlaneIndex;


                if ((sLocalLimitCompareResult_NodeCode == "PASSED")&&(sLocalLimitCompareResult_NodeVolt == "FAILED")) {
                    double LowerLimit_tmp = 0;
                    double UpperLimit_tmp = 1200;
                    //TEST(JudgePins[macroIndex], sJudgeNameInTable_NodeVolt, LIMIT(TM::GE, LowerLimit_tmp,TM::LE, UpperLimit_tmp), NodeVolt[SiteID][MacroID][LaneID],true);
                    //                                    TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, sJudgeNameInTable_NodeVolt, LIMIT(TM::GE, LowerLimit_tmp,TM::LE, UpperLimit_tmp), NodeVoltValueForJudge); //modify for the datalog format,if use pin as parameter,dalog show: testname@pin
                    //                                    TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, sJudgeNameInTable_NodeCode, tmLimits, NodeCodeValueForJudge);

                    judgeAndLog_ParametricTest(SiteID, sJudgeNameInTable_NodeVolt, Macro_Lane_Name, LowerLimit_tmp, NodeVoltValueForJudge[0], UpperLimit_tmp,m_TestNumber + tempTestNumber);tempTestNumber++;
                    judgeAndLog_ParametricTest(SiteID, sJudgeNameInTable_NodeCode, Macro_Lane_Name, LowLimit_NodeCode, NodeCodeValueForJudge[0], HiLimit_NodeCode,m_TestNumber + tempTestNumber);tempTestNumber++;


                } else if ((sLocalLimitCompareResult_NodeCode == "FAILED")&&(sLocalLimitCompareResult_NodeVolt == "PASSED")) {
                    double LowerLimit_tmp = 0;
                    double UpperLimit_tmp = 31;
                    //TEST(JudgePins[macroIndex], sJudgeNameInTable_NodeCode, LIMIT(TM::GE, LowerLimit_tmp,TM::LE, UpperLimit_tmp), NodeCode[SiteID][MacroID][LaneID],true);
                    //                                    TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, sJudgeNameInTable_NodeCode, LIMIT(TM::GE, LowerLimit_tmp,TM::LE, UpperLimit_tmp), NodeCodeValueForJudge);
                    //
                    //                                    TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, sJudgeNameInTable_NodeVolt, tmLimits, NodeVoltValueForJudge);

                    judgeAndLog_ParametricTest(SiteID, sJudgeNameInTable_NodeVolt, Macro_Lane_Name, LowLimit_NodeVolt, NodeVoltValueForJudge[0], HiLimit_NodeVolt,m_TestNumber + tempTestNumber);tempTestNumber++;
                    judgeAndLog_ParametricTest(SiteID, sJudgeNameInTable_NodeCode, Macro_Lane_Name, LowerLimit_tmp, NodeCodeValueForJudge[0], UpperLimit_tmp,m_TestNumber + tempTestNumber);tempTestNumber++;

                } else {
                    //                                    TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, sJudgeNameInTable_NodeCode, tmLimits, NodeCodeValueForJudge);
                    //                                    TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, sJudgeNameInTable_NodeVolt, tmLimits, NodeVoltValueForJudge);

                    judgeAndLog_ParametricTest(SiteID, sJudgeNameInTable_NodeVolt, Macro_Lane_Name, LowLimit_NodeVolt, NodeVoltValueForJudge[0], HiLimit_NodeVolt,m_TestNumber + tempTestNumber);tempTestNumber++;
                    judgeAndLog_ParametricTest(SiteID, sJudgeNameInTable_NodeCode, Macro_Lane_Name, LowLimit_NodeCode, NodeCodeValueForJudge[0], HiLimit_NodeCode,m_TestNumber + tempTestNumber);tempTestNumber++;
                }
            }
        }
        FOREACH_ACTIVESITE_END
		m_TestNumber = m_TestNumber + tempTestNumber;
}

void FW_ABIST_SSArrayD_ReadBack(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE) {
    //
    ////	D2S_FRAMEWORK;
    //	//GET_TEST_INFO;
    //
    //	MACRO_ARRAY_D  Spec_Upper_Value, Spec_Lower_Value;
    //
    //	Spec_Upper_Value.init(9999,0);
    //	Spec_Lower_Value.init(9999,0);
    //
    //	sprintf(label,"H30V101_SRAM_SSread_%s_%f_%f_",TestSuiteName.c_str(),Vcoef,Temp);
    ////	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    //                 d2s::d2s_LABEL_BEGIN("FW_ABIST_SSArrayD_ReadBack_", Global_D2S_Mode);
    //	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
    //	{
    //		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
    //		selectMacro(MacroID);
    //
    //
    //		for(uint RegIndex =0; RegIndex <FWABIST_REG_BASE.get_SS_FWABIST_REG_count(); RegIndex ++)
    //		{
    //			ostringstream strHigh,strLow;
    //			uint SpecHigh_Address = FWABIST_REG_BASE.get_SS_FWABIST_REG(RegIndex).SpecHigh_Address;
    //			uint SpecLow_Address = FWABIST_REG_BASE.get_SS_FWABIST_REG(RegIndex).SpecLow_Address;
    //			strHigh <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<SpecHigh_Address<<"_SSRegIndex_0x"<<hex<<RegIndex;
    //			strLow <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<SpecLow_Address<<"_SSRegIndex_0x"<<hex<<RegIndex;
    //			jtag.read(SpecHigh_Address>>1,strHigh.str());
    //			jtag.read(SpecLow_Address>>1,strLow.str());
    //		}
    //
    //
    //	}
    ////	fr.d2s_LABEL_END();
    //d2s::d2s_LABEL_END();
    ////	FOR_EACH_SITE_BEGIN();
    ////	INT SiteID = CURRENT_SITE_NUMBER() - 1;
    //            FOREACH_ACTIVE_SITE(api) {
    //                unsigned int SiteID = api->Get_active_site();
    //	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
    //	{
    //		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
    //
    //		for(uint RegIndex =0; RegIndex <FWABIST_REG_BASE.get_SS_FWABIST_REG_count(); RegIndex ++)
    //		{
    //			ostringstream strHigh, strLow;
    //			uint SpecHigh_Address = FWABIST_REG_BASE.get_SS_FWABIST_REG(RegIndex).SpecHigh_Address;
    //			uint SpecLow_Address = FWABIST_REG_BASE.get_SS_FWABIST_REG(RegIndex).SpecLow_Address;
    //
    //			strHigh <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<SpecHigh_Address<<"_SSRegIndex_0x"<<hex<<RegIndex;
    //			strLow <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<SpecLow_Address<<"_SSRegIndex_0x"<<hex<<RegIndex;
    //
    //
    //			Spec_Upper_Value[SiteID][MacroID][RegIndex] =  (INT)jtag.getReadValue(strHigh.str());
    //			Spec_Upper_Value[SiteID][MacroID][RegIndex] = (((INT)Spec_Upper_Value[SiteID][MacroID][RegIndex]& 0xff00)>>8) |(((INT)Spec_Upper_Value[SiteID][MacroID][RegIndex]& 0x00ff)<<8); //big edian
    //
    //			hout(DETAIL)<<"READBack: SpecHigh_Address: 0x"<<hex<<SpecHigh_Address<<"   "<<"Data: "<<dec<<Spec_Upper_Value[SiteID][MacroID][RegIndex]<<endl;
    //			Spec_Lower_Value[SiteID][MacroID][RegIndex] =  (INT)jtag.getReadValue(strLow.str());
    //			Spec_Lower_Value[SiteID][MacroID][RegIndex] = (((INT)Spec_Lower_Value[SiteID][MacroID][RegIndex]& 0xff00)>>8) |(((INT)Spec_Lower_Value[SiteID][MacroID][RegIndex]& 0x00ff)<<8); //big edian
    //			hout(DETAIL)<<"READBack: SpecLow_Address: 0x"<<hex<<SpecLow_Address<<"   "<<"Data: "<<dec<<Spec_Lower_Value[SiteID][MacroID][RegIndex]<<endl;
    //		}
    //	}
    //
    ////	FOR_EACH_SITE_END();
    //            }
    //
    //	sprintf(label,"H30V101_SRAM_SSread_%s_%f_%f_",TestSuiteName.c_str(),Vcoef,Temp);
    ////	fr.d2s_LABEL_BEGIN(label,d2sFrameWorkModeType::Enum(d2s_mode));
    //                         d2s::d2s_LABEL_BEGIN("FW_ABIST_SSArrayD_ReadBack_", Global_D2S_Mode);
    //	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
    //	{
    //		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
    //		selectMacro(MacroID);
    //
    //
    //		for(uint RegIndex =0; RegIndex <FWABIST_REG_BASE.get_SS_FWABIST_Calculate_REG_count(); RegIndex ++)
    //		{
    //			ostringstream strHigh,strLow;
    //			uint SpecHigh_Address = FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).SpecHigh_Address;
    //			uint SpecLow_Address = FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).SpecLow_Address;
    //			strHigh <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<SpecHigh_Address<<"_SSRegIndex_0x"<<hex<<RegIndex;
    //			strLow <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<SpecLow_Address<<"_SSRegIndex_0x"<<hex<<RegIndex;
    //			jtag.read(SpecHigh_Address>>1,strHigh.str());
    //			jtag.read(SpecLow_Address>>1,strLow.str());
    //		}
    //
    //
    //	}
    ////	fr.d2s_LABEL_END();
    //d2s::d2s_LABEL_END();
    ////	FOR_EACH_SITE_BEGIN();
    ////	INT SiteID = CURRENT_SITE_NUMBER() - 1;
    //            FOREACH_ACTIVE_SITE(api) {
    //                unsigned int SiteID = api->Get_active_site();
    //	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
    //	{
    //		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
    //
    //		for(uint RegIndex =0; RegIndex <FWABIST_REG_BASE.get_SS_FWABIST_Calculate_REG_count(); RegIndex ++)
    //		{
    //			ostringstream strHigh, strLow;
    //			uint SpecHigh_Address = FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).SpecHigh_Address;
    //			uint SpecLow_Address = FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).SpecLow_Address;
    //
    //			strHigh <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<SpecHigh_Address<<"_SSRegIndex_0x"<<hex<<RegIndex;
    //			strLow <<"Macro"<<"_"<<MacroID<<"_"<< "SRAM" << "_Address_0x" <<hex<<SpecLow_Address<<"_SSRegIndex_0x"<<hex<<RegIndex;
    //
    //
    //			Spec_Upper_Value[SiteID][MacroID][RegIndex] =  (INT)jtag.getReadValue(strHigh.str());
    //			Spec_Upper_Value[SiteID][MacroID][RegIndex] = (((INT)Spec_Upper_Value[SiteID][MacroID][RegIndex]& 0xff00)>>8) |(((INT)Spec_Upper_Value[SiteID][MacroID][RegIndex]& 0x00ff)<<8); //big edian
    //
    //			hout(DETAIL)<<"READBack: SpecHigh_Address: 0x"<<hex<<SpecHigh_Address<<"   "<<"Data: "<<dec<<Spec_Upper_Value[SiteID][MacroID][RegIndex]<<endl;
    //			Spec_Lower_Value[SiteID][MacroID][RegIndex] =  (INT)jtag.getReadValue(strLow.str());
    //			Spec_Lower_Value[SiteID][MacroID][RegIndex] = (((INT)Spec_Lower_Value[SiteID][MacroID][RegIndex]& 0xff00)>>8) |(((INT)Spec_Lower_Value[SiteID][MacroID][RegIndex]& 0x00ff)<<8); //big edian
    //			hout(DETAIL)<<"READBack: SpecLow_Address: 0x"<<hex<<SpecLow_Address<<"   "<<"Data: "<<dec<<Spec_Lower_Value[SiteID][MacroID][RegIndex]<<endl;
    //		}
    //	}
    //
    ////	FOR_EACH_SITE_END();
    //            }
}

void HiLink_PerMacroSSArrayD_Judge(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE, MACRO_ARRAY_D& TempResult, JUDGE_PIN Judge_Pin) {
    /***************sub func begin****************/
    //	INT SiteID = CURRENT_SITE_NUMBER() - 1;	

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
	int tempTestNumber=0;
    FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
	tempTestNumber=0;

        for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_SS_FWABIST_REG_count(); RegIndex++) {
            STRING_VECTOR JudgePins;
            JudgePins.clear();
            ARRAY_D ValueForJudge;
            ValueForJudge.resize(MacroLane_Sel.size());
            STRING testname = FWABIST_REG_BASE.get_SS_FWABIST_REG(RegIndex).name;
            //		LimitTable_Manager::InitAndUpdateLimit(testname);

            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
                switch (Judge_Pin) {
                    case 0: JudgePins.push_back(LANE_INFO[MacroID][0].RX_P);
                        break;
                    case 1: JudgePins.push_back(LANE_INFO[MacroID][0].RX_N);
                        break;
                    case 2: JudgePins.push_back(LANE_INFO[MacroID][0].TX_P);
                        break;
                    case 3: JudgePins.push_back(LANE_INFO[MacroID][0].TX_N);
                        break;
                    default: JudgePins.push_back(LANE_INFO[MacroID][0].TX_P);
                        break;
                }

                ValueForJudge[macroIndex] = TempResult[SiteID][MacroID][RegIndex];

                stringstream ss; //int 2 string					
                ss << macroIndex;
                string strmacroIndex;
                ss >> strmacroIndex;
                string Macro_Lane_Name = "M" + strmacroIndex;
                judgeAndLog_ParametricTest(SiteID, testname, Macro_Lane_Name, FWABIST_REG_BASE.get_SS_FWABIST_REG(RegIndex).SpecLow_Value, ValueForJudge[macroIndex], FWABIST_REG_BASE.get_SS_FWABIST_REG(RegIndex).SpecHigh_Value,m_TestNumber + tempTestNumber);
                tempTestNumber++;

            }

            //		TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, testname, tmLimits, ValueForJudge);
        }
        FOREACH_ACTIVESITE_END
		m_TestNumber = m_TestNumber + tempTestNumber;
    /***************sub func end****************/
}

void HiLink_PerMacroSSCalArrayD_Judge(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE, MACRO_ARRAY_D& TempResult, JUDGE_PIN Judge_Pin) {
    /***************sub func begin****************/
    //	INT SiteID = CURRENT_SITE_NUMBER() - 1;	

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
	int tempTestNumber=0;
    FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
	tempTestNumber=0;

        for (uint RegIndex = 0; RegIndex < FWABIST_REG_BASE.get_SS_FWABIST_Calculate_REG_count(); RegIndex++) {
            STRING_VECTOR JudgePins;
            JudgePins.clear();
            ARRAY_D ValueForJudge;
            ValueForJudge.resize(MacroLane_Sel.size());
            STRING testname = FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).NODE_NAME;
            //		LimitTable_Manager::InitAndUpdateLimit(testname);

            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
                switch (Judge_Pin) {
                    case 0: JudgePins.push_back(LANE_INFO[MacroID][0].RX_P);
                        break;
                    case 1: JudgePins.push_back(LANE_INFO[MacroID][0].RX_N);
                        break;
                    case 2: JudgePins.push_back(LANE_INFO[MacroID][0].TX_P);
                        break;
                    case 3: JudgePins.push_back(LANE_INFO[MacroID][0].TX_N);
                        break;
                    default: JudgePins.push_back(LANE_INFO[MacroID][0].TX_P);
                        break;
                }

                ValueForJudge[macroIndex] = TempResult[SiteID][MacroID][RegIndex];

                stringstream ss; //int 2 string					
                ss << macroIndex;
                string strmacroIndex;
                ss >> strmacroIndex;
                string Macro_Lane_Name = "M" + strmacroIndex;
                judgeAndLog_ParametricTest(SiteID, testname, Macro_Lane_Name, FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).SpecLow_Value, ValueForJudge[macroIndex], FWABIST_REG_BASE.get_SS_Calculate_REG(RegIndex).SpecHigh_Value,m_TestNumber + tempTestNumber);
                tempTestNumber++;
            }

            //		TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, testname, tmLimits, ValueForJudge);


        }
        FOREACH_ACTIVESITE_END
		m_TestNumber = m_TestNumber + tempTestNumber;
    /***************sub func end****************/
}

void CSR_READ(const MACRO_LANE_SEL& MacroLane_Sel, HILINK_Regs_Base& reg, const INT& csr, LANE_INT& perlane_value) {
    /***************this sub func must in ON_FIRST_INVOCATION_BEGIN block**************/
    perlane_value.init(0);
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    //	D2S_FRAMEWORK;

    //    fr.d2s_LABEL_BEGIN("Segment_read_",d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("CSR_READ_", Global_D2S_Mode);
    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

        selectMacro(MacroID);

        for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
            UINT LaneID = vLane[laneIndex];
            reg.SliceID(LaneID).Broadcast(0);
            ostringstream str;
            str << "CSR_READ2IDSTRING" << "_CSR_" << csr << "_M" << MacroID << "_L" << LaneID;
            reg.Read2IDString(csr, str.str());
        }
    }
    //    fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //		INT SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

            for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
                UINT LaneID = vLane[laneIndex];
                ostringstream str;
                str << "CSR_READ2IDSTRING" << "_CSR_" << csr << "_M" << MacroID << "_L" << LaneID;
                perlane_value[SiteID][MacroID][LaneID] = (INT) jtag.getReadValue(str.str())[SiteID];
            }
        }
        FOREACH_ACTIVESITE_END
}

void CSR_READ(const MACRO_LANE_SEL& MacroLane_Sel, HILINK_Regs_Base& reg, const INT& csr, MACRO_INT& permacro_value) {
    /***************this sub func must in ON_FIRST_INVOCATION_BEGIN block**************/
    permacro_value.init(0);
    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    //    fr.d2s_LABEL_BEGIN("Segment_read_",d2sFrameWorkModeType::Enum(d2s_mode));
    d2s::d2s_LABEL_BEGIN("CSR_READ_", Global_D2S_Mode);
    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        selectMacro(MacroID);

        ostringstream str;
        str << "CSR_READ2IDSTRING" << "_CSR_" << csr << "_M" << MacroID;
        reg.Read2IDString(csr, str.str());
    }
    //    fr.d2s_LABEL_END();
    d2s::d2s_LABEL_END();
    //	FOR_EACH_SITE_BEGIN();
    //		INT SiteID = CURRENT_SITE_NUMBER() - 1;
//
//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            ostringstream str;
            str << "CSR_READ2IDSTRING" << "_CSR_" << csr << "_M" << MacroID;
            permacro_value[SiteID][MacroID] = (INT) jtag.getReadValue(str.str())[SiteID];
        }
        FOREACH_ACTIVESITE_END
}

void FWreadAllRegisters2CSR_ForDebug(MACRO_LANE_SEL& MacroLane_Sel) {
    UINT site = get_focus_site();
    //	D2S_FRAMEWORK;

    int org_d2s_mode;
    //	GET_USER_FLAG("d2s_mode",&org_d2s_mode);

    //	SET_USER_FLAG("d2s_mode",1);

    org_d2s_mode = 1;
    if (org_d2s_mode != 2) {

        hout(DETAIL) << "site " << site << "'s CSR will be readback as default value!" << endl;

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            selectMacro_Now(MacroID);
            hout(DETAIL) << "Macro ===================== " << MacroID << endl;
            hout(DETAIL) << "=========CS_READ==========" << endl;

            CS.clkRegs.MacroID(MacroID).Broadcast(0);
            CS.clkdebug.MacroID(MacroID).Broadcast(0);
            SRAM.CPAPIRegs.MacroID(MacroID).Broadcast(0);
            SRAM.CSAPIRegs.MacroID(MacroID).Broadcast(0);
            SRAM.TOPAPIRegs.MacroID(MacroID).Broadcast(0);
            SRAM.ABISTAPIRegs.MacroID(MacroID).Broadcast(0);

            hout(DETAIL) << "=========clkRegs_READ==========" << endl;
            CS.clkRegs.ReadAll2CSR();
            hout(DETAIL) << "=========clkdebug_READ==========" << endl;
            CS.clkdebug.ReadAll2CSR();
            hout(DETAIL) << "=========CPAPIRegs_READ==========" << endl;
            SRAM.CPAPIRegs.ReadAll2CSR();
            hout(DETAIL) << "=========CSAPIRegs_READ==========" << endl;
            SRAM.CSAPIRegs.ReadAll2CSR();
            hout(DETAIL) << "=========TOPAPIRegs_READ==========" << endl;
            SRAM.TOPAPIRegs.ReadAll2CSR();
            hout(DETAIL) << "=========ABISTAPIRegs_READ==========" << endl;
            SRAM.ABISTAPIRegs.ReadAll2CSR();

            //			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
            //			for(uint laneIndex = 0; laneIndex<vLane.size(); laneIndex++)
            //			{
            //				UINT LaneID = vLane[laneIndex];
            //				hout(DETAIL)<<"=========DS_READ==========" << endl;
            //				hout(DETAIL)<<"Lane ID=========="<< LaneID << endl;
            //
            //				DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
            //				DS.txRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
            //				DS.clkRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
            //				DS.rxExtRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
            //				SRAM.DSAPIRegs.MacroID(MacroID).SliceID(LaneID);
            //
            //				DS.rxRegs.ReadAll2CSR();
            //				DS.rxExtRegs.ReadAll2CSR();
            //				DS.txRegs.ReadAll2CSR();
            //				DS.clkRegs.ReadAll2CSR();
            //				SRAM.DSAPIRegs.ReadAll2CSR();
            //
            //			}
        }
    }
    //	SET_USER_FLAG("d2s_mode",org_d2s_mode);
}

void FWAbist_PreJudge(const MACRO_LANE_SEL& MacroLane_Sel, MACRO_DOUBLE& permacro_value, bool& PreJudge_Result) {
    /***************this sub func must in ON_FIRST_INVOCATION_BEGIN block**************/

    PreJudge_Result = true;

    //	FOR_EACH_SITE_BEGIN();
    //		INT SiteID = CURRENT_SITE_NUMBER() - 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            //			if(permacro_value[SiteID][MacroID] == 0)
            if (permacro_value[SiteID][MacroID] != 1) {
                PreJudge_Result = false;
            }

        }
        FOREACH_ACTIVESITE_END
}

void ALL_CSR_ReadBack_TO_FILE_Debug(const MACRO_LANE_SEL& MacroLane_Sel, const string& file_name) {
//    CS.clkRegs.dumpAllCSR(MacroLane_Sel, file_name);
//    CS.clkdebug.dumpAllCSR(MacroLane_Sel,file_name);
//    DS.clkRegs.dumpAllCSR(MacroLane_Sel,file_name);
//    //	DS.txRegs.dumpAllCSR(MacroLane_Sel,file_name);
//    DS.rxRegs.dumpAllCSR(MacroLane_Sel, file_name);
////    DS.rxExtRegs.dumpAllCSR(MacroLane_Sel, file_name);
    	SRAM.ABISTAPIRegs.dumpAllCSR(MacroLane_Sel,file_name);
//    //	SRAM.CPAPIRegs.dumpAllCSR(MacroLane_Sel,file_name);
//    	SRAM.CSAPIRegs.dumpAllCSR(MacroLane_Sel,file_name);
//    //	SRAM.DSAPIRegs.dumpAllCSR(MacroLane_Sel,file_name);
    	SRAM.TOPAPIRegs.dumpAllCSR(MacroLane_Sel,file_name);

}

void ALL_CS_CSR_ReadBack_TO_FILE_Debug(const MACRO_LANE_SEL& MacroLane_Sel, const string& file_name) {
    //	CS.clkRegs.dumpAllCSR(MacroLane_Sel,file_name);
    //	CS.clkdebug.dumpAllCSR(MacroLane_Sel,file_name);

}

void ALL_DS_CSR_ReadBack_TO_FILE_Debug(const MACRO_LANE_SEL& MacroLane_Sel, const string& file_name) {

    //	DS.clkRegs.dumpAllCSR(MacroLane_Sel,file_name);
    //	DS.txRegs.dumpAllCSR(MacroLane_Sel,file_name);
    //	DS.rxRegs.dumpAllCSR(MacroLane_Sel,file_name);
    //	DS.rxExtRegs.dumpAllCSR(MacroLane_Sel,file_name);

}

void ALL_API_CSR_ReadBack_TO_FILE_Debug(const MACRO_LANE_SEL& MacroLane_Sel, const string& file_name) {
    //	CS.clkRegs.dumpAllCSR(MacroLane_Sel,file_name);
    //	CS.clkdebug.dumpAllCSR(MacroLane_Sel,file_name);
    //	DS.clkRegs.dumpAllCSR(MacroLane_Sel,file_name);
    //	DS.txRegs.dumpAllCSR(MacroLane_Sel,file_name);
    //	DS.rxRegs.dumpAllCSR(MacroLane_Sel,file_name);
    //	DS.rxExtRegs.dumpAllCSR(MacroLane_Sel,file_name);
    //	SRAM.ABISTAPIRegs.dumpAllCSR(MacroLane_Sel,file_name);
    //	SRAM.CPAPIRegs.dumpAllCSR(MacroLane_Sel,file_name);
    //	SRAM.CSAPIRegs.dumpAllCSR(MacroLane_Sel,file_name);
    //	SRAM.DSAPIRegs.dumpAllCSR(MacroLane_Sel,file_name);
    //	SRAM.TOPAPIRegs.dumpAllCSR(MacroLane_Sel,file_name);

}

void HiLink_PerLane_Judge(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname, double LimitL, LANE_DOUBLE& TempResult, double LimitH, JUDGE_PIN Judge_Pin) {

		int tempTestNumber =  0;
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

            STRING_VECTOR JudgePins;
            JudgePins.clear();
            ARRAY_D ValueForJudge;
            ValueForJudge.resize(vLane.size());

            for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
                UINT LaneID = vLane[laneIndex];
                switch (Judge_Pin) {
                    case 0: JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_P);
                        break;
                    case 1: JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_N);
                        break;
                    case 2: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);
                        break;
                    case 3: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_N);
                        break;
                    default: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);
                        break;
                }
                ValueForJudge[laneIndex] = TempResult[SiteID][MacroID][LaneID];

                stringstream ss; //int 2 string
                ss << macroIndex;
                string strmacroIndex;
                ss >> strmacroIndex;

                stringstream ss1; //int 2 string
                ss1 << laneIndex;
                string strlaneIndex;
                ss1 >> strlaneIndex;
                string Macro_Lane_Name = "M" + strmacroIndex + "_L" + strlaneIndex;

                judgeAndLog_ParametricTest(SiteID, testname, Macro_Lane_Name, LimitL, ValueForJudge[laneIndex], LimitH,tempTestNumber+m_TestNumber);
                tempTestNumber++;
            }
        }
        FOREACH_ACTIVESITE_END
		m_TestNumber = m_TestNumber + tempTestNumber;
//	vector<vector<SiteDouble>> result_MarcoLaneSite;// [marco][lane][site]
//	result_MarcoLaneSite.resize(MacroLane_Sel.size());
//	int siteCount = TheSoft.Sites().Active().GetActiveSiteCount();
//
//
//    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
//        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//        const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//		result_MarcoLaneSite[MacroID].resize(vLane.size());
//        for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
//            UINT LaneID = vLane[laneIndex];
//    		result_MarcoLaneSite[MacroID][LaneID].resize(siteCount);
//
//        	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//				result_MarcoLaneSite[MacroID][LaneID][SiteID] = (double)TempResult[SiteID][MacroID][LaneID];
//		    FOREACH_ACTIVESITE_END
//        }
//    }
//
//
//
//
//    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
//
//        UINT MacroID = MacroLane_Sel[macroIndex].MacroID; //get macro ID
//        const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane; //get lane count
//
//        for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
//            UINT LaneID = vLane[laneIndex];
//
//            stringstream ss; //int 2 string
//            ss << macroIndex;
//            string strmacroIndex;
//            ss >> strmacroIndex;
//
//            stringstream ss1; //int 2 string
//            ss1 << laneIndex;
//            string strlaneIndex;
//            ss1 >> strlaneIndex;
//            string Macro_Lane_Name = "M" + strmacroIndex + "_L" + strlaneIndex;
//
//			TheSoft.Flow().TestLimit(result_MarcoLaneSite[MacroID][LaneID],E_LEFTCLOSE_RIGHTCLOSE);//,testname+"_"+Macro_Lane_Name
//		}
//	}



}

void HiLink_PerLane_Judge(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname, double LimitL, LANE_INT& TempResult, double LimitH, JUDGE_PIN Judge_Pin) {

		int  tempTestNumber=0;
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

            STRING_VECTOR JudgePins;
            JudgePins.clear();
            ARRAY_D ValueForJudge;
            ValueForJudge.resize(vLane.size());

            for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
                UINT LaneID = vLane[laneIndex];
                switch (Judge_Pin) {
                    case 0: JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_P);
                        break;
                    case 1: JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_N);
                        break;
                    case 2: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);
                        break;
                    case 3: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_N);
                        break;
                    default: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);
                        break;
                }
                ValueForJudge[laneIndex] = double(TempResult[SiteID][MacroID][LaneID]);

                stringstream ss; //int 2 string
                ss << macroIndex;
                string strmacroIndex;
                ss >> strmacroIndex;

                stringstream ss1; //int 2 string
                ss1 << laneIndex;
                string strlaneIndex;
                ss1 >> strlaneIndex;
                string Macro_Lane_Name = "M" + strmacroIndex + "_L" + strlaneIndex;
                judgeAndLog_ParametricTest(SiteID, testname, Macro_Lane_Name, LimitL, ValueForJudge[laneIndex], LimitH, m_TestNumber + tempTestNumber);
                tempTestNumber++;
            }
        }
        FOREACH_ACTIVESITE_END
		m_TestNumber = m_TestNumber + tempTestNumber;

//	vector<vector<SiteInt>> result_MarcoLaneSite;// [marco][lane][site]
//	result_MarcoLaneSite.resize(MacroLane_Sel.size());
//	int siteCount = TheSoft.Sites().Active().GetActiveSiteCount();
//
//
//    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
//        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//        const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//		result_MarcoLaneSite[MacroID].resize(vLane.size());
//        for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
//            UINT LaneID = vLane[laneIndex];
//    		result_MarcoLaneSite[MacroID][LaneID].resize(siteCount);
//
//        	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//				result_MarcoLaneSite[MacroID][LaneID][SiteID] = (int)TempResult[SiteID][MacroID][LaneID];
//		    FOREACH_ACTIVESITE_END
//        }
//    }
//
//
//        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
//
//            UINT MacroID = MacroLane_Sel[macroIndex].MacroID; //get macro ID
//            const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane; //get lane count
//
//            for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
//                UINT LaneID = vLane[laneIndex];
//
//                stringstream ss; //int 2 string
//                ss << macroIndex;
//                string strmacroIndex;
//                ss >> strmacroIndex;
//
//                stringstream ss1; //int 2 string
//                ss1 << laneIndex;
//                string strlaneIndex;
//                ss1 >> strlaneIndex;
//                string Macro_Lane_Name = "M" + strmacroIndex + "_L" + strlaneIndex;
//
//
//				TheSoft.Flow().TestLimit(result_MarcoLaneSite[MacroID][LaneID],E_LEFTCLOSE_RIGHTCLOSE);//,testname+"_"+Macro_Lane_Name
//			}
//		}
}

void HiLink_PerLane_Judge(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname, double LimitL, LANE_UINT& TempResult, double LimitH, JUDGE_PIN Judge_Pin) {

	int tempTestNumber=0;
    FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
	tempTestNumber=0;

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

            STRING_VECTOR JudgePins;
            JudgePins.clear();
            ARRAY_D ValueForJudge;
            ValueForJudge.resize(vLane.size());

            for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
                UINT LaneID = vLane[laneIndex];
                switch (Judge_Pin) {
                    case 0: JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_P);
                        break;
                    case 1: JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_N);
                        break;
                    case 2: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);
                        break;
                    case 3: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_N);
                        break;
                    default: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);
                        break;
                }
                ValueForJudge[laneIndex] = double(TempResult[SiteID][MacroID][LaneID]);

                stringstream ss; //int 2 string
                ss << macroIndex;
                string strmacroIndex;
                ss >> strmacroIndex;

                stringstream ss1; //int 2 string
                ss1 << laneIndex;
                string strlaneIndex;
                ss1 >> strlaneIndex;
                string Macro_Lane_Name = "M" + strmacroIndex + "_L" + strlaneIndex;
                judgeAndLog_ParametricTest(SiteID, testname, Macro_Lane_Name, LimitL, ValueForJudge[laneIndex], LimitH,m_TestNumber + tempTestNumber);
                tempTestNumber++;
            }
        }
        FOREACH_ACTIVESITE_END
		m_TestNumber = m_TestNumber + tempTestNumber;

//	vector<vector<SiteInt>> result_MarcoLaneSite;// [marco][lane][site]
//	result_MarcoLaneSite.resize(MacroLane_Sel.size());
//	int siteCount = TheSoft.Sites().Active().GetActiveSiteCount();
//
//
//    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
//        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//        const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//		result_MarcoLaneSite[MacroID].resize(vLane.size());
//        for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
//            UINT LaneID = vLane[laneIndex];
//    		result_MarcoLaneSite[MacroID][LaneID].resize(siteCount);
//
//        	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//				result_MarcoLaneSite[MacroID][LaneID][SiteID] = (int)TempResult[SiteID][MacroID][LaneID];
//		    FOREACH_ACTIVESITE_END
//        }
//    }
//
//
//
//    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
//
//        UINT MacroID = MacroLane_Sel[macroIndex].MacroID; //get macro ID
//        const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane; //get lane count
//
//        for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
//            UINT LaneID = vLane[laneIndex];
//
//            stringstream ss; //int 2 string
//            ss << macroIndex;
//            string strmacroIndex;
//            ss >> strmacroIndex;
//
//            stringstream ss1; //int 2 string
//            ss1 << laneIndex;
//            string strlaneIndex;
//            ss1 >> strlaneIndex;
//            string Macro_Lane_Name = "M" + strmacroIndex + "_L" + strlaneIndex;
//
//
//			TheSoft.Flow().TestLimit(result_MarcoLaneSite[MacroID][LaneID],E_LEFTCLOSE_RIGHTCLOSE);//,testname+"_"+Macro_Lane_Name
//		}
//	}
}

void HiLink_PerMacro_Judge(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname, double LimitL, MACRO_DOUBLE& TempResult, double LimitH, JUDGE_PIN Judge_Pin) {

		int tempTestNumber=0;
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        STRING_VECTOR JudgePins;
        JudgePins.clear();
        ARRAY_D ValueForJudge;

        ValueForJudge.resize(MacroLane_Sel.size());
        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            switch (Judge_Pin) {
                case 0: JudgePins.push_back(LANE_INFO[MacroID][0].RX_P);
                    break;
                case 1: JudgePins.push_back(LANE_INFO[MacroID][0].RX_N);
                    break;
                case 2: JudgePins.push_back(LANE_INFO[MacroID][0].TX_P);
                    break;
                case 3: JudgePins.push_back(LANE_INFO[MacroID][0].TX_N);
                    break;
                default: JudgePins.push_back(LANE_INFO[MacroID][0].TX_P);
                    break;
            }
            ValueForJudge[macroIndex] = TempResult[SiteID][MacroID];

            stringstream ss; //int 2 string
            ss << macroIndex;
            string strmacroIndex;
            ss >> strmacroIndex;
            string Macro_Lane_Name = "M" + strmacroIndex;

            judgeAndLog_ParametricTest(SiteID, testname, Macro_Lane_Name, LimitL, ValueForJudge[macroIndex], LimitH,m_TestNumber + tempTestNumber);
            tempTestNumber++;
        }
        FOREACH_ACTIVESITE_END
		m_TestNumber = m_TestNumber + tempTestNumber;

//	vector<SiteDouble> result_MarcoSite;// [marco][site]
//	result_MarcoSite.resize(MacroLane_Sel.size());
//
//	int siteCount = TheSoft.Sites().Active().GetActiveSiteCount();
//
//    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
//        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//        result_MarcoSite[MacroID].resize(siteCount);
//		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//			result_MarcoSite[MacroID][SiteID] = TempResult[SiteID][MacroID];
//        FOREACH_ACTIVESITE_END
//    }
//
//
//	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
//        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//
//		stringstream ss; //int 2 string
//        ss << macroIndex;
//        string strmacroIndex;
//        ss >> strmacroIndex;
//        string Macro_Lane_Name = "M" + strmacroIndex;
//
//		TheSoft.Flow().TestLimit(result_MarcoSite[MacroID],E_LEFTCLOSE_RIGHTCLOSE);//,testname+"_"+Macro_Lane_Name
//	}


}

void HiLink_PerMacro_Judge(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname, double LimitL, MACRO_INT& TempResult, double LimitH, JUDGE_PIN Judge_Pin) {

    string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();

    STRING testsuiteName;
    if (sTestsuiteName.find("__") != string::npos) {
        testsuiteName = sTestsuiteName.substr(0, sTestsuiteName.find("__"));
    } else {
        testsuiteName = sTestsuiteName;
    }

    	int tempTestNumber=0;
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
    	tempTestNumber=0;

        STRING_VECTOR JudgePins;
        JudgePins.clear();
        ARRAY_D ValueForJudge;
        ValueForJudge.resize(MacroLane_Sel.size());
        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            switch (Judge_Pin) {
                case 0: JudgePins.push_back(LANE_INFO[MacroID][0].RX_P);
                    break;
                case 1: JudgePins.push_back(LANE_INFO[MacroID][0].RX_N);
                    break;
                case 2: JudgePins.push_back(LANE_INFO[MacroID][0].TX_P);
                    break;
                case 3: JudgePins.push_back(LANE_INFO[MacroID][0].TX_N);
                    break;
                default: JudgePins.push_back(LANE_INFO[MacroID][0].TX_P);
                    break;
            }
            ValueForJudge[macroIndex] = double(TempResult[SiteID][MacroID]);
            stringstream ss; //int 2 string
            ss << macroIndex;
            string strmacroIndex;
            ss >> strmacroIndex;
            string Macro_Lane_Name = "M" + strmacroIndex;
            judgeAndLog_ParametricTest(SiteID, testname, Macro_Lane_Name, LimitL, ValueForJudge[macroIndex], LimitH,m_TestNumber + tempTestNumber);
            tempTestNumber++;
        }
        FOREACH_ACTIVESITE_END
		m_TestNumber = m_TestNumber + tempTestNumber;

//	vector<SiteInt> result_MarcoSite;// [marco][site]
//	result_MarcoSite.resize(MacroLane_Sel.size());
//
//	int siteCount = TheSoft.Sites().Active().GetActiveSiteCount();
//
//    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
//        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//        result_MarcoSite[MacroID].resize(siteCount);
//        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//		result_MarcoSite[MacroID][SiteID] = TempResult[SiteID][MacroID];
//	    FOREACH_ACTIVESITE_END
//
//    }
//
//
//	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
//        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//
//		stringstream ss; //int 2 string
//        ss << macroIndex;
//        string strmacroIndex;
//        ss >> strmacroIndex;
//        string Macro_Lane_Name = "M" + strmacroIndex;
//
//		TheSoft.Flow().TestLimit(result_MarcoSite[MacroID],E_LEFTCLOSE_RIGHTCLOSE);//,testname+"_"+Macro_Lane_Name
//	}



}

void HiLink_PerSite_Judge(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname, SITE_DOUBLE& TempResult, JUDGE_PIN Judge_Pin) {
    //	LimitTable_Manager::UpdateLimit(testname);
    //	string sTestsuiteName;
    //	 GET_TESTSUITE_NAME	  (sTestsuiteName);
    //	/***************sub func begin****************/
    //	INT SiteID = CURRENT_SITE_NUMBER() - 1;
    //	STRING	JudgePins;
    //	switch (Judge_Pin)
    //	{
    //		case 0: JudgePins = LANE_INFO[0][0].RX_P;break;
    //		case 1: JudgePins = LANE_INFO[0][0].RX_N;break;
    //		case 2: JudgePins = LANE_INFO[0][0].TX_P;break;
    //		case 3: JudgePins = LANE_INFO[0][0].TX_N;break;
    //		default: JudgePins = LANE_INFO[0][0].TX_P;break;
    //	}
    //	DOUBLE		ValueForJudge = TempResult[SiteID];
    //
    //	TestSet.testsuite(sTestsuiteName).cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, testname, tmLimits, ValueForJudge);
    //	TestSet.testsuite_default();
    //	/***************sub func end****************/
}


SITE_INT H30_FailBin_Flag;
int m_TestNumber = -999;
int m_HardBin = -999;
int m_SoftBin = -999;

void judgeAndLog_ParametricTest(INT SiteID, string testname, string Macro_Lane_Name, double LimitL, double TestVal, double LimitH,int testNumber) {

    int Fail_flag = 0;
    if (TestVal < LimitL || TestVal > LimitH) {
        Fail_flag = 1;
        H30_FailBin_Flag[SiteID] = 1;
//        api->Set_result_bin(6271);//add by tony 20210607
    }

    string Result = "Pass";
    if (Fail_flag == 1) {
        Result = "Fail";
    }
///tony 20210525
//	void TestLimit(const string pinname,int site,double siteResultVal,double llimit,double hlimit,unsigned int failhbin,unsigned int failsbin,
//		       string unit,string limitname,unsigned int testnum,PhxAPI::JudgeTpye_E judgetype = PhxAPI::E_Fail,PhxAPI::TestLimitCompare_E limitrule = PhxAPI::E_LEFTOPEN_RIGHTCLOSE);//One pin,one result(double),select one site

//    TheSoft.Flow().TestLimit(testname,SiteID,TestVal,LimitL,LimitH,m_HardBin,m_SoftBin,"","\t\t\t"+Macro_Lane_Name,testNumber,E_Fail,E_LEFTCLOSE_RIGHTCLOSE);
    TheSoft.Flow().TestLimit(Macro_Lane_Name,SiteID,TestVal,LimitL,LimitH,m_HardBin,m_SoftBin,"","\t"+testname,testNumber,E_Fail,E_LEFTCLOSE_RIGHTCLOSE);
//    printf("%-12d %-3d %-6s %-45s %-10s %-18f %-18f %-18f\n", m_TestNumber, SiteID, Result.c_str(), testname.c_str(), Macro_Lane_Name.c_str(), LimitL, TestVal, LimitH);
//    printf("%-12d %-3d %-6s %-45s %-10s %-18f %-18f %-18f\n", m_TestNumber, SiteID, Result.c_str(), testname.c_str(), Macro_Lane_Name.c_str(), LimitL, TestVal, LimitH);

//init code    
    //printf("%-12d %-5d %-10s %-30s %-30s %-20f %-20f %-20f\n", testNumber, SiteID, Result.c_str(), testname.c_str(), Macro_Lane_Name.c_str(), LimitL, TestVal, LimitH);
//    api->Datalog_ascii_print("%-12d %-5d %-10s %-30s %-30s %-20f %-20f %-20f", m_TestNumber, SiteID, Result.c_str(), testname.c_str(), Macro_Lane_Name.c_str(), LimitL, TestVal, LimitH);
    //    api->Datalog_STDF_parametric_test("%-12d %-5d %-10s %-30s %-30s %-20f %-20f %-20f",m_TestNumber,SiteID,Result.c_str(),testname.c_str(),Macro_Lane_Name.c_str(), LimitL, TestVal, LimitH);
//    m_TestNumber++;
}

void judgeAndLog_ParametricTest_DC(INT SiteID, string testname, string Macro_Lane_Name, double LimitL, double TestVal, double LimitH) {

    int Fail_flag = 0;
    if (TestVal < LimitL || TestVal > LimitH) {
        Fail_flag = 1;
        H30_FailBin_Flag = 1;
    }

    string Result = "Pass";
    if (Fail_flag == 1) {
        Result = "Fail";
    }
///tony 20210525
    printf("%-12d %-3d %-6s %-45s %-10s %-18f %-18f %-18f\n", m_TestNumber, SiteID, Result.c_str(), testname.c_str(), Macro_Lane_Name.c_str(), LimitL, TestVal, LimitH);
//init code    
//    printf("%-12d %-5d %-10s %-30s %-30s %-20f %-20f %-20f", m_TestNumber, SiteID, Result.c_str(), testname.c_str(), Macro_Lane_Name.c_str(), LimitL, TestVal, LimitH);
//    api->Datalog_ascii_print("%-12d %-5d %-10s %-30s %-30s %-20f %-20f %-20f", m_TestNumber, SiteID, Result.c_str(), testname.c_str(), Macro_Lane_Name.c_str(), LimitL, TestVal, LimitH);
    //    api->Datalog_STDF_parametric_test("%-12d %-5d %-10s %-30s %-30s %-20f %-20f %-20f",m_TestNumber,SiteID,Result.c_str(),testname.c_str(),Macro_Lane_Name.c_str(), LimitL, TestVal, LimitH);
    m_TestNumber++;
}

void get_pinlists(const MACRO_LANE_SEL& MacroLane_Sel, STRING& sPinList_P, STRING& sPinList_N, STRING& sPinList, STRING PinType) {
    sPinList_P = "";
    sPinList_N = "";
    bool IsFirst = true;
    for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
        UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
        const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

        for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
            UINT LaneID = vLane[laneIndex];
            if (!IsFirst) {
                sPinList_P += ",";
                sPinList_N += ",";
            }
            IsFirst = false;
            if (PinType == "RX") {
                sPinList_P += LANE_INFO[MacroID][LaneID].RX_P;
                sPinList_N += LANE_INFO[MacroID][LaneID].RX_N;
            } else {//if (PinType == "TX")
                sPinList_P += LANE_INFO[MacroID][LaneID].TX_P;
                sPinList_N += LANE_INFO[MacroID][LaneID].TX_N;
            }
        }
    }

    sPinList = sPinList_P + "," + sPinList_N;
}

bool Update_LaneData_InTolerance(const MACRO_LANE_SEL& MacroLane_Sel, const DOUBLE& SpecValue, LANE_DOUBLE& ErrorCount, LANE_DOUBLE& TempResult, LANE_INT& FindFlag) {
    INT iFindAll = 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
            for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
                UINT LaneID = vLane[laneIndex];
                if (ErrorCount[SiteID][MacroID][LaneID] == 0 && FindFlag[SiteID][MacroID][LaneID] == 0) {
                    TempResult[SiteID][MacroID][LaneID] = SpecValue;
                    iFindAll = 0;
                } else {
                    FindFlag[SiteID][MacroID][LaneID] = 1;
                }
            }
        }
        FOREACH_ACTIVESITE_END
    return iFindAll;
}

bool Update_LaneData_InTolerance(const MACRO_LANE_SEL& MacroLane_Sel, const INT& SpecValue, LANE_DOUBLE& ErrorCount, LANE_DOUBLE& TempResult, LANE_INT& FindFlag) {
    INT iFindAll = 1;

//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
            const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
            for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
                UINT LaneID = vLane[laneIndex];
                if (ErrorCount[SiteID][MacroID][LaneID] == 0 && FindFlag[SiteID][MacroID][LaneID] == 0) {
                    TempResult[SiteID][MacroID][LaneID] = SpecValue;
                    iFindAll = 0;
                } else {
                    FindFlag[SiteID][MacroID][LaneID] = 1;
                }
            }
        }
        FOREACH_ACTIVESITE_END
    return iFindAll;
}

void SetTestBin() {
    int FailBinNum;
//
//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
//        if (api->Get_result_bin_status() == BIN_PASS) {
//            if (H30_FailBin_Flag[SiteID] == 0) {
//                api->Set_result_bin(1);
//            } else {
//                const char * node_name = api->Get_current_node_name(); //must click "execute node xxxx" or run flow start 
//                string strnode_name = node_name;
////                string strnode_name = string(api->Get_current_node_name());//modify by tony 20210520
//                //last 4 chars
//                string node_fail_bin = strnode_name.substr(strnode_name.length() - 4, strnode_name.length());
//                //string To INT
//                FailBinNum = atoi(node_fail_bin.c_str());
////                api->Set_result_bin(FailBinNum); // //masked by tony 20210607
//                api->Set_result_bin(1); // //masked by tony 20210607
//            }
//        } else {
//            const char * node_name = api->Get_current_node_name();
//            string strnode_name = node_name;
////            string strnode_name = string(api->Get_current_node_name());//modify by tony 20210520
//
//            //last 4 chars
//            string node_fail_bin = strnode_name.substr(strnode_name.length() - 4, strnode_name.length());
//            //string To INT
//            FailBinNum = atoi(node_fail_bin.c_str());
////            api->Set_result_bin(FailBinNum); // //masked by tony 20210607
//                api->Set_result_bin(1); // //masked by tony 20210607            
//        }
//
//        //        Get_test_result(api);		
//    }
    
    
//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();    
//            if (H30_FailBin_Flag[SiteID] == 0) {
//                api->Set_result_bin(1);
//            } else {
//                const char * node_name = api->Get_current_node_name(); //must click "execute node xxxx" or run flow start 
//                string strnode_name = node_name;
////                string strnode_name = string(api->Get_current_node_name());//modify by tony 20210520
//                //last 4 chars
//                string node_fail_bin = strnode_name.substr(strnode_name.length() - 4, strnode_name.length());
//                //string To INT
//                FailBinNum = atoi(node_fail_bin.c_str());
//                api->Set_result_bin(FailBinNum); // //masked by tony 20210607
//                H30_FailBin_Flag[SiteID] = 0;
//            }    
//    }
}
