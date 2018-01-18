//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseTelecommandManager_1.cpp
//
// Version	1.1
// Date		11.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Telecommand/DC_DummyTelecommandLoader.h"
#include "../Telecommand/CC_TelecommandManager.h"
#include "../System/DC_DummyObsClock.h"
#include "../Telecommand/TelecommandLoader.h"
#include "TestCaseTelecommandManager_1.h"

TestCaseTelecommandManager_1::TestCaseTelecommandManager_1(void) :
	TestCaseGenericSetUp(ID_TELECOMMANDMANAGER*10+1,"TestCaseTelecommandManager_1") {
		return;
}

void TestCaseTelecommandManager_1::runTestCase(void) {

   // Create the telecommand manager
   CC_TelecommandManager* pTcm = new CC_TelecommandManager();

   // Check the value of the class identifier
   if ( pTcm->getClassId() != ID_TELECOMMANDMANAGER )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Check that the telecommand loader is not configured
   if ( pTcm->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Create and load an OBS clock and verify that it is loaded
   DC_DummyObsClock* pClk = new DC_DummyObsClock();
   pTcm->setObsClock(pClk);
   if ( pTcm->getObsClock() != pClk )
   {    setTestResult(TEST_FAILURE, "Wrong OBS clock");
        return;
   }

   // Create and load a telecommand loader and verify that it is loaded
   DC_DummyTelecommandLoader* pTcl = new DC_DummyTelecommandLoader();
   pTcm->setTelecommandLoader(pTcl);
   if ( pTcm->getTelecommandLoader() != pTcl )
   {    setTestResult(TEST_FAILURE, "Wrong telecommand loader");
        return;
   }

   // Set the pending telecommand list size and verify correctness
   pTcm->setPendingTelecommandListSize(10);
   if ( pTcm->getPendingTelecommandListSize() != 10 )
   {    setTestResult(TEST_FAILURE, "Wrong pending telecommand list size");
        return;
   }

   // Check that the telecommand manager is configured
   if ( !pTcm->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Check the number of pending telecommands
   if ( pTcm->getPendingTelecommands() != 0 )
   {    setTestResult(TEST_FAILURE, "Wrong number of pending telecommands");
        return;
   }

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;

}
