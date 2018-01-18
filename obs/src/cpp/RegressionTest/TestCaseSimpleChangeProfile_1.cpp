//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseSimpleChangeProfile_1.cpp
//
// Version	1.2
// Date		13.04.03 (Version 1.1)
//          01.10.03 (Version 1.2)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.2: replaced double and int with TD_Float and TD_Integer

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../FDIR/MonitoringProfile.h"
#include "../FDIR/DC_SimpleChangeProfile.h"
#include "../Event/DC_EventRepository.h"
#include "TestCaseSimpleChangeProfile_1.h"

TestCaseSimpleChangeProfile_1::TestCaseSimpleChangeProfile_1(void) :
	TestCaseGenericSetUp(ID_SIMPLECHANGEPROFILE*10+1,"TestCaseSimpleChangeProfile_1") {
		return;
}

void TestCaseSimpleChangeProfile_1::runTestCase(void) {

   DC_SimpleChangeProfile* mp = new DC_SimpleChangeProfile();

   // Check the value of the class identifier
   if ( mp->getClassId() != ID_SIMPLECHANGEPROFILE )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Check that monitoring check is enabled
   if ( !mp->isEnabled() )
   {    setTestResult(TEST_FAILURE, "Wrong enable status");
        return;
   }

   // Set the reference value
   TD_Integer rv = 10;
   mp->setReferenceValue(rv);
   if ( mp->getReferenceValue() != rv )
   {    setTestResult(TEST_FAILURE, "Wrong reference value");
        return;
   }

   // Check monitoring check for a case with "no deviation from profile"
   if ( mp->deviatesFromProfile(rv) )
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

   // Check monitoring check for a case with "deviation from profile"
   DC_EventRepository* rep = CC_RootObject::getEventRepository();
   unsigned int nEvt = rep->getCounter();
   if ( !mp->deviatesFromProfile((TD_Integer)(rv+1)) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }

   // Check generation of event reporting detection of deviation from profile
   if ( rep->getCounter() != (nEvt+1) )
   {    setTestResult(TEST_FAILURE, "Wrong number of events");
        return;
   }
   rep->latest();
   if ( rep->getEventType() != EVT_MON_PROFILE_VIOLATION )
   {    setTestResult(TEST_FAILURE, "Wrong event type");
        return;
   }

   // Disable monitoring profile and check new enable status
   mp->setEnabled(DISABLED);
   if ( mp->isEnabled() != DISABLED )
   {    setTestResult(TEST_FAILURE, "Wrong enable status");
        return;
   }

   // Check monitoring check for a case with "deviation from profile"
   // NB: the monitoring profile component is now disabled
   if ( mp->deviatesFromProfile((TD_Integer)(rv+1)) )
   {    setTestResult(TEST_FAILURE, "Wrong monitoring check result");
        return;
   }

   // Check that no events were generated
   if ( rep->getCounter() != (nEvt+1) )
   {    setTestResult(TEST_FAILURE, "Wrong number of events");
        return;
   }

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;

}
