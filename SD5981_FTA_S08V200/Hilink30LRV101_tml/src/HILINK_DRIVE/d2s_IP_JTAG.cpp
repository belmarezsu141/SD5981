/*
 * d2s_IP_JTAG.cpp
 *
 *  Created on: Jun 13, 2016
 *      Author: yanfen.fang
 */

#include <HILINK_DRIVE/d2s_IP_JTAG.h>

#include <iostream>
#include <sstream>
#include <set>
using namespace std;
bool PrintDebugEn= false; //add by tony 20211009
bool PrintFWDetailLogEn= false;
d2sWorkModeType Global_D2S_Mode= ProductionMode;  ////ProductionMode//LearningMode

#undef __debug__

const INT d2s_IP_JTAG::HilinkDR2AddrLength = 17;
const INT d2s_IP_JTAG::HilinkDR2DataLength = 16;
const string d2s_IP_JTAG::CONTEXT_POSTFIX_MAP[2] = {"_STD", "_FASTDIFF"};
const string d2s_IP_JTAG::JTAG_MODE_MAP[10]={	"writeDR2","writeDR1","writeDR0",
                                                "writeIR2","writeIR1","writeIR0",
                                                "read","wait",
                                                "write_DR","write_IR"
                                        };
d2s_IP_JTAG::d2s_IP_JTAG() : d2s() {
    JTAG_id = 0;
}

map<string, set<int> > d2s_IP_JTAG::synchronized_address;
d2sFrameWorkModeType::Enum d2s_IP_JTAG::exchg_d2smode = d2sFrameWorkModeType::DefaultMode;
bool d2s_IP_JTAG::exchg_ind2sblock = false;
int d2s_IP_JTAG::JTAG_id = 0;

void
d2s_IP_JTAG::init_val(int id) {
    //	portName=JTAG_PORT_CONFIG[id].port_name;
    //	JTAG_id=id;
    //	cycleOffset=0;
    //	label_md5_tag.clear();
    //	label_md5_tag.reserve(16*1024);
    //	burst_md5_tag="";
    //	burstLabels.clear();
    //	inD2sBlock=false;
    //	checkPassFail=false;
    //	LabelPassFailMap.clear();
    //	LabelPassFailResult.clear();
    //	call_id=0;
    //	Context="";
    //	jtag_mode=JTAG_WR_DR2;
    //	context=CTX_DEFAULT;
    //	template_selector=0;
    //	check_csr=false;
    //
    //	#ifdef AHB_MODE
    //		readid_macroid_map.clear();
    //		read_template_postfix="";
    //	#endif
    //
    //	IR_cycles=getJtagPatternCycleByTDILength(JTAG_PORT_CONFIG[id].HilinkIRLength);
    //	DR0_cycles=getJtagPatternCycleByTDILength(JTAG_PORT_CONFIG[id].HilinkDR0Length);
    //	DR1_cycles=getJtagPatternCycleByTDILength(JTAG_PORT_CONFIG[id].HilinkDR1Length);
    //	DR2_cycles=getJtagPatternCycleByTDILength(1+HilinkDR2AddrLength+HilinkDR2DataLength+1,JTAG_DR2_ENTRY_DUMMY_CYCLE);


}

d2s_IP_JTAG::d2s_IP_JTAG(int id, bool pre_d2s) : d2s(pre_d2s) {
    init_val(id);
}

d2s_IP_JTAG::d2s_IP_JTAG(const std::string& pName) : d2s() {
    init_val(0);
}

d2s_IP_JTAG::~d2s_IP_JTAG() {
    // TODO Auto-generated destructor stub
}

//void
//d2s_IP_JTAG::getContext(){
//	string answer;
//	FW_TASK("GCTX? CURR,",answer);
//	Context = answer.substr(12,answer.size()-14);
////	Context = "FASTDIFF";
//	if(Context == "")
//	{
//		Context = "DEFAULT";
//	}
//	if (Context == "DEFAULT")
//	{
//		context = CTX_DEFAULT;
//	}
//	else if  (Context == "FASTDIFF")
//	{
//		context = CTX_FASTDIFF;
//	}
//}

void
d2s_IP_JTAG::setJtagMode(const string& mode) {
	if(mode=="writeIR0"){jtag_mode=JTAG_WR_IR0;return;}
	if(mode=="writeDR0"){jtag_mode=JTAG_WR_DR0;return;}
	if(mode=="writeIR1"){jtag_mode=JTAG_WR_IR1;return;}
	if(mode=="writeDR1"){jtag_mode=JTAG_WR_DR1;return;}
	if(mode=="writeIR2"){jtag_mode=JTAG_WR_IR2;return;}
	if(mode=="writeDR2"){jtag_mode=JTAG_WR_DR2;return;}
	jtag_mode=JTAG_WR_DR2;
}

#ifdef AHB_MODE

void
d2s_IP_JTAG::readAndStoreValues(const std::string& id, int offset) {
    if (readid_macroid_map.find(id) != readid_macroid_map.end()) {
        setmacroid(readid_macroid_map[id]);
    } else {
//        cerr << "Error: No ID:" << id << endl;
    }
    d2s_Serial::readAndStoreValues(id, offset);
}
#endif

void
d2s_IP_JTAG::setmacroid(int macroidvar) {
    if (macroid != macroidvar) {
        macroid = macroidvar;
        //readCycleMapInitialized = 0;
    }
}

std::string
d2s_IP_JTAG::getInterfaceName() {
#ifndef AHB_MODE
	 switch(jtag_mode){
     case JTAG_WR_IR2:
    	 return "JTAG_WR_IR2_";
     case JTAG_WR_IR1:
    	 return "JTAG_WR_IR1_";
     case JTAG_WR_IR0:
    	 return "JTAG_WR_IR0_";
     case JTAG_WR_DR0:
    	 return "JTAG_WR_DR0_";
     case JTAG_WR_DR1:
    	 return "JTAG_WR_DR1_";
     case JTAG_WR_DR2:
    	 return "JTAG_WR_DR2_";
     default:
//                    cerr<<"Error: JTAG MODE is not set!"<<endl;
             //ABORT_TEST();
    	 return "JTAG_"; //+JTAG_MODE_MAP[jtag_mode]+CONTEXT_POSTFIX_MAP[context]

	 }
#else
    string tmp = "AHB_";
    //tmp+=JTAG_MODE_MAP[jtag_mode]+CONTEXT_POSTFIX_MAP[context]+read_template_postfix;
    return tmp;
#endif
}

int
d2s_IP_JTAG::getAddressBits() {

    int length=0;
    switch(jtag_mode){
            case JTAG_WR_IR2:
            case JTAG_WR_IR1:
            case JTAG_WR_IR0:
                    length= JTAG_PORT_CONFIG[JTAG_id].HilinkIRLength;
                    break;
            case JTAG_WR_DR0:
                    length= JTAG_PORT_CONFIG[JTAG_id].HilinkDR0Length;
                    break;
            case JTAG_WR_DR1:
                    length= JTAG_PORT_CONFIG[JTAG_id].HilinkDR1Length;
                    break;
            case JTAG_WR_DR2:
                    return HilinkDR2AddrLength;
            default:
//                    cerr<<"Error: JTAG MODE is not set!"<<endl;
                    //ABORT_TEST();
                    return 0;
    };
    return length>32?length-32:0;

}

int
d2s_IP_JTAG::getDataBits() {

    int length=0;
    switch(jtag_mode){
            case JTAG_WR_IR2:
            case JTAG_WR_IR1:
            case JTAG_WR_IR0:
                    length= JTAG_PORT_CONFIG[JTAG_id].HilinkIRLength;
                    if(length>HILINK_MAX_IRLength_NUM){
//                            cerr<<"Error: IRx Length: "<<length<<" is not available in JTAG_PORT_CONFIG[] of userconfig!"<<endl;
//                            ERROR_EXIT(TM::ABORT_FLOW);
                    }
                    break;
            case JTAG_WR_DR0:
                    length= JTAG_PORT_CONFIG[JTAG_id].HilinkDR0Length;
                    if(length>HILINK_MAX_DRxLength_NUM){
//                            cerr<<"Error: DR0 Length: "<<length<<" is not available in JTAG_PORT_CONFIG[] of userconfig!"<<endl;
//                            ERROR_EXIT(TM::ABORT_FLOW);
                    }
                    break;
            case JTAG_WR_DR1:
                    length= JTAG_PORT_CONFIG[JTAG_id].HilinkDR1Length;
                    if(length>HILINK_MAX_DRxLength_NUM){
//                            cerr<<"Error: DR1 Length: "<<length<<" is not available in JTAG_PORT_CONFIG[] of userconfig!"<<endl;
//                            ERROR_EXIT(TM::ABORT_FLOW);
                    }
                    break;
            case JTAG_WR_DR2:
                    return HilinkDR2DataLength;
            default:
//                    cerr<<"Error: JTAG MODE is not set!"<<endl;
//                    ABORT_TEST();
                    return 0;
    };
    return length>32?32:length;
    
}




//int d2s_IP_JTAG::IR1_cycles = 0;
//int d2s_IP_JTAG::IR2_cycles = 0;
//int d2s_IP_JTAG::SDR1_cycles = 0;
//int d2s_IP_JTAG::SDR2_cycles = 0;
//int d2s_IP_JTAG::SDR3_END_cycles = 0;
//int d2s_IP_JTAG::SDR4_END_cycles = 0;
//int d2s_IP_JTAG::SDR_Head_64BIT_Length = 0;
//int d2s_IP_JTAG::SDR_Body_64BIT_Length = 0;
//int d2s_IP_JTAG::DR2_cycles = 0;

int
d2s_IP_JTAG::getHighWaveformIndex() {
    return JTAG_INPUT_HIGH;
}

int
d2s_IP_JTAG::getLowWaveformIndex() {
    return JTAG_INPUT_LOW;
}

int
d2s_IP_JTAG::getHighStrobeWaveformIndex() {
    return JTAG_OUTPUT_HIGH;
}

int
d2s_IP_JTAG::getLowStrobeWaveformIndex() {
    return JTAG_OUTPUT_LOW;
}

int
d2s_IP_JTAG::getMaskStrobeWaveformIndex() {
#ifndef AHB_MODE
    return JTAG_OUTPUT_MASK;
#else
    return AHB_OUTPUT_MASK;
#endif
}

int
d2s_IP_JTAG::getWriteCycles() {

    int cycle = 0;
    //    switch (jtag_mode) {
    //        case JTAG_WR_DR2:
    //            cycle = DR2_cycles;
    //            break;
    //        case JTAG_WR_IR1:
    //            cycle = IR1_cycles;
    //            break;
    //            break;
    //        case JTAG_WR_IR2:
    //            cycle = IR2_cycles;
    //            break;
    //            break;
    //        case JTAG_WR_SDR1:
    //            cycle = SDR1_cycles;
    //            break;
    //            break;
    //        case JTAG_WR_SDR2:
    //            cycle = SDR2_cycles;
    //            break;
    //            break;
    //        case writeSDR_HEAD:
    //            cycle = SDR_Head_64BIT_Length;
    //            break;
    //            break;
    //        case writeSDR_BODY:
    //            cycle = SDR_Body_64BIT_Length;
    //            break;
    //            break;
    //        case writeSDR3_END:
    //            cycle = SDR3_END_cycles;
    //            break;
    //            break;
    //        case writeSDR4_END:
    //            cycle = SDR4_END_cycles;
    //            break;
    //            break;
    //        default:
//                cerr << "this value should be cached: " << jtag_mode << "  :  " << PatternManager::getCyclesFromLabel(getWriteTemplatePatternName(), portName) << endl;
    //            return PatternManager::getCyclesFromLabel(getWriteTemplatePatternName(), portName);
    //    }
    return cycle;

}

std::string
d2s_IP_JTAG::getWriteTemplatePatternName() {
    
    //int d2s_template_id=0;
	string temp_test = "";
    switch(jtag_mode){
            case JTAG_WR_IR0:
	            temp_test = "d2s_JTAG_writeIR0_template_STD_h30";
	            break;							
            case JTAG_WR_DR0:
	            temp_test = "d2s_JTAG_writeDR0_template_STD_h30";
	            break;				
            case JTAG_WR_IR1:
	            temp_test = "d2s_JTAG_writeIR1_template_STD_h30";
	            break;				
            case JTAG_WR_DR1:
	            temp_test = "d2s_JTAG_writeDR1_template_STD_h30";
	            break;				
            case JTAG_WR_IR2:
	            temp_test = "d2s_JTAG_writeIR2_template_STD_h30";
	            break;				
            case JTAG_WR_DR2:
                    //d2s_template_id=jtag_mode;
                    //break;
	            temp_test = "d2s_JTAG_writeDR2_template_STD_h30";
	            break;						
            default:
                    //d2s_template_id=JTAG_WR_DR;
                    //break;
	            cerr << "Error: JTAG MODE is not set!" << endl;
	            //ABORT_TEST();
	            return "";					
    }
    //return JTAG_PORT_CONFIG[JTAG_id].d2s_template[d2s_template_id]+CONTEXT_POSTFIX_MAP[context];
	return temp_test;

}

std::string
d2s_IP_JTAG::getWritePinName() {
    return JTAG_PORT_CONFIG[JTAG_id].tdi_pin;
}

int
d2s_IP_JTAG::getWriteAddressVectorNumberLSB() {

    int length=0;
    switch(jtag_mode){
            case JTAG_WR_IR0:
            case JTAG_WR_IR1:
            case JTAG_WR_IR2:
                    length=JTAG_PORT_CONFIG[JTAG_id].HilinkIRLength;
                    break;
            case JTAG_WR_DR0:
                    length=JTAG_PORT_CONFIG[JTAG_id].HilinkDR0Length;
                    break;
            case JTAG_WR_DR1:
                    length=JTAG_PORT_CONFIG[JTAG_id].HilinkDR1Length;
                    break;
            case JTAG_WR_DR2:
                    return HilinkDR2DataLength + 8;
            default:
                    return 0;
                    break;
    }
    return length>32?40:length+8;
    
}

int
d2s_IP_JTAG::getWriteAddressVectorNumberMSB() {

    int length=0;
    switch(jtag_mode){
            case JTAG_WR_IR0:
            case JTAG_WR_IR1:
            case JTAG_WR_IR2:
                    length=JTAG_PORT_CONFIG[JTAG_id].HilinkIRLength;
                    break;
            case JTAG_WR_DR0:
                    length=JTAG_PORT_CONFIG[JTAG_id].HilinkDR0Length;
                    break;
            case JTAG_WR_DR1:
                    length=JTAG_PORT_CONFIG[JTAG_id].HilinkDR1Length;
                    break;
            case JTAG_WR_DR2:
                    return HilinkDR2DataLength + HilinkDR2AddrLength + 7;
            default:
                    return 0;
                    break;
    }
    return length>32?length+7:length+8;

}

int
d2s_IP_JTAG::getWriteDataVectorNumberLSB() {

    return 8;

}

int
d2s_IP_JTAG::getWriteDataVectorNumberMSB() {

    int length=0;
    switch(jtag_mode){
            case JTAG_WR_IR0:
            case JTAG_WR_IR1:
            case JTAG_WR_IR2:
                    length=JTAG_PORT_CONFIG[JTAG_id].HilinkIRLength;
                    break;
            case JTAG_WR_DR0:
                    length=JTAG_PORT_CONFIG[JTAG_id].HilinkDR0Length;
                    break;
            case JTAG_WR_DR1:
                    length=JTAG_PORT_CONFIG[JTAG_id].HilinkDR1Length;
                    break;
            case JTAG_WR_DR2:
                    return HilinkDR2DataLength + 7;
            default:
                    return 0;
                    break;
    }
    return length>32?39:length+7;


}

std::string
d2s_IP_JTAG::getReadTemplatePatternName() {
    return  "d2s_JTAG_read_template_STD";
    //return JTAG_PORT_CONFIG[JTAG_id].d2s_template[JTAG_RD] + CONTEXT_POSTFIX_MAP[context];

}

std::string
d2s_IP_JTAG::getReadAddressPinName() {
    return JTAG_PORT_CONFIG[JTAG_id].tdi_pin;
}

std::string
d2s_IP_JTAG::getReadPinName() {

    return JTAG_PORT_CONFIG[JTAG_id].tdo_pin;

}

//int d2s_IP_JTAG::getReadCycles() {
//
//    return JTAG_READ_PATTERN_CYCLE;
//
//}

int d2s_IP_JTAG::getReadAddressVectorNumberLSB() {
    return JTAG_READ_ADDR_LSB_CYCLE;
}

int d2s_IP_JTAG::getReadAddressVectorNumberMSB() {
    return JTAG_READ_ADDR_MSB_CYCLE;
}

int d2s_IP_JTAG::getReadDataCycleNumberLSB() {
    return JTAG_READ_DATA_LSB_CYCLE;
}

int d2s_IP_JTAG::getReadDataCycleNumberMSB() {
    return JTAG_READ_DATA_MSB_CYCLE;
}

int d2s_IP_JTAG::getReadDataVectorNumberLSB() {
    return JTAG_READ_DATA_LSB_CYCLE;
}

int d2s_IP_JTAG::getReadDataVectorNumberMSB() {
    return JTAG_READ_DATA_MSB_CYCLE;
}


int d2s_IP_JTAG::getExpectAddressVectorNumberLSB() {
    return JTAG_EXPECT_ADDR_LSB_CYCLE;
}

int d2s_IP_JTAG::getExpectAddressVectorNumberMSB() {
    return JTAG_EXPECT_ADDR_MSB_CYCLE;
}

/*int d2s_IP_JTAG::getExpectDataCycleNumberLSB() {
    return JTAG_EXPECT_DATA_LSB_CYCLE;
}*/

/*int d2s_IP_JTAG::getExpectDataCycleNumberMSB() {
    return JTAG_EXPECT_DATA_MSB_CYCLE;
}*/

int d2s_IP_JTAG::getExpectDataVectorNumberLSB() {
    return JTAG_EXPECT_DATA_LSB_CYCLE;
}

int d2s_IP_JTAG::getExpectDataVectorNumberMSB() {
    return JTAG_EXPECT_DATA_MSB_CYCLE;
}
//std::string getExpectTemplatePatternName();
std::string d2s_IP_JTAG::getExpectTemplatePatternName() {
	return "d2s_JTAG_expect_template";

   //eturn JTAG_PORT_CONFIG[JTAG_id].d2s_template[JTAG_EP] + CONTEXT_POSTFIX_MAP[context];

}

int d2s_IP_JTAG::getExpectPatternVectors() {
    return 96;
}
std::string d2s_IP_JTAG::getExpectAddressPinName() {
    return JTAG_PORT_CONFIG[JTAG_id].tdi_pin;
}

std::string d2s_IP_JTAG::getExpectPinName() {

    return JTAG_PORT_CONFIG[JTAG_id].tdo_pin;

}


//std::string
//d2s_IP_JTAG::getTimingPort() {
//    return JTAG_PORT_CONFIG[JTAG_id].port_name;
//}

void
d2s_IP_JTAG::expectValue(long long address, long long value, long long mask, const string& id, const string& label) {
    d2s::expectValue(address, value, mask);
    //	if(!label.empty()){
    //		static int isCheck=0;
    //		static bool is_flow_variable_exists=true;
    //		if(is_flow_variable_exists){
    //			try{
    //				//GET_USER_FLAG("CSR_atomic_operation",&isCheck);
    //			}
    //			catch(...){
    //				is_flow_variable_exists=false;
    //				isCheck=0;
    //			}
    //		}
    //		if((isCheck&0x2)||(isCheck&0x8)){
    //			T_HILINK_JTAG_CSR_CHECK_CYCLE_INFO tmp={label,cycleOffset,macroid};
    //			csr_check_cycle_info.push_back(tmp);
    //		}
    //	}
    //#ifndef AHB_MODE
    //	if(!label.empty()){
    //		d2s_Serial::expectValue(address,value,mask,label);
    //	}
    //	else{
    //		unsigned long long label_code=0xDB30000000000000LL;
    //		label_code |= ( (unsigned long long)(address & 0x3ffff) << 32 );
    //		label_code |= ( (unsigned long long)(value & 0xffff) << 16 );
    //		label_code |= ( mask & 0xffff );
    //
    //		d2s_Serial::expectValue_label_code(address,value,mask,&label_code);
    //	}
    //#else
    //	if(macroid==0){
    //		read_template_postfix="_"+AHB_MACRO0_NAME;
    //	}
    //	else{
    //		read_template_postfix="_"+AHB_MACRO1_NAME;
    //	}
    //
    //	if(!label.empty()){
    //		d2s_Serial::expectValue(address,value,mask,label);
    //	}
    //	else{
    //
    //		unsigned long long label_code=0xDB30000000000000LL;
    //		label_code |= ( (unsigned long long)(address & 0x3ffff) << 32 );
    //		label_code |= ( (unsigned long long)(value & 0xffff) << 16 );
    //		label_code |= ( mask & 0xffff );
    //
    //		if(macroid==1){
    //			label_code |= 0x0008000000000000LL;
    //		}
    //
    //		d2s_Serial::expectValue_label_code(address,value,mask,&label_code);
    //	}
    //	read_template_postfix="";
    //#endif
}

void
d2s_IP_JTAG::preExec(const std::string& burstName) {
    //	if(!isProductionMode() && burstLabels.size() == 0){
    //		cerr<<"Error burst \""<< d2sFramework::get_current_prefix() <<"\" is empty!"<<endl;
    //	//	ERROR_EXIT(TM::ABORT_FLOW);
    //	}
    //	d2s_Serial::preExec(burstName);

    //	static string lastTestSuiteName = "";
    //	string testSuiteName;
    //	GET_TESTSUITE_NAME(testSuiteName);
    //	if(lastTestSuiteName != testSuiteName){
    //		lastTestSuiteName = testSuiteName;
    //		CSR_Check_result.clear();
    //		FOR_EACH_SITE_BEGIN();
    //			CSR_Check_result[CURRENT_SITE_NUMBER()]=true;
    //		FOR_EACH_SITE_END();
    //	}

}

//map<int,bool> d2s_IP_JTAG::CSR_Check_result;

//void
//d2s_IP_JTAG::display_fail_registers(const string& csr_check_id,uint fail_code){
//	assert(fail_code != 0);
//	M_CSR_REG_INFO::iterator csr_itr=CSR_Check_Info.find(csr_check_id);
//	if(csr_itr != CSR_Check_Info.end()){
//		cout<<" fail resgiters: "<<endl;
//		map<string,uint>& map_reg=csr_itr->second;
//		for(map<string,uint>::iterator itr=map_reg.begin();itr!=map_reg.end();itr++){
//			if(itr->second & fail_code){
////				cout<<"\t"<<itr->first<<" bits[0x"<<setfill('0')<<setw(4)<<right<<hex<<itr->second<<dec<<"]"<<endl;
//			}
//		}
//	}
//	cout<<endl;
//}

void
d2s_IP_JTAG::postExec(const std::string& executedId, bool executionWasSuccessful) {
    //	static int isCheck=0;
    //	static bool is_flow_variable_exists=true;
    //	if(is_flow_variable_exists){
    //		try{
    //	//		GET_USER_FLAG("CSR_atomic_operation",&isCheck);
    //		}
    //		catch(...){
    //			is_flow_variable_exists=false;
    //			isCheck=0;
    //		}
    //	}
    //	if(readOffsets.size()>0 && (isCheck & 0x2) && check_csr){
    //		cerr<<"Error:"<<d2sFramework::get_current_prefix()<<" EMBEDED AUTO CSR CHECK and read can not work together!"<<endl;
    //	//	ERROR_EXIT(TM::ABORT_FLOW);
    //	}
    //
    //	d2s_Serial::postExec(executedId,executionWasSuccessful);
    //
    //	if((isCheck & 0x2)&& check_csr){
    //		store query focus
    //		string prevSite;
    ////		fwout << "PQFC?" << endl;
    ////		prevSite = fwresult[0][0];
    ////#ifdef __debug__
    ////		cout << prevSite << endl;
    ////#endif
    ////		FOR_EACH_SITE_BEGIN();
    ////			int site=CURRENT_SITE_NUMBER();
    ////            bool passFail = false;
    ////            if(executionWasSuccessful){
    ////				fwout << "PQFC " << site << endl;
    ////				fwout << "PASS? (" << portName << ")" << endl; //would checking global pass/fail (for all ports) first be faster? [PRLT?]
    ////				passFail = (fwresult[0][0]=="P")?true:false;
    ////            }
    ////            else{
    ////            	passFail = false;
    ////            }
    ////			CSR_Check_result[site] = (CSR_Check_result[site] && passFail);
    ////
    ////			if(!passFail){	//debug
    ////				cout<<"Error: Embedded CSR CHECK result site"<<site<<" FAIL"<<endl;
    ////				string sn;
    //////				GET_TESTSUITE_NAME(sn);
    ////				cout<<"suitename = "<<sn<<"\n d2s-block:"<<d2sFramework::get_current_prefix()<<" Embedded CSR CHECK information (1 means bit fail): "<<endl;
    ////				for(uint j=0;j<csr_check_cycle_info.size();j++){

    ////					d2s_Serial::readAndStoreValues(csr_check_cycle_info[j].csr_check_id,csr_check_cycle_info[j].cycle);
    ////
    ////					uint val=(uint)readIdValues[portName][site][csr_check_cycle_info[j].csr_check_id];
    ////
    ////					if(val){
    ////						cout<<"site"<<site<<" "<<csr_check_cycle_info[j].csr_check_id<<" = 0x"<<setfill('0')<<setw(4)<<right<<hex<<val<<dec;
    ////						if(isCheck & 0x4){
    ////							display_fail_registers(csr_check_cycle_info[j].csr_check_id,val);
    ////						}
    ////						else{
    ////							cout<<endl;
    ////						}
    ////					}
    ////				}
    ////			}
    //
    ////		FOR_EACH_SITE_END();
    //
    //        //restore query focus
    ////        fwout << "PQFC " << prevSite << endl;
    //	}
    //	check_csr=false;
}

int d2s_IP_JTAG::isCheck() {
    return isCSRCheck;
}

bool
d2s_IP_JTAG::has_CSR_Check_Passed() {
    int site; //=CURRENT_SITE_NUMBER();
    //return CSR_Check_result[site];
}

void
d2s_IP_JTAG::add_CSR_Reg_Info(const string& csr_check_id, const string& regname, uint reg_mask) {
    assert(reg_mask != 0);
    //	M_CSR_REG_INFO::iterator csr_itr=CSR_Check_Info.find(csr_check_id);
    //	if(csr_itr == CSR_Check_Info.end()){
    //		CSR_Check_Info[csr_check_id][regname]=reg_mask;
    //	}
    //	else{
    //		map<string,uint>& map_reg=csr_itr->second;
    //		map<string,uint>::iterator reg_itr=map_reg.find(regname);
    //		if(reg_itr == map_reg.end()){
    //			map_reg[regname]=reg_mask;
    //		}
    //	}
}

void
d2s_IP_JTAG::enableCSRCheckForNextExecution() {
    //	if(checkPassFail){
    //		cerr<<"Error:"<<d2sFramework::get_current_prefix()<<" EMBEDED AUTO CSR CHECK and expectValue can not work together!"<<endl;
    //	//	ERROR_EXIT(TM::ABORT_FLOW);
    //	}
    check_csr = true;
}

void
d2s_IP_JTAG::enablePassFailCheckForNextExecution() {
    //	if(check_csr){
    //		cerr<<"Error: "<<d2sFramework::get_current_prefix()<<" EMBEDED AUTO CSR CHECK and expectValue can not work together!"<<endl;
    //	//	ERROR_EXIT(TM::ABORT_FLOW);
    //	}
    //	checkPassFail = true;
#if 0
    fwout << "DCRM OVEM,LMAP,,(@@)" << endl; //* enable Digital Compare Result
#endif
}

double
d2s_IP_JTAG::getTimingPeriod() {
    static double period = -1000.0;
    if (period < 0) {
        int debug = 0;
        //		FLUSH(TM::APRM);
        //		fwout << "PCLK? PRM, PRM, (" << getTimingPort() << "), EXACT"
        //				<< endl;
        //		if (fwresult.size() != 1) {
        //			if (debug)
        //				cerr
        //				<< "ERROR couldn't evaluate timing period for timing-port: "
        //				<< getTimingPort() << endl;
        //			period = 0.0;
        //		} else {
        //			period = fwresult[0].getDoubleParam(2);
        //		}
    }
    return period;
}

bool
d2s_IP_JTAG::getExpectValue(const string& id) {
    if (LabelPassFailResult.find(id) != LabelPassFailResult.end()) {
        int site; //=CURRENT_SITE_NUMBER();
        if (LabelPassFailResult.find(id)->second.find(site) != LabelPassFailResult.find(id)->second.end()) {
            return LabelPassFailResult[id][site];
        } else {
//            cerr << "Error: no expect result for id:" << id << " site:" << site << endl;
            //			ABORT_TEST();
        }
    } else {
//        cerr << "Error: no expect result for id:" << id << endl;
        //		ABORT_TEST();
    }
    return false;
}

std::string
d2s_IP_JTAG::getWaitTemplatePatternName() {
	 return "d2s_JTAG_wait_template";
    //return JTAG_PORT_CONFIG[JTAG_id].d2s_template[JTAG_WAIT] + CONTEXT_POSTFIX_MAP[context];
}

//void
//d2s_IP_JTAG::write_TMS(const std::string& templatePatternName) {
//#ifndef AHB_MODE
//    /*************singlle template data**************/
//    //Step 1: Clean TMS in templates:
//    const string& tms_pin = JTAG_PORT_CONFIG[JTAG_id].tms_pin;
//
//
//    int length = 0;
//    switch (jtag_mode) {
//        case JTAG_WR_DR2:
//            HilinkDR2DataLength + HilinkDR2AddrLength + 7;
//            break;
//        case JTAG_WR_IR1:
//            length = JTAG_PORT_CONFIG[JTAG_id].HilinkIR1Length + 7;
//            break;
//        case JTAG_WR_IR2:
//            length = JTAG_PORT_CONFIG[JTAG_id].HilinkIR2Length + 7;
//            break;
//        case JTAG_WR_SDR1:
//            length = JTAG_PORT_CONFIG[JTAG_id].HilinkSDR1Length + 7;
//            break;
//        case JTAG_WR_SDR2:
//            length = JTAG_PORT_CONFIG[JTAG_id].HilinkSDR2Length + 7;
//            break;
//        case writeSDR_HEAD:
//            length = JTAG_PORT_CONFIG[JTAG_id].HilinkSDR_64BIT_Length + 7;
//            break;
//        case writeSDR_BODY:
//            length = JTAG_PORT_CONFIG[JTAG_id].HilinkSDR_64BIT_Length;
//            break;
//        case writeSDR3_END:
//            length = JTAG_PORT_CONFIG[JTAG_id].HilinkSDR3_END_Length + 4;
//            break;
//        case writeSDR4_END:
//            length = JTAG_PORT_CONFIG[JTAG_id].HilinkSDR4_END_Length + 4;
//            break;
//        default:
//            length = 10;
//            break;
//    }
//
//
//
//    //    VEC_LABEL_EDIT tempVecEdit_clean_TMS(templatePatternName, tms_pin);
//    //    VECTOR_DATA vectorData_clean_TMS[length];
//    //    for (int TemplateBitIndex = 0; TemplateBitIndex < length; TemplateBitIndex++) {
//    //        vectorData_clean_TMS[TemplateBitIndex].phyWvfIndex = 0;
//    //        vectorData_clean_TMS[TemplateBitIndex].vectorNum = TemplateBitIndex;
//    //    }
//    //    tempVecEdit_clean_TMS.downloadUserVectors(vectorData_clean_TMS, length); //TODO long than 80
//    //
//    //    //Step 2: Drive High Before TDI writing:
//    //    VEC_LABEL_EDIT tempVecEdit_DvHigh_BefTDIWrite(templatePatternName, tms_pin);
//    //    VECTOR_DATA vectorData_DvHigh_BefTDIWrite[2];
//    //    switch (jtag_mode) {
//    //        case JTAG_WR_DR2:
//    //            vectorData_DvHigh_BefTDIWrite[0].phyWvfIndex = 1;
//    //            vectorData_DvHigh_BefTDIWrite[0].vectorNum = 4;
//    //            vectorData_DvHigh_BefTDIWrite[1].phyWvfIndex = 0;
//    //            vectorData_DvHigh_BefTDIWrite[1].vectorNum = 5;
//    //            tempVecEdit_DvHigh_BefTDIWrite.downloadUserVectors(vectorData_DvHigh_BefTDIWrite, 2);
//    //            break;
//    //        case JTAG_WR_IR1:
//    //            vectorData_DvHigh_BefTDIWrite[0].phyWvfIndex = 1;
//    //            vectorData_DvHigh_BefTDIWrite[0].vectorNum = 4;
//    //            vectorData_DvHigh_BefTDIWrite[1].phyWvfIndex = 1;
//    //            vectorData_DvHigh_BefTDIWrite[1].vectorNum = 5;
//    //            tempVecEdit_DvHigh_BefTDIWrite.downloadUserVectors(vectorData_DvHigh_BefTDIWrite, 2);
//    //            break;
//    //        case JTAG_WR_IR2:
//    //            vectorData_DvHigh_BefTDIWrite[0].phyWvfIndex = 1;
//    //            vectorData_DvHigh_BefTDIWrite[0].vectorNum = 4;
//    //            vectorData_DvHigh_BefTDIWrite[1].phyWvfIndex = 1;
//    //            vectorData_DvHigh_BefTDIWrite[1].vectorNum = 5;
//    //            tempVecEdit_DvHigh_BefTDIWrite.downloadUserVectors(vectorData_DvHigh_BefTDIWrite, 2);
//    //            break;
//    //        case JTAG_WR_SDR1:
//    //            vectorData_DvHigh_BefTDIWrite[0].phyWvfIndex = 1;
//    //            vectorData_DvHigh_BefTDIWrite[0].vectorNum = 4;
//    //            vectorData_DvHigh_BefTDIWrite[1].phyWvfIndex = 0;
//    //            vectorData_DvHigh_BefTDIWrite[1].vectorNum = 5;
//    //            tempVecEdit_DvHigh_BefTDIWrite.downloadUserVectors(vectorData_DvHigh_BefTDIWrite, 2);
//    //            break;
//    //        case JTAG_WR_SDR2:
//    //            vectorData_DvHigh_BefTDIWrite[0].phyWvfIndex = 1;
//    //            vectorData_DvHigh_BefTDIWrite[0].vectorNum = 4;
//    //            vectorData_DvHigh_BefTDIWrite[1].phyWvfIndex = 0;
//    //            vectorData_DvHigh_BefTDIWrite[1].vectorNum = 5;
//    //            tempVecEdit_DvHigh_BefTDIWrite.downloadUserVectors(vectorData_DvHigh_BefTDIWrite, 2);
//    //            break;
//    //        case writeSDR_HEAD:
//    //            vectorData_DvHigh_BefTDIWrite[0].phyWvfIndex = 1;
//    //            vectorData_DvHigh_BefTDIWrite[0].vectorNum = 4;
//    //            vectorData_DvHigh_BefTDIWrite[1].phyWvfIndex = 0;
//    //            vectorData_DvHigh_BefTDIWrite[1].vectorNum = 5;
//    //            tempVecEdit_DvHigh_BefTDIWrite.downloadUserVectors(vectorData_DvHigh_BefTDIWrite, 2);
//    //            break;
//    //        case writeSDR3_END: break;
//    //        case writeSDR_BODY: break;
//    //        case writeSDR4_END: break;
//    //        default:
//    //            vectorData_DvHigh_BefTDIWrite[0].phyWvfIndex = 0;
//    //            vectorData_DvHigh_BefTDIWrite[0].vectorNum = 4;
//    //            vectorData_DvHigh_BefTDIWrite[1].phyWvfIndex = 0;
//    //            vectorData_DvHigh_BefTDIWrite[1].vectorNum = 5;
//    //            tempVecEdit_DvHigh_BefTDIWrite.downloadUserVectors(vectorData_DvHigh_BefTDIWrite, 2);
//    //            break;
//    //    }
//    //    // Step3 Drive High after TDI is done:
//    //    int cycle1, cycle2;
//    //    switch (jtag_mode) {
//    //        case JTAG_WR_DR2:
//    //            cycle1 = 8 + HilinkDR2AddrLength + HilinkDR2DataLength;
//    //            cycle2 = 8 + HilinkDR2AddrLength + HilinkDR2DataLength + 1;
//    //            break;
//    //        case JTAG_WR_IR1:
//    //            cycle1 = 8 + JTAG_PORT_CONFIG[JTAG_id].HilinkIR1Length - 1;
//    //            cycle2 = 8 + JTAG_PORT_CONFIG[JTAG_id].HilinkIR1Length;
//    //            break;
//    //        case JTAG_WR_IR2:
//    //            cycle1 = 8 + JTAG_PORT_CONFIG[JTAG_id].HilinkIR2Length - 1;
//    //            cycle2 = 8 + JTAG_PORT_CONFIG[JTAG_id].HilinkIR2Length;
//    //            break;
//    //        case JTAG_WR_SDR1:
//    //            cycle1 = 8 + JTAG_PORT_CONFIG[JTAG_id].HilinkSDR1Length - 1;
//    //            cycle2 = 8 + JTAG_PORT_CONFIG[JTAG_id].HilinkSDR1Length;
//    //            break;
//    //        case JTAG_WR_SDR2:
//    //            cycle1 = 8 + JTAG_PORT_CONFIG[JTAG_id].HilinkSDR2Length - 1;
//    //            cycle2 = 8 + JTAG_PORT_CONFIG[JTAG_id].HilinkSDR2Length;
//    //            break;
//    //        case writeSDR_HEAD:break;
//    //        case writeSDR_BODY:break;
//    //        case writeSDR3_END:
//    //            cycle1 = 8 + JTAG_PORT_CONFIG[JTAG_id].HilinkSDR3_END_Length - 1;
//    //            cycle2 = 8 + JTAG_PORT_CONFIG[JTAG_id].HilinkSDR3_END_Length;
//    //            break;
//    //        case writeSDR4_END:
//    //            cycle1 = 8 + JTAG_PORT_CONFIG[JTAG_id].HilinkSDR4_END_Length - 1;
//    //            cycle2 = 8 + JTAG_PORT_CONFIG[JTAG_id].HilinkSDR4_END_Length;
//    //
//    //            break;
//    //
//    //        default:
//    //            cycle1 = 8 + 17 + 16;
//    //            cycle2 = 8 + 17 + 16 + 1;
//    //            break;
//    //    }
//    //
//    //    VEC_LABEL_EDIT tempVecEdit_TMS(templatePatternName, tms_pin);
//    //    VECTOR_DATA vectorData[2];
//    //    vectorData[0].phyWvfIndex = 1;
//    //    vectorData[0].vectorNum = cycle1; //8 + pins -> second*getPadding() - 1;
//    //    vectorData[1].phyWvfIndex = 1;
//    //    vectorData[1].vectorNum = cycle2; //8 + pins -> second * getPadding();
//    //
//    //    switch (jtag_mode) {
//    //        case JTAG_WR_DR2:
//    //            tempVecEdit_TMS.downloadUserVectors(vectorData, 2);
//    //            break;
//    //        case JTAG_WR_IR1:
//    //            tempVecEdit_TMS.downloadUserVectors(vectorData, 2);
//    //            break;
//    //        case JTAG_WR_IR2:
//    //            tempVecEdit_TMS.downloadUserVectors(vectorData, 2);
//    //            break;
//    //        case JTAG_WR_SDR1:
//    //            tempVecEdit_TMS.downloadUserVectors(vectorData, 2);
//    //            break;
//    //        case JTAG_WR_SDR2:
//    //            tempVecEdit_TMS.downloadUserVectors(vectorData, 2);
//    //            break;
//    //        case writeSDR_HEAD:break;
//    //        case writeSDR_BODY:break;
//    //        case writeSDR3_END:break;
//    //            tempVecEdit_TMS.downloadUserVectors(vectorData, 2);
//    //            break;
//    //        case writeSDR4_END:
//    //            tempVecEdit_TMS.downloadUserVectors(vectorData, 2);
//    //            break;
//    //        default:
//    //            tempVecEdit_TMS.downloadUserVectors(vectorData, 2);
//    //            break;
//    //    }
//
//#endif
//}

void d2s_IP_JTAG::writeDynamicPerSite(long long address, const map<int, long long>& value, const string& id) {
    d2s::writeDynamic(address, value, id);
//	d2s::writeDynamic(address, value);//, id  modify by tony 20210817
}
//void
//d2s_IP_JTAG::writeDynamicPerSite_EX(long long address, const HILINK_PERSITE_WRITEDYN_EX& data, const string& id){
//	checkWrite();
//	if(!inD2sBlock){
//		cerr << "writeDynamic can only be used when inside a d2s_LABEL_BEGIN/END-block" << endl;
//		assert(inD2sBlock);
//	}
//#ifndef AHB_MODE
//	if(jtag_mode!=JTAG_WR_DR2){
//		cerr<<"Error: writeDynamicPerSite_EX is only supported under write DR2!"<<endl;
//	//	ERROR_EXIT(TM::ABORT_FLOW);
//	}
//#endif
//	long long dummy;
//	string templateLabelName = getNewWriteDynamicLabelName(address, dummy, id);
//	pair<set<string>::iterator, bool> ret = writeDynamicIDs.insert(id);
//	if(ret.second != false){
//		//first time for this id; add label to burst (in learning mode)
//		cycleOffset += getWriteCycles();
//		call_id++;
//
//		if(currentFrameworkMode == d2sFrameWorkModeType::LearningMode || currentFrameworkMode == d2sFrameWorkModeType::EngineeringMode){
//			//copy template pattern
//			if(!isCreatedByFW()){
//				if(!PatternManager::isPatternAvailable(templateLabelName)){
//					PatternManager::copyLabel(getWriteTemplatePatternName(), templateLabelName);
//				}
//			}
//			else{
//				createWritePattern(address, 0x00,templateLabelName);
//			}
//			burstLabels.push_back(templateLabelName);
//		}
//	}
//	else{
//		cerr<<"Error: Label "<<templateLabelName<<" is already exists!"<<endl;
//	//	ERROR_EXIT(TM::ABORT_FLOW);
//	}
//
//
//	HILINK_PERSITE_WRITEDYN_EX::const_iterator it;
//
////	FOR_EACH_SITE_BEGIN();
////		int SiteID = CURRENT_SITE_NUMBER() - 1;
////		it = data.find(SiteID);
////		if (it != data.end()) {
////			prepareDynamicWriteLabel_EX(address, it -> second, templateLabelName);
////		} else {
////			cerr<<"Error: map data is not consistency with site number,Please check map parameters!"<<endl;
////		}
////	FOR_EACH_SITE_END();
//
//	label_md5_tag.append(templateLabelName);
//	label_md5_tag.push_back('\n');
//}

void
d2s_IP_JTAG::prepareDynamicWriteLabel_EX(long long address, const T_HILINK_JTAG_WRITEDYN& data, const std::string& templatePatternName) {
#ifndef AHB_MODE
    if (jtag_mode != JTAG_WR_DR2) {
//        cerr << "Error: writeDynamicPerSite_EX is only supported under write DR2!" << endl;
        //	ERROR_EXIT(TM::ABORT_FLOW);
    }
#endif
    //	if(data.type==HILINK_JTAG_WRITEDYN_WAIT){
    //		VEC_LABEL_EDIT tempVecEdit_clean_TDI(templatePatternName, JTAG_PORT_CONFIG[JTAG_id].tdi_pin);
    //		VECTOR_DATA vectorData_clean_TDI[getWriteCycles()];
    //		for(int TemplateBitIndex = 0; TemplateBitIndex < getWriteCycles(); TemplateBitIndex ++)
    //		{
    //			vectorData_clean_TDI[TemplateBitIndex].phyWvfIndex=0;
    //			vectorData_clean_TDI[TemplateBitIndex].vectorNum = TemplateBitIndex;
    //		}
    //		tempVecEdit_clean_TDI.downloadUserVectors(vectorData_clean_TDI,getWriteCycles());
#ifndef AHB_MODE
    //		VEC_LABEL_EDIT tempVecEdit_clean_TMS(templatePatternName, JTAG_PORT_CONFIG[JTAG_id].tms_pin);
    //		VECTOR_DATA vectorData_clean_TMS[getWriteCycles()];
    //		for(int TemplateBitIndex = 0; TemplateBitIndex < getWriteCycles(); TemplateBitIndex ++)
    //		{
    //			vectorData_clean_TMS[TemplateBitIndex].phyWvfIndex=0;
    //			vectorData_clean_TMS[TemplateBitIndex].vectorNum = TemplateBitIndex;
    //		}
    //		tempVecEdit_clean_TMS.downloadUserVectors(vectorData_clean_TMS,getWriteCycles());
#else	//AHB_MODE
    VEC_LABEL_EDIT tempVecEdit_clean_SHIFTDR(templatePatternName, AHB_SHIFT_DR);
    VECTOR_DATA vectorData_clean_SHIFTDR[getWriteCycles()];
    for (int TemplateBitIndex = 0; TemplateBitIndex < getWriteCycles(); TemplateBitIndex++) {
        vectorData_clean_SHIFTDR[TemplateBitIndex].phyWvfIndex = 0;
        vectorData_clean_SHIFTDR[TemplateBitIndex].vectorNum = TemplateBitIndex;
    }
    tempVecEdit_clean_SHIFTDR.downloadUserVectors(vectorData_clean_SHIFTDR, getWriteCycles());

    VEC_LABEL_EDIT tempVecEdit_clean_UPDATEDR(templatePatternName, AHB_UPDATE_DR);
    VECTOR_DATA vectorData_clean_UPDATEDR[getWriteCycles()];
    for (int TemplateBitIndex = 0; TemplateBitIndex < getWriteCycles(); TemplateBitIndex++) {
        vectorData_clean_UPDATEDR[TemplateBitIndex].phyWvfIndex = 0;
        vectorData_clean_UPDATEDR[TemplateBitIndex].vectorNum = TemplateBitIndex;
    }
    tempVecEdit_clean_UPDATEDR.downloadUserVectors(vectorData_clean_UPDATEDR, getWriteCycles());
#endif	//AHB_MODE
}
//	else{
//#ifndef AHB_MODE
//		string tck_vec;
//		string tdi_vec;
//		string tdo_vec;
//		string tms_vec;
//		string trstn_vec;
//		T_JTAG_VEC_DATA vec_data={
//			tck_vec,
//			tdi_vec,
//			tdo_vec,
//			tms_vec,
//			trstn_vec
//		};
//		int len=len=1+HilinkDR2AddrLength+HilinkDR2DataLength+1;
//		unsigned long long value;
//		value  = (address & 0x1ffff);
//		value |= 0x20000;
//		value <<= 16;
//		value |= (data.data & 0xffff) ;
//		value <<= 1;
//		int size=create_JTAG_WRITE_Pattern(false,JTAG_DR2_ENTRY_DUMMY_CYCLE,vec_data,len,value);
//
//		VEC_LABEL_EDIT tempVecEdit_clean_TDI(templatePatternName, JTAG_PORT_CONFIG[JTAG_id].tdi_pin);
//		VECTOR_DATA vectorData_clean_TDI[size];
//		for(int TemplateBitIndex = 0; TemplateBitIndex < size; TemplateBitIndex ++)
//		{
//			vectorData_clean_TDI[TemplateBitIndex].phyWvfIndex=(int)tdi_vec[TemplateBitIndex];
//			vectorData_clean_TDI[TemplateBitIndex].vectorNum = TemplateBitIndex;
//		}
//		tempVecEdit_clean_TDI.downloadUserVectors(vectorData_clean_TDI,size);
//
//		VEC_LABEL_EDIT tempVecEdit_clean_TMS(templatePatternName, JTAG_PORT_CONFIG[JTAG_id].tms_pin);
//		VECTOR_DATA vectorData_clean_TMS[size];
//		for(int TemplateBitIndex = 0; TemplateBitIndex < size; TemplateBitIndex ++)
//		{
//			vectorData_clean_TMS[TemplateBitIndex].phyWvfIndex=(int)tms_vec[TemplateBitIndex];
//			vectorData_clean_TMS[TemplateBitIndex].vectorNum = TemplateBitIndex;
//		}
//		tempVecEdit_clean_TMS.downloadUserVectors(vectorData_clean_TMS,size);
//#else	//AHB_MODE
//		string vec_tdi;
//		string vec_tck;
//		string vec_AHB_MACRO0_INTERCEPT;
//		string vec_AHB_MACRO1_INTERCEPT;
//		string vec_AHB_SHIFT_DR;
//		string vec_AHB_MACRO0_TDO;
//		string vec_AHB_MACRO1_TDO;
//		string vec_AHB_UPDATE_DR;
//
//		T_AHB_VEC_DATA vec_data={
//			vec_tdi,
//			vec_tck,
//			vec_AHB_MACRO0_INTERCEPT,
//			vec_AHB_MACRO1_INTERCEPT,
//			vec_AHB_SHIFT_DR,
//			vec_AHB_MACRO0_TDO,
//			vec_AHB_MACRO1_TDO,
//			vec_AHB_UPDATE_DR
//		};
//
//		int size=AHB_WRITE_PATTERN_CYCLE;
//		create_AHB_WRITE_Pattern(address,data.data,vec_data);
//
//		VEC_LABEL_EDIT tempVecEdit_clean_TDI(templatePatternName, JTAG_PORT_CONFIG[JTAG_id].tdi_pin);
//		VECTOR_DATA vectorData_clean_TDI[size];
//		for(int TemplateBitIndex = 0; TemplateBitIndex < size; TemplateBitIndex ++)
//		{
//			vectorData_clean_TDI[TemplateBitIndex].phyWvfIndex=(int)vec_tdi[TemplateBitIndex];
//			vectorData_clean_TDI[TemplateBitIndex].vectorNum = TemplateBitIndex;
//		}
//		tempVecEdit_clean_TDI.downloadUserVectors(vectorData_clean_TDI,size);
//
//		VEC_LABEL_EDIT tempVecEdit_clean_SHIFTDR(templatePatternName, AHB_SHIFT_DR);
//		VECTOR_DATA vectorData_clean_SHIFTDR[size];
//		for(int TemplateBitIndex = 0; TemplateBitIndex < size; TemplateBitIndex ++)
//		{
//			vectorData_clean_SHIFTDR[TemplateBitIndex].phyWvfIndex=(int)vec_AHB_SHIFT_DR[TemplateBitIndex];
//			vectorData_clean_SHIFTDR[TemplateBitIndex].vectorNum = TemplateBitIndex;
//		}
//		tempVecEdit_clean_SHIFTDR.downloadUserVectors(vectorData_clean_SHIFTDR,size);
//
//		VEC_LABEL_EDIT tempVecEdit_clean_UPDATEDR(templatePatternName, AHB_UPDATE_DR);
//		VECTOR_DATA vectorData_clean_UPDATEDR[size];
//		for(int TemplateBitIndex = 0; TemplateBitIndex < size; TemplateBitIndex ++)
//		{
//			vectorData_clean_UPDATEDR[TemplateBitIndex].phyWvfIndex=(int)vec_AHB_UPDATE_DR[TemplateBitIndex];
//			vectorData_clean_UPDATEDR[TemplateBitIndex].vectorNum = TemplateBitIndex;
//		}
//		tempVecEdit_clean_UPDATEDR.downloadUserVectors(vectorData_clean_UPDATEDR,size);
//#endif	//AHB_MODE
//	}

//}

void
d2s_IP_JTAG::prepareDynamicWriteLabel(long long address, long long data, const std::string& templatePatternName) {
    //initWriteValueVectorMaps();
    int HIGH_WFIndex = getHighWaveformIndex();
    int LOW_WFIndex = getLowWaveformIndex();

    //	map<string, int> pinBitCount;
    //	map<string, VECTOR_DATA*> pinVecData;
    //
    //	bitvaluePinVector::const_iterator valuesAddress = writeAddressValueVectorMap[currentFormat].begin();
    //	for( ; valuesAddress != writeAddressValueVectorMap[currentFormat].end(); valuesAddress++){
    //		long long bitValue = valuesAddress->first;
    //		string pinToModify = valuesAddress->second.first;
    //		int cycle = valuesAddress->second.second;
    //		if(pinBitCount.find(pinToModify) == pinBitCount.end()){
    //			pinBitCount[pinToModify] = 0;
    //			pinVecData[pinToModify] = new VECTOR_DATA[128 * getPadding()]; //TODO: find a better way to find max bits...
    //		}
    //
    //		for(int padding=0; padding<getPadding(); padding++){
    //			pinVecData[pinToModify][pinBitCount[pinToModify]*getPadding()+padding].vectorNum = cycle+padding;
    //			pinVecData[pinToModify][pinBitCount[pinToModify]*getPadding()+padding].phyWvfIndex = (address & bitValue)? HIGH_WFIndex:LOW_WFIndex;
    //		}
    //
    //		pinBitCount[pinToModify]++;
    //	}
    //
    //	bitvaluePinVector::const_iterator valuesData = writeDataValueVectorMap[currentFormat].begin();
    //	for( ; valuesData != writeDataValueVectorMap[currentFormat].end(); valuesData++){
    //		long long bitValue = valuesData->first;
    //		string pinToModify = valuesData->second.first;
    //		int cycle = valuesData->second.second;
    //
    //		if(pinBitCount.find(pinToModify) == pinBitCount.end()){
    //
    //			pinBitCount[pinToModify] = 0;
    //			pinVecData[pinToModify] = new VECTOR_DATA[128 * getPadding()]; //TODO: find a better way to find max bits...
    //		}
    //
    //		for(int padding=0; padding<getPadding(); padding++){
    //			pinVecData[pinToModify][pinBitCount[pinToModify]*getPadding()+padding].vectorNum = cycle+padding;
    //			pinVecData[pinToModify][pinBitCount[pinToModify]*getPadding()+padding].phyWvfIndex = (data & bitValue)? HIGH_WFIndex:LOW_WFIndex;
    //		}
    //
    //		pinBitCount[pinToModify]++;
    //	}
    //
    //	map<string, int>::const_iterator pins = pinBitCount.begin();
    //	for( ; pins != pinBitCount.end(); pins++)
    //	{
    //		string pinToModify = pins->first;
    //		VEC_LABEL_EDIT tempVecEdit(templatePatternName, pinToModify);
    //		tempVecEdit.downloadUserVectors(pinVecData[pins->first], pins->second*getPadding());
    //		delete[] pinVecData[pinToModify];
    //	}
}

void
d2s_IP_JTAG::prepareDynamicReadOrExpectValueLabel(long long address, const std::string& labelName, long long data, long long strobeMask) {
    //	initReadAndExpectValueVectorMaps();
    //
    //	int HIGH_WFIndex = getHighWaveformIndex();
    //	int LOW_WFIndex = getLowWaveformIndex();
    //	int highStrobeWfIndex = getHighStrobeWaveformIndex();
    //	int lowStrobeWfIndex = getLowStrobeWaveformIndex();
    //	int xStrobeWfIndex = getMaskStrobeWaveformIndex();
    //
    //	map<string, int> pinBitCount;
    //	map<string, VECTOR_DATA*> pinVecData;
    //
    //	//address
    //	bitvaluePinVector::const_iterator valuesAddress = readAndExpectAddressValueVectorMap[currentFormat].begin();
    //	for( ; valuesAddress != readAndExpectAddressValueVectorMap[currentFormat].end(); valuesAddress++){
    //		long long bitValue = valuesAddress->first;
    //		string pinToModify = valuesAddress->second.first;
    //		int cycle = valuesAddress->second.second;
    //		if(pinBitCount.find(pinToModify) == pinBitCount.end()){
    //			pinBitCount[pinToModify] = 0;
    //			pinVecData[pinToModify] = new VECTOR_DATA[256 * getPadding()]; //TODO: find a better way to find max bits...
    //		}
    //
    //		for(int padding=0; padding<getPadding(); padding++){
    //			pinVecData[pinToModify][pinBitCount[pinToModify]*getPadding()+padding].vectorNum = cycle+padding;
    //			pinVecData[pinToModify][pinBitCount[pinToModify]*getPadding()+padding].phyWvfIndex = (address & bitValue)? HIGH_WFIndex:LOW_WFIndex;
    //		}
    //
    //		pinBitCount[pinToModify]++;
    //	}
    //
    //	//data
    //	bitvaluePinVector::const_iterator valuesData = readAndExpectDataValueVectorMap[currentFormat].begin();
    //	for( ; valuesData != readAndExpectDataValueVectorMap[currentFormat].end(); valuesData++){
    //		long long bitValue = valuesData->first;
    //		string pinToModify = valuesData->second.first;
    //		int cycle = valuesData->second.second;
    //		if(pinBitCount.find(pinToModify) == pinBitCount.end()){
    //			pinBitCount[pinToModify] = 0;
    //			pinVecData[pinToModify] = new VECTOR_DATA[256 * getPadding()]; //TODO: find a better way to find max bits...
    //		}
    //
    //		for(int padding=0; padding<getPadding(); padding++){
    //			pinVecData[pinToModify][pinBitCount[pinToModify]*getPadding()+padding].vectorNum = cycle+padding;
    //			if(strobeMask & bitValue){
    //				pinVecData[pinToModify][pinBitCount[pinToModify]*getPadding()+padding].phyWvfIndex = xStrobeWfIndex;
    //			}
    //			else{
    //				pinVecData[pinToModify][pinBitCount[pinToModify]*getPadding()+padding].phyWvfIndex = (data & bitValue)?highStrobeWfIndex:lowStrobeWfIndex;
    //			}
    //		}
    //
    //		pinBitCount[pinToModify]++;
    //	}
    //
    //	map<string, int>::const_iterator pins = pinBitCount.begin();
    //	for( ; pins != pinBitCount.end(); pins++)
    //	{
    //		string pinToModify = pins->first;
    //		VEC_LABEL_EDIT tempVecEdit(labelName, pinToModify);
    //		tempVecEdit.downloadUserVectors(pinVecData[pins->first], pins->second*getPadding());
    //		delete[] pinVecData[pinToModify];
    //	}

}

void
d2s_IP_JTAG::write_IRxDR0DR1(unsigned long long value) {
    unsigned long long data, addr;
    data = addr = 0;

//    if ((jtag_mode == writeSDR_HEAD) || (jtag_mode == writeSDR_BODY)) {
//        data = value & 0xFFFFFFFFFFFFFFFFLL;
//        addr = 0; //for the IRxDR0DR1, addr=0
//
//        write(addr, data);
//    } else {
        if (((value >> getDataBits()) >> getAddressBits()) == 0) { //TODO
            data = value & 0xffffffff;
            addr = (value >> 32) & 0xffffffff; //for the IRxDR0DR1, addr=0

            if (addr & 0xFFFF0000) {
                unsigned long long label_code = 0xDB10000000000000LL;
                label_code |= addr;
                string label_md5;
                label_md5.clear();
                label_md5.append((char*) &label_code, 8);
                label_code = 0xDB20000000000000LL;
                label_code |= data;
                label_md5.append((char*) &label_code, 8);
                write(addr, data);
            } else {
                unsigned long long label_code = 0xDB11000000000000LL;
                label_code |= (value & 0x00FFFFFFFFFFFFFFLL);
                write(addr, data);
            }
        } else {
//            cerr << "Error: Please check the IR0/IR1/DR0/DR1 value length setting in HILINK_INFO[] of userConfig!" << endl;
            //		ABORT_TEST();// analog/digital sequence
            //ERROR_EXIT(TM::ABORT_FLOW);
        }


//    }

    /*	data=value & 0xffffffff;
            addr=(value>>32) & 0xffffffff;
            write(addr,data);*/

}

d2s_IP_JTAG&
d2s_IP_JTAG::Instance() {
    JTAG_id = 0;
    current_JTAG_port_id = 0;
    return JTAG_port(current_JTAG_port_id);
}

void
d2s_IP_JTAG::select_JTAG(int id) {
#ifndef AHB_MODE
    //    if (exchg_ind2sblock) {
    //        cerr << "Error: select_JTAG cannot be used in d2sBlock!" << endl;
    //        //	ERROR_EXIT(TM::ABORT_FLOW);//ARES
    //    }
    //    if (id == -1) {
    //        d2s_status::set_status("JTAG_port", "-1");
    //        current_JTAG_port_id = 0;
    //        return;
    //    }
    //    assert(id >= 0 and id < JTAG_PORT_COUNT);
    //    current_JTAG_port_id = id;
    //    char buf[64];
    //    sprintf(buf, "%d", id);
    //    d2s_status::set_status("JTAG_port", buf);
    //
    //    IR1_cycles = getJtagPatternCycleByTDILength(JTAG_WR_IR1, JTAG_PORT_CONFIG[id].HilinkIR1Length);
    //    SDR1_cycles = getJtagPatternCycleByTDILength(JTAG_WR_SDR1, JTAG_PORT_CONFIG[id].HilinkSDR1Length);
    //    SDR2_cycles = getJtagPatternCycleByTDILength(JTAG_WR_SDR2, JTAG_PORT_CONFIG[id].HilinkSDR2Length);
    //    SDR3_END_cycles = getJtagPatternCycleByTDILength(writeSDR3_END, JTAG_PORT_CONFIG[id].HilinkSDR3_END_Length);
    //    SDR4_END_cycles = getJtagPatternCycleByTDILength(writeSDR4_END, JTAG_PORT_CONFIG[id].HilinkSDR4_END_Length);
    //    SDR_Head_64BIT_Length = getJtagPatternCycleByTDILength(writeSDR_HEAD, JTAG_PORT_CONFIG[id].HilinkSDR_64BIT_Length);
    //    SDR_Body_64BIT_Length = getJtagPatternCycleByTDILength(writeSDR_BODY, JTAG_PORT_CONFIG[id].HilinkSDR_64BIT_Length);
    //    IR2_cycles = getJtagPatternCycleByTDILength(JTAG_WR_IR2, JTAG_PORT_CONFIG[id].HilinkIR2Length);
    //    DR2_cycles = getJtagPatternCycleByTDILength(JTAG_WR_DR2, 1 + HilinkDR2AddrLength + HilinkDR2DataLength + 1, JTAG_DR2_ENTRY_DUMMY_CYCLE);


#endif
}

void
d2s_IP_JTAG::switch_JTAG(int id) {
#ifndef AHB_MODE
    //    assert(id >= 0 and id < JTAG_PORT_COUNT);
    //    string port_id;
    //    d2s_status::isStatusAvailable("JTAG_port", port_id);
    //    if (port_id != "-1") {
    //        cerr << "Error: D2S_FRAMEWORK_JTAG(-1) must be used at first before use switch_JTAG!" << endl;
    //        ERROR_EXIT(TM::ABORT_FLOW);
    //    }
    //    current_JTAG_port_id = id;
    //
    //    IR1_cycles = getJtagPatternCycleByTDILength(JTAG_WR_IR1, JTAG_PORT_CONFIG[id].HilinkIR1Length);
    //    SDR1_cycles = getJtagPatternCycleByTDILength(JTAG_WR_SDR1, JTAG_PORT_CONFIG[id].HilinkSDR1Length);
    //    SDR2_cycles = getJtagPatternCycleByTDILength(JTAG_WR_SDR2, JTAG_PORT_CONFIG[id].HilinkSDR2Length);
    //    SDR3_END_cycles = getJtagPatternCycleByTDILength(writeSDR3_END, JTAG_PORT_CONFIG[id].HilinkSDR3_END_Length);
    //    SDR4_END_cycles = getJtagPatternCycleByTDILength(writeSDR4_END, JTAG_PORT_CONFIG[id].HilinkSDR4_END_Length);
    //    SDR_Head_64BIT_Length = getJtagPatternCycleByTDILength(writeSDR_HEAD, JTAG_PORT_CONFIG[id].HilinkSDR_64BIT_Length);
    //    SDR_Body_64BIT_Length = getJtagPatternCycleByTDILength(writeSDR_BODY, JTAG_PORT_CONFIG[id].HilinkSDR_64BIT_Length);
    //    IR2_cycles = getJtagPatternCycleByTDILength(JTAG_WR_IR2, JTAG_PORT_CONFIG[id].HilinkIR2Length);
    //    DR2_cycles = getJtagPatternCycleByTDILength(JTAG_WR_DR2, 1 + HilinkDR2AddrLength + HilinkDR2DataLength + 1, JTAG_DR2_ENTRY_DUMMY_CYCLE);
#endif
}

int
d2s_IP_JTAG::get_current_JTAG_port() {
    return current_JTAG_port_id;
}

int d2s_IP_JTAG::current_JTAG_port_id = DEFAULT_JTAG_PORT;

d2s_IP_JTAG&
d2s_IP_JTAG::JTAG_port(int id) {
    assert(id >= 0 and id < JTAG_PORT_COUNT);
    static vector<d2s_IP_JTAG> JTAG_ports;
    static int is_init = 0;
    if (!is_init) {
        for (uint i = 0; i < JTAG_PORT_COUNT; i++) {
            JTAG_ports.push_back(d2s_IP_JTAG(i));
        }
        is_init = 1;
        printf("init JTAG_ports!\n");
    }
    return JTAG_ports[id];
}

int d2s_IP_JTAG::getReadPatternVectors() {
    return 96;
}

int d2s_IP_JTAG::getWritePatternVectors() {
    int length = 0;
    switch (jtag_mode) {
        case JTAG_WR_DR2:
            length = 48;
            break;
        case JTAG_WR_DR1:
            length = 48;
            break;
        case JTAG_WR_DR0:
            length = 48;
            break;           
        case JTAG_WR_IR2:
            length = 24;
            break;
        case JTAG_WR_IR1:
            length = 24;
            break;
        case JTAG_WR_IR0:
            length = 24;
            break;
        default:
//            cerr << "Error: JTAG MODE is not set!" << endl;
            //ABORT_TEST();
            return 0;
    };
    return length; //Ares??? TODO SDR3
}

std::string d2s_IP_JTAG::getReadTemplateTestName() {
    return "d2s_JTAG_read_template_STD";
}

std::string d2s_IP_JTAG::getWaitTemplateTestName() {
    return "d2s_JTAG_wait_template";
}

std::string d2s_IP_JTAG::getWriteTemplateTestName() {
    string temp_test = "";
    switch (jtag_mode) {
        case JTAG_WR_DR2:
            temp_test = "d2s_JTAG_writeDR2_template_STD";
            break;
        case JTAG_WR_DR1:
            temp_test = "d2s_JTAG_writeDR1_template_STD";
            break;
        case JTAG_WR_DR0:
            temp_test = "d2s_JTAG_writeDR0_template_STD";
            break;           
        case JTAG_WR_IR2:
            temp_test = "d2s_JTAG_writeIR2_template_STD";
            break;
        case JTAG_WR_IR1:
            temp_test = "d2s_JTAG_writeIR1_template_STD";
            break;
        case JTAG_WR_IR0:
            temp_test = "d2s_JTAG_writeIR0_template_STD";
            break;

        default:
//            cerr << "Error: JTAG MODE is not set!" << endl;
            //ABORT_TEST();
            return "";
    };
    return temp_test;
}

d2s_IP_JTAG&
d2s_IP_JTAG::pre_d2s_Instance() {
    JTAG_id = 0;
    current_JTAG_port_id = 0;
    d2s_IP_JTAG& inst = pre_d2s_JTAG_port(current_JTAG_port_id);
    //inst.getContext();
    return inst;
}

d2s_IP_JTAG&
d2s_IP_JTAG::pre_d2s_JTAG_port(int id) {
    assert(id >= 0 and id < JTAG_PORT_COUNT);
    static vector<d2s_IP_JTAG> pre_d2s_JTAG_ports;
    static int is_init = 0;
    if (!is_init) {
        for (uint i = 0; i < JTAG_PORT_COUNT; i++) {
            pre_d2s_JTAG_ports.push_back(d2s_IP_JTAG(i, true));
        }
        is_init = 1;
        printf("init pre_d2s JTAG_ports!\n");
    }
    return pre_d2s_JTAG_ports[id];
}

void
d2s_IP_JTAG::setFrameworkMode(const d2sFrameWorkModeType::Enum mode) {
    if (is_pre_d2s) {
//        cerr << "Error: setFrameworkMode can not be used in pre_d2s JTAG!" << endl;
        //	ERROR_EXIT(TM::ABORT_FLOW);
    }
    exchg_d2smode = mode;
    //d2s_Serial::setFrameworkMode(mode);
}

//bool d2s_IP_JTAG::is_in_d2s_block(){
//	return inD2sBlock;
//}

void
d2s_IP_JTAG::setD2sBlockBegin() {
    //	if(is_pre_d2s){
    //		cerr<<"Error: pre d2s JTAG can not be used in normal d2s block!"<<endl;
    //	//	ERROR_EXIT(TM::ABORT_FLOW);
    //	}
    //	exchg_ind2sblock=true;
    //	synchronized_address.clear();
    //	d2s_Serial::setD2sBlockBegin();
    //	AppendSuiteName=false;
    //	csr_check_cycle_info.clear();
    //	CSR_Check_Info.clear();
    //
    //	isCSRCheck=false;
    //	static bool is_flow_variable_exists=true;
    //	if(is_flow_variable_exists){
    //		try{
    //			int isCheck;
    //		//	GET_USER_FLAG("CSR_atomic_operation",&isCheck);
    //			isCSRCheck=isCheck;
    //		}
    //		catch(...){
    //			is_flow_variable_exists=false;
    //			isCSRCheck=false;
    //		}
    //	}

}

void
d2s_IP_JTAG::setD2sBlockEnd() {
    //	exchg_ind2sblock=false;
    //	d2s_Serial::setD2sBlockEnd();
    //	if(isProductionMode() || !GLOBAL_CSR_SYNC_FLAG){
    //		return;
    //	}
    //	if(		synchronized_address.find("MACRO_SELECTED")==synchronized_address.end() &&
    //			synchronized_address.find("AUTO_CSR_SYNC_DONE")!=synchronized_address.end()
    //	){
    //		cerr<<"Error: In d2s-block "<<d2sFramework::get_current_prefix()<<" selectMacro or selectMacro_MB must be executed in each d2s block!"<<endl;
    //	//	ERROR_EXIT(TM::ABORT_FLOW);
    //	}
}

bool
d2s_IP_JTAG::is_address_synchronized(const string& reg_grp, uint addr) {
    if (!is_pre_d2s) {
//        cerr << "Error: must be used by pre d2s JTAG!" << endl;
        //	ERROR_EXIT(TM::ABORT_FLOW);
    }
    assert(exchg_ind2sblock);
    bool result = false;
    map<string, set<int> >::iterator itr = synchronized_address.find(reg_grp);
    if (itr == synchronized_address.end()) {
        result = false;
    } else {
        result = (itr->second.find(addr) != itr->second.end());
    }
#ifdef __debug__
//    cout << "check synchronized_flag " << reg_grp << ":" << addr << " = " << result << endl;
#endif
    return result;
}

void
d2s_IP_JTAG::set_address_synchronized_flag(const string& reg_grp, uint addr) {
    if (!is_pre_d2s) {
//        cerr << "Error: must be used by pre d2s JTAG!" << endl;
        //	ERROR_EXIT(TM::ABORT_FLOW);
    }
    assert(exchg_ind2sblock);
    map<string, set<int> >::iterator itr = synchronized_address.find(reg_grp);
    if (itr == synchronized_address.end()) {
        set<int> tmp;
        tmp.insert(addr);
        synchronized_address.insert(pair<string, set<int> >(reg_grp, tmp));
    } else {
        itr->second.insert(addr);
    }
#ifdef __debug__
//    cout << "set synchronized_flag " << reg_grp << ":" << addr << endl;
#endif

}

void
d2s_IP_JTAG::pre_d2s_begin() {
    if (!is_pre_d2s) {
//        cerr << "Error: must be used by pre d2s JTAG!" << endl;
        //	ERROR_EXIT(TM::ABORT_FLOW);
    }
    //	readOffsets.clear();
    //	writeDynamicIDs.clear();
    //	checkPassFail = false;
    //	burst_md5_tag="";
    //	label_md5_tag.clear();
    //	burstLabels.clear();
    //	cycleOffset = 0;
    //	call_id=0;
    //	inD2sBlock=exchg_ind2sblock;
    //	currentFrameworkMode = exchg_d2smode;
    //	is_production_mode=(currentFrameworkMode==2);
}

void
d2s_IP_JTAG::pre_d2s_end(const string& label, bool append_suitename, bool overwrite) {
    if (!is_pre_d2s) {
//        cerr << "Error: must be used by pre d2s JTAG!" << endl;
        //	ERROR_EXIT(TM::ABORT_FLOW);
    }

    //	readIdValues.clear();
    //	string md5_labels=get_MD5(label_md5_tag);
    //	string tmp;
    //	d2s_status::isStatusAvailable("JTAG_port",tmp);
    //	md5_labels+=tmp;
    //	d2s_status::isStatusAvailable("CTX",tmp);
    //	md5_labels+=tmp;
    //#ifdef AUTO_HWPRBS
    //	d2s_status::isStatusAvailable("HWPRBS",tmp);
    //	md5_labels+=tmp;
    //#endif
    //
    //	if(append_suitename){
    //	//	GET_TESTSUITE_NAME(tmp);
    //		md5_labels+=tmp;
    //	}
    //
    //	md5_labels=get_MD5(md5_labels);
    //
    //
    //	static bool is_user_var_exists=true;
    //	string prefix_tag="";
    //	if(is_user_var_exists){
    //		try{
    //		//	GET_USER_STRING("d2s_prefix",prefix_tag);
    //			prefix_tag+="_";
    //		}
    //		catch(...){
    //			is_user_var_exists=false;
    //		}
    //	}
    //
    //	string labelName=label+prefix_tag+"_"+md5_labels;
    //
    //	if(overwrite || !PatternManager::isPatternAvailable(labelName, "MPBU", portName)){
    //		if(currentFrameworkMode == d2sFrameWorkModeType::LearningMode || currentFrameworkMode == d2sFrameWorkModeType::EngineeringMode){
    //			if(burstLabels.size() != 0){
    //				PatternManager::createBurst(labelName, burstLabels, portName);
    //			}
    //			else{
    //				cout<<"Error: !!!!!!burst call list"<<labelName<<"@"<<portName<<" is empty!!!!!!!!!"<<endl;
    //				if(PatternManager::isPatternAvailable(labelName, "MPBU", portName)){
    //					PatternManager::deleteLabel(labelName, portName);
    //				}
    //		//		ERROR_EXIT(TM::ABORT_FLOW);
    //			}
    //		}
    //#ifdef AUTO_HWPRBS
    //	string hwprbs_status;
    //	d2s_status::isStatusAvailable("HWPRBS",hwprbs_status);
    //	if(hwprbs_status=="ON"){
    //		vector<string> rx_labels;
    //		vector<string> tx_labels;
    //		rx_labels.push_back(HWPRBS_RX_LABEL);
    //		tx_labels.push_back(HWPRBS_TX_LABEL);
    //		PatternManager::createBurst(labelName, rx_labels, HWPRBS_RX_PORT);
    //		PatternManager::createBurst(labelName, tx_labels, HWPRBS_TX_PORT);
    //	}
    //#endif
    //	}
    //#ifdef __debug__
    //	cout<<"pre d2s execute label: "<<labelName<<endl;
    //#endif
    ////	Primary.label(labelName);替換
    ////	FUNCTIONAL_TEST();//替換
    //	evalutateReads();
    //
    //	readOffsets.clear();
    //	writeDynamicIDs.clear();
    //	checkPassFail = false;
    //	burst_md5_tag="";
    //	label_md5_tag.clear();
    //	burstLabels.clear();
    //	cycleOffset = 0;
    //	call_id=0;
    //
    //	inD2sBlock=false;
    //	currentFrameworkMode = d2sFrameWorkModeType::DefaultMode;

}

void
d2s_IP_JTAG::setAppendSuiteName() {
    AppendSuiteName = true;
}

bool
d2s_IP_JTAG::needAppendSuiteName() {
    return AppendSuiteName;
}



//bool
//d2s_IP_JTAG::isCreatedByFW(){
//	return true;
//}
#ifndef AHB_MODE
//void
//d2s_IP_JTAG::make_capture_pattern(uint addr){
//	T_MAIN_PATTERN_DATA pattern_data;
//	pattern_data.port=getTimingPort();
//	if (context == CTX_DEFAULT)
//	{
//		pattern_data.context="DEFAULT";
//		pattern_data.wavetable=JTAG_PORT_CONFIG[JTAG_id].wavetable.std_wavetable;
//	}
//	else
//	{
//		pattern_data.context="FASTDIFF";
//		pattern_data.wavetable=JTAG_PORT_CONFIG[JTAG_id].wavetable.fastdiff_wavetable;
//	}
//
//	pattern_data.pattern_data.clear();
//	pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tck_pin,""));
//	pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tdi_pin,""));
//	pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tdo_pin,""));
//	pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tms_pin,""));
//	pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].trstn_pin,""));
//
//
//	T_JTAG_VEC_DATA vec_data={
//		pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].tck_pin)->second,
//		pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].tdi_pin)->second,
//		pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].tdo_pin)->second,
//		pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].tms_pin)->second,
//		pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].trstn_pin)->second
//	};
//
//	create_JTAG_DR2_CAPTURE_Pattern(addr,vec_data);
//	pattern_data.size=JTAG_READ_PATTERN_CYCLE;
//	ostringstream str;
//	str<<getInterfaceName()<<"_CAP_0x"<<hex<<addr;
//	create_all_nop_pattern(str.str(),pattern_data);
//}
//
//void
//d2s_IP_JTAG::createMultiWritePattern(vector<long long> address,vector<long long> data,const std::string& labelName){
//	T_MAIN_PATTERN_DATA pattern_data;
//	pattern_data.size = 0;
//
//	int len;
//	unsigned long long value=0;
//	bool is_IR=false;
//	int entery_cycle=JTAG_IRx_DR0_DR1_ENTRY_DUMMY_CYCLE;
//
//	if(jtag_mode == JTAG_WR_DR2)
//	{
//		  len=1+HilinkDR2AddrLength+HilinkDR2DataLength+1;
//		  entery_cycle=JTAG_DR2_ENTRY_DUMMY_CYCLE;
//
//		  string temp_tck;
//		  string temp_tdi;
//		  string temp_tdo;
//		  string temp_tms;
//		  string temp_trstn;
//		  T_JTAG_VEC_DATA vec_data = {
//				  temp_tck,
//				  temp_tdi,
//				  temp_tdo,
//				  temp_tms,
//				  temp_trstn
//		  };
//
//		  pattern_data.port=getTimingPort();
//		  if (context == CTX_DEFAULT)
//		  {
//			  pattern_data.context="DEFAULT";
//			  pattern_data.wavetable=JTAG_PORT_CONFIG[JTAG_id].wavetable.std_wavetable;
//		  }
//		  else
//		  {
//			  pattern_data.context="FASTDIFF";
//			  pattern_data.wavetable=JTAG_PORT_CONFIG[JTAG_id].wavetable.fastdiff_wavetable;
//		  }
//		  pattern_data.pattern_data.clear();
//		  pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tck_pin,""));
//		  pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tdi_pin,""));
//		  pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tdo_pin,""));
//		  pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tms_pin,""));
//		  pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].trstn_pin,""));
//
//		  for(uint i=0;i<address.size() and i<data.size();i++){
////			  len=1+HilinkDR2AddrLength_32Bit+HilinkDR2DataLength_32Bit+1;
////			  entery_cycle=JTAG_DR2_ENTRY_DUMMY_CYCLE;
//			  value = 0;
//			  temp_tck.clear();
//			  temp_tdi.clear();
//			  temp_tdo.clear();
//			  temp_tms.clear();
//			  temp_trstn.clear();
//
//			  value  = address[i] & 0x1ffff;
//			  value |= 0x20000;
//			  value <<= 16; // left shift 32
//			  value |= (data[i] & 0xffff);
//			  value <<= 1;
//
//
//
//
//
//
//
//			   int size=create_JTAG_WRITE_Pattern(is_IR,entery_cycle,vec_data,len,value);
//
//			   pattern_data.pattern_data[JTAG_PORT_CONFIG[JTAG_id].tck_pin] += temp_tck;
//			   pattern_data.pattern_data[JTAG_PORT_CONFIG[JTAG_id].tdi_pin] += temp_tdi;
//			   pattern_data.pattern_data[JTAG_PORT_CONFIG[JTAG_id].tdo_pin] += temp_tdo;
//			   pattern_data.pattern_data[JTAG_PORT_CONFIG[JTAG_id].tms_pin] += temp_tms;
//			   pattern_data.pattern_data[JTAG_PORT_CONFIG[JTAG_id].trstn_pin] += temp_trstn;
//
//			   pattern_data.size += size;
//		  }
//		  create_all_nop_pattern(labelName,pattern_data);
//	}
//	else{
//		cout<< "createMultiWritePattern only used in 32Bit D2S !!!"<<endl;
//	}
//
//}









//void
//d2s_IP_JTAG::createWritePattern(long long address, long long data, const std::string& labelName){
//	T_MAIN_PATTERN_DATA pattern_data;
//	int len;
//	unsigned long long value=0;
//	bool is_IR=false;
//	int entery_cycle=JTAG_IRx_DR0_DR1_ENTRY_DUMMY_CYCLE;
//	switch(jtag_mode){
//		case JTAG_WR_IR0:
//		case JTAG_WR_IR1:
//		case JTAG_WR_IR2:
//		{
//			len=JTAG_PORT_CONFIG[JTAG_id].HilinkIRLength;
//			value=( (((unsigned long long)address) <<32 ) | data );
//			is_IR=true;
//			break;
//		}
//		case JTAG_WR_DR0:
//		{
//			len=JTAG_PORT_CONFIG[JTAG_id].HilinkDR0Length;
//			value=( (((unsigned long long)address) <<32 ) | data );
//			break;
//		}
//		case JTAG_WR_DR1:
//		{
//			len=JTAG_PORT_CONFIG[JTAG_id].HilinkDR1Length;
//			value=( (((unsigned long long)address) <<32 ) | data );
//			break;
//		}
//		case JTAG_WR_DR2:
//		{
//			len=1+HilinkDR2AddrLength+HilinkDR2DataLength+1;
//			value  = (address & 0x1ffff);
//			value |= 0x20000;
//			value <<= 16;
//			value |= (data & 0xffff) ;
//			value <<= 1;
//			entery_cycle=JTAG_DR2_ENTRY_DUMMY_CYCLE;
//			break;
//		}
//		default:
//			cerr<<"Error: JTAG MODE ERROR!"<<endl;
//	//		ERROR_EXIT(TM::ABORT_FLOW);
//			break;
//	}
//	pattern_data.port=getTimingPort();
//	if (context == CTX_DEFAULT)
//	{
//		pattern_data.context="DEFAULT";
//		pattern_data.wavetable=JTAG_PORT_CONFIG[JTAG_id].wavetable.std_wavetable;
//	}
//	else
//	{
//		pattern_data.context="FASTDIFF";
//		pattern_data.wavetable=JTAG_PORT_CONFIG[JTAG_id].wavetable.fastdiff_wavetable;
//	}
//	pattern_data.pattern_data.clear();
//	pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tck_pin,""));
//	pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tdi_pin,""));
//	pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tdo_pin,""));
//	pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tms_pin,""));
//	pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].trstn_pin,""));
//
//	T_JTAG_VEC_DATA vec_data={
//		pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].tck_pin)->second,
//		pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].tdi_pin)->second,
//		pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].tdo_pin)->second,
//		pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].tms_pin)->second,
//		pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].trstn_pin)->second
//	};
//
//
//	int size=create_JTAG_WRITE_Pattern(is_IR,entery_cycle,vec_data,len,value);
//	pattern_data.size=size;
//
//	create_all_nop_pattern(labelName,pattern_data);
//}


//void
//d2s_IP_JTAG::createWaitPattern(long long cycle, const std::string& labelName){
//	static bool isInit=false;
//	static T_MAIN_PATTERN_DATA pattern_data;
//	if(!isInit){
//		pattern_data.port=getTimingPort();
//		pattern_data.size=8;
//		pattern_data.pattern_data.clear();
//		string vecidx_0,vecidx_1,vecidx_clk,vecidx_X;
//
//		vecidx_0.clear();
//		vecidx_0.append(8,JTAG_INPUT_LOW);
//		vecidx_1.clear();
//		vecidx_1.append(8,JTAG_INPUT_HIGH);
//		vecidx_clk.clear();
//		vecidx_clk.append(8,JTAG_INPUT_CLK);
//		vecidx_X.clear();
//		vecidx_X.append(8,JTAG_OUTPUT_MASK);
//
//		pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tck_pin,vecidx_clk));
//		pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tdi_pin,vecidx_0));
//		pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tdo_pin,vecidx_X));
//		pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tms_pin,vecidx_0));
//		pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].trstn_pin,vecidx_1));
//		isInit=true;
//	}
//	pattern_data.port=getTimingPort();
//	if (context == CTX_DEFAULT)
//	{
//		pattern_data.context="DEFAULT";
//		pattern_data.wavetable=JTAG_PORT_CONFIG[JTAG_id].wavetable.std_wavetable;
//	}
//	else
//	{
//		pattern_data.context="FASTDIFF";
//		pattern_data.wavetable=JTAG_PORT_CONFIG[JTAG_id].wavetable.fastdiff_wavetable;
//	}
//	create_wait_pattern(labelName,cycle,pattern_data);
//}
//
//void
//d2s_IP_JTAG::createMultiReadExpectPattern(vector<long long> address, const std::string& labelName, long long value, long long mask){
//	 T_MAIN_PATTERN_DATA pattern_data;
//	 pattern_data.size = 0;
//
//	 pattern_data.port=getTimingPort();
//	   string temp_tck;
//	   string temp_tdi;
//	   string temp_tdo;
//	   string temp_tms;
//	   string temp_trstn;
//
//	   T_JTAG_VEC_DATA vec_data={
//		   temp_tck,
//		   temp_tdi,
//		   temp_tdo,
//		   temp_tms,
//		   temp_trstn
//	   };
//
//	  if (context == CTX_DEFAULT)
//	  {
//	    pattern_data.context="DEFAULT";
//	    pattern_data.wavetable=JTAG_PORT_CONFIG[JTAG_id].wavetable.std_wavetable;
//	  }
//	  else
//	  {
//	    pattern_data.context="FASTDIFF";
//	    pattern_data.wavetable=JTAG_PORT_CONFIG[JTAG_id].wavetable.fastdiff_wavetable;
//	  }
//
//	   pattern_data.pattern_data.clear();
//	   pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tck_pin,""));
//	   pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tdi_pin,""));
//	   pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tdo_pin,""));
//	   pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tms_pin,""));
//	   pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].trstn_pin,""));
//
//	   for(uint i=0;i < address.size();i++){
//		   temp_tck.clear();
//		   temp_tdi.clear();
//		   temp_tdo.clear();
//		   temp_tms.clear();
//		   temp_trstn.clear();
//
//		   create_JTAG_DR2_READ_Pattern(address[i],vec_data,value,mask);
//		   pattern_data.pattern_data[JTAG_PORT_CONFIG[JTAG_id].tck_pin] += vec_data.vec_tck;
//		   pattern_data.pattern_data[JTAG_PORT_CONFIG[JTAG_id].tdi_pin] += vec_data.vec_tdi;
//		   pattern_data.pattern_data[JTAG_PORT_CONFIG[JTAG_id].tdo_pin] += vec_data.vec_tdo;
//		   pattern_data.pattern_data[JTAG_PORT_CONFIG[JTAG_id].tms_pin] += vec_data.vec_tms;
//		   pattern_data.pattern_data[JTAG_PORT_CONFIG[JTAG_id].trstn_pin] += vec_data.vec_trstn;
//
//		   pattern_data.size += JTAG_READ_PATTERN_CYCLE;
//	   }
//
//	   create_all_nop_pattern(labelName,pattern_data);
//}










//void
//d2s_IP_JTAG::createReadExpectPattern(long long address, const std::string& labelName, long long value, long long mask){
//	T_MAIN_PATTERN_DATA pattern_data;
//	pattern_data.port=getTimingPort();
//	if (context == CTX_DEFAULT)
//	{
//		pattern_data.context="DEFAULT";
//		pattern_data.wavetable=JTAG_PORT_CONFIG[JTAG_id].wavetable.std_wavetable;
//	}
//	else
//	{
//		pattern_data.context="FASTDIFF";
//		pattern_data.wavetable=JTAG_PORT_CONFIG[JTAG_id].wavetable.fastdiff_wavetable;
//	}
//
//	pattern_data.pattern_data.clear();
//	pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tck_pin,""));
//	pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tdi_pin,""));
//	pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tdo_pin,""));
//	pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].tms_pin,""));
//	pattern_data.pattern_data.insert(pair<string,string>(JTAG_PORT_CONFIG[JTAG_id].trstn_pin,""));
//
//
//	T_JTAG_VEC_DATA vec_data={
//		pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].tck_pin)->second,
//		pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].tdi_pin)->second,
//		pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].tdo_pin)->second,
//		pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].tms_pin)->second,
//		pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].trstn_pin)->second
//	};
//
//	create_JTAG_DR2_READ_Pattern(address,vec_data,value,mask);
//	pattern_data.size=JTAG_READ_PATTERN_CYCLE;
//
//	create_all_nop_pattern(labelName,pattern_data);
//}
#else

void
d2s_IP_JTAG::createWritePattern(long long address, long long data, const std::string& labelName) {
    T_MAIN_PATTERN_DATA pattern_data;
    pattern_data.port = getTimingPort();
    if (context == CTX_DEFAULT) {
        pattern_data.context = "DEFAULT";
        pattern_data.wavetable = JTAG_PORT_CONFIG[JTAG_id].wavetable.std_wavetable;
    } else {
        pattern_data.context = "FASTDIFF";
        pattern_data.wavetable = JTAG_PORT_CONFIG[JTAG_id].wavetable.fastdiff_wavetable;
    }

    pattern_data.pattern_data.clear();
    pattern_data.pattern_data.insert(pair<string, string>(JTAG_PORT_CONFIG[JTAG_id].tdi_pin, ""));
    pattern_data.pattern_data.insert(pair<string, string>(JTAG_PORT_CONFIG[JTAG_id].tck_pin, ""));
    pattern_data.pattern_data.insert(pair<string, string>(AHB_MACRO0_INTERCEPT, ""));
    pattern_data.pattern_data.insert(pair<string, string>(AHB_MACRO1_INTERCEPT, ""));
    pattern_data.pattern_data.insert(pair<string, string>(AHB_SHIFT_DR, ""));
    pattern_data.pattern_data.insert(pair<string, string>(AHB_MACRO0_TDO, ""));
    pattern_data.pattern_data.insert(pair<string, string>(AHB_MACRO1_TDO, ""));
    pattern_data.pattern_data.insert(pair<string, string>(AHB_UPDATE_DR, ""));


    T_AHB_VEC_DATA vec_data = {
        pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].tdi_pin)->second,
        pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].tck_pin)->second,
        pattern_data.pattern_data.find(AHB_MACRO0_INTERCEPT)->second,
        pattern_data.pattern_data.find(AHB_MACRO1_INTERCEPT)->second,
        pattern_data.pattern_data.find(AHB_SHIFT_DR)->second,
        pattern_data.pattern_data.find(AHB_MACRO0_TDO)->second,
        pattern_data.pattern_data.find(AHB_MACRO1_TDO)->second,
        pattern_data.pattern_data.find(AHB_UPDATE_DR)->second
    };

    create_AHB_WRITE_Pattern(address, data, vec_data);
    pattern_data.size = AHB_WRITE_PATTERN_CYCLE;

    create_all_nop_pattern(labelName, pattern_data);
}

void
d2s_IP_JTAG::createWaitPattern(long long cycle, const std::string& labelName) {
    static bool isInit = false;
    static T_MAIN_PATTERN_DATA pattern_data;
    if (!isInit) {
        pattern_data.port = getTimingPort();
        pattern_data.size = 8;
        pattern_data.pattern_data.clear();
        string vecidx_0, vecidx_bypass, vecidx_clk, vecidx_X;

        vecidx_0.clear();
        vecidx_0.append(8, AHB_INPUT_LOW);
        vecidx_bypass.clear();
        vecidx_bypass.append(8, AHB_INPUT_BYPASS);
        vecidx_clk.clear();
        vecidx_clk.append(8, AHB_INPUT_CLK);
        vecidx_X.clear();
        vecidx_X.append(8, AHB_OUTPUT_MASK);

        pattern_data.pattern_data.insert(pair<string, string>(JTAG_PORT_CONFIG[JTAG_id].tdi_pin, vecidx_0));
        pattern_data.pattern_data.insert(pair<string, string>(JTAG_PORT_CONFIG[JTAG_id].tck_pin, vecidx_clk));
        pattern_data.pattern_data.insert(pair<string, string>(AHB_MACRO0_INTERCEPT, vecidx_bypass));
        pattern_data.pattern_data.insert(pair<string, string>(AHB_MACRO1_INTERCEPT, vecidx_bypass));
        pattern_data.pattern_data.insert(pair<string, string>(AHB_SHIFT_DR, vecidx_0));
        pattern_data.pattern_data.insert(pair<string, string>(AHB_MACRO0_TDO, vecidx_X));
        pattern_data.pattern_data.insert(pair<string, string>(AHB_MACRO1_TDO, vecidx_X));
        pattern_data.pattern_data.insert(pair<string, string>(AHB_UPDATE_DR, vecidx_0));
        isInit = true;
    }
    pattern_data.port = getTimingPort();
    if (context == CTX_DEFAULT) {
        pattern_data.context = "DEFAULT";
        pattern_data.wavetable = JTAG_PORT_CONFIG[JTAG_id].wavetable.std_wavetable;
    } else {
        pattern_data.context = "FASTDIFF";
        pattern_data.wavetable = JTAG_PORT_CONFIG[JTAG_id].wavetable.fastdiff_wavetable;
    }
    create_wait_pattern(labelName, cycle, pattern_data);
}

void
d2s_IP_JTAG::createReadExpectPattern(long long address, const std::string& labelName, long long value, long long mask) {
    T_MAIN_PATTERN_DATA pattern_data;
    pattern_data.port = getTimingPort();
    if (context == CTX_DEFAULT) {
        pattern_data.context = "DEFAULT";
        pattern_data.wavetable = JTAG_PORT_CONFIG[JTAG_id].wavetable.std_wavetable;
    } else {
        pattern_data.context = "FASTDIFF";
        pattern_data.wavetable = JTAG_PORT_CONFIG[JTAG_id].wavetable.fastdiff_wavetable;
    }

    pattern_data.pattern_data.clear();
    pattern_data.pattern_data.insert(pair<string, string>(JTAG_PORT_CONFIG[JTAG_id].tdi_pin, ""));
    pattern_data.pattern_data.insert(pair<string, string>(JTAG_PORT_CONFIG[JTAG_id].tck_pin, ""));
    pattern_data.pattern_data.insert(pair<string, string>(AHB_MACRO0_INTERCEPT, ""));
    pattern_data.pattern_data.insert(pair<string, string>(AHB_MACRO1_INTERCEPT, ""));
    pattern_data.pattern_data.insert(pair<string, string>(AHB_SHIFT_DR, ""));
    pattern_data.pattern_data.insert(pair<string, string>(AHB_MACRO0_TDO, ""));
    pattern_data.pattern_data.insert(pair<string, string>(AHB_MACRO1_TDO, ""));
    pattern_data.pattern_data.insert(pair<string, string>(AHB_UPDATE_DR, ""));


    T_AHB_VEC_DATA vec_data = {
        pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].tdi_pin)->second,
        pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].tck_pin)->second,
        pattern_data.pattern_data.find(AHB_MACRO0_INTERCEPT)->second,
        pattern_data.pattern_data.find(AHB_MACRO1_INTERCEPT)->second,
        pattern_data.pattern_data.find(AHB_SHIFT_DR)->second,
        pattern_data.pattern_data.find(AHB_MACRO0_TDO)->second,
        pattern_data.pattern_data.find(AHB_MACRO1_TDO)->second,
        pattern_data.pattern_data.find(AHB_UPDATE_DR)->second
    };

    create_AHB_READ_Pattern(address, macroid, vec_data, value, mask);
    pattern_data.size = AHB_READ_PATTERN_CYCLE;

    create_all_nop_pattern(labelName, pattern_data);
}

void
d2s_IP_JTAG::make_capture_pattern(uint addr) {
    T_MAIN_PATTERN_DATA pattern_data;
    pattern_data.port = getTimingPort();
    if (context == CTX_DEFAULT) {
        pattern_data.context = "DEFAULT";
        pattern_data.wavetable = JTAG_PORT_CONFIG[JTAG_id].wavetable.std_wavetable;
    } else {
        pattern_data.context = "FASTDIFF";
        pattern_data.wavetable = JTAG_PORT_CONFIG[JTAG_id].wavetable.fastdiff_wavetable;
    }

    pattern_data.pattern_data.clear();
    pattern_data.pattern_data.insert(pair<string, string>(JTAG_PORT_CONFIG[JTAG_id].tdi_pin, ""));
    pattern_data.pattern_data.insert(pair<string, string>(JTAG_PORT_CONFIG[JTAG_id].tck_pin, ""));
    pattern_data.pattern_data.insert(pair<string, string>(AHB_MACRO0_INTERCEPT, ""));
    pattern_data.pattern_data.insert(pair<string, string>(AHB_MACRO1_INTERCEPT, ""));
    pattern_data.pattern_data.insert(pair<string, string>(AHB_SHIFT_DR, ""));
    pattern_data.pattern_data.insert(pair<string, string>(AHB_MACRO0_TDO, ""));
    pattern_data.pattern_data.insert(pair<string, string>(AHB_MACRO1_TDO, ""));
    pattern_data.pattern_data.insert(pair<string, string>(AHB_UPDATE_DR, ""));


    T_AHB_VEC_DATA vec_data = {
        pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].tdi_pin)->second,
        pattern_data.pattern_data.find(JTAG_PORT_CONFIG[JTAG_id].tck_pin)->second,
        pattern_data.pattern_data.find(AHB_MACRO0_INTERCEPT)->second,
        pattern_data.pattern_data.find(AHB_MACRO1_INTERCEPT)->second,
        pattern_data.pattern_data.find(AHB_SHIFT_DR)->second,
        pattern_data.pattern_data.find(AHB_MACRO0_TDO)->second,
        pattern_data.pattern_data.find(AHB_MACRO1_TDO)->second,
        pattern_data.pattern_data.find(AHB_UPDATE_DR)->second
    };

    create_AHB_CAPTURE_Pattern(addr, macroid, vec_data);
    pattern_data.size = AHB_READ_PATTERN_CYCLE;
    ostringstream str;
    str << getInterfaceName() << (macroid == 0 ? "_BP" : "_C2C") << "_CAP_0x" << hex << addr;
    create_all_nop_pattern(str.str(), pattern_data);
}
#endif



//class ___{
//public:
//	___(){
//		printf("--------------------------\n");
//		printf("initial hilink d2s V2.0!\n");
//		d2s_IP_JTAG::JTAG_port(0);
//		d2s_IP_JTAG::pre_d2s_JTAG_port(0);
//		printf("--------------------------\n");
//	};
//};
//___ ____;

#undef __debug__

