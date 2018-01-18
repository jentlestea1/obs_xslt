//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DataItem16TmWord.h
//
// Version	1.0
// Date		04.12.02
// Author	A. Pasetti (P&P Software)

#ifndef DC_DataItem16TmWordH
#define DC_DataItem16TmWordH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Data/DC_RawDataItem.h"
#include "StructuredTelemetryPacket.h"

/**
 * Telemetry item encapsulating a 16-bit integer accessed through a
 * raw data item. The raw data item is loaded as a configuration parameter.
 * @see DC_RawDataItem
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_DataItem16TmWord : public StructuredTelemetryPacket {

  private:
    DC_RawDataItem* pDataItem;

  public:

    /**
     * Instantiate the telemetry packet component. This constructor initializes the
     * size of the internal telemetry buffer of the superclass to 2 and sets
     * the initial value of the telemetry buffer to 0.
     * A pseudo-code implementation for this constructor is as follows: <PRE>
     *		setNumberOfBytes(2);
     *		setUnsignedShort(0,0);</PRE>
     */
    DC_DataItem16TmWord(void);

    /**
     * Implement the <i>data update service</i>. The internal telemetry buffer
     * is loaded with the value of the data item.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *		tmWord = . . .;  // retrieve the 16-bit value of the data item
     *		setUnsignedShort(0,tmWord);</PRE>
     */
    virtual void update(void);

    /**
     * Load the data item that is the source of the telemetry data for this
     * telemetry packet.
     * The data item is assumed to encapsulate a 16-bit value.
     * @param pDataItem the data item acting as source of telemetry data
     */
    void setDataItem(DC_RawDataItem* pDataItem);

    /**
     * Perform a class-specific configuration check on a
     * <code>DC_DataItem16TmWord</code>: verify that the data item has been
     * loaded.
     * @return true if the object is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);
};

#endif
