//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyTelecommand_1.cpp
//
// Version	1.1
// Date		18.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Telecommand/DC_DummyTelecommand.h"
#include "TestCaseDummyTelecommand_1.h"

TestCaseDummyTelecommand_1::TestCaseDummyTelecommand_1(void) :
	TestCaseGenericSetUp(ID_DUMMYTELECOMMAND*10+1,"TestCaseDummyTelecommand_1") {
		return;
}

void TestCaseDummyTelecommand_1::runTestCase(void) {

   // Create the dummy telecommand components
   DC_DummyTelecommand* pTc = new DC_DummyTelecommand();

   // Check the value of the class identifier
   if ( pTc->getClassId() != ID_DUMMYTELECOMMAND )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Check configuration status
   if ( pTc->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Check default values of TC attributes
   if ( pTc->getTelecommandId() != pTc->getInstanceId() )
   {    setTestResult(TEST_FAILURE, "Wrong TC ID value");
        return;
   }
   if ( pTc->getType() != (pTc->getClassId()%256) )
   {    setTestResult(TEST_FAILURE, "Wrong TC type value");
        return;
   }
   if ( pTc->getSubType() != 0 )
   {    setTestResult(TEST_FAILURE, "Wrong TC subtype value");
        return;
   }
   if ( pTc->getSource() != 0 )
   {    setTestResult(TEST_FAILURE, "Wrong telecommand source attribute");
        return;
   }
   if ( pTc->getAcknowledgeLevel() != 0 )
   {    setTestResult(TEST_FAILURE, "Wrong TC acknowledge value");
        return;
   }
   if ( pTc->isInUse() != false )
   {    setTestResult(TEST_FAILURE, "Wrong initial value of InUse attribute");
        return;
   }

   // Set the telecommand time tag and verify that
   // the telecommand becomes configured
   TD_ObsTime tt = 20;
   pTc->setTimeTag(tt);
   if ( pTc->getTimeTag() != (TD_ObsTime)tt )
   {    setTestResult(TEST_FAILURE, "Wrong time tag value");
        return;
   }
   if ( !pTc->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Change the value of the "in use" attribute and check success
   pTc->setInUse(true);
   if ( pTc->isInUse() != true)
   {    setTestResult(TEST_FAILURE, "Wrong value of InUse attribute");
        return;
   }

   // Check the initial value of the execution counter
   if ( pTc->getExecutionCounter() != 0 )
   {    setTestResult(TEST_FAILURE, "Wrong initial value of execution counter");
        return;
   }

   // Check the number of raw data
   if ( pTc->getNumberOfRawData() != 0 )
   {    setTestResult(TEST_FAILURE, "Wrong number of raw data");
        return;
   }

   // Check the execution check return value
   if ( !pTc->canExecute() )
   {    setTestResult(TEST_FAILURE, "Wrong execution check return value");
        return;
   }

   // Check the validity check return value
   if ( !pTc->isValid() )
   {    setTestResult(TEST_FAILURE, "Wrong validity check return value");
        return;
   }

   // Make two execute requests and check increment of execution counter
   pTc->execute();
   pTc->execute();
   if ( pTc->getExecutionCounter() != 2 )
   {    setTestResult(TEST_FAILURE, "Wrong execution check counter value");
        return;
   }

   // Change the execution check return value and check that the change is
   // implemented
   pTc->setExecutionCheckValue(TC_CANNOT_EXECUTE);
   if ( pTc->canExecute() )
   {    setTestResult(TEST_FAILURE, "Wrong execution check return value");
        return;
   }

   // Change the validity check return value and check that the change is
   // implemented
   pTc->setValidityCheckValue(NOT_VALID);
   if ( pTc->isValid() )
   {    setTestResult(TEST_FAILURE, "Wrong validity check return value");
        return;
   }

   // Change the execution check code and check that the change is
   // implemented
   pTc->setExecutionCheckCode(1);
   if ( pTc->getExecutionCheckCode()!=1 )
   {    setTestResult(TEST_FAILURE, "Wrong execution check code");
        return;
   }

   // Change the validity check code and check that the change is
   // implemented
   pTc->setValidityCheckCode(1);
   if ( pTc->getValidityCheckCode()!=1 )
   {    setTestResult(TEST_FAILURE, "Wrong validity check code");
        return;
   }

   // Dummy method calls
   pTc->setAcknowledgeLevel(0);
   pTc->setTelecommandId(0);
   pTc->setSource(0);
   pTc->setType(0);
   pTc->setSubType(0);

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;

}
