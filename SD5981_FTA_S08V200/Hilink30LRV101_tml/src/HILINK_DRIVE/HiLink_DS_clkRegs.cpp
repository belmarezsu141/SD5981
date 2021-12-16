#include <HILINK_DRIVE/HiLink_DS_clkRegs.h>

#include <iostream>
using namespace std;
DS_clkRegs::DS_clkRegs() {
	// TODO Auto-generated constructor stub
	for(int i=0;i<DS_CLK_CSR_NUM;i++){
		csr[i]=0;
	}
	sliceID=0;
	macroID=0;
	broadcast=false;
	reset_csr_verify();
}

DS_clkRegs::~DS_clkRegs() {}

bool
DS_clkRegs::get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos){
	if(csrIndex>=DS_CLK_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	return REG_INFO.get_reg_infos(csrIndex,reg_infos);
}

DS_clkRegs&
DS_clkRegs::getInstance(){
	static DS_clkRegs theInstance;
	return theInstance;
}

uint
DS_clkRegs::get_HILINK_MAX_LANE_NUM(){
	//TODO: add your code for CSR Address mapping
	return HILINK_LANE_NUM;
}

uint
DS_clkRegs::getAddressMapToHiLink(int csrIndex){
	if(csrIndex>=DS_CLK_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	//TODO: add your code for CSR Address mapping
	return (uint)(0x4000 | (broadcast << 13) | (sliceID << 9) | ((uint)0x2<< 7) | csrIndex << 1);
}


uint&
DS_clkRegs::get_csr(uint csrIndex){
	if(csrIndex>=DS_CLK_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
//		ERROR_EXIT(TM::ABORT_FLOW);
	}
	return csr[csrIndex];
}

void
DS_clkRegs::get_default_MacroLaneID(T_MacroLaneID& id){
	//TODO: add your code for CSR Address mapping
	id.MacroID=macroID;
	id.LaneID=sliceID;
}

uint
DS_clkRegs::getCSRCount(){
	return DS_CLK_CSR_NUM;
}

string
DS_clkRegs::getName(){
	return "DS_CLK";
}

///////////////////////////////////////////////////////////////////////////


	/// Dataslice power sequence control 
	/// 0 = Power down entire DS  sequentially
	/// 1 = Power up entire DS  sequentially
	/// 
	/// Note: New  in v101.  Used as a trigger to  sequentially power up the entire Dataslice with default settings
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dspwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{0,"dspwrdb",15,15}
	};
	return reg;
}

	/// Select high-speed clock spine ( for both RX and TX )
	/// 0 = Select clock spine 0
	/// 1 = Select clock spine 1
	/// (Independent RX and TX selection no longer supported in v101)
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::clkspinesel(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{0,"clkspinesel",14,14}
	};
	return reg;
}

	/// Resets ds power sequence. Active low.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dspwrsqsoftrstb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{0,"dspwrsqsoftrstb",12,12}
	};
	return reg;
}

	/// DS power sequence time between steps for regulators (TBS2)
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dspwrsqtbs2(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{0,"dspwrsqtbs2",11,8}
	};
	return reg;
}

	/// Power Sequencing status
	/// 0 =  sequence not done/incomplete
	/// 1 =  sequence complete
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dspwrsqdone(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{0,"dspwrsqdone",7,7}
	};
	return reg;
}

	/// DS power sequence time between steps (TBS)
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dspwrsqtbs(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{0,"dspwrsqtbs",6,4}
	};
	return reg;
}

	/// Dsclk spine clock 0 distribution power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::buf0pwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{0,"buf0pwrdb",3,3}
	};
	return reg;
}

	/// Dsclk spine clock 1 distribution power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::buf1pwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{0,"buf1pwrdb",2,2}
	};
	return reg;
}

	/// New in V101: Power sequence mode selector. 
	/// 00 =  This is the default  power sequence mode to be used.   Power up/down sequence follows required steps and value from registers.
	/// 01: Power sequence follows preset values (Test purposes only).
	/// 10: Power sequence is bypassed (old V100 mode).  
	/// 11: Not used
	/// Note:  Do not change PWRSQMODE once the Dataslice is powered up or in use.  Disruption may result.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::pwrsqmode(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{0,"pwrsqmode",1,0}
	};
	return reg;
}

	/// Dsclk RX PI voltage reference bias power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::clkgenbiaspwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"clkgenbiaspwrdb",15,15}
	};
	return reg;
}

	/// Dsclk regulator power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::clkgenvregpwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"clkgenvregpwrdb",14,14}
	};
	return reg;
}

	/// Dsclk  spine clock mux quadrature divider power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
	/// New in v101: Used as a Trigger to sequentially power up/down DSLK circuitry (both to RX and TX)  with default settings
	/// (register name in v100 was RXQDIV2PWRDB)
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::qdiv2pwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"qdiv2pwrdb",13,13}
	};
	return reg;
}

	/// spare not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::txcmlpwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"txcmlpwrdb",12,12}
	};
	return reg;
}

	/// Dsclk TX  pi power down control. Active low.
	/// 0 = Power Down
	/// 1= Power up
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::txcmospipwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"txcmospipwrdb",11,11}
	};
	return reg;
}

	/// DSCLK regulator inrush current limit DPM trimming.
	/// 0 = select voltage reference for SS corner
	/// 1 = select voltage reference for TT/FF corner
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vregdpmen(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"vregdpmen",6,6}
	};
	return reg;
}

	/// Dsclk regulator bleed current control.
	/// 0 = enable bleed current
	/// 1 = disable bleed current
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vregbleedb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"vregbleedb",5,5}
	};
	return reg;
}

	/// Voltage level control of dsclk regulator. (default =0.923v)
	/// 00000 = Minimum voltage.
	/// 00001
	/// 00010
	/// ..
	/// 10100=voltage(default)
	/// ?.
	/// 11111 = Maximum voltage.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vreglvl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"vreglvl",4,0}
	};
	return reg;
}

	/// DSCLK regulator inrush current limit. Active low.
	/// 0: regulator inrush current limit  mode
	/// 1: regulator mission mode
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::clkvreginrushpwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{2,"clkvreginrushpwrdb",15,15}
	};
	return reg;
}

	/// Dsclk PI driver select ref for loading resistance determination. 
	/// 000: min loading resistance -- 10G application
	/// 011:                                                 -- 32G application
	/// 111: max loading resistance
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::reprefsel(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{2,"reprefsel",14,12}
	};
	return reg;
}

	/// reference range select for dsclk regulator
	/// 00:  vref between 750mV  and  850mV
	/// 01: vref  between 851mV and 925mV
	/// 10: vref between 926mV and 985mV
	/// 11: vref between 986mV and 1050mV
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::clkvregvrefrng(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{2,"clkvregvrefrng",11,10}
	};
	return reg;
}

	/// RX PI DPM based drive strength adjust to CC divider
	///      11- min current drive to PI
	///      00- max current drive to PI (30G default)
	/// TT/FF  value should be 2'b11(30G)
	/// SS value should be 2'b01(30G)
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::clkrxdpm(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{2,"clkrxdpm",9,8}
	};
	return reg;
}

	/// Dsclk PI drivers input common mode voltage control. 
	/// 00 = Minimum input common mode voltage.
	/// 01
	/// 10
	/// 11 = Maximum input common mode voltage.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vrefsel(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{2,"vrefsel",7,6}
	};
	return reg;
}

	/// TX PI DPM based drive strength adjust to CC divider
	///      11- min current drive to PI
	///      00- max current drive to PI
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::clktxccdivdpm(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{2,"clktxccdivdpm",5,4}
	};
	return reg;
}

	/// Dsclk TX Div2 I/Q output capacitance loading control.     
	///      x00- min cap load; 30G (default)
	///       ...
	///     x11- max cap load
	/// i.e. bit [2] not assigned
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::clktxcaploadtrim(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{2,"clktxcaploadtrim",3,1}
	};
	return reg;
}

	/// 0- TX pi-predistortion disabled
	/// 1- TX pi-predistortion enabled
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::clktxpipredistpwrdnb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{2,"clktxpipredistpwrdnb",0,0}
	};
	return reg;
}

	/// Dsclk spine clock mux output capacitance loading control. Binary coded.
	/// 00 = Min capacitance loading ( setting for 32G app)
	/// 01 =     (setting for 10G app)          
	/// 10
	/// 11 = Max  capacitance loading
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::muxcshuntctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{3,"muxcshuntctrl",12,11}
	};
	return reg;
}

	/// Dsclk RX Div2 I/Q output capacitance loading control.
	/// Binary weighted caps.
	/// 000: min cap loading  (setting for 32G application)
	///  ...
	/// 111: max cap loading  (setting for 10G application)
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::caploadtrim(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{3,"caploadtrim",10,8}
	};
	return reg;
}

	/// Dsclk RX CML PI driver AC coupling capacitance selection. 
	/// 00: min cap loading  (setting for 32G application)
	/// 01:                                 (setting for 10G application)
	/// 10:
	/// 11: max cap loading
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::pidrvhpftcaptrim(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{3,"pidrvhpftcaptrim",6,5}
	};
	return reg;
}

	/// DSCK spare bits (restored back as spare from v100)
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkspare(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{3,"dsclkspare",4,0}
	};
	return reg;
}

	/// Dsclk ATB control. Selected signal will go to dsclk_atb_out.
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = Select vref of Rx PI driver output
	/// 010 = High Impedance
	/// 011 = Select dsclk_pi_vref
	/// 100 = High Impedance
	/// 101 = Select dsclk 3/4 vreg local sense
	/// 110 = High Impedance
	/// 111 = High Impedance
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclktopatbctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{4,"dsclktopatbctrl",15,13}
	};
	return reg;
}

	/// Dsclk regulator ATB control. Selected signal will go to hv_txtop_atb_out.
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = select vref
	/// 010 = select vlow 
	/// 011 = High Impedance
	/// 100 = High Impedance
	/// 101 = select vmid
	/// 110 = select dsclk 2/3 sense voltage
	/// 111 = High Impedance
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vregatbctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{4,"vregatbctrl",12,10}
	};
	return reg;
}

	/// TX PI bias current scale
	///    00: max current
	///    11: min current
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::clktxpibiastrim(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{4,"clktxpibiastrim",9,8}
	};
	return reg;
}

	/// Spare not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::clktxbibufbiastrim(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{4,"clktxbibufbiastrim",7,6}
	};
	return reg;
}

	/// spare not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::clktxpibufloadtrim(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{4,"clktxpibufloadtrim",5,4}
	};
	return reg;
}

	/// spare not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::clktxpidrvloadctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{4,"clktxpidrvloadctrl",3,2}
	};
	return reg;
}

	/// Dsclk TXPI CML bias control control.
	/// 0: use PI default bias
	/// 1:  boost PI bias by 50uA (default for 30 G)
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::clktxpibiascoarsetrim(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{4,"clktxpibiascoarsetrim",1,1}
	};
	return reg;
}

	/// Dataslice bias receiver power down control. Active low.
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsbiasrcvrpwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{5,"dsbiasrcvrpwrdb",15,15}
	};
	return reg;
}

	/// ADC (in DataSlice) power down control.
	/// 0: Power down
	/// 1: Power up
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsadcpwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{5,"dsadcpwrdb",14,14}
	};
	return reg;
}

	/// Comparator(in DataSlice) power down control. Active low.
	/// 0 = Power down calcomp.
	/// 1 = Power up calcomp.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dscalcomppwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{5,"dscalcomppwrdb",13,13}
	};
	return reg;
}

	/// Calibration comparator (in DataSlice) power down control. Active low.
	/// 0 = Power down.
	/// 1 = Power up.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dscalcompvrefpwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{5,"dscalcompvrefpwrdb",12,12}
	};
	return reg;
}

	/// not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dscalcompvrefrng(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{5,"dscalcompvrefrng",11,10}
	};
	return reg;
}

	/// Dataslice bias receivers commn-mode rejection control.
	/// 0: H30 Experimental mode (not recommended)
	/// 1: Mission mode
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsbiasrcvrselcm(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{5,"dsbiasrcvrselcm",9,9}
	};
	return reg;
}

	/// Dataslice bias receivers test mode enable control. 
	/// 0 = Mission mode (using differential bias voltage)
	/// 1 = Enable test mode (self bias)
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsbiasrcvrtsten(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{5,"dsbiasrcvrtsten",8,8}
	};
	return reg;
}

	/// 00: initial calibration using comparator, start from hard-coded default values
	/// 01: update calibration using comparator, start from current value
	/// 10: initial calibration using ADC, start from hard-coded default values (NOT SUPPORTED)
	/// 11: update calibration using ADC, start from current value (NOT SUPPORTED)
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dscalmode(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{5,"dscalmode",7,6}
	};
	return reg;
}

	/// ADC decimation filter ready
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsadcdfrdy(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{5,"dsadcdfrdy",5,5}
	};
	return reg;
}

	/// ADC timer divider ratio - Optional divider used in determining ADC settling delay.   Also refer to DSADCTIMER[1:0] .
	/// 0= bypass additional divider
	/// 1= enable additional divider
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsadctimerdiv(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{5,"dsadctimerdiv",4,4}
	};
	return reg;
}

	/// ADC timer value - From ADC start, enforced settling delay before ADC beings sampling.  Also refer  to DSADCTIMERDIV.
	/// For DSADCTIMERDIV= 0 
	/// 00:      5 ADC clock cycles (1.56us @ 3.2MHz)
	/// 01:    37 ADC clock cycles (11.6us @ 3.2MHz)
	/// 10:    85 ADC clock cycles (26.6us @ 3.2MHz)
	/// 11:  165 ADC clock cycles (51.6us @ 3.2MHz)
	/// 
	/// For DSADCTIMERDIV= 1 
	/// 00:   6 ADC clock cycles   (1.87us     @ 3.2MHz)
	/// 01: 70 ADC clock cycles   (21.87us  @ 3.2MHz)
	/// 10: 166 ADC clock cycles (51.87us  @ 3.2MHz)
	/// 11: 326 ADC clock cycles (101.87us@ 3.2MHz)
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsadctimer(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{5,"dsadctimer",3,2}
	};
	return reg;
}

	/// adc deadband select
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsadcdeadbandsel(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{5,"dsadcdeadbandsel",1,0}
	};
	return reg;
}

	/// ADC(in DataSlice) reset. Active low.
	/// 0 = Reset
	/// 1 = Normal operation mode
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsadcrstb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{6,"dsadcrstb",15,15}
	};
	return reg;
}

	/// ADC (in DataSlice)absolute measurement mode enable control.
	/// 0 = Relative measurement mode (using hvcc as reference)
	/// 1 = Absolute measurement mode (using vref_bg as reference)
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsadcabsmeasen(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{6,"dsadcabsmeasen",14,14}
	};
	return reg;
}

	/// ADC test mode (in DataSlice)enable control.
	/// 0 = Normal operation mode
	/// 1 = Enable test mode (connect ADC input to Vcm)
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsadctsten(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{6,"dsadctsten",13,13}
	};
	return reg;
}

	/// Internal common mode voltage control for opamp and comparator reference(in DataSlice).
	/// 00 = 10/24 * hvcc
	/// ;01 = 11/24 * hvcc
	/// ;10 = 12/24 * hvcc
	/// ;11 = 13/24 * hvcc.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsadcvcmctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{6,"dsadcvcmctrl",12,11}
	};
	return reg;
}

	/// Status of dataslice analog comparator out value
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dscalcompout(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{6,"dscalcompout",10,10}
	};
	return reg;
}

	/// Comparator operating mode selection.
	/// 0 = Single-end mode (compare vinp with vref)
	/// 1 = Differential mode (compare vinp and vinm)
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dscalcompmodesel(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{6,"dscalcompmodesel",9,9}
	};
	return reg;
}

	/// Select OTB/AB input of calibration comparator.
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = Select Rx otbp / otbm
	/// 010 = Select Tx otbp / otbm
	/// 011 = Select Tx2rx loopback otbp / otbm
	/// 100 = Select Tx atb
	/// 101 = Select Dsclk atb
	/// 110 = Select hvcc
	/// 111 = Select vss
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dscalcompotbctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{6,"dscalcompotbctrl",8,6}
	};
	return reg;
}

	/// Set Reference voltage selection for calibration comparator (default=637.5mV) used for TX drv and predrv regulator calibration, RX clock and Data  regulator calibration, DSCLK regulator calibration.  Access valid only if TXCALMODE, RXCALMODE, DSCLKCALIBMODE is set to manual.
	/// 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 111111 =  Vref=800mV
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dscalcompvrefsel(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{6,"dscalcompvrefsel",5,0}
	};
	return reg;
}

	/// Dataslice top level ATB output enable.
	/// 0 = Disable dataslice top level ATB output.
	/// 1 = Enable dataslice top lelvel ATB output.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dstoplvlatbouten(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{7,"dstoplvlatbouten",15,15}
	};
	return reg;
}

	/// Dataslice top level ATB control.
	/// 0000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 0001 = Select RX top ATB output
	/// 0010 = Select Tx top ATB output
	/// 0011 = Select Dsclk top ATB outputput
	/// 0100 = Select Tx to Rx loopback ATB output
	/// 0101 = Select bias receivers ATB output
	/// 0110 = Select calibration comparator ATB output
	/// 0111 = Select hvcc
	/// 1000 = select comp vref
	/// 1001 = Select RX otbp
	/// 1010 = Select RX otbm
	/// 1011 = Select TX otbp
	/// 1100 = Select TX otbm
	/// 1101 = Select Tx to Rx loopback otbp
	/// 1110 = Select Tx to Rx loopback otbm
	/// 1111 = Select vss
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dstopatbctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{7,"dstopatbctrl",14,11}
	};
	return reg;
}

	/// Dataslice bias receiver ATB selection.
	/// 00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 = Select icvp 50uA current.
	/// 10 = Select iccp 50uA current.
	/// 11 = Select iptat_50uA current
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsbiasrcvratbctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{7,"dsbiasrcvratbctrl",4,3}
	};
	return reg;
}

	/// ATB selection for calibration comparator.
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = Select vcmref
	/// 010 = Select vout_opamp
	/// 011 = Select vref
	/// 100 = Select vinp
	/// 101 = Select vinm/vref
	/// vinm @ ds_calcomp_mode_sel = 1
	/// vref @ ds_calcomp_mode_sel = 0
	/// 110 to 111 = Invalid settings
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dscalcompatbctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{7,"dscalcompatbctrl",2,0}
	};
	return reg;
}

	/// 0 = calibration is based on analog comparator output
	/// 1 = calibration is based on ADC output
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsadccompsel(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{8,"dsadccompsel",15,15}
	};
	return reg;
}

	/// ADC and Comparator clock pre stage divider ratio.  Sets [DSADCCOMPCLKPREDIV+1] as the divide ratio that is performed on the hclk.   Ie, 
	/// hclk / [DSADCCOMPCLKPREDIV+1]
	/// This clock is then further divided by two different dividers, one to provide the clock for the ADC and one to provide the clock for the comparator.  See  DSADCCLKDIV and  DSCOMPCLKDIV for more information
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsadccompclkprediv(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{8,"dsadccompclkprediv",14,8}
	};
	return reg;
}

	/// divider ratio to generate adc clock after the pre stage divider. (See also DSADCCOMPCLKPREDIV)
	/// 000 = div by 256
	/// 001 = div by 128
	/// 010 = div by 64
	/// 011 = div by 32
	/// 100 = div by 16
	/// 101 = div by 8
	/// 110 = div by 4
	/// 111 = div by 2
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsadcclkdiv(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{8,"dsadcclkdiv",7,5}
	};
	return reg;
}

	/// divider ratio to generate comparator clock after the pre stage divider.(See also DSADCCOMPCLKPREDIV)
	/// 000 = div by 512
	/// 001 = div by 256
	/// 010 = div by 128
	/// 011 = div by 64
	/// 100 = div by 32
	/// 101 = div by 16
	/// 110 = div by 8
	/// 111 = div by 4
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dscompclkdiv(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{8,"dscompclkdiv",4,2}
	};
	return reg;
}

	/// adc decimation filter mode
	/// 00 = single sho mode
	/// 01 = continuous mode
	/// 10 and 11 = not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsadcconvmode(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{8,"dsadcconvmode",1,0}
	};
	return reg;
}

	/// decimation factor selection
	/// 00 = 256
	/// 01 = 512
	/// 10 = 1024
	/// 11 = 2048
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsdecmfactor(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{9,"dsdecmfactor",15,14}
	};
	return reg;
}

	/// decimation filter order
	/// x0 = sync 1
	/// x1 = sync 2
	/// (bit #1 not used)
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsdforder(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{9,"dsdforder",13,12}
	};
	return reg;
}

	/// decimation filter reference value
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsdfrefcode(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{9,"dsdfrefcode",11,0}
	};
	return reg;
}

	/// Not implemented. Use DSADCDFRDY instead.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsdfrdy(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{10,"dsdfrdy",15,15}
	};
	return reg;
}

	/// status of decimation filter comparator
	/// 0 = decimation data below reference level
	/// 1 = decimation data above reference level
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsdfcompstatus(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{10,"dsdfcompstatus",14,14}
	};
	return reg;
}

	/// status of decimation filter data
	/// ABOVE decimation filter
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsdfdata(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{10,"dsdfdata",11,0}
	};
	return reg;
}

	/// 0 = auto
	/// 1 = manual
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkcalibmode(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{11,"dsclkcalibmode",15,15}
	};
	return reg;
}

	/// DSCLK calibration start control.
	/// 0 = Do not start DSCLK calibration
	/// ;1 = Start DSCLK calibration. Self clear after calibration is done.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkcalibstart(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{11,"dsclkcalibstart",14,14}
	};
	return reg;
}

	/// dsclk calibration block soft reset; active low
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkcalibsoftrstb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{11,"dsclkcalibsoftrstb",13,13}
	};
	return reg;
}

	/// dsclk calibration comparator direction control
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkcalibdir(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{11,"dsclkcalibdir",12,12}
	};
	return reg;
}

	/// Set Comparator reference voltage  for DSCLK voltage regulator calibration.   
	/// Calib Target (mV)= 600 * (1+dsclkcalibregrefsel/64)
	/// Note: CLKVREGVREFRNG[1:0] must be correspondingly set to a range which supports the calibration target voltage.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkcalibregrefsel(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{11,"dsclkcalibregrefsel",5,0}
	};
	return reg;
}

	/// Configuration of timer for waiting, which is the cycles of reference clock. Timer value = (2powDSCLKCALTIMERVALUE) -1 , where DSCLKCALTIMERVALUE =0 to 22.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkcaltimervalue(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{12,"dsclkcaltimervalue",14,5}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkcaltimerdivvalue(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{12,"dsclkcaltimerdivvalue",4,2}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkcaltimerdiven(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{12,"dsclkcaltimerdiven",1,1}
	};
	return reg;
}

	/// Stop timer, for debugging.
	/// 0 = normal
	/// 1 = stop the timer
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkcaltimerstop(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{12,"dsclkcaltimerstop",0,0}
	};
	return reg;
}

	/// Recovered clock divide ratio
	/// output frequency= rx_center_wordclk / (RXRECCLKFBDIV + 1)
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::rxrecclkfbdiv(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{13,"rxrecclkfbdiv",15,10}
	};
	return reg;
}

	/// recovered clock powerdown. active low
	/// 0 =  powerdown
	/// 1 =  enable
	/// NOTE: PER MACRO, ONLY 1 DS MAY ENABLE
	/// RECOVERED CLOCK FEATURE AT A TIME
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::rxrecclkpwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{13,"rxrecclkpwrdb",9,9}
	};
	return reg;
}

	/// TX I-PI static fine delay adjust
	/// 00 =  min delay
	/// 11 =   max delay
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclktxdlyctrli(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{13,"dsclktxdlyctrli",5,4}
	};
	return reg;
}

	/// TX Q-PI static fine delay adjust
	/// 00 =  min delay
	/// 11 =   max delay
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclktxdlyctrlq(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{13,"dsclktxdlyctrlq",3,2}
	};
	return reg;
}

	/// TX I-PI DPM for static fine delay adjust
	/// 0 =  nominal delay (30G -- default)
	/// 1 =  increase delay
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclktxidpm(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{13,"dsclktxidpm",1,1}
	};
	return reg;
}

	/// TX Q-PI DPM for static fine delay adjust
	/// 0 =  nominal delay (30G -- default)
	/// 1 =  increase delay
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclktxqdpm(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{13,"dsclktxqdpm",0,0}
	};
	return reg;
}

	/// 01= bypass vrefgen calibration
	/// 10= bypass dsclk regulator calibration
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkcalbypass(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{14,"dsclkcalbypass",15,14}
	};
	return reg;
}

	/// Vrefgen calibarted code 16
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vrefgenrefcode16(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{14,"vrefgenrefcode16",13,8}
	};
	return reg;
}

	/// Bypass vrefgen interpolation adjustment function
	/// 0 using vrefgen interpolation
	/// 1 bypass vrefgen interpolation
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vrefgenintrpbp(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{14,"vrefgenintrpbp",7,7}
	};
	return reg;
}

	/// vrefgen calibration direction
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vrefgencaldir(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{14,"vrefgencaldir",6,6}
	};
	return reg;
}

	/// Vrefgen calibarted code 26
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vrefgenrefcode26(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{14,"vrefgenrefcode26",5,0}
	};
	return reg;
}

	/// 0 =  vref gen calibrate bandgap
	/// 1 =  vref gen calibrate hvcc
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vrefgenbgsel(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{15,"vrefgenbgsel",14,14}
	};
	return reg;
}

	/// Vrefgen calibarted code 38
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vrefgenrefcode38(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{15,"vrefgenrefcode38",13,8}
	};
	return reg;
}

	/// Vrefgen calibarted code 48
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vrefgenrefcode48(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{15,"vrefgenrefcode48",5,0}
	};
	return reg;
}

	/// vrefgen offset value at 16
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vrefgenofst16(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{16,"vrefgenofst16",15,8}
	};
	return reg;
}

	/// vrefgen offset value at 26
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vrefgenofst26(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{16,"vrefgenofst26",7,0}
	};
	return reg;
}

	/// vrefgen offset value at 38
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vrefgenofst38(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{17,"vrefgenofst38",15,8}
	};
	return reg;
}

	/// vrefgen offset value at 48
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vrefgenofst48(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{17,"vrefgenofst48",7,0}
	};
	return reg;
}

	/// Vrefgen initial value for code 16 calibration
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vrefgenrefintl16(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{18,"vrefgenrefintl16",13,8}
	};
	return reg;
}

	/// Vrefgen initial value for code 26 calibration
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vrefgenrefintl26(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{18,"vrefgenrefintl26",5,0}
	};
	return reg;
}

	/// Vrefgen initial value for code 38 calibration
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vrefgenrefintl38(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{19,"vrefgenrefintl38",13,8}
	};
	return reg;
}

	/// Vrefgen initial value for code 48 calibration
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vrefgenrefintl48(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{19,"vrefgenrefintl48",5,0}
	};
	return reg;
}
bool
DS_clkRegs::_REG_INFO::get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos){
	reg_infos.clear();
	switch(csr){
		case 0:
			reg_infos.push_back(dspwrdb().reg_info);
			reg_infos.push_back(clkspinesel().reg_info);
			reg_infos.push_back(dspwrsqsoftrstb().reg_info);
			reg_infos.push_back(dspwrsqtbs2().reg_info);
			reg_infos.push_back(dspwrsqdone().reg_info);
			reg_infos.push_back(dspwrsqtbs().reg_info);
			reg_infos.push_back(buf0pwrdb().reg_info);
			reg_infos.push_back(buf1pwrdb().reg_info);
			reg_infos.push_back(pwrsqmode().reg_info);
			break;
		case 1:
			reg_infos.push_back(clkgenbiaspwrdb().reg_info);
			reg_infos.push_back(clkgenvregpwrdb().reg_info);
			reg_infos.push_back(qdiv2pwrdb().reg_info);
			reg_infos.push_back(txcmlpwrdb().reg_info);
			reg_infos.push_back(txcmospipwrdb().reg_info);
			reg_infos.push_back(vregdpmen().reg_info);
			reg_infos.push_back(vregbleedb().reg_info);
			reg_infos.push_back(vreglvl().reg_info);
			break;
		case 2:
			reg_infos.push_back(clkvreginrushpwrdb().reg_info);
			reg_infos.push_back(reprefsel().reg_info);
			reg_infos.push_back(clkvregvrefrng().reg_info);
			reg_infos.push_back(clkrxdpm().reg_info);
			reg_infos.push_back(vrefsel().reg_info);
			reg_infos.push_back(clktxccdivdpm().reg_info);
			reg_infos.push_back(clktxcaploadtrim().reg_info);
			reg_infos.push_back(clktxpipredistpwrdnb().reg_info);
			break;
		case 3:
			reg_infos.push_back(muxcshuntctrl().reg_info);
			reg_infos.push_back(caploadtrim().reg_info);
			reg_infos.push_back(pidrvhpftcaptrim().reg_info);
			reg_infos.push_back(dsclkspare().reg_info);
			break;
		case 4:
			reg_infos.push_back(dsclktopatbctrl().reg_info);
			reg_infos.push_back(vregatbctrl().reg_info);
			reg_infos.push_back(clktxpibiastrim().reg_info);
			reg_infos.push_back(clktxbibufbiastrim().reg_info);
			reg_infos.push_back(clktxpibufloadtrim().reg_info);
			reg_infos.push_back(clktxpidrvloadctrl().reg_info);
			reg_infos.push_back(clktxpibiascoarsetrim().reg_info);
			break;
		case 5:
			reg_infos.push_back(dsbiasrcvrpwrdb().reg_info);
			reg_infos.push_back(dsadcpwrdb().reg_info);
			reg_infos.push_back(dscalcomppwrdb().reg_info);
			reg_infos.push_back(dscalcompvrefpwrdb().reg_info);
			reg_infos.push_back(dscalcompvrefrng().reg_info);
			reg_infos.push_back(dsbiasrcvrselcm().reg_info);
			reg_infos.push_back(dsbiasrcvrtsten().reg_info);
			reg_infos.push_back(dscalmode().reg_info);
			reg_infos.push_back(dsadcdfrdy().reg_info);
			reg_infos.push_back(dsadctimerdiv().reg_info);
			reg_infos.push_back(dsadctimer().reg_info);
			reg_infos.push_back(dsadcdeadbandsel().reg_info);
			break;
		case 6:
			reg_infos.push_back(dsadcrstb().reg_info);
			reg_infos.push_back(dsadcabsmeasen().reg_info);
			reg_infos.push_back(dsadctsten().reg_info);
			reg_infos.push_back(dsadcvcmctrl().reg_info);
			reg_infos.push_back(dscalcompout().reg_info);
			reg_infos.push_back(dscalcompmodesel().reg_info);
			reg_infos.push_back(dscalcompotbctrl().reg_info);
			reg_infos.push_back(dscalcompvrefsel().reg_info);
			break;
		case 7:
			reg_infos.push_back(dstoplvlatbouten().reg_info);
			reg_infos.push_back(dstopatbctrl().reg_info);
			reg_infos.push_back(dsbiasrcvratbctrl().reg_info);
			reg_infos.push_back(dscalcompatbctrl().reg_info);
			break;
		case 8:
			reg_infos.push_back(dsadccompsel().reg_info);
			reg_infos.push_back(dsadccompclkprediv().reg_info);
			reg_infos.push_back(dsadcclkdiv().reg_info);
			reg_infos.push_back(dscompclkdiv().reg_info);
			reg_infos.push_back(dsadcconvmode().reg_info);
			break;
		case 9:
			reg_infos.push_back(dsdecmfactor().reg_info);
			reg_infos.push_back(dsdforder().reg_info);
			reg_infos.push_back(dsdfrefcode().reg_info);
			break;
		case 10:
			reg_infos.push_back(dsdfrdy().reg_info);
			reg_infos.push_back(dsdfcompstatus().reg_info);
			reg_infos.push_back(dsdfdata().reg_info);
			break;
		case 11:
			reg_infos.push_back(dsclkcalibmode().reg_info);
			reg_infos.push_back(dsclkcalibstart().reg_info);
			reg_infos.push_back(dsclkcalibsoftrstb().reg_info);
			reg_infos.push_back(dsclkcalibdir().reg_info);
			reg_infos.push_back(dsclkcalibregrefsel().reg_info);
			break;
		case 12:
			reg_infos.push_back(dsclkcaltimervalue().reg_info);
			reg_infos.push_back(dsclkcaltimerdivvalue().reg_info);
			reg_infos.push_back(dsclkcaltimerdiven().reg_info);
			reg_infos.push_back(dsclkcaltimerstop().reg_info);
			break;
		case 13:
			reg_infos.push_back(rxrecclkfbdiv().reg_info);
			reg_infos.push_back(rxrecclkpwrdb().reg_info);
			reg_infos.push_back(dsclktxdlyctrli().reg_info);
			reg_infos.push_back(dsclktxdlyctrlq().reg_info);
			reg_infos.push_back(dsclktxidpm().reg_info);
			reg_infos.push_back(dsclktxqdpm().reg_info);
			break;
		case 14:
			reg_infos.push_back(dsclkcalbypass().reg_info);
			reg_infos.push_back(vrefgenrefcode16().reg_info);
			reg_infos.push_back(vrefgenintrpbp().reg_info);
			reg_infos.push_back(vrefgencaldir().reg_info);
			reg_infos.push_back(vrefgenrefcode26().reg_info);
			break;
		case 15:
			reg_infos.push_back(vrefgenbgsel().reg_info);
			reg_infos.push_back(vrefgenrefcode38().reg_info);
			reg_infos.push_back(vrefgenrefcode48().reg_info);
			break;
		case 16:
			reg_infos.push_back(vrefgenofst16().reg_info);
			reg_infos.push_back(vrefgenofst26().reg_info);
			break;
		case 17:
			reg_infos.push_back(vrefgenofst38().reg_info);
			reg_infos.push_back(vrefgenofst48().reg_info);
			break;
		case 18:
			reg_infos.push_back(vrefgenrefintl16().reg_info);
			reg_infos.push_back(vrefgenrefintl26().reg_info);
			break;
		case 19:
			reg_infos.push_back(vrefgenrefintl38().reg_info);
			reg_infos.push_back(vrefgenrefintl48().reg_info);
			break;
		default:
			break;
	}
	return (reg_infos.size()>0);
}


DS_clkRegs&
DS_clkRegs::setdspwrdb(uint val){
	fill_csr_bits(val,REG_INFO.dspwrdb());	//CSR0[15:15]
	return *this;
}
uint
DS_clkRegs::getdspwrdb(){
	return get_csr_bits(REG_INFO.dspwrdb());	//CSR0[15:15]
}

DS_clkRegs&
DS_clkRegs::setclkspinesel(uint val){
	fill_csr_bits(val,REG_INFO.clkspinesel());	//CSR0[14:14]
	return *this;
}
uint
DS_clkRegs::getclkspinesel(){
	return get_csr_bits(REG_INFO.clkspinesel());	//CSR0[14:14]
}

DS_clkRegs&
DS_clkRegs::setdspwrsqsoftrstb(uint val){
	fill_csr_bits(val,REG_INFO.dspwrsqsoftrstb());	//CSR0[12:12]
	return *this;
}
uint
DS_clkRegs::getdspwrsqsoftrstb(){
	return get_csr_bits(REG_INFO.dspwrsqsoftrstb());	//CSR0[12:12]
}

DS_clkRegs&
DS_clkRegs::setdspwrsqtbs2(uint val){
	fill_csr_bits(val,REG_INFO.dspwrsqtbs2());	//CSR0[11:8]
	return *this;
}
uint
DS_clkRegs::getdspwrsqtbs2(){
	return get_csr_bits(REG_INFO.dspwrsqtbs2());	//CSR0[11:8]
}

uint
DS_clkRegs::getdspwrsqdone(){
	return get_csr_bits(REG_INFO.dspwrsqdone());	//CSR0[7:7]
}

DS_clkRegs&
DS_clkRegs::setdspwrsqtbs(uint val){
	fill_csr_bits(val,REG_INFO.dspwrsqtbs());	//CSR0[6:4]
	return *this;
}
uint
DS_clkRegs::getdspwrsqtbs(){
	return get_csr_bits(REG_INFO.dspwrsqtbs());	//CSR0[6:4]
}

DS_clkRegs&
DS_clkRegs::setbuf0pwrdb(uint val){
	fill_csr_bits(val,REG_INFO.buf0pwrdb());	//CSR0[3:3]
	return *this;
}
uint
DS_clkRegs::getbuf0pwrdb(){
	return get_csr_bits(REG_INFO.buf0pwrdb());	//CSR0[3:3]
}

DS_clkRegs&
DS_clkRegs::setbuf1pwrdb(uint val){
	fill_csr_bits(val,REG_INFO.buf1pwrdb());	//CSR0[2:2]
	return *this;
}
uint
DS_clkRegs::getbuf1pwrdb(){
	return get_csr_bits(REG_INFO.buf1pwrdb());	//CSR0[2:2]
}

DS_clkRegs&
DS_clkRegs::setpwrsqmode(uint val){
	fill_csr_bits(val,REG_INFO.pwrsqmode());	//CSR0[1:0]
	return *this;
}
uint
DS_clkRegs::getpwrsqmode(){
	return get_csr_bits(REG_INFO.pwrsqmode());	//CSR0[1:0]
}

DS_clkRegs&
DS_clkRegs::setclkgenbiaspwrdb(uint val){
	fill_csr_bits(val,REG_INFO.clkgenbiaspwrdb());	//CSR1[15:15]
	return *this;
}
uint
DS_clkRegs::getclkgenbiaspwrdb(){
	return get_csr_bits(REG_INFO.clkgenbiaspwrdb());	//CSR1[15:15]
}

DS_clkRegs&
DS_clkRegs::setclkgenvregpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.clkgenvregpwrdb());	//CSR1[14:14]
	return *this;
}
uint
DS_clkRegs::getclkgenvregpwrdb(){
	return get_csr_bits(REG_INFO.clkgenvregpwrdb());	//CSR1[14:14]
}

DS_clkRegs&
DS_clkRegs::setqdiv2pwrdb(uint val){
	fill_csr_bits(val,REG_INFO.qdiv2pwrdb());	//CSR1[13:13]
	return *this;
}
uint
DS_clkRegs::getqdiv2pwrdb(){
	return get_csr_bits(REG_INFO.qdiv2pwrdb());	//CSR1[13:13]
}

DS_clkRegs&
DS_clkRegs::settxcmlpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.txcmlpwrdb());	//CSR1[12:12]
	return *this;
}
uint
DS_clkRegs::gettxcmlpwrdb(){
	return get_csr_bits(REG_INFO.txcmlpwrdb());	//CSR1[12:12]
}

DS_clkRegs&
DS_clkRegs::settxcmospipwrdb(uint val){
	fill_csr_bits(val,REG_INFO.txcmospipwrdb());	//CSR1[11:11]
	return *this;
}
uint
DS_clkRegs::gettxcmospipwrdb(){
	return get_csr_bits(REG_INFO.txcmospipwrdb());	//CSR1[11:11]
}

DS_clkRegs&
DS_clkRegs::setvregdpmen(uint val){
	fill_csr_bits(val,REG_INFO.vregdpmen());	//CSR1[6:6]
	return *this;
}
uint
DS_clkRegs::getvregdpmen(){
	return get_csr_bits(REG_INFO.vregdpmen());	//CSR1[6:6]
}

DS_clkRegs&
DS_clkRegs::setvregbleedb(uint val){
	fill_csr_bits(val,REG_INFO.vregbleedb());	//CSR1[5:5]
	return *this;
}
uint
DS_clkRegs::getvregbleedb(){
	return get_csr_bits(REG_INFO.vregbleedb());	//CSR1[5:5]
}

DS_clkRegs&
DS_clkRegs::setvreglvl(uint val){
	fill_csr_bits(val,REG_INFO.vreglvl());	//CSR1[4:0]
	return *this;
}
uint
DS_clkRegs::getvreglvl(){
	return get_csr_bits(REG_INFO.vreglvl());	//CSR1[4:0]
}

DS_clkRegs&
DS_clkRegs::setclkvreginrushpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.clkvreginrushpwrdb());	//CSR2[15:15]
	return *this;
}
uint
DS_clkRegs::getclkvreginrushpwrdb(){
	return get_csr_bits(REG_INFO.clkvreginrushpwrdb());	//CSR2[15:15]
}

DS_clkRegs&
DS_clkRegs::setreprefsel(uint val){
	fill_csr_bits(val,REG_INFO.reprefsel());	//CSR2[14:12]
	return *this;
}
uint
DS_clkRegs::getreprefsel(){
	return get_csr_bits(REG_INFO.reprefsel());	//CSR2[14:12]
}

DS_clkRegs&
DS_clkRegs::setclkvregvrefrng(uint val){
	fill_csr_bits(val,REG_INFO.clkvregvrefrng());	//CSR2[11:10]
	return *this;
}
uint
DS_clkRegs::getclkvregvrefrng(){
	return get_csr_bits(REG_INFO.clkvregvrefrng());	//CSR2[11:10]
}

DS_clkRegs&
DS_clkRegs::setclkrxdpm(uint val){
	fill_csr_bits(val,REG_INFO.clkrxdpm());	//CSR2[9:8]
	return *this;
}
uint
DS_clkRegs::getclkrxdpm(){
	return get_csr_bits(REG_INFO.clkrxdpm());	//CSR2[9:8]
}

DS_clkRegs&
DS_clkRegs::setvrefsel(uint val){
	fill_csr_bits(val,REG_INFO.vrefsel());	//CSR2[7:6]
	return *this;
}
uint
DS_clkRegs::getvrefsel(){
	return get_csr_bits(REG_INFO.vrefsel());	//CSR2[7:6]
}

DS_clkRegs&
DS_clkRegs::setclktxccdivdpm(uint val){
	fill_csr_bits(val,REG_INFO.clktxccdivdpm());	//CSR2[5:4]
	return *this;
}
uint
DS_clkRegs::getclktxccdivdpm(){
	return get_csr_bits(REG_INFO.clktxccdivdpm());	//CSR2[5:4]
}

DS_clkRegs&
DS_clkRegs::setclktxcaploadtrim(uint val){
	fill_csr_bits(val,REG_INFO.clktxcaploadtrim());	//CSR2[3:1]
	return *this;
}
uint
DS_clkRegs::getclktxcaploadtrim(){
	return get_csr_bits(REG_INFO.clktxcaploadtrim());	//CSR2[3:1]
}

DS_clkRegs&
DS_clkRegs::setclktxpipredistpwrdnb(uint val){
	fill_csr_bits(val,REG_INFO.clktxpipredistpwrdnb());	//CSR2[0:0]
	return *this;
}
uint
DS_clkRegs::getclktxpipredistpwrdnb(){
	return get_csr_bits(REG_INFO.clktxpipredistpwrdnb());	//CSR2[0:0]
}

DS_clkRegs&
DS_clkRegs::setmuxcshuntctrl(uint val){
	fill_csr_bits(val,REG_INFO.muxcshuntctrl());	//CSR3[12:11]
	return *this;
}
uint
DS_clkRegs::getmuxcshuntctrl(){
	return get_csr_bits(REG_INFO.muxcshuntctrl());	//CSR3[12:11]
}

DS_clkRegs&
DS_clkRegs::setcaploadtrim(uint val){
	fill_csr_bits(val,REG_INFO.caploadtrim());	//CSR3[10:8]
	return *this;
}
uint
DS_clkRegs::getcaploadtrim(){
	return get_csr_bits(REG_INFO.caploadtrim());	//CSR3[10:8]
}

DS_clkRegs&
DS_clkRegs::setpidrvhpftcaptrim(uint val){
	fill_csr_bits(val,REG_INFO.pidrvhpftcaptrim());	//CSR3[6:5]
	return *this;
}
uint
DS_clkRegs::getpidrvhpftcaptrim(){
	return get_csr_bits(REG_INFO.pidrvhpftcaptrim());	//CSR3[6:5]
}

DS_clkRegs&
DS_clkRegs::setdsclkspare(uint val){
	fill_csr_bits(val,REG_INFO.dsclkspare());	//CSR3[4:0]
	return *this;
}
uint
DS_clkRegs::getdsclkspare(){
	return get_csr_bits(REG_INFO.dsclkspare());	//CSR3[4:0]
}

DS_clkRegs&
DS_clkRegs::setdsclktopatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.dsclktopatbctrl());	//CSR4[15:13]
	return *this;
}
uint
DS_clkRegs::getdsclktopatbctrl(){
	return get_csr_bits(REG_INFO.dsclktopatbctrl());	//CSR4[15:13]
}

DS_clkRegs&
DS_clkRegs::setvregatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.vregatbctrl());	//CSR4[12:10]
	return *this;
}
uint
DS_clkRegs::getvregatbctrl(){
	return get_csr_bits(REG_INFO.vregatbctrl());	//CSR4[12:10]
}

DS_clkRegs&
DS_clkRegs::setclktxpibiastrim(uint val){
	fill_csr_bits(val,REG_INFO.clktxpibiastrim());	//CSR4[9:8]
	return *this;
}
uint
DS_clkRegs::getclktxpibiastrim(){
	return get_csr_bits(REG_INFO.clktxpibiastrim());	//CSR4[9:8]
}

DS_clkRegs&
DS_clkRegs::setclktxbibufbiastrim(uint val){
	fill_csr_bits(val,REG_INFO.clktxbibufbiastrim());	//CSR4[7:6]
	return *this;
}
uint
DS_clkRegs::getclktxbibufbiastrim(){
	return get_csr_bits(REG_INFO.clktxbibufbiastrim());	//CSR4[7:6]
}

DS_clkRegs&
DS_clkRegs::setclktxpibufloadtrim(uint val){
	fill_csr_bits(val,REG_INFO.clktxpibufloadtrim());	//CSR4[5:4]
	return *this;
}
uint
DS_clkRegs::getclktxpibufloadtrim(){
	return get_csr_bits(REG_INFO.clktxpibufloadtrim());	//CSR4[5:4]
}

DS_clkRegs&
DS_clkRegs::setclktxpidrvloadctrl(uint val){
	fill_csr_bits(val,REG_INFO.clktxpidrvloadctrl());	//CSR4[3:2]
	return *this;
}
uint
DS_clkRegs::getclktxpidrvloadctrl(){
	return get_csr_bits(REG_INFO.clktxpidrvloadctrl());	//CSR4[3:2]
}

DS_clkRegs&
DS_clkRegs::setclktxpibiascoarsetrim(uint val){
	fill_csr_bits(val,REG_INFO.clktxpibiascoarsetrim());	//CSR4[1:1]
	return *this;
}
uint
DS_clkRegs::getclktxpibiascoarsetrim(){
	return get_csr_bits(REG_INFO.clktxpibiascoarsetrim());	//CSR4[1:1]
}

DS_clkRegs&
DS_clkRegs::setdsbiasrcvrpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.dsbiasrcvrpwrdb());	//CSR5[15:15]
	return *this;
}
uint
DS_clkRegs::getdsbiasrcvrpwrdb(){
	return get_csr_bits(REG_INFO.dsbiasrcvrpwrdb());	//CSR5[15:15]
}

DS_clkRegs&
DS_clkRegs::setdsadcpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.dsadcpwrdb());	//CSR5[14:14]
	return *this;
}
uint
DS_clkRegs::getdsadcpwrdb(){
	return get_csr_bits(REG_INFO.dsadcpwrdb());	//CSR5[14:14]
}

DS_clkRegs&
DS_clkRegs::setdscalcomppwrdb(uint val){
	fill_csr_bits(val,REG_INFO.dscalcomppwrdb());	//CSR5[13:13]
	return *this;
}
uint
DS_clkRegs::getdscalcomppwrdb(){
	return get_csr_bits(REG_INFO.dscalcomppwrdb());	//CSR5[13:13]
}

DS_clkRegs&
DS_clkRegs::setdscalcompvrefpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.dscalcompvrefpwrdb());	//CSR5[12:12]
	return *this;
}
uint
DS_clkRegs::getdscalcompvrefpwrdb(){
	return get_csr_bits(REG_INFO.dscalcompvrefpwrdb());	//CSR5[12:12]
}

DS_clkRegs&
DS_clkRegs::setdscalcompvrefrng(uint val){
	fill_csr_bits(val,REG_INFO.dscalcompvrefrng());	//CSR5[11:10]
	return *this;
}
uint
DS_clkRegs::getdscalcompvrefrng(){
	return get_csr_bits(REG_INFO.dscalcompvrefrng());	//CSR5[11:10]
}

DS_clkRegs&
DS_clkRegs::setdsbiasrcvrselcm(uint val){
	fill_csr_bits(val,REG_INFO.dsbiasrcvrselcm());	//CSR5[9:9]
	return *this;
}
uint
DS_clkRegs::getdsbiasrcvrselcm(){
	return get_csr_bits(REG_INFO.dsbiasrcvrselcm());	//CSR5[9:9]
}

DS_clkRegs&
DS_clkRegs::setdsbiasrcvrtsten(uint val){
	fill_csr_bits(val,REG_INFO.dsbiasrcvrtsten());	//CSR5[8:8]
	return *this;
}
uint
DS_clkRegs::getdsbiasrcvrtsten(){
	return get_csr_bits(REG_INFO.dsbiasrcvrtsten());	//CSR5[8:8]
}

DS_clkRegs&
DS_clkRegs::setdscalmode(uint val){
	fill_csr_bits(val,REG_INFO.dscalmode());	//CSR5[7:6]
	return *this;
}
uint
DS_clkRegs::getdscalmode(){
	return get_csr_bits(REG_INFO.dscalmode());	//CSR5[7:6]
}

uint
DS_clkRegs::getdsadcdfrdy(){
	return get_csr_bits(REG_INFO.dsadcdfrdy());	//CSR5[5:5]
}

DS_clkRegs&
DS_clkRegs::setdsadctimerdiv(uint val){
	fill_csr_bits(val,REG_INFO.dsadctimerdiv());	//CSR5[4:4]
	return *this;
}
uint
DS_clkRegs::getdsadctimerdiv(){
	return get_csr_bits(REG_INFO.dsadctimerdiv());	//CSR5[4:4]
}

DS_clkRegs&
DS_clkRegs::setdsadctimer(uint val){
	fill_csr_bits(val,REG_INFO.dsadctimer());	//CSR5[3:2]
	return *this;
}
uint
DS_clkRegs::getdsadctimer(){
	return get_csr_bits(REG_INFO.dsadctimer());	//CSR5[3:2]
}

DS_clkRegs&
DS_clkRegs::setdsadcdeadbandsel(uint val){
	fill_csr_bits(val,REG_INFO.dsadcdeadbandsel());	//CSR5[1:0]
	return *this;
}
uint
DS_clkRegs::getdsadcdeadbandsel(){
	return get_csr_bits(REG_INFO.dsadcdeadbandsel());	//CSR5[1:0]
}

DS_clkRegs&
DS_clkRegs::setdsadcrstb(uint val){
	fill_csr_bits(val,REG_INFO.dsadcrstb());	//CSR6[15:15]
	return *this;
}
uint
DS_clkRegs::getdsadcrstb(){
	return get_csr_bits(REG_INFO.dsadcrstb());	//CSR6[15:15]
}

DS_clkRegs&
DS_clkRegs::setdsadcabsmeasen(uint val){
	fill_csr_bits(val,REG_INFO.dsadcabsmeasen());	//CSR6[14:14]
	return *this;
}
uint
DS_clkRegs::getdsadcabsmeasen(){
	return get_csr_bits(REG_INFO.dsadcabsmeasen());	//CSR6[14:14]
}

DS_clkRegs&
DS_clkRegs::setdsadctsten(uint val){
	fill_csr_bits(val,REG_INFO.dsadctsten());	//CSR6[13:13]
	return *this;
}
uint
DS_clkRegs::getdsadctsten(){
	return get_csr_bits(REG_INFO.dsadctsten());	//CSR6[13:13]
}

DS_clkRegs&
DS_clkRegs::setdsadcvcmctrl(uint val){
	fill_csr_bits(val,REG_INFO.dsadcvcmctrl());	//CSR6[12:11]
	return *this;
}
uint
DS_clkRegs::getdsadcvcmctrl(){
	return get_csr_bits(REG_INFO.dsadcvcmctrl());	//CSR6[12:11]
}

uint
DS_clkRegs::getdscalcompout(){
	return get_csr_bits(REG_INFO.dscalcompout());	//CSR6[10:10]
}

DS_clkRegs&
DS_clkRegs::setdscalcompmodesel(uint val){
	fill_csr_bits(val,REG_INFO.dscalcompmodesel());	//CSR6[9:9]
	return *this;
}
uint
DS_clkRegs::getdscalcompmodesel(){
	return get_csr_bits(REG_INFO.dscalcompmodesel());	//CSR6[9:9]
}

DS_clkRegs&
DS_clkRegs::setdscalcompotbctrl(uint val){
	fill_csr_bits(val,REG_INFO.dscalcompotbctrl());	//CSR6[8:6]
	return *this;
}
uint
DS_clkRegs::getdscalcompotbctrl(){
	return get_csr_bits(REG_INFO.dscalcompotbctrl());	//CSR6[8:6]
}

DS_clkRegs&
DS_clkRegs::setdscalcompvrefsel(uint val){
	fill_csr_bits(val,REG_INFO.dscalcompvrefsel());	//CSR6[5:0]
	return *this;
}
uint
DS_clkRegs::getdscalcompvrefsel(){
	return get_csr_bits(REG_INFO.dscalcompvrefsel());	//CSR6[5:0]
}

DS_clkRegs&
DS_clkRegs::setdstoplvlatbouten(uint val){
	fill_csr_bits(val,REG_INFO.dstoplvlatbouten());	//CSR7[15:15]
	return *this;
}
uint
DS_clkRegs::getdstoplvlatbouten(){
	return get_csr_bits(REG_INFO.dstoplvlatbouten());	//CSR7[15:15]
}

DS_clkRegs&
DS_clkRegs::setdstopatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.dstopatbctrl());	//CSR7[14:11]
	return *this;
}
uint
DS_clkRegs::getdstopatbctrl(){
	return get_csr_bits(REG_INFO.dstopatbctrl());	//CSR7[14:11]
}

DS_clkRegs&
DS_clkRegs::setdsbiasrcvratbctrl(uint val){
	fill_csr_bits(val,REG_INFO.dsbiasrcvratbctrl());	//CSR7[4:3]
	return *this;
}
uint
DS_clkRegs::getdsbiasrcvratbctrl(){
	return get_csr_bits(REG_INFO.dsbiasrcvratbctrl());	//CSR7[4:3]
}

DS_clkRegs&
DS_clkRegs::setdscalcompatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.dscalcompatbctrl());	//CSR7[2:0]
	return *this;
}
uint
DS_clkRegs::getdscalcompatbctrl(){
	return get_csr_bits(REG_INFO.dscalcompatbctrl());	//CSR7[2:0]
}

DS_clkRegs&
DS_clkRegs::setdsadccompsel(uint val){
	fill_csr_bits(val,REG_INFO.dsadccompsel());	//CSR8[15:15]
	return *this;
}
uint
DS_clkRegs::getdsadccompsel(){
	return get_csr_bits(REG_INFO.dsadccompsel());	//CSR8[15:15]
}

DS_clkRegs&
DS_clkRegs::setdsadccompclkprediv(uint val){
	fill_csr_bits(val,REG_INFO.dsadccompclkprediv());	//CSR8[14:8]
	return *this;
}
uint
DS_clkRegs::getdsadccompclkprediv(){
	return get_csr_bits(REG_INFO.dsadccompclkprediv());	//CSR8[14:8]
}

DS_clkRegs&
DS_clkRegs::setdsadcclkdiv(uint val){
	fill_csr_bits(val,REG_INFO.dsadcclkdiv());	//CSR8[7:5]
	return *this;
}
uint
DS_clkRegs::getdsadcclkdiv(){
	return get_csr_bits(REG_INFO.dsadcclkdiv());	//CSR8[7:5]
}

DS_clkRegs&
DS_clkRegs::setdscompclkdiv(uint val){
	fill_csr_bits(val,REG_INFO.dscompclkdiv());	//CSR8[4:2]
	return *this;
}
uint
DS_clkRegs::getdscompclkdiv(){
	return get_csr_bits(REG_INFO.dscompclkdiv());	//CSR8[4:2]
}

DS_clkRegs&
DS_clkRegs::setdsadcconvmode(uint val){
	fill_csr_bits(val,REG_INFO.dsadcconvmode());	//CSR8[1:0]
	return *this;
}
uint
DS_clkRegs::getdsadcconvmode(){
	return get_csr_bits(REG_INFO.dsadcconvmode());	//CSR8[1:0]
}

DS_clkRegs&
DS_clkRegs::setdsdecmfactor(uint val){
	fill_csr_bits(val,REG_INFO.dsdecmfactor());	//CSR9[15:14]
	return *this;
}
uint
DS_clkRegs::getdsdecmfactor(){
	return get_csr_bits(REG_INFO.dsdecmfactor());	//CSR9[15:14]
}

DS_clkRegs&
DS_clkRegs::setdsdforder(uint val){
	fill_csr_bits(val,REG_INFO.dsdforder());	//CSR9[13:12]
	return *this;
}
uint
DS_clkRegs::getdsdforder(){
	return get_csr_bits(REG_INFO.dsdforder());	//CSR9[13:12]
}

DS_clkRegs&
DS_clkRegs::setdsdfrefcode(uint val){
	fill_csr_bits(val,REG_INFO.dsdfrefcode());	//CSR9[11:0]
	return *this;
}
uint
DS_clkRegs::getdsdfrefcode(){
	return get_csr_bits(REG_INFO.dsdfrefcode());	//CSR9[11:0]
}

uint
DS_clkRegs::getdsdfrdy(){
	return get_csr_bits(REG_INFO.dsdfrdy());	//CSR10[15:15]
}

uint
DS_clkRegs::getdsdfcompstatus(){
	return get_csr_bits(REG_INFO.dsdfcompstatus());	//CSR10[14:14]
}

uint
DS_clkRegs::getdsdfdata(){
	return get_csr_bits(REG_INFO.dsdfdata());	//CSR10[11:0]
}

DS_clkRegs&
DS_clkRegs::setdsclkcalibmode(uint val){
	fill_csr_bits(val,REG_INFO.dsclkcalibmode());	//CSR11[15:15]
	return *this;
}
uint
DS_clkRegs::getdsclkcalibmode(){
	return get_csr_bits(REG_INFO.dsclkcalibmode());	//CSR11[15:15]
}

DS_clkRegs&
DS_clkRegs::setdsclkcalibstart(uint val){
	fill_csr_bits(val,REG_INFO.dsclkcalibstart());	//CSR11[14:14]
	return *this;
}
uint
DS_clkRegs::getdsclkcalibstart(){
	return get_csr_bits(REG_INFO.dsclkcalibstart());	//CSR11[14:14]
}

DS_clkRegs&
DS_clkRegs::setdsclkcalibsoftrstb(uint val){
	fill_csr_bits(val,REG_INFO.dsclkcalibsoftrstb());	//CSR11[13:13]
	return *this;
}
uint
DS_clkRegs::getdsclkcalibsoftrstb(){
	return get_csr_bits(REG_INFO.dsclkcalibsoftrstb());	//CSR11[13:13]
}

DS_clkRegs&
DS_clkRegs::setdsclkcalibdir(uint val){
	fill_csr_bits(val,REG_INFO.dsclkcalibdir());	//CSR11[12:12]
	return *this;
}
uint
DS_clkRegs::getdsclkcalibdir(){
	return get_csr_bits(REG_INFO.dsclkcalibdir());	//CSR11[12:12]
}

DS_clkRegs&
DS_clkRegs::setdsclkcalibregrefsel(uint val){
	fill_csr_bits(val,REG_INFO.dsclkcalibregrefsel());	//CSR11[5:0]
	return *this;
}
uint
DS_clkRegs::getdsclkcalibregrefsel(){
	return get_csr_bits(REG_INFO.dsclkcalibregrefsel());	//CSR11[5:0]
}

DS_clkRegs&
DS_clkRegs::setdsclkcaltimervalue(uint val){
	fill_csr_bits(val,REG_INFO.dsclkcaltimervalue());	//CSR12[14:5]
	return *this;
}
uint
DS_clkRegs::getdsclkcaltimervalue(){
	return get_csr_bits(REG_INFO.dsclkcaltimervalue());	//CSR12[14:5]
}

DS_clkRegs&
DS_clkRegs::setdsclkcaltimerdivvalue(uint val){
	fill_csr_bits(val,REG_INFO.dsclkcaltimerdivvalue());	//CSR12[4:2]
	return *this;
}
uint
DS_clkRegs::getdsclkcaltimerdivvalue(){
	return get_csr_bits(REG_INFO.dsclkcaltimerdivvalue());	//CSR12[4:2]
}

DS_clkRegs&
DS_clkRegs::setdsclkcaltimerdiven(uint val){
	fill_csr_bits(val,REG_INFO.dsclkcaltimerdiven());	//CSR12[1:1]
	return *this;
}
uint
DS_clkRegs::getdsclkcaltimerdiven(){
	return get_csr_bits(REG_INFO.dsclkcaltimerdiven());	//CSR12[1:1]
}

DS_clkRegs&
DS_clkRegs::setdsclkcaltimerstop(uint val){
	fill_csr_bits(val,REG_INFO.dsclkcaltimerstop());	//CSR12[0:0]
	return *this;
}
uint
DS_clkRegs::getdsclkcaltimerstop(){
	return get_csr_bits(REG_INFO.dsclkcaltimerstop());	//CSR12[0:0]
}

DS_clkRegs&
DS_clkRegs::setrxrecclkfbdiv(uint val){
	fill_csr_bits(val,REG_INFO.rxrecclkfbdiv());	//CSR13[15:10]
	return *this;
}
uint
DS_clkRegs::getrxrecclkfbdiv(){
	return get_csr_bits(REG_INFO.rxrecclkfbdiv());	//CSR13[15:10]
}

DS_clkRegs&
DS_clkRegs::setrxrecclkpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.rxrecclkpwrdb());	//CSR13[9:9]
	return *this;
}
uint
DS_clkRegs::getrxrecclkpwrdb(){
	return get_csr_bits(REG_INFO.rxrecclkpwrdb());	//CSR13[9:9]
}

DS_clkRegs&
DS_clkRegs::setdsclktxdlyctrli(uint val){
	fill_csr_bits(val,REG_INFO.dsclktxdlyctrli());	//CSR13[5:4]
	return *this;
}
uint
DS_clkRegs::getdsclktxdlyctrli(){
	return get_csr_bits(REG_INFO.dsclktxdlyctrli());	//CSR13[5:4]
}

DS_clkRegs&
DS_clkRegs::setdsclktxdlyctrlq(uint val){
	fill_csr_bits(val,REG_INFO.dsclktxdlyctrlq());	//CSR13[3:2]
	return *this;
}
uint
DS_clkRegs::getdsclktxdlyctrlq(){
	return get_csr_bits(REG_INFO.dsclktxdlyctrlq());	//CSR13[3:2]
}

DS_clkRegs&
DS_clkRegs::setdsclktxidpm(uint val){
	fill_csr_bits(val,REG_INFO.dsclktxidpm());	//CSR13[1:1]
	return *this;
}
uint
DS_clkRegs::getdsclktxidpm(){
	return get_csr_bits(REG_INFO.dsclktxidpm());	//CSR13[1:1]
}

DS_clkRegs&
DS_clkRegs::setdsclktxqdpm(uint val){
	fill_csr_bits(val,REG_INFO.dsclktxqdpm());	//CSR13[0:0]
	return *this;
}
uint
DS_clkRegs::getdsclktxqdpm(){
	return get_csr_bits(REG_INFO.dsclktxqdpm());	//CSR13[0:0]
}

DS_clkRegs&
DS_clkRegs::setdsclkcalbypass(uint val){
	fill_csr_bits(val,REG_INFO.dsclkcalbypass());	//CSR14[15:14]
	return *this;
}
uint
DS_clkRegs::getdsclkcalbypass(){
	return get_csr_bits(REG_INFO.dsclkcalbypass());	//CSR14[15:14]
}

DS_clkRegs&
DS_clkRegs::setvrefgenrefcode16(uint val){
	fill_csr_bits(val,REG_INFO.vrefgenrefcode16());	//CSR14[13:8]
	return *this;
}
uint
DS_clkRegs::getvrefgenrefcode16(){
	return get_csr_bits(REG_INFO.vrefgenrefcode16());	//CSR14[13:8]
}

DS_clkRegs&
DS_clkRegs::setvrefgenintrpbp(uint val){
	fill_csr_bits(val,REG_INFO.vrefgenintrpbp());	//CSR14[7:7]
	return *this;
}
uint
DS_clkRegs::getvrefgenintrpbp(){
	return get_csr_bits(REG_INFO.vrefgenintrpbp());	//CSR14[7:7]
}

DS_clkRegs&
DS_clkRegs::setvrefgencaldir(uint val){
	fill_csr_bits(val,REG_INFO.vrefgencaldir());	//CSR14[6:6]
	return *this;
}
uint
DS_clkRegs::getvrefgencaldir(){
	return get_csr_bits(REG_INFO.vrefgencaldir());	//CSR14[6:6]
}

DS_clkRegs&
DS_clkRegs::setvrefgenrefcode26(uint val){
	fill_csr_bits(val,REG_INFO.vrefgenrefcode26());	//CSR14[5:0]
	return *this;
}
uint
DS_clkRegs::getvrefgenrefcode26(){
	return get_csr_bits(REG_INFO.vrefgenrefcode26());	//CSR14[5:0]
}

DS_clkRegs&
DS_clkRegs::setvrefgenbgsel(uint val){
	fill_csr_bits(val,REG_INFO.vrefgenbgsel());	//CSR15[14:14]
	return *this;
}
uint
DS_clkRegs::getvrefgenbgsel(){
	return get_csr_bits(REG_INFO.vrefgenbgsel());	//CSR15[14:14]
}

DS_clkRegs&
DS_clkRegs::setvrefgenrefcode38(uint val){
	fill_csr_bits(val,REG_INFO.vrefgenrefcode38());	//CSR15[13:8]
	return *this;
}
uint
DS_clkRegs::getvrefgenrefcode38(){
	return get_csr_bits(REG_INFO.vrefgenrefcode38());	//CSR15[13:8]
}

DS_clkRegs&
DS_clkRegs::setvrefgenrefcode48(uint val){
	fill_csr_bits(val,REG_INFO.vrefgenrefcode48());	//CSR15[5:0]
	return *this;
}
uint
DS_clkRegs::getvrefgenrefcode48(){
	return get_csr_bits(REG_INFO.vrefgenrefcode48());	//CSR15[5:0]
}

DS_clkRegs&
DS_clkRegs::setvrefgenofst16(uint val){
	fill_csr_bits(val,REG_INFO.vrefgenofst16());	//CSR16[15:8]
	return *this;
}
uint
DS_clkRegs::getvrefgenofst16(){
	return get_csr_bits(REG_INFO.vrefgenofst16());	//CSR16[15:8]
}

DS_clkRegs&
DS_clkRegs::setvrefgenofst26(uint val){
	fill_csr_bits(val,REG_INFO.vrefgenofst26());	//CSR16[7:0]
	return *this;
}
uint
DS_clkRegs::getvrefgenofst26(){
	return get_csr_bits(REG_INFO.vrefgenofst26());	//CSR16[7:0]
}

DS_clkRegs&
DS_clkRegs::setvrefgenofst38(uint val){
	fill_csr_bits(val,REG_INFO.vrefgenofst38());	//CSR17[15:8]
	return *this;
}
uint
DS_clkRegs::getvrefgenofst38(){
	return get_csr_bits(REG_INFO.vrefgenofst38());	//CSR17[15:8]
}

DS_clkRegs&
DS_clkRegs::setvrefgenofst48(uint val){
	fill_csr_bits(val,REG_INFO.vrefgenofst48());	//CSR17[7:0]
	return *this;
}
uint
DS_clkRegs::getvrefgenofst48(){
	return get_csr_bits(REG_INFO.vrefgenofst48());	//CSR17[7:0]
}

DS_clkRegs&
DS_clkRegs::setvrefgenrefintl16(uint val){
	fill_csr_bits(val,REG_INFO.vrefgenrefintl16());	//CSR18[13:8]
	return *this;
}
uint
DS_clkRegs::getvrefgenrefintl16(){
	return get_csr_bits(REG_INFO.vrefgenrefintl16());	//CSR18[13:8]
}

DS_clkRegs&
DS_clkRegs::setvrefgenrefintl26(uint val){
	fill_csr_bits(val,REG_INFO.vrefgenrefintl26());	//CSR18[5:0]
	return *this;
}
uint
DS_clkRegs::getvrefgenrefintl26(){
	return get_csr_bits(REG_INFO.vrefgenrefintl26());	//CSR18[5:0]
}

DS_clkRegs&
DS_clkRegs::setvrefgenrefintl38(uint val){
	fill_csr_bits(val,REG_INFO.vrefgenrefintl38());	//CSR19[13:8]
	return *this;
}
uint
DS_clkRegs::getvrefgenrefintl38(){
	return get_csr_bits(REG_INFO.vrefgenrefintl38());	//CSR19[13:8]
}

DS_clkRegs&
DS_clkRegs::setvrefgenrefintl48(uint val){
	fill_csr_bits(val,REG_INFO.vrefgenrefintl48());	//CSR19[5:0]
	return *this;
}
uint
DS_clkRegs::getvrefgenrefintl48(){
	return get_csr_bits(REG_INFO.vrefgenrefintl48());	//CSR19[5:0]
}

E_HILINK_REGISTER_TYPE DS_clkRegs::getType()
{
	return HILINK_PERLANE_REGISTER;
}
