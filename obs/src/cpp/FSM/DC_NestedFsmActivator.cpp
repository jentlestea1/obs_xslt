//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_NestedFsmActivator.cpp
//
// Version	1.0
// Date		23.06.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "DC_NestedFsmActivator.h"

DC_NestedFsmActivator::DC_NestedFsmActivator(void) {
	pTargetFsm=pNULL;
	setClassId(ID_NESTEDFSMACTIVATOR);
}

void DC_NestedFsmActivator::setTargetFsm(CC_FSM* pTargetFsm) {
	assert(pTargetFsm!=pNULL);
	this->pTargetFsm=pTargetFsm;
}

CC_FSM *DC_NestedFsmActivator::getTargetFsm(void) {
	assert(pTargetFsm!=pNULL);
	return pTargetFsm;
}

void DC_NestedFsmActivator::doContinue(void) {
	assert(isObjectConfigured());
	pTargetFsm->activate();
}

void DC_NestedFsmActivator::doInit(void) {
	assert(isObjectConfigured());
	pTargetFsm->reset();
}

bool DC_NestedFsmActivator::isObjectConfigured(void) {
	return (FsmState::isObjectConfigured() && pTargetFsm!=pNULL);
}
