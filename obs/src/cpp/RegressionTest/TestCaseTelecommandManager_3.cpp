//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseTelecommandManager_3.cpp
//
// Version	1.1
// Date		11.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"
#include "../Telecommand/DC_DummyTelecommandLoader.h"
#include "../Telecommand/CC_TelecommandManager.h"
#include "../System/DC_DummyObsClock.h"
#include "../Telecommand/TelecommandLoader.h"
#include "../Telecommand/DC_DummyTelecommand.h"
#include "TestCaseTelecommandManager_3.h"

TestCaseTelecommandManager_3::TestCaseTelecommandManager_3(void) :
	TestCaseGenericSetUp(ID_TELECOMMANDMANAGER*10+3,"TestCaseTelecommandManager_3") {
		return;
}

void TestCaseTelecommandManager_3::runTestCase(void) {

   // Retrieve the event repository
   DC_EventRepository* pRep = CC_RootObject::getEventRepository();

   // Create the telecommand manager
   CC_TelecommandManager* pTcm = new CC_TelecommandManager();

   // Define the identifiers and time tags for the dummy telecommands
   TD_ObsTime tcTt1 = 0;
   TD_ObsTime tcTt2 = 0;
   TD_ObsTime tcTt3 = 0;
   TD_TelecommandId tcId1 = 1;
   TD_TelecommandId tcId2 = 2;
   TD_TelecommandId tcId3 = 3;

   // Create and load an OBS clock
   DC_DummyObsClock* pClk = new DC_DummyObsClock();
   pClk->setTime(tcTt1+1);
   pClk->setCycle(0);
   pTcm->setObsClock(pClk);

   // Create and configure the dummy telecommands
   DC_DummyTelecommand* pTc1 = new DC_DummyTelecommand();
   DC_DummyTelecommand* pTc2 = new DC_DummyTelecommand();
   DC_DummyTelecommand* pTc3 = new DC_DummyTelecommand();
   pTc1->setTelecommandId(tcId1);
   pTc2->setTelecommandId(tcId2);
   pTc3->setTelecommandId(tcId3);
   pTc1->setTimeTag(tcTt1);
   pTc2->setTimeTag(tcTt2);
   pTc3->setTimeTag(tcTt3);
   pTc1->setExecutionCheckValue(TC_CANNOT_EXECUTE);
   pTc2->setValidityCheckValue(NOT_VALID);

   // Create, configure and load a dummy telecommand loader
   DC_DummyTelecommandLoader* pTcl = new DC_DummyTelecommandLoader();
   pTcl->setSampleTelecommand(0,pTc1);
   pTcl->setSampleTelecommand(1,pTc2);
   pTcl->setSampleTelecommand(2,pTc3);
   pTcm->setTelecommandLoader(pTcl);
   pTcl->setTelecommandManager(pTcm);

   // Set the pending telecommand list size
   pTcm->setPendingTelecommandListSize(2);

   // Check that the telecommand manager is configured
   if ( !pTcm->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Activate the telecommand loader twice and check that the
   // second telecommand is rejected because its validity check fails
   pTcl->activate();
   pTcl->activate();
   pRep->latest();
   if ( (pRep->getEventType() != EVT_TC_NOT_VALID) )
   {    setTestResult(TEST_FAILURE, "Wrong event type");
        return;
   }

   // Replace the second telecommand in the telecommand loader,
   // activate the telecommand loader twice and check that the
   // last load attempt is rejected because the pending telecommand
   // list is full
   pTcl->setSampleTelecommand(1,pTc3);
   pTcl->activate();        // load TC3 (second entry in dummy TC Loader
   pTcl->activate();        // load TC3 (third entry in dummy TC Loader
   pRep->latest();
   if ( (pRep->getEventType() != EVT_TC_LIST_FULL) )
   {    setTestResult(TEST_FAILURE, "Wrong event type");
        return;
   }

   // Activate the telecommand manager and check that the second
   // telecommand is executed but the first
   // is not executed because its execution check fails
   pTcm->activate();
   if (pTc3->getExecutionCounter() != 1)
   {    setTestResult(TEST_FAILURE, "Third telecommand was not executed");
        return;
   }
   if (pTc1->getExecutionCounter() != 0)
   {    setTestResult(TEST_FAILURE, "First telecommand was executed");
        return;
   }

   // Check generation of event to record telecommand unloading
   pRep->latest();      // TC 3 punctual action was executed
   pRep->previous();    // TC 3 was successfully executed
   pRep->previous();    // TC 1 execution check failed
   if ( (pRep->getEventType() != EVT_TC_EXEC_CHECK_FAIL) )
   {    setTestResult(TEST_FAILURE, "Wrong event type");
        return;
   }

   // Check allocation counter value
   if ( pTcl->getAllocationCounter() != 0 )
   {    setTestResult(TEST_FAILURE, "Wrong allocation counter value");
        return;
   }

   // Activate the telecommand loader three times and verify that two
   // telecommands are loaded
   pTcl->activate();
   pTcl->activate();
   pTcl->activate();
   if ( pTcm->getPendingTelecommands()!=2 )
   {    setTestResult(TEST_FAILURE, "Wrong number of pending telecommands");
        return;
   }
   if ( pTcl->getAllocationCounter() != 2 )
   {    setTestResult(TEST_FAILURE, "Wrong allocation counter value");
        return;
   }

   // Reset telecommand manager and verify number of pending telecommands
   unsigned int nEvt = pRep->getCounter();
   pTcm->reset();
   if ( pTcm->getPendingTelecommands()!=0 )
   {    setTestResult(TEST_FAILURE, "Wrong number of pending telecommands");
        return;
   }

   // Verify events generated as a result of the reset
   if ( (pRep->getCounter() != nEvt+2)  )
   {    setTestResult(TEST_FAILURE, "Wrong number of events");
        return;
   }
   pRep->latest();
   if ( (pRep->getEventType() != EVT_TC_ABORTED)  )
   {    setTestResult(TEST_FAILURE, "Wrong event type");
        return;
   }
   pRep->previous();
   if ( (pRep->getEventType() != EVT_TC_ABORTED)  )
   {    setTestResult(TEST_FAILURE, "Wrong event type");
        return;
   }

   // Check allocation counter value
   if ( pTcl->getAllocationCounter() != 0 )
   {    setTestResult(TEST_FAILURE, "Wrong allocation counter value");
        return;
   }

   // Activate the telecommand loader three times and verify that two
   // telecommands are loaded
   pTcl->activate();
   pTcl->activate();
   pTcl->activate();
   if ( pTcm->getPendingTelecommands()!=2 )
   {    setTestResult(TEST_FAILURE, "Wrong number of pending telecommands");
        return;
   }
   if ( pTcl->getAllocationCounter() != 2 )
   {    setTestResult(TEST_FAILURE, "Wrong allocation counter value");
        return;
   }

   // Abort the first telecommand
   nEvt = pRep->getCounter();
   pTcm->abort(pTc1->getTelecommandId());
   if ( pTcm->getPendingTelecommands()!=1 )
   {    setTestResult(TEST_FAILURE, "Wrong number of pending telecommands");
        return;
   }
   if ( pTcl->getAllocationCounter() != 1 )
   {    setTestResult(TEST_FAILURE, "Wrong allocation counter value");
        return;
   }

   // Check abort event
   if ( (pRep->getCounter() != nEvt+1)  )
   {    setTestResult(TEST_FAILURE, "Wrong number of events");
        return;
   }
   pRep->latest();
   if ( (pRep->getEventType() != EVT_TC_ABORTED)  )
   {    setTestResult(TEST_FAILURE, "Wrong event type");
        return;
   }

   // Abort the last telecommand
   pTcm->abort(pTc3);
   if ( pTcm->getPendingTelecommands()!=0 )
   {    setTestResult(TEST_FAILURE, "Wrong number of pending telecommands");
        return;
   }
   if ( pTcl->getAllocationCounter() != 0 )
   {    setTestResult(TEST_FAILURE, "Wrong allocation counter value");
        return;
   }

   // Check abort event
   if ( (pRep->getCounter() != nEvt+2)  )
   {    setTestResult(TEST_FAILURE, "Wrong number of events");
        return;
   }
   pRep->latest();
   if ( (pRep->getEventType() != EVT_TC_ABORTED)  )
   {    setTestResult(TEST_FAILURE, "Wrong event type");
        return;
   }

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;

}
