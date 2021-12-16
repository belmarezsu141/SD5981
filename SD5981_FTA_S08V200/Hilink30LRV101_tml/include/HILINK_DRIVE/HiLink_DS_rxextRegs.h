#ifndef HILINKDSRXEXTREGS_H_
#define HILINKDSRXEXTREGS_H_

#include <HILINK_DRIVE/HiLink_Regs_Base.h>
#define DS_RXEXT_CSR_NUM 51

class DS_rxextRegs:public HILINK_Regs_Base{
protected:
	DS_rxextRegs();
	virtual ~DS_rxextRegs();

	uint& get_csr(uint csrIndex);
	virtual void get_default_MacroLaneID(T_MacroLaneID& id);

public:
	bool get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos);
	static DS_rxextRegs& getInstance();
	string getName();
	uint getCSRCount();
	E_HILINK_REGISTER_TYPE getType();
	uint get_HILINK_MAX_LANE_NUM();
	uint getAddressMapToHiLink(int csrIndex);

///////////////////////////////////////////////////////////////////////////

private:
	class _REG_INFO{
		public:

	/// RX writable spare (digital)
			const T_REG_INFO_EX& dsspare1();	//CSR0[15:8]

	/// RX spare to analog
	/// V101:
	/// DSSPARE[7:0] = unassigned
	/// 
	/// V101 IpDrop3.3:
	/// Bit # [7:5] = unassigned
	/// Bit #[4] = repurposed for alphagen_stepsize function; refer to DFEALPHAGENSTEPSIZE for usage
	/// Bit # [3:0] = repurposed for alphagen monitor offset code correction. refer to RXSPARE[7:0] for usage
	/// 
	/// V101 IpDrop4.0:
	/// Bit # [7:6] = unassigned
	/// Bit #[5] = repurposed for div by5 clock aligned to rx_center_wordclk
	///       0 = use standard auxclk output programming
	///       1= select div by5 clock aligned to wordclk for auxclk output
	/// Bit #[4] = repurposed for alphagen_stepsize function; refer to DFEALPHAGENSTEPSIZE for usage
	/// Bit #[3:0] = repurposed for alphagen monitor offset code correction.  refer to RXSPARE[7:0] for usage
			const T_REG_INFO_EX& dsspare();	//CSR0[7:0]

	/// CDR 1st accumulator value.
			const T_REG_INFO_EX& rxcdraccmul1();	//CSR1[13:0]

	/// CDR 2nd accumulator value.
			const T_REG_INFO_EX& rxcdraccmul2();	//CSR2[9:0]

	/// CDR phase gain output value
			const T_REG_INFO_EX& rxcdrphsgnout();	//CSR3[9:0]

	/// Center channel t1_0 negative slicer offset
	/// 
	/// bit[6] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] - magnitude of offset (binary),
	/// 000000 = Minimum offset
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum offset
			const T_REG_INFO_EX& cen0neglatofst();	//CSR4[14:8]

	/// Center channel t1_0 positive slicer offset
	/// 
	/// bit[6] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] - magnitude of offset,
	/// 000000 = Minimum offset
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum offset
			const T_REG_INFO_EX& cen0poslatofst();	//CSR4[6:0]

	/// center channel t1_90 negative slicer offset
	/// 
	/// bit[6] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] - magnitude of offset,
	/// 000000 = Minimum offset
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum offset
			const T_REG_INFO_EX& cen90neglatofst();	//CSR5[14:8]

	/// center channel t1_90 positive slicer offset
	/// 
	/// bit[5] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[4:0] - magnitude of offset
	/// 00000 = Minimum offset
	/// 00001 =
	/// 00010 =
	/// ..
	/// 11111 = Maximum offset
			const T_REG_INFO_EX& cen90poslatofst();	//CSR5[6:0]

	/// center channel t1_180 negative slicer offset
	/// 
	/// bit[6] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] - magnitude of offset ,
	/// 000000 = Minimum offset
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum offset
			const T_REG_INFO_EX& cen180neglatofst();	//CSR6[14:8]

	/// center channel t1_180 positive slicer offset
	/// 
	/// bit[6] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] - magnitude of offset (binary),
	/// 000000 = Minimum offset
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum offset
			const T_REG_INFO_EX& cen180poslatofst();	//CSR6[6:0]

	/// center channel t1_270 negative slicer offset
	/// 
	/// bit[6] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] - magnitude of offset ,
	/// 000000 = Minimum offset
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum offset
			const T_REG_INFO_EX& cen270neglatofst();	//CSR7[14:8]

	/// center channel t1_270 positive slicer offset
	/// 
	/// bit[6] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] - magnitude of offset (binary),
	/// 000000 = Minimum offset
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum offset
			const T_REG_INFO_EX& cen270poslatofst();	//CSR7[6:0]

	/// edge channel t1_0 negative slicer offset
	/// 
	/// bit[6] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] - magnitude of offset,
	/// 000000 = Minimum offset
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum offset
			const T_REG_INFO_EX& edg0neglatofst();	//CSR8[14:8]

	/// edge channel t1_0 positive slicer offset
	/// 
	/// bit[6] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] - magnitude of offset,
	/// 000000 = Minimum offset
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum offset
			const T_REG_INFO_EX& edg0poslatofst();	//CSR8[6:0]

	/// edge channel t1_90 negative slicer offset
	/// 
	/// bit[6] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] - magnitude of offset (binary),
	/// 000000 = Minimum offset
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum offset
			const T_REG_INFO_EX& edg90neglatofst();	//CSR9[14:8]

	/// edge channel t1_90 positive slicer offset
	/// 
	/// bit[6] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] - magnitude of offset (binary),
	/// 000000 = Minimum offset
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum offset
			const T_REG_INFO_EX& edg90poslatofst();	//CSR9[6:0]

	/// edge channel t1_180 negative slicer offset
	/// 
	/// bit[6] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] - magnitude of offset,
	/// 000000 = Minimum offset
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum offset
			const T_REG_INFO_EX& edg180neglatofst();	//CSR10[14:8]

	/// edge channel t1_180 positive slicer offset
	/// 
	/// bit[6] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] - magnitude of offset ,
	/// 000000 = Minimum offset
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum offset
			const T_REG_INFO_EX& edg180poslatofst();	//CSR10[6:0]

	/// edge channel t1_270 negative slicer offset
	/// 
	/// bit[6] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] - magnitude of offset ,
	/// 000000 = Minimum offset
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum offset
			const T_REG_INFO_EX& edg270neglatofst();	//CSR11[14:8]

	/// edge channel t1_270 positive slicer offset
	/// 
	/// bit[6] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] - magnitude of offset,
	/// 000000 = Minimum offset
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum offset
			const T_REG_INFO_EX& edg270poslatofst();	//CSR11[6:0]

	/// monitor channel t1_0 slicer offset
	/// 
	/// bit[6] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] - magnitude of offset,
	/// 000000 = Minimum offset
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum offset
			const T_REG_INFO_EX& mon0latofst();	//CSR12[14:8]

	/// monitor channel t1_90 slicer offset
	/// 
	/// bit[6] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] - magnitude of offset (binary),
	/// 000000 = Minimum offset
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum offset
			const T_REG_INFO_EX& mon90latofst();	//CSR12[6:0]

	/// monitor channel t1_180 slicer offset
	/// 
	/// bit[6] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] - magnitude of offset,
	/// 000000 = Minimum offset
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum offset
			const T_REG_INFO_EX& mon180latofst();	//CSR13[14:8]

	/// monitor channel t1_270 slicer offset
	/// 
	/// bit[6] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] - magnitude of offset,
	/// 000000 = Minimum offset
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum offset
			const T_REG_INFO_EX& mon270latofst();	//CSR13[6:0]

	/// New in V101: Used to simulate DS power sequence in rx_quiet mode for testing. Should be 1'b0 during mission mode
			const T_REG_INFO_EX& pwrsqrxquiet();	//CSR14[12:12]

	/// Status of rx_quiet Pin
			const T_REG_INFO_EX& rxquietstatus();	//CSR14[11:11]

	/// ALOS Configuration
	/// 000 = both ALOS and ENERGY_DETECT pins and LOSANA register bit (RX CSR15[0]) will be set to high when the signal squelch loss detection is detected
	/// 001 = both ALOS and ENERGY_DETECT pins and LOSANA register bit (RX CSR15[0]) will be set to high when there are not enough transitions
	/// 010 = both ALOS and ENERGY_DETECT pins and LOSANA register bit (RX CSR15[0]) will be set to high when inner eye is not open enough vertically 
	/// 011 = both ALOS and ENERGY_DETECT pins and LOSANA register bit (RX CSR15[0]) will be set to high when inner eye is not open enough horizontally 
	/// 100= both ALOS and ENERGY_DETECT pins and LOSANA register bit (RX CSR15[0]) will be set to high when there are not enough transitions or inner eye is not open enough either vertically or horizontally
	/// 101= both ALOS and ENERGY_DETECT pins and LOSANA register bit (RX CSR15[0]) will be set to high when the signal squelch loss detection is detected or there are not enough transitions
	/// 110 = both ALOS and ENERGY_DETECT pins and LOSANA register bit (RX CSR15[0]) will be set to high when the signal squelch loss detection is detected or inner eye is not open enough vertically or horizontally
	/// 111= both ALOS and ENERGY_DETECT pins and LOSANA register bit (RX CSR15[0]) will be set to high when the signal squelch loss detection is detected or there are not enough transitions or inner eye is not open enough vertically or horizontally
			const T_REG_INFO_EX& aloscfg();	//CSR14[10:8]

	/// Not used
			const T_REG_INFO_EX& rxtxeeequieten();	//CSR14[7:7]

	/// Not used
			const T_REG_INFO_EX& rxtxeeealerten();	//CSR14[6:6]

	/// Training enable bit; Applicable to both TX (control eye monitor) and RX (for tap mapping).
			const T_REG_INFO_EX& rxtxlttrainen();	//CSR14[5:5]

	/// energy efficient ethernet enable bit. Applicable to both TX and RX.
			const T_REG_INFO_EX& rxtxeeeen();	//CSR14[4:4]

	/// defines the powerdown granularity of the RX circuitry when EEE tx quiet is asserted
	/// 1000: most power savings
	/// 1100: moderate power savings
	/// 1110: least power savings
	/// others: no power savings
			const T_REG_INFO_EX& rxeeepwrdbsel();	//CSR14[3:0]

	/// Rx latch offset detector enable signal
	/// 0 = disabled
	/// 1 = enabled
			const T_REG_INFO_EX& rxlatofstdeten();	//CSR15[15:15]

	/// Rx latch offset detector mode
	/// 0 = latch offset detector status in 2-bit mode
	/// 1 = latch offset detector status in 15-bit mode
			const T_REG_INFO_EX& rxlatofstmode();	//CSR15[14:14]

	/// Choose  one of the channel for latch offset detection
	/// 0000 =  center Q channel
	/// ;0001 =  center I channel
	/// ;0010 =  center Qb channel
	/// ;0011 =  center Ib channel
	/// ;0100 =  edge Q channel
	/// ;0101 =  edge I channel
	/// ;0110 =  edge Qb channel
	/// ;0111 =  edge Ib channel
	/// ;1000 =  monitor Q channel
	/// ;1001 =  monintor I channel
	/// ;1010 =  monitor Qb channel
	/// ;1011 =  monintor Ib channel;
			const T_REG_INFO_EX& rxlatdatasel();	//CSR15[3:0]

	/// ISI accumulator 0 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr0();	//CSR16[15:0]

	/// ISI accumulator 1 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr1();	//CSR17[15:0]

	/// ISI accumulator 2 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr2();	//CSR18[15:0]

	/// ISI accumulator 3 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr3();	//CSR19[15:0]

	/// ISI accumulator 4 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr4();	//CSR20[15:0]

	/// ISI accumulator 5 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr5();	//CSR21[15:0]

	/// ISI accumulator 6 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr6();	//CSR22[15:0]

	/// ISI accumulator 7 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr7();	//CSR23[15:0]

	/// ISI accumulator 8 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr8();	//CSR24[15:0]

	/// ISI accumulator 9 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr9();	//CSR25[15:0]

	/// ISI accumulator 10 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr10();	//CSR26[15:0]

	/// ISI accumulator 11 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr11();	//CSR27[15:0]

	/// ISI accumulator 12 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr12();	//CSR28[15:0]

	/// ISI accumulator 13 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr13();	//CSR29[15:0]

	/// ISI accumulator 14 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr14();	//CSR30[15:0]

	/// ISI accumulator 15 count, used for equalization adaptation
			const T_REG_INFO_EX& isierr15();	//CSR31[15:0]

	/// [bad key===> "v101:
	/// bits #[7:4] = repurposed for alphagen center postive offset correction.
	/// bits #[3:0] = repurposed for alphagen center negative offset correction.
	/// Coding-A exhibits common-mode current changes as offset swept
	/// Coding-B maintains constant common-mode current as offset swept
	/// at expense of reducing differential tuning range
	/// {RXSPARE[7,4], RXSPARE[3:0] }
	/// Coding-A               Coding-B
	/// 1111,0000:             1111,0001:   max positive offset
	/// 1000,0000:             1100,0100:   mid positive offset
	/// 0000,0000:             1000,1000:   zero offset.
	/// 0000,1000:             0100,1100:   mid negative offset
	/// 0000,1111:             0001,1111:   max negative offset
	/// 
	/// V101 IpDrop3.3 and  IpDrop3.4
	/// differential offset correction present on all alphagen channels. circuit change maintains constant common-mode current as offset swept
	/// bits #[7:4] = repurposed for alphagen center offset correction. 
	/// bits #[3:0] = repurposed for alphagen edge offset correction. 
	/// bits #[3:0] = repurposed for alphagen monitor offset correction. 
	/// The following modified gray coding scheme is used:
	///  7: 0100; 6: 0101; 5: 0111; 4: 0110; 3: 0010; 2: 0011; 1: 0001;   0: 0000/1100 ;  -1: 1101; -2: 1111; -3: 1110; -4: 1010; -5: 1011;  -6: 1001;  -7: 1000" <====key bad]
			const T_REG_INFO_EX& rxspare();	//CSR32[7:0]

	/// CTLE regulator power down control. 
	/// 0: Power down
	/// 1: Power up
			const T_REG_INFO_EX& ctlevregpwrdb();	//CSR33[15:15]

	/// Not Implemented in analog.
			const T_REG_INFO_EX& ctlevreginrushpwrdb();	//CSR33[14:14]

	/// CTLE regulator reference range select
	/// x0 =  select low range  (850mV to 950mV)
	/// x1 =  select high range (950mV to 1050mV)
	/// bit [1] not connected in analog
			const T_REG_INFO_EX& ctlevregvrefrng();	//CSR33[13:12]

	/// Enable CTLE regulator bypass mode
	/// 0 =  mission mode
	/// 1 =  bypass mode - enable CTLEVREGBYPASSSEL[2:0] to be used to manually increase sourcing capability of CTLE regulator
			const T_REG_INFO_EX& ctlevregbypasstohv();	//CSR33[11:11]

	/// Voltage level control of CTLE regulator.
	/// 000 =  Minimum voltage
	/// ?.
	/// 111 =  Maximum voltage
			const T_REG_INFO_EX& ctlevregvrefsel();	//CSR33[10:8]

	/// Manual CTLE supply trim when in bypass mode
	/// 000 =  min supply voltage
	/// ��..
	/// 111 = max supply voltage
			const T_REG_INFO_EX& ctlevregbypasssel();	//CSR33[7:5]

	/// Configure CTLE regulator current sourcing capability
	/// 0 = CTLE regulator configured to only drive CTLE current load
	/// 1 =  mission mode -- CTLE regulator configured to drive CTLE + summer current load
			const T_REG_INFO_EX& ctlevregsummerloaden();	//CSR33[4:4]

	/// CTLE regulator DPM trim.
	/// All bits equally weighted.
	/// 000 =  SS/TT/FF
			const T_REG_INFO_EX& ctlevregdpmpvt();	//CSR33[3:1]

	/// iptat temperature compensation coefficient for Replica
			const T_REG_INFO_EX& ctleiptatctrltc1();	//CSR34[15:12]

	/// iptat temperature compensation coefficient for CTLE stages
			const T_REG_INFO_EX& ctleiptatctrltc2();	//CSR34[11:8]

	/// rxctle current scaling control for Replica
			const T_REG_INFO_EX& ctleibiastunerep();	//CSR34[5:3]

	/// rxctle current scaling control for VSR CTLE Stage1
			const T_REG_INFO_EX& ctleibiastunestg1();	//CSR34[2:0]

	/// rxctle current scaling control for VSR CTLE Stage2
			const T_REG_INFO_EX& ctleibiastunestg2();	//CSR35[15:13]

	/// rxctle current scaling control for VSR CTLE Stage3
			const T_REG_INFO_EX& ctleibiastunestg3();	//CSR35[12:10]

	/// Rx CTLE Replica Current source calibration enable control.  
	/// 0 =  Disable
	/// 1 =  Enable
			const T_REG_INFO_EX& ctleicalrepen();	//CSR35[5:5]

	/// Calibration bits for CTLE Replica Current Source.
			const T_REG_INFO_EX& ctlerepical();	//CSR35[4:0]

	/// Rx CTLE Stages Current source calibration enable control. 
	/// 0 =  Disable
	/// 1 =  Enable
			const T_REG_INFO_EX& ctleicalctleen();	//CSR36[15:15]

	/// Calibration bits for CTLE Stage 1 Current Source
			const T_REG_INFO_EX& ctleicalst1();	//CSR36[14:10]

	/// Calibration bits for CTLE Stage 2 Current Source
			const T_REG_INFO_EX& ctleicalst2();	//CSR36[9:5]

	/// Calibration bits for CTLE Stage 3 Current Source
			const T_REG_INFO_EX& ctleicalst3();	//CSR36[4:0]

	/// Rx Summer current source calibration enable control.
	/// 0: Disable
	/// 1: Enable
			const T_REG_INFO_EX& dfesumicalen();	//CSR37[14:14]

	/// Calibration bits for summer current source.
			const T_REG_INFO_EX& dfesumiical();	//CSR37[13:9]

	/// Calibration bits for summer current source.
			const T_REG_INFO_EX& dfesumqical();	//CSR37[8:4]

	/// iptat temperature compensation coefficient for summer
			const T_REG_INFO_EX& dfesumiptattcctrl();	//CSR37[3:0]

	/// resets edge cycling digital block. Active low
			const T_REG_INFO_EX& edgecycsoftrstb();	//CSR38[15:15]

	/// Edge channel cycling enable
	/// 0 =  Normal Mode; 
	/// 1 =  Edge Channel Cycling enable
			const T_REG_INFO_EX& edgecycen();	//CSR38[14:14]

	/// Edge channel cycling mode
	/// 0 =  partial cycling; 1 =  full cycling
			const T_REG_INFO_EX& edgecymode();	//CSR38[13:13]

	/// Power sequence enable for edge channel cycling
	/// 0 =  disable power sequencing for edge channel cycling
	/// ;1 =  enable power sequencing for edge channel cycling;
			const T_REG_INFO_EX& edgecycpsen();	//CSR38[12:12]

	/// edge cycling analog settling time control.
	/// 00 = 0 word cycle
	/// 01 = 2 word cycles
	/// 10 = 4 word cycles 
	/// 11 = 8 word cycles
			const T_REG_INFO_EX& edgcycanastl();	//CSR38[11:10]

	/// Edge channel transition step during edge cycling
	/// 00 = 1 cycle 
	/// 01 = 2 cycles
	/// 10 = 4 cycles 
	/// 11 = 8 cycles
			const T_REG_INFO_EX& edgcyctranstep();	//CSR38[9:8]

	/// Edge channel off time during edge cycling
	/// 0000 = 10 cycles;    0001 = 20 cycles;     0010 = 30 cycles; 
	/// 0011 = 40 cycles;    0100 = 50 cycles;     0101 = 75 cycles; 
	/// 0110 = 100 cycles;  0111 = 150 cycles;   1000 = 200 cycles; 
	/// 1001 = 300 cycles;  1010 = 400 cycles;   1011 = 600 cycles; 
	/// 1100 = 800 cycles;  1101 = 1200 cycles; 1110 = 1600 cycles
	/// ;1111 = 2400 cycles
			const T_REG_INFO_EX& edgcycofftime();	//CSR38[7:4]

	/// Edge channel on time during edge cycling (number of word clock cycles)
	/// 0000 = 10 cycles;    0001 = 20 cycles;     0010 = 30 cycles; 
	/// 0011 = 40 cycles;    0100 = 50 cycles;     0101 = 60 cycles; 
	/// 0110 = 70 cycles;    0111 =  80 cycles;    1000 = 90 cycles; 
	/// 1001 = 100 cycles;  1010 = 110 cycles;  1011 = 120 cycles; 
	/// 1100 = 130 cycles;  1101 = 140 cycles;  1110 = 150 cycles
	/// ;1111 = 160 cycles
			const T_REG_INFO_EX& edgcycontime();	//CSR38[3:0]

	/// 10-bit repeating pattern (TRP) detection enable.
	/// 0 = disable; 1 = Enable
			const T_REG_INFO_EX& trpdeten();	//CSR39[15:15]

	/// Decision threshold.  
	/// 000 = 4;    001 = 8;     010 = 16;    011 = 32; 
	/// 100 = 64; 101= 128;  110 = 256;  111 = 512;
			const T_REG_INFO_EX& trpdetthr();	//CSR39[14:12]

	/// Total number of bits considered. 
	/// 00 = 160 bits;   01 = 320 bits  
	/// 10 = 640 bits;   11 = 1280 bits
			const T_REG_INFO_EX& trpdetwin();	//CSR39[9:8]

	/// 10-bit repeating pattern (TRP) detection status.
	/// 0 = 10-bit repeating pattern not detected.
	/// 1 = 10-bit repeating pattern detected. Remains at 1 until read.
			const T_REG_INFO_EX& trpdetstatus();	//CSR39[0:0]

	/// Rx Calibration Task selection list1 .  Here 1= bypass and 0=perform calibration
	/// bit[15] =   CTLE regulator calibration
	/// bit[14] =   CTLE replica block opamp input offset calibration
	/// bit[13] =   clock regulator calibration
	/// bit[12] =   data regulator calibration
	/// bit[11] =   signal detection offset calibration
	/// bit[10] =   CTLE 1st equalizer stage offset calibration
	/// bit[9] =   CTLE 1st gain stage offset calibration
	/// bit[8] =   CTLE 2nd equalizer stage offset calibration
	/// bit[7] =   CTLE 2nd gain stage offset calibration
	/// bit[6] =   CTLE 3rd equalizer stage offset calibration
	/// bit[5] =   CTLE 3rd gain stage offset calibration
	/// bit[4] =   I path of even summer offset calibration
	/// bit[3] =   Q path of even summer offset calibration
	/// bit[2] =   I path of odd summer offset calibration
	/// bit[1] =   Q path of odd summer offset calibration
	/// bit[0] =   summer load resistance calibration
			const T_REG_INFO_EX& rxcalibtasksel1();	//CSR40[15:0]

	/// Rx Calibration Task selection list2.  Here 1=bypass and 0= perform calibration
	/// bit[15] =   center channel latch calibration
	/// bit[14] =   edge channel latch calibration
	/// bit[13] =   monitor channel latch calibration
	/// bits[12] =  bypass ctle stage5,6 and summer stages offset re-calibration  which is run before any center/edge/monitor latch calibration
	/// bit[11] =  bypass 1st load summer resistance calibration which is run before the Ipath of Even offset calibration
	/// bits[10:9] =  bypasses the center and edge negative latch offset calibration respectively required for VSR
	/// bits[8:0] =  not used
			const T_REG_INFO_EX& rxcalibtasksel2();	//CSR41[15:0]

	/// User defined WL or HL value to be used in the peak detector algorithm when EMTASKCTRL[4:3] = 2�b11 or provided as the WL value for area calculation purposes
			const T_REG_INFO_EX& emswcorner0();	//CSR42[8:0]

	/// User defined WR or HU value to be used in the peak detector algorithm when EMTASKCTRL[4:3] = 2�b11 or provided as the WR value for area calculation purposes
			const T_REG_INFO_EX& emswcorner1();	//CSR43[8:0]

	/// Rx calibration comparator direction
	/// [15:7] Reserved
	/// [6] RX LATCH
	/// [5] CTLE regulator
	/// [4] Opamp
	/// [3] Summer Load Resistance
	/// [2] Clock and Data Regulator
	/// [1] Signal Detection
	/// [0] CML stage
			const T_REG_INFO_EX& rxcaldir();	//CSR44[15:0]

	/// RX writable spare2 (digital)
			const T_REG_INFO_EX& dsspare2();	//CSR45[15:0]

	/// RX writable spare2 (digital)
			const T_REG_INFO_EX& dsspare3();	//CSR46[15:0]

	/// RX writable spare2 (digital)
			const T_REG_INFO_EX& dsspare4();	//CSR47[15:0]

	/// Configures the number of 10-bit words to accumulate for reporting the status
			const T_REG_INFO_EX& rxlatofstnumword();	//CSR48[10:0]

	/// Configures the offset detection threshold by programming the number of expected 'logic 1' bits in the accumulation window (defined by RXLATOFSTNUMWORD)
			const T_REG_INFO_EX& rxlatofstthresh();	//CSR49[14:0]

	/// Status of rx latch offset detector.
	/// 
	/// When RXLATOFSTMODE = 0, 
	/// RXLATOFSTDETSTATUS[1:0] indicates
	/// 00 = 0s and 1s are equal 
	/// 01 = more 1s detected
	/// 10 = reserved  
	/// 11 = more 0s detected
	/// 
	/// when RXLATOFSTMODE =1 , 
	/// RXLATOFSTDETSTATUS[14:0] indicates total number of Ones in the accumulation window
			const T_REG_INFO_EX& rxlatofstdetstatus();	//CSR50[14:0]
			bool get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos);
	};
public:
	_REG_INFO REG_INFO;

	uint csr[DS_RXEXT_CSR_NUM];


	//CSR0[15:8]
	DS_rxextRegs& setdsspare1(uint val);
	uint getdsspare1();

	//CSR0[7:0]
	DS_rxextRegs& setdsspare(uint val);
	uint getdsspare();

	//CSR1[13:0]
	uint getrxcdraccmul1();

	//CSR2[9:0]
	uint getrxcdraccmul2();

	//CSR3[9:0]
	uint getrxcdrphsgnout();

	//CSR4[14:8]
	DS_rxextRegs& setcen0neglatofst(uint val);
	uint getcen0neglatofst();

	//CSR4[6:0]
	DS_rxextRegs& setcen0poslatofst(uint val);
	uint getcen0poslatofst();

	//CSR5[14:8]
	DS_rxextRegs& setcen90neglatofst(uint val);
	uint getcen90neglatofst();

	//CSR5[6:0]
	DS_rxextRegs& setcen90poslatofst(uint val);
	uint getcen90poslatofst();

	//CSR6[14:8]
	DS_rxextRegs& setcen180neglatofst(uint val);
	uint getcen180neglatofst();

	//CSR6[6:0]
	DS_rxextRegs& setcen180poslatofst(uint val);
	uint getcen180poslatofst();

	//CSR7[14:8]
	DS_rxextRegs& setcen270neglatofst(uint val);
	uint getcen270neglatofst();

	//CSR7[6:0]
	DS_rxextRegs& setcen270poslatofst(uint val);
	uint getcen270poslatofst();

	//CSR8[14:8]
	DS_rxextRegs& setedg0neglatofst(uint val);
	uint getedg0neglatofst();

	//CSR8[6:0]
	DS_rxextRegs& setedg0poslatofst(uint val);
	uint getedg0poslatofst();

	//CSR9[14:8]
	DS_rxextRegs& setedg90neglatofst(uint val);
	uint getedg90neglatofst();

	//CSR9[6:0]
	DS_rxextRegs& setedg90poslatofst(uint val);
	uint getedg90poslatofst();

	//CSR10[14:8]
	DS_rxextRegs& setedg180neglatofst(uint val);
	uint getedg180neglatofst();

	//CSR10[6:0]
	DS_rxextRegs& setedg180poslatofst(uint val);
	uint getedg180poslatofst();

	//CSR11[14:8]
	DS_rxextRegs& setedg270neglatofst(uint val);
	uint getedg270neglatofst();

	//CSR11[6:0]
	DS_rxextRegs& setedg270poslatofst(uint val);
	uint getedg270poslatofst();

	//CSR12[14:8]
	DS_rxextRegs& setmon0latofst(uint val);
	uint getmon0latofst();

	//CSR12[6:0]
	DS_rxextRegs& setmon90latofst(uint val);
	uint getmon90latofst();

	//CSR13[14:8]
	DS_rxextRegs& setmon180latofst(uint val);
	uint getmon180latofst();

	//CSR13[6:0]
	DS_rxextRegs& setmon270latofst(uint val);
	uint getmon270latofst();

	//CSR14[12:12]
	DS_rxextRegs& setpwrsqrxquiet(uint val);
	uint getpwrsqrxquiet();

	//CSR14[11:11]
	uint getrxquietstatus();

	//CSR14[10:8]
	DS_rxextRegs& setaloscfg(uint val);
	uint getaloscfg();

	//CSR14[7:7]
	DS_rxextRegs& setrxtxeeequieten(uint val);
	uint getrxtxeeequieten();

	//CSR14[6:6]
	DS_rxextRegs& setrxtxeeealerten(uint val);
	uint getrxtxeeealerten();

	//CSR14[5:5]
	DS_rxextRegs& setrxtxlttrainen(uint val);
	uint getrxtxlttrainen();

	//CSR14[4:4]
	DS_rxextRegs& setrxtxeeeen(uint val);
	uint getrxtxeeeen();

	//CSR14[3:0]
	DS_rxextRegs& setrxeeepwrdbsel(uint val);
	uint getrxeeepwrdbsel();

	//CSR15[15:15]
	DS_rxextRegs& setrxlatofstdeten(uint val);
	uint getrxlatofstdeten();

	//CSR15[14:14]
	DS_rxextRegs& setrxlatofstmode(uint val);
	uint getrxlatofstmode();

	//CSR15[3:0]
	DS_rxextRegs& setrxlatdatasel(uint val);
	uint getrxlatdatasel();

	//CSR16[15:0]
	uint getisierr0();

	//CSR17[15:0]
	uint getisierr1();

	//CSR18[15:0]
	uint getisierr2();

	//CSR19[15:0]
	uint getisierr3();

	//CSR20[15:0]
	uint getisierr4();

	//CSR21[15:0]
	uint getisierr5();

	//CSR22[15:0]
	uint getisierr6();

	//CSR23[15:0]
	uint getisierr7();

	//CSR24[15:0]
	uint getisierr8();

	//CSR25[15:0]
	uint getisierr9();

	//CSR26[15:0]
	uint getisierr10();

	//CSR27[15:0]
	uint getisierr11();

	//CSR28[15:0]
	uint getisierr12();

	//CSR29[15:0]
	uint getisierr13();

	//CSR30[15:0]
	uint getisierr14();

	//CSR31[15:0]
	uint getisierr15();

	//CSR32[7:0]
	DS_rxextRegs& setrxspare(uint val);
	uint getrxspare();

	//CSR33[15:15]
	DS_rxextRegs& setctlevregpwrdb(uint val);
	uint getctlevregpwrdb();

	//CSR33[14:14]
	DS_rxextRegs& setctlevreginrushpwrdb(uint val);
	uint getctlevreginrushpwrdb();

	//CSR33[13:12]
	DS_rxextRegs& setctlevregvrefrng(uint val);
	uint getctlevregvrefrng();

	//CSR33[11:11]
	DS_rxextRegs& setctlevregbypasstohv(uint val);
	uint getctlevregbypasstohv();

	//CSR33[10:8]
	DS_rxextRegs& setctlevregvrefsel(uint val);
	uint getctlevregvrefsel();

	//CSR33[7:5]
	DS_rxextRegs& setctlevregbypasssel(uint val);
	uint getctlevregbypasssel();

	//CSR33[4:4]
	DS_rxextRegs& setctlevregsummerloaden(uint val);
	uint getctlevregsummerloaden();

	//CSR33[3:1]
	DS_rxextRegs& setctlevregdpmpvt(uint val);
	uint getctlevregdpmpvt();

	//CSR34[15:12]
	DS_rxextRegs& setctleiptatctrltc1(uint val);
	uint getctleiptatctrltc1();

	//CSR34[11:8]
	DS_rxextRegs& setctleiptatctrltc2(uint val);
	uint getctleiptatctrltc2();

	//CSR34[5:3]
	DS_rxextRegs& setctleibiastunerep(uint val);
	uint getctleibiastunerep();

	//CSR34[2:0]
	DS_rxextRegs& setctleibiastunestg1(uint val);
	uint getctleibiastunestg1();

	//CSR35[15:13]
	DS_rxextRegs& setctleibiastunestg2(uint val);
	uint getctleibiastunestg2();

	//CSR35[12:10]
	DS_rxextRegs& setctleibiastunestg3(uint val);
	uint getctleibiastunestg3();

	//CSR35[5:5]
	DS_rxextRegs& setctleicalrepen(uint val);
	uint getctleicalrepen();

	//CSR35[4:0]
	DS_rxextRegs& setctlerepical(uint val);
	uint getctlerepical();

	//CSR36[15:15]
	DS_rxextRegs& setctleicalctleen(uint val);
	uint getctleicalctleen();

	//CSR36[14:10]
	DS_rxextRegs& setctleicalst1(uint val);
	uint getctleicalst1();

	//CSR36[9:5]
	DS_rxextRegs& setctleicalst2(uint val);
	uint getctleicalst2();

	//CSR36[4:0]
	DS_rxextRegs& setctleicalst3(uint val);
	uint getctleicalst3();

	//CSR37[14:14]
	DS_rxextRegs& setdfesumicalen(uint val);
	uint getdfesumicalen();

	//CSR37[13:9]
	DS_rxextRegs& setdfesumiical(uint val);
	uint getdfesumiical();

	//CSR37[8:4]
	DS_rxextRegs& setdfesumqical(uint val);
	uint getdfesumqical();

	//CSR37[3:0]
	DS_rxextRegs& setdfesumiptattcctrl(uint val);
	uint getdfesumiptattcctrl();

	//CSR38[15:15]
	DS_rxextRegs& setedgecycsoftrstb(uint val);
	uint getedgecycsoftrstb();

	//CSR38[14:14]
	DS_rxextRegs& setedgecycen(uint val);
	uint getedgecycen();

	//CSR38[13:13]
	DS_rxextRegs& setedgecymode(uint val);
	uint getedgecymode();

	//CSR38[12:12]
	DS_rxextRegs& setedgecycpsen(uint val);
	uint getedgecycpsen();

	//CSR38[11:10]
	DS_rxextRegs& setedgcycanastl(uint val);
	uint getedgcycanastl();

	//CSR38[9:8]
	DS_rxextRegs& setedgcyctranstep(uint val);
	uint getedgcyctranstep();

	//CSR38[7:4]
	DS_rxextRegs& setedgcycofftime(uint val);
	uint getedgcycofftime();

	//CSR38[3:0]
	DS_rxextRegs& setedgcycontime(uint val);
	uint getedgcycontime();

	//CSR39[15:15]
	DS_rxextRegs& settrpdeten(uint val);
	uint gettrpdeten();

	//CSR39[14:12]
	DS_rxextRegs& settrpdetthr(uint val);
	uint gettrpdetthr();

	//CSR39[9:8]
	DS_rxextRegs& settrpdetwin(uint val);
	uint gettrpdetwin();

	//CSR39[0:0]
	uint gettrpdetstatus();

	//CSR40[15:0]
	DS_rxextRegs& setrxcalibtasksel1(uint val);
	uint getrxcalibtasksel1();

	//CSR41[15:0]
	DS_rxextRegs& setrxcalibtasksel2(uint val);
	uint getrxcalibtasksel2();

	//CSR42[8:0]
	DS_rxextRegs& setemswcorner0(uint val);
	uint getemswcorner0();

	//CSR43[8:0]
	DS_rxextRegs& setemswcorner1(uint val);
	uint getemswcorner1();

	//CSR44[15:0]
	DS_rxextRegs& setrxcaldir(uint val);
	uint getrxcaldir();

	//CSR45[15:0]
	DS_rxextRegs& setdsspare2(uint val);
	uint getdsspare2();

	//CSR46[15:0]
	DS_rxextRegs& setdsspare3(uint val);
	uint getdsspare3();

	//CSR47[15:0]
	DS_rxextRegs& setdsspare4(uint val);
	uint getdsspare4();

	//CSR48[10:0]
	DS_rxextRegs& setrxlatofstnumword(uint val);
	uint getrxlatofstnumword();

	//CSR49[14:0]
	DS_rxextRegs& setrxlatofstthresh(uint val);
	uint getrxlatofstthresh();

	//CSR50[14:0]
	uint getrxlatofstdetstatus();

};

#endif // HILINKDSRXEXTREGS_H_
