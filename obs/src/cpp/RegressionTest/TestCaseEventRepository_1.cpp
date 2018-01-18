//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseEventRepository_1.cpp
//
// Version	1.1
// Date		18.04.03
// Author	A. Pasetti (P&P Software)

#include "TestCaseEventRepository_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../System/DC_DummyObsClock.h"
#include "../Event/DC_EventRepository.h"

TestCaseEventRepository_1::TestCaseEventRepository_1(void) :
	TestCaseGenericSetUp(ID_EVENTREPOSITORY*10+1,"TestCaseEventRepository_1") {
		return;
}

void TestCaseEventRepository_1::runTestCase(void) {

   DC_EventRepository* pRep = new DC_EventRepository();

   // Check the correctness of the class identifier
   if ( (pRep->getClassId() != ID_EVENTREPOSITORY) )
	{	setTestResult(TEST_FAILURE,
        "Wrong class identifier for the event repository class");
	   return;
	}

   // Event repository objects are not configured upon creation
   if ( (pRep->isObjectConfigured() == CONFIGURED) )
	{	setTestResult(TEST_FAILURE,
        "Wrong event repository configuration status upon repository creation");
	   return;
	}

   // Check the default values of the event repository attributes
   if ( !(pRep->isEnabled()) ||
        (pRep->getCounter() != 0) ||
        (pRep->getRepositorySize() != 0) )
	{	setTestResult(TEST_FAILURE,
             "Wrong default value of event repository attribute");
		return;
	}

    // Check default selective enable status (NB: event types are positive)
    for (unsigned int i=1; i<=(unsigned int)LAST_EVENT_TYPE; i++)
        if ( !pRep->isEnabled((TD_EventType)i) )
	   {	setTestResult(TEST_FAILURE,
             "Wrong default value of selective enable status");
		    return;
	   }

   // Load an OBS Clock component
   DC_DummyObsClock* pClk = new DC_DummyObsClock();
   pRep->setObsClock(pClk);

   // Verify that the OBS Clock was properly loaded
   if (pRep->getObsClock()!=pClk) {
        setTestResult(TEST_FAILURE,"setObsClock() failed.");
        return;
   }

   // Initialize the repository size
   pRep->setRepositorySize(4);

   // Event repository should now be configured
   if ( (pRep->isObjectConfigured() == NOT_CONFIGURED) )
	{	setTestResult(TEST_FAILURE,
             "Wrong event repository configuration status after configuration");
		return;
	}

   // Check repository size
   if ( pRep->getRepositorySize() != 4)
	{	setTestResult(TEST_FAILURE,
             "Wrong value of event repository size");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
