//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseSimpleChangeProfile_1.h
//
// Version	1.0
// Date		11.01.03
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseSimpleChangeProfile_1H
#define TestCaseSimpleChangeProfile_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Check the functionality of the <code>MonitoringProfile</code>
 * abstract class as they are implemented in the
 * <code>SimpleChangeProfile</code> concrete class. Additionally, the
 * specific functionalities of the <code>SimpleChangeProfile</code>
 * are also checked.
 * <p>
 * One instance of the <code>SimpleChangeProfile</code> is created and
 * the following specific tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the monitoring check of the profile component
 * is initially enabled.</li>
 * <li>A reference value is loaded in the simple change profile
 * and it is verified that the load operation is correctly performed.</li>
 * <li>A test value identical to the reference value is passed through
 * the simple change profile and it is verified that the monitoring
 * check service reports "no deviation from profile detected".</li>
 * <li>A test value different from the reference value is passed through
 * the simple change profile and it is verified that the monitoring
 * check service reports "deviation from profile detected" and that
 * an event report has been created to record the profile violation.</li>
 * <li>Non-nominal behaviour check: it is checked that the monitoring check with a real-valued argument
 * reports "deviation from profile detected".</li>
 * <li>The monitoring is disabled and it is verified that
 * the enable status is correctly reported.</li>
 * <li>A test value different from the reference value is passed through
 * the disabled simple change profile and it is verified that the monitoring
 * check service reports "no deviation from profile detected" and that
 * no event reports are created.</li>
 * </ol>
 * @see DC_SimpleChangeProfile
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseSimpleChangeProfile_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_SIMPLECHANGEPROFILE*10+1 and "TestCaseSimpleChangeProfile_1".
      */
     TestCaseSimpleChangeProfile_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
     virtual void runTestCase(void);
};

#endif
