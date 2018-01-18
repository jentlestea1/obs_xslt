//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyObsClock_1.cpp
//
// Version	1.1
// Date		14.04.03
// Author	A. Pasetti (P&P Software)

#include "TestCaseDummyObsClock_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../System/DC_DummyObsClock.h"

TestCaseDummyObsClock_1::TestCaseDummyObsClock_1(void) :
	TestCaseGenericSetUp(ID_DUMMYOBSCLOCK*10+1,"TestCaseDummyObsClock_1") {
		return;
}

void TestCaseDummyObsClock_1::runTestCase(void) {

     DC_DummyObsClock* pClk = new DC_DummyObsClock();

     // Dummy OBS Clock objects should be configured upon creation
     if ( (pClk->isObjectConfigured() != CONFIGURED) )
	{	setTestResult(TEST_FAILURE, "Dummy OBS clock component should be configured");
		return;
	}

     // Check that the timing data have correct values (they should be zero
     // upon creation)
	if ( (pClk->getTime() != 0) || (pClk->getCycle() != 0) )
	{	setTestResult(TEST_FAILURE, "Incorrect timing initial values");
		return;
	}

     // Set the timing data
     pClk->setTime(10);
     pClk->setCycle(1);

     // Check that the timing data have correct values
	if ( (pClk->getTime() != 10) || (pClk->getCycle() != 1) )
	{	setTestResult(TEST_FAILURE, "Incorrect timing values");
		return;
	}

     // Reset clock component and verify that time and cycle are reset to 0
     pClk->reset();
	if ( (pClk->getTime() != 0) || (pClk->getCycle() != 0) )
	{	setTestResult(TEST_FAILURE, "Timing data have not been correctly reset");
		return;
	}

    // Do dummy method call
    pClk->synchronizeWithSystemTime();

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
