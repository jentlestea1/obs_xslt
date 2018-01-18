//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyPUSTelecommand_1.cpp
//
// Version	1.1
// Date		18.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Telecommand/DC_DummyPUSTelecommand.h"
#include "TestCaseDummyPUSTelecommand_1.h"

TestCaseDummyPUSTelecommand_1::TestCaseDummyPUSTelecommand_1(void) :
	TestCaseGenericSetUp(ID_DUMMYPUSTELECOMMAND*10+1,"TestCaseDummyPUSTelecommand_1") {
		return;
}

void TestCaseDummyPUSTelecommand_1::runTestCase(void) {

   // Create the dummy telecommand components
   DC_DummyPUSTelecommand* pTc = new DC_DummyPUSTelecommand();

   // Check the value of the class identifier
   if ( pTc->getClassId() != ID_DUMMYPUSTELECOMMAND )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Check configuration status
   if ( pTc->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Set and read back the TC attributes
   if ( pTc->getTelecommandId() != TEST_TC_ID )
   {    setTestResult(TEST_FAILURE, "Wrong TC ID value");
        return;
   }
   if ( pTc->getType() != TEST_TC_TYPE )
   {    setTestResult(TEST_FAILURE, "Wrong TC type value");
        return;
   }
   if ( pTc->getSubType() != TEST_TC_SUBTYPE )
   {    setTestResult(TEST_FAILURE, "Wrong TC subtype value");
        return;
   }
   if ( pTc->getSource() != TEST_TC_SOURCE )
   {    setTestResult(TEST_FAILURE, "Wrong TC source value");
        return;
   }
   pTc->setTimeTag(5);
   if ( pTc->getTimeTag() != 5 )
   {    setTestResult(TEST_FAILURE, "Wrong time tag value");
        return;
   }
   if ( pTc->getAcknowledgeLevel() != 0 )
   {    setTestResult(TEST_FAILURE, "Wrong TC acknowledge level");
        return;
   }
   if ( pTc->getPacketId() != (2048+4096+TEST_TC_APID) )
   {    setTestResult(TEST_FAILURE, "Wrong packet ID");
        return;
   }

   // Check that the telecommand becomes configured
   if ( !pTc->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Update acknowledge level and check success
   pTc->setAcknowledgeLevel(10);
   if ( pTc->isAcceptanceAckRequired() )
   {    setTestResult(TEST_FAILURE, "Wrong acceptance acknowledge value");
        return;
   }
   if ( !pTc->isStartAckRequired() )
   {    setTestResult(TEST_FAILURE, "Wrong start acknowledge value");
        return;
   }
   if ( pTc->isProgressAckRequired() )
   {    setTestResult(TEST_FAILURE, "Wrong progress acknowledge value");
        return;
   }
   if ( !pTc->isCompletionAckRequired() )
   {    setTestResult(TEST_FAILURE, "Wrong completion acknowledge value");
        return;
   }

   // Make two execute requests and check increment of execution counter
   pTc->execute();
   pTc->execute();
   if ( pTc->getExecutionCounter() != 2 )
   {    setTestResult(TEST_FAILURE, "Wrong execution check counter value");
        return;
   }

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;

}
