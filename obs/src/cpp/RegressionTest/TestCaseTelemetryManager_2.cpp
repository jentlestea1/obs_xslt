//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseTelemetryManager_2.cpp
//
// Version	1.1
// Date		04.03.04
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"
#include "../Telemetry/DC_SimpleTelemetryModeManager.h"
#include "../Telemetry/DC_ByteArrayTelemetryStream.h"
#include "../Telemetry/DC_DummyTelemetryPacket.h"
#include "../Telemetry/CC_TelemetryManager.h"
#include "../Telemetry/TelemetryModeManager.h"
#include "TestCaseTelemetryManager_2.h"


TestCaseTelemetryManager_2::TestCaseTelemetryManager_2(void) :
	TestCaseWithEvtCheck(ID_TELEMETRYMANAGER*10+2,"TestCaseTelemetryManager_2") {
		return;
}

void TestCaseTelemetryManager_2::runTestCase(void) {

   // Retrieve the event repository and the event counter
   unsigned int nEvt = getNumberOfEvents();

   // Create the telemetry manager
   CC_TelemetryManager* pTm = new CC_TelemetryManager();

   // Create and configure the dummy telemetry packets
   unsigned char d11 = 11;
   unsigned char d12 = 12;
   unsigned char d21 = 21;
   unsigned char d22 = 22;
   DC_DummyTelemetryPacket* pTW1 = new DC_DummyTelemetryPacket();
   DC_DummyTelemetryPacket* pTW2 = new DC_DummyTelemetryPacket();
   pTW1->setNumberOfBytes(2);
   pTW1->setValue(0,d11);
   pTW1->setValue(1,d12);
   pTW2->setNumberOfBytes(2);
   pTW2->setValue(0,d21);
   pTW2->setValue(1,d22);

   // Create, configure and load the telemetry mode manager
   DC_SimpleTelemetryModeManager* pTmMm = new DC_SimpleTelemetryModeManager();
   pTmMm->setListLength(0,2);
   pTmMm->setListItem(0,0,pTW1);
   pTmMm->setListItem(0,1,pTW2);
   pTmMm->reset();
   pTm->setTelemetryModeManager(pTmMm);

   // Create, configure and load the telemetry stream
   unsigned int const size = 8;
   unsigned char tmData[size];      // TM data are written here
   for (unsigned int i=0; i<size; i++)
       tmData[i] = 0;
   DC_ByteArrayTelemetryStream* pTmSt = new DC_ByteArrayTelemetryStream();
   pTmSt->setCapacity(size);
   pTmSt->setStartingAddress(tmData);
   pTm->setTelemetryStream(pTmSt);
   pTm->setImmediateQueueSize(2);

   // Check that the components are configured
   if ( ( !pTm->isObjectConfigured() ) ||
        ( !pTmMm->isObjectConfigured() ) ||
        ( !pTmSt->isObjectConfigured() ) ||
        ( !pTW1->isObjectConfigured() ) ||
        ( !pTW2->isObjectConfigured() ) )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Reset "in use" status
   pTW1->setInUse(true);
   pTW2->setInUse(true);

   // Load the TM packets, unload them and check success (try to unload pTW2 twice)
   if (pTm->isImmediateQueueFull())
   {    setTestResult(TEST_FAILURE, "Wrong status of immediate dispatch queue");
        return;
   }
   if (pTm->getImmediateQueueLoaded()!=0)
   {    setTestResult(TEST_FAILURE, "Wrong number of entries in immediate dispatch queue");
        return;
   }
   pTm->sendTelemetryPacket(pTW1);
   pTm->sendTelemetryPacket(pTW2);
   if (pTm->getImmediateQueueLoaded()!=2)
   {    setTestResult(TEST_FAILURE, "Wrong number of entries in immediate dispatch queue");
        return;
   }
   if (!pTm->isImmediateQueueFull())
   {    setTestResult(TEST_FAILURE, "Wrong status of immediate dispatch queue");
        return;
   }
   pTm->unloadTelemetryPacket(pTW2);
   if (pTm->getImmediateQueueLoaded()!=1)
   {    setTestResult(TEST_FAILURE, "Wrong number of entries in immediate dispatch queue");
        return;
   }
   if (pTm->isImmediateQueueFull())
   {    setTestResult(TEST_FAILURE, "Wrong status of immediate dispatch queue");
        return;
   }
   pTm->unloadTelemetryPacket(pTW2);
   if (pTm->getImmediateQueueLoaded()!=1)
   {    setTestResult(TEST_FAILURE, "Wrong number of entries in immediate dispatch queue");
        return;
   }
   pTm->unloadTelemetryPacket(pTW1);
   if (pTm->getImmediateQueueLoaded()!=0)
   {    setTestResult(TEST_FAILURE, "Wrong number of entries in immediate dispatch queue");
        return;
   }

   // Activate telemetry manager and check correctness of values sent to TM stream
   // (Recall that the values encapsulated in the DC_DummyTelemetryPacket component
   // are incremented by 1 every time the component receives an update request)
   pTm->activate();
   if ( ( tmData[0] != d11+1 ) || ( tmData[1] != d12+1 ) )
   {    setTestResult(TEST_FAILURE, "Wrong data written to telemetry stream");
        return;
   }
   if ( ( tmData[2] != d21+1 ) || ( tmData[3] != d22+1 ) )
   {    setTestResult(TEST_FAILURE, "Wrong data written to telemetry stream");
        return;
   }

   // Check that "in use" status has not been changed
   if ( !pTW1->isInUse() )
   {    setTestResult(TEST_FAILURE, "Wrong inUse status");
        return;
   }
   if ( !pTW2->isInUse() )
   {    setTestResult(TEST_FAILURE, "Wrong inUse status");
        return;
   }

   // Submit telemetry packets for immediate dispatch, activate telemetry manager
   // and check that telemetry data are correctly written to telemetry stream
   pTm->sendTelemetryPacket(pTW1);
   pTm->sendTelemetryPacket(pTW2);
   pTm->activate();
   if ( ( tmData[0] != d11+2 ) || ( tmData[1] != d12+2 ) )
   {    setTestResult(TEST_FAILURE, "Wrong data written to telemetry stream");
        return;
   }
   if ( ( tmData[2] != d21+2 ) || ( tmData[3] != d22+2 ) )
   {    setTestResult(TEST_FAILURE, "Wrong data written to telemetry stream");
        return;
   }
   if ( ( tmData[4] != d11+3 ) || ( tmData[5] != d12+3 ) )
   {    setTestResult(TEST_FAILURE, "Wrong data written to telemetry stream");
        return;
   }
   if ( ( tmData[6] != d21+3 ) || ( tmData[7] != d22+3 ) )
   {    setTestResult(TEST_FAILURE, "Wrong data written to telemetry stream");
        return;
   }

   // Check that "in use" status has been set to "not in use"
   if ( pTW1->isInUse() )
   {    setTestResult(TEST_FAILURE, "Wrong inUse status");
        return;
   }
   if ( pTW2->isInUse() )
   {    setTestResult(TEST_FAILURE, "Wrong inUse status");
        return;
   }

   // Reset "in use" status
   pTW1->setInUse(true);
   pTW2->setInUse(true);

   // Reset the array where telemetry data are written
   for (unsigned int i=0; i<size; i++)
       tmData[i] = 0;

   // Force the first telemetry packet to be "not valid"
   pTW1->setValidStatus(NOT_VALID);

   // Activate telemetry manager and check that only the second telemetry packet
   // is sent to TM stream
   pTm->activate();
   if ( ( tmData[0] != d21+4 ) || ( tmData[1] != d22+4 ) )
   {    setTestResult(TEST_FAILURE, "Wrong data written to telemetry stream");
        return;
   }
   if ( ( tmData[2] != 0 ) || ( tmData[3] != 0 ) )
   {    setTestResult(TEST_FAILURE, "Wrong data written to telemetry stream");
        return;
   }

   // Check that the correct event was generated
   if ( !verifyLatestEvent(nEvt+1,EVT_TM_ITEM_NOT_VALID) )
        return;
   nEvt++;

   // Decrease the size of the telemetry stream and make the telemetry
   // valid again
   pTmSt->setCapacity(3);
   pTW1->setValidStatus(VALID);

   // Activate the telemetry manager and check that the correct event is generated
   // (The second telemetry packet should have been rejected)
   pTm->activate();
   if ( !verifyLatestEvent(nEvt+1,EVT_TOO_MANY_TM_BYTES ) )
        return;
   nEvt++;

   // Reset the array where telemetry data are written, reset the
   // size of the telemetry stream, and reset the values of the telemetry packets
   pTmSt->setCapacity(size);
   pTW1->setValue(0,d11);
   pTW1->setValue(1,d12);
   pTW2->setValue(0,d21);
   pTW2->setValue(1,d22);
   for (unsigned int i=0; i<size; i++)
       tmData[i] = 0;

   // Force the first telemetry packet to be "not valid" and submit it for
   // immediate dispatch to the telemetry stream. Activate the telemetry manager.
   // The immediate dispatch packet should not be written to the telemetry stream.
   // Two events should be generated (the telemetry packet is sent twice!)
   pTW1->setValidStatus(NOT_VALID);
   pTm->sendTelemetryPacket(pTW1);
   pTm->activate();
   if ( ( tmData[4] != 0 ) || ( tmData[5] != 0 ) )
   {    setTestResult(TEST_FAILURE, "Wrong data written to telemetry stream");
        return;
   }
   if ( !verifyLatestEvent(nEvt+2,EVT_TM_ITEM_NOT_VALID) )
        return;
   if ( !verifySpecificEvent(nEvt+1,EVT_TM_ITEM_NOT_VALID) )
        return;
   nEvt++;
   nEvt++;

   // Check that "in use" status of pTW1 has been set to "not in use"
   if ( pTW1->isInUse() )
   {    setTestResult(TEST_FAILURE, "Wrong inUse status");
        return;
   }
   if ( !pTW2->isInUse() )
   {    setTestResult(TEST_FAILURE, "Wrong inUse status");
        return;
   }

   // Reset "in use" status
   pTW1->setInUse(true);
   pTW2->setInUse(true);

   // Reset the array where telemetry data are written
   for (unsigned int i=0; i<size; i++)
       tmData[i] = 0;

   // Decrease the size of the telemetry stream to make it too small for the
   // telemetry packet, make the telemetry valid again, and resubmit for sending
   // to the TM stream
   // Nothing should be written to the TM stream and two events should be generated
   // (one for the repetitive packet and one for the immediate dispatch packet)
   pTmSt->setCapacity(1);
   pTW1->setValidStatus(VALID);
   pTm->sendTelemetryPacket(pTW1);
   pTm->activate();
   if ( ( tmData[0] != 0 ) || ( tmData[1] != 0 ) )
   {    setTestResult(TEST_FAILURE, "Wrong data written to telemetry stream");
        return;
   }
   if ( !verifyLatestEvent(nEvt+2,EVT_TOO_MANY_TM_BYTES) )
        return;
   if ( !verifySpecificEvent(nEvt+1,EVT_TOO_MANY_TM_BYTES) )
        return;
   nEvt++;
   nEvt++;

   // Check that "in use" status of pTW1 has been set to "not in use"
   if ( pTW1->isInUse() )
   {    setTestResult(TEST_FAILURE, "Wrong inUse status");
        return;
   }
   if ( !pTW2->isInUse() )
   {    setTestResult(TEST_FAILURE, "Wrong inUse status");
        return;
   }

   // Reset "in use" status
   pTW1->setInUse(true);
   pTW2->setInUse(true);
   // Try to submit three packets for immediate dispatch (the capacity of the
   // imemdiate dispatch queue is 2) and check that the correct event is generated
   pTm->sendTelemetryPacket(pTW1);
   pTm->sendTelemetryPacket(pTW1);
   pTm->sendTelemetryPacket(pTW1);
   if ( !verifyLatestEvent(nEvt+1,EVT_TM_QUEUE_FULL) )
        return;
   nEvt++;

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;
}
