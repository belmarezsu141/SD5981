#ifndef HILINKCSCLKREGS_H_
#define HILINKCSCLKREGS_H_

#include <HILINK_DRIVE/HiLink_Regs_Base.h>
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

	/// Select the source of PLL0's reference clock. (Refer to fig.5 in  HiLink30_datasheet)
	/// 0 = Select the reference clock from REFCLKBUS0 as PLL0's reference clock.
	/// 1 = Select the reference clock from REFCLKBUS1 as PLL0's reference clock.
			const T_REG_INFO_EX& pll0refclksel();	//CSR0[14:14]

	/// Set the vco 'Na' divider value  for PLL0  (Refer to fig.7 in  HiLink30_datasheet). 
	/// 00 =  1                
	/// 01 =  2                
	/// 10 =  3              
	/// 11 =  2
			const T_REG_INFO_EX& pll0vcodivna();	//CSR0[12:11]

	/// Set the vco 'Ka'   divider value  for PLL0   (Refer to fig.7 in  HiLink30_datasheet).     
	/// 00 =  1                
	/// 01 =  1.5                
	/// 10 =  2              
	/// 11 =   2
			const T_REG_INFO_EX& pll0vcodivka();	//CSR0[10:9]

	/// Sets the P-counter value of the feedback divider ratio (Nb) for PLL0 (Refer to fig.7 in  HiLink30_datasheet).   The feedback divider ratio is calculated as follows:
	///          Nb=4*(P+1)+S+2      
	/// where  P is greater than or equal to 1;   S is greater than or equal to 0;   and S is the maximum possible value where P is greater than or equal to S;   Nb,P,S are all integer values
	/// (Refer to  PLL0FBDIVS for definition of  S value)
			const T_REG_INFO_EX& pll0fbdivp();	//CSR0[8:4]

	/// Sets the S-counter value of the feedback divider ratio (Nb) for PLL0 (Refer to fig.7 in  HiLink30_datasheet).   The feedback divider ratio is calculated as follows:
	///          Nb=4*(P+1)+S+2   
	/// where  P is greater than or equal to 1;   S  is greater than or equal to 0;   and S is the maximum possible value P is greater than or equal to S;  Nb,P,S are all integer values
	/// (Refer to PLL0FBDIVP for definition of  P value)
			const T_REG_INFO_EX& pll0fbdivs();	//CSR0[3:0]

	/// (Changed function in V101)
	/// CS refclk monitor powerdown
	/// 0 = Power down
	/// 1= Power up
			const T_REG_INFO_EX& pll0hsclkdistpwrdb();	//CSR1[15:15]

	/// spare signal in H30 CS
			const T_REG_INFO_EX& pll0hsclkdivpwrdb();	//CSR1[14:14]

	/// Sets the High-speed clock spine divider 'Kb' for PLL0  (Refer to fig.7 in  HiLink30_datasheet) :
	///                   Kb
	/// xx00:            1
	/// xx01:            2
	/// xx10:            3
	/// xx11:          power down Kb divider
			const T_REG_INFO_EX& pll0hsclkdiv();	//CSR1[13:10]

	/// bit[1:0] spare signal in H30 CS
	/// bit[2]  The M-divider in the pll0 hsclk has a div-by-2 at its input.  This control will bypass it:
	/// 0 = div-by-2 not bypassed
	/// 1 = div-by-2 is bypassed
			const T_REG_INFO_EX& pll0hsclkdistspare();	//CSR1[9:7]

	/// Sets the Reference clock divider 'M' for PLL0  (Refer to fig.7 in  HiLink30_datasheet)
	/// 00 = 1 
	/// 01 = 1 
	/// 10 = 2 
	/// 11 = 3
			const T_REG_INFO_EX& pll0refclkdiv();	//CSR1[6:5]

	/// PLL0 south facing hsclk distribution power down 
	/// 0 = powered down
	/// 1= powered up
			const T_REG_INFO_EX& pll0hsclkdivsouthpwrdb();	//CSR1[4:4]

	/// Sets the Word clock divider 'J_40b' for PLL0 (Refer to fig.7 in  HiLink30_datasheet)
	/// 00 = divided by 10  (ie, spine clock div-by-20)
	/// 01 = divided by 20 (ie, spine clock div-by-40)
	/// 10 = divided by 8  (ie, spine clock div-by-16)
	/// 11 = divided by 16  (ie, spine clock div-by-32)
			const T_REG_INFO_EX& pll0mclkdiv40b();	//CSR1[3:2]

	/// Sets the Word clock divider 'J_32b'  (for 32-bit application) for PLL0  (Refer to fig.7 in  HiLink30_datasheet)
	/// 00 = divided by 8  (ie, spine clock div-by-16)
	/// 01 = divided by 16  (ie, spine clock div-by-32)
	/// 10 = divided by 10  (ie, spine clock div-by-20)
	/// 11 = divided by 20  (ie, spine clock div-by-40)
			const T_REG_INFO_EX& pll0mclkdiv32b();	//CSR1[1:0]

	/// Sets  LCVCO out-of-lock threshold for PLL0.   A value between 1 and 31 can be set.  
	/// Note: For LCVCO to lock, this field should not be programmed to 0.
			const T_REG_INFO_EX& pll0lolthr();	//CSR2[10:6]

	/// Sets LCVCO loss-of-clock threshold for PLL0.
	/// 000 = 128
	/// 001 = 256
	/// 010 = 512
	/// 011 = 1024
	/// 100 = 2048
	/// 101 = 4096
	/// 11x = 4096
	/// (Note: A value less the 0x5 will cause False alarm )
			const T_REG_INFO_EX& pll0locthr();	//CSR2[5:3]

	/// LCVCO loss-of-lock mode for PLL0. Choose how loss-of-lock detection will start after LCVCO calibration is done (coarse tune).
	/// 0 = automatically start.
	/// 1 = manually start.
			const T_REG_INFO_EX& pll0lolmode();	//CSR2[2:2]

	/// LCVCO out-of-lock status for PLL0. Out-of-lock status is latched until being read.
	/// 0 = LCVCO locked
	/// 1 = LCVCO out of lock
			const T_REG_INFO_EX& pll0outoflock();	//CSR2[1:1]

	/// Loss of LCVCO clock indicator for PLL0. Status is latched until being read 
	/// 0 = LCVCO clock is active
	/// 1 = LCVCO clock is not active
			const T_REG_INFO_EX& pll0lossoflcvcoclk();	//CSR2[0:0]

	/// Select the source of PLL1's reference clock. (Refer to fig.5 in  HiLink30_datasheet)
	/// 0 = Select the reference clock from REFCLKBUS0 as PLL1's reference clock.
	/// 1 = Select the reference clock from REFCLKBUS1 as PLL1's reference clock.
			const T_REG_INFO_EX& pll1refclksel();	//CSR3[15:15]

	/// Sets the Reference clock divider 'M' for PLL1  (Refer to fig.7 in  HiLink30_datasheet)
	/// 00 = 1 
	/// 01 = 1 
	/// 10 = 2 
	/// 11 = 3
			const T_REG_INFO_EX& pll1refclkdiv();	//CSR3[14:13]

	/// Set the vco  'Na'  divider value  for PLL1  (Refer to fig.7 in  HiLink30_datasheet). 
	/// 00 =  1                
	/// 01 =  2                
	/// 10 =  3              
	/// 11 =  2
			const T_REG_INFO_EX& pll1vcodivna();	//CSR3[12:11]

	/// Set the vco 'Ka' divider value for PLL1  (Refer to fig.7 in  HiLink30_datasheet). 
	/// 00 =  1                
	/// 01 =  1.5                
	/// 10 =  2              
	/// 11 =   2
			const T_REG_INFO_EX& pll1vcodivka();	//CSR3[10:9]

	/// Sets the P-counter value of the feedback divider ratio (Nb) for PLL0 (Refer to fig.7 in  HiLink30_datasheet).   The feedback divider ratio is calculated as follows:
	///          Nb=4*(P+1)+S+2   
	/// where  P greater than or equal to 1;   S  greater than or equal to 0;   and S is the maximum possible value where P greater than or equal to S;   Nb,P,S are all integer values
	/// (Refer to CSR3 register field PLL1FBDIVS for definition of  S value)
			const T_REG_INFO_EX& pll1fbdivp();	//CSR3[8:4]

	/// Sets the S-counter value of the feedback divider ratio (Nb) for PLL0 (Refer to fig.7 in  HiLink30_datasheet).   The feedback divider ratio is calculated as follows:
	///          Nb=4*(P+1)+S+2   
	/// where  P greater than or equal to 1;   S  greater than or equal to 0;   and S is the maximum possible value where P greater than or equal to S;  Nb,P,S are all integer values
	/// (Refer to CSR3 register field PLL1FBDIVP for definition of  P value)
			const T_REG_INFO_EX& pll1fbdivs();	//CSR3[3:0]

	/// spare signal, not  used in  hsclkdist block
			const T_REG_INFO_EX& pll1hsclkdistpwrdb();	//CSR4[15:15]

	/// spare signal in H30 CS
			const T_REG_INFO_EX& pll1hsclkdivpwrdb();	//CSR4[14:14]

	/// Sets the High-speed clock spine divider 'Kb' for PLL1  (Refer to fig.7 in  HiLink30_datasheet) :
	///                   Kb
	/// xx00:            1
	/// xx01:            2
	/// xx10:            3
	/// xx11:           power down Kb divider
			const T_REG_INFO_EX& pll1hsclkdiv();	//CSR4[13:10]

	/// bit[1:0]: spare signal in H30 CS
	/// bit[2] :  The M-divider in the pll1 hsclk has a div-by-2 at its input.  This control will bypass it:
	/// 0 = div-by-2 not bypassed
	/// 1 = div-by-2 is bypassed
			const T_REG_INFO_EX& pll1hsclkdistspare();	//CSR4[9:7]

	/// PLL1 south facing hsclk distribution power down 
	/// 0 = powered down
	/// 1= powered up
			const T_REG_INFO_EX& pll1hsclkdivsouthpwrdb();	//CSR4[4:4]

	/// Sets the Word clock divider 'J_40b' for PLL1 (Refer to fig.7 in  HiLink30_datasheet)
	/// 00 = divided by 10 (ie., spine clock divided by 20)
	/// 01 = divided by 20 (ie., spine clock divided by 40)
	/// 10 = divided by 8  (ie., spine clock divided by 16)
	/// 11 = divided by 16 (ie., spine clock divided by 32)
			const T_REG_INFO_EX& pll1mclkdiv40b();	//CSR4[3:2]

	/// Sets the Word clock divider 'J_32b'  (for 32-bit application) for PLL1  (Refer to fig.7 in  HiLink30_datasheet)
	/// 00 = divided by 8  (ie., spine clock divided by 16)
	/// 01 = divided by 16 (ie., spine clock divided by 32)
	/// 10 = divided by 10 (ie., spine clock divided by 20)
	/// 11 = divided by 20 (ie., spine clock divided by 40)
			const T_REG_INFO_EX& pll1mclkdiv32b();	//CSR4[1:0]

	/// Sets  LCVCO out-of-lock threshold for PLL1.   A value between 1 and 31 can be set.  
	/// Note: For LCVCO to lock, this field should not be programmed to 0.
			const T_REG_INFO_EX& pll1lolthr();	//CSR5[10:6]

	/// LCVCO loss-of-clock threshold for PLL1.
	/// 000 = 128
	/// 001 = 256
	/// 010 = 512
	/// 011 = 1024
	/// 100 = 2048
	/// 101 = 4096
	/// 11x = 4096
	/// (Note: A value less the 0x5 will cause False alarm )
			const T_REG_INFO_EX& pll1locthr();	//CSR5[5:3]

	/// Select LCVCO loss-of-lock detection mode for PLL1. It determines how the loss-of-lock detection will start after LCVCO calibration is done (coarse tune).
	/// 0 = automatic
	/// 1 = manual
			const T_REG_INFO_EX& pll1lolmode();	//CSR5[2:2]

	/// LCVCO out-of-lock status for PLL1. Out-of-lock status is latched until being read 
	/// 0 = LCVCO locked
	/// 1 = LCVCO out of lock
			const T_REG_INFO_EX& pll1outoflock();	//CSR5[1:1]

	/// Loss of LCVCO clock indicator for PLL1. Status is latched until being read 
	/// 0 = LCVCO clock is active
	/// 1 = LCVCO clock is not active
			const T_REG_INFO_EX& pll1lossoflcvcoclk();	//CSR5[0:0]

	/// Div-40 word clk select. (Refer to fig.6 in  HiLink30_datasheet)
	/// 0 = Choose the div-40 clock from PLL0.
	/// 1 = Choose the div-40 clock from PLL1.
			const T_REG_INFO_EX& wordclk40bsel();	//CSR6[15:15]

	/// Div-32 word clk select. (Refer to fig.6  in  HiLink30_datasheet)
	/// 0 = Choose the div-32 clock from PLL0.
	/// 1 = Choose the div-32 clock from PLL1.
			const T_REG_INFO_EX& wordclk32bsel();	//CSR6[14:14]

	/// Word clock select. (Refer to fig.6  in HiLink30_datasheet)
	/// 0 = Choose the 40B word clock.
	/// 1 = Choose the 32B word clock.
			const T_REG_INFO_EX& wordclksel();	//CSR6[13:13]

	/// Core clock select. (Refer to fig.6  in  HiLink30_datasheet)
	/// 0 = Choose lifeclk2dig clock as the source of core clock.
	/// 1 = Choose mclk_40bit/mclk_32bit clock as the core clock
			const T_REG_INFO_EX& coreclksel();	//CSR6[12:12]

	/// enable the clock for the new LCVCO regulator in the slave PLL
	/// 0 = disable   
	/// 1= enable the clock from master hsclkdist to be clocking the  slave LCVCO new regulator
			const T_REG_INFO_EX& pll0hsclk2vcovregen();	//CSR6[4:4]

	/// Divider ratio for lifeclk2dig  (Refer to fig.6  in HiLink30_datasheet) . Used for life clock generation.
	/// 00 = divided by 1
	/// 01 = divided by 2
	/// 10 = divided by 3
	/// 11 = divided by 4
			const T_REG_INFO_EX& lifeclk2digdiv();	//CSR6[3:2]

	/// Divider ratio for wordclk2dig  (Refer to fig.6  in HiLink30_datasheet) . Used for life clock generation.
	/// 00 = divided by 1
	/// 01 = divided by 2
	/// 10 = divided by 3
	/// 11 = divided by 4
			const T_REG_INFO_EX& wordclk2digdiv();	//CSR6[1:0]

	/// CMU (Clock Multiplier Unit) bias distribution power down, active low
	/// 0 = power down
	/// 1= power up
			const T_REG_INFO_EX& biascmupwrdb();	//CSR7[15:15]

	/// refclk cml2cmos buffer power down, active low. When activated, lifeclk2dig disable
	/// 0= power down
	/// 1= power up
			const T_REG_INFO_EX& refclkdistpwrdb();	//CSR7[14:14]

	/// CMU (Clock Multiplier Unit) bias distribution test mode enable , active high
	/// 0 = mission mode
	/// 1 = test mode enabled
			const T_REG_INFO_EX& biascmutestmode();	//CSR7[13:13]

	/// ADC (in ClockSlice)  power down, active low
	/// 0 = Power down 
	/// 1 = Power up
			const T_REG_INFO_EX& adcpwrdb();	//CSR7[12:12]

	/// Comparator (in ClockSlice)  power down, active low.
	/// 0 = Power down 
	/// 1 = Power up
			const T_REG_INFO_EX& comppwrdb();	//CSR7[11:11]

	/// refclk0 distribution buffer bias control
	/// 00 = xx uA
	/// 01 = 
	/// 10 =
	/// 11 = yy uA
			const T_REG_INFO_EX& refclk0biasctrl();	//CSR7[3:2]

	/// refclk1 distribution buffer bias control
	/// 00 = xx uA
	/// 01 = 
	/// 10 =
	/// 11 = yy uA
			const T_REG_INFO_EX& refclk1biasctrl();	//CSR7[1:0]

	/// PLL0 power down, active low
	/// 0 = Power down 
	/// 1 = Power up
	/// New in v101: Used as a trigger to power up/down PLL0 sequentially with default settings.   (PLL1 if ON will also sequentially power down before PLL0)
			const T_REG_INFO_EX& pll0pwrdb();	//CSR8[15:15]

	/// provide a 200k feedback resistor shunt across the DLF (Digital Loop Filter) integrator capacitor in PLL0, active low. 
	/// 0 = no resistor in shunt
	/// 1 = 200K resistor shunt across DLF integ cap applied
			const T_REG_INFO_EX& pll0dlfresfbpwrdb();	//CSR8[9:9]

	/// DLF (Digital Loop Filter) circuitry power down for PLL0, active low
	/// 0 = Power down 
	/// 1 = Power up
			const T_REG_INFO_EX& pll0dlfpwrdb();	//CSR8[8:8]

	/// Sample and Hold circuitry power down in PLL0, active low
	/// 0 = Power down 
	/// 1 = Power up
			const T_REG_INFO_EX& pll0dlfshpwrdb();	//CSR8[7:7]

	/// DLF test mode power down in PLL0. It also disconnects DTB and ATB DLF muxes,  active  low.
	/// 0 = Power down 
	/// 1 = Power up
			const T_REG_INFO_EX& pll0dlftstpwrdb();	//CSR8[6:6]

	/// DLF active common mode circuitry power down for PLL0.  A 100k feedback resistor shunts the DLF integrator capacitor instead. Active Low
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& pll0dlfcmfbpwrdb();	//CSR8[5:5]

	/// Enable chopping function
	/// 0: chopping is disabled on the DLF
	/// 1: chopping is enabled on the DLF
			const T_REG_INFO_EX& pll0dlfchoppwrdb();	//CSR8[4:4]

	/// PLL0 pll regulator power down, active low
	/// 0 = Power down 
	/// 1 = Power up
			const T_REG_INFO_EX& pll0vregpllpwrdb();	//CSR8[3:3]

	/// PLL0  dlf regulator power down, active low
	/// 0 = Power down 
	/// 1 = Power up
			const T_REG_INFO_EX& pll0vregdlfpwrdb();	//CSR8[2:2]

	/// PLL0 vcodivider regulator power down, active low
	/// 0 = Power down 
	/// 1 = Power up
			const T_REG_INFO_EX& pll0vregvcodivpwrdb();	//CSR8[0:0]

	/// Swap PFD (Phase Frequency Detector) UP and DOWN signal for PLL0, Active high
			const T_REG_INFO_EX& pll0pfdupdnswap();	//CSR9[14:14]

	/// Force the PFD output to be UP for PLL0.
	/// 0 = Let the PFD detect frequency and phase difference.
	/// 1 = Force the PFD output to be UP.
	/// Note: setting both PFDFORCEUP and PFDFORCEDN to 1 is not allowed.
			const T_REG_INFO_EX& pll0pfdforceup();	//CSR9[13:13]

	/// Force the PFD output to be DOWN for PLL0.
	/// 0 = Let the PFD detect frequency and phase difference.
	/// 1 = Force the PFD output to be DOWN.
	/// Note: setting both PFDFORCEUP and PFDFORCEDN to 1 is not allowed.
			const T_REG_INFO_EX& pll0pfdforcedn();	//CSR9[12:12]

	/// Select the pulse width of the PFD outputs (both UP/DOWN) to adjust the bandwidth of the PLL0.
	/// 00 = 65ps
	/// 01 = 84ps
	/// 10 = 104ps
	/// 11 = 135ps
			const T_REG_INFO_EX& pll0pfdpulsewidth();	//CSR9[11:10]

	/// VCO calibration enable signal for PLL0, active low.
	/// 0 = Open Loop PLL
	/// 1 = Closed loop PLL
	/// 
	/// Note: In VCO auto calib. mode, when the calib. FSM starts, it loads the register value on the signal which drives the analog. When the calib. FSM finishes, it sets 1 on the same signal.
			const T_REG_INFO_EX& pll0cpcalrstb();	//CSR9[7:7]

	/// PLL0 vtune differential voltage control when VCO is being calibrated: (The asserted levels have changed in v101)
	/// 000 =  -400mV
	/// 001 =  -300mV
	/// 010 =  -200mV
	/// 011 =  -100mV
	/// 100  =  0V (default)
	/// 101 =  100mV
	/// 110 =  200mV
	/// 111 =  300mV
			const T_REG_INFO_EX& pll0cpcalrstlvl();	//CSR9[6:4]

	/// Selects Charge pump reference voltage level for PLL0. 
	/// 000 =  463mV
	/// 001 =  470mV
	/// 010 =  480mV 
	/// 011 =  493mV
	/// 100 =  502mV (default)
	/// 101 =  517mV
	/// 110 =  527mV
	/// 111 =  536mV
			const T_REG_INFO_EX& pll0cpvreflvl();	//CSR9[2:0]

	/// Programs PLL0 integral charge pump current 
	/// 00 = 10 uA
	/// 01 = 20 uA
	/// 10 = 40 uA
	/// 11 = 60 uA
			const T_REG_INFO_EX& pll0cpintcrntsel();	//CSR10[12:11]

	/// Programs PLL0 proportional charge pump current  
	/// 000 = 1000 uA
	/// 001 = 1200 uA
	/// 010 = 1400 uA
	/// 011 = 1600 uA
	/// 100 = 1800 uA
	/// 101 = 2000 uA
	/// 110 = 2200 uA
	/// 111 = 2400 uA
			const T_REG_INFO_EX& pll0cppropcrntsel();	//CSR10[6:4]

	/// Programs the PLL0 DLF (Digital Loop Filter) integrator capacitor (Cint) unit count from 6 to 14. Each Cint unit is 545fF. Select the DLF integrator capacitor (Cint) and proportional capacitor (Cprop). dlf_cint_sel_i[2] is spare bit.
	/// [1:0]=00, Cint=2.4pF,  Cprop=2.18pF
	/// [1:0]=01, integral C=4.8pF,  Cprop=2.18pF
	/// Default  [1:0]=10, Cint=7.2pF,  Cprop=4.36pF
	/// [1:0]=11, Cint=9.6pF,  Cprop=4.36pF
			const T_REG_INFO_EX& pll0dlfcintsel();	//CSR11[15:13]

	/// Sets PLL0 Sample and Hold clock sample width
	/// 0 = 1 ps
	/// 1 = 2 ps
			const T_REG_INFO_EX& pll0dlfshdelsel();	//CSR11[7:7]

	/// Diagnostic test mode for PLL0 DLF to sample internal digital signals of the DLF.
	/// (Not for Customer use)
			const T_REG_INFO_EX& pll0dlfseldtb();	//CSR11[6:2]

	/// Switches in PLL0 Sample and Hold capacitors
	/// 00 =  no caps connected
	/// 01 =  1.6pF
	/// 10 =  1.6pF
	/// 11 =  3.2pF
			const T_REG_INFO_EX& pll0dlfshcapsel();	//CSR11[1:0]

	/// VCO band select control bits for PLL0:
	/// 000 =  band0
	/// 001 =  band1
	/// 010 =  band2
	/// 011 =  band3
	/// Others = Not valid
			const T_REG_INFO_EX& pll0vcobandsel();	//CSR12[14:12]

	/// PLL0 Regulator RC filter short out control pin:
	/// 0 =  RC Filter is in use
	/// 1 =  RC Filter is shorted
			const T_REG_INFO_EX& pll0vcoregfilshorten();	//CSR12[11:11]

	/// This control bit is for test only. If PLL0 VCO can not start oscillating, setting this control bit  HIGH  (or 1) connects lvcc_vcocore directly to hvcc.
			const T_REG_INFO_EX& pll0vcoswthhien();	//CSR12[10:10]

	/// DESCRIPTION CHANGED IN V101 .... 
	/// PLL0 VCO frequency calibration control bits:
	/// Bit[4:1] 
	/// 0000= all caps turned off(highest osc freq for the band)
	/// 0001=1 cap turned on
	/// 0010= 2 caps turned on
	/// ...........
	/// 1111= 15 caps turned on 
	/// 
	/// Bit[0]  selects turn on of Half caps for increased freq granularity
			const T_REG_INFO_EX& pll0vcofreqcal();	//CSR12[9:5]

	/// regulator output voltage control bits used to trim internal  supply voltage of  PLL0 VCO
	/// 00000 = minimum Voltage 
	/// ..
	/// 11111 =  maximum Voltage
			const T_REG_INFO_EX& pll0vcoitank();	//CSR12[4:0]

	/// reference select for PLL0 VCO second regulator
	/// Reference voltage control signal for new regulator =  
	/// (Binary code)
	/// 0000 =  445mV
	/// 0001 =  455mV
	/// 0010 =  465mV
	/// 0011 =  475mV
	/// 0100 =  485mV
	/// 0101 =  495mV
	/// 0110 =  505mV
	/// 0111 =  515mV 
	/// 1000 =  525mV
	/// 1001 =  535mV
	/// 1010 =  545mV
	/// 1011 =  555mV
	/// 1100 to 1111 =  not used
			const T_REG_INFO_EX& pll0vcovref();	//CSR13[15:12]

	/// bit[1] used to control 1/4 LSB freqcal on PLL0 VCO tuning
	/// 0 = 1/4 LSB freqcal is not active
	/// 1 = 1/4 LSB freqcal is active
	/// 
	/// bit[0] spare bit
			const T_REG_INFO_EX& pll0vcodivspare();	//CSR13[11:10]

	/// select second regulator for PLL0 VCO 
	/// 0 = old regulator
	/// 1 = new regulator
			const T_REG_INFO_EX& pll0vcovregsel();	//CSR13[9:9]

	/// control code for divide-by-1.5 for PLL0
			const T_REG_INFO_EX& pll0vcodiv1p5ctrlcode();	//CSR13[8:4]

	/// select the clock input for the second regulator for PLL0 VCO
	/// 0 = external clock
	/// 1 = clock from VCO
			const T_REG_INFO_EX& pll0vcovregclksel();	//CSR13[3:3]

	/// Repurposed
	/// Switch low voltage control signal for new regulator for PLL0 =  
	/// (Binary code)
	/// 000 =  100mV
	/// 001 =  200mV
	/// 010 =  300mV
	/// 011 =  400mV
	/// 100 =  500mV
	/// 101 =  600mV
	/// 110 =  700mV
	/// 111 =  800mV
			const T_REG_INFO_EX& pll0vcodpmctrl();	//CSR13[2:0]

	/// Spare not used in v101
			const T_REG_INFO_EX& pll0vcopdpwrdb();	//CSR14[15:15]

	/// PLL0 voltage regulator process compensation control signal = 
	/// 0 =  ss corner
	/// 1 =  other corner
			const T_REG_INFO_EX& pll0vregplldpmen();	//CSR14[14:14]

	/// PLL0 voltage regulator bleed current control
	/// 0 =  enable bleed current
	/// 1 =  disable bleed current
			const T_REG_INFO_EX& pll0vregpllbleedb();	//CSR14[13:13]

	/// Voltage level control of vreg_pll  regulator of PLL0.
	/// 00000 =  Minimum voltage.
	/// ..
	/// 11111 =  Maximum voltage.
			const T_REG_INFO_EX& pll0vregpllsel();	//CSR14[12:8]

	/// DLF (Digital Loop Filter) regulator process compensation control signal for PLL0 :
	/// 0 =  ss corner
	/// 1 =  other corner
			const T_REG_INFO_EX& pll0vregdlfdpmen();	//CSR14[6:6]

	/// DLF clocking regulator bleed current control for PLL0.
	/// 0 =  enable bleed current
	/// 1 =  disable bleed current
			const T_REG_INFO_EX& pll0vregdlfbleedb();	//CSR14[5:5]

	/// Voltage level control of  vreg_dlf regulator of PLL0.
	/// 00000 = Minimum voltage.
	/// ..
	/// 11111 = Maximum voltage.
			const T_REG_INFO_EX& pll0vregdlfsel();	//CSR14[4:0]

	/// bandwidth selection for new regulator for PLL0
			const T_REG_INFO_EX& pll0vconewregbwsel();	//CSR15[15:14]

	/// Power down for vtune buffer  for PLL0
	/// 0 = power off   
	/// 1 = power on
			const T_REG_INFO_EX& pll0vcovtunebufpwrdb();	//CSR15[13:13]

	/// Spare not used
			const T_REG_INFO_EX& pll0vcocompenstart();	//CSR15[12:12]

	/// Spare not used
			const T_REG_INFO_EX& pll0vcocompenpwrdb();	//CSR15[11:11]

	/// Spare not used
			const T_REG_INFO_EX& pll0vcocompenbw();	//CSR15[10:9]

	/// PLL0 ITANK selection mode
	/// 0 =  Auto- calibrated by FSM
	/// 1 =  Manual - assigned by user
			const T_REG_INFO_EX& pll0itankcalmode();	//CSR15[8:8]

	/// PLL0 FREQCAL selection mode
	/// 0 =  Auto- calibrated by FSM
	/// 1 =  Manual - assigned by user
			const T_REG_INFO_EX& pll0freqcalmode();	//CSR15[7:7]

	/// vcodiv regulator process compensation control signal for PLL0 
	/// 0 =  ss corner
	/// 1 =  other corner
			const T_REG_INFO_EX& pll0vregvcodivdpmen();	//CSR15[6:6]

	/// vcodiv regulator bleed circuit control for PLL0
	/// 0 =  enable bleed current
	/// 1 =  disable bleed current
			const T_REG_INFO_EX& pll0vregvcodivbleedb();	//CSR15[5:5]

	/// Voltage level control of vreg_vcodiv  regulator of PLL0
	/// 00000: Minimum voltage.
	/// ..
	/// 11111: Maximum voltage.
			const T_REG_INFO_EX& pll0vregvcodivsel();	//CSR15[4:0]

	/// bit[15] PLL0 LCVCO compensation force High
	/// 0 = normal operation
	/// 1 = force High
	/// 
	/// bit[14] PLL0 H16 compensator powerdown
	/// 0 = power off
	/// 1 = power on (active)
	/// 
	/// bits[13:0]  spare
			const T_REG_INFO_EX& pll0spare();	//CSR16[15:0]

	/// PLL1 power down, active low
	/// New in v101: Used as a trigger to power up/down PLL1 sequentially with default settings.
			const T_REG_INFO_EX& pll1pwrdb();	//CSR17[15:15]

	/// provide a 200k feedback resistor shunt across the DLF (Digital Loop Filter) integrator capacitor in PLL1, active low. 
	/// 0 = no resistor in shunt
	/// 1 = 200K resistor shunt across DLF integ cap applied
			const T_REG_INFO_EX& pll1dlfresfbpwrdb();	//CSR17[9:9]

	/// DLF (Digital Loop Filter) circuitry power down for PLL1, active low
	/// 0 = Power down 
	/// 1 = Power up
			const T_REG_INFO_EX& pll1dlfpwrdb();	//CSR17[8:8]

	/// Sample and Hold circuitry power down in PLL1, active low
	/// 0 = Power down 
	/// 1 = Power up
			const T_REG_INFO_EX& pll1dlfshpwrdb();	//CSR17[7:7]

	/// DLF  test mode power down in PLL1. It also disconnects DTB and ATB DLF muxes,  active  low.
	/// 0 = Power down 
	/// 1 = Power up
			const T_REG_INFO_EX& pll1dlftstpwrdb();	//CSR17[6:6]

	/// DLF active common mode circuitry power down for PLL1.  A 100k feedback resistor shunts the DLF integrator capacitor instead. Active Low
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& pll1dlfcmfbpwrdb();	//CSR17[5:5]

	/// pll1 enable chopping function
	/// 0: chopping is disabled on the DLF
	/// 1: chopping is enabled on the DLF
			const T_REG_INFO_EX& pll1dlfchoppwrdb();	//CSR17[4:4]

	/// PLL1 pll regulator power down, active low
	/// 0 = Power down 
	/// 1 = Power up
			const T_REG_INFO_EX& pll1vregpllpwrdb();	//CSR17[3:3]

	/// PLL1  dlf regulator power down, active low
	/// 0 = Power down 
	/// 1 = Power up
			const T_REG_INFO_EX& pll1vregdlfpwrdb();	//CSR17[2:2]

	/// PLL1 vcodivider regulator power down, active low
	/// 0 = Power down 
	/// 1 = Power up
			const T_REG_INFO_EX& pll1vregvcodivpwrdb();	//CSR17[0:0]

	/// Swap PFD (Phase Frequency Detector) UP and DOWN signal for PLL1, Active high
			const T_REG_INFO_EX& pll1pfdupdnswap();	//CSR18[14:14]

	/// Force the PFD output to be UP for PLL1.
	/// 0 = Let the PFD detect frequency and phase difference.
	/// 1 = Force the PFD output to be UP.
	/// Note: setting both PFDFORCEUP and PFDFORCEDN to 1 is not allowed.
			const T_REG_INFO_EX& pll1pfdforceup();	//CSR18[13:13]

	/// Force the PFD output to be DOWN for PLL1.
	/// 0 = Let the PFD detect frequency and phase difference.
	/// 1 = Force the PFD output to be DOWN.
	/// Note: setting both PFDFORCEUP and PFDFORCEDN to 1 is not allowed.
			const T_REG_INFO_EX& pll1pfdforcedn();	//CSR18[12:12]

	/// Select the pulse width of the PFD outputs (both UP/DOWN) to adjust the bandwidth of the PLL1.
	/// 00 = 65ps
	/// 01 = 84ps
	/// 10 = 104ps
	/// 11 = 135ps
			const T_REG_INFO_EX& pll1pfdpulsewidth();	//CSR18[11:10]

	/// VCO calibration enable signal for PLL1, active low.
	/// 0 = Open Loop PLL
	/// 1 = Closed loop PLL
	/// 
	/// Note: In VCO auto calib. mode, when the calib. FSM starts, it loads the register value on the signal which drives the analog. When the calib. FSM finishes, it sets 1 on the same signal.
			const T_REG_INFO_EX& pll1cpcalrstb();	//CSR18[7:7]

	/// PLL1 vtune differential voltage control when VCO is being calibrated :  (asserted levels have changed in v101)
	/// 000 =  -400mV
	/// 001 =  -300mV
	/// 010 =  -200mV
	/// 011 =  -100mV
	/// 100 =  0V (default )
	/// 101 =  100mV
	/// 110 =  200mV
	/// 111 =  300mV
			const T_REG_INFO_EX& pll1cpcalrstlvl();	//CSR18[6:4]

	/// Selects Charge pump reference voltage level for PLL0. 
	/// 000 =  463mV
	/// 001 =  470mV
	/// 010 =  480mV 
	/// 011 =  493mV
	/// 100 =  502mV (default)
	/// 101 =  517mV
	/// 110 =  527mV
	/// 111 =  536mV
			const T_REG_INFO_EX& pll1cpvreflvl();	//CSR18[2:0]

	/// Programs PLL1 integral charge pump current 
	/// 00 = 10 uA
	/// 01 = 20 uA
	/// 10 = 30 uA
	/// 11 = 40 uA
			const T_REG_INFO_EX& pll1cpintcrntsel();	//CSR19[12:11]

	/// Programs PLL1 proportional charge pump current  
	/// 000 = 1000 uA
	/// 001 = 1200 uA
	/// 010 = 1400 uA
	/// 011 = 1600 uA
	/// 100 = 1800 uA
	/// 101 = 2000 uA
	/// 110 = 2200 uA
	/// 111 = 2400 uA
			const T_REG_INFO_EX& pll1cppropcrntsel();	//CSR19[6:4]

	/// Programs the PLL1 DLF (Digital Loop Filter) integrator capacitor (Cint) unit count from 6 to 14. Each Cint unit is 545fF. Select the DLF integrator capacitor (Cint) and proportional capacitor (Cprop). dlf_cint_sel_i[2] is spare bit.
	/// [1:0]=00, Cint=2.4pF,  Cprop=2.18pF
	/// [1:0]=01, integral C=4.8pF,  Cprop=2.18pF
	/// Default  [1:0]=10, Cint=7.2pF,  Cprop=4.36pF
	/// [1:0]=11, Cint=9.6pF,  Cprop=4.36pF
			const T_REG_INFO_EX& pll1dlfcintsel();	//CSR20[15:13]

	/// Sets PLL1 Sample and Hold clock sample width
	/// 0 = 1 ps
	/// 1 = 2 ps
			const T_REG_INFO_EX& pll1dlfshdelsel();	//CSR20[7:7]

	/// Diagnostic test mode for PLL1 DLF to sample internal digital signals of the DLF.
	/// (Not for Customer use)
			const T_REG_INFO_EX& pll1dlfseldtb();	//CSR20[6:2]

	/// Switches in PLL1 Sample and Hold capacitors
	/// 00 =  no caps connected
	/// 01 =  1.6pF
	/// 10 =  1.6pF
	/// 11 =  3.2pF
			const T_REG_INFO_EX& pll1dlfshcapsel();	//CSR20[1:0]

	/// VCO band select control bits for PLL1 : 
	/// 000 =  band0
	/// 001 =  band1
	/// 010 =  band2
	/// 011 =  band3
	/// Others  =  Not valid
			const T_REG_INFO_EX& pll1vcobandsel();	//CSR21[14:12]

	/// PLL1 Regulator RC filter short out control pin = 
	/// 0 =  RC Filter is in use
	/// 1 =  RC Filter is shorted
			const T_REG_INFO_EX& pll1vcoregfilshorten();	//CSR21[11:11]

	/// This control bit is for test only. If PLL1 VCO can not start oscillating, setting this control bit  HIGH  connects lvcc_vcocore directly to hvcc.
			const T_REG_INFO_EX& pll1vcoswthhien();	//CSR21[10:10]

	/// DESCRIPTION CHANGED IN V101 .... 
	/// 
	/// PLL1 VCO frequency calibration control bits:
	/// Bit[4:1] 
	/// 0000= all caps turned off(highest osc freq for the band)
	/// 0001=1 cap turned on
	/// 0010= 2 caps turned on
	/// ...........
	/// 1111= 15 caps turned on 
	/// 
	/// Bit[0]  selects turn on of Half caps for increased freq granularity
			const T_REG_INFO_EX& pll1vcofreqcal();	//CSR21[9:5]

	/// regulator output voltage control bits used to trim internal  supply voltage of  PLL1 VCO
	/// 00000 = minimum Voltage 
	/// ..
	/// 11111 =  maximum Voltage
			const T_REG_INFO_EX& pll1vcoitank();	//CSR21[4:0]

	/// reference select for PLL1 VCO second regulator
	/// Reference voltage control signal for new regulator =  
	/// (Binary code)
	/// 0000 =  445mV
	/// 0001 =  455mV
	/// 0010 =  465mV
	/// 0011 =  475mV
	/// 0100 =  485mV
	/// 0101 =  495mV
	/// 0110 =  505mV
	/// 0111 =  515mV 
	/// 1000 =  525mV
	/// 1001 =  535mV
	/// 1010 =  545mV
	/// 1011 =  555mV
	/// 1100 ?1111 =  not used
			const T_REG_INFO_EX& pll1vcovref();	//CSR22[15:12]

	/// bit[1] used to control 1/4 LSB freqcal on PLL1 VCO tuning
	/// 0 = 1/4 LSB freqcal is not active
	/// 1 = 1/4 LSB freqcal is active
	/// 
	/// bit[0] spare bit
			const T_REG_INFO_EX& pll1vcodivspare();	//CSR22[11:10]

	/// select second regulator for PLL1 VCO 
	/// 0 = old regulator
	/// 1 = new regulator
			const T_REG_INFO_EX& pll1vcovregsel();	//CSR22[9:9]

	/// control code for divide-by-1.5 for PLL1
			const T_REG_INFO_EX& pll1vcodiv1p5ctrlcode();	//CSR22[8:4]

	/// select the clock input for the second regulator for PLL1 VCO
	/// 0 = external clock
	/// 1 = clock from VCO
			const T_REG_INFO_EX& pll1vcovregclksel();	//CSR22[3:3]

	/// Repurposed -
	/// Switch low voltage control signal for new regulator for PLL1 :  
	/// 000 =  100mV
	/// 001 =  200mV
	/// 010 =  300mV
	/// 011 =  400mV
	/// 100 =  500mV
	/// 101 =  600mV
	/// 110 =  700mV
	/// 111 =  800mV
			const T_REG_INFO_EX& pll1vcodpmctrl();	//CSR22[2:0]

	/// spare not used in v101
			const T_REG_INFO_EX& pll1vcopdpwrdb();	//CSR23[15:15]

	/// PLL1 voltage regulator process compensation control signal: 
	/// 0 =  ss corner
	/// 1 =  other corner
			const T_REG_INFO_EX& pll1vregplldpmen();	//CSR23[14:14]

	/// PLL1 voltage regulator bleed current control
	/// 0 =  enable bleed current
	/// 1 =  disable bleed current
			const T_REG_INFO_EX& pll1vregpllbleedb();	//CSR23[13:13]

	/// Voltage level control of vreg_pll  regulator of PLL1.
	/// 00000: Minimum voltage.
	/// ..
	/// 11111: Maximum voltage.
			const T_REG_INFO_EX& pll1vregpllsel();	//CSR23[12:8]

	/// DLF (Digital Loop Filter)  regulator process compensation control signal for PLL1 : 
	/// 0 =  ss corner
	/// 1 =  other corner
			const T_REG_INFO_EX& pll1vregdlfdpmen();	//CSR23[6:6]

	/// DLF clocking regulator bleed current control for PLL1.
	/// 0 =  enable bleed current
	/// 1 =  disable bleed current
			const T_REG_INFO_EX& pll1vregdlfbleedb();	//CSR23[5:5]

	/// Voltage level control of  vreg_dlf regulator of PLL1.
	/// 00000: Minimum voltage.
	/// ..
	/// 11111: Maximum voltage.
			const T_REG_INFO_EX& pll1vregdlfsel();	//CSR23[4:0]

	/// bandwidth selection for new regulator for PLL1
			const T_REG_INFO_EX& pll1vconewregbwsel();	//CSR24[15:14]

	/// Power down for vtune buffer  for PLL1
	/// 0 = power off   
	/// 1 = power on
			const T_REG_INFO_EX& pll1vcovtunebufpwrdb();	//CSR24[13:13]

	/// spare not used
			const T_REG_INFO_EX& pll1vcocompenstart();	//CSR24[12:12]

	/// spare not used
			const T_REG_INFO_EX& pll1vcocompenpwrdb();	//CSR24[11:11]

	/// spare not used
			const T_REG_INFO_EX& pll1vcocompenbw();	//CSR24[10:9]

	/// PLL1 ITANK selection mode
	/// 0 =  Auto- calibrated by FSM
	/// 1 =  Manual - assigned by user
			const T_REG_INFO_EX& pll1itankcalmode();	//CSR24[8:8]

	/// PLL1 FREQCAL selection mode
	/// 0 =  Auto- calibrated by FSM
	/// 1 =  Manual - assigned by user
			const T_REG_INFO_EX& pll1freqcalmode();	//CSR24[7:7]

	/// vcodiv regulator process compensation control signal for PLL1 : 
	/// 0 =  ss corner
	/// 1 =  other corner
			const T_REG_INFO_EX& pll1vregvcodivdpmen();	//CSR24[6:6]

	/// vcodiv regulator bleed circuit control for PLL1
	/// 0 =  enable bleed current
	/// 1 =  disable bleed current
			const T_REG_INFO_EX& pll1vregvcodivbleedb();	//CSR24[5:5]

	/// Voltage level control of vreg_vcodiv  regulator of PLL1
	/// 00000: Minimum voltage.
	/// ..
	/// 11111: Maximum voltage.
			const T_REG_INFO_EX& pll1vregvcodivsel();	//CSR24[4:0]

	/// bit[15] PLL1 LCVCO compensation force High
	/// 0 = normal operation
	/// 1 = force High
	/// 
	/// bit[14] PLL1 H16 compensator powerdown
	/// 0 = power off
	/// 1 = power on (active)
	/// 
	/// bits[13:0]  spare
			const T_REG_INFO_EX& pll1spare();	//CSR25[15:0]

	/// ADC (in Clock Slice)  Reset to discharge integrator and Start New measurement
	/// 0 = Reset to discharge integrator
	/// 1 =  Start New measurement
	/// Default as requested by Digital Design
			const T_REG_INFO_EX& adcrstb();	//CSR26[15:15]

	/// ADC (in Clock Slice) reference selector.  This bit also selects between hvcc_scaler code and 800mV mapper code from within DF code mapper:
	/// 0 = HVCC is the reference
	/// 1 = vref_bg (bandgap voltage 800mV) is the reference
			const T_REG_INFO_EX& adcabsmeasen();	//CSR26[14:14]

	/// ADC (in Clock Slice) input voltage selector
	/// 0 = This setting is for mission mode
	/// Both inputs are de-selected when TSENSOREN is enabled
	/// 1 = The ADC inputs are both connected to a reference voltage for calibration purpose
			const T_REG_INFO_EX& adctsten();	//CSR26[13:13]

	/// ADC (in Clock Slice) common mode control signal
	/// 00 = 500 mV
	/// 01 = 550 mV
	/// 10 = 600 mV
	/// 11 = 650 mV
			const T_REG_INFO_EX& adcvcmctrl();	//CSR26[12:11]

	/// Not Used
			const T_REG_INFO_EX& cstopfsmcalspare();	//CSR26[10:10]

	/// DPM Initial Settings Enable
	/// 0 =  default
	/// 1 =  Set by FW to propagate initial settings to analog I/F
			const T_REG_INFO_EX& dpminitsettingen();	//CSR26[9:9]

	/// Set to 1 to reset CS TOP FSM
			const T_REG_INFO_EX& cstopfsmcalclr();	//CSR26[8:8]

	/// MISC CAL FORCE DEFAULT =  set each bit to 1 to force misc cal fsm to start from default value. 
	/// [7] =  BGV cal
	/// [6] =  RXTERM cal
	/// [5] =  PLL0/PLL1_CPVREF cal
	/// [4] =  PLL0/PLL1_VREG_DLF_PLL_VCODIV cal
			const T_REG_INFO_EX& misccalforcedefault();	//CSR26[7:4]

	/// DPM Detection Done
			const T_REG_INFO_EX& dpmdetdone();	//CSR26[3:3]

	/// DPM Detection Task Select = 
	/// [0] =  set to 1 to enable Temperature Sensor reading
	/// [1] =  Set to 1 to enable P-Channel Vth reading
	/// [2] =  Set to 1 to enable N-Channel Vth reading
	/// To start DPM detection, set CS CSR58[15] to 1
			const T_REG_INFO_EX& dpmdettasksel();	//CSR26[2:0]

	/// Comparator (in ClockSlice) reference mode select. Also see related register CS CSR7 COMPPWRDB )
	/// 0 =  Comparator operation is single-ended.  The input selected by CS CSR27 COMPCALMUXCTRL=2'b11 is compared against reference voltage set by CS CSR27 COMPVREFSEL 
	/// 1 = Comparator operation is differential.  The inputs selected by CS CSR27 COMPCALMUXCTRL
			const T_REG_INFO_EX& compmodesel();	//CSR27[15:15]

	/// Comparator input signal select:
	/// x00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// x01 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// x10 = Disabled/High Impedance (NO INPUT SELECTED)
	/// x11 = clockslice atb bus, sigle ended (Refer to related register CSATBTOPSEL )
			const T_REG_INFO_EX& compcalmuxctrl();	//CSR27[14:12]

	/// Comparator Vref generator select bits : 
	/// Setting = 400mV + (6.25mV x  COMPVREFSEL)                                    
	/// 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
			const T_REG_INFO_EX& compvrefsel();	//CSR27[11:6]

	/// Offset override voltage, to be changed before starting vrefgen cal.
	/// 0: VREFGENOFFSET will be updated with calibrated offset after vrefgen cal
	/// 1: VREFGENOFFSET will not be updated with calibrated offset after vrefgen cal
			const T_REG_INFO_EX& overrideoffset();	//CSR27[5:5]

	/// Depending on the sign bit VREFGENOFFSET[4] polarity (0 or 1), the common Vrefgen calibrated offset correction will be added/subtracted to/from the target value of all voltage calibrations
			const T_REG_INFO_EX& vrefgenoffset();	//CSR27[4:0]

	/// TOP_FSM Bypass control
	/// 0 = TOP_FSM controls vco_top_fsm (v101 mode)
	/// 1 = vco_top_fsm is directly controlled by firmware (v100 mode).  TOP_FSM contol of vco_top_fsm is bypassed.
			const T_REG_INFO_EX& topvcofsmbypass();	//CSR28[15:15]

	/// Select which PLL's VCO to be calibrated by the automatic calibration FSM.
	/// 0 = Select PLL0
	/// 1 = Select PLL1
			const T_REG_INFO_EX& lcvcocalsel();	//CSR28[14:14]

	/// Choose calibrate procedure in automatic calibration mode, i.e., when LCVCOCALMODE is set to 0.
	/// 00 = 2-pass calibration
	/// 01 = 1-pass calibration (both voltage and frequency)
	/// 10 = 1-pass calibration (voltage only)
	/// 11 = 1-pass calibration (frequency only)
			const T_REG_INFO_EX& lcvcocalctrl();	//CSR28[13:12]

	/// PLL0 Power Sequence Done Status bit
	/// New in V101
			const T_REG_INFO_EX& cspll0pwrseqdone();	//CSR28[11:11]

	/// PLL1 Power Sequence Done Status bit
	/// New in V101
			const T_REG_INFO_EX& cspll1pwrseqdone();	//CSR28[10:10]

	/// Power sequence FSM clear 
	/// New in V101
			const T_REG_INFO_EX& cspwrseqfsmclr();	//CSR28[9:9]

	/// Firmware overwrite of Power up sequence (Do not use)
	/// New in V101: for special test purposes only
			const T_REG_INFO_EX& csfwoverwrite();	//CSR28[8:8]

	/// CSR CS CAL MODE bits are connected to MISC CAL FSM via CS_TOP_FSM, which allows MISC and VCO calibration tasks to be launched from alternate start bits. The mode selections are:
	///  00 = CSR propagation. To propagate CSR values to analog I/F on all signals intercepted by MISC CAL FSM and DPM Detection FSM (Vreg sel, atb,...)
	///  01 = MISC cal launched from misccalfsmastart
	///  10 = NOT to be used by FW/user
	///  11 = VCO cal launched from cs_calib_start
			const T_REG_INFO_EX& cscalmode();	//CSR28[7:6]

	/// select between the ADC (in ClockSlice) or Comparator (in ClockSlice) for CP Vref and Vreg calibration tasks
	/// 0= Comparator selected  
	/// 1=ADC selected
			const T_REG_INFO_EX& csadccompsel();	//CSR28[5:5]

	/// LCVCO calibrations completed. Latched until being read 
	/// 0 = LCVCO calibrations do not finish yet.
	/// 1 = LCVCO calibrations finish.
			const T_REG_INFO_EX& lcvcocaldone();	//CSR28[4:4]

	/// LCVCO calibrations didn't succeed. Latched until being read.
	/// 0 = LCVCO calibrations didn't complete successfully.
	/// 1 = LCVCO calibrations completed successfully.
			const T_REG_INFO_EX& lcvcocalerr();	//CSR28[3:3]

	/// Status of LCVCO calibrations. If LCVCO calibrations didn't succeed, this register gives the internals status and/or conditions of the calibration processes.
	/// Mapping TBD.
			const T_REG_INFO_EX& lcvcocalstatus();	//CSR28[2:0]

	/// atb_out2pin signal select : 
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = atbout_clockslice
	/// 010 = atbout_auxclockslice
	/// 011 = atbout_serviceslice
	/// 100 = atbout_dataslice
	/// other settings =  High Impedance
			const T_REG_INFO_EX& atbfinalsel();	//CSR29[15:13]

	/// clockslice atb bus select : 
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  biascmu atb bus 
	/// 010 =  pll0 atb bus
	/// 011 =  pll1 atb bus
	/// 100 =  service slice atb bus
	/// 101 =  dataslice atb bus
	/// 110 =  mos detector osc atb out
	/// 111 =  low offset comparator
			const T_REG_INFO_EX& csatbtopsel();	//CSR29[12:10]

	/// Reserved fields. Analog pins don't exist
			const T_REG_INFO_EX& csatbspare();	//CSR29[9:6]

	/// bias atb bus select :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 to 101 =  do not use
	/// 110 =  icvp 50u
	/// 111 =  iccp 50u
			const T_REG_INFO_EX& biasatbsel();	//CSR29[5:3]

	/// Comparator ATB bus select bits :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  Internal node vcmref is selected (vref to latch comparator)
	/// 010 =  Internal node vout_opamp is selected (positive di to latch comparator
	/// 011 =  Internal node vref is selected (reference voltage for comparator)
	/// 100 =  Internal node vp1 is selected (positive input of comparator)
	/// 101 =  Internal node vm1 is selected (negative input of comparator)
	/// 110 =  no input selected
	/// 111 =  no input selected
			const T_REG_INFO_EX& compatbctrl();	//CSR29[2:0]

	/// PLL0 atb bus select :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  pll0_regulator atb bus
	/// 010 =  no input selected
	/// 011 =  pll0 dlf atb bus
	/// 100 =  pll0 vco atb bus
	/// 101 =  no input selected
	/// 110 =  pll0 hsclk distribution atb bus
	/// 111 =  pll0 vco to adc test signal
			const T_REG_INFO_EX& pll0atbplltopsel();	//CSR30[15:13]

	/// PLL0 dlf atb bus select : 
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  vcmf_i
	/// 010 =  vcmfctrl_o
	/// 011 =  vref_0p525_io
	/// 100 =  pbiastop
	/// 101 =  pbiasbot
	/// 110 =  sampp_o
	/// 111 =  sampm_o
			const T_REG_INFO_EX& pll0atbpllctrl();	//CSR30[10:8]

	/// PLL0 vco atb bus select
	/// 00 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 =  lvcc_vcocore_atb
	/// 10 =  vref_atb
	/// 11 =  no input selected
			const T_REG_INFO_EX& pll0atbvcoctrl();	//CSR30[6:5]

	/// pll0 vco2adc atb bus select
	/// 00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 =  lvcc_vcocore_half
	/// 10 =   vcotunep_add    
	/// 11 =   vcotunem_add
			const T_REG_INFO_EX& pll0adcvcoctrl();	//CSR30[4:3]

	/// PLL0 Digital test bus output
			const T_REG_INFO_EX& pll0dtbout();	//CSR30[0:0]

	/// PLL0 regulator atb bus select :
	/// 000 = High Impedance (NO INPUT SELECTED)
	/// 001 =  pll regulator atb bus
	/// 010 =  dlf regulator atb bus
	/// 011 =  vcodiv regulator atb bus
	/// 100 =  High Impedance
	/// 101 to 111 = High Impedance
			const T_REG_INFO_EX& pll0atbvregsel();	//CSR31[14:12]

	/// PLL0 pll regulator atb bus select :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  vref
	/// 010 =  lbias/vbeos
	/// 011 =  High Impedance
	/// 100 =  High Impedance
	/// 101 =  vmid
	/// 110 =  vreg_half  
	/// 111 =  High Impedance
			const T_REG_INFO_EX& pll0atbvregpllctrl();	//CSR31[11:9]

	/// PLL0 dlf regulator atb bus select :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  vref
	/// 010 =  lbias/vbeos
	/// 011 =  High Impedance
	/// 100 =  High Impedance
	/// 101 =  vmid
	/// 110 =  vreg_half  
	/// 111 =  High Impedance
			const T_REG_INFO_EX& pll0atbvregdlfctrl();	//CSR31[8:6]

	/// PLL0 vcodiv regulator atb bus select : 
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  vref
	/// 010 =  lbias/vbeos
	/// 011 =  High Impedance
	/// 100 =  High Impedance
	/// 101 =  vmid
	/// 110 =  vreg_half  
	/// 111 =  High Impedance
			const T_REG_INFO_EX& pll0atbvregvcodivctrl();	//CSR31[2:0]

	/// PLL1 atb bus select :
	/// 000 =    Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  pll1_regulator atb bus     
	/// 010 =  no connection                 
	/// 011 =  pll1 dlf atb bus
	/// 100 =  pll1 vco atb bus
	/// 101 =  no connection
	/// 110 =  pll1 hsclk distribution atb bus
	/// 111 =  pll1 vco to adc test signal
			const T_REG_INFO_EX& pll1atbplltopsel();	//CSR32[15:13]

	/// PLL1 dlf atb bus select :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  vcmf_i
	/// 010 =  vcmfctrl_o
	/// 011 =  vref_0p525_io
	/// 100 =  pbiastop
	/// 101 =  pbiasbot
	/// 110 =  sampp_o
	/// 111 =  sampm_o
			const T_REG_INFO_EX& pll1atbpllctrl();	//CSR32[10:8]

	/// PLL1 vco atb bus select
	/// 00 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 =  lvcc_vcocore_atb
	/// 10 =  vref_atb
	/// 11 =  no input selected
			const T_REG_INFO_EX& pll1atbvcoctrl();	//CSR32[6:5]

	/// PLL1 vco2adc atb bus select
	/// 00 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 =  lvcc_vcocore_half
	/// 10 =  vcotunep_add
	/// 11 =  vcotunem_add
			const T_REG_INFO_EX& pll1adcvcoctrl();	//CSR32[4:3]

	/// PLL1 digital test bus output
			const T_REG_INFO_EX& pll1dtbout();	//CSR32[0:0]

	/// pll1 regulator atb bus select :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED) 
	/// 001 =  pll regulator atb bus
	/// 010 =  dlf regulator atb bus
	/// 011 =  vcodiv regulator atb bus
	/// 100 to 111 =  High Impedance
			const T_REG_INFO_EX& pll1atbvregsel();	//CSR33[14:12]

	/// pll1 pll regulator atb bus select :  
	/// 000 =    High Impedance (NO INPUT SELECTED)
	/// 001 =  vref
	/// 010 =  lbias/vbeos
	/// 011 =  High Impedance
	/// 100 =  High Impedance
	/// 101 =  vmid
	/// 110 =  vreg_half 
	/// 111 =  High Impedance
			const T_REG_INFO_EX& pll1atbvregpllctrl();	//CSR33[11:9]

	/// pll1 dlf regulator atb bus select :  
	/// 000 =    High Impedance (NO INPUT SELECTED)
	/// 001 =  vref
	/// 010 =  lbias/vbeos
	/// 011 =  High Impedance
	/// 100 =  High Impedance
	/// 101 =  vmid
	/// 110 =  vreg_half  
	/// 111 =  High Impedance
			const T_REG_INFO_EX& pll1atbvregdlfctrl();	//CSR33[8:6]

	/// pll1 vcodiv regulator atb bus select : 
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  vref
	/// 010 =  lbias/vbeos
	/// 011 =  High Impedance
	/// 100 =  High Impedance
	/// 101 =  vmid
	/// 110 =  vreg_half
	/// 111 =  High Impedance
			const T_REG_INFO_EX& pll1atbvregvcodivctrl();	//CSR33[2:0]

	/// Serviceslice (SS) power down control. Active low.
	/// 0 = Power down the serviceslice
	/// 1 = Power up the serviceslice
			const T_REG_INFO_EX& sspwrdb();	//CSR34[15:15]

	/// SS refclk0 receiver power down, active low
	/// 0 = power down
	/// 1= power up
			const T_REG_INFO_EX& ssrefclk0pwrdb();	//CSR34[14:14]

	/// SS refclk1 receiver power down, active low
	/// 0 = power down
	/// 1= power up
			const T_REG_INFO_EX& ssrefclk1pwrdb();	//CSR34[13:13]

	/// SS refclk0 CML divider power down, active low
	/// 0 = power down
	/// 1= power up
			const T_REG_INFO_EX& ssrefclk0cmldivpwrdb();	//CSR34[12:12]

	/// SS refclk1 CML divider power down, active low
	/// 0 = power down
	/// 1= power up
			const T_REG_INFO_EX& ssrefclk1cmldivpwrdb();	//CSR34[11:11]

	/// SS refclk0 divider ratio select (Refer to fig.4 in the HiLink30_datasheet)
	/// 0 = div1
	/// 1 = div2
	/// Only applicable when there is a serviceslice in the macro.
			const T_REG_INFO_EX& ssrefclk0div2sel();	//CSR34[10:10]

	/// SS refclk1 divider ratio select (Refer to fig.4 in the HiLink30_datasheet)
	/// 0 = div1
	/// 1 = div2
	/// Only applicable when there is a serviceslice in the macro.
			const T_REG_INFO_EX& ssrefclk1div2sel();	//CSR34[9:9]

	/// Select the refclk bus 1's source. Only applicable when there is a serviceslice applicable.
	/// 0 = Choose the reference clock 1 from the bump as the refclk bus 1's source.
	/// 1 = tied low  .  Not available.   [Choose a CMOS reference clock from the core as the refclk bus 1's source] Applicable only when the CMOS reference clock is available to HiLink.
	/// Note: If the CMOS reference clock is not available to HiLink, this bit should be set to 0.
			const T_REG_INFO_EX& sscmosrefclksel();	//CSR34[8:8]

	/// SS refclk0 buffer bias control 
	/// 00 = xx uA
	/// 01 = 
	/// 10 = 
	/// 11 = yy uA
			const T_REG_INFO_EX& ssrefclk0biasctrl();	//CSR34[7:6]

	/// SS refclk1 buffer bias control 
	/// 00 = xx uA
	/// 01 = 
	/// 10 = 
	/// 11 = yy uA
			const T_REG_INFO_EX& ssrefclk1biasctrl();	//CSR34[5:4]

	/// SS refclk0 distribution buffer bias control 
	/// 00 = xx uA
	/// 01 = 
	/// 10 = 
	/// 11 = yy uA
			const T_REG_INFO_EX& ssrefclk0distbiasctrl();	//CSR34[3:2]

	/// SS refclk1 distribution buffer bias control signal
	/// 00 = xx uA
	/// 01 = 
	/// 10 = 
	/// 11 = yy uA
			const T_REG_INFO_EX& ssrefclk1distbiasctrl();	//CSR34[1:0]

	/// Powers down the bias icv. Active low
	/// 0 =  Power down  
	/// 1 =  Power up
			const T_REG_INFO_EX& biasmstricvpwrdb();	//CSR35[9:9]

	/// Powers down the bias icc. Active low
	/// 0 =  Power down  
	/// 1 =  Power up
			const T_REG_INFO_EX& biasmstriccpwrdb();	//CSR35[8:8]

	/// Powers down the bias iptat. Active low
	/// 0 =  Power down  
	/// 1 =  Power up
			const T_REG_INFO_EX& biasmstriptatpwrdb();	//CSR35[7:7]

	/// Vbg Power down. Active low.
	/// 0 =  Power down  
	/// 1 =  Power up
			const T_REG_INFO_EX& vbgpwrdb();	//CSR35[6:6]

	/// Vptat Power down. Active low.
	/// 0 =  Power down  
	/// 1 =  Power up
			const T_REG_INFO_EX& vptatpwrdb();	//CSR35[5:5]

	/// ADC (in ServiceSlice) and temperature sensor powerdown
	/// 0 =  Power down  
	/// 1 =  Power up
			const T_REG_INFO_EX& ssadcpwrdb();	//CSR35[4:4]

	/// Comparator (in ServiceSlice) power down :
	/// 0 =  Power down  
	/// 1 =  Power up
			const T_REG_INFO_EX& sscomppwrdb();	//CSR35[3:3]

	/// Comparator vref resistor ladder generator power down = 
	/// 0 =  Resistor ladder will output 0V at the output
	/// 1 =  Resistor ladder is active, with an output given by the ladder control bits
			const T_REG_INFO_EX& sscompvrefpwrdb();	//CSR35[2:2]

	/// not used
			const T_REG_INFO_EX& mosdetidacpwrdb();	//CSR35[1:1]

	/// Repurposed: CS DPM detector power down
	/// 0 = power down 
	/// 1 = power up
			const T_REG_INFO_EX& mosdetcml2cmospwrdb();	//CSR35[0:0]

	/// Test mode control. Active high
	/// 0 =  mission mode  
	/// 1 =  Test mode is active  which will output LVCC divided-down to 600mV. Over-rides bias  master opamp output.
			const T_REG_INFO_EX& bg600mvlvccresdiv();	//CSR36[15:15]

	/// hv_vref_bg source select:
	/// 0 =  bg buffer opamp is configured in one stage output mode. (High impedance) 
	/// 
	/// 1 =  bg buffer opamp is configured in two-stage output mode (low impedance)
			const T_REG_INFO_EX& bgbufsel();	//CSR36[14:14]

	/// calibration enable signal, Active high
	/// 0 =mission mode
	/// 1 = calibration mode
			const T_REG_INFO_EX& bgbufcalen();	//CSR36[13:13]

	/// BG buffer offset.
	/// 0 0000 = most negative offset
	/// ..
	/// ..
	/// ..
	/// 0 1111 = zero offset
	/// 1 0000 = zero offset 
	/// ..
	/// ..
	/// ..
	/// 1 1111 = most positive offset
			const T_REG_INFO_EX& bgbufofst();	//CSR36[12:8]

	/// Control signal setting Circuit configuration
	/// [1:0] = 00 no effect
	/// [1:0]= 01 Bias for Service Slice refclk is derived from CC current source 
	/// [1:0]= 10 Bias for Service Slice refclk is derived from   the di pin hv_vbg_ptat_in
	/// [1:0]= 11 Bias for Service Slice refclk is derived from  the di pin hv_vbg_cc_in
	/// [3:2] = 00 no effect
	/// [3:2]= 01 CV bias transmitter output value is derived from lvcc
	/// [3:2]= 10 CV bias transmitter output value is derived from the di pin hv_vbg_cc_in
	/// [3:2]= 11 CV bias transmitter output value is derived from the di pin hv_vbg_ptat_in
	/// [5:4] = 00 no effect
	/// [5:4]= 01 PTAT bias transmitter output value is derived from lvcc
	/// [5:4]= 10 PTAT bias transmitter output value is derived from the di pin hv_vbg_cc_in
	/// [5:4]= 11 PTAT bias transmitter output value is derived from the di pin hv_vbg_ptat_in
	/// [7:6] = 00 no effect
	/// [7:6]= 01 CC bias transmitter output value is derived from lvcc
	/// [7:6]= 10 CC bias transmitter output value is derived from the di pin hv_vbg_cc_in
	/// [7:6]= 11 CC bias transmitter output value is derived from the di pin hv_vbg_ptat_in
			const T_REG_INFO_EX& bgbypass();	//CSR36[7:0]

	/// Offset calibration output
			const T_REG_INFO_EX& bgbufcaltrig();	//CSR37[15:15]

	/// Reset internal DFF in the VBG block  (Band Gap reference voltage generator)  Assert the signal low to  disable the chopper circuit clock.  
	/// 0 = disable chopping
	/// 1 = enable chopping
			const T_REG_INFO_EX& vbgrstb();	//CSR37[14:14]

	/// Bypass BG/PTAT, generating BG/PTAT from hvcc. Active low
			const T_REG_INFO_EX& vbgbypassb();	//CSR37[13:13]

	/// BG/PTAT mode selection.
	/// 0 =  BG mode
	/// 1 =  PTAT mode;
			const T_REG_INFO_EX& vbgmode();	//CSR37[12:12]

	/// Chopping clock mode selection.
	/// 0 =   2MHz
	/// 1 =   4MHz;
			const T_REG_INFO_EX& vbgchopclkmode();	//CSR37[11:11]

	/// VBG DEM (Dynamic element matching) clock  selection.
	/// 0 =   2MHz.
	/// 1 =   4MHz;
			const T_REG_INFO_EX& vbgdemclkmode();	//CSR37[10:10]

	/// Enable Chopping clock. Active high
			const T_REG_INFO_EX& vbgenchop();	//CSR37[8:8]

	/// Enable DEM clock. Active high
			const T_REG_INFO_EX& vbgendem();	//CSR37[7:7]

	/// Selects bandgap voltage output value according to the following ; 
	/// 000 =   769mV; 
	/// 001 =   780mV; 
	/// 010 =   791mV; 
	/// 011 =   802mV; 
	/// 100 =   814mV; 
	/// 101 =   825mV; 
	/// 110 =   837mV; 
	/// 111 =   848mV
			const T_REG_INFO_EX& vbgreflvl();	//CSR37[2:0]

	/// Resets internal DFF in the VPTAT block (used to generate  current Proportional To Absolute Temperature).  Assert the signal low to disable  the chopper circuit.
	/// 0 = disable chopper
	/// 1 = enable chopper
			const T_REG_INFO_EX& vptatrstb();	//CSR38[14:14]

	/// Bypass BG/PTAT, generating BG/PTAT from hvcc. Active low
			const T_REG_INFO_EX& vptatbypassb();	//CSR38[13:13]

	/// BG/PTAT mode selection.
	/// 0 =  BG mode
	/// 1 =   PTAT mode;
			const T_REG_INFO_EX& vptatmode();	//CSR38[12:12]

	/// Chopping clock mode selection.
	/// 0 =   2MHz.
	/// 1 =   4MHz;
			const T_REG_INFO_EX& vptatchopclkmode();	//CSR38[11:11]

	/// VPTAT  DEM (Dynamic element matching) clock  selection.
	/// 0 =   2MHz.
	/// 1 =   4MHz
			const T_REG_INFO_EX& vptatdemclkmode();	//CSR38[10:10]

	/// Enable VPTAT block Chopping clock. Active high
	/// 0 = disable
	/// 1 = enable
			const T_REG_INFO_EX& vptatenchop();	//CSR38[8:8]

	/// Enable VPTAT DEM clock. Active high
	/// 0 = disable
	/// 1 = enable
			const T_REG_INFO_EX& vptatendem();	//CSR38[7:7]

	/// Selects ptat voltage output value according to the following ; 
	/// 000 =   769mV; 
	/// 001 =   780mV; 
	/// 010 =   791mV; 
	/// 011 =   802mV; 
	/// 100 =   814mV; 
	/// 101 =   825mV; 
	/// 110 =   837mV; 
	/// 111 =   848mV
			const T_REG_INFO_EX& vptatreflvl();	//CSR38[2:0]

	/// ADC (in Service Slice) reset enable
	/// 0 =  Reset enabled
	/// 1 =  Reset disabled
	/// Default as requested by Digital Design
			const T_REG_INFO_EX& ssadcrstb();	//CSR39[15:15]

	/// ADC (in Service Slice) reference selector:
	/// 0 =  HVCC is the reference
	/// 1 =  vref_bg (bandgap voltage 800mV) is the reference
			const T_REG_INFO_EX& ssadcabsmeasen();	//CSR39[14:14]

	/// ADC (in Service Slice) input voltage selector
	/// [SSADCTSTEN=1 and TSENSOREN=X]: Internal vcm_buff voltage is selected
	/// [SSADCTSTEN=0 and  TSENSOREN=0]: External voltage from ATB bus is selected
	/// [SSADCTSTEN=0 and  TSENSOREN=1]: temperature sensor  is selected
			const T_REG_INFO_EX& ssadctsten();	//CSR39[13:13]

	/// ADC (in Service Slice) common mode control signal
	/// 00 = 500 mV
	/// 01 = 550 mV
	/// 10 = 600 mV
	/// 11 = 650 mV
			const T_REG_INFO_EX& ssadcvcmctrl();	//CSR39[12:11]

	/// ADC (in Service Slice) input selector bits :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  Vth detector Vgsp is selected
	/// 010 =  Vth detector Vgsn is selected
	/// 011 =  hvcc_div internal signal is selected
	/// 100 =  lvcc_div internal signal is selected
	/// 101 =  ss_atb_out internal signal selected
	/// 110 =  adc_tielo internal signal is selected
	/// 111 =  adc_tielo internal signal is selected
	/// hvcc_div and lvcc_div are derived from a resistor divider, which divides the voltage hvcc and lvcc by 2.
	/// ss_atb_out are derived from various muxed-in internal voltages from the Service Slice.
			const T_REG_INFO_EX& ssadcinputsel();	//CSR39[10:8]

	/// Temperature sensor ADC enable
	/// 1 =  Temperature sensor output is selected
	/// 0 =  Temperature sensor output is disabled
	/// When enabled (logic 1), the two other dis selected by ss_adc_tst_enb are disabled.
			const T_REG_INFO_EX& tsensoren();	//CSR39[7:7]

	/// Temp Sensor coding for DataSlice temp detection. These bits are set in the ClockSlice digital engine and are based on the 10-bit temp measurement word:
	/// 000 = temp is in the range  [-40 to 20] �C
	/// 001 = temp is in the range  [-20 to 0] �C
	/// 010 = temp is in the range  [0 to 20] �C
	/// 011 = temp is in the range  [20 to 40] �C
	/// 100 = temp is in the range  [40 to 60] �C
	/// 101  = temp is in the range [60 to 80] �C
	/// 110 = temp is in the range  [80 to 100] �C
	/// 111 = temp is in the range  [100 to 125] �C
			const T_REG_INFO_EX& tsensorcstemp();	//CSR39[6:4]

	/// Comparator (in Service Slice) reference mode select. [Also see related register CS CSR35 SSCOMPPWRDB]
	/// 0 = Comparator operation is single-ended.  The input selected by CSR40 SSCOMPVINPSEL is compared against reference voltage set by  CS CSR40 SSCOMPVREFSEL
	/// 1 = Comparator operation is differential.  The inputs selected by CS CSR40 SSCOMPVINPSEL and SSCOMPVINMSEL are compared
			const T_REG_INFO_EX& sscompmodesel();	//CSR40[15:15]

	/// Select bits for the Vinm  input to the high precision comparator (in Service Slice).  [Also see related register CS CSR44 RPOLYDETCALSEL before selection]
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  rx_termcal_otbm di selected (used to calibrate the Poly resistor).
	/// 010 =  rpolydet_otbm_up di selected (used for process detection)
	/// 011 =  rpolydet_otbm_dn di selected (used for process detection)
	/// 100 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// ..
	/// 111 =  High Impedance
			const T_REG_INFO_EX& sscompvinmsel();	//CSR40[14:12]

	/// Select bits for the Vinp input to the high precision comparator (in Service Slice) . [Also see related register CS CSR44 RPOLYDETCALSEL before selection]
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  rx_termcal_otbp di selected (used to calibrate the Poly resistor). 
	/// 010 =  rpolydet_otbc di selected (used for process detection)
	/// 011 =  comp_tielo di selected (output should go low)
	/// 100 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// ..
	/// 111 =  High Impedance
			const T_REG_INFO_EX& sscompvinpsel();	//CSR40[11:9]

	/// Comparator (in Service Slice) Vref generator select bits =  [Also see related register CS CSR35 SSCOMPVREFPWRDB before selection]
	/// Setting = 400mV + (6.25mV x  SSCOMPVREFSEL)                                                                                                                                                                                         000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 111111 =  Vref=793.75mV
			const T_REG_INFO_EX& sscompvrefsel();	//CSR40[8:3]

	/// Output of serviceslice's comparator.
			const T_REG_INFO_EX& sscompstatus();	//CSR40[0:0]

	/// Process detector enable (uses threshold voltage Vth of MOS transistor to classify process corners). [Also see related register CS CSR39 SSADCINPUTSEL]
	/// 0 =  Vth process detector is disabled
	/// 1 =  Vth process detector is enabled
			const T_REG_INFO_EX& mosdeten();	//CSR41[15:15]

	/// Selects between high voltage or core MOS transistors to detect its threshold voltage (Vth).  [Also see related register CS CSR41 MOSDETEN before selection]
	/// 0 =  Core transistor selected(uLVT)
	/// 1 =  High Voltage transistor selected(SVT)
			const T_REG_INFO_EX& mosdetmostypesel();	//CSR41[14:14]

	/// not used
			const T_REG_INFO_EX& mosdetvcocalen();	//CSR41[13:13]

	/// not used
			const T_REG_INFO_EX& mosdetioscptune();	//CSR41[12:10]

	/// not used
			const T_REG_INFO_EX& mosdetioscdacofst();	//CSR41[9:8]

	/// not used
			const T_REG_INFO_EX& mosdetioscdaccal();	//CSR41[7:0]

	/// Repurposed mosdet_psel[2] : Not implemented 
	/// bit[2]:
	/// 0 = Bias receiver opamp is in h30 mode (vss IR cancellation mode)
	/// 1= Bias receiver opamp is in h28/legacy mode (no VSS IR cancellation) (default)
	/// 
	/// bits[1:0] : not used
			const T_REG_INFO_EX& mosdetpsel();	//CSR42[15:13]

	/// not used
			const T_REG_INFO_EX& mosdets1sel();	//CSR42[12:10]

	/// not used
			const T_REG_INFO_EX& mosdets2sel();	//CSR42[9:8]

	/// not used
			const T_REG_INFO_EX& mosdetiosccrosstune();	//CSR42[7:7]

	/// not used
			const T_REG_INFO_EX& mosdetoscdiv();	//CSR42[1:0]

	/// Process corner code for the Nch transistor decoded in the ClockSlice  based on its threshold voltage measured.  This code is sent  to the Service Slice to be distributed to all the Dataslices.  Applies to macro with ServiceSlice ONLY  [See also related register CS CSR56 DPMNMOSCNR]
	/// 000 =  -3 sigma Vth Nch fast corner
	/// 001 =  -2 sigma Vth Nch fast corner
	/// 010 =  -1 sigma Vth Nch fast corner
	/// 011 =  Typ Vth Nch corner
	/// 100 =  +1 sigma Vth Nch slow corner
	/// 101 =  +2 sigma Vth Nch slow corner
	/// 110 =  +3 sigma Vth Nch slow corner
	/// 111 =  not used
			const T_REG_INFO_EX& mosdetcsnmoscnr();	//CSR43[15:13]

	/// Process corner code for the Pch transistor decoded in the ClockSlice  based on its threshold voltage measured.  This code is sent  to the Service Slice to be distributed to all the Dataslices.  Applies to macro with ServiceSlice ONLY  [See also related register CS CSR56 DPMPMOSCNR]
	/// 000 =  -3 sigma Vth Pch fast corner
	/// 001 =  -2 sigma Vth Pch fast corner
	/// 010 =  -1 sigma Vth Pch fast corner
	/// 011 =  Typ Vth Pch corner
	/// 100 =  +1 sigma Vth Pch slow corner
	/// 101 =  +2 sigma Vth Pch slow corner
	/// 110 =  +3 sigma Vth Pch slow corner
	/// 111 =  not used
			const T_REG_INFO_EX& mosdetcspmoscnr();	//CSR43[12:10]

	/// CMOS Process corner code based on ILO (injection locking Oscillator) frequency measured.  This code is sent  to the Service Slice to be distributed to all the Dataslices.  Limitation =  cannot detect FS and SF corners.   Applies to macro with ServiceSlice ONLY  [See also related register CS CSR56 DPMCMOSCNR]
	/// 000 =  -3 sigma Vth CMOS fast corner
	/// 001 =  -2 sigma Vth CMOS fast corner
	/// 010 =  -1 sigma Vth CMOS fast corner
	/// 011 =  Typ Vth CMOS corner
	/// 100 =  +1 sigma Vth CMOS slow corner
	/// 101 =  +2 sigma Vth CMOS slow corner
	/// 110 =  +3 sigma Vth CMOS slow corner
	/// 111 =  not used
			const T_REG_INFO_EX& mosdetcscmoscnr();	//CSR43[9:7]

	/// Clock divider for Chopping circuit of DEM clk
	/// bits[6:1] :  pre div ratio (specify N-1)
	/// bit[0] : 0 = div by 2 ; 1 = div by 4
	/// [For refclk freq of 156.25Mhz, the default value of 0x13 will divide the refclk by 10x4 = 40 to generate 3.9MHz clock]
			const T_REG_INFO_EX& sschopdemclkdiv();	//CSR43[6:0]

	/// Rpoly calibration/detection select bit:
	/// 0 = Output calibration voltages (otbp, otbm, otbc, otbm_up and otbm_dn) are tri-stated. 
	/// 1 = Output calibration voltages (otbp, otbm, otbc, otbm_up and otbm_dn) are made available and calibration/detection may start.
			const T_REG_INFO_EX& rpolydetcalsel();	//CSR44[15:15]

	/// Termination resistor calibration enable:
	/// 0 = Calibration is disabled
	/// 1 =  Calibration is enabled
			const T_REG_INFO_EX& rpolydethvrxtermcalen();	//CSR44[14:14]

	/// Termination replica resistor calibration bits : 
	/// 0000 =  Termination replica is open
	/// 0001 =  Highest resistance value 
	/// ....
	/// 1111 =  Lowest resistance value
			const T_REG_INFO_EX& rpolydetcsrxtermcal();	//CSR44[13:10]

	/// Rpoly (poly-silicon Resistor) process corner code based on  its measured characteristics.  This code is sent  to the Service Slice to be distributed to all the Dataslices. Applies to macro with ServiceSlice ONLY  [See also related register CS CSR57 DPMRPOLYCNR].
	/// 00 = fast poly resistor 
	/// 01 = typical poly resistor
	/// 10 = slow poly resistor
	/// 11 = not used
			const T_REG_INFO_EX& rpolydetcsrpolycnr();	//CSR44[5:4]

	/// Service slice spare input bits for dpm.
			const T_REG_INFO_EX& ssdpmsparein();	//CSR44[3:0]

	/// Serviceslice spare bits.
			const T_REG_INFO_EX& ssspare();	//CSR45[15:0]

	/// SS atb (Service slice Test bus) bus control signal : 
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED) 
	/// 001 =  refclk receiver atb output
	/// 010 = bias master atb output
	/// 011 = dpm atb output
	/// 1xx = High Impedance
			const T_REG_INFO_EX& ssatbsel();	//CSR46[14:12]

	/// refclk receiver atb bus control signal :
	/// 000000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// xx0101 =  refclk0 receiver buffer bias voltage
	/// 01xx10 = refclk1 receiver buffer bias voltage
	/// other setting =  not allowed
			const T_REG_INFO_EX& refclkreceiveratbsel();	//CSR46[11:6]

	/// bias master atb control signal bits 5 to 3 :
	/// 000000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001xxx =  Selects bandgap related output from selection of  bits 2 to 0 (below)
	/// 010000 =  icvp_50u; 
	/// 011000 =  iptat_50u
	/// 100000 =  iccp_50u; 
	/// 101000 =  High Impedance
	/// 110000 =  hv_vref_bg 
	/// ;111000 =  High impedance
	/// 
	/// bits 2 to 0  (Band gap related)
	/// 001000  =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001001  =  iptat_10u
	/// 001010  =  ibg_10u
	/// 001011  =  vptat_inp
	/// 001100  =  vptat_inn; 
	/// 001101  =  vbg_inp
	/// 001110  =  vbg_inn
	/// ;001111  =  vbg_nstrt
			const T_REG_INFO_EX& biasmstratbsel();	//CSR46[5:0]

	/// ATB bus select bits for internal tsensor voltages
	/// 00 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 =  Internal Vbe voltage is selected
	/// 10 =  Internal sw cap voltage output is selected (output of temp sensor)
	/// 11 =  no input selected
			const T_REG_INFO_EX& tsensorhvatbsel();	//CSR47[12:11]

	/// Comparator (in Service Slice) ATB bus select bits :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  Internal node vcmref is selected (vref to latch comparator)
	/// 010 =  Internal node vout_opamp is selected (positive di to latch comparator
	/// 011 =  Internal node vref is selected (reference voltage for comparator)
	/// 100 =  Internal node vp1 is selected (positive input of comparator)
	/// 101 =  Internal node vm1 is selected (negative input of comparator)
	/// 110 =  no input selected
	/// 111 =  no input selected
			const T_REG_INFO_EX& sscompatbctrl();	//CSR47[10:8]

	/// Not used.
	/// TOP_FSM 2nd Pass Calibration Enable
	/// 0 =  disable TOP_FSM  2nd pass calibration
	/// 1 =  enable TOP_FSM   2nd pass calibration
			const T_REG_INFO_EX& topvcofsm2ndpassen();	//CSR47[5:5]

	/// TOP_FSM 1st Pass Itank calibration Bypass
	/// 0 =  TOP_FSM 1st pass includes itank calibration
	/// 1 =  TOP_FSM 1st pass itank calibration is bypassed
			const T_REG_INFO_EX& firstpassitankbypass();	//CSR47[4:4]

	/// Not used 
	/// When CS_TRANS_MAX_FREQCAL=4/8/16, fddiff_cnt is accumulated 2/4/8 times for each sign changed freqcal points or top edge freqcal point (f31) or bottom edge freqcal point (f0)  
	/// 0 =  summing mode
	/// 1 =  Average mode
			const T_REG_INFO_EX& fddiffavemodesel();	//CSR47[3:3]

	/// Freqcal Preference Select
	/// 0 =  select lower freqcal number
	/// 1 =  select higher freqcal number
			const T_REG_INFO_EX& freqcalprefsel();	//CSR47[2:2]

	/// Bandsel Preference Select
	/// 0 =  select lower bandsel number
	/// 1 =  select higher bandsel number
			const T_REG_INFO_EX& bandselprefsel();	//CSR47[1:1]

	/// Exit On Threshold (aka EOT) enable (also applicable in v100 mode)
	/// 0 = TOP_FSM continues to search for next freqcal point even if last freqcal point fd_diff_cnt is less than or eq to threshold
	/// 1 = enable TOP_FSM to exit when fd_diff less than or eq to threshold (2 points params will not be reported)
	/// 
	/// Re-purposed. Now used as bdsel force.
	/// 0 = bdsel force is OFF
	/// ;1 = bdsel force is ON.
	/// 
	/// When bdsel force is off, if two solutions (on two adjacent bands) or one solution and two edge points can be distinguished by their fd_diffs (i.e., the difference > 2) the solution with smaller fd_diff will be selected as the final solution; If not, then the solution on the lower band will be selected as the final solution if bdsel_pref is 0; Or, the solution on the higher band will be selected as the final solution if bdsel_pref is 1.
	/// 
	/// When bdsel force is ON, for the two solutions on two adjacent bands case, the solution on the higher band will be selected as the final solution; For the one solution and two edge points case, if any two can be distinguished by their fd_diffs (i.e., the difference > 2), between the solution and the edge point 1 (derived from the first run), the solution is always selected; between the solution and the edge point 2  (derived from the second run), the one which has a smaller fd_diff is selected. If any two cannot be distinguished by their fd_diffs (i.e., the difference > 2), always the one on the higher band is selected.
			const T_REG_INFO_EX& exitonthreshold();	//CSR47[0:0]

	/// DPM (Service Slice) ATB bus select bits :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  tielo is selected
	/// 010 =  Internal Vth detector mosdet_vgs (n/p) di is selected
	/// 011 =  Internal Poly resistor calibration/detection rpolydet_hvatb_output di is selected
	/// 100 =   Internal High-Pre comparator comp_atb_output is selected
	/// 101 =  Internal Temp sensor tsensor_hvatb_vbepnp di is selected
	/// 110-111 =  High Impedance
			const T_REG_INFO_EX& ssdpmatbsel();	//CSR48[15:13]

	/// Vth process detector atb control signal:
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = vgsn  (N-type transistor) selected 
	/// 010 = vgsp  (P-type transistor) selected
	/// 011 to 111 = High Impedance
	///  
	///  See MOSDETMOSTYPESEL to choose  uLVT or SVT transistor
			const T_REG_INFO_EX& mosdetvgsatbctrl();	//CSR48[8:6]

	/// ILO ATB bus control bits:
	/// 000: Disabled/High Impedance (NO INPUT SELECTED)
	/// 001: vgsn (N-type transistor) selected 
	/// 010: vgsp  (P-type transistor) selected
	/// 011 to 111: Disabled/High Impedance (NO INPUT SELECTED)
	/// 
	///  See MOSDETMOSTYPESEL to choose  uLVT or SVT transistor
			const T_REG_INFO_EX& mosdetoscatbctrl();	//CSR48[5:3]

	/// ATB bus selector, brings out internal voltages in the Rpoly detector/calibration for debug/testing purposes:
	/// 000: Disabled/High Impedance (NO INPUT SELECTED)
	/// 001: otbp output is selected
	/// 010: otbm output is selected
	/// 011: otbc output is selected
	/// 100: otbm_up output is selected
	/// 101: otbm_dn output is selected
	/// 110: internal indm voltage is selected
	/// 110: Disabled/High Impedance (NO INPUT SELECTED)
			const T_REG_INFO_EX& rpolydethvatbctrl();	//CSR48[2:0]

	/// Shared ADC/Comparator Pre Divider to generate 6.4MHz clock from lifeclk2dig to feed CSADCCLKDIV and CSCOMPCLKDIV  
	/// i.e,   6.4Mhz  = Lifeclk2dig  Mhz / (ADCCOMPCLKPREDIV + 1)
			const T_REG_INFO_EX& adccompclkprediv();	//CSR49[14:8]

	/// CS ADC Clock Frequency  selector (Input clock freq to the CS ADC Clock divider block should be  6.4Mhz set by  ADCCOMPCLKPREDIV)
	/// 000 =  25KHz 
	/// 001 =  50KHz
	/// 010 =  100KHz
	/// 011 =  200KHz
	/// 100 =  400KHz
	/// 101 =  800KHz
	/// 110 =  1.6MHz
	/// 111 =  3.2MHz
			const T_REG_INFO_EX& csadcclkdiv();	//CSR49[7:5]

	/// CS Comparator Clock  Frequency selector (Input clock freq to the CS Comparator Clock divider block should be 6.4Mhz set by  ADCCOMPCLKPREDIV) 
	/// 000 =  12.5KHz 
	/// 001 =  25KHz
	/// 010 =  50KHz
	/// 011 =  100KHz
	/// 100 =  200KHz
	/// 101 =  400KHz
	/// 110 =  800KHz
	/// 111 =  1.6MHz
			const T_REG_INFO_EX& cscompclkdiv();	//CSR49[4:2]

	/// CS DF DeadBand Select (each step ~ 6.25mV) : 
	/// 00 =  +/- 1 step
	/// 01 =  +/- 2 steps
	/// 10 =  +/- 3 steps
	/// 11 =  +/- 4 steps
			const T_REG_INFO_EX& csdfdeadbandsel();	//CSR49[1:0]

	/// CS Decimation Factor Select :
	/// 00 =  256
	/// 01 =  512
	/// 10 =  1024
	/// 11 =  2048
			const T_REG_INFO_EX& csdecmfactor();	//CSR50[15:14]

	/// CS ADC Conversion Mode:
	/// 0 = Single shot measurement 
	/// 1 = Continuous measurement
			const T_REG_INFO_EX& csadcconvmode();	//CSR50[13:13]

	/// CS Decimation Filter Order:
	/// 0 = Sync_1
	/// 1 = Sync_2
			const T_REG_INFO_EX& csdforder();	//CSR50[12:12]

	/// CS Decimation Filter Reference Code: The Decimator Data is compared against this Reference code at the end of each measurement
			const T_REG_INFO_EX& csdfrefcode();	//CSR50[11:0]

	/// CS Decimation Filter Ready: Set to 1 to indicate CSDFDATA and CSDFCOMPSTATUS are ready for reading
	/// - Single shot mode: set to 1 at the end of each cyle
	/// - Continuous mode: pulsing depend on CSADCCONVMODE[1]
			const T_REG_INFO_EX& csdfrdy();	//CSR51[15:15]

	/// CS Decimation Filter Compare Status :
	/// 0 =  CSDFDATA smaller than  CSDFREFCODE
	/// 1 =  CSDFDATA greater or equal CSDFREFCODE
			const T_REG_INFO_EX& csdfcompstatus();	//CSR51[14:14]

	/// CS Decimation Filter Compare Status DeadBand M :
	/// 0 =  CSDFDA greater or equal CSDFREFCODE - DeadBand
	/// 1 =  CSDFDATA smaller CSDFREFCODE - DeadBand
			const T_REG_INFO_EX& csdfcompstatusdbm();	//CSR51[13:13]

	/// CS Decimation Filter Compare Status DeadBand P : 
	/// 0 =  CSDFDA smaller or equal CSDFREFCODE + DeadBand
	/// 1 =  CSDFDATA greater CSDFREFCODE + DeadBand
			const T_REG_INFO_EX& csdfcompstatusdbp();	//CSR51[12:12]

	/// CS Decimation Filter Data
			const T_REG_INFO_EX& csdfdata();	//CSR51[11:0]

	/// CS DF Auto Timer Value (Timer is always on, ADC_CLK@3.2MHz)
	/// 00:   6 ADC clock cycles   (1.87us     @ 3.2MHz)
	/// 01: 70 ADC clock cycles   (21.87us  @ 3.2MHz)
	/// 10: 166 ADC clock cycles (51.87us  @ 3.2MHz)
	/// 11: 326 ADC clock cycles (101.87us@ 3.2MHz)
			const T_REG_INFO_EX& csdfautotimervalue();	//CSR52[11:10]

	/// SS DF Auto Timer Value (Timer is always on, ADC_CLK@400KHz)
	/// 00:   6 ADC clock cycles   (15us     @ 400KHz)
	/// 01: 70 ADC clock cycles   (175us  @ 400KHz)
	/// 10: 166 ADC clock cycles (415us  @ 400KHz)
	/// 11: 326 ADC clock cycles (815us@ 400KHz)
			const T_REG_INFO_EX& ssdfautotimervalue();	//CSR52[9:8]

	/// SS (Service Slice)  ADC Clock Divider :
	/// 000 =  25KHz 
	/// 001 =  50KHz
	/// 010 =  100KHz
	/// 011 =  200KHz
	/// 100 =  400KHz
	/// 101 =  800KHz
	/// 110 =  1.6MHz
	/// 111 =  3.2MHz
			const T_REG_INFO_EX& ssadcclkdiv();	//CSR52[7:5]

	/// SS Comparator Clock Divider :
	/// 000 =  12.5KHz 
	/// 001 =  25KHz
	/// 010 =  50KHz
	/// 011 =  100KHz
	/// 100 =  200KHz
	/// 101 =  400KHz
	/// 110 =  800KHz
	/// 111 =  1.6MHz
			const T_REG_INFO_EX& sscompclkdiv();	//CSR52[4:2]

	/// SS DF DeadBand Select (each step ~ 6.25mV) :
	/// 00 =  +/- 1 step
	/// 01 =  +/- 2 steps
	/// 10 =  +/- 3 steps
	/// 11 =  +/- 4 steps
			const T_REG_INFO_EX& ssdfdeadbandsel();	//CSR52[1:0]

	/// SS Decimation Factor Select :
	/// 00 =  256
	/// 01 =  512
	/// 10 =  1024
	/// 11 =  2048
			const T_REG_INFO_EX& ssdecmfactor();	//CSR53[15:14]

	/// SS ADC Conversion Mode :
	/// 0 =  Single shot measurement 
	/// 1 =  Continuous measurement
			const T_REG_INFO_EX& ssadcconvmode();	//CSR53[13:13]

	/// SS Decimation Filter Order :
	/// 0 =  Sync_1
	/// 1 =  Sync_2
			const T_REG_INFO_EX& ssdforder();	//CSR53[12:12]

	/// SS Decimation Filter Reference Code: The Decimator Data is compared against this Reference code at the end of each measurement
			const T_REG_INFO_EX& ssdfrefcode();	//CSR53[11:0]

	/// SS Decimation Filter Ready: Set to 1 to indicate SSDFDATA and SSDFCOMPSTATUS are ready for reading
	/// - Single shot mode: set to 1 at the end of each cyle
	/// - Continuous mode: pulsing depend on SSADCCONVMODE[1]
			const T_REG_INFO_EX& ssdfrdy();	//CSR54[15:15]

	/// SS Decimation Filter Compare Status :
	/// 0 =  SSDFDATA smaller than  SSDFREFCODE
	/// 1 =  SSDFDATA greater or equal SSDFREFCODE
			const T_REG_INFO_EX& ssdfcompstatus();	//CSR54[14:14]

	/// SS Decimation Filter Compare Status DeadBand M :
	/// 0 =  CSDFDATA  greater than or equal CSDFREFCODE - DeadBand
	/// 1 =  CSDFDATA   smaller than  CSDFREFCODE - DeadBand
			const T_REG_INFO_EX& ssdfcompstatusdbm();	//CSR54[13:13]

	/// SS Decimation Filter Compare Status DeadBand P : 
	/// 0 =  CSDFDATA  smaller than or equal CSDFREFCODE + DeadBand
	/// 1 =  CSDFDATA   greater than CSDFREFCODE + DeadBand
			const T_REG_INFO_EX& ssdfcompstatusdbp();	//CSR54[12:12]

	/// SS Decimation Filter Data
			const T_REG_INFO_EX& ssdfdata();	//CSR54[11:0]

	/// NOT USED IN V101
			const T_REG_INFO_EX& ringvcorefclkdiv();	//CSR55[15:8]

	/// NOT USED IN V101
			const T_REG_INFO_EX& ringvcofdclkdiv();	//CSR55[4:0]

	/// DPM (Process /temperature monitoring) nmos corner status code shared with all Dataslices for optimizing performance
	/// 000 =  -3  sigma  Vth Nch fast corner
	/// 001 =  -2 sigma Vth Nch fast corner
	/// 010 =  -1 sigma Vth Nch fast corner
	/// 011 =  Typ Vth Nch corner
	/// 100 =  +1 sigma Vth Nch slow corner
	/// 101 =  +2 sigma Vth Nch slow corner
	/// 110 =  +3 sigma Vth Nch slow corner
			const T_REG_INFO_EX& dpmnmoscnr();	//CSR56[15:13]

	/// DPM pmos corner status code shared with all Dataslices for optimizing performance
	/// 000 =  -3 sigma Vth Pch fast corner
	/// 001 =  -2 sigma Vth Pch fast corner
	/// 010 =  -1 sigma Vth Pch fast corner
	/// 011 =  Typ Vth Pch corner
	/// 100 =  +1 sigma Vth Pch slow corner
	/// 101 =  +2 sigma Vth Pch slow corner
	/// 110 =  +3 sigma Vth Pch slow corner
			const T_REG_INFO_EX& dpmpmoscnr();	//CSR56[12:10]

	/// DPM cmos corner status code shared with all Dataslices for optimizing performance
	/// 000 =  -3 sigma Vth CMOS fast corner
	/// 001 =  -2 sigma Vth CMOS fast corner
	/// 010 =  -1 sigma Vth CMOS fast corner
	/// 011 =  Typ Vth CMOS corner
	/// 100 =  +1 sigma Vth CMOS slow corner
	/// 101 =  +2 sigma Vth CMOS slow corner
	/// 110 =  +3 sigma Vth CMOS slow corner
			const T_REG_INFO_EX& dpmcmoscnr();	//CSR56[9:7]

	/// DPM temperature status code  shared with all Dataslices for optimizing performance
	/// 000 = temp is in the range  [-40 to 20] �C
	/// 001 = temp is in the range  [-20 to 0] �C
	/// 010 = temp is in the range  [0 to 20] �C
	/// 011 = temp is in the range  [20 to 40] �C
	/// 100 = temp is in the range  [40 to 60] �C
	/// 101  = temp is in the range [60 to 80] �C
	/// 110 = temp is in the range  [80 to 100] �C
	/// 111 = temp is in the range  [100 to 125] �C
			const T_REG_INFO_EX& dpmtemperature();	//CSR56[6:4]

	/// DPM Termination replica resistor calibration code shared with all Dataslices for optimizing performance
	/// 0000 =  Termination replica is open
	/// 0001 =  Highest resistance value 
	/// ..
	/// 1111 =  Lowest resistance value
			const T_REG_INFO_EX& dpmrxtermcal();	//CSR57[13:10]

	/// Clock slice spare output bits for dpm.
			const T_REG_INFO_EX& dpmspare();	//CSR57[9:6]

	/// DPM rpoly resistor corner status code shared with all Dataslices for optimizing performance
	/// 00 = Fast resistor process
	/// 01 = Typical resistor process
	/// 10 = Slow resistor process
			const T_REG_INFO_EX& dpmrpolycnr();	//CSR57[5:4]

	/// Service slice spare output bits for dpm.
			const T_REG_INFO_EX& ssdpmspareout();	//CSR57[3:0]

	/// Start Calibration / Finetune task from CS_TOP_FSM
			const T_REG_INFO_EX& cstopfsm_cal_start();	//CSR58[15:15]

	/// DPM Finetune Enable : 
	/// 0 =  To STOP Continuous DPM once started
	/// 1 =  To Enable Continuous DPM.
	/// This bit must be set together with CSR58[15, 12:3] to finetune all the voltage regulators and to capture PLL0LVCCVCOCORE / PLL1LVCCVCOCORE voltages as well as monitor Temperature
			const T_REG_INFO_EX& dpmfinetuneen();	//CSR58[14:14]

	/// CS_TOP_FSM Calibration Task Select.  Set the following bits to 1 to calibrate :
	/// [0] =  ADC Bandgap Voltage Cal  
	/// [1] =  CS Comparator Vrefgen Cal 
	/// [2] =  RXTERM Cal  
	/// [3] =  PLL0 DLF VREG Cal  
	/// [4] =  PLL0 PLL VREG Cal
	/// [5] =  PLL0 CP VREF Cal
	/// [6] =  PLL0 VCODIV VREG Cal
	/// [7] =  PLL1 DLF VREG Cal
	/// [8] =  PLL1 PLL VREG Cal
	/// [9] =   PLL1 CP VREF Cal
	/// [10] = PLL1 VCODIV VREG Cal
	/// [11] =  PLL0 VCO Cal
	/// [12] =  PLL1 VCO Cal
	/// [13] =  No Selection
			const T_REG_INFO_EX& cstopfsm_cal_task_sel();	//CSR58[13:0]

	/// CS_TOP_FSM Calibration Done.   set to 1 to indicate that all selected calibration tasks are completed
			const T_REG_INFO_EX& cstopfsm_cal_done();	//CSR59[15:15]

	/// DPM Finetune Ready (temprd, pll0lvccvcocore, pll1lvccvcocore being updated)
	/// Clear on Read
			const T_REG_INFO_EX& dpmfinetunerdy();	//CSR59[14:14]

	/// CS_TOP_FSM Calibration Task Status correspond to the  CSTOPFSM_CAL_TASK_SEL
	/// [0] =  ADC Bandgap Voltage Cal  
	/// [1] =  CS Comparator Vrefgen Cal 
	/// [2] =  RXTERM Cal  
	/// [3] =  PLL0 DLF VREG Cal  
	/// [4] =  PLL0 PLL VREG Cal
	/// [5] =  PLL0 CP VREF Cal
	/// [6] =  PLL0 VCODIV VREG Cal
	/// [7] =  PLL1 DLF VREG Cal
	/// [8] =  PLL1 PLL VREG Cal
	/// [9] =   PLL1 CP VREF Cal
	/// [10] = PLL1 VCODIV VREG Cal
	/// [11] =  PLL0 VCO Cal
	/// [12] =  PLL1 VCO Cal
	/// [13] =  Not used
			const T_REG_INFO_EX& cstopfsm_cal_task_status();	//CSR59[13:0]

	/// PLL0 VREG PLL Comparator Vref  select bits :
	/// Setting = 400mV + (6.25mV x PLL0VREGPLLCOMPVREF)  000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
			const T_REG_INFO_EX& pll0vregpllcompvref();	//CSR60[11:6]

	/// PLL1 VREG PLL Comparator Vref  select bits :
	/// Setting = 400mV + (6.25mV x PLL1VREGPLLCOMPVREF) 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
			const T_REG_INFO_EX& pll1vregpllcompvref();	//CSR60[5:0]

	/// PLL0 VREG DLF Comparator Vref  select bits :
	/// Setting = 400mV + (6.25mV x PLL0VREGDLFCOMPVREF) 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
			const T_REG_INFO_EX& pll0vregdlfcompvref();	//CSR61[11:6]

	/// PLL1 VREG DLF Comparator Vref  select bits :
	/// Setting = 400mV + (6.25mV x PLL1VREGDLFCOMPVREF) 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
			const T_REG_INFO_EX& pll1vregdlfcompvref();	//CSR61[5:0]

	/// PLL0 VREG VCODIV Comparator Vref  select bits :
	/// Setting = 400mV+ (6.25mV x PLL0VREGVCODIVCOMPVREF)   
	/// 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
			const T_REG_INFO_EX& pll0vregvcodivcompvref();	//CSR62[11:6]

	/// PLL1 VREG VCODIV Comparator Vref  select bits :
	/// Setting = 400mV+ (6.25mV x PLL1VREGVCODIVCOMPVREF)   
	/// 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
			const T_REG_INFO_EX& pll1vregvcodivcompvref();	//CSR62[5:0]

	/// PLL0 CP REF Comparator Vref  select bits :
	/// Setting = 400mV + (6.25mV x PLL0VREGCPVREFCOMPVREF)                                 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
			const T_REG_INFO_EX& pll0vregcpvrefcompvref();	//CSR63[11:6]

	/// PLL1 CP REF Comparator Vref  select bits :
	/// Setting = 400mV + (6.25mV PLL1VREGCPVREFCOMPVREF)                                000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
			const T_REG_INFO_EX& pll1vregcpvrefcompvref();	//CSR63[5:0]
			bool get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos);
	};
public:
	_REG_INFO REG_INFO;

	uint csr[CS_CLK_CSR_NUM];


	//CSR0[15:15]
	CS_clkRegs& setcspwrdb(uint val);
	uint getcspwrdb();

	//CSR0[14:14]
	CS_clkRegs& setpll0refclksel(uint val);
	uint getpll0refclksel();

	//CSR0[12:11]
	CS_clkRegs& setpll0vcodivna(uint val);
	uint getpll0vcodivna();

	//CSR0[10:9]
	CS_clkRegs& setpll0vcodivka(uint val);
	uint getpll0vcodivka();

	//CSR0[8:4]
	CS_clkRegs& setpll0fbdivp(uint val);
	uint getpll0fbdivp();

	//CSR0[3:0]
	CS_clkRegs& setpll0fbdivs(uint val);
	uint getpll0fbdivs();

	//CSR1[15:15]
	CS_clkRegs& setpll0hsclkdistpwrdb(uint val);
	uint getpll0hsclkdistpwrdb();

	//CSR1[14:14]
	CS_clkRegs& setpll0hsclkdivpwrdb(uint val);
	uint getpll0hsclkdivpwrdb();

	//CSR1[13:10]
	CS_clkRegs& setpll0hsclkdiv(uint val);
	uint getpll0hsclkdiv();

	//CSR1[9:7]
	CS_clkRegs& setpll0hsclkdistspare(uint val);
	uint getpll0hsclkdistspare();

	//CSR1[6:5]
	CS_clkRegs& setpll0refclkdiv(uint val);
	uint getpll0refclkdiv();

	//CSR1[4:4]
	CS_clkRegs& setpll0hsclkdivsouthpwrdb(uint val);
	uint getpll0hsclkdivsouthpwrdb();

	//CSR1[3:2]
	CS_clkRegs& setpll0mclkdiv40b(uint val);
	uint getpll0mclkdiv40b();

	//CSR1[1:0]
	CS_clkRegs& setpll0mclkdiv32b(uint val);
	uint getpll0mclkdiv32b();

	//CSR2[10:6]
	CS_clkRegs& setpll0lolthr(uint val);
	uint getpll0lolthr();

	//CSR2[5:3]
	CS_clkRegs& setpll0locthr(uint val);
	uint getpll0locthr();

	//CSR2[2:2]
	CS_clkRegs& setpll0lolmode(uint val);
	uint getpll0lolmode();

	//CSR2[1:1]
	uint getpll0outoflock();

	//CSR2[0:0]
	uint getpll0lossoflcvcoclk();

	//CSR3[15:15]
	CS_clkRegs& setpll1refclksel(uint val);
	uint getpll1refclksel();

	//CSR3[14:13]
	CS_clkRegs& setpll1refclkdiv(uint val);
	uint getpll1refclkdiv();

	//CSR3[12:11]
	CS_clkRegs& setpll1vcodivna(uint val);
	uint getpll1vcodivna();

	//CSR3[10:9]
	CS_clkRegs& setpll1vcodivka(uint val);
	uint getpll1vcodivka();

	//CSR3[8:4]
	CS_clkRegs& setpll1fbdivp(uint val);
	uint getpll1fbdivp();

	//CSR3[3:0]
	CS_clkRegs& setpll1fbdivs(uint val);
	uint getpll1fbdivs();

	//CSR4[15:15]
	CS_clkRegs& setpll1hsclkdistpwrdb(uint val);
	uint getpll1hsclkdistpwrdb();

	//CSR4[14:14]
	CS_clkRegs& setpll1hsclkdivpwrdb(uint val);
	uint getpll1hsclkdivpwrdb();

	//CSR4[13:10]
	CS_clkRegs& setpll1hsclkdiv(uint val);
	uint getpll1hsclkdiv();

	//CSR4[9:7]
	CS_clkRegs& setpll1hsclkdistspare(uint val);
	uint getpll1hsclkdistspare();

	//CSR4[4:4]
	CS_clkRegs& setpll1hsclkdivsouthpwrdb(uint val);
	uint getpll1hsclkdivsouthpwrdb();

	//CSR4[3:2]
	CS_clkRegs& setpll1mclkdiv40b(uint val);
	uint getpll1mclkdiv40b();

	//CSR4[1:0]
	CS_clkRegs& setpll1mclkdiv32b(uint val);
	uint getpll1mclkdiv32b();

	//CSR5[10:6]
	CS_clkRegs& setpll1lolthr(uint val);
	uint getpll1lolthr();

	//CSR5[5:3]
	CS_clkRegs& setpll1locthr(uint val);
	uint getpll1locthr();

	//CSR5[2:2]
	CS_clkRegs& setpll1lolmode(uint val);
	uint getpll1lolmode();

	//CSR5[1:1]
	uint getpll1outoflock();

	//CSR5[0:0]
	uint getpll1lossoflcvcoclk();

	//CSR6[15:15]
	CS_clkRegs& setwordclk40bsel(uint val);
	uint getwordclk40bsel();

	//CSR6[14:14]
	CS_clkRegs& setwordclk32bsel(uint val);
	uint getwordclk32bsel();

	//CSR6[13:13]
	CS_clkRegs& setwordclksel(uint val);
	uint getwordclksel();

	//CSR6[12:12]
	CS_clkRegs& setcoreclksel(uint val);
	uint getcoreclksel();

	//CSR6[4:4]
	CS_clkRegs& setpll0hsclk2vcovregen(uint val);
	uint getpll0hsclk2vcovregen();

	//CSR6[3:2]
	CS_clkRegs& setlifeclk2digdiv(uint val);
	uint getlifeclk2digdiv();

	//CSR6[1:0]
	CS_clkRegs& setwordclk2digdiv(uint val);
	uint getwordclk2digdiv();

	//CSR7[15:15]
	CS_clkRegs& setbiascmupwrdb(uint val);
	uint getbiascmupwrdb();

	//CSR7[14:14]
	CS_clkRegs& setrefclkdistpwrdb(uint val);
	uint getrefclkdistpwrdb();

	//CSR7[13:13]
	CS_clkRegs& setbiascmutestmode(uint val);
	uint getbiascmutestmode();

	//CSR7[12:12]
	CS_clkRegs& setadcpwrdb(uint val);
	uint getadcpwrdb();

	//CSR7[11:11]
	CS_clkRegs& setcomppwrdb(uint val);
	uint getcomppwrdb();

	//CSR7[3:2]
	CS_clkRegs& setrefclk0biasctrl(uint val);
	uint getrefclk0biasctrl();

	//CSR7[1:0]
	CS_clkRegs& setrefclk1biasctrl(uint val);
	uint getrefclk1biasctrl();

	//CSR8[15:15]
	CS_clkRegs& setpll0pwrdb(uint val);
	uint getpll0pwrdb();

	//CSR8[9:9]
	CS_clkRegs& setpll0dlfresfbpwrdb(uint val);
	uint getpll0dlfresfbpwrdb();

	//CSR8[8:8]
	CS_clkRegs& setpll0dlfpwrdb(uint val);
	uint getpll0dlfpwrdb();

	//CSR8[7:7]
	CS_clkRegs& setpll0dlfshpwrdb(uint val);
	uint getpll0dlfshpwrdb();

	//CSR8[6:6]
	CS_clkRegs& setpll0dlftstpwrdb(uint val);
	uint getpll0dlftstpwrdb();

	//CSR8[5:5]
	CS_clkRegs& setpll0dlfcmfbpwrdb(uint val);
	uint getpll0dlfcmfbpwrdb();

	//CSR8[4:4]
	CS_clkRegs& setpll0dlfchoppwrdb(uint val);
	uint getpll0dlfchoppwrdb();

	//CSR8[3:3]
	CS_clkRegs& setpll0vregpllpwrdb(uint val);
	uint getpll0vregpllpwrdb();

	//CSR8[2:2]
	CS_clkRegs& setpll0vregdlfpwrdb(uint val);
	uint getpll0vregdlfpwrdb();

	//CSR8[0:0]
	CS_clkRegs& setpll0vregvcodivpwrdb(uint val);
	uint getpll0vregvcodivpwrdb();

	//CSR9[14:14]
	CS_clkRegs& setpll0pfdupdnswap(uint val);
	uint getpll0pfdupdnswap();

	//CSR9[13:13]
	CS_clkRegs& setpll0pfdforceup(uint val);
	uint getpll0pfdforceup();

	//CSR9[12:12]
	CS_clkRegs& setpll0pfdforcedn(uint val);
	uint getpll0pfdforcedn();

	//CSR9[11:10]
	CS_clkRegs& setpll0pfdpulsewidth(uint val);
	uint getpll0pfdpulsewidth();

	//CSR9[7:7]
	CS_clkRegs& setpll0cpcalrstb(uint val);
	uint getpll0cpcalrstb();

	//CSR9[6:4]
	CS_clkRegs& setpll0cpcalrstlvl(uint val);
	uint getpll0cpcalrstlvl();

	//CSR9[2:0]
	CS_clkRegs& setpll0cpvreflvl(uint val);
	uint getpll0cpvreflvl();

	//CSR10[12:11]
	CS_clkRegs& setpll0cpintcrntsel(uint val);
	uint getpll0cpintcrntsel();

	//CSR10[6:4]
	CS_clkRegs& setpll0cppropcrntsel(uint val);
	uint getpll0cppropcrntsel();

	//CSR11[15:13]
	CS_clkRegs& setpll0dlfcintsel(uint val);
	uint getpll0dlfcintsel();

	//CSR11[7:7]
	CS_clkRegs& setpll0dlfshdelsel(uint val);
	uint getpll0dlfshdelsel();

	//CSR11[6:2]
	CS_clkRegs& setpll0dlfseldtb(uint val);
	uint getpll0dlfseldtb();

	//CSR11[1:0]
	CS_clkRegs& setpll0dlfshcapsel(uint val);
	uint getpll0dlfshcapsel();

	//CSR12[14:12]
	CS_clkRegs& setpll0vcobandsel(uint val);
	uint getpll0vcobandsel();

	//CSR12[11:11]
	CS_clkRegs& setpll0vcoregfilshorten(uint val);
	uint getpll0vcoregfilshorten();

	//CSR12[10:10]
	CS_clkRegs& setpll0vcoswthhien(uint val);
	uint getpll0vcoswthhien();

	//CSR12[9:5]
	CS_clkRegs& setpll0vcofreqcal(uint val);
	uint getpll0vcofreqcal();

	//CSR12[4:0]
	CS_clkRegs& setpll0vcoitank(uint val);
	uint getpll0vcoitank();

	//CSR13[15:12]
	CS_clkRegs& setpll0vcovref(uint val);
	uint getpll0vcovref();

	//CSR13[11:10]
	CS_clkRegs& setpll0vcodivspare(uint val);
	uint getpll0vcodivspare();

	//CSR13[9:9]
	CS_clkRegs& setpll0vcovregsel(uint val);
	uint getpll0vcovregsel();

	//CSR13[8:4]
	CS_clkRegs& setpll0vcodiv1p5ctrlcode(uint val);
	uint getpll0vcodiv1p5ctrlcode();

	//CSR13[3:3]
	CS_clkRegs& setpll0vcovregclksel(uint val);
	uint getpll0vcovregclksel();

	//CSR13[2:0]
	CS_clkRegs& setpll0vcodpmctrl(uint val);
	uint getpll0vcodpmctrl();

	//CSR14[15:15]
	CS_clkRegs& setpll0vcopdpwrdb(uint val);
	uint getpll0vcopdpwrdb();

	//CSR14[14:14]
	CS_clkRegs& setpll0vregplldpmen(uint val);
	uint getpll0vregplldpmen();

	//CSR14[13:13]
	CS_clkRegs& setpll0vregpllbleedb(uint val);
	uint getpll0vregpllbleedb();

	//CSR14[12:8]
	CS_clkRegs& setpll0vregpllsel(uint val);
	uint getpll0vregpllsel();

	//CSR14[6:6]
	CS_clkRegs& setpll0vregdlfdpmen(uint val);
	uint getpll0vregdlfdpmen();

	//CSR14[5:5]
	CS_clkRegs& setpll0vregdlfbleedb(uint val);
	uint getpll0vregdlfbleedb();

	//CSR14[4:0]
	CS_clkRegs& setpll0vregdlfsel(uint val);
	uint getpll0vregdlfsel();

	//CSR15[15:14]
	CS_clkRegs& setpll0vconewregbwsel(uint val);
	uint getpll0vconewregbwsel();

	//CSR15[13:13]
	CS_clkRegs& setpll0vcovtunebufpwrdb(uint val);
	uint getpll0vcovtunebufpwrdb();

	//CSR15[12:12]
	CS_clkRegs& setpll0vcocompenstart(uint val);
	uint getpll0vcocompenstart();

	//CSR15[11:11]
	CS_clkRegs& setpll0vcocompenpwrdb(uint val);
	uint getpll0vcocompenpwrdb();

	//CSR15[10:9]
	CS_clkRegs& setpll0vcocompenbw(uint val);
	uint getpll0vcocompenbw();

	//CSR15[8:8]
	CS_clkRegs& setpll0itankcalmode(uint val);
	uint getpll0itankcalmode();

	//CSR15[7:7]
	CS_clkRegs& setpll0freqcalmode(uint val);
	uint getpll0freqcalmode();

	//CSR15[6:6]
	CS_clkRegs& setpll0vregvcodivdpmen(uint val);
	uint getpll0vregvcodivdpmen();

	//CSR15[5:5]
	CS_clkRegs& setpll0vregvcodivbleedb(uint val);
	uint getpll0vregvcodivbleedb();

	//CSR15[4:0]
	CS_clkRegs& setpll0vregvcodivsel(uint val);
	uint getpll0vregvcodivsel();

	//CSR16[15:0]
	CS_clkRegs& setpll0spare(uint val);
	uint getpll0spare();

	//CSR17[15:15]
	CS_clkRegs& setpll1pwrdb(uint val);
	uint getpll1pwrdb();

	//CSR17[9:9]
	CS_clkRegs& setpll1dlfresfbpwrdb(uint val);
	uint getpll1dlfresfbpwrdb();

	//CSR17[8:8]
	CS_clkRegs& setpll1dlfpwrdb(uint val);
	uint getpll1dlfpwrdb();

	//CSR17[7:7]
	CS_clkRegs& setpll1dlfshpwrdb(uint val);
	uint getpll1dlfshpwrdb();

	//CSR17[6:6]
	CS_clkRegs& setpll1dlftstpwrdb(uint val);
	uint getpll1dlftstpwrdb();

	//CSR17[5:5]
	CS_clkRegs& setpll1dlfcmfbpwrdb(uint val);
	uint getpll1dlfcmfbpwrdb();

	//CSR17[4:4]
	CS_clkRegs& setpll1dlfchoppwrdb(uint val);
	uint getpll1dlfchoppwrdb();

	//CSR17[3:3]
	CS_clkRegs& setpll1vregpllpwrdb(uint val);
	uint getpll1vregpllpwrdb();

	//CSR17[2:2]
	CS_clkRegs& setpll1vregdlfpwrdb(uint val);
	uint getpll1vregdlfpwrdb();

	//CSR17[0:0]
	CS_clkRegs& setpll1vregvcodivpwrdb(uint val);
	uint getpll1vregvcodivpwrdb();

	//CSR18[14:14]
	CS_clkRegs& setpll1pfdupdnswap(uint val);
	uint getpll1pfdupdnswap();

	//CSR18[13:13]
	CS_clkRegs& setpll1pfdforceup(uint val);
	uint getpll1pfdforceup();

	//CSR18[12:12]
	CS_clkRegs& setpll1pfdforcedn(uint val);
	uint getpll1pfdforcedn();

	//CSR18[11:10]
	CS_clkRegs& setpll1pfdpulsewidth(uint val);
	uint getpll1pfdpulsewidth();

	//CSR18[7:7]
	CS_clkRegs& setpll1cpcalrstb(uint val);
	uint getpll1cpcalrstb();

	//CSR18[6:4]
	CS_clkRegs& setpll1cpcalrstlvl(uint val);
	uint getpll1cpcalrstlvl();

	//CSR18[2:0]
	CS_clkRegs& setpll1cpvreflvl(uint val);
	uint getpll1cpvreflvl();

	//CSR19[12:11]
	CS_clkRegs& setpll1cpintcrntsel(uint val);
	uint getpll1cpintcrntsel();

	//CSR19[6:4]
	CS_clkRegs& setpll1cppropcrntsel(uint val);
	uint getpll1cppropcrntsel();

	//CSR20[15:13]
	CS_clkRegs& setpll1dlfcintsel(uint val);
	uint getpll1dlfcintsel();

	//CSR20[7:7]
	CS_clkRegs& setpll1dlfshdelsel(uint val);
	uint getpll1dlfshdelsel();

	//CSR20[6:2]
	CS_clkRegs& setpll1dlfseldtb(uint val);
	uint getpll1dlfseldtb();

	//CSR20[1:0]
	CS_clkRegs& setpll1dlfshcapsel(uint val);
	uint getpll1dlfshcapsel();

	//CSR21[14:12]
	CS_clkRegs& setpll1vcobandsel(uint val);
	uint getpll1vcobandsel();

	//CSR21[11:11]
	CS_clkRegs& setpll1vcoregfilshorten(uint val);
	uint getpll1vcoregfilshorten();

	//CSR21[10:10]
	CS_clkRegs& setpll1vcoswthhien(uint val);
	uint getpll1vcoswthhien();

	//CSR21[9:5]
	CS_clkRegs& setpll1vcofreqcal(uint val);
	uint getpll1vcofreqcal();

	//CSR21[4:0]
	CS_clkRegs& setpll1vcoitank(uint val);
	uint getpll1vcoitank();

	//CSR22[15:12]
	CS_clkRegs& setpll1vcovref(uint val);
	uint getpll1vcovref();

	//CSR22[11:10]
	CS_clkRegs& setpll1vcodivspare(uint val);
	uint getpll1vcodivspare();

	//CSR22[9:9]
	CS_clkRegs& setpll1vcovregsel(uint val);
	uint getpll1vcovregsel();

	//CSR22[8:4]
	CS_clkRegs& setpll1vcodiv1p5ctrlcode(uint val);
	uint getpll1vcodiv1p5ctrlcode();

	//CSR22[3:3]
	CS_clkRegs& setpll1vcovregclksel(uint val);
	uint getpll1vcovregclksel();

	//CSR22[2:0]
	CS_clkRegs& setpll1vcodpmctrl(uint val);
	uint getpll1vcodpmctrl();

	//CSR23[15:15]
	CS_clkRegs& setpll1vcopdpwrdb(uint val);
	uint getpll1vcopdpwrdb();

	//CSR23[14:14]
	CS_clkRegs& setpll1vregplldpmen(uint val);
	uint getpll1vregplldpmen();

	//CSR23[13:13]
	CS_clkRegs& setpll1vregpllbleedb(uint val);
	uint getpll1vregpllbleedb();

	//CSR23[12:8]
	CS_clkRegs& setpll1vregpllsel(uint val);
	uint getpll1vregpllsel();

	//CSR23[6:6]
	CS_clkRegs& setpll1vregdlfdpmen(uint val);
	uint getpll1vregdlfdpmen();

	//CSR23[5:5]
	CS_clkRegs& setpll1vregdlfbleedb(uint val);
	uint getpll1vregdlfbleedb();

	//CSR23[4:0]
	CS_clkRegs& setpll1vregdlfsel(uint val);
	uint getpll1vregdlfsel();

	//CSR24[15:14]
	CS_clkRegs& setpll1vconewregbwsel(uint val);
	uint getpll1vconewregbwsel();

	//CSR24[13:13]
	CS_clkRegs& setpll1vcovtunebufpwrdb(uint val);
	uint getpll1vcovtunebufpwrdb();

	//CSR24[12:12]
	CS_clkRegs& setpll1vcocompenstart(uint val);
	uint getpll1vcocompenstart();

	//CSR24[11:11]
	CS_clkRegs& setpll1vcocompenpwrdb(uint val);
	uint getpll1vcocompenpwrdb();

	//CSR24[10:9]
	CS_clkRegs& setpll1vcocompenbw(uint val);
	uint getpll1vcocompenbw();

	//CSR24[8:8]
	CS_clkRegs& setpll1itankcalmode(uint val);
	uint getpll1itankcalmode();

	//CSR24[7:7]
	CS_clkRegs& setpll1freqcalmode(uint val);
	uint getpll1freqcalmode();

	//CSR24[6:6]
	CS_clkRegs& setpll1vregvcodivdpmen(uint val);
	uint getpll1vregvcodivdpmen();

	//CSR24[5:5]
	CS_clkRegs& setpll1vregvcodivbleedb(uint val);
	uint getpll1vregvcodivbleedb();

	//CSR24[4:0]
	CS_clkRegs& setpll1vregvcodivsel(uint val);
	uint getpll1vregvcodivsel();

	//CSR25[15:0]
	CS_clkRegs& setpll1spare(uint val);
	uint getpll1spare();

	//CSR26[15:15]
	CS_clkRegs& setadcrstb(uint val);
	uint getadcrstb();

	//CSR26[14:14]
	CS_clkRegs& setadcabsmeasen(uint val);
	uint getadcabsmeasen();

	//CSR26[13:13]
	CS_clkRegs& setadctsten(uint val);
	uint getadctsten();

	//CSR26[12:11]
	CS_clkRegs& setadcvcmctrl(uint val);
	uint getadcvcmctrl();

	//CSR26[10:10]
	uint getcstopfsmcalspare();

	//CSR26[9:9]
	CS_clkRegs& setdpminitsettingen(uint val);
	uint getdpminitsettingen();

	//CSR26[8:8]
	CS_clkRegs& setcstopfsmcalclr(uint val);
	uint getcstopfsmcalclr();

	//CSR26[7:4]
	CS_clkRegs& setmisccalforcedefault(uint val);
	uint getmisccalforcedefault();

	//CSR26[3:3]
	uint getdpmdetdone();

	//CSR26[2:0]
	CS_clkRegs& setdpmdettasksel(uint val);
	uint getdpmdettasksel();

	//CSR27[15:15]
	CS_clkRegs& setcompmodesel(uint val);
	uint getcompmodesel();

	//CSR27[14:12]
	CS_clkRegs& setcompcalmuxctrl(uint val);
	uint getcompcalmuxctrl();

	//CSR27[11:6]
	CS_clkRegs& setcompvrefsel(uint val);
	uint getcompvrefsel();

	//CSR27[5:5]
	CS_clkRegs& setoverrideoffset(uint val);
	uint getoverrideoffset();

	//CSR27[4:0]
	CS_clkRegs& setvrefgenoffset(uint val);
	uint getvrefgenoffset();

	//CSR28[15:15]
	CS_clkRegs& settopvcofsmbypass(uint val);
	uint gettopvcofsmbypass();

	//CSR28[14:14]
	CS_clkRegs& setlcvcocalsel(uint val);
	uint getlcvcocalsel();

	//CSR28[13:12]
	CS_clkRegs& setlcvcocalctrl(uint val);
	uint getlcvcocalctrl();

	//CSR28[11:11]
	uint getcspll0pwrseqdone();

	//CSR28[10:10]
	uint getcspll1pwrseqdone();

	//CSR28[9:9]
	CS_clkRegs& setcspwrseqfsmclr(uint val);
	uint getcspwrseqfsmclr();

	//CSR28[8:8]
	CS_clkRegs& setcsfwoverwrite(uint val);
	uint getcsfwoverwrite();

	//CSR28[7:6]
	CS_clkRegs& setcscalmode(uint val);
	uint getcscalmode();

	//CSR28[5:5]
	CS_clkRegs& setcsadccompsel(uint val);
	uint getcsadccompsel();

	//CSR28[4:4]
	uint getlcvcocaldone();

	//CSR28[3:3]
	uint getlcvcocalerr();

	//CSR28[2:0]
	uint getlcvcocalstatus();

	//CSR29[15:13]
	CS_clkRegs& setatbfinalsel(uint val);
	uint getatbfinalsel();

	//CSR29[12:10]
	CS_clkRegs& setcsatbtopsel(uint val);
	uint getcsatbtopsel();

	//CSR29[9:6]
	CS_clkRegs& setcsatbspare(uint val);
	uint getcsatbspare();

	//CSR29[5:3]
	CS_clkRegs& setbiasatbsel(uint val);
	uint getbiasatbsel();

	//CSR29[2:0]
	CS_clkRegs& setcompatbctrl(uint val);
	uint getcompatbctrl();

	//CSR30[15:13]
	CS_clkRegs& setpll0atbplltopsel(uint val);
	uint getpll0atbplltopsel();

	//CSR30[10:8]
	CS_clkRegs& setpll0atbpllctrl(uint val);
	uint getpll0atbpllctrl();

	//CSR30[6:5]
	CS_clkRegs& setpll0atbvcoctrl(uint val);
	uint getpll0atbvcoctrl();

	//CSR30[4:3]
	CS_clkRegs& setpll0adcvcoctrl(uint val);
	uint getpll0adcvcoctrl();

	//CSR30[0:0]
	uint getpll0dtbout();

	//CSR31[14:12]
	CS_clkRegs& setpll0atbvregsel(uint val);
	uint getpll0atbvregsel();

	//CSR31[11:9]
	CS_clkRegs& setpll0atbvregpllctrl(uint val);
	uint getpll0atbvregpllctrl();

	//CSR31[8:6]
	CS_clkRegs& setpll0atbvregdlfctrl(uint val);
	uint getpll0atbvregdlfctrl();

	//CSR31[2:0]
	CS_clkRegs& setpll0atbvregvcodivctrl(uint val);
	uint getpll0atbvregvcodivctrl();

	//CSR32[15:13]
	CS_clkRegs& setpll1atbplltopsel(uint val);
	uint getpll1atbplltopsel();

	//CSR32[10:8]
	CS_clkRegs& setpll1atbpllctrl(uint val);
	uint getpll1atbpllctrl();

	//CSR32[6:5]
	CS_clkRegs& setpll1atbvcoctrl(uint val);
	uint getpll1atbvcoctrl();

	//CSR32[4:3]
	CS_clkRegs& setpll1adcvcoctrl(uint val);
	uint getpll1adcvcoctrl();

	//CSR32[0:0]
	uint getpll1dtbout();

	//CSR33[14:12]
	CS_clkRegs& setpll1atbvregsel(uint val);
	uint getpll1atbvregsel();

	//CSR33[11:9]
	CS_clkRegs& setpll1atbvregpllctrl(uint val);
	uint getpll1atbvregpllctrl();

	//CSR33[8:6]
	CS_clkRegs& setpll1atbvregdlfctrl(uint val);
	uint getpll1atbvregdlfctrl();

	//CSR33[2:0]
	CS_clkRegs& setpll1atbvregvcodivctrl(uint val);
	uint getpll1atbvregvcodivctrl();

	//CSR34[15:15]
	CS_clkRegs& setsspwrdb(uint val);
	uint getsspwrdb();

	//CSR34[14:14]
	CS_clkRegs& setssrefclk0pwrdb(uint val);
	uint getssrefclk0pwrdb();

	//CSR34[13:13]
	CS_clkRegs& setssrefclk1pwrdb(uint val);
	uint getssrefclk1pwrdb();

	//CSR34[12:12]
	CS_clkRegs& setssrefclk0cmldivpwrdb(uint val);
	uint getssrefclk0cmldivpwrdb();

	//CSR34[11:11]
	CS_clkRegs& setssrefclk1cmldivpwrdb(uint val);
	uint getssrefclk1cmldivpwrdb();

	//CSR34[10:10]
	CS_clkRegs& setssrefclk0div2sel(uint val);
	uint getssrefclk0div2sel();

	//CSR34[9:9]
	CS_clkRegs& setssrefclk1div2sel(uint val);
	uint getssrefclk1div2sel();

	//CSR34[8:8]
	CS_clkRegs& setsscmosrefclksel(uint val);
	uint getsscmosrefclksel();

	//CSR34[7:6]
	CS_clkRegs& setssrefclk0biasctrl(uint val);
	uint getssrefclk0biasctrl();

	//CSR34[5:4]
	CS_clkRegs& setssrefclk1biasctrl(uint val);
	uint getssrefclk1biasctrl();

	//CSR34[3:2]
	CS_clkRegs& setssrefclk0distbiasctrl(uint val);
	uint getssrefclk0distbiasctrl();

	//CSR34[1:0]
	CS_clkRegs& setssrefclk1distbiasctrl(uint val);
	uint getssrefclk1distbiasctrl();

	//CSR35[9:9]
	CS_clkRegs& setbiasmstricvpwrdb(uint val);
	uint getbiasmstricvpwrdb();

	//CSR35[8:8]
	CS_clkRegs& setbiasmstriccpwrdb(uint val);
	uint getbiasmstriccpwrdb();

	//CSR35[7:7]
	CS_clkRegs& setbiasmstriptatpwrdb(uint val);
	uint getbiasmstriptatpwrdb();

	//CSR35[6:6]
	CS_clkRegs& setvbgpwrdb(uint val);
	uint getvbgpwrdb();

	//CSR35[5:5]
	CS_clkRegs& setvptatpwrdb(uint val);
	uint getvptatpwrdb();

	//CSR35[4:4]
	CS_clkRegs& setssadcpwrdb(uint val);
	uint getssadcpwrdb();

	//CSR35[3:3]
	CS_clkRegs& setsscomppwrdb(uint val);
	uint getsscomppwrdb();

	//CSR35[2:2]
	CS_clkRegs& setsscompvrefpwrdb(uint val);
	uint getsscompvrefpwrdb();

	//CSR35[1:1]
	CS_clkRegs& setmosdetidacpwrdb(uint val);
	uint getmosdetidacpwrdb();

	//CSR35[0:0]
	CS_clkRegs& setmosdetcml2cmospwrdb(uint val);
	uint getmosdetcml2cmospwrdb();

	//CSR36[15:15]
	CS_clkRegs& setbg600mvlvccresdiv(uint val);
	uint getbg600mvlvccresdiv();

	//CSR36[14:14]
	CS_clkRegs& setbgbufsel(uint val);
	uint getbgbufsel();

	//CSR36[13:13]
	CS_clkRegs& setbgbufcalen(uint val);
	uint getbgbufcalen();

	//CSR36[12:8]
	CS_clkRegs& setbgbufofst(uint val);
	uint getbgbufofst();

	//CSR36[7:0]
	CS_clkRegs& setbgbypass(uint val);
	uint getbgbypass();

	//CSR37[15:15]
	uint getbgbufcaltrig();

	//CSR37[14:14]
	CS_clkRegs& setvbgrstb(uint val);
	uint getvbgrstb();

	//CSR37[13:13]
	CS_clkRegs& setvbgbypassb(uint val);
	uint getvbgbypassb();

	//CSR37[12:12]
	CS_clkRegs& setvbgmode(uint val);
	uint getvbgmode();

	//CSR37[11:11]
	CS_clkRegs& setvbgchopclkmode(uint val);
	uint getvbgchopclkmode();

	//CSR37[10:10]
	CS_clkRegs& setvbgdemclkmode(uint val);
	uint getvbgdemclkmode();

	//CSR37[8:8]
	CS_clkRegs& setvbgenchop(uint val);
	uint getvbgenchop();

	//CSR37[7:7]
	CS_clkRegs& setvbgendem(uint val);
	uint getvbgendem();

	//CSR37[2:0]
	CS_clkRegs& setvbgreflvl(uint val);
	uint getvbgreflvl();

	//CSR38[14:14]
	CS_clkRegs& setvptatrstb(uint val);
	uint getvptatrstb();

	//CSR38[13:13]
	CS_clkRegs& setvptatbypassb(uint val);
	uint getvptatbypassb();

	//CSR38[12:12]
	CS_clkRegs& setvptatmode(uint val);
	uint getvptatmode();

	//CSR38[11:11]
	CS_clkRegs& setvptatchopclkmode(uint val);
	uint getvptatchopclkmode();

	//CSR38[10:10]
	CS_clkRegs& setvptatdemclkmode(uint val);
	uint getvptatdemclkmode();

	//CSR38[8:8]
	CS_clkRegs& setvptatenchop(uint val);
	uint getvptatenchop();

	//CSR38[7:7]
	CS_clkRegs& setvptatendem(uint val);
	uint getvptatendem();

	//CSR38[2:0]
	CS_clkRegs& setvptatreflvl(uint val);
	uint getvptatreflvl();

	//CSR39[15:15]
	CS_clkRegs& setssadcrstb(uint val);
	uint getssadcrstb();

	//CSR39[14:14]
	CS_clkRegs& setssadcabsmeasen(uint val);
	uint getssadcabsmeasen();

	//CSR39[13:13]
	CS_clkRegs& setssadctsten(uint val);
	uint getssadctsten();

	//CSR39[12:11]
	CS_clkRegs& setssadcvcmctrl(uint val);
	uint getssadcvcmctrl();

	//CSR39[10:8]
	CS_clkRegs& setssadcinputsel(uint val);
	uint getssadcinputsel();

	//CSR39[7:7]
	CS_clkRegs& settsensoren(uint val);
	uint gettsensoren();

	//CSR39[6:4]
	CS_clkRegs& settsensorcstemp(uint val);
	uint gettsensorcstemp();

	//CSR40[15:15]
	CS_clkRegs& setsscompmodesel(uint val);
	uint getsscompmodesel();

	//CSR40[14:12]
	CS_clkRegs& setsscompvinmsel(uint val);
	uint getsscompvinmsel();

	//CSR40[11:9]
	CS_clkRegs& setsscompvinpsel(uint val);
	uint getsscompvinpsel();

	//CSR40[8:3]
	CS_clkRegs& setsscompvrefsel(uint val);
	uint getsscompvrefsel();

	//CSR40[0:0]
	uint getsscompstatus();

	//CSR41[15:15]
	CS_clkRegs& setmosdeten(uint val);
	uint getmosdeten();

	//CSR41[14:14]
	CS_clkRegs& setmosdetmostypesel(uint val);
	uint getmosdetmostypesel();

	//CSR41[13:13]
	CS_clkRegs& setmosdetvcocalen(uint val);
	uint getmosdetvcocalen();

	//CSR41[12:10]
	CS_clkRegs& setmosdetioscptune(uint val);
	uint getmosdetioscptune();

	//CSR41[9:8]
	CS_clkRegs& setmosdetioscdacofst(uint val);
	uint getmosdetioscdacofst();

	//CSR41[7:0]
	CS_clkRegs& setmosdetioscdaccal(uint val);
	uint getmosdetioscdaccal();

	//CSR42[15:13]
	CS_clkRegs& setmosdetpsel(uint val);
	uint getmosdetpsel();

	//CSR42[12:10]
	CS_clkRegs& setmosdets1sel(uint val);
	uint getmosdets1sel();

	//CSR42[9:8]
	CS_clkRegs& setmosdets2sel(uint val);
	uint getmosdets2sel();

	//CSR42[7:7]
	CS_clkRegs& setmosdetiosccrosstune(uint val);
	uint getmosdetiosccrosstune();

	//CSR42[1:0]
	CS_clkRegs& setmosdetoscdiv(uint val);
	uint getmosdetoscdiv();

	//CSR43[15:13]
	CS_clkRegs& setmosdetcsnmoscnr(uint val);
	uint getmosdetcsnmoscnr();

	//CSR43[12:10]
	CS_clkRegs& setmosdetcspmoscnr(uint val);
	uint getmosdetcspmoscnr();

	//CSR43[9:7]
	CS_clkRegs& setmosdetcscmoscnr(uint val);
	uint getmosdetcscmoscnr();

	//CSR43[6:0]
	CS_clkRegs& setsschopdemclkdiv(uint val);
	uint getsschopdemclkdiv();

	//CSR44[15:15]
	CS_clkRegs& setrpolydetcalsel(uint val);
	uint getrpolydetcalsel();

	//CSR44[14:14]
	CS_clkRegs& setrpolydethvrxtermcalen(uint val);
	uint getrpolydethvrxtermcalen();

	//CSR44[13:10]
	CS_clkRegs& setrpolydetcsrxtermcal(uint val);
	uint getrpolydetcsrxtermcal();

	//CSR44[5:4]
	CS_clkRegs& setrpolydetcsrpolycnr(uint val);
	uint getrpolydetcsrpolycnr();

	//CSR44[3:0]
	CS_clkRegs& setssdpmsparein(uint val);
	uint getssdpmsparein();

	//CSR45[15:0]
	CS_clkRegs& setssspare(uint val);
	uint getssspare();

	//CSR46[14:12]
	CS_clkRegs& setssatbsel(uint val);
	uint getssatbsel();

	//CSR46[11:6]
	CS_clkRegs& setrefclkreceiveratbsel(uint val);
	uint getrefclkreceiveratbsel();

	//CSR46[5:0]
	CS_clkRegs& setbiasmstratbsel(uint val);
	uint getbiasmstratbsel();

	//CSR47[12:11]
	CS_clkRegs& settsensorhvatbsel(uint val);
	uint gettsensorhvatbsel();

	//CSR47[10:8]
	CS_clkRegs& setsscompatbctrl(uint val);
	uint getsscompatbctrl();

	//CSR47[5:5]
	CS_clkRegs& settopvcofsm2ndpassen(uint val);
	uint gettopvcofsm2ndpassen();

	//CSR47[4:4]
	CS_clkRegs& setfirstpassitankbypass(uint val);
	uint getfirstpassitankbypass();

	//CSR47[3:3]
	CS_clkRegs& setfddiffavemodesel(uint val);
	uint getfddiffavemodesel();

	//CSR47[2:2]
	CS_clkRegs& setfreqcalprefsel(uint val);
	uint getfreqcalprefsel();

	//CSR47[1:1]
	CS_clkRegs& setbandselprefsel(uint val);
	uint getbandselprefsel();

	//CSR47[0:0]
	CS_clkRegs& setexitonthreshold(uint val);
	uint getexitonthreshold();

	//CSR48[15:13]
	CS_clkRegs& setssdpmatbsel(uint val);
	uint getssdpmatbsel();

	//CSR48[8:6]
	CS_clkRegs& setmosdetvgsatbctrl(uint val);
	uint getmosdetvgsatbctrl();

	//CSR48[5:3]
	CS_clkRegs& setmosdetoscatbctrl(uint val);
	uint getmosdetoscatbctrl();

	//CSR48[2:0]
	CS_clkRegs& setrpolydethvatbctrl(uint val);
	uint getrpolydethvatbctrl();

	//CSR49[14:8]
	CS_clkRegs& setadccompclkprediv(uint val);
	uint getadccompclkprediv();

	//CSR49[7:5]
	CS_clkRegs& setcsadcclkdiv(uint val);
	uint getcsadcclkdiv();

	//CSR49[4:2]
	CS_clkRegs& setcscompclkdiv(uint val);
	uint getcscompclkdiv();

	//CSR49[1:0]
	CS_clkRegs& setcsdfdeadbandsel(uint val);
	uint getcsdfdeadbandsel();

	//CSR50[15:14]
	CS_clkRegs& setcsdecmfactor(uint val);
	uint getcsdecmfactor();

	//CSR50[13:13]
	CS_clkRegs& setcsadcconvmode(uint val);
	uint getcsadcconvmode();

	//CSR50[12:12]
	CS_clkRegs& setcsdforder(uint val);
	uint getcsdforder();

	//CSR50[11:0]
	CS_clkRegs& setcsdfrefcode(uint val);
	uint getcsdfrefcode();

	//CSR51[15:15]
	uint getcsdfrdy();

	//CSR51[14:14]
	uint getcsdfcompstatus();

	//CSR51[13:13]
	uint getcsdfcompstatusdbm();

	//CSR51[12:12]
	uint getcsdfcompstatusdbp();

	//CSR51[11:0]
	uint getcsdfdata();

	//CSR52[11:10]
	CS_clkRegs& setcsdfautotimervalue(uint val);
	uint getcsdfautotimervalue();

	//CSR52[9:8]
	CS_clkRegs& setssdfautotimervalue(uint val);
	uint getssdfautotimervalue();

	//CSR52[7:5]
	CS_clkRegs& setssadcclkdiv(uint val);
	uint getssadcclkdiv();

	//CSR52[4:2]
	CS_clkRegs& setsscompclkdiv(uint val);
	uint getsscompclkdiv();

	//CSR52[1:0]
	CS_clkRegs& setssdfdeadbandsel(uint val);
	uint getssdfdeadbandsel();

	//CSR53[15:14]
	CS_clkRegs& setssdecmfactor(uint val);
	uint getssdecmfactor();

	//CSR53[13:13]
	CS_clkRegs& setssadcconvmode(uint val);
	uint getssadcconvmode();

	//CSR53[12:12]
	CS_clkRegs& setssdforder(uint val);
	uint getssdforder();

	//CSR53[11:0]
	CS_clkRegs& setssdfrefcode(uint val);
	uint getssdfrefcode();

	//CSR54[15:15]
	uint getssdfrdy();

	//CSR54[14:14]
	uint getssdfcompstatus();

	//CSR54[13:13]
	uint getssdfcompstatusdbm();

	//CSR54[12:12]
	uint getssdfcompstatusdbp();

	//CSR54[11:0]
	uint getssdfdata();

	//CSR55[15:8]
	CS_clkRegs& setringvcorefclkdiv(uint val);
	uint getringvcorefclkdiv();

	//CSR55[4:0]
	CS_clkRegs& setringvcofdclkdiv(uint val);
	uint getringvcofdclkdiv();

	//CSR56[15:13]
	uint getdpmnmoscnr();

	//CSR56[12:10]
	uint getdpmpmoscnr();

	//CSR56[9:7]
	uint getdpmcmoscnr();

	//CSR56[6:4]
	uint getdpmtemperature();

	//CSR57[13:10]
	uint getdpmrxtermcal();

	//CSR57[9:6]
	uint getdpmspare();

	//CSR57[5:4]
	uint getdpmrpolycnr();

	//CSR57[3:0]
	uint getssdpmspareout();

	//CSR58[15:15]
	CS_clkRegs& setcstopfsm_cal_start(uint val);
	uint getcstopfsm_cal_start();

	//CSR58[14:14]
	CS_clkRegs& setdpmfinetuneen(uint val);
	uint getdpmfinetuneen();

	//CSR58[13:0]
	CS_clkRegs& setcstopfsm_cal_task_sel(uint val);
	uint getcstopfsm_cal_task_sel();

	//CSR59[15:15]
	uint getcstopfsm_cal_done();

	//CSR59[14:14]
	uint getdpmfinetunerdy();

	//CSR59[13:0]
	uint getcstopfsm_cal_task_status();

	//CSR60[11:6]
	CS_clkRegs& setpll0vregpllcompvref(uint val);
	uint getpll0vregpllcompvref();

	//CSR60[5:0]
	CS_clkRegs& setpll1vregpllcompvref(uint val);
	uint getpll1vregpllcompvref();

	//CSR61[11:6]
	CS_clkRegs& setpll0vregdlfcompvref(uint val);
	uint getpll0vregdlfcompvref();

	//CSR61[5:0]
	CS_clkRegs& setpll1vregdlfcompvref(uint val);
	uint getpll1vregdlfcompvref();

	//CSR62[11:6]
	CS_clkRegs& setpll0vregvcodivcompvref(uint val);
	uint getpll0vregvcodivcompvref();

	//CSR62[5:0]
	CS_clkRegs& setpll1vregvcodivcompvref(uint val);
	uint getpll1vregvcodivcompvref();

	//CSR63[11:6]
	CS_clkRegs& setpll0vregcpvrefcompvref(uint val);
	uint getpll0vregcpvrefcompvref();

	//CSR63[5:0]
	CS_clkRegs& setpll1vregcpvrefcompvref(uint val);
	uint getpll1vregcpvrefcompvref();

};

#endif // HILINKCSCLKREGS_H_
