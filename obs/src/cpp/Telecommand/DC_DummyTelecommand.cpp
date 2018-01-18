//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyTelecommand.cpp
//
// Version	1.0
// Date		4.12.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_DummyTelecommand.h"

DC_DummyTelecommand::DC_DummyTelecommand(void) {
   executionCounter = 0; 
   executionCheckValue = TC_CAN_EXECUTE;
   validityCheckValue = VALID;
   executionCheckCode = 0;
   validityCheckCode = 0;
   setClassId(ID_DUMMYTELECOMMAND);
}

unsigned int DC_DummyTelecommand::getExecutionCounter(void) {
   return executionCounter;
}

TD_ActionOutcome DC_DummyTelecommand::doAction(void) {
   executionCounter++;
   return ACTION_SUCCESS;
}

bool DC_DummyTelecommand::canExecute(void) {
    return executionCheckValue;
}

bool DC_DummyTelecommand::isValid(void) {
    return validityCheckValue;
}

void DC_DummyTelecommand::setExecutionCheckValue(bool executionCheckValue) {
    this->executionCheckValue = executionCheckValue;
}

void DC_DummyTelecommand::setValidityCheckValue(bool validityCheckValue) {
    this->validityCheckValue = validityCheckValue;
}

TD_CheckCode DC_DummyTelecommand::getValidityCheckCode(void) const {
    return validityCheckCode;
}

TD_CheckCode DC_DummyTelecommand::getExecutionCheckCode(void) const {
    return executionCheckCode;
}

void DC_DummyTelecommand::setValidityCheckCode(TD_CheckCode validityCheckCode) {
    this->validityCheckCode = validityCheckCode;
}

void DC_DummyTelecommand::setExecutionCheckCode(TD_CheckCode executionCheckCode) {
    this->executionCheckCode = executionCheckCode;
}

