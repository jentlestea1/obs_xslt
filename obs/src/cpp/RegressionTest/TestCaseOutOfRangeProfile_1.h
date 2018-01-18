//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseOutOfRangeProfile_1.h
//
// Version	1.0
// Date		16.01.03
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseOutOfRangeProfile_1H
#define TestCaseOutOfRangeProfile_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Check the functionalities implemented by class
 * <code>DC_OutOfRangeProfile</code>.
 * One instance of this class is created and
 * the following specific tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The monitoring profile is configured, a test value
 * lying within the range is passed through the monitoring profile
 * and it is verified that the monitoring
 * check service reports "no deviation from profile detected".</li>
 * <li>A test value lying outside the range is passed through
 * the monitoring profile and it is verified that the monitoring
 * check service reports "deviation from profile detected".</li>
 * </ol>
 * @see DC_OutOfRangeProfile
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseOutOfRangeProfile_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_OUTOFRANGEPROFILE*10+1 and "TestCaseOutOfRangeProfile_1".
      */
     TestCaseOutOfRangeProfile_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
     virtual void runTestCase(void);
};

#endif
