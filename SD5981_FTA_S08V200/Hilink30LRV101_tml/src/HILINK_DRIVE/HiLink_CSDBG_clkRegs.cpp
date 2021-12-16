#include <HILINK_DRIVE/HiLink_CSDBG_clkRegs.h>

#include <iostream>
using namespace std;
CSDBG_clkRegs::CSDBG_clkRegs() {
	// TODO Auto-generated constructor stub
	for(int i=0;i<CSDBG_CLK_CSR_NUM;i++){
		csr[i]=0;
	}
	sliceID=0;
	macroID=0;
	broadcast=false;
	reset_csr_verify();
}

CSDBG_clkRegs::~CSDBG_clkRegs() {}

bool
CSDBG_clkRegs::get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos){
	if(csrIndex>=CSDBG_CLK_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	return REG_INFO.get_reg_infos(csrIndex,reg_infos);
}

CSDBG_clkRegs&
CSDBG_clkRegs::getInstance(){
	static CSDBG_clkRegs theInstance;
	return theInstance;
}

uint
CSDBG_clkRegs::get_HILINK_MAX_LANE_NUM(){
	//TODO: add your code for CSR Address mapping
	return 1;
}

uint
CSDBG_clkRegs::getAddressMapToHiLink(int csrIndex){
	if(csrIndex>=CSDBG_CLK_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	//TODO: add your code for CSR Address mapping
	return (int)(0x0000 | (broadcast << 13) | (sliceID << 9)|((uint)0x3 << 7) | csrIndex << 1);
}


uint&
CSDBG_clkRegs::get_csr(uint csrIndex){
	if(csrIndex>=CSDBG_CLK_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	return csr[csrIndex];
}

void
CSDBG_clkRegs::get_default_MacroLaneID(T_MacroLaneID& id){
	//TODO: add your code for CSR Address mapping
	id.MacroID=macroID;
	id.LaneID=sliceID;
}

uint
CSDBG_clkRegs::getCSRCount(){
	return CSDBG_CLK_CSR_NUM;
}

string
CSDBG_clkRegs::getName(){
	return "CSDBG_CLK";
}

///////////////////////////////////////////////////////////////////////////


	/// Clockslice loss of clock detector pll1 reset. Active low.
	/// 0 = Reset loss of clock detector part
	/// 1 = Reset is not active
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lcd_1_soft_rst_n(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{0,"cs_lcd_1_soft_rst_n",15,15}
	};
	return reg;
}

	/// Clockslice loss of lock detector pll1 reset. Active low.
	/// 0 = Reset loss of lock detector part
	/// 1 = Reset is not active
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lld_1_soft_rst_n(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{0,"cs_lld_1_soft_rst_n",14,14}
	};
	return reg;
}

	/// Clear the loss of lock detector. Active high.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lld_clr(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{0,"cs_lld_clr",13,13}
	};
	return reg;
}

	/// Clear the frequency detector. Active high.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_fd_clr(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{0,"cs_fd_clr",12,12}
	};
	return reg;
}

	/// Clear the status of calibration. Active high.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_calib_clr(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{0,"cs_calib_clr",11,11}
	};
	return reg;
}

	/// Start clockslice loss of clock detector. Active rising edge.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lcd_start(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{0,"cs_lcd_start",10,10}
	};
	return reg;
}

	/// Start clockslice loss of lock detector. Active rising edge.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lld_start(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{0,"cs_lld_start",9,9}
	};
	return reg;
}

	/// VCO_CAL_FSM  Alternate start bit. Used with CSCALMODE=3 and
	/// - LCVCOCALSEL=0 for PLL0 calibration
	/// - LCVCOCALSEL=1 for PLL1 calibration
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_calib_start(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{0,"cs_calib_start",8,8}
	};
	return reg;
}

	/// Enable clockslice loss of clock detector. Active high.
	/// 0 = Don't enable the detector, Gating the clock
	/// 1 = Enable the detector
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lcd_enable(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{0,"cs_lcd_enable",7,7}
	};
	return reg;
}

	/// Enable clockslice loss of lock detector. Active high.
	/// 0 = Don't enable the detector, Gating the clock
	/// 1 = Enable the detector
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lld_enable(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{0,"cs_lld_enable",6,6}
	};
	return reg;
}

	/// Enable clockslice calibration. Active high.
	/// 0 = Don't enable calibration, Gating the clock
	/// 1 = Enable calibration
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_calib_enable(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{0,"cs_calib_enable",5,5}
	};
	return reg;
}

	/// Clockslice loss of clock detector pll0 reset. Active low.
	/// 0 = Reset loss of clock detector part
	/// 1 = Reset is not active
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lcd_soft_rst_n(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{0,"cs_lcd_soft_rst_n",4,4}
	};
	return reg;
}

	/// Clockslice loss of lock detector pll0 reset. Active low.
	/// 0 = Reset loss of lock detector part
	/// 1 = Reset is not active
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lld_soft_rst_n(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{0,"cs_lld_soft_rst_n",3,3}
	};
	return reg;
}

	/// Clockslice calibration reset. Active low.
	/// 0 = Reset calibration part
	/// 1 = Reset is not active
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_calib_soft_rst_n(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{0,"cs_calib_soft_rst_n",2,2}
	};
	return reg;
}

	/// Clockslice bus reset. Active low.
	/// 0 = Reset bus part
	/// 1 = Reset is not active
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_bus_soft_rst_n(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{0,"cs_bus_soft_rst_n",1,1}
	};
	return reg;
}

	/// Clockslice global reset. Active low.
	/// 0 = Reset whole digital circuit
	/// 1 = Reset is not active
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_glb_soft_rst_n(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{0,"cs_glb_soft_rst_n",0,0}
	};
	return reg;
}

	/// Clockslice analog test bus select. Select which analog signal to be brought out through analog test muxes for observation.
	/// NOT IMPLEMENTED
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::csatbsel14to0(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{1,"csatbsel14to0",14,0}
	};
	return reg;
}

	/// TOP_FSM[3:0] and vco_calfsm[4:0] current state 
	/// Arranged as TOP_FSM[3:0], and cs_vco_top_fsm[4:0]
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::vco_fsm_state(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{2,"vco_fsm_state",15,7}
	};
	return reg;
}

	/// Control direction of general purpose calibration FSM for debugging.
	/// [6]: For lock of check calibration.
	/// [5]: For maximum amplitude calibration.
	/// [4]: For band selection calibration.
	/// [3]: For frequency calibration.
	/// [2]: For minimum amplitude calibration.
	/// [1]: For initial amplitude calibration. NC
	/// [0]: For offset calibration. NC
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_direction_ctrl(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{2,"cs_direction_ctrl",6,0}
	};
	return reg;
}

	/// Calibration mode configuration for band selection calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_calib_mode_bdsel(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{3,"cs_calib_mode_bdsel",14,12}
	};
	return reg;
}

	/// Calibration mode configuration for frequency calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_calib_mode_freqcal(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{3,"cs_calib_mode_freqcal",11,9}
	};
	return reg;
}

	/// Calibration mode configuration for minimum amplitude calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_calib_mode_minamp(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{3,"cs_calib_mode_minamp",8,6}
	};
	return reg;
}

	/// Calibration mode configuration for lock of check calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_calib_mode_lckchk(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{3,"cs_calib_mode_lckchk",5,3}
	};
	return reg;
}

	/// Calibration mode configuration for maximum amplitude calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_calib_mode_maxamp(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{3,"cs_calib_mode_maxamp",2,0}
	};
	return reg;
}

	/// CS Power Sequencing FSM current state
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_pwr_seq_state(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{4,"cs_pwr_seq_state",15,10}
	};
	return reg;
}

	/// CS pwr_Seq_fsm completes power sequencing execution
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_fsm_pwr_seq_done(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{4,"cs_fsm_pwr_seq_done",9,9}
	};
	return reg;
}

	/// CS Power Sequence TBS Timer
	/// [7 = 5] thermal encoding  000_0000 to 111_1111
	/// [4 = 0] binary   0_0000 to 1_1111
	/// For lifeclock frequency of 156.25Mhz
	/// 0 to 31 =  TBS=3-34 cycles (19.2ns to  217.6ns)
	/// 32 to 63 =  TBS=35-66 cycles (224.0ns to 422.4ns)
	/// 96 to 127 =  TBS=99-130 cycles (633.6ns to 832.0 ns)
	/// ?2016 to 2047 =  TBS=2019-2050 cycles (12.921 us to  13.120 us)
	/// 4064 to 4095 =  TBS=4067-4098 cycles (26.028 us to 26.227 us)
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cspwrseqtbstimer(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{4,"cspwrseqtbstimer",7,0}
	};
	return reg;
}

	/// MISC_CAL_FSM Alternate Start bit. Used with CSCALMODE=1
	/// 1 =  Start MISC_CAL_FSM
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::misccalfsmastart(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{5,"misccalfsmastart",15,15}
	};
	return reg;
}

	/// DPM Detection FSM Alternate Start bit
	/// 1 =  Start DPM Detection FSM
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::dpmdetectastart(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{5,"dpmdetectastart",14,14}
	};
	return reg;
}

	/// DPM Detection FSM clear.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::dpmdetfsmclr(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{5,"dpmdetfsmclr",13,13}
	};
	return reg;
}

	/// Output of clockslice's comparator.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::compstatus(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{5,"compstatus",12,12}
	};
	return reg;
}

	/// Comparator Vref generator target select bits :
	/// Setting = 400mV + (6.25mV x  COMPVREFSEL)  
	/// 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::compvrefseltarget(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{5,"compvrefseltarget",5,0}
	};
	return reg;
}

	/// Define maximum calibration control code for minimum amplitude calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_ctrl_code_max_minamp(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{6,"cs_ctrl_code_max_minamp",14,10}
	};
	return reg;
}

	/// Define minimum calibration control codefor minimum amplitude calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_ctrl_code_min_minamp(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{6,"cs_ctrl_code_min_minamp",9,5}
	};
	return reg;
}

	/// Define maximum calibration control code for initial amplitude calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_ctrl_code_max_initamp(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{6,"cs_ctrl_code_max_initamp",4,0}
	};
	return reg;
}

	/// Define minimum calibration control code for band selection calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_ctrl_code_min_bdsel(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{7,"cs_ctrl_code_min_bdsel",14,10}
	};
	return reg;
}

	/// Define maximum calibration control code for frequency calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_ctrl_code_max_freqcal(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{7,"cs_ctrl_code_max_freqcal",9,5}
	};
	return reg;
}

	/// Define minimum calibration control code for frequency calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_ctrl_code_min_freqcal(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{7,"cs_ctrl_code_min_freqcal",4,0}
	};
	return reg;
}

	/// Define maximum calibration control code for maximum amplitude calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_ctrl_code_max_maxamp(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{8,"cs_ctrl_code_max_maxamp",14,10}
	};
	return reg;
}

	/// Define minimum calibration control code for maximum amplitude calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_ctrl_code_min_maxamp(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{8,"cs_ctrl_code_min_maxamp",9,5}
	};
	return reg;
}

	/// Define maximum calibration control code for band selection calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_ctrl_code_max_bdsel(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{8,"cs_ctrl_code_max_bdsel",4,0}
	};
	return reg;
}

	/// Define maximum calibration control code for lock of check calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_ctrl_code_max_lckchk(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{9,"cs_ctrl_code_max_lckchk",9,5}
	};
	return reg;
}

	/// Define minimum calibration control codefor lock of check calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_ctrl_code_min_lckchk(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{9,"cs_ctrl_code_min_lckchk",4,0}
	};
	return reg;
}

	/// The solution flag of the first VCO calibration run.
	/// 0: No solution found in the first VCO calibration run
	/// ;1: Solution was found in the first VCO calibration run.
	/// 
	/// If the V101 top VCO calibration FSM is enabled (V101 mode), it's the solution flag of the first VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
	/// 
	/// If the V101 top VCO calibration FSM is disabled (V100 mode), there is no second run, it's the solution flag of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::firstsolnflag(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{10,"firstsolnflag",15,15}
	};
	return reg;
}

	/// The band sel of the first VCO calibration run.
	/// 
	/// If the V101 top VCO calibration FSM is enabled (V101 mode), it's the band sel of the first VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
	/// 
	/// If the V101 top VCO calibration FSM is disabled (V100 mode), there is no second run, it's the band sel of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::firstbdsel(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{10,"firstbdsel",12,10}
	};
	return reg;
}

	/// The point 1 freqcal of the first VCO calibration run.
	/// 
	/// If the V101 top VCO calibration FSM is enabled (V101 mode), it's the point 1 freqcal of the first VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
	/// 
	/// If the V101 top VCO calibration FSM is disabled (V100 mode), there is no second run, it's the point 1 freqcal of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::firstfreqcalp1(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{10,"firstfreqcalp1",9,5}
	};
	return reg;
}

	/// The point 2 freqcal of the first VCO calibration run.
	/// 
	/// If the V101 top VCO calibration FSM is enabled (V101 mode), it's the point 2 freqcal of the first VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
	/// 
	/// If the V101 top VCO calibration FSM is disabled (V100 mode), there is no second run, it's the point 2 freqcal of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::firstfreqcalp2(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{10,"firstfreqcalp2",4,0}
	};
	return reg;
}

	/// The solution flag of the second VCO calibration run. It only applies to the V101 mode (i.e., the V101 top VCO calibration FSM is enabled) since there no second run.
	/// 
	/// 0: No solution found in the second VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected
	/// ;1: Solution was found in the second VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::secondsolnflag(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{11,"secondsolnflag",15,15}
	};
	return reg;
}

	/// The band sel of the second VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected. It only applies to the V101 mode (i.e., the V101 top VCO calibration FSM is enabled) since there no second run.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::secondbdsel(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{11,"secondbdsel",12,10}
	};
	return reg;
}

	/// The point 1 freqcal of the second VCO calibration run or the first edge point freqcal.
	/// 
	/// In the V101 mode (i.e., the V101 top VCO calibration FSM is enabled), if there is a solution found in the second VCO calibration run, it's the point 2 freqcal of the second VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected. Otherwise, it's the first edge point freqcal of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
	/// 
	/// In the V100 mode (i.e., the V101 top VCO calibration FSM is disabled), there is no second run, it's the edge point freqcal of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::secondfreqcalp1(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{11,"secondfreqcalp1",9,5}
	};
	return reg;
}

	/// The point 2 freqcal of the second VCO calibration run. It only applies to the V101 mode (i.e., the V101 top VCO calibration FSM is enabled). If there is a solution found in the second VCO calibration run, it's the point 2 freqcal of the second VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected. Otherwise, it's the second edge point freqcal of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::secondfreqcalp2(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{11,"secondfreqcalp2",4,0}
	};
	return reg;
}

	/// Define initial calibration control code for lock of check calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_init_code_lckchk(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{12,"cs_init_code_lckchk",4,0}
	};
	return reg;
}

	/// Configure the maximum transitions for minimum amplitude calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_trans_max_minamp(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{13,"cs_trans_max_minamp",11,8}
	};
	return reg;
}

	/// Configure the maximum EVEN transitions only for frequency calibration: 2/4/8/16 to accumulate fd_diff count by 1/2/4/8 times
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_trans_max_freqcal(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{13,"cs_trans_max_freqcal",4,0}
	};
	return reg;
}

	/// Configure the maximum transitions for lock of check calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_trans_max_lckchk(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{14,"cs_trans_max_lckchk",11,8}
	};
	return reg;
}

	/// Configure the maximum transitions for maximum amplitude calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_trans_max_maxamp(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{14,"cs_trans_max_maxamp",7,4}
	};
	return reg;
}

	/// Configure the maximum transitions for band selection calibration.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_trans_max_bdsel(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{14,"cs_trans_max_bdsel",3,0}
	};
	return reg;
}

	/// Define the threshold of frequency detector. If abs[number of refclk cycle - number of fbclk cycle] less than threshold, it would indicate that PLL is locked.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_fd_threshold(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{15,"cs_fd_threshold",10,1}
	};
	return reg;
}

	/// When loss of lock detecting, it could enable timer for waiting specified time.
	/// 0 = disable
	/// 1 = enable
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_meas_fd_wait(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{15,"cs_meas_fd_wait",0,0}
	};
	return reg;
}

	/// Define the decrease value of reference clock counter.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_fd_ref_cnt_dv(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{16,"cs_fd_ref_cnt_dv",15,14}
	};
	return reg;
}

	/// The initial value of reference and feedback clock counter.
	/// Note: modified to program low resolution
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_fd_ref_cnt_lv(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{16,"cs_fd_ref_cnt_lv",13,0}
	};
	return reg;
}

	/// Define the decrease value of feedback clock counter.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_fd_fb_cnt_dv(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{17,"cs_fd_fb_cnt_dv",15,14}
	};
	return reg;
}

	/// The initial value of high resolution count for reference and feedback clock counters.
	/// Note: modified to program high resolution
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_fd_fb_cnt_lv(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{17,"cs_fd_fb_cnt_lv",13,0}
	};
	return reg;
}

	/// Configuration of timer for waiting, which is the cycles of reference clock. Timer is controlled by cs_vco_top_fsm during itank calibration. At the beginning of each GCAL control code, the timer is loaded with this value and counts down. When the timer expires, GCAL checks for comparator output changes.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_timer_value(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{18,"cs_timer_value",14,5}
	};
	return reg;
}

	/// Configuration of divider in timer.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_timer_div_value(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{18,"cs_timer_div_value",4,2}
	};
	return reg;
}

	/// Currently NOT used
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_timer_div_en(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{18,"cs_timer_div_en",1,1}
	};
	return reg;
}

	/// Stop timer, for debugging.
	/// 0 = normal
	/// 1 = stop the timer
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_timer_stop(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{18,"cs_timer_stop",0,0}
	};
	return reg;
}

	/// The divider of feedback clock for loss of lock detector.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lld_fb_div_ratio(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{19,"cs_lld_fb_div_ratio",3,1}
	};
	return reg;
}

	/// The LLD operation manner:
	/// 0 = operate always.
	/// 1 = Perform loss of lock one time then halt.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lld_once(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{19,"cs_lld_once",0,0}
	};
	return reg;
}

	/// The decrease value of reference clock counter.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lld_ref_cnt_dv(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{20,"cs_lld_ref_cnt_dv",14,12}
	};
	return reg;
}

	/// The initial value of reference clock counter.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lld_ref_cnt_lv(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{20,"cs_lld_ref_cnt_lv",11,0}
	};
	return reg;
}

	/// The decrease value of feedback clock counter.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lld_fb_cnt_dv(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{21,"cs_lld_fb_cnt_dv",14,12}
	};
	return reg;
}

	/// The initial value of feedback clock counter.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lld_fb_cnt_lv(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{21,"cs_lld_fb_cnt_lv",11,0}
	};
	return reg;
}

	/// The divider of feedback clock of loss of clock.
	/// (Note: A value less the 0x4 will cause False alarm )
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lcd_fb_div_ratio(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{22,"cs_lcd_fb_div_ratio",9,1}
	};
	return reg;
}

	/// Override the status of loss of clock.
	/// 0 = normal
	/// 1 = override
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lcd_override(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{22,"cs_lcd_override",0,0}
	};
	return reg;
}

	/// The initial value of feedback clock counter.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lcd_fb_cnt_lv(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{23,"cs_lcd_fb_cnt_lv",11,0}
	};
	return reg;
}

	/// The point 1 fd_diff of the first VCO calibration run. Unsigned value.
	/// 
	/// If the V101 top VCO calibration FSM is enabled (V101 mode), it's the point 1 fd_diff of the first VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
	/// 
	/// If the V101 top VCO calibration FSM is disabled (V100 mode), there is no second run, it's the point 1 fd_diff of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::firstfddiffp1(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{24,"firstfddiffp1",14,0}
	};
	return reg;
}

	/// The point 2 fd diff of the first VCO calibration run. Unsigned value.
	/// 
	/// If the V101 top VCO calibration FSM is enabled (V101 mode), it's the point 2 fd diff of the first VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
	/// 
	/// If the V101 top VCO calibration FSM is disabled (V100 mode), there is no second run, it's the point 2 fd diff of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::firstfddiffp2(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{25,"firstfddiffp2",14,0}
	};
	return reg;
}

	/// Debugging control:
	/// [15]: cs comparator status inversion. 0:Normal, 1: Invert
	/// [14]: Not used.
	/// [13]: freqcal +/-1 control 
	/// [12]: bandsel +/-1 control. Used together with bit [11]=1
	/// [11]: bandsel de-bouncing control
	/// [10]: Search method for frequency calibration. [1]: enable starting freqcal in the middle of a bandsel
	/// [9:7]: Not used.
	/// [6]:  Select mclk1_north_out/mclk1_south_out source. 0:select pll1_dtb_out. 1: select pll1_mclk2dig_40b
	/// [5]: Select mclk0_north_out/mclk0_south_out source. 0:select pll0_dtb_out. 1: select pll0_mclk2dig_40b
	/// [4]: Not used.
	/// [3:2]:pll_transcnt_sel. Control which transition counter will be output to csdbg_csr39[9:6] for debug purpose.01: min_amp. 10:max_amp
	/// [1]: pll_max_amp_code_sel . Minamp2maxamp_code source selection. Not being used.
	/// [0]: pll_freqcal_bdsel_ctrl. 1: disable gcal_mon_data being sourced  by fd_diff sign during frequency calibration
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_debugging_ctrl1(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{26,"cs_debugging_ctrl1",15,0}
	};
	return reg;
}

	/// The status of VCO calibration.
	/// 0 = incomplete
	/// 1 = complete.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_calib_done(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{27,"cs_calib_done",15,15}
	};
	return reg;
}

	/// VCO calibration result status
	/// 0 = failure
	/// 1 = success.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_calib_success(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{27,"cs_calib_success",14,14}
	};
	return reg;
}

	/// The reference clock counter of loss of lock detector.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lld_ref_freq(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{27,"cs_lld_ref_freq",11,0}
	};
	return reg;
}

	/// The point 1 fd diff of the second VCO calibration run or the first edge point fd diff. Unsigned value.
	/// 
	/// In the V101 mode (i.e., the V101 top VCO calibration FSM is enabled), if there is a solution found in the second VCO calibration run, it's the point 2 fd diff of the second VCO 
	/// calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected. Otherwise, it's the first edge point fd diff of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
	/// 
	/// In the V100 mode (i.e., the V101 top VCO calibration FSM is disabled), there is no second run, it's the edge point fd diff of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::secondfddiffp1(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{28,"secondfddiffp1",14,0}
	};
	return reg;
}

	/// The point 2 fd diff of the second VCO calibration run. It only applies to the V101 mode (i.e., the V101 top VCO calibration FSM is enabled). If there is a solution found in the second VCO calibration run, it's the point 2 fd diff of the second VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected. Otherwise, it's the second edge point fd diff of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected. Unsigned value.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::secondfddiffp2(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{29,"secondfddiffp2",14,0}
	};
	return reg;
}

	/// Pll0/1 fd_diff count of selected bdsel and freqcal. Unsigned value.
	/// 
	/// Note: 0x7FFF is the power up default (ie, freqcal point does not exist)
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_fd_diff_freq(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{30,"cs_fd_diff_freq",14,0}
	};
	return reg;
}

	/// The status of loss of lock.
	/// 0 = incomplete
	/// 1 = complete
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lld_done(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{31,"cs_lld_done",15,15}
	};
	return reg;
}

	/// The difference of reference clock counter and feedback clock counter for loss of lock detector.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lld_diff_freq(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{31,"cs_lld_diff_freq",12,0}
	};
	return reg;
}

	/// The feedback clock counter of loss of lock detector.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_lld_fb_freq(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{32,"cs_lld_fb_freq",11,0}
	};
	return reg;
}

	/// VCO CAL Miscellaneous Status:
	/// [15] = Loss of fb clock. Indicate during VCO calibration, the fb clock was ever lost.
	/// [14:10] = Reserved
	/// [9] =  pll0/1_fd_status: fd_diff cnt meets threshold (v100/v101)
	/// [8:5] =  transition counter output
	/// [4] =  transition warning
	/// [3:1] =  vcm fsm calib mode
	/// [0] = shared pll0/1 calrstb
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_misc_status(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{33,"cs_misc_status",15,0}
	};
	return reg;
}

	/// VCO CAL FSM Status:
	/// [15:14] = Not used.
	/// [13] = vcofsm shared pll0/1 calib state error (v100 mode only)
	/// [12:0] = vcofsm shared pll0/1 calib state flag (v100 mode only)
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_calib_fsm_status(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{34,"cs_calib_fsm_status",15,0}
	};
	return reg;
}

	/// VCO GCAL FSM Status:
	/// [15:13]: The bdsel when the fb clock got lost during the VCO calibration
	/// ;[12:8]: The freqcal when the fb clock got lost during the VCO calibration
	/// ;[7]: shared pll0/1 gcal error (due to internal state error
	/// [6]: shared pll0/1 gcal transition status
	/// [5:0]: shared pll0/1 gcal state flag
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::cs_gcalib_fsm_status(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{35,"cs_gcalib_fsm_status",15,0}
	};
	return reg;
}

	/// 0 = auto
	/// 1 = manual
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_calib_mode(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{36,"ringvco_calib_mode",15,15}
	};
	return reg;
}

	/// Start ring VCO calibration. Active rising edge.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_calib_start(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{36,"ringvco_calib_start",14,14}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_calib_done(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{36,"ringvco_calib_done",5,5}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_calib_err(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{36,"ringvco_calib_err",4,4}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_autotune_status(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{36,"ringvco_autotune_status",3,0}
	};
	return reg;
}

	/// Start Ring VCO frequency detector. Active high.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_fd_start(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{37,"ringvco_fd_start",15,15}
	};
	return reg;
}

	/// Clear the frequency detector. Active high.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_fd_clr(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{37,"ringvco_fd_clr",14,14}
	};
	return reg;
}

	/// Define the threshold of frequency detector. If abs[number of refclk cycle - number of fbclk cycle] less than threshold, it would indicate that PLL is locked.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_fd_threshold(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{37,"ringvco_fd_threshold",9,0}
	};
	return reg;
}

	/// Define the decrease value of reference clock counter.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_fd_ref_cnt_dv(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{38,"ringvco_fd_ref_cnt_dv",13,12}
	};
	return reg;
}

	/// The initial value of reference clock counter.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_fd_ref_cnt_lv(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{38,"ringvco_fd_ref_cnt_lv",11,0}
	};
	return reg;
}

	/// Define the decrease value of feedback clock counter.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_fd_fb_cnt_dv(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{39,"ringvco_fd_fb_cnt_dv",13,12}
	};
	return reg;
}

	/// The initial value of feedback clock counter.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_fd_fb_cnt_lv(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{39,"ringvco_fd_fb_cnt_lv",11,0}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_timer_value(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{40,"ringvco_timer_value",14,5}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_timer_div_value(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{40,"ringvco_timer_div_value",4,2}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_timer_div_en(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{40,"ringvco_timer_div_en",1,1}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_timer_stop(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{40,"ringvco_timer_stop",0,0}
	};
	return reg;
}

	/// The status of calibration FSM for debugging purpose. Following internal signals could be read back.
	/// [15:12]= vcoctrl
	/// [11:4]=IDAC code (driven by FSM)
	/// [3:0]= FSM encoded current state
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_calib_fsm_status(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{41,"ringvco_calib_fsm_status",15,0}
	};
	return reg;
}

	/// Ring VCO Misc Calibration Status:
	/// [15-9]=unused
	/// [8]=FD status
	/// [7:0]=IDAC code used for DPM processing. Driven by FSM or MOSDETIOSCDACCAL (CS_CSR41[7:0]) based on RINGVCO_CALIB_MODE (DBG_CSR-36) setting.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_misc_status(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{42,"ringvco_misc_status",15,0}
	};
	return reg;
}

	/// The reference clock counter of frequency detector.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_fd_ref_freq(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{43,"ringvco_fd_ref_freq",11,0}
	};
	return reg;
}

	/// The feedback clock counter of frequency detector.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_fd_fb_freq(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{44,"ringvco_fd_fb_freq",11,0}
	};
	return reg;
}

	/// The difference of reference clock counter and feedback clock counter for frequency detector.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::ringvco_fd_diff_freq(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{45,"ringvco_fd_diff_freq",12,0}
	};
	return reg;
}

	/// 
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::csspare1(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{46,"csspare1",15,0}
	};
	return reg;
}

	/// 
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::csspare2(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{47,"csspare2",15,0}
	};
	return reg;
}

	/// Configuration of timer for waiting, which is the cycles of reference clock.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::misc_calib_timer_value(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{48,"misc_calib_timer_value",15,4}
	};
	return reg;
}

	/// Configuration of divider in timer, for debugging.
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::misc_calib_timer_div_value(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{48,"misc_calib_timer_div_value",3,0}
	};
	return reg;
}

	/// MISC_CALIB_GCAL_DIR[4]: ADC BGV
	/// MISC_CALIB_GCAL_DIR[3]: RX term
	/// MISC_CALIB_GCAL_DIR[2]: vref
	/// MISC_CALIB_GCAL_DIR[1]: vreg
	/// MISC_CALIB_GCAL_DIR[0]: vref_gen
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::misc_calib_gcal_dir(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{49,"misc_calib_gcal_dir",15,11}
	};
	return reg;
}

	/// MISC CALIB FSM internal state for debug purpose
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::misc_calib_fsm_state(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{49,"misc_calib_fsm_state",10,5}
	};
	return reg;
}

	/// Stop timer for debug purpose
	/// 0: Normal
	/// 1: Stop timer
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::misc_calib_timer_stop(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{49,"misc_calib_timer_stop",4,4}
	};
	return reg;
}

	/// Clear MISC CALIB FSM 
	/// 0: Normal
	/// 1: Stop FSM
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::misc_calib_fsm_clr(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{49,"misc_calib_fsm_clr",3,3}
	};
	return reg;
}

	/// Number of Transition applied to MISC_CALIB_TASK 0 to 10
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::misc_calib_trans(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{49,"misc_calib_trans",2,0}
	};
	return reg;
}

	/// 0=Enable fsm to select reference value from DF_code_mapper 
	/// 1=Disable fsm from selecting reference value generated by DF_code_mapper, hence CSDFREFCODE (csr50) is selected as reference for cs df comparator status during calibration or dpm finetuning
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::fsm_sel_cs_df_refcode_disable(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{50,"fsm_sel_cs_df_refcode_disable",15,15}
	};
	return reg;
}

	/// PLL1 CS Comparator voltage reference for itank calibration.  The following setting will be added/subtracted with VREFGENOFFSET before sending out on comp_vref_sel port during itank calibration.
	/// Setting = 400mV + (6.25mV x PLL0_ITANK_COMPVREF) 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::pll1_itank_compvref(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{50,"pll1_itank_compvref",11,6}
	};
	return reg;
}

	/// PLL0 CS Comparator voltage reference for itank calibration.  The following setting will be added/subtracted with VREFGENOFFSET before sending out on comp_vref_sel port during itank calibration.
	/// Setting = 400mV + (6.25mV x PLL0_ITANK_COMPVREF) 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::pll0_itank_compvref(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{50,"pll0_itank_compvref",5,0}
	};
	return reg;
}

	/// Temperature Reading
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::temprd(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{51,"temprd",9,0}
	};
	return reg;
}

	/// P-Channel Vth Reading
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::pchnrd(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{52,"pchnrd",9,0}
	};
	return reg;
}

	/// N-Channel Vth Reading
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::nchnrd(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{53,"nchnrd",9,0}
	};
	return reg;
}

	/// PLL0 LVCC_VCO_CORE Voltage Reading
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::pll0lvccvcocore(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{54,"pll0lvccvcocore",9,0}
	};
	return reg;
}

	/// PLL1 LVCC_VCO_CORE Voltage Reading
const T_REG_INFO_EX&
CSDBG_clkRegs::_REG_INFO::pll1lvccvcocore(){
	const static T_REG_INFO_EX reg={CSDBG_clkRegs::getInstance(),
		{55,"pll1lvccvcocore",9,0}
	};
	return reg;
}
bool
CSDBG_clkRegs::_REG_INFO::get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos){
	reg_infos.clear();
	switch(csr){
		case 0:
			reg_infos.push_back(cs_lcd_1_soft_rst_n().reg_info);
			reg_infos.push_back(cs_lld_1_soft_rst_n().reg_info);
			reg_infos.push_back(cs_lld_clr().reg_info);
			reg_infos.push_back(cs_fd_clr().reg_info);
			reg_infos.push_back(cs_calib_clr().reg_info);
			reg_infos.push_back(cs_lcd_start().reg_info);
			reg_infos.push_back(cs_lld_start().reg_info);
			reg_infos.push_back(cs_calib_start().reg_info);
			reg_infos.push_back(cs_lcd_enable().reg_info);
			reg_infos.push_back(cs_lld_enable().reg_info);
			reg_infos.push_back(cs_calib_enable().reg_info);
			reg_infos.push_back(cs_lcd_soft_rst_n().reg_info);
			reg_infos.push_back(cs_lld_soft_rst_n().reg_info);
			reg_infos.push_back(cs_calib_soft_rst_n().reg_info);
			reg_infos.push_back(cs_bus_soft_rst_n().reg_info);
			reg_infos.push_back(cs_glb_soft_rst_n().reg_info);
			break;
		case 1:
			reg_infos.push_back(csatbsel14to0().reg_info);
			break;
		case 2:
			reg_infos.push_back(vco_fsm_state().reg_info);
			reg_infos.push_back(cs_direction_ctrl().reg_info);
			break;
		case 3:
			reg_infos.push_back(cs_calib_mode_bdsel().reg_info);
			reg_infos.push_back(cs_calib_mode_freqcal().reg_info);
			reg_infos.push_back(cs_calib_mode_minamp().reg_info);
			reg_infos.push_back(cs_calib_mode_lckchk().reg_info);
			reg_infos.push_back(cs_calib_mode_maxamp().reg_info);
			break;
		case 4:
			reg_infos.push_back(cs_pwr_seq_state().reg_info);
			reg_infos.push_back(cs_fsm_pwr_seq_done().reg_info);
			reg_infos.push_back(cspwrseqtbstimer().reg_info);
			break;
		case 5:
			reg_infos.push_back(misccalfsmastart().reg_info);
			reg_infos.push_back(dpmdetectastart().reg_info);
			reg_infos.push_back(dpmdetfsmclr().reg_info);
			reg_infos.push_back(compstatus().reg_info);
			reg_infos.push_back(compvrefseltarget().reg_info);
			break;
		case 6:
			reg_infos.push_back(cs_ctrl_code_max_minamp().reg_info);
			reg_infos.push_back(cs_ctrl_code_min_minamp().reg_info);
			reg_infos.push_back(cs_ctrl_code_max_initamp().reg_info);
			break;
		case 7:
			reg_infos.push_back(cs_ctrl_code_min_bdsel().reg_info);
			reg_infos.push_back(cs_ctrl_code_max_freqcal().reg_info);
			reg_infos.push_back(cs_ctrl_code_min_freqcal().reg_info);
			break;
		case 8:
			reg_infos.push_back(cs_ctrl_code_max_maxamp().reg_info);
			reg_infos.push_back(cs_ctrl_code_min_maxamp().reg_info);
			reg_infos.push_back(cs_ctrl_code_max_bdsel().reg_info);
			break;
		case 9:
			reg_infos.push_back(cs_ctrl_code_max_lckchk().reg_info);
			reg_infos.push_back(cs_ctrl_code_min_lckchk().reg_info);
			break;
		case 10:
			reg_infos.push_back(firstsolnflag().reg_info);
			reg_infos.push_back(firstbdsel().reg_info);
			reg_infos.push_back(firstfreqcalp1().reg_info);
			reg_infos.push_back(firstfreqcalp2().reg_info);
			break;
		case 11:
			reg_infos.push_back(secondsolnflag().reg_info);
			reg_infos.push_back(secondbdsel().reg_info);
			reg_infos.push_back(secondfreqcalp1().reg_info);
			reg_infos.push_back(secondfreqcalp2().reg_info);
			break;
		case 12:
			reg_infos.push_back(cs_init_code_lckchk().reg_info);
			break;
		case 13:
			reg_infos.push_back(cs_trans_max_minamp().reg_info);
			reg_infos.push_back(cs_trans_max_freqcal().reg_info);
			break;
		case 14:
			reg_infos.push_back(cs_trans_max_lckchk().reg_info);
			reg_infos.push_back(cs_trans_max_maxamp().reg_info);
			reg_infos.push_back(cs_trans_max_bdsel().reg_info);
			break;
		case 15:
			reg_infos.push_back(cs_fd_threshold().reg_info);
			reg_infos.push_back(cs_meas_fd_wait().reg_info);
			break;
		case 16:
			reg_infos.push_back(cs_fd_ref_cnt_dv().reg_info);
			reg_infos.push_back(cs_fd_ref_cnt_lv().reg_info);
			break;
		case 17:
			reg_infos.push_back(cs_fd_fb_cnt_dv().reg_info);
			reg_infos.push_back(cs_fd_fb_cnt_lv().reg_info);
			break;
		case 18:
			reg_infos.push_back(cs_timer_value().reg_info);
			reg_infos.push_back(cs_timer_div_value().reg_info);
			reg_infos.push_back(cs_timer_div_en().reg_info);
			reg_infos.push_back(cs_timer_stop().reg_info);
			break;
		case 19:
			reg_infos.push_back(cs_lld_fb_div_ratio().reg_info);
			reg_infos.push_back(cs_lld_once().reg_info);
			break;
		case 20:
			reg_infos.push_back(cs_lld_ref_cnt_dv().reg_info);
			reg_infos.push_back(cs_lld_ref_cnt_lv().reg_info);
			break;
		case 21:
			reg_infos.push_back(cs_lld_fb_cnt_dv().reg_info);
			reg_infos.push_back(cs_lld_fb_cnt_lv().reg_info);
			break;
		case 22:
			reg_infos.push_back(cs_lcd_fb_div_ratio().reg_info);
			reg_infos.push_back(cs_lcd_override().reg_info);
			break;
		case 23:
			reg_infos.push_back(cs_lcd_fb_cnt_lv().reg_info);
			break;
		case 24:
			reg_infos.push_back(firstfddiffp1().reg_info);
			break;
		case 25:
			reg_infos.push_back(firstfddiffp2().reg_info);
			break;
		case 26:
			reg_infos.push_back(cs_debugging_ctrl1().reg_info);
			break;
		case 27:
			reg_infos.push_back(cs_calib_done().reg_info);
			reg_infos.push_back(cs_calib_success().reg_info);
			reg_infos.push_back(cs_lld_ref_freq().reg_info);
			break;
		case 28:
			reg_infos.push_back(secondfddiffp1().reg_info);
			break;
		case 29:
			reg_infos.push_back(secondfddiffp2().reg_info);
			break;
		case 30:
			reg_infos.push_back(cs_fd_diff_freq().reg_info);
			break;
		case 31:
			reg_infos.push_back(cs_lld_done().reg_info);
			reg_infos.push_back(cs_lld_diff_freq().reg_info);
			break;
		case 32:
			reg_infos.push_back(cs_lld_fb_freq().reg_info);
			break;
		case 33:
			reg_infos.push_back(cs_misc_status().reg_info);
			break;
		case 34:
			reg_infos.push_back(cs_calib_fsm_status().reg_info);
			break;
		case 35:
			reg_infos.push_back(cs_gcalib_fsm_status().reg_info);
			break;
		case 36:
			reg_infos.push_back(ringvco_calib_mode().reg_info);
			reg_infos.push_back(ringvco_calib_start().reg_info);
			reg_infos.push_back(ringvco_calib_done().reg_info);
			reg_infos.push_back(ringvco_calib_err().reg_info);
			reg_infos.push_back(ringvco_autotune_status().reg_info);
			break;
		case 37:
			reg_infos.push_back(ringvco_fd_start().reg_info);
			reg_infos.push_back(ringvco_fd_clr().reg_info);
			reg_infos.push_back(ringvco_fd_threshold().reg_info);
			break;
		case 38:
			reg_infos.push_back(ringvco_fd_ref_cnt_dv().reg_info);
			reg_infos.push_back(ringvco_fd_ref_cnt_lv().reg_info);
			break;
		case 39:
			reg_infos.push_back(ringvco_fd_fb_cnt_dv().reg_info);
			reg_infos.push_back(ringvco_fd_fb_cnt_lv().reg_info);
			break;
		case 40:
			reg_infos.push_back(ringvco_timer_value().reg_info);
			reg_infos.push_back(ringvco_timer_div_value().reg_info);
			reg_infos.push_back(ringvco_timer_div_en().reg_info);
			reg_infos.push_back(ringvco_timer_stop().reg_info);
			break;
		case 41:
			reg_infos.push_back(ringvco_calib_fsm_status().reg_info);
			break;
		case 42:
			reg_infos.push_back(ringvco_misc_status().reg_info);
			break;
		case 43:
			reg_infos.push_back(ringvco_fd_ref_freq().reg_info);
			break;
		case 44:
			reg_infos.push_back(ringvco_fd_fb_freq().reg_info);
			break;
		case 45:
			reg_infos.push_back(ringvco_fd_diff_freq().reg_info);
			break;
		case 46:
			reg_infos.push_back(csspare1().reg_info);
			break;
		case 47:
			reg_infos.push_back(csspare2().reg_info);
			break;
		case 48:
			reg_infos.push_back(misc_calib_timer_value().reg_info);
			reg_infos.push_back(misc_calib_timer_div_value().reg_info);
			break;
		case 49:
			reg_infos.push_back(misc_calib_gcal_dir().reg_info);
			reg_infos.push_back(misc_calib_fsm_state().reg_info);
			reg_infos.push_back(misc_calib_timer_stop().reg_info);
			reg_infos.push_back(misc_calib_fsm_clr().reg_info);
			reg_infos.push_back(misc_calib_trans().reg_info);
			break;
		case 50:
			reg_infos.push_back(fsm_sel_cs_df_refcode_disable().reg_info);
			reg_infos.push_back(pll1_itank_compvref().reg_info);
			reg_infos.push_back(pll0_itank_compvref().reg_info);
			break;
		case 51:
			reg_infos.push_back(temprd().reg_info);
			break;
		case 52:
			reg_infos.push_back(pchnrd().reg_info);
			break;
		case 53:
			reg_infos.push_back(nchnrd().reg_info);
			break;
		case 54:
			reg_infos.push_back(pll0lvccvcocore().reg_info);
			break;
		case 55:
			reg_infos.push_back(pll1lvccvcocore().reg_info);
			break;
		default:
			break;
	}
	return (reg_infos.size()>0);
}


CSDBG_clkRegs&
CSDBG_clkRegs::setcs_lcd_1_soft_rst_n(uint val){
	fill_csr_bits(val,REG_INFO.cs_lcd_1_soft_rst_n());	//CSR0[15:15]
	return *this;
}
uint
CSDBG_clkRegs::getcs_lcd_1_soft_rst_n(){
	return get_csr_bits(REG_INFO.cs_lcd_1_soft_rst_n());	//CSR0[15:15]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_lld_1_soft_rst_n(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_1_soft_rst_n());	//CSR0[14:14]
	return *this;
}
uint
CSDBG_clkRegs::getcs_lld_1_soft_rst_n(){
	return get_csr_bits(REG_INFO.cs_lld_1_soft_rst_n());	//CSR0[14:14]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_lld_clr(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_clr());	//CSR0[13:13]
	return *this;
}
uint
CSDBG_clkRegs::getcs_lld_clr(){
	return get_csr_bits(REG_INFO.cs_lld_clr());	//CSR0[13:13]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_fd_clr(uint val){
	fill_csr_bits(val,REG_INFO.cs_fd_clr());	//CSR0[12:12]
	return *this;
}
uint
CSDBG_clkRegs::getcs_fd_clr(){
	return get_csr_bits(REG_INFO.cs_fd_clr());	//CSR0[12:12]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_calib_clr(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_clr());	//CSR0[11:11]
	return *this;
}
uint
CSDBG_clkRegs::getcs_calib_clr(){
	return get_csr_bits(REG_INFO.cs_calib_clr());	//CSR0[11:11]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_lcd_start(uint val){
	fill_csr_bits(val,REG_INFO.cs_lcd_start());	//CSR0[10:10]
	return *this;
}
uint
CSDBG_clkRegs::getcs_lcd_start(){
	return get_csr_bits(REG_INFO.cs_lcd_start());	//CSR0[10:10]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_lld_start(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_start());	//CSR0[9:9]
	return *this;
}
uint
CSDBG_clkRegs::getcs_lld_start(){
	return get_csr_bits(REG_INFO.cs_lld_start());	//CSR0[9:9]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_calib_start(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_start());	//CSR0[8:8]
	return *this;
}
uint
CSDBG_clkRegs::getcs_calib_start(){
	return get_csr_bits(REG_INFO.cs_calib_start());	//CSR0[8:8]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_lcd_enable(uint val){
	fill_csr_bits(val,REG_INFO.cs_lcd_enable());	//CSR0[7:7]
	return *this;
}
uint
CSDBG_clkRegs::getcs_lcd_enable(){
	return get_csr_bits(REG_INFO.cs_lcd_enable());	//CSR0[7:7]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_lld_enable(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_enable());	//CSR0[6:6]
	return *this;
}
uint
CSDBG_clkRegs::getcs_lld_enable(){
	return get_csr_bits(REG_INFO.cs_lld_enable());	//CSR0[6:6]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_calib_enable(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_enable());	//CSR0[5:5]
	return *this;
}
uint
CSDBG_clkRegs::getcs_calib_enable(){
	return get_csr_bits(REG_INFO.cs_calib_enable());	//CSR0[5:5]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_lcd_soft_rst_n(uint val){
	fill_csr_bits(val,REG_INFO.cs_lcd_soft_rst_n());	//CSR0[4:4]
	return *this;
}
uint
CSDBG_clkRegs::getcs_lcd_soft_rst_n(){
	return get_csr_bits(REG_INFO.cs_lcd_soft_rst_n());	//CSR0[4:4]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_lld_soft_rst_n(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_soft_rst_n());	//CSR0[3:3]
	return *this;
}
uint
CSDBG_clkRegs::getcs_lld_soft_rst_n(){
	return get_csr_bits(REG_INFO.cs_lld_soft_rst_n());	//CSR0[3:3]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_calib_soft_rst_n(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_soft_rst_n());	//CSR0[2:2]
	return *this;
}
uint
CSDBG_clkRegs::getcs_calib_soft_rst_n(){
	return get_csr_bits(REG_INFO.cs_calib_soft_rst_n());	//CSR0[2:2]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_bus_soft_rst_n(uint val){
	fill_csr_bits(val,REG_INFO.cs_bus_soft_rst_n());	//CSR0[1:1]
	return *this;
}
uint
CSDBG_clkRegs::getcs_bus_soft_rst_n(){
	return get_csr_bits(REG_INFO.cs_bus_soft_rst_n());	//CSR0[1:1]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_glb_soft_rst_n(uint val){
	fill_csr_bits(val,REG_INFO.cs_glb_soft_rst_n());	//CSR0[0:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_glb_soft_rst_n(){
	return get_csr_bits(REG_INFO.cs_glb_soft_rst_n());	//CSR0[0:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcsatbsel14to0(uint val){
	fill_csr_bits(val,REG_INFO.csatbsel14to0());	//CSR1[14:0]
	return *this;
}
uint
CSDBG_clkRegs::getcsatbsel14to0(){
	return get_csr_bits(REG_INFO.csatbsel14to0());	//CSR1[14:0]
}

uint
CSDBG_clkRegs::getvco_fsm_state(){
	return get_csr_bits(REG_INFO.vco_fsm_state());	//CSR2[15:7]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_direction_ctrl(uint val){
	fill_csr_bits(val,REG_INFO.cs_direction_ctrl());	//CSR2[6:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_direction_ctrl(){
	return get_csr_bits(REG_INFO.cs_direction_ctrl());	//CSR2[6:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_calib_mode_bdsel(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_mode_bdsel());	//CSR3[14:12]
	return *this;
}
uint
CSDBG_clkRegs::getcs_calib_mode_bdsel(){
	return get_csr_bits(REG_INFO.cs_calib_mode_bdsel());	//CSR3[14:12]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_calib_mode_freqcal(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_mode_freqcal());	//CSR3[11:9]
	return *this;
}
uint
CSDBG_clkRegs::getcs_calib_mode_freqcal(){
	return get_csr_bits(REG_INFO.cs_calib_mode_freqcal());	//CSR3[11:9]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_calib_mode_minamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_mode_minamp());	//CSR3[8:6]
	return *this;
}
uint
CSDBG_clkRegs::getcs_calib_mode_minamp(){
	return get_csr_bits(REG_INFO.cs_calib_mode_minamp());	//CSR3[8:6]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_calib_mode_lckchk(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_mode_lckchk());	//CSR3[5:3]
	return *this;
}
uint
CSDBG_clkRegs::getcs_calib_mode_lckchk(){
	return get_csr_bits(REG_INFO.cs_calib_mode_lckchk());	//CSR3[5:3]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_calib_mode_maxamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_mode_maxamp());	//CSR3[2:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_calib_mode_maxamp(){
	return get_csr_bits(REG_INFO.cs_calib_mode_maxamp());	//CSR3[2:0]
}

uint
CSDBG_clkRegs::getcs_pwr_seq_state(){
	return get_csr_bits(REG_INFO.cs_pwr_seq_state());	//CSR4[15:10]
}

uint
CSDBG_clkRegs::getcs_fsm_pwr_seq_done(){
	return get_csr_bits(REG_INFO.cs_fsm_pwr_seq_done());	//CSR4[9:9]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcspwrseqtbstimer(uint val){
	fill_csr_bits(val,REG_INFO.cspwrseqtbstimer());	//CSR4[7:0]
	return *this;
}
uint
CSDBG_clkRegs::getcspwrseqtbstimer(){
	return get_csr_bits(REG_INFO.cspwrseqtbstimer());	//CSR4[7:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setmisccalfsmastart(uint val){
	fill_csr_bits(val,REG_INFO.misccalfsmastart());	//CSR5[15:15]
	return *this;
}
uint
CSDBG_clkRegs::getmisccalfsmastart(){
	return get_csr_bits(REG_INFO.misccalfsmastart());	//CSR5[15:15]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setdpmdetectastart(uint val){
	fill_csr_bits(val,REG_INFO.dpmdetectastart());	//CSR5[14:14]
	return *this;
}
uint
CSDBG_clkRegs::getdpmdetectastart(){
	return get_csr_bits(REG_INFO.dpmdetectastart());	//CSR5[14:14]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setdpmdetfsmclr(uint val){
	fill_csr_bits(val,REG_INFO.dpmdetfsmclr());	//CSR5[13:13]
	return *this;
}
uint
CSDBG_clkRegs::getdpmdetfsmclr(){
	return get_csr_bits(REG_INFO.dpmdetfsmclr());	//CSR5[13:13]
}

uint
CSDBG_clkRegs::getcompstatus(){
	return get_csr_bits(REG_INFO.compstatus());	//CSR5[12:12]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcompvrefseltarget(uint val){
	fill_csr_bits(val,REG_INFO.compvrefseltarget());	//CSR5[5:0]
	return *this;
}
uint
CSDBG_clkRegs::getcompvrefseltarget(){
	return get_csr_bits(REG_INFO.compvrefseltarget());	//CSR5[5:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_ctrl_code_max_minamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_max_minamp());	//CSR6[14:10]
	return *this;
}
uint
CSDBG_clkRegs::getcs_ctrl_code_max_minamp(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_max_minamp());	//CSR6[14:10]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_ctrl_code_min_minamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_min_minamp());	//CSR6[9:5]
	return *this;
}
uint
CSDBG_clkRegs::getcs_ctrl_code_min_minamp(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_min_minamp());	//CSR6[9:5]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_ctrl_code_max_initamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_max_initamp());	//CSR6[4:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_ctrl_code_max_initamp(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_max_initamp());	//CSR6[4:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_ctrl_code_min_bdsel(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_min_bdsel());	//CSR7[14:10]
	return *this;
}
uint
CSDBG_clkRegs::getcs_ctrl_code_min_bdsel(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_min_bdsel());	//CSR7[14:10]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_ctrl_code_max_freqcal(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_max_freqcal());	//CSR7[9:5]
	return *this;
}
uint
CSDBG_clkRegs::getcs_ctrl_code_max_freqcal(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_max_freqcal());	//CSR7[9:5]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_ctrl_code_min_freqcal(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_min_freqcal());	//CSR7[4:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_ctrl_code_min_freqcal(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_min_freqcal());	//CSR7[4:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_ctrl_code_max_maxamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_max_maxamp());	//CSR8[14:10]
	return *this;
}
uint
CSDBG_clkRegs::getcs_ctrl_code_max_maxamp(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_max_maxamp());	//CSR8[14:10]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_ctrl_code_min_maxamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_min_maxamp());	//CSR8[9:5]
	return *this;
}
uint
CSDBG_clkRegs::getcs_ctrl_code_min_maxamp(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_min_maxamp());	//CSR8[9:5]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_ctrl_code_max_bdsel(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_max_bdsel());	//CSR8[4:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_ctrl_code_max_bdsel(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_max_bdsel());	//CSR8[4:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_ctrl_code_max_lckchk(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_max_lckchk());	//CSR9[9:5]
	return *this;
}
uint
CSDBG_clkRegs::getcs_ctrl_code_max_lckchk(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_max_lckchk());	//CSR9[9:5]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_ctrl_code_min_lckchk(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_min_lckchk());	//CSR9[4:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_ctrl_code_min_lckchk(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_min_lckchk());	//CSR9[4:0]
}

uint
CSDBG_clkRegs::getfirstsolnflag(){
	return get_csr_bits(REG_INFO.firstsolnflag());	//CSR10[15:15]
}

uint
CSDBG_clkRegs::getfirstbdsel(){
	return get_csr_bits(REG_INFO.firstbdsel());	//CSR10[12:10]
}

uint
CSDBG_clkRegs::getfirstfreqcalp1(){
	return get_csr_bits(REG_INFO.firstfreqcalp1());	//CSR10[9:5]
}

uint
CSDBG_clkRegs::getfirstfreqcalp2(){
	return get_csr_bits(REG_INFO.firstfreqcalp2());	//CSR10[4:0]
}

uint
CSDBG_clkRegs::getsecondsolnflag(){
	return get_csr_bits(REG_INFO.secondsolnflag());	//CSR11[15:15]
}

uint
CSDBG_clkRegs::getsecondbdsel(){
	return get_csr_bits(REG_INFO.secondbdsel());	//CSR11[12:10]
}

uint
CSDBG_clkRegs::getsecondfreqcalp1(){
	return get_csr_bits(REG_INFO.secondfreqcalp1());	//CSR11[9:5]
}

uint
CSDBG_clkRegs::getsecondfreqcalp2(){
	return get_csr_bits(REG_INFO.secondfreqcalp2());	//CSR11[4:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_init_code_lckchk(uint val){
	fill_csr_bits(val,REG_INFO.cs_init_code_lckchk());	//CSR12[4:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_init_code_lckchk(){
	return get_csr_bits(REG_INFO.cs_init_code_lckchk());	//CSR12[4:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_trans_max_minamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_trans_max_minamp());	//CSR13[11:8]
	return *this;
}
uint
CSDBG_clkRegs::getcs_trans_max_minamp(){
	return get_csr_bits(REG_INFO.cs_trans_max_minamp());	//CSR13[11:8]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_trans_max_freqcal(uint val){
	fill_csr_bits(val,REG_INFO.cs_trans_max_freqcal());	//CSR13[4:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_trans_max_freqcal(){
	return get_csr_bits(REG_INFO.cs_trans_max_freqcal());	//CSR13[4:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_trans_max_lckchk(uint val){
	fill_csr_bits(val,REG_INFO.cs_trans_max_lckchk());	//CSR14[11:8]
	return *this;
}
uint
CSDBG_clkRegs::getcs_trans_max_lckchk(){
	return get_csr_bits(REG_INFO.cs_trans_max_lckchk());	//CSR14[11:8]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_trans_max_maxamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_trans_max_maxamp());	//CSR14[7:4]
	return *this;
}
uint
CSDBG_clkRegs::getcs_trans_max_maxamp(){
	return get_csr_bits(REG_INFO.cs_trans_max_maxamp());	//CSR14[7:4]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_trans_max_bdsel(uint val){
	fill_csr_bits(val,REG_INFO.cs_trans_max_bdsel());	//CSR14[3:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_trans_max_bdsel(){
	return get_csr_bits(REG_INFO.cs_trans_max_bdsel());	//CSR14[3:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_fd_threshold(uint val){
	fill_csr_bits(val,REG_INFO.cs_fd_threshold());	//CSR15[10:1]
	return *this;
}
uint
CSDBG_clkRegs::getcs_fd_threshold(){
	return get_csr_bits(REG_INFO.cs_fd_threshold());	//CSR15[10:1]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_meas_fd_wait(uint val){
	fill_csr_bits(val,REG_INFO.cs_meas_fd_wait());	//CSR15[0:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_meas_fd_wait(){
	return get_csr_bits(REG_INFO.cs_meas_fd_wait());	//CSR15[0:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_fd_ref_cnt_dv(uint val){
	fill_csr_bits(val,REG_INFO.cs_fd_ref_cnt_dv());	//CSR16[15:14]
	return *this;
}
uint
CSDBG_clkRegs::getcs_fd_ref_cnt_dv(){
	return get_csr_bits(REG_INFO.cs_fd_ref_cnt_dv());	//CSR16[15:14]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_fd_ref_cnt_lv(uint val){
	fill_csr_bits(val,REG_INFO.cs_fd_ref_cnt_lv());	//CSR16[13:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_fd_ref_cnt_lv(){
	return get_csr_bits(REG_INFO.cs_fd_ref_cnt_lv());	//CSR16[13:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_fd_fb_cnt_dv(uint val){
	fill_csr_bits(val,REG_INFO.cs_fd_fb_cnt_dv());	//CSR17[15:14]
	return *this;
}
uint
CSDBG_clkRegs::getcs_fd_fb_cnt_dv(){
	return get_csr_bits(REG_INFO.cs_fd_fb_cnt_dv());	//CSR17[15:14]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_fd_fb_cnt_lv(uint val){
	fill_csr_bits(val,REG_INFO.cs_fd_fb_cnt_lv());	//CSR17[13:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_fd_fb_cnt_lv(){
	return get_csr_bits(REG_INFO.cs_fd_fb_cnt_lv());	//CSR17[13:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_timer_value(uint val){
	fill_csr_bits(val,REG_INFO.cs_timer_value());	//CSR18[14:5]
	return *this;
}
uint
CSDBG_clkRegs::getcs_timer_value(){
	return get_csr_bits(REG_INFO.cs_timer_value());	//CSR18[14:5]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_timer_div_value(uint val){
	fill_csr_bits(val,REG_INFO.cs_timer_div_value());	//CSR18[4:2]
	return *this;
}
uint
CSDBG_clkRegs::getcs_timer_div_value(){
	return get_csr_bits(REG_INFO.cs_timer_div_value());	//CSR18[4:2]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_timer_div_en(uint val){
	fill_csr_bits(val,REG_INFO.cs_timer_div_en());	//CSR18[1:1]
	return *this;
}
uint
CSDBG_clkRegs::getcs_timer_div_en(){
	return get_csr_bits(REG_INFO.cs_timer_div_en());	//CSR18[1:1]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_timer_stop(uint val){
	fill_csr_bits(val,REG_INFO.cs_timer_stop());	//CSR18[0:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_timer_stop(){
	return get_csr_bits(REG_INFO.cs_timer_stop());	//CSR18[0:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_lld_fb_div_ratio(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_fb_div_ratio());	//CSR19[3:1]
	return *this;
}
uint
CSDBG_clkRegs::getcs_lld_fb_div_ratio(){
	return get_csr_bits(REG_INFO.cs_lld_fb_div_ratio());	//CSR19[3:1]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_lld_once(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_once());	//CSR19[0:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_lld_once(){
	return get_csr_bits(REG_INFO.cs_lld_once());	//CSR19[0:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_lld_ref_cnt_dv(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_ref_cnt_dv());	//CSR20[14:12]
	return *this;
}
uint
CSDBG_clkRegs::getcs_lld_ref_cnt_dv(){
	return get_csr_bits(REG_INFO.cs_lld_ref_cnt_dv());	//CSR20[14:12]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_lld_ref_cnt_lv(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_ref_cnt_lv());	//CSR20[11:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_lld_ref_cnt_lv(){
	return get_csr_bits(REG_INFO.cs_lld_ref_cnt_lv());	//CSR20[11:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_lld_fb_cnt_dv(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_fb_cnt_dv());	//CSR21[14:12]
	return *this;
}
uint
CSDBG_clkRegs::getcs_lld_fb_cnt_dv(){
	return get_csr_bits(REG_INFO.cs_lld_fb_cnt_dv());	//CSR21[14:12]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_lld_fb_cnt_lv(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_fb_cnt_lv());	//CSR21[11:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_lld_fb_cnt_lv(){
	return get_csr_bits(REG_INFO.cs_lld_fb_cnt_lv());	//CSR21[11:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_lcd_fb_div_ratio(uint val){
	fill_csr_bits(val,REG_INFO.cs_lcd_fb_div_ratio());	//CSR22[9:1]
	return *this;
}
uint
CSDBG_clkRegs::getcs_lcd_fb_div_ratio(){
	return get_csr_bits(REG_INFO.cs_lcd_fb_div_ratio());	//CSR22[9:1]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_lcd_override(uint val){
	fill_csr_bits(val,REG_INFO.cs_lcd_override());	//CSR22[0:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_lcd_override(){
	return get_csr_bits(REG_INFO.cs_lcd_override());	//CSR22[0:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_lcd_fb_cnt_lv(uint val){
	fill_csr_bits(val,REG_INFO.cs_lcd_fb_cnt_lv());	//CSR23[11:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_lcd_fb_cnt_lv(){
	return get_csr_bits(REG_INFO.cs_lcd_fb_cnt_lv());	//CSR23[11:0]
}

uint
CSDBG_clkRegs::getfirstfddiffp1(){
	return get_csr_bits(REG_INFO.firstfddiffp1());	//CSR24[14:0]
}

uint
CSDBG_clkRegs::getfirstfddiffp2(){
	return get_csr_bits(REG_INFO.firstfddiffp2());	//CSR25[14:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setcs_debugging_ctrl1(uint val){
	fill_csr_bits(val,REG_INFO.cs_debugging_ctrl1());	//CSR26[15:0]
	return *this;
}
uint
CSDBG_clkRegs::getcs_debugging_ctrl1(){
	return get_csr_bits(REG_INFO.cs_debugging_ctrl1());	//CSR26[15:0]
}

uint
CSDBG_clkRegs::getcs_calib_done(){
	return get_csr_bits(REG_INFO.cs_calib_done());	//CSR27[15:15]
}

uint
CSDBG_clkRegs::getcs_calib_success(){
	return get_csr_bits(REG_INFO.cs_calib_success());	//CSR27[14:14]
}

uint
CSDBG_clkRegs::getcs_lld_ref_freq(){
	return get_csr_bits(REG_INFO.cs_lld_ref_freq());	//CSR27[11:0]
}

uint
CSDBG_clkRegs::getsecondfddiffp1(){
	return get_csr_bits(REG_INFO.secondfddiffp1());	//CSR28[14:0]
}

uint
CSDBG_clkRegs::getsecondfddiffp2(){
	return get_csr_bits(REG_INFO.secondfddiffp2());	//CSR29[14:0]
}

uint
CSDBG_clkRegs::getcs_fd_diff_freq(){
	return get_csr_bits(REG_INFO.cs_fd_diff_freq());	//CSR30[14:0]
}

uint
CSDBG_clkRegs::getcs_lld_done(){
	return get_csr_bits(REG_INFO.cs_lld_done());	//CSR31[15:15]
}

uint
CSDBG_clkRegs::getcs_lld_diff_freq(){
	return get_csr_bits(REG_INFO.cs_lld_diff_freq());	//CSR31[12:0]
}

uint
CSDBG_clkRegs::getcs_lld_fb_freq(){
	return get_csr_bits(REG_INFO.cs_lld_fb_freq());	//CSR32[11:0]
}

uint
CSDBG_clkRegs::getcs_misc_status(){
	return get_csr_bits(REG_INFO.cs_misc_status());	//CSR33[15:0]
}

uint
CSDBG_clkRegs::getcs_calib_fsm_status(){
	return get_csr_bits(REG_INFO.cs_calib_fsm_status());	//CSR34[15:0]
}

uint
CSDBG_clkRegs::getcs_gcalib_fsm_status(){
	return get_csr_bits(REG_INFO.cs_gcalib_fsm_status());	//CSR35[15:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setringvco_calib_mode(uint val){
	fill_csr_bits(val,REG_INFO.ringvco_calib_mode());	//CSR36[15:15]
	return *this;
}
uint
CSDBG_clkRegs::getringvco_calib_mode(){
	return get_csr_bits(REG_INFO.ringvco_calib_mode());	//CSR36[15:15]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setringvco_calib_start(uint val){
	fill_csr_bits(val,REG_INFO.ringvco_calib_start());	//CSR36[14:14]
	return *this;
}
uint
CSDBG_clkRegs::getringvco_calib_start(){
	return get_csr_bits(REG_INFO.ringvco_calib_start());	//CSR36[14:14]
}

uint
CSDBG_clkRegs::getringvco_calib_done(){
	return get_csr_bits(REG_INFO.ringvco_calib_done());	//CSR36[5:5]
}

uint
CSDBG_clkRegs::getringvco_calib_err(){
	return get_csr_bits(REG_INFO.ringvco_calib_err());	//CSR36[4:4]
}

uint
CSDBG_clkRegs::getringvco_autotune_status(){
	return get_csr_bits(REG_INFO.ringvco_autotune_status());	//CSR36[3:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setringvco_fd_start(uint val){
	fill_csr_bits(val,REG_INFO.ringvco_fd_start());	//CSR37[15:15]
	return *this;
}
uint
CSDBG_clkRegs::getringvco_fd_start(){
	return get_csr_bits(REG_INFO.ringvco_fd_start());	//CSR37[15:15]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setringvco_fd_clr(uint val){
	fill_csr_bits(val,REG_INFO.ringvco_fd_clr());	//CSR37[14:14]
	return *this;
}
uint
CSDBG_clkRegs::getringvco_fd_clr(){
	return get_csr_bits(REG_INFO.ringvco_fd_clr());	//CSR37[14:14]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setringvco_fd_threshold(uint val){
	fill_csr_bits(val,REG_INFO.ringvco_fd_threshold());	//CSR37[9:0]
	return *this;
}
uint
CSDBG_clkRegs::getringvco_fd_threshold(){
	return get_csr_bits(REG_INFO.ringvco_fd_threshold());	//CSR37[9:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setringvco_fd_ref_cnt_dv(uint val){
	fill_csr_bits(val,REG_INFO.ringvco_fd_ref_cnt_dv());	//CSR38[13:12]
	return *this;
}
uint
CSDBG_clkRegs::getringvco_fd_ref_cnt_dv(){
	return get_csr_bits(REG_INFO.ringvco_fd_ref_cnt_dv());	//CSR38[13:12]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setringvco_fd_ref_cnt_lv(uint val){
	fill_csr_bits(val,REG_INFO.ringvco_fd_ref_cnt_lv());	//CSR38[11:0]
	return *this;
}
uint
CSDBG_clkRegs::getringvco_fd_ref_cnt_lv(){
	return get_csr_bits(REG_INFO.ringvco_fd_ref_cnt_lv());	//CSR38[11:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setringvco_fd_fb_cnt_dv(uint val){
	fill_csr_bits(val,REG_INFO.ringvco_fd_fb_cnt_dv());	//CSR39[13:12]
	return *this;
}
uint
CSDBG_clkRegs::getringvco_fd_fb_cnt_dv(){
	return get_csr_bits(REG_INFO.ringvco_fd_fb_cnt_dv());	//CSR39[13:12]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setringvco_fd_fb_cnt_lv(uint val){
	fill_csr_bits(val,REG_INFO.ringvco_fd_fb_cnt_lv());	//CSR39[11:0]
	return *this;
}
uint
CSDBG_clkRegs::getringvco_fd_fb_cnt_lv(){
	return get_csr_bits(REG_INFO.ringvco_fd_fb_cnt_lv());	//CSR39[11:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setringvco_timer_value(uint val){
	fill_csr_bits(val,REG_INFO.ringvco_timer_value());	//CSR40[14:5]
	return *this;
}
uint
CSDBG_clkRegs::getringvco_timer_value(){
	return get_csr_bits(REG_INFO.ringvco_timer_value());	//CSR40[14:5]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setringvco_timer_div_value(uint val){
	fill_csr_bits(val,REG_INFO.ringvco_timer_div_value());	//CSR40[4:2]
	return *this;
}
uint
CSDBG_clkRegs::getringvco_timer_div_value(){
	return get_csr_bits(REG_INFO.ringvco_timer_div_value());	//CSR40[4:2]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setringvco_timer_div_en(uint val){
	fill_csr_bits(val,REG_INFO.ringvco_timer_div_en());	//CSR40[1:1]
	return *this;
}
uint
CSDBG_clkRegs::getringvco_timer_div_en(){
	return get_csr_bits(REG_INFO.ringvco_timer_div_en());	//CSR40[1:1]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setringvco_timer_stop(uint val){
	fill_csr_bits(val,REG_INFO.ringvco_timer_stop());	//CSR40[0:0]
	return *this;
}
uint
CSDBG_clkRegs::getringvco_timer_stop(){
	return get_csr_bits(REG_INFO.ringvco_timer_stop());	//CSR40[0:0]
}

uint
CSDBG_clkRegs::getringvco_calib_fsm_status(){
	return get_csr_bits(REG_INFO.ringvco_calib_fsm_status());	//CSR41[15:0]
}

uint
CSDBG_clkRegs::getringvco_misc_status(){
	return get_csr_bits(REG_INFO.ringvco_misc_status());	//CSR42[15:0]
}

uint
CSDBG_clkRegs::getringvco_fd_ref_freq(){
	return get_csr_bits(REG_INFO.ringvco_fd_ref_freq());	//CSR43[11:0]
}

uint
CSDBG_clkRegs::getringvco_fd_fb_freq(){
	return get_csr_bits(REG_INFO.ringvco_fd_fb_freq());	//CSR44[11:0]
}

uint
CSDBG_clkRegs::getringvco_fd_diff_freq(){
	return get_csr_bits(REG_INFO.ringvco_fd_diff_freq());	//CSR45[12:0]
}

uint
CSDBG_clkRegs::getcsspare1(){
	return get_csr_bits(REG_INFO.csspare1());	//CSR46[15:0]
}

uint
CSDBG_clkRegs::getcsspare2(){
	return get_csr_bits(REG_INFO.csspare2());	//CSR47[15:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setmisc_calib_timer_value(uint val){
	fill_csr_bits(val,REG_INFO.misc_calib_timer_value());	//CSR48[15:4]
	return *this;
}
uint
CSDBG_clkRegs::getmisc_calib_timer_value(){
	return get_csr_bits(REG_INFO.misc_calib_timer_value());	//CSR48[15:4]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setmisc_calib_timer_div_value(uint val){
	fill_csr_bits(val,REG_INFO.misc_calib_timer_div_value());	//CSR48[3:0]
	return *this;
}
uint
CSDBG_clkRegs::getmisc_calib_timer_div_value(){
	return get_csr_bits(REG_INFO.misc_calib_timer_div_value());	//CSR48[3:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setmisc_calib_gcal_dir(uint val){
	fill_csr_bits(val,REG_INFO.misc_calib_gcal_dir());	//CSR49[15:11]
	return *this;
}
uint
CSDBG_clkRegs::getmisc_calib_gcal_dir(){
	return get_csr_bits(REG_INFO.misc_calib_gcal_dir());	//CSR49[15:11]
}

uint
CSDBG_clkRegs::getmisc_calib_fsm_state(){
	return get_csr_bits(REG_INFO.misc_calib_fsm_state());	//CSR49[10:5]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setmisc_calib_timer_stop(uint val){
	fill_csr_bits(val,REG_INFO.misc_calib_timer_stop());	//CSR49[4:4]
	return *this;
}
uint
CSDBG_clkRegs::getmisc_calib_timer_stop(){
	return get_csr_bits(REG_INFO.misc_calib_timer_stop());	//CSR49[4:4]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setmisc_calib_fsm_clr(uint val){
	fill_csr_bits(val,REG_INFO.misc_calib_fsm_clr());	//CSR49[3:3]
	return *this;
}
uint
CSDBG_clkRegs::getmisc_calib_fsm_clr(){
	return get_csr_bits(REG_INFO.misc_calib_fsm_clr());	//CSR49[3:3]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setmisc_calib_trans(uint val){
	fill_csr_bits(val,REG_INFO.misc_calib_trans());	//CSR49[2:0]
	return *this;
}
uint
CSDBG_clkRegs::getmisc_calib_trans(){
	return get_csr_bits(REG_INFO.misc_calib_trans());	//CSR49[2:0]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setfsm_sel_cs_df_refcode_disable(uint val){
	fill_csr_bits(val,REG_INFO.fsm_sel_cs_df_refcode_disable());	//CSR50[15:15]
	return *this;
}
uint
CSDBG_clkRegs::getfsm_sel_cs_df_refcode_disable(){
	return get_csr_bits(REG_INFO.fsm_sel_cs_df_refcode_disable());	//CSR50[15:15]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setpll1_itank_compvref(uint val){
	fill_csr_bits(val,REG_INFO.pll1_itank_compvref());	//CSR50[11:6]
	return *this;
}
uint
CSDBG_clkRegs::getpll1_itank_compvref(){
	return get_csr_bits(REG_INFO.pll1_itank_compvref());	//CSR50[11:6]
}

CSDBG_clkRegs&
CSDBG_clkRegs::setpll0_itank_compvref(uint val){
	fill_csr_bits(val,REG_INFO.pll0_itank_compvref());	//CSR50[5:0]
	return *this;
}
uint
CSDBG_clkRegs::getpll0_itank_compvref(){
	return get_csr_bits(REG_INFO.pll0_itank_compvref());	//CSR50[5:0]
}

uint
CSDBG_clkRegs::gettemprd(){
	return get_csr_bits(REG_INFO.temprd());	//CSR51[9:0]
}

uint
CSDBG_clkRegs::getpchnrd(){
	return get_csr_bits(REG_INFO.pchnrd());	//CSR52[9:0]
}

uint
CSDBG_clkRegs::getnchnrd(){
	return get_csr_bits(REG_INFO.nchnrd());	//CSR53[9:0]
}

uint
CSDBG_clkRegs::getpll0lvccvcocore(){
	return get_csr_bits(REG_INFO.pll0lvccvcocore());	//CSR54[9:0]
}

uint
CSDBG_clkRegs::getpll1lvccvcocore(){
	return get_csr_bits(REG_INFO.pll1lvccvcocore());	//CSR55[9:0]
}
E_HILINK_REGISTER_TYPE CSDBG_clkRegs::getType()
{
	return HILINK_PERMACRO_REGISTER;
}
