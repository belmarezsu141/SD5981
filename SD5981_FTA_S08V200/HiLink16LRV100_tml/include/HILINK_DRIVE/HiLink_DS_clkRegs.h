#ifndef HILINKDSCLKREGS_H_
#define HILINKDSCLKREGS_H_

#include "HiLink_Regs_Base.h"
#define DS_CLK_CSR_NUM 50

class DS_clkRegs:public HILINK_Regs_Base{
protected:
	DS_clkRegs();
	virtual ~DS_clkRegs();

	uint& get_csr(uint csrIndex);
	virtual void get_default_MacroLaneID(T_MacroLaneID& id);

public:
	bool get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos);
	static DS_clkRegs& getInstance();
	string getName();
	uint getCSRCount();
	E_HILINK_REGISTER_TYPE getType();
	uint get_HILINK_MAX_LANE_NUM();
	uint getAddressMapToHiLink(int csrIndex);

///////////////////////////////////////////////////////////////////////////

private:
	class _REG_INFO{
		public:

	/// Dataslice clocking power down control. Active low.
	/// 0 = Power down all dsclk circuitry
	/// 1 = Power up all dsclk circuitry
	/// 
	/// Note: This function is not available at this moment.
			const T_REG_INFO_EX& dsclkpwrdb();	//CSR0[15:15]

	/// Select high-speed clock spine for both TX and RX.
	/// 0 = Select clock spine 0 from the clockslice 0
	/// 1 = Select clock spine 1 from the clockslice 1 (if applicable)
			const T_REG_INFO_EX& clkspinesel();	//CSR0[14:14]

	/// Select high-speed clock spine for TX if the TX is running at different from the RX.
	/// 0 = Select clock spine 0 from the clockslice 0
	/// 1 = Select clock spine 1 from the clockslice 1 (if applicable)
			const T_REG_INFO_EX& txclkspinesel();	//CSR0[13:13]

	/// Reference clock div2 enable (part of 'L' divider).
	/// 0 = Do not use div2 on the DSCLK refclk path
	/// 1 = Use div2 on the DSCLK refclk path
			const T_REG_INFO_EX& refdiv2en();	//CSR0[12:12]

	/// 0 = Use ring oscillator to generated phases
	/// 1 = Use divider to generate phases for low data rate configuration
			const T_REG_INFO_EX& bypassdiven();	//CSR0[11:11]

	/// 0 = Use the clock from the TX phase interpolator for the TX path.
	/// 1 = Bypass the TX phase interpolator and use the clock selected from clock spines for the TX path.
			const T_REG_INFO_EX& txbypassen();	//CSR0[10:10]

	/// Ring-VCO out-of-lock threshold (by default, choose from 1/4096 to 31/4096).
	/// Note: For LCVCO to lock, this field should not be programmed to 0.
			const T_REG_INFO_EX& ringvcololthr();	//CSR0[9:5]

	/// Ring-VCO loss-of-clock threshold.
	/// 000 = 128
	/// 001 = 256
	/// 010 = 512
	/// 011 = 1024
	/// 100 = 2048
	/// 101 = 4096
	/// 11x = 4096
	/// Not used
			const T_REG_INFO_EX& ringvcolocthr();	//CSR0[4:2]

	/// DSCKL out of lock status
	/// 0 = DSCLK is locked
	/// 1 = DSCLK  is out of lock
			const T_REG_INFO_EX& ringvcooutoflock();	//CSR0[1:1]

	/// DSCLK loss of clock status
	/// 0 = DSCLK clock is not lost
	/// 1 = DSCLK clock is lost
			const T_REG_INFO_EX& lossofringvcoclk();	//CSR0[0:0]

	/// This power down is for the whole dataslice.
			const T_REG_INFO_EX& dsnmirpwrdb();	//CSR1[15:15]

	/// 0 = Power down clock spine buffer 0 circuitry
	/// 1 = Power up all clock spine buffer 0 circuitry
			const T_REG_INFO_EX& buf0pwrdb();	//CSR1[14:14]

	/// 0 = Power down clock spine buffer 1 circuitry
	/// 1 = Power up all clock spine buffer 1 circuitry
			const T_REG_INFO_EX& buf1pwrdb();	//CSR1[13:13]

	/// 0 = power down injection clock to ring oscillator. 
	/// 1 = power up injection clock
			const T_REG_INFO_EX& dsclkgenpwrdb();	//CSR1[12:12]

	/// 0 = power down DSCLK  IDAC. 
	/// 1 = power up DSCLK IDAC
	/// Note: Powered down in bypass divider mode
			const T_REG_INFO_EX& idacpwrdb();	//CSR1[11:11]

	/// dsclk vregdac powerdown
	/// 0 = power down DSCLK IDAC Regulator. 
	/// 1 = power up DSCLK IDAC Regulator
	/// Note: Powered down in bypass divider mode
			const T_REG_INFO_EX& vregdacpwrdb();	//CSR1[10:10]

	/// dsclk vregl powerdown
	/// 0 = power down DSCLK cml2cmos Regulator. 
	/// 1 = power up DSCLK cml2cmos Regulator
			const T_REG_INFO_EX& vreglpwrdb();	//CSR1[9:9]

	/// dsclk lld feedback clock source selection signal
	/// 0 = rxcenterwordclk
	/// 1 = txcp_wordclk
			const T_REG_INFO_EX& lldclk_sel();	//CSR1[8:8]

	/// DSCLK lld start mode signal
	/// 0 = start automaticlly when dsclk calibration done
	/// 1 = start manually by configured register CSR10_DSCLK_LLD_START
			const T_REG_INFO_EX& lld_start_mode();	//CSR1[7:7]

	/// Enable calibration and observation of the IDAC output voltage,low active.
	/// 0: Enable.
	/// 1: Power down.
			const T_REG_INFO_EX& vcocalen();	//CSR1[4:4]

	/// Enable ILO calibration. ILO not injected,low active.
	/// 0: Enable.
	/// 1: Power down.
			const T_REG_INFO_EX& ilocalen();	//CSR1[3:3]

	/// Enable ILO injectors. 
	/// Disable during ILO calibration,low active.
	/// 0: Enable.
	/// 1: Power down.
			const T_REG_INFO_EX& injen();	//CSR1[2:2]

	/// (Unused)
			const T_REG_INFO_EX& oscclken();	//CSR1[1:1]

	/// 0 = Disable bleed for IDAC Regulator
	/// 1 = Enable
	/// Not used
			const T_REG_INFO_EX& vregbleeden();	//CSR1[0:0]

	/// DSCLK replicabias OP vref  selection
	/// 0=780
	/// 1=765
	/// 2=750
	/// 3=735
	/// 4=720
	/// 5=705
	/// 6=690
	/// 7=675
			const T_REG_INFO_EX& reprefsel();	//CSR2[14:12]

	/// dsclk replicabias module vpbias selection
	/// 0= select dsclk_rep_loadctrl[2:0] output
	/// 1=560
	/// 2=460
	/// 3=360
	/// 4=310
	/// 5=260
	/// 6=210
	/// 7=160
			const T_REG_INFO_EX& reploadctrl();	//CSR2[10:8]

	/// DSCLK south in channel CML bias selection
			const T_REG_INFO_EX& lane0ctrl();	//CSR2[5:4]

	/// DSCLK north in channel CML bias selection
			const T_REG_INFO_EX& lane1ctrl();	//CSR2[3:2]

	/// dsclk ilo hs clock CML bias selection
	/// when datarate>15Gbps(hsclk>7.5G), the uer should configure it to 00, others, the value is 2'b10
			const T_REG_INFO_EX& muxctrl();	//CSR2[1:0]

	/// biasscale[1]:
	/// 0=pidrive bias current of 50uA
	/// 1=pidriver bias current of 70uA
	/// biasscale[0]:
	/// 0=disable icv mix to icc bias currents
	/// 1=enable icv mix to icc bias currents
			const T_REG_INFO_EX& biasscale();	//CSR3[15:14]

	/// 0 = no additional offset current to IDAC
			const T_REG_INFO_EX& ioscdacofst();	//CSR3[13:12]

	/// Ring oscillator IDAC tune. Controls IDAC mirror ratio
			const T_REG_INFO_EX& ioscptune();	//CSR3[10:8]

	/// dsclk replicabias OP vref  selection
			const T_REG_INFO_EX& dsclk_rep_refsel_mux();	//CSR3[7:5]

	/// Unused
			const T_REG_INFO_EX& ioscscale();	//CSR3[4:0]

	/// Ring oscillator regulator level control, Not used
			const T_REG_INFO_EX& vregdaclvl();	//CSR4[14:12]

	/// dsclk vregl voltage control
	/// 000 = 0.83V
	/// 001 = 0.86V
	/// 010 = 0.90V
	/// 011 = 0.95V
	/// 100 = 1.01V
	/// 101 = 1.03V
	/// 110 = 1.06V
	/// 111 = 1.08V
			const T_REG_INFO_EX& vreglowlvl();	//CSR4[10:8]

	/// Used for slew rate control of the ILO 8 phase bypass divider. DSCLK_LDIVSLEWCTRL[2:0] = floor(divider_out_clk/250MHz)-1
	/// Not used, repetition with DSCLK_BYPASS_DIV_SLEW
			const T_REG_INFO_EX& dsclk_ldivslewctrl();	//CSR4[6:4]

	/// dsclk PI driver current bias control
			const T_REG_INFO_EX& tunepidrv();	//CSR4[3:1]

	/// Reset should enabled and then disabled before using the bypass divider to ensure output phases are correct.
	/// 0 = enable reset
	/// 1 = disable reset
			const T_REG_INFO_EX& refclkdivrstb();	//CSR4[0:0]

	/// Bit[5:4] of DSSPARE.
			const T_REG_INFO_EX& dsspare5to4();	//CSR5[13:12]

	/// Ring-VCO amplitude reference for calibration. Table units in mV.
	/// 0=648
	/// 1=633
	/// 2=618
	/// 3=603
	/// 4=588
	/// 5=573
	/// 6=558
	/// 7=543
	/// 8=534
	/// 9=518
	/// 10=503
	/// 11=488
	/// 12=473
	/// 13=458
	/// 14=443
	/// 15=428
			const T_REG_INFO_EX& voscref();	//CSR5[11:8]

	/// Ring-VCO bias current. Used for calibration.
			const T_REG_INFO_EX& ioscdaccal();	//CSR5[7:0]

	/// 0 = default
	/// 1 = increase cross coupling factor in ring
			const T_REG_INFO_EX& ilocrosstune();	//CSR6[15:15]

	/// Ring oscillator injection strength control:
	/// '000': disable main path injectors
	/// '001':  
	/// '010:
			const T_REG_INFO_EX& injlvl();	//CSR6[14:12]

	/// Secondary path ring oscillator injection tuning 
	/// '000': disable secondary path injectors
	/// '001':  
	/// '010:
			const T_REG_INFO_EX& injtune();	//CSR6[10:8]

	/// VCO Main Path Strength
			const T_REG_INFO_EX& psel();	//CSR6[7:5]

	/// VCO Secondary Path 1 Strength
			const T_REG_INFO_EX& s1sel();	//CSR6[4:2]

	/// VCO Secondary Path 2 Strength
			const T_REG_INFO_EX& s2sel();	//CSR6[1:0]

	/// n/c
	/// icvp_atb
	/// iccp50_atb
	/// vosc_vref
	/// tiehi
	/// hvcc
	/// tielo
	/// vss
			const T_REG_INFO_EX& dsclkbiasatbctrl();	//CSR7[15:12]

	/// n/c
	/// clkgen_atb
	/// dsclkreg_atb
	/// bias_atb
	/// vpbias
	/// vregdac
	/// lvcc
	/// vss
			const T_REG_INFO_EX& dsclktopatbctrl();	//CSR7[11:9]

	/// n/c
	/// inp_atb
	/// vosc
	/// pbias0
	/// pbias
	/// vpcasc
	/// itest
	/// vregdac
			const T_REG_INFO_EX& dsclkgenatbctrl();	//CSR7[8:6]

	/// 0 = bias receivers operate normally
	/// 1 = sample the icvp50uA current from DSCLK bias receivers
	/// 2 = sample the iptatp50uA current from DSCLK bias receivers
	/// 3 = sample the iccp50uA current from DSCLK bias receivers
			const T_REG_INFO_EX& dsclkrxbiasatbctrl();	//CSR7[5:4]

	/// 0000=nc
	/// 1000=vregdac
	/// 1xxx=nc
	/// 0001=vref
	/// 0010=vregout
	/// 0011=vgp
	/// 0100=vgpc
	/// 0101=vbiasn
	/// 0110=vmir_lf
	/// 0111=vmir_hf
			const T_REG_INFO_EX& dsclkregsatbctrl();	//CSR7[3:0]

	/// Bit[3:0] of DSSPARE.
			const T_REG_INFO_EX& dsspare3to0();	//CSR8[15:12]

	/// Dataslice top-level ATB Control
			const T_REG_INFO_EX& dstopatbctrl();	//CSR8[10:8]

	/// default: b00011011
	/// set ptatmixctrl[2:0] = ptatmixctrl[5:3]
	///  ptatmixctrl[6]=
	///  ptatmixctrl[7]=
			const T_REG_INFO_EX& ptatmixctrl();	//CSR8[7:0]

	/// DSCLK global reset. Active low.
			const T_REG_INFO_EX& dsclkrstb();	//CSR9[15:15]

	/// Not used
			const T_REG_INFO_EX& dsclkdigspare1();	//CSR9[14:14]

	/// Calibration mode for RXCTLE offset
	/// 0 = Automatic calibration
	/// 1 = Manual calibration
			const T_REG_INFO_EX& rxctle_stx_offset_mode();	//CSR9[13:13]

	/// 000 = Auto-calibration algorithm 1
	/// 001 = Auto-calibration algorithm 2
	/// 010 = Auto-calibration algorithm 3
	/// 011 = Auto-calibration full scan
	/// 100 = Manual calibration
			const T_REG_INFO_EX& autotune();	//CSR9[12:10]

	/// DSCLK calibration done clear signal
	/// 0 = keep unchaged 
	/// 1 = clear dsclkcaldone  to zero
			const T_REG_INFO_EX& dsclkcaldone_clr();	//CSR9[8:8]

	/// Direction control for the comparator calibration.
	/// 0 = TBD
	/// 1 = TBD
			const T_REG_INFO_EX& dsclkcompcaldir();	//CSR9[7:7]

	/// Not used
			const T_REG_INFO_EX& dsclkdigspare2();	//CSR9[6:6]

	/// DSCLK calibraion done status, Active high.
			const T_REG_INFO_EX& dsclkcaldone();	//CSR9[5:5]

	/// DSCLK calibration result error status,Active high.
	/// 1: Error
	/// 0: Not error
			const T_REG_INFO_EX& dsclkcalerr();	//CSR9[4:4]

	/// Current status for DSCLK calibration control state machine
			const T_REG_INFO_EX& autotunestatus();	//CSR9[3:0]

	/// Start DSCLK frequency detector. Active high.
			const T_REG_INFO_EX& dsclk_fd_start();	//CSR10[14:14]

	/// Clear the loss of lock detector. Active high.
			const T_REG_INFO_EX& dsclk_lld_clr();	//CSR10[13:13]

	/// Clear the frequency detector. Active high.
			const T_REG_INFO_EX& dsclk_fd_clr();	//CSR10[12:12]

	/// Clear the status of calibration. Active high.
	/// Not used
			const T_REG_INFO_EX& dsclk_calib_clr();	//CSR10[11:11]

	/// Start DSCLK loss of clock detector. Active rising edge.
			const T_REG_INFO_EX& dsclk_lcd_start();	//CSR10[10:10]

	/// Start DSCLK loss of lock detector. Active rising edge.
			const T_REG_INFO_EX& dsclk_lld_start();	//CSR10[9:9]

	/// Start DSCLK calibration. Active rising edge.
			const T_REG_INFO_EX& dsclk_calib_start();	//CSR10[8:8]

	/// Enable DSCLK loss of clock detector. Active high.
	/// 0 = Don't enable the detector, Gating the clock
	/// 1 = Enable the detector.
	/// Not used
			const T_REG_INFO_EX& dsclk_lcd_enable();	//CSR10[7:7]

	/// Enable DSCLK loss of lock detector. Active high.
	/// 0 = Don't enable the detector, Gating the clock
	/// 1 = Enable the detector.
	/// Not used
			const T_REG_INFO_EX& dsclk_lld_enable();	//CSR10[6:6]

	/// Enable DSCLK calibration. Active high.
	/// 0 = Don't enable calibration, Gating the clock
	/// 1 = Enable calibration
	/// Not used
			const T_REG_INFO_EX& dsclk_calib_enable();	//CSR10[5:5]

	/// DSCLK loss of clock detector reset. Active low.
	/// 0 = Reset loss of clock detector part
	/// 1 = Reset is not active
			const T_REG_INFO_EX& dsclk_lcd_soft_rst_n();	//CSR10[4:4]

	/// DSCLK loss of lock detector reset. Active low.
	/// 0 = Reset loss of lock detector part
	/// 1 = Reset is not active
			const T_REG_INFO_EX& dsclk_lld_soft_rst_n();	//CSR10[3:3]

	/// DSCLK calibration reset. Active low.
	/// 0 = Reset calibration part
	/// 1 = Reset is not active.
	/// Not used
			const T_REG_INFO_EX& dsclk_calib_soft_rst_n();	//CSR10[2:2]

	/// DSCLK bus reset. Active low.
	/// 0 = Reset bus part
	/// 1 = Reset is not active
	/// Not used
			const T_REG_INFO_EX& dsclk_bus_soft_rst_n();	//CSR10[1:1]

	/// DSCLK global reset. Active low.
	/// 0 = Reset whole digital circuit
	/// 1 = Reset is not active
	/// Not used, repetitionon with register DSCLKRSTB
			const T_REG_INFO_EX& dsclk_glb_soft_rst_n();	//CSR10[0:0]

	/// dsclk regl selfbleed
			const T_REG_INFO_EX& dsclk_regl_selfbleed();	//CSR11[14:11]

	/// Threshold set for DSCLK frequency detection
			const T_REG_INFO_EX& dsclk_fd_threshold();	//CSR11[10:1]

	/// Not used
			const T_REG_INFO_EX& dsclk_meas_fd_wait();	//CSR11[0:0]

	/// Timer divide parameter set for frequency detection counter in ref_clk clock
			const T_REG_INFO_EX& dsclk_fd_ref_cnt_dv();	//CSR12[13:12]

	/// Timer parameter set for  for frequency detection counter in ref_clk clock
			const T_REG_INFO_EX& dsclk_fd_ref_cnt_lv();	//CSR12[11:0]

	/// Timer divide parameter set for frequency detection counter in fb_clk  clock
			const T_REG_INFO_EX& dsclk_fd_fb_cnt_dv();	//CSR13[13:12]

	/// Timer parameter set for  for frequency detection counter in fb_clk clock
			const T_REG_INFO_EX& dsclk_fd_fb_cnt_lv();	//CSR13[11:0]

	/// DSCLK calibration timer divide parameter set
			const T_REG_INFO_EX& dsclk_timer_value();	//CSR14[14:5]

	/// DSCLK calibration timer  parameter set
			const T_REG_INFO_EX& dsclk_timer_div_value();	//CSR14[4:2]

	/// DSCLK calibration timer  enable, Active high
			const T_REG_INFO_EX& dsclk_timer_div_en();	//CSR14[1:1]

	/// DSCLK calibration stop  control , Active high
			const T_REG_INFO_EX& dsclk_timer_stop();	//CSR14[0:0]

	/// Not used, repetition with register RINGVCOLOLTHR[4:0]
			const T_REG_INFO_EX& dsclk_lld_lck_threshold();	//CSR15[13:4]

	/// Timer divide parameter set  for DSCLK loss of lock detection
			const T_REG_INFO_EX& dsclk_lld_fb_div_ratio();	//CSR15[3:1]

	/// DSCLK loss of lock detection time,
	/// 1: Only detection one time after start
	/// 0: More than one timer after start
			const T_REG_INFO_EX& dsclk_lld_once();	//CSR15[0:0]

	/// Timer divide parameter set for LLD counter in ref_clk clock
			const T_REG_INFO_EX& dsclk_lld_ref_cnt_dv();	//CSR16[14:12]

	/// Timer parameter set for  for LLD counter in ref_clk clock
			const T_REG_INFO_EX& dsclk_lld_ref_cnt_lv();	//CSR16[11:0]

	/// Timer divide parameter set for LLD counter in fb_clk clock
			const T_REG_INFO_EX& dsclk_lld_fb_cnt_dv();	//CSR17[14:12]

	/// Timer parameter set for  for LLD counter in fb_clk clock
			const T_REG_INFO_EX& dsclk_lld_fb_cnt_lv();	//CSR17[11:0]

	/// dsclk mux replicabias module vpbias selection
			const T_REG_INFO_EX& dsclk_rep_loadctrl_mux();	//CSR18[12:10]

	/// Timer divide parameter set for LCD counter in fb_clk clock
			const T_REG_INFO_EX& dsclk_lcd_fb_div_ratio();	//CSR18[9:1]

	/// Override to clear the LCD status, active high
			const T_REG_INFO_EX& dsclk_lcd_override();	//CSR18[0:0]

	/// Timer parameter set for LCD counter in fb_clk clock,Only bit [2:0] valid
			const T_REG_INFO_EX& dsclk_lcd_fb_cnt_lv();	//CSR19[11:0]

	/// Not used
			const T_REG_INFO_EX& dsclk_debugging_ctrl1();	//CSR20[15:0]

	/// Counter value for DSCLK FD in ref_clk clock
			const T_REG_INFO_EX& dsclk_fd_ref_freq();	//CSR21[11:0]

	/// Counter value for DSCLK FD in fb_clk clock
			const T_REG_INFO_EX& dsclk_fd_fb_freq();	//CSR22[11:0]

	/// Counter different value for DSCLK_FD_FB_FREQ with DSCLK_FD_REF_FREQ
			const T_REG_INFO_EX& dsclk_fd_diff_freq();	//CSR23[12:0]

	/// Lock of loss detection done, high active
			const T_REG_INFO_EX& dsclk_lld_done();	//CSR24[15:15]

	/// Counter different value for LLD counter in fb_clk and ref_clk clock
			const T_REG_INFO_EX& dsclk_lld_diff_freq();	//CSR24[12:0]

	/// Counter  value for LLD  in fb_clk clock
			const T_REG_INFO_EX& dsclk_lld_fb_freq();	//CSR25[11:0]

	/// DSCLK calibration status 
	/// [15]    : Loss of clock detection done.
	///              1: Detection done.
	///              0: Detection not done.
	/// [14:2] : Reserved
	/// [1]      :  Low offset comparator status from analog and the default value is 1
	/// [0]      : Frequency detection lock status 
	///              1:  Lock.
	///              0:  Not Lock.
			const T_REG_INFO_EX& dsclk_misc_status();	//CSR26[15:0]

	/// Calibrated value for VOSCREF
			const T_REG_INFO_EX& dsclk_calib_voscref();	//CSR27[15:12]

	/// Calibrated value for IOSCDACCAL
			const T_REG_INFO_EX& dsclk_calib_ioscdaccal();	//CSR27[11:4]

	/// set the slew of pidiv input divider clocking; 
	/// skew[2:0]= floor (fckin/250M) -1 ;
			const T_REG_INFO_EX& dsclk_bypass_div_slew();	//CSR28[15:13]

	/// Counter  value for LLD  in ref_clk clock
			const T_REG_INFO_EX& dsclk_lld_ref_freq();	//CSR28[11:0]

	/// ptatmix configure value when vco curve value is 0x4
			const T_REG_INFO_EX& ptatmix_vco_4();	//CSR29[15:8]

	/// dsclk PI driver reference voltage control.
	/// 00 = 0.75*Lvcc
	/// 01 = 0.80*Lvcc
	/// 10 = 0.85*Lvcc
	/// 11 = 0.90*Lvcc
			const T_REG_INFO_EX& dsclk_pidrv_refsel();	//CSR29[6:5]

	/// dsclk cml2cmos powerdown, low active.
	/// 0 = Power down.
	/// 1 = Power up.
			const T_REG_INFO_EX& dsclk_cml2cmos_pwrdnb();	//CSR29[4:4]

	/// Select high-speed clock spine for both TX and RX as pin data 
	/// rate switch, the register only valid in PCIe/SATA/SAS mode.
	/// 1 = Select clock spine not by pin rate switch logic
	/// 0 = Select clock spine  by pin rate swtich logic
			const T_REG_INFO_EX& clkspine_sw_sel();	//CSR29[2:2]

	/// Select high-speed clock spine for TX if the TX is running at different from the RX as pin rate switch, the register only valid in PCIe/SATA/SAS mode.
	/// 1 = Select clock spine not by pin rate switch
	/// 0 = Select clock spine  from pin rate switch logic
			const T_REG_INFO_EX& txclkspine_sw_sel();	//CSR29[1:1]

	/// ptatmix configure value when vco curve value is 0x5
			const T_REG_INFO_EX& ptatmix_vco_5();	//CSR30[15:8]

	/// ptatmix configure value when vco curve value is 0x6
			const T_REG_INFO_EX& ptatmix_vco_6();	//CSR30[7:0]

	/// ptatmix configure value when vco curve value is 0x7
			const T_REG_INFO_EX& ptatmix_vco_7();	//CSR31[15:8]

	/// ptatmix configure value when vco curve value is 0x8
			const T_REG_INFO_EX& ptatmix_vco_8();	//CSR31[7:0]

	/// ptatmix configure value when vco curve value is 0x9
			const T_REG_INFO_EX& ptatmix_vco_9();	//CSR32[15:8]

	/// ptatmix configure value when vco curve value is 0xA
			const T_REG_INFO_EX& ptatmix_vco_a();	//CSR32[7:0]

	/// ptatmix configure value when vco curve value is 0xB
			const T_REG_INFO_EX& ptatmix_vco_b();	//CSR33[15:8]

	/// ptatmix configure value when vco curve value is 0xC
			const T_REG_INFO_EX& ptatmix_vco_c();	//CSR33[7:0]

	/// ptatmix configure value when vco curve value is 0xD
			const T_REG_INFO_EX& ptatmix_vco_d();	//CSR34[15:8]

	/// ptatmix configure value when vco curve value is 0xE
			const T_REG_INFO_EX& ptatmix_vco_e();	//CSR34[7:0]

	/// ptatmix configure value when vco curve value is 0xF
			const T_REG_INFO_EX& ptatmix_vco_f();	//CSR35[15:8]

	/// Spare for DSCLK analog.
	/// DSCLKSPARE[2] control Regulator loading adjust power down and the default value is 1
	/// DSCLKSPARE[1:0] control Regulator reference voltage tuning and the default value is 10.
	/// 00: 0.717V
	/// 01: 0.777V
	/// 10: 0.797V
	/// 11: 0.827V
			const T_REG_INFO_EX& dsclkspare();	//CSR35[7:0]

	/// dsclk calibration ioscdacctrl min value
			const T_REG_INFO_EX& idac_min();	//CSR36[15:8]

	/// dsclk calibration ioscdacctrl value and its max value is 255
			const T_REG_INFO_EX& idac_max();	//CSR36[7:0]

	/// dsclk calibration transition counter min value
			const T_REG_INFO_EX& trans_min();	//CSR37[15:12]

	/// dsclk calibration transition counter max value
			const T_REG_INFO_EX& trans_max();	//CSR37[11:8]

	/// dsclk calibration vco curve min value
			const T_REG_INFO_EX& vco_min();	//CSR37[7:4]

	/// dsclk calibration vco curve max value
			const T_REG_INFO_EX& vco_max();	//CSR37[3:0]

	/// dsclk calibration mapping psel  code when vco curve value is 4
			const T_REG_INFO_EX& dsclk_psel_vco_4();	//CSR38[15:13]

	/// dsclk calibration mapping s1sel  code when vco curve value is 4
			const T_REG_INFO_EX& dsclk_s1sel_vco_4();	//CSR38[12:10]

	/// dsclk calibration mapping s2sel  code when vco curve value is 4
			const T_REG_INFO_EX& dsclk_s2sel_vco_4();	//CSR38[9:8]

	/// dsclk calibration mapping inject level  code when vco curve value is 4
			const T_REG_INFO_EX& dsclk_injlev_vco_4();	//CSR38[6:4]

	/// dsclk calibration mapping inject tune code when vco curve value is 4
			const T_REG_INFO_EX& dsclk_injtune_vco_4();	//CSR38[2:0]

	/// dsclk calibration mapping psel  code when vco curve value is 5
			const T_REG_INFO_EX& dsclk_psel_vco_5();	//CSR39[15:13]

	/// dsclk calibration mapping s1sel  code when vco curve value is 5
			const T_REG_INFO_EX& dsclk_s1sel_vco_5();	//CSR39[12:10]

	/// dsclk calibration mapping s2sel  code when vco curve value is 5
			const T_REG_INFO_EX& dsclk_s2sel_vco_5();	//CSR39[9:8]

	/// dsclk calibration mapping inject level  code when vco curve value is 5
			const T_REG_INFO_EX& dsclk_injlev_vco_5();	//CSR39[6:4]

	/// dsclk calibration mapping inject tune code when vco curve value is 5
			const T_REG_INFO_EX& dsclk_injtune_vco_5();	//CSR39[2:0]

	/// dsclk calibration mapping psel  code when vco curve value is 6
			const T_REG_INFO_EX& dsclk_psel_vco_6();	//CSR40[15:13]

	/// dsclk calibration mapping s1sel  code when vco curve value is 6
			const T_REG_INFO_EX& dsclk_s1sel_vco_6();	//CSR40[12:10]

	/// dsclk calibration mapping s2sel  code when vco curve value is 6
			const T_REG_INFO_EX& dsclk_s2sel_vco_6();	//CSR40[9:8]

	/// dsclk calibration mapping inject level  code when vco curve value is 6
			const T_REG_INFO_EX& dsclk_injlev_vco_6();	//CSR40[6:4]

	/// dsclk calibration mapping inject tune code when vco curve value is 6
			const T_REG_INFO_EX& dsclk_injtune_vco_6();	//CSR40[2:0]

	/// dsclk calibration mapping psel  code when vco curve value is 7
			const T_REG_INFO_EX& dsclk_psel_vco_7();	//CSR41[15:13]

	/// dsclk calibration mapping s1sel  code when vco curve value is 7
			const T_REG_INFO_EX& dsclk_s1sel_vco_7();	//CSR41[12:10]

	/// dsclk calibration mapping s2sel  code when vco curve value is 7
			const T_REG_INFO_EX& dsclk_s2sel_vco_7();	//CSR41[9:8]

	/// dsclk calibration mapping inject level  code when vco curve value is 7
			const T_REG_INFO_EX& dsclk_injlev_vco_7();	//CSR41[6:4]

	/// dsclk calibration mapping inject tune code when vco curve value is 7
			const T_REG_INFO_EX& dsclk_injtune_vco_7();	//CSR41[2:0]

	/// dsclk calibration mapping psel  code when vco curve value is  8
			const T_REG_INFO_EX& dsclk_psel_vco_8();	//CSR42[15:13]

	/// dsclk calibration mapping s1sel  code when vco curve value is  8
			const T_REG_INFO_EX& dsclk_s1sel_vco_8();	//CSR42[12:10]

	/// dsclk calibration mapping s2sel  code when vco curve value is  8
			const T_REG_INFO_EX& dsclk_s2sel_vco_8();	//CSR42[9:8]

	/// dsclk calibration mapping inject level  code when vco curve value is  8
			const T_REG_INFO_EX& dsclk_injlev_vco_8();	//CSR42[6:4]

	/// dsclk calibration mapping inject tune code when vco curve value is 8
			const T_REG_INFO_EX& dsclk_injtune_vco_8();	//CSR42[2:0]

	/// dsclk calibration mapping psel  code when vco curve value is 9
			const T_REG_INFO_EX& dsclk_psel_vco_9();	//CSR43[15:13]

	/// dsclk calibration mapping s1sel  code when vco curve value is 9
			const T_REG_INFO_EX& dsclk_s1sel_vco_9();	//CSR43[12:10]

	/// dsclk calibration mapping s2sel  code when vco curve value is 9
			const T_REG_INFO_EX& dsclk_s2sel_vco_9();	//CSR43[9:8]

	/// dsclk calibration mapping inject level  code when vco curve value is 9
			const T_REG_INFO_EX& dsclk_injlev_vco_9();	//CSR43[6:4]

	/// dsclk calibration mapping inject tune code when vco curve value is 9
			const T_REG_INFO_EX& dsclk_injtune_vco_9();	//CSR43[2:0]

	/// dsclk calibration mapping psel  code when vco curve value is 10
			const T_REG_INFO_EX& dsclk_psel_vco_a();	//CSR44[15:13]

	/// dsclk calibration mapping s1sel  code when vco curve value is 10
			const T_REG_INFO_EX& dsclk_s1sel_vco_a();	//CSR44[12:10]

	/// dsclk calibration mapping s2sel  code when vco curve value is 10
			const T_REG_INFO_EX& dsclk_s2sel_vco_a();	//CSR44[9:8]

	/// dsclk calibration mapping inject level  code when vco curve value is 10
			const T_REG_INFO_EX& dsclk_injlev_vco_a();	//CSR44[6:4]

	/// dsclk calibration mapping inject tune code when vco curve value is 10
			const T_REG_INFO_EX& dsclk_injtune_vco_a();	//CSR44[2:0]

	/// dsclk calibration mapping psel  code when vco curve value is 11
			const T_REG_INFO_EX& dsclk_psel_vco_b();	//CSR45[15:13]

	/// dsclk calibration mapping s1sel  code when vco curve value is 11
			const T_REG_INFO_EX& dsclk_s1sel_vco_b();	//CSR45[12:10]

	/// dsclk calibration mapping s2sel  code when vco curve value is 11
			const T_REG_INFO_EX& dsclk_s2sel_vco_b();	//CSR45[9:8]

	/// dsclk calibration mapping inject level  code when vco curve value is 11
			const T_REG_INFO_EX& dsclk_injlev_vco_b();	//CSR45[6:4]

	/// dsclk calibration mapping inject tune code when vco curve value is 11
			const T_REG_INFO_EX& dsclk_injtune_vco_b();	//CSR45[2:0]

	/// dsclk calibration mapping psel  code when vco curve value is 12
			const T_REG_INFO_EX& dsclk_psel_vco_c();	//CSR46[15:13]

	/// dsclk calibration mapping s1sel  code when vco curve value is 12
			const T_REG_INFO_EX& dsclk_s1sel_vco_c();	//CSR46[12:10]

	/// dsclk calibration mapping s2sel  code when vco curve value is 12
			const T_REG_INFO_EX& dsclk_s2sel_vco_c();	//CSR46[9:8]

	/// dsclk calibration mapping inject level  code when vco curve value is 12
			const T_REG_INFO_EX& dsclk_injlev_vco_c();	//CSR46[6:4]

	/// dsclk calibration mapping inject tune code when vco curve value is 12
			const T_REG_INFO_EX& dsclk_injtune_vco_c();	//CSR46[2:0]

	/// dsclk calibration mapping psel  code when vco curve value is 13
			const T_REG_INFO_EX& dsclk_psel_vco_d();	//CSR47[15:13]

	/// dsclk calibration mapping s1sel  code when vco curve value is 13
			const T_REG_INFO_EX& dsclk_s1sel_vco_d();	//CSR47[12:10]

	/// dsclk calibration mapping s2sel  code when vco curve value is 13
			const T_REG_INFO_EX& dsclk_s2sel_vco_d();	//CSR47[9:8]

	/// dsclk calibration mapping inject level  code when vco curve value is 13
			const T_REG_INFO_EX& dsclk_injlev_vco_d();	//CSR47[6:4]

	/// dsclk calibration mapping inject tune code when vco curve value is 13
			const T_REG_INFO_EX& dsclk_injtune_vco_d();	//CSR47[2:0]

	/// dsclk calibration mapping psel  code when vco curve value is 14
			const T_REG_INFO_EX& dsclk_psel_vco_e();	//CSR48[15:13]

	/// dsclk calibration mapping s1sel  code when vco curve value is 14
			const T_REG_INFO_EX& dsclk_s1sel_vco_e();	//CSR48[12:10]

	/// dsclk calibration mapping s2sel  code when vco curve value is 14
			const T_REG_INFO_EX& dsclk_s2sel_vco_e();	//CSR48[9:8]

	/// dsclk calibration mapping inject level  code when vco curve value is 14
			const T_REG_INFO_EX& dsclk_injlev_vco_e();	//CSR48[6:4]

	/// dsclk calibration mapping inject tune code when vco curve value is 14
			const T_REG_INFO_EX& dsclk_injtune_vco_e();	//CSR48[2:0]

	/// dsclk calibration mapping psel  code when vco curve value is 15
			const T_REG_INFO_EX& dsclk_psel_vco_f();	//CSR49[15:13]

	/// dsclk calibration mapping s1sel  code when vco curve value is 15
			const T_REG_INFO_EX& dsclk_s1sel_vco_f();	//CSR49[12:10]

	/// dsclk calibration mapping s2sel  code when vco curve value is 15
			const T_REG_INFO_EX& dsclk_s2sel_vco_f();	//CSR49[9:8]

	/// dsclk calibration mapping inject level  code when vco curve value is 15
			const T_REG_INFO_EX& dsclk_injlev_vco_f();	//CSR49[6:4]

	/// dsclk calibration mapping inject tune code when vco curve value is 15
			const T_REG_INFO_EX& dsclk_injtune_vco_f();	//CSR49[2:0]
			bool get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos);
	};
public:
	_REG_INFO REG_INFO;

	uint csr[DS_CLK_CSR_NUM];


	//CSR0[15:15]
	DS_clkRegs& setdsclkpwrdb(uint val);
	uint getdsclkpwrdb();

	//CSR0[14:14]
	DS_clkRegs& setclkspinesel(uint val);
	uint getclkspinesel();

	//CSR0[13:13]
	DS_clkRegs& settxclkspinesel(uint val);
	uint gettxclkspinesel();

	//CSR0[12:12]
	DS_clkRegs& setrefdiv2en(uint val);
	uint getrefdiv2en();

	//CSR0[11:11]
	DS_clkRegs& setbypassdiven(uint val);
	uint getbypassdiven();

	//CSR0[10:10]
	DS_clkRegs& settxbypassen(uint val);
	uint gettxbypassen();

	//CSR0[9:5]
	DS_clkRegs& setringvcololthr(uint val);
	uint getringvcololthr();

	//CSR0[4:2]
	DS_clkRegs& setringvcolocthr(uint val);
	uint getringvcolocthr();

	//CSR0[1:1]
	uint getringvcooutoflock();

	//CSR0[0:0]
	uint getlossofringvcoclk();

	//CSR1[15:15]
	DS_clkRegs& setdsnmirpwrdb(uint val);
	uint getdsnmirpwrdb();

	//CSR1[14:14]
	DS_clkRegs& setbuf0pwrdb(uint val);
	uint getbuf0pwrdb();

	//CSR1[13:13]
	DS_clkRegs& setbuf1pwrdb(uint val);
	uint getbuf1pwrdb();

	//CSR1[12:12]
	DS_clkRegs& setdsclkgenpwrdb(uint val);
	uint getdsclkgenpwrdb();

	//CSR1[11:11]
	DS_clkRegs& setidacpwrdb(uint val);
	uint getidacpwrdb();

	//CSR1[10:10]
	DS_clkRegs& setvregdacpwrdb(uint val);
	uint getvregdacpwrdb();

	//CSR1[9:9]
	DS_clkRegs& setvreglpwrdb(uint val);
	uint getvreglpwrdb();

	//CSR1[8:8]
	DS_clkRegs& setlldclk_sel(uint val);
	uint getlldclk_sel();

	//CSR1[7:7]
	DS_clkRegs& setlld_start_mode(uint val);
	uint getlld_start_mode();

	//CSR1[4:4]
	DS_clkRegs& setvcocalen(uint val);
	uint getvcocalen();

	//CSR1[3:3]
	DS_clkRegs& setilocalen(uint val);
	uint getilocalen();

	//CSR1[2:2]
	DS_clkRegs& setinjen(uint val);
	uint getinjen();

	//CSR1[1:1]
	DS_clkRegs& setoscclken(uint val);
	uint getoscclken();

	//CSR1[0:0]
	DS_clkRegs& setvregbleeden(uint val);
	uint getvregbleeden();

	//CSR2[14:12]
	DS_clkRegs& setreprefsel(uint val);
	uint getreprefsel();

	//CSR2[10:8]
	DS_clkRegs& setreploadctrl(uint val);
	uint getreploadctrl();

	//CSR2[5:4]
	DS_clkRegs& setlane0ctrl(uint val);
	uint getlane0ctrl();

	//CSR2[3:2]
	DS_clkRegs& setlane1ctrl(uint val);
	uint getlane1ctrl();

	//CSR2[1:0]
	DS_clkRegs& setmuxctrl(uint val);
	uint getmuxctrl();

	//CSR3[15:14]
	DS_clkRegs& setbiasscale(uint val);
	uint getbiasscale();

	//CSR3[13:12]
	DS_clkRegs& setioscdacofst(uint val);
	uint getioscdacofst();

	//CSR3[10:8]
	DS_clkRegs& setioscptune(uint val);
	uint getioscptune();

	//CSR3[7:5]
	DS_clkRegs& setdsclk_rep_refsel_mux(uint val);
	uint getdsclk_rep_refsel_mux();

	//CSR3[4:0]
	DS_clkRegs& setioscscale(uint val);
	uint getioscscale();

	//CSR4[14:12]
	DS_clkRegs& setvregdaclvl(uint val);
	uint getvregdaclvl();

	//CSR4[10:8]
	DS_clkRegs& setvreglowlvl(uint val);
	uint getvreglowlvl();

	//CSR4[6:4]
	DS_clkRegs& setdsclk_ldivslewctrl(uint val);
	uint getdsclk_ldivslewctrl();

	//CSR4[3:1]
	DS_clkRegs& settunepidrv(uint val);
	uint gettunepidrv();

	//CSR4[0:0]
	DS_clkRegs& setrefclkdivrstb(uint val);
	uint getrefclkdivrstb();

	//CSR5[13:12]
	DS_clkRegs& setdsspare5to4(uint val);
	uint getdsspare5to4();

	//CSR5[11:8]
	DS_clkRegs& setvoscref(uint val);
	uint getvoscref();

	//CSR5[7:0]
	DS_clkRegs& setioscdaccal(uint val);
	uint getioscdaccal();

	//CSR6[15:15]
	DS_clkRegs& setilocrosstune(uint val);
	uint getilocrosstune();

	//CSR6[14:12]
	DS_clkRegs& setinjlvl(uint val);
	uint getinjlvl();

	//CSR6[10:8]
	DS_clkRegs& setinjtune(uint val);
	uint getinjtune();

	//CSR6[7:5]
	DS_clkRegs& setpsel(uint val);
	uint getpsel();

	//CSR6[4:2]
	DS_clkRegs& sets1sel(uint val);
	uint gets1sel();

	//CSR6[1:0]
	DS_clkRegs& sets2sel(uint val);
	uint gets2sel();

	//CSR7[15:12]
	DS_clkRegs& setdsclkbiasatbctrl(uint val);
	uint getdsclkbiasatbctrl();

	//CSR7[11:9]
	DS_clkRegs& setdsclktopatbctrl(uint val);
	uint getdsclktopatbctrl();

	//CSR7[8:6]
	DS_clkRegs& setdsclkgenatbctrl(uint val);
	uint getdsclkgenatbctrl();

	//CSR7[5:4]
	DS_clkRegs& setdsclkrxbiasatbctrl(uint val);
	uint getdsclkrxbiasatbctrl();

	//CSR7[3:0]
	DS_clkRegs& setdsclkregsatbctrl(uint val);
	uint getdsclkregsatbctrl();

	//CSR8[15:12]
	DS_clkRegs& setdsspare3to0(uint val);
	uint getdsspare3to0();

	//CSR8[10:8]
	DS_clkRegs& setdstopatbctrl(uint val);
	uint getdstopatbctrl();

	//CSR8[7:0]
	DS_clkRegs& setptatmixctrl(uint val);
	uint getptatmixctrl();

	//CSR9[15:15]
	DS_clkRegs& setdsclkrstb(uint val);
	uint getdsclkrstb();

	//CSR9[14:14]
	DS_clkRegs& setdsclkdigspare1(uint val);
	uint getdsclkdigspare1();

	//CSR9[13:13]
	DS_clkRegs& setrxctle_stx_offset_mode(uint val);
	uint getrxctle_stx_offset_mode();

	//CSR9[12:10]
	DS_clkRegs& setautotune(uint val);
	uint getautotune();

	//CSR9[8:8]
	DS_clkRegs& setdsclkcaldone_clr(uint val);
	uint getdsclkcaldone_clr();

	//CSR9[7:7]
	DS_clkRegs& setdsclkcompcaldir(uint val);
	uint getdsclkcompcaldir();

	//CSR9[6:6]
	DS_clkRegs& setdsclkdigspare2(uint val);
	uint getdsclkdigspare2();

	//CSR9[5:5]
	uint getdsclkcaldone();

	//CSR9[4:4]
	uint getdsclkcalerr();

	//CSR9[3:0]
	uint getautotunestatus();

	//CSR10[14:14]
	DS_clkRegs& setdsclk_fd_start(uint val);
	uint getdsclk_fd_start();

	//CSR10[13:13]
	DS_clkRegs& setdsclk_lld_clr(uint val);
	uint getdsclk_lld_clr();

	//CSR10[12:12]
	DS_clkRegs& setdsclk_fd_clr(uint val);
	uint getdsclk_fd_clr();

	//CSR10[11:11]
	DS_clkRegs& setdsclk_calib_clr(uint val);
	uint getdsclk_calib_clr();

	//CSR10[10:10]
	DS_clkRegs& setdsclk_lcd_start(uint val);
	uint getdsclk_lcd_start();

	//CSR10[9:9]
	DS_clkRegs& setdsclk_lld_start(uint val);
	uint getdsclk_lld_start();

	//CSR10[8:8]
	DS_clkRegs& setdsclk_calib_start(uint val);
	uint getdsclk_calib_start();

	//CSR10[7:7]
	DS_clkRegs& setdsclk_lcd_enable(uint val);
	uint getdsclk_lcd_enable();

	//CSR10[6:6]
	DS_clkRegs& setdsclk_lld_enable(uint val);
	uint getdsclk_lld_enable();

	//CSR10[5:5]
	DS_clkRegs& setdsclk_calib_enable(uint val);
	uint getdsclk_calib_enable();

	//CSR10[4:4]
	DS_clkRegs& setdsclk_lcd_soft_rst_n(uint val);
	uint getdsclk_lcd_soft_rst_n();

	//CSR10[3:3]
	DS_clkRegs& setdsclk_lld_soft_rst_n(uint val);
	uint getdsclk_lld_soft_rst_n();

	//CSR10[2:2]
	DS_clkRegs& setdsclk_calib_soft_rst_n(uint val);
	uint getdsclk_calib_soft_rst_n();

	//CSR10[1:1]
	DS_clkRegs& setdsclk_bus_soft_rst_n(uint val);
	uint getdsclk_bus_soft_rst_n();

	//CSR10[0:0]
	DS_clkRegs& setdsclk_glb_soft_rst_n(uint val);
	uint getdsclk_glb_soft_rst_n();

	//CSR11[14:11]
	DS_clkRegs& setdsclk_regl_selfbleed(uint val);
	uint getdsclk_regl_selfbleed();

	//CSR11[10:1]
	DS_clkRegs& setdsclk_fd_threshold(uint val);
	uint getdsclk_fd_threshold();

	//CSR11[0:0]
	DS_clkRegs& setdsclk_meas_fd_wait(uint val);
	uint getdsclk_meas_fd_wait();

	//CSR12[13:12]
	DS_clkRegs& setdsclk_fd_ref_cnt_dv(uint val);
	uint getdsclk_fd_ref_cnt_dv();

	//CSR12[11:0]
	DS_clkRegs& setdsclk_fd_ref_cnt_lv(uint val);
	uint getdsclk_fd_ref_cnt_lv();

	//CSR13[13:12]
	DS_clkRegs& setdsclk_fd_fb_cnt_dv(uint val);
	uint getdsclk_fd_fb_cnt_dv();

	//CSR13[11:0]
	DS_clkRegs& setdsclk_fd_fb_cnt_lv(uint val);
	uint getdsclk_fd_fb_cnt_lv();

	//CSR14[14:5]
	DS_clkRegs& setdsclk_timer_value(uint val);
	uint getdsclk_timer_value();

	//CSR14[4:2]
	DS_clkRegs& setdsclk_timer_div_value(uint val);
	uint getdsclk_timer_div_value();

	//CSR14[1:1]
	DS_clkRegs& setdsclk_timer_div_en(uint val);
	uint getdsclk_timer_div_en();

	//CSR14[0:0]
	DS_clkRegs& setdsclk_timer_stop(uint val);
	uint getdsclk_timer_stop();

	//CSR15[13:4]
	DS_clkRegs& setdsclk_lld_lck_threshold(uint val);
	uint getdsclk_lld_lck_threshold();

	//CSR15[3:1]
	DS_clkRegs& setdsclk_lld_fb_div_ratio(uint val);
	uint getdsclk_lld_fb_div_ratio();

	//CSR15[0:0]
	DS_clkRegs& setdsclk_lld_once(uint val);
	uint getdsclk_lld_once();

	//CSR16[14:12]
	DS_clkRegs& setdsclk_lld_ref_cnt_dv(uint val);
	uint getdsclk_lld_ref_cnt_dv();

	//CSR16[11:0]
	DS_clkRegs& setdsclk_lld_ref_cnt_lv(uint val);
	uint getdsclk_lld_ref_cnt_lv();

	//CSR17[14:12]
	DS_clkRegs& setdsclk_lld_fb_cnt_dv(uint val);
	uint getdsclk_lld_fb_cnt_dv();

	//CSR17[11:0]
	DS_clkRegs& setdsclk_lld_fb_cnt_lv(uint val);
	uint getdsclk_lld_fb_cnt_lv();

	//CSR18[12:10]
	DS_clkRegs& setdsclk_rep_loadctrl_mux(uint val);
	uint getdsclk_rep_loadctrl_mux();

	//CSR18[9:1]
	DS_clkRegs& setdsclk_lcd_fb_div_ratio(uint val);
	uint getdsclk_lcd_fb_div_ratio();

	//CSR18[0:0]
	DS_clkRegs& setdsclk_lcd_override(uint val);
	uint getdsclk_lcd_override();

	//CSR19[11:0]
	DS_clkRegs& setdsclk_lcd_fb_cnt_lv(uint val);
	uint getdsclk_lcd_fb_cnt_lv();

	//CSR20[15:0]
	DS_clkRegs& setdsclk_debugging_ctrl1(uint val);
	uint getdsclk_debugging_ctrl1();

	//CSR21[11:0]
	uint getdsclk_fd_ref_freq();

	//CSR22[11:0]
	uint getdsclk_fd_fb_freq();

	//CSR23[12:0]
	uint getdsclk_fd_diff_freq();

	//CSR24[15:15]
	uint getdsclk_lld_done();

	//CSR24[12:0]
	uint getdsclk_lld_diff_freq();

	//CSR25[11:0]
	uint getdsclk_lld_fb_freq();

	//CSR26[15:0]
	uint getdsclk_misc_status();

	//CSR27[15:12]
	uint getdsclk_calib_voscref();

	//CSR27[11:4]
	uint getdsclk_calib_ioscdaccal();

	//CSR28[15:13]
	DS_clkRegs& setdsclk_bypass_div_slew(uint val);
	uint getdsclk_bypass_div_slew();

	//CSR28[11:0]
	uint getdsclk_lld_ref_freq();

	//CSR29[15:8]
	DS_clkRegs& setptatmix_vco_4(uint val);
	uint getptatmix_vco_4();

	//CSR29[6:5]
	DS_clkRegs& setdsclk_pidrv_refsel(uint val);
	uint getdsclk_pidrv_refsel();

	//CSR29[4:4]
	DS_clkRegs& setdsclk_cml2cmos_pwrdnb(uint val);
	uint getdsclk_cml2cmos_pwrdnb();

	//CSR29[2:2]
	DS_clkRegs& setclkspine_sw_sel(uint val);
	uint getclkspine_sw_sel();

	//CSR29[1:1]
	DS_clkRegs& settxclkspine_sw_sel(uint val);
	uint gettxclkspine_sw_sel();

	//CSR30[15:8]
	DS_clkRegs& setptatmix_vco_5(uint val);
	uint getptatmix_vco_5();

	//CSR30[7:0]
	DS_clkRegs& setptatmix_vco_6(uint val);
	uint getptatmix_vco_6();

	//CSR31[15:8]
	DS_clkRegs& setptatmix_vco_7(uint val);
	uint getptatmix_vco_7();

	//CSR31[7:0]
	DS_clkRegs& setptatmix_vco_8(uint val);
	uint getptatmix_vco_8();

	//CSR32[15:8]
	DS_clkRegs& setptatmix_vco_9(uint val);
	uint getptatmix_vco_9();

	//CSR32[7:0]
	DS_clkRegs& setptatmix_vco_a(uint val);
	uint getptatmix_vco_a();

	//CSR33[15:8]
	DS_clkRegs& setptatmix_vco_b(uint val);
	uint getptatmix_vco_b();

	//CSR33[7:0]
	DS_clkRegs& setptatmix_vco_c(uint val);
	uint getptatmix_vco_c();

	//CSR34[15:8]
	DS_clkRegs& setptatmix_vco_d(uint val);
	uint getptatmix_vco_d();

	//CSR34[7:0]
	DS_clkRegs& setptatmix_vco_e(uint val);
	uint getptatmix_vco_e();

	//CSR35[15:8]
	DS_clkRegs& setptatmix_vco_f(uint val);
	uint getptatmix_vco_f();

	//CSR35[7:0]
	DS_clkRegs& setdsclkspare(uint val);
	uint getdsclkspare();

	//CSR36[15:8]
	DS_clkRegs& setidac_min(uint val);
	uint getidac_min();

	//CSR36[7:0]
	DS_clkRegs& setidac_max(uint val);
	uint getidac_max();

	//CSR37[15:12]
	DS_clkRegs& settrans_min(uint val);
	uint gettrans_min();

	//CSR37[11:8]
	DS_clkRegs& settrans_max(uint val);
	uint gettrans_max();

	//CSR37[7:4]
	DS_clkRegs& setvco_min(uint val);
	uint getvco_min();

	//CSR37[3:0]
	DS_clkRegs& setvco_max(uint val);
	uint getvco_max();

	//CSR38[15:13]
	DS_clkRegs& setdsclk_psel_vco_4(uint val);
	uint getdsclk_psel_vco_4();

	//CSR38[12:10]
	DS_clkRegs& setdsclk_s1sel_vco_4(uint val);
	uint getdsclk_s1sel_vco_4();

	//CSR38[9:8]
	DS_clkRegs& setdsclk_s2sel_vco_4(uint val);
	uint getdsclk_s2sel_vco_4();

	//CSR38[6:4]
	DS_clkRegs& setdsclk_injlev_vco_4(uint val);
	uint getdsclk_injlev_vco_4();

	//CSR38[2:0]
	DS_clkRegs& setdsclk_injtune_vco_4(uint val);
	uint getdsclk_injtune_vco_4();

	//CSR39[15:13]
	DS_clkRegs& setdsclk_psel_vco_5(uint val);
	uint getdsclk_psel_vco_5();

	//CSR39[12:10]
	DS_clkRegs& setdsclk_s1sel_vco_5(uint val);
	uint getdsclk_s1sel_vco_5();

	//CSR39[9:8]
	DS_clkRegs& setdsclk_s2sel_vco_5(uint val);
	uint getdsclk_s2sel_vco_5();

	//CSR39[6:4]
	DS_clkRegs& setdsclk_injlev_vco_5(uint val);
	uint getdsclk_injlev_vco_5();

	//CSR39[2:0]
	DS_clkRegs& setdsclk_injtune_vco_5(uint val);
	uint getdsclk_injtune_vco_5();

	//CSR40[15:13]
	DS_clkRegs& setdsclk_psel_vco_6(uint val);
	uint getdsclk_psel_vco_6();

	//CSR40[12:10]
	DS_clkRegs& setdsclk_s1sel_vco_6(uint val);
	uint getdsclk_s1sel_vco_6();

	//CSR40[9:8]
	DS_clkRegs& setdsclk_s2sel_vco_6(uint val);
	uint getdsclk_s2sel_vco_6();

	//CSR40[6:4]
	DS_clkRegs& setdsclk_injlev_vco_6(uint val);
	uint getdsclk_injlev_vco_6();

	//CSR40[2:0]
	DS_clkRegs& setdsclk_injtune_vco_6(uint val);
	uint getdsclk_injtune_vco_6();

	//CSR41[15:13]
	DS_clkRegs& setdsclk_psel_vco_7(uint val);
	uint getdsclk_psel_vco_7();

	//CSR41[12:10]
	DS_clkRegs& setdsclk_s1sel_vco_7(uint val);
	uint getdsclk_s1sel_vco_7();

	//CSR41[9:8]
	DS_clkRegs& setdsclk_s2sel_vco_7(uint val);
	uint getdsclk_s2sel_vco_7();

	//CSR41[6:4]
	DS_clkRegs& setdsclk_injlev_vco_7(uint val);
	uint getdsclk_injlev_vco_7();

	//CSR41[2:0]
	DS_clkRegs& setdsclk_injtune_vco_7(uint val);
	uint getdsclk_injtune_vco_7();

	//CSR42[15:13]
	DS_clkRegs& setdsclk_psel_vco_8(uint val);
	uint getdsclk_psel_vco_8();

	//CSR42[12:10]
	DS_clkRegs& setdsclk_s1sel_vco_8(uint val);
	uint getdsclk_s1sel_vco_8();

	//CSR42[9:8]
	DS_clkRegs& setdsclk_s2sel_vco_8(uint val);
	uint getdsclk_s2sel_vco_8();

	//CSR42[6:4]
	DS_clkRegs& setdsclk_injlev_vco_8(uint val);
	uint getdsclk_injlev_vco_8();

	//CSR42[2:0]
	DS_clkRegs& setdsclk_injtune_vco_8(uint val);
	uint getdsclk_injtune_vco_8();

	//CSR43[15:13]
	DS_clkRegs& setdsclk_psel_vco_9(uint val);
	uint getdsclk_psel_vco_9();

	//CSR43[12:10]
	DS_clkRegs& setdsclk_s1sel_vco_9(uint val);
	uint getdsclk_s1sel_vco_9();

	//CSR43[9:8]
	DS_clkRegs& setdsclk_s2sel_vco_9(uint val);
	uint getdsclk_s2sel_vco_9();

	//CSR43[6:4]
	DS_clkRegs& setdsclk_injlev_vco_9(uint val);
	uint getdsclk_injlev_vco_9();

	//CSR43[2:0]
	DS_clkRegs& setdsclk_injtune_vco_9(uint val);
	uint getdsclk_injtune_vco_9();

	//CSR44[15:13]
	DS_clkRegs& setdsclk_psel_vco_a(uint val);
	uint getdsclk_psel_vco_a();

	//CSR44[12:10]
	DS_clkRegs& setdsclk_s1sel_vco_a(uint val);
	uint getdsclk_s1sel_vco_a();

	//CSR44[9:8]
	DS_clkRegs& setdsclk_s2sel_vco_a(uint val);
	uint getdsclk_s2sel_vco_a();

	//CSR44[6:4]
	DS_clkRegs& setdsclk_injlev_vco_a(uint val);
	uint getdsclk_injlev_vco_a();

	//CSR44[2:0]
	DS_clkRegs& setdsclk_injtune_vco_a(uint val);
	uint getdsclk_injtune_vco_a();

	//CSR45[15:13]
	DS_clkRegs& setdsclk_psel_vco_b(uint val);
	uint getdsclk_psel_vco_b();

	//CSR45[12:10]
	DS_clkRegs& setdsclk_s1sel_vco_b(uint val);
	uint getdsclk_s1sel_vco_b();

	//CSR45[9:8]
	DS_clkRegs& setdsclk_s2sel_vco_b(uint val);
	uint getdsclk_s2sel_vco_b();

	//CSR45[6:4]
	DS_clkRegs& setdsclk_injlev_vco_b(uint val);
	uint getdsclk_injlev_vco_b();

	//CSR45[2:0]
	DS_clkRegs& setdsclk_injtune_vco_b(uint val);
	uint getdsclk_injtune_vco_b();

	//CSR46[15:13]
	DS_clkRegs& setdsclk_psel_vco_c(uint val);
	uint getdsclk_psel_vco_c();

	//CSR46[12:10]
	DS_clkRegs& setdsclk_s1sel_vco_c(uint val);
	uint getdsclk_s1sel_vco_c();

	//CSR46[9:8]
	DS_clkRegs& setdsclk_s2sel_vco_c(uint val);
	uint getdsclk_s2sel_vco_c();

	//CSR46[6:4]
	DS_clkRegs& setdsclk_injlev_vco_c(uint val);
	uint getdsclk_injlev_vco_c();

	//CSR46[2:0]
	DS_clkRegs& setdsclk_injtune_vco_c(uint val);
	uint getdsclk_injtune_vco_c();

	//CSR47[15:13]
	DS_clkRegs& setdsclk_psel_vco_d(uint val);
	uint getdsclk_psel_vco_d();

	//CSR47[12:10]
	DS_clkRegs& setdsclk_s1sel_vco_d(uint val);
	uint getdsclk_s1sel_vco_d();

	//CSR47[9:8]
	DS_clkRegs& setdsclk_s2sel_vco_d(uint val);
	uint getdsclk_s2sel_vco_d();

	//CSR47[6:4]
	DS_clkRegs& setdsclk_injlev_vco_d(uint val);
	uint getdsclk_injlev_vco_d();

	//CSR47[2:0]
	DS_clkRegs& setdsclk_injtune_vco_d(uint val);
	uint getdsclk_injtune_vco_d();

	//CSR48[15:13]
	DS_clkRegs& setdsclk_psel_vco_e(uint val);
	uint getdsclk_psel_vco_e();

	//CSR48[12:10]
	DS_clkRegs& setdsclk_s1sel_vco_e(uint val);
	uint getdsclk_s1sel_vco_e();

	//CSR48[9:8]
	DS_clkRegs& setdsclk_s2sel_vco_e(uint val);
	uint getdsclk_s2sel_vco_e();

	//CSR48[6:4]
	DS_clkRegs& setdsclk_injlev_vco_e(uint val);
	uint getdsclk_injlev_vco_e();

	//CSR48[2:0]
	DS_clkRegs& setdsclk_injtune_vco_e(uint val);
	uint getdsclk_injtune_vco_e();

	//CSR49[15:13]
	DS_clkRegs& setdsclk_psel_vco_f(uint val);
	uint getdsclk_psel_vco_f();

	//CSR49[12:10]
	DS_clkRegs& setdsclk_s1sel_vco_f(uint val);
	uint getdsclk_s1sel_vco_f();

	//CSR49[9:8]
	DS_clkRegs& setdsclk_s2sel_vco_f(uint val);
	uint getdsclk_s2sel_vco_f();

	//CSR49[6:4]
	DS_clkRegs& setdsclk_injlev_vco_f(uint val);
	uint getdsclk_injlev_vco_f();

	//CSR49[2:0]
	DS_clkRegs& setdsclk_injtune_vco_f(uint val);
	uint getdsclk_injtune_vco_f();

};

#endif // HILINKDSCLKREGS_H_
