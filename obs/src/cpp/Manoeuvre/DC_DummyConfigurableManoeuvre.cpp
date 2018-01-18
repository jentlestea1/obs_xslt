//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyConfigurableManoeuvre.cpp
//
// Version	1.0
// Date		10.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_DummyConfigurableManoeuvre.h"

DC_DummyConfigurableManoeuvre::DC_DummyConfigurableManoeuvre(void) {
    initializationActionCounter = 0;
    continuationActionCounter = 0;
    terminationActionCounter = 0;
    startCheck = MAN_CANNOT_START;
    continuationCheck = MAN_CANNOT_CONTINUE;
    terminationCheck = MAN_HAS_NOT_TERMINATED;
    setClassId(ID_DUMMYCONFIGURABLEMANOEUVRE);
}

void DC_DummyConfigurableManoeuvre::internalTerminate(void) {
    terminationActionCounter++;
}

bool DC_DummyConfigurableManoeuvre::canStart(void) {
    assert( !isExecuting() );
    return startCheck;
}

void DC_DummyConfigurableManoeuvre::initialize(void) {
    assert( !isExecuting() );
    initializationActionCounter++;
}

bool DC_DummyConfigurableManoeuvre::canContinue(void) {
    assert( isExecuting() );
    return continuationCheck;
}

void DC_DummyConfigurableManoeuvre::doInternalContinue(void) {
    assert( isExecuting() );
    continuationActionCounter++;
}

bool DC_DummyConfigurableManoeuvre::isFinished(void) {
    assert( isExecuting() );
    return terminationCheck;
}

void DC_DummyConfigurableManoeuvre::setStartCheckStatus(bool startCheck) {
    this->startCheck = startCheck;
}

void DC_DummyConfigurableManoeuvre::setContinuationCheckStatus(bool continuationCheck) {
    this->continuationCheck = continuationCheck;
}

void DC_DummyConfigurableManoeuvre::setContinuationCheckCode(TD_CheckCode continuationCheckCode) {
    this->continuationCheckCode=continuationCheckCode;
}

TD_CheckCode DC_DummyConfigurableManoeuvre::getContinuationCheckCode() const {
    return continuationCheckCode;
}

void DC_DummyConfigurableManoeuvre::setTerminationCheckStatus(bool terminationCheck) {
    this->terminationCheck = terminationCheck;
}

int DC_DummyConfigurableManoeuvre::getInitializationActionCounter(void) {
    return initializationActionCounter;
}

int DC_DummyConfigurableManoeuvre::getContinuationActionCounter(void) {
    return continuationActionCounter;
}

int DC_DummyConfigurableManoeuvre::getTerminationActionCounter(void) {
    return terminationActionCounter;
}
