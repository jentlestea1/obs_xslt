//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_TestTracer.cpp
//
// Version	1.0
// Date		30.09.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestCompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_TestTracer.h"
#include <time.h>

DC_TestTracer::DC_TestTracer(void) {
	logFile = pNULL;
#ifdef MS_HOST
   if( (logFile  = fopen(TEST_TRACER_LOG_FILE,"w")) == pNULL )
       printf( "\nThe file %s could not be opened\n",TEST_TRACER_LOG_FILE);
	else
       printf( "\nThe file %s was successfully opened\n",TEST_TRACER_LOG_FILE);

   // Write header information
   time_t ltime;
   time( &ltime );
   fprintf(logFile,"Test Tracer Log File\n");
   fprintf(logFile,"Test Run Performed on %s\n",ctime( &ltime ));
#else
   printf("Test Tracer Log File\n");
   printf("\n");
#endif

   // Set the class identifer
   setClassId(ID_TESTTRACER);
}

void DC_TestTracer::sendRawTrace(TD_TraceItem rawItem) const {
#ifdef MS_HOST
   assert( logFile != pNULL);
   fprintf(logFile,"Raw_Tracer_Item: %x\n", rawItem);
#else
   printf("Raw Tracer Item: %x\n", rawItem);
#endif
}

void DC_TestTracer::closeLogFile(void) {
#ifdef MS_HOST
   assert( logFile != pNULL);
   fclose(logFile);
   logFile = pNULL;
#endif
}

const char* const DC_TestTracer::getLogFileName(void) {
#ifdef MS_HOST
   return TEST_TRACER_LOG_FILE;
#else
   return pNULL;
#endif
}
