//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseRootObject_3.h
//
// Version	1.0
// Date		13.09.02
// Author	     A. Pasetti (P&P Software)

#ifndef TestCaseRootObject_3H
#define TestCaseRootObject_3H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Check the object and system configuration check services.
 * The following specific checks are performed: <ol>
 * <li>Two <code>CC_RootObject</code> instances are created and it is checked
 * that their object configuration services report "object configured".</li>
 * <li>It is checked
 * that the system configuration check service reports "system configured".</li>
 * <li>An event object is created but not fully configured and it is checked
 * that the system configuration check service reports "system not configured".</li>
 * </ol>
 * Since it checks the system configuration service, this test case should be
 * the first test case to be executed in a test run.
 * If it is not, it might fail unpredictably.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseRootObject_3 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_ROOTOBJECT*10+3 and "TestCaseRootObject_3".
      */
     TestCaseRootObject_3(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
