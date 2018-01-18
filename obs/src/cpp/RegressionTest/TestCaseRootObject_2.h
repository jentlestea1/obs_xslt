//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseRootObject_2.h
//
// Version	1.0
// Date		13.09.02
// Author	     A. Pasetti (P&P Software)

#ifndef TestCaseRootObject_2H
#define TestCaseRootObject_2H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify setting of class ID's in class <code>CC_RootObject</code>.
 * The following specific tests are performed: <ol>
 * <li>The class ID for class <code>CC_RootObject</code> is read
 * out and its value is verified.</li>
 * <li>The class ID of two different instances of classes <code>CC_RootObject</code>
 * is read out and it is verified that the two values are identical.</li>
 * </ol>
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseRootObject_2 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_ROOTOBJECT*10+2 and "TestCaseRootObject_2".
      */
     TestCaseRootObject_2(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
