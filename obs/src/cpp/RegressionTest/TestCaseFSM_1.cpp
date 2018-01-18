//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseFSM_1.cpp
//
// Version	1.0
// Date		04.10.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../FSM/CC_FSM.h"
#include "../FSM/DC_DummyFsmState.h"
#include "../Utilities/TestCaseWithEvtCheck.h"
#include "TestCaseFSM_1.h"

TestCaseFSM_1::TestCaseFSM_1(void) :
	TestCaseWithEvtCheck(ID_FSM*10+1,"TestCaseFSM_1") {
		return;
}

void TestCaseFSM_1::runTestCase(void) {

   CC_FSM* pFsm = new CC_FSM();
   unsigned int nEvt = getNumberOfEvents();

   // Check the correctness of the class identifier
   if ( (pFsm->getClassId() != ID_FSM) )
	{	setTestResult(TEST_FAILURE,"Wrong class identifier for the FSM class");
	   return;
	}

   // FSM should not be configured upon creation
   if ( (pFsm->isObjectConfigured() == CONFIGURED) )
	{	setTestResult(TEST_FAILURE,"Wrong event repository configuration status upon repository creation");
		return;
	}

   // Set the number of states and check correctness
   pFsm->setNumberOfStates(4);
   if ( (pFsm->getNumberOfStates() != 4 ) )
	{	setTestResult(TEST_FAILURE,"Wrong number of FSM states");
		return;
	}

   // Load dummy FsmStates and check that the load operation is correctly executed
   DC_DummyFsmState* pState[4];
   for (TD_FsmStateIndex i=0; i<pFsm->getNumberOfStates(); i++)
      pState[i] = new DC_DummyFsmState();
   for (TD_FsmStateIndex i=0; i<pFsm->getNumberOfStates(); i++)
      pFsm->setState(i,pState[i]);
   for (TD_FsmStateIndex i=0; i<pFsm->getNumberOfStates(); i++)
      if (pFsm->getState(i) != pState[i])
   	  {	setTestResult(TEST_FAILURE,"Wrong loaded state is reported");
	   	return;
	  }

   // Attempt non-nominal state load
   if (isNonNominalCheckAllowed()) {
      pFsm->setState(5,pState[0]);
      if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_FS) )
      	return;
   }

   // Reset the FSM
   pFsm->reset();

   // Check correctness of default state
   if ( pFsm->getCurrentState() != 0)
	{	setTestResult(TEST_FAILURE,
             "Wrong default state");
		return;
	}

   // Check that all state transitions are enabled
   for (TD_FsmStateIndex i=0; i<pFsm->getNumberOfStates(); i++)
      if ( !pFsm->isTransitionEnabled(i) )
   	  {	setTestResult(TEST_FAILURE,
             "All state transitions should be enabled");
	   	return;
	   }

   // Unload one state and check that the object is not configured
   if (isNonNominalCheckAllowed()) {
        pFsm->setState(0,pNULL);
        if ( (pFsm->isObjectConfigured() == CONFIGURED) )
	    {	setTestResult(TEST_FAILURE,
             "Wrong FSM configuration status");
		    return;
        }
   }

   // Reload state and check that FSM object is configured
    pFsm->setState(0,pState[0]);
    if ( (pFsm->isObjectConfigured() == NOT_CONFIGURED) )
	{	setTestResult(TEST_FAILURE,
             "Wrong FSM configuration status after configuration was completed");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
