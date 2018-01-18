//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyPunctualAction.cpp
//
// Version	1.1
// Date		01.10.02 (Version 1.0)
//          30.09.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: Added an activation counter and its getter method

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_DummyPunctualAction.h"

DC_DummyPunctualAction::DC_DummyPunctualAction(void) {
    counter=0;
    setClassId(ID_DUMMYPUNCTUALACTION);
}

TD_ActionOutcome DC_DummyPunctualAction::doAction(void) {
    ++counter;
    return ACTION_SUCCESS;
}

unsigned int DC_DummyPunctualAction::getActivationCounter(void) const {
    return counter;
}
