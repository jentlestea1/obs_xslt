//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DeltaProfile.cpp
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
#include "DC_DeltaProfile.h"

#include <math.h>

DC_DeltaProfile::DC_DeltaProfile(void) {
    setClassId(ID_DELTAPROFILE);
    deltaThreshold = (TD_Float)0.0;
    previousValue = (TD_Float)0.0;
    reset();
}

bool DC_DeltaProfile::doProfileCheck(TD_Float value) {
    assert( deltaThreshold>(TD_Float)0.0 );

    if (notFirst && fabs(value-previousValue)>(double)deltaThreshold) {
        previousValue = value;
        return MON_PROFILE_DEVIATION;
    }
    else {
        notFirst = true;
        previousValue = value;
        return NO_MON_PROFILE_DEVIATION;
    }
}

bool DC_DeltaProfile::doProfileCheck(TD_Integer value) {
    assert( deltaThreshold>(TD_Float)0.0 );
    return doProfileCheck( (TD_Float)value );
}

void DC_DeltaProfile::setDeltaThreshold(TD_Float deltaThreshold) {
    assert( deltaThreshold>(TD_Float)0.0 );
    this->deltaThreshold = deltaThreshold;
}

TD_Float DC_DeltaProfile::getDeltaThreshold(void) {
    assert( deltaThreshold>(TD_Float)0.0 );
    return deltaThreshold;
}

void DC_DeltaProfile::reset(void) {
    notFirst = false;
}

bool DC_DeltaProfile::isObjectConfigured(void) {
   return (MonitoringProfile::isObjectConfigured() && deltaThreshold>(TD_Float)0.0);
}
