//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_TestPUSTelecommand.cpp
//
// Version	1.0
// Date		4.01.04
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTelecommand.h"
#include "DC_TestPUSTelecommand.h"

DC_TestPUSTelecommand::DC_TestPUSTelecommand(void) {
   setClassId(ID_TESTPUSTELECOMMAND);
   setType(PUS_TYPE_TEST);
   setSubType(PUS_ST_TC_TEST);
   executionSuccess = 0;
   executionCounter = 0; 
   executionCheckValue = TC_CAN_EXECUTE;
   validityCheckValue = VALID;
   executionCheckCode = 0;
   validityCheckCode = 0;
   lasti = 0;
}

unsigned int DC_TestPUSTelecommand::getExecutionCounter(void) {
   return executionCounter;
}

TD_ActionOutcome DC_TestPUSTelecommand::doAction(void) {
   if (executionCounter<255)
        executionCounter++;
   else
       executionCounter=0;
   if (executionSuccess)
       return ACTION_SUCCESS;
   else
       return ACTION_FAILURE;
}

bool DC_TestPUSTelecommand::canExecute(void) {
    return executionCheckValue;
}

bool DC_TestPUSTelecommand::isValid(void) {
    return validityCheckValue;
}

void DC_TestPUSTelecommand::setExecutionCheckValue(bool executionCheckValue) {
    this->executionCheckValue = executionCheckValue;
}

void DC_TestPUSTelecommand::setValidityCheckValue(bool validityCheckValue) {
    this->validityCheckValue = validityCheckValue;
}

TD_CheckCode DC_TestPUSTelecommand::getValidityCheckCode(void) const {
    return validityCheckCode;
}

TD_CheckCode DC_TestPUSTelecommand::getExecutionCheckCode(void) const {
    return executionCheckCode;
}

void DC_TestPUSTelecommand::setValidityCheckCode(TD_CheckCode validityCheckCode) {
    this->validityCheckCode = validityCheckCode;
}

void DC_TestPUSTelecommand::setExecutionCheckCode(TD_CheckCode executionCheckCode) {
    this->executionCheckCode = executionCheckCode;
}

void DC_TestPUSTelecommand::setActionOutcome(bool executionSuccess) {
    this->executionSuccess = executionSuccess;
}

bool DC_TestPUSTelecommand::getActionOutcome() {
     return executionSuccess;
}

void DC_TestPUSTelecommand::setRawData(unsigned int i, unsigned char d) {
    assert( i<6 );
    assert( (i==0) || (i==(lasti+1)) );    // check that i argument increments by 1 in each call

    lasti = i;
    switch (i) {
        case 0:
            executionCounter = d;
            return;
        case 1:
             if (d>0)
                 executionCheckValue = true;
             else
                 executionCheckValue = false;
             return;
        case 2:
             if (d>0)
                 validityCheckValue = true;
             else
                 validityCheckValue = false;
             return;
        case 3:
            executionCheckCode = d;
            return;
        case 4:
            validityCheckCode = d;
            return;
        case 5:
             if (d>0)
                 executionSuccess = true;
             else
                 executionSuccess = false;
             return;

    }
}

unsigned int DC_TestPUSTelecommand::getNumberOfRawData(void) const {
    return 6;
}

