//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyPUSTelemetryPacket_1.h
//
// Version	1.0
// Date		04.03.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseDummyPUSTelemetryPacket_1H
#define TestCaseDummyPUSTelemetryPacket_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Check the functionalities implemented by class <code>PUSTelemetryPacket</code>.
 * Since this class is abstract, the checks are carried out on its concrete subclass
 * <code>DC_DummyPUSTelemetryPacket</code>.
 * An instance of this class is created and the following specific
 * checks are carried out: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The value of the encapsulated byte is set and read out with
 * the data acquisition service and its correctness is verified.</li>
 * <li>It is verified that the default value returned by the
 * data acquisitions service is 0.</li>
 * <li>The implementation of the update service is verified.</li>
 * <li>The value of the encapsulated byte is set to 255 and an
 * update request is made. It is verified that the value of the
 * encapsulated byte is correctly wrapped around to 0..</li>
 * <li>The telemetry packet time tag is set and then read back and its correctness
 * is checked.</li>
 * <li>The telemetry packet type is set and then read back and its correctness
 * is checked.</li>
 * <li>The telemetry packet sub type is set and then read back and its correctness
 * is checked.</li>
 * <li>The telemetry packet identifier is read and the correctness of its value is
 * checked.</li>
 * <li>The default value of the telemetry packet destination is checked.</li>
 * <li>The telemetry packet destination is modified and then read back and its correctness
 * is checked.</li>
 * <li>The value of the OBS Clock is read and it is checkes that it is different from NULL.</li>
 * </ol>
 * @see DC_PUSTelemetryPacket
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseDummyPUSTelemetryPacket_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_DUMMYPUSTELEMETRYPACKET*10+1 and "TestCaseDummyPUSTelemetryPacket_1".
      */
     TestCaseDummyPUSTelemetryPacket_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
      virtual void runTestCase(void);
};

#endif
