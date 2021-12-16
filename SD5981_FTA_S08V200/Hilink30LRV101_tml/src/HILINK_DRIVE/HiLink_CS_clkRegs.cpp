#include <HILINK_DRIVE/HiLink_CS_clkRegs.h>

#include <iostream>
using namespace std;
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
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
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
	//TODO: add your code for CSR Address mapping
	return 1;
}

uint
CS_clkRegs::getAddressMapToHiLink(int csrIndex){
	if(csrIndex>=CS_CLK_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	//TODO: add your code for CSR Address mapping
	return (int)(0x0000 | (broadcast << 13) | (sliceID << 9)|((uint)0x0 << 7) | csrIndex << 1);
}


uint&
CS_clkRegs::get_csr(uint csrIndex){
	if(csrIndex>=CS_CLK_CSR_NUM){
//		cerr<<"Error: CSRIndex should not be larger than "<<dec<<getCSRCount()<<endl;
		//    ERROR_EXIT(TM::ABORT_FLOW);
	}
	return csr[csrIndex];
}

void
CS_clkRegs::get_default_MacroLaneID(T_MacroLaneID& id){
	//TODO: add your code for CSR Address mapping
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

	/// Select the source of PLL0's reference clock. (Refer to fig.5 in  HiLink30_datasheet)
	/// 0 = Select the reference clock from REFCLKBUS0 as PLL0's reference clock.
	/// 1 = Select the reference clock from REFCLKBUS1 as PLL0's reference clock.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0refclksel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{0,"pll0refclksel",14,14}
	};
	return reg;
}

	/// Set the vco 'Na' divider value  for PLL0  (Refer to fig.7 in  HiLink30_datasheet). 
	/// 00 =  1                
	/// 01 =  2                
	/// 10 =  3              
	/// 11 =  2
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vcodivna(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{0,"pll0vcodivna",12,11}
	};
	return reg;
}

	/// Set the vco 'Ka'   divider value  for PLL0   (Refer to fig.7 in  HiLink30_datasheet).     
	/// 00 =  1                
	/// 01 =  1.5                
	/// 10 =  2              
	/// 11 =   2
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vcodivka(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{0,"pll0vcodivka",10,9}
	};
	return reg;
}

	/// Sets the P-counter value of the feedback divider ratio (Nb) for PLL0 (Refer to fig.7 in  HiLink30_datasheet).   The feedback divider ratio is calculated as follows:
	///          Nb=4*(P+1)+S+2      
	/// where  P is greater than or equal to 1;   S is greater than or equal to 0;   and S is the maximum possible value where P is greater than or equal to S;   Nb,P,S are all integer values
	/// (Refer to  PLL0FBDIVS for definition of  S value)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0fbdivp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{0,"pll0fbdivp",8,4}
	};
	return reg;
}

	/// Sets the S-counter value of the feedback divider ratio (Nb) for PLL0 (Refer to fig.7 in  HiLink30_datasheet).   The feedback divider ratio is calculated as follows:
	///          Nb=4*(P+1)+S+2   
	/// where  P is greater than or equal to 1;   S  is greater than or equal to 0;   and S is the maximum possible value P is greater than or equal to S;  Nb,P,S are all integer values
	/// (Refer to PLL0FBDIVP for definition of  P value)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0fbdivs(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{0,"pll0fbdivs",3,0}
	};
	return reg;
}

	/// (Changed function in V101)
	/// CS refclk monitor powerdown
	/// 0 = Power down
	/// 1= Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0hsclkdistpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{1,"pll0hsclkdistpwrdb",15,15}
	};
	return reg;
}

	/// spare signal in H30 CS
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0hsclkdivpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{1,"pll0hsclkdivpwrdb",14,14}
	};
	return reg;
}

	/// Sets the High-speed clock spine divider 'Kb' for PLL0  (Refer to fig.7 in  HiLink30_datasheet) :
	///                   Kb
	/// xx00:            1
	/// xx01:            2
	/// xx10:            3
	/// xx11:          power down Kb divider
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0hsclkdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{1,"pll0hsclkdiv",13,10}
	};
	return reg;
}

	/// bit[1:0] spare signal in H30 CS
	/// bit[2]  The M-divider in the pll0 hsclk has a div-by-2 at its input.  This control will bypass it:
	/// 0 = div-by-2 not bypassed
	/// 1 = div-by-2 is bypassed
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0hsclkdistspare(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{1,"pll0hsclkdistspare",9,7}
	};
	return reg;
}

	/// Sets the Reference clock divider 'M' for PLL0  (Refer to fig.7 in  HiLink30_datasheet)
	/// 00 = 1 
	/// 01 = 1 
	/// 10 = 2 
	/// 11 = 3
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0refclkdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{1,"pll0refclkdiv",6,5}
	};
	return reg;
}

	/// PLL0 south facing hsclk distribution power down 
	/// 0 = powered down
	/// 1= powered up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0hsclkdivsouthpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{1,"pll0hsclkdivsouthpwrdb",4,4}
	};
	return reg;
}

	/// Sets the Word clock divider 'J_40b' for PLL0 (Refer to fig.7 in  HiLink30_datasheet)
	/// 00 = divided by 10  (ie, spine clock div-by-20)
	/// 01 = divided by 20 (ie, spine clock div-by-40)
	/// 10 = divided by 8  (ie, spine clock div-by-16)
	/// 11 = divided by 16  (ie, spine clock div-by-32)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0mclkdiv40b(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{1,"pll0mclkdiv40b",3,2}
	};
	return reg;
}

	/// Sets the Word clock divider 'J_32b'  (for 32-bit application) for PLL0  (Refer to fig.7 in  HiLink30_datasheet)
	/// 00 = divided by 8  (ie, spine clock div-by-16)
	/// 01 = divided by 16  (ie, spine clock div-by-32)
	/// 10 = divided by 10  (ie, spine clock div-by-20)
	/// 11 = divided by 20  (ie, spine clock div-by-40)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0mclkdiv32b(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{1,"pll0mclkdiv32b",1,0}
	};
	return reg;
}

	/// Sets  LCVCO out-of-lock threshold for PLL0.   A value between 1 and 31 can be set.  
	/// Note: For LCVCO to lock, this field should not be programmed to 0.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0lolthr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{2,"pll0lolthr",10,6}
	};
	return reg;
}

	/// Sets LCVCO loss-of-clock threshold for PLL0.
	/// 000 = 128
	/// 001 = 256
	/// 010 = 512
	/// 011 = 1024
	/// 100 = 2048
	/// 101 = 4096
	/// 11x = 4096
	/// (Note: A value less the 0x5 will cause False alarm )
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0locthr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{2,"pll0locthr",5,3}
	};
	return reg;
}

	/// LCVCO loss-of-lock mode for PLL0. Choose how loss-of-lock detection will start after LCVCO calibration is done (coarse tune).
	/// 0 = automatically start.
	/// 1 = manually start.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0lolmode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{2,"pll0lolmode",2,2}
	};
	return reg;
}

	/// LCVCO out-of-lock status for PLL0. Out-of-lock status is latched until being read.
	/// 0 = LCVCO locked
	/// 1 = LCVCO out of lock
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0outoflock(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{2,"pll0outoflock",1,1}
	};
	return reg;
}

	/// Loss of LCVCO clock indicator for PLL0. Status is latched until being read 
	/// 0 = LCVCO clock is active
	/// 1 = LCVCO clock is not active
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0lossoflcvcoclk(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{2,"pll0lossoflcvcoclk",0,0}
	};
	return reg;
}

	/// Select the source of PLL1's reference clock. (Refer to fig.5 in  HiLink30_datasheet)
	/// 0 = Select the reference clock from REFCLKBUS0 as PLL1's reference clock.
	/// 1 = Select the reference clock from REFCLKBUS1 as PLL1's reference clock.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1refclksel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{3,"pll1refclksel",15,15}
	};
	return reg;
}

	/// Sets the Reference clock divider 'M' for PLL1  (Refer to fig.7 in  HiLink30_datasheet)
	/// 00 = 1 
	/// 01 = 1 
	/// 10 = 2 
	/// 11 = 3
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1refclkdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{3,"pll1refclkdiv",14,13}
	};
	return reg;
}

	/// Set the vco  'Na'  divider value  for PLL1  (Refer to fig.7 in  HiLink30_datasheet). 
	/// 00 =  1                
	/// 01 =  2                
	/// 10 =  3              
	/// 11 =  2
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vcodivna(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{3,"pll1vcodivna",12,11}
	};
	return reg;
}

	/// Set the vco 'Ka' divider value for PLL1  (Refer to fig.7 in  HiLink30_datasheet). 
	/// 00 =  1                
	/// 01 =  1.5                
	/// 10 =  2              
	/// 11 =   2
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vcodivka(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{3,"pll1vcodivka",10,9}
	};
	return reg;
}

	/// Sets the P-counter value of the feedback divider ratio (Nb) for PLL0 (Refer to fig.7 in  HiLink30_datasheet).   The feedback divider ratio is calculated as follows:
	///          Nb=4*(P+1)+S+2   
	/// where  P greater than or equal to 1;   S  greater than or equal to 0;   and S is the maximum possible value where P greater than or equal to S;   Nb,P,S are all integer values
	/// (Refer to CSR3 register field PLL1FBDIVS for definition of  S value)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1fbdivp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{3,"pll1fbdivp",8,4}
	};
	return reg;
}

	/// Sets the S-counter value of the feedback divider ratio (Nb) for PLL0 (Refer to fig.7 in  HiLink30_datasheet).   The feedback divider ratio is calculated as follows:
	///          Nb=4*(P+1)+S+2   
	/// where  P greater than or equal to 1;   S  greater than or equal to 0;   and S is the maximum possible value where P greater than or equal to S;  Nb,P,S are all integer values
	/// (Refer to CSR3 register field PLL1FBDIVP for definition of  P value)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1fbdivs(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{3,"pll1fbdivs",3,0}
	};
	return reg;
}

	/// spare signal, not  used in  hsclkdist block
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1hsclkdistpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{4,"pll1hsclkdistpwrdb",15,15}
	};
	return reg;
}

	/// spare signal in H30 CS
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1hsclkdivpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{4,"pll1hsclkdivpwrdb",14,14}
	};
	return reg;
}

	/// Sets the High-speed clock spine divider 'Kb' for PLL1  (Refer to fig.7 in  HiLink30_datasheet) :
	///                   Kb
	/// xx00:            1
	/// xx01:            2
	/// xx10:            3
	/// xx11:           power down Kb divider
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1hsclkdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{4,"pll1hsclkdiv",13,10}
	};
	return reg;
}

	/// bit[1:0]: spare signal in H30 CS
	/// bit[2] :  The M-divider in the pll1 hsclk has a div-by-2 at its input.  This control will bypass it:
	/// 0 = div-by-2 not bypassed
	/// 1 = div-by-2 is bypassed
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1hsclkdistspare(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{4,"pll1hsclkdistspare",9,7}
	};
	return reg;
}

	/// PLL1 south facing hsclk distribution power down 
	/// 0 = powered down
	/// 1= powered up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1hsclkdivsouthpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{4,"pll1hsclkdivsouthpwrdb",4,4}
	};
	return reg;
}

	/// Sets the Word clock divider 'J_40b' for PLL1 (Refer to fig.7 in  HiLink30_datasheet)
	/// 00 = divided by 10 (ie., spine clock divided by 20)
	/// 01 = divided by 20 (ie., spine clock divided by 40)
	/// 10 = divided by 8  (ie., spine clock divided by 16)
	/// 11 = divided by 16 (ie., spine clock divided by 32)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1mclkdiv40b(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{4,"pll1mclkdiv40b",3,2}
	};
	return reg;
}

	/// Sets the Word clock divider 'J_32b'  (for 32-bit application) for PLL1  (Refer to fig.7 in  HiLink30_datasheet)
	/// 00 = divided by 8  (ie., spine clock divided by 16)
	/// 01 = divided by 16 (ie., spine clock divided by 32)
	/// 10 = divided by 10 (ie., spine clock divided by 20)
	/// 11 = divided by 20 (ie., spine clock divided by 40)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1mclkdiv32b(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{4,"pll1mclkdiv32b",1,0}
	};
	return reg;
}

	/// Sets  LCVCO out-of-lock threshold for PLL1.   A value between 1 and 31 can be set.  
	/// Note: For LCVCO to lock, this field should not be programmed to 0.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1lolthr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{5,"pll1lolthr",10,6}
	};
	return reg;
}

	/// LCVCO loss-of-clock threshold for PLL1.
	/// 000 = 128
	/// 001 = 256
	/// 010 = 512
	/// 011 = 1024
	/// 100 = 2048
	/// 101 = 4096
	/// 11x = 4096
	/// (Note: A value less the 0x5 will cause False alarm )
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1locthr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{5,"pll1locthr",5,3}
	};
	return reg;
}

	/// Select LCVCO loss-of-lock detection mode for PLL1. It determines how the loss-of-lock detection will start after LCVCO calibration is done (coarse tune).
	/// 0 = automatic
	/// 1 = manual
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1lolmode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{5,"pll1lolmode",2,2}
	};
	return reg;
}

	/// LCVCO out-of-lock status for PLL1. Out-of-lock status is latched until being read 
	/// 0 = LCVCO locked
	/// 1 = LCVCO out of lock
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1outoflock(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{5,"pll1outoflock",1,1}
	};
	return reg;
}

	/// Loss of LCVCO clock indicator for PLL1. Status is latched until being read 
	/// 0 = LCVCO clock is active
	/// 1 = LCVCO clock is not active
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1lossoflcvcoclk(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{5,"pll1lossoflcvcoclk",0,0}
	};
	return reg;
}

	/// Div-40 word clk select. (Refer to fig.6 in  HiLink30_datasheet)
	/// 0 = Choose the div-40 clock from PLL0.
	/// 1 = Choose the div-40 clock from PLL1.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::wordclk40bsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{6,"wordclk40bsel",15,15}
	};
	return reg;
}

	/// Div-32 word clk select. (Refer to fig.6  in  HiLink30_datasheet)
	/// 0 = Choose the div-32 clock from PLL0.
	/// 1 = Choose the div-32 clock from PLL1.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::wordclk32bsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{6,"wordclk32bsel",14,14}
	};
	return reg;
}

	/// Word clock select. (Refer to fig.6  in HiLink30_datasheet)
	/// 0 = Choose the 40B word clock.
	/// 1 = Choose the 32B word clock.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::wordclksel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{6,"wordclksel",13,13}
	};
	return reg;
}

	/// Core clock select. (Refer to fig.6  in  HiLink30_datasheet)
	/// 0 = Choose lifeclk2dig clock as the source of core clock.
	/// 1 = Choose mclk_40bit/mclk_32bit clock as the core clock
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::coreclksel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{6,"coreclksel",12,12}
	};
	return reg;
}

	/// enable the clock for the new LCVCO regulator in the slave PLL
	/// 0 = disable   
	/// 1= enable the clock from master hsclkdist to be clocking the  slave LCVCO new regulator
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0hsclk2vcovregen(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{6,"pll0hsclk2vcovregen",4,4}
	};
	return reg;
}

	/// Divider ratio for lifeclk2dig  (Refer to fig.6  in HiLink30_datasheet) . Used for life clock generation.
	/// 00 = divided by 1
	/// 01 = divided by 2
	/// 10 = divided by 3
	/// 11 = divided by 4
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lifeclk2digdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{6,"lifeclk2digdiv",3,2}
	};
	return reg;
}

	/// Divider ratio for wordclk2dig  (Refer to fig.6  in HiLink30_datasheet) . Used for life clock generation.
	/// 00 = divided by 1
	/// 01 = divided by 2
	/// 10 = divided by 3
	/// 11 = divided by 4
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::wordclk2digdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{6,"wordclk2digdiv",1,0}
	};
	return reg;
}

	/// CMU (Clock Multiplier Unit) bias distribution power down, active low
	/// 0 = power down
	/// 1= power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::biascmupwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{7,"biascmupwrdb",15,15}
	};
	return reg;
}

	/// refclk cml2cmos buffer power down, active low. When activated, lifeclk2dig disable
	/// 0= power down
	/// 1= power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::refclkdistpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{7,"refclkdistpwrdb",14,14}
	};
	return reg;
}

	/// CMU (Clock Multiplier Unit) bias distribution test mode enable , active high
	/// 0 = mission mode
	/// 1 = test mode enabled
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::biascmutestmode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{7,"biascmutestmode",13,13}
	};
	return reg;
}

	/// ADC (in ClockSlice)  power down, active low
	/// 0 = Power down 
	/// 1 = Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::adcpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{7,"adcpwrdb",12,12}
	};
	return reg;
}

	/// Comparator (in ClockSlice)  power down, active low.
	/// 0 = Power down 
	/// 1 = Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::comppwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{7,"comppwrdb",11,11}
	};
	return reg;
}

	/// refclk0 distribution buffer bias control
	/// 00 = xx uA
	/// 01 = 
	/// 10 =
	/// 11 = yy uA
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::refclk0biasctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{7,"refclk0biasctrl",3,2}
	};
	return reg;
}

	/// refclk1 distribution buffer bias control
	/// 00 = xx uA
	/// 01 = 
	/// 10 =
	/// 11 = yy uA
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::refclk1biasctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{7,"refclk1biasctrl",1,0}
	};
	return reg;
}

	/// PLL0 power down, active low
	/// 0 = Power down 
	/// 1 = Power up
	/// New in v101: Used as a trigger to power up/down PLL0 sequentially with default settings.   (PLL1 if ON will also sequentially power down before PLL0)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0pwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{8,"pll0pwrdb",15,15}
	};
	return reg;
}

	/// provide a 200k feedback resistor shunt across the DLF (Digital Loop Filter) integrator capacitor in PLL0, active low. 
	/// 0 = no resistor in shunt
	/// 1 = 200K resistor shunt across DLF integ cap applied
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0dlfresfbpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{8,"pll0dlfresfbpwrdb",9,9}
	};
	return reg;
}

	/// DLF (Digital Loop Filter) circuitry power down for PLL0, active low
	/// 0 = Power down 
	/// 1 = Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0dlfpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{8,"pll0dlfpwrdb",8,8}
	};
	return reg;
}

	/// Sample and Hold circuitry power down in PLL0, active low
	/// 0 = Power down 
	/// 1 = Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0dlfshpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{8,"pll0dlfshpwrdb",7,7}
	};
	return reg;
}

	/// DLF test mode power down in PLL0. It also disconnects DTB and ATB DLF muxes,  active  low.
	/// 0 = Power down 
	/// 1 = Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0dlftstpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{8,"pll0dlftstpwrdb",6,6}
	};
	return reg;
}

	/// DLF active common mode circuitry power down for PLL0.  A 100k feedback resistor shunts the DLF integrator capacitor instead. Active Low
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0dlfcmfbpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{8,"pll0dlfcmfbpwrdb",5,5}
	};
	return reg;
}

	/// Enable chopping function
	/// 0: chopping is disabled on the DLF
	/// 1: chopping is enabled on the DLF
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0dlfchoppwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{8,"pll0dlfchoppwrdb",4,4}
	};
	return reg;
}

	/// PLL0 pll regulator power down, active low
	/// 0 = Power down 
	/// 1 = Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vregpllpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{8,"pll0vregpllpwrdb",3,3}
	};
	return reg;
}

	/// PLL0  dlf regulator power down, active low
	/// 0 = Power down 
	/// 1 = Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vregdlfpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{8,"pll0vregdlfpwrdb",2,2}
	};
	return reg;
}

	/// PLL0 vcodivider regulator power down, active low
	/// 0 = Power down 
	/// 1 = Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vregvcodivpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{8,"pll0vregvcodivpwrdb",0,0}
	};
	return reg;
}

	/// Swap PFD (Phase Frequency Detector) UP and DOWN signal for PLL0, Active high
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0pfdupdnswap(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{9,"pll0pfdupdnswap",14,14}
	};
	return reg;
}

	/// Force the PFD output to be UP for PLL0.
	/// 0 = Let the PFD detect frequency and phase difference.
	/// 1 = Force the PFD output to be UP.
	/// Note: setting both PFDFORCEUP and PFDFORCEDN to 1 is not allowed.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0pfdforceup(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{9,"pll0pfdforceup",13,13}
	};
	return reg;
}

	/// Force the PFD output to be DOWN for PLL0.
	/// 0 = Let the PFD detect frequency and phase difference.
	/// 1 = Force the PFD output to be DOWN.
	/// Note: setting both PFDFORCEUP and PFDFORCEDN to 1 is not allowed.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0pfdforcedn(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{9,"pll0pfdforcedn",12,12}
	};
	return reg;
}

	/// Select the pulse width of the PFD outputs (both UP/DOWN) to adjust the bandwidth of the PLL0.
	/// 00 = 65ps
	/// 01 = 84ps
	/// 10 = 104ps
	/// 11 = 135ps
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0pfdpulsewidth(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{9,"pll0pfdpulsewidth",11,10}
	};
	return reg;
}

	/// VCO calibration enable signal for PLL0, active low.
	/// 0 = Open Loop PLL
	/// 1 = Closed loop PLL
	/// 
	/// Note: In VCO auto calib. mode, when the calib. FSM starts, it loads the register value on the signal which drives the analog. When the calib. FSM finishes, it sets 1 on the same signal.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0cpcalrstb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{9,"pll0cpcalrstb",7,7}
	};
	return reg;
}

	/// PLL0 vtune differential voltage control when VCO is being calibrated: (The asserted levels have changed in v101)
	/// 000 =  -400mV
	/// 001 =  -300mV
	/// 010 =  -200mV
	/// 011 =  -100mV
	/// 100  =  0V (default)
	/// 101 =  100mV
	/// 110 =  200mV
	/// 111 =  300mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0cpcalrstlvl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{9,"pll0cpcalrstlvl",6,4}
	};
	return reg;
}

	/// Selects Charge pump reference voltage level for PLL0. 
	/// 000 =  463mV
	/// 001 =  470mV
	/// 010 =  480mV 
	/// 011 =  493mV
	/// 100 =  502mV (default)
	/// 101 =  517mV
	/// 110 =  527mV
	/// 111 =  536mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0cpvreflvl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{9,"pll0cpvreflvl",2,0}
	};
	return reg;
}

	/// Programs PLL0 integral charge pump current 
	/// 00 = 10 uA
	/// 01 = 20 uA
	/// 10 = 40 uA
	/// 11 = 60 uA
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0cpintcrntsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{10,"pll0cpintcrntsel",12,11}
	};
	return reg;
}

	/// Programs PLL0 proportional charge pump current  
	/// 000 = 1000 uA
	/// 001 = 1200 uA
	/// 010 = 1400 uA
	/// 011 = 1600 uA
	/// 100 = 1800 uA
	/// 101 = 2000 uA
	/// 110 = 2200 uA
	/// 111 = 2400 uA
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0cppropcrntsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{10,"pll0cppropcrntsel",6,4}
	};
	return reg;
}

	/// Programs the PLL0 DLF (Digital Loop Filter) integrator capacitor (Cint) unit count from 6 to 14. Each Cint unit is 545fF. Select the DLF integrator capacitor (Cint) and proportional capacitor (Cprop). dlf_cint_sel_i[2] is spare bit.
	/// [1:0]=00, Cint=2.4pF,  Cprop=2.18pF
	/// [1:0]=01, integral C=4.8pF,  Cprop=2.18pF
	/// Default  [1:0]=10, Cint=7.2pF,  Cprop=4.36pF
	/// [1:0]=11, Cint=9.6pF,  Cprop=4.36pF
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0dlfcintsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{11,"pll0dlfcintsel",15,13}
	};
	return reg;
}

	/// Sets PLL0 Sample and Hold clock sample width
	/// 0 = 1 ps
	/// 1 = 2 ps
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0dlfshdelsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{11,"pll0dlfshdelsel",7,7}
	};
	return reg;
}

	/// Diagnostic test mode for PLL0 DLF to sample internal digital signals of the DLF.
	/// (Not for Customer use)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0dlfseldtb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{11,"pll0dlfseldtb",6,2}
	};
	return reg;
}

	/// Switches in PLL0 Sample and Hold capacitors
	/// 00 =  no caps connected
	/// 01 =  1.6pF
	/// 10 =  1.6pF
	/// 11 =  3.2pF
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0dlfshcapsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{11,"pll0dlfshcapsel",1,0}
	};
	return reg;
}

	/// VCO band select control bits for PLL0:
	/// 000 =  band0
	/// 001 =  band1
	/// 010 =  band2
	/// 011 =  band3
	/// Others = Not valid
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vcobandsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{12,"pll0vcobandsel",14,12}
	};
	return reg;
}

	/// PLL0 Regulator RC filter short out control pin:
	/// 0 =  RC Filter is in use
	/// 1 =  RC Filter is shorted
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vcoregfilshorten(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{12,"pll0vcoregfilshorten",11,11}
	};
	return reg;
}

	/// This control bit is for test only. If PLL0 VCO can not start oscillating, setting this control bit  HIGH  (or 1) connects lvcc_vcocore directly to hvcc.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vcoswthhien(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{12,"pll0vcoswthhien",10,10}
	};
	return reg;
}

	/// DESCRIPTION CHANGED IN V101 .... 
	/// PLL0 VCO frequency calibration control bits:
	/// Bit[4:1] 
	/// 0000= all caps turned off(highest osc freq for the band)
	/// 0001=1 cap turned on
	/// 0010= 2 caps turned on
	/// ...........
	/// 1111= 15 caps turned on 
	/// 
	/// Bit[0]  selects turn on of Half caps for increased freq granularity
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vcofreqcal(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{12,"pll0vcofreqcal",9,5}
	};
	return reg;
}

	/// regulator output voltage control bits used to trim internal  supply voltage of  PLL0 VCO
	/// 00000 = minimum Voltage 
	/// ..
	/// 11111 =  maximum Voltage
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vcoitank(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{12,"pll0vcoitank",4,0}
	};
	return reg;
}

	/// reference select for PLL0 VCO second regulator
	/// Reference voltage control signal for new regulator =  
	/// (Binary code)
	/// 0000 =  445mV
	/// 0001 =  455mV
	/// 0010 =  465mV
	/// 0011 =  475mV
	/// 0100 =  485mV
	/// 0101 =  495mV
	/// 0110 =  505mV
	/// 0111 =  515mV 
	/// 1000 =  525mV
	/// 1001 =  535mV
	/// 1010 =  545mV
	/// 1011 =  555mV
	/// 1100 to 1111 =  not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vcovref(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{13,"pll0vcovref",15,12}
	};
	return reg;
}

	/// bit[1] used to control 1/4 LSB freqcal on PLL0 VCO tuning
	/// 0 = 1/4 LSB freqcal is not active
	/// 1 = 1/4 LSB freqcal is active
	/// 
	/// bit[0] spare bit
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vcodivspare(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{13,"pll0vcodivspare",11,10}
	};
	return reg;
}

	/// select second regulator for PLL0 VCO 
	/// 0 = old regulator
	/// 1 = new regulator
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vcovregsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{13,"pll0vcovregsel",9,9}
	};
	return reg;
}

	/// control code for divide-by-1.5 for PLL0
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vcodiv1p5ctrlcode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{13,"pll0vcodiv1p5ctrlcode",8,4}
	};
	return reg;
}

	/// select the clock input for the second regulator for PLL0 VCO
	/// 0 = external clock
	/// 1 = clock from VCO
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vcovregclksel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{13,"pll0vcovregclksel",3,3}
	};
	return reg;
}

	/// Repurposed
	/// Switch low voltage control signal for new regulator for PLL0 =  
	/// (Binary code)
	/// 000 =  100mV
	/// 001 =  200mV
	/// 010 =  300mV
	/// 011 =  400mV
	/// 100 =  500mV
	/// 101 =  600mV
	/// 110 =  700mV
	/// 111 =  800mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vcodpmctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{13,"pll0vcodpmctrl",2,0}
	};
	return reg;
}

	/// Spare not used in v101
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vcopdpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{14,"pll0vcopdpwrdb",15,15}
	};
	return reg;
}

	/// PLL0 voltage regulator process compensation control signal = 
	/// 0 =  ss corner
	/// 1 =  other corner
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vregplldpmen(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{14,"pll0vregplldpmen",14,14}
	};
	return reg;
}

	/// PLL0 voltage regulator bleed current control
	/// 0 =  enable bleed current
	/// 1 =  disable bleed current
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vregpllbleedb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{14,"pll0vregpllbleedb",13,13}
	};
	return reg;
}

	/// Voltage level control of vreg_pll  regulator of PLL0.
	/// 00000 =  Minimum voltage.
	/// ..
	/// 11111 =  Maximum voltage.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vregpllsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{14,"pll0vregpllsel",12,8}
	};
	return reg;
}

	/// DLF (Digital Loop Filter) regulator process compensation control signal for PLL0 :
	/// 0 =  ss corner
	/// 1 =  other corner
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vregdlfdpmen(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{14,"pll0vregdlfdpmen",6,6}
	};
	return reg;
}

	/// DLF clocking regulator bleed current control for PLL0.
	/// 0 =  enable bleed current
	/// 1 =  disable bleed current
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vregdlfbleedb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{14,"pll0vregdlfbleedb",5,5}
	};
	return reg;
}

	/// Voltage level control of  vreg_dlf regulator of PLL0.
	/// 00000 = Minimum voltage.
	/// ..
	/// 11111 = Maximum voltage.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vregdlfsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{14,"pll0vregdlfsel",4,0}
	};
	return reg;
}

	/// bandwidth selection for new regulator for PLL0
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vconewregbwsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{15,"pll0vconewregbwsel",15,14}
	};
	return reg;
}

	/// Power down for vtune buffer  for PLL0
	/// 0 = power off   
	/// 1 = power on
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vcovtunebufpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{15,"pll0vcovtunebufpwrdb",13,13}
	};
	return reg;
}

	/// Spare not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vcocompenstart(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{15,"pll0vcocompenstart",12,12}
	};
	return reg;
}

	/// Spare not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vcocompenpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{15,"pll0vcocompenpwrdb",11,11}
	};
	return reg;
}

	/// Spare not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vcocompenbw(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{15,"pll0vcocompenbw",10,9}
	};
	return reg;
}

	/// PLL0 ITANK selection mode
	/// 0 =  Auto- calibrated by FSM
	/// 1 =  Manual - assigned by user
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0itankcalmode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{15,"pll0itankcalmode",8,8}
	};
	return reg;
}

	/// PLL0 FREQCAL selection mode
	/// 0 =  Auto- calibrated by FSM
	/// 1 =  Manual - assigned by user
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0freqcalmode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{15,"pll0freqcalmode",7,7}
	};
	return reg;
}

	/// vcodiv regulator process compensation control signal for PLL0 
	/// 0 =  ss corner
	/// 1 =  other corner
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vregvcodivdpmen(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{15,"pll0vregvcodivdpmen",6,6}
	};
	return reg;
}

	/// vcodiv regulator bleed circuit control for PLL0
	/// 0 =  enable bleed current
	/// 1 =  disable bleed current
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vregvcodivbleedb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{15,"pll0vregvcodivbleedb",5,5}
	};
	return reg;
}

	/// Voltage level control of vreg_vcodiv  regulator of PLL0
	/// 00000: Minimum voltage.
	/// ..
	/// 11111: Maximum voltage.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vregvcodivsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{15,"pll0vregvcodivsel",4,0}
	};
	return reg;
}

	/// bit[15] PLL0 LCVCO compensation force High
	/// 0 = normal operation
	/// 1 = force High
	/// 
	/// bit[14] PLL0 H16 compensator powerdown
	/// 0 = power off
	/// 1 = power on (active)
	/// 
	/// bits[13:0]  spare
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0spare(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{16,"pll0spare",15,0}
	};
	return reg;
}

	/// PLL1 power down, active low
	/// New in v101: Used as a trigger to power up/down PLL1 sequentially with default settings.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1pwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{17,"pll1pwrdb",15,15}
	};
	return reg;
}

	/// provide a 200k feedback resistor shunt across the DLF (Digital Loop Filter) integrator capacitor in PLL1, active low. 
	/// 0 = no resistor in shunt
	/// 1 = 200K resistor shunt across DLF integ cap applied
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1dlfresfbpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{17,"pll1dlfresfbpwrdb",9,9}
	};
	return reg;
}

	/// DLF (Digital Loop Filter) circuitry power down for PLL1, active low
	/// 0 = Power down 
	/// 1 = Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1dlfpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{17,"pll1dlfpwrdb",8,8}
	};
	return reg;
}

	/// Sample and Hold circuitry power down in PLL1, active low
	/// 0 = Power down 
	/// 1 = Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1dlfshpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{17,"pll1dlfshpwrdb",7,7}
	};
	return reg;
}

	/// DLF  test mode power down in PLL1. It also disconnects DTB and ATB DLF muxes,  active  low.
	/// 0 = Power down 
	/// 1 = Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1dlftstpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{17,"pll1dlftstpwrdb",6,6}
	};
	return reg;
}

	/// DLF active common mode circuitry power down for PLL1.  A 100k feedback resistor shunts the DLF integrator capacitor instead. Active Low
	/// 0 = Power down
	/// 1 = Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1dlfcmfbpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{17,"pll1dlfcmfbpwrdb",5,5}
	};
	return reg;
}

	/// pll1 enable chopping function
	/// 0: chopping is disabled on the DLF
	/// 1: chopping is enabled on the DLF
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1dlfchoppwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{17,"pll1dlfchoppwrdb",4,4}
	};
	return reg;
}

	/// PLL1 pll regulator power down, active low
	/// 0 = Power down 
	/// 1 = Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vregpllpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{17,"pll1vregpllpwrdb",3,3}
	};
	return reg;
}

	/// PLL1  dlf regulator power down, active low
	/// 0 = Power down 
	/// 1 = Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vregdlfpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{17,"pll1vregdlfpwrdb",2,2}
	};
	return reg;
}

	/// PLL1 vcodivider regulator power down, active low
	/// 0 = Power down 
	/// 1 = Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vregvcodivpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{17,"pll1vregvcodivpwrdb",0,0}
	};
	return reg;
}

	/// Swap PFD (Phase Frequency Detector) UP and DOWN signal for PLL1, Active high
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1pfdupdnswap(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{18,"pll1pfdupdnswap",14,14}
	};
	return reg;
}

	/// Force the PFD output to be UP for PLL1.
	/// 0 = Let the PFD detect frequency and phase difference.
	/// 1 = Force the PFD output to be UP.
	/// Note: setting both PFDFORCEUP and PFDFORCEDN to 1 is not allowed.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1pfdforceup(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{18,"pll1pfdforceup",13,13}
	};
	return reg;
}

	/// Force the PFD output to be DOWN for PLL1.
	/// 0 = Let the PFD detect frequency and phase difference.
	/// 1 = Force the PFD output to be DOWN.
	/// Note: setting both PFDFORCEUP and PFDFORCEDN to 1 is not allowed.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1pfdforcedn(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{18,"pll1pfdforcedn",12,12}
	};
	return reg;
}

	/// Select the pulse width of the PFD outputs (both UP/DOWN) to adjust the bandwidth of the PLL1.
	/// 00 = 65ps
	/// 01 = 84ps
	/// 10 = 104ps
	/// 11 = 135ps
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1pfdpulsewidth(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{18,"pll1pfdpulsewidth",11,10}
	};
	return reg;
}

	/// VCO calibration enable signal for PLL1, active low.
	/// 0 = Open Loop PLL
	/// 1 = Closed loop PLL
	/// 
	/// Note: In VCO auto calib. mode, when the calib. FSM starts, it loads the register value on the signal which drives the analog. When the calib. FSM finishes, it sets 1 on the same signal.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1cpcalrstb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{18,"pll1cpcalrstb",7,7}
	};
	return reg;
}

	/// PLL1 vtune differential voltage control when VCO is being calibrated :  (asserted levels have changed in v101)
	/// 000 =  -400mV
	/// 001 =  -300mV
	/// 010 =  -200mV
	/// 011 =  -100mV
	/// 100 =  0V (default )
	/// 101 =  100mV
	/// 110 =  200mV
	/// 111 =  300mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1cpcalrstlvl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{18,"pll1cpcalrstlvl",6,4}
	};
	return reg;
}

	/// Selects Charge pump reference voltage level for PLL0. 
	/// 000 =  463mV
	/// 001 =  470mV
	/// 010 =  480mV 
	/// 011 =  493mV
	/// 100 =  502mV (default)
	/// 101 =  517mV
	/// 110 =  527mV
	/// 111 =  536mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1cpvreflvl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{18,"pll1cpvreflvl",2,0}
	};
	return reg;
}

	/// Programs PLL1 integral charge pump current 
	/// 00 = 10 uA
	/// 01 = 20 uA
	/// 10 = 30 uA
	/// 11 = 40 uA
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1cpintcrntsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{19,"pll1cpintcrntsel",12,11}
	};
	return reg;
}

	/// Programs PLL1 proportional charge pump current  
	/// 000 = 1000 uA
	/// 001 = 1200 uA
	/// 010 = 1400 uA
	/// 011 = 1600 uA
	/// 100 = 1800 uA
	/// 101 = 2000 uA
	/// 110 = 2200 uA
	/// 111 = 2400 uA
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1cppropcrntsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{19,"pll1cppropcrntsel",6,4}
	};
	return reg;
}

	/// Programs the PLL1 DLF (Digital Loop Filter) integrator capacitor (Cint) unit count from 6 to 14. Each Cint unit is 545fF. Select the DLF integrator capacitor (Cint) and proportional capacitor (Cprop). dlf_cint_sel_i[2] is spare bit.
	/// [1:0]=00, Cint=2.4pF,  Cprop=2.18pF
	/// [1:0]=01, integral C=4.8pF,  Cprop=2.18pF
	/// Default  [1:0]=10, Cint=7.2pF,  Cprop=4.36pF
	/// [1:0]=11, Cint=9.6pF,  Cprop=4.36pF
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1dlfcintsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{20,"pll1dlfcintsel",15,13}
	};
	return reg;
}

	/// Sets PLL1 Sample and Hold clock sample width
	/// 0 = 1 ps
	/// 1 = 2 ps
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1dlfshdelsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{20,"pll1dlfshdelsel",7,7}
	};
	return reg;
}

	/// Diagnostic test mode for PLL1 DLF to sample internal digital signals of the DLF.
	/// (Not for Customer use)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1dlfseldtb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{20,"pll1dlfseldtb",6,2}
	};
	return reg;
}

	/// Switches in PLL1 Sample and Hold capacitors
	/// 00 =  no caps connected
	/// 01 =  1.6pF
	/// 10 =  1.6pF
	/// 11 =  3.2pF
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1dlfshcapsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{20,"pll1dlfshcapsel",1,0}
	};
	return reg;
}

	/// VCO band select control bits for PLL1 : 
	/// 000 =  band0
	/// 001 =  band1
	/// 010 =  band2
	/// 011 =  band3
	/// Others  =  Not valid
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vcobandsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{21,"pll1vcobandsel",14,12}
	};
	return reg;
}

	/// PLL1 Regulator RC filter short out control pin = 
	/// 0 =  RC Filter is in use
	/// 1 =  RC Filter is shorted
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vcoregfilshorten(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{21,"pll1vcoregfilshorten",11,11}
	};
	return reg;
}

	/// This control bit is for test only. If PLL1 VCO can not start oscillating, setting this control bit  HIGH  connects lvcc_vcocore directly to hvcc.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vcoswthhien(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{21,"pll1vcoswthhien",10,10}
	};
	return reg;
}

	/// DESCRIPTION CHANGED IN V101 .... 
	/// 
	/// PLL1 VCO frequency calibration control bits:
	/// Bit[4:1] 
	/// 0000= all caps turned off(highest osc freq for the band)
	/// 0001=1 cap turned on
	/// 0010= 2 caps turned on
	/// ...........
	/// 1111= 15 caps turned on 
	/// 
	/// Bit[0]  selects turn on of Half caps for increased freq granularity
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vcofreqcal(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{21,"pll1vcofreqcal",9,5}
	};
	return reg;
}

	/// regulator output voltage control bits used to trim internal  supply voltage of  PLL1 VCO
	/// 00000 = minimum Voltage 
	/// ..
	/// 11111 =  maximum Voltage
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vcoitank(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{21,"pll1vcoitank",4,0}
	};
	return reg;
}

	/// reference select for PLL1 VCO second regulator
	/// Reference voltage control signal for new regulator =  
	/// (Binary code)
	/// 0000 =  445mV
	/// 0001 =  455mV
	/// 0010 =  465mV
	/// 0011 =  475mV
	/// 0100 =  485mV
	/// 0101 =  495mV
	/// 0110 =  505mV
	/// 0111 =  515mV 
	/// 1000 =  525mV
	/// 1001 =  535mV
	/// 1010 =  545mV
	/// 1011 =  555mV
	/// 1100 ?1111 =  not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vcovref(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{22,"pll1vcovref",15,12}
	};
	return reg;
}

	/// bit[1] used to control 1/4 LSB freqcal on PLL1 VCO tuning
	/// 0 = 1/4 LSB freqcal is not active
	/// 1 = 1/4 LSB freqcal is active
	/// 
	/// bit[0] spare bit
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vcodivspare(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{22,"pll1vcodivspare",11,10}
	};
	return reg;
}

	/// select second regulator for PLL1 VCO 
	/// 0 = old regulator
	/// 1 = new regulator
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vcovregsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{22,"pll1vcovregsel",9,9}
	};
	return reg;
}

	/// control code for divide-by-1.5 for PLL1
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vcodiv1p5ctrlcode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{22,"pll1vcodiv1p5ctrlcode",8,4}
	};
	return reg;
}

	/// select the clock input for the second regulator for PLL1 VCO
	/// 0 = external clock
	/// 1 = clock from VCO
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vcovregclksel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{22,"pll1vcovregclksel",3,3}
	};
	return reg;
}

	/// Repurposed -
	/// Switch low voltage control signal for new regulator for PLL1 :  
	/// 000 =  100mV
	/// 001 =  200mV
	/// 010 =  300mV
	/// 011 =  400mV
	/// 100 =  500mV
	/// 101 =  600mV
	/// 110 =  700mV
	/// 111 =  800mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vcodpmctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{22,"pll1vcodpmctrl",2,0}
	};
	return reg;
}

	/// spare not used in v101
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vcopdpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{23,"pll1vcopdpwrdb",15,15}
	};
	return reg;
}

	/// PLL1 voltage regulator process compensation control signal: 
	/// 0 =  ss corner
	/// 1 =  other corner
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vregplldpmen(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{23,"pll1vregplldpmen",14,14}
	};
	return reg;
}

	/// PLL1 voltage regulator bleed current control
	/// 0 =  enable bleed current
	/// 1 =  disable bleed current
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vregpllbleedb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{23,"pll1vregpllbleedb",13,13}
	};
	return reg;
}

	/// Voltage level control of vreg_pll  regulator of PLL1.
	/// 00000: Minimum voltage.
	/// ..
	/// 11111: Maximum voltage.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vregpllsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{23,"pll1vregpllsel",12,8}
	};
	return reg;
}

	/// DLF (Digital Loop Filter)  regulator process compensation control signal for PLL1 : 
	/// 0 =  ss corner
	/// 1 =  other corner
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vregdlfdpmen(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{23,"pll1vregdlfdpmen",6,6}
	};
	return reg;
}

	/// DLF clocking regulator bleed current control for PLL1.
	/// 0 =  enable bleed current
	/// 1 =  disable bleed current
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vregdlfbleedb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{23,"pll1vregdlfbleedb",5,5}
	};
	return reg;
}

	/// Voltage level control of  vreg_dlf regulator of PLL1.
	/// 00000: Minimum voltage.
	/// ..
	/// 11111: Maximum voltage.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vregdlfsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{23,"pll1vregdlfsel",4,0}
	};
	return reg;
}

	/// bandwidth selection for new regulator for PLL1
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vconewregbwsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{24,"pll1vconewregbwsel",15,14}
	};
	return reg;
}

	/// Power down for vtune buffer  for PLL1
	/// 0 = power off   
	/// 1 = power on
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vcovtunebufpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{24,"pll1vcovtunebufpwrdb",13,13}
	};
	return reg;
}

	/// spare not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vcocompenstart(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{24,"pll1vcocompenstart",12,12}
	};
	return reg;
}

	/// spare not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vcocompenpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{24,"pll1vcocompenpwrdb",11,11}
	};
	return reg;
}

	/// spare not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vcocompenbw(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{24,"pll1vcocompenbw",10,9}
	};
	return reg;
}

	/// PLL1 ITANK selection mode
	/// 0 =  Auto- calibrated by FSM
	/// 1 =  Manual - assigned by user
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1itankcalmode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{24,"pll1itankcalmode",8,8}
	};
	return reg;
}

	/// PLL1 FREQCAL selection mode
	/// 0 =  Auto- calibrated by FSM
	/// 1 =  Manual - assigned by user
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1freqcalmode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{24,"pll1freqcalmode",7,7}
	};
	return reg;
}

	/// vcodiv regulator process compensation control signal for PLL1 : 
	/// 0 =  ss corner
	/// 1 =  other corner
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vregvcodivdpmen(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{24,"pll1vregvcodivdpmen",6,6}
	};
	return reg;
}

	/// vcodiv regulator bleed circuit control for PLL1
	/// 0 =  enable bleed current
	/// 1 =  disable bleed current
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vregvcodivbleedb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{24,"pll1vregvcodivbleedb",5,5}
	};
	return reg;
}

	/// Voltage level control of vreg_vcodiv  regulator of PLL1
	/// 00000: Minimum voltage.
	/// ..
	/// 11111: Maximum voltage.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vregvcodivsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{24,"pll1vregvcodivsel",4,0}
	};
	return reg;
}

	/// bit[15] PLL1 LCVCO compensation force High
	/// 0 = normal operation
	/// 1 = force High
	/// 
	/// bit[14] PLL1 H16 compensator powerdown
	/// 0 = power off
	/// 1 = power on (active)
	/// 
	/// bits[13:0]  spare
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1spare(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{25,"pll1spare",15,0}
	};
	return reg;
}

	/// ADC (in Clock Slice)  Reset to discharge integrator and Start New measurement
	/// 0 = Reset to discharge integrator
	/// 1 =  Start New measurement
	/// Default as requested by Digital Design
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::adcrstb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{26,"adcrstb",15,15}
	};
	return reg;
}

	/// ADC (in Clock Slice) reference selector.  This bit also selects between hvcc_scaler code and 800mV mapper code from within DF code mapper:
	/// 0 = HVCC is the reference
	/// 1 = vref_bg (bandgap voltage 800mV) is the reference
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::adcabsmeasen(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{26,"adcabsmeasen",14,14}
	};
	return reg;
}

	/// ADC (in Clock Slice) input voltage selector
	/// 0 = This setting is for mission mode
	/// Both inputs are de-selected when TSENSOREN is enabled
	/// 1 = The ADC inputs are both connected to a reference voltage for calibration purpose
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::adctsten(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{26,"adctsten",13,13}
	};
	return reg;
}

	/// ADC (in Clock Slice) common mode control signal
	/// 00 = 500 mV
	/// 01 = 550 mV
	/// 10 = 600 mV
	/// 11 = 650 mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::adcvcmctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{26,"adcvcmctrl",12,11}
	};
	return reg;
}

	/// Not Used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cstopfsmcalspare(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{26,"cstopfsmcalspare",10,10}
	};
	return reg;
}

	/// DPM Initial Settings Enable
	/// 0 =  default
	/// 1 =  Set by FW to propagate initial settings to analog I/F
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dpminitsettingen(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{26,"dpminitsettingen",9,9}
	};
	return reg;
}

	/// Set to 1 to reset CS TOP FSM
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cstopfsmcalclr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{26,"cstopfsmcalclr",8,8}
	};
	return reg;
}

	/// MISC CAL FORCE DEFAULT =  set each bit to 1 to force misc cal fsm to start from default value. 
	/// [7] =  BGV cal
	/// [6] =  RXTERM cal
	/// [5] =  PLL0/PLL1_CPVREF cal
	/// [4] =  PLL0/PLL1_VREG_DLF_PLL_VCODIV cal
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::misccalforcedefault(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{26,"misccalforcedefault",7,4}
	};
	return reg;
}

	/// DPM Detection Done
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dpmdetdone(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{26,"dpmdetdone",3,3}
	};
	return reg;
}

	/// DPM Detection Task Select = 
	/// [0] =  set to 1 to enable Temperature Sensor reading
	/// [1] =  Set to 1 to enable P-Channel Vth reading
	/// [2] =  Set to 1 to enable N-Channel Vth reading
	/// To start DPM detection, set CS CSR58[15] to 1
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dpmdettasksel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{26,"dpmdettasksel",2,0}
	};
	return reg;
}

	/// Comparator (in ClockSlice) reference mode select. Also see related register CS CSR7 COMPPWRDB )
	/// 0 =  Comparator operation is single-ended.  The input selected by CS CSR27 COMPCALMUXCTRL=2'b11 is compared against reference voltage set by CS CSR27 COMPVREFSEL 
	/// 1 = Comparator operation is differential.  The inputs selected by CS CSR27 COMPCALMUXCTRL
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::compmodesel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{27,"compmodesel",15,15}
	};
	return reg;
}

	/// Comparator input signal select:
	/// x00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// x01 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// x10 = Disabled/High Impedance (NO INPUT SELECTED)
	/// x11 = clockslice atb bus, sigle ended (Refer to related register CSATBTOPSEL )
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::compcalmuxctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{27,"compcalmuxctrl",14,12}
	};
	return reg;
}

	/// Comparator Vref generator select bits : 
	/// Setting = 400mV + (6.25mV x  COMPVREFSEL)                                    
	/// 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::compvrefsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{27,"compvrefsel",11,6}
	};
	return reg;
}

	/// Offset override voltage, to be changed before starting vrefgen cal.
	/// 0: VREFGENOFFSET will be updated with calibrated offset after vrefgen cal
	/// 1: VREFGENOFFSET will not be updated with calibrated offset after vrefgen cal
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::overrideoffset(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{27,"overrideoffset",5,5}
	};
	return reg;
}

	/// Depending on the sign bit VREFGENOFFSET[4] polarity (0 or 1), the common Vrefgen calibrated offset correction will be added/subtracted to/from the target value of all voltage calibrations
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vrefgenoffset(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{27,"vrefgenoffset",4,0}
	};
	return reg;
}

	/// TOP_FSM Bypass control
	/// 0 = TOP_FSM controls vco_top_fsm (v101 mode)
	/// 1 = vco_top_fsm is directly controlled by firmware (v100 mode).  TOP_FSM contol of vco_top_fsm is bypassed.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::topvcofsmbypass(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{28,"topvcofsmbypass",15,15}
	};
	return reg;
}

	/// Select which PLL's VCO to be calibrated by the automatic calibration FSM.
	/// 0 = Select PLL0
	/// 1 = Select PLL1
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvcocalsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{28,"lcvcocalsel",14,14}
	};
	return reg;
}

	/// Choose calibrate procedure in automatic calibration mode, i.e., when LCVCOCALMODE is set to 0.
	/// 00 = 2-pass calibration
	/// 01 = 1-pass calibration (both voltage and frequency)
	/// 10 = 1-pass calibration (voltage only)
	/// 11 = 1-pass calibration (frequency only)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvcocalctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{28,"lcvcocalctrl",13,12}
	};
	return reg;
}

	/// PLL0 Power Sequence Done Status bit
	/// New in V101
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cspll0pwrseqdone(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{28,"cspll0pwrseqdone",11,11}
	};
	return reg;
}

	/// PLL1 Power Sequence Done Status bit
	/// New in V101
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cspll1pwrseqdone(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{28,"cspll1pwrseqdone",10,10}
	};
	return reg;
}

	/// Power sequence FSM clear 
	/// New in V101
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cspwrseqfsmclr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{28,"cspwrseqfsmclr",9,9}
	};
	return reg;
}

	/// Firmware overwrite of Power up sequence (Do not use)
	/// New in V101: for special test purposes only
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csfwoverwrite(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{28,"csfwoverwrite",8,8}
	};
	return reg;
}

	/// CSR CS CAL MODE bits are connected to MISC CAL FSM via CS_TOP_FSM, which allows MISC and VCO calibration tasks to be launched from alternate start bits. The mode selections are:
	///  00 = CSR propagation. To propagate CSR values to analog I/F on all signals intercepted by MISC CAL FSM and DPM Detection FSM (Vreg sel, atb,...)
	///  01 = MISC cal launched from misccalfsmastart
	///  10 = NOT to be used by FW/user
	///  11 = VCO cal launched from cs_calib_start
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cscalmode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{28,"cscalmode",7,6}
	};
	return reg;
}

	/// select between the ADC (in ClockSlice) or Comparator (in ClockSlice) for CP Vref and Vreg calibration tasks
	/// 0= Comparator selected  
	/// 1=ADC selected
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csadccompsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{28,"csadccompsel",5,5}
	};
	return reg;
}

	/// LCVCO calibrations completed. Latched until being read 
	/// 0 = LCVCO calibrations do not finish yet.
	/// 1 = LCVCO calibrations finish.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvcocaldone(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{28,"lcvcocaldone",4,4}
	};
	return reg;
}

	/// LCVCO calibrations didn't succeed. Latched until being read.
	/// 0 = LCVCO calibrations didn't complete successfully.
	/// 1 = LCVCO calibrations completed successfully.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvcocalerr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{28,"lcvcocalerr",3,3}
	};
	return reg;
}

	/// Status of LCVCO calibrations. If LCVCO calibrations didn't succeed, this register gives the internals status and/or conditions of the calibration processes.
	/// Mapping TBD.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::lcvcocalstatus(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{28,"lcvcocalstatus",2,0}
	};
	return reg;
}

	/// atb_out2pin signal select : 
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = atbout_clockslice
	/// 010 = atbout_auxclockslice
	/// 011 = atbout_serviceslice
	/// 100 = atbout_dataslice
	/// other settings =  High Impedance
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::atbfinalsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{29,"atbfinalsel",15,13}
	};
	return reg;
}

	/// clockslice atb bus select : 
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  biascmu atb bus 
	/// 010 =  pll0 atb bus
	/// 011 =  pll1 atb bus
	/// 100 =  service slice atb bus
	/// 101 =  dataslice atb bus
	/// 110 =  mos detector osc atb out
	/// 111 =  low offset comparator
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csatbtopsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{29,"csatbtopsel",12,10}
	};
	return reg;
}

	/// Reserved fields. Analog pins don't exist
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csatbspare(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{29,"csatbspare",9,6}
	};
	return reg;
}

	/// bias atb bus select :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 to 101 =  do not use
	/// 110 =  icvp 50u
	/// 111 =  iccp 50u
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::biasatbsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{29,"biasatbsel",5,3}
	};
	return reg;
}

	/// Comparator ATB bus select bits :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  Internal node vcmref is selected (vref to latch comparator)
	/// 010 =  Internal node vout_opamp is selected (positive di to latch comparator
	/// 011 =  Internal node vref is selected (reference voltage for comparator)
	/// 100 =  Internal node vp1 is selected (positive input of comparator)
	/// 101 =  Internal node vm1 is selected (negative input of comparator)
	/// 110 =  no input selected
	/// 111 =  no input selected
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::compatbctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{29,"compatbctrl",2,0}
	};
	return reg;
}

	/// PLL0 atb bus select :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  pll0_regulator atb bus
	/// 010 =  no input selected
	/// 011 =  pll0 dlf atb bus
	/// 100 =  pll0 vco atb bus
	/// 101 =  no input selected
	/// 110 =  pll0 hsclk distribution atb bus
	/// 111 =  pll0 vco to adc test signal
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0atbplltopsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{30,"pll0atbplltopsel",15,13}
	};
	return reg;
}

	/// PLL0 dlf atb bus select : 
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  vcmf_i
	/// 010 =  vcmfctrl_o
	/// 011 =  vref_0p525_io
	/// 100 =  pbiastop
	/// 101 =  pbiasbot
	/// 110 =  sampp_o
	/// 111 =  sampm_o
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0atbpllctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{30,"pll0atbpllctrl",10,8}
	};
	return reg;
}

	/// PLL0 vco atb bus select
	/// 00 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 =  lvcc_vcocore_atb
	/// 10 =  vref_atb
	/// 11 =  no input selected
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0atbvcoctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{30,"pll0atbvcoctrl",6,5}
	};
	return reg;
}

	/// pll0 vco2adc atb bus select
	/// 00 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 =  lvcc_vcocore_half
	/// 10 =   vcotunep_add    
	/// 11 =   vcotunem_add
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0adcvcoctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{30,"pll0adcvcoctrl",4,3}
	};
	return reg;
}

	/// PLL0 Digital test bus output
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0dtbout(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{30,"pll0dtbout",0,0}
	};
	return reg;
}

	/// PLL0 regulator atb bus select :
	/// 000 = High Impedance (NO INPUT SELECTED)
	/// 001 =  pll regulator atb bus
	/// 010 =  dlf regulator atb bus
	/// 011 =  vcodiv regulator atb bus
	/// 100 =  High Impedance
	/// 101 to 111 = High Impedance
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0atbvregsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{31,"pll0atbvregsel",14,12}
	};
	return reg;
}

	/// PLL0 pll regulator atb bus select :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  vref
	/// 010 =  lbias/vbeos
	/// 011 =  High Impedance
	/// 100 =  High Impedance
	/// 101 =  vmid
	/// 110 =  vreg_half  
	/// 111 =  High Impedance
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0atbvregpllctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{31,"pll0atbvregpllctrl",11,9}
	};
	return reg;
}

	/// PLL0 dlf regulator atb bus select :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  vref
	/// 010 =  lbias/vbeos
	/// 011 =  High Impedance
	/// 100 =  High Impedance
	/// 101 =  vmid
	/// 110 =  vreg_half  
	/// 111 =  High Impedance
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0atbvregdlfctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{31,"pll0atbvregdlfctrl",8,6}
	};
	return reg;
}

	/// PLL0 vcodiv regulator atb bus select : 
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  vref
	/// 010 =  lbias/vbeos
	/// 011 =  High Impedance
	/// 100 =  High Impedance
	/// 101 =  vmid
	/// 110 =  vreg_half  
	/// 111 =  High Impedance
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0atbvregvcodivctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{31,"pll0atbvregvcodivctrl",2,0}
	};
	return reg;
}

	/// PLL1 atb bus select :
	/// 000 =    Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  pll1_regulator atb bus     
	/// 010 =  no connection                 
	/// 011 =  pll1 dlf atb bus
	/// 100 =  pll1 vco atb bus
	/// 101 =  no connection
	/// 110 =  pll1 hsclk distribution atb bus
	/// 111 =  pll1 vco to adc test signal
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1atbplltopsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{32,"pll1atbplltopsel",15,13}
	};
	return reg;
}

	/// PLL1 dlf atb bus select :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  vcmf_i
	/// 010 =  vcmfctrl_o
	/// 011 =  vref_0p525_io
	/// 100 =  pbiastop
	/// 101 =  pbiasbot
	/// 110 =  sampp_o
	/// 111 =  sampm_o
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1atbpllctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{32,"pll1atbpllctrl",10,8}
	};
	return reg;
}

	/// PLL1 vco atb bus select
	/// 00 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 =  lvcc_vcocore_atb
	/// 10 =  vref_atb
	/// 11 =  no input selected
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1atbvcoctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{32,"pll1atbvcoctrl",6,5}
	};
	return reg;
}

	/// PLL1 vco2adc atb bus select
	/// 00 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 =  lvcc_vcocore_half
	/// 10 =  vcotunep_add
	/// 11 =  vcotunem_add
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1adcvcoctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{32,"pll1adcvcoctrl",4,3}
	};
	return reg;
}

	/// PLL1 digital test bus output
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1dtbout(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{32,"pll1dtbout",0,0}
	};
	return reg;
}

	/// pll1 regulator atb bus select :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED) 
	/// 001 =  pll regulator atb bus
	/// 010 =  dlf regulator atb bus
	/// 011 =  vcodiv regulator atb bus
	/// 100 to 111 =  High Impedance
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1atbvregsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{33,"pll1atbvregsel",14,12}
	};
	return reg;
}

	/// pll1 pll regulator atb bus select :  
	/// 000 =    High Impedance (NO INPUT SELECTED)
	/// 001 =  vref
	/// 010 =  lbias/vbeos
	/// 011 =  High Impedance
	/// 100 =  High Impedance
	/// 101 =  vmid
	/// 110 =  vreg_half 
	/// 111 =  High Impedance
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1atbvregpllctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{33,"pll1atbvregpllctrl",11,9}
	};
	return reg;
}

	/// pll1 dlf regulator atb bus select :  
	/// 000 =    High Impedance (NO INPUT SELECTED)
	/// 001 =  vref
	/// 010 =  lbias/vbeos
	/// 011 =  High Impedance
	/// 100 =  High Impedance
	/// 101 =  vmid
	/// 110 =  vreg_half  
	/// 111 =  High Impedance
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1atbvregdlfctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{33,"pll1atbvregdlfctrl",8,6}
	};
	return reg;
}

	/// pll1 vcodiv regulator atb bus select : 
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  vref
	/// 010 =  lbias/vbeos
	/// 011 =  High Impedance
	/// 100 =  High Impedance
	/// 101 =  vmid
	/// 110 =  vreg_half
	/// 111 =  High Impedance
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1atbvregvcodivctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{33,"pll1atbvregvcodivctrl",2,0}
	};
	return reg;
}

	/// Serviceslice (SS) power down control. Active low.
	/// 0 = Power down the serviceslice
	/// 1 = Power up the serviceslice
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::sspwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{34,"sspwrdb",15,15}
	};
	return reg;
}

	/// SS refclk0 receiver power down, active low
	/// 0 = power down
	/// 1= power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk0pwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{34,"ssrefclk0pwrdb",14,14}
	};
	return reg;
}

	/// SS refclk1 receiver power down, active low
	/// 0 = power down
	/// 1= power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk1pwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{34,"ssrefclk1pwrdb",13,13}
	};
	return reg;
}

	/// SS refclk0 CML divider power down, active low
	/// 0 = power down
	/// 1= power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk0cmldivpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{34,"ssrefclk0cmldivpwrdb",12,12}
	};
	return reg;
}

	/// SS refclk1 CML divider power down, active low
	/// 0 = power down
	/// 1= power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk1cmldivpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{34,"ssrefclk1cmldivpwrdb",11,11}
	};
	return reg;
}

	/// SS refclk0 divider ratio select (Refer to fig.4 in the HiLink30_datasheet)
	/// 0 = div1
	/// 1 = div2
	/// Only applicable when there is a serviceslice in the macro.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk0div2sel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{34,"ssrefclk0div2sel",10,10}
	};
	return reg;
}

	/// SS refclk1 divider ratio select (Refer to fig.4 in the HiLink30_datasheet)
	/// 0 = div1
	/// 1 = div2
	/// Only applicable when there is a serviceslice in the macro.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk1div2sel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{34,"ssrefclk1div2sel",9,9}
	};
	return reg;
}

	/// Select the refclk bus 1's source. Only applicable when there is a serviceslice applicable.
	/// 0 = Choose the reference clock 1 from the bump as the refclk bus 1's source.
	/// 1 = tied low  .  Not available.   [Choose a CMOS reference clock from the core as the refclk bus 1's source] Applicable only when the CMOS reference clock is available to HiLink.
	/// Note: If the CMOS reference clock is not available to HiLink, this bit should be set to 0.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::sscmosrefclksel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{34,"sscmosrefclksel",8,8}
	};
	return reg;
}

	/// SS refclk0 buffer bias control 
	/// 00 = xx uA
	/// 01 = 
	/// 10 = 
	/// 11 = yy uA
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk0biasctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{34,"ssrefclk0biasctrl",7,6}
	};
	return reg;
}

	/// SS refclk1 buffer bias control 
	/// 00 = xx uA
	/// 01 = 
	/// 10 = 
	/// 11 = yy uA
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk1biasctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{34,"ssrefclk1biasctrl",5,4}
	};
	return reg;
}

	/// SS refclk0 distribution buffer bias control 
	/// 00 = xx uA
	/// 01 = 
	/// 10 = 
	/// 11 = yy uA
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk0distbiasctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{34,"ssrefclk0distbiasctrl",3,2}
	};
	return reg;
}

	/// SS refclk1 distribution buffer bias control signal
	/// 00 = xx uA
	/// 01 = 
	/// 10 = 
	/// 11 = yy uA
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssrefclk1distbiasctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{34,"ssrefclk1distbiasctrl",1,0}
	};
	return reg;
}

	/// Powers down the bias icv. Active low
	/// 0 =  Power down  
	/// 1 =  Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::biasmstricvpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{35,"biasmstricvpwrdb",9,9}
	};
	return reg;
}

	/// Powers down the bias icc. Active low
	/// 0 =  Power down  
	/// 1 =  Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::biasmstriccpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{35,"biasmstriccpwrdb",8,8}
	};
	return reg;
}

	/// Powers down the bias iptat. Active low
	/// 0 =  Power down  
	/// 1 =  Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::biasmstriptatpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{35,"biasmstriptatpwrdb",7,7}
	};
	return reg;
}

	/// Vbg Power down. Active low.
	/// 0 =  Power down  
	/// 1 =  Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vbgpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{35,"vbgpwrdb",6,6}
	};
	return reg;
}

	/// Vptat Power down. Active low.
	/// 0 =  Power down  
	/// 1 =  Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vptatpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{35,"vptatpwrdb",5,5}
	};
	return reg;
}

	/// ADC (in ServiceSlice) and temperature sensor powerdown
	/// 0 =  Power down  
	/// 1 =  Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssadcpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{35,"ssadcpwrdb",4,4}
	};
	return reg;
}

	/// Comparator (in ServiceSlice) power down :
	/// 0 =  Power down  
	/// 1 =  Power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::sscomppwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{35,"sscomppwrdb",3,3}
	};
	return reg;
}

	/// Comparator vref resistor ladder generator power down = 
	/// 0 =  Resistor ladder will output 0V at the output
	/// 1 =  Resistor ladder is active, with an output given by the ladder control bits
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::sscompvrefpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{35,"sscompvrefpwrdb",2,2}
	};
	return reg;
}

	/// not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::mosdetidacpwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{35,"mosdetidacpwrdb",1,1}
	};
	return reg;
}

	/// Repurposed: CS DPM detector power down
	/// 0 = power down 
	/// 1 = power up
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::mosdetcml2cmospwrdb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{35,"mosdetcml2cmospwrdb",0,0}
	};
	return reg;
}

	/// Test mode control. Active high
	/// 0 =  mission mode  
	/// 1 =  Test mode is active  which will output LVCC divided-down to 600mV. Over-rides bias  master opamp output.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::bg600mvlvccresdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{36,"bg600mvlvccresdiv",15,15}
	};
	return reg;
}

	/// hv_vref_bg source select:
	/// 0 =  bg buffer opamp is configured in one stage output mode. (High impedance) 
	/// 
	/// 1 =  bg buffer opamp is configured in two-stage output mode (low impedance)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::bgbufsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{36,"bgbufsel",14,14}
	};
	return reg;
}

	/// calibration enable signal, Active high
	/// 0 =mission mode
	/// 1 = calibration mode
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::bgbufcalen(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{36,"bgbufcalen",13,13}
	};
	return reg;
}

	/// BG buffer offset.
	/// 0 0000 = most negative offset
	/// ..
	/// ..
	/// ..
	/// 0 1111 = zero offset
	/// 1 0000 = zero offset 
	/// ..
	/// ..
	/// ..
	/// 1 1111 = most positive offset
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::bgbufofst(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{36,"bgbufofst",12,8}
	};
	return reg;
}

	/// Control signal setting Circuit configuration
	/// [1:0] = 00 no effect
	/// [1:0]= 01 Bias for Service Slice refclk is derived from CC current source 
	/// [1:0]= 10 Bias for Service Slice refclk is derived from   the di pin hv_vbg_ptat_in
	/// [1:0]= 11 Bias for Service Slice refclk is derived from  the di pin hv_vbg_cc_in
	/// [3:2] = 00 no effect
	/// [3:2]= 01 CV bias transmitter output value is derived from lvcc
	/// [3:2]= 10 CV bias transmitter output value is derived from the di pin hv_vbg_cc_in
	/// [3:2]= 11 CV bias transmitter output value is derived from the di pin hv_vbg_ptat_in
	/// [5:4] = 00 no effect
	/// [5:4]= 01 PTAT bias transmitter output value is derived from lvcc
	/// [5:4]= 10 PTAT bias transmitter output value is derived from the di pin hv_vbg_cc_in
	/// [5:4]= 11 PTAT bias transmitter output value is derived from the di pin hv_vbg_ptat_in
	/// [7:6] = 00 no effect
	/// [7:6]= 01 CC bias transmitter output value is derived from lvcc
	/// [7:6]= 10 CC bias transmitter output value is derived from the di pin hv_vbg_cc_in
	/// [7:6]= 11 CC bias transmitter output value is derived from the di pin hv_vbg_ptat_in
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::bgbypass(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{36,"bgbypass",7,0}
	};
	return reg;
}

	/// Offset calibration output
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::bgbufcaltrig(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{37,"bgbufcaltrig",15,15}
	};
	return reg;
}

	/// Reset internal DFF in the VBG block  (Band Gap reference voltage generator)  Assert the signal low to  disable the chopper circuit clock.  
	/// 0 = disable chopping
	/// 1 = enable chopping
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vbgrstb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{37,"vbgrstb",14,14}
	};
	return reg;
}

	/// Bypass BG/PTAT, generating BG/PTAT from hvcc. Active low
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vbgbypassb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{37,"vbgbypassb",13,13}
	};
	return reg;
}

	/// BG/PTAT mode selection.
	/// 0 =  BG mode
	/// 1 =  PTAT mode;
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vbgmode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{37,"vbgmode",12,12}
	};
	return reg;
}

	/// Chopping clock mode selection.
	/// 0 =   2MHz
	/// 1 =   4MHz;
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vbgchopclkmode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{37,"vbgchopclkmode",11,11}
	};
	return reg;
}

	/// VBG DEM (Dynamic element matching) clock  selection.
	/// 0 =   2MHz.
	/// 1 =   4MHz;
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vbgdemclkmode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{37,"vbgdemclkmode",10,10}
	};
	return reg;
}

	/// Enable Chopping clock. Active high
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vbgenchop(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{37,"vbgenchop",8,8}
	};
	return reg;
}

	/// Enable DEM clock. Active high
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vbgendem(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{37,"vbgendem",7,7}
	};
	return reg;
}

	/// Selects bandgap voltage output value according to the following ; 
	/// 000 =   769mV; 
	/// 001 =   780mV; 
	/// 010 =   791mV; 
	/// 011 =   802mV; 
	/// 100 =   814mV; 
	/// 101 =   825mV; 
	/// 110 =   837mV; 
	/// 111 =   848mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vbgreflvl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{37,"vbgreflvl",2,0}
	};
	return reg;
}

	/// Resets internal DFF in the VPTAT block (used to generate  current Proportional To Absolute Temperature).  Assert the signal low to disable  the chopper circuit.
	/// 0 = disable chopper
	/// 1 = enable chopper
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vptatrstb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{38,"vptatrstb",14,14}
	};
	return reg;
}

	/// Bypass BG/PTAT, generating BG/PTAT from hvcc. Active low
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vptatbypassb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{38,"vptatbypassb",13,13}
	};
	return reg;
}

	/// BG/PTAT mode selection.
	/// 0 =  BG mode
	/// 1 =   PTAT mode;
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vptatmode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{38,"vptatmode",12,12}
	};
	return reg;
}

	/// Chopping clock mode selection.
	/// 0 =   2MHz.
	/// 1 =   4MHz;
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vptatchopclkmode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{38,"vptatchopclkmode",11,11}
	};
	return reg;
}

	/// VPTAT  DEM (Dynamic element matching) clock  selection.
	/// 0 =   2MHz.
	/// 1 =   4MHz
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vptatdemclkmode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{38,"vptatdemclkmode",10,10}
	};
	return reg;
}

	/// Enable VPTAT block Chopping clock. Active high
	/// 0 = disable
	/// 1 = enable
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vptatenchop(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{38,"vptatenchop",8,8}
	};
	return reg;
}

	/// Enable VPTAT DEM clock. Active high
	/// 0 = disable
	/// 1 = enable
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vptatendem(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{38,"vptatendem",7,7}
	};
	return reg;
}

	/// Selects ptat voltage output value according to the following ; 
	/// 000 =   769mV; 
	/// 001 =   780mV; 
	/// 010 =   791mV; 
	/// 011 =   802mV; 
	/// 100 =   814mV; 
	/// 101 =   825mV; 
	/// 110 =   837mV; 
	/// 111 =   848mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::vptatreflvl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{38,"vptatreflvl",2,0}
	};
	return reg;
}

	/// ADC (in Service Slice) reset enable
	/// 0 =  Reset enabled
	/// 1 =  Reset disabled
	/// Default as requested by Digital Design
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssadcrstb(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{39,"ssadcrstb",15,15}
	};
	return reg;
}

	/// ADC (in Service Slice) reference selector:
	/// 0 =  HVCC is the reference
	/// 1 =  vref_bg (bandgap voltage 800mV) is the reference
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssadcabsmeasen(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{39,"ssadcabsmeasen",14,14}
	};
	return reg;
}

	/// ADC (in Service Slice) input voltage selector
	/// [SSADCTSTEN=1 and TSENSOREN=X]: Internal vcm_buff voltage is selected
	/// [SSADCTSTEN=0 and  TSENSOREN=0]: External voltage from ATB bus is selected
	/// [SSADCTSTEN=0 and  TSENSOREN=1]: temperature sensor  is selected
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssadctsten(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{39,"ssadctsten",13,13}
	};
	return reg;
}

	/// ADC (in Service Slice) common mode control signal
	/// 00 = 500 mV
	/// 01 = 550 mV
	/// 10 = 600 mV
	/// 11 = 650 mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssadcvcmctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{39,"ssadcvcmctrl",12,11}
	};
	return reg;
}

	/// ADC (in Service Slice) input selector bits :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  Vth detector Vgsp is selected
	/// 010 =  Vth detector Vgsn is selected
	/// 011 =  hvcc_div internal signal is selected
	/// 100 =  lvcc_div internal signal is selected
	/// 101 =  ss_atb_out internal signal selected
	/// 110 =  adc_tielo internal signal is selected
	/// 111 =  adc_tielo internal signal is selected
	/// hvcc_div and lvcc_div are derived from a resistor divider, which divides the voltage hvcc and lvcc by 2.
	/// ss_atb_out are derived from various muxed-in internal voltages from the Service Slice.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssadcinputsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{39,"ssadcinputsel",10,8}
	};
	return reg;
}

	/// Temperature sensor ADC enable
	/// 1 =  Temperature sensor output is selected
	/// 0 =  Temperature sensor output is disabled
	/// When enabled (logic 1), the two other dis selected by ss_adc_tst_enb are disabled.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::tsensoren(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{39,"tsensoren",7,7}
	};
	return reg;
}

	/// Temp Sensor coding for DataSlice temp detection. These bits are set in the ClockSlice digital engine and are based on the 10-bit temp measurement word:
	/// 000 = temp is in the range  [-40 to 20] �C
	/// 001 = temp is in the range  [-20 to 0] �C
	/// 010 = temp is in the range  [0 to 20] �C
	/// 011 = temp is in the range  [20 to 40] �C
	/// 100 = temp is in the range  [40 to 60] �C
	/// 101  = temp is in the range [60 to 80] �C
	/// 110 = temp is in the range  [80 to 100] �C
	/// 111 = temp is in the range  [100 to 125] �C
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::tsensorcstemp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{39,"tsensorcstemp",6,4}
	};
	return reg;
}

	/// Comparator (in Service Slice) reference mode select. [Also see related register CS CSR35 SSCOMPPWRDB]
	/// 0 = Comparator operation is single-ended.  The input selected by CSR40 SSCOMPVINPSEL is compared against reference voltage set by  CS CSR40 SSCOMPVREFSEL
	/// 1 = Comparator operation is differential.  The inputs selected by CS CSR40 SSCOMPVINPSEL and SSCOMPVINMSEL are compared
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::sscompmodesel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{40,"sscompmodesel",15,15}
	};
	return reg;
}

	/// Select bits for the Vinm  input to the high precision comparator (in Service Slice).  [Also see related register CS CSR44 RPOLYDETCALSEL before selection]
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  rx_termcal_otbm di selected (used to calibrate the Poly resistor).
	/// 010 =  rpolydet_otbm_up di selected (used for process detection)
	/// 011 =  rpolydet_otbm_dn di selected (used for process detection)
	/// 100 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// ..
	/// 111 =  High Impedance
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::sscompvinmsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{40,"sscompvinmsel",14,12}
	};
	return reg;
}

	/// Select bits for the Vinp input to the high precision comparator (in Service Slice) . [Also see related register CS CSR44 RPOLYDETCALSEL before selection]
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  rx_termcal_otbp di selected (used to calibrate the Poly resistor). 
	/// 010 =  rpolydet_otbc di selected (used for process detection)
	/// 011 =  comp_tielo di selected (output should go low)
	/// 100 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// ..
	/// 111 =  High Impedance
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::sscompvinpsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{40,"sscompvinpsel",11,9}
	};
	return reg;
}

	/// Comparator (in Service Slice) Vref generator select bits =  [Also see related register CS CSR35 SSCOMPVREFPWRDB before selection]
	/// Setting = 400mV + (6.25mV x  SSCOMPVREFSEL)                                                                                                                                                                                         000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 111111 =  Vref=793.75mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::sscompvrefsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{40,"sscompvrefsel",8,3}
	};
	return reg;
}

	/// Output of serviceslice's comparator.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::sscompstatus(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{40,"sscompstatus",0,0}
	};
	return reg;
}

	/// Process detector enable (uses threshold voltage Vth of MOS transistor to classify process corners). [Also see related register CS CSR39 SSADCINPUTSEL]
	/// 0 =  Vth process detector is disabled
	/// 1 =  Vth process detector is enabled
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::mosdeten(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{41,"mosdeten",15,15}
	};
	return reg;
}

	/// Selects between high voltage or core MOS transistors to detect its threshold voltage (Vth).  [Also see related register CS CSR41 MOSDETEN before selection]
	/// 0 =  Core transistor selected(uLVT)
	/// 1 =  High Voltage transistor selected(SVT)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::mosdetmostypesel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{41,"mosdetmostypesel",14,14}
	};
	return reg;
}

	/// not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::mosdetvcocalen(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{41,"mosdetvcocalen",13,13}
	};
	return reg;
}

	/// not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::mosdetioscptune(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{41,"mosdetioscptune",12,10}
	};
	return reg;
}

	/// not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::mosdetioscdacofst(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{41,"mosdetioscdacofst",9,8}
	};
	return reg;
}

	/// not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::mosdetioscdaccal(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{41,"mosdetioscdaccal",7,0}
	};
	return reg;
}

	/// Repurposed mosdet_psel[2] : Not implemented 
	/// bit[2]:
	/// 0 = Bias receiver opamp is in h30 mode (vss IR cancellation mode)
	/// 1= Bias receiver opamp is in h28/legacy mode (no VSS IR cancellation) (default)
	/// 
	/// bits[1:0] : not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::mosdetpsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{42,"mosdetpsel",15,13}
	};
	return reg;
}

	/// not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::mosdets1sel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{42,"mosdets1sel",12,10}
	};
	return reg;
}

	/// not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::mosdets2sel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{42,"mosdets2sel",9,8}
	};
	return reg;
}

	/// not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::mosdetiosccrosstune(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{42,"mosdetiosccrosstune",7,7}
	};
	return reg;
}

	/// not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::mosdetoscdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{42,"mosdetoscdiv",1,0}
	};
	return reg;
}

	/// Process corner code for the Nch transistor decoded in the ClockSlice  based on its threshold voltage measured.  This code is sent  to the Service Slice to be distributed to all the Dataslices.  Applies to macro with ServiceSlice ONLY  [See also related register CS CSR56 DPMNMOSCNR]
	/// 000 =  -3 sigma Vth Nch fast corner
	/// 001 =  -2 sigma Vth Nch fast corner
	/// 010 =  -1 sigma Vth Nch fast corner
	/// 011 =  Typ Vth Nch corner
	/// 100 =  +1 sigma Vth Nch slow corner
	/// 101 =  +2 sigma Vth Nch slow corner
	/// 110 =  +3 sigma Vth Nch slow corner
	/// 111 =  not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::mosdetcsnmoscnr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{43,"mosdetcsnmoscnr",15,13}
	};
	return reg;
}

	/// Process corner code for the Pch transistor decoded in the ClockSlice  based on its threshold voltage measured.  This code is sent  to the Service Slice to be distributed to all the Dataslices.  Applies to macro with ServiceSlice ONLY  [See also related register CS CSR56 DPMPMOSCNR]
	/// 000 =  -3 sigma Vth Pch fast corner
	/// 001 =  -2 sigma Vth Pch fast corner
	/// 010 =  -1 sigma Vth Pch fast corner
	/// 011 =  Typ Vth Pch corner
	/// 100 =  +1 sigma Vth Pch slow corner
	/// 101 =  +2 sigma Vth Pch slow corner
	/// 110 =  +3 sigma Vth Pch slow corner
	/// 111 =  not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::mosdetcspmoscnr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{43,"mosdetcspmoscnr",12,10}
	};
	return reg;
}

	/// CMOS Process corner code based on ILO (injection locking Oscillator) frequency measured.  This code is sent  to the Service Slice to be distributed to all the Dataslices.  Limitation =  cannot detect FS and SF corners.   Applies to macro with ServiceSlice ONLY  [See also related register CS CSR56 DPMCMOSCNR]
	/// 000 =  -3 sigma Vth CMOS fast corner
	/// 001 =  -2 sigma Vth CMOS fast corner
	/// 010 =  -1 sigma Vth CMOS fast corner
	/// 011 =  Typ Vth CMOS corner
	/// 100 =  +1 sigma Vth CMOS slow corner
	/// 101 =  +2 sigma Vth CMOS slow corner
	/// 110 =  +3 sigma Vth CMOS slow corner
	/// 111 =  not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::mosdetcscmoscnr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{43,"mosdetcscmoscnr",9,7}
	};
	return reg;
}

	/// Clock divider for Chopping circuit of DEM clk
	/// bits[6:1] :  pre div ratio (specify N-1)
	/// bit[0] : 0 = div by 2 ; 1 = div by 4
	/// [For refclk freq of 156.25Mhz, the default value of 0x13 will divide the refclk by 10x4 = 40 to generate 3.9MHz clock]
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::sschopdemclkdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{43,"sschopdemclkdiv",6,0}
	};
	return reg;
}

	/// Rpoly calibration/detection select bit:
	/// 0 = Output calibration voltages (otbp, otbm, otbc, otbm_up and otbm_dn) are tri-stated. 
	/// 1 = Output calibration voltages (otbp, otbm, otbc, otbm_up and otbm_dn) are made available and calibration/detection may start.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::rpolydetcalsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{44,"rpolydetcalsel",15,15}
	};
	return reg;
}

	/// Termination resistor calibration enable:
	/// 0 = Calibration is disabled
	/// 1 =  Calibration is enabled
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::rpolydethvrxtermcalen(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{44,"rpolydethvrxtermcalen",14,14}
	};
	return reg;
}

	/// Termination replica resistor calibration bits : 
	/// 0000 =  Termination replica is open
	/// 0001 =  Highest resistance value 
	/// ....
	/// 1111 =  Lowest resistance value
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::rpolydetcsrxtermcal(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{44,"rpolydetcsrxtermcal",13,10}
	};
	return reg;
}

	/// Rpoly (poly-silicon Resistor) process corner code based on  its measured characteristics.  This code is sent  to the Service Slice to be distributed to all the Dataslices. Applies to macro with ServiceSlice ONLY  [See also related register CS CSR57 DPMRPOLYCNR].
	/// 00 = fast poly resistor 
	/// 01 = typical poly resistor
	/// 10 = slow poly resistor
	/// 11 = not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::rpolydetcsrpolycnr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{44,"rpolydetcsrpolycnr",5,4}
	};
	return reg;
}

	/// Service slice spare input bits for dpm.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssdpmsparein(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{44,"ssdpmsparein",3,0}
	};
	return reg;
}

	/// Serviceslice spare bits.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssspare(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{45,"ssspare",15,0}
	};
	return reg;
}

	/// SS atb (Service slice Test bus) bus control signal : 
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED) 
	/// 001 =  refclk receiver atb output
	/// 010 = bias master atb output
	/// 011 = dpm atb output
	/// 1xx = High Impedance
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssatbsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{46,"ssatbsel",14,12}
	};
	return reg;
}

	/// refclk receiver atb bus control signal :
	/// 000000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// xx0101 =  refclk0 receiver buffer bias voltage
	/// 01xx10 = refclk1 receiver buffer bias voltage
	/// other setting =  not allowed
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::refclkreceiveratbsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{46,"refclkreceiveratbsel",11,6}
	};
	return reg;
}

	/// bias master atb control signal bits 5 to 3 :
	/// 000000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001xxx =  Selects bandgap related output from selection of  bits 2 to 0 (below)
	/// 010000 =  icvp_50u; 
	/// 011000 =  iptat_50u
	/// 100000 =  iccp_50u; 
	/// 101000 =  High Impedance
	/// 110000 =  hv_vref_bg 
	/// ;111000 =  High impedance
	/// 
	/// bits 2 to 0  (Band gap related)
	/// 001000  =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001001  =  iptat_10u
	/// 001010  =  ibg_10u
	/// 001011  =  vptat_inp
	/// 001100  =  vptat_inn; 
	/// 001101  =  vbg_inp
	/// 001110  =  vbg_inn
	/// ;001111  =  vbg_nstrt
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::biasmstratbsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{46,"biasmstratbsel",5,0}
	};
	return reg;
}

	/// ATB bus select bits for internal tsensor voltages
	/// 00 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 01 =  Internal Vbe voltage is selected
	/// 10 =  Internal sw cap voltage output is selected (output of temp sensor)
	/// 11 =  no input selected
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::tsensorhvatbsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{47,"tsensorhvatbsel",12,11}
	};
	return reg;
}

	/// Comparator (in Service Slice) ATB bus select bits :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  Internal node vcmref is selected (vref to latch comparator)
	/// 010 =  Internal node vout_opamp is selected (positive di to latch comparator
	/// 011 =  Internal node vref is selected (reference voltage for comparator)
	/// 100 =  Internal node vp1 is selected (positive input of comparator)
	/// 101 =  Internal node vm1 is selected (negative input of comparator)
	/// 110 =  no input selected
	/// 111 =  no input selected
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::sscompatbctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{47,"sscompatbctrl",10,8}
	};
	return reg;
}

	/// Not used.
	/// TOP_FSM 2nd Pass Calibration Enable
	/// 0 =  disable TOP_FSM  2nd pass calibration
	/// 1 =  enable TOP_FSM   2nd pass calibration
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::topvcofsm2ndpassen(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{47,"topvcofsm2ndpassen",5,5}
	};
	return reg;
}

	/// TOP_FSM 1st Pass Itank calibration Bypass
	/// 0 =  TOP_FSM 1st pass includes itank calibration
	/// 1 =  TOP_FSM 1st pass itank calibration is bypassed
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::firstpassitankbypass(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{47,"firstpassitankbypass",4,4}
	};
	return reg;
}

	/// Not used 
	/// When CS_TRANS_MAX_FREQCAL=4/8/16, fddiff_cnt is accumulated 2/4/8 times for each sign changed freqcal points or top edge freqcal point (f31) or bottom edge freqcal point (f0)  
	/// 0 =  summing mode
	/// 1 =  Average mode
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::fddiffavemodesel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{47,"fddiffavemodesel",3,3}
	};
	return reg;
}

	/// Freqcal Preference Select
	/// 0 =  select lower freqcal number
	/// 1 =  select higher freqcal number
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::freqcalprefsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{47,"freqcalprefsel",2,2}
	};
	return reg;
}

	/// Bandsel Preference Select
	/// 0 =  select lower bandsel number
	/// 1 =  select higher bandsel number
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::bandselprefsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{47,"bandselprefsel",1,1}
	};
	return reg;
}

	/// Exit On Threshold (aka EOT) enable (also applicable in v100 mode)
	/// 0 = TOP_FSM continues to search for next freqcal point even if last freqcal point fd_diff_cnt is less than or eq to threshold
	/// 1 = enable TOP_FSM to exit when fd_diff less than or eq to threshold (2 points params will not be reported)
	/// 
	/// Re-purposed. Now used as bdsel force.
	/// 0 = bdsel force is OFF
	/// ;1 = bdsel force is ON.
	/// 
	/// When bdsel force is off, if two solutions (on two adjacent bands) or one solution and two edge points can be distinguished by their fd_diffs (i.e., the difference > 2) the solution with smaller fd_diff will be selected as the final solution; If not, then the solution on the lower band will be selected as the final solution if bdsel_pref is 0; Or, the solution on the higher band will be selected as the final solution if bdsel_pref is 1.
	/// 
	/// When bdsel force is ON, for the two solutions on two adjacent bands case, the solution on the higher band will be selected as the final solution; For the one solution and two edge points case, if any two can be distinguished by their fd_diffs (i.e., the difference > 2), between the solution and the edge point 1 (derived from the first run), the solution is always selected; between the solution and the edge point 2  (derived from the second run), the one which has a smaller fd_diff is selected. If any two cannot be distinguished by their fd_diffs (i.e., the difference > 2), always the one on the higher band is selected.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::exitonthreshold(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{47,"exitonthreshold",0,0}
	};
	return reg;
}

	/// DPM (Service Slice) ATB bus select bits :
	/// 000 =  Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 =  tielo is selected
	/// 010 =  Internal Vth detector mosdet_vgs (n/p) di is selected
	/// 011 =  Internal Poly resistor calibration/detection rpolydet_hvatb_output di is selected
	/// 100 =   Internal High-Pre comparator comp_atb_output is selected
	/// 101 =  Internal Temp sensor tsensor_hvatb_vbepnp di is selected
	/// 110-111 =  High Impedance
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssdpmatbsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{48,"ssdpmatbsel",15,13}
	};
	return reg;
}

	/// Vth process detector atb control signal:
	/// 000 = Disabled/High Impedance (NO INPUT SELECTED)
	/// 001 = vgsn  (N-type transistor) selected 
	/// 010 = vgsp  (P-type transistor) selected
	/// 011 to 111 = High Impedance
	///  
	///  See MOSDETMOSTYPESEL to choose  uLVT or SVT transistor
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::mosdetvgsatbctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{48,"mosdetvgsatbctrl",8,6}
	};
	return reg;
}

	/// ILO ATB bus control bits:
	/// 000: Disabled/High Impedance (NO INPUT SELECTED)
	/// 001: vgsn (N-type transistor) selected 
	/// 010: vgsp  (P-type transistor) selected
	/// 011 to 111: Disabled/High Impedance (NO INPUT SELECTED)
	/// 
	///  See MOSDETMOSTYPESEL to choose  uLVT or SVT transistor
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::mosdetoscatbctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{48,"mosdetoscatbctrl",5,3}
	};
	return reg;
}

	/// ATB bus selector, brings out internal voltages in the Rpoly detector/calibration for debug/testing purposes:
	/// 000: Disabled/High Impedance (NO INPUT SELECTED)
	/// 001: otbp output is selected
	/// 010: otbm output is selected
	/// 011: otbc output is selected
	/// 100: otbm_up output is selected
	/// 101: otbm_dn output is selected
	/// 110: internal indm voltage is selected
	/// 110: Disabled/High Impedance (NO INPUT SELECTED)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::rpolydethvatbctrl(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{48,"rpolydethvatbctrl",2,0}
	};
	return reg;
}

	/// Shared ADC/Comparator Pre Divider to generate 6.4MHz clock from lifeclk2dig to feed CSADCCLKDIV and CSCOMPCLKDIV  
	/// i.e,   6.4Mhz  = Lifeclk2dig  Mhz / (ADCCOMPCLKPREDIV + 1)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::adccompclkprediv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{49,"adccompclkprediv",14,8}
	};
	return reg;
}

	/// CS ADC Clock Frequency  selector (Input clock freq to the CS ADC Clock divider block should be  6.4Mhz set by  ADCCOMPCLKPREDIV)
	/// 000 =  25KHz 
	/// 001 =  50KHz
	/// 010 =  100KHz
	/// 011 =  200KHz
	/// 100 =  400KHz
	/// 101 =  800KHz
	/// 110 =  1.6MHz
	/// 111 =  3.2MHz
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csadcclkdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{49,"csadcclkdiv",7,5}
	};
	return reg;
}

	/// CS Comparator Clock  Frequency selector (Input clock freq to the CS Comparator Clock divider block should be 6.4Mhz set by  ADCCOMPCLKPREDIV) 
	/// 000 =  12.5KHz 
	/// 001 =  25KHz
	/// 010 =  50KHz
	/// 011 =  100KHz
	/// 100 =  200KHz
	/// 101 =  400KHz
	/// 110 =  800KHz
	/// 111 =  1.6MHz
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cscompclkdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{49,"cscompclkdiv",4,2}
	};
	return reg;
}

	/// CS DF DeadBand Select (each step ~ 6.25mV) : 
	/// 00 =  +/- 1 step
	/// 01 =  +/- 2 steps
	/// 10 =  +/- 3 steps
	/// 11 =  +/- 4 steps
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csdfdeadbandsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{49,"csdfdeadbandsel",1,0}
	};
	return reg;
}

	/// CS Decimation Factor Select :
	/// 00 =  256
	/// 01 =  512
	/// 10 =  1024
	/// 11 =  2048
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csdecmfactor(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{50,"csdecmfactor",15,14}
	};
	return reg;
}

	/// CS ADC Conversion Mode:
	/// 0 = Single shot measurement 
	/// 1 = Continuous measurement
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csadcconvmode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{50,"csadcconvmode",13,13}
	};
	return reg;
}

	/// CS Decimation Filter Order:
	/// 0 = Sync_1
	/// 1 = Sync_2
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csdforder(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{50,"csdforder",12,12}
	};
	return reg;
}

	/// CS Decimation Filter Reference Code: The Decimator Data is compared against this Reference code at the end of each measurement
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csdfrefcode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{50,"csdfrefcode",11,0}
	};
	return reg;
}

	/// CS Decimation Filter Ready: Set to 1 to indicate CSDFDATA and CSDFCOMPSTATUS are ready for reading
	/// - Single shot mode: set to 1 at the end of each cyle
	/// - Continuous mode: pulsing depend on CSADCCONVMODE[1]
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csdfrdy(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{51,"csdfrdy",15,15}
	};
	return reg;
}

	/// CS Decimation Filter Compare Status :
	/// 0 =  CSDFDATA smaller than  CSDFREFCODE
	/// 1 =  CSDFDATA greater or equal CSDFREFCODE
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csdfcompstatus(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{51,"csdfcompstatus",14,14}
	};
	return reg;
}

	/// CS Decimation Filter Compare Status DeadBand M :
	/// 0 =  CSDFDA greater or equal CSDFREFCODE - DeadBand
	/// 1 =  CSDFDATA smaller CSDFREFCODE - DeadBand
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csdfcompstatusdbm(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{51,"csdfcompstatusdbm",13,13}
	};
	return reg;
}

	/// CS Decimation Filter Compare Status DeadBand P : 
	/// 0 =  CSDFDA smaller or equal CSDFREFCODE + DeadBand
	/// 1 =  CSDFDATA greater CSDFREFCODE + DeadBand
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csdfcompstatusdbp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{51,"csdfcompstatusdbp",12,12}
	};
	return reg;
}

	/// CS Decimation Filter Data
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csdfdata(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{51,"csdfdata",11,0}
	};
	return reg;
}

	/// CS DF Auto Timer Value (Timer is always on, ADC_CLK@3.2MHz)
	/// 00:   6 ADC clock cycles   (1.87us     @ 3.2MHz)
	/// 01: 70 ADC clock cycles   (21.87us  @ 3.2MHz)
	/// 10: 166 ADC clock cycles (51.87us  @ 3.2MHz)
	/// 11: 326 ADC clock cycles (101.87us@ 3.2MHz)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::csdfautotimervalue(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{52,"csdfautotimervalue",11,10}
	};
	return reg;
}

	/// SS DF Auto Timer Value (Timer is always on, ADC_CLK@400KHz)
	/// 00:   6 ADC clock cycles   (15us     @ 400KHz)
	/// 01: 70 ADC clock cycles   (175us  @ 400KHz)
	/// 10: 166 ADC clock cycles (415us  @ 400KHz)
	/// 11: 326 ADC clock cycles (815us@ 400KHz)
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssdfautotimervalue(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{52,"ssdfautotimervalue",9,8}
	};
	return reg;
}

	/// SS (Service Slice)  ADC Clock Divider :
	/// 000 =  25KHz 
	/// 001 =  50KHz
	/// 010 =  100KHz
	/// 011 =  200KHz
	/// 100 =  400KHz
	/// 101 =  800KHz
	/// 110 =  1.6MHz
	/// 111 =  3.2MHz
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssadcclkdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{52,"ssadcclkdiv",7,5}
	};
	return reg;
}

	/// SS Comparator Clock Divider :
	/// 000 =  12.5KHz 
	/// 001 =  25KHz
	/// 010 =  50KHz
	/// 011 =  100KHz
	/// 100 =  200KHz
	/// 101 =  400KHz
	/// 110 =  800KHz
	/// 111 =  1.6MHz
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::sscompclkdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{52,"sscompclkdiv",4,2}
	};
	return reg;
}

	/// SS DF DeadBand Select (each step ~ 6.25mV) :
	/// 00 =  +/- 1 step
	/// 01 =  +/- 2 steps
	/// 10 =  +/- 3 steps
	/// 11 =  +/- 4 steps
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssdfdeadbandsel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{52,"ssdfdeadbandsel",1,0}
	};
	return reg;
}

	/// SS Decimation Factor Select :
	/// 00 =  256
	/// 01 =  512
	/// 10 =  1024
	/// 11 =  2048
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssdecmfactor(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{53,"ssdecmfactor",15,14}
	};
	return reg;
}

	/// SS ADC Conversion Mode :
	/// 0 =  Single shot measurement 
	/// 1 =  Continuous measurement
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssadcconvmode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{53,"ssadcconvmode",13,13}
	};
	return reg;
}

	/// SS Decimation Filter Order :
	/// 0 =  Sync_1
	/// 1 =  Sync_2
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssdforder(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{53,"ssdforder",12,12}
	};
	return reg;
}

	/// SS Decimation Filter Reference Code: The Decimator Data is compared against this Reference code at the end of each measurement
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssdfrefcode(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{53,"ssdfrefcode",11,0}
	};
	return reg;
}

	/// SS Decimation Filter Ready: Set to 1 to indicate SSDFDATA and SSDFCOMPSTATUS are ready for reading
	/// - Single shot mode: set to 1 at the end of each cyle
	/// - Continuous mode: pulsing depend on SSADCCONVMODE[1]
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssdfrdy(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{54,"ssdfrdy",15,15}
	};
	return reg;
}

	/// SS Decimation Filter Compare Status :
	/// 0 =  SSDFDATA smaller than  SSDFREFCODE
	/// 1 =  SSDFDATA greater or equal SSDFREFCODE
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssdfcompstatus(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{54,"ssdfcompstatus",14,14}
	};
	return reg;
}

	/// SS Decimation Filter Compare Status DeadBand M :
	/// 0 =  CSDFDATA  greater than or equal CSDFREFCODE - DeadBand
	/// 1 =  CSDFDATA   smaller than  CSDFREFCODE - DeadBand
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssdfcompstatusdbm(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{54,"ssdfcompstatusdbm",13,13}
	};
	return reg;
}

	/// SS Decimation Filter Compare Status DeadBand P : 
	/// 0 =  CSDFDATA  smaller than or equal CSDFREFCODE + DeadBand
	/// 1 =  CSDFDATA   greater than CSDFREFCODE + DeadBand
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssdfcompstatusdbp(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{54,"ssdfcompstatusdbp",12,12}
	};
	return reg;
}

	/// SS Decimation Filter Data
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssdfdata(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{54,"ssdfdata",11,0}
	};
	return reg;
}

	/// NOT USED IN V101
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ringvcorefclkdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{55,"ringvcorefclkdiv",15,8}
	};
	return reg;
}

	/// NOT USED IN V101
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ringvcofdclkdiv(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{55,"ringvcofdclkdiv",4,0}
	};
	return reg;
}

	/// DPM (Process /temperature monitoring) nmos corner status code shared with all Dataslices for optimizing performance
	/// 000 =  -3  sigma  Vth Nch fast corner
	/// 001 =  -2 sigma Vth Nch fast corner
	/// 010 =  -1 sigma Vth Nch fast corner
	/// 011 =  Typ Vth Nch corner
	/// 100 =  +1 sigma Vth Nch slow corner
	/// 101 =  +2 sigma Vth Nch slow corner
	/// 110 =  +3 sigma Vth Nch slow corner
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dpmnmoscnr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{56,"dpmnmoscnr",15,13}
	};
	return reg;
}

	/// DPM pmos corner status code shared with all Dataslices for optimizing performance
	/// 000 =  -3 sigma Vth Pch fast corner
	/// 001 =  -2 sigma Vth Pch fast corner
	/// 010 =  -1 sigma Vth Pch fast corner
	/// 011 =  Typ Vth Pch corner
	/// 100 =  +1 sigma Vth Pch slow corner
	/// 101 =  +2 sigma Vth Pch slow corner
	/// 110 =  +3 sigma Vth Pch slow corner
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dpmpmoscnr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{56,"dpmpmoscnr",12,10}
	};
	return reg;
}

	/// DPM cmos corner status code shared with all Dataslices for optimizing performance
	/// 000 =  -3 sigma Vth CMOS fast corner
	/// 001 =  -2 sigma Vth CMOS fast corner
	/// 010 =  -1 sigma Vth CMOS fast corner
	/// 011 =  Typ Vth CMOS corner
	/// 100 =  +1 sigma Vth CMOS slow corner
	/// 101 =  +2 sigma Vth CMOS slow corner
	/// 110 =  +3 sigma Vth CMOS slow corner
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dpmcmoscnr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{56,"dpmcmoscnr",9,7}
	};
	return reg;
}

	/// DPM temperature status code  shared with all Dataslices for optimizing performance
	/// 000 = temp is in the range  [-40 to 20] �C
	/// 001 = temp is in the range  [-20 to 0] �C
	/// 010 = temp is in the range  [0 to 20] �C
	/// 011 = temp is in the range  [20 to 40] �C
	/// 100 = temp is in the range  [40 to 60] �C
	/// 101  = temp is in the range [60 to 80] �C
	/// 110 = temp is in the range  [80 to 100] �C
	/// 111 = temp is in the range  [100 to 125] �C
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dpmtemperature(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{56,"dpmtemperature",6,4}
	};
	return reg;
}

	/// DPM Termination replica resistor calibration code shared with all Dataslices for optimizing performance
	/// 0000 =  Termination replica is open
	/// 0001 =  Highest resistance value 
	/// ..
	/// 1111 =  Lowest resistance value
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dpmrxtermcal(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{57,"dpmrxtermcal",13,10}
	};
	return reg;
}

	/// Clock slice spare output bits for dpm.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dpmspare(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{57,"dpmspare",9,6}
	};
	return reg;
}

	/// DPM rpoly resistor corner status code shared with all Dataslices for optimizing performance
	/// 00 = Fast resistor process
	/// 01 = Typical resistor process
	/// 10 = Slow resistor process
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dpmrpolycnr(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{57,"dpmrpolycnr",5,4}
	};
	return reg;
}

	/// Service slice spare output bits for dpm.
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::ssdpmspareout(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{57,"ssdpmspareout",3,0}
	};
	return reg;
}

	/// Start Calibration / Finetune task from CS_TOP_FSM
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cstopfsm_cal_start(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{58,"cstopfsm_cal_start",15,15}
	};
	return reg;
}

	/// DPM Finetune Enable : 
	/// 0 =  To STOP Continuous DPM once started
	/// 1 =  To Enable Continuous DPM.
	/// This bit must be set together with CSR58[15, 12:3] to finetune all the voltage regulators and to capture PLL0LVCCVCOCORE / PLL1LVCCVCOCORE voltages as well as monitor Temperature
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dpmfinetuneen(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{58,"dpmfinetuneen",14,14}
	};
	return reg;
}

	/// CS_TOP_FSM Calibration Task Select.  Set the following bits to 1 to calibrate :
	/// [0] =  ADC Bandgap Voltage Cal  
	/// [1] =  CS Comparator Vrefgen Cal 
	/// [2] =  RXTERM Cal  
	/// [3] =  PLL0 DLF VREG Cal  
	/// [4] =  PLL0 PLL VREG Cal
	/// [5] =  PLL0 CP VREF Cal
	/// [6] =  PLL0 VCODIV VREG Cal
	/// [7] =  PLL1 DLF VREG Cal
	/// [8] =  PLL1 PLL VREG Cal
	/// [9] =   PLL1 CP VREF Cal
	/// [10] = PLL1 VCODIV VREG Cal
	/// [11] =  PLL0 VCO Cal
	/// [12] =  PLL1 VCO Cal
	/// [13] =  No Selection
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cstopfsm_cal_task_sel(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{58,"cstopfsm_cal_task_sel",13,0}
	};
	return reg;
}

	/// CS_TOP_FSM Calibration Done.   set to 1 to indicate that all selected calibration tasks are completed
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cstopfsm_cal_done(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{59,"cstopfsm_cal_done",15,15}
	};
	return reg;
}

	/// DPM Finetune Ready (temprd, pll0lvccvcocore, pll1lvccvcocore being updated)
	/// Clear on Read
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::dpmfinetunerdy(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{59,"dpmfinetunerdy",14,14}
	};
	return reg;
}

	/// CS_TOP_FSM Calibration Task Status correspond to the  CSTOPFSM_CAL_TASK_SEL
	/// [0] =  ADC Bandgap Voltage Cal  
	/// [1] =  CS Comparator Vrefgen Cal 
	/// [2] =  RXTERM Cal  
	/// [3] =  PLL0 DLF VREG Cal  
	/// [4] =  PLL0 PLL VREG Cal
	/// [5] =  PLL0 CP VREF Cal
	/// [6] =  PLL0 VCODIV VREG Cal
	/// [7] =  PLL1 DLF VREG Cal
	/// [8] =  PLL1 PLL VREG Cal
	/// [9] =   PLL1 CP VREF Cal
	/// [10] = PLL1 VCODIV VREG Cal
	/// [11] =  PLL0 VCO Cal
	/// [12] =  PLL1 VCO Cal
	/// [13] =  Not used
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::cstopfsm_cal_task_status(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{59,"cstopfsm_cal_task_status",13,0}
	};
	return reg;
}

	/// PLL0 VREG PLL Comparator Vref  select bits :
	/// Setting = 400mV + (6.25mV x PLL0VREGPLLCOMPVREF)  000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vregpllcompvref(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{60,"pll0vregpllcompvref",11,6}
	};
	return reg;
}

	/// PLL1 VREG PLL Comparator Vref  select bits :
	/// Setting = 400mV + (6.25mV x PLL1VREGPLLCOMPVREF) 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vregpllcompvref(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{60,"pll1vregpllcompvref",5,0}
	};
	return reg;
}

	/// PLL0 VREG DLF Comparator Vref  select bits :
	/// Setting = 400mV + (6.25mV x PLL0VREGDLFCOMPVREF) 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vregdlfcompvref(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{61,"pll0vregdlfcompvref",11,6}
	};
	return reg;
}

	/// PLL1 VREG DLF Comparator Vref  select bits :
	/// Setting = 400mV + (6.25mV x PLL1VREGDLFCOMPVREF) 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vregdlfcompvref(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{61,"pll1vregdlfcompvref",5,0}
	};
	return reg;
}

	/// PLL0 VREG VCODIV Comparator Vref  select bits :
	/// Setting = 400mV+ (6.25mV x PLL0VREGVCODIVCOMPVREF)   
	/// 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vregvcodivcompvref(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{62,"pll0vregvcodivcompvref",11,6}
	};
	return reg;
}

	/// PLL1 VREG VCODIV Comparator Vref  select bits :
	/// Setting = 400mV+ (6.25mV x PLL1VREGVCODIVCOMPVREF)   
	/// 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vregvcodivcompvref(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{62,"pll1vregvcodivcompvref",5,0}
	};
	return reg;
}

	/// PLL0 CP REF Comparator Vref  select bits :
	/// Setting = 400mV + (6.25mV x PLL0VREGCPVREFCOMPVREF)                                 000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll0vregcpvrefcompvref(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{63,"pll0vregcpvrefcompvref",11,6}
	};
	return reg;
}

	/// PLL1 CP REF Comparator Vref  select bits :
	/// Setting = 400mV + (6.25mV PLL1VREGCPVREFCOMPVREF)                                000000 =  Vref=400mV
	/// 000001 =  Vref=406.25mV
	/// 000010 =  Vref=412.5mV
	/// ..
	/// 001111 =   Vref=493.75mV
	/// ..
	/// 111111 =  Vref=793.75mV
const T_REG_INFO_EX&
CS_clkRegs::_REG_INFO::pll1vregcpvrefcompvref(){
	const static T_REG_INFO_EX reg={CS_clkRegs::getInstance(),
		{63,"pll1vregcpvrefcompvref",5,0}
	};
	return reg;
}
bool
CS_clkRegs::_REG_INFO::get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos){
	reg_infos.clear();
	switch(csr){
		case 0:
			reg_infos.push_back(cspwrdb().reg_info);
			reg_infos.push_back(pll0refclksel().reg_info);
			reg_infos.push_back(pll0vcodivna().reg_info);
			reg_infos.push_back(pll0vcodivka().reg_info);
			reg_infos.push_back(pll0fbdivp().reg_info);
			reg_infos.push_back(pll0fbdivs().reg_info);
			break;
		case 1:
			reg_infos.push_back(pll0hsclkdistpwrdb().reg_info);
			reg_infos.push_back(pll0hsclkdivpwrdb().reg_info);
			reg_infos.push_back(pll0hsclkdiv().reg_info);
			reg_infos.push_back(pll0hsclkdistspare().reg_info);
			reg_infos.push_back(pll0refclkdiv().reg_info);
			reg_infos.push_back(pll0hsclkdivsouthpwrdb().reg_info);
			reg_infos.push_back(pll0mclkdiv40b().reg_info);
			reg_infos.push_back(pll0mclkdiv32b().reg_info);
			break;
		case 2:
			reg_infos.push_back(pll0lolthr().reg_info);
			reg_infos.push_back(pll0locthr().reg_info);
			reg_infos.push_back(pll0lolmode().reg_info);
			reg_infos.push_back(pll0outoflock().reg_info);
			reg_infos.push_back(pll0lossoflcvcoclk().reg_info);
			break;
		case 3:
			reg_infos.push_back(pll1refclksel().reg_info);
			reg_infos.push_back(pll1refclkdiv().reg_info);
			reg_infos.push_back(pll1vcodivna().reg_info);
			reg_infos.push_back(pll1vcodivka().reg_info);
			reg_infos.push_back(pll1fbdivp().reg_info);
			reg_infos.push_back(pll1fbdivs().reg_info);
			break;
		case 4:
			reg_infos.push_back(pll1hsclkdistpwrdb().reg_info);
			reg_infos.push_back(pll1hsclkdivpwrdb().reg_info);
			reg_infos.push_back(pll1hsclkdiv().reg_info);
			reg_infos.push_back(pll1hsclkdistspare().reg_info);
			reg_infos.push_back(pll1hsclkdivsouthpwrdb().reg_info);
			reg_infos.push_back(pll1mclkdiv40b().reg_info);
			reg_infos.push_back(pll1mclkdiv32b().reg_info);
			break;
		case 5:
			reg_infos.push_back(pll1lolthr().reg_info);
			reg_infos.push_back(pll1locthr().reg_info);
			reg_infos.push_back(pll1lolmode().reg_info);
			reg_infos.push_back(pll1outoflock().reg_info);
			reg_infos.push_back(pll1lossoflcvcoclk().reg_info);
			break;
		case 6:
			reg_infos.push_back(wordclk40bsel().reg_info);
			reg_infos.push_back(wordclk32bsel().reg_info);
			reg_infos.push_back(wordclksel().reg_info);
			reg_infos.push_back(coreclksel().reg_info);
			reg_infos.push_back(pll0hsclk2vcovregen().reg_info);
			reg_infos.push_back(lifeclk2digdiv().reg_info);
			reg_infos.push_back(wordclk2digdiv().reg_info);
			break;
		case 7:
			reg_infos.push_back(biascmupwrdb().reg_info);
			reg_infos.push_back(refclkdistpwrdb().reg_info);
			reg_infos.push_back(biascmutestmode().reg_info);
			reg_infos.push_back(adcpwrdb().reg_info);
			reg_infos.push_back(comppwrdb().reg_info);
			reg_infos.push_back(refclk0biasctrl().reg_info);
			reg_infos.push_back(refclk1biasctrl().reg_info);
			break;
		case 8:
			reg_infos.push_back(pll0pwrdb().reg_info);
			reg_infos.push_back(pll0dlfresfbpwrdb().reg_info);
			reg_infos.push_back(pll0dlfpwrdb().reg_info);
			reg_infos.push_back(pll0dlfshpwrdb().reg_info);
			reg_infos.push_back(pll0dlftstpwrdb().reg_info);
			reg_infos.push_back(pll0dlfcmfbpwrdb().reg_info);
			reg_infos.push_back(pll0dlfchoppwrdb().reg_info);
			reg_infos.push_back(pll0vregpllpwrdb().reg_info);
			reg_infos.push_back(pll0vregdlfpwrdb().reg_info);
			reg_infos.push_back(pll0vregvcodivpwrdb().reg_info);
			break;
		case 9:
			reg_infos.push_back(pll0pfdupdnswap().reg_info);
			reg_infos.push_back(pll0pfdforceup().reg_info);
			reg_infos.push_back(pll0pfdforcedn().reg_info);
			reg_infos.push_back(pll0pfdpulsewidth().reg_info);
			reg_infos.push_back(pll0cpcalrstb().reg_info);
			reg_infos.push_back(pll0cpcalrstlvl().reg_info);
			reg_infos.push_back(pll0cpvreflvl().reg_info);
			break;
		case 10:
			reg_infos.push_back(pll0cpintcrntsel().reg_info);
			reg_infos.push_back(pll0cppropcrntsel().reg_info);
			break;
		case 11:
			reg_infos.push_back(pll0dlfcintsel().reg_info);
			reg_infos.push_back(pll0dlfshdelsel().reg_info);
			reg_infos.push_back(pll0dlfseldtb().reg_info);
			reg_infos.push_back(pll0dlfshcapsel().reg_info);
			break;
		case 12:
			reg_infos.push_back(pll0vcobandsel().reg_info);
			reg_infos.push_back(pll0vcoregfilshorten().reg_info);
			reg_infos.push_back(pll0vcoswthhien().reg_info);
			reg_infos.push_back(pll0vcofreqcal().reg_info);
			reg_infos.push_back(pll0vcoitank().reg_info);
			break;
		case 13:
			reg_infos.push_back(pll0vcovref().reg_info);
			reg_infos.push_back(pll0vcodivspare().reg_info);
			reg_infos.push_back(pll0vcovregsel().reg_info);
			reg_infos.push_back(pll0vcodiv1p5ctrlcode().reg_info);
			reg_infos.push_back(pll0vcovregclksel().reg_info);
			reg_infos.push_back(pll0vcodpmctrl().reg_info);
			break;
		case 14:
			reg_infos.push_back(pll0vcopdpwrdb().reg_info);
			reg_infos.push_back(pll0vregplldpmen().reg_info);
			reg_infos.push_back(pll0vregpllbleedb().reg_info);
			reg_infos.push_back(pll0vregpllsel().reg_info);
			reg_infos.push_back(pll0vregdlfdpmen().reg_info);
			reg_infos.push_back(pll0vregdlfbleedb().reg_info);
			reg_infos.push_back(pll0vregdlfsel().reg_info);
			break;
		case 15:
			reg_infos.push_back(pll0vconewregbwsel().reg_info);
			reg_infos.push_back(pll0vcovtunebufpwrdb().reg_info);
			reg_infos.push_back(pll0vcocompenstart().reg_info);
			reg_infos.push_back(pll0vcocompenpwrdb().reg_info);
			reg_infos.push_back(pll0vcocompenbw().reg_info);
			reg_infos.push_back(pll0itankcalmode().reg_info);
			reg_infos.push_back(pll0freqcalmode().reg_info);
			reg_infos.push_back(pll0vregvcodivdpmen().reg_info);
			reg_infos.push_back(pll0vregvcodivbleedb().reg_info);
			reg_infos.push_back(pll0vregvcodivsel().reg_info);
			break;
		case 16:
			reg_infos.push_back(pll0spare().reg_info);
			break;
		case 17:
			reg_infos.push_back(pll1pwrdb().reg_info);
			reg_infos.push_back(pll1dlfresfbpwrdb().reg_info);
			reg_infos.push_back(pll1dlfpwrdb().reg_info);
			reg_infos.push_back(pll1dlfshpwrdb().reg_info);
			reg_infos.push_back(pll1dlftstpwrdb().reg_info);
			reg_infos.push_back(pll1dlfcmfbpwrdb().reg_info);
			reg_infos.push_back(pll1dlfchoppwrdb().reg_info);
			reg_infos.push_back(pll1vregpllpwrdb().reg_info);
			reg_infos.push_back(pll1vregdlfpwrdb().reg_info);
			reg_infos.push_back(pll1vregvcodivpwrdb().reg_info);
			break;
		case 18:
			reg_infos.push_back(pll1pfdupdnswap().reg_info);
			reg_infos.push_back(pll1pfdforceup().reg_info);
			reg_infos.push_back(pll1pfdforcedn().reg_info);
			reg_infos.push_back(pll1pfdpulsewidth().reg_info);
			reg_infos.push_back(pll1cpcalrstb().reg_info);
			reg_infos.push_back(pll1cpcalrstlvl().reg_info);
			reg_infos.push_back(pll1cpvreflvl().reg_info);
			break;
		case 19:
			reg_infos.push_back(pll1cpintcrntsel().reg_info);
			reg_infos.push_back(pll1cppropcrntsel().reg_info);
			break;
		case 20:
			reg_infos.push_back(pll1dlfcintsel().reg_info);
			reg_infos.push_back(pll1dlfshdelsel().reg_info);
			reg_infos.push_back(pll1dlfseldtb().reg_info);
			reg_infos.push_back(pll1dlfshcapsel().reg_info);
			break;
		case 21:
			reg_infos.push_back(pll1vcobandsel().reg_info);
			reg_infos.push_back(pll1vcoregfilshorten().reg_info);
			reg_infos.push_back(pll1vcoswthhien().reg_info);
			reg_infos.push_back(pll1vcofreqcal().reg_info);
			reg_infos.push_back(pll1vcoitank().reg_info);
			break;
		case 22:
			reg_infos.push_back(pll1vcovref().reg_info);
			reg_infos.push_back(pll1vcodivspare().reg_info);
			reg_infos.push_back(pll1vcovregsel().reg_info);
			reg_infos.push_back(pll1vcodiv1p5ctrlcode().reg_info);
			reg_infos.push_back(pll1vcovregclksel().reg_info);
			reg_infos.push_back(pll1vcodpmctrl().reg_info);
			break;
		case 23:
			reg_infos.push_back(pll1vcopdpwrdb().reg_info);
			reg_infos.push_back(pll1vregplldpmen().reg_info);
			reg_infos.push_back(pll1vregpllbleedb().reg_info);
			reg_infos.push_back(pll1vregpllsel().reg_info);
			reg_infos.push_back(pll1vregdlfdpmen().reg_info);
			reg_infos.push_back(pll1vregdlfbleedb().reg_info);
			reg_infos.push_back(pll1vregdlfsel().reg_info);
			break;
		case 24:
			reg_infos.push_back(pll1vconewregbwsel().reg_info);
			reg_infos.push_back(pll1vcovtunebufpwrdb().reg_info);
			reg_infos.push_back(pll1vcocompenstart().reg_info);
			reg_infos.push_back(pll1vcocompenpwrdb().reg_info);
			reg_infos.push_back(pll1vcocompenbw().reg_info);
			reg_infos.push_back(pll1itankcalmode().reg_info);
			reg_infos.push_back(pll1freqcalmode().reg_info);
			reg_infos.push_back(pll1vregvcodivdpmen().reg_info);
			reg_infos.push_back(pll1vregvcodivbleedb().reg_info);
			reg_infos.push_back(pll1vregvcodivsel().reg_info);
			break;
		case 25:
			reg_infos.push_back(pll1spare().reg_info);
			break;
		case 26:
			reg_infos.push_back(adcrstb().reg_info);
			reg_infos.push_back(adcabsmeasen().reg_info);
			reg_infos.push_back(adctsten().reg_info);
			reg_infos.push_back(adcvcmctrl().reg_info);
			reg_infos.push_back(cstopfsmcalspare().reg_info);
			reg_infos.push_back(dpminitsettingen().reg_info);
			reg_infos.push_back(cstopfsmcalclr().reg_info);
			reg_infos.push_back(misccalforcedefault().reg_info);
			reg_infos.push_back(dpmdetdone().reg_info);
			reg_infos.push_back(dpmdettasksel().reg_info);
			break;
		case 27:
			reg_infos.push_back(compmodesel().reg_info);
			reg_infos.push_back(compcalmuxctrl().reg_info);
			reg_infos.push_back(compvrefsel().reg_info);
			reg_infos.push_back(overrideoffset().reg_info);
			reg_infos.push_back(vrefgenoffset().reg_info);
			break;
		case 28:
			reg_infos.push_back(topvcofsmbypass().reg_info);
			reg_infos.push_back(lcvcocalsel().reg_info);
			reg_infos.push_back(lcvcocalctrl().reg_info);
			reg_infos.push_back(cspll0pwrseqdone().reg_info);
			reg_infos.push_back(cspll1pwrseqdone().reg_info);
			reg_infos.push_back(cspwrseqfsmclr().reg_info);
			reg_infos.push_back(csfwoverwrite().reg_info);
			reg_infos.push_back(cscalmode().reg_info);
			reg_infos.push_back(csadccompsel().reg_info);
			reg_infos.push_back(lcvcocaldone().reg_info);
			reg_infos.push_back(lcvcocalerr().reg_info);
			reg_infos.push_back(lcvcocalstatus().reg_info);
			break;
		case 29:
			reg_infos.push_back(atbfinalsel().reg_info);
			reg_infos.push_back(csatbtopsel().reg_info);
			reg_infos.push_back(csatbspare().reg_info);
			reg_infos.push_back(biasatbsel().reg_info);
			reg_infos.push_back(compatbctrl().reg_info);
			break;
		case 30:
			reg_infos.push_back(pll0atbplltopsel().reg_info);
			reg_infos.push_back(pll0atbpllctrl().reg_info);
			reg_infos.push_back(pll0atbvcoctrl().reg_info);
			reg_infos.push_back(pll0adcvcoctrl().reg_info);
			reg_infos.push_back(pll0dtbout().reg_info);
			break;
		case 31:
			reg_infos.push_back(pll0atbvregsel().reg_info);
			reg_infos.push_back(pll0atbvregpllctrl().reg_info);
			reg_infos.push_back(pll0atbvregdlfctrl().reg_info);
			reg_infos.push_back(pll0atbvregvcodivctrl().reg_info);
			break;
		case 32:
			reg_infos.push_back(pll1atbplltopsel().reg_info);
			reg_infos.push_back(pll1atbpllctrl().reg_info);
			reg_infos.push_back(pll1atbvcoctrl().reg_info);
			reg_infos.push_back(pll1adcvcoctrl().reg_info);
			reg_infos.push_back(pll1dtbout().reg_info);
			break;
		case 33:
			reg_infos.push_back(pll1atbvregsel().reg_info);
			reg_infos.push_back(pll1atbvregpllctrl().reg_info);
			reg_infos.push_back(pll1atbvregdlfctrl().reg_info);
			reg_infos.push_back(pll1atbvregvcodivctrl().reg_info);
			break;
		case 34:
			reg_infos.push_back(sspwrdb().reg_info);
			reg_infos.push_back(ssrefclk0pwrdb().reg_info);
			reg_infos.push_back(ssrefclk1pwrdb().reg_info);
			reg_infos.push_back(ssrefclk0cmldivpwrdb().reg_info);
			reg_infos.push_back(ssrefclk1cmldivpwrdb().reg_info);
			reg_infos.push_back(ssrefclk0div2sel().reg_info);
			reg_infos.push_back(ssrefclk1div2sel().reg_info);
			reg_infos.push_back(sscmosrefclksel().reg_info);
			reg_infos.push_back(ssrefclk0biasctrl().reg_info);
			reg_infos.push_back(ssrefclk1biasctrl().reg_info);
			reg_infos.push_back(ssrefclk0distbiasctrl().reg_info);
			reg_infos.push_back(ssrefclk1distbiasctrl().reg_info);
			break;
		case 35:
			reg_infos.push_back(biasmstricvpwrdb().reg_info);
			reg_infos.push_back(biasmstriccpwrdb().reg_info);
			reg_infos.push_back(biasmstriptatpwrdb().reg_info);
			reg_infos.push_back(vbgpwrdb().reg_info);
			reg_infos.push_back(vptatpwrdb().reg_info);
			reg_infos.push_back(ssadcpwrdb().reg_info);
			reg_infos.push_back(sscomppwrdb().reg_info);
			reg_infos.push_back(sscompvrefpwrdb().reg_info);
			reg_infos.push_back(mosdetidacpwrdb().reg_info);
			reg_infos.push_back(mosdetcml2cmospwrdb().reg_info);
			break;
		case 36:
			reg_infos.push_back(bg600mvlvccresdiv().reg_info);
			reg_infos.push_back(bgbufsel().reg_info);
			reg_infos.push_back(bgbufcalen().reg_info);
			reg_infos.push_back(bgbufofst().reg_info);
			reg_infos.push_back(bgbypass().reg_info);
			break;
		case 37:
			reg_infos.push_back(bgbufcaltrig().reg_info);
			reg_infos.push_back(vbgrstb().reg_info);
			reg_infos.push_back(vbgbypassb().reg_info);
			reg_infos.push_back(vbgmode().reg_info);
			reg_infos.push_back(vbgchopclkmode().reg_info);
			reg_infos.push_back(vbgdemclkmode().reg_info);
			reg_infos.push_back(vbgenchop().reg_info);
			reg_infos.push_back(vbgendem().reg_info);
			reg_infos.push_back(vbgreflvl().reg_info);
			break;
		case 38:
			reg_infos.push_back(vptatrstb().reg_info);
			reg_infos.push_back(vptatbypassb().reg_info);
			reg_infos.push_back(vptatmode().reg_info);
			reg_infos.push_back(vptatchopclkmode().reg_info);
			reg_infos.push_back(vptatdemclkmode().reg_info);
			reg_infos.push_back(vptatenchop().reg_info);
			reg_infos.push_back(vptatendem().reg_info);
			reg_infos.push_back(vptatreflvl().reg_info);
			break;
		case 39:
			reg_infos.push_back(ssadcrstb().reg_info);
			reg_infos.push_back(ssadcabsmeasen().reg_info);
			reg_infos.push_back(ssadctsten().reg_info);
			reg_infos.push_back(ssadcvcmctrl().reg_info);
			reg_infos.push_back(ssadcinputsel().reg_info);
			reg_infos.push_back(tsensoren().reg_info);
			reg_infos.push_back(tsensorcstemp().reg_info);
			break;
		case 40:
			reg_infos.push_back(sscompmodesel().reg_info);
			reg_infos.push_back(sscompvinmsel().reg_info);
			reg_infos.push_back(sscompvinpsel().reg_info);
			reg_infos.push_back(sscompvrefsel().reg_info);
			reg_infos.push_back(sscompstatus().reg_info);
			break;
		case 41:
			reg_infos.push_back(mosdeten().reg_info);
			reg_infos.push_back(mosdetmostypesel().reg_info);
			reg_infos.push_back(mosdetvcocalen().reg_info);
			reg_infos.push_back(mosdetioscptune().reg_info);
			reg_infos.push_back(mosdetioscdacofst().reg_info);
			reg_infos.push_back(mosdetioscdaccal().reg_info);
			break;
		case 42:
			reg_infos.push_back(mosdetpsel().reg_info);
			reg_infos.push_back(mosdets1sel().reg_info);
			reg_infos.push_back(mosdets2sel().reg_info);
			reg_infos.push_back(mosdetiosccrosstune().reg_info);
			reg_infos.push_back(mosdetoscdiv().reg_info);
			break;
		case 43:
			reg_infos.push_back(mosdetcsnmoscnr().reg_info);
			reg_infos.push_back(mosdetcspmoscnr().reg_info);
			reg_infos.push_back(mosdetcscmoscnr().reg_info);
			reg_infos.push_back(sschopdemclkdiv().reg_info);
			break;
		case 44:
			reg_infos.push_back(rpolydetcalsel().reg_info);
			reg_infos.push_back(rpolydethvrxtermcalen().reg_info);
			reg_infos.push_back(rpolydetcsrxtermcal().reg_info);
			reg_infos.push_back(rpolydetcsrpolycnr().reg_info);
			reg_infos.push_back(ssdpmsparein().reg_info);
			break;
		case 45:
			reg_infos.push_back(ssspare().reg_info);
			break;
		case 46:
			reg_infos.push_back(ssatbsel().reg_info);
			reg_infos.push_back(refclkreceiveratbsel().reg_info);
			reg_infos.push_back(biasmstratbsel().reg_info);
			break;
		case 47:
			reg_infos.push_back(tsensorhvatbsel().reg_info);
			reg_infos.push_back(sscompatbctrl().reg_info);
			reg_infos.push_back(topvcofsm2ndpassen().reg_info);
			reg_infos.push_back(firstpassitankbypass().reg_info);
			reg_infos.push_back(fddiffavemodesel().reg_info);
			reg_infos.push_back(freqcalprefsel().reg_info);
			reg_infos.push_back(bandselprefsel().reg_info);
			reg_infos.push_back(exitonthreshold().reg_info);
			break;
		case 48:
			reg_infos.push_back(ssdpmatbsel().reg_info);
			reg_infos.push_back(mosdetvgsatbctrl().reg_info);
			reg_infos.push_back(mosdetoscatbctrl().reg_info);
			reg_infos.push_back(rpolydethvatbctrl().reg_info);
			break;
		case 49:
			reg_infos.push_back(adccompclkprediv().reg_info);
			reg_infos.push_back(csadcclkdiv().reg_info);
			reg_infos.push_back(cscompclkdiv().reg_info);
			reg_infos.push_back(csdfdeadbandsel().reg_info);
			break;
		case 50:
			reg_infos.push_back(csdecmfactor().reg_info);
			reg_infos.push_back(csadcconvmode().reg_info);
			reg_infos.push_back(csdforder().reg_info);
			reg_infos.push_back(csdfrefcode().reg_info);
			break;
		case 51:
			reg_infos.push_back(csdfrdy().reg_info);
			reg_infos.push_back(csdfcompstatus().reg_info);
			reg_infos.push_back(csdfcompstatusdbm().reg_info);
			reg_infos.push_back(csdfcompstatusdbp().reg_info);
			reg_infos.push_back(csdfdata().reg_info);
			break;
		case 52:
			reg_infos.push_back(csdfautotimervalue().reg_info);
			reg_infos.push_back(ssdfautotimervalue().reg_info);
			reg_infos.push_back(ssadcclkdiv().reg_info);
			reg_infos.push_back(sscompclkdiv().reg_info);
			reg_infos.push_back(ssdfdeadbandsel().reg_info);
			break;
		case 53:
			reg_infos.push_back(ssdecmfactor().reg_info);
			reg_infos.push_back(ssadcconvmode().reg_info);
			reg_infos.push_back(ssdforder().reg_info);
			reg_infos.push_back(ssdfrefcode().reg_info);
			break;
		case 54:
			reg_infos.push_back(ssdfrdy().reg_info);
			reg_infos.push_back(ssdfcompstatus().reg_info);
			reg_infos.push_back(ssdfcompstatusdbm().reg_info);
			reg_infos.push_back(ssdfcompstatusdbp().reg_info);
			reg_infos.push_back(ssdfdata().reg_info);
			break;
		case 55:
			reg_infos.push_back(ringvcorefclkdiv().reg_info);
			reg_infos.push_back(ringvcofdclkdiv().reg_info);
			break;
		case 56:
			reg_infos.push_back(dpmnmoscnr().reg_info);
			reg_infos.push_back(dpmpmoscnr().reg_info);
			reg_infos.push_back(dpmcmoscnr().reg_info);
			reg_infos.push_back(dpmtemperature().reg_info);
			break;
		case 57:
			reg_infos.push_back(dpmrxtermcal().reg_info);
			reg_infos.push_back(dpmspare().reg_info);
			reg_infos.push_back(dpmrpolycnr().reg_info);
			reg_infos.push_back(ssdpmspareout().reg_info);
			break;
		case 58:
			reg_infos.push_back(cstopfsm_cal_start().reg_info);
			reg_infos.push_back(dpmfinetuneen().reg_info);
			reg_infos.push_back(cstopfsm_cal_task_sel().reg_info);
			break;
		case 59:
			reg_infos.push_back(cstopfsm_cal_done().reg_info);
			reg_infos.push_back(dpmfinetunerdy().reg_info);
			reg_infos.push_back(cstopfsm_cal_task_status().reg_info);
			break;
		case 60:
			reg_infos.push_back(pll0vregpllcompvref().reg_info);
			reg_infos.push_back(pll1vregpllcompvref().reg_info);
			break;
		case 61:
			reg_infos.push_back(pll0vregdlfcompvref().reg_info);
			reg_infos.push_back(pll1vregdlfcompvref().reg_info);
			break;
		case 62:
			reg_infos.push_back(pll0vregvcodivcompvref().reg_info);
			reg_infos.push_back(pll1vregvcodivcompvref().reg_info);
			break;
		case 63:
			reg_infos.push_back(pll0vregcpvrefcompvref().reg_info);
			reg_infos.push_back(pll1vregcpvrefcompvref().reg_info);
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
CS_clkRegs::setpll0refclksel(uint val){
	fill_csr_bits(val,REG_INFO.pll0refclksel());	//CSR0[14:14]
	return *this;
}
uint
CS_clkRegs::getpll0refclksel(){
	return get_csr_bits(REG_INFO.pll0refclksel());	//CSR0[14:14]
}

CS_clkRegs&
CS_clkRegs::setpll0vcodivna(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcodivna());	//CSR0[12:11]
	return *this;
}
uint
CS_clkRegs::getpll0vcodivna(){
	return get_csr_bits(REG_INFO.pll0vcodivna());	//CSR0[12:11]
}

CS_clkRegs&
CS_clkRegs::setpll0vcodivka(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcodivka());	//CSR0[10:9]
	return *this;
}
uint
CS_clkRegs::getpll0vcodivka(){
	return get_csr_bits(REG_INFO.pll0vcodivka());	//CSR0[10:9]
}

CS_clkRegs&
CS_clkRegs::setpll0fbdivp(uint val){
	fill_csr_bits(val,REG_INFO.pll0fbdivp());	//CSR0[8:4]
	return *this;
}
uint
CS_clkRegs::getpll0fbdivp(){
	return get_csr_bits(REG_INFO.pll0fbdivp());	//CSR0[8:4]
}

CS_clkRegs&
CS_clkRegs::setpll0fbdivs(uint val){
	fill_csr_bits(val,REG_INFO.pll0fbdivs());	//CSR0[3:0]
	return *this;
}
uint
CS_clkRegs::getpll0fbdivs(){
	return get_csr_bits(REG_INFO.pll0fbdivs());	//CSR0[3:0]
}

CS_clkRegs&
CS_clkRegs::setpll0hsclkdistpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll0hsclkdistpwrdb());	//CSR1[15:15]
	return *this;
}
uint
CS_clkRegs::getpll0hsclkdistpwrdb(){
	return get_csr_bits(REG_INFO.pll0hsclkdistpwrdb());	//CSR1[15:15]
}

CS_clkRegs&
CS_clkRegs::setpll0hsclkdivpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll0hsclkdivpwrdb());	//CSR1[14:14]
	return *this;
}
uint
CS_clkRegs::getpll0hsclkdivpwrdb(){
	return get_csr_bits(REG_INFO.pll0hsclkdivpwrdb());	//CSR1[14:14]
}

CS_clkRegs&
CS_clkRegs::setpll0hsclkdiv(uint val){
	fill_csr_bits(val,REG_INFO.pll0hsclkdiv());	//CSR1[13:10]
	return *this;
}
uint
CS_clkRegs::getpll0hsclkdiv(){
	return get_csr_bits(REG_INFO.pll0hsclkdiv());	//CSR1[13:10]
}

CS_clkRegs&
CS_clkRegs::setpll0hsclkdistspare(uint val){
	fill_csr_bits(val,REG_INFO.pll0hsclkdistspare());	//CSR1[9:7]
	return *this;
}
uint
CS_clkRegs::getpll0hsclkdistspare(){
	return get_csr_bits(REG_INFO.pll0hsclkdistspare());	//CSR1[9:7]
}

CS_clkRegs&
CS_clkRegs::setpll0refclkdiv(uint val){
	fill_csr_bits(val,REG_INFO.pll0refclkdiv());	//CSR1[6:5]
	return *this;
}
uint
CS_clkRegs::getpll0refclkdiv(){
	return get_csr_bits(REG_INFO.pll0refclkdiv());	//CSR1[6:5]
}

CS_clkRegs&
CS_clkRegs::setpll0hsclkdivsouthpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll0hsclkdivsouthpwrdb());	//CSR1[4:4]
	return *this;
}
uint
CS_clkRegs::getpll0hsclkdivsouthpwrdb(){
	return get_csr_bits(REG_INFO.pll0hsclkdivsouthpwrdb());	//CSR1[4:4]
}

CS_clkRegs&
CS_clkRegs::setpll0mclkdiv40b(uint val){
	fill_csr_bits(val,REG_INFO.pll0mclkdiv40b());	//CSR1[3:2]
	return *this;
}
uint
CS_clkRegs::getpll0mclkdiv40b(){
	return get_csr_bits(REG_INFO.pll0mclkdiv40b());	//CSR1[3:2]
}

CS_clkRegs&
CS_clkRegs::setpll0mclkdiv32b(uint val){
	fill_csr_bits(val,REG_INFO.pll0mclkdiv32b());	//CSR1[1:0]
	return *this;
}
uint
CS_clkRegs::getpll0mclkdiv32b(){
	return get_csr_bits(REG_INFO.pll0mclkdiv32b());	//CSR1[1:0]
}

CS_clkRegs&
CS_clkRegs::setpll0lolthr(uint val){
	fill_csr_bits(val,REG_INFO.pll0lolthr());	//CSR2[10:6]
	return *this;
}
uint
CS_clkRegs::getpll0lolthr(){
	return get_csr_bits(REG_INFO.pll0lolthr());	//CSR2[10:6]
}

CS_clkRegs&
CS_clkRegs::setpll0locthr(uint val){
	fill_csr_bits(val,REG_INFO.pll0locthr());	//CSR2[5:3]
	return *this;
}
uint
CS_clkRegs::getpll0locthr(){
	return get_csr_bits(REG_INFO.pll0locthr());	//CSR2[5:3]
}

CS_clkRegs&
CS_clkRegs::setpll0lolmode(uint val){
	fill_csr_bits(val,REG_INFO.pll0lolmode());	//CSR2[2:2]
	return *this;
}
uint
CS_clkRegs::getpll0lolmode(){
	return get_csr_bits(REG_INFO.pll0lolmode());	//CSR2[2:2]
}

uint
CS_clkRegs::getpll0outoflock(){
	return get_csr_bits(REG_INFO.pll0outoflock());	//CSR2[1:1]
}

uint
CS_clkRegs::getpll0lossoflcvcoclk(){
	return get_csr_bits(REG_INFO.pll0lossoflcvcoclk());	//CSR2[0:0]
}

CS_clkRegs&
CS_clkRegs::setpll1refclksel(uint val){
	fill_csr_bits(val,REG_INFO.pll1refclksel());	//CSR3[15:15]
	return *this;
}
uint
CS_clkRegs::getpll1refclksel(){
	return get_csr_bits(REG_INFO.pll1refclksel());	//CSR3[15:15]
}

CS_clkRegs&
CS_clkRegs::setpll1refclkdiv(uint val){
	fill_csr_bits(val,REG_INFO.pll1refclkdiv());	//CSR3[14:13]
	return *this;
}
uint
CS_clkRegs::getpll1refclkdiv(){
	return get_csr_bits(REG_INFO.pll1refclkdiv());	//CSR3[14:13]
}

CS_clkRegs&
CS_clkRegs::setpll1vcodivna(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcodivna());	//CSR3[12:11]
	return *this;
}
uint
CS_clkRegs::getpll1vcodivna(){
	return get_csr_bits(REG_INFO.pll1vcodivna());	//CSR3[12:11]
}

CS_clkRegs&
CS_clkRegs::setpll1vcodivka(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcodivka());	//CSR3[10:9]
	return *this;
}
uint
CS_clkRegs::getpll1vcodivka(){
	return get_csr_bits(REG_INFO.pll1vcodivka());	//CSR3[10:9]
}

CS_clkRegs&
CS_clkRegs::setpll1fbdivp(uint val){
	fill_csr_bits(val,REG_INFO.pll1fbdivp());	//CSR3[8:4]
	return *this;
}
uint
CS_clkRegs::getpll1fbdivp(){
	return get_csr_bits(REG_INFO.pll1fbdivp());	//CSR3[8:4]
}

CS_clkRegs&
CS_clkRegs::setpll1fbdivs(uint val){
	fill_csr_bits(val,REG_INFO.pll1fbdivs());	//CSR3[3:0]
	return *this;
}
uint
CS_clkRegs::getpll1fbdivs(){
	return get_csr_bits(REG_INFO.pll1fbdivs());	//CSR3[3:0]
}

CS_clkRegs&
CS_clkRegs::setpll1hsclkdistpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll1hsclkdistpwrdb());	//CSR4[15:15]
	return *this;
}
uint
CS_clkRegs::getpll1hsclkdistpwrdb(){
	return get_csr_bits(REG_INFO.pll1hsclkdistpwrdb());	//CSR4[15:15]
}

CS_clkRegs&
CS_clkRegs::setpll1hsclkdivpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll1hsclkdivpwrdb());	//CSR4[14:14]
	return *this;
}
uint
CS_clkRegs::getpll1hsclkdivpwrdb(){
	return get_csr_bits(REG_INFO.pll1hsclkdivpwrdb());	//CSR4[14:14]
}

CS_clkRegs&
CS_clkRegs::setpll1hsclkdiv(uint val){
	fill_csr_bits(val,REG_INFO.pll1hsclkdiv());	//CSR4[13:10]
	return *this;
}
uint
CS_clkRegs::getpll1hsclkdiv(){
	return get_csr_bits(REG_INFO.pll1hsclkdiv());	//CSR4[13:10]
}

CS_clkRegs&
CS_clkRegs::setpll1hsclkdistspare(uint val){
	fill_csr_bits(val,REG_INFO.pll1hsclkdistspare());	//CSR4[9:7]
	return *this;
}
uint
CS_clkRegs::getpll1hsclkdistspare(){
	return get_csr_bits(REG_INFO.pll1hsclkdistspare());	//CSR4[9:7]
}

CS_clkRegs&
CS_clkRegs::setpll1hsclkdivsouthpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll1hsclkdivsouthpwrdb());	//CSR4[4:4]
	return *this;
}
uint
CS_clkRegs::getpll1hsclkdivsouthpwrdb(){
	return get_csr_bits(REG_INFO.pll1hsclkdivsouthpwrdb());	//CSR4[4:4]
}

CS_clkRegs&
CS_clkRegs::setpll1mclkdiv40b(uint val){
	fill_csr_bits(val,REG_INFO.pll1mclkdiv40b());	//CSR4[3:2]
	return *this;
}
uint
CS_clkRegs::getpll1mclkdiv40b(){
	return get_csr_bits(REG_INFO.pll1mclkdiv40b());	//CSR4[3:2]
}

CS_clkRegs&
CS_clkRegs::setpll1mclkdiv32b(uint val){
	fill_csr_bits(val,REG_INFO.pll1mclkdiv32b());	//CSR4[1:0]
	return *this;
}
uint
CS_clkRegs::getpll1mclkdiv32b(){
	return get_csr_bits(REG_INFO.pll1mclkdiv32b());	//CSR4[1:0]
}

CS_clkRegs&
CS_clkRegs::setpll1lolthr(uint val){
	fill_csr_bits(val,REG_INFO.pll1lolthr());	//CSR5[10:6]
	return *this;
}
uint
CS_clkRegs::getpll1lolthr(){
	return get_csr_bits(REG_INFO.pll1lolthr());	//CSR5[10:6]
}

CS_clkRegs&
CS_clkRegs::setpll1locthr(uint val){
	fill_csr_bits(val,REG_INFO.pll1locthr());	//CSR5[5:3]
	return *this;
}
uint
CS_clkRegs::getpll1locthr(){
	return get_csr_bits(REG_INFO.pll1locthr());	//CSR5[5:3]
}

CS_clkRegs&
CS_clkRegs::setpll1lolmode(uint val){
	fill_csr_bits(val,REG_INFO.pll1lolmode());	//CSR5[2:2]
	return *this;
}
uint
CS_clkRegs::getpll1lolmode(){
	return get_csr_bits(REG_INFO.pll1lolmode());	//CSR5[2:2]
}

uint
CS_clkRegs::getpll1outoflock(){
	return get_csr_bits(REG_INFO.pll1outoflock());	//CSR5[1:1]
}

uint
CS_clkRegs::getpll1lossoflcvcoclk(){
	return get_csr_bits(REG_INFO.pll1lossoflcvcoclk());	//CSR5[0:0]
}

CS_clkRegs&
CS_clkRegs::setwordclk40bsel(uint val){
	fill_csr_bits(val,REG_INFO.wordclk40bsel());	//CSR6[15:15]
	return *this;
}
uint
CS_clkRegs::getwordclk40bsel(){
	return get_csr_bits(REG_INFO.wordclk40bsel());	//CSR6[15:15]
}

CS_clkRegs&
CS_clkRegs::setwordclk32bsel(uint val){
	fill_csr_bits(val,REG_INFO.wordclk32bsel());	//CSR6[14:14]
	return *this;
}
uint
CS_clkRegs::getwordclk32bsel(){
	return get_csr_bits(REG_INFO.wordclk32bsel());	//CSR6[14:14]
}

CS_clkRegs&
CS_clkRegs::setwordclksel(uint val){
	fill_csr_bits(val,REG_INFO.wordclksel());	//CSR6[13:13]
	return *this;
}
uint
CS_clkRegs::getwordclksel(){
	return get_csr_bits(REG_INFO.wordclksel());	//CSR6[13:13]
}

CS_clkRegs&
CS_clkRegs::setcoreclksel(uint val){
	fill_csr_bits(val,REG_INFO.coreclksel());	//CSR6[12:12]
	return *this;
}
uint
CS_clkRegs::getcoreclksel(){
	return get_csr_bits(REG_INFO.coreclksel());	//CSR6[12:12]
}

CS_clkRegs&
CS_clkRegs::setpll0hsclk2vcovregen(uint val){
	fill_csr_bits(val,REG_INFO.pll0hsclk2vcovregen());	//CSR6[4:4]
	return *this;
}
uint
CS_clkRegs::getpll0hsclk2vcovregen(){
	return get_csr_bits(REG_INFO.pll0hsclk2vcovregen());	//CSR6[4:4]
}

CS_clkRegs&
CS_clkRegs::setlifeclk2digdiv(uint val){
	fill_csr_bits(val,REG_INFO.lifeclk2digdiv());	//CSR6[3:2]
	return *this;
}
uint
CS_clkRegs::getlifeclk2digdiv(){
	return get_csr_bits(REG_INFO.lifeclk2digdiv());	//CSR6[3:2]
}

CS_clkRegs&
CS_clkRegs::setwordclk2digdiv(uint val){
	fill_csr_bits(val,REG_INFO.wordclk2digdiv());	//CSR6[1:0]
	return *this;
}
uint
CS_clkRegs::getwordclk2digdiv(){
	return get_csr_bits(REG_INFO.wordclk2digdiv());	//CSR6[1:0]
}

CS_clkRegs&
CS_clkRegs::setbiascmupwrdb(uint val){
	fill_csr_bits(val,REG_INFO.biascmupwrdb());	//CSR7[15:15]
	return *this;
}
uint
CS_clkRegs::getbiascmupwrdb(){
	return get_csr_bits(REG_INFO.biascmupwrdb());	//CSR7[15:15]
}

CS_clkRegs&
CS_clkRegs::setrefclkdistpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.refclkdistpwrdb());	//CSR7[14:14]
	return *this;
}
uint
CS_clkRegs::getrefclkdistpwrdb(){
	return get_csr_bits(REG_INFO.refclkdistpwrdb());	//CSR7[14:14]
}

CS_clkRegs&
CS_clkRegs::setbiascmutestmode(uint val){
	fill_csr_bits(val,REG_INFO.biascmutestmode());	//CSR7[13:13]
	return *this;
}
uint
CS_clkRegs::getbiascmutestmode(){
	return get_csr_bits(REG_INFO.biascmutestmode());	//CSR7[13:13]
}

CS_clkRegs&
CS_clkRegs::setadcpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.adcpwrdb());	//CSR7[12:12]
	return *this;
}
uint
CS_clkRegs::getadcpwrdb(){
	return get_csr_bits(REG_INFO.adcpwrdb());	//CSR7[12:12]
}

CS_clkRegs&
CS_clkRegs::setcomppwrdb(uint val){
	fill_csr_bits(val,REG_INFO.comppwrdb());	//CSR7[11:11]
	return *this;
}
uint
CS_clkRegs::getcomppwrdb(){
	return get_csr_bits(REG_INFO.comppwrdb());	//CSR7[11:11]
}

CS_clkRegs&
CS_clkRegs::setrefclk0biasctrl(uint val){
	fill_csr_bits(val,REG_INFO.refclk0biasctrl());	//CSR7[3:2]
	return *this;
}
uint
CS_clkRegs::getrefclk0biasctrl(){
	return get_csr_bits(REG_INFO.refclk0biasctrl());	//CSR7[3:2]
}

CS_clkRegs&
CS_clkRegs::setrefclk1biasctrl(uint val){
	fill_csr_bits(val,REG_INFO.refclk1biasctrl());	//CSR7[1:0]
	return *this;
}
uint
CS_clkRegs::getrefclk1biasctrl(){
	return get_csr_bits(REG_INFO.refclk1biasctrl());	//CSR7[1:0]
}

CS_clkRegs&
CS_clkRegs::setpll0pwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll0pwrdb());	//CSR8[15:15]
	return *this;
}
uint
CS_clkRegs::getpll0pwrdb(){
	return get_csr_bits(REG_INFO.pll0pwrdb());	//CSR8[15:15]
}

CS_clkRegs&
CS_clkRegs::setpll0dlfresfbpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll0dlfresfbpwrdb());	//CSR8[9:9]
	return *this;
}
uint
CS_clkRegs::getpll0dlfresfbpwrdb(){
	return get_csr_bits(REG_INFO.pll0dlfresfbpwrdb());	//CSR8[9:9]
}

CS_clkRegs&
CS_clkRegs::setpll0dlfpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll0dlfpwrdb());	//CSR8[8:8]
	return *this;
}
uint
CS_clkRegs::getpll0dlfpwrdb(){
	return get_csr_bits(REG_INFO.pll0dlfpwrdb());	//CSR8[8:8]
}

CS_clkRegs&
CS_clkRegs::setpll0dlfshpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll0dlfshpwrdb());	//CSR8[7:7]
	return *this;
}
uint
CS_clkRegs::getpll0dlfshpwrdb(){
	return get_csr_bits(REG_INFO.pll0dlfshpwrdb());	//CSR8[7:7]
}

CS_clkRegs&
CS_clkRegs::setpll0dlftstpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll0dlftstpwrdb());	//CSR8[6:6]
	return *this;
}
uint
CS_clkRegs::getpll0dlftstpwrdb(){
	return get_csr_bits(REG_INFO.pll0dlftstpwrdb());	//CSR8[6:6]
}

CS_clkRegs&
CS_clkRegs::setpll0dlfcmfbpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll0dlfcmfbpwrdb());	//CSR8[5:5]
	return *this;
}
uint
CS_clkRegs::getpll0dlfcmfbpwrdb(){
	return get_csr_bits(REG_INFO.pll0dlfcmfbpwrdb());	//CSR8[5:5]
}

CS_clkRegs&
CS_clkRegs::setpll0dlfchoppwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll0dlfchoppwrdb());	//CSR8[4:4]
	return *this;
}
uint
CS_clkRegs::getpll0dlfchoppwrdb(){
	return get_csr_bits(REG_INFO.pll0dlfchoppwrdb());	//CSR8[4:4]
}

CS_clkRegs&
CS_clkRegs::setpll0vregpllpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll0vregpllpwrdb());	//CSR8[3:3]
	return *this;
}
uint
CS_clkRegs::getpll0vregpllpwrdb(){
	return get_csr_bits(REG_INFO.pll0vregpllpwrdb());	//CSR8[3:3]
}

CS_clkRegs&
CS_clkRegs::setpll0vregdlfpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll0vregdlfpwrdb());	//CSR8[2:2]
	return *this;
}
uint
CS_clkRegs::getpll0vregdlfpwrdb(){
	return get_csr_bits(REG_INFO.pll0vregdlfpwrdb());	//CSR8[2:2]
}

CS_clkRegs&
CS_clkRegs::setpll0vregvcodivpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll0vregvcodivpwrdb());	//CSR8[0:0]
	return *this;
}
uint
CS_clkRegs::getpll0vregvcodivpwrdb(){
	return get_csr_bits(REG_INFO.pll0vregvcodivpwrdb());	//CSR8[0:0]
}

CS_clkRegs&
CS_clkRegs::setpll0pfdupdnswap(uint val){
	fill_csr_bits(val,REG_INFO.pll0pfdupdnswap());	//CSR9[14:14]
	return *this;
}
uint
CS_clkRegs::getpll0pfdupdnswap(){
	return get_csr_bits(REG_INFO.pll0pfdupdnswap());	//CSR9[14:14]
}

CS_clkRegs&
CS_clkRegs::setpll0pfdforceup(uint val){
	fill_csr_bits(val,REG_INFO.pll0pfdforceup());	//CSR9[13:13]
	return *this;
}
uint
CS_clkRegs::getpll0pfdforceup(){
	return get_csr_bits(REG_INFO.pll0pfdforceup());	//CSR9[13:13]
}

CS_clkRegs&
CS_clkRegs::setpll0pfdforcedn(uint val){
	fill_csr_bits(val,REG_INFO.pll0pfdforcedn());	//CSR9[12:12]
	return *this;
}
uint
CS_clkRegs::getpll0pfdforcedn(){
	return get_csr_bits(REG_INFO.pll0pfdforcedn());	//CSR9[12:12]
}

CS_clkRegs&
CS_clkRegs::setpll0pfdpulsewidth(uint val){
	fill_csr_bits(val,REG_INFO.pll0pfdpulsewidth());	//CSR9[11:10]
	return *this;
}
uint
CS_clkRegs::getpll0pfdpulsewidth(){
	return get_csr_bits(REG_INFO.pll0pfdpulsewidth());	//CSR9[11:10]
}

CS_clkRegs&
CS_clkRegs::setpll0cpcalrstb(uint val){
	fill_csr_bits(val,REG_INFO.pll0cpcalrstb());	//CSR9[7:7]
	return *this;
}
uint
CS_clkRegs::getpll0cpcalrstb(){
	return get_csr_bits(REG_INFO.pll0cpcalrstb());	//CSR9[7:7]
}

CS_clkRegs&
CS_clkRegs::setpll0cpcalrstlvl(uint val){
	fill_csr_bits(val,REG_INFO.pll0cpcalrstlvl());	//CSR9[6:4]
	return *this;
}
uint
CS_clkRegs::getpll0cpcalrstlvl(){
	return get_csr_bits(REG_INFO.pll0cpcalrstlvl());	//CSR9[6:4]
}

CS_clkRegs&
CS_clkRegs::setpll0cpvreflvl(uint val){
	fill_csr_bits(val,REG_INFO.pll0cpvreflvl());	//CSR9[2:0]
	return *this;
}
uint
CS_clkRegs::getpll0cpvreflvl(){
	return get_csr_bits(REG_INFO.pll0cpvreflvl());	//CSR9[2:0]
}

CS_clkRegs&
CS_clkRegs::setpll0cpintcrntsel(uint val){
	fill_csr_bits(val,REG_INFO.pll0cpintcrntsel());	//CSR10[12:11]
	return *this;
}
uint
CS_clkRegs::getpll0cpintcrntsel(){
	return get_csr_bits(REG_INFO.pll0cpintcrntsel());	//CSR10[12:11]
}

CS_clkRegs&
CS_clkRegs::setpll0cppropcrntsel(uint val){
	fill_csr_bits(val,REG_INFO.pll0cppropcrntsel());	//CSR10[6:4]
	return *this;
}
uint
CS_clkRegs::getpll0cppropcrntsel(){
	return get_csr_bits(REG_INFO.pll0cppropcrntsel());	//CSR10[6:4]
}

CS_clkRegs&
CS_clkRegs::setpll0dlfcintsel(uint val){
	fill_csr_bits(val,REG_INFO.pll0dlfcintsel());	//CSR11[15:13]
	return *this;
}
uint
CS_clkRegs::getpll0dlfcintsel(){
	return get_csr_bits(REG_INFO.pll0dlfcintsel());	//CSR11[15:13]
}

CS_clkRegs&
CS_clkRegs::setpll0dlfshdelsel(uint val){
	fill_csr_bits(val,REG_INFO.pll0dlfshdelsel());	//CSR11[7:7]
	return *this;
}
uint
CS_clkRegs::getpll0dlfshdelsel(){
	return get_csr_bits(REG_INFO.pll0dlfshdelsel());	//CSR11[7:7]
}

CS_clkRegs&
CS_clkRegs::setpll0dlfseldtb(uint val){
	fill_csr_bits(val,REG_INFO.pll0dlfseldtb());	//CSR11[6:2]
	return *this;
}
uint
CS_clkRegs::getpll0dlfseldtb(){
	return get_csr_bits(REG_INFO.pll0dlfseldtb());	//CSR11[6:2]
}

CS_clkRegs&
CS_clkRegs::setpll0dlfshcapsel(uint val){
	fill_csr_bits(val,REG_INFO.pll0dlfshcapsel());	//CSR11[1:0]
	return *this;
}
uint
CS_clkRegs::getpll0dlfshcapsel(){
	return get_csr_bits(REG_INFO.pll0dlfshcapsel());	//CSR11[1:0]
}

CS_clkRegs&
CS_clkRegs::setpll0vcobandsel(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcobandsel());	//CSR12[14:12]
	return *this;
}
uint
CS_clkRegs::getpll0vcobandsel(){
	return get_csr_bits(REG_INFO.pll0vcobandsel());	//CSR12[14:12]
}

CS_clkRegs&
CS_clkRegs::setpll0vcoregfilshorten(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcoregfilshorten());	//CSR12[11:11]
	return *this;
}
uint
CS_clkRegs::getpll0vcoregfilshorten(){
	return get_csr_bits(REG_INFO.pll0vcoregfilshorten());	//CSR12[11:11]
}

CS_clkRegs&
CS_clkRegs::setpll0vcoswthhien(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcoswthhien());	//CSR12[10:10]
	return *this;
}
uint
CS_clkRegs::getpll0vcoswthhien(){
	return get_csr_bits(REG_INFO.pll0vcoswthhien());	//CSR12[10:10]
}

CS_clkRegs&
CS_clkRegs::setpll0vcofreqcal(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcofreqcal());	//CSR12[9:5]
	return *this;
}
uint
CS_clkRegs::getpll0vcofreqcal(){
	return get_csr_bits(REG_INFO.pll0vcofreqcal());	//CSR12[9:5]
}

CS_clkRegs&
CS_clkRegs::setpll0vcoitank(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcoitank());	//CSR12[4:0]
	return *this;
}
uint
CS_clkRegs::getpll0vcoitank(){
	return get_csr_bits(REG_INFO.pll0vcoitank());	//CSR12[4:0]
}

CS_clkRegs&
CS_clkRegs::setpll0vcovref(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcovref());	//CSR13[15:12]
	return *this;
}
uint
CS_clkRegs::getpll0vcovref(){
	return get_csr_bits(REG_INFO.pll0vcovref());	//CSR13[15:12]
}

CS_clkRegs&
CS_clkRegs::setpll0vcodivspare(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcodivspare());	//CSR13[11:10]
	return *this;
}
uint
CS_clkRegs::getpll0vcodivspare(){
	return get_csr_bits(REG_INFO.pll0vcodivspare());	//CSR13[11:10]
}

CS_clkRegs&
CS_clkRegs::setpll0vcovregsel(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcovregsel());	//CSR13[9:9]
	return *this;
}
uint
CS_clkRegs::getpll0vcovregsel(){
	return get_csr_bits(REG_INFO.pll0vcovregsel());	//CSR13[9:9]
}

CS_clkRegs&
CS_clkRegs::setpll0vcodiv1p5ctrlcode(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcodiv1p5ctrlcode());	//CSR13[8:4]
	return *this;
}
uint
CS_clkRegs::getpll0vcodiv1p5ctrlcode(){
	return get_csr_bits(REG_INFO.pll0vcodiv1p5ctrlcode());	//CSR13[8:4]
}

CS_clkRegs&
CS_clkRegs::setpll0vcovregclksel(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcovregclksel());	//CSR13[3:3]
	return *this;
}
uint
CS_clkRegs::getpll0vcovregclksel(){
	return get_csr_bits(REG_INFO.pll0vcovregclksel());	//CSR13[3:3]
}

CS_clkRegs&
CS_clkRegs::setpll0vcodpmctrl(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcodpmctrl());	//CSR13[2:0]
	return *this;
}
uint
CS_clkRegs::getpll0vcodpmctrl(){
	return get_csr_bits(REG_INFO.pll0vcodpmctrl());	//CSR13[2:0]
}

CS_clkRegs&
CS_clkRegs::setpll0vcopdpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcopdpwrdb());	//CSR14[15:15]
	return *this;
}
uint
CS_clkRegs::getpll0vcopdpwrdb(){
	return get_csr_bits(REG_INFO.pll0vcopdpwrdb());	//CSR14[15:15]
}

CS_clkRegs&
CS_clkRegs::setpll0vregplldpmen(uint val){
	fill_csr_bits(val,REG_INFO.pll0vregplldpmen());	//CSR14[14:14]
	return *this;
}
uint
CS_clkRegs::getpll0vregplldpmen(){
	return get_csr_bits(REG_INFO.pll0vregplldpmen());	//CSR14[14:14]
}

CS_clkRegs&
CS_clkRegs::setpll0vregpllbleedb(uint val){
	fill_csr_bits(val,REG_INFO.pll0vregpllbleedb());	//CSR14[13:13]
	return *this;
}
uint
CS_clkRegs::getpll0vregpllbleedb(){
	return get_csr_bits(REG_INFO.pll0vregpllbleedb());	//CSR14[13:13]
}

CS_clkRegs&
CS_clkRegs::setpll0vregpllsel(uint val){
	fill_csr_bits(val,REG_INFO.pll0vregpllsel());	//CSR14[12:8]
	return *this;
}
uint
CS_clkRegs::getpll0vregpllsel(){
	return get_csr_bits(REG_INFO.pll0vregpllsel());	//CSR14[12:8]
}

CS_clkRegs&
CS_clkRegs::setpll0vregdlfdpmen(uint val){
	fill_csr_bits(val,REG_INFO.pll0vregdlfdpmen());	//CSR14[6:6]
	return *this;
}
uint
CS_clkRegs::getpll0vregdlfdpmen(){
	return get_csr_bits(REG_INFO.pll0vregdlfdpmen());	//CSR14[6:6]
}

CS_clkRegs&
CS_clkRegs::setpll0vregdlfbleedb(uint val){
	fill_csr_bits(val,REG_INFO.pll0vregdlfbleedb());	//CSR14[5:5]
	return *this;
}
uint
CS_clkRegs::getpll0vregdlfbleedb(){
	return get_csr_bits(REG_INFO.pll0vregdlfbleedb());	//CSR14[5:5]
}

CS_clkRegs&
CS_clkRegs::setpll0vregdlfsel(uint val){
	fill_csr_bits(val,REG_INFO.pll0vregdlfsel());	//CSR14[4:0]
	return *this;
}
uint
CS_clkRegs::getpll0vregdlfsel(){
	return get_csr_bits(REG_INFO.pll0vregdlfsel());	//CSR14[4:0]
}

CS_clkRegs&
CS_clkRegs::setpll0vconewregbwsel(uint val){
	fill_csr_bits(val,REG_INFO.pll0vconewregbwsel());	//CSR15[15:14]
	return *this;
}
uint
CS_clkRegs::getpll0vconewregbwsel(){
	return get_csr_bits(REG_INFO.pll0vconewregbwsel());	//CSR15[15:14]
}

CS_clkRegs&
CS_clkRegs::setpll0vcovtunebufpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcovtunebufpwrdb());	//CSR15[13:13]
	return *this;
}
uint
CS_clkRegs::getpll0vcovtunebufpwrdb(){
	return get_csr_bits(REG_INFO.pll0vcovtunebufpwrdb());	//CSR15[13:13]
}

CS_clkRegs&
CS_clkRegs::setpll0vcocompenstart(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcocompenstart());	//CSR15[12:12]
	return *this;
}
uint
CS_clkRegs::getpll0vcocompenstart(){
	return get_csr_bits(REG_INFO.pll0vcocompenstart());	//CSR15[12:12]
}

CS_clkRegs&
CS_clkRegs::setpll0vcocompenpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcocompenpwrdb());	//CSR15[11:11]
	return *this;
}
uint
CS_clkRegs::getpll0vcocompenpwrdb(){
	return get_csr_bits(REG_INFO.pll0vcocompenpwrdb());	//CSR15[11:11]
}

CS_clkRegs&
CS_clkRegs::setpll0vcocompenbw(uint val){
	fill_csr_bits(val,REG_INFO.pll0vcocompenbw());	//CSR15[10:9]
	return *this;
}
uint
CS_clkRegs::getpll0vcocompenbw(){
	return get_csr_bits(REG_INFO.pll0vcocompenbw());	//CSR15[10:9]
}

CS_clkRegs&
CS_clkRegs::setpll0itankcalmode(uint val){
	fill_csr_bits(val,REG_INFO.pll0itankcalmode());	//CSR15[8:8]
	return *this;
}
uint
CS_clkRegs::getpll0itankcalmode(){
	return get_csr_bits(REG_INFO.pll0itankcalmode());	//CSR15[8:8]
}

CS_clkRegs&
CS_clkRegs::setpll0freqcalmode(uint val){
	fill_csr_bits(val,REG_INFO.pll0freqcalmode());	//CSR15[7:7]
	return *this;
}
uint
CS_clkRegs::getpll0freqcalmode(){
	return get_csr_bits(REG_INFO.pll0freqcalmode());	//CSR15[7:7]
}

CS_clkRegs&
CS_clkRegs::setpll0vregvcodivdpmen(uint val){
	fill_csr_bits(val,REG_INFO.pll0vregvcodivdpmen());	//CSR15[6:6]
	return *this;
}
uint
CS_clkRegs::getpll0vregvcodivdpmen(){
	return get_csr_bits(REG_INFO.pll0vregvcodivdpmen());	//CSR15[6:6]
}

CS_clkRegs&
CS_clkRegs::setpll0vregvcodivbleedb(uint val){
	fill_csr_bits(val,REG_INFO.pll0vregvcodivbleedb());	//CSR15[5:5]
	return *this;
}
uint
CS_clkRegs::getpll0vregvcodivbleedb(){
	return get_csr_bits(REG_INFO.pll0vregvcodivbleedb());	//CSR15[5:5]
}

CS_clkRegs&
CS_clkRegs::setpll0vregvcodivsel(uint val){
	fill_csr_bits(val,REG_INFO.pll0vregvcodivsel());	//CSR15[4:0]
	return *this;
}
uint
CS_clkRegs::getpll0vregvcodivsel(){
	return get_csr_bits(REG_INFO.pll0vregvcodivsel());	//CSR15[4:0]
}

CS_clkRegs&
CS_clkRegs::setpll0spare(uint val){
	fill_csr_bits(val,REG_INFO.pll0spare());	//CSR16[15:0]
	return *this;
}
uint
CS_clkRegs::getpll0spare(){
	return get_csr_bits(REG_INFO.pll0spare());	//CSR16[15:0]
}

CS_clkRegs&
CS_clkRegs::setpll1pwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll1pwrdb());	//CSR17[15:15]
	return *this;
}
uint
CS_clkRegs::getpll1pwrdb(){
	return get_csr_bits(REG_INFO.pll1pwrdb());	//CSR17[15:15]
}

CS_clkRegs&
CS_clkRegs::setpll1dlfresfbpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll1dlfresfbpwrdb());	//CSR17[9:9]
	return *this;
}
uint
CS_clkRegs::getpll1dlfresfbpwrdb(){
	return get_csr_bits(REG_INFO.pll1dlfresfbpwrdb());	//CSR17[9:9]
}

CS_clkRegs&
CS_clkRegs::setpll1dlfpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll1dlfpwrdb());	//CSR17[8:8]
	return *this;
}
uint
CS_clkRegs::getpll1dlfpwrdb(){
	return get_csr_bits(REG_INFO.pll1dlfpwrdb());	//CSR17[8:8]
}

CS_clkRegs&
CS_clkRegs::setpll1dlfshpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll1dlfshpwrdb());	//CSR17[7:7]
	return *this;
}
uint
CS_clkRegs::getpll1dlfshpwrdb(){
	return get_csr_bits(REG_INFO.pll1dlfshpwrdb());	//CSR17[7:7]
}

CS_clkRegs&
CS_clkRegs::setpll1dlftstpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll1dlftstpwrdb());	//CSR17[6:6]
	return *this;
}
uint
CS_clkRegs::getpll1dlftstpwrdb(){
	return get_csr_bits(REG_INFO.pll1dlftstpwrdb());	//CSR17[6:6]
}

CS_clkRegs&
CS_clkRegs::setpll1dlfcmfbpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll1dlfcmfbpwrdb());	//CSR17[5:5]
	return *this;
}
uint
CS_clkRegs::getpll1dlfcmfbpwrdb(){
	return get_csr_bits(REG_INFO.pll1dlfcmfbpwrdb());	//CSR17[5:5]
}

CS_clkRegs&
CS_clkRegs::setpll1dlfchoppwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll1dlfchoppwrdb());	//CSR17[4:4]
	return *this;
}
uint
CS_clkRegs::getpll1dlfchoppwrdb(){
	return get_csr_bits(REG_INFO.pll1dlfchoppwrdb());	//CSR17[4:4]
}

CS_clkRegs&
CS_clkRegs::setpll1vregpllpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll1vregpllpwrdb());	//CSR17[3:3]
	return *this;
}
uint
CS_clkRegs::getpll1vregpllpwrdb(){
	return get_csr_bits(REG_INFO.pll1vregpllpwrdb());	//CSR17[3:3]
}

CS_clkRegs&
CS_clkRegs::setpll1vregdlfpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll1vregdlfpwrdb());	//CSR17[2:2]
	return *this;
}
uint
CS_clkRegs::getpll1vregdlfpwrdb(){
	return get_csr_bits(REG_INFO.pll1vregdlfpwrdb());	//CSR17[2:2]
}

CS_clkRegs&
CS_clkRegs::setpll1vregvcodivpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll1vregvcodivpwrdb());	//CSR17[0:0]
	return *this;
}
uint
CS_clkRegs::getpll1vregvcodivpwrdb(){
	return get_csr_bits(REG_INFO.pll1vregvcodivpwrdb());	//CSR17[0:0]
}

CS_clkRegs&
CS_clkRegs::setpll1pfdupdnswap(uint val){
	fill_csr_bits(val,REG_INFO.pll1pfdupdnswap());	//CSR18[14:14]
	return *this;
}
uint
CS_clkRegs::getpll1pfdupdnswap(){
	return get_csr_bits(REG_INFO.pll1pfdupdnswap());	//CSR18[14:14]
}

CS_clkRegs&
CS_clkRegs::setpll1pfdforceup(uint val){
	fill_csr_bits(val,REG_INFO.pll1pfdforceup());	//CSR18[13:13]
	return *this;
}
uint
CS_clkRegs::getpll1pfdforceup(){
	return get_csr_bits(REG_INFO.pll1pfdforceup());	//CSR18[13:13]
}

CS_clkRegs&
CS_clkRegs::setpll1pfdforcedn(uint val){
	fill_csr_bits(val,REG_INFO.pll1pfdforcedn());	//CSR18[12:12]
	return *this;
}
uint
CS_clkRegs::getpll1pfdforcedn(){
	return get_csr_bits(REG_INFO.pll1pfdforcedn());	//CSR18[12:12]
}

CS_clkRegs&
CS_clkRegs::setpll1pfdpulsewidth(uint val){
	fill_csr_bits(val,REG_INFO.pll1pfdpulsewidth());	//CSR18[11:10]
	return *this;
}
uint
CS_clkRegs::getpll1pfdpulsewidth(){
	return get_csr_bits(REG_INFO.pll1pfdpulsewidth());	//CSR18[11:10]
}

CS_clkRegs&
CS_clkRegs::setpll1cpcalrstb(uint val){
	fill_csr_bits(val,REG_INFO.pll1cpcalrstb());	//CSR18[7:7]
	return *this;
}
uint
CS_clkRegs::getpll1cpcalrstb(){
	return get_csr_bits(REG_INFO.pll1cpcalrstb());	//CSR18[7:7]
}

CS_clkRegs&
CS_clkRegs::setpll1cpcalrstlvl(uint val){
	fill_csr_bits(val,REG_INFO.pll1cpcalrstlvl());	//CSR18[6:4]
	return *this;
}
uint
CS_clkRegs::getpll1cpcalrstlvl(){
	return get_csr_bits(REG_INFO.pll1cpcalrstlvl());	//CSR18[6:4]
}

CS_clkRegs&
CS_clkRegs::setpll1cpvreflvl(uint val){
	fill_csr_bits(val,REG_INFO.pll1cpvreflvl());	//CSR18[2:0]
	return *this;
}
uint
CS_clkRegs::getpll1cpvreflvl(){
	return get_csr_bits(REG_INFO.pll1cpvreflvl());	//CSR18[2:0]
}

CS_clkRegs&
CS_clkRegs::setpll1cpintcrntsel(uint val){
	fill_csr_bits(val,REG_INFO.pll1cpintcrntsel());	//CSR19[12:11]
	return *this;
}
uint
CS_clkRegs::getpll1cpintcrntsel(){
	return get_csr_bits(REG_INFO.pll1cpintcrntsel());	//CSR19[12:11]
}

CS_clkRegs&
CS_clkRegs::setpll1cppropcrntsel(uint val){
	fill_csr_bits(val,REG_INFO.pll1cppropcrntsel());	//CSR19[6:4]
	return *this;
}
uint
CS_clkRegs::getpll1cppropcrntsel(){
	return get_csr_bits(REG_INFO.pll1cppropcrntsel());	//CSR19[6:4]
}

CS_clkRegs&
CS_clkRegs::setpll1dlfcintsel(uint val){
	fill_csr_bits(val,REG_INFO.pll1dlfcintsel());	//CSR20[15:13]
	return *this;
}
uint
CS_clkRegs::getpll1dlfcintsel(){
	return get_csr_bits(REG_INFO.pll1dlfcintsel());	//CSR20[15:13]
}

CS_clkRegs&
CS_clkRegs::setpll1dlfshdelsel(uint val){
	fill_csr_bits(val,REG_INFO.pll1dlfshdelsel());	//CSR20[7:7]
	return *this;
}
uint
CS_clkRegs::getpll1dlfshdelsel(){
	return get_csr_bits(REG_INFO.pll1dlfshdelsel());	//CSR20[7:7]
}

CS_clkRegs&
CS_clkRegs::setpll1dlfseldtb(uint val){
	fill_csr_bits(val,REG_INFO.pll1dlfseldtb());	//CSR20[6:2]
	return *this;
}
uint
CS_clkRegs::getpll1dlfseldtb(){
	return get_csr_bits(REG_INFO.pll1dlfseldtb());	//CSR20[6:2]
}

CS_clkRegs&
CS_clkRegs::setpll1dlfshcapsel(uint val){
	fill_csr_bits(val,REG_INFO.pll1dlfshcapsel());	//CSR20[1:0]
	return *this;
}
uint
CS_clkRegs::getpll1dlfshcapsel(){
	return get_csr_bits(REG_INFO.pll1dlfshcapsel());	//CSR20[1:0]
}

CS_clkRegs&
CS_clkRegs::setpll1vcobandsel(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcobandsel());	//CSR21[14:12]
	return *this;
}
uint
CS_clkRegs::getpll1vcobandsel(){
	return get_csr_bits(REG_INFO.pll1vcobandsel());	//CSR21[14:12]
}

CS_clkRegs&
CS_clkRegs::setpll1vcoregfilshorten(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcoregfilshorten());	//CSR21[11:11]
	return *this;
}
uint
CS_clkRegs::getpll1vcoregfilshorten(){
	return get_csr_bits(REG_INFO.pll1vcoregfilshorten());	//CSR21[11:11]
}

CS_clkRegs&
CS_clkRegs::setpll1vcoswthhien(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcoswthhien());	//CSR21[10:10]
	return *this;
}
uint
CS_clkRegs::getpll1vcoswthhien(){
	return get_csr_bits(REG_INFO.pll1vcoswthhien());	//CSR21[10:10]
}

CS_clkRegs&
CS_clkRegs::setpll1vcofreqcal(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcofreqcal());	//CSR21[9:5]
	return *this;
}
uint
CS_clkRegs::getpll1vcofreqcal(){
	return get_csr_bits(REG_INFO.pll1vcofreqcal());	//CSR21[9:5]
}

CS_clkRegs&
CS_clkRegs::setpll1vcoitank(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcoitank());	//CSR21[4:0]
	return *this;
}
uint
CS_clkRegs::getpll1vcoitank(){
	return get_csr_bits(REG_INFO.pll1vcoitank());	//CSR21[4:0]
}

CS_clkRegs&
CS_clkRegs::setpll1vcovref(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcovref());	//CSR22[15:12]
	return *this;
}
uint
CS_clkRegs::getpll1vcovref(){
	return get_csr_bits(REG_INFO.pll1vcovref());	//CSR22[15:12]
}

CS_clkRegs&
CS_clkRegs::setpll1vcodivspare(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcodivspare());	//CSR22[11:10]
	return *this;
}
uint
CS_clkRegs::getpll1vcodivspare(){
	return get_csr_bits(REG_INFO.pll1vcodivspare());	//CSR22[11:10]
}

CS_clkRegs&
CS_clkRegs::setpll1vcovregsel(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcovregsel());	//CSR22[9:9]
	return *this;
}
uint
CS_clkRegs::getpll1vcovregsel(){
	return get_csr_bits(REG_INFO.pll1vcovregsel());	//CSR22[9:9]
}

CS_clkRegs&
CS_clkRegs::setpll1vcodiv1p5ctrlcode(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcodiv1p5ctrlcode());	//CSR22[8:4]
	return *this;
}
uint
CS_clkRegs::getpll1vcodiv1p5ctrlcode(){
	return get_csr_bits(REG_INFO.pll1vcodiv1p5ctrlcode());	//CSR22[8:4]
}

CS_clkRegs&
CS_clkRegs::setpll1vcovregclksel(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcovregclksel());	//CSR22[3:3]
	return *this;
}
uint
CS_clkRegs::getpll1vcovregclksel(){
	return get_csr_bits(REG_INFO.pll1vcovregclksel());	//CSR22[3:3]
}

CS_clkRegs&
CS_clkRegs::setpll1vcodpmctrl(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcodpmctrl());	//CSR22[2:0]
	return *this;
}
uint
CS_clkRegs::getpll1vcodpmctrl(){
	return get_csr_bits(REG_INFO.pll1vcodpmctrl());	//CSR22[2:0]
}

CS_clkRegs&
CS_clkRegs::setpll1vcopdpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcopdpwrdb());	//CSR23[15:15]
	return *this;
}
uint
CS_clkRegs::getpll1vcopdpwrdb(){
	return get_csr_bits(REG_INFO.pll1vcopdpwrdb());	//CSR23[15:15]
}

CS_clkRegs&
CS_clkRegs::setpll1vregplldpmen(uint val){
	fill_csr_bits(val,REG_INFO.pll1vregplldpmen());	//CSR23[14:14]
	return *this;
}
uint
CS_clkRegs::getpll1vregplldpmen(){
	return get_csr_bits(REG_INFO.pll1vregplldpmen());	//CSR23[14:14]
}

CS_clkRegs&
CS_clkRegs::setpll1vregpllbleedb(uint val){
	fill_csr_bits(val,REG_INFO.pll1vregpllbleedb());	//CSR23[13:13]
	return *this;
}
uint
CS_clkRegs::getpll1vregpllbleedb(){
	return get_csr_bits(REG_INFO.pll1vregpllbleedb());	//CSR23[13:13]
}

CS_clkRegs&
CS_clkRegs::setpll1vregpllsel(uint val){
	fill_csr_bits(val,REG_INFO.pll1vregpllsel());	//CSR23[12:8]
	return *this;
}
uint
CS_clkRegs::getpll1vregpllsel(){
	return get_csr_bits(REG_INFO.pll1vregpllsel());	//CSR23[12:8]
}

CS_clkRegs&
CS_clkRegs::setpll1vregdlfdpmen(uint val){
	fill_csr_bits(val,REG_INFO.pll1vregdlfdpmen());	//CSR23[6:6]
	return *this;
}
uint
CS_clkRegs::getpll1vregdlfdpmen(){
	return get_csr_bits(REG_INFO.pll1vregdlfdpmen());	//CSR23[6:6]
}

CS_clkRegs&
CS_clkRegs::setpll1vregdlfbleedb(uint val){
	fill_csr_bits(val,REG_INFO.pll1vregdlfbleedb());	//CSR23[5:5]
	return *this;
}
uint
CS_clkRegs::getpll1vregdlfbleedb(){
	return get_csr_bits(REG_INFO.pll1vregdlfbleedb());	//CSR23[5:5]
}

CS_clkRegs&
CS_clkRegs::setpll1vregdlfsel(uint val){
	fill_csr_bits(val,REG_INFO.pll1vregdlfsel());	//CSR23[4:0]
	return *this;
}
uint
CS_clkRegs::getpll1vregdlfsel(){
	return get_csr_bits(REG_INFO.pll1vregdlfsel());	//CSR23[4:0]
}

CS_clkRegs&
CS_clkRegs::setpll1vconewregbwsel(uint val){
	fill_csr_bits(val,REG_INFO.pll1vconewregbwsel());	//CSR24[15:14]
	return *this;
}
uint
CS_clkRegs::getpll1vconewregbwsel(){
	return get_csr_bits(REG_INFO.pll1vconewregbwsel());	//CSR24[15:14]
}

CS_clkRegs&
CS_clkRegs::setpll1vcovtunebufpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcovtunebufpwrdb());	//CSR24[13:13]
	return *this;
}
uint
CS_clkRegs::getpll1vcovtunebufpwrdb(){
	return get_csr_bits(REG_INFO.pll1vcovtunebufpwrdb());	//CSR24[13:13]
}

CS_clkRegs&
CS_clkRegs::setpll1vcocompenstart(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcocompenstart());	//CSR24[12:12]
	return *this;
}
uint
CS_clkRegs::getpll1vcocompenstart(){
	return get_csr_bits(REG_INFO.pll1vcocompenstart());	//CSR24[12:12]
}

CS_clkRegs&
CS_clkRegs::setpll1vcocompenpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcocompenpwrdb());	//CSR24[11:11]
	return *this;
}
uint
CS_clkRegs::getpll1vcocompenpwrdb(){
	return get_csr_bits(REG_INFO.pll1vcocompenpwrdb());	//CSR24[11:11]
}

CS_clkRegs&
CS_clkRegs::setpll1vcocompenbw(uint val){
	fill_csr_bits(val,REG_INFO.pll1vcocompenbw());	//CSR24[10:9]
	return *this;
}
uint
CS_clkRegs::getpll1vcocompenbw(){
	return get_csr_bits(REG_INFO.pll1vcocompenbw());	//CSR24[10:9]
}

CS_clkRegs&
CS_clkRegs::setpll1itankcalmode(uint val){
	fill_csr_bits(val,REG_INFO.pll1itankcalmode());	//CSR24[8:8]
	return *this;
}
uint
CS_clkRegs::getpll1itankcalmode(){
	return get_csr_bits(REG_INFO.pll1itankcalmode());	//CSR24[8:8]
}

CS_clkRegs&
CS_clkRegs::setpll1freqcalmode(uint val){
	fill_csr_bits(val,REG_INFO.pll1freqcalmode());	//CSR24[7:7]
	return *this;
}
uint
CS_clkRegs::getpll1freqcalmode(){
	return get_csr_bits(REG_INFO.pll1freqcalmode());	//CSR24[7:7]
}

CS_clkRegs&
CS_clkRegs::setpll1vregvcodivdpmen(uint val){
	fill_csr_bits(val,REG_INFO.pll1vregvcodivdpmen());	//CSR24[6:6]
	return *this;
}
uint
CS_clkRegs::getpll1vregvcodivdpmen(){
	return get_csr_bits(REG_INFO.pll1vregvcodivdpmen());	//CSR24[6:6]
}

CS_clkRegs&
CS_clkRegs::setpll1vregvcodivbleedb(uint val){
	fill_csr_bits(val,REG_INFO.pll1vregvcodivbleedb());	//CSR24[5:5]
	return *this;
}
uint
CS_clkRegs::getpll1vregvcodivbleedb(){
	return get_csr_bits(REG_INFO.pll1vregvcodivbleedb());	//CSR24[5:5]
}

CS_clkRegs&
CS_clkRegs::setpll1vregvcodivsel(uint val){
	fill_csr_bits(val,REG_INFO.pll1vregvcodivsel());	//CSR24[4:0]
	return *this;
}
uint
CS_clkRegs::getpll1vregvcodivsel(){
	return get_csr_bits(REG_INFO.pll1vregvcodivsel());	//CSR24[4:0]
}

CS_clkRegs&
CS_clkRegs::setpll1spare(uint val){
	fill_csr_bits(val,REG_INFO.pll1spare());	//CSR25[15:0]
	return *this;
}
uint
CS_clkRegs::getpll1spare(){
	return get_csr_bits(REG_INFO.pll1spare());	//CSR25[15:0]
}

CS_clkRegs&
CS_clkRegs::setadcrstb(uint val){
	fill_csr_bits(val,REG_INFO.adcrstb());	//CSR26[15:15]
	return *this;
}
uint
CS_clkRegs::getadcrstb(){
	return get_csr_bits(REG_INFO.adcrstb());	//CSR26[15:15]
}

CS_clkRegs&
CS_clkRegs::setadcabsmeasen(uint val){
	fill_csr_bits(val,REG_INFO.adcabsmeasen());	//CSR26[14:14]
	return *this;
}
uint
CS_clkRegs::getadcabsmeasen(){
	return get_csr_bits(REG_INFO.adcabsmeasen());	//CSR26[14:14]
}

CS_clkRegs&
CS_clkRegs::setadctsten(uint val){
	fill_csr_bits(val,REG_INFO.adctsten());	//CSR26[13:13]
	return *this;
}
uint
CS_clkRegs::getadctsten(){
	return get_csr_bits(REG_INFO.adctsten());	//CSR26[13:13]
}

CS_clkRegs&
CS_clkRegs::setadcvcmctrl(uint val){
	fill_csr_bits(val,REG_INFO.adcvcmctrl());	//CSR26[12:11]
	return *this;
}
uint
CS_clkRegs::getadcvcmctrl(){
	return get_csr_bits(REG_INFO.adcvcmctrl());	//CSR26[12:11]
}

uint
CS_clkRegs::getcstopfsmcalspare(){
	return get_csr_bits(REG_INFO.cstopfsmcalspare());	//CSR26[10:10]
}

CS_clkRegs&
CS_clkRegs::setdpminitsettingen(uint val){
	fill_csr_bits(val,REG_INFO.dpminitsettingen());	//CSR26[9:9]
	return *this;
}
uint
CS_clkRegs::getdpminitsettingen(){
	return get_csr_bits(REG_INFO.dpminitsettingen());	//CSR26[9:9]
}

CS_clkRegs&
CS_clkRegs::setcstopfsmcalclr(uint val){
	fill_csr_bits(val,REG_INFO.cstopfsmcalclr());	//CSR26[8:8]
	return *this;
}
uint
CS_clkRegs::getcstopfsmcalclr(){
	return get_csr_bits(REG_INFO.cstopfsmcalclr());	//CSR26[8:8]
}

CS_clkRegs&
CS_clkRegs::setmisccalforcedefault(uint val){
	fill_csr_bits(val,REG_INFO.misccalforcedefault());	//CSR26[7:4]
	return *this;
}
uint
CS_clkRegs::getmisccalforcedefault(){
	return get_csr_bits(REG_INFO.misccalforcedefault());	//CSR26[7:4]
}

uint
CS_clkRegs::getdpmdetdone(){
	return get_csr_bits(REG_INFO.dpmdetdone());	//CSR26[3:3]
}

CS_clkRegs&
CS_clkRegs::setdpmdettasksel(uint val){
	fill_csr_bits(val,REG_INFO.dpmdettasksel());	//CSR26[2:0]
	return *this;
}
uint
CS_clkRegs::getdpmdettasksel(){
	return get_csr_bits(REG_INFO.dpmdettasksel());	//CSR26[2:0]
}

CS_clkRegs&
CS_clkRegs::setcompmodesel(uint val){
	fill_csr_bits(val,REG_INFO.compmodesel());	//CSR27[15:15]
	return *this;
}
uint
CS_clkRegs::getcompmodesel(){
	return get_csr_bits(REG_INFO.compmodesel());	//CSR27[15:15]
}

CS_clkRegs&
CS_clkRegs::setcompcalmuxctrl(uint val){
	fill_csr_bits(val,REG_INFO.compcalmuxctrl());	//CSR27[14:12]
	return *this;
}
uint
CS_clkRegs::getcompcalmuxctrl(){
	return get_csr_bits(REG_INFO.compcalmuxctrl());	//CSR27[14:12]
}

CS_clkRegs&
CS_clkRegs::setcompvrefsel(uint val){
	fill_csr_bits(val,REG_INFO.compvrefsel());	//CSR27[11:6]
	return *this;
}
uint
CS_clkRegs::getcompvrefsel(){
	return get_csr_bits(REG_INFO.compvrefsel());	//CSR27[11:6]
}

CS_clkRegs&
CS_clkRegs::setoverrideoffset(uint val){
	fill_csr_bits(val,REG_INFO.overrideoffset());	//CSR27[5:5]
	return *this;
}
uint
CS_clkRegs::getoverrideoffset(){
	return get_csr_bits(REG_INFO.overrideoffset());	//CSR27[5:5]
}

CS_clkRegs&
CS_clkRegs::setvrefgenoffset(uint val){
	fill_csr_bits(val,REG_INFO.vrefgenoffset());	//CSR27[4:0]
	return *this;
}
uint
CS_clkRegs::getvrefgenoffset(){
	return get_csr_bits(REG_INFO.vrefgenoffset());	//CSR27[4:0]
}

CS_clkRegs&
CS_clkRegs::settopvcofsmbypass(uint val){
	fill_csr_bits(val,REG_INFO.topvcofsmbypass());	//CSR28[15:15]
	return *this;
}
uint
CS_clkRegs::gettopvcofsmbypass(){
	return get_csr_bits(REG_INFO.topvcofsmbypass());	//CSR28[15:15]
}

CS_clkRegs&
CS_clkRegs::setlcvcocalsel(uint val){
	fill_csr_bits(val,REG_INFO.lcvcocalsel());	//CSR28[14:14]
	return *this;
}
uint
CS_clkRegs::getlcvcocalsel(){
	return get_csr_bits(REG_INFO.lcvcocalsel());	//CSR28[14:14]
}

CS_clkRegs&
CS_clkRegs::setlcvcocalctrl(uint val){
	fill_csr_bits(val,REG_INFO.lcvcocalctrl());	//CSR28[13:12]
	return *this;
}
uint
CS_clkRegs::getlcvcocalctrl(){
	return get_csr_bits(REG_INFO.lcvcocalctrl());	//CSR28[13:12]
}

uint
CS_clkRegs::getcspll0pwrseqdone(){
	return get_csr_bits(REG_INFO.cspll0pwrseqdone());	//CSR28[11:11]
}

uint
CS_clkRegs::getcspll1pwrseqdone(){
	return get_csr_bits(REG_INFO.cspll1pwrseqdone());	//CSR28[10:10]
}

CS_clkRegs&
CS_clkRegs::setcspwrseqfsmclr(uint val){
	fill_csr_bits(val,REG_INFO.cspwrseqfsmclr());	//CSR28[9:9]
	return *this;
}
uint
CS_clkRegs::getcspwrseqfsmclr(){
	return get_csr_bits(REG_INFO.cspwrseqfsmclr());	//CSR28[9:9]
}

CS_clkRegs&
CS_clkRegs::setcsfwoverwrite(uint val){
	fill_csr_bits(val,REG_INFO.csfwoverwrite());	//CSR28[8:8]
	return *this;
}
uint
CS_clkRegs::getcsfwoverwrite(){
	return get_csr_bits(REG_INFO.csfwoverwrite());	//CSR28[8:8]
}

CS_clkRegs&
CS_clkRegs::setcscalmode(uint val){
	fill_csr_bits(val,REG_INFO.cscalmode());	//CSR28[7:6]
	return *this;
}
uint
CS_clkRegs::getcscalmode(){
	return get_csr_bits(REG_INFO.cscalmode());	//CSR28[7:6]
}

CS_clkRegs&
CS_clkRegs::setcsadccompsel(uint val){
	fill_csr_bits(val,REG_INFO.csadccompsel());	//CSR28[5:5]
	return *this;
}
uint
CS_clkRegs::getcsadccompsel(){
	return get_csr_bits(REG_INFO.csadccompsel());	//CSR28[5:5]
}

uint
CS_clkRegs::getlcvcocaldone(){
	return get_csr_bits(REG_INFO.lcvcocaldone());	//CSR28[4:4]
}

uint
CS_clkRegs::getlcvcocalerr(){
	return get_csr_bits(REG_INFO.lcvcocalerr());	//CSR28[3:3]
}

uint
CS_clkRegs::getlcvcocalstatus(){
	return get_csr_bits(REG_INFO.lcvcocalstatus());	//CSR28[2:0]
}

CS_clkRegs&
CS_clkRegs::setatbfinalsel(uint val){
	fill_csr_bits(val,REG_INFO.atbfinalsel());	//CSR29[15:13]
	return *this;
}
uint
CS_clkRegs::getatbfinalsel(){
	return get_csr_bits(REG_INFO.atbfinalsel());	//CSR29[15:13]
}

CS_clkRegs&
CS_clkRegs::setcsatbtopsel(uint val){
	fill_csr_bits(val,REG_INFO.csatbtopsel());	//CSR29[12:10]
	return *this;
}
uint
CS_clkRegs::getcsatbtopsel(){
	return get_csr_bits(REG_INFO.csatbtopsel());	//CSR29[12:10]
}

CS_clkRegs&
CS_clkRegs::setcsatbspare(uint val){
	fill_csr_bits(val,REG_INFO.csatbspare());	//CSR29[9:6]
	return *this;
}
uint
CS_clkRegs::getcsatbspare(){
	return get_csr_bits(REG_INFO.csatbspare());	//CSR29[9:6]
}

CS_clkRegs&
CS_clkRegs::setbiasatbsel(uint val){
	fill_csr_bits(val,REG_INFO.biasatbsel());	//CSR29[5:3]
	return *this;
}
uint
CS_clkRegs::getbiasatbsel(){
	return get_csr_bits(REG_INFO.biasatbsel());	//CSR29[5:3]
}

CS_clkRegs&
CS_clkRegs::setcompatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.compatbctrl());	//CSR29[2:0]
	return *this;
}
uint
CS_clkRegs::getcompatbctrl(){
	return get_csr_bits(REG_INFO.compatbctrl());	//CSR29[2:0]
}

CS_clkRegs&
CS_clkRegs::setpll0atbplltopsel(uint val){
	fill_csr_bits(val,REG_INFO.pll0atbplltopsel());	//CSR30[15:13]
	return *this;
}
uint
CS_clkRegs::getpll0atbplltopsel(){
	return get_csr_bits(REG_INFO.pll0atbplltopsel());	//CSR30[15:13]
}

CS_clkRegs&
CS_clkRegs::setpll0atbpllctrl(uint val){
	fill_csr_bits(val,REG_INFO.pll0atbpllctrl());	//CSR30[10:8]
	return *this;
}
uint
CS_clkRegs::getpll0atbpllctrl(){
	return get_csr_bits(REG_INFO.pll0atbpllctrl());	//CSR30[10:8]
}

CS_clkRegs&
CS_clkRegs::setpll0atbvcoctrl(uint val){
	fill_csr_bits(val,REG_INFO.pll0atbvcoctrl());	//CSR30[6:5]
	return *this;
}
uint
CS_clkRegs::getpll0atbvcoctrl(){
	return get_csr_bits(REG_INFO.pll0atbvcoctrl());	//CSR30[6:5]
}

CS_clkRegs&
CS_clkRegs::setpll0adcvcoctrl(uint val){
	fill_csr_bits(val,REG_INFO.pll0adcvcoctrl());	//CSR30[4:3]
	return *this;
}
uint
CS_clkRegs::getpll0adcvcoctrl(){
	return get_csr_bits(REG_INFO.pll0adcvcoctrl());	//CSR30[4:3]
}

uint
CS_clkRegs::getpll0dtbout(){
	return get_csr_bits(REG_INFO.pll0dtbout());	//CSR30[0:0]
}

CS_clkRegs&
CS_clkRegs::setpll0atbvregsel(uint val){
	fill_csr_bits(val,REG_INFO.pll0atbvregsel());	//CSR31[14:12]
	return *this;
}
uint
CS_clkRegs::getpll0atbvregsel(){
	return get_csr_bits(REG_INFO.pll0atbvregsel());	//CSR31[14:12]
}

CS_clkRegs&
CS_clkRegs::setpll0atbvregpllctrl(uint val){
	fill_csr_bits(val,REG_INFO.pll0atbvregpllctrl());	//CSR31[11:9]
	return *this;
}
uint
CS_clkRegs::getpll0atbvregpllctrl(){
	return get_csr_bits(REG_INFO.pll0atbvregpllctrl());	//CSR31[11:9]
}

CS_clkRegs&
CS_clkRegs::setpll0atbvregdlfctrl(uint val){
	fill_csr_bits(val,REG_INFO.pll0atbvregdlfctrl());	//CSR31[8:6]
	return *this;
}
uint
CS_clkRegs::getpll0atbvregdlfctrl(){
	return get_csr_bits(REG_INFO.pll0atbvregdlfctrl());	//CSR31[8:6]
}

CS_clkRegs&
CS_clkRegs::setpll0atbvregvcodivctrl(uint val){
	fill_csr_bits(val,REG_INFO.pll0atbvregvcodivctrl());	//CSR31[2:0]
	return *this;
}
uint
CS_clkRegs::getpll0atbvregvcodivctrl(){
	return get_csr_bits(REG_INFO.pll0atbvregvcodivctrl());	//CSR31[2:0]
}

CS_clkRegs&
CS_clkRegs::setpll1atbplltopsel(uint val){
	fill_csr_bits(val,REG_INFO.pll1atbplltopsel());	//CSR32[15:13]
	return *this;
}
uint
CS_clkRegs::getpll1atbplltopsel(){
	return get_csr_bits(REG_INFO.pll1atbplltopsel());	//CSR32[15:13]
}

CS_clkRegs&
CS_clkRegs::setpll1atbpllctrl(uint val){
	fill_csr_bits(val,REG_INFO.pll1atbpllctrl());	//CSR32[10:8]
	return *this;
}
uint
CS_clkRegs::getpll1atbpllctrl(){
	return get_csr_bits(REG_INFO.pll1atbpllctrl());	//CSR32[10:8]
}

CS_clkRegs&
CS_clkRegs::setpll1atbvcoctrl(uint val){
	fill_csr_bits(val,REG_INFO.pll1atbvcoctrl());	//CSR32[6:5]
	return *this;
}
uint
CS_clkRegs::getpll1atbvcoctrl(){
	return get_csr_bits(REG_INFO.pll1atbvcoctrl());	//CSR32[6:5]
}

CS_clkRegs&
CS_clkRegs::setpll1adcvcoctrl(uint val){
	fill_csr_bits(val,REG_INFO.pll1adcvcoctrl());	//CSR32[4:3]
	return *this;
}
uint
CS_clkRegs::getpll1adcvcoctrl(){
	return get_csr_bits(REG_INFO.pll1adcvcoctrl());	//CSR32[4:3]
}

uint
CS_clkRegs::getpll1dtbout(){
	return get_csr_bits(REG_INFO.pll1dtbout());	//CSR32[0:0]
}

CS_clkRegs&
CS_clkRegs::setpll1atbvregsel(uint val){
	fill_csr_bits(val,REG_INFO.pll1atbvregsel());	//CSR33[14:12]
	return *this;
}
uint
CS_clkRegs::getpll1atbvregsel(){
	return get_csr_bits(REG_INFO.pll1atbvregsel());	//CSR33[14:12]
}

CS_clkRegs&
CS_clkRegs::setpll1atbvregpllctrl(uint val){
	fill_csr_bits(val,REG_INFO.pll1atbvregpllctrl());	//CSR33[11:9]
	return *this;
}
uint
CS_clkRegs::getpll1atbvregpllctrl(){
	return get_csr_bits(REG_INFO.pll1atbvregpllctrl());	//CSR33[11:9]
}

CS_clkRegs&
CS_clkRegs::setpll1atbvregdlfctrl(uint val){
	fill_csr_bits(val,REG_INFO.pll1atbvregdlfctrl());	//CSR33[8:6]
	return *this;
}
uint
CS_clkRegs::getpll1atbvregdlfctrl(){
	return get_csr_bits(REG_INFO.pll1atbvregdlfctrl());	//CSR33[8:6]
}

CS_clkRegs&
CS_clkRegs::setpll1atbvregvcodivctrl(uint val){
	fill_csr_bits(val,REG_INFO.pll1atbvregvcodivctrl());	//CSR33[2:0]
	return *this;
}
uint
CS_clkRegs::getpll1atbvregvcodivctrl(){
	return get_csr_bits(REG_INFO.pll1atbvregvcodivctrl());	//CSR33[2:0]
}

CS_clkRegs&
CS_clkRegs::setsspwrdb(uint val){
	fill_csr_bits(val,REG_INFO.sspwrdb());	//CSR34[15:15]
	return *this;
}
uint
CS_clkRegs::getsspwrdb(){
	return get_csr_bits(REG_INFO.sspwrdb());	//CSR34[15:15]
}

CS_clkRegs&
CS_clkRegs::setssrefclk0pwrdb(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk0pwrdb());	//CSR34[14:14]
	return *this;
}
uint
CS_clkRegs::getssrefclk0pwrdb(){
	return get_csr_bits(REG_INFO.ssrefclk0pwrdb());	//CSR34[14:14]
}

CS_clkRegs&
CS_clkRegs::setssrefclk1pwrdb(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk1pwrdb());	//CSR34[13:13]
	return *this;
}
uint
CS_clkRegs::getssrefclk1pwrdb(){
	return get_csr_bits(REG_INFO.ssrefclk1pwrdb());	//CSR34[13:13]
}

CS_clkRegs&
CS_clkRegs::setssrefclk0cmldivpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk0cmldivpwrdb());	//CSR34[12:12]
	return *this;
}
uint
CS_clkRegs::getssrefclk0cmldivpwrdb(){
	return get_csr_bits(REG_INFO.ssrefclk0cmldivpwrdb());	//CSR34[12:12]
}

CS_clkRegs&
CS_clkRegs::setssrefclk1cmldivpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk1cmldivpwrdb());	//CSR34[11:11]
	return *this;
}
uint
CS_clkRegs::getssrefclk1cmldivpwrdb(){
	return get_csr_bits(REG_INFO.ssrefclk1cmldivpwrdb());	//CSR34[11:11]
}

CS_clkRegs&
CS_clkRegs::setssrefclk0div2sel(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk0div2sel());	//CSR34[10:10]
	return *this;
}
uint
CS_clkRegs::getssrefclk0div2sel(){
	return get_csr_bits(REG_INFO.ssrefclk0div2sel());	//CSR34[10:10]
}

CS_clkRegs&
CS_clkRegs::setssrefclk1div2sel(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk1div2sel());	//CSR34[9:9]
	return *this;
}
uint
CS_clkRegs::getssrefclk1div2sel(){
	return get_csr_bits(REG_INFO.ssrefclk1div2sel());	//CSR34[9:9]
}

CS_clkRegs&
CS_clkRegs::setsscmosrefclksel(uint val){
	fill_csr_bits(val,REG_INFO.sscmosrefclksel());	//CSR34[8:8]
	return *this;
}
uint
CS_clkRegs::getsscmosrefclksel(){
	return get_csr_bits(REG_INFO.sscmosrefclksel());	//CSR34[8:8]
}

CS_clkRegs&
CS_clkRegs::setssrefclk0biasctrl(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk0biasctrl());	//CSR34[7:6]
	return *this;
}
uint
CS_clkRegs::getssrefclk0biasctrl(){
	return get_csr_bits(REG_INFO.ssrefclk0biasctrl());	//CSR34[7:6]
}

CS_clkRegs&
CS_clkRegs::setssrefclk1biasctrl(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk1biasctrl());	//CSR34[5:4]
	return *this;
}
uint
CS_clkRegs::getssrefclk1biasctrl(){
	return get_csr_bits(REG_INFO.ssrefclk1biasctrl());	//CSR34[5:4]
}

CS_clkRegs&
CS_clkRegs::setssrefclk0distbiasctrl(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk0distbiasctrl());	//CSR34[3:2]
	return *this;
}
uint
CS_clkRegs::getssrefclk0distbiasctrl(){
	return get_csr_bits(REG_INFO.ssrefclk0distbiasctrl());	//CSR34[3:2]
}

CS_clkRegs&
CS_clkRegs::setssrefclk1distbiasctrl(uint val){
	fill_csr_bits(val,REG_INFO.ssrefclk1distbiasctrl());	//CSR34[1:0]
	return *this;
}
uint
CS_clkRegs::getssrefclk1distbiasctrl(){
	return get_csr_bits(REG_INFO.ssrefclk1distbiasctrl());	//CSR34[1:0]
}

CS_clkRegs&
CS_clkRegs::setbiasmstricvpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.biasmstricvpwrdb());	//CSR35[9:9]
	return *this;
}
uint
CS_clkRegs::getbiasmstricvpwrdb(){
	return get_csr_bits(REG_INFO.biasmstricvpwrdb());	//CSR35[9:9]
}

CS_clkRegs&
CS_clkRegs::setbiasmstriccpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.biasmstriccpwrdb());	//CSR35[8:8]
	return *this;
}
uint
CS_clkRegs::getbiasmstriccpwrdb(){
	return get_csr_bits(REG_INFO.biasmstriccpwrdb());	//CSR35[8:8]
}

CS_clkRegs&
CS_clkRegs::setbiasmstriptatpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.biasmstriptatpwrdb());	//CSR35[7:7]
	return *this;
}
uint
CS_clkRegs::getbiasmstriptatpwrdb(){
	return get_csr_bits(REG_INFO.biasmstriptatpwrdb());	//CSR35[7:7]
}

CS_clkRegs&
CS_clkRegs::setvbgpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.vbgpwrdb());	//CSR35[6:6]
	return *this;
}
uint
CS_clkRegs::getvbgpwrdb(){
	return get_csr_bits(REG_INFO.vbgpwrdb());	//CSR35[6:6]
}

CS_clkRegs&
CS_clkRegs::setvptatpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.vptatpwrdb());	//CSR35[5:5]
	return *this;
}
uint
CS_clkRegs::getvptatpwrdb(){
	return get_csr_bits(REG_INFO.vptatpwrdb());	//CSR35[5:5]
}

CS_clkRegs&
CS_clkRegs::setssadcpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.ssadcpwrdb());	//CSR35[4:4]
	return *this;
}
uint
CS_clkRegs::getssadcpwrdb(){
	return get_csr_bits(REG_INFO.ssadcpwrdb());	//CSR35[4:4]
}

CS_clkRegs&
CS_clkRegs::setsscomppwrdb(uint val){
	fill_csr_bits(val,REG_INFO.sscomppwrdb());	//CSR35[3:3]
	return *this;
}
uint
CS_clkRegs::getsscomppwrdb(){
	return get_csr_bits(REG_INFO.sscomppwrdb());	//CSR35[3:3]
}

CS_clkRegs&
CS_clkRegs::setsscompvrefpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.sscompvrefpwrdb());	//CSR35[2:2]
	return *this;
}
uint
CS_clkRegs::getsscompvrefpwrdb(){
	return get_csr_bits(REG_INFO.sscompvrefpwrdb());	//CSR35[2:2]
}

CS_clkRegs&
CS_clkRegs::setmosdetidacpwrdb(uint val){
	fill_csr_bits(val,REG_INFO.mosdetidacpwrdb());	//CSR35[1:1]
	return *this;
}
uint
CS_clkRegs::getmosdetidacpwrdb(){
	return get_csr_bits(REG_INFO.mosdetidacpwrdb());	//CSR35[1:1]
}

CS_clkRegs&
CS_clkRegs::setmosdetcml2cmospwrdb(uint val){
	fill_csr_bits(val,REG_INFO.mosdetcml2cmospwrdb());	//CSR35[0:0]
	return *this;
}
uint
CS_clkRegs::getmosdetcml2cmospwrdb(){
	return get_csr_bits(REG_INFO.mosdetcml2cmospwrdb());	//CSR35[0:0]
}

CS_clkRegs&
CS_clkRegs::setbg600mvlvccresdiv(uint val){
	fill_csr_bits(val,REG_INFO.bg600mvlvccresdiv());	//CSR36[15:15]
	return *this;
}
uint
CS_clkRegs::getbg600mvlvccresdiv(){
	return get_csr_bits(REG_INFO.bg600mvlvccresdiv());	//CSR36[15:15]
}

CS_clkRegs&
CS_clkRegs::setbgbufsel(uint val){
	fill_csr_bits(val,REG_INFO.bgbufsel());	//CSR36[14:14]
	return *this;
}
uint
CS_clkRegs::getbgbufsel(){
	return get_csr_bits(REG_INFO.bgbufsel());	//CSR36[14:14]
}

CS_clkRegs&
CS_clkRegs::setbgbufcalen(uint val){
	fill_csr_bits(val,REG_INFO.bgbufcalen());	//CSR36[13:13]
	return *this;
}
uint
CS_clkRegs::getbgbufcalen(){
	return get_csr_bits(REG_INFO.bgbufcalen());	//CSR36[13:13]
}

CS_clkRegs&
CS_clkRegs::setbgbufofst(uint val){
	fill_csr_bits(val,REG_INFO.bgbufofst());	//CSR36[12:8]
	return *this;
}
uint
CS_clkRegs::getbgbufofst(){
	return get_csr_bits(REG_INFO.bgbufofst());	//CSR36[12:8]
}

CS_clkRegs&
CS_clkRegs::setbgbypass(uint val){
	fill_csr_bits(val,REG_INFO.bgbypass());	//CSR36[7:0]
	return *this;
}
uint
CS_clkRegs::getbgbypass(){
	return get_csr_bits(REG_INFO.bgbypass());	//CSR36[7:0]
}

uint
CS_clkRegs::getbgbufcaltrig(){
	return get_csr_bits(REG_INFO.bgbufcaltrig());	//CSR37[15:15]
}

CS_clkRegs&
CS_clkRegs::setvbgrstb(uint val){
	fill_csr_bits(val,REG_INFO.vbgrstb());	//CSR37[14:14]
	return *this;
}
uint
CS_clkRegs::getvbgrstb(){
	return get_csr_bits(REG_INFO.vbgrstb());	//CSR37[14:14]
}

CS_clkRegs&
CS_clkRegs::setvbgbypassb(uint val){
	fill_csr_bits(val,REG_INFO.vbgbypassb());	//CSR37[13:13]
	return *this;
}
uint
CS_clkRegs::getvbgbypassb(){
	return get_csr_bits(REG_INFO.vbgbypassb());	//CSR37[13:13]
}

CS_clkRegs&
CS_clkRegs::setvbgmode(uint val){
	fill_csr_bits(val,REG_INFO.vbgmode());	//CSR37[12:12]
	return *this;
}
uint
CS_clkRegs::getvbgmode(){
	return get_csr_bits(REG_INFO.vbgmode());	//CSR37[12:12]
}

CS_clkRegs&
CS_clkRegs::setvbgchopclkmode(uint val){
	fill_csr_bits(val,REG_INFO.vbgchopclkmode());	//CSR37[11:11]
	return *this;
}
uint
CS_clkRegs::getvbgchopclkmode(){
	return get_csr_bits(REG_INFO.vbgchopclkmode());	//CSR37[11:11]
}

CS_clkRegs&
CS_clkRegs::setvbgdemclkmode(uint val){
	fill_csr_bits(val,REG_INFO.vbgdemclkmode());	//CSR37[10:10]
	return *this;
}
uint
CS_clkRegs::getvbgdemclkmode(){
	return get_csr_bits(REG_INFO.vbgdemclkmode());	//CSR37[10:10]
}

CS_clkRegs&
CS_clkRegs::setvbgenchop(uint val){
	fill_csr_bits(val,REG_INFO.vbgenchop());	//CSR37[8:8]
	return *this;
}
uint
CS_clkRegs::getvbgenchop(){
	return get_csr_bits(REG_INFO.vbgenchop());	//CSR37[8:8]
}

CS_clkRegs&
CS_clkRegs::setvbgendem(uint val){
	fill_csr_bits(val,REG_INFO.vbgendem());	//CSR37[7:7]
	return *this;
}
uint
CS_clkRegs::getvbgendem(){
	return get_csr_bits(REG_INFO.vbgendem());	//CSR37[7:7]
}

CS_clkRegs&
CS_clkRegs::setvbgreflvl(uint val){
	fill_csr_bits(val,REG_INFO.vbgreflvl());	//CSR37[2:0]
	return *this;
}
uint
CS_clkRegs::getvbgreflvl(){
	return get_csr_bits(REG_INFO.vbgreflvl());	//CSR37[2:0]
}

CS_clkRegs&
CS_clkRegs::setvptatrstb(uint val){
	fill_csr_bits(val,REG_INFO.vptatrstb());	//CSR38[14:14]
	return *this;
}
uint
CS_clkRegs::getvptatrstb(){
	return get_csr_bits(REG_INFO.vptatrstb());	//CSR38[14:14]
}

CS_clkRegs&
CS_clkRegs::setvptatbypassb(uint val){
	fill_csr_bits(val,REG_INFO.vptatbypassb());	//CSR38[13:13]
	return *this;
}
uint
CS_clkRegs::getvptatbypassb(){
	return get_csr_bits(REG_INFO.vptatbypassb());	//CSR38[13:13]
}

CS_clkRegs&
CS_clkRegs::setvptatmode(uint val){
	fill_csr_bits(val,REG_INFO.vptatmode());	//CSR38[12:12]
	return *this;
}
uint
CS_clkRegs::getvptatmode(){
	return get_csr_bits(REG_INFO.vptatmode());	//CSR38[12:12]
}

CS_clkRegs&
CS_clkRegs::setvptatchopclkmode(uint val){
	fill_csr_bits(val,REG_INFO.vptatchopclkmode());	//CSR38[11:11]
	return *this;
}
uint
CS_clkRegs::getvptatchopclkmode(){
	return get_csr_bits(REG_INFO.vptatchopclkmode());	//CSR38[11:11]
}

CS_clkRegs&
CS_clkRegs::setvptatdemclkmode(uint val){
	fill_csr_bits(val,REG_INFO.vptatdemclkmode());	//CSR38[10:10]
	return *this;
}
uint
CS_clkRegs::getvptatdemclkmode(){
	return get_csr_bits(REG_INFO.vptatdemclkmode());	//CSR38[10:10]
}

CS_clkRegs&
CS_clkRegs::setvptatenchop(uint val){
	fill_csr_bits(val,REG_INFO.vptatenchop());	//CSR38[8:8]
	return *this;
}
uint
CS_clkRegs::getvptatenchop(){
	return get_csr_bits(REG_INFO.vptatenchop());	//CSR38[8:8]
}

CS_clkRegs&
CS_clkRegs::setvptatendem(uint val){
	fill_csr_bits(val,REG_INFO.vptatendem());	//CSR38[7:7]
	return *this;
}
uint
CS_clkRegs::getvptatendem(){
	return get_csr_bits(REG_INFO.vptatendem());	//CSR38[7:7]
}

CS_clkRegs&
CS_clkRegs::setvptatreflvl(uint val){
	fill_csr_bits(val,REG_INFO.vptatreflvl());	//CSR38[2:0]
	return *this;
}
uint
CS_clkRegs::getvptatreflvl(){
	return get_csr_bits(REG_INFO.vptatreflvl());	//CSR38[2:0]
}

CS_clkRegs&
CS_clkRegs::setssadcrstb(uint val){
	fill_csr_bits(val,REG_INFO.ssadcrstb());	//CSR39[15:15]
	return *this;
}
uint
CS_clkRegs::getssadcrstb(){
	return get_csr_bits(REG_INFO.ssadcrstb());	//CSR39[15:15]
}

CS_clkRegs&
CS_clkRegs::setssadcabsmeasen(uint val){
	fill_csr_bits(val,REG_INFO.ssadcabsmeasen());	//CSR39[14:14]
	return *this;
}
uint
CS_clkRegs::getssadcabsmeasen(){
	return get_csr_bits(REG_INFO.ssadcabsmeasen());	//CSR39[14:14]
}

CS_clkRegs&
CS_clkRegs::setssadctsten(uint val){
	fill_csr_bits(val,REG_INFO.ssadctsten());	//CSR39[13:13]
	return *this;
}
uint
CS_clkRegs::getssadctsten(){
	return get_csr_bits(REG_INFO.ssadctsten());	//CSR39[13:13]
}

CS_clkRegs&
CS_clkRegs::setssadcvcmctrl(uint val){
	fill_csr_bits(val,REG_INFO.ssadcvcmctrl());	//CSR39[12:11]
	return *this;
}
uint
CS_clkRegs::getssadcvcmctrl(){
	return get_csr_bits(REG_INFO.ssadcvcmctrl());	//CSR39[12:11]
}

CS_clkRegs&
CS_clkRegs::setssadcinputsel(uint val){
	fill_csr_bits(val,REG_INFO.ssadcinputsel());	//CSR39[10:8]
	return *this;
}
uint
CS_clkRegs::getssadcinputsel(){
	return get_csr_bits(REG_INFO.ssadcinputsel());	//CSR39[10:8]
}

CS_clkRegs&
CS_clkRegs::settsensoren(uint val){
	fill_csr_bits(val,REG_INFO.tsensoren());	//CSR39[7:7]
	return *this;
}
uint
CS_clkRegs::gettsensoren(){
	return get_csr_bits(REG_INFO.tsensoren());	//CSR39[7:7]
}

CS_clkRegs&
CS_clkRegs::settsensorcstemp(uint val){
	fill_csr_bits(val,REG_INFO.tsensorcstemp());	//CSR39[6:4]
	return *this;
}
uint
CS_clkRegs::gettsensorcstemp(){
	return get_csr_bits(REG_INFO.tsensorcstemp());	//CSR39[6:4]
}

CS_clkRegs&
CS_clkRegs::setsscompmodesel(uint val){
	fill_csr_bits(val,REG_INFO.sscompmodesel());	//CSR40[15:15]
	return *this;
}
uint
CS_clkRegs::getsscompmodesel(){
	return get_csr_bits(REG_INFO.sscompmodesel());	//CSR40[15:15]
}

CS_clkRegs&
CS_clkRegs::setsscompvinmsel(uint val){
	fill_csr_bits(val,REG_INFO.sscompvinmsel());	//CSR40[14:12]
	return *this;
}
uint
CS_clkRegs::getsscompvinmsel(){
	return get_csr_bits(REG_INFO.sscompvinmsel());	//CSR40[14:12]
}

CS_clkRegs&
CS_clkRegs::setsscompvinpsel(uint val){
	fill_csr_bits(val,REG_INFO.sscompvinpsel());	//CSR40[11:9]
	return *this;
}
uint
CS_clkRegs::getsscompvinpsel(){
	return get_csr_bits(REG_INFO.sscompvinpsel());	//CSR40[11:9]
}

CS_clkRegs&
CS_clkRegs::setsscompvrefsel(uint val){
	fill_csr_bits(val,REG_INFO.sscompvrefsel());	//CSR40[8:3]
	return *this;
}
uint
CS_clkRegs::getsscompvrefsel(){
	return get_csr_bits(REG_INFO.sscompvrefsel());	//CSR40[8:3]
}

uint
CS_clkRegs::getsscompstatus(){
	return get_csr_bits(REG_INFO.sscompstatus());	//CSR40[0:0]
}

CS_clkRegs&
CS_clkRegs::setmosdeten(uint val){
	fill_csr_bits(val,REG_INFO.mosdeten());	//CSR41[15:15]
	return *this;
}
uint
CS_clkRegs::getmosdeten(){
	return get_csr_bits(REG_INFO.mosdeten());	//CSR41[15:15]
}

CS_clkRegs&
CS_clkRegs::setmosdetmostypesel(uint val){
	fill_csr_bits(val,REG_INFO.mosdetmostypesel());	//CSR41[14:14]
	return *this;
}
uint
CS_clkRegs::getmosdetmostypesel(){
	return get_csr_bits(REG_INFO.mosdetmostypesel());	//CSR41[14:14]
}

CS_clkRegs&
CS_clkRegs::setmosdetvcocalen(uint val){
	fill_csr_bits(val,REG_INFO.mosdetvcocalen());	//CSR41[13:13]
	return *this;
}
uint
CS_clkRegs::getmosdetvcocalen(){
	return get_csr_bits(REG_INFO.mosdetvcocalen());	//CSR41[13:13]
}

CS_clkRegs&
CS_clkRegs::setmosdetioscptune(uint val){
	fill_csr_bits(val,REG_INFO.mosdetioscptune());	//CSR41[12:10]
	return *this;
}
uint
CS_clkRegs::getmosdetioscptune(){
	return get_csr_bits(REG_INFO.mosdetioscptune());	//CSR41[12:10]
}

CS_clkRegs&
CS_clkRegs::setmosdetioscdacofst(uint val){
	fill_csr_bits(val,REG_INFO.mosdetioscdacofst());	//CSR41[9:8]
	return *this;
}
uint
CS_clkRegs::getmosdetioscdacofst(){
	return get_csr_bits(REG_INFO.mosdetioscdacofst());	//CSR41[9:8]
}

CS_clkRegs&
CS_clkRegs::setmosdetioscdaccal(uint val){
	fill_csr_bits(val,REG_INFO.mosdetioscdaccal());	//CSR41[7:0]
	return *this;
}
uint
CS_clkRegs::getmosdetioscdaccal(){
	return get_csr_bits(REG_INFO.mosdetioscdaccal());	//CSR41[7:0]
}

CS_clkRegs&
CS_clkRegs::setmosdetpsel(uint val){
	fill_csr_bits(val,REG_INFO.mosdetpsel());	//CSR42[15:13]
	return *this;
}
uint
CS_clkRegs::getmosdetpsel(){
	return get_csr_bits(REG_INFO.mosdetpsel());	//CSR42[15:13]
}

CS_clkRegs&
CS_clkRegs::setmosdets1sel(uint val){
	fill_csr_bits(val,REG_INFO.mosdets1sel());	//CSR42[12:10]
	return *this;
}
uint
CS_clkRegs::getmosdets1sel(){
	return get_csr_bits(REG_INFO.mosdets1sel());	//CSR42[12:10]
}

CS_clkRegs&
CS_clkRegs::setmosdets2sel(uint val){
	fill_csr_bits(val,REG_INFO.mosdets2sel());	//CSR42[9:8]
	return *this;
}
uint
CS_clkRegs::getmosdets2sel(){
	return get_csr_bits(REG_INFO.mosdets2sel());	//CSR42[9:8]
}

CS_clkRegs&
CS_clkRegs::setmosdetiosccrosstune(uint val){
	fill_csr_bits(val,REG_INFO.mosdetiosccrosstune());	//CSR42[7:7]
	return *this;
}
uint
CS_clkRegs::getmosdetiosccrosstune(){
	return get_csr_bits(REG_INFO.mosdetiosccrosstune());	//CSR42[7:7]
}

CS_clkRegs&
CS_clkRegs::setmosdetoscdiv(uint val){
	fill_csr_bits(val,REG_INFO.mosdetoscdiv());	//CSR42[1:0]
	return *this;
}
uint
CS_clkRegs::getmosdetoscdiv(){
	return get_csr_bits(REG_INFO.mosdetoscdiv());	//CSR42[1:0]
}

CS_clkRegs&
CS_clkRegs::setmosdetcsnmoscnr(uint val){
	fill_csr_bits(val,REG_INFO.mosdetcsnmoscnr());	//CSR43[15:13]
	return *this;
}
uint
CS_clkRegs::getmosdetcsnmoscnr(){
	return get_csr_bits(REG_INFO.mosdetcsnmoscnr());	//CSR43[15:13]
}

CS_clkRegs&
CS_clkRegs::setmosdetcspmoscnr(uint val){
	fill_csr_bits(val,REG_INFO.mosdetcspmoscnr());	//CSR43[12:10]
	return *this;
}
uint
CS_clkRegs::getmosdetcspmoscnr(){
	return get_csr_bits(REG_INFO.mosdetcspmoscnr());	//CSR43[12:10]
}

CS_clkRegs&
CS_clkRegs::setmosdetcscmoscnr(uint val){
	fill_csr_bits(val,REG_INFO.mosdetcscmoscnr());	//CSR43[9:7]
	return *this;
}
uint
CS_clkRegs::getmosdetcscmoscnr(){
	return get_csr_bits(REG_INFO.mosdetcscmoscnr());	//CSR43[9:7]
}

CS_clkRegs&
CS_clkRegs::setsschopdemclkdiv(uint val){
	fill_csr_bits(val,REG_INFO.sschopdemclkdiv());	//CSR43[6:0]
	return *this;
}
uint
CS_clkRegs::getsschopdemclkdiv(){
	return get_csr_bits(REG_INFO.sschopdemclkdiv());	//CSR43[6:0]
}

CS_clkRegs&
CS_clkRegs::setrpolydetcalsel(uint val){
	fill_csr_bits(val,REG_INFO.rpolydetcalsel());	//CSR44[15:15]
	return *this;
}
uint
CS_clkRegs::getrpolydetcalsel(){
	return get_csr_bits(REG_INFO.rpolydetcalsel());	//CSR44[15:15]
}

CS_clkRegs&
CS_clkRegs::setrpolydethvrxtermcalen(uint val){
	fill_csr_bits(val,REG_INFO.rpolydethvrxtermcalen());	//CSR44[14:14]
	return *this;
}
uint
CS_clkRegs::getrpolydethvrxtermcalen(){
	return get_csr_bits(REG_INFO.rpolydethvrxtermcalen());	//CSR44[14:14]
}

CS_clkRegs&
CS_clkRegs::setrpolydetcsrxtermcal(uint val){
	fill_csr_bits(val,REG_INFO.rpolydetcsrxtermcal());	//CSR44[13:10]
	return *this;
}
uint
CS_clkRegs::getrpolydetcsrxtermcal(){
	return get_csr_bits(REG_INFO.rpolydetcsrxtermcal());	//CSR44[13:10]
}

CS_clkRegs&
CS_clkRegs::setrpolydetcsrpolycnr(uint val){
	fill_csr_bits(val,REG_INFO.rpolydetcsrpolycnr());	//CSR44[5:4]
	return *this;
}
uint
CS_clkRegs::getrpolydetcsrpolycnr(){
	return get_csr_bits(REG_INFO.rpolydetcsrpolycnr());	//CSR44[5:4]
}

CS_clkRegs&
CS_clkRegs::setssdpmsparein(uint val){
	fill_csr_bits(val,REG_INFO.ssdpmsparein());	//CSR44[3:0]
	return *this;
}
uint
CS_clkRegs::getssdpmsparein(){
	return get_csr_bits(REG_INFO.ssdpmsparein());	//CSR44[3:0]
}

CS_clkRegs&
CS_clkRegs::setssspare(uint val){
	fill_csr_bits(val,REG_INFO.ssspare());	//CSR45[15:0]
	return *this;
}
uint
CS_clkRegs::getssspare(){
	return get_csr_bits(REG_INFO.ssspare());	//CSR45[15:0]
}

CS_clkRegs&
CS_clkRegs::setssatbsel(uint val){
	fill_csr_bits(val,REG_INFO.ssatbsel());	//CSR46[14:12]
	return *this;
}
uint
CS_clkRegs::getssatbsel(){
	return get_csr_bits(REG_INFO.ssatbsel());	//CSR46[14:12]
}

CS_clkRegs&
CS_clkRegs::setrefclkreceiveratbsel(uint val){
	fill_csr_bits(val,REG_INFO.refclkreceiveratbsel());	//CSR46[11:6]
	return *this;
}
uint
CS_clkRegs::getrefclkreceiveratbsel(){
	return get_csr_bits(REG_INFO.refclkreceiveratbsel());	//CSR46[11:6]
}

CS_clkRegs&
CS_clkRegs::setbiasmstratbsel(uint val){
	fill_csr_bits(val,REG_INFO.biasmstratbsel());	//CSR46[5:0]
	return *this;
}
uint
CS_clkRegs::getbiasmstratbsel(){
	return get_csr_bits(REG_INFO.biasmstratbsel());	//CSR46[5:0]
}

CS_clkRegs&
CS_clkRegs::settsensorhvatbsel(uint val){
	fill_csr_bits(val,REG_INFO.tsensorhvatbsel());	//CSR47[12:11]
	return *this;
}
uint
CS_clkRegs::gettsensorhvatbsel(){
	return get_csr_bits(REG_INFO.tsensorhvatbsel());	//CSR47[12:11]
}

CS_clkRegs&
CS_clkRegs::setsscompatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.sscompatbctrl());	//CSR47[10:8]
	return *this;
}
uint
CS_clkRegs::getsscompatbctrl(){
	return get_csr_bits(REG_INFO.sscompatbctrl());	//CSR47[10:8]
}

CS_clkRegs&
CS_clkRegs::settopvcofsm2ndpassen(uint val){
	fill_csr_bits(val,REG_INFO.topvcofsm2ndpassen());	//CSR47[5:5]
	return *this;
}
uint
CS_clkRegs::gettopvcofsm2ndpassen(){
	return get_csr_bits(REG_INFO.topvcofsm2ndpassen());	//CSR47[5:5]
}

CS_clkRegs&
CS_clkRegs::setfirstpassitankbypass(uint val){
	fill_csr_bits(val,REG_INFO.firstpassitankbypass());	//CSR47[4:4]
	return *this;
}
uint
CS_clkRegs::getfirstpassitankbypass(){
	return get_csr_bits(REG_INFO.firstpassitankbypass());	//CSR47[4:4]
}

CS_clkRegs&
CS_clkRegs::setfddiffavemodesel(uint val){
	fill_csr_bits(val,REG_INFO.fddiffavemodesel());	//CSR47[3:3]
	return *this;
}
uint
CS_clkRegs::getfddiffavemodesel(){
	return get_csr_bits(REG_INFO.fddiffavemodesel());	//CSR47[3:3]
}

CS_clkRegs&
CS_clkRegs::setfreqcalprefsel(uint val){
	fill_csr_bits(val,REG_INFO.freqcalprefsel());	//CSR47[2:2]
	return *this;
}
uint
CS_clkRegs::getfreqcalprefsel(){
	return get_csr_bits(REG_INFO.freqcalprefsel());	//CSR47[2:2]
}

CS_clkRegs&
CS_clkRegs::setbandselprefsel(uint val){
	fill_csr_bits(val,REG_INFO.bandselprefsel());	//CSR47[1:1]
	return *this;
}
uint
CS_clkRegs::getbandselprefsel(){
	return get_csr_bits(REG_INFO.bandselprefsel());	//CSR47[1:1]
}

CS_clkRegs&
CS_clkRegs::setexitonthreshold(uint val){
	fill_csr_bits(val,REG_INFO.exitonthreshold());	//CSR47[0:0]
	return *this;
}
uint
CS_clkRegs::getexitonthreshold(){
	return get_csr_bits(REG_INFO.exitonthreshold());	//CSR47[0:0]
}

CS_clkRegs&
CS_clkRegs::setssdpmatbsel(uint val){
	fill_csr_bits(val,REG_INFO.ssdpmatbsel());	//CSR48[15:13]
	return *this;
}
uint
CS_clkRegs::getssdpmatbsel(){
	return get_csr_bits(REG_INFO.ssdpmatbsel());	//CSR48[15:13]
}

CS_clkRegs&
CS_clkRegs::setmosdetvgsatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.mosdetvgsatbctrl());	//CSR48[8:6]
	return *this;
}
uint
CS_clkRegs::getmosdetvgsatbctrl(){
	return get_csr_bits(REG_INFO.mosdetvgsatbctrl());	//CSR48[8:6]
}

CS_clkRegs&
CS_clkRegs::setmosdetoscatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.mosdetoscatbctrl());	//CSR48[5:3]
	return *this;
}
uint
CS_clkRegs::getmosdetoscatbctrl(){
	return get_csr_bits(REG_INFO.mosdetoscatbctrl());	//CSR48[5:3]
}

CS_clkRegs&
CS_clkRegs::setrpolydethvatbctrl(uint val){
	fill_csr_bits(val,REG_INFO.rpolydethvatbctrl());	//CSR48[2:0]
	return *this;
}
uint
CS_clkRegs::getrpolydethvatbctrl(){
	return get_csr_bits(REG_INFO.rpolydethvatbctrl());	//CSR48[2:0]
}

CS_clkRegs&
CS_clkRegs::setadccompclkprediv(uint val){
	fill_csr_bits(val,REG_INFO.adccompclkprediv());	//CSR49[14:8]
	return *this;
}
uint
CS_clkRegs::getadccompclkprediv(){
	return get_csr_bits(REG_INFO.adccompclkprediv());	//CSR49[14:8]
}

CS_clkRegs&
CS_clkRegs::setcsadcclkdiv(uint val){
	fill_csr_bits(val,REG_INFO.csadcclkdiv());	//CSR49[7:5]
	return *this;
}
uint
CS_clkRegs::getcsadcclkdiv(){
	return get_csr_bits(REG_INFO.csadcclkdiv());	//CSR49[7:5]
}

CS_clkRegs&
CS_clkRegs::setcscompclkdiv(uint val){
	fill_csr_bits(val,REG_INFO.cscompclkdiv());	//CSR49[4:2]
	return *this;
}
uint
CS_clkRegs::getcscompclkdiv(){
	return get_csr_bits(REG_INFO.cscompclkdiv());	//CSR49[4:2]
}

CS_clkRegs&
CS_clkRegs::setcsdfdeadbandsel(uint val){
	fill_csr_bits(val,REG_INFO.csdfdeadbandsel());	//CSR49[1:0]
	return *this;
}
uint
CS_clkRegs::getcsdfdeadbandsel(){
	return get_csr_bits(REG_INFO.csdfdeadbandsel());	//CSR49[1:0]
}

CS_clkRegs&
CS_clkRegs::setcsdecmfactor(uint val){
	fill_csr_bits(val,REG_INFO.csdecmfactor());	//CSR50[15:14]
	return *this;
}
uint
CS_clkRegs::getcsdecmfactor(){
	return get_csr_bits(REG_INFO.csdecmfactor());	//CSR50[15:14]
}

CS_clkRegs&
CS_clkRegs::setcsadcconvmode(uint val){
	fill_csr_bits(val,REG_INFO.csadcconvmode());	//CSR50[13:13]
	return *this;
}
uint
CS_clkRegs::getcsadcconvmode(){
	return get_csr_bits(REG_INFO.csadcconvmode());	//CSR50[13:13]
}

CS_clkRegs&
CS_clkRegs::setcsdforder(uint val){
	fill_csr_bits(val,REG_INFO.csdforder());	//CSR50[12:12]
	return *this;
}
uint
CS_clkRegs::getcsdforder(){
	return get_csr_bits(REG_INFO.csdforder());	//CSR50[12:12]
}

CS_clkRegs&
CS_clkRegs::setcsdfrefcode(uint val){
	fill_csr_bits(val,REG_INFO.csdfrefcode());	//CSR50[11:0]
	return *this;
}
uint
CS_clkRegs::getcsdfrefcode(){
	return get_csr_bits(REG_INFO.csdfrefcode());	//CSR50[11:0]
}

uint
CS_clkRegs::getcsdfrdy(){
	return get_csr_bits(REG_INFO.csdfrdy());	//CSR51[15:15]
}

uint
CS_clkRegs::getcsdfcompstatus(){
	return get_csr_bits(REG_INFO.csdfcompstatus());	//CSR51[14:14]
}

uint
CS_clkRegs::getcsdfcompstatusdbm(){
	return get_csr_bits(REG_INFO.csdfcompstatusdbm());	//CSR51[13:13]
}

uint
CS_clkRegs::getcsdfcompstatusdbp(){
	return get_csr_bits(REG_INFO.csdfcompstatusdbp());	//CSR51[12:12]
}

uint
CS_clkRegs::getcsdfdata(){
	return get_csr_bits(REG_INFO.csdfdata());	//CSR51[11:0]
}

CS_clkRegs&
CS_clkRegs::setcsdfautotimervalue(uint val){
	fill_csr_bits(val,REG_INFO.csdfautotimervalue());	//CSR52[11:10]
	return *this;
}
uint
CS_clkRegs::getcsdfautotimervalue(){
	return get_csr_bits(REG_INFO.csdfautotimervalue());	//CSR52[11:10]
}

CS_clkRegs&
CS_clkRegs::setssdfautotimervalue(uint val){
	fill_csr_bits(val,REG_INFO.ssdfautotimervalue());	//CSR52[9:8]
	return *this;
}
uint
CS_clkRegs::getssdfautotimervalue(){
	return get_csr_bits(REG_INFO.ssdfautotimervalue());	//CSR52[9:8]
}

CS_clkRegs&
CS_clkRegs::setssadcclkdiv(uint val){
	fill_csr_bits(val,REG_INFO.ssadcclkdiv());	//CSR52[7:5]
	return *this;
}
uint
CS_clkRegs::getssadcclkdiv(){
	return get_csr_bits(REG_INFO.ssadcclkdiv());	//CSR52[7:5]
}

CS_clkRegs&
CS_clkRegs::setsscompclkdiv(uint val){
	fill_csr_bits(val,REG_INFO.sscompclkdiv());	//CSR52[4:2]
	return *this;
}
uint
CS_clkRegs::getsscompclkdiv(){
	return get_csr_bits(REG_INFO.sscompclkdiv());	//CSR52[4:2]
}

CS_clkRegs&
CS_clkRegs::setssdfdeadbandsel(uint val){
	fill_csr_bits(val,REG_INFO.ssdfdeadbandsel());	//CSR52[1:0]
	return *this;
}
uint
CS_clkRegs::getssdfdeadbandsel(){
	return get_csr_bits(REG_INFO.ssdfdeadbandsel());	//CSR52[1:0]
}

CS_clkRegs&
CS_clkRegs::setssdecmfactor(uint val){
	fill_csr_bits(val,REG_INFO.ssdecmfactor());	//CSR53[15:14]
	return *this;
}
uint
CS_clkRegs::getssdecmfactor(){
	return get_csr_bits(REG_INFO.ssdecmfactor());	//CSR53[15:14]
}

CS_clkRegs&
CS_clkRegs::setssadcconvmode(uint val){
	fill_csr_bits(val,REG_INFO.ssadcconvmode());	//CSR53[13:13]
	return *this;
}
uint
CS_clkRegs::getssadcconvmode(){
	return get_csr_bits(REG_INFO.ssadcconvmode());	//CSR53[13:13]
}

CS_clkRegs&
CS_clkRegs::setssdforder(uint val){
	fill_csr_bits(val,REG_INFO.ssdforder());	//CSR53[12:12]
	return *this;
}
uint
CS_clkRegs::getssdforder(){
	return get_csr_bits(REG_INFO.ssdforder());	//CSR53[12:12]
}

CS_clkRegs&
CS_clkRegs::setssdfrefcode(uint val){
	fill_csr_bits(val,REG_INFO.ssdfrefcode());	//CSR53[11:0]
	return *this;
}
uint
CS_clkRegs::getssdfrefcode(){
	return get_csr_bits(REG_INFO.ssdfrefcode());	//CSR53[11:0]
}

uint
CS_clkRegs::getssdfrdy(){
	return get_csr_bits(REG_INFO.ssdfrdy());	//CSR54[15:15]
}

uint
CS_clkRegs::getssdfcompstatus(){
	return get_csr_bits(REG_INFO.ssdfcompstatus());	//CSR54[14:14]
}

uint
CS_clkRegs::getssdfcompstatusdbm(){
	return get_csr_bits(REG_INFO.ssdfcompstatusdbm());	//CSR54[13:13]
}

uint
CS_clkRegs::getssdfcompstatusdbp(){
	return get_csr_bits(REG_INFO.ssdfcompstatusdbp());	//CSR54[12:12]
}

uint
CS_clkRegs::getssdfdata(){
	return get_csr_bits(REG_INFO.ssdfdata());	//CSR54[11:0]
}

CS_clkRegs&
CS_clkRegs::setringvcorefclkdiv(uint val){
	fill_csr_bits(val,REG_INFO.ringvcorefclkdiv());	//CSR55[15:8]
	return *this;
}
uint
CS_clkRegs::getringvcorefclkdiv(){
	return get_csr_bits(REG_INFO.ringvcorefclkdiv());	//CSR55[15:8]
}

CS_clkRegs&
CS_clkRegs::setringvcofdclkdiv(uint val){
	fill_csr_bits(val,REG_INFO.ringvcofdclkdiv());	//CSR55[4:0]
	return *this;
}
uint
CS_clkRegs::getringvcofdclkdiv(){
	return get_csr_bits(REG_INFO.ringvcofdclkdiv());	//CSR55[4:0]
}

uint
CS_clkRegs::getdpmnmoscnr(){
	return get_csr_bits(REG_INFO.dpmnmoscnr());	//CSR56[15:13]
}

uint
CS_clkRegs::getdpmpmoscnr(){
	return get_csr_bits(REG_INFO.dpmpmoscnr());	//CSR56[12:10]
}

uint
CS_clkRegs::getdpmcmoscnr(){
	return get_csr_bits(REG_INFO.dpmcmoscnr());	//CSR56[9:7]
}

uint
CS_clkRegs::getdpmtemperature(){
	return get_csr_bits(REG_INFO.dpmtemperature());	//CSR56[6:4]
}

uint
CS_clkRegs::getdpmrxtermcal(){
	return get_csr_bits(REG_INFO.dpmrxtermcal());	//CSR57[13:10]
}

uint
CS_clkRegs::getdpmspare(){
	return get_csr_bits(REG_INFO.dpmspare());	//CSR57[9:6]
}

uint
CS_clkRegs::getdpmrpolycnr(){
	return get_csr_bits(REG_INFO.dpmrpolycnr());	//CSR57[5:4]
}

uint
CS_clkRegs::getssdpmspareout(){
	return get_csr_bits(REG_INFO.ssdpmspareout());	//CSR57[3:0]
}

CS_clkRegs&
CS_clkRegs::setcstopfsm_cal_start(uint val){
	fill_csr_bits(val,REG_INFO.cstopfsm_cal_start());	//CSR58[15:15]
	return *this;
}
uint
CS_clkRegs::getcstopfsm_cal_start(){
	return get_csr_bits(REG_INFO.cstopfsm_cal_start());	//CSR58[15:15]
}

CS_clkRegs&
CS_clkRegs::setdpmfinetuneen(uint val){
	fill_csr_bits(val,REG_INFO.dpmfinetuneen());	//CSR58[14:14]
	return *this;
}
uint
CS_clkRegs::getdpmfinetuneen(){
	return get_csr_bits(REG_INFO.dpmfinetuneen());	//CSR58[14:14]
}

CS_clkRegs&
CS_clkRegs::setcstopfsm_cal_task_sel(uint val){
	fill_csr_bits(val,REG_INFO.cstopfsm_cal_task_sel());	//CSR58[13:0]
	return *this;
}
uint
CS_clkRegs::getcstopfsm_cal_task_sel(){
	return get_csr_bits(REG_INFO.cstopfsm_cal_task_sel());	//CSR58[13:0]
}

uint
CS_clkRegs::getcstopfsm_cal_done(){
	return get_csr_bits(REG_INFO.cstopfsm_cal_done());	//CSR59[15:15]
}

uint
CS_clkRegs::getdpmfinetunerdy(){
	return get_csr_bits(REG_INFO.dpmfinetunerdy());	//CSR59[14:14]
}

uint
CS_clkRegs::getcstopfsm_cal_task_status(){
	return get_csr_bits(REG_INFO.cstopfsm_cal_task_status());	//CSR59[13:0]
}

CS_clkRegs&
CS_clkRegs::setpll0vregpllcompvref(uint val){
	fill_csr_bits(val,REG_INFO.pll0vregpllcompvref());	//CSR60[11:6]
	return *this;
}
uint
CS_clkRegs::getpll0vregpllcompvref(){
	return get_csr_bits(REG_INFO.pll0vregpllcompvref());	//CSR60[11:6]
}

CS_clkRegs&
CS_clkRegs::setpll1vregpllcompvref(uint val){
	fill_csr_bits(val,REG_INFO.pll1vregpllcompvref());	//CSR60[5:0]
	return *this;
}
uint
CS_clkRegs::getpll1vregpllcompvref(){
	return get_csr_bits(REG_INFO.pll1vregpllcompvref());	//CSR60[5:0]
}

CS_clkRegs&
CS_clkRegs::setpll0vregdlfcompvref(uint val){
	fill_csr_bits(val,REG_INFO.pll0vregdlfcompvref());	//CSR61[11:6]
	return *this;
}
uint
CS_clkRegs::getpll0vregdlfcompvref(){
	return get_csr_bits(REG_INFO.pll0vregdlfcompvref());	//CSR61[11:6]
}

CS_clkRegs&
CS_clkRegs::setpll1vregdlfcompvref(uint val){
	fill_csr_bits(val,REG_INFO.pll1vregdlfcompvref());	//CSR61[5:0]
	return *this;
}
uint
CS_clkRegs::getpll1vregdlfcompvref(){
	return get_csr_bits(REG_INFO.pll1vregdlfcompvref());	//CSR61[5:0]
}

CS_clkRegs&
CS_clkRegs::setpll0vregvcodivcompvref(uint val){
	fill_csr_bits(val,REG_INFO.pll0vregvcodivcompvref());	//CSR62[11:6]
	return *this;
}
uint
CS_clkRegs::getpll0vregvcodivcompvref(){
	return get_csr_bits(REG_INFO.pll0vregvcodivcompvref());	//CSR62[11:6]
}

CS_clkRegs&
CS_clkRegs::setpll1vregvcodivcompvref(uint val){
	fill_csr_bits(val,REG_INFO.pll1vregvcodivcompvref());	//CSR62[5:0]
	return *this;
}
uint
CS_clkRegs::getpll1vregvcodivcompvref(){
	return get_csr_bits(REG_INFO.pll1vregvcodivcompvref());	//CSR62[5:0]
}

CS_clkRegs&
CS_clkRegs::setpll0vregcpvrefcompvref(uint val){
	fill_csr_bits(val,REG_INFO.pll0vregcpvrefcompvref());	//CSR63[11:6]
	return *this;
}
uint
CS_clkRegs::getpll0vregcpvrefcompvref(){
	return get_csr_bits(REG_INFO.pll0vregcpvrefcompvref());	//CSR63[11:6]
}

CS_clkRegs&
CS_clkRegs::setpll1vregcpvrefcompvref(uint val){
	fill_csr_bits(val,REG_INFO.pll1vregcpvrefcompvref());	//CSR63[5:0]
	return *this;
}
uint
CS_clkRegs::getpll1vregcpvrefcompvref(){
	return get_csr_bits(REG_INFO.pll1vregcpvrefcompvref());	//CSR63[5:0]
}
E_HILINK_REGISTER_TYPE CS_clkRegs::getType()
{
	return HILINK_PERMACRO_REGISTER;
}
