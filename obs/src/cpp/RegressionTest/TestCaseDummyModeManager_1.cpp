//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyModeManager_1.cpp
//
// Version	1.1
// Date		14.04.03
// Author	A. Pasetti (P&P Software)

#include "TestCaseDummyModeManager_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Base/DC_DummyModeManager.h"
#include "../Base/ModeManager.h"
#include "../Event/DC_EventRepository.h"

TestCaseDummyModeManager_1::TestCaseDummyModeManager_1(void) :
	TestCaseWithEvtCheck(ID_DUMMYMODEMANAGER*10+1,"TestCaseDummyModeManager_1") {
		return;
}

void TestCaseDummyModeManager_1::runTestCase(void) {

    unsigned int nEvt = getNumberOfEvents();
    DC_DummyModeManager* pMM = new DC_DummyModeManager();
    DC_EventRepository* pRep = pMM->getEventRepository();

    // Verify correctness of class identifier
    if ( pMM->getClassId() != ID_DUMMYMODEMANAGER)
	{	setTestResult(TEST_FAILURE, "Wrong class identifier");
		return;
	}

    // Dummy mode managers should not be configured at creation
    if ( pMM->isObjectConfigured() == CONFIGURED )
	{	setTestResult(TEST_FAILURE, "Wrong configuration status at creation");
		return;
	}

    // Load number of modes and check correctness
    TD_Mode n = 3;
    pMM->setNumberOfModes(n);
    if ( pMM->getNumberOfModes() != n)
	{	setTestResult(TEST_FAILURE, "Wrong number of modes");
		return;
	}

    // Load default mode and check that component is configured
    TD_Mode def = 1;
    pMM->setDefaultMode(def);
    if ( pMM->isObjectConfigured() != CONFIGURED )
	{	setTestResult(TEST_FAILURE, "Wrong configuration status");
		return;
	}

    // Attempt to load illegal default mode and check correct event
    if (isNonNominalCheckAllowed()) {
        pMM->setDefaultMode(3);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_MM) )
	        return;
        nEvt++;
    }

    // Reset the component to complete initialization sequence
    // The current mode should be the default mode
    pMM->reset();
    if ( pMM->getCurrentMode() != def)
	{	setTestResult(TEST_FAILURE, "Current mode is not default mode");
		return;
	}

    // Check that all mode transitions are enabled
    if ( !pMM->isTransitionEnabled() )
	{	setTestResult(TEST_FAILURE, "Transitions are not enabled");
		return;
	}
    for (TD_Mode i=0; i<n; i++)
        if ( !pMM->isTransitionEnabled(i) )
    	{	setTestResult(TEST_FAILURE, "Transition is not enabled");
	    	return;
	    }

    // Perform an update and verify correct functioning and event reporting
    pMM->update();
    if ( pMM->getCurrentMode() != def+1 )
	{	setTestResult(TEST_FAILURE, "Mode transition was not performed");
		return;
	}
    if ( pRep->getCounter() != nEvt+1 )
	{	setTestResult(TEST_FAILURE, "Wrong number of events");
		return;
	}
    if (!verifyLatestEvent(nEvt+1,EVT_MOD_TRANS_PERFORMED))
		return;
    nEvt++;

    // Disable mode transitions and verify correctness
    pMM->setTransitionEnableStatus(DISABLED);
    if ( pMM->isTransitionEnabled() )
	{	setTestResult(TEST_FAILURE, "Wrong transition enable status");
		return;
	}

    // Attempt update and verify that no mode transition occurs and that
    // event report was correctly generated
    pMM->update();
    if ( pMM->getCurrentMode() != def+1 )
	{	setTestResult(TEST_FAILURE, "Wrong operational mode");
		return;
	}
    if (!verifyLatestEvent(nEvt+1,EVT_MOD_TRANS_INHIBITED))
		return;
    nEvt++;

    // Disable transitions to mode and verify correctness
    pMM->setTransitionEnableStatus(ENABLED);
    pMM->setTransitionEnableStatus(1,DISABLED);
    if ( pMM->isTransitionEnabled(1) != DISABLED )
	{	setTestResult(TEST_FAILURE, "Wrong enable status");
		return;
	}

    // Make two update requests. The last one should fail
    pMM->update();  // perform transition from mode 2 to mode 0
    pMM->update();  // attempt (disabled) transitions from mode 0 to mode 1
    if ( pMM->getCurrentMode() != 0 )
	{	setTestResult(TEST_FAILURE, "Wrong mode");
		return;
	}
    nEvt = nEvt+2; // each call to update() should generate an event

    // Attempt to todisable transition to non-existent mode and check correct event
    if (isNonNominalCheckAllowed()) {
        pMM->setTransitionEnableStatus(3,false);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_MM) )
	        return;
        nEvt++;
    }

    // Perform reset and verify correctness
    pMM->reset();
    if ( pMM->getCurrentMode() != def )
	{	setTestResult(TEST_FAILURE, "Wrong mode after reset");
		return;
	}
    if ( !pMM->isTransitionEnabled() )
	{	setTestResult(TEST_FAILURE, "Wrong transition enable status after reset");
		return;
	}
    for (TD_Mode i=0; i<n; i++)
        if ( !pMM->isTransitionEnabled(i) )
    	{	setTestResult(TEST_FAILURE, "Transition is not enabled after reset");
	    	return;
	    }

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
