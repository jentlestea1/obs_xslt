//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyTelemetryPacket_1.cpp
//
// Version	1.1
// Date		18.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_DummyTelemetryPacket.h"
#include "TestCaseDummyTelemetryPacket_1.h"

TestCaseDummyTelemetryPacket_1::TestCaseDummyTelemetryPacket_1(void) :
	TestCaseGenericSetUp(ID_DUMMYTELEMETRYITEM*10+1,"TestCaseDummyTelemetryPacket_1") {
		return;
}

void TestCaseDummyTelemetryPacket_1::runTestCase(void) {

   DC_DummyTelemetryPacket* pTmWord = new DC_DummyTelemetryPacket();

   // Check the value of the class identifier
   if ( pTmWord->getClassId() != ID_DUMMYTELEMETRYITEM )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Check configuration statur
   if ( pTmWord->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Set number of bytes and check configuration status
   pTmWord->setNumberOfBytes(2);
   if ( !pTmWord->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Check number of bytes
   if ( pTmWord->getNumberOfBytes() != 2 )
   {    setTestResult(TEST_FAILURE, "Wrong number of bytes");
        return;
   }

   // Check default value of the encapsulated telemetry bytes
   if ( pTmWord->getUnsignedByte(0) != 0 )
   {    setTestResult(TEST_FAILURE, "Wrong telemetry byte value");
        return;
   }
   if ( pTmWord->getUnsignedByte(1) != 0 )
   {    setTestResult(TEST_FAILURE, "Wrong telemetry byte value");
        return;
   }

   // Set and read out the encapsulated telemetry byte
   pTmWord->setValue(0,1);
   if ( pTmWord->getUnsignedByte(0) != 1 )
   {    setTestResult(TEST_FAILURE, "Wrong telemetry byte value");
        return;
   }
   pTmWord->setValue(1,2);
   if ( pTmWord->getUnsignedByte(1) != 2 )
   {    setTestResult(TEST_FAILURE, "Wrong telemetry byte value");
        return;
   }

   // Check default value of the validity check service
   if ( !pTmWord->isValid() )
   {    setTestResult(TEST_FAILURE, "Wrong validity check result");
        return;
   }

   // Set and read out the validity status
   pTmWord->setValidStatus(NOT_VALID);
   if ( pTmWord->isValid() )
   {    setTestResult(TEST_FAILURE, "Wrong validity check result");
        return;
   }

   // Check update service (the update service simply increments by one the
   // value of the telemetry bytes)
   pTmWord->update();
   if ( pTmWord->getUnsignedByte(0) != 2 )
   {    setTestResult(TEST_FAILURE, "Wrong telemetry byte value");
        return;
   }
   if ( pTmWord->getUnsignedByte(1) != 3 )
   {    setTestResult(TEST_FAILURE, "Wrong telemetry byte value");
        return;
   }

   // Check update service with wrap around
   pTmWord->setValue(0,255);
   pTmWord->update();
   if ( pTmWord->getUnsignedByte(0) != 0 )
   {    setTestResult(TEST_FAILURE, "Wrong telemetry byte value");
        return;
   }
   if ( pTmWord->getUnsignedByte(1) != 4 )
   {    setTestResult(TEST_FAILURE, "Wrong telemetry byte value");
        return;
   }

   // Check default values of non-implemented attributes
   if (pTmWord->getDestination() != 0)
   {    setTestResult(TEST_FAILURE, "Wrong telemetry destination");
        return;
   }
   if (pTmWord->getType() != pTmWord->getClassId()%256 )
   {    setTestResult(TEST_FAILURE, "Wrong telemetry type");
        return;
   }
   if (pTmWord->getSubType() != 0)
   {    setTestResult(TEST_FAILURE, "Wrong telemetry sub type");
        return;
   }
   if (pTmWord->getTimeTag() != 0)
   {    setTestResult(TEST_FAILURE, "Wrong telemetry time tag");
        return;
   }

   if (pTmWord->isInUse())
   {    setTestResult(TEST_FAILURE, "Wrong inUse status");
        return;
   }

   // Check implementation of "in use" flag
   pTmWord->setInUse(true);
   if (!pTmWord->isInUse())
   {    setTestResult(TEST_FAILURE, "Wrong inUse status");
        return;
   }

   // Check number of bytes
   if ( pTmWord->getNumberOfBytes() != 2 )
   {    setTestResult(TEST_FAILURE, "Wrong number of bytes");
        return;
   }

   // Check default value of fast acquisition service
   if ( pTmWord->getStartAddress() != pNULL )
   {    setTestResult(TEST_FAILURE, "Wrong fast aquisition service");
        return;
   }
   if ( pTmWord->isFastAcquisitionImplemented() )
   {    setTestResult(TEST_FAILURE, "Wrong fast aquisition service availability check");
        return;
   }

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;

}
