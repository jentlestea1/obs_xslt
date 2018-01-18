//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseFSM_2.h
//
// Version	1.0
// Date		04.10.02
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseFSM_2H
#define TestCaseFSM_2H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the basic state transition operations of an FSM. One FSM instance
 * is created and configured with 4 dummy FsmStates (states 0 to 3). Three
 * FsmEvents are created and configured to be associated to the FSM and to
 * trigger transitions to, respectively, states 1, 2 and 0.
 * The following tests are then performed: <ol>
 * <li>It is verified
 * that the object configuration service on the FSM
 * reports "object configured".</li>
 * <li>The first FsmEvent is fired and it is verified that the FSM makes
 * a transition to state 1. It is also verified that the transition is only
 * made after the FSM has been activated.</li>
 * <li>It is checked that the correct event is created to record the
 * occurrence of the state transition.</li>
 * <li>The FSM is activated twice and it is verified that no state transitions
 * take place.</li>
 * <li>The second and third FsmEvents are fired in sequence and it is verified
 * that only the second firing has effect.</li>
 * <li>Transitions into state 2 are disabled and then the second FsmEvent is
 * fired and it is verified that this has no effect.</li>
 * <li>It is checked that the correct event is created to record the
 * failure of a state transition to occur due to the transition being
 * disabled.</li>
 * <li>Non-nominal behaviour check: an attempt is made to disable a transition
 * into a non-existent state and it is
 * checked that the correct event is generated. </li>
 * </ol>
 * @see CC_FSM
 * @see DC_FsmEvent
 * @see DC_DummyFsmState
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseFSM_2 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_FSM*10+2 and "TestCaseFSM_2".
      */
     TestCaseFSM_2(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
