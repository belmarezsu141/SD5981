#ifndef HILINKCSCLKREGS_H_
#define HILINKCSCLKREGS_H_

#include "HiLink_Regs_Base.h"
#define CS_CLK_CSR_NUM 64

class CS_clkRegs:public HILINK_Regs_Base{
protected:
	CS_clkRegs();
	virtual ~CS_clkRegs();

	uint& get_csr(uint csrIndex);
	virtual void get_default_MacroLaneID(T_MacroLaneID& id);

public:
	bool get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos);
	static CS_clkRegs& getInstance();
	string getName();
	uint getCSRCount();
	E_HILINK_REGISTER_TYPE getType();
	uint get_HILINK_MAX_LANE_NUM();
	uint getAddressMapToHiLink(int csrIndex);

///////////////////////////////////////////////////////////////////////////

private:
	class _REG_INFO{
		public:

	/// Clockslice power down control. Active low.
	/// 0 = Power down the clockslice except oscillator and refclk associated circuit.
	/// 1 = Power up the clockslice.
			const T_REG_INFO_EX& cspwrdb();	//CSR0[15:15]

	/// Only applicable when there is a serviceslice in the macro.
			const T_REG_INFO_EX& ssrefclk0div2sel();	//CSR0[14:14]

	/// Only applicable when there is a serviceslice in the macro.
			const T_REG_INFO_EX& ssrefclk1div2sel();	//CSR0[13:13]

	/// Select the refclk bus 1's source. Only applicable when there is a serviceslice applicable.
	/// 0 = Choose the reference clock 1 from the bump as the refclk bus 1's source.
	/// 1 = Choose a CMOS reference clock from the core as the refclk bus 1's source. Applicable only when the CMOS reference clock is available to HiLink.
	/// Note: If the CMOS reference clock is not available to HiLink, this bit should be set to 0.
			const T_REG_INFO_EX& sscmosrefclksel();	//CSR0[12:12]

	/// Select the source of PLL's reference clock.
	/// 0 = Select the reference clock from REFCLKBUS0 as PLL's reference clock.
	/// 1 = Select the reference clock from REFCLKBUS1 as PLL's reference clock.
			const T_REG_INFO_EX& refclksel();	//CSR0[11:11]

	/// Life clock select.
	/// 0 = Choose one of the reference clocks as life clock.
	/// 1 = Choose word clock derived from LCVCO as life clock.
			const T_REG_INFO_EX& lifeclksel();	//CSR0[10:10]

	/// Core clock select.
	/// 0 = Choose local life clock as the source of core clock.
	/// 1 = Choose life clock from the other clockslice as the source of core clock.
			const T_REG_INFO_EX& coreclksel();	//CSR0[9:9]

	/// Programs loop filter capacitors. Binary weighted capacitor array, where C=LPFCAP*Cmin, Cmin=750fF (after die shrink), for example:
	/// 0000: C = 0
	/// 0001: C = Cmin
	/// 0010: C = 2*Cmin
	/// ＃...
	/// 1111: C = 15*Cmin
	/// 
	/// Only used in PLF mode.
			const T_REG_INFO_EX& lpfcap();	//CSR0[7:4]

	/// Programs loop filter total resistance. Thermometer encoded. Only five settings are valid.
	/// 0000: R =  2.6 kohm
	/// 0001: R =  1.55 kohm
	/// 0011: R =  0.85 kohm
	/// 0111: R =  0.475 kohm
	/// 1111: R =  0.25 kohm
	/// 
	/// Only used in PLF mode
			const T_REG_INFO_EX& lpfres();	//CSR0[3:0]

	/// CML divider ratio (the 'K' divider). 
	///                div_to_lane     div_to_pll
	///                      (Kb)                     (Ka)
	/// 00 =              1                           2
	/// 01 =              1                           3
	/// 10 =              2                           2
	/// 11 =              2                           3
			const T_REG_INFO_EX& cmldiv();	//CSR1[15:14]

	/// The P value of the feedback divider ratio (part of the 'N' divider),
	/// which is determined by N=2*P+S+3, where the following conditions shall be met: 
	/// normal mode(ssc-off) : P ≡1;S≡0; and S is the maximum possible value ≒ P
	/// For SSC-on Mode: P ≡6;S≡5; and S is the maximum possible odd value less than P or (P-1)
			const T_REG_INFO_EX& fbdivp();	//CSR1[13:8]

	/// The S value of the feedback divider ratio (part of the 'N' divider), 
	/// which is determined by N=2*P+S+3, where the following conditions shall be met: 
	/// normal mode(ssc-off) : P ≡1;S≡0; and S is the maximum possible value ≒ P
	/// For SSC-on Mode: P ≡6;S≡5; and S is the maximum possible odd value less than P or (P-1)
			const T_REG_INFO_EX& fbdivs();	//CSR1[7:2]

	/// Reference clock divider ratio (the 'M' divider).
	/// 00 = 1
	/// 01 = 1 (default)
	/// 10 = 2
	/// 11 = 3
			const T_REG_INFO_EX& refclkdiv();	//CSR1[1:0]

	/// Divider ratio for lifeclk2dig. Used for life clock generation.
	/// 00 = divided by 1
	/// 01 = divided by 2
	/// 10 = divided by 3
	/// 11 = divided by 4
			const T_REG_INFO_EX& lifeclk2digdiv();	//CSR2[15:14]

	/// Divider ratio for wordclk2dig. Used for life clock generation.
	/// 00 = divided by 1
	/// 01 = divided by 2
	/// 10 = divided by 3
	/// 11 = divided by 4
			const T_REG_INFO_EX& wordclk2digdiv();	//CSR2[13:12]

	/// LCVCO out-of-lock threshold (by default, choose from 1/4096 to 31/4096).
	/// Note: For LCVCO to lock, this field should not be programmed to 0.
			const T_REG_INFO_EX& lcvcololthr();	//CSR2[10:6]

	/// LCVCO loss-of-clock threshold.
	/// 000 = 128
	/// 001 = 256
	/// 010 = 512
	/// 011 = 1024
	/// 100 = 2048
	/// 101 = 4096
	/// 11x = 4096
			const T_REG_INFO_EX& lcvcolocthr();	//CSR2[5:3]

	/// LCVCO loss-of-lock mode. Choose how loss-of-lock detection will start after LCVCO calibration is done (coarse tune).
	/// 0 = automatically start.
	/// 1 = manually start.
			const T_REG_INFO_EX& lcvcololmode();	//CSR2[2:2]

	/// LCVCO out-of-lock status. Out-of-lock status is latched until next detection finished.
	/// 0 = LCVCO locked
	/// 1 = LCVCO out of lock
			const T_REG_INFO_EX& lcvcooutoflock();	//CSR2[1:1]

	/// Loss of LCVCO clock indicator. Status is latched until next detection finished.
	/// 0 = LCVCO clock is active
	/// 1 = LCVCO clock is not active
			const T_REG_INFO_EX& lossoflcvcoclk();	//CSR2[0:0]

	/// LCVCO power down control. Active low.
	/// 0 = Power down the LCVCO.
	/// 1 = Power up the LCVCO.
			const T_REG_INFO_EX& pllpwrdb();	//CSR3[15:15]

	/// Active high. Swaps PFD polarity.
	/// LOW 每 negative polarity. DLF mode
	/// HIGH 每 positive polarity PLF mode.
			const T_REG_INFO_EX& pfdupdnswap();	//CSR3[14:14]

	/// Force the PFD output to be UP.
	/// 0 = Let the PFD detect frequency and phase difference.
	/// 1 = Force the PFD output to be UP.
	/// Note: setting both PFDFORCEUP and PFDFORCEDN to 1 is not allowed.
			const T_REG_INFO_EX& pfdforceup();	//CSR3[13:13]

	/// Force the PFD output to be DOWN.
	/// 0 = Let the PFD detect frequency and phase difference.
	/// 1 = Force the PFD output to be DOWN.
	/// Note: setting both PFDFORCEUP and PFDFORCEDN to 1 is not allowed.
			const T_REG_INFO_EX& pfdforcedn();	//CSR3[12:12]

	/// Select the pulse width of the PFD outputs (both UP/DOWN) to adjust the linearity of the PFD.
	/// 00 = 61ps
	/// 01 = 85ps
	/// 10 = 120ps
	/// 11 = 158ps
			const T_REG_INFO_EX& pfdpulsewidth();	//CSR3[11:10]

	/// Active high. Used to connect 532K resistor as pull-up or pull-down to the DLF inputs as follows: 
	/// 00 = Not connected
	/// 01 = 532K pull-up resistors connected to DLF inputs
	/// 10 = 532K pull-down resistors connected to DLF inputs
	/// 11 = Not allowed
			const T_REG_INFO_EX& cpauxres();	//CSR3[9:8]

	/// Active low.  Powers down the passive-mode CMFB opamp.
			const T_REG_INFO_EX& cpcmfbpwrdb();	//CSR3[7:7]

	/// Active low. Powers down the PLL ※integral§ CPs such that only residual leakage currents are flowing.
			const T_REG_INFO_EX& cpintegcppwrdb();	//CSR3[6:6]

	/// These control bits are only used in PLF mode. Selects bias current and degeneration resistance in charge pump cmfb opamp as follows: 
	/// CPRDEG[0] = 0 每 Rdegen= 500 ohms
	/// CPRDEG[0] = 1 每 Rdegen= 188 ohms
	/// CPRDEG[1] = 0 每 I_bias= 50uA
	/// CPRDEG[1] = 1 每 I_bias= 25uA
			const T_REG_INFO_EX& cprdeg();	//CSR3[5:4]

	/// Configures the ※proportional§ CP to operate in DLF-mode or PLF-mode.
	/// LOW - selects ※DLF-mode.§ The two replica driver opamps are disabled and the replica charge pumps are both connected to the vref common mode voltage.
	/// High - selects ※PLF-mode.§ The two replica driver opamps are powered-on and they are used to drive the replica charge pumps.  The vref common mode voltage is not connected to the proportional charge pump.
			const T_REG_INFO_EX& cpvrefpropsel();	//CSR3[3:3]

	/// Programs the common-mode reference for both the DLF mode and the PLF mode. The voltage levels are selected as follows: 
	/// 000- 498 mV; 
	/// 001- 512 mV
	/// ;010- 522 mV; 
	/// 011- 530 mV; 
	/// 100- 457 mV; 
	/// 101- 465 mV; 
	/// 110- 475 mV; 
	/// 111- 489 mV.
			const T_REG_INFO_EX& cpreflvl();	//CSR3[2:0]

	/// input common mode adjusting for Kb Divider
	/// 00: lvcc_regulated - 0.3V
	/// 01: lvcc_regulated - 0.33V
	/// 10: lvcc_regulated - 0.36V
	/// 11: lvcc_regulated - 0.39V
			const T_REG_INFO_EX& cmldivkbvcmsel();	//CSR4[15:14]

	/// change the integral and proportional current
	/// 0: the proptional cp current is 320uA base with 80uA control step
	/// 1:the proptional cp current is 160uA base with 40uA control step
			const T_REG_INFO_EX& cp_i_propchp_tune();	//CSR4[13:13]

	/// Programs ※integral§ charge pump current from 20 to 160uA in 20uA steps.
			const T_REG_INFO_EX& cpcurrentint();	//CSR4[12:10]

	/// Bits [3:0] program ※proportional§ charge pump current from 320 to 1600uA in 80uA steps for both DLF mode and PLF mode. Bits [5:4] are used only in PLF mode to select the output drive capability of the replica driver opamps. Quiescent drive capability changes from  100uA  to  400uA typical in 100uA  steps. The drive capability will increase as the operating point moves away from the quiescent condition.
			const T_REG_INFO_EX& cpcurrent();	//CSR4[9:4]

	/// Changing these R and C settings will cause the phase margin of the passive CMFB opamp circuit to increase and decrease.
	/// These control bits are only used in PLF mode. Changing these R and C settings will cause the phase margin of the passive CMFB opamp circuit to increase and decrease. Programs the resistor and capacitor values in the compensation network of the PLF-mode CP cmfb circuit according to the following:
	/// Cp_rzero_cmfb[3,2] = 00   R= 2379 ohms
	/// Cp_rzero_cmfb[3,2] = 01   R= 884 ohms
	/// Cp_rzero_cmfb[3,2] = 10   R= 170 ohms
	/// Cp_rzero_cmfb[3,2] = 11   R= 2005 ohms
	/// Cp_rzero_cmfb[1,0] = 00   C= 1.128 pF
	/// Cp_rzero_cmfb[1,0] = 01   C= 3.385 pF
	/// Cp_rzero_cmfb[1,0] = 10   C= 4.513 pF
	/// Cp_rzero_cmfb[1,0] = 11   C= 6.77 pF
			const T_REG_INFO_EX& cprzerocmfb();	//CSR4[3:0]

	/// LOW - selects ※DLF-mode§ 
	/// High - selects ※PLF-mode§
			const T_REG_INFO_EX& cpdlfmuxsel();	//CSR5[15:15]

	/// control vref_gen drive ability
	/// ;cp_spare[0]: connected n0 and p0 to vref_gen output
	/// ;cp_spare[1]: connected n1 and p1 to vref_gen output
	/// cp_spare[2]: connected n2 and p2 to vref_gen output
			const T_REG_INFO_EX& cpspare2to0();	//CSR5[14:12]

	/// Digital loop filter power down control. Active low.
			const T_REG_INFO_EX& dlfpwrdb();	//CSR5[11:11]

	/// extra mim cap sel for dlf, high to connect into the circuit
	/// cap value is 10.9pF
			const T_REG_INFO_EX& dlfextramimcap();	//CSR5[10:10]

	/// Active  LOW power down for the DLF test mode. Powers down and disconnect DTB and ATB DLF muxes.
			const T_REG_INFO_EX& dlftstpwrdb();	//CSR5[9:9]

	/// power down CMFB of  DLF mode
			const T_REG_INFO_EX& dlfcmfbpwrdb();	//CSR5[8:8]

	/// Sets S and H clock sample width 
	/// HIGH 每 2 ps
	/// LOW 每 1 ps
			const T_REG_INFO_EX& dlfshdelsel();	//CSR5[7:7]

	/// PLL digital test bus (DTB) control When DLF test mode enabled, ends following test signals in said order to the ※dtb_o§ pin: ph1, ph1a, ph2, ph2a, samp_clk_i, fref_i, calrstb_i, cmfpwrdb_i.
			const T_REG_INFO_EX& dlfseldtb();	//CSR5[6:2]

	/// set the sample capacitor of  S/H stage in DLF mode. 
	/// 00: 0
	/// 01: 1.55p
	/// 10: 1.55p
	/// 11: 3.1p
			const T_REG_INFO_EX& dlfshcapsel();	//CSR5[1:0]

	/// Optional bias current control for the future.
			const T_REG_INFO_EX& cmlbufoutbiassel();	//CSR6[15:14]

	/// Bits [2:0] used for replica bias common mode select from 900 to 780 mV in 15 mV steps  (thermal code)
	/// Bits [5:3] used for ※pbias§ override in a test mode range from 0 to 550 mV (thermometer code)
			const T_REG_INFO_EX& cmldivbiascal();	//CSR6[13:8]

	/// lcvco_spare[3:2] are for spare pins
	/// lcvco_spare[1]is for peak detector power down
	/// 0:  enable peak detector / 1:  power down peak detector 
	/// lcvco_spare[0] is for vco temperature direction switch.
	/// 0:  normal direction / 1:  opposite direction
			const T_REG_INFO_EX& lcvcospare();	//CSR6[7:4]

	/// One hot coded.
	/// 000 = 0000_0001 (reserved)
	/// 001 = 0000_0010 (reserved)
	/// 010 = 0000_0100 (reserved)
	/// 011 = 0000_1000 (reserved)
	/// 100 = 0001_0000 (LCVCO min amplitude)
	/// 101 = 0010_0000 (LCVCO max amplitude)
	/// 110 = 0100_0000 (reserved)
	/// 111 = 1000_0000 (reserved)
			const T_REG_INFO_EX& lcvcoselpeaklvl();	//CSR6[2:0]

	/// When VCO calibration is auto-mode, Force Power On peak detector
			const T_REG_INFO_EX& lcvco_pwron_force_en();	//CSR7[15:15]

	/// Choose LCVCO tuning band in manual calibration mode, i.e., when LCVCOCALMODE is set to 1.
	/// 000 = 1st band (highest)
	/// 001 = 2nd band
	/// 010 = 3rd band 
	/// 011 = 4th band (lowest on V100)
	/// 100 = 5th band  (reserved for future use)
	/// 101 = 6th band (reserved for future use)
	/// 11x = 7th band (reserved for future use)
			const T_REG_INFO_EX& lcvcobandsel();	//CSR7[14:12]

	/// VCO tank freqency calibration code, 
	/// freqcal[19:1] is thermo code, freqcal[0] is binary code, which weight is 0.5. 
	/// 3 settings may overlaps in one frequency range. 
	/// 0000_0000_0000_0000_0000      0f
	/// 00000000000000000001      10f
	/// 00000000000000000010      20f
	/// 00000000000000000011      30f
	/// 00000000000000000110      40f
	/// 00000000000000000111      50f
	/// 00000000000000001110      60f
	/// ......
	/// 01111111111111111111      18*20f+10f
	/// 1111_1111_1111_1111_1110      19*20f
	/// 11111111111111111111      19*20f+10f
			const T_REG_INFO_EX& lcvcofreqcal();	//CSR7[10:5]

	/// Set the LCVCO amplitude value for min and max amplitude calibrations in manual calibration mode, i.e., when LCVCOCALMODE is set to 1.  Binary setting needs to be converted to gray code, then thermo code before sending to the analog.
	/// 00000 = 0000_0000_0000_0000 (min)
	/// 00001 = 0000_0000_0000_0001
	/// 00010 = 0000_0000_0000_0011
	/// ＃＃
	/// 01111 = 0111_1111_1111_1111
	/// 1xxxx = 1111_1111_1111_1111 (max)
			const T_REG_INFO_EX& lcvcoitank();	//CSR7[4:0]

	/// Hsclk Distribution  powerdown control, Active low.
			const T_REG_INFO_EX& hsclkfrclkspinepwrdb();	//CSR8[14:14]

	/// power down extra hsclk drvier in CSH V102
	/// 0:  power down
	/// 1:  power on
			const T_REG_INFO_EX& hsclkfromsspwrdb();	//CSR8[13:13]

	/// Disconnected internally
			const T_REG_INFO_EX& hsclktosspwrdb();	//CSR8[12:12]

	/// Binary tail current control of buffers connected to a clockslice cmldivider 
	/// 00 每 0 % current increase
	/// 01 每 16 % current increase
	/// 10 每 30 % current increase
	/// 11 每 50 % current increase
			const T_REG_INFO_EX& hsclkfromcsbiasctrl();	//CSR8[11:10]

	/// Disconnected internally
			const T_REG_INFO_EX& hsclkfromssbiasctrl();	//CSR8[9:8]

	/// Set current of extra hsclk driver, 
	/// Icp = 600uA +hsclk_from_cs_mux_bias_ctrl[1:0]*100uA.
			const T_REG_INFO_EX& hsclktossbiasctrl();	//CSR8[7:6]

	/// Hsclk Distribution  replica bias common mode select from 900 to 780 mV in 15 mV steps .
			const T_REG_INFO_EX& hsclkreploadctrl();	//CSR8[5:3]

	/// Hsclk Distribution  replica load selection.
			const T_REG_INFO_EX& hsclkreprefsel();	//CSR8[2:0]

	/// hsclkspare[2:1] is not used currently
	/// hsclkspare[0] is used to choose buffer input common mode voltage
	/// 0:Vcm_buf=Vref_buf; 
	/// 1:Vcm_buf=Vref
			const T_REG_INFO_EX& hsclkspare();	//CSR9[14:12]

	/// CS Bias Top powerdown control, Active Low.
			const T_REG_INFO_EX& biascmupwrdb();	//CSR9[8:8]

	/// biascvcal[7:2] not used currently
	/// biascvcal[1]  icc common mode rejection selection
	///     0: turn on the common mode rejection
	///     1: turn off the common mode rejection
	/// biascvcal[0]  icv common mode rejection selection
	///     0: turn on the common mode rejection
	///     1: turn off the common mode rejection
			const T_REG_INFO_EX& biascvcal();	//CSR9[7:0]

	/// 0 = Clockslice bias receivers operate in normal mode
	/// ;1 = Clockslice bias receivers in emergency operating mode.
			const T_REG_INFO_EX& csrxbiasbackupgen();	//CSR10[15:15]

	/// csspare[14] is for H16 testchip macro B spine clock 1 selection
	///     0: from CSH0
	///     1: from CSL
	/// csspare[13:7] are CS Analog Top Spare bits
	/// csspare[6]  is for CS ATB output buffer selection
	///     0: output from buffer
	///     1: directly output (bypass buffer)
	/// csspare[5:4] Regulator referrence voltage tuning(default value : 2'b10)
	///     00 : 0.717V
	///     01 : 0.777V
	///     10 : 0.797V
	///     11 : 0.827V
	/// csspare[3] DLF Regulator loading adjust power down(default value : 1'b1); 
	///     0: power down
	///     1: active
	/// csspare[2] CML Regulator loading adjust power down(default value : 1'b1); 
	///     0: power down
	///     1: active
	/// csspare[1] PLL Regulator loading adjust power down(default value : 1'b1); 
	///     0: power down
	///     1: active
	/// csspare[0] is for low-offset comparator calibration mode selection(default value : 1'b0)
	///    0: vrefp and vrefm
	///    1: vss
			const T_REG_INFO_EX& csspare();	//CSR10[14:0]

	/// CS Regulator powerdown control, Active low.
			const T_REG_INFO_EX& vregpwrdb();	//CSR11[15:15]

	/// change the connection of the noise reduction cap(120pF)
	/// 0: disconnect the noise reduction cap
	/// 1: connect the noise reduction cap
			const T_REG_INFO_EX& vregcapsel();	//CSR11[12:12]

	/// adjust bleed current value on vreg power down mode
	/// bleed current = 75uA * vreg_pll_selfbleed[3:0]
			const T_REG_INFO_EX& vregselfbleed();	//CSR11[11:8]

	/// one hot code, set reference voltage of opamp in regulator
	/// 00000001: 0.834
	/// 00000010: 0.855
	/// 00000100: 0.899
	/// 00001000: 0.958
	/// 00010000: 1.004 (default)
	/// 00100000: 1.024
	/// 01000000: 1.055
	/// 10000000: 1.077
			const T_REG_INFO_EX& vregplllvl();	//CSR11[7:0]

	/// CS Calibraiton Module powerdown control, Active low.
			const T_REG_INFO_EX& calpwrdb();	//CSR12[15:15]

	/// Configures the PLL Control Path such that the VCO can be calibrated with zero volts differential control voltage. Disables the PFD, forces charge pump currents to flow in the reset pathways, enables the replica opamps and common-mode opamp, connects charge pump outputs to common mode reference voltage. Active low.
			const T_REG_INFO_EX& calrstb();	//CSR12[14:14]

	/// Bypass post maximum amplitude calibration frequency check enable, active high.
			const T_REG_INFO_EX& cs_post_lckchk_bypass();	//CSR12[8:8]

	/// Bypass initial amplitude calibration enable, active high.
			const T_REG_INFO_EX& cs_initamp_calib_bypass();	//CSR12[7:7]

	/// CS Low-offset Comparator calibration enable.
	/// 0=disable
	/// 1=enable
			const T_REG_INFO_EX& cslowoffcal();	//CSR12[6:6]

	/// Binary coding, Following is convertion.
	/// 63: +31
	/// 62: +30
	/// .
	/// .
	/// .
	/// 1: -30
	/// 0: -31
			const T_REG_INFO_EX& cslowoffsetctrl();	//CSR12[5:0]

	/// Select whether LCVCO calibrations (offset, min amplitude, frequency, max amplitude) are done automatically or manually. Switching from manul mode to automatic mode restarts the auto calibration process.
	/// 0 = Automatic LCVCO calibrations
	/// 1 = Manual LCVCO calibrations
			const T_REG_INFO_EX& lcvcocalmode();	//CSR13[15:15]

	/// Choose what to calibrate in manual calibration mode, i.e., when LCVCOCALMODE is set to 1.
	/// 00 = Comparator offset compensation
	/// 01 = Amplitude calibration (both min and max)
	/// 10 = Frequency calibration (frequency coarse tune)
	/// 11 = Reserved
			const T_REG_INFO_EX& lcvcocalctrl();	//CSR13[13:10]

	/// 
			const T_REG_INFO_EX& ptatcalout();	//CSR13[9:9]

	/// 
			const T_REG_INFO_EX& cvcalout();	//CSR13[8:8]

	/// 
			const T_REG_INFO_EX& comparestatus();	//CSR13[7:6]

	/// 
			const T_REG_INFO_EX& dtbout();	//CSR13[5:5]

	/// LCVCO calibrations completed. 
	/// 0 = LCVCO calibrations do not finish yet.
	/// 1 = LCVCO calibrations finish.
			const T_REG_INFO_EX& lcvcocaldone();	//CSR13[4:4]

	/// LCVCO calibrations didn't succeed. Not available in current design.
	/// 0 = LCVCO calibrations didn't complete successfully.
	/// 1 = LCVCO calibrations completed successfully.
			const T_REG_INFO_EX& lcvcocalerr();	//CSR13[3:3]

	/// Status of LCVCO calibrations. If LCVCO calibrations didn't succeed, this register gives the internals status and/or conditions of the calibration processes.
	/// Mapping TBD.
			const T_REG_INFO_EX& lcvcocalstatus();	//CSR13[2:0]

	/// Clock Slice Digital test bus select.
	/// 0000 = wordclk2dig_div2
	/// 0001 = wordclk2dig
	/// 0010 = lifeclk2dig
	/// 0011= refclk2dig
	/// 0100 = divclk2dig
	/// 0101 = divclk2dig devide by 2
	/// 0110 = wordclk2dig_16b32b
	/// 1xxx = DTB out from CS analog
	/// default = wordclk2dig
			const T_REG_INFO_EX& csdtbsel();	//CSR14[15:12]

	/// Regulator ATB selection control.
			const T_REG_INFO_EX& vregatbctrl();	//CSR14[11:3]

	/// CS Top ATB BUS selection.
			const T_REG_INFO_EX& csatbfinalsel();	//CSR14[2:0]

	/// Clockslice analog test bus select. Select which analog signal to be brought out through analog test muxes for observation.
	/// Mapping TBD
			const T_REG_INFO_EX& csatbsel23to16();	//CSR15[15:8]

	/// ssspare[7:4] are serviceslice spare bits.
	/// ss_spare[3:1] are for Process Sensor output selection
	///     000: core ulvt nmos voltage output
	/// ;    001: core svt nmos voltage ouput
	/// ;    010: io nmos voltage output
	/// ;    011: core ulvt pmos voltage output
	/// ;    100: core svt pmos voltage output
	/// ;    101: io pmos voltage output
	/// ;    110: ploy res voltage output
	/// ;    111: iccp50 current output
	/// ssspare[0] is for ATB signal selection.
	///     0:  select Bandgap atb from buffer
	///     1:  bypass Bandgap atb from buffer
			const T_REG_INFO_EX& ssspare();	//CSR15[7:0]

	/// Serviceslice power down control. Active low.
	/// 0 = Power down the serviceslice
	/// 1 = Power up the serviceslice
			const T_REG_INFO_EX& sspwrdb();	//CSR16[15:15]

	/// SS refclk0 power down Active low
			const T_REG_INFO_EX& ssrefclk0pwrdb();	//CSR16[14:14]

	/// SS refclk1 power down Active low
			const T_REG_INFO_EX& ssrefclk1pwrdb();	//CSR16[13:13]

	/// Currently no use.
			const T_REG_INFO_EX& sshsclkss2cspwrdb();	//CSR16[9:9]

	/// Currently no use.
			const T_REG_INFO_EX& sshsclkcs2sspwrdb();	//CSR16[8:8]

	/// SS reference clock0 CML-div2 powerdown control, Active low.
			const T_REG_INFO_EX& ssrefclk0cmldivpwrdb();	//CSR16[7:7]

	/// Currently no use.
			const T_REG_INFO_EX& ssrefclk0atten();	//CSR16[5:4]

	/// SS reference clock1 CML-div2 powerdown control, Active low.
			const T_REG_INFO_EX& ssrefclk1cmldivpwrdb();	//CSR16[3:3]

	/// Currently no use.
			const T_REG_INFO_EX& ssrefclk1atten();	//CSR16[1:0]

	/// BG600mV source selection for CC current generation.
	/// 0 = Bandgap 800mV
	/// 1 =  Lvcc divided 800mV.
			const T_REG_INFO_EX& bg600mvlvccresdiv();	//CSR17[15:15]

	/// Active high. Test mode which disables the constant current generator when set to 0
			const T_REG_INFO_EX& bgccen();	//CSR17[14:14]

	/// Active high. Test mode which disables the constant voltage bandgap when set to 0
			const T_REG_INFO_EX& bgcven();	//CSR17[13:13]

	/// Active high. Test mode which disables the PTAT bandgap when set to 0
			const T_REG_INFO_EX& bgpaten();	//CSR17[12:12]

	/// Test mode which forces the startup circuit in the bandgap or the ptat to be active; 
	/// Bg_force_start[0]=0   no effect; 
	/// Bg_force_start[0]=1   bg force startup; 
	/// Bg_force_start[1]=0   no effect; 
	/// Bg_force_start[1]=1   ptat force startup
			const T_REG_INFO_EX& bgforcestart();	//CSR17[11:10]

	/// Test mode which disables the startup circuit in the bandgap or the ptat; 
	/// bg_start_bypass[0]=0   no effect; 
	/// bg_start_bypass[0]=1   bg disable startup; 
	/// bg_start_bypass[0]=1   bg disable startup; 
	/// bg_start_bypass[1]=0   no effect; 
	/// bg_start_bypass[1]=1   ptat disable startup
			const T_REG_INFO_EX& bgstartbypass();	//CSR17[9:8]

	/// Bandgap Bypass control bit.
			const T_REG_INFO_EX& bgbypass();	//CSR17[7:0]

	/// Not used (reserved for future use).
			const T_REG_INFO_EX& hvvbgccin();	//CSR18[15:15]

	/// Selects bandgap voltage output value according to the following ; 
	/// 000:  800 mV; 
	/// 001:  769 mV; 
	/// 010:  738 mV; 
	/// 011:  707 mV; 
	/// 100:  922 mV; 
	/// 101:  891 mV; 
	/// 110:  861 mV; 
	/// 111:  830 mV
			const T_REG_INFO_EX& vbgreflvl();	//CSR18[14:12]

	/// Not used (reserved for future use).
			const T_REG_INFO_EX& hvvbgptatin();	//CSR18[11:11]

	/// Selects ptat voltage output value according to the following ; 
	/// 000:  800 mV; 
	/// 001:  769 mV; 
	/// 010:  738 mV; 
	/// 011:  707 mV; 
	/// 100:  922 mV; 
	/// 101:  891 mV; 
	/// 110:  861 mV; 
	/// 111:  830 mV
			const T_REG_INFO_EX& vbgptatlvl();	//CSR18[10:8]

	/// Spare pins, not connected in this revision
			const T_REG_INFO_EX& biasselptatmix();	//CSR18[7:0]

	/// Only bit[11:0] are used.
			const T_REG_INFO_EX& ssatbsel();	//CSR19[15:0]

	/// Clear the loss of lock detector. Active high.
			const T_REG_INFO_EX& cs_lld_clr();	//CSR20[13:13]

	/// Clear the frequency detector. Active high.
			const T_REG_INFO_EX& cs_fd_clr();	//CSR20[12:12]

	/// Clear the status of calibration. Active high.
			const T_REG_INFO_EX& cs_calib_clr();	//CSR20[11:11]

	/// Start clockslice loss of clock detector. Active rising edge.
			const T_REG_INFO_EX& cs_lcd_start();	//CSR20[10:10]

	/// Start clockslice loss of lock detector. Active rising edge.
			const T_REG_INFO_EX& cs_lld_start();	//CSR20[9:9]

	/// Start clockslice calibration. Active rising edge.
			const T_REG_INFO_EX& cs_calib_start();	//CSR20[8:8]

	/// Enable clockslice loss of clock detector. Active high.
	/// 0 = Don't enable the detector, Gating the clock
	/// 1 = Enable the detector
			const T_REG_INFO_EX& cs_lcd_enable();	//CSR20[7:7]

	/// Enable clockslice loss of lock detector. Active high.
	/// 0 = Don't enable the detector, Gating the clock
	/// 1 = Enable the detector
			const T_REG_INFO_EX& cs_lld_enable();	//CSR20[6:6]

	/// Enable clockslice calibration. Active high.
	/// 0 = Don't enable calibration, Gating the clock
	/// 1 = Enable calibration
			const T_REG_INFO_EX& cs_calib_enable();	//CSR20[5:5]

	/// Clockslice loss of clock detector reset. Active low.
	/// 0 = Reset loss of clock detector part
	/// 1 = Reset is not active
			const T_REG_INFO_EX& cs_lcd_soft_rst_n();	//CSR20[4:4]

	/// Clockslice loss of lock detector reset. Active low.
	/// 0 = Reset loss of lock detector part
	/// 1 = Reset is not active
			const T_REG_INFO_EX& cs_lld_soft_rst_n();	//CSR20[3:3]

	/// Clockslice calibration reset. Active low.
	/// 0 = Reset calibration part
	/// 1 = Reset is not active
			const T_REG_INFO_EX& cs_calib_soft_rst_n();	//CSR20[2:2]

	/// Clockslice global reset. Active low.
	/// 0 = Reset whole digital circuit
	/// 1 = Reset is not active
			const T_REG_INFO_EX& cs_glb_soft_rst_n();	//CSR20[0:0]

	/// Clockslice analog test bus select. Select which analog signal to be brought out through analog test muxes for observation.
	/// Mapping TBD.
			const T_REG_INFO_EX& csatbsel15to0();	//CSR21[15:0]

	/// Control direction of general purpose calibration FSM for debugging.
	/// [6]: For lock of check calibration.
	/// [5]: For maximum amplitude calibration.
	/// [4]: For band selection calibration.
	/// [3]: For frequency calibration.
	/// [2]: For minimum amplitude calibration.
	/// [1]: For initial amplitude calibration.
	/// [0]: For offset calibration.
			const T_REG_INFO_EX& cs_direction_ctrl();	//CSR22[6:0]

	/// Calibration mode configuration for band selection calibration.
			const T_REG_INFO_EX& cs_calib_mode_bdsel();	//CSR23[14:12]

	/// Calibration mode configuration for frequency calibration.
			const T_REG_INFO_EX& cs_calib_mode_freqcal();	//CSR23[11:9]

	/// Calibration mode configuration for minimum amplitude calibration.
			const T_REG_INFO_EX& cs_calib_mode_minamp();	//CSR23[8:6]

	/// Calibration mode configuration for initial amplitude calibration.
			const T_REG_INFO_EX& cs_calib_mode_initamp();	//CSR23[5:3]

	/// Calibration mode configuration for offset calibration.
			const T_REG_INFO_EX& cs_calib_mode_offset();	//CSR23[2:0]

	/// Calibration mode configuration for lock of check calibration.
			const T_REG_INFO_EX& cs_calib_mode_lckchk();	//CSR24[5:3]

	/// Calibration mode configuration for maximum amplitude calibration.
			const T_REG_INFO_EX& cs_calib_mode_maxamp();	//CSR24[2:0]

	/// Define minimum calibration control code for initial amplitude calibration.
			const T_REG_INFO_EX& cs_ctrl_code_min_initamp();	//CSR25[15:11]

	/// Define maximum calibration control code for offset calibration.
			const T_REG_INFO_EX& cs_ctrl_code_max_offset();	//CSR25[10:5]

	/// Define minimum calibration control code for offset calibration.
			const T_REG_INFO_EX& cs_ctrl_code_min_offset();	//CSR25[4:0]

	/// Define maximum calibration control code for minimum amplitude calibration.
			const T_REG_INFO_EX& cs_ctrl_code_max_minamp();	//CSR26[14:10]

	/// Define minimum calibration control codefor minimum amplitude calibration.
			const T_REG_INFO_EX& cs_ctrl_code_min_minamp();	//CSR26[9:5]

	/// Define maximum calibration control code for initial amplitude calibration.
			const T_REG_INFO_EX& cs_ctrl_code_max_initamp();	//CSR26[4:0]

	/// Define minimum calibration control code for band selection calibration.
			const T_REG_INFO_EX& cs_ctrl_code_min_bdsel();	//CSR27[14:10]

	/// Define minimum calibration control code for frequency calibration.
			const T_REG_INFO_EX& cs_ctrl_code_min_freqcal();	//CSR27[5:0]

	/// Define maximum calibration control code for maximum amplitude calibration.
			const T_REG_INFO_EX& cs_ctrl_code_max_maxamp();	//CSR28[14:10]

	/// Define minimum calibration control code for maximum amplitude calibration.
			const T_REG_INFO_EX& cs_ctrl_code_min_maxamp();	//CSR28[9:5]

	/// Define maximum calibration control code for band selection calibration.
			const T_REG_INFO_EX& cs_ctrl_code_max_bdsel();	//CSR28[4:0]

	/// Define maximum calibration control code for lock of check calibration.
			const T_REG_INFO_EX& cs_ctrl_code_max_lckchk();	//CSR29[9:5]

	/// Define minimum calibration control codefor lock of check calibration.
			const T_REG_INFO_EX& cs_ctrl_code_min_lckchk();	//CSR29[4:0]

	/// Define initial calibration control code for initial amplitude calibration.
			const T_REG_INFO_EX& cs_init_code_amp();	//CSR30[11:7]

	/// Define initial calibration control code for offset calibration.
			const T_REG_INFO_EX& cs_init_code_offset();	//CSR30[6:2]

	/// Define initial calibration control code for band selection calibration.
			const T_REG_INFO_EX& cs_init_code_bdsel();	//CSR30[1:0]

	/// Define initial calibration control code for maximum amplitude calibration. Not available in current design.
			const T_REG_INFO_EX& cs_init_code_maxamp();	//CSR31[15:11]

	/// Define initial calibration control code for  frequency calibration.
			const T_REG_INFO_EX& cs_init_code_freqcal();	//CSR31[10:5]

	/// Define initial calibration control code for minimum amplitude calibration.
			const T_REG_INFO_EX& cs_init_code_minamp();	//CSR31[4:0]

	/// Define maximum calibration control code for frequency calibration.
			const T_REG_INFO_EX& cs_ctrl_code_max_freqcal();	//CSR32[10:5]

	/// Define initial calibration control code for lock of check calibration.
			const T_REG_INFO_EX& cs_init_code_lckchk();	//CSR32[4:0]

	/// Configure the maximum transitions for frequency calibration.
			const T_REG_INFO_EX& cs_trans_max_freqcal();	//CSR33[15:12]

	/// Configure the maximum transitions for minimum amplitude calibration.
			const T_REG_INFO_EX& cs_trans_max_minamp();	//CSR33[11:8]

	/// Configure the maximum transitions for initial amplitude calibration.
			const T_REG_INFO_EX& cs_trans_max_initamp();	//CSR33[7:4]

	/// Configure the maximum transitions for offset calibration.
			const T_REG_INFO_EX& cs_trans_max_offset();	//CSR33[3:0]

	/// Configure the maximum transitions for lock of check calibration.
			const T_REG_INFO_EX& cs_trans_max_lckchk();	//CSR34[11:8]

	/// Configure the maximum transitions for maximum amplitude calibration.
			const T_REG_INFO_EX& cs_trans_max_maxamp();	//CSR34[7:4]

	/// Configure the maximum transitions for band selection calibration.
			const T_REG_INFO_EX& cs_trans_max_bdsel();	//CSR34[3:0]

	/// Define the threshold of frequency detector. If abs[number of refclk cycle - number of fbclk cycle less than threshold, it would indicate that PLL is locked.
			const T_REG_INFO_EX& cs_fd_threshold();	//CSR35[10:1]

	/// When loss of lock detecting, it could enable timer for waiting specified time.
	/// 0 = disable
	/// 1 = enable
			const T_REG_INFO_EX& cs_meas_fd_wait();	//CSR35[0:0]

	/// Define the decrease value of reference clock counter.
			const T_REG_INFO_EX& cs_fd_ref_cnt_dv();	//CSR36[13:12]

	/// The initial value of reference clock counter.
			const T_REG_INFO_EX& cs_fd_ref_cnt_lv();	//CSR36[11:0]

	/// Define the decrease value of feedback clock counter.
			const T_REG_INFO_EX& cs_fd_fb_cnt_dv();	//CSR37[13:12]

	/// The initial value of feedback clock counter.
			const T_REG_INFO_EX& cs_fd_fb_cnt_lv();	//CSR37[11:0]

	/// Configuration of timer for waiting, which is the cycles of reference clock.
			const T_REG_INFO_EX& cs_timer_value();	//CSR38[14:5]

	/// Configuration of divider in timer.
			const T_REG_INFO_EX& cs_timer_div_value();	//CSR38[4:2]

	/// Enable the divider in timer. Not available in current design.
	/// 0 = disable
	/// 1 = enable
			const T_REG_INFO_EX& cs_timer_div_en();	//CSR38[1:1]

	/// Stop timer, for debugging.
	/// 0 = normal
	/// 1 = stop the timer
			const T_REG_INFO_EX& cs_timer_stop();	//CSR38[0:0]

	/// The divider of feedback clock for loss of lock detector.
			const T_REG_INFO_EX& cs_lld_fb_div_ratio();	//CSR39[3:1]

	/// The LLD operation manner:
	/// 0 = operate always.
	/// 1 = Perform loss of lock one time then halt.
			const T_REG_INFO_EX& cs_lld_once();	//CSR39[0:0]

	/// The decrease value of reference clock counter.
			const T_REG_INFO_EX& cs_lld_ref_cnt_dv();	//CSR40[14:12]

	/// The initial value of reference clock counter.
			const T_REG_INFO_EX& cs_lld_ref_cnt_lv();	//CSR40[11:0]

	/// The decrease value of feedback clock counter.
			const T_REG_INFO_EX& cs_lld_fb_cnt_dv();	//CSR41[14:12]

	/// The initial value of feedback clock counter.
			const T_REG_INFO_EX& cs_lld_fb_cnt_lv();	//CSR41[11:0]

	/// The divider of feedback clock of loss of clock.
			const T_REG_INFO_EX& cs_lcd_fb_div_ratio();	//CSR42[9:1]

	/// Override the status of loss of clock.
	/// 0 = normal
	/// 1 = override
			const T_REG_INFO_EX& cs_lcd_override();	//CSR42[0:0]

	/// SSC Generator freeze mode enable, active high
			const T_REG_INFO_EX& ssc_freeze();	//CSR43[13:13]

	/// SSC Generator freeze mode select
	/// 0 = Freeze in current PPM
	/// 1 = Freeze to 0 PPM
			const T_REG_INFO_EX& ssc_freeze_mode();	//CSR43[12:12]

	/// SSC freeze mode enable source select
			const T_REG_INFO_EX& ssc_freeze_en_sel();	//CSR43[11:11]

	/// The initial value of feedback clock counter. Not used incurrent design.
	/// Used CS_LCD_FB_CNT_LV[0] as cs_lcd_clksel configure. and the signal indicated clockslice lcd refclk and fdclk select signal
	/// 0 = refclk is  refclk2dig and fdclk is as pll0_divclk2dig
	/// 1 = refclk is pll0_divclk2dig and fdclk is as refclk2dig
	/// the default value of CS_LCD_FB_CNT_LV[0] is 1
			const T_REG_INFO_EX& cs_lcd_fb_cnt_lv();	//CSR43[10:0]

	/// cp_dlf_resfdbkpwrd,DLF Feedback resistor powerdown control.
	/// 2'b00: 100K Resistor ON 
	/// 2'b01:  200K Resistor ON
	/// 2'b10:  200K Resistor ON.
	/// 2'b11: 200K Resistor OFF.
			const T_REG_INFO_EX& cp_dlf_resfdbkpwrdb();	//CSR44[15:14]

	/// Prop CP Switch capacitor S/H clock edge control bit
	/// 0: 1.4pF
	/// 1: 4.2pF
			const T_REG_INFO_EX& cp_dlf_sample_edge_switch();	//CSR44[13:13]

	/// cp_dlf common mode feedback mode switch control
	/// 0: Default mode
	/// 1: Revised mode
			const T_REG_INFO_EX& cp_dlf_cmfb_switch();	//CSR44[12:12]

	/// set the current for refclk1 cml driver in the CS
	/// 2'b00 :  I
	/// 2'b01:   I*1.16
	/// 2'b10:   I*1.33
	/// 2'b11:  I*1.48
			const T_REG_INFO_EX& refclk1_cml_bias_ctrl();	//CSR44[11:10]

	/// set the current for refclk1 cml driver in the CS
	/// 2'b00 :  I
	/// 2'b01:   I*1.16
	/// 2'b10:   I*1.33
	/// 2'b11:  I*1.48
			const T_REG_INFO_EX& refclk0_cml_bias_ctrl();	//CSR44[9:8]

	/// Prop CP Replica Opamp compensation control bit.
	/// 0: Default status
	/// 1: Revised status
			const T_REG_INFO_EX& cp_op_compensation_switch();	//CSR44[5:5]

	/// Set capacitor of DLF(pF):
	/// 00000: 0.342pF
	/// 00001: 0.684pF
	/// 00010: 1.026pF
	/// 00011: 1.368pF
	/// 00100: 1.71pF
	/// 00101: 2.052pF
	/// 00110: 2.394pF
	/// 00111: 2.736pF
	/// 01000: 3.078pF
	/// 01001: 3.42pF
	/// 01010: 3.762pF
	/// 01011: 4.104pF
	/// 01100: 4.446pF
	/// 01101: 4.788pF
	/// 01110: 5.13pF
	/// 01111: 5.472pF
	/// 10000: 5.814pF
	/// 10001: 6.156pF
	/// 10010: 6.498pF
	/// 10011: 6.84pF
	/// 10100: 7.182pF
	/// 10101: 7.524pF
	/// 10110: 7.866pF
	/// 10111: 8.208pF
	/// 11000: 8.55pF
	/// 11001: 8.892pF
	/// 11010: 9.234pF 
	/// 11011: 9.576pF
	/// 11100: 9.918pF
	/// 11101: 10.26pF
	/// 11110: 10.602pF
	/// 11111: 10.944pF
			const T_REG_INFO_EX& cpcintsel();	//CSR44[4:0]

	/// set the current for refclk1 cml distributor in the SS.
	/// 2'b00 :  I
	/// 2'b01:   I*1.16
	/// 2'b10:   I*1.33
	/// 2'b11:  I*1.48
			const T_REG_INFO_EX& ssrefclk1_distbiasctrl();	//CSR45[15:14]

	/// set the current for refclk0 cml distributor in the SS.
	/// 2'b00 :  I
	/// 2'b01:   I*1.16
	/// 2'b10:   I*1.33
	/// 2'b11:  I*1.48
			const T_REG_INFO_EX& ssrefclk0_distbiasctrl();	//CSR45[13:12]

	/// Set the current for refclk1 cml receiver in the SS.
	/// 2'b00 :  I
	/// 2'b01:   I*1.16
	/// 2'b10:   I*1.33
	/// 2'b11:  I*1.48
			const T_REG_INFO_EX& ssrefclk1_rcvbiasctrl();	//CSR45[11:10]

	/// Set the current for refclk1 cml receiver in the SS.
	/// 2'b00 :  I
	/// 2'b01:   I*1.16
	/// 2'b10:   I*1.33
	/// 2'b11:  I*1.48
			const T_REG_INFO_EX& ssrefclk0_rcvbiasctrl();	//CSR45[9:8]

	/// SS master/slave mode switch.
	/// 0: Master mode.
	/// 1: Slaver mode
			const T_REG_INFO_EX& ss_slavemode();	//CSR45[7:7]

	/// Spare register for clockslice digital used
			const T_REG_INFO_EX& cs_spare();	//CSR45[6:0]

	/// For debugging purpose.
	/// [15]: Compare status inversion control. 0=normal; 1=inverse.
	/// [14:13]: Frequency calibration freqcal+/-1 control when freqcal changed.
	/// [12]: Band selection calibration band+/-1 control.
	/// [11]: Band selection calibration de-bouncing control.
	/// [10]: Search method for frequency calibration.
	/// [9:7]: Maximum peak level.
	/// [6:4]: Minimum peak level.
	/// [3:2]: Control which transition counter will output , for debugging.
	/// [1]: Unused for present version, don't configure.
	/// [0]: Fix the FD status 0 for frequency calibration.
			const T_REG_INFO_EX& cs_debugging_ctrl1();	//CSR46[15:0]

	/// choose startup voltage level
			const T_REG_INFO_EX& bg_stu_ref_sel();	//CSR47[14:13]

	/// choose icv current mirror bias from local icv generation or bandgap core
			const T_REG_INFO_EX& bg_icv_ref_sel();	//CSR47[12:12]

	/// The reference clock counter of loss of lock detector.
			const T_REG_INFO_EX& cs_lld_ref_freq();	//CSR47[11:0]

	/// temperature compensation ability adjusting register
	/// the bigger the register is, the stronger the compensation ability is
			const T_REG_INFO_EX& tempcompensel();	//CSR48[15:14]

	/// temperature compensation current adjusting register
	/// current = 6.25uA + 12.5uA*lcvco_tempcompensel_current[1:0]
			const T_REG_INFO_EX& tempcompensel_current();	//CSR48[13:12]

	/// The reference clock counter of frequency detector.
			const T_REG_INFO_EX& cs_fd_ref_freq();	//CSR48[11:0]

	/// vtune shift adjusting register, adjust the value of vdiv_0p8 and vidv_0p2
	/// 0000: vdiv_0p8 = 0.9V      /   vdiv_0p2 = 0.06V
	/// 0001: vdiv_0p8 = 0.78V    /   vdiv_0p2 = 0.06V
	/// 0010: vdiv_0p8 = 0.66V    /   vdiv_0p2 = 0.06V
	/// 0011: vdiv_0p8 = vtunem  /   vdiv_0p2 = 0.06V
	/// 0100: vdiv_0p8 = 0.9V      /   vdiv_0p2 = 0.18V
	/// 0101: vdiv_0p8 = 0.78V    /   vdiv_0p2 = 0.18V
	/// 0110: vdiv_0p8 = 0.66V    /   vdiv_0p2 = 0.18V
	/// 0111: vdiv_0p8 = vtunem  /   vdiv_0p2 = 0.18V
	/// 1000: vdiv_0p8 = 0.9V      /   vdiv_0p2 = 0.3V
	/// 1001: vdiv_0p8 = 0.78V    /   vdiv_0p2 = 0.3V
	/// 1010: vdiv_0p8 = 0.66V    /   vdiv_0p2 = 0.3V
	/// 1011: vdiv_0p8 = vtunem  /   vdiv_0p2 = 0.3V
	/// 1100: vdiv_0p8 = 0.8V      /   vdiv_0p2 = vtunep
	/// 1101: vdiv_0p8 = 0.78V    /   vdiv_0p2 = vtunep
	/// 1110: vdiv_0p8 = 0.66V    /   vdiv_0p2 = vtunep
	/// 1111: vdiv_0p8 = vtunem  /   vdiv_0p2 = vtunep
			const T_REG_INFO_EX& vtuneshift_sel();	//CSR49[15:12]

	/// The feedback clock counter of frequency detector.
			const T_REG_INFO_EX& cs_fd_fb_freq();	//CSR49[11:0]

	/// The difference of reference clock counter and feedback clock counter for frequency detector.
			const T_REG_INFO_EX& cs_fd_diff_freq();	//CSR50[12:0]

	/// The status of loss of lock.
	/// 0 = incomplete
	/// 1 = complete
			const T_REG_INFO_EX& cs_lld_done();	//CSR51[15:15]

	/// The difference of reference clock counter and feedback clock counter for loss of lock detector.
			const T_REG_INFO_EX& cs_lld_diff_freq();	//CSR51[12:0]

	/// The feedback clock counter of loss of lock detector.
			const T_REG_INFO_EX& cs_lld_fb_freq();	//CSR52[11:0]

	/// Debugging for purpose. Following internal signals could be read back.
	/// [15]=cs_lcd_done
	/// [14]=cs_pwrdb
	/// [13]=cs_calrstb and the default value is 1.
	/// [12:10]=cs_peak_level and the default value is 100.
	/// [9]=cs_offset_cal
	/// [8:3]=cs_offset and the default value is 0x20.
	/// [2:0]=cs_calib_mode
			const T_REG_INFO_EX& cs_misc_status();	//CSR53[15:0]

	/// the status of calibration FSM for debugging purpose. Following internal signals could be read back.
	/// [15]=1'b0
	/// [14:9]=cs_freqcal and the default value is 0x6.
	/// [8:3]=cs_itank and the default value is 0xc.
	/// [2]=fd_status
	/// [1]=cs_trans_warning
	/// [0]=cs_calib_state_err
			const T_REG_INFO_EX& cs_calib_fsm_status();	//CSR54[15:0]

	/// The status of general purpose calibration FSM, for debugging.  Following internal signals could be read back.
	/// [15]=1'b0
	/// [14:12]=cs_bdsel and the default value is 0x1.
	/// [11:6]=cs_gcalib_state_flag
	/// [5:2]=cs_trans_cnt
	/// [1]=cs_gcalib_trans_status and the default value is 0x1.
	/// [0]=cs_gcalib_err
			const T_REG_INFO_EX& cs_gcalib_fsm_status();	//CSR55[15:0]

	/// SSC modulation type:
	/// 00: down-spreading
	/// ;01: center-spreading
	/// ;10: fixed ppm, codeword = sscamp; 
	/// 11: fixed ppm, codeword = -sscamp;
			const T_REG_INFO_EX& ssctype();	//CSR56[15:14]

	/// Set the SSC modulation period (frequency), by setting the number of reference clock cycles to have one staircase step. Its value can be calculated as follows,
	/// sscfreq= (reference_clock_freq)/(2*M*(sscamp+1)*ssc_modulation_freq)ㄛbut SSCFREQ > 9'd0.
			const T_REG_INFO_EX& sscfreq();	//CSR56[8:0]

	/// These control bits are just used in SSC mode.
	/// Programs the feedback clock pulse width by 2*Ka*Tvco*ㄗssc_pulsewidth[1:0] +2ㄘ
			const T_REG_INFO_EX& ssc_pulsewidth();	//CSR57[13:12]

	/// CS mode select,
	/// 0: normal mode
	/// 1: SSC mode
			const T_REG_INFO_EX& ssc_bypassb();	//CSR57[7:7]

	/// This configuration variable defines the peak-to-peak SSC modulation frequency deviation, by defining the total number of staircases in half period of SSC.
	/// Its value can be calculated as follows, 
	/// ssctype = 00:
	/// sscamp=floor((ssc_p2p_ppm)/□10■^6 *N/2*32*2^(truncation_bits) )
	/// ssctype = 01:
	///  sscamp=2*floor((ssc_p2p_ppm)/2/□10■^6 *N/2*32*2^(truncation_bits) )
			const T_REG_INFO_EX& sscamp();	//CSR57[6:0]

	/// Clear SSC generator start and internal counter, high active.
	/// 0: Not clear.
	/// 1: Clear
			const T_REG_INFO_EX& ssc_gen_clr();	//CSR58[15:15]

	/// Soft reset for Digital SSC generator logic , low active.
			const T_REG_INFO_EX& ssc_gen_soft_rstb();	//CSR58[14:14]

	/// SSC generator start mode.
	/// 0: Auto mode, start SSC generator by  logic calibration done signal.
	/// 1: Manual mode, start SSC generator by configure register 
	///    SSC_GEN_MANUL_START via software
			const T_REG_INFO_EX& ssc_gen_start_mode();	//CSR58[13:13]

	/// intergral chargepump current step control, 
	///  0 = 20uA per step.
	///  1 = 5uA per step.
			const T_REG_INFO_EX& cp_i_intchp_tune();	//CSR58[12:12]

	/// PLL wordclk2dig_32b powerdown, active low.
	/// 0: Power down
	/// 1: Power up
			const T_REG_INFO_EX& pwrdb_pll0_wordclk2dig_32b();	//CSR58[11:11]

	/// LCVCO Temp compensation circuit power down, active low
	/// 0: Power down
	/// 1: Power up
			const T_REG_INFO_EX& lcvco_tempcompensate_pwrdb();	//CSR58[10:10]

	/// These control bit is just used in SSC mode, and decide the clock domain of the digital blocks of SSC Gen.
	/// 0: worked at fbclk2dig domain
	/// 1: worked at refclk2dig domain
			const T_REG_INFO_EX& ssc_clksel();	//CSR58[9:9]

	/// Start SSC generator by manual mode, high active.
	/// 0:  Start disable
	/// 1: Start enbale
			const T_REG_INFO_EX& ssc_gen_manual_start();	//CSR58[8:8]

	/// SSC PI phase setting in manual mode. 
	/// MSB=1 indicates SSC PI is in manual mode. And the 5 LSB bits are the desired SSC PI phase value (binary coded).
	/// MSB=0 indicates SSC PI is auto mode, and is controlled by the internal logic.
			const T_REG_INFO_EX& ssc_phswrite();	//CSR58[5:0]

	/// Read the SSC PI code value in auto mode for debug.
			const T_REG_INFO_EX& ssc_picode();	//CSR59[4:0]

	/// Start to read SSC_PICODE, Clear the start after read by logic(RWW type)
	/// Note: The step read the SSC_PICODE register:
	/// (1) Configure  SSC_PICODE_READ_START = 1'b1
	/// ;(2) Logic clear the SSC_PICODE_READ_START, softeware must wait until SSC_PICODE_READ_START=0
	/// (3)Read Register SSC_PICODE after de-asert SSC_PICODE_READ_START
			const T_REG_INFO_EX& ssc_picode_read_start();	//CSR60[15:15]

	/// Truncation bits of SSC accumulation
	/// 000: 2bits
	/// 001: 3bits
	/// 010: 4bits
	/// 011: 5bits.
	/// 100: 6bits.
	/// Others: reserved
			const T_REG_INFO_EX& sscatt();	//CSR60[14:12]

	/// Spare registers for SSC control
			const T_REG_INFO_EX& ssc_spare();	//CSR60[11:10]

	/// Feedbk divider output clock pulsewidth modulation
	///  0: pulsewidth equal 2 period of Ka clock  
	///  1: pulsewidth equal 3 period of Ka clock
			const T_REG_INFO_EX& fbkclk_pulsewidth_mod();	//CSR60[9:9]

	/// SSC block power down control
	///  0: power off   1: power on
	///  Note: should be set to 1 on SSC mode or mode dynamic change between SSC and default
			const T_REG_INFO_EX& ssc_pwrdb();	//CSR60[8:8]

	/// SSC PI picode MSB signal delay control register,
	/// ssc_picode_delay[1:0] = 00/01/10/11
			const T_REG_INFO_EX& ssc_picode_delay();	//CSR60[7:6]

	/// SSC PI output buffer capacitance adjusting register,
	/// piout_caps[1:0] = 00/01/10/11
			const T_REG_INFO_EX& piout_caps();	//CSR60[5:4]

	/// SSC PI pi input driver current adjusting register,
	/// pidrvin_cur[1:0] = 00/01/10/11
			const T_REG_INFO_EX& pidrvin_cur();	//CSR60[3:2]

	/// SSC PI input driver capacitance adjusting register
	/// pidrvin_caps[1:0]= 00/01/10/11
			const T_REG_INFO_EX& pidrvin_caps();	//CSR60[1:0]

	/// Word clock divider by 2 ( 'W'divider).
	/// 0 = divided by 1 (default)
	/// 1 = divided by 2
			const T_REG_INFO_EX& wordclkdiv2();	//CSR61[15:15]

	/// Word clock divider ratio ( 'J'divider).
	/// 00 = divided by 20
	/// 01 = divided by 10(default)
	/// 10 = divided by 16
	/// 11 = divided by 8
			const T_REG_INFO_EX& wordclkdiv();	//CSR61[14:13]

	/// Set divide ratio of wordclkdiv2_16b32b post divider.('V' divider)
	/// 0 = divided by 1 (default)
	/// 1 = divided by 2
			const T_REG_INFO_EX& wordclkdiv2_16b32b();	//CSR61[12:12]

	/// Sample Tsensor temperature numbers:
	/// 00 = 16
	/// 01 = 32
	/// 10 = 64
	/// 11 = 128
			const T_REG_INFO_EX& meas_num();	//CSR62[15:14]

	/// clock divide parameter to get 1MHz for Tsensor
			const T_REG_INFO_EX& temp_clk_div();	//CSR62[13:5]

	/// Enable Tsensor measuring tempertature
			const T_REG_INFO_EX& tsen_temp_en();	//CSR62[4:4]

	/// Tsensor converting timing select:
	/// 00 = 0.512ms
	/// 01 = 0.256ms
	/// 10 = 1.024ms
	/// 11 =2.048ms
			const T_REG_INFO_EX& tsen_temp_ct_sel();	//CSR62[3:2]

	/// Tsensor Ouput chip current temperature
			const T_REG_INFO_EX& chip_temp_out();	//CSR63[15:6]
			bool get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos);
	};
public:
	_REG_INFO REG_INFO;

	uint csr[CS_CLK_CSR_NUM];


	//CSR0[15:15]
	CS_clkRegs& setcspwrdb(uint val);
	uint getcspwrdb();

	//CSR0[14:14]
	CS_clkRegs& setssrefclk0div2sel(uint val);
	uint getssrefclk0div2sel();

	//CSR0[13:13]
	CS_clkRegs& setssrefclk1div2sel(uint val);
	uint getssrefclk1div2sel();

	//CSR0[12:12]
	CS_clkRegs& setsscmosrefclksel(uint val);
	uint getsscmosrefclksel();

	//CSR0[11:11]
	CS_clkRegs& setrefclksel(uint val);
	uint getrefclksel();

	//CSR0[10:10]
	CS_clkRegs& setlifeclksel(uint val);
	uint getlifeclksel();

	//CSR0[9:9]
	CS_clkRegs& setcoreclksel(uint val);
	uint getcoreclksel();

	//CSR0[7:4]
	CS_clkRegs& setlpfcap(uint val);
	uint getlpfcap();

	//CSR0[3:0]
	CS_clkRegs& setlpfres(uint val);
	uint getlpfres();

	//CSR1[15:14]
	CS_clkRegs& setcmldiv(uint val);
	uint getcmldiv();

	//CSR1[13:8]
	CS_clkRegs& setfbdivp(uint val);
	uint getfbdivp();

	//CSR1[7:2]
	CS_clkRegs& setfbdivs(uint val);
	uint getfbdivs();

	//CSR1[1:0]
	CS_clkRegs& setrefclkdiv(uint val);
	uint getrefclkdiv();

	//CSR2[15:14]
	CS_clkRegs& setlifeclk2digdiv(uint val);
	uint getlifeclk2digdiv();

	//CSR2[13:12]
	CS_clkRegs& setwordclk2digdiv(uint val);
	uint getwordclk2digdiv();

	//CSR2[10:6]
	CS_clkRegs& setlcvcololthr(uint val);
	uint getlcvcololthr();

	//CSR2[5:3]
	CS_clkRegs& setlcvcolocthr(uint val);
	uint getlcvcolocthr();

	//CSR2[2:2]
	CS_clkRegs& setlcvcololmode(uint val);
	uint getlcvcololmode();

	//CSR2[1:1]
	uint getlcvcooutoflock();

	//CSR2[0:0]
	uint getlossoflcvcoclk();

	//CSR3[15:15]
	CS_clkRegs& setpllpwrdb(uint val);
	uint getpllpwrdb();

	//CSR3[14:14]
	CS_clkRegs& setpfdupdnswap(uint val);
	uint getpfdupdnswap();

	//CSR3[13:13]
	CS_clkRegs& setpfdforceup(uint val);
	uint getpfdforceup();

	//CSR3[12:12]
	CS_clkRegs& setpfdforcedn(uint val);
	uint getpfdforcedn();

	//CSR3[11:10]
	CS_clkRegs& setpfdpulsewidth(uint val);
	uint getpfdpulsewidth();

	//CSR3[9:8]
	CS_clkRegs& setcpauxres(uint val);
	uint getcpauxres();

	//CSR3[7:7]
	CS_clkRegs& setcpcmfbpwrdb(uint val);
	uint getcpcmfbpwrdb();

	//CSR3[6:6]
	CS_clkRegs& setcpintegcppwrdb(uint val);
	uint getcpintegcppwrdb();

	//CSR3[5:4]
	CS_clkRegs& setcprdeg(uint val);
	uint getcprdeg();

	//CSR3[3:3]
	CS_clkRegs& setcpvrefpropsel(uint val);
	uint getcpvrefpropsel();

	//CSR3[2:0]
	CS_clkRegs& setcpreflvl(uint val);
	uint getcpreflvl();

	//CSR4[15:14]
	CS_clkRegs& setcmldivkbvcmsel(uint val);
	uint getcmldivkbvcmsel();

	//CSR4[13:13]
	CS_clkRegs& setcp_i_propchp_tune(uint val);
	uint getcp_i_propchp_tune();

	//CSR4[12:10]
	CS_clkRegs& setcpcurrentint(uint val);
	uint getcpcurrentint();

	//CSR4[9:4]
	CS_clkRegs& setcpcurrent(uint val);
	uint getcpcurrent();

	//CSR4[3:0]
	CS_clkRegs& setcprzerocmfb(uint val);
	uint getcprzerocmfb();

	//CSR5[15:15]
	CS_clkRegs& setcpdlfmuxsel(uint val);
	uint getcpdlfmuxsel();

	//CSR5[14:12]
	CS_clkRegs& setcpspare2to0(uint val);
	uint getcpspare2to0();

	//CSR5[11:11]
	CS_clkRegs& setdlfpwrdb(uint val);
	uint getdlfpwrdb();

	//CSR5[10:10]
	CS_clkRegs& setdlfextramimcap(uint val);
	uint getdlfextramimcap();

	//CSR5[9:9]
	CS_clkRegs& setdlftstpwrdb(uint val);
	uint getdlftstpwrdb();

	//CSR5[8:8]
	CS_clkRegs& setdlfcmfbpwrdb(uint val);
	uint getdlfcmfbpwrdb();

	//CSR5[7:7]
	CS_clkRegs& setdlfshdelsel(uint val);
	uint getdlfshdelsel();

	//CSR5[6:2]
	CS_clkRegs& setdlfseldtb(uint val);
	uint getdlfseldtb();

	//CSR5[1:0]
	CS_clkRegs& setdlfshcapsel(uint val);
	uint getdlfshcapsel();

	//CSR6[15:14]
	CS_clkRegs& setcmlbufoutbiassel(uint val);
	uint getcmlbufoutbiassel();

	//CSR6[13:8]
	CS_clkRegs& setcmldivbiascal(uint val);
	uint getcmldivbiascal();

	//CSR6[7:4]
	CS_clkRegs& setlcvcospare(uint val);
	uint getlcvcospare();

	//CSR6[2:0]
	CS_clkRegs& setlcvcoselpeaklvl(uint val);
	uint getlcvcoselpeaklvl();

	//CSR7[15:15]
	CS_clkRegs& setlcvco_pwron_force_en(uint val);
	uint getlcvco_pwron_force_en();

	//CSR7[14:12]
	CS_clkRegs& setlcvcobandsel(uint val);
	uint getlcvcobandsel();

	//CSR7[10:5]
	CS_clkRegs& setlcvcofreqcal(uint val);
	uint getlcvcofreqcal();

	//CSR7[4:0]
	CS_clkRegs& setlcvcoitank(uint val);
	uint getlcvcoitank();

	//CSR8[14:14]
	CS_clkRegs& sethsclkfrclkspinepwrdb(uint val);
	uint gethsclkfrclkspinepwrdb();

	//CSR8[13:13]
	CS_clkRegs& sethsclkfromsspwrdb(uint val);
	uint gethsclkfromsspwrdb();

	//CSR8[12:12]
	CS_clkRegs& sethsclktosspwrdb(uint val);
	uint gethsclktosspwrdb();

	//CSR8[11:10]
	CS_clkRegs& sethsclkfromcsbiasctrl(uint val);
	uint gethsclkfromcsbiasctrl();

	//CSR8[9:8]
	CS_clkRegs& sethsclkfromssbiasctrl(uint val);
	uint gethsclkfromssbiasctrl();

	//CSR8[7:6]
	CS_clkRegs& sethsclktossbiasctrl(uint val);
	uint gethsclktossbiasctrl();

	//CSR8[5:3]
	CS_clkRegs& sethsclkreploadctrl(uint val);
	uint gethsclkreploadctrl();

	//CSR8[2:0]
	CS_clkRegs& sethsclkreprefsel(uint val);
	uint gethsclkreprefsel();

	//CSR9[14:12]
	CS_clkRegs& sethsclkspare(uint val);
	uint gethsclkspare();

	//CSR9[8:8]
	CS_clkRegs& setbiascmupwrdb(uint val);
	uint getbiascmupwrdb();

	//CSR9[7:0]
	CS_clkRegs& setbiascvcal(uint val);
	uint getbiascvcal();

	//CSR10[15:15]
	CS_clkRegs& setcsrxbiasbackupgen(uint val);
	uint getcsrxbiasbackupgen();

	//CSR10[14:0]
	CS_clkRegs& setcsspare(uint val);
	uint getcsspare();

	//CSR11[15:15]
	CS_clkRegs& setvregpwrdb(uint val);
	uint getvregpwrdb();

	//CSR11[12:12]
	CS_clkRegs& setvregcapsel(uint val);
	uint getvregcapsel();

	//CSR11[11:8]
	CS_clkRegs& setvregselfbleed(uint val);
	uint getvregselfbleed();

	//CSR11[7:0]
	CS_clkRegs& setvregplllvl(uint val);
	uint getvregplllvl();

	//CSR12[15:15]
	CS_clkRegs& setcalpwrdb(uint val);
	uint getcalpwrdb();

	//CSR12[14:14]
	CS_clkRegs& setcalrstb(uint val);
	uint getcalrstb();

	//CSR12[8:8]
	CS_clkRegs& setcs_post_lckchk_bypass(uint val);
	uint getcs_post_lckchk_bypass();

	//CSR12[7:7]
	CS_clkRegs& setcs_initamp_calib_bypass(uint val);
	uint getcs_initamp_calib_bypass();

	//CSR12[6:6]
	CS_clkRegs& setcslowoffcal(uint val);
	uint getcslowoffcal();

	//CSR12[5:0]
	CS_clkRegs& setcslowoffsetctrl(uint val);
	uint getcslowoffsetctrl();

	//CSR13[15:15]
	CS_clkRegs& setlcvcocalmode(uint val);
	uint getlcvcocalmode();

	//CSR13[13:10]
	CS_clkRegs& setlcvcocalctrl(uint val);
	uint getlcvcocalctrl();

	//CSR13[9:9]
	uint getptatcalout();

	//CSR13[8:8]
	uint getcvcalout();

	//CSR13[7:6]
	uint getcomparestatus();

	//CSR13[5:5]
	uint getdtbout();

	//CSR13[4:4]
	uint getlcvcocaldone();

	//CSR13[3:3]
	uint getlcvcocalerr();

	//CSR13[2:0]
	uint getlcvcocalstatus();

	//CSR14[15:12]
	CS_clkRegs& setcsdtbsel(uint val);
	uint getcsdtbsel();

	//CSR14[11:3]
	CS_clkRegs& setvregatbctrl(uint val);
	uint getvregatbctrl();

	//CSR14[2:0]
	CS_clkRegs& setcsatbfinalsel(uint val);
	uint getcsatbfinalsel();

	//CSR15[15:8]
	CS_clkRegs& setcsatbsel23to16(uint val);
	uint getcsatbsel23to16();

	//CSR15[7:0]
	CS_clkRegs& setssspare(uint val);
	uint getssspare();

	//CSR16[15:15]
	CS_clkRegs& setsspwrdb(uint val);
	uint getsspwrdb();

	//CSR16[14:14]
	CS_clkRegs& setssrefclk0pwrdb(uint val);
	uint getssrefclk0pwrdb();

	//CSR16[13:13]
	CS_clkRegs& setssrefclk1pwrdb(uint val);
	uint getssrefclk1pwrdb();

	//CSR16[9:9]
	CS_clkRegs& setsshsclkss2cspwrdb(uint val);
	uint getsshsclkss2cspwrdb();

	//CSR16[8:8]
	CS_clkRegs& setsshsclkcs2sspwrdb(uint val);
	uint getsshsclkcs2sspwrdb();

	//CSR16[7:7]
	CS_clkRegs& setssrefclk0cmldivpwrdb(uint val);
	uint getssrefclk0cmldivpwrdb();

	//CSR16[5:4]
	CS_clkRegs& setssrefclk0atten(uint val);
	uint getssrefclk0atten();

	//CSR16[3:3]
	CS_clkRegs& setssrefclk1cmldivpwrdb(uint val);
	uint getssrefclk1cmldivpwrdb();

	//CSR16[1:0]
	CS_clkRegs& setssrefclk1atten(uint val);
	uint getssrefclk1atten();

	//CSR17[15:15]
	CS_clkRegs& setbg600mvlvccresdiv(uint val);
	uint getbg600mvlvccresdiv();

	//CSR17[14:14]
	CS_clkRegs& setbgccen(uint val);
	uint getbgccen();

	//CSR17[13:13]
	CS_clkRegs& setbgcven(uint val);
	uint getbgcven();

	//CSR17[12:12]
	CS_clkRegs& setbgpaten(uint val);
	uint getbgpaten();

	//CSR17[11:10]
	CS_clkRegs& setbgforcestart(uint val);
	uint getbgforcestart();

	//CSR17[9:8]
	CS_clkRegs& setbgstartbypass(uint val);
	uint getbgstartbypass();

	//CSR17[7:0]
	CS_clkRegs& setbgbypass(uint val);
	uint getbgbypass();

	//CSR18[15:15]
	CS_clkRegs& sethvvbgccin(uint val);
	uint gethvvbgccin();

	//CSR18[14:12]
	CS_clkRegs& setvbgreflvl(uint val);
	uint getvbgreflvl();

	//CSR18[11:11]
	CS_clkRegs& sethvvbgptatin(uint val);
	uint gethvvbgptatin();

	//CSR18[10:8]
	CS_clkRegs& setvbgptatlvl(uint val);
	uint getvbgptatlvl();

	//CSR18[7:0]
	CS_clkRegs& setbiasselptatmix(uint val);
	uint getbiasselptatmix();

	//CSR19[15:0]
	CS_clkRegs& setssatbsel(uint val);
	uint getssatbsel();

	//CSR20[13:13]
	CS_clkRegs& setcs_lld_clr(uint val);
	uint getcs_lld_clr();

	//CSR20[12:12]
	CS_clkRegs& setcs_fd_clr(uint val);
	uint getcs_fd_clr();

	//CSR20[11:11]
	CS_clkRegs& setcs_calib_clr(uint val);
	uint getcs_calib_clr();

	//CSR20[10:10]
	CS_clkRegs& setcs_lcd_start(uint val);
	uint getcs_lcd_start();

	//CSR20[9:9]
	CS_clkRegs& setcs_lld_start(uint val);
	uint getcs_lld_start();

	//CSR20[8:8]
	CS_clkRegs& setcs_calib_start(uint val);
	uint getcs_calib_start();

	//CSR20[7:7]
	CS_clkRegs& setcs_lcd_enable(uint val);
	uint getcs_lcd_enable();

	//CSR20[6:6]
	CS_clkRegs& setcs_lld_enable(uint val);
	uint getcs_lld_enable();

	//CSR20[5:5]
	CS_clkRegs& setcs_calib_enable(uint val);
	uint getcs_calib_enable();

	//CSR20[4:4]
	CS_clkRegs& setcs_lcd_soft_rst_n(uint val);
	uint getcs_lcd_soft_rst_n();

	//CSR20[3:3]
	CS_clkRegs& setcs_lld_soft_rst_n(uint val);
	uint getcs_lld_soft_rst_n();

	//CSR20[2:2]
	CS_clkRegs& setcs_calib_soft_rst_n(uint val);
	uint getcs_calib_soft_rst_n();

	//CSR20[0:0]
	CS_clkRegs& setcs_glb_soft_rst_n(uint val);
	uint getcs_glb_soft_rst_n();

	//CSR21[15:0]
	CS_clkRegs& setcsatbsel15to0(uint val);
	uint getcsatbsel15to0();

	//CSR22[6:0]
	CS_clkRegs& setcs_direction_ctrl(uint val);
	uint getcs_direction_ctrl();

	//CSR23[14:12]
	CS_clkRegs& setcs_calib_mode_bdsel(uint val);
	uint getcs_calib_mode_bdsel();

	//CSR23[11:9]
	CS_clkRegs& setcs_calib_mode_freqcal(uint val);
	uint getcs_calib_mode_freqcal();

	//CSR23[8:6]
	CS_clkRegs& setcs_calib_mode_minamp(uint val);
	uint getcs_calib_mode_minamp();

	//CSR23[5:3]
	CS_clkRegs& setcs_calib_mode_initamp(uint val);
	uint getcs_calib_mode_initamp();

	//CSR23[2:0]
	CS_clkRegs& setcs_calib_mode_offset(uint val);
	uint getcs_calib_mode_offset();

	//CSR24[5:3]
	CS_clkRegs& setcs_calib_mode_lckchk(uint val);
	uint getcs_calib_mode_lckchk();

	//CSR24[2:0]
	CS_clkRegs& setcs_calib_mode_maxamp(uint val);
	uint getcs_calib_mode_maxamp();

	//CSR25[15:11]
	CS_clkRegs& setcs_ctrl_code_min_initamp(uint val);
	uint getcs_ctrl_code_min_initamp();

	//CSR25[10:5]
	CS_clkRegs& setcs_ctrl_code_max_offset(uint val);
	uint getcs_ctrl_code_max_offset();

	//CSR25[4:0]
	CS_clkRegs& setcs_ctrl_code_min_offset(uint val);
	uint getcs_ctrl_code_min_offset();

	//CSR26[14:10]
	CS_clkRegs& setcs_ctrl_code_max_minamp(uint val);
	uint getcs_ctrl_code_max_minamp();

	//CSR26[9:5]
	CS_clkRegs& setcs_ctrl_code_min_minamp(uint val);
	uint getcs_ctrl_code_min_minamp();

	//CSR26[4:0]
	CS_clkRegs& setcs_ctrl_code_max_initamp(uint val);
	uint getcs_ctrl_code_max_initamp();

	//CSR27[14:10]
	CS_clkRegs& setcs_ctrl_code_min_bdsel(uint val);
	uint getcs_ctrl_code_min_bdsel();

	//CSR27[5:0]
	CS_clkRegs& setcs_ctrl_code_min_freqcal(uint val);
	uint getcs_ctrl_code_min_freqcal();

	//CSR28[14:10]
	CS_clkRegs& setcs_ctrl_code_max_maxamp(uint val);
	uint getcs_ctrl_code_max_maxamp();

	//CSR28[9:5]
	CS_clkRegs& setcs_ctrl_code_min_maxamp(uint val);
	uint getcs_ctrl_code_min_maxamp();

	//CSR28[4:0]
	CS_clkRegs& setcs_ctrl_code_max_bdsel(uint val);
	uint getcs_ctrl_code_max_bdsel();

	//CSR29[9:5]
	CS_clkRegs& setcs_ctrl_code_max_lckchk(uint val);
	uint getcs_ctrl_code_max_lckchk();

	//CSR29[4:0]
	CS_clkRegs& setcs_ctrl_code_min_lckchk(uint val);
	uint getcs_ctrl_code_min_lckchk();

	//CSR30[11:7]
	CS_clkRegs& setcs_init_code_amp(uint val);
	uint getcs_init_code_amp();

	//CSR30[6:2]
	CS_clkRegs& setcs_init_code_offset(uint val);
	uint getcs_init_code_offset();

	//CSR30[1:0]
	CS_clkRegs& setcs_init_code_bdsel(uint val);
	uint getcs_init_code_bdsel();

	//CSR31[15:11]
	CS_clkRegs& setcs_init_code_maxamp(uint val);
	uint getcs_init_code_maxamp();

	//CSR31[10:5]
	CS_clkRegs& setcs_init_code_freqcal(uint val);
	uint getcs_init_code_freqcal();

	//CSR31[4:0]
	CS_clkRegs& setcs_init_code_minamp(uint val);
	uint getcs_init_code_minamp();

	//CSR32[10:5]
	CS_clkRegs& setcs_ctrl_code_max_freqcal(uint val);
	uint getcs_ctrl_code_max_freqcal();

	//CSR32[4:0]
	CS_clkRegs& setcs_init_code_lckchk(uint val);
	uint getcs_init_code_lckchk();

	//CSR33[15:12]
	CS_clkRegs& setcs_trans_max_freqcal(uint val);
	uint getcs_trans_max_freqcal();

	//CSR33[11:8]
	CS_clkRegs& setcs_trans_max_minamp(uint val);
	uint getcs_trans_max_minamp();

	//CSR33[7:4]
	CS_clkRegs& setcs_trans_max_initamp(uint val);
	uint getcs_trans_max_initamp();

	//CSR33[3:0]
	CS_clkRegs& setcs_trans_max_offset(uint val);
	uint getcs_trans_max_offset();

	//CSR34[11:8]
	CS_clkRegs& setcs_trans_max_lckchk(uint val);
	uint getcs_trans_max_lckchk();

	//CSR34[7:4]
	CS_clkRegs& setcs_trans_max_maxamp(uint val);
	uint getcs_trans_max_maxamp();

	//CSR34[3:0]
	CS_clkRegs& setcs_trans_max_bdsel(uint val);
	uint getcs_trans_max_bdsel();

	//CSR35[10:1]
	CS_clkRegs& setcs_fd_threshold(uint val);
	uint getcs_fd_threshold();

	//CSR35[0:0]
	CS_clkRegs& setcs_meas_fd_wait(uint val);
	uint getcs_meas_fd_wait();

	//CSR36[13:12]
	CS_clkRegs& setcs_fd_ref_cnt_dv(uint val);
	uint getcs_fd_ref_cnt_dv();

	//CSR36[11:0]
	CS_clkRegs& setcs_fd_ref_cnt_lv(uint val);
	uint getcs_fd_ref_cnt_lv();

	//CSR37[13:12]
	CS_clkRegs& setcs_fd_fb_cnt_dv(uint val);
	uint getcs_fd_fb_cnt_dv();

	//CSR37[11:0]
	CS_clkRegs& setcs_fd_fb_cnt_lv(uint val);
	uint getcs_fd_fb_cnt_lv();

	//CSR38[14:5]
	CS_clkRegs& setcs_timer_value(uint val);
	uint getcs_timer_value();

	//CSR38[4:2]
	CS_clkRegs& setcs_timer_div_value(uint val);
	uint getcs_timer_div_value();

	//CSR38[1:1]
	CS_clkRegs& setcs_timer_div_en(uint val);
	uint getcs_timer_div_en();

	//CSR38[0:0]
	CS_clkRegs& setcs_timer_stop(uint val);
	uint getcs_timer_stop();

	//CSR39[3:1]
	CS_clkRegs& setcs_lld_fb_div_ratio(uint val);
	uint getcs_lld_fb_div_ratio();

	//CSR39[0:0]
	CS_clkRegs& setcs_lld_once(uint val);
	uint getcs_lld_once();

	//CSR40[14:12]
	CS_clkRegs& setcs_lld_ref_cnt_dv(uint val);
	uint getcs_lld_ref_cnt_dv();

	//CSR40[11:0]
	CS_clkRegs& setcs_lld_ref_cnt_lv(uint val);
	uint getcs_lld_ref_cnt_lv();

	//CSR41[14:12]
	CS_clkRegs& setcs_lld_fb_cnt_dv(uint val);
	uint getcs_lld_fb_cnt_dv();

	//CSR41[11:0]
	CS_clkRegs& setcs_lld_fb_cnt_lv(uint val);
	uint getcs_lld_fb_cnt_lv();

	//CSR42[9:1]
	CS_clkRegs& setcs_lcd_fb_div_ratio(uint val);
	uint getcs_lcd_fb_div_ratio();

	//CSR42[0:0]
	CS_clkRegs& setcs_lcd_override(uint val);
	uint getcs_lcd_override();

	//CSR43[13:13]
	CS_clkRegs& setssc_freeze(uint val);
	uint getssc_freeze();

	//CSR43[12:12]
	CS_clkRegs& setssc_freeze_mode(uint val);
	uint getssc_freeze_mode();

	//CSR43[11:11]
	CS_clkRegs& setssc_freeze_en_sel(uint val);
	uint getssc_freeze_en_sel();

	//CSR43[10:0]
	CS_clkRegs& setcs_lcd_fb_cnt_lv(uint val);
	uint getcs_lcd_fb_cnt_lv();

	//CSR44[15:14]
	CS_clkRegs& setcp_dlf_resfdbkpwrdb(uint val);
	uint getcp_dlf_resfdbkpwrdb();

	//CSR44[13:13]
	CS_clkRegs& setcp_dlf_sample_edge_switch(uint val);
	uint getcp_dlf_sample_edge_switch();

	//CSR44[12:12]
	CS_clkRegs& setcp_dlf_cmfb_switch(uint val);
	uint getcp_dlf_cmfb_switch();

	//CSR44[11:10]
	CS_clkRegs& setrefclk1_cml_bias_ctrl(uint val);
	uint getrefclk1_cml_bias_ctrl();

	//CSR44[9:8]
	CS_clkRegs& setrefclk0_cml_bias_ctrl(uint val);
	uint getrefclk0_cml_bias_ctrl();

	//CSR44[5:5]
	CS_clkRegs& setcp_op_compensation_switch(uint val);
	uint getcp_op_compensation_switch();

	//CSR44[4:0]
	CS_clkRegs& setcpcintsel(uint val);
	uint getcpcintsel();

	//CSR45[15:14]
	CS_clkRegs& setssrefclk1_distbiasctrl(uint val);
	uint getssrefclk1_distbiasctrl();

	//CSR45[13:12]
	CS_clkRegs& setssrefclk0_distbiasctrl(uint val);
	uint getssrefclk0_distbiasctrl();

	//CSR45[11:10]
	CS_clkRegs& setssrefclk1_rcvbiasctrl(uint val);
	uint getssrefclk1_rcvbiasctrl();

	//CSR45[9:8]
	CS_clkRegs& setssrefclk0_rcvbiasctrl(uint val);
	uint getssrefclk0_rcvbiasctrl();

	//CSR45[7:7]
	CS_clkRegs& setss_slavemode(uint val);
	uint getss_slavemode();

	//CSR45[6:0]
	CS_clkRegs& setcs_spare(uint val);
	uint getcs_spare();

	//CSR46[15:0]
	CS_clkRegs& setcs_debugging_ctrl1(uint val);
	uint getcs_debugging_ctrl1();

	//CSR47[14:13]
	CS_clkRegs& setbg_stu_ref_sel(uint val);
	uint getbg_stu_ref_sel();

	//CSR47[12:12]
	CS_clkRegs& setbg_icv_ref_sel(uint val);
	uint getbg_icv_ref_sel();

	//CSR47[11:0]
	uint getcs_lld_ref_freq();

	//CSR48[15:14]
	CS_clkRegs& settempcompensel(uint val);
	uint gettempcompensel();

	//CSR48[13:12]
	CS_clkRegs& settempcompensel_current(uint val);
	uint gettempcompensel_current();

	//CSR48[11:0]
	uint getcs_fd_ref_freq();

	//CSR49[15:12]
	CS_clkRegs& setvtuneshift_sel(uint val);
	uint getvtuneshift_sel();

	//CSR49[11:0]
	uint getcs_fd_fb_freq();

	//CSR50[12:0]
	uint getcs_fd_diff_freq();

	//CSR51[15:15]
	uint getcs_lld_done();

	//CSR51[12:0]
	uint getcs_lld_diff_freq();

	//CSR52[11:0]
	uint getcs_lld_fb_freq();

	//CSR53[15:0]
	uint getcs_misc_status();

	//CSR54[15:0]
	uint getcs_calib_fsm_status();

	//CSR55[15:0]
	uint getcs_gcalib_fsm_status();

	//CSR56[15:14]
	CS_clkRegs& setssctype(uint val);
	uint getssctype();

	//CSR56[8:0]
	CS_clkRegs& setsscfreq(uint val);
	uint getsscfreq();

	//CSR57[13:12]
	CS_clkRegs& setssc_pulsewidth(uint val);
	uint getssc_pulsewidth();

	//CSR57[7:7]
	CS_clkRegs& setssc_bypassb(uint val);
	uint getssc_bypassb();

	//CSR57[6:0]
	CS_clkRegs& setsscamp(uint val);
	uint getsscamp();

	//CSR58[15:15]
	CS_clkRegs& setssc_gen_clr(uint val);
	uint getssc_gen_clr();

	//CSR58[14:14]
	CS_clkRegs& setssc_gen_soft_rstb(uint val);
	uint getssc_gen_soft_rstb();

	//CSR58[13:13]
	CS_clkRegs& setssc_gen_start_mode(uint val);
	uint getssc_gen_start_mode();

	//CSR58[12:12]
	CS_clkRegs& setcp_i_intchp_tune(uint val);
	uint getcp_i_intchp_tune();

	//CSR58[11:11]
	CS_clkRegs& setpwrdb_pll0_wordclk2dig_32b(uint val);
	uint getpwrdb_pll0_wordclk2dig_32b();

	//CSR58[10:10]
	CS_clkRegs& setlcvco_tempcompensate_pwrdb(uint val);
	uint getlcvco_tempcompensate_pwrdb();

	//CSR58[9:9]
	CS_clkRegs& setssc_clksel(uint val);
	uint getssc_clksel();

	//CSR58[8:8]
	CS_clkRegs& setssc_gen_manual_start(uint val);
	uint getssc_gen_manual_start();

	//CSR58[5:0]
	CS_clkRegs& setssc_phswrite(uint val);
	uint getssc_phswrite();

	//CSR59[4:0]
	uint getssc_picode();

	//CSR60[15:15]
	CS_clkRegs& setssc_picode_read_start(uint val);
	uint getssc_picode_read_start();

	//CSR60[14:12]
	CS_clkRegs& setsscatt(uint val);
	uint getsscatt();

	//CSR60[11:10]
	CS_clkRegs& setssc_spare(uint val);
	uint getssc_spare();

	//CSR60[9:9]
	CS_clkRegs& setfbkclk_pulsewidth_mod(uint val);
	uint getfbkclk_pulsewidth_mod();

	//CSR60[8:8]
	CS_clkRegs& setssc_pwrdb(uint val);
	uint getssc_pwrdb();

	//CSR60[7:6]
	CS_clkRegs& setssc_picode_delay(uint val);
	uint getssc_picode_delay();

	//CSR60[5:4]
	CS_clkRegs& setpiout_caps(uint val);
	uint getpiout_caps();

	//CSR60[3:2]
	CS_clkRegs& setpidrvin_cur(uint val);
	uint getpidrvin_cur();

	//CSR60[1:0]
	CS_clkRegs& setpidrvin_caps(uint val);
	uint getpidrvin_caps();

	//CSR61[15:15]
	CS_clkRegs& setwordclkdiv2(uint val);
	uint getwordclkdiv2();

	//CSR61[14:13]
	CS_clkRegs& setwordclkdiv(uint val);
	uint getwordclkdiv();

	//CSR61[12:12]
	CS_clkRegs& setwordclkdiv2_16b32b(uint val);
	uint getwordclkdiv2_16b32b();

	//CSR62[15:14]
	CS_clkRegs& setmeas_num(uint val);
	uint getmeas_num();

	//CSR62[13:5]
	CS_clkRegs& settemp_clk_div(uint val);
	uint gettemp_clk_div();

	//CSR62[4:4]
	CS_clkRegs& settsen_temp_en(uint val);
	uint gettsen_temp_en();

	//CSR62[3:2]
	CS_clkRegs& settsen_temp_ct_sel(uint val);
	uint gettsen_temp_ct_sel();

	//CSR63[15:6]
	uint getchip_temp_out();

};

#endif // HILINKCSCLKREGS_H_
