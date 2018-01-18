//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseSimplePunctualActionModeManager_1.cpp
//
// Version	1.0
// Date		29.09.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/DC_SimplePunctualActionModeManager.h"
#include "../Base/DC_DummyPunctualAction.h"
#include "../Base/ModeManager.h"
#include "TestCaseSimplePunctualActionModeManager_1.h"

TestCaseSimplePunctualActionModeManager_1::TestCaseSimplePunctualActionModeManager_1(void) :
	TestCaseGenericSetUp(ID_SIMPLEPUNCTUALACTIONMODEMANAGER*10+1,
                         "TestCaseSimplePunctualActionModeManager_1") {
    return;
}

void TestCaseSimplePunctualActionModeManager_1::runTestCase(void) {
    PunctualAction                     *pPA=new DC_DummyPunctualAction;
    DC_SimplePunctualActionModeManager *pMM=new DC_SimplePunctualActionModeManager;

    // Verify correctness of class identifier
    if (pMM->getClassId()!=ID_SIMPLEPUNCTUALACTIONMODEMANAGER) {
        setTestResult(TEST_FAILURE,"Wrong class identifier");
		return;
	}

    // Configure the simple punctual action mode manager with
    // one list of 1 dummy punctual action
    pMM->setListLength(0,1);
    pMM->setListItem(0,0,pPA);
    pMM->reset();

    // Check that the telemetry mode managers is configured
    if (!pMM->isObjectConfigured()) {
        setTestResult(TEST_FAILURE,"Wrong configuration status at creation");
		return;
	}

    // Check current mode and number of modes
    if (pMM->getNumberOfModes()!=1) {
        setTestResult(TEST_FAILURE,"Wrong number of modes");
		return;
	}

    if (pMM->getCurrentMode()) {
        setTestResult(TEST_FAILURE,"Wrong current mode");
		return;
	}

    // Make an update request and check that the current mode has not changed
    pMM->update();
    if (pMM->getCurrentMode()!=0) {
        setTestResult(TEST_FAILURE,"Wrong current mode");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
