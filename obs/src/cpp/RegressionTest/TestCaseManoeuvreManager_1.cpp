//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseManoeuvreManager_1.cpp
//
// Version	1.0
// Date		08.05.03
// Author	R. Totaro

#include "TestCaseManoeuvreManager_1.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../Manoeuvre/CC_ManoeuvreManager.h"
#include "../Manoeuvre/DC_DummyManoeuvre.h"

TestCaseManoeuvreManager_1::TestCaseManoeuvreManager_1(void) :
	TestCaseWithEvtCheck(ID_MANOEUVREMANAGER*10+1,"TestCaseManoeuvreManager_1") {
	return;
}

void TestCaseManoeuvreManager_1::runTestCase(void) {
    CC_ManoeuvreManager *pMM =new CC_ManoeuvreManager();
    const unsigned int   nEvt=getNumberOfEvents();
	const unsigned int   nMan=8;

    // Verify correctness of class identifier
    if (pMM->getClassId()!=ID_MANOEUVREMANAGER) {
		setTestResult(TEST_FAILURE,"Wrong class identifier");
		return;
	}

	// A newly created ManoeuvreManager shall not be configured
	if (pMM->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Newly created ManoeuvreManager already configured");
		return;
	}

	// Configure the ManoeuvreManager and verify the operation
	pMM->setPendingManoeuvreListSize(nMan);
	if (pMM->getPendingManoeuvreListSize()!=nMan) {
		setTestResult(TEST_FAILURE,"Wrong getPendingManoeuvreListSize return value");
		return;
	}

	// Now it should be configured
	if (!pMM->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"ManoeuvreManager not configured");
		return;
	}

	// Clearly, there shall be no pending manoeuvres
	if (pMM->getPendingManoeuvres()!=0) {
		setTestResult(TEST_FAILURE,"Wrong getPendingManoeuvres return value");
		return;
	}

	// The following steps check the load(), unload() and abort() methods.
	// Let's create an array of DC_DummyManoeuvre pointers to be used in the
	// subsequent tests.
	DC_DummyManoeuvre *pDM[nMan+1];

	for (unsigned int i=0; i<=nMan; i++)
        pDM[i]=new DC_DummyManoeuvre();

	for (unsigned int i=0;i<nMan;i++) {
		// Load the manouvre
		pMM->load(pDM[i]);

		// Verify that manCounter is incremented
		if (pMM->getPendingManoeuvres()!=(i+1)) {
			setTestResult(TEST_FAILURE,"manCounter was not incremented");
			return;
		}

		// Set the "in use" flag
        pDM[i]->setInUse(true);
	}

	// A manoeuvre is aborted and the effect of the operation verified
	pMM->abort(pDM[nMan-1]);
	if (pMM->getPendingManoeuvres()!=(nMan-1)) {
		setTestResult(TEST_FAILURE,"manCounter was not decremented");
		return;
	}

	// Check that the manouvre is no longer in use
	if (pDM[nMan-1]->isInUse()) {
		setTestResult(TEST_FAILURE,"Aborted manoeuvre still in use");
		return;
	}

	// Load the previously aborted manoeuvre
	pMM->load(pDM[nMan-1]);

	// Try loading more manoeuvres that the allocated space and verify
	// that the event is reported.
	pMM->load(pDM[nMan]);
	if (!verifyLatestEvent((nEvt+nMan+3),EVT_MAN_LIST_FULL))
		return;

	// Finally, let's reset the manoeuvre manager and verify that all
	// the pending manoeuvres are aborted.
	pMM->reset();
	for (int i=0;i<nMan;i++) {
		if (pDM[i]->isInUse()) {
			setTestResult(TEST_FAILURE,"Reset failed to abort a manoeuvre");
			return;
		}
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
