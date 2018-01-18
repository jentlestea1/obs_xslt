//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseTelecommandManager_2.cpp
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
#include "TestCaseTelecommandManager_2.h"

TestCaseTelecommandManager_2::TestCaseTelecommandManager_2(void) :
	TestCaseGenericSetUp(ID_TELECOMMANDMANAGER*10+2,"TestCaseTelecommandManager_2") {
		return;
}

void TestCaseTelecommandManager_2::runTestCase(void) {

   // Create the telecommand manager
   CC_TelecommandManager* pTcm = new CC_TelecommandManager();

   // Define the identifiers and time tags for the dummy telecommands
   TD_ObsTime tcTt1 = 3;
   TD_ObsTime tcTt2 = 5;
   TD_ObsTime tcTt3 = 0;
   TD_TelecommandId tcId1 = 1;
   TD_TelecommandId tcId2 = 2;
   TD_TelecommandId tcId3 = 3;

   // Create and load an OBS clock
   DC_DummyObsClock* pClk = new DC_DummyObsClock();
   pClk->setTime(tcTt1-1);
   pClk->setCycle(0);
   pTcm->setObsClock(pClk);

   // Create and configure the three dummy telecommands
   DC_DummyTelecommand* pTc1 = new DC_DummyTelecommand();
   DC_DummyTelecommand* pTc2 = new DC_DummyTelecommand();
   DC_DummyTelecommand* pTc3 = new DC_DummyTelecommand();
   pTc1->setTelecommandId(tcId1);
   pTc2->setTelecommandId(tcId2);
   pTc3->setTelecommandId(tcId3);
   pTc1->setTimeTag(tcTt1);
   pTc2->setTimeTag(tcTt2);
   pTc3->setTimeTag(tcTt3);

   // Create, configure and load a dummy telecommand loader
   DC_DummyTelecommandLoader* pTcl = new DC_DummyTelecommandLoader();
   pTcl->setSampleTelecommand(0,pTc1);
   pTcl->setSampleTelecommand(1,pTc2);
   pTcl->setSampleTelecommand(2,pTc3);
   pTcm->setTelecommandLoader(pTcl);
   pTcl->setTelecommandManager(pTcm);

   // Set the pending telecommand list size
   pTcm->setPendingTelecommandListSize(10);

   // Check that the telecommand manager is configured
   if ( !pTcm->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Activate the telecommand loader three times and check that dummy
   // telecommands were loaded in telecommand manager
   pTcl->activate();
   pTcl->activate();
   pTcl->activate();
   if ( pTcm->getPendingTelecommands() != 3 )
   {    setTestResult(TEST_FAILURE, "Wrong number of pending telecommands");
        return;
   }

   // Check allocation counter value
   if ( pTcl->getAllocationCounter() != 3 )
   {    setTestResult(TEST_FAILURE, "Wrong allocation counter value");
        return;
   }

   // Activate the telecommand manager and check that the third
   // telecommand is executed
   pTcm->activate();
   if (pTc3->getExecutionCounter() != 1)
   {    setTestResult(TEST_FAILURE, "Third telecommand was not executed");
        return;
   }

   // Check number of pending telecommands
   if ( pTcm->getPendingTelecommands() != 2 )
   {    setTestResult(TEST_FAILURE, "Wrong number of pending telecommands");
        return;
   }

   // Check generation of event to record telecommand successful execution and unloading
   DC_EventRepository* pRep = CC_RootObject::getEventRepository();
   pRep->latest();
   if ( (pRep->getEventType() != EVT_TC_EXEC_SUCC) )
   {    setTestResult(TEST_FAILURE, "Wrong unload event");
        return;
   }

   // Activate telecommand manager and advance dummy time to the point
   // where the first telecommand should be executed and check execution
   pTcm->activate();
   pTcm->activate();
   pClk->setTime(tcTt1+1);
   pClk->setCycle(0);
   pTcm->activate();
   if (pTc1->getExecutionCounter() != 1)
   {    setTestResult(TEST_FAILURE, "First telecommand was not executed");
        return;
   }

   // Check number of pending telecommands
   if ( pTcm->getPendingTelecommands() != 1 )
   {    setTestResult(TEST_FAILURE, "Wrong number of pending telecommands");
        return;
   }

   // Activate telecommand manager and advance dummy time to the point
   // where the second telecommand should be executed and check execution
   pTcm->activate();
   pTcm->activate();
   pClk->setTime(tcTt2+1);
   pClk->setCycle(0);
   pTcm->activate();
   if (pTc2->getExecutionCounter() != 1)
   {    setTestResult(TEST_FAILURE, "Second telecommand was not executed");
        return;
   }

   // Check number of pending telecommands
   if ( pTcm->getPendingTelecommands() != 0 )
   {    setTestResult(TEST_FAILURE, "Wrong number of pending telecommands");
        return;
   }

   // Check allocation counter value
   if ( pTcl->getAllocationCounter() != 0 )
   {    setTestResult(TEST_FAILURE, "Wrong allocation counter value");
        return;
   }

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;

}
