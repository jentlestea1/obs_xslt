//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_StuckDataProfile.cpp
//
// Version	1.1
// Date		07.01.03 (Version 1.0)
//          01.10.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: replaced double and int with TD_Float and TD_Integer

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_StuckDataProfile.h"

DC_StuckDataProfile::DC_StuckDataProfile(void) {
    setClassId(ID_STUCKDATAPROFILE);
    stuckThreshold = 0;
    reset();
}

bool DC_StuckDataProfile::doProfileCheck(TD_Float value) {
    assert(false);
    return MON_PROFILE_DEVIATION;
}

bool DC_StuckDataProfile::doProfileCheck(TD_Integer value) {
    assert(counter<(stuckThreshold+1));

    if (value!=previousValue) {
        counter=0;
        previousValue=value;
    }
    else {
        counter++;

        if (counter==stuckThreshold) {
            counter=0;
            return MON_PROFILE_DEVIATION; 
        }
    }

    return NO_MON_PROFILE_DEVIATION;
}

void DC_StuckDataProfile::setStuckThreshold(unsigned int stuckThreshold) {
    this->stuckThreshold = stuckThreshold;
}

unsigned int DC_StuckDataProfile::getStuckThreshold(void) const {
    return stuckThreshold;
}

void DC_StuckDataProfile::reset(void) {
    counter = 0;
    previousValue = PREVIOUS_VALUE_INIT;
}

bool DC_StuckDataProfile::isObjectConfigured(void) {
   return (MonitoringProfile::isObjectConfigured() && stuckThreshold>0);
}
