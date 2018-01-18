//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyDatabase_1.cpp
//
// Version	1.0
// Date		13.09.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_DummyDatabase.h"
#include "TestCaseDummyDatabase_1.h"

TestCaseDummyDatabase_1::TestCaseDummyDatabase_1(void) :
	TestCaseGenericSetUp(ID_DUMMYDATABASE*10+1,"TestCaseDummyDatabase_1") {
		return;
}

void TestCaseDummyDatabase_1::runTestCase(void) {

   // Instantiate basic database
   DC_DummyDatabase* pDB = new DC_DummyDatabase();

   // Verify correctness of class ID
   if (pDB->getClassId() != ID_DUMMYDATABASE)
	{	setTestResult(TEST_FAILURE, "Wrong class ID");
		return;
	}

   // Check that size of the database
    if ( pDB->getTableLength() != 1 )
	{	setTestResult(TEST_FAILURE, "Incorrect database size");
		return;
	}

   // Check the value of the database item
    if ( pDB->getParameterChar(0) != 0 )
	{	setTestResult(TEST_FAILURE, "Incorrect database parameter value");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
