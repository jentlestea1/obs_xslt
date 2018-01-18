//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyTelemetryPacket_1.h
//
// Version	1.0
// Date		04.03.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseDataTelemetryPacket_1H
#define TestCaseDataTelemetryPacket_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the telemetry packet services as implemented
 * by class <code>DC_DummyTelemetryPacket</code>.
 * An instance of this class is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the configuration service reports "object not configured".</li>
 * <li>The number of encapsulated bytes is set to 2 and it is verified that
 * the configuration service reports "object configured".</li>
 * <li>It is verified that the number of encapsulated bytes is correctly reported
 * to be equal to 2.</li>
 * <li>The value of the encapsulated bytes is set and read out with
 * the data acquisition service and its correctness is verified.</li>
 * <li>It is verified that the default value returned by the
 * data acquisitions service is 0 for all encapsulated bytes.</li>
 * <li>It is verified that the default value returned by the
 * the validity check is "data valid".</li>
 * <li>The validity status is set and read out and its correctness
 * is verified.</li>
 * <li>The implementation of the update service is verified.</li>
 * <li>The value of one of encapsulated bytes is set to 255 and an
 * update request is made. It is verified that the value of the
 * encapsulated byte is correctly wrapped around to 0..</li>
 * <li>The default value of the telemetry packet time tag is read out and its correctness
 * is verified.</li>
 * <li>The default value of the telemetry packet type is read out and its correctness
 * is verified.</li>
 * <li>The default value of the telemetry packet subtype is read out and its correctness
 * is verified.</li>
 * <li>The default value of the telemetry packet destination is read out and its correctness
 * is verified.</li>
 * <li>The default value of the "in use" flag is read out and its correctness is verified.</li>
 * <li>The implementation of the "in use" flag is checked.</li>
 * <li>The default implementation of the "fast data acqusition service" is checked.</li>
 * </ol>
 * @see DC_DummyTelemetryPacket
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseDummyTelemetryPacket_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_DUMMYTelemetryPacket*10+1 and "TestCaseDummyTelemetryPacket_1".
      */
     TestCaseDummyTelemetryPacket_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
      virtual void runTestCase(void);
};

#endif
