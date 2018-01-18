//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TelemetryStream.h
//
// Version	1.0
// Date		02.03.03 
// Author	A. Pasetti (P&P Software)
//
// Change Record:

#ifndef TelemetryStreamH
#define TelemetryStreamH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"

/**
 * Base class from which all telemetry stream classes are derived.
 * A <i>telemetry stream</i> represents a
 * data sink to which individual <i>telemetry packets</i> can be written.
 * The telemetry packets are assumed to be encapsulated in objects of type
 * <code>TelemetryPacket</code>.
 * This is an abstract class since the mechanism through which the telemetry
 * items are written to a physical telemetry channel vary widely across
 * applications.
 * <p>
 * The basic service provided by this class is implemented by a <code>write</code>
 * operation that takes an instance of type <code>TelemetryPacket</code> as
 * an argument. An application would implement this operation to write the content
 * of the telemetry packet to a physical telemetry channel.
 * Additionally, housekeeping operations are provided to manage the telemetry
 * stream.
 * These operations are designed to be compatible with a wide range of
 * concrete telemetry stream mechanisms.
 * Given the diversity of such mechanisms, this means that the semantics of
 * the operations is only weakly defined in this base class. More specific
 * definitions are left to the sub-classes. There is however one important constraint
 * on the implementations provided by the sub-classes. Some of the methods declared
 * by class <code>TelemetryStream</code> receive as an argument a pointer to the
 * telemetry packet whose content must be written to the telemetry data sink.
 * Telemetry packets are in principle allocated dynamically by a <i>telemetry packet
 * factory</i>. Hence, if the telemetry stream needs to buffer information about the
 * telemetry packet, it should do so by copying its content to an internal buffer. It
 * should <i>not</i> try to store the pointer to the telemetry packet in order to
 * access it at a later time.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup Telemetry
 */
class TelemetryStream : public CC_RootObject {

  public:

    /**
     * Instantiate a telemetry stream component. This constructor returns without taking
     * any action.
     */
    TelemetryStream(void);

    /**
     * Reset the telemetry stream. The effect of a reset are
     * implementation-specific.
     * This class provides a default implementation that does not take any
     * action.
     */
    virtual void reset(void);

    /**
     * Flush the telemetry stream. The effect of a flush are
     * implementation-specific.
     * This class provides a default implementation that does not take any
     * action.
     * This operation is typically useful when the telemetry stream maintains
     * an internal buffer to which it writes the telemetry data. The <code>flush</code>
     * operation can then be implemented to emtpy the buffer and write its content
     * to a telemetry channel.
     */
    virtual void flush(void);

    /**
     * Return the capacity of the telemetry stream.
     * Some telemetry stream may have a capacity attribute associated to them.
     * This method returns its value.
     * This class provides a default implementation that returns MAX_INT.
     * @see MAX_INT
     * @return the capacity of the telemetry stream
     */
    virtual unsigned int getCapacity(void);

    /**
     * Check whether there is enough space in the telemetry stream for writing
     * the argument telemetry packet.
     * Some telemetry streams may have a limited capacity.
     * Before performing a write operation, it may therefore be necessary to
     * check whether there is enough space in the
     * telemetry stream for the data that it is desired to write.
     * This operation checks whether there is enough space for writing the
     * content of the argument telemetry packet.
     * This class provides a default implementation that always returns
     * "enough space".
     * @param pTmPacket the telemetry packet to be written to the telemetry stream
     * @return true if there is enough space in the telemetry stream to write
     * n bytes, false otherwise
     */
    virtual bool doesPacketFit(TelemetryPacket* pTmPacket);

    /**
     * Write the content of the telemetry packet to the telemetry stream.
     * @param tmItem the telemetry packet to be written to the telemetry stream
     */
    virtual void write(TelemetryPacket* tmItem) = 0;
};

#endif
