//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseFSM_3.h
//
// Version	1.0
// Date		04.10.02
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseFSM_3H
#define TestCaseFSM_3H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the state activation and autonomous transition operations of an FSM.
 * One FSM instance
 * is created and configured with 4 <code>DummyConfigurableFsmStates</code>
 * (states 0 to 3). State i is configured to have state i+1 (modulus 4) as its
 * next state.
 * The following tests are then performed: <ol>
 * <li>The correctness of the <code>DummyConfigurableFsmStates</code>
 * class identifier is verified.</li>
 * <li>The FSM is activated twice and it is verified that this is reflected
 * in the value of the activation counter of its state 0.</li>
 * <li>It is verified that the initialization counter of state 0 is equal to 1.</li>
 * <li>The termination check of state 0 is loaded with <code>true</code>, the
 * FSM is activated and it is verified that an autonomous state transition to
 * state 1 takes place.</li>
 * <li>It is checked that the correct event is created to record the
 * occurrence of the state transition.</li>
 * <li>It is checked that the exit counter of state 0 and the initialization
 * counter of state 1 are equal to 1.</li>
 * <li>The exit check of state 1 is loaded with <code>false</code>, and its
 * termination check is loaded with <code>true</code>, the FSM is activated
 * and it is checked that no transition takes place.</li>
 * <li>It is checked that the correct event to record the failure of the exit
 * check from state 1 was generated.</li>
 * <li>It is checked that the activation counter of state 1 has been
 * incremented by 1.</li>
 * <li>The initialization check of state 2 is loaded with <code>false</code>,
 * the exit check of state 1 is loaded with <code>true</code>, the FSM is
 * activated once, and it is checked that no state transition takes place.</li>
 * <li>It is checked that the correct event to record the failure of the initialization
 * check for state 2 was generated.</li>
 * <li>The initialization check of state 2 is loaded with <code>true</code>,
 * FSM transitions into state 2 are disabled, the FSM is
 * activated once, and it is checked that no state transition takes place.</li>
 * <li>It is checked that the correct event to record the failure of the
 * transition due to FSM transitions into state 2 being disabled was generated.</li>
 * <li>The FSM transitions into state 2 are enabled, all FSM state transitions
 * are disabled, the FSM is activated once, and it is checked that no state
 * transition takes place.</li>
 * <li>It is checked that the correct event to record the failure of the
 * transition due to all FSM transitions being disabled was generated.</li>
 * <li>The FSM transitions are enabled, the FSM is activated once, and it is
 * checked that a state transition to state 2
 * takes place.</li>
 * <li>It is checked that the exit counter of state 1, the initialization
 * counter of state 2, and the activation counter of state 2 are equal to 1.</li>
 * <li>Non-nominal behaviour check: an attempt is made to make a transition request
 * to a non-existent state and it is
 * checked that the correct event is generated. </li>
 * </ol>
 * @see DC_FsmEvent
 * @see DC_DummyConfigurableFsmState
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseFSM_3 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_FSM*10+3 and "TestCaseFSM_3".
      */
     TestCaseFSM_3(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
