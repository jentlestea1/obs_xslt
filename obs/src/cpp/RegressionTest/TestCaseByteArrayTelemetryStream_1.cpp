//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseByteArrayTelemetryStream_1.cpp
//
// Version	1.1
// Date		18.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestCompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Telemetry/DC_ByteArrayTelemetryStream.h"
#include "../Telemetry/DC_DummyTelemetryPacket.h"
#include "TestCaseByteArrayTelemetryStream_1.h"

TestCaseByteArrayTelemetryStream_1::TestCaseByteArrayTelemetryStream_1(void) :
	TestCaseGenericSetUp(ID_BYTEARRAYTELEMETRYSTREAM*10+1,"TestCaseByteArrayTelemetryStream_1") {
		return;
}

void TestCaseByteArrayTelemetryStream_1::runTestCase(void) {

   // Create the byte array
   unsigned int const size = 5;
   unsigned char ba[size];
   for (int i=0; i<size; i++)
       ba[i]=0;

   // Create the telemetry stream component
   DC_ByteArrayTelemetryStream* pTmStream = new DC_ByteArrayTelemetryStream();

   // Create and configure the telemetry packet to be written to the stream
   DC_DummyTelemetryPacket* pTI = new DC_DummyTelemetryPacket();
   pTI->setNumberOfBytes(2);
   pTI->setValue(0,1);
   pTI->setValue(1,2);

   // Check the value of the class identifier
   if ( pTmStream->getClassId() != ID_BYTEARRAYTELEMETRYSTREAM )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Check that the telemetry stream is not configured
   if ( pTmStream->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong object configuration status");
        return;
   }

   // Set the size of the byte array and verify correctness
   pTmStream->setCapacity(size);
   if ( pTmStream->getCapacity() != size )
   {    setTestResult(TEST_FAILURE, "Wrong telemetry stream size");
        return;
   }

   // Set the starting address of the byte array and verify correctness
   pTmStream->setStartingAddress(ba);
   if ( pTmStream->getStartingAddress() != ba )
   {    setTestResult(TEST_FAILURE, "Wrong byte array starting address");
        return;
   }

   // Check that the telemetry stream is now configured
   if ( !pTmStream->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong object configuration status");
        return;
   }

   // Make write requests and check success
   pTmStream->write(pTI);
   if ( (ba[0] != 1) || (ba[1] != 2) )
   {    setTestResult(TEST_FAILURE, "Write request failed");
        return;
   }

   // Check doesPacketFit method
   if ( !pTmStream->doesPacketFit(pTI) )
   {    setTestResult(TEST_FAILURE, "Failure of method doesPacketFit");
        return;
   }

   // Write a new telemetry packet and check again doesPacketFit method (now it should fail)
   pTmStream->write(pTI);
   if ( pTmStream->doesPacketFit(pTI) )
   {    setTestResult(TEST_FAILURE, "Failure of method doesPacketFit");
        return;
   }

   // Make a write request that should be only partially executed
   pTmStream->write(pTI);
   if ( ba[4] != 1 )
   {    setTestResult(TEST_FAILURE, "Write request failed");
        return;
   }

   // Reset telemetry stream and verify new write request
   pTmStream->reset();
   pTI->setValue(0,3);
   pTI->setValue(1,4);
   pTmStream->write(pTI);
   if ( (ba[0] != 3) || (ba[1] != 4) )
   {    setTestResult(TEST_FAILURE, "Write request failed");
        return;
   }

   // Saturate again the telemetry stream, flush and write again
   pTmStream->write(pTI);
   pTmStream->write(pTI);
   pTmStream->flush();
   pTI->setValue(0,5);
   pTI->setValue(1,6);
   pTmStream->write(pTI);
   if ( (ba[0] != 5) || (ba[1] != 6) )
   {    setTestResult(TEST_FAILURE, "Write request failed");
        return;
   }

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;

}
