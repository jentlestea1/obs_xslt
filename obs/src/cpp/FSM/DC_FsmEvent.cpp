//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_FsmEvent.cpp
//
// Version	1.0
// Date		02.10.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "DC_FsmEvent.h"
#include "CC_FSM.h"

DC_FsmEvent::DC_FsmEvent(void) {
   pTargetFsm = pNULL;
   targetState = -1;
   setClassId(ID_FSMEVENT);
}

void DC_FsmEvent::setTargetFsm(CC_FSM* pFsm) {
   assert( pFsm != pNULL );
   pTargetFsm = pFsm;
}

void DC_FsmEvent::setTargetState(TD_FsmStateIndex stateIndex) {
   assert( stateIndex >= 0 );
   targetState = stateIndex;
}

CC_FSM* DC_FsmEvent::getTargetFsm(void) const {
   assert( pTargetFsm != pNULL );
   return pTargetFsm;
}

TD_FsmStateIndex DC_FsmEvent::getTargetState(void) const {
   assert( targetState >= 0 );
   return targetState;
}

bool DC_FsmEvent::isObjectConfigured(void) {
    return (PunctualAction::isObjectConfigured() && targetState>=0 && pTargetFsm!=pNULL &&
            targetState<pTargetFsm->getNumberOfStates());
}

TD_ActionOutcome DC_FsmEvent::doAction(void) {
   pTargetFsm->makeTransitionRequest(targetState);
   return ACTION_SUCCESS;
}
