//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_FromFsmEvent.cpp
//
// Version	1.0
// Date		02.10.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "DC_FromFsmEvent.h"
#include "CC_FSM.h"

DC_FromFsmEvent::DC_FromFsmEvent(void) {
   startingState = -1;
   setClassId(ID_FROMFSMEVENT);
}

void DC_FromFsmEvent::setStartingState(TD_FsmStateIndex startingState) {
    assert( startingState >= 0 );
    this->startingState = startingState;
}

TD_FsmStateIndex DC_FromFsmEvent::getStartingState(void) const {
    assert( startingState >= 0 );
    return startingState;
}

bool DC_FromFsmEvent::isObjectConfigured(void) {
    return (DC_FsmEvent::isObjectConfigured() && startingState>=0 &&
            startingState<getTargetFsm()->getNumberOfStates());
}

TD_ActionOutcome DC_FromFsmEvent::doAction(void) {
    assert( isObjectConfigured() );
    if (getTargetFsm()->getCurrentState() == startingState)
        return DC_FsmEvent::doAction();
    else
        return ACTION_FAILURE;
}
