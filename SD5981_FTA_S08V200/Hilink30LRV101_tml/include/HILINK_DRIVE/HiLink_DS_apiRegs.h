#ifndef HILINKDSAPIREGS_H_
#define HILINKDSAPIREGS_H_

#include <HILINK_DRIVE/HiLink_Regs_Base.h>
#define DS_API_CSR_NUM 18

class DS_apiRegs:public HILINK_Regs_Base{
protected:
	DS_apiRegs();
	virtual ~DS_apiRegs();

	uint& get_csr(uint csrIndex);
	virtual void get_default_MacroLaneID(T_MacroLaneID& id);

public:
	bool get_reg_infos(uint csrIndex,vector<T_REG_INFO>& reg_infos);
	static DS_apiRegs& getInstance();
	string getName();
	uint getCSRCount();
	E_HILINK_REGISTER_TYPE getType();
	uint get_HILINK_MAX_LANE_NUM();
	uint getAddressMapToHiLink(int csrIndex);

///////////////////////////////////////////////////////////////////////////

private:
	class _REG_INFO{
		public:

	/// Ds handling reset 
	/// 0: release ds handling
	/// 1: reset ds handling
			const T_REG_INFO_EX& ds_soft_reset_api();	//CSR0[15:15]

	/// DEBUG - Halt after single step 
			const T_REG_INFO_EX& ds_haltsinglestep_api();	//CSR0[14:14]

	/// DEBUG - Halt after state change 
			const T_REG_INFO_EX& ds_haltstatechange_api();	//CSR0[13:13]

	/// DEBUG - Halt all DS execution
			const T_REG_INFO_EX& ds_haltimmediately_api();	//CSR0[12:12]

	/// Spare for DS control
			const T_REG_INFO_EX& ds_ctrl0_spare11to8_api();	//CSR0[11:8]

	/// DS Calibration enable, used with ds calibration bypass control
			const T_REG_INFO_EX& ds_calib_en_api();	//CSR0[7:7]

	/// fast ctle enable
			const T_REG_INFO_EX& ds_fast_ctle_en_api();	//CSR0[6:6]

	/// CTLE enable (Default 1)
			const T_REG_INFO_EX& ds_ctle_en_api();	//CSR0[5:5]

	/// DFE enable (Default 1), used with dfe bypass control
			const T_REG_INFO_EX& ds_dfe_en_api();	//CSR0[4:4]

	/// Dynamic Process Monitor and dfe summer offset enable (during continuous DFE) (Default 0), used with dpm bypass control
			const T_REG_INFO_EX& ds_dpm_en_api();	//CSR0[3:3]

	/// CTLE Offset Correction Enable  (Default 0), used with offset bypass control
			const T_REG_INFO_EX& ds_offset_en_api();	//CSR0[2:2]

	/// Dataslice low power mode select.
	/// 0: Performance mode
	/// 1: SR mode
	/// 2: Debug mode
	/// 3: Normal mode
			const T_REG_INFO_EX& ds_power_mode_api();	//CSR0[1:0]

	/// the data rate of tx in Gbps, ceil of data rate
			const T_REG_INFO_EX& tx_data_rate_api();	//CSR1[15:11]

	/// spare
			const T_REG_INFO_EX& ds_ctrl1_spare10to8();	//CSR1[10:8]

	/// the data rate of rx in Gbps, ceil of data rate
			const T_REG_INFO_EX& rx_data_rate_api();	//CSR1[7:3]

	/// spare
			const T_REG_INFO_EX& ds_ctrl1_spare2to0();	//CSR1[2:0]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& dsclkvrefgencalbypass_api();	//CSR2[15:15]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& dsclkvregcalbypass_api();	//CSR2[14:14]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& rxctlevregcalbypass_api();	//CSR2[13:13]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& rxopampofstcalbypass_api();	//CSR2[12:12]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& rxsumloadrescalbypass_api();	//CSR2[11:11]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& rxclkvregcalbypass_api();	//CSR2[10:10]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& rxdatavregcalbypass_api();	//CSR2[9:9]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& rxsigdetofstcalbypass_api();	//CSR2[8:8]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& rxctleofstcalbypass_api();	//CSR2[7:7]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& rxsumofstcalbypass_api();	//CSR2[6:6]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& rxlatchofstcalbypass_api();	//CSR2[5:5]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& rxalfgenofstcalbypass_api();	//CSR2[4:4]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& txdrvregcalbypass_api();	//CSR2[3:3]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& txpredrvregcalbypass_api();	//CSR2[2:2]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& txcenterpabypass_api();	//CSR2[1:1]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& txrxserlpbkofstcalbypass_api();	//CSR2[0:0]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& txdcdcalibbypass_api();	//CSR3[15:15]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& rxctlerefcalibbypass_api();	//CSR3[14:14]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& rxctlecurrentcalibbypass_api();	//CSR3[13:13]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& lpbkdcdcalibbypass_api();	//CSR3[12:12]

	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& rxalfgenstepsizecalibbypass_api();	//CSR3[11:11]
	/// calibration bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& rxctlerefminthbypass_api();	//CSR3[10:10]		//rxctlerefminthbypass_api
	/// spare
			const T_REG_INFO_EX& ds_ctrl3_spare9to1();	//CSR3[9:1]

	/// simple calibration for re-doing calibration to save time.
	/// 1: Wirte previous calibration or ate adaptation results back to chip
	/// 0: disable
			const T_REG_INFO_EX& ds_write_back_ctrl_api();	//CSR3[0:0]

	/// REFSEL enable (Default 0)
			const T_REG_INFO_EX& ctle_refsel_en_api();	//CSR4[15:15]

	/// Zero Adjust enable (Default 0)
			const T_REG_INFO_EX& ctle_zero_adj_en_api();	//CSR4[14:14]

	/// Squelch enable (Default 0)
			const T_REG_INFO_EX& ctle_squelch_en_api();	//CSR4[13:13]

	/// Mid-Band enable (Default 0)
			const T_REG_INFO_EX& ctle_mid_band_en_api();	//CSR4[12:12]

	/// Support eee mode enable(Default 0) 
	/// 0: disable 
	/// 1: enable, check rxquietstatus and disable all register operation and pause dfe when rxquietstatus==0
			const T_REG_INFO_EX& support_eee_mode_en_api();	//CSR4[11:11]

	/// CTLE Metric. 
	/// 0 = WIDTH
	/// 1 = HEIGHT
	/// 2 = 4PT_AREA
	/// 3 = 8PT_AREA
	/// Others are reserved.
			const T_REG_INFO_EX& ctle_eye_metric_api();	//CSR4[10:8]

	/// DFE Enabled in ctle
	/// 2b'00: Disable DFE in CTLE
	/// 2b'01: Tap0-Tap1
	/// 2b'10: Tap0-Tap6
	/// 2b'11: Tap0-Tap13
			const T_REG_INFO_EX& ctle_tap_en_api();	//CSR4[7:6]

	/// 000:I Channel
	/// 001:Q Channel
	/// 010:2in1 Eye, I eye and Q eye
			const T_REG_INFO_EX& ctle_eye_type_api();	//CSR4[5:3]

	/// TBD
			const T_REG_INFO_EX& ctle_eye_avg_count_api();	//CSR4[2:0]

	/// Eye scan BER for CTLE adaptation
			const T_REG_INFO_EX& ctle_eye_contour_index_api();	//CSR5[15:12]

	/// D-Level Target cursor
	/// 0 = 160 mV
	/// 1 = 180 mV
	/// 2 = 200 mV
	/// 3 = 220 mV
	/// 4 = 240 mV
	/// 5 = 260 mV
	/// 6 = 280 mV
	/// 7 = 300 mV
			const T_REG_INFO_EX& dlev_target_api();	//CSR5[11:9]

	/// Gain Attn enable (Default 1)
			const T_REG_INFO_EX& gain_attn_en_api();	//CSR5[8:8]

	/// offset bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& dfesumofst_bypass_api();	//CSR5[7:7]

	/// offset bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& ctleofst6_bypass_api();	//CSR5[6:6]

	/// offset bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& ctleofst5_bypass_api();	//CSR5[5:5]

	/// offset bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& ctleofst4_bypass_api();	//CSR5[4:4]

	/// offset bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& ctleofst3_bypass_api();	//CSR5[3:3]

	/// offset bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& ctleofst2_bypass_api();	//CSR5[2:2]

	/// offset bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& ctleofst1_bypass_api();	//CSR5[1:1]

	/// whether to use the table combining boost and squelch during ctle or dfe.
			const T_REG_INFO_EX& ds_boost_squelch_en_api();	//CSR5[0:0]

	/// dfe bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& dfe_tap13_bypass_api();	//CSR6[15:15]

	/// dfe bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& dfe_tap12_bypass_api();	//CSR6[14:14]

	/// dfe bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& dfe_tap11_bypass_api();	//CSR6[13:13]

	/// dfe bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& dfe_tap10_bypass_api();	//CSR6[12:12]

	/// dfe bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& dfe_tap9_bypass_api();	//CSR6[11:11]

	/// dfe bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& dfe_tap8_bypass_api();	//CSR6[10:10]

	/// dfe bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& dfe_tap7_bypass_api();	//CSR6[9:9]

	/// dfe bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& dfe_tap6_bypass_api();	//CSR6[8:8]

	/// dfe bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& dfe_tap5_bypass_api();	//CSR6[7:7]

	/// dfe bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& dfe_tap4_bypass_api();	//CSR6[6:6]

	/// dfe bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& dfe_tap3_bypass_api();	//CSR6[5:5]

	/// dfe bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& dfe_tap2_bypass_api();	//CSR6[4:4]

	/// dfe bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& dfe_tap1_bypass_api();	//CSR6[3:3]

	/// dfe bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& dfe_tap0_bypass_api();	//CSR6[2:2]

	/// boost enable during dfe adaptation
			const T_REG_INFO_EX& dfe_boost_en_api();	//CSR6[1:1]

	/// squelch enable during dfe adaptation
			const T_REG_INFO_EX& dfe_squelch_en_api();	//CSR6[0:0]

	/// zero enable during dfe adaptation.
			const T_REG_INFO_EX& dfe_zero_en_api();	//CSR7[15:15]

	/// biastune enable during dfe adaptation
			const T_REG_INFO_EX& dfe_biastune_en_api();	//CSR7[14:14]

	/// DFE EYE Metric. 
	/// 0: WIDTH
	/// 1: HEIGHT
	/// 2: 4PT_AREA
	/// 3: 8PT_AREA
	/// Others are reserved.
			const T_REG_INFO_EX& dfe_eye_metric_api();	//CSR7[13:11]

	/// 000: I Channel
	/// 001: Q Channel
	/// 010: Ib
	/// 011: Qb
	/// Others are reserved.
			const T_REG_INFO_EX& dfe_eye_type_api();	//CSR7[10:8]

	/// TBD
			const T_REG_INFO_EX& ctle_dfe_with_same_priority_api();	//CSR7[7:7]

	/// TBD
			const T_REG_INFO_EX& dfe_eye_avg_count_api();	//CSR7[6:4]

	/// Eye scan BER for DFE adaptation
			const T_REG_INFO_EX& dfe_eye_contour_index_api();	//CSR7[3:0]

	/// dpm bypass control. 0:not bypass, 1:bypass
			const T_REG_INFO_EX& ds_clkreg_bypass_api();	//CSR8[15:15]

	/// dpm bypass control. 0:not bypass, 1:bypass
			const T_REG_INFO_EX& ds_txdrvreg_bypass_api();	//CSR8[14:14]

	/// dpm bypass control. 0:not bypass, 1:bypass
			const T_REG_INFO_EX& ds_txpredrvreg_bypass_api();	//CSR8[13:13]

	/// dpm bypass control. 0:not bypass, 1:bypass
			const T_REG_INFO_EX& ds_rxclkreg_bypass_api();	//CSR8[12:12]

	/// dpm bypass control. 0:not bypass, 1:bypass
			const T_REG_INFO_EX& ds_rxdatareg_bypass_api();	//CSR8[11:11]

	/// Data Centering enable (during continuous DFE)
			const T_REG_INFO_EX& centering_en_api();	//CSR8[10:10]

	/// En alos protection
			const T_REG_INFO_EX& ctle_alos_protect_en_api();	//CSR8[9:9]

	/// En eye los protection
			const T_REG_INFO_EX& ctle_eyelos_protect_en_api();	//CSR8[8:8]

	/// En bypass dfe tap1 in CTLE
			const T_REG_INFO_EX& ctle_dfetap1_bypass_en_api();	//CSR8[7:7]

	/// En alos protection
			const T_REG_INFO_EX& dfe_alos_protect_en_api();	//CSR8[6:6]

	/// En eye los protection
			const T_REG_INFO_EX& dfe_eyelos_protect_en_api();	//CSR8[5:5]

	/// En non-random data protection
			const T_REG_INFO_EX& dfe_non_random_protect_en_api();	//CSR8[4:4]

	/// Fast ctle for short and good channel. Just for outer loop back of ATE.
			const T_REG_INFO_EX& ate_ctle_en_api();	//CSR8[3:3]

	/// alphagen offset enable
			const T_REG_INFO_EX& alphagen_ofst_en_api();	//CSR8[2:2]

	/// Temperature Trigger boost enable api
	/// 0:disable 1:enable
			const T_REG_INFO_EX& ds_temp_trig_boost_en_api();	//CSR8[1:1]

	/// spare
			const T_REG_INFO_EX& ds_latch_offset_en_api();	//CSR8[0:0]

	/// Write from 0 to 1, wait until it changes to 0. 4-points eye diagram infor will be obtained. Only support full/half/Quarter rate mode.
			const T_REG_INFO_EX& fw_eye_start_api();	//CSR9[15:15]

	/// 000: I Channel
	/// 001: Q Channel
	/// 010: Ib
	/// 011: Qb
	/// Others are reserved.
			const T_REG_INFO_EX& fw_eye_type_api();	//CSR9[14:12]

	/// Data Centering aux enable (during continuous DFE)
			const T_REG_INFO_EX& ds_cenetring_aux_en_api();	//CSR9[11:10]

	/// The times of eye width scanning for ATE
	/// 00: Disable
	/// 01: 8 times avg
	/// 10: 16 times avg
	/// 11: 24 times avg
			const T_REG_INFO_EX& fw_ate_eye_width_times_api();	//CSR9[9:8]

	/// dfe bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& dfe_tap15_bypass_api();	//CSR9[7:7]

	/// dfe bypass control. 0: not bypass, 1:bypass
			const T_REG_INFO_EX& dfe_tap14_bypass_api();	//CSR9[6:6]

	/// 
			const T_REG_INFO_EX& ds_abnormal_restart_adapt_api();	//CSR9[5:5]

	/// rx training support enable  0:disable, 1: enable
			const T_REG_INFO_EX& ds_rx_train_en_api();	//CSR9[4:4]

	/// dfe run interval 
	/// 0: no interval
	/// 1:dfe run and pause time is 1:1
	/// 2:dfe run and pause time is 1:2
	/// 3:dfe run and pause time is 1:4
	/// 4:dfe run and pause time is 1:8
	/// 5:dfe run and pause time is 1:16
	/// 6:dfe run and pause time is 1:32
	/// 7:dfe run and pause time is 1:64
	/// 8:dfe run and pause time is 1:128
			const T_REG_INFO_EX& dfe_run_interval_api();	//CSR9[3:0]

	/// DFE trigger boost mode
	/// 0: normal mode
	/// 1: fast mode
			const T_REG_INFO_EX& dfe_trig_boost_mode_api();	//CSR10[15:15]

	/// Ctle latch offset enable (Default 0)
			const T_REG_INFO_EX& ctle_latchofst_en_api();	//CSR10[14:14]

	/// H30 TestChip (Default 0)
	/// 0:  ASIC
	/// 1: H30 Testchip
			const T_REG_INFO_EX& h30_testchip_api();	//CSR10[13:13]

	/// spare
			const T_REG_INFO_EX& ds_ctrl10_spare13to0();	//CSR10[12:0]

	/// spare
			const T_REG_INFO_EX& ds_ctrl11_spare15to0();	//CSR11[15:0]

	/// DS Top FSM state
			const T_REG_INFO_EX& ds_top_fsm_api();	//CSR12[15:8]

	/// DS Sub0 FSM state
			const T_REG_INFO_EX& ds_sub0_fsm_api();	//CSR12[7:0]

	/// DS Sub1 FSM state
			const T_REG_INFO_EX& ds_sub1_fsm_api();	//CSR13[15:8]

	/// DS Sub2 FSM state
			const T_REG_INFO_EX& ds_sub2_fsm_api();	//CSR13[7:0]

	/// DS Sub3 FSM state
			const T_REG_INFO_EX& ds_sub3_fsm_api();	//CSR14[15:12]

	/// DS D-Level achieved
			const T_REG_INFO_EX& dlvl_achieved_status_api();	//CSR14[11:11]

	/// DS Loss of D-Level detected
			const T_REG_INFO_EX& los_det_status_api();	//CSR14[10:10]

	/// DS Data Centering achieved
			const T_REG_INFO_EX& data_center_status_api();	//CSR14[9:9]

	/// DS CTLE done
			const T_REG_INFO_EX& ctle_done_status_api();	//CSR14[8:8]

	/// DS Adaptation Reset Done
			const T_REG_INFO_EX& ds_soft_reset_status_api();	//CSR14[7:7]

	/// DS Adaptation Reset Done
			const T_REG_INFO_EX& ds_calib_done_status_api();	//CSR14[6:6]

	/// DS Adaptation Done
			const T_REG_INFO_EX& ds_adapt_done_status_api();	//CSR14[5:5]

	/// Spare
			const T_REG_INFO_EX& ds_stat14_spare6to0();	//CSR14[4:0]

	/// eye height of 4-point eye diagram
			const T_REG_INFO_EX& fw_eye_height_api();	//CSR15[15:8]

	/// eye width of 4-point eye diagram
			const T_REG_INFO_EX& fw_eye_width_api();	//CSR15[7:0]

	/// the max eye width during ate eye width sanning
			const T_REG_INFO_EX& fw_ate_max_eye_width_api();	//CSR16[15:8]

	/// the min eye width during ate eye width sanning
			const T_REG_INFO_EX& fw_ate_min_eye_width_api();	//CSR16[7:0]

	/// spare
			const T_REG_INFO_EX& ds_stat17_spare15to0();	//CSR17[15:0]
			bool get_reg_infos(uint csr,vector<T_REG_INFO>& reg_infos);
	};
public:
	_REG_INFO REG_INFO;

	uint csr[DS_API_CSR_NUM];


	//CSR0[15:15]
	DS_apiRegs& setds_soft_reset_api(uint val);
	uint getds_soft_reset_api();

	//CSR0[14:14]
	DS_apiRegs& setds_haltsinglestep_api(uint val);
	uint getds_haltsinglestep_api();

	//CSR0[13:13]
	DS_apiRegs& setds_haltstatechange_api(uint val);
	uint getds_haltstatechange_api();

	//CSR0[12:12]
	DS_apiRegs& setds_haltimmediately_api(uint val);
	uint getds_haltimmediately_api();

	//CSR0[11:8]
	DS_apiRegs& setds_ctrl0_spare11to8_api(uint val);
	uint getds_ctrl0_spare11to8_api();

	//CSR0[7:7]
	DS_apiRegs& setds_calib_en_api(uint val);
	uint getds_calib_en_api();

	//CSR0[6:6]
	DS_apiRegs& setds_fast_ctle_en_api(uint val);
	uint getds_fast_ctle_en_api();

	//CSR0[5:5]
	DS_apiRegs& setds_ctle_en_api(uint val);
	uint getds_ctle_en_api();

	//CSR0[4:4]
	DS_apiRegs& setds_dfe_en_api(uint val);
	uint getds_dfe_en_api();

	//CSR0[3:3]
	DS_apiRegs& setds_dpm_en_api(uint val);
	uint getds_dpm_en_api();

	//CSR0[2:2]
	DS_apiRegs& setds_offset_en_api(uint val);
	uint getds_offset_en_api();

	//CSR0[1:0]
	DS_apiRegs& setds_power_mode_api(uint val);
	uint getds_power_mode_api();

	//CSR1[15:11]
	DS_apiRegs& settx_data_rate_api(uint val);
	uint gettx_data_rate_api();

	//CSR1[10:8]
	DS_apiRegs& setds_ctrl1_spare10to8(uint val);
	uint getds_ctrl1_spare10to8();

	//CSR1[7:3]
	DS_apiRegs& setrx_data_rate_api(uint val);
	uint getrx_data_rate_api();

	//CSR1[2:0]
	DS_apiRegs& setds_ctrl1_spare2to0(uint val);
	uint getds_ctrl1_spare2to0();

	//CSR2[15:15]
	DS_apiRegs& setdsclkvrefgencalbypass_api(uint val);
	uint getdsclkvrefgencalbypass_api();

	//CSR2[14:14]
	DS_apiRegs& setdsclkvregcalbypass_api(uint val);
	uint getdsclkvregcalbypass_api();

	//CSR2[13:13]
	DS_apiRegs& setrxctlevregcalbypass_api(uint val);
	uint getrxctlevregcalbypass_api();

	//CSR2[12:12]
	DS_apiRegs& setrxopampofstcalbypass_api(uint val);
	uint getrxopampofstcalbypass_api();

	//CSR2[11:11]
	DS_apiRegs& setrxsumloadrescalbypass_api(uint val);
	uint getrxsumloadrescalbypass_api();

	//CSR2[10:10]
	DS_apiRegs& setrxclkvregcalbypass_api(uint val);
	uint getrxclkvregcalbypass_api();

	//CSR2[9:9]
	DS_apiRegs& setrxdatavregcalbypass_api(uint val);
	uint getrxdatavregcalbypass_api();

	//CSR2[8:8]
	DS_apiRegs& setrxsigdetofstcalbypass_api(uint val);
	uint getrxsigdetofstcalbypass_api();

	//CSR2[7:7]
	DS_apiRegs& setrxctleofstcalbypass_api(uint val);
	uint getrxctleofstcalbypass_api();

	//CSR2[6:6]
	DS_apiRegs& setrxsumofstcalbypass_api(uint val);
	uint getrxsumofstcalbypass_api();

	//CSR2[5:5]
	DS_apiRegs& setrxlatchofstcalbypass_api(uint val);
	uint getrxlatchofstcalbypass_api();

	//CSR2[4:4]
	DS_apiRegs& setrxalfgenofstcalbypass_api(uint val);
	uint getrxalfgenofstcalbypass_api();

	//CSR2[3:3]
	DS_apiRegs& settxdrvregcalbypass_api(uint val);
	uint gettxdrvregcalbypass_api();

	//CSR2[2:2]
	DS_apiRegs& settxpredrvregcalbypass_api(uint val);
	uint gettxpredrvregcalbypass_api();

	//CSR2[1:1]
	DS_apiRegs& settxcenterpabypass_api(uint val);
	uint gettxcenterpabypass_api();

	//CSR2[0:0]
	DS_apiRegs& settxrxserlpbkofstcalbypass_api(uint val);
	uint gettxrxserlpbkofstcalbypass_api();

	//CSR3[15:15]
	DS_apiRegs& settxdcdcalibbypass_api(uint val);
	uint gettxdcdcalibbypass_api();

	//CSR3[14:14]
	DS_apiRegs& setrxctlerefcalibbypass_api(uint val);
	uint getrxctlerefcalibbypass_api();

	//CSR3[13:13]
	DS_apiRegs& setrxctlecurrentcalibbypass_api(uint val);
	uint getrxctlecurrentcalibbypass_api();

	//CSR3[12:12]
	DS_apiRegs& setlpbkdcdcalibbypass_api(uint val);
	uint getlpbkdcdcalibbypass_api();

	//CSR3[11:11]
	DS_apiRegs& setrxalfgenstepsizecalibbypass_api(uint val);
	uint getrxalfgenstepsizecalibbypass_api();
	//rxctlerefminthbypass_api
	//CSR3[10:10]
	DS_apiRegs& setrxctlerefminthbypass_api(uint val);
	uint getrxctlerefminthbypass_api();

	//CSR3[9:1]
	DS_apiRegs& setds_ctrl3_spare9to1(uint val);
	uint getds_ctrl3_spare9to1();

	//CSR3[0:0]
	DS_apiRegs& setds_write_back_ctrl_api(uint val);
	uint getds_write_back_ctrl_api();

	//CSR4[15:15]
	DS_apiRegs& setctle_refsel_en_api(uint val);
	uint getctle_refsel_en_api();

	//CSR4[14:14]
	DS_apiRegs& setctle_zero_adj_en_api(uint val);
	uint getctle_zero_adj_en_api();

	//CSR4[13:13]
	DS_apiRegs& setctle_squelch_en_api(uint val);
	uint getctle_squelch_en_api();

	//CSR4[12:12]
	DS_apiRegs& setctle_mid_band_en_api(uint val);
	uint getctle_mid_band_en_api();

	//CSR4[11:11]
	DS_apiRegs& setsupport_eee_mode_en_api(uint val);
	uint getsupport_eee_mode_en_api();

	//CSR4[10:8]
	DS_apiRegs& setctle_eye_metric_api(uint val);
	uint getctle_eye_metric_api();

	//CSR4[7:6]
	DS_apiRegs& setctle_tap_en_api(uint val);
	uint getctle_tap_en_api();

	//CSR4[5:3]
	DS_apiRegs& setctle_eye_type_api(uint val);
	uint getctle_eye_type_api();

	//CSR4[2:0]
	DS_apiRegs& setctle_eye_avg_count_api(uint val);
	uint getctle_eye_avg_count_api();

	//CSR5[15:12]
	DS_apiRegs& setctle_eye_contour_index_api(uint val);
	uint getctle_eye_contour_index_api();

	//CSR5[11:9]
	DS_apiRegs& setdlev_target_api(uint val);
	uint getdlev_target_api();

	//CSR5[8:8]
	DS_apiRegs& setgain_attn_en_api(uint val);
	uint getgain_attn_en_api();

	//CSR5[7:7]
	DS_apiRegs& setdfesumofst_bypass_api(uint val);
	uint getdfesumofst_bypass_api();

	//CSR5[6:6]
	DS_apiRegs& setctleofst6_bypass_api(uint val);
	uint getctleofst6_bypass_api();

	//CSR5[5:5]
	DS_apiRegs& setctleofst5_bypass_api(uint val);
	uint getctleofst5_bypass_api();

	//CSR5[4:4]
	DS_apiRegs& setctleofst4_bypass_api(uint val);
	uint getctleofst4_bypass_api();

	//CSR5[3:3]
	DS_apiRegs& setctleofst3_bypass_api(uint val);
	uint getctleofst3_bypass_api();

	//CSR5[2:2]
	DS_apiRegs& setctleofst2_bypass_api(uint val);
	uint getctleofst2_bypass_api();

	//CSR5[1:1]
	DS_apiRegs& setctleofst1_bypass_api(uint val);
	uint getctleofst1_bypass_api();

	//CSR5[0:0]
	DS_apiRegs& setds_boost_squelch_en_api(uint val);
	uint getds_boost_squelch_en_api();

	//CSR6[15:15]
	DS_apiRegs& setdfe_tap13_bypass_api(uint val);
	uint getdfe_tap13_bypass_api();

	//CSR6[14:14]
	DS_apiRegs& setdfe_tap12_bypass_api(uint val);
	uint getdfe_tap12_bypass_api();

	//CSR6[13:13]
	DS_apiRegs& setdfe_tap11_bypass_api(uint val);
	uint getdfe_tap11_bypass_api();

	//CSR6[12:12]
	DS_apiRegs& setdfe_tap10_bypass_api(uint val);
	uint getdfe_tap10_bypass_api();

	//CSR6[11:11]
	DS_apiRegs& setdfe_tap9_bypass_api(uint val);
	uint getdfe_tap9_bypass_api();

	//CSR6[10:10]
	DS_apiRegs& setdfe_tap8_bypass_api(uint val);
	uint getdfe_tap8_bypass_api();

	//CSR6[9:9]
	DS_apiRegs& setdfe_tap7_bypass_api(uint val);
	uint getdfe_tap7_bypass_api();

	//CSR6[8:8]
	DS_apiRegs& setdfe_tap6_bypass_api(uint val);
	uint getdfe_tap6_bypass_api();

	//CSR6[7:7]
	DS_apiRegs& setdfe_tap5_bypass_api(uint val);
	uint getdfe_tap5_bypass_api();

	//CSR6[6:6]
	DS_apiRegs& setdfe_tap4_bypass_api(uint val);
	uint getdfe_tap4_bypass_api();

	//CSR6[5:5]
	DS_apiRegs& setdfe_tap3_bypass_api(uint val);
	uint getdfe_tap3_bypass_api();

	//CSR6[4:4]
	DS_apiRegs& setdfe_tap2_bypass_api(uint val);
	uint getdfe_tap2_bypass_api();

	//CSR6[3:3]
	DS_apiRegs& setdfe_tap1_bypass_api(uint val);
	uint getdfe_tap1_bypass_api();

	//CSR6[2:2]
	DS_apiRegs& setdfe_tap0_bypass_api(uint val);
	uint getdfe_tap0_bypass_api();

	//CSR6[1:1]
	DS_apiRegs& setdfe_boost_en_api(uint val);
	uint getdfe_boost_en_api();

	//CSR6[0:0]
	DS_apiRegs& setdfe_squelch_en_api(uint val);
	uint getdfe_squelch_en_api();

	//CSR7[15:15]
	DS_apiRegs& setdfe_zero_en_api(uint val);
	uint getdfe_zero_en_api();

	//CSR7[14:14]
	DS_apiRegs& setdfe_biastune_en_api(uint val);
	uint getdfe_biastune_en_api();

	//CSR7[13:11]
	DS_apiRegs& setdfe_eye_metric_api(uint val);
	uint getdfe_eye_metric_api();

	//CSR7[10:8]
	DS_apiRegs& setdfe_eye_type_api(uint val);
	uint getdfe_eye_type_api();

	//CSR7[7:7]
	DS_apiRegs& setctle_dfe_with_same_priority_api(uint val);
	uint getctle_dfe_with_same_priority_api();

	//CSR7[6:4]
	DS_apiRegs& setdfe_eye_avg_count_api(uint val);
	uint getdfe_eye_avg_count_api();

	//CSR7[3:0]
	DS_apiRegs& setdfe_eye_contour_index_api(uint val);
	uint getdfe_eye_contour_index_api();

	//CSR8[15:15]
	DS_apiRegs& setds_clkreg_bypass_api(uint val);
	uint getds_clkreg_bypass_api();

	//CSR8[14:14]
	DS_apiRegs& setds_txdrvreg_bypass_api(uint val);
	uint getds_txdrvreg_bypass_api();

	//CSR8[13:13]
	DS_apiRegs& setds_txpredrvreg_bypass_api(uint val);
	uint getds_txpredrvreg_bypass_api();

	//CSR8[12:12]
	DS_apiRegs& setds_rxclkreg_bypass_api(uint val);
	uint getds_rxclkreg_bypass_api();

	//CSR8[11:11]
	DS_apiRegs& setds_rxdatareg_bypass_api(uint val);
	uint getds_rxdatareg_bypass_api();

	//CSR8[10:10]
	DS_apiRegs& setcentering_en_api(uint val);
	uint getcentering_en_api();

	//CSR8[9:9]
	DS_apiRegs& setctle_alos_protect_en_api(uint val);
	uint getctle_alos_protect_en_api();

	//CSR8[8:8]
	DS_apiRegs& setctle_eyelos_protect_en_api(uint val);
	uint getctle_eyelos_protect_en_api();

	//CSR8[7:7]
	DS_apiRegs& setctle_dfetap1_bypass_en_api(uint val);
	uint getctle_dfetap1_bypass_en_api();

	//CSR8[6:6]
	DS_apiRegs& setdfe_alos_protect_en_api(uint val);
	uint getdfe_alos_protect_en_api();

	//CSR8[5:5]
	DS_apiRegs& setdfe_eyelos_protect_en_api(uint val);
	uint getdfe_eyelos_protect_en_api();

	//CSR8[4:4]
	DS_apiRegs& setdfe_non_random_protect_en_api(uint val);
	uint getdfe_non_random_protect_en_api();

	//CSR8[3:3]
	DS_apiRegs& setate_ctle_en_api(uint val);
	uint getate_ctle_en_api();

	//CSR8[2:2]
	DS_apiRegs& setalphagen_ofst_en_api(uint val);
	uint getalphagen_ofst_en_api();

	//CSR8[1:1]
	DS_apiRegs& setds_temp_trig_boost_en_api(uint val);
	uint getds_temp_trig_boost_en_api();

	//CSR8[0:0]
	DS_apiRegs& setds_latch_offset_en_api(uint val);
	uint getds_latch_offset_en_api();

	//CSR9[15:15]
	DS_apiRegs& setfw_eye_start_api(uint val);
	uint getfw_eye_start_api();

	//CSR9[14:12]
	DS_apiRegs& setfw_eye_type_api(uint val);
	uint getfw_eye_type_api();

	//CSR9[11:10]
	DS_apiRegs& setds_cenetring_aux_en_api(uint val);
	uint getds_cenetring_aux_en_api();

	//CSR9[9:8]
	DS_apiRegs& setfw_ate_eye_width_times_api(uint val);
	uint getfw_ate_eye_width_times_api();

	//CSR9[7:7]
	DS_apiRegs& setdfe_tap15_bypass_api(uint val);
	uint getdfe_tap15_bypass_api();

	//CSR9[6:6]
	DS_apiRegs& setdfe_tap14_bypass_api(uint val);
	uint getdfe_tap14_bypass_api();

	//CSR9[5:5]
	DS_apiRegs& setds_abnormal_restart_adapt_api(uint val);
	uint getds_abnormal_restart_adapt_api();

	//CSR9[4:4]
	DS_apiRegs& setds_rx_train_en_api(uint val);
	uint getds_rx_train_en_api();

	//CSR9[3:0]
	DS_apiRegs& setdfe_run_interval_api(uint val);
	uint getdfe_run_interval_api();

	//CSR10[15:15]
	DS_apiRegs& setdfe_trig_boost_mode_api(uint val);
	uint getdfe_trig_boost_mode_api();

	//CSR10[14:14]
	DS_apiRegs& setctle_latchofst_en_api(uint val);
	uint getctle_latchofst_en_api();

	//CSR10[13:13]
	DS_apiRegs& seth30_testchip_api(uint val);
	uint geth30_testchip_api();

	//CSR10[12:0]
	DS_apiRegs& setds_ctrl10_spare13to0(uint val);
	uint getds_ctrl10_spare13to0();

	//CSR11[15:0]
	DS_apiRegs& setds_ctrl11_spare15to0(uint val);
	uint getds_ctrl11_spare15to0();

	//CSR12[15:8]
	DS_apiRegs& setds_top_fsm_api(uint val);
	uint getds_top_fsm_api();

	//CSR12[7:0]
	DS_apiRegs& setds_sub0_fsm_api(uint val);
	uint getds_sub0_fsm_api();

	//CSR13[15:8]
	DS_apiRegs& setds_sub1_fsm_api(uint val);
	uint getds_sub1_fsm_api();

	//CSR13[7:0]
	DS_apiRegs& setds_sub2_fsm_api(uint val);
	uint getds_sub2_fsm_api();

	//CSR14[15:12]
	DS_apiRegs& setds_sub3_fsm_api(uint val);
	uint getds_sub3_fsm_api();

	//CSR14[11:11]
	DS_apiRegs& setdlvl_achieved_status_api(uint val);
	uint getdlvl_achieved_status_api();

	//CSR14[10:10]
	DS_apiRegs& setlos_det_status_api(uint val);
	uint getlos_det_status_api();

	//CSR14[9:9]
	DS_apiRegs& setdata_center_status_api(uint val);
	uint getdata_center_status_api();

	//CSR14[8:8]
	DS_apiRegs& setctle_done_status_api(uint val);
	uint getctle_done_status_api();

	//CSR14[7:7]
	DS_apiRegs& setds_soft_reset_status_api(uint val);
	uint getds_soft_reset_status_api();

	//CSR14[6:6]
	DS_apiRegs& setds_calib_done_status_api(uint val);
	uint getds_calib_done_status_api();

	//CSR14[5:5]
	DS_apiRegs& setds_adapt_done_status_api(uint val);
	uint getds_adapt_done_status_api();

	//CSR14[4:0]
	DS_apiRegs& setds_stat14_spare6to0(uint val);
	uint getds_stat14_spare6to0();

	//CSR15[15:8]
	DS_apiRegs& setfw_eye_height_api(uint val);
	uint getfw_eye_height_api();

	//CSR15[7:0]
	DS_apiRegs& setfw_eye_width_api(uint val);
	uint getfw_eye_width_api();

	//CSR16[15:8]
	DS_apiRegs& setfw_ate_max_eye_width_api(uint val);
	uint getfw_ate_max_eye_width_api();

	//CSR16[7:0]
	DS_apiRegs& setfw_ate_min_eye_width_api(uint val);
	uint getfw_ate_min_eye_width_api();

	//CSR17[15:0]
	DS_apiRegs& setds_stat17_spare15to0(uint val);
	uint getds_stat17_spare15to0();

};

#endif // HILINKDSAPIREGS_H_
