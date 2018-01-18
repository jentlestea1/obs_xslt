//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseByteArrayTelemetryStream_1.h
//
// Version	1.0
// Date		04.03.03
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseByteArrayTelemetryStream_1H
#define TestCaseByteArrayTelemetryStream_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the telemetry stream services as implemented
 * by class <code>DC_ByteArrayTelemetryStream</code>.
 * An instance of this class is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the configuration check service of the object
 * initially reports "object not configured".</li>
 * <li>The size of the byte array is set and then read out and
 * it is verified that that the read-out value is correct.</li>
 * <li>The startiing address of the byte array is loaded and then read out and
 * it is verified that that the read-out value is correct.</li>
 * <li>It is verified that the configuration check service now reports
 * "object configured".</li>
 * <li>A write request is made for a telemetry packet (an instance of class
 * <code>DC_DummyTelemetryPacket</code>) is used and it is verified that
 * the correct values are writtent to the byte array.</li>
 * <li>The <code>doesPacketFit</code> method is called twice to return
 * "item fits" in the first case and "item does not fit" in the second
 * case.</li>
 * <li>Additional write requests are made that should not be executed
 * because there is no more space in the byte array.</li>
 * <li>The telemetry stream is reset and it is verified that the
 * write requests can now be processed.</li>
 * <li>The byte array is again filled up and it is then flushed. It
 * is verified that the flush operation is successful.</li>
 * </ol>
 * @see DC_ByteArrayTelemetryStream
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseByteArrayTelemetryStream_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_BYTEARRAYTELEMETRYSTREAM*10+1 and "TestCaseByteArrayTelemetryStream_1".
      */
     TestCaseByteArrayTelemetryStream_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
