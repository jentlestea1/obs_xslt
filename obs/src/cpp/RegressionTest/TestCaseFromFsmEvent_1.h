//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseFromFsmEvent_1.h
//
// Version	1.0
// Date		04.10.02
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseFromFsmEvent_1H
#define TestCaseFromFsmEvent_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the functionalities offered by the <code>DC_FromFsmEvent</code>
 * class. One FSM instance
 * is created and configured with 4 dummy FsmStates (states 0 to 3). One
 * <code>FromFsmEvents</code> is then instantiated and the following
 * specific tests are then performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified
 * that the object configuration service on the <code>FromFsmEvents</code>
 * reports "object not configured".</li>
 * <li>The <code>FromFsmEvents</code> is configured with a target
 * FSM, a starting and target state and it is verified that the configuration
 * operation on the class-specific part of the object (the definition of
 * the starting state) is correctly executed.</li>
 * <li>It is verified
 * that the object configuration service on the <code>FromFsmEvents</code>
 * reports "object configured".</li>
 * <li>The FSM is placed in a state different from the starting state
 * of the <code>FromFsmEvents</code>, the latter is fired and it is verified
 * that the state of the FSM has not changed.</li>
 * <li>The FSM is placed in a state equal to the starting state
 * of the <code>FromFsmEvents</code>, the latter is fired and it is verified
 * that the FSM performs a transition to the target state of the
 * <code>FromFsmEvents</code>.</li>
 * </ol>
 * @see CC_FSM
 * @see DC_FromFsmEvent
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseFromFsmEvent_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_FROMFSMSTATE*10+1 and "TestCaseFromFsmEvent_1".
      */
     TestCaseFromFsmEvent_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
