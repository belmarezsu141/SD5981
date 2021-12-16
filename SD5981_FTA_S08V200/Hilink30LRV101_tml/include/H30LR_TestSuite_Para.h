#include <stdio.h>
#include <string>

using namespace std;




typedef struct stLoadJAMSetup{
    string    JAM1;
    string    JAM2;
    string    JAM3;
    string    JAM4;
    string    JAM5;
    string    JAM6;
    string    KEEP_ALIVE;
}stLoadJAMSetup;

typedef struct stHiLink30_PowerUp_Reset{
    string      mHiLink30_MacroList;
    string      WorkingMode;
    int      mEqnNum;
    int      mPRBSMODE;     
    string      PowerUpControlPattern;
    string      InitPattern;
    string mChronusPattern;
    int iPrintLvl;
}stHiLink30_PowerUp_Reset;

typedef struct stHILINK_Download_FW{
    string      HiLink30_MacroList;
    int         PRBSMODE;
    int         FwType;
    int         iPrintLvl;
}stHILINK_Download_FW;

typedef struct stHILINK_FW_CAL{
    string      mHiLink30_MacroList;
    string      sCalibrationType;
    string      iFull_Cal_en;
    string      iFullAdaptaionEn;
    string      sLoopBackMode;
    int         iPll_Select;
    double      dRefCLK_MHz;
    double      dRefCLK_MHz2;
    int         iRefclkBus;
    int         iSdivder;
    int         iMDiv;
    string      sRateMode;
    double      dKa;
    int         iKb;
    double      dHSCLK_GHz;
    int         iNa;
    int         iNb;
    int         iP;
    int         iS;
    int         iHsClkDistClkSpare_Bit2;
    int         iJ_40b;
    int         iJ_32b;
    string      sDataWidth;
    int    iPrintLvl;
}stHILINK_FW_CAL;

typedef struct stSSBandGap{
    int    iPrintLvl;
}stSSBandGap;

typedef struct stExt_2K_Resistor_Check{
    int    iPrintLvl;
}stExt_2K_Resistor_Check;

typedef struct stDPM_TEST_BY_FW{
    string    mHiLink30_MacroList;
    string    sJudgementType;
    double    dRefCLK_MHz;
    double    dRefCLK_MHz2;
    int    iPrintLvl;
}stDPM_TEST_BY_FW;


typedef struct stHILINK_FW_ADAPTATION{
    string    mHiLink30_MacroList;
    string    sCalibrationType;
    string    iFull_Cal_en;
    string    iFullAdaptaionEn;
    string    sLoopBackMode;
    int    iPll_Select;
    double    dRefCLK_MHz;
    double    dRefCLK_MHz2;
    int    iRefclkBus;
    int    iPrintLvl;
}stHILINK_FW_ADAPTATION;

typedef struct stMIN_MAX_PWR{
    string    mHiLink30_MacroList;
    int       iPll_Select;
    string    TestMode;
    string    mHVCC_Pin;
    string    mLVCC_Pin;
    string    mHVCC_Spec;
    string    mLVCC_Spec;
    string    sLoopBackMode;
    string    mPowerUpControlPattern;
    int    iPrintLvl;
}stMIN_MAX_PWR;


typedef struct stRxSigResBefCal_IFVM{
    string    mHiLink30_MacroList;
    double    mCurrentSource1_mA;
    double    mCurrentSource2_mA;
    int    iPrintLvl;
}stRxSigResBefCal_IFVM;

typedef struct stRxDiffResBefCal_VFIM{
    string    mHiLink30_MacroList;
    double    mForceV_P;
    int    iPrintLvl;
}stRxDiffResBefCal_VFIM;

typedef struct stRxResAftCal_VFIM{
    string    mHiLink30_MacroList;
    double    mRange_vol;
    double    mStep_vol;
    string    mMeasureMode;
    int    iPrintLvl;
}stRxResAftCal_VFIM;

typedef struct stRxTermVoltToGnd_AC{
    string    mHiLink30_MacroList;
    string    mPattern;
    double    miForce;
    int    iPrintLvl;
}stRxTermVoltToGnd_AC;

typedef struct stTxResAftCal{
    string    mHiLink30_MacroList;
    string    sPatternType;
    double    mcurrent1_mA;
    double    mcurrent2_mA;
    int    iPrintLvl;
}stTxResAftCal;

typedef struct stTxTermVolt{
    string    mHiLink30_MacroList;
    string    mLoopBackMode;
    string    mPattern;
    int    iPolarity;
    double    miForce;
    int    iPrintLvl;
}stTxTermVolt;

typedef struct stTxFIR_DC{
    string    mHiLink30_MacroList;
    string    mFIR_SCAN;
    string    mPattern;
    int    mRateMode;
    int    iPrintLvl;
}stTxFIR_DC;

typedef struct stVcoLockRange{
    string    mHiLink30_MacroList;
    int    iPll_Select;
    int    iRefclkBus;
    int    iPrintLvl;
}stVcoLockRange;

typedef struct stRefclkLockRange{
    string    mHiLink30_MacroList;
    int    iPll_Select;
    int    RefclkBus;
    string    PowerUpControlPattern;
    string    InitPattern;
    string    ClockSpec0;
    string    ClockSpec1;
    string    ClockSpec2;
    string    ClockSpec3;
    string    ClockSpec4;
    string    ClockSpec5;
    int    iPrintLvl;
}stRefclkLockRange;

typedef struct stClkPurity_ABIST{
    string    sHiLink30_MacroList;
    string    sLoopBackMode;
    double    dRefCLK_MHz;
    double    dRefCLK_MHz2;
    int    iTxMain;
    int    iTxPre1st;
    int    iTxPost1st;
    int    iTxPre2nd;
    int    iTxPost2nd;
    double    dDataRate;
    int    iRateMode;
    string    mUseFixCTLE;
    int    iCTLEACTGN1;
    int    iCTLEACTGN2;
    int    iCTLEACTGN3;
    int    iCTLEBST1;
    int    iCTLEBST2;
    int    iCTLEBST3;
    int    iPrintLvl;
}stClkPurity_ABIST;

typedef struct stTxRxBertPrbs15_ABIST{
    string    mHiLink30_MacroList;
    string    sLoopBackMode;
    int    iTxMain;
    int    iTxPre1st;
    int    iTxPost1st;
    int    iTxPre2nd;
    int    iTxPost2nd;
    int    iRateMode;
    int    iDataWidth;
    double    mPPMOffset;
    string    mUseFixCTLE;
    int    iPrintLvl;
}stTxRxBertPrbs15_ABIST;

typedef struct stTxEScopePrbs15_ABIST{
    string    mHiLink30_MacroList;
    string    sLoopBackMode;
    double    dRefCLK_MHz;
    double    dRefCLK_MHz2;
    int    iTxMain;
    int    iTxPre1st;
    int    iTxPost1st;
    int    iTxPre2nd;
    int    iTxPost2nd;
    double    mDataRate;
    string    mUseFixCTLE;
    string    mEyeScope;
    string    mPRBSMode;
    string    sEyeDiagMethod;
    int    iPrintLvl;
}stTxEScopePrbs15_ABIST;

typedef struct stRxSensitivity_ABIST{
    string    sHiLink30_MacroList;
    string    sLoopBackMode;
    int    iTxMain;
    int    iTxPre1st;
    int    iTxPost1st;
    int    iTxPre2nd;
    int    iTxPost2nd;
    string    mUseFixCTLE;
    int    iMAINSTOP;
    int    iMAINSTEP;
    int    iPrintLvl;
}stRxSensitivity_ABIST;

typedef struct stRxJitterTol_ABIST{
    string    mHiLink30_MacroList;
    string    sLoopBackMode;
    int    iTxMain;
    int    iTxPre1st;
    int    iTxPost1st;
    int    iTxPre2nd;
    int    iTxPost2nd;
    double    mDataRate;
    string    mUseFixCTLE;
    int    iPrintLvl;
}stRxJitterTol_ABIST;

typedef struct stRxFreqOffsetTol_ABIST{
    string    mHiLink30_MacroList;
    string    sLoopBackMode;
    int    iTxMain;
    int    iTxPre1st;
    int    iTxPost1st;
    int    iTxPre2nd;
    int    iTxPost2nd;
    int    iRateMode;
    int    iDataWidth;
    string    mUseFixCTLE;
    int    iPrintLvl;
}stRxFreqOffsetTol_ABIST;

typedef struct stRxALOS_ABIST{
    string    mHiLink30_MacroList;
    string    sLoopBackMode;
    int    iTxMain_H;
    int    iTxMain_L;
    string    mUseFixCTLE;
    int    iPrintLvl;
}stRxALOS_ABIST;

typedef struct stFuncBertPrbs15_ABIST{
    string    mHiLink30_MacroList;
    string    sLoopBackMode;
    int    iTxMain;
    int    iTxPre1st;
    int    iTxPost1st;
    int    iTxPre2nd;
    int    iTxPost2nd;
    int    iPrintLvl;
}stFuncBertPrbs15_ABIST;

typedef struct stEyeMonitorCheckPrbs31_ABIST{
    string    mHiLink30_MacroList;
    string    sLoopBackMode;
    double    dRefCLK_MHz;
    double    dRefCLK_MHz2;
    double    mDataRate;
    int    iTxMain;
    int    iTxPre1st;
    int    iTxPost1st;
    int    iTxPre2nd;
    int    iTxPost2nd;
    string    mUseFixCTLE;
    int    iPrintLvl;
}stEyeMonitorCheckPrbs31_ABIST;

typedef struct stRxStressAll_ABIST{
    string    mHiLink30_MacroList;
    string    sLoopBackMode;
    double    dRefCLK_MHz;
    double    dRefCLK_MHz2;
    int    iTxMain;
    int    iTxPre1st;
    int    iTxPost1st;
    int    iTxPre2nd;
    int    iTxPost2nd;
    double    mDataRate;
    string    mEyeScope;
    double    mFreqOffset;
    double    JitterAmpRequired;
    int    iRateMode;
    int    iDataWidth;
    string    mUseFixCTLE;
    string    sEyeDiagMethod;
    int    iPrintLvl;
}stRxStressAll_ABIST;

typedef struct stAVS_Verify_ABIST{
    string    sDPSPinList;
    string    sLoopBackMode;
    string    sHiLink30_MacroList;
    string    sSearch_Direction;
    int    iTxMain;
    int    iTxPre1st;
    int    iTxPost1st;
    int    iTxPre2nd;
    int    iTxPost2nd;
    string    mUseFixCTLE;
    double    dSearchLow;
    double    dSearchHigh;
    double    dSearchStep;
    int    iPrintLvl;
}stAVS_Verify_ABIST;

typedef struct stCTLE{
    string    mHiLink30_MacroList;
    string    mUseFixCTLE;
    int    iCTLEACTGN1;
    int    iCTLEACTGN2;
    int    iCTLEACTGN3;
    int    iCTLEBST1;
    int    iCTLEBST2;
    int    iCTLEBST3;
    int    iPrintLvl;
}stCTLE;

typedef struct stFWABIST_ATB{
    string    mHiLink30_MacroList;
    string    sJudgementType;
    double    dRefCLK_MHz;
    double    dRefCLK2_MHz;
    int    iPrintLvl;
}stFWABIST_ATB;

typedef struct stDcGain{
    string    mHiLink30_MacroList;
    string    sJudgementType;
    double    dRefCLK_MHz;
    double    dRefCLK2_MHz;
    int    iPrintLvl;
}stDcGain;

typedef struct stAlphagen{
    string    mHiLink30_MacroList;
    string    sJudgementType;
    double    dRefCLK_MHz;
    double    dRefCLK2_MHz;
    int    iPrintLvl;
}stAlphagen;

typedef struct stRegulator{
    string    mHiLink30_MacroList;
    string    sJudgementType;
    double    dRefCLK_MHz;
    double    dRefCLK2_MHz;
    int    iPrintLvl;
}stRegulator;

typedef struct stFWABIST_AdcStability{
    string    mHiLink30_MacroList;
    string    sJudgementType;
    double    dRefCLK_MHz;
    double    dRefCLK2_MHz;
    int    iPrintLvl;
}stFWABIST_AdcStability;

typedef struct stFWABIST_Comparator{
    string    mHiLink30_MacroList;
    string    sJudgementType;
    double    dRefCLK_MHz;
    double    dRefCLK2_MHz;
    int    iPrintLvl;
}stFWABIST_Comparator;

typedef struct stFWABIST_DLOS{
    string    mHiLink30_MacroList;
    string    sJudgementType;
    double    dRefCLK_MHz;
    double    dRefCLK2_MHz;
    int    iPrintLvl;
}stFWABIST_DLOS;

typedef struct stFWABIST_DFEIDAC{
    string    mHiLink30_MacroList;
    string    sJudgementType;
    double    dRefCLK_MHz;
    double    dRefCLK2_MHz;
    int    iPrintLvl;
}stFWABIST_DFEIDAC;

typedef struct stLatchOffset{
    string    mHiLink30_MacroList;
    string    sJudgementType;
    double    dRefCLK_MHz;
    double    dRefCLK2_MHz;
    int    iPrintLvl;
}stLatchOffset;

typedef struct stFWABIST_VCOTuningRange{
    string    mHiLink30_MacroList;
    string    sJudgementType;
    double    dRefCLK_MHz;
    double    dRefCLK2_MHz;
    int    iRefclkBus;
    int    iPrintLvl;
}stFWABIST_VCOTuningRange;

typedef struct stTxFIR_DC_Limit{
        double LimitL_INL;
        double LimitH_INL;                
        double LimitL_DNL;
        double LimitH_DNL;                
        double LimitL_GAIN;
        double LimitH_GAIN;                
        double LimitL_OFFSET;
        double LimitH_OFFSET;
}stTxFIR_DC_Limit;