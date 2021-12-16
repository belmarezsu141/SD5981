/*
 * HiLink_Drive.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: Jason
 */

#include <HILINK_DRIVE/HiLink_Drive.h>


struct HILINK_DS DS={
			DS_rxRegs::getInstance(),
			DS_txRegs::getInstance(),
			DS_clkRegs::getInstance()
		};

const struct HILINK_CS CS={CS_clkRegs::getInstance()};

const struct HILINK_MCU MCU={CP_apiRegs::getInstance()};

struct HILINK_DEVICE HiLink16 = {CS,MCU,DS};

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
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		if(!eachsite[SiteID]){
			result = false;
		}
	FOREACH_ACTIVESITE_END
	return result;
}

bool
SITE_PASSFAIL_RESULT::isAllSiteFailed(){
	bool result=true;
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		if(eachsite[SiteID]){
			result = false;
		}
	FOREACH_ACTIVESITE_END
	return result;
}

bool&
SITE_PASSFAIL_RESULT::operator[](uint SiteID){
	return eachsite[SiteID];
}

SITE_PASSFAIL_RESULT&
SITE_PASSFAIL_RESULT::operator&=(SITE_PASSFAIL_RESULT& that){
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		eachsite[SiteID] = eachsite[SiteID] && that[SiteID];
	FOREACH_ACTIVESITE_END
	return *this;
}
