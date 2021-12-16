/*
 * HiLink_Drive.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: Jason
 */


#include <Common_Func/HiLink30_Common_Func.h>

#if 1
struct HILINK_DS DS={
			DS_rxRegs::getInstance(),
			DS_rxextRegs::getInstance(),
			DS_txRegs::getInstance(),
			DS_clkRegs::getInstance()
		};

struct HILINK_SRAM SRAM={
			CS_apiRegs::getInstance(),
			TOP_apiRegs::getInstance(),
			DS_apiRegs::getInstance(),
			ABIST_apiRegs::getInstance(),
			CP_apiRegs::getInstance()
		};


const struct HILINK_CS CS={
		CS_clkRegs::getInstance(),
		CSDBG_clkRegs::getInstance()
};



const struct HILINK_CP CP={CP_apiRegs::getInstance()};


#endif

SITE_PASSFAIL_RESULT::SITE_PASSFAIL_RESULT(){
	eachsite.init(false);
}

SITE_PASSFAIL_RESULT::~SITE_PASSFAIL_RESULT(){

}

void
SITE_PASSFAIL_RESULT::init(bool value){
	eachsite.init(value);
}

bool
SITE_PASSFAIL_RESULT::isAllSitePassed(){
	bool result=true;
//	FOR_EACH_SITE_BEGIN();
//		uint SiteID=CURRENT_SITE_NUMBER()-1;
//		if(!eachsite[SiteID]){
//			result = false;
//		}
//	FOR_EACH_SITE_END();
	return result;
}

bool
SITE_PASSFAIL_RESULT::isAllSiteFailed(){
	bool result=true;
//	FOR_EACH_SITE_BEGIN();
//		uint SiteID=CURRENT_SITE_NUMBER()-1;
//		if(eachsite[SiteID]){
//			result = false;
//		}
//	FOR_EACH_SITE_END();
	return result;
}

bool&
SITE_PASSFAIL_RESULT::operator[](uint SiteID){
	return eachsite[SiteID];
}

SITE_PASSFAIL_RESULT&
SITE_PASSFAIL_RESULT::operator&=(SITE_PASSFAIL_RESULT& that){
//	FOR_EACH_SITE_BEGIN();
//		uint SiteID=CURRENT_SITE_NUMBER()-1;
//		eachsite[SiteID] = eachsite[SiteID] && that[SiteID];
//	FOR_EACH_SITE_END();
	return *this;
}

