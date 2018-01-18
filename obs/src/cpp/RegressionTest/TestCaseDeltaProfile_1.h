//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseStuckDeltaProfile_1.h
//
// Version	1.0
// Date		11.01.03
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseStuckDeltaProfile_1H
#define TestCaseStuckDeltaProfile_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Check the functionality of the <code>DeltaProfile</code> class.
 * One instance of the class is created and
 * the following specific tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the configuration check service of the
 * simple change profile initially reports "not configured".</li>
 * <li>A delta threshold is loaded in the profile component
 * and it is verified that the load operation is correctly performed.</li>
 * <li>It is verified that the configuration check service of the
 * profile component reports "configured".</li>
 * <li>A sequence of test values of double type that should not
 * trigger the profile are
 * passed through its monitoring check service it is verified that the
 * check service reports "no deviation from profile detected".</li>
 * <li>A sequence of test values of double type that should trigger
 * the monitoring
 * check are passed through the profile component and it is verified that
 * the check service reports "deviation from profile detected".</li>
 * <li>A reset operation is performed and it is verified that
 * this interrupts the execution of the monitoring check.</li>
 * <li>A sequence of test values of integer type that should not
 * trigger the profile are
 * passed through its monitoring check service it is verified that the
 * check service reports "no deviation from profile detected".</li>
 * <li>A sequence of test values of integer type that should trigger
 * the monitoring
 * check are passed through the profile component and it is verified that
 * the check service reports "deviation from profile detected".</li>
 * </ol>
 * @see DC_DeltaProfile
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseDeltaProfile_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_DELTAPROFILE*10+1 and "TestCaseStuckDeltaProfile_1".
      */
     TestCaseDeltaProfile_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
     virtual void runTestCase(void);
};

#endif
