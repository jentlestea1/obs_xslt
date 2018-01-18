//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDataPoolMonitor_1.h
//
// Version	1.0
// Date		30.10.03 (Version 1.0)
// Author	R. Totaro
//
// Change Record:

#ifndef TestCaseDataPoolMonitor_1H
#define TestCaseDataPoolMonitor_1H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Verify the services provided by the <code>DC_DataPoolMonitor</code> class.
 * A <code>DC_SampleFullDataPool</code> is created and configured with
 * a <code>DC_NullRecoveryAction</code> and a <code>DC_OutOfRangeProfile</code>
 * for each of the values it contains. The data pool is then linked to the
 * <code>CC_RootObject</code>. A <code>DC_DataPoolMonitor</code> object
 * is then created and the following tests are performed upon it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The <code>execute()</code> method is called and it is verified that the
 * validity status of the data items is left unchanged and no recovery action
 * was invoked.</li>
 * <li>The values in the data pool are set outside the range defined by the
 * monitoring profiles and <code>DC_DataPoolMonitor::execute()</code> is
 * invoked once again. It is then checked that the validity status of all the
 * values in the data pool is set to <code>NOT_VALID</code> and that the
 * recovery actions were invoked.</li>
 * </ol>
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseDataPoolMonitor_1 : public TestCaseWithEvtCheck {
public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_DATAPOOLMONITOR*10+1 and "TestCaseDataPoolMonitor_1".
	 */
    TestCaseDataPoolMonitor_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};
#endif
