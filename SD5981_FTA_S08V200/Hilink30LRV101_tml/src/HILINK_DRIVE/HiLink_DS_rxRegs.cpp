#include <HILINK_DRIVE/HiLink_DS_rxRegs.h>

#include <iostream>
using namespace std;
DS_rxRegs::DS_rxRegs() {
	// TODO Auto-generated constructor stub
	for(int i=0;i<DS_RX_CSR_NUM;i++){
		csr[i]=0;
	}
	sliceID=0;
	macroID=0;
	broadcast=false;
	reset_csr_verify();
}

DS_rxRegs::~DS_rxRegs() {}

bool
DS_rxRegs::get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos){
	if(csrIndex>=DS_RX_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	return REG_INFO.get_reg_infos(csrIndex,reg_infos);
}

DS_rxRegs&
DS_rxRegs::getInstance(){
	static DS_rxRegs theInstance;
	return theInstance;
}

uint
DS_rxRegs::get_HILINK_MAX_LANE_NUM(){
	//TODO: add your code for CSR Address mapping
	return HILINK_LANE_NUM;
}

uint
DS_rxRegs::getAddressMapToHiLink(int csrIndex){
	if(csrIndex>=DS_RX_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	//TODO: add your code for CSR Address mapping
	return (uint)(0x4000 | (broadcast << 13) | (sliceID << 9) | ((uint)0x1<< 7) | csrIndex << 1);
}


uint&
DS_rxRegs::get_csr(uint csrIndex){
	if(csrIndex>=DS_RX_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	return csr[csrIndex];
}

void
DS_rxRegs::get_default_MacroLaneID(T_MacroLaneID& id){
	//TODO: add your code for CSR Address mapping
	id.MacroID=macroID;
	id.LaneID=sliceID;
}

uint
DS_rxRegs::getCSRCount(){
	return DS_RX_CSR_NUM;
}

string
DS_rxRegs::getName(){
	return "DS_RX";
}

///////////////////////////////////////////////////////////////////////////


	/// Receive path power down control. Active low.
	/// 0 = Power down all receiver circuitry 
	/// 1 = Power up all receiver circuitry
	/// New in v101:  Now used as a trigger to power up/down the Receiver circuits (CTLE, Center Channel, Edge Channel, Monitor Channel, DFE taps) in sequence with default settings.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{0,"rxpwrdb",15,15}
	};
	return reg;
}

	/// Power down control of rx_auxclk.
	/// 0 = Power down rx_auxclk output.
	/// 1 = Power up rx_auxclk output.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxauxclkpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{0,"rxauxclkpwrdb",14,14}
	};
	return reg;
}

	/// CML low power enable. 
	/// 0 = Normal CML power consumption
	/// 1 = Enable CML low power
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::lpcmlen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{0,"lpcmlen",11,11}
	};
	return reg;
}

	/// Mute control for the RX input stage. The average (long term) voltage of the p, and m inputs are equalized. Offset calibration requires  RXMUTE to be 1.
	/// 0 = Normal operation.
	/// 1 = Mute input to first CTLE stage.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxmute(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{0,"rxmute",9,9}
	};
	return reg;
}

	/// CTLE 1st eq stage coarse boost range select
	/// 0:  select default boost range  
	/// 1:select extended boost range
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleboosten1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{0,"ctleboosten1",8,8}
	};
	return reg;
}

	/// P_32b  divider selector  related to rx_auxclk_32b  recovered clock for external gearboxing    [ref to fig.9 Data Slice Clock Generation in the DataSheet]. Also see related register  RXAUXCLKPWRDB  and DFESPARE (div by 5 mode enable)
	/// 00 = divide by 8 (or divide by 10 if div by 5 mode enabled)
	/// 01 = divide by 16 (or divide by 20 if div by 5 mode enabled)
	/// 10 = divide by 32 (or divide by 40 if div by 5 mode enabled)
	/// 11 = divide by 4 (or divide by 5 if div by 5 mode enabled)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxauxclkdiv(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{0,"rxauxclkdiv",4,3}
	};
	return reg;
}

	/// Rx input signal attenuation control.  
	/// 000:   -1.2dB 
	/// 001:   -1.9dB
	/// 010:   -2.55dB 
	/// 011:   -3.15dB
	/// 100:   -3.75dB 
	/// 101:   -4.25dB
	/// 110:   -4.75dB 
	/// 111:   -5.25dB
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlepassgn(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{0,"ctlepassgn",2,0}
	};
	return reg;
}

	/// Not Used In V101
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlehfzen1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{1,"ctlehfzen1",15,15}
	};
	return reg;
}

	/// CTLE  1st eq stage coarse boost select. 
	/// 000 = Lowest coarse boost setting
	/// 001 =
	/// 010 =
	/// .
	/// 110 = 
	/// 111 = Highest coarse boost setting
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleboostc1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{1,"ctleboostc1",14,12}
	};
	return reg;
}

	/// CTLE 1st eq stage mid-band capacitor select. 
	/// 00 = Lowest capacitor setting (highest mid-band frequency)
	/// 01 =
	/// 10 =
	/// 11 = Highest capacitor setting (lowest mid-band frequency)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlecmband1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{1,"ctlecmband1",11,10}
	};
	return reg;
}

	/// CTLE 1st eq stage mid-band resistor control.
	/// 00 =   disabled midband function (CTLECMBAND1 function is also disabled).
	/// 01 =   Highest resistor setting (Lowest mid-band boost)
	/// 10 = 
	/// 11 =  Lowest resistor setting (Highest mid-band boost)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlermband1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{1,"ctlermband1",9,8}
	};
	return reg;
}

	/// CTLE 1st eq stage high frequency zero control. 
	/// 000 = Highest zero frequency 
	/// 001    
	/// 010   
	/// ..   
	/// 110 = Lowest zero frequency 
	/// 111 = invalid setting
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleza1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{1,"ctleza1",7,5}
	};
	return reg;
}

	/// CTLE 1st eq stage squelch control bits. 
	/// 
	/// 00 = No squelch applied
	/// 01 = min squelch applied
	/// 10  or 11 = max squelch applied
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlesqh1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{1,"ctlesqh1",4,3}
	};
	return reg;
}

	/// CTLE 1st gain stage gain control.  
	/// 000 = Lower gain setting
	/// 001=
	/// 010=
	/// ..
	/// 110=
	/// 111 = Highest gain setting
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleactgn1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{1,"ctleactgn1",2,0}
	};
	return reg;
}

	/// Not Used In V101
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlehfzen2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{2,"ctlehfzen2",15,15}
	};
	return reg;
}

	/// CTLE 2nd eq stage coarse boost select. 
	/// 000 = Lowest coarse boost setting
	/// 001 =
	/// 010 =
	/// ..
	/// 110 = 
	/// 111 = Highest coarse boost setting
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleboostc2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{2,"ctleboostc2",14,12}
	};
	return reg;
}

	/// CTLE 2nd eq stage mid-band capacitor select. 
	/// 00 = Lowest capacitor setting (highest mid-band frequency)
	/// 01 = 
	/// 10 = 
	/// 11 = Highest capacitor setting (lowest mid-band frequency)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlecmband2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{2,"ctlecmband2",11,10}
	};
	return reg;
}

	/// CTLE 2nd eq stage mid-band resistor control.
	/// 00 =   disabled midband function (CTLECMBAND2 function is also disabled).
	/// 01 =   Highest resistor setting (Lowest mid-band boost)
	/// 10 = 
	/// 11 =  Lowest resistor setting (Highest mid-band boost)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlermband2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{2,"ctlermband2",9,8}
	};
	return reg;
}

	/// CTLE 2nd eq stage high frequency zero control. 
	/// 000 = Highest zero frequency 
	/// 001    
	/// 010   
	/// ..
	/// 110 = Lowest zero frequency 
	/// 111 = invalid setting
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleza2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{2,"ctleza2",7,5}
	};
	return reg;
}

	/// CTLE 2nd equalizer stage squelch control bits. 
	/// 
	/// 00 = No squelch applied
	/// 01 = Lowest squelch applied
	/// 10 or 11 = Highest squelch applied
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlesqh2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{2,"ctlesqh2",4,3}
	};
	return reg;
}

	/// CTLE 2nd gain stage gain control. 
	/// 000 = Lower gain setting
	/// 001 =
	/// 010 =
	/// ..
	/// 110 = 
	/// 111 = Highest gain setting
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleactgn2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{2,"ctleactgn2",2,0}
	};
	return reg;
}

	/// Not Used In V101
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlehfzen3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{3,"ctlehfzen3",15,15}
	};
	return reg;
}

	/// CTLE 3rd eq stage coarse boost select. 
	/// 000 = Lowest coarse boost setting
	/// 001 = 
	/// 010 =
	/// ..
	/// 110 = 
	/// 111 = Highest coarse boost setting
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleboostc3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{3,"ctleboostc3",14,12}
	};
	return reg;
}

	/// CTLE 3rd eq stage mid-band capacitor select. 
	/// 00 = Lowest capacitor setting (highest mid-band frequency)
	/// 01 =
	/// 10 =
	/// 11 = Highest capacitor setting (lowest mid-band frequency)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlecmband3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{3,"ctlecmband3",11,10}
	};
	return reg;
}

	/// CTLE 3rd eq stage mid-band resistor control.
	/// 00 =   disabled midband function (CTLECMBAND3 function is also disabled).
	/// 01 =   Highest resistor setting (Lowest mid-band boost)
	/// 10 = 
	/// 11 =  Lowest resistor setting (Highest mid-band boost)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlermband3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{3,"ctlermband3",9,8}
	};
	return reg;
}

	/// CTLE 3rd eq stage high frequency zero control. 
	/// 000 = Highest zero frequency 
	/// 001    
	/// 010   
	/// ..
	/// 110 = Lowest zero frequency 
	/// 111 = invalid setting
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleza3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{3,"ctleza3",7,5}
	};
	return reg;
}

	/// CTLE 3rd eq stage squelch control bits.  
	/// 
	/// 00 = No squelch applied
	/// 01 = Lowest squelch applied
	/// 10 or 11 = Highest squelch applied
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlesqh3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{3,"ctlesqh3",4,3}
	};
	return reg;
}

	/// CTLE 3rd gain stage gain control.
	/// 000 = Lower gain setting
	/// 001 =
	/// 010 =
	/// ..
	/// 110 = 
	/// 111 = Highest gain setting (default)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleactgn3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{3,"ctleactgn3",2,0}
	};
	return reg;
}

	/// CTLE 1st gain stage inductor un-peaking enable.
	/// 0 = Un-peaking disabled (normal bandwidth)
	/// 1 = Un-peaking enabled (smaller bandwidth)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlegnlunpken1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{4,"ctlegnlunpken1",3,3}
	};
	return reg;
}

	/// CTLE 2nd gain stage inductor un-peaking enable.
	/// 0 = Un-peaking disabled (normal bandwidth)
	/// 1 = Un-peaking enabled (smaller bandwidth)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlegnlunpken2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{4,"ctlegnlunpken2",2,2}
	};
	return reg;
}

	/// CTLE 3rd gain stage inductor un-peaking enable.
	/// 0 = Un-peaking disabled (normal bandwidth)
	/// 1 = Un-peaking enabled (smaller bandwidth)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlegnlunpken3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{4,"ctlegnlunpken3",1,1}
	};
	return reg;
}

	/// DFE feedback power down control (DFE idac and tap gen clock). Active low.
	/// 0 = Power down DFE feedback
	/// 1 = Power up DFE feedback
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfepwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{5,"dfepwrdb",15,15}
	};
	return reg;
}

	/// DFE tap power down control for taps 10-15. Active low.
	/// 0 = Power down all taps from 10 to 15.
	/// 1 = Power up all taps from 10 to 15.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfemvtappwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{5,"dfemvtappwrdb",14,14}
	};
	return reg;
}

	/// DFE tap power down for tap 1-9
	/// bit[0] = tap1 (0 =  power down; 1 = power up DFE tap1)
	/// bit[1] = tap2 (0 =  power down; 1 = power up DFE tap2)
	/// bit[2] = tap3 (0 =  power down; 1 = power up DFE tap3)
	/// bit[3] = tap4 (0 =  power down; 1 = power up DFE tap4)
	/// bit[4] = tap5 (0 =  power down; 1 = power up DFE tap5)
	/// bit[5] = tap6 (0 =  power down; 1 = power up DFE tap6)
	/// bit[6] = tap7 (0 =  power down; 1 = power up DFE tap7)
	/// bit[7] = tap8 (0 =  power down; 1 = power up DFE tap8)
	/// bit[8] = tap9 (0 =  power down; 1 = power up DFE tap9)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfefxtappwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{5,"dfefxtappwrdb",13,5}
	};
	return reg;
}

	/// Rx DFE Isummer boost control. 
	/// 00 = Minimum boost
	/// 01 =
	/// 10 =
	/// 11 = Maximum boost
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfesumboost(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{5,"dfesumboost",4,3}
	};
	return reg;
}

	/// Rx DFE Isummer gain control. 
	/// 000 = Minimum gain
	/// 001  =  
	/// ��..  
	/// 111  = Maximum gain
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfegnsum(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{5,"dfegnsum",2,0}
	};
	return reg;
}

	/// Main DFE Power sequence control  Active low.
	/// 0 = Power down DFE sequence
	/// 1 = Power up DFE sequence
	/// New in V101: Used as a trigger to power up/down the RX DFE taps in sequence with default settings.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxdfemainpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{6,"rxdfemainpwrdb",7,7}
	};
	return reg;
}

	/// DFE fixed tap 2 polarity and weight.  
	/// 
	/// bit[6] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[5:0] -  weight (binary),
	/// 000000 = Minimum Tap Weight
	/// 000001 =
	/// 000010 =
	/// ..
	/// 111111 = Maximum Tap Weight
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfefxtap2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{6,"dfefxtap2",6,0}
	};
	return reg;
}

	/// DFE fixed tap 3 polarity and weight.  
	/// 
	/// bit[5] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[4:0] -  weight (binary),
	/// 00000 = Minimum Tap Weight
	/// 00001 =
	/// 00010 =
	/// ..
	/// 11111 = Maximum Tap Weight
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfefxtap3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{7,"dfefxtap3",13,8}
	};
	return reg;
}

	/// DFE fixed tap 4 polarity and weight.   
	/// 
	/// bit[5] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[4:0] -  weight (binary),
	/// 00000 = Minimum Tap Weight
	/// 00001=
	/// 00010 = 
	/// ?..
	/// 11111 = Maximum Tap Weight
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfefxtap4(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{7,"dfefxtap4",5,0}
	};
	return reg;
}

	/// DFE fixed tap 5 polarity and weight.  
	/// 
	/// bit[5] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[4:0] -  weight (binary),
	/// 00000 = Minimum Tap Weight
	/// 00001 =
	/// 00010 =
	/// ..
	/// 11111 = Maximum Tap Weight
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfefxtap5(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{8,"dfefxtap5",15,10}
	};
	return reg;
}

	/// DFE fixed tap 6 polarity and weight.  
	/// 
	/// bit[4] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] -  weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfefxtap6(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{8,"dfefxtap6",9,5}
	};
	return reg;
}

	/// DFE fixed tap 7 polarity and weight.  
	/// 
	/// bit[4] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] -  weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfefxtap7(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{8,"dfefxtap7",4,0}
	};
	return reg;
}

	/// DFE Tap   8 polarity and weight.   
	/// 
	/// bit[4] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfefxtap8(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{9,"dfefxtap8",12,8}
	};
	return reg;
}

	/// DFE Tap 9  polarity and weight.   
	/// 
	/// bit[4] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfefxtap9(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{9,"dfefxtap9",4,0}
	};
	return reg;
}

	/// DFE Tap 10 polarity and weight.  
	/// 
	/// bit[4] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfemvtap1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{10,"dfemvtap1",14,10}
	};
	return reg;
}

	/// DFE Tap 11  polarity and  weight.  
	/// 
	/// bit[4] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfemvtap2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{10,"dfemvtap2",9,5}
	};
	return reg;
}

	/// DFE Tap 12  polarity and weight.  
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfemvtap3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{10,"dfemvtap3",4,0}
	};
	return reg;
}

	/// DFE Tap 13  polarity and weight.  
	/// 
	/// bit[4] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfemvtap4(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{11,"dfemvtap4",14,10}
	};
	return reg;
}

	/// DFE Tap 12  polarity and weight. 
	/// 
	/// bit[4] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfemvtap5(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{11,"dfemvtap5",9,5}
	};
	return reg;
}

	/// DFE Tap 13  polarity and weight.   
	/// 
	/// bit[4] - polarity bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - weight (binary),
	/// 0000 = Minimum Tap Weight
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1111 = Maximum Tap Weight
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfemvtap6(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{11,"dfemvtap6",4,0}
	};
	return reg;
}

	/// Receiver digital circuitry reset. Active low.
	/// 0 = Reset RX logic
	/// 1 = RX out of reset
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxrstb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{12,"rxrstb",15,15}
	};
	return reg;
}

	/// RX data width select  (also refer to related register RXRATEMODE)
	/// 00 = Normal Mode 
	/// Sends 40 bits at Full-rate   
	/// Sends 20 bits at Half-rate, using Full-rate clk
	/// Sends 10 bits at Quarter-rate, using Full-rate clk 
	/// Sends 5 bits at Octal-rate, using Full-rate clk
	/// Sends 3 bits at Hex-rate, using Full-rate clk
	/// 01 = 2X Mode   
	/// Sends 40 bits at Half-rate, using Half-rate clk 
	/// Sends 20 bits at Quarter-rate, using Half-rate clk
	/// Sends 10 bits at Octal-rate, using Half-rate clk
	/// Sends 5 bits at Hex-rate, using Half-rate clk
	/// 10 = 4X Mode  
	/// Sends 40 bits at Quarter-rate, using Quarter-rate clk 
	/// Sends 20 bits at Octal-rate, using Quarter-rate clk
	/// Sends 10 bits at Hex-rate, using Quarter-rate clk
	/// 11 = Reserved
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxdwidth(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{12,"rxdwidth",14,13}
	};
	return reg;
}

	/// RX bit rate mode.
	/// 000 = full-rate
	/// 001 = 1/2-rate
	/// 010 = 1/4-rate
	/// 011 = 1/8-rate
	/// 100   = 1/16-rate
	/// 101 to 111 = do not use
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxratemode(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{12,"rxratemode",12,10}
	};
	return reg;
}

	/// Selects the mapping of the parallel RXD bus from the serial bit order:
	/// 0 = LSB is the first serial bit 
	/// 1 = MSB is the first bit input
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxbitorder(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{12,"rxbitorder",9,9}
	};
	return reg;
}

	/// RX data polarity control. When set, all received bits are inverted before being sent out to the core.
	/// 0 = Do not invert the RX data
	/// 1 = Invert RX the data
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxpolarity(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{12,"rxpolarity",8,8}
	};
	return reg;
}

	/// Enable TX-RX parallel loopback.
	/// 0 = mission mode
	/// 1 = Enable the TX-to-RX parallel loopback. In this mode the 40 bit TX data  from the core are looped back and sent  to the core.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::txrxparlpbken(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{12,"txrxparlpbken",7,7}
	};
	return reg;
}

	/// Choose monitor channel for eye scan
	/// 0: monitor I channel
	/// 1: monitor Q channel
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mdatasel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{12,"mdatasel",6,6}
	};
	return reg;
}

	/// Eye monitor center data masking enable (applicable only in the full-rate mode)
	/// 1 = enable (in this case eye monitor uses only ~50% of the bits based on the sign of the previous center bit set by TAP1POL) 
	/// 0 = disable
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::tap1en(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{12,"tap1en",5,5}
	};
	return reg;
}

	/// Set the polarity of the previous center bit for eye monitor data masking (applicable only on in the full-rate mode and when TAP1EN is set to 1)
	/// 1 = process the center bit only if the previous bit is 1    
	/// 0 = process the center bit if the previous bit is 0
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::tap1pol(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{12,"tap1pol",4,4}
	};
	return reg;
}

	/// Freeze CDR. When CDR is frozen, it doesn't track the jitter and PPM of incoming data.
	/// 0 = Normal operation
	/// 1 = CDR is frozen
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cdrfreeze(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{12,"cdrfreeze",3,3}
	};
	return reg;
}

	/// Box car select
	/// 0 = Majority voting
	/// 1 = box car mode
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::boxcarsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{12,"boxcarsel",2,2}
	};
	return reg;
}

	/// Second loop enable. By enabling the second loop integrator CDR can track more PPM up to +/-XXXXppm, 
	/// 0 = Disable the CDR's second loop integrator.
	/// 1 = Enable the second loop integrator.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::secloopen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{12,"secloopen",1,1}
	};
	return reg;
}

	/// Each transition of this bit, from 0 to 1 or from 1 to 0, will cause the RX phase rotator to move 1UI  to slip one serial bit. Multiple slips can be achieved by toggling this bit. Each transition has to wait for previous slip to complete (at least 64 word clock cycles).
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::bitslip(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{12,"bitslip",0,0}
	};
	return reg;
}

	/// CDR soft reset. Active low.
	/// 0 = Reset CDR
	/// 1 = Normal operation
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cdrrstb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{13,"cdrrstb",15,15}
	};
	return reg;
}

	/// CDR phase gain.
	/// 000 = 1;    001 = 2;    010 = 3;    011 = 4
	/// ;100 = 5;  101 = 6;  110 = 7;  111 = 8.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::phsgn(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{13,"phsgn",14,12}
	};
	return reg;
}

	/// Use center channel data only for CDR adaptation in subrate mode.
	/// 0 = feature diabled.  
	/// 1 = feature enabled. CDR only use data from analog center channel for adaptation.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cdredgeoffen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{13,"cdredgeoffen",7,7}
	};
	return reg;
}

	/// Center clock phase adjustment freeze
	/// 0 = adjustment running normally
	/// 1 = adjustment is frozen at current value
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cpafreeze(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{13,"cpafreeze",6,6}
	};
	return reg;
}

	/// Center clock phase adjustment gain selection
	/// 00 = Full Rate, shift to right by 7
	/// 01 = Half Rate, shift to right by 6
	/// 10 = Quarter Rate, shift to right by 5
	/// 11 = Octal Rate, shift to right by 4
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cpagainsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{13,"cpagainsel",5,4}
	};
	return reg;
}

	/// Center clock phase adjustment
	/// 0= adjustment is disabled
	/// 1= adjustment is enabled
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cpaenable(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{13,"cpaenable",3,3}
	};
	return reg;
}

	/// CDR frequency gain
	/// 000 = 1;    001 = 2;    010 = 4;    011 = 8
	/// ;100 = 16;  101 = 32;  110 = 64;  111 = 128.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::freqgn(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{13,"freqgn",2,0}
	};
	return reg;
}

	/// Phase offset between the center channel and the edge channel. A 2's complement value (-128 to 127) with each step of 1/32 full-rate UI. Nominal setting depends on the rate mode as follows,
	/// Rate Mode      Nominal setting
	/// full-rate           -16 ( 11110000)
	/// 1/2 rate                0
	/// 1/4 rate                0
	/// 1/8 rate                0
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cphsofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{14,"cphsofst",15,8}
	};
	return reg;
}

	/// Edge phase offset. A 2's complement value (-128 to 127) to adjust the edge phase when the CDR is frozen.  Can be used to slip one or multiple bits of RXD. To do bit slip, freeze the CDR first. Then write +/-32for +/-1UI move, or +/-64 for +/-2UI or +127/-128 for +/-4UI . For more than 4UI move, use multiple commands.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ephsofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{14,"ephsofst",7,0}
	};
	return reg;
}

	/// Transition density detection enable. When disabled, all transition density detection logic is reset.
	/// 0 = Disable transition density detector
	/// 1 = Enable transition density detector
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::tdden(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"tdden",15,15}
	};
	return reg;
}

	/// Set the threshold for transition density detector.
	/// 000 = 32          100 = 512
	/// 001 = 64          101 = 1024
	/// 010 = 128        110 = 2048
	/// 011 = 256        111 = 4096
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::tddthr(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"tddthr",14,12}
	};
	return reg;
}

	/// Eye scan based LOS detection enable.
	/// 0 = Disable eye scan based LOS detection
	/// 1 = Enable eye scan based LOS detection
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::loseyeen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"loseyeen",11,11}
	};
	return reg;
}

	/// Eye scan based LOS threshold.
	/// 00 = 12 vertical/2 horizontal steps
	/// 01 = 28 vertical/4 horizontal steps
	/// 10 = 44 vertical/8 horizontal steps
	/// 11 = 60 vertical/16 horizontal steps
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::loseyethr(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"loseyethr",10,9}
	};
	return reg;
}

	/// Set 1 to clear an internal 42-bit timer counter to 0. This bit works together with TIMECNTSTART.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::timecntclr(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"timecntclr",8,8}
	};
	return reg;
}

	/// LOS configuration.
	/// LOSCFG[2]:
	/// 0 = LOS pin is a real time status of the transition density detector
	/// 1 = LOS pin is a latched status of the transition density detector (clear after read)
	/// LOSCFG[1:0]:
	/// 00 = Both LOS pin and LOS register bit (RX CSR15[4] below) will be set to high when there are no enough transitions.
	/// 01 = Both LOS pin and LOS register bit  will be set to high when inner eye is not open enough vertically.
	/// 10 = Both LOS pin and LOS register bit  will be set to high when inner eye is not open enough horizontally.
	/// 11 = Both LOS pin and LOS register bit will be set to high when there are no enough transitions, or inner eye is not open enough either vertically or horizontally.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::loscfg(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"loscfg",7,5}
	};
	return reg;
}

	/// Loss of signal indication. This bit will be set to 1 when inadequate RX signal (the transition density falls below TDDTHR[2:0]) is detected or eye is not open enough vertically or horizontally after an eye scan, depending on the LOS configuration (RX CSR15[7:5] LOSCFG above).
	/// 0 = Adequate RX signal (transitions) or eye opening.
	/// 1 = Inadequate RX signal (transitions) or eye openning.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::los(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"los",4,4}
	};
	return reg;
}

	/// Transition density based Loss of signal indication (Clear on read).
	/// 0 = Transition density is above preset threshold.
	/// 1 = Transition density falls below preset threshold.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::lostran(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"lostran",3,3}
	};
	return reg;
}

	/// Eye scan based (vertical) loss-of-signal indication.
	/// 0 = Vertical opening of last inner eye scan is bigger than the threshold.
	/// 1 = Vertical opening of last inner eye scan is less than the threshold.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::loseyever(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"loseyever",2,2}
	};
	return reg;
}

	/// Eye scan based (horizontal) loss-of-signal indication.
	/// 0 = Horizontal opening of last inner eye scan is bigger than the threshold.
	/// 1 = Horizontal opening of last inner eye scan is less than the threshold.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::loseyehor(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"loseyehor",1,1}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::losana(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"losana",0,0}
	};
	return reg;
}

	/// Set 1 to start an internal 42-bit timer. Self cleared when the timer is full. The timer can be stopped at any time by writing 0 to this register.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::timecntstart(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{16,"timecntstart",15,15}
	};
	return reg;
}

	/// set  IQ offset for the monitor channel (2's complement value)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::moniqofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{16,"moniqofst",14,8}
	};
	return reg;
}

	/// 0=normal, using center data for prbs detection
	/// 1= using monitor data for prbs detection
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::prbsemdatasel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{16,"prbsemdatasel",7,7}
	};
	return reg;
}

	/// Voltage offset polarity control for ISI calculation.
	/// 0 = Normal
	/// 1 = Invert
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::volofstpol(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{16,"volofstpol",6,6}
	};
	return reg;
}

	/// PRBS checker enable.
	/// 0 = Disable (default)
	/// 1 = Enable
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::prbschken(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{16,"prbschken",5,5}
	};
	return reg;
}

	/// PRBS checker mode.
	/// 0 = Synchronous mode. In this mode, the PRBS checker is synchronized with the input data (i.e., feeding the PRBS checker with the input data).
	/// 1 = Free running mode.
	/// Normally, the PRBS checker should be set in synchronous mode. Once the PRBS checker is synchronized (no error detected), it can be switched to free running mode to prevent error propagation during error detection.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::prbschkmode(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{16,"prbschkmode",4,4}
	};
	return reg;
}

	/// PRBS pattern select for the PRBS checker: 
	/// 0000 = PRBS7 (X7+X6+1)
	/// 0001 = PRBS9 (X9+X5+1)
	/// 0010 = PRBS10 (X10+X7+1)
	/// 0011 = PRBS11 (X11+X9+1)
	/// 0100 = PRBS15 (X15+X14+1)
	/// 0101 = PRBS20 (X20+X17+1)
	/// 0110 = PRBS23 (X23+X18+1)
	/// 0111 = PRBS31 (X31+X28+1)
	/// 1000 = 1-0-1 pattern
	/// 1001 to 1111 = Disabled
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::prbschkpatsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{16,"prbschkpatsel",3,0}
	};
	return reg;
}

	/// Rx monitor channel power down control. Active low.
	/// Now used in Digital RTL only.   See also RXCPMONPWRDB and RXCPMONQPWRDB
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyemonpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{17,"eyemonpwrdb",15,15}
	};
	return reg;
}

	/// Eye scan START/STOP control
	/// 0 = Stop
	/// 1 = Start. Self clear after eye scan is done.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyescanstart(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{17,"eyescanstart",14,14}
	};
	return reg;
}

	/// Eye monitor status
	/// 0 = not ready for scan
	/// 1 = ready for scan
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::emready(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{17,"emready",13,13}
	};
	return reg;
}

	/// The status of last eye monitor task.
	/// 0 = Succeeded;  1 =  Failed
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::emtaskstatus(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{17,"emtaskstatus",12,12}
	};
	return reg;
}

	/// Eye scan mode.
	/// 000: Auto horizontal inner eye scan;  10x: Manual inner eye scan
	/// ;001: Auto vertical inner eye scan;  11x: Manual outer eye scan
	/// ;010: Auto horizontal outer eye scan;   011: Auto vertical outer eye scan
	/// 
	/// ;     For automatic horizontal eye scan, eye monitor sweeps horizontally at a certain voltage setting set by MVOLOFST[8:0] to find the inner most eye corners (left and right) at a given BER. The horizontal starting point is programmable through MPHSOFST[7:0]. If starting from inside, the eye monitor continues left and right with a linear search and returns both left and right corners when completes;  otherwise, continues left and right with a linear search until the eye boundaries are found or the bound limits are reached, and returns both corners (left and right) or one corner (left = right), or flags the scan has failed to find corners.
	///      For automatic vertical eye scan, eye monitor sweeps vertically at a certain phase setting set by MPHSOFST[7:0] to find the inner most eye corners (lower and upper) at a given BER. The vertical starting point is controlled by the eye monitor, i.e., not programmable. If starting from inside of the eye, the scan continues with a binary search and returns both upper and lower corners when completes; otherwise, it continues up and down with a linear search until the eye boundaries are found or the bound limits are reached, and returns both corners (upper and lower) or one corner (upper = lower), or flags the scan has failed to find corners. It is also possible to force to use the linear search only which would be very time consuming. For the linear search, the eye monitor can jump with a programmable voltage offset  steps (2, 4, 8,16 and etc.) to speed up the search.
	///      For manual eye scan, the user has full control over how to measure the eye. Both phase and voltage settings are programmable through MPHSOFST[7:0] and MVOLOFST[8:0] respectively. They need to be set before the scan starts
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyescanmode(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{17,"eyescanmode",11,9}
	};
	return reg;
}

	/// 0 = indicates normal corner values returned
	/// 1 = indicates that EM voltage offset is already at the max value but BER contour not satisfied
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::emvolovrmax(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{17,"emvolovrmax",8,8}
	};
	return reg;
}

	/// Creates a composite result out of a one dlev(1,1) scan and one dlev(1,0) scan.
	/// 0 = Composite area is disabled; 
	/// 1 = Composite area scan is enabled
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::compeyeen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{17,"compeyeen",7,7}
	};
	return reg;
}

	/// Eye scan window select.
	/// 0 = Choose normal eye scan window
	/// 1 = Choose extended eye scan window
	/// Note: extended eye scan window is used to get more accurate and fine tuned results. It requires longer time to scan the eye. So it should be used wisely.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyescanwinsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{17,"eyescanwinsel",6,6}
	};
	return reg;
}

	/// Eye scan window. bit[5] is reserved for future use.
	///     For automatic inner eye scan (both horz and vert), it sets the eye scan window, i.e., the number of words to be checked for a mismatch, which is calculated as (4*SCALE* 2powEYESCANWINSEL* 2powEYESCANWIN[4:0]), where SCALE=8. To speed up the scan, we may look at a smaller scan window first, which is calculated as (SCALE* 2powEYESCANWINSEL*  2powEYESCANWIN[4:0] ). When reaching the edge of the eye, we need to use the big scan window to fine tune the edge. Fine tuning is not needed for the vertical scan is the binary search is chosen. For half, quarter and octal rates and full rates with the tap 1 enabled, calculations need to be scaled accordingly so that the target BER stays the same.   For automatic outer eye scan, it auto sets the allowed mismatch limit (no of bits), which is calculated as (64*SCALE* 2powEYESCANWINSEL* EYESCANWIN[4:0]), where SCALE = 16, within a fixed eye scan window which is calculated as (4*64*SCALE* 2powEYESCANWINSEL). For half, quarter and octal rates and the full rate with the tap 1 enabled, calculations need to be scaled accordingly so that the target BER stays the same. There is also an option to allow both the mismatch limit and the scan window to be fully controlled manually. In this case, the mismatch limit is set by MMTHR[15:0], while the scan window is calculated as (2powEYESCANWIN[4:0]). Scaling is not needed for half, quarter and octal rates and the full rate with the tap 1 enabled.  For manual inner eye scan, eye monitor keeps comparing the monitor data with the recovered data at certain MPHSOFST[7:0] and MVOLOFST[7:0] settings until a mismatch is found or the scan is stopped by writing EYESCANSTART to '0'.  For manual outer eye scan, it sets the measurement window, i.e., the number of words counted for mismatch and ISI error accumulation, which is calculated as (16*32*EYESCANWIN[3:0]).
	///      When the extended eye scan window mode is enabled, all above eye scan window and mismatch limit values are doubled except the BER is manually selected.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyescanwin(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{17,"eyescanwin",5,0}
	};
	return reg;
}

	/// Eye monitor phase offset w.r.t. the nominal eye center (2's complement value).
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mphsofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{18,"mphsofst",8,0}
	};
	return reg;
}

	/// set  IQ offset for the center channel
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ceniqofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{19,"ceniqofst",15,9}
	};
	return reg;
}

	/// Selects which channel to scan in the eye monitor.
	/// 00 = select I (phase 0) , only valid in full rate mode
	/// 01 = select Q (phase 90), valid in all rate mode
	/// 10 = select Ib (phase 180), only valid in full rate mode
	/// 11 =  select Qb (phase 270), valid in full rate and half rate mode
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::monslcsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{19,"monslcsel",8,7}
	};
	return reg;
}

	/// set IQ offset for the edge channel
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::edgiqofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{19,"edgiqofst",6,0}
	};
	return reg;
}

	/// PRBS checker error status. The bit is set to 1 when at least one error is detected. Status is latched until being read (clear on read).
	/// 0 = No errors detected.
	/// 1 = At least 1 error detected by the PRBS detector.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::prbserr(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{20,"prbserr",15,15}
	};
	return reg;
}

	/// PRBSCNTEXP[3:0] gives the exponent portion of the 26 bit error counter. (clear on read)
	/// 0 = total error is PRBSCNT
	/// 1-15 = total error is 2pow(10+PRBSCNTEXP)+PRBSCNT*2(PRBSCNTEXP-1)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::prbscntexp(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{20,"prbscntexp",14,11}
	};
	return reg;
}

	/// PRBS error count
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::prbscnt(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{20,"prbscnt",10,0}
	};
	return reg;
}

	/// Set mismatch threshold for eye scan (only the enhanced basic eye scan).  If MMTHR[15:0] = 0, the mismatch threshold will be determined by EYESCANWIN[5:0].  If MMTHR[15:0] is not equal to 0, the BER used for eye scan is calculated as  BER = MMTHR[15:0]/(2powEYESCANWIN*NBITS), which applies all rate modes and whether or not the tap 1 is enabled. EYESCANWINSEL will not take effect in this case.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mmthr(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{21,"mmthr",15,0}
	};
	return reg;
}

	/// Currently Not supported in v101 (Reserved for four eye scan selection)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::emfoureyesel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{22,"emfoureyesel",13,12}
	};
	return reg;
}

	/// Eye monitor voltage offset (2's complement value).
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mvolofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{22,"mvolofst",8,0}
	};
	return reg;
}

	/// For basic eye scan:
	/// bits[8:0] ?Left  or lower corner of the most recent automatic horizontal/vertical eye scan.
	/// 
	/// For peak detection:
	/// bits[8:0] ?Left  or lower corner  associated with the maximum detected peak.
	/// 
	/// For area calculation:
	/// bits[8:0] ?Not used.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::emresult0(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{23,"emresult0",8,0}
	};
	return reg;
}

	/// For basic eye scan:
	/// bits[8:0] ?Right  or upper corner of the most recent automatic horizontal/vertical eye scan.
	/// 
	/// For peak detection,
	/// bits[8:0] ?Right  or upper corner  associated with the maximum detected peak.
	/// 
	/// For area calculation,
	/// bits[8:0] ?Not used.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::emresult1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{24,"emresult1",8,0}
	};
	return reg;
}

	/// Only applies to the enhanced basic eye scan.
	/// bit[3]  Vertical scan algorithm.  0= automatic choose binary or linear; 1=linear search.
	/// bits[2:0]  Vertical scan step.
	/// 000 = 1 step;    001 =  2 steps;   010 =  4 steps;      
	/// 011 = 8 steps;  100 = 16 steps;  101 = 64 steps;   
	/// 110 = 128 steps;  111 =  256 steps
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyescanctrl(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{25,"eyescanctrl",15,12}
	};
	return reg;
}

	/// 0000 = Basic eye scan             
	/// 0001 = Peak detection
	/// 0010 = Area calculation
	/// 0011 = Four eye capturing (currently not supported in V101)
	/// 0100 - 1111 = Reserved
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyemontask(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{25,"eyemontask",11,8}
	};
	return reg;
}

	/// 0: Basic eye scan algorithm (compatible with H30 V100)
	/// 1: Enhanced basic eye scan algorithm
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyescanalg(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{25,"eyescanalg",7,7}
	};
	return reg;
}

	/// For the extended basic eye scan:
	/// bits[4:0] ?Not used.    
	///                                                                                                 
	/// For peak detection:
	/// bits[4:3] ?00 = WL/WR or HL/HU are auto-discovered  and
	/// then the [WL, WR]  or [HL, HU] range  is searched; 01 =  Search 1 UI going to the left and 1 UI going      
	/// to the right;  10 = Search 1/2 UI going to the left                            
	/// and 1/2 UI going to the right; 11 = WL/WR or HL/HU are
	/// provided from user registers (see EMSWCORNER0[8:0], EMSWCORNER1[8:0])
	/// bit[2] ?Peak detection algorithm. 1 = Exhaustive search
	/// ;0 = Fast search (i.e., the first maximal peak is returned)
	/// ;bits[1:0] ?Phase or voltage step(s)  to jump during peak
	/// Detection: 00 = 1 step;  01 = 4 steps;  10 =  8 steps;  11 = 15 steps
	/// 
	/// For area calculation:
	/// bit[4] ?Set the WL/WR corners using EMSWCORNER0/1 registers
	/// bit[3] ?Area calculation scaling factor. 0 = No scaling
	/// ;1 = Scale down by 2 the corner values
	/// bits[2:0] ?Area calculation points which is calculated 
	/// as 4*EMTASKCTRL[2:0].
	/// 
	/// For waveform scope:
	/// bit[4] ?Not used;  bit[3] ?Read next segment
	/// ;bit[2] ?Reference sample is based on a 0 to 1 transition
	/// ;bits[1:0] - Number of phase offsets to sample using a step of 2pow[1:0] starting from �UI going to +UI.
	///  For four consecutive eye capturing: not supported in V101
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::emtaskctrl(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{25,"emtaskctrl",6,2}
	};
	return reg;
}

	/// scaling factor for returned EM corner values
	/// 0: no scaling
	/// ;1: corners are scaled to full rate range
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::emcornerscaling(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{25,"emcornerscaling",1,1}
	};
	return reg;
}

	/// 1 enables em corner guard to ensure corner1 is always on the left or lower side
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::emcornergrden(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{25,"emcornergrden",0,0}
	};
	return reg;
}

	/// Wait time for analog to settle during eye monitor Voltage scan
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::monvolscanstltime(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{26,"monvolscanstltime",7,0}
	};
	return reg;
}

	/// Eye monitor task averaging control.
	/// bits[3:2] ?Selects an average function between arithmetical mean and mode (most frequent number)
	/// 00 = Performs the arithmetical mean over [1:0] samples, both vertical and horizontal scans
	/// 01 = Returns the mode (most frequent number) over [1:0] samples, both vertical and horizontal scans
	/// 10 = Returns the mode  for horizontal scans and the mean for vertical scans, over [1:0] samples
	/// 11 = Reserved
	/// bits[1:0] ?Number of samples to collect
	/// 00 = 1 sample;  01 = 8  samples;  10 = 16 samples;  11 = 32 samples;
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::emtaskavrg(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{27,"emtaskavrg",15,12}
	};
	return reg;
}

	/// Tap1 related offset value to be added to the EMRESULT0[15:0] value. Only valid when the tap 1 is enabled.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cornerofst0(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{27,"cornerofst0",8,0}
	};
	return reg;
}

	/// Tap1 related offset value to be added to the EMRESULT1[15:0] value. Only valid when the tap 1 is enabled.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cornerofst1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{28,"cornerofst1",8,0}
	};
	return reg;
}

	/// For basic eye scan:
	/// bits[15:0] ?Not used.
	/// 
	/// For peak detection:
	/// bits[15:9] - Not used
	/// bits[8:0] ?Phase or voltage offsets associated with the maximum detected peak.
	/// 
	/// For area calculation:
	/// bits[15:0] ?Value of the calculated area.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::emresult2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{29,"emresult2",15,0}
	};
	return reg;
}

	/// Eye monitor scan max voltage offset setting.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mvolmax(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{30,"mvolmax",8,0}
	};
	return reg;
}

	/// RX termination calibration value selection
	/// 0 = value from dpm control line (from Service Slice where cal replica block is located)
	/// 1 = value from regiser RXTERMCAL
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxtermcalsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{31,"rxtermcalsel",15,15}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxtermcaldir(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{31,"rxtermcaldir",14,14}
	};
	return reg;
}

	/// Rx latch offset range scale.
	/// 0: Normal offset range
	/// 1: Normal * 0.7 offset range
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxlatofstrangescale(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{31,"rxlatofstrangescale",13,13}
	};
	return reg;
}

	/// Select calibration mode for the CTLE Replica Opamp.
	/// 0 = open loop
	/// ;1 = closed loop.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxctlerepopcalmode(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{31,"rxctlerepopcalmode",12,12}
	};
	return reg;
}

	/// Manual input  of Calibration bits for termination resistor. 
	/// 0000 =  High impedance setting
	/// 0001 =  Highest calibrated resistance setting
	/// ��...
	/// 1110 = Lowest calibrated resistance setting
	/// 1111 =  same as above
	/// 
	/// For Typical Corner: 4'b0101: ~50Ohm, 4'b0111: ~45Ohm
	/// (Mode selected  by  register  RXTERMCALSEL)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxtermcal(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{31,"rxtermcal",3,0}
	};
	return reg;
}

	/// RX calibration mode. Switching from manual mode to automatic mode restarts the calibration process.
	/// 0 = Automatic calibration
	/// 1 = Manual calibration
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcalmode(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{32,"rxcalmode",15,15}
	};
	return reg;
}

	/// Data Slice calibration start control. Used only in automatic and semi-automatic modes.
	/// 0 = Do not start data slice calibrations
	/// 1 = Start all data slice calibrations (automatic way). Self clear after calibration is done.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dscalstart(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{32,"dscalstart",14,14}
	};
	return reg;
}

	/// RX calibration start control. Used only in automatic and semi-automatic modes.
	/// 0 = Do not start RX calibrations
	/// 1 = Start RX calibrations. Self clear after calibration is done.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcalstart(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{32,"rxcalstart",13,13}
	};
	return reg;
}

	/// Termination floating enable 
	/// 0 = connect RX termination common mode reference point to GND
	/// 1= floating RX termination common mode reference point 
	/// (defaults and description different from v100)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxtermfloating(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{32,"rxtermfloating",12,12}
	};
	return reg;
}

	/// Latch offset calibration enable
	/// 0 = Skip offset calibration for center, edge and monitor channel latches during the automatic calibration process
	/// 1 = Perform offset calibration for center, edge and monitor channel latches during the automatic calibration process
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxdatalatchcalen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{32,"rxdatalatchcalen",7,7}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxofstcaldir(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{32,"rxofstcaldir",6,6}
	};
	return reg;
}

	/// RX OTB select. It chooses analog circuit for offset calibration. Only applies to manual offset calibration mode. 
	/// 000000 = no selection
	/// 000001 = Select CTLE bias block current mirror bias voltage
	/// 000010 = Select CTLE load replica amplifier offset
	/// 000011 = Select CTLE vreg opamp inputs
	/// 000100 = Select CTLE vreg calibration voltages
	/// 000101 = Select VSR CTLE replica ical
	/// 000110 = Select VSR CTLE eq stage 1 ical
	/// 000111 = Select VSR CTLE gain stage 1 ical
	/// 001000 = Select VSR CTLE gain stage 2 ical
	/// 001001 = Select CTLE eq stage 1 offset
	/// 001010 = Select CTLE gain stage 1 offset
	/// 001011 = Select CTLE eq stage 2 offset
	/// 001100 = Select CTLE gain stage 2 offset
	/// 001101 = Select CTLE eq stage 3 offset
	/// 001110 = Select CTLE gain stage 3 offset
	/// 001111 = Select DFE summer supply
	/// 010000 = Select DFE I even summer offset
	/// 010001 = Select DFE Q even summer offset
	/// 010010 = Select DFE I odd  summer offset
	/// 010011 = Select DFE Q odd  summer offset
	/// 010100 =  Unassigned, Not connected
	/// 010101 = I-even summer restrim calibration voltages
	/// 010110 = RX IQ detector voltages
	/// 011111 to 111111 = Unassigned, Not connected
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxofstsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{32,"rxofstsel",5,0}
	};
	return reg;
}

	/// CLTE stage 1 offset control. Used for manual offset calibration.
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset ,
	/// 0000 = no offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleofst1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{33,"ctleofst1",14,10}
	};
	return reg;
}

	/// CLTE stage 2 offset control. Used for manual offset calibration. 
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset ,
	/// 0000 = no offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleofst2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{33,"ctleofst2",9,5}
	};
	return reg;
}

	/// CLTE stage 3 offset control. Used for manual offset calibration. 
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset ,
	/// 0000 = no offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleofst3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{33,"ctleofst3",4,0}
	};
	return reg;
}

	/// CLTE stage 4 offset control. Used for manual offset calibration. 
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset ,
	/// 0000 = no offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleofst4(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{34,"ctleofst4",14,10}
	};
	return reg;
}

	/// CLTE stage 5 offset control. Used for manual offset calibration. 
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset ,
	/// 0000 = no offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleofst5(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{34,"ctleofst5",9,5}
	};
	return reg;
}

	/// CLTE stage 6 offset control. Used for manual offset calibration. 
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset ,
	/// 0000 = no offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleofst6(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{34,"ctleofst6",4,0}
	};
	return reg;
}

	/// Isum Ieven offset,
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset ,
	/// 0000 = Minimum offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfeievnsumofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{35,"dfeievnsumofst",14,10}
	};
	return reg;
}

	/// Isum Iodd offset,
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset (binary),
	/// 0000 = Minimum offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfeioddsumofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{35,"dfeioddsumofst",9,5}
	};
	return reg;
}

	/// Isum Qeven offset,
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset (binary),
	/// 0000 = Minimum offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfeqevnsumofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{35,"dfeqevnsumofst",4,0}
	};
	return reg;
}

	/// Isum Qodd offset,
	/// 
	/// bit[4] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[3:0] - magnitude of offset (binary),
	/// 0000 = Minimum offset
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum offset
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfeqoddsumofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{36,"dfeqoddsumofst",14,10}
	};
	return reg;
}

	/// rxctle current scaling control
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxctleibiastune(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{36,"rxctleibiastune",7,5}
	};
	return reg;
}

	/// resistive tuning for passive midband freq shaping function
	/// 000 = lowest resistor setting (highest zero freq location)
	/// 111 = highest resistor setting (lowest zero freq location)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxctlepasstune(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{36,"rxctlepasstune",2,0}
	};
	return reg;
}

	/// set iptat temperature compensation coefficient
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleiptattcctrl(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{37,"ctleiptattcctrl",11,8}
	};
	return reg;
}

	/// bypass programmable iptat bias
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleiptatbypass(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{37,"ctleiptatbypass",6,6}
	};
	return reg;
}

	/// enable clock to for SC resistor
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlescresen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{37,"ctlescresen",5,5}
	};
	return reg;
}

	/// Divider ratio to generate SC resistor clock. divider ratio is continuous from 1 to 31
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlescresclkdiv(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{37,"ctlescresclkdiv",4,0}
	};
	return reg;
}

	/// power down  ALOS detection stage, active low
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxsigdetpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{38,"rxsigdetpwrdb",15,15}
	};
	return reg;
}

	/// select divide ratio for high speed sampling clock (input ref clk is HSCLK/2)
	/// 00 = div by 2
	/// 01 = div by 4
	/// 10 = div by 16
	/// 11 = div by 8
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxsigdetclkdiv(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{38,"rxsigdetclkdiv",14,13}
	};
	return reg;
}

	/// clk delay offset for complimentary sampling channel
	/// 0 = PCIE/common
	/// 1 = SATA/SAS
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxsigdetclkdlysel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{38,"rxsigdetclkdlysel",12,12}
	};
	return reg;
}

	/// power down ALOS buffer stage, active low
	/// 0 = ALOS calibration mode
	/// 1 = ALOS mission mode
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxsigdetcalpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{38,"rxsigdetcalpwrdb",10,10}
	};
	return reg;
}

	/// enable high speed clock path, active high
	/// 0 = disable
	/// 1= enable high speed clock path
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxdigdetclkbufen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{38,"rxdigdetclkbufen",9,9}
	};
	return reg;
}

	/// connect input stage buffer outputs to the otb bus
	/// 0 = disconnect
	/// 1= connect
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxsigdetatbsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{38,"rxsigdetatbsel",8,8}
	};
	return reg;
}

	/// set signal detection threshold 
	///  (changed in v101)
	/// bit[3]  sign bit
	/// 0= positive
	/// 1= negative
	/// bit[2:0]  magnitude of threshold
	/// 000= min
	/// 001=
	/// 010=
	/// ��
	/// 111=max
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxsigdetvthres(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{39,"rxsigdetvthres",13,10}
	};
	return reg;
}

	/// signal detection hysteresis adjust (new in v101)
	/// 00: no hysterisis
	/// 11: max hysterisis
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxsigdethyst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{39,"rxsigdethyst",9,8}
	};
	return reg;
}

	/// alos buffer offset control. Used for manual offset calibration.  
	/// Bit[4]: sign bit of magnitude
	/// 0= positive
	/// 1= negative
	/// 
	/// bits[3:0]= offset magnitude
	/// 0000 = zero offset 
	/// 0001 = 
	/// ..
	/// 1111 = max offset
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxsigdetoffset(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{39,"rxsigdetoffset",4,0}
	};
	return reg;
}

	/// Status of Squelch detection. Result is only available in sata/sas mode
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdetsqlchlos(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{40,"sigdetsqlchlos",15,15}
	};
	return reg;
}

	/// Status of signal loss detection. Results is only available in PCIE or common mode
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdetlos(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{40,"sigdetlos",14,14}
	};
	return reg;
}

	/// function not implemented. Should set to 1.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdettxrxstat(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{40,"sigdettxrxstat",13,13}
	};
	return reg;
}

	/// Signal and squelch detection window 4*2powSIGDETWIN
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdetwin(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{40,"sigdetwin",11,8}
	};
	return reg;
}

	/// 01 =  enables signal detect sata mode
	/// x0/11 = enables common mode or PCI mode
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdetpmamode(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{40,"sigdetpmamode",6,5}
	};
	return reg;
}

	/// 0 =  threshold is controled by SIGDETTHRCFGSEL[2:0]
	/// 1 = threshold is set by SIGDETTHRSELMAN[2:0]
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdetmanual(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{40,"sigdetmanual",4,4}
	};
	return reg;
}

	/// Manual selection for signal detect and squelch threshold value.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdetthrselman(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{40,"sigdetthrselman",3,1}
	};
	return reg;
}

	/// Enable for Signal detect and Squelch
	/// 0 = function disabled
	/// 1 = function enabled
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdeten(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{40,"sigdeten",0,0}
	};
	return reg;
}

	/// 1xx/000 = signal detect threshold is set by SIGDETTHRS3
	/// 01x = signal detect threshold is set by SIGDETTHRS2
	/// 001 = signal detect threshold is set by SIGDETTHRS1
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdetthrcfgsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{41,"sigdetthrcfgsel",14,12}
	};
	return reg;
}

	/// signal detect threshold parameter3. suited for 2.5/5G pcie mode
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdetthrs1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{41,"sigdetthrs1",10,0}
	};
	return reg;
}

	/// signal detect threshold parameter3. suited for all sata/sas
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdetthrs2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{42,"sigdetthrs2",10,0}
	};
	return reg;
}

	/// signal detect threshold parameter3. suited to pcie 8G in pcie mode or common mode
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdetthrs3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{43,"sigdetthrs3",10,0}
	};
	return reg;
}

	/// Analog status for RX CTLE load replica block opamp offset calibration trigger
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxctlerepofftrig(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{44,"rxctlerepofftrig",15,15}
	};
	return reg;
}

	/// Power down control of CTLE stage 1 to 4.
	/// 0 = Power down.
	/// 1=  Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlestg1to4pwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{44,"ctlestg1to4pwrdb",14,14}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::replicacaldir(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{44,"replicacaldir",13,13}
	};
	return reg;
}

	/// Select configuration for CTLE load replica opamp
	/// 0 =   configure CTLE replica opamp for open-loop offset calibration.
	/// 1 =  configure CTLE replica opamp for mission-mode operation
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlerepcalen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{44,"ctlerepcalen",12,12}
	};
	return reg;
}

	/// Offset control for CTLE load replica. Used for manual offset calibration. 
	/// bit[5] - sign bit,
	/// 0 = Positive
	/// 1 = Negative
	/// 
	/// bit[4:1] - magnitude of offset,
	/// 111 = Maximum offset
	/// 000 = no offset 
	/// 
	/// bit[0] - Not used
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlerepcalcode(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{44,"ctlerepcalcode",11,6}
	};
	return reg;
}

	/// select CTLE replica reference voltage
	/// Voltage is relative to CTLE local supply (vreg)
	/// 000 =  vreg - 190mV
	/// 001 =  vreg - 200mV
	/// 010 =  vreg - 210mV
	/// 011 =  vreg - 220mV
	/// 100 =  vreg - 230mV
	/// 101 =  vreg - 240mV
	/// 110 =  vreg - 250mV
	/// 111 =  vreg - 260mV
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlerefsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{44,"ctlerefsel",5,3}
	};
	return reg;
}

	/// CTLE replica output mux control bits. 
	/// 
	/// 000:  Opamp output is selected (normal operation mode)
	/// 001:  lvcc
	/// 010:  vss
	/// 011:  0.57V
	/// 100:  0.47V
	/// 101:  0.36V
	/// 110:  0.31V
	/// 111:  0.26V
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleloadsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{44,"ctleloadsel",2,0}
	};
	return reg;
}

	/// DS power sequence time between steps for regulators(TBS3)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dspwrsqtbs3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{45,"dspwrsqtbs3",13,10}
	};
	return reg;
}

	/// Set Comparator reference voltage selection for  CTLE regulator voltage calibration
	/// Calib Target (mV)= 600 * (1+vregctlerefsel/64)
	/// Note: CTLEVREGVREFRNG[1:0] must be correspondingly set to a range which supports the calibration target value
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::vregctlerefsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{45,"vregctlerefsel",9,4}
	};
	return reg;
}

	/// Center I-Channel sampling clock delay control 
	/// 00 = no delay
	/// 01 = 175fs
	/// 10 = 350fs
	/// 11 = 550fs
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpcendlyctrli(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{45,"rxcpcendlyctrli",3,2}
	};
	return reg;
}

	/// Center Q-Channel sampling clock delay control 
	/// 00 = no delay
	/// 01 = 175fs
	/// 10 = 350fs
	/// 11 = 550fs
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpcendlyctrlq(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{45,"rxcpcendlyctrlq",1,0}
	};
	return reg;
}

	/// Rx center channel clocking path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpcenpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{46,"rxcpcenpwrdb",15,15}
	};
	return reg;
}

	/// Powerdown for center I-channel PI CML buffer stage.
	/// (Gated by RXCPCENPWRDB)
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpcenipibufpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{46,"rxcpcenipibufpwrdb",13,13}
	};
	return reg;
}

	/// Powerdown for center I-channel PI CML2CMOS  stage.
	/// (Gated by RXCPCENPWRDB)
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpcenipicmlcmospwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{46,"rxcpcenipicmlcmospwrdb",12,12}
	};
	return reg;
}

	/// Powerdown for center I-channel PI core  stage.
	/// (Gated by RXCPCENPWRDB)
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpcenipicorepwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{46,"rxcpcenipicorepwrdb",11,11}
	};
	return reg;
}

	/// Powerdown for center Q-channel PI CML buffer stage.
	/// (Gated by RXCPCENPWRDB)
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpcenqpibufpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{46,"rxcpcenqpibufpwrdb",10,10}
	};
	return reg;
}

	/// Powerdown for center Q-channel PI CML2CMOS  stage.
	/// (Gated by RXCPCENPWRDB)
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpcenqpicmlcmospwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{46,"rxcpcenqpicmlcmospwrdb",9,9}
	};
	return reg;
}

	/// Powerdown for center Q-channel PI core  stage.
	/// (Gated by RXCPCENPWRDB)
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpcenqpicorepwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{46,"rxcpcenqpicorepwrdb",8,8}
	};
	return reg;
}

	/// Rx center channel PI  bias current scale. 
	/// 00 = Maximum current
	/// 11 = Minimum current
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpcenpibiastrim(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{46,"rxcpcenpibiastrim",5,4}
	};
	return reg;
}

	/// Rx center channel PI buffer bias current scale. 
	/// 00 = Minimum current
	/// 11 = Maximum current
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpcenpibufbiastrim(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{46,"rxcpcenpibufbiastrim",3,2}
	};
	return reg;
}

	/// Rx center channel PI buffer load resistance control. 
	/// 00 = Minimum load resistance
	/// 11 = Maximum load resistance
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpcenpibufloadtrim(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{46,"rxcpcenpibufloadtrim",1,0}
	};
	return reg;
}

	/// Rx edge channel clocking path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpedgpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{47,"rxcpedgpwrdb",15,15}
	};
	return reg;
}

	/// Powerdown for edge I-channel PI CML buffer stage.
	/// (Gated by RXCPEDGPWRDB)
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpedgipibufpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{47,"rxcpedgipibufpwrdb",14,14}
	};
	return reg;
}

	/// Powerdown for edge I-channel PI CML2CMOS  stage.
	/// (Gated by RXCPEDGPWRDB)
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpedgipicmlcmospwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{47,"rxcpedgipicmlcmospwrdb",13,13}
	};
	return reg;
}

	/// Powerdown for edge I-channel PI core  stage.
	/// (Gated by RXCPEDGPWRDB)
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpedgipicorepwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{47,"rxcpedgipicorepwrdb",12,12}
	};
	return reg;
}

	/// Powerdown for center Q-channel PI CML buffer stage.
	/// (Gated by RXCPEDGPWRDB)
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpedgqpibufpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{47,"rxcpedgqpibufpwrdb",11,11}
	};
	return reg;
}

	/// Powerdown for edge Q-channel PI CML2CMOS  stage.
	/// (Gated by RXCPEDGPWRDB)
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpedgqpicmlcmospwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{47,"rxcpedgqpicmlcmospwrdb",10,10}
	};
	return reg;
}

	/// Powerdown for edge Q-channel PI core  stage.
	/// (Gated by RXCPEDGPWRDB)
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpedgqpicorepwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{47,"rxcpedgqpicorepwrdb",9,9}
	};
	return reg;
}

	/// Edge I-Channel sampling clock delay control 
	/// 00 = no delay
	/// 01 = 175fs
	/// 10 = 350fs
	/// 11 = 550fs
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpedgdlyctrli(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{47,"rxcpedgdlyctrli",8,7}
	};
	return reg;
}

	/// Edge Q-Channel sampling clock delay control 
	/// 00 = no delay
	/// 01 = 175fs
	/// 10 = 350fs
	/// 11 = 550fs
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpedgdlyctrlq(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{47,"rxcpedgdlyctrlq",6,5}
	};
	return reg;
}

	/// Rx center PI spare control bits.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpcenphsgenspare(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{47,"rxcpcenphsgenspare",4,3}
	};
	return reg;
}

	/// Rx edge PI spare control bits.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpedgphsgenspare(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{47,"rxcpedgphsgenspare",2,1}
	};
	return reg;
}

	/// Enable Rx IQ detector  
	/// 0 = detector disabled
	/// 1 = detector enabled
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxiqdetpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{47,"rxiqdetpwrdb",0,0}
	};
	return reg;
}

	/// Rx monitor I-channel clocking path power down control. Active low.
	/// 0: Power down
	/// 1: Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpmonpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{48,"rxcpmonpwrdb",15,15}
	};
	return reg;
}

	/// Rx monitor Q-channel clocking path power down control. Active low.
	/// 0: Power down
	/// 1: Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpmonqpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{48,"rxcpmonqpwrdb",14,14}
	};
	return reg;
}

	/// Powerdown for monitor I-channel PI CML buffer stage.
	/// (Gated by RXCPMONPWRDB)
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpmonipibufpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{48,"rxcpmonipibufpwrdb",13,13}
	};
	return reg;
}

	/// Powerdown for monitor I-channel PI CML2CMOS  stage.
	/// (Gated by RXCPMONPWRDB)
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpmonipicmlcmospwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{48,"rxcpmonipicmlcmospwrdb",12,12}
	};
	return reg;
}

	/// Powerdown for monitor I-channel PI core  stage.
	/// (Gated by RXCPMONPWRDB)
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpmonipicorepwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{48,"rxcpmonipicorepwrdb",11,11}
	};
	return reg;
}

	/// Powerdown for monitor Q-channel PI CML buffer stage.
	/// (Gated by RXCPMONPWRDB)
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpmonqpibufpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{48,"rxcpmonqpibufpwrdb",10,10}
	};
	return reg;
}

	/// Powerdown for monitor Q-channel PI CML2CMOS  stage.
	/// (Gated by RXCPMONPWRDB)
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpmonqpicmlcmospwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{48,"rxcpmonqpicmlcmospwrdb",9,9}
	};
	return reg;
}

	/// Powerdown for monitor Q-channel PI core  stage.
	/// (Gated by RXCPMONPWRDB)
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpmonqpicorepwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{48,"rxcpmonqpicorepwrdb",8,8}
	};
	return reg;
}

	/// Monitor channel  Full (both I and Q  ch) or Partial (only I ch)   power up/down cycle mode when RXMONPWRDB is asserted/deasserted 
	/// 0=  Full monitor channel (both I and Q ch) will power up/down in sequence
	/// 1 = Partial monitor channel (only I ch) will power up/down  in sequence.  Q ch will remain powered down
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxmonpwrcycmode(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{48,"rxmonpwrcycmode",6,6}
	};
	return reg;
}

	/// Monitor I and Q channel power  sequence control (also see RXMONPWRCYCMODE)
	/// 0= power down monitor  channel
	/// 1 = power up monitor channel 
	/// New in v101:  Now used as a trigger to power up/down the Monitor channel circuits in sequence with default settings
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxmonpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{48,"rxmonpwrdb",5,5}
	};
	return reg;
}

	/// Edge channel power sequence control
	/// 0 = power down edge channel
	/// 1 = power up edge channel
	/// New in v101:  Now used as a trigger to power up/down the Edge channel circuits in sequence with default settings
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxedgpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{48,"rxedgpwrdb",4,4}
	};
	return reg;
}

	/// Monitor I-Channel sampling clock delay control 
	/// 00: no delay
	/// 01: 175fs
	/// 10: 350fs
	/// 11: 550fs
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpmondlyctrli(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{48,"rxcpmondlyctrli",3,2}
	};
	return reg;
}

	/// Monitor Q-Channel sampling clock delay control 
	/// 00: no delay
	/// 01: 175fs
	/// 10: 350fs
	/// 11: 550fs
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcpmondlyctrlq(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{48,"rxcpmondlyctrlq",1,0}
	};
	return reg;
}

	/// Rx center slicer I path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::censlcipwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{49,"censlcipwrdb",15,15}
	};
	return reg;
}

	/// Rx center slicer Q path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::censlcqpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{49,"censlcqpwrdb",14,14}
	};
	return reg;
}

	/// Rx center slicer I_b path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::censlcibpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{49,"censlcibpwrdb",13,13}
	};
	return reg;
}

	/// Rx center slicer Q_b path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::censlcqbpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{49,"censlcqbpwrdb",12,12}
	};
	return reg;
}

	/// Rx edge slicer I path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::edgslcipwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{49,"edgslcipwrdb",11,11}
	};
	return reg;
}

	/// Rx edge slicer Q path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::edgslcqpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{49,"edgslcqpwrdb",10,10}
	};
	return reg;
}

	/// Rx edge slicer I_b path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::edgslcibpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{49,"edgslcibpwrdb",9,9}
	};
	return reg;
}

	/// Rx edge slicer Q_b path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::edgslcqbpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{49,"edgslcqbpwrdb",8,8}
	};
	return reg;
}

	/// Rx monitor slicer I path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::monslcipwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{49,"monslcipwrdb",7,7}
	};
	return reg;
}

	/// Rx monitor slicer I_b path power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::monslcibpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{49,"monslcibpwrdb",6,6}
	};
	return reg;
}

	/// Rx center channel demux power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cendemuxpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{49,"cendemuxpwrdb",5,5}
	};
	return reg;
}

	/// Rx edge channel demux power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::edgdemuxpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{49,"edgdemuxpwrdb",4,4}
	};
	return reg;
}

	/// Rx monitor channel demux power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mondemuxpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{49,"mondemuxpwrdb",3,3}
	};
	return reg;
}

	/// Center channel power sequence control
	/// 0 = power down center channel
	/// 1 = power up center channel
	/// New in v101:  Now used as a trigger to power up/down the Center channel circuits in sequence with default settings
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcenpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{49,"rxcenpwrdb",2,2}
	};
	return reg;
}

	/// Rx mon slicer Q path power down control. Active low.
	/// 0: Power down
	/// 1: Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::monslcqpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{49,"monslcqpwrdb",1,1}
	};
	return reg;
}

	/// Rx mon slicer Q_b path power down control. Active low.
	/// 0: Power down
	/// 1: Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::monslcqbpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{49,"monslcqbpwrdb",0,0}
	};
	return reg;
}

	/// 0: selects vcm_refgen output voltage
	/// 1: selects common mode of ieven summer 
	///  Default is to use internally generated reference for alpha IDAC
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfesumvrefsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{50,"dfesumvrefsel",15,15}
	};
	return reg;
}

	/// controls otbm output:
	/// 0: summer outputm is put on otbm (mode to calibrate summer offset)
	/// 1: vcmrefgen is put on otbm (mode to calibrate summer load resistor)
	/// 
	/// Set to 0 to calibrate summer offset
	/// Set to 1 to calibrate summer load resistance
	/// (The same atb control bus is used to select the individual summer output, this bit controls what is put on the otbm output when the summer atb is enabled)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfesumrtrimen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{50,"dfesumrtrimen",14,14}
	};
	return reg;
}

	/// reference range select for rx vregclk regulator
	/// 00 = vref between 750mV  and  850mV
	/// 01 = vref  between 851mV and 925mV
	/// 10 = vref between 926mV and 985mV
	/// 11 = vref between 986mV and 1050mV
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::vregclkvrefrng(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{50,"vregclkvrefrng",13,12}
	};
	return reg;
}

	/// Adjusts bandwidth of  rx vregclk regulator
	/// 00 =  min bandwidth, max gain
	/// ?.
	/// 11 =  max bandwidth, min gain
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::vregclkpreampsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{50,"vregclkpreampsel",11,10}
	};
	return reg;
}

	/// reference range select for rx vregdata regulator
	/// 00 = vref between 750mV  and  850mV
	/// 01 = vref  between 851mV and 925mV
	/// 10 = vref between 926mV and 985mV
	/// 11 = vref between 986mV and 1050mV
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::vregdatavrefrng(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{50,"vregdatavrefrng",9,8}
	};
	return reg;
}

	/// Rx DFE Isummer loading resistance trimming, target to 70ohm. 
	/// 0000 = Minimum load resistance
	/// 0001 =
	/// 0010 =
	/// ..
	/// 1110 = 
	/// 1111 = Maximum load resistance
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfesumrestrim(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{50,"dfesumrestrim",7,4}
	};
	return reg;
}

	/// Enable control of auxiliary offset of Rx DFE summers. Used during latch calibration.
	/// 0 = Disable
	/// 1 = Enable
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfesumauxofsten(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{50,"dfesumauxofsten",3,3}
	};
	return reg;
}

	/// Polarity control of summer output which have auxiliary offset applied.
	/// 0: doutp = 1, doutm = 0
	/// 1: doutp = 0, doutm = 1
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfesumauxofstpol(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{50,"dfesumauxofstpol",2,2}
	};
	return reg;
}

	/// Selection of which summer to apply auxiliary offset.
	/// 00 = Ieven summer
	/// 01 = Qeven summer
	/// 10 = Iodd summer
	/// 11 = Qodd summer
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfesumauxofstsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{50,"dfesumauxofstsel",1,0}
	};
	return reg;
}

	/// Center channel DFE Tap 1 polarity and weight.
	/// 
	/// bit[7] - polarity bit,
	/// 0 = Positive polarity.
	/// 1 = Negative polarity.
	/// 
	/// bit[6:0] - weight
	/// 0000000 = Minimum magnitude (zero)
	/// 0000001 =
	/// 0000010 =
	/// ..
	/// 1111110 = 
	/// 1111111 = Maximum magnitude
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfefxtap1cen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{51,"dfefxtap1cen",15,8}
	};
	return reg;
}

	/// Edge channel DFE Tap 1 polarity and weight.
	/// 
	/// bit[7] - polarity bit,
	/// 0 = Positive polarity.
	/// 1 = Negative polarity.
	/// 
	/// bit[6:0] - weight (binary),
	/// 0000000 = Minimum magnitude (zero)
	/// 0000001 =
	/// 0000010 =
	/// ..
	/// 1111110 = 
	/// 1111111 = Maximum magnitude
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfefxtap1edg(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{51,"dfefxtap1edg",7,0}
	};
	return reg;
}

	/// Rx DFE spare control bit is now Repurposed - 
	/// auxilliary clock divide by 5 mode control
	/// 0: div by 5 mode disabled
	/// 1: div by 5 mode enabled
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfespare(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{52,"dfespare",15,15}
	};
	return reg;
}

	/// Rx DFE tap injector scale control.
	/// 00 = 1mV step
	/// 01 = 1.4mV step
	/// 10 = 2mV step
	/// 11 = 3.5mV step
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfetapinjscale(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{52,"dfetapinjscale",14,13}
	};
	return reg;
}

	/// Rx DFE slicer bandwidth control. 
	/// 00 = Minimum slicer bandwidth
	/// 01 =
	/// 10 =
	/// 11 = Maximum slicer bandwidth
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfeslicerbwsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{52,"dfeslicerbwsel",12,11}
	};
	return reg;
}

	/// Vcm ref voltage for summer load resistance calibration
	/// Vcm_ref(mV) (IR drop from LVCC)
	/// 00 = 165mV   calibrates to 62 Ohms
	/// 01 = 172mV   calibrates to 64 Ohms
	/// 10 = 180mV   calibrates to 66 Ohms (default)
	/// 11 = 187mV   calibrates to 72 Ohms
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxdfesumvreftrim(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{52,"rxdfesumvreftrim",10,9}
	};
	return reg;
}

	/// Rx DFE alphagen resistance trimming. 
	/// 000 = Minimum resistance
	/// 001 =
	/// 010 =
	/// 011 = Maximum resistance
	/// 100 to 111 = Reserved (Not used)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfealphagenrtrim(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{52,"dfealphagenrtrim",8,6}
	};
	return reg;
}

	/// Select Rx DFE alphagen replica block reference voltage  
	/// 000 = Select summer_vref
	/// 001 = lvcc
	/// 010 = lvcc - 35mV
	/// 011 = lvcc - 70mV
	/// 100 = lvcc - 105mV
	/// 101 = lvcc - 140mV
	/// 110 = lvcc - 175mV
	/// 111 = lvcc - 210mV
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfealphagenrefsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{52,"dfealphagenrefsel",5,3}
	};
	return reg;
}

	/// Rx DFE alphagen replica block output mux control bits. 
	/// 000 = Opamp output is selected (normal operation mode)
	/// 001 = hvcc
	/// 010 = vss
	/// 011 = 720mV 
	/// 100 = 720mV
	/// 101 = 540mV
	/// 110 = 360mV
	/// 111 = 180mV
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfealphagenloadsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{52,"dfealphagenloadsel",2,0}
	};
	return reg;
}

	/// Rx clock path regulator power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::vregclkpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{53,"vregclkpwrdb",15,15}
	};
	return reg;
}

	/// Rx clocking regulator output voltage trimming.
	/// 0 = select voltage reference for SS corner
	/// 1 = select voltage reference for TT/FF corner
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::vregclkdpmen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{53,"vregclkdpmen",14,14}
	};
	return reg;
}

	/// Rx clocking regulator bleed current control.
	/// 0: enable bleed current
	/// 1: disable bleed current
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::vregclkbleedb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{53,"vregclkbleedb",13,13}
	};
	return reg;
}

	/// Voltage level control of Rx clocking regulator.  
	/// (default = 0.927V)
	/// 00000 = Minimum voltage.
	/// 00001
	/// 00010
	/// ..
	/// 10100= voltage (default)
	/// ?..
	/// 11111 = Maximum voltage.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::vregclklvl(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{53,"vregclklvl",12,8}
	};
	return reg;
}

	/// Rx data path regulator power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::vregdatapwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{53,"vregdatapwrdb",7,7}
	};
	return reg;
}

	/// Rx data regulator inrush current limit DPM trimming.
	/// 0 = select voltage reference for SS corner
	/// 1 = select voltage reference for TT/FF corner
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::vregdatadpmen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{53,"vregdatadpmen",6,6}
	};
	return reg;
}

	/// Rx data regulator bleed current control.
	/// 0 = enable bleed current
	/// 1 = disable bleed current
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::vregdatableedb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{53,"vregdatableedb",5,5}
	};
	return reg;
}

	/// Voltage level control of Rx data regulator.(Default 0.927V)  
	/// 00000 = Minimum voltage.
	/// 00001 
	/// 00010
	/// ..
	/// 10100= voltage(default)
	/// ?..
	/// 11111 = Maximum voltage.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::vregdatalvl(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{53,"vregdatalvl",4,0}
	};
	return reg;
}

	/// RX clock regulator inrush current limit. Active low.
	/// 0: regulator inrush current limit  mode
	/// 1: regulator mission mode
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::vregclkinrushpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{54,"vregclkinrushpwrdb",15,15}
	};
	return reg;
}

	/// RX data regulator inrush current limit. Active low.
	/// 0: regulator inrush current limit  mode
	/// 1: regulator mission mode
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::vregdatainrushpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{54,"vregdatainrushpwrdb",14,14}
	};
	return reg;
}

	/// Set Comparator reference voltage selection for RX  clock regulator  voltage calibration
	/// Calib Target (mV)= 600 * (1+vregclkrefsel/64)
	/// Note: VREGCLKVREFRNG[1:0] must be correspondingly set to a range which supports the calibration target value
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::vregclkrefsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{54,"vregclkrefsel",13,8}
	};
	return reg;
}

	/// Comparator reference voltage selection for RX data regulator voltage calibration:
	/// Calib Target (mV)= 600 * (1+vregdatarefsel/64)
	/// Note: VREGDATAVREFRNG[1:0] must be correspondingly set to a range which supports the calibration target value
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::vregdatarefsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{54,"vregdatarefsel",5,0}
	};
	return reg;
}

	/// Rx_top ATB selection.
	/// 00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 = Selects Rx otbp bus
	/// 10 = Selects Rx otbm bus
	/// 11 = Disabled
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxatbmuxsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{55,"rxatbmuxsel",15,14}
	};
	return reg;
}

	/// Rx DFE alphagen otbm output selection. Selected signal will go to rx_otbm.
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = Select rx_center_vthrm
	/// 010 = Select rx_edge_vthrm
	/// 011 = Select rx_mon_vthrm  (valid only from V101 IpDrop3.3 onwards)
	/// 100 = Select alphagen_vcm_vref
	/// 101 = Select alphagen_center_vcm  (valid only from V101 IpDrop3.3 onwards)
	/// 110 -111 =  no connect
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfealphagentopmatbctrl(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{55,"dfealphagentopmatbctrl",13,11}
	};
	return reg;
}

	/// Rx DFE alphagen otbp output selection. Selected signal will go to rx_otbp.
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = Select rx_center_vthrp
	/// 010 = Select rx_edge_vthrp
	/// 011 = Select rx_mon_vthrp (valid only from V101 IpDrop3.3 onwards)
	/// 100 = Select  summer_vcm
	/// 101 = Select alphagen_center_vpbias (valid  only from V101 IpDrop3.3 onwards)
	/// 110 -111 =  no connect
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfealphagentoppatbctrl(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{55,"dfealphagentoppatbctrl",10,8}
	};
	return reg;
}

	/// 0 = default
	/// 1 = mute/zero alphagen DAC output
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfealphagencenmute(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{55,"dfealphagencenmute",7,7}
	};
	return reg;
}

	/// 0 = default
	/// 1 = mute/zero alphagen DAC output
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfealphagenedgmute(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{55,"dfealphagenedgmute",6,6}
	};
	return reg;
}

	/// 0 =  default
	/// 1 = mute/zero alphagen DAC output
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfealphagenmonmute(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{55,"dfealphagenmonmute",5,5}
	};
	return reg;
}

	/// [bad key===> "Rx DFE alphagen step size trim
	/// v101:  
	/// 0 = Minimum step size  (2.3mV)
	/// 1 = Maximum step size  ( 4mV)
	/// 
	/// v101 IpDrop3.3 and IpDrop3.4
	/// used in conjunction with DSSPARE[4] to expand programming resolution
	/// { DSSPARE[4], DFEALPHAGENSTEPSIZE }
	/// 00: step size ~ 1.5mV
	/// 01: step size ~ 2.0mV
	/// 10: step size ~ 2.5mV
	/// 11: step size ~ 3.0mV" <====key bad]
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfealphagenstepsize(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{55,"dfealphagenstepsize",4,4}
	};
	return reg;
}

	/// Rx DFE Ibias control. 
	/// 00 = 4.3mA (Minimum bias current)
	/// 01 = 4.5mA
	/// 10 = 5.3mA
	/// 11 = 6.5mA (Maximum bias current)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfesumbias(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{55,"dfesumbias",2,1}
	};
	return reg;
}

	/// enable ptat bias of summer, active high
	/// 0= disable ptat bias
	/// 1 = enable ptat bias
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxdfesumbiasptaten(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{55,"rxdfesumbiasptaten",0,0}
	};
	return reg;
}

	/// Rx clock regulator ATB control. Selected signal will go to rx_otbp.
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = select vref
	/// 010 = select vlow 
	/// 011 = High Impedance
	/// 100 = High Impedance
	/// 101 = select vmid
	/// 110 = select rxclk 2/3 vreg sense
	/// 111 = High Impedance
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::vregclkatbctrl(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{56,"vregclkatbctrl",15,13}
	};
	return reg;
}

	/// Rx data regulator ATB control. Selected signal will go to rx_otbp.
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = select vref
	/// 010 = select vlow
	/// 011 = High Impedance
	/// 100 = High Impedance
	/// 101 = select vmid
	/// 110 = select rxdata 2/3 vreg sense
	/// 111 = High Impedance
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::vregdataatbctrl(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{56,"vregdataatbctrl",12,10}
	};
	return reg;
}

	/// Comparator reference voltage selection for RX supply trim summer calibration:
	/// 000000: Vref=400mV
	/// 000001: Vref=406.25mV
	/// 000010: Vref=412.5mV
	/// ..
	/// 111111: Vref=800mV
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::suptrimsummerrefsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{56,"suptrimsummerrefsel",5,0}
	};
	return reg;
}

	/// 0 = AC-JTAG receiver is controlled by pins
	/// ;1 = AC-JTAG receiver is controlled by register.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtagsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{57,"jtagsel",11,11}
	};
	return reg;
}

	/// RX JTAG Positive output
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtagoutp(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{57,"jtagoutp",10,10}
	};
	return reg;
}

	/// RX JTAG Negative output
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtagoutm(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{57,"jtagoutm",9,9}
	};
	return reg;
}

	/// RX JTAG power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtagpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{57,"jtagpwrdb",8,8}
	};
	return reg;
}

	/// Rx JTAG AC mode enable control.
	/// 0 = Disable AC mode (use DC mode)
	/// 1 = Enable AC mode
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtagacmodeen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{57,"jtagacmodeen",7,7}
	};
	return reg;
}

	/// Rx JTAG initial clock.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtaginitclk(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{57,"jtaginitclk",6,6}
	};
	return reg;
}

	/// Rx JTAG initial P input.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtaginitp(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{57,"jtaginitp",5,5}
	};
	return reg;
}

	/// Rx JTAG initial M input.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtaginitm(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{57,"jtaginitm",4,4}
	};
	return reg;
}

	/// RX JTAG hysteresis threshold control.
	/// Not used for now.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtaghystadj(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{57,"jtaghystadj",3,2}
	};
	return reg;
}

	/// Rx JTAG threshold control. 
	/// 00 = Minimum threshold
	/// 01
	/// 10
	/// 11 = Maximum threshold
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtagthadj(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{57,"jtagthadj",1,0}
	};
	return reg;
}

	/// not used
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ceearly(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{58,"ceearly",15,15}
	};
	return reg;
}

	/// not used
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::celate(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{58,"celate",14,14}
	};
	return reg;
}

	/// Center - Monitor Channel Early status for coarse align
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cmearly(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{58,"cmearly",13,13}
	};
	return reg;
}

	/// Center - Monitor Channel Late status for coarse align
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cmlate(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{58,"cmlate",12,12}
	};
	return reg;
}

	/// Edge channel sleep control.
	/// 0 = Mission mode
	/// 1 = Sleep mode
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::edgesleep(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{58,"edgesleep",8,8}
	};
	return reg;
}

	/// Center-Edge coarse align enable. 
	/// 0 = Disable
	/// 1 = Enable
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ecoarsealignen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{58,"ecoarsealignen",7,7}
	};
	return reg;
}

	/// Center-Edge coarse alignment step.
	/// 000 = +48;   100 = -48
	/// ;001 = +54;   101 = -54
	/// ;010 = +60;   110 = -60
	/// ;011 = +64;   111 = -64.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ecoarsealignstep(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{58,"ecoarsealignstep",6,4}
	};
	return reg;
}

	/// Rx center-monitor coarse alignment enable control. Active low.
	/// 0: Disable coarse alignment.
	/// 1: Enable coarse alignement.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mcoarsealignen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{58,"mcoarsealignen",3,3}
	};
	return reg;
}

	/// Monitor-Center coarse alignment step.
	/// 000 = +48;   100 = -48
	/// ;001 = +54;   101 = -54
	/// ;010 = +60;   110 = -60
	/// ;011 = +64;   111 = -64.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mcoarsealignstep(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{58,"mcoarsealignstep",2,0}
	};
	return reg;
}

	/// not used
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::misierrdone(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{59,"misierrdone",15,15}
	};
	return reg;
}

	/// This register contains the present binary phase setting of the center channel phase interpolator.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cphsval(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{59,"cphsval",14,8}
	};
	return reg;
}

	/// This register contains the present binary phase setting of the edge channel phase interpolator.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ephsval(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{59,"ephsval",6,0}
	};
	return reg;
}

	/// This register contains the present binary phase setting of the monitor channel phase interpolator.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mphsofstval(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{60,"mphsofstval",15,9}
	};
	return reg;
}

	/// Eye monitor voltage offset.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mvolofstval(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{60,"mvolofstval",8,0}
	};
	return reg;
}

	/// Mismatch count which is calculated as,  
	/// if MMCNT[15:11] is zero, total count is MMCNT[10:0]
	/// if MMCNT[15:11] is non zero, total count is 2pow(10+MMCNT[15:11] ) +MMCNT[10:0] *2pow(MMCNT[15:11]-1)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mmcnt(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{61,"mmcnt",15,0}
	};
	return reg;
}

	/// TIMEREXP[4:0] gives the exponent portion of the internal 42-bit timer.
	/// 0 = MSB of the timer is at position 10 in the complete count
	/// 1 = MSB of the timer is at position 11 in the complete count
	/// 2 = MSB of the timer is at position 12 in the complete count
	/// ..
	/// 31 = MSB of the timer is at position 41 in the complete count
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::timerexp(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{62,"timerexp",15,11}
	};
	return reg;
}

	/// TIMER[10:0], together with the exponent portion (TIMEREXP[4:0]), gives the cycle count of the counting clock. TIMER[10:0] is only the lower 11-bit portion of the internal 42-bit timer.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::timer(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{62,"timer",10,0}
	};
	return reg;
}

	/// Configuration of timer for waiting, which is the cycles of reference clock. Timer value = (2 pow RXCALTIMERVALUE) -1 , where RXCALTIMERVALUE =0 to 22.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcal_timer_value(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{63,"rxcal_timer_value",14,5}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcal_timer_div_value(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{63,"rxcal_timer_div_value",4,2}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcal_timer_div_en(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{63,"rxcal_timer_div_en",1,1}
	};
	return reg;
}

	/// Stop timer, for debugging.
	/// 0 = normal
	/// 1 = stop the timer
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcal_timer_stop(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{63,"rxcal_timer_stop",0,0}
	};
	return reg;
}
bool
DS_rxRegs::_REG_INFO::get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos){
	reg_infos.clear();
	switch(csr){
		case 0:
			reg_infos.push_back(rxpwrdb().reg_info);
			reg_infos.push_back(rxauxclkpwrdb().reg_info);
			reg_infos.push_back(lpcmlen().reg_info);
			reg_infos.push_back(rxmute().reg_info);
			reg_infos.push_back(ctleboosten1().reg_info);
			reg_infos.push_back(rxauxclkdiv().reg_info);
			reg_infos.push_back(ctlepassgn().reg_info);
			break;
		case 1:
			reg_infos.push_back(ctlehfzen1().reg_info);
			reg_infos.push_back(ctleboostc1().reg_info);
			reg_infos.push_back(ctlecmband1().reg_info);
			reg_infos.push_back(ctlermband1().reg_info);
			reg_infos.push_back(ctleza1().reg_info);
			reg_infos.push_back(ctlesqh1().reg_info);
			reg_infos.push_back(ctleactgn1().reg_info);
			break;
		case 2:
			reg_infos.push_back(ctlehfzen2().reg_info);
			reg_infos.push_back(ctleboostc2().reg_info);
			reg_infos.push_back(ctlecmband2().reg_info);
			reg_infos.push_back(ctlermband2().reg_info);
			reg_infos.push_back(ctleza2().reg_info);
			reg_infos.push_back(ctlesqh2().reg_info);
			reg_infos.push_back(ctleactgn2().reg_info);
			break;
		case 3:
			reg_infos.push_back(ctlehfzen3().reg_info);
			reg_infos.push_back(ctleboostc3().reg_info);
			reg_infos.push_back(ctlecmband3().reg_info);
			reg_infos.push_back(ctlermband3().reg_info);
			reg_infos.push_back(ctleza3().reg_info);
			reg_infos.push_back(ctlesqh3().reg_info);
			reg_infos.push_back(ctleactgn3().reg_info);
			break;
		case 4:
			reg_infos.push_back(ctlegnlunpken1().reg_info);
			reg_infos.push_back(ctlegnlunpken2().reg_info);
			reg_infos.push_back(ctlegnlunpken3().reg_info);
			break;
		case 5:
			reg_infos.push_back(dfepwrdb().reg_info);
			reg_infos.push_back(dfemvtappwrdb().reg_info);
			reg_infos.push_back(dfefxtappwrdb().reg_info);
			reg_infos.push_back(dfesumboost().reg_info);
			reg_infos.push_back(dfegnsum().reg_info);
			break;
		case 6:
			reg_infos.push_back(rxdfemainpwrdb().reg_info);
			reg_infos.push_back(dfefxtap2().reg_info);
			break;
		case 7:
			reg_infos.push_back(dfefxtap3().reg_info);
			reg_infos.push_back(dfefxtap4().reg_info);
			break;
		case 8:
			reg_infos.push_back(dfefxtap5().reg_info);
			reg_infos.push_back(dfefxtap6().reg_info);
			reg_infos.push_back(dfefxtap7().reg_info);
			break;
		case 9:
			reg_infos.push_back(dfefxtap8().reg_info);
			reg_infos.push_back(dfefxtap9().reg_info);
			break;
		case 10:
			reg_infos.push_back(dfemvtap1().reg_info);
			reg_infos.push_back(dfemvtap2().reg_info);
			reg_infos.push_back(dfemvtap3().reg_info);
			break;
		case 11:
			reg_infos.push_back(dfemvtap4().reg_info);
			reg_infos.push_back(dfemvtap5().reg_info);
			reg_infos.push_back(dfemvtap6().reg_info);
			break;
		case 12:
			reg_infos.push_back(rxrstb().reg_info);
			reg_infos.push_back(rxdwidth().reg_info);
			reg_infos.push_back(rxratemode().reg_info);
			reg_infos.push_back(rxbitorder().reg_info);
			reg_infos.push_back(rxpolarity().reg_info);
			reg_infos.push_back(txrxparlpbken().reg_info);
			reg_infos.push_back(mdatasel().reg_info);
			reg_infos.push_back(tap1en().reg_info);
			reg_infos.push_back(tap1pol().reg_info);
			reg_infos.push_back(cdrfreeze().reg_info);
			reg_infos.push_back(boxcarsel().reg_info);
			reg_infos.push_back(secloopen().reg_info);
			reg_infos.push_back(bitslip().reg_info);
			break;
		case 13:
			reg_infos.push_back(cdrrstb().reg_info);
			reg_infos.push_back(phsgn().reg_info);
			reg_infos.push_back(cdredgeoffen().reg_info);
			reg_infos.push_back(cpafreeze().reg_info);
			reg_infos.push_back(cpagainsel().reg_info);
			reg_infos.push_back(cpaenable().reg_info);
			reg_infos.push_back(freqgn().reg_info);
			break;
		case 14:
			reg_infos.push_back(cphsofst().reg_info);
			reg_infos.push_back(ephsofst().reg_info);
			break;
		case 15:
			reg_infos.push_back(tdden().reg_info);
			reg_infos.push_back(tddthr().reg_info);
			reg_infos.push_back(loseyeen().reg_info);
			reg_infos.push_back(loseyethr().reg_info);
			reg_infos.push_back(timecntclr().reg_info);
			reg_infos.push_back(loscfg().reg_info);
			reg_infos.push_back(los().reg_info);
			reg_infos.push_back(lostran().reg_info);
			reg_infos.push_back(loseyever().reg_info);
			reg_infos.push_back(loseyehor().reg_info);
			reg_infos.push_back(losana().reg_info);
			break;
		case 16:
			reg_infos.push_back(timecntstart().reg_info);
			reg_infos.push_back(moniqofst().reg_info);
			reg_infos.push_back(prbsemdatasel().reg_info);
			reg_infos.push_back(volofstpol().reg_info);
			reg_infos.push_back(prbschken().reg_info);
			reg_infos.push_back(prbschkmode().reg_info);
			reg_infos.push_back(prbschkpatsel().reg_info);
			break;
		case 17:
			reg_infos.push_back(eyemonpwrdb().reg_info);
			reg_infos.push_back(eyescanstart().reg_info);
			reg_infos.push_back(emready().reg_info);
			reg_infos.push_back(emtaskstatus().reg_info);
			reg_infos.push_back(eyescanmode().reg_info);
			reg_infos.push_back(emvolovrmax().reg_info);
			reg_infos.push_back(compeyeen().reg_info);
			reg_infos.push_back(eyescanwinsel().reg_info);
			reg_infos.push_back(eyescanwin().reg_info);
			break;
		case 18:
			reg_infos.push_back(mphsofst().reg_info);
			break;
		case 19:
			reg_infos.push_back(ceniqofst().reg_info);
			reg_infos.push_back(monslcsel().reg_info);
			reg_infos.push_back(edgiqofst().reg_info);
			break;
		case 20:
			reg_infos.push_back(prbserr().reg_info);
			reg_infos.push_back(prbscntexp().reg_info);
			reg_infos.push_back(prbscnt().reg_info);
			break;
		case 21:
			reg_infos.push_back(mmthr().reg_info);
			break;
		case 22:
			reg_infos.push_back(emfoureyesel().reg_info);
			reg_infos.push_back(mvolofst().reg_info);
			break;
		case 23:
			reg_infos.push_back(emresult0().reg_info);
			break;
		case 24:
			reg_infos.push_back(emresult1().reg_info);
			break;
		case 25:
			reg_infos.push_back(eyescanctrl().reg_info);
			reg_infos.push_back(eyemontask().reg_info);
			reg_infos.push_back(eyescanalg().reg_info);
			reg_infos.push_back(emtaskctrl().reg_info);
			reg_infos.push_back(emcornerscaling().reg_info);
			reg_infos.push_back(emcornergrden().reg_info);
			break;
		case 26:
			reg_infos.push_back(monvolscanstltime().reg_info);
			break;
		case 27:
			reg_infos.push_back(emtaskavrg().reg_info);
			reg_infos.push_back(cornerofst0().reg_info);
			break;
		case 28:
			reg_infos.push_back(cornerofst1().reg_info);
			break;
		case 29:
			reg_infos.push_back(emresult2().reg_info);
			break;
		case 30:
			reg_infos.push_back(mvolmax().reg_info);
			break;
		case 31:
			reg_infos.push_back(rxtermcalsel().reg_info);
			reg_infos.push_back(rxtermcaldir().reg_info);
			reg_infos.push_back(rxlatofstrangescale().reg_info);
			reg_infos.push_back(rxctlerepopcalmode().reg_info);
			reg_infos.push_back(rxtermcal().reg_info);
			break;
		case 32:
			reg_infos.push_back(rxcalmode().reg_info);
			reg_infos.push_back(dscalstart().reg_info);
			reg_infos.push_back(rxcalstart().reg_info);
			reg_infos.push_back(rxtermfloating().reg_info);
			reg_infos.push_back(rxdatalatchcalen().reg_info);
			reg_infos.push_back(rxofstcaldir().reg_info);
			reg_infos.push_back(rxofstsel().reg_info);
			break;
		case 33:
			reg_infos.push_back(ctleofst1().reg_info);
			reg_infos.push_back(ctleofst2().reg_info);
			reg_infos.push_back(ctleofst3().reg_info);
			break;
		case 34:
			reg_infos.push_back(ctleofst4().reg_info);
			reg_infos.push_back(ctleofst5().reg_info);
			reg_infos.push_back(ctleofst6().reg_info);
			break;
		case 35:
			reg_infos.push_back(dfeievnsumofst().reg_info);
			reg_infos.push_back(dfeioddsumofst().reg_info);
			reg_infos.push_back(dfeqevnsumofst().reg_info);
			break;
		case 36:
			reg_infos.push_back(dfeqoddsumofst().reg_info);
			reg_infos.push_back(rxctleibiastune().reg_info);
			reg_infos.push_back(rxctlepasstune().reg_info);
			break;
		case 37:
			reg_infos.push_back(ctleiptattcctrl().reg_info);
			reg_infos.push_back(ctleiptatbypass().reg_info);
			reg_infos.push_back(ctlescresen().reg_info);
			reg_infos.push_back(ctlescresclkdiv().reg_info);
			break;
		case 38:
			reg_infos.push_back(rxsigdetpwrdb().reg_info);
			reg_infos.push_back(rxsigdetclkdiv().reg_info);
			reg_infos.push_back(rxsigdetclkdlysel().reg_info);
			reg_infos.push_back(rxsigdetcalpwrdb().reg_info);
			reg_infos.push_back(rxdigdetclkbufen().reg_info);
			reg_infos.push_back(rxsigdetatbsel().reg_info);
			break;
		case 39:
			reg_infos.push_back(rxsigdetvthres().reg_info);
			reg_infos.push_back(rxsigdethyst().reg_info);
			reg_infos.push_back(rxsigdetoffset().reg_info);
			break;
		case 40:
			reg_infos.push_back(sigdetsqlchlos().reg_info);
			reg_infos.push_back(sigdetlos().reg_info);
			reg_infos.push_back(sigdettxrxstat().reg_info);
			reg_infos.push_back(sigdetwin().reg_info);
			reg_infos.push_back(sigdetpmamode().reg_info);
			reg_infos.push_back(sigdetmanual().reg_info);
			reg_infos.push_back(sigdetthrselman().reg_info);
			reg_infos.push_back(sigdeten().reg_info);
			break;
		case 41:
			reg_infos.push_back(sigdetthrcfgsel().reg_info);
			reg_infos.push_back(sigdetthrs1().reg_info);
			break;
		case 42:
			reg_infos.push_back(sigdetthrs2().reg_info);
			break;
		case 43:
			reg_infos.push_back(sigdetthrs3().reg_info);
			break;
		case 44:
			reg_infos.push_back(rxctlerepofftrig().reg_info);
			reg_infos.push_back(ctlestg1to4pwrdb().reg_info);
			reg_infos.push_back(replicacaldir().reg_info);
			reg_infos.push_back(ctlerepcalen().reg_info);
			reg_infos.push_back(ctlerepcalcode().reg_info);
			reg_infos.push_back(ctlerefsel().reg_info);
			reg_infos.push_back(ctleloadsel().reg_info);
			break;
		case 45:
			reg_infos.push_back(dspwrsqtbs3().reg_info);
			reg_infos.push_back(vregctlerefsel().reg_info);
			reg_infos.push_back(rxcpcendlyctrli().reg_info);
			reg_infos.push_back(rxcpcendlyctrlq().reg_info);
			break;
		case 46:
			reg_infos.push_back(rxcpcenpwrdb().reg_info);
			reg_infos.push_back(rxcpcenipibufpwrdb().reg_info);
			reg_infos.push_back(rxcpcenipicmlcmospwrdb().reg_info);
			reg_infos.push_back(rxcpcenipicorepwrdb().reg_info);
			reg_infos.push_back(rxcpcenqpibufpwrdb().reg_info);
			reg_infos.push_back(rxcpcenqpicmlcmospwrdb().reg_info);
			reg_infos.push_back(rxcpcenqpicorepwrdb().reg_info);
			reg_infos.push_back(rxcpcenpibiastrim().reg_info);
			reg_infos.push_back(rxcpcenpibufbiastrim().reg_info);
			reg_infos.push_back(rxcpcenpibufloadtrim().reg_info);
			break;
		case 47:
			reg_infos.push_back(rxcpedgpwrdb().reg_info);
			reg_infos.push_back(rxcpedgipibufpwrdb().reg_info);
			reg_infos.push_back(rxcpedgipicmlcmospwrdb().reg_info);
			reg_infos.push_back(rxcpedgipicorepwrdb().reg_info);
			reg_infos.push_back(rxcpedgqpibufpwrdb().reg_info);
			reg_infos.push_back(rxcpedgqpicmlcmospwrdb().reg_info);
			reg_infos.push_back(rxcpedgqpicorepwrdb().reg_info);
			reg_infos.push_back(rxcpedgdlyctrli().reg_info);
			reg_infos.push_back(rxcpedgdlyctrlq().reg_info);
			reg_infos.push_back(rxcpcenphsgenspare().reg_info);
			reg_infos.push_back(rxcpedgphsgenspare().reg_info);
			reg_infos.push_back(rxiqdetpwrdb().reg_info);
			break;
		case 48:
			reg_infos.push_back(rxcpmonpwrdb().reg_info);
			reg_infos.push_back(rxcpmonqpwrdb().reg_info);
			reg_infos.push_back(rxcpmonipibufpwrdb().reg_info);
			reg_infos.push_back(rxcpmonipicmlcmospwrdb().reg_info);
			reg_infos.push_back(rxcpmonipicorepwrdb().reg_info);
			reg_infos.push_back(rxcpmonqpibufpwrdb().reg_info);
			reg_infos.push_back(rxcpmonqpicmlcmospwrdb().reg_info);
			reg_infos.push_back(rxcpmonqpicorepwrdb().reg_info);
			reg_infos.push_back(rxmonpwrcycmode().reg_info);
			reg_infos.push_back(rxmonpwrdb().reg_info);
			reg_infos.push_back(rxedgpwrdb().reg_info);
			reg_infos.push_back(rxcpmondlyctrli().reg_info);
			reg_infos.push_back(rxcpmondlyctrlq().reg_info);
			break;
		case 49:
			reg_infos.push_back(censlcipwrdb().reg_info);
			reg_infos.push_back(censlcqpwrdb().reg_info);
			reg_infos.push_back(censlcibpwrdb().reg_info);
			reg_infos.push_back(censlcqbpwrdb().reg_info);
			reg_infos.push_back(edgslcipwrdb().reg_info);
			reg_infos.push_back(edgslcqpwrdb().reg_info);
			reg_infos.push_back(edgslcibpwrdb().reg_info);
			reg_infos.push_back(edgslcqbpwrdb().reg_info);
			reg_infos.push_back(monslcipwrdb().reg_info);
			reg_infos.push_back(monslcibpwrdb().reg_info);
			reg_infos.push_back(cendemuxpwrdb().reg_info);
			reg_infos.push_back(edgdemuxpwrdb().reg_info);
			reg_infos.push_back(mondemuxpwrdb().reg_info);
			reg_infos.push_back(rxcenpwrdb().reg_info);
			reg_infos.push_back(monslcqpwrdb().reg_info);
			reg_infos.push_back(monslcqbpwrdb().reg_info);
			break;
		case 50:
			reg_infos.push_back(dfesumvrefsel().reg_info);
			reg_infos.push_back(dfesumrtrimen().reg_info);
			reg_infos.push_back(vregclkvrefrng().reg_info);
			reg_infos.push_back(vregclkpreampsel().reg_info);
			reg_infos.push_back(vregdatavrefrng().reg_info);
			reg_infos.push_back(dfesumrestrim().reg_info);
			reg_infos.push_back(dfesumauxofsten().reg_info);
			reg_infos.push_back(dfesumauxofstpol().reg_info);
			reg_infos.push_back(dfesumauxofstsel().reg_info);
			break;
		case 51:
			reg_infos.push_back(dfefxtap1cen().reg_info);
			reg_infos.push_back(dfefxtap1edg().reg_info);
			break;
		case 52:
			reg_infos.push_back(dfespare().reg_info);
			reg_infos.push_back(dfetapinjscale().reg_info);
			reg_infos.push_back(dfeslicerbwsel().reg_info);
			reg_infos.push_back(rxdfesumvreftrim().reg_info);
			reg_infos.push_back(dfealphagenrtrim().reg_info);
			reg_infos.push_back(dfealphagenrefsel().reg_info);
			reg_infos.push_back(dfealphagenloadsel().reg_info);
			break;
		case 53:
			reg_infos.push_back(vregclkpwrdb().reg_info);
			reg_infos.push_back(vregclkdpmen().reg_info);
			reg_infos.push_back(vregclkbleedb().reg_info);
			reg_infos.push_back(vregclklvl().reg_info);
			reg_infos.push_back(vregdatapwrdb().reg_info);
			reg_infos.push_back(vregdatadpmen().reg_info);
			reg_infos.push_back(vregdatableedb().reg_info);
			reg_infos.push_back(vregdatalvl().reg_info);
			break;
		case 54:
			reg_infos.push_back(vregclkinrushpwrdb().reg_info);
			reg_infos.push_back(vregdatainrushpwrdb().reg_info);
			reg_infos.push_back(vregclkrefsel().reg_info);
			reg_infos.push_back(vregdatarefsel().reg_info);
			break;
		case 55:
			reg_infos.push_back(rxatbmuxsel().reg_info);
			reg_infos.push_back(dfealphagentopmatbctrl().reg_info);
			reg_infos.push_back(dfealphagentoppatbctrl().reg_info);
			reg_infos.push_back(dfealphagencenmute().reg_info);
			reg_infos.push_back(dfealphagenedgmute().reg_info);
			reg_infos.push_back(dfealphagenmonmute().reg_info);
			reg_infos.push_back(dfealphagenstepsize().reg_info);
			reg_infos.push_back(dfesumbias().reg_info);
			reg_infos.push_back(rxdfesumbiasptaten().reg_info);
			break;
		case 56:
			reg_infos.push_back(vregclkatbctrl().reg_info);
			reg_infos.push_back(vregdataatbctrl().reg_info);
			reg_infos.push_back(suptrimsummerrefsel().reg_info);
			break;
		case 57:
			reg_infos.push_back(jtagsel().reg_info);
			reg_infos.push_back(jtagoutp().reg_info);
			reg_infos.push_back(jtagoutm().reg_info);
			reg_infos.push_back(jtagpwrdb().reg_info);
			reg_infos.push_back(jtagacmodeen().reg_info);
			reg_infos.push_back(jtaginitclk().reg_info);
			reg_infos.push_back(jtaginitp().reg_info);
			reg_infos.push_back(jtaginitm().reg_info);
			reg_infos.push_back(jtaghystadj().reg_info);
			reg_infos.push_back(jtagthadj().reg_info);
			break;
		case 58:
			reg_infos.push_back(ceearly().reg_info);
			reg_infos.push_back(celate().reg_info);
			reg_infos.push_back(cmearly().reg_info);
			reg_infos.push_back(cmlate().reg_info);
			reg_infos.push_back(edgesleep().reg_info);
			reg_infos.push_back(ecoarsealignen().reg_info);
			reg_infos.push_back(ecoarsealignstep().reg_info);
			reg_infos.push_back(mcoarsealignen().reg_info);
			reg_infos.push_back(mcoarsealignstep().reg_info);
			break;
		case 59:
			reg_infos.push_back(misierrdone().reg_info);
			reg_infos.push_back(cphsval().reg_info);
			reg_infos.push_back(ephsval().reg_info);
			break;
		case 60:
			reg_infos.push_back(mphsofstval().reg_info);
			reg_infos.push_back(mvolofstval().reg_info);
			break;
		case 61:
			reg_infos.push_back(mmcnt().reg_info);
			break;
		case 62:
			reg_infos.push_back(timerexp().reg_info);
			reg_infos.push_back(timer().reg_info);
			break;
		case 63:
			reg_infos.push_back(rxcal_timer_value().reg_info);
			reg_infos.push_back(rxcal_timer_div_value().reg_info);
			reg_infos.push_back(rxcal_timer_div_en().reg_info);
			reg_infos.push_back(rxcal_timer_stop().reg_info);
			break;
		default:
			break;
	}
	return (reg_infos.size()>0);
}


DS_rxRegs&
DS_rxRegs::setrxpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxpwrdb());	//CSR0[15:15]
	return *this;
}
uint
DS_rxRegs::getrxpwrdb(){
	return get_csr_bits(REG_INFO.rxpwrdb());	//CSR0[15:15]
}

DS_rxRegs&
DS_rxRegs::setrxauxclkpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxauxclkpwrdb());	//CSR0[14:14]
	return *this;
}
uint
DS_rxRegs::getrxauxclkpwrdb(){
	return get_csr_bits(REG_INFO.rxauxclkpwrdb());	//CSR0[14:14]
}

DS_rxRegs&
DS_rxRegs::setlpcmlen(uint val){
	fill_csr_bits(val,REG_INFO.lpcmlen());	//CSR0[11:11]
	return *this;
}
uint
DS_rxRegs::getlpcmlen(){
	return get_csr_bits(REG_INFO.lpcmlen());	//CSR0[11:11]
}

DS_rxRegs&
DS_rxRegs::setrxmute(uint val){
	fill_csr_bits(val,REG_INFO.rxmute());	//CSR0[9:9]
	return *this;
}
uint
DS_rxRegs::getrxmute(){
	return get_csr_bits(REG_INFO.rxmute());	//CSR0[9:9]
}

DS_rxRegs&
DS_rxRegs::setctleboosten1(uint val){
	fill_csr_bits(val,REG_INFO.ctleboosten1());	//CSR0[8:8]
	return *this;
}
uint
DS_rxRegs::getctleboosten1(){
	return get_csr_bits(REG_INFO.ctleboosten1());	//CSR0[8:8]
}

DS_rxRegs&
DS_rxRegs::setrxauxclkdiv(uint val){
	fill_csr_bits(val,REG_INFO.rxauxclkdiv());	//CSR0[4:3]
	return *this;
}
uint
DS_rxRegs::getrxauxclkdiv(){
	return get_csr_bits(REG_INFO.rxauxclkdiv());	//CSR0[4:3]
}

DS_rxRegs&
DS_rxRegs::setctlepassgn(uint val){
	fill_csr_bits(val,REG_INFO.ctlepassgn());	//CSR0[2:0]
	return *this;
}
uint
DS_rxRegs::getctlepassgn(){
	return get_csr_bits(REG_INFO.ctlepassgn());	//CSR0[2:0]
}

DS_rxRegs&
DS_rxRegs::setctlehfzen1(uint val){
	fill_csr_bits(val,REG_INFO.ctlehfzen1());	//CSR1[15:15]
	return *this;
}
uint
DS_rxRegs::getctlehfzen1(){
	return get_csr_bits(REG_INFO.ctlehfzen1());	//CSR1[15:15]
}

DS_rxRegs&
DS_rxRegs::setctleboostc1(uint val){
	fill_csr_bits(val,REG_INFO.ctleboostc1());	//CSR1[14:12]
	return *this;
}
uint
DS_rxRegs::getctleboostc1(){
	return get_csr_bits(REG_INFO.ctleboostc1());	//CSR1[14:12]
}

DS_rxRegs&
DS_rxRegs::setctlecmband1(uint val){
	fill_csr_bits(val,REG_INFO.ctlecmband1());	//CSR1[11:10]
	return *this;
}
uint
DS_rxRegs::getctlecmband1(){
	return get_csr_bits(REG_INFO.ctlecmband1());	//CSR1[11:10]
}

DS_rxRegs&
DS_rxRegs::setctlermband1(uint val){
	fill_csr_bits(val,REG_INFO.ctlermband1());	//CSR1[9:8]
	return *this;
}
uint
DS_rxRegs::getctlermband1(){
	return get_csr_bits(REG_INFO.ctlermband1());	//CSR1[9:8]
}

DS_rxRegs&
DS_rxRegs::setctleza1(uint val){
	fill_csr_bits(val,REG_INFO.ctleza1());	//CSR1[7:5]
	return *this;
}
uint
DS_rxRegs::getctleza1(){
	return get_csr_bits(REG_INFO.ctleza1());	//CSR1[7:5]
}

DS_rxRegs&
DS_rxRegs::setctlesqh1(uint val){
	fill_csr_bits(val,REG_INFO.ctlesqh1());	//CSR1[4:3]
	return *this;
}
uint
DS_rxRegs::getctlesqh1(){
	return get_csr_bits(REG_INFO.ctlesqh1());	//CSR1[4:3]
}

DS_rxRegs&
DS_rxRegs::setctleactgn1(uint val){
	fill_csr_bits(val,REG_INFO.ctleactgn1());	//CSR1[2:0]
	return *this;
}
uint
DS_rxRegs::getctleactgn1(){
	return get_csr_bits(REG_INFO.ctleactgn1());	//CSR1[2:0]
}

DS_rxRegs&
DS_rxRegs::setctlehfzen2(uint val){
	fill_csr_bits(val,REG_INFO.ctlehfzen2());	//CSR2[15:15]
	return *this;
}
uint
DS_rxRegs::getctlehfzen2(){
	return get_csr_bits(REG_INFO.ctlehfzen2());	//CSR2[15:15]
}

DS_rxRegs&
DS_rxRegs::setctleboostc2(uint val){
	fill_csr_bits(val,REG_INFO.ctleboostc2());	//CSR2[14:12]
	return *this;
}
uint
DS_rxRegs::getctleboostc2(){
	return get_csr_bits(REG_INFO.ctleboostc2());	//CSR2[14:12]
}

DS_rxRegs&
DS_rxRegs::setctlecmband2(uint val){
	fill_csr_bits(val,REG_INFO.ctlecmband2());	//CSR2[11:10]
	return *this;
}
uint
DS_rxRegs::getctlecmband2(){
	return get_csr_bits(REG_INFO.ctlecmband2());	//CSR2[11:10]
}

DS_rxRegs&
DS_rxRegs::setctlermband2(uint val){
	fill_csr_bits(val,REG_INFO.ctlermband2());	//CSR2[9:8]
	return *this;
}
uint
DS_rxRegs::getctlermband2(){
	return get_csr_bits(REG_INFO.ctlermband2());	//CSR2[9:8]
}

DS_rxRegs&
DS_rxRegs::setctleza2(uint val){
	fill_csr_bits(val,REG_INFO.ctleza2());	//CSR2[7:5]
	return *this;
}
uint
DS_rxRegs::getctleza2(){
	return get_csr_bits(REG_INFO.ctleza2());	//CSR2[7:5]
}

DS_rxRegs&
DS_rxRegs::setctlesqh2(uint val){
	fill_csr_bits(val,REG_INFO.ctlesqh2());	//CSR2[4:3]
	return *this;
}
uint
DS_rxRegs::getctlesqh2(){
	return get_csr_bits(REG_INFO.ctlesqh2());	//CSR2[4:3]
}

DS_rxRegs&
DS_rxRegs::setctleactgn2(uint val){
	fill_csr_bits(val,REG_INFO.ctleactgn2());	//CSR2[2:0]
	return *this;
}
uint
DS_rxRegs::getctleactgn2(){
	return get_csr_bits(REG_INFO.ctleactgn2());	//CSR2[2:0]
}

DS_rxRegs&
DS_rxRegs::setctlehfzen3(uint val){
	fill_csr_bits(val,REG_INFO.ctlehfzen3());	//CSR3[15:15]
	return *this;
}
uint
DS_rxRegs::getctlehfzen3(){
	return get_csr_bits(REG_INFO.ctlehfzen3());	//CSR3[15:15]
}

DS_rxRegs&
DS_rxRegs::setctleboostc3(uint val){
	fill_csr_bits(val,REG_INFO.ctleboostc3());	//CSR3[14:12]
	return *this;
}
uint
DS_rxRegs::getctleboostc3(){
	return get_csr_bits(REG_INFO.ctleboostc3());	//CSR3[14:12]
}

DS_rxRegs&
DS_rxRegs::setctlecmband3(uint val){
	fill_csr_bits(val,REG_INFO.ctlecmband3());	//CSR3[11:10]
	return *this;
}
uint
DS_rxRegs::getctlecmband3(){
	return get_csr_bits(REG_INFO.ctlecmband3());	//CSR3[11:10]
}

DS_rxRegs&
DS_rxRegs::setctlermband3(uint val){
	fill_csr_bits(val,REG_INFO.ctlermband3());	//CSR3[9:8]
	return *this;
}
uint
DS_rxRegs::getctlermband3(){
	return get_csr_bits(REG_INFO.ctlermband3());	//CSR3[9:8]
}

DS_rxRegs&
DS_rxRegs::setctleza3(uint val){
	fill_csr_bits(val,REG_INFO.ctleza3());	//CSR3[7:5]
	return *this;
}
uint
DS_rxRegs::getctleza3(){
	return get_csr_bits(REG_INFO.ctleza3());	//CSR3[7:5]
}

DS_rxRegs&
DS_rxRegs::setctlesqh3(uint val){
	fill_csr_bits(val,REG_INFO.ctlesqh3());	//CSR3[4:3]
	return *this;
}
uint
DS_rxRegs::getctlesqh3(){
	return get_csr_bits(REG_INFO.ctlesqh3());	//CSR3[4:3]
}

DS_rxRegs&
DS_rxRegs::setctleactgn3(uint val){
	fill_csr_bits(val,REG_INFO.ctleactgn3());	//CSR3[2:0]
	return *this;
}
uint
DS_rxRegs::getctleactgn3(){
	return get_csr_bits(REG_INFO.ctleactgn3());	//CSR3[2:0]
}

DS_rxRegs&
DS_rxRegs::setctlegnlunpken1(uint val){
	fill_csr_bits(val,REG_INFO.ctlegnlunpken1());	//CSR4[3:3]
	return *this;
}
uint
DS_rxRegs::getctlegnlunpken1(){
	return get_csr_bits(REG_INFO.ctlegnlunpken1());	//CSR4[3:3]
}

DS_rxRegs&
DS_rxRegs::setctlegnlunpken2(uint val){
	fill_csr_bits(val,REG_INFO.ctlegnlunpken2());	//CSR4[2:2]
	return *this;
}
uint
DS_rxRegs::getctlegnlunpken2(){
	return get_csr_bits(REG_INFO.ctlegnlunpken2());	//CSR4[2:2]
}

DS_rxRegs&
DS_rxRegs::setctlegnlunpken3(uint val){
	fill_csr_bits(val,REG_INFO.ctlegnlunpken3());	//CSR4[1:1]
	return *this;
}
uint
DS_rxRegs::getctlegnlunpken3(){
	return get_csr_bits(REG_INFO.ctlegnlunpken3());	//CSR4[1:1]
}

DS_rxRegs&
DS_rxRegs::setdfepwrdb(uint val){
	fill_csr_bits(val,REG_INFO.dfepwrdb());	//CSR5[15:15]
	return *this;
}
uint
DS_rxRegs::getdfepwrdb(){
	return get_csr_bits(REG_INFO.dfepwrdb());	//CSR5[15:15]
}

DS_rxRegs&
DS_rxRegs::setdfemvtappwrdb(uint val){
	fill_csr_bits(val,REG_INFO.dfemvtappwrdb());	//CSR5[14:14]
	return *this;
}
uint
DS_rxRegs::getdfemvtappwrdb(){
	return get_csr_bits(REG_INFO.dfemvtappwrdb());	//CSR5[14:14]
}

DS_rxRegs&
DS_rxRegs::setdfefxtappwrdb(uint val){
	fill_csr_bits(val,REG_INFO.dfefxtappwrdb());	//CSR5[13:5]
	return *this;
}
uint
DS_rxRegs::getdfefxtappwrdb(){
	return get_csr_bits(REG_INFO.dfefxtappwrdb());	//CSR5[13:5]
}

DS_rxRegs&
DS_rxRegs::setdfesumboost(uint val){
	fill_csr_bits(val,REG_INFO.dfesumboost());	//CSR5[4:3]
	return *this;
}
uint
DS_rxRegs::getdfesumboost(){
	return get_csr_bits(REG_INFO.dfesumboost());	//CSR5[4:3]
}

DS_rxRegs&
DS_rxRegs::setdfegnsum(uint val){
	fill_csr_bits(val,REG_INFO.dfegnsum());	//CSR5[2:0]
	return *this;
}
uint
DS_rxRegs::getdfegnsum(){
	return get_csr_bits(REG_INFO.dfegnsum());	//CSR5[2:0]
}

DS_rxRegs&
DS_rxRegs::setrxdfemainpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxdfemainpwrdb());	//CSR6[7:7]
	return *this;
}
uint
DS_rxRegs::getrxdfemainpwrdb(){
	return get_csr_bits(REG_INFO.rxdfemainpwrdb());	//CSR6[7:7]
}

DS_rxRegs&
DS_rxRegs::setdfefxtap2(uint val){
	fill_csr_bits(val,REG_INFO.dfefxtap2());	//CSR6[6:0]
	return *this;
}
uint
DS_rxRegs::getdfefxtap2(){
	return get_csr_bits(REG_INFO.dfefxtap2());	//CSR6[6:0]
}

DS_rxRegs&
DS_rxRegs::setdfefxtap3(uint val){
	fill_csr_bits(val,REG_INFO.dfefxtap3());	//CSR7[13:8]
	return *this;
}
uint
DS_rxRegs::getdfefxtap3(){
	return get_csr_bits(REG_INFO.dfefxtap3());	//CSR7[13:8]
}

DS_rxRegs&
DS_rxRegs::setdfefxtap4(uint val){
	fill_csr_bits(val,REG_INFO.dfefxtap4());	//CSR7[5:0]
	return *this;
}
uint
DS_rxRegs::getdfefxtap4(){
	return get_csr_bits(REG_INFO.dfefxtap4());	//CSR7[5:0]
}

DS_rxRegs&
DS_rxRegs::setdfefxtap5(uint val){
	fill_csr_bits(val,REG_INFO.dfefxtap5());	//CSR8[15:10]
	return *this;
}
uint
DS_rxRegs::getdfefxtap5(){
	return get_csr_bits(REG_INFO.dfefxtap5());	//CSR8[15:10]
}

DS_rxRegs&
DS_rxRegs::setdfefxtap6(uint val){
	fill_csr_bits(val,REG_INFO.dfefxtap6());	//CSR8[9:5]
	return *this;
}
uint
DS_rxRegs::getdfefxtap6(){
	return get_csr_bits(REG_INFO.dfefxtap6());	//CSR8[9:5]
}

DS_rxRegs&
DS_rxRegs::setdfefxtap7(uint val){
	fill_csr_bits(val,REG_INFO.dfefxtap7());	//CSR8[4:0]
	return *this;
}
uint
DS_rxRegs::getdfefxtap7(){
	return get_csr_bits(REG_INFO.dfefxtap7());	//CSR8[4:0]
}

DS_rxRegs&
DS_rxRegs::setdfefxtap8(uint val){
	fill_csr_bits(val,REG_INFO.dfefxtap8());	//CSR9[12:8]
	return *this;
}
uint
DS_rxRegs::getdfefxtap8(){
	return get_csr_bits(REG_INFO.dfefxtap8());	//CSR9[12:8]
}

DS_rxRegs&
DS_rxRegs::setdfefxtap9(uint val){
	fill_csr_bits(val,REG_INFO.dfefxtap9());	//CSR9[4:0]
	return *this;
}
uint
DS_rxRegs::getdfefxtap9(){
	return get_csr_bits(REG_INFO.dfefxtap9());	//CSR9[4:0]
}

DS_rxRegs&
DS_rxRegs::setdfemvtap1(uint val){
	fill_csr_bits(val,REG_INFO.dfemvtap1());	//CSR10[14:10]
	return *this;
}
uint
DS_rxRegs::getdfemvtap1(){
	return get_csr_bits(REG_INFO.dfemvtap1());	//CSR10[14:10]
}

DS_rxRegs&
DS_rxRegs::setdfemvtap2(uint val){
	fill_csr_bits(val,REG_INFO.dfemvtap2());	//CSR10[9:5]
	return *this;
}
uint
DS_rxRegs::getdfemvtap2(){
	return get_csr_bits(REG_INFO.dfemvtap2());	//CSR10[9:5]
}

DS_rxRegs&
DS_rxRegs::setdfemvtap3(uint val){
	fill_csr_bits(val,REG_INFO.dfemvtap3());	//CSR10[4:0]
	return *this;
}
uint
DS_rxRegs::getdfemvtap3(){
	return get_csr_bits(REG_INFO.dfemvtap3());	//CSR10[4:0]
}

DS_rxRegs&
DS_rxRegs::setdfemvtap4(uint val){
	fill_csr_bits(val,REG_INFO.dfemvtap4());	//CSR11[14:10]
	return *this;
}
uint
DS_rxRegs::getdfemvtap4(){
	return get_csr_bits(REG_INFO.dfemvtap4());	//CSR11[14:10]
}

DS_rxRegs&
DS_rxRegs::setdfemvtap5(uint val){
	fill_csr_bits(val,REG_INFO.dfemvtap5());	//CSR11[9:5]
	return *this;
}
uint
DS_rxRegs::getdfemvtap5(){
	return get_csr_bits(REG_INFO.dfemvtap5());	//CSR11[9:5]
}

DS_rxRegs&
DS_rxRegs::setdfemvtap6(uint val){
	fill_csr_bits(val,REG_INFO.dfemvtap6());	//CSR11[4:0]
	return *this;
}
uint
DS_rxRegs::getdfemvtap6(){
	return get_csr_bits(REG_INFO.dfemvtap6());	//CSR11[4:0]
}

DS_rxRegs&
DS_rxRegs::setrxrstb(uint val){
	fill_csr_bits(val,REG_INFO.rxrstb());	//CSR12[15:15]
	return *this;
}
uint
DS_rxRegs::getrxrstb(){
	return get_csr_bits(REG_INFO.rxrstb());	//CSR12[15:15]
}

DS_rxRegs&
DS_rxRegs::setrxdwidth(uint val){
	fill_csr_bits(val,REG_INFO.rxdwidth());	//CSR12[14:13]
	return *this;
}
uint
DS_rxRegs::getrxdwidth(){
	return get_csr_bits(REG_INFO.rxdwidth());	//CSR12[14:13]
}

DS_rxRegs&
DS_rxRegs::setrxratemode(uint val){
	fill_csr_bits(val,REG_INFO.rxratemode());	//CSR12[12:10]
	return *this;
}
uint
DS_rxRegs::getrxratemode(){
	return get_csr_bits(REG_INFO.rxratemode());	//CSR12[12:10]
}

DS_rxRegs&
DS_rxRegs::setrxbitorder(uint val){
	fill_csr_bits(val,REG_INFO.rxbitorder());	//CSR12[9:9]
	return *this;
}
uint
DS_rxRegs::getrxbitorder(){
	return get_csr_bits(REG_INFO.rxbitorder());	//CSR12[9:9]
}

DS_rxRegs&
DS_rxRegs::setrxpolarity(uint val){
	fill_csr_bits(val,REG_INFO.rxpolarity());	//CSR12[8:8]
	return *this;
}
uint
DS_rxRegs::getrxpolarity(){
	return get_csr_bits(REG_INFO.rxpolarity());	//CSR12[8:8]
}

DS_rxRegs&
DS_rxRegs::settxrxparlpbken(uint val){
	fill_csr_bits(val,REG_INFO.txrxparlpbken());	//CSR12[7:7]
	return *this;
}
uint
DS_rxRegs::gettxrxparlpbken(){
	return get_csr_bits(REG_INFO.txrxparlpbken());	//CSR12[7:7]
}

DS_rxRegs&
DS_rxRegs::setmdatasel(uint val){
	fill_csr_bits(val,REG_INFO.mdatasel());	//CSR12[6:6]
	return *this;
}
uint
DS_rxRegs::getmdatasel(){
	return get_csr_bits(REG_INFO.mdatasel());	//CSR12[6:6]
}

DS_rxRegs&
DS_rxRegs::settap1en(uint val){
	fill_csr_bits(val,REG_INFO.tap1en());	//CSR12[5:5]
	return *this;
}
uint
DS_rxRegs::gettap1en(){
	return get_csr_bits(REG_INFO.tap1en());	//CSR12[5:5]
}

DS_rxRegs&
DS_rxRegs::settap1pol(uint val){
	fill_csr_bits(val,REG_INFO.tap1pol());	//CSR12[4:4]
	return *this;
}
uint
DS_rxRegs::gettap1pol(){
	return get_csr_bits(REG_INFO.tap1pol());	//CSR12[4:4]
}

DS_rxRegs&
DS_rxRegs::setcdrfreeze(uint val){
	fill_csr_bits(val,REG_INFO.cdrfreeze());	//CSR12[3:3]
	return *this;
}
uint
DS_rxRegs::getcdrfreeze(){
	return get_csr_bits(REG_INFO.cdrfreeze());	//CSR12[3:3]
}

DS_rxRegs&
DS_rxRegs::setboxcarsel(uint val){
	fill_csr_bits(val,REG_INFO.boxcarsel());	//CSR12[2:2]
	return *this;
}
uint
DS_rxRegs::getboxcarsel(){
	return get_csr_bits(REG_INFO.boxcarsel());	//CSR12[2:2]
}

DS_rxRegs&
DS_rxRegs::setsecloopen(uint val){
	fill_csr_bits(val,REG_INFO.secloopen());	//CSR12[1:1]
	return *this;
}
uint
DS_rxRegs::getsecloopen(){
	return get_csr_bits(REG_INFO.secloopen());	//CSR12[1:1]
}

DS_rxRegs&
DS_rxRegs::setbitslip(uint val){
	fill_csr_bits(val,REG_INFO.bitslip());	//CSR12[0:0]
	return *this;
}
uint
DS_rxRegs::getbitslip(){
	return get_csr_bits(REG_INFO.bitslip());	//CSR12[0:0]
}

DS_rxRegs&
DS_rxRegs::setcdrrstb(uint val){
	fill_csr_bits(val,REG_INFO.cdrrstb());	//CSR13[15:15]
	return *this;
}
uint
DS_rxRegs::getcdrrstb(){
	return get_csr_bits(REG_INFO.cdrrstb());	//CSR13[15:15]
}

DS_rxRegs&
DS_rxRegs::setphsgn(uint val){
	fill_csr_bits(val,REG_INFO.phsgn());	//CSR13[14:12]
	return *this;
}
uint
DS_rxRegs::getphsgn(){
	return get_csr_bits(REG_INFO.phsgn());	//CSR13[14:12]
}

DS_rxRegs&
DS_rxRegs::setcdredgeoffen(uint val){
	fill_csr_bits(val,REG_INFO.cdredgeoffen());	//CSR13[7:7]
	return *this;
}
uint
DS_rxRegs::getcdredgeoffen(){
	return get_csr_bits(REG_INFO.cdredgeoffen());	//CSR13[7:7]
}

DS_rxRegs&
DS_rxRegs::setcpafreeze(uint val){
	fill_csr_bits(val,REG_INFO.cpafreeze());	//CSR13[6:6]
	return *this;
}
uint
DS_rxRegs::getcpafreeze(){
	return get_csr_bits(REG_INFO.cpafreeze());	//CSR13[6:6]
}

DS_rxRegs&
DS_rxRegs::setcpagainsel(uint val){
	fill_csr_bits(val,REG_INFO.cpagainsel());	//CSR13[5:4]
	return *this;
}
uint
DS_rxRegs::getcpagainsel(){
	return get_csr_bits(REG_INFO.cpagainsel());	//CSR13[5:4]
}

DS_rxRegs&
DS_rxRegs::setcpaenable(uint val){
	fill_csr_bits(val,REG_INFO.cpaenable());	//CSR13[3:3]
	return *this;
}
uint
DS_rxRegs::getcpaenable(){
	return get_csr_bits(REG_INFO.cpaenable());	//CSR13[3:3]
}

DS_rxRegs&
DS_rxRegs::setfreqgn(uint val){
	fill_csr_bits(val,REG_INFO.freqgn());	//CSR13[2:0]
	return *this;
}
uint
DS_rxRegs::getfreqgn(){
	return get_csr_bits(REG_INFO.freqgn());	//CSR13[2:0]
}

DS_rxRegs&
DS_rxRegs::setcphsofst(uint val){
	fill_csr_bits(val,REG_INFO.cphsofst());	//CSR14[15:8]
	return *this;
}
uint
DS_rxRegs::getcphsofst(){
	return get_csr_bits(REG_INFO.cphsofst());	//CSR14[15:8]
}

DS_rxRegs&
DS_rxRegs::setephsofst(uint val){
	fill_csr_bits(val,REG_INFO.ephsofst());	//CSR14[7:0]
	return *this;
}
uint
DS_rxRegs::getephsofst(){
	return get_csr_bits(REG_INFO.ephsofst());	//CSR14[7:0]
}

DS_rxRegs&
DS_rxRegs::settdden(uint val){
	fill_csr_bits(val,REG_INFO.tdden());	//CSR15[15:15]
	return *this;
}
uint
DS_rxRegs::gettdden(){
	return get_csr_bits(REG_INFO.tdden());	//CSR15[15:15]
}

DS_rxRegs&
DS_rxRegs::settddthr(uint val){
	fill_csr_bits(val,REG_INFO.tddthr());	//CSR15[14:12]
	return *this;
}
uint
DS_rxRegs::gettddthr(){
	return get_csr_bits(REG_INFO.tddthr());	//CSR15[14:12]
}

DS_rxRegs&
DS_rxRegs::setloseyeen(uint val){
	fill_csr_bits(val,REG_INFO.loseyeen());	//CSR15[11:11]
	return *this;
}
uint
DS_rxRegs::getloseyeen(){
	return get_csr_bits(REG_INFO.loseyeen());	//CSR15[11:11]
}

DS_rxRegs&
DS_rxRegs::setloseyethr(uint val){
	fill_csr_bits(val,REG_INFO.loseyethr());	//CSR15[10:9]
	return *this;
}
uint
DS_rxRegs::getloseyethr(){
	return get_csr_bits(REG_INFO.loseyethr());	//CSR15[10:9]
}

DS_rxRegs&
DS_rxRegs::settimecntclr(uint val){
	fill_csr_bits(val,REG_INFO.timecntclr());	//CSR15[8:8]
	return *this;
}
uint
DS_rxRegs::gettimecntclr(){
	return get_csr_bits(REG_INFO.timecntclr());	//CSR15[8:8]
}

DS_rxRegs&
DS_rxRegs::setloscfg(uint val){
	fill_csr_bits(val,REG_INFO.loscfg());	//CSR15[7:5]
	return *this;
}
uint
DS_rxRegs::getloscfg(){
	return get_csr_bits(REG_INFO.loscfg());	//CSR15[7:5]
}

uint
DS_rxRegs::getlos(){
	return get_csr_bits(REG_INFO.los());	//CSR15[4:4]
}

uint
DS_rxRegs::getlostran(){
	return get_csr_bits(REG_INFO.lostran());	//CSR15[3:3]
}

uint
DS_rxRegs::getloseyever(){
	return get_csr_bits(REG_INFO.loseyever());	//CSR15[2:2]
}

uint
DS_rxRegs::getloseyehor(){
	return get_csr_bits(REG_INFO.loseyehor());	//CSR15[1:1]
}

uint
DS_rxRegs::getlosana(){
	return get_csr_bits(REG_INFO.losana());	//CSR15[0:0]
}

DS_rxRegs&
DS_rxRegs::settimecntstart(uint val){
	fill_csr_bits(val,REG_INFO.timecntstart());	//CSR16[15:15]
	return *this;
}
uint
DS_rxRegs::gettimecntstart(){
	return get_csr_bits(REG_INFO.timecntstart());	//CSR16[15:15]
}

DS_rxRegs&
DS_rxRegs::setmoniqofst(uint val){
	fill_csr_bits(val,REG_INFO.moniqofst());	//CSR16[14:8]
	return *this;
}
uint
DS_rxRegs::getmoniqofst(){
	return get_csr_bits(REG_INFO.moniqofst());	//CSR16[14:8]
}

DS_rxRegs&
DS_rxRegs::setprbsemdatasel(uint val){
	fill_csr_bits(val,REG_INFO.prbsemdatasel());	//CSR16[7:7]
	return *this;
}
uint
DS_rxRegs::getprbsemdatasel(){
	return get_csr_bits(REG_INFO.prbsemdatasel());	//CSR16[7:7]
}

DS_rxRegs&
DS_rxRegs::setvolofstpol(uint val){
	fill_csr_bits(val,REG_INFO.volofstpol());	//CSR16[6:6]
	return *this;
}
uint
DS_rxRegs::getvolofstpol(){
	return get_csr_bits(REG_INFO.volofstpol());	//CSR16[6:6]
}

DS_rxRegs&
DS_rxRegs::setprbschken(uint val){
	fill_csr_bits(val,REG_INFO.prbschken());	//CSR16[5:5]
	return *this;
}
uint
DS_rxRegs::getprbschken(){
	return get_csr_bits(REG_INFO.prbschken());	//CSR16[5:5]
}

DS_rxRegs&
DS_rxRegs::setprbschkmode(uint val){
	fill_csr_bits(val,REG_INFO.prbschkmode());	//CSR16[4:4]
	return *this;
}
uint
DS_rxRegs::getprbschkmode(){
	return get_csr_bits(REG_INFO.prbschkmode());	//CSR16[4:4]
}

DS_rxRegs&
DS_rxRegs::setprbschkpatsel(uint val){
	fill_csr_bits(val,REG_INFO.prbschkpatsel());	//CSR16[3:0]
	return *this;
}
uint
DS_rxRegs::getprbschkpatsel(){
	return get_csr_bits(REG_INFO.prbschkpatsel());	//CSR16[3:0]
}

DS_rxRegs&
DS_rxRegs::seteyemonpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.eyemonpwrdb());	//CSR17[15:15]
	return *this;
}
uint
DS_rxRegs::geteyemonpwrdb(){
	return get_csr_bits(REG_INFO.eyemonpwrdb());	//CSR17[15:15]
}

DS_rxRegs&
DS_rxRegs::seteyescanstart(uint val){
	fill_csr_bits(val,REG_INFO.eyescanstart());	//CSR17[14:14]
	return *this;
}
uint
DS_rxRegs::geteyescanstart(){
	return get_csr_bits(REG_INFO.eyescanstart());	//CSR17[14:14]
}

uint
DS_rxRegs::getemready(){
	return get_csr_bits(REG_INFO.emready());	//CSR17[13:13]
}

uint
DS_rxRegs::getemtaskstatus(){
	return get_csr_bits(REG_INFO.emtaskstatus());	//CSR17[12:12]
}

DS_rxRegs&
DS_rxRegs::seteyescanmode(uint val){
	fill_csr_bits(val,REG_INFO.eyescanmode());	//CSR17[11:9]
	return *this;
}
uint
DS_rxRegs::geteyescanmode(){
	return get_csr_bits(REG_INFO.eyescanmode());	//CSR17[11:9]
}

uint
DS_rxRegs::getemvolovrmax(){
	return get_csr_bits(REG_INFO.emvolovrmax());	//CSR17[8:8]
}

DS_rxRegs&
DS_rxRegs::setcompeyeen(uint val){
	fill_csr_bits(val,REG_INFO.compeyeen());	//CSR17[7:7]
	return *this;
}
uint
DS_rxRegs::getcompeyeen(){
	return get_csr_bits(REG_INFO.compeyeen());	//CSR17[7:7]
}

DS_rxRegs&
DS_rxRegs::seteyescanwinsel(uint val){
	fill_csr_bits(val,REG_INFO.eyescanwinsel());	//CSR17[6:6]
	return *this;
}
uint
DS_rxRegs::geteyescanwinsel(){
	return get_csr_bits(REG_INFO.eyescanwinsel());	//CSR17[6:6]
}

DS_rxRegs&
DS_rxRegs::seteyescanwin(uint val){
	fill_csr_bits(val,REG_INFO.eyescanwin());	//CSR17[5:0]
	return *this;
}
uint
DS_rxRegs::geteyescanwin(){
	return get_csr_bits(REG_INFO.eyescanwin());	//CSR17[5:0]
}

DS_rxRegs&
DS_rxRegs::setmphsofst(uint val){
	fill_csr_bits(val,REG_INFO.mphsofst());	//CSR18[8:0]
	return *this;
}
uint
DS_rxRegs::getmphsofst(){
	return get_csr_bits(REG_INFO.mphsofst());	//CSR18[8:0]
}

DS_rxRegs&
DS_rxRegs::setceniqofst(uint val){
	fill_csr_bits(val,REG_INFO.ceniqofst());	//CSR19[15:9]
	return *this;
}
uint
DS_rxRegs::getceniqofst(){
	return get_csr_bits(REG_INFO.ceniqofst());	//CSR19[15:9]
}

DS_rxRegs&
DS_rxRegs::setmonslcsel(uint val){
	fill_csr_bits(val,REG_INFO.monslcsel());	//CSR19[8:7]
	return *this;
}
uint
DS_rxRegs::getmonslcsel(){
	return get_csr_bits(REG_INFO.monslcsel());	//CSR19[8:7]
}

DS_rxRegs&
DS_rxRegs::setedgiqofst(uint val){
	fill_csr_bits(val,REG_INFO.edgiqofst());	//CSR19[6:0]
	return *this;
}
uint
DS_rxRegs::getedgiqofst(){
	return get_csr_bits(REG_INFO.edgiqofst());	//CSR19[6:0]
}

uint
DS_rxRegs::getprbserr(){
	return get_csr_bits(REG_INFO.prbserr());	//CSR20[15:15]
}

uint
DS_rxRegs::getprbscntexp(){
	return get_csr_bits(REG_INFO.prbscntexp());	//CSR20[14:11]
}

uint
DS_rxRegs::getprbscnt(){
	return get_csr_bits(REG_INFO.prbscnt());	//CSR20[10:0]
}

DS_rxRegs&
DS_rxRegs::setmmthr(uint val){
	fill_csr_bits(val,REG_INFO.mmthr());	//CSR21[15:0]
	return *this;
}
uint
DS_rxRegs::getmmthr(){
	return get_csr_bits(REG_INFO.mmthr());	//CSR21[15:0]
}

DS_rxRegs&
DS_rxRegs::setemfoureyesel(uint val){
	fill_csr_bits(val,REG_INFO.emfoureyesel());	//CSR22[13:12]
	return *this;
}
uint
DS_rxRegs::getemfoureyesel(){
	return get_csr_bits(REG_INFO.emfoureyesel());	//CSR22[13:12]
}

DS_rxRegs&
DS_rxRegs::setmvolofst(uint val){
	fill_csr_bits(val,REG_INFO.mvolofst());	//CSR22[8:0]
	return *this;
}
uint
DS_rxRegs::getmvolofst(){
	return get_csr_bits(REG_INFO.mvolofst());	//CSR22[8:0]
}

uint
DS_rxRegs::getemresult0(){
	return get_csr_bits(REG_INFO.emresult0());	//CSR23[8:0]
}

uint
DS_rxRegs::getemresult1(){
	return get_csr_bits(REG_INFO.emresult1());	//CSR24[8:0]
}

DS_rxRegs&
DS_rxRegs::seteyescanctrl(uint val){
	fill_csr_bits(val,REG_INFO.eyescanctrl());	//CSR25[15:12]
	return *this;
}
uint
DS_rxRegs::geteyescanctrl(){
	return get_csr_bits(REG_INFO.eyescanctrl());	//CSR25[15:12]
}

DS_rxRegs&
DS_rxRegs::seteyemontask(uint val){
	fill_csr_bits(val,REG_INFO.eyemontask());	//CSR25[11:8]
	return *this;
}
uint
DS_rxRegs::geteyemontask(){
	return get_csr_bits(REG_INFO.eyemontask());	//CSR25[11:8]
}

DS_rxRegs&
DS_rxRegs::seteyescanalg(uint val){
	fill_csr_bits(val,REG_INFO.eyescanalg());	//CSR25[7:7]
	return *this;
}
uint
DS_rxRegs::geteyescanalg(){
	return get_csr_bits(REG_INFO.eyescanalg());	//CSR25[7:7]
}

DS_rxRegs&
DS_rxRegs::setemtaskctrl(uint val){
	fill_csr_bits(val,REG_INFO.emtaskctrl());	//CSR25[6:2]
	return *this;
}
uint
DS_rxRegs::getemtaskctrl(){
	return get_csr_bits(REG_INFO.emtaskctrl());	//CSR25[6:2]
}

DS_rxRegs&
DS_rxRegs::setemcornerscaling(uint val){
	fill_csr_bits(val,REG_INFO.emcornerscaling());	//CSR25[1:1]
	return *this;
}
uint
DS_rxRegs::getemcornerscaling(){
	return get_csr_bits(REG_INFO.emcornerscaling());	//CSR25[1:1]
}

DS_rxRegs&
DS_rxRegs::setemcornergrden(uint val){
	fill_csr_bits(val,REG_INFO.emcornergrden());	//CSR25[0:0]
	return *this;
}
uint
DS_rxRegs::getemcornergrden(){
	return get_csr_bits(REG_INFO.emcornergrden());	//CSR25[0:0]
}

DS_rxRegs&
DS_rxRegs::setmonvolscanstltime(uint val){
	fill_csr_bits(val,REG_INFO.monvolscanstltime());	//CSR26[7:0]
	return *this;
}
uint
DS_rxRegs::getmonvolscanstltime(){
	return get_csr_bits(REG_INFO.monvolscanstltime());	//CSR26[7:0]
}

DS_rxRegs&
DS_rxRegs::setemtaskavrg(uint val){
	fill_csr_bits(val,REG_INFO.emtaskavrg());	//CSR27[15:12]
	return *this;
}
uint
DS_rxRegs::getemtaskavrg(){
	return get_csr_bits(REG_INFO.emtaskavrg());	//CSR27[15:12]
}

DS_rxRegs&
DS_rxRegs::setcornerofst0(uint val){
	fill_csr_bits(val,REG_INFO.cornerofst0());	//CSR27[8:0]
	return *this;
}
uint
DS_rxRegs::getcornerofst0(){
	return get_csr_bits(REG_INFO.cornerofst0());	//CSR27[8:0]
}

DS_rxRegs&
DS_rxRegs::setcornerofst1(uint val){
	fill_csr_bits(val,REG_INFO.cornerofst1());	//CSR28[8:0]
	return *this;
}
uint
DS_rxRegs::getcornerofst1(){
	return get_csr_bits(REG_INFO.cornerofst1());	//CSR28[8:0]
}

uint
DS_rxRegs::getemresult2(){
	return get_csr_bits(REG_INFO.emresult2());	//CSR29[15:0]
}

DS_rxRegs&
DS_rxRegs::setmvolmax(uint val){
	fill_csr_bits(val,REG_INFO.mvolmax());	//CSR30[8:0]
	return *this;
}
uint
DS_rxRegs::getmvolmax(){
	return get_csr_bits(REG_INFO.mvolmax());	//CSR30[8:0]
}

DS_rxRegs&
DS_rxRegs::setrxtermcalsel(uint val){
	fill_csr_bits(val,REG_INFO.rxtermcalsel());	//CSR31[15:15]
	return *this;
}
uint
DS_rxRegs::getrxtermcalsel(){
	return get_csr_bits(REG_INFO.rxtermcalsel());	//CSR31[15:15]
}

DS_rxRegs&
DS_rxRegs::setrxtermcaldir(uint val){
	fill_csr_bits(val,REG_INFO.rxtermcaldir());	//CSR31[14:14]
	return *this;
}
uint
DS_rxRegs::getrxtermcaldir(){
	return get_csr_bits(REG_INFO.rxtermcaldir());	//CSR31[14:14]
}

DS_rxRegs&
DS_rxRegs::setrxlatofstrangescale(uint val){
	fill_csr_bits(val,REG_INFO.rxlatofstrangescale());	//CSR31[13:13]
	return *this;
}
uint
DS_rxRegs::getrxlatofstrangescale(){
	return get_csr_bits(REG_INFO.rxlatofstrangescale());	//CSR31[13:13]
}

DS_rxRegs&
DS_rxRegs::setrxctlerepopcalmode(uint val){
	fill_csr_bits(val,REG_INFO.rxctlerepopcalmode());	//CSR31[12:12]
	return *this;
}
uint
DS_rxRegs::getrxctlerepopcalmode(){
	return get_csr_bits(REG_INFO.rxctlerepopcalmode());	//CSR31[12:12]
}

DS_rxRegs&
DS_rxRegs::setrxtermcal(uint val){
	fill_csr_bits(val,REG_INFO.rxtermcal());	//CSR31[3:0]
	return *this;
}
uint
DS_rxRegs::getrxtermcal(){
	return get_csr_bits(REG_INFO.rxtermcal());	//CSR31[3:0]
}

DS_rxRegs&
DS_rxRegs::setrxcalmode(uint val){
	fill_csr_bits(val,REG_INFO.rxcalmode());	//CSR32[15:15]
	return *this;
}
uint
DS_rxRegs::getrxcalmode(){
	return get_csr_bits(REG_INFO.rxcalmode());	//CSR32[15:15]
}

DS_rxRegs&
DS_rxRegs::setdscalstart(uint val){
	fill_csr_bits(val,REG_INFO.dscalstart());	//CSR32[14:14]
	return *this;
}
uint
DS_rxRegs::getdscalstart(){
	return get_csr_bits(REG_INFO.dscalstart());	//CSR32[14:14]
}

DS_rxRegs&
DS_rxRegs::setrxcalstart(uint val){
	fill_csr_bits(val,REG_INFO.rxcalstart());	//CSR32[13:13]
	return *this;
}
uint
DS_rxRegs::getrxcalstart(){
	return get_csr_bits(REG_INFO.rxcalstart());	//CSR32[13:13]
}

DS_rxRegs&
DS_rxRegs::setrxtermfloating(uint val){
	fill_csr_bits(val,REG_INFO.rxtermfloating());	//CSR32[12:12]
	return *this;
}
uint
DS_rxRegs::getrxtermfloating(){
	return get_csr_bits(REG_INFO.rxtermfloating());	//CSR32[12:12]
}

DS_rxRegs&
DS_rxRegs::setrxdatalatchcalen(uint val){
	fill_csr_bits(val,REG_INFO.rxdatalatchcalen());	//CSR32[7:7]
	return *this;
}
uint
DS_rxRegs::getrxdatalatchcalen(){
	return get_csr_bits(REG_INFO.rxdatalatchcalen());	//CSR32[7:7]
}

DS_rxRegs&
DS_rxRegs::setrxofstcaldir(uint val){
	fill_csr_bits(val,REG_INFO.rxofstcaldir());	//CSR32[6:6]
	return *this;
}
uint
DS_rxRegs::getrxofstcaldir(){
	return get_csr_bits(REG_INFO.rxofstcaldir());	//CSR32[6:6]
}

DS_rxRegs&
DS_rxRegs::setrxofstsel(uint val){
	fill_csr_bits(val,REG_INFO.rxofstsel());	//CSR32[5:0]
	return *this;
}
uint
DS_rxRegs::getrxofstsel(){
	return get_csr_bits(REG_INFO.rxofstsel());	//CSR32[5:0]
}

DS_rxRegs&
DS_rxRegs::setctleofst1(uint val){
	fill_csr_bits(val,REG_INFO.ctleofst1());	//CSR33[14:10]
	return *this;
}
uint
DS_rxRegs::getctleofst1(){
	return get_csr_bits(REG_INFO.ctleofst1());	//CSR33[14:10]
}

DS_rxRegs&
DS_rxRegs::setctleofst2(uint val){
	fill_csr_bits(val,REG_INFO.ctleofst2());	//CSR33[9:5]
	return *this;
}
uint
DS_rxRegs::getctleofst2(){
	return get_csr_bits(REG_INFO.ctleofst2());	//CSR33[9:5]
}

DS_rxRegs&
DS_rxRegs::setctleofst3(uint val){
	fill_csr_bits(val,REG_INFO.ctleofst3());	//CSR33[4:0]
	return *this;
}
uint
DS_rxRegs::getctleofst3(){
	return get_csr_bits(REG_INFO.ctleofst3());	//CSR33[4:0]
}

DS_rxRegs&
DS_rxRegs::setctleofst4(uint val){
	fill_csr_bits(val,REG_INFO.ctleofst4());	//CSR34[14:10]
	return *this;
}
uint
DS_rxRegs::getctleofst4(){
	return get_csr_bits(REG_INFO.ctleofst4());	//CSR34[14:10]
}

DS_rxRegs&
DS_rxRegs::setctleofst5(uint val){
	fill_csr_bits(val,REG_INFO.ctleofst5());	//CSR34[9:5]
	return *this;
}
uint
DS_rxRegs::getctleofst5(){
	return get_csr_bits(REG_INFO.ctleofst5());	//CSR34[9:5]
}

DS_rxRegs&
DS_rxRegs::setctleofst6(uint val){
	fill_csr_bits(val,REG_INFO.ctleofst6());	//CSR34[4:0]
	return *this;
}
uint
DS_rxRegs::getctleofst6(){
	return get_csr_bits(REG_INFO.ctleofst6());	//CSR34[4:0]
}

DS_rxRegs&
DS_rxRegs::setdfeievnsumofst(uint val){
	fill_csr_bits(val,REG_INFO.dfeievnsumofst());	//CSR35[14:10]
	return *this;
}
uint
DS_rxRegs::getdfeievnsumofst(){
	return get_csr_bits(REG_INFO.dfeievnsumofst());	//CSR35[14:10]
}

DS_rxRegs&
DS_rxRegs::setdfeioddsumofst(uint val){
	fill_csr_bits(val,REG_INFO.dfeioddsumofst());	//CSR35[9:5]
	return *this;
}
uint
DS_rxRegs::getdfeioddsumofst(){
	return get_csr_bits(REG_INFO.dfeioddsumofst());	//CSR35[9:5]
}

DS_rxRegs&
DS_rxRegs::setdfeqevnsumofst(uint val){
	fill_csr_bits(val,REG_INFO.dfeqevnsumofst());	//CSR35[4:0]
	return *this;
}
uint
DS_rxRegs::getdfeqevnsumofst(){
	return get_csr_bits(REG_INFO.dfeqevnsumofst());	//CSR35[4:0]
}

DS_rxRegs&
DS_rxRegs::setdfeqoddsumofst(uint val){
	fill_csr_bits(val,REG_INFO.dfeqoddsumofst());	//CSR36[14:10]
	return *this;
}
uint
DS_rxRegs::getdfeqoddsumofst(){
	return get_csr_bits(REG_INFO.dfeqoddsumofst());	//CSR36[14:10]
}

DS_rxRegs&
DS_rxRegs::setrxctleibiastune(uint val){
	fill_csr_bits(val,REG_INFO.rxctleibiastune());	//CSR36[7:5]
	return *this;
}
uint
DS_rxRegs::getrxctleibiastune(){
	return get_csr_bits(REG_INFO.rxctleibiastune());	//CSR36[7:5]
}

DS_rxRegs&
DS_rxRegs::setrxctlepasstune(uint val){
	fill_csr_bits(val,REG_INFO.rxctlepasstune());	//CSR36[2:0]
	return *this;
}
uint
DS_rxRegs::getrxctlepasstune(){
	return get_csr_bits(REG_INFO.rxctlepasstune());	//CSR36[2:0]
}

DS_rxRegs&
DS_rxRegs::setctleiptattcctrl(uint val){
	fill_csr_bits(val,REG_INFO.ctleiptattcctrl());	//CSR37[11:8]
	return *this;
}
uint
DS_rxRegs::getctleiptattcctrl(){
	return get_csr_bits(REG_INFO.ctleiptattcctrl());	//CSR37[11:8]
}

DS_rxRegs&
DS_rxRegs::setctleiptatbypass(uint val){
	fill_csr_bits(val,REG_INFO.ctleiptatbypass());	//CSR37[6:6]
	return *this;
}
uint
DS_rxRegs::getctleiptatbypass(){
	return get_csr_bits(REG_INFO.ctleiptatbypass());	//CSR37[6:6]
}

DS_rxRegs&
DS_rxRegs::setctlescresen(uint val){
	fill_csr_bits(val,REG_INFO.ctlescresen());	//CSR37[5:5]
	return *this;
}
uint
DS_rxRegs::getctlescresen(){
	return get_csr_bits(REG_INFO.ctlescresen());	//CSR37[5:5]
}

DS_rxRegs&
DS_rxRegs::setctlescresclkdiv(uint val){
	fill_csr_bits(val,REG_INFO.ctlescresclkdiv());	//CSR37[4:0]
	return *this;
}
uint
DS_rxRegs::getctlescresclkdiv(){
	return get_csr_bits(REG_INFO.ctlescresclkdiv());	//CSR37[4:0]
}

DS_rxRegs&
DS_rxRegs::setrxsigdetpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxsigdetpwrdb());	//CSR38[15:15]
	return *this;
}
uint
DS_rxRegs::getrxsigdetpwrdb(){
	return get_csr_bits(REG_INFO.rxsigdetpwrdb());	//CSR38[15:15]
}

DS_rxRegs&
DS_rxRegs::setrxsigdetclkdiv(uint val){
	fill_csr_bits(val,REG_INFO.rxsigdetclkdiv());	//CSR38[14:13]
	return *this;
}
uint
DS_rxRegs::getrxsigdetclkdiv(){
	return get_csr_bits(REG_INFO.rxsigdetclkdiv());	//CSR38[14:13]
}

DS_rxRegs&
DS_rxRegs::setrxsigdetclkdlysel(uint val){
	fill_csr_bits(val,REG_INFO.rxsigdetclkdlysel());	//CSR38[12:12]
	return *this;
}
uint
DS_rxRegs::getrxsigdetclkdlysel(){
	return get_csr_bits(REG_INFO.rxsigdetclkdlysel());	//CSR38[12:12]
}

DS_rxRegs&
DS_rxRegs::setrxsigdetcalpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxsigdetcalpwrdb());	//CSR38[10:10]
	return *this;
}
uint
DS_rxRegs::getrxsigdetcalpwrdb(){
	return get_csr_bits(REG_INFO.rxsigdetcalpwrdb());	//CSR38[10:10]
}

DS_rxRegs&
DS_rxRegs::setrxdigdetclkbufen(uint val){
	fill_csr_bits(val,REG_INFO.rxdigdetclkbufen());	//CSR38[9:9]
	return *this;
}
uint
DS_rxRegs::getrxdigdetclkbufen(){
	return get_csr_bits(REG_INFO.rxdigdetclkbufen());	//CSR38[9:9]
}

DS_rxRegs&
DS_rxRegs::setrxsigdetatbsel(uint val){
	fill_csr_bits(val,REG_INFO.rxsigdetatbsel());	//CSR38[8:8]
	return *this;
}
uint
DS_rxRegs::getrxsigdetatbsel(){
	return get_csr_bits(REG_INFO.rxsigdetatbsel());	//CSR38[8:8]
}

DS_rxRegs&
DS_rxRegs::setrxsigdetvthres(uint val){
	fill_csr_bits(val,REG_INFO.rxsigdetvthres());	//CSR39[13:10]
	return *this;
}
uint
DS_rxRegs::getrxsigdetvthres(){
	return get_csr_bits(REG_INFO.rxsigdetvthres());	//CSR39[13:10]
}

DS_rxRegs&
DS_rxRegs::setrxsigdethyst(uint val){
	fill_csr_bits(val,REG_INFO.rxsigdethyst());	//CSR39[9:8]
	return *this;
}
uint
DS_rxRegs::getrxsigdethyst(){
	return get_csr_bits(REG_INFO.rxsigdethyst());	//CSR39[9:8]
}

DS_rxRegs&
DS_rxRegs::setrxsigdetoffset(uint val){
	fill_csr_bits(val,REG_INFO.rxsigdetoffset());	//CSR39[4:0]
	return *this;
}
uint
DS_rxRegs::getrxsigdetoffset(){
	return get_csr_bits(REG_INFO.rxsigdetoffset());	//CSR39[4:0]
}

uint
DS_rxRegs::getsigdetsqlchlos(){
	return get_csr_bits(REG_INFO.sigdetsqlchlos());	//CSR40[15:15]
}

uint
DS_rxRegs::getsigdetlos(){
	return get_csr_bits(REG_INFO.sigdetlos());	//CSR40[14:14]
}

DS_rxRegs&
DS_rxRegs::setsigdettxrxstat(uint val){
	fill_csr_bits(val,REG_INFO.sigdettxrxstat());	//CSR40[13:13]
	return *this;
}
uint
DS_rxRegs::getsigdettxrxstat(){
	return get_csr_bits(REG_INFO.sigdettxrxstat());	//CSR40[13:13]
}

DS_rxRegs&
DS_rxRegs::setsigdetwin(uint val){
	fill_csr_bits(val,REG_INFO.sigdetwin());	//CSR40[11:8]
	return *this;
}
uint
DS_rxRegs::getsigdetwin(){
	return get_csr_bits(REG_INFO.sigdetwin());	//CSR40[11:8]
}

DS_rxRegs&
DS_rxRegs::setsigdetpmamode(uint val){
	fill_csr_bits(val,REG_INFO.sigdetpmamode());	//CSR40[6:5]
	return *this;
}
uint
DS_rxRegs::getsigdetpmamode(){
	return get_csr_bits(REG_INFO.sigdetpmamode());	//CSR40[6:5]
}

DS_rxRegs&
DS_rxRegs::setsigdetmanual(uint val){
	fill_csr_bits(val,REG_INFO.sigdetmanual());	//CSR40[4:4]
	return *this;
}
uint
DS_rxRegs::getsigdetmanual(){
	return get_csr_bits(REG_INFO.sigdetmanual());	//CSR40[4:4]
}

DS_rxRegs&
DS_rxRegs::setsigdetthrselman(uint val){
	fill_csr_bits(val,REG_INFO.sigdetthrselman());	//CSR40[3:1]
	return *this;
}
uint
DS_rxRegs::getsigdetthrselman(){
	return get_csr_bits(REG_INFO.sigdetthrselman());	//CSR40[3:1]
}

DS_rxRegs&
DS_rxRegs::setsigdeten(uint val){
	fill_csr_bits(val,REG_INFO.sigdeten());	//CSR40[0:0]
	return *this;
}
uint
DS_rxRegs::getsigdeten(){
	return get_csr_bits(REG_INFO.sigdeten());	//CSR40[0:0]
}

DS_rxRegs&
DS_rxRegs::setsigdetthrcfgsel(uint val){
	fill_csr_bits(val,REG_INFO.sigdetthrcfgsel());	//CSR41[14:12]
	return *this;
}
uint
DS_rxRegs::getsigdetthrcfgsel(){
	return get_csr_bits(REG_INFO.sigdetthrcfgsel());	//CSR41[14:12]
}

DS_rxRegs&
DS_rxRegs::setsigdetthrs1(uint val){
	fill_csr_bits(val,REG_INFO.sigdetthrs1());	//CSR41[10:0]
	return *this;
}
uint
DS_rxRegs::getsigdetthrs1(){
	return get_csr_bits(REG_INFO.sigdetthrs1());	//CSR41[10:0]
}

DS_rxRegs&
DS_rxRegs::setsigdetthrs2(uint val){
	fill_csr_bits(val,REG_INFO.sigdetthrs2());	//CSR42[10:0]
	return *this;
}
uint
DS_rxRegs::getsigdetthrs2(){
	return get_csr_bits(REG_INFO.sigdetthrs2());	//CSR42[10:0]
}

DS_rxRegs&
DS_rxRegs::setsigdetthrs3(uint val){
	fill_csr_bits(val,REG_INFO.sigdetthrs3());	//CSR43[10:0]
	return *this;
}
uint
DS_rxRegs::getsigdetthrs3(){
	return get_csr_bits(REG_INFO.sigdetthrs3());	//CSR43[10:0]
}

uint
DS_rxRegs::getrxctlerepofftrig(){
	return get_csr_bits(REG_INFO.rxctlerepofftrig());	//CSR44[15:15]
}

DS_rxRegs&
DS_rxRegs::setctlestg1to4pwrdb(uint val){
	fill_csr_bits(val,REG_INFO.ctlestg1to4pwrdb());	//CSR44[14:14]
	return *this;
}
uint
DS_rxRegs::getctlestg1to4pwrdb(){
	return get_csr_bits(REG_INFO.ctlestg1to4pwrdb());	//CSR44[14:14]
}

DS_rxRegs&
DS_rxRegs::setreplicacaldir(uint val){
	fill_csr_bits(val,REG_INFO.replicacaldir());	//CSR44[13:13]
	return *this;
}
uint
DS_rxRegs::getreplicacaldir(){
	return get_csr_bits(REG_INFO.replicacaldir());	//CSR44[13:13]
}

DS_rxRegs&
DS_rxRegs::setctlerepcalen(uint val){
	fill_csr_bits(val,REG_INFO.ctlerepcalen());	//CSR44[12:12]
	return *this;
}
uint
DS_rxRegs::getctlerepcalen(){
	return get_csr_bits(REG_INFO.ctlerepcalen());	//CSR44[12:12]
}

DS_rxRegs&
DS_rxRegs::setctlerepcalcode(uint val){
	fill_csr_bits(val,REG_INFO.ctlerepcalcode());	//CSR44[11:6]
	return *this;
}
uint
DS_rxRegs::getctlerepcalcode(){
	return get_csr_bits(REG_INFO.ctlerepcalcode());	//CSR44[11:6]
}

DS_rxRegs&
DS_rxRegs::setctlerefsel(uint val){
	fill_csr_bits(val,REG_INFO.ctlerefsel());	//CSR44[5:3]
	return *this;
}
uint
DS_rxRegs::getctlerefsel(){
	return get_csr_bits(REG_INFO.ctlerefsel());	//CSR44[5:3]
}

DS_rxRegs&
DS_rxRegs::setctleloadsel(uint val){
	fill_csr_bits(val,REG_INFO.ctleloadsel());	//CSR44[2:0]
	return *this;
}
uint
DS_rxRegs::getctleloadsel(){
	return get_csr_bits(REG_INFO.ctleloadsel());	//CSR44[2:0]
}

DS_rxRegs&
DS_rxRegs::setdspwrsqtbs3(uint val){
	fill_csr_bits(val,REG_INFO.dspwrsqtbs3());	//CSR45[13:10]
	return *this;
}
uint
DS_rxRegs::getdspwrsqtbs3(){
	return get_csr_bits(REG_INFO.dspwrsqtbs3());	//CSR45[13:10]
}

DS_rxRegs&
DS_rxRegs::setvregctlerefsel(uint val){
	fill_csr_bits(val,REG_INFO.vregctlerefsel());	//CSR45[9:4]
	return *this;
}
uint
DS_rxRegs::getvregctlerefsel(){
	return get_csr_bits(REG_INFO.vregctlerefsel());	//CSR45[9:4]
}

DS_rxRegs&
DS_rxRegs::setrxcpcendlyctrli(uint val){
	fill_csr_bits(val,REG_INFO.rxcpcendlyctrli());	//CSR45[3:2]
	return *this;
}
uint
DS_rxRegs::getrxcpcendlyctrli(){
	return get_csr_bits(REG_INFO.rxcpcendlyctrli());	//CSR45[3:2]
}

DS_rxRegs&
DS_rxRegs::setrxcpcendlyctrlq(uint val){
	fill_csr_bits(val,REG_INFO.rxcpcendlyctrlq());	//CSR45[1:0]
	return *this;
}
uint
DS_rxRegs::getrxcpcendlyctrlq(){
	return get_csr_bits(REG_INFO.rxcpcendlyctrlq());	//CSR45[1:0]
}

DS_rxRegs&
DS_rxRegs::setrxcpcenpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpcenpwrdb());	//CSR46[15:15]
	return *this;
}
uint
DS_rxRegs::getrxcpcenpwrdb(){
	return get_csr_bits(REG_INFO.rxcpcenpwrdb());	//CSR46[15:15]
}

DS_rxRegs&
DS_rxRegs::setrxcpcenipibufpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpcenipibufpwrdb());	//CSR46[13:13]
	return *this;
}
uint
DS_rxRegs::getrxcpcenipibufpwrdb(){
	return get_csr_bits(REG_INFO.rxcpcenipibufpwrdb());	//CSR46[13:13]
}

DS_rxRegs&
DS_rxRegs::setrxcpcenipicmlcmospwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpcenipicmlcmospwrdb());	//CSR46[12:12]
	return *this;
}
uint
DS_rxRegs::getrxcpcenipicmlcmospwrdb(){
	return get_csr_bits(REG_INFO.rxcpcenipicmlcmospwrdb());	//CSR46[12:12]
}

DS_rxRegs&
DS_rxRegs::setrxcpcenipicorepwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpcenipicorepwrdb());	//CSR46[11:11]
	return *this;
}
uint
DS_rxRegs::getrxcpcenipicorepwrdb(){
	return get_csr_bits(REG_INFO.rxcpcenipicorepwrdb());	//CSR46[11:11]
}

DS_rxRegs&
DS_rxRegs::setrxcpcenqpibufpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpcenqpibufpwrdb());	//CSR46[10:10]
	return *this;
}
uint
DS_rxRegs::getrxcpcenqpibufpwrdb(){
	return get_csr_bits(REG_INFO.rxcpcenqpibufpwrdb());	//CSR46[10:10]
}

DS_rxRegs&
DS_rxRegs::setrxcpcenqpicmlcmospwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpcenqpicmlcmospwrdb());	//CSR46[9:9]
	return *this;
}
uint
DS_rxRegs::getrxcpcenqpicmlcmospwrdb(){
	return get_csr_bits(REG_INFO.rxcpcenqpicmlcmospwrdb());	//CSR46[9:9]
}

DS_rxRegs&
DS_rxRegs::setrxcpcenqpicorepwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpcenqpicorepwrdb());	//CSR46[8:8]
	return *this;
}
uint
DS_rxRegs::getrxcpcenqpicorepwrdb(){
	return get_csr_bits(REG_INFO.rxcpcenqpicorepwrdb());	//CSR46[8:8]
}

DS_rxRegs&
DS_rxRegs::setrxcpcenpibiastrim(uint val){
	fill_csr_bits(val,REG_INFO.rxcpcenpibiastrim());	//CSR46[5:4]
	return *this;
}
uint
DS_rxRegs::getrxcpcenpibiastrim(){
	return get_csr_bits(REG_INFO.rxcpcenpibiastrim());	//CSR46[5:4]
}

DS_rxRegs&
DS_rxRegs::setrxcpcenpibufbiastrim(uint val){
	fill_csr_bits(val,REG_INFO.rxcpcenpibufbiastrim());	//CSR46[3:2]
	return *this;
}
uint
DS_rxRegs::getrxcpcenpibufbiastrim(){
	return get_csr_bits(REG_INFO.rxcpcenpibufbiastrim());	//CSR46[3:2]
}

DS_rxRegs&
DS_rxRegs::setrxcpcenpibufloadtrim(uint val){
	fill_csr_bits(val,REG_INFO.rxcpcenpibufloadtrim());	//CSR46[1:0]
	return *this;
}
uint
DS_rxRegs::getrxcpcenpibufloadtrim(){
	return get_csr_bits(REG_INFO.rxcpcenpibufloadtrim());	//CSR46[1:0]
}

DS_rxRegs&
DS_rxRegs::setrxcpedgpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpedgpwrdb());	//CSR47[15:15]
	return *this;
}
uint
DS_rxRegs::getrxcpedgpwrdb(){
	return get_csr_bits(REG_INFO.rxcpedgpwrdb());	//CSR47[15:15]
}

DS_rxRegs&
DS_rxRegs::setrxcpedgipibufpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpedgipibufpwrdb());	//CSR47[14:14]
	return *this;
}
uint
DS_rxRegs::getrxcpedgipibufpwrdb(){
	return get_csr_bits(REG_INFO.rxcpedgipibufpwrdb());	//CSR47[14:14]
}

DS_rxRegs&
DS_rxRegs::setrxcpedgipicmlcmospwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpedgipicmlcmospwrdb());	//CSR47[13:13]
	return *this;
}
uint
DS_rxRegs::getrxcpedgipicmlcmospwrdb(){
	return get_csr_bits(REG_INFO.rxcpedgipicmlcmospwrdb());	//CSR47[13:13]
}

DS_rxRegs&
DS_rxRegs::setrxcpedgipicorepwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpedgipicorepwrdb());	//CSR47[12:12]
	return *this;
}
uint
DS_rxRegs::getrxcpedgipicorepwrdb(){
	return get_csr_bits(REG_INFO.rxcpedgipicorepwrdb());	//CSR47[12:12]
}

DS_rxRegs&
DS_rxRegs::setrxcpedgqpibufpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpedgqpibufpwrdb());	//CSR47[11:11]
	return *this;
}
uint
DS_rxRegs::getrxcpedgqpibufpwrdb(){
	return get_csr_bits(REG_INFO.rxcpedgqpibufpwrdb());	//CSR47[11:11]
}

DS_rxRegs&
DS_rxRegs::setrxcpedgqpicmlcmospwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpedgqpicmlcmospwrdb());	//CSR47[10:10]
	return *this;
}
uint
DS_rxRegs::getrxcpedgqpicmlcmospwrdb(){
	return get_csr_bits(REG_INFO.rxcpedgqpicmlcmospwrdb());	//CSR47[10:10]
}

DS_rxRegs&
DS_rxRegs::setrxcpedgqpicorepwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpedgqpicorepwrdb());	//CSR47[9:9]
	return *this;
}
uint
DS_rxRegs::getrxcpedgqpicorepwrdb(){
	return get_csr_bits(REG_INFO.rxcpedgqpicorepwrdb());	//CSR47[9:9]
}

DS_rxRegs&
DS_rxRegs::setrxcpedgdlyctrli(uint val){
	fill_csr_bits(val,REG_INFO.rxcpedgdlyctrli());	//CSR47[8:7]
	return *this;
}
uint
DS_rxRegs::getrxcpedgdlyctrli(){
	return get_csr_bits(REG_INFO.rxcpedgdlyctrli());	//CSR47[8:7]
}

DS_rxRegs&
DS_rxRegs::setrxcpedgdlyctrlq(uint val){
	fill_csr_bits(val,REG_INFO.rxcpedgdlyctrlq());	//CSR47[6:5]
	return *this;
}
uint
DS_rxRegs::getrxcpedgdlyctrlq(){
	return get_csr_bits(REG_INFO.rxcpedgdlyctrlq());	//CSR47[6:5]
}

DS_rxRegs&
DS_rxRegs::setrxcpcenphsgenspare(uint val){
	fill_csr_bits(val,REG_INFO.rxcpcenphsgenspare());	//CSR47[4:3]
	return *this;
}
uint
DS_rxRegs::getrxcpcenphsgenspare(){
	return get_csr_bits(REG_INFO.rxcpcenphsgenspare());	//CSR47[4:3]
}

DS_rxRegs&
DS_rxRegs::setrxcpedgphsgenspare(uint val){
	fill_csr_bits(val,REG_INFO.rxcpedgphsgenspare());	//CSR47[2:1]
	return *this;
}
uint
DS_rxRegs::getrxcpedgphsgenspare(){
	return get_csr_bits(REG_INFO.rxcpedgphsgenspare());	//CSR47[2:1]
}

DS_rxRegs&
DS_rxRegs::setrxiqdetpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxiqdetpwrdb());	//CSR47[0:0]
	return *this;
}
uint
DS_rxRegs::getrxiqdetpwrdb(){
	return get_csr_bits(REG_INFO.rxiqdetpwrdb());	//CSR47[0:0]
}

DS_rxRegs&
DS_rxRegs::setrxcpmonpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpmonpwrdb());	//CSR48[15:15]
	return *this;
}
uint
DS_rxRegs::getrxcpmonpwrdb(){
	return get_csr_bits(REG_INFO.rxcpmonpwrdb());	//CSR48[15:15]
}

DS_rxRegs&
DS_rxRegs::setrxcpmonqpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpmonqpwrdb());	//CSR48[14:14]
	return *this;
}
uint
DS_rxRegs::getrxcpmonqpwrdb(){
	return get_csr_bits(REG_INFO.rxcpmonqpwrdb());	//CSR48[14:14]
}

DS_rxRegs&
DS_rxRegs::setrxcpmonipibufpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpmonipibufpwrdb());	//CSR48[13:13]
	return *this;
}
uint
DS_rxRegs::getrxcpmonipibufpwrdb(){
	return get_csr_bits(REG_INFO.rxcpmonipibufpwrdb());	//CSR48[13:13]
}

DS_rxRegs&
DS_rxRegs::setrxcpmonipicmlcmospwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpmonipicmlcmospwrdb());	//CSR48[12:12]
	return *this;
}
uint
DS_rxRegs::getrxcpmonipicmlcmospwrdb(){
	return get_csr_bits(REG_INFO.rxcpmonipicmlcmospwrdb());	//CSR48[12:12]
}

DS_rxRegs&
DS_rxRegs::setrxcpmonipicorepwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpmonipicorepwrdb());	//CSR48[11:11]
	return *this;
}
uint
DS_rxRegs::getrxcpmonipicorepwrdb(){
	return get_csr_bits(REG_INFO.rxcpmonipicorepwrdb());	//CSR48[11:11]
}

DS_rxRegs&
DS_rxRegs::setrxcpmonqpibufpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpmonqpibufpwrdb());	//CSR48[10:10]
	return *this;
}
uint
DS_rxRegs::getrxcpmonqpibufpwrdb(){
	return get_csr_bits(REG_INFO.rxcpmonqpibufpwrdb());	//CSR48[10:10]
}

DS_rxRegs&
DS_rxRegs::setrxcpmonqpicmlcmospwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpmonqpicmlcmospwrdb());	//CSR48[9:9]
	return *this;
}
uint
DS_rxRegs::getrxcpmonqpicmlcmospwrdb(){
	return get_csr_bits(REG_INFO.rxcpmonqpicmlcmospwrdb());	//CSR48[9:9]
}

DS_rxRegs&
DS_rxRegs::setrxcpmonqpicorepwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcpmonqpicorepwrdb());	//CSR48[8:8]
	return *this;
}
uint
DS_rxRegs::getrxcpmonqpicorepwrdb(){
	return get_csr_bits(REG_INFO.rxcpmonqpicorepwrdb());	//CSR48[8:8]
}

DS_rxRegs&
DS_rxRegs::setrxmonpwrcycmode(uint val){
	fill_csr_bits(val,REG_INFO.rxmonpwrcycmode());	//CSR48[6:6]
	return *this;
}
uint
DS_rxRegs::getrxmonpwrcycmode(){
	return get_csr_bits(REG_INFO.rxmonpwrcycmode());	//CSR48[6:6]
}

DS_rxRegs&
DS_rxRegs::setrxmonpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxmonpwrdb());	//CSR48[5:5]
	return *this;
}
uint
DS_rxRegs::getrxmonpwrdb(){
	return get_csr_bits(REG_INFO.rxmonpwrdb());	//CSR48[5:5]
}

DS_rxRegs&
DS_rxRegs::setrxedgpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxedgpwrdb());	//CSR48[4:4]
	return *this;
}
uint
DS_rxRegs::getrxedgpwrdb(){
	return get_csr_bits(REG_INFO.rxedgpwrdb());	//CSR48[4:4]
}

DS_rxRegs&
DS_rxRegs::setrxcpmondlyctrli(uint val){
	fill_csr_bits(val,REG_INFO.rxcpmondlyctrli());	//CSR48[3:2]
	return *this;
}
uint
DS_rxRegs::getrxcpmondlyctrli(){
	return get_csr_bits(REG_INFO.rxcpmondlyctrli());	//CSR48[3:2]
}

DS_rxRegs&
DS_rxRegs::setrxcpmondlyctrlq(uint val){
	fill_csr_bits(val,REG_INFO.rxcpmondlyctrlq());	//CSR48[1:0]
	return *this;
}
uint
DS_rxRegs::getrxcpmondlyctrlq(){
	return get_csr_bits(REG_INFO.rxcpmondlyctrlq());	//CSR48[1:0]
}

DS_rxRegs&
DS_rxRegs::setcenslcipwrdb(uint val){
	fill_csr_bits(val,REG_INFO.censlcipwrdb());	//CSR49[15:15]
	return *this;
}
uint
DS_rxRegs::getcenslcipwrdb(){
	return get_csr_bits(REG_INFO.censlcipwrdb());	//CSR49[15:15]
}

DS_rxRegs&
DS_rxRegs::setcenslcqpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.censlcqpwrdb());	//CSR49[14:14]
	return *this;
}
uint
DS_rxRegs::getcenslcqpwrdb(){
	return get_csr_bits(REG_INFO.censlcqpwrdb());	//CSR49[14:14]
}

DS_rxRegs&
DS_rxRegs::setcenslcibpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.censlcibpwrdb());	//CSR49[13:13]
	return *this;
}
uint
DS_rxRegs::getcenslcibpwrdb(){
	return get_csr_bits(REG_INFO.censlcibpwrdb());	//CSR49[13:13]
}

DS_rxRegs&
DS_rxRegs::setcenslcqbpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.censlcqbpwrdb());	//CSR49[12:12]
	return *this;
}
uint
DS_rxRegs::getcenslcqbpwrdb(){
	return get_csr_bits(REG_INFO.censlcqbpwrdb());	//CSR49[12:12]
}

DS_rxRegs&
DS_rxRegs::setedgslcipwrdb(uint val){
	fill_csr_bits(val,REG_INFO.edgslcipwrdb());	//CSR49[11:11]
	return *this;
}
uint
DS_rxRegs::getedgslcipwrdb(){
	return get_csr_bits(REG_INFO.edgslcipwrdb());	//CSR49[11:11]
}

DS_rxRegs&
DS_rxRegs::setedgslcqpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.edgslcqpwrdb());	//CSR49[10:10]
	return *this;
}
uint
DS_rxRegs::getedgslcqpwrdb(){
	return get_csr_bits(REG_INFO.edgslcqpwrdb());	//CSR49[10:10]
}

DS_rxRegs&
DS_rxRegs::setedgslcibpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.edgslcibpwrdb());	//CSR49[9:9]
	return *this;
}
uint
DS_rxRegs::getedgslcibpwrdb(){
	return get_csr_bits(REG_INFO.edgslcibpwrdb());	//CSR49[9:9]
}

DS_rxRegs&
DS_rxRegs::setedgslcqbpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.edgslcqbpwrdb());	//CSR49[8:8]
	return *this;
}
uint
DS_rxRegs::getedgslcqbpwrdb(){
	return get_csr_bits(REG_INFO.edgslcqbpwrdb());	//CSR49[8:8]
}

DS_rxRegs&
DS_rxRegs::setmonslcipwrdb(uint val){
	fill_csr_bits(val,REG_INFO.monslcipwrdb());	//CSR49[7:7]
	return *this;
}
uint
DS_rxRegs::getmonslcipwrdb(){
	return get_csr_bits(REG_INFO.monslcipwrdb());	//CSR49[7:7]
}

DS_rxRegs&
DS_rxRegs::setmonslcibpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.monslcibpwrdb());	//CSR49[6:6]
	return *this;
}
uint
DS_rxRegs::getmonslcibpwrdb(){
	return get_csr_bits(REG_INFO.monslcibpwrdb());	//CSR49[6:6]
}

DS_rxRegs&
DS_rxRegs::setcendemuxpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.cendemuxpwrdb());	//CSR49[5:5]
	return *this;
}
uint
DS_rxRegs::getcendemuxpwrdb(){
	return get_csr_bits(REG_INFO.cendemuxpwrdb());	//CSR49[5:5]
}

DS_rxRegs&
DS_rxRegs::setedgdemuxpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.edgdemuxpwrdb());	//CSR49[4:4]
	return *this;
}
uint
DS_rxRegs::getedgdemuxpwrdb(){
	return get_csr_bits(REG_INFO.edgdemuxpwrdb());	//CSR49[4:4]
}

DS_rxRegs&
DS_rxRegs::setmondemuxpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.mondemuxpwrdb());	//CSR49[3:3]
	return *this;
}
uint
DS_rxRegs::getmondemuxpwrdb(){
	return get_csr_bits(REG_INFO.mondemuxpwrdb());	//CSR49[3:3]
}

DS_rxRegs&
DS_rxRegs::setrxcenpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxcenpwrdb());	//CSR49[2:2]
	return *this;
}
uint
DS_rxRegs::getrxcenpwrdb(){
	return get_csr_bits(REG_INFO.rxcenpwrdb());	//CSR49[2:2]
}

DS_rxRegs&
DS_rxRegs::setmonslcqpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.monslcqpwrdb());	//CSR49[1:1]
	return *this;
}
uint
DS_rxRegs::getmonslcqpwrdb(){
	return get_csr_bits(REG_INFO.monslcqpwrdb());	//CSR49[1:1]
}

DS_rxRegs&
DS_rxRegs::setmonslcqbpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.monslcqbpwrdb());	//CSR49[0:0]
	return *this;
}
uint
DS_rxRegs::getmonslcqbpwrdb(){
	return get_csr_bits(REG_INFO.monslcqbpwrdb());	//CSR49[0:0]
}

DS_rxRegs&
DS_rxRegs::setdfesumvrefsel(uint val){
	fill_csr_bits(val,REG_INFO.dfesumvrefsel());	//CSR50[15:15]
	return *this;
}
uint
DS_rxRegs::getdfesumvrefsel(){
	return get_csr_bits(REG_INFO.dfesumvrefsel());	//CSR50[15:15]
}

DS_rxRegs&
DS_rxRegs::setdfesumrtrimen(uint val){
	fill_csr_bits(val,REG_INFO.dfesumrtrimen());	//CSR50[14:14]
	return *this;
}
uint
DS_rxRegs::getdfesumrtrimen(){
	return get_csr_bits(REG_INFO.dfesumrtrimen());	//CSR50[14:14]
}

DS_rxRegs&
DS_rxRegs::setvregclkvrefrng(uint val){
	fill_csr_bits(val,REG_INFO.vregclkvrefrng());	//CSR50[13:12]
	return *this;
}
uint
DS_rxRegs::getvregclkvrefrng(){
	return get_csr_bits(REG_INFO.vregclkvrefrng());	//CSR50[13:12]
}

DS_rxRegs&
DS_rxRegs::setvregclkpreampsel(uint val){
	fill_csr_bits(val,REG_INFO.vregclkpreampsel());	//CSR50[11:10]
	return *this;
}
uint
DS_rxRegs::getvregclkpreampsel(){
	return get_csr_bits(REG_INFO.vregclkpreampsel());	//CSR50[11:10]
}

DS_rxRegs&
DS_rxRegs::setvregdatavrefrng(uint val){
	fill_csr_bits(val,REG_INFO.vregdatavrefrng());	//CSR50[9:8]
	return *this;
}
uint
DS_rxRegs::getvregdatavrefrng(){
	return get_csr_bits(REG_INFO.vregdatavrefrng());	//CSR50[9:8]
}

DS_rxRegs&
DS_rxRegs::setdfesumrestrim(uint val){
	fill_csr_bits(val,REG_INFO.dfesumrestrim());	//CSR50[7:4]
	return *this;
}
uint
DS_rxRegs::getdfesumrestrim(){
	return get_csr_bits(REG_INFO.dfesumrestrim());	//CSR50[7:4]
}

DS_rxRegs&
DS_rxRegs::setdfesumauxofsten(uint val){
	fill_csr_bits(val,REG_INFO.dfesumauxofsten());	//CSR50[3:3]
	return *this;
}
uint
DS_rxRegs::getdfesumauxofsten(){
	return get_csr_bits(REG_INFO.dfesumauxofsten());	//CSR50[3:3]
}

DS_rxRegs&
DS_rxRegs::setdfesumauxofstpol(uint val){
	fill_csr_bits(val,REG_INFO.dfesumauxofstpol());	//CSR50[2:2]
	return *this;
}
uint
DS_rxRegs::getdfesumauxofstpol(){
	return get_csr_bits(REG_INFO.dfesumauxofstpol());	//CSR50[2:2]
}

DS_rxRegs&
DS_rxRegs::setdfesumauxofstsel(uint val){
	fill_csr_bits(val,REG_INFO.dfesumauxofstsel());	//CSR50[1:0]
	return *this;
}
uint
DS_rxRegs::getdfesumauxofstsel(){
	return get_csr_bits(REG_INFO.dfesumauxofstsel());	//CSR50[1:0]
}

DS_rxRegs&
DS_rxRegs::setdfefxtap1cen(uint val){
	fill_csr_bits(val,REG_INFO.dfefxtap1cen());	//CSR51[15:8]
	return *this;
}
uint
DS_rxRegs::getdfefxtap1cen(){
	return get_csr_bits(REG_INFO.dfefxtap1cen());	//CSR51[15:8]
}

DS_rxRegs&
DS_rxRegs::setdfefxtap1edg(uint val){
	fill_csr_bits(val,REG_INFO.dfefxtap1edg());	//CSR51[7:0]
	return *this;
}
uint
DS_rxRegs::getdfefxtap1edg(){
	return get_csr_bits(REG_INFO.dfefxtap1edg());	//CSR51[7:0]
}

DS_rxRegs&
DS_rxRegs::setdfespare(uint val){
	fill_csr_bits(val,REG_INFO.dfespare());	//CSR52[15:15]
	return *this;
}
uint
DS_rxRegs::getdfespare(){
	return get_csr_bits(REG_INFO.dfespare());	//CSR52[15:15]
}

DS_rxRegs&
DS_rxRegs::setdfetapinjscale(uint val){
	fill_csr_bits(val,REG_INFO.dfetapinjscale());	//CSR52[14:13]
	return *this;
}
uint
DS_rxRegs::getdfetapinjscale(){
	return get_csr_bits(REG_INFO.dfetapinjscale());	//CSR52[14:13]
}

DS_rxRegs&
DS_rxRegs::setdfeslicerbwsel(uint val){
	fill_csr_bits(val,REG_INFO.dfeslicerbwsel());	//CSR52[12:11]
	return *this;
}
uint
DS_rxRegs::getdfeslicerbwsel(){
	return get_csr_bits(REG_INFO.dfeslicerbwsel());	//CSR52[12:11]
}

DS_rxRegs&
DS_rxRegs::setrxdfesumvreftrim(uint val){
	fill_csr_bits(val,REG_INFO.rxdfesumvreftrim());	//CSR52[10:9]
	return *this;
}
uint
DS_rxRegs::getrxdfesumvreftrim(){
	return get_csr_bits(REG_INFO.rxdfesumvreftrim());	//CSR52[10:9]
}

DS_rxRegs&
DS_rxRegs::setdfealphagenrtrim(uint val){
	fill_csr_bits(val,REG_INFO.dfealphagenrtrim());	//CSR52[8:6]
	return *this;
}
uint
DS_rxRegs::getdfealphagenrtrim(){
	return get_csr_bits(REG_INFO.dfealphagenrtrim());	//CSR52[8:6]
}

DS_rxRegs&
DS_rxRegs::setdfealphagenrefsel(uint val){
	fill_csr_bits(val,REG_INFO.dfealphagenrefsel());	//CSR52[5:3]
	return *this;
}
uint
DS_rxRegs::getdfealphagenrefsel(){
	return get_csr_bits(REG_INFO.dfealphagenrefsel());	//CSR52[5:3]
}

DS_rxRegs&
DS_rxRegs::setdfealphagenloadsel(uint val){
	fill_csr_bits(val,REG_INFO.dfealphagenloadsel());	//CSR52[2:0]
	return *this;
}
uint
DS_rxRegs::getdfealphagenloadsel(){
	return get_csr_bits(REG_INFO.dfealphagenloadsel());	//CSR52[2:0]
}

DS_rxRegs&
DS_rxRegs::setvregclkpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.vregclkpwrdb());	//CSR53[15:15]
	return *this;
}
uint
DS_rxRegs::getvregclkpwrdb(){
	return get_csr_bits(REG_INFO.vregclkpwrdb());	//CSR53[15:15]
}

DS_rxRegs&
DS_rxRegs::setvregclkdpmen(uint val){
	fill_csr_bits(val,REG_INFO.vregclkdpmen());	//CSR53[14:14]
	return *this;
}
uint
DS_rxRegs::getvregclkdpmen(){
	return get_csr_bits(REG_INFO.vregclkdpmen());	//CSR53[14:14]
}

DS_rxRegs&
DS_rxRegs::setvregclkbleedb(uint val){
	fill_csr_bits(val,REG_INFO.vregclkbleedb());	//CSR53[13:13]
	return *this;
}
uint
DS_rxRegs::getvregclkbleedb(){
	return get_csr_bits(REG_INFO.vregclkbleedb());	//CSR53[13:13]
}

DS_rxRegs&
DS_rxRegs::setvregclklvl(uint val){
	fill_csr_bits(val,REG_INFO.vregclklvl());	//CSR53[12:8]
	return *this;
}
uint
DS_rxRegs::getvregclklvl(){
	return get_csr_bits(REG_INFO.vregclklvl());	//CSR53[12:8]
}

DS_rxRegs&
DS_rxRegs::setvregdatapwrdb(uint val){
	fill_csr_bits(val,REG_INFO.vregdatapwrdb());	//CSR53[7:7]
	return *this;
}
uint
DS_rxRegs::getvregdatapwrdb(){
	return get_csr_bits(REG_INFO.vregdatapwrdb());	//CSR53[7:7]
}

DS_rxRegs&
DS_rxRegs::setvregdatadpmen(uint val){
	fill_csr_bits(val,REG_INFO.vregdatadpmen());	//CSR53[6:6]
	return *this;
}
uint
DS_rxRegs::getvregdatadpmen(){
	return get_csr_bits(REG_INFO.vregdatadpmen());	//CSR53[6:6]
}

DS_rxRegs&
DS_rxRegs::setvregdatableedb(uint val){
	fill_csr_bits(val,REG_INFO.vregdatableedb());	//CSR53[5:5]
	return *this;
}
uint
DS_rxRegs::getvregdatableedb(){
	return get_csr_bits(REG_INFO.vregdatableedb());	//CSR53[5:5]
}

DS_rxRegs&
DS_rxRegs::setvregdatalvl(uint val){
	fill_csr_bits(val,REG_INFO.vregdatalvl());	//CSR53[4:0]
	return *this;
}
uint
DS_rxRegs::getvregdatalvl(){
	return get_csr_bits(REG_INFO.vregdatalvl());	//CSR53[4:0]
}

DS_rxRegs&
DS_rxRegs::setvregclkinrushpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.vregclkinrushpwrdb());	//CSR54[15:15]
	return *this;
}
uint
DS_rxRegs::getvregclkinrushpwrdb(){
	return get_csr_bits(REG_INFO.vregclkinrushpwrdb());	//CSR54[15:15]
}

DS_rxRegs&
DS_rxRegs::setvregdatainrushpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.vregdatainrushpwrdb());	//CSR54[14:14]
	return *this;
}
uint
DS_rxRegs::getvregdatainrushpwrdb(){
	return get_csr_bits(REG_INFO.vregdatainrushpwrdb());	//CSR54[14:14]
}

DS_rxRegs&
DS_rxRegs::setvregclkrefsel(uint val){
	fill_csr_bits(val,REG_INFO.vregclkrefsel());	//CSR54[13:8]
	return *this;
}
uint
DS_rxRegs::getvregclkrefsel(){
	return get_csr_bits(REG_INFO.vregclkrefsel());	//CSR54[13:8]
}

DS_rxRegs&
DS_rxRegs::setvregdatarefsel(uint val){
	fill_csr_bits(val,REG_INFO.vregdatarefsel());	//CSR54[5:0]
	return *this;
}
uint
DS_rxRegs::getvregdatarefsel(){
	return get_csr_bits(REG_INFO.vregdatarefsel());	//CSR54[5:0]
}

DS_rxRegs&
DS_rxRegs::setrxatbmuxsel(uint val){
	fill_csr_bits(val,REG_INFO.rxatbmuxsel());	//CSR55[15:14]
	return *this;
}
uint
DS_rxRegs::getrxatbmuxsel(){
	return get_csr_bits(REG_INFO.rxatbmuxsel());	//CSR55[15:14]
}

DS_rxRegs&
DS_rxRegs::setdfealphagentopmatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.dfealphagentopmatbctrl());	//CSR55[13:11]
	return *this;
}
uint
DS_rxRegs::getdfealphagentopmatbctrl(){
	return get_csr_bits(REG_INFO.dfealphagentopmatbctrl());	//CSR55[13:11]
}

DS_rxRegs&
DS_rxRegs::setdfealphagentoppatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.dfealphagentoppatbctrl());	//CSR55[10:8]
	return *this;
}
uint
DS_rxRegs::getdfealphagentoppatbctrl(){
	return get_csr_bits(REG_INFO.dfealphagentoppatbctrl());	//CSR55[10:8]
}

DS_rxRegs&
DS_rxRegs::setdfealphagencenmute(uint val){
	fill_csr_bits(val,REG_INFO.dfealphagencenmute());	//CSR55[7:7]
	return *this;
}
uint
DS_rxRegs::getdfealphagencenmute(){
	return get_csr_bits(REG_INFO.dfealphagencenmute());	//CSR55[7:7]
}

DS_rxRegs&
DS_rxRegs::setdfealphagenedgmute(uint val){
	fill_csr_bits(val,REG_INFO.dfealphagenedgmute());	//CSR55[6:6]
	return *this;
}
uint
DS_rxRegs::getdfealphagenedgmute(){
	return get_csr_bits(REG_INFO.dfealphagenedgmute());	//CSR55[6:6]
}

DS_rxRegs&
DS_rxRegs::setdfealphagenmonmute(uint val){
	fill_csr_bits(val,REG_INFO.dfealphagenmonmute());	//CSR55[5:5]
	return *this;
}
uint
DS_rxRegs::getdfealphagenmonmute(){
	return get_csr_bits(REG_INFO.dfealphagenmonmute());	//CSR55[5:5]
}

DS_rxRegs&
DS_rxRegs::setdfealphagenstepsize(uint val){
	fill_csr_bits(val,REG_INFO.dfealphagenstepsize());	//CSR55[4:4]
	return *this;
}
uint
DS_rxRegs::getdfealphagenstepsize(){
	return get_csr_bits(REG_INFO.dfealphagenstepsize());	//CSR55[4:4]
}

DS_rxRegs&
DS_rxRegs::setdfesumbias(uint val){
	fill_csr_bits(val,REG_INFO.dfesumbias());	//CSR55[2:1]
	return *this;
}
uint
DS_rxRegs::getdfesumbias(){
	return get_csr_bits(REG_INFO.dfesumbias());	//CSR55[2:1]
}

DS_rxRegs&
DS_rxRegs::setrxdfesumbiasptaten(uint val){
	fill_csr_bits(val,REG_INFO.rxdfesumbiasptaten());	//CSR55[0:0]
	return *this;
}
uint
DS_rxRegs::getrxdfesumbiasptaten(){
	return get_csr_bits(REG_INFO.rxdfesumbiasptaten());	//CSR55[0:0]
}

DS_rxRegs&
DS_rxRegs::setvregclkatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.vregclkatbctrl());	//CSR56[15:13]
	return *this;
}
uint
DS_rxRegs::getvregclkatbctrl(){
	return get_csr_bits(REG_INFO.vregclkatbctrl());	//CSR56[15:13]
}

DS_rxRegs&
DS_rxRegs::setvregdataatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.vregdataatbctrl());	//CSR56[12:10]
	return *this;
}
uint
DS_rxRegs::getvregdataatbctrl(){
	return get_csr_bits(REG_INFO.vregdataatbctrl());	//CSR56[12:10]
}

DS_rxRegs&
DS_rxRegs::setsuptrimsummerrefsel(uint val){
	fill_csr_bits(val,REG_INFO.suptrimsummerrefsel());	//CSR56[5:0]
	return *this;
}
uint
DS_rxRegs::getsuptrimsummerrefsel(){
	return get_csr_bits(REG_INFO.suptrimsummerrefsel());	//CSR56[5:0]
}

DS_rxRegs&
DS_rxRegs::setjtagsel(uint val){
	fill_csr_bits(val,REG_INFO.jtagsel());	//CSR57[11:11]
	return *this;
}
uint
DS_rxRegs::getjtagsel(){
	return get_csr_bits(REG_INFO.jtagsel());	//CSR57[11:11]
}

uint
DS_rxRegs::getjtagoutp(){
	return get_csr_bits(REG_INFO.jtagoutp());	//CSR57[10:10]
}

uint
DS_rxRegs::getjtagoutm(){
	return get_csr_bits(REG_INFO.jtagoutm());	//CSR57[9:9]
}

DS_rxRegs&
DS_rxRegs::setjtagpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.jtagpwrdb());	//CSR57[8:8]
	return *this;
}
uint
DS_rxRegs::getjtagpwrdb(){
	return get_csr_bits(REG_INFO.jtagpwrdb());	//CSR57[8:8]
}

DS_rxRegs&
DS_rxRegs::setjtagacmodeen(uint val){
	fill_csr_bits(val,REG_INFO.jtagacmodeen());	//CSR57[7:7]
	return *this;
}
uint
DS_rxRegs::getjtagacmodeen(){
	return get_csr_bits(REG_INFO.jtagacmodeen());	//CSR57[7:7]
}

DS_rxRegs&
DS_rxRegs::setjtaginitclk(uint val){
	fill_csr_bits(val,REG_INFO.jtaginitclk());	//CSR57[6:6]
	return *this;
}
uint
DS_rxRegs::getjtaginitclk(){
	return get_csr_bits(REG_INFO.jtaginitclk());	//CSR57[6:6]
}

DS_rxRegs&
DS_rxRegs::setjtaginitp(uint val){
	fill_csr_bits(val,REG_INFO.jtaginitp());	//CSR57[5:5]
	return *this;
}
uint
DS_rxRegs::getjtaginitp(){
	return get_csr_bits(REG_INFO.jtaginitp());	//CSR57[5:5]
}

DS_rxRegs&
DS_rxRegs::setjtaginitm(uint val){
	fill_csr_bits(val,REG_INFO.jtaginitm());	//CSR57[4:4]
	return *this;
}
uint
DS_rxRegs::getjtaginitm(){
	return get_csr_bits(REG_INFO.jtaginitm());	//CSR57[4:4]
}

DS_rxRegs&
DS_rxRegs::setjtaghystadj(uint val){
	fill_csr_bits(val,REG_INFO.jtaghystadj());	//CSR57[3:2]
	return *this;
}
uint
DS_rxRegs::getjtaghystadj(){
	return get_csr_bits(REG_INFO.jtaghystadj());	//CSR57[3:2]
}

DS_rxRegs&
DS_rxRegs::setjtagthadj(uint val){
	fill_csr_bits(val,REG_INFO.jtagthadj());	//CSR57[1:0]
	return *this;
}
uint
DS_rxRegs::getjtagthadj(){
	return get_csr_bits(REG_INFO.jtagthadj());	//CSR57[1:0]
}

uint
DS_rxRegs::getceearly(){
	return get_csr_bits(REG_INFO.ceearly());	//CSR58[15:15]
}

uint
DS_rxRegs::getcelate(){
	return get_csr_bits(REG_INFO.celate());	//CSR58[14:14]
}

uint
DS_rxRegs::getcmearly(){
	return get_csr_bits(REG_INFO.cmearly());	//CSR58[13:13]
}

uint
DS_rxRegs::getcmlate(){
	return get_csr_bits(REG_INFO.cmlate());	//CSR58[12:12]
}

DS_rxRegs&
DS_rxRegs::setedgesleep(uint val){
	fill_csr_bits(val,REG_INFO.edgesleep());	//CSR58[8:8]
	return *this;
}
uint
DS_rxRegs::getedgesleep(){
	return get_csr_bits(REG_INFO.edgesleep());	//CSR58[8:8]
}

DS_rxRegs&
DS_rxRegs::setecoarsealignen(uint val){
	fill_csr_bits(val,REG_INFO.ecoarsealignen());	//CSR58[7:7]
	return *this;
}
uint
DS_rxRegs::getecoarsealignen(){
	return get_csr_bits(REG_INFO.ecoarsealignen());	//CSR58[7:7]
}

DS_rxRegs&
DS_rxRegs::setecoarsealignstep(uint val){
	fill_csr_bits(val,REG_INFO.ecoarsealignstep());	//CSR58[6:4]
	return *this;
}
uint
DS_rxRegs::getecoarsealignstep(){
	return get_csr_bits(REG_INFO.ecoarsealignstep());	//CSR58[6:4]
}

DS_rxRegs&
DS_rxRegs::setmcoarsealignen(uint val){
	fill_csr_bits(val,REG_INFO.mcoarsealignen());	//CSR58[3:3]
	return *this;
}
uint
DS_rxRegs::getmcoarsealignen(){
	return get_csr_bits(REG_INFO.mcoarsealignen());	//CSR58[3:3]
}

DS_rxRegs&
DS_rxRegs::setmcoarsealignstep(uint val){
	fill_csr_bits(val,REG_INFO.mcoarsealignstep());	//CSR58[2:0]
	return *this;
}
uint
DS_rxRegs::getmcoarsealignstep(){
	return get_csr_bits(REG_INFO.mcoarsealignstep());	//CSR58[2:0]
}

uint
DS_rxRegs::getmisierrdone(){
	return get_csr_bits(REG_INFO.misierrdone());	//CSR59[15:15]
}

uint
DS_rxRegs::getcphsval(){
	return get_csr_bits(REG_INFO.cphsval());	//CSR59[14:8]
}

uint
DS_rxRegs::getephsval(){
	return get_csr_bits(REG_INFO.ephsval());	//CSR59[6:0]
}

uint
DS_rxRegs::getmphsofstval(){
	return get_csr_bits(REG_INFO.mphsofstval());	//CSR60[15:9]
}

uint
DS_rxRegs::getmvolofstval(){
	return get_csr_bits(REG_INFO.mvolofstval());	//CSR60[8:0]
}

uint
DS_rxRegs::getmmcnt(){
	return get_csr_bits(REG_INFO.mmcnt());	//CSR61[15:0]
}

uint
DS_rxRegs::gettimerexp(){
	return get_csr_bits(REG_INFO.timerexp());	//CSR62[15:11]
}

uint
DS_rxRegs::gettimer(){
	return get_csr_bits(REG_INFO.timer());	//CSR62[10:0]
}

DS_rxRegs&
DS_rxRegs::setrxcal_timer_value(uint val){
	fill_csr_bits(val,REG_INFO.rxcal_timer_value());	//CSR63[14:5]
	return *this;
}
uint
DS_rxRegs::getrxcal_timer_value(){
	return get_csr_bits(REG_INFO.rxcal_timer_value());	//CSR63[14:5]
}

DS_rxRegs&
DS_rxRegs::setrxcal_timer_div_value(uint val){
	fill_csr_bits(val,REG_INFO.rxcal_timer_div_value());	//CSR63[4:2]
	return *this;
}
uint
DS_rxRegs::getrxcal_timer_div_value(){
	return get_csr_bits(REG_INFO.rxcal_timer_div_value());	//CSR63[4:2]
}

DS_rxRegs&
DS_rxRegs::setrxcal_timer_div_en(uint val){
	fill_csr_bits(val,REG_INFO.rxcal_timer_div_en());	//CSR63[1:1]
	return *this;
}
uint
DS_rxRegs::getrxcal_timer_div_en(){
	return get_csr_bits(REG_INFO.rxcal_timer_div_en());	//CSR63[1:1]
}

DS_rxRegs&
DS_rxRegs::setrxcal_timer_stop(uint val){
	fill_csr_bits(val,REG_INFO.rxcal_timer_stop());	//CSR63[0:0]
	return *this;
}
uint
DS_rxRegs::getrxcal_timer_stop(){
	return get_csr_bits(REG_INFO.rxcal_timer_stop());	//CSR63[0:0]
}
E_HILINK_REGISTER_TYPE DS_rxRegs::getType()
{
	return HILINK_PERLANE_REGISTER;
}
