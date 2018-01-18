//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseInRangeProfile_1.h
//
// Version	1.0
// Date		16.01.03
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseInRangeProfile_1H
#define TestCaseInRangeProfile_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Check the functionalities implemented by the abstract class
 * <code>RangeProfile</code>. The checks are performed on the concrete
 * class <code>DC_InRangeProfile</code>. The specific functionalities
 * implemented by class <code>DC_InRangeProfile</code> are also checked.
 * One instance of this class is created and
 * the following specific tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the configuration check service of the
 * in range profile initially reports "not configured".</li>
 * <li>A lower bound value is loaded in the monitoring profile
 * and it is verified that the load operation is correctly performed.</li>
 * <li>An upper bound value is loaded in the monitoring profile
 * and it is verified that the load operation is correctly performed.</li>
 * <li>It is verified that the configuration check service of the
 * in range profile now reports "configured".</li>
 * <li>A test value of type <code>double</code> lying outside the
 * range is passed through
 * the monitoring profile and it is verified that the monitoring
 * check service reports "no deviation from profile detected".</li>
 * <li>A test value type <code>double</code> lying within the
 * range is passed through
 * the monitoring profile and it is verified that the monitoring
 * check service reports "deviation from profile detected".</li>
 * <li>The monitoring profile is disabled and the same test valued
 * is again passed through the profile. It is checked that the monitoring
 * check service now reports "no deviation from profile detected".</li>
 * <li>The monitoring profile is enabled. A test value of type <code>int</code> lying outside the
 * range is passed through
 * the monitoring profile and it is verified that the monitoring
 * check service reports "no deviation from profile detected".</li>
 * <li>A test value type <code>int</code> lying within the
 * range is passed through
 * the monitoring profile and it is verified that the monitoring
 * check service reports "deviation from profile detected".</li>
 * </ol>
 * @see RangeProfile
 * @see DC_InRangeProfile
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseInRangeProfile_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_INRANGEPROFILE*10+1 and "TestCaseInRangeProfile_1".
      */
     TestCaseInRangeProfile_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
     virtual void runTestCase(void);
};

#endif
