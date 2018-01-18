//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyTracer_1.cpp
//
// Version	1.1
// Date		18.04.03
// Author	A. Pasetti (P&P Software)

#include "TestCaseDummyTracer_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../System/Tracer.h"
#include "../System/DC_DummyTracer.h"

TestCaseDummyTracer_1::TestCaseDummyTracer_1(void) :
	TestCaseGenericSetUp(ID_DUMMYTRACER*10+1,"TestCaseDummyTracer_1") {
		return;
}

void TestCaseDummyTracer_1::runTestCase(void) {

   DC_DummyTracer* pTrc = new DC_DummyTracer();

   // Dummy tracer should be disabled upon creation
   if ( (pTrc->isEnabled() != DISABLED) )
	{	setTestResult(TEST_FAILURE, "Dummy Tracer component should be disabled");
		return;
	}

   // Send a synch trace signal. This operation should have no effect. No
   // correctness check can be performed. The test can fail only through
   // a run time-error.
   TD_TraceItem item = 0x0001;
   pTrc->sendSynchTrace(item);

   // Send a packet trace signal. This operation should have no effect. No
   // correctness check can be performed. The test can fail only through
   // a run time-error.
   TD_TraceItem itemPacket[2];
   itemPacket[0] = 0x0002;
   itemPacket[0] = 0x0003;
   pTrc->sendPacketTrace(2,itemPacket);

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
