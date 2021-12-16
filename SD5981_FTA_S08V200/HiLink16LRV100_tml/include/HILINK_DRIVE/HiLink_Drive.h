/*
 * HiLink_Drive.h
 *
 *  Created on: Aug 19, 2016
 *      Author: yanfen.fang
 */

#ifndef HILINK_DRIVE_H_
#define HILINK_DRIVE_H_

#include <HILINK_DRIVE/MacroLaneCtrl.h>
#include <Common_Func/System_Common_Func.h>


//TODO: configure for your own HILINK IP
#if 1
typedef HILINK_Regs_Base HILINK16_Regs;



#include "HiLink_CP_apiRegs.h"
#include "HiLink_CS_clkRegs.h"
#include "HiLink_DS_clkRegs.h"
#include "HiLink_DS_rxRegs.h"
#include "HiLink_DS_txRegs.h"


struct HILINK_CS{
	CS_clkRegs& clkRegs;
};
const extern struct HILINK_CS CS;


struct HILINK_MCU{
	CP_apiRegs& mcuRegs;
};
const extern struct HILINK_MCU MCU;


struct HILINK_DS{
	DS_rxRegs& rxRegs;
	DS_txRegs& txRegs;
	DS_clkRegs& clkRegs;
	void Broadcast() const{
		rxRegs.SliceID(0).Broadcast(1);
		txRegs.SliceID(0).Broadcast(1);
		clkRegs.SliceID(0).Broadcast(1);
		hout(REG_ACCESS) << "******* DS Broadcast Enable *******" << endl;
	}
	void Unicast() const{
		rxRegs.Broadcast(0);
		txRegs.Broadcast(0);
		clkRegs.Broadcast(0);
	}
};

extern struct HILINK_DS DS;


struct HILINK_DEVICE{
	const struct HILINK_CS& CS;
	const struct HILINK_MCU& MCU;
	const struct HILINK_DS& DS;
};

extern struct HILINK_DEVICE HiLink16;


#endif

#endif /* HILINK_DRIVE_H_ */
