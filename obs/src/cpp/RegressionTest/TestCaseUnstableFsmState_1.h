//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseUnstableFsmState_1.h
//
// Version	1.0
// Date		15.07.03 (Version 1.0)
// Author	R. Totaro

#ifndef TestCaseUnstableFsmState_1H
#define TestCaseUnstableFsmState_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the services of an unstable FSM state. One
 * <code>DC_UnstableFsmState</code> object is created and the following
 * tests are performed upon it: <ol>
 * <li>It is verified that the object under test returns the correct class id.</li>
 * <li>It is verified that <code>isFinished()</code> returns <code>true</code>.</li>
 * <li>A dummy call to <code>doContinue</code> is performed (this is necessary for
 * test coverage reasons).</li>
 * </ol>
 * @see DC_UnstableFsmState
 * @see FsmState
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseUnstableFsmState_1 : public TestCaseGenericSetUp {
public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_UNSTABLEFSMSTATE*10+1 and "TestCaseUnstableFsmState_1".
	 */
	TestCaseUnstableFsmState_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};
#endif
