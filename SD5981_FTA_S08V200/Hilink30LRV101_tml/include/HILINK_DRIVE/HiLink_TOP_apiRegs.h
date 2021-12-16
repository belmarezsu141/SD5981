#ifndef HILINKTOPAPIREGS_H_
#define HILINKTOPAPIREGS_H_

#include <HILINK_DRIVE/HiLink_Regs_Base.h>
#define TOP_API_CSR_NUM 1

class TOP_apiRegs:public HILINK_Regs_Base{
protected:
	TOP_apiRegs();
	virtual ~TOP_apiRegs();

	uint& get_csr(uint csrIndex);
	virtual void get_default_MacroLaneID(T_MacroLaneID& id);

public:
	bool get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos);
	static TOP_apiRegs& getInstance();
	string getName();
	uint getCSRCount();
	E_HILINK_REGISTER_TYPE getType();
	uint get_HILINK_MAX_LANE_NUM();
	uint getAddressMapToHiLink(int csrIndex);

///////////////////////////////////////////////////////////////////////////

private:
	class _REG_INFO{
		public:

	/// Top FSM done flag.
	/// 0 = TOP FSM is running
	/// 1 = TOP FSM done
			const T_REG_INFO_EX& top_fsm_done_api();	//CSR0[15:15]

	/// Number of Clockslices (0..2).  Written by firmware upon detection.
			const T_REG_INFO_EX& cs_slice_count_api();	//CSR0[14:13]

	/// Number of Dataslices (0..16).  Written by firmware upon detection.
			const T_REG_INFO_EX& ds_slice_count_api();	//CSR0[12:8]

	/// spare API for future extension
			const T_REG_INFO_EX& top_spare7to7();	//CSR0[7:7]

	/// DEBUG - Halt after single step 
			const T_REG_INFO_EX& top_haltsinglestep_api();	//CSR0[6:6]

	/// DEBUG - Halt after state change 
			const T_REG_INFO_EX& top_haltstatechange_api();	//CSR0[5:5]

	/// DEBUG - Halt all execution
			const T_REG_INFO_EX& top_haltimmediately_api();	//CSR0[4:4]

	/// Top FSM State (0..15)
	/// 0 = TOP_INIT
	/// 1 = CLOCKSLICE Handling
	/// 2 = DATASLICE Handling
	/// 3 = CS DPM
	/// 4 = DONE
			const T_REG_INFO_EX& top_fsm_api();	//CSR0[3:0]
			bool get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos);
	};
public:
	_REG_INFO REG_INFO;

	uint csr[TOP_API_CSR_NUM];


	//CSR0[15:15]
	TOP_apiRegs& settop_fsm_done_api(uint val);
	uint gettop_fsm_done_api();

	//CSR0[14:13]
	TOP_apiRegs& setcs_slice_count_api(uint val);
	uint getcs_slice_count_api();

	//CSR0[12:8]
	TOP_apiRegs& setds_slice_count_api(uint val);
	uint getds_slice_count_api();

	//CSR0[7:7]
	TOP_apiRegs& settop_spare7to7(uint val);
	uint gettop_spare7to7();

	//CSR0[6:6]
	TOP_apiRegs& settop_haltsinglestep_api(uint val);
	uint gettop_haltsinglestep_api();

	//CSR0[5:5]
	TOP_apiRegs& settop_haltstatechange_api(uint val);
	uint gettop_haltstatechange_api();

	//CSR0[4:4]
	TOP_apiRegs& settop_haltimmediately_api(uint val);
	uint gettop_haltimmediately_api();

	//CSR0[3:0]
	TOP_apiRegs& settop_fsm_api(uint val);
	uint gettop_fsm_api();

};

#endif // HILINKTOPAPIREGS_H_
