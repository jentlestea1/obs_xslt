//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyFsmState_1.cpp
//
// Version	1.0
// Date		13.09.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../FSM/FsmState.h"
#include "../FSM/DC_DummyFsmState.h"
#include "TestCaseDummyFsmState_1.h"

TestCaseDummyFsmState_1::TestCaseDummyFsmState_1(void) :
	TestCaseGenericSetUp(ID_DUMMYFSMSTATE*10+1,"TestCaseDummyFsmState_1") {
		return;
}

void TestCaseDummyFsmState_1::runTestCase(void) {

   DC_DummyFsmState* pFsmState = new DC_DummyFsmState();

   // Verify correctness of class ID
   if (pFsmState->getClassId() != ID_DUMMYFSMSTATE)
	{	setTestResult(TEST_FAILURE, "Wrong class ID");
		return;
	}

   // Check correct value of "next state" at creation
	if ( pFsmState->getNextState() != pNULL )
	{	setTestResult(TEST_FAILURE, "Incorrect initial value of next state");
		return;
	}
   // Load a "next state" and check correctness
   DC_DummyFsmState* pNextState = new DC_DummyFsmState();
   pFsmState->setNextState(pNextState);
	if ( pFsmState->getNextState() != pNextState )
	{	setTestResult(TEST_FAILURE, "Incorrect loading of next state");
		return;
	}

   // Check correctness of exit, termination and initialization checks
	if ( (pFsmState->canExit() != true) ||
        (pFsmState->isFinished() != false) ||
        (pFsmState->canEnter() != true) )
	{	setTestResult(TEST_FAILURE, "Incorrect check return values at creation");
		return;
	}

   // Perform actions
   pFsmState->doInit();
   pFsmState->doContinue();
   pFsmState->doExit();

   // Check correctness of exit, termination and initialization checks
	if ( (pFsmState->canExit() != true) ||
        (pFsmState->isFinished() != false) ||
        (pFsmState->canEnter() != true) )
	{	setTestResult(TEST_FAILURE, "Incorrect check return values after actions");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
