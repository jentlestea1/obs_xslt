//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_UnstableFsmState.cpp
//
// Version	1.0
// Date		14.07.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_UnstableFsmState.h"

DC_UnstableFsmState::DC_UnstableFsmState(void) {
	setClassId(ID_UNSTABLEFSMSTATE);
}

void DC_UnstableFsmState::doContinue(void) {
    return;
}

bool DC_UnstableFsmState::isFinished(void) {
    return true;
}
