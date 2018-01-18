//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// RecoveryAction.cpp
//
// Version	1.0
// Date		24.06.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "RecoveryAction.h"

RecoveryAction::RecoveryAction(void) {
	pNextRecoveryAction=pNULL;
}

TD_ActionOutcome RecoveryAction::doAction(void) {
	TD_ActionOutcome outcome=ACTION_CANNOT_EXECUTE;

	if (canExecute())
		outcome=doRecoveryAction();

	if (pNextRecoveryAction)
		outcome=pNextRecoveryAction->execute();

	return outcome;
}

bool RecoveryAction::canExecute(void) {
	return true;
}

void RecoveryAction::setNextRecoveryAction(RecoveryAction *pNextRecoveryAction) {
	assert(pNextRecoveryAction!=pNULL);
	this->pNextRecoveryAction=pNextRecoveryAction;
}

RecoveryAction *RecoveryAction::getNextRecoveryAction(void) {
	return pNextRecoveryAction;
}
