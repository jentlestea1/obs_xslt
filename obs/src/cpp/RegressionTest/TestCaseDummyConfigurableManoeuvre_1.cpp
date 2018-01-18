//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyConfigurableManoeuvre_1.cpp
//
// Version	1.0
// Date		06.05.03
// Author	R. Totaro

#include "TestCaseDummyConfigurableManoeuvre_1.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../Manoeuvre/DC_DummyConfigurableManoeuvre.h"

TestCaseDummyConfigurableManoeuvre_1::TestCaseDummyConfigurableManoeuvre_1(void) :
	TestCaseGenericSetUp(ID_DUMMYCONFIGURABLEMANOEUVRE*10+1,
						 "TestCaseDummyConfigurableManoeuvre_1") {
	return;
}

void TestCaseDummyConfigurableManoeuvre_1::runTestCase(void) {
    DC_DummyConfigurableManoeuvre *pDCM=new DC_DummyConfigurableManoeuvre();

    // Verify correctness of class identifier
    if (pDCM->getClassId()!=ID_DUMMYCONFIGURABLEMANOEUVRE) {
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
