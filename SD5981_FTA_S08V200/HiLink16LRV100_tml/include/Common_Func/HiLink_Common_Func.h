/*
 * HiLink_Common_Func.h
 *
 *  Created on: Apr 12, 2017
 *      Author: yanfen.fang
 */

#ifndef HILINK_COMMON_FUNC_H_
#define HILINK_COMMON_FUNC_H_
#include <HILINK_DRIVE/HiLink_Drive.h>
#include <Common_Func/System_Common_Func.h>
#include <iomanip>
PinArrayDouble PPMU_FIMV_measure(string Pins,double iforce,double vExpect,double waittime,int sampleSize,bool disconnect=true); //thy add 2021.11.29
PinArrayDouble PPMU_FVMI_measure(string Pins,double vforce,double irange,double waittime,int sampleSize,bool disconnect=true); //thy add 2021.11.29
void PPMU_FV_Waitmeasure(string Pins,double vforce,double irange,double waittime,int sampleSize);//thy add 2021.11.29
void PPMU_FI_Waitmeasure(string Pins,double iforce,double vExpect,double waittime,int sampleSize);//thy add 2021.11.29
void PPMU_FV(string Pins,double vforce,double irange);//thy add 2021.11.29
void PPMU_FI(string Pins,double iforce,double VclampH,double VclampL);//thy add 2021.11.29
void GET_SYSTEM_FLAG(string specName,int result);//thy add 2021.11.30
void GET_TESTSUITE_NAME(string& TestName);
extern SITE_INT CSR_CHECK_JUDGE_RESULT;
extern SITE_INT H16_FailBin_Flag;
extern string m_TestName;
extern int m_TestNumber;
extern int m_HardBin;
extern int m_SoftBin;
extern int isDPS128;

JI JitterInjection(const INT& DataWidth, const INT& RateMode, const DOUBLE& DataRate, DOUBLE& JitterAmpRequired);
INT FreqOffset(const INT& DataWidth, const INT& RateMode, DOUBLE FreqOffsetRequired);
void setJitterInjection(DOUBLE amplitude, DOUBLE Frequency,const STRING& PinList_P);

bool Update_LaneData_InTolerance(const MACRO_LANE_SEL& MacroLane_Sel, const DOUBLE& SpecValue, LANE_DOUBLE& ErrorCount, LANE_DOUBLE& TempResult, LANE_INT& FindFlag);
bool Update_LaneData_InTolerance(const MACRO_LANE_SEL& MacroLane_Sel, const INT& SpecValue, LANE_DOUBLE& ErrorCount, LANE_DOUBLE& TempResult, LANE_INT& FindFlag);//add by LX


void JTAG_READ(const MACRO_LANE_SEL& MacroLane_Sel, const uint addr,MACRO_INT& permacro_value);

void CSR_READ(const MACRO_LANE_SEL& MacroLane_Sel, HILINK_Regs_Base& reg, const INT& csrindex,LANE_INT& perlane_value);
void CSR_READ(const MACRO_LANE_SEL& MacroLane_Sel, HILINK_Regs_Base& reg, const INT& csrindex,MACRO_INT& permacro_value);
void CSR_READ(const MACRO_LANE_SEL& MacroLane_Sel, const INT& iCSSlice, HILINK_Regs_Base& reg, const INT& csrindex,MACRO_INT& permacro_value);

void Update_ForDynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, LANE_INT& Segmentvalue, LANE_INT& CSRvalue);
void Update_ForDynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, MACRO_INT& Segmentvalue, MACRO_INT& CSRvalue);

void getSegmentFromCSR(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, LANE_INT& CSRvalue, LANE_INT& Segmentvalue);
void getSegmentFromCSR(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, MACRO_INT& CSRvalue, MACRO_INT& Segmentvalue);

void SEGMENT_READ(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,LANE_INT& perlane_value);
void SEGMENT_READ(const MACRO_LANE_SEL& MacroLane_Sel, const INT& iCSSlice, const T_REG_INFO_EX& reg_info_ex,MACRO_INT& permacro_value);

void SEGMENT_READ(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,LANE_DOUBLE& perlane_value);
void SEGMENT_READ(const MACRO_LANE_SEL& MacroLane_Sel, const INT& iCSSlice, const T_REG_INFO_EX& reg_info_ex,MACRO_DOUBLE& permacro_value);

void SEGMENT_READ(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,MACRO_INT& permacro_value);
void SEGMENT_READ(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,MACRO_DOUBLE& permacro_value);

void SEGMENT_EXPECT(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,UINT value, SITE_PASSFAIL_RESULT& ExpectResult);
void SEGMENT_EXPECT(const MACRO_LANE_SEL& MacroLane_Sel, const INT& iCSSlice, const T_REG_INFO_EX& reg_info_ex,UINT value, SITE_PASSFAIL_RESULT& ExpectResult);
void SEGMENT_EXPECT(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,UINT value, SITE_PASSFAIL_RESULT& ExpectResult,MACRO_INT& permacro_value);
void SEGMENT_EXPECT(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,UINT value, SITE_PASSFAIL_RESULT& ExpectResult,LANE_INT& perlane_value);

void WaitDone(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,UINT value, INT MaxCheckCount, DOUBLE IntervalTime_ms, SITE_PASSFAIL_RESULT& ExpectResult);
void WaitDone(const MACRO_LANE_SEL& MacroLane_Sel, const INT& iCSSlice, const T_REG_INFO_EX& reg_info_ex,UINT value, INT MaxCheckCount, DOUBLE IntervalTime_ms, SITE_PASSFAIL_RESULT& ExpectResult);

void WaitDone(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,UINT value, INT MaxCheckCount, DOUBLE IntervalTime_ms, SITE_PASSFAIL_RESULT& ExpectResult,LANE_INT& perlane_result);
void WaitDone(const MACRO_LANE_SEL& MacroLane_Sel, const INT& iCSSlice, const T_REG_INFO_EX& reg_info_ex,UINT value, INT MaxCheckCount, DOUBLE IntervalTime_ms, SITE_PASSFAIL_RESULT& ExpectResult,MACRO_INT& permacro_result);
void WaitDone(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,UINT value, INT MaxCheckCount, DOUBLE IntervalTime_ms, SITE_PASSFAIL_RESULT& ExpectResult,MACRO_INT& permacro_result);

void PrintSegInfo(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, LANE_INT perlane_value);
void PrintCSRInfo(const MACRO_LANE_SEL& MacroLane_Sel, HILINK_Regs_Base& reg, const INT& csrindex, LANE_INT perlane_value);
void PrintSegInfo(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, MACRO_INT permacro_value);
void PrintCSRInfo(const MACRO_LANE_SEL& MacroLane_Sel, HILINK_Regs_Base& reg, const INT& csrindex, MACRO_INT permacro_value);
void DumpCSRInfo(const MACRO_LANE_SEL& MacroLane_Sel, HILINK_Regs_Base& reg, const INT& csrindex);

void PlotEyeDiagram(const MACRO_LANE_SEL& MacroLane_Sel, LANE_EYEDIAGRAM& eyeDiagram, INT uiSize,int  iRateMode, INT iMonitorDelay = 0);

void GetRxPinList(const MACRO_LANE_SEL& MacroLane_Sel, STRING& sPinList_P, STRING& sPinList_N, STRING& sPinList);
void GetTxPinList(const MACRO_LANE_SEL& MacroLane_Sel, STRING& sPinList_P, STRING& sPinList_N, STRING& sPinList);

void DynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, HILINK_Regs_Base& reg,uint csrIndex,LANE_INT& perLane_value,uint id=0);
void DynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, HILINK_Regs_Base& reg,uint csrIndex,MACRO_INT& perMacro_value,uint CSSlice=0,uint id=0);

void Read2IDString(const MACRO_LANE_SEL& MacroLane_Sel,const uint addr,const string& id="");
void Read2IDString(const MACRO_LANE_SEL& MacroLane_Sel,HILINK_Regs_Base& reg,uint csrIndex,const string& id="");
void ExpectValue(const MACRO_LANE_SEL& MacroLane_Sel ,HILINK_Regs_Base& reg, uint csrIndex,uint value, uint mask=0x0000);
void ExpectSegment(const MACRO_LANE_SEL& MacroLane_Sel ,const T_REG_INFO_EX& reg_info_ex,uint value);

void getReadValue(const MACRO_LANE_SEL& MacroLane_Sel,uint addr,MACRO_INT& macro_int,const string& id="");
void getReadValue(const MACRO_LANE_SEL& MacroLane_Sel,HILINK_Regs_Base& reg,uint csrIndex,LANE_INT& lane_int,const string& id="");
void getReadValue(const MACRO_LANE_SEL& MacroLane_Sel,HILINK_Regs_Base& reg,uint csrIndex,MACRO_INT& macro_int,const string& id="");

void hasJTAGPassed(const string& label,SITE_PASSFAIL_RESULT& result);
bool hasAllSitesPassed();

void SIGDET_expect_everyone_ALL0(const MACRO_LANE_SEL& MacroLane_Sel,T_ALOS_SEARCH_INFO& search_info,SITE_PASSFAIL_RESULT& ExpectResult);
void SIGDET_Search(const MACRO_LANE_SEL& MacroLane_Sel,T_ALOS_SEARCH_INFO& search_info,LANE_DOUBLE& All0_min_perlane,LANE_DOUBLE& All1_max_perlane,LANE_DOUBLE& vgap_perlane);
void SIGDET_Search_theLane(uint MacroID,uint LaneID,T_ALOS_SEARCH_INFO& search_info,LANE_DOUBLE& All0_min_perlane,LANE_DOUBLE& All1_max_perlane,
		HILINK_LANE_DATA_CONTAINER<SIGDET_STATUS>& SIGDET_status_allsite,
		LANE_SIGDET_STATUS& SIGDET_status_perlane,double spec_val,double step_val,int d2s_mode);

void HiLink_PerLane_Judge( const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname,double LimitL, LANE_DOUBLE& TempResult, double LimitH,JUDGE_PIN Judge_Pin = PIN_TXP);
void HiLink_PerLane_Judge( const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname,double LimitL, LANE_INT& TempResult,double LimitH,JUDGE_PIN Judge_Pin = PIN_TXP);
void HiLink_PerLane_Judge( const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname,double LimitL, LANE_UINT& TempResult,double LimitH,JUDGE_PIN Judge_Pin = PIN_TXP);
void HiLink_PerMacro_Judge(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname, double LimitL, MACRO_DOUBLE& TempResult,double LimitH, JUDGE_PIN Judge_Pin = PIN_TXP);
void HiLink_PerMacro_Judge(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname,double LimitL,  MACRO_INT& TempResult,double LimitH, JUDGE_PIN Judge_Pin = PIN_TXP);
void HiLink_PerSite_Judge(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname, SITE_DOUBLE& TempResult, JUDGE_PIN Judge_Pin = PIN_TXP);
void judgeAndLog_ParametricTest(INT SiteID, string testname, string Macro_Lane_Name,double LimitL,double TestVal,double LimitH,int testNumber);
void judgeAndLog_ParametricTest_DC(string TestNameLimit,double TestVal,double LimitL,double LimitH);
void HiLink_PerLane_DummyJudge(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname, LANE_DOUBLE& TempResult, JUDGE_PIN Judge_Pin = PIN_RXP);
void HiLink_PerMacro_DummyJudge(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname, MACRO_DOUBLE& TempResult, JUDGE_PIN Judge_Pin = PIN_RXP);
void HiLink_PerSite_DummyJudge(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname, SITE_DOUBLE& TempResult, JUDGE_PIN Judge_Pin = PIN_RXP);


void Relay_Control(STRING sTxRelayState);
void PrintLaneSegInfo(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, LANE_INT perlane_value);
void Update_DSReg_ForDynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, LANE_INT& Segmentvalue, LANE_INT& CSRvalue);
void Update_CSReg_ForDynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, MACRO_INT& Segmentvalue, MACRO_INT& CSRvalue);

void parseSiteDataFromMacroInt(map<int,long long>& val,MACRO_INT& macro_data,uint MacroID);
void Update_DSReg_ForDynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, LANE_INT& Segmentvalue, LANE_INT& CSRvalue);
void optimize_RX_cycles(const INT JTAG_CYCLE, DOUBLE DataRate_JTAG, DOUBLE DataRate_pHilink_RX);

/***************used for dynamic write***********/
void parseSiteDataFromLaneInt(map<int,long long>& val,LANE_INT& lane_data,uint MacroID,uint LaneID);
void parseSiteDataFromMacroInt(map<int,long long>& val,MACRO_INT& macro_data,uint MacroID);
void Update_CSR_ForDynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, MACRO_INT& Segmentvalue, MACRO_INT& CSRvalue, const T_REG_INFO_EX& reg_info_ex);

void UpdateSiteData(LANE_INT& lane_data,map<int,long long>& val,uint MacroID,uint LaneID);
void UpdateSiteData(MACRO_INT& macro_data,map<int,long long>& val,uint MacroID);
uint int2signbitint(int val,const T_REG_INFO_EX& reg_info_ex);



//add by LX
void Load_FirmWare(const MACRO_LANE_SEL& MacroLane_Sel);
void ReadFirmWareRevAndPrint(MACRO_LANE_SEL& MacroLane_Sel);
void FWreadDefaultRegisters2CSR_RefCLKLockRange(const MACRO_LANE_SEL& MacroLane_Sel, INT mCSSlice);
DOUBLE calculate_clocks(INT  mKa, INT  mKb, INT  mJJ, INT  mM, INT  mN, DOUBLE Refclkfreq = 156.25);
void AnalogLosCheck(const MACRO_LANE_SEL& MacroLane_Sel, const INT& ReadCnt, LANE_INT& SigdetLosStat, STRING pRXlabel = "", LONG cycnum = 0);
void Squelch_check(const MACRO_LANE_SEL& MacroLane_Sel, const INT& ReadCnt, LANE_INT& SquelchStat, STRING pRXlabel = "", LONG cycnum = 0);
void squelch_det_idle_check(const MACRO_LANE_SEL& MacroLane_Sel, vector<ARRAY_D>& vsquelch_det_idle, STRING LabelName, INT LabelCycle);
void squelch_det_burst_check(const MACRO_LANE_SEL& MacroLane_Sel, vector<ARRAY_D>& vsquelch_det_burst, STRING LabelName, INT LabelCycle);
void Tx_RxDET_Detect(const MACRO_LANE_SEL& MacroLane_Sel, LANE_DOUBLE& Tx_rxdet_result);
void ReadAndCalcVCOFreqcalCurveLength(const MACRO_LANE_SEL& MacroLane_Sel, const INT& iCSSlice, MACRO_DOUBLE& CurveLength);
void LogDiffFreqOpenLoop(const MACRO_LANE_SEL& MacroLane_Sel, const INT& iCSSlice, MACRO_DOUBLE& OpenLoopLLDDIFF);
void GetTxFIR(TxFIR_SETTING& FIR_ORI);

double get_spec_val (const string& sType, const string& sSpecName);
int GET_DigitalCapture_XMode(string& PinName);
void replace_str(string& str, const string sb, const string sa);
string int2String(int input);
void DSP_MINMAX(ARRAY_D& src,DOUBLE *min,DOUBLE *max,INT *min_index,INT *max_index);

#endif /* HILINK_COMMON_FUNC_H_ */
