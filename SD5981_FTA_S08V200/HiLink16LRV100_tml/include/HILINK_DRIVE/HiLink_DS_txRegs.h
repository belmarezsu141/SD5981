#ifndef HILINKDSTXREGS_H_
#define HILINKDSTXREGS_H_

#include "HiLink_Regs_Base.h"
#define DS_TX_CSR_NUM 62

class DS_txRegs:public HILINK_Regs_Base{
protected:
	DS_txRegs();
	virtual ~DS_txRegs();

	uint& get_csr(uint csrIndex);
	virtual void get_default_MacroLaneID(T_MacroLaneID& id);

public:
	bool get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos);
	static DS_txRegs& getInstance();
	string getName();
	uint getCSRCount();
	E_HILINK_REGISTER_TYPE getType();
	uint get_HILINK_MAX_LANE_NUM();
	uint getAddressMapToHiLink(int csrIndex);

///////////////////////////////////////////////////////////////////////////

private:
	class _REG_INFO{
		public:

	/// Transmit path power down control. Active low. This pin will gate other analog power down pins. Defaults have been chosen to ensure TX default state is ON.
	/// 0 = Powers down all related TX circuitry and forces a power down values on TXDRVREGPWRDB,TXCPPWRDB,TXDRVDATDEPCOMPPWRDB,TXDRVCALPWRDB,TXTAPPWRDB[7:0],TXDRVSLEWPWRDB. Does not power down the Clock regulator which is used in the Receiver block.
	/// 1 = Powers up all transmit circuitry. Releases force on  TXDRVREGPWRDB,TXCPPWRDB, TXDRVDATDEPCOMPPWRDB,TXDRVCALPWRDB,TXTAPPWRDB[7:0],TXDRVSLEWPWRDB.
			const T_REG_INFO_EX& txpwrdb();	//CSR0[15:15]

	/// txcp_wordclk16b32b divider selection
	/// 0 = divider 8 for 16b
	/// 1 = divider 16 for 32b
			const T_REG_INFO_EX& txclk_16b32b_sel();	//CSR0[14:14]

	/// txcp_wordclk16b32b power down signal
	/// 0 = power down
	/// 1 = enable
			const T_REG_INFO_EX& txclk_16b32b_pwrdb();	//CSR0[13:13]

	/// Regulator (txclk_vreg and txdrv_vreg) output voltage level
	/// 000 = 0.83V
	/// 001 = 0.86V
	/// 010 = 0.90V(default)
	/// 011 = 0.95V
	/// 100 = 1.01V
	/// 101 = 1.03V
	/// 110 = 1.06V
	/// 111 = 1.08V
			const T_REG_INFO_EX& tx_clkregs_level();	//CSR0[12:10]

	/// The second pre-cursor of the TX driver FIR. Used for pre-emphasis control. A signed magnitude value.
	/// Only when CSR34_TXDRV_MAP_SEL  is configured to 1, the register is valid.
			const T_REG_INFO_EX& txfirpre2();	//CSR0[9:5]

	/// The first pre-cursor of the TX driver FIR. Used for pre-emphasis control.
	/// When CSR34_TXDRV_MAP_SEL and CSR48_PCIE_SAS_PIN_EN were configured to 0, the regsiter is the unsigned value, only when  CSR34_TXDRV_MAP_SEL  is configured to 1, the register is the signed value.
			const T_REG_INFO_EX& txfirpre1();	//CSR0[4:0]

	/// The main cursor of the TX driver FIR. Used for pre-emphasis control. A binary value.
			const T_REG_INFO_EX& txfirmain();	//CSR1[15:10]

	/// The first post-cursor of the TX driver FIR. Used for pre-emphasis control.
	/// When CSR34_TXDRV_MAP_SEL and CSR48_PCIE_SAS_PIN_EN were configured to 0, the regsiter is the unsigned value, only when  CSR34_TXDRV_MAP_SEL  is configured to 1, the register is the signed value.
			const T_REG_INFO_EX& txfirpost1();	//CSR1[9:5]

	/// The second post-cursor of the TX driver FIR. Used for pre-emphasis control. A signed magnitude value.
	/// Only when CSR34_TXDRV_MAP_SEL  is configured to 1, the register is valid.
			const T_REG_INFO_EX& txfirpost2();	//CSR1[4:0]

	/// Transmit digital circuitry reset. Active low.
	/// 0 = Reset TX digital logic.
	/// 1 = Normal operation.
			const T_REG_INFO_EX& txrstb();	//CSR2[15:15]

	/// TX data width select.
	/// 000 = 16 bit parallel interface.
	/// 001 = 20 bit parallel interface .
	/// 010 = 32 bit interface.
	/// 011 = 40 bit interface.
	/// 1xx = Reserved.
			const T_REG_INFO_EX& txdwidth();	//CSR2[14:12]

	/// TX bit rate mode:
	/// 00 = full-rate
	/// 01 = 1/2-rate
	/// 10 = 1/4-rate
	/// 11 = 1/8-rate
			const T_REG_INFO_EX& txratemode();	//CSR2[11:10]

	/// Selects the mapping of the parallel TXD bits to the serial bit order.
	/// 0 = LSB is the bit serially output first. 
	/// 1 = MSB is the bit serially output first
			const T_REG_INFO_EX& txbitorder();	//CSR2[9:9]

	/// TX data polarity control. When set, all transmit bits are inverted before being serialized out.
	/// 0 = Do not invert the TX data.
	/// 1 = Invert the TX data
			const T_REG_INFO_EX& txpolarity();	//CSR2[8:8]

	/// Select the clock to which the TX clock is aligned.
	/// 00 = Choose the clock coming along with the TX data from the core
	/// ;01 = Choose the recovered clock from the RX
	/// ;10 = Choose the mclk
	/// ;11 = Choose the clock derived from one of the clock spines. Note that when this selection is made, self-align mode cannot be used (i.e., TXALIGNMODE[2:0]=000).
			const T_REG_INFO_EX& txclksel();	//CSR2[7:6]

	/// Select the parallel TX data to be sent.
	/// 00 = select core data (i.e., TXD).
	/// 01 = select RX parallel data (parallel loop back). 
	/// 10 = select pattern for PRBS generation. 
	/// 11 = Reserved for future use
			const T_REG_INFO_EX& txdatasel();	//CSR2[5:4]

	/// TX alignment window select for the TX phase aligner.
	/// 0 = 2UI
	/// 1 = 4UI
	/// Note : The Numbers are given in 'full' rate UIs
			const T_REG_INFO_EX& txdeadbandsel();	//CSR2[3:3]

	/// TX phase align mode
	/// 000 = Self-align mode.
	/// 001 = Plesio-synchronous self align mode (Not supported in the current version)
	/// 010 = Copy mode where the RX phase code is copied. 
	/// 011 = Freeze mode the TXPHSWRITE[7:0] is set manually
	/// 100 = Jitter generation for test mode
	/// 101 = Synchronous master mode (TXCLKSEL[1:0] must be set to '11')
	/// 11x = Reserved
			const T_REG_INFO_EX& txalignmode();	//CSR2[2:0]

	/// 0 = Normal feature
	/// 1 = Extended feature
			const T_REG_INFO_EX& jitppmctrl();	//CSR3[15:15]

	/// Select jitter frequency (normal/extended):
	/// 000 = infinite words (doesn't move)/1 word
	/// 001 = 2/2 words
	/// 010 = 3/3 words
	/// 011 = 4/4 words
	/// 100 = 6/5 words
	/// 101 = 8/6 words
	/// 110 = 12/7 words
	/// 111 = 16/8 words
			const T_REG_INFO_EX& jitfreq();	//CSR3[14:12]

	/// Select jitter amplitude (normal/extended).
	/// 0000 = 12/3 times           1000 = 12/20 times
	/// 0001 = 16/4 times           1001 = 12/24 times
	/// 0010 = 24/5 times           1010 = 12/32 times
	/// 0011 = 32/6 times           1011 = 12/40 times
	/// 0100 = 48/8 times           1100 = 12/48 times
	/// 0101 = 64/10 times         1101 = 12/64 times
	/// 0110 = 96/12 times         1110 = 12/80 times
	/// 0111 = 128/16 times       1111 = 12/96 times
	/// The number is 2X in 1/2-rate and 4X at 1/4-rate and 8X at 1/8 rate
			const T_REG_INFO_EX& jitamp();	//CSR3[11:8]

	/// Select the k value in calculating the jitter period.
	/// 0 = k=0
	/// 1 = k=1
			const T_REG_INFO_EX& kfactor();	//CSR3[7:7]

	/// not used
			const T_REG_INFO_EX& eco_idlemode_sel();	//CSR3[6:6]

	/// not used
			const T_REG_INFO_EX& eco_tx_detectrx_sel();	//CSR3[5:5]

	/// The MSB (i.e., PPMGEN[4]) defines the slew rate direction. Remaining bits, i.e., PPMGEN[3:0] define the number of words (normal/extended):
	/// 0000 = infinite/0 words    1000 = infinite/12 words
	/// 0001 = 2/2 words                1001 = infinite/16 words
	/// 0010 = 3/3 words                1010 = infinite/20 words
	/// 0011 = 4/4 words                1011 = infinite/24 words
	/// 0100 = 6/5 words                1100 = infinite/32 words
	/// 0101 = 8/6 words                1101 = infinite/40 words
	/// 0110 = 12/8 words              1110 = infinite/48 words
	/// 0111 = 16/10 words            1111 = infinite/64 words
			const T_REG_INFO_EX& ppmgen();	//CSR3[4:0]

	/// TX phase interpolator control (2's complement number).
			const T_REG_INFO_EX& txphswrite();	//CSR4[15:8]

	/// not used
			const T_REG_INFO_EX& tx_tx2rxloopbacksel_eco();	//CSR4[7:7]

	/// PRBS generator enable:. When switching this bit from 0 to 1, PRBS generator is reset.
	/// 0 = Disable PRBS generator
	/// 1 = Enable PRBS generator
			const T_REG_INFO_EX& prbsgenen();	//CSR4[4:4]

	/// Select a pattern for PRBS generator:
	/// 0000 = PRBS7 (X7+X6+1)
	/// 0001 = PRBS9 (X9+X5+1)
	/// 0010 = PRBS10 (X10+X7+1)
	/// 0011 = PRBS11 (X11+X9+1)
	/// 0100 = PRBS15 (X15+X14+1)
	/// 0101 = PRBS20 (X20+X17+1)
	/// 0110 = PRBS23 (X23+X18+1)
	/// 0111 = PRBS31 (X31+X28+1)
	/// 1000 = Custom pattern
	/// 
	/// Note: neither the PRBS pattern nor the custom pattern is affected by TXBITORDER (CSR2[9]).
			const T_REG_INFO_EX& prbsgenpatsel();	//CSR4[3:0]

	/// Custom pattern part 1 (bit[79:64]).
			const T_REG_INFO_EX& txcuspat1();	//CSR5[15:0]

	/// Custom pattern part 2 (bit[63:48]).
			const T_REG_INFO_EX& txcuspat2();	//CSR6[15:0]

	/// Custom pattern part 3 (bit[47:32]).
			const T_REG_INFO_EX& txcuspat3();	//CSR7[15:0]

	/// Custom pattern part 4 (bit[31:16]).
			const T_REG_INFO_EX& txcuspat4();	//CSR8[15:0]

	/// Custom pattern part 5 (bit[15:0]).
			const T_REG_INFO_EX& txcuspat5();	//CSR9[15:0]

	/// Driver clock path power control. This is the power down control for the TX phase interpolator and the subsequent cml2cmos converter. It's used in the synchronous master interface mode to power down the TX phase interpolator for power saving purpose.
	/// 0 = Power down driver clock path
	/// 1 = Power up driver clock path
			const T_REG_INFO_EX& txcppwrdb();	//CSR10[15:15]

	/// TX and RX Clock path voltage regulator power control:
	/// 0 = Power down driver (and rx) clock path
	/// 1 = Power up driver (and rx) clock path and also tx driver voltage regulator
			const T_REG_INFO_EX& txclkregpwrdb();	//CSR10[14:14]

	/// Driver voltage regulator power control:
	/// 0 = Power down driver voltage regulator
	/// 1 = Power up driver voltage regulator
			const T_REG_INFO_EX& txdrvregpwrdb();	//CSR10[13:13]

	/// Driver termination calibration circuitry power control:
	/// 0 = Power down calibration circuitry
	/// 1 = Power up calibration circuitry
			const T_REG_INFO_EX& txdrvcalpwrdb();	//CSR10[12:12]

	/// Driver slew circuitry power control:
	/// 0 = Power down slew control circuitry, (fastest slew)
	/// 1 = Power up slew control circuitry
			const T_REG_INFO_EX& txdrvslewpwrdb();	//CSR10[11:11]

	/// Data dependant noise compensation power down control.
			const T_REG_INFO_EX& txdrvdatdepcomppwrdb();	//CSR10[10:10]

	/// Receiver detect circuitry power control:
	/// 0 = Power down receiver detect circuitry
	/// 1 = Power up receiver detect circuitry
			const T_REG_INFO_EX& txrxdetpwrdb();	//CSR10[9:9]

	/// txdrvf1sel and txdrvf2sel source controlled signal  when PMA mode is PCIE/SATA
	/// 0 = txdrvf1sel and txdrvf2sel controlled by logic when PMA mode is in PCIE/SATA mode
	/// 1 = txdrvf1sel and txdrvf2sel controlled by register TX_CSR12.TXDRVF1SEL and TX_CSR12.TXDRVF2SEL.
			const T_REG_INFO_EX& txdrvbypass();	//CSR10[8:8]

	/// Driver tap powerdown. Active low.
	/// TXTAPPWRDB[0]=1: Power up FLOATING SEG1; t=-2 (or t=+1)->txfirpre2
	/// TXTAPPWRDB[1]=1: Power up SEG2; t=-1->txfirpre1
	/// TXTAPPWRDB[2]=1: Power up SEG3; t=+1->txfirpost1
	/// TXTAPPWRDB[3]=1: Power up FLOATING SEG4; t=+2 (or t=-1)->txfirpost2
	/// TXTAPPWRDB[4]=1: Power up SEG1; t=0
	/// TXTAPPWRDB[5]=1: Power up SEG2; t=0
	/// TXTAPPWRDB[6]=1: Power up SEG3; t=0
	/// TXTAPPWRDB[7]=1: Power up SEG4; t=0
			const T_REG_INFO_EX& txtappwrdb();	//CSR10[7:0]

	/// the 2 lsb was used and the default value of TXREGSPARE[1:0] is 10.
	/// TXREGSPARE[1:0] indicated Regulator referrence voltage tuning
	/// 00 : 0.717V
	/// 01 : 0.777V
	/// 10 : 0.797V
	/// 11 : 0.827V
			const T_REG_INFO_EX& txregspare();	//CSR11[15:8]

	/// Amount of (sourcing) regulator current compensation.
			const T_REG_INFO_EX& txregpatdepsrc();	//CSR11[7:3]

	/// Regulator output voltage level when Vref_tune is set to 0x10
	/// 000 = 0.83V
	/// 001 = 0.86V
	/// 010 = 0.90V
	/// 011 = 0.95V(default)
	/// 100 = 1.01V
	/// 101 = 1.03V
	/// 110 = 1.06V
	/// 111 = 1.08V
			const T_REG_INFO_EX& txregdrvlvl();	//CSR11[2:0]

	/// Amount of (sinking) regulator current compensation.
			const T_REG_INFO_EX& txedgebleed();	//CSR12[15:12]

	/// Not used
			const T_REG_INFO_EX& txpassbleed();	//CSR12[11:8]

	/// TX driver mapping satrt enable, mapping process will satrt when a rising edge of TXDRVSWCTRL detected.
			const T_REG_INFO_EX& txdrvswctrl();	//CSR12[7:7]

	/// Driver floating tap #1 control:
	/// 0 = Include tap t=-2
	/// 1 = Increase power of tap t=+1. This will double the amount of available t=+1 tap
			const T_REG_INFO_EX& txdrvf1sel();	//CSR12[6:6]

	/// Driver floating tap #2 control:
	/// 0 = Include tap t=+2
	/// 1 = Increase power of tap t=-1. This will double the amount of available t=-1 tap
			const T_REG_INFO_EX& txdrvf2sel();	//CSR12[5:5]

	/// TXDRVTAPINV[0]=1: Invert tap FLOATING weight t=-2 (or t=+1)
	/// TXDRVTAPINV[1]=1: Invert tap weight t=-1
	/// TXDRVTAPINV[2]=1: Invert tap weight t=+1
	/// TXDRVTAPINV[3]=1: Invert tap FLOATING weight t=+2 (or t=-1)
	/// TXDRVTAPINV[4]=1: Invert tap weight t=0
			const T_REG_INFO_EX& txdrvtapinv();	//CSR12[4:0]

	/// Generate 2.5mA current for pull-up resistance calibration
	/// 0 = Disabled
	/// 1 = Calibrate
			const T_REG_INFO_EX& txdrvcalhisel();	//CSR13[15:15]

	/// Generate 2.5mA current for pull-done resistance calibration
	/// 0 = Disabled
	/// 1 = Calibrate
			const T_REG_INFO_EX& txdrvcallosel();	//CSR13[14:14]

	/// Calibrate pull-up resistance
	/// 0 = Disabled
	/// 1 = Calibrate
			const T_REG_INFO_EX& txdrvcalpsel();	//CSR13[13:13]

	/// Calibrate pull-dn resistance
	/// 0 = Disabled
	/// 1 = Calibrate
			const T_REG_INFO_EX& txdrvcalmsel();	//CSR13[12:12]

	/// Select calibration path (p/m)
	/// 00 = Disabled
	/// 01 = Observe calibration results via tx 'p' port
	/// 10 = Observe  calibration results via tx 'm' port
	/// 11 = Observe LVCC
			const T_REG_INFO_EX& txdrvotbpctrl();	//CSR13[11:10]

	/// Select calibration reference
	/// 00 = Disabled
	/// 01 = Reference for calibrated pull-up resistance
	/// 10 = Mid-rail
	/// 11 = Reference for calibrated pull-dn resistance
			const T_REG_INFO_EX& txdrvotbmctrl();	//CSR13[9:8]

	/// monitor RX calibration comparator feedback
			const T_REG_INFO_EX& dstxlowoffpwrdb();	//CSR13[7:7]

	/// This bit is used to control the BIAS receiver test feature. This feature is used to bypass the dataslice bias receivers in order to do isolated parametric testing. Unsuported.
			const T_REG_INFO_EX& dstxlowoffcal();	//CSR13[6:6]

	/// Not used
			const T_REG_INFO_EX& dstxlowoffctrl();	//CSR13[5:0]

	/// TX driver calibration start control. Used only in automatic and semi-automatic modes.
	/// 0 = Do not start TX driver calibration
	/// 1 = Start TX driver calibration
			const T_REG_INFO_EX& txdrvcalstart();	//CSR14[15:15]

	/// Not used. This register is hardcoded to read '0'
			const T_REG_INFO_EX& dstxlowoffout();	//CSR14[14:14]

	/// Direction control for calibrating the lowoff comparator for the TX driver.
	/// 0 = positive direction
	/// 1 = negative direction
			const T_REG_INFO_EX& txdrvcaldir();	//CSR14[13:13]

	/// Calibration voltage output control
	/// 00 = Disabled
	/// 01 = Observe driver calibration output voltage
	/// 10 = Unused
	/// 11 = Observe VSS
			const T_REG_INFO_EX& txtopotbctrl();	//CSR14[12:11]

	/// TX driver slew rate control:
	/// When TXDRSLEWPWRDB the driver is to its optimal slew. 
	/// 000 = Fastest or smallest rise and fall times
	/// ��.
	/// 111 = Slowest or longest rise and fall times. This feature is meant to be used only at lower data rates.
			const T_REG_INFO_EX& txdrvslew();	//CSR14[10:8]

	/// Not used
			const T_REG_INFO_EX& txdrvregcalen();	//CSR14[7:7]

	/// Adjust current handling of driver regulator
	/// 0 = More current
	/// 1 = Less current
			const T_REG_INFO_EX& txdrvregslicetune();	//CSR14[6:6]

	/// TX termination calibration mode. Switching from manual mode to auto mode restarts the auto calibration process.
	/// 00 = Auto full TX termination calibration and FFE mapping via FSM
	/// 01 = Only TX termination calibration via FSM
	/// 10 = Only TX FFE mapping via FSM
	/// 11 = Manual termination calibration or FFE mapping via related registers.
			const T_REG_INFO_EX& txtermcalmode();	//CSR14[5:4]

	/// Not used
			const T_REG_INFO_EX& txdrvtesten();	//CSR15[15:15]

	/// Not used
			const T_REG_INFO_EX& txdrvtestin();	//CSR15[14:14]

	/// Select TX driver regulator observation point
	/// 001 = vregout
	/// 010 = vss
	/// 011 = vgp
	/// 100 = hvcc
	/// 101 = vbiasn
	/// 110 = vmir_lf
	/// 111 = vmir_hf
			const T_REG_INFO_EX& txdrvregatbctrl();	//CSR15[13:11]

	/// Selects pre-mux in front of the low offset comparator.
	/// 00 = Tristate
	/// 01 = RX calibration will use the low offset comparator 
	/// 10 = TX calibration will use the low offset comparator
	/// 11 = DSCLK calibration will use the low offset comparator
			const T_REG_INFO_EX& dslowoffctrl();	//CSR15[10:9]

	/// Select TX clock regulator observation point
	/// 001 = vregout
	/// 010 = vref
	/// 011 = vgp
	/// 100 = vgpc
	/// 101 = vbiasn
	/// 110 = vmir_lf
	/// 111 = vmir_hf
			const T_REG_INFO_EX& txclkregatbctrl();	//CSR15[8:6]

	/// Select TX driver observation point
	/// 00 = Disabled
	/// 01 = P slew voltage
	/// 10 = N slew voltage
	/// 11 = VREG_DRV
			const T_REG_INFO_EX& txdrvatbctrl();	//CSR15[5:4]

	/// Select TX master mirror observation point
	/// 00 = Disabled
	/// 01 = CV output
	/// 10 = HVCC
	/// 11 = CC output
			const T_REG_INFO_EX& txmastermiratbctrl();	//CSR15[3:2]

	/// Select TX top observation point
	/// 00 = rxdetect vref
	/// 01 = TX regulators atb
	/// 10 = TX master mirror atb
	/// 11 = TX driver atb
			const T_REG_INFO_EX& txtopatbctrl();	//CSR15[1:0]

	/// TXDRVSEL[7:0] for TX driver cluster 1.
			const T_REG_INFO_EX& txdrvsel1();	//CSR16[15:8]

	/// Driver cluster 1 slice based control:
	/// [7:5]      = SEGCTRL1[23:21] (slice 8)
	/// [4:2]      = SEGCTRL1[20:18] (slice 7)
	/// [1:0]      = SEGCTRL1[17:16] (part of slice 6)
			const T_REG_INFO_EX& seg1ctrl23to16();	//CSR16[7:0]

	/// Driver cluster 1 slice based control:
	/// [15]         = SEGCTRL1[15] (part of slice 6)
	/// [14:12]   = SEGCTRL1[14:12] (slice 5)
	/// [11:9]     = SEGCTRL1[11:9] (slice 4)
	/// [8:6]       = SEGCTRL1[8:6] (slice 3)
	/// [5:3]       = SEGCTRL1[5:3] (slice 2)
	/// [2:0]       = SEGCTRL1[2:0] (slice 1)
			const T_REG_INFO_EX& seg1ctrl15to0();	//CSR17[15:0]

	/// TXDRVSEL[15:8] for TX driver cluster 2.
			const T_REG_INFO_EX& txdrvsel2();	//CSR18[15:8]

	/// Driver cluster 2 slice based control:
	/// [7:5]      = SEGCTRL1[23:21] (slice 8)
	/// [4:2]      = SEGCTRL1[20:18] (slice 7)
	/// [1:0]      = SEGCTRL1[17:16] (part of slice 6)
			const T_REG_INFO_EX& seg2ctrl23to16();	//CSR18[7:0]

	/// Driver cluster 2 slice based control:
	/// [15]         = SEGCTRL1[15] (part of slice 6)
	/// [14:12]   = SEGCTRL1[14:12] (slice 5)
	/// [11:9]     = SEGCTRL1[11:9] (slice 4)
	/// [8:6]       = SEGCTRL1[8:6] (slice 3)
	/// [5:3]       = SEGCTRL1[5:3] (slice 2)
	/// [2:0]       = SEGCTRL1[2:0] (slice 1)
			const T_REG_INFO_EX& seg2ctrl15to0();	//CSR19[15:0]

	/// TXDRVSEL[23:16] for TX driver cluster 3.
			const T_REG_INFO_EX& txdrvsel3();	//CSR20[15:8]

	/// Driver cluster 3 slice based control:
	/// [7:5]      = SEGCTRL1[23:21] (slice 8)
	/// [4:2]      = SEGCTRL1[20:18] (slice 7)
	/// [1:0]      = SEGCTRL1[17:16] (part of slice 6)
			const T_REG_INFO_EX& seg3ctrl23to16();	//CSR20[7:0]

	/// Driver cluster 3 slice based control:
	/// [15]         = SEGCTRL1[15] (part of slice 6)
	/// [14:12]   = SEGCTRL1[14:12] (slice 5)
	/// [11:9]     = SEGCTRL1[11:9] (slice 4)
	/// [8:6]       = SEGCTRL1[8:6] (slice 3)
	/// [5:3]       = SEGCTRL1[5:3] (slice 2)
	/// [2:0]       = SEGCTRL1[2:0] (slice 1)
			const T_REG_INFO_EX& seg3ctrl15to0();	//CSR21[15:0]

	/// TXDRVSEL[31:24] for TX driver cluster 4.
			const T_REG_INFO_EX& txdrvsel4();	//CSR22[15:8]

	/// Driver cluster 4 slice based control:
	/// [7:5]      = SEGCTRL1[23:21] (slice 8)
	/// [4:2]      = SEGCTRL1[20:18] (slice 7)
	/// [1:0]      = SEGCTRL1[17:16] (part of slice 6)
			const T_REG_INFO_EX& seg4ctrl23to16();	//CSR22[7:0]

	/// Driver cluster 2 slice based control:
	/// [15]         = SEGCTRL1[15] (part of slice 6)
	/// [14:12]   = SEGCTRL1[14:12] (slice 5)
	/// [11:9]     = SEGCTRL1[11:9] (slice 4)
	/// [8:6]       = SEGCTRL1[8:6] (slice 3)
	/// [5:3]       = SEGCTRL1[5:3] (slice 2)
	/// [2:0]       = SEGCTRL1[2:0] (slice 1)
			const T_REG_INFO_EX& seg4ctrl15to0();	//CSR23[15:0]

	/// This register contains the present binary phase value of the TX phase interpolator.
			const T_REG_INFO_EX& txphsval();	//CSR24[14:8]

	/// Not used
			const T_REG_INFO_EX& nmoscalstatus();	//CSR24[7:4]

	/// Not used
			const T_REG_INFO_EX& pmoscalstatus();	//CSR24[3:0]

	/// the 0-bit as the control signal of:txdrv_cal_replica_en
	/// 0= driver direct calibration
	/// 1= driver replica calibration
	/// the 1-bit as the control signal of txdrv_sliceboost_tune
	/// 0= driver boost tune off
	/// 1= driver boost tune on
	/// the 2 to 7 bit dose not use.
			const T_REG_INFO_EX& txspare();	//CSR25[15:8]

	/// Hi-Z and Idle mode switch control for TX.
	/// 0 = idle
	/// 1 = Hi-Z
			const T_REG_INFO_EX& tx_idle_hiz_sw_crg();	//CSR25[7:7]

	/// For debug. RX detection output mode switch.
			const T_REG_INFO_EX& tx_detectrx_sel();	//CSR25[6:6]

	/// Loopback path select
	/// 0 = data is coming from the bump
	/// 1 = data is not coming from the bump
			const T_REG_INFO_EX& tx_tx2rxloopbacksel();	//CSR25[5:5]

	/// all slices of P-driver and M-dirver status controlled by calibration logic or stuck to 0(txdrv_open_enp and txdrv_open_enm)
	/// 0 = all slices of P-driver and M-driver closed
	/// 1 = all slices of P-driver and M-driver status controlled by calibration logic
			const T_REG_INFO_EX& txdrv_open_en();	//CSR25[4:4]

	/// 
			const T_REG_INFO_EX& txdigspare();	//CSR25[3:2]

	/// Direction control for TX driver down side calibration.
	/// 0 = TBD
	/// 1 = TBD
			const T_REG_INFO_EX& txdrvcaldndir();	//CSR25[1:1]

	/// Direction control for TX driver up side calibration.
	/// 0 = TBD
	/// 1 = TBD
			const T_REG_INFO_EX& txdrvcalupdir();	//CSR25[0:0]

	/// 0 = TX Driver calibration is still in progress
	/// 1 = TX Driver calibration has completed
			const T_REG_INFO_EX& txdrvcaldone();	//CSR26[15:15]

	/// 0 = TX tap mapping is not done
	/// 1 = TX tap mapping is done
			const T_REG_INFO_EX& txtapmapdone();	//CSR26[14:14]

	/// Result of TX driver down side calibration.
			const T_REG_INFO_EX& txdrvncaldn();	//CSR26[11:6]

	/// Result of TX driver up side calibration.
			const T_REG_INFO_EX& txdrvncalup();	//CSR26[5:0]

	/// Stop TX driver calibration timer, for debugging.
	/// 0 = normal
	/// 1 = stop the timer
			const T_REG_INFO_EX& txcal_timer_stop();	//CSR27[14:14]

	/// Configuration of the TX driver calibration timer for waiting, which is the cycles of reference clock.
			const T_REG_INFO_EX& txcal_timer_value();	//CSR27[13:4]

	/// Enable the divider in TX driver calibration timer,not available in current design.
	/// 0 = disable
	/// 1 = enable
			const T_REG_INFO_EX& txcal_timer_div_en();	//CSR27[3:3]

	/// Configuration of divider in TX driver calibration timer, for debugging.
			const T_REG_INFO_EX& txcal_timer_div_value();	//CSR27[2:0]

	/// The first post-cursor of the TX driver FIR from the pin 'tx_deemph'. For TX configuration debugging.
			const T_REG_INFO_EX& tx_training_firpost1();	//CSR28[15:11]

	/// The main-cursor of the TX driver FIR from the pin 'tx_deemph'. For TX configuration debugging.
			const T_REG_INFO_EX& tx_training_firmain();	//CSR28[10:5]

	/// The first pre-cursor of the TX driver FIR from the pin 'tx_deemph'. For TX configuration debugging.
			const T_REG_INFO_EX& tx_training_firpre1();	//CSR28[4:0]

	/// The full swing of TX driver.
			const T_REG_INFO_EX& tx_local_fs();	//CSR29[13:8]

	/// The low frequency swing of TX driver.
			const T_REG_INFO_EX& tx_local_lf();	//CSR29[5:0]

	/// Stop receiver detection timer, for debugging.
	/// 0 = normal
	/// 1 = stop the timer
			const T_REG_INFO_EX& rxdet_timer_stop();	//CSR30[14:14]

	/// Configuration of receiver detection timer for receiver detector initialization, which is the cycles of reference clock.
			const T_REG_INFO_EX& rxdet_init_timer_value();	//CSR30[13:4]

	/// Configuration of divider in receiver detection timer for receiver detector initialization, for debugging.
			const T_REG_INFO_EX& rxdet_init_timer_div_value();	//CSR30[2:0]

	/// Configuration of receiver detection timer for receiver detector charge/discharge, which is the cycles of reference clock.
			const T_REG_INFO_EX& rxdet_charge_timer_value();	//CSR31[13:4]

	/// Configuration of divider in receiver detection timer for receiver detector charge/discharge, for debugging.
			const T_REG_INFO_EX& rxdet_charge_timer_div_value();	//CSR31[2:0]

	/// Monitor value from pin 'TX_RXDET_EN'.
			const T_REG_INFO_EX& tx_rxdet_en_pin_mon();	//CSR32[14:14]

	/// Indicate the result of receiver detect is valid for read.
	/// 0 = The result of receiver detect is invalid
	/// 1 = The result of receiver detect is valid
			const T_REG_INFO_EX& tx_rxdet_ready();	//CSR32[13:13]

	/// The result of receiver detect, valid when 'TX_RXDET_READY' is high
	/// 0 = no  receiver has been connect to local transmitter
	/// 1 = a  receiver has been connect to local transmitter
			const T_REG_INFO_EX& tx_rxdet_out();	//CSR32[12:12]

	/// Indicate the power status of the analog circuit for receiver detect, for debugging.
	/// 0 = power down the receiver detect circuit
	/// 1 = power on the receiver detect circuit
			const T_REG_INFO_EX& tx_rxdet_pwrdb();	//CSR32[11:11]

	/// Indicate current status of receiver detect, for debuggsing.
	/// 000 = idle
	/// 101 = discharge
	/// 110 = charge
	/// 100 = initial
	/// else = reserved
			const T_REG_INFO_EX& tx_rxdet_mode();	//CSR32[10:8]

	/// TX driver FFE configuration start error flag, clear when read.  Error will be assert when the value of pin  'tx_deemph' changed while mapping.
	/// 0 = No error have been detected while TX driver FFE configuration
	/// 1= At lease one error have been detected while TX driver FFE configuration
			const T_REG_INFO_EX& tx_training_start_err();	//CSR32[5:5]

	/// Indicate the polarity of TX driver FFE tap.
	/// 0 = The coefficient of current tap is positive
	/// 1 = The coefficient of current tap is nagitive
			const T_REG_INFO_EX& txdrv_tap_inv();	//CSR32[4:0]

	/// Monitor value of pin 'TXDRV_IDLE_EN'.
			const T_REG_INFO_EX& txdrv_idle_en_pin_mon();	//CSR33[15:15]

	/// TX driver IDLE enable,  active high. Only available in PCIe L0 or SAS phyrdy states and pin disabled ('PCIE_SAS_PIN_EN'=0). For debugging.
	/// Note: Set TX driver to idle while TX driver calibration is not permitted.
			const T_REG_INFO_EX& txdrv_idle_en();	//CSR33[14:14]

	/// not used
			const T_REG_INFO_EX& txdrv_open_en_eco();	//CSR33[13:13]

	/// TX driver IDLE enable extra delay control, for debug using.
	/// 0 = IDLE enable arrive to analog 2 txwclk cycles after parallel data
	/// 1 =  IDLE enable arrive to analog 1 txwclk cycles after parallel data
			const T_REG_INFO_EX& txdrv_idle_en_dly();	//CSR33[11:11]

	/// Select the source of TX PI code to analog.(for C2M application)
	/// 0 = Select PI code from Phase Aligner
	/// 1 = Select External PI code
			const T_REG_INFO_EX& picodein_sel();	//CSR33[10:10]

	/// Indicate TX phase align status
	/// 0 = phase align is still running
	/// 1 = phase align is done
			const T_REG_INFO_EX& tx_phase_align_done();	//CSR33[9:9]

	/// TX phase align done status clear enable, active high.
			const T_REG_INFO_EX& tx_pa_status_clr();	//CSR33[8:8]

	/// The threshold of phase align.
			const T_REG_INFO_EX& tx_phase_align_thr();	//CSR33[7:0]

	/// Force all the slices of driver P to be open.
	/// 0: normal
	/// 1: open
			const T_REG_INFO_EX& txdrv_open_en_p();	//CSR34[15:15]

	/// Force all the slices of driver M to be open.
	/// 0: normal
	/// 1: open
			const T_REG_INFO_EX& txdrv_open_en_m();	//CSR34[14:14]

	/// TX driver IDLE control bypass enable for debug, active high. For debugging.
	/// 0 = Enable TX driver IDLE control
	/// 1 = Bypass TX driver IDLE control
			const T_REG_INFO_EX& txdrv_idle_bypass();	//CSR34[13:13]

	/// TX data rate and bus width switch bypass enable, for debugging.
	/// 0 = enbale TX data rate and bus width switch
	/// 1 = bypass TX data rate and bus width switch
			const T_REG_INFO_EX& tx_wrate_sw_bypass();	//CSR34[12:12]

	/// TX receiver detect enable, active high.  Only available in PCIe L0/L0s/L1 states and pin disabled ('PCIE_SAS_PIN_EN'=0)
	/// Note: Receiver detection while TX driver calibration is not permitted.
			const T_REG_INFO_EX& tx_rxdet_en();	//CSR34[11:11]

	/// Receiver detect threshold(reference voltage) control
	/// 00 = 0.822*Vregdrv
	/// 01 = 0.856*Vregdrv
	/// 10 = 0.890*Vregdrv
	/// 11 = 0.925*Vregdrv
			const T_REG_INFO_EX& tx_rxdet_level();	//CSR34[10:9]

	/// The delay of idle enable signal adjustment in analog circuit, for debugging.
	/// 000 = No extra delay
	/// 001 = Extra delay 8UI
	/// 010 = Extra delay 16UI
	/// 011 = Extra delay 24UI
	/// 1xx = Extra delay 32UI
			const T_REG_INFO_EX& tx_idle_dly_ana();	//CSR34[8:6]

	/// txoclk source select
	/// 0 = select txoclk to output port 
	/// 1 = select mclk to output port
			const T_REG_INFO_EX& txoclk_sel();	//CSR34[5:5]

	/// Tx driver mapping select, for debug using.
	/// 0 = mapping from registers ('PCIE_SAS_PIN_EN'=0) or from pin  ('PCIE_SAS_PIN_EN'=1)
	/// 1 = mapping always from registers.
			const T_REG_INFO_EX& txdrv_map_sel();	//CSR34[4:4]

	/// TX driver tap invert control select, only used when mapping from the pin 'tx_deemph'.
	/// 0 = Force pre1 and  post1 tap to negative value and other taps to positive value
	/// 1 = FFE tap invert controled by TX_CSR12 'TXDRVTAPINV[4:0]'
			const T_REG_INFO_EX& txdrv_tapinv_sel();	//CSR34[3:3]

	/// when data-rate switched, hsclk or mclk source select signal
	/// 0 = 2.5/5G pcie or 1.5/3/6G sata mode, select hsclk0 and mclk0 from clockslice0, when worked in PCIE 8G or SATA 12G mode, select hsclk1 and mclk1 form clockslice1
	/// 1 = 2.5/5G pcie or 1.5/3/6G sata mode, select hsclk1 and mclk1 from clockslice1, when worked in PCIE 8G or SATA 12G mode, select hsclk0 and mclk0 from clockslice0
			const T_REG_INFO_EX& pcie_wrate_hsclk_sel();	//CSR34[2:2]

	/// TX termination calibration targe resist value choice.
	/// 00 = revered
	/// 01 = 50 Ohm
	/// 10 = revered
	/// 11 = 45 Ohm
			const T_REG_INFO_EX& txdrv_ressel();	//CSR34[1:0]

	/// TX driver slice boost enable
			const T_REG_INFO_EX& txdrv_sliceboost_en();	//CSR35[13:13]

	/// Regulator loading adjust power down;
			const T_REG_INFO_EX& clkreg_selfbleed_pdb();	//CSR35[12:12]

	/// Regulator loading adjust ;
			const T_REG_INFO_EX& clkreg_selfbleed();	//CSR35[11:8]

	/// TX termination calibration results down(N) offset compensate, the MSB is the sign-bit, and the other bits the unsigned binary code. The range from -7 to +7.
	/// Note: the value must configure before tx calibration start
			const T_REG_INFO_EX& ncaldn_offset();	//CSR35[7:4]

	/// TX termination calibration results up(P) offset compensate, the MSB is the sign-bit, and the other bits the unsigned binary code. The range from -7 to +7.
	/// Note: the value must configure before tx calibration start
			const T_REG_INFO_EX& ncalup_offset();	//CSR35[3:0]

	/// PCIe/SAS global control block software reset, low active. Only active in PCIe/SAS mode.
	/// 0 = Reset  PCIe/SAS global control block logic.
	/// 1 = Normal operation.
			const T_REG_INFO_EX& pcie_sas_sw_rstb();	//CSR48[15:15]

	/// Pin powerState[2:0], datarate[2:0],datawidth[2:0] for global control block,
	/// Pin tx_idle_en, detectrx_en,txdeemph[17:0] for TX_DIG
	/// Pin rxeyediag_start,rxctlepreset[2:0] for RX_DIG enable, 
	/// 0 = Disable
	/// 1 = Enable
	/// Notes: forbid to configure both PSTATE_WRATE_VLD and PCIE_SAS_PIN_EN  register   to  1'b1 .
			const T_REG_INFO_EX& pcie_sas_pin_en();	//CSR48[14:14]

	/// The HiLink 15BP supports three main modes: PCIe mode,  SAS and SATA mode. 
	/// 00 = PCIE mode
	/// 01 = SAS and SATA mode
	/// 10 = Normal mode
	/// 11=  Reserved
			const T_REG_INFO_EX& pma_mode();	//CSR48[13:12]

	/// Valid for PCIE_SAS_POWER_STATE, PCIE_SAS_DATA_RATE,PCIE_SAS_DATA_WIDTH register configure . Only active in PCIe/SAS mode.
	/// 1: valid
	/// 0: invalid
	/// Notes: forbid to configure both PSTATE_WRATE_VLD and PCIE_SAS_PIN_EN  register   to  1'b1 .
			const T_REG_INFO_EX& pstate_wrate_vld();	//CSR48[11:11]

	/// Power state parameter configure, active when PSTATE_WRATE_VLD =1 . Only used  in PCIe/SAS mode.
	/// 000 =  PCIe L0 or SAS/SATA PHYRDY state
	/// 001 =  PCIe L0s or SAS/SATA PARTIAL state
	/// 010 =  PCIe L1 state
	/// 100 =  PCIe L2 or SAS/SATA SLUMBE state
	/// others = forbid
			const T_REG_INFO_EX& pcie_sas_power_state();	//CSR48[10:8]

	/// Data rate  parameter configure, active when PSTATE_WRATE_VLD =1 . Only used  in PCIe/SAS mode.
	/// 3'b000��Gen1-2.5GT/s
	/// 3'b001��Gen2-5.0GT/s
	/// 3'b010��Gen3-8.0GT/s
	/// SAS/SATA Mode:
	/// 3'b100��Gen1-1.5GT/s
	/// 3'b101��Gen2-3.0GT/s
	/// 3'b110��Gen3-6.0GT/s
	/// 3'b111��Gen3-12GT/s
	/// others = forbid
			const T_REG_INFO_EX& pcie_sas_data_rate();	//CSR48[6:4]

	/// Hilink TX/RX ready configure.
	/// Once  hilink initialization is done, configure this register, pin rxtx_status will be assert, TX/RX will  start to receive PCIe/SAS core any control request.(eg.
	///  (1) Power state/data rate/width switch request.
	///  (2) Loss/receiver detect control request. etc.).
	/// 1:  Ready
	/// 0: Not ready.
	/// Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& pcie_sas_rxtx_status_rdy();	//CSR48[3:3]

	/// Data width  parameter configure, active when PSTATE_WRATE_VLD =1 . Only used  in PCIe/SAS mode.
	///  Only active in PCIe/SAS mode.
	/// 000 = 16(8,4) bit parallel data
	/// 001 = 20(10,5) bit parallel data
	/// 010 = 32(16,8) bit parallel data
	/// 011 = 40(20,10)bit parallel data
	/// others = forbid
			const T_REG_INFO_EX& pcie_sas_data_width();	//CSR48[2:0]

	/// Mask power down control for RX signal detect function  in PCIe/SAS mode, high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
			const T_REG_INFO_EX& rxsigdet_pwrdnb_msk();	//CSR49[15:15]

	/// Mask power down control for  Transmit Receiver detection  control in PCIe/SAS mode , high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
			const T_REG_INFO_EX& txrxdet_pwrdnb_msk();	//CSR49[14:14]

	/// Mask power down control for  HiLink RX Analog  in PCIe/SAS mode, high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
			const T_REG_INFO_EX& rxpwrdnb_msk();	//CSR49[13:13]

	/// Mask power down control for  HiLink TX Analog in PCIe/SAS mode, high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
			const T_REG_INFO_EX& txpwrdnb_msk();	//CSR49[12:12]

	/// Mask power down control for  DSCLK  all dsclk circuit except spine clock buffer ,regulator and cml2cmos circuit  in PCIe/SAS mode, high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
			const T_REG_INFO_EX& dsclkgen_pwrdnb_msk();	//CSR49[11:11]

	/// Mask power down control for  HiLink analog DSCLK IDAC  in PCIe/SAS mode, high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
			const T_REG_INFO_EX& dsclk_idac_pwrdnb_msk();	//CSR49[10:10]

	/// Mask  power down control for dsclk idac regulator  in PCIe/SAS mode, high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
			const T_REG_INFO_EX& dsclk_vregdac_pwrdnb_msk();	//CSR49[9:9]

	/// Mask  power down control for Power down dsclk cml2cms regulator in PCIe/SAS mode , high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
			const T_REG_INFO_EX& dsclk_vregl_pwrdnb_msk();	//CSR49[8:8]

	/// Mask reset control in RX signal detect  when power state switch happen,high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
			const T_REG_INFO_EX& rx_sw_sigdet_rstb_msk();	//CSR49[6:6]

	/// Mask cdr reset control in RX when power state switch happen,high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
			const T_REG_INFO_EX& rx_sw_cdr_rstb_msk();	//CSR49[5:5]

	/// Mask reset control in RX when power state switch happen,high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
			const T_REG_INFO_EX& rx_sw_rstb_msk();	//CSR49[4:4]

	/// Mask clock control in RX loss detect block, Only active in PCIe/SAS mode.
	/// high active.
	/// 0 = Not mask
	/// 1 = Mask
			const T_REG_INFO_EX& rx_loss_det_clk_en_msk();	//CSR49[3:3]

	/// Mask rxwordclk enable control when power state switch happen, high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
			const T_REG_INFO_EX& rx_sw_clk_en_msk();	//CSR49[2:2]

	/// Mask txwordclk enable control when power state switch happen,high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
			const T_REG_INFO_EX& tx_sw_clk_en_msk();	//CSR49[1:1]

	/// Mask reset control in TX when power state switch happen,high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
			const T_REG_INFO_EX& tx_sw_rstb_msk();	//CSR49[0:0]

	/// Divider value for power state switch timer. Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& pstate_timer_div_value();	//CSR50[15:12]

	/// Time value for power state switch timer. Only active in PCIe/SAS mode.
	/// Note: TX/RX clock stable time  = ( PSTATE_TIMER_DIV_VALUE + 1) * (PSTATE_TIMER_VALUE + 1) * cycle time of hclk clock after power up.
			const T_REG_INFO_EX& pstate_timer_value();	//CSR50[9:0]

	/// Divider value for DSCLK calibration timeout. Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& dsclk_timer_div_value();	//CSR51[15:12]

	/// Spare configure regiser
			const T_REG_INFO_EX& pcie_sas_spare();	//CSR51[11:4]

	/// Divider value for data rate/width switch timeout. Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& wrate_timer_div_value();	//CSR51[3:0]

	/// Time value for DSCLK calibraion timeout. Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& dsclk_timer_value();	//CSR52[13:0]

	/// Time value for data rate/width switch timeout. Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& wrate_timer_value();	//CSR53[13:0]

	/// Histroy alarm for power state code error. Only active in PCIe/SAS mode,  Clear after
	/// softeware read.
			const T_REG_INFO_EX& his_alarm_pstate_code_err();	//CSR54[15:15]

	/// Histroy alarm for illegal power state switch. Only active in PCIe/SAS mode. Clear after softeware read.
			const T_REG_INFO_EX& his_alarm_pstate_sw_err();	//CSR54[14:14]

	/// History alarm for illegal data rate/width switch, Only active in PCIe/SAS mode.  Clear after softeware read.
			const T_REG_INFO_EX& his_alarm_wrate_sw_err();	//CSR54[13:13]

	/// History alarm for power state and rate/width switch at the same time. Only active in PCIe/SAS mode. Clear after softeware read.
			const T_REG_INFO_EX& his_alarm_pstate_wrate_err();	//CSR54[12:12]

	/// History alarm for Only one  power state and rate/width switch request lauch when HiLink status is not ready, Only active in PCIe/SAS mode.  Clear after softeware read.
			const T_REG_INFO_EX& his_alarm_one_sw_req_vio();	//CSR54[11:11]

	/// History alarm for two or more power state and rate/width switch request lauch when HiLink status is not ready, Only active in PCIe/SAS mode.  Clear after softeware read.
			const T_REG_INFO_EX& his_alarm_sw_req_drop();	//CSR54[10:10]

	/// Alarm for DSCLK calibration timeout in rate/width switch. Only active in PCIe/SAS mode. Clear after softeware read.
			const T_REG_INFO_EX& alarm_dsclk_calib_timeout();	//CSR54[9:9]

	/// Alarm for TX rate/width switch timeout. Only active in PCIe/SAS mode. Clear after softeware read.
			const T_REG_INFO_EX& alarm_wrate_txsw_timeout();	//CSR54[8:8]

	/// Alarm for RX rate/width switch timeout. Only active in PCIe/SAS mode. Clear after softeware read.
			const T_REG_INFO_EX& alarm_wrate_rxsw_timeout();	//CSR54[7:7]

	/// Status reigster for PCIE_SAS_POWER_STATE[2:0] , PCIE_SAS_DATA_WIDTH[2:0],PCIE_SAS_DATA_RATE[2:0] parameter load done in intialization process, Only active in PCIe/SAS mode,in common mode, Don't care
	/// the status.
			const T_REG_INFO_EX& pstate_wrate_load_done();	//CSR54[6:6]

	/// History alarm for  data rate parameter error from PIN.Only active in PCIe/SAS mode.  Clear after softeware read.
			const T_REG_INFO_EX& his_alarm_width_para_err();	//CSR54[5:5]

	/// History alarm for  data width parameter error from PIN.Only active in PCIe/SAS mode. Clear after softeware read.
			const T_REG_INFO_EX& his_alarm_rate_para_err();	//CSR54[4:4]

	/// Current power state when power state switch not obey to PCIe/SAS protocol. Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& curr_power_state();	//CSR55[10:8]

	/// Next power state when power state switch not obey to PCIe/SAS protocol. Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& next_power_state();	//CSR55[6:4]

	/// Latest error power state code. Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& power_state_err_code();	//CSR55[2:0]

	/// Current data rate value,when rate/width switch at power state = L1/L2. Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& curr_data_rate();	//CSR56[14:12]

	/// Next data rate value,when rate/width switch at power state = L1/L2. Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& next_data_rate();	//CSR56[10:8]

	/// Current data width value,when rate/width switch at power state = L1/L2. Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& curr_data_width();	//CSR56[6:4]

	/// Next data width value,when rate/width switch at power state = L1/L2. Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& next_data_width();	//CSR56[2:0]

	/// Regulator loading adjust power down;
			const T_REG_INFO_EX& drvreg_selfbleed_pdb();	//CSR57[15:15]

	/// Regulator loading adjust ;
			const T_REG_INFO_EX& drvreg_selfbleed();	//CSR57[14:11]

	/// Data rate on the pin between PCIe/SAS core with HiLink in time. Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& pin_data_rate();	//CSR57[10:8]

	/// Data width on the pin between PCIe/SAS core with HiLink in time. Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& pin_data_width();	//CSR57[6:4]

	/// Power state on the pin between PCIe/SAS core with HiLink in time. Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& pin_power_state();	//CSR57[2:0]

	/// Current state for power state, data width and rate switch global control FSM. Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& sw_glb_fsm_curr_st();	//CSR58[15:14]

	/// Current state for Power state switch timer FSM. Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& pstate_time_fsm_curr_st();	//CSR58[10:8]

	/// Hilink status for ready to receive power state, data rate and width switch request, high active. Only active in PCIe/SAS mode.
	/// 1 = Ready to receive switch request
	/// 0 = Not ready to receive switch request
			const T_REG_INFO_EX& rxtx_status();	//CSR58[7:7]

	/// Current state for data rate and width switch FSM. Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& wrate_sw_fsm_curr_st();	//CSR58[6:4]

	/// Current state for Power state switch FSM. Only active in PCIe/SAS mode.
			const T_REG_INFO_EX& pstate_fsm_curr_st();	//CSR58[2:0]

	/// Select test signal for PCIe/SAS control , DSCLK, TX_DIG, RX_DIG block.
			const T_REG_INFO_EX& ds_dig_test_sel();	//CSR59[7:0]

	/// Interface signal status between PCIe/SAS Control block with TX/RX_DIG block for power state, rate, and width switch, Only active PCIe/SAS mode and for debug.
	/// [15]   : syn_rx_wrate_sw_done             
	/// [14]   : syn_tx_wrate_sw_done              
	/// [13]   : o_glb_dsclk_sw_clkspinesel     
	/// [12]   : o_glb_tx_wrate_sw_flag             
	/// [11]   : o_glb_rx_clk_en                            
	/// [10]   : o_glb_rx_loss_squ_det_clk_en  
	/// [9]     : o_glb_rx_sw_rstb                          
	/// [8]     : o_glb_rx_sw_sigdet_rstb             
	/// [7]     : o_glb_rx_para_vld    
	/// [6:4]  : o_glb_rx_data_rate 
	/// [3]     : o_glb_rx_sw_cdr_rstb                        
	/// [2:0]  : o_glb_rx_data_width
			const T_REG_INFO_EX& pstate_wrate_if_status();	//CSR60[15:0]

	/// Power state switch type signal for debug in  PCIe/SAS control block,Only active PCIe/SAS mode.
	/// [15:8]: Reserve
	/// [7]     : latch_pstate_wrate_sw  signal
	/// [6]     : latch_wrate_pstate_sw  signal
	/// [5]     : latch_buf_l0_l0s_sw      signal
	/// [4]     : latch_buf_l0_l1_sw        signal
	/// [3]     : latch_buf_l0_l2_sw        signal
	/// [2]     : latch_buf_l0s_l0_sw      signal
	/// [1]     : latch_buf_l1_l0_sw        signal
	/// [0]     : latch_buf_l2_l0_sw        signal
			const T_REG_INFO_EX& pstate_sw_status();	//CSR61[15:0]
			bool get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos);
	};
public:
	_REG_INFO REG_INFO;

	uint csr[DS_TX_CSR_NUM];


	//CSR0[15:15]
	DS_txRegs& settxpwrdb(uint val);
	uint gettxpwrdb();

	//CSR0[14:14]
	DS_txRegs& settxclk_16b32b_sel(uint val);
	uint gettxclk_16b32b_sel();

	//CSR0[13:13]
	DS_txRegs& settxclk_16b32b_pwrdb(uint val);
	uint gettxclk_16b32b_pwrdb();

	//CSR0[12:10]
	DS_txRegs& settx_clkregs_level(uint val);
	uint gettx_clkregs_level();

	//CSR0[9:5]
	DS_txRegs& settxfirpre2(uint val);
	uint gettxfirpre2();

	//CSR0[4:0]
	DS_txRegs& settxfirpre1(uint val);
	uint gettxfirpre1();

	//CSR1[15:10]
	DS_txRegs& settxfirmain(uint val);
	uint gettxfirmain();

	//CSR1[9:5]
	DS_txRegs& settxfirpost1(uint val);
	uint gettxfirpost1();

	//CSR1[4:0]
	DS_txRegs& settxfirpost2(uint val);
	uint gettxfirpost2();

	//CSR2[15:15]
	DS_txRegs& settxrstb(uint val);
	uint gettxrstb();

	//CSR2[14:12]
	DS_txRegs& settxdwidth(uint val);
	uint gettxdwidth();

	//CSR2[11:10]
	DS_txRegs& settxratemode(uint val);
	uint gettxratemode();

	//CSR2[9:9]
	DS_txRegs& settxbitorder(uint val);
	uint gettxbitorder();

	//CSR2[8:8]
	DS_txRegs& settxpolarity(uint val);
	uint gettxpolarity();

	//CSR2[7:6]
	DS_txRegs& settxclksel(uint val);
	uint gettxclksel();

	//CSR2[5:4]
	DS_txRegs& settxdatasel(uint val);
	uint gettxdatasel();

	//CSR2[3:3]
	DS_txRegs& settxdeadbandsel(uint val);
	uint gettxdeadbandsel();

	//CSR2[2:0]
	DS_txRegs& settxalignmode(uint val);
	uint gettxalignmode();

	//CSR3[15:15]
	DS_txRegs& setjitppmctrl(uint val);
	uint getjitppmctrl();

	//CSR3[14:12]
	DS_txRegs& setjitfreq(uint val);
	uint getjitfreq();

	//CSR3[11:8]
	DS_txRegs& setjitamp(uint val);
	uint getjitamp();

	//CSR3[7:7]
	DS_txRegs& setkfactor(uint val);
	uint getkfactor();

	//CSR3[6:6]
	DS_txRegs& seteco_idlemode_sel(uint val);
	uint geteco_idlemode_sel();

	//CSR3[5:5]
	DS_txRegs& seteco_tx_detectrx_sel(uint val);
	uint geteco_tx_detectrx_sel();

	//CSR3[4:0]
	DS_txRegs& setppmgen(uint val);
	uint getppmgen();

	//CSR4[15:8]
	DS_txRegs& settxphswrite(uint val);
	uint gettxphswrite();

	//CSR4[7:7]
	DS_txRegs& settx_tx2rxloopbacksel_eco(uint val);
	uint gettx_tx2rxloopbacksel_eco();

	//CSR4[4:4]
	DS_txRegs& setprbsgenen(uint val);
	uint getprbsgenen();

	//CSR4[3:0]
	DS_txRegs& setprbsgenpatsel(uint val);
	uint getprbsgenpatsel();

	//CSR5[15:0]
	DS_txRegs& settxcuspat1(uint val);
	uint gettxcuspat1();

	//CSR6[15:0]
	DS_txRegs& settxcuspat2(uint val);
	uint gettxcuspat2();

	//CSR7[15:0]
	DS_txRegs& settxcuspat3(uint val);
	uint gettxcuspat3();

	//CSR8[15:0]
	DS_txRegs& settxcuspat4(uint val);
	uint gettxcuspat4();

	//CSR9[15:0]
	DS_txRegs& settxcuspat5(uint val);
	uint gettxcuspat5();

	//CSR10[15:15]
	DS_txRegs& settxcppwrdb(uint val);
	uint gettxcppwrdb();

	//CSR10[14:14]
	DS_txRegs& settxclkregpwrdb(uint val);
	uint gettxclkregpwrdb();

	//CSR10[13:13]
	DS_txRegs& settxdrvregpwrdb(uint val);
	uint gettxdrvregpwrdb();

	//CSR10[12:12]
	DS_txRegs& settxdrvcalpwrdb(uint val);
	uint gettxdrvcalpwrdb();

	//CSR10[11:11]
	DS_txRegs& settxdrvslewpwrdb(uint val);
	uint gettxdrvslewpwrdb();

	//CSR10[10:10]
	DS_txRegs& settxdrvdatdepcomppwrdb(uint val);
	uint gettxdrvdatdepcomppwrdb();

	//CSR10[9:9]
	DS_txRegs& settxrxdetpwrdb(uint val);
	uint gettxrxdetpwrdb();

	//CSR10[8:8]
	DS_txRegs& settxdrvbypass(uint val);
	uint gettxdrvbypass();

	//CSR10[7:0]
	DS_txRegs& settxtappwrdb(uint val);
	uint gettxtappwrdb();

	//CSR11[15:8]
	DS_txRegs& settxregspare(uint val);
	uint gettxregspare();

	//CSR11[7:3]
	DS_txRegs& settxregpatdepsrc(uint val);
	uint gettxregpatdepsrc();

	//CSR11[2:0]
	DS_txRegs& settxregdrvlvl(uint val);
	uint gettxregdrvlvl();

	//CSR12[15:12]
	DS_txRegs& settxedgebleed(uint val);
	uint gettxedgebleed();

	//CSR12[11:8]
	DS_txRegs& settxpassbleed(uint val);
	uint gettxpassbleed();

	//CSR12[7:7]
	DS_txRegs& settxdrvswctrl(uint val);
	uint gettxdrvswctrl();

	//CSR12[6:6]
	DS_txRegs& settxdrvf1sel(uint val);
	uint gettxdrvf1sel();

	//CSR12[5:5]
	DS_txRegs& settxdrvf2sel(uint val);
	uint gettxdrvf2sel();

	//CSR12[4:0]
	DS_txRegs& settxdrvtapinv(uint val);
	uint gettxdrvtapinv();

	//CSR13[15:15]
	DS_txRegs& settxdrvcalhisel(uint val);
	uint gettxdrvcalhisel();

	//CSR13[14:14]
	DS_txRegs& settxdrvcallosel(uint val);
	uint gettxdrvcallosel();

	//CSR13[13:13]
	DS_txRegs& settxdrvcalpsel(uint val);
	uint gettxdrvcalpsel();

	//CSR13[12:12]
	DS_txRegs& settxdrvcalmsel(uint val);
	uint gettxdrvcalmsel();

	//CSR13[11:10]
	DS_txRegs& settxdrvotbpctrl(uint val);
	uint gettxdrvotbpctrl();

	//CSR13[9:8]
	DS_txRegs& settxdrvotbmctrl(uint val);
	uint gettxdrvotbmctrl();

	//CSR13[7:7]
	DS_txRegs& setdstxlowoffpwrdb(uint val);
	uint getdstxlowoffpwrdb();

	//CSR13[6:6]
	DS_txRegs& setdstxlowoffcal(uint val);
	uint getdstxlowoffcal();

	//CSR13[5:0]
	DS_txRegs& setdstxlowoffctrl(uint val);
	uint getdstxlowoffctrl();

	//CSR14[15:15]
	DS_txRegs& settxdrvcalstart(uint val);
	uint gettxdrvcalstart();

	//CSR14[14:14]
	uint getdstxlowoffout();

	//CSR14[13:13]
	DS_txRegs& settxdrvcaldir(uint val);
	uint gettxdrvcaldir();

	//CSR14[12:11]
	DS_txRegs& settxtopotbctrl(uint val);
	uint gettxtopotbctrl();

	//CSR14[10:8]
	DS_txRegs& settxdrvslew(uint val);
	uint gettxdrvslew();

	//CSR14[7:7]
	DS_txRegs& settxdrvregcalen(uint val);
	uint gettxdrvregcalen();

	//CSR14[6:6]
	DS_txRegs& settxdrvregslicetune(uint val);
	uint gettxdrvregslicetune();

	//CSR14[5:4]
	DS_txRegs& settxtermcalmode(uint val);
	uint gettxtermcalmode();

	//CSR15[15:15]
	DS_txRegs& settxdrvtesten(uint val);
	uint gettxdrvtesten();

	//CSR15[14:14]
	DS_txRegs& settxdrvtestin(uint val);
	uint gettxdrvtestin();

	//CSR15[13:11]
	DS_txRegs& settxdrvregatbctrl(uint val);
	uint gettxdrvregatbctrl();

	//CSR15[10:9]
	DS_txRegs& setdslowoffctrl(uint val);
	uint getdslowoffctrl();

	//CSR15[8:6]
	DS_txRegs& settxclkregatbctrl(uint val);
	uint gettxclkregatbctrl();

	//CSR15[5:4]
	DS_txRegs& settxdrvatbctrl(uint val);
	uint gettxdrvatbctrl();

	//CSR15[3:2]
	DS_txRegs& settxmastermiratbctrl(uint val);
	uint gettxmastermiratbctrl();

	//CSR15[1:0]
	DS_txRegs& settxtopatbctrl(uint val);
	uint gettxtopatbctrl();

	//CSR16[15:8]
	DS_txRegs& settxdrvsel1(uint val);
	uint gettxdrvsel1();

	//CSR16[7:0]
	DS_txRegs& setseg1ctrl23to16(uint val);
	uint getseg1ctrl23to16();

	//CSR17[15:0]
	DS_txRegs& setseg1ctrl15to0(uint val);
	uint getseg1ctrl15to0();

	//CSR18[15:8]
	DS_txRegs& settxdrvsel2(uint val);
	uint gettxdrvsel2();

	//CSR18[7:0]
	DS_txRegs& setseg2ctrl23to16(uint val);
	uint getseg2ctrl23to16();

	//CSR19[15:0]
	DS_txRegs& setseg2ctrl15to0(uint val);
	uint getseg2ctrl15to0();

	//CSR20[15:8]
	DS_txRegs& settxdrvsel3(uint val);
	uint gettxdrvsel3();

	//CSR20[7:0]
	DS_txRegs& setseg3ctrl23to16(uint val);
	uint getseg3ctrl23to16();

	//CSR21[15:0]
	DS_txRegs& setseg3ctrl15to0(uint val);
	uint getseg3ctrl15to0();

	//CSR22[15:8]
	DS_txRegs& settxdrvsel4(uint val);
	uint gettxdrvsel4();

	//CSR22[7:0]
	DS_txRegs& setseg4ctrl23to16(uint val);
	uint getseg4ctrl23to16();

	//CSR23[15:0]
	DS_txRegs& setseg4ctrl15to0(uint val);
	uint getseg4ctrl15to0();

	//CSR24[14:8]
	uint gettxphsval();

	//CSR24[7:4]
	uint getnmoscalstatus();

	//CSR24[3:0]
	uint getpmoscalstatus();

	//CSR25[15:8]
	DS_txRegs& settxspare(uint val);
	uint gettxspare();

	//CSR25[7:7]
	DS_txRegs& settx_idle_hiz_sw_crg(uint val);
	uint gettx_idle_hiz_sw_crg();

	//CSR25[6:6]
	DS_txRegs& settx_detectrx_sel(uint val);
	uint gettx_detectrx_sel();

	//CSR25[5:5]
	DS_txRegs& settx_tx2rxloopbacksel(uint val);
	uint gettx_tx2rxloopbacksel();

	//CSR25[4:4]
	DS_txRegs& settxdrv_open_en(uint val);
	uint gettxdrv_open_en();

	//CSR25[3:2]
	DS_txRegs& settxdigspare(uint val);
	uint gettxdigspare();

	//CSR25[1:1]
	DS_txRegs& settxdrvcaldndir(uint val);
	uint gettxdrvcaldndir();

	//CSR25[0:0]
	DS_txRegs& settxdrvcalupdir(uint val);
	uint gettxdrvcalupdir();

	//CSR26[15:15]
	uint gettxdrvcaldone();

	//CSR26[14:14]
	uint gettxtapmapdone();

	//CSR26[11:6]
	uint gettxdrvncaldn();

	//CSR26[5:0]
	uint gettxdrvncalup();

	//CSR27[14:14]
	DS_txRegs& settxcal_timer_stop(uint val);
	uint gettxcal_timer_stop();

	//CSR27[13:4]
	DS_txRegs& settxcal_timer_value(uint val);
	uint gettxcal_timer_value();

	//CSR27[3:3]
	DS_txRegs& settxcal_timer_div_en(uint val);
	uint gettxcal_timer_div_en();

	//CSR27[2:0]
	DS_txRegs& settxcal_timer_div_value(uint val);
	uint gettxcal_timer_div_value();

	//CSR28[15:11]
	uint gettx_training_firpost1();

	//CSR28[10:5]
	uint gettx_training_firmain();

	//CSR28[4:0]
	uint gettx_training_firpre1();

	//CSR29[13:8]
	uint gettx_local_fs();

	//CSR29[5:0]
	uint gettx_local_lf();

	//CSR30[14:14]
	DS_txRegs& setrxdet_timer_stop(uint val);
	uint getrxdet_timer_stop();

	//CSR30[13:4]
	DS_txRegs& setrxdet_init_timer_value(uint val);
	uint getrxdet_init_timer_value();

	//CSR30[2:0]
	DS_txRegs& setrxdet_init_timer_div_value(uint val);
	uint getrxdet_init_timer_div_value();

	//CSR31[13:4]
	DS_txRegs& setrxdet_charge_timer_value(uint val);
	uint getrxdet_charge_timer_value();

	//CSR31[2:0]
	DS_txRegs& setrxdet_charge_timer_div_value(uint val);
	uint getrxdet_charge_timer_div_value();

	//CSR32[14:14]
	uint gettx_rxdet_en_pin_mon();

	//CSR32[13:13]
	uint gettx_rxdet_ready();

	//CSR32[12:12]
	uint gettx_rxdet_out();

	//CSR32[11:11]
	uint gettx_rxdet_pwrdb();

	//CSR32[10:8]
	uint gettx_rxdet_mode();

	//CSR32[5:5]
	uint gettx_training_start_err();

	//CSR32[4:0]
	uint gettxdrv_tap_inv();

	//CSR33[15:15]
	uint gettxdrv_idle_en_pin_mon();

	//CSR33[14:14]
	DS_txRegs& settxdrv_idle_en(uint val);
	uint gettxdrv_idle_en();

	//CSR33[13:13]
	DS_txRegs& settxdrv_open_en_eco(uint val);
	uint gettxdrv_open_en_eco();

	//CSR33[11:11]
	DS_txRegs& settxdrv_idle_en_dly(uint val);
	uint gettxdrv_idle_en_dly();

	//CSR33[10:10]
	DS_txRegs& setpicodein_sel(uint val);
	uint getpicodein_sel();

	//CSR33[9:9]
	uint gettx_phase_align_done();

	//CSR33[8:8]
	DS_txRegs& settx_pa_status_clr(uint val);
	uint gettx_pa_status_clr();

	//CSR33[7:0]
	DS_txRegs& settx_phase_align_thr(uint val);
	uint gettx_phase_align_thr();

	//CSR34[15:15]
	DS_txRegs& settxdrv_open_en_p(uint val);
	uint gettxdrv_open_en_p();

	//CSR34[14:14]
	DS_txRegs& settxdrv_open_en_m(uint val);
	uint gettxdrv_open_en_m();

	//CSR34[13:13]
	DS_txRegs& settxdrv_idle_bypass(uint val);
	uint gettxdrv_idle_bypass();

	//CSR34[12:12]
	DS_txRegs& settx_wrate_sw_bypass(uint val);
	uint gettx_wrate_sw_bypass();

	//CSR34[11:11]
	DS_txRegs& settx_rxdet_en(uint val);
	uint gettx_rxdet_en();

	//CSR34[10:9]
	DS_txRegs& settx_rxdet_level(uint val);
	uint gettx_rxdet_level();

	//CSR34[8:6]
	DS_txRegs& settx_idle_dly_ana(uint val);
	uint gettx_idle_dly_ana();

	//CSR34[5:5]
	DS_txRegs& settxoclk_sel(uint val);
	uint gettxoclk_sel();

	//CSR34[4:4]
	DS_txRegs& settxdrv_map_sel(uint val);
	uint gettxdrv_map_sel();

	//CSR34[3:3]
	DS_txRegs& settxdrv_tapinv_sel(uint val);
	uint gettxdrv_tapinv_sel();

	//CSR34[2:2]
	DS_txRegs& setpcie_wrate_hsclk_sel(uint val);
	uint getpcie_wrate_hsclk_sel();

	//CSR34[1:0]
	DS_txRegs& settxdrv_ressel(uint val);
	uint gettxdrv_ressel();

	//CSR35[13:13]
	DS_txRegs& settxdrv_sliceboost_en(uint val);
	uint gettxdrv_sliceboost_en();

	//CSR35[12:12]
	DS_txRegs& setclkreg_selfbleed_pdb(uint val);
	uint getclkreg_selfbleed_pdb();

	//CSR35[11:8]
	DS_txRegs& setclkreg_selfbleed(uint val);
	uint getclkreg_selfbleed();

	//CSR35[7:4]
	DS_txRegs& setncaldn_offset(uint val);
	uint getncaldn_offset();

	//CSR35[3:0]
	DS_txRegs& setncalup_offset(uint val);
	uint getncalup_offset();

	//CSR48[15:15]
	DS_txRegs& setpcie_sas_sw_rstb(uint val);
	uint getpcie_sas_sw_rstb();

	//CSR48[14:14]
	DS_txRegs& setpcie_sas_pin_en(uint val);
	uint getpcie_sas_pin_en();

	//CSR48[13:12]
	DS_txRegs& setpma_mode(uint val);
	uint getpma_mode();

	//CSR48[11:11]
	DS_txRegs& setpstate_wrate_vld(uint val);
	uint getpstate_wrate_vld();

	//CSR48[10:8]
	DS_txRegs& setpcie_sas_power_state(uint val);
	uint getpcie_sas_power_state();

	//CSR48[6:4]
	DS_txRegs& setpcie_sas_data_rate(uint val);
	uint getpcie_sas_data_rate();

	//CSR48[3:3]
	DS_txRegs& setpcie_sas_rxtx_status_rdy(uint val);
	uint getpcie_sas_rxtx_status_rdy();

	//CSR48[2:0]
	DS_txRegs& setpcie_sas_data_width(uint val);
	uint getpcie_sas_data_width();

	//CSR49[15:15]
	DS_txRegs& setrxsigdet_pwrdnb_msk(uint val);
	uint getrxsigdet_pwrdnb_msk();

	//CSR49[14:14]
	DS_txRegs& settxrxdet_pwrdnb_msk(uint val);
	uint gettxrxdet_pwrdnb_msk();

	//CSR49[13:13]
	DS_txRegs& setrxpwrdnb_msk(uint val);
	uint getrxpwrdnb_msk();

	//CSR49[12:12]
	DS_txRegs& settxpwrdnb_msk(uint val);
	uint gettxpwrdnb_msk();

	//CSR49[11:11]
	DS_txRegs& setdsclkgen_pwrdnb_msk(uint val);
	uint getdsclkgen_pwrdnb_msk();

	//CSR49[10:10]
	DS_txRegs& setdsclk_idac_pwrdnb_msk(uint val);
	uint getdsclk_idac_pwrdnb_msk();

	//CSR49[9:9]
	DS_txRegs& setdsclk_vregdac_pwrdnb_msk(uint val);
	uint getdsclk_vregdac_pwrdnb_msk();

	//CSR49[8:8]
	DS_txRegs& setdsclk_vregl_pwrdnb_msk(uint val);
	uint getdsclk_vregl_pwrdnb_msk();

	//CSR49[6:6]
	DS_txRegs& setrx_sw_sigdet_rstb_msk(uint val);
	uint getrx_sw_sigdet_rstb_msk();

	//CSR49[5:5]
	DS_txRegs& setrx_sw_cdr_rstb_msk(uint val);
	uint getrx_sw_cdr_rstb_msk();

	//CSR49[4:4]
	DS_txRegs& setrx_sw_rstb_msk(uint val);
	uint getrx_sw_rstb_msk();

	//CSR49[3:3]
	DS_txRegs& setrx_loss_det_clk_en_msk(uint val);
	uint getrx_loss_det_clk_en_msk();

	//CSR49[2:2]
	DS_txRegs& setrx_sw_clk_en_msk(uint val);
	uint getrx_sw_clk_en_msk();

	//CSR49[1:1]
	DS_txRegs& settx_sw_clk_en_msk(uint val);
	uint gettx_sw_clk_en_msk();

	//CSR49[0:0]
	DS_txRegs& settx_sw_rstb_msk(uint val);
	uint gettx_sw_rstb_msk();

	//CSR50[15:12]
	DS_txRegs& setpstate_timer_div_value(uint val);
	uint getpstate_timer_div_value();

	//CSR50[9:0]
	DS_txRegs& setpstate_timer_value(uint val);
	uint getpstate_timer_value();

	//CSR51[15:12]
	DS_txRegs& setdsclk_timer_div_value(uint val);
	uint getdsclk_timer_div_value();

	//CSR51[11:4]
	DS_txRegs& setpcie_sas_spare(uint val);
	uint getpcie_sas_spare();

	//CSR51[3:0]
	DS_txRegs& setwrate_timer_div_value(uint val);
	uint getwrate_timer_div_value();

	//CSR52[13:0]
	DS_txRegs& setdsclk_timer_value(uint val);
	uint getdsclk_timer_value();

	//CSR53[13:0]
	DS_txRegs& setwrate_timer_value(uint val);
	uint getwrate_timer_value();

	//CSR54[15:15]
	uint gethis_alarm_pstate_code_err();

	//CSR54[14:14]
	uint gethis_alarm_pstate_sw_err();

	//CSR54[13:13]
	uint gethis_alarm_wrate_sw_err();

	//CSR54[12:12]
	uint gethis_alarm_pstate_wrate_err();

	//CSR54[11:11]
	uint gethis_alarm_one_sw_req_vio();

	//CSR54[10:10]
	uint gethis_alarm_sw_req_drop();

	//CSR54[9:9]
	uint getalarm_dsclk_calib_timeout();

	//CSR54[8:8]
	uint getalarm_wrate_txsw_timeout();

	//CSR54[7:7]
	uint getalarm_wrate_rxsw_timeout();

	//CSR54[6:6]
	uint getpstate_wrate_load_done();

	//CSR54[5:5]
	uint gethis_alarm_width_para_err();

	//CSR54[4:4]
	uint gethis_alarm_rate_para_err();

	//CSR55[10:8]
	uint getcurr_power_state();

	//CSR55[6:4]
	uint getnext_power_state();

	//CSR55[2:0]
	uint getpower_state_err_code();

	//CSR56[14:12]
	uint getcurr_data_rate();

	//CSR56[10:8]
	uint getnext_data_rate();

	//CSR56[6:4]
	uint getcurr_data_width();

	//CSR56[2:0]
	uint getnext_data_width();

	//CSR57[15:15]
	DS_txRegs& setdrvreg_selfbleed_pdb(uint val);
	uint getdrvreg_selfbleed_pdb();

	//CSR57[14:11]
	DS_txRegs& setdrvreg_selfbleed(uint val);
	uint getdrvreg_selfbleed();

	//CSR57[10:8]
	uint getpin_data_rate();

	//CSR57[6:4]
	uint getpin_data_width();

	//CSR57[2:0]
	uint getpin_power_state();

	//CSR58[15:14]
	uint getsw_glb_fsm_curr_st();

	//CSR58[10:8]
	uint getpstate_time_fsm_curr_st();

	//CSR58[7:7]
	uint getrxtx_status();

	//CSR58[6:4]
	uint getwrate_sw_fsm_curr_st();

	//CSR58[2:0]
	uint getpstate_fsm_curr_st();

	//CSR59[7:0]
	DS_txRegs& setds_dig_test_sel(uint val);
	uint getds_dig_test_sel();

	//CSR60[15:0]
	uint getpstate_wrate_if_status();

	//CSR61[15:0]
	uint getpstate_sw_status();

};

#endif // HILINKDSTXREGS_H_
