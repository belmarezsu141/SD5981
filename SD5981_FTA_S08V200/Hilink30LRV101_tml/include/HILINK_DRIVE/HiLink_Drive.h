/*
 * HiLink_Drive.h
 *
 *  Created on: Aug 19, 2016
 *      Author: yanfen.fang
 */

#ifndef HILINK_DRIVE_H_
#define HILINK_DRIVE_H_

#include <Common_Func/System_Common_Func.h>
#include <HILINK_DRIVE/MacroLaneCtrl.h>


//TODO: configure for your own HILINK IP
#if 1
typedef HILINK_Regs_Base HILINK30_Regs;

#include <HILINK_DRIVE/HiLink_DS_rxRegs.h>
#include <HILINK_DRIVE/HiLink_DS_rxextRegs.h>
#include <HILINK_DRIVE/HiLink_DS_txRegs.h>
#include <HILINK_DRIVE/HiLink_DS_clkRegs.h>

#include <HILINK_DRIVE/HiLink_CS_clkRegs.h>
#include <HILINK_DRIVE/HiLink_CSDBG_clkRegs.h>

#include <HILINK_DRIVE/HiLink_CP_apiRegs.h>
#include <HILINK_DRIVE/HiLink_CS_apiRegs.h>
#include <HILINK_DRIVE/HiLink_DS_apiRegs.h>
#include <HILINK_DRIVE/HiLink_ABIST_apiRegs.h>
#include <HILINK_DRIVE/HiLink_TOP_apiRegs.h>

struct HILINK_DS{
	DS_rxRegs& rxRegs;
	DS_rxextRegs& rxExtRegs;
	DS_txRegs& txRegs;
	DS_clkRegs& clkRegs;
	void Broadcast() const{
		rxRegs.SliceID(0).Broadcast(1);
		rxExtRegs.SliceID(0).Broadcast(1);
		txRegs.SliceID(0).Broadcast(1);
		clkRegs.SliceID(0).Broadcast(1);

	}
	// best to add .MacroID()
//	void Unicast() const{
//		rxRegs.SliceID(0).Broadcast(0);
//		rxextRegs.SliceID(0).Broadcast(0);
//		txRegs.SliceID(0).Broadcast(0);
//		clkRegs.SliceID(0).Broadcast(0);
//	}
};

extern struct HILINK_DS DS;

struct HILINK_CS{
	CS_clkRegs& clkRegs;
	CSDBG_clkRegs& clkdebug;
};
const extern struct HILINK_CS CS;



struct HILINK_CP{
	CP_apiRegs& apiRegs;
};
const extern struct HILINK_CP CP;

struct HILINK_SRAM
{
	CS_apiRegs& CSAPIRegs;
	TOP_apiRegs& TOPAPIRegs;
	DS_apiRegs&  DSAPIRegs;
	ABIST_apiRegs&  ABISTAPIRegs;
	CP_apiRegs& CPAPIRegs;
};

extern struct HILINK_SRAM SRAM;

typedef struct{
	bool 	 allpass;
	bool 	 allfail;
	ARRAY_I  eachsite;
}	EXPECT_RESULT;
#endif

#endif /* HILINK_DRIVE_H_ */
