//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyConfigurableManoeuvre_1.h
//
// Version	1.0
// Date		12.04.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseDummyConfigurableManoeuvre_1H
#define TestCaseDummyConfigurableManoeuvre_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the services implemented by the
 * <code>DC_DummyConfigurableManoeuvre</code>. One instance
 * of this class is created and the following tests are performed
 * upon it: <ol>
 * <li>The correctness of the class identified is verified.</li>
 * <li>It is verified that the action counters are equal to zero at
 * creation.</li>
 * <li>The manoeuvre is put in use it is verified that its
 * start check returns "manoeuvre cannot start".</li>
 * <li>The initialization action is performed and it is verified that
 * the initialization action counter is incremented by one.</li>
 * <li>The continuation action is performed and it is verified that
 * the continuation action counter is incremented by one.</li>
 * <li>It is verified that the continuaion check returns "manoeuvre
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
 * @see DC_DummyConfigurableManoeuvre
 * @see Manoeuvre
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseDummyConfigurableManoeuvre_1 : public TestCaseGenericSetUp
{
public :
    /**
     * Set the identifier and the name of the test case to, respectively,
     * ID_DUMMYCONFIGURABLEMANOEUVRE*10+1 and "TestCaseDummyConfigurableManoeuvre_1".
     */
	TestCaseDummyConfigurableManoeuvre_1(void);

    /**
     * Execute the test case. See class comment for details.
     */
	virtual void runTestCase(void);
};

#endif
