//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestSuite.cpp
//
// Version	1.0
// Date		13.09.02
// Author	     A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "TestSuite.h"
#include "TestCase.h"
#include "../Utilities/TestUtilities.h"
#include <string.h>

TestSuite::TestSuite(FILE* outputFile) {

	out = outputFile;
	testCaseCounter = 0;
}

void TestSuite::runTestSuite(void) {

     printRegressionTestHeader(out);

	for (int i=0; i<testCaseCounter; i++)
	{
        if (!list[i]->setUpTestCase()) {
               printErrorMsg(out,list[i]->getTestName(),"Test set up failed ...");
               continue;
        } else {
		       list[i]->runTestCase();
        }
        if (!list[i]->shutDownTestCase()) {
               printErrorMsg(out,list[i]->getTestName(),"Test shut down failed ...");
               continue;
        }

		if (list[i]->getTestOutcome())
			printTestSuccess(out,list[i]->getTestName(),list[i]->getTestMessage());
		else
			printTestFailed(out,list[i]->getTestName(),list[i]->getTestMessage());
	}

     printRegressionTestTail(out);
}

void TestSuite::loadTestCase(TestCase* newTestCase) {

	if (testCaseCounter<MAX_TEST_CASES_IN_SUITE)
	{	list[testCaseCounter] = newTestCase;
		testCaseCounter++;
	}
     else
          printf("TestSuite: Test case %s could not be loaded because the list of test cases is already full ...",
                    newTestCase);
}
