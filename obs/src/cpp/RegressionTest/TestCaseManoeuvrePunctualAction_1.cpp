//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseManoeuvrePunctualAction_1.cpp
//
// Version	1.0
// Date		06.06.03
// Author	R. Totaro

#include "TestCaseManoeuvrePunctualAction_1.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../Manoeuvre/DC_DummyManoeuvre.h"
#include "../Manoeuvre/CC_ManoeuvreManager.h"
#include "../Manoeuvre/DC_ManoeuvrePunctualAction.h"

TestCaseManoeuvrePunctualAction_1::TestCaseManoeuvrePunctualAction_1(void) :
	TestCaseGenericSetUp(ID_MANOEUVREPUNCTUALACTION*10+1,"TestCaseManoeuvrePunctualAction_1") {
	return;
}

void TestCaseManoeuvrePunctualAction_1::runTestCase(void) {
	Manoeuvre                  *pDM =new DC_DummyManoeuvre();
	CC_ManoeuvreManager        *pMM =new CC_ManoeuvreManager();
    DC_ManoeuvrePunctualAction *pMPA=new DC_ManoeuvrePunctualAction();

	// Initialize the manoeuvre manager
	pMM->setPendingManoeuvreListSize(1);

    // Verify correctness of class identifier
    if (pMPA->getClassId()!=ID_MANOEUVREPUNCTUALACTION) {
		setTestResult(TEST_FAILURE,"Wrong class identifier");
		return;
	}

	// The newly created object should not be configured
	if (pMPA->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Newly created object is configured");
		return;
	}

	// We link a manoeuvre manager to the action and verify that
	// it is properly reported and the object is not yet configured
	pMPA->setManoeuvreManager(pMM);

	if (pMPA->getManoeuvreManager()!=pMM) {
		setTestResult(TEST_FAILURE,"Could not set/get the manoeuvre manager");
		return;
	}

	if (pMPA->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Wrong configuration status");
		return;
	}

	// We link a manoeuvre to the action and verify that it
	// is properly reported and the object is now configured
	pMPA->setManoeuvre(pDM);

	if (pMPA->getManoeuvre()!=pDM) {
		setTestResult(TEST_FAILURE,"Could not set/get the manoeuvre");
		return;
	}

	if (!pMPA->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Object is not configured");
		return;
	}

	// Let's execute the action and verify that the manoeuvre is loaded
	pMPA->execute();

	if (pMM->getPendingManoeuvres()!=1) {
		setTestResult(TEST_FAILURE,"Action failed to execute");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
