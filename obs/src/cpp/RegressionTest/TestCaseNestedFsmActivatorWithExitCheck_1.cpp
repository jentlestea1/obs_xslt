//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseNestedFsmActivatorWithExitCheck_1.cpp
//
// Version	1.0
// Date		08.07.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../FSM/DC_FsmEvent.h"
#include "../FSM/DC_DummyFsmState.h"
#include "../FSM/DC_NestedFsmActivatorWithExitCheck.h"
#include "TestCaseNestedFsmActivatorWithExitCheck_1.h"

TestCaseNestedFsmActivatorWithExitCheck_1::TestCaseNestedFsmActivatorWithExitCheck_1(void) :
	TestCaseGenericSetUp(ID_NESTEDFSMACTIVATORWITHEXITCHECK*10+1,
						 "TestCaseNestedFsmActivatorWithExitCheck_1") {
	return;
}

void TestCaseNestedFsmActivatorWithExitCheck_1::runTestCase(void) {
	const TD_FsmStateIndex              numStates  =8;
	const TD_FsmStateIndex              targetState=5;
	CC_FSM                             *pFSM       =new CC_FSM;
	DC_NestedFsmActivatorWithExitCheck *pNFA       =new DC_NestedFsmActivatorWithExitCheck;
	DC_DummyFsmState                   *pFS[numStates];
	DC_FsmEvent                        *pFE[numStates];

	// Initialize the FSM
	pFSM->setNumberOfStates(numStates);

	for (TD_FsmStateIndex i=0;i<numStates;i++) {
		// Create and load FSM states
		pFS[i]=new DC_DummyFsmState;
		pFSM->setState(i,pFS[i]);

		// Create and configure FSM events
		pFE[i]=new DC_FsmEvent;
		pFE[i]->setTargetFsm(pFSM);
		pFE[i]->setTargetState((i+1)%numStates);
	}

	pFSM->reset();

	// Verify the correctness of the class id
	if (pNFA->getClassId()!=ID_NESTEDFSMACTIVATORWITHEXITCHECK) {
		setTestResult(TEST_FAILURE,"Wrong class id");
		return;
	}

	// The object shall not be configured yet
	if (pNFA->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Newly created object is configured");
		return;
	}

	// Let's attach the nested FSM to the state and verify that
	// object is not yet configured
	pNFA->setTargetFsm(pFSM);

	if (pNFA->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Object is wrongly configured");
		return;
	}

	// After setting the target state the object should be configured
	pNFA->setTargetState(targetState);

	if (pNFA->getTargetState()!=targetState) {
		setTestResult(TEST_FAILURE,"setTargetState() failed");
		return;
	}

	if (!pNFA->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Object is not configured");
		return;
	}

	// Verify that canExit() returns true only when tha machine is
	// in the right state
	for (TD_FsmStateIndex i=0;i<numStates;i++) {
		pFE[i]->execute();
		pNFA->doContinue();

		if ((pNFA->canExit() && pFSM->getCurrentState()!=targetState) ||
			(!pNFA->canExit() && pFSM->getCurrentState()==targetState)) {
			setTestResult(TEST_FAILURE,"canExit() failed");
			return;
		}
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
