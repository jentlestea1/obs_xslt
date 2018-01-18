//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyTelemetryStream_1.h
//
// Version	1.0
// Date		21.11.03 (Version 1.0)
// Author	R. Totaro

#ifndef TestCaseDataTelemetryStream_1H
#define TestCaseDataTelemetryStream_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the telemetry stream services as implemented
 * by class <code>DC_DummyTelemetryStream</code>.
 * An instance of this class is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is checked.</li>
 * <li>The default return value of method <code>getCapacity</code> is checked.</li>
 * <li>The default return value of method <code>doesPacketFit</code> is checked.</li>
 * <li>Dummy calls are performed to methods <code>reset</code>, <code>flsuh</code>
 * and <code>write</code>.</li>
 * </ol>
 * @see DC_DummyTelemetryStream
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseDummyTelemetryStream_1 : public TestCaseGenericSetUp {
public:
    /**
     * Set the identifier and the name of the test case to, respectively,
     * ID_DUMMYTELEMETRYSTREAM*10+1 and "TestCaseDummyTelemetryStream_1".
     */
    TestCaseDummyTelemetryStream_1(void);

    /**
     * Execute the test case. See class comment for details.
     */
     virtual void runTestCase(void);
};
#endif
