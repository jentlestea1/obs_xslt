//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_SimpleChangeProfile.cpp
//
// Version	1.1
// Date		04.01.03 (Version 1.0)
//          01.10.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: replaced double and int with TD_Float and TD_Integer

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_SimpleChangeProfile.h"

DC_SimpleChangeProfile::DC_SimpleChangeProfile(void) {
    setClassId(ID_SIMPLECHANGEPROFILE);
    referenceValue = 0;
}

bool DC_SimpleChangeProfile::doProfileCheck(TD_Float value) {
    assert(false);
    return MON_PROFILE_DEVIATION;
}

bool DC_SimpleChangeProfile::doProfileCheck(TD_Integer value) {
    return (value!=referenceValue); 
}

void DC_SimpleChangeProfile::setReferenceValue(TD_Integer refValue) {
    referenceValue = refValue;
}

TD_Integer DC_SimpleChangeProfile::getReferenceValue(void) const {
    return referenceValue;
}
