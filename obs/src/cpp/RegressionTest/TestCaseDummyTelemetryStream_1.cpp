//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyTelemetryStream_1.cpp
//
// Version	1.0
// Date		21.11.03 (Version 1.0)
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_DummyTelemetryPacket.h"
#include "../Telemetry/DC_DummyTelemetryStream.h"
#include "TestCaseDummyTelemetryStream_1.h"

TestCaseDummyTelemetryStream_1::TestCaseDummyTelemetryStream_1(void) :
	TestCaseGenericSetUp(ID_DUMMYTELEMETRYSTREAM*10+1,"TestCaseDummyTelemetryStream_1") {
    return;
}

void TestCaseDummyTelemetryStream_1::runTestCase(void) {
    DC_DummyTelemetryStream *pTmStream=new DC_DummyTelemetryStream;
    DC_DummyTelemetryPacket   *pTmItem  =new DC_DummyTelemetryPacket;

    // Check the value of the class identifier
    if (pTmStream->getClassId()!=ID_DUMMYTELEMETRYSTREAM) {
        setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
    }

    // Check getCapacity()'s return value
    if (pTmStream->getCapacity()!=MAX_INT) {
        setTestResult(TEST_FAILURE, "getCapacity() failed.");
        return;
    }

    // Check doesPacketFit()'s return value
    if (!pTmStream->doesPacketFit(pTmItem)) {
        setTestResult(TEST_FAILURE, "doesPacketFit() failed.");
        return;
    }

    // The following three calls won't do anything at all. They are
    // here to exercise the code.
    pTmStream->reset();
    pTmStream->flush();
    pTmStream->write(pTmItem);

    setTestResult(TEST_SUCCESS,"Test Successful");
    return;
}
