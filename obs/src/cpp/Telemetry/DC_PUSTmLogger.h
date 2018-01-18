//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSTmLogger.h
//
// Version	1.0
// Date		04.02.04 (Version 1.0)
// Author	A. Pasetti (P&P Software)

#ifndef DC_PUSTmLoggerH
#define DC_PUSTmLoggerH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "TelemetryStream.h"

/**
 * <i>Telemetry logger stream</i> that logs all telemetry packets in an internal
 * data structure and offers methods to inspect their content. 
 * This class defines a <i>telemetry buffer</i> where telemetry
 * packets are stored as they are written to the telemetry stream.
 * The telemetry buffer is organized as a circular buffer.
 * When the end of the buffer is reached, its first entry is overwritten.
 * This class must be configured by specifying the capacity of the
 * buffer and the maximum length (in bytes) of the application data
 * of the telemetry packets to be stored in the buffer.
 * This class is intended to be used for testing purposes only.
 * <p>
 * This telemetry stream writes the following data to the telemery
 * buffer for each telemetry packet: <ul>
 * <li>The application data read from the telemetry packet.</li>
 * <li>The number of bytes in the application data.</li>
 * <li>The type of the telemetry packet.</li>
 * <li>The subtype of the telemetry packet.</li>
 * <li>The packet time tag as read from the telemetry packet. </li>
 * </ul>
 * Each of the above items can be separately accessed through dedicated
 * getter methods. 
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_PUSTmLogger : public TelemetryStream {

  private:

      struct TmPacket {
          TD_TelemetryType type;
          TD_TelemetrySubType subType;
          TD_ObsTime timeTag;
          unsigned char* data;
          unsigned int nData;
      };

      TmPacket* tmBuffer;
      unsigned int maxData;
      unsigned int counter;
      unsigned int capacity;

   public:

    /**
     * Instantiate the component. The class identifier is set. The 
     * telemetry buffer is left uninitialized to signify that the component
     * is not yet configured. 
     */
    DC_PUSTmLogger(void);

    /**
     * Set the capacity of the telemetry buffer. 
     * The capacity of the telemetry buffer is the maximum number of
     * telemetry packets that can be written to the buffer without
     * overwriting any existing packet. This is an initialization
     * method that should only be called once. 
     * Only positive values for the argument of this method are legal.
     * @param n the capacity of the telemetry buffer
     */
    void setBufferCapacity(unsigned int n);

    /**
     * Return the capacity of the telemetry buffer. 
     * @see #setBufferCapacity
     * @return the capacity of the telemetry buffer
     */
    unsigned int getBufferCapacity(void) const;

    /**
     * Set the maximum length (in number of bytes) of the application
     * of the telemetry packets. This is an initialization
     * method that should only be called once. 
     * Only positive values for the argument of this method are legal.
     * @param n the maximum length of the telemetry packet application data
     */
    void setMaxPacketLength(unsigned int n);

    /**
     * Return the capacity of the telemetry buffer. 
     * @see #setBufferCapacity
     * @return the capacity of the telemetry buffer
     */
    unsigned int getMaxPacketLength(void) const;

    /**
     * Get the number of packets that have been written to the telemetry
     * logger so far.
     * @return the number of packets written so far
     */
    unsigned int getPacketCounter(void) const;

    /**
     * Get the type of the i-th packet before the last in the telemetry
     * buffer. If N is the number of packets to have been written so far 
     * to the telemetry logger stream, then this method returns the type
     * of the (N-i)-th packet to have been written to the logger.
     * The value of i should be smaller than the capacity of the telemetry 
     * buffer. If this is not the case, then a value of zero is returned.
     * @param i the packet index
     * @return the packet type
     */
    TD_TelemetryType getType(unsigned int i) const;

    /**
     * Get the subtype of the i-th packet before the last in the telemetry
     * buffer. The way the argument i is interpreted is the same as for 
     * method <code>getType</code>.
     * @see #getType
     * @param i the packet index
     * @return the packet sub type
     */
    TD_TelemetrySubType getSubType(unsigned int i) const;

    /**
     * Get the time tag of the i-th packet before the last in the telemetry
     * buffer. The way the argument i is interpreted is the same as for 
     * method <code>getType</code>.
     * @see #getType
     * @param i the packet index
     * @return the packet time tag
     */
    TD_ObsTime getTimeTag(unsigned int i) const;

    /**
     * Get the length (number of bytes in the application data) of the 
     * i-th packet before the last in the telemetry
     * buffer. The way the argument i is interpreted is the same as for 
     * method <code>getType</code>.
     * @see #getType
     * @param i the packet index
     * @return the packet length
     */
    unsigned int getLength(unsigned int i) const;

    /**
     * Get the j-th application data byte of the 
     * i-th packet before the last in the telemetry
     * buffer. The way the argument i is interpreted is the same as for 
     * method <code>getType</code>. The argument j must lie in the range
     * [0,L-1] where L is the length of the i-th packet (as returned 
     * by method <code>getLength</code>).
     * @see #getType
     * @param i the packet index
     * @param j the byte index
     * @return the application data byte
     */
    unsigned char getData(unsigned int i, unsigned int j) const;

    /**
     * Return true if the argument packet fits in the telemetry logger.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *      if ( pItem->getNumberOfBytes()<getMaxPacketLength() )
     *          return true;
     *	    else
     *          return false; </PRE>
     * @param pPacket the telemetry packet to be written to the telemetry stream
     * @return true if the telemetry packet fits in the telemetry logger,
     * false otherwise
     */
    virtual bool doesPacketFit(TelemetryPacket* pPacket);

    /**
     * Write one telemetry packet to the telemetry logger.
     * When the telemetry logger is full, its oldest entry is overwritten.
     * If the length of the packet exceeds M (the maximum length set with method
     * <code>setMaxPacketLength</code>), then only the first M application
     * data bytes are written to the telemetry logger.
     * The telemetry packet data are extracted from the telemetry packet 
     * component through its <i>data acquisition service</i>. If the packet
     * provides it, then the <i>fast version</i> of the service is used.
     * Otherwise the <i>safe version</i> is used. Method 
     *<code>isFastAcquisitionImplemented</code> is used to determine 
     * whether the fast version is provided.
     * @param pItem the telemetry packet to be written to the telemetry stream
     */
    virtual void write(TelemetryPacket* pItem);

    /**
     * Perform a class-specific configuration check on the telemetry logger stream:
     * verify that the maximum length of the telemetry packets and the maximum
     * number of telemetry packets have been set.
     * @return true if the telemetry logger stream is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);

};

#endif
