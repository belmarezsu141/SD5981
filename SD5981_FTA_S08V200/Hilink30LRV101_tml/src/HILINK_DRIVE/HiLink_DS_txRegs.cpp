#include <HILINK_DRIVE/HiLink_DS_txRegs.h>

#include <iostream>
using namespace std;
DS_txRegs::DS_txRegs() {
	// TODO Auto-generated constructor stub
	for(int i=0;i<DS_TX_CSR_NUM;i++){
		csr[i]=0;
	}
	sliceID=0;
	macroID=0;
	broadcast=false;
	reset_csr_verify();
}

DS_txRegs::~DS_txRegs() {}

bool
DS_txRegs::get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos){
	if(csrIndex>=DS_TX_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	return REG_INFO.get_reg_infos(csrIndex,reg_infos);
}

DS_txRegs&
DS_txRegs::getInstance(){
	static DS_txRegs theInstance;
	return theInstance;
}

uint
DS_txRegs::get_HILINK_MAX_LANE_NUM(){
	//TODO: add your code for CSR Address mapping
	return HILINK_LANE_NUM;
}

uint
DS_txRegs::getAddressMapToHiLink(int csrIndex){
	if(csrIndex>=DS_TX_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	//TODO: add your code for CSR Address mapping
	return (uint)(0x4000 | (broadcast << 13) | (sliceID << 9) | ((uint)0x0<< 7) | csrIndex << 1);
}


uint&
DS_txRegs::get_csr(uint csrIndex){
	if(csrIndex>=DS_TX_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	return csr[csrIndex];
}

void
DS_txRegs::get_default_MacroLaneID(T_MacroLaneID& id){
	//TODO: add your code for CSR Address mapping
	id.MacroID=macroID;
	id.LaneID=sliceID;
}

uint
DS_txRegs::getCSRCount(){
	return DS_TX_CSR_NUM;
}

string
DS_txRegs::getName(){
	return "DS_TX";
}

///////////////////////////////////////////////////////////////////////////


	/// Transmit path power down control. Active low. This pin will gate other analog power down pins. 
	/// 0 = Power down all related TX circuitry and forces a power down values on TXTAPPWRDB[7:0].  
	/// 1 = Powers up all transmit circuitry in sequence.  
	/// New in v101:  Now used as a trigger to power up/down the Transmitter circuits
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txpwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{0,"txpwrdb",15,15}
	};
	return reg;
}

	/// Enable control of cap-slices of Tx driver. For every bit,
	/// x000 = all cap slices disabled
	/// x111 = all cap slices enabled
	/// bit[3] is no connect
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcapen(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{0,"txdrvcapen",13,10}
	};
	return reg;
}

	/// The pre-cursor 2 of the TX driver FIR. Used for pre-emphasis control . A sign magnitude (binary) value.  [also see related register DS TX CSR11 TXTAPPWRDB before using any of the TXFIR**** registers below]
	/// bit[9]  -  polarity  of pre-cursor 2 of the TX driver FIR
	/// bit[8:5] -   magnitude of pre-cursor 2 of the Tx driver FIR
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txfirpre2(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{0,"txfirpre2",9,5}
	};
	return reg;
}

	/// The pre-cursor 1 of the TX driver FIR. Used for pre-emphasis control. A sign magnitude (binary) value. 
	/// bit[4]  -  polarity  of pre-cursor 1 of the TX driver FIR
	/// bit[3:0] -   magnitude of pre-cursor 1 of the Tx driver FIR
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txfirpre1(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{0,"txfirpre1",4,0}
	};
	return reg;
}

	/// The main cursor of the TX driver FIR. Used for pre-emphasis control. A binary  value.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txfirmain(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{1,"txfirmain",15,10}
	};
	return reg;
}

	/// The  post-cursor 1 of the TX driver FIR. This value is added to TXFIRPOST1X to set post_cursor value.  Used for pre-emphasis control. A sign magnitude (binary) value.
	/// bit[9]  -  polarity  of post-cursor 1 of the TX driver FIR
	/// bit[8:5] -   magnitude of post-cursor 1 of the Tx driver FIR
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txfirpost1(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{1,"txfirpost1",9,5}
	};
	return reg;
}

	/// The post_cursor 1 extension  of the TX driver FIR.    This value is added to TXFIRPOST1 to set post_cursor value. Used for pre-emphasis control. A sign magnitude  (binary) value.  
	/// bit[4]  -  polarity  of post-cursor 1x of the TX driver FIR
	/// bit[3:0] -   magnitude of post-cursor 1x of the Tx driver FIR
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txfirpost1x(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{1,"txfirpost1x",4,0}
	};
	return reg;
}

	/// Transmit digital circuitry reset. Active low.
	/// 0 = Reset TX digital logic.
	/// 1 = Normal operation.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrstb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{2,"txrstb",15,15}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdwidth(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{2,"txdwidth",14,13}
	};
	return reg;
}

	/// TX bit rate mode. [Refer to Table.3 in HiLink30_datasheet and related register TXDWIDTH]
	/// 000 = full-rate
	/// 001 = 1/2-rate
	/// 010 = 1/4-rate
	/// 011 = 1/8-rate
	/// 100   = 1/16-rate
	/// 101 to 111 = do not use
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txratemode(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{2,"txratemode",12,10}
	};
	return reg;
}

	/// Selects the mapping of the parallel TXD bits to the serial bit order.
	/// 0 = LSB is the bit serially output first. 
	/// 1 = MSB is the bit serially output first
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txbitorder(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{2,"txbitorder",9,9}
	};
	return reg;
}

	/// TX data polarity control. When set, all transmit bits are inverted before being serialized out.
	/// 0 = Do not invert the TX data.
	/// 1 = Invert the TX data
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txpolarity(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{2,"txpolarity",8,8}
	};
	return reg;
}

	/// Select the clock to which the TX clock is aligned.
	/// 00 = Choose the clock coming along with the TX data from the core
	/// ;01 = Choose the recovered clock from the RX
	/// ;10 = Choose the mclk
	/// ;11 = Choose the clock derived from one of the clock spines. Note that when this selection is made, self-align mode cannot be used (i.e., TXALIGNMODE[2:0]=000 can't be used).
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txclksel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{2,"txclksel",7,6}
	};
	return reg;
}

	/// Select the parallel TX data to be sent.
	/// 00 = select core data (i.e., TXD).
	/// 01 = select RX parallel data (RX-TX parallel loop back). 
	/// 10 = select pattern for PRBS generation. 
	/// 11 = Reserved for future use
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdatasel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{2,"txdatasel",5,4}
	};
	return reg;
}

	/// TX alignment window select for the TX phase aligner.
	/// 0 = 4 UI  
	/// 1 = 8 UI  
	/// Note : The Numbers are given in 'full' rate UIs
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdeadbandsel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{2,"txdeadbandsel",3,3}
	};
	return reg;
}

	/// TX phase align mode
	/// 000 = Self-align mode.
	/// 001 = Plesio-synchronous self align mode (Not supported in the current version)
	/// 010 = Copy mode where the RX phase code is copied(Not supported in current version)
	/// 011 = Freeze mode the TXPHSWRITE[7:0] is set manually
	/// 100 = Jitter generation for test mode
	/// 101 = Synchronous master mode (TXCLKSEL[1:0] must be set to '11')   - Refer to fig. 14 in the HiLink30_datasheet
	/// 11x = Reserved
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txalignmode(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{2,"txalignmode",2,0}
	};
	return reg;
}

	/// 0 = Normal feature
	/// 1 = Extended feature
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::jitppmctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{3,"jitppmctrl",15,15}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::jitfreq(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{3,"jitfreq",14,12}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::jitamp(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{3,"jitamp",11,8}
	};
	return reg;
}

	/// Select the k value in calculating the jitter period.
	/// 0 =    k=0 , where JITAMP is changed by subtracting 1 from no. of phase steps before a change in direction 
	/// 1 =    k=1, where JITAMP is as defined
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::kfactor(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{3,"kfactor",7,7}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::ppmgen(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{3,"ppmgen",4,0}
	};
	return reg;
}

	/// TX phase interpolator control  (2's complement number).
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txphswrite(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{4,"txphswrite",15,8}
	};
	return reg;
}

	/// PRBS generator enable:. When switching this bit from 0 to 1, PRBS generator is reset.
	/// 0 = Disable PRBS generator
	/// 1 = Enable PRBS generator
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::prbsgenen(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{4,"prbsgenen",4,4}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::prbsgenpatsel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{4,"prbsgenpatsel",3,0}
	};
	return reg;
}

	/// Custom pattern part 1 (bit[79:64]).
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcuspat1(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{5,"txcuspat1",15,0}
	};
	return reg;
}

	/// Custom pattern part 2 (bit[63:48]).
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcuspat2(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{6,"txcuspat2",15,0}
	};
	return reg;
}

	/// Custom pattern part 3 (bit[47:32]).
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcuspat3(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{7,"txcuspat3",15,0}
	};
	return reg;
}

	/// Custom pattern part 4 (bit[31:16]).
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcuspat4(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{8,"txcuspat4",15,0}
	};
	return reg;
}

	/// Custom pattern part 5 (bit[15:0]).
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcuspat5(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{9,"txcuspat5",15,0}
	};
	return reg;
}

	/// TX PI skew correction: [7] reserved; [6:0] are 2's complement
	/// 3F: +63
	/// 00: 0
	/// 40:-64
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcpddlcal(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{10,"txcpddlcal",7,0}
	};
	return reg;
}

	/// Tx driver regulator power down control. Active low.  [see also related register DS TX CSR12 TXDRVREGLVL, TXDRVREGDPMEN, TXDRVREGBLEEDB]
	/// 0 = power down.
	/// 1 = power up.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvregpwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{11,"txdrvregpwrdb",13,13}
	};
	return reg;
}

	/// Tx driver calibration control. Active low.
	/// 0 = power down calibration circuits.
	/// 1 = power up calibration circuits.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcalpwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{11,"txdrvcalpwrdb",12,12}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txtappwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{11,"txtappwrdb",7,0}
	};
	return reg;
}

	/// Tx I/Q detector I-phase input swap control.
	/// 0 = Normal mode
	/// 1 = Swap i-phase and ib-phase
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcpdetswapi(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{12,"txcpdetswapi",15,15}
	};
	return reg;
}

	/// Tx I/Q detector Q-phase input swap control.
	/// 0 = Normal mode
	/// 1 = Swap q-phase and qb-phase
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcpdetswapq(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{12,"txcpdetswapq",14,14}
	};
	return reg;
}

	/// Not implemented in analog.
	/// May be repurposed for DCD detector operation.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcpdetiqmode(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{12,"txcpdetiqmode",13,13}
	};
	return reg;
}

	/// Tx I/Q detector powerdown control
	/// 0 = powerdown
	/// 1 = enabled
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcpdetiqpwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{12,"txcpdetiqpwrdb",12,12}
	};
	return reg;
}

	/// Tx driver regulator bleed current control.
	/// 0 = enable bleed current
	/// 1 = disable bleed current
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvregbleedb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{12,"txdrvregbleedb",6,6}
	};
	return reg;
}

	/// Tx driver/predriver regulator inrush current limit DPM trimming.
	/// 0 = select voltage reference for SS corner
	/// 1 = select voltage reference for TT/FF corner
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvregdpmen(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{12,"txdrvregdpmen",5,5}
	};
	return reg;
}

	/// Voltage level control of Tx driver regulator.[see also related register fields TXDRVREGPWRDB and TXDRVREGBLEEDB]
	/// 00000 = Minimum voltage.
	/// 00001
	/// 00010
	/// ?.
	/// 10100 = voltage (default) 0.927V (TT)
	/// 11111 = Maximum voltage.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvreglvl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{12,"txdrvreglvl",4,0}
	};
	return reg;
}

	/// Tx output voltage swing control (Function behaviour only explicitly defined when FIR not in use)
	/// 4'b1111 = max swing (assumes 32 slices driving)
	/// 4'b0111 = 0.75x swing
	/// 4'b0011 = 0.50x swing
	/// 4'b0001 = 0.25x swing
	/// 4'b0000 = min swing (no output)
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvampctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{13,"txdrvampctrl",12,9}
	};
	return reg;
}

	/// 0 to 1 transition =  start tap mapping FSM
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvswctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{13,"txdrvswctrl",7,7}
	};
	return reg;
}

	/// Polarity control of FIR taps (MANUAL mode only -  ref to register TXTERMCALMODE. Also see related register DS TX CSR11 TXTAPPWRDB) . 
	/// 
	/// TXDRVTAPINV[0]= PRE1 tap polarity (0 = Positive ; 1 = negative )
	/// TXDRVTAPINV[1]= PRE2  tap polarity  (0 = Positive ; 1 = negative )
	/// TXDRVTAPINV[2]= POST1  tap polarity  (0 = Positive ; 1 = negative )
	/// TXDRVTAPINV[3]= POST1X  tap polarity  (0 = Positive ; 1 = negative )
	/// TXDRVTAPINV[4]= MAIN  tap polarity  (0 = Positive ; 1 = negative )
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvtapinv(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{13,"txdrvtapinv",4,0}
	};
	return reg;
}

	/// Tx driver P-side calibration current control. [also see related register DS TX CSR11 TXDRVCALPWRDB before using any of the TXDRVCAL**** registers below]
	/// 0 = Turn off P-side calibration current.
	/// 1 = Turn on P-side calibration current.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcalhisel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{14,"txdrvcalhisel",15,15}
	};
	return reg;
}

	/// Tx driver M-side calibration current control.
	/// 0 = Turn off M-side calibration current.
	/// 1 = Turn on M-side calibration current.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcallosel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{14,"txdrvcallosel",14,14}
	};
	return reg;
}

	/// Tx driver calibration txo_p end seletion.
	/// 0 = disable
	/// 1 = Select txo_p end to calibrate
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcalpsel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{14,"txdrvcalpsel",13,13}
	};
	return reg;
}

	/// Tx driver calibration txo_m end seletion.
	/// 0 = disable
	/// 1 = Select txo_m end to calibrate
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcalmsel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{14,"txdrvcalmsel",12,12}
	};
	return reg;
}

	/// Tx driver otbp mux control. Selected signal will go to hv_txtop_otbm.
	/// 00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 = sense DRV  p (txo_p)
	/// 10 = sense DRV  m (txo_m)
	/// 11 = floating
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvotbpctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{14,"txdrvotbpctrl",11,10}
	};
	return reg;
}

	/// Tx driver otbm mux control. Selected signal will go to hv_txtop_otbp.
	/// 00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 = select vref_high
	/// 10 = select vref_middle
	/// 11 = select vref_low
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvotbmctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{14,"txdrvotbmctrl",9,8}
	};
	return reg;
}

	/// Tx top otb mux control. Select signal that go to hv_txtop_otbp/m.
	/// 00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 = selects tx drv otbp/otbm related signal (ie output of TXDRVOTBPCTRL or TXDRVOTBMCTRL mux above)
	/// 10 = select IQ de-skew sensing signal
	/// 11 = select txdrv_sensep/txdrv_sensem
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txtopotbctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{14,"txtopotbctrl",7,6}
	};
	return reg;
}

	/// New in v101: Used to simulate DS power sequence in tx_quiet mode for testing.  Should be 1'b0 during mission mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pwrsqtxquiet(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{14,"pwrsqtxquiet",5,5}
	};
	return reg;
}

	/// Status of tx_quiet pin
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txquietstatus(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{14,"txquietstatus",4,4}
	};
	return reg;
}

	/// Defines the powerdown granularity of the TX circuitry when EEE tx quiet is asserted
	/// 1000 = most power savings
	/// 1100 = moderate power savings
	/// 1110 = least power savings
	/// others =  no power savings
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txeeepwrdbsel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{14,"txeeepwrdbsel",3,0}
	};
	return reg;
}

	/// TX driver calibration start control. Used only in automatic and semi-automatic modes. (see also related register DS TX CSR11 TXDRVCALPWRDB before selection)
	/// 0 = Do not start TX driver calibration
	/// 1 = Start TX driver calibration.  Self clear after calibration is done
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcalstart(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"txdrvcalstart",15,15}
	};
	return reg;
}

	/// Not used. This register is hardcoded to read '0'
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::dstxlowoffout(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"dstxlowoffout",14,14}
	};
	return reg;
}

	/// Direction control for calibrating the lowoff comparator for both TX driver and TX pre driver
	/// 0 =The control code increases when the compare status is 0 and  the control code decrease when the compare status is 1
	/// 1 = The control code increases when the compare status is 1 and  the control code decrease when the compare status is 0
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcaldir(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"txdrvcaldir",13,13}
	};
	return reg;
}

	/// TX calibration mode
	/// 0 = Automatic calibration 
	/// 1 = Manual calibration
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcalmode(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"txcalmode",11,11}
	};
	return reg;
}

	/// TX Slice selection mode 
	/// 0 = Number of slices in pullup/pulldown state is controlled by the calibration FSM
	/// 1 = Number of slices in pullup/pulldown state is controlled by the TXDRVNCALUP[5:0]/TXDRVNCALDN[5:0] register fields
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txslicemode(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"txslicemode",10,10}
	};
	return reg;
}

	/// Repurposed - Description Change
	/// (TX IQ offset value selection. 
	/// 0 = select from CSR 
	/// 1 = select from calibration FSM)
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txiqofstmode(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"txiqofstmode",9,9}
	};
	return reg;
}

	/// TX IQ de-skew calibration bypass control
	/// 0 = normal
	/// 1 = bypass deskew calibration
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcaldeskewbp(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"txcaldeskewbp",8,8}
	};
	return reg;
}

	/// Bypass the driver regulator calibration
	/// 0 = normal
	/// 1 = bypass
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcaldrvregbp(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"txcaldrvregbp",7,7}
	};
	return reg;
}

	/// Bypass the pre-driver regulator calibration
	/// 0 = normal
	/// 1 = bypass
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcalpredrvregbp(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"txcalpredrvregbp",6,6}
	};
	return reg;
}

	/// TX driver calibration and tap mapping mode control.
	/// 00 =   Auto mode controlled by FSM including driver calibration and tap mapping 
	/// 01 =  Semiautomatic mode, FIR coefficients are controlled by driver calibration FSM
	/// 10 =  Semiautomatic mode, FIR coefficients are controlled by tap mapping  FSM
	/// 11 =  Manual mode
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txtermcalmode(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"txtermcalmode",5,4}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txotbrefsel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"txotbrefsel",3,2}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txotbsel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"txotbsel",1,0}
	};
	return reg;
}

	/// Bypass the P-Side PMOS termination calibration
	/// 0 = normal
	/// 1 = bypass
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcaldrvpmosbp(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{16,"txcaldrvpmosbp",15,15}
	};
	return reg;
}

	/// Bypass the M-Side NMOS termination calibration
	///  0 = normal
	///  1 = bypass
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcaldrvnmosbp(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{16,"txcaldrvnmosbp",14,14}
	};
	return reg;
}

	/// Tx driver regulator ATB control. Selected signal will go to hv_txtop_atb_out.
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = select vref
	/// 010 = select vlow 
	/// 011 = High impedance
	/// 100 = High impedance
	/// 101 = select vmid
	/// 110 = select txdrv 2/3 vreg sense voltage
	/// 111 = High impedance
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvregatbctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{16,"txdrvregatbctrl",13,11}
	};
	return reg;
}

	/// Max transition setting for DS calibration
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::dscalmaxtrans(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{16,"dscalmaxtrans",10,7}
	};
	return reg;
}

	/// Controls the TX-to-RX loopback stage 2 offset calibration direction
	/// 0 = increases when the compare status is 0, decreases when the compare status is 1
	/// 1 = increases when the compare status is 1, decreases when the compare status is 0
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcallpbkofst2dir(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{16,"txcallpbkofst2dir",6,6}
	};
	return reg;
}

	/// Controls the TX-to-RX loopback stage 1 offset calibration direction
	/// 0 =  increases when the compare status is 0, decreases when the compare status is 1
	/// 1 =  increases when the compare status is 1, decreases when the compare status is 0
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcallpbkofst1dir(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{16,"txcallpbkofst1dir",5,5}
	};
	return reg;
}

	/// Bypass the TX-to-RX loopback stage 2 offset calibration
	/// 0 = normal
	/// 1 = bypas
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcallpbkofst2bp(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{16,"txcallpbkofst2bp",4,4}
	};
	return reg;
}

	/// Bypass the TX-to-RX loopback stage 1 offset calibration
	/// 0 = normal
	/// 1 = bypass
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcallpbkofst1bp(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{16,"txcallpbkofst1bp",3,3}
	};
	return reg;
}

	/// Not used (see TXDRVCALDIR)
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txpredrvcaldir(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{16,"txpredrvcaldir",2,2}
	};
	return reg;
}

	/// Tx top ATB control. Selected signal will go to hv_txtop_atb_out.
	/// 00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 =  select TX regulator ATB bus
	/// 10 = select txpredrv 2/3 vreg sense voltage
	/// 11 = select txdrv 2/3 vreg sense voltage
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txtopatbctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{16,"txtopatbctrl",1,0}
	};
	return reg;
}

	/// Tx driver slicers output  data control for each of the 8 slices in cluster 0  (MANUAL mode only -  ref to register TXTERMCALMODE. Also see related register DS TX CSR11 TXTAPPWRDB ) . 
	/// For every bit,
	/// 0 = main tap
	/// ;1 = Other tap ( PRE2 - refer to FIR mapping for details)
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvsel1(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{17,"txdrvsel1",15,8}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::seg1ctrl23to16(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{17,"seg1ctrl23to16",7,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::seg1ctrl15to0(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{18,"seg1ctrl15to0",15,0}
	};
	return reg;
}

	/// Tx driver slicers output data control for each of the 8 slices in cluster 1.
	/// For every bit,
	/// 0 = main tap
	/// ;1 = other tap (PRE1- refer to FIR mapping for details).
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvsel2(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{19,"txdrvsel2",15,8}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::seg2ctrl23to16(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{19,"seg2ctrl23to16",7,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::seg2ctrl15to0(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{20,"seg2ctrl15to0",15,0}
	};
	return reg;
}

	/// Tx driver slicers output  control for each of the 8 slices in cluster 2. For every bit,
	/// 0 = main tap
	/// ;1 = other tap (POST1 - refer to FIR mapping for details).
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvsel3(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{21,"txdrvsel3",15,8}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::seg3ctrl23to16(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{21,"seg3ctrl23to16",7,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::seg3ctrl15to0(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{22,"seg3ctrl15to0",15,0}
	};
	return reg;
}

	/// Tx driver slicers output data control for each of 8 slice in cluster 3. For every bit,
	/// 0 = main tap
	/// ;1 = other tap (POST1X - refer to FIR mapping for details).
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvsel4(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{23,"txdrvsel4",15,8}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::seg4ctrl23to16(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{23,"seg4ctrl23to16",7,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::seg4ctrl15to0(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{24,"seg4ctrl15to0",15,0}
	};
	return reg;
}

	/// This register contains the present binary phase value of the TX phase interpolator.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txphsval(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{25,"txphsval",14,8}
	};
	return reg;
}

	/// Number of nmos calibration cells.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::nmoscalconf(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{25,"nmoscalconf",7,4}
	};
	return reg;
}

	/// Number of pmos calibration cells.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pmoscalconf(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{25,"pmoscalconf",3,0}
	};
	return reg;
}

	/// Tx spare control bits.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txspare(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{26,"txspare",15,8}
	};
	return reg;
}

	/// spare register bits
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdigspare(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{26,"txdigspare",7,2}
	};
	return reg;
}

	/// Direction control for TX driver down side calibration.
	/// 0  =  The control code increases when the compare status is 0 and  the control code decrease when the compare status is 1
	/// 1  =  The control code increases when the compare status is 1 and  the control code decrease when the compare status is 0
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcaldndir(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{26,"txdrvcaldndir",1,1}
	};
	return reg;
}

	/// Direction control for TX driver up side calibration.
	/// 0  =  The control code increases when the compare status is 0 and  the control code decrease when the compare status is 1
	/// 1  =  The control code increases when the compare status is 1 and  the control code decrease when the compare status is 0
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcalupdir(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{26,"txdrvcalupdir",0,0}
	};
	return reg;
}

	/// 0 = TX Driver calibration is still in progress
	/// 1 = TX Driver calibration has completed
	/// (This may be redundant since TXDRVCALSTART is now self clear after calibration is done)
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcaldone(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{27,"txdrvcaldone",15,15}
	};
	return reg;
}

	/// 0 = TX tap mapping is not done
	/// 1 = TX tap mapping is done
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txtapmapdone(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{27,"txtapmapdone",14,14}
	};
	return reg;
}

	/// Number of calibrated TX slices in pull-down state
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvncaldn(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{27,"txdrvncaldn",11,6}
	};
	return reg;
}

	/// Number of calibrated TX slices in pull-up state
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvncalup(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{27,"txdrvncalup",5,0}
	};
	return reg;
}

	/// tx iq deskew value for swap_i=0 and swap_q=0
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txiqofstff1(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{28,"txiqofstff1",13,8}
	};
	return reg;
}

	/// tx iq deskew value for swap_i=1 and swap_q=0
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txiqofstff2(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{28,"txiqofstff2",5,0}
	};
	return reg;
}

	/// tx iq deskew value for swap_i=0 and swap_q=1
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txiqofstff3(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{29,"txiqofstff3",13,8}
	};
	return reg;
}

	/// iq deskew average value(rounding) equal to TXIQOFSTFF1+TXIQOFSTFF2+TXIQOFSTFF3/3.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txiqofstffavg(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{29,"txiqofstffavg",5,0}
	};
	return reg;
}

	/// Set Comparator reference voltage selection for tx predriver regulator calibration:
	/// Calib Target (mV)= 600 * (1+txclkregcalrefsel/64)
	/// Note: TXPREDRVREGVREFRNG[1:0] must be correspondingly set to a range which supports the calibration target value
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txclkregcalrefsel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{30,"txclkregcalrefsel",13,8}
	};
	return reg;
}

	/// Set Comparator reference voltage selection for tx driver regulator calibration:
	/// Calib Target (mV)= 600 * (1+txdrvregcalrefsel/64)
	/// Note: TXDRVREGVREFRNG[1:0] must be correspondingly set to a range which supports the calibration target value
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvregcalrefsel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{30,"txdrvregcalrefsel",5,0}
	};
	return reg;
}

	/// Configuration of timer for waiting, which is the cycles of reference clock.  Timer value = (2powTXCALTIMERVALUE) -1 , where TXCALTIMERVALUE =0 to 22.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcaltimervalue(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{31,"txcaltimervalue",14,5}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcaltimerdivvalue(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{31,"txcaltimerdivvalue",4,2}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcaltimerdiven(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{31,"txcaltimerdiven",1,1}
	};
	return reg;
}

	/// Stop timer, for debugging.
	/// 0 = normal
	/// 1 = stop the timer
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcaltimerstop(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{31,"txcaltimerstop",0,0}
	};
	return reg;
}

	/// reference range select for txdrv regulator
	/// 00 =   vref between 750mV  and  850mV
	/// 01 =  vref  between 851mV and 925mV
	/// 10 =  vref between 926mV and 985mV
	/// 11 =  vref between 986mV and 1050mV
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvregvrefrng(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{32,"txdrvregvrefrng",15,14}
	};
	return reg;
}

	/// reference range select for txpredrv regulator
	/// 00 =   vref between 750mV  and  850mV
	/// 01 =  vref  between 851mV and 925mV
	/// 10 =  vref between 926mV and 985mV
	/// 11 =  vref between 986mV and 1050mV
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txpredrvregvrefrng(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{32,"txpredrvregvrefrng",13,12}
	};
	return reg;
}

	/// Voltage level control of Tx predriver regulator. [ also refer to related register TXPREDRVREGPWRDB]
	/// 00000: Minimum voltage.
	/// 00001
	/// 00010
	/// .
	/// 10100 = voltage (default) 0.927 (TT)
	/// ��...
	/// 11111: Maximum voltage.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txpredrvreglvl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{32,"txpredrvreglvl",11,7}
	};
	return reg;
}

	/// TX driver regulator inrush current limit. Active low.
	/// 0 =  regulator inrush current limit  mode
	/// 1 =  regulator mission mode
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvreginrushpwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{32,"txdrvreginrushpwrdb",6,6}
	};
	return reg;
}

	/// TX predriver regulator inrush current limit. Active low.
	/// 0 =  regulator inrush current limit  mode
	/// 1 =  regulator mission mode
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txpredrvreginrushpwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{32,"txpredrvreginrushpwrdb",5,5}
	};
	return reg;
}

	/// Tx predriver regulator power down control. Active low.
	/// 0 =  power down.
	/// 1 =  power up.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txpredrvregpwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{32,"txpredrvregpwrdb",4,4}
	};
	return reg;
}

	/// Tx predriver regulator ATB control.  
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  select vref
	/// 010 =  select low bias
	/// 011 =  High Impedance
	/// 100 =  High Impedance
	/// 101 =  select vmid
	/// 110 =  select txpredrv 2/3 vreg sense voltage
	/// 111 =  High Impedance
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txpredrvregatbctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{32,"txpredrvregatbctrl",3,1}
	};
	return reg;
}

	/// TX bit error injection enable.
	/// 0 =  Disable; 1 =  Enable
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txerrinjen(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{33,"txerrinjen",15,15}
	};
	return reg;
}

	/// TX bit error injection mode
	/// 0 =  Single shot mode; 1 =  continuous mode
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txerrinjmode(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{33,"txerrinjmode",14,14}
	};
	return reg;
}

	/// TX bit error injection pattern selection
	/// 00 =  Type 1 Inject error pattern specified by TXERRINJCTRL[15:0].
	/// 01 =  Type 2 Inject consecutive errors specified by TXERRINJCTRL[15:0] (max. 255).
	/// 10 =  Reserved
	/// 11 =  Reserved
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txerrinjpttn(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{33,"txerrinjpttn",13,12}
	};
	return reg;
}

	/// TX bit error injection start. In single shot mode, setting this bit to 1 will cause the error pattern specified by TXERRINJPTTN[1:0] to be injected once. Self clear upon completion. In continuous mode, setting this bit to 1 will cause the error pattern specified by TXERRINJPTTN[1 = 0] to be injected continuously until this bit is set to 0. Not self clear in continuous mode.
	/// 0 =  Stop; 1 =  Start.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txerrinjstart(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{33,"txerrinjstart",5,5}
	};
	return reg;
}

	/// TX bit error injection interval (N) for continuous mode. The error pattern specified by TXERRINJPTTN[1:0] is injected every 2powN word clock cycles.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txerrinjintvl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{33,"txerrinjintvl",4,0}
	};
	return reg;
}

	/// TX bit error injection control. 
	/// 
	/// If the error pattern is Type I, the actual error pattern is specified by TXERRINJCTRL[15:0] (0=no error, 1=error); 
	/// 
	/// If the error pattern is Type 2, TXERRINJCTRL[7:0] gives the number of consecutive errors to be injected (max 255); Bits[15:8] are ignored.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txerrinjctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{34,"txerrinjctrl",15,0}
	};
	return reg;
}

	/// set Tx to Rx serial loopback in calibration mode.
	/// 0 = Disable calibration Tx to Rx serial loopback (mission mode)
	/// 1 = configure Tx to Rx serial loopback path for DC calibration
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrxserlpbkcalen(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{35,"txrxserlpbkcalen",15,15}
	};
	return reg;
}

	/// Offset calibration selection for TX to RX serial loopback. 
	/// 00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 = Select Tx2Rx serial loopback stage 1 output
	/// 10 = Select Tx2Rx serial loopback stage 2 output
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrxserlpbkotbsel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{35,"txrxserlpbkotbsel",13,12}
	};
	return reg;
}

	/// TX to RX serial loopback enable.
	/// 0 = Normal operation. Receiver in mission mode. Loopback disabled
	/// 1 = High speed TX to RX loopback is enabled (RX input is ignored)
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrxserlpbken(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{35,"txrxserlpbken",11,11}
	};
	return reg;
}

	/// Repurposed control pin
	/// Allow for independent control of CTLE loopback MUX when loopback is not enabled
	/// 0 = loopback mux controlled by TXRXSERLPBKEN
	/// 1 = enable loopback mux
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrxserlpbkgainsel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{35,"txrxserlpbkgainsel",10,10}
	};
	return reg;
}

	/// Select which TX2RX serial loopback path to use
	/// 0: pre-driver TX loopback path
	/// 1: driver bump TX loopback path  (PROPER OPERATION REQUIRES DRIVER TERMINATION!)
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrxserlpbksel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{35,"txrxserlpbksel",9,9}
	};
	return reg;
}

	/// Not implemented in Analog
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrxserlpbksupatbsel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{35,"txrxserlpbksupatbsel",8,7}
	};
	return reg;
}

	/// ATB selection for TX to RX serial loopback.
	/// 00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 = Select otbp output
	/// 10 = Select otbm output
	/// 11 = Select vss
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrxserlpbkatbctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{35,"txrxserlpbkatbctrl",6,5}
	};
	return reg;
}

	/// Automatic resistor DPM based bandwidth adjust for loopback.
	/// This field should be user programmed based on die/macro resistor DPM measurement
	/// DPM_Setting =  Res Corner - (resulting gain code in gray selected)
	/// 00 =  min res corner - (000)
	/// 01 = typ res corner - (010)
	/// 10 =  max res corner -  (110)
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrxserlpbkdpm(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{35,"txrxserlpbkdpm",4,3}
	};
	return reg;
}

	/// Enable Loopback DPM based bandwidth adjustment by stage (Recommend default override to disable this feature.)
	/// x1 =  stage 1 gain controlled automatically based on TXRXSERLPBKDPM
	/// x0 =  stage 1 gain controlled directly by TXRXSERLPBKGN1
	/// 1x =  stage 2 gain controlled automatically based on TXRXSERLPBKDPM
	/// 0x =  stage 2 gain controlled directly by TXRXSERLPBKGN2
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrxserlpbkdpmen(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{35,"txrxserlpbkdpmen",2,1}
	};
	return reg;
}

	/// TX to RX serial loopback stage 1 gain. 
	/// 000 = Minimum gain
	/// 001
	/// ..
	/// 111 = Maximum gain
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrxserlpbkgn1(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{36,"txrxserlpbkgn1",12,10}
	};
	return reg;
}

	/// TX to RX serial loopback stage 2 gain . 
	/// 000 = Minimum gain
	/// 001 
	/// ..
	/// 111 = Maximum gain
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrxserlpbkgn2(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{36,"txrxserlpbkgn2",7,5}
	};
	return reg;
}

	/// TX to RX serial loopback stage 3 gain. 
	/// 000 = Minimum gain (default)
	/// 001
	/// 010
	/// ..
	/// 111 = Maximum gain
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrxserlpbkgn3(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{36,"txrxserlpbkgn3",2,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrxserlpbkofst1(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{37,"txrxserlpbkofst1",14,10}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrxserlpbkofst2(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{37,"txrxserlpbkofst2",9,5}
	};
	return reg;
}

	/// Not implemented in Analog.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrxserlpbkofst3(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{37,"txrxserlpbkofst3",4,0}
	};
	return reg;
}

	/// NOT IMPLEMENTED IN ANALOG
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrxserlpbkltrim1(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{38,"txrxserlpbkltrim1",11,8}
	};
	return reg;
}

	/// NOT IMPLEMENTED IN ANALOG
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrxserlpbkltrim2(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{38,"txrxserlpbkltrim2",7,4}
	};
	return reg;
}
bool
DS_txRegs::_REG_INFO::get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos){
	reg_infos.clear();
	switch(csr){
		case 0:
			reg_infos.push_back(txpwrdb().reg_info);
			reg_infos.push_back(txdrvcapen().reg_info);
			reg_infos.push_back(txfirpre2().reg_info);
			reg_infos.push_back(txfirpre1().reg_info);
			break;
		case 1:
			reg_infos.push_back(txfirmain().reg_info);
			reg_infos.push_back(txfirpost1().reg_info);
			reg_infos.push_back(txfirpost1x().reg_info);
			break;
		case 2:
			reg_infos.push_back(txrstb().reg_info);
			reg_infos.push_back(txdwidth().reg_info);
			reg_infos.push_back(txratemode().reg_info);
			reg_infos.push_back(txbitorder().reg_info);
			reg_infos.push_back(txpolarity().reg_info);
			reg_infos.push_back(txclksel().reg_info);
			reg_infos.push_back(txdatasel().reg_info);
			reg_infos.push_back(txdeadbandsel().reg_info);
			reg_infos.push_back(txalignmode().reg_info);
			break;
		case 3:
			reg_infos.push_back(jitppmctrl().reg_info);
			reg_infos.push_back(jitfreq().reg_info);
			reg_infos.push_back(jitamp().reg_info);
			reg_infos.push_back(kfactor().reg_info);
			reg_infos.push_back(ppmgen().reg_info);
			break;
		case 4:
			reg_infos.push_back(txphswrite().reg_info);
			reg_infos.push_back(prbsgenen().reg_info);
			reg_infos.push_back(prbsgenpatsel().reg_info);
			break;
		case 5:
			reg_infos.push_back(txcuspat1().reg_info);
			break;
		case 6:
			reg_infos.push_back(txcuspat2().reg_info);
			break;
		case 7:
			reg_infos.push_back(txcuspat3().reg_info);
			break;
		case 8:
			reg_infos.push_back(txcuspat4().reg_info);
			break;
		case 9:
			reg_infos.push_back(txcuspat5().reg_info);
			break;
		case 10:
			reg_infos.push_back(txcpddlcal().reg_info);
			break;
		case 11:
			reg_infos.push_back(txdrvregpwrdb().reg_info);
			reg_infos.push_back(txdrvcalpwrdb().reg_info);
			reg_infos.push_back(txtappwrdb().reg_info);
			break;
		case 12:
			reg_infos.push_back(txcpdetswapi().reg_info);
			reg_infos.push_back(txcpdetswapq().reg_info);
			reg_infos.push_back(txcpdetiqmode().reg_info);
			reg_infos.push_back(txcpdetiqpwrdb().reg_info);
			reg_infos.push_back(txdrvregbleedb().reg_info);
			reg_infos.push_back(txdrvregdpmen().reg_info);
			reg_infos.push_back(txdrvreglvl().reg_info);
			break;
		case 13:
			reg_infos.push_back(txdrvampctrl().reg_info);
			reg_infos.push_back(txdrvswctrl().reg_info);
			reg_infos.push_back(txdrvtapinv().reg_info);
			break;
		case 14:
			reg_infos.push_back(txdrvcalhisel().reg_info);
			reg_infos.push_back(txdrvcallosel().reg_info);
			reg_infos.push_back(txdrvcalpsel().reg_info);
			reg_infos.push_back(txdrvcalmsel().reg_info);
			reg_infos.push_back(txdrvotbpctrl().reg_info);
			reg_infos.push_back(txdrvotbmctrl().reg_info);
			reg_infos.push_back(txtopotbctrl().reg_info);
			reg_infos.push_back(pwrsqtxquiet().reg_info);
			reg_infos.push_back(txquietstatus().reg_info);
			reg_infos.push_back(txeeepwrdbsel().reg_info);
			break;
		case 15:
			reg_infos.push_back(txdrvcalstart().reg_info);
			reg_infos.push_back(dstxlowoffout().reg_info);
			reg_infos.push_back(txdrvcaldir().reg_info);
			reg_infos.push_back(txcalmode().reg_info);
			reg_infos.push_back(txslicemode().reg_info);
			reg_infos.push_back(txiqofstmode().reg_info);
			reg_infos.push_back(txcaldeskewbp().reg_info);
			reg_infos.push_back(txcaldrvregbp().reg_info);
			reg_infos.push_back(txcalpredrvregbp().reg_info);
			reg_infos.push_back(txtermcalmode().reg_info);
			reg_infos.push_back(txotbrefsel().reg_info);
			reg_infos.push_back(txotbsel().reg_info);
			break;
		case 16:
			reg_infos.push_back(txcaldrvpmosbp().reg_info);
			reg_infos.push_back(txcaldrvnmosbp().reg_info);
			reg_infos.push_back(txdrvregatbctrl().reg_info);
			reg_infos.push_back(dscalmaxtrans().reg_info);
			reg_infos.push_back(txcallpbkofst2dir().reg_info);
			reg_infos.push_back(txcallpbkofst1dir().reg_info);
			reg_infos.push_back(txcallpbkofst2bp().reg_info);
			reg_infos.push_back(txcallpbkofst1bp().reg_info);
			reg_infos.push_back(txpredrvcaldir().reg_info);
			reg_infos.push_back(txtopatbctrl().reg_info);
			break;
		case 17:
			reg_infos.push_back(txdrvsel1().reg_info);
			reg_infos.push_back(seg1ctrl23to16().reg_info);
			break;
		case 18:
			reg_infos.push_back(seg1ctrl15to0().reg_info);
			break;
		case 19:
			reg_infos.push_back(txdrvsel2().reg_info);
			reg_infos.push_back(seg2ctrl23to16().reg_info);
			break;
		case 20:
			reg_infos.push_back(seg2ctrl15to0().reg_info);
			break;
		case 21:
			reg_infos.push_back(txdrvsel3().reg_info);
			reg_infos.push_back(seg3ctrl23to16().reg_info);
			break;
		case 22:
			reg_infos.push_back(seg3ctrl15to0().reg_info);
			break;
		case 23:
			reg_infos.push_back(txdrvsel4().reg_info);
			reg_infos.push_back(seg4ctrl23to16().reg_info);
			break;
		case 24:
			reg_infos.push_back(seg4ctrl15to0().reg_info);
			break;
		case 25:
			reg_infos.push_back(txphsval().reg_info);
			reg_infos.push_back(nmoscalconf().reg_info);
			reg_infos.push_back(pmoscalconf().reg_info);
			break;
		case 26:
			reg_infos.push_back(txspare().reg_info);
			reg_infos.push_back(txdigspare().reg_info);
			reg_infos.push_back(txdrvcaldndir().reg_info);
			reg_infos.push_back(txdrvcalupdir().reg_info);
			break;
		case 27:
			reg_infos.push_back(txdrvcaldone().reg_info);
			reg_infos.push_back(txtapmapdone().reg_info);
			reg_infos.push_back(txdrvncaldn().reg_info);
			reg_infos.push_back(txdrvncalup().reg_info);
			break;
		case 28:
			reg_infos.push_back(txiqofstff1().reg_info);
			reg_infos.push_back(txiqofstff2().reg_info);
			break;
		case 29:
			reg_infos.push_back(txiqofstff3().reg_info);
			reg_infos.push_back(txiqofstffavg().reg_info);
			break;
		case 30:
			reg_infos.push_back(txclkregcalrefsel().reg_info);
			reg_infos.push_back(txdrvregcalrefsel().reg_info);
			break;
		case 31:
			reg_infos.push_back(txcaltimervalue().reg_info);
			reg_infos.push_back(txcaltimerdivvalue().reg_info);
			reg_infos.push_back(txcaltimerdiven().reg_info);
			reg_infos.push_back(txcaltimerstop().reg_info);
			break;
		case 32:
			reg_infos.push_back(txdrvregvrefrng().reg_info);
			reg_infos.push_back(txpredrvregvrefrng().reg_info);
			reg_infos.push_back(txpredrvreglvl().reg_info);
			reg_infos.push_back(txdrvreginrushpwrdb().reg_info);
			reg_infos.push_back(txpredrvreginrushpwrdb().reg_info);
			reg_infos.push_back(txpredrvregpwrdb().reg_info);
			reg_infos.push_back(txpredrvregatbctrl().reg_info);
			break;
		case 33:
			reg_infos.push_back(txerrinjen().reg_info);
			reg_infos.push_back(txerrinjmode().reg_info);
			reg_infos.push_back(txerrinjpttn().reg_info);
			reg_infos.push_back(txerrinjstart().reg_info);
			reg_infos.push_back(txerrinjintvl().reg_info);
			break;
		case 34:
			reg_infos.push_back(txerrinjctrl().reg_info);
			break;
		case 35:
			reg_infos.push_back(txrxserlpbkcalen().reg_info);
			reg_infos.push_back(txrxserlpbkotbsel().reg_info);
			reg_infos.push_back(txrxserlpbken().reg_info);
			reg_infos.push_back(txrxserlpbkgainsel().reg_info);
			reg_infos.push_back(txrxserlpbksel().reg_info);
			reg_infos.push_back(txrxserlpbksupatbsel().reg_info);
			reg_infos.push_back(txrxserlpbkatbctrl().reg_info);
			reg_infos.push_back(txrxserlpbkdpm().reg_info);
			reg_infos.push_back(txrxserlpbkdpmen().reg_info);
			break;
		case 36:
			reg_infos.push_back(txrxserlpbkgn1().reg_info);
			reg_infos.push_back(txrxserlpbkgn2().reg_info);
			reg_infos.push_back(txrxserlpbkgn3().reg_info);
			break;
		case 37:
			reg_infos.push_back(txrxserlpbkofst1().reg_info);
			reg_infos.push_back(txrxserlpbkofst2().reg_info);
			reg_infos.push_back(txrxserlpbkofst3().reg_info);
			break;
		case 38:
			reg_infos.push_back(txrxserlpbkltrim1().reg_info);
			reg_infos.push_back(txrxserlpbkltrim2().reg_info);
			break;
		default:
			break;
	}
	return (reg_infos.size()>0);
}


DS_txRegs&
DS_txRegs::settxpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.txpwrdb());	//CSR0[15:15]
	return *this;
}
uint
DS_txRegs::gettxpwrdb(){
	return get_csr_bits(REG_INFO.txpwrdb());	//CSR0[15:15]
}

DS_txRegs&
DS_txRegs::settxdrvcapen(uint val){
	fill_csr_bits(val,REG_INFO.txdrvcapen());	//CSR0[13:10]
	return *this;
}
uint
DS_txRegs::gettxdrvcapen(){
	return get_csr_bits(REG_INFO.txdrvcapen());	//CSR0[13:10]
}

DS_txRegs&
DS_txRegs::settxfirpre2(uint val){
	fill_csr_bits(val,REG_INFO.txfirpre2());	//CSR0[9:5]
	return *this;
}
uint
DS_txRegs::gettxfirpre2(){
	return get_csr_bits(REG_INFO.txfirpre2());	//CSR0[9:5]
}

DS_txRegs&
DS_txRegs::settxfirpre1(uint val){
	fill_csr_bits(val,REG_INFO.txfirpre1());	//CSR0[4:0]
	return *this;
}
uint
DS_txRegs::gettxfirpre1(){
	return get_csr_bits(REG_INFO.txfirpre1());	//CSR0[4:0]
}

DS_txRegs&
DS_txRegs::settxfirmain(uint val){
	fill_csr_bits(val,REG_INFO.txfirmain());	//CSR1[15:10]
	return *this;
}
uint
DS_txRegs::gettxfirmain(){
	return get_csr_bits(REG_INFO.txfirmain());	//CSR1[15:10]
}

DS_txRegs&
DS_txRegs::settxfirpost1(uint val){
	fill_csr_bits(val,REG_INFO.txfirpost1());	//CSR1[9:5]
	return *this;
}
uint
DS_txRegs::gettxfirpost1(){
	return get_csr_bits(REG_INFO.txfirpost1());	//CSR1[9:5]
}

DS_txRegs&
DS_txRegs::settxfirpost1x(uint val){
	fill_csr_bits(val,REG_INFO.txfirpost1x());	//CSR1[4:0]
	return *this;
}
uint
DS_txRegs::gettxfirpost1x(){
	return get_csr_bits(REG_INFO.txfirpost1x());	//CSR1[4:0]
}

DS_txRegs&
DS_txRegs::settxrstb(uint val){
	fill_csr_bits(val,REG_INFO.txrstb());	//CSR2[15:15]
	return *this;
}
uint
DS_txRegs::gettxrstb(){
	return get_csr_bits(REG_INFO.txrstb());	//CSR2[15:15]
}

DS_txRegs&
DS_txRegs::settxdwidth(uint val){
	fill_csr_bits(val,REG_INFO.txdwidth());	//CSR2[14:13]
	return *this;
}
uint
DS_txRegs::gettxdwidth(){
	return get_csr_bits(REG_INFO.txdwidth());	//CSR2[14:13]
}

DS_txRegs&
DS_txRegs::settxratemode(uint val){
	fill_csr_bits(val,REG_INFO.txratemode());	//CSR2[12:10]
	return *this;
}
uint
DS_txRegs::gettxratemode(){
	return get_csr_bits(REG_INFO.txratemode());	//CSR2[12:10]
}

DS_txRegs&
DS_txRegs::settxbitorder(uint val){
	fill_csr_bits(val,REG_INFO.txbitorder());	//CSR2[9:9]
	return *this;
}
uint
DS_txRegs::gettxbitorder(){
	return get_csr_bits(REG_INFO.txbitorder());	//CSR2[9:9]
}

DS_txRegs&
DS_txRegs::settxpolarity(uint val){
	fill_csr_bits(val,REG_INFO.txpolarity());	//CSR2[8:8]
	return *this;
}
uint
DS_txRegs::gettxpolarity(){
	return get_csr_bits(REG_INFO.txpolarity());	//CSR2[8:8]
}

DS_txRegs&
DS_txRegs::settxclksel(uint val){
	fill_csr_bits(val,REG_INFO.txclksel());	//CSR2[7:6]
	return *this;
}
uint
DS_txRegs::gettxclksel(){
	return get_csr_bits(REG_INFO.txclksel());	//CSR2[7:6]
}

DS_txRegs&
DS_txRegs::settxdatasel(uint val){
	fill_csr_bits(val,REG_INFO.txdatasel());	//CSR2[5:4]
	return *this;
}
uint
DS_txRegs::gettxdatasel(){
	return get_csr_bits(REG_INFO.txdatasel());	//CSR2[5:4]
}

DS_txRegs&
DS_txRegs::settxdeadbandsel(uint val){
	fill_csr_bits(val,REG_INFO.txdeadbandsel());	//CSR2[3:3]
	return *this;
}
uint
DS_txRegs::gettxdeadbandsel(){
	return get_csr_bits(REG_INFO.txdeadbandsel());	//CSR2[3:3]
}

DS_txRegs&
DS_txRegs::settxalignmode(uint val){
	fill_csr_bits(val,REG_INFO.txalignmode());	//CSR2[2:0]
	return *this;
}
uint
DS_txRegs::gettxalignmode(){
	return get_csr_bits(REG_INFO.txalignmode());	//CSR2[2:0]
}

DS_txRegs&
DS_txRegs::setjitppmctrl(uint val){
	fill_csr_bits(val,REG_INFO.jitppmctrl());	//CSR3[15:15]
	return *this;
}
uint
DS_txRegs::getjitppmctrl(){
	return get_csr_bits(REG_INFO.jitppmctrl());	//CSR3[15:15]
}

DS_txRegs&
DS_txRegs::setjitfreq(uint val){
	fill_csr_bits(val,REG_INFO.jitfreq());	//CSR3[14:12]
	return *this;
}
uint
DS_txRegs::getjitfreq(){
	return get_csr_bits(REG_INFO.jitfreq());	//CSR3[14:12]
}

DS_txRegs&
DS_txRegs::setjitamp(uint val){
	fill_csr_bits(val,REG_INFO.jitamp());	//CSR3[11:8]
	return *this;
}
uint
DS_txRegs::getjitamp(){
	return get_csr_bits(REG_INFO.jitamp());	//CSR3[11:8]
}

DS_txRegs&
DS_txRegs::setkfactor(uint val){
	fill_csr_bits(val,REG_INFO.kfactor());	//CSR3[7:7]
	return *this;
}
uint
DS_txRegs::getkfactor(){
	return get_csr_bits(REG_INFO.kfactor());	//CSR3[7:7]
}

DS_txRegs&
DS_txRegs::setppmgen(uint val){
	fill_csr_bits(val,REG_INFO.ppmgen());	//CSR3[4:0]
	return *this;
}
uint
DS_txRegs::getppmgen(){
	return get_csr_bits(REG_INFO.ppmgen());	//CSR3[4:0]
}

DS_txRegs&
DS_txRegs::settxphswrite(uint val){
	fill_csr_bits(val,REG_INFO.txphswrite());	//CSR4[15:8]
	return *this;
}
uint
DS_txRegs::gettxphswrite(){
	return get_csr_bits(REG_INFO.txphswrite());	//CSR4[15:8]
}

DS_txRegs&
DS_txRegs::setprbsgenen(uint val){
	fill_csr_bits(val,REG_INFO.prbsgenen());	//CSR4[4:4]
	return *this;
}
uint
DS_txRegs::getprbsgenen(){
	return get_csr_bits(REG_INFO.prbsgenen());	//CSR4[4:4]
}

DS_txRegs&
DS_txRegs::setprbsgenpatsel(uint val){
	fill_csr_bits(val,REG_INFO.prbsgenpatsel());	//CSR4[3:0]
	return *this;
}
uint
DS_txRegs::getprbsgenpatsel(){
	return get_csr_bits(REG_INFO.prbsgenpatsel());	//CSR4[3:0]
}

DS_txRegs&
DS_txRegs::settxcuspat1(uint val){
	fill_csr_bits(val,REG_INFO.txcuspat1());	//CSR5[15:0]
	return *this;
}
uint
DS_txRegs::gettxcuspat1(){
	return get_csr_bits(REG_INFO.txcuspat1());	//CSR5[15:0]
}

DS_txRegs&
DS_txRegs::settxcuspat2(uint val){
	fill_csr_bits(val,REG_INFO.txcuspat2());	//CSR6[15:0]
	return *this;
}
uint
DS_txRegs::gettxcuspat2(){
	return get_csr_bits(REG_INFO.txcuspat2());	//CSR6[15:0]
}

DS_txRegs&
DS_txRegs::settxcuspat3(uint val){
	fill_csr_bits(val,REG_INFO.txcuspat3());	//CSR7[15:0]
	return *this;
}
uint
DS_txRegs::gettxcuspat3(){
	return get_csr_bits(REG_INFO.txcuspat3());	//CSR7[15:0]
}

DS_txRegs&
DS_txRegs::settxcuspat4(uint val){
	fill_csr_bits(val,REG_INFO.txcuspat4());	//CSR8[15:0]
	return *this;
}
uint
DS_txRegs::gettxcuspat4(){
	return get_csr_bits(REG_INFO.txcuspat4());	//CSR8[15:0]
}

DS_txRegs&
DS_txRegs::settxcuspat5(uint val){
	fill_csr_bits(val,REG_INFO.txcuspat5());	//CSR9[15:0]
	return *this;
}
uint
DS_txRegs::gettxcuspat5(){
	return get_csr_bits(REG_INFO.txcuspat5());	//CSR9[15:0]
}

DS_txRegs&
DS_txRegs::settxcpddlcal(uint val){
	fill_csr_bits(val,REG_INFO.txcpddlcal());	//CSR10[7:0]
	return *this;
}
uint
DS_txRegs::gettxcpddlcal(){
	return get_csr_bits(REG_INFO.txcpddlcal());	//CSR10[7:0]
}

DS_txRegs&
DS_txRegs::settxdrvregpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.txdrvregpwrdb());	//CSR11[13:13]
	return *this;
}
uint
DS_txRegs::gettxdrvregpwrdb(){
	return get_csr_bits(REG_INFO.txdrvregpwrdb());	//CSR11[13:13]
}

DS_txRegs&
DS_txRegs::settxdrvcalpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.txdrvcalpwrdb());	//CSR11[12:12]
	return *this;
}
uint
DS_txRegs::gettxdrvcalpwrdb(){
	return get_csr_bits(REG_INFO.txdrvcalpwrdb());	//CSR11[12:12]
}

DS_txRegs&
DS_txRegs::settxtappwrdb(uint val){
	fill_csr_bits(val,REG_INFO.txtappwrdb());	//CSR11[7:0]
	return *this;
}
uint
DS_txRegs::gettxtappwrdb(){
	return get_csr_bits(REG_INFO.txtappwrdb());	//CSR11[7:0]
}

DS_txRegs&
DS_txRegs::settxcpdetswapi(uint val){
	fill_csr_bits(val,REG_INFO.txcpdetswapi());	//CSR12[15:15]
	return *this;
}
uint
DS_txRegs::gettxcpdetswapi(){
	return get_csr_bits(REG_INFO.txcpdetswapi());	//CSR12[15:15]
}

DS_txRegs&
DS_txRegs::settxcpdetswapq(uint val){
	fill_csr_bits(val,REG_INFO.txcpdetswapq());	//CSR12[14:14]
	return *this;
}
uint
DS_txRegs::gettxcpdetswapq(){
	return get_csr_bits(REG_INFO.txcpdetswapq());	//CSR12[14:14]
}

DS_txRegs&
DS_txRegs::settxcpdetiqmode(uint val){
	fill_csr_bits(val,REG_INFO.txcpdetiqmode());	//CSR12[13:13]
	return *this;
}
uint
DS_txRegs::gettxcpdetiqmode(){
	return get_csr_bits(REG_INFO.txcpdetiqmode());	//CSR12[13:13]
}

DS_txRegs&
DS_txRegs::settxcpdetiqpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.txcpdetiqpwrdb());	//CSR12[12:12]
	return *this;
}
uint
DS_txRegs::gettxcpdetiqpwrdb(){
	return get_csr_bits(REG_INFO.txcpdetiqpwrdb());	//CSR12[12:12]
}

DS_txRegs&
DS_txRegs::settxdrvregbleedb(uint val){
	fill_csr_bits(val,REG_INFO.txdrvregbleedb());	//CSR12[6:6]
	return *this;
}
uint
DS_txRegs::gettxdrvregbleedb(){
	return get_csr_bits(REG_INFO.txdrvregbleedb());	//CSR12[6:6]
}

DS_txRegs&
DS_txRegs::settxdrvregdpmen(uint val){
	fill_csr_bits(val,REG_INFO.txdrvregdpmen());	//CSR12[5:5]
	return *this;
}
uint
DS_txRegs::gettxdrvregdpmen(){
	return get_csr_bits(REG_INFO.txdrvregdpmen());	//CSR12[5:5]
}

DS_txRegs&
DS_txRegs::settxdrvreglvl(uint val){
	fill_csr_bits(val,REG_INFO.txdrvreglvl());	//CSR12[4:0]
	return *this;
}
uint
DS_txRegs::gettxdrvreglvl(){
	return get_csr_bits(REG_INFO.txdrvreglvl());	//CSR12[4:0]
}

DS_txRegs&
DS_txRegs::settxdrvampctrl(uint val){
	fill_csr_bits(val,REG_INFO.txdrvampctrl());	//CSR13[12:9]
	return *this;
}
uint
DS_txRegs::gettxdrvampctrl(){
	return get_csr_bits(REG_INFO.txdrvampctrl());	//CSR13[12:9]
}

DS_txRegs&
DS_txRegs::settxdrvswctrl(uint val){
	fill_csr_bits(val,REG_INFO.txdrvswctrl());	//CSR13[7:7]
	return *this;
}
uint
DS_txRegs::gettxdrvswctrl(){
	return get_csr_bits(REG_INFO.txdrvswctrl());	//CSR13[7:7]
}

DS_txRegs&
DS_txRegs::settxdrvtapinv(uint val){
	fill_csr_bits(val,REG_INFO.txdrvtapinv());	//CSR13[4:0]
	return *this;
}
uint
DS_txRegs::gettxdrvtapinv(){
	return get_csr_bits(REG_INFO.txdrvtapinv());	//CSR13[4:0]
}

DS_txRegs&
DS_txRegs::settxdrvcalhisel(uint val){
	fill_csr_bits(val,REG_INFO.txdrvcalhisel());	//CSR14[15:15]
	return *this;
}
uint
DS_txRegs::gettxdrvcalhisel(){
	return get_csr_bits(REG_INFO.txdrvcalhisel());	//CSR14[15:15]
}

DS_txRegs&
DS_txRegs::settxdrvcallosel(uint val){
	fill_csr_bits(val,REG_INFO.txdrvcallosel());	//CSR14[14:14]
	return *this;
}
uint
DS_txRegs::gettxdrvcallosel(){
	return get_csr_bits(REG_INFO.txdrvcallosel());	//CSR14[14:14]
}

DS_txRegs&
DS_txRegs::settxdrvcalpsel(uint val){
	fill_csr_bits(val,REG_INFO.txdrvcalpsel());	//CSR14[13:13]
	return *this;
}
uint
DS_txRegs::gettxdrvcalpsel(){
	return get_csr_bits(REG_INFO.txdrvcalpsel());	//CSR14[13:13]
}

DS_txRegs&
DS_txRegs::settxdrvcalmsel(uint val){
	fill_csr_bits(val,REG_INFO.txdrvcalmsel());	//CSR14[12:12]
	return *this;
}
uint
DS_txRegs::gettxdrvcalmsel(){
	return get_csr_bits(REG_INFO.txdrvcalmsel());	//CSR14[12:12]
}

DS_txRegs&
DS_txRegs::settxdrvotbpctrl(uint val){
	fill_csr_bits(val,REG_INFO.txdrvotbpctrl());	//CSR14[11:10]
	return *this;
}
uint
DS_txRegs::gettxdrvotbpctrl(){
	return get_csr_bits(REG_INFO.txdrvotbpctrl());	//CSR14[11:10]
}

DS_txRegs&
DS_txRegs::settxdrvotbmctrl(uint val){
	fill_csr_bits(val,REG_INFO.txdrvotbmctrl());	//CSR14[9:8]
	return *this;
}
uint
DS_txRegs::gettxdrvotbmctrl(){
	return get_csr_bits(REG_INFO.txdrvotbmctrl());	//CSR14[9:8]
}

DS_txRegs&
DS_txRegs::settxtopotbctrl(uint val){
	fill_csr_bits(val,REG_INFO.txtopotbctrl());	//CSR14[7:6]
	return *this;
}
uint
DS_txRegs::gettxtopotbctrl(){
	return get_csr_bits(REG_INFO.txtopotbctrl());	//CSR14[7:6]
}

DS_txRegs&
DS_txRegs::setpwrsqtxquiet(uint val){
	fill_csr_bits(val,REG_INFO.pwrsqtxquiet());	//CSR14[5:5]
	return *this;
}
uint
DS_txRegs::getpwrsqtxquiet(){
	return get_csr_bits(REG_INFO.pwrsqtxquiet());	//CSR14[5:5]
}

uint
DS_txRegs::gettxquietstatus(){
	return get_csr_bits(REG_INFO.txquietstatus());	//CSR14[4:4]
}

DS_txRegs&
DS_txRegs::settxeeepwrdbsel(uint val){
	fill_csr_bits(val,REG_INFO.txeeepwrdbsel());	//CSR14[3:0]
	return *this;
}
uint
DS_txRegs::gettxeeepwrdbsel(){
	return get_csr_bits(REG_INFO.txeeepwrdbsel());	//CSR14[3:0]
}

DS_txRegs&
DS_txRegs::settxdrvcalstart(uint val){
	fill_csr_bits(val,REG_INFO.txdrvcalstart());	//CSR15[15:15]
	return *this;
}
uint
DS_txRegs::gettxdrvcalstart(){
	return get_csr_bits(REG_INFO.txdrvcalstart());	//CSR15[15:15]
}

uint
DS_txRegs::getdstxlowoffout(){
	return get_csr_bits(REG_INFO.dstxlowoffout());	//CSR15[14:14]
}

DS_txRegs&
DS_txRegs::settxdrvcaldir(uint val){
	fill_csr_bits(val,REG_INFO.txdrvcaldir());	//CSR15[13:13]
	return *this;
}
uint
DS_txRegs::gettxdrvcaldir(){
	return get_csr_bits(REG_INFO.txdrvcaldir());	//CSR15[13:13]
}

DS_txRegs&
DS_txRegs::settxcalmode(uint val){
	fill_csr_bits(val,REG_INFO.txcalmode());	//CSR15[11:11]
	return *this;
}
uint
DS_txRegs::gettxcalmode(){
	return get_csr_bits(REG_INFO.txcalmode());	//CSR15[11:11]
}

DS_txRegs&
DS_txRegs::settxslicemode(uint val){
	fill_csr_bits(val,REG_INFO.txslicemode());	//CSR15[10:10]
	return *this;
}
uint
DS_txRegs::gettxslicemode(){
	return get_csr_bits(REG_INFO.txslicemode());	//CSR15[10:10]
}

DS_txRegs&
DS_txRegs::settxiqofstmode(uint val){
	fill_csr_bits(val,REG_INFO.txiqofstmode());	//CSR15[9:9]
	return *this;
}
uint
DS_txRegs::gettxiqofstmode(){
	return get_csr_bits(REG_INFO.txiqofstmode());	//CSR15[9:9]
}

DS_txRegs&
DS_txRegs::settxcaldeskewbp(uint val){
	fill_csr_bits(val,REG_INFO.txcaldeskewbp());	//CSR15[8:8]
	return *this;
}
uint
DS_txRegs::gettxcaldeskewbp(){
	return get_csr_bits(REG_INFO.txcaldeskewbp());	//CSR15[8:8]
}

DS_txRegs&
DS_txRegs::settxcaldrvregbp(uint val){
	fill_csr_bits(val,REG_INFO.txcaldrvregbp());	//CSR15[7:7]
	return *this;
}
uint
DS_txRegs::gettxcaldrvregbp(){
	return get_csr_bits(REG_INFO.txcaldrvregbp());	//CSR15[7:7]
}

DS_txRegs&
DS_txRegs::settxcalpredrvregbp(uint val){
	fill_csr_bits(val,REG_INFO.txcalpredrvregbp());	//CSR15[6:6]
	return *this;
}
uint
DS_txRegs::gettxcalpredrvregbp(){
	return get_csr_bits(REG_INFO.txcalpredrvregbp());	//CSR15[6:6]
}

DS_txRegs&
DS_txRegs::settxtermcalmode(uint val){
	fill_csr_bits(val,REG_INFO.txtermcalmode());	//CSR15[5:4]
	return *this;
}
uint
DS_txRegs::gettxtermcalmode(){
	return get_csr_bits(REG_INFO.txtermcalmode());	//CSR15[5:4]
}

DS_txRegs&
DS_txRegs::settxotbrefsel(uint val){
	fill_csr_bits(val,REG_INFO.txotbrefsel());	//CSR15[3:2]
	return *this;
}
uint
DS_txRegs::gettxotbrefsel(){
	return get_csr_bits(REG_INFO.txotbrefsel());	//CSR15[3:2]
}

DS_txRegs&
DS_txRegs::settxotbsel(uint val){
	fill_csr_bits(val,REG_INFO.txotbsel());	//CSR15[1:0]
	return *this;
}
uint
DS_txRegs::gettxotbsel(){
	return get_csr_bits(REG_INFO.txotbsel());	//CSR15[1:0]
}

DS_txRegs&
DS_txRegs::settxcaldrvpmosbp(uint val){
	fill_csr_bits(val,REG_INFO.txcaldrvpmosbp());	//CSR16[15:15]
	return *this;
}
uint
DS_txRegs::gettxcaldrvpmosbp(){
	return get_csr_bits(REG_INFO.txcaldrvpmosbp());	//CSR16[15:15]
}

DS_txRegs&
DS_txRegs::settxcaldrvnmosbp(uint val){
	fill_csr_bits(val,REG_INFO.txcaldrvnmosbp());	//CSR16[14:14]
	return *this;
}
uint
DS_txRegs::gettxcaldrvnmosbp(){
	return get_csr_bits(REG_INFO.txcaldrvnmosbp());	//CSR16[14:14]
}

DS_txRegs&
DS_txRegs::settxdrvregatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.txdrvregatbctrl());	//CSR16[13:11]
	return *this;
}
uint
DS_txRegs::gettxdrvregatbctrl(){
	return get_csr_bits(REG_INFO.txdrvregatbctrl());	//CSR16[13:11]
}

DS_txRegs&
DS_txRegs::setdscalmaxtrans(uint val){
	fill_csr_bits(val,REG_INFO.dscalmaxtrans());	//CSR16[10:7]
	return *this;
}
uint
DS_txRegs::getdscalmaxtrans(){
	return get_csr_bits(REG_INFO.dscalmaxtrans());	//CSR16[10:7]
}

DS_txRegs&
DS_txRegs::settxcallpbkofst2dir(uint val){
	fill_csr_bits(val,REG_INFO.txcallpbkofst2dir());	//CSR16[6:6]
	return *this;
}
uint
DS_txRegs::gettxcallpbkofst2dir(){
	return get_csr_bits(REG_INFO.txcallpbkofst2dir());	//CSR16[6:6]
}

DS_txRegs&
DS_txRegs::settxcallpbkofst1dir(uint val){
	fill_csr_bits(val,REG_INFO.txcallpbkofst1dir());	//CSR16[5:5]
	return *this;
}
uint
DS_txRegs::gettxcallpbkofst1dir(){
	return get_csr_bits(REG_INFO.txcallpbkofst1dir());	//CSR16[5:5]
}

DS_txRegs&
DS_txRegs::settxcallpbkofst2bp(uint val){
	fill_csr_bits(val,REG_INFO.txcallpbkofst2bp());	//CSR16[4:4]
	return *this;
}
uint
DS_txRegs::gettxcallpbkofst2bp(){
	return get_csr_bits(REG_INFO.txcallpbkofst2bp());	//CSR16[4:4]
}

DS_txRegs&
DS_txRegs::settxcallpbkofst1bp(uint val){
	fill_csr_bits(val,REG_INFO.txcallpbkofst1bp());	//CSR16[3:3]
	return *this;
}
uint
DS_txRegs::gettxcallpbkofst1bp(){
	return get_csr_bits(REG_INFO.txcallpbkofst1bp());	//CSR16[3:3]
}

DS_txRegs&
DS_txRegs::settxpredrvcaldir(uint val){
	fill_csr_bits(val,REG_INFO.txpredrvcaldir());	//CSR16[2:2]
	return *this;
}
uint
DS_txRegs::gettxpredrvcaldir(){
	return get_csr_bits(REG_INFO.txpredrvcaldir());	//CSR16[2:2]
}

DS_txRegs&
DS_txRegs::settxtopatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.txtopatbctrl());	//CSR16[1:0]
	return *this;
}
uint
DS_txRegs::gettxtopatbctrl(){
	return get_csr_bits(REG_INFO.txtopatbctrl());	//CSR16[1:0]
}

DS_txRegs&
DS_txRegs::settxdrvsel1(uint val){
	fill_csr_bits(val,REG_INFO.txdrvsel1());	//CSR17[15:8]
	return *this;
}
uint
DS_txRegs::gettxdrvsel1(){
	return get_csr_bits(REG_INFO.txdrvsel1());	//CSR17[15:8]
}

DS_txRegs&
DS_txRegs::setseg1ctrl23to16(uint val){
	fill_csr_bits(val,REG_INFO.seg1ctrl23to16());	//CSR17[7:0]
	return *this;
}
uint
DS_txRegs::getseg1ctrl23to16(){
	return get_csr_bits(REG_INFO.seg1ctrl23to16());	//CSR17[7:0]
}

DS_txRegs&
DS_txRegs::setseg1ctrl15to0(uint val){
	fill_csr_bits(val,REG_INFO.seg1ctrl15to0());	//CSR18[15:0]
	return *this;
}
uint
DS_txRegs::getseg1ctrl15to0(){
	return get_csr_bits(REG_INFO.seg1ctrl15to0());	//CSR18[15:0]
}

DS_txRegs&
DS_txRegs::settxdrvsel2(uint val){
	fill_csr_bits(val,REG_INFO.txdrvsel2());	//CSR19[15:8]
	return *this;
}
uint
DS_txRegs::gettxdrvsel2(){
	return get_csr_bits(REG_INFO.txdrvsel2());	//CSR19[15:8]
}

DS_txRegs&
DS_txRegs::setseg2ctrl23to16(uint val){
	fill_csr_bits(val,REG_INFO.seg2ctrl23to16());	//CSR19[7:0]
	return *this;
}
uint
DS_txRegs::getseg2ctrl23to16(){
	return get_csr_bits(REG_INFO.seg2ctrl23to16());	//CSR19[7:0]
}

DS_txRegs&
DS_txRegs::setseg2ctrl15to0(uint val){
	fill_csr_bits(val,REG_INFO.seg2ctrl15to0());	//CSR20[15:0]
	return *this;
}
uint
DS_txRegs::getseg2ctrl15to0(){
	return get_csr_bits(REG_INFO.seg2ctrl15to0());	//CSR20[15:0]
}

DS_txRegs&
DS_txRegs::settxdrvsel3(uint val){
	fill_csr_bits(val,REG_INFO.txdrvsel3());	//CSR21[15:8]
	return *this;
}
uint
DS_txRegs::gettxdrvsel3(){
	return get_csr_bits(REG_INFO.txdrvsel3());	//CSR21[15:8]
}

DS_txRegs&
DS_txRegs::setseg3ctrl23to16(uint val){
	fill_csr_bits(val,REG_INFO.seg3ctrl23to16());	//CSR21[7:0]
	return *this;
}
uint
DS_txRegs::getseg3ctrl23to16(){
	return get_csr_bits(REG_INFO.seg3ctrl23to16());	//CSR21[7:0]
}

DS_txRegs&
DS_txRegs::setseg3ctrl15to0(uint val){
	fill_csr_bits(val,REG_INFO.seg3ctrl15to0());	//CSR22[15:0]
	return *this;
}
uint
DS_txRegs::getseg3ctrl15to0(){
	return get_csr_bits(REG_INFO.seg3ctrl15to0());	//CSR22[15:0]
}

DS_txRegs&
DS_txRegs::settxdrvsel4(uint val){
	fill_csr_bits(val,REG_INFO.txdrvsel4());	//CSR23[15:8]
	return *this;
}
uint
DS_txRegs::gettxdrvsel4(){
	return get_csr_bits(REG_INFO.txdrvsel4());	//CSR23[15:8]
}

DS_txRegs&
DS_txRegs::setseg4ctrl23to16(uint val){
	fill_csr_bits(val,REG_INFO.seg4ctrl23to16());	//CSR23[7:0]
	return *this;
}
uint
DS_txRegs::getseg4ctrl23to16(){
	return get_csr_bits(REG_INFO.seg4ctrl23to16());	//CSR23[7:0]
}

DS_txRegs&
DS_txRegs::setseg4ctrl15to0(uint val){
	fill_csr_bits(val,REG_INFO.seg4ctrl15to0());	//CSR24[15:0]
	return *this;
}
uint
DS_txRegs::getseg4ctrl15to0(){
	return get_csr_bits(REG_INFO.seg4ctrl15to0());	//CSR24[15:0]
}

uint
DS_txRegs::gettxphsval(){
	return get_csr_bits(REG_INFO.txphsval());	//CSR25[14:8]
}

DS_txRegs&
DS_txRegs::setnmoscalconf(uint val){
	fill_csr_bits(val,REG_INFO.nmoscalconf());	//CSR25[7:4]
	return *this;
}
uint
DS_txRegs::getnmoscalconf(){
	return get_csr_bits(REG_INFO.nmoscalconf());	//CSR25[7:4]
}

DS_txRegs&
DS_txRegs::setpmoscalconf(uint val){
	fill_csr_bits(val,REG_INFO.pmoscalconf());	//CSR25[3:0]
	return *this;
}
uint
DS_txRegs::getpmoscalconf(){
	return get_csr_bits(REG_INFO.pmoscalconf());	//CSR25[3:0]
}

DS_txRegs&
DS_txRegs::settxspare(uint val){
	fill_csr_bits(val,REG_INFO.txspare());	//CSR26[15:8]
	return *this;
}
uint
DS_txRegs::gettxspare(){
	return get_csr_bits(REG_INFO.txspare());	//CSR26[15:8]
}

DS_txRegs&
DS_txRegs::settxdigspare(uint val){
	fill_csr_bits(val,REG_INFO.txdigspare());	//CSR26[7:2]
	return *this;
}
uint
DS_txRegs::gettxdigspare(){
	return get_csr_bits(REG_INFO.txdigspare());	//CSR26[7:2]
}

DS_txRegs&
DS_txRegs::settxdrvcaldndir(uint val){
	fill_csr_bits(val,REG_INFO.txdrvcaldndir());	//CSR26[1:1]
	return *this;
}
uint
DS_txRegs::gettxdrvcaldndir(){
	return get_csr_bits(REG_INFO.txdrvcaldndir());	//CSR26[1:1]
}

DS_txRegs&
DS_txRegs::settxdrvcalupdir(uint val){
	fill_csr_bits(val,REG_INFO.txdrvcalupdir());	//CSR26[0:0]
	return *this;
}
uint
DS_txRegs::gettxdrvcalupdir(){
	return get_csr_bits(REG_INFO.txdrvcalupdir());	//CSR26[0:0]
}

uint
DS_txRegs::gettxdrvcaldone(){
	return get_csr_bits(REG_INFO.txdrvcaldone());	//CSR27[15:15]
}

uint
DS_txRegs::gettxtapmapdone(){
	return get_csr_bits(REG_INFO.txtapmapdone());	//CSR27[14:14]
}

DS_txRegs&
DS_txRegs::settxdrvncaldn(uint val){
	fill_csr_bits(val,REG_INFO.txdrvncaldn());	//CSR27[11:6]
	return *this;
}
uint
DS_txRegs::gettxdrvncaldn(){
	return get_csr_bits(REG_INFO.txdrvncaldn());	//CSR27[11:6]
}

DS_txRegs&
DS_txRegs::settxdrvncalup(uint val){
	fill_csr_bits(val,REG_INFO.txdrvncalup());	//CSR27[5:0]
	return *this;
}
uint
DS_txRegs::gettxdrvncalup(){
	return get_csr_bits(REG_INFO.txdrvncalup());	//CSR27[5:0]
}

uint
DS_txRegs::gettxiqofstff1(){
	return get_csr_bits(REG_INFO.txiqofstff1());	//CSR28[13:8]
}

uint
DS_txRegs::gettxiqofstff2(){
	return get_csr_bits(REG_INFO.txiqofstff2());	//CSR28[5:0]
}

uint
DS_txRegs::gettxiqofstff3(){
	return get_csr_bits(REG_INFO.txiqofstff3());	//CSR29[13:8]
}

uint
DS_txRegs::gettxiqofstffavg(){
	return get_csr_bits(REG_INFO.txiqofstffavg());	//CSR29[5:0]
}

DS_txRegs&
DS_txRegs::settxclkregcalrefsel(uint val){
	fill_csr_bits(val,REG_INFO.txclkregcalrefsel());	//CSR30[13:8]
	return *this;
}
uint
DS_txRegs::gettxclkregcalrefsel(){
	return get_csr_bits(REG_INFO.txclkregcalrefsel());	//CSR30[13:8]
}

DS_txRegs&
DS_txRegs::settxdrvregcalrefsel(uint val){
	fill_csr_bits(val,REG_INFO.txdrvregcalrefsel());	//CSR30[5:0]
	return *this;
}
uint
DS_txRegs::gettxdrvregcalrefsel(){
	return get_csr_bits(REG_INFO.txdrvregcalrefsel());	//CSR30[5:0]
}

DS_txRegs&
DS_txRegs::settxcaltimervalue(uint val){
	fill_csr_bits(val,REG_INFO.txcaltimervalue());	//CSR31[14:5]
	return *this;
}
uint
DS_txRegs::gettxcaltimervalue(){
	return get_csr_bits(REG_INFO.txcaltimervalue());	//CSR31[14:5]
}

DS_txRegs&
DS_txRegs::settxcaltimerdivvalue(uint val){
	fill_csr_bits(val,REG_INFO.txcaltimerdivvalue());	//CSR31[4:2]
	return *this;
}
uint
DS_txRegs::gettxcaltimerdivvalue(){
	return get_csr_bits(REG_INFO.txcaltimerdivvalue());	//CSR31[4:2]
}

DS_txRegs&
DS_txRegs::settxcaltimerdiven(uint val){
	fill_csr_bits(val,REG_INFO.txcaltimerdiven());	//CSR31[1:1]
	return *this;
}
uint
DS_txRegs::gettxcaltimerdiven(){
	return get_csr_bits(REG_INFO.txcaltimerdiven());	//CSR31[1:1]
}

DS_txRegs&
DS_txRegs::settxcaltimerstop(uint val){
	fill_csr_bits(val,REG_INFO.txcaltimerstop());	//CSR31[0:0]
	return *this;
}
uint
DS_txRegs::gettxcaltimerstop(){
	return get_csr_bits(REG_INFO.txcaltimerstop());	//CSR31[0:0]
}

DS_txRegs&
DS_txRegs::settxdrvregvrefrng(uint val){
	fill_csr_bits(val,REG_INFO.txdrvregvrefrng());	//CSR32[15:14]
	return *this;
}
uint
DS_txRegs::gettxdrvregvrefrng(){
	return get_csr_bits(REG_INFO.txdrvregvrefrng());	//CSR32[15:14]
}

DS_txRegs&
DS_txRegs::settxpredrvregvrefrng(uint val){
	fill_csr_bits(val,REG_INFO.txpredrvregvrefrng());	//CSR32[13:12]
	return *this;
}
uint
DS_txRegs::gettxpredrvregvrefrng(){
	return get_csr_bits(REG_INFO.txpredrvregvrefrng());	//CSR32[13:12]
}

DS_txRegs&
DS_txRegs::settxpredrvreglvl(uint val){
	fill_csr_bits(val,REG_INFO.txpredrvreglvl());	//CSR32[11:7]
	return *this;
}
uint
DS_txRegs::gettxpredrvreglvl(){
	return get_csr_bits(REG_INFO.txpredrvreglvl());	//CSR32[11:7]
}

DS_txRegs&
DS_txRegs::settxdrvreginrushpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.txdrvreginrushpwrdb());	//CSR32[6:6]
	return *this;
}
uint
DS_txRegs::gettxdrvreginrushpwrdb(){
	return get_csr_bits(REG_INFO.txdrvreginrushpwrdb());	//CSR32[6:6]
}

DS_txRegs&
DS_txRegs::settxpredrvreginrushpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.txpredrvreginrushpwrdb());	//CSR32[5:5]
	return *this;
}
uint
DS_txRegs::gettxpredrvreginrushpwrdb(){
	return get_csr_bits(REG_INFO.txpredrvreginrushpwrdb());	//CSR32[5:5]
}

DS_txRegs&
DS_txRegs::settxpredrvregpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.txpredrvregpwrdb());	//CSR32[4:4]
	return *this;
}
uint
DS_txRegs::gettxpredrvregpwrdb(){
	return get_csr_bits(REG_INFO.txpredrvregpwrdb());	//CSR32[4:4]
}

DS_txRegs&
DS_txRegs::settxpredrvregatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.txpredrvregatbctrl());	//CSR32[3:1]
	return *this;
}
uint
DS_txRegs::gettxpredrvregatbctrl(){
	return get_csr_bits(REG_INFO.txpredrvregatbctrl());	//CSR32[3:1]
}

DS_txRegs&
DS_txRegs::settxerrinjen(uint val){
	fill_csr_bits(val,REG_INFO.txerrinjen());	//CSR33[15:15]
	return *this;
}
uint
DS_txRegs::gettxerrinjen(){
	return get_csr_bits(REG_INFO.txerrinjen());	//CSR33[15:15]
}

DS_txRegs&
DS_txRegs::settxerrinjmode(uint val){
	fill_csr_bits(val,REG_INFO.txerrinjmode());	//CSR33[14:14]
	return *this;
}
uint
DS_txRegs::gettxerrinjmode(){
	return get_csr_bits(REG_INFO.txerrinjmode());	//CSR33[14:14]
}

DS_txRegs&
DS_txRegs::settxerrinjpttn(uint val){
	fill_csr_bits(val,REG_INFO.txerrinjpttn());	//CSR33[13:12]
	return *this;
}
uint
DS_txRegs::gettxerrinjpttn(){
	return get_csr_bits(REG_INFO.txerrinjpttn());	//CSR33[13:12]
}

DS_txRegs&
DS_txRegs::settxerrinjstart(uint val){
	fill_csr_bits(val,REG_INFO.txerrinjstart());	//CSR33[5:5]
	return *this;
}
uint
DS_txRegs::gettxerrinjstart(){
	return get_csr_bits(REG_INFO.txerrinjstart());	//CSR33[5:5]
}

DS_txRegs&
DS_txRegs::settxerrinjintvl(uint val){
	fill_csr_bits(val,REG_INFO.txerrinjintvl());	//CSR33[4:0]
	return *this;
}
uint
DS_txRegs::gettxerrinjintvl(){
	return get_csr_bits(REG_INFO.txerrinjintvl());	//CSR33[4:0]
}

DS_txRegs&
DS_txRegs::settxerrinjctrl(uint val){
	fill_csr_bits(val,REG_INFO.txerrinjctrl());	//CSR34[15:0]
	return *this;
}
uint
DS_txRegs::gettxerrinjctrl(){
	return get_csr_bits(REG_INFO.txerrinjctrl());	//CSR34[15:0]
}

DS_txRegs&
DS_txRegs::settxrxserlpbkcalen(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbkcalen());	//CSR35[15:15]
	return *this;
}
uint
DS_txRegs::gettxrxserlpbkcalen(){
	return get_csr_bits(REG_INFO.txrxserlpbkcalen());	//CSR35[15:15]
}

DS_txRegs&
DS_txRegs::settxrxserlpbkotbsel(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbkotbsel());	//CSR35[13:12]
	return *this;
}
uint
DS_txRegs::gettxrxserlpbkotbsel(){
	return get_csr_bits(REG_INFO.txrxserlpbkotbsel());	//CSR35[13:12]
}

DS_txRegs&
DS_txRegs::settxrxserlpbken(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbken());	//CSR35[11:11]
	return *this;
}
uint
DS_txRegs::gettxrxserlpbken(){
	return get_csr_bits(REG_INFO.txrxserlpbken());	//CSR35[11:11]
}

DS_txRegs&
DS_txRegs::settxrxserlpbkgainsel(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbkgainsel());	//CSR35[10:10]
	return *this;
}
uint
DS_txRegs::gettxrxserlpbkgainsel(){
	return get_csr_bits(REG_INFO.txrxserlpbkgainsel());	//CSR35[10:10]
}

DS_txRegs&
DS_txRegs::settxrxserlpbksel(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbksel());	//CSR35[9:9]
	return *this;
}
uint
DS_txRegs::gettxrxserlpbksel(){
	return get_csr_bits(REG_INFO.txrxserlpbksel());	//CSR35[9:9]
}

DS_txRegs&
DS_txRegs::settxrxserlpbksupatbsel(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbksupatbsel());	//CSR35[8:7]
	return *this;
}
uint
DS_txRegs::gettxrxserlpbksupatbsel(){
	return get_csr_bits(REG_INFO.txrxserlpbksupatbsel());	//CSR35[8:7]
}

DS_txRegs&
DS_txRegs::settxrxserlpbkatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbkatbctrl());	//CSR35[6:5]
	return *this;
}
uint
DS_txRegs::gettxrxserlpbkatbctrl(){
	return get_csr_bits(REG_INFO.txrxserlpbkatbctrl());	//CSR35[6:5]
}

DS_txRegs&
DS_txRegs::settxrxserlpbkdpm(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbkdpm());	//CSR35[4:3]
	return *this;
}
uint
DS_txRegs::gettxrxserlpbkdpm(){
	return get_csr_bits(REG_INFO.txrxserlpbkdpm());	//CSR35[4:3]
}

DS_txRegs&
DS_txRegs::settxrxserlpbkdpmen(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbkdpmen());	//CSR35[2:1]
	return *this;
}
uint
DS_txRegs::gettxrxserlpbkdpmen(){
	return get_csr_bits(REG_INFO.txrxserlpbkdpmen());	//CSR35[2:1]
}

DS_txRegs&
DS_txRegs::settxrxserlpbkgn1(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbkgn1());	//CSR36[12:10]
	return *this;
}
uint
DS_txRegs::gettxrxserlpbkgn1(){
	return get_csr_bits(REG_INFO.txrxserlpbkgn1());	//CSR36[12:10]
}

DS_txRegs&
DS_txRegs::settxrxserlpbkgn2(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbkgn2());	//CSR36[7:5]
	return *this;
}
uint
DS_txRegs::gettxrxserlpbkgn2(){
	return get_csr_bits(REG_INFO.txrxserlpbkgn2());	//CSR36[7:5]
}

DS_txRegs&
DS_txRegs::settxrxserlpbkgn3(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbkgn3());	//CSR36[2:0]
	return *this;
}
uint
DS_txRegs::gettxrxserlpbkgn3(){
	return get_csr_bits(REG_INFO.txrxserlpbkgn3());	//CSR36[2:0]
}

DS_txRegs&
DS_txRegs::settxrxserlpbkofst1(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbkofst1());	//CSR37[14:10]
	return *this;
}
uint
DS_txRegs::gettxrxserlpbkofst1(){
	return get_csr_bits(REG_INFO.txrxserlpbkofst1());	//CSR37[14:10]
}

DS_txRegs&
DS_txRegs::settxrxserlpbkofst2(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbkofst2());	//CSR37[9:5]
	return *this;
}
uint
DS_txRegs::gettxrxserlpbkofst2(){
	return get_csr_bits(REG_INFO.txrxserlpbkofst2());	//CSR37[9:5]
}

DS_txRegs&
DS_txRegs::settxrxserlpbkofst3(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbkofst3());	//CSR37[4:0]
	return *this;
}
uint
DS_txRegs::gettxrxserlpbkofst3(){
	return get_csr_bits(REG_INFO.txrxserlpbkofst3());	//CSR37[4:0]
}

DS_txRegs&
DS_txRegs::settxrxserlpbkltrim1(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbkltrim1());	//CSR38[11:8]
	return *this;
}
uint
DS_txRegs::gettxrxserlpbkltrim1(){
	return get_csr_bits(REG_INFO.txrxserlpbkltrim1());	//CSR38[11:8]
}

DS_txRegs&
DS_txRegs::settxrxserlpbkltrim2(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbkltrim2());	//CSR38[7:4]
	return *this;
}
uint
DS_txRegs::gettxrxserlpbkltrim2(){
	return get_csr_bits(REG_INFO.txrxserlpbkltrim2());	//CSR38[7:4]
}

E_HILINK_REGISTER_TYPE DS_txRegs::getType()
{
	return HILINK_PERLANE_REGISTER;
}
