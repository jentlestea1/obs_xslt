//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyFsmState_1.h
//
// Version	1.0
// Date		02.10.02
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseDummyFsmState_1H
#define TestCaseDummyFsmState_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the functionalities implemented by the
 * <code>DC_FsmEvent</code> component.
 * An instance of the <code>DC_DummyFsmState</code> is created and the following
 * specific tests are performed upon it: <ol>
 * <li>It is verified that the class ID of the component has the correct value.</li>
 * <li>It is verified that the "next state" at creation is pNULL.</li>
 * <li>A "next state" is loaded in the component and it is verified that
 * the load operation is correctly executed.</li>
 * <li>It is verified that the initialization, exit and termination checks report
 * the correct results.</li>
 * <li>The initialization, continued and exit actions are executed and then it is
 * verified that the initialization, exit and termination checks still report
 * the correct results.</li>
 * </ol>
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseDummyFsmState_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_OBSDUMMYFSMSTATE*10+1 and "TestCaseDummyFsmState_1".
      */
     TestCaseDummyFsmState_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
