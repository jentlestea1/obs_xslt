//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseEventRepository_3.cpp
//
// Version	1.1
// Date		25.02.03
// Author	A. Pasetti (P&P Software)

#include "TestCaseEventRepository_3.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../System/DC_DummyObsClock.h"
#include "../Event/DC_EventRepository.h"
#include "../Event/DC_Event.h"

TestCaseEventRepository_3::TestCaseEventRepository_3(void) :
	TestCaseGenericSetUp(ID_EVENTREPOSITORY*10+3,"TestCaseEventRepository_3") {
		return;
}

void TestCaseEventRepository_3::runTestCase(void) {

   DC_EventRepository* pRep = new DC_EventRepository();

   TD_EventType type1 = (TD_EventType)0x0001;
   TD_EventType type2 = (TD_EventType)0x0002;
   TD_EventType type3 = (TD_EventType)0x0010;

   // Configure the event repository: load OBS clock and set repository size
   unsigned int size = 4;
   DC_DummyObsClock* pClk = new DC_DummyObsClock();
   pRep->setObsClock(pClk);
   pRep->setRepositorySize(size);

   // Check correct configuration
   if ( (pRep->isObjectConfigured() == NOT_CONFIGURED) )
	{	setTestResult(TEST_FAILURE,
           "Wrong event repository configuration status after configuration");
 	   return;
	}

   // Fill up the repository with a few events
   pRep->create(pRep,type1);
   pRep->create(pRep,type2);
   pRep->create(pRep,type3);
   pRep->create(pRep,type1);
   pRep->create(pRep,type2);

   // Disable repository and check correctness
   pRep->setEnabled(DISABLED);
   if ( (pRep->isEnabled()) )
	{	setTestResult(TEST_FAILURE,"Wrong enable status");
		return;
	}

   // Retrieve status of the repository
   unsigned int counter = pRep->getCounter();
   pRep->latest();
   TD_EventType type = pRep->getEventType();

   // Attempt to create event and check that nothing happens
   pRep->create(pRep,type1);
   if ( (pRep->getCounter() != counter) )
	{	setTestResult(TEST_FAILURE,"Event created in disabled repository");
		return;
	}
   pRep->latest();
   if ( pRep->getEventType() != type )
	{	setTestResult(TEST_FAILURE,
             "Event created in disabled repository");
		return;
	}

   // Enable repositoy and check that events can now be created
   pRep->setEnabled(ENABLED);
   pRep->create(pRep,type3);
   if ( (pRep->getCounter() != counter+1) )
	{	setTestResult(TEST_FAILURE,"Failure to create event in enabled repository");
		return;
	}
   pRep->latest();
   if ( pRep->getEventType() != type3 )
	{	setTestResult(TEST_FAILURE,
             "Failure to create event in enabled repository");
		return;
	}

   // Set event repository mask and check that the correct mask is loaded
    pRep->setEnabled(type2,DISABLED);
    if ( pRep->isEnabled(type2) )
	{	setTestResult(TEST_FAILURE,
             "Error in setting event repository mask");
		return;
	}

   // Check that creation of masked event is disabled
   pRep->create(pRep,type2);
   if ( (pRep->getCounter() != counter+1) )
	{	setTestResult(TEST_FAILURE,"Failure to selectively disabled event creation");
		return;
	}

   // Check that creation of unmasked events is still ensabled
   pRep->create(pRep,type3);
   if ( (pRep->getCounter() != counter+2) )
	{	setTestResult(TEST_FAILURE,"Failure to selectively enabled event creation");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
