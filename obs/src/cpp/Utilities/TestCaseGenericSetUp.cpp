//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseGenericSetUp.cpp
//
// Version	1.0
// Date		13.04.03
// Author	A. Pasetti (P&P Software)

#include "TestCaseGenericSetUp.h"
#include "TestCase.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"
#include "../Data/DC_DummyDataPool.h"
#include "../Data/DC_DummyDatabase.h"
#include "../System/DC_DummyObsClock.h"
#include "../System/DC_DummyTracer.h"
#include "../Telemetry/PUSTelemetryPacket.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Telemetry/DC_PUSTcVerificationPacket.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"
#include "../Telemetry/DC_DummyPUSTelemetryPacket.h"
#include "../Telecommand/PUSTelecommand.h"

bool TestCaseGenericSetUp::firstActivation = true;

TestCaseGenericSetUp::TestCaseGenericSetUp(int testId, char* testName):
     TestCase(testId,testName) {
     return;
}

bool TestCaseGenericSetUp::setUpTestCase(void) {

   if (firstActivation) {
     // Initialize the system list size in class CC_RootObject
     CC_RootObject::setSystemListSize(MAX_N_OBJECTS);

     // Load an event repository into class CC_RootObject
     DC_EventRepository* pRep = new DC_EventRepository();
     DC_DummyObsClock* pClk = new DC_DummyObsClock();
     pRep->setObsClock(pClk);
     pRep->setRepositorySize(EVT_REP_SIZE);

     // Load repository into CC_RootObject and check success
     CC_RootObject::setEventRepository(pRep);
     if ( CC_RootObject::getEventRepository()!=pRep )
         return INITIALIZATION_FAILURE;

     // Load a dummy database into class CC_RootObject and check success
     DC_DummyDatabase* pDB = new DC_DummyDatabase();
     CC_RootObject::setParameterDatabase(pDB);
     if ( CC_RootObject::getParameterDatabase()!=pDB )
         return INITIALIZATION_FAILURE;

     // Load a dummy datapool into class CC_RootObject and check success
     DC_DummyDataPool* pDP = new DC_DummyDataPool();
     CC_RootObject::setDataPool(pDP);
     if ( CC_RootObject::getDataPool()!=pDP )
         return INITIALIZATION_FAILURE;

     // Load a tracer into class CC_RootObject and check success
     DC_DummyTracer* pTrc = new DC_DummyTracer();
     CC_RootObject::setTracer(pTrc);
     if ( CC_RootObject::getTracer()!=pTrc )
         return INITIALIZATION_FAILURE;

     // Configure the static part of PUS telecommand and telemetry classes
     PUSTelemetryPacket::setDefaultDestination(TEST_TM_DEF_DEST);
     PUSTelemetryPacket::setApplicationId(TEST_TM_APID);
     PUSTelemetryPacket::setObsClock(pClk);
     PUSTelecommand::setApplicationId(TEST_TC_APID);

     firstActivation = false;
   }

	return INITIALIZATION_SUCCESS;
}

void TestCaseGenericSetUp::runTestCase(void) {
     return;
}

bool TestCaseGenericSetUp::shutDownTestCase(void) {
     return SHUTDOWN_SUCCESS;
}
