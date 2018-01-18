//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseStuckDataProfile_1.cpp
//
// Version	1.1
// Date		11.01.03 (Version 1.0)
//          01.10.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: replaced double and int with TD_Float and TD_Integer

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../FDIR/MonitoringProfile.h"
#include "../FDIR/DC_StuckDataProfile.h"
#include "../Event/DC_EventRepository.h"
#include "TestCaseStuckDataProfile_1.h"

TestCaseStuckDataProfile_1::TestCaseStuckDataProfile_1(void) :
	TestCaseGenericSetUp(ID_STUCKDATAPROFILE*10+1,"TestCaseStuckDataProfile_1") {
		return;
}

void TestCaseStuckDataProfile_1::runTestCase(void) {

   DC_StuckDataProfile* mp = new DC_StuckDataProfile();
   unsigned int stuckThreshold = 2;
   TD_Integer sv = 10;

   // Check the value of the class identifier
   if ( mp->getClassId() != ID_STUCKDATAPROFILE )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Check configuration status
   if ( mp->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Set the stuck threshold
   mp->setStuckThreshold(stuckThreshold);
   if ( mp->getStuckThreshold() != stuckThreshold )
   {    setTestResult(TEST_FAILURE, "Wrong stuck threshold value");
        return;
   }

   // Check configuration status
   if ( !mp->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Check monitoring check for a case with "no deviation from profile"
   if ( mp->deviatesFromProfile(sv) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }
   if ( mp->deviatesFromProfile(sv) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }
   if ( mp->deviatesFromProfile((TD_Integer)(sv+1)) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }

   // Check monitoring check for a case with "deviation from profile"
   if ( mp->deviatesFromProfile(sv) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }
   if ( mp->deviatesFromProfile(sv) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }
   if ( !mp->deviatesFromProfile(sv) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }

   // Check the effect of resetting the monitoring check
   if ( mp->deviatesFromProfile((TD_Integer)(sv+1)) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }
   if ( mp->deviatesFromProfile((TD_Integer)(sv+1)) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }
   mp->reset();
   if ( mp->deviatesFromProfile((TD_Integer)(sv+1)) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }
   if ( mp->deviatesFromProfile((TD_Integer)(sv+1)) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }
   if ( !mp->deviatesFromProfile((TD_Integer)(sv+1)) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }

   // Check monitoring check for real-valued argument
   if (isNonNominalCheckAllowed()) {
        if ( !mp->deviatesFromProfile((TD_Float)1.0) )
        {    setTestResult(TEST_FAILURE, "Wrong monitoring check result for real-valued argument");
             return;
        }
   }

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;

}
