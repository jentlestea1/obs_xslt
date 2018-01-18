//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseTestPUSConfigurableManoeuvre_1.cpp
//
// Version	1.0
// Date		06.02.04
// Author	A. Pasetti

#include "TestCaseTestPUSConfigurableManoeuvre_1.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Manoeuvre/DC_TestPUSConfigurableManoeuvre.h"

TestCaseTestPUSConfigurableManoeuvre_1::TestCaseTestPUSConfigurableManoeuvre_1(void) :
	TestCaseWithEvtCheck(ID_TESTPUSCONFIGURABLEMANOEUVRE*10+1,
						 "TestCaseTestPUSConfigurableManoeuvre_1") {
	return;
}

void TestCaseTestPUSConfigurableManoeuvre_1::runTestCase(void) {
    DC_TestPUSConfigurableManoeuvre *pDCM=new DC_TestPUSConfigurableManoeuvre();

    // Verify correctness of class identifier
    if (pDCM->getClassId()!=ID_TESTPUSCONFIGURABLEMANOEUVRE) {
		setTestResult(TEST_FAILURE,"Wrong class identifier");
		return;
	}

	// Check that the action counters are set to zero
	if (pDCM->getInitializationActionCounter()!=0 ||
		pDCM->getContinuationActionCounter()  !=0 ||
		pDCM->getTerminationActionCounter()   !=0) {
		setTestResult(TEST_FAILURE,"Action counter(s) not equal to zero");
		return;
	}

    // Check completion and progress acknowledge flag values
    if (pDCM->isCompletionAckRequired() || pDCM->isProgressAckRequired() || pDCM->isStartAckRequired() ) {
		setTestResult(TEST_FAILURE,"Incorrect acknowledge flag default values");
		return;
	}

    // Set and read back start, completion and progress acknowledge flag values
    pDCM->setStartAckFlag(true);
    pDCM->setCompletionAckFlag(true);
    pDCM->setProgressAckFlag(true);
    if (!pDCM->isCompletionAckRequired() || !pDCM->isProgressAckRequired()) {
		setTestResult(TEST_FAILURE,"Incorrect acknowledge flag default values");
		return;
	}

    // Set and read back telecommand identifier value
    pDCM->setTelecommandId(13);
    if (pDCM->getTelecommandId()!=13) {
		setTestResult(TEST_FAILURE,"Incorrect telecommand ID value");
		return;
	}

	// Verify the canStart() return value
	pDCM->setInUse(true);
	if (pDCM->canStart()!=MAN_CANNOT_START) {
		setTestResult(TEST_FAILURE,"Incorrect canStart() return value");
		return;
	}

	// Verify that the initializationActionCounter is incremented
	pDCM->initialize();
	if (pDCM->getInitializationActionCounter()!=1) {
		setTestResult(TEST_FAILURE,"initializationActionCounter not incremented");
		return;
	}

	// Verify that the continuationActionCounter is incremented 
	pDCM->doContinue();
	if (pDCM->getContinuationActionCounter()!=1) {
		setTestResult(TEST_FAILURE,"continuationActionCounter not incremented");
		return;
	}

	// Verify a "manoeuvre progress event" is generated when the manoeuvre advances
    unsigned int nEvt = this->getNumberOfEvents();
	pDCM->doContinue();
	if (pDCM->getContinuationActionCounter()!=2) {
		setTestResult(TEST_FAILURE,"continuationActionCounter not incremented");
		return;
	}
    if (!verifyLatestEvent(nEvt+1,EVT_MAN_PROGRESS))   
        return;

	// Check that the continuation flag is properly set
	if (pDCM->canContinue()!=MAN_CANNOT_CONTINUE) {
		setTestResult(TEST_FAILURE,"Incorrect canContinue() return value");
		return;
	}

	// Check that the termination flag is properly set
	if (pDCM->isFinished()!=MAN_HAS_NOT_TERMINATED) {
		setTestResult(TEST_FAILURE,"Incorrect isFinished() return value");
		return;
	}

	// Verify that the terminationActionCounter is incremented
	pDCM->terminate();
	if (pDCM->getTerminationActionCounter()!=1) {
		setTestResult(TEST_FAILURE,"terminationActionCounter not incremented");
		return;
	}

	// Check that the status flags can be modified
    pDCM->setStartCheckStatus(MAN_CAN_START);
    pDCM->setContinuationCheckStatus(MAN_CAN_CONTINUE);
    pDCM->setTerminationCheckStatus(MAN_HAS_TERMINATED);

	pDCM->initialize();

	if (pDCM->canStart()!=MAN_CAN_START) {
		setTestResult(TEST_FAILURE,"Incorrect canStart() return value");
		return;
	}

	pDCM->doContinue();

	if (pDCM->canContinue()!=MAN_CAN_CONTINUE) {
		setTestResult(TEST_FAILURE,"Incorrect canContinue() return value");
		return;
	}

	if (pDCM->isFinished()!=MAN_HAS_TERMINATED) {
		setTestResult(TEST_FAILURE,"Incorrect isFinished() return value");
		return;
	}

	pDCM->terminate();

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
