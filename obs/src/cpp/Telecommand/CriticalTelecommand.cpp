//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// CriticalTelecommand.cpp
//
// Version	1.1
// Date		20.06.03
// Author	A. Pasetti (P&P Software), R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../System/ObsClock.h"
#include "CriticalTelecommand.h"

CriticalTelecommand::CriticalTelecommand(void) {
	reset();
}

void CriticalTelecommand::reset(void) {
    maxArmedDuration=-1;
    timeWhenArmed   =-1;
    pObsClock       =pNULL;
    isTcCritical    =CRITICAL;
    isTcArmed       =NOT_ARMED;
}

bool CriticalTelecommand::isCritical(void) {
    return isTcCritical;
}

void CriticalTelecommand::setCriticalityLevel(bool isCritical) {
    isTcCritical = isCritical;
}

bool CriticalTelecommand::isArmed(void) {
    return isTcArmed;
}

bool CriticalTelecommand::isImageValid(void) {
    return VALID;
}

void CriticalTelecommand::storeImage(void) {
    return;
}

void CriticalTelecommand::setMaxArmedDuration(TD_ObsTime t) {
    assert( t>0 );
    maxArmedDuration = t;
}

TD_ObsTime CriticalTelecommand::getMaxArmedDuration(void) {
    return maxArmedDuration;
}

TD_ObsTime CriticalTelecommand::getTimeWhenArmed(void) {
    return timeWhenArmed;
}

ObsClock* CriticalTelecommand::getObsClock(void) const {
   assert ( pObsClock );
   return pObsClock;
}

void CriticalTelecommand::setObsClock(ObsClock* pClock) {
   assert ( pClock );
   pObsClock = pClock;
}

bool CriticalTelecommand::canExecute(void) {
    assert(isObjectConfigured());

	if (isTcCritical && isTcArmed) {
		if ((pObsClock->getTime()-timeWhenArmed)>=maxArmedDuration) {
			CC_RootObject::getEventRepository()->create(this,EVT_CRIT_TC_TIMEOUT);
			return TC_CANNOT_EXECUTE;
		}

		if (!isImageValid()) {
			CC_RootObject::getEventRepository()->create(this,EVT_CRIT_TC_IMG_INV);
			return TC_CANNOT_EXECUTE;
		}
	}

    return TC_CAN_EXECUTE;
}

TD_ActionOutcome CriticalTelecommand::doAction(void) {
	assert(isObjectConfigured());

	if (isTcArmed || !isTcCritical) {
		isTcArmed=NOT_ARMED;
		timeWhenArmed=-1;

		return doCriticalAction();
	}
	else {
		isTcArmed=ARMED;
		timeWhenArmed=pObsClock->getTime();

		CC_RootObject::getEventRepository()->create(this,EVT_CRIT_TC_ARMED);

		return ACTION_SUCCESS;
	}
}

bool CriticalTelecommand::isObjectConfigured(void) {
   return (Telecommand::isObjectConfigured() && maxArmedDuration>0 && pObsClock!=pNULL);
}
