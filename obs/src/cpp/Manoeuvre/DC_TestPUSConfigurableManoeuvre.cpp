//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_TestPUSConfigurableManoeuvre.cpp
//
// Version	1.0
// Date		10.02.04
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Manoeuvre/PUSTcManoeuvre.h"
#include "DC_TestPUSConfigurableManoeuvre.h"

DC_TestPUSConfigurableManoeuvre::DC_TestPUSConfigurableManoeuvre(void) {
    initializationActionCounter = 0;
    continuationActionCounter = 0;
    terminationActionCounter = 0;
    startCheck = MAN_CANNOT_START;
    continuationCheck = MAN_CANNOT_CONTINUE;
    terminationCheck = MAN_HAS_NOT_TERMINATED;
    setClassId(ID_TESTPUSCONFIGURABLEMANOEUVRE);
}

void DC_TestPUSConfigurableManoeuvre::internalTerminate(void) {
    terminationActionCounter++;
}

bool DC_TestPUSConfigurableManoeuvre::canStart(void) {
    assert( !isExecuting() );
    return startCheck;
}

void DC_TestPUSConfigurableManoeuvre::initialize(void) {
    assert( !isExecuting() );
    initializationActionCounter++;
}

bool DC_TestPUSConfigurableManoeuvre::canContinue(void) {
    assert( isExecuting() );
    return continuationCheck;
}

void DC_TestPUSConfigurableManoeuvre::doInternalContinue(void) {
    assert( isExecuting() );
    continuationActionCounter++;
    generateProgressEvent();
}

bool DC_TestPUSConfigurableManoeuvre::isFinished(void) {
    assert( isExecuting() );
    return terminationCheck;
}

void DC_TestPUSConfigurableManoeuvre::setStartCheckStatus(bool startCheck) {
    this->startCheck = startCheck;
}

void DC_TestPUSConfigurableManoeuvre::setContinuationCheckStatus(bool continuationCheck) {
    this->continuationCheck = continuationCheck;
}

void DC_TestPUSConfigurableManoeuvre::setContinuationCheckCode(TD_CheckCode continuationCheckCode) {
    this->continuationCheckCode=continuationCheckCode;
}

TD_CheckCode DC_TestPUSConfigurableManoeuvre::getContinuationCheckCode() const {
    return continuationCheckCode;
}

void DC_TestPUSConfigurableManoeuvre::setTerminationCheckStatus(bool terminationCheck) {
    this->terminationCheck = terminationCheck;
}

int DC_TestPUSConfigurableManoeuvre::getInitializationActionCounter(void) {
    return initializationActionCounter;
}

int DC_TestPUSConfigurableManoeuvre::getContinuationActionCounter(void) {
    return continuationActionCounter;
}

int DC_TestPUSConfigurableManoeuvre::getTerminationActionCounter(void) {
    return terminationActionCounter;
}
