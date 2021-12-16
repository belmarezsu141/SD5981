#include <HILINK_DRIVE/HiLink_ABIST_apiRegs.h>

#include <iostream>
using namespace std;
ABIST_apiRegs::ABIST_apiRegs() {
	// TODO Auto-generated constructor stub
	for(int i=0;i<ABIST_API_CSR_NUM;i++){
		csr[i]=0;
	}
	sliceID=0;
	macroID=0;
	broadcast=false;
	reset_csr_verify();
}

ABIST_apiRegs::~ABIST_apiRegs() {}

bool
ABIST_apiRegs::get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos){
	if(csrIndex>=ABIST_API_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	return REG_INFO.get_reg_infos(csrIndex,reg_infos);
}

ABIST_apiRegs&
ABIST_apiRegs::getInstance(){
	static ABIST_apiRegs theInstance;
	return theInstance;
}

uint
ABIST_apiRegs::get_HILINK_MAX_LANE_NUM(){
	//TODO: add your code for CSR Address mapping
	return HILINK_LANE_NUM;
}

uint
ABIST_apiRegs::getAddressMapToHiLink(int csrIndex){
	if(csrIndex>=ABIST_API_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	//TODO: add your code for CSR Address mapping
	uint retAddress = 0;
	retAddress = 0x1FDB6 + csrIndex*2;
	return retAddress;
}


uint&
ABIST_apiRegs::get_csr(uint csrIndex){
	if(csrIndex>=ABIST_API_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	return csr[csrIndex];
}

void
ABIST_apiRegs::get_default_MacroLaneID(T_MacroLaneID& id){
	//TODO: add your code for CSR Address mapping
	id.MacroID=macroID;
	id.LaneID=sliceID;
}

uint
ABIST_apiRegs::getCSRCount(){
	return ABIST_API_CSR_NUM;
}

string
ABIST_apiRegs::getName(){
	return "ABIST_API";
}

///////////////////////////////////////////////////////////////////////////


	/// 0:disable, 1:enable
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::vco_lock_range_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{0,"vco_lock_range_abist_api",15,15}
	};
	return reg;
}

	/// 0:disable, 1:enable
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::vco_lock_robustness_static_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{0,"vco_lock_robustness_static_abist_api",14,14}
	};
	return reg;
}

	/// 0:disable, 1:enable
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::vco_lock_robustness_dynamic_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{0,"vco_lock_robustness_dynamic_abist_api",13,13}
	};
	return reg;
}

	/// 0:disable, 1:enable
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::vco_band_freq_range_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{0,"vco_band_freq_range_abist_api",12,12}
	};
	return reg;
}

	/// 0:disable, 1:enable
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::tx2rx_outer_lpbk_clk_purity_wcdr_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{0,"tx2rx_outer_lpbk_clk_purity_wcdr_abist_api",11,11}
	};
	return reg;
}

	/// 0:disable, 1:enable
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::tx2rx_outer_lpbk_clk_purity_wocdr_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{0,"tx2rx_outer_lpbk_clk_purity_wocdr_abist_api",10,10}
	};
	return reg;
}

	/// 0:disable, 1:enable
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::tx2rx_outer_lpbk_prbs_stress_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{0,"tx2rx_outer_lpbk_prbs_stress_abist_api",9,9}
	};
	return reg;
}

	/// 0:disable, 1:enable
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::tx2rx_predriver_lpbk_clk_purity_wcdr_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{0,"tx2rx_predriver_lpbk_clk_purity_wcdr_abist_api",8,8}
	};
	return reg;
}

	/// 0:disable, 1:enable
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::tx2rx_predriver_lpbk_prbs_stress_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{0,"tx2rx_predriver_lpbk_prbs_stress_abist_api",7,7}
	};
	return reg;
}

	/// 0:disable, 1:enable
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::tx2rx_bumpdriver_lpbk_prbs_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{0,"tx2rx_bumpdriver_lpbk_prbs_abist_api",6,6}
	};
	return reg;
}

	/// 0:disable, 1:enable
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::corner_sensor_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{0,"corner_sensor_abist_api",5,5}
	};
	return reg;
}

	/// 0:disable, 1:enable
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::fir_dc_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{0,"fir_dc_abist_api",4,4}
	};
	return reg;
}

	/// 0:disable, 1:enable
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::atb_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{0,"atb_abist_api",3,3}
	};
	return reg;
}

	/// 0:disable, 1:enable
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::calib_register_check_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{0,"calib_register_check_abist_api",2,2}
	};
	return reg;
}

	/// 0:disable, 1:enable
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::ctle_dc_gain_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{0,"ctle_dc_gain_abist_api",1,1}
	};
	return reg;
}

	/// 0:disable, 1:enable
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::latch_ofst_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{0,"latch_ofst_abist_api",0,0}
	};
	return reg;
}

	/// 0:disable, 1:enable
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::alphagen_sweep_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{1,"alphagen_sweep_abist_api",15,15}
	};
	return reg;
}

	/// 0:disable, 1:enable
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::regulator_sweep_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{1,"regulator_sweep_abist_api",14,14}
	};
	return reg;
}

	/// 0:disable, 1:enable
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::dfe_idac_sweep_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{1,"dfe_idac_sweep_abist_api",13,13}
	};
	return reg;
}

	/// Spare
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::adc_stability_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{1,"adc_stability_abist_api",12,12}
	};
	return reg;
}

const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::dlos_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{1,"dlos_abist_api",11,11}
	};
	return reg;
}

const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::comparator_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{1,"comparator_abist_api",10,10}
	};
	return reg;
}

const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::abist_ctrl1_spare9to0(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{1,"abist_ctrl1_spare9to0",9,0}
	};
	return reg;
}
	/// 00: Full; 
	/// 01: Simplified Mode0
	/// 10: Simplified Mode1
	/// 11: Simplified Mode2
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::test_mode_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{2,"test_mode_abist_api",15,14}
	};
	return reg;
}

	/// adc_stability_ss_adc_bypass_api
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::adc_stability_ss_adc_bypass_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{2,"adc_stability_ss_adc_bypass_api",13,13}
	};
	return reg;
}

/// adc_stability_cs_adc_bypass_api
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::adc_stability_cs_adc_bypass_api(){
const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
	{2,"adc_stability_cs_adc_bypass_api",12,12}
};
return reg;
}
/// adc_stability_ds_adc_bypass_api
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::adc_stability_ds_adc_bypass_api(){
const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
	{2,"adc_stability_ds_adc_bypass_api",11,11}
};
return reg;
}
/// adc_stability_adc_loop_cnt_api
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::adc_stability_adc_loop_cnt_api(){
const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
	{2,"adc_stability_adc_loop_cnt_api",10,8}
};
return reg;
}
/// adc_stability_ref_vol_mode_api
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::adc_stability_ref_vol_mode_api(){
const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
	{2,"adc_stability_ref_vol_mode_api",7,6}
};
return reg;
}

/// spare
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::abist_ctrl2_spare5to0(){
const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
	{2,"abist_ctrl2_spare5to0",5,0}
};
return reg;
}

	/// Spare
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::abist_ctrl3_spare15to0(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{3,"abist_ctrl3_spare15to0",15,0}
	};
	return reg;
}

	/// 0: something wrong with the spec in fw; 1: PASS
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::vco_lock_range_status_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{4,"vco_lock_range_status_abist_api",15,15}
	};
	return reg;
}

	/// 0: something wrong with the spec in fw; 1: PASS
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::vco_lock_robustness_static_status_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{4,"vco_lock_robustness_static_status_abist_api",14,14}
	};
	return reg;
}

	/// 0: something wrong with the spec in fw; 1: PASS
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::vco_lock_robustness_dynamic_status_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{4,"vco_lock_robustness_dynamic_status_abist_api",13,13}
	};
	return reg;
}

	/// 0: something wrong with the spec in fw; 1: PASS
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::vco_band_freq_range_status_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{4,"vco_band_freq_range_status_abist_api",12,12}
	};
	return reg;
}

	/// 0: something wrong with the spec in fw; 1: PASS
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::tx2rx_outer_lpbk_clk_purity_wcdr_status_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{4,"tx2rx_outer_lpbk_clk_purity_wcdr_status_abist_api",11,11}
	};
	return reg;
}

	/// 0: something wrong with the spec in fw; 1: PASS
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::tx2rx_outer_lpbk_clk_purity_wocdr_status_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{4,"tx2rx_outer_lpbk_clk_purity_wocdr_status_abist_api",10,10}
	};
	return reg;
}

	/// 0: something wrong with the spec in fw; 1: PASS
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::tx2rx_outer_lpbk_prbs_stress_status_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{4,"tx2rx_outer_lpbk_prbs_stress_status_abist_api",9,9}
	};
	return reg;
}

	/// 0: something wrong with the spec in fw; 1: PASS
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::tx2rx_predriver_lpbk_clk_purity_wcdr_status_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{4,"tx2rx_predriver_lpbk_clk_purity_wcdr_status_abist_api",8,8}
	};
	return reg;
}

	/// 0: something wrong with the spec in fw; 1: PASS
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::tx2rx_predriver_lpbk_prbs_stress_status_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{4,"tx2rx_predriver_lpbk_prbs_stress_status_abist_api",7,7}
	};
	return reg;
}

	/// 0: something wrong with the spec in fw; 1: PASS
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::tx2rx_bumpdriver_lpbk_prbs_status_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{4,"tx2rx_bumpdriver_lpbk_prbs_status_abist_api",6,6}
	};
	return reg;
}

	/// 0: something wrong with the spec in fw; 1: PASS
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::corner_sensor_status_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{4,"corner_sensor_status_abist_api",5,5}
	};
	return reg;
}

	/// 0: something wrong with the spec in fw; 1: PASS
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::fir_dc_status_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{4,"fir_dc_status_abist_api",4,4}
	};
	return reg;
}

	/// 0: something wrong with the spec in fw; 1: PASS
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::atb_status_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{4,"atb_status_abist_api",3,3}
	};
	return reg;
}

	/// 0: something wrong with the spec in fw; 1: PASS
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::calib_register_check_status_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{4,"calib_register_check_status_abist_api",2,2}
	};
	return reg;
}

	/// 0: something wrong with the spec in fw; 1: PASS
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::ctle_dc_gain_status_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{4,"ctle_dc_gain_status_abist_api",1,1}
	};
	return reg;
}

	/// 0: something wrong with the spec in fw; 1: PASS
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::latch_ofst_status_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{4,"latch_ofst_status_abist_api",0,0}
	};
	return reg;
}

	/// 0: something wrong with the spec in fw; 1: PASS
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::alphagen_sweep_status_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{5,"alphagen_sweep_status_abist_api",15,15}
	};
	return reg;
}

	/// 0: something wrong with the spec in fw; 1: PASS
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::regulator_sweep_status_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{5,"regulator_sweep_status_abist_api",14,14}
	};
	return reg;
}

	/// 0: something wrong with the spec in fw; 1: PASS
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::dfe_idac_sweep_status_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{5,"dfe_idac_sweep_status_abist_api",13,13}
	};
	return reg;
}

/// adc_stability_status_abist_api
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::adc_stability_status_abist_api(){
const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
	{5,"adc_stability_status_abist_api",12,12}
};
return reg;
}
/// Spare
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::dlos_status_abist_api(){
const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
	{5,"dlos_status_abist_api",11,11}
};
return reg;
}
/// Spare
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::comparator_status_abist_api(){
const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
	{5,"comparator_status_abist_api",10,10}
};
return reg;
}
	/// Spare
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::abist_status1_spare9to0(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{5,"abist_status1_spare9to0",9,0}
	};
	return reg;
}

	/// ABIST Top FSM state
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::top_fsm_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{6,"top_fsm_abist_api",15,8}
	};
	return reg;
}

	/// ABIST Sub0 FSM state
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::sub0_fsm_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{6,"sub0_fsm_abist_api",7,0}
	};
	return reg;
}

	/// ABIST Sub1 FSM state
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::sub1_fsm_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{7,"sub1_fsm_abist_api",15,8}
	};
	return reg;
}

	/// ABIST Sub2 FSM state
const T_REG_INFO_EX&
ABIST_apiRegs::_REG_INFO::sub2_fsm_abist_api(){
	const static T_REG_INFO_EX reg={ABIST_apiRegs::getInstance(),
		{7,"sub2_fsm_abist_api",7,0}
	};
	return reg;
}
bool
ABIST_apiRegs::_REG_INFO::get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos){
	reg_infos.clear();
	switch(csr){
		case 0:
			reg_infos.push_back(vco_lock_range_abist_api().reg_info);
			reg_infos.push_back(vco_lock_robustness_static_abist_api().reg_info);
			reg_infos.push_back(vco_lock_robustness_dynamic_abist_api().reg_info);
			reg_infos.push_back(vco_band_freq_range_abist_api().reg_info);
			reg_infos.push_back(tx2rx_outer_lpbk_clk_purity_wcdr_abist_api().reg_info);
			reg_infos.push_back(tx2rx_outer_lpbk_clk_purity_wocdr_abist_api().reg_info);
			reg_infos.push_back(tx2rx_outer_lpbk_prbs_stress_abist_api().reg_info);
			reg_infos.push_back(tx2rx_predriver_lpbk_clk_purity_wcdr_abist_api().reg_info);
			reg_infos.push_back(tx2rx_predriver_lpbk_prbs_stress_abist_api().reg_info);
			reg_infos.push_back(tx2rx_bumpdriver_lpbk_prbs_abist_api().reg_info);
			reg_infos.push_back(corner_sensor_abist_api().reg_info);
			reg_infos.push_back(fir_dc_abist_api().reg_info);
			reg_infos.push_back(atb_abist_api().reg_info);
			reg_infos.push_back(calib_register_check_abist_api().reg_info);
			reg_infos.push_back(ctle_dc_gain_abist_api().reg_info);
			reg_infos.push_back(latch_ofst_abist_api().reg_info);
			break;
		case 1:
			reg_infos.push_back(alphagen_sweep_abist_api().reg_info);
			reg_infos.push_back(regulator_sweep_abist_api().reg_info);
			reg_infos.push_back(dfe_idac_sweep_abist_api().reg_info);
			reg_infos.push_back(adc_stability_abist_api().reg_info);
			reg_infos.push_back(dlos_abist_api().reg_info);
			reg_infos.push_back(comparator_abist_api().reg_info);
			reg_infos.push_back(abist_ctrl1_spare9to0().reg_info);
			break;
		case 2:
			reg_infos.push_back(test_mode_abist_api().reg_info);
			reg_infos.push_back(adc_stability_ss_adc_bypass_api().reg_info);
			reg_infos.push_back(adc_stability_cs_adc_bypass_api().reg_info);
			reg_infos.push_back(adc_stability_ds_adc_bypass_api().reg_info);
			reg_infos.push_back(adc_stability_adc_loop_cnt_api().reg_info);
			reg_infos.push_back(adc_stability_ref_vol_mode_api().reg_info);
			reg_infos.push_back(abist_ctrl2_spare5to0().reg_info);
			break;
		case 3:
			reg_infos.push_back(abist_ctrl3_spare15to0().reg_info);
			break;
		case 4:
			reg_infos.push_back(vco_lock_range_status_abist_api().reg_info);
			reg_infos.push_back(vco_lock_robustness_static_status_abist_api().reg_info);
			reg_infos.push_back(vco_lock_robustness_dynamic_status_abist_api().reg_info);
			reg_infos.push_back(vco_band_freq_range_status_abist_api().reg_info);
			reg_infos.push_back(tx2rx_outer_lpbk_clk_purity_wcdr_status_abist_api().reg_info);
			reg_infos.push_back(tx2rx_outer_lpbk_clk_purity_wocdr_status_abist_api().reg_info);
			reg_infos.push_back(tx2rx_outer_lpbk_prbs_stress_status_abist_api().reg_info);
			reg_infos.push_back(tx2rx_predriver_lpbk_clk_purity_wcdr_status_abist_api().reg_info);
			reg_infos.push_back(tx2rx_predriver_lpbk_prbs_stress_status_abist_api().reg_info);
			reg_infos.push_back(tx2rx_bumpdriver_lpbk_prbs_status_abist_api().reg_info);
			reg_infos.push_back(corner_sensor_status_abist_api().reg_info);
			reg_infos.push_back(fir_dc_status_abist_api().reg_info);
			reg_infos.push_back(atb_status_abist_api().reg_info);
			reg_infos.push_back(calib_register_check_status_abist_api().reg_info);
			reg_infos.push_back(ctle_dc_gain_status_abist_api().reg_info);
			reg_infos.push_back(latch_ofst_status_abist_api().reg_info);
			break;
		case 5:
			reg_infos.push_back(alphagen_sweep_status_abist_api().reg_info);
			reg_infos.push_back(regulator_sweep_status_abist_api().reg_info);
			reg_infos.push_back(dfe_idac_sweep_status_abist_api().reg_info);
			reg_infos.push_back(adc_stability_status_abist_api().reg_info);
			reg_infos.push_back(dlos_status_abist_api().reg_info);
			reg_infos.push_back(comparator_status_abist_api().reg_info);
			reg_infos.push_back(abist_status1_spare9to0().reg_info);
			break;
		case 6:
			reg_infos.push_back(top_fsm_abist_api().reg_info);
			reg_infos.push_back(sub0_fsm_abist_api().reg_info);
			break;
		case 7:
			reg_infos.push_back(sub1_fsm_abist_api().reg_info);
			reg_infos.push_back(sub2_fsm_abist_api().reg_info);
			break;
		default:
			break;
	}
	return (reg_infos.size()>0);
}


ABIST_apiRegs&
ABIST_apiRegs::setvco_lock_range_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.vco_lock_range_abist_api());	//CSR0[15:15]
	return *this;
}
uint
ABIST_apiRegs::getvco_lock_range_abist_api(){
	return get_csr_bits(REG_INFO.vco_lock_range_abist_api());	//CSR0[15:15]
}

ABIST_apiRegs&
ABIST_apiRegs::setvco_lock_robustness_static_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.vco_lock_robustness_static_abist_api());	//CSR0[14:14]
	return *this;
}
uint
ABIST_apiRegs::getvco_lock_robustness_static_abist_api(){
	return get_csr_bits(REG_INFO.vco_lock_robustness_static_abist_api());	//CSR0[14:14]
}

ABIST_apiRegs&
ABIST_apiRegs::setvco_lock_robustness_dynamic_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.vco_lock_robustness_dynamic_abist_api());	//CSR0[13:13]
	return *this;
}
uint
ABIST_apiRegs::getvco_lock_robustness_dynamic_abist_api(){
	return get_csr_bits(REG_INFO.vco_lock_robustness_dynamic_abist_api());	//CSR0[13:13]
}

ABIST_apiRegs&
ABIST_apiRegs::setvco_band_freq_range_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.vco_band_freq_range_abist_api());	//CSR0[12:12]
	return *this;
}
uint
ABIST_apiRegs::getvco_band_freq_range_abist_api(){
	return get_csr_bits(REG_INFO.vco_band_freq_range_abist_api());	//CSR0[12:12]
}

ABIST_apiRegs&
ABIST_apiRegs::settx2rx_outer_lpbk_clk_purity_wcdr_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.tx2rx_outer_lpbk_clk_purity_wcdr_abist_api());	//CSR0[11:11]
	return *this;
}
uint
ABIST_apiRegs::gettx2rx_outer_lpbk_clk_purity_wcdr_abist_api(){
	return get_csr_bits(REG_INFO.tx2rx_outer_lpbk_clk_purity_wcdr_abist_api());	//CSR0[11:11]
}

ABIST_apiRegs&
ABIST_apiRegs::settx2rx_outer_lpbk_clk_purity_wocdr_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.tx2rx_outer_lpbk_clk_purity_wocdr_abist_api());	//CSR0[10:10]
	return *this;
}
uint
ABIST_apiRegs::gettx2rx_outer_lpbk_clk_purity_wocdr_abist_api(){
	return get_csr_bits(REG_INFO.tx2rx_outer_lpbk_clk_purity_wocdr_abist_api());	//CSR0[10:10]
}

ABIST_apiRegs&
ABIST_apiRegs::settx2rx_outer_lpbk_prbs_stress_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.tx2rx_outer_lpbk_prbs_stress_abist_api());	//CSR0[9:9]
	return *this;
}
uint
ABIST_apiRegs::gettx2rx_outer_lpbk_prbs_stress_abist_api(){
	return get_csr_bits(REG_INFO.tx2rx_outer_lpbk_prbs_stress_abist_api());	//CSR0[9:9]
}

ABIST_apiRegs&
ABIST_apiRegs::settx2rx_predriver_lpbk_clk_purity_wcdr_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.tx2rx_predriver_lpbk_clk_purity_wcdr_abist_api());	//CSR0[8:8]
	return *this;
}
uint
ABIST_apiRegs::gettx2rx_predriver_lpbk_clk_purity_wcdr_abist_api(){
	return get_csr_bits(REG_INFO.tx2rx_predriver_lpbk_clk_purity_wcdr_abist_api());	//CSR0[8:8]
}

ABIST_apiRegs&
ABIST_apiRegs::settx2rx_predriver_lpbk_prbs_stress_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.tx2rx_predriver_lpbk_prbs_stress_abist_api());	//CSR0[7:7]
	return *this;
}
uint
ABIST_apiRegs::gettx2rx_predriver_lpbk_prbs_stress_abist_api(){
	return get_csr_bits(REG_INFO.tx2rx_predriver_lpbk_prbs_stress_abist_api());	//CSR0[7:7]
}

ABIST_apiRegs&
ABIST_apiRegs::settx2rx_bumpdriver_lpbk_prbs_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.tx2rx_bumpdriver_lpbk_prbs_abist_api());	//CSR0[6:6]
	return *this;
}
uint
ABIST_apiRegs::gettx2rx_bumpdriver_lpbk_prbs_abist_api(){
	return get_csr_bits(REG_INFO.tx2rx_bumpdriver_lpbk_prbs_abist_api());	//CSR0[6:6]
}

ABIST_apiRegs&
ABIST_apiRegs::setcorner_sensor_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.corner_sensor_abist_api());	//CSR0[5:5]
	return *this;
}
uint
ABIST_apiRegs::getcorner_sensor_abist_api(){
	return get_csr_bits(REG_INFO.corner_sensor_abist_api());	//CSR0[5:5]
}

ABIST_apiRegs&
ABIST_apiRegs::setfir_dc_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.fir_dc_abist_api());	//CSR0[4:4]
	return *this;
}
uint
ABIST_apiRegs::getfir_dc_abist_api(){
	return get_csr_bits(REG_INFO.fir_dc_abist_api());	//CSR0[4:4]
}

ABIST_apiRegs&
ABIST_apiRegs::setatb_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.atb_abist_api());	//CSR0[3:3]
	return *this;
}
uint
ABIST_apiRegs::getatb_abist_api(){
	return get_csr_bits(REG_INFO.atb_abist_api());	//CSR0[3:3]
}

ABIST_apiRegs&
ABIST_apiRegs::setcalib_register_check_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.calib_register_check_abist_api());	//CSR0[2:2]
	return *this;
}
uint
ABIST_apiRegs::getcalib_register_check_abist_api(){
	return get_csr_bits(REG_INFO.calib_register_check_abist_api());	//CSR0[2:2]
}

ABIST_apiRegs&
ABIST_apiRegs::setctle_dc_gain_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.ctle_dc_gain_abist_api());	//CSR0[1:1]
	return *this;
}
uint
ABIST_apiRegs::getctle_dc_gain_abist_api(){
	return get_csr_bits(REG_INFO.ctle_dc_gain_abist_api());	//CSR0[1:1]
}

ABIST_apiRegs&
ABIST_apiRegs::setlatch_ofst_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.latch_ofst_abist_api());	//CSR0[0:0]
	return *this;
}
uint
ABIST_apiRegs::getlatch_ofst_abist_api(){
	return get_csr_bits(REG_INFO.latch_ofst_abist_api());	//CSR0[0:0]
}

ABIST_apiRegs&
ABIST_apiRegs::setalphagen_sweep_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.alphagen_sweep_abist_api());	//CSR1[15:15]
	return *this;
}
uint
ABIST_apiRegs::getalphagen_sweep_abist_api(){
	return get_csr_bits(REG_INFO.alphagen_sweep_abist_api());	//CSR1[15:15]
}

ABIST_apiRegs&
ABIST_apiRegs::setregulator_sweep_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.regulator_sweep_abist_api());	//CSR1[14:14]
	return *this;
}
uint
ABIST_apiRegs::getregulator_sweep_abist_api(){
	return get_csr_bits(REG_INFO.regulator_sweep_abist_api());	//CSR1[14:14]
}

ABIST_apiRegs&
ABIST_apiRegs::setdfe_idac_sweep_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_idac_sweep_abist_api());	//CSR1[13:13]
	return *this;
}
uint
ABIST_apiRegs::getdfe_idac_sweep_abist_api(){
	return get_csr_bits(REG_INFO.dfe_idac_sweep_abist_api());	//CSR1[13:13]
}
ABIST_apiRegs&
ABIST_apiRegs::setadc_stability_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.adc_stability_abist_api());	//CSR1[12:0]
	return *this;
}
uint
ABIST_apiRegs::getadc_stability_abist_api(){
	return get_csr_bits(REG_INFO.adc_stability_abist_api());	//CSR1[12:0]
}

ABIST_apiRegs&
ABIST_apiRegs::setdlos_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.dlos_abist_api());	//CSR1[11:11]
	return *this;
}
uint
ABIST_apiRegs::getdlos_abist_api(){
	return get_csr_bits(REG_INFO.dlos_abist_api());	//CSR1[11:11]
}

ABIST_apiRegs&
ABIST_apiRegs::setcomparator_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.comparator_abist_api());	//CSR1[10:10]
	return *this;
}
uint
ABIST_apiRegs::getcomparator_abist_api(){
	return get_csr_bits(REG_INFO.comparator_abist_api());	//CSR1[10:10]
}

ABIST_apiRegs&
ABIST_apiRegs::setabist_ctrl1_spare9to0(uint val){
	fill_csr_bits(val,REG_INFO.abist_ctrl1_spare9to0());	//CSR1[9:0]
	return *this;
}
uint
ABIST_apiRegs::getabist_ctrl1_spare9to0(){
	return get_csr_bits(REG_INFO.abist_ctrl1_spare9to0());	//CSR1[9:0]
}

ABIST_apiRegs&
ABIST_apiRegs::settest_mode_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.test_mode_abist_api());	//CSR2[15:14]
	return *this;
}
uint
ABIST_apiRegs::gettest_mode_abist_api(){
	return get_csr_bits(REG_INFO.test_mode_abist_api());	//CSR2[15:14]
}

ABIST_apiRegs&
ABIST_apiRegs::setadc_stability_ss_adc_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.adc_stability_ss_adc_bypass_api());	//CSR2[13:13]
	return *this;
}
uint
ABIST_apiRegs::getadc_stability_ss_adc_bypass_api(){
	return get_csr_bits(REG_INFO.adc_stability_ss_adc_bypass_api());	//CSR2[13:13]
}

ABIST_apiRegs&
ABIST_apiRegs::setadc_stability_cs_adc_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.adc_stability_cs_adc_bypass_api());	//CSR2[12:12]
	return *this;
}
uint
ABIST_apiRegs::getadc_stability_cs_adc_bypass_api(){
	return get_csr_bits(REG_INFO.adc_stability_cs_adc_bypass_api());	//CSR2[12:12]
}

ABIST_apiRegs&
ABIST_apiRegs::setadc_stability_ds_adc_bypass_api(uint val){
	fill_csr_bits(val,REG_INFO.adc_stability_ds_adc_bypass_api());	//CSR2[11:11]
	return *this;
}
uint
ABIST_apiRegs::getadc_stability_ds_adc_bypass_api(){
	return get_csr_bits(REG_INFO.adc_stability_ds_adc_bypass_api());	//CSR2[11:11]
}

ABIST_apiRegs&
ABIST_apiRegs::setadc_stability_adc_loop_cnt_api(uint val){
	fill_csr_bits(val,REG_INFO.adc_stability_adc_loop_cnt_api());	//CSR2[10:8]
	return *this;
}
uint
ABIST_apiRegs::getadc_stability_adc_loop_cnt_api(){
	return get_csr_bits(REG_INFO.adc_stability_adc_loop_cnt_api());	//CSR2[10:8]
}

ABIST_apiRegs&
ABIST_apiRegs::setadc_stability_ref_vol_mode_api(uint val){
	fill_csr_bits(val,REG_INFO.adc_stability_ref_vol_mode_api());	//CSR2[7:6]
	return *this;
}
uint
ABIST_apiRegs::getadc_stability_ref_vol_mode_api(){
	return get_csr_bits(REG_INFO.adc_stability_ref_vol_mode_api());	//CSR2[7:6]
}

ABIST_apiRegs&
ABIST_apiRegs::setabist_ctrl2_spare5to0(uint val){
	fill_csr_bits(val,REG_INFO.abist_ctrl2_spare5to0());	//CSR2[5:0]
	return *this;
}
uint
ABIST_apiRegs::getabist_ctrl2_spare5to0(){
	return get_csr_bits(REG_INFO.abist_ctrl2_spare5to0());	//CSR2[5:0]
}

ABIST_apiRegs&
ABIST_apiRegs::setabist_ctrl3_spare15to0(uint val){
	fill_csr_bits(val,REG_INFO.abist_ctrl3_spare15to0());	//CSR3[15:0]
	return *this;
}
uint
ABIST_apiRegs::getabist_ctrl3_spare15to0(){
	return get_csr_bits(REG_INFO.abist_ctrl3_spare15to0());	//CSR3[15:0]
}

ABIST_apiRegs&
ABIST_apiRegs::setvco_lock_range_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.vco_lock_range_status_abist_api());	//CSR4[15:15]
	return *this;
}
uint
ABIST_apiRegs::getvco_lock_range_status_abist_api(){
	return get_csr_bits(REG_INFO.vco_lock_range_status_abist_api());	//CSR4[15:15]
}

ABIST_apiRegs&
ABIST_apiRegs::setvco_lock_robustness_static_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.vco_lock_robustness_static_status_abist_api());	//CSR4[14:14]
	return *this;
}
uint
ABIST_apiRegs::getvco_lock_robustness_static_status_abist_api(){
	return get_csr_bits(REG_INFO.vco_lock_robustness_static_status_abist_api());	//CSR4[14:14]
}

ABIST_apiRegs&
ABIST_apiRegs::setvco_lock_robustness_dynamic_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.vco_lock_robustness_dynamic_status_abist_api());	//CSR4[13:13]
	return *this;
}
uint
ABIST_apiRegs::getvco_lock_robustness_dynamic_status_abist_api(){
	return get_csr_bits(REG_INFO.vco_lock_robustness_dynamic_status_abist_api());	//CSR4[13:13]
}

ABIST_apiRegs&
ABIST_apiRegs::setvco_band_freq_range_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.vco_band_freq_range_status_abist_api());	//CSR4[12:12]
	return *this;
}
uint
ABIST_apiRegs::getvco_band_freq_range_status_abist_api(){
	return get_csr_bits(REG_INFO.vco_band_freq_range_status_abist_api());	//CSR4[12:12]
}

ABIST_apiRegs&
ABIST_apiRegs::settx2rx_outer_lpbk_clk_purity_wcdr_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.tx2rx_outer_lpbk_clk_purity_wcdr_status_abist_api());	//CSR4[11:11]
	return *this;
}
uint
ABIST_apiRegs::gettx2rx_outer_lpbk_clk_purity_wcdr_status_abist_api(){
	return get_csr_bits(REG_INFO.tx2rx_outer_lpbk_clk_purity_wcdr_status_abist_api());	//CSR4[11:11]
}

ABIST_apiRegs&
ABIST_apiRegs::settx2rx_outer_lpbk_clk_purity_wocdr_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.tx2rx_outer_lpbk_clk_purity_wocdr_status_abist_api());	//CSR4[10:10]
	return *this;
}
uint
ABIST_apiRegs::gettx2rx_outer_lpbk_clk_purity_wocdr_status_abist_api(){
	return get_csr_bits(REG_INFO.tx2rx_outer_lpbk_clk_purity_wocdr_status_abist_api());	//CSR4[10:10]
}

ABIST_apiRegs&
ABIST_apiRegs::settx2rx_outer_lpbk_prbs_stress_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.tx2rx_outer_lpbk_prbs_stress_status_abist_api());	//CSR4[9:9]
	return *this;
}
uint
ABIST_apiRegs::gettx2rx_outer_lpbk_prbs_stress_status_abist_api(){
	return get_csr_bits(REG_INFO.tx2rx_outer_lpbk_prbs_stress_status_abist_api());	//CSR4[9:9]
}

ABIST_apiRegs&
ABIST_apiRegs::settx2rx_predriver_lpbk_clk_purity_wcdr_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.tx2rx_predriver_lpbk_clk_purity_wcdr_status_abist_api());	//CSR4[8:8]
	return *this;
}
uint
ABIST_apiRegs::gettx2rx_predriver_lpbk_clk_purity_wcdr_status_abist_api(){
	return get_csr_bits(REG_INFO.tx2rx_predriver_lpbk_clk_purity_wcdr_status_abist_api());	//CSR4[8:8]
}

ABIST_apiRegs&
ABIST_apiRegs::settx2rx_predriver_lpbk_prbs_stress_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.tx2rx_predriver_lpbk_prbs_stress_status_abist_api());	//CSR4[7:7]
	return *this;
}
uint
ABIST_apiRegs::gettx2rx_predriver_lpbk_prbs_stress_status_abist_api(){
	return get_csr_bits(REG_INFO.tx2rx_predriver_lpbk_prbs_stress_status_abist_api());	//CSR4[7:7]
}

ABIST_apiRegs&
ABIST_apiRegs::settx2rx_bumpdriver_lpbk_prbs_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.tx2rx_bumpdriver_lpbk_prbs_status_abist_api());	//CSR4[6:6]
	return *this;
}
uint
ABIST_apiRegs::gettx2rx_bumpdriver_lpbk_prbs_status_abist_api(){
	return get_csr_bits(REG_INFO.tx2rx_bumpdriver_lpbk_prbs_status_abist_api());	//CSR4[6:6]
}

ABIST_apiRegs&
ABIST_apiRegs::setcorner_sensor_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.corner_sensor_status_abist_api());	//CSR4[5:5]
	return *this;
}
uint
ABIST_apiRegs::getcorner_sensor_status_abist_api(){
	return get_csr_bits(REG_INFO.corner_sensor_status_abist_api());	//CSR4[5:5]
}

ABIST_apiRegs&
ABIST_apiRegs::setfir_dc_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.fir_dc_status_abist_api());	//CSR4[4:4]
	return *this;
}
uint
ABIST_apiRegs::getfir_dc_status_abist_api(){
	return get_csr_bits(REG_INFO.fir_dc_status_abist_api());	//CSR4[4:4]
}

ABIST_apiRegs&
ABIST_apiRegs::setatb_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.atb_status_abist_api());	//CSR4[3:3]
	return *this;
}
uint
ABIST_apiRegs::getatb_status_abist_api(){
	return get_csr_bits(REG_INFO.atb_status_abist_api());	//CSR4[3:3]
}

ABIST_apiRegs&
ABIST_apiRegs::setcalib_register_check_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.calib_register_check_status_abist_api());	//CSR4[2:2]
	return *this;
}
uint
ABIST_apiRegs::getcalib_register_check_status_abist_api(){
	return get_csr_bits(REG_INFO.calib_register_check_status_abist_api());	//CSR4[2:2]
}

ABIST_apiRegs&
ABIST_apiRegs::setctle_dc_gain_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.ctle_dc_gain_status_abist_api());	//CSR4[1:1]
	return *this;
}
uint
ABIST_apiRegs::getctle_dc_gain_status_abist_api(){
	return get_csr_bits(REG_INFO.ctle_dc_gain_status_abist_api());	//CSR4[1:1]
}

ABIST_apiRegs&
ABIST_apiRegs::setlatch_ofst_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.latch_ofst_status_abist_api());	//CSR4[0:0]
	return *this;
}
uint
ABIST_apiRegs::getlatch_ofst_status_abist_api(){
	return get_csr_bits(REG_INFO.latch_ofst_status_abist_api());	//CSR4[0:0]
}

ABIST_apiRegs&
ABIST_apiRegs::setalphagen_sweep_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.alphagen_sweep_status_abist_api());	//CSR5[15:15]
	return *this;
}
uint
ABIST_apiRegs::getalphagen_sweep_status_abist_api(){
	return get_csr_bits(REG_INFO.alphagen_sweep_status_abist_api());	//CSR5[15:15]
}

ABIST_apiRegs&
ABIST_apiRegs::setregulator_sweep_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.regulator_sweep_status_abist_api());	//CSR5[14:14]
	return *this;
}
uint
ABIST_apiRegs::getregulator_sweep_status_abist_api(){
	return get_csr_bits(REG_INFO.regulator_sweep_status_abist_api());	//CSR5[14:14]
}

ABIST_apiRegs&
ABIST_apiRegs::setdfe_idac_sweep_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.dfe_idac_sweep_status_abist_api());	//CSR5[13:13]
	return *this;
}
uint
ABIST_apiRegs::getdfe_idac_sweep_status_abist_api(){
	return get_csr_bits(REG_INFO.dfe_idac_sweep_status_abist_api());	//CSR5[13:13]
}

ABIST_apiRegs&
ABIST_apiRegs::setadc_stability_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.adc_stability_status_abist_api());	//CSR5[12:12]
	return *this;
}

uint
ABIST_apiRegs::getadc_stability_status_abist_api(){
	return get_csr_bits(REG_INFO.adc_stability_status_abist_api());	//CSR5[12:12]
}
ABIST_apiRegs&
ABIST_apiRegs::setdlos_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.dlos_status_abist_api());	//CSR5[11:11]
	return *this;
}
uint
ABIST_apiRegs::getdlos_status_abist_api(){
	return get_csr_bits(REG_INFO.dlos_status_abist_api());	//CSR5[11:11]
}

ABIST_apiRegs&
ABIST_apiRegs::setcomparator_status_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.comparator_status_abist_api());	//CSR5[10:10]
	return *this;
}
uint
ABIST_apiRegs::getcomparator_status_abist_api(){
	return get_csr_bits(REG_INFO.comparator_status_abist_api());	//CSR5[10:10]
}

ABIST_apiRegs&
ABIST_apiRegs::setabist_status1_spare9to0(uint val){
	fill_csr_bits(val,REG_INFO.abist_status1_spare9to0());	//CSR5[9:0]
	return *this;
}
uint
ABIST_apiRegs::getabist_status1_spare9to0(){
	return get_csr_bits(REG_INFO.abist_status1_spare9to0());	//CSR5[9:0]
}

ABIST_apiRegs&
ABIST_apiRegs::settop_fsm_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.top_fsm_abist_api());	//CSR6[15:8]
	return *this;
}
uint
ABIST_apiRegs::gettop_fsm_abist_api(){
	return get_csr_bits(REG_INFO.top_fsm_abist_api());	//CSR6[15:8]
}

ABIST_apiRegs&
ABIST_apiRegs::setsub0_fsm_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.sub0_fsm_abist_api());	//CSR6[7:0]
	return *this;
}
uint
ABIST_apiRegs::getsub0_fsm_abist_api(){
	return get_csr_bits(REG_INFO.sub0_fsm_abist_api());	//CSR6[7:0]
}

ABIST_apiRegs&
ABIST_apiRegs::setsub1_fsm_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.sub1_fsm_abist_api());	//CSR7[15:8]
	return *this;
}
uint
ABIST_apiRegs::getsub1_fsm_abist_api(){
	return get_csr_bits(REG_INFO.sub1_fsm_abist_api());	//CSR7[15:8]
}

ABIST_apiRegs&
ABIST_apiRegs::setsub2_fsm_abist_api(uint val){
	fill_csr_bits(val,REG_INFO.sub2_fsm_abist_api());	//CSR7[7:0]
	return *this;
}
uint
ABIST_apiRegs::getsub2_fsm_abist_api(){
	return get_csr_bits(REG_INFO.sub2_fsm_abist_api());	//CSR7[7:0]
}

E_HILINK_REGISTER_TYPE ABIST_apiRegs::getType()
{
	return HILINK_PERMACRO_REGISTER;
}
