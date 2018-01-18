//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyRecoveryAction.cpp
//
// Version	1.0
// Date		25.06.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "DC_DummyRecoveryAction.h"

DC_DummyRecoveryAction::DC_DummyRecoveryAction(void) {
	actionCanExecute=true;
	actionOutcome=ACTION_SUCCESS;
	setClassId(ID_DUMMYRECOVERYACTION);
}

TD_ActionOutcome DC_DummyRecoveryAction::doRecoveryAction(void) {
	return actionOutcome;
}

bool DC_DummyRecoveryAction::canExecute(void) {
	return actionCanExecute;
}

void DC_DummyRecoveryAction::setActionOutcome(TD_ActionOutcome nextOutcome) {
	actionOutcome=nextOutcome;
}

void DC_DummyRecoveryAction::setExecutionFlag(bool canExecute) {
	actionCanExecute=canExecute;
}
