//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseFileTelemetryStream_2.cpp
//
// Version	1.0
// Date		04.03.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Telemetry/DC_FileTelemetryStream.h"
#include "../Telemetry/DC_DummyTelemetryPacket.h"
#include "TestCaseFileTelemetryStream_2.h"
#include <stdio.h>

TestCaseFileTelemetryStream_2::TestCaseFileTelemetryStream_2(void) :
	TestCaseGenericSetUp(ID_FILETELEMETRYSTREAM*10+2,"TestCaseFileTelemetryStream_2") {
		return;
}

void TestCaseFileTelemetryStream_2::runTestCase(void) {

   DC_FileTelemetryStream* pTmStream = new DC_FileTelemetryStream();

   // Load the telemetry stream and check correctness
   FILE* out=pNULL;
   pTmStream->setOutputStream(out);
   if ( pTmStream->getOutputStream() != pNULL )
   {    setTestResult(TEST_FAILURE, "Wrong telemetry stream file");
        return;
   }

   // Create and configure the telemetry packet to be written to the stream
   DC_DummyTelemetryPacket* pTI = new DC_DummyTelemetryPacket();
   pTI->setNumberOfBytes(2);
   pTI->setValue(0,1);
   pTI->setValue(1,2);

   // Write telemetry packet to the telemetry stream
   pTmStream->write(pTI);
   pTmStream->flush();
   pTI->setValue(0,2);
   pTI->setValue(1,3);
   pTmStream->write(pTI);
   pTmStream->flush();

   // Close output file and set test result message
   if ( out != pNULL )
    fclose(out);
   setTestResult(TEST_SUCCESS, "Check standard output");
   return;
}
