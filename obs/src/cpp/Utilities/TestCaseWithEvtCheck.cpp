//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseWithEvtCheck.cpp
//
// Version	1.0
// Date		28.11.03 
// Author	R. Totaro
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "TestCaseWithEvtCheck.h"

#include <stdio.h>

TestCaseWithEvtCheck::TestCaseWithEvtCheck(int testId,char *testName):
	TestCaseGenericSetUp(testId,testName) {
        return;
}

bool TestCaseWithEvtCheck::setUpTestCase(void) {
    return TestCaseGenericSetUp::setUpTestCase();
}

unsigned int TestCaseWithEvtCheck::getNumberOfEvents(void) const {
    return CC_RootObject::getEventRepository()->getCounter();
}

unsigned int TestCaseWithEvtCheck::getEventRepositorySize(void) const {
    return CC_RootObject::getEventRepository()->getRepositorySize();
}

bool TestCaseWithEvtCheck::verifyLatestEventHidden(const int line,
                                                   const unsigned int nEvt,
											       const TD_EventType eventType) {
    char msg[512];

    assert(eventType>0);

    DC_EventRepository* pRep = CC_RootObject::getEventRepository();

    if (pRep->getCounter()!=nEvt) {
        sprintf(msg,"Wrong number of events at line %d",line);
		setTestResult(TEST_FAILURE,msg);
        return false;
	}

    pRep->latest();
	if (pRep->getEventType()!=eventType) {
        sprintf(msg,"Wrong event type at line %d",line);
		setTestResult(TEST_FAILURE,msg);
		return false;
	}

	return true;
}

bool TestCaseWithEvtCheck::verifySpecificEventHidden(const int line,
                                                     const unsigned int n,
											         const TD_EventType eventType) {
    char      msg[512];
    DC_EventRepository* pRep = CC_RootObject::getEventRepository();
	const int distance=(pRep->getCounter()-n);

	assert(eventType>0);
	assert(distance<(int)pRep->getRepositorySize());

	if (distance<0) {
        sprintf(msg,"Wrong number of events at line %d",line);
		setTestResult(TEST_FAILURE,msg);
		return false;
	}

    pRep->latest();
	for (int i=0;i<distance;i++)
		pRep->previous();

	if (pRep->getEventType()!=eventType) {
        sprintf(msg,"Wrong event type at line %d",line);
		setTestResult(TEST_FAILURE,msg);
		return false;
	}

	return true;
}
