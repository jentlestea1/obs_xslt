//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// CC_FSM.cpp
//
// Version	1.0
// Date	    11.04.03 
// Author	A. Pasetti (P&P Software)
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "FsmState.h"
#include "CC_FSM.h"

CC_FSM::CC_FSM(void) {
   pCurrentState = pNULL;
   numberOfStates = 0;
   currentState = -1;
   requestedTargetState = -1;
   setClassId(ID_FSM);
}

void CC_FSM::reset(void) {
   assert( numberOfStates > 0 );
   assert( pState[0] != pNULL );

   // Enable all state transitions
   for (TD_FsmStateIndex i=0; i<numberOfStates; i++)
      transitionEnabled[i] = ENABLED;

   allTransitionEnabled = ENABLED;

   // Compute the nextState indices
   for (TD_FsmStateIndex i=0; i<numberOfStates; i++)
   {  FsmState* pNS = pState[i]->getNextState();
      if ( pNS != pNULL )
      {   for (TD_FsmStateIndex j=0; j<numberOfStates; j++)
            if ( pNS == pState[j] )
               pNextState[i] = j;
      }
   }

   if ( currentState >= 0 )
      pCurrentState->doExit();

   pCurrentState = pState[0];
   currentState = 0;
   pCurrentState->doInit();
}

bool CC_FSM::isObjectConfigured(void) {
   if (!CC_RootObject::isObjectConfigured() || numberOfStates<=0 || pCurrentState==pNULL)
       return NOT_CONFIGURED;

   for (TD_FsmStateIndex i=0; i<numberOfStates; i++) {
       if (pState[i] == pNULL)
           return NOT_CONFIGURED;
   }

   return CONFIGURED;
}

void CC_FSM::setNumberOfStates(TD_FsmStateIndex n) {
   assert( n > 0 );
   assert( numberOfStates == 0 );       // Method should only be called once

   numberOfStates = n;

   // Create and initialize the array that holds the FSM states and their
   // next states
   pState = new FsmState*[n];
   for (TD_FsmStateIndex i=0; i<numberOfStates; i++)
      pState[i] = pNULL;

   pNextState = new TD_FsmStateIndex[n];
   for (TD_FsmStateIndex i=0; i<numberOfStates; i++)
      pNextState[i] = -1;

   // Create and initialize the array that holds the state transition
   // enable status
   transitionEnabled = new bool[n];
   for (TD_FsmStateIndex i=0; i<numberOfStates; i++)
      transitionEnabled[i] = ENABLED;
}

TD_FsmStateIndex CC_FSM::getNumberOfStates(void) const {
   return numberOfStates;
}

void CC_FSM::setState(TD_FsmStateIndex i, FsmState* s) {
   assert( numberOfStates > 0 );
   assert( (i < numberOfStates) && (s != pNULL) );
   assert( pState != pNULL );

   if ( (i < numberOfStates) && (i >= 0) )
       pState[i] = s;
   else
       CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_FS);
}

void CC_FSM::setTransitionEnableStatus(TD_FsmStateIndex toState, bool enabled) {
   assert( toState < numberOfStates );
   assert( transitionEnabled != pNULL );

   if ( (toState < numberOfStates) && (toState >= 0) )
       transitionEnabled[toState] = enabled;
   else
       CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_FS);
}

void CC_FSM::setTransitionEnableStatus(bool enabled) {
   allTransitionEnabled = enabled;
}

void CC_FSM::makeTransitionRequest(TD_FsmStateIndex targetState) {
   assert( isObjectConfigured() );
   assert( targetState >= 0 );
   assert( targetState < numberOfStates );

   if ( (targetState < numberOfStates) && (targetState >= 0) )
       requestedTargetState = targetState;
   else
       CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_FS);
}

void CC_FSM::activate(void) {
   assert( isObjectConfigured() );

   if ( requestedTargetState >= 0 )     // a state transition request is pending
   {  tryTransition(requestedTargetState);
      requestedTargetState = -1;
      pCurrentState->doContinue();
      return;
   }

   if ( (pCurrentState->isFinished()) &&
        (pCurrentState->getNextState()!=pNULL) )
      tryTransition( pNextState[currentState] );

   pCurrentState->doContinue();

   return;
}

void CC_FSM::tryTransition(TD_FsmStateIndex targetState) {
   assert( isObjectConfigured() );
   assert( targetState >= 0 );
   assert( targetState < numberOfStates );

   if (!isTransitionEnabled())
   {  CC_RootObject::getEventRepository()->create(this,EVT_FSM_ALL_TRANSITION_DISABLED);
      return;
   }

   if (!isTransitionEnabled(targetState))
   {  CC_RootObject::getEventRepository()->create(this,EVT_FSM_TRANSITION_DISABLED);
      return;
   }

   if (!pCurrentState->canExit())
   {  CC_RootObject::getEventRepository()->create(this,EVT_FSM_EXIT_FAILED);
      return;
   }

   FsmState* pTargetState = pState[targetState];
   if ( !pTargetState->canEnter() )
   {  CC_RootObject::getEventRepository()->create(this,EVT_FSM_ENTRY_FAILED);
      return;
   }

   pCurrentState->doExit();
   pCurrentState = pTargetState;
   currentState = targetState;
   pCurrentState->doInit();

   CC_RootObject::getEventRepository()->create(this,EVT_FSM_TRANSITION);
   return;
}
