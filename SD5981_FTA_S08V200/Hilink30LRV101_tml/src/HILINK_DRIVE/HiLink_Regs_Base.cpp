/*
 * HiLink_Regs_Base.cpp
 *
 *  Created on: Aug 19, 2016
 *      Author: yanfen.fang
 */
#include <HILINK_DRIVE/HiLink_Regs_Base.h>

#include <iomanip>
#include "TestClass.h"
#include <UserAPI.h>

#include <Common_Func/System_Common_Func.h>
#include <HILINK_DRIVE/d2s_JTAG.h>
#include <HILINK_DRIVE/MacroLaneCtrl.h>

d2s_JTAG& the_jtag = d2s_JTAG::Instance();
d2s_JTAG& the_pre_d2s_jtag = d2s_JTAG::pre_d2s_Instance();
uint HILINK_Regs_Base::value_mask = 0;
HILINK_Regs_Base::HILINK_Regs_Base() {
    verify_started = false;
    focus_csr = 0;
    focus_regs.clear();

    broadcast = false;
    macroID = HILINK_INFO.getFirstMacroID();
    sliceID = 0;
    csr_mask = 0x0000;
    globalMacroLane_Sel.clear();
    CSR_CHECK_PreFix = "";

}

HILINK_Regs_Base::~HILINK_Regs_Base() {

}

bool
HILINK_Regs_Base::verify_SliceID(uint id) {
    if (getType() == HILINK_PERMACRO_REGISTER) {
        return (id == 0);
    }
    return !(LANE_INFO[macroID][id].type == LANE_DISABLE);
}

HILINK_Regs_Base&
HILINK_Regs_Base::SliceID(uint id) {
    if (!the_jtag.isProductionMode()) {
        if (id >= get_HILINK_MAX_LANE_NUM()) {
//            cerr << "Error: SliceID: " << id << " should be less than " << get_HILINK_MAX_LANE_NUM() << " which set in Userconfig!" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (HILINK_INFO[macroID].Lane_Num <= 0) {
//            cerr << "Warning: MacroID: " << id << " is invalid!" << endl; //TODO
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }; //TODO

        if (!verify_SliceID(id)) {
//            cerr << "Warning: " << getName() << " SliceID: " << id << " is invalid!" << endl; //TODO
            //		ERROR_EXIT(TM::ABORT_FLOW);//TODO
        }
    }
    sliceID = id;
    globalLaneID = id;
    return *this;
}

HILINK_Regs_Base&
HILINK_Regs_Base::Broadcast(bool flag) {
    broadcast = flag;
    return *this;
}

HILINK_Regs_Base&
HILINK_Regs_Base::MacroID(uint id) {
    if (!the_jtag.isProductionMode()) {
        if (HILINK_INFO[id].Lane_Num <= 0) {
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }; //TODO
    }

    macroID = id;
    globalMacroID = id;
    return *this;
}

uint
HILINK_Regs_Base::fill_bits(uint word, const T_REG_INFO_EX& reg_info_ex, uint value) {
    uint hb = reg_info_ex.reg_info.hi_bit;
    uint lb = reg_info_ex.reg_info.low_bit;

    if (!the_jtag.isProductionMode()) {

        if (hb >= 16) {
//            cerr << "Error: High Bit=" << hb << " should be less than 16 in REG_INFO config!" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }

        if (lb >= 16) {
//            cerr << "Error: Low Bit=" << lb << " should be less than 16 in REG_INFO config!" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (hb < lb) {
//            cerr << "Error: High Bit=" << hb << " should not be less than Low bit=" << lb << " in REG_INFO config!" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }

        uint width = hb - lb;
        if (value > HI_BIT_MASK[width]) {
            INT iDebugAnalog;
            //			GET_TESTFLOW_FLAG	("debug_analog",&iDebugAnalog);
            //			if(iDebugAnalog)
            //			{
            //				cerr<<"Warning: REG value is out of setting range!"<<endl;
            //				cerr<<"Warning:\t "<<reg_info_ex.parent.getName()<<" "<<reg_info_ex.reg_info.reg_name<<" bit "<<hb<<":"<<lb<<hex<<", but set value = 0x"<<value<<dec<<endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
            //			}
        }
    }

    value = value << lb;

    value = ((value & HI_BIT_MASK[hb]) & (~LO_BIT_MASK[lb]));
    value = (value | (word & (~HI_BIT_MASK[hb])));
    value = (value | (word & LO_BIT_MASK[lb]));
    value_mask = HI_BIT_MASK[hb] & (~LO_BIT_MASK[lb]);
    return value;
}

bool
HILINK_Regs_Base::verify_CSR_write_missing() {
    return !verify_started;
}

uint
HILINK_Regs_Base::get_bits(uint word, const T_REG_INFO& reg_info) {
    uint hb = reg_info.hi_bit;
    uint lb = reg_info.low_bit;
    if (!the_jtag.isProductionMode()) {
        if (hb >= 16) {
//            cerr << "Error: High Bit should be less than 16!" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }

        if (lb >= 16) {
//            cerr << "Error: Low Bit should be less than 16!" << endl;
            //		ERROR_EXIT(TM::ABORT_FLOW);
        }

        if (hb < lb) {
//            cerr << "Error: High Bit should not be less than Low bit!" << endl;
            //		ERROR_EXIT(TM::ABORT_FLOW);
        }
    }
    uint value;

    value = ((word & HI_BIT_MASK[hb]) & (~LO_BIT_MASK[lb]));
    value = (value >> lb);


    return value;
}

uint
HILINK_Regs_Base::get_bits(uint word, const T_REG_INFO_EX& reg_info_ex) {
    return get_bits(word, reg_info_ex.reg_info);
}

M_CSR_INFO
HILINK_Regs_Base::decode(uint word, const vector<T_REG_INFO>& reg_infos) {
    M_CSR_INFO rtn;
    rtn.clear();
    for (uint i = 0; i < reg_infos.size(); ++i) {
        rtn[reg_infos[i].reg_name] = get_bits(word, reg_infos[i]);
    }
    return rtn;
}

void
HILINK_Regs_Base::reset_csr_verify() {
    verify_started = false;
    focus_csr = 0;
    focus_regs.clear();
    csr_mask = 0x0000;
}

bool
HILINK_Regs_Base::csr_verify(const T_REG_INFO& reg_info, uint val) {
    val = 0xffff;
    val &= (HI_BIT_MASK[reg_info.hi_bit]);
    val &= (~LO_BIT_MASK[reg_info.low_bit]);
    csr_mask |= val;

    if (the_jtag.isProductionMode()) {
        verify_started = true;
        focus_csr = reg_info.csr;
        return true;
    }

    if (verify_started) {
        if (reg_info.csr != focus_csr) {
            return false;
        } else {
            if (focus_regs.find(reg_info.reg_name) != focus_regs.end()) {
                return false;
            } else {
                focus_regs.insert(pair<string, uint>(reg_info.reg_name, val));
            }
        }
    } else {
        verify_started = true;
        focus_csr = reg_info.csr;
        focus_regs.insert(pair<string, uint>(reg_info.reg_name, val));
    }
    return true;
}

void
HILINK_Regs_Base::fill_csr_bits(uint val, const T_REG_INFO_EX& reg_info_ex) {
    if (!the_jtag.isProductionMode()) {
        if (!the_jtag.is_in_d2s_block()) {
//            cerr << "Error: setxxx command must be used inside d2s block!" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
        uint csrindex = reg_info_ex.reg_info.csr;
        get_csr(csrindex) = fill_bits(get_csr(csrindex), reg_info_ex, val); //* add value to a word(csr)
        if (!csr_verify(reg_info_ex.reg_info, val)) {//* error if write the different CSR or several same reg before write_dut()
//            cout << getName() << " CSR VERIFY FAILED!" << endl;
//            cout << "\t focus_csr: " << focus_csr << endl;
//            cout << "\t focus_regs: " << endl;
            for (map<string, uint>::iterator itr = focus_regs.begin(); itr != focus_regs.end(); itr++) {
//                cout << "\t\t register name" << itr->first << " , register bits: 0x" << hex << itr->second << endl;
            }
//            cout << "\t Current register: " << reg_info_ex.reg_info.reg_name << "@CSR(" << dec << reg_info_ex.reg_info.csr << ") : 0x" << hex << val << dec << endl;
//            cerr << "Error:\t Please do not configure different CSR or configure same REG before the current Write2DUT()" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
    } else {
        uint mask = 0xffff;
        mask &= (HI_BIT_MASK[reg_info_ex.reg_info.hi_bit]);
        mask &= (~LO_BIT_MASK[reg_info_ex.reg_info.low_bit]);
        csr_mask |= mask;
        uint csrindex = reg_info_ex.reg_info.csr;
        focus_csr = csrindex;
        get_csr(csrindex) = ((get_csr(csrindex)&~mask) | ((val << reg_info_ex.reg_info.low_bit) & mask));
    }
}

uint
HILINK_Regs_Base::get_csr_bits(const T_REG_INFO_EX& reg_info_ex) {
    if (!the_jtag.isProductionMode()) {
        if (the_jtag.is_in_d2s_block()) {
            //cerr<<"Warning: In d2sBlock "<<d2sFramework::get_current_prefix()
            //<<" "<<reg_info_ex.parent.getName()<<"::get"<<reg_info_ex.reg_info.reg_name
            //<<"() should be used outside d2s block!"<<endl;
        }
    }
    uint csrindex = reg_info_ex.reg_info.csr;
    return get_bits(get_csr(csrindex), reg_info_ex);
}

bool
HILINK_Regs_Base::GetCurrentCSRInfo(uint csrindex, M_CSR_INFO& csr_info) {
    if (csrindex >= getCSRCount()) {
//        cerr << "Error: CSRIndex should not be larger than " << dec << getCSRCount() << endl;
        //		ERROR_EXIT(TM::ABORT_FLOW);
    }
    vector<T_REG_INFO> reg_infos;
    if (get_reg_infos(csrindex, reg_infos)) {
        csr_info.clear();
        csr_info = decode(get_csr(csrindex), reg_infos);
        return true;
    }
    return false;
}

string
HILINK_Regs_Base::getCSRInfoString(uint csrindex, int value) {
    if (csrindex >= getCSRCount()) {
//        cerr << "Error: CSRIndex should not be larger than " << dec << getCSRCount() << endl;
        //		ERROR_EXIT(TM::ABORT_FLOW);
    }
    ostringstream str;
    vector<T_REG_INFO> reg_infos;
    M_CSR_INFO csr_info;
    csr_info.clear();

    if (get_reg_infos(csrindex, reg_infos)) {
        if (value < 0) {
            value = get_csr(csrindex);
        }
        csr_info = decode(value, reg_infos);
        unsigned long long code = (getAddressMapToHiLink(csrindex) << 16) | value;
        str << "CSR" << csrindex << "\t[15:0]\t0x" << hex << code << ";" << dec << endl;
        for (uint i = 0; i < reg_infos.size(); i++) {
            T_REG_INFO& info = reg_infos[i];
            //TODO：解決平臺問題
            str<<"\t"<<setw(24)<<left<<info.reg_name<<"\t["<<info.hi_bit<<":"<<info.low_bit<<"]\t0x"<<hex<<csr_info[info.reg_name]<<dec<<endl;
        }
        return str.str();
    }

    return "";
}

//TODO

string
HILINK_Regs_Base::getCSRInfoStringDiff(uint csrindex, int value_dut, int value) {
    if (csrindex >= getCSRCount()) {
//        cerr << "Error: CSRIndex should not be larger than " << dec << getCSRCount() << endl;
        //		ERROR_EXIT(TM::ABORT_FLOW);
    }
    ostringstream str;
    vector<T_REG_INFO> reg_infos, reg_infos_dut;
    M_CSR_INFO csr_info, csr_info_dut;
    csr_info.clear();
    csr_info_dut.clear();

    if (get_reg_infos(csrindex, reg_infos)) {
        /*		if(value<0){
                                value=get_csr(csrindex);
                        }*/
        csr_info = decode(value, reg_infos);
        csr_info_dut = decode(value_dut, reg_infos_dut);
        unsigned long long code = (getAddressMapToHiLink(csrindex) << 16) | value;
        str << "CSR" << csrindex << "\t[15:0]\t0x" << hex << code << ";" << dec << endl;
        for (uint i = 0; i < reg_infos.size(); i++) {

            if (csr_info != csr_info_dut) {
                T_REG_INFO& info = reg_infos[i];
                str << "\t" << info.reg_name << "\t[" << info.hi_bit << ":" << info.low_bit << "]\t0x" << hex << " local: " << csr_info[info.reg_name] << dec << endl;
                str << "\t" << info.reg_name << "\t[" << info.hi_bit << ":" << info.low_bit << "]\t0x" << hex << " dut: " << csr_info_dut[info.reg_name] << dec << endl;
            }
        }
        return str.str();
    }

    return "";
}

bool
HILINK_Regs_Base::decodeCSR(uint csrindex, uint csrValue, M_CSR_INFO& csr_info) {
    if (csrindex >= getCSRCount()) {
//        cerr << "Error: CSRIndex should not be larger than " << dec << getCSRCount() << endl;
        //		ERROR_EXIT(TM::ABORT_FLOW);
    }
    vector<T_REG_INFO> reg_infos;
    if (get_reg_infos(csrindex, reg_infos)) {
        csr_info.clear();
        csr_info = decode(csrValue, reg_infos);
        return true;
    }
    return false;
}

void
HILINK_Regs_Base::ExpectValue(uint csrindex, int value, int mask, const string& id) {
    if (!the_jtag.isProductionMode()) {
        if (broadcast == 1) {//TODO
//            cerr << "Error: broadcast should be 0 when expectValue() is required!" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (csrindex >= getCSRCount()) {
//            cerr << "Error: CSRIndex=" << csrindex << " should be less than " << dec << getCSRCount() << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (!verify_CSR_write_missing()) {
//            cout << "Error: " << getName() << " previous writing is missing" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
    }
    int mAddr = getAddressMapToHiLink(csrindex) & 0x03FFFF;

    the_jtag.expectValue(mAddr >> 1, value, mask, id);
}

void
HILINK_Regs_Base::CheckCSR(uint csrindex, int value, int mask) {
    if (!the_jtag.isProductionMode()) {
        if (csrindex >= getCSRCount()) {
//            cerr << "Error: CSRIndex should not be larger than " << dec << getCSRCount() << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (!verify_CSR_write_missing()) {
//            cout << "Error: " << getName() << " previous writing is missing" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
    }
    if (value >= 0) {
        ExpectValue(csrindex, value, mask);
    } else {//* in case of no sync
        int mAddr = getAddressMapToHiLink(csrindex) & 0x03FFFF;

        ostringstream str;
        str << getName() << "_M" << dec << macroID << "L" << dec << sliceID << "_Verify(" << dec << csrindex << ")" << endl;
        the_jtag.expectValue(mAddr >> 1, get_csr(csrindex), mask, "", str.str());
    }
}

void
HILINK_Regs_Base::Read2IDString(uint csrindex, const string& id) {
    if (!the_jtag.isProductionMode()) {
        if (broadcast == 1) {//TODO
//            cerr << "Error: broadcast should be 0 when reading CSR is required!" << endl;
            //		ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (csrindex >= getCSRCount()) {
//            cerr << "Error: CSRIndex=" << csrindex << " should be less than " << dec << getCSRCount() << endl;
            //		ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (!verify_CSR_write_missing()) {
//            cout << "Error: " << getName() << " previous writing is missing" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
    }
    int mAddr = getAddressMapToHiLink(csrindex) & 0x03FFFF;


    unsigned long long label_code = 0xDB40000000000000LL;
    label_code |= ((unsigned long long) (mAddr & 0x3ffff));
    //	string label_md5;
    //	label_md5.resize(8);
    //	label_md5.assign((char*)&label_code,8);

    //the_jtag.read(mAddr>>1,id,&label_code);
    the_jtag.read(mAddr >> 1, id);
}

void//TODO
HILINK_Regs_Base::Read2ID(uint csrindex) {
    if (!the_jtag.isProductionMode()) {
        if (csrindex >= getCSRCount()) {
//            cerr << "Error: CSRIndex should be less than " << dec << getCSRCount() << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (!verify_CSR_write_missing()) {
//            cout << "Error: " << getName() << " previous writing is missing" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
    }

    int mAddr = getAddressMapToHiLink(csrindex) & 0x03FFFF;

    char buf[256];
    string name = getName();
    sprintf(buf, "%s_M%dL%d_ReadCSR%d", name.c_str(), macroID, sliceID, csrindex);
    the_jtag.read(mAddr >> 1, buf);
}

//TODO

/*  masked by tony 20210818  redefine with below function
int
HILINK_Regs_Base::Read2CSR(uint csrindex) {
    //	D2S_FRAMEWORK;

    char buf[256];
    //	sprintf(label,"Read2CSRMPB_DS_CLK_L%d_CSR%d_READ_%s",sliceID,csrindex,jtag.Context.c_str());

    //	fr.d2s_LABEL_BEGIN("ReadCSR",d2sFrameWorkModeType::Enum(d2s_mode));
    //		Read2ID(csrindex);
    //	fr.d2s_LABEL_END();
    //
    //	string name = getName();//TODO
    //	sprintf(buf,"%s_M%dL%d_ReadCSR%d",name.c_str(),macroID,sliceID,csrindex);
    //	get_csr(csrindex) = (uint)(jtag.getReadValue(buf));//* uint& get_csr()

    //	sprintf(tmp,"DS_CLK_L%d_CSR%d_%s",sliceID,csrindex,jtag.Context.c_str());
    //	csr[csrindex] = (UINT)(jtag.getReadValue(tmp));


    //hout(REG_ACCESS) << "================ Macro[" << dec << macroID << "]" << "  Lane[" << sliceID << "]" << "  Read  ================" << endl;
    if (hout.getLevel() >= 4) {
        //		//hout(REG_ACCESS) << setw(10)  << "REG_ACCESS   (Site" << setw(4) << setfill('0') << CURRENT_SITE_NUMBER() << ") : " << setw(0) << setfill(' ');
        //		char buf[1024];
        //		sprintf(buf,"---- %s CSR[%2u]\tAddr = 0x%04x \t Data = 0x%04x ----------",getName().c_str(),csrindex,getAddressMapToHiLink(csrindex),get_csr(csrindex));
        //		//hout(REG_ACCESS) << buf<<endl;

        //hout(REG_ACCESS) << getCSRInfoString(csrindex);

        //		//hout(REG_ACCESS) << setw(10)  << "REG_ACCESS   (Site" << setw(4) << setfill('0') << CURRENT_SITE_NUMBER() << ") : " << setw(0) << setfill(' ');
        //hout(REG_ACCESS) << "-----------------------------------------------------------------" << endl;
    }
    return get_csr(csrindex);
}
*/


int
HILINK_Regs_Base::Read2CSR(uint csrindex) {  //check with V100 have api  note by tony 20210818
    //	D2S_FRAMEWORK;
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    char buf[256];
    
    d2s::d2s_LABEL_BEGIN( "Read2CSRMPB_DS_CLK_L", Global_D2S_Mode);
            Read2ID(csrindex);
    d2s::d2s_LABEL_END();

    string name = getName();//TODO
    sprintf(buf,"%s_M%dL%d_ReadCSR%d",name.c_str(),macroID,sliceID,csrindex);
    get_csr(csrindex) = (uint)(jtag.getReadValue(buf)).begin()->second;//* uint& get_csr()  //modify by tony 20210818

    
//    char tmp[256]; 
//    sprintf(tmp,"DS_CLK_L%d_CSR%d_%s",sliceID,csrindex,jtag.Context.c_str());
//    csr[csrindex] = (UINT)(jtag.getReadValue(tmp));


    //hout(REG_ACCESS) << "================ Macro[" << dec << macroID << "]" << "  Lane[" << sliceID << "]" << "  Read  ================" << endl;
    if (hout.getLevel() >= 4) {
        //		//hout(REG_ACCESS) << setw(10)  << "REG_ACCESS   (Site" << setw(4) << setfill('0') << CURRENT_SITE_NUMBER() << ") : " << setw(0) << setfill(' ');
        //		char buf[1024];
        //		sprintf(buf,"---- %s CSR[%2u]\tAddr = 0x%04x \t Data = 0x%04x ----------",getName().c_str(),csrindex,getAddressMapToHiLink(csrindex),get_csr(csrindex));
        //		//hout(REG_ACCESS) << buf<<endl;

        //hout(REG_ACCESS) << getCSRInfoString(csrindex);

        //		//hout(REG_ACCESS) << setw(10)  << "REG_ACCESS   (Site" << setw(4) << setfill('0') << CURRENT_SITE_NUMBER() << ") : " << setw(0) << setfill(' ');
        //hout(REG_ACCESS) << "-----------------------------------------------------------------" << endl;
    }
    return get_csr(csrindex);
}
void
HILINK_Regs_Base::Write2DUT(uint csrindex, bool bMarcoBroadcast) {

    int mAddr = getAddressMapToHiLink(csrindex);
    int mData = get_csr(csrindex);
    uint mask = csr_mask;
    int md5Data = get_csr(csrindex)&csr_mask;
    uint readback_csr = mData;
    if (!the_jtag.isProductionMode()) {
        if (csrindex >= getCSRCount()) {
//            cerr << "Error: CSRIndex=" << csrindex << " should be less than " << dec << getCSRCount() << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (!verify_started) {
//            cout << "Error: " << getName() << " NO register is written!" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (focus_csr != csrindex) {
//            cout << "Error: " << getName() << " WRITE CSR(" << csrindex << ") and focus CSR(" << focus_csr << ") mismatch!" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
        bool skip_CSR_sync = false; //the_pre_d2s_jtag.is_address_synchronized(getName()+"_SKIP_CSR_SYNC_ALL",0);
        if (GLOBAL_CSR_SYNC_FLAG && csr_mask != 0xffff && !skip_CSR_sync) {
            mData = sync_CSR_pre_d2s(csrindex, mData, mask, readback_csr);
            get_csr(csrindex) = mData;
            if(bMarcoBroadcast){
                sync_CSR_selectMacro_MB(globalMacroLane_Sel);
            }            
        }
    }


    if (csr_mask != 0xffff) {
        the_jtag.setAppendSuiteName();
        check_CSR_pre_d2s(csrindex, readback_csr, csr_mask);
    }


    //	if(!focus_regs.empty()){
    //		for(map<string,uint>::iterator itr=focus_regs.begin();itr!=focus_regs.end();itr++){
    //			mask |= itr->second;
    //		}
    //	}
    //	else{
    //		mask=0xffff;
    //	}

    unsigned long long label_code = 0xDB00000000000000LL;
    label_code |= ((unsigned long long) (mAddr & 0x3ffff) << 32);
    label_code |= ((unsigned long long) (mData & mask & 0xffff) << 16);
    label_code |= (mask & 0xffff);
    //	string label_md5;
    //	label_md5.resize(8);
    //	label_md5.assign((char*)&label_code,8);

    //	if(!focus_regs.empty()){
    //		string label_md5=getName()+"~";
    //		ostringstream str;
    //		str<<"CSR("<<csrindex<<")~";
    //		label_md5+=str.str();
    //		for(map<string,uint>::iterator itr=focus_regs.begin();itr!=focus_regs.end();itr++){
    //			ostringstream str;
    //			str<<itr->first<<":0x"<<hex<<itr->second<<"~";
    //			label_md5+=str.str();
    //		}
    //		if(DebugON){
    //			cout<<"focus_regs is not empty,so "<<endl;//TODO
    //			cout<<"label_md5: "<<label_md5<<endl;//TODO
    //		}
    //		jtag.write(mAddr>>1,mData,label_md5);
    //	}
    //	else{
    //		if(DebugON){
    //			cout<<"focus_regs is empty,so "<<endl;//TODO
    //			cout<<"label_md5: "<<""<<endl;//TODO
    //		}
    //		jtag.write(mAddr>>1,mData);
    //	}
    if (hout.getLevel() & 0x8) {
        //hout(REG_ACCESS) << getName() << " Write CSR(" << csrindex << ", 0x" << hex << mData << ")" << dec << endl;
    }

    //the_jtag.write(mAddr>>1,mData,&label_code);
    //the_jtag.expectValue(0Xff, 0X1234, 0x00FF);//zdb
    the_jtag.write(mAddr >> 1, mData, md5Data);
    reset_csr_verify();
}

void
HILINK_Regs_Base::Write2DUT_WITHMASK(uint csrindex, uint Mask) {

    int mAddr = getAddressMapToHiLink(csrindex);
    int mData = get_csr(csrindex);
    uint mask = csr_mask;
    uint readback_csr = mData;
    if (!the_jtag.isProductionMode()) {
        if (csrindex >= getCSRCount()) {
//            cerr << "Error: CSRIndex=" << csrindex << " should be less than " << dec << getCSRCount() << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (!verify_started) {
//            cout << "Error: " << getName() << " NO register is written!" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (focus_csr != csrindex) {
//            cout << "Error: " << getName() << " WRITE CSR(" << csrindex << ") and focus CSR(" << focus_csr << ") mismatch!" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
        bool skip_CSR_sync = the_pre_d2s_jtag.is_address_synchronized(getName() + "_SKIP_CSR_SYNC_ALL", 0);
        if (GLOBAL_CSR_SYNC_FLAG && csr_mask != 0xffff && !skip_CSR_sync) {
            mData = sync_CSR_pre_d2s(csrindex, mData, mask, readback_csr);
            get_csr(csrindex) = mData;
        }
    }


    if ((csr_mask | Mask) != 0xffff) {
        the_jtag.setAppendSuiteName();
        check_CSR_pre_d2s(csrindex, readback_csr, (csr_mask | Mask));
    }


    //	if(!focus_regs.empty()){
    //		for(map<string,uint>::iterator itr=focus_regs.begin();itr!=focus_regs.end();itr++){
    //			mask |= itr->second;
    //		}
    //	}
    //	else{
    //		mask=0xffff;
    //	}

    unsigned long long label_code = 0xDB00000000000000LL;
    label_code |= ((unsigned long long) (mAddr & 0x3ffff) << 32);
    label_code |= ((unsigned long long) (mData & mask & 0xffff) << 16);
    label_code |= (mask & 0xffff);
    //	string label_md5;
    //	label_md5.resize(8);
    //	label_md5.assign((char*)&label_code,8);

    //	if(!focus_regs.empty()){
    //		string label_md5=getName()+"~";
    //		ostringstream str;
    //		str<<"CSR("<<csrindex<<")~";
    //		label_md5+=str.str();
    //		for(map<string,uint>::iterator itr=focus_regs.begin();itr!=focus_regs.end();itr++){
    //			ostringstream str;
    //			str<<itr->first<<":0x"<<hex<<itr->second<<"~";
    //			label_md5+=str.str();
    //		}
    //		if(DebugON){
    //			cout<<"focus_regs is not empty,so "<<endl;//TODO
    //			cout<<"label_md5: "<<label_md5<<endl;//TODO
    //		}
    //		jtag.write(mAddr>>1,mData,label_md5);
    //	}
    //	else{
    //		if(DebugON){
    //			cout<<"focus_regs is empty,so "<<endl;//TODO
    //			cout<<"label_md5: "<<""<<endl;//TODO
    //		}
    //		jtag.write(mAddr>>1,mData);
    //	}
    if (hout.getLevel() & 0x8) {
        //hout(REG_ACCESS) << getName() << " Write CSR(" << csrindex << ", 0x" << hex << mData << ")" << dec << endl;
    }

    //the_jtag.write(mAddr>>1,mData,&label_code);
    the_jtag.write(mAddr >> 1, mData);
    reset_csr_verify();
}

void
HILINK_Regs_Base::Write2DUT() {
    if (!the_jtag.isProductionMode()) {
        if (!verify_started) {
//            cout << "Error: " << getName() << " NO register is written!" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
    }
    Write2DUT(focus_csr);
}

void
HILINK_Regs_Base::Write2DUT_DYN(uint csrindex, const string& id) {
    if (!the_jtag.isProductionMode()) {
        if (csrindex >= getCSRCount()) {
//            cerr << "Error: CSRIndex should not be larger than " << dec << getCSRCount() << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (!verify_started) {
//            cout << "Error: " << getName() << " NO register is written!" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (focus_csr != csrindex) {
//            cout << "Error: " << getName() << " WRITE CSR(" << csrindex << ") and focus CSR(" << focus_csr << ") mismatch!" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
    }

    int mAddr = getAddressMapToHiLink(csrindex);
    int mData = get_csr(csrindex)&0xFFFF;



    //    the_jtag.writeDynamic(mAddr>>1,mData,id);
    reset_csr_verify();

    //zhenghe add this code to avoid DynamicWrite and selectMacro_MB() or SelectMacro() in same d2s block
    the_pre_d2s_jtag.set_address_synchronized_flag(getName() + "DYNwrite", csrindex);
    if ((the_pre_d2s_jtag.is_address_synchronized(getName() + "firstlane_sync", csrindex)) or (the_pre_d2s_jtag.is_address_synchronized(getName() + "perlane_sync", csrindex))) {
//        cout << "Error: SelectMacro() and SelectMacro_MB() or dynamicwrite() Can't be used in same d2s block for same CSR" << endl;
        //		ERROR_EXIT(TM::ABORT_FLOW);
    }
}

void
HILINK_Regs_Base::Write2DUT_DYN(uint csrindex, int value, const string& id) {
    if (!the_jtag.isProductionMode()) {
        if (csrindex >= getCSRCount()) {
//            cerr << "Error: CSRIndex should not be larger than " << dec << getCSRCount() << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (!verify_CSR_write_missing()) {
//            cout << getName() << " previous writing is missing" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
    }

    int mAddr = getAddressMapToHiLink(csrindex);
    int mData = value & 0xFFFF;

//#define MAX_SITES 8
//
//	the_jtag.writeDynamic(mAddr >> 1, (long long int*)mData,MAX_SITES);//id  modify by tony 20210818
//
//#undef MAX_SITES

	the_jtag.writeDynamic(mAddr >> 1, (long long int*)mData,id);//id  modify by tony 20210915

	reset_csr_verify();

    //zhenghe add this code to avoid DynamicWrite and selectMacro_MB() or SelectMacro() in same d2s block
    //    the_pre_d2s_jtag.set_address_synchronized_flag(getName() + "DYNwrite", csrindex);
    //    if ((the_pre_d2s_jtag.is_address_synchronized(getName() + "firstlane_sync", csrindex)) or (the_pre_d2s_jtag.is_address_synchronized(getName() + "perlane_sync", csrindex))) {
    //        cout << "Error: SelectMacro() and SelectMacro_MB() or dynamicwrite() Can't be used in same d2s block for same CSR" << endl;
    //        //		ERROR_EXIT(TM::ABORT_FLOW);
    //    }
}

void
HILINK_Regs_Base::Write2DUT_DYN(uint csrindex, const map<int, long long>& value, const string& id) {
    if (!the_jtag.isProductionMode()) {
        if (csrindex >= getCSRCount()) {
//            cerr << "Error: CSRIndex should not be larger than " << dec << getCSRCount() << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (!verify_CSR_write_missing()) {
//            cout << getName() << " previous writing is missing" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
    }

    int mAddr = getAddressMapToHiLink(csrindex);

    the_jtag.writeDynamicPerSite(mAddr >> 1, value, id);
    reset_csr_verify();

    //zhenghe add this code to avoid DynamicWrite and selectMacro_MB() or SelectMacro() in same d2s block
    // the_pre_d2s_jtag.set_address_synchronized_flag(getName() + "DYNwrite", csrindex);
    //    if ((the_pre_d2s_jtag.is_address_synchronized(getName() + "firstlane_sync", csrindex)) or (the_pre_d2s_jtag.is_address_synchronized(getName() + "perlane_sync", csrindex))) {
    //        cout << "Error: SelectMacro() and SelectMacro_MB() or dynamicwrite() Can't be used in same d2s block for same CSR" << endl;
    //        //		ERROR_EXIT(TM::ABORT_FLOW);
    //    }
}

void
HILINK_Regs_Base::Write2DUT_DYN(uint csrindex, const HILINK_PERSITE_WRITEDYN_EX& value, const string& id) {
    if (!the_jtag.isProductionMode()) {
        if (csrindex >= getCSRCount()) {
//            cerr << "Error: CSRIndex should not be larger than " << dec << getCSRCount() << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (!verify_CSR_write_missing()) {
//            cout << getName() << " previous writing is missing" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
    }

    int mAddr = getAddressMapToHiLink(csrindex);

    //the_jtag.writeDynamicPerSite_EX(mAddr>>1,value,id);
    reset_csr_verify();

    //zhenghe add this code to avoid DynamicWrite and selectMacro_MB() or SelectMacro() in same d2s block
    the_pre_d2s_jtag.set_address_synchronized_flag(getName() + "DYNwrite", csrindex);
    if ((the_pre_d2s_jtag.is_address_synchronized(getName() + "firstlane_sync", csrindex)) or (the_pre_d2s_jtag.is_address_synchronized(getName() + "perlane_sync", csrindex))) {
//        cout << "Error: SelectMacro() and SelectMacro_MB() or dynamicwrite() Can't be used in same d2s block for same CSR" << endl;
        //		ERROR_EXIT(TM::ABORT_FLOW);
    }

}

void
HILINK_Regs_Base::Write2DUT(uint csrIndex, int value) {
    if (!the_jtag.isProductionMode()) {
        if (csrIndex >= getCSRCount()) {
//            cerr << "Error: CSRIndex=" << csrIndex << " should be less than " << dec << getCSRCount() << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
        if (!verify_CSR_write_missing()) {
//            cout << "Error: " << getName() << " previous writing is missing" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
    }
    get_csr(csrIndex) = value;
    verify_started = true;
    focus_csr = csrIndex;
    csr_mask = 0xffff;
    Write2DUT(csrIndex);
}

void
HILINK_Regs_Base::read_all_csr(uint MacroID, uint SliceID, map<uint, vector<uint> >& rtn) {  //check V100 have api ,note by tony 20210818
    rtn.clear();
//    FOREACH_ACTIVE_SITE(api) {
//        INT SiteID = api->Get_active_site();
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

    		rtn[SiteID].resize(getCSRCount(),0);
        FOREACH_ACTIVESITE_END
    d2s_JTAG& jtag = d2s_JTAG::Instance();

    d2s::d2s_LABEL_BEGIN( "read_all_csr", Global_D2S_Mode);
            selectMacro(MacroID);
            this->MacroID(MacroID).SliceID(SliceID).Broadcast(0);
            for(uint i=0;i<getCSRCount();i++){
                    ostringstream buf;
                    buf<<"CSR"<<i;
                    Read2IDString(i,buf.str());
            }
    d2s::d2s_LABEL_END();
//    FOREACH_ACTIVE_SITE(api) {
//        INT SiteID = api->Get_active_site();
        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
    		for(uint i=0;i<getCSRCount();i++){
    			ostringstream buf;
    			buf<<"CSR"<<i;
    			rtn[SiteID][i]=jtag.getReadValue(buf.str())[SiteID];
    		}
        FOREACH_ACTIVESITE_END
}

//
//void
//HILINK_Regs_Base::read_all_csr(uint MacroID, uint SliceID, map<uint, vector<uint> >& rtn) {   ////redefine ,masked by tony 20210818
//    rtn.clear();

////    FOREACH_ACTIVE_SITE(api) {
////        INT SiteID = api->Get_active_site();
////    		rtn[SiteID].resize(getCSRCount(),0);
////    }
////    d2s_JTAG& jtag = d2s_JTAG::Instance();
////
////    d2s::d2s_LABEL_BEGIN( "read_all_csr", Global_D2S_Mode);
////            selectMacro(MacroID);
////            this->MacroID(MacroID).SliceID(SliceID).Broadcast(0);
////            for(uint i=0;i<getCSRCount();i++){
////                    ostringstream buf;
////                    buf<<"CSR"<<i;
////                    Read2IDString(i,buf.str());
////            }
////    d2s::d2s_LABEL_END();
////    FOREACH_ACTIVE_SITE(api) {
////        INT SiteID = api->Get_active_site();
////    		for(uint i=0;i<getCSRCount();i++){
////    			ostringstream buf;
////    			buf<<"CSR"<<i;
////    			rtn[SiteID][i]=jtag.getReadValue(buf.str());
////    		}
////    }

//}

void
HILINK_Regs_Base::read_all_csr(uint MacroID, uint SliceID, vector<uint>& rtn) {
    rtn.clear();
    rtn.resize(getCSRCount(), 0);
    //D2S_FRAMEWORK;
    //	D2S.d2s_LABEL_BEGIN("read_all_csr",d2sFrameWorkModeType::Enum(d2s_mode));
    //		selectMacro(MacroID);
    //		this->MacroID(MacroID).SliceID(SliceID).Broadcast(0);
    //		for(uint i=0;i<rtn.size();i++){
    //			ostringstream buf;
    //			buf<<"CSR"<<i;
    //			Read2IDString(i,buf.str());
    //		}
    //	fr.d2s_LABEL_END();
    //	for(uint i=0;i<rtn.size();i++){
    //		ostringstream buf;
    //		buf<<"CSR"<<i;
    //		rtn[i]=jtag.getReadValue(buf.str());
    //	}
}

uint HILINK_Regs_Base::globalMacroID = 0;
uint HILINK_Regs_Base::globalLaneID = 0;
MACRO_LANE_SEL HILINK_Regs_Base::globalMacroLane_Sel;

void
HILINK_Regs_Base::get_default_MacroLaneID(T_MacroLaneID& id) {
    id.MacroID = globalMacroID;
    id.LaneID = globalLaneID;
}

void
HILINK_Regs_Base::setAutoReadbackMacroLane(uint MacroID, uint LaneID) {
    globalMacroID = MacroID;
    globalLaneID = LaneID;
    globalMacroLane_Sel.clear();
}

void
HILINK_Regs_Base::setAutoReadbackMacroLane(const MACRO_LANE_SEL& MacroLane_Sel) {
    assert(MacroLane_Sel.size() > 0);
    globalMacroID = MacroLane_Sel[0].MacroID;
    if (MacroLane_Sel[0].vLane.size() > 0) {
        globalLaneID = MacroLane_Sel[0].vLane[0];
    } else {
        globalLaneID = 0;
    }
    globalMacroLane_Sel.clear();
    T_MACRO_LANE_SEL tmp;
    for (uint midx = 0; midx < MacroLane_Sel.size(); midx++) {
        tmp.MacroID = MacroLane_Sel[midx].MacroID;
        tmp.SliceID = MacroLane_Sel[midx].SliceID;
        tmp.vLane.clear();
        for (uint lidx = 0; lidx < MacroLane_Sel[midx].vLane.size(); lidx++) {
            tmp.vLane.push_back(MacroLane_Sel[midx].vLane[lidx]);
        }
        globalMacroLane_Sel.push_back(tmp);
    }
}

uint
HILINK_Regs_Base::sync_CSR_pre_d2s(uint csrindex, uint data, uint mask, uint& readback_csr) {
    uint rtn = data;

    readback_csr = data;
    static bool notified = false;
    if (!notified) {
//        cout << "Info: CSR pre d2s synchronization is turned on, make sure SelectMacro is executed in every d2s blocks!" << endl;
        notified = true;
    }
    //the_pre_d2s_jtag.set_address_synchronized_flag("AUTO_CSR_SYNC_DONE", 0);
    string prelane_title = "";
    //zhenghe modify this to avoid selectmacro and selectMacro_MB in same d2s block
    //    if (globalMacroLane_Sel.size() < 1) {
    //        ostringstream str;
    //        str << "_M" << globalMacroID << "L" << globalLaneID;
    //        prelane_title = str.str();
    //        if ((the_pre_d2s_jtag.is_address_synchronized(getName() + "firstlane_sync", csrindex)) or (the_pre_d2s_jtag.is_address_synchronized(getName() + "DYNwrite", csrindex))) {
    //            cout << "Error: SelectMacro() and SelectMacro_MB() or dynamicwrite() Can't be used in same d2s block for same CSR" << endl;
    //            //			ERROR_EXIT(TM::ABORT_FLOW);
    //        }
    //        the_pre_d2s_jtag.set_address_synchronized_flag(getName() + "perlane_sync", csrindex);
    //
    //    } else {
    //        if ((the_pre_d2s_jtag.is_address_synchronized(getName() + "perlane_sync", csrindex)) or (the_pre_d2s_jtag.is_address_synchronized(getName() + "DYNwrite", csrindex))) {
    //            cout << "Error: SelectMacro() and SelectMacro_MB() or dynamicwrite() Can't be used in same d2s block for same CSR" << endl;
    //            //			ERROR_EXIT(TM::ABORT_FLOW);
    //        }
    //        the_pre_d2s_jtag.set_address_synchronized_flag(getName() + "firstlane_sync", csrindex);
    //
    //    }
    //    if (the_pre_d2s_jtag.is_address_synchronized(getName() + prelane_title, csrindex)) {
    //        //cout<<getName()<<" CSR"<<csrindex<<" is already synchronized!"<<endl;
    //        return rtn;
    //    } else {
    //cout<<"Synchronizing "<<getName()<<" CSR"<<csrindex<<endl;
    uint backup_macroid = macroID, backup_sliceid = sliceID;
    bool backup_broadcast = broadcast;
    T_MacroLaneID macrolaneid;
    //		get_default_MacroLaneID(macrolaneid);
    macrolaneid.MacroID = globalMacroID;
    macrolaneid.LaneID = globalLaneID;

    //ARRAY_I sites;
    /*
                    if(TM::ifWithinParallelBlock()){
                            GET_TEST_FOCUS(sites);
                            bool target_exists=false;
                            for(int i=0;i<sites.size();i++){
                                    if(sites[i] == FOCUS_SITE){
                                            SET_TEST_FOCUS(FOCUS_SITE);
                                            target_exists=true;
                                            break;
                                    }
                            }
                            if(!target_exists){
                                    SET_TEST_FOCUS(sites[0]);
                            }
                    }
     */
    //the_pre_d2s_jtag.pre_d2s_begin();
    macroID = macrolaneid.MacroID;
    sliceID = macrolaneid.LaneID;
    broadcast = 0;
    pred2s_selectMacro(macroID);
    int mAddr = getAddressMapToHiLink(csrindex);
    the_pre_d2s_jtag.read(mAddr >> 1, "ReadBack");
    uint current_csr = the_pre_d2s_jtag.getReadValue("ReadBack").begin()->second;
    if (the_pre_d2s_jtag.Is_simulator()) {
        current_csr = 0xabcd;
    }
    readback_csr = current_csr;
    macroID = backup_macroid;
    sliceID = backup_sliceid;
    broadcast = backup_broadcast;

    // the_pre_d2s_jtag.set_address_synchronized_flag(getName() + prelane_title, csrindex);
    rtn = ((data & mask) | (current_csr & (~mask)));

    return rtn;
}

string HILINK_Regs_Base::CSR_CHECK_PreFix;

void
HILINK_Regs_Base::check_CSR_pre_d2s(int csrindex, uint readback_csr, uint mask) {
    //	static int isCheck=0;
    //	static bool is_flow_variable_exists=true;
    //	if(is_flow_variable_exists){
    //		try{
    //			GET_USER_FLAG("CSR_atomic_operation",&isCheck);
    //		}
    //		catch(...){
    //			is_flow_variable_exists=false;
    //			isCheck=false;
    //		}
    //	}
    int isCheck = 0; //the_jtag.isCheck();//通过用户设置的flag zdb
    if (!isCheck) {
        return;
    }



    bool Skip_ALL_CSR_CHECK = false; //the_pre_d2s_jtag.is_address_synchronized(getName() + "_SKIP_CSR_CHECK_ALL", 0);
    if (Skip_ALL_CSR_CHECK) {
        return;
    }


    //    if (the_pre_d2s_jtag.is_address_synchronized(getName() + "_SKIP_CSR_CHECK", csrindex)) {
    //        return;
    //    }
    //    string prelane_title = "";
    //    if (globalMacroLane_Sel.size() < 1) {
    //        ostringstream str;
    //        str << "_M" << globalMacroID << "L" << globalLaneID;
    //        prelane_title = str.str();
    //    }
    //    if (the_pre_d2s_jtag.is_address_synchronized(getName() + "_CSR_CHECK" + prelane_title, csrindex)) {
    //        return;
    //    }

    if ((isCheck & 0x2) || (isCheck & 0x8)) {

        the_jtag.enableCSRCheckForNextExecution();
    }

    if (globalMacroLane_Sel.size() < 1) {
        MACRO_LANE_SEL csr_check_macrolane;
        T_MACRO_LANE_SEL tmp;
        tmp.MacroID = globalMacroID;
        tmp.SliceID = 0;
        tmp.vLane.clear();
        tmp.vLane.push_back(globalLaneID);
        csr_check_macrolane.push_back(tmp);
        if (isCheck & 0x1) {
            do_check_CSR_pre_d2s(csr_check_macrolane, csrindex, readback_csr, mask);
        }
        if ((isCheck & 0x2) || (isCheck & 0x8)) {
            embed_check_CSR_into_d2s(csr_check_macrolane, csrindex, readback_csr, mask);
        }
    } else {
        if (isCheck & 0x1) {
            do_check_CSR_pre_d2s(globalMacroLane_Sel, csrindex, readback_csr, mask);
        }
        if ((isCheck & 0x2) || (isCheck & 0x8)) {
            embed_check_CSR_into_d2s(globalMacroLane_Sel, csrindex, readback_csr, mask);
            csr_check_selectMacro_MB(globalMacroLane_Sel);
        }
    }
    //the_pre_d2s_jtag.set_address_synchronized_flag(getName() + "_CSR_CHECK" + prelane_title, csrindex);
}

void
HILINK_Regs_Base::embed_check_CSR_into_d2s(MACRO_LANE_SEL& MacroLane_Sel, int csrindex, uint readback_csr, uint mask) {
    if (hout.getLevel() & 0x8) {
        //hout(REG_ACCESS) << "embed auto CSR check " << getName() << " CSR(" << csrindex << ") readback = 0x" << hex << readback_csr << dec << endl;
    }


    uint backup_macroid = macroID, backup_sliceid = sliceID;
    bool backup_broadcast = broadcast;
    broadcast = 0;
    uint csr_value = readback_csr;
    int isCheck = 0; //the_jtag.isCheck();//通过用户设置的flag zdb
    vector<T_REG_INFO> reg_infos;
    map<string, uint> reg_map;
    if (isCheck & 0x4) {
        get_reg_infos(csrindex, reg_infos);
        for (uint i = 0; i < reg_infos.size(); i++) {
            uint mask = 0xffff;
            mask &= (HI_BIT_MASK[reg_infos[i].hi_bit]);
            mask &= (~LO_BIT_MASK[reg_infos[i].low_bit]);
            reg_map[reg_infos[i].reg_name] = mask;
        }
    }

    for (uint midx = 0; midx < MacroLane_Sel.size(); midx++) {
        uint MacroID = MacroLane_Sel[midx].MacroID;
        const vector<uint>& vLane = MacroLane_Sel[midx].vLane;

        if (globalMacroLane_Sel.size() > 0) {
            csr_check_selectMacro(MacroID);
        }
        macroID = MacroID;

        if (getType() == HILINK_PERMACRO_REGISTER) {
            int mAddr = getAddressMapToHiLink(csrindex);
            ostringstream str;
            //            str << getName() << "_M" << dec << macroID << "_Verify(" << dec << csrindex << ")";
            //            if (hout.getLevel() & 0x8) {
            //                //hout(REG_ACCESS) << "d2s CSR CHECK " << str.str() << " csr_value = 0x" << hex << csr_value << " mask = 0x" << hex << mask << dec << endl;
            //            }

            the_jtag.expectValue(mAddr >> 1, csr_value, mask, "", str.str());
            if (isCheck & 0x4) {
                for (map<string, uint>::iterator itr = reg_map.begin(); itr != reg_map.end(); itr++) {
                    the_jtag.add_CSR_Reg_Info(str.str(), itr->first, itr->second);
                }
            }

        } else if (getType() == HILINK_PERLANE_REGISTER) {
            if (isCheck & 0x8) {
                uint LaneID = vLane[0];
                sliceID = LaneID;
                int mAddr = getAddressMapToHiLink(csrindex);
                ostringstream str;
                //                str << getName() << "_M" << dec << macroID << "L" << dec << sliceID << "_Verify(" << dec << csrindex << ")";
                //
                //                if (hout.getLevel() & 0x8) {
                //                    //hout(REG_ACCESS) << "d2s CSR CHECK " << str.str() << " csr_value = 0x" << hex << csr_value << " mask = 0x" << hex << mask << dec << endl;
                //                }

                the_jtag.expectValue(mAddr >> 1, csr_value, mask, "", str.str());
                if (isCheck & 0x4) {
                    for (map<string, uint>::iterator itr = reg_map.begin(); itr != reg_map.end(); itr++) {
                        the_jtag.add_CSR_Reg_Info(str.str(), itr->first, itr->second);
                    }
                }
            } else {
                for (uint lidx = 0; lidx < vLane.size(); lidx++) {
                    uint LaneID = vLane[lidx];
                    sliceID = LaneID;
                    int mAddr = getAddressMapToHiLink(csrindex);
                    ostringstream str;
                    //                    str << getName() << "_M" << dec << macroID << "L" << dec << sliceID << "_Verify(" << dec << csrindex << ")";
                    //
                    //                    if (hout.getLevel() & 0x8) {
                    //                        //hout(REG_ACCESS) << "d2s CSR CHECK " << str.str() << " csr_value = 0x" << hex << csr_value << " mask = 0x" << hex << mask << dec << endl;
                    //                    }

                    the_jtag.expectValue(mAddr >> 1, csr_value, mask, "", str.str());
                    if (isCheck & 0x4) {
                        for (map<string, uint>::iterator itr = reg_map.begin(); itr != reg_map.end(); itr++) {
                            the_jtag.add_CSR_Reg_Info(str.str(), itr->first, itr->second);
                        }
                    }
                }
            }
        } else {
//            cerr << "Error: incorrect REGISTER TYPE!" << endl;
            //			ERROR_EXIT(TM::ABORT_FLOW);
        }
    }
    macroID = backup_macroid;
    sliceID = backup_sliceid;
    broadcast = backup_broadcast;
}

void
HILINK_Regs_Base::do_check_CSR_pre_d2s(MACRO_LANE_SEL& MacroLane_Sel, int csrindex, uint readback_csr, uint mask) {
    uint backup_macroid = macroID, backup_sliceid = sliceID;
    bool backup_broadcast = broadcast;
    broadcast = 0;
    uint csr_value = readback_csr;


    //the_pre_d2s_jtag.pre_d2s_begin();
    //the_pre_d2s_jtag.enablePassFailCheckForNextExecution();
    for (uint midx = 0; midx < MacroLane_Sel.size(); midx++) {
        uint MacroID = MacroLane_Sel[midx].MacroID;
        const vector<uint>& vLane = MacroLane_Sel[midx].vLane;

        pred2s_selectMacro(MacroID); //ZDB
        //selectMacro(MacroID);
        macroID = MacroID;

        if (getType() == HILINK_PERMACRO_REGISTER) {
            int mAddr = getAddressMapToHiLink(csrindex);
            ostringstream str;
            //            str << getName() << "_M" << dec << macroID << "_Verify(" << dec << csrindex << ")";
            //
            //            if (hout.getLevel() & 0x8) {
            //                //hout(REG_ACCESS) << "pre_d2s CSR CHECK " << str.str() << " csr_value = 0x" << hex << csr_value << " mask = 0x" << hex << mask << dec << endl;
            //            }

            the_pre_d2s_jtag.expectValue(mAddr >> 1, csr_value, mask, "", str.str());
        } else if (getType() == HILINK_PERLANE_REGISTER) {
            for (uint lidx = 0; lidx < vLane.size(); lidx++) {
                uint LaneID = vLane[lidx];
                sliceID = LaneID;
                int mAddr = getAddressMapToHiLink(csrindex);
                ostringstream str;
                //                str << getName() << "_M" << dec << macroID << "L" << dec << sliceID << "_Verify(" << dec << csrindex << ")";
                //
                //                if (hout.getLevel() & 0x8) {
                //                    //hout(REG_ACCESS) << "pre_d2s CSR CHECK " << str.str() << " csr_value = 0x" << hex << csr_value << " mask = 0x" << hex << mask << dec << endl;
                //                }

                the_pre_d2s_jtag.expectValue(mAddr >> 1, csr_value, mask, "", str.str());
            }
        } else {
//            cerr << "Error: incorrect REGISTER TYPE!" << endl;
            //ERROR_EXIT(TM::ABORT_FLOW);
        }
    }
    //the_pre_d2s_jtag.pre_d2s_end("pred2s_AUTOCSRCHECK_" + d2sFramework::get_current_prefix() + "_" + CSR_CHECK_PreFix + "_", true, true);

    //    bool allpass = true;
    //    map<int, bool> current_result;
    //    FOR_EACH_SITE_BEGIN();
    //    current_result[CURRENT_SITE_NUMBER()] = true;
    //    if (!GET_FUNCTIONAL_RESULT()) {
    //        allpass = false;
    //        current_result[CURRENT_SITE_NUMBER()] = false;
    //    }
    //    FOR_EACH_SITE_END();


    //    if (!allpass || !the_pre_d2s_jtag.isProductionMode()) {
    //        //the_pre_d2s_jtag.pre_d2s_begin();
    //        for (uint midx = 0; midx < MacroLane_Sel.size(); midx++) {
    //            uint MacroID = MacroLane_Sel[midx].MacroID;
    //            const vector<uint>& vLane = MacroLane_Sel[midx].vLane;
    //
    //            pred2s_selectMacro(MacroID);
    //            macroID = MacroID;
    //
    //            if (getType() == HILINK_PERMACRO_REGISTER) {
    //                int mAddr = getAddressMapToHiLink(csrindex);
    //                ostringstream str;
    //                str << getName() << "_M" << dec << MacroID << "_Verify(" << dec << csrindex << ")";
    //
    //                if (hout.getLevel() & 0x8) {
    //                    //hout(REG_ACCESS) << "pre_d2s CSR CHECK READ " << str.str() << " csr_value = 0x" << hex << csr_value << " mask = 0x" << hex << mask << dec << endl;
    //                }
    //
    //                the_pre_d2s_jtag.read(mAddr >> 1, str.str());
    //            } else if (getType() == HILINK_PERLANE_REGISTER) {
    //                for (uint lidx = 0; lidx < vLane.size(); lidx++) {
    //                    uint LaneID = vLane[lidx];
    //                    sliceID = LaneID;
    //                    int mAddr = getAddressMapToHiLink(csrindex);
    //                    ostringstream str;
    //                    str << getName() << "_M" << dec << MacroID << "L" << dec << LaneID << "_Verify(" << dec << csrindex << ")";
    //
    //                    if (hout.getLevel() & 0x8) {
    //                        //hout(REG_ACCESS) << "pre_d2s CSR CHECK READ " << str.str() << " csr_value = 0x" << hex << csr_value << " mask = 0x" << hex << mask << dec << endl;
    //                    }
    //                    the_pre_d2s_jtag.read(mAddr >> 1, str.str());
    //                }
    //            } else {
    //                cerr << "Error: incorrect REGISTER TYPE!" << endl;
    //                //ERROR_EXIT(TM::ABORT_FLOW);
    //            }
    //        }
    //        //the_pre_d2s_jtag.pre_d2s_end("pred2s_AUTOCSRCHECK_" + d2sFramework::get_current_prefix());
    //
    //        FOR_EACH_SITE_BEGIN();
    //        if (!current_result[CURRENT_SITE_NUMBER()] || !the_pre_d2s_jtag.isProductionMode()) {
    //            ostringstream dlg;
    //            if (!current_result[CURRENT_SITE_NUMBER()]) {
    //                dlg << "site" << CURRENT_SITE_NUMBER() << " " << getName() << " CSR(" << csrindex << ") CHECK ON Site" << CURRENT_SITE_NUMBER() << " FAIL" << endl;
    //            }
    //            vector<T_REG_INFO> reg_infos;
    //            get_reg_infos(csrindex, reg_infos);
    //            dlg << "site" << CURRENT_SITE_NUMBER() << " " << getName() << " Verify CSR(" << dec << csrindex << ")\t";
    //            for (uint i = 0; i < reg_infos.size(); i++) {
    //                dlg << reg_infos[i].reg_name << "[" << reg_infos[i].hi_bit << ":" << reg_infos[i].low_bit << "]\t";
    //            }
    //            dlg << endl;
    //            M_CSR_INFO csr_info;
    //
    //            for (uint midx = 0; midx < MacroLane_Sel.size(); midx++) {
    //                uint MacroID = MacroLane_Sel[midx].MacroID;
    //                const vector<uint>& vLane = MacroLane_Sel[midx].vLane;
    //
    //                if (getType() == HILINK_PERMACRO_REGISTER) {
    //                    ostringstream str;
    //                    str << getName() << "_M" << dec << MacroID << "_Verify(" << dec << csrindex << ")";
    //                    uint value = the_pre_d2s_jtag.getReadValue(str.str());
    //
    //                    dlg << "M" << MacroID << " : " << hex << "0x" << value << dec << "\t";
    //                    decodeCSR(csrindex, value, csr_info);
    //                    for (uint i = 0; i < reg_infos.size(); i++) {
    //                        int val = csr_info[reg_infos[i].reg_name];
    //                        dlg << dec << val << "(0x" << hex << val << dec << ")\t";
    //                    }
    //                    dlg << endl;
    //                } else if (getType() == HILINK_PERLANE_REGISTER) {
    //                    for (uint lidx = 0; lidx < vLane.size(); lidx++) {
    //                        uint LaneID = vLane[lidx];
    //
    //                        ostringstream str;
    //
    //                        str << getName() << "_M" << dec << MacroID << "L" << dec << LaneID << "_Verify(" << dec << csrindex << ")";
    //                        uint value = the_pre_d2s_jtag.getReadValue(str.str());
    //                        dlg << "M" << MacroID << "L" << LaneID << " : " << hex << "0x" << value << dec << "\t";
    //                        decodeCSR(csrindex, value, csr_info);
    //                        for (uint i = 0; i < reg_infos.size(); i++) {
    //                            int val = csr_info[reg_infos[i].reg_name];
    //                            dlg << dec << val << "(0x" << hex << val << dec << ")\t";
    //                        }
    //                        dlg << endl;
    //                    }
    //                } else {
    //                    cerr << "Error: incorrect REGISTER TYPE!" << endl;
    //                    ERROR_EXIT(TM::ABORT_FLOW);
    //                }
    //            }
    //            dlg << endl;
    //            cout << dlg.str() << endl;
    //            PUT_DATALOG(dlg.str());
    //        }
    //        FOR_EACH_SITE_END();
    //    }

    macroID = backup_macroid;
    sliceID = backup_sliceid;
    broadcast = backup_broadcast;

}

void
HILINK_Regs_Base::addSkipCheckCSR(uint csrindex) {
    if (csrindex < getCSRCount()) {

        the_pre_d2s_jtag.set_address_synchronized_flag(getName() + "_SKIP_CSR_CHECK", csrindex);
    } else {
//        cerr << "Error: " << getName() << " CSR" << csrindex << " is invalid!" << endl;
        //		ERROR_EXIT(TM::ABORT_FLOW);
    }
}

void
HILINK_Regs_Base::ReadAll2CSR() {
    vector<UINT> CSRs;
    T_MacroLaneID id;
    get_default_MacroLaneID(id);
    read_all_csr(id.MacroID, id.LaneID, CSRs);
    for (UINT i = 0; i < getCSRCount(); i++) {
        get_csr(i) = CSRs[i];
    }
    if (hout.getLevel() == DETAIL) {
        //hout(DETAIL) << "\n";
        //hout(DETAIL) << "*****************************************************************" << endl;
        //hout(DETAIL) << "********************** Read " << getName() << " All Regs **********************" << endl;
        //hout(DETAIL) << "*****************************************************************" << endl;
        for (UINT i = 0; i < getCSRCount(); i++) {
            DisplayAllSegmentOfCSR(i);
        }
    }
}

void
HILINK_Regs_Base::DisplayAllSegmentOfCSR(uint csrIndex) {
    /************** Log all segment value after read ******************/
    vector<T_REG_INFO> reg_infos;
    get_reg_infos(csrIndex, reg_infos);
    char csrstr[128];
    sprintf(csrstr, "---- %s CSR[%u]\tAddr = 0x%04x \t Data = 0x%04x ----\n", getName().c_str(), csrIndex, getAddressMapToHiLink(csrIndex), get_csr(csrIndex));
    //hout(DETAIL) << csrstr;
    //hout(DETAIL) << "-----------------------------------------------------------------\n";
    for (UINT j = 0; j < reg_infos.size(); j++) {
        UINT val = get_bits(get_csr(csrIndex), reg_infos[j]);
        char segstr[128];
        sprintf(segstr, "| %-32s CSR[bit %2u:%-2u] = 0x%04x(%3u) |\n", reg_infos[j].reg_name.c_str(), reg_infos[j].hi_bit, reg_infos[j].low_bit, val, val);
        //hout(DETAIL) << segstr;
    }
    //hout(DETAIL) << "-----------------------------------------------------------------\n";
}

void
HILINK_Regs_Base::dumpAllCSR(const MACRO_LANE_SEL& MacroLaneSel, ostringstream& str) {
    if (getType() == HILINK_PERMACRO_REGISTER) {
        dumpAllMacroCSR(MacroLaneSel, str);
    } else {
        dumpAllSliceCSR(MacroLaneSel, str);
    }
}

void
HILINK_Regs_Base::dumpAllCSR(const MACRO_LANE_SEL& MacroLaneSel ,const string& file_name) {
    if (getType() == HILINK_PERMACRO_REGISTER) {
        dumpAllMacroCSR(MacroLaneSel, file_name);
    } else {
        dumpAllSliceCSR(MacroLaneSel, file_name);
    }
}



void
HILINK_Regs_Base::dumpCSR(const uint& MacroID, const uint& LaneID, ostringstream& str) {
    if (getType() == HILINK_PERMACRO_REGISTER) {
        dumpMacroCSR(MacroID, 0, str);
    } else {
        dumpSliceCSR(MacroID, LaneID, str);
    }
}

void
HILINK_Regs_Base::dumpAllSliceCSR(const MACRO_LANE_SEL& MacroLaneSel, ostringstream& str) {
    map<uint, vector<uint> > CSRs;
    for (uint midx = 0; midx < MacroLaneSel.size(); midx++) {
        uint MacroID = MacroLaneSel[midx].MacroID;
        const vector<uint>& vLane = MacroLaneSel[midx].vLane;
        for (uint lidx = 0; lidx < vLane.size(); lidx++) {

            str << "******************** " << getName() << " ********************" << endl;

            string tmp;

            uint LaneID = vLane[lidx];
            read_all_csr(MacroID, LaneID, CSRs);
            //			FOR_EACH_SITE_BEGIN();
            //				uint SiteID=CURRENT_SITE_NUMBER()-1;
            //				str<<"--------------- Site: "<<SiteID<<" MacroID: "<<MacroID<<"\t SliceID: "<<LaneID<<"---------------"<<endl;
            //				for(uint i=0;i<getCSRCount();i++){
            //					tmp=getCSRInfoString(i,CSRs[SiteID][i]);
            //					if(!tmp.empty()){
            //						str<<tmp<<endl;
            //					}
            //				}
            //				str<<"--------------------------------------------------------"<<endl<<endl;
            //			FOR_EACH_SITE_END();
        }
    }
}

void
HILINK_Regs_Base::dumpAllSliceCSR(const MACRO_LANE_SEL& MacroLaneSel,const string& file_name) {
    map<uint, vector<uint> > CSRs;
    
    ostringstream str;
    str << "******************** " << getName() << " ********************" << endl;
    
    for (uint midx = 0; midx < MacroLaneSel.size(); midx++) {
        uint MacroID = MacroLaneSel[midx].MacroID;
        const vector<uint>& vLane = MacroLaneSel[midx].vLane;
//        const vector<uint>& vLane = getRelativeLanes(MacrolLaneSel[midx]);
        for (uint lidx = 0; lidx < vLane.size(); lidx++) {
            string tmp="";
            uint LaneID = vLane[lidx];
            read_all_csr(MacroID, LaneID, CSRs);
//            FOREACH_ACTIVE_SITE(api) {
//                    unsigned int SiteID = api->Get_active_site();
                    FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

                        str<<"--------------- Site: "<<SiteID<<" MacroID: "<<MacroID<<"\t SliceID: "<<LaneID<<"---------------"<<endl;
                        for(uint i=0;i<getCSRCount();i++){
                                tmp=getCSRInfoString(i,CSRs[SiteID][i]);
                                if(!tmp.empty()){
                                        str<<tmp<<endl;
                                }
                        }
                        str<<"--------------------------------------------------------"<<endl<<endl;
                        FOREACH_ACTIVESITE_END
        }
    }
    if(file_name.empty()){
        printf("%-10s\n",str.str().c_str());
    }
    else{
        ostringstream File_name;
//        const char* devpath;
//        devpath = api->Get_program_path();
        string devpath = TheSoft.GetProgramPath();
        devpath = "E:\\wenxinyu\\git-workspace";
        
        File_name<<devpath<<"\\report\\"<<file_name<<"_"<<getName()<<".log";
        
        ofstream csrfile;
        csrfile.open(File_name.str().c_str(),ios::binary);
        csrfile<<str.str()<<endl;
        csrfile.close();
    }
}

void
HILINK_Regs_Base::dumpSliceCSR(const uint& MacroID, const uint& LaneID, ostringstream& str) {
    map<uint, vector<uint> > CSRs;
    str << "******************** " << getName() << " ********************" << endl;
    string tmp;
    read_all_csr(MacroID, LaneID, CSRs);
    //	FOR_EACH_SITE_BEGIN();
    //		uint SiteID=CURRENT_SITE_NUMBER()-1;
    //		str<<"--------------- Site: "<<SiteID<<" MacroID: "<<MacroID<<"\t SliceID: "<<LaneID<<"---------------"<<endl;
    //		for(uint i=0;i<getCSRCount();i++){
    //			tmp=getCSRInfoString(i,CSRs[SiteID][i]);
    //			if(!tmp.empty()){
    //				str<<tmp<<endl;
    //			}
    //		}
    //		str<<"--------------------------------------------------------"<<endl<<endl;
    //	FOR_EACH_SITE_END();


}

void
HILINK_Regs_Base::dumpAllMacroCSR(const MACRO_LANE_SEL& MacroLaneSel, ostringstream& str) {
    map<uint, vector<uint> > CSRs;
    for (uint midx = 0; midx < MacroLaneSel.size(); midx++) {
        uint MacroID = MacroLaneSel[midx].MacroID;
        uint SliceID = MacroLaneSel[midx].SliceID;
        read_all_csr(MacroID, SliceID, CSRs);
        str << "******************** " << getName() << " ********************" << endl;
        string tmp;
        //		FOR_EACH_SITE_BEGIN();
        //			uint SiteID=CURRENT_SITE_NUMBER()-1;
        //			str<<"--------------- Site: "<<SiteID<<" MacroID: "<<MacroID<<"\t SliceID: "<<SliceID<<"---------------"<<endl;
        //			for(uint i=0;i<getCSRCount();i++){
        //				tmp=getCSRInfoString(i,CSRs[SiteID][i]);
        //				if(!tmp.empty()){
        //					str<<tmp<<endl;
        //				}
        //			}
        //			str<<"--------------------------------------------------------"<<endl<<endl;
        //		FOR_EACH_SITE_END();

    }

}

void
HILINK_Regs_Base::dumpAllMacroCSR(const MACRO_LANE_SEL& MacroLaneSel,const string& file_name) {
    map<uint, vector<uint> > CSRs;
    
    ostringstream str;
    str << "******************** " << getName() << " ********************" << endl;
    string tmp="";
    for (uint midx = 0; midx < MacroLaneSel.size(); midx++) {
        uint MacroID = MacroLaneSel[midx].MacroID;
        uint SliceID = MacroLaneSel[midx].SliceID;
        read_all_csr(MacroID, SliceID, CSRs);
        
//        FOREACH_ACTIVE_SITE(api) {
//                unsigned int SiteID = api->Get_active_site();
                FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
                str<<"--------------- Site: "<<SiteID<<" MacroID: "<<MacroID<<"\t SliceID: "<<SliceID<<"---------------"<<endl;
                for(uint i=0;i<getCSRCount();i++){
                        tmp=getCSRInfoString(i,CSRs[SiteID][i]);
                        if(!tmp.empty()){
                                str<<tmp<<endl;
                        }
                }
                str<<"--------------------------------------------------------"<<endl<<endl;
                FOREACH_ACTIVESITE_END

    }
    if(file_name.empty()){
        printf("%-10s\n",str.str().c_str());
    }
    else{
        ostringstream File_name;
//        const char* devpath;
//        devpath = api->Get_program_path();
        string devpath = TheSoft.GetProgramPath();
        devpath = "E:\\wenxinyu\\git-workspace";
        
        File_name<<devpath<<"\\report\\"<<file_name<<"_"<<getName()<<".log";
//        printf("%-20s\n",File_name.str().c_str());
        
//        string File_name = string("E:\\wenxinyu\\git-workspace\\report\\123.log");
        ofstream csrfile;
        csrfile.open(File_name.str().c_str(),ios::binary);
        csrfile<<str.str()<<endl;
        csrfile.close();
    }

}

void
HILINK_Regs_Base::dumpMacroCSR(const uint& MacroID, const uint& SliceID, ostringstream& str) {
    map<uint, vector<uint> > CSRs;
    read_all_csr(MacroID, SliceID, CSRs);
    str << "******************** " << getName() << " ********************" << endl;
    string tmp;
    //	FOR_EACH_SITE_BEGIN();
    //		uint SiteID=CURRENT_SITE_NUMBER()-1;
    //		str<<"--------------- Site: "<<SiteID<<" MacroID: "<<MacroID<<"\t SliceID: "<<SliceID<<"---------------"<<endl;
    //		for(uint i=0;i<getCSRCount();i++){
    //			tmp=getCSRInfoString(i,CSRs[SiteID][i]);
    //			if(!tmp.empty()){
    //				str<<tmp<<endl;
    //			}
    //		}
    //		str<<"--------------------------------------------------------"<<endl<<endl;
    //	FOR_EACH_SITE_END();



}

void
HILINK_Regs_Base::skip_CSR_Sync() {

    the_pre_d2s_jtag.set_address_synchronized_flag(getName() + "_SKIP_CSR_SYNC_ALL", 0);
}

void
HILINK_Regs_Base::skip_CSR_Check() {

    the_pre_d2s_jtag.set_address_synchronized_flag(getName() + "_SKIP_CSR_CHECK_ALL", 0);
}

