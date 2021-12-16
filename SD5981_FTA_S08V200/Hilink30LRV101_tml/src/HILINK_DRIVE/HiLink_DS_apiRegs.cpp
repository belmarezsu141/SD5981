#include <HILINK_DRIVE/HiLink_DS_apiRegs.h>

#include <iostream>
using namespace std;
DS_apiRegs::DS_apiRegs() {
	// TODO Auto-generated constructor stub
	for(int i=0;i<DS_API_CSR_NUM;i++){
		csr[i]=0;
	}
	sliceID=0;
	macroID=0;
	broadcast=false;
	reset_csr_verify();
}

DS_apiRegs::~DS_apiRegs() {}

bool
DS_apiRegs::get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos){
	if(csrIndex>=DS_API_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	return REG_INFO.get_reg_infos(csrIndex,reg_infos);
}

DS_apiRegs&
DS_apiRegs::getInstance(){
	static DS_apiRegs theInstance;
	return theInstance;
}

uint
DS_apiRegs::get_HILINK_MAX_LANE_NUM(){
	//TODO: add your code for CSR Address mapping
	return HILINK_LANE_NUM;
}

uint
DS_apiRegs::getAddressMapToHiLink(int csrIndex){
	if(csrIndex>=DS_API_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	//TODO: add your code for CSR Address mapping
	uint retAddress = 0;
	retAddress = 0x1FFC2 - (sliceID * 0x12 * 2) + (csrIndex*2);
	return retAddress;
}


uint&
DS_apiRegs::get_csr(uint csrIndex){
	if(csrIndex>=DS_API_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	return csr[csrIndex];
}

void
DS_apiRegs::get_default_MacroLaneID(T_MacroLaneID& id){
	//TODO: add your code for CSR Address mapping
	id.MacroID=macroID;
	id.LaneID=sliceID;
}

uint
DS_apiRegs::getCSRCount(){
	return DS_API_CSR_NUM;
}

string
DS_apiRegs::getName(){
	return "DS_API";
}

///////////////////////////////////////////////////////////////////////////


	/// Ds handling reset 
	/// 0: release ds handling
	/// 1: reset ds handling
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_soft_reset_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{0,"ds_soft_reset_api",15,15}
	};
	return reg;
}

	/// DEBUG - Halt after single step 
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_haltsinglestep_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{0,"ds_haltsinglestep_api",14,14}
	};
	return reg;
}

	/// DEBUG - Halt after state change 
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_haltstatechange_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{0,"ds_haltstatechange_api",13,13}
	};
	return reg;
}

	/// DEBUG - Halt all DS execution
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_haltimmediately_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{0,"ds_haltimmediately_api",12,12}
	};
	return reg;
}

	/// Spare for DS control
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_ctrl0_spare11to8_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{0,"ds_ctrl0_spare11to8_api",11,8}
	};
	return reg;
}

	/// DS Calibration enable, used with ds calibration bypass control
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_calib_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{0,"ds_calib_en_api",7,7}
	};
	return reg;
}

	/// fast ctle enable
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_fast_ctle_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{0,"ds_fast_ctle_en_api",6,6}
	};
	return reg;
}

	/// CTLE enable (Default 1)
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_ctle_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{0,"ds_ctle_en_api",5,5}
	};
	return reg;
}

	/// DFE enable (Default 1), used with dfe bypass control
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_dfe_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{0,"ds_dfe_en_api",4,4}
	};
	return reg;
}

	/// Dynamic Process Monitor and dfe summer offset enable (during continuous DFE) (Default 0), used with dpm bypass control
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_dpm_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{0,"ds_dpm_en_api",3,3}
	};
	return reg;
}

	/// CTLE Offset Correction Enable  (Default 0), used with offset bypass control
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_offset_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{0,"ds_offset_en_api",2,2}
	};
	return reg;
}

	/// Dataslice low power mode select.
	/// 0: Performance mode
	/// 1: SR mode
	/// 2: Debug mode
	/// 3: Normal mode
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_power_mode_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{0,"ds_power_mode_api",1,0}
	};
	return reg;
}

	/// the data rate of tx in Gbps, ceil of data rate
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::tx_data_rate_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{1,"tx_data_rate_api",15,11}
	};
	return reg;
}

	/// spare
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_ctrl1_spare10to8(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{1,"ds_ctrl1_spare10to8",10,8}
	};
	return reg;
}

	/// the data rate of rx in Gbps, ceil of data rate
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::rx_data_rate_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{1,"rx_data_rate_api",7,3}
	};
	return reg;
}

	/// spare
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_ctrl1_spare2to0(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{1,"ds_ctrl1_spare2to0",2,0}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dsclkvrefgencalbypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{2,"dsclkvrefgencalbypass_api",15,15}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dsclkvregcalbypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{2,"dsclkvregcalbypass_api",14,14}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::rxctlevregcalbypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{2,"rxctlevregcalbypass_api",13,13}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::rxopampofstcalbypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{2,"rxopampofstcalbypass_api",12,12}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::rxsumloadrescalbypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{2,"rxsumloadrescalbypass_api",11,11}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::rxclkvregcalbypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{2,"rxclkvregcalbypass_api",10,10}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::rxdatavregcalbypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{2,"rxdatavregcalbypass_api",9,9}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::rxsigdetofstcalbypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{2,"rxsigdetofstcalbypass_api",8,8}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::rxctleofstcalbypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{2,"rxctleofstcalbypass_api",7,7}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::rxsumofstcalbypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{2,"rxsumofstcalbypass_api",6,6}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::rxlatchofstcalbypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{2,"rxlatchofstcalbypass_api",5,5}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::rxalfgenofstcalbypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{2,"rxalfgenofstcalbypass_api",4,4}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::txdrvregcalbypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{2,"txdrvregcalbypass_api",3,3}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::txpredrvregcalbypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{2,"txpredrvregcalbypass_api",2,2}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::txcenterpabypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{2,"txcenterpabypass_api",1,1}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::txrxserlpbkofstcalbypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{2,"txrxserlpbkofstcalbypass_api",0,0}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::txdcdcalibbypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{3,"txdcdcalibbypass_api",15,15}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::rxctlerefcalibbypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{3,"rxctlerefcalibbypass_api",14,14}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::rxctlecurrentcalibbypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{3,"rxctlecurrentcalibbypass_api",13,13}
	};
	return reg;
}

	/// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::lpbkdcdcalibbypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{3,"lpbkdcdcalibbypass_api",12,12}
	};
	return reg;
}

//	/// spare
//const T_REG_INFO_EX&
//DS_apiRegs::_REG_INFO::ds_ctrl3_spare12to1(){
//	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
//		{3,"ds_ctrl3_spare12to1",11,1}
//	};
//	return reg;
//}
//add by shaoxue for sd5806 a30 ->b20
// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::rxalfgenstepsizecalibbypass_api(){
const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
	{3,"rxalfgenstepsizecalibbypass_api",11,11}
};
return reg;
}
// calibration bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::rxctlerefminthbypass_api(){
const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
	{3,"rxctlerefminthbypass_api",10,10}
};
return reg;
}
/// spare
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_ctrl3_spare9to1(){
const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
	{3,"ds_ctrl3_spare9to1",9,1}
};
return reg;
}
	/// simple calibration for re-doing calibration to save time.
	/// 1: Wirte previous calibration or ate adaptation results back to chip
	/// 0: disable
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_write_back_ctrl_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{3,"ds_write_back_ctrl_api",0,0}
	};
	return reg;
}

	/// REFSEL enable (Default 0)
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctle_refsel_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{4,"ctle_refsel_en_api",15,15}
	};
	return reg;
}

	/// Zero Adjust enable (Default 0)
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctle_zero_adj_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{4,"ctle_zero_adj_en_api",14,14}
	};
	return reg;
}

	/// Squelch enable (Default 0)
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctle_squelch_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{4,"ctle_squelch_en_api",13,13}
	};
	return reg;
}

	/// Mid-Band enable (Default 0)
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctle_mid_band_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{4,"ctle_mid_band_en_api",12,12}
	};
	return reg;
}

	/// Support eee mode enable(Default 0) 
	/// 0: disable 
	/// 1: enable, check rxquietstatus and disable all register operation and pause dfe when rxquietstatus==0
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::support_eee_mode_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{4,"support_eee_mode_en_api",11,11}
	};
	return reg;
}

	/// CTLE Metric. 
	/// 0 = WIDTH
	/// 1 = HEIGHT
	/// 2 = 4PT_AREA
	/// 3 = 8PT_AREA
	/// Others are reserved.
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctle_eye_metric_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{4,"ctle_eye_metric_api",10,8}
	};
	return reg;
}

	/// DFE Enabled in ctle
	/// 2b'00: Disable DFE in CTLE
	/// 2b'01: Tap0-Tap1
	/// 2b'10: Tap0-Tap6
	/// 2b'11: Tap0-Tap13
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctle_tap_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{4,"ctle_tap_en_api",7,6}
	};
	return reg;
}

	/// 000:I Channel
	/// 001:Q Channel
	/// 010:2in1 Eye, I eye and Q eye
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctle_eye_type_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{4,"ctle_eye_type_api",5,3}
	};
	return reg;
}

	/// TBD
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctle_eye_avg_count_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{4,"ctle_eye_avg_count_api",2,0}
	};
	return reg;
}

	/// Eye scan BER for CTLE adaptation
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctle_eye_contour_index_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{5,"ctle_eye_contour_index_api",15,12}
	};
	return reg;
}

	/// D-Level Target cursor
	/// 0 = 160 mV
	/// 1 = 180 mV
	/// 2 = 200 mV
	/// 3 = 220 mV
	/// 4 = 240 mV
	/// 5 = 260 mV
	/// 6 = 280 mV
	/// 7 = 300 mV
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dlev_target_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{5,"dlev_target_api",11,9}
	};
	return reg;
}

	/// Gain Attn enable (Default 1)
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::gain_attn_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{5,"gain_attn_en_api",8,8}
	};
	return reg;
}

	/// offset bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfesumofst_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{5,"dfesumofst_bypass_api",7,7}
	};
	return reg;
}

	/// offset bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctleofst6_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{5,"ctleofst6_bypass_api",6,6}
	};
	return reg;
}

	/// offset bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctleofst5_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{5,"ctleofst5_bypass_api",5,5}
	};
	return reg;
}

	/// offset bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctleofst4_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{5,"ctleofst4_bypass_api",4,4}
	};
	return reg;
}

	/// offset bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctleofst3_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{5,"ctleofst3_bypass_api",3,3}
	};
	return reg;
}

	/// offset bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctleofst2_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{5,"ctleofst2_bypass_api",2,2}
	};
	return reg;
}

	/// offset bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctleofst1_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{5,"ctleofst1_bypass_api",1,1}
	};
	return reg;
}

	/// whether to use the table combining boost and squelch during ctle or dfe.
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_boost_squelch_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{5,"ds_boost_squelch_en_api",0,0}
	};
	return reg;
}

	/// dfe bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_tap13_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{6,"dfe_tap13_bypass_api",15,15}
	};
	return reg;
}

	/// dfe bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_tap12_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{6,"dfe_tap12_bypass_api",14,14}
	};
	return reg;
}

	/// dfe bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_tap11_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{6,"dfe_tap11_bypass_api",13,13}
	};
	return reg;
}

	/// dfe bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_tap10_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{6,"dfe_tap10_bypass_api",12,12}
	};
	return reg;
}

	/// dfe bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_tap9_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{6,"dfe_tap9_bypass_api",11,11}
	};
	return reg;
}

	/// dfe bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_tap8_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{6,"dfe_tap8_bypass_api",10,10}
	};
	return reg;
}

	/// dfe bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_tap7_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{6,"dfe_tap7_bypass_api",9,9}
	};
	return reg;
}

	/// dfe bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_tap6_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{6,"dfe_tap6_bypass_api",8,8}
	};
	return reg;
}

	/// dfe bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_tap5_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{6,"dfe_tap5_bypass_api",7,7}
	};
	return reg;
}

	/// dfe bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_tap4_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{6,"dfe_tap4_bypass_api",6,6}
	};
	return reg;
}

	/// dfe bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_tap3_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{6,"dfe_tap3_bypass_api",5,5}
	};
	return reg;
}

	/// dfe bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_tap2_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{6,"dfe_tap2_bypass_api",4,4}
	};
	return reg;
}

	/// dfe bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_tap1_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{6,"dfe_tap1_bypass_api",3,3}
	};
	return reg;
}

	/// dfe bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_tap0_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{6,"dfe_tap0_bypass_api",2,2}
	};
	return reg;
}

	/// boost enable during dfe adaptation
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_boost_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{6,"dfe_boost_en_api",1,1}
	};
	return reg;
}

	/// squelch enable during dfe adaptation
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_squelch_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{6,"dfe_squelch_en_api",0,0}
	};
	return reg;
}

	/// zero enable during dfe adaptation.
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_zero_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{7,"dfe_zero_en_api",15,15}
	};
	return reg;
}

	/// biastune enable during dfe adaptation
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_biastune_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{7,"dfe_biastune_en_api",14,14}
	};
	return reg;
}

	/// DFE EYE Metric. 
	/// 0: WIDTH
	/// 1: HEIGHT
	/// 2: 4PT_AREA
	/// 3: 8PT_AREA
	/// Others are reserved.
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_eye_metric_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{7,"dfe_eye_metric_api",13,11}
	};
	return reg;
}

	/// 000: I Channel
	/// 001: Q Channel
	/// 010: Ib
	/// 011: Qb
	/// Others are reserved.
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_eye_type_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{7,"dfe_eye_type_api",10,8}
	};
	return reg;
}

	/// TBD
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctle_dfe_with_same_priority_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{7,"ctle_dfe_with_same_priority_api",7,7}
	};
	return reg;
}

	/// TBD
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_eye_avg_count_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{7,"dfe_eye_avg_count_api",6,4}
	};
	return reg;
}

	/// Eye scan BER for DFE adaptation
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_eye_contour_index_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{7,"dfe_eye_contour_index_api",3,0}
	};
	return reg;
}

	/// dpm bypass control. 0:not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_clkreg_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{8,"ds_clkreg_bypass_api",15,15}
	};
	return reg;
}

	/// dpm bypass control. 0:not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_txdrvreg_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{8,"ds_txdrvreg_bypass_api",14,14}
	};
	return reg;
}

	/// dpm bypass control. 0:not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_txpredrvreg_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{8,"ds_txpredrvreg_bypass_api",13,13}
	};
	return reg;
}

	/// dpm bypass control. 0:not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_rxclkreg_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{8,"ds_rxclkreg_bypass_api",12,12}
	};
	return reg;
}

	/// dpm bypass control. 0:not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_rxdatareg_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{8,"ds_rxdatareg_bypass_api",11,11}
	};
	return reg;
}

	/// Data Centering enable (during continuous DFE)
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::centering_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{8,"centering_en_api",10,10}
	};
	return reg;
}

	/// En alos protection
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctle_alos_protect_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{8,"ctle_alos_protect_en_api",9,9}
	};
	return reg;
}

	/// En eye los protection
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctle_eyelos_protect_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{8,"ctle_eyelos_protect_en_api",8,8}
	};
	return reg;
}

	/// En bypass dfe tap1 in CTLE
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctle_dfetap1_bypass_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{8,"ctle_dfetap1_bypass_en_api",7,7}
	};
	return reg;
}

	/// En alos protection
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_alos_protect_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{8,"dfe_alos_protect_en_api",6,6}
	};
	return reg;
}

	/// En eye los protection
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_eyelos_protect_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{8,"dfe_eyelos_protect_en_api",5,5}
	};
	return reg;
}

	/// En non-random data protection
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_non_random_protect_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{8,"dfe_non_random_protect_en_api",4,4}
	};
	return reg;
}

	/// Fast ctle for short and good channel. Just for outer loop back of ATE.
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ate_ctle_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{8,"ate_ctle_en_api",3,3}
	};
	return reg;
}

	/// alphagen offset enable
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::alphagen_ofst_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{8,"alphagen_ofst_en_api",2,2}
	};
	return reg;
}

	/// Temperature Trigger boost enable api
	/// 0:disable 1:enable
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_temp_trig_boost_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{8,"ds_temp_trig_boost_en_api",1,1}
	};
	return reg;
}

	/// spare
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_latch_offset_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{8,"ds_latch_offset_en_api",0,0}
	};
	return reg;
}

	/// Write from 0 to 1, wait until it changes to 0. 4-points eye diagram infor will be obtained. Only support full/half/Quarter rate mode.
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::fw_eye_start_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{9,"fw_eye_start_api",15,15}
	};
	return reg;
}

	/// 000: I Channel
	/// 001: Q Channel
	/// 010: Ib
	/// 011: Qb
	/// Others are reserved.
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::fw_eye_type_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{9,"fw_eye_type_api",14,12}
	};
	return reg;
}

	/// Data Centering aux enable (during continuous DFE)
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_cenetring_aux_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{9,"ds_cenetring_aux_en_api",11,10}
	};
	return reg;
}

	/// The times of eye width scanning for ATE
	/// 00: Disable
	/// 01: 8 times avg
	/// 10: 16 times avg
	/// 11: 24 times avg
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::fw_ate_eye_width_times_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{9,"fw_ate_eye_width_times_api",9,8}
	};
	return reg;
}

	/// dfe bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_tap15_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{9,"dfe_tap15_bypass_api",7,7}
	};
	return reg;
}

	/// dfe bypass control. 0: not bypass, 1:bypass
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_tap14_bypass_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{9,"dfe_tap14_bypass_api",6,6}
	};
	return reg;
}

	/// 
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_abnormal_restart_adapt_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{9,"ds_abnormal_restart_adapt_api",5,5}
	};
	return reg;
}

	/// rx training support enable  0:disable, 1: enable
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_rx_train_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{9,"ds_rx_train_en_api",4,4}
	};
	return reg;
}

	/// dfe run interval 
	/// 0: no interval
	/// 1:dfe run and pause time is 1:1
	/// 2:dfe run and pause time is 1:2
	/// 3:dfe run and pause time is 1:4
	/// 4:dfe run and pause time is 1:8
	/// 5:dfe run and pause time is 1:16
	/// 6:dfe run and pause time is 1:32
	/// 7:dfe run and pause time is 1:64
	/// 8:dfe run and pause time is 1:128
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_run_interval_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{9,"dfe_run_interval_api",3,0}
	};
	return reg;
}

	/// DFE trigger boost mode
	/// 0: normal mode
	/// 1: fast mode
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dfe_trig_boost_mode_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{10,"dfe_trig_boost_mode_api",15,15}
	};
	return reg;
}

	/// Ctle latch offset enable (Default 0)
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctle_latchofst_en_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{10,"ctle_latchofst_en_api",14,14}
	};
	return reg;
}

	/// H30 TestChip (Default 0)
	/// 0:  ASIC
	/// 1: H30 Testchip
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::h30_testchip_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{10,"h30_testchip_api",13,13}
	};
	return reg;
}

	/// spare
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_ctrl10_spare13to0(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{10,"ds_ctrl10_spare13to0",12,0}
	};
	return reg;
}

	/// spare
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_ctrl11_spare15to0(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{11,"ds_ctrl11_spare15to0",15,0}
	};
	return reg;
}

	/// DS Top FSM state
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_top_fsm_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{12,"ds_top_fsm_api",15,8}
	};
	return reg;
}

	/// DS Sub0 FSM state
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_sub0_fsm_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{12,"ds_sub0_fsm_api",7,0}
	};
	return reg;
}

	/// DS Sub1 FSM state
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_sub1_fsm_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{13,"ds_sub1_fsm_api",15,8}
	};
	return reg;
}

	/// DS Sub2 FSM state
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_sub2_fsm_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{13,"ds_sub2_fsm_api",7,0}
	};
	return reg;
}

	/// DS Sub3 FSM state
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_sub3_fsm_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{14,"ds_sub3_fsm_api",15,12}
	};
	return reg;
}

	/// DS D-Level achieved
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::dlvl_achieved_status_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{14,"dlvl_achieved_status_api",11,11}
	};
	return reg;
}

	/// DS Loss of D-Level detected
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::los_det_status_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{14,"los_det_status_api",10,10}
	};
	return reg;
}

	/// DS Data Centering achieved
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::data_center_status_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{14,"data_center_status_api",9,9}
	};
	return reg;
}

	/// DS CTLE done
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ctle_done_status_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{14,"ctle_done_status_api",8,8}
	};
	return reg;
}

	/// DS Adaptation Reset Done
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_soft_reset_status_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{14,"ds_soft_reset_status_api",7,7}
	};
	return reg;
}

	/// DS Adaptation Reset Done
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_calib_done_status_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{14,"ds_calib_done_status_api",6,6}
	};
	return reg;
}

	/// DS Adaptation Done
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_adapt_done_status_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{14,"ds_adapt_done_status_api",5,5}
	};
	return reg;
}

	/// Spare
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_stat14_spare6to0(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{14,"ds_stat14_spare6to0",4,0}
	};
	return reg;
}

	/// eye height of 4-point eye diagram
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::fw_eye_height_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{15,"fw_eye_height_api",15,8}
	};
	return reg;
}

	/// eye width of 4-point eye diagram
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::fw_eye_width_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{15,"fw_eye_width_api",7,0}
	};
	return reg;
}

	/// the max eye width during ate eye width sanning
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::fw_ate_max_eye_width_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{16,"fw_ate_max_eye_width_api",15,8}
	};
	return reg;
}

	/// the min eye width during ate eye width sanning
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::fw_ate_min_eye_width_api(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{16,"fw_ate_min_eye_width_api",7,0}
	};
	return reg;
}

	/// spare
const T_REG_INFO_EX&
DS_apiRegs::_REG_INFO::ds_stat17_spare15to0(){
	const static T_REG_INFO_EX reg={DS_apiRegs::getInstance(),
		{17,"ds_stat17_spare15to0",15,0}
	};
	return reg;
}
bool
DS_apiRegs::_REG_INFO::get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos){
	reg_infos.clear();
	switch(csr){
		case 0:
			reg_infos.push_back(ds_soft_reset_api().reg_info);
			reg_infos.push_back(ds_haltsinglestep_api().reg_info);
			reg_infos.push_back(ds_haltstatechange_api().reg_info);
			reg_infos.push_back(ds_haltimmediately_api().reg_info);
			reg_infos.push_back(ds_ctrl0_spare11to8_api().reg_info);
			reg_infos.push_back(ds_calib_en_api().reg_info);
			reg_infos.push_back(ds_fast_ctle_en_api().reg_info);
			reg_infos.push_back(ds_ctle_en_api().reg_info);
			reg_infos.push_back(ds_dfe_en_api().reg_info);
			reg_infos.push_back(ds_dpm_en_api().reg_info);
			reg_infos.push_back(ds_offset_en_api().reg_info);
			reg_infos.push_back(ds_power_mode_api().reg_info);
			break;
		case 1:
			reg_infos.push_back(tx_data_rate_api().reg_info);
			reg_infos.push_back(ds_ctrl1_spare10to8().reg_info);
			reg_infos.push_back(rx_data_rate_api().reg_info);
			reg_infos.push_back(ds_ctrl1_spare2to0().reg_info);
			break;
		case 2:
			reg_infos.push_back(dsclkvrefgencalbypass_api().reg_info);
			reg_infos.push_back(dsclkvregcalbypass_api().reg_info);
			reg_infos.push_back(rxctlevregcalbypass_api().reg_info);
			reg_infos.push_back(rxopampofstcalbypass_api().reg_info);
			reg_infos.push_back(rxsumloadrescalbypass_api().reg_info);
			reg_infos.push_back(rxclkvregcalbypass_api().reg_info);
			reg_infos.push_back(rxdatavregcalbypass_api().reg_info);
			reg_infos.push_back(rxsigdetofstcalbypass_api().reg_info);
			reg_infos.push_back(rxctleofstcalbypass_api().reg_info);
			reg_infos.push_back(rxsumofstcalbypass_api().reg_info);
			reg_infos.push_back(rxlatchofstcalbypass_api().reg_info);
			reg_infos.push_back(rxalfgenofstcalbypass_api().reg_info);
			reg_infos.push_back(txdrvregcalbypass_api().reg_info);
			reg_infos.push_back(txpredrvregcalbypass_api().reg_info);
			reg_infos.push_back(txcenterpabypass_api().reg_info);
			reg_infos.push_back(txrxserlpbkofstcalbypass_api().reg_info);
			break;
		case 3:
			reg_infos.push_back(txdcdcalibbypass_api().reg_info);
			reg_infos.push_back(rxctlerefcalibbypass_api().reg_info);
			reg_infos.push_back(rxctlecurrentcalibbypass_api().reg_info);
			reg_infos.push_back(lpbkdcdcalibbypass_api().reg_info);
			reg_infos.push_back(rxalfgenstepsizecalibbypass_api().reg_info);			//rxalfgenstepsizecalibbypass_api add by shaoxue
			reg_infos.push_back(rxctlerefminthbypass_api().reg_info);//rxctlerefminthbypass_api
			reg_infos.push_back(ds_ctrl3_spare9to1().reg_info);
			reg_infos.push_back(ds_write_back_ctrl_api().reg_info);
			break;
		case 4:
			reg_infos.push_back(ctle_refsel_en_api().reg_info);
			reg_infos.push_back(ctle_zero_adj_en_api().reg_info);
			reg_infos.push_back(ctle_squelch_en_api().reg_info);
			reg_infos.push_back(ctle_mid_band_en_api().reg_info);
			reg_infos.push_back(support_eee_mode_en_api().reg_info);
			reg_infos.push_back(ctle_eye_metric_api().reg_info);
			reg_infos.push_back(ctle_tap_en_api().reg_info);
			reg_infos.push_back(ctle_eye_type_api().reg_info);
			reg_infos.push_back(ctle_eye_avg_count_api().reg_info);
			break;
		case 5:
			reg_infos.push_back(ctle_eye_contour_index_api().reg_info);
			reg_infos.push_back(dlev_target_api().reg_info);
			reg_infos.push_back(gain_attn_en_api().reg_info);
			reg_infos.push_back(dfesumofst_bypass_api().reg_info);
			reg_infos.push_back(ctleofst6_bypass_api().reg_info);
			reg_infos.push_back(ctleofst5_bypass_api().reg_info);
			reg_infos.push_back(ctleofst4_bypass_api().reg_info);
			reg_infos.push_back(ctleofst3_bypass_api().reg_info);
			reg_infos.push_back(ctleofst2_bypass_api().reg_info);
			reg_infos.push_back(ctleofst1_bypass_api().reg_info);
			reg_infos.push_back(ds_boost_squelch_en_api().reg_info);
			break;
		case 6:
			reg_infos.push_back(dfe_tap13_bypass_api().reg_info);
			reg_infos.push_back(dfe_tap12_bypass_api().reg_info);
			reg_infos.push_back(dfe_tap11_bypass_api().reg_info);
			reg_infos.push_back(dfe_tap10_bypass_api().reg_info);
			reg_infos.push_back(dfe_tap9_bypass_api().reg_info);
			reg_infos.push_back(dfe_tap8_bypass_api().reg_info);
			reg_infos.push_back(dfe_tap7_bypass_api().reg_info);
			reg_infos.push_back(dfe_tap6_bypass_api().reg_info);
			reg_infos.push_back(dfe_tap5_bypass_api().reg_info);
			reg_infos.push_back(dfe_tap4_bypass_api().reg_info);
			reg_infos.push_back(dfe_tap3_bypass_api().reg_info);
			reg_infos.push_back(dfe_tap2_bypass_api().reg_info);
			reg_infos.push_back(dfe_tap1_bypass_api().reg_info);
			reg_infos.push_back(dfe_tap0_bypass_api().reg_info);
			reg_infos.push_back(dfe_boost_en_api().reg_info);
			reg_infos.push_back(dfe_squelch_en_api().reg_info);
			break;
		case 7:
			reg_infos.push_back(dfe_zero_en_api().reg_info);
			reg_infos.push_back(dfe_biastune_en_api().reg_info);
			reg_infos.push_back(dfe_eye_metric_api().reg_info);
			reg_infos.push_back(dfe_eye_type_api().reg_info);
			reg_infos.push_back(ctle_dfe_with_same_priority_api().reg_info);
			reg_infos.push_back(dfe_eye_avg_count_api().reg_info);
			reg_infos.push_back(dfe_eye_contour_index_api().reg_info);
			break;
		case 8:
			reg_infos.push_back(ds_clkreg_bypass_api().reg_info);
			reg_infos.push_back(ds_txdrvreg_bypass_api().reg_info);
			reg_infos.push_back(ds_txpredrvreg_bypass_api().reg_info);
			reg_infos.push_back(ds_rxclkreg_bypass_api().reg_info);
			reg_infos.push_back(ds_rxdatareg_bypass_api().reg_info);
			reg_infos.push_back(centering_en_api().reg_info);
			reg_infos.push_back(ctle_alos_protect_en_api().reg_info);
			reg_infos.push_back(ctle_eyelos_protect_en_api().reg_info);
			reg_infos.push_back(ctle_dfetap1_bypass_en_api().reg_info);
			reg_infos.push_back(dfe_alos_protect_en_api().reg_info);
			reg_infos.push_back(dfe_eyelos_protect_en_api().reg_info);
			reg_infos.push_back(dfe_non_random_protect_en_api().reg_info);
			reg_infos.push_back(ate_ctle_en_api().reg_info);
			reg_infos.push_back(alphagen_ofst_en_api().reg_info);
			reg_infos.push_back(ds_temp_trig_boost_en_api().reg_info);
			reg_infos.push_back(ds_latch_offset_en_api().reg_info);
			break;
		case 9:
			reg_infos.push_back(fw_eye_start_api().reg_info);
			reg_infos.push_back(fw_eye_type_api().reg_info);
			reg_infos.push_back(ds_cenetring_aux_en_api().reg_info);
			reg_infos.push_back(fw_ate_eye_width_times_api().reg_info);
			reg_infos.push_back(dfe_tap15_bypass_api().reg_info);
			reg_infos.push_back(dfe_tap14_bypass_api().reg_info);
			reg_infos.push_back(ds_abnormal_restart_adapt_api().reg_info);
			reg_infos.push_back(ds_rx_train_en_api().reg_info);
			reg_infos.push_back(dfe_run_interval_api().reg_info);
			break;
		case 10:
			reg_infos.push_back(dfe_trig_boost_mode_api().reg_info);
			reg_infos.push_back(ctle_latchofst_en_api().reg_info);
			reg_infos.push_back(h30_testchip_api().reg_info);
			reg_infos.push_back(ds_ctrl10_spare13to0().reg_info);
			break;
		case 11:
			reg_infos.push_back(ds_ctrl11_spare15to0().reg_info);
			break;
		case 12:
			reg_infos.push_back(ds_top_fsm_api().reg_info);
			reg_infos.push_back(ds_sub0_fsm_api().reg_info);
			break;
		case 13:
			reg_infos.push_back(ds_sub1_fsm_api().reg_info);
			reg_infos.push_back(ds_sub2_fsm_api().reg_info);
			break;
		case 14:
			reg_infos.push_back(ds_sub3_fsm_api().reg_info);
			reg_infos.push_back(dlvl_achieved_status_api().reg_info);
			reg_infos.push_back(los_det_status_api().reg_info);
			reg_infos.push_back(data_center_status_api().reg_info);
			reg_infos.push_back(ctle_done_status_api().reg_info);
			reg_infos.push_back(ds_soft_reset_status_api().reg_info);
			reg_infos.push_back(ds_calib_done_status_api().reg_info);
			reg_infos.push_back(ds_adapt_done_status_api().reg_info);
			reg_infos.push_back(ds_stat14_spare6to0().reg_info);
			break;
		case 15:
			reg_infos.push_back(fw_eye_height_api().reg_info);
			reg_infos.push_back(fw_eye_width_api().reg_info);
			break;
		case 16:
			reg_infos.push_back(fw_ate_max_eye_width_api().reg_info);
			reg_infos.push_back(fw_ate_min_eye_width_api().reg_info);
			break;
		case 17:
			reg_infos.push_back(ds_stat17_spare15to0().reg_info);
			break;
		default:
			break;
	}
	return (reg_infos.size()>0);
}


DS_apiRegs&
DS_apiRegs::setds_soft_reset_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_soft_reset_api());	//CSR0[15:15]
	return *this;
}
uint
DS_apiRegs::getds_soft_reset_api(){
	return get_csr_bits(REG_INFO.ds_soft_reset_api());	//CSR0[15:15]
}

DS_apiRegs&
DS_apiRegs::setds_haltsinglestep_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_haltsinglestep_api());	//CSR0[14:14]
	return *this;
}
uint
DS_apiRegs::getds_haltsinglestep_api(){
	return get_csr_bits(REG_INFO.ds_haltsinglestep_api());	//CSR0[14:14]
}

DS_apiRegs&
DS_apiRegs::setds_haltstatechange_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_haltstatechange_api());	//CSR0[13:13]
	return *this;
}
uint
DS_apiRegs::getds_haltstatechange_api(){
	return get_csr_bits(REG_INFO.ds_haltstatechange_api());	//CSR0[13:13]
}

DS_apiRegs&
DS_apiRegs::setds_haltimmediately_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_haltimmediately_api());	//CSR0[12:12]
	return *this;
}
uint
DS_apiRegs::getds_haltimmediately_api(){
	return get_csr_bits(REG_INFO.ds_haltimmediately_api());	//CSR0[12:12]
}

DS_apiRegs&
DS_apiRegs::setds_ctrl0_spare11to8_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_ctrl0_spare11to8_api());	//CSR0[11:8]
	return *this;
}
uint
DS_apiRegs::getds_ctrl0_spare11to8_api(){
	return get_csr_bits(REG_INFO.ds_ctrl0_spare11to8_api());	//CSR0[11:8]
}

DS_apiRegs&
DS_apiRegs::setds_calib_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_calib_en_api());	//CSR0[7:7]
	return *this;
}
uint
DS_apiRegs::getds_calib_en_api(){
	return get_csr_bits(REG_INFO.ds_calib_en_api());	//CSR0[7:7]
}

DS_apiRegs&
DS_apiRegs::setds_fast_ctle_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_fast_ctle_en_api());	//CSR0[6:6]
	return *this;
}
uint
DS_apiRegs::getds_fast_ctle_en_api(){
	return get_csr_bits(REG_INFO.ds_fast_ctle_en_api());	//CSR0[6:6]
}

DS_apiRegs&
DS_apiRegs::setds_ctle_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_ctle_en_api());	//CSR0[5:5]
	return *this;
}
uint
DS_apiRegs::getds_ctle_en_api(){
	return get_csr_bits(REG_INFO.ds_ctle_en_api());	//CSR0[5:5]
}

DS_apiRegs&
DS_apiRegs::setds_dfe_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_dfe_en_api());	//CSR0[4:4]
	return *this;
}
uint
DS_apiRegs::getds_dfe_en_api(){
	return get_csr_bits(REG_INFO.ds_dfe_en_api());	//CSR0[4:4]
}

DS_apiRegs&
DS_apiRegs::setds_dpm_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_dpm_en_api());	//CSR0[3:3]
	return *this;
}
uint
DS_apiRegs::getds_dpm_en_api(){
	return get_csr_bits(REG_INFO.ds_dpm_en_api());	//CSR0[3:3]
}

DS_apiRegs&
DS_apiRegs::setds_offset_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_offset_en_api());	//CSR0[2:2]
	return *this;
}
uint
DS_apiRegs::getds_offset_en_api(){
	return get_csr_bits(REG_INFO.ds_offset_en_api());	//CSR0[2:2]
}

DS_apiRegs&
DS_apiRegs::setds_power_mode_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_power_mode_api());	//CSR0[1:0]
	return *this;
}
uint
DS_apiRegs::getds_power_mode_api(){
	return get_csr_bits(REG_INFO.ds_power_mode_api());	//CSR0[1:0]
}

DS_apiRegs&
DS_apiRegs::settx_data_rate_api(uint val){
	fill_csr_bits(val,REG_INFO.tx_data_rate_api());	//CSR1[15:11]
	return *this;
}
uint
DS_apiRegs::gettx_data_rate_api(){
	return get_csr_bits(REG_INFO.tx_data_rate_api());	//CSR1[15:11]
}

DS_apiRegs&
DS_apiRegs::setds_ctrl1_spare10to8(uint val){
	fill_csr_bits(val,REG_INFO.ds_ctrl1_spare10to8());	//CSR1[10:8]
	return *this;
}
uint
DS_apiRegs::getds_ctrl1_spare10to8(){
	return get_csr_bits(REG_INFO.ds_ctrl1_spare10to8());	//CSR1[10:8]
}

DS_apiRegs&
DS_apiRegs::setrx_data_rate_api(uint val){
	fill_csr_bits(val,REG_INFO.rx_data_rate_api());	//CSR1[7:3]
	return *this;
}
uint
DS_apiRegs::getrx_data_rate_api(){
	return get_csr_bits(REG_INFO.rx_data_rate_api());	//CSR1[7:3]
}

DS_apiRegs&
DS_apiRegs::setds_ctrl1_spare2to0(uint val){
	fill_csr_bits(val,REG_INFO.ds_ctrl1_spare2to0());	//CSR1[2:0]
	return *this;
}
uint
DS_apiRegs::getds_ctrl1_spare2to0(){
	return get_csr_bits(REG_INFO.ds_ctrl1_spare2to0());	//CSR1[2:0]
}

DS_apiRegs&
DS_apiRegs::setdsclkvrefgencalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.dsclkvrefgencalbypass_api());	//CSR2[15:15]
	return *this;
}
uint
DS_apiRegs::getdsclkvrefgencalbypass_api(){
	return get_csr_bits(REG_INFO.dsclkvrefgencalbypass_api());	//CSR2[15:15]
}

DS_apiRegs&
DS_apiRegs::setdsclkvregcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.dsclkvregcalbypass_api());	//CSR2[14:14]
	return *this;
}
uint
DS_apiRegs::getdsclkvregcalbypass_api(){
	return get_csr_bits(REG_INFO.dsclkvregcalbypass_api());	//CSR2[14:14]
}

DS_apiRegs&
DS_apiRegs::setrxctlevregcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.rxctlevregcalbypass_api());	//CSR2[13:13]
	return *this;
}
uint
DS_apiRegs::getrxctlevregcalbypass_api(){
	return get_csr_bits(REG_INFO.rxctlevregcalbypass_api());	//CSR2[13:13]
}

DS_apiRegs&
DS_apiRegs::setrxopampofstcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.rxopampofstcalbypass_api());	//CSR2[12:12]
	return *this;
}
uint
DS_apiRegs::getrxopampofstcalbypass_api(){
	return get_csr_bits(REG_INFO.rxopampofstcalbypass_api());	//CSR2[12:12]
}

DS_apiRegs&
DS_apiRegs::setrxsumloadrescalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.rxsumloadrescalbypass_api());	//CSR2[11:11]
	return *this;
}
uint
DS_apiRegs::getrxsumloadrescalbypass_api(){
	return get_csr_bits(REG_INFO.rxsumloadrescalbypass_api());	//CSR2[11:11]
}

DS_apiRegs&
DS_apiRegs::setrxclkvregcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.rxclkvregcalbypass_api());	//CSR2[10:10]
	return *this;
}
uint
DS_apiRegs::getrxclkvregcalbypass_api(){
	return get_csr_bits(REG_INFO.rxclkvregcalbypass_api());	//CSR2[10:10]
}

DS_apiRegs&
DS_apiRegs::setrxdatavregcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.rxdatavregcalbypass_api());	//CSR2[9:9]
	return *this;
}
uint
DS_apiRegs::getrxdatavregcalbypass_api(){
	return get_csr_bits(REG_INFO.rxdatavregcalbypass_api());	//CSR2[9:9]
}

DS_apiRegs&
DS_apiRegs::setrxsigdetofstcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.rxsigdetofstcalbypass_api());	//CSR2[8:8]
	return *this;
}
uint
DS_apiRegs::getrxsigdetofstcalbypass_api(){
	return get_csr_bits(REG_INFO.rxsigdetofstcalbypass_api());	//CSR2[8:8]
}

DS_apiRegs&
DS_apiRegs::setrxctleofstcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.rxctleofstcalbypass_api());	//CSR2[7:7]
	return *this;
}
uint
DS_apiRegs::getrxctleofstcalbypass_api(){
	return get_csr_bits(REG_INFO.rxctleofstcalbypass_api());	//CSR2[7:7]
}

DS_apiRegs&
DS_apiRegs::setrxsumofstcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.rxsumofstcalbypass_api());	//CSR2[6:6]
	return *this;
}
uint
DS_apiRegs::getrxsumofstcalbypass_api(){
	return get_csr_bits(REG_INFO.rxsumofstcalbypass_api());	//CSR2[6:6]
}

DS_apiRegs&
DS_apiRegs::setrxlatchofstcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.rxlatchofstcalbypass_api());	//CSR2[5:5]
	return *this;
}
uint
DS_apiRegs::getrxlatchofstcalbypass_api(){
	return get_csr_bits(REG_INFO.rxlatchofstcalbypass_api());	//CSR2[5:5]
}

DS_apiRegs&
DS_apiRegs::setrxalfgenofstcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.rxalfgenofstcalbypass_api());	//CSR2[4:4]
	return *this;
}
uint
DS_apiRegs::getrxalfgenofstcalbypass_api(){
	return get_csr_bits(REG_INFO.rxalfgenofstcalbypass_api());	//CSR2[4:4]
}

DS_apiRegs&
DS_apiRegs::settxdrvregcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.txdrvregcalbypass_api());	//CSR2[3:3]
	return *this;
}
uint
DS_apiRegs::gettxdrvregcalbypass_api(){
	return get_csr_bits(REG_INFO.txdrvregcalbypass_api());	//CSR2[3:3]
}

DS_apiRegs&
DS_apiRegs::settxpredrvregcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.txpredrvregcalbypass_api());	//CSR2[2:2]
	return *this;
}
uint
DS_apiRegs::gettxpredrvregcalbypass_api(){
	return get_csr_bits(REG_INFO.txpredrvregcalbypass_api());	//CSR2[2:2]
}

DS_apiRegs&
DS_apiRegs::settxcenterpabypass_api(uint val){
	fill_csr_bits(val,REG_INFO.txcenterpabypass_api());	//CSR2[1:1]
	return *this;
}
uint
DS_apiRegs::gettxcenterpabypass_api(){
	return get_csr_bits(REG_INFO.txcenterpabypass_api());	//CSR2[1:1]
}

DS_apiRegs&
DS_apiRegs::settxrxserlpbkofstcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbkofstcalbypass_api());	//CSR2[0:0]
	return *this;
}
uint
DS_apiRegs::gettxrxserlpbkofstcalbypass_api(){
	return get_csr_bits(REG_INFO.txrxserlpbkofstcalbypass_api());	//CSR2[0:0]
}

DS_apiRegs&
DS_apiRegs::settxdcdcalibbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.txdcdcalibbypass_api());	//CSR3[15:15]
	return *this;
}
uint
DS_apiRegs::gettxdcdcalibbypass_api(){
	return get_csr_bits(REG_INFO.txdcdcalibbypass_api());	//CSR3[15:15]
}

DS_apiRegs&
DS_apiRegs::setrxctlerefcalibbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.rxctlerefcalibbypass_api());	//CSR3[14:14]
	return *this;
}
uint
DS_apiRegs::getrxctlerefcalibbypass_api(){
	return get_csr_bits(REG_INFO.rxctlerefcalibbypass_api());	//CSR3[14:14]
}

DS_apiRegs&
DS_apiRegs::setrxctlecurrentcalibbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.rxctlecurrentcalibbypass_api());	//CSR3[13:13]
	return *this;
}
uint
DS_apiRegs::getrxctlecurrentcalibbypass_api(){
	return get_csr_bits(REG_INFO.rxctlecurrentcalibbypass_api());	//CSR3[13:13]
}

DS_apiRegs&
DS_apiRegs::setlpbkdcdcalibbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.lpbkdcdcalibbypass_api());	//CSR3[12:12]
	return *this;
}
uint
DS_apiRegs::getlpbkdcdcalibbypass_api(){
	return get_csr_bits(REG_INFO.lpbkdcdcalibbypass_api());	//CSR3[12:12]
}
//rxalfgenstepsizecalibbypass_api
DS_apiRegs&
DS_apiRegs::setrxalfgenstepsizecalibbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.rxalfgenstepsizecalibbypass_api());	//CSR3[11:11]
	return *this;
}
uint
DS_apiRegs::getrxalfgenstepsizecalibbypass_api(){
	return get_csr_bits(REG_INFO.rxalfgenstepsizecalibbypass_api());	//CSR3[11:11]
}
//rxctlerefminthbypass_api
DS_apiRegs&
DS_apiRegs::setrxctlerefminthbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.rxctlerefminthbypass_api());	//CSR3[10:10]
	return *this;
}
uint
DS_apiRegs::getrxctlerefminthbypass_api(){
	return get_csr_bits(REG_INFO.rxctlerefminthbypass_api());	//CSR3[10:10]
}
DS_apiRegs&
DS_apiRegs::setds_ctrl3_spare9to1(uint val){
	fill_csr_bits(val,REG_INFO.ds_ctrl3_spare9to1());	//CSR3[9:1]
	return *this;
}
uint
DS_apiRegs::getds_ctrl3_spare9to1(){
	return get_csr_bits(REG_INFO.ds_ctrl3_spare9to1());	//CSR3[9:1]
}

DS_apiRegs&
DS_apiRegs::setds_write_back_ctrl_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_write_back_ctrl_api());	//CSR3[0:0]
	return *this;
}
uint
DS_apiRegs::getds_write_back_ctrl_api(){
	return get_csr_bits(REG_INFO.ds_write_back_ctrl_api());	//CSR3[0:0]
}

DS_apiRegs&
DS_apiRegs::setctle_refsel_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ctle_refsel_en_api());	//CSR4[15:15]
	return *this;
}
uint
DS_apiRegs::getctle_refsel_en_api(){
	return get_csr_bits(REG_INFO.ctle_refsel_en_api());	//CSR4[15:15]
}

DS_apiRegs&
DS_apiRegs::setctle_zero_adj_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ctle_zero_adj_en_api());	//CSR4[14:14]
	return *this;
}
uint
DS_apiRegs::getctle_zero_adj_en_api(){
	return get_csr_bits(REG_INFO.ctle_zero_adj_en_api());	//CSR4[14:14]
}

DS_apiRegs&
DS_apiRegs::setctle_squelch_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ctle_squelch_en_api());	//CSR4[13:13]
	return *this;
}
uint
DS_apiRegs::getctle_squelch_en_api(){
	return get_csr_bits(REG_INFO.ctle_squelch_en_api());	//CSR4[13:13]
}

DS_apiRegs&
DS_apiRegs::setctle_mid_band_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ctle_mid_band_en_api());	//CSR4[12:12]
	return *this;
}
uint
DS_apiRegs::getctle_mid_band_en_api(){
	return get_csr_bits(REG_INFO.ctle_mid_band_en_api());	//CSR4[12:12]
}

DS_apiRegs&
DS_apiRegs::setsupport_eee_mode_en_api(uint val){
	fill_csr_bits(val,REG_INFO.support_eee_mode_en_api());	//CSR4[11:11]
	return *this;
}
uint
DS_apiRegs::getsupport_eee_mode_en_api(){
	return get_csr_bits(REG_INFO.support_eee_mode_en_api());	//CSR4[11:11]
}

DS_apiRegs&
DS_apiRegs::setctle_eye_metric_api(uint val){
	fill_csr_bits(val,REG_INFO.ctle_eye_metric_api());	//CSR4[10:8]
	return *this;
}
uint
DS_apiRegs::getctle_eye_metric_api(){
	return get_csr_bits(REG_INFO.ctle_eye_metric_api());	//CSR4[10:8]
}

DS_apiRegs&
DS_apiRegs::setctle_tap_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ctle_tap_en_api());	//CSR4[7:6]
	return *this;
}
uint
DS_apiRegs::getctle_tap_en_api(){
	return get_csr_bits(REG_INFO.ctle_tap_en_api());	//CSR4[7:6]
}

DS_apiRegs&
DS_apiRegs::setctle_eye_type_api(uint val){
	fill_csr_bits(val,REG_INFO.ctle_eye_type_api());	//CSR4[5:3]
	return *this;
}
uint
DS_apiRegs::getctle_eye_type_api(){
	return get_csr_bits(REG_INFO.ctle_eye_type_api());	//CSR4[5:3]
}

DS_apiRegs&
DS_apiRegs::setctle_eye_avg_count_api(uint val){
	fill_csr_bits(val,REG_INFO.ctle_eye_avg_count_api());	//CSR4[2:0]
	return *this;
}
uint
DS_apiRegs::getctle_eye_avg_count_api(){
	return get_csr_bits(REG_INFO.ctle_eye_avg_count_api());	//CSR4[2:0]
}

DS_apiRegs&
DS_apiRegs::setctle_eye_contour_index_api(uint val){
	fill_csr_bits(val,REG_INFO.ctle_eye_contour_index_api());	//CSR5[15:12]
	return *this;
}
uint
DS_apiRegs::getctle_eye_contour_index_api(){
	return get_csr_bits(REG_INFO.ctle_eye_contour_index_api());	//CSR5[15:12]
}

DS_apiRegs&
DS_apiRegs::setdlev_target_api(uint val){
	fill_csr_bits(val,REG_INFO.dlev_target_api());	//CSR5[11:9]
	return *this;
}
uint
DS_apiRegs::getdlev_target_api(){
	return get_csr_bits(REG_INFO.dlev_target_api());	//CSR5[11:9]
}

DS_apiRegs&
DS_apiRegs::setgain_attn_en_api(uint val){
	fill_csr_bits(val,REG_INFO.gain_attn_en_api());	//CSR5[8:8]
	return *this;
}
uint
DS_apiRegs::getgain_attn_en_api(){
	return get_csr_bits(REG_INFO.gain_attn_en_api());	//CSR5[8:8]
}

DS_apiRegs&
DS_apiRegs::setdfesumofst_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.dfesumofst_bypass_api());	//CSR5[7:7]
	return *this;
}
uint
DS_apiRegs::getdfesumofst_bypass_api(){
	return get_csr_bits(REG_INFO.dfesumofst_bypass_api());	//CSR5[7:7]
}

DS_apiRegs&
DS_apiRegs::setctleofst6_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.ctleofst6_bypass_api());	//CSR5[6:6]
	return *this;
}
uint
DS_apiRegs::getctleofst6_bypass_api(){
	return get_csr_bits(REG_INFO.ctleofst6_bypass_api());	//CSR5[6:6]
}

DS_apiRegs&
DS_apiRegs::setctleofst5_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.ctleofst5_bypass_api());	//CSR5[5:5]
	return *this;
}
uint
DS_apiRegs::getctleofst5_bypass_api(){
	return get_csr_bits(REG_INFO.ctleofst5_bypass_api());	//CSR5[5:5]
}

DS_apiRegs&
DS_apiRegs::setctleofst4_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.ctleofst4_bypass_api());	//CSR5[4:4]
	return *this;
}
uint
DS_apiRegs::getctleofst4_bypass_api(){
	return get_csr_bits(REG_INFO.ctleofst4_bypass_api());	//CSR5[4:4]
}

DS_apiRegs&
DS_apiRegs::setctleofst3_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.ctleofst3_bypass_api());	//CSR5[3:3]
	return *this;
}
uint
DS_apiRegs::getctleofst3_bypass_api(){
	return get_csr_bits(REG_INFO.ctleofst3_bypass_api());	//CSR5[3:3]
}

DS_apiRegs&
DS_apiRegs::setctleofst2_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.ctleofst2_bypass_api());	//CSR5[2:2]
	return *this;
}
uint
DS_apiRegs::getctleofst2_bypass_api(){
	return get_csr_bits(REG_INFO.ctleofst2_bypass_api());	//CSR5[2:2]
}

DS_apiRegs&
DS_apiRegs::setctleofst1_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.ctleofst1_bypass_api());	//CSR5[1:1]
	return *this;
}
uint
DS_apiRegs::getctleofst1_bypass_api(){
	return get_csr_bits(REG_INFO.ctleofst1_bypass_api());	//CSR5[1:1]
}

DS_apiRegs&
DS_apiRegs::setds_boost_squelch_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_boost_squelch_en_api());	//CSR5[0:0]
	return *this;
}
uint
DS_apiRegs::getds_boost_squelch_en_api(){
	return get_csr_bits(REG_INFO.ds_boost_squelch_en_api());	//CSR5[0:0]
}

DS_apiRegs&
DS_apiRegs::setdfe_tap13_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_tap13_bypass_api());	//CSR6[15:15]
	return *this;
}
uint
DS_apiRegs::getdfe_tap13_bypass_api(){
	return get_csr_bits(REG_INFO.dfe_tap13_bypass_api());	//CSR6[15:15]
}

DS_apiRegs&
DS_apiRegs::setdfe_tap12_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_tap12_bypass_api());	//CSR6[14:14]
	return *this;
}
uint
DS_apiRegs::getdfe_tap12_bypass_api(){
	return get_csr_bits(REG_INFO.dfe_tap12_bypass_api());	//CSR6[14:14]
}

DS_apiRegs&
DS_apiRegs::setdfe_tap11_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_tap11_bypass_api());	//CSR6[13:13]
	return *this;
}
uint
DS_apiRegs::getdfe_tap11_bypass_api(){
	return get_csr_bits(REG_INFO.dfe_tap11_bypass_api());	//CSR6[13:13]
}

DS_apiRegs&
DS_apiRegs::setdfe_tap10_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_tap10_bypass_api());	//CSR6[12:12]
	return *this;
}
uint
DS_apiRegs::getdfe_tap10_bypass_api(){
	return get_csr_bits(REG_INFO.dfe_tap10_bypass_api());	//CSR6[12:12]
}

DS_apiRegs&
DS_apiRegs::setdfe_tap9_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_tap9_bypass_api());	//CSR6[11:11]
	return *this;
}
uint
DS_apiRegs::getdfe_tap9_bypass_api(){
	return get_csr_bits(REG_INFO.dfe_tap9_bypass_api());	//CSR6[11:11]
}

DS_apiRegs&
DS_apiRegs::setdfe_tap8_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_tap8_bypass_api());	//CSR6[10:10]
	return *this;
}
uint
DS_apiRegs::getdfe_tap8_bypass_api(){
	return get_csr_bits(REG_INFO.dfe_tap8_bypass_api());	//CSR6[10:10]
}

DS_apiRegs&
DS_apiRegs::setdfe_tap7_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_tap7_bypass_api());	//CSR6[9:9]
	return *this;
}
uint
DS_apiRegs::getdfe_tap7_bypass_api(){
	return get_csr_bits(REG_INFO.dfe_tap7_bypass_api());	//CSR6[9:9]
}

DS_apiRegs&
DS_apiRegs::setdfe_tap6_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_tap6_bypass_api());	//CSR6[8:8]
	return *this;
}
uint
DS_apiRegs::getdfe_tap6_bypass_api(){
	return get_csr_bits(REG_INFO.dfe_tap6_bypass_api());	//CSR6[8:8]
}

DS_apiRegs&
DS_apiRegs::setdfe_tap5_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_tap5_bypass_api());	//CSR6[7:7]
	return *this;
}
uint
DS_apiRegs::getdfe_tap5_bypass_api(){
	return get_csr_bits(REG_INFO.dfe_tap5_bypass_api());	//CSR6[7:7]
}

DS_apiRegs&
DS_apiRegs::setdfe_tap4_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_tap4_bypass_api());	//CSR6[6:6]
	return *this;
}
uint
DS_apiRegs::getdfe_tap4_bypass_api(){
	return get_csr_bits(REG_INFO.dfe_tap4_bypass_api());	//CSR6[6:6]
}

DS_apiRegs&
DS_apiRegs::setdfe_tap3_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_tap3_bypass_api());	//CSR6[5:5]
	return *this;
}
uint
DS_apiRegs::getdfe_tap3_bypass_api(){
	return get_csr_bits(REG_INFO.dfe_tap3_bypass_api());	//CSR6[5:5]
}

DS_apiRegs&
DS_apiRegs::setdfe_tap2_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_tap2_bypass_api());	//CSR6[4:4]
	return *this;
}
uint
DS_apiRegs::getdfe_tap2_bypass_api(){
	return get_csr_bits(REG_INFO.dfe_tap2_bypass_api());	//CSR6[4:4]
}

DS_apiRegs&
DS_apiRegs::setdfe_tap1_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_tap1_bypass_api());	//CSR6[3:3]
	return *this;
}
uint
DS_apiRegs::getdfe_tap1_bypass_api(){
	return get_csr_bits(REG_INFO.dfe_tap1_bypass_api());	//CSR6[3:3]
}

DS_apiRegs&
DS_apiRegs::setdfe_tap0_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_tap0_bypass_api());	//CSR6[2:2]
	return *this;
}
uint
DS_apiRegs::getdfe_tap0_bypass_api(){
	return get_csr_bits(REG_INFO.dfe_tap0_bypass_api());	//CSR6[2:2]
}

DS_apiRegs&
DS_apiRegs::setdfe_boost_en_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_boost_en_api());	//CSR6[1:1]
	return *this;
}
uint
DS_apiRegs::getdfe_boost_en_api(){
	return get_csr_bits(REG_INFO.dfe_boost_en_api());	//CSR6[1:1]
}

DS_apiRegs&
DS_apiRegs::setdfe_squelch_en_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_squelch_en_api());	//CSR6[0:0]
	return *this;
}
uint
DS_apiRegs::getdfe_squelch_en_api(){
	return get_csr_bits(REG_INFO.dfe_squelch_en_api());	//CSR6[0:0]
}

DS_apiRegs&
DS_apiRegs::setdfe_zero_en_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_zero_en_api());	//CSR7[15:15]
	return *this;
}
uint
DS_apiRegs::getdfe_zero_en_api(){
	return get_csr_bits(REG_INFO.dfe_zero_en_api());	//CSR7[15:15]
}

DS_apiRegs&
DS_apiRegs::setdfe_biastune_en_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_biastune_en_api());	//CSR7[14:14]
	return *this;
}
uint
DS_apiRegs::getdfe_biastune_en_api(){
	return get_csr_bits(REG_INFO.dfe_biastune_en_api());	//CSR7[14:14]
}

DS_apiRegs&
DS_apiRegs::setdfe_eye_metric_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_eye_metric_api());	//CSR7[13:11]
	return *this;
}
uint
DS_apiRegs::getdfe_eye_metric_api(){
	return get_csr_bits(REG_INFO.dfe_eye_metric_api());	//CSR7[13:11]
}

DS_apiRegs&
DS_apiRegs::setdfe_eye_type_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_eye_type_api());	//CSR7[10:8]
	return *this;
}
uint
DS_apiRegs::getdfe_eye_type_api(){
	return get_csr_bits(REG_INFO.dfe_eye_type_api());	//CSR7[10:8]
}

DS_apiRegs&
DS_apiRegs::setctle_dfe_with_same_priority_api(uint val){
	fill_csr_bits(val,REG_INFO.ctle_dfe_with_same_priority_api());	//CSR7[7:7]
	return *this;
}
uint
DS_apiRegs::getctle_dfe_with_same_priority_api(){
	return get_csr_bits(REG_INFO.ctle_dfe_with_same_priority_api());	//CSR7[7:7]
}

DS_apiRegs&
DS_apiRegs::setdfe_eye_avg_count_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_eye_avg_count_api());	//CSR7[6:4]
	return *this;
}
uint
DS_apiRegs::getdfe_eye_avg_count_api(){
	return get_csr_bits(REG_INFO.dfe_eye_avg_count_api());	//CSR7[6:4]
}

DS_apiRegs&
DS_apiRegs::setdfe_eye_contour_index_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_eye_contour_index_api());	//CSR7[3:0]
	return *this;
}
uint
DS_apiRegs::getdfe_eye_contour_index_api(){
	return get_csr_bits(REG_INFO.dfe_eye_contour_index_api());	//CSR7[3:0]
}

DS_apiRegs&
DS_apiRegs::setds_clkreg_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_clkreg_bypass_api());	//CSR8[15:15]
	return *this;
}
uint
DS_apiRegs::getds_clkreg_bypass_api(){
	return get_csr_bits(REG_INFO.ds_clkreg_bypass_api());	//CSR8[15:15]
}

DS_apiRegs&
DS_apiRegs::setds_txdrvreg_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_txdrvreg_bypass_api());	//CSR8[14:14]
	return *this;
}
uint
DS_apiRegs::getds_txdrvreg_bypass_api(){
	return get_csr_bits(REG_INFO.ds_txdrvreg_bypass_api());	//CSR8[14:14]
}

DS_apiRegs&
DS_apiRegs::setds_txpredrvreg_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_txpredrvreg_bypass_api());	//CSR8[13:13]
	return *this;
}
uint
DS_apiRegs::getds_txpredrvreg_bypass_api(){
	return get_csr_bits(REG_INFO.ds_txpredrvreg_bypass_api());	//CSR8[13:13]
}

DS_apiRegs&
DS_apiRegs::setds_rxclkreg_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_rxclkreg_bypass_api());	//CSR8[12:12]
	return *this;
}
uint
DS_apiRegs::getds_rxclkreg_bypass_api(){
	return get_csr_bits(REG_INFO.ds_rxclkreg_bypass_api());	//CSR8[12:12]
}

DS_apiRegs&
DS_apiRegs::setds_rxdatareg_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_rxdatareg_bypass_api());	//CSR8[11:11]
	return *this;
}
uint
DS_apiRegs::getds_rxdatareg_bypass_api(){
	return get_csr_bits(REG_INFO.ds_rxdatareg_bypass_api());	//CSR8[11:11]
}

DS_apiRegs&
DS_apiRegs::setcentering_en_api(uint val){
	fill_csr_bits(val,REG_INFO.centering_en_api());	//CSR8[10:10]
	return *this;
}
uint
DS_apiRegs::getcentering_en_api(){
	return get_csr_bits(REG_INFO.centering_en_api());	//CSR8[10:10]
}

DS_apiRegs&
DS_apiRegs::setctle_alos_protect_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ctle_alos_protect_en_api());	//CSR8[9:9]
	return *this;
}
uint
DS_apiRegs::getctle_alos_protect_en_api(){
	return get_csr_bits(REG_INFO.ctle_alos_protect_en_api());	//CSR8[9:9]
}

DS_apiRegs&
DS_apiRegs::setctle_eyelos_protect_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ctle_eyelos_protect_en_api());	//CSR8[8:8]
	return *this;
}
uint
DS_apiRegs::getctle_eyelos_protect_en_api(){
	return get_csr_bits(REG_INFO.ctle_eyelos_protect_en_api());	//CSR8[8:8]
}

DS_apiRegs&
DS_apiRegs::setctle_dfetap1_bypass_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ctle_dfetap1_bypass_en_api());	//CSR8[7:7]
	return *this;
}
uint
DS_apiRegs::getctle_dfetap1_bypass_en_api(){
	return get_csr_bits(REG_INFO.ctle_dfetap1_bypass_en_api());	//CSR8[7:7]
}

DS_apiRegs&
DS_apiRegs::setdfe_alos_protect_en_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_alos_protect_en_api());	//CSR8[6:6]
	return *this;
}
uint
DS_apiRegs::getdfe_alos_protect_en_api(){
	return get_csr_bits(REG_INFO.dfe_alos_protect_en_api());	//CSR8[6:6]
}

DS_apiRegs&
DS_apiRegs::setdfe_eyelos_protect_en_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_eyelos_protect_en_api());	//CSR8[5:5]
	return *this;
}
uint
DS_apiRegs::getdfe_eyelos_protect_en_api(){
	return get_csr_bits(REG_INFO.dfe_eyelos_protect_en_api());	//CSR8[5:5]
}

DS_apiRegs&
DS_apiRegs::setdfe_non_random_protect_en_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_non_random_protect_en_api());	//CSR8[4:4]
	return *this;
}
uint
DS_apiRegs::getdfe_non_random_protect_en_api(){
	return get_csr_bits(REG_INFO.dfe_non_random_protect_en_api());	//CSR8[4:4]
}

DS_apiRegs&
DS_apiRegs::setate_ctle_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ate_ctle_en_api());	//CSR8[3:3]
	return *this;
}
uint
DS_apiRegs::getate_ctle_en_api(){
	return get_csr_bits(REG_INFO.ate_ctle_en_api());	//CSR8[3:3]
}

DS_apiRegs&
DS_apiRegs::setalphagen_ofst_en_api(uint val){
	fill_csr_bits(val,REG_INFO.alphagen_ofst_en_api());	//CSR8[2:2]
	return *this;
}
uint
DS_apiRegs::getalphagen_ofst_en_api(){
	return get_csr_bits(REG_INFO.alphagen_ofst_en_api());	//CSR8[2:2]
}

DS_apiRegs&
DS_apiRegs::setds_temp_trig_boost_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_temp_trig_boost_en_api());	//CSR8[1:1]
	return *this;
}
uint
DS_apiRegs::getds_temp_trig_boost_en_api(){
	return get_csr_bits(REG_INFO.ds_temp_trig_boost_en_api());	//CSR8[1:1]
}

DS_apiRegs&
DS_apiRegs::setds_latch_offset_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_latch_offset_en_api());	//CSR8[0:0]
	return *this;
}
uint
DS_apiRegs::getds_latch_offset_en_api(){
	return get_csr_bits(REG_INFO.ds_latch_offset_en_api());	//CSR8[0:0]
}

DS_apiRegs&
DS_apiRegs::setfw_eye_start_api(uint val){
	fill_csr_bits(val,REG_INFO.fw_eye_start_api());	//CSR9[15:15]
	return *this;
}
uint
DS_apiRegs::getfw_eye_start_api(){
	return get_csr_bits(REG_INFO.fw_eye_start_api());	//CSR9[15:15]
}

DS_apiRegs&
DS_apiRegs::setfw_eye_type_api(uint val){
	fill_csr_bits(val,REG_INFO.fw_eye_type_api());	//CSR9[14:12]
	return *this;
}
uint
DS_apiRegs::getfw_eye_type_api(){
	return get_csr_bits(REG_INFO.fw_eye_type_api());	//CSR9[14:12]
}

DS_apiRegs&
DS_apiRegs::setds_cenetring_aux_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_cenetring_aux_en_api());	//CSR9[11:10]
	return *this;
}
uint
DS_apiRegs::getds_cenetring_aux_en_api(){
	return get_csr_bits(REG_INFO.ds_cenetring_aux_en_api());	//CSR9[11:10]
}

DS_apiRegs&
DS_apiRegs::setfw_ate_eye_width_times_api(uint val){
	fill_csr_bits(val,REG_INFO.fw_ate_eye_width_times_api());	//CSR9[9:8]
	return *this;
}
uint
DS_apiRegs::getfw_ate_eye_width_times_api(){
	return get_csr_bits(REG_INFO.fw_ate_eye_width_times_api());	//CSR9[9:8]
}

DS_apiRegs&
DS_apiRegs::setdfe_tap15_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_tap15_bypass_api());	//CSR9[7:7]
	return *this;
}
uint
DS_apiRegs::getdfe_tap15_bypass_api(){
	return get_csr_bits(REG_INFO.dfe_tap15_bypass_api());	//CSR9[7:7]
}

DS_apiRegs&
DS_apiRegs::setdfe_tap14_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_tap14_bypass_api());	//CSR9[6:6]
	return *this;
}
uint
DS_apiRegs::getdfe_tap14_bypass_api(){
	return get_csr_bits(REG_INFO.dfe_tap14_bypass_api());	//CSR9[6:6]
}

DS_apiRegs&
DS_apiRegs::setds_abnormal_restart_adapt_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_abnormal_restart_adapt_api());	//CSR9[5:5]
	return *this;
}
uint
DS_apiRegs::getds_abnormal_restart_adapt_api(){
	return get_csr_bits(REG_INFO.ds_abnormal_restart_adapt_api());	//CSR9[5:5]
}

DS_apiRegs&
DS_apiRegs::setds_rx_train_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_rx_train_en_api());	//CSR9[4:4]
	return *this;
}
uint
DS_apiRegs::getds_rx_train_en_api(){
	return get_csr_bits(REG_INFO.ds_rx_train_en_api());	//CSR9[4:4]
}

DS_apiRegs&
DS_apiRegs::setdfe_run_interval_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_run_interval_api());	//CSR9[3:0]
	return *this;
}
uint
DS_apiRegs::getdfe_run_interval_api(){
	return get_csr_bits(REG_INFO.dfe_run_interval_api());	//CSR9[3:0]
}

DS_apiRegs&
DS_apiRegs::setdfe_trig_boost_mode_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_trig_boost_mode_api());	//CSR10[15:15]
	return *this;
}
uint
DS_apiRegs::getdfe_trig_boost_mode_api(){
	return get_csr_bits(REG_INFO.dfe_trig_boost_mode_api());	//CSR10[15:15]
}

DS_apiRegs&
DS_apiRegs::setctle_latchofst_en_api(uint val){
	fill_csr_bits(val,REG_INFO.ctle_latchofst_en_api());	//CSR10[14:14]
	return *this;
}
uint
DS_apiRegs::getctle_latchofst_en_api(){
	return get_csr_bits(REG_INFO.ctle_latchofst_en_api());	//CSR10[14:14]
}

DS_apiRegs&
DS_apiRegs::seth30_testchip_api(uint val){
	fill_csr_bits(val,REG_INFO.h30_testchip_api());	//CSR10[13:13]
	return *this;
}
uint
DS_apiRegs::geth30_testchip_api(){
	return get_csr_bits(REG_INFO.h30_testchip_api());	//CSR10[13:13]
}

DS_apiRegs&
DS_apiRegs::setds_ctrl10_spare13to0(uint val){
	fill_csr_bits(val,REG_INFO.ds_ctrl10_spare13to0());	//CSR10[12:0]
	return *this;
}
uint
DS_apiRegs::getds_ctrl10_spare13to0(){
	return get_csr_bits(REG_INFO.ds_ctrl10_spare13to0());	//CSR10[12:0]
}

DS_apiRegs&
DS_apiRegs::setds_ctrl11_spare15to0(uint val){
	fill_csr_bits(val,REG_INFO.ds_ctrl11_spare15to0());	//CSR11[15:0]
	return *this;
}
uint
DS_apiRegs::getds_ctrl11_spare15to0(){
	return get_csr_bits(REG_INFO.ds_ctrl11_spare15to0());	//CSR11[15:0]
}

DS_apiRegs&
DS_apiRegs::setds_top_fsm_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_top_fsm_api());	//CSR12[15:8]
	return *this;
}
uint
DS_apiRegs::getds_top_fsm_api(){
	return get_csr_bits(REG_INFO.ds_top_fsm_api());	//CSR12[15:8]
}

DS_apiRegs&
DS_apiRegs::setds_sub0_fsm_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_sub0_fsm_api());	//CSR12[7:0]
	return *this;
}
uint
DS_apiRegs::getds_sub0_fsm_api(){
	return get_csr_bits(REG_INFO.ds_sub0_fsm_api());	//CSR12[7:0]
}

DS_apiRegs&
DS_apiRegs::setds_sub1_fsm_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_sub1_fsm_api());	//CSR13[15:8]
	return *this;
}
uint
DS_apiRegs::getds_sub1_fsm_api(){
	return get_csr_bits(REG_INFO.ds_sub1_fsm_api());	//CSR13[15:8]
}

DS_apiRegs&
DS_apiRegs::setds_sub2_fsm_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_sub2_fsm_api());	//CSR13[7:0]
	return *this;
}
uint
DS_apiRegs::getds_sub2_fsm_api(){
	return get_csr_bits(REG_INFO.ds_sub2_fsm_api());	//CSR13[7:0]
}

DS_apiRegs&
DS_apiRegs::setds_sub3_fsm_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_sub3_fsm_api());	//CSR14[15:12]
	return *this;
}
uint
DS_apiRegs::getds_sub3_fsm_api(){
	return get_csr_bits(REG_INFO.ds_sub3_fsm_api());	//CSR14[15:12]
}

DS_apiRegs&
DS_apiRegs::setdlvl_achieved_status_api(uint val){
	fill_csr_bits(val,REG_INFO.dlvl_achieved_status_api());	//CSR14[11:11]
	return *this;
}
uint
DS_apiRegs::getdlvl_achieved_status_api(){
	return get_csr_bits(REG_INFO.dlvl_achieved_status_api());	//CSR14[11:11]
}

DS_apiRegs&
DS_apiRegs::setlos_det_status_api(uint val){
	fill_csr_bits(val,REG_INFO.los_det_status_api());	//CSR14[10:10]
	return *this;
}
uint
DS_apiRegs::getlos_det_status_api(){
	return get_csr_bits(REG_INFO.los_det_status_api());	//CSR14[10:10]
}

DS_apiRegs&
DS_apiRegs::setdata_center_status_api(uint val){
	fill_csr_bits(val,REG_INFO.data_center_status_api());	//CSR14[9:9]
	return *this;
}
uint
DS_apiRegs::getdata_center_status_api(){
	return get_csr_bits(REG_INFO.data_center_status_api());	//CSR14[9:9]
}

DS_apiRegs&
DS_apiRegs::setctle_done_status_api(uint val){
	fill_csr_bits(val,REG_INFO.ctle_done_status_api());	//CSR14[8:8]
	return *this;
}
uint
DS_apiRegs::getctle_done_status_api(){
	return get_csr_bits(REG_INFO.ctle_done_status_api());	//CSR14[8:8]
}

DS_apiRegs&
DS_apiRegs::setds_soft_reset_status_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_soft_reset_status_api());	//CSR14[7:7]
	return *this;
}
uint
DS_apiRegs::getds_soft_reset_status_api(){
	return get_csr_bits(REG_INFO.ds_soft_reset_status_api());	//CSR14[7:7]
}

DS_apiRegs&
DS_apiRegs::setds_calib_done_status_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_calib_done_status_api());	//CSR14[6:6]
	return *this;
}
uint
DS_apiRegs::getds_calib_done_status_api(){
	return get_csr_bits(REG_INFO.ds_calib_done_status_api());	//CSR14[6:6]
}

DS_apiRegs&
DS_apiRegs::setds_adapt_done_status_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_adapt_done_status_api());	//CSR14[5:5]
	return *this;
}
uint
DS_apiRegs::getds_adapt_done_status_api(){
	return get_csr_bits(REG_INFO.ds_adapt_done_status_api());	//CSR14[5:5]
}

DS_apiRegs&
DS_apiRegs::setds_stat14_spare6to0(uint val){
	fill_csr_bits(val,REG_INFO.ds_stat14_spare6to0());	//CSR14[4:0]
	return *this;
}
uint
DS_apiRegs::getds_stat14_spare6to0(){
	return get_csr_bits(REG_INFO.ds_stat14_spare6to0());	//CSR14[4:0]
}

DS_apiRegs&
DS_apiRegs::setfw_eye_height_api(uint val){
	fill_csr_bits(val,REG_INFO.fw_eye_height_api());	//CSR15[15:8]
	return *this;
}
uint
DS_apiRegs::getfw_eye_height_api(){
	return get_csr_bits(REG_INFO.fw_eye_height_api());	//CSR15[15:8]
}

DS_apiRegs&
DS_apiRegs::setfw_eye_width_api(uint val){
	fill_csr_bits(val,REG_INFO.fw_eye_width_api());	//CSR15[7:0]
	return *this;
}
uint
DS_apiRegs::getfw_eye_width_api(){
	return get_csr_bits(REG_INFO.fw_eye_width_api());	//CSR15[7:0]
}

DS_apiRegs&
DS_apiRegs::setfw_ate_max_eye_width_api(uint val){
	fill_csr_bits(val,REG_INFO.fw_ate_max_eye_width_api());	//CSR16[15:8]
	return *this;
}
uint
DS_apiRegs::getfw_ate_max_eye_width_api(){
	return get_csr_bits(REG_INFO.fw_ate_max_eye_width_api());	//CSR16[15:8]
}

DS_apiRegs&
DS_apiRegs::setfw_ate_min_eye_width_api(uint val){
	fill_csr_bits(val,REG_INFO.fw_ate_min_eye_width_api());	//CSR16[7:0]
	return *this;
}
uint
DS_apiRegs::getfw_ate_min_eye_width_api(){
	return get_csr_bits(REG_INFO.fw_ate_min_eye_width_api());	//CSR16[7:0]
}

DS_apiRegs&
DS_apiRegs::setds_stat17_spare15to0(uint val){
	fill_csr_bits(val,REG_INFO.ds_stat17_spare15to0());	//CSR17[15:0]
	return *this;
}
uint
DS_apiRegs::getds_stat17_spare15to0(){
	return get_csr_bits(REG_INFO.ds_stat17_spare15to0());	//CSR17[15:0]
}
E_HILINK_REGISTER_TYPE DS_apiRegs::getType()
{
	return HILINK_PERLANE_REGISTER;
}
