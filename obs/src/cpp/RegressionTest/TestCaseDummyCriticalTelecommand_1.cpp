//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyCriticalTelecommand_1.cpp
//
// Version	1.0
// Date		17.06.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../System/DC_DummyObsClock.h"
#include "../Telecommand/DC_DummyCriticalTelecommand.h"
#include "TestCaseDummyCriticalTelecommand_1.h"

TestCaseDummyCriticalTelecommand_1::TestCaseDummyCriticalTelecommand_1(void) :
	TestCaseGenericSetUp(ID_DUMMYCRITICALTELECOMMAND*10+1,
						 "TestCaseDummyCriticalTelecommand_1") {
	return;
}

void TestCaseDummyCriticalTelecommand_1::runTestCase(void) {
	const TD_ObsTime             timeTag         =0;
	const TD_ObsTime             maxArmedDuration=10;
	ObsClock                    *pObsClk         =new DC_DummyObsClock();
	DC_DummyCriticalTelecommand *pTC             =new DC_DummyCriticalTelecommand();

	// Verify the correctness of the class id
	if (pTC->getClassId()!=ID_DUMMYCRITICALTELECOMMAND) {
		setTestResult(TEST_FAILURE,"Wrong class id");
		return;
	}

	// The following will configure CriticalTelecommand's base class...
	pTC->setTimeTag(timeTag);

	// ...however CriticalTelecommand shall still be unconfigured
	if (pTC->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Newly created object is configured");
		return;
	}

	// Let's set the armed duration and verify that the TC is not yet configured
	pTC->setMaxArmedDuration(maxArmedDuration);
	if (pTC->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Wrong configuration status");
		return;
	}

	// Verify that the max armed duration was properly set
	if (pTC->getMaxArmedDuration()!=maxArmedDuration) {
		setTestResult(TEST_FAILURE,"getMaxArmedDuration() failed");
		return;
	}

	// After this the TC shall be configured
	pTC->setObsClock(pObsClk);
	if (!pTC->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Wrong configuration status");
		return;
	}

	// Verify that the ObsClock pointer was properly set
	if (pTC->getObsClock()!=pObsClk) {
		setTestResult(TEST_FAILURE,"getObsClock() failed");
		return;
	}

	// A newly created TC shall be critical...
	if (!pTC->isCritical()) {
		setTestResult(TEST_FAILURE,"Newly created TC is critical");
		return;
	}

	// ...and should not be armed
	if (pTC->isArmed()) {
		setTestResult(TEST_FAILURE,"Newly created TC is armed");
		return;
	}

	// Let's verify that we can change the criticality level
	pTC->setCriticalityLevel(false);
	if (pTC->isCritical()) {
		setTestResult(TEST_FAILURE,"setCriticalityLevel() failed");
		return;
	}

	// Verify that isImageValid() and setImageValidity() work as expected
	if (pTC->isImageValid()) {
		setTestResult(TEST_FAILURE,"The image of a newly created TC is valid");
		return;
	}

	pTC->setImageValidity(true);
	if (!pTC->isImageValid()) {
		setTestResult(TEST_FAILURE,"setImageValidity() failed");
		return;
	}

	// Verify that the "time when armed" is invalid
	if (pTC->getTimeWhenArmed()>=0) {
		setTestResult(TEST_FAILURE,"Wrong initial \"time when armed\"");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
