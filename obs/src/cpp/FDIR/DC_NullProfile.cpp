//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_NullProfile.cpp
//
// Version	1.0
// Date		01.10.03 (Version 1.0)
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_NullProfile.h"

DC_NullProfile::DC_NullProfile(void) {
    setClassId(ID_NULLPROFILE);
}

bool DC_NullProfile::doProfileCheck(TD_Float value) {
    return NO_MON_PROFILE_DEVIATION;
}

bool DC_NullProfile::doProfileCheck(TD_Integer value) {
    return NO_MON_PROFILE_DEVIATION;
}
