//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyPUSTelemetryPacket_1.cpp
//
// Version	1.1
// Date		18.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_DummyPUSTelemetryPacket.h"
#include "../System/DC_DummyObsClock.h"
#include "TestCaseDummyPUSTelemetryPacket_1.h"

TestCaseDummyPUSTelemetryPacket_1::TestCaseDummyPUSTelemetryPacket_1(void) :
	TestCaseGenericSetUp(ID_DUMMYPUSTELEMETRYPACKET*10+1,"TestCaseDummyPUSTelemetryPacket_1") {
    return;
}

void TestCaseDummyPUSTelemetryPacket_1::runTestCase(void) {

   DC_DummyPUSTelemetryPacket* pTmWord = new DC_DummyPUSTelemetryPacket;

   // Check the value of the class identifier
   if ( pTmWord->getClassId() != ID_DUMMYPUSTELEMETRYPACKET )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Verify that the object is configured
   if (!pTmWord->isObjectConfigured()) {
       setTestResult(TEST_FAILURE,"Wrong configuration status");
       return;
   }

   // Check default value of the encapsulated telemetry byte
   if ( pTmWord->getUnsignedByte(0) != 0 )
   {    setTestResult(TEST_FAILURE, "Wrong telemetry byte value");
        return;
   }

   // Set and read out the encapsulated telemetry byte
   pTmWord->setValue(2);
   if ( pTmWord->getUnsignedByte(0) != 2 )
   {    setTestResult(TEST_FAILURE, "Wrong telemetry byte value");
        return;
   }

   // Check update service
   pTmWord->update();
   if ( pTmWord->getUnsignedByte(0) != 3 )
   {    setTestResult(TEST_FAILURE, "Wrong telemetry byte value");
        return;
   }

   // Check update service with wrap around
   pTmWord->setValue(255);
   pTmWord->update();
   if ( pTmWord->getUnsignedByte(0) != 0 )
   {    setTestResult(TEST_FAILURE, "Wrong telemetry byte value");
        return;
   }

   // Check the attribute values
   if (pTmWord->getDefaultDestination()!=TEST_TM_DEF_DEST) {
       setTestResult(TEST_FAILURE,"Wrong default telemetry destination");
       return;
   }

   if (pTmWord->getDestination() != TEST_TM_DEF_DEST)
   {    setTestResult(TEST_FAILURE, "Wrong telemetry destination");
        return;
   }
   if (pTmWord->getType() != TEST_TM_TYPE)
   {    setTestResult(TEST_FAILURE, "Wrong telemetry type");
        return;
   }
   if (pTmWord->getSubType() != TEST_TM_SUBTYPE)
   {    setTestResult(TEST_FAILURE, "Wrong telemetry sub type");
        return;
   }
   if (pTmWord->getTimeTag() != TEST_TM_TIMETAG)
   {    setTestResult(TEST_FAILURE, "Wrong telemetry time tag");
        return;
   }
   if ( pTmWord->getPacketId() != (2048+TEST_TM_APID) )
   {    setTestResult(TEST_FAILURE, "Wrong packet ID");
        return;
   }

   // Update TM destination and check success
   pTmWord->setDestination(TEST_TM_DEST);
   if (pTmWord->getDestination() != TEST_TM_DEST)
   {    setTestResult(TEST_FAILURE, "Wrong telemetry destination");
        return;
   }

   // Check OBS clock
   if (pTmWord->getObsClock() == pNULL)
   {    setTestResult(TEST_FAILURE, "Wrong clock plug-in");
        return;
   }

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;

}
