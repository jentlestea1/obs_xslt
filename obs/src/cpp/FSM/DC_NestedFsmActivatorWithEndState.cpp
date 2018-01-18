//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_NestedFsmActivatorWithEndState.cpp
//
// Version	1.0
// Date		23.06.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../FSM/CC_FSM.h"
#include "DC_NestedFsmActivatorWithEndState.h"

DC_NestedFsmActivatorWithEndState::DC_NestedFsmActivatorWithEndState(void) {
	targetState=-1;
	setClassId(ID_NESTEDFSMACTIVATORWITHENDSTATE);
}

void DC_NestedFsmActivatorWithEndState::setTargetState(TD_FsmStateIndex targetState) {
	assert(targetState>=0);
	this->targetState=targetState;
}

TD_FsmStateIndex DC_NestedFsmActivatorWithEndState::getTargetState(void) {
	assert(targetState>=0);
	return targetState;
}

bool DC_NestedFsmActivatorWithEndState::isFinished(void) {
	assert(isObjectConfigured());
	return (getTargetFsm()->getCurrentState()==targetState);
}

bool DC_NestedFsmActivatorWithEndState::isObjectConfigured(void) {
	return (DC_NestedFsmActivator::isObjectConfigured() && targetState>=0);
}
