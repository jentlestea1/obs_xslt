//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_NullRecoveryAction.cpp
//
// Version	1.0
// Date		24.06.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "DC_NullRecoveryAction.h"

DC_NullRecoveryAction::DC_NullRecoveryAction(void) {
	setClassId(ID_NULLRECOVERYACTION);
}

TD_ActionOutcome DC_NullRecoveryAction::doRecoveryAction(void) {
	return ACTION_SUCCESS;
}
