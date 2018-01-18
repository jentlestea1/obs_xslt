//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseFsmEvent_1.h
//
// Version	1.0
// Date		02.10.02
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseFsmEvent_1H
#define TestCaseFsmEvent_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the functionalities implemented by the
 * <code>DC_FsmEvent</code> component.
 * An instance of the <code>DC_FsmEvent</code> is created and the following
 * specific tests are performed upon it: <ol>
 * <li>It is verified that the class ID of the component has the correct value.</li>
 * <li>It is verified that the FsmEvent is not configured at creation (object
 * configuration service reports
 * "not configured").</li>
 * <li>A target state is loaded in the FsmEvent and it is verified that
 * the load operation is correctly executed.</li>
 * <li>A target FSM is loaded in the FsmEvent and it is verified that
 * the load operation is correctly executed.</li>
 * <li>After the target FSM and target states have been loaded, it is verified
 * that the FsmEvent is configured (object configuration service reports
 * "configured").</li>
 * </ol>
 * @see DC_FsmEvent
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseFsmEvent_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_OBSFSMEVENT*10+1 and "TestCaseFsmEvent_1".
      */
     TestCaseFsmEvent_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
