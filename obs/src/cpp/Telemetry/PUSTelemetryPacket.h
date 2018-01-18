//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// PUSTelemetryPacket.h
//
// Version	1.0
// Date		01.12.02
// Author	A. Pasetti (P&P Software)

#ifndef PUSTelemetryPacketH
#define PUSTelemetryPacketH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Telemetry/TelemetryPacket.h"

/**
 * Base class from which all PUS telemetry packet classes are derived.
 * A PUS telemetry packet class encapsulate a packet of telemetry data
 * that is compliant with the Packet Utilization Stadard (PUS). PUS
 * telemetry packet classes are organized as <i>telemetry packets</i> in the
 * sense that this class extends class <code>TelemetryPacket</code>. Class
 * <code>TelemetryPacket</code> defines a <i>data acquisition service</i> to
 * acquire a stream of telemetry bytes. From the point of view of the
 * <code>PUSTelemetryPacket</code> class, this stream of bytes represent
 * the source data part of the PUS packet encapsulated by the class.
 * The mapping between the attributes defined by the <code>TelemetryPacket</code> superclass
 * and the attributes mandated by the PUS is as follows:<ul>
 * <li>The <i>packet ID</i> PUS attribute has a fixed value for all telemetry packet
 * originating from the same
 * application process and it is therefore implemented as a static attribute.</li>
 * <li>The <i>service type</i> PUS attribute is mapped to the <i>telemetry packet
 * type</i> attribute of the <code>TelemetryPacket</code> class.</li>
 * <li>The <i>service subtype</i> PUS attribute is mapped to the <i>telemetry packet
 * subtype</i> attribute of the <code>TelemetryPacket</code> class.</li>
 * <li>The <i>destination</i> PUS attribute is mapped to the <i>telemetry packet
 * destination</i> attribute of the <code>TelemetryPacket</code> class.</li>
 * <li>The <i>time</i> PUS attribute is mapped to the <i>telemetry packet
 * time tag</i> attribute of the <code>TelemetryPacket</code> class.</li>
 * </ul>
 * Since most telemetry packets in an application can be expected to have the
 * same destination, this class also defines a static <i>default destination</i>
 * attribute.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup PUS
 * @ingroup Telemetry
 */
class PUSTelemetryPacket : public TelemetryPacket {

  private:
    static TD_TelemetryDestination defaultDestination;
    static TD_PUSPacketId packetId;
    static ObsClock* pObsClock;
    TD_TelemetryType type;
    TD_TelemetrySubType subType;
    TD_TelemetryDestination dest;
    TD_ObsTime timeTag;

  public:

    /**
     * Instantiate a PUS telemetry packet component.
     * The telemetry attributes are set as follows: <ul>
     * <li>The telemetry time tag is set to a non-legal value to indicate
     * that the telemetry packet component is not yet configured</li>
     * <li>The telemetry type is set to a non-legal value to indicate
     * that the telemetry component is not yet configured</li>
     * <li>The telemetry subtype is set to a non-legal value to indicate
     * that the telemetry packet component is not yet configured</li>
     * <li>The telemetry destination is set equal to the default destination</li>
     * </ul>
     * Note that the packet identifier (a static attribute) is initialized to an illegal value
     * to indicate that the component is not yet initialized.
     */
    PUSTelemetryPacket(void);

    /**
     * Setter method for the application identifier (APID). The APID is used to construct
     * the telemetry packet identifier. The APID is placed in the 11 least-significant bits
     * of the PUS packet identifier. A pseudo-code implementation for this method is as
     * follows: <pre>
     *      packetId = 2**11;           // set the fixed part of the packet ID
     *      packetId = packetId + apid; // set the APID part of the packet ID </pre>
     * The APID should be smaller than 2**11.
     * @see getPacketId
     * @param apid the identifier of the application generating the telemetry packet
     */
    static void setApplicationId(TD_APID apid);

    /**
     * Setter method for the telemetry packet type.
     * @param tmType the telemetry packet type
     */
    virtual void setType(TD_TelemetryType tmType);

    /**
     * Setter method for the telemetry packet sub-type.
     * @param tmSubType the telemetry packet sub-type
     */
    virtual void setSubType(TD_TelemetrySubType tmSubType);

    /**
     * Setter method for the telemetry packet destination.
     * @param tmDest telemetry packet destination
     */
    virtual void setDestination(TD_TelemetryDestination tmDest);

    /**
     * Getter method for the telemetry packet identifier. The telemetry packet
     * identifier is assumed to be fixed for all telemetry packets in the same
     * application process. According to the PUS, the packet identifier consists
     * of the following four fields: <ul>
     * <li>The version number: this field is fixed and equal to 0</li>
     * <li>The type: this field is fixed and equal to 0</li>
     * <li>The data field header: this field is fixed and equal to 1 (indicating
     * that a telemetry packet always has a secondary header)</li>
     * <li>The application ID: this field is fixed within the application process and
     * it is equal to the application identifier</li>
     * </ul>
     * @see #setApplicationId
     * @return the packet identifier
     */
    static TD_PUSPacketId getPacketId(void);

    /**
     * Getter method for the telemetry packet default destination.
     * @return the telemetry packet default destination
     */
    static TD_TelemetryDestination getDefaultDestination(void);

    /**
     * Setter method for the telemetry packet default destination.
     * @param defDest the telemetry packet default destination
     */
    static void setDefaultDestination(TD_TelemetryDestination defDest);

    /**
     * Getter method for the telemetry type.
     * @return the telemetry sub-type
     */
    virtual TD_TelemetryType getType(void) const;

    /**
     * Getter method for the telemetry sub-type.
     * @return the telemetry sub-type
     */
    virtual TD_TelemetrySubType getSubType(void) const;

    /**
     * Getter method for the telemetry packet time tag.
     * @return the telemetry packet time
     */
    virtual TD_ObsTime getTimeTag(void) const;

    /**
     * Setter method for the telemetry packet time tag.
     * @param timeTag the telemetry packet time tag
     */
    virtual void setTimeTag(TD_ObsTime timeTag);

    /**
     * Getter method for the telemetry packet destination.
     * @return the telemetry packet destination
     */
    virtual TD_TelemetryDestination getDestination(void) const;

    /**
     * Load the OBS Clock component. Telemetry packets may need access to
     * this component in order to time-stamp the telemetry data as they are collected.
     * @param pObsClock the OBS Clock component.
     */
    static void setObsClock(ObsClock* pObsClock);

    /**
     * Return the OBS Clock component.
     * @see #setObsClock
     * @return the OBS Clock component.
     */
    static ObsClock* getObsClock(void);

    /**
     * Perform a class-specific configuration check on the telemetry packet:
     * verify that the type, the
     * sub type, the destination, the time tag, and the packet identifier have a legal value.
     * @return true if the component is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);

};

#endif
