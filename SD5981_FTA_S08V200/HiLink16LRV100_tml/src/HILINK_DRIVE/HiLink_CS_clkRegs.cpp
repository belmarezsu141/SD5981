#include <HILINK_DRIVE/HiLink_CS_clkRegs.h>
CS_clkRegs::CS_clkRegs() {
	// TODO Auto-generated constructor stub
	for(int i=0;i<CS_CLK_CSR_NUM;i++){
		csr[i]=0;
	}
	sliceID=0;
	macroID=0;
	broadcast=false;
	reset_csr_verify();
}

CS_clkRegs::~CS_clkRegs() {}

bool
CS_clkRegs::get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos){
	if(csrIndex>=CS_CLK_CSR_NUM){
		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	return REG_INFO.get_reg_infos(csrIndex,reg_infos);
}

CS_clkRegs&
CS_clkRegs::getInstance(){
	static CS_clkRegs theInstance;
	return theInstance;
}

uint
CS_clkRegs::get_HILINK_MAX_LANE_NUM(){
	return 2;
}

uint
CS_clkRegs::getAddressMapToHiLink(int csrIndex){
	if(csrIndex>=CS_CLK_CSR_NUM){
		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	return (int)(0x0000 | (broadcast << 13) | (sliceID << 9) | csrIndex << 1);
}


uint&
CS_clkRegs::get_csr(uint csrIndex){
	if(csrIndex>=CS_CLK_CSR_NUM){
		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	return csr[csrIndex];
}

void
CS_clkRegs::get_default_MacroLaneID(T_MacroLaneID& id){
	id.MacroID=macroID;
	id.LaneID=sliceID;
}

uint
CS_clkRegs::getCSRCount(){
	return CS_CLK_CSR_NUM;
}

string
CS_clkRegs::getName(){
	return "CS_CLK";
}

E_HILINK_REGISTER_TYPE
CS_clkRegs::getType(){
	return HILINK_PERMACRO_REGISTER;
}
///////////////////////////////////////////////////////////////////////////


	/// Clockslice power down control. Active low.
	/// 0 = Power down the clockslice except oscillator and refclk associated circuit.
	/// 1 = Power up the clockslice.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cspwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{0,"cspwrdb",15,15}
	};
	return reg;
}

	/// Only applicable when there is a serviceslice in the macro.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk0div2sel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{0,"ssrefclk0div2sel",14,14}
	};
	return reg;
}

	/// Only applicable when there is a serviceslice in the macro.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk1div2sel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{0,"ssrefclk1div2sel",13,13}
	};
	return reg;
}

	/// Select the refclk bus 1's source. Only applicable when there is a serviceslice applicable.
	/// 0 = Choose the reference clock 1 from the bump as the refclk bus 1's source.
	/// 1 = Choose a CMOS reference clock from the core as the refclk bus 1's source. Applicable only when the CMOS reference clock is available to HiLink.
	/// Note: If the CMOS reference clock is not available to HiLink, this bit should be set to 0.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::sscmosrefclksel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{0,"sscmosrefclksel",12,12}
	};
	return reg;
}

	/// Select the source of PLL's reference clock.
	/// 0 = Select the reference clock from REFCLKBUS0 as PLL's reference clock.
	/// 1 = Select the reference clock from REFCLKBUS1 as PLL's reference clock.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::refclksel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{0,"refclksel",11,11}
	};
	return reg;
}

	/// Life clock select.
	/// 0 = Choose one of the reference clocks as life clock.
	/// 1 = Choose word clock derived from LCVCO as life clock.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lifeclksel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{0,"lifeclksel",10,10}
	};
	return reg;
}

	/// Core clock select.
	/// 0 = Choose local life clock as the source of core clock.
	/// 1 = Choose life clock from the other clockslice as the source of core clock.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::coreclksel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{0,"coreclksel",9,9}
	};
	return reg;
}

	/// Programs loop filter capacitors. Binary weighted capacitor array, where C=LPFCAP*Cmin, Cmin=750fF (after die shrink), for example:
	/// 0000: C = 0
	/// 0001: C = Cmin
	/// 0010: C = 2*Cmin
	/// ��...
	/// 1111: C = 15*Cmin
	/// 
	/// Only used in PLF mode.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lpfcap(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{0,"lpfcap",7,4}
	};
	return reg;
}

	/// Programs loop filter total resistance. Thermometer encoded. Only five settings are valid.
	/// 0000: R =  2.6 kohm
	/// 0001: R =  1.55 kohm
	/// 0011: R =  0.85 kohm
	/// 0111: R =  0.475 kohm
	/// 1111: R =  0.25 kohm
	/// 
	/// Only used in PLF mode
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lpfres(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{0,"lpfres",3,0}
	};
	return reg;
}

	/// CML divider ratio (the 'K' divider). 
	///                div_to_lane     div_to_pll
	///                      (Kb)                     (Ka)
	/// 00 =              1                           2
	/// 01 =              1                           3
	/// 10 =              2                           2
	/// 11 =              2                           3
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cmldiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{1,"cmldiv",15,14}
	};
	return reg;
}

	/// The P value of the feedback divider ratio (part of the 'N' divider),
	/// which is determined by N=2*P+S+3, where the following conditions shall be met: 
	/// normal mode(ssc-off) : P ��1;S��0; and S is the maximum possible value �� P
	/// For SSC-on Mode: P ��6;S��5; and S is the maximum possible odd value less than P or (P-1)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::fbdivp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{1,"fbdivp",13,8}
	};
	return reg;
}

	/// The S value of the feedback divider ratio (part of the 'N' divider), 
	/// which is determined by N=2*P+S+3, where the following conditions shall be met: 
	/// normal mode(ssc-off) : P ��1;S��0; and S is the maximum possible value �� P
	/// For SSC-on Mode: P ��6;S��5; and S is the maximum possible odd value less than P or (P-1)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::fbdivs(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{1,"fbdivs",7,2}
	};
	return reg;
}

	/// Reference clock divider ratio (the 'M' divider).
	/// 00 = 1
	/// 01 = 1 (default)
	/// 10 = 2
	/// 11 = 3
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::refclkdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{1,"refclkdiv",1,0}
	};
	return reg;
}

	/// Divider ratio for lifeclk2dig. Used for life clock generation.
	/// 00 = divided by 1
	/// 01 = divided by 2
	/// 10 = divided by 3
	/// 11 = divided by 4
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lifeclk2digdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{2,"lifeclk2digdiv",15,14}
	};
	return reg;
}

	/// Divider ratio for wordclk2dig. Used for life clock generation.
	/// 00 = divided by 1
	/// 01 = divided by 2
	/// 10 = divided by 3
	/// 11 = divided by 4
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::wordclk2digdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{2,"wordclk2digdiv",13,12}
	};
	return reg;
}

	/// LCVCO out-of-lock threshold (by default, choose from 1/4096 to 31/4096).
	/// Note: For LCVCO to lock, this field should not be programmed to 0.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvcololthr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{2,"lcvcololthr",10,6}
	};
	return reg;
}

	/// LCVCO loss-of-clock threshold.
	/// 000 = 128
	/// 001 = 256
	/// 010 = 512
	/// 011 = 1024
	/// 100 = 2048
	/// 101 = 4096
	/// 11x = 4096
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvcolocthr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{2,"lcvcolocthr",5,3}
	};
	return reg;
}

	/// LCVCO loss-of-lock mode. Choose how loss-of-lock detection will start after LCVCO calibration is done (coarse tune).
	/// 0 = automatically start.
	/// 1 = manually start.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvcololmode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{2,"lcvcololmode",2,2}
	};
	return reg;
}

	/// LCVCO out-of-lock status. Out-of-lock status is latched until next detection finished.
	/// 0 = LCVCO locked
	/// 1 = LCVCO out of lock
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvcooutoflock(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{2,"lcvcooutoflock",1,1}
	};
	return reg;
}

	/// Loss of LCVCO clock indicator. Status is latched until next detection finished.
	/// 0 = LCVCO clock is active
	/// 1 = LCVCO clock is not active
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lossoflcvcoclk(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{2,"lossoflcvcoclk",0,0}
	};
	return reg;
}

	/// LCVCO power down control. Active low.
	/// 0 = Power down the LCVCO.
	/// 1 = Power up the LCVCO.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pllpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{3,"pllpwrdb",15,15}
	};
	return reg;
}

	/// Active high. Swaps PFD polarity.
	/// LOW �C negative polarity. DLF mode
	/// HIGH �C positive polarity PLF mode.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pfdupdnswap(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{3,"pfdupdnswap",14,14}
	};
	return reg;
}

	/// Force the PFD output to be UP.
	/// 0 = Let the PFD detect frequency and phase difference.
	/// 1 = Force the PFD output to be UP.
	/// Note: setting both PFDFORCEUP and PFDFORCEDN to 1 is not allowed.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pfdforceup(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{3,"pfdforceup",13,13}
	};
	return reg;
}

	/// Force the PFD output to be DOWN.
	/// 0 = Let the PFD detect frequency and phase difference.
	/// 1 = Force the PFD output to be DOWN.
	/// Note: setting both PFDFORCEUP and PFDFORCEDN to 1 is not allowed.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pfdforcedn(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{3,"pfdforcedn",12,12}
	};
	return reg;
}

	/// Select the pulse width of the PFD outputs (both UP/DOWN) to adjust the linearity of the PFD.
	/// 00 = 61ps
	/// 01 = 85ps
	/// 10 = 120ps
	/// 11 = 158ps
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pfdpulsewidth(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{3,"pfdpulsewidth",11,10}
	};
	return reg;
}

	/// Active high. Used to connect 532K resistor as pull-up or pull-down to the DLF inputs as follows: 
	/// 00 = Not connected
	/// 01 = 532K pull-up resistors connected to DLF inputs
	/// 10 = 532K pull-down resistors connected to DLF inputs
	/// 11 = Not allowed
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cpauxres(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{3,"cpauxres",9,8}
	};
	return reg;
}

	/// Active low.  Powers down the passive-mode CMFB opamp.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cpcmfbpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{3,"cpcmfbpwrdb",7,7}
	};
	return reg;
}

	/// Active low. Powers down the PLL ��integral�� CPs such that only residual leakage currents are flowing.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cpintegcppwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{3,"cpintegcppwrdb",6,6}
	};
	return reg;
}

	/// These control bits are only used in PLF mode. Selects bias current and degeneration resistance in charge pump cmfb opamp as follows: 
	/// CPRDEG[0] = 0 �C Rdegen= 500 ohms
	/// CPRDEG[0] = 1 �C Rdegen= 188 ohms
	/// CPRDEG[1] = 0 �C I_bias= 50uA
	/// CPRDEG[1] = 1 �C I_bias= 25uA
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cprdeg(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{3,"cprdeg",5,4}
	};
	return reg;
}

	/// Configures the ��proportional�� CP to operate in DLF-mode or PLF-mode.
	/// LOW - selects ��DLF-mode.�� The two replica driver opamps are disabled and the replica charge pumps are both connected to the vref common mode voltage.
	/// High - selects ��PLF-mode.�� The two replica driver opamps are powered-on and they are used to drive the replica charge pumps.  The vref common mode voltage is not connected to the proportional charge pump.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cpvrefpropsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{3,"cpvrefpropsel",3,3}
	};
	return reg;
}

	/// Programs the common-mode reference for both the DLF mode and the PLF mode. The voltage levels are selected as follows: 
	/// 000- 498 mV; 
	/// 001- 512 mV
	/// ;010- 522 mV; 
	/// 011- 530 mV; 
	/// 100- 457 mV; 
	/// 101- 465 mV; 
	/// 110- 475 mV; 
	/// 111- 489 mV.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cpreflvl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{3,"cpreflvl",2,0}
	};
	return reg;
}

	/// input common mode adjusting for Kb Divider
	/// 00: lvcc_regulated - 0.3V
	/// 01: lvcc_regulated - 0.33V
	/// 10: lvcc_regulated - 0.36V
	/// 11: lvcc_regulated - 0.39V
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cmldivkbvcmsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{4,"cmldivkbvcmsel",15,14}
	};
	return reg;
}

	/// change the integral and proportional current
	/// 0: the proptional cp current is 320uA base with 80uA control step
	/// 1:the proptional cp current is 160uA base with 40uA control step
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cp_i_propchp_tune(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{4,"cp_i_propchp_tune",13,13}
	};
	return reg;
}

	/// Programs ��integral�� charge pump current from 20 to 160uA in 20uA steps.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cpcurrentint(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{4,"cpcurrentint",12,10}
	};
	return reg;
}

	/// Bits [3:0] program ��proportional�� charge pump current from 320 to 1600uA in 80uA steps for both DLF mode and PLF mode. Bits [5:4] are used only in PLF mode to select the output drive capability of the replica driver opamps. Quiescent drive capability changes from  100uA  to  400uA typical in 100uA  steps. The drive capability will increase as the operating point moves away from the quiescent condition.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cpcurrent(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{4,"cpcurrent",9,4}
	};
	return reg;
}

	/// Changing these R and C settings will cause the phase margin of the passive CMFB opamp circuit to increase and decrease.
	/// These control bits are only used in PLF mode. Changing these R and C settings will cause the phase margin of the passive CMFB opamp circuit to increase and decrease. Programs the resistor and capacitor values in the compensation network of the PLF-mode CP cmfb circuit according to the following:
	/// Cp_rzero_cmfb[3,2] = 00   R= 2379 ohms
	/// Cp_rzero_cmfb[3,2] = 01   R= 884 ohms
	/// Cp_rzero_cmfb[3,2] = 10   R= 170 ohms
	/// Cp_rzero_cmfb[3,2] = 11   R= 2005 ohms
	/// Cp_rzero_cmfb[1,0] = 00   C= 1.128 pF
	/// Cp_rzero_cmfb[1,0] = 01   C= 3.385 pF
	/// Cp_rzero_cmfb[1,0] = 10   C= 4.513 pF
	/// Cp_rzero_cmfb[1,0] = 11   C= 6.77 pF
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cprzerocmfb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{4,"cprzerocmfb",3,0}
	};
	return reg;
}

	/// LOW - selects ��DLF-mode��
	/// High - selects ��PLF-mode��
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cpdlfmuxsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{5,"cpdlfmuxsel",15,15}
	};
	return reg;
}

	/// control vref_gen drive ability
	/// ;cp_spare[0]: connected n0 and p0 to vref_gen output
	/// ;cp_spare[1]: connected n1 and p1 to vref_gen output
	/// cp_spare[2]: connected n2 and p2 to vref_gen output
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cpspare2to0(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{5,"cpspare2to0",14,12}
	};
	return reg;
}

	/// Digital loop filter power down control. Active low.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dlfpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{5,"dlfpwrdb",11,11}
	};
	return reg;
}

	/// extra mim cap sel for dlf, high to connect into the circuit
	/// cap value is 10.9pF
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dlfextramimcap(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{5,"dlfextramimcap",10,10}
	};
	return reg;
}

	/// Active  LOW power down for the DLF test mode. Powers down and disconnect DTB and ATB DLF muxes.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dlftstpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{5,"dlftstpwrdb",9,9}
	};
	return reg;
}

	/// power down CMFB of  DLF mode
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dlfcmfbpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{5,"dlfcmfbpwrdb",8,8}
	};
	return reg;
}

	/// Sets S and H clock sample width 
	/// HIGH �C 2 ps
	/// LOW �C 1 ps
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dlfshdelsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{5,"dlfshdelsel",7,7}
	};
	return reg;
}

	/// PLL digital test bus (DTB) control When DLF test mode enabled, ends following test signals in said order to the ��dtb_o�� pin: ph1, ph1a, ph2, ph2a, samp_clk_i, fref_i, calrstb_i, cmfpwrdb_i.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dlfseldtb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{5,"dlfseldtb",6,2}
	};
	return reg;
}

	/// set the sample capacitor of  S/H stage in DLF mode. 
	/// 00: 0
	/// 01: 1.55p
	/// 10: 1.55p
	/// 11: 3.1p
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dlfshcapsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{5,"dlfshcapsel",1,0}
	};
	return reg;
}

	/// Optional bias current control for the future.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cmlbufoutbiassel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{6,"cmlbufoutbiassel",15,14}
	};
	return reg;
}

	/// Bits [2:0] used for replica bias common mode select from 900 to 780 mV in 15 mV steps  (thermal code)
	/// Bits [5:3] used for ��pbias�� override in a test mode range from 0 to 550 mV (thermometer code)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cmldivbiascal(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{6,"cmldivbiascal",13,8}
	};
	return reg;
}

	/// lcvco_spare[3:2] are for spare pins
	/// lcvco_spare[1]is for peak detector power down
	/// 0:  enable peak detector / 1:  power down peak detector 
	/// lcvco_spare[0] is for vco temperature direction switch.
	/// 0:  normal direction / 1:  opposite direction
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvcospare(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{6,"lcvcospare",7,4}
	};
	return reg;
}

	/// One hot coded.
	/// 000 = 0000_0001 (reserved)
	/// 001 = 0000_0010 (reserved)
	/// 010 = 0000_0100 (reserved)
	/// 011 = 0000_1000 (reserved)
	/// 100 = 0001_0000 (LCVCO min amplitude)
	/// 101 = 0010_0000 (LCVCO max amplitude)
	/// 110 = 0100_0000 (reserved)
	/// 111 = 1000_0000 (reserved)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvcoselpeaklvl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{6,"lcvcoselpeaklvl",2,0}
	};
	return reg;
}

	/// When VCO calibration is auto-mode, Force Power On peak detector
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvco_pwron_force_en(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{7,"lcvco_pwron_force_en",15,15}
	};
	return reg;
}

	/// Choose LCVCO tuning band in manual calibration mode, i.e., when LCVCOCALMODE is set to 1.
	/// 000 = 1st band (highest)
	/// 001 = 2nd band
	/// 010 = 3rd band 
	/// 011 = 4th band (lowest on V100)
	/// 100 = 5th band  (reserved for future use)
	/// 101 = 6th band (reserved for future use)
	/// 11x = 7th band (reserved for future use)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvcobandsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{7,"lcvcobandsel",14,12}
	};
	return reg;
}

	/// VCO tank freqency calibration code, 
	/// freqcal[19:1] is thermo code, freqcal[0] is binary code, which weight is 0.5. 
	/// 3 settings may overlaps in one frequency range. 
	/// 0000_0000_0000_0000_0000      0f
	/// 00000000000000000001      10f
	/// 00000000000000000010      20f
	/// 00000000000000000011      30f
	/// 00000000000000000110      40f
	/// 00000000000000000111      50f
	/// 00000000000000001110      60f
	/// ......
	/// 01111111111111111111      18*20f+10f
	/// 1111_1111_1111_1111_1110      19*20f
	/// 11111111111111111111      19*20f+10f
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvcofreqcal(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{7,"lcvcofreqcal",10,5}
	};
	return reg;
}

	/// Set the LCVCO amplitude value for min and max amplitude calibrations in manual calibration mode, i.e., when LCVCOCALMODE is set to 1.  Binary setting needs to be converted to gray code, then thermo code before sending to the analog.
	/// 00000 = 0000_0000_0000_0000 (min)
	/// 00001 = 0000_0000_0000_0001
	/// 00010 = 0000_0000_0000_0011
	/// ����
	/// 01111 = 0111_1111_1111_1111
	/// 1xxxx = 1111_1111_1111_1111 (max)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvcoitank(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{7,"lcvcoitank",4,0}
	};
	return reg;
}

	/// Hsclk Distribution  powerdown control, Active low.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::hsclkfrclkspinepwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{8,"hsclkfrclkspinepwrdb",14,14}
	};
	return reg;
}

	/// power down extra hsclk drvier in CSH V102
	/// 0:  power down
	/// 1:  power on
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::hsclkfromsspwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{8,"hsclkfromsspwrdb",13,13}
	};
	return reg;
}

	/// Disconnected internally
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::hsclktosspwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{8,"hsclktosspwrdb",12,12}
	};
	return reg;
}

	/// Binary tail current control of buffers connected to a clockslice cmldivider 
	/// 00 �C 0 % current increase
	/// 01 �C 16 % current increase
	/// 10 �C 30 % current increase
	/// 11 �C 50 % current increase
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::hsclkfromcsbiasctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{8,"hsclkfromcsbiasctrl",11,10}
	};
	return reg;
}

	/// Disconnected internally
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::hsclkfromssbiasctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{8,"hsclkfromssbiasctrl",9,8}
	};
	return reg;
}

	/// Set current of extra hsclk driver, 
	/// Icp = 600uA +hsclk_from_cs_mux_bias_ctrl[1:0]*100uA.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::hsclktossbiasctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{8,"hsclktossbiasctrl",7,6}
	};
	return reg;
}

	/// Hsclk Distribution  replica bias common mode select from 900 to 780 mV in 15 mV steps .
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::hsclkreploadctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{8,"hsclkreploadctrl",5,3}
	};
	return reg;
}

	/// Hsclk Distribution  replica load selection.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::hsclkreprefsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{8,"hsclkreprefsel",2,0}
	};
	return reg;
}

	/// hsclkspare[2:1] is not used currently
	/// hsclkspare[0] is used to choose buffer input common mode voltage
	/// 0:Vcm_buf=Vref_buf; 
	/// 1:Vcm_buf=Vref
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::hsclkspare(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{9,"hsclkspare",14,12}
	};
	return reg;
}

	/// CS Bias Top powerdown control, Active Low.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::biascmupwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{9,"biascmupwrdb",8,8}
	};
	return reg;
}

	/// biascvcal[7:2] not used currently
	/// biascvcal[1]  icc common mode rejection selection
	///     0: turn on the common mode rejection
	///     1: turn off the common mode rejection
	/// biascvcal[0]  icv common mode rejection selection
	///     0: turn on the common mode rejection
	///     1: turn off the common mode rejection
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::biascvcal(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{9,"biascvcal",7,0}
	};
	return reg;
}

	/// 0 = Clockslice bias receivers operate in normal mode
	/// ;1 = Clockslice bias receivers in emergency operating mode.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csrxbiasbackupgen(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{10,"csrxbiasbackupgen",15,15}
	};
	return reg;
}

	/// csspare[14] is for H16 testchip macro B spine clock 1 selection
	///     0: from CSH0
	///     1: from CSL
	/// csspare[13:7] are CS Analog Top Spare bits
	/// csspare[6]  is for CS ATB output buffer selection
	///     0: output from buffer
	///     1: directly output (bypass buffer)
	/// csspare[5:4] Regulator referrence voltage tuning(default value : 2'b10)
	///     00 : 0.717V
	///     01 : 0.777V
	///     10 : 0.797V
	///     11 : 0.827V
	/// csspare[3] DLF Regulator loading adjust power down(default value : 1'b1); 
	///     0: power down
	///     1: active
	/// csspare[2] CML Regulator loading adjust power down(default value : 1'b1); 
	///     0: power down
	///     1: active
	/// csspare[1] PLL Regulator loading adjust power down(default value : 1'b1); 
	///     0: power down
	///     1: active
	/// csspare[0] is for low-offset comparator calibration mode selection(default value : 1'b0)
	///    0: vrefp and vrefm
	///    1: vss
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csspare(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{10,"csspare",14,0}
	};
	return reg;
}

	/// CS Regulator powerdown control, Active low.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vregpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{11,"vregpwrdb",15,15}
	};
	return reg;
}

	/// change the connection of the noise reduction cap(120pF)
	/// 0: disconnect the noise reduction cap
	/// 1: connect the noise reduction cap
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vregcapsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{11,"vregcapsel",12,12}
	};
	return reg;
}

	/// adjust bleed current value on vreg power down mode
	/// bleed current = 75uA * vreg_pll_selfbleed[3:0]
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vregselfbleed(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{11,"vregselfbleed",11,8}
	};
	return reg;
}

	/// one hot code, set reference voltage of opamp in regulator
	/// 00000001: 0.834
	/// 00000010: 0.855
	/// 00000100: 0.899
	/// 00001000: 0.958
	/// 00010000: 1.004 (default)
	/// 00100000: 1.024
	/// 01000000: 1.055
	/// 10000000: 1.077
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vregplllvl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{11,"vregplllvl",7,0}
	};
	return reg;
}

	/// CS Calibraiton Module powerdown control, Active low.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::calpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{12,"calpwrdb",15,15}
	};
	return reg;
}

	/// Configures the PLL Control Path such that the VCO can be calibrated with zero volts differential control voltage. Disables the PFD, forces charge pump currents to flow in the reset pathways, enables the replica opamps and common-mode opamp, connects charge pump outputs to common mode reference voltage. Active low.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::calrstb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{12,"calrstb",14,14}
	};
	return reg;
}

	/// Bypass post maximum amplitude calibration frequency check enable, active high.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_post_lckchk_bypass(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{12,"cs_post_lckchk_bypass",8,8}
	};
	return reg;
}

	/// Bypass initial amplitude calibration enable, active high.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_initamp_calib_bypass(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{12,"cs_initamp_calib_bypass",7,7}
	};
	return reg;
}

	/// CS Low-offset Comparator calibration enable.
	/// 0=disable
	/// 1=enable
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cslowoffcal(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{12,"cslowoffcal",6,6}
	};
	return reg;
}

	/// Binary coding, Following is convertion.
	/// 63: +31
	/// 62: +30
	/// .
	/// .
	/// .
	/// 1: -30
	/// 0: -31
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cslowoffsetctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{12,"cslowoffsetctrl",5,0}
	};
	return reg;
}

	/// Select whether LCVCO calibrations (offset, min amplitude, frequency, max amplitude) are done automatically or manually. Switching from manul mode to automatic mode restarts the auto calibration process.
	/// 0 = Automatic LCVCO calibrations
	/// 1 = Manual LCVCO calibrations
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvcocalmode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{13,"lcvcocalmode",15,15}
	};
	return reg;
}

	/// Choose what to calibrate in manual calibration mode, i.e., when LCVCOCALMODE is set to 1.
	/// 00 = Comparator offset compensation
	/// 01 = Amplitude calibration (both min and max)
	/// 10 = Frequency calibration (frequency coarse tune)
	/// 11 = Reserved
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvcocalctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{13,"lcvcocalctrl",13,10}
	};
	return reg;
}

	/// 
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ptatcalout(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{13,"ptatcalout",9,9}
	};
	return reg;
}

	/// 
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cvcalout(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{13,"cvcalout",8,8}
	};
	return reg;
}

	/// 
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::comparestatus(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{13,"comparestatus",7,6}
	};
	return reg;
}

	/// 
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dtbout(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{13,"dtbout",5,5}
	};
	return reg;
}

	/// LCVCO calibrations completed. 
	/// 0 = LCVCO calibrations do not finish yet.
	/// 1 = LCVCO calibrations finish.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvcocaldone(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{13,"lcvcocaldone",4,4}
	};
	return reg;
}

	/// LCVCO calibrations didn't succeed. Not available in current design.
	/// 0 = LCVCO calibrations didn't complete successfully.
	/// 1 = LCVCO calibrations completed successfully.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvcocalerr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{13,"lcvcocalerr",3,3}
	};
	return reg;
}

	/// Status of LCVCO calibrations. If LCVCO calibrations didn't succeed, this register gives the internals status and/or conditions of the calibration processes.
	/// Mapping TBD.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvcocalstatus(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{13,"lcvcocalstatus",2,0}
	};
	return reg;
}

	/// Clock Slice Digital test bus select.
	/// 0000 = wordclk2dig_div2
	/// 0001 = wordclk2dig
	/// 0010 = lifeclk2dig
	/// 0011= refclk2dig
	/// 0100 = divclk2dig
	/// 0101 = divclk2dig devide by 2
	/// 0110 = wordclk2dig_16b32b
	/// 1xxx = DTB out from CS analog
	/// default = wordclk2dig
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csdtbsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{14,"csdtbsel",15,12}
	};
	return reg;
}

	/// Regulator ATB selection control.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vregatbctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{14,"vregatbctrl",11,3}
	};
	return reg;
}

	/// CS Top ATB BUS selection.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csatbfinalsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{14,"csatbfinalsel",2,0}
	};
	return reg;
}

	/// Clockslice analog test bus select. Select which analog signal to be brought out through analog test muxes for observation.
	/// Mapping TBD
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csatbsel23to16(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{15,"csatbsel23to16",15,8}
	};
	return reg;
}

	/// ssspare[7:4] are serviceslice spare bits.
	/// ss_spare[3:1] are for Process Sensor output selection
	///     000: core ulvt nmos voltage output
	/// ;    001: core svt nmos voltage ouput
	/// ;    010: io nmos voltage output
	/// ;    011: core ulvt pmos voltage output
	/// ;    100: core svt pmos voltage output
	/// ;    101: io pmos voltage output
	/// ;    110: ploy res voltage output
	/// ;    111: iccp50 current output
	/// ssspare[0] is for ATB signal selection.
	///     0:  select Bandgap atb from buffer
	///     1:  bypass Bandgap atb from buffer
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssspare(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{15,"ssspare",7,0}
	};
	return reg;
}

	/// Serviceslice power down control. Active low.
	/// 0 = Power down the serviceslice
	/// 1 = Power up the serviceslice
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::sspwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{16,"sspwrdb",15,15}
	};
	return reg;
}

	/// SS refclk0 power down Active low
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk0pwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{16,"ssrefclk0pwrdb",14,14}
	};
	return reg;
}

	/// SS refclk1 power down Active low
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk1pwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{16,"ssrefclk1pwrdb",13,13}
	};
	return reg;
}

	/// Currently no use.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::sshsclkss2cspwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{16,"sshsclkss2cspwrdb",9,9}
	};
	return reg;
}

	/// Currently no use.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::sshsclkcs2sspwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{16,"sshsclkcs2sspwrdb",8,8}
	};
	return reg;
}

	/// SS reference clock0 CML-div2 powerdown control, Active low.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk0cmldivpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{16,"ssrefclk0cmldivpwrdb",7,7}
	};
	return reg;
}

	/// Currently no use.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk0atten(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{16,"ssrefclk0atten",5,4}
	};
	return reg;
}

	/// SS reference clock1 CML-div2 powerdown control, Active low.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk1cmldivpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{16,"ssrefclk1cmldivpwrdb",3,3}
	};
	return reg;
}

	/// Currently no use.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk1atten(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{16,"ssrefclk1atten",1,0}
	};
	return reg;
}

	/// BG600mV source selection for CC current generation.
	/// 0 = Bandgap 800mV
	/// 1 =  Lvcc divided 800mV.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::bg600mvlvccresdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{17,"bg600mvlvccresdiv",15,15}
	};
	return reg;
}

	/// Active high. Test mode which disables the constant current generator when set to 0
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::bgccen(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{17,"bgccen",14,14}
	};
	return reg;
}

	/// Active high. Test mode which disables the constant voltage bandgap when set to 0
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::bgcven(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{17,"bgcven",13,13}
	};
	return reg;
}

	/// Active high. Test mode which disables the PTAT bandgap when set to 0
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::bgpaten(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{17,"bgpaten",12,12}
	};
	return reg;
}

	/// Test mode which forces the startup circuit in the bandgap or the ptat to be active; 
	/// Bg_force_start[0]=0   no effect; 
	/// Bg_force_start[0]=1   bg force startup; 
	/// Bg_force_start[1]=0   no effect; 
	/// Bg_force_start[1]=1   ptat force startup
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::bgforcestart(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{17,"bgforcestart",11,10}
	};
	return reg;
}

	/// Test mode which disables the startup circuit in the bandgap or the ptat; 
	/// bg_start_bypass[0]=0   no effect; 
	/// bg_start_bypass[0]=1   bg disable startup; 
	/// bg_start_bypass[0]=1   bg disable startup; 
	/// bg_start_bypass[1]=0   no effect; 
	/// bg_start_bypass[1]=1   ptat disable startup
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::bgstartbypass(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{17,"bgstartbypass",9,8}
	};
	return reg;
}

	/// Bandgap Bypass control bit.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::bgbypass(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{17,"bgbypass",7,0}
	};
	return reg;
}

	/// Not used (reserved for future use).
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::hvvbgccin(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{18,"hvvbgccin",15,15}
	};
	return reg;
}

	/// Selects bandgap voltage output value according to the following ; 
	/// 000:  800 mV; 
	/// 001:  769 mV; 
	/// 010:  738 mV; 
	/// 011:  707 mV; 
	/// 100:  922 mV; 
	/// 101:  891 mV; 
	/// 110:  861 mV; 
	/// 111:  830 mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vbgreflvl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{18,"vbgreflvl",14,12}
	};
	return reg;
}

	/// Not used (reserved for future use).
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::hvvbgptatin(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{18,"hvvbgptatin",11,11}
	};
	return reg;
}

	/// Selects ptat voltage output value according to the following ; 
	/// 000:  800 mV; 
	/// 001:  769 mV; 
	/// 010:  738 mV; 
	/// 011:  707 mV; 
	/// 100:  922 mV; 
	/// 101:  891 mV; 
	/// 110:  861 mV; 
	/// 111:  830 mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vbgptatlvl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{18,"vbgptatlvl",10,8}
	};
	return reg;
}

	/// Spare pins, not connected in this revision
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::biasselptatmix(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{18,"biasselptatmix",7,0}
	};
	return reg;
}

	/// Only bit[11:0] are used.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssatbsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{19,"ssatbsel",15,0}
	};
	return reg;
}

	/// Clear the loss of lock detector. Active high.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lld_clr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{20,"cs_lld_clr",13,13}
	};
	return reg;
}

	/// Clear the frequency detector. Active high.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_fd_clr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{20,"cs_fd_clr",12,12}
	};
	return reg;
}

	/// Clear the status of calibration. Active high.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_calib_clr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{20,"cs_calib_clr",11,11}
	};
	return reg;
}

	/// Start clockslice loss of clock detector. Active rising edge.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lcd_start(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{20,"cs_lcd_start",10,10}
	};
	return reg;
}

	/// Start clockslice loss of lock detector. Active rising edge.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lld_start(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{20,"cs_lld_start",9,9}
	};
	return reg;
}

	/// Start clockslice calibration. Active rising edge.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_calib_start(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{20,"cs_calib_start",8,8}
	};
	return reg;
}

	/// Enable clockslice loss of clock detector. Active high.
	/// 0 = Don't enable the detector, Gating the clock
	/// 1 = Enable the detector
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lcd_enable(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{20,"cs_lcd_enable",7,7}
	};
	return reg;
}

	/// Enable clockslice loss of lock detector. Active high.
	/// 0 = Don't enable the detector, Gating the clock
	/// 1 = Enable the detector
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lld_enable(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{20,"cs_lld_enable",6,6}
	};
	return reg;
}

	/// Enable clockslice calibration. Active high.
	/// 0 = Don't enable calibration, Gating the clock
	/// 1 = Enable calibration
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_calib_enable(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{20,"cs_calib_enable",5,5}
	};
	return reg;
}

	/// Clockslice loss of clock detector reset. Active low.
	/// 0 = Reset loss of clock detector part
	/// 1 = Reset is not active
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lcd_soft_rst_n(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{20,"cs_lcd_soft_rst_n",4,4}
	};
	return reg;
}

	/// Clockslice loss of lock detector reset. Active low.
	/// 0 = Reset loss of lock detector part
	/// 1 = Reset is not active
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lld_soft_rst_n(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{20,"cs_lld_soft_rst_n",3,3}
	};
	return reg;
}

	/// Clockslice calibration reset. Active low.
	/// 0 = Reset calibration part
	/// 1 = Reset is not active
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_calib_soft_rst_n(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{20,"cs_calib_soft_rst_n",2,2}
	};
	return reg;
}

	/// Clockslice global reset. Active low.
	/// 0 = Reset whole digital circuit
	/// 1 = Reset is not active
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_glb_soft_rst_n(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{20,"cs_glb_soft_rst_n",0,0}
	};
	return reg;
}

	/// Clockslice analog test bus select. Select which analog signal to be brought out through analog test muxes for observation.
	/// Mapping TBD.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csatbsel15to0(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{21,"csatbsel15to0",15,0}
	};
	return reg;
}

	/// Control direction of general purpose calibration FSM for debugging.
	/// [6]: For lock of check calibration.
	/// [5]: For maximum amplitude calibration.
	/// [4]: For band selection calibration.
	/// [3]: For frequency calibration.
	/// [2]: For minimum amplitude calibration.
	/// [1]: For initial amplitude calibration.
	/// [0]: For offset calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_direction_ctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{22,"cs_direction_ctrl",6,0}
	};
	return reg;
}

	/// Calibration mode configuration for band selection calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_calib_mode_bdsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{23,"cs_calib_mode_bdsel",14,12}
	};
	return reg;
}

	/// Calibration mode configuration for frequency calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_calib_mode_freqcal(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{23,"cs_calib_mode_freqcal",11,9}
	};
	return reg;
}

	/// Calibration mode configuration for minimum amplitude calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_calib_mode_minamp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{23,"cs_calib_mode_minamp",8,6}
	};
	return reg;
}

	/// Calibration mode configuration for initial amplitude calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_calib_mode_initamp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{23,"cs_calib_mode_initamp",5,3}
	};
	return reg;
}

	/// Calibration mode configuration for offset calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_calib_mode_offset(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{23,"cs_calib_mode_offset",2,0}
	};
	return reg;
}

	/// Calibration mode configuration for lock of check calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_calib_mode_lckchk(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{24,"cs_calib_mode_lckchk",5,3}
	};
	return reg;
}

	/// Calibration mode configuration for maximum amplitude calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_calib_mode_maxamp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{24,"cs_calib_mode_maxamp",2,0}
	};
	return reg;
}

	/// Define minimum calibration control code for initial amplitude calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_ctrl_code_min_initamp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{25,"cs_ctrl_code_min_initamp",15,11}
	};
	return reg;
}

	/// Define maximum calibration control code for offset calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_ctrl_code_max_offset(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{25,"cs_ctrl_code_max_offset",10,5}
	};
	return reg;
}

	/// Define minimum calibration control code for offset calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_ctrl_code_min_offset(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{25,"cs_ctrl_code_min_offset",4,0}
	};
	return reg;
}

	/// Define maximum calibration control code for minimum amplitude calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_ctrl_code_max_minamp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{26,"cs_ctrl_code_max_minamp",14,10}
	};
	return reg;
}

	/// Define minimum calibration control codefor minimum amplitude calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_ctrl_code_min_minamp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{26,"cs_ctrl_code_min_minamp",9,5}
	};
	return reg;
}

	/// Define maximum calibration control code for initial amplitude calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_ctrl_code_max_initamp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{26,"cs_ctrl_code_max_initamp",4,0}
	};
	return reg;
}

	/// Define minimum calibration control code for band selection calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_ctrl_code_min_bdsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{27,"cs_ctrl_code_min_bdsel",14,10}
	};
	return reg;
}

	/// Define minimum calibration control code for frequency calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_ctrl_code_min_freqcal(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{27,"cs_ctrl_code_min_freqcal",5,0}
	};
	return reg;
}

	/// Define maximum calibration control code for maximum amplitude calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_ctrl_code_max_maxamp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{28,"cs_ctrl_code_max_maxamp",14,10}
	};
	return reg;
}

	/// Define minimum calibration control code for maximum amplitude calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_ctrl_code_min_maxamp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{28,"cs_ctrl_code_min_maxamp",9,5}
	};
	return reg;
}

	/// Define maximum calibration control code for band selection calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_ctrl_code_max_bdsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{28,"cs_ctrl_code_max_bdsel",4,0}
	};
	return reg;
}

	/// Define maximum calibration control code for lock of check calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_ctrl_code_max_lckchk(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{29,"cs_ctrl_code_max_lckchk",9,5}
	};
	return reg;
}

	/// Define minimum calibration control codefor lock of check calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_ctrl_code_min_lckchk(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{29,"cs_ctrl_code_min_lckchk",4,0}
	};
	return reg;
}

	/// Define initial calibration control code for initial amplitude calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_init_code_amp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{30,"cs_init_code_amp",11,7}
	};
	return reg;
}

	/// Define initial calibration control code for offset calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_init_code_offset(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{30,"cs_init_code_offset",6,2}
	};
	return reg;
}

	/// Define initial calibration control code for band selection calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_init_code_bdsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{30,"cs_init_code_bdsel",1,0}
	};
	return reg;
}

	/// Define initial calibration control code for maximum amplitude calibration. Not available in current design.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_init_code_maxamp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{31,"cs_init_code_maxamp",15,11}
	};
	return reg;
}

	/// Define initial calibration control code for  frequency calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_init_code_freqcal(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{31,"cs_init_code_freqcal",10,5}
	};
	return reg;
}

	/// Define initial calibration control code for minimum amplitude calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_init_code_minamp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{31,"cs_init_code_minamp",4,0}
	};
	return reg;
}

	/// Define maximum calibration control code for frequency calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_ctrl_code_max_freqcal(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{32,"cs_ctrl_code_max_freqcal",10,5}
	};
	return reg;
}

	/// Define initial calibration control code for lock of check calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_init_code_lckchk(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{32,"cs_init_code_lckchk",4,0}
	};
	return reg;
}

	/// Configure the maximum transitions for frequency calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_trans_max_freqcal(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{33,"cs_trans_max_freqcal",15,12}
	};
	return reg;
}

	/// Configure the maximum transitions for minimum amplitude calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_trans_max_minamp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{33,"cs_trans_max_minamp",11,8}
	};
	return reg;
}

	/// Configure the maximum transitions for initial amplitude calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_trans_max_initamp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{33,"cs_trans_max_initamp",7,4}
	};
	return reg;
}

	/// Configure the maximum transitions for offset calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_trans_max_offset(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{33,"cs_trans_max_offset",3,0}
	};
	return reg;
}

	/// Configure the maximum transitions for lock of check calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_trans_max_lckchk(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{34,"cs_trans_max_lckchk",11,8}
	};
	return reg;
}

	/// Configure the maximum transitions for maximum amplitude calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_trans_max_maxamp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{34,"cs_trans_max_maxamp",7,4}
	};
	return reg;
}

	/// Configure the maximum transitions for band selection calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_trans_max_bdsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{34,"cs_trans_max_bdsel",3,0}
	};
	return reg;
}

	/// Define the threshold of frequency detector. If abs[number of refclk cycle - number of fbclk cycle less than threshold, it would indicate that PLL is locked.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_fd_threshold(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{35,"cs_fd_threshold",10,1}
	};
	return reg;
}

	/// When loss of lock detecting, it could enable timer for waiting specified time.
	/// 0 = disable
	/// 1 = enable
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_meas_fd_wait(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{35,"cs_meas_fd_wait",0,0}
	};
	return reg;
}

	/// Define the decrease value of reference clock counter.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_fd_ref_cnt_dv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{36,"cs_fd_ref_cnt_dv",13,12}
	};
	return reg;
}

	/// The initial value of reference clock counter.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_fd_ref_cnt_lv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{36,"cs_fd_ref_cnt_lv",11,0}
	};
	return reg;
}

	/// Define the decrease value of feedback clock counter.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_fd_fb_cnt_dv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{37,"cs_fd_fb_cnt_dv",13,12}
	};
	return reg;
}

	/// The initial value of feedback clock counter.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_fd_fb_cnt_lv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{37,"cs_fd_fb_cnt_lv",11,0}
	};
	return reg;
}

	/// Configuration of timer for waiting, which is the cycles of reference clock.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_timer_value(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{38,"cs_timer_value",14,5}
	};
	return reg;
}

	/// Configuration of divider in timer.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_timer_div_value(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{38,"cs_timer_div_value",4,2}
	};
	return reg;
}

	/// Enable the divider in timer. Not available in current design.
	/// 0 = disable
	/// 1 = enable
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_timer_div_en(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{38,"cs_timer_div_en",1,1}
	};
	return reg;
}

	/// Stop timer, for debugging.
	/// 0 = normal
	/// 1 = stop the timer
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_timer_stop(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{38,"cs_timer_stop",0,0}
	};
	return reg;
}

	/// The divider of feedback clock for loss of lock detector.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lld_fb_div_ratio(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{39,"cs_lld_fb_div_ratio",3,1}
	};
	return reg;
}

	/// The LLD operation manner:
	/// 0 = operate always.
	/// 1 = Perform loss of lock one time then halt.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lld_once(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{39,"cs_lld_once",0,0}
	};
	return reg;
}

	/// The decrease value of reference clock counter.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lld_ref_cnt_dv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{40,"cs_lld_ref_cnt_dv",14,12}
	};
	return reg;
}

	/// The initial value of reference clock counter.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lld_ref_cnt_lv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{40,"cs_lld_ref_cnt_lv",11,0}
	};
	return reg;
}

	/// The decrease value of feedback clock counter.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lld_fb_cnt_dv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{41,"cs_lld_fb_cnt_dv",14,12}
	};
	return reg;
}

	/// The initial value of feedback clock counter.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lld_fb_cnt_lv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{41,"cs_lld_fb_cnt_lv",11,0}
	};
	return reg;
}

	/// The divider of feedback clock of loss of clock.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lcd_fb_div_ratio(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{42,"cs_lcd_fb_div_ratio",9,1}
	};
	return reg;
}

	/// Override the status of loss of clock.
	/// 0 = normal
	/// 1 = override
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lcd_override(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{42,"cs_lcd_override",0,0}
	};
	return reg;
}

	/// SSC Generator freeze mode enable, active high
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssc_freeze(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{43,"ssc_freeze",13,13}
	};
	return reg;
}

	/// SSC Generator freeze mode select
	/// 0 = Freeze in current PPM
	/// 1 = Freeze to 0 PPM
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssc_freeze_mode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{43,"ssc_freeze_mode",12,12}
	};
	return reg;
}

	/// SSC freeze mode enable source select
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssc_freeze_en_sel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{43,"ssc_freeze_en_sel",11,11}
	};
	return reg;
}

	/// The initial value of feedback clock counter. Not used incurrent design.
	/// Used CS_LCD_FB_CNT_LV[0] as cs_lcd_clksel configure. and the signal indicated clockslice lcd refclk and fdclk select signal
	/// 0 = refclk is  refclk2dig and fdclk is as pll0_divclk2dig
	/// 1 = refclk is pll0_divclk2dig and fdclk is as refclk2dig
	/// the default value of CS_LCD_FB_CNT_LV[0] is 1
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lcd_fb_cnt_lv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{43,"cs_lcd_fb_cnt_lv",10,0}
	};
	return reg;
}

	/// cp_dlf_resfdbkpwrd,DLF Feedback resistor powerdown control.
	/// 2'b00: 100K Resistor ON 
	/// 2'b01:  200K Resistor ON
	/// 2'b10:  200K Resistor ON.
	/// 2'b11: 200K Resistor OFF.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cp_dlf_resfdbkpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{44,"cp_dlf_resfdbkpwrdb",15,14}
	};
	return reg;
}

	/// Prop CP Switch capacitor S/H clock edge control bit
	/// 0: 1.4pF
	/// 1: 4.2pF
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cp_dlf_sample_edge_switch(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{44,"cp_dlf_sample_edge_switch",13,13}
	};
	return reg;
}

	/// cp_dlf common mode feedback mode switch control
	/// 0: Default mode
	/// 1: Revised mode
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cp_dlf_cmfb_switch(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{44,"cp_dlf_cmfb_switch",12,12}
	};
	return reg;
}

	/// set the current for refclk1 cml driver in the CS
	/// 2'b00 :  I
	/// 2'b01:   I*1.16
	/// 2'b10:   I*1.33
	/// 2'b11:  I*1.48
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::refclk1_cml_bias_ctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{44,"refclk1_cml_bias_ctrl",11,10}
	};
	return reg;
}

	/// set the current for refclk1 cml driver in the CS
	/// 2'b00 :  I
	/// 2'b01:   I*1.16
	/// 2'b10:   I*1.33
	/// 2'b11:  I*1.48
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::refclk0_cml_bias_ctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{44,"refclk0_cml_bias_ctrl",9,8}
	};
	return reg;
}

	/// Prop CP Replica Opamp compensation control bit.
	/// 0: Default status
	/// 1: Revised status
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cp_op_compensation_switch(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{44,"cp_op_compensation_switch",5,5}
	};
	return reg;
}

	/// Set capacitor of DLF(pF):
	/// 00000: 0.342pF
	/// 00001: 0.684pF
	/// 00010: 1.026pF
	/// 00011: 1.368pF
	/// 00100: 1.71pF
	/// 00101: 2.052pF
	/// 00110: 2.394pF
	/// 00111: 2.736pF
	/// 01000: 3.078pF
	/// 01001: 3.42pF
	/// 01010: 3.762pF
	/// 01011: 4.104pF
	/// 01100: 4.446pF
	/// 01101: 4.788pF
	/// 01110: 5.13pF
	/// 01111: 5.472pF
	/// 10000: 5.814pF
	/// 10001: 6.156pF
	/// 10010: 6.498pF
	/// 10011: 6.84pF
	/// 10100: 7.182pF
	/// 10101: 7.524pF
	/// 10110: 7.866pF
	/// 10111: 8.208pF
	/// 11000: 8.55pF
	/// 11001: 8.892pF
	/// 11010: 9.234pF 
	/// 11011: 9.576pF
	/// 11100: 9.918pF
	/// 11101: 10.26pF
	/// 11110: 10.602pF
	/// 11111: 10.944pF
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cpcintsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{44,"cpcintsel",4,0}
	};
	return reg;
}

	/// set the current for refclk1 cml distributor in the SS.
	/// 2'b00 :  I
	/// 2'b01:   I*1.16
	/// 2'b10:   I*1.33
	/// 2'b11:  I*1.48
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk1_distbiasctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{45,"ssrefclk1_distbiasctrl",15,14}
	};
	return reg;
}

	/// set the current for refclk0 cml distributor in the SS.
	/// 2'b00 :  I
	/// 2'b01:   I*1.16
	/// 2'b10:   I*1.33
	/// 2'b11:  I*1.48
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk0_distbiasctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{45,"ssrefclk0_distbiasctrl",13,12}
	};
	return reg;
}

	/// Set the current for refclk1 cml receiver in the SS.
	/// 2'b00 :  I
	/// 2'b01:   I*1.16
	/// 2'b10:   I*1.33
	/// 2'b11:  I*1.48
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk1_rcvbiasctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{45,"ssrefclk1_rcvbiasctrl",11,10}
	};
	return reg;
}

	/// Set the current for refclk1 cml receiver in the SS.
	/// 2'b00 :  I
	/// 2'b01:   I*1.16
	/// 2'b10:   I*1.33
	/// 2'b11:  I*1.48
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk0_rcvbiasctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{45,"ssrefclk0_rcvbiasctrl",9,8}
	};
	return reg;
}

	/// SS master/slave mode switch.
	/// 0: Master mode.
	/// 1: Slaver mode
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ss_slavemode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{45,"ss_slavemode",7,7}
	};
	return reg;
}

	/// Spare register for clockslice digital used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_spare(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{45,"cs_spare",6,0}
	};
	return reg;
}

	/// For debugging purpose.
	/// [15]: Compare status inversion control. 0=normal; 1=inverse.
	/// [14:13]: Frequency calibration freqcal+/-1 control when freqcal changed.
	/// [12]: Band selection calibration band+/-1 control.
	/// [11]: Band selection calibration de-bouncing control.
	/// [10]: Search method for frequency calibration.
	/// [9:7]: Maximum peak level.
	/// [6:4]: Minimum peak level.
	/// [3:2]: Control which transition counter will output , for debugging.
	/// [1]: Unused for present version, don't configure.
	/// [0]: Fix the FD status 0 for frequency calibration.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_debugging_ctrl1(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{46,"cs_debugging_ctrl1",15,0}
	};
	return reg;
}

	/// choose startup voltage level
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::bg_stu_ref_sel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{47,"bg_stu_ref_sel",14,13}
	};
	return reg;
}

	/// choose icv current mirror bias from local icv generation or bandgap core
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::bg_icv_ref_sel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{47,"bg_icv_ref_sel",12,12}
	};
	return reg;
}

	/// The reference clock counter of loss of lock detector.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lld_ref_freq(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{47,"cs_lld_ref_freq",11,0}
	};
	return reg;
}

	/// temperature compensation ability adjusting register
	/// the bigger the register is, the stronger the compensation ability is
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::tempcompensel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{48,"tempcompensel",15,14}
	};
	return reg;
}

	/// temperature compensation current adjusting register
	/// current = 6.25uA + 12.5uA*lcvco_tempcompensel_current[1:0]
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::tempcompensel_current(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{48,"tempcompensel_current",13,12}
	};
	return reg;
}

	/// The reference clock counter of frequency detector.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_fd_ref_freq(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{48,"cs_fd_ref_freq",11,0}
	};
	return reg;
}

	/// vtune shift adjusting register, adjust the value of vdiv_0p8 and vidv_0p2
	/// 0000: vdiv_0p8 = 0.9V      /   vdiv_0p2 = 0.06V
	/// 0001: vdiv_0p8 = 0.78V    /   vdiv_0p2 = 0.06V
	/// 0010: vdiv_0p8 = 0.66V    /   vdiv_0p2 = 0.06V
	/// 0011: vdiv_0p8 = vtunem  /   vdiv_0p2 = 0.06V
	/// 0100: vdiv_0p8 = 0.9V      /   vdiv_0p2 = 0.18V
	/// 0101: vdiv_0p8 = 0.78V    /   vdiv_0p2 = 0.18V
	/// 0110: vdiv_0p8 = 0.66V    /   vdiv_0p2 = 0.18V
	/// 0111: vdiv_0p8 = vtunem  /   vdiv_0p2 = 0.18V
	/// 1000: vdiv_0p8 = 0.9V      /   vdiv_0p2 = 0.3V
	/// 1001: vdiv_0p8 = 0.78V    /   vdiv_0p2 = 0.3V
	/// 1010: vdiv_0p8 = 0.66V    /   vdiv_0p2 = 0.3V
	/// 1011: vdiv_0p8 = vtunem  /   vdiv_0p2 = 0.3V
	/// 1100: vdiv_0p8 = 0.8V      /   vdiv_0p2 = vtunep
	/// 1101: vdiv_0p8 = 0.78V    /   vdiv_0p2 = vtunep
	/// 1110: vdiv_0p8 = 0.66V    /   vdiv_0p2 = vtunep
	/// 1111: vdiv_0p8 = vtunem  /   vdiv_0p2 = vtunep
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vtuneshift_sel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{49,"vtuneshift_sel",15,12}
	};
	return reg;
}

	/// The feedback clock counter of frequency detector.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_fd_fb_freq(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{49,"cs_fd_fb_freq",11,0}
	};
	return reg;
}

	/// The difference of reference clock counter and feedback clock counter for frequency detector.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_fd_diff_freq(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{50,"cs_fd_diff_freq",12,0}
	};
	return reg;
}

	/// The status of loss of lock.
	/// 0 = incomplete
	/// 1 = complete
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lld_done(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{51,"cs_lld_done",15,15}
	};
	return reg;
}

	/// The difference of reference clock counter and feedback clock counter for loss of lock detector.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lld_diff_freq(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{51,"cs_lld_diff_freq",12,0}
	};
	return reg;
}

	/// The feedback clock counter of loss of lock detector.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_lld_fb_freq(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{52,"cs_lld_fb_freq",11,0}
	};
	return reg;
}

	/// Debugging for purpose. Following internal signals could be read back.
	/// [15]=cs_lcd_done
	/// [14]=cs_pwrdb
	/// [13]=cs_calrstb and the default value is 1.
	/// [12:10]=cs_peak_level and the default value is 100.
	/// [9]=cs_offset_cal
	/// [8:3]=cs_offset and the default value is 0x20.
	/// [2:0]=cs_calib_mode
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_misc_status(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{53,"cs_misc_status",15,0}
	};
	return reg;
}

	/// the status of calibration FSM for debugging purpose. Following internal signals could be read back.
	/// [15]=1'b0
	/// [14:9]=cs_freqcal and the default value is 0x6.
	/// [8:3]=cs_itank and the default value is 0xc.
	/// [2]=fd_status
	/// [1]=cs_trans_warning
	/// [0]=cs_calib_state_err
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_calib_fsm_status(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{54,"cs_calib_fsm_status",15,0}
	};
	return reg;
}

	/// The status of general purpose calibration FSM, for debugging.  Following internal signals could be read back.
	/// [15]=1'b0
	/// [14:12]=cs_bdsel and the default value is 0x1.
	/// [11:6]=cs_gcalib_state_flag
	/// [5:2]=cs_trans_cnt
	/// [1]=cs_gcalib_trans_status and the default value is 0x1.
	/// [0]=cs_gcalib_err
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cs_gcalib_fsm_status(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{55,"cs_gcalib_fsm_status",15,0}
	};
	return reg;
}

	/// SSC modulation type:
	/// 00: down-spreading
	/// ;01: center-spreading
	/// ;10: fixed ppm, codeword = sscamp; 
	/// 11: fixed ppm, codeword = -sscamp;
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssctype(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{56,"ssctype",15,14}
	};
	return reg;
}

	/// Set the SSC modulation period (frequency), by setting the number of reference clock cycles to have one staircase step. Its value can be calculated as follows,
	/// sscfreq= (reference_clock_freq)/(2*M*(sscamp+1)*ssc_modulation_freq)��but SSCFREQ > 9'd0.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::sscfreq(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{56,"sscfreq",8,0}
	};
	return reg;
}

	/// These control bits are just used in SSC mode.
	/// Programs the feedback clock pulse width by 2*Ka*Tvco*��ssc_pulsewidth[1:0] +2��
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssc_pulsewidth(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{57,"ssc_pulsewidth",13,12}
	};
	return reg;
}

	/// CS mode select,
	/// 0: normal mode
	/// 1: SSC mode
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssc_bypassb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{57,"ssc_bypassb",7,7}
	};
	return reg;
}

	/// This configuration variable defines the peak-to-peak SSC modulation frequency deviation, by defining the total number of staircases in half period of SSC.
	/// Its value can be calculated as follows, 
	/// ssctype = 00:
	/// sscamp=floor((ssc_p2p_ppm)/��10��^6 *N/2*32*2^(truncation_bits) )
	/// ssctype = 01:
	///  sscamp=2*floor((ssc_p2p_ppm)/2/��10��^6 *N/2*32*2^(truncation_bits) )
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::sscamp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{57,"sscamp",6,0}
	};
	return reg;
}

	/// Clear SSC generator start and internal counter, high active.
	/// 0: Not clear.
	/// 1: Clear
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssc_gen_clr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{58,"ssc_gen_clr",15,15}
	};
	return reg;
}

	/// Soft reset for Digital SSC generator logic , low active.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssc_gen_soft_rstb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{58,"ssc_gen_soft_rstb",14,14}
	};
	return reg;
}

	/// SSC generator start mode.
	/// 0: Auto mode, start SSC generator by  logic calibration done signal.
	/// 1: Manual mode, start SSC generator by configure register 
	///    SSC_GEN_MANUL_START via software
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssc_gen_start_mode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{58,"ssc_gen_start_mode",13,13}
	};
	return reg;
}

	/// intergral chargepump current step control, 
	///  0 = 20uA per step.
	///  1 = 5uA per step.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cp_i_intchp_tune(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{58,"cp_i_intchp_tune",12,12}
	};
	return reg;
}

	/// PLL wordclk2dig_32b powerdown, active low.
	/// 0: Power down
	/// 1: Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pwrdb_pll0_wordclk2dig_32b(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{58,"pwrdb_pll0_wordclk2dig_32b",11,11}
	};
	return reg;
}

	/// LCVCO Temp compensation circuit power down, active low
	/// 0: Power down
	/// 1: Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvco_tempcompensate_pwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{58,"lcvco_tempcompensate_pwrdb",10,10}
	};
	return reg;
}

	/// These control bit is just used in SSC mode, and decide the clock domain of the digital blocks of SSC Gen.
	/// 0: worked at fbclk2dig domain
	/// 1: worked at refclk2dig domain
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssc_clksel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{58,"ssc_clksel",9,9}
	};
	return reg;
}

	/// Start SSC generator by manual mode, high active.
	/// 0:  Start disable
	/// 1: Start enbale
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssc_gen_manual_start(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{58,"ssc_gen_manual_start",8,8}
	};
	return reg;
}

	/// SSC PI phase setting in manual mode. 
	/// MSB=1 indicates SSC PI is in manual mode. And the 5 LSB bits are the desired SSC PI phase value (binary coded).
	/// MSB=0 indicates SSC PI is auto mode, and is controlled by the internal logic.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssc_phswrite(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{58,"ssc_phswrite",5,0}
	};
	return reg;
}

	/// Read the SSC PI code value in auto mode for debug.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssc_picode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{59,"ssc_picode",4,0}
	};
	return reg;
}

	/// Start to read SSC_PICODE, Clear the start after read by logic(RWW type)
	/// Note: The step read the SSC_PICODE register:
	/// (1) Configure  SSC_PICODE_READ_START = 1'b1
	/// ;(2) Logic clear the SSC_PICODE_READ_START, softeware must wait until SSC_PICODE_READ_START=0
	/// (3)Read Register SSC_PICODE after de-asert SSC_PICODE_READ_START
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssc_picode_read_start(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{60,"ssc_picode_read_start",15,15}
	};
	return reg;
}

	/// Truncation bits of SSC accumulation
	/// 000: 2bits
	/// 001: 3bits
	/// 010: 4bits
	/// 011: 5bits.
	/// 100: 6bits.
	/// Others: reserved
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::sscatt(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{60,"sscatt",14,12}
	};
	return reg;
}

	/// Spare registers for SSC control
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssc_spare(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{60,"ssc_spare",11,10}
	};
	return reg;
}

	/// Feedbk divider output clock pulsewidth modulation
	///  0: pulsewidth equal 2 period of Ka clock  
	///  1: pulsewidth equal 3 period of Ka clock
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::fbkclk_pulsewidth_mod(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{60,"fbkclk_pulsewidth_mod",9,9}
	};
	return reg;
}

	/// SSC block power down control
	///  0: power off   1: power on
	///  Note: should be set to 1 on SSC mode or mode dynamic change between SSC and default
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssc_pwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{60,"ssc_pwrdb",8,8}
	};
	return reg;
}

	/// SSC PI picode MSB signal delay control register,
	/// ssc_picode_delay[1:0] = 00/01/10/11
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssc_picode_delay(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{60,"ssc_picode_delay",7,6}
	};
	return reg;
}

	/// SSC PI output buffer capacitance adjusting register,
	/// piout_caps[1:0] = 00/01/10/11
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::piout_caps(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{60,"piout_caps",5,4}
	};
	return reg;
}

	/// SSC PI pi input driver current adjusting register,
	/// pidrvin_cur[1:0] = 00/01/10/11
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pidrvin_cur(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{60,"pidrvin_cur",3,2}
	};
	return reg;
}

	/// SSC PI input driver capacitance adjusting register
	/// pidrvin_caps[1:0]= 00/01/10/11
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pidrvin_caps(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{60,"pidrvin_caps",1,0}
	};
	return reg;
}

	/// Word clock divider by 2 ( 'W'divider).
	/// 0 = divided by 1 (default)
	/// 1 = divided by 2
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::wordclkdiv2(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{61,"wordclkdiv2",15,15}
	};
	return reg;
}

	/// Word clock divider ratio ( 'J'divider).
	/// 00 = divided by 20
	/// 01 = divided by 10(default)
	/// 10 = divided by 16
	/// 11 = divided by 8
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::wordclkdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{61,"wordclkdiv",14,13}
	};
	return reg;
}

	/// Set divide ratio of wordclkdiv2_16b32b post divider.('V' divider)
	/// 0 = divided by 1 (default)
	/// 1 = divided by 2
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::wordclkdiv2_16b32b(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{61,"wordclkdiv2_16b32b",12,12}
	};
	return reg;
}

	/// Sample Tsensor temperature numbers:
	/// 00 = 16
	/// 01 = 32
	/// 10 = 64
	/// 11 = 128
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::meas_num(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{62,"meas_num",15,14}
	};
	return reg;
}

	/// clock divide parameter to get 1MHz for Tsensor
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::temp_clk_div(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{62,"temp_clk_div",13,5}
	};
	return reg;
}

	/// Enable Tsensor measuring tempertature
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::tsen_temp_en(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{62,"tsen_temp_en",4,4}
	};
	return reg;
}

	/// Tsensor converting timing select:
	/// 00 = 0.512ms
	/// 01 = 0.256ms
	/// 10 = 1.024ms
	/// 11 =2.048ms
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::tsen_temp_ct_sel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{62,"tsen_temp_ct_sel",3,2}
	};
	return reg;
}

	/// Tsensor Ouput chip current temperature
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::chip_temp_out(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{63,"chip_temp_out",15,6}
	};
	return reg;
}
bool
CS_clkRegs::_REG_INFO::get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos){
	reg_infos.clear();
	switch(csr){
		case 0:
			reg_infos.push_back(cspwrdb().reg_info);
			reg_infos.push_back(ssrefclk0div2sel().reg_info);
			reg_infos.push_back(ssrefclk1div2sel().reg_info);
			reg_infos.push_back(sscmosrefclksel().reg_info);
			reg_infos.push_back(refclksel().reg_info);
			reg_infos.push_back(lifeclksel().reg_info);
			reg_infos.push_back(coreclksel().reg_info);
			reg_infos.push_back(lpfcap().reg_info);
			reg_infos.push_back(lpfres().reg_info);
			break;
		case 1:
			reg_infos.push_back(cmldiv().reg_info);
			reg_infos.push_back(fbdivp().reg_info);
			reg_infos.push_back(fbdivs().reg_info);
			reg_infos.push_back(refclkdiv().reg_info);
			break;
		case 2:
			reg_infos.push_back(lifeclk2digdiv().reg_info);
			reg_infos.push_back(wordclk2digdiv().reg_info);
			reg_infos.push_back(lcvcololthr().reg_info);
			reg_infos.push_back(lcvcolocthr().reg_info);
			reg_infos.push_back(lcvcololmode().reg_info);
			reg_infos.push_back(lcvcooutoflock().reg_info);
			reg_infos.push_back(lossoflcvcoclk().reg_info);
			break;
		case 3:
			reg_infos.push_back(pllpwrdb().reg_info);
			reg_infos.push_back(pfdupdnswap().reg_info);
			reg_infos.push_back(pfdforceup().reg_info);
			reg_infos.push_back(pfdforcedn().reg_info);
			reg_infos.push_back(pfdpulsewidth().reg_info);
			reg_infos.push_back(cpauxres().reg_info);
			reg_infos.push_back(cpcmfbpwrdb().reg_info);
			reg_infos.push_back(cpintegcppwrdb().reg_info);
			reg_infos.push_back(cprdeg().reg_info);
			reg_infos.push_back(cpvrefpropsel().reg_info);
			reg_infos.push_back(cpreflvl().reg_info);
			break;
		case 4:
			reg_infos.push_back(cmldivkbvcmsel().reg_info);
			reg_infos.push_back(cp_i_propchp_tune().reg_info);
			reg_infos.push_back(cpcurrentint().reg_info);
			reg_infos.push_back(cpcurrent().reg_info);
			reg_infos.push_back(cprzerocmfb().reg_info);
			break;
		case 5:
			reg_infos.push_back(cpdlfmuxsel().reg_info);
			reg_infos.push_back(cpspare2to0().reg_info);
			reg_infos.push_back(dlfpwrdb().reg_info);
			reg_infos.push_back(dlfextramimcap().reg_info);
			reg_infos.push_back(dlftstpwrdb().reg_info);
			reg_infos.push_back(dlfcmfbpwrdb().reg_info);
			reg_infos.push_back(dlfshdelsel().reg_info);
			reg_infos.push_back(dlfseldtb().reg_info);
			reg_infos.push_back(dlfshcapsel().reg_info);
			break;
		case 6:
			reg_infos.push_back(cmlbufoutbiassel().reg_info);
			reg_infos.push_back(cmldivbiascal().reg_info);
			reg_infos.push_back(lcvcospare().reg_info);
			reg_infos.push_back(lcvcoselpeaklvl().reg_info);
			break;
		case 7:
			reg_infos.push_back(lcvco_pwron_force_en().reg_info);
			reg_infos.push_back(lcvcobandsel().reg_info);
			reg_infos.push_back(lcvcofreqcal().reg_info);
			reg_infos.push_back(lcvcoitank().reg_info);
			break;
		case 8:
			reg_infos.push_back(hsclkfrclkspinepwrdb().reg_info);
			reg_infos.push_back(hsclkfromsspwrdb().reg_info);
			reg_infos.push_back(hsclktosspwrdb().reg_info);
			reg_infos.push_back(hsclkfromcsbiasctrl().reg_info);
			reg_infos.push_back(hsclkfromssbiasctrl().reg_info);
			reg_infos.push_back(hsclktossbiasctrl().reg_info);
			reg_infos.push_back(hsclkreploadctrl().reg_info);
			reg_infos.push_back(hsclkreprefsel().reg_info);
			break;
		case 9:
			reg_infos.push_back(hsclkspare().reg_info);
			reg_infos.push_back(biascmupwrdb().reg_info);
			reg_infos.push_back(biascvcal().reg_info);
			break;
		case 10:
			reg_infos.push_back(csrxbiasbackupgen().reg_info);
			reg_infos.push_back(csspare().reg_info);
			break;
		case 11:
			reg_infos.push_back(vregpwrdb().reg_info);
			reg_infos.push_back(vregcapsel().reg_info);
			reg_infos.push_back(vregselfbleed().reg_info);
			reg_infos.push_back(vregplllvl().reg_info);
			break;
		case 12:
			reg_infos.push_back(calpwrdb().reg_info);
			reg_infos.push_back(calrstb().reg_info);
			reg_infos.push_back(cs_post_lckchk_bypass().reg_info);
			reg_infos.push_back(cs_initamp_calib_bypass().reg_info);
			reg_infos.push_back(cslowoffcal().reg_info);
			reg_infos.push_back(cslowoffsetctrl().reg_info);
			break;
		case 13:
			reg_infos.push_back(lcvcocalmode().reg_info);
			reg_infos.push_back(lcvcocalctrl().reg_info);
			reg_infos.push_back(ptatcalout().reg_info);
			reg_infos.push_back(cvcalout().reg_info);
			reg_infos.push_back(comparestatus().reg_info);
			reg_infos.push_back(dtbout().reg_info);
			reg_infos.push_back(lcvcocaldone().reg_info);
			reg_infos.push_back(lcvcocalerr().reg_info);
			reg_infos.push_back(lcvcocalstatus().reg_info);
			break;
		case 14:
			reg_infos.push_back(csdtbsel().reg_info);
			reg_infos.push_back(vregatbctrl().reg_info);
			reg_infos.push_back(csatbfinalsel().reg_info);
			break;
		case 15:
			reg_infos.push_back(csatbsel23to16().reg_info);
			reg_infos.push_back(ssspare().reg_info);
			break;
		case 16:
			reg_infos.push_back(sspwrdb().reg_info);
			reg_infos.push_back(ssrefclk0pwrdb().reg_info);
			reg_infos.push_back(ssrefclk1pwrdb().reg_info);
			reg_infos.push_back(sshsclkss2cspwrdb().reg_info);
			reg_infos.push_back(sshsclkcs2sspwrdb().reg_info);
			reg_infos.push_back(ssrefclk0cmldivpwrdb().reg_info);
			reg_infos.push_back(ssrefclk0atten().reg_info);
			reg_infos.push_back(ssrefclk1cmldivpwrdb().reg_info);
			reg_infos.push_back(ssrefclk1atten().reg_info);
			break;
		case 17:
			reg_infos.push_back(bg600mvlvccresdiv().reg_info);
			reg_infos.push_back(bgccen().reg_info);
			reg_infos.push_back(bgcven().reg_info);
			reg_infos.push_back(bgpaten().reg_info);
			reg_infos.push_back(bgforcestart().reg_info);
			reg_infos.push_back(bgstartbypass().reg_info);
			reg_infos.push_back(bgbypass().reg_info);
			break;
		case 18:
			reg_infos.push_back(hvvbgccin().reg_info);
			reg_infos.push_back(vbgreflvl().reg_info);
			reg_infos.push_back(hvvbgptatin().reg_info);
			reg_infos.push_back(vbgptatlvl().reg_info);
			reg_infos.push_back(biasselptatmix().reg_info);
			break;
		case 19:
			reg_infos.push_back(ssatbsel().reg_info);
			break;
		case 20:
			reg_infos.push_back(cs_lld_clr().reg_info);
			reg_infos.push_back(cs_fd_clr().reg_info);
			reg_infos.push_back(cs_calib_clr().reg_info);
			reg_infos.push_back(cs_lcd_start().reg_info);
			reg_infos.push_back(cs_lld_start().reg_info);
			reg_infos.push_back(cs_calib_start().reg_info);
			reg_infos.push_back(cs_lcd_enable().reg_info);
			reg_infos.push_back(cs_lld_enable().reg_info);
			reg_infos.push_back(cs_calib_enable().reg_info);
			reg_infos.push_back(cs_lcd_soft_rst_n().reg_info);
			reg_infos.push_back(cs_lld_soft_rst_n().reg_info);
			reg_infos.push_back(cs_calib_soft_rst_n().reg_info);
			reg_infos.push_back(cs_glb_soft_rst_n().reg_info);
			break;
		case 21:
			reg_infos.push_back(csatbsel15to0().reg_info);
			break;
		case 22:
			reg_infos.push_back(cs_direction_ctrl().reg_info);
			break;
		case 23:
			reg_infos.push_back(cs_calib_mode_bdsel().reg_info);
			reg_infos.push_back(cs_calib_mode_freqcal().reg_info);
			reg_infos.push_back(cs_calib_mode_minamp().reg_info);
			reg_infos.push_back(cs_calib_mode_initamp().reg_info);
			reg_infos.push_back(cs_calib_mode_offset().reg_info);
			break;
		case 24:
			reg_infos.push_back(cs_calib_mode_lckchk().reg_info);
			reg_infos.push_back(cs_calib_mode_maxamp().reg_info);
			break;
		case 25:
			reg_infos.push_back(cs_ctrl_code_min_initamp().reg_info);
			reg_infos.push_back(cs_ctrl_code_max_offset().reg_info);
			reg_infos.push_back(cs_ctrl_code_min_offset().reg_info);
			break;
		case 26:
			reg_infos.push_back(cs_ctrl_code_max_minamp().reg_info);
			reg_infos.push_back(cs_ctrl_code_min_minamp().reg_info);
			reg_infos.push_back(cs_ctrl_code_max_initamp().reg_info);
			break;
		case 27:
			reg_infos.push_back(cs_ctrl_code_min_bdsel().reg_info);
			reg_infos.push_back(cs_ctrl_code_min_freqcal().reg_info);
			break;
		case 28:
			reg_infos.push_back(cs_ctrl_code_max_maxamp().reg_info);
			reg_infos.push_back(cs_ctrl_code_min_maxamp().reg_info);
			reg_infos.push_back(cs_ctrl_code_max_bdsel().reg_info);
			break;
		case 29:
			reg_infos.push_back(cs_ctrl_code_max_lckchk().reg_info);
			reg_infos.push_back(cs_ctrl_code_min_lckchk().reg_info);
			break;
		case 30:
			reg_infos.push_back(cs_init_code_amp().reg_info);
			reg_infos.push_back(cs_init_code_offset().reg_info);
			reg_infos.push_back(cs_init_code_bdsel().reg_info);
			break;
		case 31:
			reg_infos.push_back(cs_init_code_maxamp().reg_info);
			reg_infos.push_back(cs_init_code_freqcal().reg_info);
			reg_infos.push_back(cs_init_code_minamp().reg_info);
			break;
		case 32:
			reg_infos.push_back(cs_ctrl_code_max_freqcal().reg_info);
			reg_infos.push_back(cs_init_code_lckchk().reg_info);
			break;
		case 33:
			reg_infos.push_back(cs_trans_max_freqcal().reg_info);
			reg_infos.push_back(cs_trans_max_minamp().reg_info);
			reg_infos.push_back(cs_trans_max_initamp().reg_info);
			reg_infos.push_back(cs_trans_max_offset().reg_info);
			break;
		case 34:
			reg_infos.push_back(cs_trans_max_lckchk().reg_info);
			reg_infos.push_back(cs_trans_max_maxamp().reg_info);
			reg_infos.push_back(cs_trans_max_bdsel().reg_info);
			break;
		case 35:
			reg_infos.push_back(cs_fd_threshold().reg_info);
			reg_infos.push_back(cs_meas_fd_wait().reg_info);
			break;
		case 36:
			reg_infos.push_back(cs_fd_ref_cnt_dv().reg_info);
			reg_infos.push_back(cs_fd_ref_cnt_lv().reg_info);
			break;
		case 37:
			reg_infos.push_back(cs_fd_fb_cnt_dv().reg_info);
			reg_infos.push_back(cs_fd_fb_cnt_lv().reg_info);
			break;
		case 38:
			reg_infos.push_back(cs_timer_value().reg_info);
			reg_infos.push_back(cs_timer_div_value().reg_info);
			reg_infos.push_back(cs_timer_div_en().reg_info);
			reg_infos.push_back(cs_timer_stop().reg_info);
			break;
		case 39:
			reg_infos.push_back(cs_lld_fb_div_ratio().reg_info);
			reg_infos.push_back(cs_lld_once().reg_info);
			break;
		case 40:
			reg_infos.push_back(cs_lld_ref_cnt_dv().reg_info);
			reg_infos.push_back(cs_lld_ref_cnt_lv().reg_info);
			break;
		case 41:
			reg_infos.push_back(cs_lld_fb_cnt_dv().reg_info);
			reg_infos.push_back(cs_lld_fb_cnt_lv().reg_info);
			break;
		case 42:
			reg_infos.push_back(cs_lcd_fb_div_ratio().reg_info);
			reg_infos.push_back(cs_lcd_override().reg_info);
			break;
		case 43:
			reg_infos.push_back(ssc_freeze().reg_info);
			reg_infos.push_back(ssc_freeze_mode().reg_info);
			reg_infos.push_back(ssc_freeze_en_sel().reg_info);
			reg_infos.push_back(cs_lcd_fb_cnt_lv().reg_info);
			break;
		case 44:
			reg_infos.push_back(cp_dlf_resfdbkpwrdb().reg_info);
			reg_infos.push_back(cp_dlf_sample_edge_switch().reg_info);
			reg_infos.push_back(cp_dlf_cmfb_switch().reg_info);
			reg_infos.push_back(refclk1_cml_bias_ctrl().reg_info);
			reg_infos.push_back(refclk0_cml_bias_ctrl().reg_info);
			reg_infos.push_back(cp_op_compensation_switch().reg_info);
			reg_infos.push_back(cpcintsel().reg_info);
			break;
		case 45:
			reg_infos.push_back(ssrefclk1_distbiasctrl().reg_info);
			reg_infos.push_back(ssrefclk0_distbiasctrl().reg_info);
			reg_infos.push_back(ssrefclk1_rcvbiasctrl().reg_info);
			reg_infos.push_back(ssrefclk0_rcvbiasctrl().reg_info);
			reg_infos.push_back(ss_slavemode().reg_info);
			reg_infos.push_back(cs_spare().reg_info);
			break;
		case 46:
			reg_infos.push_back(cs_debugging_ctrl1().reg_info);
			break;
		case 47:
			reg_infos.push_back(bg_stu_ref_sel().reg_info);
			reg_infos.push_back(bg_icv_ref_sel().reg_info);
			reg_infos.push_back(cs_lld_ref_freq().reg_info);
			break;
		case 48:
			reg_infos.push_back(tempcompensel().reg_info);
			reg_infos.push_back(tempcompensel_current().reg_info);
			reg_infos.push_back(cs_fd_ref_freq().reg_info);
			break;
		case 49:
			reg_infos.push_back(vtuneshift_sel().reg_info);
			reg_infos.push_back(cs_fd_fb_freq().reg_info);
			break;
		case 50:
			reg_infos.push_back(cs_fd_diff_freq().reg_info);
			break;
		case 51:
			reg_infos.push_back(cs_lld_done().reg_info);
			reg_infos.push_back(cs_lld_diff_freq().reg_info);
			break;
		case 52:
			reg_infos.push_back(cs_lld_fb_freq().reg_info);
			break;
		case 53:
			reg_infos.push_back(cs_misc_status().reg_info);
			break;
		case 54:
			reg_infos.push_back(cs_calib_fsm_status().reg_info);
			break;
		case 55:
			reg_infos.push_back(cs_gcalib_fsm_status().reg_info);
			break;
		case 56:
			reg_infos.push_back(ssctype().reg_info);
			reg_infos.push_back(sscfreq().reg_info);
			break;
		case 57:
			reg_infos.push_back(ssc_pulsewidth().reg_info);
			reg_infos.push_back(ssc_bypassb().reg_info);
			reg_infos.push_back(sscamp().reg_info);
			break;
		case 58:
			reg_infos.push_back(ssc_gen_clr().reg_info);
			reg_infos.push_back(ssc_gen_soft_rstb().reg_info);
			reg_infos.push_back(ssc_gen_start_mode().reg_info);
			reg_infos.push_back(cp_i_intchp_tune().reg_info);
			reg_infos.push_back(pwrdb_pll0_wordclk2dig_32b().reg_info);
			reg_infos.push_back(lcvco_tempcompensate_pwrdb().reg_info);
			reg_infos.push_back(ssc_clksel().reg_info);
			reg_infos.push_back(ssc_gen_manual_start().reg_info);
			reg_infos.push_back(ssc_phswrite().reg_info);
			break;
		case 59:
			reg_infos.push_back(ssc_picode().reg_info);
			break;
		case 60:
			reg_infos.push_back(ssc_picode_read_start().reg_info);
			reg_infos.push_back(sscatt().reg_info);
			reg_infos.push_back(ssc_spare().reg_info);
			reg_infos.push_back(fbkclk_pulsewidth_mod().reg_info);
			reg_infos.push_back(ssc_pwrdb().reg_info);
			reg_infos.push_back(ssc_picode_delay().reg_info);
			reg_infos.push_back(piout_caps().reg_info);
			reg_infos.push_back(pidrvin_cur().reg_info);
			reg_infos.push_back(pidrvin_caps().reg_info);
			break;
		case 61:
			reg_infos.push_back(wordclkdiv2().reg_info);
			reg_infos.push_back(wordclkdiv().reg_info);
			reg_infos.push_back(wordclkdiv2_16b32b().reg_info);
			break;
		case 62:
			reg_infos.push_back(meas_num().reg_info);
			reg_infos.push_back(temp_clk_div().reg_info);
			reg_infos.push_back(tsen_temp_en().reg_info);
			reg_infos.push_back(tsen_temp_ct_sel().reg_info);
			break;
		case 63:
			reg_infos.push_back(chip_temp_out().reg_info);
			break;
		default:
			break;
	}
	return (reg_infos.size()>0);
}


CS_clkRegs&
CS_clkRegs::setcspwrdb(uint val){
	fill_csr_bits(val,REG_INFO.cspwrdb());	//CSR0[15:15]
	return *this;
}
uint
CS_clkRegs::getcspwrdb(){
	return get_csr_bits(REG_INFO.cspwrdb());	//CSR0[15:15]
}

CS_clkRegs&
CS_clkRegs::setssrefclk0div2sel(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk0div2sel());	//CSR0[14:14]
	return *this;
}
uint
CS_clkRegs::getssrefclk0div2sel(){
	return get_csr_bits(REG_INFO.ssrefclk0div2sel());	//CSR0[14:14]
}

CS_clkRegs&
CS_clkRegs::setssrefclk1div2sel(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk1div2sel());	//CSR0[13:13]
	return *this;
}
uint
CS_clkRegs::getssrefclk1div2sel(){
	return get_csr_bits(REG_INFO.ssrefclk1div2sel());	//CSR0[13:13]
}

CS_clkRegs&
CS_clkRegs::setsscmosrefclksel(uint val){
	fill_csr_bits(val,REG_INFO.sscmosrefclksel());	//CSR0[12:12]
	return *this;
}
uint
CS_clkRegs::getsscmosrefclksel(){
	return get_csr_bits(REG_INFO.sscmosrefclksel());	//CSR0[12:12]
}

CS_clkRegs&
CS_clkRegs::setrefclksel(uint val){
	fill_csr_bits(val,REG_INFO.refclksel());	//CSR0[11:11]
	return *this;
}
uint
CS_clkRegs::getrefclksel(){
	return get_csr_bits(REG_INFO.refclksel());	//CSR0[11:11]
}

CS_clkRegs&
CS_clkRegs::setlifeclksel(uint val){
	fill_csr_bits(val,REG_INFO.lifeclksel());	//CSR0[10:10]
	return *this;
}
uint
CS_clkRegs::getlifeclksel(){
	return get_csr_bits(REG_INFO.lifeclksel());	//CSR0[10:10]
}

CS_clkRegs&
CS_clkRegs::setcoreclksel(uint val){
	fill_csr_bits(val,REG_INFO.coreclksel());	//CSR0[9:9]
	return *this;
}
uint
CS_clkRegs::getcoreclksel(){
	return get_csr_bits(REG_INFO.coreclksel());	//CSR0[9:9]
}

CS_clkRegs&
CS_clkRegs::setlpfcap(uint val){
	fill_csr_bits(val,REG_INFO.lpfcap());	//CSR0[7:4]
	return *this;
}
uint
CS_clkRegs::getlpfcap(){
	return get_csr_bits(REG_INFO.lpfcap());	//CSR0[7:4]
}

CS_clkRegs&
CS_clkRegs::setlpfres(uint val){
	fill_csr_bits(val,REG_INFO.lpfres());	//CSR0[3:0]
	return *this;
}
uint
CS_clkRegs::getlpfres(){
	return get_csr_bits(REG_INFO.lpfres());	//CSR0[3:0]
}

CS_clkRegs&
CS_clkRegs::setcmldiv(uint val){
	fill_csr_bits(val,REG_INFO.cmldiv());	//CSR1[15:14]
	return *this;
}
uint
CS_clkRegs::getcmldiv(){
	return get_csr_bits(REG_INFO.cmldiv());	//CSR1[15:14]
}

CS_clkRegs&
CS_clkRegs::setfbdivp(uint val){
	fill_csr_bits(val,REG_INFO.fbdivp());	//CSR1[13:8]
	return *this;
}
uint
CS_clkRegs::getfbdivp(){
	return get_csr_bits(REG_INFO.fbdivp());	//CSR1[13:8]
}

CS_clkRegs&
CS_clkRegs::setfbdivs(uint val){
	fill_csr_bits(val,REG_INFO.fbdivs());	//CSR1[7:2]
	return *this;
}
uint
CS_clkRegs::getfbdivs(){
	return get_csr_bits(REG_INFO.fbdivs());	//CSR1[7:2]
}

CS_clkRegs&
CS_clkRegs::setrefclkdiv(uint val){
	fill_csr_bits(val,REG_INFO.refclkdiv());	//CSR1[1:0]
	return *this;
}
uint
CS_clkRegs::getrefclkdiv(){
	return get_csr_bits(REG_INFO.refclkdiv());	//CSR1[1:0]
}

CS_clkRegs&
CS_clkRegs::setlifeclk2digdiv(uint val){
	fill_csr_bits(val,REG_INFO.lifeclk2digdiv());	//CSR2[15:14]
	return *this;
}
uint
CS_clkRegs::getlifeclk2digdiv(){
	return get_csr_bits(REG_INFO.lifeclk2digdiv());	//CSR2[15:14]
}

CS_clkRegs&
CS_clkRegs::setwordclk2digdiv(uint val){
	fill_csr_bits(val,REG_INFO.wordclk2digdiv());	//CSR2[13:12]
	return *this;
}
uint
CS_clkRegs::getwordclk2digdiv(){
	return get_csr_bits(REG_INFO.wordclk2digdiv());	//CSR2[13:12]
}

CS_clkRegs&
CS_clkRegs::setlcvcololthr(uint val){
	fill_csr_bits(val,REG_INFO.lcvcololthr());	//CSR2[10:6]
	return *this;
}
uint
CS_clkRegs::getlcvcololthr(){
	return get_csr_bits(REG_INFO.lcvcololthr());	//CSR2[10:6]
}

CS_clkRegs&
CS_clkRegs::setlcvcolocthr(uint val){
	fill_csr_bits(val,REG_INFO.lcvcolocthr());	//CSR2[5:3]
	return *this;
}
uint
CS_clkRegs::getlcvcolocthr(){
	return get_csr_bits(REG_INFO.lcvcolocthr());	//CSR2[5:3]
}

CS_clkRegs&
CS_clkRegs::setlcvcololmode(uint val){
	fill_csr_bits(val,REG_INFO.lcvcololmode());	//CSR2[2:2]
	return *this;
}
uint
CS_clkRegs::getlcvcololmode(){
	return get_csr_bits(REG_INFO.lcvcololmode());	//CSR2[2:2]
}

uint
CS_clkRegs::getlcvcooutoflock(){
	return get_csr_bits(REG_INFO.lcvcooutoflock());	//CSR2[1:1]
}

uint
CS_clkRegs::getlossoflcvcoclk(){
	return get_csr_bits(REG_INFO.lossoflcvcoclk());	//CSR2[0:0]
}

CS_clkRegs&
CS_clkRegs::setpllpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pllpwrdb());	//CSR3[15:15]
	return *this;
}
uint
CS_clkRegs::getpllpwrdb(){
	return get_csr_bits(REG_INFO.pllpwrdb());	//CSR3[15:15]
}

CS_clkRegs&
CS_clkRegs::setpfdupdnswap(uint val){
	fill_csr_bits(val,REG_INFO.pfdupdnswap());	//CSR3[14:14]
	return *this;
}
uint
CS_clkRegs::getpfdupdnswap(){
	return get_csr_bits(REG_INFO.pfdupdnswap());	//CSR3[14:14]
}

CS_clkRegs&
CS_clkRegs::setpfdforceup(uint val){
	fill_csr_bits(val,REG_INFO.pfdforceup());	//CSR3[13:13]
	return *this;
}
uint
CS_clkRegs::getpfdforceup(){
	return get_csr_bits(REG_INFO.pfdforceup());	//CSR3[13:13]
}

CS_clkRegs&
CS_clkRegs::setpfdforcedn(uint val){
	fill_csr_bits(val,REG_INFO.pfdforcedn());	//CSR3[12:12]
	return *this;
}
uint
CS_clkRegs::getpfdforcedn(){
	return get_csr_bits(REG_INFO.pfdforcedn());	//CSR3[12:12]
}

CS_clkRegs&
CS_clkRegs::setpfdpulsewidth(uint val){
	fill_csr_bits(val,REG_INFO.pfdpulsewidth());	//CSR3[11:10]
	return *this;
}
uint
CS_clkRegs::getpfdpulsewidth(){
	return get_csr_bits(REG_INFO.pfdpulsewidth());	//CSR3[11:10]
}

CS_clkRegs&
CS_clkRegs::setcpauxres(uint val){
	fill_csr_bits(val,REG_INFO.cpauxres());	//CSR3[9:8]
	return *this;
}
uint
CS_clkRegs::getcpauxres(){
	return get_csr_bits(REG_INFO.cpauxres());	//CSR3[9:8]
}

CS_clkRegs&
CS_clkRegs::setcpcmfbpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.cpcmfbpwrdb());	//CSR3[7:7]
	return *this;
}
uint
CS_clkRegs::getcpcmfbpwrdb(){
	return get_csr_bits(REG_INFO.cpcmfbpwrdb());	//CSR3[7:7]
}

CS_clkRegs&
CS_clkRegs::setcpintegcppwrdb(uint val){
	fill_csr_bits(val,REG_INFO.cpintegcppwrdb());	//CSR3[6:6]
	return *this;
}
uint
CS_clkRegs::getcpintegcppwrdb(){
	return get_csr_bits(REG_INFO.cpintegcppwrdb());	//CSR3[6:6]
}

CS_clkRegs&
CS_clkRegs::setcprdeg(uint val){
	fill_csr_bits(val,REG_INFO.cprdeg());	//CSR3[5:4]
	return *this;
}
uint
CS_clkRegs::getcprdeg(){
	return get_csr_bits(REG_INFO.cprdeg());	//CSR3[5:4]
}

CS_clkRegs&
CS_clkRegs::setcpvrefpropsel(uint val){
	fill_csr_bits(val,REG_INFO.cpvrefpropsel());	//CSR3[3:3]
	return *this;
}
uint
CS_clkRegs::getcpvrefpropsel(){
	return get_csr_bits(REG_INFO.cpvrefpropsel());	//CSR3[3:3]
}

CS_clkRegs&
CS_clkRegs::setcpreflvl(uint val){
	fill_csr_bits(val,REG_INFO.cpreflvl());	//CSR3[2:0]
	return *this;
}
uint
CS_clkRegs::getcpreflvl(){
	return get_csr_bits(REG_INFO.cpreflvl());	//CSR3[2:0]
}

CS_clkRegs&
CS_clkRegs::setcmldivkbvcmsel(uint val){
	fill_csr_bits(val,REG_INFO.cmldivkbvcmsel());	//CSR4[15:14]
	return *this;
}
uint
CS_clkRegs::getcmldivkbvcmsel(){
	return get_csr_bits(REG_INFO.cmldivkbvcmsel());	//CSR4[15:14]
}

CS_clkRegs&
CS_clkRegs::setcp_i_propchp_tune(uint val){
	fill_csr_bits(val,REG_INFO.cp_i_propchp_tune());	//CSR4[13:13]
	return *this;
}
uint
CS_clkRegs::getcp_i_propchp_tune(){
	return get_csr_bits(REG_INFO.cp_i_propchp_tune());	//CSR4[13:13]
}

CS_clkRegs&
CS_clkRegs::setcpcurrentint(uint val){
	fill_csr_bits(val,REG_INFO.cpcurrentint());	//CSR4[12:10]
	return *this;
}
uint
CS_clkRegs::getcpcurrentint(){
	return get_csr_bits(REG_INFO.cpcurrentint());	//CSR4[12:10]
}

CS_clkRegs&
CS_clkRegs::setcpcurrent(uint val){
	fill_csr_bits(val,REG_INFO.cpcurrent());	//CSR4[9:4]
	return *this;
}
uint
CS_clkRegs::getcpcurrent(){
	return get_csr_bits(REG_INFO.cpcurrent());	//CSR4[9:4]
}

CS_clkRegs&
CS_clkRegs::setcprzerocmfb(uint val){
	fill_csr_bits(val,REG_INFO.cprzerocmfb());	//CSR4[3:0]
	return *this;
}
uint
CS_clkRegs::getcprzerocmfb(){
	return get_csr_bits(REG_INFO.cprzerocmfb());	//CSR4[3:0]
}

CS_clkRegs&
CS_clkRegs::setcpdlfmuxsel(uint val){
	fill_csr_bits(val,REG_INFO.cpdlfmuxsel());	//CSR5[15:15]
	return *this;
}
uint
CS_clkRegs::getcpdlfmuxsel(){
	return get_csr_bits(REG_INFO.cpdlfmuxsel());	//CSR5[15:15]
}

CS_clkRegs&
CS_clkRegs::setcpspare2to0(uint val){
	fill_csr_bits(val,REG_INFO.cpspare2to0());	//CSR5[14:12]
	return *this;
}
uint
CS_clkRegs::getcpspare2to0(){
	return get_csr_bits(REG_INFO.cpspare2to0());	//CSR5[14:12]
}

CS_clkRegs&
CS_clkRegs::setdlfpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.dlfpwrdb());	//CSR5[11:11]
	return *this;
}
uint
CS_clkRegs::getdlfpwrdb(){
	return get_csr_bits(REG_INFO.dlfpwrdb());	//CSR5[11:11]
}

CS_clkRegs&
CS_clkRegs::setdlfextramimcap(uint val){
	fill_csr_bits(val,REG_INFO.dlfextramimcap());	//CSR5[10:10]
	return *this;
}
uint
CS_clkRegs::getdlfextramimcap(){
	return get_csr_bits(REG_INFO.dlfextramimcap());	//CSR5[10:10]
}

CS_clkRegs&
CS_clkRegs::setdlftstpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.dlftstpwrdb());	//CSR5[9:9]
	return *this;
}
uint
CS_clkRegs::getdlftstpwrdb(){
	return get_csr_bits(REG_INFO.dlftstpwrdb());	//CSR5[9:9]
}

CS_clkRegs&
CS_clkRegs::setdlfcmfbpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.dlfcmfbpwrdb());	//CSR5[8:8]
	return *this;
}
uint
CS_clkRegs::getdlfcmfbpwrdb(){
	return get_csr_bits(REG_INFO.dlfcmfbpwrdb());	//CSR5[8:8]
}

CS_clkRegs&
CS_clkRegs::setdlfshdelsel(uint val){
	fill_csr_bits(val,REG_INFO.dlfshdelsel());	//CSR5[7:7]
	return *this;
}
uint
CS_clkRegs::getdlfshdelsel(){
	return get_csr_bits(REG_INFO.dlfshdelsel());	//CSR5[7:7]
}

CS_clkRegs&
CS_clkRegs::setdlfseldtb(uint val){
	fill_csr_bits(val,REG_INFO.dlfseldtb());	//CSR5[6:2]
	return *this;
}
uint
CS_clkRegs::getdlfseldtb(){
	return get_csr_bits(REG_INFO.dlfseldtb());	//CSR5[6:2]
}

CS_clkRegs&
CS_clkRegs::setdlfshcapsel(uint val){
	fill_csr_bits(val,REG_INFO.dlfshcapsel());	//CSR5[1:0]
	return *this;
}
uint
CS_clkRegs::getdlfshcapsel(){
	return get_csr_bits(REG_INFO.dlfshcapsel());	//CSR5[1:0]
}

CS_clkRegs&
CS_clkRegs::setcmlbufoutbiassel(uint val){
	fill_csr_bits(val,REG_INFO.cmlbufoutbiassel());	//CSR6[15:14]
	return *this;
}
uint
CS_clkRegs::getcmlbufoutbiassel(){
	return get_csr_bits(REG_INFO.cmlbufoutbiassel());	//CSR6[15:14]
}

CS_clkRegs&
CS_clkRegs::setcmldivbiascal(uint val){
	fill_csr_bits(val,REG_INFO.cmldivbiascal());	//CSR6[13:8]
	return *this;
}
uint
CS_clkRegs::getcmldivbiascal(){
	return get_csr_bits(REG_INFO.cmldivbiascal());	//CSR6[13:8]
}

CS_clkRegs&
CS_clkRegs::setlcvcospare(uint val){
	fill_csr_bits(val,REG_INFO.lcvcospare());	//CSR6[7:4]
	return *this;
}
uint
CS_clkRegs::getlcvcospare(){
	return get_csr_bits(REG_INFO.lcvcospare());	//CSR6[7:4]
}

CS_clkRegs&
CS_clkRegs::setlcvcoselpeaklvl(uint val){
	fill_csr_bits(val,REG_INFO.lcvcoselpeaklvl());	//CSR6[2:0]
	return *this;
}
uint
CS_clkRegs::getlcvcoselpeaklvl(){
	return get_csr_bits(REG_INFO.lcvcoselpeaklvl());	//CSR6[2:0]
}

CS_clkRegs&
CS_clkRegs::setlcvco_pwron_force_en(uint val){
	fill_csr_bits(val,REG_INFO.lcvco_pwron_force_en());	//CSR7[15:15]
	return *this;
}
uint
CS_clkRegs::getlcvco_pwron_force_en(){
	return get_csr_bits(REG_INFO.lcvco_pwron_force_en());	//CSR7[15:15]
}

CS_clkRegs&
CS_clkRegs::setlcvcobandsel(uint val){
	fill_csr_bits(val,REG_INFO.lcvcobandsel());	//CSR7[14:12]
	return *this;
}
uint
CS_clkRegs::getlcvcobandsel(){
	return get_csr_bits(REG_INFO.lcvcobandsel());	//CSR7[14:12]
}

CS_clkRegs&
CS_clkRegs::setlcvcofreqcal(uint val){
	fill_csr_bits(val,REG_INFO.lcvcofreqcal());	//CSR7[10:5]
	return *this;
}
uint
CS_clkRegs::getlcvcofreqcal(){
	return get_csr_bits(REG_INFO.lcvcofreqcal());	//CSR7[10:5]
}

CS_clkRegs&
CS_clkRegs::setlcvcoitank(uint val){
	fill_csr_bits(val,REG_INFO.lcvcoitank());	//CSR7[4:0]
	return *this;
}
uint
CS_clkRegs::getlcvcoitank(){
	return get_csr_bits(REG_INFO.lcvcoitank());	//CSR7[4:0]
}

CS_clkRegs&
CS_clkRegs::sethsclkfrclkspinepwrdb(uint val){
	fill_csr_bits(val,REG_INFO.hsclkfrclkspinepwrdb());	//CSR8[14:14]
	return *this;
}
uint
CS_clkRegs::gethsclkfrclkspinepwrdb(){
	return get_csr_bits(REG_INFO.hsclkfrclkspinepwrdb());	//CSR8[14:14]
}

CS_clkRegs&
CS_clkRegs::sethsclkfromsspwrdb(uint val){
	fill_csr_bits(val,REG_INFO.hsclkfromsspwrdb());	//CSR8[13:13]
	return *this;
}
uint
CS_clkRegs::gethsclkfromsspwrdb(){
	return get_csr_bits(REG_INFO.hsclkfromsspwrdb());	//CSR8[13:13]
}

CS_clkRegs&
CS_clkRegs::sethsclktosspwrdb(uint val){
	fill_csr_bits(val,REG_INFO.hsclktosspwrdb());	//CSR8[12:12]
	return *this;
}
uint
CS_clkRegs::gethsclktosspwrdb(){
	return get_csr_bits(REG_INFO.hsclktosspwrdb());	//CSR8[12:12]
}

CS_clkRegs&
CS_clkRegs::sethsclkfromcsbiasctrl(uint val){
	fill_csr_bits(val,REG_INFO.hsclkfromcsbiasctrl());	//CSR8[11:10]
	return *this;
}
uint
CS_clkRegs::gethsclkfromcsbiasctrl(){
	return get_csr_bits(REG_INFO.hsclkfromcsbiasctrl());	//CSR8[11:10]
}

CS_clkRegs&
CS_clkRegs::sethsclkfromssbiasctrl(uint val){
	fill_csr_bits(val,REG_INFO.hsclkfromssbiasctrl());	//CSR8[9:8]
	return *this;
}
uint
CS_clkRegs::gethsclkfromssbiasctrl(){
	return get_csr_bits(REG_INFO.hsclkfromssbiasctrl());	//CSR8[9:8]
}

CS_clkRegs&
CS_clkRegs::sethsclktossbiasctrl(uint val){
	fill_csr_bits(val,REG_INFO.hsclktossbiasctrl());	//CSR8[7:6]
	return *this;
}
uint
CS_clkRegs::gethsclktossbiasctrl(){
	return get_csr_bits(REG_INFO.hsclktossbiasctrl());	//CSR8[7:6]
}

CS_clkRegs&
CS_clkRegs::sethsclkreploadctrl(uint val){
	fill_csr_bits(val,REG_INFO.hsclkreploadctrl());	//CSR8[5:3]
	return *this;
}
uint
CS_clkRegs::gethsclkreploadctrl(){
	return get_csr_bits(REG_INFO.hsclkreploadctrl());	//CSR8[5:3]
}

CS_clkRegs&
CS_clkRegs::sethsclkreprefsel(uint val){
	fill_csr_bits(val,REG_INFO.hsclkreprefsel());	//CSR8[2:0]
	return *this;
}
uint
CS_clkRegs::gethsclkreprefsel(){
	return get_csr_bits(REG_INFO.hsclkreprefsel());	//CSR8[2:0]
}

CS_clkRegs&
CS_clkRegs::sethsclkspare(uint val){
	fill_csr_bits(val,REG_INFO.hsclkspare());	//CSR9[14:12]
	return *this;
}
uint
CS_clkRegs::gethsclkspare(){
	return get_csr_bits(REG_INFO.hsclkspare());	//CSR9[14:12]
}

CS_clkRegs&
CS_clkRegs::setbiascmupwrdb(uint val){
	fill_csr_bits(val,REG_INFO.biascmupwrdb());	//CSR9[8:8]
	return *this;
}
uint
CS_clkRegs::getbiascmupwrdb(){
	return get_csr_bits(REG_INFO.biascmupwrdb());	//CSR9[8:8]
}

CS_clkRegs&
CS_clkRegs::setbiascvcal(uint val){
	fill_csr_bits(val,REG_INFO.biascvcal());	//CSR9[7:0]
	return *this;
}
uint
CS_clkRegs::getbiascvcal(){
	return get_csr_bits(REG_INFO.biascvcal());	//CSR9[7:0]
}

CS_clkRegs&
CS_clkRegs::setcsrxbiasbackupgen(uint val){
	fill_csr_bits(val,REG_INFO.csrxbiasbackupgen());	//CSR10[15:15]
	return *this;
}
uint
CS_clkRegs::getcsrxbiasbackupgen(){
	return get_csr_bits(REG_INFO.csrxbiasbackupgen());	//CSR10[15:15]
}

CS_clkRegs&
CS_clkRegs::setcsspare(uint val){
	fill_csr_bits(val,REG_INFO.csspare());	//CSR10[14:0]
	return *this;
}
uint
CS_clkRegs::getcsspare(){
	return get_csr_bits(REG_INFO.csspare());	//CSR10[14:0]
}

CS_clkRegs&
CS_clkRegs::setvregpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.vregpwrdb());	//CSR11[15:15]
	return *this;
}
uint
CS_clkRegs::getvregpwrdb(){
	return get_csr_bits(REG_INFO.vregpwrdb());	//CSR11[15:15]
}

CS_clkRegs&
CS_clkRegs::setvregcapsel(uint val){
	fill_csr_bits(val,REG_INFO.vregcapsel());	//CSR11[12:12]
	return *this;
}
uint
CS_clkRegs::getvregcapsel(){
	return get_csr_bits(REG_INFO.vregcapsel());	//CSR11[12:12]
}

CS_clkRegs&
CS_clkRegs::setvregselfbleed(uint val){
	fill_csr_bits(val,REG_INFO.vregselfbleed());	//CSR11[11:8]
	return *this;
}
uint
CS_clkRegs::getvregselfbleed(){
	return get_csr_bits(REG_INFO.vregselfbleed());	//CSR11[11:8]
}

CS_clkRegs&
CS_clkRegs::setvregplllvl(uint val){
	fill_csr_bits(val,REG_INFO.vregplllvl());	//CSR11[7:0]
	return *this;
}
uint
CS_clkRegs::getvregplllvl(){
	return get_csr_bits(REG_INFO.vregplllvl());	//CSR11[7:0]
}

CS_clkRegs&
CS_clkRegs::setcalpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.calpwrdb());	//CSR12[15:15]
	return *this;
}
uint
CS_clkRegs::getcalpwrdb(){
	return get_csr_bits(REG_INFO.calpwrdb());	//CSR12[15:15]
}

CS_clkRegs&
CS_clkRegs::setcalrstb(uint val){
	fill_csr_bits(val,REG_INFO.calrstb());	//CSR12[14:14]
	return *this;
}
uint
CS_clkRegs::getcalrstb(){
	return get_csr_bits(REG_INFO.calrstb());	//CSR12[14:14]
}

CS_clkRegs&
CS_clkRegs::setcs_post_lckchk_bypass(uint val){
	fill_csr_bits(val,REG_INFO.cs_post_lckchk_bypass());	//CSR12[8:8]
	return *this;
}
uint
CS_clkRegs::getcs_post_lckchk_bypass(){
	return get_csr_bits(REG_INFO.cs_post_lckchk_bypass());	//CSR12[8:8]
}

CS_clkRegs&
CS_clkRegs::setcs_initamp_calib_bypass(uint val){
	fill_csr_bits(val,REG_INFO.cs_initamp_calib_bypass());	//CSR12[7:7]
	return *this;
}
uint
CS_clkRegs::getcs_initamp_calib_bypass(){
	return get_csr_bits(REG_INFO.cs_initamp_calib_bypass());	//CSR12[7:7]
}

CS_clkRegs&
CS_clkRegs::setcslowoffcal(uint val){
	fill_csr_bits(val,REG_INFO.cslowoffcal());	//CSR12[6:6]
	return *this;
}
uint
CS_clkRegs::getcslowoffcal(){
	return get_csr_bits(REG_INFO.cslowoffcal());	//CSR12[6:6]
}

CS_clkRegs&
CS_clkRegs::setcslowoffsetctrl(uint val){
	fill_csr_bits(val,REG_INFO.cslowoffsetctrl());	//CSR12[5:0]
	return *this;
}
uint
CS_clkRegs::getcslowoffsetctrl(){
	return get_csr_bits(REG_INFO.cslowoffsetctrl());	//CSR12[5:0]
}

CS_clkRegs&
CS_clkRegs::setlcvcocalmode(uint val){
	fill_csr_bits(val,REG_INFO.lcvcocalmode());	//CSR13[15:15]
	return *this;
}
uint
CS_clkRegs::getlcvcocalmode(){
	return get_csr_bits(REG_INFO.lcvcocalmode());	//CSR13[15:15]
}

CS_clkRegs&
CS_clkRegs::setlcvcocalctrl(uint val){
	fill_csr_bits(val,REG_INFO.lcvcocalctrl());	//CSR13[13:10]
	return *this;
}
uint
CS_clkRegs::getlcvcocalctrl(){
	return get_csr_bits(REG_INFO.lcvcocalctrl());	//CSR13[13:10]
}

uint
CS_clkRegs::getptatcalout(){
	return get_csr_bits(REG_INFO.ptatcalout());	//CSR13[9:9]
}

uint
CS_clkRegs::getcvcalout(){
	return get_csr_bits(REG_INFO.cvcalout());	//CSR13[8:8]
}

uint
CS_clkRegs::getcomparestatus(){
	return get_csr_bits(REG_INFO.comparestatus());	//CSR13[7:6]
}

uint
CS_clkRegs::getdtbout(){
	return get_csr_bits(REG_INFO.dtbout());	//CSR13[5:5]
}

uint
CS_clkRegs::getlcvcocaldone(){
	return get_csr_bits(REG_INFO.lcvcocaldone());	//CSR13[4:4]
}

uint
CS_clkRegs::getlcvcocalerr(){
	return get_csr_bits(REG_INFO.lcvcocalerr());	//CSR13[3:3]
}

uint
CS_clkRegs::getlcvcocalstatus(){
	return get_csr_bits(REG_INFO.lcvcocalstatus());	//CSR13[2:0]
}

CS_clkRegs&
CS_clkRegs::setcsdtbsel(uint val){
	fill_csr_bits(val,REG_INFO.csdtbsel());	//CSR14[15:12]
	return *this;
}
uint
CS_clkRegs::getcsdtbsel(){
	return get_csr_bits(REG_INFO.csdtbsel());	//CSR14[15:12]
}

CS_clkRegs&
CS_clkRegs::setvregatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.vregatbctrl());	//CSR14[11:3]
	return *this;
}
uint
CS_clkRegs::getvregatbctrl(){
	return get_csr_bits(REG_INFO.vregatbctrl());	//CSR14[11:3]
}

CS_clkRegs&
CS_clkRegs::setcsatbfinalsel(uint val){
	fill_csr_bits(val,REG_INFO.csatbfinalsel());	//CSR14[2:0]
	return *this;
}
uint
CS_clkRegs::getcsatbfinalsel(){
	return get_csr_bits(REG_INFO.csatbfinalsel());	//CSR14[2:0]
}

CS_clkRegs&
CS_clkRegs::setcsatbsel23to16(uint val){
	fill_csr_bits(val,REG_INFO.csatbsel23to16());	//CSR15[15:8]
	return *this;
}
uint
CS_clkRegs::getcsatbsel23to16(){
	return get_csr_bits(REG_INFO.csatbsel23to16());	//CSR15[15:8]
}

CS_clkRegs&
CS_clkRegs::setssspare(uint val){
	fill_csr_bits(val,REG_INFO.ssspare());	//CSR15[7:0]
	return *this;
}
uint
CS_clkRegs::getssspare(){
	return get_csr_bits(REG_INFO.ssspare());	//CSR15[7:0]
}

CS_clkRegs&
CS_clkRegs::setsspwrdb(uint val){
	fill_csr_bits(val,REG_INFO.sspwrdb());	//CSR16[15:15]
	return *this;
}
uint
CS_clkRegs::getsspwrdb(){
	return get_csr_bits(REG_INFO.sspwrdb());	//CSR16[15:15]
}

CS_clkRegs&
CS_clkRegs::setssrefclk0pwrdb(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk0pwrdb());	//CSR16[14:14]
	return *this;
}
uint
CS_clkRegs::getssrefclk0pwrdb(){
	return get_csr_bits(REG_INFO.ssrefclk0pwrdb());	//CSR16[14:14]
}

CS_clkRegs&
CS_clkRegs::setssrefclk1pwrdb(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk1pwrdb());	//CSR16[13:13]
	return *this;
}
uint
CS_clkRegs::getssrefclk1pwrdb(){
	return get_csr_bits(REG_INFO.ssrefclk1pwrdb());	//CSR16[13:13]
}

CS_clkRegs&
CS_clkRegs::setsshsclkss2cspwrdb(uint val){
	fill_csr_bits(val,REG_INFO.sshsclkss2cspwrdb());	//CSR16[9:9]
	return *this;
}
uint
CS_clkRegs::getsshsclkss2cspwrdb(){
	return get_csr_bits(REG_INFO.sshsclkss2cspwrdb());	//CSR16[9:9]
}

CS_clkRegs&
CS_clkRegs::setsshsclkcs2sspwrdb(uint val){
	fill_csr_bits(val,REG_INFO.sshsclkcs2sspwrdb());	//CSR16[8:8]
	return *this;
}
uint
CS_clkRegs::getsshsclkcs2sspwrdb(){
	return get_csr_bits(REG_INFO.sshsclkcs2sspwrdb());	//CSR16[8:8]
}

CS_clkRegs&
CS_clkRegs::setssrefclk0cmldivpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk0cmldivpwrdb());	//CSR16[7:7]
	return *this;
}
uint
CS_clkRegs::getssrefclk0cmldivpwrdb(){
	return get_csr_bits(REG_INFO.ssrefclk0cmldivpwrdb());	//CSR16[7:7]
}

CS_clkRegs&
CS_clkRegs::setssrefclk0atten(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk0atten());	//CSR16[5:4]
	return *this;
}
uint
CS_clkRegs::getssrefclk0atten(){
	return get_csr_bits(REG_INFO.ssrefclk0atten());	//CSR16[5:4]
}

CS_clkRegs&
CS_clkRegs::setssrefclk1cmldivpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk1cmldivpwrdb());	//CSR16[3:3]
	return *this;
}
uint
CS_clkRegs::getssrefclk1cmldivpwrdb(){
	return get_csr_bits(REG_INFO.ssrefclk1cmldivpwrdb());	//CSR16[3:3]
}

CS_clkRegs&
CS_clkRegs::setssrefclk1atten(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk1atten());	//CSR16[1:0]
	return *this;
}
uint
CS_clkRegs::getssrefclk1atten(){
	return get_csr_bits(REG_INFO.ssrefclk1atten());	//CSR16[1:0]
}

CS_clkRegs&
CS_clkRegs::setbg600mvlvccresdiv(uint val){
	fill_csr_bits(val,REG_INFO.bg600mvlvccresdiv());	//CSR17[15:15]
	return *this;
}
uint
CS_clkRegs::getbg600mvlvccresdiv(){
	return get_csr_bits(REG_INFO.bg600mvlvccresdiv());	//CSR17[15:15]
}

CS_clkRegs&
CS_clkRegs::setbgccen(uint val){
	fill_csr_bits(val,REG_INFO.bgccen());	//CSR17[14:14]
	return *this;
}
uint
CS_clkRegs::getbgccen(){
	return get_csr_bits(REG_INFO.bgccen());	//CSR17[14:14]
}

CS_clkRegs&
CS_clkRegs::setbgcven(uint val){
	fill_csr_bits(val,REG_INFO.bgcven());	//CSR17[13:13]
	return *this;
}
uint
CS_clkRegs::getbgcven(){
	return get_csr_bits(REG_INFO.bgcven());	//CSR17[13:13]
}

CS_clkRegs&
CS_clkRegs::setbgpaten(uint val){
	fill_csr_bits(val,REG_INFO.bgpaten());	//CSR17[12:12]
	return *this;
}
uint
CS_clkRegs::getbgpaten(){
	return get_csr_bits(REG_INFO.bgpaten());	//CSR17[12:12]
}

CS_clkRegs&
CS_clkRegs::setbgforcestart(uint val){
	fill_csr_bits(val,REG_INFO.bgforcestart());	//CSR17[11:10]
	return *this;
}
uint
CS_clkRegs::getbgforcestart(){
	return get_csr_bits(REG_INFO.bgforcestart());	//CSR17[11:10]
}

CS_clkRegs&
CS_clkRegs::setbgstartbypass(uint val){
	fill_csr_bits(val,REG_INFO.bgstartbypass());	//CSR17[9:8]
	return *this;
}
uint
CS_clkRegs::getbgstartbypass(){
	return get_csr_bits(REG_INFO.bgstartbypass());	//CSR17[9:8]
}

CS_clkRegs&
CS_clkRegs::setbgbypass(uint val){
	fill_csr_bits(val,REG_INFO.bgbypass());	//CSR17[7:0]
	return *this;
}
uint
CS_clkRegs::getbgbypass(){
	return get_csr_bits(REG_INFO.bgbypass());	//CSR17[7:0]
}

CS_clkRegs&
CS_clkRegs::sethvvbgccin(uint val){
	fill_csr_bits(val,REG_INFO.hvvbgccin());	//CSR18[15:15]
	return *this;
}
uint
CS_clkRegs::gethvvbgccin(){
	return get_csr_bits(REG_INFO.hvvbgccin());	//CSR18[15:15]
}

CS_clkRegs&
CS_clkRegs::setvbgreflvl(uint val){
	fill_csr_bits(val,REG_INFO.vbgreflvl());	//CSR18[14:12]
	return *this;
}
uint
CS_clkRegs::getvbgreflvl(){
	return get_csr_bits(REG_INFO.vbgreflvl());	//CSR18[14:12]
}

CS_clkRegs&
CS_clkRegs::sethvvbgptatin(uint val){
	fill_csr_bits(val,REG_INFO.hvvbgptatin());	//CSR18[11:11]
	return *this;
}
uint
CS_clkRegs::gethvvbgptatin(){
	return get_csr_bits(REG_INFO.hvvbgptatin());	//CSR18[11:11]
}

CS_clkRegs&
CS_clkRegs::setvbgptatlvl(uint val){
	fill_csr_bits(val,REG_INFO.vbgptatlvl());	//CSR18[10:8]
	return *this;
}
uint
CS_clkRegs::getvbgptatlvl(){
	return get_csr_bits(REG_INFO.vbgptatlvl());	//CSR18[10:8]
}

CS_clkRegs&
CS_clkRegs::setbiasselptatmix(uint val){
	fill_csr_bits(val,REG_INFO.biasselptatmix());	//CSR18[7:0]
	return *this;
}
uint
CS_clkRegs::getbiasselptatmix(){
	return get_csr_bits(REG_INFO.biasselptatmix());	//CSR18[7:0]
}

CS_clkRegs&
CS_clkRegs::setssatbsel(uint val){
	fill_csr_bits(val,REG_INFO.ssatbsel());	//CSR19[15:0]
	return *this;
}
uint
CS_clkRegs::getssatbsel(){
	return get_csr_bits(REG_INFO.ssatbsel());	//CSR19[15:0]
}

CS_clkRegs&
CS_clkRegs::setcs_lld_clr(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_clr());	//CSR20[13:13]
	return *this;
}
uint
CS_clkRegs::getcs_lld_clr(){
	return get_csr_bits(REG_INFO.cs_lld_clr());	//CSR20[13:13]
}

CS_clkRegs&
CS_clkRegs::setcs_fd_clr(uint val){
	fill_csr_bits(val,REG_INFO.cs_fd_clr());	//CSR20[12:12]
	return *this;
}
uint
CS_clkRegs::getcs_fd_clr(){
	return get_csr_bits(REG_INFO.cs_fd_clr());	//CSR20[12:12]
}

CS_clkRegs&
CS_clkRegs::setcs_calib_clr(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_clr());	//CSR20[11:11]
	return *this;
}
uint
CS_clkRegs::getcs_calib_clr(){
	return get_csr_bits(REG_INFO.cs_calib_clr());	//CSR20[11:11]
}

CS_clkRegs&
CS_clkRegs::setcs_lcd_start(uint val){
	fill_csr_bits(val,REG_INFO.cs_lcd_start());	//CSR20[10:10]
	return *this;
}
uint
CS_clkRegs::getcs_lcd_start(){
	return get_csr_bits(REG_INFO.cs_lcd_start());	//CSR20[10:10]
}

CS_clkRegs&
CS_clkRegs::setcs_lld_start(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_start());	//CSR20[9:9]
	return *this;
}
uint
CS_clkRegs::getcs_lld_start(){
	return get_csr_bits(REG_INFO.cs_lld_start());	//CSR20[9:9]
}

CS_clkRegs&
CS_clkRegs::setcs_calib_start(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_start());	//CSR20[8:8]
	return *this;
}
uint
CS_clkRegs::getcs_calib_start(){
	return get_csr_bits(REG_INFO.cs_calib_start());	//CSR20[8:8]
}

CS_clkRegs&
CS_clkRegs::setcs_lcd_enable(uint val){
	fill_csr_bits(val,REG_INFO.cs_lcd_enable());	//CSR20[7:7]
	return *this;
}
uint
CS_clkRegs::getcs_lcd_enable(){
	return get_csr_bits(REG_INFO.cs_lcd_enable());	//CSR20[7:7]
}

CS_clkRegs&
CS_clkRegs::setcs_lld_enable(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_enable());	//CSR20[6:6]
	return *this;
}
uint
CS_clkRegs::getcs_lld_enable(){
	return get_csr_bits(REG_INFO.cs_lld_enable());	//CSR20[6:6]
}

CS_clkRegs&
CS_clkRegs::setcs_calib_enable(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_enable());	//CSR20[5:5]
	return *this;
}
uint
CS_clkRegs::getcs_calib_enable(){
	return get_csr_bits(REG_INFO.cs_calib_enable());	//CSR20[5:5]
}

CS_clkRegs&
CS_clkRegs::setcs_lcd_soft_rst_n(uint val){
	fill_csr_bits(val,REG_INFO.cs_lcd_soft_rst_n());	//CSR20[4:4]
	return *this;
}
uint
CS_clkRegs::getcs_lcd_soft_rst_n(){
	return get_csr_bits(REG_INFO.cs_lcd_soft_rst_n());	//CSR20[4:4]
}

CS_clkRegs&
CS_clkRegs::setcs_lld_soft_rst_n(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_soft_rst_n());	//CSR20[3:3]
	return *this;
}
uint
CS_clkRegs::getcs_lld_soft_rst_n(){
	return get_csr_bits(REG_INFO.cs_lld_soft_rst_n());	//CSR20[3:3]
}

CS_clkRegs&
CS_clkRegs::setcs_calib_soft_rst_n(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_soft_rst_n());	//CSR20[2:2]
	return *this;
}
uint
CS_clkRegs::getcs_calib_soft_rst_n(){
	return get_csr_bits(REG_INFO.cs_calib_soft_rst_n());	//CSR20[2:2]
}

CS_clkRegs&
CS_clkRegs::setcs_glb_soft_rst_n(uint val){
	fill_csr_bits(val,REG_INFO.cs_glb_soft_rst_n());	//CSR20[0:0]
	return *this;
}
uint
CS_clkRegs::getcs_glb_soft_rst_n(){
	return get_csr_bits(REG_INFO.cs_glb_soft_rst_n());	//CSR20[0:0]
}

CS_clkRegs&
CS_clkRegs::setcsatbsel15to0(uint val){
	fill_csr_bits(val,REG_INFO.csatbsel15to0());	//CSR21[15:0]
	return *this;
}
uint
CS_clkRegs::getcsatbsel15to0(){
	return get_csr_bits(REG_INFO.csatbsel15to0());	//CSR21[15:0]
}

CS_clkRegs&
CS_clkRegs::setcs_direction_ctrl(uint val){
	fill_csr_bits(val,REG_INFO.cs_direction_ctrl());	//CSR22[6:0]
	return *this;
}
uint
CS_clkRegs::getcs_direction_ctrl(){
	return get_csr_bits(REG_INFO.cs_direction_ctrl());	//CSR22[6:0]
}

CS_clkRegs&
CS_clkRegs::setcs_calib_mode_bdsel(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_mode_bdsel());	//CSR23[14:12]
	return *this;
}
uint
CS_clkRegs::getcs_calib_mode_bdsel(){
	return get_csr_bits(REG_INFO.cs_calib_mode_bdsel());	//CSR23[14:12]
}

CS_clkRegs&
CS_clkRegs::setcs_calib_mode_freqcal(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_mode_freqcal());	//CSR23[11:9]
	return *this;
}
uint
CS_clkRegs::getcs_calib_mode_freqcal(){
	return get_csr_bits(REG_INFO.cs_calib_mode_freqcal());	//CSR23[11:9]
}

CS_clkRegs&
CS_clkRegs::setcs_calib_mode_minamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_mode_minamp());	//CSR23[8:6]
	return *this;
}
uint
CS_clkRegs::getcs_calib_mode_minamp(){
	return get_csr_bits(REG_INFO.cs_calib_mode_minamp());	//CSR23[8:6]
}

CS_clkRegs&
CS_clkRegs::setcs_calib_mode_initamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_mode_initamp());	//CSR23[5:3]
	return *this;
}
uint
CS_clkRegs::getcs_calib_mode_initamp(){
	return get_csr_bits(REG_INFO.cs_calib_mode_initamp());	//CSR23[5:3]
}

CS_clkRegs&
CS_clkRegs::setcs_calib_mode_offset(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_mode_offset());	//CSR23[2:0]
	return *this;
}
uint
CS_clkRegs::getcs_calib_mode_offset(){
	return get_csr_bits(REG_INFO.cs_calib_mode_offset());	//CSR23[2:0]
}

CS_clkRegs&
CS_clkRegs::setcs_calib_mode_lckchk(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_mode_lckchk());	//CSR24[5:3]
	return *this;
}
uint
CS_clkRegs::getcs_calib_mode_lckchk(){
	return get_csr_bits(REG_INFO.cs_calib_mode_lckchk());	//CSR24[5:3]
}

CS_clkRegs&
CS_clkRegs::setcs_calib_mode_maxamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_calib_mode_maxamp());	//CSR24[2:0]
	return *this;
}
uint
CS_clkRegs::getcs_calib_mode_maxamp(){
	return get_csr_bits(REG_INFO.cs_calib_mode_maxamp());	//CSR24[2:0]
}

CS_clkRegs&
CS_clkRegs::setcs_ctrl_code_min_initamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_min_initamp());	//CSR25[15:11]
	return *this;
}
uint
CS_clkRegs::getcs_ctrl_code_min_initamp(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_min_initamp());	//CSR25[15:11]
}

CS_clkRegs&
CS_clkRegs::setcs_ctrl_code_max_offset(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_max_offset());	//CSR25[10:5]
	return *this;
}
uint
CS_clkRegs::getcs_ctrl_code_max_offset(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_max_offset());	//CSR25[10:5]
}

CS_clkRegs&
CS_clkRegs::setcs_ctrl_code_min_offset(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_min_offset());	//CSR25[4:0]
	return *this;
}
uint
CS_clkRegs::getcs_ctrl_code_min_offset(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_min_offset());	//CSR25[4:0]
}

CS_clkRegs&
CS_clkRegs::setcs_ctrl_code_max_minamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_max_minamp());	//CSR26[14:10]
	return *this;
}
uint
CS_clkRegs::getcs_ctrl_code_max_minamp(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_max_minamp());	//CSR26[14:10]
}

CS_clkRegs&
CS_clkRegs::setcs_ctrl_code_min_minamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_min_minamp());	//CSR26[9:5]
	return *this;
}
uint
CS_clkRegs::getcs_ctrl_code_min_minamp(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_min_minamp());	//CSR26[9:5]
}

CS_clkRegs&
CS_clkRegs::setcs_ctrl_code_max_initamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_max_initamp());	//CSR26[4:0]
	return *this;
}
uint
CS_clkRegs::getcs_ctrl_code_max_initamp(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_max_initamp());	//CSR26[4:0]
}

CS_clkRegs&
CS_clkRegs::setcs_ctrl_code_min_bdsel(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_min_bdsel());	//CSR27[14:10]
	return *this;
}
uint
CS_clkRegs::getcs_ctrl_code_min_bdsel(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_min_bdsel());	//CSR27[14:10]
}

CS_clkRegs&
CS_clkRegs::setcs_ctrl_code_min_freqcal(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_min_freqcal());	//CSR27[5:0]
	return *this;
}
uint
CS_clkRegs::getcs_ctrl_code_min_freqcal(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_min_freqcal());	//CSR27[5:0]
}

CS_clkRegs&
CS_clkRegs::setcs_ctrl_code_max_maxamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_max_maxamp());	//CSR28[14:10]
	return *this;
}
uint
CS_clkRegs::getcs_ctrl_code_max_maxamp(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_max_maxamp());	//CSR28[14:10]
}

CS_clkRegs&
CS_clkRegs::setcs_ctrl_code_min_maxamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_min_maxamp());	//CSR28[9:5]
	return *this;
}
uint
CS_clkRegs::getcs_ctrl_code_min_maxamp(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_min_maxamp());	//CSR28[9:5]
}

CS_clkRegs&
CS_clkRegs::setcs_ctrl_code_max_bdsel(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_max_bdsel());	//CSR28[4:0]
	return *this;
}
uint
CS_clkRegs::getcs_ctrl_code_max_bdsel(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_max_bdsel());	//CSR28[4:0]
}

CS_clkRegs&
CS_clkRegs::setcs_ctrl_code_max_lckchk(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_max_lckchk());	//CSR29[9:5]
	return *this;
}
uint
CS_clkRegs::getcs_ctrl_code_max_lckchk(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_max_lckchk());	//CSR29[9:5]
}

CS_clkRegs&
CS_clkRegs::setcs_ctrl_code_min_lckchk(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_min_lckchk());	//CSR29[4:0]
	return *this;
}
uint
CS_clkRegs::getcs_ctrl_code_min_lckchk(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_min_lckchk());	//CSR29[4:0]
}

CS_clkRegs&
CS_clkRegs::setcs_init_code_amp(uint val){
	fill_csr_bits(val,REG_INFO.cs_init_code_amp());	//CSR30[11:7]
	return *this;
}
uint
CS_clkRegs::getcs_init_code_amp(){
	return get_csr_bits(REG_INFO.cs_init_code_amp());	//CSR30[11:7]
}

CS_clkRegs&
CS_clkRegs::setcs_init_code_offset(uint val){
	fill_csr_bits(val,REG_INFO.cs_init_code_offset());	//CSR30[6:2]
	return *this;
}
uint
CS_clkRegs::getcs_init_code_offset(){
	return get_csr_bits(REG_INFO.cs_init_code_offset());	//CSR30[6:2]
}

CS_clkRegs&
CS_clkRegs::setcs_init_code_bdsel(uint val){
	fill_csr_bits(val,REG_INFO.cs_init_code_bdsel());	//CSR30[1:0]
	return *this;
}
uint
CS_clkRegs::getcs_init_code_bdsel(){
	return get_csr_bits(REG_INFO.cs_init_code_bdsel());	//CSR30[1:0]
}

CS_clkRegs&
CS_clkRegs::setcs_init_code_maxamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_init_code_maxamp());	//CSR31[15:11]
	return *this;
}
uint
CS_clkRegs::getcs_init_code_maxamp(){
	return get_csr_bits(REG_INFO.cs_init_code_maxamp());	//CSR31[15:11]
}

CS_clkRegs&
CS_clkRegs::setcs_init_code_freqcal(uint val){
	fill_csr_bits(val,REG_INFO.cs_init_code_freqcal());	//CSR31[10:5]
	return *this;
}
uint
CS_clkRegs::getcs_init_code_freqcal(){
	return get_csr_bits(REG_INFO.cs_init_code_freqcal());	//CSR31[10:5]
}

CS_clkRegs&
CS_clkRegs::setcs_init_code_minamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_init_code_minamp());	//CSR31[4:0]
	return *this;
}
uint
CS_clkRegs::getcs_init_code_minamp(){
	return get_csr_bits(REG_INFO.cs_init_code_minamp());	//CSR31[4:0]
}

CS_clkRegs&
CS_clkRegs::setcs_ctrl_code_max_freqcal(uint val){
	fill_csr_bits(val,REG_INFO.cs_ctrl_code_max_freqcal());	//CSR32[10:5]
	return *this;
}
uint
CS_clkRegs::getcs_ctrl_code_max_freqcal(){
	return get_csr_bits(REG_INFO.cs_ctrl_code_max_freqcal());	//CSR32[10:5]
}

CS_clkRegs&
CS_clkRegs::setcs_init_code_lckchk(uint val){
	fill_csr_bits(val,REG_INFO.cs_init_code_lckchk());	//CSR32[4:0]
	return *this;
}
uint
CS_clkRegs::getcs_init_code_lckchk(){
	return get_csr_bits(REG_INFO.cs_init_code_lckchk());	//CSR32[4:0]
}

CS_clkRegs&
CS_clkRegs::setcs_trans_max_freqcal(uint val){
	fill_csr_bits(val,REG_INFO.cs_trans_max_freqcal());	//CSR33[15:12]
	return *this;
}
uint
CS_clkRegs::getcs_trans_max_freqcal(){
	return get_csr_bits(REG_INFO.cs_trans_max_freqcal());	//CSR33[15:12]
}

CS_clkRegs&
CS_clkRegs::setcs_trans_max_minamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_trans_max_minamp());	//CSR33[11:8]
	return *this;
}
uint
CS_clkRegs::getcs_trans_max_minamp(){
	return get_csr_bits(REG_INFO.cs_trans_max_minamp());	//CSR33[11:8]
}

CS_clkRegs&
CS_clkRegs::setcs_trans_max_initamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_trans_max_initamp());	//CSR33[7:4]
	return *this;
}
uint
CS_clkRegs::getcs_trans_max_initamp(){
	return get_csr_bits(REG_INFO.cs_trans_max_initamp());	//CSR33[7:4]
}

CS_clkRegs&
CS_clkRegs::setcs_trans_max_offset(uint val){
	fill_csr_bits(val,REG_INFO.cs_trans_max_offset());	//CSR33[3:0]
	return *this;
}
uint
CS_clkRegs::getcs_trans_max_offset(){
	return get_csr_bits(REG_INFO.cs_trans_max_offset());	//CSR33[3:0]
}

CS_clkRegs&
CS_clkRegs::setcs_trans_max_lckchk(uint val){
	fill_csr_bits(val,REG_INFO.cs_trans_max_lckchk());	//CSR34[11:8]
	return *this;
}
uint
CS_clkRegs::getcs_trans_max_lckchk(){
	return get_csr_bits(REG_INFO.cs_trans_max_lckchk());	//CSR34[11:8]
}

CS_clkRegs&
CS_clkRegs::setcs_trans_max_maxamp(uint val){
	fill_csr_bits(val,REG_INFO.cs_trans_max_maxamp());	//CSR34[7:4]
	return *this;
}
uint
CS_clkRegs::getcs_trans_max_maxamp(){
	return get_csr_bits(REG_INFO.cs_trans_max_maxamp());	//CSR34[7:4]
}

CS_clkRegs&
CS_clkRegs::setcs_trans_max_bdsel(uint val){
	fill_csr_bits(val,REG_INFO.cs_trans_max_bdsel());	//CSR34[3:0]
	return *this;
}
uint
CS_clkRegs::getcs_trans_max_bdsel(){
	return get_csr_bits(REG_INFO.cs_trans_max_bdsel());	//CSR34[3:0]
}

CS_clkRegs&
CS_clkRegs::setcs_fd_threshold(uint val){
	fill_csr_bits(val,REG_INFO.cs_fd_threshold());	//CSR35[10:1]
	return *this;
}
uint
CS_clkRegs::getcs_fd_threshold(){
	return get_csr_bits(REG_INFO.cs_fd_threshold());	//CSR35[10:1]
}

CS_clkRegs&
CS_clkRegs::setcs_meas_fd_wait(uint val){
	fill_csr_bits(val,REG_INFO.cs_meas_fd_wait());	//CSR35[0:0]
	return *this;
}
uint
CS_clkRegs::getcs_meas_fd_wait(){
	return get_csr_bits(REG_INFO.cs_meas_fd_wait());	//CSR35[0:0]
}

CS_clkRegs&
CS_clkRegs::setcs_fd_ref_cnt_dv(uint val){
	fill_csr_bits(val,REG_INFO.cs_fd_ref_cnt_dv());	//CSR36[13:12]
	return *this;
}
uint
CS_clkRegs::getcs_fd_ref_cnt_dv(){
	return get_csr_bits(REG_INFO.cs_fd_ref_cnt_dv());	//CSR36[13:12]
}

CS_clkRegs&
CS_clkRegs::setcs_fd_ref_cnt_lv(uint val){
	fill_csr_bits(val,REG_INFO.cs_fd_ref_cnt_lv());	//CSR36[11:0]
	return *this;
}
uint
CS_clkRegs::getcs_fd_ref_cnt_lv(){
	return get_csr_bits(REG_INFO.cs_fd_ref_cnt_lv());	//CSR36[11:0]
}

CS_clkRegs&
CS_clkRegs::setcs_fd_fb_cnt_dv(uint val){
	fill_csr_bits(val,REG_INFO.cs_fd_fb_cnt_dv());	//CSR37[13:12]
	return *this;
}
uint
CS_clkRegs::getcs_fd_fb_cnt_dv(){
	return get_csr_bits(REG_INFO.cs_fd_fb_cnt_dv());	//CSR37[13:12]
}

CS_clkRegs&
CS_clkRegs::setcs_fd_fb_cnt_lv(uint val){
	fill_csr_bits(val,REG_INFO.cs_fd_fb_cnt_lv());	//CSR37[11:0]
	return *this;
}
uint
CS_clkRegs::getcs_fd_fb_cnt_lv(){
	return get_csr_bits(REG_INFO.cs_fd_fb_cnt_lv());	//CSR37[11:0]
}

CS_clkRegs&
CS_clkRegs::setcs_timer_value(uint val){
	fill_csr_bits(val,REG_INFO.cs_timer_value());	//CSR38[14:5]
	return *this;
}
uint
CS_clkRegs::getcs_timer_value(){
	return get_csr_bits(REG_INFO.cs_timer_value());	//CSR38[14:5]
}

CS_clkRegs&
CS_clkRegs::setcs_timer_div_value(uint val){
	fill_csr_bits(val,REG_INFO.cs_timer_div_value());	//CSR38[4:2]
	return *this;
}
uint
CS_clkRegs::getcs_timer_div_value(){
	return get_csr_bits(REG_INFO.cs_timer_div_value());	//CSR38[4:2]
}

CS_clkRegs&
CS_clkRegs::setcs_timer_div_en(uint val){
	fill_csr_bits(val,REG_INFO.cs_timer_div_en());	//CSR38[1:1]
	return *this;
}
uint
CS_clkRegs::getcs_timer_div_en(){
	return get_csr_bits(REG_INFO.cs_timer_div_en());	//CSR38[1:1]
}

CS_clkRegs&
CS_clkRegs::setcs_timer_stop(uint val){
	fill_csr_bits(val,REG_INFO.cs_timer_stop());	//CSR38[0:0]
	return *this;
}
uint
CS_clkRegs::getcs_timer_stop(){
	return get_csr_bits(REG_INFO.cs_timer_stop());	//CSR38[0:0]
}

CS_clkRegs&
CS_clkRegs::setcs_lld_fb_div_ratio(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_fb_div_ratio());	//CSR39[3:1]
	return *this;
}
uint
CS_clkRegs::getcs_lld_fb_div_ratio(){
	return get_csr_bits(REG_INFO.cs_lld_fb_div_ratio());	//CSR39[3:1]
}

CS_clkRegs&
CS_clkRegs::setcs_lld_once(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_once());	//CSR39[0:0]
	return *this;
}
uint
CS_clkRegs::getcs_lld_once(){
	return get_csr_bits(REG_INFO.cs_lld_once());	//CSR39[0:0]
}

CS_clkRegs&
CS_clkRegs::setcs_lld_ref_cnt_dv(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_ref_cnt_dv());	//CSR40[14:12]
	return *this;
}
uint
CS_clkRegs::getcs_lld_ref_cnt_dv(){
	return get_csr_bits(REG_INFO.cs_lld_ref_cnt_dv());	//CSR40[14:12]
}

CS_clkRegs&
CS_clkRegs::setcs_lld_ref_cnt_lv(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_ref_cnt_lv());	//CSR40[11:0]
	return *this;
}
uint
CS_clkRegs::getcs_lld_ref_cnt_lv(){
	return get_csr_bits(REG_INFO.cs_lld_ref_cnt_lv());	//CSR40[11:0]
}

CS_clkRegs&
CS_clkRegs::setcs_lld_fb_cnt_dv(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_fb_cnt_dv());	//CSR41[14:12]
	return *this;
}
uint
CS_clkRegs::getcs_lld_fb_cnt_dv(){
	return get_csr_bits(REG_INFO.cs_lld_fb_cnt_dv());	//CSR41[14:12]
}

CS_clkRegs&
CS_clkRegs::setcs_lld_fb_cnt_lv(uint val){
	fill_csr_bits(val,REG_INFO.cs_lld_fb_cnt_lv());	//CSR41[11:0]
	return *this;
}
uint
CS_clkRegs::getcs_lld_fb_cnt_lv(){
	return get_csr_bits(REG_INFO.cs_lld_fb_cnt_lv());	//CSR41[11:0]
}

CS_clkRegs&
CS_clkRegs::setcs_lcd_fb_div_ratio(uint val){
	fill_csr_bits(val,REG_INFO.cs_lcd_fb_div_ratio());	//CSR42[9:1]
	return *this;
}
uint
CS_clkRegs::getcs_lcd_fb_div_ratio(){
	return get_csr_bits(REG_INFO.cs_lcd_fb_div_ratio());	//CSR42[9:1]
}

CS_clkRegs&
CS_clkRegs::setcs_lcd_override(uint val){
	fill_csr_bits(val,REG_INFO.cs_lcd_override());	//CSR42[0:0]
	return *this;
}
uint
CS_clkRegs::getcs_lcd_override(){
	return get_csr_bits(REG_INFO.cs_lcd_override());	//CSR42[0:0]
}

CS_clkRegs&
CS_clkRegs::setssc_freeze(uint val){
	fill_csr_bits(val,REG_INFO.ssc_freeze());	//CSR43[13:13]
	return *this;
}
uint
CS_clkRegs::getssc_freeze(){
	return get_csr_bits(REG_INFO.ssc_freeze());	//CSR43[13:13]
}

CS_clkRegs&
CS_clkRegs::setssc_freeze_mode(uint val){
	fill_csr_bits(val,REG_INFO.ssc_freeze_mode());	//CSR43[12:12]
	return *this;
}
uint
CS_clkRegs::getssc_freeze_mode(){
	return get_csr_bits(REG_INFO.ssc_freeze_mode());	//CSR43[12:12]
}

CS_clkRegs&
CS_clkRegs::setssc_freeze_en_sel(uint val){
	fill_csr_bits(val,REG_INFO.ssc_freeze_en_sel());	//CSR43[11:11]
	return *this;
}
uint
CS_clkRegs::getssc_freeze_en_sel(){
	return get_csr_bits(REG_INFO.ssc_freeze_en_sel());	//CSR43[11:11]
}

CS_clkRegs&
CS_clkRegs::setcs_lcd_fb_cnt_lv(uint val){
	fill_csr_bits(val,REG_INFO.cs_lcd_fb_cnt_lv());	//CSR43[10:0]
	return *this;
}
uint
CS_clkRegs::getcs_lcd_fb_cnt_lv(){
	return get_csr_bits(REG_INFO.cs_lcd_fb_cnt_lv());	//CSR43[10:0]
}

CS_clkRegs&
CS_clkRegs::setcp_dlf_resfdbkpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.cp_dlf_resfdbkpwrdb());	//CSR44[15:14]
	return *this;
}
uint
CS_clkRegs::getcp_dlf_resfdbkpwrdb(){
	return get_csr_bits(REG_INFO.cp_dlf_resfdbkpwrdb());	//CSR44[15:14]
}

CS_clkRegs&
CS_clkRegs::setcp_dlf_sample_edge_switch(uint val){
	fill_csr_bits(val,REG_INFO.cp_dlf_sample_edge_switch());	//CSR44[13:13]
	return *this;
}
uint
CS_clkRegs::getcp_dlf_sample_edge_switch(){
	return get_csr_bits(REG_INFO.cp_dlf_sample_edge_switch());	//CSR44[13:13]
}

CS_clkRegs&
CS_clkRegs::setcp_dlf_cmfb_switch(uint val){
	fill_csr_bits(val,REG_INFO.cp_dlf_cmfb_switch());	//CSR44[12:12]
	return *this;
}
uint
CS_clkRegs::getcp_dlf_cmfb_switch(){
	return get_csr_bits(REG_INFO.cp_dlf_cmfb_switch());	//CSR44[12:12]
}

CS_clkRegs&
CS_clkRegs::setrefclk1_cml_bias_ctrl(uint val){
	fill_csr_bits(val,REG_INFO.refclk1_cml_bias_ctrl());	//CSR44[11:10]
	return *this;
}
uint
CS_clkRegs::getrefclk1_cml_bias_ctrl(){
	return get_csr_bits(REG_INFO.refclk1_cml_bias_ctrl());	//CSR44[11:10]
}

CS_clkRegs&
CS_clkRegs::setrefclk0_cml_bias_ctrl(uint val){
	fill_csr_bits(val,REG_INFO.refclk0_cml_bias_ctrl());	//CSR44[9:8]
	return *this;
}
uint
CS_clkRegs::getrefclk0_cml_bias_ctrl(){
	return get_csr_bits(REG_INFO.refclk0_cml_bias_ctrl());	//CSR44[9:8]
}

CS_clkRegs&
CS_clkRegs::setcp_op_compensation_switch(uint val){
	fill_csr_bits(val,REG_INFO.cp_op_compensation_switch());	//CSR44[5:5]
	return *this;
}
uint
CS_clkRegs::getcp_op_compensation_switch(){
	return get_csr_bits(REG_INFO.cp_op_compensation_switch());	//CSR44[5:5]
}

CS_clkRegs&
CS_clkRegs::setcpcintsel(uint val){
	fill_csr_bits(val,REG_INFO.cpcintsel());	//CSR44[4:0]
	return *this;
}
uint
CS_clkRegs::getcpcintsel(){
	return get_csr_bits(REG_INFO.cpcintsel());	//CSR44[4:0]
}

CS_clkRegs&
CS_clkRegs::setssrefclk1_distbiasctrl(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk1_distbiasctrl());	//CSR45[15:14]
	return *this;
}
uint
CS_clkRegs::getssrefclk1_distbiasctrl(){
	return get_csr_bits(REG_INFO.ssrefclk1_distbiasctrl());	//CSR45[15:14]
}

CS_clkRegs&
CS_clkRegs::setssrefclk0_distbiasctrl(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk0_distbiasctrl());	//CSR45[13:12]
	return *this;
}
uint
CS_clkRegs::getssrefclk0_distbiasctrl(){
	return get_csr_bits(REG_INFO.ssrefclk0_distbiasctrl());	//CSR45[13:12]
}

CS_clkRegs&
CS_clkRegs::setssrefclk1_rcvbiasctrl(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk1_rcvbiasctrl());	//CSR45[11:10]
	return *this;
}
uint
CS_clkRegs::getssrefclk1_rcvbiasctrl(){
	return get_csr_bits(REG_INFO.ssrefclk1_rcvbiasctrl());	//CSR45[11:10]
}

CS_clkRegs&
CS_clkRegs::setssrefclk0_rcvbiasctrl(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk0_rcvbiasctrl());	//CSR45[9:8]
	return *this;
}
uint
CS_clkRegs::getssrefclk0_rcvbiasctrl(){
	return get_csr_bits(REG_INFO.ssrefclk0_rcvbiasctrl());	//CSR45[9:8]
}

CS_clkRegs&
CS_clkRegs::setss_slavemode(uint val){
	fill_csr_bits(val,REG_INFO.ss_slavemode());	//CSR45[7:7]
	return *this;
}
uint
CS_clkRegs::getss_slavemode(){
	return get_csr_bits(REG_INFO.ss_slavemode());	//CSR45[7:7]
}

CS_clkRegs&
CS_clkRegs::setcs_spare(uint val){
	fill_csr_bits(val,REG_INFO.cs_spare());	//CSR45[6:0]
	return *this;
}
uint
CS_clkRegs::getcs_spare(){
	return get_csr_bits(REG_INFO.cs_spare());	//CSR45[6:0]
}

CS_clkRegs&
CS_clkRegs::setcs_debugging_ctrl1(uint val){
	fill_csr_bits(val,REG_INFO.cs_debugging_ctrl1());	//CSR46[15:0]
	return *this;
}
uint
CS_clkRegs::getcs_debugging_ctrl1(){
	return get_csr_bits(REG_INFO.cs_debugging_ctrl1());	//CSR46[15:0]
}

CS_clkRegs&
CS_clkRegs::setbg_stu_ref_sel(uint val){
	fill_csr_bits(val,REG_INFO.bg_stu_ref_sel());	//CSR47[14:13]
	return *this;
}
uint
CS_clkRegs::getbg_stu_ref_sel(){
	return get_csr_bits(REG_INFO.bg_stu_ref_sel());	//CSR47[14:13]
}

CS_clkRegs&
CS_clkRegs::setbg_icv_ref_sel(uint val){
	fill_csr_bits(val,REG_INFO.bg_icv_ref_sel());	//CSR47[12:12]
	return *this;
}
uint
CS_clkRegs::getbg_icv_ref_sel(){
	return get_csr_bits(REG_INFO.bg_icv_ref_sel());	//CSR47[12:12]
}

uint
CS_clkRegs::getcs_lld_ref_freq(){
	return get_csr_bits(REG_INFO.cs_lld_ref_freq());	//CSR47[11:0]
}

CS_clkRegs&
CS_clkRegs::settempcompensel(uint val){
	fill_csr_bits(val,REG_INFO.tempcompensel());	//CSR48[15:14]
	return *this;
}
uint
CS_clkRegs::gettempcompensel(){
	return get_csr_bits(REG_INFO.tempcompensel());	//CSR48[15:14]
}

CS_clkRegs&
CS_clkRegs::settempcompensel_current(uint val){
	fill_csr_bits(val,REG_INFO.tempcompensel_current());	//CSR48[13:12]
	return *this;
}
uint
CS_clkRegs::gettempcompensel_current(){
	return get_csr_bits(REG_INFO.tempcompensel_current());	//CSR48[13:12]
}

uint
CS_clkRegs::getcs_fd_ref_freq(){
	return get_csr_bits(REG_INFO.cs_fd_ref_freq());	//CSR48[11:0]
}

CS_clkRegs&
CS_clkRegs::setvtuneshift_sel(uint val){
	fill_csr_bits(val,REG_INFO.vtuneshift_sel());	//CSR49[15:12]
	return *this;
}
uint
CS_clkRegs::getvtuneshift_sel(){
	return get_csr_bits(REG_INFO.vtuneshift_sel());	//CSR49[15:12]
}

uint
CS_clkRegs::getcs_fd_fb_freq(){
	return get_csr_bits(REG_INFO.cs_fd_fb_freq());	//CSR49[11:0]
}

uint
CS_clkRegs::getcs_fd_diff_freq(){
	return get_csr_bits(REG_INFO.cs_fd_diff_freq());	//CSR50[12:0]
}

uint
CS_clkRegs::getcs_lld_done(){
	return get_csr_bits(REG_INFO.cs_lld_done());	//CSR51[15:15]
}

uint
CS_clkRegs::getcs_lld_diff_freq(){
	return get_csr_bits(REG_INFO.cs_lld_diff_freq());	//CSR51[12:0]
}

uint
CS_clkRegs::getcs_lld_fb_freq(){
	return get_csr_bits(REG_INFO.cs_lld_fb_freq());	//CSR52[11:0]
}

uint
CS_clkRegs::getcs_misc_status(){
	return get_csr_bits(REG_INFO.cs_misc_status());	//CSR53[15:0]
}

uint
CS_clkRegs::getcs_calib_fsm_status(){
	return get_csr_bits(REG_INFO.cs_calib_fsm_status());	//CSR54[15:0]
}

uint
CS_clkRegs::getcs_gcalib_fsm_status(){
	return get_csr_bits(REG_INFO.cs_gcalib_fsm_status());	//CSR55[15:0]
}

CS_clkRegs&
CS_clkRegs::setssctype(uint val){
	fill_csr_bits(val,REG_INFO.ssctype());	//CSR56[15:14]
	return *this;
}
uint
CS_clkRegs::getssctype(){
	return get_csr_bits(REG_INFO.ssctype());	//CSR56[15:14]
}

CS_clkRegs&
CS_clkRegs::setsscfreq(uint val){
	fill_csr_bits(val,REG_INFO.sscfreq());	//CSR56[8:0]
	return *this;
}
uint
CS_clkRegs::getsscfreq(){
	return get_csr_bits(REG_INFO.sscfreq());	//CSR56[8:0]
}

CS_clkRegs&
CS_clkRegs::setssc_pulsewidth(uint val){
	fill_csr_bits(val,REG_INFO.ssc_pulsewidth());	//CSR57[13:12]
	return *this;
}
uint
CS_clkRegs::getssc_pulsewidth(){
	return get_csr_bits(REG_INFO.ssc_pulsewidth());	//CSR57[13:12]
}

CS_clkRegs&
CS_clkRegs::setssc_bypassb(uint val){
	fill_csr_bits(val,REG_INFO.ssc_bypassb());	//CSR57[7:7]
	return *this;
}
uint
CS_clkRegs::getssc_bypassb(){
	return get_csr_bits(REG_INFO.ssc_bypassb());	//CSR57[7:7]
}

CS_clkRegs&
CS_clkRegs::setsscamp(uint val){
	fill_csr_bits(val,REG_INFO.sscamp());	//CSR57[6:0]
	return *this;
}
uint
CS_clkRegs::getsscamp(){
	return get_csr_bits(REG_INFO.sscamp());	//CSR57[6:0]
}

CS_clkRegs&
CS_clkRegs::setssc_gen_clr(uint val){
	fill_csr_bits(val,REG_INFO.ssc_gen_clr());	//CSR58[15:15]
	return *this;
}
uint
CS_clkRegs::getssc_gen_clr(){
	return get_csr_bits(REG_INFO.ssc_gen_clr());	//CSR58[15:15]
}

CS_clkRegs&
CS_clkRegs::setssc_gen_soft_rstb(uint val){
	fill_csr_bits(val,REG_INFO.ssc_gen_soft_rstb());	//CSR58[14:14]
	return *this;
}
uint
CS_clkRegs::getssc_gen_soft_rstb(){
	return get_csr_bits(REG_INFO.ssc_gen_soft_rstb());	//CSR58[14:14]
}

CS_clkRegs&
CS_clkRegs::setssc_gen_start_mode(uint val){
	fill_csr_bits(val,REG_INFO.ssc_gen_start_mode());	//CSR58[13:13]
	return *this;
}
uint
CS_clkRegs::getssc_gen_start_mode(){
	return get_csr_bits(REG_INFO.ssc_gen_start_mode());	//CSR58[13:13]
}

CS_clkRegs&
CS_clkRegs::setcp_i_intchp_tune(uint val){
	fill_csr_bits(val,REG_INFO.cp_i_intchp_tune());	//CSR58[12:12]
	return *this;
}
uint
CS_clkRegs::getcp_i_intchp_tune(){
	return get_csr_bits(REG_INFO.cp_i_intchp_tune());	//CSR58[12:12]
}

CS_clkRegs&
CS_clkRegs::setpwrdb_pll0_wordclk2dig_32b(uint val){
	fill_csr_bits(val,REG_INFO.pwrdb_pll0_wordclk2dig_32b());	//CSR58[11:11]
	return *this;
}
uint
CS_clkRegs::getpwrdb_pll0_wordclk2dig_32b(){
	return get_csr_bits(REG_INFO.pwrdb_pll0_wordclk2dig_32b());	//CSR58[11:11]
}

CS_clkRegs&
CS_clkRegs::setlcvco_tempcompensate_pwrdb(uint val){
	fill_csr_bits(val,REG_INFO.lcvco_tempcompensate_pwrdb());	//CSR58[10:10]
	return *this;
}
uint
CS_clkRegs::getlcvco_tempcompensate_pwrdb(){
	return get_csr_bits(REG_INFO.lcvco_tempcompensate_pwrdb());	//CSR58[10:10]
}

CS_clkRegs&
CS_clkRegs::setssc_clksel(uint val){
	fill_csr_bits(val,REG_INFO.ssc_clksel());	//CSR58[9:9]
	return *this;
}
uint
CS_clkRegs::getssc_clksel(){
	return get_csr_bits(REG_INFO.ssc_clksel());	//CSR58[9:9]
}

CS_clkRegs&
CS_clkRegs::setssc_gen_manual_start(uint val){
	fill_csr_bits(val,REG_INFO.ssc_gen_manual_start());	//CSR58[8:8]
	return *this;
}
uint
CS_clkRegs::getssc_gen_manual_start(){
	return get_csr_bits(REG_INFO.ssc_gen_manual_start());	//CSR58[8:8]
}

CS_clkRegs&
CS_clkRegs::setssc_phswrite(uint val){
	fill_csr_bits(val,REG_INFO.ssc_phswrite());	//CSR58[5:0]
	return *this;
}
uint
CS_clkRegs::getssc_phswrite(){
	return get_csr_bits(REG_INFO.ssc_phswrite());	//CSR58[5:0]
}

uint
CS_clkRegs::getssc_picode(){
	return get_csr_bits(REG_INFO.ssc_picode());	//CSR59[4:0]
}

CS_clkRegs&
CS_clkRegs::setssc_picode_read_start(uint val){
	fill_csr_bits(val,REG_INFO.ssc_picode_read_start());	//CSR60[15:15]
	return *this;
}
uint
CS_clkRegs::getssc_picode_read_start(){
	return get_csr_bits(REG_INFO.ssc_picode_read_start());	//CSR60[15:15]
}

CS_clkRegs&
CS_clkRegs::setsscatt(uint val){
	fill_csr_bits(val,REG_INFO.sscatt());	//CSR60[14:12]
	return *this;
}
uint
CS_clkRegs::getsscatt(){
	return get_csr_bits(REG_INFO.sscatt());	//CSR60[14:12]
}

CS_clkRegs&
CS_clkRegs::setssc_spare(uint val){
	fill_csr_bits(val,REG_INFO.ssc_spare());	//CSR60[11:10]
	return *this;
}
uint
CS_clkRegs::getssc_spare(){
	return get_csr_bits(REG_INFO.ssc_spare());	//CSR60[11:10]
}

CS_clkRegs&
CS_clkRegs::setfbkclk_pulsewidth_mod(uint val){
	fill_csr_bits(val,REG_INFO.fbkclk_pulsewidth_mod());	//CSR60[9:9]
	return *this;
}
uint
CS_clkRegs::getfbkclk_pulsewidth_mod(){
	return get_csr_bits(REG_INFO.fbkclk_pulsewidth_mod());	//CSR60[9:9]
}

CS_clkRegs&
CS_clkRegs::setssc_pwrdb(uint val){
	fill_csr_bits(val,REG_INFO.ssc_pwrdb());	//CSR60[8:8]
	return *this;
}
uint
CS_clkRegs::getssc_pwrdb(){
	return get_csr_bits(REG_INFO.ssc_pwrdb());	//CSR60[8:8]
}

CS_clkRegs&
CS_clkRegs::setssc_picode_delay(uint val){
	fill_csr_bits(val,REG_INFO.ssc_picode_delay());	//CSR60[7:6]
	return *this;
}
uint
CS_clkRegs::getssc_picode_delay(){
	return get_csr_bits(REG_INFO.ssc_picode_delay());	//CSR60[7:6]
}

CS_clkRegs&
CS_clkRegs::setpiout_caps(uint val){
	fill_csr_bits(val,REG_INFO.piout_caps());	//CSR60[5:4]
	return *this;
}
uint
CS_clkRegs::getpiout_caps(){
	return get_csr_bits(REG_INFO.piout_caps());	//CSR60[5:4]
}

CS_clkRegs&
CS_clkRegs::setpidrvin_cur(uint val){
	fill_csr_bits(val,REG_INFO.pidrvin_cur());	//CSR60[3:2]
	return *this;
}
uint
CS_clkRegs::getpidrvin_cur(){
	return get_csr_bits(REG_INFO.pidrvin_cur());	//CSR60[3:2]
}

CS_clkRegs&
CS_clkRegs::setpidrvin_caps(uint val){
	fill_csr_bits(val,REG_INFO.pidrvin_caps());	//CSR60[1:0]
	return *this;
}
uint
CS_clkRegs::getpidrvin_caps(){
	return get_csr_bits(REG_INFO.pidrvin_caps());	//CSR60[1:0]
}

CS_clkRegs&
CS_clkRegs::setwordclkdiv2(uint val){
	fill_csr_bits(val,REG_INFO.wordclkdiv2());	//CSR61[15:15]
	return *this;
}
uint
CS_clkRegs::getwordclkdiv2(){
	return get_csr_bits(REG_INFO.wordclkdiv2());	//CSR61[15:15]
}

CS_clkRegs&
CS_clkRegs::setwordclkdiv(uint val){
	fill_csr_bits(val,REG_INFO.wordclkdiv());	//CSR61[14:13]
	return *this;
}
uint
CS_clkRegs::getwordclkdiv(){
	return get_csr_bits(REG_INFO.wordclkdiv());	//CSR61[14:13]
}

CS_clkRegs&
CS_clkRegs::setwordclkdiv2_16b32b(uint val){
	fill_csr_bits(val,REG_INFO.wordclkdiv2_16b32b());	//CSR61[12:12]
	return *this;
}
uint
CS_clkRegs::getwordclkdiv2_16b32b(){
	return get_csr_bits(REG_INFO.wordclkdiv2_16b32b());	//CSR61[12:12]
}

CS_clkRegs&
CS_clkRegs::setmeas_num(uint val){
	fill_csr_bits(val,REG_INFO.meas_num());	//CSR62[15:14]
	return *this;
}
uint
CS_clkRegs::getmeas_num(){
	return get_csr_bits(REG_INFO.meas_num());	//CSR62[15:14]
}

CS_clkRegs&
CS_clkRegs::settemp_clk_div(uint val){
	fill_csr_bits(val,REG_INFO.temp_clk_div());	//CSR62[13:5]
	return *this;
}
uint
CS_clkRegs::gettemp_clk_div(){
	return get_csr_bits(REG_INFO.temp_clk_div());	//CSR62[13:5]
}

CS_clkRegs&
CS_clkRegs::settsen_temp_en(uint val){
	fill_csr_bits(val,REG_INFO.tsen_temp_en());	//CSR62[4:4]
	return *this;
}
uint
CS_clkRegs::gettsen_temp_en(){
	return get_csr_bits(REG_INFO.tsen_temp_en());	//CSR62[4:4]
}

CS_clkRegs&
CS_clkRegs::settsen_temp_ct_sel(uint val){
	fill_csr_bits(val,REG_INFO.tsen_temp_ct_sel());	//CSR62[3:2]
	return *this;
}
uint
CS_clkRegs::gettsen_temp_ct_sel(){
	return get_csr_bits(REG_INFO.tsen_temp_ct_sel());	//CSR62[3:2]
}

uint
CS_clkRegs::getchip_temp_out(){
	return get_csr_bits(REG_INFO.chip_temp_out());	//CSR63[15:6]
}

