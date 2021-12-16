<?xml version="1.0" encoding="UTF-8" ?>
<tests>
    <test name="H30_DISCONNECT" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.Disconnect">
            <propvalues />
        </testclass>
    </test>
    <test name="d2s_JAM_setup_156M25_On" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.LoadJAMSetup">
            <propvalues>
                <propvalue name="JAM1" value="" />
                <propvalue name="JAM2" value="" />
                <propvalue name="JAM3" value="" />
                <propvalue name="JAM4" value="" />
                <propvalue name="JAM5" value="" />
                <propvalue name="JAM6" value="" />
                <propvalue name="KEEP_ALIVE" value="ON" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_Download_FW_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_Download_FW">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="FwType" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL0_PLL1_108_1_1_18_12_V1_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS" />
                <propvalue name="Full_Cal_Enable" value="FullCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="-1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="SSbandGap" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.SSBandGap">
            <propvalues>
                <propvalue name="PinList" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="External_2K" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.Ext_2K_Resistor_Check">
            <propvalues>
                <propvalue name="PinList" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_DPM_TEST_BY_FW" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.DPM_TEST_BY_FW">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="JudgementType" value="ReadBack_InternalSpec_TMJudge" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDN_1" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_Download_FW_VDDN_1" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_Download_FW">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="FwType" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL0_PLL1_108_1_1_18_12_V1_VDDN_1" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="FullCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="-1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_Download_FW_VDDN_2" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_Download_FW">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="FwType" value="2" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_ADPT_156M25_28G125_1190full40_Refclk0_PLL0_PLL1_108_1_1_18_12_V1_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_ADAPTATION">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="FullAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="-1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_Download_FW_VDDN_3" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_Download_FW">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="FwType" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_MIN_PWR_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.MIN_PWR">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="TestMode" value="MIN_PWR" />
                <propvalue name="HVCC_Pin" value="" />
                <propvalue name="LVCC_Pin" value="" />
                <propvalue name="HVCC_Spec" value="" />
                <propvalue name="LVCC_Spec" value="" />
                <propvalue name="PowerUpControlPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDN_2" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_RxSigResBefCal_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.RxSigResBefCal_IFVM">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="CurrentSource1_mA" value="-5" />
                <propvalue name="CurrentSource2_mA" value="-1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_RxdiffResBefCal_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.RxDiffResBefCal_VFIM">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="ForceV" value="500" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_1" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL0_108_1_1_18_12_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_MAX_PWR_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.MAX_PWR">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="TestMode" value="MAX_PWR" />
                <propvalue name="HVCC_Pin" value="" />
                <propvalue name="LVCC_Pin" value="" />
                <propvalue name="HVCC_Spec" value="" />
                <propvalue name="LVCC_Spec" value="" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="PowerUpControlPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDN_3" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL0_108_1_1_18_12_V1_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_RxSigResAftCal_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.RxResAftCal_VFIM">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="Range_vol" value="500" />
                <propvalue name="Step_vol" value="50" />
                <propvalue name="Test_Mode" value="Sig" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_RxDiffResAftCal_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.RxResAftCal_VFIM">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="Range_vol" value="500" />
                <propvalue name="Step_vol" value="50" />
                <propvalue name="Test_Mode" value="Diff" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_RxTermVoltToGnd_AC" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.RxTermVoltToGnd_AC">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="Pattern" value="ALL0" />
                <propvalue name="ForceCurr" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxSigResAftCal_All0_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.TxResAftCal">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="PatternType" value="ALL0" />
                <propvalue name="current1_mA" value="-3" />
                <propvalue name="current2_mA" value="-4" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxSigResAftCal_All1_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.TxResAftCal">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="PatternType" value="ALL1" />
                <propvalue name="current1_mA" value="-3" />
                <propvalue name="current2_mA" value="-4" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxTermVolt_All0_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.TxTermVolt">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pattern" value="ALL0" />
                <propvalue name="Polarity" value="0" />
                <propvalue name="ForceCurr" value="-0.1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxTermVolt_All1_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.TxTermVolt">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pattern" value="ALL0" />
                <propvalue name="Polarity" value="1" />
                <propvalue name="ForceCurr" value="-0.1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDN_4" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL0_108_1_1_18_12_V1_VDDN_1" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxFIR_DC_MAIN_ALL0_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.TxFIR_DC">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="FIR_SCAN" value="MAIN" />
                <propvalue name="Data" value="ALL0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxFIR_DC_MAIN_ALL1_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.TxFIR_DC">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="FIR_SCAN" value="MAIN" />
                <propvalue name="Data" value="ALL1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxFIR_DC_PRE1_ALL0_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.TxFIR_DC">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="FIR_SCAN" value="PRE1ST" />
                <propvalue name="Data" value="ALL0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxFIR_DC_PRE1_ALL1_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.TxFIR_DC">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="FIR_SCAN" value="PRE1ST" />
                <propvalue name="Data" value="ALL1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxFIR_DC_PRE2_ALL0_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.TxFIR_DC">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="FIR_SCAN" value="PRE2ND" />
                <propvalue name="Data" value="ALL0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxFIR_DC_PRE2_ALL1_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.TxFIR_DC">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="FIR_SCAN" value="PRE2ND" />
                <propvalue name="Data" value="ALL1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxFIR_DC_POST1_ALL0_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.TxFIR_DC">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="FIR_SCAN" value="POST1ST" />
                <propvalue name="Data" value="ALL0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxFIR_DC_POST1_ALL1_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.TxFIR_DC">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="FIR_SCAN" value="POST1ST" />
                <propvalue name="Data" value="ALL1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="d2s_JAM_setup_156M25_On_1" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.LoadJAMSetup">
            <propvalues>
                <propvalue name="JAM1" value="" />
                <propvalue name="JAM2" value="" />
                <propvalue name="JAM3" value="" />
                <propvalue name="JAM4" value="" />
                <propvalue name="JAM5" value="" />
                <propvalue name="JAM6" value="" />
                <propvalue name="KEEP_ALIVE" value="ON" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_VCOLockRange_Refclk0_ABIST_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.VcoLockRange">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="Pll_Select" value="-1" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_2" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_VCOLockRange_Refclk0_ABIST_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.VcoLockRange">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="Pll_Select" value="-1" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="d2s_JAM_setup_156M25_Off" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.LoadJAMSetup">
            <propvalues>
                <propvalue name="JAM1" value="" />
                <propvalue name="JAM2" value="" />
                <propvalue name="JAM3" value="" />
                <propvalue name="JAM4" value="" />
                <propvalue name="JAM5" value="" />
                <propvalue name="JAM6" value="" />
                <propvalue name="KEEP_ALIVE" value="ON" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_RefclkLockRange_Refclk0_PLL_1_PLL_0" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.RefclkLockRange">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="Pll_Select" value="-1" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ClockSpec0" value="BYPASS" />
                <propvalue name="ClockSpec1" value="BYPASS" />
                <propvalue name="ClockSpec2" value="BYPASS" />
                <propvalue name="ClockSpec3" value="BYPASS" />
                <propvalue name="ClockSpec4" value="BYPASS" />
                <propvalue name="ClockSpec5" value="BYPASS" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_RefclkLockRange_Refclk1_PLL_1_PLL_0" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.RefclkLockRange">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="Pll_Select" value="-1" />
                <propvalue name="RefclkBus" value="1" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ClockSpec0" value="BYPASS" />
                <propvalue name="ClockSpec1" value="BYPASS" />
                <propvalue name="ClockSpec2" value="BYPASS" />
                <propvalue name="ClockSpec3" value="BYPASS" />
                <propvalue name="ClockSpec4" value="BYPASS" />
                <propvalue name="ClockSpec5" value="BYPASS" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="d2s_JAM_setup_156M25_On_2" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.LoadJAMSetup">
            <propvalues>
                <propvalue name="JAM1" value="" />
                <propvalue name="JAM2" value="" />
                <propvalue name="JAM3" value="" />
                <propvalue name="JAM4" value="" />
                <propvalue name="JAM5" value="" />
                <propvalue name="JAM6" value="" />
                <propvalue name="KEEP_ALIVE" value="ON" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDN_5" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_21G875_1170full40_Refclk0_PLL0_108_1_1_6_5_V1_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.9375" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="35" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="5" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_ClkPurity_Refclk0_PLL0_Fmin_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.ClkPurity_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="DataRate" value="21.875" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="UseFixCTLE" value="YES" />
                <propvalue name="UseFixCTLE.CTLEACTGN1" value="7" />
                <propvalue name="UseFixCTLE.CTLEACTGN2" value="7" />
                <propvalue name="UseFixCTLE.CTLEACTGN3" value="7" />
                <propvalue name="UseFixCTLE.CTLEBST1" value="0" />
                <propvalue name="UseFixCTLE.CTLEBST2" value="0" />
                <propvalue name="UseFixCTLE.CTLEBST3" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDN_6" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_20G625_1P5166full40_Refclk0_PLL0_108_1_1_6_3_V1_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.3125" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_ClkPurity_Refclk0_PLL0_Fmax_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.ClkPurity_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="DataRate" value="20.625" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="UseFixCTLE" value="YES" />
                <propvalue name="UseFixCTLE.CTLEACTGN1" value="7" />
                <propvalue name="UseFixCTLE.CTLEACTGN2" value="7" />
                <propvalue name="UseFixCTLE.CTLEACTGN3" value="7" />
                <propvalue name="UseFixCTLE.CTLEBST1" value="0" />
                <propvalue name="UseFixCTLE.CTLEBST2" value="0" />
                <propvalue name="UseFixCTLE.CTLEBST3" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDN_7" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_21G875_1170full40_Refclk0_PLL1_108_1_1_6_5_V1_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.9375" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="35" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="5" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_ClkPurity_Refclk0_PLL1_Fmin_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.ClkPurity_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="DataRate" value="21.875" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="UseFixCTLE" value="YES" />
                <propvalue name="UseFixCTLE.CTLEACTGN1" value="7" />
                <propvalue name="UseFixCTLE.CTLEACTGN2" value="7" />
                <propvalue name="UseFixCTLE.CTLEACTGN3" value="7" />
                <propvalue name="UseFixCTLE.CTLEBST1" value="0" />
                <propvalue name="UseFixCTLE.CTLEBST2" value="0" />
                <propvalue name="UseFixCTLE.CTLEBST3" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDN_8" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_20G625_1P5166full40_Refclk0_PLL1_108_1_1_6_3_V1_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.3125" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_ClkPurity_Refclk0_PLL1_Fmax_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.ClkPurity_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="DataRate" value="20.625" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="UseFixCTLE" value="YES" />
                <propvalue name="UseFixCTLE.CTLEACTGN1" value="7" />
                <propvalue name="UseFixCTLE.CTLEACTGN2" value="7" />
                <propvalue name="UseFixCTLE.CTLEACTGN3" value="7" />
                <propvalue name="UseFixCTLE.CTLEBST1" value="0" />
                <propvalue name="UseFixCTLE.CTLEBST2" value="0" />
                <propvalue name="UseFixCTLE.CTLEBST3" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="d2s_JAM_setup_109M375_On" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.LoadJAMSetup">
            <propvalues>
                <propvalue name="JAM1" value="" />
                <propvalue name="JAM2" value="" />
                <propvalue name="JAM3" value="" />
                <propvalue name="JAM4" value="" />
                <propvalue name="JAM5" value="" />
                <propvalue name="JAM6" value="" />
                <propvalue name="KEEP_ALIVE" value="ON" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_1" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_109M375_27G34375_11125full40_Refclk1_PLL0_108_1_1_26_15_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="109.375" />
                <propvalue name="RefCLK_MHz2" value="109.375" />
                <propvalue name="RefclkBus" value="1" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.671875" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="125" />
                <propvalue name="P" value="26" />
                <propvalue name="S" value="15" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_109M375_27G34375_11125full40_Refclk1_PLL0_108_1_1_26_15_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_2" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_109M375_27G34375_11125full40_Refclk1_PLL1_108_1_1_26_15_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="109.375" />
                <propvalue name="RefCLK_MHz2" value="109.375" />
                <propvalue name="RefclkBus" value="1" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.671875" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="125" />
                <propvalue name="P" value="26" />
                <propvalue name="S" value="15" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_109M375_27G34375_11125full40_Refclk1_PLL1_108_1_1_26_15_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="d2s_JAM_setup_156M25_On_3" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.LoadJAMSetup">
            <propvalues>
                <propvalue name="JAM1" value="" />
                <propvalue name="JAM2" value="" />
                <propvalue name="JAM3" value="" />
                <propvalue name="JAM4" value="" />
                <propvalue name="JAM5" value="" />
                <propvalue name="JAM6" value="" />
                <propvalue name="KEEP_ALIVE" value="ON" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_3" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_1G25_1P5264octal10_Refclk0_PLL0_108_1_1_6_2_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="3" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="32" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="2" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_1G25_1P5264octal10_Refclk0_PLL0_108_1_1_6_2_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="3" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_4" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_1G25_1P5264octal10_Refclk0_PLL1_108_1_1_6_2_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="3" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="32" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="2" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_1G25_1P5264octal10_Refclk0_PLL1_108_1_1_6_2_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="3" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_5" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_3G125_1280quarter10_Refclk0_PLL0_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="6.25" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_3G125_1280quarter10_Refclk0_PLL0_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_6" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_3G125_1180octal10_Refclk0_PLL0_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="3" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="12.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_3G125_1180octal10_Refclk0_PLL0_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="3" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_7" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_3G125_1280quarter10_Refclk0_PLL1_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="6.25" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_3G125_1280quarter10_Refclk0_PLL1_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_8" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_3G125_1180octal10_Refclk0_PLL1_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="3" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="12.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_3G125_1180octal10_Refclk0_PLL1_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="3" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_9" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_3G75_1P5148quarter20_Refclk0_PLL0_2016_1_1_4_2_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="7.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="24" />
                <propvalue name="P" value="4" />
                <propvalue name="S" value="2" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="20" />
                <propvalue name="J_32b" value="16" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_3G75_1P5148quarter20_Refclk0_PLL0_2016_1_1_4_2_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_10" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_3G75_1P5148quarter20_Refclk0_PLL1_2016_1_1_4_2_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="7.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="24" />
                <propvalue name="P" value="4" />
                <propvalue name="S" value="2" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="20" />
                <propvalue name="J_32b" value="16" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_3G75_1P5148quarter20_Refclk0_PLL1_2016_1_1_4_2_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_11" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_5G_1P5264half20_Refclk0_PLL0_108_1_1_6_2_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="32" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="2" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_5G_1P5264half20_Refclk0_PLL0_108_1_1_6_2_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_12" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_5G_1P5264half20_Refclk0_PLL1_108_1_1_6_2_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="32" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="2" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_5G_1P5264half20_Refclk0_PLL1_108_1_1_6_2_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_13" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_5G15625_1P5266half20_Refclk0_PLL0_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5.15625" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_5G15625_1P5266half20_Refclk0_PLL0_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_14" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_5G15625_1P5166quarter20_Refclk0_PLL0_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.3125" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_5G15625_1P5166quarter20_Refclk0_PLL0_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_15" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_5G15625_1P5266half20_Refclk0_PLL1_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5.15625" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_5G15625_1P5266half20_Refclk0_PLL1_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_16" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_5G15625_1P5166quarter20_Refclk0_PLL1_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.3125" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_5G15625_1P5166quarter20_Refclk0_PLL1_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_17" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_6G25_1180quarter10_Refclk0_PLL0_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="12.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_6G25_1180quarter10_Refclk0_PLL0_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_18" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_6G25_1280half20_Refclk0_PLL0_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="6.25" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_6G25_1280half20_Refclk0_PLL0_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_19" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_6G25_1180quarter10_Refclk0_PLL1_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="12.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_6G25_1180quarter10_Refclk0_PLL1_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_20" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_6G25_1280half20_Refclk0_PLL1_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="6.25" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_6G25_1280half20_Refclk0_PLL1_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_21" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_6G25_1280half40_Refclk0_PLL0_2016_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_g" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="6.25" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="20" />
                <propvalue name="J_32b" value="16" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_6G25_1280half40_Refclk0_PLL0_2016_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_g" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_22" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_8G125_1P5152half40_Refclk0_PLL0_2016_1_1_4_4_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="8.125" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="26" />
                <propvalue name="P" value="4" />
                <propvalue name="S" value="4" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="20" />
                <propvalue name="J_32b" value="16" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_8G125_1P5152half40_Refclk0_PLL0_2016_1_1_4_4_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_23" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_8G125_1P5152half40_Refclk0_PLL1_2016_1_1_4_4_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="8.125" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="26" />
                <propvalue name="P" value="4" />
                <propvalue name="S" value="4" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="20" />
                <propvalue name="J_32b" value="16" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_8G125_1P5152half40_Refclk0_PLL1_2016_1_1_4_4_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_24" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_10G3125_1P5266full40_Refclk0_PLL0_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5.15625" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_10G3125_1P5266full40_Refclk0_PLL0_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_25" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_10G3125_1P5166half40_Refclk0_PLL0_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.3125" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_10G3125_1P5166half40_Refclk0_PLL0_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_26" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_10G3125_1P5266full40_Refclk0_PLL1_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5.15625" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_10G3125_1P5266full40_Refclk0_PLL1_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_27" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_10G3125_1P5166half40_Refclk0_PLL1_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.3125" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_10G3125_1P5166half40_Refclk0_PLL1_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_28" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_10G9375_1270full40_Refclk0_PLL0_108_1_1_6_5_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5.46875" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="35" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="5" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_10G9375_1270full40_Refclk0_PLL0_108_1_1_6_5_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_29" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_10G9375_1170half40_Refclk0_PLL0_108_1_1_6_5_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.9375" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="35" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="5" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_10G9375_1170half40_Refclk0_PLL0_108_1_1_6_5_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_30" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_10G9375_1270full40_Refclk0_PLL1_108_1_1_6_5_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5.46875" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="35" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="5" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_10G9375_1270full40_Refclk0_PLL1_108_1_1_6_5_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_31" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_10G9375_1170half40_Refclk0_PLL1_108_1_1_6_5_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.9375" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="35" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="5" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_10G9375_1170half40_Refclk0_PLL1_108_1_1_6_5_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_32" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_12G5_1280full40_Refclk0_PLL0_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_f" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="6.25" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_12G5_1280full40_Refclk0_PLL0_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_f" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_33" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_12G5_1280full40_Refclk0_PLL1_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="6.25" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_12G5_1280full40_Refclk0_PLL1_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_34" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_15G_1296full40_Refclk0_PLL0_108_1_1_9_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_f" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="7.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="48" />
                <propvalue name="P" value="9" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_15G_1296full40_Refclk0_PLL0_108_1_1_9_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_f" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_35" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_15G_1296full40_Refclk0_PLL1_108_1_1_9_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="7.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="48" />
                <propvalue name="P" value="9" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_15G_1296full40_Refclk0_PLL1_108_1_1_9_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_36" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_20G625_1P5166full40_Refclk0_PLL0_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.3125" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_20G625_1P5166full40_Refclk0_PLL0_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_37" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_20G625_1P5166full40_Refclk0_PLL1_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.3125" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_20G625_1P5166full40_Refclk0_PLL1_108_1_1_6_3_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_38" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_21G875_1170full40_Refclk0_PLL0_108_1_1_6_5_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.9375" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="35" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="5" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_21G875_1170full40_Refclk0_PLL0_108_1_1_6_5_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_39" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_21G875_1170full40_Refclk0_PLL1_108_1_1_6_5_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.9375" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="35" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="5" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_21G875_1170full40_Refclk0_PLL1_108_1_1_6_5_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_40" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_25G_1180full40_Refclk0_PLL0_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="12.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_25G_1180full40_Refclk0_PLL0_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_41" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_25G_1180full40_Refclk0_PLL1_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="12.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_25G_1180full40_Refclk0_PLL1_108_1_1_7_6_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_42" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_25G78125_11165full40_Refclk0_PLL0_108_2_1_10_9_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="2" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="12.890625" />
                <propvalue name="Na" value="3" />
                <propvalue name="Nb" value="55" />
                <propvalue name="P" value="10" />
                <propvalue name="S" value="9" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_25G78125_11165full40_Refclk0_PLL0_108_2_1_10_9_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_43" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_25G78125_11165full40_Refclk0_PLL1_108_2_1_10_9_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="2" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="12.890625" />
                <propvalue name="Na" value="3" />
                <propvalue name="Nb" value="55" />
                <propvalue name="P" value="10" />
                <propvalue name="S" value="9" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_25G78125_11165full40_Refclk0_PLL1_108_2_1_10_9_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_44" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_26G5625_1185full40_Refclk0_PLL0_108_1_1_16_15_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.28125" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="85" />
                <propvalue name="P" value="16" />
                <propvalue name="S" value="15" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_26G5625_1185full40_Refclk0_PLL0_108_1_1_16_15_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_45" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_26G5625_1185full40_Refclk0_PLL1_108_1_1_16_15_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.28125" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="85" />
                <propvalue name="P" value="16" />
                <propvalue name="S" value="15" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_26G5625_1185full40_Refclk0_PLL1_108_1_1_16_15_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_46" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL0_108_1_1_18_12_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_f" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_28G125_1190full40_Refclk0_PLL0_108_1_1_18_12_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_f" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_47" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL1_108_1_1_18_12_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_28G125_1190full40_Refclk0_PLL1_108_1_1_18_12_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="d2s_JAM_setup_195M3125_On" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.LoadJAMSetup">
            <propvalues>
                <propvalue name="JAM1" value="" />
                <propvalue name="JAM2" value="" />
                <propvalue name="JAM3" value="" />
                <propvalue name="JAM4" value="" />
                <propvalue name="JAM5" value="" />
                <propvalue name="JAM6" value="" />
                <propvalue name="KEEP_ALIVE" value="ON" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_48" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_195M3125_27G34375_1170full40_Refclk1_PLL0_108_1_1_13_12_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="195.3125" />
                <propvalue name="RefCLK_MHz2" value="195.3125" />
                <propvalue name="RefclkBus" value="1" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.671875" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="70" />
                <propvalue name="P" value="13" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_195M3125_27G34375_1170full40_Refclk1_PLL0_108_1_1_13_12_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_49" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_195M3125_27G34375_1170full40_Refclk1_PLL1_108_1_1_13_12_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="195.3125" />
                <propvalue name="RefCLK_MHz2" value="195.3125" />
                <propvalue name="RefclkBus" value="1" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.671875" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="70" />
                <propvalue name="P" value="13" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_195M3125_27G34375_1170full40_Refclk1_PLL1_108_1_1_13_12_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="d2s_JAM_setup_273M4375_On" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.LoadJAMSetup">
            <propvalues>
                <propvalue name="JAM1" value="" />
                <propvalue name="JAM2" value="" />
                <propvalue name="JAM3" value="" />
                <propvalue name="JAM4" value="" />
                <propvalue name="JAM5" value="" />
                <propvalue name="JAM6" value="" />
                <propvalue name="KEEP_ALIVE" value="ON" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_50" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_273M4375_27G34375_1150full40_Refclk1_PLL0_108_1_1_9_8_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="273.4375" />
                <propvalue name="RefCLK_MHz2" value="273.4375" />
                <propvalue name="RefclkBus" value="1" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.671875" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="50" />
                <propvalue name="P" value="9" />
                <propvalue name="S" value="8" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_273M4375_27G34375_1150full40_Refclk1_PLL0_108_1_1_9_8_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_51" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_273M4375_27G34375_1150full40_Refclk1_PLL1_108_1_1_9_8_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="273.4375" />
                <propvalue name="RefCLK_MHz2" value="273.4375" />
                <propvalue name="RefclkBus" value="1" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.671875" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="50" />
                <propvalue name="P" value="9" />
                <propvalue name="S" value="8" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_273M4375_27G34375_1150full40_Refclk1_PLL1_108_1_1_9_8_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="d2s_JAM_setup_109M375_On_1" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.LoadJAMSetup">
            <propvalues>
                <propvalue name="JAM1" value="" />
                <propvalue name="JAM2" value="" />
                <propvalue name="JAM3" value="" />
                <propvalue name="JAM4" value="" />
                <propvalue name="JAM5" value="" />
                <propvalue name="JAM6" value="" />
                <propvalue name="KEEP_ALIVE" value="ON" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_3" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_109M375_27G34375_11125full40_Refclk1_PLL0_108_1_1_26_15_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="109.375" />
                <propvalue name="RefCLK_MHz2" value="109.375" />
                <propvalue name="RefclkBus" value="1" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.671875" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="125" />
                <propvalue name="P" value="26" />
                <propvalue name="S" value="15" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_109M375_27G34375_11125full40_Refclk1_PLL0_108_1_1_26_15_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_4" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_109M375_27G34375_11125full40_Refclk1_PLL1_108_1_1_26_15_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="109.375" />
                <propvalue name="RefCLK_MHz2" value="109.375" />
                <propvalue name="RefclkBus" value="1" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.671875" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="125" />
                <propvalue name="P" value="26" />
                <propvalue name="S" value="15" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_109M375_27G34375_11125full40_Refclk1_PLL1_108_1_1_26_15_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="d2s_JAM_setup_156M25_On_4" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.LoadJAMSetup">
            <propvalues>
                <propvalue name="JAM1" value="" />
                <propvalue name="JAM2" value="" />
                <propvalue name="JAM3" value="" />
                <propvalue name="JAM4" value="" />
                <propvalue name="JAM5" value="" />
                <propvalue name="JAM6" value="" />
                <propvalue name="KEEP_ALIVE" value="ON" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_5" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_1G25_1P5264octal10_Refclk0_PLL0_108_1_1_6_2_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="3" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="32" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="2" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_1G25_1P5264octal10_Refclk0_PLL0_108_1_1_6_2_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="3" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_6" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_1G25_1P5264octal10_Refclk0_PLL1_108_1_1_6_2_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="3" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="32" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="2" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_1G25_1P5264octal10_Refclk0_PLL1_108_1_1_6_2_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="3" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_7" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_3G125_1280quarter10_Refclk0_PLL0_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="6.25" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_3G125_1280quarter10_Refclk0_PLL0_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_8" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_3G125_1180octal10_Refclk0_PLL0_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="3" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="12.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_3G125_1180octal10_Refclk0_PLL0_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="3" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_9" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_3G125_1280quarter10_Refclk0_PLL1_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="6.25" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_3G125_1280quarter10_Refclk0_PLL1_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_10" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_3G125_1180octal10_Refclk0_PLL1_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="3" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="12.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_3G125_1180octal10_Refclk0_PLL1_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="3" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_11" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_3G75_1P5148quarter20_Refclk0_PLL0_2016_1_1_4_2_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="7.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="24" />
                <propvalue name="P" value="4" />
                <propvalue name="S" value="2" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="20" />
                <propvalue name="J_32b" value="16" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_3G75_1P5148quarter20_Refclk0_PLL0_2016_1_1_4_2_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_12" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_3G75_1P5148quarter20_Refclk0_PLL1_2016_1_1_4_2_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="7.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="24" />
                <propvalue name="P" value="4" />
                <propvalue name="S" value="2" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="20" />
                <propvalue name="J_32b" value="16" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_3G75_1P5148quarter20_Refclk0_PLL1_2016_1_1_4_2_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_13" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_5G_1P5264half20_Refclk0_PLL0_108_1_1_6_2_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="32" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="2" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_5G_1P5264half20_Refclk0_PLL0_108_1_1_6_2_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_14" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_5G_1P5264half20_Refclk0_PLL1_108_1_1_6_2_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="32" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="2" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_5G_1P5264half20_Refclk0_PLL1_108_1_1_6_2_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_15" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_5G15625_1P5266half20_Refclk0_PLL0_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5.15625" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_5G15625_1P5266half20_Refclk0_PLL0_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_16" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_5G15625_1P5166quarter20_Refclk0_PLL0_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.3125" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_5G15625_1P5166quarter20_Refclk0_PLL0_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_17" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_5G15625_1P5266half20_Refclk0_PLL1_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5.15625" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_5G15625_1P5266half20_Refclk0_PLL1_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_18" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_5G15625_1P5166quarter20_Refclk0_PLL1_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.3125" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_5G15625_1P5166quarter20_Refclk0_PLL1_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_19" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_6G25_1180quarter10_Refclk0_PLL0_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="12.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_6G25_1180quarter10_Refclk0_PLL0_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_20" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_6G25_1280half20_Refclk0_PLL0_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="6.25" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_6G25_1280half20_Refclk0_PLL0_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_21" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_6G25_1180quarter10_Refclk0_PLL1_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="12.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_6G25_1180quarter10_Refclk0_PLL1_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_22" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_6G25_1280half20_Refclk0_PLL1_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="6.25" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_6G25_1280half20_Refclk0_PLL1_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_23" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_6G25_1280half40_Refclk0_PLL0_2016_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_g" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="6.25" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="20" />
                <propvalue name="J_32b" value="16" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_6G25_1280half40_Refclk0_PLL0_2016_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_g" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_24" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_8G125_1P5152half40_Refclk0_PLL0_2016_1_1_4_4_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="8.125" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="26" />
                <propvalue name="P" value="4" />
                <propvalue name="S" value="4" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="20" />
                <propvalue name="J_32b" value="16" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_8G125_1P5152half40_Refclk0_PLL0_2016_1_1_4_4_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_25" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_8G125_1P5152half40_Refclk0_PLL1_2016_1_1_4_4_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="8.125" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="26" />
                <propvalue name="P" value="4" />
                <propvalue name="S" value="4" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="20" />
                <propvalue name="J_32b" value="16" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_8G125_1P5152half40_Refclk0_PLL1_2016_1_1_4_4_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_26" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_10G3125_1P5266full40_Refclk0_PLL0_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5.15625" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_10G3125_1P5266full40_Refclk0_PLL0_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_27" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_10G3125_1P5166half40_Refclk0_PLL0_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.3125" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_10G3125_1P5166half40_Refclk0_PLL0_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_28" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_10G3125_1P5266full40_Refclk0_PLL1_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5.15625" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_10G3125_1P5266full40_Refclk0_PLL1_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_29" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_10G3125_1P5166half40_Refclk0_PLL1_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.3125" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_10G3125_1P5166half40_Refclk0_PLL1_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_30" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_10G9375_1270full40_Refclk0_PLL0_108_1_1_6_5_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5.46875" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="35" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="5" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_10G9375_1270full40_Refclk0_PLL0_108_1_1_6_5_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_31" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_10G9375_1170half40_Refclk0_PLL0_108_1_1_6_5_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.9375" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="35" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="5" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_10G9375_1170half40_Refclk0_PLL0_108_1_1_6_5_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_32" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_10G9375_1270full40_Refclk0_PLL1_108_1_1_6_5_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5.46875" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="35" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="5" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_10G9375_1270full40_Refclk0_PLL1_108_1_1_6_5_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_33" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_10G9375_1170half40_Refclk0_PLL1_108_1_1_6_5_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.9375" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="35" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="5" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_10G9375_1170half40_Refclk0_PLL1_108_1_1_6_5_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_34" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_12G5_1280full40_Refclk0_PLL0_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_f" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="6.25" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_12G5_1280full40_Refclk0_PLL0_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_f" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_35" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_12G5_1280full40_Refclk0_PLL1_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="6.25" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_12G5_1280full40_Refclk0_PLL1_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_36" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_15G_1296full40_Refclk0_PLL0_108_1_1_9_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_f" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="7.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="48" />
                <propvalue name="P" value="9" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_15G_1296full40_Refclk0_PLL0_108_1_1_9_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_f" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_37" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_15G_1296full40_Refclk0_PLL1_108_1_1_9_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="7.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="48" />
                <propvalue name="P" value="9" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_15G_1296full40_Refclk0_PLL1_108_1_1_9_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_38" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_20G625_1P5166full40_Refclk0_PLL0_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.3125" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_20G625_1P5166full40_Refclk0_PLL0_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_39" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_20G625_1P5166full40_Refclk0_PLL1_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.3125" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_20G625_1P5166full40_Refclk0_PLL1_108_1_1_6_3_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_40" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_21G875_1170full40_Refclk0_PLL0_108_1_1_6_5_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.9375" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="35" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="5" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_21G875_1170full40_Refclk0_PLL0_108_1_1_6_5_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_41" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_21G875_1170full40_Refclk0_PLL1_108_1_1_6_5_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="10.9375" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="35" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="5" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_21G875_1170full40_Refclk0_PLL1_108_1_1_6_5_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_a" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_42" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_25G_1180full40_Refclk0_PLL0_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="12.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_25G_1180full40_Refclk0_PLL0_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_43" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_25G_1180full40_Refclk0_PLL1_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="12.5" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="40" />
                <propvalue name="P" value="7" />
                <propvalue name="S" value="6" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_25G_1180full40_Refclk0_PLL1_108_1_1_7_6_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_44" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_25G78125_11165full40_Refclk0_PLL0_108_2_1_10_9_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="2" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="12.890625" />
                <propvalue name="Na" value="3" />
                <propvalue name="Nb" value="55" />
                <propvalue name="P" value="10" />
                <propvalue name="S" value="9" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_25G78125_11165full40_Refclk0_PLL0_108_2_1_10_9_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_45" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_25G78125_11165full40_Refclk0_PLL1_108_2_1_10_9_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="2" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="12.890625" />
                <propvalue name="Na" value="3" />
                <propvalue name="Nb" value="55" />
                <propvalue name="P" value="10" />
                <propvalue name="S" value="9" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_25G78125_11165full40_Refclk0_PLL1_108_2_1_10_9_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_46" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_26G5625_1185full40_Refclk0_PLL0_108_1_1_16_15_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.28125" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="85" />
                <propvalue name="P" value="16" />
                <propvalue name="S" value="15" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_26G5625_1185full40_Refclk0_PLL0_108_1_1_16_15_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_47" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_26G5625_1185full40_Refclk0_PLL1_108_1_1_16_15_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.28125" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="85" />
                <propvalue name="P" value="16" />
                <propvalue name="S" value="15" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_26G5625_1185full40_Refclk0_PLL1_108_1_1_16_15_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_b" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_48" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL0_108_1_1_18_12_V1_VDDH_1" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_f" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_28G125_1190full40_Refclk0_PLL0_108_1_1_18_12_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_f" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_49" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL1_108_1_1_18_12_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_28G125_1190full40_Refclk0_PLL1_108_1_1_18_12_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="d2s_JAM_setup_195M3125_On_1" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.LoadJAMSetup">
            <propvalues>
                <propvalue name="JAM1" value="" />
                <propvalue name="JAM2" value="" />
                <propvalue name="JAM3" value="" />
                <propvalue name="JAM4" value="" />
                <propvalue name="JAM5" value="" />
                <propvalue name="JAM6" value="" />
                <propvalue name="KEEP_ALIVE" value="ON" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_50" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_195M3125_27G34375_1170full40_Refclk1_PLL0_108_1_1_13_12_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="195.3125" />
                <propvalue name="RefCLK_MHz2" value="195.3125" />
                <propvalue name="RefclkBus" value="1" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.671875" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="70" />
                <propvalue name="P" value="13" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_195M3125_27G34375_1170full40_Refclk1_PLL0_108_1_1_13_12_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_51" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_195M3125_27G34375_1170full40_Refclk1_PLL1_108_1_1_13_12_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="195.3125" />
                <propvalue name="RefCLK_MHz2" value="195.3125" />
                <propvalue name="RefclkBus" value="1" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.671875" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="70" />
                <propvalue name="P" value="13" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_195M3125_27G34375_1170full40_Refclk1_PLL1_108_1_1_13_12_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="d2s_JAM_setup_273M4375_On_1" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.LoadJAMSetup">
            <propvalues>
                <propvalue name="JAM1" value="" />
                <propvalue name="JAM2" value="" />
                <propvalue name="JAM3" value="" />
                <propvalue name="JAM4" value="" />
                <propvalue name="JAM5" value="" />
                <propvalue name="JAM6" value="" />
                <propvalue name="KEEP_ALIVE" value="ON" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_52" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_273M4375_27G34375_1150full40_Refclk1_PLL0_108_1_1_9_8_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="273.4375" />
                <propvalue name="RefCLK_MHz2" value="273.4375" />
                <propvalue name="RefclkBus" value="1" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.671875" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="50" />
                <propvalue name="P" value="9" />
                <propvalue name="S" value="8" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_273M4375_27G34375_1150full40_Refclk1_PLL0_108_1_1_9_8_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_53" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_273M4375_27G34375_1150full40_Refclk1_PLL1_108_1_1_9_8_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="273.4375" />
                <propvalue name="RefCLK_MHz2" value="273.4375" />
                <propvalue name="RefclkBus" value="1" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.671875" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="50" />
                <propvalue name="P" value="9" />
                <propvalue name="S" value="8" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_273M4375_27G34375_1150full40_Refclk1_PLL1_108_1_1_9_8_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="d2s_JAM_setup_156M25_On_5" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.LoadJAMSetup">
            <propvalues>
                <propvalue name="JAM1" value="" />
                <propvalue name="JAM2" value="" />
                <propvalue name="JAM3" value="" />
                <propvalue name="JAM4" value="" />
                <propvalue name="JAM5" value="" />
                <propvalue name="JAM6" value="" />
                <propvalue name="KEEP_ALIVE" value="ON" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDN_9" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL0_108_1_1_18_12_V1_VDDN_2" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxEScopePrbs15_28G125_ABIST" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.TxEScopePrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="DataRate" value="28.125" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="FULL_EYE" value="NO" />
                <propvalue name="PRBSMode" value="PRBS15" />
                <propvalue name="EyeDiagram Method" value="FW" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_RxSensitivity_28G125_ABIST" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.RxSensitivity_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="MAIN_STOP" value="0" />
                <propvalue name="MAIN_STEP" value="3" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_RxJitterTol_28G125_ABIST" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.RxJitterTol_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="DataRate" value="28.125" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_RxFreqOffsetTol_28G125_ABIST" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.RxFreqOffsetTol_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_RxALOS_28G125_ABIST" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.RxALOS_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxMain_H" value="24" />
                <propvalue name="TxMain_L" value="0" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDN_10" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL0_108_1_1_18_12_V1_VDDN_3" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="PreDriver" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FuncBertPrbs_156M25_28G125_1190full40_Refclk0_PLL0_108_1_1_18_12_V1_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.FuncBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="PreDriver" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="d2s_JAM_setup_156M25_On_6" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.LoadJAMSetup">
            <propvalues>
                <propvalue name="JAM1" value="" />
                <propvalue name="JAM2" value="" />
                <propvalue name="JAM3" value="" />
                <propvalue name="JAM4" value="" />
                <propvalue name="JAM5" value="" />
                <propvalue name="JAM6" value="" />
                <propvalue name="KEEP_ALIVE" value="ON" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDN_11" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_10G3125_1P5266full40_Refclk0_PLL0_108_1_1_6_3_V1_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="Bump" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="5.15625" />
                <propvalue name="Na" value="2" />
                <propvalue name="Nb" value="33" />
                <propvalue name="P" value="6" />
                <propvalue name="S" value="3" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FuncBertPrbs_156M25_10G3125_1P5266full40_Refclk0_PLL0_108_1_1_6_3_V1_VDDN" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDN" comment="">
        <testclass name="libHilink30LRV101_tml.FuncBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="Bump" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="d2s_JAM_setup_156M25_On_7" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.LoadJAMSetup">
            <propvalues>
                <propvalue name="JAM1" value="" />
                <propvalue name="JAM2" value="" />
                <propvalue name="JAM3" value="" />
                <propvalue name="JAM4" value="" />
                <propvalue name="JAM5" value="" />
                <propvalue name="JAM6" value="" />
                <propvalue name="KEEP_ALIVE" value="ON" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_52" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL0_108_1_1_18_12_V1_VDDL_1" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_EyeMonitorCheckPrbs31_28G125_ABIST" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.EyeMonitorCheckPrbs31_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="DataRate" value="28.125" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="0" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="-6" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_53" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_14G0625_1190half20_Refclk0_PLL0_108_1_1_18_12_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_EyeMonitorCheckPrbs31_14G0625_ABIST" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.EyeMonitorCheckPrbs31_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="DataRate" value="14.0625" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="0" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="-6" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_54" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_7G03125_1190quar20_Refclk0_PLL0_108_1_1_18_12_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_EyeMonitorCheckPrbs31_7G03125_ABIST" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.EyeMonitorCheckPrbs31_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="DataRate" value="7.03125" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="0" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="-6" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_54" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL0_108_1_1_18_12_V1_VDDH_2" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_RxStrsAll_28G125_ABIST_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.RxStressAll_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="TxFIR.TxMain" value="35" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="DataRate" value="28.125" />
                <propvalue name="FULL_EYE" value="NO" />
                <propvalue name="FreqOffset" value="100" />
                <propvalue name="JIAmp" value="0.09375" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="EyeDiagram Method" value="FW" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_55" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL0_108_1_1_18_12_V1_VDDL_2" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_RxStrsAll_28G125_ABIST_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.RxStressAll_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="TxFIR.TxMain" value="35" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="DataRate" value="28.125" />
                <propvalue name="FULL_EYE" value="NO" />
                <propvalue name="FreqOffset" value="100" />
                <propvalue name="JIAmp" value="0.09375" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="EyeDiagram Method" value="FW" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_55" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL0_108_1_1_18_12_V1_VDDH_3" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_AVS_Verify_28G125_ABIST_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.AVS_Verify_ABIST">
            <propvalues>
                <propvalue name="DPSPinList" value="" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="Search Direction" value="High2Low" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="Search_Low" value="0.71375" />
                <propvalue name="Search_High" value="0.88625" />
                <propvalue name="Search_Step" value="0.00625" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_56" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL0_108_1_1_18_12_V1_VDDL_3" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="BypassAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_AVS_Verify_28G125_ABIST_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.AVS_Verify_ABIST">
            <propvalues>
                <propvalue name="DPSPinList" value="" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="Search Direction" value="Low2High" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="Search_Low" value="0.71375" />
                <propvalue name="Search_High" value="0.88625" />
                <propvalue name="Search_Step" value="0.00625" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_57" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_Download_FW_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_Download_FW">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="FwType" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="CTLE_A" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.CTLE">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="UseFixCTLE" value="YES" />
                <propvalue name="UseFixCTLE.CTLEACTGN1" value="7" />
                <propvalue name="UseFixCTLE.CTLEACTGN2" value="7" />
                <propvalue name="UseFixCTLE.CTLEACTGN3" value="7" />
                <propvalue name="UseFixCTLE.CTLEBST1" value="7" />
                <propvalue name="UseFixCTLE.CTLEBST2" value="7" />
                <propvalue name="UseFixCTLE.CTLEBST3" value="7" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL0_PLL1_108_1_1_18_12_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="FullCal_FWABIST_USE" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="-1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_Atb_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.FWABIST_ATB">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="JudgementType" value="UseExternalSpec_FW_Judge" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK2_MHz" value="156.25" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_DcGain" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.DcGain">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="JudgementType" value="UseExternalSpec_FW_Judge" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK2_MHz" value="156.25" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_Alphagen" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.Alphagen">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="JudgementType" value="UseExternalSpec_FW_Judge" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK2_MHz" value="156.25" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_Regulator" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.Regulator">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="JudgementType" value="UseExternalSpec_FW_Judge" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK2_MHz" value="156.25" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_ADCstability" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.FWABIST_AdcStability">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="JudgementType" value="UseExternalSpec_FW_Judge" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK2_MHz" value="156.25" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_Comparator" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.FWABIST_Comparator">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="JudgementType" value="UseExternalSpec_FW_Judge" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK2_MHz" value="156.25" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_DLOS" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.FWABIST_DLOS">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="JudgementType" value="UseExternalSpec_FW_Judge" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK2_MHz" value="156.25" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_58" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_Download_FW_VDDL_1" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_Download_FW">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="FwType" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="CTLE" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.CTLE">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="UseFixCTLE" value="YES" />
                <propvalue name="UseFixCTLE.CTLEACTGN1" value="0" />
                <propvalue name="UseFixCTLE.CTLEACTGN2" value="0" />
                <propvalue name="UseFixCTLE.CTLEACTGN3" value="0" />
                <propvalue name="UseFixCTLE.CTLEBST1" value="7" />
                <propvalue name="UseFixCTLE.CTLEBST2" value="7" />
                <propvalue name="UseFixCTLE.CTLEBST3" value="7" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL0_PLL1_108_1_1_18_12_V1_VDDL_1" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="FullCal_FWABIST_USE" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="-1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_DFEIDAC_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.FWABIST_DFEIDAC">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="JudgementType" value="UseExternalSpec_FW_Judge" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK2_MHz" value="156.25" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_LatchOffset_VDDL_to_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.LatchOffset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="JudgementType" value="UseExternalSpec_FW_Judge" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK2_MHz" value="156.25" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_LatchOffset_VDDL_to_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.LatchOffset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="JudgementType" value="UseExternalSpec_FW_Judge" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK2_MHz" value="156.25" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_56" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_Download_FW_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_Download_FW">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="FwType" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="CTLE_1" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.CTLE">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="UseFixCTLE" value="YES" />
                <propvalue name="UseFixCTLE.CTLEACTGN1" value="0" />
                <propvalue name="UseFixCTLE.CTLEACTGN2" value="0" />
                <propvalue name="UseFixCTLE.CTLEACTGN3" value="0" />
                <propvalue name="UseFixCTLE.CTLEBST1" value="7" />
                <propvalue name="UseFixCTLE.CTLEBST2" value="7" />
                <propvalue name="UseFixCTLE.CTLEBST3" value="7" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL0_PLL1_108_1_1_18_12_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="FullCal_FWABIST_USE" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="-1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_LatchOffset_VDDH_to_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.LatchOffset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="JudgementType" value="UseExternalSpec_FW_Judge" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK2_MHz" value="156.25" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDL_59" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_Download_FW_VDDL_2" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_Download_FW">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="FwType" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_VCOTuningRange" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.FWABIST_VCOTuningRange">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="JudgementType" value="UseExternalSpec_FW_Judge" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK2_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_PowerUp_Reset_VDDH_57" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HiLink30_PowerUp_Reset">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="WorkingMode" value="PowerUp_Init" />
                <propvalue name="EQNNUM" value="200" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="PowerUpControlPattern" value="HILINK_R01_SD5981V100_PowerUpSeqCtrl_ALL_X1_SM_V1" />
                <propvalue name="InitPattern" value="HILINK_R01_SD5981V100_INIT_ALL_X1_SM_V1" />
                <propvalue name="ChronusPattern" value="" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_Download_FW_VDDH_1" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_Download_FW">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="PRBSMODE" value="0" />
                <propvalue name="FwType" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="CTLE_A_1" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.CTLE">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="UseFixCTLE" value="YES" />
                <propvalue name="UseFixCTLE.CTLEACTGN1" value="7" />
                <propvalue name="UseFixCTLE.CTLEACTGN2" value="7" />
                <propvalue name="UseFixCTLE.CTLEACTGN3" value="7" />
                <propvalue name="UseFixCTLE.CTLEBST1" value="7" />
                <propvalue name="UseFixCTLE.CTLEBST2" value="7" />
                <propvalue name="UseFixCTLE.CTLEBST3" value="7" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FW_CAL_156M25_28G125_1190full40_Refclk0_PLL0_PLL1_108_1_1_18_12_V1_VDDH_1" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_c" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="FullCal_FWABIST_USE" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="-1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="14.0625" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="90" />
                <propvalue name="P" value="18" />
                <propvalue name="S" value="12" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_Atb_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.FWABIST_ATB">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="JudgementType" value="UseExternalSpec_FW_Judge" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK2_MHz" value="156.25" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FWCAL_156M25_9G6875_1p5262full40_Refclk0_PLL0_108_1_1_12_8_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="4.84375" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="62" />
                <propvalue name="P" value="12" />
                <propvalue name="S" value="8" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_9G6875_1p5262full40_Refclk0_PLL0_108_1_1_12_8_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FWCAL_156M25_9G6875_1p5262full40_Refclk0_PLL1_108_1_1_12_8_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="4.84375" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="62" />
                <propvalue name="P" value="12" />
                <propvalue name="S" value="8" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_9G6875_1p5262full40_Refclk0_PLL1_108_1_1_12_8_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FWCAL_156M25_9G6875_1p5262full40_Refclk0_PLL0_108_1_1_12_8_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="4.84375" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="62" />
                <propvalue name="P" value="12" />
                <propvalue name="S" value="8" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_9G6875_1p5262full40_Refclk0_PLL0_108_1_1_12_8_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FWCAL_156M25_9G6875_1p5262full40_Refclk0_PLL1_108_1_1_12_8_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1.5" />
                <propvalue name="Kb" value="2" />
                <propvalue name="HSCLK_GHz" value="4.84375" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="62" />
                <propvalue name="P" value="12" />
                <propvalue name="S" value="8" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_9G6875_1p5262full40_Refclk0_PLL1_108_1_1_12_8_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FWCAL_156M25_27G1875_1187full40_Refclk0_PLL0_108_1_1_17_13_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.59375" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="87" />
                <propvalue name="P" value="17" />
                <propvalue name="S" value="13" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_27G1875_1187full40_Refclk0_PLL0_108_1_1_17_13_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FWCAL_156M25_27G1875_1187full40_Refclk0_PLL1_108_1_1_17_13_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.59375" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="87" />
                <propvalue name="P" value="17" />
                <propvalue name="S" value="13" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_27G1875_1187full40_Refclk0_PLL1_108_1_1_17_13_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FWCAL_156M25_27G1875_1187full40_Refclk0_PLL0_108_1_1_17_13_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.59375" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="87" />
                <propvalue name="P" value="17" />
                <propvalue name="S" value="13" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_27G1875_1187full40_Refclk0_PLL0_108_1_1_17_13_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FWCAL_156M25_27G1875_1187full40_Refclk0_PLL1_108_1_1_17_13_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.59375" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="87" />
                <propvalue name="P" value="17" />
                <propvalue name="S" value="13" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_27G1875_1187full40_Refclk0_PLL1_108_1_1_17_13_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FWCAL_156M25_26G25_1184full40_Refclk0_PLL0_108_1_1_5_2_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.59375" />
                <propvalue name="Na" value="3" />
                <propvalue name="Nb" value="28" />
                <propvalue name="P" value="5" />
                <propvalue name="S" value="2" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_26G25_1184full40_Refclk0_PLL0_108_1_1_5_2_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FWCAL_156M25_26G25_1184full40_Refclk0_PLL1_108_1_1_5_2_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.59375" />
                <propvalue name="Na" value="3" />
                <propvalue name="Nb" value="28" />
                <propvalue name="P" value="5" />
                <propvalue name="S" value="2" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_26G25_1184full40_Refclk0_PLL1_108_1_1_5_2_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FWCAL_156M25_26G25_1184full40_Refclk0_PLL0_108_1_1_5_2_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.59375" />
                <propvalue name="Na" value="3" />
                <propvalue name="Nb" value="28" />
                <propvalue name="P" value="5" />
                <propvalue name="S" value="2" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_26G25_1184full40_Refclk0_PLL0_108_1_1_5_2_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FWCAL_156M25_26G25_1184full40_Refclk0_PLL1_108_1_1_5_2_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="13.59375" />
                <propvalue name="Na" value="3" />
                <propvalue name="Nb" value="28" />
                <propvalue name="P" value="5" />
                <propvalue name="S" value="2" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_26G25_1184full40_Refclk0_PLL1_108_1_1_5_2_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_e" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FWCAL_156M25_23G4375_1175full40_Refclk0_PLL0_108_1_1_14_13_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="11.71875" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="75" />
                <propvalue name="P" value="14" />
                <propvalue name="S" value="13" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_23G4375_1175full40_Refclk0_PLL0_108_1_1_14_13_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FWCAL_156M25_23G4375_1175full40_Refclk0_PLL1_108_1_1_14_13_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="11.71875" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="75" />
                <propvalue name="P" value="14" />
                <propvalue name="S" value="13" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_23G4375_1175full40_Refclk0_PLL1_108_1_1_14_13_V1_VDDH" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDH" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FWCAL_156M25_23G4375_1175full40_Refclk0_PLL0_108_1_1_14_13_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="0" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="11.71875" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="75" />
                <propvalue name="P" value="14" />
                <propvalue name="S" value="13" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_23G4375_1175full40_Refclk0_PLL0_108_1_1_14_13_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_FWCAL_156M25_23G4375_1175full40_Refclk0_PLL1_108_1_1_14_13_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="CalibrationSection" value="SS_CS_DS" />
                <propvalue name="Full_Cal_Enable" value="BypassCal" />
                <propvalue name="Full Adaptation Enable" value="NoAdpt" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="Pll_Select" value="1" />
                <propvalue name="RefCLK_MHz" value="156.25" />
                <propvalue name="RefCLK_MHz2" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="Sdivder" value="1" />
                <propvalue name="MDiv" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="Ka" value="1" />
                <propvalue name="Kb" value="1" />
                <propvalue name="HSCLK_GHz" value="11.71875" />
                <propvalue name="Na" value="1" />
                <propvalue name="Nb" value="75" />
                <propvalue name="P" value="14" />
                <propvalue name="S" value="13" />
                <propvalue name="HsClkDistClkSpare_Bit2" value="0" />
                <propvalue name="J_40b" value="10" />
                <propvalue name="J_32b" value="8" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H30_TxRxBertPrbs_156M25_23G4375_1175full40_Refclk0_PLL1_108_1_1_14_13_V1_VDDL" type="Test" timing="TIM_H30LR" level="HilinK_H30/H16" pattern="" power="H30LR_VDDL" comment="">
        <testclass name="libHilink30LRV101_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="HiLink30_MacroList" value="_d" />
                <propvalue name="LoopBackMode" value="External" />
                <propvalue name="TxFIR.TxMain" value="57" />
                <propvalue name="TxFIR.TxPre1st" value="-6" />
                <propvalue name="TxFIR.TxPost1st" value="0" />
                <propvalue name="TxFIR.TxPre2nd" value="0" />
                <propvalue name="TxFIR.TxPost2nd" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="FreqOffset_PPM" value="100" />
                <propvalue name="UseFixCTLE" value="NO" />
                <propvalue name="PrintLvl[0~8]" value="3" />
            </propvalues>
        </testclass>
    </test>
</tests>
