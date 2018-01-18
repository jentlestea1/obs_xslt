//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyManoeuvre_1.cpp
//
// Version	1.1
// Date		08.05.03
// Author	R. Totaro

#include "TestCaseDummyManoeuvre_1.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../Manoeuvre/DC_DummyManoeuvre.h"

TestCaseDummyManoeuvre_1::TestCaseDummyManoeuvre_1(void) :
	TestCaseWithEvtCheck(ID_DUMMYMANOEUVRE*10+1,"TestCaseDummyManoeuvre_1")
{
	return;
}

void TestCaseDummyManoeuvre_1::runTestCase()
{
    DC_DummyManoeuvre  *pDM =new DC_DummyManoeuvre();
    const unsigned int  nEvt=getNumberOfEvents();

    // Verify correctness of class identifier
    if (pDM->getClassId()!=ID_DUMMYMANOEUVRE) {
		setTestResult(TEST_FAILURE,"Wrong class identifier");
		return;
	}

    // Newly created manoeuvres should be enabled
    if (!pDM->isEnabled()) {
		setTestResult(TEST_FAILURE,"Manoeuvre not enabled");
		return;
	}

    // Check value of continuation check code
    if ( pDM->getContinuationCheckCode()!=0 ) {
		setTestResult(TEST_FAILURE,"Continuation check code is incorrect");
		return;
	}

    // Newly created manoeuvres should not be in use
    if (pDM->isInUse()) {
		setTestResult(TEST_FAILURE,"Wrong value of inUse flag (true)");
		return;
	}

    // Newly created manoeuvres should not be executing
    if (pDM->isExecuting()) {
		setTestResult(TEST_FAILURE,"Wrong value of isExecuting flag (true)");
		return;
	}

    // Newly created manoeuvres should not be suspended
    if (pDM->isSuspended()) {
		setTestResult(TEST_FAILURE,"Wrong value of isSuspended flag (true)");
		return;
	}

	// Verify that the enable flag can be modified
	pDM->setEnabled(false);
    if (pDM->isEnabled()) {
		setTestResult(TEST_FAILURE,"Failed to disable the manoeuvre");
		return;
	}

	// Verify that the inUse flag can be modified
	pDM->setInUse(true);
    if (!pDM->isInUse()) {
		setTestResult(TEST_FAILURE,"Failed to change the inUse flag");
		return;
	}

	// Verify that the isSuspended flag can be modified
    pDM->setIsSuspended(true);
    if (!pDM->isSuspended()) {
		setTestResult(TEST_FAILURE,"Failed to change the isSuspended flag");
		return;
	}

	// Verify the event reporting
	if (!verifyLatestEvent(nEvt+1,EVT_MAN_SUSPENDED))
		return;

	// Resume manoeuvre and check correct event reporting
    pDM->setIsSuspended(false);
	if (!verifyLatestEvent(nEvt+2,EVT_MAN_RESUMED))
		return;

	// Verify that a disable manoeuvre cannot be started
	if (pDM->canStart()!=MAN_CANNOT_START) {
		setTestResult(TEST_FAILURE,"Disabled manoeuvre can be started");
		return;
	}

	// Now, let's check the opposite situation
	pDM->setEnabled(true);
	if (pDM->canStart()!=MAN_CAN_START) {
		setTestResult(TEST_FAILURE,"Enabled manoeuvre cannot be started");
		return;
	}

	// Let's start the manoeuvre
	pDM->initialize();
	pDM->doContinue();

	// Verify that the manoeuvre is executing
	if (!pDM->isExecuting()) {
		setTestResult(TEST_FAILURE,"Manoeuvre cannot be started");
		return;
	}

	// Verify the event reporting
	if (!verifyLatestEvent(nEvt+3,EVT_MAN_STARTED))
		return;

	// Check that the manoeuvre can continue
	if (!pDM->canContinue()) {
		setTestResult(TEST_FAILURE,"canContinue() reports wrong status");
		return;
	}

	// Verify the termination check
    if (!pDM->isFinished()) {
		setTestResult(TEST_FAILURE,"Failed termination check");
		return;
	}

	// The manoeuvre is aborted and the execution status and event report are verified
	pDM->abort();
	if (pDM->isExecuting()) {
		setTestResult(TEST_FAILURE,"Manoeuvre cannot be aborted");
		return;
	}

	if (!verifyLatestEvent(nEvt+4,EVT_MAN_ABORTED))
		return;

	// Let's now do a full initialization/execution/termination cycle
	pDM->initialize();
	pDM->doContinue();
	pDM->terminate();
	if (pDM->isExecuting()) {
		setTestResult(TEST_FAILURE,"Failed to terminate the manoeuvre");
		return;
	}

	// Verify the event reporting
	// The initialize()/doContinue() pair generates an event.
	if (!verifyLatestEvent(nEvt+6,EVT_MAN_TERMINATED))
		return;

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
