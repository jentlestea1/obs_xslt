//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseForbiddenValueProfile_1.h
//
// Version	1.0
// Date		11.01.03
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseForbiddenValueProfile_1H
#define TestCaseForbiddenValueProfile_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Check the functionality of the <code>DC_ForbiddenValueProfile</code>
 * class. One instance of the class is created and
 * the following specific tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>A forbidden value is loaded in the monitoring profile
 * and it is verified that the load operation is correctly performed.</li>
 * <li>A test value different from the forbidden value is passed through
 * the monitoring profile and it is verified that the monitoring
 * check service reports "no deviation from profile detected".</li>
 * <li>A test value equal to the forbidden value is passed through
 * the monitoring profile and it is verified that the monitoring
 * check service reports "deviation from profile detected".</li>
 * <li>The monitoring profile is disabled and the test value is again passed through
 * the monitoring profile. It is checked that the monitoring
 * check service reports "no deviation from profile detected".</li>
 * <li>Non-nominal behaviour check: it is checked that the monitoring check with a real-valued argument
 * reports "deviation from profile detected".</li>
 * </ol>
 * @see DC_ForbiddenValueProfile
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseForbiddenValueProfile_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_FORBIDDENVALUEPROFILE*10+1 and "TestCaseForbiddenValueProfile_1".
      */
     TestCaseForbiddenValueProfile_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
     virtual void runTestCase(void);
};

#endif
