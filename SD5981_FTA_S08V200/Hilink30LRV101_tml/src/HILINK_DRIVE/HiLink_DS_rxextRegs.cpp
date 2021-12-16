#include <HILINK_DRIVE/HiLink_DS_rxextRegs.h>

#include <iostream>
using namespace std;
DS_rxextRegs::DS_rxextRegs() {
	// TODO Auto-generated constructor stub
	for(int i=0;i<DS_RXEXT_CSR_NUM;i++){
		csr[i]=0;
	}
	sliceID=0;
	macroID=0;
	broadcast=false;
	reset_csr_verify();
}

DS_rxextRegs::~DS_rxextRegs() {}

bool
DS_rxextRegs::get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos){
	if(csrIndex>=DS_RXEXT_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	return REG_INFO.get_reg_infos(csrIndex,reg_infos);
}

DS_rxextRegs&
DS_rxextRegs::getInstance(){
	static DS_rxextRegs theInstance;
	return theInstance;
}

uint
DS_rxextRegs::get_HILINK_MAX_LANE_NUM(){
	//TODO: add your code for CSR Address mapping
	return HILINK_LANE_NUM;
}

uint
DS_rxextRegs::getAddressMapToHiLink(int csrIndex){
	if(csrIndex>=DS_RXEXT_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	//TODO: add your code for CSR Address mapping
	return (uint)(0x4000 | (broadcast << 13) | (sliceID << 9) | ((uint)0x3<< 7) | csrIndex << 1);
}


uint&
DS_rxextRegs::get_csr(uint csrIndex){
	if(csrIndex>=DS_RXEXT_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	return csr[csrIndex];
}

void
DS_rxextRegs::get_default_MacroLaneID(T_MacroLaneID& id){
	//TODO: add your code for CSR Address mapping
	id.MacroID=macroID;
	id.LaneID=sliceID;
}

uint
DS_rxextRegs::getCSRCount(){
	return DS_RXEXT_CSR_NUM;
}

string
DS_rxextRegs::getName(){
	return "DS_RXEXT";
}

///////////////////////////////////////////////////////////////////////////


	/// RX writable spare (digital)
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::dsspare1(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{0,"dsspare1",15,8}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::dsspare(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{0,"dsspare",7,0}
	};
	return reg;
}

	/// CDR 1st accumulator value.
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::rxcdraccmul1(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{1,"rxcdraccmul1",13,0}
	};
	return reg;
}

	/// CDR 2nd accumulator value.
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::rxcdraccmul2(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{2,"rxcdraccmul2",9,0}
	};
	return reg;
}

	/// CDR phase gain output value
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::rxcdrphsgnout(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{3,"rxcdrphsgnout",9,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::cen0neglatofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{4,"cen0neglatofst",14,8}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::cen0poslatofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{4,"cen0poslatofst",6,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::cen90neglatofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{5,"cen90neglatofst",14,8}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::cen90poslatofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{5,"cen90poslatofst",6,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::cen180neglatofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{6,"cen180neglatofst",14,8}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::cen180poslatofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{6,"cen180poslatofst",6,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::cen270neglatofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{7,"cen270neglatofst",14,8}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::cen270poslatofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{7,"cen270poslatofst",6,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::edg0neglatofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{8,"edg0neglatofst",14,8}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::edg0poslatofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{8,"edg0poslatofst",6,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::edg90neglatofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{9,"edg90neglatofst",14,8}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::edg90poslatofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{9,"edg90poslatofst",6,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::edg180neglatofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{10,"edg180neglatofst",14,8}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::edg180poslatofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{10,"edg180poslatofst",6,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::edg270neglatofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{11,"edg270neglatofst",14,8}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::edg270poslatofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{11,"edg270poslatofst",6,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::mon0latofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{12,"mon0latofst",14,8}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::mon90latofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{12,"mon90latofst",6,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::mon180latofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{13,"mon180latofst",14,8}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::mon270latofst(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{13,"mon270latofst",6,0}
	};
	return reg;
}

	/// New in V101: Used to simulate DS power sequence in rx_quiet mode for testing. Should be 1'b0 during mission mode
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::pwrsqrxquiet(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{14,"pwrsqrxquiet",12,12}
	};
	return reg;
}

	/// Status of rx_quiet Pin
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::rxquietstatus(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{14,"rxquietstatus",11,11}
	};
	return reg;
}

	/// ALOS Configuration
	/// 000 = both ALOS and ENERGY_DETECT pins and LOSANA register bit (RX CSR15[0]) will be set to high when the signal squelch loss detection is detected
	/// 001 = both ALOS and ENERGY_DETECT pins and LOSANA register bit (RX CSR15[0]) will be set to high when there are not enough transitions
	/// 010 = both ALOS and ENERGY_DETECT pins and LOSANA register bit (RX CSR15[0]) will be set to high when inner eye is not open enough vertically 
	/// 011 = both ALOS and ENERGY_DETECT pins and LOSANA register bit (RX CSR15[0]) will be set to high when inner eye is not open enough horizontally 
	/// 100= both ALOS and ENERGY_DETECT pins and LOSANA register bit (RX CSR15[0]) will be set to high when there are not enough transitions or inner eye is not open enough either vertically or horizontally
	/// 101= both ALOS and ENERGY_DETECT pins and LOSANA register bit (RX CSR15[0]) will be set to high when the signal squelch loss detection is detected or there are not enough transitions
	/// 110 = both ALOS and ENERGY_DETECT pins and LOSANA register bit (RX CSR15[0]) will be set to high when the signal squelch loss detection is detected or inner eye is not open enough vertically or horizontally
	/// 111= both ALOS and ENERGY_DETECT pins and LOSANA register bit (RX CSR15[0]) will be set to high when the signal squelch loss detection is detected or there are not enough transitions or inner eye is not open enough vertically or horizontally
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::aloscfg(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{14,"aloscfg",10,8}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::rxtxeeequieten(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{14,"rxtxeeequieten",7,7}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::rxtxeeealerten(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{14,"rxtxeeealerten",6,6}
	};
	return reg;
}

	/// Training enable bit; Applicable to both TX (control eye monitor) and RX (for tap mapping).
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::rxtxlttrainen(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{14,"rxtxlttrainen",5,5}
	};
	return reg;
}

	/// energy efficient ethernet enable bit. Applicable to both TX and RX.
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::rxtxeeeen(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{14,"rxtxeeeen",4,4}
	};
	return reg;
}

	/// defines the powerdown granularity of the RX circuitry when EEE tx quiet is asserted
	/// 1000: most power savings
	/// 1100: moderate power savings
	/// 1110: least power savings
	/// others: no power savings
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::rxeeepwrdbsel(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{14,"rxeeepwrdbsel",3,0}
	};
	return reg;
}

	/// Rx latch offset detector enable signal
	/// 0 = disabled
	/// 1 = enabled
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::rxlatofstdeten(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{15,"rxlatofstdeten",15,15}
	};
	return reg;
}

	/// Rx latch offset detector mode
	/// 0 = latch offset detector status in 2-bit mode
	/// 1 = latch offset detector status in 15-bit mode
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::rxlatofstmode(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{15,"rxlatofstmode",14,14}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::rxlatdatasel(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{15,"rxlatdatasel",3,0}
	};
	return reg;
}

	/// ISI accumulator 0 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::isierr0(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{16,"isierr0",15,0}
	};
	return reg;
}

	/// ISI accumulator 1 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::isierr1(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{17,"isierr1",15,0}
	};
	return reg;
}

	/// ISI accumulator 2 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::isierr2(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{18,"isierr2",15,0}
	};
	return reg;
}

	/// ISI accumulator 3 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::isierr3(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{19,"isierr3",15,0}
	};
	return reg;
}

	/// ISI accumulator 4 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::isierr4(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{20,"isierr4",15,0}
	};
	return reg;
}

	/// ISI accumulator 5 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::isierr5(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{21,"isierr5",15,0}
	};
	return reg;
}

	/// ISI accumulator 6 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::isierr6(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{22,"isierr6",15,0}
	};
	return reg;
}

	/// ISI accumulator 7 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::isierr7(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{23,"isierr7",15,0}
	};
	return reg;
}

	/// ISI accumulator 8 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::isierr8(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{24,"isierr8",15,0}
	};
	return reg;
}

	/// ISI accumulator 9 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::isierr9(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{25,"isierr9",15,0}
	};
	return reg;
}

	/// ISI accumulator 10 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::isierr10(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{26,"isierr10",15,0}
	};
	return reg;
}

	/// ISI accumulator 11 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::isierr11(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{27,"isierr11",15,0}
	};
	return reg;
}

	/// ISI accumulator 12 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::isierr12(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{28,"isierr12",15,0}
	};
	return reg;
}

	/// ISI accumulator 13 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::isierr13(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{29,"isierr13",15,0}
	};
	return reg;
}

	/// ISI accumulator 14 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::isierr14(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{30,"isierr14",15,0}
	};
	return reg;
}

	/// ISI accumulator 15 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::isierr15(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{31,"isierr15",15,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::rxspare(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{32,"rxspare",7,0}
	};
	return reg;
}

	/// CTLE regulator power down control. 
	/// 0: Power down
	/// 1: Power up
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctlevregpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{33,"ctlevregpwrdb",15,15}
	};
	return reg;
}

	/// Not Implemented in analog.
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctlevreginrushpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{33,"ctlevreginrushpwrdb",14,14}
	};
	return reg;
}

	/// CTLE regulator reference range select
	/// x0 =  select low range  (850mV to 950mV)
	/// x1 =  select high range (950mV to 1050mV)
	/// bit [1] not connected in analog
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctlevregvrefrng(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{33,"ctlevregvrefrng",13,12}
	};
	return reg;
}

	/// Enable CTLE regulator bypass mode
	/// 0 =  mission mode
	/// 1 =  bypass mode - enable CTLEVREGBYPASSSEL[2:0] to be used to manually increase sourcing capability of CTLE regulator
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctlevregbypasstohv(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{33,"ctlevregbypasstohv",11,11}
	};
	return reg;
}

	/// Voltage level control of CTLE regulator.
	/// 000 =  Minimum voltage
	/// ?.
	/// 111 =  Maximum voltage
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctlevregvrefsel(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{33,"ctlevregvrefsel",10,8}
	};
	return reg;
}

	/// Manual CTLE supply trim when in bypass mode
	/// 000 =  min supply voltage
	/// ��..
	/// 111 = max supply voltage
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctlevregbypasssel(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{33,"ctlevregbypasssel",7,5}
	};
	return reg;
}

	/// Configure CTLE regulator current sourcing capability
	/// 0 = CTLE regulator configured to only drive CTLE current load
	/// 1 =  mission mode -- CTLE regulator configured to drive CTLE + summer current load
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctlevregsummerloaden(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{33,"ctlevregsummerloaden",4,4}
	};
	return reg;
}

	/// CTLE regulator DPM trim.
	/// All bits equally weighted.
	/// 000 =  SS/TT/FF
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctlevregdpmpvt(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{33,"ctlevregdpmpvt",3,1}
	};
	return reg;
}

	/// iptat temperature compensation coefficient for Replica
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctleiptatctrltc1(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{34,"ctleiptatctrltc1",15,12}
	};
	return reg;
}

	/// iptat temperature compensation coefficient for CTLE stages
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctleiptatctrltc2(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{34,"ctleiptatctrltc2",11,8}
	};
	return reg;
}

	/// rxctle current scaling control for Replica
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctleibiastunerep(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{34,"ctleibiastunerep",5,3}
	};
	return reg;
}

	/// rxctle current scaling control for VSR CTLE Stage1
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctleibiastunestg1(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{34,"ctleibiastunestg1",2,0}
	};
	return reg;
}

	/// rxctle current scaling control for VSR CTLE Stage2
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctleibiastunestg2(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{35,"ctleibiastunestg2",15,13}
	};
	return reg;
}

	/// rxctle current scaling control for VSR CTLE Stage3
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctleibiastunestg3(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{35,"ctleibiastunestg3",12,10}
	};
	return reg;
}

	/// Rx CTLE Replica Current source calibration enable control.  
	/// 0 =  Disable
	/// 1 =  Enable
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctleicalrepen(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{35,"ctleicalrepen",5,5}
	};
	return reg;
}

	/// Calibration bits for CTLE Replica Current Source.
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctlerepical(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{35,"ctlerepical",4,0}
	};
	return reg;
}

	/// Rx CTLE Stages Current source calibration enable control. 
	/// 0 =  Disable
	/// 1 =  Enable
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctleicalctleen(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{36,"ctleicalctleen",15,15}
	};
	return reg;
}

	/// Calibration bits for CTLE Stage 1 Current Source
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctleicalst1(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{36,"ctleicalst1",14,10}
	};
	return reg;
}

	/// Calibration bits for CTLE Stage 2 Current Source
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctleicalst2(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{36,"ctleicalst2",9,5}
	};
	return reg;
}

	/// Calibration bits for CTLE Stage 3 Current Source
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::ctleicalst3(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{36,"ctleicalst3",4,0}
	};
	return reg;
}

	/// Rx Summer current source calibration enable control.
	/// 0: Disable
	/// 1: Enable
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::dfesumicalen(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{37,"dfesumicalen",14,14}
	};
	return reg;
}

	/// Calibration bits for summer current source.
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::dfesumiical(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{37,"dfesumiical",13,9}
	};
	return reg;
}

	/// Calibration bits for summer current source.
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::dfesumqical(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{37,"dfesumqical",8,4}
	};
	return reg;
}

	/// iptat temperature compensation coefficient for summer
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::dfesumiptattcctrl(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{37,"dfesumiptattcctrl",3,0}
	};
	return reg;
}

	/// resets edge cycling digital block. Active low
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::edgecycsoftrstb(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{38,"edgecycsoftrstb",15,15}
	};
	return reg;
}

	/// Edge channel cycling enable
	/// 0 =  Normal Mode; 
	/// 1 =  Edge Channel Cycling enable
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::edgecycen(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{38,"edgecycen",14,14}
	};
	return reg;
}

	/// Edge channel cycling mode
	/// 0 =  partial cycling; 1 =  full cycling
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::edgecymode(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{38,"edgecymode",13,13}
	};
	return reg;
}

	/// Power sequence enable for edge channel cycling
	/// 0 =  disable power sequencing for edge channel cycling
	/// ;1 =  enable power sequencing for edge channel cycling;
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::edgecycpsen(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{38,"edgecycpsen",12,12}
	};
	return reg;
}

	/// edge cycling analog settling time control.
	/// 00 = 0 word cycle
	/// 01 = 2 word cycles
	/// 10 = 4 word cycles 
	/// 11 = 8 word cycles
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::edgcycanastl(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{38,"edgcycanastl",11,10}
	};
	return reg;
}

	/// Edge channel transition step during edge cycling
	/// 00 = 1 cycle 
	/// 01 = 2 cycles
	/// 10 = 4 cycles 
	/// 11 = 8 cycles
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::edgcyctranstep(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{38,"edgcyctranstep",9,8}
	};
	return reg;
}

	/// Edge channel off time during edge cycling
	/// 0000 = 10 cycles;    0001 = 20 cycles;     0010 = 30 cycles; 
	/// 0011 = 40 cycles;    0100 = 50 cycles;     0101 = 75 cycles; 
	/// 0110 = 100 cycles;  0111 = 150 cycles;   1000 = 200 cycles; 
	/// 1001 = 300 cycles;  1010 = 400 cycles;   1011 = 600 cycles; 
	/// 1100 = 800 cycles;  1101 = 1200 cycles; 1110 = 1600 cycles
	/// ;1111 = 2400 cycles
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::edgcycofftime(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{38,"edgcycofftime",7,4}
	};
	return reg;
}

	/// Edge channel on time during edge cycling (number of word clock cycles)
	/// 0000 = 10 cycles;    0001 = 20 cycles;     0010 = 30 cycles; 
	/// 0011 = 40 cycles;    0100 = 50 cycles;     0101 = 60 cycles; 
	/// 0110 = 70 cycles;    0111 =  80 cycles;    1000 = 90 cycles; 
	/// 1001 = 100 cycles;  1010 = 110 cycles;  1011 = 120 cycles; 
	/// 1100 = 130 cycles;  1101 = 140 cycles;  1110 = 150 cycles
	/// ;1111 = 160 cycles
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::edgcycontime(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{38,"edgcycontime",3,0}
	};
	return reg;
}

	/// 10-bit repeating pattern (TRP) detection enable.
	/// 0 = disable; 1 = Enable
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::trpdeten(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{39,"trpdeten",15,15}
	};
	return reg;
}

	/// Decision threshold.  
	/// 000 = 4;    001 = 8;     010 = 16;    011 = 32; 
	/// 100 = 64; 101= 128;  110 = 256;  111 = 512;
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::trpdetthr(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{39,"trpdetthr",14,12}
	};
	return reg;
}

	/// Total number of bits considered. 
	/// 00 = 160 bits;   01 = 320 bits  
	/// 10 = 640 bits;   11 = 1280 bits
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::trpdetwin(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{39,"trpdetwin",9,8}
	};
	return reg;
}

	/// 10-bit repeating pattern (TRP) detection status.
	/// 0 = 10-bit repeating pattern not detected.
	/// 1 = 10-bit repeating pattern detected. Remains at 1 until read.
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::trpdetstatus(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{39,"trpdetstatus",0,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::rxcalibtasksel1(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{40,"rxcalibtasksel1",15,0}
	};
	return reg;
}

	/// Rx Calibration Task selection list2.  Here 1=bypass and 0= perform calibration
	/// bit[15] =   center channel latch calibration
	/// bit[14] =   edge channel latch calibration
	/// bit[13] =   monitor channel latch calibration
	/// bits[12] =  bypass ctle stage5,6 and summer stages offset re-calibration  which is run before any center/edge/monitor latch calibration
	/// bit[11] =  bypass 1st load summer resistance calibration which is run before the Ipath of Even offset calibration
	/// bits[10:9] =  bypasses the center and edge negative latch offset calibration respectively required for VSR
	/// bits[8:0] =  not used
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::rxcalibtasksel2(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{41,"rxcalibtasksel2",15,0}
	};
	return reg;
}

	/// User defined WL or HL value to be used in the peak detector algorithm when EMTASKCTRL[4:3] = 2�b11 or provided as the WL value for area calculation purposes
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::emswcorner0(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{42,"emswcorner0",8,0}
	};
	return reg;
}

	/// User defined WR or HU value to be used in the peak detector algorithm when EMTASKCTRL[4:3] = 2�b11 or provided as the WR value for area calculation purposes
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::emswcorner1(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{43,"emswcorner1",8,0}
	};
	return reg;
}

	/// Rx calibration comparator direction
	/// [15:7] Reserved
	/// [6] RX LATCH
	/// [5] CTLE regulator
	/// [4] Opamp
	/// [3] Summer Load Resistance
	/// [2] Clock and Data Regulator
	/// [1] Signal Detection
	/// [0] CML stage
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::rxcaldir(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{44,"rxcaldir",15,0}
	};
	return reg;
}

	/// RX writable spare2 (digital)
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::dsspare2(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{45,"dsspare2",15,0}
	};
	return reg;
}

	/// RX writable spare2 (digital)
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::dsspare3(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{46,"dsspare3",15,0}
	};
	return reg;
}

	/// RX writable spare2 (digital)
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::dsspare4(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{47,"dsspare4",15,0}
	};
	return reg;
}

	/// Configures the number of 10-bit words to accumulate for reporting the status
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::rxlatofstnumword(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{48,"rxlatofstnumword",10,0}
	};
	return reg;
}

	/// Configures the offset detection threshold by programming the number of expected 'logic 1' bits in the accumulation window (defined by RXLATOFSTNUMWORD)
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::rxlatofstthresh(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{49,"rxlatofstthresh",14,0}
	};
	return reg;
}

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
const T_REG_INFO_EX&
DS_rxextRegs::_REG_INFO::rxlatofstdetstatus(){
	const static T_REG_INFO_EX reg={DS_rxextRegs::getInstance(),
		{50,"rxlatofstdetstatus",14,0}
	};
	return reg;
}
bool
DS_rxextRegs::_REG_INFO::get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos){
	reg_infos.clear();
	switch(csr){
		case 0:
			reg_infos.push_back(dsspare1().reg_info);
			reg_infos.push_back(dsspare().reg_info);
			break;
		case 1:
			reg_infos.push_back(rxcdraccmul1().reg_info);
			break;
		case 2:
			reg_infos.push_back(rxcdraccmul2().reg_info);
			break;
		case 3:
			reg_infos.push_back(rxcdrphsgnout().reg_info);
			break;
		case 4:
			reg_infos.push_back(cen0neglatofst().reg_info);
			reg_infos.push_back(cen0poslatofst().reg_info);
			break;
		case 5:
			reg_infos.push_back(cen90neglatofst().reg_info);
			reg_infos.push_back(cen90poslatofst().reg_info);
			break;
		case 6:
			reg_infos.push_back(cen180neglatofst().reg_info);
			reg_infos.push_back(cen180poslatofst().reg_info);
			break;
		case 7:
			reg_infos.push_back(cen270neglatofst().reg_info);
			reg_infos.push_back(cen270poslatofst().reg_info);
			break;
		case 8:
			reg_infos.push_back(edg0neglatofst().reg_info);
			reg_infos.push_back(edg0poslatofst().reg_info);
			break;
		case 9:
			reg_infos.push_back(edg90neglatofst().reg_info);
			reg_infos.push_back(edg90poslatofst().reg_info);
			break;
		case 10:
			reg_infos.push_back(edg180neglatofst().reg_info);
			reg_infos.push_back(edg180poslatofst().reg_info);
			break;
		case 11:
			reg_infos.push_back(edg270neglatofst().reg_info);
			reg_infos.push_back(edg270poslatofst().reg_info);
			break;
		case 12:
			reg_infos.push_back(mon0latofst().reg_info);
			reg_infos.push_back(mon90latofst().reg_info);
			break;
		case 13:
			reg_infos.push_back(mon180latofst().reg_info);
			reg_infos.push_back(mon270latofst().reg_info);
			break;
		case 14:
			reg_infos.push_back(pwrsqrxquiet().reg_info);
			reg_infos.push_back(rxquietstatus().reg_info);
			reg_infos.push_back(aloscfg().reg_info);
			reg_infos.push_back(rxtxeeequieten().reg_info);
			reg_infos.push_back(rxtxeeealerten().reg_info);
			reg_infos.push_back(rxtxlttrainen().reg_info);
			reg_infos.push_back(rxtxeeeen().reg_info);
			reg_infos.push_back(rxeeepwrdbsel().reg_info);
			break;
		case 15:
			reg_infos.push_back(rxlatofstdeten().reg_info);
			reg_infos.push_back(rxlatofstmode().reg_info);
			reg_infos.push_back(rxlatdatasel().reg_info);
			break;
		case 16:
			reg_infos.push_back(isierr0().reg_info);
			break;
		case 17:
			reg_infos.push_back(isierr1().reg_info);
			break;
		case 18:
			reg_infos.push_back(isierr2().reg_info);
			break;
		case 19:
			reg_infos.push_back(isierr3().reg_info);
			break;
		case 20:
			reg_infos.push_back(isierr4().reg_info);
			break;
		case 21:
			reg_infos.push_back(isierr5().reg_info);
			break;
		case 22:
			reg_infos.push_back(isierr6().reg_info);
			break;
		case 23:
			reg_infos.push_back(isierr7().reg_info);
			break;
		case 24:
			reg_infos.push_back(isierr8().reg_info);
			break;
		case 25:
			reg_infos.push_back(isierr9().reg_info);
			break;
		case 26:
			reg_infos.push_back(isierr10().reg_info);
			break;
		case 27:
			reg_infos.push_back(isierr11().reg_info);
			break;
		case 28:
			reg_infos.push_back(isierr12().reg_info);
			break;
		case 29:
			reg_infos.push_back(isierr13().reg_info);
			break;
		case 30:
			reg_infos.push_back(isierr14().reg_info);
			break;
		case 31:
			reg_infos.push_back(isierr15().reg_info);
			break;
		case 32:
			reg_infos.push_back(rxspare().reg_info);
			break;
		case 33:
			reg_infos.push_back(ctlevregpwrdb().reg_info);
			reg_infos.push_back(ctlevreginrushpwrdb().reg_info);
			reg_infos.push_back(ctlevregvrefrng().reg_info);
			reg_infos.push_back(ctlevregbypasstohv().reg_info);
			reg_infos.push_back(ctlevregvrefsel().reg_info);
			reg_infos.push_back(ctlevregbypasssel().reg_info);
			reg_infos.push_back(ctlevregsummerloaden().reg_info);
			reg_infos.push_back(ctlevregdpmpvt().reg_info);
			break;
		case 34:
			reg_infos.push_back(ctleiptatctrltc1().reg_info);
			reg_infos.push_back(ctleiptatctrltc2().reg_info);
			reg_infos.push_back(ctleibiastunerep().reg_info);
			reg_infos.push_back(ctleibiastunestg1().reg_info);
			break;
		case 35:
			reg_infos.push_back(ctleibiastunestg2().reg_info);
			reg_infos.push_back(ctleibiastunestg3().reg_info);
			reg_infos.push_back(ctleicalrepen().reg_info);
			reg_infos.push_back(ctlerepical().reg_info);
			break;
		case 36:
			reg_infos.push_back(ctleicalctleen().reg_info);
			reg_infos.push_back(ctleicalst1().reg_info);
			reg_infos.push_back(ctleicalst2().reg_info);
			reg_infos.push_back(ctleicalst3().reg_info);
			break;
		case 37:
			reg_infos.push_back(dfesumicalen().reg_info);
			reg_infos.push_back(dfesumiical().reg_info);
			reg_infos.push_back(dfesumqical().reg_info);
			reg_infos.push_back(dfesumiptattcctrl().reg_info);
			break;
		case 38:
			reg_infos.push_back(edgecycsoftrstb().reg_info);
			reg_infos.push_back(edgecycen().reg_info);
			reg_infos.push_back(edgecymode().reg_info);
			reg_infos.push_back(edgecycpsen().reg_info);
			reg_infos.push_back(edgcycanastl().reg_info);
			reg_infos.push_back(edgcyctranstep().reg_info);
			reg_infos.push_back(edgcycofftime().reg_info);
			reg_infos.push_back(edgcycontime().reg_info);
			break;
		case 39:
			reg_infos.push_back(trpdeten().reg_info);
			reg_infos.push_back(trpdetthr().reg_info);
			reg_infos.push_back(trpdetwin().reg_info);
			reg_infos.push_back(trpdetstatus().reg_info);
			break;
		case 40:
			reg_infos.push_back(rxcalibtasksel1().reg_info);
			break;
		case 41:
			reg_infos.push_back(rxcalibtasksel2().reg_info);
			break;
		case 42:
			reg_infos.push_back(emswcorner0().reg_info);
			break;
		case 43:
			reg_infos.push_back(emswcorner1().reg_info);
			break;
		case 44:
			reg_infos.push_back(rxcaldir().reg_info);
			break;
		case 45:
			reg_infos.push_back(dsspare2().reg_info);
			break;
		case 46:
			reg_infos.push_back(dsspare3().reg_info);
			break;
		case 47:
			reg_infos.push_back(dsspare4().reg_info);
			break;
		case 48:
			reg_infos.push_back(rxlatofstnumword().reg_info);
			break;
		case 49:
			reg_infos.push_back(rxlatofstthresh().reg_info);
			break;
		case 50:
			reg_infos.push_back(rxlatofstdetstatus().reg_info);
			break;
		default:
			break;
	}
	return (reg_infos.size()>0);
}


DS_rxextRegs&
DS_rxextRegs::setdsspare1(uint val){
	fill_csr_bits(val,REG_INFO.dsspare1());	//CSR0[15:8]
	return *this;
}
uint
DS_rxextRegs::getdsspare1(){
	return get_csr_bits(REG_INFO.dsspare1());	//CSR0[15:8]
}

DS_rxextRegs&
DS_rxextRegs::setdsspare(uint val){
	fill_csr_bits(val,REG_INFO.dsspare());	//CSR0[7:0]
	return *this;
}
uint
DS_rxextRegs::getdsspare(){
	return get_csr_bits(REG_INFO.dsspare());	//CSR0[7:0]
}

uint
DS_rxextRegs::getrxcdraccmul1(){
	return get_csr_bits(REG_INFO.rxcdraccmul1());	//CSR1[13:0]
}

uint
DS_rxextRegs::getrxcdraccmul2(){
	return get_csr_bits(REG_INFO.rxcdraccmul2());	//CSR2[9:0]
}

uint
DS_rxextRegs::getrxcdrphsgnout(){
	return get_csr_bits(REG_INFO.rxcdrphsgnout());	//CSR3[9:0]
}

DS_rxextRegs&
DS_rxextRegs::setcen0neglatofst(uint val){
	fill_csr_bits(val,REG_INFO.cen0neglatofst());	//CSR4[14:8]
	return *this;
}
uint
DS_rxextRegs::getcen0neglatofst(){
	return get_csr_bits(REG_INFO.cen0neglatofst());	//CSR4[14:8]
}

DS_rxextRegs&
DS_rxextRegs::setcen0poslatofst(uint val){
	fill_csr_bits(val,REG_INFO.cen0poslatofst());	//CSR4[6:0]
	return *this;
}
uint
DS_rxextRegs::getcen0poslatofst(){
	return get_csr_bits(REG_INFO.cen0poslatofst());	//CSR4[6:0]
}

DS_rxextRegs&
DS_rxextRegs::setcen90neglatofst(uint val){
	fill_csr_bits(val,REG_INFO.cen90neglatofst());	//CSR5[14:8]
	return *this;
}
uint
DS_rxextRegs::getcen90neglatofst(){
	return get_csr_bits(REG_INFO.cen90neglatofst());	//CSR5[14:8]
}

DS_rxextRegs&
DS_rxextRegs::setcen90poslatofst(uint val){
	fill_csr_bits(val,REG_INFO.cen90poslatofst());	//CSR5[6:0]
	return *this;
}
uint
DS_rxextRegs::getcen90poslatofst(){
	return get_csr_bits(REG_INFO.cen90poslatofst());	//CSR5[6:0]
}

DS_rxextRegs&
DS_rxextRegs::setcen180neglatofst(uint val){
	fill_csr_bits(val,REG_INFO.cen180neglatofst());	//CSR6[14:8]
	return *this;
}
uint
DS_rxextRegs::getcen180neglatofst(){
	return get_csr_bits(REG_INFO.cen180neglatofst());	//CSR6[14:8]
}

DS_rxextRegs&
DS_rxextRegs::setcen180poslatofst(uint val){
	fill_csr_bits(val,REG_INFO.cen180poslatofst());	//CSR6[6:0]
	return *this;
}
uint
DS_rxextRegs::getcen180poslatofst(){
	return get_csr_bits(REG_INFO.cen180poslatofst());	//CSR6[6:0]
}

DS_rxextRegs&
DS_rxextRegs::setcen270neglatofst(uint val){
	fill_csr_bits(val,REG_INFO.cen270neglatofst());	//CSR7[14:8]
	return *this;
}
uint
DS_rxextRegs::getcen270neglatofst(){
	return get_csr_bits(REG_INFO.cen270neglatofst());	//CSR7[14:8]
}

DS_rxextRegs&
DS_rxextRegs::setcen270poslatofst(uint val){
	fill_csr_bits(val,REG_INFO.cen270poslatofst());	//CSR7[6:0]
	return *this;
}
uint
DS_rxextRegs::getcen270poslatofst(){
	return get_csr_bits(REG_INFO.cen270poslatofst());	//CSR7[6:0]
}

DS_rxextRegs&
DS_rxextRegs::setedg0neglatofst(uint val){
	fill_csr_bits(val,REG_INFO.edg0neglatofst());	//CSR8[14:8]
	return *this;
}
uint
DS_rxextRegs::getedg0neglatofst(){
	return get_csr_bits(REG_INFO.edg0neglatofst());	//CSR8[14:8]
}

DS_rxextRegs&
DS_rxextRegs::setedg0poslatofst(uint val){
	fill_csr_bits(val,REG_INFO.edg0poslatofst());	//CSR8[6:0]
	return *this;
}
uint
DS_rxextRegs::getedg0poslatofst(){
	return get_csr_bits(REG_INFO.edg0poslatofst());	//CSR8[6:0]
}

DS_rxextRegs&
DS_rxextRegs::setedg90neglatofst(uint val){
	fill_csr_bits(val,REG_INFO.edg90neglatofst());	//CSR9[14:8]
	return *this;
}
uint
DS_rxextRegs::getedg90neglatofst(){
	return get_csr_bits(REG_INFO.edg90neglatofst());	//CSR9[14:8]
}

DS_rxextRegs&
DS_rxextRegs::setedg90poslatofst(uint val){
	fill_csr_bits(val,REG_INFO.edg90poslatofst());	//CSR9[6:0]
	return *this;
}
uint
DS_rxextRegs::getedg90poslatofst(){
	return get_csr_bits(REG_INFO.edg90poslatofst());	//CSR9[6:0]
}

DS_rxextRegs&
DS_rxextRegs::setedg180neglatofst(uint val){
	fill_csr_bits(val,REG_INFO.edg180neglatofst());	//CSR10[14:8]
	return *this;
}
uint
DS_rxextRegs::getedg180neglatofst(){
	return get_csr_bits(REG_INFO.edg180neglatofst());	//CSR10[14:8]
}

DS_rxextRegs&
DS_rxextRegs::setedg180poslatofst(uint val){
	fill_csr_bits(val,REG_INFO.edg180poslatofst());	//CSR10[6:0]
	return *this;
}
uint
DS_rxextRegs::getedg180poslatofst(){
	return get_csr_bits(REG_INFO.edg180poslatofst());	//CSR10[6:0]
}

DS_rxextRegs&
DS_rxextRegs::setedg270neglatofst(uint val){
	fill_csr_bits(val,REG_INFO.edg270neglatofst());	//CSR11[14:8]
	return *this;
}
uint
DS_rxextRegs::getedg270neglatofst(){
	return get_csr_bits(REG_INFO.edg270neglatofst());	//CSR11[14:8]
}

DS_rxextRegs&
DS_rxextRegs::setedg270poslatofst(uint val){
	fill_csr_bits(val,REG_INFO.edg270poslatofst());	//CSR11[6:0]
	return *this;
}
uint
DS_rxextRegs::getedg270poslatofst(){
	return get_csr_bits(REG_INFO.edg270poslatofst());	//CSR11[6:0]
}

DS_rxextRegs&
DS_rxextRegs::setmon0latofst(uint val){
	fill_csr_bits(val,REG_INFO.mon0latofst());	//CSR12[14:8]
	return *this;
}
uint
DS_rxextRegs::getmon0latofst(){
	return get_csr_bits(REG_INFO.mon0latofst());	//CSR12[14:8]
}

DS_rxextRegs&
DS_rxextRegs::setmon90latofst(uint val){
	fill_csr_bits(val,REG_INFO.mon90latofst());	//CSR12[6:0]
	return *this;
}
uint
DS_rxextRegs::getmon90latofst(){
	return get_csr_bits(REG_INFO.mon90latofst());	//CSR12[6:0]
}

DS_rxextRegs&
DS_rxextRegs::setmon180latofst(uint val){
	fill_csr_bits(val,REG_INFO.mon180latofst());	//CSR13[14:8]
	return *this;
}
uint
DS_rxextRegs::getmon180latofst(){
	return get_csr_bits(REG_INFO.mon180latofst());	//CSR13[14:8]
}

DS_rxextRegs&
DS_rxextRegs::setmon270latofst(uint val){
	fill_csr_bits(val,REG_INFO.mon270latofst());	//CSR13[6:0]
	return *this;
}
uint
DS_rxextRegs::getmon270latofst(){
	return get_csr_bits(REG_INFO.mon270latofst());	//CSR13[6:0]
}

DS_rxextRegs&
DS_rxextRegs::setpwrsqrxquiet(uint val){
	fill_csr_bits(val,REG_INFO.pwrsqrxquiet());	//CSR14[12:12]
	return *this;
}
uint
DS_rxextRegs::getpwrsqrxquiet(){
	return get_csr_bits(REG_INFO.pwrsqrxquiet());	//CSR14[12:12]
}

uint
DS_rxextRegs::getrxquietstatus(){
	return get_csr_bits(REG_INFO.rxquietstatus());	//CSR14[11:11]
}

DS_rxextRegs&
DS_rxextRegs::setaloscfg(uint val){
	fill_csr_bits(val,REG_INFO.aloscfg());	//CSR14[10:8]
	return *this;
}
uint
DS_rxextRegs::getaloscfg(){
	return get_csr_bits(REG_INFO.aloscfg());	//CSR14[10:8]
}

DS_rxextRegs&
DS_rxextRegs::setrxtxeeequieten(uint val){
	fill_csr_bits(val,REG_INFO.rxtxeeequieten());	//CSR14[7:7]
	return *this;
}
uint
DS_rxextRegs::getrxtxeeequieten(){
	return get_csr_bits(REG_INFO.rxtxeeequieten());	//CSR14[7:7]
}

DS_rxextRegs&
DS_rxextRegs::setrxtxeeealerten(uint val){
	fill_csr_bits(val,REG_INFO.rxtxeeealerten());	//CSR14[6:6]
	return *this;
}
uint
DS_rxextRegs::getrxtxeeealerten(){
	return get_csr_bits(REG_INFO.rxtxeeealerten());	//CSR14[6:6]
}

DS_rxextRegs&
DS_rxextRegs::setrxtxlttrainen(uint val){
	fill_csr_bits(val,REG_INFO.rxtxlttrainen());	//CSR14[5:5]
	return *this;
}
uint
DS_rxextRegs::getrxtxlttrainen(){
	return get_csr_bits(REG_INFO.rxtxlttrainen());	//CSR14[5:5]
}

DS_rxextRegs&
DS_rxextRegs::setrxtxeeeen(uint val){
	fill_csr_bits(val,REG_INFO.rxtxeeeen());	//CSR14[4:4]
	return *this;
}
uint
DS_rxextRegs::getrxtxeeeen(){
	return get_csr_bits(REG_INFO.rxtxeeeen());	//CSR14[4:4]
}

DS_rxextRegs&
DS_rxextRegs::setrxeeepwrdbsel(uint val){
	fill_csr_bits(val,REG_INFO.rxeeepwrdbsel());	//CSR14[3:0]
	return *this;
}
uint
DS_rxextRegs::getrxeeepwrdbsel(){
	return get_csr_bits(REG_INFO.rxeeepwrdbsel());	//CSR14[3:0]
}

DS_rxextRegs&
DS_rxextRegs::setrxlatofstdeten(uint val){
	fill_csr_bits(val,REG_INFO.rxlatofstdeten());	//CSR15[15:15]
	return *this;
}
uint
DS_rxextRegs::getrxlatofstdeten(){
	return get_csr_bits(REG_INFO.rxlatofstdeten());	//CSR15[15:15]
}

DS_rxextRegs&
DS_rxextRegs::setrxlatofstmode(uint val){
	fill_csr_bits(val,REG_INFO.rxlatofstmode());	//CSR15[14:14]
	return *this;
}
uint
DS_rxextRegs::getrxlatofstmode(){
	return get_csr_bits(REG_INFO.rxlatofstmode());	//CSR15[14:14]
}

DS_rxextRegs&
DS_rxextRegs::setrxlatdatasel(uint val){
	fill_csr_bits(val,REG_INFO.rxlatdatasel());	//CSR15[3:0]
	return *this;
}
uint
DS_rxextRegs::getrxlatdatasel(){
	return get_csr_bits(REG_INFO.rxlatdatasel());	//CSR15[3:0]
}

uint
DS_rxextRegs::getisierr0(){
	return get_csr_bits(REG_INFO.isierr0());	//CSR16[15:0]
}

uint
DS_rxextRegs::getisierr1(){
	return get_csr_bits(REG_INFO.isierr1());	//CSR17[15:0]
}

uint
DS_rxextRegs::getisierr2(){
	return get_csr_bits(REG_INFO.isierr2());	//CSR18[15:0]
}

uint
DS_rxextRegs::getisierr3(){
	return get_csr_bits(REG_INFO.isierr3());	//CSR19[15:0]
}

uint
DS_rxextRegs::getisierr4(){
	return get_csr_bits(REG_INFO.isierr4());	//CSR20[15:0]
}

uint
DS_rxextRegs::getisierr5(){
	return get_csr_bits(REG_INFO.isierr5());	//CSR21[15:0]
}

uint
DS_rxextRegs::getisierr6(){
	return get_csr_bits(REG_INFO.isierr6());	//CSR22[15:0]
}

uint
DS_rxextRegs::getisierr7(){
	return get_csr_bits(REG_INFO.isierr7());	//CSR23[15:0]
}

uint
DS_rxextRegs::getisierr8(){
	return get_csr_bits(REG_INFO.isierr8());	//CSR24[15:0]
}

uint
DS_rxextRegs::getisierr9(){
	return get_csr_bits(REG_INFO.isierr9());	//CSR25[15:0]
}

uint
DS_rxextRegs::getisierr10(){
	return get_csr_bits(REG_INFO.isierr10());	//CSR26[15:0]
}

uint
DS_rxextRegs::getisierr11(){
	return get_csr_bits(REG_INFO.isierr11());	//CSR27[15:0]
}

uint
DS_rxextRegs::getisierr12(){
	return get_csr_bits(REG_INFO.isierr12());	//CSR28[15:0]
}

uint
DS_rxextRegs::getisierr13(){
	return get_csr_bits(REG_INFO.isierr13());	//CSR29[15:0]
}

uint
DS_rxextRegs::getisierr14(){
	return get_csr_bits(REG_INFO.isierr14());	//CSR30[15:0]
}

uint
DS_rxextRegs::getisierr15(){
	return get_csr_bits(REG_INFO.isierr15());	//CSR31[15:0]
}

DS_rxextRegs&
DS_rxextRegs::setrxspare(uint val){
	fill_csr_bits(val,REG_INFO.rxspare());	//CSR32[7:0]
	return *this;
}
uint
DS_rxextRegs::getrxspare(){
	return get_csr_bits(REG_INFO.rxspare());	//CSR32[7:0]
}

DS_rxextRegs&
DS_rxextRegs::setctlevregpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.ctlevregpwrdb());	//CSR33[15:15]
	return *this;
}
uint
DS_rxextRegs::getctlevregpwrdb(){
	return get_csr_bits(REG_INFO.ctlevregpwrdb());	//CSR33[15:15]
}

DS_rxextRegs&
DS_rxextRegs::setctlevreginrushpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.ctlevreginrushpwrdb());	//CSR33[14:14]
	return *this;
}
uint
DS_rxextRegs::getctlevreginrushpwrdb(){
	return get_csr_bits(REG_INFO.ctlevreginrushpwrdb());	//CSR33[14:14]
}

DS_rxextRegs&
DS_rxextRegs::setctlevregvrefrng(uint val){
	fill_csr_bits(val,REG_INFO.ctlevregvrefrng());	//CSR33[13:12]
	return *this;
}
uint
DS_rxextRegs::getctlevregvrefrng(){
	return get_csr_bits(REG_INFO.ctlevregvrefrng());	//CSR33[13:12]
}

DS_rxextRegs&
DS_rxextRegs::setctlevregbypasstohv(uint val){
	fill_csr_bits(val,REG_INFO.ctlevregbypasstohv());	//CSR33[11:11]
	return *this;
}
uint
DS_rxextRegs::getctlevregbypasstohv(){
	return get_csr_bits(REG_INFO.ctlevregbypasstohv());	//CSR33[11:11]
}

DS_rxextRegs&
DS_rxextRegs::setctlevregvrefsel(uint val){
	fill_csr_bits(val,REG_INFO.ctlevregvrefsel());	//CSR33[10:8]
	return *this;
}
uint
DS_rxextRegs::getctlevregvrefsel(){
	return get_csr_bits(REG_INFO.ctlevregvrefsel());	//CSR33[10:8]
}

DS_rxextRegs&
DS_rxextRegs::setctlevregbypasssel(uint val){
	fill_csr_bits(val,REG_INFO.ctlevregbypasssel());	//CSR33[7:5]
	return *this;
}
uint
DS_rxextRegs::getctlevregbypasssel(){
	return get_csr_bits(REG_INFO.ctlevregbypasssel());	//CSR33[7:5]
}

DS_rxextRegs&
DS_rxextRegs::setctlevregsummerloaden(uint val){
	fill_csr_bits(val,REG_INFO.ctlevregsummerloaden());	//CSR33[4:4]
	return *this;
}
uint
DS_rxextRegs::getctlevregsummerloaden(){
	return get_csr_bits(REG_INFO.ctlevregsummerloaden());	//CSR33[4:4]
}

DS_rxextRegs&
DS_rxextRegs::setctlevregdpmpvt(uint val){
	fill_csr_bits(val,REG_INFO.ctlevregdpmpvt());	//CSR33[3:1]
	return *this;
}
uint
DS_rxextRegs::getctlevregdpmpvt(){
	return get_csr_bits(REG_INFO.ctlevregdpmpvt());	//CSR33[3:1]
}

DS_rxextRegs&
DS_rxextRegs::setctleiptatctrltc1(uint val){
	fill_csr_bits(val,REG_INFO.ctleiptatctrltc1());	//CSR34[15:12]
	return *this;
}
uint
DS_rxextRegs::getctleiptatctrltc1(){
	return get_csr_bits(REG_INFO.ctleiptatctrltc1());	//CSR34[15:12]
}

DS_rxextRegs&
DS_rxextRegs::setctleiptatctrltc2(uint val){
	fill_csr_bits(val,REG_INFO.ctleiptatctrltc2());	//CSR34[11:8]
	return *this;
}
uint
DS_rxextRegs::getctleiptatctrltc2(){
	return get_csr_bits(REG_INFO.ctleiptatctrltc2());	//CSR34[11:8]
}

DS_rxextRegs&
DS_rxextRegs::setctleibiastunerep(uint val){
	fill_csr_bits(val,REG_INFO.ctleibiastunerep());	//CSR34[5:3]
	return *this;
}
uint
DS_rxextRegs::getctleibiastunerep(){
	return get_csr_bits(REG_INFO.ctleibiastunerep());	//CSR34[5:3]
}

DS_rxextRegs&
DS_rxextRegs::setctleibiastunestg1(uint val){
	fill_csr_bits(val,REG_INFO.ctleibiastunestg1());	//CSR34[2:0]
	return *this;
}
uint
DS_rxextRegs::getctleibiastunestg1(){
	return get_csr_bits(REG_INFO.ctleibiastunestg1());	//CSR34[2:0]
}

DS_rxextRegs&
DS_rxextRegs::setctleibiastunestg2(uint val){
	fill_csr_bits(val,REG_INFO.ctleibiastunestg2());	//CSR35[15:13]
	return *this;
}
uint
DS_rxextRegs::getctleibiastunestg2(){
	return get_csr_bits(REG_INFO.ctleibiastunestg2());	//CSR35[15:13]
}

DS_rxextRegs&
DS_rxextRegs::setctleibiastunestg3(uint val){
	fill_csr_bits(val,REG_INFO.ctleibiastunestg3());	//CSR35[12:10]
	return *this;
}
uint
DS_rxextRegs::getctleibiastunestg3(){
	return get_csr_bits(REG_INFO.ctleibiastunestg3());	//CSR35[12:10]
}

DS_rxextRegs&
DS_rxextRegs::setctleicalrepen(uint val){
	fill_csr_bits(val,REG_INFO.ctleicalrepen());	//CSR35[5:5]
	return *this;
}
uint
DS_rxextRegs::getctleicalrepen(){
	return get_csr_bits(REG_INFO.ctleicalrepen());	//CSR35[5:5]
}

DS_rxextRegs&
DS_rxextRegs::setctlerepical(uint val){
	fill_csr_bits(val,REG_INFO.ctlerepical());	//CSR35[4:0]
	return *this;
}
uint
DS_rxextRegs::getctlerepical(){
	return get_csr_bits(REG_INFO.ctlerepical());	//CSR35[4:0]
}

DS_rxextRegs&
DS_rxextRegs::setctleicalctleen(uint val){
	fill_csr_bits(val,REG_INFO.ctleicalctleen());	//CSR36[15:15]
	return *this;
}
uint
DS_rxextRegs::getctleicalctleen(){
	return get_csr_bits(REG_INFO.ctleicalctleen());	//CSR36[15:15]
}

DS_rxextRegs&
DS_rxextRegs::setctleicalst1(uint val){
	fill_csr_bits(val,REG_INFO.ctleicalst1());	//CSR36[14:10]
	return *this;
}
uint
DS_rxextRegs::getctleicalst1(){
	return get_csr_bits(REG_INFO.ctleicalst1());	//CSR36[14:10]
}

DS_rxextRegs&
DS_rxextRegs::setctleicalst2(uint val){
	fill_csr_bits(val,REG_INFO.ctleicalst2());	//CSR36[9:5]
	return *this;
}
uint
DS_rxextRegs::getctleicalst2(){
	return get_csr_bits(REG_INFO.ctleicalst2());	//CSR36[9:5]
}

DS_rxextRegs&
DS_rxextRegs::setctleicalst3(uint val){
	fill_csr_bits(val,REG_INFO.ctleicalst3());	//CSR36[4:0]
	return *this;
}
uint
DS_rxextRegs::getctleicalst3(){
	return get_csr_bits(REG_INFO.ctleicalst3());	//CSR36[4:0]
}

DS_rxextRegs&
DS_rxextRegs::setdfesumicalen(uint val){
	fill_csr_bits(val,REG_INFO.dfesumicalen());	//CSR37[14:14]
	return *this;
}
uint
DS_rxextRegs::getdfesumicalen(){
	return get_csr_bits(REG_INFO.dfesumicalen());	//CSR37[14:14]
}

DS_rxextRegs&
DS_rxextRegs::setdfesumiical(uint val){
	fill_csr_bits(val,REG_INFO.dfesumiical());	//CSR37[13:9]
	return *this;
}
uint
DS_rxextRegs::getdfesumiical(){
	return get_csr_bits(REG_INFO.dfesumiical());	//CSR37[13:9]
}

DS_rxextRegs&
DS_rxextRegs::setdfesumqical(uint val){
	fill_csr_bits(val,REG_INFO.dfesumqical());	//CSR37[8:4]
	return *this;
}
uint
DS_rxextRegs::getdfesumqical(){
	return get_csr_bits(REG_INFO.dfesumqical());	//CSR37[8:4]
}

DS_rxextRegs&
DS_rxextRegs::setdfesumiptattcctrl(uint val){
	fill_csr_bits(val,REG_INFO.dfesumiptattcctrl());	//CSR37[3:0]
	return *this;
}
uint
DS_rxextRegs::getdfesumiptattcctrl(){
	return get_csr_bits(REG_INFO.dfesumiptattcctrl());	//CSR37[3:0]
}

DS_rxextRegs&
DS_rxextRegs::setedgecycsoftrstb(uint val){
	fill_csr_bits(val,REG_INFO.edgecycsoftrstb());	//CSR38[15:15]
	return *this;
}
uint
DS_rxextRegs::getedgecycsoftrstb(){
	return get_csr_bits(REG_INFO.edgecycsoftrstb());	//CSR38[15:15]
}

DS_rxextRegs&
DS_rxextRegs::setedgecycen(uint val){
	fill_csr_bits(val,REG_INFO.edgecycen());	//CSR38[14:14]
	return *this;
}
uint
DS_rxextRegs::getedgecycen(){
	return get_csr_bits(REG_INFO.edgecycen());	//CSR38[14:14]
}

DS_rxextRegs&
DS_rxextRegs::setedgecymode(uint val){
	fill_csr_bits(val,REG_INFO.edgecymode());	//CSR38[13:13]
	return *this;
}
uint
DS_rxextRegs::getedgecymode(){
	return get_csr_bits(REG_INFO.edgecymode());	//CSR38[13:13]
}

DS_rxextRegs&
DS_rxextRegs::setedgecycpsen(uint val){
	fill_csr_bits(val,REG_INFO.edgecycpsen());	//CSR38[12:12]
	return *this;
}
uint
DS_rxextRegs::getedgecycpsen(){
	return get_csr_bits(REG_INFO.edgecycpsen());	//CSR38[12:12]
}

DS_rxextRegs&
DS_rxextRegs::setedgcycanastl(uint val){
	fill_csr_bits(val,REG_INFO.edgcycanastl());	//CSR38[11:10]
	return *this;
}
uint
DS_rxextRegs::getedgcycanastl(){
	return get_csr_bits(REG_INFO.edgcycanastl());	//CSR38[11:10]
}

DS_rxextRegs&
DS_rxextRegs::setedgcyctranstep(uint val){
	fill_csr_bits(val,REG_INFO.edgcyctranstep());	//CSR38[9:8]
	return *this;
}
uint
DS_rxextRegs::getedgcyctranstep(){
	return get_csr_bits(REG_INFO.edgcyctranstep());	//CSR38[9:8]
}

DS_rxextRegs&
DS_rxextRegs::setedgcycofftime(uint val){
	fill_csr_bits(val,REG_INFO.edgcycofftime());	//CSR38[7:4]
	return *this;
}
uint
DS_rxextRegs::getedgcycofftime(){
	return get_csr_bits(REG_INFO.edgcycofftime());	//CSR38[7:4]
}

DS_rxextRegs&
DS_rxextRegs::setedgcycontime(uint val){
	fill_csr_bits(val,REG_INFO.edgcycontime());	//CSR38[3:0]
	return *this;
}
uint
DS_rxextRegs::getedgcycontime(){
	return get_csr_bits(REG_INFO.edgcycontime());	//CSR38[3:0]
}

DS_rxextRegs&
DS_rxextRegs::settrpdeten(uint val){
	fill_csr_bits(val,REG_INFO.trpdeten());	//CSR39[15:15]
	return *this;
}
uint
DS_rxextRegs::gettrpdeten(){
	return get_csr_bits(REG_INFO.trpdeten());	//CSR39[15:15]
}

DS_rxextRegs&
DS_rxextRegs::settrpdetthr(uint val){
	fill_csr_bits(val,REG_INFO.trpdetthr());	//CSR39[14:12]
	return *this;
}
uint
DS_rxextRegs::gettrpdetthr(){
	return get_csr_bits(REG_INFO.trpdetthr());	//CSR39[14:12]
}

DS_rxextRegs&
DS_rxextRegs::settrpdetwin(uint val){
	fill_csr_bits(val,REG_INFO.trpdetwin());	//CSR39[9:8]
	return *this;
}
uint
DS_rxextRegs::gettrpdetwin(){
	return get_csr_bits(REG_INFO.trpdetwin());	//CSR39[9:8]
}

uint
DS_rxextRegs::gettrpdetstatus(){
	return get_csr_bits(REG_INFO.trpdetstatus());	//CSR39[0:0]
}

DS_rxextRegs&
DS_rxextRegs::setrxcalibtasksel1(uint val){
	fill_csr_bits(val,REG_INFO.rxcalibtasksel1());	//CSR40[15:0]
	return *this;
}
uint
DS_rxextRegs::getrxcalibtasksel1(){
	return get_csr_bits(REG_INFO.rxcalibtasksel1());	//CSR40[15:0]
}

DS_rxextRegs&
DS_rxextRegs::setrxcalibtasksel2(uint val){
	fill_csr_bits(val,REG_INFO.rxcalibtasksel2());	//CSR41[15:0]
	return *this;
}
uint
DS_rxextRegs::getrxcalibtasksel2(){
	return get_csr_bits(REG_INFO.rxcalibtasksel2());	//CSR41[15:0]
}

DS_rxextRegs&
DS_rxextRegs::setemswcorner0(uint val){
	fill_csr_bits(val,REG_INFO.emswcorner0());	//CSR42[8:0]
	return *this;
}
uint
DS_rxextRegs::getemswcorner0(){
	return get_csr_bits(REG_INFO.emswcorner0());	//CSR42[8:0]
}

DS_rxextRegs&
DS_rxextRegs::setemswcorner1(uint val){
	fill_csr_bits(val,REG_INFO.emswcorner1());	//CSR43[8:0]
	return *this;
}
uint
DS_rxextRegs::getemswcorner1(){
	return get_csr_bits(REG_INFO.emswcorner1());	//CSR43[8:0]
}

DS_rxextRegs&
DS_rxextRegs::setrxcaldir(uint val){
	fill_csr_bits(val,REG_INFO.rxcaldir());	//CSR44[15:0]
	return *this;
}
uint
DS_rxextRegs::getrxcaldir(){
	return get_csr_bits(REG_INFO.rxcaldir());	//CSR44[15:0]
}

DS_rxextRegs&
DS_rxextRegs::setdsspare2(uint val){
	fill_csr_bits(val,REG_INFO.dsspare2());	//CSR45[15:0]
	return *this;
}
uint
DS_rxextRegs::getdsspare2(){
	return get_csr_bits(REG_INFO.dsspare2());	//CSR45[15:0]
}

DS_rxextRegs&
DS_rxextRegs::setdsspare3(uint val){
	fill_csr_bits(val,REG_INFO.dsspare3());	//CSR46[15:0]
	return *this;
}
uint
DS_rxextRegs::getdsspare3(){
	return get_csr_bits(REG_INFO.dsspare3());	//CSR46[15:0]
}

DS_rxextRegs&
DS_rxextRegs::setdsspare4(uint val){
	fill_csr_bits(val,REG_INFO.dsspare4());	//CSR47[15:0]
	return *this;
}
uint
DS_rxextRegs::getdsspare4(){
	return get_csr_bits(REG_INFO.dsspare4());	//CSR47[15:0]
}

DS_rxextRegs&
DS_rxextRegs::setrxlatofstnumword(uint val){
	fill_csr_bits(val,REG_INFO.rxlatofstnumword());	//CSR48[10:0]
	return *this;
}
uint
DS_rxextRegs::getrxlatofstnumword(){
	return get_csr_bits(REG_INFO.rxlatofstnumword());	//CSR48[10:0]
}

DS_rxextRegs&
DS_rxextRegs::setrxlatofstthresh(uint val){
	fill_csr_bits(val,REG_INFO.rxlatofstthresh());	//CSR49[14:0]
	return *this;
}
uint
DS_rxextRegs::getrxlatofstthresh(){
	return get_csr_bits(REG_INFO.rxlatofstthresh());	//CSR49[14:0]
}

uint
DS_rxextRegs::getrxlatofstdetstatus(){
	return get_csr_bits(REG_INFO.rxlatofstdetstatus());	//CSR50[14:0]
}

E_HILINK_REGISTER_TYPE DS_rxextRegs::getType()
{
	return HILINK_PERLANE_REGISTER;
}
