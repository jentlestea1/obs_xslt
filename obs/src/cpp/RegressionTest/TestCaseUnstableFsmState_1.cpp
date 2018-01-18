//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseUnstableFsmState_1.cpp
//
// Version	1.0
// Date		15.07.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../FSM/DC_UnstableFsmState.h"
#include "TestCaseUnstableFsmState_1.h"

TestCaseUnstableFsmState_1::TestCaseUnstableFsmState_1(void) :
	TestCaseGenericSetUp(ID_UNSTABLEFSMSTATE*10+1,"TestCaseUnstableFsmState_1") {
	return;
}

void TestCaseUnstableFsmState_1::runTestCase(void) {
	DC_UnstableFsmState *pUFS=new DC_UnstableFsmState;

	// Verify the correctness of the class id
	if (pUFS->getClassId()!=ID_UNSTABLEFSMSTATE) {
		setTestResult(TEST_FAILURE,"Wrong class id");
		return;
	}

    // Verify that isFinished() returns true
    if (!pUFS->isFinished()) {
		setTestResult(TEST_FAILURE,"isFinished() failed.");
		return;
    }

    // Dummy call to doContinue()
    pUFS->doContinue();

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
