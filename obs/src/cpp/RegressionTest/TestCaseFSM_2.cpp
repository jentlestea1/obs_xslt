//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseFSM_2.cpp
//
// Version	1.1
// Date		04.04.03
// Author	A. Pasetti (P&P Software)

#include "TestCaseFSM_2.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../FSM/CC_FSM.h"
#include "../FSM/DC_DummyFsmState.h"
#include "../FSM/DC_FsmEvent.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"

TestCaseFSM_2::TestCaseFSM_2(void) :
	TestCaseGenericSetUp(ID_FSM*10+2,"TestCaseFSM_2") {
		return;
}

void TestCaseFSM_2::runTestCase(void) {

   CC_FSM* pFsm = new CC_FSM();

   // Configure the FSM
   pFsm->setNumberOfStates(4);

   DC_DummyFsmState* pState[4];
   for (TD_FsmStateIndex i=0; i<pFsm->getNumberOfStates(); i++)
      pState[i] = new DC_DummyFsmState();

   for (TD_FsmStateIndex i=0; i<pFsm->getNumberOfStates(); i++)
      pFsm->setState(i,pState[i]);

   pFsm->reset();

   // FSM object should now be configured
   if ( (pFsm->isObjectConfigured() == NOT_CONFIGURED) )
	{	setTestResult(TEST_FAILURE,
             "Wrong FSM configuration status after configuration was completed");
		return;
	}

   // Create and configure the FsmEvents
   DC_FsmEvent* pFsmEvt_1 = new DC_FsmEvent();
   DC_FsmEvent* pFsmEvt_2 = new DC_FsmEvent();
   DC_FsmEvent* pFsmEvt_3 = new DC_FsmEvent();
   pFsmEvt_1->setTargetFsm(pFsm);
   pFsmEvt_2->setTargetFsm(pFsm);
   pFsmEvt_3->setTargetFsm(pFsm);
   pFsmEvt_1->setTargetState(1);
   pFsmEvt_2->setTargetState(2);
   pFsmEvt_3->setTargetState(0);

   // Activate FSM twice (just to exercise the FSM)
   pFsm->activate();
   pFsm->activate();

   // Fire FsmEvent 1 and check transition
   pFsmEvt_1->execute();
   if ( pFsm->getCurrentState() != 0)
	{	setTestResult(TEST_FAILURE,
             "No state transition should have occurred");
		return;
	}
   pFsm->activate();
   if ( pFsm->getCurrentState() != 1)
	{	setTestResult(TEST_FAILURE,
             "Wrong state after FsmEvt_1 firing");
		return;
	}

   // Check that the correct event was created
   DC_EventRepository* pRep = CC_RootObject::getEventRepository();
   pRep->latest();
   if ( pRep->getEventType() != EVT_FSM_TRANSITION )
	{	setTestResult(TEST_FAILURE,
             "Wrong event after state transition");
		return;
	}

   // Activate FSM twice and check that no state transition takes place
   pFsm->activate();
   pFsm->activate();
   if ( pFsm->getCurrentState() != 1)
	{	setTestResult(TEST_FAILURE,
             "Wrong state after activation of FSM");
		return;
	}

   // Fire events 2 and 3 and check that only second firing has an effect
   pFsmEvt_2->execute();
   pFsmEvt_3->execute();
   pFsm->activate();
   if ( pFsm->getCurrentState() != 0)
	{	setTestResult(TEST_FAILURE,
             "Wrong state after FsmEvt_2 and FsmEvt_3 firing");
		return;
	}

   // Activate FSM twice (just to exercise state 0)
   pFsm->activate();
   pFsm->activate();

   // Disable transitions into state 2, fire FsmEvt_2 and check that
   // no transition takes place
   pFsm->setTransitionEnableStatus(2,DISABLED);
   pFsmEvt_2->execute();
   pFsm->activate();
   if ( pFsm->getCurrentState() != 0)
	{	setTestResult(TEST_FAILURE,
             "Wrong state after FsmEvt_2 firing");
		return;
	}

   // Check that the correct event was created
   pRep->latest();
   if ( pRep->getEventType() != EVT_FSM_TRANSITION_DISABLED )
	{	setTestResult(TEST_FAILURE,
             "Wrong event after state transition");
		return;
	}

    // Attempt to disable transition into non-existent state
    if (isNonNominalCheckAllowed()) {
        pFsm->setTransitionEnableStatus(4,DISABLED);
        pRep->latest();
        if ( pRep->getEventType() != EVT_ILLEGAL_FS )
	    {	setTestResult(TEST_FAILURE,
                "Failure of non-nominal behaviour check");
		    return;
	    }
    }

    setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
