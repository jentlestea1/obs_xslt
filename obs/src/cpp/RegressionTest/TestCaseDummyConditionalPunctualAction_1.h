//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyConditionalPunctualAction_1.h
//
// Version	1.0
// Date		04.06.03 (Version 1.0)
// Author	R. Totaro

#ifndef TestCaseDummyConditionalPunctualAction_1H
#define TestCaseDummyConditionalPunctualAction_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the services of conditional punctual actions. One
 * <code>DC_DummyConditionalPunctualAction</code> object is created and the following
 * tests are performed upon it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The execution flag is set to <code>false</code> and an <code>execute</code> request
 * is made on the conditional punctual action. It is verified that the outcome is
 * <code>ACTION_CANNOT_EXECUTE</code>.</li>
 * <li>The execution flag is set to <code>true</code> and an <code>execute</code> request
 * is made on the conditional punctual action. It is verified that the outcome is
 * <code>ACTION_SUCCESS</code>.</li>
 * </ol>
 * @see DC_DummyConditionalPunctualAction
 * @see ConditionalPunctualAction
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseDummyConditionalPunctualAction_1 : public TestCaseGenericSetUp {
public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_DUMMYCONDITIONALPUNCTUALACTION*10+1 and "TestCaseDummyConditionalPunctualAction_1".
	 */
	TestCaseDummyConditionalPunctualAction_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};
#endif
