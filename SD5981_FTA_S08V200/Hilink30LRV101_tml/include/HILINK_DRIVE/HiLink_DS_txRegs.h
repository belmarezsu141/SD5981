#ifndef HILINKDSTXREGS_H_
#define HILINKDSTXREGS_H_

#include <HILINK_DRIVE/HiLink_Regs_Base.h>
#define DS_TX_CSR_NUM 39

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

	/// Transmit path power down control. Active low. This pin will gate other analog power down pins. 
	/// 0 = Power down all related TX circuitry and forces a power down values on TXTAPPWRDB[7:0].  
	/// 1 = Powers up all transmit circuitry in sequence.  
	/// New in v101:  Now used as a trigger to power up/down the Transmitter circuits
			const T_REG_INFO_EX& txpwrdb();	//CSR0[15:15]

	/// Enable control of cap-slices of Tx driver. For every bit,
	/// x000 = all cap slices disabled
	/// x111 = all cap slices enabled
	/// bit[3] is no connect
			const T_REG_INFO_EX& txdrvcapen();	//CSR0[13:10]

	/// The pre-cursor 2 of the TX driver FIR. Used for pre-emphasis control . A sign magnitude (binary) value.  [also see related register DS TX CSR11 TXTAPPWRDB before using any of the TXFIR**** registers below]
	/// bit[9]  -  polarity  of pre-cursor 2 of the TX driver FIR
	/// bit[8:5] -   magnitude of pre-cursor 2 of the Tx driver FIR
			const T_REG_INFO_EX& txfirpre2();	//CSR0[9:5]

	/// The pre-cursor 1 of the TX driver FIR. Used for pre-emphasis control. A sign magnitude (binary) value. 
	/// bit[4]  -  polarity  of pre-cursor 1 of the TX driver FIR
	/// bit[3:0] -   magnitude of pre-cursor 1 of the Tx driver FIR
			const T_REG_INFO_EX& txfirpre1();	//CSR0[4:0]

	/// The main cursor of the TX driver FIR. Used for pre-emphasis control. A binary  value.
			const T_REG_INFO_EX& txfirmain();	//CSR1[15:10]

	/// The  post-cursor 1 of the TX driver FIR. This value is added to TXFIRPOST1X to set post_cursor value.  Used for pre-emphasis control. A sign magnitude (binary) value.
	/// bit[9]  -  polarity  of post-cursor 1 of the TX driver FIR
	/// bit[8:5] -   magnitude of post-cursor 1 of the Tx driver FIR
			const T_REG_INFO_EX& txfirpost1();	//CSR1[9:5]

	/// The post_cursor 1 extension  of the TX driver FIR.    This value is added to TXFIRPOST1 to set post_cursor value. Used for pre-emphasis control. A sign magnitude  (binary) value.  
	/// bit[4]  -  polarity  of post-cursor 1x of the TX driver FIR
	/// bit[3:0] -   magnitude of post-cursor 1x of the Tx driver FIR
			const T_REG_INFO_EX& txfirpost1x();	//CSR1[4:0]

	/// Transmit digital circuitry reset. Active low.
	/// 0 = Reset TX digital logic.
	/// 1 = Normal operation.
			const T_REG_INFO_EX& txrstb();	//CSR2[15:15]

	/// TX data width select. [Refer to Table.3 in HiLink30_datasheet and related register TXRATEMODE]
	/// 00 = Normal Mode 
	/// Accepts 40 bits at Full-rate, using full rate clock   and sends each bit once
	/// Accepts 20 bits at Half-rate, using full rate clock  and sends each bit 2x
	/// Accepts 10 bits at Quarter-rate, using full rate clock  and sends each bit 4x
	/// Accepts 5 bits at Octal-rate, using full rate clock   and sends each bit 8x
	/// Accepts 3 bits at Hex-rate , using full rate clock  and sends each bit 16x
	/// 01 = 2X Mode   
	/// Accepts 40 bits at Half-rate, using Half-rate clk  and sends each bit once
	/// Accepts 20 bits at Quarter-rate, using Half-rate clk and sends each bit 2x
	/// Accepts 10 bits at Octal-rate, using Half-rate clk and sends each bit 4x
	/// Accepts 5 bits at Hex-rate, using Half-rate clk and sends each bit 8x
	/// 10 = 4X Mode
	/// Accepts 40 bits at Quarter-rate, using Quarter-rate clk and sends each bit once
	/// Accepts 20 bits at Octal-rate, using Quarter-rate clk and sends each bit 2x
	/// Accepts 10 bits at Hex-rate, using Quarter-rate clk and sends each bit 4x
	/// 11 = Reserved
			const T_REG_INFO_EX& txdwidth();	//CSR2[14:13]

	/// TX bit rate mode. [Refer to Table.3 in HiLink30_datasheet and related register TXDWIDTH]
	/// 000 = full-rate
	/// 001 = 1/2-rate
	/// 010 = 1/4-rate
	/// 011 = 1/8-rate
	/// 100   = 1/16-rate
	/// 101 to 111 = do not use
			const T_REG_INFO_EX& txratemode();	//CSR2[12:10]

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
	/// ;11 = Choose the clock derived from one of the clock spines. Note that when this selection is made, self-align mode cannot be used (i.e., TXALIGNMODE[2:0]=000 can't be used).
			const T_REG_INFO_EX& txclksel();	//CSR2[7:6]

	/// Select the parallel TX data to be sent.
	/// 00 = select core data (i.e., TXD).
	/// 01 = select RX parallel data (RX-TX parallel loop back). 
	/// 10 = select pattern for PRBS generation. 
	/// 11 = Reserved for future use
			const T_REG_INFO_EX& txdatasel();	//CSR2[5:4]

	/// TX alignment window select for the TX phase aligner.
	/// 0 = 4 UI  
	/// 1 = 8 UI  
	/// Note : The Numbers are given in 'full' rate UIs
			const T_REG_INFO_EX& txdeadbandsel();	//CSR2[3:3]

	/// TX phase align mode
	/// 000 = Self-align mode.
	/// 001 = Plesio-synchronous self align mode (Not supported in the current version)
	/// 010 = Copy mode where the RX phase code is copied(Not supported in current version)
	/// 011 = Freeze mode the TXPHSWRITE[7:0] is set manually
	/// 100 = Jitter generation for test mode
	/// 101 = Synchronous master mode (TXCLKSEL[1:0] must be set to '11')   - Refer to fig. 14 in the HiLink30_datasheet
	/// 11x = Reserved
			const T_REG_INFO_EX& txalignmode();	//CSR2[2:0]

	/// 0 = Normal feature
	/// 1 = Extended feature
			const T_REG_INFO_EX& jitppmctrl();	//CSR3[15:15]

	/// Set the sinusoidal jitter period (frequency), by setting the number frequency of one step change (or the number of wordclk necessary to have one step change).
	///            (normal/extended) - see JITPPMCTRL to select feature
	/// 000 = steady state/1 step per wordclk
	/// 001 = 1 step per 2 wordclk /1 step per 2 wordclk
	/// 010 = 1 step per 3 wordclk /1 step per 3 wordclk
	/// 011 = 1 step per 4 wordclk/1 step per 4  wordclk
	/// 100 = 1 step per 6 wordclk/1 step per 5 wordclk
	/// 101 = 1 step per 8 wordclk/1 step per 6 wordclk
	/// 110 = 1 step per 12 wordclk/1 step per 7 wordclk
	/// 111 = 1 step per 16 wordclk/1 step per 8 wordclk
	/// 
	/// At half-rate mode, numbers are doubled
	/// At quarter rate mode, numbers are multiplied by 4
	/// At Octal rate mode, numbers are multiplied by 8 
	/// At Hex rate mode, numbers are multiplied by 16
			const T_REG_INFO_EX& jitfreq();	//CSR3[14:12]

	/// Select peak-peak sinusoidal jitter amplitude by defining the total number of steps change before reversing the change direction
	///             (normal/extended) - see JITPPMCTRL to select feature
	/// 0000 = 12 phase steps/3 phase steps    
	/// 
	/// 0000 = 12  /3 times         1000 = 12/20 times
	/// 0001 = 16/4 times           1001 = 12/24 times
	/// 0010 = 24/5 times           1010 = 12/32 times
	/// 0011 = 32/6 times           1011 = 12/40 times
	/// 0100 = 48/8 times           1100 = 12/48 times
	/// 0101 = 64/10 times         1101 = 12/64 times
	/// 0110 = 96/12 times         1110 = 12/80 times
	/// 0111 = 128/16 times       1111 = 12/96 times
	/// 
	/// At half-rate mode, numbers are doubled
	/// At quarter rate mode, numbers are multiplied by 4
	/// At Octal rate mode, numbers are multiplied by 8 
	/// At Hex rate mode, numbers are multiplied by 16
			const T_REG_INFO_EX& jitamp();	//CSR3[11:8]

	/// Select the k value in calculating the jitter period.
	/// 0 =    k=0 , where JITAMP is changed by subtracting 1 from no. of phase steps before a change in direction 
	/// 1 =    k=1, where JITAMP is as defined
			const T_REG_INFO_EX& kfactor();	//CSR3[7:7]

	/// Sets Continuous txphasecode increments or decrements.   PPMGEN[4] is sign bit and defines the  phase interpolator direction where,  
	/// 0 =  positive direction rotation (phase increments)
	/// 1 =  negative direction (phase decrements)  
	/// 
	/// PPMGEN[3:0] defines the number of wordclk necessary to have one step change        
	///            (normal/extended) - see JITPPMCTRL to select feature
	/// 0000 = steady state/steady state
	/// 0001 = 1 step per 2 wordclk /1 step per 2 wordclk
	/// 0010 = 1 step per 3 wordclk /1 step per 3 wordclk
	/// 0011 = 1 step per 4 wordclk/1 step per 4  wordclk
	/// 0100 = 1 step per 6 wordclk/1 step per 5 wordclk
	/// 0101 = 1 step per 8 wordclk/1 step per 6 wordclk
	/// 0110 = 1 step per 12 wordclk/1 step per 10 wordclk
	/// 0111 = 1 step per 16 wordclk/1 step per 10 wordclk
	/// 1000 = steady state/1 step per 12 wordclk
	/// 1001 = steady state/1 step per 16 wordclk
	/// 1010 = steady state/1 step per 20 wordclk
	/// 1011 = steady state/1 step per 24 wordclk
	/// 1100 = steady state/1 step per 32 wordclk
	/// 1101 = steady state/1 step per 40 wordclk
	/// 1110 = steady state/1 step per 48 wordclk
	/// 1111 = steady state/1 step per 64 wordclk
	/// 
	/// At half-rate mode, numbers are doubled
	/// At quarter rate mode, numbers are multiplied by 4
	/// At Octal rate mode, numbers are multiplied by 8 
	/// At Hex rate mode, numbers are multiplied by 16
			const T_REG_INFO_EX& ppmgen();	//CSR3[4:0]

	/// TX phase interpolator control  (2's complement number).
			const T_REG_INFO_EX& txphswrite();	//CSR4[15:8]

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
	/// 1000 = Custom pattern ( Refer to TXCUSPAT* register to specify the custom pattern)
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

	/// TX PI skew correction: [7] reserved; [6:0] are 2's complement
	/// 3F: +63
	/// 00: 0
	/// 40:-64
			const T_REG_INFO_EX& txcpddlcal();	//CSR10[7:0]

	/// Tx driver regulator power down control. Active low.  [see also related register DS TX CSR12 TXDRVREGLVL, TXDRVREGDPMEN, TXDRVREGBLEEDB]
	/// 0 = power down.
	/// 1 = power up.
			const T_REG_INFO_EX& txdrvregpwrdb();	//CSR11[13:13]

	/// Tx driver calibration control. Active low.
	/// 0 = power down calibration circuits.
	/// 1 = power up calibration circuits.
			const T_REG_INFO_EX& txdrvcalpwrdb();	//CSR11[12:12]

	/// Tx FIR tap power down control. Active low.
	/// (Assignment has changed in v101)
	/// bit[0] =  Tx driver cluster 1 pre 1 tap  (0= power down; 1= power up)
	/// bit[1] =  Tx driver  cluster 0 pre 2 tap  (0= power down; 1= power up)
	/// bit[2] = Tx driver   cluster 2 post 1 tap (0= power down; 1= power up)
	/// bit[3] =  Tx driver   cluster 3 post 1x tap (0 = power down; 1= power up)
	/// bit[4] =  Tx driver  cluster 1 main tap (0 = power down; 1 = power up)
	/// bit[5] =  Tx driver  cluster 0 main tap (0 = power down; 1 = power up)
	/// bit[6] =  Tx driver  cluster 2 main tap (0 = power down; 1 = power up)
	/// bit[7] =  Tx driver  cluster 3 main tap (0 = power down; 1 = power up)
			const T_REG_INFO_EX& txtappwrdb();	//CSR11[7:0]

	/// Tx I/Q detector I-phase input swap control.
	/// 0 = Normal mode
	/// 1 = Swap i-phase and ib-phase
			const T_REG_INFO_EX& txcpdetswapi();	//CSR12[15:15]

	/// Tx I/Q detector Q-phase input swap control.
	/// 0 = Normal mode
	/// 1 = Swap q-phase and qb-phase
			const T_REG_INFO_EX& txcpdetswapq();	//CSR12[14:14]

	/// Not implemented in analog.
	/// May be repurposed for DCD detector operation.
			const T_REG_INFO_EX& txcpdetiqmode();	//CSR12[13:13]

	/// Tx I/Q detector powerdown control
	/// 0 = powerdown
	/// 1 = enabled
			const T_REG_INFO_EX& txcpdetiqpwrdb();	//CSR12[12:12]

	/// Tx driver regulator bleed current control.
	/// 0 = enable bleed current
	/// 1 = disable bleed current
			const T_REG_INFO_EX& txdrvregbleedb();	//CSR12[6:6]

	/// Tx driver/predriver regulator inrush current limit DPM trimming.
	/// 0 = select voltage reference for SS corner
	/// 1 = select voltage reference for TT/FF corner
			const T_REG_INFO_EX& txdrvregdpmen();	//CSR12[5:5]

	/// Voltage level control of Tx driver regulator.[see also related register fields TXDRVREGPWRDB and TXDRVREGBLEEDB]
	/// 00000 = Minimum voltage.
	/// 00001
	/// 00010
	/// ?.
	/// 10100 = voltage (default) 0.927V (TT)
	/// 11111 = Maximum voltage.
			const T_REG_INFO_EX& txdrvreglvl();	//CSR12[4:0]

	/// Tx output voltage swing control (Function behaviour only explicitly defined when FIR not in use)
	/// 4'b1111 = max swing (assumes 32 slices driving)
	/// 4'b0111 = 0.75x swing
	/// 4'b0011 = 0.50x swing
	/// 4'b0001 = 0.25x swing
	/// 4'b0000 = min swing (no output)
			const T_REG_INFO_EX& txdrvampctrl();	//CSR13[12:9]

	/// 0 to 1 transition =  start tap mapping FSM
			const T_REG_INFO_EX& txdrvswctrl();	//CSR13[7:7]

	/// Polarity control of FIR taps (MANUAL mode only -  ref to register TXTERMCALMODE. Also see related register DS TX CSR11 TXTAPPWRDB) . 
	/// 
	/// TXDRVTAPINV[0]= PRE1 tap polarity (0 = Positive ; 1 = negative )
	/// TXDRVTAPINV[1]= PRE2  tap polarity  (0 = Positive ; 1 = negative )
	/// TXDRVTAPINV[2]= POST1  tap polarity  (0 = Positive ; 1 = negative )
	/// TXDRVTAPINV[3]= POST1X  tap polarity  (0 = Positive ; 1 = negative )
	/// TXDRVTAPINV[4]= MAIN  tap polarity  (0 = Positive ; 1 = negative )
			const T_REG_INFO_EX& txdrvtapinv();	//CSR13[4:0]

	/// Tx driver P-side calibration current control. [also see related register DS TX CSR11 TXDRVCALPWRDB before using any of the TXDRVCAL**** registers below]
	/// 0 = Turn off P-side calibration current.
	/// 1 = Turn on P-side calibration current.
			const T_REG_INFO_EX& txdrvcalhisel();	//CSR14[15:15]

	/// Tx driver M-side calibration current control.
	/// 0 = Turn off M-side calibration current.
	/// 1 = Turn on M-side calibration current.
			const T_REG_INFO_EX& txdrvcallosel();	//CSR14[14:14]

	/// Tx driver calibration txo_p end seletion.
	/// 0 = disable
	/// 1 = Select txo_p end to calibrate
			const T_REG_INFO_EX& txdrvcalpsel();	//CSR14[13:13]

	/// Tx driver calibration txo_m end seletion.
	/// 0 = disable
	/// 1 = Select txo_m end to calibrate
			const T_REG_INFO_EX& txdrvcalmsel();	//CSR14[12:12]

	/// Tx driver otbp mux control. Selected signal will go to hv_txtop_otbm.
	/// 00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 = sense DRV  p (txo_p)
	/// 10 = sense DRV  m (txo_m)
	/// 11 = floating
			const T_REG_INFO_EX& txdrvotbpctrl();	//CSR14[11:10]

	/// Tx driver otbm mux control. Selected signal will go to hv_txtop_otbp.
	/// 00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 = select vref_high
	/// 10 = select vref_middle
	/// 11 = select vref_low
			const T_REG_INFO_EX& txdrvotbmctrl();	//CSR14[9:8]

	/// Tx top otb mux control. Select signal that go to hv_txtop_otbp/m.
	/// 00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 = selects tx drv otbp/otbm related signal (ie output of TXDRVOTBPCTRL or TXDRVOTBMCTRL mux above)
	/// 10 = select IQ de-skew sensing signal
	/// 11 = select txdrv_sensep/txdrv_sensem
			const T_REG_INFO_EX& txtopotbctrl();	//CSR14[7:6]

	/// New in v101: Used to simulate DS power sequence in tx_quiet mode for testing.  Should be 1'b0 during mission mode.
			const T_REG_INFO_EX& pwrsqtxquiet();	//CSR14[5:5]

	/// Status of tx_quiet pin
			const T_REG_INFO_EX& txquietstatus();	//CSR14[4:4]

	/// Defines the powerdown granularity of the TX circuitry when EEE tx quiet is asserted
	/// 1000 = most power savings
	/// 1100 = moderate power savings
	/// 1110 = least power savings
	/// others =  no power savings
			const T_REG_INFO_EX& txeeepwrdbsel();	//CSR14[3:0]

	/// TX driver calibration start control. Used only in automatic and semi-automatic modes. (see also related register DS TX CSR11 TXDRVCALPWRDB before selection)
	/// 0 = Do not start TX driver calibration
	/// 1 = Start TX driver calibration.  Self clear after calibration is done
			const T_REG_INFO_EX& txdrvcalstart();	//CSR15[15:15]

	/// Not used. This register is hardcoded to read '0'
			const T_REG_INFO_EX& dstxlowoffout();	//CSR15[14:14]

	/// Direction control for calibrating the lowoff comparator for both TX driver and TX pre driver
	/// 0 =The control code increases when the compare status is 0 and  the control code decrease when the compare status is 1
	/// 1 = The control code increases when the compare status is 1 and  the control code decrease when the compare status is 0
			const T_REG_INFO_EX& txdrvcaldir();	//CSR15[13:13]

	/// TX calibration mode
	/// 0 = Automatic calibration 
	/// 1 = Manual calibration
			const T_REG_INFO_EX& txcalmode();	//CSR15[11:11]

	/// TX Slice selection mode 
	/// 0 = Number of slices in pullup/pulldown state is controlled by the calibration FSM
	/// 1 = Number of slices in pullup/pulldown state is controlled by the TXDRVNCALUP[5:0]/TXDRVNCALDN[5:0] register fields
			const T_REG_INFO_EX& txslicemode();	//CSR15[10:10]

	/// Repurposed - Description Change
	/// (TX IQ offset value selection. 
	/// 0 = select from CSR 
	/// 1 = select from calibration FSM)
			const T_REG_INFO_EX& txiqofstmode();	//CSR15[9:9]

	/// TX IQ de-skew calibration bypass control
	/// 0 = normal
	/// 1 = bypass deskew calibration
			const T_REG_INFO_EX& txcaldeskewbp();	//CSR15[8:8]

	/// Bypass the driver regulator calibration
	/// 0 = normal
	/// 1 = bypass
			const T_REG_INFO_EX& txcaldrvregbp();	//CSR15[7:7]

	/// Bypass the pre-driver regulator calibration
	/// 0 = normal
	/// 1 = bypass
			const T_REG_INFO_EX& txcalpredrvregbp();	//CSR15[6:6]

	/// TX driver calibration and tap mapping mode control.
	/// 00 =   Auto mode controlled by FSM including driver calibration and tap mapping 
	/// 01 =  Semiautomatic mode, FIR coefficients are controlled by driver calibration FSM
	/// 10 =  Semiautomatic mode, FIR coefficients are controlled by tap mapping  FSM
	/// 11 =  Manual mode
			const T_REG_INFO_EX& txtermcalmode();	//CSR15[5:4]

	/// Not used
			const T_REG_INFO_EX& txotbrefsel();	//CSR15[3:2]

	/// Not used
			const T_REG_INFO_EX& txotbsel();	//CSR15[1:0]

	/// Bypass the P-Side PMOS termination calibration
	/// 0 = normal
	/// 1 = bypass
			const T_REG_INFO_EX& txcaldrvpmosbp();	//CSR16[15:15]

	/// Bypass the M-Side NMOS termination calibration
	///  0 = normal
	///  1 = bypass
			const T_REG_INFO_EX& txcaldrvnmosbp();	//CSR16[14:14]

	/// Tx driver regulator ATB control. Selected signal will go to hv_txtop_atb_out.
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = select vref
	/// 010 = select vlow 
	/// 011 = High impedance
	/// 100 = High impedance
	/// 101 = select vmid
	/// 110 = select txdrv 2/3 vreg sense voltage
	/// 111 = High impedance
			const T_REG_INFO_EX& txdrvregatbctrl();	//CSR16[13:11]

	/// Max transition setting for DS calibration
			const T_REG_INFO_EX& dscalmaxtrans();	//CSR16[10:7]

	/// Controls the TX-to-RX loopback stage 2 offset calibration direction
	/// 0 = increases when the compare status is 0, decreases when the compare status is 1
	/// 1 = increases when the compare status is 1, decreases when the compare status is 0
			const T_REG_INFO_EX& txcallpbkofst2dir();	//CSR16[6:6]

	/// Controls the TX-to-RX loopback stage 1 offset calibration direction
	/// 0 =  increases when the compare status is 0, decreases when the compare status is 1
	/// 1 =  increases when the compare status is 1, decreases when the compare status is 0
			const T_REG_INFO_EX& txcallpbkofst1dir();	//CSR16[5:5]

	/// Bypass the TX-to-RX loopback stage 2 offset calibration
	/// 0 = normal
	/// 1 = bypas
			const T_REG_INFO_EX& txcallpbkofst2bp();	//CSR16[4:4]

	/// Bypass the TX-to-RX loopback stage 1 offset calibration
	/// 0 = normal
	/// 1 = bypass
			const T_REG_INFO_EX& txcallpbkofst1bp();	//CSR16[3:3]

	/// Not used (see TXDRVCALDIR)
			const T_REG_INFO_EX& txpredrvcaldir();	//CSR16[2:2]

	/// Tx top ATB control. Selected signal will go to hv_txtop_atb_out.
	/// 00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 =  select TX regulator ATB bus
	/// 10 = select txpredrv 2/3 vreg sense voltage
	/// 11 = select txdrv 2/3 vreg sense voltage
			const T_REG_INFO_EX& txtopatbctrl();	//CSR16[1:0]

	/// Tx driver slicers output  data control for each of the 8 slices in cluster 0  (MANUAL mode only -  ref to register TXTERMCALMODE. Also see related register DS TX CSR11 TXTAPPWRDB ) . 
	/// For every bit,
	/// 0 = main tap
	/// ;1 = Other tap ( PRE2 - refer to FIR mapping for details)
			const T_REG_INFO_EX& txdrvsel1();	//CSR17[15:8]

	/// Driver cluster 0 slice based control: (MAIN or PRE2 decided by TXDRVSEL1 above)  
	/// bits [7:5]      = SEGCTRL1[23:21] -  slice 8 output control 
	/// bits [4:2]      = SEGCTRL1[20:18]  - slice 7 output control 
	/// bits [1:0]      = SEGCTRL1[17:16]  - upper bits of slice 6 output control   (also see DS TX CSR18 SEG1CTRL15TO0)
	/// 
	/// For each slice:
	/// 000 = code to set slice Output Open-Open       
	/// 001 = code to set slice Output Drive-Open
	/// 010 = code to set slice Output Short-Open       
	/// 011 = code to set slice Output Drive-Drive
	/// 100 = code to set slice Output Open-Drive        
	/// 101 = code to set slice Output Open-Short
	/// 110/111 = code to set slice Output Open-Open
			const T_REG_INFO_EX& seg1ctrl23to16();	//CSR17[7:0]

	/// Driver cluster 0 slice based control: (MAIN or PRE1 decided by TXDRVSEL1 above)  
	/// bit [15]         = SEGCTRL1[15]  - lower bit of slice 6 output control (also see DS TX CSR17 SEG1CTRL23TO16)
	/// bits [14:12]   = SEGCTRL1[14:12]  - slice 5 output control
	/// bits [11:9]     = SEGCTRL1[11:9] - slice 4 output control
	/// bits [8:6]       = SEGCTRL1[8:6] - slice 3 output control 
	/// bits [5:3]       = SEGCTRL1[5:3] - slice 2 output control
	/// bits [2:0]       = SEGCTRL1[2:0] - slice 1 output control
	/// 
	/// For each slice:
	/// 000 = code to set slice Output Open-Open       
	/// 001 = code to set slice Output Drive-Open
	/// 010 = code to set slice Output Short-Open       
	/// 011 = code to set slice Output Drive-Drive
	/// 100 = code to set slice Output Open-Drive        
	/// 101 = code to set slice Output Open-Short
	/// 110/111 = code to set slice Output Open-Open
			const T_REG_INFO_EX& seg1ctrl15to0();	//CSR18[15:0]

	/// Tx driver slicers output data control for each of the 8 slices in cluster 1.
	/// For every bit,
	/// 0 = main tap
	/// ;1 = other tap (PRE1- refer to FIR mapping for details).
			const T_REG_INFO_EX& txdrvsel2();	//CSR19[15:8]

	/// Driver cluster 1 slice based control: (MAIN or PRE1 decided by TXDRVSEL2 above)
	/// bits [7:5]      = SEGCTRL2[23:21] - slice 8 output control
	/// bits [4:2]      = SEGCTRL2[20:18] - slice 7 output control
	/// bits [1:0]      = SEGCTRL2[17:16]  - upper bits of slice 6 output control (also see DS TX CSR20 SEG2CTRL15TO0)
	/// 
	/// For each slice:
	/// 000 = code to set slice Output Open-Open       
	/// 001 = code to set slice Output Drive-Open
	/// 010 = code to set slice Output Short-Open       
	/// 011 = code to set slice Output Drive-Drive
	/// 100 = code to set slice Output Open-Drive        
	/// 101 = code to set slice Output Open-Short
	/// 110/111 = code to set slice Output Open-Open
			const T_REG_INFO_EX& seg2ctrl23to16();	//CSR19[7:0]

	/// Driver cluster 1 slice based control: (MAIN or PRE1 decided by TXDRVSEL2 above))
	/// bit [15]         = SEGCTRL2[15] - lower bit of slice 6 output control (also see DS TX CSR19 SEG2CTRL23TO16)
	/// bits [14:12]   = SEGCTRL2[14:12] - slice 5 output control
	/// bits [11:9]     = SEGCTRL2[11:9]  - slice 4 output control
	/// bits [8:6]       = SEGCTRL2[8:6] - slice 3 output control
	/// bits [5:3]       = SEGCTRL2[5:3] - slice 2 output control 
	/// bits [2:0]       = SEGCTRL2[2:0] - slice 1 output control
	/// 
	/// For each slice:
	/// 000 = code to set slice Output Open-Open       
	/// 001 = code to set slice Output Drive-Open
	/// 010 = code to set slice Output Short-Open       
	/// 011 = code to set slice Output Drive-Drive
	/// 100 = code to set slice Output Open-Drive        
	/// 101 = code to set slice Output Open-Short
	/// 110/111 = code to set slice Output Open-Open
			const T_REG_INFO_EX& seg2ctrl15to0();	//CSR20[15:0]

	/// Tx driver slicers output  control for each of the 8 slices in cluster 2. For every bit,
	/// 0 = main tap
	/// ;1 = other tap (POST1 - refer to FIR mapping for details).
			const T_REG_INFO_EX& txdrvsel3();	//CSR21[15:8]

	/// Driver cluster 2 slice based control: ( MAIN or POST1 decided by TXDRVSEL3 above)
	/// bits [7:5]      = SEGCTRL3[23:21] - slice 8 output control
	/// bits[4:2]      = SEGCTRL3[20:18] - slice 7 output control
	/// bits[1:0]      = SEGCTRL3[17:16] - upper bits of slice 6 output control (also see DS TX CSR22 SEG3CTRL15TO0)
	/// 
	/// For each slice:
	/// 000 = code to set slice Output Open-Open       
	/// 001 = code to set slice Output Drive-Open
	/// 010 = code to set slice Output Short-Open       
	/// 011 = code to set slice Output Drive-Drive
	/// 100 = code to set slice Output Open-Drive        
	/// 101 = code to set slice Output Open-Short
	/// 110/111 = code to set slice Output Open-Open
			const T_REG_INFO_EX& seg3ctrl23to16();	//CSR21[7:0]

	/// Driver cluster 2 slice based control: ( MAIN or POST1 decided by TXDRVSEL3 above)
	/// bit [15]         = SEGCTRL3[15] - lower bit of slice 6 output control (also see DS TX CSR21 SEG3CTRL23TO16)
	/// bits [14:12]   = SEGCTRL3[14:12] - slice 5 output control
	/// bits [11:9]     = SEGCTRL3[11:9] -slice 4 output control
	/// bits [8:6]       = SEGCTRL3[8:6] - slice 3 output control
	/// bits [5:3]       = SEGCTRL3[5:3] - slice 2 output control
	/// bits [2:0]       = SEGCTRL3[2:0] - slice 1 output control
	/// 
	/// For each slice:
	/// 000 = code to set slice Output Open-Open       
	/// 001 = code to set slice Output Drive-Open
	/// 010 = code to set slice Output Short-Open       
	/// 011 = code to set slice Output Drive-Drive
	/// 100 = code to set slice Output Open-Drive        
	/// 101 = code to set slice Output Open-Short
	/// 110/111 = code to set slice Output Open-Open
			const T_REG_INFO_EX& seg3ctrl15to0();	//CSR22[15:0]

	/// Tx driver slicers output data control for each of 8 slice in cluster 3. For every bit,
	/// 0 = main tap
	/// ;1 = other tap (POST1X - refer to FIR mapping for details).
			const T_REG_INFO_EX& txdrvsel4();	//CSR23[15:8]

	/// Driver cluster 3 slice based control: (MAIN or POST1X decided by TXDRVSEL4 above)
	/// bits [7:5]      = SEGCTRL4[23:21] -  slice 8 output control 
	/// bits [4:2]      = SEGCTRL4[20:18] - slice 7 output control
	/// bits [1:0]      = SEGCTRL4[17:16] - upper bits of slice 6 output control  (also see DS TX CSR24 SEG4CTRL15TO0)
	/// 
	/// For each slice:
	/// 000 = code to set slice Output Open-Open       
	/// 001 = code to set slice Output Drive-Open
	/// 010 = code to set slice Output Short-Open       
	/// 011 = code to set slice Output Drive-Drive
	/// 100 = code to set slice Output Open-Drive        
	/// 101 = code to set slice Output Open-Short
	/// 110/111 = code to set slice Output Open-Open
			const T_REG_INFO_EX& seg4ctrl23to16();	//CSR23[7:0]

	/// Driver cluster 3 slice based control: (MAIN or POST1X decided by TXDRVSEL4 above)
	/// bit [15]         = SEGCTRL4[15] - lower bit of slice 6 output control (also see DS TX CSR23 SEG4CTRL23TO16)
	/// bits [14:12]   = SEGCTRL4[14:12] - slice 5 output control
	/// bits [11:9]     = SEGCTRL4[11:9] - slice 4 output control
	/// bits [8:6]       = SEGCTRL4[8:6] - slice 3 output control
	/// bits [5:3]       = SEGCTRL4[5:3] - slice 2 output control
	/// bits [2:0]       = SEGCTRL4[2:0] - slice 1 output control
	/// 
	/// For each slice:
	/// 000 = code to set slice Output Open-Open       
	/// 001 = code to set slice Output Drive-Open
	/// 010 = code to set slice Output Short-Open       
	/// 011 = code to set slice Output Drive-Drive
	/// 100 = code to set slice Output Open-Drive        
	/// 101 = code to set slice Output Open-Short
	/// 110/111 = code to set slice Output Open-Open
			const T_REG_INFO_EX& seg4ctrl15to0();	//CSR24[15:0]

	/// This register contains the present binary phase value of the TX phase interpolator.
			const T_REG_INFO_EX& txphsval();	//CSR25[14:8]

	/// Number of nmos calibration cells.
			const T_REG_INFO_EX& nmoscalconf();	//CSR25[7:4]

	/// Number of pmos calibration cells.
			const T_REG_INFO_EX& pmoscalconf();	//CSR25[3:0]

	/// Tx spare control bits.
			const T_REG_INFO_EX& txspare();	//CSR26[15:8]

	/// spare register bits
			const T_REG_INFO_EX& txdigspare();	//CSR26[7:2]

	/// Direction control for TX driver down side calibration.
	/// 0  =  The control code increases when the compare status is 0 and  the control code decrease when the compare status is 1
	/// 1  =  The control code increases when the compare status is 1 and  the control code decrease when the compare status is 0
			const T_REG_INFO_EX& txdrvcaldndir();	//CSR26[1:1]

	/// Direction control for TX driver up side calibration.
	/// 0  =  The control code increases when the compare status is 0 and  the control code decrease when the compare status is 1
	/// 1  =  The control code increases when the compare status is 1 and  the control code decrease when the compare status is 0
			const T_REG_INFO_EX& txdrvcalupdir();	//CSR26[0:0]

	/// 0 = TX Driver calibration is still in progress
	/// 1 = TX Driver calibration has completed
	/// (This may be redundant since TXDRVCALSTART is now self clear after calibration is done)
			const T_REG_INFO_EX& txdrvcaldone();	//CSR27[15:15]

	/// 0 = TX tap mapping is not done
	/// 1 = TX tap mapping is done
			const T_REG_INFO_EX& txtapmapdone();	//CSR27[14:14]

	/// Number of calibrated TX slices in pull-down state
			const T_REG_INFO_EX& txdrvncaldn();	//CSR27[11:6]

	/// Number of calibrated TX slices in pull-up state
			const T_REG_INFO_EX& txdrvncalup();	//CSR27[5:0]

	/// tx iq deskew value for swap_i=0 and swap_q=0
			const T_REG_INFO_EX& txiqofstff1();	//CSR28[13:8]

	/// tx iq deskew value for swap_i=1 and swap_q=0
			const T_REG_INFO_EX& txiqofstff2();	//CSR28[5:0]

	/// tx iq deskew value for swap_i=0 and swap_q=1
			const T_REG_INFO_EX& txiqofstff3();	//CSR29[13:8]

	/// iq deskew average value(rounding) equal to TXIQOFSTFF1+TXIQOFSTFF2+TXIQOFSTFF3/3.
			const T_REG_INFO_EX& txiqofstffavg();	//CSR29[5:0]

	/// Set Comparator reference voltage selection for tx predriver regulator calibration:
	/// Calib Target (mV)= 600 * (1+txclkregcalrefsel/64)
	/// Note: TXPREDRVREGVREFRNG[1:0] must be correspondingly set to a range which supports the calibration target value
			const T_REG_INFO_EX& txclkregcalrefsel();	//CSR30[13:8]

	/// Set Comparator reference voltage selection for tx driver regulator calibration:
	/// Calib Target (mV)= 600 * (1+txdrvregcalrefsel/64)
	/// Note: TXDRVREGVREFRNG[1:0] must be correspondingly set to a range which supports the calibration target value
			const T_REG_INFO_EX& txdrvregcalrefsel();	//CSR30[5:0]

	/// Configuration of timer for waiting, which is the cycles of reference clock.  Timer value = (2powTXCALTIMERVALUE) -1 , where TXCALTIMERVALUE =0 to 22.
			const T_REG_INFO_EX& txcaltimervalue();	//CSR31[14:5]

	/// Not used
			const T_REG_INFO_EX& txcaltimerdivvalue();	//CSR31[4:2]

	/// Not used
			const T_REG_INFO_EX& txcaltimerdiven();	//CSR31[1:1]

	/// Stop timer, for debugging.
	/// 0 = normal
	/// 1 = stop the timer
			const T_REG_INFO_EX& txcaltimerstop();	//CSR31[0:0]

	/// reference range select for txdrv regulator
	/// 00 =   vref between 750mV  and  850mV
	/// 01 =  vref  between 851mV and 925mV
	/// 10 =  vref between 926mV and 985mV
	/// 11 =  vref between 986mV and 1050mV
			const T_REG_INFO_EX& txdrvregvrefrng();	//CSR32[15:14]

	/// reference range select for txpredrv regulator
	/// 00 =   vref between 750mV  and  850mV
	/// 01 =  vref  between 851mV and 925mV
	/// 10 =  vref between 926mV and 985mV
	/// 11 =  vref between 986mV and 1050mV
			const T_REG_INFO_EX& txpredrvregvrefrng();	//CSR32[13:12]

	/// Voltage level control of Tx predriver regulator. [ also refer to related register TXPREDRVREGPWRDB]
	/// 00000: Minimum voltage.
	/// 00001
	/// 00010
	/// .
	/// 10100 = voltage (default) 0.927 (TT)
	/// ��...
	/// 11111: Maximum voltage.
			const T_REG_INFO_EX& txpredrvreglvl();	//CSR32[11:7]

	/// TX driver regulator inrush current limit. Active low.
	/// 0 =  regulator inrush current limit  mode
	/// 1 =  regulator mission mode
			const T_REG_INFO_EX& txdrvreginrushpwrdb();	//CSR32[6:6]

	/// TX predriver regulator inrush current limit. Active low.
	/// 0 =  regulator inrush current limit  mode
	/// 1 =  regulator mission mode
			const T_REG_INFO_EX& txpredrvreginrushpwrdb();	//CSR32[5:5]

	/// Tx predriver regulator power down control. Active low.
	/// 0 =  power down.
	/// 1 =  power up.
			const T_REG_INFO_EX& txpredrvregpwrdb();	//CSR32[4:4]

	/// Tx predriver regulator ATB control.  
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  select vref
	/// 010 =  select low bias
	/// 011 =  High Impedance
	/// 100 =  High Impedance
	/// 101 =  select vmid
	/// 110 =  select txpredrv 2/3 vreg sense voltage
	/// 111 =  High Impedance
			const T_REG_INFO_EX& txpredrvregatbctrl();	//CSR32[3:1]

	/// TX bit error injection enable.
	/// 0 =  Disable; 1 =  Enable
			const T_REG_INFO_EX& txerrinjen();	//CSR33[15:15]

	/// TX bit error injection mode
	/// 0 =  Single shot mode; 1 =  continuous mode
			const T_REG_INFO_EX& txerrinjmode();	//CSR33[14:14]

	/// TX bit error injection pattern selection
	/// 00 =  Type 1 Inject error pattern specified by TXERRINJCTRL[15:0].
	/// 01 =  Type 2 Inject consecutive errors specified by TXERRINJCTRL[15:0] (max. 255).
	/// 10 =  Reserved
	/// 11 =  Reserved
			const T_REG_INFO_EX& txerrinjpttn();	//CSR33[13:12]

	/// TX bit error injection start. In single shot mode, setting this bit to 1 will cause the error pattern specified by TXERRINJPTTN[1:0] to be injected once. Self clear upon completion. In continuous mode, setting this bit to 1 will cause the error pattern specified by TXERRINJPTTN[1 = 0] to be injected continuously until this bit is set to 0. Not self clear in continuous mode.
	/// 0 =  Stop; 1 =  Start.
			const T_REG_INFO_EX& txerrinjstart();	//CSR33[5:5]

	/// TX bit error injection interval (N) for continuous mode. The error pattern specified by TXERRINJPTTN[1:0] is injected every 2powN word clock cycles.
			const T_REG_INFO_EX& txerrinjintvl();	//CSR33[4:0]

	/// TX bit error injection control. 
	/// 
	/// If the error pattern is Type I, the actual error pattern is specified by TXERRINJCTRL[15:0] (0=no error, 1=error); 
	/// 
	/// If the error pattern is Type 2, TXERRINJCTRL[7:0] gives the number of consecutive errors to be injected (max 255); Bits[15:8] are ignored.
			const T_REG_INFO_EX& txerrinjctrl();	//CSR34[15:0]

	/// set Tx to Rx serial loopback in calibration mode.
	/// 0 = Disable calibration Tx to Rx serial loopback (mission mode)
	/// 1 = configure Tx to Rx serial loopback path for DC calibration
			const T_REG_INFO_EX& txrxserlpbkcalen();	//CSR35[15:15]

	/// Offset calibration selection for TX to RX serial loopback. 
	/// 00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 = Select Tx2Rx serial loopback stage 1 output
	/// 10 = Select Tx2Rx serial loopback stage 2 output
			const T_REG_INFO_EX& txrxserlpbkotbsel();	//CSR35[13:12]

	/// TX to RX serial loopback enable.
	/// 0 = Normal operation. Receiver in mission mode. Loopback disabled
	/// 1 = High speed TX to RX loopback is enabled (RX input is ignored)
			const T_REG_INFO_EX& txrxserlpbken();	//CSR35[11:11]

	/// Repurposed control pin
	/// Allow for independent control of CTLE loopback MUX when loopback is not enabled
	/// 0 = loopback mux controlled by TXRXSERLPBKEN
	/// 1 = enable loopback mux
			const T_REG_INFO_EX& txrxserlpbkgainsel();	//CSR35[10:10]

	/// Select which TX2RX serial loopback path to use
	/// 0: pre-driver TX loopback path
	/// 1: driver bump TX loopback path  (PROPER OPERATION REQUIRES DRIVER TERMINATION!)
			const T_REG_INFO_EX& txrxserlpbksel();	//CSR35[9:9]

	/// Not implemented in Analog
			const T_REG_INFO_EX& txrxserlpbksupatbsel();	//CSR35[8:7]

	/// ATB selection for TX to RX serial loopback.
	/// 00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 = Select otbp output
	/// 10 = Select otbm output
	/// 11 = Select vss
			const T_REG_INFO_EX& txrxserlpbkatbctrl();	//CSR35[6:5]

	/// Automatic resistor DPM based bandwidth adjust for loopback.
	/// This field should be user programmed based on die/macro resistor DPM measurement
	/// DPM_Setting =  Res Corner - (resulting gain code in gray selected)
	/// 00 =  min res corner - (000)
	/// 01 = typ res corner - (010)
	/// 10 =  max res corner -  (110)
			const T_REG_INFO_EX& txrxserlpbkdpm();	//CSR35[4:3]

	/// Enable Loopback DPM based bandwidth adjustment by stage (Recommend default override to disable this feature.)
	/// x1 =  stage 1 gain controlled automatically based on TXRXSERLPBKDPM
	/// x0 =  stage 1 gain controlled directly by TXRXSERLPBKGN1
	/// 1x =  stage 2 gain controlled automatically based on TXRXSERLPBKDPM
	/// 0x =  stage 2 gain controlled directly by TXRXSERLPBKGN2
			const T_REG_INFO_EX& txrxserlpbkdpmen();	//CSR35[2:1]

	/// TX to RX serial loopback stage 1 gain. 
	/// 000 = Minimum gain
	/// 001
	/// ..
	/// 111 = Maximum gain
			const T_REG_INFO_EX& txrxserlpbkgn1();	//CSR36[12:10]

	/// TX to RX serial loopback stage 2 gain . 
	/// 000 = Minimum gain
	/// 001 
	/// ..
	/// 111 = Maximum gain
			const T_REG_INFO_EX& txrxserlpbkgn2();	//CSR36[7:5]

	/// TX to RX serial loopback stage 3 gain. 
	/// 000 = Minimum gain (default)
	/// 001
	/// 010
	/// ..
	/// 111 = Maximum gain
			const T_REG_INFO_EX& txrxserlpbkgn3();	//CSR36[2:0]

	/// Offset control for TX to RX serial loopback stage 1. Used for manual offset calibration. 
	/// bit[4]: sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset,
	/// 0000 = Minimum offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum offset
			const T_REG_INFO_EX& txrxserlpbkofst1();	//CSR37[14:10]

	/// Offset control for TX to RX serial loopback stage 2. Used for manual offset calibration. 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset ,
	/// 0000 = Minimum offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum offset
			const T_REG_INFO_EX& txrxserlpbkofst2();	//CSR37[9:5]

	/// Not implemented in Analog.
			const T_REG_INFO_EX& txrxserlpbkofst3();	//CSR37[4:0]

	/// NOT IMPLEMENTED IN ANALOG
			const T_REG_INFO_EX& txrxserlpbkltrim1();	//CSR38[11:8]

	/// NOT IMPLEMENTED IN ANALOG
			const T_REG_INFO_EX& txrxserlpbkltrim2();	//CSR38[7:4]
			bool get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos);
	};
public:
	_REG_INFO REG_INFO;

	uint csr[DS_TX_CSR_NUM];


	//CSR0[15:15]
	DS_txRegs& settxpwrdb(uint val);
	uint gettxpwrdb();

	//CSR0[13:10]
	DS_txRegs& settxdrvcapen(uint val);
	uint gettxdrvcapen();

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
	DS_txRegs& settxfirpost1x(uint val);
	uint gettxfirpost1x();

	//CSR2[15:15]
	DS_txRegs& settxrstb(uint val);
	uint gettxrstb();

	//CSR2[14:13]
	DS_txRegs& settxdwidth(uint val);
	uint gettxdwidth();

	//CSR2[12:10]
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

	//CSR3[4:0]
	DS_txRegs& setppmgen(uint val);
	uint getppmgen();

	//CSR4[15:8]
	DS_txRegs& settxphswrite(uint val);
	uint gettxphswrite();

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

	//CSR10[7:0]
	DS_txRegs& settxcpddlcal(uint val);
	uint gettxcpddlcal();

	//CSR11[13:13]
	DS_txRegs& settxdrvregpwrdb(uint val);
	uint gettxdrvregpwrdb();

	//CSR11[12:12]
	DS_txRegs& settxdrvcalpwrdb(uint val);
	uint gettxdrvcalpwrdb();

	//CSR11[7:0]
	DS_txRegs& settxtappwrdb(uint val);
	uint gettxtappwrdb();

	//CSR12[15:15]
	DS_txRegs& settxcpdetswapi(uint val);
	uint gettxcpdetswapi();

	//CSR12[14:14]
	DS_txRegs& settxcpdetswapq(uint val);
	uint gettxcpdetswapq();

	//CSR12[13:13]
	DS_txRegs& settxcpdetiqmode(uint val);
	uint gettxcpdetiqmode();

	//CSR12[12:12]
	DS_txRegs& settxcpdetiqpwrdb(uint val);
	uint gettxcpdetiqpwrdb();

	//CSR12[6:6]
	DS_txRegs& settxdrvregbleedb(uint val);
	uint gettxdrvregbleedb();

	//CSR12[5:5]
	DS_txRegs& settxdrvregdpmen(uint val);
	uint gettxdrvregdpmen();

	//CSR12[4:0]
	DS_txRegs& settxdrvreglvl(uint val);
	uint gettxdrvreglvl();

	//CSR13[12:9]
	DS_txRegs& settxdrvampctrl(uint val);
	uint gettxdrvampctrl();

	//CSR13[7:7]
	DS_txRegs& settxdrvswctrl(uint val);
	uint gettxdrvswctrl();

	//CSR13[4:0]
	DS_txRegs& settxdrvtapinv(uint val);
	uint gettxdrvtapinv();

	//CSR14[15:15]
	DS_txRegs& settxdrvcalhisel(uint val);
	uint gettxdrvcalhisel();

	//CSR14[14:14]
	DS_txRegs& settxdrvcallosel(uint val);
	uint gettxdrvcallosel();

	//CSR14[13:13]
	DS_txRegs& settxdrvcalpsel(uint val);
	uint gettxdrvcalpsel();

	//CSR14[12:12]
	DS_txRegs& settxdrvcalmsel(uint val);
	uint gettxdrvcalmsel();

	//CSR14[11:10]
	DS_txRegs& settxdrvotbpctrl(uint val);
	uint gettxdrvotbpctrl();

	//CSR14[9:8]
	DS_txRegs& settxdrvotbmctrl(uint val);
	uint gettxdrvotbmctrl();

	//CSR14[7:6]
	DS_txRegs& settxtopotbctrl(uint val);
	uint gettxtopotbctrl();

	//CSR14[5:5]
	DS_txRegs& setpwrsqtxquiet(uint val);
	uint getpwrsqtxquiet();

	//CSR14[4:4]
	uint gettxquietstatus();

	//CSR14[3:0]
	DS_txRegs& settxeeepwrdbsel(uint val);
	uint gettxeeepwrdbsel();

	//CSR15[15:15]
	DS_txRegs& settxdrvcalstart(uint val);
	uint gettxdrvcalstart();

	//CSR15[14:14]
	uint getdstxlowoffout();

	//CSR15[13:13]
	DS_txRegs& settxdrvcaldir(uint val);
	uint gettxdrvcaldir();

	//CSR15[11:11]
	DS_txRegs& settxcalmode(uint val);
	uint gettxcalmode();

	//CSR15[10:10]
	DS_txRegs& settxslicemode(uint val);
	uint gettxslicemode();

	//CSR15[9:9]
	DS_txRegs& settxiqofstmode(uint val);
	uint gettxiqofstmode();

	//CSR15[8:8]
	DS_txRegs& settxcaldeskewbp(uint val);
	uint gettxcaldeskewbp();

	//CSR15[7:7]
	DS_txRegs& settxcaldrvregbp(uint val);
	uint gettxcaldrvregbp();

	//CSR15[6:6]
	DS_txRegs& settxcalpredrvregbp(uint val);
	uint gettxcalpredrvregbp();

	//CSR15[5:4]
	DS_txRegs& settxtermcalmode(uint val);
	uint gettxtermcalmode();

	//CSR15[3:2]
	DS_txRegs& settxotbrefsel(uint val);
	uint gettxotbrefsel();

	//CSR15[1:0]
	DS_txRegs& settxotbsel(uint val);
	uint gettxotbsel();

	//CSR16[15:15]
	DS_txRegs& settxcaldrvpmosbp(uint val);
	uint gettxcaldrvpmosbp();

	//CSR16[14:14]
	DS_txRegs& settxcaldrvnmosbp(uint val);
	uint gettxcaldrvnmosbp();

	//CSR16[13:11]
	DS_txRegs& settxdrvregatbctrl(uint val);
	uint gettxdrvregatbctrl();

	//CSR16[10:7]
	DS_txRegs& setdscalmaxtrans(uint val);
	uint getdscalmaxtrans();

	//CSR16[6:6]
	DS_txRegs& settxcallpbkofst2dir(uint val);
	uint gettxcallpbkofst2dir();

	//CSR16[5:5]
	DS_txRegs& settxcallpbkofst1dir(uint val);
	uint gettxcallpbkofst1dir();

	//CSR16[4:4]
	DS_txRegs& settxcallpbkofst2bp(uint val);
	uint gettxcallpbkofst2bp();

	//CSR16[3:3]
	DS_txRegs& settxcallpbkofst1bp(uint val);
	uint gettxcallpbkofst1bp();

	//CSR16[2:2]
	DS_txRegs& settxpredrvcaldir(uint val);
	uint gettxpredrvcaldir();

	//CSR16[1:0]
	DS_txRegs& settxtopatbctrl(uint val);
	uint gettxtopatbctrl();

	//CSR17[15:8]
	DS_txRegs& settxdrvsel1(uint val);
	uint gettxdrvsel1();

	//CSR17[7:0]
	DS_txRegs& setseg1ctrl23to16(uint val);
	uint getseg1ctrl23to16();

	//CSR18[15:0]
	DS_txRegs& setseg1ctrl15to0(uint val);
	uint getseg1ctrl15to0();

	//CSR19[15:8]
	DS_txRegs& settxdrvsel2(uint val);
	uint gettxdrvsel2();

	//CSR19[7:0]
	DS_txRegs& setseg2ctrl23to16(uint val);
	uint getseg2ctrl23to16();

	//CSR20[15:0]
	DS_txRegs& setseg2ctrl15to0(uint val);
	uint getseg2ctrl15to0();

	//CSR21[15:8]
	DS_txRegs& settxdrvsel3(uint val);
	uint gettxdrvsel3();

	//CSR21[7:0]
	DS_txRegs& setseg3ctrl23to16(uint val);
	uint getseg3ctrl23to16();

	//CSR22[15:0]
	DS_txRegs& setseg3ctrl15to0(uint val);
	uint getseg3ctrl15to0();

	//CSR23[15:8]
	DS_txRegs& settxdrvsel4(uint val);
	uint gettxdrvsel4();

	//CSR23[7:0]
	DS_txRegs& setseg4ctrl23to16(uint val);
	uint getseg4ctrl23to16();

	//CSR24[15:0]
	DS_txRegs& setseg4ctrl15to0(uint val);
	uint getseg4ctrl15to0();

	//CSR25[14:8]
	uint gettxphsval();

	//CSR25[7:4]
	DS_txRegs& setnmoscalconf(uint val);
	uint getnmoscalconf();

	//CSR25[3:0]
	DS_txRegs& setpmoscalconf(uint val);
	uint getpmoscalconf();

	//CSR26[15:8]
	DS_txRegs& settxspare(uint val);
	uint gettxspare();

	//CSR26[7:2]
	DS_txRegs& settxdigspare(uint val);
	uint gettxdigspare();

	//CSR26[1:1]
	DS_txRegs& settxdrvcaldndir(uint val);
	uint gettxdrvcaldndir();

	//CSR26[0:0]
	DS_txRegs& settxdrvcalupdir(uint val);
	uint gettxdrvcalupdir();

	//CSR27[15:15]
	uint gettxdrvcaldone();

	//CSR27[14:14]
	uint gettxtapmapdone();

	//CSR27[11:6]
	DS_txRegs& settxdrvncaldn(uint val);
	uint gettxdrvncaldn();

	//CSR27[5:0]
	DS_txRegs& settxdrvncalup(uint val);
	uint gettxdrvncalup();

	//CSR28[13:8]
	uint gettxiqofstff1();

	//CSR28[5:0]
	uint gettxiqofstff2();

	//CSR29[13:8]
	uint gettxiqofstff3();

	//CSR29[5:0]
	uint gettxiqofstffavg();

	//CSR30[13:8]
	DS_txRegs& settxclkregcalrefsel(uint val);
	uint gettxclkregcalrefsel();

	//CSR30[5:0]
	DS_txRegs& settxdrvregcalrefsel(uint val);
	uint gettxdrvregcalrefsel();

	//CSR31[14:5]
	DS_txRegs& settxcaltimervalue(uint val);
	uint gettxcaltimervalue();

	//CSR31[4:2]
	DS_txRegs& settxcaltimerdivvalue(uint val);
	uint gettxcaltimerdivvalue();

	//CSR31[1:1]
	DS_txRegs& settxcaltimerdiven(uint val);
	uint gettxcaltimerdiven();

	//CSR31[0:0]
	DS_txRegs& settxcaltimerstop(uint val);
	uint gettxcaltimerstop();

	//CSR32[15:14]
	DS_txRegs& settxdrvregvrefrng(uint val);
	uint gettxdrvregvrefrng();

	//CSR32[13:12]
	DS_txRegs& settxpredrvregvrefrng(uint val);
	uint gettxpredrvregvrefrng();

	//CSR32[11:7]
	DS_txRegs& settxpredrvreglvl(uint val);
	uint gettxpredrvreglvl();

	//CSR32[6:6]
	DS_txRegs& settxdrvreginrushpwrdb(uint val);
	uint gettxdrvreginrushpwrdb();

	//CSR32[5:5]
	DS_txRegs& settxpredrvreginrushpwrdb(uint val);
	uint gettxpredrvreginrushpwrdb();

	//CSR32[4:4]
	DS_txRegs& settxpredrvregpwrdb(uint val);
	uint gettxpredrvregpwrdb();

	//CSR32[3:1]
	DS_txRegs& settxpredrvregatbctrl(uint val);
	uint gettxpredrvregatbctrl();

	//CSR33[15:15]
	DS_txRegs& settxerrinjen(uint val);
	uint gettxerrinjen();

	//CSR33[14:14]
	DS_txRegs& settxerrinjmode(uint val);
	uint gettxerrinjmode();

	//CSR33[13:12]
	DS_txRegs& settxerrinjpttn(uint val);
	uint gettxerrinjpttn();

	//CSR33[5:5]
	DS_txRegs& settxerrinjstart(uint val);
	uint gettxerrinjstart();

	//CSR33[4:0]
	DS_txRegs& settxerrinjintvl(uint val);
	uint gettxerrinjintvl();

	//CSR34[15:0]
	DS_txRegs& settxerrinjctrl(uint val);
	uint gettxerrinjctrl();

	//CSR35[15:15]
	DS_txRegs& settxrxserlpbkcalen(uint val);
	uint gettxrxserlpbkcalen();

	//CSR35[13:12]
	DS_txRegs& settxrxserlpbkotbsel(uint val);
	uint gettxrxserlpbkotbsel();

	//CSR35[11:11]
	DS_txRegs& settxrxserlpbken(uint val);
	uint gettxrxserlpbken();

	//CSR35[10:10]
	DS_txRegs& settxrxserlpbkgainsel(uint val);
	uint gettxrxserlpbkgainsel();

	//CSR35[9:9]
	DS_txRegs& settxrxserlpbksel(uint val);
	uint gettxrxserlpbksel();

	//CSR35[8:7]
	DS_txRegs& settxrxserlpbksupatbsel(uint val);
	uint gettxrxserlpbksupatbsel();

	//CSR35[6:5]
	DS_txRegs& settxrxserlpbkatbctrl(uint val);
	uint gettxrxserlpbkatbctrl();

	//CSR35[4:3]
	DS_txRegs& settxrxserlpbkdpm(uint val);
	uint gettxrxserlpbkdpm();

	//CSR35[2:1]
	DS_txRegs& settxrxserlpbkdpmen(uint val);
	uint gettxrxserlpbkdpmen();

	//CSR36[12:10]
	DS_txRegs& settxrxserlpbkgn1(uint val);
	uint gettxrxserlpbkgn1();

	//CSR36[7:5]
	DS_txRegs& settxrxserlpbkgn2(uint val);
	uint gettxrxserlpbkgn2();

	//CSR36[2:0]
	DS_txRegs& settxrxserlpbkgn3(uint val);
	uint gettxrxserlpbkgn3();

	//CSR37[14:10]
	DS_txRegs& settxrxserlpbkofst1(uint val);
	uint gettxrxserlpbkofst1();

	//CSR37[9:5]
	DS_txRegs& settxrxserlpbkofst2(uint val);
	uint gettxrxserlpbkofst2();

	//CSR37[4:0]
	DS_txRegs& settxrxserlpbkofst3(uint val);
	uint gettxrxserlpbkofst3();

	//CSR38[11:8]
	DS_txRegs& settxrxserlpbkltrim1(uint val);
	uint gettxrxserlpbkltrim1();

	//CSR38[7:4]
	DS_txRegs& settxrxserlpbkltrim2(uint val);
	uint gettxrxserlpbkltrim2();

};

#endif // HILINKDSTXREGS_H_
