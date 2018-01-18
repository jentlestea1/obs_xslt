//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_ForbiddenValueProfile.cpp
//
// Version	1.1
// Date		16.01.03 (Version 1.0)
//          01.10.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: replaced double and int with TD_Float and TD_Integer

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_ForbiddenValueProfile.h"

DC_ForbiddenValueProfile::DC_ForbiddenValueProfile(void) {
    setClassId(ID_FORBIDDENVALUEPROFILE);
    forbiddenValue = 0;
}

bool DC_ForbiddenValueProfile::doProfileCheck(TD_Float value) {
    assert(false);
    return MON_PROFILE_DEVIATION;
}

bool DC_ForbiddenValueProfile::doProfileCheck(TD_Integer value) {
    return (value==forbiddenValue);
}

void DC_ForbiddenValueProfile::setForbiddenValue(TD_Integer forbiddenValue) {
    this->forbiddenValue=forbiddenValue;
}

TD_Integer DC_ForbiddenValueProfile::getForbiddenValue(void) const {
    return forbiddenValue;
}
