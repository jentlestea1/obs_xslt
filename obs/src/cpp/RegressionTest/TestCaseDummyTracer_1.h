//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyTracer_1.h
//
// Version	1.0
// Date		13.09.02
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseDummyTracer_1H
#define TestCaseDummyTracer_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the functionality of the
 * <code>DC_DummyTracer</code> component.
 * The following specific tests are performed: <ol>
 * <li>A <code>DC_DummyTracer</code> instance is created and it is verified
 * that it enable status is "disabled".</li>
 * <li>A synch trace signal is sent through the dummy tracer component.
 * This operation should have no effect.</li>
 * <li>A packet trace signal is sent through the dummy tracer component.
 * This operation should have no effect.</li>
 * </ol>
 * @see DC_DummyTracer
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseDummyTracer_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_OBSDUMMYTRACER*10+1 and "TestCaseDummyTracer_1".
      */
     TestCaseDummyTracer_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
