//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseNestedFsmActivatorWithEndState_1.h
//
// Version	1.0
// Date		24.06.03 (Version 1.0)
// Author	R. Totaro

#ifndef TestCaseNestedFsmActivatorWithEndState_1H
#define TestCaseNestedFsmActivatorWithEndState_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the services of nested FSM states. One
 * <code>DC_NestedFsmActivatorWithEndState</code> object is created and the following
 * procedure is performed upon it: <ol>
 * <li>A FSM, its states and a corresponding number of events are created. The
 * FSM and the events are configured and initialized. These objects will be
 * used to test the <code>DC_NestedFsmActivatorWithEndState</code> implementation.</li>
 * <li>It is verified that the object under test returns the correct class id.</li>
 * <li>It is verified that a newly created object is not configured.</li>
 * <li>The previously created <code>CC_FSM</code> is attached to the object. It is
 * verified that the object is not yet configured.</li>
 * <li>The target state is set by calling <code>setTargetState()</code>. It is verified
 * that <code>getTargetState()</code> returns the proper value and that the object is
 * conofigured.</li>
 * <li>The FSM is advanced through all its states and it is verified that
 * <code>isFinished()</code> returns true only when the FSM state is equal to the
 * target state.</li>
 * </ol>
 * @see DC_NestedFsmActivatorWithEndState
 * @see CC_FSM
 * @see FsmState
 * @see DC_DummyFsmState
 * @see DC_FsmEvent
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseNestedFsmActivatorWithEndState_1 : public TestCaseGenericSetUp {
public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_NESTEDFSMACTIVATORWITHENDSTATE*10+1 and "TestCaseNestedFsmActivatorWithEndState_1".
	 */
	TestCaseNestedFsmActivatorWithEndState_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};
#endif
