#ifndef HILINKCPAPI_H_
#define HILINKCPAPI_H_

#include "HiLink_Regs_Base.h"
#define CP_API_CSR_NUM 8

class CP_apiRegs:public HILINK_Regs_Base{
protected:
	CP_apiRegs();
	virtual ~CP_apiRegs();

	uint& get_csr(uint csrIndex);
	virtual void get_default_MacroLaneID(T_MacroLaneID& id);

public:
	bool get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos);
	static CP_apiRegs& getInstance();
	string getName();
	uint getCSRCount();
	E_HILINK_REGISTER_TYPE getType();
	uint get_HILINK_MAX_LANE_NUM();
	uint getAddressMapToHiLink(int csrIndex);

///////////////////////////////////////////////////////////////////////////

private:
	class _REG_INFO{
		public:

	/// Interrupt request to 8051. User could write these bits to notify MCU of one interrupt from external devices.
			const T_REG_INFO_EX& intreq2mcu();	//CSR0[15:8]

	/// Clock Slice Master Interface Interface Mode
	/// 00: Synchronous AHB/APB
	/// 01: Asynchronous AHB/APB
	/// 10: Bypass mode
	/// 11: Reserved
	/// Note: No use in H16
			const T_REG_INFO_EX& csmasterifmode();	//CSR0[3:2]

	/// MCU Power Down
	/// 0: power down 8051
	/// 1: power up 8051
			const T_REG_INFO_EX& mcupwrdb();	//CSR0[1:1]

	/// MCU Reset
	/// 0 = Reset MCU
	/// 1 = Enable MCU
	/// MCU is in a reset state after power up. User could assert this bit to start the program loaded in ROM and/or RAM.
			const T_REG_INFO_EX& mcurstb();	//CSR0[0:0]

	/// SRAM two bits ECC error interrupt
	/// 0 = No SRAM two bits ECC error detected
	/// 1 = SRAM two bits ECC error detected
	/// Writable from user to clear the interrupt
			const T_REG_INFO_EX& srameccint();	//CSR1[10:10]

	/// Watchdog Overflow Interrupt
	/// 0 = No watchdog overflow
	/// 1 = Watchdog overflow
	/// Writable from user to clear the interrupt
			const T_REG_INFO_EX& wdogoverflowint();	//CSR1[9:9]

	/// MCU Program Counter Overflow Interrupt
	/// 0 = No PC overflow
	/// 1 = PC overflow
	/// Writable from user to clear the interrupt
			const T_REG_INFO_EX& mcupcoverflowint();	//CSR1[8:8]

	/// Interrupt from MCU/8051
	/// Interrupt source from SFR 0xB1. 
	/// 0 = No interrupt
	/// 1 = Interrupt
	/// Writable from user to clear the interrupt
			const T_REG_INFO_EX& sfrint();	//CSR1[7:0]

	/// Interrupt Mask. Enable/Disable the interrupt source. When one specific interrupt source is enabled, one interrupt from that source would assert output mcu_int to request external intervention.
	/// 0: Disable the interrupt
	/// 1: Enable the interrupt
			const T_REG_INFO_EX& mcuintmask();	//CSR2[15:0]

	/// MCU Program Counter value
			const T_REG_INFO_EX& mcupc();	//CSR3[15:0]

	/// Type: 000 = LR
	///          001-1xx = TBD
			const T_REG_INFO_EX& type();	//CSR4[15:13]

	/// Rate: 000 = 16G
	///           001 = 30G
	///           011-111 = TBD
			const T_REG_INFO_EX& rate();	//CSR4[12:10]

	/// Foundry:
	///  00 = TSMC
	///  01 ¨C 11 = TBD
			const T_REG_INFO_EX& foundry();	//CSR4[9:8]

	/// Technology Node
	///  000 = 28nm
	///  001 = 40nm
	///  010 = 16nm
	/// 011-111 = TBD
			const T_REG_INFO_EX& technode();	//CSR4[7:5]

	/// Control Plane Digital Revision
			const T_REG_INFO_EX& cpdigrev();	//CSR4[4:0]

	/// SRAM ECC error inject enable, active high
			const T_REG_INFO_EX& err_inject_en();	//CSR5[15:0]

	/// SRAM ECC two bit error address
			const T_REG_INFO_EX& ecc_two_bit_err_addr();	//CSR6[15:0]

	/// SRAM ECC error inject mode
	/// 0 = Inject ECC error continuous
	/// 1 = Only inject one ECC error
			const T_REG_INFO_EX& err_inject_once();	//CSR7[15:15]

	/// SRAM ECC check bypass enable
	/// 0 = Enable SRAM ECC check
	/// 1 = Bypass SRAM ECC check
			const T_REG_INFO_EX& ecc_bypass();	//CSR7[14:14]

	/// SRAM ECC one bit error couner, if the value is 0, it indicated it has not one bit ECC error, if the value is not 0, it indicated it has one bit ECC error. It can be read clearly.
			const T_REG_INFO_EX& ecc_single_err_cnt();	//CSR7[9:0]
			bool get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos);
	};
public:
	_REG_INFO REG_INFO;

	uint csr[CP_API_CSR_NUM];


	//CSR0[15:8]
	CP_apiRegs& setintreq2mcu(uint val);
	uint getintreq2mcu();

	//CSR0[3:2]
	CP_apiRegs& setcsmasterifmode(uint val);
	uint getcsmasterifmode();

	//CSR0[1:1]
	CP_apiRegs& setmcupwrdb(uint val);
	uint getmcupwrdb();

	//CSR0[0:0]
	CP_apiRegs& setmcurstb(uint val);
	uint getmcurstb();

	//CSR1[10:10]
	CP_apiRegs& setsrameccint(uint val);
	uint getsrameccint();

	//CSR1[9:9]
	CP_apiRegs& setwdogoverflowint(uint val);
	uint getwdogoverflowint();

	//CSR1[8:8]
	CP_apiRegs& setmcupcoverflowint(uint val);
	uint getmcupcoverflowint();

	//CSR1[7:0]
	CP_apiRegs& setsfrint(uint val);
	uint getsfrint();

	//CSR2[15:0]
	CP_apiRegs& setmcuintmask(uint val);
	uint getmcuintmask();

	//CSR3[15:0]
	uint getmcupc();

	//CSR4[15:13]
	uint gettype();

	//CSR4[12:10]
	uint getrate();

	//CSR4[9:8]
	uint getfoundry();

	//CSR4[7:5]
	uint gettechnode();

	//CSR4[4:0]
	uint getcpdigrev();

	//CSR5[15:0]
	CP_apiRegs& seterr_inject_en(uint val);
	uint geterr_inject_en();

	//CSR6[15:0]
	uint getecc_two_bit_err_addr();

	//CSR7[15:15]
	CP_apiRegs& seterr_inject_once(uint val);
	uint geterr_inject_once();

	//CSR7[14:14]
	CP_apiRegs& setecc_bypass(uint val);
	uint getecc_bypass();

	//CSR7[9:0]
	uint getecc_single_err_cnt();

};

#endif // HILINKCPAPI_H_
