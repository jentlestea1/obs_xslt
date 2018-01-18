//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseRecoveryAction_1.h
//
// Version	1.0
// Date		25.06.03 (Version 1.0)
// Author	R. Totaro

#ifndef TestCaseRecoveryAction_1H
#define TestCaseRecoveryAction_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the services of recovery actions. One <code>DC_NullRecoveryAction</code> object
 * (from now on referred to as "pNRA") and one <code>DC_DummyRecoveryAction</code>
 * object (from now on referred to as "pDRA") are created and the following
 * tests are performed upon them:<ol>
 * <li>The correctness of both class ids is verified.</li>
 * <li>It is verified that <code>pDRA->getNextRecoveryAction()</code>
 * returns <code>NULL</code>.</li>
 * <li>It is verified that a call to <code>pDRA->execute()</code> returns
 * <code>ACTION_SUCCESS</code>.</li>
 * <li><code>pDRA</code>'s execution flag is set to <code>false</code> and
 * <code>pDRA->execute()</code> is invoked. It is verified that it returns
 * <code>ACTION_CANNOT_EXECUTE</code>.</li>
 * <li>It is verified that <code>pNRA->execute()</code> returns
 * <code>ACTION_SUCCESS</code>.</li>
 * <li><code>pDRA</code> is set as <code>pNRA</code>'s "next recovery action". It is
 * verified that <code>NRA->getNextRecoveryAction()</code> returns the correct value.</li>
 * <li>The action outcome of <code>pDRA</code> is set to <code>ACTION_FAILURE</code> and its
 * execution flag to <code>true</code>. It is verified that <code>pNRA->execute()</code>
 * returns <code>ACTION_FAILURE</code>.</li>
 * </ol>
 * @see RecoveryAction
 * @see DC_NullRecoveryAction
 * @see DC_DummyRecoveryAction
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseRecoveryAction_1 : public TestCaseGenericSetUp {
public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_DUMMYRECOVERYACTION*10+1 and "TestCaseRecoveryAction_1".
	 */
	TestCaseRecoveryAction_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};
#endif
