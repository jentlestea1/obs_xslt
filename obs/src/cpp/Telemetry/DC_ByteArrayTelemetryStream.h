//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_ByteArrayTelemetryStream.h
//
// Version	1.0
// Date		04.03.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)

#ifndef DC_ByteArrayTelemetryStreamH
#define DC_ByteArrayTelemetryStreamH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Data/DC_DataItem.h"
#include "TelemetryStream.h"

/**
 * Telemetry stream that writes the telemetry data to an array of
 * bytes (the <i>byte array</i>). Only the telemetry bytes in the telemetry
 * item are written to the stream. Header information (the telemetry packet
 * destination, time tag, type and subtype) are ignored. The byte array is characterized by
 * a <i>starting address</i> and by a <i>size</i>. The starting
 * address and the size are settable configuration parameters.
 * <p>
 * This class maintains a <i>write counter</i>. The write counter
 * is reset to 0 by
 * a call to operation <code>reset</code> or <code>flush</code>.
 * It is incremented every
 * time a byte is written to the byte array.
 * If its value is smaller than the size of the byte array, then the
 * write counter points
 * to the location in the byte array where the next telemetry data
 * will be written. Write requests that cannot be processed because
 * there is not enough space in the byte array have no effect.
 * It is the responsibility of the user to perform reset or flush
 * operations when the byte array has been completely filled.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_ByteArrayTelemetryStream : public TelemetryStream {

  private:
      unsigned char* tmData;     // the byte array
      unsigned int size;        // the size of the byte array in bytes
      unsigned int writeCounter;

  public:

    /**
     * Instantiate the component. The class identifier is set. The size and
     * starting address of the byte array are set to illegal values to signify
     * that the component is not yet configured. The write counter is set
     * to zero.
     */
    DC_ByteArrayTelemetryStream(void);

    /**
     * Reset the telemetry stream. The write counter is reset to 0.
     */
    virtual void reset(void);

    /**
     * The flush operation is equivalent to a reset operation.
     * @see #reset
     */
    virtual void flush(void);

    /**
     * Return the capacity of the telemetry stream. The capacity of this
     * telemetry stream is equal to the size in bytes of the byte array.
     * @return the size of the byte array in number of bytes
     */
    virtual unsigned int getCapacity(void);

    /**
     * Set the capacity of the telemetry stream. The capacity of this
     * telemetry stream is equal to the size in bytes of the byte array.
     * If s is the staring address of the byte array (loaded with method
     * <code>setStartingAddress</code>) and if L is the byte array size
     * defined with this method, then the i-th location of the byte array is
     * internally accessed as s[i] where i must be in the range [0,L-1].
     * It is the responsibility of the user to ensure that the locations thus
     * accessed are free for use by this telemetry stream component.
     * Note that the size of the byte array should be greater than 0.
     * @see #setStartingAddress
     * @param n the size of the byte array in number of bytes
     */
    void setCapacity(unsigned int n);

    /**
     * Set the starting address of the byte array. This component does not
     * perform any memory allocation operation. It assumes that the memory
     * for the byte array has already been allocated by the caller of this
     * method.
     * @param pAddress pointer to the first location of the byte array
     */
    void setStartingAddress(unsigned char* pAddress);

    /**
     * Get the starting address of the byte array.
     * @return the pointer to the first location of the byte array
     */
    unsigned char* getStartingAddress(void) const;

    /**
     * Return true if there is enough space in the byte array to write
     * the argument telemetry packet.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *	    if ( pItem->getNumberOFBytes() greater than (N-writeCounter) )
     *	        return false;
     *	    else
     *          return true; </PRE>
	 * where N is the size of the byte array and
     * <code>writeCounter</code> is the value of the write counter.
     * <p>
     * @param pPacket the telemetry packet to be written to the telemetry stream
     * @return true if there is enough space in the telemetry stream to write
     * the telemetry packet, false otherwise
     */
    virtual bool doesPacketFit(TelemetryPacket* pPacket);

    /**
     * Write one telemetry packet to the byte array.
     * The telemetry bytes read from the telemetry packet are written starting at
     * location wc in the byte array
     * where wc is the value of the write counter.
     * When the end of the byte array is reached, the method returns.
     * @param pItem the telemetry packet to be written to the telemetry stream
     */
    virtual void write(TelemetryPacket* pItem);

    /**
     * Perform a class-specific configuration check on the telemetry stream:
     * verify that the size and starting address of the byte array have
     * been loaded.
     * @return true if the telemetry stream is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);

};

#endif
