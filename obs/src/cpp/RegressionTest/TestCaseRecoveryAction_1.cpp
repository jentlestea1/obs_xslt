//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseRecoveryAction_1.cpp
//
// Version	1.0
// Date		25.06.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../FDIR/DC_NullRecoveryAction.h"
#include "../FDIR/DC_DummyRecoveryAction.h"
#include "TestCaseRecoveryAction_1.h"

TestCaseRecoveryAction_1::TestCaseRecoveryAction_1(void) :
	TestCaseGenericSetUp(ID_DUMMYRECOVERYACTION*10+1,"TestCaseRecoveryAction_1") {
	return;
}

void TestCaseRecoveryAction_1::runTestCase(void) {
	DC_NullRecoveryAction  *pNRA=new DC_NullRecoveryAction;
	DC_DummyRecoveryAction *pDRA=new DC_DummyRecoveryAction;

	// Verify the correctness of the class ids
	if (pNRA->getClassId()!=ID_NULLRECOVERYACTION) {
		setTestResult(TEST_FAILURE,"Wrong class id");
		return;
	}

	if (pDRA->getClassId()!=ID_DUMMYRECOVERYACTION) {
		setTestResult(TEST_FAILURE,"Wrong class id");
		return;
	}

	// Initially there shall be no next recovery action
	if (pDRA->getNextRecoveryAction()) {
		setTestResult(TEST_FAILURE,"Initialization failure");
		return;
	}

	// The execution flag shall be true: calling execute() shall return
	// ACTION_SUCCESS.
	if (pDRA->execute()!=ACTION_SUCCESS) {
		setTestResult(TEST_FAILURE,"Execution flag wrongly set");
		return;
	}

	// We set the execution flag to false. A call to execute()
	// shall now return ACTION_CANNOT_EXECUTE.
	pDRA->setExecutionFlag(false);
	if (pDRA->execute()!=ACTION_CANNOT_EXECUTE) {
		setTestResult(TEST_FAILURE,"setExecutionFlag() failed");
		return;
	}

	// Invoking pNRA->execute() shall return ACTION_SUCCESS
	if (pNRA->execute()!=ACTION_SUCCESS) {
		setTestResult(TEST_FAILURE,"Execution flag wrongly set");
		return;
	}

	// We now set pDRA as pNRA's next recovery action and verify
	// it worked.
	pNRA->setNextRecoveryAction(pDRA);
	if (pNRA->getNextRecoveryAction()!=pDRA) {
		setTestResult(TEST_FAILURE,"setNextRecoveryAction() failed");
		return;
	}

	// We set pDRA's outcome to ACTION_FAILURE and its execution
	// flag to true.
	pDRA->setActionOutcome(ACTION_FAILURE);
	pDRA->setExecutionFlag(true);

	// Calling pNRA->execute() shall now return pDRA's outcome
	// (that is ACTION_FAILURE).
	if (pNRA->execute()!=ACTION_FAILURE) {
		setTestResult(TEST_FAILURE,"Wrong outcome");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
