#include <HILINK_DRIVE/HiLink_DS_rxRegs.h>
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
		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
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
	return HILINK_LANE_NUM;
}

uint
DS_rxRegs::getAddressMapToHiLink(int csrIndex){
	if(csrIndex>=DS_RX_CSR_NUM){
		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	return (uint)(0x4000 | (broadcast << 13) | (sliceID << 9) | ((uint)/*SUBBLOCKID.*/1 << 7) | csrIndex << 1);
	return 0;
}


uint&
DS_rxRegs::get_csr(uint csrIndex){
	if(csrIndex>=DS_RX_CSR_NUM){
		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	return csr[csrIndex];
}

void
DS_rxRegs::get_default_MacroLaneID(T_MacroLaneID& id){
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

E_HILINK_REGISTER_TYPE
DS_rxRegs::getType(){
	return HILINK_PERLANE_REGISTER;
}
///////////////////////////////////////////////////////////////////////////


	/// Receive path power down control. Active low.
	/// 0 = Power down all receiver circuitry
	/// 1 = Power up all receiver circuitry
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{0,"rxpwrdb",15,15}
	};
	return reg;
}

	/// Recovered clock power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::recclkpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{0,"recclkpwrdb",14,14}
	};
	return reg;
}

	/// Bypass  on-die RX capacitor.
	/// 0 = CAP is not bypassed
	/// 1 = Bypass CAP
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcapbypass(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{0,"rxcapbypass",13,13}
	};
	return reg;
}

	/// Mute control for the RX input stage.
	/// 0 = Normal operation.
	/// 1 = Mute input to first CTLE stage.
	/// The average (long term) voltage of the ��p��, and ��m�� inputs are equalized. Offset calibration requires  RXMUTE to be 1.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxmute(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{0,"rxmute",12,12}
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

	/// TX to RX serial loopback enable.
	/// 0 = Normal operation receiver in mission mode.
	/// 1 = High speed TX to RX loopback is enabled.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::txrxserlpbken(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{0,"txrxserlpbken",10,10}
	};
	return reg;
}

	/// Configure any rate divider from rx high speed reccovery clock.
	/// The output clock frequency can be caculated as : 
	/// Output clock freq= HSCLK freq /  Nrxwidth / Nrecc. 
	/// a) HSCLK freq is the frequency of spine clock, 
	/// b) Nrxwidth equal 8 when register RXDWIDTH is set to 000/010, 
	/// and equal 10 when  RXDWIDTH set to 001/011��
	/// c) Nrecc is the divN of this register; 
	/// 00 0000= div1
	/// 00 0001= div2
	/// ��������������..
	/// 11 1111=div64
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::recclkdiv(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{0,"recclkdiv",9,4}
	};
	return reg;
}

	/// cdr recovery clock divide 16 output power down.
	/// 0=power down
	/// 1=power up 
	/// notes: it power up only for 16Gbp
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::wordclkdiv_pwrdnb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{0,"wordclkdiv_pwrdnb",3,3}
	};
	return reg;
}

	/// Input passive attenuator control.
	/// 000 = -1 dB (minimum)
	/// 001 = -2 dB
	/// 010 = -3dB
	/// 011 = -4dB
	/// 100 = -5dB
	/// 101 = -6dB
	/// 110 = -6.5dB
	/// 111 = -7dB (maximum)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlepassgn(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{0,"ctlepassgn",2,0}
	};
	return reg;
}

	/// CTLE boost control (stage 1). 
	/// 0000= minimum
	/// 0001
	/// 0010
	/// 0011
	/// 0100
	/// 0101
	/// 0110
	/// 0111
	/// 1000
	/// 1001
	/// 1010
	/// 1011
	/// 1100
	/// 1101
	/// 1110
	/// 1111= maximum
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlebst1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{1,"ctlebst1",15,12}
	};
	return reg;
}

	/// CTLE mid-band capacitor control (stage 1).
	/// Use in tandem with RMBAND to boost mid-band frequencies (100MHz - 600MHz).
	/// 00 = highest zero frequency
	/// 01 
	/// 10
	/// 11 = lowest zero frequency
	/// 
	/// IF CTLERMBAND[1:0] FOR STAGE is set to '00'
	/// mid-band zero function is deactivated.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlecmband1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{1,"ctlecmband1",11,10}
	};
	return reg;
}

	/// CTLE mid-band resistor control (stage 1). Use in tandem with CMBAND to boost mid-band frequencies (100MHz - 600MHz).
	/// 00 = Mid-band zero deactivated.
	/// 01 = Low boost. (Low freq.  cancelling pole)
	/// 10 = Mid boost. 
	/// 11 = Highest boost. (1 to  1.5dB).
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlermband1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{1,"ctlermband1",9,8}
	};
	return reg;
}

	/// CTLE zero adjust control (stage 1).
	/// Extends frequency coverage of CTLE to lower frequencies.  Maintains boost magnitude down to 3-GHz. 
	/// 00 = primary zero is at highest frequency 
	/// 01 = intermediate frequency
	/// 10 = lowest frequency
	/// 11 = NA
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleza1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{1,"ctleza1",7,6}
	};
	return reg;
}

	/// CTLE squelch control (stage 1).  Attenuates high frequencies, and can be used to lower boost.
	/// 00=No squelch
	/// 01 and 10 = 50% squelch
	/// 11= Max squelch
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlesqh1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{1,"ctlesqh1",5,4}
	};
	return reg;
}

	/// CTLE active gain (stage 1).  Gain adjust control for stage 1 of  embedded VGA.
	/// 0000 = minimum gain.
	/// 0001, 0010, 0011, 0100, 0101, 0110 0111 1000 1001 1010 1011 1100 1101 1110 = intermediate settings.
	/// 1111 = maximum gain.
	/// 
	/// Total of 16 gain settings monotonically increasing from
	/// the minimum setting to maximum.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleactgn1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{1,"ctleactgn1",3,0}
	};
	return reg;
}

	/// CTLE boost control (stage 2). 
	/// 000 = minimum
	/// 0001
	/// 0010
	/// 0011
	/// 0100
	/// 0101
	/// 0110
	/// 0111
	/// 1000
	/// 1001
	/// 1010
	/// 1011
	/// 1100
	/// 1101
	/// 1110
	/// 1111= maximum
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlebst2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{2,"ctlebst2",15,12}
	};
	return reg;
}

	/// CTLE mid-band capacitor control (stage 2).
	/// Use in tandem with RMBAND to boost mid-band frequencies (100MHz - 600MHz).
	/// 00 = highest zero frequency
	/// 01 
	/// 10
	/// 11 = lowest zero frequency
	/// 
	/// IF CTLERMBAND[1:0] FOR STAGE is set to '00'
	/// mid-band zero function is deactivated.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlecmband2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{2,"ctlecmband2",11,10}
	};
	return reg;
}

	/// CTLE mid-band resistor control (stage 2). Use in tandem with CMBAND to boost mid-band frequencies (100MHz - 600MHz).
	/// 00 = Mid-band zero deactivated.
	/// 01 = Low boost. (Low freq.  cancelling pole)
	/// 10 = Mid boost. 
	/// 11 = Highest boost. (1 to  1.5dB).
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlermband2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{2,"ctlermband2",9,8}
	};
	return reg;
}

	/// CTLE zero adjust control (stage 2).
	/// Extends frequency coverage of CTLE to lower frequencies.  Maintains boost magnitude down to 3-GHz. 
	/// 00 = primary zero is at highest frequency 
	/// 01 = intermediate frequency
	/// 10 = lowest frequency
	/// 11 = NA
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleza2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{2,"ctleza2",7,6}
	};
	return reg;
}

	/// CTLE squelch control (stage 2).  Attenuates high frequencies, and can be used to lower boost.
	/// 00=No squelch
	/// 01 and 10 = 50% squelch
	/// 11= Max squelch
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlesqh2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{2,"ctlesqh2",5,4}
	};
	return reg;
}

	/// CTLE active gain (stage 2).  Gain adjust control for stage 2 of  embedded VGA.
	/// 0000= minimum gain.
	/// 0001, 0010, 0011, 0100, 0101, 0110 0111 1000 1001, 1010, 1011, 1100, 1101, 1110 = intermediate settings.
	/// 1111 = maximum gain.
	/// 
	/// Total of 16 gain settings monotonically increasing from
	/// the minimum setting to maximum.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleactgn2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{2,"ctleactgn2",3,0}
	};
	return reg;
}

	/// CTLE boost control (stage 3). 
	/// 000 = minimum
	/// 0001
	/// 0010
	/// 0011
	/// 0100
	/// 0101
	/// 0110
	/// 0111
	/// 1000
	/// 1001
	/// 1010
	/// 1011
	/// 1100
	/// 1101
	/// 1110
	/// 1111= maximum
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlebst3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{3,"ctlebst3",15,12}
	};
	return reg;
}

	/// CTLE mid-band capacitor control (stage 3).
	/// Use in tandem with RMBAND to boost mid-band frequencies (100MHz - 600MHz).
	/// 00 = highest zero frequency
	/// 01 
	/// 10
	/// 11 = lowest zero frequency
	/// 
	/// IF CTLERMBAND[1:0] FOR STAGE is set to '00'
	/// mid-band zero function is deactivated.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlecmband3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{3,"ctlecmband3",11,10}
	};
	return reg;
}

	/// CTLE mid-band resistor control (stage 3). Use in tandem with CMBAND to boost mid-band frequencies (100MHz - 600MHz).
	/// 00 = Mid-band zero deactivated.
	/// 01 = Low boost. (Low freq.  cancelling pole)
	/// 10 = Mid boost. 
	/// 11 = Highest boost. (1 to  1.5dB).
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlermband3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{3,"ctlermband3",9,8}
	};
	return reg;
}

	/// CTLE zero adjust control (stage 3).
	/// Extends frequency coverage of CTLE to lower frequencies.  Maintains boost magnitude down to 3-GHz. 
	/// 00 = primary zero is at highest frequency 
	/// 01 = intermediate frequency
	/// 10 = lowest frequency
	/// 11 = NA
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleza3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{3,"ctleza3",7,6}
	};
	return reg;
}

	/// CTLE squelch control (stage 3).  Attenuates high frequencies, and can be used to lower boost.
	/// 00=No squelch
	/// 01 and 10 = 50% squelch
	/// 11= Max squelch
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlesqh3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{3,"ctlesqh3",5,4}
	};
	return reg;
}

	/// CTLE active gain (stage 3).  Gain adjust control for stage 2 of  embedded VGA.
	/// 0000= minimum gain.
	/// 0001, 0010, 0011, 0100, 0101, 0110 0111 1000 1001, 1010, 1011, 1100, 1101, 1110 = intermediate settings.
	/// 1111 = maximum gain.
	/// 
	/// Total of 16 gain settings monotonically increasing from
	/// the minimum setting to maximum.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleactgn3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{3,"ctleactgn3",3,0}
	};
	return reg;
}

	/// DFE power down control. Active low.
	/// 0 = Power down DFE circuitry
	/// 1 = Power up DFE circuitry
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfepwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{4,"dfepwrdb",15,15}
	};
	return reg;
}

	/// Auxiliary DFE tap (tap beyond 29UI) power down control. Active low.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfeauxmvtappwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{4,"dfeauxmvtappwrdb",14,14}
	};
	return reg;
}

	/// DFE floating tap power down control. Active low.
	/// 0 = Power down all floating taps circuitry.
	/// 1 = Power up all floating taps circuitry
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfemvtappwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{4,"dfemvtappwrdb",13,13}
	};
	return reg;
}

	/// DFE fixed tap enables
	/// LSB = fixed tap1
	/// xxx1x = fixed tap2
	/// xx1xx = fixed tap3
	/// x1xxx = fixed tap4
	/// MSB = fixed tap5
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfefxtapen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{4,"dfefxtapen",12,8}
	};
	return reg;
}

	/// rx termination offset comperate when rx calibration done, the MSB is the sign-bit of offset, and the last three bit is offset value that the user want to compenrate, the range the user configured is from -7 to +7. when the MSB is 1, the offset descrease, otherwise, the offset increase.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxtermofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{4,"rxtermofst",7,4}
	};
	return reg;
}

	/// Gain control for DFE summer.  Affects only the main datapath (e.g. main cursor).
	/// 000 = minimum dc gain
	/// 001 = default
	/// 011
	/// 111 = maximum dc gain
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfegnsum(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{4,"dfegnsum",2,0}
	};
	return reg;
}

	/// DFE fixed tap1 amplitude setting, sign bit plus binary code amplitude for 0-63.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfefxtap1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{5,"dfefxtap1",15,9}
	};
	return reg;
}

	/// DFE fixed tap2 amplitude setting, sign bit plus binary code amplitude for 0-31.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfefxtap2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{5,"dfefxtap2",5,0}
	};
	return reg;
}

	/// RX AC couple burst mode enable
	/// 0 = AC couple burst mode enable
	/// 1 = AC couple normal mode enable
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ana_bmen_n(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{6,"ana_bmen_n",15,15}
	};
	return reg;
}

	/// DFE fixed tap3 amplitude setting, sign bit plus binary code amplitude for 0-15.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfefxtap3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{6,"dfefxtap3",14,10}
	};
	return reg;
}

	/// DFE fixed tap4 amplitude setting, sign bit plus binary code amplitude for 0-15.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfefxtap4(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{6,"dfefxtap4",9,5}
	};
	return reg;
}

	/// DFE fixed tap5 amplitude setting, sign bit plus binary code amplitude for 0-15.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfefxtap5(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{6,"dfefxtap5",4,0}
	};
	return reg;
}

	/// rx termination  power down.
	/// 0=power down
	/// 1=power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxterm_pwrdnb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{7,"rxterm_pwrdnb",15,15}
	};
	return reg;
}

	/// center edge phase offset signal. The default value is 0x20, the range is from 16~48.
	/// when PMA_MODE is PCIE or SATA mode, it is only  available in full-rate mode.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cephase_full(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{7,"cephase_full",14,9}
	};
	return reg;
}

	/// 10bit loopback pattern data transtion density threshold value
	/// 000 = 4
	/// 001 = 8
	/// 010 = 16
	/// 011 = 32
	/// 100 = 64
	/// 101 = 128
	/// 110 = 256
	/// 111 = 512
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::pat_des_lvl(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{7,"pat_des_lvl",8,6}
	};
	return reg;
}

	/// when cmphase and emphase async, the cmphase and emphase synchronize enable signal.
	/// 0 = disable 
	/// 1 = enbale
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::emphase_sync(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{7,"emphase_sync",5,5}
	};
	return reg;
}

	/// DFE floating taps select. Details TBD
	/// 00000 = fixed taps;                   01100 = floating taps 28 - 33
	/// ;00001 = floating taps 6 - 11;   01101 = floating taps 30 - 35
	/// ;00010 = floating taps 8 - 13;   01110 = floating taps 32 - 37
	/// ;00011 = floating taps 10 - 15; 01111 = floating taps 34 - 39
	/// ;00100 = floating taps 12 - 17; 10000 = floating taps 36 - 41
	/// ;00101 = floating taps 14 - 19; 10001 = floating taps 38 - 43
	/// ;00110 = floating taps 16 - 21; 10010 = floating taps 40 - 45
	/// ;00111 = floating taps 18 - 23; 10011 = floating taps 42 - 47
	/// ;01000 = floating taps 20 - 25; 10100 = floating taps 44 - 49
	/// ;01001 = floating taps 22 - 27; 10101 = floating taps 46 - 51
	/// ;01010 = floating taps 24 - 29; 10110 - 11111 = fixed taps.
	/// 01011 = floating taps 26 - 31
	/// 
	/// ;Note: when DFEMVTAPSEL[4:0] > '01010',  DFEAUXMVTAPPWRDB (DSRX.CSR[14]) must be set to 1.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfemvtapsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{7,"dfemvtapsel",4,0}
	};
	return reg;
}

	/// rxterm_floating controlled sel
	/// 0 = controlled by Asic Core pin rxterm_floating
	/// 1 = controlled by register CSR27_RXTERM_FLOATING_EN
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxterm_floating_sel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{8,"rxterm_floating_sel",15,15}
	};
	return reg;
}

	/// DFE floating tap1 amplitude setting, sign bit plus binary code amplitude for 0-15.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfemvtap1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{8,"dfemvtap1",14,10}
	};
	return reg;
}

	/// DFE floating tap2 amplitude setting, sign bit plus binary code amplitude for 0-15.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfemvtap2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{8,"dfemvtap2",9,5}
	};
	return reg;
}

	/// DFE floating tap3 amplitude setting, sign bit plus binary code amplitude for 0-15.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfemvtap3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{8,"dfemvtap3",4,0}
	};
	return reg;
}

	/// DFE floating tap4 amplitude setting, sign bit plus binary code amplitude for 0-15.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfemvtap4(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{9,"dfemvtap4",14,10}
	};
	return reg;
}

	/// DFE floating tap5 amplitude setting, sign bit plus binary code amplitude for 0-15.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfemvtap5(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{9,"dfemvtap5",9,5}
	};
	return reg;
}

	/// DFE floating tap6 amplitude setting, sign bit plus binary code amplitude for 0-15.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfemvtap6(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{9,"dfemvtap6",4,0}
	};
	return reg;
}

	/// Receiver digital circuitry reset. Active low.
	/// 0 = Reset RX logic
	/// 1 = RX out of reset
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxrstb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{10,"rxrstb",15,15}
	};
	return reg;
}

	/// RX data width select.
	/// 000 = 16 (8, 4, 2) bit parallel interface.
	/// 001 = 20 (10, 5, 2.5) bit parallel interface.
	/// 010 = 32 (16, 8, 4) bit interface.
	/// 011 = 40 (20, 10, 5) bit interface.
	/// 1xx  = Reserved
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxdwidth(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{10,"rxdwidth",14,12}
	};
	return reg;
}

	/// RX bit rate mode.
	/// 00 = full-rate
	/// 01 = 1/2-rate
	/// 10 = 1/4-rate
	/// 11 = 1/8-rate
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxratemode(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{10,"rxratemode",11,10}
	};
	return reg;
}

	/// Selects the mapping of the parallel RXD bus from the serial bit order:
	/// 0 = LSB is the first serial bit 
	/// 1 = MSB is the first bit input
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxbitorder(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{10,"rxbitorder",9,9}
	};
	return reg;
}

	/// RX data polarity control. When set, all received bits are inverted before being sent out to the core.
	/// 0 = Do not invert the RX data
	/// 1 = Invert RX the data
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxpolarity(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{10,"rxpolarity",8,8}
	};
	return reg;
}

	/// Select the parallel RX data to be sent to the core.
	/// 0 = Select the recovered data.
	/// 1 = Select the TX data coming from the core. This enables the TX-to-RX parallel loopback.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::txrxparlpbken(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{10,"txrxparlpbken",7,7}
	};
	return reg;
}

	/// CDR Work Mode
	/// 0: Non-SSC CDR Mode
	/// 1: SSC CDR Mode
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cdr_mode(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{10,"cdr_mode",6,6}
	};
	return reg;
}

	/// data-rate/width switch related signals(include rxdwidth, rxratemode and cphsofst) source select control
	/// 0: switch control 
	/// 1: register control
	/// Notes: it is only available for PCIE or SAS mode.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sw_para_source_sel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{10,"sw_para_source_sel",5,5}
	};
	return reg;
}

	/// Freeze CDR. When CDR is frozen, it doesn't track the jitter and PPM of incoming data.
	/// 0 = Normal operation
	/// 1 = CDR is frozen
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cdrfreeze(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{10,"cdrfreeze",3,3}
	};
	return reg;
}

	/// Bang-bang phase detect mode select.
	/// 0 = Normal
	/// 1 = Filter out bad transitions
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::bbpdmode(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{10,"bbpdmode",2,2}
	};
	return reg;
}

	/// Second loop enable. By enabling the second loop integrator CDR can track more PPM up to +/-XXXXppm, 
	/// 0 = Disable the CDR's second loop integrator.
	/// 1 = Enable the second loop integrator.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::secloopen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{10,"secloopen",1,1}
	};
	return reg;
}

	/// Each transition of this bit, from 0 to 1 or from 1 to 0, will cause the RX phase rotator to move 1UI (direction is TBD) to slip one serial bit. Multiple slips can be achieved by toggling this bit. Each transition has to wait for previous slip to complete (at least 64 word clock cycles).
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::bitslip(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{10,"bitslip",0,0}
	};
	return reg;
}

	/// CDR soft reset. Active low.
	/// 0 = Reset CDR
	/// 1 = Normal operation
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cdrrstb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{11,"cdrrstb",15,15}
	};
	return reg;
}

	/// CDR phase gain.
	/// 000 = 1;    001 = 2;    010 = 4;    011 = 8
	/// ;100 = 16;  101 = 32;  110 = 64;  111 = 128.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cdrphsgn(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{11,"cdrphsgn",13,11}
	};
	return reg;
}

	/// First integral loop gain.
	/// 000 = 0.25;   001 = 0.5;   010 = 1;     011 = 2
	/// ;100 = 4;        101 = 8;      110 = 16;   111 = 32.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cdrk1gn(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{11,"cdrk1gn",10,8}
	};
	return reg;
}

	/// CDR second integral loop gain.
	/// 000 = 1;    001 = 2;    010 = 4;    011 = 8
	/// ;100 = 16;  101 = 32;  110 = 64;  111 = 128.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cdrk2gn(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{11,"cdrk2gn",7,5}
	};
	return reg;
}

	/// Saturation value for truncated output of the first integral 
	/// 000 = 32
	/// 001 = 64
	/// 010 = 128
	/// 011 = 256
	/// 100 = 512
	/// 101 = 1024 (default)
	/// 110 = 2048
	/// 111 = 4096
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::freqintsat(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{11,"freqintsat",4,2}
	};
	return reg;
}

	/// Number of dither bits of the first integral
	/// 00 = 4 dither bit
	/// 01 = 5 dither bit
	/// 10 = 6 dither bit
	/// 11 = 7 dither bit
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::freqintatt(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{11,"freqintatt",1,0}
	};
	return reg;
}

	/// Phase offset between the center channel and the edge channel. A 2's complement value (-128 to 127) with each step of 1/64 full-rate UI. Nominal setting depends on the rate mode as follows,
	/// Rate Mode      Nominal setting
	/// full-rate           +32 (0010_0000)
	/// 1/2 rate                0
	/// 1/4 rate                0
	/// 1/8 rate                0
	/// when worked in SSC CDR mode, its value is +16.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cphsofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{12,"cphsofst",15,8}
	};
	return reg;
}

	/// Edge phase offset. A 2's complement value (-128 to 127) to adjust the edge phase when the CDR is frozen.  Can be used to slip one or multiple bits of RXD. To do bit slip, freeze the CDR first. Then write +/-64 (01000000/11000000) for +/-1UI move, or +127/-128 (01111111/10000000). For more than 2UI move, use multiple commands.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ephsofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{12,"ephsofst",7,0}
	};
	return reg;
}

	/// Transition density detection enable. When disabled, all transition density detection logic is reset.
	/// 0 = Disable transition density detector
	/// 1 = Enable transition density detector
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::tdden(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{13,"tdden",15,15}
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
		{13,"tddthr",14,12}
	};
	return reg;
}

	/// Eye scan based LOS detection enable.
	/// 0 = Disable eye scan based LOS detection
	/// 1 = Enable eye scan based LOS detection
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::loseyeen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{13,"loseyeen",11,11}
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
		{13,"loseyethr",10,9}
	};
	return reg;
}

	/// Enable analog LOS detection. (Not available yet)
	/// 0 = Disable
	/// 1 = Enable
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::losanaen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{13,"losanaen",8,8}
	};
	return reg;
}

	/// LOS configuration.
	/// LOSCFG[2]:
	/// 0 = LOS pin is a real time status of the transition density detector
	/// 1 = LOS pin is a latched status of the transition density detector (clear after read)
	/// LOSCFG[1:0]:
	/// 00 = Both LOS pin and LOS register bit (RX CSR13[4]) will be set to high when there are no enough transitions.
	/// 01 = Both LOS pin and LOS register bit (RX CSR13[4]) will be set to high when inner eye is not open enough vertically.
	/// 10 = Both LOS pin and LOS register bit (RX CSR13[4]) will be set to high when inner eye is not open enough horizontally.
	/// 11 = Both LOS pin and LOS register bit (RX CSR13[4]) will be set to high when there are no enough transitions, or inner eye is not open enough either vertically or horizontally.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::loscfg(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{13,"loscfg",7,5}
	};
	return reg;
}

	/// Loss of signal indication. This bit will be set to 1 when inadequate RX signal (the transition density falls below TDDTHR[2:0]) is detected or eye is not open enough vertically or horizontally after an eye scan, depending on the LOS configuration (RX CSR13[7:5]).
	/// 0 = Adequate RX signal (transitions) or eye opening.
	/// 1 = Inadequate RX signal (transitions) or eye openning.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::los(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{13,"los",4,4}
	};
	return reg;
}

	/// Transition density based Loss of signal indication (Clear on read).
	/// 0 = Transition density is above preset threshold.
	/// 1 = Transition density falls below preset threshold.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::lostran(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{13,"lostran",3,3}
	};
	return reg;
}

	/// Eye scan based (vertical) loss-of-signal indication.
	/// 0 = Vertical opening of last inner eye scan is bigger than the threshold.
	/// 1 = Vertical opening of last inner eye scan is less than the threshold.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::loseyever(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{13,"loseyever",2,2}
	};
	return reg;
}

	/// Eye scan based (horizontal) loss-of-signal indication.
	/// 0 = Horizontal opening of last inner eye scan is bigger than the threshold.
	/// 1 = Horizontal opening of last inner eye scan is less than the threshold.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::loseyehor(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{13,"loseyehor",1,1}
	};
	return reg;
}

	/// not used at this memont
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::losana(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{13,"losana",0,0}
	};
	return reg;
}

	/// Set 1 to start an internal 42-bit timer. Self cleared when the timer is full. The timer can be stopped at any time by writing 0 to this register.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::timecntstart(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{14,"timecntstart",15,15}
	};
	return reg;
}

	/// Select the divider 2 or 4 for PCIE signal and SAS squelch detection 
	/// 0 = select the divider 2
	/// 1 = select the divider 4
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdet_clkdiv(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{14,"sigdet_clkdiv",14,14}
	};
	return reg;
}

	/// sigdetclk divider(dsclk_digdet_clk_div) controlled by register configure or digial logic for debug
	/// 0 = control by register SIGDET_CLKDIV
	/// 1 = control by digital logic according data-rate switches
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdetclkdiv_pinsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{14,"sigdetclkdiv_pinsel",13,13}
	};
	return reg;
}

	/// rx_clk clock domain for eco use and these are floating signals
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dsrx_rxclk_res(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{14,"dsrx_rxclk_res",12,6}
	};
	return reg;
}

	/// PRBS checker enable.
	/// 0 = Disable (default)
	/// 1 = Enable
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::prbschken(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{14,"prbschken",5,5}
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
		{14,"prbschkmode",4,4}
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
	/// 1000 = custom pattern 0101 code
	/// 1001 = custom pattern 0011_0011 code
	/// 1010 = custom pattern 00001111_00001111 code
	/// other select will not do check
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::prbschkpatsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{14,"prbschkpatsel",3,0}
	};
	return reg;
}

	/// Eye monitor power down control. Active low.
	/// 0 = Eye monitor is powered down (analog)/disabled (digital)
	/// 1 = Eye monitor is powered up (analog)/enabled (digital)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyemonpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"eyemonpwrdb",15,15}
	};
	return reg;
}

	/// Voltage offset polarity control for ISI calculation.
	/// 0 = Normal
	/// 1 = Invert
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::volofstpol(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"volofstpol",14,14}
	};
	return reg;
}

	/// Monitor eye metric start / stop request for FOM
	/// 0: Stop eye metric for FOM
	/// 1:Enables eye metric measurement
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxeyediag_start(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"rxeyediag_start",13,13}
	};
	return reg;
}

	/// Monitor eye metric done for FOM 
	/// 0: eye metric doing 
	/// 1: eye metric done
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxeyediag_done(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"rxeyediag_done",12,12}
	};
	return reg;
}

	/// Eye monitor status
	/// 0 = not ready for scan
	/// 1 = ready for scan
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::emready(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"emready",11,11}
	};
	return reg;
}

	/// Eye scan START/STOP control
	/// 0 = Stop
	/// 1 = Start. Self clear after eye scan is done.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyescanstart(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"eyescanstart",10,10}
	};
	return reg;
}

	/// Eye scan mode.
	/// 000 = Automatic horizontal inner eye scan
	/// ;001 = Automatic vertical inner eye scan
	/// ;010 = Automatic horizontal outer eye scan
	/// ;011 = Automatic vertical outer eye scan
	/// ;10x = Manual inner eye scan
	/// ;11x = Manual outer eye scan.
	/// 
	/// For automatic horizontal eye scan, eye monitor sweeps horizontally at a certain voltage setting set by MVOLOFST[7:0] to find the inner most eye corners (left and right) at a given BER. The horizontal starting point is programmable through MPHSOFST[7:0].
	/// 
	/// For automatic vertical eye scan, eye monitor sweeps vertically at a certain phase setting set by MPHSOFST[7:0] to find the inner most eye corners (lower and upper) at a given BER. The vertical starting point is controlled by the eye monitor, i.e., not programmable.
	/// 
	/// For manual eye scan, the user has full control over how to measure the eye. Both phase and voltage settings are programmable through MPHSOFST[7:0] and MVOLOFST[7:0] respectively. They need to be set before the scan starts.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyescanmode(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"eyescanmode",9,7}
	};
	return reg;
}

	/// Eye scan window select.
	/// 0 = Choose normal eye scan window
	/// 1 = Choose extended eye scan window
	/// 
	/// Note: extended eye scan window is used to get more accurate and fine tuned results. It requires longer time to scan the eye. So it should be used wisely.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyescanwinsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"eyescanwinsel",6,6}
	};
	return reg;
}

	/// Eye scan window. EYESCANWIN[5:4] are reserved for future use.
	/// 
	/// For automatic inner eye scan (both horizontal and vertical), it sets the eye scan window, i.e., the number of words to be checked for a mismatch, which is calculated as  32*2^EYESCANWIN[3:0].
	/// 
	/// For automatic outer eye scan, it sets the allowed mismatches limit, which is calculated as 64*8*EYESCANWIN[3:0], within a fixed eye scan window (512 words).
	/// 
	/// For manual inner eye scan, eye monitor keeps comparing the monitor data with the recovered data at certain MPHSOFST[7:0] and MVOLOFST[7:0] settings until a mismatch is found or the scan is stopped by writing EYESCANSTART to '0'.
	/// 
	/// For manual outer eye scan, it sets the measurement window, i.e., the number of words counted for mismatch and ISI error accumulation, which is calculated as 32*8*EYESCANWIN[3:0]].
	/// 
	/// When the extended eye scan window mode is enabled, all above eye scan window and mismatch limit values are doubled.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyescanwin(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{15,"eyescanwin",5,0}
	};
	return reg;
}

	/// Eye monitor phase offset (2's complement value).
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mphsofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{16,"mphsofst",15,8}
	};
	return reg;
}

	/// Eye monitor voltage offset (2's complement value).
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mvolofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{16,"mvolofst",7,0}
	};
	return reg;
}

	/// Eyemetric for FOM access abormal indicater
	/// 0: eyemetric for FOM access successfully
	/// 1: eyemetric for FOM access abormal stop and rxeyediag_done is always 0
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyemetric_abormal(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{17,"eyemetric_abormal",14,14}
	};
	return reg;
}

	/// Mismatch accumulator threshold = 64*MMTHRESHOLD[5:0]
	/// 0x00 = inner eye.
	/// 
	/// Not used at the moment.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mmthr(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{17,"mmthr",13,10}
	};
	return reg;
}

	/// eye-metric for FOM with manual mode
	/// 0: eye-metric for FOM results generated by eyescan with eyemonitor 
	/// 1: eye-metric for FOM results configureg by register (EYEMETRIC_SUM[7:0])
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyemetric_manual(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{17,"eyemetric_manual",9,9}
	};
	return reg;
}

	/// eye metric for FOM start/stop request when pcie_stat_pin_en is low.
	/// 0:Stop eye metric measurement for FOM
	/// 1:Start eye metric measurement for FOM
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyemetric_start(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{17,"eyemetric_start",8,8}
	};
	return reg;
}

	/// eye-metric for FOM with manual mode  results and configured by register
	/// the results were configured by register through firmware launch eyescan and scan twice 
	/// Note: when eye-metric for FOM with manual mode, the EYEMETRIC_SUM must prior to or simultaneously EYEMETRIC_MANUAL and EYEMETRIC_START
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyemetric_sum(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{17,"eyemetric_sum",7,0}
	};
	return reg;
}

	/// PRBS checker error status. The bit is set to 1 when at least one error is detected. Status is latched until being read (clear on read).
	/// 0 = No errors detected.
	/// 1 = At least 1 error detected by the PRBS detector.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::prbserr(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{18,"prbserr",15,15}
	};
	return reg;
}

	/// PRBSCNTEXP[3:0] gives the exponent portion of the 26 bit error counter. (clear on read)
	/// 0 = most significant bit of PRBSCNT[10:0] is position 10 in the complete count
	/// ������������..
	/// 15 = most signficant bit of PRBSCNT[10:0] is position 25 in the complete count
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::prbscntexp(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{18,"prbscntexp",14,11}
	};
	return reg;
}

	/// PRBS error count
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::prbscnt(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{18,"prbscnt",10,0}
	};
	return reg;
}

	/// Left or lower corner of the most recent automatic horizontal/vertical eye scan.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyecor0(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{19,"eyecor0",15,8}
	};
	return reg;
}

	/// Right or upper corner of the most recent automatic horizontal/vertical eye scan.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyecor1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{19,"eyecor1",7,0}
	};
	return reg;
}

	/// ISI accumulator 0 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::isierr0(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{20,"isierr0",15,0}
	};
	return reg;
}

	/// ISI accumulator 1 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::isierr1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{21,"isierr1",15,0}
	};
	return reg;
}

	/// ISI accumulator 2 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::isierr2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{22,"isierr2",15,0}
	};
	return reg;
}

	/// ISI accumulator 3 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::isierr3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{23,"isierr3",15,0}
	};
	return reg;
}

	/// ISI accumulator 4 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::isierr4(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{24,"isierr4",15,0}
	};
	return reg;
}

	/// ISI accumulator 5 count, used for equalization adaptation
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::isierr5(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{25,"isierr5",15,0}
	};
	return reg;
}

	/// Activates reference circuit required for termination calibration.
	/// 0 = Deactivated
	/// 1 = Reference circuit is powered-up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxtermcalen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{26,"rxtermcalen",15,15}
	};
	return reg;
}

	/// Direction control for RX termination calibration.
	/// 0 = TBD
	/// 1 = TBD
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxtermcaldir(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{26,"rxtermcaldir",14,14}
	};
	return reg;
}

	/// 14-bit rx termination resistor trimming control.
	/// MSB = 1  (default). Activate termination.
	/// MSB = 0 For high impedance.  All other bits must be set to '0' for high impedance.  Invalid mission-mode setting.
	/// 10000000000000 = 60 Ohm
	/// 10000000000001 = 58.5 Ohm
	/// 10000000000011 = 55.7 Ohm
	/// 10000000000111 = 53.22 Ohm
	/// 10000000001111 = 50.9 Ohm
	/// 10000000011111 = 48.79 Ohm
	/// 10000000111111 = 46.84 Ohm
	/// 10000001111111 = 45 Ohm
	/// 10000011111111 = 43.37 Ohm
	/// 10000111111111 = 41.82 Ohm
	/// 10001111111111 = 40.37 Ohm
	/// 10011111111111 = 39 Ohm
	/// 10111111111111 = 37.7 Ohm
	/// 11111111111111 = 36.59 Ohm
	/// 
	/// Above values are guidance.  Not intended to define precise analog values across real samples.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxtermcal(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{26,"rxtermcal",13,0}
	};
	return reg;
}

	/// RX calibration mode. Switching from manual mode to automatic mode restarts the calibration process.
	/// 0 = Automatic calibration
	/// 1 = Manual calibration
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcalmode(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{27,"rxcalmode",15,15}
	};
	return reg;
}

	/// Data Slice calibration start control. Used only in automatic and semi-automatic modes.
	/// 0 = Do not start data slice calibrations
	/// 1 = Start all data slice calibrations (automatic way)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dscalstart(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{27,"dscalstart",14,14}
	};
	return reg;
}

	/// RX calibration start control. Used only in automatic and semi-automatic modes.
	/// 0 = Do not start RX calibrations
	/// 1 = Start RX calibrations self clean once rxcal_done is 1
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcalstart(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{27,"rxcalstart",13,13}
	};
	return reg;
}

	/// rx termination floating control.
	/// 0 = Termination floating disable--low impedance.
	/// 1 = Termination floating enable---high impedance.
	/// Notes��when Termination is in floating, the received data also transfered, not fixed 0 or 1,  the SOC need attention it.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxterm_floating_en(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{27,"rxterm_floating_en",12,12}
	};
	return reg;
}

	/// signal loss detected window setting and it is available in PCIE 2.5 or 5G
	/// the detected window is equal to 2^(SIGDET_WIN_PCIE+2)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdet_win_pcie(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{27,"sigdet_win_pcie",11,8}
	};
	return reg;
}

	/// Latch offset calibration enable
	/// 0 = Skip offset calibration for center, edge and monitor channels' latches during the automatic calibration process
	/// 1 = Do offset calibration for center, edge and monitor channels' latches during the automatic calibration process
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxdatalatchcalen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{27,"rxdatalatchcalen",7,7}
	};
	return reg;
}

	/// Direction control for RX offset calibration.
	/// 0 = TBD
	/// 1 = TBD
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxofstcaldir(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{27,"rxofstcaldir",6,6}
	};
	return reg;
}

	/// RX offset calibration select. It chooses analog circuit for offset calibration. Only applies to manual offset calibration mode.
	/// 000000 = No block is selected for offset calibration
	/// 000001 = Select CTLE stage 1 which is the CTLE boost stage 1
	/// 000010 = Select CTLE stage 2 which is the CTLE gain stage 1
	/// 000011 = Select CTLE stage 3 which is the CTLE boost stage 2
	/// 000100 = Select CTLE stage 4 which is the CTLE gain stage 2
	/// 000101 = Select CTLE stage 5 which is the CTLE boost stage 3
	/// 000110 = Select CTLE stage 6 which is the CTLE gain stage 3
	/// 000111 = Select DFE center channel even summer
	/// 001000 = Select DFE center channel odd summer
	/// 001001 = Select center channel even sense amplifier
	/// 001010 = Select center channel odd sense amplifier
	/// 001011 = Select edge channel even sense amplifier
	/// 001100 = Select edge channel odd sense amplifier
	/// 001101 = Select monitor even stage 1
	/// 001110 = Select monitor odd stage 1
	/// 001111 = Select monitor even stage 2
	/// 010000= Select monitor odd stage 2
	/// 010001 = Select monitor channel even sense amplifier
	/// 010010 = Select monitor channel odd sense amplifier
	/// 011111= Select rxctle replica
	/// 100000 = Select rxpa replica
	/// 100001 = Select sigdet calibration
	/// 100010 = Select rxterm calibration
	/// 100011 = Select comparator calibration
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxofstsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{27,"rxofstsel",5,0}
	};
	return reg;
}

	/// Offset control for the CTLE gain stage 1. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude. 
	/// 00000; 10000 = no offset.
	/// 01111; 11111 = full scale.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleofst1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{28,"ctleofst1",14,10}
	};
	return reg;
}

	/// Offset control for the CTLE boost stage 1. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleofst2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{28,"ctleofst2",9,5}
	};
	return reg;
}

	/// Offset control for the CTLE gain stage 2. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleofst3(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{28,"ctleofst3",4,0}
	};
	return reg;
}

	/// Offset control for the CTLR boost stage 2. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleofst4(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{29,"ctleofst4",14,10}
	};
	return reg;
}

	/// Offset control for the CTLE gain stage 3. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleofst5(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{29,"ctleofst5",9,5}
	};
	return reg;
}

	/// Offset control for the CTLE boost stage 3. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleofst6(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{29,"ctleofst6",4,0}
	};
	return reg;
}

	/// signal loss calibration enable signal
	/// 0 = signal loss calibration disable
	/// 1 = signal loss calibration enable
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdet_cal_en(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{30,"sigdet_cal_en",15,15}
	};
	return reg;
}

	/// Used to control  signal detection comparator offset calibration (Vppd):
	/// 000000 : 3mV
	/// 000001: 6mV
	/// ������.
	/// 100000:  81mV
	/// ������
	/// 111111:  162mV
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdet_offset(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{30,"sigdet_offset",14,10}
	};
	return reg;
}

	/// Offset control for the DFE center channel even summer. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfeevnsumofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{30,"dfeevnsumofst",9,5}
	};
	return reg;
}

	/// Offset control for the DFE center channel odd summer. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dfeoddsumofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{30,"dfeoddsumofst",4,0}
	};
	return reg;
}

	/// Monitor Offset control for the center channel even sense amplifier calibration feedback
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxctrensampofftrig(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{31,"rxctrensampofftrig",15,15}
	};
	return reg;
}

	/// Offset control for the center channel even sense amplifier. Used for manual offset calibration.
	/// MSB is signed bit, the other five bits are magnitude.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cevnsnsampofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{31,"cevnsnsampofst",14,9}
	};
	return reg;
}

	/// offset enable control for the center channel even sense amplifier. Used for manual offset calibration.
	/// 0= disable
	/// ;1= enable
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxctrensampencal(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{31,"rxctrensampencal",8,8}
	};
	return reg;
}

	/// rx center, edge and monitor sense amplifier calibration direction control
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxsnsampdir(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{31,"rxsnsampdir",7,7}
	};
	return reg;
}

	/// signal loss calibrtion direction control signal
	/// 0 = TBD
	/// 1 = TBD
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxsigdetdir(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{31,"rxsigdetdir",6,6}
	};
	return reg;
}

	/// rx termination calibration targe resist value choice.
	/// 00 = 50 Ohm
	/// 01 = 45 Ohm
	/// 10 = 42.5 Ohm
	/// 11 = NA
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxterm_ressel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{31,"rxterm_ressel",5,4}
	};
	return reg;
}

	/// recover clock divider choice for parallel banwidth; 
	/// 0 = divider 8 for ASIC 16bit
	/// 1 = divider 16 for ASIC 32bit
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::wordclk_divsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{31,"wordclk_divsel",3,3}
	};
	return reg;
}

	/// switch capacitor resistor enable control 
	/// 0 = disable switch capacitor resistor block and 
	/// 1 = enable switch capacitor resistor block
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxctle_scresen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{31,"rxctle_scresen",2,2}
	};
	return reg;
}

	/// attenuator block input low frequnecy clock divider coefficents
	/// 0 = divier 75
	/// 1 = divider 40
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxctle_scres_clk_div(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{31,"rxctle_scres_clk_div",1,1}
	};
	return reg;
}

	/// Select the clock1 and clock2 delay for sata/sas
	/// 0 = PCIE/common mode
	/// 1 = SAS mode
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rx_sigdet_bld_dly_sel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{31,"rx_sigdet_bld_dly_sel",0,0}
	};
	return reg;
}

	/// monitor Offset control for the center channel odd sense amplifier calibration feedback
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxctronsampofftrig(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{32,"rxctronsampofftrig",15,15}
	};
	return reg;
}

	/// Offset control for the center channel odd sense amplifier. Used for manual offset calibration.
	/// MSB is signed bit, the other five bits are magnitude.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::coddsnsampofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{32,"coddsnsampofst",14,9}
	};
	return reg;
}

	/// offset enable control for the center channel odd sense amplifier. Used for manual offset calibration.
	/// 0= disable
	/// ;1= enable
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxctronsampencal(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{32,"rxctronsampencal",8,8}
	};
	return reg;
}

	/// RX AC couple burst mode attenuation setting
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::bm_ac_r_sel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{32,"bm_ac_r_sel",7,6}
	};
	return reg;
}

	/// attenuator middle band equalization resistor select ;
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxctle_mbersel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{32,"rxctle_mbersel",5,3}
	};
	return reg;
}

	/// monitor  Offset control for edge channel even sense amplifier calibration feedback
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxedgensampofftrig(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{33,"rxedgensampofftrig",15,15}
	};
	return reg;
}

	/// Offset control for the edge channel even sense amplifier. Used for manual offset calibration.
	/// MSB is signed bit, the other five bits are magnitude.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eevnsnsampofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{33,"eevnsnsampofst",14,9}
	};
	return reg;
}

	/// offset enable control for the edge channel even sense amplifier. Used for manual offset calibration.
	/// 0= disable
	/// ;1= enable
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxedgensampencal(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{33,"rxedgensampencal",8,8}
	};
	return reg;
}

	/// analog spare signal to RO register for future use
	/// when DS puts CS slave south, the value of ds_spare_o[0] is zero, when DS puts CS slave north, the value of ds_spare_o[0] is high.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ds_spare_o(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{33,"ds_spare_o",7,0}
	};
	return reg;
}

	/// monitor Offset control for the edge channel odd sense amplifier calibration feedback
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxedgonsampofftrig(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{34,"rxedgonsampofftrig",15,15}
	};
	return reg;
}

	/// Offset control for the edge channel odd sense amplifier. Used for manual offset calibration.
	/// MSB is signed bit, the other five bits are magnitude.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eoddsnsampofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{34,"eoddsnsampofst",14,9}
	};
	return reg;
}

	/// offset enable control for the edge channel odd sense amplifier. Used for manual offset calibration.
	/// 0= disable
	/// ;1= enable
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxedgonsampencal(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{34,"rxedgonsampencal",8,8}
	};
	return reg;
}

	/// Monitor Offset control for the monitor channel even sense amplifier feedback
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxmonensampofftrig(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{35,"rxmonensampofftrig",15,15}
	};
	return reg;
}

	/// Offset control for the monitor channel even sense amplifier. Used for manual offset calibration.
	/// MSB is signed bit, the other five bits are magnitude.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mevnsnsampofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{35,"mevnsnsampofst",14,9}
	};
	return reg;
}

	/// offset enable control for the monitor channel even sense amplifier. Used for manual offset calibration.
	/// 0= disable
	/// ;1= enable
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxmonensampencal(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{35,"rxmonensampencal",8,8}
	};
	return reg;
}

	/// monitor Offset control for the monitor channel odd sense amplifier calibration feedback
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxmononsampofftrig(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{36,"rxmononsampofftrig",15,15}
	};
	return reg;
}

	/// Offset control for the monitor channel odd sense amplifier. Used for manual offset calibration.
	/// MSB is signed bit, the other five bits are magnitude.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::moddsnsampofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{36,"moddsnsampofst",14,9}
	};
	return reg;
}

	/// offset enable control for the monitor channel odd sense amplifier. Used for manual offset calibration.
	/// 0= disable
	/// ;1= enable
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxmononsampencal(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{36,"rxmononsampencal",8,8}
	};
	return reg;
}

	/// Offset control for the monitor channel even stage1. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyest1evnofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{36,"eyest1evnofst",7,3}
	};
	return reg;
}

	/// Offset control for the monitor channel even stage2. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyest2evnofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{37,"eyest2evnofst",15,11}
	};
	return reg;
}

	/// Squelch detection threshold setting when PMA_MODE is SAS mode.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::squelch_det_thr(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{37,"squelch_det_thr",10,0}
	};
	return reg;
}

	/// this register is floating for eco use
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dsrx_cor_res(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{38,"dsrx_cor_res",15,10}
	};
	return reg;
}

	/// Offset control for the monitor channel odd stage1. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyest1oddofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{38,"eyest1oddofst",9,5}
	};
	return reg;
}

	/// Offset control for the monitor channel odd stage2. Used for manual offset calibration.
	/// MSB is signed bit, the other four bits are magnitude.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyest2oddofst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{38,"eyest2oddofst",4,0}
	};
	return reg;
}

	/// monitor Offset calibration code for op-amp in load regulation loop feedback
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxctlerepofftrig(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{39,"rxctlerepofftrig",15,15}
	};
	return reg;
}

	/// Direction control for replica calibration.
	/// 0 = TBD
	/// 1 = TBD
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::replicacaldir(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{39,"replicacaldir",12,12}
	};
	return reg;
}

	/// Enable self-calibration of op-amp offset. Offset FSM monitors RXCTLEREPOFFTRIG.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxctlerepcalen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{39,"rxctlerepcalen",11,11}
	};
	return reg;
}

	/// Offset calibration code for op-amp in load regulation loop. Sign-magnitude code.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxctlerepcalcode(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{39,"rxctlerepcalcode",10,6}
	};
	return reg;
}

	/// Reference voltage selection for CTLE load resistor regulation loop.  Simultaneoulsy affects multiple performance parameters like gain, bandwidth, and slope.
	/// 
	/// 011 = higher BW, lower DC gain for CTLE.
	/// 100 = default.
	/// 101= highest dc gain. Recommended setting for limiting amplifier 
	/// configuration.
	/// 
	/// Settings 000/001/010, and 110/111 are used for debug.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxctlerefsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{39,"rxctlerefsel",5,3}
	};
	return reg;
}

	/// Control voltage selection for CTLE loads.                                                                000 = generated by regulator.
	/// All other settings are invalid. (test modes).
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxctleloadsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{39,"rxctleloadsel",2,0}
	};
	return reg;
}

	/// reserved between analog and digital interface
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxspare(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{40,"rxspare",15,8}
	};
	return reg;
}

	/// signal loss and squelch detection threshold select control signal
	/// 0 = controlled by digital logic whith datarate
	/// 1 = controlled by register(SIGDET_THR_SEL_MAN)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdet_manual(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{40,"sigdet_manual",7,7}
	};
	return reg;
}

	/// signal loss  threshold and detect window select signal with manul mode
	/// 0 =  PCIE 2.5 or 5G
	/// 1 = SAS/common/PCIE 8G mode
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdet_thr_sel_man(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{40,"sigdet_thr_sel_man",6,6}
	};
	return reg;
}

	/// monitor signal loss detection threshold and detect window select signal
	/// 1 =  PCIE 2.5 or 5G
	/// 1 = SAS/common/PCIE 8G mode
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdet_thr_sel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{40,"sigdet_thr_sel",5,5}
	};
	return reg;
}

	/// monitor the value of ctlepreset that from PCS
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlepreset(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{40,"ctlepreset",2,0}
	};
	return reg;
}

	/// 
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxparepofftrig(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{41,"rxparepofftrig",15,15}
	};
	return reg;
}

	/// Enable self-calibration of opamp in PA replica load regulation.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxpacalen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{41,"rxpacalen",11,11}
	};
	return reg;
}

	/// Offset calibration code for op-amp in load regulation loop. Sign-magnitude code.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxpacalcode(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{41,"rxpacalcode",10,6}
	};
	return reg;
}

	/// Reference voltage selection for pre-amplifier load resistor regulation loop.  Simultaneoulsy affects multiple performance parameters.
	/// 
	/// 011 = default gain.
	/// 
	/// Other settings are for test purposes only.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxparefsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{41,"rxparefsel",5,3}
	};
	return reg;
}

	/// Control voltage selection for latch load.                                                                0 = generated by regulator.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxpaloadsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{41,"rxpaloadsel",2,0}
	};
	return reg;
}

	/// RX calibration comparator power down control
	/// 0 = power down
	/// 1 = power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dsrxlowoffpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{42,"dsrxlowoffpwrdb",15,15}
	};
	return reg;
}

	/// RX calibration comparator enable signal
	/// 0 = disable
	/// 1 = enable
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dsrxlowoffcal(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{42,"dsrxlowoffcal",14,14}
	};
	return reg;
}

	/// RX calibration code for comparator
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dsrxlowoffctrl(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{42,"dsrxlowoffctrl",13,8}
	};
	return reg;
}

	/// Direction control for RX lowoff comparator calibration.
	/// 0 = TBD
	/// 1 = TBD
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxlowoffcaldir(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{42,"rxlowoffcaldir",7,7}
	};
	return reg;
}

	/// monitor RX calibration comparator feedback
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::dsrxlowoffout(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{42,"dsrxlowoffout",6,6}
	};
	return reg;
}

	/// monitor RX calibration control code value
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcalread(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{42,"rxcalread",5,0}
	};
	return reg;
}

	/// This bit allows the user to change the polarity of the Eye Monitor offset voltage direction.
	/// 0: Default, A positive increase in MVOLOFST[7:0] will result in positive voltage offset
	/// 1:Inverted,A positive increase in MVOLOFST[7:0] will result in negative voltage offset (V101)
	/// not used
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxeye_polarityswitch(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{43,"rxeye_polarityswitch",15,15}
	};
	return reg;
}

	/// ctle preset decoder from PCS  reponse enable signal for ctle_est1~3_boost and ctle_gst1~3_gain value
	/// 0: disable reponse and the value are configured by register csr_ctlebst1~3 and csr_ctleactgn1~3
	/// 1: enable reponse and the values are decoder of ctlepreset
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctlepreset_en(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{43,"ctlepreset_en",14,14}
	};
	return reg;
}

	/// TX to TX serial loopback atb control signals
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::txrxserlpbkatbctrl(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{43,"txrxserlpbkatbctrl",13,12}
	};
	return reg;
}

	/// 
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxlowoffatbctrl(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{43,"rxlowoffatbctrl",11,10}
	};
	return reg;
}

	/// RX mux selection for access to low-offset comparator, and second level atb bus mux.
	/// 00 = no select.
	/// 01 = selects RX otbp bus
	/// 10 = selects RX otbm bus
	/// 11 = selects 'vss' reference.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxatbmuxsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{43,"rxatbmuxsel",9,8}
	};
	return reg;
}

	/// un-used.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxatbsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{43,"rxatbsel",7,0}
	};
	return reg;
}

	/// squelch detection window. It can be programmed to 2^2 , 2^3,2^4,2^5,2^6,2^7 ,2^8 ,2^9  and 2^10 
	/// 0X0: 4 
	/// 0X1: 8 
	/// 0X2:  16 
	/// 0X3: 32
	/// 0X4: 64 
	/// 0X5: 128
	/// 0X6: 256 
	/// 0X7: 512 
	/// 0X8: 1024 
	/// Notes: it is only available in SAS mode.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::squelch_detwin(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{44,"squelch_detwin",15,12}
	};
	return reg;
}

	/// 0 = AC-JTAG receiver is controlled by pins
	/// ;1 = AC-JTAG receiver is controlled by register.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtagsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{44,"jtagsel",11,11}
	};
	return reg;
}

	/// 
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtagoutp(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{44,"jtagoutp",10,10}
	};
	return reg;
}

	/// 
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtagoutm(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{44,"jtagoutm",9,9}
	};
	return reg;
}

	/// JTAG power down control. Active low.
	/// TBD
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtagpwrdb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{44,"jtagpwrdb",8,8}
	};
	return reg;
}

	/// JTAG AC mode enable
	/// TBD
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtagacmodeen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{44,"jtagacmodeen",7,7}
	};
	return reg;
}

	/// 
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtaginitclk(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{44,"jtaginitclk",6,6}
	};
	return reg;
}

	/// 
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtaginitp(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{44,"jtaginitp",5,5}
	};
	return reg;
}

	/// 
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtaginitm(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{44,"jtaginitm",4,4}
	};
	return reg;
}

	/// JTAG hysteresis thrshold control
	/// TBD
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtaghystadj(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{44,"jtaghystadj",3,2}
	};
	return reg;
}

	/// JTAG threshold control
	/// 00: 100mv
	/// ;01:110mc
	/// ;10:120mv
	/// ;11:130mv
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::jtagthadj(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{44,"jtagthadj",1,0}
	};
	return reg;
}

	/// Monitor center and edge early signal
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ceearly(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{45,"ceearly",15,15}
	};
	return reg;
}

	/// Monitor center and edge late signal
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::celate(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{45,"celate",14,14}
	};
	return reg;
}

	/// Monitor center and monitor early signal
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cmearly(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{45,"cmearly",13,13}
	};
	return reg;
}

	/// Monitor center and monitor late signal
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cmlate(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{45,"cmlate",12,12}
	};
	return reg;
}

	/// monitor cdr coarsealigndone status
	/// 0=coarsealign doing
	/// 1= coarsealign done
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cdr_coarsealigndone(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{45,"cdr_coarsealigndone",11,11}
	};
	return reg;
}

	/// monitor sscdr coarsealigndone status
	/// 0=coarsealign doing
	/// 1= coarsealign done
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sscdr_coarsealigndone(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{45,"sscdr_coarsealigndone",10,10}
	};
	return reg;
}

	/// Edge channel sleep control.
	/// 0 = Mission mode
	/// 1 = Sleep mode
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::edgesleep(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{45,"edgesleep",8,8}
	};
	return reg;
}

	/// Center-Edge coarse align enable.
	/// 0 = Disable
	/// 1 = Enable
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ecoarsealignen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{45,"ecoarsealignen",7,7}
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
		{45,"ecoarsealignstep",6,4}
	};
	return reg;
}

	/// Monitor-Center coarse align enable. Only applicable when eye monitor is enabled.
	/// 0 = Disable
	/// 1 = Enable
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mcoarsealignen(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{45,"mcoarsealignen",3,3}
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
		{45,"mcoarsealignstep",2,0}
	};
	return reg;
}

	/// This register contains the present binary phase setting of the center channel phase interpolator.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cphsval(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{46,"cphsval",14,8}
	};
	return reg;
}

	/// 10bit period pattern data density detect results
	/// 0 = pattern is not 10bit period data pattern
	/// 1 = pattern is the 10bit perido data pattern
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::pat_per_los(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{46,"pat_per_los",7,7}
	};
	return reg;
}

	/// This register contains the present binary phase setting of the edge channel phase interpolator.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ephsval(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{46,"ephsval",6,0}
	};
	return reg;
}

	/// Not used.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::misierrdone(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{47,"misierrdone",15,15}
	};
	return reg;
}

	/// This register contains the present binary phase setting of the monitor channel phase interpolator.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mphsofstval(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{47,"mphsofstval",14,8}
	};
	return reg;
}

	/// Eye monitor voltage offset.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mvolofstval(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{47,"mvolofstval",7,0}
	};
	return reg;
}

	/// Mismatch count which is calculated as,  when MMCNT[13:11] is equal to zero, MMCNT[10:0]x2^MMCNT[13:11]. Otherwise, MMCNT=2^(MMCNT[13:11]) * (1024+MMCNT[10:0]/2)
	/// Note: MMCNT[15:14] are not used.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mmcnt(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{48,"mmcnt",15,0}
	};
	return reg;
}

	/// TIMEREXP[4:0] gives the exponent portion of the internal 42-bit timer.
	/// 0 = MSB of the timer is at position 10 in the complete count
	/// 1 = MSB of the timer is at position 11 in the complete count
	/// 2 = MSB of the timer is at position 12 in the complete count
	/// ������������..
	/// 31 = MSB of the timer is at position 41 in the complete count
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::timerexp(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{49,"timerexp",15,11}
	};
	return reg;
}

	/// TIMER[10:0], together with the exponent portion (TIMEREXP[4:0]), gives the cycle count of the counting clock. TIMER[10:0] is only the lower 11-bit portion of the internal 42-bit timer.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::timer(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{49,"timer",10,0}
	};
	return reg;
}

	/// squelch detection enable signal
	/// 0 = squelch detection is disable
	/// 1 = squelch detection is enable
	/// the user enable this function until ds calibration done
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::squelch_det_en(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{50,"squelch_det_en",15,15}
	};
	return reg;
}

	/// Configuration of timer for waiting, which is the cycles of reference clock.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcal_timer_value(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{50,"rxcal_timer_value",14,5}
	};
	return reg;
}

	/// Configuration of divider in timer, for debugging.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcal_timer_div_value(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{50,"rxcal_timer_div_value",4,2}
	};
	return reg;
}

	/// Enable the divider in timer, for debugging.
	/// 0 = disable
	/// 1 = enable
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcal_timer_div_en(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{50,"rxcal_timer_div_en",1,1}
	};
	return reg;
}

	/// Stop timer, for debugging.
	/// 0 = normal
	/// 1 = stop the timer
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxcal_timer_stop(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{50,"rxcal_timer_stop",0,0}
	};
	return reg;
}

	/// This register contains the present binary phase setting of the center channel phase  interpolator of SSC CDR
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::cphase_ssc(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{51,"cphase_ssc",15,10}
	};
	return reg;
}

	/// eyescan ready indicator signal and when read it is high, it indicates eyescan can be started.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyescan_rdy(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{51,"eyescan_rdy",9,9}
	};
	return reg;
}

	/// when data-rate swithed in PCIE/SATA mode, the SSCDR soft reset reset through data-rate swithed, and release through alos in PCIE mode, or squelch los in SATA mode
	/// 0 = SSCDR soft reset release through data-rate swithed finished
	/// 1 = SSCDR soft reset release through alos or squelch los is low.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sscdr_sftrst_ctrl(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{51,"sscdr_sftrst_ctrl",8,8}
	};
	return reg;
}

	/// Fast-PI-Based SSC CDR demux Mode
	/// 0: demux=4, Max freq offset 6000ppm, Max data rate 8.0Gbps
	/// 1: demux=8, only SAS 12Gbps needed, Max freq offset 3000ppm, Max data rate 12.0Gbps
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sscdr_demux_mode(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{51,"sscdr_demux_mode",7,7}
	};
	return reg;
}

	/// SSC CDR internal signal probe request
	/// 0: keep unchanged
	/// ;1: read sscdr signal request.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sscdr_atb_req(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{51,"sscdr_atb_req",6,6}
	};
	return reg;
}

	/// This register contains the present binary phase setting of the edge channel phase interpolator of SSC CDR
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ephase_ssc(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{51,"ephase_ssc",5,0}
	};
	return reg;
}

	/// This register contains the present binary phase setting of the monitor channel phase interpolator of SSC CDR
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mphase_ssc(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{52,"mphase_ssc",15,10}
	};
	return reg;
}

	/// select CDR internal bus to probe at csr_sscdr_atb_out[6:0]
	/// 3��b000: loop2_value[6:0]
	/// 3��b001: c_eoffset[5:0]
	/// 3��b010: m_eoffset[5:0]
	/// 3��b011: bitslip/ephase_adj/ /coarsealign
	/// 3��b1xx: for future use
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sscdr_atb_sel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{52,"sscdr_atb_sel",9,7}
	};
	return reg;
}

	/// Monitor SSC CDR internal test bus
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sscdr_atb_out(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{52,"sscdr_atb_out",6,0}
	};
	return reg;
}

	/// Fast-PI-Based SSC CDR integral gain
	/// note: the mininal value is must equal to 4
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sscdr_intg_gain(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{53,"sscdr_intg_gain",15,11}
	};
	return reg;
}

	/// Fast-PI-Based SSC CDR proportional gain
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sscdr_prop_gain(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{53,"sscdr_prop_gain",10,6}
	};
	return reg;
}

	/// Fast-PI-Based SSC CDR 2nd loop saturate value
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sscdr_loop2_sat(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{53,"sscdr_loop2_sat",5,0}
	};
	return reg;
}

	/// eye metric scan mode for FOM 
	/// 000=automatic horizontal inner eye scan
	/// ;001=automatic vertical inner eye scan
	/// ;others: reversed
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyemetric_scanmode(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{54,"eyemetric_scanmode",15,13}
	};
	return reg;
}

	/// eyemetric scan window select for FOM
	/// 0=choose normal eye scan window
	/// ;1=choose extended eye scan window.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyemetric_scanwinsel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{54,"eyemetric_scanwinsel",12,12}
	};
	return reg;
}

	/// eyemetric scan window for FOM
	/// For auto inner eye scan(both horizontal and vertical), it sets the eye scan window, the number of words to be checked for a mismatch, which is calculated as 32*2^EYEMETRIC_SCANWIN.
	/// For auto outer eye scan, it sets the allowed mismatches limit, which is calculated as 64*8*EYEMETRIC_SCANWIN,within a fixed eye scan window (512 words)
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyemetric_scanwin(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{54,"eyemetric_scanwin",11,8}
	};
	return reg;
}

	/// Monitor eye-mertric results for FOM  
	/// provide the PHY link equalization evaluation Fugure of Merit value. The value is encoded as an integer from 0 to 255.
	/// note:
	///  RXEYEDIAG_STAT=(EYECOR1_FST-EYECORNER0_FST) +(EYECOR1_SEC-EYECOR0_SEC) when eyemetric_manual is 0
	/// when eye-metric with manual mode, it value is configured by register EYEMETRIC_SUM
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxeyediag_stat(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{54,"rxeyediag_stat",7,0}
	};
	return reg;
}

	/// Eye monitor phase offset (2's complement value).
	/// Only used eyemetric start  for FOM valid and the first eyescan.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mphsofst_fst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{55,"mphsofst_fst",15,8}
	};
	return reg;
}

	/// Eye monitor voltage offset (2's complement value).
	/// Only used eyemetric start valid for FOM and the first eyescan.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mvolofst_fst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{55,"mvolofst_fst",7,0}
	};
	return reg;
}

	/// Eye monitor phase offset (2's complement value).
	/// Only used eyemetric start for FOM valid and the second eyescan.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mphsofst_sec(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{56,"mphsofst_sec",15,8}
	};
	return reg;
}

	/// Eye monitor voltage offset (2's complement value).
	/// Only used eyemetric start for FOM  valid and the second eyescan.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::mvolofst_sec(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{56,"mvolofst_sec",7,0}
	};
	return reg;
}

	/// Left or lower corner of the most recent automatic horizontal/vertical eye scan.
	/// Only used eyemetric start valid for FOM and the first eyescan.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyecor0_fst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{57,"eyecor0_fst",15,8}
	};
	return reg;
}

	/// Right or upper corner of the most recent automatic 
	/// horizontal/vertical eye scan.
	/// Only used eyemetric start valid for FOM and the first eyescan.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyecor1_fst(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{57,"eyecor1_fst",7,0}
	};
	return reg;
}

	/// Left or lower corner of the most recent automatic horizontal/vertical eye scan.
	/// Only used eyemetric start valid for FOM  and the second eyescan.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyecor0_sec(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{58,"eyecor0_sec",15,8}
	};
	return reg;
}

	/// Right or upper corner of the most recent automatic 
	/// horizontal/vertical eye scan.
	/// Only used eyemetric start valid for FOM  and the second eyescan.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::eyecor1_sec(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{58,"eyecor1_sec",7,0}
	};
	return reg;
}

	/// Adjust the signal detection level (vlv  Vppd):
	/// 000000 : 20mV
	/// 000001: 26mV
	/// ������.
	/// 100000:  192mV
	/// ������
	/// 111111:  384mV
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdet_vlv(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{59,"sigdet_vlv",15,9}
	};
	return reg;
}

	/// rx signal detect power down.
	/// 0=power down
	/// 1=power up
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxsigdet_pwrdnb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{59,"rxsigdet_pwrdnb",8,8}
	};
	return reg;
}

	/// configure the clock divider rate from  high speed recovery clock, which frequency is the same as spine clock. 
	/// divide reference clock for  different XPON mode
	/// 000=divide  66;   (for 10GXEPON/10G EPON) 
	/// 001=divide 32;   (for XGPON)
	/// 01x=divide 16;   (for GPON/EPON/2.5GPON)
	/// 1xx=adjustable  divide rate configure, the rate is setting through the register RECCLKDIV[5:0]
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::rxrecclk_sel(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{59,"rxrecclk_sel",7,5}
	};
	return reg;
}

	/// BCDR controll signal source select 
	/// 0 =  BCDR controll signal comes from ASIC pin ana_bmen_n/ bm_ac_r_sel,
	/// 1 = BCDR controll signal comes from register csr6_ana_bmen_en/ csr32_bm_ac_r_sel
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::bcdr_pin_en(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{59,"bcdr_pin_en",4,4}
	};
	return reg;
}

	/// decoder the  receiver ctle boost_st1~3 and gain_st1~3 parameter value when pcie_stat_pin_en is low.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::ctleparset(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{59,"ctleparset",2,0}
	};
	return reg;
}

	/// signal loss detection enable
	/// 0: disable squelch or signal loss detection,
	/// 1: enable squelch or signal loss detection.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdet_enable(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{60,"sigdet_enable",15,15}
	};
	return reg;
}

	/// signal loss(alos) detection window in PCIE 8G/Common/SAS mode. It can be programmed to 2^2 , 2^3,2^4,2^5,2^6,2^7 ,2^8 ,2^9  and 2^10 
	/// 0X0: 4 
	/// 0X1: 8 
	/// 0X2:  16 
	/// 0X3: 32
	/// 0X4: 64 
	/// 0X5: 128
	/// 0X6: 256 
	/// 0X7: 512 
	/// 0X8: 1024
	/// Notes��when worked in common mode, the default value is  0x6, the pcie 8G mode, the default value is 0x4, the sas mode, the default value is 0x0.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdet_win(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{60,"sigdet_win",14,11}
	};
	return reg;
}

	/// signal loss detection threshold only used in pice 2.5G/5G working mode
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdet_thr_s1(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{60,"sigdet_thr_s1",10,0}
	};
	return reg;
}

	/// PCIE signal loss detection output
	/// 0-indicate signal level is above preset threshold for PCIE
	/// 1- indicate signal level falls below preset threshold for PCIE
	/// note:  it is only available for PCIE or common mode.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdet_los(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{61,"sigdet_los",15,15}
	};
	return reg;
}

	/// Fast-PI-Based SSC CDR reset control
	/// 1=At loss of signal, reset the CDR
	/// 0=Disregard LOS
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sscdr_rst_by_sigdet(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{61,"sscdr_rst_by_sigdet",14,14}
	};
	return reg;
}

	/// eye-metric for FOM generation reponse control signals
	/// 0: eye-metric for FOM generation is not response and the signals eyescanstart, eyescanmode, eyescanwinsel and eyescanwin is available.
	/// 1: eye-metric for FOM generation is response and eyemetric_start, eyemetric_scanwin, eyemeric_scanmode and eyemetric_scanwinsel is available
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::remotetx(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{61,"remotetx",13,13}
	};
	return reg;
}

	/// SAS/SATA squelch detection output
	/// 0-indicate 1.5Gbps OOB-signal for SAS on receive pins
	/// 1- indicate electrical idle for SAS on receive pins
	/// note: it is only available for SAS  mode.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::squelch_det(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{61,"squelch_det",12,12}
	};
	return reg;
}

	/// signal and squelch detection soft reset 
	/// 0: reset 
	/// 1: release
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdet_rstb(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{61,"sigdet_rstb",11,11}
	};
	return reg;
}

	/// signal loss threshold used in  SAS mode, Common mode or PCIE 8G mode
	/// Note: when worked in SAS mode, the default value is 0x2, when worked in Common mode, the default value is 0x40, when worked in PCIE 8G mode, the defaule value is 0x14
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sigdet_thr_s2(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{61,"sigdet_thr_s2",10,0}
	};
	return reg;
}

	/// 10bit period pattern data density detect window setting
	/// 00 = 2^4
	/// 01 = 2^5
	/// 10 = 2^6
	/// 11 = 2^7
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::pat_det_win(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{62,"pat_det_win",15,14}
	};
	return reg;
}

	/// monitor sscdr_cmphase in  sscdr cmphase generate when eyescan doing in digital part
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::sscdr_cmphase(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{62,"sscdr_cmphase",13,8}
	};
	return reg;
}

	/// emphase configuration when cmphase and emphase async.
const T_REG_INFO_EX&
DS_rxRegs::_REG_INFO::emphase_delta(){
	const static T_REG_INFO_EX reg={DS_rxRegs::getInstance(),
		{62,"emphase_delta",7,0}
	};
	return reg;
}
bool
DS_rxRegs::_REG_INFO::get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos){
	reg_infos.clear();
	switch(csr){
		case 0:
			reg_infos.push_back(rxpwrdb().reg_info);
			reg_infos.push_back(recclkpwrdb().reg_info);
			reg_infos.push_back(rxcapbypass().reg_info);
			reg_infos.push_back(rxmute().reg_info);
			reg_infos.push_back(lpcmlen().reg_info);
			reg_infos.push_back(txrxserlpbken().reg_info);
			reg_infos.push_back(recclkdiv().reg_info);
			reg_infos.push_back(wordclkdiv_pwrdnb().reg_info);
			reg_infos.push_back(ctlepassgn().reg_info);
			break;
		case 1:
			reg_infos.push_back(ctlebst1().reg_info);
			reg_infos.push_back(ctlecmband1().reg_info);
			reg_infos.push_back(ctlermband1().reg_info);
			reg_infos.push_back(ctleza1().reg_info);
			reg_infos.push_back(ctlesqh1().reg_info);
			reg_infos.push_back(ctleactgn1().reg_info);
			break;
		case 2:
			reg_infos.push_back(ctlebst2().reg_info);
			reg_infos.push_back(ctlecmband2().reg_info);
			reg_infos.push_back(ctlermband2().reg_info);
			reg_infos.push_back(ctleza2().reg_info);
			reg_infos.push_back(ctlesqh2().reg_info);
			reg_infos.push_back(ctleactgn2().reg_info);
			break;
		case 3:
			reg_infos.push_back(ctlebst3().reg_info);
			reg_infos.push_back(ctlecmband3().reg_info);
			reg_infos.push_back(ctlermband3().reg_info);
			reg_infos.push_back(ctleza3().reg_info);
			reg_infos.push_back(ctlesqh3().reg_info);
			reg_infos.push_back(ctleactgn3().reg_info);
			break;
		case 4:
			reg_infos.push_back(dfepwrdb().reg_info);
			reg_infos.push_back(dfeauxmvtappwrdb().reg_info);
			reg_infos.push_back(dfemvtappwrdb().reg_info);
			reg_infos.push_back(dfefxtapen().reg_info);
			reg_infos.push_back(rxtermofst().reg_info);
			reg_infos.push_back(dfegnsum().reg_info);
			break;
		case 5:
			reg_infos.push_back(dfefxtap1().reg_info);
			reg_infos.push_back(dfefxtap2().reg_info);
			break;
		case 6:
			reg_infos.push_back(ana_bmen_n().reg_info);
			reg_infos.push_back(dfefxtap3().reg_info);
			reg_infos.push_back(dfefxtap4().reg_info);
			reg_infos.push_back(dfefxtap5().reg_info);
			break;
		case 7:
			reg_infos.push_back(rxterm_pwrdnb().reg_info);
			reg_infos.push_back(cephase_full().reg_info);
			reg_infos.push_back(pat_des_lvl().reg_info);
			reg_infos.push_back(emphase_sync().reg_info);
			reg_infos.push_back(dfemvtapsel().reg_info);
			break;
		case 8:
			reg_infos.push_back(rxterm_floating_sel().reg_info);
			reg_infos.push_back(dfemvtap1().reg_info);
			reg_infos.push_back(dfemvtap2().reg_info);
			reg_infos.push_back(dfemvtap3().reg_info);
			break;
		case 9:
			reg_infos.push_back(dfemvtap4().reg_info);
			reg_infos.push_back(dfemvtap5().reg_info);
			reg_infos.push_back(dfemvtap6().reg_info);
			break;
		case 10:
			reg_infos.push_back(rxrstb().reg_info);
			reg_infos.push_back(rxdwidth().reg_info);
			reg_infos.push_back(rxratemode().reg_info);
			reg_infos.push_back(rxbitorder().reg_info);
			reg_infos.push_back(rxpolarity().reg_info);
			reg_infos.push_back(txrxparlpbken().reg_info);
			reg_infos.push_back(cdr_mode().reg_info);
			reg_infos.push_back(sw_para_source_sel().reg_info);
			reg_infos.push_back(cdrfreeze().reg_info);
			reg_infos.push_back(bbpdmode().reg_info);
			reg_infos.push_back(secloopen().reg_info);
			reg_infos.push_back(bitslip().reg_info);
			break;
		case 11:
			reg_infos.push_back(cdrrstb().reg_info);
			reg_infos.push_back(cdrphsgn().reg_info);
			reg_infos.push_back(cdrk1gn().reg_info);
			reg_infos.push_back(cdrk2gn().reg_info);
			reg_infos.push_back(freqintsat().reg_info);
			reg_infos.push_back(freqintatt().reg_info);
			break;
		case 12:
			reg_infos.push_back(cphsofst().reg_info);
			reg_infos.push_back(ephsofst().reg_info);
			break;
		case 13:
			reg_infos.push_back(tdden().reg_info);
			reg_infos.push_back(tddthr().reg_info);
			reg_infos.push_back(loseyeen().reg_info);
			reg_infos.push_back(loseyethr().reg_info);
			reg_infos.push_back(losanaen().reg_info);
			reg_infos.push_back(loscfg().reg_info);
			reg_infos.push_back(los().reg_info);
			reg_infos.push_back(lostran().reg_info);
			reg_infos.push_back(loseyever().reg_info);
			reg_infos.push_back(loseyehor().reg_info);
			reg_infos.push_back(losana().reg_info);
			break;
		case 14:
			reg_infos.push_back(timecntstart().reg_info);
			reg_infos.push_back(sigdet_clkdiv().reg_info);
			reg_infos.push_back(sigdetclkdiv_pinsel().reg_info);
			reg_infos.push_back(dsrx_rxclk_res().reg_info);
			reg_infos.push_back(prbschken().reg_info);
			reg_infos.push_back(prbschkmode().reg_info);
			reg_infos.push_back(prbschkpatsel().reg_info);
			break;
		case 15:
			reg_infos.push_back(eyemonpwrdb().reg_info);
			reg_infos.push_back(volofstpol().reg_info);
			reg_infos.push_back(rxeyediag_start().reg_info);
			reg_infos.push_back(rxeyediag_done().reg_info);
			reg_infos.push_back(emready().reg_info);
			reg_infos.push_back(eyescanstart().reg_info);
			reg_infos.push_back(eyescanmode().reg_info);
			reg_infos.push_back(eyescanwinsel().reg_info);
			reg_infos.push_back(eyescanwin().reg_info);
			break;
		case 16:
			reg_infos.push_back(mphsofst().reg_info);
			reg_infos.push_back(mvolofst().reg_info);
			break;
		case 17:
			reg_infos.push_back(eyemetric_abormal().reg_info);
			reg_infos.push_back(mmthr().reg_info);
			reg_infos.push_back(eyemetric_manual().reg_info);
			reg_infos.push_back(eyemetric_start().reg_info);
			reg_infos.push_back(eyemetric_sum().reg_info);
			break;
		case 18:
			reg_infos.push_back(prbserr().reg_info);
			reg_infos.push_back(prbscntexp().reg_info);
			reg_infos.push_back(prbscnt().reg_info);
			break;
		case 19:
			reg_infos.push_back(eyecor0().reg_info);
			reg_infos.push_back(eyecor1().reg_info);
			break;
		case 20:
			reg_infos.push_back(isierr0().reg_info);
			break;
		case 21:
			reg_infos.push_back(isierr1().reg_info);
			break;
		case 22:
			reg_infos.push_back(isierr2().reg_info);
			break;
		case 23:
			reg_infos.push_back(isierr3().reg_info);
			break;
		case 24:
			reg_infos.push_back(isierr4().reg_info);
			break;
		case 25:
			reg_infos.push_back(isierr5().reg_info);
			break;
		case 26:
			reg_infos.push_back(rxtermcalen().reg_info);
			reg_infos.push_back(rxtermcaldir().reg_info);
			reg_infos.push_back(rxtermcal().reg_info);
			break;
		case 27:
			reg_infos.push_back(rxcalmode().reg_info);
			reg_infos.push_back(dscalstart().reg_info);
			reg_infos.push_back(rxcalstart().reg_info);
			reg_infos.push_back(rxterm_floating_en().reg_info);
			reg_infos.push_back(sigdet_win_pcie().reg_info);
			reg_infos.push_back(rxdatalatchcalen().reg_info);
			reg_infos.push_back(rxofstcaldir().reg_info);
			reg_infos.push_back(rxofstsel().reg_info);
			break;
		case 28:
			reg_infos.push_back(ctleofst1().reg_info);
			reg_infos.push_back(ctleofst2().reg_info);
			reg_infos.push_back(ctleofst3().reg_info);
			break;
		case 29:
			reg_infos.push_back(ctleofst4().reg_info);
			reg_infos.push_back(ctleofst5().reg_info);
			reg_infos.push_back(ctleofst6().reg_info);
			break;
		case 30:
			reg_infos.push_back(sigdet_cal_en().reg_info);
			reg_infos.push_back(sigdet_offset().reg_info);
			reg_infos.push_back(dfeevnsumofst().reg_info);
			reg_infos.push_back(dfeoddsumofst().reg_info);
			break;
		case 31:
			reg_infos.push_back(rxctrensampofftrig().reg_info);
			reg_infos.push_back(cevnsnsampofst().reg_info);
			reg_infos.push_back(rxctrensampencal().reg_info);
			reg_infos.push_back(rxsnsampdir().reg_info);
			reg_infos.push_back(rxsigdetdir().reg_info);
			reg_infos.push_back(rxterm_ressel().reg_info);
			reg_infos.push_back(wordclk_divsel().reg_info);
			reg_infos.push_back(rxctle_scresen().reg_info);
			reg_infos.push_back(rxctle_scres_clk_div().reg_info);
			reg_infos.push_back(rx_sigdet_bld_dly_sel().reg_info);
			break;
		case 32:
			reg_infos.push_back(rxctronsampofftrig().reg_info);
			reg_infos.push_back(coddsnsampofst().reg_info);
			reg_infos.push_back(rxctronsampencal().reg_info);
			reg_infos.push_back(bm_ac_r_sel().reg_info);
			reg_infos.push_back(rxctle_mbersel().reg_info);
			break;
		case 33:
			reg_infos.push_back(rxedgensampofftrig().reg_info);
			reg_infos.push_back(eevnsnsampofst().reg_info);
			reg_infos.push_back(rxedgensampencal().reg_info);
			reg_infos.push_back(ds_spare_o().reg_info);
			break;
		case 34:
			reg_infos.push_back(rxedgonsampofftrig().reg_info);
			reg_infos.push_back(eoddsnsampofst().reg_info);
			reg_infos.push_back(rxedgonsampencal().reg_info);
			break;
		case 35:
			reg_infos.push_back(rxmonensampofftrig().reg_info);
			reg_infos.push_back(mevnsnsampofst().reg_info);
			reg_infos.push_back(rxmonensampencal().reg_info);
			break;
		case 36:
			reg_infos.push_back(rxmononsampofftrig().reg_info);
			reg_infos.push_back(moddsnsampofst().reg_info);
			reg_infos.push_back(rxmononsampencal().reg_info);
			reg_infos.push_back(eyest1evnofst().reg_info);
			break;
		case 37:
			reg_infos.push_back(eyest2evnofst().reg_info);
			reg_infos.push_back(squelch_det_thr().reg_info);
			break;
		case 38:
			reg_infos.push_back(dsrx_cor_res().reg_info);
			reg_infos.push_back(eyest1oddofst().reg_info);
			reg_infos.push_back(eyest2oddofst().reg_info);
			break;
		case 39:
			reg_infos.push_back(rxctlerepofftrig().reg_info);
			reg_infos.push_back(replicacaldir().reg_info);
			reg_infos.push_back(rxctlerepcalen().reg_info);
			reg_infos.push_back(rxctlerepcalcode().reg_info);
			reg_infos.push_back(rxctlerefsel().reg_info);
			reg_infos.push_back(rxctleloadsel().reg_info);
			break;
		case 40:
			reg_infos.push_back(rxspare().reg_info);
			reg_infos.push_back(sigdet_manual().reg_info);
			reg_infos.push_back(sigdet_thr_sel_man().reg_info);
			reg_infos.push_back(sigdet_thr_sel().reg_info);
			reg_infos.push_back(ctlepreset().reg_info);
			break;
		case 41:
			reg_infos.push_back(rxparepofftrig().reg_info);
			reg_infos.push_back(rxpacalen().reg_info);
			reg_infos.push_back(rxpacalcode().reg_info);
			reg_infos.push_back(rxparefsel().reg_info);
			reg_infos.push_back(rxpaloadsel().reg_info);
			break;
		case 42:
			reg_infos.push_back(dsrxlowoffpwrdb().reg_info);
			reg_infos.push_back(dsrxlowoffcal().reg_info);
			reg_infos.push_back(dsrxlowoffctrl().reg_info);
			reg_infos.push_back(rxlowoffcaldir().reg_info);
			reg_infos.push_back(dsrxlowoffout().reg_info);
			reg_infos.push_back(rxcalread().reg_info);
			break;
		case 43:
			reg_infos.push_back(rxeye_polarityswitch().reg_info);
			reg_infos.push_back(ctlepreset_en().reg_info);
			reg_infos.push_back(txrxserlpbkatbctrl().reg_info);
			reg_infos.push_back(rxlowoffatbctrl().reg_info);
			reg_infos.push_back(rxatbmuxsel().reg_info);
			reg_infos.push_back(rxatbsel().reg_info);
			break;
		case 44:
			reg_infos.push_back(squelch_detwin().reg_info);
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
		case 45:
			reg_infos.push_back(ceearly().reg_info);
			reg_infos.push_back(celate().reg_info);
			reg_infos.push_back(cmearly().reg_info);
			reg_infos.push_back(cmlate().reg_info);
			reg_infos.push_back(cdr_coarsealigndone().reg_info);
			reg_infos.push_back(sscdr_coarsealigndone().reg_info);
			reg_infos.push_back(edgesleep().reg_info);
			reg_infos.push_back(ecoarsealignen().reg_info);
			reg_infos.push_back(ecoarsealignstep().reg_info);
			reg_infos.push_back(mcoarsealignen().reg_info);
			reg_infos.push_back(mcoarsealignstep().reg_info);
			break;
		case 46:
			reg_infos.push_back(cphsval().reg_info);
			reg_infos.push_back(pat_per_los().reg_info);
			reg_infos.push_back(ephsval().reg_info);
			break;
		case 47:
			reg_infos.push_back(misierrdone().reg_info);
			reg_infos.push_back(mphsofstval().reg_info);
			reg_infos.push_back(mvolofstval().reg_info);
			break;
		case 48:
			reg_infos.push_back(mmcnt().reg_info);
			break;
		case 49:
			reg_infos.push_back(timerexp().reg_info);
			reg_infos.push_back(timer().reg_info);
			break;
		case 50:
			reg_infos.push_back(squelch_det_en().reg_info);
			reg_infos.push_back(rxcal_timer_value().reg_info);
			reg_infos.push_back(rxcal_timer_div_value().reg_info);
			reg_infos.push_back(rxcal_timer_div_en().reg_info);
			reg_infos.push_back(rxcal_timer_stop().reg_info);
			break;
		case 51:
			reg_infos.push_back(cphase_ssc().reg_info);
			reg_infos.push_back(eyescan_rdy().reg_info);
			reg_infos.push_back(sscdr_sftrst_ctrl().reg_info);
			reg_infos.push_back(sscdr_demux_mode().reg_info);
			reg_infos.push_back(sscdr_atb_req().reg_info);
			reg_infos.push_back(ephase_ssc().reg_info);
			break;
		case 52:
			reg_infos.push_back(mphase_ssc().reg_info);
			reg_infos.push_back(sscdr_atb_sel().reg_info);
			reg_infos.push_back(sscdr_atb_out().reg_info);
			break;
		case 53:
			reg_infos.push_back(sscdr_intg_gain().reg_info);
			reg_infos.push_back(sscdr_prop_gain().reg_info);
			reg_infos.push_back(sscdr_loop2_sat().reg_info);
			break;
		case 54:
			reg_infos.push_back(eyemetric_scanmode().reg_info);
			reg_infos.push_back(eyemetric_scanwinsel().reg_info);
			reg_infos.push_back(eyemetric_scanwin().reg_info);
			reg_infos.push_back(rxeyediag_stat().reg_info);
			break;
		case 55:
			reg_infos.push_back(mphsofst_fst().reg_info);
			reg_infos.push_back(mvolofst_fst().reg_info);
			break;
		case 56:
			reg_infos.push_back(mphsofst_sec().reg_info);
			reg_infos.push_back(mvolofst_sec().reg_info);
			break;
		case 57:
			reg_infos.push_back(eyecor0_fst().reg_info);
			reg_infos.push_back(eyecor1_fst().reg_info);
			break;
		case 58:
			reg_infos.push_back(eyecor0_sec().reg_info);
			reg_infos.push_back(eyecor1_sec().reg_info);
			break;
		case 59:
			reg_infos.push_back(sigdet_vlv().reg_info);
			reg_infos.push_back(rxsigdet_pwrdnb().reg_info);
			reg_infos.push_back(rxrecclk_sel().reg_info);
			reg_infos.push_back(bcdr_pin_en().reg_info);
			reg_infos.push_back(ctleparset().reg_info);
			break;
		case 60:
			reg_infos.push_back(sigdet_enable().reg_info);
			reg_infos.push_back(sigdet_win().reg_info);
			reg_infos.push_back(sigdet_thr_s1().reg_info);
			break;
		case 61:
			reg_infos.push_back(sigdet_los().reg_info);
			reg_infos.push_back(sscdr_rst_by_sigdet().reg_info);
			reg_infos.push_back(remotetx().reg_info);
			reg_infos.push_back(squelch_det().reg_info);
			reg_infos.push_back(sigdet_rstb().reg_info);
			reg_infos.push_back(sigdet_thr_s2().reg_info);
			break;
		case 62:
			reg_infos.push_back(pat_det_win().reg_info);
			reg_infos.push_back(sscdr_cmphase().reg_info);
			reg_infos.push_back(emphase_delta().reg_info);
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
DS_rxRegs::setrecclkpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.recclkpwrdb());	//CSR0[14:14]
	return *this;
}
uint
DS_rxRegs::getrecclkpwrdb(){
	return get_csr_bits(REG_INFO.recclkpwrdb());	//CSR0[14:14]
}

DS_rxRegs&
DS_rxRegs::setrxcapbypass(uint val){
	fill_csr_bits(val,REG_INFO.rxcapbypass());	//CSR0[13:13]
	return *this;
}
uint
DS_rxRegs::getrxcapbypass(){
	return get_csr_bits(REG_INFO.rxcapbypass());	//CSR0[13:13]
}

DS_rxRegs&
DS_rxRegs::setrxmute(uint val){
	fill_csr_bits(val,REG_INFO.rxmute());	//CSR0[12:12]
	return *this;
}
uint
DS_rxRegs::getrxmute(){
	return get_csr_bits(REG_INFO.rxmute());	//CSR0[12:12]
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
DS_rxRegs::settxrxserlpbken(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbken());	//CSR0[10:10]
	return *this;
}
uint
DS_rxRegs::gettxrxserlpbken(){
	return get_csr_bits(REG_INFO.txrxserlpbken());	//CSR0[10:10]
}

DS_rxRegs&
DS_rxRegs::setrecclkdiv(uint val){
	fill_csr_bits(val,REG_INFO.recclkdiv());	//CSR0[9:4]
	return *this;
}
uint
DS_rxRegs::getrecclkdiv(){
	return get_csr_bits(REG_INFO.recclkdiv());	//CSR0[9:4]
}

DS_rxRegs&
DS_rxRegs::setwordclkdiv_pwrdnb(uint val){
	fill_csr_bits(val,REG_INFO.wordclkdiv_pwrdnb());	//CSR0[3:3]
	return *this;
}
uint
DS_rxRegs::getwordclkdiv_pwrdnb(){
	return get_csr_bits(REG_INFO.wordclkdiv_pwrdnb());	//CSR0[3:3]
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
DS_rxRegs::setctlebst1(uint val){
	fill_csr_bits(val,REG_INFO.ctlebst1());	//CSR1[15:12]
	return *this;
}
uint
DS_rxRegs::getctlebst1(){
	return get_csr_bits(REG_INFO.ctlebst1());	//CSR1[15:12]
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
	fill_csr_bits(val,REG_INFO.ctleza1());	//CSR1[7:6]
	return *this;
}
uint
DS_rxRegs::getctleza1(){
	return get_csr_bits(REG_INFO.ctleza1());	//CSR1[7:6]
}

DS_rxRegs&
DS_rxRegs::setctlesqh1(uint val){
	fill_csr_bits(val,REG_INFO.ctlesqh1());	//CSR1[5:4]
	return *this;
}
uint
DS_rxRegs::getctlesqh1(){
	return get_csr_bits(REG_INFO.ctlesqh1());	//CSR1[5:4]
}

DS_rxRegs&
DS_rxRegs::setctleactgn1(uint val){
	fill_csr_bits(val,REG_INFO.ctleactgn1());	//CSR1[3:0]
	return *this;
}
uint
DS_rxRegs::getctleactgn1(){
	return get_csr_bits(REG_INFO.ctleactgn1());	//CSR1[3:0]
}

DS_rxRegs&
DS_rxRegs::setctlebst2(uint val){
	fill_csr_bits(val,REG_INFO.ctlebst2());	//CSR2[15:12]
	return *this;
}
uint
DS_rxRegs::getctlebst2(){
	return get_csr_bits(REG_INFO.ctlebst2());	//CSR2[15:12]
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
	fill_csr_bits(val,REG_INFO.ctleza2());	//CSR2[7:6]
	return *this;
}
uint
DS_rxRegs::getctleza2(){
	return get_csr_bits(REG_INFO.ctleza2());	//CSR2[7:6]
}

DS_rxRegs&
DS_rxRegs::setctlesqh2(uint val){
	fill_csr_bits(val,REG_INFO.ctlesqh2());	//CSR2[5:4]
	return *this;
}
uint
DS_rxRegs::getctlesqh2(){
	return get_csr_bits(REG_INFO.ctlesqh2());	//CSR2[5:4]
}

DS_rxRegs&
DS_rxRegs::setctleactgn2(uint val){
	fill_csr_bits(val,REG_INFO.ctleactgn2());	//CSR2[3:0]
	return *this;
}
uint
DS_rxRegs::getctleactgn2(){
	return get_csr_bits(REG_INFO.ctleactgn2());	//CSR2[3:0]
}

DS_rxRegs&
DS_rxRegs::setctlebst3(uint val){
	fill_csr_bits(val,REG_INFO.ctlebst3());	//CSR3[15:12]
	return *this;
}
uint
DS_rxRegs::getctlebst3(){
	return get_csr_bits(REG_INFO.ctlebst3());	//CSR3[15:12]
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
	fill_csr_bits(val,REG_INFO.ctleza3());	//CSR3[7:6]
	return *this;
}
uint
DS_rxRegs::getctleza3(){
	return get_csr_bits(REG_INFO.ctleza3());	//CSR3[7:6]
}

DS_rxRegs&
DS_rxRegs::setctlesqh3(uint val){
	fill_csr_bits(val,REG_INFO.ctlesqh3());	//CSR3[5:4]
	return *this;
}
uint
DS_rxRegs::getctlesqh3(){
	return get_csr_bits(REG_INFO.ctlesqh3());	//CSR3[5:4]
}

DS_rxRegs&
DS_rxRegs::setctleactgn3(uint val){
	fill_csr_bits(val,REG_INFO.ctleactgn3());	//CSR3[3:0]
	return *this;
}
uint
DS_rxRegs::getctleactgn3(){
	return get_csr_bits(REG_INFO.ctleactgn3());	//CSR3[3:0]
}

DS_rxRegs&
DS_rxRegs::setdfepwrdb(uint val){
	fill_csr_bits(val,REG_INFO.dfepwrdb());	//CSR4[15:15]
	return *this;
}
uint
DS_rxRegs::getdfepwrdb(){
	return get_csr_bits(REG_INFO.dfepwrdb());	//CSR4[15:15]
}

DS_rxRegs&
DS_rxRegs::setdfeauxmvtappwrdb(uint val){
	fill_csr_bits(val,REG_INFO.dfeauxmvtappwrdb());	//CSR4[14:14]
	return *this;
}
uint
DS_rxRegs::getdfeauxmvtappwrdb(){
	return get_csr_bits(REG_INFO.dfeauxmvtappwrdb());	//CSR4[14:14]
}

DS_rxRegs&
DS_rxRegs::setdfemvtappwrdb(uint val){
	fill_csr_bits(val,REG_INFO.dfemvtappwrdb());	//CSR4[13:13]
	return *this;
}
uint
DS_rxRegs::getdfemvtappwrdb(){
	return get_csr_bits(REG_INFO.dfemvtappwrdb());	//CSR4[13:13]
}

DS_rxRegs&
DS_rxRegs::setdfefxtapen(uint val){
	fill_csr_bits(val,REG_INFO.dfefxtapen());	//CSR4[12:8]
	return *this;
}
uint
DS_rxRegs::getdfefxtapen(){
	return get_csr_bits(REG_INFO.dfefxtapen());	//CSR4[12:8]
}

DS_rxRegs&
DS_rxRegs::setrxtermofst(uint val){
	fill_csr_bits(val,REG_INFO.rxtermofst());	//CSR4[7:4]
	return *this;
}
uint
DS_rxRegs::getrxtermofst(){
	return get_csr_bits(REG_INFO.rxtermofst());	//CSR4[7:4]
}

DS_rxRegs&
DS_rxRegs::setdfegnsum(uint val){
	fill_csr_bits(val,REG_INFO.dfegnsum());	//CSR4[2:0]
	return *this;
}
uint
DS_rxRegs::getdfegnsum(){
	return get_csr_bits(REG_INFO.dfegnsum());	//CSR4[2:0]
}

DS_rxRegs&
DS_rxRegs::setdfefxtap1(uint val){
	fill_csr_bits(val,REG_INFO.dfefxtap1());	//CSR5[15:9]
	return *this;
}
uint
DS_rxRegs::getdfefxtap1(){
	return get_csr_bits(REG_INFO.dfefxtap1());	//CSR5[15:9]
}

DS_rxRegs&
DS_rxRegs::setdfefxtap2(uint val){
	fill_csr_bits(val,REG_INFO.dfefxtap2());	//CSR5[5:0]
	return *this;
}
uint
DS_rxRegs::getdfefxtap2(){
	return get_csr_bits(REG_INFO.dfefxtap2());	//CSR5[5:0]
}

DS_rxRegs&
DS_rxRegs::setana_bmen_n(uint val){
	fill_csr_bits(val,REG_INFO.ana_bmen_n());	//CSR6[15:15]
	return *this;
}
uint
DS_rxRegs::getana_bmen_n(){
	return get_csr_bits(REG_INFO.ana_bmen_n());	//CSR6[15:15]
}

DS_rxRegs&
DS_rxRegs::setdfefxtap3(uint val){
	fill_csr_bits(val,REG_INFO.dfefxtap3());	//CSR6[14:10]
	return *this;
}
uint
DS_rxRegs::getdfefxtap3(){
	return get_csr_bits(REG_INFO.dfefxtap3());	//CSR6[14:10]
}

DS_rxRegs&
DS_rxRegs::setdfefxtap4(uint val){
	fill_csr_bits(val,REG_INFO.dfefxtap4());	//CSR6[9:5]
	return *this;
}
uint
DS_rxRegs::getdfefxtap4(){
	return get_csr_bits(REG_INFO.dfefxtap4());	//CSR6[9:5]
}

DS_rxRegs&
DS_rxRegs::setdfefxtap5(uint val){
	fill_csr_bits(val,REG_INFO.dfefxtap5());	//CSR6[4:0]
	return *this;
}
uint
DS_rxRegs::getdfefxtap5(){
	return get_csr_bits(REG_INFO.dfefxtap5());	//CSR6[4:0]
}

DS_rxRegs&
DS_rxRegs::setrxterm_pwrdnb(uint val){
	fill_csr_bits(val,REG_INFO.rxterm_pwrdnb());	//CSR7[15:15]
	return *this;
}
uint
DS_rxRegs::getrxterm_pwrdnb(){
	return get_csr_bits(REG_INFO.rxterm_pwrdnb());	//CSR7[15:15]
}

DS_rxRegs&
DS_rxRegs::setcephase_full(uint val){
	fill_csr_bits(val,REG_INFO.cephase_full());	//CSR7[14:9]
	return *this;
}
uint
DS_rxRegs::getcephase_full(){
	return get_csr_bits(REG_INFO.cephase_full());	//CSR7[14:9]
}

DS_rxRegs&
DS_rxRegs::setpat_des_lvl(uint val){
	fill_csr_bits(val,REG_INFO.pat_des_lvl());	//CSR7[8:6]
	return *this;
}
uint
DS_rxRegs::getpat_des_lvl(){
	return get_csr_bits(REG_INFO.pat_des_lvl());	//CSR7[8:6]
}

DS_rxRegs&
DS_rxRegs::setemphase_sync(uint val){
	fill_csr_bits(val,REG_INFO.emphase_sync());	//CSR7[5:5]
	return *this;
}
uint
DS_rxRegs::getemphase_sync(){
	return get_csr_bits(REG_INFO.emphase_sync());	//CSR7[5:5]
}

DS_rxRegs&
DS_rxRegs::setdfemvtapsel(uint val){
	fill_csr_bits(val,REG_INFO.dfemvtapsel());	//CSR7[4:0]
	return *this;
}
uint
DS_rxRegs::getdfemvtapsel(){
	return get_csr_bits(REG_INFO.dfemvtapsel());	//CSR7[4:0]
}

DS_rxRegs&
DS_rxRegs::setrxterm_floating_sel(uint val){
	fill_csr_bits(val,REG_INFO.rxterm_floating_sel());	//CSR8[15:15]
	return *this;
}
uint
DS_rxRegs::getrxterm_floating_sel(){
	return get_csr_bits(REG_INFO.rxterm_floating_sel());	//CSR8[15:15]
}

DS_rxRegs&
DS_rxRegs::setdfemvtap1(uint val){
	fill_csr_bits(val,REG_INFO.dfemvtap1());	//CSR8[14:10]
	return *this;
}
uint
DS_rxRegs::getdfemvtap1(){
	return get_csr_bits(REG_INFO.dfemvtap1());	//CSR8[14:10]
}

DS_rxRegs&
DS_rxRegs::setdfemvtap2(uint val){
	fill_csr_bits(val,REG_INFO.dfemvtap2());	//CSR8[9:5]
	return *this;
}
uint
DS_rxRegs::getdfemvtap2(){
	return get_csr_bits(REG_INFO.dfemvtap2());	//CSR8[9:5]
}

DS_rxRegs&
DS_rxRegs::setdfemvtap3(uint val){
	fill_csr_bits(val,REG_INFO.dfemvtap3());	//CSR8[4:0]
	return *this;
}
uint
DS_rxRegs::getdfemvtap3(){
	return get_csr_bits(REG_INFO.dfemvtap3());	//CSR8[4:0]
}

DS_rxRegs&
DS_rxRegs::setdfemvtap4(uint val){
	fill_csr_bits(val,REG_INFO.dfemvtap4());	//CSR9[14:10]
	return *this;
}
uint
DS_rxRegs::getdfemvtap4(){
	return get_csr_bits(REG_INFO.dfemvtap4());	//CSR9[14:10]
}

DS_rxRegs&
DS_rxRegs::setdfemvtap5(uint val){
	fill_csr_bits(val,REG_INFO.dfemvtap5());	//CSR9[9:5]
	return *this;
}
uint
DS_rxRegs::getdfemvtap5(){
	return get_csr_bits(REG_INFO.dfemvtap5());	//CSR9[9:5]
}

DS_rxRegs&
DS_rxRegs::setdfemvtap6(uint val){
	fill_csr_bits(val,REG_INFO.dfemvtap6());	//CSR9[4:0]
	return *this;
}
uint
DS_rxRegs::getdfemvtap6(){
	return get_csr_bits(REG_INFO.dfemvtap6());	//CSR9[4:0]
}

DS_rxRegs&
DS_rxRegs::setrxrstb(uint val){
	fill_csr_bits(val,REG_INFO.rxrstb());	//CSR10[15:15]
	return *this;
}
uint
DS_rxRegs::getrxrstb(){
	return get_csr_bits(REG_INFO.rxrstb());	//CSR10[15:15]
}

DS_rxRegs&
DS_rxRegs::setrxdwidth(uint val){
	fill_csr_bits(val,REG_INFO.rxdwidth());	//CSR10[14:12]
	return *this;
}
uint
DS_rxRegs::getrxdwidth(){
	return get_csr_bits(REG_INFO.rxdwidth());	//CSR10[14:12]
}

DS_rxRegs&
DS_rxRegs::setrxratemode(uint val){
	fill_csr_bits(val,REG_INFO.rxratemode());	//CSR10[11:10]
	return *this;
}
uint
DS_rxRegs::getrxratemode(){
	return get_csr_bits(REG_INFO.rxratemode());	//CSR10[11:10]
}

DS_rxRegs&
DS_rxRegs::setrxbitorder(uint val){
	fill_csr_bits(val,REG_INFO.rxbitorder());	//CSR10[9:9]
	return *this;
}
uint
DS_rxRegs::getrxbitorder(){
	return get_csr_bits(REG_INFO.rxbitorder());	//CSR10[9:9]
}

DS_rxRegs&
DS_rxRegs::setrxpolarity(uint val){
	fill_csr_bits(val,REG_INFO.rxpolarity());	//CSR10[8:8]
	return *this;
}
uint
DS_rxRegs::getrxpolarity(){
	return get_csr_bits(REG_INFO.rxpolarity());	//CSR10[8:8]
}

DS_rxRegs&
DS_rxRegs::settxrxparlpbken(uint val){
	fill_csr_bits(val,REG_INFO.txrxparlpbken());	//CSR10[7:7]
	return *this;
}
uint
DS_rxRegs::gettxrxparlpbken(){
	return get_csr_bits(REG_INFO.txrxparlpbken());	//CSR10[7:7]
}

DS_rxRegs&
DS_rxRegs::setcdr_mode(uint val){
	fill_csr_bits(val,REG_INFO.cdr_mode());	//CSR10[6:6]
	return *this;
}
uint
DS_rxRegs::getcdr_mode(){
	return get_csr_bits(REG_INFO.cdr_mode());	//CSR10[6:6]
}

DS_rxRegs&
DS_rxRegs::setsw_para_source_sel(uint val){
	fill_csr_bits(val,REG_INFO.sw_para_source_sel());	//CSR10[5:5]
	return *this;
}
uint
DS_rxRegs::getsw_para_source_sel(){
	return get_csr_bits(REG_INFO.sw_para_source_sel());	//CSR10[5:5]
}

DS_rxRegs&
DS_rxRegs::setcdrfreeze(uint val){
	fill_csr_bits(val,REG_INFO.cdrfreeze());	//CSR10[3:3]
	return *this;
}
uint
DS_rxRegs::getcdrfreeze(){
	return get_csr_bits(REG_INFO.cdrfreeze());	//CSR10[3:3]
}

DS_rxRegs&
DS_rxRegs::setbbpdmode(uint val){
	fill_csr_bits(val,REG_INFO.bbpdmode());	//CSR10[2:2]
	return *this;
}
uint
DS_rxRegs::getbbpdmode(){
	return get_csr_bits(REG_INFO.bbpdmode());	//CSR10[2:2]
}

DS_rxRegs&
DS_rxRegs::setsecloopen(uint val){
	fill_csr_bits(val,REG_INFO.secloopen());	//CSR10[1:1]
	return *this;
}
uint
DS_rxRegs::getsecloopen(){
	return get_csr_bits(REG_INFO.secloopen());	//CSR10[1:1]
}

DS_rxRegs&
DS_rxRegs::setbitslip(uint val){
	fill_csr_bits(val,REG_INFO.bitslip());	//CSR10[0:0]
	return *this;
}
uint
DS_rxRegs::getbitslip(){
	return get_csr_bits(REG_INFO.bitslip());	//CSR10[0:0]
}

DS_rxRegs&
DS_rxRegs::setcdrrstb(uint val){
	fill_csr_bits(val,REG_INFO.cdrrstb());	//CSR11[15:15]
	return *this;
}
uint
DS_rxRegs::getcdrrstb(){
	return get_csr_bits(REG_INFO.cdrrstb());	//CSR11[15:15]
}

DS_rxRegs&
DS_rxRegs::setcdrphsgn(uint val){
	fill_csr_bits(val,REG_INFO.cdrphsgn());	//CSR11[13:11]
	return *this;
}
uint
DS_rxRegs::getcdrphsgn(){
	return get_csr_bits(REG_INFO.cdrphsgn());	//CSR11[13:11]
}

DS_rxRegs&
DS_rxRegs::setcdrk1gn(uint val){
	fill_csr_bits(val,REG_INFO.cdrk1gn());	//CSR11[10:8]
	return *this;
}
uint
DS_rxRegs::getcdrk1gn(){
	return get_csr_bits(REG_INFO.cdrk1gn());	//CSR11[10:8]
}

DS_rxRegs&
DS_rxRegs::setcdrk2gn(uint val){
	fill_csr_bits(val,REG_INFO.cdrk2gn());	//CSR11[7:5]
	return *this;
}
uint
DS_rxRegs::getcdrk2gn(){
	return get_csr_bits(REG_INFO.cdrk2gn());	//CSR11[7:5]
}

DS_rxRegs&
DS_rxRegs::setfreqintsat(uint val){
	fill_csr_bits(val,REG_INFO.freqintsat());	//CSR11[4:2]
	return *this;
}
uint
DS_rxRegs::getfreqintsat(){
	return get_csr_bits(REG_INFO.freqintsat());	//CSR11[4:2]
}

DS_rxRegs&
DS_rxRegs::setfreqintatt(uint val){
	fill_csr_bits(val,REG_INFO.freqintatt());	//CSR11[1:0]
	return *this;
}
uint
DS_rxRegs::getfreqintatt(){
	return get_csr_bits(REG_INFO.freqintatt());	//CSR11[1:0]
}

DS_rxRegs&
DS_rxRegs::setcphsofst(uint val){
	fill_csr_bits(val,REG_INFO.cphsofst());	//CSR12[15:8]
	return *this;
}
uint
DS_rxRegs::getcphsofst(){
	return get_csr_bits(REG_INFO.cphsofst());	//CSR12[15:8]
}

DS_rxRegs&
DS_rxRegs::setephsofst(uint val){
	fill_csr_bits(val,REG_INFO.ephsofst());	//CSR12[7:0]
	return *this;
}
uint
DS_rxRegs::getephsofst(){
	return get_csr_bits(REG_INFO.ephsofst());	//CSR12[7:0]
}

DS_rxRegs&
DS_rxRegs::settdden(uint val){
	fill_csr_bits(val,REG_INFO.tdden());	//CSR13[15:15]
	return *this;
}
uint
DS_rxRegs::gettdden(){
	return get_csr_bits(REG_INFO.tdden());	//CSR13[15:15]
}

DS_rxRegs&
DS_rxRegs::settddthr(uint val){
	fill_csr_bits(val,REG_INFO.tddthr());	//CSR13[14:12]
	return *this;
}
uint
DS_rxRegs::gettddthr(){
	return get_csr_bits(REG_INFO.tddthr());	//CSR13[14:12]
}

DS_rxRegs&
DS_rxRegs::setloseyeen(uint val){
	fill_csr_bits(val,REG_INFO.loseyeen());	//CSR13[11:11]
	return *this;
}
uint
DS_rxRegs::getloseyeen(){
	return get_csr_bits(REG_INFO.loseyeen());	//CSR13[11:11]
}

DS_rxRegs&
DS_rxRegs::setloseyethr(uint val){
	fill_csr_bits(val,REG_INFO.loseyethr());	//CSR13[10:9]
	return *this;
}
uint
DS_rxRegs::getloseyethr(){
	return get_csr_bits(REG_INFO.loseyethr());	//CSR13[10:9]
}

DS_rxRegs&
DS_rxRegs::setlosanaen(uint val){
	fill_csr_bits(val,REG_INFO.losanaen());	//CSR13[8:8]
	return *this;
}
uint
DS_rxRegs::getlosanaen(){
	return get_csr_bits(REG_INFO.losanaen());	//CSR13[8:8]
}

DS_rxRegs&
DS_rxRegs::setloscfg(uint val){
	fill_csr_bits(val,REG_INFO.loscfg());	//CSR13[7:5]
	return *this;
}
uint
DS_rxRegs::getloscfg(){
	return get_csr_bits(REG_INFO.loscfg());	//CSR13[7:5]
}

uint
DS_rxRegs::getlos(){
	return get_csr_bits(REG_INFO.los());	//CSR13[4:4]
}

uint
DS_rxRegs::getlostran(){
	return get_csr_bits(REG_INFO.lostran());	//CSR13[3:3]
}

uint
DS_rxRegs::getloseyever(){
	return get_csr_bits(REG_INFO.loseyever());	//CSR13[2:2]
}

uint
DS_rxRegs::getloseyehor(){
	return get_csr_bits(REG_INFO.loseyehor());	//CSR13[1:1]
}

uint
DS_rxRegs::getlosana(){
	return get_csr_bits(REG_INFO.losana());	//CSR13[0:0]
}

DS_rxRegs&
DS_rxRegs::settimecntstart(uint val){
	fill_csr_bits(val,REG_INFO.timecntstart());	//CSR14[15:15]
	return *this;
}
uint
DS_rxRegs::gettimecntstart(){
	return get_csr_bits(REG_INFO.timecntstart());	//CSR14[15:15]
}

DS_rxRegs&
DS_rxRegs::setsigdet_clkdiv(uint val){
	fill_csr_bits(val,REG_INFO.sigdet_clkdiv());	//CSR14[14:14]
	return *this;
}
uint
DS_rxRegs::getsigdet_clkdiv(){
	return get_csr_bits(REG_INFO.sigdet_clkdiv());	//CSR14[14:14]
}

DS_rxRegs&
DS_rxRegs::setsigdetclkdiv_pinsel(uint val){
	fill_csr_bits(val,REG_INFO.sigdetclkdiv_pinsel());	//CSR14[13:13]
	return *this;
}
uint
DS_rxRegs::getsigdetclkdiv_pinsel(){
	return get_csr_bits(REG_INFO.sigdetclkdiv_pinsel());	//CSR14[13:13]
}

DS_rxRegs&
DS_rxRegs::setdsrx_rxclk_res(uint val){
	fill_csr_bits(val,REG_INFO.dsrx_rxclk_res());	//CSR14[12:6]
	return *this;
}
uint
DS_rxRegs::getdsrx_rxclk_res(){
	return get_csr_bits(REG_INFO.dsrx_rxclk_res());	//CSR14[12:6]
}

DS_rxRegs&
DS_rxRegs::setprbschken(uint val){
	fill_csr_bits(val,REG_INFO.prbschken());	//CSR14[5:5]
	return *this;
}
uint
DS_rxRegs::getprbschken(){
	return get_csr_bits(REG_INFO.prbschken());	//CSR14[5:5]
}

DS_rxRegs&
DS_rxRegs::setprbschkmode(uint val){
	fill_csr_bits(val,REG_INFO.prbschkmode());	//CSR14[4:4]
	return *this;
}
uint
DS_rxRegs::getprbschkmode(){
	return get_csr_bits(REG_INFO.prbschkmode());	//CSR14[4:4]
}

DS_rxRegs&
DS_rxRegs::setprbschkpatsel(uint val){
	fill_csr_bits(val,REG_INFO.prbschkpatsel());	//CSR14[3:0]
	return *this;
}
uint
DS_rxRegs::getprbschkpatsel(){
	return get_csr_bits(REG_INFO.prbschkpatsel());	//CSR14[3:0]
}

DS_rxRegs&
DS_rxRegs::seteyemonpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.eyemonpwrdb());	//CSR15[15:15]
	return *this;
}
uint
DS_rxRegs::geteyemonpwrdb(){
	return get_csr_bits(REG_INFO.eyemonpwrdb());	//CSR15[15:15]
}

DS_rxRegs&
DS_rxRegs::setvolofstpol(uint val){
	fill_csr_bits(val,REG_INFO.volofstpol());	//CSR15[14:14]
	return *this;
}
uint
DS_rxRegs::getvolofstpol(){
	return get_csr_bits(REG_INFO.volofstpol());	//CSR15[14:14]
}

uint
DS_rxRegs::getrxeyediag_start(){
	return get_csr_bits(REG_INFO.rxeyediag_start());	//CSR15[13:13]
}

uint
DS_rxRegs::getrxeyediag_done(){
	return get_csr_bits(REG_INFO.rxeyediag_done());	//CSR15[12:12]
}

uint
DS_rxRegs::getemready(){
	return get_csr_bits(REG_INFO.emready());	//CSR15[11:11]
}

DS_rxRegs&
DS_rxRegs::seteyescanstart(uint val){
	fill_csr_bits(val,REG_INFO.eyescanstart());	//CSR15[10:10]
	return *this;
}
uint
DS_rxRegs::geteyescanstart(){
	return get_csr_bits(REG_INFO.eyescanstart());	//CSR15[10:10]
}

DS_rxRegs&
DS_rxRegs::seteyescanmode(uint val){
	fill_csr_bits(val,REG_INFO.eyescanmode());	//CSR15[9:7]
	return *this;
}
uint
DS_rxRegs::geteyescanmode(){
	return get_csr_bits(REG_INFO.eyescanmode());	//CSR15[9:7]
}

DS_rxRegs&
DS_rxRegs::seteyescanwinsel(uint val){
	fill_csr_bits(val,REG_INFO.eyescanwinsel());	//CSR15[6:6]
	return *this;
}
uint
DS_rxRegs::geteyescanwinsel(){
	return get_csr_bits(REG_INFO.eyescanwinsel());	//CSR15[6:6]
}

DS_rxRegs&
DS_rxRegs::seteyescanwin(uint val){
	fill_csr_bits(val,REG_INFO.eyescanwin());	//CSR15[5:0]
	return *this;
}
uint
DS_rxRegs::geteyescanwin(){
	return get_csr_bits(REG_INFO.eyescanwin());	//CSR15[5:0]
}

DS_rxRegs&
DS_rxRegs::setmphsofst(uint val){
	fill_csr_bits(val,REG_INFO.mphsofst());	//CSR16[15:8]
	return *this;
}
uint
DS_rxRegs::getmphsofst(){
	return get_csr_bits(REG_INFO.mphsofst());	//CSR16[15:8]
}

DS_rxRegs&
DS_rxRegs::setmvolofst(uint val){
	fill_csr_bits(val,REG_INFO.mvolofst());	//CSR16[7:0]
	return *this;
}
uint
DS_rxRegs::getmvolofst(){
	return get_csr_bits(REG_INFO.mvolofst());	//CSR16[7:0]
}

uint
DS_rxRegs::geteyemetric_abormal(){
	return get_csr_bits(REG_INFO.eyemetric_abormal());	//CSR17[14:14]
}

DS_rxRegs&
DS_rxRegs::setmmthr(uint val){
	fill_csr_bits(val,REG_INFO.mmthr());	//CSR17[13:10]
	return *this;
}
uint
DS_rxRegs::getmmthr(){
	return get_csr_bits(REG_INFO.mmthr());	//CSR17[13:10]
}

DS_rxRegs&
DS_rxRegs::seteyemetric_manual(uint val){
	fill_csr_bits(val,REG_INFO.eyemetric_manual());	//CSR17[9:9]
	return *this;
}
uint
DS_rxRegs::geteyemetric_manual(){
	return get_csr_bits(REG_INFO.eyemetric_manual());	//CSR17[9:9]
}

DS_rxRegs&
DS_rxRegs::seteyemetric_start(uint val){
	fill_csr_bits(val,REG_INFO.eyemetric_start());	//CSR17[8:8]
	return *this;
}
uint
DS_rxRegs::geteyemetric_start(){
	return get_csr_bits(REG_INFO.eyemetric_start());	//CSR17[8:8]
}

DS_rxRegs&
DS_rxRegs::seteyemetric_sum(uint val){
	fill_csr_bits(val,REG_INFO.eyemetric_sum());	//CSR17[7:0]
	return *this;
}
uint
DS_rxRegs::geteyemetric_sum(){
	return get_csr_bits(REG_INFO.eyemetric_sum());	//CSR17[7:0]
}

uint
DS_rxRegs::getprbserr(){
	return get_csr_bits(REG_INFO.prbserr());	//CSR18[15:15]
}

uint
DS_rxRegs::getprbscntexp(){
	return get_csr_bits(REG_INFO.prbscntexp());	//CSR18[14:11]
}

uint
DS_rxRegs::getprbscnt(){
	return get_csr_bits(REG_INFO.prbscnt());	//CSR18[10:0]
}

uint
DS_rxRegs::geteyecor0(){
	return get_csr_bits(REG_INFO.eyecor0());	//CSR19[15:8]
}

uint
DS_rxRegs::geteyecor1(){
	return get_csr_bits(REG_INFO.eyecor1());	//CSR19[7:0]
}

uint
DS_rxRegs::getisierr0(){
	return get_csr_bits(REG_INFO.isierr0());	//CSR20[15:0]
}

uint
DS_rxRegs::getisierr1(){
	return get_csr_bits(REG_INFO.isierr1());	//CSR21[15:0]
}

uint
DS_rxRegs::getisierr2(){
	return get_csr_bits(REG_INFO.isierr2());	//CSR22[15:0]
}

uint
DS_rxRegs::getisierr3(){
	return get_csr_bits(REG_INFO.isierr3());	//CSR23[15:0]
}

uint
DS_rxRegs::getisierr4(){
	return get_csr_bits(REG_INFO.isierr4());	//CSR24[15:0]
}

uint
DS_rxRegs::getisierr5(){
	return get_csr_bits(REG_INFO.isierr5());	//CSR25[15:0]
}

DS_rxRegs&
DS_rxRegs::setrxtermcalen(uint val){
	fill_csr_bits(val,REG_INFO.rxtermcalen());	//CSR26[15:15]
	return *this;
}
uint
DS_rxRegs::getrxtermcalen(){
	return get_csr_bits(REG_INFO.rxtermcalen());	//CSR26[15:15]
}

DS_rxRegs&
DS_rxRegs::setrxtermcaldir(uint val){
	fill_csr_bits(val,REG_INFO.rxtermcaldir());	//CSR26[14:14]
	return *this;
}
uint
DS_rxRegs::getrxtermcaldir(){
	return get_csr_bits(REG_INFO.rxtermcaldir());	//CSR26[14:14]
}

DS_rxRegs&
DS_rxRegs::setrxtermcal(uint val){
	fill_csr_bits(val,REG_INFO.rxtermcal());	//CSR26[13:0]
	return *this;
}
uint
DS_rxRegs::getrxtermcal(){
	return get_csr_bits(REG_INFO.rxtermcal());	//CSR26[13:0]
}

DS_rxRegs&
DS_rxRegs::setrxcalmode(uint val){
	fill_csr_bits(val,REG_INFO.rxcalmode());	//CSR27[15:15]
	return *this;
}
uint
DS_rxRegs::getrxcalmode(){
	return get_csr_bits(REG_INFO.rxcalmode());	//CSR27[15:15]
}

DS_rxRegs&
DS_rxRegs::setdscalstart(uint val){
	fill_csr_bits(val,REG_INFO.dscalstart());	//CSR27[14:14]
	return *this;
}
uint
DS_rxRegs::getdscalstart(){
	return get_csr_bits(REG_INFO.dscalstart());	//CSR27[14:14]
}

DS_rxRegs&
DS_rxRegs::setrxcalstart(uint val){
	fill_csr_bits(val,REG_INFO.rxcalstart());	//CSR27[13:13]
	return *this;
}
uint
DS_rxRegs::getrxcalstart(){
	return get_csr_bits(REG_INFO.rxcalstart());	//CSR27[13:13]
}

DS_rxRegs&
DS_rxRegs::setrxterm_floating_en(uint val){
	fill_csr_bits(val,REG_INFO.rxterm_floating_en());	//CSR27[12:12]
	return *this;
}
uint
DS_rxRegs::getrxterm_floating_en(){
	return get_csr_bits(REG_INFO.rxterm_floating_en());	//CSR27[12:12]
}

DS_rxRegs&
DS_rxRegs::setsigdet_win_pcie(uint val){
	fill_csr_bits(val,REG_INFO.sigdet_win_pcie());	//CSR27[11:8]
	return *this;
}
uint
DS_rxRegs::getsigdet_win_pcie(){
	return get_csr_bits(REG_INFO.sigdet_win_pcie());	//CSR27[11:8]
}

DS_rxRegs&
DS_rxRegs::setrxdatalatchcalen(uint val){
	fill_csr_bits(val,REG_INFO.rxdatalatchcalen());	//CSR27[7:7]
	return *this;
}
uint
DS_rxRegs::getrxdatalatchcalen(){
	return get_csr_bits(REG_INFO.rxdatalatchcalen());	//CSR27[7:7]
}

DS_rxRegs&
DS_rxRegs::setrxofstcaldir(uint val){
	fill_csr_bits(val,REG_INFO.rxofstcaldir());	//CSR27[6:6]
	return *this;
}
uint
DS_rxRegs::getrxofstcaldir(){
	return get_csr_bits(REG_INFO.rxofstcaldir());	//CSR27[6:6]
}

DS_rxRegs&
DS_rxRegs::setrxofstsel(uint val){
	fill_csr_bits(val,REG_INFO.rxofstsel());	//CSR27[5:0]
	return *this;
}
uint
DS_rxRegs::getrxofstsel(){
	return get_csr_bits(REG_INFO.rxofstsel());	//CSR27[5:0]
}

DS_rxRegs&
DS_rxRegs::setctleofst1(uint val){
	fill_csr_bits(val,REG_INFO.ctleofst1());	//CSR28[14:10]
	return *this;
}
uint
DS_rxRegs::getctleofst1(){
	return get_csr_bits(REG_INFO.ctleofst1());	//CSR28[14:10]
}

DS_rxRegs&
DS_rxRegs::setctleofst2(uint val){
	fill_csr_bits(val,REG_INFO.ctleofst2());	//CSR28[9:5]
	return *this;
}
uint
DS_rxRegs::getctleofst2(){
	return get_csr_bits(REG_INFO.ctleofst2());	//CSR28[9:5]
}

DS_rxRegs&
DS_rxRegs::setctleofst3(uint val){
	fill_csr_bits(val,REG_INFO.ctleofst3());	//CSR28[4:0]
	return *this;
}
uint
DS_rxRegs::getctleofst3(){
	return get_csr_bits(REG_INFO.ctleofst3());	//CSR28[4:0]
}

DS_rxRegs&
DS_rxRegs::setctleofst4(uint val){
	fill_csr_bits(val,REG_INFO.ctleofst4());	//CSR29[14:10]
	return *this;
}
uint
DS_rxRegs::getctleofst4(){
	return get_csr_bits(REG_INFO.ctleofst4());	//CSR29[14:10]
}

DS_rxRegs&
DS_rxRegs::setctleofst5(uint val){
	fill_csr_bits(val,REG_INFO.ctleofst5());	//CSR29[9:5]
	return *this;
}
uint
DS_rxRegs::getctleofst5(){
	return get_csr_bits(REG_INFO.ctleofst5());	//CSR29[9:5]
}

DS_rxRegs&
DS_rxRegs::setctleofst6(uint val){
	fill_csr_bits(val,REG_INFO.ctleofst6());	//CSR29[4:0]
	return *this;
}
uint
DS_rxRegs::getctleofst6(){
	return get_csr_bits(REG_INFO.ctleofst6());	//CSR29[4:0]
}

DS_rxRegs&
DS_rxRegs::setsigdet_cal_en(uint val){
	fill_csr_bits(val,REG_INFO.sigdet_cal_en());	//CSR30[15:15]
	return *this;
}
uint
DS_rxRegs::getsigdet_cal_en(){
	return get_csr_bits(REG_INFO.sigdet_cal_en());	//CSR30[15:15]
}

DS_rxRegs&
DS_rxRegs::setsigdet_offset(uint val){
	fill_csr_bits(val,REG_INFO.sigdet_offset());	//CSR30[14:10]
	return *this;
}
uint
DS_rxRegs::getsigdet_offset(){
	return get_csr_bits(REG_INFO.sigdet_offset());	//CSR30[14:10]
}

DS_rxRegs&
DS_rxRegs::setdfeevnsumofst(uint val){
	fill_csr_bits(val,REG_INFO.dfeevnsumofst());	//CSR30[9:5]
	return *this;
}
uint
DS_rxRegs::getdfeevnsumofst(){
	return get_csr_bits(REG_INFO.dfeevnsumofst());	//CSR30[9:5]
}

DS_rxRegs&
DS_rxRegs::setdfeoddsumofst(uint val){
	fill_csr_bits(val,REG_INFO.dfeoddsumofst());	//CSR30[4:0]
	return *this;
}
uint
DS_rxRegs::getdfeoddsumofst(){
	return get_csr_bits(REG_INFO.dfeoddsumofst());	//CSR30[4:0]
}

uint
DS_rxRegs::getrxctrensampofftrig(){
	return get_csr_bits(REG_INFO.rxctrensampofftrig());	//CSR31[15:15]
}

DS_rxRegs&
DS_rxRegs::setcevnsnsampofst(uint val){
	fill_csr_bits(val,REG_INFO.cevnsnsampofst());	//CSR31[14:9]
	return *this;
}
uint
DS_rxRegs::getcevnsnsampofst(){
	return get_csr_bits(REG_INFO.cevnsnsampofst());	//CSR31[14:9]
}

DS_rxRegs&
DS_rxRegs::setrxctrensampencal(uint val){
	fill_csr_bits(val,REG_INFO.rxctrensampencal());	//CSR31[8:8]
	return *this;
}
uint
DS_rxRegs::getrxctrensampencal(){
	return get_csr_bits(REG_INFO.rxctrensampencal());	//CSR31[8:8]
}

DS_rxRegs&
DS_rxRegs::setrxsnsampdir(uint val){
	fill_csr_bits(val,REG_INFO.rxsnsampdir());	//CSR31[7:7]
	return *this;
}
uint
DS_rxRegs::getrxsnsampdir(){
	return get_csr_bits(REG_INFO.rxsnsampdir());	//CSR31[7:7]
}

DS_rxRegs&
DS_rxRegs::setrxsigdetdir(uint val){
	fill_csr_bits(val,REG_INFO.rxsigdetdir());	//CSR31[6:6]
	return *this;
}
uint
DS_rxRegs::getrxsigdetdir(){
	return get_csr_bits(REG_INFO.rxsigdetdir());	//CSR31[6:6]
}

DS_rxRegs&
DS_rxRegs::setrxterm_ressel(uint val){
	fill_csr_bits(val,REG_INFO.rxterm_ressel());	//CSR31[5:4]
	return *this;
}
uint
DS_rxRegs::getrxterm_ressel(){
	return get_csr_bits(REG_INFO.rxterm_ressel());	//CSR31[5:4]
}

DS_rxRegs&
DS_rxRegs::setwordclk_divsel(uint val){
	fill_csr_bits(val,REG_INFO.wordclk_divsel());	//CSR31[3:3]
	return *this;
}
uint
DS_rxRegs::getwordclk_divsel(){
	return get_csr_bits(REG_INFO.wordclk_divsel());	//CSR31[3:3]
}

DS_rxRegs&
DS_rxRegs::setrxctle_scresen(uint val){
	fill_csr_bits(val,REG_INFO.rxctle_scresen());	//CSR31[2:2]
	return *this;
}
uint
DS_rxRegs::getrxctle_scresen(){
	return get_csr_bits(REG_INFO.rxctle_scresen());	//CSR31[2:2]
}

DS_rxRegs&
DS_rxRegs::setrxctle_scres_clk_div(uint val){
	fill_csr_bits(val,REG_INFO.rxctle_scres_clk_div());	//CSR31[1:1]
	return *this;
}
uint
DS_rxRegs::getrxctle_scres_clk_div(){
	return get_csr_bits(REG_INFO.rxctle_scres_clk_div());	//CSR31[1:1]
}

DS_rxRegs&
DS_rxRegs::setrx_sigdet_bld_dly_sel(uint val){
	fill_csr_bits(val,REG_INFO.rx_sigdet_bld_dly_sel());	//CSR31[0:0]
	return *this;
}
uint
DS_rxRegs::getrx_sigdet_bld_dly_sel(){
	return get_csr_bits(REG_INFO.rx_sigdet_bld_dly_sel());	//CSR31[0:0]
}

uint
DS_rxRegs::getrxctronsampofftrig(){
	return get_csr_bits(REG_INFO.rxctronsampofftrig());	//CSR32[15:15]
}

DS_rxRegs&
DS_rxRegs::setcoddsnsampofst(uint val){
	fill_csr_bits(val,REG_INFO.coddsnsampofst());	//CSR32[14:9]
	return *this;
}
uint
DS_rxRegs::getcoddsnsampofst(){
	return get_csr_bits(REG_INFO.coddsnsampofst());	//CSR32[14:9]
}

DS_rxRegs&
DS_rxRegs::setrxctronsampencal(uint val){
	fill_csr_bits(val,REG_INFO.rxctronsampencal());	//CSR32[8:8]
	return *this;
}
uint
DS_rxRegs::getrxctronsampencal(){
	return get_csr_bits(REG_INFO.rxctronsampencal());	//CSR32[8:8]
}

DS_rxRegs&
DS_rxRegs::setbm_ac_r_sel(uint val){
	fill_csr_bits(val,REG_INFO.bm_ac_r_sel());	//CSR32[7:6]
	return *this;
}
uint
DS_rxRegs::getbm_ac_r_sel(){
	return get_csr_bits(REG_INFO.bm_ac_r_sel());	//CSR32[7:6]
}

DS_rxRegs&
DS_rxRegs::setrxctle_mbersel(uint val){
	fill_csr_bits(val,REG_INFO.rxctle_mbersel());	//CSR32[5:3]
	return *this;
}
uint
DS_rxRegs::getrxctle_mbersel(){
	return get_csr_bits(REG_INFO.rxctle_mbersel());	//CSR32[5:3]
}

uint
DS_rxRegs::getrxedgensampofftrig(){
	return get_csr_bits(REG_INFO.rxedgensampofftrig());	//CSR33[15:15]
}

DS_rxRegs&
DS_rxRegs::seteevnsnsampofst(uint val){
	fill_csr_bits(val,REG_INFO.eevnsnsampofst());	//CSR33[14:9]
	return *this;
}
uint
DS_rxRegs::geteevnsnsampofst(){
	return get_csr_bits(REG_INFO.eevnsnsampofst());	//CSR33[14:9]
}

DS_rxRegs&
DS_rxRegs::setrxedgensampencal(uint val){
	fill_csr_bits(val,REG_INFO.rxedgensampencal());	//CSR33[8:8]
	return *this;
}
uint
DS_rxRegs::getrxedgensampencal(){
	return get_csr_bits(REG_INFO.rxedgensampencal());	//CSR33[8:8]
}

uint
DS_rxRegs::getds_spare_o(){
	return get_csr_bits(REG_INFO.ds_spare_o());	//CSR33[7:0]
}

uint
DS_rxRegs::getrxedgonsampofftrig(){
	return get_csr_bits(REG_INFO.rxedgonsampofftrig());	//CSR34[15:15]
}

DS_rxRegs&
DS_rxRegs::seteoddsnsampofst(uint val){
	fill_csr_bits(val,REG_INFO.eoddsnsampofst());	//CSR34[14:9]
	return *this;
}
uint
DS_rxRegs::geteoddsnsampofst(){
	return get_csr_bits(REG_INFO.eoddsnsampofst());	//CSR34[14:9]
}

DS_rxRegs&
DS_rxRegs::setrxedgonsampencal(uint val){
	fill_csr_bits(val,REG_INFO.rxedgonsampencal());	//CSR34[8:8]
	return *this;
}
uint
DS_rxRegs::getrxedgonsampencal(){
	return get_csr_bits(REG_INFO.rxedgonsampencal());	//CSR34[8:8]
}

uint
DS_rxRegs::getrxmonensampofftrig(){
	return get_csr_bits(REG_INFO.rxmonensampofftrig());	//CSR35[15:15]
}

DS_rxRegs&
DS_rxRegs::setmevnsnsampofst(uint val){
	fill_csr_bits(val,REG_INFO.mevnsnsampofst());	//CSR35[14:9]
	return *this;
}
uint
DS_rxRegs::getmevnsnsampofst(){
	return get_csr_bits(REG_INFO.mevnsnsampofst());	//CSR35[14:9]
}

DS_rxRegs&
DS_rxRegs::setrxmonensampencal(uint val){
	fill_csr_bits(val,REG_INFO.rxmonensampencal());	//CSR35[8:8]
	return *this;
}
uint
DS_rxRegs::getrxmonensampencal(){
	return get_csr_bits(REG_INFO.rxmonensampencal());	//CSR35[8:8]
}

uint
DS_rxRegs::getrxmononsampofftrig(){
	return get_csr_bits(REG_INFO.rxmononsampofftrig());	//CSR36[15:15]
}

DS_rxRegs&
DS_rxRegs::setmoddsnsampofst(uint val){
	fill_csr_bits(val,REG_INFO.moddsnsampofst());	//CSR36[14:9]
	return *this;
}
uint
DS_rxRegs::getmoddsnsampofst(){
	return get_csr_bits(REG_INFO.moddsnsampofst());	//CSR36[14:9]
}

DS_rxRegs&
DS_rxRegs::setrxmononsampencal(uint val){
	fill_csr_bits(val,REG_INFO.rxmononsampencal());	//CSR36[8:8]
	return *this;
}
uint
DS_rxRegs::getrxmononsampencal(){
	return get_csr_bits(REG_INFO.rxmononsampencal());	//CSR36[8:8]
}

DS_rxRegs&
DS_rxRegs::seteyest1evnofst(uint val){
	fill_csr_bits(val,REG_INFO.eyest1evnofst());	//CSR36[7:3]
	return *this;
}
uint
DS_rxRegs::geteyest1evnofst(){
	return get_csr_bits(REG_INFO.eyest1evnofst());	//CSR36[7:3]
}

DS_rxRegs&
DS_rxRegs::seteyest2evnofst(uint val){
	fill_csr_bits(val,REG_INFO.eyest2evnofst());	//CSR37[15:11]
	return *this;
}
uint
DS_rxRegs::geteyest2evnofst(){
	return get_csr_bits(REG_INFO.eyest2evnofst());	//CSR37[15:11]
}

DS_rxRegs&
DS_rxRegs::setsquelch_det_thr(uint val){
	fill_csr_bits(val,REG_INFO.squelch_det_thr());	//CSR37[10:0]
	return *this;
}
uint
DS_rxRegs::getsquelch_det_thr(){
	return get_csr_bits(REG_INFO.squelch_det_thr());	//CSR37[10:0]
}

DS_rxRegs&
DS_rxRegs::setdsrx_cor_res(uint val){
	fill_csr_bits(val,REG_INFO.dsrx_cor_res());	//CSR38[15:10]
	return *this;
}
uint
DS_rxRegs::getdsrx_cor_res(){
	return get_csr_bits(REG_INFO.dsrx_cor_res());	//CSR38[15:10]
}

DS_rxRegs&
DS_rxRegs::seteyest1oddofst(uint val){
	fill_csr_bits(val,REG_INFO.eyest1oddofst());	//CSR38[9:5]
	return *this;
}
uint
DS_rxRegs::geteyest1oddofst(){
	return get_csr_bits(REG_INFO.eyest1oddofst());	//CSR38[9:5]
}

DS_rxRegs&
DS_rxRegs::seteyest2oddofst(uint val){
	fill_csr_bits(val,REG_INFO.eyest2oddofst());	//CSR38[4:0]
	return *this;
}
uint
DS_rxRegs::geteyest2oddofst(){
	return get_csr_bits(REG_INFO.eyest2oddofst());	//CSR38[4:0]
}

uint
DS_rxRegs::getrxctlerepofftrig(){
	return get_csr_bits(REG_INFO.rxctlerepofftrig());	//CSR39[15:15]
}

DS_rxRegs&
DS_rxRegs::setreplicacaldir(uint val){
	fill_csr_bits(val,REG_INFO.replicacaldir());	//CSR39[12:12]
	return *this;
}
uint
DS_rxRegs::getreplicacaldir(){
	return get_csr_bits(REG_INFO.replicacaldir());	//CSR39[12:12]
}

DS_rxRegs&
DS_rxRegs::setrxctlerepcalen(uint val){
	fill_csr_bits(val,REG_INFO.rxctlerepcalen());	//CSR39[11:11]
	return *this;
}
uint
DS_rxRegs::getrxctlerepcalen(){
	return get_csr_bits(REG_INFO.rxctlerepcalen());	//CSR39[11:11]
}

DS_rxRegs&
DS_rxRegs::setrxctlerepcalcode(uint val){
	fill_csr_bits(val,REG_INFO.rxctlerepcalcode());	//CSR39[10:6]
	return *this;
}
uint
DS_rxRegs::getrxctlerepcalcode(){
	return get_csr_bits(REG_INFO.rxctlerepcalcode());	//CSR39[10:6]
}

DS_rxRegs&
DS_rxRegs::setrxctlerefsel(uint val){
	fill_csr_bits(val,REG_INFO.rxctlerefsel());	//CSR39[5:3]
	return *this;
}
uint
DS_rxRegs::getrxctlerefsel(){
	return get_csr_bits(REG_INFO.rxctlerefsel());	//CSR39[5:3]
}

DS_rxRegs&
DS_rxRegs::setrxctleloadsel(uint val){
	fill_csr_bits(val,REG_INFO.rxctleloadsel());	//CSR39[2:0]
	return *this;
}
uint
DS_rxRegs::getrxctleloadsel(){
	return get_csr_bits(REG_INFO.rxctleloadsel());	//CSR39[2:0]
}

DS_rxRegs&
DS_rxRegs::setrxspare(uint val){
	fill_csr_bits(val,REG_INFO.rxspare());	//CSR40[15:8]
	return *this;
}
uint
DS_rxRegs::getrxspare(){
	return get_csr_bits(REG_INFO.rxspare());	//CSR40[15:8]
}

DS_rxRegs&
DS_rxRegs::setsigdet_manual(uint val){
	fill_csr_bits(val,REG_INFO.sigdet_manual());	//CSR40[7:7]
	return *this;
}
uint
DS_rxRegs::getsigdet_manual(){
	return get_csr_bits(REG_INFO.sigdet_manual());	//CSR40[7:7]
}

DS_rxRegs&
DS_rxRegs::setsigdet_thr_sel_man(uint val){
	fill_csr_bits(val,REG_INFO.sigdet_thr_sel_man());	//CSR40[6:6]
	return *this;
}
uint
DS_rxRegs::getsigdet_thr_sel_man(){
	return get_csr_bits(REG_INFO.sigdet_thr_sel_man());	//CSR40[6:6]
}

uint
DS_rxRegs::getsigdet_thr_sel(){
	return get_csr_bits(REG_INFO.sigdet_thr_sel());	//CSR40[5:5]
}

uint
DS_rxRegs::getctlepreset(){
	return get_csr_bits(REG_INFO.ctlepreset());	//CSR40[2:0]
}

uint
DS_rxRegs::getrxparepofftrig(){
	return get_csr_bits(REG_INFO.rxparepofftrig());	//CSR41[15:15]
}

DS_rxRegs&
DS_rxRegs::setrxpacalen(uint val){
	fill_csr_bits(val,REG_INFO.rxpacalen());	//CSR41[11:11]
	return *this;
}
uint
DS_rxRegs::getrxpacalen(){
	return get_csr_bits(REG_INFO.rxpacalen());	//CSR41[11:11]
}

DS_rxRegs&
DS_rxRegs::setrxpacalcode(uint val){
	fill_csr_bits(val,REG_INFO.rxpacalcode());	//CSR41[10:6]
	return *this;
}
uint
DS_rxRegs::getrxpacalcode(){
	return get_csr_bits(REG_INFO.rxpacalcode());	//CSR41[10:6]
}

DS_rxRegs&
DS_rxRegs::setrxparefsel(uint val){
	fill_csr_bits(val,REG_INFO.rxparefsel());	//CSR41[5:3]
	return *this;
}
uint
DS_rxRegs::getrxparefsel(){
	return get_csr_bits(REG_INFO.rxparefsel());	//CSR41[5:3]
}

DS_rxRegs&
DS_rxRegs::setrxpaloadsel(uint val){
	fill_csr_bits(val,REG_INFO.rxpaloadsel());	//CSR41[2:0]
	return *this;
}
uint
DS_rxRegs::getrxpaloadsel(){
	return get_csr_bits(REG_INFO.rxpaloadsel());	//CSR41[2:0]
}

DS_rxRegs&
DS_rxRegs::setdsrxlowoffpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.dsrxlowoffpwrdb());	//CSR42[15:15]
	return *this;
}
uint
DS_rxRegs::getdsrxlowoffpwrdb(){
	return get_csr_bits(REG_INFO.dsrxlowoffpwrdb());	//CSR42[15:15]
}

DS_rxRegs&
DS_rxRegs::setdsrxlowoffcal(uint val){
	fill_csr_bits(val,REG_INFO.dsrxlowoffcal());	//CSR42[14:14]
	return *this;
}
uint
DS_rxRegs::getdsrxlowoffcal(){
	return get_csr_bits(REG_INFO.dsrxlowoffcal());	//CSR42[14:14]
}

DS_rxRegs&
DS_rxRegs::setdsrxlowoffctrl(uint val){
	fill_csr_bits(val,REG_INFO.dsrxlowoffctrl());	//CSR42[13:8]
	return *this;
}
uint
DS_rxRegs::getdsrxlowoffctrl(){
	return get_csr_bits(REG_INFO.dsrxlowoffctrl());	//CSR42[13:8]
}

DS_rxRegs&
DS_rxRegs::setrxlowoffcaldir(uint val){
	fill_csr_bits(val,REG_INFO.rxlowoffcaldir());	//CSR42[7:7]
	return *this;
}
uint
DS_rxRegs::getrxlowoffcaldir(){
	return get_csr_bits(REG_INFO.rxlowoffcaldir());	//CSR42[7:7]
}

uint
DS_rxRegs::getdsrxlowoffout(){
	return get_csr_bits(REG_INFO.dsrxlowoffout());	//CSR42[6:6]
}

uint
DS_rxRegs::getrxcalread(){
	return get_csr_bits(REG_INFO.rxcalread());	//CSR42[5:0]
}

DS_rxRegs&
DS_rxRegs::setrxeye_polarityswitch(uint val){
	fill_csr_bits(val,REG_INFO.rxeye_polarityswitch());	//CSR43[15:15]
	return *this;
}
uint
DS_rxRegs::getrxeye_polarityswitch(){
	return get_csr_bits(REG_INFO.rxeye_polarityswitch());	//CSR43[15:15]
}

DS_rxRegs&
DS_rxRegs::setctlepreset_en(uint val){
	fill_csr_bits(val,REG_INFO.ctlepreset_en());	//CSR43[14:14]
	return *this;
}
uint
DS_rxRegs::getctlepreset_en(){
	return get_csr_bits(REG_INFO.ctlepreset_en());	//CSR43[14:14]
}

DS_rxRegs&
DS_rxRegs::settxrxserlpbkatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.txrxserlpbkatbctrl());	//CSR43[13:12]
	return *this;
}
uint
DS_rxRegs::gettxrxserlpbkatbctrl(){
	return get_csr_bits(REG_INFO.txrxserlpbkatbctrl());	//CSR43[13:12]
}

DS_rxRegs&
DS_rxRegs::setrxlowoffatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.rxlowoffatbctrl());	//CSR43[11:10]
	return *this;
}
uint
DS_rxRegs::getrxlowoffatbctrl(){
	return get_csr_bits(REG_INFO.rxlowoffatbctrl());	//CSR43[11:10]
}

DS_rxRegs&
DS_rxRegs::setrxatbmuxsel(uint val){
	fill_csr_bits(val,REG_INFO.rxatbmuxsel());	//CSR43[9:8]
	return *this;
}
uint
DS_rxRegs::getrxatbmuxsel(){
	return get_csr_bits(REG_INFO.rxatbmuxsel());	//CSR43[9:8]
}

DS_rxRegs&
DS_rxRegs::setrxatbsel(uint val){
	fill_csr_bits(val,REG_INFO.rxatbsel());	//CSR43[7:0]
	return *this;
}
uint
DS_rxRegs::getrxatbsel(){
	return get_csr_bits(REG_INFO.rxatbsel());	//CSR43[7:0]
}

DS_rxRegs&
DS_rxRegs::setsquelch_detwin(uint val){
	fill_csr_bits(val,REG_INFO.squelch_detwin());	//CSR44[15:12]
	return *this;
}
uint
DS_rxRegs::getsquelch_detwin(){
	return get_csr_bits(REG_INFO.squelch_detwin());	//CSR44[15:12]
}

DS_rxRegs&
DS_rxRegs::setjtagsel(uint val){
	fill_csr_bits(val,REG_INFO.jtagsel());	//CSR44[11:11]
	return *this;
}
uint
DS_rxRegs::getjtagsel(){
	return get_csr_bits(REG_INFO.jtagsel());	//CSR44[11:11]
}

uint
DS_rxRegs::getjtagoutp(){
	return get_csr_bits(REG_INFO.jtagoutp());	//CSR44[10:10]
}

uint
DS_rxRegs::getjtagoutm(){
	return get_csr_bits(REG_INFO.jtagoutm());	//CSR44[9:9]
}

DS_rxRegs&
DS_rxRegs::setjtagpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.jtagpwrdb());	//CSR44[8:8]
	return *this;
}
uint
DS_rxRegs::getjtagpwrdb(){
	return get_csr_bits(REG_INFO.jtagpwrdb());	//CSR44[8:8]
}

DS_rxRegs&
DS_rxRegs::setjtagacmodeen(uint val){
	fill_csr_bits(val,REG_INFO.jtagacmodeen());	//CSR44[7:7]
	return *this;
}
uint
DS_rxRegs::getjtagacmodeen(){
	return get_csr_bits(REG_INFO.jtagacmodeen());	//CSR44[7:7]
}

DS_rxRegs&
DS_rxRegs::setjtaginitclk(uint val){
	fill_csr_bits(val,REG_INFO.jtaginitclk());	//CSR44[6:6]
	return *this;
}
uint
DS_rxRegs::getjtaginitclk(){
	return get_csr_bits(REG_INFO.jtaginitclk());	//CSR44[6:6]
}

DS_rxRegs&
DS_rxRegs::setjtaginitp(uint val){
	fill_csr_bits(val,REG_INFO.jtaginitp());	//CSR44[5:5]
	return *this;
}
uint
DS_rxRegs::getjtaginitp(){
	return get_csr_bits(REG_INFO.jtaginitp());	//CSR44[5:5]
}

DS_rxRegs&
DS_rxRegs::setjtaginitm(uint val){
	fill_csr_bits(val,REG_INFO.jtaginitm());	//CSR44[4:4]
	return *this;
}
uint
DS_rxRegs::getjtaginitm(){
	return get_csr_bits(REG_INFO.jtaginitm());	//CSR44[4:4]
}

DS_rxRegs&
DS_rxRegs::setjtaghystadj(uint val){
	fill_csr_bits(val,REG_INFO.jtaghystadj());	//CSR44[3:2]
	return *this;
}
uint
DS_rxRegs::getjtaghystadj(){
	return get_csr_bits(REG_INFO.jtaghystadj());	//CSR44[3:2]
}

DS_rxRegs&
DS_rxRegs::setjtagthadj(uint val){
	fill_csr_bits(val,REG_INFO.jtagthadj());	//CSR44[1:0]
	return *this;
}
uint
DS_rxRegs::getjtagthadj(){
	return get_csr_bits(REG_INFO.jtagthadj());	//CSR44[1:0]
}

uint
DS_rxRegs::getceearly(){
	return get_csr_bits(REG_INFO.ceearly());	//CSR45[15:15]
}

uint
DS_rxRegs::getcelate(){
	return get_csr_bits(REG_INFO.celate());	//CSR45[14:14]
}

uint
DS_rxRegs::getcmearly(){
	return get_csr_bits(REG_INFO.cmearly());	//CSR45[13:13]
}

uint
DS_rxRegs::getcmlate(){
	return get_csr_bits(REG_INFO.cmlate());	//CSR45[12:12]
}

uint
DS_rxRegs::getcdr_coarsealigndone(){
	return get_csr_bits(REG_INFO.cdr_coarsealigndone());	//CSR45[11:11]
}

uint
DS_rxRegs::getsscdr_coarsealigndone(){
	return get_csr_bits(REG_INFO.sscdr_coarsealigndone());	//CSR45[10:10]
}

DS_rxRegs&
DS_rxRegs::setedgesleep(uint val){
	fill_csr_bits(val,REG_INFO.edgesleep());	//CSR45[8:8]
	return *this;
}
uint
DS_rxRegs::getedgesleep(){
	return get_csr_bits(REG_INFO.edgesleep());	//CSR45[8:8]
}

DS_rxRegs&
DS_rxRegs::setecoarsealignen(uint val){
	fill_csr_bits(val,REG_INFO.ecoarsealignen());	//CSR45[7:7]
	return *this;
}
uint
DS_rxRegs::getecoarsealignen(){
	return get_csr_bits(REG_INFO.ecoarsealignen());	//CSR45[7:7]
}

DS_rxRegs&
DS_rxRegs::setecoarsealignstep(uint val){
	fill_csr_bits(val,REG_INFO.ecoarsealignstep());	//CSR45[6:4]
	return *this;
}
uint
DS_rxRegs::getecoarsealignstep(){
	return get_csr_bits(REG_INFO.ecoarsealignstep());	//CSR45[6:4]
}

DS_rxRegs&
DS_rxRegs::setmcoarsealignen(uint val){
	fill_csr_bits(val,REG_INFO.mcoarsealignen());	//CSR45[3:3]
	return *this;
}
uint
DS_rxRegs::getmcoarsealignen(){
	return get_csr_bits(REG_INFO.mcoarsealignen());	//CSR45[3:3]
}

DS_rxRegs&
DS_rxRegs::setmcoarsealignstep(uint val){
	fill_csr_bits(val,REG_INFO.mcoarsealignstep());	//CSR45[2:0]
	return *this;
}
uint
DS_rxRegs::getmcoarsealignstep(){
	return get_csr_bits(REG_INFO.mcoarsealignstep());	//CSR45[2:0]
}

uint
DS_rxRegs::getcphsval(){
	return get_csr_bits(REG_INFO.cphsval());	//CSR46[14:8]
}

uint
DS_rxRegs::getpat_per_los(){
	return get_csr_bits(REG_INFO.pat_per_los());	//CSR46[7:7]
}

uint
DS_rxRegs::getephsval(){
	return get_csr_bits(REG_INFO.ephsval());	//CSR46[6:0]
}

uint
DS_rxRegs::getmisierrdone(){
	return get_csr_bits(REG_INFO.misierrdone());	//CSR47[15:15]
}

uint
DS_rxRegs::getmphsofstval(){
	return get_csr_bits(REG_INFO.mphsofstval());	//CSR47[14:8]
}

uint
DS_rxRegs::getmvolofstval(){
	return get_csr_bits(REG_INFO.mvolofstval());	//CSR47[7:0]
}

uint
DS_rxRegs::getmmcnt(){
	return get_csr_bits(REG_INFO.mmcnt());	//CSR48[15:0]
}

uint
DS_rxRegs::gettimerexp(){
	return get_csr_bits(REG_INFO.timerexp());	//CSR49[15:11]
}

uint
DS_rxRegs::gettimer(){
	return get_csr_bits(REG_INFO.timer());	//CSR49[10:0]
}

DS_rxRegs&
DS_rxRegs::setsquelch_det_en(uint val){
	fill_csr_bits(val,REG_INFO.squelch_det_en());	//CSR50[15:15]
	return *this;
}
uint
DS_rxRegs::getsquelch_det_en(){
	return get_csr_bits(REG_INFO.squelch_det_en());	//CSR50[15:15]
}

DS_rxRegs&
DS_rxRegs::setrxcal_timer_value(uint val){
	fill_csr_bits(val,REG_INFO.rxcal_timer_value());	//CSR50[14:5]
	return *this;
}
uint
DS_rxRegs::getrxcal_timer_value(){
	return get_csr_bits(REG_INFO.rxcal_timer_value());	//CSR50[14:5]
}

DS_rxRegs&
DS_rxRegs::setrxcal_timer_div_value(uint val){
	fill_csr_bits(val,REG_INFO.rxcal_timer_div_value());	//CSR50[4:2]
	return *this;
}
uint
DS_rxRegs::getrxcal_timer_div_value(){
	return get_csr_bits(REG_INFO.rxcal_timer_div_value());	//CSR50[4:2]
}

DS_rxRegs&
DS_rxRegs::setrxcal_timer_div_en(uint val){
	fill_csr_bits(val,REG_INFO.rxcal_timer_div_en());	//CSR50[1:1]
	return *this;
}
uint
DS_rxRegs::getrxcal_timer_div_en(){
	return get_csr_bits(REG_INFO.rxcal_timer_div_en());	//CSR50[1:1]
}

DS_rxRegs&
DS_rxRegs::setrxcal_timer_stop(uint val){
	fill_csr_bits(val,REG_INFO.rxcal_timer_stop());	//CSR50[0:0]
	return *this;
}
uint
DS_rxRegs::getrxcal_timer_stop(){
	return get_csr_bits(REG_INFO.rxcal_timer_stop());	//CSR50[0:0]
}

uint
DS_rxRegs::getcphase_ssc(){
	return get_csr_bits(REG_INFO.cphase_ssc());	//CSR51[15:10]
}

uint
DS_rxRegs::geteyescan_rdy(){
	return get_csr_bits(REG_INFO.eyescan_rdy());	//CSR51[9:9]
}

DS_rxRegs&
DS_rxRegs::setsscdr_sftrst_ctrl(uint val){
	fill_csr_bits(val,REG_INFO.sscdr_sftrst_ctrl());	//CSR51[8:8]
	return *this;
}
uint
DS_rxRegs::getsscdr_sftrst_ctrl(){
	return get_csr_bits(REG_INFO.sscdr_sftrst_ctrl());	//CSR51[8:8]
}

DS_rxRegs&
DS_rxRegs::setsscdr_demux_mode(uint val){
	fill_csr_bits(val,REG_INFO.sscdr_demux_mode());	//CSR51[7:7]
	return *this;
}
uint
DS_rxRegs::getsscdr_demux_mode(){
	return get_csr_bits(REG_INFO.sscdr_demux_mode());	//CSR51[7:7]
}

DS_rxRegs&
DS_rxRegs::setsscdr_atb_req(uint val){
	fill_csr_bits(val,REG_INFO.sscdr_atb_req());	//CSR51[6:6]
	return *this;
}
uint
DS_rxRegs::getsscdr_atb_req(){
	return get_csr_bits(REG_INFO.sscdr_atb_req());	//CSR51[6:6]
}

uint
DS_rxRegs::getephase_ssc(){
	return get_csr_bits(REG_INFO.ephase_ssc());	//CSR51[5:0]
}

uint
DS_rxRegs::getmphase_ssc(){
	return get_csr_bits(REG_INFO.mphase_ssc());	//CSR52[15:10]
}

DS_rxRegs&
DS_rxRegs::setsscdr_atb_sel(uint val){
	fill_csr_bits(val,REG_INFO.sscdr_atb_sel());	//CSR52[9:7]
	return *this;
}
uint
DS_rxRegs::getsscdr_atb_sel(){
	return get_csr_bits(REG_INFO.sscdr_atb_sel());	//CSR52[9:7]
}

uint
DS_rxRegs::getsscdr_atb_out(){
	return get_csr_bits(REG_INFO.sscdr_atb_out());	//CSR52[6:0]
}

DS_rxRegs&
DS_rxRegs::setsscdr_intg_gain(uint val){
	fill_csr_bits(val,REG_INFO.sscdr_intg_gain());	//CSR53[15:11]
	return *this;
}
uint
DS_rxRegs::getsscdr_intg_gain(){
	return get_csr_bits(REG_INFO.sscdr_intg_gain());	//CSR53[15:11]
}

DS_rxRegs&
DS_rxRegs::setsscdr_prop_gain(uint val){
	fill_csr_bits(val,REG_INFO.sscdr_prop_gain());	//CSR53[10:6]
	return *this;
}
uint
DS_rxRegs::getsscdr_prop_gain(){
	return get_csr_bits(REG_INFO.sscdr_prop_gain());	//CSR53[10:6]
}

DS_rxRegs&
DS_rxRegs::setsscdr_loop2_sat(uint val){
	fill_csr_bits(val,REG_INFO.sscdr_loop2_sat());	//CSR53[5:0]
	return *this;
}
uint
DS_rxRegs::getsscdr_loop2_sat(){
	return get_csr_bits(REG_INFO.sscdr_loop2_sat());	//CSR53[5:0]
}

DS_rxRegs&
DS_rxRegs::seteyemetric_scanmode(uint val){
	fill_csr_bits(val,REG_INFO.eyemetric_scanmode());	//CSR54[15:13]
	return *this;
}
uint
DS_rxRegs::geteyemetric_scanmode(){
	return get_csr_bits(REG_INFO.eyemetric_scanmode());	//CSR54[15:13]
}

DS_rxRegs&
DS_rxRegs::seteyemetric_scanwinsel(uint val){
	fill_csr_bits(val,REG_INFO.eyemetric_scanwinsel());	//CSR54[12:12]
	return *this;
}
uint
DS_rxRegs::geteyemetric_scanwinsel(){
	return get_csr_bits(REG_INFO.eyemetric_scanwinsel());	//CSR54[12:12]
}

DS_rxRegs&
DS_rxRegs::seteyemetric_scanwin(uint val){
	fill_csr_bits(val,REG_INFO.eyemetric_scanwin());	//CSR54[11:8]
	return *this;
}
uint
DS_rxRegs::geteyemetric_scanwin(){
	return get_csr_bits(REG_INFO.eyemetric_scanwin());	//CSR54[11:8]
}

uint
DS_rxRegs::getrxeyediag_stat(){
	return get_csr_bits(REG_INFO.rxeyediag_stat());	//CSR54[7:0]
}

DS_rxRegs&
DS_rxRegs::setmphsofst_fst(uint val){
	fill_csr_bits(val,REG_INFO.mphsofst_fst());	//CSR55[15:8]
	return *this;
}
uint
DS_rxRegs::getmphsofst_fst(){
	return get_csr_bits(REG_INFO.mphsofst_fst());	//CSR55[15:8]
}

DS_rxRegs&
DS_rxRegs::setmvolofst_fst(uint val){
	fill_csr_bits(val,REG_INFO.mvolofst_fst());	//CSR55[7:0]
	return *this;
}
uint
DS_rxRegs::getmvolofst_fst(){
	return get_csr_bits(REG_INFO.mvolofst_fst());	//CSR55[7:0]
}

DS_rxRegs&
DS_rxRegs::setmphsofst_sec(uint val){
	fill_csr_bits(val,REG_INFO.mphsofst_sec());	//CSR56[15:8]
	return *this;
}
uint
DS_rxRegs::getmphsofst_sec(){
	return get_csr_bits(REG_INFO.mphsofst_sec());	//CSR56[15:8]
}

DS_rxRegs&
DS_rxRegs::setmvolofst_sec(uint val){
	fill_csr_bits(val,REG_INFO.mvolofst_sec());	//CSR56[7:0]
	return *this;
}
uint
DS_rxRegs::getmvolofst_sec(){
	return get_csr_bits(REG_INFO.mvolofst_sec());	//CSR56[7:0]
}

uint
DS_rxRegs::geteyecor0_fst(){
	return get_csr_bits(REG_INFO.eyecor0_fst());	//CSR57[15:8]
}

uint
DS_rxRegs::geteyecor1_fst(){
	return get_csr_bits(REG_INFO.eyecor1_fst());	//CSR57[7:0]
}

uint
DS_rxRegs::geteyecor0_sec(){
	return get_csr_bits(REG_INFO.eyecor0_sec());	//CSR58[15:8]
}

uint
DS_rxRegs::geteyecor1_sec(){
	return get_csr_bits(REG_INFO.eyecor1_sec());	//CSR58[7:0]
}

DS_rxRegs&
DS_rxRegs::setsigdet_vlv(uint val){
	fill_csr_bits(val,REG_INFO.sigdet_vlv());	//CSR59[15:9]
	return *this;
}
uint
DS_rxRegs::getsigdet_vlv(){
	return get_csr_bits(REG_INFO.sigdet_vlv());	//CSR59[15:9]
}

DS_rxRegs&
DS_rxRegs::setrxsigdet_pwrdnb(uint val){
	fill_csr_bits(val,REG_INFO.rxsigdet_pwrdnb());	//CSR59[8:8]
	return *this;
}
uint
DS_rxRegs::getrxsigdet_pwrdnb(){
	return get_csr_bits(REG_INFO.rxsigdet_pwrdnb());	//CSR59[8:8]
}

DS_rxRegs&
DS_rxRegs::setrxrecclk_sel(uint val){
	fill_csr_bits(val,REG_INFO.rxrecclk_sel());	//CSR59[7:5]
	return *this;
}
uint
DS_rxRegs::getrxrecclk_sel(){
	return get_csr_bits(REG_INFO.rxrecclk_sel());	//CSR59[7:5]
}

DS_rxRegs&
DS_rxRegs::setbcdr_pin_en(uint val){
	fill_csr_bits(val,REG_INFO.bcdr_pin_en());	//CSR59[4:4]
	return *this;
}
uint
DS_rxRegs::getbcdr_pin_en(){
	return get_csr_bits(REG_INFO.bcdr_pin_en());	//CSR59[4:4]
}

DS_rxRegs&
DS_rxRegs::setctleparset(uint val){
	fill_csr_bits(val,REG_INFO.ctleparset());	//CSR59[2:0]
	return *this;
}
uint
DS_rxRegs::getctleparset(){
	return get_csr_bits(REG_INFO.ctleparset());	//CSR59[2:0]
}

DS_rxRegs&
DS_rxRegs::setsigdet_enable(uint val){
	fill_csr_bits(val,REG_INFO.sigdet_enable());	//CSR60[15:15]
	return *this;
}
uint
DS_rxRegs::getsigdet_enable(){
	return get_csr_bits(REG_INFO.sigdet_enable());	//CSR60[15:15]
}

DS_rxRegs&
DS_rxRegs::setsigdet_win(uint val){
	fill_csr_bits(val,REG_INFO.sigdet_win());	//CSR60[14:11]
	return *this;
}
uint
DS_rxRegs::getsigdet_win(){
	return get_csr_bits(REG_INFO.sigdet_win());	//CSR60[14:11]
}

DS_rxRegs&
DS_rxRegs::setsigdet_thr_s1(uint val){
	fill_csr_bits(val,REG_INFO.sigdet_thr_s1());	//CSR60[10:0]
	return *this;
}
uint
DS_rxRegs::getsigdet_thr_s1(){
	return get_csr_bits(REG_INFO.sigdet_thr_s1());	//CSR60[10:0]
}

uint
DS_rxRegs::getsigdet_los(){
	return get_csr_bits(REG_INFO.sigdet_los());	//CSR61[15:15]
}

DS_rxRegs&
DS_rxRegs::setsscdr_rst_by_sigdet(uint val){
	fill_csr_bits(val,REG_INFO.sscdr_rst_by_sigdet());	//CSR61[14:14]
	return *this;
}
uint
DS_rxRegs::getsscdr_rst_by_sigdet(){
	return get_csr_bits(REG_INFO.sscdr_rst_by_sigdet());	//CSR61[14:14]
}

DS_rxRegs&
DS_rxRegs::setremotetx(uint val){
	fill_csr_bits(val,REG_INFO.remotetx());	//CSR61[13:13]
	return *this;
}
uint
DS_rxRegs::getremotetx(){
	return get_csr_bits(REG_INFO.remotetx());	//CSR61[13:13]
}

uint
DS_rxRegs::getsquelch_det(){
	return get_csr_bits(REG_INFO.squelch_det());	//CSR61[12:12]
}

DS_rxRegs&
DS_rxRegs::setsigdet_rstb(uint val){
	fill_csr_bits(val,REG_INFO.sigdet_rstb());	//CSR61[11:11]
	return *this;
}
uint
DS_rxRegs::getsigdet_rstb(){
	return get_csr_bits(REG_INFO.sigdet_rstb());	//CSR61[11:11]
}

DS_rxRegs&
DS_rxRegs::setsigdet_thr_s2(uint val){
	fill_csr_bits(val,REG_INFO.sigdet_thr_s2());	//CSR61[10:0]
	return *this;
}
uint
DS_rxRegs::getsigdet_thr_s2(){
	return get_csr_bits(REG_INFO.sigdet_thr_s2());	//CSR61[10:0]
}

DS_rxRegs&
DS_rxRegs::setpat_det_win(uint val){
	fill_csr_bits(val,REG_INFO.pat_det_win());	//CSR62[15:14]
	return *this;
}
uint
DS_rxRegs::getpat_det_win(){
	return get_csr_bits(REG_INFO.pat_det_win());	//CSR62[15:14]
}

uint
DS_rxRegs::getsscdr_cmphase(){
	return get_csr_bits(REG_INFO.sscdr_cmphase());	//CSR62[13:8]
}

DS_rxRegs&
DS_rxRegs::setemphase_delta(uint val){
	fill_csr_bits(val,REG_INFO.emphase_delta());	//CSR62[7:0]
	return *this;
}
uint
DS_rxRegs::getemphase_delta(){
	return get_csr_bits(REG_INFO.emphase_delta());	//CSR62[7:0]
}

