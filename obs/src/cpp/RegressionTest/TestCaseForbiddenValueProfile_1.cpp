//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseForbiddenValueProfile_1.cpp
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
#include "../FDIR/DC_ForbiddenValueProfile.h"
#include "TestCaseForbiddenValueProfile_1.h"

TestCaseForbiddenValueProfile_1::TestCaseForbiddenValueProfile_1(void) :
	TestCaseGenericSetUp(ID_FORBIDDENVALUEPROFILE*10+1,"TestCaseForbiddenValueProfile_1") {
		return;
}

void TestCaseForbiddenValueProfile_1::runTestCase(void) {

   DC_ForbiddenValueProfile* mp = new DC_ForbiddenValueProfile();

   // Check the value of the class identifier
   if ( mp->getClassId() != ID_FORBIDDENVALUEPROFILE )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Set the forbidden value
   TD_Integer fv = 10;
   mp->setForbiddenValue(fv);
   if ( mp->getForbiddenValue() != fv )
   {    setTestResult(TEST_FAILURE, "Wrong forbidden value");
        return;
   }

   // Check monitoring check for a case with "no deviation from profile"
   if ( mp->deviatesFromProfile((TD_Integer)(fv+1)) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }

   // Check monitoring check for a case with "deviation from profile"
   if ( !mp->deviatesFromProfile(fv) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }

   // Disable monitoring profile and repeat check
   mp->setEnabled(DISABLED);
   if ( mp->deviatesFromProfile(fv) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }
   mp->setEnabled(ENABLED);

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
