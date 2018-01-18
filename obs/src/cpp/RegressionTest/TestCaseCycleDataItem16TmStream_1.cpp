//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseCycleDataItem16TmStream_1.cpp
//
// Version	1.1
// Date		18.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Telemetry/DC_CycleDataItem16TmStream.h"
#include "../Telemetry/DC_DummyTelemetryPacket.h"
#include "../Data/DC_DataItem.h"
#include "../Data/DC_RawDataItem.h"
#include "TestCaseCycleDataItem16TmStream_1.h"

TestCaseCycleDataItem16TmStream_1::TestCaseCycleDataItem16TmStream_1(void) :
	TestCaseGenericSetUp(ID_CYCLEDATAITEM16TMSTREAM*10+1,"TestCaseCycleDataItem16TmStream_1") {
		return;
}

void TestCaseCycleDataItem16TmStream_1::runTestCase(void) {

   // Create three data item components
   unsigned short var1, var2, var3;
   DC_RawDataItem* pd1 = new DC_RawDataItem( &var1 );
   DC_RawDataItem* pd2 = new DC_RawDataItem( &var2 );
   DC_RawDataItem* pd3 = new DC_RawDataItem( &var3 );

   // Create and configure the dummy telemetry data item
   unsigned char d1 = 1;
   unsigned char d2 = 2;
   unsigned char d3 = 3;
   unsigned char d4 = 4;
   DC_DummyTelemetryPacket* pTW1 = new DC_DummyTelemetryPacket();
   pTW1->setNumberOfBytes(4);
   pTW1->setValue(0,d1);
   pTW1->setValue(1,d2);
   pTW1->setValue(2,d3);
   pTW1->setValue(3,d4);

   // Create the CycleDataItem16TmStream_1 component
   DC_CycleDataItem16TmStream* pTmStream = new DC_CycleDataItem16TmStream();

   // Check the value of the class identifier
   if ( pTmStream->getClassId() != ID_CYCLEDATAITEM16TMSTREAM )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Check that the telemetry stream is not configured
   if ( pTmStream->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong object configuration status");
        return;
   }

   // Set the size of the telemetry stream and verify correctness
   pTmStream->setNumberOfDataItems(3);
   if ( pTmStream->getCapacity() != 3 )
   {    setTestResult(TEST_FAILURE, "Wrong telemetry stream size");
        return;
   }

   // Load the data item into the telemetry stream and check that the
   // telemetry stream object becomes configured
   pTmStream->setDataItem(0,pd1);
   pTmStream->setDataItem(1,pd2);
   pTmStream->setDataItem(2,pd3);
   if ( !pTmStream->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong object configuration status");
        return;
   }

   // Check that the telemetry packet can be written to the telemetry stream
   if ( !pTmStream->doesPacketFit(pTW1) )
   {    setTestResult(TEST_FAILURE, "Check on telemetry stream capacity failed");
        return;
   }

   // Make a write request to the telemetry stream and check correctness
   // (Recall that when a pair of bytes read from the telemetry packet are
   // written to a data item, the first byte is overlaid upon the least
   // significant byte of the data item and the second byte is overlaid upon
   // the most significant byte)
   pTmStream->write(pTW1);
   if ( (pd1->getUnsignedShort() != d1+256*d2) ||
        (pd2->getUnsignedShort() != d3+256*d4) )
   {    setTestResult(TEST_FAILURE, "Write operations failed");
        return;
   }

   // Check whether the telemetry packet can be written again to the telemetry stream
   if ( pTmStream->doesPacketFit(pTW1) )
   {    setTestResult(TEST_FAILURE, "Check on telemetry stream capacity failed");
        return;
   }

   // Rewrite the telemetry packet and check that the first two bytes were correctly written
   pTmStream->write(pTW1);
   if ( (pd3->getUnsignedShort() != d1+256*d2) )
   {    setTestResult(TEST_FAILURE, "Write operations failed");
        return;
   }

   // Reset the telemetry stream and clear all data items
   pTmStream->reset();
   pd1->setUnsignedShort(0);
   pd2->setUnsignedShort(0);
   pd3->setUnsignedShort(0);

   // Check that the telemetry packet can be written to the telemetry stream
   if ( !pTmStream->doesPacketFit(pTW1) )
   {    setTestResult(TEST_FAILURE, "Check on telemetry stream capacity failed");
        return;
   }

   // Make a write request to the telemetry stream and check correctness
   pTmStream->write(pTW1);
   if ( (pd1->getUnsignedShort() != d1+256*d2) ||
        (pd2->getUnsignedShort() != d3+256*d4) )
   {    setTestResult(TEST_FAILURE, "Write operations failed");
        return;
   }

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;

}
