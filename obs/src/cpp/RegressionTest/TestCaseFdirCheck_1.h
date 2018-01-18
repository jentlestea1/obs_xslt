//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseFdirCheck_1.h
//
// Version	1.0
// Date		26.06.03 (Version 1.0)
// Author	R. Totaro

#ifndef TestCaseFdirCheck_1H
#define TestCaseFdirCheck_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the services of the <code>DC_FdirCheck</code> object. One object
 * (<code>pFDIR</code>) is created and the following tests are performed upon it:<ol>
 * <li>The correctness of both class ids is verified.</li>
 * <li>It is verified that a newly created object is not configured.</li>
 * <li>A previously created <code>DC_DummyRecoveryAction</code> (<code>pFDI</code>) is
 * attached to the object as its FDI check. It is verified that the pointer
 * is correctly set and that the object is not yet configured.</li>
 * <li>A previously created <code>DC_DummyRecoveryAction</code> (<code>pDRA</code>) is
 * attached to the object as its recovery action. It is verified that the
 * pointer is correctly set and that the object is configured.</li>
 * <li>The outcome of the FDI check is set to <code>ACTION_CANNOT_EXECUTE</code>,
 * <code>pFDIR->execute()</code> is invoked and it is verified that its return code
 * is <code>ACTION_CANNOT_EXECUTE</code>.</li>
 * <li>Now the FDI check outcome is set to <code>ACTION_FAILURE</code> and the recovery
 * action's to <code>ACTION_CANNOT_EXECUTE</code>. It is tested that
 * <code>pFDIR->execute()</code> invokes the recovery action's <code>execute()</code>
 * method by verifying that its return code is indeed <code>ACTION_CANNOT_EXECUTE</code>.</li>
 * </ol>
 * @see DC_FdirCheck
 * @see DC_DummyRecoveryAction
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseFdirCheck_1 : public TestCaseGenericSetUp {
public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_FDIRCHECK*10+1 and "TestCaseFdirCheck_1".
	 */
	TestCaseFdirCheck_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};
#endif
