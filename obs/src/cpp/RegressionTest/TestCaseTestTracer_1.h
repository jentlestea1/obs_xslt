//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseTestTracer_1.h
//
// Version	1.0
// Date		13.09.02
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseTestTracer_1H
#define TestCaseTestTracer_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the functionality of the
 * <code>DC_TestTracer</code> component.
 * A <code>DC_TestTracer</code> instance is created and the following specific
 * tests are performed upon it: <ol>
 * <li>It is verified that the test tracer component is enabled at creation.</li>
 * <li>A synch trace signal is sent through the test tracer component and it
 * is verified that the trace item is correctly written to the log file.</li>
 * <li>A packet trace signal is sent through the test tracer component and it
 * is verified that the trace items are correctly written to the log file.</li>
 * <li>The test tracer is disabled and it is verified that this is correctly
 * reproted by the <code>isEnabled</code> service.</li>
 * <li>The test tracer is disabled and it is verified that attempts to send a
 * synch trace have no effect on the log file.</li>
 * <li>The test tracer is disabled and it is verified that attempts to send a
 * packet trace have no effect on the log file.</li>
 * </ol>
 * The above tests are only performed if the test application is running in a
 * desktop environment. If the application is running in an embedded environment,
 * no tests are performed and the test case always returns "test successful".
 * @see TestTracer
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseTestTracer_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_OBSTESTTRACER*10+1 and "TestCaseTestTracer_1".
      */
     TestCaseTestTracer_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
