//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseProfileList_1.cpp
//
// Version	1.3
// Date		15.09.03 (Version 1.0)
//          01.10.03 (Version 1.1)
//          08.10.03 (Version 1.2)
//          21.10.03 (Version 1.3)
// Author	R. Totaro
//
// Change Record:
//   Version 1.1: Replaced double and int with TD_Float and TD_Integer
//   Version 1.2: Added check that isObjectConfigured() works according to specs
//   Version 1.3: Replaced all occurrences of loadMonitoringProfile() with setMonitoringProfile()

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../FDIR/DC_InRangeProfile.h"
#include "../FDIR/DC_ProfileList.h"
#include "TestCaseProfileList_1.h"

TestCaseProfileList_1::TestCaseProfileList_1(void) :
	TestCaseWithEvtCheck(ID_PROFILELIST*10+1,"TestCaseProfileList_1") {
	return;
}

void TestCaseProfileList_1::runTestCase(void) {
	DC_ProfileList    *pPL       =new DC_ProfileList;
    const unsigned int nEvt      =getNumberOfEvents();
	const unsigned int listSize  =2;
	const TD_Float     rangeWidth=5.0;
	DC_InRangeProfile *pIRP[listSize];

	// Create and initialize the monitoring profiles we are using to
	// test the DC_ProfileList class.
	for (unsigned int i=0;i<listSize;i++) {
		pIRP[i]=new DC_InRangeProfile;
		pIRP[i]->setLowerBound((TD_Float)i);
		pIRP[i]->setUpperBound((TD_Float)i+rangeWidth);
	}

	// Verify the correctness of the class id
	if (pPL->getClassId()!=ID_PROFILELIST) {
		setTestResult(TEST_FAILURE,"Wrong class identifier");
		return;
	}

	// A new object shall not be configured
	if (pPL->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Newly created object already configured");
		return;
	}

	// Set the list size and verify it is reported correctly
	pPL->setListSize(listSize);
	if (pPL->getListSize()!=listSize) {
		setTestResult(TEST_FAILURE,"getListSize() failed");
		return;
	}

	// Load and get the monitoring profiles
	for (unsigned int i=0;i<listSize;i++) {
	    // The object is fully configured only when all the profiles are loaded!
	    if (pPL->isObjectConfigured()) {
		    setTestResult(TEST_FAILURE,"Wrong configuration status");
		    return;
	    }

		pPL->setMonitoringProfile(i,pIRP[i]);

		if (pPL->getMonitoringProfile(i)!=pIRP[i]) {
			setTestResult(TEST_FAILURE,"setMonitoringProfile() failed");
			return;
		}
	}

	// Only now it is configured. Let's check it.
	if (!pPL->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Object not configured");
		return;
	}

    // Verify that setMonitoringProfile() generates an error report
	// when invoked with an invalid index
    if (isNonNominalCheckAllowed()) {
	    pPL->setMonitoringProfile(listSize,pIRP[0]);
        if (!verifyLatestEvent(nEvt+1,EVT_ILLEGAL_MP))
            return;
    }

	// These profile checks shall not fail
	if (pPL->deviatesFromProfile((TD_Integer)-1)) {
		setTestResult(TEST_FAILURE,"doProfileCheck(TD_Integer): unexpected failure");
		return;
	}

	if (pPL->deviatesFromProfile((TD_Float)-1.0)) {
		setTestResult(TEST_FAILURE,"doProfileCheck(TD_Float): unexpected failure");
		return;
	}

	// These profile checks shall fail
	if (!pPL->deviatesFromProfile((TD_Integer)1)) {
		setTestResult(TEST_FAILURE,"doProfileCheck(TD_Integer): unexpected success");
		return;
	}

	if (!pPL->deviatesFromProfile((TD_Float)1.0)) {
		setTestResult(TEST_FAILURE,"doProfileCheck(TD_Float): unexpected success");
		return;
	}

	if (!pPL->deviatesFromProfile((TD_Integer)(listSize+rangeWidth-2))) {
		setTestResult(TEST_FAILURE,"doProfileCheck(TD_Integer): unexpected success");
		return;
	}

	if (!pPL->deviatesFromProfile((TD_Float)(listSize+rangeWidth-2.0))) {
		setTestResult(TEST_FAILURE,"doProfileCheck(TD_Float): unexpected success");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
