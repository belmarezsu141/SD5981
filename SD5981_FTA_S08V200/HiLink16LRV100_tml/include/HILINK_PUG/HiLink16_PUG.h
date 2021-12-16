////////////////////////////////////////////////////////////////////////////////
// Description:                                                               //
// This head file is to define APIs, which to check error count with internal //
// prbs checker and plot eye.                                                 //
////////////////////////////////////////////////////////////////////////////////

#ifndef HILINK16_PUG_H_
#define HILINK16_PUG_H_

#include <Common_Func/HiLink_Common_Func.h>

using namespace std;


extern class GLOBAL_SSPARA		SSpara;
extern class GLOBAL_CSPARA		CSpara;
extern class GLOBAL_CUSTPARA 	CUSTpara;

const INT	NA = -999;

void HiLinkPowerUpCtrl(const STRING sPowerUpCtrlPatternName);
void HiLinkResetAndInit(const STRING sInitVectorName);
void FWreadDefaultRegisters2CSR(const MACRO_LANE_SEL& MacroLane_Sel);
SITE_PASSFAIL_RESULT HiLink16_FW_CAL(const MACRO_LANE_SEL& MacroLane_Sel, GLOBAL_CUSTPARA& CUSTpara, GLOBAL_SSPARA& SSpara, GLOBAL_CSPARA& CSpara, MACRO_INT &CS_Cal_MacroResult, MACRO_INT &DS_Cal_MacroResult, LANE_INT& DS_Cal_LaneResult, STRING sCalibrationType = "", INT iDownLoadHex = 0);
void Clear_All_API_Regs();
void CsConfigurationbeforecalibration(const MACRO_LANE_SEL& MacroLane_Sel, GLOBAL_CUSTPARA& CUSTpara, GLOBAL_SSPARA& SSpara,  GLOBAL_CSPARA& CSpara);
void DSconfigurationbeforecalibration(const MACRO_LANE_SEL& MacroLane_Sel, GLOBAL_CUSTPARA& CUSTpara);
void CsConfigAPIRegsBeforeCal(UINT MacroID, INT CSslice);
void DsConfigAPIRegsBeforeCal(INT MacroID);
void ExpectCSandDSCalibrationDone(const MACRO_LANE_SEL& MacroLane_Sel, STRING sWaitCalDoneLabelName, STRING sCalibrationType);
void ExpectFWPIEyeScanDone(const MACRO_LANE_SEL& MacroLane_Sel, STRING sWaitAPIEYEDoneLabelName);
SITE_PASSFAIL_RESULT check_CS_top_API(const MACRO_LANE_SEL& MacroLane_Sel, INT CSslice, MACRO_INT& CS_Cal_MacroResult);
SITE_PASSFAIL_RESULT check_DS_top_API(const MACRO_LANE_SEL& MacroLane_Sel, MACRO_INT& DS_Cal_MacroResult, LANE_INT& DS_Cal_LaneResult);
void CsConfigaftercalibration(MACRO_LANE_SEL MacroLane_Sel, GLOBAL_CUSTPARA CUSTpara);
void DsConfigurationAfterCalibration(MACRO_LANE_SEL MacroLane_Sel, GLOBAL_CUSTPARA CUSTpara);



bool ReadBert(const MACRO_LANE_SEL& MacroLane_Sel, PRBS_Pattern mPRBS, LANE_DOUBLE& ErrorCount, STRING TestMode = "ABIST", DOUBLE wait_time_ms = 1);
bool ReadBert_ExpectValue(const MACRO_LANE_SEL& MacroLane_Sel, PRBS_Pattern mPRBS, LANE_DOUBLE& ErrorCount, STRING TestMode = "ABIST", DOUBLE wait_time_ms = 1);
bool AntiFool(const MACRO_LANE_SEL& MacroLane_Sel, PRBS_Pattern mPRBS, LANE_DOUBLE& ErrorCount, STRING TestMode = "ABIST", DOUBLE wait_time_ms = 0.1);
bool AntiFool_ExpectValue(const MACRO_LANE_SEL& MacroLane_Sel, PRBS_Pattern mPRBS, LANE_DOUBLE& ErrorCount, STRING TestMode = "ABIST", DOUBLE wait_time_ms = 0.1);

bool GetFourPointEyeDiagram(const MACRO_LANE_SEL& MacroLane_Sel, const DOUBLE &dDataRate, LANE_EYEDATA &eyeData, bool eyeheight_enable = true, STRING TestMode = "ABIST", INT averageTimes = 1);
bool GetEyeDiagram(const MACRO_LANE_SEL& MacroLane_Sel, DOUBLE& dDataRate, STRING TestMode = "ABIST", bool showInner = true, INT scanWin = 15, INT averageTimes = 1);
bool EyeScanStartCheck(const MACRO_LANE_SEL& MacroLane_Sel);
bool EyeMonitorReadyCheck(const MACRO_LANE_SEL& MacroLane_Sel);



/*Function of set Tx FIR taps
 *Return value indicate whether set operation succeed
 *To keep Tx output impedance, it?s recommended to set the sum of abs value of TXFIRPRE2, TXFIRPRE1, TXFIRMAIN, TXFIRPOST1 and TXFIRPOST2 not more than 64
 */
void Tx_tapmap_Trigger();
bool SetTxFir(TxFIR_SETTING FIR, bool PCIE_SATA_SAS_MODE = false);
void EnableTxToRxParLpbk();
void DisableTxToRxParLpbk();
void EnableTxToRxSerLpbk(const STRING& LoopBackMode = "Bump");
void DisableTxToRxSerLpbk();
void EnableRxToTxParLpbk();
void DisableRxToTxParLpbkAndSwitchToMissionMode();
void EnableTxPrbsGen(PRBS_Pattern TxPRBSGenPattern, bool PCIE_SATA_SAS_MODE = false);
void DisableTxPrbsGenAndSwitchToMissionMode(bool PCIE_SATA_SAS_MODE = false);
void EnableRxPrbsCheck(PRBS_Pattern RxPRBSCheckPattern);
void DisableRxPrbsCheck();
void SetRxCTLE(RxCTLE_SETTING CTLE);
void SetpmaMode();
void SetsigdetMode();

void GetInnerEyeMetricbyFirmwareAPI(const MACRO_LANE_SEL& MacroLane_Sel, LANE_EYEDATA &eyeData);


/*Functions of Tx/Rx/Dsclk Power up/down*/
void HiLinkPreset ();

void DSCLK_Setup(MACRO_LANE_SEL& MacroLane_Sel , LANE_DOUBLE IOSCDAC_BAND);

#endif /* HILINK16_PUG_H_ */
