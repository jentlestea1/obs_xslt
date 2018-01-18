//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseEvent_1.h
//
// Version	1.0
// Date		13.09.02
// Author	     A. Pasetti (P&P Software)

#ifndef TestCaseEvent_1H
#define TestCaseEvent_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the attribute setting and object configuration services of class
 * <code>DC_Event</code>.
 * The following specific tests are performed: <ol>
 * <li>The event type attribute of an event object is set
 * and then read out
 * and the correctness of its values is verified.</li>
 * <li>The time stamp attribute of an event object is set
 * and then read out
 * and the correctness of its values is verified.</li>
 * </ol>
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseEvent_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_EVENT*10+1 and "TestCaseEvent_1".
      */
     TestCaseEvent_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
