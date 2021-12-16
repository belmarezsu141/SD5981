#include <H30LR_TestSuite_Para.h>

#include <iostream>
#include "string.h"


//stLoadJAMSetup d2s_JAM_setup_122M88_On_LoadJAMSetup = {
//    string(""),
//    string(""),
//    string(""),
//    string(""),
//    string(""),
//    string(""),
//    string("ON")
//};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDN_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_Download_FW H30_Download_FW_VDDN_HILINK_Download_FW = {
    string("0,1"),
    0,
    0,
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDN_4_HILINK_FW_CAL = {//5.6
    string("0,1"),
    string("SS+CS"),
    string("FullCal"),
    string("NoAdpt"),
    string("External"),
    -1,// init as 0 by tony 20210608
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    3,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stSSBandGap SSbandGap_SSBandGap = {
    3
};

stExt_2K_Resistor_Check External_2K_Ext_2K_Resistor_Check = {
    3
};

stDPM_TEST_BY_FW H30_DPM_TEST_BY_FW_DPM_TEST_BY_FW = {
    string("0,1"),
    string("ReadBack_InternalSpec_TMJudge"),
    122.88,
    122.88,
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDN_1_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"), // test name , note by tony 20210517
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_Download_FW H30_Download_FW_VDDN_1_HILINK_Download_FW = {
    string("0,1"),
    0,
    0,
    3
};


stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_PLL1_1016_1_1_6_3_REF1_VDDN_1_HILINK_FW_CAL = {
    string("0,1"), //macro
    string("SS+CS+DS"), //cal type
    string("FullCal"), //FULL Cal & Bypass cal
    string("NoAdpt"), //ada_1016
    string("External"), //还回模式
    -1, //_PLL0_PLL1
    122.88, //122M88_
    122.88, //122M88_
    0, //_Refclk0
    1, //_1
    1, //_1
    string("0"), //full
    1, //_11
    1, //_11
    12.16512, //_24G33024
    3, //99
    33, //99
    6, //_6
    3, //_3
    0, //始终为0
    10, //_1016
    16, //_1016
    string("0"), //始终为0
    3////始终为3
};




stHILINK_Download_FW H30_Download_FW_VDDN_2_HILINK_Download_FW = {
    string("0,1"),
    0,
    2,
    3
};

stHILINK_FW_ADAPTATION H30_FW_ADPT_122M88_24G33024_1199full40_Refclk0_PLL0_PLL1_1016_1_1_6_3_REF1_VDDN_HILINK_FW_ADAPTATION = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("FullAdpt"),
    string("External"),
    -1,
    122.88,
    122.88,
    0,
    3
};

stHILINK_Download_FW H30_Download_FW_VDDN_3_HILINK_Download_FW = {
    string("0,1"),
    0,
    1,
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDH_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stMIN_MAX_PWR H30_MIN_PWR_VDDH_MIN_MAX_PWR = {
    string("0,1"),
    0,
    string("MIN_PWR"),
    string("HVCC12"),
    string("LVCC08"),
    string("HVCC12"),
    string("LVCC08"),
    string(""),
    string(""),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDN_2_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stRxSigResBefCal_IFVM H30_RxSigResBefCal_VDDN_RxSigResBefCal_IFVM = {
    string("0,1"),
    -5,
    -1,
    3
};

stRxDiffResBefCal_VFIM H30_RxdiffResBefCal_VDDN_RxDiffResBefCal_VFIM = {
    string("0,1"),
    500,
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDH_1_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDH_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    3,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stMIN_MAX_PWR H30_MAX_PWR_VDDH_MIN_MAX_PWR = {
    string("0,1"),
    0,
    string("MAX_PWR"),
    string("HVCC12"),
    string("LVCC08"),
    string("HVCC12"),
    string("LVCC08"),
    string("External"),
    string(""),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDN_3_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDN_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    3,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stRxResAftCal_VFIM H30_RxSigResAftCal_VDDN_RxResAftCal_VFIM = {
    string("0,1"),
    500,
    50,
    string("Sig"),
    3
};

stRxResAftCal_VFIM H30_RxDiffResAftCal_VDDN_RxResAftCal_VFIM = {
    string("0,1"),
    500,
    50,
    string("Diff"),
    3
};

stRxTermVoltToGnd_AC H30_RxTermVoltToGnd_AC_RxTermVoltToGnd_AC = {
    string("0,1"),
    string("ALL0"),
    0,
    3
};

stTxResAftCal H30_TxSigResAftCal_All0_VDDN_TxResAftCal = {
    string("0,1"),
    string("ALL0"),
    -3,
    -4,
    3
};

stTxResAftCal H30_TxSigResAftCal_All1_VDDN_TxResAftCal = {
    string("0,1"),
    string("ALL1"),
    -3,
    -4,
    3
};

stTxTermVolt H30_TxTermVolt_All0_VDDN_TxTermVolt = {
    string("0,1"),
    string("External"),
    string("ALL0"),
    0,
    -0.1,
    3
};

stTxTermVolt H30_TxTermVolt_All1_VDDN_TxTermVolt = {
    string("0,1"),
    string("External"),
    string("ALL0"),
    1,
    -0.1,
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDN_4_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDN_1_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    3,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stTxFIR_DC H30_TxFIR_DC_MAIN_ALL0_VDDN_TxFIR_DC = {
    string("0,1"),
    string("MAIN"),
    string("ALL0"),
    0,
    3
};

stTxFIR_DC H30_TxFIR_DC_MAIN_ALL1_VDDN_TxFIR_DC = {
    string("0,1"),
    string("MAIN"),
    string("ALL1"),
    0,
    3
};

stTxFIR_DC H30_TxFIR_DC_PRE1_ALL0_VDDN_TxFIR_DC = {
    string("0,1"),
    string("PRE1ST"),
    string("ALL0"),
    0,
    3
};

stTxFIR_DC H30_TxFIR_DC_PRE1_ALL1_VDDN_TxFIR_DC = {
    string("0,1"),
    string("PRE1ST"),
    string("ALL1"),
    0,
    3
};

stTxFIR_DC H30_TxFIR_DC_PRE2_ALL0_VDDN_TxFIR_DC = {
    string("0,1"),
    string("PRE2ND"),
    string("ALL0"),
    0,
    3
};

stTxFIR_DC H30_TxFIR_DC_PRE2_ALL1_VDDN_TxFIR_DC = {
    string("0,1"),
    string("PRE2ND"),
    string("ALL1"),
    0,
    3
};

stTxFIR_DC H30_TxFIR_DC_POST1_ALL0_VDDN_TxFIR_DC = {
    string("0,1"),
    string("POST1ST"),
    string("ALL0"),
    0,
    3
};

stTxFIR_DC H30_TxFIR_DC_POST1_ALL1_VDDN_TxFIR_DC = {
    string("0,1"),
    string("POST1ST"),
    string("ALL1"),
    0,
    3
};

//stLoadJAMSetup d2s_JAM_setup_156M25_On_LoadJAMSetup = {
//    string(""),
//    string(""),
//    string(""),
//    string(""),
//    string(""),
//    string(""),
//    string("ON")
//};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDH_2_HiLink30_PowerUp_Reset = {//4.27
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF2_Case02"),
    string(""),
    3
};

stVcoLockRange H30_VCOLockRange_Refclk0_ABIST_VDDH_VcoLockRange = {//4.27
    string("0,1"),
    -1,
    0,
    3
};




stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF2_Case02"), //4.27
    string(""),
    3
};

stVcoLockRange H30_VCOLockRange_Refclk0_ABIST_VDDL_VcoLockRange = {//4.27
    string("0,1"),
    -1,
    0,
    3
};


//stLoadJAMSetup d2s_JAM_setup_156M25_Off_LoadJAMSetup = {
//    string(""),
//    string(""),
//    string(""),
//    string(""),
//    string(""),
//    string(""),
//    string("ON")
//};
stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDN_16_HiLink30_PowerUp_Reset = {//4.28
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF2_Case02"),
    string(""),
    3
};




stRefclkLockRange H30LR_RefclkLockRange_PLL0_PLL1_Refclk0_M0x3_VDDN = {//4.27
    string("0,1"),
    -1,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string("BYPASS"),
    string("BYPASS"),
    string("BYPASS"),
    string("BYPASS"),
    string("BYPASS"),
    string("BYPASS"),
    3
};

//stLoadJAMSetup d2s_JAM_setup_122M88_On_1_LoadJAMSetup = {
//    string(""),
//    string(""),
//    string(""),
//    string(""),
//    string(""),
//    string(""),
//    string("ON")
//};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDN_5_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_14G7456_1P5160full40_Refclk0_PLL0_1016_1_1_5_4_REF1_VDDN_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("NoAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1.5,
    1,
    7.3728,
    2,
    30,
    5,
    4,
    0,
    10,
    16,
    string("0"),
    3
};

stClkPurity_ABIST H30_ClkPurity_Refclk0_PLL0_Fmin_VDDN_ClkPurity_ABIST = {
    string("0,1"),
    string("External"),
    122.88,
    122.88,  
    57,
    -6,
    0,
    0,
    0,
    14.7456,
    0,
    string("YES"),
    7,
    7,
    7,
    0,
    0,
    0,
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDN_6_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
}; //122.88

stHILINK_FW_CAL H30_FW_CAL_122M88_19G6608_1P5180full40_Refclk0_PLL0_2010_1_1_7_6_REF1_VDDN_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("NoAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1.5,
    1,
    9.8304,
    2,
    40,
    7,
    6,
    1,
    20,
    10,
    string("0"),
    3
};

stClkPurity_ABIST H30_ClkPurity_Refclk0_PLL0_Fmax_VDDN_ClkPurity_ABIST = {
    string("0,1"),
    string("External"),
    122.88,
    122.88,
    57,
    -6,
    0,
    0,
    0,
    19.6608,
    0,
    string("YES"),
    7,
    7,
    7,
    0,
    0,
    0,
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDN_7_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL1_1016_1_1_20_13_REF1_VDDN_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("NoAdpt"),
    string("External"),
    1,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    1,
    99,
    20,
    13,
    0,
    10,
    16,
    string("0"),
    3
};

stClkPurity_ABIST H30_ClkPurity_Refclk0_PLL1_Fmin_VDDN_ClkPurity_ABIST = {//4.27
    string("0,1"),
    string("External"),
    122.88,
    122.88,
    57,
    -6,
    0,
    0,
    0,
    24.33024,
    0,
    string("YES"),
    7,
    7,
    7,
    0,
    0,
    0,
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDN_8_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_19G6608_1P5180full40_Refclk0_PLL1_1016_1_1_7_6_REF1_VDDN_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("NoAdpt"),
    string("External"),
    1,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1.5,
    1,
    9.8304,
    2,
    40,
    7,
    6,
    0,
    10,
    16,
    string("0"),
    3
};

stClkPurity_ABIST H30_ClkPurity_Refclk0_PLL1_Fmax_VDDN_ClkPurity_ABIST = {//4.27
    string("0,1"),
    string("External"),
    122.88,
    122.88,
    57,
    -6,
    0,
    0,
    0,
    19.6608,
    0,
    string("YES"),
    7,
    7,
    7,
    0,
    0,
    0,
    3
};

//stLoadJAMSetup d2s_JAM_setup_122M88_On_2_LoadJAMSetup = {
//    string(""),
//    string(""),
//    string(""),
//    string(""),
//    string(""),
//    string(""),
//    string("ON")
//};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_1_HiLink30_PowerUp_Reset = {//4.27
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF2_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_9G8304_1P5280full40_Refclk0_PLL0_1010_1_1_7_6_REF1_VDDL_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1.5,
    2,
    4.9152,
    2,
    40,
    7,
    6,
    0,
    10,
    10,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_9G8304_1P5280full40_Refclk0_PLL0_1010_1_1_7_6_REF1_VDDL_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_2_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_9G8304_1P5180half20_Refclk0_PLL0_2010_1_1_7_6_REF1_VDDL_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("1"),
    1.5,
    1,
    9.8304,
    2,
    40,
    7,
    6,
    1,
    20,
    10,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_9G8304_1P5180half20_Refclk0_PLL0_2010_1_1_7_6_REF1_VDDL_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    1,
    0,
    100,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_3_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_9G8304_1P5280full40_Refclk0_PLL1_1016_1_1_7_6_REF1_VDDL_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    1,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1.5,
    2,
    4.9152,
    2,
    40,
    7,
    6,
    0,
    10,
    16,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_9G8304_1P5280full40_Refclk0_PLL1_1016_1_1_7_6_REF1_VDDL_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_4_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_9G8304_1P5180half20_Refclk0_PLL1_1016_1_1_7_6_REF1_VDDL_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    1,
    122.88,
    122.88,
    0,
    1,
    1,
    string("1"),
    1.5,
    1,
    9.8304,
    2,
    40,
    7,
    6,
    0,
    10,
    16,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_9G8304_1P5180half20_Refclk0_PLL1_1016_1_1_7_6_REF1_VDDL_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    1,
    0,
    100,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_5_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_14G7456_1P5160full40_Refclk0_PLL0_1016_1_1_5_4_REF1_VDDL_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1.5,
    1,
    7.3728,
    2,
    30,
    5,
    4,
    0,
    10,
    16,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_14G7456_1P5160full40_Refclk0_PLL0_1016_1_1_5_4_REF1_VDDL_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_6_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_14G7456_2160full40_Refclk0_PLL1_1016_1_1_5_4_REF1_VDDL_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    1,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    2,
    1,
    7.3728,
    2,
    30,
    5,
    4,
    0,
    10,
    16,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_14G7456_2160full40_Refclk0_PLL1_1016_1_1_5_4_REF1_VDDL_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_7_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_16G22016_1P5166full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDL_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1.5,
    1,
    8.11008,
    2,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_16G22016_1P5166full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDL_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_8_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_16G22016_1P5166full40_Refclk0_PLL1_1016_1_1_6_3_REF1_VDDL_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    1,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1.5,
    1,
    8.11008,
    2,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_16G22016_1P5166full40_Refclk0_PLL1_1016_1_1_6_3_REF1_VDDL_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_9_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDL_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    3,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_24G33024_1199full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDL_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_10_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL1_1016_1_1_20_13_REF1_VDDL_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    1,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    1,
    99,
    20,
    13,
    0,
    10,
    16,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_24G33024_1199full40_Refclk0_PLL1_1016_1_1_20_13_REF1_VDDL_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};

stLoadJAMSetup d2s_JAM_setup_122M88_On_3_LoadJAMSetup = {
    string(""),
    string(""),
    string(""),
    string(""),
    string(""),
    string(""),
    string("ON")
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDH_3_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_9G8304_1P5280full40_Refclk0_PLL0_1010_1_1_7_6_REF1_VDDH_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1.5,
    2,
    4.9152,
    2,
    40,
    7,
    6,
    0,
    10,
    10,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_9G8304_1P5280full40_Refclk0_PLL0_1010_1_1_7_6_REF1_VDDH_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDH_4_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_9G8304_1P5180half20_Refclk0_PLL0_2010_1_1_7_6_REF1_VDDH_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("1"),
    1.5,
    1,
    9.8304,
    2,
    40,
    7,
    6,
    1,
    20,
    10,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_9G8304_1P5180half20_Refclk0_PLL0_2010_1_1_7_6_REF1_VDDH_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    1,
    0,
    100,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDH_5_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_9G8304_1P5280full40_Refclk0_PLL1_1016_1_1_7_6_REF1_VDDH_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    1,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1.5,
    2,
    4.9152,
    2,
    40,
    7,
    6,
    0,
    10,
    16,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_9G8304_1P5280full40_Refclk0_PLL1_1016_1_1_7_6_REF1_VDDH_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDH_6_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_9G8304_1P5180half20_Refclk0_PLL1_1016_1_1_7_6_REF1_VDDH_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    1,
    122.88,
    122.88,
    0,
    1,
    1,
    string("1"),
    1.5,
    1,
    9.8304,
    2,
    40,
    7,
    6,
    0,
    10,
    16,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_9G8304_1P5180half20_Refclk0_PLL1_1016_1_1_7_6_REF1_VDDH_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    1,
    0,
    100,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDH_7_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_14G7456_1P5160full40_Refclk0_PLL0_1016_1_1_5_4_REF1_VDDH_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1.5,
    1,
    7.3728,
    2,
    30,
    5,
    4,
    0,
    10,
    16,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_14G7456_1P5160full40_Refclk0_PLL0_1016_1_1_5_4_REF1_VDDH_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDH_8_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_14G7456_2160full40_Refclk0_PLL1_1016_1_1_5_4_REF1_VDDH_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    1,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    2,
    1,
    7.3728,
    2,
    30,
    5,
    4,
    0,
    10,
    16,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_14G7456_2160full40_Refclk0_PLL1_1016_1_1_5_4_REF1_VDDH_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDH_9_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_16G22016_1P5166full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDH_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1.5,
    1,
    8.11008,
    2,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_16G22016_1P5166full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDH_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDH_10_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_16G22016_1P5166full40_Refclk0_PLL1_1016_1_1_6_3_REF1_VDDH_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    1,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1.5,
    1,
    8.11008,
    2,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_16G22016_1P5166full40_Refclk0_PLL1_1016_1_1_6_3_REF1_VDDH_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDH_11_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDH_1_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    3,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_24G33024_1199full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDH_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDH_12_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL1_1016_1_1_20_13_REF1_VDDH_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    1,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    1,
    99,
    20,
    13,
    0,
    10,
    16,
    string("0"),
    3
};

stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_122M88_24G33024_1199full40_Refclk0_PLL1_1016_1_1_20_13_REF1_VDDH_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};
stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_156M25_9G6875_1p5262full40_Refclk0_PLL0_0108_1_1_12_8_REF2_RxAC_M0x3_VDDH_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};


stLoadJAMSetup d2s_JAM_setup_122M88_On_4_LoadJAMSetup = {
    string(""),
    string(""),
    string(""),
    string(""),
    string(""),
    string(""),
    string("ON")
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDN_9_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDN_2_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    3,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stTxEScopePrbs15_ABIST H30_TxEScopePrbs15_24G33024_ABIST_TxEScopePrbs15_ABIST = {
    string("0,1"),
    string("External"),
    122.88,
    122.88,
    57,
    -6,
    0,
    0,
    0,
    24.33024,
//    14.7456,
    string("NO"),
    string("NO"),
    string("PRBS15"),
    string("FW"),
    3
};

stRxSensitivity_ABIST H30_RxSensitivity_24G33024_ABIST_RxSensitivity_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    string("NO"),
    0,
    3,
    3
};

stRxJitterTol_ABIST H30_RxJitterTol_30G_ABIST_RxJitterTol_ABIST = {  //5875  add by tony 20210519
    string("0,1,2,3,4,5"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    30,
    string("NO"),
    3
};

stRxJitterTol_ABIST H30_RxJitterTol_24G33024_ABIST_RxJitterTol_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    24.33024,
    string("NO"),
    3
};

stRxFreqOffsetTol_ABIST H30_RxFreqOffsetTol_24G33024_ABIST_RxFreqOffsetTol_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    string("NO"),
    3
};

stRxALOS_ABIST H30_RxALOS_24G33024_ABIST_RxALOS_ABIST = {
    string("0,1"),
    string("External"),
    24,
    0,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDN_10_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDN_3_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("NoAdpt"),
    string("PreDriver"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    3,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stFuncBertPrbs15_ABIST H30_FuncBertPrbs_122M88_24G33024_1199full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDN_FuncBertPrbs15_ABIST = {
    string("0,1"),
    string("PreDriver"),
    57,
    -6,
    0,
    0,
    0,
    3
};

stLoadJAMSetup d2s_JAM_setup_122M88_On_5_LoadJAMSetup = {
    string(""),
    string(""),
    string(""),
    string(""),
    string(""),
    string(""),
    string("ON")
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDN_11_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_9G8304_1P5280full40_Refclk0_PLL0_1010_1_1_7_6_REF1_VDDN_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("NoAdpt"),
    string("Bump"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1.5,
    2,
    4.9152,
    2,
    40,
    7,
    6,
    0,
    10,
    10,
    string("0"),
    3
};

stFuncBertPrbs15_ABIST H30_FuncBertPrbs_122M88_9G8304_1P5280full40_Refclk0_PLL0_1010_1_1_7_6_REF1_VDDN_FuncBertPrbs15_ABIST = {
    string("0,1"),
    string("Bump"),
    57,
    -6,
    0,
    0,
    0,
    3
};


stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDH_17_HiLink30_PowerUp_Reset = {//4.28
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF2_Case02"),
    string(""),
    3
};
//stHILINK_FW_CAL H30_FW_CAL_122M88_9G8304_1P5280full40_Refclk0_PLL0_1010_1_1_7_6_REF1_VDDN_HILINK_FW_CAL = {

stHILINK_FW_CAL H30_FW_CAL_156M25_9G6875_1p5262full40_Refclk0_PLL0_0108_1_1_12_8_REF2_RxAC_M0x3_VDDH_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("NoAdpt"),
    string("External"),
    0,
    156.25,
    156.25,
    0,
    1,
    1,
    string("0"),
    1.5,
    2,
    4.84375,
    1,
    62,
    12,
    8,
    0,
    1,
    8,
    string("0"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDH_18_HiLink30_PowerUp_Reset = {//4.28
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF2_Case02"),
    string(""),
    3
};
stHILINK_FW_CAL H30_FW_CAL_156M25_9G6875_1p5262full40_Refclk0_PLL1_0108_1_1_12_8_REF2_RxAC_M0x3_VDDH_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("NoAdpt"),
    string("External"),
    1,
    156.25,
    156.25,
    0,
    1,
    1,
    string("0"),
    1.5,
    2,
    4.84375,
    1,
    62,
    12,
    8,
    0,
    1,
    8,
    string("0"),
    3
};


stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_156M25_9G6875_1p5262full40_Refclk0_PLL1_0108_1_1_12_8_REF2_RxAC_M0x3_VDDH_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3

};
stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_19_HiLink30_PowerUp_Reset = {//4.28
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF2_Case02"),
    string(""),
    3
};
stHILINK_FW_CAL H30_FW_CAL_156M25_9G6875_1p5262full40_Refclk0_PLL0_0108_1_1_12_8_REF2_RxAC_M0x3_VDDL_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("NoAdpt"),
    string("External"),
    0,
    156.25,
    156.25,
    0,
    1,
    1,
    string("0"),
    1.5,
    2,
    4.84375,
    1,
    62,
    12,
    8,
    0,
    1,
    8,
    string("0"),
    3
};


stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_156M25_9G6875_1p5262full40_Refclk0_PLL0_0108_1_1_12_8_REF2_RxAC_M0x3_VDDL_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};


stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_156M25_9G6875_1p52162full40_Refclk0_PLL1_0108_1_1_12_8_REF2_RxAC_M0x3_VDDL_TxRxBertPrbs15_ABIST = {
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};


stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_20_HiLink30_PowerUp_Reset = {//4.28
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF2_Case02"),
    string(""),
    3
};
stHILINK_FW_CAL H30_FW_CAL_156M25_9G6875_1p5262full40_Refclk0_PLL1_0108_1_1_12_8_REF2_RxAC_M0x3_VDDL_HILINK_FW_CAL = {//4.28
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("NoAdpt"),
    string("External"),
    1,
    156.25,
    156.25,
    0,
    1,
    1,
    string("0"),
    1.5,
    2,
    4.84375,
    1,
    62,
    12,
    8,
    0,
    1,
    8,
    string("0"),
    3
};
stTxRxBertPrbs15_ABIST H30_TxRxBertPrbs_156M25_9G6875_1p5262full40_Refclk0_PLL1_0108_1_1_12_8_REF2_RxAC_M0x3_VDDL_TxRxBertPrbs15_ABIST = {//4.28
    string("0,1"),
    string("External"),
    57,
    -6,
    0,
    0,
    0,
    0,
    0,
    100,
    string("NO"),
    3
};
stLoadJAMSetup d2s_JAM_setup_122M88_On_6_LoadJAMSetup = {
    string(""),
    string(""),
    string(""),
    string(""),
    string(""),
    string(""),
    string("ON")
};
stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_11_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDL_1_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    3,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stEyeMonitorCheckPrbs31_ABIST H30_EyeMonitorCheckPrbs31_24G33024_ABIST_EyeMonitorCheckPrbs31_ABIST = {
    string("0,1"),
    string("External"),
    122.88,
    122.88,
    24.33024,
    57,
    0,
    0,
    -6,
    0,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_12_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_12G16512_1199half20_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDL_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("1"),
    1,
    1,
    12.16512,
    3,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stEyeMonitorCheckPrbs31_ABIST H30_EyeMonitorCheckPrbs31_12G16512_ABIST_EyeMonitorCheckPrbs31_ABIST = {
    string("0,1"),
    string("External"),
    122.88,
    122.88,
    12.16512,
    57,
    0,
    0,
    -6,
    0,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_13_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_6G08256_1199quar20_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDL_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("2"),
    1,
    1,
    12.16512,
    3,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stEyeMonitorCheckPrbs31_ABIST H30_EyeMonitorCheckPrbs31_6G08256_ABIST_EyeMonitorCheckPrbs31_ABIST = {
    string("0,1"),
    string("External"),
    122.88,
    122.88,
    6.08256,
    57,
    0,
    0,
    -6,
    0,
    string("NO"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDH_13_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDH_2_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    3,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stRxStressAll_ABIST H30_RxStrsAll_24G33024_ABIST_VDDH_RxStressAll_ABIST = {
    string("0,1"),
    string("External"),
    122.88,
    122.88,
    35,
    -6,
    0,
    0,
    0,
    24.33024,
    string("NO"),
    100,
    0.09375,
    0,
    0,
    string("NO"),
    string("FW"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_14_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDL_2_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    3,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stRxStressAll_ABIST H30_RxStrsAll_24G33024_ABIST_VDDL_RxStressAll_ABIST = {
    string("0,1"),
    string("External"),
    122.88,
    122.88,
    35,
    -6,
    0,
    0,
    0,
    24.33024,
    string("NO"),
    100,
    0.09375,
    0,
    0,
    string("NO"),
    string("FW"),
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDH_14_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDH_3_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    3,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stAVS_Verify_ABIST H30_AVS_Verify_24G33024_ABIST_VDDH_AVS_Verify_ABIST = {
    string(""),
    string("External"),
    string("0,1"),
    string("High2Low"),
    57,
    -6,
    0,
    0,
    0,
    string("NO"),
    0.71375,
    0.88625,
    0.00625,
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_15_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_1016_1_1_6_3_REF1_VDDL_3_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("BypassCal"),
    string("BypassAdpt"),
    string("External"),
    0,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    3,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stAVS_Verify_ABIST H30_AVS_Verify_24G33024_ABIST_VDDL_AVS_Verify_ABIST = {
    string(""),
    string("External"),
    string("0,1"),
    string("Low2High"),
    57,
    -6,
    0,
    0,
    0,
    string("NO"),
    0.71375,
    0.88625,
    0.00625,
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_16_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_Download_FW H30_Download_FW_VDDL_HILINK_Download_FW = {
    string("0,1"),
    0,
    0,
    3
};

stCTLE CTLE_A_CTLE = {
    string("0,1"),
    string("YES"),
    7,
    7,
    7,
    7,
    7,
    7,
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_PLL1_1016_1_1_20_13_REF1_VDDL_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("FullCal_FWABIST_USE"),
    string("NoAdpt"),
    string("External"),
    -1,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    3,
    33,
    20, //4.27
    13, //4.27
    0,
    10,
    16,
    string("0"),
    3
};

stFWABIST_ATB H30_Atb_VDDL_FWABIST_ATB = {
    string("0,1"),
//    string("UseExternalSpec_FW_Judge"),
    string("BothMethod"),
    122.88,
    122.88,
    3
};

stDcGain H30_DcGain_DcGain = {
    string("0,1"),
//    string("UseExternalSpec_FW_Judge"),
    string("BothMethod"),
    122.88,
    122.88,
    3
};

stAlphagen H30_Alphagen_Alphagen = {
    string("0,1"),
//    string("UseExternalSpec_FW_Judge"),
    string("BothMethod"),
    122.88,
    122.88,
    3
};

stRegulator H30_Regulator_Regulator = {
    string("0,1"),
//    string("UseExternalSpec_FW_Judge"),
    string("BothMethod"),
    122.88,
    122.88,
    3
};

stFWABIST_AdcStability H30_ADCstability_FWABIST_AdcStability = {
    string("0,1"),
//    string("UseExternalSpec_FW_Judge"),
    string("BothMethod"),
    122.88,
    122.88,
    3
};

stFWABIST_Comparator H30_Comparator_FWABIST_Comparator = {
    string("0,1"),
//    string("UseExternalSpec_FW_Judge"),
    string("BothMethod"),
    122.88,
    122.88,
    3
};

stFWABIST_DLOS H30_DLOS_FWABIST_DLOS = {
    string("0,1"),
//    string("UseExternalSpec_FW_Judge"),
    string("BothMethod"),
    122.88,
    122.88,
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_17_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_Download_FW H30_Download_FW_VDDL_1_HILINK_Download_FW = {
    string("0,1"),
    0,
    0,
    3
};

stCTLE CTLE_CTLE = {
    string("0,1"),
    string("YES"),
    0,
    0,
    0,
    7,
    7,
    7,
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_PLL1_1016_1_1_20_13_REF1_VDDL_1_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("FullCal_FWABIST_USE"),
    string("NoAdpt"),
    string("External"),
    -1,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    3,
    33,
    20, //4.27
    13, //4.27
    0,
    10,
    16,
    string("0"),
    3
};

stFWABIST_DFEIDAC H30_DFEIDAC_VDDL_FWABIST_DFEIDAC = {
    string("0,1"),
//    string("UseExternalSpec_FW_Judge"),
    string("BothMethod"),
    122.88,
    122.88,
    3
};

stLatchOffset H30_LatchOffset_VDDL_to_VDDL_LatchOffset = {
    string("0,1"),
//    string("UseExternalSpec_FW_Judge"),
    string("BothMethod"),
    122.88,
    122.88,
    3
};

stLatchOffset H30_LatchOffset_VDDL_to_VDDH_LatchOffset = {
    string("0,1"),
//    string("UseExternalSpec_FW_Judge"),
    string("BothMethod"),
    122.88,
    122.88,
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDH_15_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_Download_FW H30_Download_FW_VDDH_HILINK_Download_FW = {
    string("0,1"),
    0,
    0,
    3
};

stCTLE CTLE_1_CTLE = {
    string("0,1"),
    string("YES"),
    0,
    0,
    0,
    7,
    7,
    7,
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_PLL1_1016_1_1_6_3_REF1_VDDH_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("FullCal_FWABIST_USE"),
    string("NoAdpt"),
    string("External"),
    -1,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    3,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stLatchOffset H30_LatchOffset_VDDH_to_VDDL_LatchOffset = {
    string("0,1"),
//    string("UseExternalSpec_FW_Judge"),
    string("BothMethod"),
    122.88,
    122.88,
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDL_18_HiLink30_PowerUp_Reset = {//4.27
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF2_Case02"),
    string(""),
    3
};

stHILINK_Download_FW H30_Download_FW_VDDL_2_HILINK_Download_FW = {
    string("0,1"),
    0,
    0,
    3
};

stFWABIST_VCOTuningRange H30_VCOTuningRange_FWABIST_VCOTuningRange = {
    string("0,1"),
//    string("UseExternalSpec_FW_Judge"),
    string("BothMethod"),
    156.25,
    156.25,
    0,
    3
};

stHiLink30_PowerUp_Reset H30_PowerUp_Reset_VDDH_16_HiLink30_PowerUp_Reset = {
    string("0,1"),
    string("PowerUp+Init"),
    200,
    0,
    string("HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1"),
    string("HILINK_R01_HI6871V110A_INIT_ALL_REF1_Case02"),
    string(""),
    3
};

stHILINK_Download_FW H30_Download_FW_VDDH_1_HILINK_Download_FW = {
    string("0,1"),
    0,
    0,
    3
};

stCTLE CTLE_A_1_CTLE = {
    string("0,1"),
    string("YES"),
    7,
    7,
    7,
    7,
    7,
    7,
    3
};

stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_PLL1_1016_1_1_6_3_REF1_VDDL_1_HILINK_FW_CAL = {//4.29
    string("0,1"),
    string("SS+CS+DS"),
    string("FullCal_FWABIST_USE"),
    string("NoAdpt"),
    string("External"),
    -1,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    3,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};
stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_PLL1_1016_1_1_6_3_REF1_VDDL_HILINK_FW_CAL = {//4.29
    string("0,1"),
    string("SS+CS+DS"),
    string("FullCal_FWABIST_USE"),
    string("NoAdpt"),
    string("External"),
    -1,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    3,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};



stHILINK_FW_CAL H30_FW_CAL_122M88_24G33024_1199full40_Refclk0_PLL0_PLL1_1016_1_1_6_3_REF1_VDDH_1_HILINK_FW_CAL = {
    string("0,1"),
    string("SS+CS+DS"),
    string("FullCal_FWABIST_USE"),
    string("NoAdpt"),
    string("External"),
    -1,
    122.88,
    122.88,
    0,
    1,
    1,
    string("0"),
    1,
    1,
    12.16512,
    3,
    33,
    6,
    3,
    0,
    10,
    16,
    string("0"),
    3
};

stFWABIST_ATB H30_Atb_VDDH_FWABIST_ATB = {
    string("0,1"),
//    string("UseExternalSpec_FW_Judge"),
    string("BothMethod"),
    122.88,
    122.88,
    3
};


stTxFIR_DC_Limit H30_TxFIR_DC_MAIN_ALL0_VDDN_TxFIR_DC_Limit = {
    5.55,
    8.32,
    1.22,
    2.27,
    -0.6,
    -0.4,
    -0.02,
    0.02
};

stTxFIR_DC_Limit H30_TxFIR_DC_MAIN_ALL1_VDDN_TxFIR_DC_Limit = {
    5.55,
    8.32,
    1.22,
    2.27,
    0.4,
    0.6,
    -0.02,
    0.02
};

stTxFIR_DC_Limit H30_TxFIR_DC_PRE1_ALL0_VDDN_TxFIR_DC_Limit = {
    1.1,
    2.03,
    0.5,
    0.92,
    -0.284,
    -0.19,
    0.094,
    0.14
};

stTxFIR_DC_Limit H30_TxFIR_DC_PRE1_ALL1_VDDN_TxFIR_DC_Limit = {
    1.1,
    2.03,
    0.5,
    0.92,
    -0.284,
    -0.19,
    -0.094,
    0.14
};

stTxFIR_DC_Limit H30_TxFIR_DC_PRE2_ALL0_VDDN_TxFIR_DC_Limit = {
    1.1,
    2.03,
    0.5,
    0.92,
    0.19,
    0.284,
    -0.14,
    -0.094
};

stTxFIR_DC_Limit H30_TxFIR_DC_PRE2_ALL1_VDDN_TxFIR_DC_Limit = {
    1.1,
    2.03,
    0.5,
    0.92,
    0.19,
    0.284,
    -0.14,
    -0.094
};

stTxFIR_DC_Limit H30_TxFIR_DC_POST1_ALL0_VDDN_TxFIR_DC_Limit = {
    1.52,
    2.83,
    0.63,
    1.17,
    -0.43,
    -0.287,
    0.189,
    0.283
};

stTxFIR_DC_Limit H30_TxFIR_DC_POST1_ALL1_VDDN_TxFIR_DC_Limit = {
    1.52,
    2.83,
    0.63,
    1.17,
    0.287,
    0.43,
    -0.283,
    -0.189
};

