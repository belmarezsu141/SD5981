/*
 * MacroLaneCtrl.h
 *
 *  Created on: Aug 19, 2016
 *      Author: yanfen.fang
 */

#ifndef MACROLANECTRL_H_
#define MACROLANECTRL_H_
#include <api.h>

#include <HILINK_DRIVE/HiLink_Common_Types.h>
typedef int INT;

void selectMacro(INT macroid);
void selectMacro_MB(const MACRO_LANE_SEL& MacroLane_Sel);

void pred2s_selectMacro(INT macroid);
void pred2s_selectMacro_MB(const MACRO_LANE_SEL& MacroLane_Sel);


void csr_check_selectMacro(INT macroid);
void csr_check_selectMacro_MB(const MACRO_LANE_SEL& MacroLane_Sel);
void sync_CSR_selectMacro_MB(const MACRO_LANE_SEL& MacroLane_Sel) ;
void selectMacro_Now(INT macroid);
void selectMacro_Now_MB(const MACRO_LANE_SEL& MacroLane_Sel);
void Select_Macro_Lane(MACRO_LANE_SEL& sel,const STRING& macrolist,const STRING& pinlist = "");
void Select_Macro_Lane(MACRO_LANE_SEL& sel,const vector<string>& list);


#endif /* MACROLANECTRL_H_ */
