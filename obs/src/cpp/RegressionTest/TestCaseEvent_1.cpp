//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseEvent_1.cpp
//
// Version	1.0
// Date		13.09.02
// Author	     A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_Event.h"
#include "TestCaseEvent_1.h"

TestCaseEvent_1::TestCaseEvent_1(void) :
	TestCaseGenericSetUp(ID_EVENT*10+1,"TestCaseEvent_1") {
		return;
}

void TestCaseEvent_1::runTestCase(void) {

   DC_Event* pEvt = new DC_Event();

   // Set the event attributes
   pEvt->setTimeStamp(1);
   pEvt->setEventType((TD_EventType)2);

   // Check that the event attributes have correct values
	if ( (pEvt->getTimeStamp() != 1) ||
         (pEvt->getEventType() != 2) )
	{	setTestResult(TEST_FAILURE, "Incorrect event attribute values");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
