//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseFileTelemetryStream_1.h
//
// Version	1.0
// Date		04.03.03
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseFileTelemetryStream_1H
#define TestCaseFileTelemetryStream_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the file-oriented telemetry stream as implemented
 * by class <code>DC_FileTelemetryStream</code>.
 * In this test the telemetry data are written to the file
 * <code>TelemetryStream.txt</code> which should be created in the
 * directory from which the program is run. The success or otherwise
 * of the test should be verified by inspecting this file.
 * An instance of this class is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The telemetry stream file is set and it is verified that
 * the set operation succeeded.</li>
 * <li>A dummy PUS telemetry packet (instance of class <code>DC_DummyTelemetryPacket</code>)
 * is configured with two bytes with values of 1 and 2. The telemetry packet is written
 * to the telemetry stream
 * The success of this operation should be checked by inspecting
 * the telemetry output file.</li>
 * <li>The value of the bytes encapsulated in the dummy telemetry packet
 * is incremented by one and the telemetry packet is again written to the
 * telemetry stream.
 * The success of this operation should be checked by inspecting
 * the telemetry output file.</li>
 * </ol>
 * @see DC_FileTelemetryStream
 * @see DC_DummyTelemetryPacket
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseFileTelemetryStream_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_FILETELEMETRYSTREAM*10+1 and "TestCaseFileTelemetryStream_1".
      */
     TestCaseFileTelemetryStream_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
