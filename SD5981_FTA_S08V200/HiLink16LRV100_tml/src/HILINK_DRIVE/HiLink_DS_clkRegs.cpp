#include <HILINK_DRIVE/HiLink_DS_clkRegs.h>
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
		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
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
	return HILINK_LANE_NUM;
}

uint
DS_clkRegs::getAddressMapToHiLink(int csrIndex){
	if(csrIndex>=DS_CLK_CSR_NUM){
		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	return (uint)(0x4000 | (broadcast << 13) | (sliceID << 9) | ((uint)/*SUBBLOCKID.*/2 << 7) | csrIndex << 1);
}


uint&
DS_clkRegs::get_csr(uint csrIndex){
	if(csrIndex>=DS_CLK_CSR_NUM){
		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//ERROR_EXIT(TM::ABORT_FLOW);
	}
	return csr[csrIndex];
}

void
DS_clkRegs::get_default_MacroLaneID(T_MacroLaneID& id){
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

E_HILINK_REGISTER_TYPE
DS_clkRegs::getType(){
	return HILINK_PERLANE_REGISTER;
}
///////////////////////////////////////////////////////////////////////////


	/// Dataslice clocking power down control. Active low.
	/// 0 = Power down all dsclk circuitry
	/// 1 = Power up all dsclk circuitry
	/// 
	/// Note: This function is not available at this moment.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkpwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{0,"dsclkpwrdb",15,15}
	};
	return reg;
}

	/// Select high-speed clock spine for both TX and RX.
	/// 0 = Select clock spine 0 from the clockslice 0
	/// 1 = Select clock spine 1 from the clockslice 1 (if applicable)
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::clkspinesel(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{0,"clkspinesel",14,14}
	};
	return reg;
}

	/// Select high-speed clock spine for TX if the TX is running at different from the RX.
	/// 0 = Select clock spine 0 from the clockslice 0
	/// 1 = Select clock spine 1 from the clockslice 1 (if applicable)
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::txclkspinesel(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{0,"txclkspinesel",13,13}
	};
	return reg;
}

	/// Reference clock div2 enable (part of 'L' divider).
	/// 0 = Do not use div2 on the DSCLK refclk path
	/// 1 = Use div2 on the DSCLK refclk path
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::refdiv2en(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{0,"refdiv2en",12,12}
	};
	return reg;
}

	/// 0 = Use ring oscillator to generated phases
	/// 1 = Use divider to generate phases for low data rate configuration
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::bypassdiven(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{0,"bypassdiven",11,11}
	};
	return reg;
}

	/// 0 = Use the clock from the TX phase interpolator for the TX path.
	/// 1 = Bypass the TX phase interpolator and use the clock selected from clock spines for the TX path.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::txbypassen(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{0,"txbypassen",10,10}
	};
	return reg;
}

	/// Ring-VCO out-of-lock threshold (by default, choose from 1/4096 to 31/4096).
	/// Note: For LCVCO to lock, this field should not be programmed to 0.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ringvcololthr(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{0,"ringvcololthr",9,5}
	};
	return reg;
}

	/// Ring-VCO loss-of-clock threshold.
	/// 000 = 128
	/// 001 = 256
	/// 010 = 512
	/// 011 = 1024
	/// 100 = 2048
	/// 101 = 4096
	/// 11x = 4096
	/// Not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ringvcolocthr(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{0,"ringvcolocthr",4,2}
	};
	return reg;
}

	/// DSCKL out of lock status
	/// 0 = DSCLK is locked
	/// 1 = DSCLK  is out of lock
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ringvcooutoflock(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{0,"ringvcooutoflock",1,1}
	};
	return reg;
}

	/// DSCLK loss of clock status
	/// 0 = DSCLK clock is not lost
	/// 1 = DSCLK clock is lost
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::lossofringvcoclk(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{0,"lossofringvcoclk",0,0}
	};
	return reg;
}

	/// This power down is for the whole dataslice.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsnmirpwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"dsnmirpwrdb",15,15}
	};
	return reg;
}

	/// 0 = Power down clock spine buffer 0 circuitry
	/// 1 = Power up all clock spine buffer 0 circuitry
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::buf0pwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"buf0pwrdb",14,14}
	};
	return reg;
}

	/// 0 = Power down clock spine buffer 1 circuitry
	/// 1 = Power up all clock spine buffer 1 circuitry
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::buf1pwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"buf1pwrdb",13,13}
	};
	return reg;
}

	/// 0 = power down injection clock to ring oscillator. 
	/// 1 = power up injection clock
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkgenpwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"dsclkgenpwrdb",12,12}
	};
	return reg;
}

	/// 0 = power down DSCLK  IDAC. 
	/// 1 = power up DSCLK IDAC
	/// Note: Powered down in bypass divider mode
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::idacpwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"idacpwrdb",11,11}
	};
	return reg;
}

	/// dsclk vregdac powerdown
	/// 0 = power down DSCLK IDAC Regulator. 
	/// 1 = power up DSCLK IDAC Regulator
	/// Note: Powered down in bypass divider mode
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vregdacpwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"vregdacpwrdb",10,10}
	};
	return reg;
}

	/// dsclk vregl powerdown
	/// 0 = power down DSCLK cml2cmos Regulator. 
	/// 1 = power up DSCLK cml2cmos Regulator
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vreglpwrdb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"vreglpwrdb",9,9}
	};
	return reg;
}

	/// dsclk lld feedback clock source selection signal
	/// 0 = rxcenterwordclk
	/// 1 = txcp_wordclk
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::lldclk_sel(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"lldclk_sel",8,8}
	};
	return reg;
}

	/// DSCLK lld start mode signal
	/// 0 = start automaticlly when dsclk calibration done
	/// 1 = start manually by configured register CSR10_DSCLK_LLD_START
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::lld_start_mode(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"lld_start_mode",7,7}
	};
	return reg;
}

	/// Enable calibration and observation of the IDAC output voltage,low active.
	/// 0: Enable.
	/// 1: Power down.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vcocalen(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"vcocalen",4,4}
	};
	return reg;
}

	/// Enable ILO calibration. ILO not injected,low active.
	/// 0: Enable.
	/// 1: Power down.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ilocalen(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"ilocalen",3,3}
	};
	return reg;
}

	/// Enable ILO injectors. 
	/// Disable during ILO calibration,low active.
	/// 0: Enable.
	/// 1: Power down.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::injen(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"injen",2,2}
	};
	return reg;
}

	/// (Unused)
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::oscclken(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"oscclken",1,1}
	};
	return reg;
}

	/// 0 = Disable bleed for IDAC Regulator
	/// 1 = Enable
	/// Not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vregbleeden(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{1,"vregbleeden",0,0}
	};
	return reg;
}

	/// DSCLK replicabias OP vref  selection
	/// 0=780
	/// 1=765
	/// 2=750
	/// 3=735
	/// 4=720
	/// 5=705
	/// 6=690
	/// 7=675
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::reprefsel(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{2,"reprefsel",14,12}
	};
	return reg;
}

	/// dsclk replicabias module vpbias selection
	/// 0= select dsclk_rep_loadctrl[2:0] output
	/// 1=560
	/// 2=460
	/// 3=360
	/// 4=310
	/// 5=260
	/// 6=210
	/// 7=160
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::reploadctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{2,"reploadctrl",10,8}
	};
	return reg;
}

	/// DSCLK south in channel CML bias selection
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::lane0ctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{2,"lane0ctrl",5,4}
	};
	return reg;
}

	/// DSCLK north in channel CML bias selection
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::lane1ctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{2,"lane1ctrl",3,2}
	};
	return reg;
}

	/// dsclk ilo hs clock CML bias selection
	/// when datarate>15Gbps(hsclk>7.5G), the uer should configure it to 00, others, the value is 2'b10
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::muxctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{2,"muxctrl",1,0}
	};
	return reg;
}

	/// biasscale[1]:
	/// 0=pidrive bias current of 50uA
	/// 1=pidriver bias current of 70uA
	/// biasscale[0]:
	/// 0=disable icv mix to icc bias currents
	/// 1=enable icv mix to icc bias currents
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::biasscale(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{3,"biasscale",15,14}
	};
	return reg;
}

	/// 0 = no additional offset current to IDAC
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ioscdacofst(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{3,"ioscdacofst",13,12}
	};
	return reg;
}

	/// Ring oscillator IDAC tune. Controls IDAC mirror ratio
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ioscptune(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{3,"ioscptune",10,8}
	};
	return reg;
}

	/// dsclk replicabias OP vref  selection
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_rep_refsel_mux(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{3,"dsclk_rep_refsel_mux",7,5}
	};
	return reg;
}

	/// Unused
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ioscscale(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{3,"ioscscale",4,0}
	};
	return reg;
}

	/// Ring oscillator regulator level control, Not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vregdaclvl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{4,"vregdaclvl",14,12}
	};
	return reg;
}

	/// dsclk vregl voltage control
	/// 000 = 0.83V
	/// 001 = 0.86V
	/// 010 = 0.90V
	/// 011 = 0.95V
	/// 100 = 1.01V
	/// 101 = 1.03V
	/// 110 = 1.06V
	/// 111 = 1.08V
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vreglowlvl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{4,"vreglowlvl",10,8}
	};
	return reg;
}

	/// Used for slew rate control of the ILO 8 phase bypass divider. DSCLK_LDIVSLEWCTRL[2:0] = floor(divider_out_clk/250MHz)-1
	/// Not used, repetition with DSCLK_BYPASS_DIV_SLEW
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_ldivslewctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{4,"dsclk_ldivslewctrl",6,4}
	};
	return reg;
}

	/// dsclk PI driver current bias control
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::tunepidrv(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{4,"tunepidrv",3,1}
	};
	return reg;
}

	/// Reset should enabled and then disabled before using the bypass divider to ensure output phases are correct.
	/// 0 = enable reset
	/// 1 = disable reset
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::refclkdivrstb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{4,"refclkdivrstb",0,0}
	};
	return reg;
}

	/// Bit[5:4] of DSSPARE.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsspare5to4(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{5,"dsspare5to4",13,12}
	};
	return reg;
}

	/// Ring-VCO amplitude reference for calibration. Table units in mV.
	/// 0=648
	/// 1=633
	/// 2=618
	/// 3=603
	/// 4=588
	/// 5=573
	/// 6=558
	/// 7=543
	/// 8=534
	/// 9=518
	/// 10=503
	/// 11=488
	/// 12=473
	/// 13=458
	/// 14=443
	/// 15=428
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::voscref(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{5,"voscref",11,8}
	};
	return reg;
}

	/// Ring-VCO bias current. Used for calibration.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ioscdaccal(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{5,"ioscdaccal",7,0}
	};
	return reg;
}

	/// 0 = default
	/// 1 = increase cross coupling factor in ring
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ilocrosstune(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{6,"ilocrosstune",15,15}
	};
	return reg;
}

	/// Ring oscillator injection strength control:
	/// '000': disable main path injectors
	/// '001':  
	/// '010:
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::injlvl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{6,"injlvl",14,12}
	};
	return reg;
}

	/// Secondary path ring oscillator injection tuning 
	/// '000': disable secondary path injectors
	/// '001':  
	/// '010:
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::injtune(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{6,"injtune",10,8}
	};
	return reg;
}

	/// VCO Main Path Strength
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::psel(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{6,"psel",7,5}
	};
	return reg;
}

	/// VCO Secondary Path 1 Strength
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::s1sel(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{6,"s1sel",4,2}
	};
	return reg;
}

	/// VCO Secondary Path 2 Strength
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::s2sel(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{6,"s2sel",1,0}
	};
	return reg;
}

	/// n/c
	/// icvp_atb
	/// iccp50_atb
	/// vosc_vref
	/// tiehi
	/// hvcc
	/// tielo
	/// vss
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkbiasatbctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{7,"dsclkbiasatbctrl",15,12}
	};
	return reg;
}

	/// n/c
	/// clkgen_atb
	/// dsclkreg_atb
	/// bias_atb
	/// vpbias
	/// vregdac
	/// lvcc
	/// vss
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclktopatbctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{7,"dsclktopatbctrl",11,9}
	};
	return reg;
}

	/// n/c
	/// inp_atb
	/// vosc
	/// pbias0
	/// pbias
	/// vpcasc
	/// itest
	/// vregdac
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkgenatbctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{7,"dsclkgenatbctrl",8,6}
	};
	return reg;
}

	/// 0 = bias receivers operate normally
	/// 1 = sample the icvp50uA current from DSCLK bias receivers
	/// 2 = sample the iptatp50uA current from DSCLK bias receivers
	/// 3 = sample the iccp50uA current from DSCLK bias receivers
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkrxbiasatbctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{7,"dsclkrxbiasatbctrl",5,4}
	};
	return reg;
}

	/// 0000=nc
	/// 1000=vregdac
	/// 1xxx=nc
	/// 0001=vref
	/// 0010=vregout
	/// 0011=vgp
	/// 0100=vgpc
	/// 0101=vbiasn
	/// 0110=vmir_lf
	/// 0111=vmir_hf
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkregsatbctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{7,"dsclkregsatbctrl",3,0}
	};
	return reg;
}

	/// Bit[3:0] of DSSPARE.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsspare3to0(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{8,"dsspare3to0",15,12}
	};
	return reg;
}

	/// Dataslice top-level ATB Control
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dstopatbctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{8,"dstopatbctrl",10,8}
	};
	return reg;
}

	/// default: b00011011
	/// set ptatmixctrl[2:0] = ptatmixctrl[5:3]
	///  ptatmixctrl[6]=
	///  ptatmixctrl[7]=
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ptatmixctrl(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{8,"ptatmixctrl",7,0}
	};
	return reg;
}

	/// DSCLK global reset. Active low.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkrstb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{9,"dsclkrstb",15,15}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkdigspare1(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{9,"dsclkdigspare1",14,14}
	};
	return reg;
}

	/// Calibration mode for RXCTLE offset
	/// 0 = Automatic calibration
	/// 1 = Manual calibration
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::rxctle_stx_offset_mode(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{9,"rxctle_stx_offset_mode",13,13}
	};
	return reg;
}

	/// 000 = Auto-calibration algorithm 1
	/// 001 = Auto-calibration algorithm 2
	/// 010 = Auto-calibration algorithm 3
	/// 011 = Auto-calibration full scan
	/// 100 = Manual calibration
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::autotune(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{9,"autotune",12,10}
	};
	return reg;
}

	/// DSCLK calibration done clear signal
	/// 0 = keep unchaged 
	/// 1 = clear dsclkcaldone  to zero
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkcaldone_clr(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{9,"dsclkcaldone_clr",8,8}
	};
	return reg;
}

	/// Direction control for the comparator calibration.
	/// 0 = TBD
	/// 1 = TBD
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkcompcaldir(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{9,"dsclkcompcaldir",7,7}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkdigspare2(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{9,"dsclkdigspare2",6,6}
	};
	return reg;
}

	/// DSCLK calibraion done status, Active high.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkcaldone(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{9,"dsclkcaldone",5,5}
	};
	return reg;
}

	/// DSCLK calibration result error status,Active high.
	/// 1: Error
	/// 0: Not error
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkcalerr(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{9,"dsclkcalerr",4,4}
	};
	return reg;
}

	/// Current status for DSCLK calibration control state machine
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::autotunestatus(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{9,"autotunestatus",3,0}
	};
	return reg;
}

	/// Start DSCLK frequency detector. Active high.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_fd_start(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{10,"dsclk_fd_start",14,14}
	};
	return reg;
}

	/// Clear the loss of lock detector. Active high.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lld_clr(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{10,"dsclk_lld_clr",13,13}
	};
	return reg;
}

	/// Clear the frequency detector. Active high.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_fd_clr(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{10,"dsclk_fd_clr",12,12}
	};
	return reg;
}

	/// Clear the status of calibration. Active high.
	/// Not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_calib_clr(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{10,"dsclk_calib_clr",11,11}
	};
	return reg;
}

	/// Start DSCLK loss of clock detector. Active rising edge.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lcd_start(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{10,"dsclk_lcd_start",10,10}
	};
	return reg;
}

	/// Start DSCLK loss of lock detector. Active rising edge.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lld_start(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{10,"dsclk_lld_start",9,9}
	};
	return reg;
}

	/// Start DSCLK calibration. Active rising edge.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_calib_start(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{10,"dsclk_calib_start",8,8}
	};
	return reg;
}

	/// Enable DSCLK loss of clock detector. Active high.
	/// 0 = Don't enable the detector, Gating the clock
	/// 1 = Enable the detector.
	/// Not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lcd_enable(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{10,"dsclk_lcd_enable",7,7}
	};
	return reg;
}

	/// Enable DSCLK loss of lock detector. Active high.
	/// 0 = Don't enable the detector, Gating the clock
	/// 1 = Enable the detector.
	/// Not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lld_enable(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{10,"dsclk_lld_enable",6,6}
	};
	return reg;
}

	/// Enable DSCLK calibration. Active high.
	/// 0 = Don't enable calibration, Gating the clock
	/// 1 = Enable calibration
	/// Not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_calib_enable(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{10,"dsclk_calib_enable",5,5}
	};
	return reg;
}

	/// DSCLK loss of clock detector reset. Active low.
	/// 0 = Reset loss of clock detector part
	/// 1 = Reset is not active
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lcd_soft_rst_n(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{10,"dsclk_lcd_soft_rst_n",4,4}
	};
	return reg;
}

	/// DSCLK loss of lock detector reset. Active low.
	/// 0 = Reset loss of lock detector part
	/// 1 = Reset is not active
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lld_soft_rst_n(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{10,"dsclk_lld_soft_rst_n",3,3}
	};
	return reg;
}

	/// DSCLK calibration reset. Active low.
	/// 0 = Reset calibration part
	/// 1 = Reset is not active.
	/// Not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_calib_soft_rst_n(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{10,"dsclk_calib_soft_rst_n",2,2}
	};
	return reg;
}

	/// DSCLK bus reset. Active low.
	/// 0 = Reset bus part
	/// 1 = Reset is not active
	/// Not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_bus_soft_rst_n(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{10,"dsclk_bus_soft_rst_n",1,1}
	};
	return reg;
}

	/// DSCLK global reset. Active low.
	/// 0 = Reset whole digital circuit
	/// 1 = Reset is not active
	/// Not used, repetitionon with register DSCLKRSTB
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_glb_soft_rst_n(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{10,"dsclk_glb_soft_rst_n",0,0}
	};
	return reg;
}

	/// dsclk regl selfbleed
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_regl_selfbleed(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{11,"dsclk_regl_selfbleed",14,11}
	};
	return reg;
}

	/// Threshold set for DSCLK frequency detection
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_fd_threshold(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{11,"dsclk_fd_threshold",10,1}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_meas_fd_wait(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{11,"dsclk_meas_fd_wait",0,0}
	};
	return reg;
}

	/// Timer divide parameter set for frequency detection counter in ref_clk clock
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_fd_ref_cnt_dv(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{12,"dsclk_fd_ref_cnt_dv",13,12}
	};
	return reg;
}

	/// Timer parameter set for  for frequency detection counter in ref_clk clock
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_fd_ref_cnt_lv(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{12,"dsclk_fd_ref_cnt_lv",11,0}
	};
	return reg;
}

	/// Timer divide parameter set for frequency detection counter in fb_clk  clock
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_fd_fb_cnt_dv(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{13,"dsclk_fd_fb_cnt_dv",13,12}
	};
	return reg;
}

	/// Timer parameter set for  for frequency detection counter in fb_clk clock
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_fd_fb_cnt_lv(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{13,"dsclk_fd_fb_cnt_lv",11,0}
	};
	return reg;
}

	/// DSCLK calibration timer divide parameter set
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_timer_value(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{14,"dsclk_timer_value",14,5}
	};
	return reg;
}

	/// DSCLK calibration timer  parameter set
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_timer_div_value(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{14,"dsclk_timer_div_value",4,2}
	};
	return reg;
}

	/// DSCLK calibration timer  enable, Active high
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_timer_div_en(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{14,"dsclk_timer_div_en",1,1}
	};
	return reg;
}

	/// DSCLK calibration stop  control , Active high
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_timer_stop(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{14,"dsclk_timer_stop",0,0}
	};
	return reg;
}

	/// Not used, repetition with register RINGVCOLOLTHR[4:0]
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lld_lck_threshold(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{15,"dsclk_lld_lck_threshold",13,4}
	};
	return reg;
}

	/// Timer divide parameter set  for DSCLK loss of lock detection
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lld_fb_div_ratio(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{15,"dsclk_lld_fb_div_ratio",3,1}
	};
	return reg;
}

	/// DSCLK loss of lock detection time,
	/// 1: Only detection one time after start
	/// 0: More than one timer after start
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lld_once(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{15,"dsclk_lld_once",0,0}
	};
	return reg;
}

	/// Timer divide parameter set for LLD counter in ref_clk clock
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lld_ref_cnt_dv(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{16,"dsclk_lld_ref_cnt_dv",14,12}
	};
	return reg;
}

	/// Timer parameter set for  for LLD counter in ref_clk clock
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lld_ref_cnt_lv(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{16,"dsclk_lld_ref_cnt_lv",11,0}
	};
	return reg;
}

	/// Timer divide parameter set for LLD counter in fb_clk clock
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lld_fb_cnt_dv(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{17,"dsclk_lld_fb_cnt_dv",14,12}
	};
	return reg;
}

	/// Timer parameter set for  for LLD counter in fb_clk clock
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lld_fb_cnt_lv(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{17,"dsclk_lld_fb_cnt_lv",11,0}
	};
	return reg;
}

	/// dsclk mux replicabias module vpbias selection
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_rep_loadctrl_mux(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{18,"dsclk_rep_loadctrl_mux",12,10}
	};
	return reg;
}

	/// Timer divide parameter set for LCD counter in fb_clk clock
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lcd_fb_div_ratio(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{18,"dsclk_lcd_fb_div_ratio",9,1}
	};
	return reg;
}

	/// Override to clear the LCD status, active high
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lcd_override(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{18,"dsclk_lcd_override",0,0}
	};
	return reg;
}

	/// Timer parameter set for LCD counter in fb_clk clock,Only bit [2:0] valid
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lcd_fb_cnt_lv(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{19,"dsclk_lcd_fb_cnt_lv",11,0}
	};
	return reg;
}

	/// Not used
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_debugging_ctrl1(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{20,"dsclk_debugging_ctrl1",15,0}
	};
	return reg;
}

	/// Counter value for DSCLK FD in ref_clk clock
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_fd_ref_freq(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{21,"dsclk_fd_ref_freq",11,0}
	};
	return reg;
}

	/// Counter value for DSCLK FD in fb_clk clock
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_fd_fb_freq(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{22,"dsclk_fd_fb_freq",11,0}
	};
	return reg;
}

	/// Counter different value for DSCLK_FD_FB_FREQ with DSCLK_FD_REF_FREQ
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_fd_diff_freq(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{23,"dsclk_fd_diff_freq",12,0}
	};
	return reg;
}

	/// Lock of loss detection done, high active
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lld_done(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{24,"dsclk_lld_done",15,15}
	};
	return reg;
}

	/// Counter different value for LLD counter in fb_clk and ref_clk clock
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lld_diff_freq(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{24,"dsclk_lld_diff_freq",12,0}
	};
	return reg;
}

	/// Counter  value for LLD  in fb_clk clock
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lld_fb_freq(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{25,"dsclk_lld_fb_freq",11,0}
	};
	return reg;
}

	/// DSCLK calibration status 
	/// [15]    : Loss of clock detection done.
	///              1: Detection done.
	///              0: Detection not done.
	/// [14:2] : Reserved
	/// [1]      :  Low offset comparator status from analog and the default value is 1
	/// [0]      : Frequency detection lock status 
	///              1:  Lock.
	///              0:  Not Lock.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_misc_status(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{26,"dsclk_misc_status",15,0}
	};
	return reg;
}

	/// Calibrated value for VOSCREF
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_calib_voscref(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{27,"dsclk_calib_voscref",15,12}
	};
	return reg;
}

	/// Calibrated value for IOSCDACCAL
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_calib_ioscdaccal(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{27,"dsclk_calib_ioscdaccal",11,4}
	};
	return reg;
}

	/// set the slew of pidiv input divider clocking; 
	/// skew[2:0]= floor (fckin/250M) -1 ;
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_bypass_div_slew(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{28,"dsclk_bypass_div_slew",15,13}
	};
	return reg;
}

	/// Counter  value for LLD  in ref_clk clock
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_lld_ref_freq(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{28,"dsclk_lld_ref_freq",11,0}
	};
	return reg;
}

	/// ptatmix configure value when vco curve value is 0x4
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ptatmix_vco_4(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{29,"ptatmix_vco_4",15,8}
	};
	return reg;
}

	/// dsclk PI driver reference voltage control.
	/// 00 = 0.75*Lvcc
	/// 01 = 0.80*Lvcc
	/// 10 = 0.85*Lvcc
	/// 11 = 0.90*Lvcc
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_pidrv_refsel(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{29,"dsclk_pidrv_refsel",6,5}
	};
	return reg;
}

	/// dsclk cml2cmos powerdown, low active.
	/// 0 = Power down.
	/// 1 = Power up.
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_cml2cmos_pwrdnb(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{29,"dsclk_cml2cmos_pwrdnb",4,4}
	};
	return reg;
}

	/// Select high-speed clock spine for both TX and RX as pin data 
	/// rate switch, the register only valid in PCIe/SATA/SAS mode.
	/// 1 = Select clock spine not by pin rate switch logic
	/// 0 = Select clock spine  by pin rate swtich logic
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::clkspine_sw_sel(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{29,"clkspine_sw_sel",2,2}
	};
	return reg;
}

	/// Select high-speed clock spine for TX if the TX is running at different from the RX as pin rate switch, the register only valid in PCIe/SATA/SAS mode.
	/// 1 = Select clock spine not by pin rate switch
	/// 0 = Select clock spine  from pin rate switch logic
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::txclkspine_sw_sel(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{29,"txclkspine_sw_sel",1,1}
	};
	return reg;
}

	/// ptatmix configure value when vco curve value is 0x5
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ptatmix_vco_5(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{30,"ptatmix_vco_5",15,8}
	};
	return reg;
}

	/// ptatmix configure value when vco curve value is 0x6
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ptatmix_vco_6(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{30,"ptatmix_vco_6",7,0}
	};
	return reg;
}

	/// ptatmix configure value when vco curve value is 0x7
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ptatmix_vco_7(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{31,"ptatmix_vco_7",15,8}
	};
	return reg;
}

	/// ptatmix configure value when vco curve value is 0x8
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ptatmix_vco_8(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{31,"ptatmix_vco_8",7,0}
	};
	return reg;
}

	/// ptatmix configure value when vco curve value is 0x9
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ptatmix_vco_9(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{32,"ptatmix_vco_9",15,8}
	};
	return reg;
}

	/// ptatmix configure value when vco curve value is 0xA
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ptatmix_vco_a(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{32,"ptatmix_vco_a",7,0}
	};
	return reg;
}

	/// ptatmix configure value when vco curve value is 0xB
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ptatmix_vco_b(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{33,"ptatmix_vco_b",15,8}
	};
	return reg;
}

	/// ptatmix configure value when vco curve value is 0xC
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ptatmix_vco_c(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{33,"ptatmix_vco_c",7,0}
	};
	return reg;
}

	/// ptatmix configure value when vco curve value is 0xD
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ptatmix_vco_d(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{34,"ptatmix_vco_d",15,8}
	};
	return reg;
}

	/// ptatmix configure value when vco curve value is 0xE
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ptatmix_vco_e(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{34,"ptatmix_vco_e",7,0}
	};
	return reg;
}

	/// ptatmix configure value when vco curve value is 0xF
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::ptatmix_vco_f(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{35,"ptatmix_vco_f",15,8}
	};
	return reg;
}

	/// Spare for DSCLK analog.
	/// DSCLKSPARE[2] control Regulator loading adjust power down and the default value is 1
	/// DSCLKSPARE[1:0] control Regulator reference voltage tuning and the default value is 10.
	/// 00: 0.717V
	/// 01: 0.777V
	/// 10: 0.797V
	/// 11: 0.827V
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclkspare(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{35,"dsclkspare",7,0}
	};
	return reg;
}

	/// dsclk calibration ioscdacctrl min value
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::idac_min(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{36,"idac_min",15,8}
	};
	return reg;
}

	/// dsclk calibration ioscdacctrl value and its max value is 255
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::idac_max(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{36,"idac_max",7,0}
	};
	return reg;
}

	/// dsclk calibration transition counter min value
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::trans_min(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{37,"trans_min",15,12}
	};
	return reg;
}

	/// dsclk calibration transition counter max value
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::trans_max(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{37,"trans_max",11,8}
	};
	return reg;
}

	/// dsclk calibration vco curve min value
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vco_min(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{37,"vco_min",7,4}
	};
	return reg;
}

	/// dsclk calibration vco curve max value
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::vco_max(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{37,"vco_max",3,0}
	};
	return reg;
}

	/// dsclk calibration mapping psel  code when vco curve value is 4
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_psel_vco_4(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{38,"dsclk_psel_vco_4",15,13}
	};
	return reg;
}

	/// dsclk calibration mapping s1sel  code when vco curve value is 4
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s1sel_vco_4(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{38,"dsclk_s1sel_vco_4",12,10}
	};
	return reg;
}

	/// dsclk calibration mapping s2sel  code when vco curve value is 4
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s2sel_vco_4(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{38,"dsclk_s2sel_vco_4",9,8}
	};
	return reg;
}

	/// dsclk calibration mapping inject level  code when vco curve value is 4
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injlev_vco_4(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{38,"dsclk_injlev_vco_4",6,4}
	};
	return reg;
}

	/// dsclk calibration mapping inject tune code when vco curve value is 4
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injtune_vco_4(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{38,"dsclk_injtune_vco_4",2,0}
	};
	return reg;
}

	/// dsclk calibration mapping psel  code when vco curve value is 5
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_psel_vco_5(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{39,"dsclk_psel_vco_5",15,13}
	};
	return reg;
}

	/// dsclk calibration mapping s1sel  code when vco curve value is 5
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s1sel_vco_5(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{39,"dsclk_s1sel_vco_5",12,10}
	};
	return reg;
}

	/// dsclk calibration mapping s2sel  code when vco curve value is 5
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s2sel_vco_5(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{39,"dsclk_s2sel_vco_5",9,8}
	};
	return reg;
}

	/// dsclk calibration mapping inject level  code when vco curve value is 5
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injlev_vco_5(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{39,"dsclk_injlev_vco_5",6,4}
	};
	return reg;
}

	/// dsclk calibration mapping inject tune code when vco curve value is 5
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injtune_vco_5(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{39,"dsclk_injtune_vco_5",2,0}
	};
	return reg;
}

	/// dsclk calibration mapping psel  code when vco curve value is 6
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_psel_vco_6(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{40,"dsclk_psel_vco_6",15,13}
	};
	return reg;
}

	/// dsclk calibration mapping s1sel  code when vco curve value is 6
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s1sel_vco_6(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{40,"dsclk_s1sel_vco_6",12,10}
	};
	return reg;
}

	/// dsclk calibration mapping s2sel  code when vco curve value is 6
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s2sel_vco_6(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{40,"dsclk_s2sel_vco_6",9,8}
	};
	return reg;
}

	/// dsclk calibration mapping inject level  code when vco curve value is 6
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injlev_vco_6(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{40,"dsclk_injlev_vco_6",6,4}
	};
	return reg;
}

	/// dsclk calibration mapping inject tune code when vco curve value is 6
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injtune_vco_6(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{40,"dsclk_injtune_vco_6",2,0}
	};
	return reg;
}

	/// dsclk calibration mapping psel  code when vco curve value is 7
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_psel_vco_7(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{41,"dsclk_psel_vco_7",15,13}
	};
	return reg;
}

	/// dsclk calibration mapping s1sel  code when vco curve value is 7
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s1sel_vco_7(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{41,"dsclk_s1sel_vco_7",12,10}
	};
	return reg;
}

	/// dsclk calibration mapping s2sel  code when vco curve value is 7
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s2sel_vco_7(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{41,"dsclk_s2sel_vco_7",9,8}
	};
	return reg;
}

	/// dsclk calibration mapping inject level  code when vco curve value is 7
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injlev_vco_7(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{41,"dsclk_injlev_vco_7",6,4}
	};
	return reg;
}

	/// dsclk calibration mapping inject tune code when vco curve value is 7
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injtune_vco_7(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{41,"dsclk_injtune_vco_7",2,0}
	};
	return reg;
}

	/// dsclk calibration mapping psel  code when vco curve value is  8
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_psel_vco_8(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{42,"dsclk_psel_vco_8",15,13}
	};
	return reg;
}

	/// dsclk calibration mapping s1sel  code when vco curve value is  8
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s1sel_vco_8(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{42,"dsclk_s1sel_vco_8",12,10}
	};
	return reg;
}

	/// dsclk calibration mapping s2sel  code when vco curve value is  8
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s2sel_vco_8(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{42,"dsclk_s2sel_vco_8",9,8}
	};
	return reg;
}

	/// dsclk calibration mapping inject level  code when vco curve value is  8
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injlev_vco_8(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{42,"dsclk_injlev_vco_8",6,4}
	};
	return reg;
}

	/// dsclk calibration mapping inject tune code when vco curve value is 8
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injtune_vco_8(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{42,"dsclk_injtune_vco_8",2,0}
	};
	return reg;
}

	/// dsclk calibration mapping psel  code when vco curve value is 9
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_psel_vco_9(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{43,"dsclk_psel_vco_9",15,13}
	};
	return reg;
}

	/// dsclk calibration mapping s1sel  code when vco curve value is 9
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s1sel_vco_9(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{43,"dsclk_s1sel_vco_9",12,10}
	};
	return reg;
}

	/// dsclk calibration mapping s2sel  code when vco curve value is 9
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s2sel_vco_9(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{43,"dsclk_s2sel_vco_9",9,8}
	};
	return reg;
}

	/// dsclk calibration mapping inject level  code when vco curve value is 9
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injlev_vco_9(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{43,"dsclk_injlev_vco_9",6,4}
	};
	return reg;
}

	/// dsclk calibration mapping inject tune code when vco curve value is 9
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injtune_vco_9(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{43,"dsclk_injtune_vco_9",2,0}
	};
	return reg;
}

	/// dsclk calibration mapping psel  code when vco curve value is 10
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_psel_vco_a(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{44,"dsclk_psel_vco_a",15,13}
	};
	return reg;
}

	/// dsclk calibration mapping s1sel  code when vco curve value is 10
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s1sel_vco_a(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{44,"dsclk_s1sel_vco_a",12,10}
	};
	return reg;
}

	/// dsclk calibration mapping s2sel  code when vco curve value is 10
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s2sel_vco_a(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{44,"dsclk_s2sel_vco_a",9,8}
	};
	return reg;
}

	/// dsclk calibration mapping inject level  code when vco curve value is 10
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injlev_vco_a(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{44,"dsclk_injlev_vco_a",6,4}
	};
	return reg;
}

	/// dsclk calibration mapping inject tune code when vco curve value is 10
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injtune_vco_a(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{44,"dsclk_injtune_vco_a",2,0}
	};
	return reg;
}

	/// dsclk calibration mapping psel  code when vco curve value is 11
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_psel_vco_b(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{45,"dsclk_psel_vco_b",15,13}
	};
	return reg;
}

	/// dsclk calibration mapping s1sel  code when vco curve value is 11
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s1sel_vco_b(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{45,"dsclk_s1sel_vco_b",12,10}
	};
	return reg;
}

	/// dsclk calibration mapping s2sel  code when vco curve value is 11
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s2sel_vco_b(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{45,"dsclk_s2sel_vco_b",9,8}
	};
	return reg;
}

	/// dsclk calibration mapping inject level  code when vco curve value is 11
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injlev_vco_b(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{45,"dsclk_injlev_vco_b",6,4}
	};
	return reg;
}

	/// dsclk calibration mapping inject tune code when vco curve value is 11
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injtune_vco_b(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{45,"dsclk_injtune_vco_b",2,0}
	};
	return reg;
}

	/// dsclk calibration mapping psel  code when vco curve value is 12
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_psel_vco_c(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{46,"dsclk_psel_vco_c",15,13}
	};
	return reg;
}

	/// dsclk calibration mapping s1sel  code when vco curve value is 12
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s1sel_vco_c(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{46,"dsclk_s1sel_vco_c",12,10}
	};
	return reg;
}

	/// dsclk calibration mapping s2sel  code when vco curve value is 12
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s2sel_vco_c(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{46,"dsclk_s2sel_vco_c",9,8}
	};
	return reg;
}

	/// dsclk calibration mapping inject level  code when vco curve value is 12
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injlev_vco_c(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{46,"dsclk_injlev_vco_c",6,4}
	};
	return reg;
}

	/// dsclk calibration mapping inject tune code when vco curve value is 12
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injtune_vco_c(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{46,"dsclk_injtune_vco_c",2,0}
	};
	return reg;
}

	/// dsclk calibration mapping psel  code when vco curve value is 13
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_psel_vco_d(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{47,"dsclk_psel_vco_d",15,13}
	};
	return reg;
}

	/// dsclk calibration mapping s1sel  code when vco curve value is 13
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s1sel_vco_d(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{47,"dsclk_s1sel_vco_d",12,10}
	};
	return reg;
}

	/// dsclk calibration mapping s2sel  code when vco curve value is 13
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s2sel_vco_d(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{47,"dsclk_s2sel_vco_d",9,8}
	};
	return reg;
}

	/// dsclk calibration mapping inject level  code when vco curve value is 13
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injlev_vco_d(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{47,"dsclk_injlev_vco_d",6,4}
	};
	return reg;
}

	/// dsclk calibration mapping inject tune code when vco curve value is 13
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injtune_vco_d(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{47,"dsclk_injtune_vco_d",2,0}
	};
	return reg;
}

	/// dsclk calibration mapping psel  code when vco curve value is 14
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_psel_vco_e(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{48,"dsclk_psel_vco_e",15,13}
	};
	return reg;
}

	/// dsclk calibration mapping s1sel  code when vco curve value is 14
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s1sel_vco_e(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{48,"dsclk_s1sel_vco_e",12,10}
	};
	return reg;
}

	/// dsclk calibration mapping s2sel  code when vco curve value is 14
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s2sel_vco_e(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{48,"dsclk_s2sel_vco_e",9,8}
	};
	return reg;
}

	/// dsclk calibration mapping inject level  code when vco curve value is 14
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injlev_vco_e(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{48,"dsclk_injlev_vco_e",6,4}
	};
	return reg;
}

	/// dsclk calibration mapping inject tune code when vco curve value is 14
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injtune_vco_e(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{48,"dsclk_injtune_vco_e",2,0}
	};
	return reg;
}

	/// dsclk calibration mapping psel  code when vco curve value is 15
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_psel_vco_f(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{49,"dsclk_psel_vco_f",15,13}
	};
	return reg;
}

	/// dsclk calibration mapping s1sel  code when vco curve value is 15
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s1sel_vco_f(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{49,"dsclk_s1sel_vco_f",12,10}
	};
	return reg;
}

	/// dsclk calibration mapping s2sel  code when vco curve value is 15
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_s2sel_vco_f(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{49,"dsclk_s2sel_vco_f",9,8}
	};
	return reg;
}

	/// dsclk calibration mapping inject level  code when vco curve value is 15
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injlev_vco_f(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{49,"dsclk_injlev_vco_f",6,4}
	};
	return reg;
}

	/// dsclk calibration mapping inject tune code when vco curve value is 15
const T_REG_INFO_EX&
DS_clkRegs::_REG_INFO::dsclk_injtune_vco_f(){
	const static T_REG_INFO_EX reg={DS_clkRegs::getInstance(),
		{49,"dsclk_injtune_vco_f",2,0}
	};
	return reg;
}
bool
DS_clkRegs::_REG_INFO::get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos){
	reg_infos.clear();
	switch(csr){
		case 0:
			reg_infos.push_back(dsclkpwrdb().reg_info);
			reg_infos.push_back(clkspinesel().reg_info);
			reg_infos.push_back(txclkspinesel().reg_info);
			reg_infos.push_back(refdiv2en().reg_info);
			reg_infos.push_back(bypassdiven().reg_info);
			reg_infos.push_back(txbypassen().reg_info);
			reg_infos.push_back(ringvcololthr().reg_info);
			reg_infos.push_back(ringvcolocthr().reg_info);
			reg_infos.push_back(ringvcooutoflock().reg_info);
			reg_infos.push_back(lossofringvcoclk().reg_info);
			break;
		case 1:
			reg_infos.push_back(dsnmirpwrdb().reg_info);
			reg_infos.push_back(buf0pwrdb().reg_info);
			reg_infos.push_back(buf1pwrdb().reg_info);
			reg_infos.push_back(dsclkgenpwrdb().reg_info);
			reg_infos.push_back(idacpwrdb().reg_info);
			reg_infos.push_back(vregdacpwrdb().reg_info);
			reg_infos.push_back(vreglpwrdb().reg_info);
			reg_infos.push_back(lldclk_sel().reg_info);
			reg_infos.push_back(lld_start_mode().reg_info);
			reg_infos.push_back(vcocalen().reg_info);
			reg_infos.push_back(ilocalen().reg_info);
			reg_infos.push_back(injen().reg_info);
			reg_infos.push_back(oscclken().reg_info);
			reg_infos.push_back(vregbleeden().reg_info);
			break;
		case 2:
			reg_infos.push_back(reprefsel().reg_info);
			reg_infos.push_back(reploadctrl().reg_info);
			reg_infos.push_back(lane0ctrl().reg_info);
			reg_infos.push_back(lane1ctrl().reg_info);
			reg_infos.push_back(muxctrl().reg_info);
			break;
		case 3:
			reg_infos.push_back(biasscale().reg_info);
			reg_infos.push_back(ioscdacofst().reg_info);
			reg_infos.push_back(ioscptune().reg_info);
			reg_infos.push_back(dsclk_rep_refsel_mux().reg_info);
			reg_infos.push_back(ioscscale().reg_info);
			break;
		case 4:
			reg_infos.push_back(vregdaclvl().reg_info);
			reg_infos.push_back(vreglowlvl().reg_info);
			reg_infos.push_back(dsclk_ldivslewctrl().reg_info);
			reg_infos.push_back(tunepidrv().reg_info);
			reg_infos.push_back(refclkdivrstb().reg_info);
			break;
		case 5:
			reg_infos.push_back(dsspare5to4().reg_info);
			reg_infos.push_back(voscref().reg_info);
			reg_infos.push_back(ioscdaccal().reg_info);
			break;
		case 6:
			reg_infos.push_back(ilocrosstune().reg_info);
			reg_infos.push_back(injlvl().reg_info);
			reg_infos.push_back(injtune().reg_info);
			reg_infos.push_back(psel().reg_info);
			reg_infos.push_back(s1sel().reg_info);
			reg_infos.push_back(s2sel().reg_info);
			break;
		case 7:
			reg_infos.push_back(dsclkbiasatbctrl().reg_info);
			reg_infos.push_back(dsclktopatbctrl().reg_info);
			reg_infos.push_back(dsclkgenatbctrl().reg_info);
			reg_infos.push_back(dsclkrxbiasatbctrl().reg_info);
			reg_infos.push_back(dsclkregsatbctrl().reg_info);
			break;
		case 8:
			reg_infos.push_back(dsspare3to0().reg_info);
			reg_infos.push_back(dstopatbctrl().reg_info);
			reg_infos.push_back(ptatmixctrl().reg_info);
			break;
		case 9:
			reg_infos.push_back(dsclkrstb().reg_info);
			reg_infos.push_back(dsclkdigspare1().reg_info);
			reg_infos.push_back(rxctle_stx_offset_mode().reg_info);
			reg_infos.push_back(autotune().reg_info);
			reg_infos.push_back(dsclkcaldone_clr().reg_info);
			reg_infos.push_back(dsclkcompcaldir().reg_info);
			reg_infos.push_back(dsclkdigspare2().reg_info);
			reg_infos.push_back(dsclkcaldone().reg_info);
			reg_infos.push_back(dsclkcalerr().reg_info);
			reg_infos.push_back(autotunestatus().reg_info);
			break;
		case 10:
			reg_infos.push_back(dsclk_fd_start().reg_info);
			reg_infos.push_back(dsclk_lld_clr().reg_info);
			reg_infos.push_back(dsclk_fd_clr().reg_info);
			reg_infos.push_back(dsclk_calib_clr().reg_info);
			reg_infos.push_back(dsclk_lcd_start().reg_info);
			reg_infos.push_back(dsclk_lld_start().reg_info);
			reg_infos.push_back(dsclk_calib_start().reg_info);
			reg_infos.push_back(dsclk_lcd_enable().reg_info);
			reg_infos.push_back(dsclk_lld_enable().reg_info);
			reg_infos.push_back(dsclk_calib_enable().reg_info);
			reg_infos.push_back(dsclk_lcd_soft_rst_n().reg_info);
			reg_infos.push_back(dsclk_lld_soft_rst_n().reg_info);
			reg_infos.push_back(dsclk_calib_soft_rst_n().reg_info);
			reg_infos.push_back(dsclk_bus_soft_rst_n().reg_info);
			reg_infos.push_back(dsclk_glb_soft_rst_n().reg_info);
			break;
		case 11:
			reg_infos.push_back(dsclk_regl_selfbleed().reg_info);
			reg_infos.push_back(dsclk_fd_threshold().reg_info);
			reg_infos.push_back(dsclk_meas_fd_wait().reg_info);
			break;
		case 12:
			reg_infos.push_back(dsclk_fd_ref_cnt_dv().reg_info);
			reg_infos.push_back(dsclk_fd_ref_cnt_lv().reg_info);
			break;
		case 13:
			reg_infos.push_back(dsclk_fd_fb_cnt_dv().reg_info);
			reg_infos.push_back(dsclk_fd_fb_cnt_lv().reg_info);
			break;
		case 14:
			reg_infos.push_back(dsclk_timer_value().reg_info);
			reg_infos.push_back(dsclk_timer_div_value().reg_info);
			reg_infos.push_back(dsclk_timer_div_en().reg_info);
			reg_infos.push_back(dsclk_timer_stop().reg_info);
			break;
		case 15:
			reg_infos.push_back(dsclk_lld_lck_threshold().reg_info);
			reg_infos.push_back(dsclk_lld_fb_div_ratio().reg_info);
			reg_infos.push_back(dsclk_lld_once().reg_info);
			break;
		case 16:
			reg_infos.push_back(dsclk_lld_ref_cnt_dv().reg_info);
			reg_infos.push_back(dsclk_lld_ref_cnt_lv().reg_info);
			break;
		case 17:
			reg_infos.push_back(dsclk_lld_fb_cnt_dv().reg_info);
			reg_infos.push_back(dsclk_lld_fb_cnt_lv().reg_info);
			break;
		case 18:
			reg_infos.push_back(dsclk_rep_loadctrl_mux().reg_info);
			reg_infos.push_back(dsclk_lcd_fb_div_ratio().reg_info);
			reg_infos.push_back(dsclk_lcd_override().reg_info);
			break;
		case 19:
			reg_infos.push_back(dsclk_lcd_fb_cnt_lv().reg_info);
			break;
		case 20:
			reg_infos.push_back(dsclk_debugging_ctrl1().reg_info);
			break;
		case 21:
			reg_infos.push_back(dsclk_fd_ref_freq().reg_info);
			break;
		case 22:
			reg_infos.push_back(dsclk_fd_fb_freq().reg_info);
			break;
		case 23:
			reg_infos.push_back(dsclk_fd_diff_freq().reg_info);
			break;
		case 24:
			reg_infos.push_back(dsclk_lld_done().reg_info);
			reg_infos.push_back(dsclk_lld_diff_freq().reg_info);
			break;
		case 25:
			reg_infos.push_back(dsclk_lld_fb_freq().reg_info);
			break;
		case 26:
			reg_infos.push_back(dsclk_misc_status().reg_info);
			break;
		case 27:
			reg_infos.push_back(dsclk_calib_voscref().reg_info);
			reg_infos.push_back(dsclk_calib_ioscdaccal().reg_info);
			break;
		case 28:
			reg_infos.push_back(dsclk_bypass_div_slew().reg_info);
			reg_infos.push_back(dsclk_lld_ref_freq().reg_info);
			break;
		case 29:
			reg_infos.push_back(ptatmix_vco_4().reg_info);
			reg_infos.push_back(dsclk_pidrv_refsel().reg_info);
			reg_infos.push_back(dsclk_cml2cmos_pwrdnb().reg_info);
			reg_infos.push_back(clkspine_sw_sel().reg_info);
			reg_infos.push_back(txclkspine_sw_sel().reg_info);
			break;
		case 30:
			reg_infos.push_back(ptatmix_vco_5().reg_info);
			reg_infos.push_back(ptatmix_vco_6().reg_info);
			break;
		case 31:
			reg_infos.push_back(ptatmix_vco_7().reg_info);
			reg_infos.push_back(ptatmix_vco_8().reg_info);
			break;
		case 32:
			reg_infos.push_back(ptatmix_vco_9().reg_info);
			reg_infos.push_back(ptatmix_vco_a().reg_info);
			break;
		case 33:
			reg_infos.push_back(ptatmix_vco_b().reg_info);
			reg_infos.push_back(ptatmix_vco_c().reg_info);
			break;
		case 34:
			reg_infos.push_back(ptatmix_vco_d().reg_info);
			reg_infos.push_back(ptatmix_vco_e().reg_info);
			break;
		case 35:
			reg_infos.push_back(ptatmix_vco_f().reg_info);
			reg_infos.push_back(dsclkspare().reg_info);
			break;
		case 36:
			reg_infos.push_back(idac_min().reg_info);
			reg_infos.push_back(idac_max().reg_info);
			break;
		case 37:
			reg_infos.push_back(trans_min().reg_info);
			reg_infos.push_back(trans_max().reg_info);
			reg_infos.push_back(vco_min().reg_info);
			reg_infos.push_back(vco_max().reg_info);
			break;
		case 38:
			reg_infos.push_back(dsclk_psel_vco_4().reg_info);
			reg_infos.push_back(dsclk_s1sel_vco_4().reg_info);
			reg_infos.push_back(dsclk_s2sel_vco_4().reg_info);
			reg_infos.push_back(dsclk_injlev_vco_4().reg_info);
			reg_infos.push_back(dsclk_injtune_vco_4().reg_info);
			break;
		case 39:
			reg_infos.push_back(dsclk_psel_vco_5().reg_info);
			reg_infos.push_back(dsclk_s1sel_vco_5().reg_info);
			reg_infos.push_back(dsclk_s2sel_vco_5().reg_info);
			reg_infos.push_back(dsclk_injlev_vco_5().reg_info);
			reg_infos.push_back(dsclk_injtune_vco_5().reg_info);
			break;
		case 40:
			reg_infos.push_back(dsclk_psel_vco_6().reg_info);
			reg_infos.push_back(dsclk_s1sel_vco_6().reg_info);
			reg_infos.push_back(dsclk_s2sel_vco_6().reg_info);
			reg_infos.push_back(dsclk_injlev_vco_6().reg_info);
			reg_infos.push_back(dsclk_injtune_vco_6().reg_info);
			break;
		case 41:
			reg_infos.push_back(dsclk_psel_vco_7().reg_info);
			reg_infos.push_back(dsclk_s1sel_vco_7().reg_info);
			reg_infos.push_back(dsclk_s2sel_vco_7().reg_info);
			reg_infos.push_back(dsclk_injlev_vco_7().reg_info);
			reg_infos.push_back(dsclk_injtune_vco_7().reg_info);
			break;
		case 42:
			reg_infos.push_back(dsclk_psel_vco_8().reg_info);
			reg_infos.push_back(dsclk_s1sel_vco_8().reg_info);
			reg_infos.push_back(dsclk_s2sel_vco_8().reg_info);
			reg_infos.push_back(dsclk_injlev_vco_8().reg_info);
			reg_infos.push_back(dsclk_injtune_vco_8().reg_info);
			break;
		case 43:
			reg_infos.push_back(dsclk_psel_vco_9().reg_info);
			reg_infos.push_back(dsclk_s1sel_vco_9().reg_info);
			reg_infos.push_back(dsclk_s2sel_vco_9().reg_info);
			reg_infos.push_back(dsclk_injlev_vco_9().reg_info);
			reg_infos.push_back(dsclk_injtune_vco_9().reg_info);
			break;
		case 44:
			reg_infos.push_back(dsclk_psel_vco_a().reg_info);
			reg_infos.push_back(dsclk_s1sel_vco_a().reg_info);
			reg_infos.push_back(dsclk_s2sel_vco_a().reg_info);
			reg_infos.push_back(dsclk_injlev_vco_a().reg_info);
			reg_infos.push_back(dsclk_injtune_vco_a().reg_info);
			break;
		case 45:
			reg_infos.push_back(dsclk_psel_vco_b().reg_info);
			reg_infos.push_back(dsclk_s1sel_vco_b().reg_info);
			reg_infos.push_back(dsclk_s2sel_vco_b().reg_info);
			reg_infos.push_back(dsclk_injlev_vco_b().reg_info);
			reg_infos.push_back(dsclk_injtune_vco_b().reg_info);
			break;
		case 46:
			reg_infos.push_back(dsclk_psel_vco_c().reg_info);
			reg_infos.push_back(dsclk_s1sel_vco_c().reg_info);
			reg_infos.push_back(dsclk_s2sel_vco_c().reg_info);
			reg_infos.push_back(dsclk_injlev_vco_c().reg_info);
			reg_infos.push_back(dsclk_injtune_vco_c().reg_info);
			break;
		case 47:
			reg_infos.push_back(dsclk_psel_vco_d().reg_info);
			reg_infos.push_back(dsclk_s1sel_vco_d().reg_info);
			reg_infos.push_back(dsclk_s2sel_vco_d().reg_info);
			reg_infos.push_back(dsclk_injlev_vco_d().reg_info);
			reg_infos.push_back(dsclk_injtune_vco_d().reg_info);
			break;
		case 48:
			reg_infos.push_back(dsclk_psel_vco_e().reg_info);
			reg_infos.push_back(dsclk_s1sel_vco_e().reg_info);
			reg_infos.push_back(dsclk_s2sel_vco_e().reg_info);
			reg_infos.push_back(dsclk_injlev_vco_e().reg_info);
			reg_infos.push_back(dsclk_injtune_vco_e().reg_info);
			break;
		case 49:
			reg_infos.push_back(dsclk_psel_vco_f().reg_info);
			reg_infos.push_back(dsclk_s1sel_vco_f().reg_info);
			reg_infos.push_back(dsclk_s2sel_vco_f().reg_info);
			reg_infos.push_back(dsclk_injlev_vco_f().reg_info);
			reg_infos.push_back(dsclk_injtune_vco_f().reg_info);
			break;
		default:
			break;
	}
	return (reg_infos.size()>0);
}


DS_clkRegs&
DS_clkRegs::setdsclkpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.dsclkpwrdb());	//CSR0[15:15]
	return *this;
}
uint
DS_clkRegs::getdsclkpwrdb(){
	return get_csr_bits(REG_INFO.dsclkpwrdb());	//CSR0[15:15]
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
DS_clkRegs::settxclkspinesel(uint val){
	fill_csr_bits(val,REG_INFO.txclkspinesel());	//CSR0[13:13]
	return *this;
}
uint
DS_clkRegs::gettxclkspinesel(){
	return get_csr_bits(REG_INFO.txclkspinesel());	//CSR0[13:13]
}

DS_clkRegs&
DS_clkRegs::setrefdiv2en(uint val){
	fill_csr_bits(val,REG_INFO.refdiv2en());	//CSR0[12:12]
	return *this;
}
uint
DS_clkRegs::getrefdiv2en(){
	return get_csr_bits(REG_INFO.refdiv2en());	//CSR0[12:12]
}

DS_clkRegs&
DS_clkRegs::setbypassdiven(uint val){
	fill_csr_bits(val,REG_INFO.bypassdiven());	//CSR0[11:11]
	return *this;
}
uint
DS_clkRegs::getbypassdiven(){
	return get_csr_bits(REG_INFO.bypassdiven());	//CSR0[11:11]
}

DS_clkRegs&
DS_clkRegs::settxbypassen(uint val){
	fill_csr_bits(val,REG_INFO.txbypassen());	//CSR0[10:10]
	return *this;
}
uint
DS_clkRegs::gettxbypassen(){
	return get_csr_bits(REG_INFO.txbypassen());	//CSR0[10:10]
}

DS_clkRegs&
DS_clkRegs::setringvcololthr(uint val){
	fill_csr_bits(val,REG_INFO.ringvcololthr());	//CSR0[9:5]
	return *this;
}
uint
DS_clkRegs::getringvcololthr(){
	return get_csr_bits(REG_INFO.ringvcololthr());	//CSR0[9:5]
}

DS_clkRegs&
DS_clkRegs::setringvcolocthr(uint val){
	fill_csr_bits(val,REG_INFO.ringvcolocthr());	//CSR0[4:2]
	return *this;
}
uint
DS_clkRegs::getringvcolocthr(){
	return get_csr_bits(REG_INFO.ringvcolocthr());	//CSR0[4:2]
}

uint
DS_clkRegs::getringvcooutoflock(){
	return get_csr_bits(REG_INFO.ringvcooutoflock());	//CSR0[1:1]
}

uint
DS_clkRegs::getlossofringvcoclk(){
	return get_csr_bits(REG_INFO.lossofringvcoclk());	//CSR0[0:0]
}

DS_clkRegs&
DS_clkRegs::setdsnmirpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.dsnmirpwrdb());	//CSR1[15:15]
	return *this;
}
uint
DS_clkRegs::getdsnmirpwrdb(){
	return get_csr_bits(REG_INFO.dsnmirpwrdb());	//CSR1[15:15]
}

DS_clkRegs&
DS_clkRegs::setbuf0pwrdb(uint val){
	fill_csr_bits(val,REG_INFO.buf0pwrdb());	//CSR1[14:14]
	return *this;
}
uint
DS_clkRegs::getbuf0pwrdb(){
	return get_csr_bits(REG_INFO.buf0pwrdb());	//CSR1[14:14]
}

DS_clkRegs&
DS_clkRegs::setbuf1pwrdb(uint val){
	fill_csr_bits(val,REG_INFO.buf1pwrdb());	//CSR1[13:13]
	return *this;
}
uint
DS_clkRegs::getbuf1pwrdb(){
	return get_csr_bits(REG_INFO.buf1pwrdb());	//CSR1[13:13]
}

DS_clkRegs&
DS_clkRegs::setdsclkgenpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.dsclkgenpwrdb());	//CSR1[12:12]
	return *this;
}
uint
DS_clkRegs::getdsclkgenpwrdb(){
	return get_csr_bits(REG_INFO.dsclkgenpwrdb());	//CSR1[12:12]
}

DS_clkRegs&
DS_clkRegs::setidacpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.idacpwrdb());	//CSR1[11:11]
	return *this;
}
uint
DS_clkRegs::getidacpwrdb(){
	return get_csr_bits(REG_INFO.idacpwrdb());	//CSR1[11:11]
}

DS_clkRegs&
DS_clkRegs::setvregdacpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.vregdacpwrdb());	//CSR1[10:10]
	return *this;
}
uint
DS_clkRegs::getvregdacpwrdb(){
	return get_csr_bits(REG_INFO.vregdacpwrdb());	//CSR1[10:10]
}

DS_clkRegs&
DS_clkRegs::setvreglpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.vreglpwrdb());	//CSR1[9:9]
	return *this;
}
uint
DS_clkRegs::getvreglpwrdb(){
	return get_csr_bits(REG_INFO.vreglpwrdb());	//CSR1[9:9]
}

DS_clkRegs&
DS_clkRegs::setlldclk_sel(uint val){
	fill_csr_bits(val,REG_INFO.lldclk_sel());	//CSR1[8:8]
	return *this;
}
uint
DS_clkRegs::getlldclk_sel(){
	return get_csr_bits(REG_INFO.lldclk_sel());	//CSR1[8:8]
}

DS_clkRegs&
DS_clkRegs::setlld_start_mode(uint val){
	fill_csr_bits(val,REG_INFO.lld_start_mode());	//CSR1[7:7]
	return *this;
}
uint
DS_clkRegs::getlld_start_mode(){
	return get_csr_bits(REG_INFO.lld_start_mode());	//CSR1[7:7]
}

DS_clkRegs&
DS_clkRegs::setvcocalen(uint val){
	fill_csr_bits(val,REG_INFO.vcocalen());	//CSR1[4:4]
	return *this;
}
uint
DS_clkRegs::getvcocalen(){
	return get_csr_bits(REG_INFO.vcocalen());	//CSR1[4:4]
}

DS_clkRegs&
DS_clkRegs::setilocalen(uint val){
	fill_csr_bits(val,REG_INFO.ilocalen());	//CSR1[3:3]
	return *this;
}
uint
DS_clkRegs::getilocalen(){
	return get_csr_bits(REG_INFO.ilocalen());	//CSR1[3:3]
}

DS_clkRegs&
DS_clkRegs::setinjen(uint val){
	fill_csr_bits(val,REG_INFO.injen());	//CSR1[2:2]
	return *this;
}
uint
DS_clkRegs::getinjen(){
	return get_csr_bits(REG_INFO.injen());	//CSR1[2:2]
}

DS_clkRegs&
DS_clkRegs::setoscclken(uint val){
	fill_csr_bits(val,REG_INFO.oscclken());	//CSR1[1:1]
	return *this;
}
uint
DS_clkRegs::getoscclken(){
	return get_csr_bits(REG_INFO.oscclken());	//CSR1[1:1]
}

DS_clkRegs&
DS_clkRegs::setvregbleeden(uint val){
	fill_csr_bits(val,REG_INFO.vregbleeden());	//CSR1[0:0]
	return *this;
}
uint
DS_clkRegs::getvregbleeden(){
	return get_csr_bits(REG_INFO.vregbleeden());	//CSR1[0:0]
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
DS_clkRegs::setreploadctrl(uint val){
	fill_csr_bits(val,REG_INFO.reploadctrl());	//CSR2[10:8]
	return *this;
}
uint
DS_clkRegs::getreploadctrl(){
	return get_csr_bits(REG_INFO.reploadctrl());	//CSR2[10:8]
}

DS_clkRegs&
DS_clkRegs::setlane0ctrl(uint val){
	fill_csr_bits(val,REG_INFO.lane0ctrl());	//CSR2[5:4]
	return *this;
}
uint
DS_clkRegs::getlane0ctrl(){
	return get_csr_bits(REG_INFO.lane0ctrl());	//CSR2[5:4]
}

DS_clkRegs&
DS_clkRegs::setlane1ctrl(uint val){
	fill_csr_bits(val,REG_INFO.lane1ctrl());	//CSR2[3:2]
	return *this;
}
uint
DS_clkRegs::getlane1ctrl(){
	return get_csr_bits(REG_INFO.lane1ctrl());	//CSR2[3:2]
}

DS_clkRegs&
DS_clkRegs::setmuxctrl(uint val){
	fill_csr_bits(val,REG_INFO.muxctrl());	//CSR2[1:0]
	return *this;
}
uint
DS_clkRegs::getmuxctrl(){
	return get_csr_bits(REG_INFO.muxctrl());	//CSR2[1:0]
}

DS_clkRegs&
DS_clkRegs::setbiasscale(uint val){
	fill_csr_bits(val,REG_INFO.biasscale());	//CSR3[15:14]
	return *this;
}
uint
DS_clkRegs::getbiasscale(){
	return get_csr_bits(REG_INFO.biasscale());	//CSR3[15:14]
}

DS_clkRegs&
DS_clkRegs::setioscdacofst(uint val){
	fill_csr_bits(val,REG_INFO.ioscdacofst());	//CSR3[13:12]
	return *this;
}
uint
DS_clkRegs::getioscdacofst(){
	return get_csr_bits(REG_INFO.ioscdacofst());	//CSR3[13:12]
}

DS_clkRegs&
DS_clkRegs::setioscptune(uint val){
	fill_csr_bits(val,REG_INFO.ioscptune());	//CSR3[10:8]
	return *this;
}
uint
DS_clkRegs::getioscptune(){
	return get_csr_bits(REG_INFO.ioscptune());	//CSR3[10:8]
}

DS_clkRegs&
DS_clkRegs::setdsclk_rep_refsel_mux(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_rep_refsel_mux());	//CSR3[7:5]
	return *this;
}
uint
DS_clkRegs::getdsclk_rep_refsel_mux(){
	return get_csr_bits(REG_INFO.dsclk_rep_refsel_mux());	//CSR3[7:5]
}

DS_clkRegs&
DS_clkRegs::setioscscale(uint val){
	fill_csr_bits(val,REG_INFO.ioscscale());	//CSR3[4:0]
	return *this;
}
uint
DS_clkRegs::getioscscale(){
	return get_csr_bits(REG_INFO.ioscscale());	//CSR3[4:0]
}

DS_clkRegs&
DS_clkRegs::setvregdaclvl(uint val){
	fill_csr_bits(val,REG_INFO.vregdaclvl());	//CSR4[14:12]
	return *this;
}
uint
DS_clkRegs::getvregdaclvl(){
	return get_csr_bits(REG_INFO.vregdaclvl());	//CSR4[14:12]
}

DS_clkRegs&
DS_clkRegs::setvreglowlvl(uint val){
	fill_csr_bits(val,REG_INFO.vreglowlvl());	//CSR4[10:8]
	return *this;
}
uint
DS_clkRegs::getvreglowlvl(){
	return get_csr_bits(REG_INFO.vreglowlvl());	//CSR4[10:8]
}

DS_clkRegs&
DS_clkRegs::setdsclk_ldivslewctrl(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_ldivslewctrl());	//CSR4[6:4]
	return *this;
}
uint
DS_clkRegs::getdsclk_ldivslewctrl(){
	return get_csr_bits(REG_INFO.dsclk_ldivslewctrl());	//CSR4[6:4]
}

DS_clkRegs&
DS_clkRegs::settunepidrv(uint val){
	fill_csr_bits(val,REG_INFO.tunepidrv());	//CSR4[3:1]
	return *this;
}
uint
DS_clkRegs::gettunepidrv(){
	return get_csr_bits(REG_INFO.tunepidrv());	//CSR4[3:1]
}

DS_clkRegs&
DS_clkRegs::setrefclkdivrstb(uint val){
	fill_csr_bits(val,REG_INFO.refclkdivrstb());	//CSR4[0:0]
	return *this;
}
uint
DS_clkRegs::getrefclkdivrstb(){
	return get_csr_bits(REG_INFO.refclkdivrstb());	//CSR4[0:0]
}

DS_clkRegs&
DS_clkRegs::setdsspare5to4(uint val){
	fill_csr_bits(val,REG_INFO.dsspare5to4());	//CSR5[13:12]
	return *this;
}
uint
DS_clkRegs::getdsspare5to4(){
	return get_csr_bits(REG_INFO.dsspare5to4());	//CSR5[13:12]
}

DS_clkRegs&
DS_clkRegs::setvoscref(uint val){
	fill_csr_bits(val,REG_INFO.voscref());	//CSR5[11:8]
	return *this;
}
uint
DS_clkRegs::getvoscref(){
	return get_csr_bits(REG_INFO.voscref());	//CSR5[11:8]
}

DS_clkRegs&
DS_clkRegs::setioscdaccal(uint val){
	fill_csr_bits(val,REG_INFO.ioscdaccal());	//CSR5[7:0]
	return *this;
}
uint
DS_clkRegs::getioscdaccal(){
	return get_csr_bits(REG_INFO.ioscdaccal());	//CSR5[7:0]
}

DS_clkRegs&
DS_clkRegs::setilocrosstune(uint val){
	fill_csr_bits(val,REG_INFO.ilocrosstune());	//CSR6[15:15]
	return *this;
}
uint
DS_clkRegs::getilocrosstune(){
	return get_csr_bits(REG_INFO.ilocrosstune());	//CSR6[15:15]
}

DS_clkRegs&
DS_clkRegs::setinjlvl(uint val){
	fill_csr_bits(val,REG_INFO.injlvl());	//CSR6[14:12]
	return *this;
}
uint
DS_clkRegs::getinjlvl(){
	return get_csr_bits(REG_INFO.injlvl());	//CSR6[14:12]
}

DS_clkRegs&
DS_clkRegs::setinjtune(uint val){
	fill_csr_bits(val,REG_INFO.injtune());	//CSR6[10:8]
	return *this;
}
uint
DS_clkRegs::getinjtune(){
	return get_csr_bits(REG_INFO.injtune());	//CSR6[10:8]
}

DS_clkRegs&
DS_clkRegs::setpsel(uint val){
	fill_csr_bits(val,REG_INFO.psel());	//CSR6[7:5]
	return *this;
}
uint
DS_clkRegs::getpsel(){
	return get_csr_bits(REG_INFO.psel());	//CSR6[7:5]
}

DS_clkRegs&
DS_clkRegs::sets1sel(uint val){
	fill_csr_bits(val,REG_INFO.s1sel());	//CSR6[4:2]
	return *this;
}
uint
DS_clkRegs::gets1sel(){
	return get_csr_bits(REG_INFO.s1sel());	//CSR6[4:2]
}

DS_clkRegs&
DS_clkRegs::sets2sel(uint val){
	fill_csr_bits(val,REG_INFO.s2sel());	//CSR6[1:0]
	return *this;
}
uint
DS_clkRegs::gets2sel(){
	return get_csr_bits(REG_INFO.s2sel());	//CSR6[1:0]
}

DS_clkRegs&
DS_clkRegs::setdsclkbiasatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.dsclkbiasatbctrl());	//CSR7[15:12]
	return *this;
}
uint
DS_clkRegs::getdsclkbiasatbctrl(){
	return get_csr_bits(REG_INFO.dsclkbiasatbctrl());	//CSR7[15:12]
}

DS_clkRegs&
DS_clkRegs::setdsclktopatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.dsclktopatbctrl());	//CSR7[11:9]
	return *this;
}
uint
DS_clkRegs::getdsclktopatbctrl(){
	return get_csr_bits(REG_INFO.dsclktopatbctrl());	//CSR7[11:9]
}

DS_clkRegs&
DS_clkRegs::setdsclkgenatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.dsclkgenatbctrl());	//CSR7[8:6]
	return *this;
}
uint
DS_clkRegs::getdsclkgenatbctrl(){
	return get_csr_bits(REG_INFO.dsclkgenatbctrl());	//CSR7[8:6]
}

DS_clkRegs&
DS_clkRegs::setdsclkrxbiasatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.dsclkrxbiasatbctrl());	//CSR7[5:4]
	return *this;
}
uint
DS_clkRegs::getdsclkrxbiasatbctrl(){
	return get_csr_bits(REG_INFO.dsclkrxbiasatbctrl());	//CSR7[5:4]
}

DS_clkRegs&
DS_clkRegs::setdsclkregsatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.dsclkregsatbctrl());	//CSR7[3:0]
	return *this;
}
uint
DS_clkRegs::getdsclkregsatbctrl(){
	return get_csr_bits(REG_INFO.dsclkregsatbctrl());	//CSR7[3:0]
}

DS_clkRegs&
DS_clkRegs::setdsspare3to0(uint val){
	fill_csr_bits(val,REG_INFO.dsspare3to0());	//CSR8[15:12]
	return *this;
}
uint
DS_clkRegs::getdsspare3to0(){
	return get_csr_bits(REG_INFO.dsspare3to0());	//CSR8[15:12]
}

DS_clkRegs&
DS_clkRegs::setdstopatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.dstopatbctrl());	//CSR8[10:8]
	return *this;
}
uint
DS_clkRegs::getdstopatbctrl(){
	return get_csr_bits(REG_INFO.dstopatbctrl());	//CSR8[10:8]
}

DS_clkRegs&
DS_clkRegs::setptatmixctrl(uint val){
	fill_csr_bits(val,REG_INFO.ptatmixctrl());	//CSR8[7:0]
	return *this;
}
uint
DS_clkRegs::getptatmixctrl(){
	return get_csr_bits(REG_INFO.ptatmixctrl());	//CSR8[7:0]
}

DS_clkRegs&
DS_clkRegs::setdsclkrstb(uint val){
	fill_csr_bits(val,REG_INFO.dsclkrstb());	//CSR9[15:15]
	return *this;
}
uint
DS_clkRegs::getdsclkrstb(){
	return get_csr_bits(REG_INFO.dsclkrstb());	//CSR9[15:15]
}

DS_clkRegs&
DS_clkRegs::setdsclkdigspare1(uint val){
	fill_csr_bits(val,REG_INFO.dsclkdigspare1());	//CSR9[14:14]
	return *this;
}
uint
DS_clkRegs::getdsclkdigspare1(){
	return get_csr_bits(REG_INFO.dsclkdigspare1());	//CSR9[14:14]
}

DS_clkRegs&
DS_clkRegs::setrxctle_stx_offset_mode(uint val){
	fill_csr_bits(val,REG_INFO.rxctle_stx_offset_mode());	//CSR9[13:13]
	return *this;
}
uint
DS_clkRegs::getrxctle_stx_offset_mode(){
	return get_csr_bits(REG_INFO.rxctle_stx_offset_mode());	//CSR9[13:13]
}

DS_clkRegs&
DS_clkRegs::setautotune(uint val){
	fill_csr_bits(val,REG_INFO.autotune());	//CSR9[12:10]
	return *this;
}
uint
DS_clkRegs::getautotune(){
	return get_csr_bits(REG_INFO.autotune());	//CSR9[12:10]
}

DS_clkRegs&
DS_clkRegs::setdsclkcaldone_clr(uint val){
	fill_csr_bits(val,REG_INFO.dsclkcaldone_clr());	//CSR9[8:8]
	return *this;
}
uint
DS_clkRegs::getdsclkcaldone_clr(){
	return get_csr_bits(REG_INFO.dsclkcaldone_clr());	//CSR9[8:8]
}

DS_clkRegs&
DS_clkRegs::setdsclkcompcaldir(uint val){
	fill_csr_bits(val,REG_INFO.dsclkcompcaldir());	//CSR9[7:7]
	return *this;
}
uint
DS_clkRegs::getdsclkcompcaldir(){
	return get_csr_bits(REG_INFO.dsclkcompcaldir());	//CSR9[7:7]
}

DS_clkRegs&
DS_clkRegs::setdsclkdigspare2(uint val){
	fill_csr_bits(val,REG_INFO.dsclkdigspare2());	//CSR9[6:6]
	return *this;
}
uint
DS_clkRegs::getdsclkdigspare2(){
	return get_csr_bits(REG_INFO.dsclkdigspare2());	//CSR9[6:6]
}

uint
DS_clkRegs::getdsclkcaldone(){
	return get_csr_bits(REG_INFO.dsclkcaldone());	//CSR9[5:5]
}

uint
DS_clkRegs::getdsclkcalerr(){
	return get_csr_bits(REG_INFO.dsclkcalerr());	//CSR9[4:4]
}

uint
DS_clkRegs::getautotunestatus(){
	return get_csr_bits(REG_INFO.autotunestatus());	//CSR9[3:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_fd_start(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_fd_start());	//CSR10[14:14]
	return *this;
}
uint
DS_clkRegs::getdsclk_fd_start(){
	return get_csr_bits(REG_INFO.dsclk_fd_start());	//CSR10[14:14]
}

DS_clkRegs&
DS_clkRegs::setdsclk_lld_clr(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_lld_clr());	//CSR10[13:13]
	return *this;
}
uint
DS_clkRegs::getdsclk_lld_clr(){
	return get_csr_bits(REG_INFO.dsclk_lld_clr());	//CSR10[13:13]
}

DS_clkRegs&
DS_clkRegs::setdsclk_fd_clr(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_fd_clr());	//CSR10[12:12]
	return *this;
}
uint
DS_clkRegs::getdsclk_fd_clr(){
	return get_csr_bits(REG_INFO.dsclk_fd_clr());	//CSR10[12:12]
}

DS_clkRegs&
DS_clkRegs::setdsclk_calib_clr(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_calib_clr());	//CSR10[11:11]
	return *this;
}
uint
DS_clkRegs::getdsclk_calib_clr(){
	return get_csr_bits(REG_INFO.dsclk_calib_clr());	//CSR10[11:11]
}

DS_clkRegs&
DS_clkRegs::setdsclk_lcd_start(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_lcd_start());	//CSR10[10:10]
	return *this;
}
uint
DS_clkRegs::getdsclk_lcd_start(){
	return get_csr_bits(REG_INFO.dsclk_lcd_start());	//CSR10[10:10]
}

DS_clkRegs&
DS_clkRegs::setdsclk_lld_start(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_lld_start());	//CSR10[9:9]
	return *this;
}
uint
DS_clkRegs::getdsclk_lld_start(){
	return get_csr_bits(REG_INFO.dsclk_lld_start());	//CSR10[9:9]
}

DS_clkRegs&
DS_clkRegs::setdsclk_calib_start(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_calib_start());	//CSR10[8:8]
	return *this;
}
uint
DS_clkRegs::getdsclk_calib_start(){
	return get_csr_bits(REG_INFO.dsclk_calib_start());	//CSR10[8:8]
}

DS_clkRegs&
DS_clkRegs::setdsclk_lcd_enable(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_lcd_enable());	//CSR10[7:7]
	return *this;
}
uint
DS_clkRegs::getdsclk_lcd_enable(){
	return get_csr_bits(REG_INFO.dsclk_lcd_enable());	//CSR10[7:7]
}

DS_clkRegs&
DS_clkRegs::setdsclk_lld_enable(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_lld_enable());	//CSR10[6:6]
	return *this;
}
uint
DS_clkRegs::getdsclk_lld_enable(){
	return get_csr_bits(REG_INFO.dsclk_lld_enable());	//CSR10[6:6]
}

DS_clkRegs&
DS_clkRegs::setdsclk_calib_enable(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_calib_enable());	//CSR10[5:5]
	return *this;
}
uint
DS_clkRegs::getdsclk_calib_enable(){
	return get_csr_bits(REG_INFO.dsclk_calib_enable());	//CSR10[5:5]
}

DS_clkRegs&
DS_clkRegs::setdsclk_lcd_soft_rst_n(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_lcd_soft_rst_n());	//CSR10[4:4]
	return *this;
}
uint
DS_clkRegs::getdsclk_lcd_soft_rst_n(){
	return get_csr_bits(REG_INFO.dsclk_lcd_soft_rst_n());	//CSR10[4:4]
}

DS_clkRegs&
DS_clkRegs::setdsclk_lld_soft_rst_n(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_lld_soft_rst_n());	//CSR10[3:3]
	return *this;
}
uint
DS_clkRegs::getdsclk_lld_soft_rst_n(){
	return get_csr_bits(REG_INFO.dsclk_lld_soft_rst_n());	//CSR10[3:3]
}

DS_clkRegs&
DS_clkRegs::setdsclk_calib_soft_rst_n(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_calib_soft_rst_n());	//CSR10[2:2]
	return *this;
}
uint
DS_clkRegs::getdsclk_calib_soft_rst_n(){
	return get_csr_bits(REG_INFO.dsclk_calib_soft_rst_n());	//CSR10[2:2]
}

DS_clkRegs&
DS_clkRegs::setdsclk_bus_soft_rst_n(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_bus_soft_rst_n());	//CSR10[1:1]
	return *this;
}
uint
DS_clkRegs::getdsclk_bus_soft_rst_n(){
	return get_csr_bits(REG_INFO.dsclk_bus_soft_rst_n());	//CSR10[1:1]
}

DS_clkRegs&
DS_clkRegs::setdsclk_glb_soft_rst_n(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_glb_soft_rst_n());	//CSR10[0:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_glb_soft_rst_n(){
	return get_csr_bits(REG_INFO.dsclk_glb_soft_rst_n());	//CSR10[0:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_regl_selfbleed(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_regl_selfbleed());	//CSR11[14:11]
	return *this;
}
uint
DS_clkRegs::getdsclk_regl_selfbleed(){
	return get_csr_bits(REG_INFO.dsclk_regl_selfbleed());	//CSR11[14:11]
}

DS_clkRegs&
DS_clkRegs::setdsclk_fd_threshold(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_fd_threshold());	//CSR11[10:1]
	return *this;
}
uint
DS_clkRegs::getdsclk_fd_threshold(){
	return get_csr_bits(REG_INFO.dsclk_fd_threshold());	//CSR11[10:1]
}

DS_clkRegs&
DS_clkRegs::setdsclk_meas_fd_wait(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_meas_fd_wait());	//CSR11[0:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_meas_fd_wait(){
	return get_csr_bits(REG_INFO.dsclk_meas_fd_wait());	//CSR11[0:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_fd_ref_cnt_dv(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_fd_ref_cnt_dv());	//CSR12[13:12]
	return *this;
}
uint
DS_clkRegs::getdsclk_fd_ref_cnt_dv(){
	return get_csr_bits(REG_INFO.dsclk_fd_ref_cnt_dv());	//CSR12[13:12]
}

DS_clkRegs&
DS_clkRegs::setdsclk_fd_ref_cnt_lv(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_fd_ref_cnt_lv());	//CSR12[11:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_fd_ref_cnt_lv(){
	return get_csr_bits(REG_INFO.dsclk_fd_ref_cnt_lv());	//CSR12[11:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_fd_fb_cnt_dv(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_fd_fb_cnt_dv());	//CSR13[13:12]
	return *this;
}
uint
DS_clkRegs::getdsclk_fd_fb_cnt_dv(){
	return get_csr_bits(REG_INFO.dsclk_fd_fb_cnt_dv());	//CSR13[13:12]
}

DS_clkRegs&
DS_clkRegs::setdsclk_fd_fb_cnt_lv(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_fd_fb_cnt_lv());	//CSR13[11:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_fd_fb_cnt_lv(){
	return get_csr_bits(REG_INFO.dsclk_fd_fb_cnt_lv());	//CSR13[11:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_timer_value(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_timer_value());	//CSR14[14:5]
	return *this;
}
uint
DS_clkRegs::getdsclk_timer_value(){
	return get_csr_bits(REG_INFO.dsclk_timer_value());	//CSR14[14:5]
}

DS_clkRegs&
DS_clkRegs::setdsclk_timer_div_value(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_timer_div_value());	//CSR14[4:2]
	return *this;
}
uint
DS_clkRegs::getdsclk_timer_div_value(){
	return get_csr_bits(REG_INFO.dsclk_timer_div_value());	//CSR14[4:2]
}

DS_clkRegs&
DS_clkRegs::setdsclk_timer_div_en(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_timer_div_en());	//CSR14[1:1]
	return *this;
}
uint
DS_clkRegs::getdsclk_timer_div_en(){
	return get_csr_bits(REG_INFO.dsclk_timer_div_en());	//CSR14[1:1]
}

DS_clkRegs&
DS_clkRegs::setdsclk_timer_stop(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_timer_stop());	//CSR14[0:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_timer_stop(){
	return get_csr_bits(REG_INFO.dsclk_timer_stop());	//CSR14[0:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_lld_lck_threshold(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_lld_lck_threshold());	//CSR15[13:4]
	return *this;
}
uint
DS_clkRegs::getdsclk_lld_lck_threshold(){
	return get_csr_bits(REG_INFO.dsclk_lld_lck_threshold());	//CSR15[13:4]
}

DS_clkRegs&
DS_clkRegs::setdsclk_lld_fb_div_ratio(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_lld_fb_div_ratio());	//CSR15[3:1]
	return *this;
}
uint
DS_clkRegs::getdsclk_lld_fb_div_ratio(){
	return get_csr_bits(REG_INFO.dsclk_lld_fb_div_ratio());	//CSR15[3:1]
}

DS_clkRegs&
DS_clkRegs::setdsclk_lld_once(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_lld_once());	//CSR15[0:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_lld_once(){
	return get_csr_bits(REG_INFO.dsclk_lld_once());	//CSR15[0:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_lld_ref_cnt_dv(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_lld_ref_cnt_dv());	//CSR16[14:12]
	return *this;
}
uint
DS_clkRegs::getdsclk_lld_ref_cnt_dv(){
	return get_csr_bits(REG_INFO.dsclk_lld_ref_cnt_dv());	//CSR16[14:12]
}

DS_clkRegs&
DS_clkRegs::setdsclk_lld_ref_cnt_lv(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_lld_ref_cnt_lv());	//CSR16[11:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_lld_ref_cnt_lv(){
	return get_csr_bits(REG_INFO.dsclk_lld_ref_cnt_lv());	//CSR16[11:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_lld_fb_cnt_dv(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_lld_fb_cnt_dv());	//CSR17[14:12]
	return *this;
}
uint
DS_clkRegs::getdsclk_lld_fb_cnt_dv(){
	return get_csr_bits(REG_INFO.dsclk_lld_fb_cnt_dv());	//CSR17[14:12]
}

DS_clkRegs&
DS_clkRegs::setdsclk_lld_fb_cnt_lv(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_lld_fb_cnt_lv());	//CSR17[11:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_lld_fb_cnt_lv(){
	return get_csr_bits(REG_INFO.dsclk_lld_fb_cnt_lv());	//CSR17[11:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_rep_loadctrl_mux(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_rep_loadctrl_mux());	//CSR18[12:10]
	return *this;
}
uint
DS_clkRegs::getdsclk_rep_loadctrl_mux(){
	return get_csr_bits(REG_INFO.dsclk_rep_loadctrl_mux());	//CSR18[12:10]
}

DS_clkRegs&
DS_clkRegs::setdsclk_lcd_fb_div_ratio(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_lcd_fb_div_ratio());	//CSR18[9:1]
	return *this;
}
uint
DS_clkRegs::getdsclk_lcd_fb_div_ratio(){
	return get_csr_bits(REG_INFO.dsclk_lcd_fb_div_ratio());	//CSR18[9:1]
}

DS_clkRegs&
DS_clkRegs::setdsclk_lcd_override(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_lcd_override());	//CSR18[0:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_lcd_override(){
	return get_csr_bits(REG_INFO.dsclk_lcd_override());	//CSR18[0:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_lcd_fb_cnt_lv(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_lcd_fb_cnt_lv());	//CSR19[11:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_lcd_fb_cnt_lv(){
	return get_csr_bits(REG_INFO.dsclk_lcd_fb_cnt_lv());	//CSR19[11:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_debugging_ctrl1(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_debugging_ctrl1());	//CSR20[15:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_debugging_ctrl1(){
	return get_csr_bits(REG_INFO.dsclk_debugging_ctrl1());	//CSR20[15:0]
}

uint
DS_clkRegs::getdsclk_fd_ref_freq(){
	return get_csr_bits(REG_INFO.dsclk_fd_ref_freq());	//CSR21[11:0]
}

uint
DS_clkRegs::getdsclk_fd_fb_freq(){
	return get_csr_bits(REG_INFO.dsclk_fd_fb_freq());	//CSR22[11:0]
}

uint
DS_clkRegs::getdsclk_fd_diff_freq(){
	return get_csr_bits(REG_INFO.dsclk_fd_diff_freq());	//CSR23[12:0]
}

uint
DS_clkRegs::getdsclk_lld_done(){
	return get_csr_bits(REG_INFO.dsclk_lld_done());	//CSR24[15:15]
}

uint
DS_clkRegs::getdsclk_lld_diff_freq(){
	return get_csr_bits(REG_INFO.dsclk_lld_diff_freq());	//CSR24[12:0]
}

uint
DS_clkRegs::getdsclk_lld_fb_freq(){
	return get_csr_bits(REG_INFO.dsclk_lld_fb_freq());	//CSR25[11:0]
}

uint
DS_clkRegs::getdsclk_misc_status(){
	return get_csr_bits(REG_INFO.dsclk_misc_status());	//CSR26[15:0]
}

uint
DS_clkRegs::getdsclk_calib_voscref(){
	return get_csr_bits(REG_INFO.dsclk_calib_voscref());	//CSR27[15:12]
}

uint
DS_clkRegs::getdsclk_calib_ioscdaccal(){
	return get_csr_bits(REG_INFO.dsclk_calib_ioscdaccal());	//CSR27[11:4]
}

DS_clkRegs&
DS_clkRegs::setdsclk_bypass_div_slew(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_bypass_div_slew());	//CSR28[15:13]
	return *this;
}
uint
DS_clkRegs::getdsclk_bypass_div_slew(){
	return get_csr_bits(REG_INFO.dsclk_bypass_div_slew());	//CSR28[15:13]
}

uint
DS_clkRegs::getdsclk_lld_ref_freq(){
	return get_csr_bits(REG_INFO.dsclk_lld_ref_freq());	//CSR28[11:0]
}

DS_clkRegs&
DS_clkRegs::setptatmix_vco_4(uint val){
	fill_csr_bits(val,REG_INFO.ptatmix_vco_4());	//CSR29[15:8]
	return *this;
}
uint
DS_clkRegs::getptatmix_vco_4(){
	return get_csr_bits(REG_INFO.ptatmix_vco_4());	//CSR29[15:8]
}

DS_clkRegs&
DS_clkRegs::setdsclk_pidrv_refsel(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_pidrv_refsel());	//CSR29[6:5]
	return *this;
}
uint
DS_clkRegs::getdsclk_pidrv_refsel(){
	return get_csr_bits(REG_INFO.dsclk_pidrv_refsel());	//CSR29[6:5]
}

DS_clkRegs&
DS_clkRegs::setdsclk_cml2cmos_pwrdnb(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_cml2cmos_pwrdnb());	//CSR29[4:4]
	return *this;
}
uint
DS_clkRegs::getdsclk_cml2cmos_pwrdnb(){
	return get_csr_bits(REG_INFO.dsclk_cml2cmos_pwrdnb());	//CSR29[4:4]
}

DS_clkRegs&
DS_clkRegs::setclkspine_sw_sel(uint val){
	fill_csr_bits(val,REG_INFO.clkspine_sw_sel());	//CSR29[2:2]
	return *this;
}
uint
DS_clkRegs::getclkspine_sw_sel(){
	return get_csr_bits(REG_INFO.clkspine_sw_sel());	//CSR29[2:2]
}

DS_clkRegs&
DS_clkRegs::settxclkspine_sw_sel(uint val){
	fill_csr_bits(val,REG_INFO.txclkspine_sw_sel());	//CSR29[1:1]
	return *this;
}
uint
DS_clkRegs::gettxclkspine_sw_sel(){
	return get_csr_bits(REG_INFO.txclkspine_sw_sel());	//CSR29[1:1]
}

DS_clkRegs&
DS_clkRegs::setptatmix_vco_5(uint val){
	fill_csr_bits(val,REG_INFO.ptatmix_vco_5());	//CSR30[15:8]
	return *this;
}
uint
DS_clkRegs::getptatmix_vco_5(){
	return get_csr_bits(REG_INFO.ptatmix_vco_5());	//CSR30[15:8]
}

DS_clkRegs&
DS_clkRegs::setptatmix_vco_6(uint val){
	fill_csr_bits(val,REG_INFO.ptatmix_vco_6());	//CSR30[7:0]
	return *this;
}
uint
DS_clkRegs::getptatmix_vco_6(){
	return get_csr_bits(REG_INFO.ptatmix_vco_6());	//CSR30[7:0]
}

DS_clkRegs&
DS_clkRegs::setptatmix_vco_7(uint val){
	fill_csr_bits(val,REG_INFO.ptatmix_vco_7());	//CSR31[15:8]
	return *this;
}
uint
DS_clkRegs::getptatmix_vco_7(){
	return get_csr_bits(REG_INFO.ptatmix_vco_7());	//CSR31[15:8]
}

DS_clkRegs&
DS_clkRegs::setptatmix_vco_8(uint val){
	fill_csr_bits(val,REG_INFO.ptatmix_vco_8());	//CSR31[7:0]
	return *this;
}
uint
DS_clkRegs::getptatmix_vco_8(){
	return get_csr_bits(REG_INFO.ptatmix_vco_8());	//CSR31[7:0]
}

DS_clkRegs&
DS_clkRegs::setptatmix_vco_9(uint val){
	fill_csr_bits(val,REG_INFO.ptatmix_vco_9());	//CSR32[15:8]
	return *this;
}
uint
DS_clkRegs::getptatmix_vco_9(){
	return get_csr_bits(REG_INFO.ptatmix_vco_9());	//CSR32[15:8]
}

DS_clkRegs&
DS_clkRegs::setptatmix_vco_a(uint val){
	fill_csr_bits(val,REG_INFO.ptatmix_vco_a());	//CSR32[7:0]
	return *this;
}
uint
DS_clkRegs::getptatmix_vco_a(){
	return get_csr_bits(REG_INFO.ptatmix_vco_a());	//CSR32[7:0]
}

DS_clkRegs&
DS_clkRegs::setptatmix_vco_b(uint val){
	fill_csr_bits(val,REG_INFO.ptatmix_vco_b());	//CSR33[15:8]
	return *this;
}
uint
DS_clkRegs::getptatmix_vco_b(){
	return get_csr_bits(REG_INFO.ptatmix_vco_b());	//CSR33[15:8]
}

DS_clkRegs&
DS_clkRegs::setptatmix_vco_c(uint val){
	fill_csr_bits(val,REG_INFO.ptatmix_vco_c());	//CSR33[7:0]
	return *this;
}
uint
DS_clkRegs::getptatmix_vco_c(){
	return get_csr_bits(REG_INFO.ptatmix_vco_c());	//CSR33[7:0]
}

DS_clkRegs&
DS_clkRegs::setptatmix_vco_d(uint val){
	fill_csr_bits(val,REG_INFO.ptatmix_vco_d());	//CSR34[15:8]
	return *this;
}
uint
DS_clkRegs::getptatmix_vco_d(){
	return get_csr_bits(REG_INFO.ptatmix_vco_d());	//CSR34[15:8]
}

DS_clkRegs&
DS_clkRegs::setptatmix_vco_e(uint val){
	fill_csr_bits(val,REG_INFO.ptatmix_vco_e());	//CSR34[7:0]
	return *this;
}
uint
DS_clkRegs::getptatmix_vco_e(){
	return get_csr_bits(REG_INFO.ptatmix_vco_e());	//CSR34[7:0]
}

DS_clkRegs&
DS_clkRegs::setptatmix_vco_f(uint val){
	fill_csr_bits(val,REG_INFO.ptatmix_vco_f());	//CSR35[15:8]
	return *this;
}
uint
DS_clkRegs::getptatmix_vco_f(){
	return get_csr_bits(REG_INFO.ptatmix_vco_f());	//CSR35[15:8]
}

DS_clkRegs&
DS_clkRegs::setdsclkspare(uint val){
	fill_csr_bits(val,REG_INFO.dsclkspare());	//CSR35[7:0]
	return *this;
}
uint
DS_clkRegs::getdsclkspare(){
	return get_csr_bits(REG_INFO.dsclkspare());	//CSR35[7:0]
}

DS_clkRegs&
DS_clkRegs::setidac_min(uint val){
	fill_csr_bits(val,REG_INFO.idac_min());	//CSR36[15:8]
	return *this;
}
uint
DS_clkRegs::getidac_min(){
	return get_csr_bits(REG_INFO.idac_min());	//CSR36[15:8]
}

DS_clkRegs&
DS_clkRegs::setidac_max(uint val){
	fill_csr_bits(val,REG_INFO.idac_max());	//CSR36[7:0]
	return *this;
}
uint
DS_clkRegs::getidac_max(){
	return get_csr_bits(REG_INFO.idac_max());	//CSR36[7:0]
}

DS_clkRegs&
DS_clkRegs::settrans_min(uint val){
	fill_csr_bits(val,REG_INFO.trans_min());	//CSR37[15:12]
	return *this;
}
uint
DS_clkRegs::gettrans_min(){
	return get_csr_bits(REG_INFO.trans_min());	//CSR37[15:12]
}

DS_clkRegs&
DS_clkRegs::settrans_max(uint val){
	fill_csr_bits(val,REG_INFO.trans_max());	//CSR37[11:8]
	return *this;
}
uint
DS_clkRegs::gettrans_max(){
	return get_csr_bits(REG_INFO.trans_max());	//CSR37[11:8]
}

DS_clkRegs&
DS_clkRegs::setvco_min(uint val){
	fill_csr_bits(val,REG_INFO.vco_min());	//CSR37[7:4]
	return *this;
}
uint
DS_clkRegs::getvco_min(){
	return get_csr_bits(REG_INFO.vco_min());	//CSR37[7:4]
}

DS_clkRegs&
DS_clkRegs::setvco_max(uint val){
	fill_csr_bits(val,REG_INFO.vco_max());	//CSR37[3:0]
	return *this;
}
uint
DS_clkRegs::getvco_max(){
	return get_csr_bits(REG_INFO.vco_max());	//CSR37[3:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_psel_vco_4(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_psel_vco_4());	//CSR38[15:13]
	return *this;
}
uint
DS_clkRegs::getdsclk_psel_vco_4(){
	return get_csr_bits(REG_INFO.dsclk_psel_vco_4());	//CSR38[15:13]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s1sel_vco_4(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s1sel_vco_4());	//CSR38[12:10]
	return *this;
}
uint
DS_clkRegs::getdsclk_s1sel_vco_4(){
	return get_csr_bits(REG_INFO.dsclk_s1sel_vco_4());	//CSR38[12:10]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s2sel_vco_4(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s2sel_vco_4());	//CSR38[9:8]
	return *this;
}
uint
DS_clkRegs::getdsclk_s2sel_vco_4(){
	return get_csr_bits(REG_INFO.dsclk_s2sel_vco_4());	//CSR38[9:8]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injlev_vco_4(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injlev_vco_4());	//CSR38[6:4]
	return *this;
}
uint
DS_clkRegs::getdsclk_injlev_vco_4(){
	return get_csr_bits(REG_INFO.dsclk_injlev_vco_4());	//CSR38[6:4]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injtune_vco_4(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injtune_vco_4());	//CSR38[2:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_injtune_vco_4(){
	return get_csr_bits(REG_INFO.dsclk_injtune_vco_4());	//CSR38[2:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_psel_vco_5(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_psel_vco_5());	//CSR39[15:13]
	return *this;
}
uint
DS_clkRegs::getdsclk_psel_vco_5(){
	return get_csr_bits(REG_INFO.dsclk_psel_vco_5());	//CSR39[15:13]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s1sel_vco_5(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s1sel_vco_5());	//CSR39[12:10]
	return *this;
}
uint
DS_clkRegs::getdsclk_s1sel_vco_5(){
	return get_csr_bits(REG_INFO.dsclk_s1sel_vco_5());	//CSR39[12:10]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s2sel_vco_5(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s2sel_vco_5());	//CSR39[9:8]
	return *this;
}
uint
DS_clkRegs::getdsclk_s2sel_vco_5(){
	return get_csr_bits(REG_INFO.dsclk_s2sel_vco_5());	//CSR39[9:8]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injlev_vco_5(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injlev_vco_5());	//CSR39[6:4]
	return *this;
}
uint
DS_clkRegs::getdsclk_injlev_vco_5(){
	return get_csr_bits(REG_INFO.dsclk_injlev_vco_5());	//CSR39[6:4]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injtune_vco_5(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injtune_vco_5());	//CSR39[2:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_injtune_vco_5(){
	return get_csr_bits(REG_INFO.dsclk_injtune_vco_5());	//CSR39[2:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_psel_vco_6(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_psel_vco_6());	//CSR40[15:13]
	return *this;
}
uint
DS_clkRegs::getdsclk_psel_vco_6(){
	return get_csr_bits(REG_INFO.dsclk_psel_vco_6());	//CSR40[15:13]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s1sel_vco_6(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s1sel_vco_6());	//CSR40[12:10]
	return *this;
}
uint
DS_clkRegs::getdsclk_s1sel_vco_6(){
	return get_csr_bits(REG_INFO.dsclk_s1sel_vco_6());	//CSR40[12:10]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s2sel_vco_6(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s2sel_vco_6());	//CSR40[9:8]
	return *this;
}
uint
DS_clkRegs::getdsclk_s2sel_vco_6(){
	return get_csr_bits(REG_INFO.dsclk_s2sel_vco_6());	//CSR40[9:8]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injlev_vco_6(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injlev_vco_6());	//CSR40[6:4]
	return *this;
}
uint
DS_clkRegs::getdsclk_injlev_vco_6(){
	return get_csr_bits(REG_INFO.dsclk_injlev_vco_6());	//CSR40[6:4]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injtune_vco_6(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injtune_vco_6());	//CSR40[2:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_injtune_vco_6(){
	return get_csr_bits(REG_INFO.dsclk_injtune_vco_6());	//CSR40[2:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_psel_vco_7(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_psel_vco_7());	//CSR41[15:13]
	return *this;
}
uint
DS_clkRegs::getdsclk_psel_vco_7(){
	return get_csr_bits(REG_INFO.dsclk_psel_vco_7());	//CSR41[15:13]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s1sel_vco_7(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s1sel_vco_7());	//CSR41[12:10]
	return *this;
}
uint
DS_clkRegs::getdsclk_s1sel_vco_7(){
	return get_csr_bits(REG_INFO.dsclk_s1sel_vco_7());	//CSR41[12:10]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s2sel_vco_7(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s2sel_vco_7());	//CSR41[9:8]
	return *this;
}
uint
DS_clkRegs::getdsclk_s2sel_vco_7(){
	return get_csr_bits(REG_INFO.dsclk_s2sel_vco_7());	//CSR41[9:8]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injlev_vco_7(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injlev_vco_7());	//CSR41[6:4]
	return *this;
}
uint
DS_clkRegs::getdsclk_injlev_vco_7(){
	return get_csr_bits(REG_INFO.dsclk_injlev_vco_7());	//CSR41[6:4]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injtune_vco_7(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injtune_vco_7());	//CSR41[2:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_injtune_vco_7(){
	return get_csr_bits(REG_INFO.dsclk_injtune_vco_7());	//CSR41[2:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_psel_vco_8(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_psel_vco_8());	//CSR42[15:13]
	return *this;
}
uint
DS_clkRegs::getdsclk_psel_vco_8(){
	return get_csr_bits(REG_INFO.dsclk_psel_vco_8());	//CSR42[15:13]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s1sel_vco_8(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s1sel_vco_8());	//CSR42[12:10]
	return *this;
}
uint
DS_clkRegs::getdsclk_s1sel_vco_8(){
	return get_csr_bits(REG_INFO.dsclk_s1sel_vco_8());	//CSR42[12:10]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s2sel_vco_8(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s2sel_vco_8());	//CSR42[9:8]
	return *this;
}
uint
DS_clkRegs::getdsclk_s2sel_vco_8(){
	return get_csr_bits(REG_INFO.dsclk_s2sel_vco_8());	//CSR42[9:8]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injlev_vco_8(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injlev_vco_8());	//CSR42[6:4]
	return *this;
}
uint
DS_clkRegs::getdsclk_injlev_vco_8(){
	return get_csr_bits(REG_INFO.dsclk_injlev_vco_8());	//CSR42[6:4]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injtune_vco_8(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injtune_vco_8());	//CSR42[2:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_injtune_vco_8(){
	return get_csr_bits(REG_INFO.dsclk_injtune_vco_8());	//CSR42[2:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_psel_vco_9(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_psel_vco_9());	//CSR43[15:13]
	return *this;
}
uint
DS_clkRegs::getdsclk_psel_vco_9(){
	return get_csr_bits(REG_INFO.dsclk_psel_vco_9());	//CSR43[15:13]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s1sel_vco_9(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s1sel_vco_9());	//CSR43[12:10]
	return *this;
}
uint
DS_clkRegs::getdsclk_s1sel_vco_9(){
	return get_csr_bits(REG_INFO.dsclk_s1sel_vco_9());	//CSR43[12:10]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s2sel_vco_9(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s2sel_vco_9());	//CSR43[9:8]
	return *this;
}
uint
DS_clkRegs::getdsclk_s2sel_vco_9(){
	return get_csr_bits(REG_INFO.dsclk_s2sel_vco_9());	//CSR43[9:8]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injlev_vco_9(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injlev_vco_9());	//CSR43[6:4]
	return *this;
}
uint
DS_clkRegs::getdsclk_injlev_vco_9(){
	return get_csr_bits(REG_INFO.dsclk_injlev_vco_9());	//CSR43[6:4]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injtune_vco_9(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injtune_vco_9());	//CSR43[2:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_injtune_vco_9(){
	return get_csr_bits(REG_INFO.dsclk_injtune_vco_9());	//CSR43[2:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_psel_vco_a(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_psel_vco_a());	//CSR44[15:13]
	return *this;
}
uint
DS_clkRegs::getdsclk_psel_vco_a(){
	return get_csr_bits(REG_INFO.dsclk_psel_vco_a());	//CSR44[15:13]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s1sel_vco_a(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s1sel_vco_a());	//CSR44[12:10]
	return *this;
}
uint
DS_clkRegs::getdsclk_s1sel_vco_a(){
	return get_csr_bits(REG_INFO.dsclk_s1sel_vco_a());	//CSR44[12:10]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s2sel_vco_a(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s2sel_vco_a());	//CSR44[9:8]
	return *this;
}
uint
DS_clkRegs::getdsclk_s2sel_vco_a(){
	return get_csr_bits(REG_INFO.dsclk_s2sel_vco_a());	//CSR44[9:8]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injlev_vco_a(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injlev_vco_a());	//CSR44[6:4]
	return *this;
}
uint
DS_clkRegs::getdsclk_injlev_vco_a(){
	return get_csr_bits(REG_INFO.dsclk_injlev_vco_a());	//CSR44[6:4]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injtune_vco_a(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injtune_vco_a());	//CSR44[2:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_injtune_vco_a(){
	return get_csr_bits(REG_INFO.dsclk_injtune_vco_a());	//CSR44[2:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_psel_vco_b(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_psel_vco_b());	//CSR45[15:13]
	return *this;
}
uint
DS_clkRegs::getdsclk_psel_vco_b(){
	return get_csr_bits(REG_INFO.dsclk_psel_vco_b());	//CSR45[15:13]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s1sel_vco_b(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s1sel_vco_b());	//CSR45[12:10]
	return *this;
}
uint
DS_clkRegs::getdsclk_s1sel_vco_b(){
	return get_csr_bits(REG_INFO.dsclk_s1sel_vco_b());	//CSR45[12:10]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s2sel_vco_b(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s2sel_vco_b());	//CSR45[9:8]
	return *this;
}
uint
DS_clkRegs::getdsclk_s2sel_vco_b(){
	return get_csr_bits(REG_INFO.dsclk_s2sel_vco_b());	//CSR45[9:8]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injlev_vco_b(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injlev_vco_b());	//CSR45[6:4]
	return *this;
}
uint
DS_clkRegs::getdsclk_injlev_vco_b(){
	return get_csr_bits(REG_INFO.dsclk_injlev_vco_b());	//CSR45[6:4]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injtune_vco_b(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injtune_vco_b());	//CSR45[2:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_injtune_vco_b(){
	return get_csr_bits(REG_INFO.dsclk_injtune_vco_b());	//CSR45[2:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_psel_vco_c(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_psel_vco_c());	//CSR46[15:13]
	return *this;
}
uint
DS_clkRegs::getdsclk_psel_vco_c(){
	return get_csr_bits(REG_INFO.dsclk_psel_vco_c());	//CSR46[15:13]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s1sel_vco_c(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s1sel_vco_c());	//CSR46[12:10]
	return *this;
}
uint
DS_clkRegs::getdsclk_s1sel_vco_c(){
	return get_csr_bits(REG_INFO.dsclk_s1sel_vco_c());	//CSR46[12:10]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s2sel_vco_c(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s2sel_vco_c());	//CSR46[9:8]
	return *this;
}
uint
DS_clkRegs::getdsclk_s2sel_vco_c(){
	return get_csr_bits(REG_INFO.dsclk_s2sel_vco_c());	//CSR46[9:8]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injlev_vco_c(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injlev_vco_c());	//CSR46[6:4]
	return *this;
}
uint
DS_clkRegs::getdsclk_injlev_vco_c(){
	return get_csr_bits(REG_INFO.dsclk_injlev_vco_c());	//CSR46[6:4]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injtune_vco_c(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injtune_vco_c());	//CSR46[2:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_injtune_vco_c(){
	return get_csr_bits(REG_INFO.dsclk_injtune_vco_c());	//CSR46[2:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_psel_vco_d(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_psel_vco_d());	//CSR47[15:13]
	return *this;
}
uint
DS_clkRegs::getdsclk_psel_vco_d(){
	return get_csr_bits(REG_INFO.dsclk_psel_vco_d());	//CSR47[15:13]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s1sel_vco_d(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s1sel_vco_d());	//CSR47[12:10]
	return *this;
}
uint
DS_clkRegs::getdsclk_s1sel_vco_d(){
	return get_csr_bits(REG_INFO.dsclk_s1sel_vco_d());	//CSR47[12:10]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s2sel_vco_d(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s2sel_vco_d());	//CSR47[9:8]
	return *this;
}
uint
DS_clkRegs::getdsclk_s2sel_vco_d(){
	return get_csr_bits(REG_INFO.dsclk_s2sel_vco_d());	//CSR47[9:8]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injlev_vco_d(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injlev_vco_d());	//CSR47[6:4]
	return *this;
}
uint
DS_clkRegs::getdsclk_injlev_vco_d(){
	return get_csr_bits(REG_INFO.dsclk_injlev_vco_d());	//CSR47[6:4]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injtune_vco_d(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injtune_vco_d());	//CSR47[2:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_injtune_vco_d(){
	return get_csr_bits(REG_INFO.dsclk_injtune_vco_d());	//CSR47[2:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_psel_vco_e(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_psel_vco_e());	//CSR48[15:13]
	return *this;
}
uint
DS_clkRegs::getdsclk_psel_vco_e(){
	return get_csr_bits(REG_INFO.dsclk_psel_vco_e());	//CSR48[15:13]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s1sel_vco_e(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s1sel_vco_e());	//CSR48[12:10]
	return *this;
}
uint
DS_clkRegs::getdsclk_s1sel_vco_e(){
	return get_csr_bits(REG_INFO.dsclk_s1sel_vco_e());	//CSR48[12:10]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s2sel_vco_e(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s2sel_vco_e());	//CSR48[9:8]
	return *this;
}
uint
DS_clkRegs::getdsclk_s2sel_vco_e(){
	return get_csr_bits(REG_INFO.dsclk_s2sel_vco_e());	//CSR48[9:8]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injlev_vco_e(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injlev_vco_e());	//CSR48[6:4]
	return *this;
}
uint
DS_clkRegs::getdsclk_injlev_vco_e(){
	return get_csr_bits(REG_INFO.dsclk_injlev_vco_e());	//CSR48[6:4]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injtune_vco_e(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injtune_vco_e());	//CSR48[2:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_injtune_vco_e(){
	return get_csr_bits(REG_INFO.dsclk_injtune_vco_e());	//CSR48[2:0]
}

DS_clkRegs&
DS_clkRegs::setdsclk_psel_vco_f(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_psel_vco_f());	//CSR49[15:13]
	return *this;
}
uint
DS_clkRegs::getdsclk_psel_vco_f(){
	return get_csr_bits(REG_INFO.dsclk_psel_vco_f());	//CSR49[15:13]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s1sel_vco_f(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s1sel_vco_f());	//CSR49[12:10]
	return *this;
}
uint
DS_clkRegs::getdsclk_s1sel_vco_f(){
	return get_csr_bits(REG_INFO.dsclk_s1sel_vco_f());	//CSR49[12:10]
}

DS_clkRegs&
DS_clkRegs::setdsclk_s2sel_vco_f(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_s2sel_vco_f());	//CSR49[9:8]
	return *this;
}
uint
DS_clkRegs::getdsclk_s2sel_vco_f(){
	return get_csr_bits(REG_INFO.dsclk_s2sel_vco_f());	//CSR49[9:8]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injlev_vco_f(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injlev_vco_f());	//CSR49[6:4]
	return *this;
}
uint
DS_clkRegs::getdsclk_injlev_vco_f(){
	return get_csr_bits(REG_INFO.dsclk_injlev_vco_f());	//CSR49[6:4]
}

DS_clkRegs&
DS_clkRegs::setdsclk_injtune_vco_f(uint val){
	fill_csr_bits(val,REG_INFO.dsclk_injtune_vco_f());	//CSR49[2:0]
	return *this;
}
uint
DS_clkRegs::getdsclk_injtune_vco_f(){
	return get_csr_bits(REG_INFO.dsclk_injtune_vco_f());	//CSR49[2:0]
}

