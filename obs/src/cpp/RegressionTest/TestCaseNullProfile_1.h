//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseNullProfile_1.h
//
// Version	1.0
// Date		01.10.03
// Author	R. Totaro

#ifndef TestCaseNullProfile_1H
#define TestCaseNullProfile_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Check the functionalities implemented by <code>DC_NullProfile</code>.
 * One instance of this class is created and
 * the following specific tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The <code>deviatesFromProfile()</code> method (both the <code>TD_Float</code>
 * and the <code>TD_Integer</code> implementation) is invoked with 100 
 * different values and it is verified that it alwayas returns false.</li>
 * <li>A call to <code>reset</code> is performed. This is a dummy check that required to have full statement
 * coverage of the super class.<li>
 * </ol>
 * @see MonitoringProfile
 * @see DC_NullProfile
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseNullProfile_1 : public TestCaseGenericSetUp {
public:
    /**
     * Set the identifier and the name of the test case to, respectively,
     * ID_NULLPROFILE*10+1 and "TestCaseNullProfile_1".
     */
    TestCaseNullProfile_1(void);

    /**
     * Execute the test case. See class comment for details.
     */
    virtual void runTestCase(void);
};

#endif
