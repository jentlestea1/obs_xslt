//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseNestedFsmActivator_1.h
//
// Version	1.0
// Date		24.06.03 (Version 1.0)
// Author	R. Totaro

#ifndef TestCaseNestedFsmActivator_1H
#define TestCaseNestedFsmActivator_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the services of conditional punctual actions. One
 * <code>DC_NestedFsmActivator</code> object is created and the following
 * procedure is performed upon it: <ol>
 * <li>A FSM, its states and a corresponding number of events are created. The
 * FSM and the events are configured and initialized. These objects will be
 * used to test the <code>DC_NestedFsmActivator</code> implementation.</li>
 * <li>It is verified that the object under test returns the correct class id.</li>
 * <li>It is verified that a newly created object is not configured.</li>
 * <li>The previously created <code>CC_FSM</code> is attached to the object. It is
 * verified that <code>getTargetFsm()</code> returns the right value and that the
 * object is configured.</li>
 * <li>The FSM is advanced to a non-zero state and <code>doInit()</code> is invoked.
 * It is verified that the nested FSM is reset and brought back to the initial state.</li>
 * <li>An event is raised and <code>doContinue()</code> is called. It is verified that
 * the nested FSm performs a transition to the target state of the event previously raised.</li>
 * </ol>
 * @see DC_NestedFsmActivator
 * @see CC_FSM
 * @see FsmState
 * @see DC_DummyFsmState
 * @see DC_FsmEvent
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseNestedFsmActivator_1 : public TestCaseGenericSetUp {
public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_NESTEDFSMACTIVATOR*10+1 and "TestCaseNestedFsmActivator_1".
	 */
	TestCaseNestedFsmActivator_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};
#endif
