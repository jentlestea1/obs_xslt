//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_BasicPUSTmStream.h
//
// Version	1.0
// Date		04.02.04 (Version 1.0)
// Author	A. Pasetti (P&P Software)

#ifndef DC_BasicPUSTmStreamH
#define DC_BasicPUSTmStreamH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "TelemetryStream.h"

/**
 * Telemetry stream that packetizes the telemetry data according to the
 * PUS and writes them to a <i>telemetry write area</i>.
 * This component can write several packets to the telemetry write area 
 * in sequence, up to the point where there is no space left in the
 * telemetry write area. 
 * The telemetry write area is characterized by
 * a <i>starting address</i> and by a <i>size</i>. The starting
 * address and the size are settable configuration parameters.
 * They can be changed dynamically. The first byte of the telemetry write
 * area holds the number of packets that have been written to it since the
 * last time the stream was reset. Following bytes hold the images of the
 * the telemetry packets in the order in which they are written.
 * <p>
 * This component maintains a <i>write counter</i> and a <i>packet counter</i>. 
 * Both counters are reset to 0 by
 * a call to operation <code>reset</code> or <code>flush</code>.
 * The write counter is incremented every
 * time a byte is written to the telemetry write array.
 * If its value is smaller than the size of the telemetry write area, then the
 * write counter points
 * to the location in the write area where the next telemetry data byte
 * will be written. The packet counter is equal to the number of packets
 * that have been written to the telemetry write area since the stream
 * was last reset. The value of the packet counter is the same as the
 * value of the first byte of the telemetry write area.
 * <p>
 * Write requests that cannot be processed because
 * there is not enough space in the telemetry write area have no effect
 * other than the generation of event EVT_TM_STREAM_END.
 * It is the responsibility of the user to perform reset or flush
 * operations when the byte array has been completely filled.
 * <p>
 * This telemetry stream adds the header data to the packet data that it
 * retrieves from the packet itself. The format of the packet header
 * is in accordance with the PUS with the following qualifications: <ul>
 * <li>The data field header flag is always set to 1</li>
 * <li>The APID is read from the telemetry packet through method 
 * <code>getPacketId</code></li>
 * <li>The grouping flags are always set to "11" (stand-alone packet)</li>
 * <li>The packet sub-counter is omitted</li>
 * <li>The packet destination ID field is omitted</li>
 * <li>The time information is read from the telemetry packet. It is written
 * as a value of type <code>TD_ObsTime</code>.</li>
 * <li>The packet error control is set to zero (it is assumed that it is computed
 * downstream when the packet is actually dispatched to its destination)</li>
 * <li>The packet sequence count is initialized to zero when the telemetry stream
 * and is incremented by one (with wrap around) every time a packet is written.</li>
 * </ul>
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_BasicPUSTmStream : public TelemetryStream {

  private:
      unsigned char* tmData;     // the telemetry write area
      unsigned int size;        // the size of the byte array in bytes
      unsigned int writeCounter;
      unsigned short packetSequenceControl;
      unsigned int nAdditionalBytes;    // number of bytes added by this TM stream to 
                                        // the application data read from the packet

  public:

    /**
     * Instantiate the component. The class identifier is set. The size and
     * starting address of the byte array are set to illegal values to signify
     * that the component is not yet configured. The write counter is set to zero.
     */
    DC_BasicPUSTmStream(void);

    /**
     * Reset the telemetry stream. The write counter is set to 1 and the packet 
     * counter is set to 0.
     * The next packet will be written at the beginning of the telemetry
     * write area (starting at location 1, location 0 is reserved for the 
     * packet counter).
     */
    virtual void reset(void);

    /**
     * The flush operation is equivalent to a reset operation.
     * @see #reset
     */
    virtual void flush(void);

    /**
     * Return the capacity of the telemetry stream. The capacity of this
     * telemetry stream is equal to the size in bytes of the telemetry write
     * area.
     * @return the size of the byte array in number of bytes
     */
    virtual unsigned int getCapacity(void);

    /**
     * Set the capacity of the telemetry stream. The capacity of this
     * telemetry stream is equal to the size in bytes of the telemetry write
     * area.
     * If s is the staring address of the telemetry write area (loaded with method
     * <code>setStartingAddress</code>) and if L is the value loaded with 
     * with this method, then the i-th location of the telemetry write area is
     * internally accessed as s[i] where i must be in the range [0,L-1].
     * It is the responsibility of the user to ensure that the locations thus
     * accessed are free for use by this telemetry stream component.
     * Only positive values for the argument of this method are legal.
     * @see #setStartingAddress
     * @param n the size of the telemetry write area in number of bytes
     */
    void setCapacity(unsigned int n);

    /**
     * Set the starting address of the telemetry write area. This component does not
     * perform any memory allocation operation. It assumes that the memory
     * for the telemetry write area has already been allocated by the caller.
     * The telemetry stream is reset when a new start address is
     * loaded.
     * @param pAddress pointer to the first location of the byte array
     */
    void setStartAddress(unsigned char* pAddress);

    /**
     * Get the starting address of the telemetry write area.
     * @see #setStartingAddress
     * @return the pointer to the first location of the telemetry write area
     */
    unsigned char* getStartAddress(void) const;

    /**
     * Get the current value of the packet counter.
     * @return the packet counter
     */
    unsigned int getPacketCounter(void) const;

    /**
     * Get the current value of the write counter.
     * @return the write counter
     */
    unsigned int getWriteCounter(void) const;

    /**
     * Get the value of the packet sequence count. This is equal to the number of packets 
     * for which write requests have been made since the telemetry stream component 
     * was instantiated.
     * @return the packet sequence count
     */
    unsigned int getSequenceCounter(void) const;

    /**
     * Return true if there is enough space in the telemetry write area to write
     * the argument telemetry packet.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *      if ( pItem->getNumberOfBytes()==0 )
     *          return true;
     *	    if ( (pItem->getNumberOfBytes()+headerSize) greater than (N-writeCounter) )
     *	        return false;
     *	    else
     *          return true; </PRE>
	 * where N is the size of the telemetry write area,
     * <code>writeCounter</code> is the value of the write counter, and
     * <code>headerSize</code> is the size of the PUS header that method
     * <code>write</code> adds to the application data returned by the packet.
     * <p>
     * @param pPacket the telemetry packet to be written to the telemetry stream
     * @return true if there is enough space in the telemetry stream to write
     * the telemetry packet, false otherwise
     */
    virtual bool doesPacketFit(TelemetryPacket* pPacket);

    /**
     * Write one telemetry packet to the telemetry write area.
     * First the PUS header is written to the telemetry write area. Then
     * the telemetry bytes read from the telemetry packet are written in
     * sequence. The write operation begins at
     * location wc in the telemetry write area 
     * where wc is the value of the write counter.
     * Before beginning to write the packet data, a check is made to verify that
     * there is enough space in the telemetry write area. If this is not the case,
     * then an event of type
     * EVT_TM_STREAM_END is generated and the method returns.
     * After successful completion of a write operation, the packet counter is
     * incremented by 1. The sequence count is incremented by one for each write
     * request regardless of whether or not it was successful
     * <p>
     * There is no check on an overflow of either the write or
     * packet counter.
     * <p>
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
     * Perform a class-specific configuration check on the telemetry stream:
     * verify that the size and starting address of the telemetry write area have
     * been loaded.
     * @return true if the telemetry stream is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);

};

#endif
