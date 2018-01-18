//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseControlAction_1.h
//
// Version	1.0
// Date		28.07.03 (Version 1.0)
// Author	A. Pasetti

#ifndef TestCaseControlAction_1H
#define TestCaseControlAction_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Check the services offered by control actions. One
 * <code>DC_ControlAction</code> component is created and the following
 * tests are performed upon it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is checked that the configuration check service initially
 * reports: "not configured".</li>
 * <li>A control block is loaded and it is verified that the load operations
 * was successful. The control block that is loaded is an instance of
 * <code>DC_DummyControlBlock</code>.</li>
 * <li>It is checked that the configuration check service now
 * reports: "configured".</li>
 * <li>An execution request is sent to the control action and it is verified
 * that the control block is propagated.</li>
 * <li>A reset request is sent to the control action and it is verified
 * that the control block is reset.</li>
 * </ol>
 * @see DC_ControlAction
 * @see DC_DummyControlBlock
 * @author A. Pasetti
 * @version 1.0
 */
class TestCaseControlAction_1 : public TestCaseGenericSetUp {
public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_CONTROLACTION*10+1 and "TestCaseControlAction_1".
	 */
	TestCaseControlAction_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};
#endif
