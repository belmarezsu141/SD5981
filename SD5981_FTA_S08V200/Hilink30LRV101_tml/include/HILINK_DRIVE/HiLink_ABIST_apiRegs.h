#ifndef HILINKABISTAPIREGS_H_
#define HILINKABISTAPIREGS_H_

#include <HILINK_DRIVE/HiLink_Regs_Base.h>
#define ABIST_API_CSR_NUM 8

class ABIST_apiRegs:public HILINK_Regs_Base{
protected:
	ABIST_apiRegs();
	virtual ~ABIST_apiRegs();

	uint& get_csr(uint csrIndex);
	virtual void get_default_MacroLaneID(T_MacroLaneID& id);

public:
	bool get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos);
	static ABIST_apiRegs& getInstance();
	string getName();
	uint getCSRCount();
	E_HILINK_REGISTER_TYPE getType();
	uint get_HILINK_MAX_LANE_NUM();
	uint getAddressMapToHiLink(int csrIndex);

///////////////////////////////////////////////////////////////////////////

private:
	class _REG_INFO{
		public:

	/// 0:disable, 1:enable
			const T_REG_INFO_EX& vco_lock_range_abist_api();	//CSR0[15:15]

	/// 0:disable, 1:enable
			const T_REG_INFO_EX& vco_lock_robustness_static_abist_api();	//CSR0[14:14]

	/// 0:disable, 1:enable
			const T_REG_INFO_EX& vco_lock_robustness_dynamic_abist_api();	//CSR0[13:13]

	/// 0:disable, 1:enable
			const T_REG_INFO_EX& vco_band_freq_range_abist_api();	//CSR0[12:12]

	/// 0:disable, 1:enable
			const T_REG_INFO_EX& tx2rx_outer_lpbk_clk_purity_wcdr_abist_api();	//CSR0[11:11]

	/// 0:disable, 1:enable
			const T_REG_INFO_EX& tx2rx_outer_lpbk_clk_purity_wocdr_abist_api();	//CSR0[10:10]

	/// 0:disable, 1:enable
			const T_REG_INFO_EX& tx2rx_outer_lpbk_prbs_stress_abist_api();	//CSR0[9:9]

	/// 0:disable, 1:enable
			const T_REG_INFO_EX& tx2rx_predriver_lpbk_clk_purity_wcdr_abist_api();	//CSR0[8:8]

	/// 0:disable, 1:enable
			const T_REG_INFO_EX& tx2rx_predriver_lpbk_prbs_stress_abist_api();	//CSR0[7:7]

	/// 0:disable, 1:enable
			const T_REG_INFO_EX& tx2rx_bumpdriver_lpbk_prbs_abist_api();	//CSR0[6:6]

	/// 0:disable, 1:enable
			const T_REG_INFO_EX& corner_sensor_abist_api();	//CSR0[5:5]

	/// 0:disable, 1:enable
			const T_REG_INFO_EX& fir_dc_abist_api();	//CSR0[4:4]

	/// 0:disable, 1:enable
			const T_REG_INFO_EX& atb_abist_api();	//CSR0[3:3]

	/// 0:disable, 1:enable
			const T_REG_INFO_EX& calib_register_check_abist_api();	//CSR0[2:2]

	/// 0:disable, 1:enable
			const T_REG_INFO_EX& ctle_dc_gain_abist_api();	//CSR0[1:1]

	/// 0:disable, 1:enable
			const T_REG_INFO_EX& latch_ofst_abist_api();	//CSR0[0:0]

	/// 0:disable, 1:enable
			const T_REG_INFO_EX& alphagen_sweep_abist_api();	//CSR1[15:15]

	/// 0:disable, 1:enable
			const T_REG_INFO_EX& regulator_sweep_abist_api();	//CSR1[14:14]

	/// 0:disable, 1:enable
			const T_REG_INFO_EX& dfe_idac_sweep_abist_api();	//CSR1[13:13]
	/// 0:disable, 1:enable
			const T_REG_INFO_EX& adc_stability_abist_api();	//CSR1[12:12]
	/// Spare
			const T_REG_INFO_EX& dlos_abist_api();	//CSR1[11:11]

	/// Spare
			const T_REG_INFO_EX& abist_ctrl1_spare9to0();	//CSR1[10:10]

	/// Spare
			const T_REG_INFO_EX& comparator_abist_api();	//CSR1[9:0]

	/// 00: Full; 
	/// 01: Simplified Mode0
	/// 10: Simplified Mode1
	/// 11: Simplified Mode2
			const T_REG_INFO_EX& test_mode_abist_api();	//CSR2[15:14]
	/// Spare
			const T_REG_INFO_EX& adc_stability_ss_adc_bypass_api();	//CSR2[13:13]

	/// Spare
			const T_REG_INFO_EX& adc_stability_cs_adc_bypass_api();	//CSR2[12:12]

	/// Spare
			const T_REG_INFO_EX& adc_stability_ds_adc_bypass_api();	//CSR2[11:11]

	/// Spare
			const T_REG_INFO_EX& adc_stability_adc_loop_cnt_api();	//CSR2[10:8]

	/// Spare
			const T_REG_INFO_EX& adc_stability_ref_vol_mode_api();	//CSR2[7:6]


	/// Spare
			const T_REG_INFO_EX& abist_ctrl2_spare5to0();	//CSR2[5:0]

	/// Spare
			const T_REG_INFO_EX& abist_ctrl3_spare15to0();	//CSR3[15:0]

	/// 0: something wrong with the spec in fw; 1: PASS
			const T_REG_INFO_EX& vco_lock_range_status_abist_api();	//CSR4[15:15]

	/// 0: something wrong with the spec in fw; 1: PASS
			const T_REG_INFO_EX& vco_lock_robustness_static_status_abist_api();	//CSR4[14:14]

	/// 0: something wrong with the spec in fw; 1: PASS
			const T_REG_INFO_EX& vco_lock_robustness_dynamic_status_abist_api();	//CSR4[13:13]

	/// 0: something wrong with the spec in fw; 1: PASS
			const T_REG_INFO_EX& vco_band_freq_range_status_abist_api();	//CSR4[12:12]

	/// 0: something wrong with the spec in fw; 1: PASS
			const T_REG_INFO_EX& tx2rx_outer_lpbk_clk_purity_wcdr_status_abist_api();	//CSR4[11:11]

	/// 0: something wrong with the spec in fw; 1: PASS
			const T_REG_INFO_EX& tx2rx_outer_lpbk_clk_purity_wocdr_status_abist_api();	//CSR4[10:10]

	/// 0: something wrong with the spec in fw; 1: PASS
			const T_REG_INFO_EX& tx2rx_outer_lpbk_prbs_stress_status_abist_api();	//CSR4[9:9]

	/// 0: something wrong with the spec in fw; 1: PASS
			const T_REG_INFO_EX& tx2rx_predriver_lpbk_clk_purity_wcdr_status_abist_api();	//CSR4[8:8]

	/// 0: something wrong with the spec in fw; 1: PASS
			const T_REG_INFO_EX& tx2rx_predriver_lpbk_prbs_stress_status_abist_api();	//CSR4[7:7]

	/// 0: something wrong with the spec in fw; 1: PASS
			const T_REG_INFO_EX& tx2rx_bumpdriver_lpbk_prbs_status_abist_api();	//CSR4[6:6]

	/// 0: something wrong with the spec in fw; 1: PASS
			const T_REG_INFO_EX& corner_sensor_status_abist_api();	//CSR4[5:5]

	/// 0: something wrong with the spec in fw; 1: PASS
			const T_REG_INFO_EX& fir_dc_status_abist_api();	//CSR4[4:4]

	/// 0: something wrong with the spec in fw; 1: PASS
			const T_REG_INFO_EX& atb_status_abist_api();	//CSR4[3:3]

	/// 0: something wrong with the spec in fw; 1: PASS
			const T_REG_INFO_EX& calib_register_check_status_abist_api();	//CSR4[2:2]

	/// 0: something wrong with the spec in fw; 1: PASS
			const T_REG_INFO_EX& ctle_dc_gain_status_abist_api();	//CSR4[1:1]

	/// 0: something wrong with the spec in fw; 1: PASS
			const T_REG_INFO_EX& latch_ofst_status_abist_api();	//CSR4[0:0]

	/// 0: something wrong with the spec in fw; 1: PASS
			const T_REG_INFO_EX& alphagen_sweep_status_abist_api();	//CSR5[15:15]

	/// 0: something wrong with the spec in fw; 1: PASS
			const T_REG_INFO_EX& regulator_sweep_status_abist_api();	//CSR5[14:14]

	/// 0: something wrong with the spec in fw; 1: PASS
			const T_REG_INFO_EX& dfe_idac_sweep_status_abist_api();	//CSR5[13:13]

	/// Spare
			const T_REG_INFO_EX& adc_stability_status_abist_api();	//CSR5[12:12]

	/// Spare
			const T_REG_INFO_EX& dlos_status_abist_api();	//CSR5[11:11]

	/// Spare
			const T_REG_INFO_EX& comparator_status_abist_api();	//CSR5[10:10]

	/// Spare
			const T_REG_INFO_EX& abist_status1_spare9to0();	//CSR5[9:0]

	/// ABIST Top FSM state
			const T_REG_INFO_EX& top_fsm_abist_api();	//CSR6[15:8]

	/// ABIST Sub0 FSM state
			const T_REG_INFO_EX& sub0_fsm_abist_api();	//CSR6[7:0]

	/// ABIST Sub1 FSM state
			const T_REG_INFO_EX& sub1_fsm_abist_api();	//CSR7[15:8]

	/// ABIST Sub2 FSM state
			const T_REG_INFO_EX& sub2_fsm_abist_api();	//CSR7[7:0]
			bool get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos);
	};
public:
	_REG_INFO REG_INFO;

	uint csr[ABIST_API_CSR_NUM];


	//CSR0[15:15]
	ABIST_apiRegs& setvco_lock_range_abist_api(uint val);
	uint getvco_lock_range_abist_api();

	//CSR0[14:14]
	ABIST_apiRegs& setvco_lock_robustness_static_abist_api(uint val);
	uint getvco_lock_robustness_static_abist_api();

	//CSR0[13:13]
	ABIST_apiRegs& setvco_lock_robustness_dynamic_abist_api(uint val);
	uint getvco_lock_robustness_dynamic_abist_api();

	//CSR0[12:12]
	ABIST_apiRegs& setvco_band_freq_range_abist_api(uint val);
	uint getvco_band_freq_range_abist_api();

	//CSR0[11:11]
	ABIST_apiRegs& settx2rx_outer_lpbk_clk_purity_wcdr_abist_api(uint val);
	uint gettx2rx_outer_lpbk_clk_purity_wcdr_abist_api();

	//CSR0[10:10]
	ABIST_apiRegs& settx2rx_outer_lpbk_clk_purity_wocdr_abist_api(uint val);
	uint gettx2rx_outer_lpbk_clk_purity_wocdr_abist_api();

	//CSR0[9:9]
	ABIST_apiRegs& settx2rx_outer_lpbk_prbs_stress_abist_api(uint val);
	uint gettx2rx_outer_lpbk_prbs_stress_abist_api();

	//CSR0[8:8]
	ABIST_apiRegs& settx2rx_predriver_lpbk_clk_purity_wcdr_abist_api(uint val);
	uint gettx2rx_predriver_lpbk_clk_purity_wcdr_abist_api();

	//CSR0[7:7]
	ABIST_apiRegs& settx2rx_predriver_lpbk_prbs_stress_abist_api(uint val);
	uint gettx2rx_predriver_lpbk_prbs_stress_abist_api();

	//CSR0[6:6]
	ABIST_apiRegs& settx2rx_bumpdriver_lpbk_prbs_abist_api(uint val);
	uint gettx2rx_bumpdriver_lpbk_prbs_abist_api();

	//CSR0[5:5]
	ABIST_apiRegs& setcorner_sensor_abist_api(uint val);
	uint getcorner_sensor_abist_api();

	//CSR0[4:4]
	ABIST_apiRegs& setfir_dc_abist_api(uint val);
	uint getfir_dc_abist_api();

	//CSR0[3:3]
	ABIST_apiRegs& setatb_abist_api(uint val);
	uint getatb_abist_api();

	//CSR0[2:2]
	ABIST_apiRegs& setcalib_register_check_abist_api(uint val);
	uint getcalib_register_check_abist_api();

	//CSR0[1:1]
	ABIST_apiRegs& setctle_dc_gain_abist_api(uint val);
	uint getctle_dc_gain_abist_api();

	//CSR0[0:0]
	ABIST_apiRegs& setlatch_ofst_abist_api(uint val);
	uint getlatch_ofst_abist_api();

	//CSR1[15:15]
	ABIST_apiRegs& setalphagen_sweep_abist_api(uint val);
	uint getalphagen_sweep_abist_api();

	//CSR1[14:14]
	ABIST_apiRegs& setregulator_sweep_abist_api(uint val);
	uint getregulator_sweep_abist_api();

	//CSR1[13:13]
	ABIST_apiRegs& setdfe_idac_sweep_abist_api(uint val);
	uint getdfe_idac_sweep_abist_api();


	//CSR1[12:12]
	ABIST_apiRegs& setadc_stability_abist_api(uint val);
	uint getadc_stability_abist_api();

	//CSR1[11:11]
	ABIST_apiRegs& setdlos_abist_api(uint val);
	uint getdlos_abist_api();

	//CSR1[10:10]
	ABIST_apiRegs& setcomparator_abist_api(uint val);
	uint getcomparator_abist_api();

	//CSR1[9:0]
	ABIST_apiRegs& setabist_ctrl1_spare9to0(uint val);
	uint getabist_ctrl1_spare9to0();

	//CSR2[15:14]
	ABIST_apiRegs& settest_mode_abist_api(uint val);
	uint gettest_mode_abist_api();

	//CSR2[13:13]
	ABIST_apiRegs& setadc_stability_ss_adc_bypass_api(uint val);
	uint getadc_stability_ss_adc_bypass_api();

	//CSR2[12:12]
	ABIST_apiRegs& setadc_stability_cs_adc_bypass_api(uint val);
	uint getadc_stability_cs_adc_bypass_api();

	//CSR2[11:11]
	ABIST_apiRegs& setadc_stability_ds_adc_bypass_api(uint val);
	uint getadc_stability_ds_adc_bypass_api();

	//CSR2[10:8]
	ABIST_apiRegs& setadc_stability_adc_loop_cnt_api(uint val);
	uint getadc_stability_adc_loop_cnt_api();

	//CSR2[7:6]
	ABIST_apiRegs& setadc_stability_ref_vol_mode_api(uint val);
	uint getadc_stability_ref_vol_mode_api();

	//CSR2[5:0]
	ABIST_apiRegs& setabist_ctrl2_spare5to0(uint val);
	uint getabist_ctrl2_spare5to0();

	//CSR3[15:0]
	ABIST_apiRegs& setabist_ctrl3_spare15to0(uint val);
	uint getabist_ctrl3_spare15to0();

	//CSR4[15:15]
	ABIST_apiRegs& setvco_lock_range_status_abist_api(uint val);
	uint getvco_lock_range_status_abist_api();

	//CSR4[14:14]
	ABIST_apiRegs& setvco_lock_robustness_static_status_abist_api(uint val);
	uint getvco_lock_robustness_static_status_abist_api();

	//CSR4[13:13]
	ABIST_apiRegs& setvco_lock_robustness_dynamic_status_abist_api(uint val);
	uint getvco_lock_robustness_dynamic_status_abist_api();

	//CSR4[12:12]
	ABIST_apiRegs& setvco_band_freq_range_status_abist_api(uint val);
	uint getvco_band_freq_range_status_abist_api();

	//CSR4[11:11]
	ABIST_apiRegs& settx2rx_outer_lpbk_clk_purity_wcdr_status_abist_api(uint val);
	uint gettx2rx_outer_lpbk_clk_purity_wcdr_status_abist_api();

	//CSR4[10:10]
	ABIST_apiRegs& settx2rx_outer_lpbk_clk_purity_wocdr_status_abist_api(uint val);
	uint gettx2rx_outer_lpbk_clk_purity_wocdr_status_abist_api();

	//CSR4[9:9]
	ABIST_apiRegs& settx2rx_outer_lpbk_prbs_stress_status_abist_api(uint val);
	uint gettx2rx_outer_lpbk_prbs_stress_status_abist_api();

	//CSR4[8:8]
	ABIST_apiRegs& settx2rx_predriver_lpbk_clk_purity_wcdr_status_abist_api(uint val);
	uint gettx2rx_predriver_lpbk_clk_purity_wcdr_status_abist_api();

	//CSR4[7:7]
	ABIST_apiRegs& settx2rx_predriver_lpbk_prbs_stress_status_abist_api(uint val);
	uint gettx2rx_predriver_lpbk_prbs_stress_status_abist_api();

	//CSR4[6:6]
	ABIST_apiRegs& settx2rx_bumpdriver_lpbk_prbs_status_abist_api(uint val);
	uint gettx2rx_bumpdriver_lpbk_prbs_status_abist_api();

	//CSR4[5:5]
	ABIST_apiRegs& setcorner_sensor_status_abist_api(uint val);
	uint getcorner_sensor_status_abist_api();

	//CSR4[4:4]
	ABIST_apiRegs& setfir_dc_status_abist_api(uint val);
	uint getfir_dc_status_abist_api();

	//CSR4[3:3]
	ABIST_apiRegs& setatb_status_abist_api(uint val);
	uint getatb_status_abist_api();

	//CSR4[2:2]
	ABIST_apiRegs& setcalib_register_check_status_abist_api(uint val);
	uint getcalib_register_check_status_abist_api();

	//CSR4[1:1]
	ABIST_apiRegs& setctle_dc_gain_status_abist_api(uint val);
	uint getctle_dc_gain_status_abist_api();

	//CSR4[0:0]
	ABIST_apiRegs& setlatch_ofst_status_abist_api(uint val);
	uint getlatch_ofst_status_abist_api();

	//CSR5[15:15]
	ABIST_apiRegs& setalphagen_sweep_status_abist_api(uint val);
	uint getalphagen_sweep_status_abist_api();

	//CSR5[14:14]
	ABIST_apiRegs& setregulator_sweep_status_abist_api(uint val);
	uint getregulator_sweep_status_abist_api();

	//CSR5[13:13]
	ABIST_apiRegs& setdfe_idac_sweep_status_abist_api(uint val);
	uint getdfe_idac_sweep_status_abist_api();

	//CSR5[12:12]
	ABIST_apiRegs& setadc_stability_status_abist_api(uint val);
	uint getadc_stability_status_abist_api();

	//CSR5[11:11]
	ABIST_apiRegs& setdlos_status_abist_api(uint val);
	uint getdlos_status_abist_api();

	//CSR5[10:10]
	ABIST_apiRegs& setcomparator_status_abist_api(uint val);
	uint getcomparator_status_abist_api();

	//CSR5[9:0]
	ABIST_apiRegs& setabist_status1_spare9to0(uint val);
	uint getabist_status1_spare9to0();

	//CSR6[15:8]
	ABIST_apiRegs& settop_fsm_abist_api(uint val);
	uint gettop_fsm_abist_api();

	//CSR6[7:0]
	ABIST_apiRegs& setsub0_fsm_abist_api(uint val);
	uint getsub0_fsm_abist_api();

	//CSR7[15:8]
	ABIST_apiRegs& setsub1_fsm_abist_api(uint val);
	uint getsub1_fsm_abist_api();

	//CSR7[7:0]
	ABIST_apiRegs& setsub2_fsm_abist_api(uint val);
	uint getsub2_fsm_abist_api();

};

#endif // HILINKABISTAPIREGS_H_
