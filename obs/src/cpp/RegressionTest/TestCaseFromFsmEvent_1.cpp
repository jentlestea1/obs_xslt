//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseFromFsmEvent_1.cpp
//
// Version	1.1
// Date		04.04.03
// Author	A. Pasetti (P&P Software)

#include "TestCaseFromFsmEvent_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../FSM/CC_FSM.h"
#include "../FSM/DC_DummyFsmState.h"
#include "../FSM/DC_FromFsmEvent.h"

TestCaseFromFsmEvent_1::TestCaseFromFsmEvent_1(void) :
	TestCaseGenericSetUp(ID_FROMFSMEVENT*10+1,"TestCaseFromFsmEvent_1") {
		return;
}

void TestCaseFromFsmEvent_1::runTestCase(void) {

   CC_FSM* pFsm = new CC_FSM();

   // Configure the FSM
   pFsm->setNumberOfStates(4);

   DC_DummyFsmState* pState[4];
   for (TD_FsmStateIndex i=0; i<pFsm->getNumberOfStates(); i++)
      pState[i] = new DC_DummyFsmState();

   for (TD_FsmStateIndex i=0; i<pFsm->getNumberOfStates(); i++)
      pFsm->setState(i,pState[i]);

   pFsm->reset();

   // FSM object should now be configured
   if ( (pFsm->isObjectConfigured() == NOT_CONFIGURED) )
	{	setTestResult(TEST_FAILURE,
             "Wrong FSM configuration status after configuration was completed");
		return;
	}

   // Create one FromFsmEvents
   DC_FromFsmEvent* pFsmEvt_1 = new DC_FromFsmEvent();

   // Check the correctness of the class identifier
   if ( (pFsmEvt_1->getClassId() != ID_FROMFSMEVENT) )
	{	setTestResult(TEST_FAILURE,"Wrong class identifier");
	   return;
	}

   // Check that FromFsmEvent is not configured
   if ( (pFsmEvt_1->isObjectConfigured() == CONFIGURED) )
   {	setTestResult(TEST_FAILURE,"Wrong configuration status");
		return;
   }

   // Configure the FromFsmEvent object and check the success of the
   // class-specific configuration action
   TD_FsmStateIndex evtStartingState = 2;
   TD_FsmStateIndex evtTargetState = 3;
   pFsmEvt_1->setTargetFsm(pFsm);
   pFsmEvt_1->setTargetState(evtTargetState);
   pFsmEvt_1->setStartingState(evtStartingState);
   if ( pFsmEvt_1->getStartingState() != evtStartingState )
   {	setTestResult(TEST_FAILURE,"Wrong starting state");
		return;
   }

   // Check that the FromFsmEvent is configured
   if ( (pFsmEvt_1->isObjectConfigured() != CONFIGURED) )
   {	setTestResult(TEST_FAILURE,"Wrong configuration status");
		return;
   }

   // Fire the FromFsmEvent from an FSM state other than its starting space
   TD_FsmStateIndex fsmState_1 = 1;
   pFsm->makeTransitionRequest(fsmState_1);
   pFsm->activate();
   if ( pFsmEvt_1->execute() != ACTION_FAILURE )
   {	setTestResult(TEST_FAILURE,"Wrong execution return value");
		return;
   }
   pFsm->activate();
   if ( pFsm->getCurrentState() != fsmState_1 )
   {	setTestResult(TEST_FAILURE,"Wrong FSM state");
		return;
   }

   // Fire the FromFsmEvent from an FSM state equal to its starting space
   TD_FsmStateIndex fsmState_2 = evtStartingState;
   pFsm->makeTransitionRequest(fsmState_2);
   pFsm->activate();
   if ( pFsmEvt_1->execute() != ACTION_SUCCESS )
   {	setTestResult(TEST_FAILURE,"Wrong execution return value");
		return;
   }
   pFsm->activate();
   if ( pFsm->getCurrentState() != evtTargetState )
   {	setTestResult(TEST_FAILURE,"Wrong FSM state");
		return;
   }

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
