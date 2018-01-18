//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyPUSTelecommand.cpp
//
// Version	1.0
// Date		4.12.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "DC_DummyPUSTelecommand.h"

DC_DummyPUSTelecommand::DC_DummyPUSTelecommand(void) {
   executionCounter = 0; 
   setClassId(ID_DUMMYPUSTELECOMMAND);
   setAcknowledgeLevel(0);
   setTelecommandId(TEST_TC_ID);
   setSource(TEST_TC_SOURCE);
   setSubType(TEST_TC_SUBTYPE);
   setType(TEST_TC_TYPE);
}

unsigned int DC_DummyPUSTelecommand::getExecutionCounter(void) {
   return executionCounter;
}

TD_ActionOutcome DC_DummyPUSTelecommand::doAction(void) {
   executionCounter++;
   return ACTION_SUCCESS;
}

