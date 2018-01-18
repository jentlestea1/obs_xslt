//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyConditionalPunctualAction.cpp
//
// Version	1.0
// Date		04.06.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_DummyConditionalPunctualAction.h"

DC_DummyConditionalPunctualAction::DC_DummyConditionalPunctualAction(void) {
	executionFlag=false;
	setClassId(ID_DUMMYCONDITIONALPUNCTUALACTION);
}

void DC_DummyConditionalPunctualAction::setExecutionFlag(bool newState) {
	executionFlag=newState;
}

bool DC_DummyConditionalPunctualAction::canExecute(void) {
	return executionFlag;
}

TD_ActionOutcome DC_DummyConditionalPunctualAction::doConditionalAction(void) {
	return ACTION_SUCCESS;
}
