//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseFileTelemetryStream_2.h
//
// Version	1.0
// Date		04.03.03
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseFileTelemetryStream_2H
#define TestCaseFileTelemetryStream_2H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the file-oriented telemetry stream as implemented
 * by class <code>DC_FileTelemetryStream</code>.
 * In this test the telemetry data are written to the standard
 * output. The success or otherwise
 * of the test should be verified by checking the standard output.
 * An instance of this class is created and the following specific
 * tests are performed: <ol>
 * <li>The telemetry stream file is set to pNULL (to signify that
 * it is desired to direct the telemetry data to the standard
 * output) and it is verified that the set operation succeeded.</li>
 * <li>A dummy PUS telemetry packet (instance of class <code>DC_DummyTelemetryPacket</code>)
 * is configured with two bytes with values of 1 and 2. The telemetry packet is written
 * to the telemetry stream
 * The success of this operation should be checked by inspecting
 * the standard output.</li>
 * <li>The value of the bytes encapsulated in the dummy telemetry packet
 * is incremented by one and the telemetry packet is again written to the
 * telemetry stream.
 * The success of this operation should be checked by inspecting
 * the standard output.</li>
 * </ol>
 * @see DC_FileTelemetryStream
 * @see DC_DummyTelemetryPacket
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseFileTelemetryStream_2 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_FILETELEMETRYSTREAM*10+2 and "TestCaseFileTelemetryStream_2".
      */
     TestCaseFileTelemetryStream_2(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
