//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseFSM_3.cpp
//
// Version	1.0
// Date		14.10.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../FSM/CC_FSM.h"
#include "../FSM/DC_DummyConfigurableFsmState.h"
#include "../FSM/DC_FsmEvent.h"
#include "../FSM/FsmState.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"
#include "TestCaseFSM_3.h"

TestCaseFSM_3::TestCaseFSM_3(void) :
	TestCaseGenericSetUp(ID_FSM*10+3,"TestCaseFSM_3") {
		return;
}

void TestCaseFSM_3::runTestCase(void) {

   CC_FSM* pFsm = new CC_FSM();

   // Configure the FSM
   pFsm->setNumberOfStates(4);

   DC_DummyConfigurableFsmState* pState[4];
   for (TD_FsmStateIndex i=0; i<pFsm->getNumberOfStates(); i++)
      pState[i] = new DC_DummyConfigurableFsmState();

   pState[0]->setNextState(pState[1]);
   pState[1]->setNextState(pState[2]);
   pState[2]->setNextState(pState[3]);
   pState[3]->setNextState(pState[0]);

   for (TD_FsmStateIndex i=0; i<pFsm->getNumberOfStates(); i++)
      pFsm->setState(i,pState[i]);

   pFsm->reset();

   // FSM object should now be configured
   if ( (pFsm->isObjectConfigured() == NOT_CONFIGURED) )
	{	setTestResult(TEST_FAILURE,
             "Wrong FSM configuration status after configuration was completed");
		return;
	}

   // Check the correctness of the class identifier
   if ( (pState[0]->getClassId() != ID_DUMMYCONFIGURABLEFSMSTATE) )
	{	setTestResult(TEST_FAILURE,
        "Wrong class identifier for the dummy configurable FsmState class");
	   return;
	}

   // Activate FSM twice and check that state 0 is executed
   pFsm->activate();
   pFsm->activate();
   if ( pState[0]->getActivationCounter() != 2 )
	{	setTestResult(TEST_FAILURE,
             "Wrong value of activation counter for state 0");
		return;
	}

   // Verify value of initialization counter
   if ( pState[0]->getInitializationCounter() != 1 )
	{	setTestResult(TEST_FAILURE,
             "Wrong value of initialization counter for state 0");
		return;
	}

   // Force and check state transition to state 1
   pState[0]->setTerminationCheckValue(true);
   pFsm->activate();
   if ( pFsm->getCurrentState() != 1)
	{	setTestResult(TEST_FAILURE,
             "State transition to state 1 failed to take place");
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

   // Check exit, initialization and activation counters
   if ( pState[0]->getExitCounter() != 1 )
	{	setTestResult(TEST_FAILURE,
             "Wrong value of exit counter for state 0");
		return;
	}
   if ( pState[1]->getInitializationCounter() != 1 )
	{	setTestResult(TEST_FAILURE,
             "Wrong value of initialization counter for state 1");
		return;
	}
   if ( pState[1]->getActivationCounter() != 1 )
	{	setTestResult(TEST_FAILURE,
             "Wrong value of activation counter for state 1");
		return;
	}

   // Disable autonomous transition by disabling exit check and verify that
   // no transition takes place
   pState[1]->setExitCheckValue(false);
   pState[1]->setTerminationCheckValue(true);
   pFsm->activate();
   if ( pFsm->getCurrentState() != 1)
	{	setTestResult(TEST_FAILURE,
             "Illegal state transition out of state 1 took place");
		return;
	}

   // Check that the correct event was created
   pRep = CC_RootObject::getEventRepository();
   pRep->latest();
   if ( pRep->getEventType() != EVT_FSM_EXIT_FAILED )
	{	setTestResult(TEST_FAILURE,
             "Wrong event after failure of exit check");
		return;
	}

    // Check that the last FSM activation caused the execution of state 1
   if ( pState[1]->getActivationCounter() != 2 )
	{	setTestResult(TEST_FAILURE,
             "Wrong value of activation counter for state 1");
		return;
	}

   // Disable autonomous transition by disabling entry check and verify that
   // no transition takes place
   pState[1]->setExitCheckValue(true);
   pState[2]->setInitializationCheckValue(false);
   pFsm->activate();
   if ( pFsm->getCurrentState() != 1)
	{	setTestResult(TEST_FAILURE,
             "Illegal state transition out of state 1 took place");
		return;
	}

   // Check that the correct event was created
   pRep = CC_RootObject::getEventRepository();
   pRep->latest();
   if ( pRep->getEventType() != EVT_FSM_ENTRY_FAILED )
	{	setTestResult(TEST_FAILURE,
             "Wrong event after failure of exit check");
		return;
	}

   // Disable autonomous transitions by disabling FSM transitions into state 2
   // and verify that no transition takes place
   pState[2]->setInitializationCheckValue(true);
   pFsm->setTransitionEnableStatus(2, DISABLED);
   pFsm->activate();
   if ( pFsm->getCurrentState() != 1)
	{	setTestResult(TEST_FAILURE,
             "Illegal state transition out of state 1 took place");
		return;
	}

   // Check that the correct event was created
   pRep = CC_RootObject::getEventRepository();
   pRep->latest();
   if ( pRep->getEventType() != EVT_FSM_TRANSITION_DISABLED )
	{	setTestResult(TEST_FAILURE,
             "Wrong event after failure of exit check");
		return;
	}

   // Disable autonomous transitions by disabling all FSM transitions
   // and verify that no transition takes place
   pFsm->setTransitionEnableStatus(2, ENABLED);
   pFsm->setTransitionEnableStatus(DISABLED);
   pFsm->activate();
   if ( pFsm->getCurrentState() != 1)
	{	setTestResult(TEST_FAILURE,
             "Illegal state transition out of state 1 took place");
		return;
	}

   // Check that the correct event was created
   pRep = CC_RootObject::getEventRepository();
   pRep->latest();
   if ( pRep->getEventType() != EVT_FSM_ALL_TRANSITION_DISABLED )
	{	setTestResult(TEST_FAILURE,
             "Wrong event after failure of exit check");
		return;
	}

   // Enable autonomous transitions and verify that transition takes place
   pFsm->setTransitionEnableStatus(ENABLED);
   pFsm->activate();
   if ( pFsm->getCurrentState() != 2)
	{	setTestResult(TEST_FAILURE,
             "State transition to state 2 failed to take place");
		return;
	}

   // Check exit, initialization and activation counters
   if ( pState[1]->getExitCounter() != 1 )
	{	setTestResult(TEST_FAILURE,
             "Wrong value of exit counter for state 1");
		return;
	}
   if ( pState[2]->getInitializationCounter() != 1 )
	{	setTestResult(TEST_FAILURE,
             "Wrong value of initialization counter for state 2");
		return;
	}
   if ( pState[2]->getActivationCounter() != 1 )
	{	setTestResult(TEST_FAILURE,
             "Wrong value of activation counter for state 2");
		return;
	}

    // Attempt to commands transition into non-existent state
    if (isNonNominalCheckAllowed()) {
        pFsm->makeTransitionRequest(4);
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
