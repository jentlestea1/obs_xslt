//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseOutOfRangeProfile_1.cpp
//
// Version	1.2
// Date		11.04.03 (Version 1.1)
//          01.10.03 (Version 1.2)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.2: replaced double and int with TD_Float and TD_Integer

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../FDIR/DC_OutOfRangeProfile.h"
#include "../FDIR/RangeProfile.h"
#include "TestCaseOutOfRangeProfile_1.h"

TestCaseOutOfRangeProfile_1::TestCaseOutOfRangeProfile_1(void) :
	TestCaseGenericSetUp(ID_OUTOFRANGEPROFILE*10+1,"TestCaseOutOfRangeProfile_1") {
		return;
}

void TestCaseOutOfRangeProfile_1::runTestCase(void) {

   DC_OutOfRangeProfile* mp = new DC_OutOfRangeProfile();

   // Check the value of the class identifier
   if ( mp->getClassId() != ID_OUTOFRANGEPROFILE )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Configure the monitoring profile
   TD_Float lb = 10.0;
   TD_Float ub = 13.0;
   mp->setLowerBound(lb);
   mp->setUpperBound(ub);

   // Check monitoring check for a case with "no deviation from profile"
   if ( mp->deviatesFromProfile((TD_Float)((lb+ub)/2.0)) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }

   // Check monitoring check for a case with "deviation from profile"
   if ( !mp->deviatesFromProfile((TD_Float)(ub+1.0)) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;

}
