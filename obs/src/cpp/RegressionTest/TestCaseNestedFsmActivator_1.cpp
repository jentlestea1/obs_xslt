//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseNestedFsmActivator_1.cpp
//
// Version	1.0
// Date		24.06.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../FSM/DC_FsmEvent.h"
#include "../FSM/DC_DummyFsmState.h"
#include "../FSM/DC_NestedFsmActivator.h"
#include "TestCaseNestedFsmActivator_1.h"

TestCaseNestedFsmActivator_1::TestCaseNestedFsmActivator_1(void) :
	TestCaseGenericSetUp(ID_NESTEDFSMACTIVATOR*10+1,"TestCaseNestedFsmActivator_1") {
	return;
}

void TestCaseNestedFsmActivator_1::runTestCase(void) {
	const TD_FsmStateIndex numStates=3;
	CC_FSM                *pFSM     =new CC_FSM;
	DC_NestedFsmActivator *pNFA     =new DC_NestedFsmActivator;
	DC_DummyFsmState      *pFS[numStates];
	DC_FsmEvent           *pFE[numStates];

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
	if (pNFA->getClassId()!=ID_NESTEDFSMACTIVATOR) {
		setTestResult(TEST_FAILURE,"Wrong class id");
		return;
	}

	// The object shall not be configured yet
	if (pNFA->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Newly created object is configured");
		return;
	}

	// Let's attach the nested FSM to the state and verify that
	// the FSM pointer is properly stored and the object is configured
	pNFA->setTargetFsm(pFSM);

	if (pNFA->getTargetFsm()!=pFSM) {
		setTestResult(TEST_FAILURE,"setTargetFsm() failed");
		return;
	}

	if (!pNFA->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Object is not configured");
		return;
	}

	// Force a FSM transition and verify that doInit() performs
	// a reset of the nested FSM
	pFE[0]->execute();
	pFSM->activate();

	pNFA->doInit();
	if (pFSM->getCurrentState()!=0) {
		setTestResult(TEST_FAILURE,"doInit() failed");
		return;
	}

	// Let's see if doContinue() activates the nested FSM
	pFE[1]->execute();
	pNFA->doContinue();
	if (pFSM->getCurrentState()!=pFE[1]->getTargetState()) {
		setTestResult(TEST_FAILURE,"doContinue() failed");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
