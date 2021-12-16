<?xml version="1.0" encoding="UTF-8" ?>
<tests>
    <test name="RLY_On_PCM_1_2" type="Test" timing="" level="" pattern="" power="" comment="">
        <testclass name="libHiLink16LRV100_tml.SetUtilityLines">
            <propvalues>
                <propvalue name="type" value="UtilityLineName" />
                <propvalue name="utilityLineNameOn" value="" />
                <propvalue name="utilityLineNameOff" value="PCM_CTRL1_PCM_CTRL2_PCM_CTRL3_PCM_CTRL4_PCM_CTRL5_PCM_CTRL6" />
                <propvalue name="utilityPurpose" value="" />
                <propvalue name="utilityLineChannelOn" value="" />
                <propvalue name="utilityLineChannelOff" value="" />
                <propvalue name="waittime" value="0" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16_PCM_OUTPUT_156M25" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.PCMV200_Setup_Config">
            <propvalues>
                <propvalue name="PinList" value="PCM_CLKIN1P" />
                <propvalue name="PCM0" value="156M25" />
                <propvalue name="KEEP_ALIVE" value="ON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HILINK_R01_SD8105V100_INIT_Case1" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_RxSigResBefCal_AC_VDDN" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.RxSigResBefCal">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_RxdiffResBefCal_AC_VDDN" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.RxDiffResBefCal">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_Ext2kRes_VDDN" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.External2Kohm">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_HT" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HiLink_R01_K33277V100_INIT_Case01_X1_M_40ns_V2_burst" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_IO_N_M3_Vtl_HT" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.IO_N_M3_Vtl_HT">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="HVCC_SpecName" value="HVCC18_H16_1V8" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_10G3125_F_16_11_21_1010_81_Tx2Load_RxAC_VDDN_HT" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="10" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="8" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="0" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_1" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HILINK_R01_SD8105V100_INIT_Case1" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_10G3125_F_16_11_21_1010_81_Tx2Load_RxAC_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="10" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="8" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="0" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_RxSigResAftCal_AC_VDDN" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.RxSigResAftCal">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_RxDiffResAftCal_AC_VDDN_1" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.RxDiffResAftCal">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_RxTermVoltToGnd_DC_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.RxTermVoltToGnd">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_RxTermVoltToGnd_AC_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.RxTermVoltToGnd">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Couple_Mode" value="0" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxSigResAftCal_All0_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxResAftCal">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Data_Type" value="All0" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxSigResAftCal_All1_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxResAftCal">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Data_Type" value="All1" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100TxFIR_DC_MAIN_All0_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxFIR_DC_Dynamic">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="FIR_Tap" value="MAIN" />
                <propvalue name="Polarity" value="0" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100TxFIR_DC_MAIN_All1_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxFIR_DC_Dynamic">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="FIR_Tap" value="MAIN" />
                <propvalue name="Polarity" value="1" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100TxFIR_DC_PRE1_All0_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxFIR_DC_Dynamic">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="FIR_Tap" value="PRE1ST" />
                <propvalue name="Polarity" value="0" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100TxFIR_DC_PRE1_All1_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxFIR_DC_Dynamic">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="FIR_Tap" value="PRE1ST" />
                <propvalue name="Polarity" value="1" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100TxFIR_DC_PRE2_All0_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxFIR_DC_Dynamic">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="FIR_Tap" value="PRE2ND" />
                <propvalue name="Polarity" value="0" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100TxFIR_DC_PRE2_All1_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxFIR_DC_Dynamic">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="FIR_Tap" value="PRE2ND" />
                <propvalue name="Polarity" value="1" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100TxFIR_DC_POST1_All0_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxFIR_DC_Dynamic">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="FIR_Tap" value="POST1ST" />
                <propvalue name="Polarity" value="0" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100TxFIR_DC_POST1_All1_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxFIR_DC_Dynamic">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="FIR_Tap" value="POST1ST" />
                <propvalue name="Polarity" value="1" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100TxFIR_DC_POST2_All0_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxFIR_DC_Dynamic">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="FIR_Tap" value="POST2ND" />
                <propvalue name="Polarity" value="0" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100TxFIR_DC_POST2_All1_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxFIR_DC_Dynamic">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="FIR_Tap" value="POST2ND" />
                <propvalue name="Polarity" value="1" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_10G3125_F_16_11_21_1010_81_Tx2Load_RxAC_VDDN_1" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="10" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="8" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="0" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="0" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxTermVolt_All0_Amp0_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxTermVolt">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Polarity" value="0" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxTermVolt_All1_Amp0_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxTermVolt">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Polarity" value="1" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_10G3125_F_16_11_21_1010_81_Tx2Load_RxAC_VDDN_2" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="10" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="8" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="7" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="0" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxTermVolt_All0_Amp7_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxTermVolt">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Polarity" value="0" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxTermVolt_All1_Amp7_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxTermVolt">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Polarity" value="1" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="PCM_Bypass_H16" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.PCMV200_Setup_Config">
            <propvalues>
                <propvalue name="PinList" value="" />
                <propvalue name="PCM0" value="BYPASS" />
                <propvalue name="KEEP_ALIVE" value="OFF" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_RefclkLockRange_CS0L_Refclk0_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.RefclkLockRange">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="RLY_On_PCM_1_2_1" type="Test" timing="" level="" pattern="" power="" comment="">
        <testclass name="libHiLink16LRV100_tml.SetUtilityLines">
            <propvalues>
                <propvalue name="type" value="UtilityLineName" />
                <propvalue name="utilityLineNameOn" value="" />
                <propvalue name="utilityLineNameOff" value="PCM_CTRL1_PCM_CTRL2_PCM_CTRL3_PCM_CTRL4_PCM_CTRL5_PCM_CTRL6" />
                <propvalue name="utilityPurpose" value="" />
                <propvalue name="utilityLineChannelOn" value="" />
                <propvalue name="utilityLineChannelOff" value="" />
                <propvalue name="waittime" value="0" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16_PCM_OUTPUT_156M25_1" type="Test" timing="Tim_mpb_HILINK_STD_156M25_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.PCMV200_Setup_Config">
            <propvalues>
                <propvalue name="PinList" value="PCM_CLKIN1P" />
                <propvalue name="PCM0" value="156M25" />
                <propvalue name="KEEP_ALIVE" value="ON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_2" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HILINK_R01_SD8105V100_INIT_Case1" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_ILOLockMargin_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.ILOLockMargin">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="FWTest_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_3" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HILINK_R01_SD8105V100_INIT_Case1" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0H_Refclk0_156M25_10G3125_F_20_11_21_1010_101_Tx2Term_RxDC_VDDN_1" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="10" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="10" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_ILOFreqStability_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.ILOFreqStability">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="HVCC_PinName" value="" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_PTATCurrentStability_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.PTATCurrentStability">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16_PCM_OUTPUT_156M25_1_1" type="Test" timing="Tim_mpb_HILINK_STD_156M25_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.PCMV200_Setup_Config">
            <propvalues>
                <propvalue name="PinList" value="PCM_CLKIN1P" />
                <propvalue name="PCM0" value="156M25" />
                <propvalue name="KEEP_ALIVE" value="ON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_4" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HILINK_R01_SD8105V100_INIT_Case1" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_5G_F_20_11_22_109_201_Tx2Term_RxDC_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="2" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="9" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="20" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H15_ClkPurityFmin_5G_CSL_ABIST_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.ClkPurity_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_10G3125_F_16_11_21_1010_81_Tx2Term_RxDC_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="10" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="8" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H15_ClkPurityFmax_10G3125_CSL_ABIST_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.ClkPurity_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16_PCM_OUTPUT_156M25_3" type="Test" timing="Tim_mpb_HILINK_STD_156M25_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.PCMV200_Setup_Config">
            <propvalues>
                <propvalue name="PinList" value="PCM_CLKIN1P" />
                <propvalue name="PCM0" value="156M25" />
                <propvalue name="KEEP_ALIVE" value="ON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_2_1" type="Test" timing="Tim_mpb_HILINK_STD_156M25_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HiLink_R01_K33277V100_INIT_Case01_X1_M_40ns_V2_burst" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0H_Refclk0_156M25_10G3125_F_20_11_21_1010_101_Tx2Term_RxDC_VDDN_2" type="Test" timing="Tim_mpb_HILINK_STD_156M25_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="10" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="10" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="USER_SETTING" />
                <propvalue name="FIR_Tap" value="M10_M11" />
                <propvalue name="CTLE_setting" value="USER_SETTING" />
                <propvalue name="CTLEGAIN" value="12_12_12" />
                <propvalue name="CTLEBOOST" value="0_0_0 " />
                <propvalue name="CTLECMBAND" value="0_0_0 " />
                <propvalue name="CTLERMBAND" value="0_0_0 " />
                <propvalue name="CTLEZA" value="0_0_0 " />
                <propvalue name="CTLESQH" value="3_3_3" />
                <propvalue name="Couple_Mode" value="0" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_RxSquelchEye_10G3125_ABIST_VDDN" type="Test" timing="Tim_mpb_HILINK_STD_156M25_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.RxSquelchEye_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="LoopbackMode" value="External" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_5" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HILINK_R01_SD8105V100_INIT_Case1" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_10G3125_F_16_11_21_1010_81_Tx2Term_RxDC_VDDN_1" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="10" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="8" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxEScopePrbs15_10G3125_ABIST_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxEScopePrbs15_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxIjEScopePrbs15_10G3125_ABIST_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxIjEScopePrbs15_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_RxSensitivity_10G3125_ABIST_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.RxSensitivity_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_RxCTELTol_10G3125_ABIST_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.RxCTLETol_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_RxJitterTol_10G3125_ABIST_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.RxJitterTol_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_RxFreqOffsetTol_10G3125_ABIST_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.RxFreqOffsetTol_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H15_AVS_Verify_10G3125_ABIST_VDDN" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.AVS_VERIFICATION">
            <propvalues>
                <propvalue name="DVDD_SpecName" value="VDD" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16_PCM_OUTPUT_100MHz_8" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.PCMV200_Setup_Config">
            <propvalues>
                <propvalue name="PinList" value="PCM_CLKIN1P" />
                <propvalue name="PCM0" value="100M" />
                <propvalue name="KEEP_ALIVE" value="ON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_4_1" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HiLink_R01_K33277V100_INIT_Case01_X1_M_40ns_V2_burst" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_100M_5G_F_20_11_22_1615_201_Tx2Term_RxDC_VDDN_1" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="Refclk_MHz" value="100" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="2" />
                <propvalue name="FBDIV_P" value="16" />
                <propvalue name="FBDIV_S" value="15" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="20" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="0" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_RxALOS_TH_5G_ABIST_VDDN" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.AnalogLos_Detection_Common_Gonogo_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="Loopback_Mode" value="External" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_4_1_1" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HiLink_R01_K33277V100_INIT_Case01_X1_M_40ns_V2_burst" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_100M_2G5_H_40_11_22_1615_201_Tx2Term_RxDC_VDDN" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="Refclk_MHz" value="100" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="2" />
                <propvalue name="FBDIV_P" value="16" />
                <propvalue name="FBDIV_S" value="15" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="20" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="3" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="0" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="PCIE" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxIDLE_PCIE_2G5_DC" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxElectrical_IDLE_DC">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_4_1_1_1" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HiLink_R01_K33277V100_INIT_Case01_X1_M_40ns_V2_burst" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_100M_2G5_H_40_11_22_1615_201_Tx2Term_RxDC_VDDN_1" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="Refclk_MHz" value="100" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="2" />
                <propvalue name="FBDIV_P" value="16" />
                <propvalue name="FBDIV_S" value="15" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="20" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="3" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="0" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="PCIE" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxRxDET_PCIE_2G5_ABIST_VDDN" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxReceiver_Detection_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="Loopback_Mode" value="External" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_4_1_1_1_1" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HiLink_R01_K33277V100_INIT_Case01_X1_M_40ns_V2_burst" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_100M_2G5_H_40_11_22_1615_201_Tx2Term_RxDC_VDDN_2" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="Refclk_MHz" value="100" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="2" />
                <propvalue name="FBDIV_P" value="16" />
                <propvalue name="FBDIV_S" value="15" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="20" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="3" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="0" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="PCIE" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxRxNonDET_PCIE_2G5_ABIST_VDDN" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.TxReceiver_Detection_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="Loopback_Mode" value="External" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_4_1_1_1_1_1" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HiLink_R01_K33277V100_INIT_Case01_X1_M_40ns_V2_burst" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_100M_2G5_H_40_11_22_1615_201_Tx2Term_RxDC_VDDN_3" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="Refclk_MHz" value="100" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="2" />
                <propvalue name="FBDIV_P" value="16" />
                <propvalue name="FBDIV_S" value="15" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="20" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="3" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="0" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="PCIE" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_ALOS_TH_PCIE_2G5_ABIST_VDDN" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.AnalogLos_Detection_PCIE_Gonogo_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="Loopback_Mode" value="External" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16_PCM_OUTPUT_156M25_1_2" type="Test" timing="Tim_mpb_HILINK_STD_156M25_25M_SPEC" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.PCMV200_Setup_Config">
            <propvalues>
                <propvalue name="PinList" value="PCM_CLKIN1P" />
                <propvalue name="PCM0" value="156M25" />
                <propvalue name="KEEP_ALIVE" value="ON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_10" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HILINK_R01_SD8105V100_INIT_Case1" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_VCOILOLockRange_Ka2_Kb1_Refclk0_CS0L_VDDL" type="Test" timing="Tim_mpb_HILINK_STD_156M25_25M_SPEC" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.VCOILOLockRange">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="N_Min" value="28" />
                <propvalue name="N_Max" value="41" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_VCOILOLockRange_Ka3_Kb1_Refclk0_CS0L_VDDL" type="Test" timing="Tim_mpb_HILINK_STD_156M25_25M_SPEC" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.VCOILOLockRange">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="3" />
                <propvalue name="Kb" value="1" />
                <propvalue name="N_Min" value="19" />
                <propvalue name="N_Max" value="28" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_VCOILOLockRange_Ka2_Kb2_Refclk0_CS0L_VDDL" type="Test" timing="Tim_mpb_HILINK_STD_156M25_25M_SPEC" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.VCOILOLockRange">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="2" />
                <propvalue name="N_Min" value="28" />
                <propvalue name="N_Max" value="41" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_11" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HILINK_R01_SD8105V100_INIT_Case1" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0H_Refclk0_156M25_10G3125_F_20_11_21_1010_101_Tx2Term_RxDC_VDDL" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="10" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="10" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_VCOFreqcalCurve_CS0H_VDDL" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.VCOFreqcalCurve">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16_PCM_OUTPUT_100MHz_6_1" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.PCMV200_Setup_Config">
            <propvalues>
                <propvalue name="PinList" value="PCM_CLKIN1P" />
                <propvalue name="PCM0" value="100M" />
                <propvalue name="KEEP_ALIVE" value="ON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_13" type="Test" timing="Tim_mpb_Hilink15_STD_100MHz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HILINK_R01_SD8105V100_INIT_Case1" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_100M_2G5_H_40_11_22_1615_201_Tx2Term_RxDC_VDDL" type="Test" timing="Tim_mpb_Hilink15_STD_100MHz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="100" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="2" />
                <propvalue name="FBDIV_P" value="16" />
                <propvalue name="FBDIV_S" value="15" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="20" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="3" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxRxBertPrbs15_CS0L_Refclk0_100M_2G5_H_40_11_22_1615_201" type="Test" timing="Tim_mpb_Hilink15_STD_100MHz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_100M_5G_F_20_11_22_1615_201_Tx2Term_RxDC_VDDL" type="Test" timing="Tim_mpb_Hilink15_STD_100MHz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="100" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="2" />
                <propvalue name="FBDIV_P" value="16" />
                <propvalue name="FBDIV_S" value="15" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="20" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxRxBertPrbs15_CS0L_Refclk0_100M_5G_F_20_11_22_1615_201" type="Test" timing="Tim_mpb_Hilink15_STD_100MHz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16_PCM_OUTPUT_156M25_2" type="Test" timing="Tim_mpb_HILINK_STD_156M25_25M_SPEC" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.PCMV200_Setup_Config">
            <propvalues>
                <propvalue name="PinList" value="PCM_CLKIN1P" />
                <propvalue name="PCM0" value="156M25" />
                <propvalue name="KEEP_ALIVE" value="ON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_14" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HILINK_R01_SD8105V100_INIT_Case1" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_1G25_Q_40_11_22_109_201_Tx2Term_RxDC_VDDL" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="2" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="9" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="20" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="3" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxRxBertPrbs15_CS0L_Refclk0_156M25_1G25_Q_40_11_22_109_201" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_2G5_H_40_11_22_109_201_Tx2Term_RxDC_VDDL" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="2" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="9" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="20" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="3" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxRxBertPrbs15_CS0L_Refclk0_156M25_2G5_H_40_11_22_109_201" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_3G125_Q_40_11_21_1311_101_Tx2Term_RxDC_VDDL" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="13" />
                <propvalue name="FBDIV_S" value="11" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="10" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="3" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxRxBertPrbs15_CS0L_Refclk0_156M25_3G125_Q_40_11_21_1311_101" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_5G_F_20_11_22_109_201_Tx2Term_RxDC_VDDL" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="2" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="9" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="20" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxRxBertPrbs15_CS0L_Refclk0_156M25_5G_F_20_11_22_109_201" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_10G3125_F_16_11_21_1010_81_Tx2Term_RxDC_VDDL" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="10" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="8" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxRxBertPrbs15_CS0L_Refclk0_156M25_10G3125_F_16_11_21_1010_81" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DISABLE_KEEP_ALIVE_14" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.KEEP_ALIVE">
            <propvalues>
                <propvalue name="TestMode" value="DISABLE_ALIVE" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_15" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HILINK_R01_SD8105V100_INIT_Case1" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_10G3125_F_16_11_21_1010_81_Tx2Term_RxDC_VDDL_1" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="10" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="8" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H15_AVS_Verify_10G3125_ABIST_VDDL_VDDL" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.AVS_VERIFICATION">
            <propvalues>
                <propvalue name="DVDD_SpecName" value="VDD" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_17" type="Test" timing="Tim_mpb_Hilink15_STD_100MHz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HILINK_R01_SD8105V100_INIT_Case1" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_100M_1G6_O_20_11_21_2315_101_Tx2Term_RxDC_VDDL" type="Test" timing="Tim_mpb_Hilink15_STD_100MHz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="100" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="23" />
                <propvalue name="FBDIV_S" value="15" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="10" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="RateMode" value="3" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FFE_BERT_10G3125_Post1st_ABIST_VDDL" type="Test" timing="Tim_mpb_Hilink15_STD_100MHz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.FFE_BERT_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="FIR_Tap" value="Post1st" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FFE_BERT_10G3125_Pre1st_ABIST_VDDL" type="Test" timing="Tim_mpb_Hilink15_STD_100MHz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.FFE_BERT_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="FIR_Tap" value="Pre1st" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16_PCM_OUTPUT_100MHz_5" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDN" pattern="" power="Pow_HiLink_STD_VDDN" comment="">
        <testclass name="libHiLink16LRV100_tml.PCMV200_Setup_Config">
            <propvalues>
                <propvalue name="PinList" value="PCM_CLKIN1P" />
                <propvalue name="PCM0" value="100M" />
                <propvalue name="KEEP_ALIVE" value="ON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_16" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HiLink_R01_K33277V100_INIT_Case01_X1_M_40ns_V2_burst" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_100M_1G6_O_20_11_21_2315_101_Tx2Term_RxDC_VDDL_1" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="Refclk_MHz" value="100" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="23" />
                <propvalue name="FBDIV_S" value="15" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="10" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="RateMode" value="3" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="0" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FFE_BERT_1G6_Post1st_ABIST_VDDL" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.FFE_BERT_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="FIR_Tap" value="Post1st" />
                <propvalue name="Loopback_Mode" value="External" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FFE_BERT_1G6_Pre1st_ABIST_VDDL" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.FFE_BERT_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="FIR_Tap" value="Pre1st" />
                <propvalue name="Loopback_Mode" value="External" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16_PCM_OUTPUT_156M25_1_2_1" type="Test" timing="Tim_mpb_HILINK_STD_156M25_25M_SPEC" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.PCMV200_Setup_Config">
            <propvalues>
                <propvalue name="PinList" value="PCM_CLKIN1P" />
                <propvalue name="PCM0" value="156M25" />
                <propvalue name="KEEP_ALIVE" value="ON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_17_1" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HiLink_R01_K33277V100_INIT_Case01_X1_M_40ns_V2_burst" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_2G578125_Qtr_16_11_21_1010_81_Tx2Term_RxDC_VDDL" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="10" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="8" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_RxStrsAll_2G578125_Qtr_ABIST_VDDL" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.RxStressAll_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="FreqOffset_PPM" value="350" />
                <propvalue name="Jitter_UI" value="0.25" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_MIN_PWR_VDDH" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.MIN_MAX_PWR">
            <propvalues>
                <propvalue name="Power_Mode" value="MIN_PWR" />
                <propvalue name="HVCC_PinName" value="" />
                <propvalue name="HVCC_SpecName" value="" />
                <propvalue name="LVCC_PinName" value="" />
                <propvalue name="LVCC_SpecName" value="" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_20" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HILINK_R01_SD8105V100_INIT_Case1" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_10G3125_F_16_11_21_1010_81_Tx2Load_RxAC_VDDH" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="10" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="8" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="0" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_MAX_PWR_VDDH" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.MIN_MAX_PWR">
            <propvalues>
                <propvalue name="Power_Mode" value="MAX_PWR" />
                <propvalue name="HVCC_PinName" value="" />
                <propvalue name="HVCC_SpecName" value="" />
                <propvalue name="LVCC_PinName" value="" />
                <propvalue name="LVCC_SpecName" value="" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_21" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HILINK_R01_SD8105V100_INIT_Case1" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_17_2" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDL" pattern="" power="Pow_HiLink_STD_VDDL" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HiLink_R01_K33277V100_INIT_Case01_X1_M_40ns_V2_burst" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_22" type="Test" timing="Tim_mpb_HILINK_STD_156M25_25M_SPEC" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HiLink_R01_K33277V100_INIT_Case01_X1_M_40ns_V2_burst" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0H_Refclk0_156M25_10G3125_F_20_11_21_1010_101_Tx2Term_RxDC_VDDH" type="Test" timing="Tim_mpb_HILINK_STD_156M25_25M_SPEC" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="10" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="10" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="0" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_VCOFreqcalCurve_CS0L_VDDH" type="Test" timing="Tim_mpb_HILINK_STD_156M25_25M_SPEC" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.VCOFreqcalCurve">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="0" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16_PCM_OUTPUT_100MHz_6" type="Test" timing="Tim_mpb_HILINK_STD_100M_25M_SPEC" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.PCMV200_Setup_Config">
            <propvalues>
                <propvalue name="PinList" value="PCM_CLKIN1P" />
                <propvalue name="PCM0" value="100M" />
                <propvalue name="KEEP_ALIVE" value="ON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_24" type="Test" timing="Tim_mpb_Hilink15_STD_100MHz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HILINK_R01_SD8105V100_INIT_Case1" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_100M_2G5_H_40_11_22_1615_201_Tx2Term_RxDC_VDDH" type="Test" timing="Tim_mpb_Hilink15_STD_100MHz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="100" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="2" />
                <propvalue name="FBDIV_P" value="16" />
                <propvalue name="FBDIV_S" value="15" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="20" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="3" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxRxBertPrbs15_CS0L_Refclk0_100M_2G5_H_40_11_22_1615_201_1" type="Test" timing="Tim_mpb_Hilink15_STD_100MHz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_100M_5G_F_20_11_22_1615_201_Tx2Term_RxDC_VDDH" type="Test" timing="Tim_mpb_Hilink15_STD_100MHz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="100" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="2" />
                <propvalue name="FBDIV_P" value="16" />
                <propvalue name="FBDIV_S" value="15" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="20" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxRxBertPrbs15_CS0L_Refclk0_100M_5G_F_20_11_22_1615_201_1" type="Test" timing="Tim_mpb_Hilink15_STD_100MHz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16_PCM_OUTPUT_156M25_2_1" type="Test" timing="Tim_mpb_HILINK_STD_156M25_25M_SPEC" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.PCMV200_Setup_Config">
            <propvalues>
                <propvalue name="PinList" value="PCM_CLKIN1P" />
                <propvalue name="PCM0" value="156M25" />
                <propvalue name="KEEP_ALIVE" value="ON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_25" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HILINK_R01_SD8105V100_INIT_Case1" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_1G25_Q_40_11_22_109_201_Tx2Term_RxDC_VDDH" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="2" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="9" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="20" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="3" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxRxBertPrbs15_CS0L_Refclk0_156M25_1G25_Q_40_11_22_109_201_1" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_2G5_H_40_11_22_109_201_Tx2Term_RxDC_VDDH" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="2" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="9" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="20" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="3" />
                <propvalue name="RateMode" value="1" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxRxBertPrbs15_CS0L_Refclk0_156M25_2G5_H_40_11_22_109_201_1" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_3G125_Q_40_11_21_1311_101_Tx2Term_RxDC_VDDH" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="13" />
                <propvalue name="FBDIV_S" value="11" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="10" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="3" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxRxBertPrbs15_CS0L_Refclk0_156M25_3G125_Q_40_11_21_1311_101_1" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_5G_F_20_11_22_109_201_Tx2Term_RxDC_VDDH" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="2" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="9" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="20" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="1" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxRxBertPrbs15_CS0L_Refclk0_156M25_5G_F_20_11_22_109_201_1" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_10G3125_F_16_11_21_1010_81_Tx2Term_RxDC_VDDH" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="10" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="8" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_TxRxBertPrbs15_CS0L_Refclk0_156M25_10G3125_F_16_11_21_1010_81_1" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.TxRxBertPrbs15_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_DUT_Reset_Init_26" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_RESET">
            <propvalues>
                <propvalue name="DISCONNECT" value="NO" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="MultiSS_EN" value="NO" />
                <propvalue name="InitVectorName" value="HILINK_R01_SD8105V100_INIT_Case1" />
                <propvalue name="LoadFW_EN" value="NO" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_10G3125_F_16_11_21_1010_81_Tx2Term_RxDC_VDDH_1" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="10" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="8" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="RateMode" value="0" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H15_AVS_Verify_10G3125_ABIST_VDDH_VDDH" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.AVS_VERIFICATION">
            <propvalues>
                <propvalue name="DVDD_SpecName" value="VDD" />
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_FWCAL_CS0L_Refclk0_156M25_2G578125_Qtr_16_11_21_1010_81_Tx2Term_RxDC_VDDH" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.HILINK_FW_CAL">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Refclk_MHz" value="156.25" />
                <propvalue name="RefclkBus" value="0" />
                <propvalue name="CS_Number" value="0" />
                <propvalue name="Ka" value="2" />
                <propvalue name="Kb" value="1" />
                <propvalue name="FBDIV_P" value="10" />
                <propvalue name="FBDIV_S" value="10" />
                <propvalue name="W_Div" value="1" />
                <propvalue name="J_Div" value="8" />
                <propvalue name="M_Div" value="1" />
                <propvalue name="S_Div" value="1" />
                <propvalue name="SSCGen_EN" value="0" />
                <propvalue name="DataWidth" value="0" />
                <propvalue name="RateMode" value="2" />
                <propvalue name="TXDRV_RESSEL" value="2" />
                <propvalue name="RXTERM_RESSEL" value="1" />
                <propvalue name="TXREGDRVLVL" value="3" />
                <propvalue name="FIR_setting" value="DEFAULT_SETTING" />
                <propvalue name="CTLE_setting" value="DEFAULT_SETTING" />
                <propvalue name="Couple_Mode" value="1" />
                <propvalue name="SSCDR_EN" value="0" />
                <propvalue name="Protocol_Mode" value="COMMON" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="H16LRV100_RxStrsAll_2G578125_Qtr_ABIST_VDDH" type="Test" timing="Tim_mpb_Hilink15_STD_156M25Hz_spec" level="Lev_HiLink_STD_VDDH" pattern="" power="Pow_HiLink_STD_VDDH" comment="">
        <testclass name="libHiLink16LRV100_tml.RxStressAll_ABIST">
            <propvalues>
                <propvalue name="H16LR_MacroList" value="M10_M11" />
                <propvalue name="Loopback_Mode" value="Bump" />
                <propvalue name="FreqOffset_PPM" value="350" />
                <propvalue name="Jitter_UI" value="0.25" />
                <propvalue name="PrintLvl[0~15]" value="3" />
            </propvalues>
        </testclass>
    </test>
</tests>
