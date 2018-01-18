//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseFsmEvent_1.cpp
//
// Version	1.1
// Date		23.03.03
// Author	A. Pasetti (P&P Software)
//
// Change Record:
//   Version 1.1: added code to configure the FSM

#include "TestCaseFsmEvent_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../FSM/DC_FsmEvent.h"
#include "../FSM/CC_FSM.h"
#include "../FSM/DC_DummyFsmState.h"

TestCaseFsmEvent_1::TestCaseFsmEvent_1(void) :
	TestCaseGenericSetUp(ID_FSMEVENT*10+1,"TestCaseFsmEvent_1") {
		return;
}

void TestCaseFsmEvent_1::runTestCase(void) {

   DC_FsmEvent* pFsmEvt = new DC_FsmEvent();

   // Verify correctness of class ID
   if (pFsmEvt->getClassId() != ID_FSMEVENT)
	{	setTestResult(TEST_FAILURE, "Wrong class ID");
		return;
	}

   // FsmEvent object should not be configured
   if ( (pFsmEvt->isObjectConfigured() != NOT_CONFIGURED) )
	{	setTestResult(TEST_FAILURE, "FsmEvent component should not be configured at creation");
		return;
	}

   // Load a target FsmState and check correctness
   TD_FsmStateIndex state = 1;
   pFsmEvt->setTargetState(state);
	if ( pFsmEvt->getTargetState() != state )
	{	setTestResult(TEST_FAILURE, "Incorrect loading of target state");
		return;
	}

   // Create and configure an FSM
   CC_FSM* pFsm = new CC_FSM();
   pFsm->setNumberOfStates(4);

   DC_DummyFsmState* pState[4];
   for (TD_FsmStateIndex i=0; i<pFsm->getNumberOfStates(); i++)
      pState[i] = new DC_DummyFsmState();
   for (TD_FsmStateIndex i=0; i<pFsm->getNumberOfStates(); i++)
      pFsm->setState(i,pState[i]);

   pFsm->reset();

   // Load the newly created FSM as the "target FSM" and check correctness
   pFsmEvt->setTargetFsm(pFsm);
	if ( pFsmEvt->getTargetFsm() != pFsm )
	{	setTestResult(TEST_FAILURE, "Incorrect loading of target FSM");
		return;
	}

   // FsmEvent object should now be configured
   if ( (pFsmEvt->isObjectConfigured() != CONFIGURED) )
	{	setTestResult(TEST_FAILURE, "FsmEvent component should be configured");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
