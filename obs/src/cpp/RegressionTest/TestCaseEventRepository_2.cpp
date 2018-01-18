//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseEventRepository_2.cpp
//
// Version	1.1
// Date		25.02.03
// Author	A. Pasetti (P&P Software)

#include "TestCaseEventRepository_2.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../System/DC_DummyObsClock.h"
#include "../Event/DC_EventRepository.h"
#include "../Event/DC_Event.h"

TestCaseEventRepository_2::TestCaseEventRepository_2(void) :
	TestCaseGenericSetUp(ID_EVENTREPOSITORY*10+2,"TestCaseEventRepository_2") {
		return;
}

void TestCaseEventRepository_2::runTestCase(void) {

   DC_EventRepository* pRep = new DC_EventRepository();

   TD_EventType type1 = (TD_EventType)1;
   TD_EventType type2 = (TD_EventType)2;
   TD_EventType type3 = (TD_EventType)3;

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

   // Create two events in the repository
   pClk->setTime(1);
   pClk->setCycle(1);
   pRep->create(pRep,type1);
   pClk->setTime(2);
   pClk->setCycle(1);
   pRep->create(pRep,type2);

   // Check value of event counter
   if ( (pRep->getCounter() != 2) )
	{	setTestResult(TEST_FAILURE,"Wrong number of events in event repository");
		return;
	}

   // Iterate through the events in the repository and verify their types
   pRep->latest();     // position event pointer on latest event
   if ( pRep->getEventType() != type2 )
	{	setTestResult(TEST_FAILURE,
             "Wrong event type for latest event");
		return;
	}

    if (pRep->getTimeStamp()!=2) {
        setTestResult(TEST_FAILURE,"getTimeStamp() failed");
		return;
    }

   pRep->previous();
   if ( pRep->isIterationFinished() )
	{	setTestResult(TEST_FAILURE,
             "Error in repository iteration service");
		return;
	}

   if ( pRep->getEventType() != type1 )
	{	setTestResult(TEST_FAILURE,
             "Wrong event type for first event");
		return;
	}

    if (pRep->getTimeStamp()!=1) {
        setTestResult(TEST_FAILURE,"getTimeStamp() failed");
		return;
    }

   pRep->previous();
   if ( !(pRep->isIterationFinished()) )
	{	setTestResult(TEST_FAILURE,
             "Error in repository iteration service");
		return;
	}

   // Add events to the repository until one is overwritten
   unsigned int loopCounter = 0;
   for (unsigned int i=pRep->getCounter(); i<pRep->getRepositorySize()+1; i++)  {
     pRep->create(pRep,(TD_EventType)(type3+loopCounter));
     loopCounter++;
   }

   // Check value of event counter
   if ( ( pRep->getCounter() != pRep->getRepositorySize()+1 ) )
	{	setTestResult(TEST_FAILURE,"Wrong number of events in event repository");
		return;
	}

   // Check correctness of latest event
   pRep->latest();     // position event pointer on latest event
   if ( pRep->getEventType() != (TD_EventType)(type3+loopCounter-1) )
	{	setTestResult(TEST_FAILURE,
             "Wrong event type for latest event");
		return;
	}

   // Iterate through the events in the repository and check that iteration
   // service returns a number of events equal to the repository size
   unsigned int counter = 0;
   for (pRep->latest(); !pRep->isIterationFinished(); pRep->previous())
      counter++;
   if ( counter != pRep->getRepositorySize() )
	{	setTestResult(TEST_FAILURE,
             "Wrong number of events in repository");
		return;
	}

    // Verify that reset doesn't clear the event counter
    counter=pRep->getCounter();
    pRep->reset();
    if (counter!=pRep->getCounter()) {
        setTestResult(TEST_FAILURE,"Reset failed");
		return;
    }

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
