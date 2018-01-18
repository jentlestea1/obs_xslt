//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// RangeProfile.cpp
//
// Version	1.1
// Date		17.01.03 (Version 1.0)
//          01.10.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: replaced double and int with TD_Float and TD_Integer

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "RangeProfile.h"

RangeProfile::RangeProfile(void) {
    lowerBound = (TD_Float)0.0;
    upperBound = (TD_Float)0.0;
}

bool RangeProfile::doProfileCheck(TD_Integer value) {
    assert( lowerBound<upperBound );
    return doProfileCheck( (TD_Float)value );
}

void RangeProfile::setLowerBound(TD_Float lowerBound) {
    this->lowerBound = lowerBound;
}

void RangeProfile::setUpperBound(TD_Float upperBound) {
    this->upperBound = upperBound;
}

bool RangeProfile::isObjectConfigured(void) {
    return (MonitoringProfile::isObjectConfigured() && lowerBound<upperBound);
}
