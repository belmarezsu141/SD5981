#include <HILINK_DRIVE/HiLink_CS_apiRegs.h>

#include <iostream>
using namespace std;
CS_apiRegs::CS_apiRegs() {
	// TODO Auto-generated constructor stub
	for(int i=0;i<CS_API_CSR_NUM;i++){
		csr[i]=0;
	}
	sliceID=0;
	macroID=0;
	broadcast=false;
	reset_csr_verify();
}

CS_apiRegs::~CS_apiRegs() {}

bool
CS_apiRegs::get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos){
	if(csrIndex>=CS_API_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	return REG_INFO.get_reg_infos(csrIndex,reg_infos);
}

CS_apiRegs&
CS_apiRegs::getInstance(){
	static CS_apiRegs theInstance;
	return theInstance;
}

uint
CS_apiRegs::get_HILINK_MAX_LANE_NUM(){
	//TODO: add your code for CSR Address mapping
	return 1;
}

uint
CS_apiRegs::getAddressMapToHiLink(int csrIndex){
	if(csrIndex>=CS_API_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	//TODO: add your code for CSR Address mapping
	uint retAddress = 0;
	retAddress = 0x1FFFE -0xC*2 + csrIndex*2;
	return retAddress;
}


uint&
CS_apiRegs::get_csr(uint csrIndex){
	if(csrIndex>=CS_API_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	return csr[csrIndex];
}

void
CS_apiRegs::get_default_MacroLaneID(T_MacroLaneID& id){
	//TODO: add your code for CSR Address mapping
	id.MacroID=macroID;
	id.LaneID=sliceID;
}

uint
CS_apiRegs::getCSRCount(){
	return CS_API_CSR_NUM;
}

string
CS_apiRegs::getName(){
	return "CS_API";
}

///////////////////////////////////////////////////////////////////////////


	/// CS Calibration enable, used with cs calibration bypass control
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::cs_calib_en_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{0,"cs_calib_en_api",15,15}
	};
	return reg;
}

	/// DEBUG - Halt after single step 
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::cs_haltsinglestep_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{0,"cs_haltsinglestep_api",14,14}
	};
	return reg;
}

	/// DEBUG - Halt after state change 
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::cs_haltstatechange_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{0,"cs_haltstatechange_api",13,13}
	};
	return reg;
}

	/// DEBUG - Halt all CS execution
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::cs_haltimmediately_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{0,"cs_haltimmediately_api",12,12}
	};
	return reg;
}

	/// The external pin value
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::core_clk_selext_pin_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{0,"core_clk_selext_pin_api",11,11}
	};
	return reg;
}

	/// The external pin value
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::core_clk_sel_pin_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{0,"core_clk_sel_pin_api",10,10}
	};
	return reg;
}

	/// The external pin value
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::lifeclk2dig_sel_pin_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{0,"lifeclk2dig_sel_pin_api",9,9}
	};
	return reg;
}

	/// simple calibration for re-doing calibration to save time. (ATE ONLY)
	/// 1: Wirte previous calibration results back to chip
	/// 0: disable
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::cs_write_back_ctrl_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{0,"cs_write_back_ctrl_api",8,8}
	};
	return reg;
}

	/// The index number of Dataslice on the north side of Clockslice.
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::ds_index_north_cs_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{0,"ds_index_north_cs_api",7,4}
	};
	return reg;
}

	/// Spare for CS control
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::cs_ctrl0_spare3to0(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{0,"cs_ctrl0_spare3to0",3,0}
	};
	return reg;
}

	/// Frequency of refclk0 in MHz multiply by 100
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::refclk0_freqm100_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{1,"refclk0_freqm100_api",15,0}
	};
	return reg;
}

	/// Frequency of refclk1 in MHz multiply by 100
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::refclk1_freqm100_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{2,"refclk1_freqm100_api",15,0}
	};
	return reg;
}

	/// Spare for CS control
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::cs_ctrl3_spare15to15(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{3,"cs_ctrl3_spare15to15",15,15}
	};
	return reg;
}

	/// CS re-calibration enable, active high and will be self clear after calibration done.
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::cs_recalib_en_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{3,"cs_recalib_en_api",14,14}
	};
	return reg;
}

	/// calibration bypass control.  0:not bypass   1:bypass 
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll1vcodivvregcalbypass_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{3,"pll1vcodivvregcalbypass_api",13,13}
	};
	return reg;
}

	/// calibration bypass control.  0:not bypass   1:bypass 
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll1cpvrefcalbypass_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{3,"pll1cpvrefcalbypass_api",12,12}
	};
	return reg;
}

	/// calibration bypass control.  0:not bypass   1:bypass 
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll1dlfvregcalbypass_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{3,"pll1dlfvregcalbypass_api",11,11}
	};
	return reg;
}

	/// calibration bypass control.  0:not bypass   1:bypass 
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll1pllvregcalbypass_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{3,"pll1pllvregcalbypass_api",10,10}
	};
	return reg;
}

	/// calibration bypass control.  0:not bypass   1:bypass 
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll1vcocalbypass_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{3,"pll1vcocalbypass_api",9,9}
	};
	return reg;
}

	/// calibration bypass control.  0:not bypass   1:bypass 
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll0vcodivvregcalbypass_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{3,"pll0vcodivvregcalbypass_api",8,8}
	};
	return reg;
}

	/// calibration bypass control.  0:not bypass   1:bypass 
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll0cpvrefcalbypass_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{3,"pll0cpvrefcalbypass_api",7,7}
	};
	return reg;
}

	/// calibration bypass control.  0:not bypass   1:bypass 
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll0dlfvregcalbypass_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{3,"pll0dlfvregcalbypass_api",6,6}
	};
	return reg;
}

	/// calibration bypass control.  0:not bypass   1:bypass 
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll0pllvregcalbypass_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{3,"pll0pllvregcalbypass_api",5,5}
	};
	return reg;
}

	/// calibration bypass control.  0:not bypass   1:bypass 
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll0vcocalbypass_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{3,"pll0vcocalbypass_api",4,4}
	};
	return reg;
}

	/// calibration bypass control.  0:not bypass   1:bypass 
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::csvrefgencalbypass_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{3,"csvrefgencalbypass_api",3,3}
	};
	return reg;
}

	/// calibration bypass control.  0:not bypass   1:bypass 
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::csrxtermcalbypass_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{3,"csrxtermcalbypass_api",2,2}
	};
	return reg;
}

	/// calibration bypass control.  0:not bypass   1:bypass 
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::csbandgapcalbypass_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{3,"csbandgapcalbypass_api",1,1}
	};
	return reg;
}

	/// calibration bypass control.  0:not bypass   1:bypass 
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::csgetdpminfobypass_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{3,"csgetdpminfobypass_api",0,0}
	};
	return reg;
}

	/// cs dpm enable. 1:enable  0:disable
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll1vcoitank_dpm_en_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{4,"pll1vcoitank_dpm_en_api",15,15}
	};
	return reg;
}

	/// cs dpm enable. 1:enable  0:disable
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll0vcoitank_dpm_en_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{4,"pll0vcoitank_dpm_en_api",14,14}
	};
	return reg;
}

	/// cs dpm enable. 1:enable  0:disable
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll1vcodivvreg_dpm_en_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{4,"pll1vcodivvreg_dpm_en_api",13,13}
	};
	return reg;
}

	/// cs dpm enable. 1:enable  0:disable
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll1cpvref_dpm_en_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{4,"pll1cpvref_dpm_en_api",12,12}
	};
	return reg;
}

	/// cs dpm enable. 1:enable  0:disable
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll1pllvreg_dpm_en_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{4,"pll1pllvreg_dpm_en_api",11,11}
	};
	return reg;
}

	/// cs dpm enable. 1:enable  0:disable
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll1dlfvreg_dpm_en_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{4,"pll1dlfvreg_dpm_en_api",10,10}
	};
	return reg;
}

	/// cs dpm enable. 1:enable  0:disable
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll0vcodivvreg_dpm_en_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{4,"pll0vcodivvreg_dpm_en_api",9,9}
	};
	return reg;
}

	/// cs dpm enable. 1:enable  0:disable
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll0cpvref_dpm_en_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{4,"pll0cpvref_dpm_en_api",8,8}
	};
	return reg;
}

	/// cs dpm enable. 1:enable  0:disable
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll0pllvreg_dpm_en_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{4,"pll0pllvreg_dpm_en_api",7,7}
	};
	return reg;
}

	/// cs dpm enable. 1:enable  0:disable
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll0dlfvreg_dpm_en_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{4,"pll0dlfvreg_dpm_en_api",6,6}
	};
	return reg;
}

	/// cs dpm enable. 1:enable  0:disable
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::temprature_dpm_en_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{4,"temprature_dpm_en_api",5,5}
	};
	return reg;
}

	/// cs dpm enable. 1:enable  0:disable
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pmoscornre_dpm_en_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{4,"pmoscornre_dpm_en_api",4,4}
	};
	return reg;
}

	/// cs dpm enable. 1:enable  0:disable
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::nmoscornre_dpm_en_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{4,"nmoscornre_dpm_en_api",3,3}
	};
	return reg;
}

	/// cs dpm enable. 1:enable  0:disable
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::cs_dpm_en_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{4,"cs_dpm_en_api",2,2}
	};
	return reg;
}

	/// 0:not switch to mclk at the end of cs calibration.
	/// 1:switch to mclk automatically
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::coreclk_sel_en_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{4,"coreclk_sel_en_api",1,1}
	};
	return reg;
}

	/// Spare for CS control
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::cs_ctrl4_spare0to0(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{4,"cs_ctrl4_spare0to0",0,0}
	};
	return reg;
}


const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll0dlfvreg_ofst_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{5,"pll0dlfvreg_ofst_api",15,12}
	};
	return reg;
}


const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll0pllvreg_ofst_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{5,"pll0pllvreg_ofst_api",11,8}
	};
	return reg;
}


const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll0vcodivvreg_ofst_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{5,"pll0vcodivvreg_ofst_api",7,4}
	};
	return reg;
}


const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll0itankvreg_ofst_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{5,"pll0itankvreg_ofst_api",3,0}
	};
	return reg;
}


const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll1dlfvreg_ofst_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{6,"pll1dlfvreg_ofst_api",15,12}
	};
	return reg;
}


const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll1pllvreg_ofst_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{6,"pll1pllvreg_ofst_api",11,8}
	};
	return reg;
}


const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll1vcodivvreg_ofst_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{6,"pll1vcodivvreg_ofst_api",7,4}
	};
	return reg;
}


const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::pll1itankvreg_ofst_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{6,"pll1itankvreg_ofst_api",3,0}
	};
	return reg;
}


const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::dsclkvreg_ofst_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{7,"dsclkvreg_ofst_api",15,12}
	};
	return reg;
}


const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::txpredrvreg_ofst_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{7,"txpredrvreg_ofst_api",11,8}
	};
	return reg;
}

const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::rxdatavreg_ofst_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{7,"rxdatavreg_ofst_api",7,4}
	};
	return reg;
}

const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::cs_ctrl7_spare3to1(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{7,"cs_ctrl7_spare3to1",3,1}
	};
	return reg;
}

const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::regulator_offset_en_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{7,"regulator_offset_en_api",0,0}
	};
	return reg;
}

	/// CS Top FSM state
	/// 0 = Clockslice calibration FSM initial
	/// 1 = Clockslice calibration handling
	/// 3 = Clockslice calibration done
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::cs_top_fsm_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{8,"cs_top_fsm_api",15,8}
	};
	return reg;
}

	/// cs sub fsm state
	/// 0 = CS calibration initial 
	/// 1 = SS bandgap buffer offset calibration initial 
	/// 2 = SS bandgap buffer offset calibration excusive 
	/// 3 = SS bandgap buffer offset calibration adjustment 
	/// 4 = SS rpoly resistance calibration initial 
	/// 5 = SS rpoly resistance calibration excusive 
	/// 6 = SS rpoly resistance calibration adjustment 
	/// 7 = Get temperature 
	/// 8 = CS comparator vrefgen offset calibration initial 
	/// 9 = CS comparator vrefgen offset calibration excusive 
	/// 10 = CS comparator vrefgen offset calibration adjustment 
	/// 11 = CS regulators calibration initial 
	/// 12 = CS regulators calibration excusive 
	/// 13 = CS regulators calibration adjustment 
	/// 14 = CS PLL0 VCO calibration 
	/// 15 = CS PLL1 VCO calibration 
	/// 16 = CS calibration adjustment 
	/// 16 = CS calibration done
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::cs_sub0_fsm_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{8,"cs_sub0_fsm_api",7,0}
	};
	return reg;
}

	/// CS sub-sub FMS state
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::cs_sub1_fsm_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{9,"cs_sub1_fsm_api",15,8}
	};
	return reg;
}

	/// CS sub-sub-sub FSM state
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::cs_sub2_fsm_api(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{9,"cs_sub2_fsm_api",7,0}
	};
	return reg;
}

	/// spare for CS status
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::cs_stat2_spare15to0(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{10,"cs_stat2_spare15to0",15,0}
	};
	return reg;
}

	/// spare for CS status
const T_REG_INFO_EX&
CS_apiRegs::_REG_INFO::cs_stat3_spare15to0(){
	const static T_REG_INFO_EX reg={CS_apiRegs::getInstance(),
		{11,"cs_stat3_spare15to0",15,0}
	};
	return reg;
}
bool
CS_apiRegs::_REG_INFO::get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos){
	reg_infos.clear();
	switch(csr){
		case 0:
			reg_infos.push_back(cs_calib_en_api().reg_info);
			reg_infos.push_back(cs_haltsinglestep_api().reg_info);
			reg_infos.push_back(cs_haltstatechange_api().reg_info);
			reg_infos.push_back(cs_haltimmediately_api().reg_info);
			reg_infos.push_back(core_clk_selext_pin_api().reg_info);
			reg_infos.push_back(core_clk_sel_pin_api().reg_info);
			reg_infos.push_back(lifeclk2dig_sel_pin_api().reg_info);
			reg_infos.push_back(cs_write_back_ctrl_api().reg_info);
			reg_infos.push_back(ds_index_north_cs_api().reg_info);
			reg_infos.push_back(cs_ctrl0_spare3to0().reg_info);
			break;
		case 1:
			reg_infos.push_back(refclk0_freqm100_api().reg_info);
			break;
		case 2:
			reg_infos.push_back(refclk1_freqm100_api().reg_info);
			break;
		case 3:
			reg_infos.push_back(cs_ctrl3_spare15to15().reg_info);
			reg_infos.push_back(cs_recalib_en_api().reg_info);
			reg_infos.push_back(pll1vcodivvregcalbypass_api().reg_info);
			reg_infos.push_back(pll1cpvrefcalbypass_api().reg_info);
			reg_infos.push_back(pll1dlfvregcalbypass_api().reg_info);
			reg_infos.push_back(pll1pllvregcalbypass_api().reg_info);
			reg_infos.push_back(pll1vcocalbypass_api().reg_info);
			reg_infos.push_back(pll0vcodivvregcalbypass_api().reg_info);
			reg_infos.push_back(pll0cpvrefcalbypass_api().reg_info);
			reg_infos.push_back(pll0dlfvregcalbypass_api().reg_info);
			reg_infos.push_back(pll0pllvregcalbypass_api().reg_info);
			reg_infos.push_back(pll0vcocalbypass_api().reg_info);
			reg_infos.push_back(csvrefgencalbypass_api().reg_info);
			reg_infos.push_back(csrxtermcalbypass_api().reg_info);
			reg_infos.push_back(csbandgapcalbypass_api().reg_info);
			reg_infos.push_back(csgetdpminfobypass_api().reg_info);
			break;
		case 4:
			reg_infos.push_back(pll1vcoitank_dpm_en_api().reg_info);
			reg_infos.push_back(pll0vcoitank_dpm_en_api().reg_info);
			reg_infos.push_back(pll1vcodivvreg_dpm_en_api().reg_info);
			reg_infos.push_back(pll1cpvref_dpm_en_api().reg_info);
			reg_infos.push_back(pll1pllvreg_dpm_en_api().reg_info);
			reg_infos.push_back(pll1dlfvreg_dpm_en_api().reg_info);
			reg_infos.push_back(pll0vcodivvreg_dpm_en_api().reg_info);
			reg_infos.push_back(pll0cpvref_dpm_en_api().reg_info);
			reg_infos.push_back(pll0pllvreg_dpm_en_api().reg_info);
			reg_infos.push_back(pll0dlfvreg_dpm_en_api().reg_info);
			reg_infos.push_back(temprature_dpm_en_api().reg_info);
			reg_infos.push_back(pmoscornre_dpm_en_api().reg_info);
			reg_infos.push_back(nmoscornre_dpm_en_api().reg_info);
			reg_infos.push_back(cs_dpm_en_api().reg_info);
			reg_infos.push_back(coreclk_sel_en_api().reg_info);
			reg_infos.push_back(cs_ctrl4_spare0to0().reg_info);
			break;
		case 5:
			reg_infos.push_back(pll0dlfvreg_ofst_api().reg_info);
			reg_infos.push_back(pll0pllvreg_ofst_api().reg_info);
			reg_infos.push_back(pll0vcodivvreg_ofst_api().reg_info);
			reg_infos.push_back(pll0itankvreg_ofst_api().reg_info);
			break;
		case 6:
			reg_infos.push_back(pll1dlfvreg_ofst_api().reg_info);
			reg_infos.push_back(pll1pllvreg_ofst_api().reg_info);
			reg_infos.push_back(pll1vcodivvreg_ofst_api().reg_info);
			reg_infos.push_back(pll1itankvreg_ofst_api().reg_info);
			break;
		case 7:
			reg_infos.push_back(dsclkvreg_ofst_api().reg_info);
			reg_infos.push_back(txpredrvreg_ofst_api().reg_info);
			reg_infos.push_back(rxdatavreg_ofst_api().reg_info);
			reg_infos.push_back(cs_ctrl7_spare3to1().reg_info);
			reg_infos.push_back(regulator_offset_en_api().reg_info);
			break;
		case 8:
			reg_infos.push_back(cs_top_fsm_api().reg_info);
			reg_infos.push_back(cs_sub0_fsm_api().reg_info);
			break;
		case 9:
			reg_infos.push_back(cs_sub1_fsm_api().reg_info);
			reg_infos.push_back(cs_sub2_fsm_api().reg_info);
			break;
		case 10:
			reg_infos.push_back(cs_stat2_spare15to0().reg_info);
			break;
		case 11:
			reg_infos.push_back(cs_stat3_spare15to0().reg_info);
			break;
		default:
			break;
	}
	return (reg_infos.size()>0);
}


CS_apiRegs&
CS_apiRegs::setcs_calib_en_api(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_en_api());	//CSR0[15:15]
	return *this;
}
uint
CS_apiRegs::getcs_calib_en_api(){
	return get_csr_bits(REG_INFO.cs_calib_en_api());	//CSR0[15:15]
}

CS_apiRegs&
CS_apiRegs::setcs_haltsinglestep_api(uint val){
	fill_csr_bits(val,REG_INFO.cs_haltsinglestep_api());	//CSR0[14:14]
	return *this;
}
uint
CS_apiRegs::getcs_haltsinglestep_api(){
	return get_csr_bits(REG_INFO.cs_haltsinglestep_api());	//CSR0[14:14]
}

CS_apiRegs&
CS_apiRegs::setcs_haltstatechange_api(uint val){
	fill_csr_bits(val,REG_INFO.cs_haltstatechange_api());	//CSR0[13:13]
	return *this;
}
uint
CS_apiRegs::getcs_haltstatechange_api(){
	return get_csr_bits(REG_INFO.cs_haltstatechange_api());	//CSR0[13:13]
}

CS_apiRegs&
CS_apiRegs::setcs_haltimmediately_api(uint val){
	fill_csr_bits(val,REG_INFO.cs_haltimmediately_api());	//CSR0[12:12]
	return *this;
}
uint
CS_apiRegs::getcs_haltimmediately_api(){
	return get_csr_bits(REG_INFO.cs_haltimmediately_api());	//CSR0[12:12]
}

CS_apiRegs&
CS_apiRegs::setcore_clk_selext_pin_api(uint val){
	fill_csr_bits(val,REG_INFO.core_clk_selext_pin_api());	//CSR0[11:11]
	return *this;
}
uint
CS_apiRegs::getcore_clk_selext_pin_api(){
	return get_csr_bits(REG_INFO.core_clk_selext_pin_api());	//CSR0[11:11]
}

CS_apiRegs&
CS_apiRegs::setcore_clk_sel_pin_api(uint val){
	fill_csr_bits(val,REG_INFO.core_clk_sel_pin_api());	//CSR0[10:10]
	return *this;
}
uint
CS_apiRegs::getcore_clk_sel_pin_api(){
	return get_csr_bits(REG_INFO.core_clk_sel_pin_api());	//CSR0[10:10]
}

CS_apiRegs&
CS_apiRegs::setlifeclk2dig_sel_pin_api(uint val){
	fill_csr_bits(val,REG_INFO.lifeclk2dig_sel_pin_api());	//CSR0[9:9]
	return *this;
}
uint
CS_apiRegs::getlifeclk2dig_sel_pin_api(){
	return get_csr_bits(REG_INFO.lifeclk2dig_sel_pin_api());	//CSR0[9:9]
}

CS_apiRegs&
CS_apiRegs::setcs_write_back_ctrl_api(uint val){
	fill_csr_bits(val,REG_INFO.cs_write_back_ctrl_api());	//CSR0[8:8]
	return *this;
}
uint
CS_apiRegs::getcs_write_back_ctrl_api(){
	return get_csr_bits(REG_INFO.cs_write_back_ctrl_api());	//CSR0[8:8]
}

CS_apiRegs&
CS_apiRegs::setds_index_north_cs_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_index_north_cs_api());	//CSR0[7:4]
	return *this;
}
uint
CS_apiRegs::getds_index_north_cs_api(){
	return get_csr_bits(REG_INFO.ds_index_north_cs_api());	//CSR0[7:4]
}

CS_apiRegs&
CS_apiRegs::setcs_ctrl0_spare3to0(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl0_spare3to0());	//CSR0[3:0]
	return *this;
}
uint
CS_apiRegs::getcs_ctrl0_spare3to0(){
	return get_csr_bits(REG_INFO.cs_ctrl0_spare3to0());	//CSR0[3:0]
}

CS_apiRegs&
CS_apiRegs::setrefclk0_freqm100_api(uint val){
	fill_csr_bits(val,REG_INFO.refclk0_freqm100_api());	//CSR1[15:0]
	return *this;
}
uint
CS_apiRegs::getrefclk0_freqm100_api(){
	return get_csr_bits(REG_INFO.refclk0_freqm100_api());	//CSR1[15:0]
}

CS_apiRegs&
CS_apiRegs::setrefclk1_freqm100_api(uint val){
	fill_csr_bits(val,REG_INFO.refclk1_freqm100_api());	//CSR2[15:0]
	return *this;
}
uint
CS_apiRegs::getrefclk1_freqm100_api(){
	return get_csr_bits(REG_INFO.refclk1_freqm100_api());	//CSR2[15:0]
}

CS_apiRegs&
CS_apiRegs::setcs_ctrl3_spare15to15(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl3_spare15to15());	//CSR3[15:15]
	return *this;
}
uint
CS_apiRegs::getcs_ctrl3_spare15to15(){
	return get_csr_bits(REG_INFO.cs_ctrl3_spare15to15());	//CSR3[15:15]
}

CS_apiRegs&
CS_apiRegs::setcs_recalib_en_api(uint val){
	fill_csr_bits(val,REG_INFO.cs_recalib_en_api());	//CSR3[14:14]
	return *this;
}
uint
CS_apiRegs::getcs_recalib_en_api(){
	return get_csr_bits(REG_INFO.cs_recalib_en_api());	//CSR3[14:14]
}

CS_apiRegs&
CS_apiRegs::setpll1vcodivvregcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcodivvregcalbypass_api());	//CSR3[13:13]
	return *this;
}
uint
CS_apiRegs::getpll1vcodivvregcalbypass_api(){
	return get_csr_bits(REG_INFO.pll1vcodivvregcalbypass_api());	//CSR3[13:13]
}

CS_apiRegs&
CS_apiRegs::setpll1cpvrefcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.pll1cpvrefcalbypass_api());	//CSR3[12:12]
	return *this;
}
uint
CS_apiRegs::getpll1cpvrefcalbypass_api(){
	return get_csr_bits(REG_INFO.pll1cpvrefcalbypass_api());	//CSR3[12:12]
}

CS_apiRegs&
CS_apiRegs::setpll1dlfvregcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.pll1dlfvregcalbypass_api());	//CSR3[11:11]
	return *this;
}
uint
CS_apiRegs::getpll1dlfvregcalbypass_api(){
	return get_csr_bits(REG_INFO.pll1dlfvregcalbypass_api());	//CSR3[11:11]
}

CS_apiRegs&
CS_apiRegs::setpll1pllvregcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.pll1pllvregcalbypass_api());	//CSR3[10:10]
	return *this;
}
uint
CS_apiRegs::getpll1pllvregcalbypass_api(){
	return get_csr_bits(REG_INFO.pll1pllvregcalbypass_api());	//CSR3[10:10]
}

CS_apiRegs&
CS_apiRegs::setpll1vcocalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcocalbypass_api());	//CSR3[9:9]
	return *this;
}
uint
CS_apiRegs::getpll1vcocalbypass_api(){
	return get_csr_bits(REG_INFO.pll1vcocalbypass_api());	//CSR3[9:9]
}

CS_apiRegs&
CS_apiRegs::setpll0vcodivvregcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcodivvregcalbypass_api());	//CSR3[8:8]
	return *this;
}
uint
CS_apiRegs::getpll0vcodivvregcalbypass_api(){
	return get_csr_bits(REG_INFO.pll0vcodivvregcalbypass_api());	//CSR3[8:8]
}

CS_apiRegs&
CS_apiRegs::setpll0cpvrefcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.pll0cpvrefcalbypass_api());	//CSR3[7:7]
	return *this;
}
uint
CS_apiRegs::getpll0cpvrefcalbypass_api(){
	return get_csr_bits(REG_INFO.pll0cpvrefcalbypass_api());	//CSR3[7:7]
}

CS_apiRegs&
CS_apiRegs::setpll0dlfvregcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.pll0dlfvregcalbypass_api());	//CSR3[6:6]
	return *this;
}
uint
CS_apiRegs::getpll0dlfvregcalbypass_api(){
	return get_csr_bits(REG_INFO.pll0dlfvregcalbypass_api());	//CSR3[6:6]
}

CS_apiRegs&
CS_apiRegs::setpll0pllvregcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.pll0pllvregcalbypass_api());	//CSR3[5:5]
	return *this;
}
uint
CS_apiRegs::getpll0pllvregcalbypass_api(){
	return get_csr_bits(REG_INFO.pll0pllvregcalbypass_api());	//CSR3[5:5]
}

CS_apiRegs&
CS_apiRegs::setpll0vcocalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcocalbypass_api());	//CSR3[4:4]
	return *this;
}
uint
CS_apiRegs::getpll0vcocalbypass_api(){
	return get_csr_bits(REG_INFO.pll0vcocalbypass_api());	//CSR3[4:4]
}

CS_apiRegs&
CS_apiRegs::setcsvrefgencalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.csvrefgencalbypass_api());	//CSR3[3:3]
	return *this;
}
uint
CS_apiRegs::getcsvrefgencalbypass_api(){
	return get_csr_bits(REG_INFO.csvrefgencalbypass_api());	//CSR3[3:3]
}

CS_apiRegs&
CS_apiRegs::setcsrxtermcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.csrxtermcalbypass_api());	//CSR3[2:2]
	return *this;
}
uint
CS_apiRegs::getcsrxtermcalbypass_api(){
	return get_csr_bits(REG_INFO.csrxtermcalbypass_api());	//CSR3[2:2]
}

CS_apiRegs&
CS_apiRegs::setcsbandgapcalbypass_api(uint val){
	fill_csr_bits(val,REG_INFO.csbandgapcalbypass_api());	//CSR3[1:1]
	return *this;
}
uint
CS_apiRegs::getcsbandgapcalbypass_api(){
	return get_csr_bits(REG_INFO.csbandgapcalbypass_api());	//CSR3[1:1]
}

CS_apiRegs&
CS_apiRegs::setcsgetdpminfobypass_api(uint val){
	fill_csr_bits(val,REG_INFO.csgetdpminfobypass_api());	//CSR3[0:0]
	return *this;
}
uint
CS_apiRegs::getcsgetdpminfobypass_api(){
	return get_csr_bits(REG_INFO.csgetdpminfobypass_api());	//CSR3[0:0]
}

CS_apiRegs&
CS_apiRegs::setpll1vcoitank_dpm_en_api(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcoitank_dpm_en_api());	//CSR4[15:15]
	return *this;
}
uint
CS_apiRegs::getpll1vcoitank_dpm_en_api(){
	return get_csr_bits(REG_INFO.pll1vcoitank_dpm_en_api());	//CSR4[15:15]
}

CS_apiRegs&
CS_apiRegs::setpll0vcoitank_dpm_en_api(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcoitank_dpm_en_api());	//CSR4[14:14]
	return *this;
}
uint
CS_apiRegs::getpll0vcoitank_dpm_en_api(){
	return get_csr_bits(REG_INFO.pll0vcoitank_dpm_en_api());	//CSR4[14:14]
}

CS_apiRegs&
CS_apiRegs::setpll1vcodivvreg_dpm_en_api(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcodivvreg_dpm_en_api());	//CSR4[13:13]
	return *this;
}
uint
CS_apiRegs::getpll1vcodivvreg_dpm_en_api(){
	return get_csr_bits(REG_INFO.pll1vcodivvreg_dpm_en_api());	//CSR4[13:13]
}

CS_apiRegs&
CS_apiRegs::setpll1cpvref_dpm_en_api(uint val){
	fill_csr_bits(val,REG_INFO.pll1cpvref_dpm_en_api());	//CSR4[12:12]
	return *this;
}
uint
CS_apiRegs::getpll1cpvref_dpm_en_api(){
	return get_csr_bits(REG_INFO.pll1cpvref_dpm_en_api());	//CSR4[12:12]
}

CS_apiRegs&
CS_apiRegs::setpll1pllvreg_dpm_en_api(uint val){
	fill_csr_bits(val,REG_INFO.pll1pllvreg_dpm_en_api());	//CSR4[11:11]
	return *this;
}
uint
CS_apiRegs::getpll1pllvreg_dpm_en_api(){
	return get_csr_bits(REG_INFO.pll1pllvreg_dpm_en_api());	//CSR4[11:11]
}

CS_apiRegs&
CS_apiRegs::setpll1dlfvreg_dpm_en_api(uint val){
	fill_csr_bits(val,REG_INFO.pll1dlfvreg_dpm_en_api());	//CSR4[10:10]
	return *this;
}
uint
CS_apiRegs::getpll1dlfvreg_dpm_en_api(){
	return get_csr_bits(REG_INFO.pll1dlfvreg_dpm_en_api());	//CSR4[10:10]
}

CS_apiRegs&
CS_apiRegs::setpll0vcodivvreg_dpm_en_api(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcodivvreg_dpm_en_api());	//CSR4[9:9]
	return *this;
}
uint
CS_apiRegs::getpll0vcodivvreg_dpm_en_api(){
	return get_csr_bits(REG_INFO.pll0vcodivvreg_dpm_en_api());	//CSR4[9:9]
}

CS_apiRegs&
CS_apiRegs::setpll0cpvref_dpm_en_api(uint val){
	fill_csr_bits(val,REG_INFO.pll0cpvref_dpm_en_api());	//CSR4[8:8]
	return *this;
}
uint
CS_apiRegs::getpll0cpvref_dpm_en_api(){
	return get_csr_bits(REG_INFO.pll0cpvref_dpm_en_api());	//CSR4[8:8]
}

CS_apiRegs&
CS_apiRegs::setpll0pllvreg_dpm_en_api(uint val){
	fill_csr_bits(val,REG_INFO.pll0pllvreg_dpm_en_api());	//CSR4[7:7]
	return *this;
}
uint
CS_apiRegs::getpll0pllvreg_dpm_en_api(){
	return get_csr_bits(REG_INFO.pll0pllvreg_dpm_en_api());	//CSR4[7:7]
}

CS_apiRegs&
CS_apiRegs::setpll0dlfvreg_dpm_en_api(uint val){
	fill_csr_bits(val,REG_INFO.pll0dlfvreg_dpm_en_api());	//CSR4[6:6]
	return *this;
}
uint
CS_apiRegs::getpll0dlfvreg_dpm_en_api(){
	return get_csr_bits(REG_INFO.pll0dlfvreg_dpm_en_api());	//CSR4[6:6]
}

CS_apiRegs&
CS_apiRegs::settemprature_dpm_en_api(uint val){
	fill_csr_bits(val,REG_INFO.temprature_dpm_en_api());	//CSR4[5:5]
	return *this;
}
uint
CS_apiRegs::gettemprature_dpm_en_api(){
	return get_csr_bits(REG_INFO.temprature_dpm_en_api());	//CSR4[5:5]
}

CS_apiRegs&
CS_apiRegs::setpmoscornre_dpm_en_api(uint val){
	fill_csr_bits(val,REG_INFO.pmoscornre_dpm_en_api());	//CSR4[4:4]
	return *this;
}
uint
CS_apiRegs::getpmoscornre_dpm_en_api(){
	return get_csr_bits(REG_INFO.pmoscornre_dpm_en_api());	//CSR4[4:4]
}

CS_apiRegs&
CS_apiRegs::setnmoscornre_dpm_en_api(uint val){
	fill_csr_bits(val,REG_INFO.nmoscornre_dpm_en_api());	//CSR4[3:3]
	return *this;
}
uint
CS_apiRegs::getnmoscornre_dpm_en_api(){
	return get_csr_bits(REG_INFO.nmoscornre_dpm_en_api());	//CSR4[3:3]
}

CS_apiRegs&
CS_apiRegs::setcs_dpm_en_api(uint val){
	fill_csr_bits(val,REG_INFO.cs_dpm_en_api());	//CSR4[2:2]
	return *this;
}
uint
CS_apiRegs::getcs_dpm_en_api(){
	return get_csr_bits(REG_INFO.cs_dpm_en_api());	//CSR4[2:2]
}

CS_apiRegs&
CS_apiRegs::setcoreclk_sel_en_api(uint val){
	fill_csr_bits(val,REG_INFO.coreclk_sel_en_api());	//CSR4[1:1]
	return *this;
}
uint
CS_apiRegs::getcoreclk_sel_en_api(){
	return get_csr_bits(REG_INFO.coreclk_sel_en_api());	//CSR4[1:1]
}

CS_apiRegs&
CS_apiRegs::setcs_ctrl4_spare0to0(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl4_spare0to0());	//CSR4[0:0]
	return *this;
}
uint
CS_apiRegs::getcs_ctrl4_spare0to0(){
	return get_csr_bits(REG_INFO.cs_ctrl4_spare0to0());	//CSR4[0:0]
}

CS_apiRegs&
CS_apiRegs::setpll0dlfvreg_ofst_api(uint val){
	fill_csr_bits(val,REG_INFO.pll0dlfvreg_ofst_api());	//CSR5[15:12]
	return *this;
}
uint
CS_apiRegs::getpll0dlfvreg_ofst_api(){
	return get_csr_bits(REG_INFO.pll0dlfvreg_ofst_api());	//CSR5[15:12]
}

CS_apiRegs&
CS_apiRegs::setpll0pllvreg_ofst_api(uint val){
	fill_csr_bits(val,REG_INFO.pll0pllvreg_ofst_api());	//CSR5[11:8]
	return *this;
}
uint
CS_apiRegs::getpll0pllvreg_ofst_api(){
	return get_csr_bits(REG_INFO.pll0pllvreg_ofst_api());	//CSR5[11:8]
}

CS_apiRegs&
CS_apiRegs::setpll0vcodivvreg_ofst_api(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcodivvreg_ofst_api());	//CSR5[7:4]
	return *this;
}
uint
CS_apiRegs::getpll0vcodivvreg_ofst_api(){
	return get_csr_bits(REG_INFO.pll0vcodivvreg_ofst_api());	//CSR5[7:4]
}

CS_apiRegs&
CS_apiRegs::setpll0itankvreg_ofst_api(uint val){
	fill_csr_bits(val,REG_INFO.pll0itankvreg_ofst_api());	//CSR5[3:0]
	return *this;
}
uint
CS_apiRegs::getpll0itankvreg_ofst_api(){
	return get_csr_bits(REG_INFO.pll0itankvreg_ofst_api());	//CSR5[3:0]
}

CS_apiRegs&
CS_apiRegs::setpll1dlfvreg_ofst_api(uint val){
	fill_csr_bits(val,REG_INFO.pll1dlfvreg_ofst_api());	//CSR6[15:12]
	return *this;
}
uint
CS_apiRegs::getpll1dlfvreg_ofst_api(){
	return get_csr_bits(REG_INFO.pll1dlfvreg_ofst_api());	//CSR6[15:12]
}

CS_apiRegs&
CS_apiRegs::setpll1pllvreg_ofst_api(uint val){
	fill_csr_bits(val,REG_INFO.pll1pllvreg_ofst_api());	//CSR6[11:8]
	return *this;
}
uint
CS_apiRegs::getpll1pllvreg_ofst_api(){
	return get_csr_bits(REG_INFO.pll1pllvreg_ofst_api());	//CSR6[11:8]
}

CS_apiRegs&
CS_apiRegs::setpll1vcodivvreg_ofst_api(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcodivvreg_ofst_api());	//CSR6[7:4]
	return *this;
}
uint
CS_apiRegs::getpll1vcodivvreg_ofst_api(){
	return get_csr_bits(REG_INFO.pll1vcodivvreg_ofst_api());	//CSR6[7:4]
}

CS_apiRegs&
CS_apiRegs::setpll1itankvreg_ofst_api(uint val){
	fill_csr_bits(val,REG_INFO.pll1itankvreg_ofst_api());	//CSR6[3:0]
	return *this;
}
uint
CS_apiRegs::getpll1itankvreg_ofst_api(){
	return get_csr_bits(REG_INFO.pll1itankvreg_ofst_api());	//CSR6[3:0]
}

CS_apiRegs&
CS_apiRegs::setdsclkvreg_ofst_api(uint val){
	fill_csr_bits(val,REG_INFO.dsclkvreg_ofst_api());	//CSR7[15:12]
	return *this;
}
uint
CS_apiRegs::getdsclkvreg_ofst_api(){
	return get_csr_bits(REG_INFO.dsclkvreg_ofst_api());	//CSR7[15:12]
}

CS_apiRegs&
CS_apiRegs::settxpredrvreg_ofst_api(uint val){
	fill_csr_bits(val,REG_INFO.txpredrvreg_ofst_api());	//CSR7[11:8]
	return *this;
}
uint
CS_apiRegs::gettxpredrvreg_ofst_api(){
	return get_csr_bits(REG_INFO.txpredrvreg_ofst_api());	//CSR7[11:8]
}


CS_apiRegs&
CS_apiRegs::setrxdatavreg_ofst_api(uint val){
	fill_csr_bits(val,REG_INFO.rxdatavreg_ofst_api());	//CSR7[7:4]
	return *this;
}
uint
CS_apiRegs::getrxdatavreg_ofst_api(){
	return get_csr_bits(REG_INFO.rxdatavreg_ofst_api());	//CSR7[7:4]
}

CS_apiRegs&
CS_apiRegs::setcs_ctrl7_spare3to1(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl7_spare3to1());	//CSR7[3:1]
	return *this;
}
uint
CS_apiRegs::getcs_ctrl7_spare3to1(){
	return get_csr_bits(REG_INFO.cs_ctrl7_spare3to1());	//CSR7[3:1]
}


CS_apiRegs&
CS_apiRegs::setregulator_offset_en_api(uint val){
	fill_csr_bits(val,REG_INFO.regulator_offset_en_api());	//CSR7[0:0]
	return *this;
}
uint
CS_apiRegs::getregulator_offset_en_api(){
	return get_csr_bits(REG_INFO.regulator_offset_en_api());	//CSR7[0:0]
}

CS_apiRegs&
CS_apiRegs::setcs_top_fsm_api(uint val){
	fill_csr_bits(val,REG_INFO.cs_top_fsm_api());	//CSR8[15:8]
	return *this;
}
uint
CS_apiRegs::getcs_top_fsm_api(){
	return get_csr_bits(REG_INFO.cs_top_fsm_api());	//CSR8[15:8]
}

CS_apiRegs&
CS_apiRegs::setcs_sub0_fsm_api(uint val){
	fill_csr_bits(val,REG_INFO.cs_sub0_fsm_api());	//CSR8[7:0]
	return *this;
}
uint
CS_apiRegs::getcs_sub0_fsm_api(){
	return get_csr_bits(REG_INFO.cs_sub0_fsm_api());	//CSR8[7:0]
}

CS_apiRegs&
CS_apiRegs::setcs_sub1_fsm_api(uint val){
	fill_csr_bits(val,REG_INFO.cs_sub1_fsm_api());	//CSR9[15:8]
	return *this;
}
uint
CS_apiRegs::getcs_sub1_fsm_api(){
	return get_csr_bits(REG_INFO.cs_sub1_fsm_api());	//CSR9[15:8]
}

CS_apiRegs&
CS_apiRegs::setcs_sub2_fsm_api(uint val){
	fill_csr_bits(val,REG_INFO.cs_sub2_fsm_api());	//CSR9[7:0]
	return *this;
}
uint
CS_apiRegs::getcs_sub2_fsm_api(){
	return get_csr_bits(REG_INFO.cs_sub2_fsm_api());	//CSR9[7:0]
}

CS_apiRegs&
CS_apiRegs::setcs_stat2_spare15to0(uint val){
	fill_csr_bits(val,REG_INFO.cs_stat2_spare15to0());	//CSR10[15:0]
	return *this;
}
uint
CS_apiRegs::getcs_stat2_spare15to0(){
	return get_csr_bits(REG_INFO.cs_stat2_spare15to0());	//CSR10[15:0]
}

CS_apiRegs&
CS_apiRegs::setcs_stat3_spare15to0(uint val){
	fill_csr_bits(val,REG_INFO.cs_stat3_spare15to0());	//CSR11[15:0]
	return *this;
}
uint
CS_apiRegs::getcs_stat3_spare15to0(){
	return get_csr_bits(REG_INFO.cs_stat3_spare15to0());	//CSR11[15:0]
}
E_HILINK_REGISTER_TYPE CS_apiRegs::getType()
{
	return HILINK_PERMACRO_REGISTER;
}
