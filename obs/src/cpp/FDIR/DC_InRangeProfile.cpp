//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_InRangeProfile.cpp
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
#include "DC_InRangeProfile.h"

DC_InRangeProfile::DC_InRangeProfile(void) {
    setClassId(ID_INRANGEPROFILE);
}

bool DC_InRangeProfile::doProfileCheck(TD_Float value) {
    assert(getLowerBound()<getUpperBound());

    return (value>getLowerBound() && value<getUpperBound());
}
