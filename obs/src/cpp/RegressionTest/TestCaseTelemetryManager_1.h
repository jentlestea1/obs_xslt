//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseTelemetryManager_1.h
//
// Version	1.0
// Date		04.03.03
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseTelemetryManager_1H
#define TestCaseTelemetryManager_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Check the configuration process of a telemetry manager.
 * A telemetry manager instance is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the configuration check service of the telemetry
 * manager initially reports "object not configured".</li>
 * <li>A telemetry mode manager is loaded in the telemetry manager and
 * it is verified that it can be correctly read out.</li>
 * <li>A telemetry stream is loaded in the telemetry manager and
 * it is verified that it can be correctly read out.</li>
 * <li>The size of the immediate dispatch queue is set equal to zero and
 * it is verified that it can be correctly read out.</li>
 * <li>It is verified that the status of immediate dispatch queue is "queue full".</li>
 * <li>It is verified that the configuration check service of the telemetry
 * manager now reports "object configured".</li>
 * </ol>
 * @see CC_TelemetryManager
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseTelemetryManager_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_TELEMETRYMANAGER*10+1 and "TestCaseTelemetryManager_1".
      */
     TestCaseTelemetryManager_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
     virtual void runTestCase(void);
};

#endif
