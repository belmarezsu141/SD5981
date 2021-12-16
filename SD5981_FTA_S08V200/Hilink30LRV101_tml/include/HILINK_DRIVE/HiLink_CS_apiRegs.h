#ifndef HILINKCSAPIREGS_H_
#define HILINKCSAPIREGS_H_

#include <HILINK_DRIVE/HiLink_Regs_Base.h>
#define CS_API_CSR_NUM 12

class CS_apiRegs:public HILINK_Regs_Base{
protected:
	CS_apiRegs();
	virtual ~CS_apiRegs();

	uint& get_csr(uint csrIndex);
	virtual void get_default_MacroLaneID(T_MacroLaneID& id);

public:
	bool get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos);
	static CS_apiRegs& getInstance();
	string getName();
	uint getCSRCount();
	E_HILINK_REGISTER_TYPE getType();
	uint get_HILINK_MAX_LANE_NUM();
	uint getAddressMapToHiLink(int csrIndex);

///////////////////////////////////////////////////////////////////////////

private:
	class _REG_INFO{
		public:

	/// CS Calibration enable, used with cs calibration bypass control
			const T_REG_INFO_EX& cs_calib_en_api();	//CSR0[15:15]

	/// DEBUG - Halt after single step 
			const T_REG_INFO_EX& cs_haltsinglestep_api();	//CSR0[14:14]

	/// DEBUG - Halt after state change 
			const T_REG_INFO_EX& cs_haltstatechange_api();	//CSR0[13:13]

	/// DEBUG - Halt all CS execution
			const T_REG_INFO_EX& cs_haltimmediately_api();	//CSR0[12:12]

	/// The external pin value
			const T_REG_INFO_EX& core_clk_selext_pin_api();	//CSR0[11:11]

	/// The external pin value
			const T_REG_INFO_EX& core_clk_sel_pin_api();	//CSR0[10:10]

	/// The external pin value
			const T_REG_INFO_EX& lifeclk2dig_sel_pin_api();	//CSR0[9:9]

	/// simple calibration for re-doing calibration to save time. (ATE ONLY)
	/// 1: Wirte previous calibration results back to chip
	/// 0: disable
			const T_REG_INFO_EX& cs_write_back_ctrl_api();	//CSR0[8:8]

	/// The index number of Dataslice on the north side of Clockslice.
			const T_REG_INFO_EX& ds_index_north_cs_api();	//CSR0[7:4]

	/// Spare for CS control
			const T_REG_INFO_EX& cs_ctrl0_spare3to0();	//CSR0[3:0]

	/// Frequency of refclk0 in MHz multiply by 100
			const T_REG_INFO_EX& refclk0_freqm100_api();	//CSR1[15:0]

	/// Frequency of refclk1 in MHz multiply by 100
			const T_REG_INFO_EX& refclk1_freqm100_api();	//CSR2[15:0]

	/// Spare for CS control
			const T_REG_INFO_EX& cs_ctrl3_spare15to15();	//CSR3[15:15]

	/// CS re-calibration enable, active high and will be self clear after calibration done.
			const T_REG_INFO_EX& cs_recalib_en_api();	//CSR3[14:14]

	/// calibration bypass control.  0:not bypass   1:bypass 
			const T_REG_INFO_EX& pll1vcodivvregcalbypass_api();	//CSR3[13:13]

	/// calibration bypass control.  0:not bypass   1:bypass 
			const T_REG_INFO_EX& pll1cpvrefcalbypass_api();	//CSR3[12:12]

	/// calibration bypass control.  0:not bypass   1:bypass 
			const T_REG_INFO_EX& pll1dlfvregcalbypass_api();	//CSR3[11:11]

	/// calibration bypass control.  0:not bypass   1:bypass 
			const T_REG_INFO_EX& pll1pllvregcalbypass_api();	//CSR3[10:10]

	/// calibration bypass control.  0:not bypass   1:bypass 
			const T_REG_INFO_EX& pll1vcocalbypass_api();	//CSR3[9:9]

	/// calibration bypass control.  0:not bypass   1:bypass 
			const T_REG_INFO_EX& pll0vcodivvregcalbypass_api();	//CSR3[8:8]

	/// calibration bypass control.  0:not bypass   1:bypass 
			const T_REG_INFO_EX& pll0cpvrefcalbypass_api();	//CSR3[7:7]

	/// calibration bypass control.  0:not bypass   1:bypass 
			const T_REG_INFO_EX& pll0dlfvregcalbypass_api();	//CSR3[6:6]

	/// calibration bypass control.  0:not bypass   1:bypass 
			const T_REG_INFO_EX& pll0pllvregcalbypass_api();	//CSR3[5:5]

	/// calibration bypass control.  0:not bypass   1:bypass 
			const T_REG_INFO_EX& pll0vcocalbypass_api();	//CSR3[4:4]

	/// calibration bypass control.  0:not bypass   1:bypass 
			const T_REG_INFO_EX& csvrefgencalbypass_api();	//CSR3[3:3]

	/// calibration bypass control.  0:not bypass   1:bypass 
			const T_REG_INFO_EX& csrxtermcalbypass_api();	//CSR3[2:2]

	/// calibration bypass control.  0:not bypass   1:bypass 
			const T_REG_INFO_EX& csbandgapcalbypass_api();	//CSR3[1:1]

	/// calibration bypass control.  0:not bypass   1:bypass 
			const T_REG_INFO_EX& csgetdpminfobypass_api();	//CSR3[0:0]

	/// cs dpm enable. 1:enable  0:disable
			const T_REG_INFO_EX& pll1vcoitank_dpm_en_api();	//CSR4[15:15]

	/// cs dpm enable. 1:enable  0:disable
			const T_REG_INFO_EX& pll0vcoitank_dpm_en_api();	//CSR4[14:14]

	/// cs dpm enable. 1:enable  0:disable
			const T_REG_INFO_EX& pll1vcodivvreg_dpm_en_api();	//CSR4[13:13]

	/// cs dpm enable. 1:enable  0:disable
			const T_REG_INFO_EX& pll1cpvref_dpm_en_api();	//CSR4[12:12]

	/// cs dpm enable. 1:enable  0:disable
			const T_REG_INFO_EX& pll1pllvreg_dpm_en_api();	//CSR4[11:11]

	/// cs dpm enable. 1:enable  0:disable
			const T_REG_INFO_EX& pll1dlfvreg_dpm_en_api();	//CSR4[10:10]

	/// cs dpm enable. 1:enable  0:disable
			const T_REG_INFO_EX& pll0vcodivvreg_dpm_en_api();	//CSR4[9:9]

	/// cs dpm enable. 1:enable  0:disable
			const T_REG_INFO_EX& pll0cpvref_dpm_en_api();	//CSR4[8:8]

	/// cs dpm enable. 1:enable  0:disable
			const T_REG_INFO_EX& pll0pllvreg_dpm_en_api();	//CSR4[7:7]

	/// cs dpm enable. 1:enable  0:disable
			const T_REG_INFO_EX& pll0dlfvreg_dpm_en_api();	//CSR4[6:6]

	/// cs dpm enable. 1:enable  0:disable
			const T_REG_INFO_EX& temprature_dpm_en_api();	//CSR4[5:5]

	/// cs dpm enable. 1:enable  0:disable
			const T_REG_INFO_EX& pmoscornre_dpm_en_api();	//CSR4[4:4]

	/// cs dpm enable. 1:enable  0:disable
			const T_REG_INFO_EX& nmoscornre_dpm_en_api();	//CSR4[3:3]

	/// cs dpm enable. 1:enable  0:disable
			const T_REG_INFO_EX& cs_dpm_en_api();	//CSR4[2:2]

	/// 0:not switch to mclk at the end of cs calibration.
	/// 1:switch to mclk automatically
			const T_REG_INFO_EX& coreclk_sel_en_api();	//CSR4[1:1]

	/// Spare for CS control
			const T_REG_INFO_EX& cs_ctrl4_spare0to0();	//CSR4[0:0]


			const T_REG_INFO_EX& pll0dlfvreg_ofst_api();	//CSR5[15:12]


			const T_REG_INFO_EX& pll0pllvreg_ofst_api();	//CSR5[11:8]


			const T_REG_INFO_EX& pll0vcodivvreg_ofst_api();	//CSR5[7:4]


			const T_REG_INFO_EX& pll0itankvreg_ofst_api();	//CSR5[3:0]


			const T_REG_INFO_EX& pll1dlfvreg_ofst_api();	//CSR6[15:12]


			const T_REG_INFO_EX& pll1pllvreg_ofst_api();	//CSR6[11:8]


			const T_REG_INFO_EX& pll1vcodivvreg_ofst_api();	//CSR6[7:4]


			const T_REG_INFO_EX& pll1itankvreg_ofst_api();	//CSR6[3:0]


			const T_REG_INFO_EX& dsclkvreg_ofst_api();	//CSR7[15:12]


			const T_REG_INFO_EX& txpredrvreg_ofst_api();	//CSR7[11:8]


			const T_REG_INFO_EX& rxdatavreg_ofst_api();	//CSR7[7:4]


			const T_REG_INFO_EX& cs_ctrl7_spare3to1();	//CSR7[3:1]			
			

			const T_REG_INFO_EX& regulator_offset_en_api();	//CSR7[0:0]
			
			/// CS Top FSM state
	/// 0 = Clockslice calibration FSM initial
	/// 1 = Clockslice calibration handling
	/// 3 = Clockslice calibration done
			const T_REG_INFO_EX& cs_top_fsm_api();	//CSR8[15:8]

	/// cs sub fsm state
	/// 0 = CS calibration initial 
	/// 1 = SS bandgap buffer offset calibration initial 
	/// 2 = SS bandgap buffer offset calibration excusive 
	/// 3 = SS bandgap buffer offset calibration adjustment 
	/// 4 = SS rpoly resistance calibration initial 
	/// 5 = SS rpoly resistance calibration excusive 
	/// 6 = SS rpoly resistance calibration adjustment 
	/// 7 = Get temperature 
	/// 8 = CS comparator vrefgen offset calibration initial 
	/// 9 = CS comparator vrefgen offset calibration excusive 
	/// 10 = CS comparator vrefgen offset calibration adjustment 
	/// 11 = CS regulators calibration initial 
	/// 12 = CS regulators calibration excusive 
	/// 13 = CS regulators calibration adjustment 
	/// 14 = CS PLL0 VCO calibration 
	/// 15 = CS PLL1 VCO calibration 
	/// 16 = CS calibration adjustment 
	/// 16 = CS calibration done
			const T_REG_INFO_EX& cs_sub0_fsm_api();	//CSR8[7:0]

	/// CS sub-sub FMS state
			const T_REG_INFO_EX& cs_sub1_fsm_api();	//CSR9[15:8]

	/// CS sub-sub-sub FSM state
			const T_REG_INFO_EX& cs_sub2_fsm_api();	//CSR9[7:0]

	/// spare for CS status
			const T_REG_INFO_EX& cs_stat2_spare15to0();	//CSR10[15:0]

	/// spare for CS status
			const T_REG_INFO_EX& cs_stat3_spare15to0();	//CSR11[15:0]
			bool get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos);
	};
public:
	_REG_INFO REG_INFO;

	uint csr[CS_API_CSR_NUM];


	//CSR0[15:15]
	CS_apiRegs& setcs_calib_en_api(uint val);
	uint getcs_calib_en_api();

	//CSR0[14:14]
	CS_apiRegs& setcs_haltsinglestep_api(uint val);
	uint getcs_haltsinglestep_api();

	//CSR0[13:13]
	CS_apiRegs& setcs_haltstatechange_api(uint val);
	uint getcs_haltstatechange_api();

	//CSR0[12:12]
	CS_apiRegs& setcs_haltimmediately_api(uint val);
	uint getcs_haltimmediately_api();

	//CSR0[11:11]
	CS_apiRegs& setcore_clk_selext_pin_api(uint val);
	uint getcore_clk_selext_pin_api();

	//CSR0[10:10]
	CS_apiRegs& setcore_clk_sel_pin_api(uint val);
	uint getcore_clk_sel_pin_api();

	//CSR0[9:9]
	CS_apiRegs& setlifeclk2dig_sel_pin_api(uint val);
	uint getlifeclk2dig_sel_pin_api();

	//CSR0[8:8]
	CS_apiRegs& setcs_write_back_ctrl_api(uint val);
	uint getcs_write_back_ctrl_api();

	//CSR0[7:4]
	CS_apiRegs& setds_index_north_cs_api(uint val);
	uint getds_index_north_cs_api();

	//CSR0[3:0]
	CS_apiRegs& setcs_ctrl0_spare3to0(uint val);
	uint getcs_ctrl0_spare3to0();

	//CSR1[15:0]
	CS_apiRegs& setrefclk0_freqm100_api(uint val);
	uint getrefclk0_freqm100_api();

	//CSR2[15:0]
	CS_apiRegs& setrefclk1_freqm100_api(uint val);
	uint getrefclk1_freqm100_api();

	//CSR3[15:15]
	CS_apiRegs& setcs_ctrl3_spare15to15(uint val);
	uint getcs_ctrl3_spare15to15();

	//CSR3[14:14]
	CS_apiRegs& setcs_recalib_en_api(uint val);
	uint getcs_recalib_en_api();

	//CSR3[13:13]
	CS_apiRegs& setpll1vcodivvregcalbypass_api(uint val);
	uint getpll1vcodivvregcalbypass_api();

	//CSR3[12:12]
	CS_apiRegs& setpll1cpvrefcalbypass_api(uint val);
	uint getpll1cpvrefcalbypass_api();

	//CSR3[11:11]
	CS_apiRegs& setpll1dlfvregcalbypass_api(uint val);
	uint getpll1dlfvregcalbypass_api();

	//CSR3[10:10]
	CS_apiRegs& setpll1pllvregcalbypass_api(uint val);
	uint getpll1pllvregcalbypass_api();

	//CSR3[9:9]
	CS_apiRegs& setpll1vcocalbypass_api(uint val);
	uint getpll1vcocalbypass_api();

	//CSR3[8:8]
	CS_apiRegs& setpll0vcodivvregcalbypass_api(uint val);
	uint getpll0vcodivvregcalbypass_api();

	//CSR3[7:7]
	CS_apiRegs& setpll0cpvrefcalbypass_api(uint val);
	uint getpll0cpvrefcalbypass_api();

	//CSR3[6:6]
	CS_apiRegs& setpll0dlfvregcalbypass_api(uint val);
	uint getpll0dlfvregcalbypass_api();

	//CSR3[5:5]
	CS_apiRegs& setpll0pllvregcalbypass_api(uint val);
	uint getpll0pllvregcalbypass_api();

	//CSR3[4:4]
	CS_apiRegs& setpll0vcocalbypass_api(uint val);
	uint getpll0vcocalbypass_api();

	//CSR3[3:3]
	CS_apiRegs& setcsvrefgencalbypass_api(uint val);
	uint getcsvrefgencalbypass_api();

	//CSR3[2:2]
	CS_apiRegs& setcsrxtermcalbypass_api(uint val);
	uint getcsrxtermcalbypass_api();

	//CSR3[1:1]
	CS_apiRegs& setcsbandgapcalbypass_api(uint val);
	uint getcsbandgapcalbypass_api();

	//CSR3[0:0]
	CS_apiRegs& setcsgetdpminfobypass_api(uint val);
	uint getcsgetdpminfobypass_api();

	//CSR4[15:15]
	CS_apiRegs& setpll1vcoitank_dpm_en_api(uint val);
	uint getpll1vcoitank_dpm_en_api();

	//CSR4[14:14]
	CS_apiRegs& setpll0vcoitank_dpm_en_api(uint val);
	uint getpll0vcoitank_dpm_en_api();

	//CSR4[13:13]
	CS_apiRegs& setpll1vcodivvreg_dpm_en_api(uint val);
	uint getpll1vcodivvreg_dpm_en_api();

	//CSR4[12:12]
	CS_apiRegs& setpll1cpvref_dpm_en_api(uint val);
	uint getpll1cpvref_dpm_en_api();

	//CSR4[11:11]
	CS_apiRegs& setpll1pllvreg_dpm_en_api(uint val);
	uint getpll1pllvreg_dpm_en_api();

	//CSR4[10:10]
	CS_apiRegs& setpll1dlfvreg_dpm_en_api(uint val);
	uint getpll1dlfvreg_dpm_en_api();

	//CSR4[9:9]
	CS_apiRegs& setpll0vcodivvreg_dpm_en_api(uint val);
	uint getpll0vcodivvreg_dpm_en_api();

	//CSR4[8:8]
	CS_apiRegs& setpll0cpvref_dpm_en_api(uint val);
	uint getpll0cpvref_dpm_en_api();

	//CSR4[7:7]
	CS_apiRegs& setpll0pllvreg_dpm_en_api(uint val);
	uint getpll0pllvreg_dpm_en_api();

	//CSR4[6:6]
	CS_apiRegs& setpll0dlfvreg_dpm_en_api(uint val);
	uint getpll0dlfvreg_dpm_en_api();

	//CSR4[5:5]
	CS_apiRegs& settemprature_dpm_en_api(uint val);
	uint gettemprature_dpm_en_api();

	//CSR4[4:4]
	CS_apiRegs& setpmoscornre_dpm_en_api(uint val);
	uint getpmoscornre_dpm_en_api();

	//CSR4[3:3]
	CS_apiRegs& setnmoscornre_dpm_en_api(uint val);
	uint getnmoscornre_dpm_en_api();

	//CSR4[2:2]
	CS_apiRegs& setcs_dpm_en_api(uint val);
	uint getcs_dpm_en_api();

	//CSR4[1:1]
	CS_apiRegs& setcoreclk_sel_en_api(uint val);
	uint getcoreclk_sel_en_api();

	//CSR4[0:0]
	CS_apiRegs& setcs_ctrl4_spare0to0(uint val);
	uint getcs_ctrl4_spare0to0();

	//CSR5[15:12]
	CS_apiRegs& setpll0dlfvreg_ofst_api(uint val);
	uint getpll0dlfvreg_ofst_api();

	//CSR5[11:8]
	CS_apiRegs& setpll0pllvreg_ofst_api(uint val);
	uint getpll0pllvreg_ofst_api();

	//CSR5[7:4]
	CS_apiRegs& setpll0vcodivvreg_ofst_api(uint val);
	uint getpll0vcodivvreg_ofst_api();

	//CSR5[3:0]
	CS_apiRegs& setpll0itankvreg_ofst_api(uint val);
	uint getpll0itankvreg_ofst_api();

	//CSR6[15:12]
	CS_apiRegs& setpll1dlfvreg_ofst_api(uint val);
	uint getpll1dlfvreg_ofst_api();

	//CSR6[11:8]
	CS_apiRegs& setpll1pllvreg_ofst_api(uint val);
	uint getpll1pllvreg_ofst_api();

	//CSR6[7:4]
	CS_apiRegs& setpll1vcodivvreg_ofst_api(uint val);
	uint getpll1vcodivvreg_ofst_api();

	//CSR6[3:0]
	CS_apiRegs& setpll1itankvreg_ofst_api(uint val);
	uint getpll1itankvreg_ofst_api();

	//CSR7[15:12]
	CS_apiRegs& setdsclkvreg_ofst_api(uint val);
	uint getdsclkvreg_ofst_api();

	//CSR7[11:8]
	CS_apiRegs& settxpredrvreg_ofst_api(uint val);
	uint gettxpredrvreg_ofst_api();

	//CSR7[7:4]
	CS_apiRegs& setrxdatavreg_ofst_api(uint val);
	uint getrxdatavreg_ofst_api();

	//CSR7[3:1]
	CS_apiRegs& setcs_ctrl7_spare3to1(uint val);
	uint getcs_ctrl7_spare3to1();	
	
	//CSR7[0:0]
	CS_apiRegs& setregulator_offset_en_api(uint val);
	uint getregulator_offset_en_api();	
	
	//CSR8[15:8]
	CS_apiRegs& setcs_top_fsm_api(uint val);
	uint getcs_top_fsm_api();

	//CSR8[7:0]
	CS_apiRegs& setcs_sub0_fsm_api(uint val);
	uint getcs_sub0_fsm_api();

	//CSR9[15:8]
	CS_apiRegs& setcs_sub1_fsm_api(uint val);
	uint getcs_sub1_fsm_api();

	//CSR9[7:0]
	CS_apiRegs& setcs_sub2_fsm_api(uint val);
	uint getcs_sub2_fsm_api();

	//CSR10[15:0]
	CS_apiRegs& setcs_stat2_spare15to0(uint val);
	uint getcs_stat2_spare15to0();

	//CSR11[15:0]
	CS_apiRegs& setcs_stat3_spare15to0(uint val);
	uint getcs_stat3_spare15to0();

};

#endif // HILINKCSAPIREGS_H_
