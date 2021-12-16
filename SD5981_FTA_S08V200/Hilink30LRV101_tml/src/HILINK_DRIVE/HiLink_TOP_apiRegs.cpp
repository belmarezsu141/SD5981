#include <HILINK_DRIVE/HiLink_TOP_apiRegs.h>

#include <iostream>
using namespace std;
TOP_apiRegs::TOP_apiRegs() {
	// TODO Auto-generated constructor stub
	for(int i=0;i<TOP_API_CSR_NUM;i++){
		csr[i]=0;
	}
	sliceID=0;
	macroID=0;
	broadcast=false;
	reset_csr_verify();
}

TOP_apiRegs::~TOP_apiRegs() {}

bool
TOP_apiRegs::get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos){
	if(csrIndex>=TOP_API_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	return REG_INFO.get_reg_infos(csrIndex,reg_infos);
}

TOP_apiRegs&
TOP_apiRegs::getInstance(){
	static TOP_apiRegs theInstance;
	return theInstance;
}

uint
TOP_apiRegs::get_HILINK_MAX_LANE_NUM(){
	//TODO: add your code for CSR Address mapping
	return 1;
}

uint
TOP_apiRegs::getAddressMapToHiLink(int csrIndex){
	if(csrIndex>=TOP_API_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	//TODO: add your code for CSR Address mapping
	uint retAddress = 0;
	retAddress = 0x1FFFE;
	return retAddress;
}


uint&
TOP_apiRegs::get_csr(uint csrIndex){
	if(csrIndex>=TOP_API_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	return csr[csrIndex];
}

void
TOP_apiRegs::get_default_MacroLaneID(T_MacroLaneID& id){
	//TODO: add your code for CSR Address mapping
	id.MacroID=macroID;
	id.LaneID=sliceID;
}

uint
TOP_apiRegs::getCSRCount(){
	return TOP_API_CSR_NUM;
}

string
TOP_apiRegs::getName(){
	return "TOP_API";
}

///////////////////////////////////////////////////////////////////////////


	/// Top FSM done flag.
	/// 0 = TOP FSM is running
	/// 1 = TOP FSM done
const T_REG_INFO_EX&
TOP_apiRegs::_REG_INFO::top_fsm_done_api(){
	const static T_REG_INFO_EX reg={TOP_apiRegs::getInstance(),
		{0,"top_fsm_done_api",15,15}
	};
	return reg;
}

	/// Number of Clockslices (0..2).  Written by firmware upon detection.
const T_REG_INFO_EX&
TOP_apiRegs::_REG_INFO::cs_slice_count_api(){
	const static T_REG_INFO_EX reg={TOP_apiRegs::getInstance(),
		{0,"cs_slice_count_api",14,13}
	};
	return reg;
}

	/// Number of Dataslices (0..16).  Written by firmware upon detection.
const T_REG_INFO_EX&
TOP_apiRegs::_REG_INFO::ds_slice_count_api(){
	const static T_REG_INFO_EX reg={TOP_apiRegs::getInstance(),
		{0,"ds_slice_count_api",12,8}
	};
	return reg;
}

	/// spare API for future extension
const T_REG_INFO_EX&
TOP_apiRegs::_REG_INFO::top_spare7to7(){
	const static T_REG_INFO_EX reg={TOP_apiRegs::getInstance(),
		{0,"top_spare7to7",7,7}
	};
	return reg;
}

	/// DEBUG - Halt after single step 
const T_REG_INFO_EX&
TOP_apiRegs::_REG_INFO::top_haltsinglestep_api(){
	const static T_REG_INFO_EX reg={TOP_apiRegs::getInstance(),
		{0,"top_haltsinglestep_api",6,6}
	};
	return reg;
}

	/// DEBUG - Halt after state change 
const T_REG_INFO_EX&
TOP_apiRegs::_REG_INFO::top_haltstatechange_api(){
	const static T_REG_INFO_EX reg={TOP_apiRegs::getInstance(),
		{0,"top_haltstatechange_api",5,5}
	};
	return reg;
}

	/// DEBUG - Halt all execution
const T_REG_INFO_EX&
TOP_apiRegs::_REG_INFO::top_haltimmediately_api(){
	const static T_REG_INFO_EX reg={TOP_apiRegs::getInstance(),
		{0,"top_haltimmediately_api",4,4}
	};
	return reg;
}

	/// Top FSM State (0..15)
	/// 0 = TOP_INIT
	/// 1 = CLOCKSLICE Handling
	/// 2 = DATASLICE Handling
	/// 3 = CS DPM
	/// 4 = DONE
const T_REG_INFO_EX&
TOP_apiRegs::_REG_INFO::top_fsm_api(){
	const static T_REG_INFO_EX reg={TOP_apiRegs::getInstance(),
		{0,"top_fsm_api",3,0}
	};
	return reg;
}
bool
TOP_apiRegs::_REG_INFO::get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos){
	reg_infos.clear();
	switch(csr){
		case 0:
			reg_infos.push_back(top_fsm_done_api().reg_info);
			reg_infos.push_back(cs_slice_count_api().reg_info);
			reg_infos.push_back(ds_slice_count_api().reg_info);
			reg_infos.push_back(top_spare7to7().reg_info);
			reg_infos.push_back(top_haltsinglestep_api().reg_info);
			reg_infos.push_back(top_haltstatechange_api().reg_info);
			reg_infos.push_back(top_haltimmediately_api().reg_info);
			reg_infos.push_back(top_fsm_api().reg_info);
			break;
		default:
			break;
	}
	return (reg_infos.size()>0);
}


TOP_apiRegs&
TOP_apiRegs::settop_fsm_done_api(uint val){
	fill_csr_bits(val,REG_INFO.top_fsm_done_api());	//CSR0[15:15]
	return *this;
}
uint
TOP_apiRegs::gettop_fsm_done_api(){
	return get_csr_bits(REG_INFO.top_fsm_done_api());	//CSR0[15:15]
}

TOP_apiRegs&
TOP_apiRegs::setcs_slice_count_api(uint val){
	fill_csr_bits(val,REG_INFO.cs_slice_count_api());	//CSR0[14:13]
	return *this;
}
uint
TOP_apiRegs::getcs_slice_count_api(){
	return get_csr_bits(REG_INFO.cs_slice_count_api());	//CSR0[14:13]
}

TOP_apiRegs&
TOP_apiRegs::setds_slice_count_api(uint val){
	fill_csr_bits(val,REG_INFO.ds_slice_count_api());	//CSR0[12:8]
	return *this;
}
uint
TOP_apiRegs::getds_slice_count_api(){
	return get_csr_bits(REG_INFO.ds_slice_count_api());	//CSR0[12:8]
}

TOP_apiRegs&
TOP_apiRegs::settop_spare7to7(uint val){
	fill_csr_bits(val,REG_INFO.top_spare7to7());	//CSR0[7:7]
	return *this;
}
uint
TOP_apiRegs::gettop_spare7to7(){
	return get_csr_bits(REG_INFO.top_spare7to7());	//CSR0[7:7]
}

TOP_apiRegs&
TOP_apiRegs::settop_haltsinglestep_api(uint val){
	fill_csr_bits(val,REG_INFO.top_haltsinglestep_api());	//CSR0[6:6]
	return *this;
}
uint
TOP_apiRegs::gettop_haltsinglestep_api(){
	return get_csr_bits(REG_INFO.top_haltsinglestep_api());	//CSR0[6:6]
}

TOP_apiRegs&
TOP_apiRegs::settop_haltstatechange_api(uint val){
	fill_csr_bits(val,REG_INFO.top_haltstatechange_api());	//CSR0[5:5]
	return *this;
}
uint
TOP_apiRegs::gettop_haltstatechange_api(){
	return get_csr_bits(REG_INFO.top_haltstatechange_api());	//CSR0[5:5]
}

TOP_apiRegs&
TOP_apiRegs::settop_haltimmediately_api(uint val){
	fill_csr_bits(val,REG_INFO.top_haltimmediately_api());	//CSR0[4:4]
	return *this;
}
uint
TOP_apiRegs::gettop_haltimmediately_api(){
	return get_csr_bits(REG_INFO.top_haltimmediately_api());	//CSR0[4:4]
}

TOP_apiRegs&
TOP_apiRegs::settop_fsm_api(uint val){
	fill_csr_bits(val,REG_INFO.top_fsm_api());	//CSR0[3:0]
	return *this;
}
uint
TOP_apiRegs::gettop_fsm_api(){
	return get_csr_bits(REG_INFO.top_fsm_api());	//CSR0[3:0]
}

E_HILINK_REGISTER_TYPE TOP_apiRegs::getType()
{
	return HILINK_PERMACRO_REGISTER;
}
