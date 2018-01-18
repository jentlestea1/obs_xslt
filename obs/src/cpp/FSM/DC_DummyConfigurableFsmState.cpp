//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyConfigurableFsmState.cpp
//
// Version	1.0
// Date		12.10.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_DummyConfigurableFsmState.h"

DC_DummyConfigurableFsmState::DC_DummyConfigurableFsmState(void) {
   setClassId(ID_DUMMYCONFIGURABLEFSMSTATE);
   activationCounter = 0;
   initializationCounter = 0;
   exitCounter = 0;
   initializationCheck = true;
   exitCheck = true;
   terminationCheck = false;
}

void DC_DummyConfigurableFsmState::doContinue(void) {
   activationCounter++;
   return;
}

void DC_DummyConfigurableFsmState::doInit(void) {
   initializationCounter++;
   return;
}

void DC_DummyConfigurableFsmState::doExit(void) {
   exitCounter++;
   return;
}

bool DC_DummyConfigurableFsmState::canExit(void) {
   return exitCheck;
}

bool DC_DummyConfigurableFsmState::canEnter(void) {
   return initializationCheck;
}

bool DC_DummyConfigurableFsmState::isFinished(void) {
   return terminationCheck;
}

unsigned int DC_DummyConfigurableFsmState::getActivationCounter(void) {
   return activationCounter;
}

unsigned int DC_DummyConfigurableFsmState::getInitializationCounter(void) {
   return initializationCounter;
}

unsigned int DC_DummyConfigurableFsmState::getExitCounter(void) {
   return exitCounter;
}

void DC_DummyConfigurableFsmState::setInitializationCheckValue(bool value) {
   initializationCheck = value;
}

void DC_DummyConfigurableFsmState::setExitCheckValue(bool value) {
   exitCheck = value;
}

void DC_DummyConfigurableFsmState::setTerminationCheckValue(bool value) {
   terminationCheck = value;
}
