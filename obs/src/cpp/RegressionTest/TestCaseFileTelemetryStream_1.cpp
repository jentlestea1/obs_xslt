//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseFileTelemetryStream_1.cpp
//
// Version	1.1
// Date		04.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_FileTelemetryStream.h"
#include "../Telemetry/DC_DummyTelemetryPacket.h"
#include "TestCaseFileTelemetryStream_1.h"
#include <stdio.h>

TestCaseFileTelemetryStream_1::TestCaseFileTelemetryStream_1(void) :
	TestCaseGenericSetUp(ID_FILETELEMETRYSTREAM*10+1,"TestCaseFileTelemetryStream_1") {
		return;
}

void TestCaseFileTelemetryStream_1::runTestCase(void) {

   DC_FileTelemetryStream* pTmStream = new DC_FileTelemetryStream();

   // Check the value of the class identifier
   if ( pTmStream->getClassId() != ID_FILETELEMETRYSTREAM )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Open and load the telemetry stream file and check correctness
   FILE* out=pNULL;
   if( (out  = fopen("TelemetryStream.txt","w")) == pNULL )
   {    setTestResult(TEST_FAILURE, "File 'TelemetryStream.txt' could not be opened");
        return;
   }
   pTmStream->setOutputStream(out);
   if ( pTmStream->getOutputStream() != out )
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
   fclose(out);
   setTestResult(TEST_SUCCESS, "Check 'TelemetryStream.txt' file");
   return;
}
