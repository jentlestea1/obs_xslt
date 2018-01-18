//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_CycleDataItem16TmStream.h
//
// Version	1.0
// Date		05.10.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)
//
// Change Record:

#ifndef DC_CycleDataItem16TmStreamH
#define DC_CycleDataItem16TmStreamH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Data/DC_RawDataItem.h"
#include "TelemetryStream.h"

/**
 * Telemetry stream that writes the content of a telemetry packet to
 * a set of 16-bit words encapsulated in data items.
 * The data items will normally encapsulate hardware
 * registers representing the telemetry interface. The data items
 * are implemented as instances of class <code>DC_RawDataItem</code>.
 * <p>
 * This class maintains a <i>write counter</i>. The write counter has
 * a value between 0 and N-1 where N is the number of data items
 * managed by the telemetry stream. The counter is reset to 0 by
 * a call to operation <code>reset</code> or <code>flush</code>.
 * It is incremented by 1 every time a new 16-bit word is written to
 * a data item. When the write counter reaches the value of N, no
 * further items can be written and write requests remain without
 * effect until a <code>reset</code> or <code>flush</code> is performed.
 * <p>
 * The number of data items is a user-defined parameter. It must be set
 * as part of the component configuration.
 * @see DC_RawDataItem
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_CycleDataItem16TmStream : public TelemetryStream {

  private:
      DC_RawDataItem** pDataItem;       // array of pointers to DC_RawDataItem
      unsigned int nDataItems;          // number of data items
      unsigned int writeCounter;

  public:

    /**
     * Instantiate the component. The class identifier is set. The number of data
     * items is set to an illegal
     * value to signify that the component is not yet configured.
     */
    DC_CycleDataItem16TmStream(void);

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
     * Return the number of data items managed by this telemetry stream.
     * The number of data items is set with method <code>setNumberOfDataItems</code>
     * @see #setNumberOfDataItems
     * @return the size of the telemetry stream (the number of data items)
     */
    virtual unsigned int getCapacity(void);

    /**
     * Set the number of data items managed by this telemetry stream.
     * This method causes the memory for the data structure holding the
     * data items to be allocated. After the successful allocation of the
     * memory, the telemetry stream is reset.
     * <p>
     * This is an initialization method. It should be called before the
     * telemetry stream is used the first time and it should not be called more
     * than once.
     * The number of data items should be greater than 0.
     * @see #getSize
     * @param n the number of data items
     */
    void setNumberOfDataItems(unsigned int n);

    /**
     * Set the n-th data item.
     * The data item are the locations to which the bytes written from the
     * telemetry packet are written.
     * The index n must lie in the interval [0,N-1] where N is the number of data
     * items managed by this telemetry stream (the return value of method
     * <code>getSize</code>). Use of an out-of-range index has no effect.
     * @see #setNumberOfDataItems
     * @param n the index of the data item to be set
     * @param pDataItem the data item to be associated to the index-th location
     * of the telemetry stream
     */
    void setDataItem(unsigned int n, DC_RawDataItem* pDataItem);

    /**
     * Return true if it is possible to write the entire content of the argument
     * telemetry packet to the data item.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *	    if ( pItem->getNumberOfBytes() greater than 2*(N-writeCounter) )
     *	        return false;
     *	    else
     *		    return true; </PRE>
	 * where N is the number of data items in the telemetry stream and
     * <code>writeCounter</code> is the value of the write counter.
     * <p>
     * @param pPacket the telemetry packet to be written to the telemetry stream.
     * @return true if there is enough space in the telemetry stream to write
     * n bytes, false otherwise
     */
    virtual bool doesPacketFit(TelemetryPacket* pPacket);

    /**
     * Write the telemetry packet content to the data items.
     * Only the telemetry bytes in the telemetry packet are written (the header
     * information - the telemetry packet time tag, destination, type and subtype -
     * are not written).
     * A pseudo-code implementation for this method is as follows: <PRE>
     *      for (i=0; i<(pItem->getNumberOfBytes()-1); i=i+2)
     *          collect the i-th and (i+1)-bytes from pItem
     *          if ( writeCounter smaller than N-1 )
     *	            combine the i-th and (i+1)-bytes in one 16-bit word;
     *              write the 16-bit word to writeCounter-th data item;
     *              writeCounter++;
     *          else
     *              return; </PRE>
	 * where N is the number of data items in the telemetry stream.
     * The merge of two successive telemetry bytes from the telemetry packet
     * into one single 16-bit word is done by overlaying the i-th byte with the
     * least significant byte of the data item word and the (i+1)-th byte with
     * the most significant byte.
     * @param pItem the telemetry packet to be written to the
     * telemetry stream.
     */
    virtual void write(TelemetryPacket* pItem);

    /**
     * Perform a class-specific configuration check on the telemetry stream:
     * verify that the number of data items has been set and that all
     * data items have been loaded.
     * @return true if the telemetry stream is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);

};

#endif
