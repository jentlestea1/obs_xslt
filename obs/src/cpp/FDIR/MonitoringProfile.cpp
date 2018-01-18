//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// MonitoringProfile.cpp
//
// Version	1.2
// Date	    04.01.03 (Version 1.0)
//          14.04.03 (Version 1.1)
//          30.09.03 (Version 1.2)
// Author	A. Pasetti (P&P Software), R.Totaro
//
// Change Record:
//   Version 1.1: changed the parameter associated to the events (was
//                the instance ID, is the class ID)
//   Version 1.2: replaced double and int with TD_Float and TD_Integer

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "MonitoringProfile.h"

MonitoringProfile::MonitoringProfile(void) {
    enableStatus = ENABLED;
    pNext = pNULL;
}

bool MonitoringProfile::deviatesFromProfile(TD_Float value) {
    bool outcome = NO_MON_PROFILE_DEVIATION;
    if ( isEnabled() ) {
        if ( doProfileCheck(value) ) {
            CC_RootObject::getEventRepository()->create(this, EVT_MON_PROFILE_VIOLATION );
            outcome = MON_PROFILE_DEVIATION;
        }
    }
    if ( pNext!=pNULL )
        if ( pNext->deviatesFromProfile(value) )
            outcome = MON_PROFILE_DEVIATION;
    return outcome;
}

bool MonitoringProfile::deviatesFromProfile(TD_Integer value) {
    bool outcome = NO_MON_PROFILE_DEVIATION;
    if ( isEnabled() ) {
        if ( doProfileCheck(value) ) {
            CC_RootObject::getEventRepository()->create(this, EVT_MON_PROFILE_VIOLATION );
            outcome = MON_PROFILE_DEVIATION;
        }
    }
    if ( pNext!=pNULL )
        if ( pNext->deviatesFromProfile(value) )
            outcome = MON_PROFILE_DEVIATION;
    return outcome;
}

void MonitoringProfile::setNextMonitoringProfile(MonitoringProfile* pNextMonitoringProfile) {
    assert( pNextMonitoringProfile!=pNULL );
    pNext = pNextMonitoringProfile;
}

MonitoringProfile* MonitoringProfile::getNextMonitoringProfile() {
    return pNext;
}

void MonitoringProfile::reset(void) {
    return;
}
