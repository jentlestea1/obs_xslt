//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyPUSTelemetryPacket.h
//
// Version	1.0
// Date		04.03.03
// Author	A. Pasetti (P&P Software)

#ifndef DC_DummyPUSTelemetryPacketH
#define DC_DummyPUSTelemetryPacketH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "PUSTelemetryPacket.h"

/**
 * Dummy implementation of the <code>PUSTelemetryPacket</code> class
 * useful for testing purposes.
 * This telemetry packet encapsulates a single and settable byte. The
 * update service is implemented to increment the value of the byte
 * by one (with a wrap-around to zero when the value of 255 is reached).
 * The values of the telemetry packet attributes are initialized
 * to: <ul>
 * <li>The telemetry packet type is set to TEST_TM_TYPE</li>
 * <li>The telemetry packet subtype is set to TEST_TM_SUBTYPE</li>
 * <li>The telemetry packet time tag is set to TEST_TM_TIMETAG</li>
 * </ul>
 * The constants are defined in file <code>TestConstants.h</code>.
 * Note that the telemetry destination does not need to be set because
 * it is already set to a default value by the constructor of
 * class <code>PUSTelemetryPacket</code>. Similarly, the APID of the process
 * generating the telemetry data does not need to be set because it is
 * a static field that should be set during the test set up process.
 * @see TestConstants
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_DummyPUSTelemetryPacket : public PUSTelemetryPacket {

  private:
    unsigned char item;

  public:

    /**
     * Instantiate a dummy PUS telemetry packet component. The class identifier is set,
     * and the encapsulated byte is initialized with a value of 0.
     * The telemetry packet attributes are set as indicated in the class comment.
     */
    DC_DummyPUSTelemetryPacket(void);

    /**
     * This method always returns 1. This telemetry packet only encapsulates
     * one single byte.
     * @return always return 1
     */
    virtual unsigned int getNumberOfBytes(void);

    /**
     * Return the encapsulated byte. The value of the argument is ignored.
     * @return the value of the encapsulated byte
     * @param n this parameter is ignored
     */
    virtual unsigned char getUnsignedByte(unsigned int n);

    /**
     * Increment the value of the encapsulated byte by one. Wrap around to 0
     * when the value of 255 is reached.
     */
    virtual void update(void);

    /**
     * Set the value of the encapsulated byte. This is the value returned by
     * method <code>getUnsignedByteUnchecked</code>.
     * @see #getUnsignedByteUnchecked
     * @param value the value of the encapsulated byte
     */
    void setValue(unsigned char value);

};

#endif
