#ifndef HILINKCSDBGCLKREGS_H_
#define HILINKCSDBGCLKREGS_H_

#include <HILINK_DRIVE/HiLink_Regs_Base.h>
#define CSDBG_CLK_CSR_NUM 56

class CSDBG_clkRegs:public HILINK_Regs_Base{
protected:
	CSDBG_clkRegs();
	virtual ~CSDBG_clkRegs();

	uint& get_csr(uint csrIndex);
	virtual void get_default_MacroLaneID(T_MacroLaneID& id);

public:
	bool get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos);
	static CSDBG_clkRegs& getInstance();
	string getName();
	uint getCSRCount();
	E_HILINK_REGISTER_TYPE getType();
	uint get_HILINK_MAX_LANE_NUM();
	uint getAddressMapToHiLink(int csrIndex);

///////////////////////////////////////////////////////////////////////////

private:
	class _REG_INFO{
		public:

	/// Clockslice loss of clock detector pll1 reset. Active low.
	/// 0 = Reset loss of clock detector part
	/// 1 = Reset is not active
			const T_REG_INFO_EX& cs_lcd_1_soft_rst_n();	//CSR0[15:15]

	/// Clockslice loss of lock detector pll1 reset. Active low.
	/// 0 = Reset loss of lock detector part
	/// 1 = Reset is not active
			const T_REG_INFO_EX& cs_lld_1_soft_rst_n();	//CSR0[14:14]

	/// Clear the loss of lock detector. Active high.
			const T_REG_INFO_EX& cs_lld_clr();	//CSR0[13:13]

	/// Clear the frequency detector. Active high.
			const T_REG_INFO_EX& cs_fd_clr();	//CSR0[12:12]

	/// Clear the status of calibration. Active high.
			const T_REG_INFO_EX& cs_calib_clr();	//CSR0[11:11]

	/// Start clockslice loss of clock detector. Active rising edge.
			const T_REG_INFO_EX& cs_lcd_start();	//CSR0[10:10]

	/// Start clockslice loss of lock detector. Active rising edge.
			const T_REG_INFO_EX& cs_lld_start();	//CSR0[9:9]

	/// VCO_CAL_FSM  Alternate start bit. Used with CSCALMODE=3 and
	/// - LCVCOCALSEL=0 for PLL0 calibration
	/// - LCVCOCALSEL=1 for PLL1 calibration
			const T_REG_INFO_EX& cs_calib_start();	//CSR0[8:8]

	/// Enable clockslice loss of clock detector. Active high.
	/// 0 = Don't enable the detector, Gating the clock
	/// 1 = Enable the detector
			const T_REG_INFO_EX& cs_lcd_enable();	//CSR0[7:7]

	/// Enable clockslice loss of lock detector. Active high.
	/// 0 = Don't enable the detector, Gating the clock
	/// 1 = Enable the detector
			const T_REG_INFO_EX& cs_lld_enable();	//CSR0[6:6]

	/// Enable clockslice calibration. Active high.
	/// 0 = Don't enable calibration, Gating the clock
	/// 1 = Enable calibration
			const T_REG_INFO_EX& cs_calib_enable();	//CSR0[5:5]

	/// Clockslice loss of clock detector pll0 reset. Active low.
	/// 0 = Reset loss of clock detector part
	/// 1 = Reset is not active
			const T_REG_INFO_EX& cs_lcd_soft_rst_n();	//CSR0[4:4]

	/// Clockslice loss of lock detector pll0 reset. Active low.
	/// 0 = Reset loss of lock detector part
	/// 1 = Reset is not active
			const T_REG_INFO_EX& cs_lld_soft_rst_n();	//CSR0[3:3]

	/// Clockslice calibration reset. Active low.
	/// 0 = Reset calibration part
	/// 1 = Reset is not active
			const T_REG_INFO_EX& cs_calib_soft_rst_n();	//CSR0[2:2]

	/// Clockslice bus reset. Active low.
	/// 0 = Reset bus part
	/// 1 = Reset is not active
			const T_REG_INFO_EX& cs_bus_soft_rst_n();	//CSR0[1:1]

	/// Clockslice global reset. Active low.
	/// 0 = Reset whole digital circuit
	/// 1 = Reset is not active
			const T_REG_INFO_EX& cs_glb_soft_rst_n();	//CSR0[0:0]

	/// Clockslice analog test bus select. Select which analog signal to be brought out through analog test muxes for observation.
	/// NOT IMPLEMENTED
			const T_REG_INFO_EX& csatbsel14to0();	//CSR1[14:0]

	/// TOP_FSM[3:0] and vco_calfsm[4:0] current state 
	/// Arranged as TOP_FSM[3:0], and cs_vco_top_fsm[4:0]
			const T_REG_INFO_EX& vco_fsm_state();	//CSR2[15:7]

	/// Control direction of general purpose calibration FSM for debugging.
	/// [6]: For lock of check calibration.
	/// [5]: For maximum amplitude calibration.
	/// [4]: For band selection calibration.
	/// [3]: For frequency calibration.
	/// [2]: For minimum amplitude calibration.
	/// [1]: For initial amplitude calibration. NC
	/// [0]: For offset calibration. NC
			const T_REG_INFO_EX& cs_direction_ctrl();	//CSR2[6:0]

	/// Calibration mode configuration for band selection calibration.
			const T_REG_INFO_EX& cs_calib_mode_bdsel();	//CSR3[14:12]

	/// Calibration mode configuration for frequency calibration.
			const T_REG_INFO_EX& cs_calib_mode_freqcal();	//CSR3[11:9]

	/// Calibration mode configuration for minimum amplitude calibration.
			const T_REG_INFO_EX& cs_calib_mode_minamp();	//CSR3[8:6]

	/// Calibration mode configuration for lock of check calibration.
			const T_REG_INFO_EX& cs_calib_mode_lckchk();	//CSR3[5:3]

	/// Calibration mode configuration for maximum amplitude calibration.
			const T_REG_INFO_EX& cs_calib_mode_maxamp();	//CSR3[2:0]

	/// CS Power Sequencing FSM current state
			const T_REG_INFO_EX& cs_pwr_seq_state();	//CSR4[15:10]

	/// CS pwr_Seq_fsm completes power sequencing execution
			const T_REG_INFO_EX& cs_fsm_pwr_seq_done();	//CSR4[9:9]

	/// CS Power Sequence TBS Timer
	/// [7 = 5] thermal encoding  000_0000 to 111_1111
	/// [4 = 0] binary   0_0000 to 1_1111
	/// For lifeclock frequency of 156.25Mhz
	/// 0 to 31 =  TBS=3-34 cycles (19.2ns to  217.6ns)
	/// 32 to 63 =  TBS=35-66 cycles (224.0ns to 422.4ns)
	/// 96 to 127 =  TBS=99-130 cycles (633.6ns to 832.0 ns)
	/// ?2016 to 2047 =  TBS=2019-2050 cycles (12.921 us to  13.120 us)
	/// 4064 to 4095 =  TBS=4067-4098 cycles (26.028 us to 26.227 us)
			const T_REG_INFO_EX& cspwrseqtbstimer();	//CSR4[7:0]

	/// MISC_CAL_FSM Alternate Start bit. Used with CSCALMODE=1
	/// 1 =  Start MISC_CAL_FSM
			const T_REG_INFO_EX& misccalfsmastart();	//CSR5[15:15]

	/// DPM Detection FSM Alternate Start bit
	/// 1 =  Start DPM Detection FSM
			const T_REG_INFO_EX& dpmdetectastart();	//CSR5[14:14]

	/// DPM Detection FSM clear.
			const T_REG_INFO_EX& dpmdetfsmclr();	//CSR5[13:13]

	/// Output of clockslice's comparator.
			const T_REG_INFO_EX& compstatus();	//CSR5[12:12]

	/// Comparator Vref generator target select bits :
	/// Setting = 400mV + (6.25mV x  COMPVREFSEL)  
	/// 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
			const T_REG_INFO_EX& compvrefseltarget();	//CSR5[5:0]

	/// Define maximum calibration control code for minimum amplitude calibration.
			const T_REG_INFO_EX& cs_ctrl_code_max_minamp();	//CSR6[14:10]

	/// Define minimum calibration control codefor minimum amplitude calibration.
			const T_REG_INFO_EX& cs_ctrl_code_min_minamp();	//CSR6[9:5]

	/// Define maximum calibration control code for initial amplitude calibration.
			const T_REG_INFO_EX& cs_ctrl_code_max_initamp();	//CSR6[4:0]

	/// Define minimum calibration control code for band selection calibration.
			const T_REG_INFO_EX& cs_ctrl_code_min_bdsel();	//CSR7[14:10]

	/// Define maximum calibration control code for frequency calibration.
			const T_REG_INFO_EX& cs_ctrl_code_max_freqcal();	//CSR7[9:5]

	/// Define minimum calibration control code for frequency calibration.
			const T_REG_INFO_EX& cs_ctrl_code_min_freqcal();	//CSR7[4:0]

	/// Define maximum calibration control code for maximum amplitude calibration.
			const T_REG_INFO_EX& cs_ctrl_code_max_maxamp();	//CSR8[14:10]

	/// Define minimum calibration control code for maximum amplitude calibration.
			const T_REG_INFO_EX& cs_ctrl_code_min_maxamp();	//CSR8[9:5]

	/// Define maximum calibration control code for band selection calibration.
			const T_REG_INFO_EX& cs_ctrl_code_max_bdsel();	//CSR8[4:0]

	/// Define maximum calibration control code for lock of check calibration.
			const T_REG_INFO_EX& cs_ctrl_code_max_lckchk();	//CSR9[9:5]

	/// Define minimum calibration control codefor lock of check calibration.
			const T_REG_INFO_EX& cs_ctrl_code_min_lckchk();	//CSR9[4:0]

	/// The solution flag of the first VCO calibration run.
	/// 0: No solution found in the first VCO calibration run
	/// ;1: Solution was found in the first VCO calibration run.
	/// 
	/// If the V101 top VCO calibration FSM is enabled (V101 mode), it's the solution flag of the first VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
	/// 
	/// If the V101 top VCO calibration FSM is disabled (V100 mode), there is no second run, it's the solution flag of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
			const T_REG_INFO_EX& firstsolnflag();	//CSR10[15:15]

	/// The band sel of the first VCO calibration run.
	/// 
	/// If the V101 top VCO calibration FSM is enabled (V101 mode), it's the band sel of the first VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
	/// 
	/// If the V101 top VCO calibration FSM is disabled (V100 mode), there is no second run, it's the band sel of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
			const T_REG_INFO_EX& firstbdsel();	//CSR10[12:10]

	/// The point 1 freqcal of the first VCO calibration run.
	/// 
	/// If the V101 top VCO calibration FSM is enabled (V101 mode), it's the point 1 freqcal of the first VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
	/// 
	/// If the V101 top VCO calibration FSM is disabled (V100 mode), there is no second run, it's the point 1 freqcal of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
			const T_REG_INFO_EX& firstfreqcalp1();	//CSR10[9:5]

	/// The point 2 freqcal of the first VCO calibration run.
	/// 
	/// If the V101 top VCO calibration FSM is enabled (V101 mode), it's the point 2 freqcal of the first VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
	/// 
	/// If the V101 top VCO calibration FSM is disabled (V100 mode), there is no second run, it's the point 2 freqcal of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
			const T_REG_INFO_EX& firstfreqcalp2();	//CSR10[4:0]

	/// The solution flag of the second VCO calibration run. It only applies to the V101 mode (i.e., the V101 top VCO calibration FSM is enabled) since there no second run.
	/// 
	/// 0: No solution found in the second VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected
	/// ;1: Solution was found in the second VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
			const T_REG_INFO_EX& secondsolnflag();	//CSR11[15:15]

	/// The band sel of the second VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected. It only applies to the V101 mode (i.e., the V101 top VCO calibration FSM is enabled) since there no second run.
			const T_REG_INFO_EX& secondbdsel();	//CSR11[12:10]

	/// The point 1 freqcal of the second VCO calibration run or the first edge point freqcal.
	/// 
	/// In the V101 mode (i.e., the V101 top VCO calibration FSM is enabled), if there is a solution found in the second VCO calibration run, it's the point 2 freqcal of the second VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected. Otherwise, it's the first edge point freqcal of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
	/// 
	/// In the V100 mode (i.e., the V101 top VCO calibration FSM is disabled), there is no second run, it's the edge point freqcal of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
			const T_REG_INFO_EX& secondfreqcalp1();	//CSR11[9:5]

	/// The point 2 freqcal of the second VCO calibration run. It only applies to the V101 mode (i.e., the V101 top VCO calibration FSM is enabled). If there is a solution found in the second VCO calibration run, it's the point 2 freqcal of the second VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected. Otherwise, it's the second edge point freqcal of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
			const T_REG_INFO_EX& secondfreqcalp2();	//CSR11[4:0]

	/// Define initial calibration control code for lock of check calibration.
			const T_REG_INFO_EX& cs_init_code_lckchk();	//CSR12[4:0]

	/// Configure the maximum transitions for minimum amplitude calibration.
			const T_REG_INFO_EX& cs_trans_max_minamp();	//CSR13[11:8]

	/// Configure the maximum EVEN transitions only for frequency calibration: 2/4/8/16 to accumulate fd_diff count by 1/2/4/8 times
			const T_REG_INFO_EX& cs_trans_max_freqcal();	//CSR13[4:0]

	/// Configure the maximum transitions for lock of check calibration.
			const T_REG_INFO_EX& cs_trans_max_lckchk();	//CSR14[11:8]

	/// Configure the maximum transitions for maximum amplitude calibration.
			const T_REG_INFO_EX& cs_trans_max_maxamp();	//CSR14[7:4]

	/// Configure the maximum transitions for band selection calibration.
			const T_REG_INFO_EX& cs_trans_max_bdsel();	//CSR14[3:0]

	/// Define the threshold of frequency detector. If abs[number of refclk cycle - number of fbclk cycle] less than threshold, it would indicate that PLL is locked.
			const T_REG_INFO_EX& cs_fd_threshold();	//CSR15[10:1]

	/// When loss of lock detecting, it could enable timer for waiting specified time.
	/// 0 = disable
	/// 1 = enable
			const T_REG_INFO_EX& cs_meas_fd_wait();	//CSR15[0:0]

	/// Define the decrease value of reference clock counter.
			const T_REG_INFO_EX& cs_fd_ref_cnt_dv();	//CSR16[15:14]

	/// The initial value of reference and feedback clock counter.
	/// Note: modified to program low resolution
			const T_REG_INFO_EX& cs_fd_ref_cnt_lv();	//CSR16[13:0]

	/// Define the decrease value of feedback clock counter.
			const T_REG_INFO_EX& cs_fd_fb_cnt_dv();	//CSR17[15:14]

	/// The initial value of high resolution count for reference and feedback clock counters.
	/// Note: modified to program high resolution
			const T_REG_INFO_EX& cs_fd_fb_cnt_lv();	//CSR17[13:0]

	/// Configuration of timer for waiting, which is the cycles of reference clock. Timer is controlled by cs_vco_top_fsm during itank calibration. At the beginning of each GCAL control code, the timer is loaded with this value and counts down. When the timer expires, GCAL checks for comparator output changes.
			const T_REG_INFO_EX& cs_timer_value();	//CSR18[14:5]

	/// Configuration of divider in timer.
			const T_REG_INFO_EX& cs_timer_div_value();	//CSR18[4:2]

	/// Currently NOT used
			const T_REG_INFO_EX& cs_timer_div_en();	//CSR18[1:1]

	/// Stop timer, for debugging.
	/// 0 = normal
	/// 1 = stop the timer
			const T_REG_INFO_EX& cs_timer_stop();	//CSR18[0:0]

	/// The divider of feedback clock for loss of lock detector.
			const T_REG_INFO_EX& cs_lld_fb_div_ratio();	//CSR19[3:1]

	/// The LLD operation manner:
	/// 0 = operate always.
	/// 1 = Perform loss of lock one time then halt.
			const T_REG_INFO_EX& cs_lld_once();	//CSR19[0:0]

	/// The decrease value of reference clock counter.
			const T_REG_INFO_EX& cs_lld_ref_cnt_dv();	//CSR20[14:12]

	/// The initial value of reference clock counter.
			const T_REG_INFO_EX& cs_lld_ref_cnt_lv();	//CSR20[11:0]

	/// The decrease value of feedback clock counter.
			const T_REG_INFO_EX& cs_lld_fb_cnt_dv();	//CSR21[14:12]

	/// The initial value of feedback clock counter.
			const T_REG_INFO_EX& cs_lld_fb_cnt_lv();	//CSR21[11:0]

	/// The divider of feedback clock of loss of clock.
	/// (Note: A value less the 0x4 will cause False alarm )
			const T_REG_INFO_EX& cs_lcd_fb_div_ratio();	//CSR22[9:1]

	/// Override the status of loss of clock.
	/// 0 = normal
	/// 1 = override
			const T_REG_INFO_EX& cs_lcd_override();	//CSR22[0:0]

	/// The initial value of feedback clock counter.
			const T_REG_INFO_EX& cs_lcd_fb_cnt_lv();	//CSR23[11:0]

	/// The point 1 fd_diff of the first VCO calibration run. Unsigned value.
	/// 
	/// If the V101 top VCO calibration FSM is enabled (V101 mode), it's the point 1 fd_diff of the first VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
	/// 
	/// If the V101 top VCO calibration FSM is disabled (V100 mode), there is no second run, it's the point 1 fd_diff of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
			const T_REG_INFO_EX& firstfddiffp1();	//CSR24[14:0]

	/// The point 2 fd diff of the first VCO calibration run. Unsigned value.
	/// 
	/// If the V101 top VCO calibration FSM is enabled (V101 mode), it's the point 2 fd diff of the first VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
	/// 
	/// If the V101 top VCO calibration FSM is disabled (V100 mode), there is no second run, it's the point 2 fd diff of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
			const T_REG_INFO_EX& firstfddiffp2();	//CSR25[14:0]

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
			const T_REG_INFO_EX& cs_debugging_ctrl1();	//CSR26[15:0]

	/// The status of VCO calibration.
	/// 0 = incomplete
	/// 1 = complete.
			const T_REG_INFO_EX& cs_calib_done();	//CSR27[15:15]

	/// VCO calibration result status
	/// 0 = failure
	/// 1 = success.
			const T_REG_INFO_EX& cs_calib_success();	//CSR27[14:14]

	/// The reference clock counter of loss of lock detector.
			const T_REG_INFO_EX& cs_lld_ref_freq();	//CSR27[11:0]

	/// The point 1 fd diff of the second VCO calibration run or the first edge point fd diff. Unsigned value.
	/// 
	/// In the V101 mode (i.e., the V101 top VCO calibration FSM is enabled), if there is a solution found in the second VCO calibration run, it's the point 2 fd diff of the second VCO 
	/// calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected. Otherwise, it's the first edge point fd diff of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
	/// 
	/// In the V100 mode (i.e., the V101 top VCO calibration FSM is disabled), there is no second run, it's the edge point fd diff of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected.
			const T_REG_INFO_EX& secondfddiffp1();	//CSR28[14:0]

	/// The point 2 fd diff of the second VCO calibration run. It only applies to the V101 mode (i.e., the V101 top VCO calibration FSM is enabled). If there is a solution found in the second VCO calibration run, it's the point 2 fd diff of the second VCO calibration run of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected. Otherwise, it's the second edge point fd diff of either the second VCO calibration pass or the first VCO calibration pass if the second VCO calibration pass is not selected. Unsigned value.
			const T_REG_INFO_EX& secondfddiffp2();	//CSR29[14:0]

	/// Pll0/1 fd_diff count of selected bdsel and freqcal. Unsigned value.
	/// 
	/// Note: 0x7FFF is the power up default (ie, freqcal point does not exist)
			const T_REG_INFO_EX& cs_fd_diff_freq();	//CSR30[14:0]

	/// The status of loss of lock.
	/// 0 = incomplete
	/// 1 = complete
			const T_REG_INFO_EX& cs_lld_done();	//CSR31[15:15]

	/// The difference of reference clock counter and feedback clock counter for loss of lock detector.
			const T_REG_INFO_EX& cs_lld_diff_freq();	//CSR31[12:0]

	/// The feedback clock counter of loss of lock detector.
			const T_REG_INFO_EX& cs_lld_fb_freq();	//CSR32[11:0]

	/// VCO CAL Miscellaneous Status:
	/// [15] = Loss of fb clock. Indicate during VCO calibration, the fb clock was ever lost.
	/// [14:10] = Reserved
	/// [9] =  pll0/1_fd_status: fd_diff cnt meets threshold (v100/v101)
	/// [8:5] =  transition counter output
	/// [4] =  transition warning
	/// [3:1] =  vcm fsm calib mode
	/// [0] = shared pll0/1 calrstb
			const T_REG_INFO_EX& cs_misc_status();	//CSR33[15:0]

	/// VCO CAL FSM Status:
	/// [15:14] = Not used.
	/// [13] = vcofsm shared pll0/1 calib state error (v100 mode only)
	/// [12:0] = vcofsm shared pll0/1 calib state flag (v100 mode only)
			const T_REG_INFO_EX& cs_calib_fsm_status();	//CSR34[15:0]

	/// VCO GCAL FSM Status:
	/// [15:13]: The bdsel when the fb clock got lost during the VCO calibration
	/// ;[12:8]: The freqcal when the fb clock got lost during the VCO calibration
	/// ;[7]: shared pll0/1 gcal error (due to internal state error
	/// [6]: shared pll0/1 gcal transition status
	/// [5:0]: shared pll0/1 gcal state flag
			const T_REG_INFO_EX& cs_gcalib_fsm_status();	//CSR35[15:0]

	/// 0 = auto
	/// 1 = manual
			const T_REG_INFO_EX& ringvco_calib_mode();	//CSR36[15:15]

	/// Start ring VCO calibration. Active rising edge.
			const T_REG_INFO_EX& ringvco_calib_start();	//CSR36[14:14]

	/// Not used
			const T_REG_INFO_EX& ringvco_calib_done();	//CSR36[5:5]

	/// Not used
			const T_REG_INFO_EX& ringvco_calib_err();	//CSR36[4:4]

	/// Not used
			const T_REG_INFO_EX& ringvco_autotune_status();	//CSR36[3:0]

	/// Start Ring VCO frequency detector. Active high.
			const T_REG_INFO_EX& ringvco_fd_start();	//CSR37[15:15]

	/// Clear the frequency detector. Active high.
			const T_REG_INFO_EX& ringvco_fd_clr();	//CSR37[14:14]

	/// Define the threshold of frequency detector. If abs[number of refclk cycle - number of fbclk cycle] less than threshold, it would indicate that PLL is locked.
			const T_REG_INFO_EX& ringvco_fd_threshold();	//CSR37[9:0]

	/// Define the decrease value of reference clock counter.
			const T_REG_INFO_EX& ringvco_fd_ref_cnt_dv();	//CSR38[13:12]

	/// The initial value of reference clock counter.
			const T_REG_INFO_EX& ringvco_fd_ref_cnt_lv();	//CSR38[11:0]

	/// Define the decrease value of feedback clock counter.
			const T_REG_INFO_EX& ringvco_fd_fb_cnt_dv();	//CSR39[13:12]

	/// The initial value of feedback clock counter.
			const T_REG_INFO_EX& ringvco_fd_fb_cnt_lv();	//CSR39[11:0]

	/// Not used
			const T_REG_INFO_EX& ringvco_timer_value();	//CSR40[14:5]

	/// Not used
			const T_REG_INFO_EX& ringvco_timer_div_value();	//CSR40[4:2]

	/// Not used
			const T_REG_INFO_EX& ringvco_timer_div_en();	//CSR40[1:1]

	/// Not used
			const T_REG_INFO_EX& ringvco_timer_stop();	//CSR40[0:0]

	/// The status of calibration FSM for debugging purpose. Following internal signals could be read back.
	/// [15:12]= vcoctrl
	/// [11:4]=IDAC code (driven by FSM)
	/// [3:0]= FSM encoded current state
			const T_REG_INFO_EX& ringvco_calib_fsm_status();	//CSR41[15:0]

	/// Ring VCO Misc Calibration Status:
	/// [15-9]=unused
	/// [8]=FD status
	/// [7:0]=IDAC code used for DPM processing. Driven by FSM or MOSDETIOSCDACCAL (CS_CSR41[7:0]) based on RINGVCO_CALIB_MODE (DBG_CSR-36) setting.
			const T_REG_INFO_EX& ringvco_misc_status();	//CSR42[15:0]

	/// The reference clock counter of frequency detector.
			const T_REG_INFO_EX& ringvco_fd_ref_freq();	//CSR43[11:0]

	/// The feedback clock counter of frequency detector.
			const T_REG_INFO_EX& ringvco_fd_fb_freq();	//CSR44[11:0]

	/// The difference of reference clock counter and feedback clock counter for frequency detector.
			const T_REG_INFO_EX& ringvco_fd_diff_freq();	//CSR45[12:0]

	/// 
			const T_REG_INFO_EX& csspare1();	//CSR46[15:0]

	/// 
			const T_REG_INFO_EX& csspare2();	//CSR47[15:0]

	/// Configuration of timer for waiting, which is the cycles of reference clock.
			const T_REG_INFO_EX& misc_calib_timer_value();	//CSR48[15:4]

	/// Configuration of divider in timer, for debugging.
			const T_REG_INFO_EX& misc_calib_timer_div_value();	//CSR48[3:0]

	/// MISC_CALIB_GCAL_DIR[4]: ADC BGV
	/// MISC_CALIB_GCAL_DIR[3]: RX term
	/// MISC_CALIB_GCAL_DIR[2]: vref
	/// MISC_CALIB_GCAL_DIR[1]: vreg
	/// MISC_CALIB_GCAL_DIR[0]: vref_gen
			const T_REG_INFO_EX& misc_calib_gcal_dir();	//CSR49[15:11]

	/// MISC CALIB FSM internal state for debug purpose
			const T_REG_INFO_EX& misc_calib_fsm_state();	//CSR49[10:5]

	/// Stop timer for debug purpose
	/// 0: Normal
	/// 1: Stop timer
			const T_REG_INFO_EX& misc_calib_timer_stop();	//CSR49[4:4]

	/// Clear MISC CALIB FSM 
	/// 0: Normal
	/// 1: Stop FSM
			const T_REG_INFO_EX& misc_calib_fsm_clr();	//CSR49[3:3]

	/// Number of Transition applied to MISC_CALIB_TASK 0 to 10
			const T_REG_INFO_EX& misc_calib_trans();	//CSR49[2:0]

	/// 0=Enable fsm to select reference value from DF_code_mapper 
	/// 1=Disable fsm from selecting reference value generated by DF_code_mapper, hence CSDFREFCODE (csr50) is selected as reference for cs df comparator status during calibration or dpm finetuning
			const T_REG_INFO_EX& fsm_sel_cs_df_refcode_disable();	//CSR50[15:15]

	/// PLL1 CS Comparator voltage reference for itank calibration.  The following setting will be added/subtracted with VREFGENOFFSET before sending out on comp_vref_sel port during itank calibration.
	/// Setting = 400mV + (6.25mV x PLL0_ITANK_COMPVREF) 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
			const T_REG_INFO_EX& pll1_itank_compvref();	//CSR50[11:6]

	/// PLL0 CS Comparator voltage reference for itank calibration.  The following setting will be added/subtracted with VREFGENOFFSET before sending out on comp_vref_sel port during itank calibration.
	/// Setting = 400mV + (6.25mV x PLL0_ITANK_COMPVREF) 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
			const T_REG_INFO_EX& pll0_itank_compvref();	//CSR50[5:0]

	/// Temperature Reading
			const T_REG_INFO_EX& temprd();	//CSR51[9:0]

	/// P-Channel Vth Reading
			const T_REG_INFO_EX& pchnrd();	//CSR52[9:0]

	/// N-Channel Vth Reading
			const T_REG_INFO_EX& nchnrd();	//CSR53[9:0]

	/// PLL0 LVCC_VCO_CORE Voltage Reading
			const T_REG_INFO_EX& pll0lvccvcocore();	//CSR54[9:0]

	/// PLL1 LVCC_VCO_CORE Voltage Reading
			const T_REG_INFO_EX& pll1lvccvcocore();	//CSR55[9:0]
			bool get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos);
	};
public:
	_REG_INFO REG_INFO;

	uint csr[CSDBG_CLK_CSR_NUM];


	//CSR0[15:15]
	CSDBG_clkRegs& setcs_lcd_1_soft_rst_n(uint val);
	uint getcs_lcd_1_soft_rst_n();

	//CSR0[14:14]
	CSDBG_clkRegs& setcs_lld_1_soft_rst_n(uint val);
	uint getcs_lld_1_soft_rst_n();

	//CSR0[13:13]
	CSDBG_clkRegs& setcs_lld_clr(uint val);
	uint getcs_lld_clr();

	//CSR0[12:12]
	CSDBG_clkRegs& setcs_fd_clr(uint val);
	uint getcs_fd_clr();

	//CSR0[11:11]
	CSDBG_clkRegs& setcs_calib_clr(uint val);
	uint getcs_calib_clr();

	//CSR0[10:10]
	CSDBG_clkRegs& setcs_lcd_start(uint val);
	uint getcs_lcd_start();

	//CSR0[9:9]
	CSDBG_clkRegs& setcs_lld_start(uint val);
	uint getcs_lld_start();

	//CSR0[8:8]
	CSDBG_clkRegs& setcs_calib_start(uint val);
	uint getcs_calib_start();

	//CSR0[7:7]
	CSDBG_clkRegs& setcs_lcd_enable(uint val);
	uint getcs_lcd_enable();

	//CSR0[6:6]
	CSDBG_clkRegs& setcs_lld_enable(uint val);
	uint getcs_lld_enable();

	//CSR0[5:5]
	CSDBG_clkRegs& setcs_calib_enable(uint val);
	uint getcs_calib_enable();

	//CSR0[4:4]
	CSDBG_clkRegs& setcs_lcd_soft_rst_n(uint val);
	uint getcs_lcd_soft_rst_n();

	//CSR0[3:3]
	CSDBG_clkRegs& setcs_lld_soft_rst_n(uint val);
	uint getcs_lld_soft_rst_n();

	//CSR0[2:2]
	CSDBG_clkRegs& setcs_calib_soft_rst_n(uint val);
	uint getcs_calib_soft_rst_n();

	//CSR0[1:1]
	CSDBG_clkRegs& setcs_bus_soft_rst_n(uint val);
	uint getcs_bus_soft_rst_n();

	//CSR0[0:0]
	CSDBG_clkRegs& setcs_glb_soft_rst_n(uint val);
	uint getcs_glb_soft_rst_n();

	//CSR1[14:0]
	CSDBG_clkRegs& setcsatbsel14to0(uint val);
	uint getcsatbsel14to0();

	//CSR2[15:7]
	uint getvco_fsm_state();

	//CSR2[6:0]
	CSDBG_clkRegs& setcs_direction_ctrl(uint val);
	uint getcs_direction_ctrl();

	//CSR3[14:12]
	CSDBG_clkRegs& setcs_calib_mode_bdsel(uint val);
	uint getcs_calib_mode_bdsel();

	//CSR3[11:9]
	CSDBG_clkRegs& setcs_calib_mode_freqcal(uint val);
	uint getcs_calib_mode_freqcal();

	//CSR3[8:6]
	CSDBG_clkRegs& setcs_calib_mode_minamp(uint val);
	uint getcs_calib_mode_minamp();

	//CSR3[5:3]
	CSDBG_clkRegs& setcs_calib_mode_lckchk(uint val);
	uint getcs_calib_mode_lckchk();

	//CSR3[2:0]
	CSDBG_clkRegs& setcs_calib_mode_maxamp(uint val);
	uint getcs_calib_mode_maxamp();

	//CSR4[15:10]
	uint getcs_pwr_seq_state();

	//CSR4[9:9]
	uint getcs_fsm_pwr_seq_done();

	//CSR4[7:0]
	CSDBG_clkRegs& setcspwrseqtbstimer(uint val);
	uint getcspwrseqtbstimer();

	//CSR5[15:15]
	CSDBG_clkRegs& setmisccalfsmastart(uint val);
	uint getmisccalfsmastart();

	//CSR5[14:14]
	CSDBG_clkRegs& setdpmdetectastart(uint val);
	uint getdpmdetectastart();

	//CSR5[13:13]
	CSDBG_clkRegs& setdpmdetfsmclr(uint val);
	uint getdpmdetfsmclr();

	//CSR5[12:12]
	uint getcompstatus();

	//CSR5[5:0]
	CSDBG_clkRegs& setcompvrefseltarget(uint val);
	uint getcompvrefseltarget();

	//CSR6[14:10]
	CSDBG_clkRegs& setcs_ctrl_code_max_minamp(uint val);
	uint getcs_ctrl_code_max_minamp();

	//CSR6[9:5]
	CSDBG_clkRegs& setcs_ctrl_code_min_minamp(uint val);
	uint getcs_ctrl_code_min_minamp();

	//CSR6[4:0]
	CSDBG_clkRegs& setcs_ctrl_code_max_initamp(uint val);
	uint getcs_ctrl_code_max_initamp();

	//CSR7[14:10]
	CSDBG_clkRegs& setcs_ctrl_code_min_bdsel(uint val);
	uint getcs_ctrl_code_min_bdsel();

	//CSR7[9:5]
	CSDBG_clkRegs& setcs_ctrl_code_max_freqcal(uint val);
	uint getcs_ctrl_code_max_freqcal();

	//CSR7[4:0]
	CSDBG_clkRegs& setcs_ctrl_code_min_freqcal(uint val);
	uint getcs_ctrl_code_min_freqcal();

	//CSR8[14:10]
	CSDBG_clkRegs& setcs_ctrl_code_max_maxamp(uint val);
	uint getcs_ctrl_code_max_maxamp();

	//CSR8[9:5]
	CSDBG_clkRegs& setcs_ctrl_code_min_maxamp(uint val);
	uint getcs_ctrl_code_min_maxamp();

	//CSR8[4:0]
	CSDBG_clkRegs& setcs_ctrl_code_max_bdsel(uint val);
	uint getcs_ctrl_code_max_bdsel();

	//CSR9[9:5]
	CSDBG_clkRegs& setcs_ctrl_code_max_lckchk(uint val);
	uint getcs_ctrl_code_max_lckchk();

	//CSR9[4:0]
	CSDBG_clkRegs& setcs_ctrl_code_min_lckchk(uint val);
	uint getcs_ctrl_code_min_lckchk();

	//CSR10[15:15]
	uint getfirstsolnflag();

	//CSR10[12:10]
	uint getfirstbdsel();

	//CSR10[9:5]
	uint getfirstfreqcalp1();

	//CSR10[4:0]
	uint getfirstfreqcalp2();

	//CSR11[15:15]
	uint getsecondsolnflag();

	//CSR11[12:10]
	uint getsecondbdsel();

	//CSR11[9:5]
	uint getsecondfreqcalp1();

	//CSR11[4:0]
	uint getsecondfreqcalp2();

	//CSR12[4:0]
	CSDBG_clkRegs& setcs_init_code_lckchk(uint val);
	uint getcs_init_code_lckchk();

	//CSR13[11:8]
	CSDBG_clkRegs& setcs_trans_max_minamp(uint val);
	uint getcs_trans_max_minamp();

	//CSR13[4:0]
	CSDBG_clkRegs& setcs_trans_max_freqcal(uint val);
	uint getcs_trans_max_freqcal();

	//CSR14[11:8]
	CSDBG_clkRegs& setcs_trans_max_lckchk(uint val);
	uint getcs_trans_max_lckchk();

	//CSR14[7:4]
	CSDBG_clkRegs& setcs_trans_max_maxamp(uint val);
	uint getcs_trans_max_maxamp();

	//CSR14[3:0]
	CSDBG_clkRegs& setcs_trans_max_bdsel(uint val);
	uint getcs_trans_max_bdsel();

	//CSR15[10:1]
	CSDBG_clkRegs& setcs_fd_threshold(uint val);
	uint getcs_fd_threshold();

	//CSR15[0:0]
	CSDBG_clkRegs& setcs_meas_fd_wait(uint val);
	uint getcs_meas_fd_wait();

	//CSR16[15:14]
	CSDBG_clkRegs& setcs_fd_ref_cnt_dv(uint val);
	uint getcs_fd_ref_cnt_dv();

	//CSR16[13:0]
	CSDBG_clkRegs& setcs_fd_ref_cnt_lv(uint val);
	uint getcs_fd_ref_cnt_lv();

	//CSR17[15:14]
	CSDBG_clkRegs& setcs_fd_fb_cnt_dv(uint val);
	uint getcs_fd_fb_cnt_dv();

	//CSR17[13:0]
	CSDBG_clkRegs& setcs_fd_fb_cnt_lv(uint val);
	uint getcs_fd_fb_cnt_lv();

	//CSR18[14:5]
	CSDBG_clkRegs& setcs_timer_value(uint val);
	uint getcs_timer_value();

	//CSR18[4:2]
	CSDBG_clkRegs& setcs_timer_div_value(uint val);
	uint getcs_timer_div_value();

	//CSR18[1:1]
	CSDBG_clkRegs& setcs_timer_div_en(uint val);
	uint getcs_timer_div_en();

	//CSR18[0:0]
	CSDBG_clkRegs& setcs_timer_stop(uint val);
	uint getcs_timer_stop();

	//CSR19[3:1]
	CSDBG_clkRegs& setcs_lld_fb_div_ratio(uint val);
	uint getcs_lld_fb_div_ratio();

	//CSR19[0:0]
	CSDBG_clkRegs& setcs_lld_once(uint val);
	uint getcs_lld_once();

	//CSR20[14:12]
	CSDBG_clkRegs& setcs_lld_ref_cnt_dv(uint val);
	uint getcs_lld_ref_cnt_dv();

	//CSR20[11:0]
	CSDBG_clkRegs& setcs_lld_ref_cnt_lv(uint val);
	uint getcs_lld_ref_cnt_lv();

	//CSR21[14:12]
	CSDBG_clkRegs& setcs_lld_fb_cnt_dv(uint val);
	uint getcs_lld_fb_cnt_dv();

	//CSR21[11:0]
	CSDBG_clkRegs& setcs_lld_fb_cnt_lv(uint val);
	uint getcs_lld_fb_cnt_lv();

	//CSR22[9:1]
	CSDBG_clkRegs& setcs_lcd_fb_div_ratio(uint val);
	uint getcs_lcd_fb_div_ratio();

	//CSR22[0:0]
	CSDBG_clkRegs& setcs_lcd_override(uint val);
	uint getcs_lcd_override();

	//CSR23[11:0]
	CSDBG_clkRegs& setcs_lcd_fb_cnt_lv(uint val);
	uint getcs_lcd_fb_cnt_lv();

	//CSR24[14:0]
	uint getfirstfddiffp1();

	//CSR25[14:0]
	uint getfirstfddiffp2();

	//CSR26[15:0]
	CSDBG_clkRegs& setcs_debugging_ctrl1(uint val);
	uint getcs_debugging_ctrl1();

	//CSR27[15:15]
	uint getcs_calib_done();

	//CSR27[14:14]
	uint getcs_calib_success();

	//CSR27[11:0]
	uint getcs_lld_ref_freq();

	//CSR28[14:0]
	uint getsecondfddiffp1();

	//CSR29[14:0]
	uint getsecondfddiffp2();

	//CSR30[14:0]
	uint getcs_fd_diff_freq();

	//CSR31[15:15]
	uint getcs_lld_done();

	//CSR31[12:0]
	uint getcs_lld_diff_freq();

	//CSR32[11:0]
	uint getcs_lld_fb_freq();

	//CSR33[15:0]
	uint getcs_misc_status();

	//CSR34[15:0]
	uint getcs_calib_fsm_status();

	//CSR35[15:0]
	uint getcs_gcalib_fsm_status();

	//CSR36[15:15]
	CSDBG_clkRegs& setringvco_calib_mode(uint val);
	uint getringvco_calib_mode();

	//CSR36[14:14]
	CSDBG_clkRegs& setringvco_calib_start(uint val);
	uint getringvco_calib_start();

	//CSR36[5:5]
	uint getringvco_calib_done();

	//CSR36[4:4]
	uint getringvco_calib_err();

	//CSR36[3:0]
	uint getringvco_autotune_status();

	//CSR37[15:15]
	CSDBG_clkRegs& setringvco_fd_start(uint val);
	uint getringvco_fd_start();

	//CSR37[14:14]
	CSDBG_clkRegs& setringvco_fd_clr(uint val);
	uint getringvco_fd_clr();

	//CSR37[9:0]
	CSDBG_clkRegs& setringvco_fd_threshold(uint val);
	uint getringvco_fd_threshold();

	//CSR38[13:12]
	CSDBG_clkRegs& setringvco_fd_ref_cnt_dv(uint val);
	uint getringvco_fd_ref_cnt_dv();

	//CSR38[11:0]
	CSDBG_clkRegs& setringvco_fd_ref_cnt_lv(uint val);
	uint getringvco_fd_ref_cnt_lv();

	//CSR39[13:12]
	CSDBG_clkRegs& setringvco_fd_fb_cnt_dv(uint val);
	uint getringvco_fd_fb_cnt_dv();

	//CSR39[11:0]
	CSDBG_clkRegs& setringvco_fd_fb_cnt_lv(uint val);
	uint getringvco_fd_fb_cnt_lv();

	//CSR40[14:5]
	CSDBG_clkRegs& setringvco_timer_value(uint val);
	uint getringvco_timer_value();

	//CSR40[4:2]
	CSDBG_clkRegs& setringvco_timer_div_value(uint val);
	uint getringvco_timer_div_value();

	//CSR40[1:1]
	CSDBG_clkRegs& setringvco_timer_div_en(uint val);
	uint getringvco_timer_div_en();

	//CSR40[0:0]
	CSDBG_clkRegs& setringvco_timer_stop(uint val);
	uint getringvco_timer_stop();

	//CSR41[15:0]
	uint getringvco_calib_fsm_status();

	//CSR42[15:0]
	uint getringvco_misc_status();

	//CSR43[11:0]
	uint getringvco_fd_ref_freq();

	//CSR44[11:0]
	uint getringvco_fd_fb_freq();

	//CSR45[12:0]
	uint getringvco_fd_diff_freq();

	//CSR46[15:0]
	uint getcsspare1();

	//CSR47[15:0]
	uint getcsspare2();

	//CSR48[15:4]
	CSDBG_clkRegs& setmisc_calib_timer_value(uint val);
	uint getmisc_calib_timer_value();

	//CSR48[3:0]
	CSDBG_clkRegs& setmisc_calib_timer_div_value(uint val);
	uint getmisc_calib_timer_div_value();

	//CSR49[15:11]
	CSDBG_clkRegs& setmisc_calib_gcal_dir(uint val);
	uint getmisc_calib_gcal_dir();

	//CSR49[10:5]
	uint getmisc_calib_fsm_state();

	//CSR49[4:4]
	CSDBG_clkRegs& setmisc_calib_timer_stop(uint val);
	uint getmisc_calib_timer_stop();

	//CSR49[3:3]
	CSDBG_clkRegs& setmisc_calib_fsm_clr(uint val);
	uint getmisc_calib_fsm_clr();

	//CSR49[2:0]
	CSDBG_clkRegs& setmisc_calib_trans(uint val);
	uint getmisc_calib_trans();

	//CSR50[15:15]
	CSDBG_clkRegs& setfsm_sel_cs_df_refcode_disable(uint val);
	uint getfsm_sel_cs_df_refcode_disable();

	//CSR50[11:6]
	CSDBG_clkRegs& setpll1_itank_compvref(uint val);
	uint getpll1_itank_compvref();

	//CSR50[5:0]
	CSDBG_clkRegs& setpll0_itank_compvref(uint val);
	uint getpll0_itank_compvref();

	//CSR51[9:0]
	uint gettemprd();

	//CSR52[9:0]
	uint getpchnrd();

	//CSR53[9:0]
	uint getnchnrd();

	//CSR54[9:0]
	uint getpll0lvccvcocore();

	//CSR55[9:0]
	uint getpll1lvccvcocore();

};

#endif // HILINKCSDBGCLKREGS_H_
