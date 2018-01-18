//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyPunctualAction_1.cpp
//
// Version	1.3
// Date		11.04.03 (Version 1.2)
//          30.09.03 (Version 1.3)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.3: Added a test of the action's activation counter

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/DC_DummyPunctualAction.h"
#include "TestCaseDummyPunctualAction_1.h"

TestCaseDummyPunctualAction_1::TestCaseDummyPunctualAction_1(void) :
	TestCaseWithEvtCheck(ID_DUMMYPUNCTUALACTION*10+1,"TestCaseDummyPunctualAction_1") {
	return;
}

void TestCaseDummyPunctualAction_1::runTestCase(void) {
    const unsigned int nEvt     =getNumberOfEvents();
	DC_DummyPunctualAction *pAct=new DC_DummyPunctualAction;

	// Verify correctness of the class identifier
	if (pAct->getClassId()!=ID_DUMMYPUNCTUALACTION) {
		setTestResult(TEST_FAILURE,"Wrong class identifier");
		return;
	}

	// Dummy punctual actions should be enabled at creation
    if (!pAct->isEnabled()) {
        setTestResult(TEST_FAILURE,"Wrong enable status at creation");
        return;
    }

    // The activation counter shall be equal to zero
    if (pAct->getActivationCounter()) {
        setTestResult(TEST_FAILURE,"Wrong activation counter at creation");
        return;
    }

	// The outcome should be set to ACTION_RESET
	if (pAct->getLastOutcome()!=ACTION_RESET) {
		setTestResult(TEST_FAILURE,"Wrong action outcome at creation");
		return;
	}

	// Send an execute request to the punctual action and check that the
	// correct event is recorded.
	if (pAct->execute()!=ACTION_SUCCESS) {
		setTestResult(TEST_FAILURE,"Wrong punctual action outcome");
		return;
	}

	if (!verifyLatestEvent(nEvt+1,EVT_PUNCTUAL_ACTION_EXEC))
		return;

    // Verify that the activation counter was incremented
    if (pAct->getActivationCounter()!=1) {
        setTestResult(TEST_FAILURE,"Activation counter was not incremented");
        return;
    }

	// Disable the punctual action and verify correct enable status
	pAct->setEnabled(DISABLED);
	if (pAct->isEnabled()) {
		setTestResult(TEST_FAILURE, "Punctual action was not disabled");
		return;
	}

	// Send an execute request to the punctual action and check that the
	// correct event is recorded.
	if (pAct->execute()!=ACTION_DISABLED) {
		setTestResult(TEST_FAILURE,"Wrong punctual action outcome");
		return;
    }

	if (!verifyLatestEvent(nEvt+2,EVT_PUNCTUAL_ACTION_DIS))
		return;

	// Verify the the latest outcome is properly reported
	if (pAct->getLastOutcome()!=ACTION_DISABLED ) {
		setTestResult(TEST_FAILURE,"Wrong puctual action outcome");
		return;
	}

	// Reset the latest outcome and verify that it is now ACTION_RESET
	pAct->resetLastOutcome();
	if (pAct->getLastOutcome()!=ACTION_RESET) {
		setTestResult(TEST_FAILURE,"getLastOutcome() failed");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
