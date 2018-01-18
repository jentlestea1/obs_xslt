//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseManoeuvreManager_3.cpp
//
// Version	1.0
// Date		31.08.03
// Author	A. Pasetti

#include "TestCaseManoeuvreManager_3.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../Manoeuvre/DC_DummyConfigurableManoeuvre.h"
#include "../Manoeuvre/CC_ManoeuvreManager.h"

TestCaseManoeuvreManager_3::TestCaseManoeuvreManager_3(void) :
	TestCaseWithEvtCheck(ID_MANOEUVREMANAGER*10+3,"TestCaseManoeuvreManager_3") {
	return;
}

void TestCaseManoeuvreManager_3::runTestCase(void) {
    CC_ManoeuvreManager           *pMM =new CC_ManoeuvreManager();
	DC_DummyConfigurableManoeuvre *pDCM;

	// Initialize the manoeuvre manager
	pMM->setPendingManoeuvreListSize(1);

	// Allocate, load and set the start and continuation flag of the manoeuvre
	pDCM = new DC_DummyConfigurableManoeuvre();
    pDCM->setInUse(true);
	pMM->load(pDCM);
    pDCM->setStartCheckStatus(MAN_CAN_START);
    pDCM->setContinuationCheckStatus(MAN_CAN_CONTINUE);
    pDCM->setTerminationCheckStatus(MAN_HAS_NOT_TERMINATED);

	// Verify initial value of activation step counter
    if ( pDCM->getActivationStepCounter() != 0 ) {
		setTestResult(TEST_FAILURE,"Wrong initial value of activation step counter");
		return;
	}

    // Invoke twice the activate method and verify that the manoeuvre
	// continuation counter has been incremented twice
	pMM->activate();
	pMM->activate();
    if ( pDCM->getContinuationActionCounter() != 2 ) {
		setTestResult(TEST_FAILURE,"Wrong value of manoeuvre continuation counter");
		return;
	}

	// Verify value of activation step counter
    if ( pDCM->getActivationStepCounter() != 2 ) {
		setTestResult(TEST_FAILURE,"Wrong value of activation step counter");
		return;
	}

	// Suspend the manoeuvre, invoke the activate method, and verify that the manoeuvre
	// continuation counter has not been incremented
    pDCM->setIsSuspended(true);
	pMM->activate();
	if ( pDCM->getContinuationActionCounter() != 2 ) {
		setTestResult(TEST_FAILURE,"Wrong value of manoeuvre continuation counter");
		return;
	}

	// Verify value of activation step counter
    if ( pDCM->getActivationStepCounter() != 2 ) {
		setTestResult(TEST_FAILURE,"Wrong value of activation step counter");
		return;
	}

	// Force the termination of the manoeuvre and verify that the manoeuvre status
    // changes to "not suspended"
    pDCM->setTerminationCheckStatus(MAN_HAS_TERMINATED);
    pDCM->setIsSuspended(true);
	pMM->activate();
	if ( pDCM->getContinuationActionCounter() != 2 ) {
		setTestResult(TEST_FAILURE,"Wrong value of manoeuvre continuation counter");
		return;
	}
    if ( pDCM->isSuspended() ) {
		setTestResult(TEST_FAILURE,"Wrong manoeuvre suspension status");
		return;
	}

	// Reload the manoeuvre, suspend it, activate it and verify that the
    // activation step counter has been reset to 0
    pDCM->setTerminationCheckStatus(MAN_HAS_NOT_TERMINATED);
    pMM->load(pDCM);
    pDCM->setIsSuspended(true);
	pMM->activate();
    if ( pDCM->getActivationStepCounter() != 0 ) {
		setTestResult(TEST_FAILURE,"Wrong value of activation step counter");
		return;
	}
    if ( pDCM->getInitializationActionCounter() != 2 ) {
		setTestResult(TEST_FAILURE,"Wrong value of manoeuvre continuation counter");
		return;
	}

    // Abort the manoeuvre and verify that its status is changed back to "not suspended"
    pDCM->abort();
    if ( pDCM->isSuspended() ) {
		setTestResult(TEST_FAILURE,"Wrong manoeuvre suspension status");
		return;
	}

	// Verify value of activation step counter

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
