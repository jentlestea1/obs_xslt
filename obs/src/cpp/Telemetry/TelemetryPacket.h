//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TelemetryPacket.h
//
// Version	1.0
// Date		01.12.02
// Author	A. Pasetti (P&P Software)

#ifndef TelemetryPacketH
#define TelemetryPacketH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"

/**
 * Base class from which all telemetry packet classes are derived.
 * The <i>Telemetry Item</i> concept is implemented here to represent a group
 * of ordered bytes that
 * are intended to be sent to the telemetry stream and that constitute one
 * single logical unit in the sense that they are collected together.
 * This group of ordered bytes is referred to in what follows as the
 * <i>telemetry bytes</i>.
 * <p>
 * This class defines five attributes, two services, and one check.
 * The attributes allow the telemetry bytes to be characterized. They are: <ul>
 * <li>The <i>telemetry packet type</i>: this attribute defines the type of the telemetry
 * item. </li>
 * <li>The <i>telemetry packet subtype</i>: this attribute defines the subtype of the
 * telemetry packet. It is useful where the type attribute does not provide sufficient
 * granularity to characterize the telemetry packet type.</li>
 * <li>The <i>destination</i>: this attribute defines the destination of the telemetry bytes.</li>
 * <li>The <i>time tag</i>: this attribute represents a time stamp for the telemetry bytes.</li>
 * <li>The <i>in use flag</i>: this is a toggle attribute that can have two values:
 * "packet is in use" and "packet is not in use". This attribute
 * is useful when telemetry packets need to be allocated dynamically. The "in use" attribute can then
 * be used to discriminate between packets that are already allocated and
 * packets that are still free. </li>
 * </ul>
 * The two services defined by this class are: <ul>
 * <li>The <i>data update service</i> is used by a client to direct the telemetry
 * item component to update the
 * internal information that it uses to construct the telemetry bytes.</li>
 * <li>The <i>data acquisition service</i> is used by a client to format and acquire
 * the most recently updated telemetry bytes.</li>
 * </ul>
 * Finally, the check defined by this class is the
 * <i>validity check</i>. This service allows a client to ask a telemetry packet
 * component to verify that the most recently updated information is valid.
 * <p>
 * Two implementations of the data acquisition service are provided: a <i>safe implementation</i>
 * and a <i>fast implementation</i>. The safe implementation is built upon methods
 * <code>getUnsignedByte</code> and <code>getNumberOfBytes</code>. It allows the
 * most recently acquired telemetry bytes to be transfered one by one to the caller.
 * This implementation is safe because it complies with all coding rules defined for
 * the OBS Framework. However, it may not be fast because the transfer of each byte
 * requires a call to a virtual method. The alternative implementation is built on
 * methods <code>getStartAddress</code> and <code>getNumberOfBytes</code>. The former
 * method returns a pointer to the internal data area where the telemetry bytes are
 * stored. The latter returns the number of telemetry bytes. This implementation is
 * fast because the caller can copy the telemetry bytes using a fast memory copy 
 * algorithm. It is potentially unsafe because it gives the caller access to an
 * internal data structure of the telemetry packet component. The safe implementation
 * of the data update service must always be provided by all concrete subclasses.
 * The fast version may be provided by subclasses that manage large amounts of 
 * telemetry data. Method <code>isFastAcquisitionImplemented</code> is provided to
 * allow a caller to check whether the fast implementation is provided.
 * The fast version of the data acquisition service should be used only when
 * necessary for performance reasons. By default, the safe version should be used.
 * <p>
 * Telemetry item instances are intended to be used by a component that collects
 * telemetry data
 * and forwards them to a telemetry channel (in the OBS Framework, this telemetry
 * data collecting component is the <i>telemetry manager</i> instantiated from class
 * <code>CC_TelemetryManager</code>). The telemetry packet class assumes that the
 * collection of the telemetry data from one of its instances
 * is performed in three steps as follows:<ol>
 * <li>The data update service is called</li>
 * <li>The validity check is performed on the newly updated data</li>
 * <li>The data acquisition service is called to acquire the telemetry data</li>
 * </ol>
 * This class does not make any assumptions about the data structure that
 * is used internally to store the telemetry bytes.
 * It is an abstract class that is intended to provide a general interface
 * capable of modeling telemetry packet concepts
 * of varying complexity but it only provides minimal default implementations for
 * its attributes, services and for the validity check.
 * Applications should provide subclasses that implement their particular
 * telemetry concept.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup Telemetry
 */
class TelemetryPacket : public CC_RootObject {

  private:
    bool inUse;

  public:
    /**
     * Instantiate a telemetry packet component. The "in use" flag is set to: "packet
     * is not in use".
     */
    TelemetryPacket(void);

    /**
     * Setter method for the telemetry packet type. Since this class
     * identifies the telemetry packet type with the class identifier
     * (see <code>CC_RootObject</code>), this method is implemented as
     * a dummy method that returns without taking any action.
     * @see #getType
     * @param tmType the telemetry packet type
     */
    virtual void setType(TD_TelemetryType tmType);

    /**
     * Setter method for the telemetry packet sub-type. Since this class
     * does not model the telemetry packet sub-type, this method is implemented as
     * a dummy method that returns without taking any action.
     * @see #getSubType
     * @param tmSubType the telemetry packet sub-type
     */
    virtual void setSubType(TD_TelemetrySubType tmSubType);

    /**
     * Setter method for the telemetry packet time tag. Since this class
     * does not model the telemetry packet time tag, this method is implemented as
     * a dummy method that returns without taking any action.
     * @see #getTimeTag
     * @param timeTag the telemetry packet time tag
     */
    virtual void setTimeTag(TD_ObsTime timeTag);

    /**
     * Setter method for the telemetry packet destination. Since this class
     * does not model the telemetry packet destination, this method is implemented as
     * a dummy method that returns without taking any action.
     * @see #getDestination
     * @param tmDest telemetry packet destination
     */
    virtual void setDestination(TD_TelemetryDestination tmDest);

    /**
     * Return the number of bytes managed by this telemetry packet.
     * Each telemetry packet is responsible for generating a fixed number of
     * telemetry bytes. This method returns this fixed number.
     * <p>
     * @return number of bytes in this telemetry packet
     */
    virtual unsigned int getNumberOfBytes(void) = 0;

    /**
     * Implement the <i>data update service</i>.
     * A call to this method should normally be followed by a call to method
     * <CODE>isValid</CODE> to verify the validity of the newly updated data.
     */
    virtual void update(void) = 0;

    /**
     * Execute the <i>validity check</i> on the most recently updated
     * telemetry bytes.
     * This class provides a default implementation that always return "data
     * valid".
     * @see #update
     * @return true if the most recently updated telemetry bytes are valid,
     * false otherwise
     */
    virtual bool isValid(void);

    /**
     * Implement the safe version of the <i>data acquisition service</i>.
     * The telemetry data provided by this class are treated as a sequence
     * of bytes.
     * The method returns the n-th telemetry byte.
     * The parameter n must lie in the interval [0, N-1] where N is the
     * number of telemetry bytes (the return value
     * of method <CODE>getNumberOfBytes</CODE>).
     * @return value of n-th telemetry byte
     * @param n the telemetry byte to be returned (starting with byte 0)
     */
    virtual unsigned char getUnsignedByte(unsigned int n) = 0;

    /**
     * Implement the fast version of the <i>data acquisition service</i>.
     * If this version of the service is implemented, then this method returns
     * a pointer to start address of an internal data structure that holds all
     * telemetry data as a linear sequence of bytes. The size of the internal
     * data structure is given by method <code>getNumberOfBytes</code>).
     * This method only has a meaningful implementation if the fast version of the
     * data acquisition service is provided. This is the case if method
     * <code>isFastAcquisitionImplemented</code> returns a value of <code>true</code>.
     * If this is not the case, this method should return a null pointer.
     * This class provideds a default implementation that returns a null
     * pointer.
     * @return a null pointer
     */
    virtual unsigned char* getStartAddress(void);

    /**
     * Return <code>true</code> if the fast version of the data acquisition
     * service is implemented. This class provides a default implementation
     * that returns <code>false</code>.
     * @see #getStartAddress
     * @return <code>true</code> if the fast version of the data acquisition
     * service is implemented
     */
    virtual bool isFastAcquisitionImplemented(void);

    /**
     * Getter method for the telemetry packet type. This class implements the
     * the type to coincide with the lest significant byte of the class identifier.
     * A pseudo-code implementation of this method therefore is:<pre>
     *      return (TD_TelemetryType)(getClassId()%256);</pre>
     * The modulo operation ensures that there is no overflow even if there is a
     * type mismatch between type <code>TD_TelemetryType</code> the type of the
     * type of the class identifier.
     * @return the telemetry packet type
     */
    virtual TD_TelemetryType getType(void) const;

    /**
     * Getter method for the telemetry sub-type. This class does not model
     * the telemetry sub-type. This method always returns zero.
     * @return the telemetry sub-type
     */
    virtual TD_TelemetrySubType getSubType(void) const;

    /**
     * Getter method for the telemetry packet time tag. This class does not model
     * the telemetry packet time tag. This method always returns zero.
     * @return the telemetry packet time
     */
    virtual TD_ObsTime getTimeTag(void) const;

    /**
     * Getter method for the telemetry packet destination. This class does not model
     * the telemetry packet destination. This method always returns zero.
     * @return the telemetry packet destination
     */
    virtual TD_TelemetryDestination getDestination(void) const;

    /**
     * Set the value of the "in use" attribute.
     * @see #isInUse
     * @param newInUse the new value of the in use attribute
     */
    void setInUse(bool newInUse);

    /**
     * Return the value of the "in use" attribute. If the method returns true, then
     * the packet is already in use, otherwise it is free and can be configured.
     * @see #setInUse
     * @return the value of the "in use" attribute.
     */
    bool isInUse(void) const;

};

#endif
