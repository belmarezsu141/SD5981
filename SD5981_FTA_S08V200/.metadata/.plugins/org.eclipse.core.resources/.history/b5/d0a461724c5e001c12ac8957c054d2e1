/*
 * HiLink_Common_Func.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: yanfen.fang
 */

#include <cmath>
#include <SRC_d2s/d2s.h>
#include <HILINK_DRIVE/HiLink_Regs_Base.h>
#include <unistd.h>
#include <vector>
#include <UserAPI.h>
//#include <CCTimer.h>
#include <Common_Func/HiLink_Common_Func.h>
using namespace std;
using namespace PhxAPI;

//d2s_IP_JTAG& jtag = d2s_IP_JTAG::Instance();
//char label[200] = {'\0'};


void GET_SYSTEM_FLAG(string specName,int result)
{
	string specVal = TheSoft.Global().GetStringValue(specName);
	if(specVal=="yes"){
		result =1;
	}
	else{
		result =0;
	}
}

void GET_TESTSUITE_NAME(string& TestName)
{
	TestName = TheSoft.Flow().Test().GetCurrentTestName();
}

JI JitterInjection(const INT& DataWidth, const INT& RateMode, const DOUBLE& DataRate, DOUBLE& JitterAmpRequired){
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

	typedef map <int, int>::value_type  valType;

	map <int, int> mapJITAMP;
	mapJITAMP.insert(valType (0, 3));
	mapJITAMP.insert(valType (1, 4));
	mapJITAMP.insert(valType (2, 5));
	mapJITAMP.insert(valType (3, 6));
	mapJITAMP.insert(valType (4, 8));
	mapJITAMP.insert(valType (5, 10));
	mapJITAMP.insert(valType (6, 12));
	mapJITAMP.insert(valType (7, 16));
	mapJITAMP.insert(valType (8, 20));
	mapJITAMP.insert(valType (9, 24));
	mapJITAMP.insert(valType (10,32));
	mapJITAMP.insert(valType (11,40));
	mapJITAMP.insert(valType (12,48));
	mapJITAMP.insert(valType (13,64));
	mapJITAMP.insert(valType (14,80));
	mapJITAMP.insert(valType (15,96));

	DOUBLE 			UIsize = 64;
	/*set UIsize = 64 is for value in mapJITAMP will be 2X,4X,8X in half,quarter,oct ratemode*/

	DOUBLE 			WORDWIDTH;

	switch (DataWidth) {
		case 0: WORDWIDTH = 16; break;
		case 1: WORDWIDTH = 20; break;
		case 2: WORDWIDTH = 16; break;
		case 3: WORDWIDTH = 20; break;
		default: WORDWIDTH = 20; break;
	}

	switch (RateMode) {
		case 0: WORDWIDTH /= 1;
				UIsize = 64;
				break;
		case 1: WORDWIDTH /= 2;
				UIsize = 128;
				break;
		case 2: WORDWIDTH /= 4;
				UIsize = 256;
				break;
		case 3: WORDWIDTH /= 8;
				UIsize = 512;
				break;
		default: WORDWIDTH /= 1;
				UIsize = 64;
				break;
	}

	DOUBLE 			JitterAmp;
	map <int,int>::iterator itAmp;
	INT				AmpIndex = -1;

	do {
		AmpIndex ++;
		itAmp = mapJITAMP.find (AmpIndex);
		if (itAmp != mapJITAMP.end()) {
			JitterAmp = (itAmp -> second) / UIsize;
		}
	} while (JitterAmp < JitterAmpRequired && AmpIndex < 15);

	hout(DETAIL) << "JITAMP = " << dec << AmpIndex << ": JitterAmp = " <<  JitterAmp << " [UI]" << endl;

	/********Find JitterFrequency************/
	INT    			JITAMP = itAmp -> second;
//	DOUBLE 			Kfactor = (UIsize - JITAMP) / UIsize; /**GUI code**/
	DOUBLE 			UIps = 1000 / DataRate;

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
	mapJITFREQ.insert(valType (0, 1));
	mapJITFREQ.insert(valType (1, 2));
	mapJITFREQ.insert(valType (2, 3));
	mapJITFREQ.insert(valType (3, 4));
	mapJITFREQ.insert(valType (4, 5));
	mapJITFREQ.insert(valType (5, 6));
	mapJITFREQ.insert(valType (6, 7));
	mapJITFREQ.insert(valType (7, 8));

	DOUBLE 			JitterFrequency;
	map <int,int>::iterator itFreq;
	INT				FreqIndex = 0;
	DOUBLE			Diff = 0;


	JITFREQ 	MinDiffFreq = {0, 100.0, 0.0}; /**first element is FreqIndex, second is Diff between JitterFrequency and JitterFrequencyrequared, third is actual jitter freq**/

	while (FreqIndex <= 7) {
		itFreq = mapJITFREQ.find (FreqIndex);
		if (itFreq != mapJITFREQ.end()) {
//			JitterFrequency =  1000000 / (2 * (JITAMP + Kfactor) * itFreq -> second * effect_dwidth * UIps); /**MHz**/ /**GUI code***/
			JitterFrequency =  1000000 / (2 * JITAMP * itFreq -> second * WORDWIDTH * UIps); /**MHz**/
			Diff = abs(JitterFrequency - 1000 * DataRate / 1667); /**MHz**/
			if (Diff < MinDiffFreq.JFreqDiff)
			{
				MinDiffFreq.JFreqDiff = Diff;
				MinDiffFreq.Findex = itFreq -> first;
				MinDiffFreq.jFreq = JitterFrequency;
			}
		}
		FreqIndex ++;
	}

	if (((MinDiffFreq.jFreq - 1000 * DataRate / 1667) > 10) && (MinDiffFreq.Findex < 7)) {
		MinDiffFreq.Findex ++;
	}

	hout(DETAIL) << "JITFREQ = " << MinDiffFreq.Findex << ": JitterFrequency = " <<  1000000 / (2 * JITAMP * (mapJITFREQ.find(MinDiffFreq.Findex) -> second) * WORDWIDTH * UIps) << " [MHz]" << endl;

	JI  	JitterInjection = {AmpIndex, MinDiffFreq.Findex};
	return 	JitterInjection;
}

INT FreqOffset(const INT& DataWidth, const INT& RateMode, DOUBLE FreqOffsetRequired)
{
/*	The MSB (i.e., PPMGEN[4]) defines the slew rate direction. Remaining bits,
 *	i.e., PPMGEN[3:0] define the number of words (normal/extended):
 *			0000 = infinite/0 words 1000 = infinite/12 words
 *			0001 = 2/2 words 		1001 = infinite/16 words
 *			0010 = 3/3 words 		1010 = infinite/20 words
 *			0011 = 4/4 words 		1011 = infinite/24 words
 *			0100 = 6/5 words 		1100 = infinite/32 words
 *			0101 = 8/6 words 		1101 = infinite/40 words
 *			0110 = 12/8 words 		1110 = infinite/48 words
 *			0111 = 16/10 words 		1111 = infinite/64 words
 *	FrequencyOffset = 1000000 / (UIsize * WORDWIDTH * PPMGEN)*/


	typedef map <int, int>::value_type  valType;

	map <int, int> mapPPM;
	mapPPM.insert(valType (0, 0));
	mapPPM.insert(valType (1, 2));
	mapPPM.insert(valType (2, 3));
	mapPPM.insert(valType (3, 4));
	mapPPM.insert(valType (4, 5));
	mapPPM.insert(valType (5, 6));
	mapPPM.insert(valType (6, 8));
	mapPPM.insert(valType (7, 10));
	mapPPM.insert(valType (8, 12));
	mapPPM.insert(valType (9, 16));
	mapPPM.insert(valType (10,20));
	mapPPM.insert(valType (11,24));
	mapPPM.insert(valType (12,32));
	mapPPM.insert(valType (13,40));
	mapPPM.insert(valType (14,48));
	mapPPM.insert(valType (15,64));

	/*************GUI CODE BEGIN***********/
	DOUBLE 			UIsize = 64;
	DOUBLE 			WORDWIDTH;

	switch (DataWidth)
	{
		case 0: WORDWIDTH = 16; break;
		case 1: WORDWIDTH = 20; break;
		case 2: WORDWIDTH = 16; break;
		case 3: WORDWIDTH = 20; break;
		default: WORDWIDTH = 20; break;
	}

	switch (RateMode)
	{
		case 0: WORDWIDTH /= 1; UIsize = 64; break;
		case 1: WORDWIDTH /= 2; UIsize = 128; break;
		case 2: WORDWIDTH /= 4; UIsize = 256; break;
		case 3: WORDWIDTH /= 8; UIsize = 512; break;
		default: WORDWIDTH /= 1; UIsize = 64; break;
	}

	/*************GUI CODE END***********/

	DOUBLE 			FreqOffset;
	map <int,int>::iterator it;
	INT				Index = 0;
	do
	{
		Index ++;
		it = mapPPM.find (Index);
		if (it != mapPPM.end())
		{
			FreqOffset = 1000000.0 / (UIsize * WORDWIDTH * it -> second);
		}
	}
	while (FreqOffset > FreqOffsetRequired && Index < 15);

	hout(DETAIL) << "PPMGEN = " << Index << ": FREQOFFSET = " <<  FreqOffset << " [PPM]" << endl;

	return Index;
}

void setJitterInjection(DOUBLE amplitude, DOUBLE Frequency,const STRING& PinList_P){
	STRING 			sSetname = "set";
	STRING 			sContext = "FASTDIFF";

//	MODULATION_SET_TIMING 		mset1(sSetname + "1");
//	mset1.setAmplitude(amplitude)
//		 .setPeriod(1.0 / Frequency)
//		 .setShape(JITTER_INJECTION::MODULATION_SHAPE_SINE);
//
//	MODULATION_SET_TIMING 		mset2(sSetname + "2");
//	mset2.setAmplitude(0)
//		 .setPeriod(0)
//		 .setShape(JITTER_INJECTION::MODULATION_SHAPE_SINE);
//
//
//	JITTER_INJECTION_SET 		set(sSetname, sContext);
//	set.pin(PinList_P).linkModulationSets(mset1,mset2).setMode(JITTER_INJECTION::RESTART);
//	set.setAsPrimary();
}

void GetRxPinList(const MACRO_LANE_SEL& MacroLane_Sel, STRING& sPinList_P, STRING& sPinList_N, STRING& sPinList){
	sPinList_P = "";
	sPinList_N = "";
	bool IsFirst = true;
	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
	{
		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
		const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

		for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
		{
			UINT LaneID = vLane[laneIndex];
			if (!IsFirst)
			{
				sPinList_P += ",";
				sPinList_N += ",";
			}
			IsFirst = false;
			sPinList_P += LANE_INFO[MacroID][LaneID].RX_P;
			sPinList_N += LANE_INFO[MacroID][LaneID].RX_N;
		}
	}

	sPinList = sPinList_P + "," + sPinList_N;
}
void GetTxPinList(const MACRO_LANE_SEL& MacroLane_Sel, STRING& sPinList_P, STRING& sPinList_N, STRING& sPinList){
	sPinList_P = "";
	sPinList_N = "";
	bool IsFirst = true;
	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
	{
		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
		const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

		for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
		{
			UINT LaneID = vLane[laneIndex];
			if (!IsFirst)
			{
				sPinList_P += ",";
				sPinList_N += ",";
			}
			IsFirst = false;
			sPinList_P += LANE_INFO[MacroID][LaneID].TX_P;
			sPinList_N += LANE_INFO[MacroID][LaneID].TX_N;
		}
	}

	sPinList = sPinList_P + "," + sPinList_N;
}

bool Update_LaneData_InTolerance(const MACRO_LANE_SEL& MacroLane_Sel, const DOUBLE& SpecValue, LANE_DOUBLE& ErrorCount, LANE_DOUBLE& TempResult, LANE_INT& FindFlag){
	bool	iFindAll = true;
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
				UINT LaneID = vLane[laneIndex];
				if (ErrorCount[SiteID][MacroID][LaneID] == 0 && FindFlag[SiteID][MacroID][LaneID] == 0) {
					TempResult[SiteID][MacroID][LaneID] = SpecValue;
					iFindAll = false;
				} else {
					FindFlag[SiteID][MacroID][LaneID] = 1;
				}
			}
		}
	FOREACH_ACTIVESITE_END
	return iFindAll;
}

bool Update_LaneData_InTolerance(const MACRO_LANE_SEL& MacroLane_Sel, const INT& SpecValue, LANE_DOUBLE& ErrorCount, LANE_DOUBLE& TempResult, LANE_INT& FindFlag)
{
	INT		iFindAll = 1;
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
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


void Update_ForDynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, LANE_INT& Segmentvalue, LANE_INT& CSRvalue){
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				CSRvalue[SiteID][MacroID][LaneID]=HILINK_Regs_Base::fill_bits(CSRvalue[SiteID][MacroID][LaneID],reg_info_ex,Segmentvalue[SiteID][MacroID][LaneID]);
			}
		}
	FOREACH_ACTIVESITE_END
}
void Update_ForDynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, MACRO_INT& Segmentvalue, MACRO_INT& CSRvalue){
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			CSRvalue[SiteID][MacroID]=HILINK_Regs_Base::fill_bits(CSRvalue[SiteID][MacroID],reg_info_ex,Segmentvalue[SiteID][MacroID]);
		}
	FOREACH_ACTIVESITE_END
}

void getSegmentFromCSR(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, LANE_INT& CSRvalue, LANE_INT& Segmentvalue){
	if(reg_info_ex.parent.getType()!=HILINK_PERLANE_REGISTER){
		cerr<<"Error: "<<__FUNCTION__<<" in d2s-block "<<d2sFramework::get_current_prefix()<<" Register: "<<reg_info_ex.parent.getName()<<" is not PerLane type!"<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				Segmentvalue[SiteID][MacroID][LaneID]=HILINK_Regs_Base::get_bits(CSRvalue[SiteID][MacroID][LaneID],reg_info_ex);
			}
		}
	FOREACH_ACTIVESITE_END
}
void getSegmentFromCSR(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, MACRO_INT& CSRvalue, MACRO_INT& Segmentvalue){
	if(reg_info_ex.parent.getType()!=HILINK_PERMACRO_REGISTER){
		cerr<<"Error: "<<__FUNCTION__<<" in d2s-block "<<d2sFramework::get_current_prefix()<<" Register: "<<reg_info_ex.parent.getName()<<" is not PerMacro type!"<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			Segmentvalue[SiteID][MacroID]=HILINK_Regs_Base::get_bits(CSRvalue[SiteID][MacroID],reg_info_ex);
		}
	FOREACH_ACTIVESITE_END
}

void JTAG_READ(const MACRO_LANE_SEL& MacroLane_Sel, const uint addr,MACRO_INT& permacro_value){
	d2s_JTAG& jtag = d2s_JTAG::Instance();
	d2s::d2s_LABEL_BEGIN("JTAG_READ", Global_D2S_Mode);
		Read2IDString(MacroLane_Sel,addr);
	d2s::d2s_LABEL_END;
	getReadValue(MacroLane_Sel,addr,permacro_value);
}

void CSR_READ(const MACRO_LANE_SEL& MacroLane_Sel, HILINK_Regs_Base& reg, const INT& csrindex,LANE_INT& perlane_value){
	d2s_JTAG& jtag = d2s_JTAG::Instance();
	if(reg.getType()!=HILINK_PERLANE_REGISTER){
		cerr<<"Error: "<<__FUNCTION__<<" in d2s-block "<<d2sFramework::get_current_prefix()<<" Register: "<<reg.getName()<<" is not PerLane type!"<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	d2s::d2s_LABEL_BEGIN("CSR_READ", Global_D2S_Mode);
		Read2IDString(MacroLane_Sel,reg,csrindex);
	d2s::d2s_LABEL_END;
	perlane_value.init(0);
	getReadValue(MacroLane_Sel,reg,csrindex,perlane_value);
}

void CSR_READ(const MACRO_LANE_SEL& MacroLane_Sel, HILINK_Regs_Base& reg, const INT& csrindex,MACRO_INT& permacro_value){
	d2s_JTAG& jtag = d2s_JTAG::Instance();
	if(reg.getType()!=HILINK_PERMACRO_REGISTER){
		cerr<<"Error: "<<__FUNCTION__<<" in d2s-block "<<d2sFramework::get_current_prefix()<<" Register: "<<reg.getName()<<" is not PerMacro type!"<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	d2s::d2s_LABEL_BEGIN("CSR_READ", Global_D2S_Mode);
		Read2IDString(MacroLane_Sel,reg,csrindex);
	d2s::d2s_LABEL_END;
	getReadValue(MacroLane_Sel,reg,csrindex,permacro_value);
}

void CSR_READ(const MACRO_LANE_SEL& MacroLane_Sel, const INT& iCSSlice, HILINK_Regs_Base& reg, const INT& csrindex,MACRO_INT& permacro_value){
	reg.SliceID(iCSSlice);
	CSR_READ(MacroLane_Sel,reg,csrindex,permacro_value);
}

void SEGMENT_READ(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,LANE_INT& perlane_value){
	LANE_INT CSR_perlane;
	CSR_READ(MacroLane_Sel,reg_info_ex.parent,reg_info_ex.reg_info.csr,CSR_perlane);
	perlane_value.init(0);
	getSegmentFromCSR(MacroLane_Sel,reg_info_ex,CSR_perlane,perlane_value);
}

void SEGMENT_READ(const MACRO_LANE_SEL& MacroLane_Sel, const INT& iCSSlice, const T_REG_INFO_EX& reg_info_ex,MACRO_INT& permacro_value){
	MACRO_INT CSR_permacro;
	CSR_READ(MacroLane_Sel,iCSSlice,reg_info_ex.parent,reg_info_ex.reg_info.csr,CSR_permacro);
	getSegmentFromCSR(MacroLane_Sel,reg_info_ex,CSR_permacro,permacro_value);
}

void SEGMENT_READ(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,LANE_DOUBLE& perlane_value){
	LANE_INT perlane_segvalue;
	SEGMENT_READ(MacroLane_Sel,reg_info_ex,perlane_segvalue);
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				perlane_value[SiteID][MacroID][LaneID]=perlane_segvalue[SiteID][MacroID][LaneID];
			}
		}
	FOREACH_ACTIVESITE_END
}

void SEGMENT_READ(const MACRO_LANE_SEL& MacroLane_Sel, const INT& iCSSlice, const T_REG_INFO_EX& reg_info_ex,MACRO_DOUBLE& permacro_value){
	MACRO_INT permacro_segvalue;
	SEGMENT_READ(MacroLane_Sel,iCSSlice,reg_info_ex,permacro_segvalue);
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			permacro_value[SiteID][MacroID]=permacro_segvalue[SiteID][MacroID];
		}
	FOREACH_ACTIVESITE_END
}

void SEGMENT_READ(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,MACRO_INT& permacro_value){
	MACRO_INT CSR_permacro;
	CSR_READ(MacroLane_Sel,reg_info_ex.parent,reg_info_ex.reg_info.csr,CSR_permacro);
	getSegmentFromCSR(MacroLane_Sel,reg_info_ex,CSR_permacro,permacro_value);
}

void SEGMENT_READ(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,MACRO_DOUBLE& permacro_value){
	MACRO_INT permacro_segvalue;
	SEGMENT_READ(MacroLane_Sel,reg_info_ex,permacro_segvalue);
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			permacro_value[SiteID][MacroID]=permacro_segvalue[SiteID][MacroID];
		}
	FOREACH_ACTIVESITE_END
}

void SEGMENT_EXPECT(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,UINT value, SITE_PASSFAIL_RESULT& ExpectResult){
	d2s_JTAG& jtag = d2s_JTAG::Instance();
	UINT lb = reg_info_ex.reg_info.low_bit;
	UINT hb = reg_info_ex.reg_info.hi_bit;
	UINT csr = reg_info_ex.reg_info.csr;

	UINT mask = 0xFFFF;
	mask &= HI_BIT_MASK[hb];
	mask &= ~LO_BIT_MASK[lb];

	value <<= lb;
	value &= mask;

	mask = ~mask;

	ExpectResult.init(false);
	d2s::d2s_LABEL_BEGIN("SEGMENT_EXPECT", Global_D2S_Mode);
		jtag.enablePassFailCheckForNextExecution();
		ExpectValue(MacroLane_Sel,reg_info_ex.parent,csr,value,mask);
	d2s::d2s_LABEL_END;
	hasJTAGPassed("SEGMENT_EXPECT",ExpectResult);
}




void WaitDone(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex,UINT value, INT MaxCheckCount, DOUBLE IntervalTime_ms, SITE_PASSFAIL_RESULT& ExpectResult){
	int count=0;
	if(MaxCheckCount<=0){
		MaxCheckCount=1;
	}
	if(IntervalTime_ms<=0.0){
		IntervalTime_ms=0.001;
	}
	ExpectResult.init(false);
	do{
		SEGMENT_EXPECT(MacroLane_Sel,reg_info_ex,value,ExpectResult);
		TheInst.Wait(0.001*IntervalTime_ms);
		count++;
	}while(count<MaxCheckCount && !ExpectResult.isAllSitePassed());
}

void WaitDone(const MACRO_LANE_SEL& MacroLane_Sel, const INT& iCSSlice, const T_REG_INFO_EX& reg_info_ex,UINT value, INT MaxCheckCount, DOUBLE IntervalTime_ms, SITE_PASSFAIL_RESULT& ExpectResult){
	reg_info_ex.parent.SliceID(iCSSlice);
	WaitDone(MacroLane_Sel, reg_info_ex, value,MaxCheckCount,IntervalTime_ms,ExpectResult);
}


void PrintSegInfo(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, LANE_INT perlane_value){
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				hout(DETAIL) << "MacroID = " << MacroID << "\t" << "LaneID = " << LaneID << "\t"
							  << reg_info_ex.reg_info.reg_name << " = " << perlane_value[SiteID][MacroID][LaneID] << endl;
			}
		}
	FOREACH_ACTIVESITE_END
}

void PrintCSRInfo(const MACRO_LANE_SEL& MacroLane_Sel, HILINK_Regs_Base& reg, const INT& csrindex, LANE_INT perlane_value){
	if(reg.getType()!=HILINK_PERLANE_REGISTER){
		cerr<<"Error: "<<__FUNCTION__<<" in d2s-block "<<d2sFramework::get_current_prefix()<<" Register: "<<reg.getName()<<" is not PerLane type!"<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}

	vector<T_REG_INFO> reg_infos;
	reg.get_reg_infos(csrindex,reg_infos);
	M_CSR_INFO csr_info;
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		ostringstream str;
		str<<endl;
		str <<reg.getName()<<" CSR("<<dec<<csrindex<<")\t";
		for(uint i=0;i<reg_infos.size();i++){
			str<<reg_infos[i].reg_name<<"["<<reg_infos[i].hi_bit<<":"<<reg_infos[i].low_bit<<"]\t";
		}
		str<<endl;

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				uint value=perlane_value[SiteID][MacroID][LaneID];
				reg.decodeCSR(csrindex,value,csr_info);
				str << "M" << MacroID << "L" << LaneID << " : "<< hex << "0x" << value<<dec<<"\t";
				for(uint i=0;i<reg_infos.size();i++){
					int val=csr_info[reg_infos[i].reg_name];
					str<<dec<<val<<"(0x"<<hex<<val<<dec<<")\t";
				}
				str<<endl;
			}
		}
		hout(DETAIL)<<str.str()<<endl;
	FOREACH_ACTIVESITE_END
}

void PrintSegInfo(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, MACRO_INT permacro_value){
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			hout(DETAIL) << "MacroID = " << MacroID << "\t"
						<< reg_info_ex.reg_info.reg_name << " = " << permacro_value[SiteID][MacroID] << endl;
		}
	FOREACH_ACTIVESITE_END
}

void PrintCSRInfo(const MACRO_LANE_SEL& MacroLane_Sel, HILINK_Regs_Base& reg, const INT& csrindex, MACRO_INT permacro_value){
	if(reg.getType()!=HILINK_PERMACRO_REGISTER){
		cerr<<"Error: "<<__FUNCTION__<<" in d2s-block "<<d2sFramework::get_current_prefix()<<" Register: "<<reg.getName()<<" is not PerMacro type!"<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	vector<T_REG_INFO> reg_infos;
	reg.get_reg_infos(csrindex,reg_infos);
	M_CSR_INFO csr_info;
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		ostringstream str;
		str<<endl;
		str <<reg.getName()<<" CSR("<<dec<<csrindex<<")\t";
		for(uint i=0;i<reg_infos.size();i++){
			str<<reg_infos[i].reg_name<<"["<<reg_infos[i].hi_bit<<":"<<reg_infos[i].low_bit<<"]\t";
		}
		str<<endl;

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

			uint value=permacro_value[SiteID][MacroID];
			reg.decodeCSR(csrindex,value,csr_info);
			str << "M" << MacroID << " : "<< hex << "0x" << value<<dec<<"\t";
			for(uint i=0;i<reg_infos.size();i++){
				int val=csr_info[reg_infos[i].reg_name];
				str<<dec<<val<<"(0x"<<hex<<val<<dec<<")\t";
			}
			str<<endl;
		}
		hout(DETAIL)<<str.str()<<endl;
	FOREACH_ACTIVESITE_END
}

void DumpCSRInfo(const MACRO_LANE_SEL& MacroLane_Sel, HILINK_Regs_Base& reg, const INT& csrindex){
	if(reg.getType()==HILINK_PERMACRO_REGISTER){
		MACRO_INT macro_int;
		CSR_READ(MacroLane_Sel,reg,csrindex,macro_int);
		PrintCSRInfo(MacroLane_Sel,reg,csrindex,macro_int);
	}
	else{
		LANE_INT lane_int;
		CSR_READ(MacroLane_Sel,reg,csrindex,lane_int);
		PrintCSRInfo(MacroLane_Sel,reg,csrindex,lane_int);
	}
}

void PlotEyeDiagram(const MACRO_LANE_SEL& MacroLane_Sel, LANE_EYEDIAGRAM& eyeDiagram, INT uiSize,int  iRateMode,INT iMonitorDelay){
	ostringstream 			plot;
	LANE_EYEDIAGRAM 		plotShrink;
	LANE_ARRAY_I			phaseShrink;


	vector<EYEDATA>	vtmpplotData;
	for (INT i = 0; i < uiSize; i ++) {
		EYEDATA			tmpeye_perUI;
		tmpeye_perUI.eyeWidth = 0.0;
		tmpeye_perUI.eyeHeight = 0.0;
		tmpeye_perUI.leftValue = 0;
		tmpeye_perUI.rightValue = 0;
		tmpeye_perUI.bottomValue = 0;
		tmpeye_perUI.upValue = 0;

		vtmpplotData.push_back(tmpeye_perUI);
	}
	plotShrink.init(vtmpplotData);
	phaseShrink.init(uiSize,0);

	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				if (iRateMode == 0)
				{
					for (INT phaseIndex = 0; phaseIndex < uiSize; phaseIndex ++)
					{
						plotShrink[SiteID][MacroID][LaneID][phaseIndex].bottomValue = eyeDiagram[SiteID][MacroID][LaneID][phaseIndex].bottomValue;
						plotShrink[SiteID][MacroID][LaneID][phaseIndex].upValue = eyeDiagram[SiteID][MacroID][LaneID][phaseIndex].upValue;
						phaseShrink[SiteID][MacroID][LaneID][phaseIndex] = phaseIndex + (iMonitorDelay - uiSize / 2);
					}
				}
				else if (iRateMode == 1)
				{
					for (INT phaseIndex = 0; phaseIndex < uiSize / 2; phaseIndex ++)
					{
						plotShrink[SiteID][MacroID][LaneID][phaseIndex].bottomValue = (eyeDiagram[SiteID][MacroID][LaneID][2 * phaseIndex].bottomValue
																					   + eyeDiagram[SiteID][MacroID][LaneID][2 * phaseIndex + 1].bottomValue) / 2;
						plotShrink[SiteID][MacroID][LaneID][phaseIndex].upValue 	= (eyeDiagram[SiteID][MacroID][LaneID][2 * phaseIndex].upValue
																				   	   + eyeDiagram[SiteID][MacroID][LaneID][2 * phaseIndex + 1].upValue) / 2;
						phaseShrink[SiteID][MacroID][LaneID][phaseIndex] = phaseIndex + (iMonitorDelay - uiSize / 2) / 2;
					}
				}
				else if (iRateMode == 2)
				{
					for (INT phaseIndex = 0; phaseIndex < uiSize / 4; phaseIndex ++)
					{
						plotShrink[SiteID][MacroID][LaneID][phaseIndex].bottomValue = (eyeDiagram[SiteID][MacroID][LaneID][4 * phaseIndex].bottomValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][4 * phaseIndex + 1].bottomValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][4 * phaseIndex + 2].bottomValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][4 * phaseIndex + 3].bottomValue) / 4;
						plotShrink[SiteID][MacroID][LaneID][phaseIndex].upValue 	= (eyeDiagram[SiteID][MacroID][LaneID][4 * phaseIndex].upValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][4 * phaseIndex + 1].upValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][4 * phaseIndex + 2].upValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][4 * phaseIndex + 3].upValue) / 4;
						phaseShrink[SiteID][MacroID][LaneID][phaseIndex] = phaseIndex + (iMonitorDelay - uiSize / 2) / 4;
					}
				}
				else if (iRateMode == 3)
				{
					for (INT phaseIndex = 0; phaseIndex < uiSize / 8; phaseIndex ++)
					{
						plotShrink[SiteID][MacroID][LaneID][phaseIndex].bottomValue = (eyeDiagram[SiteID][MacroID][LaneID][8 * phaseIndex].bottomValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][8 * phaseIndex + 1].bottomValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][8 * phaseIndex + 2].bottomValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][8 * phaseIndex + 3].bottomValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][8 * phaseIndex + 4].bottomValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][8 * phaseIndex + 5].bottomValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][8 * phaseIndex + 6].bottomValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][8 * phaseIndex + 7].bottomValue) / 8;
						plotShrink[SiteID][MacroID][LaneID][phaseIndex].upValue 	= (eyeDiagram[SiteID][MacroID][LaneID][8 * phaseIndex].upValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][8 * phaseIndex + 1].upValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][8 * phaseIndex + 2].upValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][8 * phaseIndex + 3].upValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][8 * phaseIndex + 4].upValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][8 * phaseIndex + 5].upValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][8 * phaseIndex + 6].upValue
								   	   	   	   	   	   	   	   	   	   	   	   	   	   + eyeDiagram[SiteID][MacroID][LaneID][8 * phaseIndex + 7].upValue) / 8;
						phaseShrink[SiteID][MacroID][LaneID][phaseIndex] = phaseIndex + (iMonitorDelay - uiSize / 2) / 8;
					}
				}

				/*plot begin*/
				plot << "\n------------------------------------------\n";
				plot << "\n------------------------------------------\n";
				plot << "\t SiteID : " << SiteID;
				plot << "\n------------------------------------------\n";
				plot << "\n MacroID : " << MacroID << " ; LaneID : "<< LaneID << " ; Ratemode :" << iRateMode << "\n\n";

				/*plot x_axit */
				plot << "\n\n\n          ";
				for (short i = 0; i < 64; i ++)
				{
					if (phaseShrink[SiteID][MacroID][LaneID][i] < 0)
						plot << "-";
					else
						plot << " ";
				}
				plot << "\n          ";
				for (short i = 0; i < 64; i ++)
				{
					if (abs(phaseShrink[SiteID][MacroID][LaneID][i]) / 10 != 0)
						plot << abs(phaseShrink[SiteID][MacroID][LaneID][i]) / 10;
					else
						plot<< " ";
				}
				plot<<"\n          ";
				for (short i = 0; i < 64; i ++)
				{
					plot << abs(phaseShrink[SiteID][MacroID][LaneID][i]) % 10;
				}
				plot << "\n         +";
				for (short i = 0; i < 64; i ++)
				{
					plot << "-";
				}

				/*plot y_axit*/
				for (INT y = 64; y >= -64; y -= 4)
				{
					plot << "\n" << setw(9) << y << "|";
					for (short i = 0; i < 64; i ++)
					{
						if ((y > plotShrink[SiteID][MacroID][LaneID][i].upValue) or (y < plotShrink[SiteID][MacroID][LaneID][i].bottomValue))
							plot << "*";
						else if((y <= plotShrink[SiteID][MacroID][LaneID][i].upValue) and (y >= plotShrink[SiteID][MacroID][LaneID][i].bottomValue))
							plot << ".";
						else
							plot << "*";
					}
				}
			}
			plot << endl;
		}
	FOREACH_ACTIVESITE_END

	hout(EYEPLOT) << plot.str();
	//PUT_DATALOG(plot.str());
}

void DynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, HILINK_Regs_Base& reg,uint csrIndex,LANE_INT& perLane_value,uint id){
	if(reg.getType()!=HILINK_PERLANE_REGISTER){
		cerr<<"Error: "<<__FUNCTION__<<" in d2s-block "<<d2sFramework::get_current_prefix()<<" Register: "<<reg.getName()<<" is not PerLane type!"<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	map<int,long long> perLane_data;
	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
	{
		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
		const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

		selectMacro(MacroID);
		for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
		{
			UINT LaneID = vLane[laneIndex];
			parseSiteDataFromLaneInt(perLane_data,perLane_value,MacroID,LaneID);
			ostringstream str;
			str<<reg.getName()<<"M"<<MacroID<<"L"<<LaneID<<"ID"<<id;
			reg.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
			reg.Write2DUT_DYN(csrIndex,perLane_data,str.str());
		}
	}
	selectMacro_MB(MacroLane_Sel);
}

void DynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, HILINK_Regs_Base& reg,uint csrIndex,MACRO_INT& perMacro_value,uint CSSlice,uint id){
	if(reg.getType()!=HILINK_PERMACRO_REGISTER){
		cerr<<"Error: "<<__FUNCTION__<<" in d2s-block "<<d2sFramework::get_current_prefix()<<" Register: "<<reg.getName()<<" is not PerMacro type!"<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	map<int,long long> perMacro_data;
	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
	{
		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
		selectMacro(MacroID);

		parseSiteDataFromMacroInt(perMacro_data,perMacro_value,MacroID);
		ostringstream str;
		str<<reg.getName()<<"M"<<MacroID<<"ID"<<id;
		reg.MacroID(MacroID).SliceID(CSSlice).Broadcast(0);
		reg.Write2DUT_DYN(csrIndex,perMacro_data,str.str());
	}
	selectMacro_MB(MacroLane_Sel);
}

void Read2IDString(const MACRO_LANE_SEL& MacroLane_Sel,const uint addr,const string& id){
	d2s_JTAG& jtag=d2s_JTAG::Instance();
	for(uint macroIndex=0;macroIndex<MacroLane_Sel.size();macroIndex++){
		uint MacroID=MacroLane_Sel[macroIndex].MacroID;
		selectMacro(MacroID);
		ostringstream str;
		str<<"_ADDR_"<<hex<<addr<<dec<<"M"<<MacroID<<id;
		jtag.read(addr>>1,str.str());
	}
	selectMacro_MB(MacroLane_Sel);
}

void getReadValue(const MACRO_LANE_SEL& MacroLane_Sel,uint addr,MACRO_INT& permacro_value,const string& id){
	d2s_JTAG& jtag=d2s_JTAG::Instance();
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
	for(uint macroIndex=0;macroIndex<MacroLane_Sel.size();macroIndex++){
		uint MacroID=MacroLane_Sel[macroIndex].MacroID;

		ostringstream str;
		str<<"_ADDR_"<<hex<<addr<<dec<<"M"<<MacroID<<id;
		permacro_value[SiteID][MacroID]=jtag.getReadValue(str.str())[SiteID];
	}
	FOREACH_ACTIVESITE_END
}
void Read2IDString(const MACRO_LANE_SEL& MacroLane_Sel,HILINK_Regs_Base& reg,uint csrIndex,const string& id){
	for(uint macroIndex=0;macroIndex<MacroLane_Sel.size();macroIndex++){
		uint MacroID=MacroLane_Sel[macroIndex].MacroID;
		selectMacro(MacroID);

		if(reg.getType()==HILINK_PERMACRO_REGISTER){
			reg.MacroID(MacroID);
			reg.Broadcast(0);
			ostringstream str;
			str<<reg.getName()<<"_CSR"<<csrIndex<<"M"<<MacroID<<"_"<<id;
			reg.Read2IDString(csrIndex,str.str());
		}
		else{
			const vector<uint>& vLane=MacroLane_Sel[macroIndex].vLane;
			for(uint laneIndex=0;laneIndex<vLane.size();laneIndex++){
				uint LaneID=vLane[laneIndex];
				reg.MacroID(MacroID);
				reg.SliceID(LaneID);
				reg.Broadcast(0);
				ostringstream str;
				str<<reg.getName()<<"_CSR"<<csrIndex<<"M"<<MacroID<<"L"<<LaneID<<"_"<<id;
				reg.Read2IDString(csrIndex,str.str());
			}
		}
	}
	selectMacro_MB(MacroLane_Sel);
}

void ExpectValue(const MACRO_LANE_SEL& MacroLane_Sel ,HILINK_Regs_Base& reg, uint csrIndex,uint value, uint mask){
	for(uint macroIndex=0;macroIndex<MacroLane_Sel.size();macroIndex++){
		uint MacroID=MacroLane_Sel[macroIndex].MacroID;
		selectMacro(MacroID);

		if(reg.getType()==HILINK_PERMACRO_REGISTER){
			reg.MacroID(MacroID);
			reg.Broadcast(0);
			reg.ExpectValue(csrIndex,value,mask);
		}
		else{
			const vector<uint>& vLane=MacroLane_Sel[macroIndex].vLane;
			for(uint laneIndex=0;laneIndex<vLane.size();laneIndex++){
				uint LaneID=vLane[laneIndex];
				reg.MacroID(MacroID);
				reg.SliceID(LaneID);
				reg.Broadcast(0);
				reg.ExpectValue(csrIndex,value,mask);
			}
		}
	}
	selectMacro_MB(MacroLane_Sel);
}

void ExpectSegment(const MACRO_LANE_SEL& MacroLane_Sel ,const T_REG_INFO_EX& reg_info_ex,uint value){
	UINT lb = reg_info_ex.reg_info.low_bit;
	UINT hb = reg_info_ex.reg_info.hi_bit;
	UINT csr = reg_info_ex.reg_info.csr;

	UINT mask = 0xFFFF;
	mask &= HI_BIT_MASK[hb];
	mask &= ~LO_BIT_MASK[lb];

	value <<= lb;
	value &= mask;

	mask = ~mask;
	ExpectValue(MacroLane_Sel,reg_info_ex.parent,csr,value,mask);
}

void getReadValue(const MACRO_LANE_SEL& MacroLane_Sel,HILINK_Regs_Base& reg,uint csrIndex,LANE_INT& lane_int,const string& id){
	if(reg.getType()!=HILINK_PERLANE_REGISTER){
		cerr<<"Error: "<<__FUNCTION__<<" in d2s-block "<<d2sFramework::get_current_prefix()<<" Register: "<<reg.getName()<<" is not PerLane type!"<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
	for(uint macroIndex=0;macroIndex<MacroLane_Sel.size();macroIndex++){
		uint MacroID=MacroLane_Sel[macroIndex].MacroID;

		const vector<uint>& vLane=MacroLane_Sel[macroIndex].vLane;
		for(uint laneIndex=0;laneIndex<vLane.size();laneIndex++){
			uint LaneID=vLane[laneIndex];

			ostringstream str;
			str<<reg.getName()<<"_CSR"<<csrIndex<<"M"<<MacroID<<"L"<<LaneID<<"_"<<id;
			lane_int[SiteID][MacroID][LaneID]=d2s_JTAG::Instance().getReadValue(str.str())[SiteID];
		}
	}
	FOREACH_ACTIVESITE_END
}

void getReadValue(const MACRO_LANE_SEL& MacroLane_Sel,HILINK_Regs_Base& reg,uint csrIndex,MACRO_INT& macro_int,const string& id){
	if(reg.getType()!=HILINK_PERMACRO_REGISTER){
		cerr<<"Error: "<<__FUNCTION__<<" in d2s-block "<<d2sFramework::get_current_prefix()<<" Register: "<<reg.getName()<<" is not PerMacro type!"<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
	for(uint macroIndex=0;macroIndex<MacroLane_Sel.size();macroIndex++){
		uint MacroID=MacroLane_Sel[macroIndex].MacroID;

		ostringstream str;
		str<<reg.getName()<<"_CSR"<<csrIndex<<"M"<<MacroID<<"_"<<id;
		macro_int[SiteID][MacroID]=d2s_JTAG::Instance().getReadValue(str.str())[SiteID];
	}
	FOREACH_ACTIVESITE_END
}


void hasJTAGPassed(const string& label,SITE_PASSFAIL_RESULT& result){
	result.init(false);
//		result[SiteID]=jtag.hasPassed(label);
		map<uint32_t, bool> map_pass_fail_result = TheInst.Digital().PatEng().GetPassFail();

		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		bool size_pass = map_pass_fail_result[SiteID];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
		if(PrintDebugEn) cout<<"map_pass_fail_result["<<SiteID<<"] = "<<map_pass_fail_result[SiteID]<<endl;
		result[SiteID] = size_pass;
		FOREACH_ACTIVESITE_END

}
bool hasAllSitesPassed(){
	SITE_PASSFAIL_RESULT Result;

    map<uint32_t, bool> map_pass_fail_result = TheInst.Digital().PatEng().GetPassFail();

	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
	bool size_pass = map_pass_fail_result[SiteID];//(api->Get_result_bin_status() == BIN_PASS) ? true : false;
	if(PrintDebugEn) cout<<"map_pass_fail_result["<<SiteID<<"] = "<<map_pass_fail_result[SiteID]<<endl;
	Result[SiteID] = size_pass;

	FOREACH_ACTIVESITE_END
	return Result.isAllSitePassed();
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


SITE_INT H16_FailBin_Flag;
string m_TestName = "";
int m_TestNumber = -999;
int m_HardBin = -999;
int m_SoftBin = -999;
int isDPS128 = 0;


void judgeAndLog_ParametricTest(INT SiteID, string testname, string Macro_Lane_Name, double LimitL, double TestVal, double LimitH,int testNumber) {

    int Fail_flag = 0;
    if (TestVal < LimitL || TestVal > LimitH) {
        Fail_flag = 1;
        H16_FailBin_Flag[SiteID] = 1;
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
//    TheSoft.Flow().TestLimit(Macro_Lane_Name,SiteID,TestVal,LimitL,LimitH,m_HardBin,m_SoftBin,"","\t"+testname,testNumber,E_Fail,E_LEFTCLOSE_RIGHTCLOSE);
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
        H16_FailBin_Flag = 1;
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


void HiLink_PerLane_DummyJudge(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname, LANE_DOUBLE& TempResult, JUDGE_PIN Judge_Pin) {
	/***************sub func begin****************/
//	INT SiteID = CURRENT_SITE_NUMBER() - 1;
//	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
//		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//		const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//
//		STRING_VECTOR 	JudgePins;
//		JudgePins.clear();
//		ARRAY_D			ValueForJudge;
//		ValueForJudge.resize(vLane.size());
//
//		for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
//			UINT LaneID = vLane[laneIndex];
//			switch (Judge_Pin) {
//				case 0: JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_P);break;
//				case 1: JudgePins.push_back(LANE_INFO[MacroID][LaneID].RX_N);break;
//				case 2: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);break;
//				case 3: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_N);break;
//				default: JudgePins.push_back(LANE_INFO[MacroID][LaneID].TX_P);break;
//			}
//			ValueForJudge[laneIndex] = TempResult[SiteID][MacroID][LaneID];
//		}
//
//		TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, testname, TM::Pass, ValueForJudge);
//		/***************sub func end****************/
//	}
}


void HiLink_PerMacro_DummyJudge(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname, MACRO_DOUBLE& TempResult, JUDGE_PIN Judge_Pin) {
	/***************sub func begin****************/
//	INT SiteID = CURRENT_SITE_NUMBER() - 1;
//	STRING_VECTOR JudgePins;
//	JudgePins.clear();
//	ARRAY_D			ValueForJudge;
//	ValueForJudge.resize(MacroLane_Sel.size());
//	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
//		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//		switch (Judge_Pin) {
//			case 0: JudgePins.push_back(LANE_INFO[MacroID][0].RX_P);break;
//			case 1: JudgePins.push_back(LANE_INFO[MacroID][0].RX_N);break;
//			case 2: JudgePins.push_back(LANE_INFO[MacroID][0].TX_P);break;
//			case 3: JudgePins.push_back(LANE_INFO[MacroID][0].TX_N);break;
//			default: JudgePins.push_back(LANE_INFO[MacroID][0].TX_P);break;
//		}
//		ValueForJudge[macroIndex] = TempResult[SiteID][MacroID];
//	}
//	TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, testname, TM::Pass, ValueForJudge);
//	/***************sub func end****************/
}


void HiLink_PerSite_DummyJudge(const MACRO_LANE_SEL& MacroLane_Sel, const STRING &testname, SITE_DOUBLE& TempResult, JUDGE_PIN Judge_Pin) {
	/***************sub func begin****************/
//	INT SiteID = CURRENT_SITE_NUMBER() - 1;
//	STRING	JudgePins;
//	UINT firstmacroid = HILINK_INFO.getFirstMacroID();
//	switch (Judge_Pin)
//	{
//		case 0: JudgePins = LANE_INFO[firstmacroid][0].RX_P;break;
//		case 1: JudgePins = LANE_INFO[firstmacroid][0].RX_N;break;
//		case 2: JudgePins = LANE_INFO[firstmacroid][0].TX_P;break;
//		case 3: JudgePins = LANE_INFO[firstmacroid][0].TX_N;break;
//		default: JudgePins = "";break;
//	}
//	DOUBLE		ValueForJudge = TempResult[SiteID];
//	TestSet.cont(TM::CONTINUE).judgeAndLog_ParametricTest(JudgePins, testname, TM::Pass, ValueForJudge);
//	/***************sub func end****************/
}


void SIGDET_expect_everyone_ALL0(const MACRO_LANE_SEL& MacroLane_Sel,T_ALOS_SEARCH_INFO& search_info,SITE_PASSFAIL_RESULT& ExpectResult){
	d2s_JTAG& jtag = d2s_JTAG::Instance();
	const T_REG_INFO_EX& 	reg_info_ex=search_info.reg_info_ex;
	uint value=0;
	UINT lb = reg_info_ex.reg_info.low_bit;
	UINT hb = reg_info_ex.reg_info.hi_bit;
	UINT csr = reg_info_ex.reg_info.csr;

	UINT mask = 0xFFFF;
	mask &= HI_BIT_MASK[hb];
	mask &= ~LO_BIT_MASK[lb];

	value <<= lb;
	value &= mask;

	mask = ~mask;

	ExpectResult.init(false);

//	TransactionPort pRX(search_info.RxPortName);
//	fr.registerTransactionPort(pRX);


	d2s::d2s_LABEL_BEGIN("ALOS_EXPECT_everyone_ALL0", Global_D2S_Mode);
//		jtag.enablePassFailCheckForNextExecution();
//		if(!search_info.ALOS_RX_Pattern.empty()){
//			pRX.execLabel(search_info.ALOS_RX_Pattern,search_info.ALOS_RX_Pattern_cycle);
//		}

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size();macroIndex++) {
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<uint>& vLane = MacroLane_Sel[macroIndex].vLane;

			selectMacro(MacroID);

			for (unsigned int laneIndex = 0; laneIndex < vLane.size();laneIndex++) {
				uint LaneID = vLane[laneIndex];

				search_info.reg_info_ex.parent.MacroID(MacroID).SliceID(LaneID).Broadcast(0);

				for (size_t read_index = 0; read_index < search_info.read_count; read_index++) {
					search_info.reg_info_ex.parent.ExpectValue(csr,value,mask);
				}
			}
		}
	d2s::d2s_LABEL_END;
	hasJTAGPassed("ALOS_EXPECT_everyone_ALL0",ExpectResult);
}

void SIGDET_expect_theLane(uint MacroID,uint LaneID,uint value,T_ALOS_SEARCH_INFO& search_info,SITE_PASSFAIL_RESULT& ExpectResult){
	d2s_JTAG& jtag = d2s_JTAG::Instance();
	ostringstream str;
	str<<"SIGDET_expect_theLane_ALL"<<value;
	const T_REG_INFO_EX& 	reg_info_ex=search_info.reg_info_ex;
	UINT lb = reg_info_ex.reg_info.low_bit;
	UINT hb = reg_info_ex.reg_info.hi_bit;
	UINT csr = reg_info_ex.reg_info.csr;

	UINT mask = 0xFFFF;
	mask &= HI_BIT_MASK[hb];
	mask &= ~LO_BIT_MASK[lb];

	value <<= lb;
	value &= mask;

	mask = ~mask;

	ExpectResult.init(false);

//	TransactionPort pRX(search_info.RxPortName);
//	fr.registerTransactionPort(pRX);


	d2s::d2s_LABEL_BEGIN(str.str(), Global_D2S_Mode);
//		jtag.enablePassFailCheckForNextExecution();
//		if(!search_info.ALOS_RX_Pattern.empty()){
//			pRX.execLabel(search_info.ALOS_RX_Pattern,search_info.ALOS_RX_Pattern_cycle);
//		}

		selectMacro(MacroID);

		search_info.reg_info_ex.parent.MacroID(MacroID).SliceID(LaneID).Broadcast(0);

		for (size_t read_index = 0; read_index < search_info.read_count; read_index++) {
			search_info.reg_info_ex.parent.ExpectValue(csr,value,mask);
		}

	d2s::d2s_LABEL_END;
	hasJTAGPassed(str.str(),ExpectResult);
}

void SIGDET_Search_theLane(uint MacroID,uint LaneID,T_ALOS_SEARCH_INFO& search_info,LANE_DOUBLE& All0_min_perlane,LANE_DOUBLE& All1_max_perlane,
		HILINK_LANE_DATA_CONTAINER<SIGDET_STATUS>& SIGDET_status_allsite,
		LANE_SIGDET_STATUS& SIGDET_status_perlane,double spec_val,double step_val,int d2s_mode) {
	SITE_PASSFAIL_RESULT ExpectResult;
	bool all0_expect_passed_allsite=false;
	if((!SIGDET_status_allsite[MacroID][LaneID].find_all0) || d2s_mode !=1){
	  SIGDET_expect_theLane(MacroID,LaneID,0,search_info,ExpectResult);
	  SIGDET_status_allsite[MacroID][LaneID].find_all0=true;
	  all0_expect_passed_allsite=ExpectResult.isAllSitePassed();

	  FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		  if(!SIGDET_status_perlane[SiteID][MacroID][LaneID].find_all0 and !ExpectResult[SiteID]){
			  All0_min_perlane[SiteID][MacroID][LaneID]=spec_val+step_val;
			 SIGDET_status_perlane[SiteID][MacroID][LaneID].find_all0=true;
		  }
		  SIGDET_status_allsite[MacroID][LaneID].find_all0 =
		  (SIGDET_status_allsite[MacroID][LaneID].find_all0 && SIGDET_status_perlane[SiteID][MacroID][LaneID].find_all0);
	  FOREACH_ACTIVESITE_END
	}

	if((!SIGDET_status_allsite[MacroID][LaneID].find_all1 && !all0_expect_passed_allsite) || d2s_mode !=1){
	  SIGDET_expect_theLane(MacroID,LaneID,1,search_info,ExpectResult);
	  SIGDET_status_allsite[MacroID][LaneID].find_all1=true;
	  FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		  if(!SIGDET_status_perlane[SiteID][MacroID][LaneID].find_all1 and ExpectResult[SiteID]){
			  All1_max_perlane[SiteID][MacroID][LaneID]=spec_val;
			  SIGDET_status_perlane[SiteID][MacroID][LaneID].find_all1=true;
		  }
		  SIGDET_status_allsite[MacroID][LaneID].find_all1 =
	      (SIGDET_status_allsite[MacroID][LaneID].find_all1 && SIGDET_status_perlane[SiteID][MacroID][LaneID].find_all1);
	  FOREACH_ACTIVESITE_END
	}

}

void SIGDET_Search(const MACRO_LANE_SEL& MacroLane_Sel,T_ALOS_SEARCH_INFO& search_info,LANE_DOUBLE& All0_min_perlane,LANE_DOUBLE& All1_max_perlane,LANE_DOUBLE& vgap_perlane){
//	double start_val=search_info.start_val;
//	double stop_val=search_info.stop_val;
//	double step_val=search_info.step_val;
//	vector<string>& speclist=search_info.speclist;
//
//	All0_min_perlane.init(9999);
//	All1_max_perlane.init(-9999);
//	vgap_perlane.init(9999);
//
//
//	if(start_val<=stop_val){
//		cerr<<"Error: start value of ALOS search should be larger than stop value!"<<endl;
//		return;
//	}
//	if(step_val<=0.0){
//		cerr<<"Error: step value of ALOS search should be larger than 0.0!"<<endl;
//		return;
//	}
//	if(speclist.size()==0){
//		cerr<<"Error: No LevelSpec for ALOS search!"<<endl;
//		return;
//	}
//
//	vector<double> org_spec_Values;
//	org_spec_Values.clear();
//	for(int i =0; i<speclist.size(); i++)
//	{
//		org_spec_Values.push_back(Primary.getLevelSpec().getSpecValue(speclist[i]));
//	}
//
//	double spec_val;
//	bool isEveryLaneAll0=true;
//
//	SITE_PASSFAIL_RESULT ExpectResult;
//
//	HILINK_LANE_DATA_CONTAINER<SIGDET_STATUS> SIGDET_status_allsite;
//	LANE_SIGDET_STATUS SIGDET_status_perlane;
//
//	SIGDET_STATUS init_val={false,false};
//	SIGDET_status_allsite.init(init_val);
//	SIGDET_status_perlane.init(init_val);
//
//	for(spec_val=start_val; spec_val>=stop_val; spec_val=spec_val-step_val){
//		  hout(DETAIL) << "Alos: TxMain= "<<" "<<spec_val<<endl;
//
//		  for (uint i =0; i<speclist.size(); i++)
//		  {
//			  Primary.getLevelSpec().change(speclist[i], spec_val);
//			  //FLUSH(TM::APRM);
//		  }
//
//		  if(isEveryLaneAll0){
//			  SIGDET_expect_everyone_ALL0(MacroLane_Sel,search_info,ExpectResult);
//			  isEveryLaneAll0=ExpectResult.isAllSitePassed();
//		  }
//		  if(!isEveryLaneAll0 || Global_D2S_Mode !=1){
//			  bool everyone_find_all0=true;
//			  bool everyone_find_all1=true;
//			  for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size();macroIndex++) {
//				  UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//				  const vector<uint>& vLane = MacroLane_Sel[macroIndex].vLane;
//				  for (unsigned int laneIndex = 0; laneIndex < vLane.size();laneIndex++) {
//					  uint LaneID = vLane[laneIndex];
//
//					  SIGDET_Search_theLane(MacroID,LaneID,search_info,
//							  	  	  	  All0_min_perlane,All1_max_perlane,
//							  	  	  	  SIGDET_status_allsite,SIGDET_status_perlane,
//							  	  	  	  spec_val,step_val,
//										  Global_D2S_Mode);
//
//					  everyone_find_all0=(everyone_find_all0 && SIGDET_status_allsite[MacroID][LaneID].find_all0);
//					  everyone_find_all1=(everyone_find_all1 && SIGDET_status_allsite[MacroID][LaneID].find_all1);
//				  }
//			  }
//			  if(everyone_find_all0 && everyone_find_all1 && Global_D2S_Mode != 2){
//				  break;
//			  }
//		  }
//	 }
//
//	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//	  for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size();macroIndex++) {
//		  UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//		  const vector<uint>& vLane = MacroLane_Sel[macroIndex].vLane;
//		  for (unsigned int laneIndex = 0; laneIndex < vLane.size();laneIndex++) {
//			  uint LaneID = vLane[laneIndex];
//			  vgap_perlane[SiteID][MacroID][LaneID]= All0_min_perlane[SiteID][MacroID][LaneID]-All1_max_perlane[SiteID][MacroID][LaneID];
//		  }
//	  }
//   FOREACH_ACTIVESITE_END
//   for (uint i =0; i<speclist.size(); i++){
//	  Primary.getLevelSpec().change(speclist[i], org_spec_Values[i]);
//	  //FLUSH(TM::APRM);
//   }
}

void Relay_Control(STRING sTxRelayState)
{
//	hout(GENERAL) << "********** TxRelayState = " << sTxRelayState << " **********" << endl;
//
//	if (sTxRelayState == "TESTER")
//	{
//		FLEX_RELAY frelay;
//
//		frelay.util(TXUTI).off();
//
//		frelay.wait(3 ms);
//		frelay.execute();
//	}
//	else if (sTxRelayState == "ONBOARD_TERM")
//	{
//		FLEX_RELAY frelay;
//
//		frelay.util(TXUTI).on();
//
//		frelay.wait(3 ms);
//		frelay.execute();
//	}
}

//add by thy 20211129
PinArrayDouble PPMU_FIMV_measure(string Pins,double iforce,double vExpect,double waittime,int sampleSize,bool disconnect)
{
	TheInst.PPMU().Pins(Pins).SetClear();
	TheInst.PPMU().Pins(Pins).SetVClampH((1.25*vExpect)<6.5?(1.25*vExpect):6.5);
//	TheInst.PPMU().Pins(Pins).SetVClampL((-1.25*vExpect)>-2?(-1.25*vExpect):-2);
	TheInst.PPMU().Pins(Pins).SetVClampL(-0.5);
	TheInst.PPMU().Pins(Pins).SetIRange(fabs(iforce*1.2));
	TheInst.PPMU().Pins(Pins).SetMeasureType(E_MEASURE);
	TheInst.PPMU().Pins(Pins).SetMeasureMode(E_DC_FI_MV);
	TheInst.PPMU().Pins(Pins).Connect(1);
	TheInst.PPMU().Pins(Pins).SetIForce(iforce);
	TheInst.PPMU().Pins(Pins).SetSampleSize(sampleSize);
	TheInst.PPMU().Pins(Pins).SetWaitTime(waittime);
	TheInst.PPMU().Pins(Pins).Measure();

	PinArrayDouble result = TheInst.PPMU().Pins(Pins).GetMeasureResults();
	if(disconnect)
	{
	TheInst.PPMU().Pins(Pins).SetIForce(0.0);
	TheInst.PPMU().Pins(Pins).Connect(0);
//	TheInst.PPMU().Pins(Pins).Apply();
//	TheInst.PPMU().Pins(Pins).Measure();
	}
	return result;
}

PinArrayDouble PPMU_FVMI_measure(string Pins,double vforce,double irange,double waittime,int sampleSize,bool disconnect)
{
	TheInst.PPMU().Pins(Pins).SetClear();
	TheInst.PPMU().Pins(Pins).SetMeasureType(E_MEASURE)	;
	TheInst.PPMU().Pins(Pins).SetIClampH(0.95*irange);
	TheInst.PPMU().Pins(Pins).SetIClampL(-0.95*irange);
	TheInst.PPMU().Pins(Pins).SetIRange(irange);
	TheInst.PPMU().Pins(Pins).SetVForce(vforce)	;
	TheInst.PPMU().Pins(Pins).SetMeasureMode(E_DC_FV_MI);
	TheInst.PPMU().Pins(Pins).Connect(1);
	TheInst.PPMU().Pins(Pins).SetSampleSize(sampleSize);
	TheInst.PPMU().Pins(Pins).SetWaitTime(waittime);
	TheInst.PPMU().Pins(Pins).Measure();

	PinArrayDouble result = TheInst.PPMU().Pins(Pins).GetMeasureResults();
	if(disconnect)
	{
		TheInst.PPMU().Pins(Pins).Connect(0);
		TheInst.PPMU().Pins(Pins).SetVForce(0.0);
		TheInst.PPMU().Pins(Pins).Measure();
		TheInst.PPMU().Pins(Pins).Apply();
	}
	return result;
}

void PPMU_FI_Waitmeasure(string Pins,double iforce,double vExpect,double waittime,int sampleSize){

	TheInst.PPMU().Pins(Pins).SetClear();
	TheInst.PPMU().Pins(Pins).SetVClampH((1.25*vExpect)<6.5?(1.25*vExpect):6.5);
//	TheInst.PPMU().Pins(Pins).SetVClampL((-1.25*vExpect)>-2?(-1.25*vExpect):-2);
	TheInst.PPMU().Pins(Pins).SetVClampL(-0.5);
	TheInst.PPMU().Pins(Pins).SetIRange(fabs(iforce*1.2));
	TheInst.PPMU().Pins(Pins).SetMeasureType(E_MEASURE);
	TheInst.PPMU().Pins(Pins).SetMeasureMode(E_DC_FI_MV);
	TheInst.PPMU().Pins(Pins).Connect(1);
	TheInst.PPMU().Pins(Pins).SetIForce(iforce);
	TheInst.PPMU().Pins(Pins).SetSampleSize(sampleSize);
	TheInst.PPMU().Pins(Pins).SetWaitTime(waittime);
}


void PrintLaneSegInfo(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, LANE_INT perlane_value) {
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				hout(DETAIL) << "MacroID = " << MacroID << "\t" << "LaneID = " << LaneID << "\t"
							  << reg_info_ex.reg_info.reg_name << " = " << perlane_value[SiteID][MacroID][LaneID] << endl;
			}
		}
	FOREACH_ACTIVESITE_END
}


/************todo:to be optimize only support DS clkRegs Regs Now!***********/
void Update_CSReg_ForDynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, MACRO_INT& Segmentvalue, MACRO_INT& CSRvalue)
{
	CSRvalue.init(0);
	HILINK_Regs_Base& reg = reg_info_ex.parent;
	UINT csrIndex = reg_info_ex.reg_info.csr;

	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			CSRvalue[SiteID][MacroID] = reg.fill_bits(CSRvalue[SiteID][MacroID], reg_info_ex, Segmentvalue[SiteID][MacroID]);
		}
	FOREACH_ACTIVESITE_END
}

void Update_DSReg_ForDynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, const T_REG_INFO_EX& reg_info_ex, LANE_INT& Segmentvalue, LANE_INT& CSRvalue)
{
	CSRvalue.init(0);
	HILINK_Regs_Base& reg = reg_info_ex.parent;
	UINT csrIndex = reg_info_ex.reg_info.csr;

	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
				UINT LaneID = vLane[laneIndex];
				if (reg.getName() == "DS_CLK") {
					CSRvalue[SiteID][MacroID][LaneID] = reg.fill_bits(DS.clkRegs.csr[csrIndex], reg_info_ex, Segmentvalue[SiteID][MacroID][LaneID]);
					cout << "DS.clkRegs.csr[csrIndex] = " << DS.clkRegs.csr[csrIndex] << endl;
					cout << "CSRvalue[SiteID][MacroID][LaneID] = " << CSRvalue[SiteID][MacroID][LaneID] << endl;
				} else if (reg.getName() == "DS_TX") {
					CSRvalue[SiteID][MacroID][LaneID] = reg.fill_bits(DS.txRegs.csr[csrIndex], reg_info_ex, Segmentvalue[SiteID][MacroID][LaneID]);
				} else if (reg.getName() == "DS_RX") {
					CSRvalue[SiteID][MacroID][LaneID] = reg.fill_bits(DS.rxRegs.csr[csrIndex], reg_info_ex, Segmentvalue[SiteID][MacroID][LaneID]);
				} else {
					hout(RELEASE) << "Error: can not find related CSR Type " << endl;
					_exit(0);
				}
			}
		}
	FOREACH_ACTIVESITE_END
}


void optimize_RX_cycles(const INT JTAG_CYCLE, DOUBLE DataRate_JTAG, DOUBLE DataRate_pHilink_RX)
{
//	if (JTAG_CYCLE != 0)
//	{
//		INT  pHilink_RX_CYCLE =  (INT)(DataRate_pHilink_RX * 1000 * JTAG_CYCLE / (DataRate_JTAG * 16));
//		Sequencer.stopCycle(pHilink_RX_CYCLE,"pHilink16_RX");
//	}
}


void parseSiteDataFromLaneInt(map<int,long long>& val,LANE_INT& lane_data,uint MacroID,uint LaneID){
	val.clear();
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		val[SiteID] = lane_data[SiteID][MacroID][LaneID];
	FOREACH_ACTIVESITE_END
}

void parseSiteDataFromMacroInt(map<int,long long>& val,MACRO_INT& macro_data,uint MacroID)
{
	val.clear();
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		val[SiteID] = macro_data[SiteID][MacroID];
	FOREACH_ACTIVESITE_END
}


void Update_CSR_ForDynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, LANE_INT& Segmentvalue, LANE_INT& CSRvalue, const T_REG_INFO_EX& reg_info_ex){
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				CSRvalue[SiteID][MacroID][LaneID] = HILINK_Regs_Base::fill_bits(CSRvalue[SiteID][MacroID][LaneID], reg_info_ex, Segmentvalue[SiteID][MacroID][LaneID]);
			}
		}
	FOREACH_ACTIVESITE_END
}


void Update_CSR_ForDynamicWrite(const MACRO_LANE_SEL& MacroLane_Sel, MACRO_INT& Segmentvalue, MACRO_INT& CSRvalue, const T_REG_INFO_EX& reg_info_ex){
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			CSRvalue[SiteID][MacroID] = HILINK_Regs_Base::fill_bits(CSRvalue[SiteID][MacroID], reg_info_ex, Segmentvalue[SiteID][MacroID]);
		}
	FOREACH_ACTIVESITE_END
}

void UpdateSiteData(LANE_INT& lane_data,map<int,long long>& val,uint MacroID,uint LaneID){
	for(map<int,long long>::iterator itr=val.begin();itr!=val.end();itr++){
		lane_data[itr->first][MacroID][LaneID]=itr->second;
	}
}
void UpdateSiteData(MACRO_INT& macro_data,map<int,long long>& val,uint MacroID){
	for(map<int,long long>::iterator itr=val.begin();itr!=val.end();itr++){
		macro_data[itr->first][MacroID]=itr->second;
	}
}
uint int2signbitint(int val,const T_REG_INFO_EX& reg_info_ex){
	uint hb=reg_info_ex.reg_info.hi_bit;
	uint lb=reg_info_ex.reg_info.low_bit;

	uint sign= ( ( (val>=0)?0:1) << (hb-lb));
	uint result = (1 << (hb-lb));
	result = ~result;
	result &= abs(val);
	result |= sign;

	return result;
}







void Load_FirmWare(const MACRO_LANE_SEL& MacroLane_Sel)
{
//	d2s_JTAG& jtag = d2s_JTAG::Instance();
//	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_LoadFirmWare",Global_D2S_Mode);
//
//		selectMacro_MB(MacroLane_Sel);
//		MCU.mcuRegs.setmcurstb(0).Write2DUT(0);
//
//		if (jtag.Context == "DEFAULT"){
//			jtag.execLabel(HILINK_FIRMWARE_LABEL + "_STD", HILINK_FIRMWARE_CYCLE);
//		} else {
//			jtag.execLabel(HILINK_FIRMWARE_LABEL + "_FASTDIFF", HILINK_FIRMWARE_CYCLE);
//		}
//
//	d2s::d2s_LABEL_END;
	string patternName;
    patternName = HILINK_FIRMWARE_LABEL; //block check OK
    TheInst.Digital().Pattern().Start(patternName);
}

void ReadFirmWareRevAndPrint(MACRO_LANE_SEL& MacroLane_Sel)
{
	char 			RawFirmWareRev[MacroLane_Sel.size()][15][256];
	d2s_JTAG& jtag = d2s_JTAG::Instance();
	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_ReadFirmWareRev",Global_D2S_Mode);

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			INT 			addr = 0x1800C;
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			selectMacro(MacroID);

			for (INT i = 0; i < 15; i ++, addr +=  0x2)
			{
				sprintf(RawFirmWareRev[macroIndex][i],"H15_REG_READ_%d_M%d_%s",addr,MacroID,jtag.Context.c_str());
				jtag.read(addr>>1,RawFirmWareRev[macroIndex][i]);
			}
		}

	d2s::d2s_LABEL_END;

	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			INT					FirmWareVersion[15];
			char				FirmWareVersionOut[31];

			for (INT i = 0; i < 15; i ++)
			{
				FirmWareVersion[i] = jtag.getReadValue(RawFirmWareRev[macroIndex][i])[SiteID];
				FirmWareVersionOut[2 * i] = FirmWareVersion[i] & 0x00ff;
				FirmWareVersionOut[2 * i + 1] = (FirmWareVersion[i] & 0xff00)>>8;
			}

			FirmWareVersionOut[30] = '\0';
			hout(GENERAL) << "MacroID = " << MacroID << ":\t" << FirmWareVersionOut << endl;
			ostringstream	PrintFirmWareRev;
			PrintFirmWareRev << "MacroID = " << MacroID << ":\t" << FirmWareVersionOut << endl;
			//PUT_DATALOG(PrintFirmWareRev.str());
		}
	FOREACH_ACTIVESITE_END
}

void FWreadDefaultRegisters2CSR_RefCLKLockRange(const MACRO_LANE_SEL& MacroLane_Sel, INT mCSSlice)
{
	UINT MacroID = MacroLane_Sel[0].MacroID;
	CS.clkRegs.MacroID(MacroID).SliceID(mCSSlice).Broadcast(0);
	CS.clkRegs.ReadAll2CSR();
}

DOUBLE calculate_clocks(INT  mKa, INT  mKb, INT  mJJ, INT  mM, INT  mN, DOUBLE Refclkfreq)
{
	int M,N,JJ,Ka,Kb;
	double  HSCLKfreq, MCLKfreq, VCOfreq;
	M = mM;
	N = mN;
	JJ = mJJ;
	Ka = mKa;
	Kb = mKb;
	HSCLKfreq = Refclkfreq * N / (M * Kb);
	VCOfreq = Refclkfreq * N * Ka / M;
	MCLKfreq = VCOfreq / (Ka * JJ);
	return VCOfreq;
}

void AnalogLosCheck(const MACRO_LANE_SEL& MacroLane_Sel, const INT& ReadCnt, LANE_INT& SigdetLosStat, STRING pRXlabel, LONG cycnum)
{
	d2s_JTAG& jtag = d2s_JTAG::Instance();
//	TransactionPort pRX("pHilink16_RX");
//	fr.registerTransactionPort(pRX);

	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
	{
		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
		const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

		for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
		{
			UINT LaneID = vLane[laneIndex];
			/*************all 0 check (not los)*********/
			sprintf (label, "H16LRTV100_MPB_ANALOG_LOS_ALL0_PerLane_Macro%d_Lane_%d", MacroID, LaneID);
			d2s::d2s_LABEL_BEGIN(label,Global_D2S_Mode);

				jtag.enablePassFailCheckForNextExecution();
//				if (pRXlabel != "") {
//					pRX.execLabel(pRXlabel,cycnum);
//				}
				selectMacro(MacroID);
				DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
				for (INT ReadIdx = 0; ReadIdx < ReadCnt; ReadIdx ++)
				{
					DS.rxRegs.ExpectValue(61, 0, 0x7fff);
				}

			d2s::d2s_LABEL_END;

			sprintf (label, "H16LRTV100_MPB_ANALOG_LOS_ALL0_PerLane_Macro%d_Lane_%d", MacroID, LaneID);
			SITE_PASSFAIL_RESULT		ResAll0;
			ARRAY_I	tmp;
			bool dummy1,dummy2;
//			jtag.hasPassed(label, dummy1, dummy2, tmp);

		    map<uint32_t, bool> map_pass_fail_result = TheInst.Digital().PatEng().GetPassFail();

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				ResAll0[SiteID] = map_pass_fail_result[SiteID];
				if (true == ResAll0[SiteID]) {
					SigdetLosStat[SiteID][MacroID][LaneID] = ALL0;
				}
			FOREACH_ACTIVESITE_END
		}
	}

	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
	{
		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
		const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

		for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
		{
			UINT LaneID = vLane[laneIndex];
			/*************all 1 check (los)*********/
			sprintf (label, "H16LRTV100_MPB_ANALOG_LOS_ALL1_PerLane_Macro%d_Lane_%d", MacroID, LaneID);
			d2s::d2s_LABEL_BEGIN(label,Global_D2S_Mode);

				jtag.enablePassFailCheckForNextExecution();
//				if (pRXlabel != "") {
//					pRX.execLabel(pRXlabel,cycnum);
//				}

				selectMacro(MacroID);
				DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
				for (INT ReadIdx = 0; ReadIdx < ReadCnt; ReadIdx ++)
				{
					DS.rxRegs.ExpectValue(61, 1<<15, 0x7fff);
				}

			d2s::d2s_LABEL_END;


			sprintf (label, "H16LRTV100_MPB_ANALOG_LOS_ALL1_PerLane_Macro%d_Lane_%d", MacroID, LaneID);
			SITE_PASSFAIL_RESULT		ResAll1;
//			ARRAY_I	tmp;
//			bool dummy1,dummy2;
//			jtag.hasPassed(label, dummy1, dummy2, tmp);
		    map<uint32_t, bool> map_pass_fail_result = TheInst.Digital().PatEng().GetPassFail();

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				ResAll1[SiteID] = map_pass_fail_result[SiteID];
				if (true == ResAll1[SiteID]) {
					SigdetLosStat[SiteID][MacroID][LaneID] = ALL1;
				}
			FOREACH_ACTIVESITE_END
		}
	}

	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				if (SigdetLosStat[SiteID][MacroID][LaneID] != ALL1 && SigdetLosStat[SiteID][MacroID][LaneID] != ALL0) {
					SigdetLosStat[SiteID][MacroID][LaneID] = UNSTABLE;
				}
				switch (SigdetLosStat[SiteID][MacroID][LaneID]) {
					case ALL0:
						hout(DETAIL) << "M" << MacroID << "_L" << LaneID << ": " << "\t" <<  "AnalogLos detection ALL not Los" << endl;
						break;
					case ALL1:
						hout(DETAIL) << "M" << MacroID << "_L" << LaneID << ": " << "\t" << "AnalogLos detection ALL Los" << endl;
						break;
					case UNSTABLE:
						hout(DETAIL) << "M" << MacroID << "_L" << LaneID << ": " << "\t" <<  "AnalogLos detection UnStable" << endl;
						break;
				}
			}
		}
	FOREACH_ACTIVESITE_END
}



void Squelch_check(const MACRO_LANE_SEL& MacroLane_Sel, const INT& ReadCnt, LANE_INT& SquelchStat, STRING pRXlabel, LONG cycnum)
{
//	d2s_JTAG& jtag = d2s_JTAG::Instance();
//	TransactionPort pRX("pHilink16_RX");
//	fr.registerTransactionPort(pRX);
//
//	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
//	{
//		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//		const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//
//		for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
//		{
//			UINT LaneID = vLane[laneIndex];
//			/*************all 0 check (not los)*********/
//			sprintf (label, "H16LRTV100_MPB_SQUELCH_ALL0_PerLane_Macro%d_Lane_%d", MacroID, LaneID);
//			d2s::d2s_LABEL_BEGIN(label,Global_D2S_Mode);
//
//				jtag.enablePassFailCheckForNextExecution();
//				if (pRXlabel != "") {
//					pRX.execLabel(pRXlabel,cycnum);
//				}
//				selectMacro(MacroID);
//				DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
//				for (INT ReadIdx = 0; ReadIdx < ReadCnt; ReadIdx ++)
//				{
//					DS.rxRegs.ExpectValue(61, 0, 0xefff);
//				}
//
//			d2s::d2s_LABEL_END;
//
//
//			sprintf (label, "H16LRTV100_MPB_SQUELCH_ALL0_PerLane_Macro%d_Lane_%d", MacroID, LaneID);
//			SITE_PASSFAIL_RESULT		ResAll0;
//			ARRAY_I	tmp;
//			bool dummy1,dummy2;
//			jtag.hasPassed(label, dummy1, dummy2, tmp);
//
//			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//				ResAll0[SiteID] = tmp[SiteID];
//				if (true == ResAll0[SiteID]) {
//					SquelchStat[SiteID][MacroID][LaneID] = ALL0;
//				}
//			FOREACH_ACTIVESITE_END
//		}
//	}
//
//	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
//	{
//		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//		const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//
//		for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
//		{
//			UINT LaneID = vLane[laneIndex];
//			/*************all 1 check (los)*********/
//			sprintf (label, "H16LRTV100_MPB_SQUELCH_ALL1_PerLane_Macro%d_Lane_%d", MacroID, LaneID);
//			d2s::d2s_LABEL_BEGIN(label,Global_D2S_Mode);
//
//				jtag.enablePassFailCheckForNextExecution();
//				if (pRXlabel != "") {
//					pRX.execLabel(pRXlabel,cycnum);
//				}
//
//				selectMacro(MacroID);
//				DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
//				for (INT ReadIdx = 0; ReadIdx < ReadCnt; ReadIdx ++)
//				{
//					DS.rxRegs.ExpectValue(61, 1<<12, 0xefff);
//				}
//
//			d2s::d2s_LABEL_END;
//
//
//			sprintf (label, "H16LRTV100_MPB_SQUELCH_ALL1_PerLane_Macro%d_Lane_%d", MacroID, LaneID);
//			SITE_PASSFAIL_RESULT		ResAll1;
//			ARRAY_I	tmp;
//			bool dummy1,dummy2;
//			jtag.hasPassed(label, dummy1, dummy2, tmp);
//
//			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//				ResAll1[SiteID] = tmp[SiteID];
//				if (true == ResAll1[SiteID]) {
//					SquelchStat[SiteID][MacroID][LaneID] = ALL1;
//				}
//			FOREACH_ACTIVESITE_END
//		}
//	}
//
//
//	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
//		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
//		{
//			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
//
//			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
//			{
//				UINT LaneID = vLane[laneIndex];
//				if (SquelchStat[SiteID][MacroID][LaneID] != ALL1 && SquelchStat[SiteID][MacroID][LaneID] != ALL0) {
//					SquelchStat[SiteID][MacroID][LaneID] = UNSTABLE;
//				}
//				switch (SquelchStat[SiteID][MacroID][LaneID]) {
//					case ALL0:
//						hout(DETAIL) << "M" << MacroID << "_L" << LaneID << ": " << "\t" <<  "Squelch detection ALL not Los (OOB_burst)" << endl;
//						break;
//					case ALL1:
//						hout(DETAIL) << "M" << MacroID << "_L" << LaneID << ": " << "\t" << "Squelch detection ALL Los (OOb_idle)" << endl;
//						break;
//					case UNSTABLE:
//						hout(DETAIL) << "M" << MacroID << "_L" << LaneID << ": " << "\t" <<  "Squelch detection UnStable" << endl;
//						break;
//				}
//			}
//		}
//	FOREACH_ACTIVESITE_END
}


void squelch_det_idle_check(const MACRO_LANE_SEL& MacroLane_Sel, vector<ARRAY_D>& vsquelch_det_idle,STRING LabelName, INT LabelCycle)
{
	INT            	iOffline;
	INT 			read_cont = 10;
//	//GET_SYSTEM_FLAG		("offline",&iOffline);

	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
	{
		const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
		ARRAY_D 		tmp;
		tmp.resize(vLane.size());
		vsquelch_det_idle.push_back(tmp);
	}

	d2s_JTAG& jtag = d2s_JTAG::Instance();
//	TransactionPort pRX("pHilink16_RX");
//	fr.registerTransactionPort(pRX);
//	FW_TASK("DCRT RAM,(pJTAG)");//todo

	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_SQUELCH_NODET",Global_D2S_Mode);

//		pRX.execLabel(LabelName, LabelCycle);

		jtag.wait(0.001*2);

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			selectMacro(MacroID);

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];

				DS.rxRegs.SliceID(LaneID).Broadcast(0);
				for (INT read_index = 0; read_index < read_cont; read_index ++)
				{
					ostringstream id61;
					id61 << "CSR61_" << MacroID << "_" << LaneID << "_read" << read_index;
					DS.rxRegs.Read2IDString(61, id61.str());
				}
			}
		}

	d2s::d2s_LABEL_END;

	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
	{
		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
		const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;


		hout(DETAIL) << "Macro = " << MacroID << endl;

		INT csrindex = 61;
		for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
		{
			UINT LaneID = vLane[laneIndex];
			ARRAY_D squelch_det_tmp;
			squelch_det_tmp.resize(read_cont);

			for (INT read_index = 0; read_index < read_cont; read_index ++)
			{
				ostringstream id61;
				id61 << "CSR61_" << MacroID << "_" << LaneID << "_read" << read_index;
				INT result = jtag.getReadValue(id61.str())[SiteID];

				DS.rxRegs.csr[csrindex] = (uint)(result);

				if (hout.IsRegAccessEn()) {
					hout(REG_ACCESS) << "================ Macro[" << dec << MacroID << "]"<< "  Lane[" << LaneID << "]" << "\tRead ================" << endl;
					DS.rxRegs.DisplayAllSegmentOfCSR(csrindex);
				}

				squelch_det_tmp[read_index] = DS.rxRegs.getsquelch_det();
			}

			DOUBLE squelch_det_all1 = 1;

			for (INT read_index = 0; read_index < read_cont; read_index ++)
			{
				if(squelch_det_tmp[read_index] == 0)
				{
					squelch_det_all1 = 0;
				}
			}
			if (iOffline)
			{
				squelch_det_all1 = 1;
			}

			vsquelch_det_idle[macroIndex][laneIndex] = squelch_det_all1;

			hout(DETAIL) << "laneIndex: " << LaneID << ":" << "\t";
			if (squelch_det_all1 == 0) {
				hout(DETAIL) << "Squelch det OOB idle signal Fail" << endl;
			}
			if (squelch_det_all1 == 1) {
				hout(DETAIL) <<  "Squelch det OOB idle signal Pass" <<endl;
			}
		}
	}
	FOREACH_ACTIVESITE_END
}

void squelch_det_burst_check(const MACRO_LANE_SEL& MacroLane_Sel, vector<ARRAY_D>& vsquelch_det_burst,STRING LabelName, INT LabelCycle)
{
	INT            		iOffline;
	INT 				read_cont = 10;
	//GET_SYSTEM_FLAG		("offline",&iOffline);

	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
	{
		const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
		ARRAY_D 		tmp;
		tmp.resize(vLane.size());
		vsquelch_det_burst.push_back(tmp);
	}

	d2s_JTAG& jtag = d2s_JTAG::Instance();
//	TransactionPort pRX("pHilink16_RX");
//	fr.registerTransactionPort(pRX);
//	FW_TASK("DCRT RAM,(pJTAG)"); //todo

	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_SQUELCH_DET",Global_D2S_Mode);

//        pRX.execLabel(LabelName, LabelCycle);

		jtag.wait(0.001*2);

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			selectMacro(MacroID);

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				DS.rxRegs.SliceID(LaneID).Broadcast(0);
				for (INT read_index = 0; read_index < read_cont; read_index ++)
				{
					ostringstream id61;
					id61 << "CSR61_" << MacroID << "_" << LaneID << "_read" << read_index;
					DS.rxRegs.Read2IDString(61, id61.str());
				}
			}
        }

	d2s::d2s_LABEL_END;

	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
	{
		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
		const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

		hout(DETAIL) << "Macro = " << MacroID << endl;

		INT csrindex = 61;
		for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
		{
			UINT LaneID = vLane[laneIndex];
			ARRAY_I squelch_det_tmp;
			squelch_det_tmp.resize(read_cont);

			for (INT read_index = 0; read_index < read_cont; read_index ++)
			{
				ostringstream id61;
				id61 << "CSR61_" << MacroID << "_" << LaneID << "_read" << read_index;
				INT result = jtag.getReadValue(id61.str())[SiteID];

				DS.rxRegs.csr[csrindex] = (uint)(result);
				if (hout.IsRegAccessEn()) {
					hout(REG_ACCESS) << "================ Macro[" << dec << MacroID << "]"<< "  Lane[" << LaneID << "]" << "\tRead ================" << endl;
					DS.rxRegs.DisplayAllSegmentOfCSR(csrindex);
				}
				squelch_det_tmp[read_index] = DS.rxRegs.getsquelch_det();
			}

			DOUBLE squelch_det_all0 = 0;

			for (INT read_index = 0; read_index < read_cont; read_index ++)
			{
				if(squelch_det_tmp[read_index] == 1)
				{
					squelch_det_all0 = 1;
				}
			}

			if (iOffline)
			{
				squelch_det_all0 = 0;
			}

			vsquelch_det_burst[macroIndex][laneIndex] = squelch_det_all0;

			hout(DETAIL) << "laneIndex: " << LaneID << ":" << "\t";
			if (squelch_det_all0 == 1) {
				hout(DETAIL) << "Squelch det OOB burst signal Fail" << endl;
			}
			if (squelch_det_all0 == 0) {
				hout(DETAIL) <<  "Squelch det OOB burst signal Pass" <<endl;
			}
		}
	}
	FOREACH_ACTIVESITE_END
}

void Tx_RxDET_Detect(const MACRO_LANE_SEL& MacroLane_Sel, LANE_DOUBLE& Tx_rxdet_result)
{
	INT 			tx_rxdet_ready;
	INT 			tx_rxdet_out;
	Tx_rxdet_result.init(-1);

	d2s_JTAG& jtag = d2s_JTAG::Instance();

	for (INT ReadCount = 0; ReadCount < 30; ReadCount ++) {
		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_TXRECEIVER_DET_GetResult",Global_D2S_Mode);

			DS.txRegs.skip_CSR_Check();

			selectMacro_MB(MacroLane_Sel);
			DS.Broadcast();

			DS.txRegs.setrxdet_timer_stop (0).Write2DUT(30);
			DS.txRegs.setrxdet_timer_stop (1).Write2DUT(30);

			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

				selectMacro(MacroID);

				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
				{
					UINT LaneID = vLane[laneIndex];
					DS.txRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
					ostringstream id32;
					id32 << "RXDET_M" << MacroID << "_L" << LaneID << "_CSR32_" << jtag.Context;
					DS.txRegs.Read2IDString(32, id32.str());
				}
			}

		d2s::d2s_LABEL_END;

		INT			iDet_Flag_All = 1;
		INT 		csrindex = 32;

		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
				{
					UINT LaneID = vLane[laneIndex];
					ostringstream id32;
					id32 << "RXDET_M" << MacroID << "_L" << LaneID << "_CSR32_" << jtag.Context;
					INT	result = jtag.getReadValue(id32.str())[SiteID];

					DS.txRegs.csr[csrindex] = (uint)(result);

					if (hout.IsRegAccessEn()) {
						hout(REG_ACCESS) << "================ Macro[" << dec << MacroID << "]"<< "  Lane[" << LaneID << "]" << "\tRead ================" << endl;
						DS.txRegs.DisplayAllSegmentOfCSR(csrindex);
					}

					tx_rxdet_ready = DS.txRegs.gettx_rxdet_ready();

					hout(DETAIL) << "ReadCount = " << dec << ReadCount << "\tM" << MacroID << "_L" << LaneID
								 << " \t tx_rxdet_ready = " << tx_rxdet_ready << endl;

					if (tx_rxdet_ready == 1)
					{
						tx_rxdet_out = DS.txRegs.gettx_rxdet_out();
						if (tx_rxdet_out == 1)
						{
							Tx_rxdet_result[SiteID][MacroID][LaneID] = 1;
							hout(DETAIL) << "M" << MacroID << "_L" << LaneID << ":" << "\t" << "Dect Passed" << endl;
						}
						else
						{
							Tx_rxdet_result[SiteID][MacroID][LaneID] = 0;
							hout(DETAIL) << "M" << MacroID << "_L" << LaneID << ":" << "\t" << "Dect Failed" << endl;
						}
					}
					else
					{
						iDet_Flag_All = 0;
						if (ReadCount >= 29)
						{
							hout(DETAIL) << "M" << MacroID << "_L" << LaneID << ":" << "\t" << "tx_rxdet_ready check failed for 20 times" << endl;
						}
					}
				}
			}
		FOREACH_ACTIVESITE_END

		if (iDet_Flag_All == 1) {
			break;
		}
	}
}


void ReadAndCalcVCOFreqcalCurveLength(const MACRO_LANE_SEL& MacroLane_Sel, const INT& iCSSlice, MACRO_DOUBLE& CurveLength)
{
	INT					LLD_DIFF_UP = 0;
	INT					LLD_DIFF_DOWN = 0;
	d2s_JTAG& jtag = d2s_JTAG::Instance();
	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_VCOFreqcalCurve_Force_UP_DOWN_READ",Global_D2S_Mode);

		CS.clkRegs.skip_CSR_Check();

		/******************ForceUp and read CS_LLD_DIFF_FREQ********************/
		selectMacro_MB(MacroLane_Sel);
		CS.clkRegs.SliceID(iCSSlice).Broadcast(0);

		CS.clkRegs.setpfdforceup(0x1)
				  .setpfdforcedn(0x0)
				  .Write2DUT(3);

		jtag.wait(0.000001*500);

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			selectMacro(MacroID);
			CS.clkRegs.SliceID(iCSSlice).Broadcast(0);

			ostringstream id51_ForceUp;
			id51_ForceUp << "ForceUP_" << "M" << MacroID << "_CS" << iCSSlice << "_CSR51_" << jtag.Context;
			CS.clkRegs.Read2IDString(51, id51_ForceUp.str());
		}

		/******************ForceDown and read CS_LLD_DIFF_FREQ********************/
		selectMacro_MB(MacroLane_Sel);
		CS.clkRegs.SliceID(iCSSlice).Broadcast(0);

		CS.clkRegs.setpfdforceup(0x0)
				  .setpfdforcedn(0x1)
				  .Write2DUT(3);

		jtag.wait(0.000001*500);

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			selectMacro(MacroID);
			CS.clkRegs.SliceID(iCSSlice).Broadcast(0);

			ostringstream id51_ForceDown;
			id51_ForceDown << "ForceDOWN_" << "M" << MacroID << "_CS" << iCSSlice << "_CSR51_" << jtag.Context;
			CS.clkRegs.Read2IDString(51, id51_ForceDown.str());
		}

	d2s::d2s_LABEL_END;

	INT csrindex = 51;
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

			LLD_DIFF_UP = 0;
			LLD_DIFF_DOWN = 0;

			ostringstream id51_ForceUp;
			id51_ForceUp << "ForceUP_" << "M" << MacroID << "_CS" << iCSSlice << "_CSR51_" << jtag.Context;
			INT result = jtag.getReadValue(id51_ForceUp.str())[SiteID];

			CS.clkRegs.csr[csrindex] = (uint)(result);

			if (hout.IsRegAccessEn()) {
				hout(REG_ACCESS) << "================ Macro[" << dec << MacroID << "]"<< "  CS[" << iCSSlice << "]" << "\tRead ================" << endl;
				CS.clkRegs.DisplayAllSegmentOfCSR(csrindex);
			}
			LLD_DIFF_UP = CS.clkRegs.getcs_lld_diff_freq();

			ostringstream id51_ForceDown;
			id51_ForceDown << "ForceDOWN_" << "M" << MacroID << "_CS" << iCSSlice << "_CSR51_" << jtag.Context;
			result = jtag.getReadValue(id51_ForceDown.str())[SiteID];

			CS.clkRegs.csr[csrindex] = (uint)(result);

			if (hout.IsRegAccessEn()) {
				hout(REG_ACCESS) << "================ Macro[" << dec << MacroID << "]"<< "  CS[" << iCSSlice << "]" << "\tRead ================" << endl;
				CS.clkRegs.DisplayAllSegmentOfCSR(csrindex);
			}

			LLD_DIFF_DOWN = CS.clkRegs.getcs_lld_diff_freq();

			if ((LLD_DIFF_UP>>12) == (LLD_DIFF_DOWN>>12))
				CurveLength[SiteID][MacroID] = abs((LLD_DIFF_UP&0x0fff) - (LLD_DIFF_DOWN&0x0fff));
			else
				CurveLength[SiteID][MacroID] = abs((LLD_DIFF_UP&0x0fff) + (LLD_DIFF_DOWN&0x0fff));

			hout(DETAIL) << "MacroID = " << MacroID << "\tForce Up LLD DIFF = " << (dec) << LLD_DIFF_UP
						 << "\tForce Down LLD DIFF = " << (dec) << LLD_DIFF_DOWN
						 << "\tCurve Length = " << (dec) << CurveLength[SiteID][MacroID] << endl;
		}
	FOREACH_ACTIVESITE_END
}

void LogDiffFreqOpenLoop(const MACRO_LANE_SEL& MacroLane_Sel, const INT& iCSSlice, MACRO_DOUBLE& OpenLoopLLDDIFF)
{
	d2s_JTAG& jtag = d2s_JTAG::Instance();

	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_VCOFreqcalCurve_OpenLoop",Global_D2S_Mode);

		CS.clkRegs.skip_CSR_Check();

		selectMacro_MB(MacroLane_Sel);
		CS.clkRegs.SliceID(iCSSlice).Broadcast(0);
		CS.clkRegs.setcalrstb(0x0).Write2DUT(12);

		jtag.wait(0.000001*500);

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			selectMacro(MacroID);
			CS.clkRegs.SliceID(iCSSlice).Broadcast(0);

			ostringstream id51;
			id51 << "OpenLoop_" << "M" << MacroID << "_CS" << iCSSlice << "_CSR51_" << jtag.Context;
			CS.clkRegs.Read2IDString(51, id51.str());
		}

		/*************restore to close loop mode*****************/
		selectMacro_MB(MacroLane_Sel);
		CS.clkRegs.SliceID(iCSSlice).Broadcast(0);
		CS.clkRegs.setcalrstb(0x1).Write2DUT(12);

	d2s::d2s_LABEL_END;

	INT csrindex = 51;
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

			ostringstream id51;
			id51 << "OpenLoop_" << "M" << MacroID << "_CS" << iCSSlice << "_CSR51_" << jtag.Context;
			INT result = jtag.getReadValue(id51.str())[SiteID];

			CS.clkRegs.csr[csrindex] = (uint)(result);

			if (hout.IsRegAccessEn()) {
				hout(REG_ACCESS) << "================ Macro[" << dec << MacroID << "]"<< "  CS[" << iCSSlice << "]" << "\tRead ================" << endl;
				CS.clkRegs.DisplayAllSegmentOfCSR(csrindex);
			}

			OpenLoopLLDDIFF[SiteID][MacroID] = CS.clkRegs.getcs_lld_diff_freq();
			hout(DETAIL) << "MacroID = " << MacroID << "\t OpenLoop LLD DIFF = " << (dec) << OpenLoopLLDDIFF[SiteID][MacroID] << endl;
		}
	FOREACH_ACTIVESITE_END
}

void GetTxFIR(TxFIR_SETTING& FIR_ORI)
{
	FIR_ORI.iTxMain = DS.txRegs.gettxfirmain();
	FIR_ORI.iTxPre1st = DS.txRegs.gettxfirpre1();
	FIR_ORI.iTxPre2nd = DS.txRegs.gettxfirpre2();
	FIR_ORI.iTxPost1st = DS.txRegs.gettxfirpost1();
	FIR_ORI.iTxPost2nd = DS.txRegs.gettxfirpost2();

	FIR_ORI.iTxPre1st = (FIR_ORI.iTxPre1st > 0x10) ? -(FIR_ORI.iTxPre1st - 0x10) : FIR_ORI.iTxPre1st;
	FIR_ORI.iTxPre2nd = (FIR_ORI.iTxPre2nd > 0x10) ? -(FIR_ORI.iTxPre2nd - 0x10) : FIR_ORI.iTxPre2nd;
	FIR_ORI.iTxPost1st = (FIR_ORI.iTxPost1st > 0x10) ? -(FIR_ORI.iTxPost1st - 0x10) : FIR_ORI.iTxPost1st;
	FIR_ORI.iTxPost2nd = (FIR_ORI.iTxPost2nd > 0x10) ? -(FIR_ORI.iTxPost2nd - 0x10) : FIR_ORI.iTxPost2nd;
}

double get_spec_val (const string& sType, const string& sSpecName){

    double dVal;
//
//    if(sType == "TIM") fwout << "SVLR? TIM,PRM,,\"" << sSpecName << "\"" << endl;
//    else               fwout << "SVLR? LEV,PRM,,\"" << sSpecName << "\"" << endl;
//
//    dVal = atof(fwresult[0][4].c_str());

    return dVal;
}

int GET_DigitalCapture_XMode(string& PinName)			//Get X-mode of C in wavetable for Digital Capture
{
//	int WFDS_INDEX=0;
//	if(Primary.isTimingPortBased() == true)
//	{
//		WFDS_INDEX = 4;
//	}
//	else
//	{
//		WFDS_INDEX = 2;
//	}
//	int XmodeDigitalCapture=0;
//	string str_FW_commmand="";
//	string str_FW_Answer = "";
//	STRING_VECTOR STV_FW_Answer;
//	STRING_VECTOR STV_STV_FW_Answer;
//
//	str_FW_commmand = " WFDS? PRM,ALL,,(" +PinName+ ")\n";
//	FW_TASK(str_FW_commmand,str_FW_Answer);
//	parseListOfString(str_FW_Answer,STV_FW_Answer,'\n');
//
//
//	for(unsigned int index=0; index < STV_FW_Answer.size() ;index++)
//	{
//		STV_STV_FW_Answer.clear();
//		parseListOfString(STV_FW_Answer[index],STV_STV_FW_Answer,'"');
//		int pos =0;
//		int xmode = 0;
//		while(STV_STV_FW_Answer[WFDS_INDEX].find(":C",pos) !=string::npos)
//		{
//			xmode++;
//			pos = STV_STV_FW_Answer[WFDS_INDEX].find(":C",pos) +1;
//		}
//
//		if( (XmodeDigitalCapture == 0) && (xmode !=0) )
//		{
//			XmodeDigitalCapture = xmode;
//		}
//		else if( (XmodeDigitalCapture != 0) && (xmode !=0))
//		{
//			if(XmodeDigitalCapture != xmode)
//			{
//				cout << "**** __FILE__:" << __FILE__ << endl;
//				cout << "**** __LINE__:" << __LINE__ << endl;
//				throw Error("ERROR","The C and D in Wavetable definde error");
//			}
//		}
//
//	}
//
//	if(XmodeDigitalCapture == 0)
//	{
////		throw Error("ERROR","No C Find in pin("+PinName+")");
//	}
//
//	return XmodeDigitalCapture;
}

void replace_str(string& str, const string sb, const string sa){
    string::size_type n, nb = 0;

    while((n = str.find(sb,nb)) != string::npos){
        str.replace(n,sb.size(),sa);
        nb = n + sa.size();
    }
}

string int2String(int input)
{
  string out_string;
  stringstream stream;
  stream.str("");
  stream << input;
  out_string = stream.str();

  return out_string;
}

void DSP_MINMAX(ARRAY_D& src,DOUBLE *min,DOUBLE *max,INT *min_index,INT *max_index)
{
	int size = sizeof(src);
	*max = src[0];
	*min = src[0];

	for (INT i = 1;i <= size; i++){
		if (*max < src[i]){
			*max = src[i];
			*max_index = i ;
		}
		if (*min < src[i]){
			*min = src[i];
			*min_index = i ;
		}
	}

}

