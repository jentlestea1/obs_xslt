//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyPunctualAction_1.h
//
// Version	1.3
// Date		01.10.02 (Version 1.0)
//          24.02.03 (Version 1.1)
//          03.06.03 (Version 1.2)
//          30.09.03 (Version 1.3)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: update of comments
//   Version 1.2: added tests of getLastOutcome() & resetLastOutcome() methods
//   Version 1.2: the base class is now TestCaseWithEvtCheck

#ifndef TestCaseDummyPunctualAction_1H
#define TestCaseDummyPunctualAction_1H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Verify the enable service and the event registration service
 * of punctual actions.
 * One <code>DC_DummyPunctualAction</code> is created and the following tests
 * are performed upon it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the punctual action is enabled at creation.</li>
 * <li>It is verified that <code>getLastOutcome</code> returns <code>ACTION_RESET</code>.</li>
 * <li>An <code>execute</code> request is made on the punctual action and it is verified
 * that the punctual action returns a "action successful" outcome and
 * that an event recording the correct execution status is created.</li>
 * <li>The punctual action is disabled and it is verified that the disabled
 * status is correctly reported by the punctual action.</li>
 * <li>An <code>execute</code> request is made on the disabled punctual action
 * and it is verified that an event recording the correct execution status is created.</li>
 * <li>It is verified that <code>getLastOutcome</code> correctly reports the latest event.</li>
 * <li><code>resetLastOutcome</code> is invoked and it is verified that
 * <code>getLastOutcome</code> returns <code>ACTION_RESET</code>.</li>
 * </ol>
 * @see DC_DummyPunctualAction
 * @see PunctualAction
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.3
 */
class TestCaseDummyPunctualAction_1 : public TestCaseWithEvtCheck {
public :
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_DUMMYPUNCTUALACTION*10+1 and "TestCaseDummyPunctualAction_1".
	 */
    TestCaseDummyPunctualAction_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};

#endif
