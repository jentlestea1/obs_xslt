//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_NestedFsmActivatorWithExitCheck.cpp
//
// Version	1.0
// Date		08.07.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../FSM/CC_FSM.h"
#include "DC_NestedFsmActivatorWithExitCheck.h"

DC_NestedFsmActivatorWithExitCheck::DC_NestedFsmActivatorWithExitCheck(void) {
	targetState=-1;
	setClassId(ID_NESTEDFSMACTIVATORWITHEXITCHECK);
}

void DC_NestedFsmActivatorWithExitCheck::setTargetState(TD_FsmStateIndex targetState) {
	assert(targetState>=0);
	this->targetState=targetState;
}

TD_FsmStateIndex DC_NestedFsmActivatorWithExitCheck::getTargetState(void) {
	assert(targetState>=0);
	return targetState;
}

bool DC_NestedFsmActivatorWithExitCheck::canExit(void) {
	assert(isObjectConfigured());
	return (getTargetFsm()->getCurrentState()==targetState);
}

bool DC_NestedFsmActivatorWithExitCheck::isObjectConfigured(void) {
	return (DC_NestedFsmActivator::isObjectConfigured() && targetState>=0);
}
