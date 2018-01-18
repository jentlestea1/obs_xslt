//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseInRangeProfile_1.cpp
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
#include "../FDIR/DC_InRangeProfile.h"
#include "../FDIR/RangeProfile.h"
#include "TestCaseInRangeProfile_1.h"

TestCaseInRangeProfile_1::TestCaseInRangeProfile_1(void) :
	TestCaseGenericSetUp(ID_INRANGEPROFILE*10+1,"TestCaseInRangeProfile_1") {
		return;
}

void TestCaseInRangeProfile_1::runTestCase(void) {

   DC_InRangeProfile* mp = new DC_InRangeProfile();

   // Check the value of the class identifier
   if ( mp->getClassId() != ID_INRANGEPROFILE )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Check configuration status
   if ( mp->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Set the lower bound
   TD_Float lb = 10.0;
   mp->setLowerBound(lb);
   TD_Float ret = mp->getLowerBound();
   TD_Float eps = (TD_Float)0.00001;
   if ( ((ret-lb)>eps) || ((lb-ret)>eps) )
   {    setTestResult(TEST_FAILURE, "Wrong lower bound value");
        return;
   }

   // Set the upper bound
   TD_Float ub = (TD_Float)12.0;
   mp->setUpperBound(ub);
   ret = mp->getUpperBound();
   if ( ((ret-ub)>eps) || ((ub-ret)>eps) )
   {    setTestResult(TEST_FAILURE, "Wrong lower bound value");
        return;
   }

   // Check configuration status
   if ( !mp->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Check monitoring check for a case with "no deviation from profile"
   if ( mp->deviatesFromProfile(lb-1) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }

   // Check monitoring check for a case with "deviation from profile"
   if ( !mp->deviatesFromProfile((lb+ub)/2) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }

   // Disable monitoring profile and repeat check
   mp->setEnabled(DISABLED);
   if ( mp->deviatesFromProfile((lb+ub)/2) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }

   // Enabble and check monitoring check for a case with "no deviation from profile"
   mp->setEnabled(ENABLED);
   if ( mp->deviatesFromProfile((lb-1)) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }

   // Check monitoring check for a case with "deviation from profile"
   if ( !mp->deviatesFromProfile((lb+ub)/2) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;

}
