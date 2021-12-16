#ifndef  _HILINK_REG_BASE_H_
#define _HILINK_REG_BASE_H_

//for test method API interfaces
//#include "mapi.hpp"
using namespace std;
//using namespace V93kLimits;
#include <HILINK_DRIVE/d2s_JTAG.h>
//#include "HiLink_Types.h"
#include <HILINK_DRIVE/HiLink_Common_Types.h>


const uint HI_BIT_MASK[]={
		0x0001,
		0x0003,
		0x0007,
		0x000F,
		0x001F,
		0x003F,
		0x007F,
		0x00FF,
		0x01FF,
		0x03FF,
		0x07FF,
		0x0FFF,
		0x1FFF,
		0x3FFF,
		0x7FFF,
		0xFFFF
};

const uint LO_BIT_MASK[]={
		0x0000,
		0x0001,
		0x0003,
		0x0007,
		0x000F,
		0x001F,
		0x003F,
		0x007F,
		0x00FF,
		0x01FF,
		0x03FF,
		0x07FF,
		0x0FFF,
		0x1FFF,
		0x3FFF,
		0x7FFF
};

typedef enum{
	HILINK_PERMACRO_REGISTER,
	HILINK_PERLANE_REGISTER
} E_HILINK_REGISTER_TYPE;

class HILINK_Regs_Base
{
public:

	/*
	 * build register information for relative register
	 * in each registers
	 * example:
	class {
		public:
			T_REG_INFO reg1(){static T_REG_INFO reg={0,"reg1",15,15};return reg;}
			T_REG_INFO reg2(){static T_REG_INFO reg={0,"reg2",14,14};return reg;}
			T_REG_INFO reg3(){static T_REG_INFO reg={0,"reg2",13,13};return reg;}
			...
			bool get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos){
				reg_infos.clear();
				switch(csr){
					case 0:
						reg_infos.push_back(reg1());
						reg_infos.push_back(reg2());
						reg_infos.push_back(reg3());
						break;
					...
				}
				return (reg_infos.size()>0);
			}
	} REG_INFO_CONTAIN;
	*/

protected:
	static string lastTestSuite;

	M_CSR_INFO decode(uint word,const vector<T_REG_INFO>& reg_infos);

	bool verify_started;
	uint focus_csr;
	map<string,uint> focus_regs;
	uint csr_mask;

	bool broadcast;
	uint macroID;
	uint sliceID;
        static uint value_mask;

	void reset_csr_verify();
	bool csr_verify(const T_REG_INFO& reg_info,uint val);

	virtual void fill_csr_bits(uint val,const T_REG_INFO_EX& reg_info_ex);
	virtual uint get_csr_bits(const T_REG_INFO_EX& reg_info_ex);

	virtual uint getAddressMapToHiLink(int csrIndex)=0;

	static uint get_bits(uint word,const T_REG_INFO& reg_info);

	void read_all_csr(uint MacroID,uint SliceID,vector<uint>& rtn);
    void read_all_csr(uint MacroID,uint SliceID,map<uint,vector<uint>  >& rtn);
	//void read_all_csr(uint MacroID,uint SliceID,map<uint,vector<uint>  >& rtn);

	static uint globalMacroID;
	static uint globalLaneID;
	static MACRO_LANE_SEL globalMacroLane_Sel;
	virtual void get_default_MacroLaneID(T_MacroLaneID& id);

	virtual uint sync_CSR_pre_d2s(uint csrindex,uint data,uint mask,uint& readback_csr);
	virtual void check_CSR_pre_d2s(int csrindex,uint readback_csr,uint mask=0x0000);
	void do_check_CSR_pre_d2s(MACRO_LANE_SEL& MacroLane_Sel,int csrindex,uint readback_csr,uint mask=0x0000);
	void embed_check_CSR_into_d2s(MACRO_LANE_SEL& MacroLane_Sel,int csrindex,uint readback_csr,uint mask=0x0000);

	void dumpAllSliceCSR(const MACRO_LANE_SEL& MacroLaneSel,ostringstream& str);
        void dumpAllSliceCSR(const MACRO_LANE_SEL& MacroLaneSel,const string& file_name);
	void dumpAllMacroCSR(const MACRO_LANE_SEL& MacroLaneSel,ostringstream& str);
        void dumpAllMacroCSR(const MACRO_LANE_SEL& MacroLaneSel,const string& file_name);
	void dumpSliceCSR(const uint& MacroID,const uint& LaneID,ostringstream& str);
	void dumpMacroCSR(const uint& MacroID,const uint& SliceID,ostringstream& str);

	virtual bool verify_SliceID(uint id);

public:

	virtual uint& get_csr(uint csrindex)=0;
	virtual uint get_HILINK_MAX_LANE_NUM() = 0;//TODO
	virtual uint getCSRCount()=0;
	virtual string getName()=0;
	virtual E_HILINK_REGISTER_TYPE getType()=0;

	HILINK_Regs_Base& MacroID(uint id);
	HILINK_Regs_Base& SliceID(uint id);
	HILINK_Regs_Base& Broadcast(bool flag);

	HILINK_Regs_Base();
	virtual ~HILINK_Regs_Base();

	static void setAutoReadbackMacroLane(uint MacroID,uint LaneID);
	static void setAutoReadbackMacroLane(const MACRO_LANE_SEL& MacroLane_Sel);

	void addSkipCheckCSR(uint csrindex);

	static uint get_bits(uint word,const T_REG_INFO_EX& reg_info_ex);
	static uint fill_bits(uint word,const T_REG_INFO_EX& reg_info_ex,uint value);

	bool verify_CSR_write_missing();

	virtual bool get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos)=0;
	virtual bool GetCurrentCSRInfo(uint csrindex,M_CSR_INFO& csr_info);
	virtual string getCSRInfoString(uint csrindex,int value =-1);
	virtual string getCSRInfoStringDiff(uint csrindex,int value_dut, int value);//TODO
	virtual bool decodeCSR(uint csrindex,uint csrValue,M_CSR_INFO& csr_info);

	virtual void ExpectValue(uint csrindex, int value, int mask = 0LL,const string& id="");
	virtual void Read2IDString(uint csrindex, const string& id);
		virtual void Read2ID(uint csrindex);//TODO
	virtual int Read2CSR(uint csrindex);//TODO
   // virtual int Read2CSR(uint csrindex);//TODO

	virtual void CheckCSR(uint csrindex, int value=-1, int mask = 0LL);

	void ReadAll2CSR();
	void DisplayAllSegmentOfCSR(uint csrIndex);
	void dumpAllCSR(const MACRO_LANE_SEL& MacroLaneSel,ostringstream& str);
        void dumpAllCSR(const MACRO_LANE_SEL& MacroLaneSel,const string& file_name);
	void dumpCSR(const uint& MacroID,const uint& LaneID,ostringstream& str);


	virtual void Write2DUT(uint csrIndex, int value);
	virtual void Write2DUT(uint csrindex, bool bMarcoBroadcast = true);
        
	virtual void Write2DUT_WITHMASK(uint csrindex,uint Mask);
	virtual void Write2DUT();
	virtual void Write2DUT_DYN(uint csrindex,const string& id);
	virtual void Write2DUT_DYN(uint csrindex,int value,const string& id);

	/***************used for dynamic write***********/
	virtual void Write2DUT_DYN(uint csrindex, const map<int, long long>& value,const string& id);
	virtual void Write2DUT_DYN(uint csrindex, const HILINK_PERSITE_WRITEDYN_EX& value,const string& id);

	void skip_CSR_Sync();
	void skip_CSR_Check();

	static string CSR_CHECK_PreFix;
};


#endif
