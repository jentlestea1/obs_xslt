//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCase.cpp
//
// Version	1.0
// Date		13.09.02
// Author	A. Pasetti (P&P Software)
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestConstants.h"
#include "TestCase.h"
#include <string.h>

TestCase::TestCase(int id,char* name) {
	testId = id;

	testName = new char[strlen(name)+1];
	strcpy(testName,name);

	testResultFlag = false;
}

void TestCase::setTestResult(bool outcome, char* msg) {
    // Check that method is called for the first time
    if (testResultFlag) {
        const char *error = "INVALID TEST -- SetTestResult called more than once";

        testOutcome = false;
        testMessage = new char[strlen(error)+1];
        strcpy(testMessage,error);
    }
    else {
        testOutcome = outcome;
        testMessage = new char[strlen(msg)+1];
        strcpy(testMessage,msg);
    }
}

bool TestCase::isNonNominalCheckAllowed(void) const {
#if defined(NDEBUG) || !defined(USE_SYSTEM_ASSERT)
    return true;
#else
    return false;
#endif
}

bool TestCase::shutDownTestCase(void) {
     return SHUTDOWN_SUCCESS;
}

bool TestCase::setUpTestCase(void) {
	return INITIALIZATION_SUCCESS;
}

char* TestCase::getTestName(void) const {
     return testName;
}

bool TestCase::getTestOutcome(void) const {
     return testOutcome;
}

char* TestCase::getTestMessage(void) const {
     return testMessage;
}
