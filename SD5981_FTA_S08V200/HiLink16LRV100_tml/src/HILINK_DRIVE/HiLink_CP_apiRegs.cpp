#include <HILINK_DRIVE/HiLink_CP_apiRegs.h>
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
		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
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
	return 1;
}

uint
CP_apiRegs::getAddressMapToHiLink(int csrIndex){
	if(csrIndex>=CP_API_CSR_NUM){
		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	//TODO: add your code for CSR Address mapping
	return (int)(0xfff0 | csrIndex << 1);
}


uint&
CP_apiRegs::get_csr(uint csrIndex){
	if(csrIndex>=CP_API_CSR_NUM){
		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	return csr[csrIndex];
}

void
CP_apiRegs::get_default_MacroLaneID(T_MacroLaneID& id){
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

E_HILINK_REGISTER_TYPE
CP_apiRegs::getType(){
	return HILINK_PERMACRO_REGISTER;
}
///////////////////////////////////////////////////////////////////////////


	/// Interrupt request to 8051. User could write these bits to notify MCU of one interrupt from external devices.
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::intreq2mcu(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{0,"intreq2mcu",15,8}
	};
	return reg;
}

	/// Clock Slice Master Interface Interface Mode
	/// 00: Synchronous AHB/APB
	/// 01: Asynchronous AHB/APB
	/// 10: Bypass mode
	/// 11: Reserved
	/// Note: No use in H16
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::csmasterifmode(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{0,"csmasterifmode",3,2}
	};
	return reg;
}

	/// MCU Power Down
	/// 0: power down 8051
	/// 1: power up 8051
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::mcupwrdb(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{0,"mcupwrdb",1,1}
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
		{0,"mcurstb",0,0}
	};
	return reg;
}

	/// SRAM two bits ECC error interrupt
	/// 0 = No SRAM two bits ECC error detected
	/// 1 = SRAM two bits ECC error detected
	/// Writable from user to clear the interrupt
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::srameccint(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{1,"srameccint",10,10}
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
		{1,"wdogoverflowint",9,9}
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
		{1,"mcupcoverflowint",8,8}
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
		{1,"sfrint",7,0}
	};
	return reg;
}

	/// Interrupt Mask. Enable/Disable the interrupt source. When one specific interrupt source is enabled, one interrupt from that source would assert output mcu_int to request external intervention.
	/// 0: Disable the interrupt
	/// 1: Enable the interrupt
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::mcuintmask(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{2,"mcuintmask",15,0}
	};
	return reg;
}

	/// MCU Program Counter value
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::mcupc(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{3,"mcupc",15,0}
	};
	return reg;
}

	/// Type: 000 = LR
	///          001-1xx = TBD
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::type(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{4,"type",15,13}
	};
	return reg;
}

	/// Rate: 000 = 16G
	///           001 = 30G
	///           011-111 = TBD
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::rate(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{4,"rate",12,10}
	};
	return reg;
}

	/// Foundry:
	///  00 = TSMC
	///  01 �C 11 = TBD
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::foundry(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{4,"foundry",9,8}
	};
	return reg;
}

	/// Technology Node
	///  000 = 28nm
	///  001 = 40nm
	///  010 = 16nm
	/// 011-111 = TBD
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::technode(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{4,"technode",7,5}
	};
	return reg;
}

	/// Control Plane Digital Revision
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::cpdigrev(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{4,"cpdigrev",4,0}
	};
	return reg;
}

	/// SRAM ECC error inject enable, active high
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::err_inject_en(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{5,"err_inject_en",15,0}
	};
	return reg;
}

	/// SRAM ECC two bit error address
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::ecc_two_bit_err_addr(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{6,"ecc_two_bit_err_addr",15,0}
	};
	return reg;
}

	/// SRAM ECC error inject mode
	/// 0 = Inject ECC error continuous
	/// 1 = Only inject one ECC error
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::err_inject_once(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{7,"err_inject_once",15,15}
	};
	return reg;
}

	/// SRAM ECC check bypass enable
	/// 0 = Enable SRAM ECC check
	/// 1 = Bypass SRAM ECC check
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::ecc_bypass(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{7,"ecc_bypass",14,14}
	};
	return reg;
}

	/// SRAM ECC one bit error couner, if the value is 0, it indicated it has not one bit ECC error, if the value is not 0, it indicated it has one bit ECC error. It can be read clearly.
const T_REG_INFO_EX&
CP_apiRegs::_REG_INFO::ecc_single_err_cnt(){
	const static T_REG_INFO_EX reg={CP_apiRegs::getInstance(),
		{7,"ecc_single_err_cnt",9,0}
	};
	return reg;
}
bool
CP_apiRegs::_REG_INFO::get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos){
	reg_infos.clear();
	switch(csr){
		case 0:
			reg_infos.push_back(intreq2mcu().reg_info);
			reg_infos.push_back(csmasterifmode().reg_info);
			reg_infos.push_back(mcupwrdb().reg_info);
			reg_infos.push_back(mcurstb().reg_info);
			break;
		case 1:
			reg_infos.push_back(srameccint().reg_info);
			reg_infos.push_back(wdogoverflowint().reg_info);
			reg_infos.push_back(mcupcoverflowint().reg_info);
			reg_infos.push_back(sfrint().reg_info);
			break;
		case 2:
			reg_infos.push_back(mcuintmask().reg_info);
			break;
		case 3:
			reg_infos.push_back(mcupc().reg_info);
			break;
		case 4:
			reg_infos.push_back(type().reg_info);
			reg_infos.push_back(rate().reg_info);
			reg_infos.push_back(foundry().reg_info);
			reg_infos.push_back(technode().reg_info);
			reg_infos.push_back(cpdigrev().reg_info);
			break;
		case 5:
			reg_infos.push_back(err_inject_en().reg_info);
			break;
		case 6:
			reg_infos.push_back(ecc_two_bit_err_addr().reg_info);
			break;
		case 7:
			reg_infos.push_back(err_inject_once().reg_info);
			reg_infos.push_back(ecc_bypass().reg_info);
			reg_infos.push_back(ecc_single_err_cnt().reg_info);
			break;
		default:
			break;
	}
	return (reg_infos.size()>0);
}


CP_apiRegs&
CP_apiRegs::setintreq2mcu(uint val){
	fill_csr_bits(val,REG_INFO.intreq2mcu());	//CSR0[15:8]
	return *this;
}
uint
CP_apiRegs::getintreq2mcu(){
	return get_csr_bits(REG_INFO.intreq2mcu());	//CSR0[15:8]
}

CP_apiRegs&
CP_apiRegs::setcsmasterifmode(uint val){
	fill_csr_bits(val,REG_INFO.csmasterifmode());	//CSR0[3:2]
	return *this;
}
uint
CP_apiRegs::getcsmasterifmode(){
	return get_csr_bits(REG_INFO.csmasterifmode());	//CSR0[3:2]
}

CP_apiRegs&
CP_apiRegs::setmcupwrdb(uint val){
	fill_csr_bits(val,REG_INFO.mcupwrdb());	//CSR0[1:1]
	return *this;
}
uint
CP_apiRegs::getmcupwrdb(){
	return get_csr_bits(REG_INFO.mcupwrdb());	//CSR0[1:1]
}

CP_apiRegs&
CP_apiRegs::setmcurstb(uint val){
	fill_csr_bits(val,REG_INFO.mcurstb());	//CSR0[0:0]
	return *this;
}
uint
CP_apiRegs::getmcurstb(){
	return get_csr_bits(REG_INFO.mcurstb());	//CSR0[0:0]
}

CP_apiRegs&
CP_apiRegs::setsrameccint(uint val){
	fill_csr_bits(val,REG_INFO.srameccint());	//CSR1[10:10]
	return *this;
}
uint
CP_apiRegs::getsrameccint(){
	return get_csr_bits(REG_INFO.srameccint());	//CSR1[10:10]
}

CP_apiRegs&
CP_apiRegs::setwdogoverflowint(uint val){
	fill_csr_bits(val,REG_INFO.wdogoverflowint());	//CSR1[9:9]
	return *this;
}
uint
CP_apiRegs::getwdogoverflowint(){
	return get_csr_bits(REG_INFO.wdogoverflowint());	//CSR1[9:9]
}

CP_apiRegs&
CP_apiRegs::setmcupcoverflowint(uint val){
	fill_csr_bits(val,REG_INFO.mcupcoverflowint());	//CSR1[8:8]
	return *this;
}
uint
CP_apiRegs::getmcupcoverflowint(){
	return get_csr_bits(REG_INFO.mcupcoverflowint());	//CSR1[8:8]
}

CP_apiRegs&
CP_apiRegs::setsfrint(uint val){
	fill_csr_bits(val,REG_INFO.sfrint());	//CSR1[7:0]
	return *this;
}
uint
CP_apiRegs::getsfrint(){
	return get_csr_bits(REG_INFO.sfrint());	//CSR1[7:0]
}

CP_apiRegs&
CP_apiRegs::setmcuintmask(uint val){
	fill_csr_bits(val,REG_INFO.mcuintmask());	//CSR2[15:0]
	return *this;
}
uint
CP_apiRegs::getmcuintmask(){
	return get_csr_bits(REG_INFO.mcuintmask());	//CSR2[15:0]
}

uint
CP_apiRegs::getmcupc(){
	return get_csr_bits(REG_INFO.mcupc());	//CSR3[15:0]
}

uint
CP_apiRegs::gettype(){
	return get_csr_bits(REG_INFO.type());	//CSR4[15:13]
}

uint
CP_apiRegs::getrate(){
	return get_csr_bits(REG_INFO.rate());	//CSR4[12:10]
}

uint
CP_apiRegs::getfoundry(){
	return get_csr_bits(REG_INFO.foundry());	//CSR4[9:8]
}

uint
CP_apiRegs::gettechnode(){
	return get_csr_bits(REG_INFO.technode());	//CSR4[7:5]
}

uint
CP_apiRegs::getcpdigrev(){
	return get_csr_bits(REG_INFO.cpdigrev());	//CSR4[4:0]
}

CP_apiRegs&
CP_apiRegs::seterr_inject_en(uint val){
	fill_csr_bits(val,REG_INFO.err_inject_en());	//CSR5[15:0]
	return *this;
}
uint
CP_apiRegs::geterr_inject_en(){
	return get_csr_bits(REG_INFO.err_inject_en());	//CSR5[15:0]
}

uint
CP_apiRegs::getecc_two_bit_err_addr(){
	return get_csr_bits(REG_INFO.ecc_two_bit_err_addr());	//CSR6[15:0]
}

CP_apiRegs&
CP_apiRegs::seterr_inject_once(uint val){
	fill_csr_bits(val,REG_INFO.err_inject_once());	//CSR7[15:15]
	return *this;
}
uint
CP_apiRegs::geterr_inject_once(){
	return get_csr_bits(REG_INFO.err_inject_once());	//CSR7[15:15]
}

CP_apiRegs&
CP_apiRegs::setecc_bypass(uint val){
	fill_csr_bits(val,REG_INFO.ecc_bypass());	//CSR7[14:14]
	return *this;
}
uint
CP_apiRegs::getecc_bypass(){
	return get_csr_bits(REG_INFO.ecc_bypass());	//CSR7[14:14]
}

uint
CP_apiRegs::getecc_single_err_cnt(){
	return get_csr_bits(REG_INFO.ecc_single_err_cnt());	//CSR7[9:0]
}

