//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseTestPUSConfigurableManoeuvre_1.h
//
// Version	1.0
// Date		12.02.04 (Version 1.0)
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseTestPUSConfigurableManoeuvre_1H
#define TestCaseTestPUSConfigurableManoeuvre_1H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Verify the services implemented by the
 * <code>DC_TestPUSConfigurableManoeuvre</code>. One instance
 * of this class is created and the following tests are performed
 * upon it: <ol>
 * <li>The correctness of the class identified is verified.</li>
 * <li>It is verified that the action counters are equal to zero at
 * creation.</li>
 * <li>The default values of the start, completion and progress acknowledge flags 
 * verified.</li>
 * <li>The values of the start, completion and progress acknowledge flags 
 * are updated and it is verified that the update operation is successful.</li>
 * <li>The value of the telecommand identifier is set and read back and it is
 * verified that the read-back value is correct.</li>
 * <li>The manoeuvre is put in use it is verified that its
 * start check returns "manoeuvre cannot start".</li>
 * <li>The initialization action is performed and it is verified that
 * the initialization action counter is incremented by one and that the
 * correct event is generated.</li>
 * <li>The continuation action is performed and it is verified that
 * the continuation action counter is incremented by one.</li>
 * <li>It is verified that the continuation check returns "manoeuvre
 * cannot continue".</li>
 * <li>It is verified that the termination check returns "manoeuvre
 * cannot terminate".</li>
 * <li>The termination action is executed and it is verfied that the
 * termination action counter is incremented by one.</li>
 * <li>The configurable return values of the manoeuvre checks are
 * inverted through method <code>setCheckStatus</code>. A complete
 * execution cycle for the manoeuvre is executed again (initialization,
 * one continuation action, termination) and it is verified that the
 * return values of the manoeuvre checks reflect the new settings.</li>
 * </ol>
 * @see DC_TestPUSConfigurableManoeuvre
 * @see Manoeuvre
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseTestPUSConfigurableManoeuvre_1 : public TestCaseWithEvtCheck {

  public :
    /**
     * Set the identifier and the name of the test case to, respectively,
     * ID_TESTPUSCONFIGURABLEMANOEUVRE*10+1 and "TestCaseTestPUSConfigurableManoeuvre_1".
     */
	TestCaseTestPUSConfigurableManoeuvre_1(void);

    /**
     * Execute the test case. See class comment for details.
     */
	virtual void runTestCase(void);
};

#endif
