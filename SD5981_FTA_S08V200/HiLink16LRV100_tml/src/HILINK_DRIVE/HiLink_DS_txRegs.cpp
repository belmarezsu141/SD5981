#include <HILINK_DRIVE/HiLink_DS_txRegs.h>
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
		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
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
	return HILINK_LANE_NUM;
}

uint
DS_txRegs::getAddressMapToHiLink(int csrIndex){
	if(csrIndex>=DS_TX_CSR_NUM){
		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	return (uint)(0x4000 | (broadcast << 13) | (sliceID << 9) | ((uint)/*SUBBLOCKID.*/0 << 7) | csrIndex << 1);
	return 0;
}


uint&
DS_txRegs::get_csr(uint csrIndex){
	if(csrIndex>=DS_TX_CSR_NUM){
		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	return csr[csrIndex];
}

void
DS_txRegs::get_default_MacroLaneID(T_MacroLaneID& id){
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

E_HILINK_REGISTER_TYPE
DS_txRegs::getType(){
	return HILINK_PERLANE_REGISTER;
}
///////////////////////////////////////////////////////////////////////////


	/// Transmit path power down control. Active low. This pin will gate other analog power down pins. Defaults have been chosen to ensure TX default state is ON.
	/// 0 = Powers down all related TX circuitry and forces a power down values on TXDRVREGPWRDB,TXCPPWRDB,TXDRVDATDEPCOMPPWRDB,TXDRVCALPWRDB,TXTAPPWRDB[7:0],TXDRVSLEWPWRDB. Does not power down the Clock regulator which is used in the Receiver block.
	/// 1 = Powers up all transmit circuitry. Releases force on  TXDRVREGPWRDB,TXCPPWRDB, TXDRVDATDEPCOMPPWRDB,TXDRVCALPWRDB,TXTAPPWRDB[7:0],TXDRVSLEWPWRDB.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txpwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{0,"txpwrdb",15,15}
	};
	return reg;
}

	/// txcp_wordclk16b32b divider selection
	/// 0 = divider 8 for 16b
	/// 1 = divider 16 for 32b
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txclk_16b32b_sel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{0,"txclk_16b32b_sel",14,14}
	};
	return reg;
}

	/// txcp_wordclk16b32b power down signal
	/// 0 = power down
	/// 1 = enable
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txclk_16b32b_pwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{0,"txclk_16b32b_pwrdb",13,13}
	};
	return reg;
}

	/// Regulator (txclk_vreg and txdrv_vreg) output voltage level
	/// 000 = 0.83V
	/// 001 = 0.86V
	/// 010 = 0.90V(default)
	/// 011 = 0.95V
	/// 100 = 1.01V
	/// 101 = 1.03V
	/// 110 = 1.06V
	/// 111 = 1.08V
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_clkregs_level(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{0,"tx_clkregs_level",12,10}
	};
	return reg;
}

	/// The second pre-cursor of the TX driver FIR. Used for pre-emphasis control. A signed magnitude value.
	/// Only when CSR34_TXDRV_MAP_SEL  is configured to 1, the register is valid.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txfirpre2(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{0,"txfirpre2",9,5}
	};
	return reg;
}

	/// The first pre-cursor of the TX driver FIR. Used for pre-emphasis control.
	/// When CSR34_TXDRV_MAP_SEL and CSR48_PCIE_SAS_PIN_EN were configured to 0, the regsiter is the unsigned value, only when  CSR34_TXDRV_MAP_SEL  is configured to 1, the register is the signed value.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txfirpre1(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{0,"txfirpre1",4,0}
	};
	return reg;
}

	/// The main cursor of the TX driver FIR. Used for pre-emphasis control. A binary value.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txfirmain(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{1,"txfirmain",15,10}
	};
	return reg;
}

	/// The first post-cursor of the TX driver FIR. Used for pre-emphasis control.
	/// When CSR34_TXDRV_MAP_SEL and CSR48_PCIE_SAS_PIN_EN were configured to 0, the regsiter is the unsigned value, only when  CSR34_TXDRV_MAP_SEL  is configured to 1, the register is the signed value.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txfirpost1(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{1,"txfirpost1",9,5}
	};
	return reg;
}

	/// The second post-cursor of the TX driver FIR. Used for pre-emphasis control. A signed magnitude value.
	/// Only when CSR34_TXDRV_MAP_SEL  is configured to 1, the register is valid.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txfirpost2(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{1,"txfirpost2",4,0}
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

	/// TX data width select.
	/// 000 = 16 bit parallel interface.
	/// 001 = 20 bit parallel interface .
	/// 010 = 32 bit interface.
	/// 011 = 40 bit interface.
	/// 1xx = Reserved.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdwidth(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{2,"txdwidth",14,12}
	};
	return reg;
}

	/// TX bit rate mode:
	/// 00 = full-rate
	/// 01 = 1/2-rate
	/// 10 = 1/4-rate
	/// 11 = 1/8-rate
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txratemode(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{2,"txratemode",11,10}
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
	/// ;11 = Choose the clock derived from one of the clock spines. Note that when this selection is made, self-align mode cannot be used (i.e., TXALIGNMODE[2:0]=000).
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txclksel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{2,"txclksel",7,6}
	};
	return reg;
}

	/// Select the parallel TX data to be sent.
	/// 00 = select core data (i.e., TXD).
	/// 01 = select RX parallel data (parallel loop back). 
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
	/// 0 = 2UI
	/// 1 = 4UI
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
	/// 010 = Copy mode where the RX phase code is copied. 
	/// 011 = Freeze mode the TXPHSWRITE[7:0] is set manually
	/// 100 = Jitter generation for test mode
	/// 101 = Synchronous master mode (TXCLKSEL[1:0] must be set to '11')
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

	/// Select jitter frequency (normal/extended):
	/// 000 = infinite words (doesn't move)/1 word
	/// 001 = 2/2 words
	/// 010 = 3/3 words
	/// 011 = 4/4 words
	/// 100 = 6/5 words
	/// 101 = 8/6 words
	/// 110 = 12/7 words
	/// 111 = 16/8 words
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::jitfreq(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{3,"jitfreq",14,12}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::jitamp(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{3,"jitamp",11,8}
	};
	return reg;
}

	/// Select the k value in calculating the jitter period.
	/// 0 = k=0
	/// 1 = k=1
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::kfactor(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{3,"kfactor",7,7}
	};
	return reg;
}

	/// not used
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::eco_idlemode_sel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{3,"eco_idlemode_sel",6,6}
	};
	return reg;
}

	/// not used
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::eco_tx_detectrx_sel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{3,"eco_tx_detectrx_sel",5,5}
	};
	return reg;
}

	/// The MSB (i.e., PPMGEN[4]) defines the slew rate direction. Remaining bits, i.e., PPMGEN[3:0] define the number of words (normal/extended):
	/// 0000 = infinite/0 words    1000 = infinite/12 words
	/// 0001 = 2/2 words                1001 = infinite/16 words
	/// 0010 = 3/3 words                1010 = infinite/20 words
	/// 0011 = 4/4 words                1011 = infinite/24 words
	/// 0100 = 6/5 words                1100 = infinite/32 words
	/// 0101 = 8/6 words                1101 = infinite/40 words
	/// 0110 = 12/8 words              1110 = infinite/48 words
	/// 0111 = 16/10 words            1111 = infinite/64 words
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::ppmgen(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{3,"ppmgen",4,0}
	};
	return reg;
}

	/// TX phase interpolator control (2's complement number).
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txphswrite(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{4,"txphswrite",15,8}
	};
	return reg;
}

	/// not used
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_tx2rxloopbacksel_eco(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{4,"tx_tx2rxloopbacksel_eco",7,7}
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
	/// 1000 = Custom pattern
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

	/// Driver clock path power control. This is the power down control for the TX phase interpolator and the subsequent cml2cmos converter. It's used in the synchronous master interface mode to power down the TX phase interpolator for power saving purpose.
	/// 0 = Power down driver clock path
	/// 1 = Power up driver clock path
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcppwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{10,"txcppwrdb",15,15}
	};
	return reg;
}

	/// TX and RX Clock path voltage regulator power control:
	/// 0 = Power down driver (and rx) clock path
	/// 1 = Power up driver (and rx) clock path and also tx driver voltage regulator
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txclkregpwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{10,"txclkregpwrdb",14,14}
	};
	return reg;
}

	/// Driver voltage regulator power control:
	/// 0 = Power down driver voltage regulator
	/// 1 = Power up driver voltage regulator
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvregpwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{10,"txdrvregpwrdb",13,13}
	};
	return reg;
}

	/// Driver termination calibration circuitry power control:
	/// 0 = Power down calibration circuitry
	/// 1 = Power up calibration circuitry
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcalpwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{10,"txdrvcalpwrdb",12,12}
	};
	return reg;
}

	/// Driver slew circuitry power control:
	/// 0 = Power down slew control circuitry, (fastest slew)
	/// 1 = Power up slew control circuitry
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvslewpwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{10,"txdrvslewpwrdb",11,11}
	};
	return reg;
}

	/// Data dependant noise compensation power down control.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvdatdepcomppwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{10,"txdrvdatdepcomppwrdb",10,10}
	};
	return reg;
}

	/// Receiver detect circuitry power control:
	/// 0 = Power down receiver detect circuitry
	/// 1 = Power up receiver detect circuitry
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrxdetpwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{10,"txrxdetpwrdb",9,9}
	};
	return reg;
}

	/// txdrvf1sel and txdrvf2sel source controlled signal  when PMA mode is PCIE/SATA
	/// 0 = txdrvf1sel and txdrvf2sel controlled by logic when PMA mode is in PCIE/SATA mode
	/// 1 = txdrvf1sel and txdrvf2sel controlled by register TX_CSR12.TXDRVF1SEL and TX_CSR12.TXDRVF2SEL.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvbypass(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{10,"txdrvbypass",8,8}
	};
	return reg;
}

	/// Driver tap powerdown. Active low.
	/// TXTAPPWRDB[0]=1: Power up FLOATING SEG1; t=-2 (or t=+1)->txfirpre2
	/// TXTAPPWRDB[1]=1: Power up SEG2; t=-1->txfirpre1
	/// TXTAPPWRDB[2]=1: Power up SEG3; t=+1->txfirpost1
	/// TXTAPPWRDB[3]=1: Power up FLOATING SEG4; t=+2 (or t=-1)->txfirpost2
	/// TXTAPPWRDB[4]=1: Power up SEG1; t=0
	/// TXTAPPWRDB[5]=1: Power up SEG2; t=0
	/// TXTAPPWRDB[6]=1: Power up SEG3; t=0
	/// TXTAPPWRDB[7]=1: Power up SEG4; t=0
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txtappwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{10,"txtappwrdb",7,0}
	};
	return reg;
}

	/// the 2 lsb was used and the default value of TXREGSPARE[1:0] is 10.
	/// TXREGSPARE[1:0] indicated Regulator referrence voltage tuning
	/// 00 : 0.717V
	/// 01 : 0.777V
	/// 10 : 0.797V
	/// 11 : 0.827V
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txregspare(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{11,"txregspare",15,8}
	};
	return reg;
}

	/// Amount of (sourcing) regulator current compensation.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txregpatdepsrc(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{11,"txregpatdepsrc",7,3}
	};
	return reg;
}

	/// Regulator output voltage level when Vref_tune is set to 0x10
	/// 000 = 0.83V
	/// 001 = 0.86V
	/// 010 = 0.90V
	/// 011 = 0.95V(default)
	/// 100 = 1.01V
	/// 101 = 1.03V
	/// 110 = 1.06V
	/// 111 = 1.08V
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txregdrvlvl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{11,"txregdrvlvl",2,0}
	};
	return reg;
}

	/// Amount of (sinking) regulator current compensation.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txedgebleed(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{12,"txedgebleed",15,12}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txpassbleed(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{12,"txpassbleed",11,8}
	};
	return reg;
}

	/// TX driver mapping satrt enable, mapping process will satrt when a rising edge of TXDRVSWCTRL detected.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvswctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{12,"txdrvswctrl",7,7}
	};
	return reg;
}

	/// Driver floating tap #1 control:
	/// 0 = Include tap t=-2
	/// 1 = Increase power of tap t=+1. This will double the amount of available t=+1 tap
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvf1sel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{12,"txdrvf1sel",6,6}
	};
	return reg;
}

	/// Driver floating tap #2 control:
	/// 0 = Include tap t=+2
	/// 1 = Increase power of tap t=-1. This will double the amount of available t=-1 tap
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvf2sel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{12,"txdrvf2sel",5,5}
	};
	return reg;
}

	/// TXDRVTAPINV[0]=1: Invert tap FLOATING weight t=-2 (or t=+1)
	/// TXDRVTAPINV[1]=1: Invert tap weight t=-1
	/// TXDRVTAPINV[2]=1: Invert tap weight t=+1
	/// TXDRVTAPINV[3]=1: Invert tap FLOATING weight t=+2 (or t=-1)
	/// TXDRVTAPINV[4]=1: Invert tap weight t=0
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvtapinv(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{12,"txdrvtapinv",4,0}
	};
	return reg;
}

	/// Generate 2.5mA current for pull-up resistance calibration
	/// 0 = Disabled
	/// 1 = Calibrate
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcalhisel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{13,"txdrvcalhisel",15,15}
	};
	return reg;
}

	/// Generate 2.5mA current for pull-done resistance calibration
	/// 0 = Disabled
	/// 1 = Calibrate
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcallosel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{13,"txdrvcallosel",14,14}
	};
	return reg;
}

	/// Calibrate pull-up resistance
	/// 0 = Disabled
	/// 1 = Calibrate
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcalpsel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{13,"txdrvcalpsel",13,13}
	};
	return reg;
}

	/// Calibrate pull-dn resistance
	/// 0 = Disabled
	/// 1 = Calibrate
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcalmsel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{13,"txdrvcalmsel",12,12}
	};
	return reg;
}

	/// Select calibration path (p/m)
	/// 00 = Disabled
	/// 01 = Observe calibration results via tx 'p' port
	/// 10 = Observe  calibration results via tx 'm' port
	/// 11 = Observe LVCC
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvotbpctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{13,"txdrvotbpctrl",11,10}
	};
	return reg;
}

	/// Select calibration reference
	/// 00 = Disabled
	/// 01 = Reference for calibrated pull-up resistance
	/// 10 = Mid-rail
	/// 11 = Reference for calibrated pull-dn resistance
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvotbmctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{13,"txdrvotbmctrl",9,8}
	};
	return reg;
}

	/// monitor RX calibration comparator feedback
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::dstxlowoffpwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{13,"dstxlowoffpwrdb",7,7}
	};
	return reg;
}

	/// This bit is used to control the BIAS receiver test feature. This feature is used to bypass the dataslice bias receivers in order to do isolated parametric testing. Unsuported.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::dstxlowoffcal(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{13,"dstxlowoffcal",6,6}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::dstxlowoffctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{13,"dstxlowoffctrl",5,0}
	};
	return reg;
}

	/// TX driver calibration start control. Used only in automatic and semi-automatic modes.
	/// 0 = Do not start TX driver calibration
	/// 1 = Start TX driver calibration
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcalstart(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{14,"txdrvcalstart",15,15}
	};
	return reg;
}

	/// Not used. This register is hardcoded to read '0'
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::dstxlowoffout(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{14,"dstxlowoffout",14,14}
	};
	return reg;
}

	/// Direction control for calibrating the lowoff comparator for the TX driver.
	/// 0 = positive direction
	/// 1 = negative direction
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcaldir(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{14,"txdrvcaldir",13,13}
	};
	return reg;
}

	/// Calibration voltage output control
	/// 00 = Disabled
	/// 01 = Observe driver calibration output voltage
	/// 10 = Unused
	/// 11 = Observe VSS
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txtopotbctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{14,"txtopotbctrl",12,11}
	};
	return reg;
}

	/// TX driver slew rate control:
	/// When TXDRSLEWPWRDB the driver is to its optimal slew. 
	/// 000 = Fastest or smallest rise and fall times
	/// ��.
	/// 111 = Slowest or longest rise and fall times. This feature is meant to be used only at lower data rates.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvslew(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{14,"txdrvslew",10,8}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvregcalen(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{14,"txdrvregcalen",7,7}
	};
	return reg;
}

	/// Adjust current handling of driver regulator
	/// 0 = More current
	/// 1 = Less current
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvregslicetune(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{14,"txdrvregslicetune",6,6}
	};
	return reg;
}

	/// TX termination calibration mode. Switching from manual mode to auto mode restarts the auto calibration process.
	/// 00 = Auto full TX termination calibration and FFE mapping via FSM
	/// 01 = Only TX termination calibration via FSM
	/// 10 = Only TX FFE mapping via FSM
	/// 11 = Manual termination calibration or FFE mapping via related registers.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txtermcalmode(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{14,"txtermcalmode",5,4}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvtesten(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"txdrvtesten",15,15}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvtestin(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"txdrvtestin",14,14}
	};
	return reg;
}

	/// Select TX driver regulator observation point
	/// 001 = vregout
	/// 010 = vss
	/// 011 = vgp
	/// 100 = hvcc
	/// 101 = vbiasn
	/// 110 = vmir_lf
	/// 111 = vmir_hf
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvregatbctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"txdrvregatbctrl",13,11}
	};
	return reg;
}

	/// Selects pre-mux in front of the low offset comparator.
	/// 00 = Tristate
	/// 01 = RX calibration will use the low offset comparator 
	/// 10 = TX calibration will use the low offset comparator
	/// 11 = DSCLK calibration will use the low offset comparator
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::dslowoffctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"dslowoffctrl",10,9}
	};
	return reg;
}

	/// Select TX clock regulator observation point
	/// 001 = vregout
	/// 010 = vref
	/// 011 = vgp
	/// 100 = vgpc
	/// 101 = vbiasn
	/// 110 = vmir_lf
	/// 111 = vmir_hf
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txclkregatbctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"txclkregatbctrl",8,6}
	};
	return reg;
}

	/// Select TX driver observation point
	/// 00 = Disabled
	/// 01 = P slew voltage
	/// 10 = N slew voltage
	/// 11 = VREG_DRV
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvatbctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"txdrvatbctrl",5,4}
	};
	return reg;
}

	/// Select TX master mirror observation point
	/// 00 = Disabled
	/// 01 = CV output
	/// 10 = HVCC
	/// 11 = CC output
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txmastermiratbctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"txmastermiratbctrl",3,2}
	};
	return reg;
}

	/// Select TX top observation point
	/// 00 = rxdetect vref
	/// 01 = TX regulators atb
	/// 10 = TX master mirror atb
	/// 11 = TX driver atb
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txtopatbctrl(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{15,"txtopatbctrl",1,0}
	};
	return reg;
}

	/// TXDRVSEL[7:0] for TX driver cluster 1.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvsel1(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{16,"txdrvsel1",15,8}
	};
	return reg;
}

	/// Driver cluster 1 slice based control:
	/// [7:5]      = SEGCTRL1[23:21] (slice 8)
	/// [4:2]      = SEGCTRL1[20:18] (slice 7)
	/// [1:0]      = SEGCTRL1[17:16] (part of slice 6)
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::seg1ctrl23to16(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{16,"seg1ctrl23to16",7,0}
	};
	return reg;
}

	/// Driver cluster 1 slice based control:
	/// [15]         = SEGCTRL1[15] (part of slice 6)
	/// [14:12]   = SEGCTRL1[14:12] (slice 5)
	/// [11:9]     = SEGCTRL1[11:9] (slice 4)
	/// [8:6]       = SEGCTRL1[8:6] (slice 3)
	/// [5:3]       = SEGCTRL1[5:3] (slice 2)
	/// [2:0]       = SEGCTRL1[2:0] (slice 1)
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::seg1ctrl15to0(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{17,"seg1ctrl15to0",15,0}
	};
	return reg;
}

	/// TXDRVSEL[15:8] for TX driver cluster 2.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvsel2(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{18,"txdrvsel2",15,8}
	};
	return reg;
}

	/// Driver cluster 2 slice based control:
	/// [7:5]      = SEGCTRL1[23:21] (slice 8)
	/// [4:2]      = SEGCTRL1[20:18] (slice 7)
	/// [1:0]      = SEGCTRL1[17:16] (part of slice 6)
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::seg2ctrl23to16(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{18,"seg2ctrl23to16",7,0}
	};
	return reg;
}

	/// Driver cluster 2 slice based control:
	/// [15]         = SEGCTRL1[15] (part of slice 6)
	/// [14:12]   = SEGCTRL1[14:12] (slice 5)
	/// [11:9]     = SEGCTRL1[11:9] (slice 4)
	/// [8:6]       = SEGCTRL1[8:6] (slice 3)
	/// [5:3]       = SEGCTRL1[5:3] (slice 2)
	/// [2:0]       = SEGCTRL1[2:0] (slice 1)
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::seg2ctrl15to0(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{19,"seg2ctrl15to0",15,0}
	};
	return reg;
}

	/// TXDRVSEL[23:16] for TX driver cluster 3.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvsel3(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{20,"txdrvsel3",15,8}
	};
	return reg;
}

	/// Driver cluster 3 slice based control:
	/// [7:5]      = SEGCTRL1[23:21] (slice 8)
	/// [4:2]      = SEGCTRL1[20:18] (slice 7)
	/// [1:0]      = SEGCTRL1[17:16] (part of slice 6)
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::seg3ctrl23to16(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{20,"seg3ctrl23to16",7,0}
	};
	return reg;
}

	/// Driver cluster 3 slice based control:
	/// [15]         = SEGCTRL1[15] (part of slice 6)
	/// [14:12]   = SEGCTRL1[14:12] (slice 5)
	/// [11:9]     = SEGCTRL1[11:9] (slice 4)
	/// [8:6]       = SEGCTRL1[8:6] (slice 3)
	/// [5:3]       = SEGCTRL1[5:3] (slice 2)
	/// [2:0]       = SEGCTRL1[2:0] (slice 1)
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::seg3ctrl15to0(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{21,"seg3ctrl15to0",15,0}
	};
	return reg;
}

	/// TXDRVSEL[31:24] for TX driver cluster 4.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvsel4(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{22,"txdrvsel4",15,8}
	};
	return reg;
}

	/// Driver cluster 4 slice based control:
	/// [7:5]      = SEGCTRL1[23:21] (slice 8)
	/// [4:2]      = SEGCTRL1[20:18] (slice 7)
	/// [1:0]      = SEGCTRL1[17:16] (part of slice 6)
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::seg4ctrl23to16(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{22,"seg4ctrl23to16",7,0}
	};
	return reg;
}

	/// Driver cluster 2 slice based control:
	/// [15]         = SEGCTRL1[15] (part of slice 6)
	/// [14:12]   = SEGCTRL1[14:12] (slice 5)
	/// [11:9]     = SEGCTRL1[11:9] (slice 4)
	/// [8:6]       = SEGCTRL1[8:6] (slice 3)
	/// [5:3]       = SEGCTRL1[5:3] (slice 2)
	/// [2:0]       = SEGCTRL1[2:0] (slice 1)
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::seg4ctrl15to0(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{23,"seg4ctrl15to0",15,0}
	};
	return reg;
}

	/// This register contains the present binary phase value of the TX phase interpolator.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txphsval(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{24,"txphsval",14,8}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::nmoscalstatus(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{24,"nmoscalstatus",7,4}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pmoscalstatus(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{24,"pmoscalstatus",3,0}
	};
	return reg;
}

	/// the 0-bit as the control signal of:txdrv_cal_replica_en
	/// 0= driver direct calibration
	/// 1= driver replica calibration
	/// the 1-bit as the control signal of txdrv_sliceboost_tune
	/// 0= driver boost tune off
	/// 1= driver boost tune on
	/// the 2 to 7 bit dose not use.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txspare(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{25,"txspare",15,8}
	};
	return reg;
}

	/// Hi-Z and Idle mode switch control for TX.
	/// 0 = idle
	/// 1 = Hi-Z
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_idle_hiz_sw_crg(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{25,"tx_idle_hiz_sw_crg",7,7}
	};
	return reg;
}

	/// For debug. RX detection output mode switch.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_detectrx_sel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{25,"tx_detectrx_sel",6,6}
	};
	return reg;
}

	/// Loopback path select
	/// 0 = data is coming from the bump
	/// 1 = data is not coming from the bump
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_tx2rxloopbacksel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{25,"tx_tx2rxloopbacksel",5,5}
	};
	return reg;
}

	/// all slices of P-driver and M-dirver status controlled by calibration logic or stuck to 0(txdrv_open_enp and txdrv_open_enm)
	/// 0 = all slices of P-driver and M-driver closed
	/// 1 = all slices of P-driver and M-driver status controlled by calibration logic
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrv_open_en(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{25,"txdrv_open_en",4,4}
	};
	return reg;
}

	/// 
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdigspare(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{25,"txdigspare",3,2}
	};
	return reg;
}

	/// Direction control for TX driver down side calibration.
	/// 0 = TBD
	/// 1 = TBD
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcaldndir(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{25,"txdrvcaldndir",1,1}
	};
	return reg;
}

	/// Direction control for TX driver up side calibration.
	/// 0 = TBD
	/// 1 = TBD
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcalupdir(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{25,"txdrvcalupdir",0,0}
	};
	return reg;
}

	/// 0 = TX Driver calibration is still in progress
	/// 1 = TX Driver calibration has completed
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvcaldone(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{26,"txdrvcaldone",15,15}
	};
	return reg;
}

	/// 0 = TX tap mapping is not done
	/// 1 = TX tap mapping is done
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txtapmapdone(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{26,"txtapmapdone",14,14}
	};
	return reg;
}

	/// Result of TX driver down side calibration.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvncaldn(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{26,"txdrvncaldn",11,6}
	};
	return reg;
}

	/// Result of TX driver up side calibration.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrvncalup(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{26,"txdrvncalup",5,0}
	};
	return reg;
}

	/// Stop TX driver calibration timer, for debugging.
	/// 0 = normal
	/// 1 = stop the timer
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcal_timer_stop(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{27,"txcal_timer_stop",14,14}
	};
	return reg;
}

	/// Configuration of the TX driver calibration timer for waiting, which is the cycles of reference clock.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcal_timer_value(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{27,"txcal_timer_value",13,4}
	};
	return reg;
}

	/// Enable the divider in TX driver calibration timer,not available in current design.
	/// 0 = disable
	/// 1 = enable
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcal_timer_div_en(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{27,"txcal_timer_div_en",3,3}
	};
	return reg;
}

	/// Configuration of divider in TX driver calibration timer, for debugging.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txcal_timer_div_value(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{27,"txcal_timer_div_value",2,0}
	};
	return reg;
}

	/// The first post-cursor of the TX driver FIR from the pin 'tx_deemph'. For TX configuration debugging.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_training_firpost1(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{28,"tx_training_firpost1",15,11}
	};
	return reg;
}

	/// The main-cursor of the TX driver FIR from the pin 'tx_deemph'. For TX configuration debugging.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_training_firmain(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{28,"tx_training_firmain",10,5}
	};
	return reg;
}

	/// The first pre-cursor of the TX driver FIR from the pin 'tx_deemph'. For TX configuration debugging.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_training_firpre1(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{28,"tx_training_firpre1",4,0}
	};
	return reg;
}

	/// The full swing of TX driver.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_local_fs(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{29,"tx_local_fs",13,8}
	};
	return reg;
}

	/// The low frequency swing of TX driver.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_local_lf(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{29,"tx_local_lf",5,0}
	};
	return reg;
}

	/// Stop receiver detection timer, for debugging.
	/// 0 = normal
	/// 1 = stop the timer
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::rxdet_timer_stop(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{30,"rxdet_timer_stop",14,14}
	};
	return reg;
}

	/// Configuration of receiver detection timer for receiver detector initialization, which is the cycles of reference clock.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::rxdet_init_timer_value(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{30,"rxdet_init_timer_value",13,4}
	};
	return reg;
}

	/// Configuration of divider in receiver detection timer for receiver detector initialization, for debugging.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::rxdet_init_timer_div_value(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{30,"rxdet_init_timer_div_value",2,0}
	};
	return reg;
}

	/// Configuration of receiver detection timer for receiver detector charge/discharge, which is the cycles of reference clock.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::rxdet_charge_timer_value(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{31,"rxdet_charge_timer_value",13,4}
	};
	return reg;
}

	/// Configuration of divider in receiver detection timer for receiver detector charge/discharge, for debugging.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::rxdet_charge_timer_div_value(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{31,"rxdet_charge_timer_div_value",2,0}
	};
	return reg;
}

	/// Monitor value from pin 'TX_RXDET_EN'.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_rxdet_en_pin_mon(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{32,"tx_rxdet_en_pin_mon",14,14}
	};
	return reg;
}

	/// Indicate the result of receiver detect is valid for read.
	/// 0 = The result of receiver detect is invalid
	/// 1 = The result of receiver detect is valid
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_rxdet_ready(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{32,"tx_rxdet_ready",13,13}
	};
	return reg;
}

	/// The result of receiver detect, valid when 'TX_RXDET_READY' is high
	/// 0 = no  receiver has been connect to local transmitter
	/// 1 = a  receiver has been connect to local transmitter
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_rxdet_out(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{32,"tx_rxdet_out",12,12}
	};
	return reg;
}

	/// Indicate the power status of the analog circuit for receiver detect, for debugging.
	/// 0 = power down the receiver detect circuit
	/// 1 = power on the receiver detect circuit
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_rxdet_pwrdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{32,"tx_rxdet_pwrdb",11,11}
	};
	return reg;
}

	/// Indicate current status of receiver detect, for debuggsing.
	/// 000 = idle
	/// 101 = discharge
	/// 110 = charge
	/// 100 = initial
	/// else = reserved
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_rxdet_mode(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{32,"tx_rxdet_mode",10,8}
	};
	return reg;
}

	/// TX driver FFE configuration start error flag, clear when read.  Error will be assert when the value of pin  'tx_deemph' changed while mapping.
	/// 0 = No error have been detected while TX driver FFE configuration
	/// 1= At lease one error have been detected while TX driver FFE configuration
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_training_start_err(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{32,"tx_training_start_err",5,5}
	};
	return reg;
}

	/// Indicate the polarity of TX driver FFE tap.
	/// 0 = The coefficient of current tap is positive
	/// 1 = The coefficient of current tap is nagitive
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrv_tap_inv(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{32,"txdrv_tap_inv",4,0}
	};
	return reg;
}

	/// Monitor value of pin 'TXDRV_IDLE_EN'.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrv_idle_en_pin_mon(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{33,"txdrv_idle_en_pin_mon",15,15}
	};
	return reg;
}

	/// TX driver IDLE enable,  active high. Only available in PCIe L0 or SAS phyrdy states and pin disabled ('PCIE_SAS_PIN_EN'=0). For debugging.
	/// Note: Set TX driver to idle while TX driver calibration is not permitted.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrv_idle_en(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{33,"txdrv_idle_en",14,14}
	};
	return reg;
}

	/// not used
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrv_open_en_eco(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{33,"txdrv_open_en_eco",13,13}
	};
	return reg;
}

	/// TX driver IDLE enable extra delay control, for debug using.
	/// 0 = IDLE enable arrive to analog 2 txwclk cycles after parallel data
	/// 1 =  IDLE enable arrive to analog 1 txwclk cycles after parallel data
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrv_idle_en_dly(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{33,"txdrv_idle_en_dly",11,11}
	};
	return reg;
}

	/// Select the source of TX PI code to analog.(for C2M application)
	/// 0 = Select PI code from Phase Aligner
	/// 1 = Select External PI code
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::picodein_sel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{33,"picodein_sel",10,10}
	};
	return reg;
}

	/// Indicate TX phase align status
	/// 0 = phase align is still running
	/// 1 = phase align is done
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_phase_align_done(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{33,"tx_phase_align_done",9,9}
	};
	return reg;
}

	/// TX phase align done status clear enable, active high.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_pa_status_clr(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{33,"tx_pa_status_clr",8,8}
	};
	return reg;
}

	/// The threshold of phase align.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_phase_align_thr(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{33,"tx_phase_align_thr",7,0}
	};
	return reg;
}

	/// Force all the slices of driver P to be open.
	/// 0: normal
	/// 1: open
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrv_open_en_p(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{34,"txdrv_open_en_p",15,15}
	};
	return reg;
}

	/// Force all the slices of driver M to be open.
	/// 0: normal
	/// 1: open
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrv_open_en_m(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{34,"txdrv_open_en_m",14,14}
	};
	return reg;
}

	/// TX driver IDLE control bypass enable for debug, active high. For debugging.
	/// 0 = Enable TX driver IDLE control
	/// 1 = Bypass TX driver IDLE control
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrv_idle_bypass(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{34,"txdrv_idle_bypass",13,13}
	};
	return reg;
}

	/// TX data rate and bus width switch bypass enable, for debugging.
	/// 0 = enbale TX data rate and bus width switch
	/// 1 = bypass TX data rate and bus width switch
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_wrate_sw_bypass(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{34,"tx_wrate_sw_bypass",12,12}
	};
	return reg;
}

	/// TX receiver detect enable, active high.  Only available in PCIe L0/L0s/L1 states and pin disabled ('PCIE_SAS_PIN_EN'=0)
	/// Note: Receiver detection while TX driver calibration is not permitted.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_rxdet_en(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{34,"tx_rxdet_en",11,11}
	};
	return reg;
}

	/// Receiver detect threshold(reference voltage) control
	/// 00 = 0.822*Vregdrv
	/// 01 = 0.856*Vregdrv
	/// 10 = 0.890*Vregdrv
	/// 11 = 0.925*Vregdrv
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_rxdet_level(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{34,"tx_rxdet_level",10,9}
	};
	return reg;
}

	/// The delay of idle enable signal adjustment in analog circuit, for debugging.
	/// 000 = No extra delay
	/// 001 = Extra delay 8UI
	/// 010 = Extra delay 16UI
	/// 011 = Extra delay 24UI
	/// 1xx = Extra delay 32UI
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_idle_dly_ana(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{34,"tx_idle_dly_ana",8,6}
	};
	return reg;
}

	/// txoclk source select
	/// 0 = select txoclk to output port 
	/// 1 = select mclk to output port
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txoclk_sel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{34,"txoclk_sel",5,5}
	};
	return reg;
}

	/// Tx driver mapping select, for debug using.
	/// 0 = mapping from registers ('PCIE_SAS_PIN_EN'=0) or from pin  ('PCIE_SAS_PIN_EN'=1)
	/// 1 = mapping always from registers.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrv_map_sel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{34,"txdrv_map_sel",4,4}
	};
	return reg;
}

	/// TX driver tap invert control select, only used when mapping from the pin 'tx_deemph'.
	/// 0 = Force pre1 and  post1 tap to negative value and other taps to positive value
	/// 1 = FFE tap invert controled by TX_CSR12 'TXDRVTAPINV[4:0]'
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrv_tapinv_sel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{34,"txdrv_tapinv_sel",3,3}
	};
	return reg;
}

	/// when data-rate switched, hsclk or mclk source select signal
	/// 0 = 2.5/5G pcie or 1.5/3/6G sata mode, select hsclk0 and mclk0 from clockslice0, when worked in PCIE 8G or SATA 12G mode, select hsclk1 and mclk1 form clockslice1
	/// 1 = 2.5/5G pcie or 1.5/3/6G sata mode, select hsclk1 and mclk1 from clockslice1, when worked in PCIE 8G or SATA 12G mode, select hsclk0 and mclk0 from clockslice0
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pcie_wrate_hsclk_sel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{34,"pcie_wrate_hsclk_sel",2,2}
	};
	return reg;
}

	/// TX termination calibration targe resist value choice.
	/// 00 = revered
	/// 01 = 50 Ohm
	/// 10 = revered
	/// 11 = 45 Ohm
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrv_ressel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{34,"txdrv_ressel",1,0}
	};
	return reg;
}

	/// TX driver slice boost enable
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txdrv_sliceboost_en(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{35,"txdrv_sliceboost_en",13,13}
	};
	return reg;
}

	/// Regulator loading adjust power down;
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::clkreg_selfbleed_pdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{35,"clkreg_selfbleed_pdb",12,12}
	};
	return reg;
}

	/// Regulator loading adjust ;
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::clkreg_selfbleed(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{35,"clkreg_selfbleed",11,8}
	};
	return reg;
}

	/// TX termination calibration results down(N) offset compensate, the MSB is the sign-bit, and the other bits the unsigned binary code. The range from -7 to +7.
	/// Note: the value must configure before tx calibration start
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::ncaldn_offset(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{35,"ncaldn_offset",7,4}
	};
	return reg;
}

	/// TX termination calibration results up(P) offset compensate, the MSB is the sign-bit, and the other bits the unsigned binary code. The range from -7 to +7.
	/// Note: the value must configure before tx calibration start
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::ncalup_offset(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{35,"ncalup_offset",3,0}
	};
	return reg;
}

	/// PCIe/SAS global control block software reset, low active. Only active in PCIe/SAS mode.
	/// 0 = Reset  PCIe/SAS global control block logic.
	/// 1 = Normal operation.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pcie_sas_sw_rstb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{48,"pcie_sas_sw_rstb",15,15}
	};
	return reg;
}

	/// Pin powerState[2:0], datarate[2:0],datawidth[2:0] for global control block,
	/// Pin tx_idle_en, detectrx_en,txdeemph[17:0] for TX_DIG
	/// Pin rxeyediag_start,rxctlepreset[2:0] for RX_DIG enable, 
	/// 0 = Disable
	/// 1 = Enable
	/// Notes: forbid to configure both PSTATE_WRATE_VLD and PCIE_SAS_PIN_EN  register   to  1'b1 .
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pcie_sas_pin_en(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{48,"pcie_sas_pin_en",14,14}
	};
	return reg;
}

	/// The HiLink 15BP supports three main modes: PCIe mode,  SAS and SATA mode. 
	/// 00 = PCIE mode
	/// 01 = SAS and SATA mode
	/// 10 = Normal mode
	/// 11=  Reserved
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pma_mode(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{48,"pma_mode",13,12}
	};
	return reg;
}

	/// Valid for PCIE_SAS_POWER_STATE, PCIE_SAS_DATA_RATE,PCIE_SAS_DATA_WIDTH register configure . Only active in PCIe/SAS mode.
	/// 1: valid
	/// 0: invalid
	/// Notes: forbid to configure both PSTATE_WRATE_VLD and PCIE_SAS_PIN_EN  register   to  1'b1 .
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pstate_wrate_vld(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{48,"pstate_wrate_vld",11,11}
	};
	return reg;
}

	/// Power state parameter configure, active when PSTATE_WRATE_VLD =1 . Only used  in PCIe/SAS mode.
	/// 000 =  PCIe L0 or SAS/SATA PHYRDY state
	/// 001 =  PCIe L0s or SAS/SATA PARTIAL state
	/// 010 =  PCIe L1 state
	/// 100 =  PCIe L2 or SAS/SATA SLUMBE state
	/// others = forbid
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pcie_sas_power_state(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{48,"pcie_sas_power_state",10,8}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pcie_sas_data_rate(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{48,"pcie_sas_data_rate",6,4}
	};
	return reg;
}

	/// Hilink TX/RX ready configure.
	/// Once  hilink initialization is done, configure this register, pin rxtx_status will be assert, TX/RX will  start to receive PCIe/SAS core any control request.(eg.
	///  (1) Power state/data rate/width switch request.
	///  (2) Loss/receiver detect control request. etc.).
	/// 1:  Ready
	/// 0: Not ready.
	/// Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pcie_sas_rxtx_status_rdy(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{48,"pcie_sas_rxtx_status_rdy",3,3}
	};
	return reg;
}

	/// Data width  parameter configure, active when PSTATE_WRATE_VLD =1 . Only used  in PCIe/SAS mode.
	///  Only active in PCIe/SAS mode.
	/// 000 = 16(8,4) bit parallel data
	/// 001 = 20(10,5) bit parallel data
	/// 010 = 32(16,8) bit parallel data
	/// 011 = 40(20,10)bit parallel data
	/// others = forbid
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pcie_sas_data_width(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{48,"pcie_sas_data_width",2,0}
	};
	return reg;
}

	/// Mask power down control for RX signal detect function  in PCIe/SAS mode, high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::rxsigdet_pwrdnb_msk(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{49,"rxsigdet_pwrdnb_msk",15,15}
	};
	return reg;
}

	/// Mask power down control for  Transmit Receiver detection  control in PCIe/SAS mode , high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txrxdet_pwrdnb_msk(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{49,"txrxdet_pwrdnb_msk",14,14}
	};
	return reg;
}

	/// Mask power down control for  HiLink RX Analog  in PCIe/SAS mode, high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::rxpwrdnb_msk(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{49,"rxpwrdnb_msk",13,13}
	};
	return reg;
}

	/// Mask power down control for  HiLink TX Analog in PCIe/SAS mode, high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::txpwrdnb_msk(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{49,"txpwrdnb_msk",12,12}
	};
	return reg;
}

	/// Mask power down control for  DSCLK  all dsclk circuit except spine clock buffer ,regulator and cml2cmos circuit  in PCIe/SAS mode, high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::dsclkgen_pwrdnb_msk(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{49,"dsclkgen_pwrdnb_msk",11,11}
	};
	return reg;
}

	/// Mask power down control for  HiLink analog DSCLK IDAC  in PCIe/SAS mode, high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::dsclk_idac_pwrdnb_msk(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{49,"dsclk_idac_pwrdnb_msk",10,10}
	};
	return reg;
}

	/// Mask  power down control for dsclk idac regulator  in PCIe/SAS mode, high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::dsclk_vregdac_pwrdnb_msk(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{49,"dsclk_vregdac_pwrdnb_msk",9,9}
	};
	return reg;
}

	/// Mask  power down control for Power down dsclk cml2cms regulator in PCIe/SAS mode , high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::dsclk_vregl_pwrdnb_msk(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{49,"dsclk_vregl_pwrdnb_msk",8,8}
	};
	return reg;
}

	/// Mask reset control in RX signal detect  when power state switch happen,high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::rx_sw_sigdet_rstb_msk(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{49,"rx_sw_sigdet_rstb_msk",6,6}
	};
	return reg;
}

	/// Mask cdr reset control in RX when power state switch happen,high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::rx_sw_cdr_rstb_msk(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{49,"rx_sw_cdr_rstb_msk",5,5}
	};
	return reg;
}

	/// Mask reset control in RX when power state switch happen,high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::rx_sw_rstb_msk(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{49,"rx_sw_rstb_msk",4,4}
	};
	return reg;
}

	/// Mask clock control in RX loss detect block, Only active in PCIe/SAS mode.
	/// high active.
	/// 0 = Not mask
	/// 1 = Mask
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::rx_loss_det_clk_en_msk(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{49,"rx_loss_det_clk_en_msk",3,3}
	};
	return reg;
}

	/// Mask rxwordclk enable control when power state switch happen, high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::rx_sw_clk_en_msk(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{49,"rx_sw_clk_en_msk",2,2}
	};
	return reg;
}

	/// Mask txwordclk enable control when power state switch happen,high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_sw_clk_en_msk(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{49,"tx_sw_clk_en_msk",1,1}
	};
	return reg;
}

	/// Mask reset control in TX when power state switch happen,high active. Only active in PCIe/SAS mode.
	/// 0 = Not mask
	/// 1 = Mask
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::tx_sw_rstb_msk(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{49,"tx_sw_rstb_msk",0,0}
	};
	return reg;
}

	/// Divider value for power state switch timer. Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pstate_timer_div_value(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{50,"pstate_timer_div_value",15,12}
	};
	return reg;
}

	/// Time value for power state switch timer. Only active in PCIe/SAS mode.
	/// Note: TX/RX clock stable time  = ( PSTATE_TIMER_DIV_VALUE + 1) * (PSTATE_TIMER_VALUE + 1) * cycle time of hclk clock after power up.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pstate_timer_value(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{50,"pstate_timer_value",9,0}
	};
	return reg;
}

	/// Divider value for DSCLK calibration timeout. Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::dsclk_timer_div_value(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{51,"dsclk_timer_div_value",15,12}
	};
	return reg;
}

	/// Spare configure regiser
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pcie_sas_spare(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{51,"pcie_sas_spare",11,4}
	};
	return reg;
}

	/// Divider value for data rate/width switch timeout. Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::wrate_timer_div_value(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{51,"wrate_timer_div_value",3,0}
	};
	return reg;
}

	/// Time value for DSCLK calibraion timeout. Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::dsclk_timer_value(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{52,"dsclk_timer_value",13,0}
	};
	return reg;
}

	/// Time value for data rate/width switch timeout. Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::wrate_timer_value(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{53,"wrate_timer_value",13,0}
	};
	return reg;
}

	/// Histroy alarm for power state code error. Only active in PCIe/SAS mode,  Clear after
	/// softeware read.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::his_alarm_pstate_code_err(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{54,"his_alarm_pstate_code_err",15,15}
	};
	return reg;
}

	/// Histroy alarm for illegal power state switch. Only active in PCIe/SAS mode. Clear after softeware read.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::his_alarm_pstate_sw_err(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{54,"his_alarm_pstate_sw_err",14,14}
	};
	return reg;
}

	/// History alarm for illegal data rate/width switch, Only active in PCIe/SAS mode.  Clear after softeware read.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::his_alarm_wrate_sw_err(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{54,"his_alarm_wrate_sw_err",13,13}
	};
	return reg;
}

	/// History alarm for power state and rate/width switch at the same time. Only active in PCIe/SAS mode. Clear after softeware read.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::his_alarm_pstate_wrate_err(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{54,"his_alarm_pstate_wrate_err",12,12}
	};
	return reg;
}

	/// History alarm for Only one  power state and rate/width switch request lauch when HiLink status is not ready, Only active in PCIe/SAS mode.  Clear after softeware read.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::his_alarm_one_sw_req_vio(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{54,"his_alarm_one_sw_req_vio",11,11}
	};
	return reg;
}

	/// History alarm for two or more power state and rate/width switch request lauch when HiLink status is not ready, Only active in PCIe/SAS mode.  Clear after softeware read.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::his_alarm_sw_req_drop(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{54,"his_alarm_sw_req_drop",10,10}
	};
	return reg;
}

	/// Alarm for DSCLK calibration timeout in rate/width switch. Only active in PCIe/SAS mode. Clear after softeware read.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::alarm_dsclk_calib_timeout(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{54,"alarm_dsclk_calib_timeout",9,9}
	};
	return reg;
}

	/// Alarm for TX rate/width switch timeout. Only active in PCIe/SAS mode. Clear after softeware read.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::alarm_wrate_txsw_timeout(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{54,"alarm_wrate_txsw_timeout",8,8}
	};
	return reg;
}

	/// Alarm for RX rate/width switch timeout. Only active in PCIe/SAS mode. Clear after softeware read.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::alarm_wrate_rxsw_timeout(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{54,"alarm_wrate_rxsw_timeout",7,7}
	};
	return reg;
}

	/// Status reigster for PCIE_SAS_POWER_STATE[2:0] , PCIE_SAS_DATA_WIDTH[2:0],PCIE_SAS_DATA_RATE[2:0] parameter load done in intialization process, Only active in PCIe/SAS mode,in common mode, Don't care
	/// the status.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pstate_wrate_load_done(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{54,"pstate_wrate_load_done",6,6}
	};
	return reg;
}

	/// History alarm for  data rate parameter error from PIN.Only active in PCIe/SAS mode.  Clear after softeware read.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::his_alarm_width_para_err(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{54,"his_alarm_width_para_err",5,5}
	};
	return reg;
}

	/// History alarm for  data width parameter error from PIN.Only active in PCIe/SAS mode. Clear after softeware read.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::his_alarm_rate_para_err(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{54,"his_alarm_rate_para_err",4,4}
	};
	return reg;
}

	/// Current power state when power state switch not obey to PCIe/SAS protocol. Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::curr_power_state(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{55,"curr_power_state",10,8}
	};
	return reg;
}

	/// Next power state when power state switch not obey to PCIe/SAS protocol. Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::next_power_state(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{55,"next_power_state",6,4}
	};
	return reg;
}

	/// Latest error power state code. Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::power_state_err_code(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{55,"power_state_err_code",2,0}
	};
	return reg;
}

	/// Current data rate value,when rate/width switch at power state = L1/L2. Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::curr_data_rate(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{56,"curr_data_rate",14,12}
	};
	return reg;
}

	/// Next data rate value,when rate/width switch at power state = L1/L2. Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::next_data_rate(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{56,"next_data_rate",10,8}
	};
	return reg;
}

	/// Current data width value,when rate/width switch at power state = L1/L2. Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::curr_data_width(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{56,"curr_data_width",6,4}
	};
	return reg;
}

	/// Next data width value,when rate/width switch at power state = L1/L2. Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::next_data_width(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{56,"next_data_width",2,0}
	};
	return reg;
}

	/// Regulator loading adjust power down;
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::drvreg_selfbleed_pdb(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{57,"drvreg_selfbleed_pdb",15,15}
	};
	return reg;
}

	/// Regulator loading adjust ;
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::drvreg_selfbleed(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{57,"drvreg_selfbleed",14,11}
	};
	return reg;
}

	/// Data rate on the pin between PCIe/SAS core with HiLink in time. Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pin_data_rate(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{57,"pin_data_rate",10,8}
	};
	return reg;
}

	/// Data width on the pin between PCIe/SAS core with HiLink in time. Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pin_data_width(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{57,"pin_data_width",6,4}
	};
	return reg;
}

	/// Power state on the pin between PCIe/SAS core with HiLink in time. Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pin_power_state(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{57,"pin_power_state",2,0}
	};
	return reg;
}

	/// Current state for power state, data width and rate switch global control FSM. Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::sw_glb_fsm_curr_st(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{58,"sw_glb_fsm_curr_st",15,14}
	};
	return reg;
}

	/// Current state for Power state switch timer FSM. Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pstate_time_fsm_curr_st(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{58,"pstate_time_fsm_curr_st",10,8}
	};
	return reg;
}

	/// Hilink status for ready to receive power state, data rate and width switch request, high active. Only active in PCIe/SAS mode.
	/// 1 = Ready to receive switch request
	/// 0 = Not ready to receive switch request
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::rxtx_status(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{58,"rxtx_status",7,7}
	};
	return reg;
}

	/// Current state for data rate and width switch FSM. Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::wrate_sw_fsm_curr_st(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{58,"wrate_sw_fsm_curr_st",6,4}
	};
	return reg;
}

	/// Current state for Power state switch FSM. Only active in PCIe/SAS mode.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pstate_fsm_curr_st(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{58,"pstate_fsm_curr_st",2,0}
	};
	return reg;
}

	/// Select test signal for PCIe/SAS control , DSCLK, TX_DIG, RX_DIG block.
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::ds_dig_test_sel(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{59,"ds_dig_test_sel",7,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pstate_wrate_if_status(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{60,"pstate_wrate_if_status",15,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_txRegs::_REG_INFO::pstate_sw_status(){
	const static T_REG_INFO_EX reg={DS_txRegs::getInstance(),
		{61,"pstate_sw_status",15,0}
	};
	return reg;
}
bool
DS_txRegs::_REG_INFO::get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos){
	reg_infos.clear();
	switch(csr){
		case 0:
			reg_infos.push_back(txpwrdb().reg_info);
			reg_infos.push_back(txclk_16b32b_sel().reg_info);
			reg_infos.push_back(txclk_16b32b_pwrdb().reg_info);
			reg_infos.push_back(tx_clkregs_level().reg_info);
			reg_infos.push_back(txfirpre2().reg_info);
			reg_infos.push_back(txfirpre1().reg_info);
			break;
		case 1:
			reg_infos.push_back(txfirmain().reg_info);
			reg_infos.push_back(txfirpost1().reg_info);
			reg_infos.push_back(txfirpost2().reg_info);
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
			reg_infos.push_back(eco_idlemode_sel().reg_info);
			reg_infos.push_back(eco_tx_detectrx_sel().reg_info);
			reg_infos.push_back(ppmgen().reg_info);
			break;
		case 4:
			reg_infos.push_back(txphswrite().reg_info);
			reg_infos.push_back(tx_tx2rxloopbacksel_eco().reg_info);
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
			reg_infos.push_back(txcppwrdb().reg_info);
			reg_infos.push_back(txclkregpwrdb().reg_info);
			reg_infos.push_back(txdrvregpwrdb().reg_info);
			reg_infos.push_back(txdrvcalpwrdb().reg_info);
			reg_infos.push_back(txdrvslewpwrdb().reg_info);
			reg_infos.push_back(txdrvdatdepcomppwrdb().reg_info);
			reg_infos.push_back(txrxdetpwrdb().reg_info);
			reg_infos.push_back(txdrvbypass().reg_info);
			reg_infos.push_back(txtappwrdb().reg_info);
			break;
		case 11:
			reg_infos.push_back(txregspare().reg_info);
			reg_infos.push_back(txregpatdepsrc().reg_info);
			reg_infos.push_back(txregdrvlvl().reg_info);
			break;
		case 12:
			reg_infos.push_back(txedgebleed().reg_info);
			reg_infos.push_back(txpassbleed().reg_info);
			reg_infos.push_back(txdrvswctrl().reg_info);
			reg_infos.push_back(txdrvf1sel().reg_info);
			reg_infos.push_back(txdrvf2sel().reg_info);
			reg_infos.push_back(txdrvtapinv().reg_info);
			break;
		case 13:
			reg_infos.push_back(txdrvcalhisel().reg_info);
			reg_infos.push_back(txdrvcallosel().reg_info);
			reg_infos.push_back(txdrvcalpsel().reg_info);
			reg_infos.push_back(txdrvcalmsel().reg_info);
			reg_infos.push_back(txdrvotbpctrl().reg_info);
			reg_infos.push_back(txdrvotbmctrl().reg_info);
			reg_infos.push_back(dstxlowoffpwrdb().reg_info);
			reg_infos.push_back(dstxlowoffcal().reg_info);
			reg_infos.push_back(dstxlowoffctrl().reg_info);
			break;
		case 14:
			reg_infos.push_back(txdrvcalstart().reg_info);
			reg_infos.push_back(dstxlowoffout().reg_info);
			reg_infos.push_back(txdrvcaldir().reg_info);
			reg_infos.push_back(txtopotbctrl().reg_info);
			reg_infos.push_back(txdrvslew().reg_info);
			reg_infos.push_back(txdrvregcalen().reg_info);
			reg_infos.push_back(txdrvregslicetune().reg_info);
			reg_infos.push_back(txtermcalmode().reg_info);
			break;
		case 15:
			reg_infos.push_back(txdrvtesten().reg_info);
			reg_infos.push_back(txdrvtestin().reg_info);
			reg_infos.push_back(txdrvregatbctrl().reg_info);
			reg_infos.push_back(dslowoffctrl().reg_info);
			reg_infos.push_back(txclkregatbctrl().reg_info);
			reg_infos.push_back(txdrvatbctrl().reg_info);
			reg_infos.push_back(txmastermiratbctrl().reg_info);
			reg_infos.push_back(txtopatbctrl().reg_info);
			break;
		case 16:
			reg_infos.push_back(txdrvsel1().reg_info);
			reg_infos.push_back(seg1ctrl23to16().reg_info);
			break;
		case 17:
			reg_infos.push_back(seg1ctrl15to0().reg_info);
			break;
		case 18:
			reg_infos.push_back(txdrvsel2().reg_info);
			reg_infos.push_back(seg2ctrl23to16().reg_info);
			break;
		case 19:
			reg_infos.push_back(seg2ctrl15to0().reg_info);
			break;
		case 20:
			reg_infos.push_back(txdrvsel3().reg_info);
			reg_infos.push_back(seg3ctrl23to16().reg_info);
			break;
		case 21:
			reg_infos.push_back(seg3ctrl15to0().reg_info);
			break;
		case 22:
			reg_infos.push_back(txdrvsel4().reg_info);
			reg_infos.push_back(seg4ctrl23to16().reg_info);
			break;
		case 23:
			reg_infos.push_back(seg4ctrl15to0().reg_info);
			break;
		case 24:
			reg_infos.push_back(txphsval().reg_info);
			reg_infos.push_back(nmoscalstatus().reg_info);
			reg_infos.push_back(pmoscalstatus().reg_info);
			break;
		case 25:
			reg_infos.push_back(txspare().reg_info);
			reg_infos.push_back(tx_idle_hiz_sw_crg().reg_info);
			reg_infos.push_back(tx_detectrx_sel().reg_info);
			reg_infos.push_back(tx_tx2rxloopbacksel().reg_info);
			reg_infos.push_back(txdrv_open_en().reg_info);
			reg_infos.push_back(txdigspare().reg_info);
			reg_infos.push_back(txdrvcaldndir().reg_info);
			reg_infos.push_back(txdrvcalupdir().reg_info);
			break;
		case 26:
			reg_infos.push_back(txdrvcaldone().reg_info);
			reg_infos.push_back(txtapmapdone().reg_info);
			reg_infos.push_back(txdrvncaldn().reg_info);
			reg_infos.push_back(txdrvncalup().reg_info);
			break;
		case 27:
			reg_infos.push_back(txcal_timer_stop().reg_info);
			reg_infos.push_back(txcal_timer_value().reg_info);
			reg_infos.push_back(txcal_timer_div_en().reg_info);
			reg_infos.push_back(txcal_timer_div_value().reg_info);
			break;
		case 28:
			reg_infos.push_back(tx_training_firpost1().reg_info);
			reg_infos.push_back(tx_training_firmain().reg_info);
			reg_infos.push_back(tx_training_firpre1().reg_info);
			break;
		case 29:
			reg_infos.push_back(tx_local_fs().reg_info);
			reg_infos.push_back(tx_local_lf().reg_info);
			break;
		case 30:
			reg_infos.push_back(rxdet_timer_stop().reg_info);
			reg_infos.push_back(rxdet_init_timer_value().reg_info);
			reg_infos.push_back(rxdet_init_timer_div_value().reg_info);
			break;
		case 31:
			reg_infos.push_back(rxdet_charge_timer_value().reg_info);
			reg_infos.push_back(rxdet_charge_timer_div_value().reg_info);
			break;
		case 32:
			reg_infos.push_back(tx_rxdet_en_pin_mon().reg_info);
			reg_infos.push_back(tx_rxdet_ready().reg_info);
			reg_infos.push_back(tx_rxdet_out().reg_info);
			reg_infos.push_back(tx_rxdet_pwrdb().reg_info);
			reg_infos.push_back(tx_rxdet_mode().reg_info);
			reg_infos.push_back(tx_training_start_err().reg_info);
			reg_infos.push_back(txdrv_tap_inv().reg_info);
			break;
		case 33:
			reg_infos.push_back(txdrv_idle_en_pin_mon().reg_info);
			reg_infos.push_back(txdrv_idle_en().reg_info);
			reg_infos.push_back(txdrv_open_en_eco().reg_info);
			reg_infos.push_back(txdrv_idle_en_dly().reg_info);
			reg_infos.push_back(picodein_sel().reg_info);
			reg_infos.push_back(tx_phase_align_done().reg_info);
			reg_infos.push_back(tx_pa_status_clr().reg_info);
			reg_infos.push_back(tx_phase_align_thr().reg_info);
			break;
		case 34:
			reg_infos.push_back(txdrv_open_en_p().reg_info);
			reg_infos.push_back(txdrv_open_en_m().reg_info);
			reg_infos.push_back(txdrv_idle_bypass().reg_info);
			reg_infos.push_back(tx_wrate_sw_bypass().reg_info);
			reg_infos.push_back(tx_rxdet_en().reg_info);
			reg_infos.push_back(tx_rxdet_level().reg_info);
			reg_infos.push_back(tx_idle_dly_ana().reg_info);
			reg_infos.push_back(txoclk_sel().reg_info);
			reg_infos.push_back(txdrv_map_sel().reg_info);
			reg_infos.push_back(txdrv_tapinv_sel().reg_info);
			reg_infos.push_back(pcie_wrate_hsclk_sel().reg_info);
			reg_infos.push_back(txdrv_ressel().reg_info);
			break;
		case 35:
			reg_infos.push_back(txdrv_sliceboost_en().reg_info);
			reg_infos.push_back(clkreg_selfbleed_pdb().reg_info);
			reg_infos.push_back(clkreg_selfbleed().reg_info);
			reg_infos.push_back(ncaldn_offset().reg_info);
			reg_infos.push_back(ncalup_offset().reg_info);
			break;
		case 48:
			reg_infos.push_back(pcie_sas_sw_rstb().reg_info);
			reg_infos.push_back(pcie_sas_pin_en().reg_info);
			reg_infos.push_back(pma_mode().reg_info);
			reg_infos.push_back(pstate_wrate_vld().reg_info);
			reg_infos.push_back(pcie_sas_power_state().reg_info);
			reg_infos.push_back(pcie_sas_data_rate().reg_info);
			reg_infos.push_back(pcie_sas_rxtx_status_rdy().reg_info);
			reg_infos.push_back(pcie_sas_data_width().reg_info);
			break;
		case 49:
			reg_infos.push_back(rxsigdet_pwrdnb_msk().reg_info);
			reg_infos.push_back(txrxdet_pwrdnb_msk().reg_info);
			reg_infos.push_back(rxpwrdnb_msk().reg_info);
			reg_infos.push_back(txpwrdnb_msk().reg_info);
			reg_infos.push_back(dsclkgen_pwrdnb_msk().reg_info);
			reg_infos.push_back(dsclk_idac_pwrdnb_msk().reg_info);
			reg_infos.push_back(dsclk_vregdac_pwrdnb_msk().reg_info);
			reg_infos.push_back(dsclk_vregl_pwrdnb_msk().reg_info);
			reg_infos.push_back(rx_sw_sigdet_rstb_msk().reg_info);
			reg_infos.push_back(rx_sw_cdr_rstb_msk().reg_info);
			reg_infos.push_back(rx_sw_rstb_msk().reg_info);
			reg_infos.push_back(rx_loss_det_clk_en_msk().reg_info);
			reg_infos.push_back(rx_sw_clk_en_msk().reg_info);
			reg_infos.push_back(tx_sw_clk_en_msk().reg_info);
			reg_infos.push_back(tx_sw_rstb_msk().reg_info);
			break;
		case 50:
			reg_infos.push_back(pstate_timer_div_value().reg_info);
			reg_infos.push_back(pstate_timer_value().reg_info);
			break;
		case 51:
			reg_infos.push_back(dsclk_timer_div_value().reg_info);
			reg_infos.push_back(pcie_sas_spare().reg_info);
			reg_infos.push_back(wrate_timer_div_value().reg_info);
			break;
		case 52:
			reg_infos.push_back(dsclk_timer_value().reg_info);
			break;
		case 53:
			reg_infos.push_back(wrate_timer_value().reg_info);
			break;
		case 54:
			reg_infos.push_back(his_alarm_pstate_code_err().reg_info);
			reg_infos.push_back(his_alarm_pstate_sw_err().reg_info);
			reg_infos.push_back(his_alarm_wrate_sw_err().reg_info);
			reg_infos.push_back(his_alarm_pstate_wrate_err().reg_info);
			reg_infos.push_back(his_alarm_one_sw_req_vio().reg_info);
			reg_infos.push_back(his_alarm_sw_req_drop().reg_info);
			reg_infos.push_back(alarm_dsclk_calib_timeout().reg_info);
			reg_infos.push_back(alarm_wrate_txsw_timeout().reg_info);
			reg_infos.push_back(alarm_wrate_rxsw_timeout().reg_info);
			reg_infos.push_back(pstate_wrate_load_done().reg_info);
			reg_infos.push_back(his_alarm_width_para_err().reg_info);
			reg_infos.push_back(his_alarm_rate_para_err().reg_info);
			break;
		case 55:
			reg_infos.push_back(curr_power_state().reg_info);
			reg_infos.push_back(next_power_state().reg_info);
			reg_infos.push_back(power_state_err_code().reg_info);
			break;
		case 56:
			reg_infos.push_back(curr_data_rate().reg_info);
			reg_infos.push_back(next_data_rate().reg_info);
			reg_infos.push_back(curr_data_width().reg_info);
			reg_infos.push_back(next_data_width().reg_info);
			break;
		case 57:
			reg_infos.push_back(drvreg_selfbleed_pdb().reg_info);
			reg_infos.push_back(drvreg_selfbleed().reg_info);
			reg_infos.push_back(pin_data_rate().reg_info);
			reg_infos.push_back(pin_data_width().reg_info);
			reg_infos.push_back(pin_power_state().reg_info);
			break;
		case 58:
			reg_infos.push_back(sw_glb_fsm_curr_st().reg_info);
			reg_infos.push_back(pstate_time_fsm_curr_st().reg_info);
			reg_infos.push_back(rxtx_status().reg_info);
			reg_infos.push_back(wrate_sw_fsm_curr_st().reg_info);
			reg_infos.push_back(pstate_fsm_curr_st().reg_info);
			break;
		case 59:
			reg_infos.push_back(ds_dig_test_sel().reg_info);
			break;
		case 60:
			reg_infos.push_back(pstate_wrate_if_status().reg_info);
			break;
		case 61:
			reg_infos.push_back(pstate_sw_status().reg_info);
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
DS_txRegs::settxclk_16b32b_sel(uint val){
	fill_csr_bits(val,REG_INFO.txclk_16b32b_sel());	//CSR0[14:14]
	return *this;
}
uint
DS_txRegs::gettxclk_16b32b_sel(){
	return get_csr_bits(REG_INFO.txclk_16b32b_sel());	//CSR0[14:14]
}

DS_txRegs&
DS_txRegs::settxclk_16b32b_pwrdb(uint val){
	fill_csr_bits(val,REG_INFO.txclk_16b32b_pwrdb());	//CSR0[13:13]
	return *this;
}
uint
DS_txRegs::gettxclk_16b32b_pwrdb(){
	return get_csr_bits(REG_INFO.txclk_16b32b_pwrdb());	//CSR0[13:13]
}

DS_txRegs&
DS_txRegs::settx_clkregs_level(uint val){
	fill_csr_bits(val,REG_INFO.tx_clkregs_level());	//CSR0[12:10]
	return *this;
}
uint
DS_txRegs::gettx_clkregs_level(){
	return get_csr_bits(REG_INFO.tx_clkregs_level());	//CSR0[12:10]
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
DS_txRegs::settxfirpost2(uint val){
	fill_csr_bits(val,REG_INFO.txfirpost2());	//CSR1[4:0]
	return *this;
}
uint
DS_txRegs::gettxfirpost2(){
	return get_csr_bits(REG_INFO.txfirpost2());	//CSR1[4:0]
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
	fill_csr_bits(val,REG_INFO.txdwidth());	//CSR2[14:12]
	return *this;
}
uint
DS_txRegs::gettxdwidth(){
	return get_csr_bits(REG_INFO.txdwidth());	//CSR2[14:12]
}

DS_txRegs&
DS_txRegs::settxratemode(uint val){
	fill_csr_bits(val,REG_INFO.txratemode());	//CSR2[11:10]
	return *this;
}
uint
DS_txRegs::gettxratemode(){
	return get_csr_bits(REG_INFO.txratemode());	//CSR2[11:10]
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
DS_txRegs::seteco_idlemode_sel(uint val){
	fill_csr_bits(val,REG_INFO.eco_idlemode_sel());	//CSR3[6:6]
	return *this;
}
uint
DS_txRegs::geteco_idlemode_sel(){
	return get_csr_bits(REG_INFO.eco_idlemode_sel());	//CSR3[6:6]
}

DS_txRegs&
DS_txRegs::seteco_tx_detectrx_sel(uint val){
	fill_csr_bits(val,REG_INFO.eco_tx_detectrx_sel());	//CSR3[5:5]
	return *this;
}
uint
DS_txRegs::geteco_tx_detectrx_sel(){
	return get_csr_bits(REG_INFO.eco_tx_detectrx_sel());	//CSR3[5:5]
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
DS_txRegs::settx_tx2rxloopbacksel_eco(uint val){
	fill_csr_bits(val,REG_INFO.tx_tx2rxloopbacksel_eco());	//CSR4[7:7]
	return *this;
}
uint
DS_txRegs::gettx_tx2rxloopbacksel_eco(){
	return get_csr_bits(REG_INFO.tx_tx2rxloopbacksel_eco());	//CSR4[7:7]
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
DS_txRegs::settxcppwrdb(uint val){
	fill_csr_bits(val,REG_INFO.txcppwrdb());	//CSR10[15:15]
	return *this;
}
uint
DS_txRegs::gettxcppwrdb(){
	return get_csr_bits(REG_INFO.txcppwrdb());	//CSR10[15:15]
}

DS_txRegs&
DS_txRegs::settxclkregpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.txclkregpwrdb());	//CSR10[14:14]
	return *this;
}
uint
DS_txRegs::gettxclkregpwrdb(){
	return get_csr_bits(REG_INFO.txclkregpwrdb());	//CSR10[14:14]
}

DS_txRegs&
DS_txRegs::settxdrvregpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.txdrvregpwrdb());	//CSR10[13:13]
	return *this;
}
uint
DS_txRegs::gettxdrvregpwrdb(){
	return get_csr_bits(REG_INFO.txdrvregpwrdb());	//CSR10[13:13]
}

DS_txRegs&
DS_txRegs::settxdrvcalpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.txdrvcalpwrdb());	//CSR10[12:12]
	return *this;
}
uint
DS_txRegs::gettxdrvcalpwrdb(){
	return get_csr_bits(REG_INFO.txdrvcalpwrdb());	//CSR10[12:12]
}

DS_txRegs&
DS_txRegs::settxdrvslewpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.txdrvslewpwrdb());	//CSR10[11:11]
	return *this;
}
uint
DS_txRegs::gettxdrvslewpwrdb(){
	return get_csr_bits(REG_INFO.txdrvslewpwrdb());	//CSR10[11:11]
}

DS_txRegs&
DS_txRegs::settxdrvdatdepcomppwrdb(uint val){
	fill_csr_bits(val,REG_INFO.txdrvdatdepcomppwrdb());	//CSR10[10:10]
	return *this;
}
uint
DS_txRegs::gettxdrvdatdepcomppwrdb(){
	return get_csr_bits(REG_INFO.txdrvdatdepcomppwrdb());	//CSR10[10:10]
}

DS_txRegs&
DS_txRegs::settxrxdetpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.txrxdetpwrdb());	//CSR10[9:9]
	return *this;
}
uint
DS_txRegs::gettxrxdetpwrdb(){
	return get_csr_bits(REG_INFO.txrxdetpwrdb());	//CSR10[9:9]
}

DS_txRegs&
DS_txRegs::settxdrvbypass(uint val){
	fill_csr_bits(val,REG_INFO.txdrvbypass());	//CSR10[8:8]
	return *this;
}
uint
DS_txRegs::gettxdrvbypass(){
	return get_csr_bits(REG_INFO.txdrvbypass());	//CSR10[8:8]
}

DS_txRegs&
DS_txRegs::settxtappwrdb(uint val){
	fill_csr_bits(val,REG_INFO.txtappwrdb());	//CSR10[7:0]
	return *this;
}
uint
DS_txRegs::gettxtappwrdb(){
	return get_csr_bits(REG_INFO.txtappwrdb());	//CSR10[7:0]
}

DS_txRegs&
DS_txRegs::settxregspare(uint val){
	fill_csr_bits(val,REG_INFO.txregspare());	//CSR11[15:8]
	return *this;
}
uint
DS_txRegs::gettxregspare(){
	return get_csr_bits(REG_INFO.txregspare());	//CSR11[15:8]
}

DS_txRegs&
DS_txRegs::settxregpatdepsrc(uint val){
	fill_csr_bits(val,REG_INFO.txregpatdepsrc());	//CSR11[7:3]
	return *this;
}
uint
DS_txRegs::gettxregpatdepsrc(){
	return get_csr_bits(REG_INFO.txregpatdepsrc());	//CSR11[7:3]
}

DS_txRegs&
DS_txRegs::settxregdrvlvl(uint val){
	fill_csr_bits(val,REG_INFO.txregdrvlvl());	//CSR11[2:0]
	return *this;
}
uint
DS_txRegs::gettxregdrvlvl(){
	return get_csr_bits(REG_INFO.txregdrvlvl());	//CSR11[2:0]
}

DS_txRegs&
DS_txRegs::settxedgebleed(uint val){
	fill_csr_bits(val,REG_INFO.txedgebleed());	//CSR12[15:12]
	return *this;
}
uint
DS_txRegs::gettxedgebleed(){
	return get_csr_bits(REG_INFO.txedgebleed());	//CSR12[15:12]
}

DS_txRegs&
DS_txRegs::settxpassbleed(uint val){
	fill_csr_bits(val,REG_INFO.txpassbleed());	//CSR12[11:8]
	return *this;
}
uint
DS_txRegs::gettxpassbleed(){
	return get_csr_bits(REG_INFO.txpassbleed());	//CSR12[11:8]
}

DS_txRegs&
DS_txRegs::settxdrvswctrl(uint val){
	fill_csr_bits(val,REG_INFO.txdrvswctrl());	//CSR12[7:7]
	return *this;
}
uint
DS_txRegs::gettxdrvswctrl(){
	return get_csr_bits(REG_INFO.txdrvswctrl());	//CSR12[7:7]
}

DS_txRegs&
DS_txRegs::settxdrvf1sel(uint val){
	fill_csr_bits(val,REG_INFO.txdrvf1sel());	//CSR12[6:6]
	return *this;
}
uint
DS_txRegs::gettxdrvf1sel(){
	return get_csr_bits(REG_INFO.txdrvf1sel());	//CSR12[6:6]
}

DS_txRegs&
DS_txRegs::settxdrvf2sel(uint val){
	fill_csr_bits(val,REG_INFO.txdrvf2sel());	//CSR12[5:5]
	return *this;
}
uint
DS_txRegs::gettxdrvf2sel(){
	return get_csr_bits(REG_INFO.txdrvf2sel());	//CSR12[5:5]
}

DS_txRegs&
DS_txRegs::settxdrvtapinv(uint val){
	fill_csr_bits(val,REG_INFO.txdrvtapinv());	//CSR12[4:0]
	return *this;
}
uint
DS_txRegs::gettxdrvtapinv(){
	return get_csr_bits(REG_INFO.txdrvtapinv());	//CSR12[4:0]
}

DS_txRegs&
DS_txRegs::settxdrvcalhisel(uint val){
	fill_csr_bits(val,REG_INFO.txdrvcalhisel());	//CSR13[15:15]
	return *this;
}
uint
DS_txRegs::gettxdrvcalhisel(){
	return get_csr_bits(REG_INFO.txdrvcalhisel());	//CSR13[15:15]
}

DS_txRegs&
DS_txRegs::settxdrvcallosel(uint val){
	fill_csr_bits(val,REG_INFO.txdrvcallosel());	//CSR13[14:14]
	return *this;
}
uint
DS_txRegs::gettxdrvcallosel(){
	return get_csr_bits(REG_INFO.txdrvcallosel());	//CSR13[14:14]
}

DS_txRegs&
DS_txRegs::settxdrvcalpsel(uint val){
	fill_csr_bits(val,REG_INFO.txdrvcalpsel());	//CSR13[13:13]
	return *this;
}
uint
DS_txRegs::gettxdrvcalpsel(){
	return get_csr_bits(REG_INFO.txdrvcalpsel());	//CSR13[13:13]
}

DS_txRegs&
DS_txRegs::settxdrvcalmsel(uint val){
	fill_csr_bits(val,REG_INFO.txdrvcalmsel());	//CSR13[12:12]
	return *this;
}
uint
DS_txRegs::gettxdrvcalmsel(){
	return get_csr_bits(REG_INFO.txdrvcalmsel());	//CSR13[12:12]
}

DS_txRegs&
DS_txRegs::settxdrvotbpctrl(uint val){
	fill_csr_bits(val,REG_INFO.txdrvotbpctrl());	//CSR13[11:10]
	return *this;
}
uint
DS_txRegs::gettxdrvotbpctrl(){
	return get_csr_bits(REG_INFO.txdrvotbpctrl());	//CSR13[11:10]
}

DS_txRegs&
DS_txRegs::settxdrvotbmctrl(uint val){
	fill_csr_bits(val,REG_INFO.txdrvotbmctrl());	//CSR13[9:8]
	return *this;
}
uint
DS_txRegs::gettxdrvotbmctrl(){
	return get_csr_bits(REG_INFO.txdrvotbmctrl());	//CSR13[9:8]
}

DS_txRegs&
DS_txRegs::setdstxlowoffpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.dstxlowoffpwrdb());	//CSR13[7:7]
	return *this;
}
uint
DS_txRegs::getdstxlowoffpwrdb(){
	return get_csr_bits(REG_INFO.dstxlowoffpwrdb());	//CSR13[7:7]
}

DS_txRegs&
DS_txRegs::setdstxlowoffcal(uint val){
	fill_csr_bits(val,REG_INFO.dstxlowoffcal());	//CSR13[6:6]
	return *this;
}
uint
DS_txRegs::getdstxlowoffcal(){
	return get_csr_bits(REG_INFO.dstxlowoffcal());	//CSR13[6:6]
}

DS_txRegs&
DS_txRegs::setdstxlowoffctrl(uint val){
	fill_csr_bits(val,REG_INFO.dstxlowoffctrl());	//CSR13[5:0]
	return *this;
}
uint
DS_txRegs::getdstxlowoffctrl(){
	return get_csr_bits(REG_INFO.dstxlowoffctrl());	//CSR13[5:0]
}

DS_txRegs&
DS_txRegs::settxdrvcalstart(uint val){
	fill_csr_bits(val,REG_INFO.txdrvcalstart());	//CSR14[15:15]
	return *this;
}
uint
DS_txRegs::gettxdrvcalstart(){
	return get_csr_bits(REG_INFO.txdrvcalstart());	//CSR14[15:15]
}

uint
DS_txRegs::getdstxlowoffout(){
	return get_csr_bits(REG_INFO.dstxlowoffout());	//CSR14[14:14]
}

DS_txRegs&
DS_txRegs::settxdrvcaldir(uint val){
	fill_csr_bits(val,REG_INFO.txdrvcaldir());	//CSR14[13:13]
	return *this;
}
uint
DS_txRegs::gettxdrvcaldir(){
	return get_csr_bits(REG_INFO.txdrvcaldir());	//CSR14[13:13]
}

DS_txRegs&
DS_txRegs::settxtopotbctrl(uint val){
	fill_csr_bits(val,REG_INFO.txtopotbctrl());	//CSR14[12:11]
	return *this;
}
uint
DS_txRegs::gettxtopotbctrl(){
	return get_csr_bits(REG_INFO.txtopotbctrl());	//CSR14[12:11]
}

DS_txRegs&
DS_txRegs::settxdrvslew(uint val){
	fill_csr_bits(val,REG_INFO.txdrvslew());	//CSR14[10:8]
	return *this;
}
uint
DS_txRegs::gettxdrvslew(){
	return get_csr_bits(REG_INFO.txdrvslew());	//CSR14[10:8]
}

DS_txRegs&
DS_txRegs::settxdrvregcalen(uint val){
	fill_csr_bits(val,REG_INFO.txdrvregcalen());	//CSR14[7:7]
	return *this;
}
uint
DS_txRegs::gettxdrvregcalen(){
	return get_csr_bits(REG_INFO.txdrvregcalen());	//CSR14[7:7]
}

DS_txRegs&
DS_txRegs::settxdrvregslicetune(uint val){
	fill_csr_bits(val,REG_INFO.txdrvregslicetune());	//CSR14[6:6]
	return *this;
}
uint
DS_txRegs::gettxdrvregslicetune(){
	return get_csr_bits(REG_INFO.txdrvregslicetune());	//CSR14[6:6]
}

DS_txRegs&
DS_txRegs::settxtermcalmode(uint val){
	fill_csr_bits(val,REG_INFO.txtermcalmode());	//CSR14[5:4]
	return *this;
}
uint
DS_txRegs::gettxtermcalmode(){
	return get_csr_bits(REG_INFO.txtermcalmode());	//CSR14[5:4]
}

DS_txRegs&
DS_txRegs::settxdrvtesten(uint val){
	fill_csr_bits(val,REG_INFO.txdrvtesten());	//CSR15[15:15]
	return *this;
}
uint
DS_txRegs::gettxdrvtesten(){
	return get_csr_bits(REG_INFO.txdrvtesten());	//CSR15[15:15]
}

DS_txRegs&
DS_txRegs::settxdrvtestin(uint val){
	fill_csr_bits(val,REG_INFO.txdrvtestin());	//CSR15[14:14]
	return *this;
}
uint
DS_txRegs::gettxdrvtestin(){
	return get_csr_bits(REG_INFO.txdrvtestin());	//CSR15[14:14]
}

DS_txRegs&
DS_txRegs::settxdrvregatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.txdrvregatbctrl());	//CSR15[13:11]
	return *this;
}
uint
DS_txRegs::gettxdrvregatbctrl(){
	return get_csr_bits(REG_INFO.txdrvregatbctrl());	//CSR15[13:11]
}

DS_txRegs&
DS_txRegs::setdslowoffctrl(uint val){
	fill_csr_bits(val,REG_INFO.dslowoffctrl());	//CSR15[10:9]
	return *this;
}
uint
DS_txRegs::getdslowoffctrl(){
	return get_csr_bits(REG_INFO.dslowoffctrl());	//CSR15[10:9]
}

DS_txRegs&
DS_txRegs::settxclkregatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.txclkregatbctrl());	//CSR15[8:6]
	return *this;
}
uint
DS_txRegs::gettxclkregatbctrl(){
	return get_csr_bits(REG_INFO.txclkregatbctrl());	//CSR15[8:6]
}

DS_txRegs&
DS_txRegs::settxdrvatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.txdrvatbctrl());	//CSR15[5:4]
	return *this;
}
uint
DS_txRegs::gettxdrvatbctrl(){
	return get_csr_bits(REG_INFO.txdrvatbctrl());	//CSR15[5:4]
}

DS_txRegs&
DS_txRegs::settxmastermiratbctrl(uint val){
	fill_csr_bits(val,REG_INFO.txmastermiratbctrl());	//CSR15[3:2]
	return *this;
}
uint
DS_txRegs::gettxmastermiratbctrl(){
	return get_csr_bits(REG_INFO.txmastermiratbctrl());	//CSR15[3:2]
}

DS_txRegs&
DS_txRegs::settxtopatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.txtopatbctrl());	//CSR15[1:0]
	return *this;
}
uint
DS_txRegs::gettxtopatbctrl(){
	return get_csr_bits(REG_INFO.txtopatbctrl());	//CSR15[1:0]
}

DS_txRegs&
DS_txRegs::settxdrvsel1(uint val){
	fill_csr_bits(val,REG_INFO.txdrvsel1());	//CSR16[15:8]
	return *this;
}
uint
DS_txRegs::gettxdrvsel1(){
	return get_csr_bits(REG_INFO.txdrvsel1());	//CSR16[15:8]
}

DS_txRegs&
DS_txRegs::setseg1ctrl23to16(uint val){
	fill_csr_bits(val,REG_INFO.seg1ctrl23to16());	//CSR16[7:0]
	return *this;
}
uint
DS_txRegs::getseg1ctrl23to16(){
	return get_csr_bits(REG_INFO.seg1ctrl23to16());	//CSR16[7:0]
}

DS_txRegs&
DS_txRegs::setseg1ctrl15to0(uint val){
	fill_csr_bits(val,REG_INFO.seg1ctrl15to0());	//CSR17[15:0]
	return *this;
}
uint
DS_txRegs::getseg1ctrl15to0(){
	return get_csr_bits(REG_INFO.seg1ctrl15to0());	//CSR17[15:0]
}

DS_txRegs&
DS_txRegs::settxdrvsel2(uint val){
	fill_csr_bits(val,REG_INFO.txdrvsel2());	//CSR18[15:8]
	return *this;
}
uint
DS_txRegs::gettxdrvsel2(){
	return get_csr_bits(REG_INFO.txdrvsel2());	//CSR18[15:8]
}

DS_txRegs&
DS_txRegs::setseg2ctrl23to16(uint val){
	fill_csr_bits(val,REG_INFO.seg2ctrl23to16());	//CSR18[7:0]
	return *this;
}
uint
DS_txRegs::getseg2ctrl23to16(){
	return get_csr_bits(REG_INFO.seg2ctrl23to16());	//CSR18[7:0]
}

DS_txRegs&
DS_txRegs::setseg2ctrl15to0(uint val){
	fill_csr_bits(val,REG_INFO.seg2ctrl15to0());	//CSR19[15:0]
	return *this;
}
uint
DS_txRegs::getseg2ctrl15to0(){
	return get_csr_bits(REG_INFO.seg2ctrl15to0());	//CSR19[15:0]
}

DS_txRegs&
DS_txRegs::settxdrvsel3(uint val){
	fill_csr_bits(val,REG_INFO.txdrvsel3());	//CSR20[15:8]
	return *this;
}
uint
DS_txRegs::gettxdrvsel3(){
	return get_csr_bits(REG_INFO.txdrvsel3());	//CSR20[15:8]
}

DS_txRegs&
DS_txRegs::setseg3ctrl23to16(uint val){
	fill_csr_bits(val,REG_INFO.seg3ctrl23to16());	//CSR20[7:0]
	return *this;
}
uint
DS_txRegs::getseg3ctrl23to16(){
	return get_csr_bits(REG_INFO.seg3ctrl23to16());	//CSR20[7:0]
}

DS_txRegs&
DS_txRegs::setseg3ctrl15to0(uint val){
	fill_csr_bits(val,REG_INFO.seg3ctrl15to0());	//CSR21[15:0]
	return *this;
}
uint
DS_txRegs::getseg3ctrl15to0(){
	return get_csr_bits(REG_INFO.seg3ctrl15to0());	//CSR21[15:0]
}

DS_txRegs&
DS_txRegs::settxdrvsel4(uint val){
	fill_csr_bits(val,REG_INFO.txdrvsel4());	//CSR22[15:8]
	return *this;
}
uint
DS_txRegs::gettxdrvsel4(){
	return get_csr_bits(REG_INFO.txdrvsel4());	//CSR22[15:8]
}

DS_txRegs&
DS_txRegs::setseg4ctrl23to16(uint val){
	fill_csr_bits(val,REG_INFO.seg4ctrl23to16());	//CSR22[7:0]
	return *this;
}
uint
DS_txRegs::getseg4ctrl23to16(){
	return get_csr_bits(REG_INFO.seg4ctrl23to16());	//CSR22[7:0]
}

DS_txRegs&
DS_txRegs::setseg4ctrl15to0(uint val){
	fill_csr_bits(val,REG_INFO.seg4ctrl15to0());	//CSR23[15:0]
	return *this;
}
uint
DS_txRegs::getseg4ctrl15to0(){
	return get_csr_bits(REG_INFO.seg4ctrl15to0());	//CSR23[15:0]
}

uint
DS_txRegs::gettxphsval(){
	return get_csr_bits(REG_INFO.txphsval());	//CSR24[14:8]
}

uint
DS_txRegs::getnmoscalstatus(){
	return get_csr_bits(REG_INFO.nmoscalstatus());	//CSR24[7:4]
}

uint
DS_txRegs::getpmoscalstatus(){
	return get_csr_bits(REG_INFO.pmoscalstatus());	//CSR24[3:0]
}

DS_txRegs&
DS_txRegs::settxspare(uint val){
	fill_csr_bits(val,REG_INFO.txspare());	//CSR25[15:8]
	return *this;
}
uint
DS_txRegs::gettxspare(){
	return get_csr_bits(REG_INFO.txspare());	//CSR25[15:8]
}

DS_txRegs&
DS_txRegs::settx_idle_hiz_sw_crg(uint val){
	fill_csr_bits(val,REG_INFO.tx_idle_hiz_sw_crg());	//CSR25[7:7]
	return *this;
}
uint
DS_txRegs::gettx_idle_hiz_sw_crg(){
	return get_csr_bits(REG_INFO.tx_idle_hiz_sw_crg());	//CSR25[7:7]
}

DS_txRegs&
DS_txRegs::settx_detectrx_sel(uint val){
	fill_csr_bits(val,REG_INFO.tx_detectrx_sel());	//CSR25[6:6]
	return *this;
}
uint
DS_txRegs::gettx_detectrx_sel(){
	return get_csr_bits(REG_INFO.tx_detectrx_sel());	//CSR25[6:6]
}

DS_txRegs&
DS_txRegs::settx_tx2rxloopbacksel(uint val){
	fill_csr_bits(val,REG_INFO.tx_tx2rxloopbacksel());	//CSR25[5:5]
	return *this;
}
uint
DS_txRegs::gettx_tx2rxloopbacksel(){
	return get_csr_bits(REG_INFO.tx_tx2rxloopbacksel());	//CSR25[5:5]
}

DS_txRegs&
DS_txRegs::settxdrv_open_en(uint val){
	fill_csr_bits(val,REG_INFO.txdrv_open_en());	//CSR25[4:4]
	return *this;
}
uint
DS_txRegs::gettxdrv_open_en(){
	return get_csr_bits(REG_INFO.txdrv_open_en());	//CSR25[4:4]
}

DS_txRegs&
DS_txRegs::settxdigspare(uint val){
	fill_csr_bits(val,REG_INFO.txdigspare());	//CSR25[3:2]
	return *this;
}
uint
DS_txRegs::gettxdigspare(){
	return get_csr_bits(REG_INFO.txdigspare());	//CSR25[3:2]
}

DS_txRegs&
DS_txRegs::settxdrvcaldndir(uint val){
	fill_csr_bits(val,REG_INFO.txdrvcaldndir());	//CSR25[1:1]
	return *this;
}
uint
DS_txRegs::gettxdrvcaldndir(){
	return get_csr_bits(REG_INFO.txdrvcaldndir());	//CSR25[1:1]
}

DS_txRegs&
DS_txRegs::settxdrvcalupdir(uint val){
	fill_csr_bits(val,REG_INFO.txdrvcalupdir());	//CSR25[0:0]
	return *this;
}
uint
DS_txRegs::gettxdrvcalupdir(){
	return get_csr_bits(REG_INFO.txdrvcalupdir());	//CSR25[0:0]
}

uint
DS_txRegs::gettxdrvcaldone(){
	return get_csr_bits(REG_INFO.txdrvcaldone());	//CSR26[15:15]
}

uint
DS_txRegs::gettxtapmapdone(){
	return get_csr_bits(REG_INFO.txtapmapdone());	//CSR26[14:14]
}

uint
DS_txRegs::gettxdrvncaldn(){
	return get_csr_bits(REG_INFO.txdrvncaldn());	//CSR26[11:6]
}

uint
DS_txRegs::gettxdrvncalup(){
	return get_csr_bits(REG_INFO.txdrvncalup());	//CSR26[5:0]
}

DS_txRegs&
DS_txRegs::settxcal_timer_stop(uint val){
	fill_csr_bits(val,REG_INFO.txcal_timer_stop());	//CSR27[14:14]
	return *this;
}
uint
DS_txRegs::gettxcal_timer_stop(){
	return get_csr_bits(REG_INFO.txcal_timer_stop());	//CSR27[14:14]
}

DS_txRegs&
DS_txRegs::settxcal_timer_value(uint val){
	fill_csr_bits(val,REG_INFO.txcal_timer_value());	//CSR27[13:4]
	return *this;
}
uint
DS_txRegs::gettxcal_timer_value(){
	return get_csr_bits(REG_INFO.txcal_timer_value());	//CSR27[13:4]
}

DS_txRegs&
DS_txRegs::settxcal_timer_div_en(uint val){
	fill_csr_bits(val,REG_INFO.txcal_timer_div_en());	//CSR27[3:3]
	return *this;
}
uint
DS_txRegs::gettxcal_timer_div_en(){
	return get_csr_bits(REG_INFO.txcal_timer_div_en());	//CSR27[3:3]
}

DS_txRegs&
DS_txRegs::settxcal_timer_div_value(uint val){
	fill_csr_bits(val,REG_INFO.txcal_timer_div_value());	//CSR27[2:0]
	return *this;
}
uint
DS_txRegs::gettxcal_timer_div_value(){
	return get_csr_bits(REG_INFO.txcal_timer_div_value());	//CSR27[2:0]
}

uint
DS_txRegs::gettx_training_firpost1(){
	return get_csr_bits(REG_INFO.tx_training_firpost1());	//CSR28[15:11]
}

uint
DS_txRegs::gettx_training_firmain(){
	return get_csr_bits(REG_INFO.tx_training_firmain());	//CSR28[10:5]
}

uint
DS_txRegs::gettx_training_firpre1(){
	return get_csr_bits(REG_INFO.tx_training_firpre1());	//CSR28[4:0]
}

uint
DS_txRegs::gettx_local_fs(){
	return get_csr_bits(REG_INFO.tx_local_fs());	//CSR29[13:8]
}

uint
DS_txRegs::gettx_local_lf(){
	return get_csr_bits(REG_INFO.tx_local_lf());	//CSR29[5:0]
}

DS_txRegs&
DS_txRegs::setrxdet_timer_stop(uint val){
	fill_csr_bits(val,REG_INFO.rxdet_timer_stop());	//CSR30[14:14]
	return *this;
}
uint
DS_txRegs::getrxdet_timer_stop(){
	return get_csr_bits(REG_INFO.rxdet_timer_stop());	//CSR30[14:14]
}

DS_txRegs&
DS_txRegs::setrxdet_init_timer_value(uint val){
	fill_csr_bits(val,REG_INFO.rxdet_init_timer_value());	//CSR30[13:4]
	return *this;
}
uint
DS_txRegs::getrxdet_init_timer_value(){
	return get_csr_bits(REG_INFO.rxdet_init_timer_value());	//CSR30[13:4]
}

DS_txRegs&
DS_txRegs::setrxdet_init_timer_div_value(uint val){
	fill_csr_bits(val,REG_INFO.rxdet_init_timer_div_value());	//CSR30[2:0]
	return *this;
}
uint
DS_txRegs::getrxdet_init_timer_div_value(){
	return get_csr_bits(REG_INFO.rxdet_init_timer_div_value());	//CSR30[2:0]
}

DS_txRegs&
DS_txRegs::setrxdet_charge_timer_value(uint val){
	fill_csr_bits(val,REG_INFO.rxdet_charge_timer_value());	//CSR31[13:4]
	return *this;
}
uint
DS_txRegs::getrxdet_charge_timer_value(){
	return get_csr_bits(REG_INFO.rxdet_charge_timer_value());	//CSR31[13:4]
}

DS_txRegs&
DS_txRegs::setrxdet_charge_timer_div_value(uint val){
	fill_csr_bits(val,REG_INFO.rxdet_charge_timer_div_value());	//CSR31[2:0]
	return *this;
}
uint
DS_txRegs::getrxdet_charge_timer_div_value(){
	return get_csr_bits(REG_INFO.rxdet_charge_timer_div_value());	//CSR31[2:0]
}

uint
DS_txRegs::gettx_rxdet_en_pin_mon(){
	return get_csr_bits(REG_INFO.tx_rxdet_en_pin_mon());	//CSR32[14:14]
}

uint
DS_txRegs::gettx_rxdet_ready(){
	return get_csr_bits(REG_INFO.tx_rxdet_ready());	//CSR32[13:13]
}

uint
DS_txRegs::gettx_rxdet_out(){
	return get_csr_bits(REG_INFO.tx_rxdet_out());	//CSR32[12:12]
}

uint
DS_txRegs::gettx_rxdet_pwrdb(){
	return get_csr_bits(REG_INFO.tx_rxdet_pwrdb());	//CSR32[11:11]
}

uint
DS_txRegs::gettx_rxdet_mode(){
	return get_csr_bits(REG_INFO.tx_rxdet_mode());	//CSR32[10:8]
}

uint
DS_txRegs::gettx_training_start_err(){
	return get_csr_bits(REG_INFO.tx_training_start_err());	//CSR32[5:5]
}

uint
DS_txRegs::gettxdrv_tap_inv(){
	return get_csr_bits(REG_INFO.txdrv_tap_inv());	//CSR32[4:0]
}

uint
DS_txRegs::gettxdrv_idle_en_pin_mon(){
	return get_csr_bits(REG_INFO.txdrv_idle_en_pin_mon());	//CSR33[15:15]
}

DS_txRegs&
DS_txRegs::settxdrv_idle_en(uint val){
	fill_csr_bits(val,REG_INFO.txdrv_idle_en());	//CSR33[14:14]
	return *this;
}
uint
DS_txRegs::gettxdrv_idle_en(){
	return get_csr_bits(REG_INFO.txdrv_idle_en());	//CSR33[14:14]
}

DS_txRegs&
DS_txRegs::settxdrv_open_en_eco(uint val){
	fill_csr_bits(val,REG_INFO.txdrv_open_en_eco());	//CSR33[13:13]
	return *this;
}
uint
DS_txRegs::gettxdrv_open_en_eco(){
	return get_csr_bits(REG_INFO.txdrv_open_en_eco());	//CSR33[13:13]
}

DS_txRegs&
DS_txRegs::settxdrv_idle_en_dly(uint val){
	fill_csr_bits(val,REG_INFO.txdrv_idle_en_dly());	//CSR33[11:11]
	return *this;
}
uint
DS_txRegs::gettxdrv_idle_en_dly(){
	return get_csr_bits(REG_INFO.txdrv_idle_en_dly());	//CSR33[11:11]
}

DS_txRegs&
DS_txRegs::setpicodein_sel(uint val){
	fill_csr_bits(val,REG_INFO.picodein_sel());	//CSR33[10:10]
	return *this;
}
uint
DS_txRegs::getpicodein_sel(){
	return get_csr_bits(REG_INFO.picodein_sel());	//CSR33[10:10]
}

uint
DS_txRegs::gettx_phase_align_done(){
	return get_csr_bits(REG_INFO.tx_phase_align_done());	//CSR33[9:9]
}

DS_txRegs&
DS_txRegs::settx_pa_status_clr(uint val){
	fill_csr_bits(val,REG_INFO.tx_pa_status_clr());	//CSR33[8:8]
	return *this;
}
uint
DS_txRegs::gettx_pa_status_clr(){
	return get_csr_bits(REG_INFO.tx_pa_status_clr());	//CSR33[8:8]
}

DS_txRegs&
DS_txRegs::settx_phase_align_thr(uint val){
	fill_csr_bits(val,REG_INFO.tx_phase_align_thr());	//CSR33[7:0]
	return *this;
}
uint
DS_txRegs::gettx_phase_align_thr(){
	return get_csr_bits(REG_INFO.tx_phase_align_thr());	//CSR33[7:0]
}

DS_txRegs&
DS_txRegs::settxdrv_open_en_p(uint val){
	fill_csr_bits(val,REG_INFO.txdrv_open_en_p());	//CSR34[15:15]
	return *this;
}
uint
DS_txRegs::gettxdrv_open_en_p(){
	return get_csr_bits(REG_INFO.txdrv_open_en_p());	//CSR34[15:15]
}

DS_txRegs&
DS_txRegs::settxdrv_open_en_m(uint val){
	fill_csr_bits(val,REG_INFO.txdrv_open_en_m());	//CSR34[14:14]
	return *this;
}
uint
DS_txRegs::gettxdrv_open_en_m(){
	return get_csr_bits(REG_INFO.txdrv_open_en_m());	//CSR34[14:14]
}

DS_txRegs&
DS_txRegs::settxdrv_idle_bypass(uint val){
	fill_csr_bits(val,REG_INFO.txdrv_idle_bypass());	//CSR34[13:13]
	return *this;
}
uint
DS_txRegs::gettxdrv_idle_bypass(){
	return get_csr_bits(REG_INFO.txdrv_idle_bypass());	//CSR34[13:13]
}

DS_txRegs&
DS_txRegs::settx_wrate_sw_bypass(uint val){
	fill_csr_bits(val,REG_INFO.tx_wrate_sw_bypass());	//CSR34[12:12]
	return *this;
}
uint
DS_txRegs::gettx_wrate_sw_bypass(){
	return get_csr_bits(REG_INFO.tx_wrate_sw_bypass());	//CSR34[12:12]
}

DS_txRegs&
DS_txRegs::settx_rxdet_en(uint val){
	fill_csr_bits(val,REG_INFO.tx_rxdet_en());	//CSR34[11:11]
	return *this;
}
uint
DS_txRegs::gettx_rxdet_en(){
	return get_csr_bits(REG_INFO.tx_rxdet_en());	//CSR34[11:11]
}

DS_txRegs&
DS_txRegs::settx_rxdet_level(uint val){
	fill_csr_bits(val,REG_INFO.tx_rxdet_level());	//CSR34[10:9]
	return *this;
}
uint
DS_txRegs::gettx_rxdet_level(){
	return get_csr_bits(REG_INFO.tx_rxdet_level());	//CSR34[10:9]
}

DS_txRegs&
DS_txRegs::settx_idle_dly_ana(uint val){
	fill_csr_bits(val,REG_INFO.tx_idle_dly_ana());	//CSR34[8:6]
	return *this;
}
uint
DS_txRegs::gettx_idle_dly_ana(){
	return get_csr_bits(REG_INFO.tx_idle_dly_ana());	//CSR34[8:6]
}

DS_txRegs&
DS_txRegs::settxoclk_sel(uint val){
	fill_csr_bits(val,REG_INFO.txoclk_sel());	//CSR34[5:5]
	return *this;
}
uint
DS_txRegs::gettxoclk_sel(){
	return get_csr_bits(REG_INFO.txoclk_sel());	//CSR34[5:5]
}

DS_txRegs&
DS_txRegs::settxdrv_map_sel(uint val){
	fill_csr_bits(val,REG_INFO.txdrv_map_sel());	//CSR34[4:4]
	return *this;
}
uint
DS_txRegs::gettxdrv_map_sel(){
	return get_csr_bits(REG_INFO.txdrv_map_sel());	//CSR34[4:4]
}

DS_txRegs&
DS_txRegs::settxdrv_tapinv_sel(uint val){
	fill_csr_bits(val,REG_INFO.txdrv_tapinv_sel());	//CSR34[3:3]
	return *this;
}
uint
DS_txRegs::gettxdrv_tapinv_sel(){
	return get_csr_bits(REG_INFO.txdrv_tapinv_sel());	//CSR34[3:3]
}

DS_txRegs&
DS_txRegs::setpcie_wrate_hsclk_sel(uint val){
	fill_csr_bits(val,REG_INFO.pcie_wrate_hsclk_sel());	//CSR34[2:2]
	return *this;
}
uint
DS_txRegs::getpcie_wrate_hsclk_sel(){
	return get_csr_bits(REG_INFO.pcie_wrate_hsclk_sel());	//CSR34[2:2]
}

DS_txRegs&
DS_txRegs::settxdrv_ressel(uint val){
	fill_csr_bits(val,REG_INFO.txdrv_ressel());	//CSR34[1:0]
	return *this;
}
uint
DS_txRegs::gettxdrv_ressel(){
	return get_csr_bits(REG_INFO.txdrv_ressel());	//CSR34[1:0]
}

DS_txRegs&
DS_txRegs::settxdrv_sliceboost_en(uint val){
	fill_csr_bits(val,REG_INFO.txdrv_sliceboost_en());	//CSR35[13:13]
	return *this;
}
uint
DS_txRegs::gettxdrv_sliceboost_en(){
	return get_csr_bits(REG_INFO.txdrv_sliceboost_en());	//CSR35[13:13]
}

DS_txRegs&
DS_txRegs::setclkreg_selfbleed_pdb(uint val){
	fill_csr_bits(val,REG_INFO.clkreg_selfbleed_pdb());	//CSR35[12:12]
	return *this;
}
uint
DS_txRegs::getclkreg_selfbleed_pdb(){
	return get_csr_bits(REG_INFO.clkreg_selfbleed_pdb());	//CSR35[12:12]
}

DS_txRegs&
DS_txRegs::setclkreg_selfbleed(uint val){
	fill_csr_bits(val,REG_INFO.clkreg_selfbleed());	//CSR35[11:8]
	return *this;
}
uint
DS_txRegs::getclkreg_selfbleed(){
	return get_csr_bits(REG_INFO.clkreg_selfbleed());	//CSR35[11:8]
}

DS_txRegs&
DS_txRegs::setncaldn_offset(uint val){
	fill_csr_bits(val,REG_INFO.ncaldn_offset());	//CSR35[7:4]
	return *this;
}
uint
DS_txRegs::getncaldn_offset(){
	return get_csr_bits(REG_INFO.ncaldn_offset());	//CSR35[7:4]
}

DS_txRegs&
DS_txRegs::setncalup_offset(uint val){
	fill_csr_bits(val,REG_INFO.ncalup_offset());	//CSR35[3:0]
	return *this;
}
uint
DS_txRegs::getncalup_offset(){
	return get_csr_bits(REG_INFO.ncalup_offset());	//CSR35[3:0]
}

DS_txRegs&
DS_txRegs::setpcie_sas_sw_rstb(uint val){
	fill_csr_bits(val,REG_INFO.pcie_sas_sw_rstb());	//CSR48[15:15]
	return *this;
}
uint
DS_txRegs::getpcie_sas_sw_rstb(){
	return get_csr_bits(REG_INFO.pcie_sas_sw_rstb());	//CSR48[15:15]
}

DS_txRegs&
DS_txRegs::setpcie_sas_pin_en(uint val){
	fill_csr_bits(val,REG_INFO.pcie_sas_pin_en());	//CSR48[14:14]
	return *this;
}
uint
DS_txRegs::getpcie_sas_pin_en(){
	return get_csr_bits(REG_INFO.pcie_sas_pin_en());	//CSR48[14:14]
}

DS_txRegs&
DS_txRegs::setpma_mode(uint val){
	fill_csr_bits(val,REG_INFO.pma_mode());	//CSR48[13:12]
	return *this;
}
uint
DS_txRegs::getpma_mode(){
	return get_csr_bits(REG_INFO.pma_mode());	//CSR48[13:12]
}

DS_txRegs&
DS_txRegs::setpstate_wrate_vld(uint val){
	fill_csr_bits(val,REG_INFO.pstate_wrate_vld());	//CSR48[11:11]
	return *this;
}
uint
DS_txRegs::getpstate_wrate_vld(){
	return get_csr_bits(REG_INFO.pstate_wrate_vld());	//CSR48[11:11]
}

DS_txRegs&
DS_txRegs::setpcie_sas_power_state(uint val){
	fill_csr_bits(val,REG_INFO.pcie_sas_power_state());	//CSR48[10:8]
	return *this;
}
uint
DS_txRegs::getpcie_sas_power_state(){
	return get_csr_bits(REG_INFO.pcie_sas_power_state());	//CSR48[10:8]
}

DS_txRegs&
DS_txRegs::setpcie_sas_data_rate(uint val){
	fill_csr_bits(val,REG_INFO.pcie_sas_data_rate());	//CSR48[6:4]
	return *this;
}
uint
DS_txRegs::getpcie_sas_data_rate(){
	return get_csr_bits(REG_INFO.pcie_sas_data_rate());	//CSR48[6:4]
}

DS_txRegs&
DS_txRegs::setpcie_sas_rxtx_status_rdy(uint val){
	fill_csr_bits(val,REG_INFO.pcie_sas_rxtx_status_rdy());	//CSR48[3:3]
	return *this;
}
uint
DS_txRegs::getpcie_sas_rxtx_status_rdy(){
	return get_csr_bits(REG_INFO.pcie_sas_rxtx_status_rdy());	//CSR48[3:3]
}

DS_txRegs&
DS_txRegs::setpcie_sas_data_width(uint val){
	fill_csr_bits(val,REG_INFO.pcie_sas_data_width());	//CSR48[2:0]
	return *this;
}
uint
DS_txRegs::getpcie_sas_data_width(){
	return get_csr_bits(REG_INFO.pcie_sas_data_width());	//CSR48[2:0]
}

DS_txRegs&
DS_txRegs::setrxsigdet_pwrdnb_msk(uint val){
	fill_csr_bits(val,REG_INFO.rxsigdet_pwrdnb_msk());	//CSR49[15:15]
	return *this;
}
uint
DS_txRegs::getrxsigdet_pwrdnb_msk(){
	return get_csr_bits(REG_INFO.rxsigdet_pwrdnb_msk());	//CSR49[15:15]
}

DS_txRegs&
DS_txRegs::settxrxdet_pwrdnb_msk(uint val){
	fill_csr_bits(val,REG_INFO.txrxdet_pwrdnb_msk());	//CSR49[14:14]
	return *this;
}
uint
DS_txRegs::gettxrxdet_pwrdnb_msk(){
	return get_csr_bits(REG_INFO.txrxdet_pwrdnb_msk());	//CSR49[14:14]
}

DS_txRegs&
DS_txRegs::setrxpwrdnb_msk(uint val){
	fill_csr_bits(val,REG_INFO.rxpwrdnb_msk());	//CSR49[13:13]
	return *this;
}
uint
DS_txRegs::getrxpwrdnb_msk(){
	return get_csr_bits(REG_INFO.rxpwrdnb_msk());	//CSR49[13:13]
}

DS_txRegs&
DS_txRegs::settxpwrdnb_msk(uint val){
	fill_csr_bits(val,REG_INFO.txpwrdnb_msk());	//CSR49[12:12]
	return *this;
}
uint
DS_txRegs::gettxpwrdnb_msk(){
	return get_csr_bits(REG_INFO.txpwrdnb_msk());	//CSR49[12:12]
}

DS_txRegs&
DS_txRegs::setdsclkgen_pwrdnb_msk(uint val){
	fill_csr_bits(val,REG_INFO.dsclkgen_pwrdnb_msk());	//CSR49[11:11]
	return *this;
}
uint
DS_txRegs::getdsclkgen_pwrdnb_msk(){
	return get_csr_bits(REG_INFO.dsclkgen_pwrdnb_msk());	//CSR49[11:11]
}

DS_txRegs&
DS_txRegs::setdsclk_idac_pwrdnb_msk(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_idac_pwrdnb_msk());	//CSR49[10:10]
	return *this;
}
uint
DS_txRegs::getdsclk_idac_pwrdnb_msk(){
	return get_csr_bits(REG_INFO.dsclk_idac_pwrdnb_msk());	//CSR49[10:10]
}

DS_txRegs&
DS_txRegs::setdsclk_vregdac_pwrdnb_msk(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_vregdac_pwrdnb_msk());	//CSR49[9:9]
	return *this;
}
uint
DS_txRegs::getdsclk_vregdac_pwrdnb_msk(){
	return get_csr_bits(REG_INFO.dsclk_vregdac_pwrdnb_msk());	//CSR49[9:9]
}

DS_txRegs&
DS_txRegs::setdsclk_vregl_pwrdnb_msk(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_vregl_pwrdnb_msk());	//CSR49[8:8]
	return *this;
}
uint
DS_txRegs::getdsclk_vregl_pwrdnb_msk(){
	return get_csr_bits(REG_INFO.dsclk_vregl_pwrdnb_msk());	//CSR49[8:8]
}

DS_txRegs&
DS_txRegs::setrx_sw_sigdet_rstb_msk(uint val){
	fill_csr_bits(val,REG_INFO.rx_sw_sigdet_rstb_msk());	//CSR49[6:6]
	return *this;
}
uint
DS_txRegs::getrx_sw_sigdet_rstb_msk(){
	return get_csr_bits(REG_INFO.rx_sw_sigdet_rstb_msk());	//CSR49[6:6]
}

DS_txRegs&
DS_txRegs::setrx_sw_cdr_rstb_msk(uint val){
	fill_csr_bits(val,REG_INFO.rx_sw_cdr_rstb_msk());	//CSR49[5:5]
	return *this;
}
uint
DS_txRegs::getrx_sw_cdr_rstb_msk(){
	return get_csr_bits(REG_INFO.rx_sw_cdr_rstb_msk());	//CSR49[5:5]
}

DS_txRegs&
DS_txRegs::setrx_sw_rstb_msk(uint val){
	fill_csr_bits(val,REG_INFO.rx_sw_rstb_msk());	//CSR49[4:4]
	return *this;
}
uint
DS_txRegs::getrx_sw_rstb_msk(){
	return get_csr_bits(REG_INFO.rx_sw_rstb_msk());	//CSR49[4:4]
}

DS_txRegs&
DS_txRegs::setrx_loss_det_clk_en_msk(uint val){
	fill_csr_bits(val,REG_INFO.rx_loss_det_clk_en_msk());	//CSR49[3:3]
	return *this;
}
uint
DS_txRegs::getrx_loss_det_clk_en_msk(){
	return get_csr_bits(REG_INFO.rx_loss_det_clk_en_msk());	//CSR49[3:3]
}

DS_txRegs&
DS_txRegs::setrx_sw_clk_en_msk(uint val){
	fill_csr_bits(val,REG_INFO.rx_sw_clk_en_msk());	//CSR49[2:2]
	return *this;
}
uint
DS_txRegs::getrx_sw_clk_en_msk(){
	return get_csr_bits(REG_INFO.rx_sw_clk_en_msk());	//CSR49[2:2]
}

DS_txRegs&
DS_txRegs::settx_sw_clk_en_msk(uint val){
	fill_csr_bits(val,REG_INFO.tx_sw_clk_en_msk());	//CSR49[1:1]
	return *this;
}
uint
DS_txRegs::gettx_sw_clk_en_msk(){
	return get_csr_bits(REG_INFO.tx_sw_clk_en_msk());	//CSR49[1:1]
}

DS_txRegs&
DS_txRegs::settx_sw_rstb_msk(uint val){
	fill_csr_bits(val,REG_INFO.tx_sw_rstb_msk());	//CSR49[0:0]
	return *this;
}
uint
DS_txRegs::gettx_sw_rstb_msk(){
	return get_csr_bits(REG_INFO.tx_sw_rstb_msk());	//CSR49[0:0]
}

DS_txRegs&
DS_txRegs::setpstate_timer_div_value(uint val){
	fill_csr_bits(val,REG_INFO.pstate_timer_div_value());	//CSR50[15:12]
	return *this;
}
uint
DS_txRegs::getpstate_timer_div_value(){
	return get_csr_bits(REG_INFO.pstate_timer_div_value());	//CSR50[15:12]
}

DS_txRegs&
DS_txRegs::setpstate_timer_value(uint val){
	fill_csr_bits(val,REG_INFO.pstate_timer_value());	//CSR50[9:0]
	return *this;
}
uint
DS_txRegs::getpstate_timer_value(){
	return get_csr_bits(REG_INFO.pstate_timer_value());	//CSR50[9:0]
}

DS_txRegs&
DS_txRegs::setdsclk_timer_div_value(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_timer_div_value());	//CSR51[15:12]
	return *this;
}
uint
DS_txRegs::getdsclk_timer_div_value(){
	return get_csr_bits(REG_INFO.dsclk_timer_div_value());	//CSR51[15:12]
}

DS_txRegs&
DS_txRegs::setpcie_sas_spare(uint val){
	fill_csr_bits(val,REG_INFO.pcie_sas_spare());	//CSR51[11:4]
	return *this;
}
uint
DS_txRegs::getpcie_sas_spare(){
	return get_csr_bits(REG_INFO.pcie_sas_spare());	//CSR51[11:4]
}

DS_txRegs&
DS_txRegs::setwrate_timer_div_value(uint val){
	fill_csr_bits(val,REG_INFO.wrate_timer_div_value());	//CSR51[3:0]
	return *this;
}
uint
DS_txRegs::getwrate_timer_div_value(){
	return get_csr_bits(REG_INFO.wrate_timer_div_value());	//CSR51[3:0]
}

DS_txRegs&
DS_txRegs::setdsclk_timer_value(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_timer_value());	//CSR52[13:0]
	return *this;
}
uint
DS_txRegs::getdsclk_timer_value(){
	return get_csr_bits(REG_INFO.dsclk_timer_value());	//CSR52[13:0]
}

DS_txRegs&
DS_txRegs::setwrate_timer_value(uint val){
	fill_csr_bits(val,REG_INFO.wrate_timer_value());	//CSR53[13:0]
	return *this;
}
uint
DS_txRegs::getwrate_timer_value(){
	return get_csr_bits(REG_INFO.wrate_timer_value());	//CSR53[13:0]
}

uint
DS_txRegs::gethis_alarm_pstate_code_err(){
	return get_csr_bits(REG_INFO.his_alarm_pstate_code_err());	//CSR54[15:15]
}

uint
DS_txRegs::gethis_alarm_pstate_sw_err(){
	return get_csr_bits(REG_INFO.his_alarm_pstate_sw_err());	//CSR54[14:14]
}

uint
DS_txRegs::gethis_alarm_wrate_sw_err(){
	return get_csr_bits(REG_INFO.his_alarm_wrate_sw_err());	//CSR54[13:13]
}

uint
DS_txRegs::gethis_alarm_pstate_wrate_err(){
	return get_csr_bits(REG_INFO.his_alarm_pstate_wrate_err());	//CSR54[12:12]
}

uint
DS_txRegs::gethis_alarm_one_sw_req_vio(){
	return get_csr_bits(REG_INFO.his_alarm_one_sw_req_vio());	//CSR54[11:11]
}

uint
DS_txRegs::gethis_alarm_sw_req_drop(){
	return get_csr_bits(REG_INFO.his_alarm_sw_req_drop());	//CSR54[10:10]
}

uint
DS_txRegs::getalarm_dsclk_calib_timeout(){
	return get_csr_bits(REG_INFO.alarm_dsclk_calib_timeout());	//CSR54[9:9]
}

uint
DS_txRegs::getalarm_wrate_txsw_timeout(){
	return get_csr_bits(REG_INFO.alarm_wrate_txsw_timeout());	//CSR54[8:8]
}

uint
DS_txRegs::getalarm_wrate_rxsw_timeout(){
	return get_csr_bits(REG_INFO.alarm_wrate_rxsw_timeout());	//CSR54[7:7]
}

uint
DS_txRegs::getpstate_wrate_load_done(){
	return get_csr_bits(REG_INFO.pstate_wrate_load_done());	//CSR54[6:6]
}

uint
DS_txRegs::gethis_alarm_width_para_err(){
	return get_csr_bits(REG_INFO.his_alarm_width_para_err());	//CSR54[5:5]
}

uint
DS_txRegs::gethis_alarm_rate_para_err(){
	return get_csr_bits(REG_INFO.his_alarm_rate_para_err());	//CSR54[4:4]
}

uint
DS_txRegs::getcurr_power_state(){
	return get_csr_bits(REG_INFO.curr_power_state());	//CSR55[10:8]
}

uint
DS_txRegs::getnext_power_state(){
	return get_csr_bits(REG_INFO.next_power_state());	//CSR55[6:4]
}

uint
DS_txRegs::getpower_state_err_code(){
	return get_csr_bits(REG_INFO.power_state_err_code());	//CSR55[2:0]
}

uint
DS_txRegs::getcurr_data_rate(){
	return get_csr_bits(REG_INFO.curr_data_rate());	//CSR56[14:12]
}

uint
DS_txRegs::getnext_data_rate(){
	return get_csr_bits(REG_INFO.next_data_rate());	//CSR56[10:8]
}

uint
DS_txRegs::getcurr_data_width(){
	return get_csr_bits(REG_INFO.curr_data_width());	//CSR56[6:4]
}

uint
DS_txRegs::getnext_data_width(){
	return get_csr_bits(REG_INFO.next_data_width());	//CSR56[2:0]
}

DS_txRegs&
DS_txRegs::setdrvreg_selfbleed_pdb(uint val){
	fill_csr_bits(val,REG_INFO.drvreg_selfbleed_pdb());	//CSR57[15:15]
	return *this;
}
uint
DS_txRegs::getdrvreg_selfbleed_pdb(){
	return get_csr_bits(REG_INFO.drvreg_selfbleed_pdb());	//CSR57[15:15]
}

DS_txRegs&
DS_txRegs::setdrvreg_selfbleed(uint val){
	fill_csr_bits(val,REG_INFO.drvreg_selfbleed());	//CSR57[14:11]
	return *this;
}
uint
DS_txRegs::getdrvreg_selfbleed(){
	return get_csr_bits(REG_INFO.drvreg_selfbleed());	//CSR57[14:11]
}

uint
DS_txRegs::getpin_data_rate(){
	return get_csr_bits(REG_INFO.pin_data_rate());	//CSR57[10:8]
}

uint
DS_txRegs::getpin_data_width(){
	return get_csr_bits(REG_INFO.pin_data_width());	//CSR57[6:4]
}

uint
DS_txRegs::getpin_power_state(){
	return get_csr_bits(REG_INFO.pin_power_state());	//CSR57[2:0]
}

uint
DS_txRegs::getsw_glb_fsm_curr_st(){
	return get_csr_bits(REG_INFO.sw_glb_fsm_curr_st());	//CSR58[15:14]
}

uint
DS_txRegs::getpstate_time_fsm_curr_st(){
	return get_csr_bits(REG_INFO.pstate_time_fsm_curr_st());	//CSR58[10:8]
}

uint
DS_txRegs::getrxtx_status(){
	return get_csr_bits(REG_INFO.rxtx_status());	//CSR58[7:7]
}

uint
DS_txRegs::getwrate_sw_fsm_curr_st(){
	return get_csr_bits(REG_INFO.wrate_sw_fsm_curr_st());	//CSR58[6:4]
}

uint
DS_txRegs::getpstate_fsm_curr_st(){
	return get_csr_bits(REG_INFO.pstate_fsm_curr_st());	//CSR58[2:0]
}

DS_txRegs&
DS_txRegs::setds_dig_test_sel(uint val){
	fill_csr_bits(val,REG_INFO.ds_dig_test_sel());	//CSR59[7:0]
	return *this;
}
uint
DS_txRegs::getds_dig_test_sel(){
	return get_csr_bits(REG_INFO.ds_dig_test_sel());	//CSR59[7:0]
}

uint
DS_txRegs::getpstate_wrate_if_status(){
	return get_csr_bits(REG_INFO.pstate_wrate_if_status());	//CSR60[15:0]
}

uint
DS_txRegs::getpstate_sw_status(){
	return get_csr_bits(REG_INFO.pstate_sw_status());	//CSR61[15:0]
}

