#ifndef HILINKCPAPI_H_
#define HILINKCPAPI_H_

#include <HILINK_DRIVE/HiLink_Regs_Base.h>
#define CP_API_CSR_NUM 16

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

	/// InstDatRAM ECC error inject register
	/// [15:0]: bit error vector
			const T_REG_INFO_EX& eccerrinj();	//CSR0[15:0]

	/// InstDatRAM ECC single-bit error count register
	/// [15:0]: error count
			const T_REG_INFO_EX& eccerrcnt();	//CSR1[15:0]

	/// Interrupt request to 8051. User could write these bits to notify MCU of one interrupt from external devices. 
			const T_REG_INFO_EX& intreq2mcu();	//CSR8[15:8]

	/// Clock Slice Master Interface Interface Mode
	/// 00: Synchronous AHB/APB
	/// 01: Asynchronous AHB/APB
	/// 10: Bypass mode
	/// 11: Reserved
			const T_REG_INFO_EX& csmasterifmode();	//CSR8[3:2]

	/// MCU Power Down
	/// 0: power down 8051
	/// 1: power up 8051
			const T_REG_INFO_EX& mcupwrdb();	//CSR8[1:1]

	/// MCU Reset
	/// 0 = Reset MCU
	/// 1 = Enable MCU
	/// MCU is in a reset state after power up. User could assert this bit to start the program loaded in ROM and/or RAM.
			const T_REG_INFO_EX& mcurstb();	//CSR8[0:0]

	/// InstDatROM parity error
			const T_REG_INFO_EX& romparerr();	//CSR9[11:11]

	/// InstDatRAM ECC 2-bit (uncorrectable) error
			const T_REG_INFO_EX& rameccerr();	//CSR9[10:10]

	/// Watchdog Overflow Interrupt
	/// 0 = No watchdog overflow
	/// 1 = Watchdog overflow
	/// Writable from user to clear the interrupt
			const T_REG_INFO_EX& wdogoverflowint();	//CSR9[9:9]

	/// MCU Program Counter Overflow Interrupt
	/// 0 = No PC overflow
	/// 1 = PC overflow
	/// Writable from user to clear the interrupt
			const T_REG_INFO_EX& mcupcoverflowint();	//CSR9[8:8]

	/// Interrupt from MCU/8051
	/// Interrupt source from SFR 0xB1. 
	/// 0 = No interrupt
	/// 1 = Interrupt
	/// Writable from user to clear the interrupt
			const T_REG_INFO_EX& sfrint();	//CSR9[7:0]

	/// Interrupt Mask. Enable/Disable the interrupt source. When one specific interrupt source is enabled, one interrupt from that source would assert output mcu_int to request external intervention.
	/// 0: Disable the interrupt
	/// 1: Enable the interrupt
			const T_REG_INFO_EX& mcuintmask();	//CSR10[15:0]

	/// Type: 000 = BP
	///      001 = CM
	///      010 = CC
	///      011-1xx = TBD
			const T_REG_INFO_EX& mcupc();	//CSR11[15:0]

	/// Type: 000 = BP
	///      001 = CM
	///      010 = CC
	///      011-1xx = TBD
			const T_REG_INFO_EX& type();	//CSR12[15:13]

	/// Rate: 001 = 30G
	///    others = TBD
			const T_REG_INFO_EX& rate();	//CSR12[12:10]

	/// Foundry:
	///  00 = TSMC
	///  01 �C 11 = TBD
			const T_REG_INFO_EX& foundry();	//CSR12[9:8]

	/// Technology Node
	///  010 = 16nm
	///  others = TBD
			const T_REG_INFO_EX& technode();	//CSR12[7:5]

	/// Control Plane Digital Revision
			const T_REG_INFO_EX& cpdigrev();	//CSR12[4:0]

	/// InstDatRAM ECC error address register
	///  [15:0]: address of uncorrectable error
			const T_REG_INFO_EX& rameccerraddr();	//CSR13[15:0]

	/// InstDatROM Parity error address register
	///  [15:0]: address of parity error
			const T_REG_INFO_EX& romparerraddr();	//CSR14[15:0]

	/// unused
			const T_REG_INFO_EX& spare1();	//CSR15[15:6]

	/// InstDatROM parity error insert (auto reset after InstDatROM parity error interrupt)
			const T_REG_INFO_EX& romparerrinsert();	//CSR15[5:5]

	/// InstDatRAM ECC bypass
			const T_REG_INFO_EX& rameccbypass();	//CSR15[4:4]

	/// disable MCU instruction execution upon InstDatROM parity error
			const T_REG_INFO_EX& instromparerrmcuinhibit();	//CSR15[3:3]

	/// disable MCU instruction execution upon InstDatRAM ECC 2-bit (uncorrectable) error
			const T_REG_INFO_EX& instrameccerrmcuinhibit();	//CSR15[2:2]

	/// disable MCU memory access upon InstDatROM parity error
			const T_REG_INFO_EX& datromparerrmcuinhibit();	//CSR15[1:1]

	/// disable MCU memory access upon InstDatRAM ECC 2-bit (uncorrectable) error
			const T_REG_INFO_EX& datrameccerrmcuinhibit();	//CSR15[0:0]
			bool get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos);
	};
public:
	_REG_INFO REG_INFO;

	uint csr[CP_API_CSR_NUM];


	//CSR0[15:0]
	CP_apiRegs& seteccerrinj(uint val);
	uint geteccerrinj();

	//CSR1[15:0]
	CP_apiRegs& seteccerrcnt(uint val);
	uint geteccerrcnt();

	//CSR8[15:8]
	CP_apiRegs& setintreq2mcu(uint val);
	uint getintreq2mcu();

	//CSR8[3:2]
	CP_apiRegs& setcsmasterifmode(uint val);
	uint getcsmasterifmode();

	//CSR8[1:1]
	CP_apiRegs& setmcupwrdb(uint val);
	uint getmcupwrdb();

	//CSR8[0:0]
	CP_apiRegs& setmcurstb(uint val);
	uint getmcurstb();

	//CSR9[11:11]
	CP_apiRegs& setromparerr(uint val);
	uint getromparerr();

	//CSR9[10:10]
	CP_apiRegs& setrameccerr(uint val);
	uint getrameccerr();

	//CSR9[9:9]
	CP_apiRegs& setwdogoverflowint(uint val);
	uint getwdogoverflowint();

	//CSR9[8:8]
	CP_apiRegs& setmcupcoverflowint(uint val);
	uint getmcupcoverflowint();

	//CSR9[7:0]
	CP_apiRegs& setsfrint(uint val);
	uint getsfrint();

	//CSR10[15:0]
	CP_apiRegs& setmcuintmask(uint val);
	uint getmcuintmask();

	//CSR11[15:0]
	uint getmcupc();

	//CSR12[15:13]
	uint gettype();

	//CSR12[12:10]
	uint getrate();

	//CSR12[9:8]
	uint getfoundry();

	//CSR12[7:5]
	uint gettechnode();

	//CSR12[4:0]
	uint getcpdigrev();

	//CSR13[15:0]
	uint getrameccerraddr();

	//CSR14[15:0]
	uint getromparerraddr();

	//CSR15[15:6]
	CP_apiRegs& setspare1(uint val);
	uint getspare1();

	//CSR15[5:5]
	CP_apiRegs& setromparerrinsert(uint val);
	uint getromparerrinsert();

	//CSR15[4:4]
	CP_apiRegs& setrameccbypass(uint val);
	uint getrameccbypass();

	//CSR15[3:3]
	CP_apiRegs& setinstromparerrmcuinhibit(uint val);
	uint getinstromparerrmcuinhibit();

	//CSR15[2:2]
	CP_apiRegs& setinstrameccerrmcuinhibit(uint val);
	uint getinstrameccerrmcuinhibit();

	//CSR15[1:1]
	CP_apiRegs& setdatromparerrmcuinhibit(uint val);
	uint getdatromparerrmcuinhibit();

	//CSR15[0:0]
	CP_apiRegs& setdatrameccerrmcuinhibit(uint val);
	uint getdatrameccerrmcuinhibit();

};

#endif // HILINKCPAPI_H_
