//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseCyclingPunctualActionModeManager_1.cpp
//
// Version	1.0
// Date		18.01.04
// Author	A. Pasetti (P&P Software)

#include "TestCaseCyclingPunctualActionModeManager_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/DC_CyclingPunctualActionModeManager.h"
#include "../Base/DC_DummyPunctualAction.h"
#include "../Base/ModeManager.h"
#include "../Event/DC_EventRepository.h"

TestCaseCyclingPunctualActionModeManager_1::TestCaseCyclingPunctualActionModeManager_1(void) :
	TestCaseWithEvtCheck(ID_CYCLINGPUNCTUALACTIONMODEMANAGER*10+1,"TestCaseCyclingPunctualActionModeManager_1") {
		return;
}

void TestCaseCyclingPunctualActionModeManager_1::runTestCase(void) {

    unsigned int nEvt = getNumberOfEvents();
    DC_CyclingPunctualActionModeManager* pMM = new DC_CyclingPunctualActionModeManager();

    // Verify correctness of class identifier
    if ( pMM->getClassId() != ID_CYCLINGPUNCTUALACTIONMODEMANAGER)
	{	setTestResult(TEST_FAILURE, "Wrong class identifier");
		return;
	}

    // Mode managers should not be configured at creation
    if ( pMM->isObjectConfigured() == CONFIGURED )
	{	setTestResult(TEST_FAILURE, "Wrong configuration status at creation");
		return;
	}

	// Create the items to be loaded in the list mode manager
	DC_DummyPunctualAction* list1 = new DC_DummyPunctualAction[3];
	DC_DummyPunctualAction* list2 = new DC_DummyPunctualAction[2];
	DC_DummyPunctualAction* list3 = new DC_DummyPunctualAction[3];

    // Configure the dummy mode manager
    TD_Mode n = 3;
    TD_Mode def = 1;
    pMM->setNumberOfModes(n);
    pMM->setDefaultMode(def);
    pMM->setListLength(0,3);
    pMM->setListLength(1,2);
    pMM->setListLength(2,3);
    pMM->setListItem(0,0,&list1[0]);
    pMM->setListItem(0,1,&list1[1]);
    pMM->setListItem(0,2,&list1[2]);
    pMM->setListItem(1,0,&list2[0]);
    pMM->setListItem(1,1,&list2[1]);
    pMM->setListItem(2,0,&list3[0]);
    pMM->setListItem(2,1,&list3[1]);
    pMM->setListItem(2,2,&list3[2]);
    pMM->reset();

    // Verify that the component is now configured
    if ( pMM->isObjectConfigured() != CONFIGURED )
	{	setTestResult(TEST_FAILURE, "Wrong configuration status");
		return;
	}

    // Iterate through the list items and verify correctness
    int i = 0;
    for (pMM->first(); !pMM->isIterationFinished(); pMM->next()) {
        PunctualAction* a = pMM->getIterationPunctualAction();
        if ( (a) != &list2[i] )
	    {	setTestResult(TEST_FAILURE, "Error during iteration");
		    return;
	    }
        i++;
    }
    if ( i != 2 )
	{	setTestResult(TEST_FAILURE, "Wrong number of iteration cycles");
		return;
	}

    // Check effect of non-nominal call to next()
    pMM->next();
    if ( &list2[1]!=(pMM->getIterationPunctualAction()) )
    {   setTestResult(TEST_FAILURE, "Error after non-nominal call to nextInt()");
	    return;
	}

    // Check iterators with an intermediate call to update()
    pMM->update();  // active list should now be a3[]
    if ( pMM->getCurrentMode()!=def+1 )
    {	setTestResult(TEST_FAILURE, "Wrong mode");
	    return;
    }

    pMM->first();                   // iteration list should now be a3[]
    PunctualAction* item = pMM->getIterationPunctualAction();
    if ( (item) != &list3[0] )
    {	setTestResult(TEST_FAILURE, "Error during iteration");
	    return;
    }

    pMM->update();  // active list should now be a1[] but iteration list should still be a3[]
    if ( pMM->getCurrentMode()!=0 )
    {	setTestResult(TEST_FAILURE, "Wrong mode");
	    return;
    }

    pMM->next();
    item = pMM->getIterationPunctualAction();
    if ( (item) != &list3[1] )
    {	setTestResult(TEST_FAILURE, "Error during iteration");
	    return;
    }

    // Attempt illegal reconfiguration of list and check correctness of event
    if (isNonNominalCheckAllowed()) {
        pMM->setListItem(1,2,&list2[1]);
        if (verifyLatestEvent(nEvt+1,EVT_ILLEGAL_MM))
            return;
        nEvt++;
    }

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
