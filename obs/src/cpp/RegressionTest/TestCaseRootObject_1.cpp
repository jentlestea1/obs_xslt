//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseRootObject_1.cpp
//
// Version	1.0
// Date		13.09.02
// Author	     A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../Base/CC_RootObject.h"
#include "TestCaseRootObject_1.h"

TestCaseRootObject_1::TestCaseRootObject_1(void) :
	TestCaseGenericSetUp(ID_ROOTOBJECT*10+1,"TestCaseRootObject_1") {
		return;
}

void TestCaseRootObject_1::runTestCase(void) {

     CC_RootObject* pr1 = new CC_RootObject();
     CC_RootObject* pr2 = new CC_RootObject();
     CC_RootObject* pr3 = new CC_RootObject();

	if ( pr2->getInstanceId() != (pr1->getInstanceId()+1) )
	{	setTestResult(TEST_FAILURE, "Incorrect setting of instance identifier");
		return;
	}

	if ( pr3->getInstanceId() != (pr2->getInstanceId()+1) )
	{	setTestResult(TEST_FAILURE, "Incorrect setting of instance identifier");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
