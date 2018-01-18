//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseSimpleTelemetryModeManager_1.h
//
// Version	1.0
// Date		02.03.03
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseSimpleTelemetryModeManager_1H
#define TestCaseSimpleTelemetryModeManager_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the services implemented
 * by class <code>DC_SimpleTelemetryModeManager</code>. An instance of
 * the class is created and
 * the following specific tests are performed upon it:<ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The mode manager is configured and it is verified that it
 * has only one mode and that its default mode index is 0.</li>
 * <li>It is verified that calls to its <code>update</code>
 * method have no effect on the mode.</li>
 * </ol>
 * @see DC_SimpleTelemetryModeManager
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseSimpleTelemetryModeManager_1 : public TestCaseGenericSetUp {
public :
    /**
     * Set the identifier and the name of the test case to, respectively,
     * ID_SIMPLETELEMETRYMODEMANAGER*10+1 and
     * "TestCaseSimpleTelemetryModeManager_1".
     */
    TestCaseSimpleTelemetryModeManager_1(void);

    /**
     * Execute the test case. See class comment for details.
     */
    virtual void runTestCase(void);
};

#endif
