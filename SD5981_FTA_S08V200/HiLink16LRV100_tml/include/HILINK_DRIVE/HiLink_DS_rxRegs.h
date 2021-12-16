#ifndef HILINKDSRXREGS_H_
#define HILINKDSRXREGS_H_

#include "HiLink_Regs_Base.h"
#define DS_RX_CSR_NUM 63

class DS_rxRegs:public HILINK_Regs_Base{
protected:
	DS_rxRegs();
	virtual ~DS_rxRegs();

	uint& get_csr(uint csrIndex);
	virtual void get_default_MacroLaneID(T_MacroLaneID& id);

public:
	bool get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos);
	static DS_rxRegs& getInstance();
	string getName();
	uint getCSRCount();
	E_HILINK_REGISTER_TYPE getType();
	uint get_HILINK_MAX_LANE_NUM();
	uint getAddressMapToHiLink(int csrIndex);

///////////////////////////////////////////////////////////////////////////

private:
	class _REG_INFO{
		public:

	/// Receive path power down control. Active low.
	/// 0 = Power down all receiver circuitry
	/// 1 = Power up all receiver circuitry
			const T_REG_INFO_EX& rxpwrdb();	//CSR0[15:15]

	/// Recovered clock power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& recclkpwrdb();	//CSR0[14:14]

	/// Bypass  on-die RX capacitor.
	/// 0 = CAP is not bypassed
	/// 1 = Bypass CAP
			const T_REG_INFO_EX& rxcapbypass();	//CSR0[13:13]

	/// Mute control for the RX input stage.
	/// 0 = Normal operation.
	/// 1 = Mute input to first CTLE stage.
	/// The average (long term) voltage of the ¡®p¡¯, and ¡®m¡¯ inputs are equalized. Offset calibration requires  RXMUTE to be 1.
			const T_REG_INFO_EX& rxmute();	//CSR0[12:12]

	/// CML low power enable. 
	/// 0 = Normal CML power consumption
	/// 1 = Enable CML low power
			const T_REG_INFO_EX& lpcmlen();	//CSR0[11:11]

	/// TX to RX serial loopback enable.
	/// 0 = Normal operation receiver in mission mode.
	/// 1 = High speed TX to RX loopback is enabled.
			const T_REG_INFO_EX& txrxserlpbken();	//CSR0[10:10]

	/// Configure any rate divider from rx high speed reccovery clock.
	/// The output clock frequency can be caculated as : 
	/// Output clock freq= HSCLK freq /  Nrxwidth / Nrecc. 
	/// a) HSCLK freq is the frequency of spine clock, 
	/// b) Nrxwidth equal 8 when register RXDWIDTH is set to 000/010, 
	/// and equal 10 when  RXDWIDTH set to 001/011£» 
	/// c) Nrecc is the divN of this register; 
	/// 00 0000= div1
	/// 00 0001= div2
	/// ¡­¡­¡­¡­¡­¡­¡­..
	/// 11 1111=div64
			const T_REG_INFO_EX& recclkdiv();	//CSR0[9:4]

	/// cdr recovery clock divide 16 output power down.
	/// 0=power down
	/// 1=power up 
	/// notes: it power up only for 16Gbp
			const T_REG_INFO_EX& wordclkdiv_pwrdnb();	//CSR0[3:3]

	/// Input passive attenuator control.
	/// 000 = -1 dB (minimum)
	/// 001 = -2 dB
	/// 010 = -3dB
	/// 011 = -4dB
	/// 100 = -5dB
	/// 101 = -6dB
	/// 110 = -6.5dB
	/// 111 = -7dB (maximum)
			const T_REG_INFO_EX& ctlepassgn();	//CSR0[2:0]

	/// CTLE boost control (stage 1). 
	/// 0000= minimum
	/// 0001
	/// 0010
	/// 0011
	/// 0100
	/// 0101
	/// 0110
	/// 0111
	/// 1000
	/// 1001
	/// 1010
	/// 1011
	/// 1100
	/// 1101
	/// 1110
	/// 1111= maximum
			const T_REG_INFO_EX& ctlebst1();	//CSR1[15:12]

	/// CTLE mid-band capacitor control (stage 1).
	/// Use in tandem with RMBAND to boost mid-band frequencies (100MHz - 600MHz).
	/// 00 = highest zero frequency
	/// 01 
	/// 10
	/// 11 = lowest zero frequency
	/// 
	/// IF CTLERMBAND[1:0] FOR STAGE is set to '00'
	/// mid-band zero function is deactivated.
			const T_REG_INFO_EX& ctlecmband1();	//CSR1[11:10]

	/// CTLE mid-band resistor control (stage 1). Use in tandem with CMBAND to boost mid-band frequencies (100MHz - 600MHz).
	/// 00 = Mid-band zero deactivated.
	/// 01 = Low boost. (Low freq.  cancelling pole)
	/// 10 = Mid boost. 
	/// 11 = Highest boost. (1 to  1.5dB).
			const T_REG_INFO_EX& ctlermband1();	//CSR1[9:8]

	/// CTLE zero adjust control (stage 1).
	/// Extends frequency coverage of CTLE to lower frequencies.  Maintains boost magnitude down to 3-GHz. 
	/// 00 = primary zero is at highest frequency 
	/// 01 = intermediate frequency
	/// 10 = lowest frequency
	/// 11 = NA
			const T_REG_INFO_EX& ctleza1();	//CSR1[7:6]

	/// CTLE squelch control (stage 1).  Attenuates high frequencies, and can be used to lower boost.
	/// 00=No squelch
	/// 01 and 10 = 50% squelch
	/// 11= Max squelch
			const T_REG_INFO_EX& ctlesqh1();	//CSR1[5:4]

	/// CTLE active gain (stage 1).  Gain adjust control for stage 1 of  embedded VGA.
	/// 0000 = minimum gain.
	/// 0001, 0010, 0011, 0100, 0101, 0110 0111 1000 1001 1010 1011 1100 1101 1110 = intermediate settings.
	/// 1111 = maximum gain.
	/// 
	/// Total of 16 gain settings monotonically increasing from
	/// the minimum setting to maximum.
			const T_REG_INFO_EX& ctleactgn1();	//CSR1[3:0]

	/// CTLE boost control (stage 2). 
	/// 000 = minimum
	/// 0001
	/// 0010
	/// 0011
	/// 0100
	/// 0101
	/// 0110
	/// 0111
	/// 1000
	/// 1001
	/// 1010
	/// 1011
	/// 1100
	/// 1101
	/// 1110
	/// 1111= maximum
			const T_REG_INFO_EX& ctlebst2();	//CSR2[15:12]

	/// CTLE mid-band capacitor control (stage 2).
	/// Use in tandem with RMBAND to boost mid-band frequencies (100MHz - 600MHz).
	/// 00 = highest zero frequency
	/// 01 
	/// 10
	/// 11 = lowest zero frequency
	/// 
	/// IF CTLERMBAND[1:0] FOR STAGE is set to '00'
	/// mid-band zero function is deactivated.
			const T_REG_INFO_EX& ctlecmband2();	//CSR2[11:10]

	/// CTLE mid-band resistor control (stage 2). Use in tandem with CMBAND to boost mid-band frequencies (100MHz - 600MHz).
	/// 00 = Mid-band zero deactivated.
	/// 01 = Low boost. (Low freq.  cancelling pole)
	/// 10 = Mid boost. 
	/// 11 = Highest boost. (1 to  1.5dB).
			const T_REG_INFO_EX& ctlermband2();	//CSR2[9:8]

	/// CTLE zero adjust control (stage 2).
	/// Extends frequency coverage of CTLE to lower frequencies.  Maintains boost magnitude down to 3-GHz. 
	/// 00 = primary zero is at highest frequency 
	/// 01 = intermediate frequency
	/// 10 = lowest frequency
	/// 11 = NA
			const T_REG_INFO_EX& ctleza2();	//CSR2[7:6]

	/// CTLE squelch control (stage 2).  Attenuates high frequencies, and can be used to lower boost.
	/// 00=No squelch
	/// 01 and 10 = 50% squelch
	/// 11= Max squelch
			const T_REG_INFO_EX& ctlesqh2();	//CSR2[5:4]

	/// CTLE active gain (stage 2).  Gain adjust control for stage 2 of  embedded VGA.
	/// 0000= minimum gain.
	/// 0001, 0010, 0011, 0100, 0101, 0110 0111 1000 1001, 1010, 1011, 1100, 1101, 1110 = intermediate settings.
	/// 1111 = maximum gain.
	/// 
	/// Total of 16 gain settings monotonically increasing from
	/// the minimum setting to maximum.
			const T_REG_INFO_EX& ctleactgn2();	//CSR2[3:0]

	/// CTLE boost control (stage 3). 
	/// 000 = minimum
	/// 0001
	/// 0010
	/// 0011
	/// 0100
	/// 0101
	/// 0110
	/// 0111
	/// 1000
	/// 1001
	/// 1010
	/// 1011
	/// 1100
	/// 1101
	/// 1110
	/// 1111= maximum
			const T_REG_INFO_EX& ctlebst3();	//CSR3[15:12]

	/// CTLE mid-band capacitor control (stage 3).
	/// Use in tandem with RMBAND to boost mid-band frequencies (100MHz - 600MHz).
	/// 00 = highest zero frequency
	/// 01 
	/// 10
	/// 11 = lowest zero frequency
	/// 
	/// IF CTLERMBAND[1:0] FOR STAGE is set to '00'
	/// mid-band zero function is deactivated.
			const T_REG_INFO_EX& ctlecmband3();	//CSR3[11:10]

	/// CTLE mid-band resistor control (stage 3). Use in tandem with CMBAND to boost mid-band frequencies (100MHz - 600MHz).
	/// 00 = Mid-band zero deactivated.
	/// 01 = Low boost. (Low freq.  cancelling pole)
	/// 10 = Mid boost. 
	/// 11 = Highest boost. (1 to  1.5dB).
			const T_REG_INFO_EX& ctlermband3();	//CSR3[9:8]

	/// CTLE zero adjust control (stage 3).
	/// Extends frequency coverage of CTLE to lower frequencies.  Maintains boost magnitude down to 3-GHz. 
	/// 00 = primary zero is at highest frequency 
	/// 01 = intermediate frequency
	/// 10 = lowest frequency
	/// 11 = NA
			const T_REG_INFO_EX& ctleza3();	//CSR3[7:6]

	/// CTLE squelch control (stage 3).  Attenuates high frequencies, and can be used to lower boost.
	/// 00=No squelch
	/// 01 and 10 = 50% squelch
	/// 11= Max squelch
			const T_REG_INFO_EX& ctlesqh3();	//CSR3[5:4]

	/// CTLE active gain (stage 3).  Gain adjust control for stage 2 of  embedded VGA.
	/// 0000= minimum gain.
	/// 0001, 0010, 0011, 0100, 0101, 0110 0111 1000 1001, 1010, 1011, 1100, 1101, 1110 = intermediate settings.
	/// 1111 = maximum gain.
	/// 
	/// Total of 16 gain settings monotonically increasing from
	/// the minimum setting to maximum.
			const T_REG_INFO_EX& ctleactgn3();	//CSR3[3:0]

	/// DFE power down control. Active low.
	/// 0 = Power down DFE circuitry
	/// 1 = Power up DFE circuitry
			const T_REG_INFO_EX& dfepwrdb();	//CSR4[15:15]

	/// Auxiliary DFE tap (tap beyond 29UI) power down control. Active low.
			const T_REG_INFO_EX& dfeauxmvtappwrdb();	//CSR4[14:14]

	/// DFE floating tap power down control. Active low.
	/// 0 = Power down all floating taps circuitry.
	/// 1 = Power up all floating taps circuitry
			const T_REG_INFO_EX& dfemvtappwrdb();	//CSR4[13:13]

	/// DFE fixed tap enables
	/// LSB = fixed tap1
	/// xxx1x = fixed tap2
	/// xx1xx = fixed tap3
	/// x1xxx = fixed tap4
	/// MSB = fixed tap5
			const T_REG_INFO_EX& dfefxtapen();	//CSR4[12:8]

	/// rx termination offset comperate when rx calibration done, the MSB is the sign-bit of offset, and the last three bit is offset value that the user want to compenrate, the range the user configured is from -7 to +7. when the MSB is 1, the offset descrease, otherwise, the offset increase.
			const T_REG_INFO_EX& rxtermofst();	//CSR4[7:4]

	/// Gain control for DFE summer.  Affects only the main datapath (e.g. main cursor).
	/// 000 = minimum dc gain
	/// 001 = default
	/// 011
	/// 111 = maximum dc gain
			const T_REG_INFO_EX& dfegnsum();	//CSR4[2:0]

	/// DFE fixed tap1 amplitude setting, sign bit plus binary code amplitude for 0-63.
			const T_REG_INFO_EX& dfefxtap1();	//CSR5[15:9]

	/// DFE fixed tap2 amplitude setting, sign bit plus binary code amplitude for 0-31.
			const T_REG_INFO_EX& dfefxtap2();	//CSR5[5:0]

	/// RX AC couple burst mode enable
	/// 0 = AC couple burst mode enable
	/// 1 = AC couple normal mode enable
			const T_REG_INFO_EX& ana_bmen_n();	//CSR6[15:15]

	/// DFE fixed tap3 amplitude setting, sign bit plus binary code amplitude for 0-15.
			const T_REG_INFO_EX& dfefxtap3();	//CSR6[14:10]

	/// DFE fixed tap4 amplitude setting, sign bit plus binary code amplitude for 0-15.
			const T_REG_INFO_EX& dfefxtap4();	//CSR6[9:5]

	/// DFE fixed tap5 amplitude setting, sign bit plus binary code amplitude for 0-15.
			const T_REG_INFO_EX& dfefxtap5();	//CSR6[4:0]

	/// rx termination  power down.
	/// 0=power down
	/// 1=power up
			const T_REG_INFO_EX& rxterm_pwrdnb();	//CSR7[15:15]

	/// center edge phase offset signal. The default value is 0x20, the range is from 16~48.
	/// when PMA_MODE is PCIE or SATA mode, it is only  available in full-rate mode.
			const T_REG_INFO_EX& cephase_full();	//CSR7[14:9]

	/// 10bit loopback pattern data transtion density threshold value
	/// 000 = 4
	/// 001 = 8
	/// 010 = 16
	/// 011 = 32
	/// 100 = 64
	/// 101 = 128
	/// 110 = 256
	/// 111 = 512
			const T_REG_INFO_EX& pat_des_lvl();	//CSR7[8:6]

	/// when cmphase and emphase async, the cmphase and emphase synchronize enable signal.
	/// 0 = disable 
	/// 1 = enbale
			const T_REG_INFO_EX& emphase_sync();	//CSR7[5:5]

	/// DFE floating taps select. Details TBD
	/// 00000 = fixed taps;                   01100 = floating taps 28 - 33
	/// ;00001 = floating taps 6 - 11;   01101 = floating taps 30 - 35
	/// ;00010 = floating taps 8 - 13;   01110 = floating taps 32 - 37
	/// ;00011 = floating taps 10 - 15; 01111 = floating taps 34 - 39
	/// ;00100 = floating taps 12 - 17; 10000 = floating taps 36 - 41
	/// ;00101 = floating taps 14 - 19; 10001 = floating taps 38 - 43
	/// ;00110 = floating taps 16 - 21; 10010 = floating taps 40 - 45
	/// ;00111 = floating taps 18 - 23; 10011 = floating taps 42 - 47
	/// ;01000 = floating taps 20 - 25; 10100 = floating taps 44 - 49
	/// ;01001 = floating taps 22 - 27; 10101 = floating taps 46 - 51
	/// ;01010 = floating taps 24 - 29; 10110 - 11111 = fixed taps.
	/// 01011 = floating taps 26 - 31
	/// 
	/// ;Note: when DFEMVTAPSEL[4:0] > '01010',  DFEAUXMVTAPPWRDB (DSRX.CSR[14]) must be set to 1.
			const T_REG_INFO_EX& dfemvtapsel();	//CSR7[4:0]

	/// rxterm_floating controlled sel
	/// 0 = controlled by Asic Core pin rxterm_floating
	/// 1 = controlled by register CSR27_RXTERM_FLOATING_EN
			const T_REG_INFO_EX& rxterm_floating_sel();	//CSR8[15:15]

	/// DFE floating tap1 amplitude setting, sign bit plus binary code amplitude for 0-15.
			const T_REG_INFO_EX& dfemvtap1();	//CSR8[14:10]

	/// DFE floating tap2 amplitude setting, sign bit plus binary code amplitude for 0-15.
			const T_REG_INFO_EX& dfemvtap2();	//CSR8[9:5]

	/// DFE floating tap3 amplitude setting, sign bit plus binary code amplitude for 0-15.
			const T_REG_INFO_EX& dfemvtap3();	//CSR8[4:0]

	/// DFE floating tap4 amplitude setting, sign bit plus binary code amplitude for 0-15.
			const T_REG_INFO_EX& dfemvtap4();	//CSR9[14:10]

	/// DFE floating tap5 amplitude setting, sign bit plus binary code amplitude for 0-15.
			const T_REG_INFO_EX& dfemvtap5();	//CSR9[9:5]

	/// DFE floating tap6 amplitude setting, sign bit plus binary code amplitude for 0-15.
			const T_REG_INFO_EX& dfemvtap6();	//CSR9[4:0]

	/// Receiver digital circuitry reset. Active low.
	/// 0 = Reset RX logic
	/// 1 = RX out of reset
			const T_REG_INFO_EX& rxrstb();	//CSR10[15:15]

	/// RX data width select.
	/// 000 = 16 (8, 4, 2) bit parallel interface.
	/// 001 = 20 (10, 5, 2.5) bit parallel interface.
	/// 010 = 32 (16, 8, 4) bit interface.
	/// 011 = 40 (20, 10, 5) bit interface.
	/// 1xx  = Reserved
			const T_REG_INFO_EX& rxdwidth();	//CSR10[14:12]

	/// RX bit rate mode.
	/// 00 = full-rate
	/// 01 = 1/2-rate
	/// 10 = 1/4-rate
	/// 11 = 1/8-rate
			const T_REG_INFO_EX& rxratemode();	//CSR10[11:10]

	/// Selects the mapping of the parallel RXD bus from the serial bit order:
	/// 0 = LSB is the first serial bit 
	/// 1 = MSB is the first bit input
			const T_REG_INFO_EX& rxbitorder();	//CSR10[9:9]

	/// RX data polarity control. When set, all received bits are inverted before being sent out to the core.
	/// 0 = Do not invert the RX data
	/// 1 = Invert RX the data
			const T_REG_INFO_EX& rxpolarity();	//CSR10[8:8]

	/// Select the parallel RX data to be sent to the core.
	/// 0 = Select the recovered data.
	/// 1 = Select the TX data coming from the core. This enables the TX-to-RX parallel loopback.
			const T_REG_INFO_EX& txrxparlpbken();	//CSR10[7:7]

	/// CDR Work Mode
	/// 0: Non-SSC CDR Mode
	/// 1: SSC CDR Mode
			const T_REG_INFO_EX& cdr_mode();	//CSR10[6:6]

	/// data-rate/width switch related signals(include rxdwidth, rxratemode and cphsofst) source select control
	/// 0: switch control 
	/// 1: register control
	/// Notes: it is only available for PCIE or SAS mode.
			const T_REG_INFO_EX& sw_para_source_sel();	//CSR10[5:5]

	/// Freeze CDR. When CDR is frozen, it doesn't track the jitter and PPM of incoming data.
	/// 0 = Normal operation
	/// 1 = CDR is frozen
			const T_REG_INFO_EX& cdrfreeze();	//CSR10[3:3]

	/// Bang-bang phase detect mode select.
	/// 0 = Normal
	/// 1 = Filter out bad transitions
			const T_REG_INFO_EX& bbpdmode();	//CSR10[2:2]

	/// Second loop enable. By enabling the second loop integrator CDR can track more PPM up to +/-XXXXppm, 
	/// 0 = Disable the CDR's second loop integrator.
	/// 1 = Enable the second loop integrator.
			const T_REG_INFO_EX& secloopen();	//CSR10[1:1]

	/// Each transition of this bit, from 0 to 1 or from 1 to 0, will cause the RX phase rotator to move 1UI (direction is TBD) to slip one serial bit. Multiple slips can be achieved by toggling this bit. Each transition has to wait for previous slip to complete (at least 64 word clock cycles).
			const T_REG_INFO_EX& bitslip();	//CSR10[0:0]

	/// CDR soft reset. Active low.
	/// 0 = Reset CDR
	/// 1 = Normal operation
			const T_REG_INFO_EX& cdrrstb();	//CSR11[15:15]

	/// CDR phase gain.
	/// 000 = 1;    001 = 2;    010 = 4;    011 = 8
	/// ;100 = 16;  101 = 32;  110 = 64;  111 = 128.
			const T_REG_INFO_EX& cdrphsgn();	//CSR11[13:11]

	/// First integral loop gain.
	/// 000 = 0.25;   001 = 0.5;   010 = 1;     011 = 2
	/// ;100 = 4;        101 = 8;      110 = 16;   111 = 32.
			const T_REG_INFO_EX& cdrk1gn();	//CSR11[10:8]

	/// CDR second integral loop gain.
	/// 000 = 1;    001 = 2;    010 = 4;    011 = 8
	/// ;100 = 16;  101 = 32;  110 = 64;  111 = 128.
			const T_REG_INFO_EX& cdrk2gn();	//CSR11[7:5]

	/// Saturation value for truncated output of the first integral 
	/// 000 = 32
	/// 001 = 64
	/// 010 = 128
	/// 011 = 256
	/// 100 = 512
	/// 101 = 1024 (default)
	/// 110 = 2048
	/// 111 = 4096
			const T_REG_INFO_EX& freqintsat();	//CSR11[4:2]

	/// Number of dither bits of the first integral
	/// 00 = 4 dither bit
	/// 01 = 5 dither bit
	/// 10 = 6 dither bit
	/// 11 = 7 dither bit
			const T_REG_INFO_EX& freqintatt();	//CSR11[1:0]

	/// Phase offset between the center channel and the edge channel. A 2's complement value (-128 to 127) with each step of 1/64 full-rate UI. Nominal setting depends on the rate mode as follows,
	/// Rate Mode      Nominal setting
	/// full-rate           +32 (0010_0000)
	/// 1/2 rate                0
	/// 1/4 rate                0
	/// 1/8 rate                0
	/// when worked in SSC CDR mode, its value is +16.
			const T_REG_INFO_EX& cphsofst();	//CSR12[15:8]

	/// Edge phase offset. A 2's complement value (-128 to 127) to adjust the edge phase when the CDR is frozen.  Can be used to slip one or multiple bits of RXD. To do bit slip, freeze the CDR first. Then write +/-64 (01000000/11000000) for +/-1UI move, or +127/-128 (01111111/10000000). For more than 2UI move, use multiple commands.
			const T_REG_INFO_EX& ephsofst();	//CSR12[7:0]

	/// Transition density detection enable. When disabled, all transition density detection logic is reset.
	/// 0 = Disable transition density detector
	/// 1 = Enable transition density detector
			const T_REG_INFO_EX& tdden();	//CSR13[15:15]

	/// Set the threshold for transition density detector.
	/// 000 = 32          100 = 512
	/// 001 = 64          101 = 1024
	/// 010 = 128        110 = 2048
	/// 011 = 256        111 = 4096
			const T_REG_INFO_EX& tddthr();	//CSR13[14:12]

	/// Eye scan based LOS detection enable.
	/// 0 = Disable eye scan based LOS detection
	/// 1 = Enable eye scan based LOS detection
			const T_REG_INFO_EX& loseyeen();	//CSR13[11:11]

	/// Eye scan based LOS threshold.
	/// 00 = 12 vertical/2 horizontal steps
	/// 01 = 28 vertical/4 horizontal steps
	/// 10 = 44 vertical/8 horizontal steps
	/// 11 = 60 vertical/16 horizontal steps
			const T_REG_INFO_EX& loseyethr();	//CSR13[10:9]

	/// Enable analog LOS detection. (Not available yet)
	/// 0 = Disable
	/// 1 = Enable
			const T_REG_INFO_EX& losanaen();	//CSR13[8:8]

	/// LOS configuration.
	/// LOSCFG[2]:
	/// 0 = LOS pin is a real time status of the transition density detector
	/// 1 = LOS pin is a latched status of the transition density detector (clear after read)
	/// LOSCFG[1:0]:
	/// 00 = Both LOS pin and LOS register bit (RX CSR13[4]) will be set to high when there are no enough transitions.
	/// 01 = Both LOS pin and LOS register bit (RX CSR13[4]) will be set to high when inner eye is not open enough vertically.
	/// 10 = Both LOS pin and LOS register bit (RX CSR13[4]) will be set to high when inner eye is not open enough horizontally.
	/// 11 = Both LOS pin and LOS register bit (RX CSR13[4]) will be set to high when there are no enough transitions, or inner eye is not open enough either vertically or horizontally.
			const T_REG_INFO_EX& loscfg();	//CSR13[7:5]

	/// Loss of signal indication. This bit will be set to 1 when inadequate RX signal (the transition density falls below TDDTHR[2:0]) is detected or eye is not open enough vertically or horizontally after an eye scan, depending on the LOS configuration (RX CSR13[7:5]).
	/// 0 = Adequate RX signal (transitions) or eye opening.
	/// 1 = Inadequate RX signal (transitions) or eye openning.
			const T_REG_INFO_EX& los();	//CSR13[4:4]

	/// Transition density based Loss of signal indication (Clear on read).
	/// 0 = Transition density is above preset threshold.
	/// 1 = Transition density falls below preset threshold.
			const T_REG_INFO_EX& lostran();	//CSR13[3:3]

	/// Eye scan based (vertical) loss-of-signal indication.
	/// 0 = Vertical opening of last inner eye scan is bigger than the threshold.
	/// 1 = Vertical opening of last inner eye scan is less than the threshold.
			const T_REG_INFO_EX& loseyever();	//CSR13[2:2]

	/// Eye scan based (horizontal) loss-of-signal indication.
	/// 0 = Horizontal opening of last inner eye scan is bigger than the threshold.
	/// 1 = Horizontal opening of last inner eye scan is less than the threshold.
			const T_REG_INFO_EX& loseyehor();	//CSR13[1:1]

	/// not used at this memont
			const T_REG_INFO_EX& losana();	//CSR13[0:0]

	/// Set 1 to start an internal 42-bit timer. Self cleared when the timer is full. The timer can be stopped at any time by writing 0 to this register.
			const T_REG_INFO_EX& timecntstart();	//CSR14[15:15]

	/// Select the divider 2 or 4 for PCIE signal and SAS squelch detection 
	/// 0 = select the divider 2
	/// 1 = select the divider 4
			const T_REG_INFO_EX& sigdet_clkdiv();	//CSR14[14:14]

	/// sigdetclk divider(dsclk_digdet_clk_div) controlled by register configure or digial logic for debug
	/// 0 = control by register SIGDET_CLKDIV
	/// 1 = control by digital logic according data-rate switches
			const T_REG_INFO_EX& sigdetclkdiv_pinsel();	//CSR14[13:13]

	/// rx_clk clock domain for eco use and these are floating signals
			const T_REG_INFO_EX& dsrx_rxclk_res();	//CSR14[12:6]

	/// PRBS checker enable.
	/// 0 = Disable (default)
	/// 1 = Enable
			const T_REG_INFO_EX& prbschken();	//CSR14[5:5]

	/// PRBS checker mode.
	/// 0 = Synchronous mode. In this mode, the PRBS checker is synchronized with the input data (i.e., feeding the PRBS checker with the input data).
	/// 1 = Free running mode.
	/// Normally, the PRBS checker should be set in synchronous mode. Once the PRBS checker is synchronized (no error detected), it can be switched to free running mode to prevent error propagation during error detection.
			const T_REG_INFO_EX& prbschkmode();	//CSR14[4:4]

	/// PRBS pattern select for the PRBS checker: 
	/// 0000 = PRBS7 (X7+X6+1)
	/// 0001 = PRBS9 (X9+X5+1)
	/// 0010 = PRBS10 (X10+X7+1)
	/// 0011 = PRBS11 (X11+X9+1)
	/// 0100 = PRBS15 (X15+X14+1)
	/// 0101 = PRBS20 (X20+X17+1)
	/// 0110 = PRBS23 (X23+X18+1)
	/// 0111 = PRBS31 (X31+X28+1)
	/// 1000 = custom pattern 0101 code
	/// 1001 = custom pattern 0011_0011 code
	/// 1010 = custom pattern 00001111_00001111 code
	/// other select will not do check
			const T_REG_INFO_EX& prbschkpatsel();	//CSR14[3:0]

	/// Eye monitor power down control. Active low.
	/// 0 = Eye monitor is powered down (analog)/disabled (digital)
	/// 1 = Eye monitor is powered up (analog)/enabled (digital)
			const T_REG_INFO_EX& eyemonpwrdb();	//CSR15[15:15]

	/// Voltage offset polarity control for ISI calculation.
	/// 0 = Normal
	/// 1 = Invert
			const T_REG_INFO_EX& volofstpol();	//CSR15[14:14]

	/// Monitor eye metric start / stop request for FOM
	/// 0: Stop eye metric for FOM
	/// 1:Enables eye metric measurement
			const T_REG_INFO_EX& rxeyediag_start();	//CSR15[13:13]

	/// Monitor eye metric done for FOM 
	/// 0: eye metric doing 
	/// 1: eye metric done
			const T_REG_INFO_EX& rxeyediag_done();	//CSR15[12:12]

	/// Eye monitor status
	/// 0 = not ready for scan
	/// 1 = ready for scan
			const T_REG_INFO_EX& emready();	//CSR15[11:11]

	/// Eye scan START/STOP control
	/// 0 = Stop
	/// 1 = Start. Self clear after eye scan is done.
			const T_REG_INFO_EX& eyescanstart();	//CSR15[10:10]

	/// Eye scan mode.
	/// 000 = Automatic horizontal inner eye scan
	/// ;001 = Automatic vertical inner eye scan
	/// ;010 = Automatic horizontal outer eye scan
	/// ;011 = Automatic vertical outer eye scan
	/// ;10x = Manual inner eye scan
	/// ;11x = Manual outer eye scan.
	/// 
	/// For automatic horizontal eye scan, eye monitor sweeps horizontally at a certain voltage setting set by MVOLOFST[7:0] to find the inner most eye corners (left and right) at a given BER. The horizontal starting point is programmable through MPHSOFST[7:0].
	/// 
	/// For automatic vertical eye scan, eye monitor sweeps vertically at a certain phase setting set by MPHSOFST[7:0] to find the inner most eye corners (lower and upper) at a given BER. The vertical starting point is controlled by the eye monitor, i.e., not programmable.
	/// 
	/// For manual eye scan, the user has full control over how to measure the eye. Both phase and voltage settings are programmable through MPHSOFST[7:0] and MVOLOFST[7:0] respectively. They need to be set before the scan starts.
			const T_REG_INFO_EX& eyescanmode();	//CSR15[9:7]

	/// Eye scan window select.
	/// 0 = Choose normal eye scan window
	/// 1 = Choose extended eye scan window
	/// 
	/// Note: extended eye scan window is used to get more accurate and fine tuned results. It requires longer time to scan the eye. So it should be used wisely.
			const T_REG_INFO_EX& eyescanwinsel();	//CSR15[6:6]

	/// Eye scan window. EYESCANWIN[5:4] are reserved for future use.
	/// 
	/// For automatic inner eye scan (both horizontal and vertical), it sets the eye scan window, i.e., the number of words to be checked for a mismatch, which is calculated as  32*2^EYESCANWIN[3:0].
	/// 
	/// For automatic outer eye scan, it sets the allowed mismatches limit, which is calculated as 64*8*EYESCANWIN[3:0], within a fixed eye scan window (512 words).
	/// 
	/// For manual inner eye scan, eye monitor keeps comparing the monitor data with the recovered data at certain MPHSOFST[7:0] and MVOLOFST[7:0] settings until a mismatch is found or the scan is stopped by writing EYESCANSTART to '0'.
	/// 
	/// For manual outer eye scan, it sets the measurement window, i.e., the number of words counted for mismatch and ISI error accumulation, which is calculated as 32*8*EYESCANWIN[3:0]].
	/// 
	/// When the extended eye scan window mode is enabled, all above eye scan window and mismatch limit values are doubled.
			const T_REG_INFO_EX& eyescanwin();	//CSR15[5:0]

	/// Eye monitor phase offset (2's complement value).
			const T_REG_INFO_EX& mphsofst();	//CSR16[15:8]

	/// Eye monitor voltage offset (2's complement value).
			const T_REG_INFO_EX& mvolofst();	//CSR16[7:0]

	/// Eyemetric for FOM access abormal indicater
	/// 0: eyemetric for FOM access successfully
	/// 1: eyemetric for FOM access abormal stop and rxeyediag_done is always 0
			const T_REG_INFO_EX& eyemetric_abormal();	//CSR17[14:14]

	/// Mismatch accumulator threshold = 64*MMTHRESHOLD[5:0]
	/// 0x00 = inner eye.
	/// 
	/// Not used at the moment.
			const T_REG_INFO_EX& mmthr();	//CSR17[13:10]

	/// eye-metric for FOM with manual mode
	/// 0: eye-metric for FOM results generated by eyescan with eyemonitor 
	/// 1: eye-metric for FOM results configureg by register (EYEMETRIC_SUM[7:0])
			const T_REG_INFO_EX& eyemetric_manual();	//CSR17[9:9]

	/// eye metric for FOM start/stop request when pcie_stat_pin_en is low.
	/// 0:Stop eye metric measurement for FOM
	/// 1:Start eye metric measurement for FOM
			const T_REG_INFO_EX& eyemetric_start();	//CSR17[8:8]

	/// eye-metric for FOM with manual mode  results and configured by register
	/// the results were configured by register through firmware launch eyescan and scan twice 
	/// Note: when eye-metric for FOM with manual mode, the EYEMETRIC_SUM must prior to or simultaneously EYEMETRIC_MANUAL and EYEMETRIC_START
			const T_REG_INFO_EX& eyemetric_sum();	//CSR17[7:0]

	/// PRBS checker error status. The bit is set to 1 when at least one error is detected. Status is latched until being read (clear on read).
	/// 0 = No errors detected.
	/// 1 = At least 1 error detected by the PRBS detector.
			const T_REG_INFO_EX& prbserr();	//CSR18[15:15]

	/// PRBSCNTEXP[3:0] gives the exponent portion of the 26 bit error counter. (clear on read)
	/// 0 = most significant bit of PRBSCNT[10:0] is position 10 in the complete count
	/// ¡­¡­¡­¡­¡­¡­..
	/// 15 = most signficant bit of PRBSCNT[10:0] is position 25 in the complete count
			const T_REG_INFO_EX& prbscntexp();	//CSR18[14:11]

	/// PRBS error count
			const T_REG_INFO_EX& prbscnt();	//CSR18[10:0]

	/// Left or lower corner of the most recent automatic horizontal/vertical eye scan.
			const T_REG_INFO_EX& eyecor0();	//CSR19[15:8]

	/// Right or upper corner of the most recent automatic horizontal/vertical eye scan.
			const T_REG_INFO_EX& eyecor1();	//CSR19[7:0]

	/// ISI accumulator 0 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr0();	//CSR20[15:0]

	/// ISI accumulator 1 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr1();	//CSR21[15:0]

	/// ISI accumulator 2 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr2();	//CSR22[15:0]

	/// ISI accumulator 3 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr3();	//CSR23[15:0]

	/// ISI accumulator 4 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr4();	//CSR24[15:0]

	/// ISI accumulator 5 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr5();	//CSR25[15:0]

	/// Activates reference circuit required for termination calibration.
	/// 0 = Deactivated
	/// 1 = Reference circuit is powered-up
			const T_REG_INFO_EX& rxtermcalen();	//CSR26[15:15]

	/// Direction control for RX termination calibration.
	/// 0 = TBD
	/// 1 = TBD
			const T_REG_INFO_EX& rxtermcaldir();	//CSR26[14:14]

	/// 14-bit rx termination resistor trimming control.
	/// MSB = 1  (default). Activate termination.
	/// MSB = 0 For high impedance.  All other bits must be set to '0' for high impedance.  Invalid mission-mode setting.
	/// 10000000000000 = 60 Ohm
	/// 10000000000001 = 58.5 Ohm
	/// 10000000000011 = 55.7 Ohm
	/// 10000000000111 = 53.22 Ohm
	/// 10000000001111 = 50.9 Ohm
	/// 10000000011111 = 48.79 Ohm
	/// 10000000111111 = 46.84 Ohm
	/// 10000001111111 = 45 Ohm
	/// 10000011111111 = 43.37 Ohm
	/// 10000111111111 = 41.82 Ohm
	/// 10001111111111 = 40.37 Ohm
	/// 10011111111111 = 39 Ohm
	/// 10111111111111 = 37.7 Ohm
	/// 11111111111111 = 36.59 Ohm
	/// 
	/// Above values are guidance.  Not intended to define precise analog values across real samples.
			const T_REG_INFO_EX& rxtermcal();	//CSR26[13:0]

	/// RX calibration mode. Switching from manual mode to automatic mode restarts the calibration process.
	/// 0 = Automatic calibration
	/// 1 = Manual calibration
			const T_REG_INFO_EX& rxcalmode();	//CSR27[15:15]

	/// Data Slice calibration start control. Used only in automatic and semi-automatic modes.
	/// 0 = Do not start data slice calibrations
	/// 1 = Start all data slice calibrations (automatic way)
			const T_REG_INFO_EX& dscalstart();	//CSR27[14:14]

	/// RX calibration start control. Used only in automatic and semi-automatic modes.
	/// 0 = Do not start RX calibrations
	/// 1 = Start RX calibrations self clean once rxcal_done is 1
			const T_REG_INFO_EX& rxcalstart();	//CSR27[13:13]

	/// rx termination floating control.
	/// 0 = Termination floating disable--low impedance.
	/// 1 = Termination floating enable---high impedance.
	/// Notes£ºwhen Termination is in floating, the received data also transfered, not fixed 0 or 1,  the SOC need attention it.
			const T_REG_INFO_EX& rxterm_floating_en();	//CSR27[12:12]

	/// signal loss detected window setting and it is available in PCIE 2.5 or 5G
	/// the detected window is equal to 2^(SIGDET_WIN_PCIE+2)
			const T_REG_INFO_EX& sigdet_win_pcie();	//CSR27[11:8]

	/// Latch offset calibration enable
	/// 0 = Skip offset calibration for center, edge and monitor channels' latches during the automatic calibration process
	/// 1 = Do offset calibration for center, edge and monitor channels' latches during the automatic calibration process
			const T_REG_INFO_EX& rxdatalatchcalen();	//CSR27[7:7]

	/// Direction control for RX offset calibration.
	/// 0 = TBD
	/// 1 = TBD
			const T_REG_INFO_EX& rxofstcaldir();	//CSR27[6:6]

	/// RX offset calibration select. It chooses analog circuit for offset calibration. Only applies to manual offset calibration mode.
	/// 000000 = No block is selected for offset calibration
	/// 000001 = Select CTLE stage 1 which is the CTLE boost stage 1
	/// 000010 = Select CTLE stage 2 which is the CTLE gain stage 1
	/// 000011 = Select CTLE stage 3 which is the CTLE boost stage 2
	/// 000100 = Select CTLE stage 4 which is the CTLE gain stage 2
	/// 000101 = Select CTLE stage 5 which is the CTLE boost stage 3
	/// 000110 = Select CTLE stage 6 which is the CTLE gain stage 3
	/// 000111 = Select DFE center channel even summer
	/// 001000 = Select DFE center channel odd summer
	/// 001001 = Select center channel even sense amplifier
	/// 001010 = Select center channel odd sense amplifier
	/// 001011 = Select edge channel even sense amplifier
	/// 001100 = Select edge channel odd sense amplifier
	/// 001101 = Select monitor even stage 1
	/// 001110 = Select monitor odd stage 1
	/// 001111 = Select monitor even stage 2
	/// 010000= Select monitor odd stage 2
	/// 010001 = Select monitor channel even sense amplifier
	/// 010010 = Select monitor channel odd sense amplifier
	/// 011111= Select rxctle replica
	/// 100000 = Select rxpa replica
	/// 100001 = Select sigdet calibration
	/// 100010 = Select rxterm calibration
	/// 100011 = Select comparator calibration
			const T_REG_INFO_EX& rxofstsel();	//CSR27[5:0]

	/// Offset control for the CTLE gain stage 1. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude. 
	/// 00000; 10000 = no offset.
	/// 01111; 11111 = full scale.
			const T_REG_INFO_EX& ctleofst1();	//CSR28[14:10]

	/// Offset control for the CTLE boost stage 1. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
			const T_REG_INFO_EX& ctleofst2();	//CSR28[9:5]

	/// Offset control for the CTLE gain stage 2. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
			const T_REG_INFO_EX& ctleofst3();	//CSR28[4:0]

	/// Offset control for the CTLR boost stage 2. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
			const T_REG_INFO_EX& ctleofst4();	//CSR29[14:10]

	/// Offset control for the CTLE gain stage 3. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
			const T_REG_INFO_EX& ctleofst5();	//CSR29[9:5]

	/// Offset control for the CTLE boost stage 3. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
			const T_REG_INFO_EX& ctleofst6();	//CSR29[4:0]

	/// signal loss calibration enable signal
	/// 0 = signal loss calibration disable
	/// 1 = signal loss calibration enable
			const T_REG_INFO_EX& sigdet_cal_en();	//CSR30[15:15]

	/// Used to control  signal detection comparator offset calibration (Vppd):
	/// 000000 : 3mV
	/// 000001: 6mV
	/// ¡­¡­¡­.
	/// 100000:  81mV
	/// ¡­¡­¡­
	/// 111111:  162mV
			const T_REG_INFO_EX& sigdet_offset();	//CSR30[14:10]

	/// Offset control for the DFE center channel even summer. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
			const T_REG_INFO_EX& dfeevnsumofst();	//CSR30[9:5]

	/// Offset control for the DFE center channel odd summer. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
			const T_REG_INFO_EX& dfeoddsumofst();	//CSR30[4:0]

	/// Monitor Offset control for the center channel even sense amplifier calibration feedback
			const T_REG_INFO_EX& rxctrensampofftrig();	//CSR31[15:15]

	/// Offset control for the center channel even sense amplifier. Used for manual offset calibration.
	/// MSB is signed bit, the other five bits are magnitude.
			const T_REG_INFO_EX& cevnsnsampofst();	//CSR31[14:9]

	/// offset enable control for the center channel even sense amplifier. Used for manual offset calibration.
	/// 0= disable
	/// ;1= enable
			const T_REG_INFO_EX& rxctrensampencal();	//CSR31[8:8]

	/// rx center, edge and monitor sense amplifier calibration direction control
			const T_REG_INFO_EX& rxsnsampdir();	//CSR31[7:7]

	/// signal loss calibrtion direction control signal
	/// 0 = TBD
	/// 1 = TBD
			const T_REG_INFO_EX& rxsigdetdir();	//CSR31[6:6]

	/// rx termination calibration targe resist value choice.
	/// 00 = 50 Ohm
	/// 01 = 45 Ohm
	/// 10 = 42.5 Ohm
	/// 11 = NA
			const T_REG_INFO_EX& rxterm_ressel();	//CSR31[5:4]

	/// recover clock divider choice for parallel banwidth; 
	/// 0 = divider 8 for ASIC 16bit
	/// 1 = divider 16 for ASIC 32bit
			const T_REG_INFO_EX& wordclk_divsel();	//CSR31[3:3]

	/// switch capacitor resistor enable control 
	/// 0 = disable switch capacitor resistor block and 
	/// 1 = enable switch capacitor resistor block
			const T_REG_INFO_EX& rxctle_scresen();	//CSR31[2:2]

	/// attenuator block input low frequnecy clock divider coefficents
	/// 0 = divier 75
	/// 1 = divider 40
			const T_REG_INFO_EX& rxctle_scres_clk_div();	//CSR31[1:1]

	/// Select the clock1 and clock2 delay for sata/sas
	/// 0 = PCIE/common mode
	/// 1 = SAS mode
			const T_REG_INFO_EX& rx_sigdet_bld_dly_sel();	//CSR31[0:0]

	/// monitor Offset control for the center channel odd sense amplifier calibration feedback
			const T_REG_INFO_EX& rxctronsampofftrig();	//CSR32[15:15]

	/// Offset control for the center channel odd sense amplifier. Used for manual offset calibration.
	/// MSB is signed bit, the other five bits are magnitude.
			const T_REG_INFO_EX& coddsnsampofst();	//CSR32[14:9]

	/// offset enable control for the center channel odd sense amplifier. Used for manual offset calibration.
	/// 0= disable
	/// ;1= enable
			const T_REG_INFO_EX& rxctronsampencal();	//CSR32[8:8]

	/// RX AC couple burst mode attenuation setting
			const T_REG_INFO_EX& bm_ac_r_sel();	//CSR32[7:6]

	/// attenuator middle band equalization resistor select ;
			const T_REG_INFO_EX& rxctle_mbersel();	//CSR32[5:3]

	/// monitor  Offset control for edge channel even sense amplifier calibration feedback
			const T_REG_INFO_EX& rxedgensampofftrig();	//CSR33[15:15]

	/// Offset control for the edge channel even sense amplifier. Used for manual offset calibration.
	/// MSB is signed bit, the other five bits are magnitude.
			const T_REG_INFO_EX& eevnsnsampofst();	//CSR33[14:9]

	/// offset enable control for the edge channel even sense amplifier. Used for manual offset calibration.
	/// 0= disable
	/// ;1= enable
			const T_REG_INFO_EX& rxedgensampencal();	//CSR33[8:8]

	/// analog spare signal to RO register for future use
	/// when DS puts CS slave south, the value of ds_spare_o[0] is zero, when DS puts CS slave north, the value of ds_spare_o[0] is high.
			const T_REG_INFO_EX& ds_spare_o();	//CSR33[7:0]

	/// monitor Offset control for the edge channel odd sense amplifier calibration feedback
			const T_REG_INFO_EX& rxedgonsampofftrig();	//CSR34[15:15]

	/// Offset control for the edge channel odd sense amplifier. Used for manual offset calibration.
	/// MSB is signed bit, the other five bits are magnitude.
			const T_REG_INFO_EX& eoddsnsampofst();	//CSR34[14:9]

	/// offset enable control for the edge channel odd sense amplifier. Used for manual offset calibration.
	/// 0= disable
	/// ;1= enable
			const T_REG_INFO_EX& rxedgonsampencal();	//CSR34[8:8]

	/// Monitor Offset control for the monitor channel even sense amplifier feedback
			const T_REG_INFO_EX& rxmonensampofftrig();	//CSR35[15:15]

	/// Offset control for the monitor channel even sense amplifier. Used for manual offset calibration.
	/// MSB is signed bit, the other five bits are magnitude.
			const T_REG_INFO_EX& mevnsnsampofst();	//CSR35[14:9]

	/// offset enable control for the monitor channel even sense amplifier. Used for manual offset calibration.
	/// 0= disable
	/// ;1= enable
			const T_REG_INFO_EX& rxmonensampencal();	//CSR35[8:8]

	/// monitor Offset control for the monitor channel odd sense amplifier calibration feedback
			const T_REG_INFO_EX& rxmononsampofftrig();	//CSR36[15:15]

	/// Offset control for the monitor channel odd sense amplifier. Used for manual offset calibration.
	/// MSB is signed bit, the other five bits are magnitude.
			const T_REG_INFO_EX& moddsnsampofst();	//CSR36[14:9]

	/// offset enable control for the monitor channel odd sense amplifier. Used for manual offset calibration.
	/// 0= disable
	/// ;1= enable
			const T_REG_INFO_EX& rxmononsampencal();	//CSR36[8:8]

	/// Offset control for the monitor channel even stage1. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
			const T_REG_INFO_EX& eyest1evnofst();	//CSR36[7:3]

	/// Offset control for the monitor channel even stage2. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
			const T_REG_INFO_EX& eyest2evnofst();	//CSR37[15:11]

	/// Squelch detection threshold setting when PMA_MODE is SAS mode.
			const T_REG_INFO_EX& squelch_det_thr();	//CSR37[10:0]

	/// this register is floating for eco use
			const T_REG_INFO_EX& dsrx_cor_res();	//CSR38[15:10]

	/// Offset control for the monitor channel odd stage1. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
			const T_REG_INFO_EX& eyest1oddofst();	//CSR38[9:5]

	/// Offset control for the monitor channel odd stage2. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
			const T_REG_INFO_EX& eyest2oddofst();	//CSR38[4:0]

	/// monitor Offset calibration code for op-amp in load regulation loop feedback
			const T_REG_INFO_EX& rxctlerepofftrig();	//CSR39[15:15]

	/// Direction control for replica calibration.
	/// 0 = TBD
	/// 1 = TBD
			const T_REG_INFO_EX& replicacaldir();	//CSR39[12:12]

	/// Enable self-calibration of op-amp offset. Offset FSM monitors RXCTLEREPOFFTRIG.
			const T_REG_INFO_EX& rxctlerepcalen();	//CSR39[11:11]

	/// Offset calibration code for op-amp in load regulation loop. Sign-magnitude code.
			const T_REG_INFO_EX& rxctlerepcalcode();	//CSR39[10:6]

	/// Reference voltage selection for CTLE load resistor regulation loop.  Simultaneoulsy affects multiple performance parameters like gain, bandwidth, and slope.
	/// 
	/// 011 = higher BW, lower DC gain for CTLE.
	/// 100 = default.
	/// 101= highest dc gain. Recommended setting for limiting amplifier 
	/// configuration.
	/// 
	/// Settings 000/001/010, and 110/111 are used for debug.
			const T_REG_INFO_EX& rxctlerefsel();	//CSR39[5:3]

	/// Control voltage selection for CTLE loads.                                                                000 = generated by regulator.
	/// All other settings are invalid. (test modes).
			const T_REG_INFO_EX& rxctleloadsel();	//CSR39[2:0]

	/// reserved between analog and digital interface
			const T_REG_INFO_EX& rxspare();	//CSR40[15:8]

	/// signal loss and squelch detection threshold select control signal
	/// 0 = controlled by digital logic whith datarate
	/// 1 = controlled by register(SIGDET_THR_SEL_MAN)
			const T_REG_INFO_EX& sigdet_manual();	//CSR40[7:7]

	/// signal loss  threshold and detect window select signal with manul mode
	/// 0 =  PCIE 2.5 or 5G
	/// 1 = SAS/common/PCIE 8G mode
			const T_REG_INFO_EX& sigdet_thr_sel_man();	//CSR40[6:6]

	/// monitor signal loss detection threshold and detect window select signal
	/// 1 =  PCIE 2.5 or 5G
	/// 1 = SAS/common/PCIE 8G mode
			const T_REG_INFO_EX& sigdet_thr_sel();	//CSR40[5:5]

	/// monitor the value of ctlepreset that from PCS
			const T_REG_INFO_EX& ctlepreset();	//CSR40[2:0]

	/// 
			const T_REG_INFO_EX& rxparepofftrig();	//CSR41[15:15]

	/// Enable self-calibration of opamp in PA replica load regulation.
			const T_REG_INFO_EX& rxpacalen();	//CSR41[11:11]

	/// Offset calibration code for op-amp in load regulation loop. Sign-magnitude code.
			const T_REG_INFO_EX& rxpacalcode();	//CSR41[10:6]

	/// Reference voltage selection for pre-amplifier load resistor regulation loop.  Simultaneoulsy affects multiple performance parameters.
	/// 
	/// 011 = default gain.
	/// 
	/// Other settings are for test purposes only.
			const T_REG_INFO_EX& rxparefsel();	//CSR41[5:3]

	/// Control voltage selection for latch load.                                                                0 = generated by regulator.
			const T_REG_INFO_EX& rxpaloadsel();	//CSR41[2:0]

	/// RX calibration comparator power down control
	/// 0 = power down
	/// 1 = power up
			const T_REG_INFO_EX& dsrxlowoffpwrdb();	//CSR42[15:15]

	/// RX calibration comparator enable signal
	/// 0 = disable
	/// 1 = enable
			const T_REG_INFO_EX& dsrxlowoffcal();	//CSR42[14:14]

	/// RX calibration code for comparator
			const T_REG_INFO_EX& dsrxlowoffctrl();	//CSR42[13:8]

	/// Direction control for RX lowoff comparator calibration.
	/// 0 = TBD
	/// 1 = TBD
			const T_REG_INFO_EX& rxlowoffcaldir();	//CSR42[7:7]

	/// monitor RX calibration comparator feedback
			const T_REG_INFO_EX& dsrxlowoffout();	//CSR42[6:6]

	/// monitor RX calibration control code value
			const T_REG_INFO_EX& rxcalread();	//CSR42[5:0]

	/// This bit allows the user to change the polarity of the Eye Monitor offset voltage direction.
	/// 0: Default, A positive increase in MVOLOFST[7:0] will result in positive voltage offset
	/// 1:Inverted,A positive increase in MVOLOFST[7:0] will result in negative voltage offset (V101)
	/// not used
			const T_REG_INFO_EX& rxeye_polarityswitch();	//CSR43[15:15]

	/// ctle preset decoder from PCS  reponse enable signal for ctle_est1~3_boost and ctle_gst1~3_gain value
	/// 0: disable reponse and the value are configured by register csr_ctlebst1~3 and csr_ctleactgn1~3
	/// 1: enable reponse and the values are decoder of ctlepreset
			const T_REG_INFO_EX& ctlepreset_en();	//CSR43[14:14]

	/// TX to TX serial loopback atb control signals
			const T_REG_INFO_EX& txrxserlpbkatbctrl();	//CSR43[13:12]

	/// 
			const T_REG_INFO_EX& rxlowoffatbctrl();	//CSR43[11:10]

	/// RX mux selection for access to low-offset comparator, and second level atb bus mux.
	/// 00 = no select.
	/// 01 = selects RX otbp bus
	/// 10 = selects RX otbm bus
	/// 11 = selects 'vss' reference.
			const T_REG_INFO_EX& rxatbmuxsel();	//CSR43[9:8]

	/// un-used.
			const T_REG_INFO_EX& rxatbsel();	//CSR43[7:0]

	/// squelch detection window. It can be programmed to 2^2 , 2^3,2^4,2^5,2^6,2^7 ,2^8 ,2^9  and 2^10 
	/// 0X0: 4 
	/// 0X1: 8 
	/// 0X2:  16 
	/// 0X3: 32
	/// 0X4: 64 
	/// 0X5: 128
	/// 0X6: 256 
	/// 0X7: 512 
	/// 0X8: 1024 
	/// Notes: it is only available in SAS mode.
			const T_REG_INFO_EX& squelch_detwin();	//CSR44[15:12]

	/// 0 = AC-JTAG receiver is controlled by pins
	/// ;1 = AC-JTAG receiver is controlled by register.
			const T_REG_INFO_EX& jtagsel();	//CSR44[11:11]

	/// 
			const T_REG_INFO_EX& jtagoutp();	//CSR44[10:10]

	/// 
			const T_REG_INFO_EX& jtagoutm();	//CSR44[9:9]

	/// JTAG power down control. Active low.
	/// TBD
			const T_REG_INFO_EX& jtagpwrdb();	//CSR44[8:8]

	/// JTAG AC mode enable
	/// TBD
			const T_REG_INFO_EX& jtagacmodeen();	//CSR44[7:7]

	/// 
			const T_REG_INFO_EX& jtaginitclk();	//CSR44[6:6]

	/// 
			const T_REG_INFO_EX& jtaginitp();	//CSR44[5:5]

	/// 
			const T_REG_INFO_EX& jtaginitm();	//CSR44[4:4]

	/// JTAG hysteresis thrshold control
	/// TBD
			const T_REG_INFO_EX& jtaghystadj();	//CSR44[3:2]

	/// JTAG threshold control
	/// 00: 100mv
	/// ;01:110mc
	/// ;10:120mv
	/// ;11:130mv
			const T_REG_INFO_EX& jtagthadj();	//CSR44[1:0]

	/// Monitor center and edge early signal
			const T_REG_INFO_EX& ceearly();	//CSR45[15:15]

	/// Monitor center and edge late signal
			const T_REG_INFO_EX& celate();	//CSR45[14:14]

	/// Monitor center and monitor early signal
			const T_REG_INFO_EX& cmearly();	//CSR45[13:13]

	/// Monitor center and monitor late signal
			const T_REG_INFO_EX& cmlate();	//CSR45[12:12]

	/// monitor cdr coarsealigndone status
	/// 0=coarsealign doing
	/// 1= coarsealign done
			const T_REG_INFO_EX& cdr_coarsealigndone();	//CSR45[11:11]

	/// monitor sscdr coarsealigndone status
	/// 0=coarsealign doing
	/// 1= coarsealign done
			const T_REG_INFO_EX& sscdr_coarsealigndone();	//CSR45[10:10]

	/// Edge channel sleep control.
	/// 0 = Mission mode
	/// 1 = Sleep mode
			const T_REG_INFO_EX& edgesleep();	//CSR45[8:8]

	/// Center-Edge coarse align enable.
	/// 0 = Disable
	/// 1 = Enable
			const T_REG_INFO_EX& ecoarsealignen();	//CSR45[7:7]

	/// Center-Edge coarse alignment step.
	/// 000 = +48;   100 = -48
	/// ;001 = +54;   101 = -54
	/// ;010 = +60;   110 = -60
	/// ;011 = +64;   111 = -64.
			const T_REG_INFO_EX& ecoarsealignstep();	//CSR45[6:4]

	/// Monitor-Center coarse align enable. Only applicable when eye monitor is enabled.
	/// 0 = Disable
	/// 1 = Enable
			const T_REG_INFO_EX& mcoarsealignen();	//CSR45[3:3]

	/// Monitor-Center coarse alignment step.
	/// 000 = +48;   100 = -48
	/// ;001 = +54;   101 = -54
	/// ;010 = +60;   110 = -60
	/// ;011 = +64;   111 = -64.
			const T_REG_INFO_EX& mcoarsealignstep();	//CSR45[2:0]

	/// This register contains the present binary phase setting of the center channel phase interpolator.
			const T_REG_INFO_EX& cphsval();	//CSR46[14:8]

	/// 10bit period pattern data density detect results
	/// 0 = pattern is not 10bit period data pattern
	/// 1 = pattern is the 10bit perido data pattern
			const T_REG_INFO_EX& pat_per_los();	//CSR46[7:7]

	/// This register contains the present binary phase setting of the edge channel phase interpolator.
			const T_REG_INFO_EX& ephsval();	//CSR46[6:0]

	/// Not used.
			const T_REG_INFO_EX& misierrdone();	//CSR47[15:15]

	/// This register contains the present binary phase setting of the monitor channel phase interpolator.
			const T_REG_INFO_EX& mphsofstval();	//CSR47[14:8]

	/// Eye monitor voltage offset.
			const T_REG_INFO_EX& mvolofstval();	//CSR47[7:0]

	/// Mismatch count which is calculated as,  when MMCNT[13:11] is equal to zero, MMCNT[10:0]x2^MMCNT[13:11]. Otherwise, MMCNT=2^(MMCNT[13:11]) * (1024+MMCNT[10:0]/2)
	/// Note: MMCNT[15:14] are not used.
			const T_REG_INFO_EX& mmcnt();	//CSR48[15:0]

	/// TIMEREXP[4:0] gives the exponent portion of the internal 42-bit timer.
	/// 0 = MSB of the timer is at position 10 in the complete count
	/// 1 = MSB of the timer is at position 11 in the complete count
	/// 2 = MSB of the timer is at position 12 in the complete count
	/// ¡­¡­¡­¡­¡­¡­..
	/// 31 = MSB of the timer is at position 41 in the complete count
			const T_REG_INFO_EX& timerexp();	//CSR49[15:11]

	/// TIMER[10:0], together with the exponent portion (TIMEREXP[4:0]), gives the cycle count of the counting clock. TIMER[10:0] is only the lower 11-bit portion of the internal 42-bit timer.
			const T_REG_INFO_EX& timer();	//CSR49[10:0]

	/// squelch detection enable signal
	/// 0 = squelch detection is disable
	/// 1 = squelch detection is enable
	/// the user enable this function until ds calibration done
			const T_REG_INFO_EX& squelch_det_en();	//CSR50[15:15]

	/// Configuration of timer for waiting, which is the cycles of reference clock.
			const T_REG_INFO_EX& rxcal_timer_value();	//CSR50[14:5]

	/// Configuration of divider in timer, for debugging.
			const T_REG_INFO_EX& rxcal_timer_div_value();	//CSR50[4:2]

	/// Enable the divider in timer, for debugging.
	/// 0 = disable
	/// 1 = enable
			const T_REG_INFO_EX& rxcal_timer_div_en();	//CSR50[1:1]

	/// Stop timer, for debugging.
	/// 0 = normal
	/// 1 = stop the timer
			const T_REG_INFO_EX& rxcal_timer_stop();	//CSR50[0:0]

	/// This register contains the present binary phase setting of the center channel phase  interpolator of SSC CDR
			const T_REG_INFO_EX& cphase_ssc();	//CSR51[15:10]

	/// eyescan ready indicator signal and when read it is high, it indicates eyescan can be started.
			const T_REG_INFO_EX& eyescan_rdy();	//CSR51[9:9]

	/// when data-rate swithed in PCIE/SATA mode, the SSCDR soft reset reset through data-rate swithed, and release through alos in PCIE mode, or squelch los in SATA mode
	/// 0 = SSCDR soft reset release through data-rate swithed finished
	/// 1 = SSCDR soft reset release through alos or squelch los is low.
			const T_REG_INFO_EX& sscdr_sftrst_ctrl();	//CSR51[8:8]

	/// Fast-PI-Based SSC CDR demux Mode
	/// 0: demux=4, Max freq offset 6000ppm, Max data rate 8.0Gbps
	/// 1: demux=8, only SAS 12Gbps needed, Max freq offset 3000ppm, Max data rate 12.0Gbps
			const T_REG_INFO_EX& sscdr_demux_mode();	//CSR51[7:7]

	/// SSC CDR internal signal probe request
	/// 0: keep unchanged
	/// ;1: read sscdr signal request.
			const T_REG_INFO_EX& sscdr_atb_req();	//CSR51[6:6]

	/// This register contains the present binary phase setting of the edge channel phase interpolator of SSC CDR
			const T_REG_INFO_EX& ephase_ssc();	//CSR51[5:0]

	/// This register contains the present binary phase setting of the monitor channel phase interpolator of SSC CDR
			const T_REG_INFO_EX& mphase_ssc();	//CSR52[15:10]

	/// select CDR internal bus to probe at csr_sscdr_atb_out[6:0]
	/// 3¡¯b000: loop2_value[6:0]
	/// 3¡¯b001: c_eoffset[5:0]
	/// 3¡¯b010: m_eoffset[5:0]
	/// 3¡¯b011: bitslip/ephase_adj/ /coarsealign
	/// 3¡¯b1xx: for future use
			const T_REG_INFO_EX& sscdr_atb_sel();	//CSR52[9:7]

	/// Monitor SSC CDR internal test bus
			const T_REG_INFO_EX& sscdr_atb_out();	//CSR52[6:0]

	/// Fast-PI-Based SSC CDR integral gain
	/// note: the mininal value is must equal to 4
			const T_REG_INFO_EX& sscdr_intg_gain();	//CSR53[15:11]

	/// Fast-PI-Based SSC CDR proportional gain
			const T_REG_INFO_EX& sscdr_prop_gain();	//CSR53[10:6]

	/// Fast-PI-Based SSC CDR 2nd loop saturate value
			const T_REG_INFO_EX& sscdr_loop2_sat();	//CSR53[5:0]

	/// eye metric scan mode for FOM 
	/// 000=automatic horizontal inner eye scan
	/// ;001=automatic vertical inner eye scan
	/// ;others: reversed
			const T_REG_INFO_EX& eyemetric_scanmode();	//CSR54[15:13]

	/// eyemetric scan window select for FOM
	/// 0=choose normal eye scan window
	/// ;1=choose extended eye scan window.
			const T_REG_INFO_EX& eyemetric_scanwinsel();	//CSR54[12:12]

	/// eyemetric scan window for FOM
	/// For auto inner eye scan(both horizontal and vertical), it sets the eye scan window, the number of words to be checked for a mismatch, which is calculated as 32*2^EYEMETRIC_SCANWIN.
	/// For auto outer eye scan, it sets the allowed mismatches limit, which is calculated as 64*8*EYEMETRIC_SCANWIN,within a fixed eye scan window (512 words)
			const T_REG_INFO_EX& eyemetric_scanwin();	//CSR54[11:8]

	/// Monitor eye-mertric results for FOM  
	/// provide the PHY link equalization evaluation Fugure of Merit value. The value is encoded as an integer from 0 to 255.
	/// note:
	///  RXEYEDIAG_STAT=(EYECOR1_FST-EYECORNER0_FST) +(EYECOR1_SEC-EYECOR0_SEC) when eyemetric_manual is 0
	/// when eye-metric with manual mode, it value is configured by register EYEMETRIC_SUM
			const T_REG_INFO_EX& rxeyediag_stat();	//CSR54[7:0]

	/// Eye monitor phase offset (2's complement value).
	/// Only used eyemetric start  for FOM valid and the first eyescan.
			const T_REG_INFO_EX& mphsofst_fst();	//CSR55[15:8]

	/// Eye monitor voltage offset (2's complement value).
	/// Only used eyemetric start valid for FOM and the first eyescan.
			const T_REG_INFO_EX& mvolofst_fst();	//CSR55[7:0]

	/// Eye monitor phase offset (2's complement value).
	/// Only used eyemetric start for FOM valid and the second eyescan.
			const T_REG_INFO_EX& mphsofst_sec();	//CSR56[15:8]

	/// Eye monitor voltage offset (2's complement value).
	/// Only used eyemetric start for FOM  valid and the second eyescan.
			const T_REG_INFO_EX& mvolofst_sec();	//CSR56[7:0]

	/// Left or lower corner of the most recent automatic horizontal/vertical eye scan.
	/// Only used eyemetric start valid for FOM and the first eyescan.
			const T_REG_INFO_EX& eyecor0_fst();	//CSR57[15:8]

	/// Right or upper corner of the most recent automatic 
	/// horizontal/vertical eye scan.
	/// Only used eyemetric start valid for FOM and the first eyescan.
			const T_REG_INFO_EX& eyecor1_fst();	//CSR57[7:0]

	/// Left or lower corner of the most recent automatic horizontal/vertical eye scan.
	/// Only used eyemetric start valid for FOM  and the second eyescan.
			const T_REG_INFO_EX& eyecor0_sec();	//CSR58[15:8]

	/// Right or upper corner of the most recent automatic 
	/// horizontal/vertical eye scan.
	/// Only used eyemetric start valid for FOM  and the second eyescan.
			const T_REG_INFO_EX& eyecor1_sec();	//CSR58[7:0]

	/// Adjust the signal detection level (vlv  Vppd):
	/// 000000 : 20mV
	/// 000001: 26mV
	/// ¡­¡­¡­.
	/// 100000:  192mV
	/// ¡­¡­¡­
	/// 111111:  384mV
			const T_REG_INFO_EX& sigdet_vlv();	//CSR59[15:9]

	/// rx signal detect power down.
	/// 0=power down
	/// 1=power up
			const T_REG_INFO_EX& rxsigdet_pwrdnb();	//CSR59[8:8]

	/// configure the clock divider rate from  high speed recovery clock, which frequency is the same as spine clock. 
	/// divide reference clock for  different XPON mode
	/// 000=divide  66;   (for 10GXEPON/10G EPON) 
	/// 001=divide 32;   (for XGPON)
	/// 01x=divide 16;   (for GPON/EPON/2.5GPON)
	/// 1xx=adjustable  divide rate configure, the rate is setting through the register RECCLKDIV[5:0]
			const T_REG_INFO_EX& rxrecclk_sel();	//CSR59[7:5]

	/// BCDR controll signal source select 
	/// 0 =  BCDR controll signal comes from ASIC pin ana_bmen_n/ bm_ac_r_sel,
	/// 1 = BCDR controll signal comes from register csr6_ana_bmen_en/ csr32_bm_ac_r_sel
			const T_REG_INFO_EX& bcdr_pin_en();	//CSR59[4:4]

	/// decoder the  receiver ctle boost_st1~3 and gain_st1~3 parameter value when pcie_stat_pin_en is low.
			const T_REG_INFO_EX& ctleparset();	//CSR59[2:0]

	/// signal loss detection enable
	/// 0: disable squelch or signal loss detection,
	/// 1: enable squelch or signal loss detection.
			const T_REG_INFO_EX& sigdet_enable();	//CSR60[15:15]

	/// signal loss(alos) detection window in PCIE 8G/Common/SAS mode. It can be programmed to 2^2 , 2^3,2^4,2^5,2^6,2^7 ,2^8 ,2^9  and 2^10 
	/// 0X0: 4 
	/// 0X1: 8 
	/// 0X2:  16 
	/// 0X3: 32
	/// 0X4: 64 
	/// 0X5: 128
	/// 0X6: 256 
	/// 0X7: 512 
	/// 0X8: 1024
	/// Notes£ºwhen worked in common mode, the default value is  0x6, the pcie 8G mode, the default value is 0x4, the sas mode, the default value is 0x0.
			const T_REG_INFO_EX& sigdet_win();	//CSR60[14:11]

	/// signal loss detection threshold only used in pice 2.5G/5G working mode
			const T_REG_INFO_EX& sigdet_thr_s1();	//CSR60[10:0]

	/// PCIE signal loss detection output
	/// 0-indicate signal level is above preset threshold for PCIE
	/// 1- indicate signal level falls below preset threshold for PCIE
	/// note:  it is only available for PCIE or common mode.
			const T_REG_INFO_EX& sigdet_los();	//CSR61[15:15]

	/// Fast-PI-Based SSC CDR reset control
	/// 1=At loss of signal, reset the CDR
	/// 0=Disregard LOS
			const T_REG_INFO_EX& sscdr_rst_by_sigdet();	//CSR61[14:14]

	/// eye-metric for FOM generation reponse control signals
	/// 0: eye-metric for FOM generation is not response and the signals eyescanstart, eyescanmode, eyescanwinsel and eyescanwin is available.
	/// 1: eye-metric for FOM generation is response and eyemetric_start, eyemetric_scanwin, eyemeric_scanmode and eyemetric_scanwinsel is available
			const T_REG_INFO_EX& remotetx();	//CSR61[13:13]

	/// SAS/SATA squelch detection output
	/// 0-indicate 1.5Gbps OOB-signal for SAS on receive pins
	/// 1- indicate electrical idle for SAS on receive pins
	/// note: it is only available for SAS  mode.
			const T_REG_INFO_EX& squelch_det();	//CSR61[12:12]

	/// signal and squelch detection soft reset 
	/// 0: reset 
	/// 1: release
			const T_REG_INFO_EX& sigdet_rstb();	//CSR61[11:11]

	/// signal loss threshold used in  SAS mode, Common mode or PCIE 8G mode
	/// Note: when worked in SAS mode, the default value is 0x2, when worked in Common mode, the default value is 0x40, when worked in PCIE 8G mode, the defaule value is 0x14
			const T_REG_INFO_EX& sigdet_thr_s2();	//CSR61[10:0]

	/// 10bit period pattern data density detect window setting
	/// 00 = 2^4
	/// 01 = 2^5
	/// 10 = 2^6
	/// 11 = 2^7
			const T_REG_INFO_EX& pat_det_win();	//CSR62[15:14]

	/// monitor sscdr_cmphase in  sscdr cmphase generate when eyescan doing in digital part
			const T_REG_INFO_EX& sscdr_cmphase();	//CSR62[13:8]

	/// emphase configuration when cmphase and emphase async.
			const T_REG_INFO_EX& emphase_delta();	//CSR62[7:0]
			bool get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos);
	};
public:
	_REG_INFO REG_INFO;

	uint csr[DS_RX_CSR_NUM];


	//CSR0[15:15]
	DS_rxRegs& setrxpwrdb(uint val);
	uint getrxpwrdb();

	//CSR0[14:14]
	DS_rxRegs& setrecclkpwrdb(uint val);
	uint getrecclkpwrdb();

	//CSR0[13:13]
	DS_rxRegs& setrxcapbypass(uint val);
	uint getrxcapbypass();

	//CSR0[12:12]
	DS_rxRegs& setrxmute(uint val);
	uint getrxmute();

	//CSR0[11:11]
	DS_rxRegs& setlpcmlen(uint val);
	uint getlpcmlen();

	//CSR0[10:10]
	DS_rxRegs& settxrxserlpbken(uint val);
	uint gettxrxserlpbken();

	//CSR0[9:4]
	DS_rxRegs& setrecclkdiv(uint val);
	uint getrecclkdiv();

	//CSR0[3:3]
	DS_rxRegs& setwordclkdiv_pwrdnb(uint val);
	uint getwordclkdiv_pwrdnb();

	//CSR0[2:0]
	DS_rxRegs& setctlepassgn(uint val);
	uint getctlepassgn();

	//CSR1[15:12]
	DS_rxRegs& setctlebst1(uint val);
	uint getctlebst1();

	//CSR1[11:10]
	DS_rxRegs& setctlecmband1(uint val);
	uint getctlecmband1();

	//CSR1[9:8]
	DS_rxRegs& setctlermband1(uint val);
	uint getctlermband1();

	//CSR1[7:6]
	DS_rxRegs& setctleza1(uint val);
	uint getctleza1();

	//CSR1[5:4]
	DS_rxRegs& setctlesqh1(uint val);
	uint getctlesqh1();

	//CSR1[3:0]
	DS_rxRegs& setctleactgn1(uint val);
	uint getctleactgn1();

	//CSR2[15:12]
	DS_rxRegs& setctlebst2(uint val);
	uint getctlebst2();

	//CSR2[11:10]
	DS_rxRegs& setctlecmband2(uint val);
	uint getctlecmband2();

	//CSR2[9:8]
	DS_rxRegs& setctlermband2(uint val);
	uint getctlermband2();

	//CSR2[7:6]
	DS_rxRegs& setctleza2(uint val);
	uint getctleza2();

	//CSR2[5:4]
	DS_rxRegs& setctlesqh2(uint val);
	uint getctlesqh2();

	//CSR2[3:0]
	DS_rxRegs& setctleactgn2(uint val);
	uint getctleactgn2();

	//CSR3[15:12]
	DS_rxRegs& setctlebst3(uint val);
	uint getctlebst3();

	//CSR3[11:10]
	DS_rxRegs& setctlecmband3(uint val);
	uint getctlecmband3();

	//CSR3[9:8]
	DS_rxRegs& setctlermband3(uint val);
	uint getctlermband3();

	//CSR3[7:6]
	DS_rxRegs& setctleza3(uint val);
	uint getctleza3();

	//CSR3[5:4]
	DS_rxRegs& setctlesqh3(uint val);
	uint getctlesqh3();

	//CSR3[3:0]
	DS_rxRegs& setctleactgn3(uint val);
	uint getctleactgn3();

	//CSR4[15:15]
	DS_rxRegs& setdfepwrdb(uint val);
	uint getdfepwrdb();

	//CSR4[14:14]
	DS_rxRegs& setdfeauxmvtappwrdb(uint val);
	uint getdfeauxmvtappwrdb();

	//CSR4[13:13]
	DS_rxRegs& setdfemvtappwrdb(uint val);
	uint getdfemvtappwrdb();

	//CSR4[12:8]
	DS_rxRegs& setdfefxtapen(uint val);
	uint getdfefxtapen();

	//CSR4[7:4]
	DS_rxRegs& setrxtermofst(uint val);
	uint getrxtermofst();

	//CSR4[2:0]
	DS_rxRegs& setdfegnsum(uint val);
	uint getdfegnsum();

	//CSR5[15:9]
	DS_rxRegs& setdfefxtap1(uint val);
	uint getdfefxtap1();

	//CSR5[5:0]
	DS_rxRegs& setdfefxtap2(uint val);
	uint getdfefxtap2();

	//CSR6[15:15]
	DS_rxRegs& setana_bmen_n(uint val);
	uint getana_bmen_n();

	//CSR6[14:10]
	DS_rxRegs& setdfefxtap3(uint val);
	uint getdfefxtap3();

	//CSR6[9:5]
	DS_rxRegs& setdfefxtap4(uint val);
	uint getdfefxtap4();

	//CSR6[4:0]
	DS_rxRegs& setdfefxtap5(uint val);
	uint getdfefxtap5();

	//CSR7[15:15]
	DS_rxRegs& setrxterm_pwrdnb(uint val);
	uint getrxterm_pwrdnb();

	//CSR7[14:9]
	DS_rxRegs& setcephase_full(uint val);
	uint getcephase_full();

	//CSR7[8:6]
	DS_rxRegs& setpat_des_lvl(uint val);
	uint getpat_des_lvl();

	//CSR7[5:5]
	DS_rxRegs& setemphase_sync(uint val);
	uint getemphase_sync();

	//CSR7[4:0]
	DS_rxRegs& setdfemvtapsel(uint val);
	uint getdfemvtapsel();

	//CSR8[15:15]
	DS_rxRegs& setrxterm_floating_sel(uint val);
	uint getrxterm_floating_sel();

	//CSR8[14:10]
	DS_rxRegs& setdfemvtap1(uint val);
	uint getdfemvtap1();

	//CSR8[9:5]
	DS_rxRegs& setdfemvtap2(uint val);
	uint getdfemvtap2();

	//CSR8[4:0]
	DS_rxRegs& setdfemvtap3(uint val);
	uint getdfemvtap3();

	//CSR9[14:10]
	DS_rxRegs& setdfemvtap4(uint val);
	uint getdfemvtap4();

	//CSR9[9:5]
	DS_rxRegs& setdfemvtap5(uint val);
	uint getdfemvtap5();

	//CSR9[4:0]
	DS_rxRegs& setdfemvtap6(uint val);
	uint getdfemvtap6();

	//CSR10[15:15]
	DS_rxRegs& setrxrstb(uint val);
	uint getrxrstb();

	//CSR10[14:12]
	DS_rxRegs& setrxdwidth(uint val);
	uint getrxdwidth();

	//CSR10[11:10]
	DS_rxRegs& setrxratemode(uint val);
	uint getrxratemode();

	//CSR10[9:9]
	DS_rxRegs& setrxbitorder(uint val);
	uint getrxbitorder();

	//CSR10[8:8]
	DS_rxRegs& setrxpolarity(uint val);
	uint getrxpolarity();

	//CSR10[7:7]
	DS_rxRegs& settxrxparlpbken(uint val);
	uint gettxrxparlpbken();

	//CSR10[6:6]
	DS_rxRegs& setcdr_mode(uint val);
	uint getcdr_mode();

	//CSR10[5:5]
	DS_rxRegs& setsw_para_source_sel(uint val);
	uint getsw_para_source_sel();

	//CSR10[3:3]
	DS_rxRegs& setcdrfreeze(uint val);
	uint getcdrfreeze();

	//CSR10[2:2]
	DS_rxRegs& setbbpdmode(uint val);
	uint getbbpdmode();

	//CSR10[1:1]
	DS_rxRegs& setsecloopen(uint val);
	uint getsecloopen();

	//CSR10[0:0]
	DS_rxRegs& setbitslip(uint val);
	uint getbitslip();

	//CSR11[15:15]
	DS_rxRegs& setcdrrstb(uint val);
	uint getcdrrstb();

	//CSR11[13:11]
	DS_rxRegs& setcdrphsgn(uint val);
	uint getcdrphsgn();

	//CSR11[10:8]
	DS_rxRegs& setcdrk1gn(uint val);
	uint getcdrk1gn();

	//CSR11[7:5]
	DS_rxRegs& setcdrk2gn(uint val);
	uint getcdrk2gn();

	//CSR11[4:2]
	DS_rxRegs& setfreqintsat(uint val);
	uint getfreqintsat();

	//CSR11[1:0]
	DS_rxRegs& setfreqintatt(uint val);
	uint getfreqintatt();

	//CSR12[15:8]
	DS_rxRegs& setcphsofst(uint val);
	uint getcphsofst();

	//CSR12[7:0]
	DS_rxRegs& setephsofst(uint val);
	uint getephsofst();

	//CSR13[15:15]
	DS_rxRegs& settdden(uint val);
	uint gettdden();

	//CSR13[14:12]
	DS_rxRegs& settddthr(uint val);
	uint gettddthr();

	//CSR13[11:11]
	DS_rxRegs& setloseyeen(uint val);
	uint getloseyeen();

	//CSR13[10:9]
	DS_rxRegs& setloseyethr(uint val);
	uint getloseyethr();

	//CSR13[8:8]
	DS_rxRegs& setlosanaen(uint val);
	uint getlosanaen();

	//CSR13[7:5]
	DS_rxRegs& setloscfg(uint val);
	uint getloscfg();

	//CSR13[4:4]
	uint getlos();

	//CSR13[3:3]
	uint getlostran();

	//CSR13[2:2]
	uint getloseyever();

	//CSR13[1:1]
	uint getloseyehor();

	//CSR13[0:0]
	uint getlosana();

	//CSR14[15:15]
	DS_rxRegs& settimecntstart(uint val);
	uint gettimecntstart();

	//CSR14[14:14]
	DS_rxRegs& setsigdet_clkdiv(uint val);
	uint getsigdet_clkdiv();

	//CSR14[13:13]
	DS_rxRegs& setsigdetclkdiv_pinsel(uint val);
	uint getsigdetclkdiv_pinsel();

	//CSR14[12:6]
	DS_rxRegs& setdsrx_rxclk_res(uint val);
	uint getdsrx_rxclk_res();

	//CSR14[5:5]
	DS_rxRegs& setprbschken(uint val);
	uint getprbschken();

	//CSR14[4:4]
	DS_rxRegs& setprbschkmode(uint val);
	uint getprbschkmode();

	//CSR14[3:0]
	DS_rxRegs& setprbschkpatsel(uint val);
	uint getprbschkpatsel();

	//CSR15[15:15]
	DS_rxRegs& seteyemonpwrdb(uint val);
	uint geteyemonpwrdb();

	//CSR15[14:14]
	DS_rxRegs& setvolofstpol(uint val);
	uint getvolofstpol();

	//CSR15[13:13]
	uint getrxeyediag_start();

	//CSR15[12:12]
	uint getrxeyediag_done();

	//CSR15[11:11]
	uint getemready();

	//CSR15[10:10]
	DS_rxRegs& seteyescanstart(uint val);
	uint geteyescanstart();

	//CSR15[9:7]
	DS_rxRegs& seteyescanmode(uint val);
	uint geteyescanmode();

	//CSR15[6:6]
	DS_rxRegs& seteyescanwinsel(uint val);
	uint geteyescanwinsel();

	//CSR15[5:0]
	DS_rxRegs& seteyescanwin(uint val);
	uint geteyescanwin();

	//CSR16[15:8]
	DS_rxRegs& setmphsofst(uint val);
	uint getmphsofst();

	//CSR16[7:0]
	DS_rxRegs& setmvolofst(uint val);
	uint getmvolofst();

	//CSR17[14:14]
	uint geteyemetric_abormal();

	//CSR17[13:10]
	DS_rxRegs& setmmthr(uint val);
	uint getmmthr();

	//CSR17[9:9]
	DS_rxRegs& seteyemetric_manual(uint val);
	uint geteyemetric_manual();

	//CSR17[8:8]
	DS_rxRegs& seteyemetric_start(uint val);
	uint geteyemetric_start();

	//CSR17[7:0]
	DS_rxRegs& seteyemetric_sum(uint val);
	uint geteyemetric_sum();

	//CSR18[15:15]
	uint getprbserr();

	//CSR18[14:11]
	uint getprbscntexp();

	//CSR18[10:0]
	uint getprbscnt();

	//CSR19[15:8]
	uint geteyecor0();

	//CSR19[7:0]
	uint geteyecor1();

	//CSR20[15:0]
	uint getisierr0();

	//CSR21[15:0]
	uint getisierr1();

	//CSR22[15:0]
	uint getisierr2();

	//CSR23[15:0]
	uint getisierr3();

	//CSR24[15:0]
	uint getisierr4();

	//CSR25[15:0]
	uint getisierr5();

	//CSR26[15:15]
	DS_rxRegs& setrxtermcalen(uint val);
	uint getrxtermcalen();

	//CSR26[14:14]
	DS_rxRegs& setrxtermcaldir(uint val);
	uint getrxtermcaldir();

	//CSR26[13:0]
	DS_rxRegs& setrxtermcal(uint val);
	uint getrxtermcal();

	//CSR27[15:15]
	DS_rxRegs& setrxcalmode(uint val);
	uint getrxcalmode();

	//CSR27[14:14]
	DS_rxRegs& setdscalstart(uint val);
	uint getdscalstart();

	//CSR27[13:13]
	DS_rxRegs& setrxcalstart(uint val);
	uint getrxcalstart();

	//CSR27[12:12]
	DS_rxRegs& setrxterm_floating_en(uint val);
	uint getrxterm_floating_en();

	//CSR27[11:8]
	DS_rxRegs& setsigdet_win_pcie(uint val);
	uint getsigdet_win_pcie();

	//CSR27[7:7]
	DS_rxRegs& setrxdatalatchcalen(uint val);
	uint getrxdatalatchcalen();

	//CSR27[6:6]
	DS_rxRegs& setrxofstcaldir(uint val);
	uint getrxofstcaldir();

	//CSR27[5:0]
	DS_rxRegs& setrxofstsel(uint val);
	uint getrxofstsel();

	//CSR28[14:10]
	DS_rxRegs& setctleofst1(uint val);
	uint getctleofst1();

	//CSR28[9:5]
	DS_rxRegs& setctleofst2(uint val);
	uint getctleofst2();

	//CSR28[4:0]
	DS_rxRegs& setctleofst3(uint val);
	uint getctleofst3();

	//CSR29[14:10]
	DS_rxRegs& setctleofst4(uint val);
	uint getctleofst4();

	//CSR29[9:5]
	DS_rxRegs& setctleofst5(uint val);
	uint getctleofst5();

	//CSR29[4:0]
	DS_rxRegs& setctleofst6(uint val);
	uint getctleofst6();

	//CSR30[15:15]
	DS_rxRegs& setsigdet_cal_en(uint val);
	uint getsigdet_cal_en();

	//CSR30[14:10]
	DS_rxRegs& setsigdet_offset(uint val);
	uint getsigdet_offset();

	//CSR30[9:5]
	DS_rxRegs& setdfeevnsumofst(uint val);
	uint getdfeevnsumofst();

	//CSR30[4:0]
	DS_rxRegs& setdfeoddsumofst(uint val);
	uint getdfeoddsumofst();

	//CSR31[15:15]
	uint getrxctrensampofftrig();

	//CSR31[14:9]
	DS_rxRegs& setcevnsnsampofst(uint val);
	uint getcevnsnsampofst();

	//CSR31[8:8]
	DS_rxRegs& setrxctrensampencal(uint val);
	uint getrxctrensampencal();

	//CSR31[7:7]
	DS_rxRegs& setrxsnsampdir(uint val);
	uint getrxsnsampdir();

	//CSR31[6:6]
	DS_rxRegs& setrxsigdetdir(uint val);
	uint getrxsigdetdir();

	//CSR31[5:4]
	DS_rxRegs& setrxterm_ressel(uint val);
	uint getrxterm_ressel();

	//CSR31[3:3]
	DS_rxRegs& setwordclk_divsel(uint val);
	uint getwordclk_divsel();

	//CSR31[2:2]
	DS_rxRegs& setrxctle_scresen(uint val);
	uint getrxctle_scresen();

	//CSR31[1:1]
	DS_rxRegs& setrxctle_scres_clk_div(uint val);
	uint getrxctle_scres_clk_div();

	//CSR31[0:0]
	DS_rxRegs& setrx_sigdet_bld_dly_sel(uint val);
	uint getrx_sigdet_bld_dly_sel();

	//CSR32[15:15]
	uint getrxctronsampofftrig();

	//CSR32[14:9]
	DS_rxRegs& setcoddsnsampofst(uint val);
	uint getcoddsnsampofst();

	//CSR32[8:8]
	DS_rxRegs& setrxctronsampencal(uint val);
	uint getrxctronsampencal();

	//CSR32[7:6]
	DS_rxRegs& setbm_ac_r_sel(uint val);
	uint getbm_ac_r_sel();

	//CSR32[5:3]
	DS_rxRegs& setrxctle_mbersel(uint val);
	uint getrxctle_mbersel();

	//CSR33[15:15]
	uint getrxedgensampofftrig();

	//CSR33[14:9]
	DS_rxRegs& seteevnsnsampofst(uint val);
	uint geteevnsnsampofst();

	//CSR33[8:8]
	DS_rxRegs& setrxedgensampencal(uint val);
	uint getrxedgensampencal();

	//CSR33[7:0]
	uint getds_spare_o();

	//CSR34[15:15]
	uint getrxedgonsampofftrig();

	//CSR34[14:9]
	DS_rxRegs& seteoddsnsampofst(uint val);
	uint geteoddsnsampofst();

	//CSR34[8:8]
	DS_rxRegs& setrxedgonsampencal(uint val);
	uint getrxedgonsampencal();

	//CSR35[15:15]
	uint getrxmonensampofftrig();

	//CSR35[14:9]
	DS_rxRegs& setmevnsnsampofst(uint val);
	uint getmevnsnsampofst();

	//CSR35[8:8]
	DS_rxRegs& setrxmonensampencal(uint val);
	uint getrxmonensampencal();

	//CSR36[15:15]
	uint getrxmononsampofftrig();

	//CSR36[14:9]
	DS_rxRegs& setmoddsnsampofst(uint val);
	uint getmoddsnsampofst();

	//CSR36[8:8]
	DS_rxRegs& setrxmononsampencal(uint val);
	uint getrxmononsampencal();

	//CSR36[7:3]
	DS_rxRegs& seteyest1evnofst(uint val);
	uint geteyest1evnofst();

	//CSR37[15:11]
	DS_rxRegs& seteyest2evnofst(uint val);
	uint geteyest2evnofst();

	//CSR37[10:0]
	DS_rxRegs& setsquelch_det_thr(uint val);
	uint getsquelch_det_thr();

	//CSR38[15:10]
	DS_rxRegs& setdsrx_cor_res(uint val);
	uint getdsrx_cor_res();

	//CSR38[9:5]
	DS_rxRegs& seteyest1oddofst(uint val);
	uint geteyest1oddofst();

	//CSR38[4:0]
	DS_rxRegs& seteyest2oddofst(uint val);
	uint geteyest2oddofst();

	//CSR39[15:15]
	uint getrxctlerepofftrig();

	//CSR39[12:12]
	DS_rxRegs& setreplicacaldir(uint val);
	uint getreplicacaldir();

	//CSR39[11:11]
	DS_rxRegs& setrxctlerepcalen(uint val);
	uint getrxctlerepcalen();

	//CSR39[10:6]
	DS_rxRegs& setrxctlerepcalcode(uint val);
	uint getrxctlerepcalcode();

	//CSR39[5:3]
	DS_rxRegs& setrxctlerefsel(uint val);
	uint getrxctlerefsel();

	//CSR39[2:0]
	DS_rxRegs& setrxctleloadsel(uint val);
	uint getrxctleloadsel();

	//CSR40[15:8]
	DS_rxRegs& setrxspare(uint val);
	uint getrxspare();

	//CSR40[7:7]
	DS_rxRegs& setsigdet_manual(uint val);
	uint getsigdet_manual();

	//CSR40[6:6]
	DS_rxRegs& setsigdet_thr_sel_man(uint val);
	uint getsigdet_thr_sel_man();

	//CSR40[5:5]
	uint getsigdet_thr_sel();

	//CSR40[2:0]
	uint getctlepreset();

	//CSR41[15:15]
	uint getrxparepofftrig();

	//CSR41[11:11]
	DS_rxRegs& setrxpacalen(uint val);
	uint getrxpacalen();

	//CSR41[10:6]
	DS_rxRegs& setrxpacalcode(uint val);
	uint getrxpacalcode();

	//CSR41[5:3]
	DS_rxRegs& setrxparefsel(uint val);
	uint getrxparefsel();

	//CSR41[2:0]
	DS_rxRegs& setrxpaloadsel(uint val);
	uint getrxpaloadsel();

	//CSR42[15:15]
	DS_rxRegs& setdsrxlowoffpwrdb(uint val);
	uint getdsrxlowoffpwrdb();

	//CSR42[14:14]
	DS_rxRegs& setdsrxlowoffcal(uint val);
	uint getdsrxlowoffcal();

	//CSR42[13:8]
	DS_rxRegs& setdsrxlowoffctrl(uint val);
	uint getdsrxlowoffctrl();

	//CSR42[7:7]
	DS_rxRegs& setrxlowoffcaldir(uint val);
	uint getrxlowoffcaldir();

	//CSR42[6:6]
	uint getdsrxlowoffout();

	//CSR42[5:0]
	uint getrxcalread();

	//CSR43[15:15]
	DS_rxRegs& setrxeye_polarityswitch(uint val);
	uint getrxeye_polarityswitch();

	//CSR43[14:14]
	DS_rxRegs& setctlepreset_en(uint val);
	uint getctlepreset_en();

	//CSR43[13:12]
	DS_rxRegs& settxrxserlpbkatbctrl(uint val);
	uint gettxrxserlpbkatbctrl();

	//CSR43[11:10]
	DS_rxRegs& setrxlowoffatbctrl(uint val);
	uint getrxlowoffatbctrl();

	//CSR43[9:8]
	DS_rxRegs& setrxatbmuxsel(uint val);
	uint getrxatbmuxsel();

	//CSR43[7:0]
	DS_rxRegs& setrxatbsel(uint val);
	uint getrxatbsel();

	//CSR44[15:12]
	DS_rxRegs& setsquelch_detwin(uint val);
	uint getsquelch_detwin();

	//CSR44[11:11]
	DS_rxRegs& setjtagsel(uint val);
	uint getjtagsel();

	//CSR44[10:10]
	uint getjtagoutp();

	//CSR44[9:9]
	uint getjtagoutm();

	//CSR44[8:8]
	DS_rxRegs& setjtagpwrdb(uint val);
	uint getjtagpwrdb();

	//CSR44[7:7]
	DS_rxRegs& setjtagacmodeen(uint val);
	uint getjtagacmodeen();

	//CSR44[6:6]
	DS_rxRegs& setjtaginitclk(uint val);
	uint getjtaginitclk();

	//CSR44[5:5]
	DS_rxRegs& setjtaginitp(uint val);
	uint getjtaginitp();

	//CSR44[4:4]
	DS_rxRegs& setjtaginitm(uint val);
	uint getjtaginitm();

	//CSR44[3:2]
	DS_rxRegs& setjtaghystadj(uint val);
	uint getjtaghystadj();

	//CSR44[1:0]
	DS_rxRegs& setjtagthadj(uint val);
	uint getjtagthadj();

	//CSR45[15:15]
	uint getceearly();

	//CSR45[14:14]
	uint getcelate();

	//CSR45[13:13]
	uint getcmearly();

	//CSR45[12:12]
	uint getcmlate();

	//CSR45[11:11]
	uint getcdr_coarsealigndone();

	//CSR45[10:10]
	uint getsscdr_coarsealigndone();

	//CSR45[8:8]
	DS_rxRegs& setedgesleep(uint val);
	uint getedgesleep();

	//CSR45[7:7]
	DS_rxRegs& setecoarsealignen(uint val);
	uint getecoarsealignen();

	//CSR45[6:4]
	DS_rxRegs& setecoarsealignstep(uint val);
	uint getecoarsealignstep();

	//CSR45[3:3]
	DS_rxRegs& setmcoarsealignen(uint val);
	uint getmcoarsealignen();

	//CSR45[2:0]
	DS_rxRegs& setmcoarsealignstep(uint val);
	uint getmcoarsealignstep();

	//CSR46[14:8]
	uint getcphsval();

	//CSR46[7:7]
	uint getpat_per_los();

	//CSR46[6:0]
	uint getephsval();

	//CSR47[15:15]
	uint getmisierrdone();

	//CSR47[14:8]
	uint getmphsofstval();

	//CSR47[7:0]
	uint getmvolofstval();

	//CSR48[15:0]
	uint getmmcnt();

	//CSR49[15:11]
	uint gettimerexp();

	//CSR49[10:0]
	uint gettimer();

	//CSR50[15:15]
	DS_rxRegs& setsquelch_det_en(uint val);
	uint getsquelch_det_en();

	//CSR50[14:5]
	DS_rxRegs& setrxcal_timer_value(uint val);
	uint getrxcal_timer_value();

	//CSR50[4:2]
	DS_rxRegs& setrxcal_timer_div_value(uint val);
	uint getrxcal_timer_div_value();

	//CSR50[1:1]
	DS_rxRegs& setrxcal_timer_div_en(uint val);
	uint getrxcal_timer_div_en();

	//CSR50[0:0]
	DS_rxRegs& setrxcal_timer_stop(uint val);
	uint getrxcal_timer_stop();

	//CSR51[15:10]
	uint getcphase_ssc();

	//CSR51[9:9]
	uint geteyescan_rdy();

	//CSR51[8:8]
	DS_rxRegs& setsscdr_sftrst_ctrl(uint val);
	uint getsscdr_sftrst_ctrl();

	//CSR51[7:7]
	DS_rxRegs& setsscdr_demux_mode(uint val);
	uint getsscdr_demux_mode();

	//CSR51[6:6]
	DS_rxRegs& setsscdr_atb_req(uint val);
	uint getsscdr_atb_req();

	//CSR51[5:0]
	uint getephase_ssc();

	//CSR52[15:10]
	uint getmphase_ssc();

	//CSR52[9:7]
	DS_rxRegs& setsscdr_atb_sel(uint val);
	uint getsscdr_atb_sel();

	//CSR52[6:0]
	uint getsscdr_atb_out();

	//CSR53[15:11]
	DS_rxRegs& setsscdr_intg_gain(uint val);
	uint getsscdr_intg_gain();

	//CSR53[10:6]
	DS_rxRegs& setsscdr_prop_gain(uint val);
	uint getsscdr_prop_gain();

	//CSR53[5:0]
	DS_rxRegs& setsscdr_loop2_sat(uint val);
	uint getsscdr_loop2_sat();

	//CSR54[15:13]
	DS_rxRegs& seteyemetric_scanmode(uint val);
	uint geteyemetric_scanmode();

	//CSR54[12:12]
	DS_rxRegs& seteyemetric_scanwinsel(uint val);
	uint geteyemetric_scanwinsel();

	//CSR54[11:8]
	DS_rxRegs& seteyemetric_scanwin(uint val);
	uint geteyemetric_scanwin();

	//CSR54[7:0]
	uint getrxeyediag_stat();

	//CSR55[15:8]
	DS_rxRegs& setmphsofst_fst(uint val);
	uint getmphsofst_fst();

	//CSR55[7:0]
	DS_rxRegs& setmvolofst_fst(uint val);
	uint getmvolofst_fst();

	//CSR56[15:8]
	DS_rxRegs& setmphsofst_sec(uint val);
	uint getmphsofst_sec();

	//CSR56[7:0]
	DS_rxRegs& setmvolofst_sec(uint val);
	uint getmvolofst_sec();

	//CSR57[15:8]
	uint geteyecor0_fst();

	//CSR57[7:0]
	uint geteyecor1_fst();

	//CSR58[15:8]
	uint geteyecor0_sec();

	//CSR58[7:0]
	uint geteyecor1_sec();

	//CSR59[15:9]
	DS_rxRegs& setsigdet_vlv(uint val);
	uint getsigdet_vlv();

	//CSR59[8:8]
	DS_rxRegs& setrxsigdet_pwrdnb(uint val);
	uint getrxsigdet_pwrdnb();

	//CSR59[7:5]
	DS_rxRegs& setrxrecclk_sel(uint val);
	uint getrxrecclk_sel();

	//CSR59[4:4]
	DS_rxRegs& setbcdr_pin_en(uint val);
	uint getbcdr_pin_en();

	//CSR59[2:0]
	DS_rxRegs& setctleparset(uint val);
	uint getctleparset();

	//CSR60[15:15]
	DS_rxRegs& setsigdet_enable(uint val);
	uint getsigdet_enable();

	//CSR60[14:11]
	DS_rxRegs& setsigdet_win(uint val);
	uint getsigdet_win();

	//CSR60[10:0]
	DS_rxRegs& setsigdet_thr_s1(uint val);
	uint getsigdet_thr_s1();

	//CSR61[15:15]
	uint getsigdet_los();

	//CSR61[14:14]
	DS_rxRegs& setsscdr_rst_by_sigdet(uint val);
	uint getsscdr_rst_by_sigdet();

	//CSR61[13:13]
	DS_rxRegs& setremotetx(uint val);
	uint getremotetx();

	//CSR61[12:12]
	uint getsquelch_det();

	//CSR61[11:11]
	DS_rxRegs& setsigdet_rstb(uint val);
	uint getsigdet_rstb();

	//CSR61[10:0]
	DS_rxRegs& setsigdet_thr_s2(uint val);
	uint getsigdet_thr_s2();

	//CSR62[15:14]
	DS_rxRegs& setpat_det_win(uint val);
	uint getpat_det_win();

	//CSR62[13:8]
	uint getsscdr_cmphase();

	//CSR62[7:0]
	DS_rxRegs& setemphase_delta(uint val);
	uint getemphase_delta();

};

#endif // HILINKDSRXREGS_H_
