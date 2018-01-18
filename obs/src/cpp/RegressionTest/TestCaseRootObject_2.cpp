//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseRootObject_2.cpp
//
// Version	1.1
// Date		13.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../Base/CC_RootObject.h"
#include "TestCaseRootObject_2.h"

TestCaseRootObject_2::TestCaseRootObject_2(void) :
	TestCaseGenericSetUp(ID_ROOTOBJECT*10+2,"TestCaseRootObject_2") {
		return;
}

void TestCaseRootObject_2::runTestCase(void) {

     CC_RootObject* pr1 = new CC_RootObject();
     CC_RootObject* pr2 = new CC_RootObject();
     CC_RootObject* pr3 = new CC_RootObject();

	if ( pr1->getClassId() != ID_ROOTOBJECT )
	{	setTestResult(TEST_FAILURE, "Incorrect setting of class identifier");
		return;
	}

	if ( pr2->getClassId() != pr1->getClassId() )
	{	setTestResult(TEST_FAILURE, "Incorrect setting of class identifier");
		return;
	}

	if ( pr3->getClassId() != pr2->getClassId() )
	{	setTestResult(TEST_FAILURE, "Incorrect setting of class identifier");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
