//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyDataPool_1.h
//
// Version	1.0
// Date		12.10.03
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseDummyDataPool_1H
#define TestCaseDummyDataPool_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Check the functionalities implemented by the <code>DC_DummyDataPool</code> class.
 * An instance of the component is created and the following
 * specific checks are performed upon it: <ol>
 * <li>It is verified that the class identifier has the correct value.</li>
 * <li>It is verified that the size of the data pool is equal to the size of the type
 * <code>TD_Integer</code>.</li>
 * <li>It is verified that the value of the item in the data pool is zero.</li>
 * </ol>
 * @see DC_BasicDataPool
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseDummyDataPool_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_DUMMYDATAPOOL*10+1 and "TestCaseDummyDataPool_1".
      */
     TestCaseDummyDataPool_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
