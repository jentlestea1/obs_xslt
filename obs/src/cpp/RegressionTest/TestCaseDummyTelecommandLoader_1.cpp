//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyTelecommandLoader_1.cpp
//
// Version	1.1
// Date		18.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Telecommand/DC_DummyTelecommand.h"
#include "../Telecommand/DC_DummyTelecommandLoader.h"
#include "../Telecommand/CC_TelecommandManager.h"
#include "../System/DC_DummyObsClock.h"
#include "../Telecommand/TelecommandLoader.h"
#include "TestCaseDummyTelecommandLoader_1.h"

TestCaseDummyTelecommandLoader_1::TestCaseDummyTelecommandLoader_1(void) :
	TestCaseGenericSetUp(ID_DUMMYTELECOMMANDLOADER*10+1,"TestCaseDummyTelecommandLoader_1") {
		return;
}

void TestCaseDummyTelecommandLoader_1::runTestCase(void) {

   // Create the dummy telecommand loader
   DC_DummyTelecommandLoader* pTcl = new DC_DummyTelecommandLoader();

   // Create and configure a telecommand manager
   CC_TelecommandManager* pTcm = new CC_TelecommandManager();
   DC_DummyObsClock* pClk = new DC_DummyObsClock();
   pTcm->setPendingTelecommandListSize(10);
   pTcm->setObsClock(pClk);
   pTcm->setTelecommandLoader(pTcl);
   pTcl->setTelecommandManager(pTcm);

   // Check the value of the class identifier
   if ( pTcl->getClassId() != ID_DUMMYTELECOMMANDLOADER )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Check that the telecommand loader is not configured
   if ( pTcl->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Create, configure and load three sample telecommands
   // and verify that the telecommand loader becomes configured
   DC_DummyTelecommand* pSampleTc1 = new DC_DummyTelecommand();
   DC_DummyTelecommand* pSampleTc2 = new DC_DummyTelecommand();
   DC_DummyTelecommand* pSampleTc3 = new DC_DummyTelecommand();
   pSampleTc1->setTimeTag(0);
   pSampleTc2->setTimeTag(0);
   pSampleTc3->setTimeTag(0);
   pTcl->setSampleTelecommand(0,pSampleTc1);
   pTcl->setSampleTelecommand(1,pSampleTc2);
   pTcl->setSampleTelecommand(2,pSampleTc3);
   if ( !pTcl->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Send two activation requests to the telecommand loader and verify
   // increment of allocation counter
   pTcl->activate();
   pTcl->activate();
   if ( pTcl->getAllocationCounter() != 2 )
   {    setTestResult(TEST_FAILURE, "Wrong value of allocation counter");
        return;
   }

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;

}
