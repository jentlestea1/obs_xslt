//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDeltaProfile_1.cpp
//
// Version	1.2
// Date		18.04.03 (Version 1.1)
//          01.10.03 (Version 1.2)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.2: replaced double and int with TD_Float and TD_Integer

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../FDIR/DC_DeltaProfile.h"
#include "TestCaseDeltaProfile_1.h"

TestCaseDeltaProfile_1::TestCaseDeltaProfile_1(void) :
	TestCaseGenericSetUp(ID_DELTAPROFILE*10+1,"TestCaseDeltaProfile_1") {
		return;
}

void TestCaseDeltaProfile_1::runTestCase(void) {

   DC_DeltaProfile* mp = new DC_DeltaProfile();
   TD_Float deltaThreshold = 2.0;
   TD_Integer valInt = 10;
   TD_Float valFloat = 5.0;

   // Check the value of the class identifier
   if ( mp->getClassId() != ID_DELTAPROFILE )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Check configuration status
   if ( mp->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Set the delta threshold
   mp->setDeltaThreshold(deltaThreshold);
   if ( mp->getDeltaThreshold() != deltaThreshold )
   {    setTestResult(TEST_FAILURE, "Wrong delta threshold value");
        return;
   }

   // Check configuration status
   if ( !mp->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Check monitoring check for a case with "no deviation from profile"
   // (argument of type double)
   if ( mp->deviatesFromProfile(valFloat) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }
   if ( mp->deviatesFromProfile(valFloat+deltaThreshold-(TD_Float)0.1) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }

   // Check monitoring check for a case with "deviation from profile"
   // (argument of type double)
   if ( mp->deviatesFromProfile(valFloat) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }
   if ( !mp->deviatesFromProfile(valFloat+deltaThreshold+(TD_Float)0.1) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }

   // Check the effect of resetting the monitoring check
   if ( mp->deviatesFromProfile(valFloat+deltaThreshold+(TD_Float)0.1) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }
   mp->reset();
   if ( mp->deviatesFromProfile(valFloat) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }

   // Check monitoring check for a case with "no deviation from profile
   // (argument of type int)
   mp->reset();
   if ( mp->deviatesFromProfile(valInt) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }
   if ( mp->deviatesFromProfile(valInt+deltaThreshold-1) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }

   // Check monitoring check for a case with "deviation from profile"
   // (argument of type int)
   if ( mp->deviatesFromProfile(valInt) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }
   if ( !mp->deviatesFromProfile(valInt+deltaThreshold+1) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;

}
