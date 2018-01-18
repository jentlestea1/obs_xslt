//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseChecksum_1.cpp
//
// Version	1.0
// Date		13.01.04
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Utilities/Checksum.h"
#include "TestCaseChecksum_1.h"

TestCaseChecksum_1::TestCaseChecksum_1(void) :
	TestCaseGenericSetUp(ID_CHECKSUM*10+1,"TestCaseChecksum_1") {
		return;
}

void TestCaseChecksum_1::runTestCase(void) {

   unsigned char data[10];
   unsigned short result;

   // Check the first stream of data
   data[0] = 0;
   data[1] = 0;

   result = doChecksum(data,2);
   if ( result!=0xFFFF )
   {	setTestResult(TEST_FAILURE, "Incorrect checksum result");
		return;
   }
   if ( !verifyChecksum(data,2,result) )
   {	setTestResult(TEST_FAILURE, "Incorrect checksum verification");
		return;
   }

   // Check the second stream of data
   data[0] = 0;
   data[1] = 0;
   data[2] = 0;

   result = doChecksum(data,3);
   if ( result!=0xFFFF )
   {	setTestResult(TEST_FAILURE, "Incorrect checksum result");
		return;
   }
   if ( !verifyChecksum(data,3,result) )
   {	setTestResult(TEST_FAILURE, "Incorrect checksum verification");
		return;
   }

   // Check the third stream of data
   data[0] = 0xAB;
   data[1] = 0xCD;
   data[2] = 0xEF;
   data[3] = 0x01;

   result = doChecksum(data,4);
   if ( result!=0x9CF8 )
   {	setTestResult(TEST_FAILURE, "Incorrect checksum result");
		return;
   }
   if ( !verifyChecksum(data,4,result) )
   {	setTestResult(TEST_FAILURE, "Incorrect checksum verification");
		return;
   }  

   verifyChecksum(data,4,result) ;

   // Check the fourth stream of data
   data[0] = 0x14;
   data[1] = 0x56;
   data[2] = 0xF8;
   data[3] = 0x9A;
   data[4] = 0x00;
   data[5] = 0x01;

   result = doChecksum(data,6);
   if ( result!=0x24DC )
   {	setTestResult(TEST_FAILURE, "Incorrect checksum result");
		return;
   }
   if ( !verifyChecksum(data,6,result) )
   {	setTestResult(TEST_FAILURE, "Incorrect checksum verification");
		return;
   }

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
