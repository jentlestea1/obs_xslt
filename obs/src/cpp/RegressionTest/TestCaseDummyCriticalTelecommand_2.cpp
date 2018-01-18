//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyCriticalTelecommand_2.cpp
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
#include "TestCaseDummyCriticalTelecommand_2.h"

TestCaseDummyCriticalTelecommand_2::TestCaseDummyCriticalTelecommand_2(void) :
	TestCaseWithEvtCheck(ID_DUMMYCRITICALTELECOMMAND*10+2,
						 "TestCaseDummyCriticalTelecommand_2") {
	return;
}

void TestCaseDummyCriticalTelecommand_2::runTestCase(void) {
	const TD_ObsTime             timeTag         =0;
	const TD_ObsTime             maxArmedDuration=10;
    const unsigned int           nEvt            =getNumberOfEvents();
	DC_DummyObsClock            *pObsClk         =new DC_DummyObsClock();
	DC_DummyCriticalTelecommand *pTC             =new DC_DummyCriticalTelecommand();

	// Initialize the object, including the base class
	pTC->setTimeTag(timeTag);
	pTC->setMaxArmedDuration(maxArmedDuration);
	pTC->setObsClock(pObsClk);

    // First we test the non-critical behaviour
	pTC->setCriticalityLevel(false);

	// The TC is not critical: canExecute() shall return true
	if (!pTC->canExecute()) {
		setTestResult(TEST_FAILURE,"Non-critical TC can not be executed");
		return;
	}

	// Executing a non-critical TC should always result in a invocation
	// of doCriticalAction().
	if (pTC->execute()!=ACTION_SUCCESS) {
		setTestResult(TEST_FAILURE,"TC execute() failed");
		return;
	}

	if (pTC->getNumberOfExecutions()!=1) {
		setTestResult(TEST_FAILURE,"doCriticalAction() not called");
		return;
	}

	// We now make the TC critical. An invocation of canExecute() shall
	// return true. A subsequent call to execute() shall arm the TC, set the
	// "time when armed" to the current time, add an EVT_CRIT_TC_ARMED to the
	// event log and return ACTION_SUCCESS.
	pTC->setCriticalityLevel(true);

	if (!pTC->canExecute()) {
		setTestResult(TEST_FAILURE,"Disarmed, critical TC cannot be executed");
		return;
	}

	if (pTC->execute()!=ACTION_SUCCESS) {
		setTestResult(TEST_FAILURE,"TC execute() failed");
		return;
	}

	if (!pTC->isArmed()) {
		setTestResult(TEST_FAILURE,"Failed to arm TC");
		return;
	}

	if (pTC->getTimeWhenArmed()!=pObsClk->getTime()) {
		setTestResult(TEST_FAILURE,"Wrong \"time when armed\"");
		return;
	}

	if (!verifySpecificEvent((nEvt+2),EVT_CRIT_TC_ARMED))
		return;

	// Invoking isImageValid() on a newly created DC_DummyCriticalTelecommand
	// returns false, thus a new call to canExecute() shall return false and add
	// an EVT_CRIT_TC_IMG_INV event to the repository with the TC id as parameter.
	if (pTC->canExecute()) {
		setTestResult(TEST_FAILURE,"TC with invalid image can be executed");
		return;
	}

	if (!verifyLatestEvent((nEvt+4),EVT_CRIT_TC_IMG_INV))
		return;

	// The arm state shall be unmodifief
	if (!pTC->isArmed()) {
		setTestResult(TEST_FAILURE,"Unexpected change in arm state");
		return;
	}

	// Reset the TC in order to perform the next test
	pTC->reset();

	// Verify that reset() did its job
	if (pTC->getTimeWhenArmed()>=0) {
		setTestResult(TEST_FAILURE,"reset() failed (timeWhenArmed)");
		return;
	}

	if (pTC->isArmed()) {
		setTestResult(TEST_FAILURE,"reset() failed (isTcArmed)");
		return;
	}

	if (pTC->getMaxArmedDuration()>=0) {
		setTestResult(TEST_FAILURE,"reset() failed (maxArmedDuration");
		return;
	}

	// Clearly the TC shall also be re-initialized
	pTC->setObsClock(pObsClk);
	pTC->setMaxArmedDuration(maxArmedDuration);

	// Now the TC is no longer armed. We call execute() to arm it (we know canExecute()
	// would return true), set the image validity flag to true and call canExecute()
	// a second time. This time it shall return true.
	pTC->execute();
	pTC->setImageValidity(true);

	if (!pTC->canExecute()) {
		setTestResult(TEST_FAILURE,"Valid TC can not be executed");
		return;
	}

	// We now call execute() and verify that doCriticalAction() is invoked
	// and the TC is disarmed.
	pTC->execute();

	if (pTC->getNumberOfExecutions()!=2) {
		setTestResult(TEST_FAILURE,"doCriticalAction() not called");
		return;
	}

	if (pTC->isArmed()) {
		setTestResult(TEST_FAILURE,"Call to execute() did not disarm TC");
		return;
	}

	if (pTC->getTimeWhenArmed()>=0) {
		setTestResult(TEST_FAILURE,"\"Time when armed\" was not reset");
		return;
	}

	// Finally, we see what happens when a timeout occurs. In this case the image
	// validity shall play no role in the test outcome. We test both cases anyway.
	// First of all, the TC shall be reset, initialized and re-armed.
	pTC->reset();
	pTC->setObsClock(pObsClk);
	pTC->setMaxArmedDuration(maxArmedDuration);
	pTC->execute();

	// The image validity is set to true
	pTC->setImageValidity(true);

	// Then the OBS clock is set to a value such that the TC times out
	pObsClk->setTime(pTC->getTimeWhenArmed()+maxArmedDuration);
    pObsClk->setCycle(0);

	// And it is verified that the TC actually times out and an event is
	// reported
	if (pTC->canExecute()) {
		setTestResult(TEST_FAILURE,"Timed-out TC can be executed");
		return;
	}

	if (!verifyLatestEvent((nEvt+10),EVT_CRIT_TC_TIMEOUT))
		return;

	// We do the same on a TC with an invalid image
	pTC->reset();
	pTC->setObsClock(pObsClk);
	pTC->setMaxArmedDuration(maxArmedDuration);
	pTC->execute();

	// The image validity is set to false, this time
	pTC->setImageValidity(false);

	// The rest is the same as in the previous test
	pObsClk->setTime(pTC->getTimeWhenArmed()+maxArmedDuration);
    pObsClk->setCycle(0);

	if (pTC->canExecute()) {
		setTestResult(TEST_FAILURE,"Timed-out TC can be executed");
		return;
	}

	if (!verifyLatestEvent((nEvt+13),EVT_CRIT_TC_TIMEOUT))
		return;

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
