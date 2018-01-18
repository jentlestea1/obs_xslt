//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseRootObject_3.cpp
//
// Version	1.1
// Date		11.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"
#include "TestCaseRootObject_3.h"

TestCaseRootObject_3::TestCaseRootObject_3(void) :
	TestCaseGenericSetUp(ID_ROOTOBJECT*10+3,"TestCaseRootObject_3") {
		return;
}

void TestCaseRootObject_3::runTestCase(void) {

   CC_RootObject* pr1 = new CC_RootObject();
   CC_RootObject* pr2 = new CC_RootObject();

   if ( (pr1->isObjectConfigured() == NOT_CONFIGURED) ||
        (pr2->isObjectConfigured() == NOT_CONFIGURED) )
	{	setTestResult(TEST_FAILURE, "Failure to report correct object configuration status");
		return;
	}

	if ( CC_RootObject::isSystemConfigured() == NOT_CONFIGURED )
	{	setTestResult(TEST_FAILURE, "Failure to report correct system configuration status");
		return;
	}

   // Create but do not configure an event repository. This should cause the
   // system configuration check to fail
   DC_EventRepository* pRep = new DC_EventRepository();
	if ( CC_RootObject::isSystemConfigured() != NOT_CONFIGURED )
	{	setTestResult(TEST_FAILURE, "Failure to report correct system configuration status");
		return;
	}

   // Make use of the pRep variable. This is necessary to avoid
   // a compiler warning
   pRep->isObjectConfigured();

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}

