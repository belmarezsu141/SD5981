#ifndef HILINKDSRXREGS_H_
#define HILINKDSRXREGS_H_

#include <HILINK_DRIVE/HiLink_Regs_Base.h>
#define DS_RX_CSR_NUM 64

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
	/// New in v101:  Now used as a trigger to power up/down the Receiver circuits (CTLE, Center Channel, Edge Channel, Monitor Channel, DFE taps) in sequence with default settings.
			const T_REG_INFO_EX& rxpwrdb();	//CSR0[15:15]

	/// Power down control of rx_auxclk.
	/// 0 = Power down rx_auxclk output.
	/// 1 = Power up rx_auxclk output.
			const T_REG_INFO_EX& rxauxclkpwrdb();	//CSR0[14:14]

	/// CML low power enable. 
	/// 0 = Normal CML power consumption
	/// 1 = Enable CML low power
			const T_REG_INFO_EX& lpcmlen();	//CSR0[11:11]

	/// Mute control for the RX input stage. The average (long term) voltage of the p, and m inputs are equalized. Offset calibration requires  RXMUTE to be 1.
	/// 0 = Normal operation.
	/// 1 = Mute input to first CTLE stage.
			const T_REG_INFO_EX& rxmute();	//CSR0[9:9]

	/// CTLE 1st eq stage coarse boost range select
	/// 0:  select default boost range  
	/// 1:select extended boost range
			const T_REG_INFO_EX& ctleboosten1();	//CSR0[8:8]

	/// P_32b  divider selector  related to rx_auxclk_32b  recovered clock for external gearboxing    [ref to fig.9 Data Slice Clock Generation in the DataSheet]. Also see related register  RXAUXCLKPWRDB  and DFESPARE (div by 5 mode enable)
	/// 00 = divide by 8 (or divide by 10 if div by 5 mode enabled)
	/// 01 = divide by 16 (or divide by 20 if div by 5 mode enabled)
	/// 10 = divide by 32 (or divide by 40 if div by 5 mode enabled)
	/// 11 = divide by 4 (or divide by 5 if div by 5 mode enabled)
			const T_REG_INFO_EX& rxauxclkdiv();	//CSR0[4:3]

	/// Rx input signal attenuation control.  
	/// 000:   -1.2dB 
	/// 001:   -1.9dB
	/// 010:   -2.55dB 
	/// 011:   -3.15dB
	/// 100:   -3.75dB 
	/// 101:   -4.25dB
	/// 110:   -4.75dB 
	/// 111:   -5.25dB
			const T_REG_INFO_EX& ctlepassgn();	//CSR0[2:0]

	/// Not Used In V101
			const T_REG_INFO_EX& ctlehfzen1();	//CSR1[15:15]

	/// CTLE  1st eq stage coarse boost select. 
	/// 000 = Lowest coarse boost setting
	/// 001 =
	/// 010 =
	/// .
	/// 110 = 
	/// 111 = Highest coarse boost setting
			const T_REG_INFO_EX& ctleboostc1();	//CSR1[14:12]

	/// CTLE 1st eq stage mid-band capacitor select. 
	/// 00 = Lowest capacitor setting (highest mid-band frequency)
	/// 01 =
	/// 10 =
	/// 11 = Highest capacitor setting (lowest mid-band frequency)
			const T_REG_INFO_EX& ctlecmband1();	//CSR1[11:10]

	/// CTLE 1st eq stage mid-band resistor control.
	/// 00 =   disabled midband function (CTLECMBAND1 function is also disabled).
	/// 01 =   Highest resistor setting (Lowest mid-band boost)
	/// 10 = 
	/// 11 =  Lowest resistor setting (Highest mid-band boost)
			const T_REG_INFO_EX& ctlermband1();	//CSR1[9:8]

	/// CTLE 1st eq stage high frequency zero control. 
	/// 000 = Highest zero frequency 
	/// 001    
	/// 010   
	/// ..   
	/// 110 = Lowest zero frequency 
	/// 111 = invalid setting
			const T_REG_INFO_EX& ctleza1();	//CSR1[7:5]

	/// CTLE 1st eq stage squelch control bits. 
	/// 
	/// 00 = No squelch applied
	/// 01 = min squelch applied
	/// 10  or 11 = max squelch applied
			const T_REG_INFO_EX& ctlesqh1();	//CSR1[4:3]

	/// CTLE 1st gain stage gain control.  
	/// 000 = Lower gain setting
	/// 001=
	/// 010=
	/// ..
	/// 110=
	/// 111 = Highest gain setting
			const T_REG_INFO_EX& ctleactgn1();	//CSR1[2:0]

	/// Not Used In V101
			const T_REG_INFO_EX& ctlehfzen2();	//CSR2[15:15]

	/// CTLE 2nd eq stage coarse boost select. 
	/// 000 = Lowest coarse boost setting
	/// 001 =
	/// 010 =
	/// ..
	/// 110 = 
	/// 111 = Highest coarse boost setting
			const T_REG_INFO_EX& ctleboostc2();	//CSR2[14:12]

	/// CTLE 2nd eq stage mid-band capacitor select. 
	/// 00 = Lowest capacitor setting (highest mid-band frequency)
	/// 01 = 
	/// 10 = 
	/// 11 = Highest capacitor setting (lowest mid-band frequency)
			const T_REG_INFO_EX& ctlecmband2();	//CSR2[11:10]

	/// CTLE 2nd eq stage mid-band resistor control.
	/// 00 =   disabled midband function (CTLECMBAND2 function is also disabled).
	/// 01 =   Highest resistor setting (Lowest mid-band boost)
	/// 10 = 
	/// 11 =  Lowest resistor setting (Highest mid-band boost)
			const T_REG_INFO_EX& ctlermband2();	//CSR2[9:8]

	/// CTLE 2nd eq stage high frequency zero control. 
	/// 000 = Highest zero frequency 
	/// 001    
	/// 010   
	/// ..
	/// 110 = Lowest zero frequency 
	/// 111 = invalid setting
			const T_REG_INFO_EX& ctleza2();	//CSR2[7:5]

	/// CTLE 2nd equalizer stage squelch control bits. 
	/// 
	/// 00 = No squelch applied
	/// 01 = Lowest squelch applied
	/// 10 or 11 = Highest squelch applied
			const T_REG_INFO_EX& ctlesqh2();	//CSR2[4:3]

	/// CTLE 2nd gain stage gain control. 
	/// 000 = Lower gain setting
	/// 001 =
	/// 010 =
	/// ..
	/// 110 = 
	/// 111 = Highest gain setting
			const T_REG_INFO_EX& ctleactgn2();	//CSR2[2:0]

	/// Not Used In V101
			const T_REG_INFO_EX& ctlehfzen3();	//CSR3[15:15]

	/// CTLE 3rd eq stage coarse boost select. 
	/// 000 = Lowest coarse boost setting
	/// 001 = 
	/// 010 =
	/// ..
	/// 110 = 
	/// 111 = Highest coarse boost setting
			const T_REG_INFO_EX& ctleboostc3();	//CSR3[14:12]

	/// CTLE 3rd eq stage mid-band capacitor select. 
	/// 00 = Lowest capacitor setting (highest mid-band frequency)
	/// 01 =
	/// 10 =
	/// 11 = Highest capacitor setting (lowest mid-band frequency)
			const T_REG_INFO_EX& ctlecmband3();	//CSR3[11:10]

	/// CTLE 3rd eq stage mid-band resistor control.
	/// 00 =   disabled midband function (CTLECMBAND3 function is also disabled).
	/// 01 =   Highest resistor setting (Lowest mid-band boost)
	/// 10 = 
	/// 11 =  Lowest resistor setting (Highest mid-band boost)
			const T_REG_INFO_EX& ctlermband3();	//CSR3[9:8]

	/// CTLE 3rd eq stage high frequency zero control. 
	/// 000 = Highest zero frequency 
	/// 001    
	/// 010   
	/// ..
	/// 110 = Lowest zero frequency 
	/// 111 = invalid setting
			const T_REG_INFO_EX& ctleza3();	//CSR3[7:5]

	/// CTLE 3rd eq stage squelch control bits.  
	/// 
	/// 00 = No squelch applied
	/// 01 = Lowest squelch applied
	/// 10 or 11 = Highest squelch applied
			const T_REG_INFO_EX& ctlesqh3();	//CSR3[4:3]

	/// CTLE 3rd gain stage gain control.
	/// 000 = Lower gain setting
	/// 001 =
	/// 010 =
	/// ..
	/// 110 = 
	/// 111 = Highest gain setting (default)
			const T_REG_INFO_EX& ctleactgn3();	//CSR3[2:0]

	/// CTLE 1st gain stage inductor un-peaking enable.
	/// 0 = Un-peaking disabled (normal bandwidth)
	/// 1 = Un-peaking enabled (smaller bandwidth)
			const T_REG_INFO_EX& ctlegnlunpken1();	//CSR4[3:3]

	/// CTLE 2nd gain stage inductor un-peaking enable.
	/// 0 = Un-peaking disabled (normal bandwidth)
	/// 1 = Un-peaking enabled (smaller bandwidth)
			const T_REG_INFO_EX& ctlegnlunpken2();	//CSR4[2:2]

	/// CTLE 3rd gain stage inductor un-peaking enable.
	/// 0 = Un-peaking disabled (normal bandwidth)
	/// 1 = Un-peaking enabled (smaller bandwidth)
			const T_REG_INFO_EX& ctlegnlunpken3();	//CSR4[1:1]

	/// DFE feedback power down control (DFE idac and tap gen clock). Active low.
	/// 0 = Power down DFE feedback
	/// 1 = Power up DFE feedback
			const T_REG_INFO_EX& dfepwrdb();	//CSR5[15:15]

	/// DFE tap power down control for taps 10-15. Active low.
	/// 0 = Power down all taps from 10 to 15.
	/// 1 = Power up all taps from 10 to 15.
			const T_REG_INFO_EX& dfemvtappwrdb();	//CSR5[14:14]

	/// DFE tap power down for tap 1-9
	/// bit[0] = tap1 (0 =  power down; 1 = power up DFE tap1)
	/// bit[1] = tap2 (0 =  power down; 1 = power up DFE tap2)
	/// bit[2] = tap3 (0 =  power down; 1 = power up DFE tap3)
	/// bit[3] = tap4 (0 =  power down; 1 = power up DFE tap4)
	/// bit[4] = tap5 (0 =  power down; 1 = power up DFE tap5)
	/// bit[5] = tap6 (0 =  power down; 1 = power up DFE tap6)
	/// bit[6] = tap7 (0 =  power down; 1 = power up DFE tap7)
	/// bit[7] = tap8 (0 =  power down; 1 = power up DFE tap8)
	/// bit[8] = tap9 (0 =  power down; 1 = power up DFE tap9)
			const T_REG_INFO_EX& dfefxtappwrdb();	//CSR5[13:5]

	/// Rx DFE Isummer boost control. 
	/// 00 = Minimum boost
	/// 01 =
	/// 10 =
	/// 11 = Maximum boost
			const T_REG_INFO_EX& dfesumboost();	//CSR5[4:3]

	/// Rx DFE Isummer gain control. 
	/// 000 = Minimum gain
	/// 001  =  
	/// ��..  
	/// 111  = Maximum gain
			const T_REG_INFO_EX& dfegnsum();	//CSR5[2:0]

	/// Main DFE Power sequence control  Active low.
	/// 0 = Power down DFE sequence
	/// 1 = Power up DFE sequence
	/// New in V101: Used as a trigger to power up/down the RX DFE taps in sequence with default settings.
			const T_REG_INFO_EX& rxdfemainpwrdb();	//CSR6[7:7]

	/// DFE fixed tap 2 polarity and weight.  
	/// 
	/// bit[6] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] -  weight (binary),
	/// 000000 = Minimum Tap Weight
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum Tap Weight
			const T_REG_INFO_EX& dfefxtap2();	//CSR6[6:0]

	/// DFE fixed tap 3 polarity and weight.  
	/// 
	/// bit[5] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[4:0] -  weight (binary),
	/// 00000 = Minimum Tap Weight
	/// 00001 =
	/// 00010 =
	/// ..
	/// 11111 = Maximum Tap Weight
			const T_REG_INFO_EX& dfefxtap3();	//CSR7[13:8]

	/// DFE fixed tap 4 polarity and weight.   
	/// 
	/// bit[5] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[4:0] -  weight (binary),
	/// 00000 = Minimum Tap Weight
	/// 00001=
	/// 00010 = 
	/// ?..
	/// 11111 = Maximum Tap Weight
			const T_REG_INFO_EX& dfefxtap4();	//CSR7[5:0]

	/// DFE fixed tap 5 polarity and weight.  
	/// 
	/// bit[5] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[4:0] -  weight (binary),
	/// 00000 = Minimum Tap Weight
	/// 00001 =
	/// 00010 =
	/// ..
	/// 11111 = Maximum Tap Weight
			const T_REG_INFO_EX& dfefxtap5();	//CSR8[15:10]

	/// DFE fixed tap 6 polarity and weight.  
	/// 
	/// bit[4] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] -  weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
			const T_REG_INFO_EX& dfefxtap6();	//CSR8[9:5]

	/// DFE fixed tap 7 polarity and weight.  
	/// 
	/// bit[4] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] -  weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
			const T_REG_INFO_EX& dfefxtap7();	//CSR8[4:0]

	/// DFE Tap   8 polarity and weight.   
	/// 
	/// bit[4] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
			const T_REG_INFO_EX& dfefxtap8();	//CSR9[12:8]

	/// DFE Tap 9  polarity and weight.   
	/// 
	/// bit[4] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
			const T_REG_INFO_EX& dfefxtap9();	//CSR9[4:0]

	/// DFE Tap 10 polarity and weight.  
	/// 
	/// bit[4] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
			const T_REG_INFO_EX& dfemvtap1();	//CSR10[14:10]

	/// DFE Tap 11  polarity and  weight.  
	/// 
	/// bit[4] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
			const T_REG_INFO_EX& dfemvtap2();	//CSR10[9:5]

	/// DFE Tap 12  polarity and weight.  
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
			const T_REG_INFO_EX& dfemvtap3();	//CSR10[4:0]

	/// DFE Tap 13  polarity and weight.  
	/// 
	/// bit[4] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
			const T_REG_INFO_EX& dfemvtap4();	//CSR11[14:10]

	/// DFE Tap 12  polarity and weight. 
	/// 
	/// bit[4] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
			const T_REG_INFO_EX& dfemvtap5();	//CSR11[9:5]

	/// DFE Tap 13  polarity and weight.   
	/// 
	/// bit[4] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
			const T_REG_INFO_EX& dfemvtap6();	//CSR11[4:0]

	/// Receiver digital circuitry reset. Active low.
	/// 0 = Reset RX logic
	/// 1 = RX out of reset
			const T_REG_INFO_EX& rxrstb();	//CSR12[15:15]

	/// RX data width select  (also refer to related register RXRATEMODE)
	/// 00 = Normal Mode 
	/// Sends 40 bits at Full-rate   
	/// Sends 20 bits at Half-rate, using Full-rate clk
	/// Sends 10 bits at Quarter-rate, using Full-rate clk 
	/// Sends 5 bits at Octal-rate, using Full-rate clk
	/// Sends 3 bits at Hex-rate, using Full-rate clk
	/// 01 = 2X Mode   
	/// Sends 40 bits at Half-rate, using Half-rate clk 
	/// Sends 20 bits at Quarter-rate, using Half-rate clk
	/// Sends 10 bits at Octal-rate, using Half-rate clk
	/// Sends 5 bits at Hex-rate, using Half-rate clk
	/// 10 = 4X Mode  
	/// Sends 40 bits at Quarter-rate, using Quarter-rate clk 
	/// Sends 20 bits at Octal-rate, using Quarter-rate clk
	/// Sends 10 bits at Hex-rate, using Quarter-rate clk
	/// 11 = Reserved
			const T_REG_INFO_EX& rxdwidth();	//CSR12[14:13]

	/// RX bit rate mode.
	/// 000 = full-rate
	/// 001 = 1/2-rate
	/// 010 = 1/4-rate
	/// 011 = 1/8-rate
	/// 100   = 1/16-rate
	/// 101 to 111 = do not use
			const T_REG_INFO_EX& rxratemode();	//CSR12[12:10]

	/// Selects the mapping of the parallel RXD bus from the serial bit order:
	/// 0 = LSB is the first serial bit 
	/// 1 = MSB is the first bit input
			const T_REG_INFO_EX& rxbitorder();	//CSR12[9:9]

	/// RX data polarity control. When set, all received bits are inverted before being sent out to the core.
	/// 0 = Do not invert the RX data
	/// 1 = Invert RX the data
			const T_REG_INFO_EX& rxpolarity();	//CSR12[8:8]

	/// Enable TX-RX parallel loopback.
	/// 0 = mission mode
	/// 1 = Enable the TX-to-RX parallel loopback. In this mode the 40 bit TX data  from the core are looped back and sent  to the core.
			const T_REG_INFO_EX& txrxparlpbken();	//CSR12[7:7]

	/// Choose monitor channel for eye scan
	/// 0: monitor I channel
	/// 1: monitor Q channel
			const T_REG_INFO_EX& mdatasel();	//CSR12[6:6]

	/// Eye monitor center data masking enable (applicable only in the full-rate mode)
	/// 1 = enable (in this case eye monitor uses only ~50% of the bits based on the sign of the previous center bit set by TAP1POL) 
	/// 0 = disable
			const T_REG_INFO_EX& tap1en();	//CSR12[5:5]

	/// Set the polarity of the previous center bit for eye monitor data masking (applicable only on in the full-rate mode and when TAP1EN is set to 1)
	/// 1 = process the center bit only if the previous bit is 1    
	/// 0 = process the center bit if the previous bit is 0
			const T_REG_INFO_EX& tap1pol();	//CSR12[4:4]

	/// Freeze CDR. When CDR is frozen, it doesn't track the jitter and PPM of incoming data.
	/// 0 = Normal operation
	/// 1 = CDR is frozen
			const T_REG_INFO_EX& cdrfreeze();	//CSR12[3:3]

	/// Box car select
	/// 0 = Majority voting
	/// 1 = box car mode
			const T_REG_INFO_EX& boxcarsel();	//CSR12[2:2]

	/// Second loop enable. By enabling the second loop integrator CDR can track more PPM up to +/-XXXXppm, 
	/// 0 = Disable the CDR's second loop integrator.
	/// 1 = Enable the second loop integrator.
			const T_REG_INFO_EX& secloopen();	//CSR12[1:1]

	/// Each transition of this bit, from 0 to 1 or from 1 to 0, will cause the RX phase rotator to move 1UI  to slip one serial bit. Multiple slips can be achieved by toggling this bit. Each transition has to wait for previous slip to complete (at least 64 word clock cycles).
			const T_REG_INFO_EX& bitslip();	//CSR12[0:0]

	/// CDR soft reset. Active low.
	/// 0 = Reset CDR
	/// 1 = Normal operation
			const T_REG_INFO_EX& cdrrstb();	//CSR13[15:15]

	/// CDR phase gain.
	/// 000 = 1;    001 = 2;    010 = 3;    011 = 4
	/// ;100 = 5;  101 = 6;  110 = 7;  111 = 8.
			const T_REG_INFO_EX& phsgn();	//CSR13[14:12]

	/// Use center channel data only for CDR adaptation in subrate mode.
	/// 0 = feature diabled.  
	/// 1 = feature enabled. CDR only use data from analog center channel for adaptation.
			const T_REG_INFO_EX& cdredgeoffen();	//CSR13[7:7]

	/// Center clock phase adjustment freeze
	/// 0 = adjustment running normally
	/// 1 = adjustment is frozen at current value
			const T_REG_INFO_EX& cpafreeze();	//CSR13[6:6]

	/// Center clock phase adjustment gain selection
	/// 00 = Full Rate, shift to right by 7
	/// 01 = Half Rate, shift to right by 6
	/// 10 = Quarter Rate, shift to right by 5
	/// 11 = Octal Rate, shift to right by 4
			const T_REG_INFO_EX& cpagainsel();	//CSR13[5:4]

	/// Center clock phase adjustment
	/// 0= adjustment is disabled
	/// 1= adjustment is enabled
			const T_REG_INFO_EX& cpaenable();	//CSR13[3:3]

	/// CDR frequency gain
	/// 000 = 1;    001 = 2;    010 = 4;    011 = 8
	/// ;100 = 16;  101 = 32;  110 = 64;  111 = 128.
			const T_REG_INFO_EX& freqgn();	//CSR13[2:0]

	/// Phase offset between the center channel and the edge channel. A 2's complement value (-128 to 127) with each step of 1/32 full-rate UI. Nominal setting depends on the rate mode as follows,
	/// Rate Mode      Nominal setting
	/// full-rate           -16 ( 11110000)
	/// 1/2 rate                0
	/// 1/4 rate                0
	/// 1/8 rate                0
			const T_REG_INFO_EX& cphsofst();	//CSR14[15:8]

	/// Edge phase offset. A 2's complement value (-128 to 127) to adjust the edge phase when the CDR is frozen.  Can be used to slip one or multiple bits of RXD. To do bit slip, freeze the CDR first. Then write +/-32for +/-1UI move, or +/-64 for +/-2UI or +127/-128 for +/-4UI . For more than 4UI move, use multiple commands.
			const T_REG_INFO_EX& ephsofst();	//CSR14[7:0]

	/// Transition density detection enable. When disabled, all transition density detection logic is reset.
	/// 0 = Disable transition density detector
	/// 1 = Enable transition density detector
			const T_REG_INFO_EX& tdden();	//CSR15[15:15]

	/// Set the threshold for transition density detector.
	/// 000 = 32          100 = 512
	/// 001 = 64          101 = 1024
	/// 010 = 128        110 = 2048
	/// 011 = 256        111 = 4096
			const T_REG_INFO_EX& tddthr();	//CSR15[14:12]

	/// Eye scan based LOS detection enable.
	/// 0 = Disable eye scan based LOS detection
	/// 1 = Enable eye scan based LOS detection
			const T_REG_INFO_EX& loseyeen();	//CSR15[11:11]

	/// Eye scan based LOS threshold.
	/// 00 = 12 vertical/2 horizontal steps
	/// 01 = 28 vertical/4 horizontal steps
	/// 10 = 44 vertical/8 horizontal steps
	/// 11 = 60 vertical/16 horizontal steps
			const T_REG_INFO_EX& loseyethr();	//CSR15[10:9]

	/// Set 1 to clear an internal 42-bit timer counter to 0. This bit works together with TIMECNTSTART.
			const T_REG_INFO_EX& timecntclr();	//CSR15[8:8]

	/// LOS configuration.
	/// LOSCFG[2]:
	/// 0 = LOS pin is a real time status of the transition density detector
	/// 1 = LOS pin is a latched status of the transition density detector (clear after read)
	/// LOSCFG[1:0]:
	/// 00 = Both LOS pin and LOS register bit (RX CSR15[4] below) will be set to high when there are no enough transitions.
	/// 01 = Both LOS pin and LOS register bit  will be set to high when inner eye is not open enough vertically.
	/// 10 = Both LOS pin and LOS register bit  will be set to high when inner eye is not open enough horizontally.
	/// 11 = Both LOS pin and LOS register bit will be set to high when there are no enough transitions, or inner eye is not open enough either vertically or horizontally.
			const T_REG_INFO_EX& loscfg();	//CSR15[7:5]

	/// Loss of signal indication. This bit will be set to 1 when inadequate RX signal (the transition density falls below TDDTHR[2:0]) is detected or eye is not open enough vertically or horizontally after an eye scan, depending on the LOS configuration (RX CSR15[7:5] LOSCFG above).
	/// 0 = Adequate RX signal (transitions) or eye opening.
	/// 1 = Inadequate RX signal (transitions) or eye openning.
			const T_REG_INFO_EX& los();	//CSR15[4:4]

	/// Transition density based Loss of signal indication (Clear on read).
	/// 0 = Transition density is above preset threshold.
	/// 1 = Transition density falls below preset threshold.
			const T_REG_INFO_EX& lostran();	//CSR15[3:3]

	/// Eye scan based (vertical) loss-of-signal indication.
	/// 0 = Vertical opening of last inner eye scan is bigger than the threshold.
	/// 1 = Vertical opening of last inner eye scan is less than the threshold.
			const T_REG_INFO_EX& loseyever();	//CSR15[2:2]

	/// Eye scan based (horizontal) loss-of-signal indication.
	/// 0 = Horizontal opening of last inner eye scan is bigger than the threshold.
	/// 1 = Horizontal opening of last inner eye scan is less than the threshold.
			const T_REG_INFO_EX& loseyehor();	//CSR15[1:1]

	/// Not used
			const T_REG_INFO_EX& losana();	//CSR15[0:0]

	/// Set 1 to start an internal 42-bit timer. Self cleared when the timer is full. The timer can be stopped at any time by writing 0 to this register.
			const T_REG_INFO_EX& timecntstart();	//CSR16[15:15]

	/// set  IQ offset for the monitor channel (2's complement value)
			const T_REG_INFO_EX& moniqofst();	//CSR16[14:8]

	/// 0=normal, using center data for prbs detection
	/// 1= using monitor data for prbs detection
			const T_REG_INFO_EX& prbsemdatasel();	//CSR16[7:7]

	/// Voltage offset polarity control for ISI calculation.
	/// 0 = Normal
	/// 1 = Invert
			const T_REG_INFO_EX& volofstpol();	//CSR16[6:6]

	/// PRBS checker enable.
	/// 0 = Disable (default)
	/// 1 = Enable
			const T_REG_INFO_EX& prbschken();	//CSR16[5:5]

	/// PRBS checker mode.
	/// 0 = Synchronous mode. In this mode, the PRBS checker is synchronized with the input data (i.e., feeding the PRBS checker with the input data).
	/// 1 = Free running mode.
	/// Normally, the PRBS checker should be set in synchronous mode. Once the PRBS checker is synchronized (no error detected), it can be switched to free running mode to prevent error propagation during error detection.
			const T_REG_INFO_EX& prbschkmode();	//CSR16[4:4]

	/// PRBS pattern select for the PRBS checker: 
	/// 0000 = PRBS7 (X7+X6+1)
	/// 0001 = PRBS9 (X9+X5+1)
	/// 0010 = PRBS10 (X10+X7+1)
	/// 0011 = PRBS11 (X11+X9+1)
	/// 0100 = PRBS15 (X15+X14+1)
	/// 0101 = PRBS20 (X20+X17+1)
	/// 0110 = PRBS23 (X23+X18+1)
	/// 0111 = PRBS31 (X31+X28+1)
	/// 1000 = 1-0-1 pattern
	/// 1001 to 1111 = Disabled
			const T_REG_INFO_EX& prbschkpatsel();	//CSR16[3:0]

	/// Rx monitor channel power down control. Active low.
	/// Now used in Digital RTL only.   See also RXCPMONPWRDB and RXCPMONQPWRDB
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& eyemonpwrdb();	//CSR17[15:15]

	/// Eye scan START/STOP control
	/// 0 = Stop
	/// 1 = Start. Self clear after eye scan is done.
			const T_REG_INFO_EX& eyescanstart();	//CSR17[14:14]

	/// Eye monitor status
	/// 0 = not ready for scan
	/// 1 = ready for scan
			const T_REG_INFO_EX& emready();	//CSR17[13:13]

	/// The status of last eye monitor task.
	/// 0 = Succeeded;  1 =  Failed
			const T_REG_INFO_EX& emtaskstatus();	//CSR17[12:12]

	/// Eye scan mode.
	/// 000: Auto horizontal inner eye scan;  10x: Manual inner eye scan
	/// ;001: Auto vertical inner eye scan;  11x: Manual outer eye scan
	/// ;010: Auto horizontal outer eye scan;   011: Auto vertical outer eye scan
	/// 
	/// ;     For automatic horizontal eye scan, eye monitor sweeps horizontally at a certain voltage setting set by MVOLOFST[8:0] to find the inner most eye corners (left and right) at a given BER. The horizontal starting point is programmable through MPHSOFST[7:0]. If starting from inside, the eye monitor continues left and right with a linear search and returns both left and right corners when completes;  otherwise, continues left and right with a linear search until the eye boundaries are found or the bound limits are reached, and returns both corners (left and right) or one corner (left = right), or flags the scan has failed to find corners.
	///      For automatic vertical eye scan, eye monitor sweeps vertically at a certain phase setting set by MPHSOFST[7:0] to find the inner most eye corners (lower and upper) at a given BER. The vertical starting point is controlled by the eye monitor, i.e., not programmable. If starting from inside of the eye, the scan continues with a binary search and returns both upper and lower corners when completes; otherwise, it continues up and down with a linear search until the eye boundaries are found or the bound limits are reached, and returns both corners (upper and lower) or one corner (upper = lower), or flags the scan has failed to find corners. It is also possible to force to use the linear search only which would be very time consuming. For the linear search, the eye monitor can jump with a programmable voltage offset  steps (2, 4, 8,16 and etc.) to speed up the search.
	///      For manual eye scan, the user has full control over how to measure the eye. Both phase and voltage settings are programmable through MPHSOFST[7:0] and MVOLOFST[8:0] respectively. They need to be set before the scan starts
			const T_REG_INFO_EX& eyescanmode();	//CSR17[11:9]

	/// 0 = indicates normal corner values returned
	/// 1 = indicates that EM voltage offset is already at the max value but BER contour not satisfied
			const T_REG_INFO_EX& emvolovrmax();	//CSR17[8:8]

	/// Creates a composite result out of a one dlev(1,1) scan and one dlev(1,0) scan.
	/// 0 = Composite area is disabled; 
	/// 1 = Composite area scan is enabled
			const T_REG_INFO_EX& compeyeen();	//CSR17[7:7]

	/// Eye scan window select.
	/// 0 = Choose normal eye scan window
	/// 1 = Choose extended eye scan window
	/// Note: extended eye scan window is used to get more accurate and fine tuned results. It requires longer time to scan the eye. So it should be used wisely.
			const T_REG_INFO_EX& eyescanwinsel();	//CSR17[6:6]

	/// Eye scan window. bit[5] is reserved for future use.
	///     For automatic inner eye scan (both horz and vert), it sets the eye scan window, i.e., the number of words to be checked for a mismatch, which is calculated as (4*SCALE* 2powEYESCANWINSEL* 2powEYESCANWIN[4:0]), where SCALE=8. To speed up the scan, we may look at a smaller scan window first, which is calculated as (SCALE* 2powEYESCANWINSEL*  2powEYESCANWIN[4:0] ). When reaching the edge of the eye, we need to use the big scan window to fine tune the edge. Fine tuning is not needed for the vertical scan is the binary search is chosen. For half, quarter and octal rates and full rates with the tap 1 enabled, calculations need to be scaled accordingly so that the target BER stays the same.   For automatic outer eye scan, it auto sets the allowed mismatch limit (no of bits), which is calculated as (64*SCALE* 2powEYESCANWINSEL* EYESCANWIN[4:0]), where SCALE = 16, within a fixed eye scan window which is calculated as (4*64*SCALE* 2powEYESCANWINSEL). For half, quarter and octal rates and the full rate with the tap 1 enabled, calculations need to be scaled accordingly so that the target BER stays the same. There is also an option to allow both the mismatch limit and the scan window to be fully controlled manually. In this case, the mismatch limit is set by MMTHR[15:0], while the scan window is calculated as (2powEYESCANWIN[4:0]). Scaling is not needed for half, quarter and octal rates and the full rate with the tap 1 enabled.  For manual inner eye scan, eye monitor keeps comparing the monitor data with the recovered data at certain MPHSOFST[7:0] and MVOLOFST[7:0] settings until a mismatch is found or the scan is stopped by writing EYESCANSTART to '0'.  For manual outer eye scan, it sets the measurement window, i.e., the number of words counted for mismatch and ISI error accumulation, which is calculated as (16*32*EYESCANWIN[3:0]).
	///      When the extended eye scan window mode is enabled, all above eye scan window and mismatch limit values are doubled except the BER is manually selected.
			const T_REG_INFO_EX& eyescanwin();	//CSR17[5:0]

	/// Eye monitor phase offset w.r.t. the nominal eye center (2's complement value).
			const T_REG_INFO_EX& mphsofst();	//CSR18[8:0]

	/// set  IQ offset for the center channel
			const T_REG_INFO_EX& ceniqofst();	//CSR19[15:9]

	/// Selects which channel to scan in the eye monitor.
	/// 00 = select I (phase 0) , only valid in full rate mode
	/// 01 = select Q (phase 90), valid in all rate mode
	/// 10 = select Ib (phase 180), only valid in full rate mode
	/// 11 =  select Qb (phase 270), valid in full rate and half rate mode
			const T_REG_INFO_EX& monslcsel();	//CSR19[8:7]

	/// set IQ offset for the edge channel
			const T_REG_INFO_EX& edgiqofst();	//CSR19[6:0]

	/// PRBS checker error status. The bit is set to 1 when at least one error is detected. Status is latched until being read (clear on read).
	/// 0 = No errors detected.
	/// 1 = At least 1 error detected by the PRBS detector.
			const T_REG_INFO_EX& prbserr();	//CSR20[15:15]

	/// PRBSCNTEXP[3:0] gives the exponent portion of the 26 bit error counter. (clear on read)
	/// 0 = total error is PRBSCNT
	/// 1-15 = total error is 2pow(10+PRBSCNTEXP)+PRBSCNT*2(PRBSCNTEXP-1)
			const T_REG_INFO_EX& prbscntexp();	//CSR20[14:11]

	/// PRBS error count
			const T_REG_INFO_EX& prbscnt();	//CSR20[10:0]

	/// Set mismatch threshold for eye scan (only the enhanced basic eye scan).  If MMTHR[15:0] = 0, the mismatch threshold will be determined by EYESCANWIN[5:0].  If MMTHR[15:0] is not equal to 0, the BER used for eye scan is calculated as  BER = MMTHR[15:0]/(2powEYESCANWIN*NBITS), which applies all rate modes and whether or not the tap 1 is enabled. EYESCANWINSEL will not take effect in this case.
			const T_REG_INFO_EX& mmthr();	//CSR21[15:0]

	/// Currently Not supported in v101 (Reserved for four eye scan selection)
			const T_REG_INFO_EX& emfoureyesel();	//CSR22[13:12]

	/// Eye monitor voltage offset (2's complement value).
			const T_REG_INFO_EX& mvolofst();	//CSR22[8:0]

	/// For basic eye scan:
	/// bits[8:0] ?Left  or lower corner of the most recent automatic horizontal/vertical eye scan.
	/// 
	/// For peak detection:
	/// bits[8:0] ?Left  or lower corner  associated with the maximum detected peak.
	/// 
	/// For area calculation:
	/// bits[8:0] ?Not used.
			const T_REG_INFO_EX& emresult0();	//CSR23[8:0]

	/// For basic eye scan:
	/// bits[8:0] ?Right  or upper corner of the most recent automatic horizontal/vertical eye scan.
	/// 
	/// For peak detection,
	/// bits[8:0] ?Right  or upper corner  associated with the maximum detected peak.
	/// 
	/// For area calculation,
	/// bits[8:0] ?Not used.
			const T_REG_INFO_EX& emresult1();	//CSR24[8:0]

	/// Only applies to the enhanced basic eye scan.
	/// bit[3]  Vertical scan algorithm.  0= automatic choose binary or linear; 1=linear search.
	/// bits[2:0]  Vertical scan step.
	/// 000 = 1 step;    001 =  2 steps;   010 =  4 steps;      
	/// 011 = 8 steps;  100 = 16 steps;  101 = 64 steps;   
	/// 110 = 128 steps;  111 =  256 steps
			const T_REG_INFO_EX& eyescanctrl();	//CSR25[15:12]

	/// 0000 = Basic eye scan             
	/// 0001 = Peak detection
	/// 0010 = Area calculation
	/// 0011 = Four eye capturing (currently not supported in V101)
	/// 0100 - 1111 = Reserved
			const T_REG_INFO_EX& eyemontask();	//CSR25[11:8]

	/// 0: Basic eye scan algorithm (compatible with H30 V100)
	/// 1: Enhanced basic eye scan algorithm
			const T_REG_INFO_EX& eyescanalg();	//CSR25[7:7]

	/// For the extended basic eye scan:
	/// bits[4:0] ?Not used.    
	///                                                                                                 
	/// For peak detection:
	/// bits[4:3] ?00 = WL/WR or HL/HU are auto-discovered  and
	/// then the [WL, WR]  or [HL, HU] range  is searched; 01 =  Search 1 UI going to the left and 1 UI going      
	/// to the right;  10 = Search 1/2 UI going to the left                            
	/// and 1/2 UI going to the right; 11 = WL/WR or HL/HU are
	/// provided from user registers (see EMSWCORNER0[8:0], EMSWCORNER1[8:0])
	/// bit[2] ?Peak detection algorithm. 1 = Exhaustive search
	/// ;0 = Fast search (i.e., the first maximal peak is returned)
	/// ;bits[1:0] ?Phase or voltage step(s)  to jump during peak
	/// Detection: 00 = 1 step;  01 = 4 steps;  10 =  8 steps;  11 = 15 steps
	/// 
	/// For area calculation:
	/// bit[4] ?Set the WL/WR corners using EMSWCORNER0/1 registers
	/// bit[3] ?Area calculation scaling factor. 0 = No scaling
	/// ;1 = Scale down by 2 the corner values
	/// bits[2:0] ?Area calculation points which is calculated 
	/// as 4*EMTASKCTRL[2:0].
	/// 
	/// For waveform scope:
	/// bit[4] ?Not used;  bit[3] ?Read next segment
	/// ;bit[2] ?Reference sample is based on a 0 to 1 transition
	/// ;bits[1:0] - Number of phase offsets to sample using a step of 2pow[1:0] starting from �UI going to +UI.
	///  For four consecutive eye capturing: not supported in V101
			const T_REG_INFO_EX& emtaskctrl();	//CSR25[6:2]

	/// scaling factor for returned EM corner values
	/// 0: no scaling
	/// ;1: corners are scaled to full rate range
			const T_REG_INFO_EX& emcornerscaling();	//CSR25[1:1]

	/// 1 enables em corner guard to ensure corner1 is always on the left or lower side
			const T_REG_INFO_EX& emcornergrden();	//CSR25[0:0]

	/// Wait time for analog to settle during eye monitor Voltage scan
			const T_REG_INFO_EX& monvolscanstltime();	//CSR26[7:0]

	/// Eye monitor task averaging control.
	/// bits[3:2] ?Selects an average function between arithmetical mean and mode (most frequent number)
	/// 00 = Performs the arithmetical mean over [1:0] samples, both vertical and horizontal scans
	/// 01 = Returns the mode (most frequent number) over [1:0] samples, both vertical and horizontal scans
	/// 10 = Returns the mode  for horizontal scans and the mean for vertical scans, over [1:0] samples
	/// 11 = Reserved
	/// bits[1:0] ?Number of samples to collect
	/// 00 = 1 sample;  01 = 8  samples;  10 = 16 samples;  11 = 32 samples;
			const T_REG_INFO_EX& emtaskavrg();	//CSR27[15:12]

	/// Tap1 related offset value to be added to the EMRESULT0[15:0] value. Only valid when the tap 1 is enabled.
			const T_REG_INFO_EX& cornerofst0();	//CSR27[8:0]

	/// Tap1 related offset value to be added to the EMRESULT1[15:0] value. Only valid when the tap 1 is enabled.
			const T_REG_INFO_EX& cornerofst1();	//CSR28[8:0]

	/// For basic eye scan:
	/// bits[15:0] ?Not used.
	/// 
	/// For peak detection:
	/// bits[15:9] - Not used
	/// bits[8:0] ?Phase or voltage offsets associated with the maximum detected peak.
	/// 
	/// For area calculation:
	/// bits[15:0] ?Value of the calculated area.
			const T_REG_INFO_EX& emresult2();	//CSR29[15:0]

	/// Eye monitor scan max voltage offset setting.
			const T_REG_INFO_EX& mvolmax();	//CSR30[8:0]

	/// RX termination calibration value selection
	/// 0 = value from dpm control line (from Service Slice where cal replica block is located)
	/// 1 = value from regiser RXTERMCAL
			const T_REG_INFO_EX& rxtermcalsel();	//CSR31[15:15]

	/// Not used
			const T_REG_INFO_EX& rxtermcaldir();	//CSR31[14:14]

	/// Rx latch offset range scale.
	/// 0: Normal offset range
	/// 1: Normal * 0.7 offset range
			const T_REG_INFO_EX& rxlatofstrangescale();	//CSR31[13:13]

	/// Select calibration mode for the CTLE Replica Opamp.
	/// 0 = open loop
	/// ;1 = closed loop.
			const T_REG_INFO_EX& rxctlerepopcalmode();	//CSR31[12:12]

	/// Manual input  of Calibration bits for termination resistor. 
	/// 0000 =  High impedance setting
	/// 0001 =  Highest calibrated resistance setting
	/// ��...
	/// 1110 = Lowest calibrated resistance setting
	/// 1111 =  same as above
	/// 
	/// For Typical Corner: 4'b0101: ~50Ohm, 4'b0111: ~45Ohm
	/// (Mode selected  by  register  RXTERMCALSEL)
			const T_REG_INFO_EX& rxtermcal();	//CSR31[3:0]

	/// RX calibration mode. Switching from manual mode to automatic mode restarts the calibration process.
	/// 0 = Automatic calibration
	/// 1 = Manual calibration
			const T_REG_INFO_EX& rxcalmode();	//CSR32[15:15]

	/// Data Slice calibration start control. Used only in automatic and semi-automatic modes.
	/// 0 = Do not start data slice calibrations
	/// 1 = Start all data slice calibrations (automatic way). Self clear after calibration is done.
			const T_REG_INFO_EX& dscalstart();	//CSR32[14:14]

	/// RX calibration start control. Used only in automatic and semi-automatic modes.
	/// 0 = Do not start RX calibrations
	/// 1 = Start RX calibrations. Self clear after calibration is done.
			const T_REG_INFO_EX& rxcalstart();	//CSR32[13:13]

	/// Termination floating enable 
	/// 0 = connect RX termination common mode reference point to GND
	/// 1= floating RX termination common mode reference point 
	/// (defaults and description different from v100)
			const T_REG_INFO_EX& rxtermfloating();	//CSR32[12:12]

	/// Latch offset calibration enable
	/// 0 = Skip offset calibration for center, edge and monitor channel latches during the automatic calibration process
	/// 1 = Perform offset calibration for center, edge and monitor channel latches during the automatic calibration process
			const T_REG_INFO_EX& rxdatalatchcalen();	//CSR32[7:7]

	/// Not used
			const T_REG_INFO_EX& rxofstcaldir();	//CSR32[6:6]

	/// RX OTB select. It chooses analog circuit for offset calibration. Only applies to manual offset calibration mode. 
	/// 000000 = no selection
	/// 000001 = Select CTLE bias block current mirror bias voltage
	/// 000010 = Select CTLE load replica amplifier offset
	/// 000011 = Select CTLE vreg opamp inputs
	/// 000100 = Select CTLE vreg calibration voltages
	/// 000101 = Select VSR CTLE replica ical
	/// 000110 = Select VSR CTLE eq stage 1 ical
	/// 000111 = Select VSR CTLE gain stage 1 ical
	/// 001000 = Select VSR CTLE gain stage 2 ical
	/// 001001 = Select CTLE eq stage 1 offset
	/// 001010 = Select CTLE gain stage 1 offset
	/// 001011 = Select CTLE eq stage 2 offset
	/// 001100 = Select CTLE gain stage 2 offset
	/// 001101 = Select CTLE eq stage 3 offset
	/// 001110 = Select CTLE gain stage 3 offset
	/// 001111 = Select DFE summer supply
	/// 010000 = Select DFE I even summer offset
	/// 010001 = Select DFE Q even summer offset
	/// 010010 = Select DFE I odd  summer offset
	/// 010011 = Select DFE Q odd  summer offset
	/// 010100 =  Unassigned, Not connected
	/// 010101 = I-even summer restrim calibration voltages
	/// 010110 = RX IQ detector voltages
	/// 011111 to 111111 = Unassigned, Not connected
			const T_REG_INFO_EX& rxofstsel();	//CSR32[5:0]

	/// CLTE stage 1 offset control. Used for manual offset calibration.
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset ,
	/// 0000 = no offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
			const T_REG_INFO_EX& ctleofst1();	//CSR33[14:10]

	/// CLTE stage 2 offset control. Used for manual offset calibration. 
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset ,
	/// 0000 = no offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
			const T_REG_INFO_EX& ctleofst2();	//CSR33[9:5]

	/// CLTE stage 3 offset control. Used for manual offset calibration. 
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset ,
	/// 0000 = no offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
			const T_REG_INFO_EX& ctleofst3();	//CSR33[4:0]

	/// CLTE stage 4 offset control. Used for manual offset calibration. 
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset ,
	/// 0000 = no offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
			const T_REG_INFO_EX& ctleofst4();	//CSR34[14:10]

	/// CLTE stage 5 offset control. Used for manual offset calibration. 
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset ,
	/// 0000 = no offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
			const T_REG_INFO_EX& ctleofst5();	//CSR34[9:5]

	/// CLTE stage 6 offset control. Used for manual offset calibration. 
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset ,
	/// 0000 = no offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
			const T_REG_INFO_EX& ctleofst6();	//CSR34[4:0]

	/// Isum Ieven offset,
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset ,
	/// 0000 = Minimum offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
			const T_REG_INFO_EX& dfeievnsumofst();	//CSR35[14:10]

	/// Isum Iodd offset,
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset (binary),
	/// 0000 = Minimum offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
			const T_REG_INFO_EX& dfeioddsumofst();	//CSR35[9:5]

	/// Isum Qeven offset,
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset (binary),
	/// 0000 = Minimum offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
			const T_REG_INFO_EX& dfeqevnsumofst();	//CSR35[4:0]

	/// Isum Qodd offset,
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset (binary),
	/// 0000 = Minimum offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
			const T_REG_INFO_EX& dfeqoddsumofst();	//CSR36[14:10]

	/// rxctle current scaling control
			const T_REG_INFO_EX& rxctleibiastune();	//CSR36[7:5]

	/// resistive tuning for passive midband freq shaping function
	/// 000 = lowest resistor setting (highest zero freq location)
	/// 111 = highest resistor setting (lowest zero freq location)
			const T_REG_INFO_EX& rxctlepasstune();	//CSR36[2:0]

	/// set iptat temperature compensation coefficient
			const T_REG_INFO_EX& ctleiptattcctrl();	//CSR37[11:8]

	/// bypass programmable iptat bias
			const T_REG_INFO_EX& ctleiptatbypass();	//CSR37[6:6]

	/// enable clock to for SC resistor
			const T_REG_INFO_EX& ctlescresen();	//CSR37[5:5]

	/// Divider ratio to generate SC resistor clock. divider ratio is continuous from 1 to 31
			const T_REG_INFO_EX& ctlescresclkdiv();	//CSR37[4:0]

	/// power down  ALOS detection stage, active low
			const T_REG_INFO_EX& rxsigdetpwrdb();	//CSR38[15:15]

	/// select divide ratio for high speed sampling clock (input ref clk is HSCLK/2)
	/// 00 = div by 2
	/// 01 = div by 4
	/// 10 = div by 16
	/// 11 = div by 8
			const T_REG_INFO_EX& rxsigdetclkdiv();	//CSR38[14:13]

	/// clk delay offset for complimentary sampling channel
	/// 0 = PCIE/common
	/// 1 = SATA/SAS
			const T_REG_INFO_EX& rxsigdetclkdlysel();	//CSR38[12:12]

	/// power down ALOS buffer stage, active low
	/// 0 = ALOS calibration mode
	/// 1 = ALOS mission mode
			const T_REG_INFO_EX& rxsigdetcalpwrdb();	//CSR38[10:10]

	/// enable high speed clock path, active high
	/// 0 = disable
	/// 1= enable high speed clock path
			const T_REG_INFO_EX& rxdigdetclkbufen();	//CSR38[9:9]

	/// connect input stage buffer outputs to the otb bus
	/// 0 = disconnect
	/// 1= connect
			const T_REG_INFO_EX& rxsigdetatbsel();	//CSR38[8:8]

	/// set signal detection threshold 
	///  (changed in v101)
	/// bit[3]  sign bit
	/// 0= positive
	/// 1= negative
	/// bit[2:0]  magnitude of threshold
	/// 000= min
	/// 001=
	/// 010=
	/// ��
	/// 111=max
			const T_REG_INFO_EX& rxsigdetvthres();	//CSR39[13:10]

	/// signal detection hysteresis adjust (new in v101)
	/// 00: no hysterisis
	/// 11: max hysterisis
			const T_REG_INFO_EX& rxsigdethyst();	//CSR39[9:8]

	/// alos buffer offset control. Used for manual offset calibration.  
	/// Bit[4]: sign bit of magnitude
	/// 0= positive
	/// 1= negative
	/// 
	/// bits[3:0]= offset magnitude
	/// 0000 = zero offset 
	/// 0001 = 
	/// ..
	/// 1111 = max offset
			const T_REG_INFO_EX& rxsigdetoffset();	//CSR39[4:0]

	/// Status of Squelch detection. Result is only available in sata/sas mode
			const T_REG_INFO_EX& sigdetsqlchlos();	//CSR40[15:15]

	/// Status of signal loss detection. Results is only available in PCIE or common mode
			const T_REG_INFO_EX& sigdetlos();	//CSR40[14:14]

	/// function not implemented. Should set to 1.
			const T_REG_INFO_EX& sigdettxrxstat();	//CSR40[13:13]

	/// Signal and squelch detection window 4*2powSIGDETWIN
			const T_REG_INFO_EX& sigdetwin();	//CSR40[11:8]

	/// 01 =  enables signal detect sata mode
	/// x0/11 = enables common mode or PCI mode
			const T_REG_INFO_EX& sigdetpmamode();	//CSR40[6:5]

	/// 0 =  threshold is controled by SIGDETTHRCFGSEL[2:0]
	/// 1 = threshold is set by SIGDETTHRSELMAN[2:0]
			const T_REG_INFO_EX& sigdetmanual();	//CSR40[4:4]

	/// Manual selection for signal detect and squelch threshold value.
			const T_REG_INFO_EX& sigdetthrselman();	//CSR40[3:1]

	/// Enable for Signal detect and Squelch
	/// 0 = function disabled
	/// 1 = function enabled
			const T_REG_INFO_EX& sigdeten();	//CSR40[0:0]

	/// 1xx/000 = signal detect threshold is set by SIGDETTHRS3
	/// 01x = signal detect threshold is set by SIGDETTHRS2
	/// 001 = signal detect threshold is set by SIGDETTHRS1
			const T_REG_INFO_EX& sigdetthrcfgsel();	//CSR41[14:12]

	/// signal detect threshold parameter3. suited for 2.5/5G pcie mode
			const T_REG_INFO_EX& sigdetthrs1();	//CSR41[10:0]

	/// signal detect threshold parameter3. suited for all sata/sas
			const T_REG_INFO_EX& sigdetthrs2();	//CSR42[10:0]

	/// signal detect threshold parameter3. suited to pcie 8G in pcie mode or common mode
			const T_REG_INFO_EX& sigdetthrs3();	//CSR43[10:0]

	/// Analog status for RX CTLE load replica block opamp offset calibration trigger
			const T_REG_INFO_EX& rxctlerepofftrig();	//CSR44[15:15]

	/// Power down control of CTLE stage 1 to 4.
	/// 0 = Power down.
	/// 1=  Power up
			const T_REG_INFO_EX& ctlestg1to4pwrdb();	//CSR44[14:14]

	/// Not used
			const T_REG_INFO_EX& replicacaldir();	//CSR44[13:13]

	/// Select configuration for CTLE load replica opamp
	/// 0 =   configure CTLE replica opamp for open-loop offset calibration.
	/// 1 =  configure CTLE replica opamp for mission-mode operation
			const T_REG_INFO_EX& ctlerepcalen();	//CSR44[12:12]

	/// Offset control for CTLE load replica. Used for manual offset calibration. 
	/// bit[5] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[4:1] - magnitude of offset,
	/// 111 = Maximum offset
	/// 000 = no offset 
	/// 
	/// bit[0] - Not used
			const T_REG_INFO_EX& ctlerepcalcode();	//CSR44[11:6]

	/// select CTLE replica reference voltage
	/// Voltage is relative to CTLE local supply (vreg)
	/// 000 =  vreg - 190mV
	/// 001 =  vreg - 200mV
	/// 010 =  vreg - 210mV
	/// 011 =  vreg - 220mV
	/// 100 =  vreg - 230mV
	/// 101 =  vreg - 240mV
	/// 110 =  vreg - 250mV
	/// 111 =  vreg - 260mV
			const T_REG_INFO_EX& ctlerefsel();	//CSR44[5:3]

	/// CTLE replica output mux control bits. 
	/// 
	/// 000:  Opamp output is selected (normal operation mode)
	/// 001:  lvcc
	/// 010:  vss
	/// 011:  0.57V
	/// 100:  0.47V
	/// 101:  0.36V
	/// 110:  0.31V
	/// 111:  0.26V
			const T_REG_INFO_EX& ctleloadsel();	//CSR44[2:0]

	/// DS power sequence time between steps for regulators(TBS3)
			const T_REG_INFO_EX& dspwrsqtbs3();	//CSR45[13:10]

	/// Set Comparator reference voltage selection for  CTLE regulator voltage calibration
	/// Calib Target (mV)= 600 * (1+vregctlerefsel/64)
	/// Note: CTLEVREGVREFRNG[1:0] must be correspondingly set to a range which supports the calibration target value
			const T_REG_INFO_EX& vregctlerefsel();	//CSR45[9:4]

	/// Center I-Channel sampling clock delay control 
	/// 00 = no delay
	/// 01 = 175fs
	/// 10 = 350fs
	/// 11 = 550fs
			const T_REG_INFO_EX& rxcpcendlyctrli();	//CSR45[3:2]

	/// Center Q-Channel sampling clock delay control 
	/// 00 = no delay
	/// 01 = 175fs
	/// 10 = 350fs
	/// 11 = 550fs
			const T_REG_INFO_EX& rxcpcendlyctrlq();	//CSR45[1:0]

	/// Rx center channel clocking path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpcenpwrdb();	//CSR46[15:15]

	/// Powerdown for center I-channel PI CML buffer stage.
	/// (Gated by RXCPCENPWRDB)
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpcenipibufpwrdb();	//CSR46[13:13]

	/// Powerdown for center I-channel PI CML2CMOS  stage.
	/// (Gated by RXCPCENPWRDB)
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpcenipicmlcmospwrdb();	//CSR46[12:12]

	/// Powerdown for center I-channel PI core  stage.
	/// (Gated by RXCPCENPWRDB)
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpcenipicorepwrdb();	//CSR46[11:11]

	/// Powerdown for center Q-channel PI CML buffer stage.
	/// (Gated by RXCPCENPWRDB)
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpcenqpibufpwrdb();	//CSR46[10:10]

	/// Powerdown for center Q-channel PI CML2CMOS  stage.
	/// (Gated by RXCPCENPWRDB)
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpcenqpicmlcmospwrdb();	//CSR46[9:9]

	/// Powerdown for center Q-channel PI core  stage.
	/// (Gated by RXCPCENPWRDB)
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpcenqpicorepwrdb();	//CSR46[8:8]

	/// Rx center channel PI  bias current scale. 
	/// 00 = Maximum current
	/// 11 = Minimum current
			const T_REG_INFO_EX& rxcpcenpibiastrim();	//CSR46[5:4]

	/// Rx center channel PI buffer bias current scale. 
	/// 00 = Minimum current
	/// 11 = Maximum current
			const T_REG_INFO_EX& rxcpcenpibufbiastrim();	//CSR46[3:2]

	/// Rx center channel PI buffer load resistance control. 
	/// 00 = Minimum load resistance
	/// 11 = Maximum load resistance
			const T_REG_INFO_EX& rxcpcenpibufloadtrim();	//CSR46[1:0]

	/// Rx edge channel clocking path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpedgpwrdb();	//CSR47[15:15]

	/// Powerdown for edge I-channel PI CML buffer stage.
	/// (Gated by RXCPEDGPWRDB)
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpedgipibufpwrdb();	//CSR47[14:14]

	/// Powerdown for edge I-channel PI CML2CMOS  stage.
	/// (Gated by RXCPEDGPWRDB)
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpedgipicmlcmospwrdb();	//CSR47[13:13]

	/// Powerdown for edge I-channel PI core  stage.
	/// (Gated by RXCPEDGPWRDB)
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpedgipicorepwrdb();	//CSR47[12:12]

	/// Powerdown for center Q-channel PI CML buffer stage.
	/// (Gated by RXCPEDGPWRDB)
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpedgqpibufpwrdb();	//CSR47[11:11]

	/// Powerdown for edge Q-channel PI CML2CMOS  stage.
	/// (Gated by RXCPEDGPWRDB)
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpedgqpicmlcmospwrdb();	//CSR47[10:10]

	/// Powerdown for edge Q-channel PI core  stage.
	/// (Gated by RXCPEDGPWRDB)
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpedgqpicorepwrdb();	//CSR47[9:9]

	/// Edge I-Channel sampling clock delay control 
	/// 00 = no delay
	/// 01 = 175fs
	/// 10 = 350fs
	/// 11 = 550fs
			const T_REG_INFO_EX& rxcpedgdlyctrli();	//CSR47[8:7]

	/// Edge Q-Channel sampling clock delay control 
	/// 00 = no delay
	/// 01 = 175fs
	/// 10 = 350fs
	/// 11 = 550fs
			const T_REG_INFO_EX& rxcpedgdlyctrlq();	//CSR47[6:5]

	/// Rx center PI spare control bits.
			const T_REG_INFO_EX& rxcpcenphsgenspare();	//CSR47[4:3]

	/// Rx edge PI spare control bits.
			const T_REG_INFO_EX& rxcpedgphsgenspare();	//CSR47[2:1]

	/// Enable Rx IQ detector  
	/// 0 = detector disabled
	/// 1 = detector enabled
			const T_REG_INFO_EX& rxiqdetpwrdb();	//CSR47[0:0]

	/// Rx monitor I-channel clocking path power down control. Active low.
	/// 0: Power down
	/// 1: Power up
			const T_REG_INFO_EX& rxcpmonpwrdb();	//CSR48[15:15]

	/// Rx monitor Q-channel clocking path power down control. Active low.
	/// 0: Power down
	/// 1: Power up
			const T_REG_INFO_EX& rxcpmonqpwrdb();	//CSR48[14:14]

	/// Powerdown for monitor I-channel PI CML buffer stage.
	/// (Gated by RXCPMONPWRDB)
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpmonipibufpwrdb();	//CSR48[13:13]

	/// Powerdown for monitor I-channel PI CML2CMOS  stage.
	/// (Gated by RXCPMONPWRDB)
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpmonipicmlcmospwrdb();	//CSR48[12:12]

	/// Powerdown for monitor I-channel PI core  stage.
	/// (Gated by RXCPMONPWRDB)
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpmonipicorepwrdb();	//CSR48[11:11]

	/// Powerdown for monitor Q-channel PI CML buffer stage.
	/// (Gated by RXCPMONPWRDB)
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpmonqpibufpwrdb();	//CSR48[10:10]

	/// Powerdown for monitor Q-channel PI CML2CMOS  stage.
	/// (Gated by RXCPMONPWRDB)
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpmonqpicmlcmospwrdb();	//CSR48[9:9]

	/// Powerdown for monitor Q-channel PI core  stage.
	/// (Gated by RXCPMONPWRDB)
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& rxcpmonqpicorepwrdb();	//CSR48[8:8]

	/// Monitor channel  Full (both I and Q  ch) or Partial (only I ch)   power up/down cycle mode when RXMONPWRDB is asserted/deasserted 
	/// 0=  Full monitor channel (both I and Q ch) will power up/down in sequence
	/// 1 = Partial monitor channel (only I ch) will power up/down  in sequence.  Q ch will remain powered down
			const T_REG_INFO_EX& rxmonpwrcycmode();	//CSR48[6:6]

	/// Monitor I and Q channel power  sequence control (also see RXMONPWRCYCMODE)
	/// 0= power down monitor  channel
	/// 1 = power up monitor channel 
	/// New in v101:  Now used as a trigger to power up/down the Monitor channel circuits in sequence with default settings
			const T_REG_INFO_EX& rxmonpwrdb();	//CSR48[5:5]

	/// Edge channel power sequence control
	/// 0 = power down edge channel
	/// 1 = power up edge channel
	/// New in v101:  Now used as a trigger to power up/down the Edge channel circuits in sequence with default settings
			const T_REG_INFO_EX& rxedgpwrdb();	//CSR48[4:4]

	/// Monitor I-Channel sampling clock delay control 
	/// 00: no delay
	/// 01: 175fs
	/// 10: 350fs
	/// 11: 550fs
			const T_REG_INFO_EX& rxcpmondlyctrli();	//CSR48[3:2]

	/// Monitor Q-Channel sampling clock delay control 
	/// 00: no delay
	/// 01: 175fs
	/// 10: 350fs
	/// 11: 550fs
			const T_REG_INFO_EX& rxcpmondlyctrlq();	//CSR48[1:0]

	/// Rx center slicer I path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& censlcipwrdb();	//CSR49[15:15]

	/// Rx center slicer Q path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& censlcqpwrdb();	//CSR49[14:14]

	/// Rx center slicer I_b path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& censlcibpwrdb();	//CSR49[13:13]

	/// Rx center slicer Q_b path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& censlcqbpwrdb();	//CSR49[12:12]

	/// Rx edge slicer I path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& edgslcipwrdb();	//CSR49[11:11]

	/// Rx edge slicer Q path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& edgslcqpwrdb();	//CSR49[10:10]

	/// Rx edge slicer I_b path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& edgslcibpwrdb();	//CSR49[9:9]

	/// Rx edge slicer Q_b path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& edgslcqbpwrdb();	//CSR49[8:8]

	/// Rx monitor slicer I path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& monslcipwrdb();	//CSR49[7:7]

	/// Rx monitor slicer I_b path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& monslcibpwrdb();	//CSR49[6:6]

	/// Rx center channel demux power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& cendemuxpwrdb();	//CSR49[5:5]

	/// Rx edge channel demux power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& edgdemuxpwrdb();	//CSR49[4:4]

	/// Rx monitor channel demux power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& mondemuxpwrdb();	//CSR49[3:3]

	/// Center channel power sequence control
	/// 0 = power down center channel
	/// 1 = power up center channel
	/// New in v101:  Now used as a trigger to power up/down the Center channel circuits in sequence with default settings
			const T_REG_INFO_EX& rxcenpwrdb();	//CSR49[2:2]

	/// Rx mon slicer Q path power down control. Active low.
	/// 0: Power down
	/// 1: Power up
			const T_REG_INFO_EX& monslcqpwrdb();	//CSR49[1:1]

	/// Rx mon slicer Q_b path power down control. Active low.
	/// 0: Power down
	/// 1: Power up
			const T_REG_INFO_EX& monslcqbpwrdb();	//CSR49[0:0]

	/// 0: selects vcm_refgen output voltage
	/// 1: selects common mode of ieven summer 
	///  Default is to use internally generated reference for alpha IDAC
			const T_REG_INFO_EX& dfesumvrefsel();	//CSR50[15:15]

	/// controls otbm output:
	/// 0: summer outputm is put on otbm (mode to calibrate summer offset)
	/// 1: vcmrefgen is put on otbm (mode to calibrate summer load resistor)
	/// 
	/// Set to 0 to calibrate summer offset
	/// Set to 1 to calibrate summer load resistance
	/// (The same atb control bus is used to select the individual summer output, this bit controls what is put on the otbm output when the summer atb is enabled)
			const T_REG_INFO_EX& dfesumrtrimen();	//CSR50[14:14]

	/// reference range select for rx vregclk regulator
	/// 00 = vref between 750mV  and  850mV
	/// 01 = vref  between 851mV and 925mV
	/// 10 = vref between 926mV and 985mV
	/// 11 = vref between 986mV and 1050mV
			const T_REG_INFO_EX& vregclkvrefrng();	//CSR50[13:12]

	/// Adjusts bandwidth of  rx vregclk regulator
	/// 00 =  min bandwidth, max gain
	/// ?.
	/// 11 =  max bandwidth, min gain
			const T_REG_INFO_EX& vregclkpreampsel();	//CSR50[11:10]

	/// reference range select for rx vregdata regulator
	/// 00 = vref between 750mV  and  850mV
	/// 01 = vref  between 851mV and 925mV
	/// 10 = vref between 926mV and 985mV
	/// 11 = vref between 986mV and 1050mV
			const T_REG_INFO_EX& vregdatavrefrng();	//CSR50[9:8]

	/// Rx DFE Isummer loading resistance trimming, target to 70ohm. 
	/// 0000 = Minimum load resistance
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum load resistance
			const T_REG_INFO_EX& dfesumrestrim();	//CSR50[7:4]

	/// Enable control of auxiliary offset of Rx DFE summers. Used during latch calibration.
	/// 0 = Disable
	/// 1 = Enable
			const T_REG_INFO_EX& dfesumauxofsten();	//CSR50[3:3]

	/// Polarity control of summer output which have auxiliary offset applied.
	/// 0: doutp = 1, doutm = 0
	/// 1: doutp = 0, doutm = 1
			const T_REG_INFO_EX& dfesumauxofstpol();	//CSR50[2:2]

	/// Selection of which summer to apply auxiliary offset.
	/// 00 = Ieven summer
	/// 01 = Qeven summer
	/// 10 = Iodd summer
	/// 11 = Qodd summer
			const T_REG_INFO_EX& dfesumauxofstsel();	//CSR50[1:0]

	/// Center channel DFE Tap 1 polarity and weight.
	/// 
	/// bit[7] - polarity bit,
	/// 0 = Positive polarity.
	/// 1 = Negative polarity.
	/// 
	/// bit[6:0] - weight
	/// 0000000 = Minimum magnitude (zero)
	/// 0000001 =
	/// 0000010 =
	/// ..
	/// 1111110 = 
	/// 1111111 = Maximum magnitude
			const T_REG_INFO_EX& dfefxtap1cen();	//CSR51[15:8]

	/// Edge channel DFE Tap 1 polarity and weight.
	/// 
	/// bit[7] - polarity bit,
	/// 0 = Positive polarity.
	/// 1 = Negative polarity.
	/// 
	/// bit[6:0] - weight (binary),
	/// 0000000 = Minimum magnitude (zero)
	/// 0000001 =
	/// 0000010 =
	/// ..
	/// 1111110 = 
	/// 1111111 = Maximum magnitude
			const T_REG_INFO_EX& dfefxtap1edg();	//CSR51[7:0]

	/// Rx DFE spare control bit is now Repurposed - 
	/// auxilliary clock divide by 5 mode control
	/// 0: div by 5 mode disabled
	/// 1: div by 5 mode enabled
			const T_REG_INFO_EX& dfespare();	//CSR52[15:15]

	/// Rx DFE tap injector scale control.
	/// 00 = 1mV step
	/// 01 = 1.4mV step
	/// 10 = 2mV step
	/// 11 = 3.5mV step
			const T_REG_INFO_EX& dfetapinjscale();	//CSR52[14:13]

	/// Rx DFE slicer bandwidth control. 
	/// 00 = Minimum slicer bandwidth
	/// 01 =
	/// 10 =
	/// 11 = Maximum slicer bandwidth
			const T_REG_INFO_EX& dfeslicerbwsel();	//CSR52[12:11]

	/// Vcm ref voltage for summer load resistance calibration
	/// Vcm_ref(mV) (IR drop from LVCC)
	/// 00 = 165mV   calibrates to 62 Ohms
	/// 01 = 172mV   calibrates to 64 Ohms
	/// 10 = 180mV   calibrates to 66 Ohms (default)
	/// 11 = 187mV   calibrates to 72 Ohms
			const T_REG_INFO_EX& rxdfesumvreftrim();	//CSR52[10:9]

	/// Rx DFE alphagen resistance trimming. 
	/// 000 = Minimum resistance
	/// 001 =
	/// 010 =
	/// 011 = Maximum resistance
	/// 100 to 111 = Reserved (Not used)
			const T_REG_INFO_EX& dfealphagenrtrim();	//CSR52[8:6]

	/// Select Rx DFE alphagen replica block reference voltage  
	/// 000 = Select summer_vref
	/// 001 = lvcc
	/// 010 = lvcc - 35mV
	/// 011 = lvcc - 70mV
	/// 100 = lvcc - 105mV
	/// 101 = lvcc - 140mV
	/// 110 = lvcc - 175mV
	/// 111 = lvcc - 210mV
			const T_REG_INFO_EX& dfealphagenrefsel();	//CSR52[5:3]

	/// Rx DFE alphagen replica block output mux control bits. 
	/// 000 = Opamp output is selected (normal operation mode)
	/// 001 = hvcc
	/// 010 = vss
	/// 011 = 720mV 
	/// 100 = 720mV
	/// 101 = 540mV
	/// 110 = 360mV
	/// 111 = 180mV
			const T_REG_INFO_EX& dfealphagenloadsel();	//CSR52[2:0]

	/// Rx clock path regulator power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& vregclkpwrdb();	//CSR53[15:15]

	/// Rx clocking regulator output voltage trimming.
	/// 0 = select voltage reference for SS corner
	/// 1 = select voltage reference for TT/FF corner
			const T_REG_INFO_EX& vregclkdpmen();	//CSR53[14:14]

	/// Rx clocking regulator bleed current control.
	/// 0: enable bleed current
	/// 1: disable bleed current
			const T_REG_INFO_EX& vregclkbleedb();	//CSR53[13:13]

	/// Voltage level control of Rx clocking regulator.  
	/// (default = 0.927V)
	/// 00000 = Minimum voltage.
	/// 00001
	/// 00010
	/// ..
	/// 10100= voltage (default)
	/// ?..
	/// 11111 = Maximum voltage.
			const T_REG_INFO_EX& vregclklvl();	//CSR53[12:8]

	/// Rx data path regulator power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& vregdatapwrdb();	//CSR53[7:7]

	/// Rx data regulator inrush current limit DPM trimming.
	/// 0 = select voltage reference for SS corner
	/// 1 = select voltage reference for TT/FF corner
			const T_REG_INFO_EX& vregdatadpmen();	//CSR53[6:6]

	/// Rx data regulator bleed current control.
	/// 0 = enable bleed current
	/// 1 = disable bleed current
			const T_REG_INFO_EX& vregdatableedb();	//CSR53[5:5]

	/// Voltage level control of Rx data regulator.(Default 0.927V)  
	/// 00000 = Minimum voltage.
	/// 00001 
	/// 00010
	/// ..
	/// 10100= voltage(default)
	/// ?..
	/// 11111 = Maximum voltage.
			const T_REG_INFO_EX& vregdatalvl();	//CSR53[4:0]

	/// RX clock regulator inrush current limit. Active low.
	/// 0: regulator inrush current limit  mode
	/// 1: regulator mission mode
			const T_REG_INFO_EX& vregclkinrushpwrdb();	//CSR54[15:15]

	/// RX data regulator inrush current limit. Active low.
	/// 0: regulator inrush current limit  mode
	/// 1: regulator mission mode
			const T_REG_INFO_EX& vregdatainrushpwrdb();	//CSR54[14:14]

	/// Set Comparator reference voltage selection for RX  clock regulator  voltage calibration
	/// Calib Target (mV)= 600 * (1+vregclkrefsel/64)
	/// Note: VREGCLKVREFRNG[1:0] must be correspondingly set to a range which supports the calibration target value
			const T_REG_INFO_EX& vregclkrefsel();	//CSR54[13:8]

	/// Comparator reference voltage selection for RX data regulator voltage calibration:
	/// Calib Target (mV)= 600 * (1+vregdatarefsel/64)
	/// Note: VREGDATAVREFRNG[1:0] must be correspondingly set to a range which supports the calibration target value
			const T_REG_INFO_EX& vregdatarefsel();	//CSR54[5:0]

	/// Rx_top ATB selection.
	/// 00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 = Selects Rx otbp bus
	/// 10 = Selects Rx otbm bus
	/// 11 = Disabled
			const T_REG_INFO_EX& rxatbmuxsel();	//CSR55[15:14]

	/// Rx DFE alphagen otbm output selection. Selected signal will go to rx_otbm.
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = Select rx_center_vthrm
	/// 010 = Select rx_edge_vthrm
	/// 011 = Select rx_mon_vthrm  (valid only from V101 IpDrop3.3 onwards)
	/// 100 = Select alphagen_vcm_vref
	/// 101 = Select alphagen_center_vcm  (valid only from V101 IpDrop3.3 onwards)
	/// 110 -111 =  no connect
			const T_REG_INFO_EX& dfealphagentopmatbctrl();	//CSR55[13:11]

	/// Rx DFE alphagen otbp output selection. Selected signal will go to rx_otbp.
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = Select rx_center_vthrp
	/// 010 = Select rx_edge_vthrp
	/// 011 = Select rx_mon_vthrp (valid only from V101 IpDrop3.3 onwards)
	/// 100 = Select  summer_vcm
	/// 101 = Select alphagen_center_vpbias (valid  only from V101 IpDrop3.3 onwards)
	/// 110 -111 =  no connect
			const T_REG_INFO_EX& dfealphagentoppatbctrl();	//CSR55[10:8]

	/// 0 = default
	/// 1 = mute/zero alphagen DAC output
			const T_REG_INFO_EX& dfealphagencenmute();	//CSR55[7:7]

	/// 0 = default
	/// 1 = mute/zero alphagen DAC output
			const T_REG_INFO_EX& dfealphagenedgmute();	//CSR55[6:6]

	/// 0 =  default
	/// 1 = mute/zero alphagen DAC output
			const T_REG_INFO_EX& dfealphagenmonmute();	//CSR55[5:5]

	/// [bad key===> "Rx DFE alphagen step size trim
	/// v101:  
	/// 0 = Minimum step size  (2.3mV)
	/// 1 = Maximum step size  ( 4mV)
	/// 
	/// v101 IpDrop3.3 and IpDrop3.4
	/// used in conjunction with DSSPARE[4] to expand programming resolution
	/// { DSSPARE[4], DFEALPHAGENSTEPSIZE }
	/// 00: step size ~ 1.5mV
	/// 01: step size ~ 2.0mV
	/// 10: step size ~ 2.5mV
	/// 11: step size ~ 3.0mV" <====key bad]
			const T_REG_INFO_EX& dfealphagenstepsize();	//CSR55[4:4]

	/// Rx DFE Ibias control. 
	/// 00 = 4.3mA (Minimum bias current)
	/// 01 = 4.5mA
	/// 10 = 5.3mA
	/// 11 = 6.5mA (Maximum bias current)
			const T_REG_INFO_EX& dfesumbias();	//CSR55[2:1]

	/// enable ptat bias of summer, active high
	/// 0= disable ptat bias
	/// 1 = enable ptat bias
			const T_REG_INFO_EX& rxdfesumbiasptaten();	//CSR55[0:0]

	/// Rx clock regulator ATB control. Selected signal will go to rx_otbp.
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = select vref
	/// 010 = select vlow 
	/// 011 = High Impedance
	/// 100 = High Impedance
	/// 101 = select vmid
	/// 110 = select rxclk 2/3 vreg sense
	/// 111 = High Impedance
			const T_REG_INFO_EX& vregclkatbctrl();	//CSR56[15:13]

	/// Rx data regulator ATB control. Selected signal will go to rx_otbp.
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = select vref
	/// 010 = select vlow
	/// 011 = High Impedance
	/// 100 = High Impedance
	/// 101 = select vmid
	/// 110 = select rxdata 2/3 vreg sense
	/// 111 = High Impedance
			const T_REG_INFO_EX& vregdataatbctrl();	//CSR56[12:10]

	/// Comparator reference voltage selection for RX supply trim summer calibration:
	/// 000000: Vref=400mV
	/// 000001: Vref=406.25mV
	/// 000010: Vref=412.5mV
	/// ..
	/// 111111: Vref=800mV
			const T_REG_INFO_EX& suptrimsummerrefsel();	//CSR56[5:0]

	/// 0 = AC-JTAG receiver is controlled by pins
	/// ;1 = AC-JTAG receiver is controlled by register.
			const T_REG_INFO_EX& jtagsel();	//CSR57[11:11]

	/// RX JTAG Positive output
			const T_REG_INFO_EX& jtagoutp();	//CSR57[10:10]

	/// RX JTAG Negative output
			const T_REG_INFO_EX& jtagoutm();	//CSR57[9:9]

	/// RX JTAG power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
			const T_REG_INFO_EX& jtagpwrdb();	//CSR57[8:8]

	/// Rx JTAG AC mode enable control.
	/// 0 = Disable AC mode (use DC mode)
	/// 1 = Enable AC mode
			const T_REG_INFO_EX& jtagacmodeen();	//CSR57[7:7]

	/// Rx JTAG initial clock.
			const T_REG_INFO_EX& jtaginitclk();	//CSR57[6:6]

	/// Rx JTAG initial P input.
			const T_REG_INFO_EX& jtaginitp();	//CSR57[5:5]

	/// Rx JTAG initial M input.
			const T_REG_INFO_EX& jtaginitm();	//CSR57[4:4]

	/// RX JTAG hysteresis threshold control.
	/// Not used for now.
			const T_REG_INFO_EX& jtaghystadj();	//CSR57[3:2]

	/// Rx JTAG threshold control. 
	/// 00 = Minimum threshold
	/// 01
	/// 10
	/// 11 = Maximum threshold
			const T_REG_INFO_EX& jtagthadj();	//CSR57[1:0]

	/// not used
			const T_REG_INFO_EX& ceearly();	//CSR58[15:15]

	/// not used
			const T_REG_INFO_EX& celate();	//CSR58[14:14]

	/// Center - Monitor Channel Early status for coarse align
			const T_REG_INFO_EX& cmearly();	//CSR58[13:13]

	/// Center - Monitor Channel Late status for coarse align
			const T_REG_INFO_EX& cmlate();	//CSR58[12:12]

	/// Edge channel sleep control.
	/// 0 = Mission mode
	/// 1 = Sleep mode
			const T_REG_INFO_EX& edgesleep();	//CSR58[8:8]

	/// Center-Edge coarse align enable. 
	/// 0 = Disable
	/// 1 = Enable
			const T_REG_INFO_EX& ecoarsealignen();	//CSR58[7:7]

	/// Center-Edge coarse alignment step.
	/// 000 = +48;   100 = -48
	/// ;001 = +54;   101 = -54
	/// ;010 = +60;   110 = -60
	/// ;011 = +64;   111 = -64.
			const T_REG_INFO_EX& ecoarsealignstep();	//CSR58[6:4]

	/// Rx center-monitor coarse alignment enable control. Active low.
	/// 0: Disable coarse alignment.
	/// 1: Enable coarse alignement.
			const T_REG_INFO_EX& mcoarsealignen();	//CSR58[3:3]

	/// Monitor-Center coarse alignment step.
	/// 000 = +48;   100 = -48
	/// ;001 = +54;   101 = -54
	/// ;010 = +60;   110 = -60
	/// ;011 = +64;   111 = -64.
			const T_REG_INFO_EX& mcoarsealignstep();	//CSR58[2:0]

	/// not used
			const T_REG_INFO_EX& misierrdone();	//CSR59[15:15]

	/// This register contains the present binary phase setting of the center channel phase interpolator.
			const T_REG_INFO_EX& cphsval();	//CSR59[14:8]

	/// This register contains the present binary phase setting of the edge channel phase interpolator.
			const T_REG_INFO_EX& ephsval();	//CSR59[6:0]

	/// This register contains the present binary phase setting of the monitor channel phase interpolator.
			const T_REG_INFO_EX& mphsofstval();	//CSR60[15:9]

	/// Eye monitor voltage offset.
			const T_REG_INFO_EX& mvolofstval();	//CSR60[8:0]

	/// Mismatch count which is calculated as,  
	/// if MMCNT[15:11] is zero, total count is MMCNT[10:0]
	/// if MMCNT[15:11] is non zero, total count is 2pow(10+MMCNT[15:11] ) +MMCNT[10:0] *2pow(MMCNT[15:11]-1)
			const T_REG_INFO_EX& mmcnt();	//CSR61[15:0]

	/// TIMEREXP[4:0] gives the exponent portion of the internal 42-bit timer.
	/// 0 = MSB of the timer is at position 10 in the complete count
	/// 1 = MSB of the timer is at position 11 in the complete count
	/// 2 = MSB of the timer is at position 12 in the complete count
	/// ..
	/// 31 = MSB of the timer is at position 41 in the complete count
			const T_REG_INFO_EX& timerexp();	//CSR62[15:11]

	/// TIMER[10:0], together with the exponent portion (TIMEREXP[4:0]), gives the cycle count of the counting clock. TIMER[10:0] is only the lower 11-bit portion of the internal 42-bit timer.
			const T_REG_INFO_EX& timer();	//CSR62[10:0]

	/// Configuration of timer for waiting, which is the cycles of reference clock. Timer value = (2 pow RXCALTIMERVALUE) -1 , where RXCALTIMERVALUE =0 to 22.
			const T_REG_INFO_EX& rxcal_timer_value();	//CSR63[14:5]

	/// Not used
			const T_REG_INFO_EX& rxcal_timer_div_value();	//CSR63[4:2]

	/// Not used
			const T_REG_INFO_EX& rxcal_timer_div_en();	//CSR63[1:1]

	/// Stop timer, for debugging.
	/// 0 = normal
	/// 1 = stop the timer
			const T_REG_INFO_EX& rxcal_timer_stop();	//CSR63[0:0]
			bool get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos);
	};
public:
	_REG_INFO REG_INFO;

	uint csr[DS_RX_CSR_NUM];


	//CSR0[15:15]
	DS_rxRegs& setrxpwrdb(uint val);
	uint getrxpwrdb();

	//CSR0[14:14]
	DS_rxRegs& setrxauxclkpwrdb(uint val);
	uint getrxauxclkpwrdb();

	//CSR0[11:11]
	DS_rxRegs& setlpcmlen(uint val);
	uint getlpcmlen();

	//CSR0[9:9]
	DS_rxRegs& setrxmute(uint val);
	uint getrxmute();

	//CSR0[8:8]
	DS_rxRegs& setctleboosten1(uint val);
	uint getctleboosten1();

	//CSR0[4:3]
	DS_rxRegs& setrxauxclkdiv(uint val);
	uint getrxauxclkdiv();

	//CSR0[2:0]
	DS_rxRegs& setctlepassgn(uint val);
	uint getctlepassgn();

	//CSR1[15:15]
	DS_rxRegs& setctlehfzen1(uint val);
	uint getctlehfzen1();

	//CSR1[14:12]
	DS_rxRegs& setctleboostc1(uint val);
	uint getctleboostc1();

	//CSR1[11:10]
	DS_rxRegs& setctlecmband1(uint val);
	uint getctlecmband1();

	//CSR1[9:8]
	DS_rxRegs& setctlermband1(uint val);
	uint getctlermband1();

	//CSR1[7:5]
	DS_rxRegs& setctleza1(uint val);
	uint getctleza1();

	//CSR1[4:3]
	DS_rxRegs& setctlesqh1(uint val);
	uint getctlesqh1();

	//CSR1[2:0]
	DS_rxRegs& setctleactgn1(uint val);
	uint getctleactgn1();

	//CSR2[15:15]
	DS_rxRegs& setctlehfzen2(uint val);
	uint getctlehfzen2();

	//CSR2[14:12]
	DS_rxRegs& setctleboostc2(uint val);
	uint getctleboostc2();

	//CSR2[11:10]
	DS_rxRegs& setctlecmband2(uint val);
	uint getctlecmband2();

	//CSR2[9:8]
	DS_rxRegs& setctlermband2(uint val);
	uint getctlermband2();

	//CSR2[7:5]
	DS_rxRegs& setctleza2(uint val);
	uint getctleza2();

	//CSR2[4:3]
	DS_rxRegs& setctlesqh2(uint val);
	uint getctlesqh2();

	//CSR2[2:0]
	DS_rxRegs& setctleactgn2(uint val);
	uint getctleactgn2();

	//CSR3[15:15]
	DS_rxRegs& setctlehfzen3(uint val);
	uint getctlehfzen3();

	//CSR3[14:12]
	DS_rxRegs& setctleboostc3(uint val);
	uint getctleboostc3();

	//CSR3[11:10]
	DS_rxRegs& setctlecmband3(uint val);
	uint getctlecmband3();

	//CSR3[9:8]
	DS_rxRegs& setctlermband3(uint val);
	uint getctlermband3();

	//CSR3[7:5]
	DS_rxRegs& setctleza3(uint val);
	uint getctleza3();

	//CSR3[4:3]
	DS_rxRegs& setctlesqh3(uint val);
	uint getctlesqh3();

	//CSR3[2:0]
	DS_rxRegs& setctleactgn3(uint val);
	uint getctleactgn3();

	//CSR4[3:3]
	DS_rxRegs& setctlegnlunpken1(uint val);
	uint getctlegnlunpken1();

	//CSR4[2:2]
	DS_rxRegs& setctlegnlunpken2(uint val);
	uint getctlegnlunpken2();

	//CSR4[1:1]
	DS_rxRegs& setctlegnlunpken3(uint val);
	uint getctlegnlunpken3();

	//CSR5[15:15]
	DS_rxRegs& setdfepwrdb(uint val);
	uint getdfepwrdb();

	//CSR5[14:14]
	DS_rxRegs& setdfemvtappwrdb(uint val);
	uint getdfemvtappwrdb();

	//CSR5[13:5]
	DS_rxRegs& setdfefxtappwrdb(uint val);
	uint getdfefxtappwrdb();

	//CSR5[4:3]
	DS_rxRegs& setdfesumboost(uint val);
	uint getdfesumboost();

	//CSR5[2:0]
	DS_rxRegs& setdfegnsum(uint val);
	uint getdfegnsum();

	//CSR6[7:7]
	DS_rxRegs& setrxdfemainpwrdb(uint val);
	uint getrxdfemainpwrdb();

	//CSR6[6:0]
	DS_rxRegs& setdfefxtap2(uint val);
	uint getdfefxtap2();

	//CSR7[13:8]
	DS_rxRegs& setdfefxtap3(uint val);
	uint getdfefxtap3();

	//CSR7[5:0]
	DS_rxRegs& setdfefxtap4(uint val);
	uint getdfefxtap4();

	//CSR8[15:10]
	DS_rxRegs& setdfefxtap5(uint val);
	uint getdfefxtap5();

	//CSR8[9:5]
	DS_rxRegs& setdfefxtap6(uint val);
	uint getdfefxtap6();

	//CSR8[4:0]
	DS_rxRegs& setdfefxtap7(uint val);
	uint getdfefxtap7();

	//CSR9[12:8]
	DS_rxRegs& setdfefxtap8(uint val);
	uint getdfefxtap8();

	//CSR9[4:0]
	DS_rxRegs& setdfefxtap9(uint val);
	uint getdfefxtap9();

	//CSR10[14:10]
	DS_rxRegs& setdfemvtap1(uint val);
	uint getdfemvtap1();

	//CSR10[9:5]
	DS_rxRegs& setdfemvtap2(uint val);
	uint getdfemvtap2();

	//CSR10[4:0]
	DS_rxRegs& setdfemvtap3(uint val);
	uint getdfemvtap3();

	//CSR11[14:10]
	DS_rxRegs& setdfemvtap4(uint val);
	uint getdfemvtap4();

	//CSR11[9:5]
	DS_rxRegs& setdfemvtap5(uint val);
	uint getdfemvtap5();

	//CSR11[4:0]
	DS_rxRegs& setdfemvtap6(uint val);
	uint getdfemvtap6();

	//CSR12[15:15]
	DS_rxRegs& setrxrstb(uint val);
	uint getrxrstb();

	//CSR12[14:13]
	DS_rxRegs& setrxdwidth(uint val);
	uint getrxdwidth();

	//CSR12[12:10]
	DS_rxRegs& setrxratemode(uint val);
	uint getrxratemode();

	//CSR12[9:9]
	DS_rxRegs& setrxbitorder(uint val);
	uint getrxbitorder();

	//CSR12[8:8]
	DS_rxRegs& setrxpolarity(uint val);
	uint getrxpolarity();

	//CSR12[7:7]
	DS_rxRegs& settxrxparlpbken(uint val);
	uint gettxrxparlpbken();

	//CSR12[6:6]
	DS_rxRegs& setmdatasel(uint val);
	uint getmdatasel();

	//CSR12[5:5]
	DS_rxRegs& settap1en(uint val);
	uint gettap1en();

	//CSR12[4:4]
	DS_rxRegs& settap1pol(uint val);
	uint gettap1pol();

	//CSR12[3:3]
	DS_rxRegs& setcdrfreeze(uint val);
	uint getcdrfreeze();

	//CSR12[2:2]
	DS_rxRegs& setboxcarsel(uint val);
	uint getboxcarsel();

	//CSR12[1:1]
	DS_rxRegs& setsecloopen(uint val);
	uint getsecloopen();

	//CSR12[0:0]
	DS_rxRegs& setbitslip(uint val);
	uint getbitslip();

	//CSR13[15:15]
	DS_rxRegs& setcdrrstb(uint val);
	uint getcdrrstb();

	//CSR13[14:12]
	DS_rxRegs& setphsgn(uint val);
	uint getphsgn();

	//CSR13[7:7]
	DS_rxRegs& setcdredgeoffen(uint val);
	uint getcdredgeoffen();

	//CSR13[6:6]
	DS_rxRegs& setcpafreeze(uint val);
	uint getcpafreeze();

	//CSR13[5:4]
	DS_rxRegs& setcpagainsel(uint val);
	uint getcpagainsel();

	//CSR13[3:3]
	DS_rxRegs& setcpaenable(uint val);
	uint getcpaenable();

	//CSR13[2:0]
	DS_rxRegs& setfreqgn(uint val);
	uint getfreqgn();

	//CSR14[15:8]
	DS_rxRegs& setcphsofst(uint val);
	uint getcphsofst();

	//CSR14[7:0]
	DS_rxRegs& setephsofst(uint val);
	uint getephsofst();

	//CSR15[15:15]
	DS_rxRegs& settdden(uint val);
	uint gettdden();

	//CSR15[14:12]
	DS_rxRegs& settddthr(uint val);
	uint gettddthr();

	//CSR15[11:11]
	DS_rxRegs& setloseyeen(uint val);
	uint getloseyeen();

	//CSR15[10:9]
	DS_rxRegs& setloseyethr(uint val);
	uint getloseyethr();

	//CSR15[8:8]
	DS_rxRegs& settimecntclr(uint val);
	uint gettimecntclr();

	//CSR15[7:5]
	DS_rxRegs& setloscfg(uint val);
	uint getloscfg();

	//CSR15[4:4]
	uint getlos();

	//CSR15[3:3]
	uint getlostran();

	//CSR15[2:2]
	uint getloseyever();

	//CSR15[1:1]
	uint getloseyehor();

	//CSR15[0:0]
	uint getlosana();

	//CSR16[15:15]
	DS_rxRegs& settimecntstart(uint val);
	uint gettimecntstart();

	//CSR16[14:8]
	DS_rxRegs& setmoniqofst(uint val);
	uint getmoniqofst();

	//CSR16[7:7]
	DS_rxRegs& setprbsemdatasel(uint val);
	uint getprbsemdatasel();

	//CSR16[6:6]
	DS_rxRegs& setvolofstpol(uint val);
	uint getvolofstpol();

	//CSR16[5:5]
	DS_rxRegs& setprbschken(uint val);
	uint getprbschken();

	//CSR16[4:4]
	DS_rxRegs& setprbschkmode(uint val);
	uint getprbschkmode();

	//CSR16[3:0]
	DS_rxRegs& setprbschkpatsel(uint val);
	uint getprbschkpatsel();

	//CSR17[15:15]
	DS_rxRegs& seteyemonpwrdb(uint val);
	uint geteyemonpwrdb();

	//CSR17[14:14]
	DS_rxRegs& seteyescanstart(uint val);
	uint geteyescanstart();

	//CSR17[13:13]
	uint getemready();

	//CSR17[12:12]
	uint getemtaskstatus();

	//CSR17[11:9]
	DS_rxRegs& seteyescanmode(uint val);
	uint geteyescanmode();

	//CSR17[8:8]
	uint getemvolovrmax();

	//CSR17[7:7]
	DS_rxRegs& setcompeyeen(uint val);
	uint getcompeyeen();

	//CSR17[6:6]
	DS_rxRegs& seteyescanwinsel(uint val);
	uint geteyescanwinsel();

	//CSR17[5:0]
	DS_rxRegs& seteyescanwin(uint val);
	uint geteyescanwin();

	//CSR18[8:0]
	DS_rxRegs& setmphsofst(uint val);
	uint getmphsofst();

	//CSR19[15:9]
	DS_rxRegs& setceniqofst(uint val);
	uint getceniqofst();

	//CSR19[8:7]
	DS_rxRegs& setmonslcsel(uint val);
	uint getmonslcsel();

	//CSR19[6:0]
	DS_rxRegs& setedgiqofst(uint val);
	uint getedgiqofst();

	//CSR20[15:15]
	uint getprbserr();

	//CSR20[14:11]
	uint getprbscntexp();

	//CSR20[10:0]
	uint getprbscnt();

	//CSR21[15:0]
	DS_rxRegs& setmmthr(uint val);
	uint getmmthr();

	//CSR22[13:12]
	DS_rxRegs& setemfoureyesel(uint val);
	uint getemfoureyesel();

	//CSR22[8:0]
	DS_rxRegs& setmvolofst(uint val);
	uint getmvolofst();

	//CSR23[8:0]
	uint getemresult0();

	//CSR24[8:0]
	uint getemresult1();

	//CSR25[15:12]
	DS_rxRegs& seteyescanctrl(uint val);
	uint geteyescanctrl();

	//CSR25[11:8]
	DS_rxRegs& seteyemontask(uint val);
	uint geteyemontask();

	//CSR25[7:7]
	DS_rxRegs& seteyescanalg(uint val);
	uint geteyescanalg();

	//CSR25[6:2]
	DS_rxRegs& setemtaskctrl(uint val);
	uint getemtaskctrl();

	//CSR25[1:1]
	DS_rxRegs& setemcornerscaling(uint val);
	uint getemcornerscaling();

	//CSR25[0:0]
	DS_rxRegs& setemcornergrden(uint val);
	uint getemcornergrden();

	//CSR26[7:0]
	DS_rxRegs& setmonvolscanstltime(uint val);
	uint getmonvolscanstltime();

	//CSR27[15:12]
	DS_rxRegs& setemtaskavrg(uint val);
	uint getemtaskavrg();

	//CSR27[8:0]
	DS_rxRegs& setcornerofst0(uint val);
	uint getcornerofst0();

	//CSR28[8:0]
	DS_rxRegs& setcornerofst1(uint val);
	uint getcornerofst1();

	//CSR29[15:0]
	uint getemresult2();

	//CSR30[8:0]
	DS_rxRegs& setmvolmax(uint val);
	uint getmvolmax();

	//CSR31[15:15]
	DS_rxRegs& setrxtermcalsel(uint val);
	uint getrxtermcalsel();

	//CSR31[14:14]
	DS_rxRegs& setrxtermcaldir(uint val);
	uint getrxtermcaldir();

	//CSR31[13:13]
	DS_rxRegs& setrxlatofstrangescale(uint val);
	uint getrxlatofstrangescale();

	//CSR31[12:12]
	DS_rxRegs& setrxctlerepopcalmode(uint val);
	uint getrxctlerepopcalmode();

	//CSR31[3:0]
	DS_rxRegs& setrxtermcal(uint val);
	uint getrxtermcal();

	//CSR32[15:15]
	DS_rxRegs& setrxcalmode(uint val);
	uint getrxcalmode();

	//CSR32[14:14]
	DS_rxRegs& setdscalstart(uint val);
	uint getdscalstart();

	//CSR32[13:13]
	DS_rxRegs& setrxcalstart(uint val);
	uint getrxcalstart();

	//CSR32[12:12]
	DS_rxRegs& setrxtermfloating(uint val);
	uint getrxtermfloating();

	//CSR32[7:7]
	DS_rxRegs& setrxdatalatchcalen(uint val);
	uint getrxdatalatchcalen();

	//CSR32[6:6]
	DS_rxRegs& setrxofstcaldir(uint val);
	uint getrxofstcaldir();

	//CSR32[5:0]
	DS_rxRegs& setrxofstsel(uint val);
	uint getrxofstsel();

	//CSR33[14:10]
	DS_rxRegs& setctleofst1(uint val);
	uint getctleofst1();

	//CSR33[9:5]
	DS_rxRegs& setctleofst2(uint val);
	uint getctleofst2();

	//CSR33[4:0]
	DS_rxRegs& setctleofst3(uint val);
	uint getctleofst3();

	//CSR34[14:10]
	DS_rxRegs& setctleofst4(uint val);
	uint getctleofst4();

	//CSR34[9:5]
	DS_rxRegs& setctleofst5(uint val);
	uint getctleofst5();

	//CSR34[4:0]
	DS_rxRegs& setctleofst6(uint val);
	uint getctleofst6();

	//CSR35[14:10]
	DS_rxRegs& setdfeievnsumofst(uint val);
	uint getdfeievnsumofst();

	//CSR35[9:5]
	DS_rxRegs& setdfeioddsumofst(uint val);
	uint getdfeioddsumofst();

	//CSR35[4:0]
	DS_rxRegs& setdfeqevnsumofst(uint val);
	uint getdfeqevnsumofst();

	//CSR36[14:10]
	DS_rxRegs& setdfeqoddsumofst(uint val);
	uint getdfeqoddsumofst();

	//CSR36[7:5]
	DS_rxRegs& setrxctleibiastune(uint val);
	uint getrxctleibiastune();

	//CSR36[2:0]
	DS_rxRegs& setrxctlepasstune(uint val);
	uint getrxctlepasstune();

	//CSR37[11:8]
	DS_rxRegs& setctleiptattcctrl(uint val);
	uint getctleiptattcctrl();

	//CSR37[6:6]
	DS_rxRegs& setctleiptatbypass(uint val);
	uint getctleiptatbypass();

	//CSR37[5:5]
	DS_rxRegs& setctlescresen(uint val);
	uint getctlescresen();

	//CSR37[4:0]
	DS_rxRegs& setctlescresclkdiv(uint val);
	uint getctlescresclkdiv();

	//CSR38[15:15]
	DS_rxRegs& setrxsigdetpwrdb(uint val);
	uint getrxsigdetpwrdb();

	//CSR38[14:13]
	DS_rxRegs& setrxsigdetclkdiv(uint val);
	uint getrxsigdetclkdiv();

	//CSR38[12:12]
	DS_rxRegs& setrxsigdetclkdlysel(uint val);
	uint getrxsigdetclkdlysel();

	//CSR38[10:10]
	DS_rxRegs& setrxsigdetcalpwrdb(uint val);
	uint getrxsigdetcalpwrdb();

	//CSR38[9:9]
	DS_rxRegs& setrxdigdetclkbufen(uint val);
	uint getrxdigdetclkbufen();

	//CSR38[8:8]
	DS_rxRegs& setrxsigdetatbsel(uint val);
	uint getrxsigdetatbsel();

	//CSR39[13:10]
	DS_rxRegs& setrxsigdetvthres(uint val);
	uint getrxsigdetvthres();

	//CSR39[9:8]
	DS_rxRegs& setrxsigdethyst(uint val);
	uint getrxsigdethyst();

	//CSR39[4:0]
	DS_rxRegs& setrxsigdetoffset(uint val);
	uint getrxsigdetoffset();

	//CSR40[15:15]
	uint getsigdetsqlchlos();

	//CSR40[14:14]
	uint getsigdetlos();

	//CSR40[13:13]
	DS_rxRegs& setsigdettxrxstat(uint val);
	uint getsigdettxrxstat();

	//CSR40[11:8]
	DS_rxRegs& setsigdetwin(uint val);
	uint getsigdetwin();

	//CSR40[6:5]
	DS_rxRegs& setsigdetpmamode(uint val);
	uint getsigdetpmamode();

	//CSR40[4:4]
	DS_rxRegs& setsigdetmanual(uint val);
	uint getsigdetmanual();

	//CSR40[3:1]
	DS_rxRegs& setsigdetthrselman(uint val);
	uint getsigdetthrselman();

	//CSR40[0:0]
	DS_rxRegs& setsigdeten(uint val);
	uint getsigdeten();

	//CSR41[14:12]
	DS_rxRegs& setsigdetthrcfgsel(uint val);
	uint getsigdetthrcfgsel();

	//CSR41[10:0]
	DS_rxRegs& setsigdetthrs1(uint val);
	uint getsigdetthrs1();

	//CSR42[10:0]
	DS_rxRegs& setsigdetthrs2(uint val);
	uint getsigdetthrs2();

	//CSR43[10:0]
	DS_rxRegs& setsigdetthrs3(uint val);
	uint getsigdetthrs3();

	//CSR44[15:15]
	uint getrxctlerepofftrig();

	//CSR44[14:14]
	DS_rxRegs& setctlestg1to4pwrdb(uint val);
	uint getctlestg1to4pwrdb();

	//CSR44[13:13]
	DS_rxRegs& setreplicacaldir(uint val);
	uint getreplicacaldir();

	//CSR44[12:12]
	DS_rxRegs& setctlerepcalen(uint val);
	uint getctlerepcalen();

	//CSR44[11:6]
	DS_rxRegs& setctlerepcalcode(uint val);
	uint getctlerepcalcode();

	//CSR44[5:3]
	DS_rxRegs& setctlerefsel(uint val);
	uint getctlerefsel();

	//CSR44[2:0]
	DS_rxRegs& setctleloadsel(uint val);
	uint getctleloadsel();

	//CSR45[13:10]
	DS_rxRegs& setdspwrsqtbs3(uint val);
	uint getdspwrsqtbs3();

	//CSR45[9:4]
	DS_rxRegs& setvregctlerefsel(uint val);
	uint getvregctlerefsel();

	//CSR45[3:2]
	DS_rxRegs& setrxcpcendlyctrli(uint val);
	uint getrxcpcendlyctrli();

	//CSR45[1:0]
	DS_rxRegs& setrxcpcendlyctrlq(uint val);
	uint getrxcpcendlyctrlq();

	//CSR46[15:15]
	DS_rxRegs& setrxcpcenpwrdb(uint val);
	uint getrxcpcenpwrdb();

	//CSR46[13:13]
	DS_rxRegs& setrxcpcenipibufpwrdb(uint val);
	uint getrxcpcenipibufpwrdb();

	//CSR46[12:12]
	DS_rxRegs& setrxcpcenipicmlcmospwrdb(uint val);
	uint getrxcpcenipicmlcmospwrdb();

	//CSR46[11:11]
	DS_rxRegs& setrxcpcenipicorepwrdb(uint val);
	uint getrxcpcenipicorepwrdb();

	//CSR46[10:10]
	DS_rxRegs& setrxcpcenqpibufpwrdb(uint val);
	uint getrxcpcenqpibufpwrdb();

	//CSR46[9:9]
	DS_rxRegs& setrxcpcenqpicmlcmospwrdb(uint val);
	uint getrxcpcenqpicmlcmospwrdb();

	//CSR46[8:8]
	DS_rxRegs& setrxcpcenqpicorepwrdb(uint val);
	uint getrxcpcenqpicorepwrdb();

	//CSR46[5:4]
	DS_rxRegs& setrxcpcenpibiastrim(uint val);
	uint getrxcpcenpibiastrim();

	//CSR46[3:2]
	DS_rxRegs& setrxcpcenpibufbiastrim(uint val);
	uint getrxcpcenpibufbiastrim();

	//CSR46[1:0]
	DS_rxRegs& setrxcpcenpibufloadtrim(uint val);
	uint getrxcpcenpibufloadtrim();

	//CSR47[15:15]
	DS_rxRegs& setrxcpedgpwrdb(uint val);
	uint getrxcpedgpwrdb();

	//CSR47[14:14]
	DS_rxRegs& setrxcpedgipibufpwrdb(uint val);
	uint getrxcpedgipibufpwrdb();

	//CSR47[13:13]
	DS_rxRegs& setrxcpedgipicmlcmospwrdb(uint val);
	uint getrxcpedgipicmlcmospwrdb();

	//CSR47[12:12]
	DS_rxRegs& setrxcpedgipicorepwrdb(uint val);
	uint getrxcpedgipicorepwrdb();

	//CSR47[11:11]
	DS_rxRegs& setrxcpedgqpibufpwrdb(uint val);
	uint getrxcpedgqpibufpwrdb();

	//CSR47[10:10]
	DS_rxRegs& setrxcpedgqpicmlcmospwrdb(uint val);
	uint getrxcpedgqpicmlcmospwrdb();

	//CSR47[9:9]
	DS_rxRegs& setrxcpedgqpicorepwrdb(uint val);
	uint getrxcpedgqpicorepwrdb();

	//CSR47[8:7]
	DS_rxRegs& setrxcpedgdlyctrli(uint val);
	uint getrxcpedgdlyctrli();

	//CSR47[6:5]
	DS_rxRegs& setrxcpedgdlyctrlq(uint val);
	uint getrxcpedgdlyctrlq();

	//CSR47[4:3]
	DS_rxRegs& setrxcpcenphsgenspare(uint val);
	uint getrxcpcenphsgenspare();

	//CSR47[2:1]
	DS_rxRegs& setrxcpedgphsgenspare(uint val);
	uint getrxcpedgphsgenspare();

	//CSR47[0:0]
	DS_rxRegs& setrxiqdetpwrdb(uint val);
	uint getrxiqdetpwrdb();

	//CSR48[15:15]
	DS_rxRegs& setrxcpmonpwrdb(uint val);
	uint getrxcpmonpwrdb();

	//CSR48[14:14]
	DS_rxRegs& setrxcpmonqpwrdb(uint val);
	uint getrxcpmonqpwrdb();

	//CSR48[13:13]
	DS_rxRegs& setrxcpmonipibufpwrdb(uint val);
	uint getrxcpmonipibufpwrdb();

	//CSR48[12:12]
	DS_rxRegs& setrxcpmonipicmlcmospwrdb(uint val);
	uint getrxcpmonipicmlcmospwrdb();

	//CSR48[11:11]
	DS_rxRegs& setrxcpmonipicorepwrdb(uint val);
	uint getrxcpmonipicorepwrdb();

	//CSR48[10:10]
	DS_rxRegs& setrxcpmonqpibufpwrdb(uint val);
	uint getrxcpmonqpibufpwrdb();

	//CSR48[9:9]
	DS_rxRegs& setrxcpmonqpicmlcmospwrdb(uint val);
	uint getrxcpmonqpicmlcmospwrdb();

	//CSR48[8:8]
	DS_rxRegs& setrxcpmonqpicorepwrdb(uint val);
	uint getrxcpmonqpicorepwrdb();

	//CSR48[6:6]
	DS_rxRegs& setrxmonpwrcycmode(uint val);
	uint getrxmonpwrcycmode();

	//CSR48[5:5]
	DS_rxRegs& setrxmonpwrdb(uint val);
	uint getrxmonpwrdb();

	//CSR48[4:4]
	DS_rxRegs& setrxedgpwrdb(uint val);
	uint getrxedgpwrdb();

	//CSR48[3:2]
	DS_rxRegs& setrxcpmondlyctrli(uint val);
	uint getrxcpmondlyctrli();

	//CSR48[1:0]
	DS_rxRegs& setrxcpmondlyctrlq(uint val);
	uint getrxcpmondlyctrlq();

	//CSR49[15:15]
	DS_rxRegs& setcenslcipwrdb(uint val);
	uint getcenslcipwrdb();

	//CSR49[14:14]
	DS_rxRegs& setcenslcqpwrdb(uint val);
	uint getcenslcqpwrdb();

	//CSR49[13:13]
	DS_rxRegs& setcenslcibpwrdb(uint val);
	uint getcenslcibpwrdb();

	//CSR49[12:12]
	DS_rxRegs& setcenslcqbpwrdb(uint val);
	uint getcenslcqbpwrdb();

	//CSR49[11:11]
	DS_rxRegs& setedgslcipwrdb(uint val);
	uint getedgslcipwrdb();

	//CSR49[10:10]
	DS_rxRegs& setedgslcqpwrdb(uint val);
	uint getedgslcqpwrdb();

	//CSR49[9:9]
	DS_rxRegs& setedgslcibpwrdb(uint val);
	uint getedgslcibpwrdb();

	//CSR49[8:8]
	DS_rxRegs& setedgslcqbpwrdb(uint val);
	uint getedgslcqbpwrdb();

	//CSR49[7:7]
	DS_rxRegs& setmonslcipwrdb(uint val);
	uint getmonslcipwrdb();

	//CSR49[6:6]
	DS_rxRegs& setmonslcibpwrdb(uint val);
	uint getmonslcibpwrdb();

	//CSR49[5:5]
	DS_rxRegs& setcendemuxpwrdb(uint val);
	uint getcendemuxpwrdb();

	//CSR49[4:4]
	DS_rxRegs& setedgdemuxpwrdb(uint val);
	uint getedgdemuxpwrdb();

	//CSR49[3:3]
	DS_rxRegs& setmondemuxpwrdb(uint val);
	uint getmondemuxpwrdb();

	//CSR49[2:2]
	DS_rxRegs& setrxcenpwrdb(uint val);
	uint getrxcenpwrdb();

	//CSR49[1:1]
	DS_rxRegs& setmonslcqpwrdb(uint val);
	uint getmonslcqpwrdb();

	//CSR49[0:0]
	DS_rxRegs& setmonslcqbpwrdb(uint val);
	uint getmonslcqbpwrdb();

	//CSR50[15:15]
	DS_rxRegs& setdfesumvrefsel(uint val);
	uint getdfesumvrefsel();

	//CSR50[14:14]
	DS_rxRegs& setdfesumrtrimen(uint val);
	uint getdfesumrtrimen();

	//CSR50[13:12]
	DS_rxRegs& setvregclkvrefrng(uint val);
	uint getvregclkvrefrng();

	//CSR50[11:10]
	DS_rxRegs& setvregclkpreampsel(uint val);
	uint getvregclkpreampsel();

	//CSR50[9:8]
	DS_rxRegs& setvregdatavrefrng(uint val);
	uint getvregdatavrefrng();

	//CSR50[7:4]
	DS_rxRegs& setdfesumrestrim(uint val);
	uint getdfesumrestrim();

	//CSR50[3:3]
	DS_rxRegs& setdfesumauxofsten(uint val);
	uint getdfesumauxofsten();

	//CSR50[2:2]
	DS_rxRegs& setdfesumauxofstpol(uint val);
	uint getdfesumauxofstpol();

	//CSR50[1:0]
	DS_rxRegs& setdfesumauxofstsel(uint val);
	uint getdfesumauxofstsel();

	//CSR51[15:8]
	DS_rxRegs& setdfefxtap1cen(uint val);
	uint getdfefxtap1cen();

	//CSR51[7:0]
	DS_rxRegs& setdfefxtap1edg(uint val);
	uint getdfefxtap1edg();

	//CSR52[15:15]
	DS_rxRegs& setdfespare(uint val);
	uint getdfespare();

	//CSR52[14:13]
	DS_rxRegs& setdfetapinjscale(uint val);
	uint getdfetapinjscale();

	//CSR52[12:11]
	DS_rxRegs& setdfeslicerbwsel(uint val);
	uint getdfeslicerbwsel();

	//CSR52[10:9]
	DS_rxRegs& setrxdfesumvreftrim(uint val);
	uint getrxdfesumvreftrim();

	//CSR52[8:6]
	DS_rxRegs& setdfealphagenrtrim(uint val);
	uint getdfealphagenrtrim();

	//CSR52[5:3]
	DS_rxRegs& setdfealphagenrefsel(uint val);
	uint getdfealphagenrefsel();

	//CSR52[2:0]
	DS_rxRegs& setdfealphagenloadsel(uint val);
	uint getdfealphagenloadsel();

	//CSR53[15:15]
	DS_rxRegs& setvregclkpwrdb(uint val);
	uint getvregclkpwrdb();

	//CSR53[14:14]
	DS_rxRegs& setvregclkdpmen(uint val);
	uint getvregclkdpmen();

	//CSR53[13:13]
	DS_rxRegs& setvregclkbleedb(uint val);
	uint getvregclkbleedb();

	//CSR53[12:8]
	DS_rxRegs& setvregclklvl(uint val);
	uint getvregclklvl();

	//CSR53[7:7]
	DS_rxRegs& setvregdatapwrdb(uint val);
	uint getvregdatapwrdb();

	//CSR53[6:6]
	DS_rxRegs& setvregdatadpmen(uint val);
	uint getvregdatadpmen();

	//CSR53[5:5]
	DS_rxRegs& setvregdatableedb(uint val);
	uint getvregdatableedb();

	//CSR53[4:0]
	DS_rxRegs& setvregdatalvl(uint val);
	uint getvregdatalvl();

	//CSR54[15:15]
	DS_rxRegs& setvregclkinrushpwrdb(uint val);
	uint getvregclkinrushpwrdb();

	//CSR54[14:14]
	DS_rxRegs& setvregdatainrushpwrdb(uint val);
	uint getvregdatainrushpwrdb();

	//CSR54[13:8]
	DS_rxRegs& setvregclkrefsel(uint val);
	uint getvregclkrefsel();

	//CSR54[5:0]
	DS_rxRegs& setvregdatarefsel(uint val);
	uint getvregdatarefsel();

	//CSR55[15:14]
	DS_rxRegs& setrxatbmuxsel(uint val);
	uint getrxatbmuxsel();

	//CSR55[13:11]
	DS_rxRegs& setdfealphagentopmatbctrl(uint val);
	uint getdfealphagentopmatbctrl();

	//CSR55[10:8]
	DS_rxRegs& setdfealphagentoppatbctrl(uint val);
	uint getdfealphagentoppatbctrl();

	//CSR55[7:7]
	DS_rxRegs& setdfealphagencenmute(uint val);
	uint getdfealphagencenmute();

	//CSR55[6:6]
	DS_rxRegs& setdfealphagenedgmute(uint val);
	uint getdfealphagenedgmute();

	//CSR55[5:5]
	DS_rxRegs& setdfealphagenmonmute(uint val);
	uint getdfealphagenmonmute();

	//CSR55[4:4]
	DS_rxRegs& setdfealphagenstepsize(uint val);
	uint getdfealphagenstepsize();

	//CSR55[2:1]
	DS_rxRegs& setdfesumbias(uint val);
	uint getdfesumbias();

	//CSR55[0:0]
	DS_rxRegs& setrxdfesumbiasptaten(uint val);
	uint getrxdfesumbiasptaten();

	//CSR56[15:13]
	DS_rxRegs& setvregclkatbctrl(uint val);
	uint getvregclkatbctrl();

	//CSR56[12:10]
	DS_rxRegs& setvregdataatbctrl(uint val);
	uint getvregdataatbctrl();

	//CSR56[5:0]
	DS_rxRegs& setsuptrimsummerrefsel(uint val);
	uint getsuptrimsummerrefsel();

	//CSR57[11:11]
	DS_rxRegs& setjtagsel(uint val);
	uint getjtagsel();

	//CSR57[10:10]
	uint getjtagoutp();

	//CSR57[9:9]
	uint getjtagoutm();

	//CSR57[8:8]
	DS_rxRegs& setjtagpwrdb(uint val);
	uint getjtagpwrdb();

	//CSR57[7:7]
	DS_rxRegs& setjtagacmodeen(uint val);
	uint getjtagacmodeen();

	//CSR57[6:6]
	DS_rxRegs& setjtaginitclk(uint val);
	uint getjtaginitclk();

	//CSR57[5:5]
	DS_rxRegs& setjtaginitp(uint val);
	uint getjtaginitp();

	//CSR57[4:4]
	DS_rxRegs& setjtaginitm(uint val);
	uint getjtaginitm();

	//CSR57[3:2]
	DS_rxRegs& setjtaghystadj(uint val);
	uint getjtaghystadj();

	//CSR57[1:0]
	DS_rxRegs& setjtagthadj(uint val);
	uint getjtagthadj();

	//CSR58[15:15]
	uint getceearly();

	//CSR58[14:14]
	uint getcelate();

	//CSR58[13:13]
	uint getcmearly();

	//CSR58[12:12]
	uint getcmlate();

	//CSR58[8:8]
	DS_rxRegs& setedgesleep(uint val);
	uint getedgesleep();

	//CSR58[7:7]
	DS_rxRegs& setecoarsealignen(uint val);
	uint getecoarsealignen();

	//CSR58[6:4]
	DS_rxRegs& setecoarsealignstep(uint val);
	uint getecoarsealignstep();

	//CSR58[3:3]
	DS_rxRegs& setmcoarsealignen(uint val);
	uint getmcoarsealignen();

	//CSR58[2:0]
	DS_rxRegs& setmcoarsealignstep(uint val);
	uint getmcoarsealignstep();

	//CSR59[15:15]
	uint getmisierrdone();

	//CSR59[14:8]
	uint getcphsval();

	//CSR59[6:0]
	uint getephsval();

	//CSR60[15:9]
	uint getmphsofstval();

	//CSR60[8:0]
	uint getmvolofstval();

	//CSR61[15:0]
	uint getmmcnt();

	//CSR62[15:11]
	uint gettimerexp();

	//CSR62[10:0]
	uint gettimer();

	//CSR63[14:5]
	DS_rxRegs& setrxcal_timer_value(uint val);
	uint getrxcal_timer_value();

	//CSR63[4:2]
	DS_rxRegs& setrxcal_timer_div_value(uint val);
	uint getrxcal_timer_div_value();

	//CSR63[1:1]
	DS_rxRegs& setrxcal_timer_div_en(uint val);
	uint getrxcal_timer_div_en();

	//CSR63[0:0]
	DS_rxRegs& setrxcal_timer_stop(uint val);
	uint getrxcal_timer_stop();

};

#endif // HILINKDSRXREGS_H_
