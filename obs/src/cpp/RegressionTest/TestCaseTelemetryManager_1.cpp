//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseTelemetryManager_1.cpp
//
// Version	1.1
// Date		04.03.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Telemetry/DC_SimpleTelemetryModeManager.h"
#include "../Telemetry/DC_CycleDataItem16TmStream.h"
#include "../Telemetry/CC_TelemetryManager.h"
#include "TestCaseTelemetryManager_1.h"

TestCaseTelemetryManager_1::TestCaseTelemetryManager_1(void) :
	TestCaseGenericSetUp(ID_TELEMETRYMANAGER*10+1,"TestCaseTelemetryManager_1") {
		return;
}

void TestCaseTelemetryManager_1::runTestCase(void) {

   // Create the telemetry manager
   CC_TelemetryManager* pTm = new CC_TelemetryManager();

   // Check the value of the class identifier
   if ( pTm->getClassId() != ID_TELEMETRYMANAGER )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Check that the telemetry manager is not configured
   if ( pTm->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Create and load a telemetry mode manager and verify that it is loaded
   DC_SimpleTelemetryModeManager* pTmMm = new DC_SimpleTelemetryModeManager();
   pTm->setTelemetryModeManager(pTmMm);
   if ( pTm->getTelemetryModeManager() != pTmMm )
   {    setTestResult(TEST_FAILURE, "Wrong telemetry mode manager");
        return;
   }

   // Create and load a telemetry stream and verify that it is loaded
   DC_CycleDataItem16TmStream* pTmSt = new DC_CycleDataItem16TmStream();
   pTm->setTelemetryStream(pTmSt);
   if ( pTm->getTelemetryStream() != pTmSt )
   {    setTestResult(TEST_FAILURE, "Wrong telemetry stream");
        return;
   }

   // Set the size of the immediate dispatch queue
   pTm->setImmediateQueueSize(0);
   if ( pTm->getImmediateQueueSize()!=0 )
   {    setTestResult(TEST_FAILURE, "Wrong immediate dispatch queue size");
        return;
   }

   // Check status of the immediate dispatch queue
   if ( pTm->getImmediateQueueSize()!=0 )
   {    setTestResult(TEST_FAILURE, "Wrong size of the immediate dispatch queue size");
        return;
   }
   if ( !pTm->isImmediateQueueFull())
   {    setTestResult(TEST_FAILURE, "Wrong status of the immediate dispatch queue size");
        return;
   }

   // Check that the telemetry manager is now configured
   if ( !pTm->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;

}
