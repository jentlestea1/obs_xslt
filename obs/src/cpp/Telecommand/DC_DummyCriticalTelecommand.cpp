//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyCriticalTelecommand.cpp
//
// Version	1.0
// Date		17.06.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_DummyCriticalTelecommand.h"

DC_DummyCriticalTelecommand::DC_DummyCriticalTelecommand(void) {
	numberOfExecutions=0;
	imageValid=false;

	setClassId(ID_DUMMYCRITICALTELECOMMAND);
}

TD_ActionOutcome DC_DummyCriticalTelecommand::doCriticalAction(void) {
	numberOfExecutions++;

	return ACTION_SUCCESS;
}

unsigned int DC_DummyCriticalTelecommand::getNumberOfExecutions(void) {
	return numberOfExecutions;
}

bool DC_DummyCriticalTelecommand::isImageValid(void) {
	return imageValid;
}

void DC_DummyCriticalTelecommand::setImageValidity(bool isValid) {
	imageValid=isValid;
}
