#ifndef HILINKDSCLKREGS_H_
#define HILINKDSCLKREGS_H_

#include <HILINK_DRIVE/HiLink_Regs_Base.h>
#define DS_CLK_CSR_NUM 20

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

	/// Dataslice power sequence control 
	/// 0 = Power down entire DS  sequentially
	/// 1 = Power up entire DS  sequentially
	/// 
	/// Note: New  in v101.  Used as a trigger to  sequentially power up the entire Dataslice with default settings
			const T_REG_INFO_EX& dspwrdb();	//CSR0[15:15]

	/// Select high-speed clock spine ( for both RX and TX )
	/// 0 = Select clock spine 0
	/// 1 = Select clock spine 1
	/// (Independent RX and TX selection no longer supported in v101)
			const T_REG_INFO_EX& clkspinesel();	//CSR0[14:14]

	/// Resets ds power sequence. Active low.
			const T_REG_INFO_EX& dspwrsqsoftrstb();	//CSR0[12:12]

	/// DS power sequence time between steps for regulators (TBS2)
			const T_REG_INFO_EX& dspwrsqtbs2();	//CSR0[11:8]

	/// Power Sequencing status
	/// 0 =  sequence not done/incomplete
	/// 1 =  sequence complete
			const T_REG_INFO_EX& dspwrsqdone();	//CSR0[7:7]

	/// DS power sequence time between steps (TBS)
			const T_REG_INFO_EX& dspwrsqtbs();	//CSR0[6:4]

	/// Dsclk spine clock 0 distribution power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& buf0pwrdb();	//CSR0[3:3]

	/// Dsclk spine clock 1 distribution power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& buf1pwrdb();	//CSR0[2:2]

	/// New in V101: Power sequence mode selector. 
	/// 00 =  This is the default  power sequence mode to be used.   Power up/down sequence follows required steps and value from registers.
	/// 01: Power sequence follows preset values (Test purposes only).
	/// 10: Power sequence is bypassed (old V100 mode).  
	/// 11: Not used
	/// Note:  Do not change PWRSQMODE once the Dataslice is powered up or in use.  Disruption may result.
			const T_REG_INFO_EX& pwrsqmode();	//CSR0[1:0]

	/// Dsclk RX PI voltage reference bias power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& clkgenbiaspwrdb();	//CSR1[15:15]

	/// Dsclk regulator power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& clkgenvregpwrdb();	//CSR1[14:14]

	/// Dsclk  spine clock mux quadrature divider power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
	/// New in v101: Used as a Trigger to sequentially power up/down DSLK circuitry (both to RX and TX)  with default settings
	/// (register name in v100 was RXQDIV2PWRDB)
			const T_REG_INFO_EX& qdiv2pwrdb();	//CSR1[13:13]

	/// spare not used
			const T_REG_INFO_EX& txcmlpwrdb();	//CSR1[12:12]

	/// Dsclk TX  pi power down control. Active low.
	/// 0 = Power Down
	/// 1= Power up
			const T_REG_INFO_EX& txcmospipwrdb();	//CSR1[11:11]

	/// DSCLK regulator inrush current limit DPM trimming.
	/// 0 = select voltage reference for SS corner
	/// 1 = select voltage reference for TT/FF corner
			const T_REG_INFO_EX& vregdpmen();	//CSR1[6:6]

	/// Dsclk regulator bleed current control.
	/// 0 = enable bleed current
	/// 1 = disable bleed current
			const T_REG_INFO_EX& vregbleedb();	//CSR1[5:5]

	/// Voltage level control of dsclk regulator. (default =0.923v)
	/// 00000 = Minimum voltage.
	/// 00001
	/// 00010
	/// ..
	/// 10100=voltage(default)
	/// ?.
	/// 11111 = Maximum voltage.
			const T_REG_INFO_EX& vreglvl();	//CSR1[4:0]

	/// DSCLK regulator inrush current limit. Active low.
	/// 0: regulator inrush current limit  mode
	/// 1: regulator mission mode
			const T_REG_INFO_EX& clkvreginrushpwrdb();	//CSR2[15:15]

	/// Dsclk PI driver select ref for loading resistance determination. 
	/// 000: min loading resistance -- 10G application
	/// 011:                                                 -- 32G application
	/// 111: max loading resistance
			const T_REG_INFO_EX& reprefsel();	//CSR2[14:12]

	/// reference range select for dsclk regulator
	/// 00:  vref between 750mV  and  850mV
	/// 01: vref  between 851mV and 925mV
	/// 10: vref between 926mV and 985mV
	/// 11: vref between 986mV and 1050mV
			const T_REG_INFO_EX& clkvregvrefrng();	//CSR2[11:10]

	/// RX PI DPM based drive strength adjust to CC divider
	///      11- min current drive to PI
	///      00- max current drive to PI (30G default)
	/// TT/FF  value should be 2'b11(30G)
	/// SS value should be 2'b01(30G)
			const T_REG_INFO_EX& clkrxdpm();	//CSR2[9:8]

	/// Dsclk PI drivers input common mode voltage control. 
	/// 00 = Minimum input common mode voltage.
	/// 01
	/// 10
	/// 11 = Maximum input common mode voltage.
			const T_REG_INFO_EX& vrefsel();	//CSR2[7:6]

	/// TX PI DPM based drive strength adjust to CC divider
	///      11- min current drive to PI
	///      00- max current drive to PI
			const T_REG_INFO_EX& clktxccdivdpm();	//CSR2[5:4]

	/// Dsclk TX Div2 I/Q output capacitance loading control.     
	///      x00- min cap load; 30G (default)
	///       ...
	///     x11- max cap load
	/// i.e. bit [2] not assigned
			const T_REG_INFO_EX& clktxcaploadtrim();	//CSR2[3:1]

	/// 0- TX pi-predistortion disabled
	/// 1- TX pi-predistortion enabled
			const T_REG_INFO_EX& clktxpipredistpwrdnb();	//CSR2[0:0]

	/// Dsclk spine clock mux output capacitance loading control. Binary coded.
	/// 00 = Min capacitance loading ( setting for 32G app)
	/// 01 =     (setting for 10G app)          
	/// 10
	/// 11 = Max  capacitance loading
			const T_REG_INFO_EX& muxcshuntctrl();	//CSR3[12:11]

	/// Dsclk RX Div2 I/Q output capacitance loading control.
	/// Binary weighted caps.
	/// 000: min cap loading  (setting for 32G application)
	///  ...
	/// 111: max cap loading  (setting for 10G application)
			const T_REG_INFO_EX& caploadtrim();	//CSR3[10:8]

	/// Dsclk RX CML PI driver AC coupling capacitance selection. 
	/// 00: min cap loading  (setting for 32G application)
	/// 01:                                 (setting for 10G application)
	/// 10:
	/// 11: max cap loading
			const T_REG_INFO_EX& pidrvhpftcaptrim();	//CSR3[6:5]

	/// DSCK spare bits (restored back as spare from v100)
			const T_REG_INFO_EX& dsclkspare();	//CSR3[4:0]

	/// Dsclk ATB control. Selected signal will go to dsclk_atb_out.
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = Select vref of Rx PI driver output
	/// 010 = High Impedance
	/// 011 = Select dsclk_pi_vref
	/// 100 = High Impedance
	/// 101 = Select dsclk 3/4 vreg local sense
	/// 110 = High Impedance
	/// 111 = High Impedance
			const T_REG_INFO_EX& dsclktopatbctrl();	//CSR4[15:13]

	/// Dsclk regulator ATB control. Selected signal will go to hv_txtop_atb_out.
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = select vref
	/// 010 = select vlow 
	/// 011 = High Impedance
	/// 100 = High Impedance
	/// 101 = select vmid
	/// 110 = select dsclk 2/3 sense voltage
	/// 111 = High Impedance
			const T_REG_INFO_EX& vregatbctrl();	//CSR4[12:10]

	/// TX PI bias current scale
	///    00: max current
	///    11: min current
			const T_REG_INFO_EX& clktxpibiastrim();	//CSR4[9:8]

	/// Spare not used
			const T_REG_INFO_EX& clktxbibufbiastrim();	//CSR4[7:6]

	/// spare not used
			const T_REG_INFO_EX& clktxpibufloadtrim();	//CSR4[5:4]

	/// spare not used
			const T_REG_INFO_EX& clktxpidrvloadctrl();	//CSR4[3:2]

	/// Dsclk TXPI CML bias control control.
	/// 0: use PI default bias
	/// 1:  boost PI bias by 50uA (default for 30 G)
			const T_REG_INFO_EX& clktxpibiascoarsetrim();	//CSR4[1:1]

	/// Dataslice bias receiver power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& dsbiasrcvrpwrdb();	//CSR5[15:15]

	/// ADC (in DataSlice) power down control.
	/// 0: Power down
	/// 1: Power up
			const T_REG_INFO_EX& dsadcpwrdb();	//CSR5[14:14]

	/// Comparator(in DataSlice) power down control. Active low.
	/// 0 = Power down calcomp.
	/// 1 = Power up calcomp.
			const T_REG_INFO_EX& dscalcomppwrdb();	//CSR5[13:13]

	/// Calibration comparator (in DataSlice) power down control. Active low.
	/// 0 = Power down.
	/// 1 = Power up.
			const T_REG_INFO_EX& dscalcompvrefpwrdb();	//CSR5[12:12]

	/// not used
			const T_REG_INFO_EX& dscalcompvrefrng();	//CSR5[11:10]

	/// Dataslice bias receivers commn-mode rejection control.
	/// 0: H30 Experimental mode (not recommended)
	/// 1: Mission mode
			const T_REG_INFO_EX& dsbiasrcvrselcm();	//CSR5[9:9]

	/// Dataslice bias receivers test mode enable control. 
	/// 0 = Mission mode (using differential bias voltage)
	/// 1 = Enable test mode (self bias)
			const T_REG_INFO_EX& dsbiasrcvrtsten();	//CSR5[8:8]

	/// 00: initial calibration using comparator, start from hard-coded default values
	/// 01: update calibration using comparator, start from current value
	/// 10: initial calibration using ADC, start from hard-coded default values (NOT SUPPORTED)
	/// 11: update calibration using ADC, start from current value (NOT SUPPORTED)
			const T_REG_INFO_EX& dscalmode();	//CSR5[7:6]

	/// ADC decimation filter ready
			const T_REG_INFO_EX& dsadcdfrdy();	//CSR5[5:5]

	/// ADC timer divider ratio - Optional divider used in determining ADC settling delay.   Also refer to DSADCTIMER[1:0] .
	/// 0= bypass additional divider
	/// 1= enable additional divider
			const T_REG_INFO_EX& dsadctimerdiv();	//CSR5[4:4]

	/// ADC timer value - From ADC start, enforced settling delay before ADC beings sampling.  Also refer  to DSADCTIMERDIV.
	/// For DSADCTIMERDIV= 0 
	/// 00:      5 ADC clock cycles (1.56us @ 3.2MHz)
	/// 01:    37 ADC clock cycles (11.6us @ 3.2MHz)
	/// 10:    85 ADC clock cycles (26.6us @ 3.2MHz)
	/// 11:  165 ADC clock cycles (51.6us @ 3.2MHz)
	/// 
	/// For DSADCTIMERDIV= 1 
	/// 00:   6 ADC clock cycles   (1.87us     @ 3.2MHz)
	/// 01: 70 ADC clock cycles   (21.87us  @ 3.2MHz)
	/// 10: 166 ADC clock cycles (51.87us  @ 3.2MHz)
	/// 11: 326 ADC clock cycles (101.87us@ 3.2MHz)
			const T_REG_INFO_EX& dsadctimer();	//CSR5[3:2]

	/// adc deadband select
			const T_REG_INFO_EX& dsadcdeadbandsel();	//CSR5[1:0]

	/// ADC(in DataSlice) reset. Active low.
	/// 0 = Reset
	/// 1 = Normal operation mode
			const T_REG_INFO_EX& dsadcrstb();	//CSR6[15:15]

	/// ADC (in DataSlice)absolute measurement mode enable control.
	/// 0 = Relative measurement mode (using hvcc as reference)
	/// 1 = Absolute measurement mode (using vref_bg as reference)
			const T_REG_INFO_EX& dsadcabsmeasen();	//CSR6[14:14]

	/// ADC test mode (in DataSlice)enable control.
	/// 0 = Normal operation mode
	/// 1 = Enable test mode (connect ADC input to Vcm)
			const T_REG_INFO_EX& dsadctsten();	//CSR6[13:13]

	/// Internal common mode voltage control for opamp and comparator reference(in DataSlice).
	/// 00 = 10/24 * hvcc
	/// ;01 = 11/24 * hvcc
	/// ;10 = 12/24 * hvcc
	/// ;11 = 13/24 * hvcc.
			const T_REG_INFO_EX& dsadcvcmctrl();	//CSR6[12:11]

	/// Status of dataslice analog comparator out value
			const T_REG_INFO_EX& dscalcompout();	//CSR6[10:10]

	/// Comparator operating mode selection.
	/// 0 = Single-end mode (compare vinp with vref)
	/// 1 = Differential mode (compare vinp and vinm)
			const T_REG_INFO_EX& dscalcompmodesel();	//CSR6[9:9]

	/// Select OTB/AB input of calibration comparator.
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = Select Rx otbp / otbm
	/// 010 = Select Tx otbp / otbm
	/// 011 = Select Tx2rx loopback otbp / otbm
	/// 100 = Select Tx atb
	/// 101 = Select Dsclk atb
	/// 110 = Select hvcc
	/// 111 = Select vss
			const T_REG_INFO_EX& dscalcompotbctrl();	//CSR6[8:6]

	/// Set Reference voltage selection for calibration comparator (default=637.5mV) used for TX drv and predrv regulator calibration, RX clock and Data  regulator calibration, DSCLK regulator calibration.  Access valid only if TXCALMODE, RXCALMODE, DSCLKCALIBMODE is set to manual.
	/// 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 111111 =  Vref=800mV
			const T_REG_INFO_EX& dscalcompvrefsel();	//CSR6[5:0]

	/// Dataslice top level ATB output enable.
	/// 0 = Disable dataslice top level ATB output.
	/// 1 = Enable dataslice top lelvel ATB output.
			const T_REG_INFO_EX& dstoplvlatbouten();	//CSR7[15:15]

	/// Dataslice top level ATB control.
	/// 0000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 0001 = Select RX top ATB output
	/// 0010 = Select Tx top ATB output
	/// 0011 = Select Dsclk top ATB outputput
	/// 0100 = Select Tx to Rx loopback ATB output
	/// 0101 = Select bias receivers ATB output
	/// 0110 = Select calibration comparator ATB output
	/// 0111 = Select hvcc
	/// 1000 = select comp vref
	/// 1001 = Select RX otbp
	/// 1010 = Select RX otbm
	/// 1011 = Select TX otbp
	/// 1100 = Select TX otbm
	/// 1101 = Select Tx to Rx loopback otbp
	/// 1110 = Select Tx to Rx loopback otbm
	/// 1111 = Select vss
			const T_REG_INFO_EX& dstopatbctrl();	//CSR7[14:11]

	/// Dataslice bias receiver ATB selection.
	/// 00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 = Select icvp 50uA current.
	/// 10 = Select iccp 50uA current.
	/// 11 = Select iptat_50uA current
			const T_REG_INFO_EX& dsbiasrcvratbctrl();	//CSR7[4:3]

	/// ATB selection for calibration comparator.
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = Select vcmref
	/// 010 = Select vout_opamp
	/// 011 = Select vref
	/// 100 = Select vinp
	/// 101 = Select vinm/vref
	/// vinm @ ds_calcomp_mode_sel = 1
	/// vref @ ds_calcomp_mode_sel = 0
	/// 110 to 111 = Invalid settings
			const T_REG_INFO_EX& dscalcompatbctrl();	//CSR7[2:0]

	/// 0 = calibration is based on analog comparator output
	/// 1 = calibration is based on ADC output
			const T_REG_INFO_EX& dsadccompsel();	//CSR8[15:15]

	/// ADC and Comparator clock pre stage divider ratio.  Sets [DSADCCOMPCLKPREDIV+1] as the divide ratio that is performed on the hclk.   Ie, 
	/// hclk / [DSADCCOMPCLKPREDIV+1]
	/// This clock is then further divided by two different dividers, one to provide the clock for the ADC and one to provide the clock for the comparator.  See  DSADCCLKDIV and  DSCOMPCLKDIV for more information
			const T_REG_INFO_EX& dsadccompclkprediv();	//CSR8[14:8]

	/// divider ratio to generate adc clock after the pre stage divider. (See also DSADCCOMPCLKPREDIV)
	/// 000 = div by 256
	/// 001 = div by 128
	/// 010 = div by 64
	/// 011 = div by 32
	/// 100 = div by 16
	/// 101 = div by 8
	/// 110 = div by 4
	/// 111 = div by 2
			const T_REG_INFO_EX& dsadcclkdiv();	//CSR8[7:5]

	/// divider ratio to generate comparator clock after the pre stage divider.(See also DSADCCOMPCLKPREDIV)
	/// 000 = div by 512
	/// 001 = div by 256
	/// 010 = div by 128
	/// 011 = div by 64
	/// 100 = div by 32
	/// 101 = div by 16
	/// 110 = div by 8
	/// 111 = div by 4
			const T_REG_INFO_EX& dscompclkdiv();	//CSR8[4:2]

	/// adc decimation filter mode
	/// 00 = single sho mode
	/// 01 = continuous mode
	/// 10 and 11 = not used
			const T_REG_INFO_EX& dsadcconvmode();	//CSR8[1:0]

	/// decimation factor selection
	/// 00 = 256
	/// 01 = 512
	/// 10 = 1024
	/// 11 = 2048
			const T_REG_INFO_EX& dsdecmfactor();	//CSR9[15:14]

	/// decimation filter order
	/// x0 = sync 1
	/// x1 = sync 2
	/// (bit #1 not used)
			const T_REG_INFO_EX& dsdforder();	//CSR9[13:12]

	/// decimation filter reference value
			const T_REG_INFO_EX& dsdfrefcode();	//CSR9[11:0]

	/// Not implemented. Use DSADCDFRDY instead.
			const T_REG_INFO_EX& dsdfrdy();	//CSR10[15:15]

	/// status of decimation filter comparator
	/// 0 = decimation data below reference level
	/// 1 = decimation data above reference level
			const T_REG_INFO_EX& dsdfcompstatus();	//CSR10[14:14]

	/// status of decimation filter data
	/// ABOVE decimation filter
			const T_REG_INFO_EX& dsdfdata();	//CSR10[11:0]

	/// 0 = auto
	/// 1 = manual
			const T_REG_INFO_EX& dsclkcalibmode();	//CSR11[15:15]

	/// DSCLK calibration start control.
	/// 0 = Do not start DSCLK calibration
	/// ;1 = Start DSCLK calibration. Self clear after calibration is done.
			const T_REG_INFO_EX& dsclkcalibstart();	//CSR11[14:14]

	/// dsclk calibration block soft reset; active low
			const T_REG_INFO_EX& dsclkcalibsoftrstb();	//CSR11[13:13]

	/// dsclk calibration comparator direction control
			const T_REG_INFO_EX& dsclkcalibdir();	//CSR11[12:12]

	/// Set Comparator reference voltage  for DSCLK voltage regulator calibration.   
	/// Calib Target (mV)= 600 * (1+dsclkcalibregrefsel/64)
	/// Note: CLKVREGVREFRNG[1:0] must be correspondingly set to a range which supports the calibration target voltage.
			const T_REG_INFO_EX& dsclkcalibregrefsel();	//CSR11[5:0]

	/// Configuration of timer for waiting, which is the cycles of reference clock. Timer value = (2powDSCLKCALTIMERVALUE) -1 , where DSCLKCALTIMERVALUE =0 to 22.
			const T_REG_INFO_EX& dsclkcaltimervalue();	//CSR12[14:5]

	/// Not used
			const T_REG_INFO_EX& dsclkcaltimerdivvalue();	//CSR12[4:2]

	/// Not used
			const T_REG_INFO_EX& dsclkcaltimerdiven();	//CSR12[1:1]

	/// Stop timer, for debugging.
	/// 0 = normal
	/// 1 = stop the timer
			const T_REG_INFO_EX& dsclkcaltimerstop();	//CSR12[0:0]

	/// Recovered clock divide ratio
	/// output frequency= rx_center_wordclk / (RXRECCLKFBDIV + 1)
			const T_REG_INFO_EX& rxrecclkfbdiv();	//CSR13[15:10]

	/// recovered clock powerdown. active low
	/// 0 =  powerdown
	/// 1 =  enable
	/// NOTE: PER MACRO, ONLY 1 DS MAY ENABLE
	/// RECOVERED CLOCK FEATURE AT A TIME
			const T_REG_INFO_EX& rxrecclkpwrdb();	//CSR13[9:9]

	/// TX I-PI static fine delay adjust
	/// 00 =  min delay
	/// 11 =   max delay
			const T_REG_INFO_EX& dsclktxdlyctrli();	//CSR13[5:4]

	/// TX Q-PI static fine delay adjust
	/// 00 =  min delay
	/// 11 =   max delay
			const T_REG_INFO_EX& dsclktxdlyctrlq();	//CSR13[3:2]

	/// TX I-PI DPM for static fine delay adjust
	/// 0 =  nominal delay (30G -- default)
	/// 1 =  increase delay
			const T_REG_INFO_EX& dsclktxidpm();	//CSR13[1:1]

	/// TX Q-PI DPM for static fine delay adjust
	/// 0 =  nominal delay (30G -- default)
	/// 1 =  increase delay
			const T_REG_INFO_EX& dsclktxqdpm();	//CSR13[0:0]

	/// 01= bypass vrefgen calibration
	/// 10= bypass dsclk regulator calibration
			const T_REG_INFO_EX& dsclkcalbypass();	//CSR14[15:14]

	/// Vrefgen calibarted code 16
			const T_REG_INFO_EX& vrefgenrefcode16();	//CSR14[13:8]

	/// Bypass vrefgen interpolation adjustment function
	/// 0 using vrefgen interpolation
	/// 1 bypass vrefgen interpolation
			const T_REG_INFO_EX& vrefgenintrpbp();	//CSR14[7:7]

	/// vrefgen calibration direction
			const T_REG_INFO_EX& vrefgencaldir();	//CSR14[6:6]

	/// Vrefgen calibarted code 26
			const T_REG_INFO_EX& vrefgenrefcode26();	//CSR14[5:0]

	/// 0 =  vref gen calibrate bandgap
	/// 1 =  vref gen calibrate hvcc
			const T_REG_INFO_EX& vrefgenbgsel();	//CSR15[14:14]

	/// Vrefgen calibarted code 38
			const T_REG_INFO_EX& vrefgenrefcode38();	//CSR15[13:8]

	/// Vrefgen calibarted code 48
			const T_REG_INFO_EX& vrefgenrefcode48();	//CSR15[5:0]

	/// vrefgen offset value at 16
			const T_REG_INFO_EX& vrefgenofst16();	//CSR16[15:8]

	/// vrefgen offset value at 26
			const T_REG_INFO_EX& vrefgenofst26();	//CSR16[7:0]

	/// vrefgen offset value at 38
			const T_REG_INFO_EX& vrefgenofst38();	//CSR17[15:8]

	/// vrefgen offset value at 48
			const T_REG_INFO_EX& vrefgenofst48();	//CSR17[7:0]

	/// Vrefgen initial value for code 16 calibration
			const T_REG_INFO_EX& vrefgenrefintl16();	//CSR18[13:8]

	/// Vrefgen initial value for code 26 calibration
			const T_REG_INFO_EX& vrefgenrefintl26();	//CSR18[5:0]

	/// Vrefgen initial value for code 38 calibration
			const T_REG_INFO_EX& vrefgenrefintl38();	//CSR19[13:8]

	/// Vrefgen initial value for code 48 calibration
			const T_REG_INFO_EX& vrefgenrefintl48();	//CSR19[5:0]
			bool get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos);
	};
public:
	_REG_INFO REG_INFO;

	uint csr[DS_CLK_CSR_NUM];


	//CSR0[15:15]
	DS_clkRegs& setdspwrdb(uint val);
	uint getdspwrdb();

	//CSR0[14:14]
	DS_clkRegs& setclkspinesel(uint val);
	uint getclkspinesel();

	//CSR0[12:12]
	DS_clkRegs& setdspwrsqsoftrstb(uint val);
	uint getdspwrsqsoftrstb();

	//CSR0[11:8]
	DS_clkRegs& setdspwrsqtbs2(uint val);
	uint getdspwrsqtbs2();

	//CSR0[7:7]
	uint getdspwrsqdone();

	//CSR0[6:4]
	DS_clkRegs& setdspwrsqtbs(uint val);
	uint getdspwrsqtbs();

	//CSR0[3:3]
	DS_clkRegs& setbuf0pwrdb(uint val);
	uint getbuf0pwrdb();

	//CSR0[2:2]
	DS_clkRegs& setbuf1pwrdb(uint val);
	uint getbuf1pwrdb();

	//CSR0[1:0]
	DS_clkRegs& setpwrsqmode(uint val);
	uint getpwrsqmode();

	//CSR1[15:15]
	DS_clkRegs& setclkgenbiaspwrdb(uint val);
	uint getclkgenbiaspwrdb();

	//CSR1[14:14]
	DS_clkRegs& setclkgenvregpwrdb(uint val);
	uint getclkgenvregpwrdb();

	//CSR1[13:13]
	DS_clkRegs& setqdiv2pwrdb(uint val);
	uint getqdiv2pwrdb();

	//CSR1[12:12]
	DS_clkRegs& settxcmlpwrdb(uint val);
	uint gettxcmlpwrdb();

	//CSR1[11:11]
	DS_clkRegs& settxcmospipwrdb(uint val);
	uint gettxcmospipwrdb();

	//CSR1[6:6]
	DS_clkRegs& setvregdpmen(uint val);
	uint getvregdpmen();

	//CSR1[5:5]
	DS_clkRegs& setvregbleedb(uint val);
	uint getvregbleedb();

	//CSR1[4:0]
	DS_clkRegs& setvreglvl(uint val);
	uint getvreglvl();

	//CSR2[15:15]
	DS_clkRegs& setclkvreginrushpwrdb(uint val);
	uint getclkvreginrushpwrdb();

	//CSR2[14:12]
	DS_clkRegs& setreprefsel(uint val);
	uint getreprefsel();

	//CSR2[11:10]
	DS_clkRegs& setclkvregvrefrng(uint val);
	uint getclkvregvrefrng();

	//CSR2[9:8]
	DS_clkRegs& setclkrxdpm(uint val);
	uint getclkrxdpm();

	//CSR2[7:6]
	DS_clkRegs& setvrefsel(uint val);
	uint getvrefsel();

	//CSR2[5:4]
	DS_clkRegs& setclktxccdivdpm(uint val);
	uint getclktxccdivdpm();

	//CSR2[3:1]
	DS_clkRegs& setclktxcaploadtrim(uint val);
	uint getclktxcaploadtrim();

	//CSR2[0:0]
	DS_clkRegs& setclktxpipredistpwrdnb(uint val);
	uint getclktxpipredistpwrdnb();

	//CSR3[12:11]
	DS_clkRegs& setmuxcshuntctrl(uint val);
	uint getmuxcshuntctrl();

	//CSR3[10:8]
	DS_clkRegs& setcaploadtrim(uint val);
	uint getcaploadtrim();

	//CSR3[6:5]
	DS_clkRegs& setpidrvhpftcaptrim(uint val);
	uint getpidrvhpftcaptrim();

	//CSR3[4:0]
	DS_clkRegs& setdsclkspare(uint val);
	uint getdsclkspare();

	//CSR4[15:13]
	DS_clkRegs& setdsclktopatbctrl(uint val);
	uint getdsclktopatbctrl();

	//CSR4[12:10]
	DS_clkRegs& setvregatbctrl(uint val);
	uint getvregatbctrl();

	//CSR4[9:8]
	DS_clkRegs& setclktxpibiastrim(uint val);
	uint getclktxpibiastrim();

	//CSR4[7:6]
	DS_clkRegs& setclktxbibufbiastrim(uint val);
	uint getclktxbibufbiastrim();

	//CSR4[5:4]
	DS_clkRegs& setclktxpibufloadtrim(uint val);
	uint getclktxpibufloadtrim();

	//CSR4[3:2]
	DS_clkRegs& setclktxpidrvloadctrl(uint val);
	uint getclktxpidrvloadctrl();

	//CSR4[1:1]
	DS_clkRegs& setclktxpibiascoarsetrim(uint val);
	uint getclktxpibiascoarsetrim();

	//CSR5[15:15]
	DS_clkRegs& setdsbiasrcvrpwrdb(uint val);
	uint getdsbiasrcvrpwrdb();

	//CSR5[14:14]
	DS_clkRegs& setdsadcpwrdb(uint val);
	uint getdsadcpwrdb();

	//CSR5[13:13]
	DS_clkRegs& setdscalcomppwrdb(uint val);
	uint getdscalcomppwrdb();

	//CSR5[12:12]
	DS_clkRegs& setdscalcompvrefpwrdb(uint val);
	uint getdscalcompvrefpwrdb();

	//CSR5[11:10]
	DS_clkRegs& setdscalcompvrefrng(uint val);
	uint getdscalcompvrefrng();

	//CSR5[9:9]
	DS_clkRegs& setdsbiasrcvrselcm(uint val);
	uint getdsbiasrcvrselcm();

	//CSR5[8:8]
	DS_clkRegs& setdsbiasrcvrtsten(uint val);
	uint getdsbiasrcvrtsten();

	//CSR5[7:6]
	DS_clkRegs& setdscalmode(uint val);
	uint getdscalmode();

	//CSR5[5:5]
	uint getdsadcdfrdy();

	//CSR5[4:4]
	DS_clkRegs& setdsadctimerdiv(uint val);
	uint getdsadctimerdiv();

	//CSR5[3:2]
	DS_clkRegs& setdsadctimer(uint val);
	uint getdsadctimer();

	//CSR5[1:0]
	DS_clkRegs& setdsadcdeadbandsel(uint val);
	uint getdsadcdeadbandsel();

	//CSR6[15:15]
	DS_clkRegs& setdsadcrstb(uint val);
	uint getdsadcrstb();

	//CSR6[14:14]
	DS_clkRegs& setdsadcabsmeasen(uint val);
	uint getdsadcabsmeasen();

	//CSR6[13:13]
	DS_clkRegs& setdsadctsten(uint val);
	uint getdsadctsten();

	//CSR6[12:11]
	DS_clkRegs& setdsadcvcmctrl(uint val);
	uint getdsadcvcmctrl();

	//CSR6[10:10]
	uint getdscalcompout();

	//CSR6[9:9]
	DS_clkRegs& setdscalcompmodesel(uint val);
	uint getdscalcompmodesel();

	//CSR6[8:6]
	DS_clkRegs& setdscalcompotbctrl(uint val);
	uint getdscalcompotbctrl();

	//CSR6[5:0]
	DS_clkRegs& setdscalcompvrefsel(uint val);
	uint getdscalcompvrefsel();

	//CSR7[15:15]
	DS_clkRegs& setdstoplvlatbouten(uint val);
	uint getdstoplvlatbouten();

	//CSR7[14:11]
	DS_clkRegs& setdstopatbctrl(uint val);
	uint getdstopatbctrl();

	//CSR7[4:3]
	DS_clkRegs& setdsbiasrcvratbctrl(uint val);
	uint getdsbiasrcvratbctrl();

	//CSR7[2:0]
	DS_clkRegs& setdscalcompatbctrl(uint val);
	uint getdscalcompatbctrl();

	//CSR8[15:15]
	DS_clkRegs& setdsadccompsel(uint val);
	uint getdsadccompsel();

	//CSR8[14:8]
	DS_clkRegs& setdsadccompclkprediv(uint val);
	uint getdsadccompclkprediv();

	//CSR8[7:5]
	DS_clkRegs& setdsadcclkdiv(uint val);
	uint getdsadcclkdiv();

	//CSR8[4:2]
	DS_clkRegs& setdscompclkdiv(uint val);
	uint getdscompclkdiv();

	//CSR8[1:0]
	DS_clkRegs& setdsadcconvmode(uint val);
	uint getdsadcconvmode();

	//CSR9[15:14]
	DS_clkRegs& setdsdecmfactor(uint val);
	uint getdsdecmfactor();

	//CSR9[13:12]
	DS_clkRegs& setdsdforder(uint val);
	uint getdsdforder();

	//CSR9[11:0]
	DS_clkRegs& setdsdfrefcode(uint val);
	uint getdsdfrefcode();

	//CSR10[15:15]
	uint getdsdfrdy();

	//CSR10[14:14]
	uint getdsdfcompstatus();

	//CSR10[11:0]
	uint getdsdfdata();

	//CSR11[15:15]
	DS_clkRegs& setdsclkcalibmode(uint val);
	uint getdsclkcalibmode();

	//CSR11[14:14]
	DS_clkRegs& setdsclkcalibstart(uint val);
	uint getdsclkcalibstart();

	//CSR11[13:13]
	DS_clkRegs& setdsclkcalibsoftrstb(uint val);
	uint getdsclkcalibsoftrstb();

	//CSR11[12:12]
	DS_clkRegs& setdsclkcalibdir(uint val);
	uint getdsclkcalibdir();

	//CSR11[5:0]
	DS_clkRegs& setdsclkcalibregrefsel(uint val);
	uint getdsclkcalibregrefsel();

	//CSR12[14:5]
	DS_clkRegs& setdsclkcaltimervalue(uint val);
	uint getdsclkcaltimervalue();

	//CSR12[4:2]
	DS_clkRegs& setdsclkcaltimerdivvalue(uint val);
	uint getdsclkcaltimerdivvalue();

	//CSR12[1:1]
	DS_clkRegs& setdsclkcaltimerdiven(uint val);
	uint getdsclkcaltimerdiven();

	//CSR12[0:0]
	DS_clkRegs& setdsclkcaltimerstop(uint val);
	uint getdsclkcaltimerstop();

	//CSR13[15:10]
	DS_clkRegs& setrxrecclkfbdiv(uint val);
	uint getrxrecclkfbdiv();

	//CSR13[9:9]
	DS_clkRegs& setrxrecclkpwrdb(uint val);
	uint getrxrecclkpwrdb();

	//CSR13[5:4]
	DS_clkRegs& setdsclktxdlyctrli(uint val);
	uint getdsclktxdlyctrli();

	//CSR13[3:2]
	DS_clkRegs& setdsclktxdlyctrlq(uint val);
	uint getdsclktxdlyctrlq();

	//CSR13[1:1]
	DS_clkRegs& setdsclktxidpm(uint val);
	uint getdsclktxidpm();

	//CSR13[0:0]
	DS_clkRegs& setdsclktxqdpm(uint val);
	uint getdsclktxqdpm();

	//CSR14[15:14]
	DS_clkRegs& setdsclkcalbypass(uint val);
	uint getdsclkcalbypass();

	//CSR14[13:8]
	DS_clkRegs& setvrefgenrefcode16(uint val);
	uint getvrefgenrefcode16();

	//CSR14[7:7]
	DS_clkRegs& setvrefgenintrpbp(uint val);
	uint getvrefgenintrpbp();

	//CSR14[6:6]
	DS_clkRegs& setvrefgencaldir(uint val);
	uint getvrefgencaldir();

	//CSR14[5:0]
	DS_clkRegs& setvrefgenrefcode26(uint val);
	uint getvrefgenrefcode26();

	//CSR15[14:14]
	DS_clkRegs& setvrefgenbgsel(uint val);
	uint getvrefgenbgsel();

	//CSR15[13:8]
	DS_clkRegs& setvrefgenrefcode38(uint val);
	uint getvrefgenrefcode38();

	//CSR15[5:0]
	DS_clkRegs& setvrefgenrefcode48(uint val);
	uint getvrefgenrefcode48();

	//CSR16[15:8]
	DS_clkRegs& setvrefgenofst16(uint val);
	uint getvrefgenofst16();

	//CSR16[7:0]
	DS_clkRegs& setvrefgenofst26(uint val);
	uint getvrefgenofst26();

	//CSR17[15:8]
	DS_clkRegs& setvrefgenofst38(uint val);
	uint getvrefgenofst38();

	//CSR17[7:0]
	DS_clkRegs& setvrefgenofst48(uint val);
	uint getvrefgenofst48();

	//CSR18[13:8]
	DS_clkRegs& setvrefgenrefintl16(uint val);
	uint getvrefgenrefintl16();

	//CSR18[5:0]
	DS_clkRegs& setvrefgenrefintl26(uint val);
	uint getvrefgenrefintl26();

	//CSR19[13:8]
	DS_clkRegs& setvrefgenrefintl38(uint val);
	uint getvrefgenrefintl38();

	//CSR19[5:0]
	DS_clkRegs& setvrefgenrefintl48(uint val);
	uint getvrefgenrefintl48();

};

#endif // HILINKDSCLKREGS_H_
