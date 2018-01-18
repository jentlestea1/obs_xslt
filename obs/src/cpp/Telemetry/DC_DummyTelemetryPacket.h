//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyTelemetryPacket.h
//
// Version	1.0
// Date		04.03.03
// Author	A. Pasetti (P&P Software)

#ifndef DC_DummyTelemetryPacketH
#define DC_DummyTelemetryPacketH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "TelemetryPacket.h"

/**
 * Dummy implementation of the <code>TelemetryPacket</code> interface
 * useful for testing purposes.
 * This telemetry packet encapsulates N settable bytes. The value of N
 * is a configuration parameter. The
 * update service is implemented to increment the value of each telemetry byte
 * by one (with a wrap-around to zero when the value of 255 is reached).
 * The <i>validity check</i> can be dynamically set up to return
 * either "data valid" or "data not valid".
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_DummyTelemetryPacket : public TelemetryPacket {

  private:
    unsigned int nOfBytes;
    unsigned char* item;
    bool validStatus;

  public:

    /**
     * Instantiate a telemetry packet component. The class identifier is set,
     * and the return
     * value of the validity check is set to "data valid". The number of
     * encapsulated bytes is set to an illegal value tosignify that the
     * component is not yet configured.
     * The constructor also calls the methods to set the telemetry packet time tag,
     * the type, the subtype, and the destination. These calls are unnecessary
     * from a functional point of view because none of these attributes is
     * implemented by the <code>TelemetryPacket</code> class. However the calls
     * are useful during testing to achieve full statement coverage of the
     * the base class.
     */
    DC_DummyTelemetryPacket(void);

    /**
     * This method always returns the number of telemetry bytes.
     * @return the number of telemetry bytes
     */
    virtual unsigned int getNumberOfBytes(void);

    /**
     * Return the n-th encapsulated byte.
     * @return the value of the n-th encapsulated byte
     * @param n the byte index
     */
    virtual unsigned char getUnsignedByte(unsigned int n);

    /**
     * Increment the value of each encapsulated byte by one. Wrap around to 0
     * when the value of 255 is reached.
     */
    virtual void update(void);

    /**
     * Set the validity status. This is the value returned by the validity check
     * (method <code>isValid</code>.
     * @see #isValid
     * @param validStatus the validity status
     */
    void setValidStatus(bool validStatus);

    /**
     * Set the value of the n-th encapsulated byte. This is the value returned by
     * method <code>getUnsignedByteUnchecked</code>. The value of n must lie in
     * the range [0,N-1] where N is the total number of telemetry bytes
     * encapsulated in the telemetry packet. Calls with out-of-range values of n
     * have no effect.
     * @see #getUnsignedByteUnchecked
     * @param value the value of the encapsulated byte
     * @param n the index of the encapsulated byte
     */
    void setValue(unsigned int n, unsigned char value);

    /**
     * Set the number of bytes encapsulated by this telemetry packet.
     * This is an initialization method. It should only be called once.
     * Only positive values of the argument n are legal.
     * The telemetry bytes are initialized to zero.
     * @see #getUnsignedByteUnchecked
     * @param n the number of bytes encapsulated in this telemetry packet
     */
    void setNumberOfBytes(unsigned int n);

    /**
     * Return the validity status set with method <code>setValidStatus</code>.
     * @see #setValidStatus
     * @return the validity status
     */
    virtual bool isValid(void);

    /**
     * Perform a class-specific configuration check on the component:
	 * verify that the number of encapsulated bytes has been set.
     * @return true if the component is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);
};

#endif
