//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseSimpleTelemetryModeManager_1.cpp
//
// Version	1.0
// Date		24.02.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_SimpleTelemetryModeManager.h"
#include "../Telemetry/DC_DataItem16TmWord.h"
#include "../Base/ModeManager.h"
#include "TestCaseSimpleTelemetryModeManager_1.h"

TestCaseSimpleTelemetryModeManager_1::TestCaseSimpleTelemetryModeManager_1(void) :
	TestCaseGenericSetUp(ID_SIMPLETELEMETRYMODEMANAGER*10+1,"TestCaseSimpleTelemetryModeManager_1") {
		return;
}

void TestCaseSimpleTelemetryModeManager_1::runTestCase(void) {

    DC_SimpleTelemetryModeManager* pMM = new DC_SimpleTelemetryModeManager();

    // Verify correctness of class identifier
    if ( pMM->getClassId() != ID_SIMPLETELEMETRYMODEMANAGER)
	{	setTestResult(TEST_FAILURE, "Wrong class identifier");
		return;
	}

    // Configure the simple telemetry mode manager with
    // one list of 2 dummy telemetry words
    pMM->setListLength(0,1);
    DC_DataItem16TmWord* pW = new DC_DataItem16TmWord();
    pMM->setListItem(0,0,pW);
    pMM->reset();

    // Check that the telemetry mode managers is configured
    if ( pMM->isObjectConfigured() != CONFIGURED )
	{	setTestResult(TEST_FAILURE, "Wrong configuration status at creation");
		return;
	}

    // Check current mode and number of modes
    if ( pMM->getNumberOfModes() != 1 )
	{	setTestResult(TEST_FAILURE, "Wrong number of modes");
		return;
	}
    if ( pMM->getCurrentMode() != 0 )
	{	setTestResult(TEST_FAILURE, "Wrong current mode");
		return;
	}

    // Make an update request and check that the current mode has not changed
    pMM->update();
    if ( pMM->getCurrentMode() != 0 )
	{	setTestResult(TEST_FAILURE, "Wrong current mode");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
