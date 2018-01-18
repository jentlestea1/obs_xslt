//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyConditionalPunctualAction_1.cpp
//
// Version	1.0
// Date		04.06.03
// Author	R. Totaro

#include "TestCaseDummyConditionalPunctualAction_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/DC_DummyConditionalPunctualAction.h"

TestCaseDummyConditionalPunctualAction_1::TestCaseDummyConditionalPunctualAction_1(void) :
	TestCaseGenericSetUp(ID_DUMMYCONDITIONALPUNCTUALACTION*10+1,
						 "TestCaseDummyConditionalPunctualAction_1") {
	return;
}

void TestCaseDummyConditionalPunctualAction_1::runTestCase(void) {
	DC_DummyConditionalPunctualAction *pAct=new DC_DummyConditionalPunctualAction();

	// Verify correctness of the class identifier
	if (pAct->getClassId()!=ID_DUMMYCONDITIONALPUNCTUALACTION) {
		setTestResult(TEST_FAILURE,"Wrong class identifier");
		return;
	}

	// Let's set the execution flag to false and verify that the
	// action does not execute
	pAct->setExecutionFlag(false);
	if (pAct->execute()!=ACTION_CANNOT_EXECUTE) {
		setTestResult(TEST_FAILURE,"Action could be executed");
		return;
	}

	// Now we perform the opposite test
	pAct->setExecutionFlag(true);
	if (pAct->execute()!=ACTION_SUCCESS) {
		setTestResult(TEST_FAILURE,"Action could not be executed");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
