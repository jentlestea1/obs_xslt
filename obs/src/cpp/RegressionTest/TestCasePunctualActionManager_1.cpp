//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCasePunctualActionManager_1.cpp
//
// Version	1.0
// Date		30.09.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../Base/DC_DummyPunctualAction.h"
#include "../Base/DC_SimplePunctualActionModeManager.h"
#include "../Base/CC_PunctualActionManager.h"
#include "TestCasePunctualActionManager_1.h"

TestCasePunctualActionManager_1::TestCasePunctualActionManager_1(void) :
	TestCaseGenericSetUp(ID_PUNCTUALACTIONMANAGER*10+1,"TestCasePunctualActionManager_1") {
	return;
}

void TestCasePunctualActionManager_1::runTestCase(void) {
    const unsigned int         numberOfActions=4;
    CC_PunctualActionManager  *pPAM =new CC_PunctualActionManager;
    DC_SimplePunctualActionModeManager *pPAMM=new DC_SimplePunctualActionModeManager;

    // Configure the mode manager and the add a newly created
    // punctual actions to its only list
    pPAMM->setListLength(0,numberOfActions);

    for (unsigned int i=0;i<numberOfActions;i++)
        pPAMM->setListItem(0,i,new DC_DummyPunctualAction);

    pPAMM->reset();

	// Verify the correctness of the class id
	if (pPAM->getClassId()!=ID_PUNCTUALACTIONMANAGER) {
		setTestResult(TEST_FAILURE,"Wrong class id");
		return;
	}

    // A newly created action manager shall not be configured
    if (pPAM->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Wrong configuration status at creation");
		return;
    }

    // The mode manager pointer shall be null
    if (pPAM->getPunctualActionModeManager()) {
		setTestResult(TEST_FAILURE,"Non NULL mode manager pointer at creation");
		return;
    }

    // Now we set the mode manager pointer and we verify that it is properly
    // stored and that the object is configured
    pPAM->setPunctualActionModeManager(pPAMM);
    if (pPAM->getPunctualActionModeManager()!=pPAMM) {
		setTestResult(TEST_FAILURE,"setPunctualActionModeManager() failed");
		return;
    }

    if (!pPAM->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Wrong configuration status");
		return;
    }

    // The activate() method is invoked twice and it is verified that
    // the punctual actions' activation counters reflect this fact
    pPAM->activate();
    pPAM->activate();

    for (pPAMM->first();pPAMM->isIterationFinished();pPAMM->next()) {
        DC_DummyPunctualAction *pDPA;

        pDPA=(DC_DummyPunctualAction *)pPAMM->getIterationPunctualAction();
        if (pDPA->getActivationCounter()!=2) {
            setTestResult(TEST_FAILURE,"activate() failed");
            return;
        }
    }

    setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
