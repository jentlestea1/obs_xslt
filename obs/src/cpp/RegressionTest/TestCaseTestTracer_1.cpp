//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseTestTracer_1.cpp
//
// Version	1.1
// Date		18.04.03
// Author	A. Pasetti (P&P Software)

#include "TestCaseTestTracer_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestCompilerSwitches.h"
#include "../System/DC_TestTracer.h"
#include <stdio.h>

TestCaseTestTracer_1::TestCaseTestTracer_1(void) :
	TestCaseGenericSetUp(ID_TESTTRACER*10+1,"TestCaseTestTracer_1") {
		return;
}

void TestCaseTestTracer_1::runTestCase(void) {

#ifdef MS_HOST
   DC_TestTracer* pTrc = new DC_TestTracer();

   // Dummy tracer should be enabled upon creation
   if ( (pTrc->isEnabled() != ENABLED) )
	{	setTestResult(TEST_FAILURE, "Test Tracer component should be enabled");
		return;
	}

   // Send a synch trace signal.
   TD_TraceItem item = 0x0001;
   pTrc->sendSynchTrace(item);

   // Disable the tracer and check status.
   pTrc->setEnabled(DISABLED);
   if ( (pTrc->isEnabled() != DISABLED) )
	{	setTestResult(TEST_FAILURE, "Test Tracer component should be disabled");
		return;
	}

   // Send a synch trace signal. This should have no effect because the tracer
   // is disabled.
   item = 0x0011;
   pTrc->sendSynchTrace(item);

   // Send a new packet trace signal. This should have no effect because the tracer
   // is disabled.
   TD_TraceItem itemPacket[2];
   itemPacket[0] = 0x0022;
   itemPacket[1] = 0x0033;
   pTrc->sendPacketTrace(2,itemPacket);

   // Enabled the tracer and send a packet trace signal.
   pTrc->setEnabled(ENABLED);
   itemPacket[0] = 0x0002;
   itemPacket[1] = 0x0003;
   pTrc->sendPacketTrace(2,itemPacket);

   // Close the log file
   pTrc->closeLogFile();

   // Re-open the log file and check that the content is as expected
   const char* const logFileName = pTrc->getLogFileName();
   FILE* logFile;
   if( (logFile  = fopen(logFileName,"r")) == pNULL )
       printf( "\nThe file %s could not be opened\n",logFileName);
	else
       printf( "\nThe file %s was successfully opened\n",logFileName);
   int readItem=0;
   char s1[81];            // strings to hold the lines read from the log file
   char s2[81];
   char s3[81];
   char s4[81];
   char s5[81];
   char s6[81];
   fgets(s1,80,logFile);    // read the log file
   fgets(s2,80,logFile);
   fgets(s3,80,logFile);
   fgets(s4,80,logFile);
   fgets(s5,80,logFile);
   fgets(s6,80,logFile);
   char h[81];             // string to hold the line header (to be ignored)
   sscanf(s4,"%s %i",&h,&readItem);
   if ( readItem != 1 )    // check first trace item written to log file
	{	setTestResult(TEST_FAILURE, "First item written to log file is wrong");
		return;
	}
   sscanf(s5,"%s %i",&h,&readItem);
   if ( readItem != 2 )    // check second trace item written to log file
	{	setTestResult(TEST_FAILURE, "Second item written to log file is wrong");
		return;
	}
   sscanf(s6,"%s %i",&h,&readItem);
   if ( readItem != 3 )    // check third trace item written to log file
	{	setTestResult(TEST_FAILURE, "Third item written to log file is wrong");
		return;
	}
#endif

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
