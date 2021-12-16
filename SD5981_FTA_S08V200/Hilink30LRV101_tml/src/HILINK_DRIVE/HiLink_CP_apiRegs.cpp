#include <HILINK_DRIVE/HiLink_CP_apiRegs.h>

#include <iostream>
using namespace std;
CP_apiRegs::CP_apiRegs() {
	// TODO Auto-generated constructor stub
	for(int i=0;i<CP_API_CSR_NUM;i++){
		csr[i]=0;
	}
	sliceID=0;
	macroID=0;
	broadcast=false;
	reset_csr_verify();
}

CP_apiRegs::~CP_apiRegs() {}

bool
CP_apiRegs::get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos){
	if(csrIndex>=CP_API_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	return REG_INFO.get_reg_infos(csrIndex,reg_infos);
}

CP_apiRegs&
CP_apiRegs::getInstance(){
	static CP_apiRegs theInstance;

	return theInstance;
}

uint
CP_apiRegs::get_HILINK_MAX_LANE_NUM(){
	//TODO: add your code for CSR Address mapping
	return 1;
}

uint
CP_apiRegs::getAddressMapToHiLink(int csrIndex){
	if(csrIndex>=CP_API_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	//TODO: add your code for CSR Address mapping
	uint retAddress =0;
	retAddress = 0x3FFE0 + csrIndex*0x2;
	return retAddress;
}


uint&
CP_apiRegs::get_csr(uint csrIndex){
	if(csrIndex>=CP_API_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	return csr[csrIndex];
}

void
CP_apiRegs::get_default_MacroLaneID(T_MacroLaneID& id){
	//TODO: add your code for CSR Address mapping
	id.MacroID=macroID;
	id.LaneID=sliceID;
}

uint
CP_apiRegs::getCSRCount(){
	return CP_API_CSR_NUM;
}

string
CP_apiRegs::getName(){
	return "CP_API";
}

///////////////////////////////////////////////////////////////////////////


	/// InstDatRAM ECC error inject register
	/// [15:0]: bit error vector
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::eccerrinj(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{0,"eccerrinj",15,0}
	};
	return reg;
}

	/// InstDatRAM ECC single-bit error count register
	/// [15:0]: error count
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::eccerrcnt(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{1,"eccerrcnt",15,0}
	};
	return reg;
}

	/// Interrupt request to 8051. User could write these bits to notify MCU of one interrupt from external devices. 
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::intreq2mcu(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{8,"intreq2mcu",15,8}
	};
	return reg;
}

	/// Clock Slice Master Interface Interface Mode
	/// 00: Synchronous AHB/APB
	/// 01: Asynchronous AHB/APB
	/// 10: Bypass mode
	/// 11: Reserved
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::csmasterifmode(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{8,"csmasterifmode",3,2}
	};
	return reg;
}

	/// MCU Power Down
	/// 0: power down 8051
	/// 1: power up 8051
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::mcupwrdb(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{8,"mcupwrdb",1,1}
	};
	return reg;
}

	/// MCU Reset
	/// 0 = Reset MCU
	/// 1 = Enable MCU
	/// MCU is in a reset state after power up. User could assert this bit to start the program loaded in ROM and/or RAM.
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::mcurstb(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{8,"mcurstb",0,0}
	};
	return reg;
}

	/// InstDatROM parity error
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::romparerr(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{9,"romparerr",11,11}
	};
	return reg;
}

	/// InstDatRAM ECC 2-bit (uncorrectable) error
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::rameccerr(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{9,"rameccerr",10,10}
	};
	return reg;
}

	/// Watchdog Overflow Interrupt
	/// 0 = No watchdog overflow
	/// 1 = Watchdog overflow
	/// Writable from user to clear the interrupt
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::wdogoverflowint(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{9,"wdogoverflowint",9,9}
	};
	return reg;
}

	/// MCU Program Counter Overflow Interrupt
	/// 0 = No PC overflow
	/// 1 = PC overflow
	/// Writable from user to clear the interrupt
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::mcupcoverflowint(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{9,"mcupcoverflowint",8,8}
	};
	return reg;
}

	/// Interrupt from MCU/8051
	/// Interrupt source from SFR 0xB1. 
	/// 0 = No interrupt
	/// 1 = Interrupt
	/// Writable from user to clear the interrupt
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::sfrint(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{9,"sfrint",7,0}
	};
	return reg;
}

	/// Interrupt Mask. Enable/Disable the interrupt source. When one specific interrupt source is enabled, one interrupt from that source would assert output mcu_int to request external intervention.
	/// 0: Disable the interrupt
	/// 1: Enable the interrupt
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::mcuintmask(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{10,"mcuintmask",15,0}
	};
	return reg;
}

	/// Type: 000 = BP
	///      001 = CM
	///      010 = CC
	///      011-1xx = TBD
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::mcupc(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{11,"mcupc",15,0}
	};
	return reg;
}

	/// Type: 000 = BP
	///      001 = CM
	///      010 = CC
	///      011-1xx = TBD
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::type(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{12,"type",15,13}
	};
	return reg;
}

	/// Rate: 001 = 30G
	///    others = TBD
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::rate(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{12,"rate",12,10}
	};
	return reg;
}

	/// Foundry:
	///  00 = TSMC
	///  01 �C 11 = TBD
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::foundry(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{12,"foundry",9,8}
	};
	return reg;
}

	/// Technology Node
	///  010 = 16nm
	///  others = TBD
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::technode(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{12,"technode",7,5}
	};
	return reg;
}

	/// Control Plane Digital Revision
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::cpdigrev(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{12,"cpdigrev",4,0}
	};
	return reg;
}

	/// InstDatRAM ECC error address register
	///  [15:0]: address of uncorrectable error
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::rameccerraddr(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{13,"rameccerraddr",15,0}
	};
	return reg;
}

	/// InstDatROM Parity error address register
	///  [15:0]: address of parity error
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::romparerraddr(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{14,"romparerraddr",15,0}
	};
	return reg;
}

	/// unused
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::spare1(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{15,"spare1",15,6}
	};
	return reg;
}

	/// InstDatROM parity error insert (auto reset after InstDatROM parity error interrupt)
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::romparerrinsert(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{15,"romparerrinsert",5,5}
	};
	return reg;
}

	/// InstDatRAM ECC bypass
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::rameccbypass(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{15,"rameccbypass",4,4}
	};
	return reg;
}

	/// disable MCU instruction execution upon InstDatROM parity error
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::instromparerrmcuinhibit(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{15,"instromparerrmcuinhibit",3,3}
	};
	return reg;
}

	/// disable MCU instruction execution upon InstDatRAM ECC 2-bit (uncorrectable) error
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::instrameccerrmcuinhibit(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{15,"instrameccerrmcuinhibit",2,2}
	};
	return reg;
}

	/// disable MCU memory access upon InstDatROM parity error
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::datromparerrmcuinhibit(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{15,"datromparerrmcuinhibit",1,1}
	};
	return reg;
}

	/// disable MCU memory access upon InstDatRAM ECC 2-bit (uncorrectable) error
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::datrameccerrmcuinhibit(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{15,"datrameccerrmcuinhibit",0,0}
	};
	return reg;
}
bool
CP_apiRegs::_REG_INFO::get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos){
	reg_infos.clear();
	switch(csr){
		case 0:
			reg_infos.push_back(eccerrinj().reg_info);
			break;
		case 1:
			reg_infos.push_back(eccerrcnt().reg_info);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			reg_infos.push_back(intreq2mcu().reg_info);
			reg_infos.push_back(csmasterifmode().reg_info);
			reg_infos.push_back(mcupwrdb().reg_info);
			reg_infos.push_back(mcurstb().reg_info);
			break;
		case 9:
			reg_infos.push_back(romparerr().reg_info);
			reg_infos.push_back(rameccerr().reg_info);
			reg_infos.push_back(wdogoverflowint().reg_info);
			reg_infos.push_back(mcupcoverflowint().reg_info);
			reg_infos.push_back(sfrint().reg_info);
			break;
		case 10:
			reg_infos.push_back(mcuintmask().reg_info);
			break;
		case 11:
			reg_infos.push_back(mcupc().reg_info);
			break;
		case 12:
			reg_infos.push_back(type().reg_info);
			reg_infos.push_back(rate().reg_info);
			reg_infos.push_back(foundry().reg_info);
			reg_infos.push_back(technode().reg_info);
			reg_infos.push_back(cpdigrev().reg_info);
			break;
		case 13:
			reg_infos.push_back(rameccerraddr().reg_info);
			break;
		case 14:
			reg_infos.push_back(romparerraddr().reg_info);
			break;
		case 15:
			reg_infos.push_back(spare1().reg_info);
			reg_infos.push_back(romparerrinsert().reg_info);
			reg_infos.push_back(rameccbypass().reg_info);
			reg_infos.push_back(instromparerrmcuinhibit().reg_info);
			reg_infos.push_back(instrameccerrmcuinhibit().reg_info);
			reg_infos.push_back(datromparerrmcuinhibit().reg_info);
			reg_infos.push_back(datrameccerrmcuinhibit().reg_info);
			break;
		default:
			break;
	}
	return (reg_infos.size()>0);
}


CP_apiRegs&
CP_apiRegs::seteccerrinj(uint val){
	fill_csr_bits(val,REG_INFO.eccerrinj());	//CSR0[15:0]
	return *this;
}
uint
CP_apiRegs::geteccerrinj(){
	return get_csr_bits(REG_INFO.eccerrinj());	//CSR0[15:0]
}

CP_apiRegs&
CP_apiRegs::seteccerrcnt(uint val){
	fill_csr_bits(val,REG_INFO.eccerrcnt());	//CSR1[15:0]
	return *this;
}
uint
CP_apiRegs::geteccerrcnt(){
	return get_csr_bits(REG_INFO.eccerrcnt());	//CSR1[15:0]
}

CP_apiRegs&
CP_apiRegs::setintreq2mcu(uint val){
	fill_csr_bits(val,REG_INFO.intreq2mcu());	//CSR8[15:8]
	return *this;
}
uint
CP_apiRegs::getintreq2mcu(){
	return get_csr_bits(REG_INFO.intreq2mcu());	//CSR8[15:8]
}

CP_apiRegs&
CP_apiRegs::setcsmasterifmode(uint val){
	fill_csr_bits(val,REG_INFO.csmasterifmode());	//CSR8[3:2]
	return *this;
}
uint
CP_apiRegs::getcsmasterifmode(){
	return get_csr_bits(REG_INFO.csmasterifmode());	//CSR8[3:2]
}

CP_apiRegs&
CP_apiRegs::setmcupwrdb(uint val){
	fill_csr_bits(val,REG_INFO.mcupwrdb());	//CSR8[1:1]
	return *this;
}
uint
CP_apiRegs::getmcupwrdb(){
	return get_csr_bits(REG_INFO.mcupwrdb());	//CSR8[1:1]
}

CP_apiRegs&
CP_apiRegs::setmcurstb(uint val){
	fill_csr_bits(val,REG_INFO.mcurstb());	//CSR8[0:0]
	return *this;
}
uint
CP_apiRegs::getmcurstb(){
	return get_csr_bits(REG_INFO.mcurstb());	//CSR8[0:0]
}

CP_apiRegs&
CP_apiRegs::setromparerr(uint val){
	fill_csr_bits(val,REG_INFO.romparerr());	//CSR9[11:11]
	return *this;
}
uint
CP_apiRegs::getromparerr(){
	return get_csr_bits(REG_INFO.romparerr());	//CSR9[11:11]
}

CP_apiRegs&
CP_apiRegs::setrameccerr(uint val){
	fill_csr_bits(val,REG_INFO.rameccerr());	//CSR9[10:10]
	return *this;
}
uint
CP_apiRegs::getrameccerr(){
	return get_csr_bits(REG_INFO.rameccerr());	//CSR9[10:10]
}

CP_apiRegs&
CP_apiRegs::setwdogoverflowint(uint val){
	fill_csr_bits(val,REG_INFO.wdogoverflowint());	//CSR9[9:9]
	return *this;
}
uint
CP_apiRegs::getwdogoverflowint(){
	return get_csr_bits(REG_INFO.wdogoverflowint());	//CSR9[9:9]
}

CP_apiRegs&
CP_apiRegs::setmcupcoverflowint(uint val){
	fill_csr_bits(val,REG_INFO.mcupcoverflowint());	//CSR9[8:8]
	return *this;
}
uint
CP_apiRegs::getmcupcoverflowint(){
	return get_csr_bits(REG_INFO.mcupcoverflowint());	//CSR9[8:8]
}

CP_apiRegs&
CP_apiRegs::setsfrint(uint val){
	fill_csr_bits(val,REG_INFO.sfrint());	//CSR9[7:0]
	return *this;
}
uint
CP_apiRegs::getsfrint(){
	return get_csr_bits(REG_INFO.sfrint());	//CSR9[7:0]
}

CP_apiRegs&
CP_apiRegs::setmcuintmask(uint val){
	fill_csr_bits(val,REG_INFO.mcuintmask());	//CSR10[15:0]
	return *this;
}
uint
CP_apiRegs::getmcuintmask(){
	return get_csr_bits(REG_INFO.mcuintmask());	//CSR10[15:0]
}

uint
CP_apiRegs::getmcupc(){
	return get_csr_bits(REG_INFO.mcupc());	//CSR11[15:0]
}

uint
CP_apiRegs::gettype(){
	return get_csr_bits(REG_INFO.type());	//CSR12[15:13]
}

uint
CP_apiRegs::getrate(){
	return get_csr_bits(REG_INFO.rate());	//CSR12[12:10]
}

uint
CP_apiRegs::getfoundry(){
	return get_csr_bits(REG_INFO.foundry());	//CSR12[9:8]
}

uint
CP_apiRegs::gettechnode(){
	return get_csr_bits(REG_INFO.technode());	//CSR12[7:5]
}

uint
CP_apiRegs::getcpdigrev(){
	return get_csr_bits(REG_INFO.cpdigrev());	//CSR12[4:0]
}

uint
CP_apiRegs::getrameccerraddr(){
	return get_csr_bits(REG_INFO.rameccerraddr());	//CSR13[15:0]
}

uint
CP_apiRegs::getromparerraddr(){
	return get_csr_bits(REG_INFO.romparerraddr());	//CSR14[15:0]
}

CP_apiRegs&
CP_apiRegs::setspare1(uint val){
	fill_csr_bits(val,REG_INFO.spare1());	//CSR15[15:6]
	return *this;
}
uint
CP_apiRegs::getspare1(){
	return get_csr_bits(REG_INFO.spare1());	//CSR15[15:6]
}

CP_apiRegs&
CP_apiRegs::setromparerrinsert(uint val){
	fill_csr_bits(val,REG_INFO.romparerrinsert());	//CSR15[5:5]
	return *this;
}
uint
CP_apiRegs::getromparerrinsert(){
	return get_csr_bits(REG_INFO.romparerrinsert());	//CSR15[5:5]
}

CP_apiRegs&
CP_apiRegs::setrameccbypass(uint val){
	fill_csr_bits(val,REG_INFO.rameccbypass());	//CSR15[4:4]
	return *this;
}
uint
CP_apiRegs::getrameccbypass(){
	return get_csr_bits(REG_INFO.rameccbypass());	//CSR15[4:4]
}

CP_apiRegs&
CP_apiRegs::setinstromparerrmcuinhibit(uint val){
	fill_csr_bits(val,REG_INFO.instromparerrmcuinhibit());	//CSR15[3:3]
	return *this;
}
uint
CP_apiRegs::getinstromparerrmcuinhibit(){
	return get_csr_bits(REG_INFO.instromparerrmcuinhibit());	//CSR15[3:3]
}

CP_apiRegs&
CP_apiRegs::setinstrameccerrmcuinhibit(uint val){
	fill_csr_bits(val,REG_INFO.instrameccerrmcuinhibit());	//CSR15[2:2]
	return *this;
}
uint
CP_apiRegs::getinstrameccerrmcuinhibit(){
	return get_csr_bits(REG_INFO.instrameccerrmcuinhibit());	//CSR15[2:2]
}

CP_apiRegs&
CP_apiRegs::setdatromparerrmcuinhibit(uint val){
	fill_csr_bits(val,REG_INFO.datromparerrmcuinhibit());	//CSR15[1:1]
	return *this;
}
uint
CP_apiRegs::getdatromparerrmcuinhibit(){
	return get_csr_bits(REG_INFO.datromparerrmcuinhibit());	//CSR15[1:1]
}

CP_apiRegs&
CP_apiRegs::setdatrameccerrmcuinhibit(uint val){
	fill_csr_bits(val,REG_INFO.datrameccerrmcuinhibit());	//CSR15[0:0]
	return *this;
}
uint
CP_apiRegs::getdatrameccerrmcuinhibit(){
	return get_csr_bits(REG_INFO.datrameccerrmcuinhibit());	//CSR15[0:0]
}
E_HILINK_REGISTER_TYPE CP_apiRegs::getType()
{
	return HILINK_PERMACRO_REGISTER;
}
