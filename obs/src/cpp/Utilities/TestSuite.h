//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCase.h
//
// Version	1.0
// Date		13.09.02
// Author	A. Pasetti (P&P Software)
//

//
// A test suite is a collection of test cases that are intended to be
// executed as a single unit.

#ifndef TestSuiteH
#define TestSuiteH

//class TestCase;
#include "TestCase.h"
#include <stdio.h>

/**
 * Collection of test cases that are intended to be
 * executed as a single unit.
 * A test suite is used intended to be used as follows. First, the test cases
 * are <i>loaded</i> into the test suite. Then, the test suite is <i>executed</i>. This
 * causes all the test cases loaded in the test suite to be executed in sequence.
 * The test suite is responsible for setting up, executing, and shutting down
 * each test case. After a test case has been shut down, the test suite queries it
 * for the outcome of the test and writes this outcome together with the accompanying
 * test message to an <i>output file</i>.
 * The data structure holding the test cases is defined statically and can hold a
 * maximum of MAX_TEST_CASES_IN_SUITE test cases.
 * @see TestCase
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup TestCases
 */
class TestSuite {

	TestCase* list[MAX_TEST_CASES_IN_SUITE];
	int testCaseCounter;
	FILE* out;

public :

     /**
      * Constructor defining the output file.
      * @param out the output file
      */
	TestSuite(FILE* out);

     /**
      * Execute all the test cases currently loaded in the test suite and
      * write outcome information to the output file
      */
	void runTestSuite(void);
	
     /**
      * Load a new test case in the test suite.
      * If the maximum number of test cases in the test suite has been exceeded,
      * then an error message is written to the output file.
      * @param newTestCase the test case to be loaded
      */
	void loadTestCase(TestCase* newTestCase);
};

#endif
