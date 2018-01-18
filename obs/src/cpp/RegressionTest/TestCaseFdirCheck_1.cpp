//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseFdirCheck_1.cpp
//
// Version	1.0
// Date		26.06.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../FDIR/DC_FdirCheck.h"
#include "../FDIR/DC_DummyRecoveryAction.h"
#include "TestCaseFdirCheck_1.h"

TestCaseFdirCheck_1::TestCaseFdirCheck_1(void) :
	TestCaseGenericSetUp(ID_FDIRCHECK*10+1,"TestCaseFdirCheck_1") {
	return;
}

void TestCaseFdirCheck_1::runTestCase(void) {
	DC_FdirCheck           *pFDIR=new DC_FdirCheck;
	DC_DummyRecoveryAction *pFDI =new DC_DummyRecoveryAction;
	DC_DummyRecoveryAction *pDRA =new DC_DummyRecoveryAction;

	// Verify the correctness of the class id
	if (pFDIR->getClassId()!=ID_FDIRCHECK) {
		setTestResult(TEST_FAILURE,"Wrong class id");
		return;
	}

	// A newly created FDIR check shall not be configured
	if (pFDIR->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Newly created FDIR check is configured");
		return;
	}

	// Let's set the FDI, verify it is properly set and that the object
	// is not configured
	pFDIR->setFdiCheck(pFDI);

	if (pFDIR->getFdiCheck()!=pFDI) {
		setTestResult(TEST_FAILURE,"setFdiCheck() failed");
		return;
	}

	if (pFDIR->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Wrong configuration status");
		return;
	}

	// We now set the recovery action and verify that it is properly
	// set. The object shall now be configured.
	pFDIR->setRecoveryAction(pDRA);

	if (pFDIR->getRecoveryAction()!=pDRA) {
		setTestResult(TEST_FAILURE,"setRecoveryAction() failed");
		return;
	}

	if (!pFDIR->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Wrong configuration status");
		return;
	}

	// The FDI check return code is set to ACTION_CANNOT_EXECUTE. This is what
	// we shall get from a call to pFDIR->execute().
	pFDI->setActionOutcome(ACTION_CANNOT_EXECUTE);

	if (pFDIR->execute()!=ACTION_CANNOT_EXECUTE) {
		setTestResult(TEST_FAILURE,"Wrong FDI check outcome");
		return;
	}

	// Now, the FDI check outcome is set to ACTION_FAILURE. The recovery action
	// shall be executed and its outcome (set to ACTION_CANNOT_EXECUTE) shall
	// be returned to the caller.
	pFDI->setActionOutcome(ACTION_FAILURE);
	pDRA->setActionOutcome(ACTION_CANNOT_EXECUTE);

	if (pFDIR->execute()!=ACTION_CANNOT_EXECUTE) {
		setTestResult(TEST_FAILURE,"Wrong recovery action outcome");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
