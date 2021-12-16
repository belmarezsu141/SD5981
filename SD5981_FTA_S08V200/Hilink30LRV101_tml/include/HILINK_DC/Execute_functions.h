/*
 * Execute_functions.h
 *
 *  Created on: 2021年7月30日
 *      Author: KF106
 */

#ifndef INCLUDE_EXECUTE_FUNCTIONS_H_
#define INCLUDE_EXECUTE_FUNCTIONS_H_
#include <DataType/PinArrayData.h>

int PowerUpCtrl_test1();
int Init_test1();
int Init_test2();
int H30_Disconnect_TX_RX_DZ();
int H30LR_Rx_setupN();
int HILINK_R01_HI6871V110A_PowerUpSeqCtrl_ALL_REF1();

PinArrayDouble H30LR_RxDiffBefCAL_ForceP();
PinArrayDouble H30LR_RxDiffAftCAL_ForceP();
PinArrayDouble H30LR_RxdiffResBefCal_FVMI();
PinArrayDouble H30LR_RxDiffResBefCal_MforceV_MI_RX();
PinArrayDouble H30LR_RxSigAftCAL_ForceAll();
PinArrayDouble H30LR_RxSigResBefCal_FIMV_1mA();
PinArrayDouble H30LR_RxSigResBefCal_FIMV_5mA();
PinArrayDouble H30LR_RxTermVoltToGnd_AC_FIMV_0mA();
PinArrayDouble H30LR_TxResAftCal_FIMV_3mA();
PinArrayDouble H30LR_TxResAftCal_FIMV_4mA();
PinArrayDouble H30LR_TxTermVolt_MForce_I_0mA();
PinArrayDouble H30LR_FIR_MForce_I_N0P1UA();
PinArrayDouble H30_PWR_DC();


#endif /* INCLUDE_EXECUTE_FUNCTIONS_H_ */
