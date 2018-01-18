//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseRootObject_1.h
//
// Version	1.0
// Date		13.09.02
// Author	     A. Pasetti (P&P Software)

#ifndef TestCaseRootObject_1H
#define TestCaseRootObject_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify setting of instance ID's in class <code>CC_RootObject</code>.
 * The following specific tests are performed: <ol>
 * <li>It is checked that the value of the instance identifier is incremented
 * by 1 every time a new insance of class <code>CC_RootObject</code>
 * is created.</li>
 * </ol>
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseRootObject_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_ROOTOBJECT*10+1 and "TestCaseRootObject_1".
      */
     TestCaseRootObject_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
