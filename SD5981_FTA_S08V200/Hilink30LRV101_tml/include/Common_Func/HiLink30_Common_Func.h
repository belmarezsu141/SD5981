////////////////////////////////////////////////////////////////////////////////
// Description:                                                               //
// This head file is to define APIs, which to check error count with internal //
// prbs checker and plot eye.                                                 //
////////////////////////////////////////////////////////////////////////////////

#ifndef HILINK30_COMMON_FUNC_H_
#define HILINK30_COMMON_FUNC_H_

#include <Common_Func/System_Common_Func.h>
#include <HILINK_DRIVE/FWABIST_REGISTER_Base.h>
#include <HILINK_DC/Execute_functions.h>

#include <H30LR_TestSuite_Para.h>
#include <H30LR_TestSuite_Para_extern.h>

#if !(defined NOGDI || defined _WINGDI_H)
        #define NOGDI
#endif

typedef std::vector<int> SiteInt;
typedef std::vector<double> SiteDouble;
typedef std::vector<bool> SiteBool;
typedef std::vector<std::string> SiteString;
//#include "winsock2.h" //masked by tony 20210817
//
//#include "mapi.hpp"
using namespace std;
extern SITE_INT CSR_CHECK_JUDGE_RESULT;
extern SITE_INT H30_FailBin_Flag;
extern int m_TestNumber;
extern int m_HardBin;
extern int m_SoftBin;
//
//extern INT Daughter_LB_Res;
//
//extern vector<ARRAY_D>	vGain_Mode0_All1_Main;
//extern vector<ARRAY_D>	vOffset_Mode0_All1_Main;
//extern vector<ARRAY_D>	vGain_Mode1_All1_Main;
//extern vector<ARRAY_D>	vOffset_Mode1_All1_Main;
//
//extern vector<ARRAY_D>	vGain_Mode0_All1_Pre1st;
//extern vector<ARRAY_D>	vOffset_Mode0_All1_Pre1st;
//extern vector<ARRAY_D>	vGain_Mode1_All1_Post1st;
//extern vector<ARRAY_D>	vOffset_Mode1_All1_Post1st;
//
//extern vector<ARRAY_D>	vGain_Mode0_All1_Pre2nd;
//extern vector<ARRAY_D>	vOffset_Mode0_All1_Pre2nd;
//extern vector<ARRAY_D>	vGain_Mode1_All1_Post2nd;
//extern vector<ARRAY_D>	vOffset_Mode1_All1_Post2nd;

typedef struct {
	DOUBLE  dmax;
	DOUBLE  dmin;
	DOUBLE  damax;
	DOUBLE  imax;
        DOUBLE  imin;
        DOUBLE  iamax;
        INT     dmax_index;
        INT     dmin_index;
        INT     damax_index;
        INT     imax_index;
        INT     imin_index;
        INT     iamax_index;
} LINEARtype;

typedef enum {
    MIN_RMS_LSB
} ILEtype;


typedef struct {
	int jitcontrol;
	int jitFreq;
	int jitamp;
	int ppmgen;
} Stress_Setting;

typedef enum {
	Ipath, Qpath, IBpath, QBpath
} SHOWPHASE;

typedef enum {
	SS,PLL
} PLLBYPASSMODE;

typedef enum {
	DISCNCT,CNCT
} REFCLKCTRL;

// CSR atomic operation and standard output




//The following sub functions are all from PUG1.0.4
//extern vector<ARRAY_I> vCTLEOFST1;
//extern vector<ARRAY_I> vCTLEOFST2;
//extern vector<ARRAY_I> vCTLEOFST3;
//extern vector<ARRAY_I> vCTLEOFST4;
//extern vector<ARRAY_I> vCTLEOFST5;
//extern vector<ARRAY_I> vCTLEOFST6;
//extern vector<ARRAY_I> vCTLEOFST7;
//extern vector<ARRAY_I> vCTLEACTGN1;
//extern vector<ARRAY_I> vCTLEACTGN2;
//extern vector<ARRAY_I> vCTLEACTGN3;
//extern vector<ARRAY_I> vRXCTLEEST1BOOST;
//extern vector<ARRAY_I> vRXCTLEEST2BOOST;
//extern vector<ARRAY_I> vRXCTLEEST3BOOST;
//extern vector<ARRAY_I> vDFEIEVNSUMOFST;
//extern vector<ARRAY_I> vDFEQEVNSUMOFST;
//extern vector<ARRAY_I> vDFEIODDSUMOFST;
//extern vector<ARRAY_I> vDFEQODDSUMOFST;

extern int csanahwversion;
// cs digital version, only one
extern int csdighwversion;
// ds analog version.
extern int dsanahwversion;
// ds digital version, only one
extern int dsdighwversion;
// ss analog version, if ss exist in macro, the version is all 0s, otherwise, the version is all 1s
extern int ssanahwversion;
extern int RxCeCmSkewCalBypass;


typedef struct
{
	unsigned int uiCTLEACTGN1;
	unsigned int uiCTLEACTGN2;
	unsigned int uiCTLEACTGN3;
	unsigned int uiCTLEBST1;
	unsigned int uiCTLEBST2;
	unsigned int uiCTLEBST3;
	unsigned int uiCTLESQH1;
	unsigned int uiCTLESQH2;
	unsigned int uiCTLESQH3;
	unsigned int uiCTLEZA1;
	unsigned int uiCTLEZA2;
	unsigned int uiCTLEZA3;
	unsigned int uiCTLERMBAND1;
	unsigned int uiCTLERMBAND2;
	unsigned int uiCTLERMBAND3;
	unsigned int uiCTLECMBAND1;
	unsigned int uiCTLECMBAND2;
	unsigned int uiCTLECMBAND3;
	unsigned int uiCTLEHFZEN1;
	unsigned int uiCTLEHFZEN2;
	unsigned int uiCTLEHFZEN3;
	unsigned int uiCTLEREFSEL;
	unsigned int uiCPHSOFFT;
    unsigned int uiCTLEloadsel;
} CtleResultPerLane;

//typedef struct
//{
//	LANE_UINT uiCTLEACTGN1;
//	LANE_UINT uiCTLEACTGN2;
//	LANE_UINT uiCTLEACTGN3;
//	LANE_UINT uiCTLEBST1;
//	LANE_UINT uiCTLEBST2;
//	LANE_UINT uiCTLEBST3;
//	LANE_UINT uiCTLESQH1;
//	LANE_UINT uiCTLESQH2;
//	LANE_UINT uiCTLESQH3;
//	LANE_UINT uiCTLEZA1;
//	LANE_UINT uiCTLEZA2;
//	LANE_UINT uiCTLEZA3;
//	LANE_UINT uiCTLERMBAND1;
//	LANE_UINT uiCTLERMBAND2;
//	LANE_UINT uiCTLERMBAND3;
//	LANE_UINT uiCTLECMBAND1;
//	LANE_UINT uiCTLECMBAND2;
//	LANE_UINT uiCTLECMBAND3;
//	LANE_UINT uiCTLEHFZEN1;
//	LANE_UINT uiCTLEHFZEN2;
//	LANE_UINT uiCTLEHFZEN3;
//	LANE_UINT uiCTLEREFSEL;
//	LANE_UINT uiCPHSOFFT;
//    LANE_UINT uiCTLEloadsel;
//} Ctle_PerLane;
//
//typedef struct
//{
//	LANE_INT uiDFEFXTAP2;
//	LANE_INT uiDFEFXTAP3;
//	LANE_INT uiDFEFXTAP4;
//	LANE_INT uiDFEFXTAP5;
//	LANE_INT uiDFEFXTAP6;
//	LANE_INT uiDFEFXTAP7;
//	LANE_INT uiDFEFXTAP8;
//	LANE_INT uiDFEFXTAP9;
//	LANE_INT uiDFEMVTAP1;
//	LANE_INT uiDFEMVTAP2;
//	LANE_INT uiDFEMVTAP3;
//	LANE_INT uiDFEMVTAP4;
//	LANE_INT uiDFEMVTAP5;
//	LANE_INT uiDFEMVTAP6;
//	LANE_INT uiDFEFXTAP1CEN;
//	LANE_INT uiDFEFXTAP1EDG;
//
//} DFE_PerLane;

typedef struct
{
	unsigned int uiDFEFXTAP2;
	unsigned int uiDFEFXTAP3;
	unsigned int uiDFEFXTAP4;
	unsigned int uiDFEFXTAP5;
	unsigned int uiDFEFXTAP6;
	unsigned int uiDFEFXTAP7;
	unsigned int uiDFEFXTAP8;
	unsigned int uiDFEFXTAP9;
	unsigned int uiDFEMVTAP1;
	unsigned int uiDFEMVTAP2;
	unsigned int uiDFEMVTAP3;
	unsigned int uiDFEMVTAP4;
	unsigned int uiDFEMVTAP5;
	unsigned int uiDFEMVTAP6;
	unsigned int uiDFEFXTAP1CEN;
	unsigned int uiDFEFXTAP1EDG;

} DFEResultPerLane;
typedef struct
{
	string BypassCal;
	string FullCal;
	string FullCal_FWABIST_USE;
	string REFLOCKRANGE_USE;
} FULLCALPARA;
typedef struct
{
	string BypassAdpt;
	string FullAdpt;
	string NoAdpt;
} ADPTPARA;
const FULLCALPARA FullCalPara={
	"BypassCal",
	"FullCal",
	"FullCal_FWABIST_USE",
	"REFLOCKRANGE_USE"
};
const ADPTPARA  AdptPara = {
		"BypassAdpt",
		"FullAdpt",
		"NoAdpt"
};

//extern vector<vector<DFEResultPerLane> >  vDfeResultPerMacroPerLane;
//extern vector<vector<CtleResultPerLane> > vCtleResultPerMacroPerLane;


//HiLink StartUp
//MultiSite


//HiLinkReset and PowerUp/down
bool MacroPowerUp(MACRO_LANE_SEL& MacroLane_Sel,const STRING& PowerUpPattern, const STRING& InitPattern, const string workingmode);
void MacroPowerDown(MACRO_LANE_SEL& vMacroLane_Sel, const STRING& PowerUpPattern);
void MacroPowerDown(UINT iMacroIndex, const STRING& PowerUpPattern);
bool MacroDsPowerUp (MACRO_LANE_SEL& vMacroLane_Sel);
bool MacroDsPowerDown (MACRO_LANE_SEL& vMacroLane_Sel);
bool RxPowerUpDown(unsigned int iMacroID,unsigned int iLaneIndex,unsigned int iPowerType);
bool TxPowerUpDown(unsigned int iMacroID,unsigned int iLaneIndex,unsigned int iPowerType);
bool DsPowerUpWiClkDis(unsigned int uiMacroID,int iLaneIndex);
bool DsPowerUpWoClkDis(MACRO_LANE_SEL& vMacroLane_Sel);
bool DsPowerDownWoClkDis(MACRO_LANE_SEL& vMacroLane_Sel);
bool DsPowerDownWiClkDis(int MacroID,int LaneIndex);

//Loading Frimware to SRAM
void LoadFirmwareToSram(MACRO_LANE_SEL& MacroLane_Sel, INT iPRBSMODE,INT iFWType);
void LoadFirmwareToSram(MACRO_LANE_SEL& MacroLane_Sel, STRING FW_Name,INT FW_Length);

//Clockslice Configuration before Calibration
bool CsPllPowerup(MACRO_LANE_SEL& MacroLane_Sel, INT pllIndex);
bool CsPllPowerDown(MACRO_LANE_SEL& MacroLane_Sel, INT pllIndex);
void CSConfigurationBeforeCalibration_SSConfig(MACRO_LANE_SEL& MacroLane_Sel, CUSTPARA &CUSTpara, SSPARA &SSpara);
void CSConfigurationBeforeCalibration_PLLConfig(MACRO_LANE_SEL& MacroLane_Sel, CUSTPARA &CUSTpara, SSPARA &SSpara , CSPARA &CSpara);


// Clear CS DS API
void Clear_CS_API();
void Clear_DS_API(MACRO_LANE_SEL& MacroLane_Sel);

//Clockslice Calibration
void CsFwCalibration(MACRO_LANE_SEL& MacroLane_Sel, CUSTPARA &CUSTpara, SSPARA &SSpara, CSPARA &CSpara, MACRO_INT &mCS_Cal_MacroResult, MACRO_INT &mCsCalVcoLockPerMacro, const string full_cal_en, const bool ss_cal_only_en);

//Clockslice Configuration after Calibration
void CSConfigurationAfterCalibration(MACRO_LANE_SEL& MacroLane_Sel);

//Dataslice Configuration before Calibration
void DsConfigurationBeforeCalibration(MACRO_LANE_SEL& vMacroLane_Sel, CSPARA& CSpara,SSPARA& SSpara,CUSTPARA& CUSTpara,const string full_cal_en);
void SetTxFir(MACRO_LANE_SEL& vMacroLane_Sel,CUSTPARA& CUSTpara);
void SetTxFir(CUSTPARA& CUSTpara);

//Dataslice Calibration
void DsFwCalibration(MACRO_LANE_SEL& MacroLane_Sel, CUSTPARA &CUSTpara, SSPARA &SSpara, CSPARA &CSpara, MACRO_INT &mDS_Cal_MacroResult, const string full_cal_en);

//Dataslice Configuration after Calibration
void DsConfigurationAfterCalibration();

//Calibration
void HiLink30_FW_CAL(MACRO_LANE_SEL& MacroLane_Sel, CUSTPARA& CUSTpara, SSPARA& SSpara, CSPARA& CSpara, MACRO_INT &mCS_Cal_MacroResult, MACRO_INT &mCsCalVcoLockPerMacro, MACRO_INT &mDS_Cal_MacroResult, STRING sCalibrationType, const string full_cal_en,INT iSSCalOnce = 1);
void FWreadDefaultRegisters2CSR(MACRO_LANE_SEL& MacroLane_Sel);

//Running Adaptation Firmware
void ATE_CTLE_Adaptation(MACRO_LANE_SEL& vMacroLane_Sel, CUSTPARA& CUSTpara,DOUBLE dRefclkMHz,DOUBLE dRefclkMHz2, MACRO_INT &mDS_Cal_MacroResult,STRING& sLoopBackMode);
void ATE_CTLE_Bypass_Adaptation(MACRO_LANE_SEL& vMacroLane_Sel, CUSTPARA& CUSTpara,DOUBLE dRefclkMHz,DOUBLE dRefclkMHz2, MACRO_INT &mDS_Cal_MacroResult,STRING& sLoopBackMode);
//DFx&Utilities

//DC
void RefClkCtrl(REFCLKCTRL refclkctrl);

//TX2RX
void EnableTxToRxParLpbk();
void DisableTxToRxParLpbk();
bool EnableTxToRxSerLpbk(MACRO_LANE_SEL &MacroLane_Sel,STRING &LoopBackMode,CUSTPARA& CUSTpara,DSAPI &DSApi);
void DisableTxToRxSerLpbk(MACRO_LANE_SEL &MacroLane_Sel,CUSTPARA& CUSTpara,DSAPI &DSApi);
bool EnableRxToTxParLpbk(MACRO_LANE_SEL &MacroLane_Sel,DSAPI &DSApi);
bool DisableRxToTxParLpbk(MACRO_LANE_SEL &MacroLane_Sel,DSAPI &DSApi);
void EnableTxPrbsGen(STRING sPRBSPatternType, INT iCustomerPattern = 0xaaaa);//Change from 0x5555 to 0xaaaa for FWABIST
void DisableTxPrbsGen();
void EnableRxPrbsCheck(STRING sPRBSPatternType);
void LoopBack_Setting(string& sLoopBackMode,MACRO_LANE_SEL &MacroLane_Sel,CUSTPARA& CUSTpara);
void SetTxBistPpmJitter(Stress_Setting& Stress_Set);
int FreqOffset(DOUBLE& FreqOffsetRequired,INT JitControl = 1);
struct JI JitterInjection(DOUBLE& DataRate, DOUBLE& JitterAmpRequired,INT JitControl = 1);

//SetCtle
void InitCtlePerMacroPerLane(MACRO_LANE_SEL& vMacroLane_Sel);
INT sigdet_los_check(const MACRO_LANE_SEL& MacroLane_Sel, LANE_DOUBLE& Sigdet_LOS, STRING sTestMode, const STRING sCheckMode);
INT sigdet_los_check(const MACRO_LANE_SEL& MacroLane_Sel, vector<ARRAY_D>& vSigdet_LOS_ALL1, vector<ARRAY_D>& vSigdet_LOS_ALL0, string sTestMode);

//Bert
void Read_Bert(MACRO_LANE_SEL& vMacroLane_Sel,LANE_DOUBLE &vErrorCount,STRING sTestMode="ABIST",bool AntiFool=false,STRING spRXLabe="",LONG lCycleNum=0,DOUBLE dWaitTime=1.0);

//Eye Diagram
unsigned int Check_EMReady(int iMacroID, int iLaneID, SITE_INT& result);
bool Check_EMReady(MACRO_LANE_SEL& vMacroLane_Sel,SITE_INT& result);
unsigned int Check_EyeScanStart(int iMacroID, int iLaneID, SITE_INT& result);
bool Check_EyeScanStart(MACRO_LANE_SEL& vMacroLane_Sel,SITE_INT& result);

//bool GeneralEyeScan(MACRO_LANE_SEL& vMacroLane_Sel, unsigned int iEyeScanMode, unsigned int iEyeScanWin, LANE_INT iPhsofst, LANE_INT iVolOfst, unsigned int iAvgTime, unsigned int iMonSlcSel, LANE_INT& iEyeCornor0, LANE_INT& iEyeCornor1);
bool GeneralEyeScan(MACRO_LANE_SEL& vMacroLane_Sel, unsigned int iEyeScanMode, unsigned int iEyeScanWin, LANE_INT iPhsofst, LANE_INT iVolOfst, unsigned int iAvgTime, unsigned int iMonSlcSel, LANE_INT& iEyeCornor0, LANE_INT& iEyeCornor1, STRING sTestMode = "ABIST",STRING spRXLabe = "",LONG lCycleNum = 1);
bool GetEyeDiagram(MACRO_LANE_SEL& vMacroLane_Sel, int iEyeScanMode, int iEyeScanWin, int iMonSlcSel, unsigned int itap1Inside, unsigned int itap1Type, STRING sTestMode = "ABIST",STRING spRXLabe = "",LONG lCycleNum = 1);//, int iEyeDiagram0[HILINK_MACRO_NUM][HILINK_MAX_LANE_NUM][512], int iEyeDiagram1[HILINK_MACRO_NUM][HILINK_MAX_LANE_NUM][512]);

bool GetFourPointEyeDiagram(MACRO_LANE_SEL& vMacroLane_Sel, unsigned int iShowInner, unsigned int iEyeScanWin, unsigned int iMonSlcSel, unsigned int itap1Inside, unsigned int itap1Type, LANE_UINT& vEyeWidth, LANE_UINT& vEyeHeight);
bool AteFwFourPointEyeScan(MACRO_LANE_SEL& MacroLane_Sel, DOUBLE dRefclkMHz, DOUBLE dRefclkMHz2, DOUBLE dDataRate,LANE_UINT& EyeWidth1, LANE_UINT& EyeHeight1, LANE_UINT& EyeWidth2, LANE_UINT& EyeHeight2,STRING sTestMode = "ABIST",STRING spRXLabe = "",LONG lCycleNum = 1);
bool AteFwEyeWidthScan(MACRO_LANE_SEL& MacroLane_Sel, DOUBLE dRefclkMHz,DOUBLE dRefclkMHz2, LANE_UINT& vEyeWidthMin, LANE_UINT& vEyeWidthMax);

//Alos
void EnableAlos(const STRING& JtagContext);
void DisableAlos();

//HSI TEST
void Rx_ATE_Setup(MACRO_LANE_SEL& MacroLane_Sel, vector<int> vCTLESetting, string& sUseFixCTLE, string& patternType);
void RxSearch_CheckClockMonitor(double dDataRate, string sPattern_Type, vector<string> vConnectedLanes);

//ADC
bool GetTemperature(MACRO_LANE_SEL& vMacroLane_Sel,MACRO_DOUBLE &iTemperature);
void SsGetAdcData(MACRO_LANE_SEL &MacroLane_Sel,MACRO_DOUBLE &adcdataresult,unsigned int adcFreq, unsigned int useVbgAsRef, unsigned int decmFactor, unsigned int refVoltage,unsigned int avgTime, unsigned int returnType,unsigned int adcinputsel);
void CsGetAdcData(MACRO_LANE_SEL &MacroLane_Sel,MACRO_DOUBLE &adcdataresult,unsigned int adcFreq, unsigned int useVbgAsRef, unsigned int decmFactor, unsigned int refVoltage,unsigned int avgTime, unsigned int returnType);
bool Check_CSTopFsm_Cal_Done(INT MacroID, SITE_INT& result);
bool Check_SSTopFsm_Cal_Done(INT MacroID, SITE_INT& result);
void Check_Top_Fsm_Done(INT MacroID,EXPECT_RESULT &result);
void Check_Top_Fsm_Done(MACRO_LANE_SEL& MacroLane_Sel,EXPECT_RESULT &result);


bool Check_SSDFCOMPSTATUS(MACRO_LANE_SEL &MacroLane_Sel,MACRO_INT compStatusPre);
bool Check_CSDFCOMPSTATUS(MACRO_LANE_SEL &MacroLane_Sel,MACRO_INT compStatusPre);

//JUDGEMENT

//GetMosCornerSw
void GetMosCornerSw(MACRO_LANE_SEL &MacroLane_Sel, unsigned int mosType,MACRO_DOUBLE &pmosCorner, MACRO_DOUBLE &nmosCorner, MACRO_DOUBLE &cmosCorner,MACRO_DOUBLE &temperature, INT BypassGetTemp);
void GetCsMosCornerSw(MACRO_LANE_SEL &MacroLane_Sel,MACRO_DOUBLE &pmosCorner, MACRO_DOUBLE &nmosCorner, MACRO_DOUBLE &cmosCorner,MACRO_DOUBLE &temperature, INT BypassGetTemp);

//Others
void get_pinlists(const MACRO_LANE_SEL& MacroLane_Sel, STRING& mPinList_P, STRING& mPinList_N, STRING& mPinList, STRING PinType = "RX");
void Antiproof_SumFIR(CUSTPARA &custpara);

//new function add by shaoxue 20170513

void Config_RefClk_CoreClk(UINT iRefclk0_freqm100, UINT iRefclk1_freqm100);
void SRAM_READ_BY_WORD(MACRO_LANE_SEL& MacroLane_Sel, INT Address,MACRO_DOUBLE& FWAbist_Result,UINT convertFlag=1,UINT sign=1);
bool DPM_Run(MACRO_LANE_SEL& MacroLane_Sel, UINT iRefclk0_freqm100,UINT iRefclk1_freqm100) ;
void PrinfToEdf_FWAbist(ostringstream& TestDatalog);

void Dump_SRAM_ByWord(MACRO_LANE_SEL& MacroLane_Sel);
void EnableAlos(MACRO_LANE_SEL& MacroLane_Sel, const STRING& JtagContext);

#define CSR_VAL -1
void init_csr_check_list(T_HILINK_CSR_CHECK& check_list);
void check_csr(vector<T_CHECK_DATA>& target,int csr,int data=CSR_VAL,int mask=0x0000);


//CSR atomic operation

void SEGMENT_READ_MACRO(const MACRO_LANE_SEL& MacroLane_Sel,const T_REG_INFO_EX& reg_info_ex,MACRO_DOUBLE& permacro_value);
void SEGMENT_EXPECT(const MACRO_LANE_SEL& MacroLane_Sel,const string& MacroOrLane,const T_REG_INFO_EX& reg_info_ex,UINT value,EXPECT_RESULT& ExpectResult);
void WaitDone(const MACRO_LANE_SEL& MacroLane_Sel,const string& MacroOrLane, const T_REG_INFO_EX& reg_info_ex,UINT value, INT MaxCheckCount, DOUBLE IntervalTime_ms, EXPECT_RESULT& ExpectResult);
void WaitDoneMacro(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,UINT value, INT MaxCheckCount, DOUBLE IntervalTime_ms, EXPECT_RESULT& ExpectResult);
void WaitDoneMacro_Value_Update(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,MACRO_DOUBLE Expect_Value, INT MaxCheckCount, DOUBLE IntervalTime_ms, EXPECT_RESULT& ExpectResult);

//DCD
bool DsDcdReCalib(MACRO_LANE_SEL &MacroLane_Sel,DSAPI &DSApi);
void CsCalibrationBypassConfig(CSAPI &CSApi);
void DsCalibrationBypassConfig(DSAPI &DSApi);
void DsAdaptationBypassConfig(DSAPI_Adaptation& DSapi_Adaptation);

//CSR verify

//FWABIST
void WritePerLaneSpecToSram(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE, const STRING& useExternalRAM = "NO");
void WritePerMacroSpecToSram(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE);
void WriteSingleSpecToSram(const MACRO_LANE_SEL& MacroLane_Sel, INT SpecHigh_Address, DOUBLE SpecHigh_Data, INT SpecLow_Address, DOUBLE SpecLow_Data, INT SpecWrittenRate);

void Config_RefClk_CoreClk(UINT iRefclk0_freqm100, UINT iRefclk1_freqm100);
void ReleaseMCU(MACRO_LANE_SEL& MacroLane_Sel);
void ResetMCU(MACRO_LANE_SEL& MacroLane_Sel);

void FW_ABIST_RESULT_READ(const MACRO_LANE_SEL& MacroLane_Sel, INT Address, MACRO_DOUBLE& FWAbist_Result);
void PrinfDataToEdf_FWAbist(ostringstream& TestDatalog);
void PrinfToEdf_FWAbist(ostringstream& TestDatalog);
void FW_ABIST_READ_HVCC(const MACRO_LANE_SEL& MacroLane_Sel, INT DSStartAddress, INT DSIncreaseStep, INT CSStartAddress, MACRO_DOUBLE& CSInfo, LANE_DOUBLE& DsInfo);
void FW_ABIST_READ_ErrorMessage(const MACRO_LANE_SEL& MacroLane_Sel, INT DSStartAddress, INT DSIncreaseStep, INT CSStartAddress, MACRO_DOUBLE& CSInfo, LANE_DOUBLE& DsInfo);
void FW_ABIST_READ_LANEDOUBLE(const MACRO_LANE_SEL& MacroLane_Sel, INT DSStartAddress, INT DSIncreaseStep, LANE_DOUBLE& DsInfo);
void FW_ABIST_READ_LANEDOUBLE(const MACRO_LANE_SEL& MacroLane_Sel, INT DSStartAddress, INT DSIncreaseStep, LANE_DOUBLE& DsInfo, LANE_DOUBLE& Half_HVCC_Public_Volt);


void FWAbistHeader(const MACRO_LANE_SEL& MacroLane_Sel, unsigned int macroIndex, STRING CalFW, STRING TestFW, STRING TestItem, ostringstream&  TestDatalog);

void SRAM_READ(const UINT& MacroID, INT StartAddress, INT StopAddress, ostringstream& SramDataLog, bool Dump_Spec = false);
void SEGMENT_EXPECT_MACRO(const MACRO_LANE_SEL& MacroLane_Sel,const T_REG_INFO_EX& reg_info_ex,UINT value,EXPECT_RESULT& ExpectResult);

void FW_ABIST_CSArrayD_ReadBack(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE);
void FW_ABIST_DSArrayD_ReadBack(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE);
void FW_ABIST_SingleSpec_ReadBack(const MACRO_LANE_SEL& MacroLane_Sel, UINT SpecHigh_Address, UINT SpecLow_Address);

void HiLink_PerLane_Judge_DcGain(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname, LANE_DOUBLE& TempResult, LANE_DOUBLE& TemperatureCode,JUDGE_PIN Judge_Pin = PIN_TXP);
void HiLink_PerMacro_Judge_Regulator(const MACRO_LANE_SEL& MacroLane_Sel,MACRO_DOUBLE& NodeCode, MACRO_DOUBLE& NodeVolt, string sJudgeNameInTable_NodeCode, string sJudgeNameInTable_NodeVolt, JUDGE_PIN Judge_Pin = PIN_TXP);
void HiLink_PerMacroCSCalArrayD_Judge(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE, MACRO_ARRAY_D& TempResult, JUDGE_PIN Judge_Pin = PIN_TXP);
void HiLink_PerLaneCalArrayD_Judge(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE, LANE_ARRAY_D& TempResult, JUDGE_PIN Judge_Pin = PIN_TXP);
void HiLink_PerMacroCSArrayD_Judge(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE, MACRO_ARRAY_D& TempResult, JUDGE_PIN Judge_Pin = PIN_TXP);
void HiLink_PerLaneArrayD_Judge(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE, LANE_ARRAY_D& TempResult, JUDGE_PIN Judge_Pin = PIN_TXP);

string LocalLimitCompare(string &OPL,double &LowLimit,string &OPH,double &HiLimit,double &Result);
void FWAbist_Calculate_Table_Processing(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE, MACRO_ARRAY_D& SS_Calculate_Output,
		MACRO_ARRAY_D& CS_Calculate_Output,	LANE_ARRAY_D&  DS_Calculate_Output, MACRO_ARRAY_MAP& SS_REG_Node_Value, MACRO_ARRAY_MAP&  CS_REG_Node_Value,
		LANE_ARRAY_MAP& DS_REG_Node_Value);

void HiLink_PerLane_Judge_Regulator(const MACRO_LANE_SEL& MacroLane_Sel,LANE_DOUBLE& NodeCode, LANE_DOUBLE& NodeVolt, string sJudgeNameInTable_NodeCode, string sJudgeNameInTable_NodeVolt, JUDGE_PIN Judge_Pin = PIN_TXP);
void FW_ABIST_SSArrayD_ReadBack(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE);
void HiLink_PerMacroSSArrayD_Judge(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE, MACRO_ARRAY_D& TempResult, JUDGE_PIN Judge_Pin = PIN_TXP);
void HiLink_PerMacroSSCalArrayD_Judge(const MACRO_LANE_SEL& MacroLane_Sel, FWABIST_REGISTER_Base& FWABIST_REG_BASE, MACRO_ARRAY_D& TempResult, JUDGE_PIN Judge_Pin= PIN_TXP);

void CSR_READ(const MACRO_LANE_SEL& MacroLane_Sel,HILINK_Regs_Base& reg, const INT& csr,MACRO_INT& permacro_value);
void CSR_READ(const MACRO_LANE_SEL& MacroLane_Sel, HILINK_Regs_Base& reg, const INT& csr,LANE_INT& perlane_value);
void FWreadAllRegisters2CSR_ForDebug(MACRO_LANE_SEL& MacroLane_Sel);

void FWAbist_PreJudge(const MACRO_LANE_SEL& MacroLane_Sel,MACRO_DOUBLE& permacro_value, bool& PreJudge_Result);

void ALL_CSR_ReadBack_TO_FILE_Debug(const MACRO_LANE_SEL& MacroLane_Sel,const string& file_name);
void ALL_CS_CSR_ReadBack_TO_FILE_Debug(const MACRO_LANE_SEL& MacroLane_Sel,const string& file_name);
void ALL_DS_CSR_ReadBack_TO_FILE_Debug(const MACRO_LANE_SEL& MacroLane_Sel,const string& file_name);
void ALL_API_CSR_ReadBack_TO_FILE_Debug(const MACRO_LANE_SEL& MacroLane_Sel,const string& file_name);

void HiLink_PerLane_Judge( const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname,double LimitL, LANE_DOUBLE& TempResult, double LimitH,JUDGE_PIN Judge_Pin = PIN_TXP);
void HiLink_PerLane_Judge( const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname,double LimitL, LANE_INT& TempResult,double LimitH,JUDGE_PIN Judge_Pin = PIN_TXP);
void HiLink_PerLane_Judge( const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname,double LimitL, LANE_UINT& TempResult,double LimitH,JUDGE_PIN Judge_Pin = PIN_TXP);
void HiLink_PerMacro_Judge(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname, double LimitL, MACRO_DOUBLE& TempResult,double LimitH, JUDGE_PIN Judge_Pin = PIN_TXP);
void HiLink_PerMacro_Judge(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname,double LimitL,  MACRO_INT& TempResult,double LimitH, JUDGE_PIN Judge_Pin = PIN_TXP);
void HiLink_PerSite_Judge(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname, SITE_DOUBLE& TempResult, JUDGE_PIN Judge_Pin = PIN_TXP);
void judgeAndLog_ParametricTest(INT SiteID, string testname, string Macro_Lane_Name,double LimitL,double TestVal,double LimitH,int testNumber);
void judgeAndLog_ParametricTest_DC(string TestNameLimit,double TestVal,double LimitL,double LimitH);
#endif /* HILINK30_COMMON_FUNC_H_ */
bool Update_LaneData_InTolerance(const MACRO_LANE_SEL& MacroLane_Sel, const DOUBLE& SpecValue, LANE_DOUBLE& ErrorCount, LANE_DOUBLE& TempResult, LANE_INT& FindFlag);
bool Update_LaneData_InTolerance(const MACRO_LANE_SEL& MacroLane_Sel, const INT& SpecValue,    LANE_DOUBLE& ErrorCount, LANE_DOUBLE& TempResult, LANE_INT& FindFlag);
void SetTestBin();
