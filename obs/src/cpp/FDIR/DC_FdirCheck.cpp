//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_FdirCheck.cpp
//
// Version	1.0
// Date		24.06.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "DC_FdirCheck.h"

DC_FdirCheck::DC_FdirCheck(void) {
	pRecoveryAction=pNULL;
	pFdiCheck=pNULL;
	setClassId(ID_FDIRCHECK);
}

TD_ActionOutcome DC_FdirCheck::doAction(void) {
	assert(isObjectConfigured());

	TD_ActionOutcome outcome=pFdiCheck->execute();

	if (outcome==ACTION_FAILURE)
		outcome=pRecoveryAction->execute();

	return outcome;
}

void DC_FdirCheck::setFdiCheck(PunctualAction *pFdiCheck) {
	assert(pFdiCheck);
	this->pFdiCheck=pFdiCheck;
}

PunctualAction *DC_FdirCheck::getFdiCheck(void) {
	assert(pFdiCheck);
	return pFdiCheck;
}

void DC_FdirCheck::setRecoveryAction(RecoveryAction *pRecoveryAction) {
	assert(pRecoveryAction);
	this->pRecoveryAction=pRecoveryAction;
}

RecoveryAction *DC_FdirCheck::getRecoveryAction(void) {
	assert(pRecoveryAction);
	return pRecoveryAction;
}

bool DC_FdirCheck::isObjectConfigured(void) {
	return (PunctualAction::isObjectConfigured() &&
            pRecoveryAction!=pNULL && pFdiCheck!=pNULL);
}
