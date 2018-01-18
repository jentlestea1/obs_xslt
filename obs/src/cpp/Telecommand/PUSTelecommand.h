//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// PUSTelecommand.h
//
// Version	1.0
// Date		15.12.03 (version 1.0)
// Author	A. Pasetti (P&P Software)
//
// Change Record:

#ifndef PUSTelecommandH
#define PUSTelecommandH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Telecommand/Telecommand.h"

/**
 * Base class from which all PUS telecommand classes are derived.
 * This class implements the attributes defined by the more
 * generic <code>Telecommand</code> superclass in a manner that ensures compatibility with the
 * Packet Utilization Standard (PUS). Only the PUS attributes that are relevant to an
 * application process are modelled by this class.
 * <p>
 * The mapping between the attributes defined by the <code>Telecommand</code> superclass
 * and the attributes mandated by the PUS is as follows:<ul>
 * <li>The <i>packet ID</i> PUS attribute has a fixed value for all telecommands in the same
 * application process and it is therefore implemented as a static attribute.</li>
 * <li>The <i>packet sequence control</i> PUS attribute is mapped to the
 * <i>telecommand identifier</i> attribute of the <code>Telecommand</code> superclass.</li>
 * <li>The <i>acknowledge field</i> PUS attribute is mapped to the
 * <i>acknowledge level</i> attribute of the <code>Telecommand</code> superclass.</li>
 * <li>The <i>service type</i> PUS attributes is mapped to the
 * <i>telecommand type</i> attribute of the <code>Telecommand</code> superclass.</li>
 * <li>The <i>service subtype</i> PUS attributes is mapped to the
 * <i>telecommand subtype</i> attribute of the <code>Telecommand</code> superclass.</li>
 * <li>The <i>source</i> PUS attribute is mapped to the
 * <i>telecommand source</i> attribute of the <code>Telecommand</code> superclass.</li>
 * </ul>
 * The mapping of the PUS acknowledge flags onto the acknowledge level attribute is done in
 * a manner that is completely transparent to the clients of this class.
 * <p>
 * This class defines a default structure of the <i>telecommand validity check</i>. 
 * The class defines an internal variable to hold the value of the validity check 
 * code and initializes it to zero. A protected method is offered to set the value
 * of the validity check code. The vallidty check returns "telecommand is valid" if the
 * value of the validity check code is equal to zero. The idea is that validity checking 
 * in a PUS telecommand is done when its application data are loaded (using the
 * <i>raw data load service</i>). During the load operation, the telecommand interprets 
 * the data and checks their validity. If the data are found to be invalid, then
 * the validity check code is set to a non-zero value.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup PUS
 * @ingroup Telecommand
 */
class PUSTelecommand : public Telecommand {

  private:
    static TD_PUSPacketId packetId;
    TD_TelecommandId tcId;
    TD_TelecommandType tcType;
    TD_TelecommandSubType tcSubType;
    TD_TelecommandSource tcSource;
    TD_TelecommandAck ackLevel;
    TD_CheckCode validityCheckCode;

  protected:

    /**
     * Setter method for the validity check code. This method would normally be called
     * by the data load service (method <code>setRawData</code>) when it 
     * detects an inconsistency or some other
     * problem in the data being loaded. The value of the code indicates the
     * type of problem.
     * @param valCheckCode the validity check code
     */
    void setValidityCheckCode(TD_CheckCode valCheckCode);


  public:

    /**
     * Instantiate a PUS telecommand.
     * The telecommand attributes are set as follows: <ul>
     * <li>The telecommand identifier is set to a non-legal value to indicate
     * that the telecommand component is not yet configured</li>
     * <li>The telecommand type is set to a non-legal value to indicate
     * that the telecommand component is not yet configured</li>
     * <li>The telecommand subtype is set to a non-legal value to indicate
     * that the telecommand component is not yet configured</li>
     * <li>The telecommand source is set to a non-legal value to indicate
     * that the telecommand component is not yet configured</li>
     * <li>The acknowledge flags are set to "false" (no acknowledge is required)</li>
     * <li>The validity check code is initialized to zero (telecommand is valid)</li>
     * </ul>
     * Note that the packet identifier (a static attribute) is initialized to an illegal value
     * to indicate that the component is not yet initialized.
     */
    PUSTelecommand(void);

    /**
     * Execute the validity check on the telecommand.
     * This method returns "telecommand valid" if the validity check code
     * is equal to zero. The validity check code is computed in method 
     * <code>setRawData</code>.
     * @see #setValidityCheckCode
     * @return true if the telecommand is valid, false otherwise
     */
    virtual bool isValid(void);

    /**
     * Return the validity check code for the telecommand.
     * @see #setValidityCheckCode
     * @return the validity check code
     */
    virtual TD_CheckCode getValidityCheckCode(void) const;

    /**
     * Getter method for the telecommand packet identifier. The telecommand packet
     * identifier is assumed to be fixed for all telecommands in the same
     * application process. According to the PUS, the packet identifier consists
     * of the following four fields: <ul>
     * <li>The version number: this field is fixed and equal to 0</li>
     * <li>The type: this field is fixed and equal to 1</li>
     * <li>The data field header: this field is fixed and equal to 1 (indicating
     * that a telecommand packet always has a secondary header)</li>
     * <li>The application ID: this field is fixed within the application process and
     * it is equal to the application identifier</li>
     * </ul>
     * @see #setApplicationId
     * @return the packet identifier
     */
    static TD_PUSPacketId getPacketId(void);

    /**
     * Setter method for the application identifier (APID). The APID is used to construct
     * the telecommand packet identifier. The APID is placed in the 11 least-significant bits
     * of the PUS packet identifier. A pseudo-code implementation for this method is as
     * follows: <pre>
     *      packetId = 2**12+2**11;     // set the fixed part of the packet ID
     *      packetId = packetId + apid; // set the APID part of the packet ID </pre>
     * The APID should be smaller than 2**11.
     * @see getPacketId
     * @param apid the identifier of the application for which the telecommand is intended
     */
    static void setApplicationId(TD_APID apid);

    /**
     * Getter method for the telecommand identifier. In this class, the
     * telecommand identifier is identified with the <i>packet sequence
     * control</i> PUS attribute.
     * @return the telecommand identifier
     */
    virtual TD_TelecommandId getTelecommandId(void) const;

    /**
     * Setter method for the telecommand identifier.
     * @see #getTelecommandId
     * @param tcIdentifier the telecommand identifier
     */
    virtual void setTelecommandId(TD_TelecommandId tcIdentifier);

    /**
     * Getter method for the telecommand type. In this class, the
     * telecommand type is identifed with the <i>telecommand service
     * type</i> PUS attribute.
     * @return the telecommand type
     */
    virtual TD_TelecommandType getType(void) const;

    /**
     * Setter method for the telecommand type.
     * @see #getType
     * @param tcType the telecommand type
     */
    virtual void setType(TD_TelecommandType tcType);

    /**
     * Getter method for the telecommand type. In this class, the
     * telecommand subtype is identifed with the <i>telecommand service
     * subtype</i> PUS attribute.
     * @return the telecommand subtype
     */
    virtual TD_TelecommandSubType getSubType(void) const;

    /**
     * Setter method for the telecommand subtype.
     * @see #getSubType
     * @param tcSubType the telecommand subtype
     */
    virtual void setSubType(TD_TelecommandSubType tcSubType);

    /**
     * Getter method for the telecommand source.
     * @return the telecommand source
     */
    virtual TD_TelecommandSource getSource(void) const;

    /**
     * Setter method for the telecommand source.
     * @see #getSource
     * @param tcSource the telecommand source
     */
    virtual void setSource(TD_TelecommandSource tcSource);

    /**
     * Set the value of the acknowledge level for this telecommand.
     * The acknowledge level implements the PUS acknowledge field as
     * follows: <ul>
     * <li>Bit 0 represents the acceptance acknowledge flag</li>
     * <li>Bit 1 represents the start acknowledge flag</li>
     * <li>Bit 2 represents the progress acknowledge flag</li>
     * <li>Bit 3 represents the completion acknowledge flag</li>
     * </ul>
     * Bit 0 is the least-significant bit.
     * @see #getAcknowledgeLevel
     * @param ackLevel the new value of the acknowledge level attribute
     */
    virtual void setAcknowledgeLevel(TD_TelecommandAck ackLevel);

    /**
     * Return the value of the acknowledge level attribute.
     * Note that methods are also provided to return the values of the
     * individual PUS acknowledge flags.
     * @see #setAcknowledgeLevel
     * @return the value of the acknowledge level attribute
     */
    virtual TD_TelecommandAck getAcknowledgeLevel(void) const;

    /**
     * Return the true if acknowledgement of telecommand acceptance is
     * required. The return value is read from the acknowledge level attribute.
     * @see #setAcknowledgeLevel
     * @return the value of the acceptance acknowledge flag
     */
    bool isAcceptanceAckRequired(void) const;

    /**
     * Return the true if acknowledgement of telecommand execution start is
     * required. The return value is read from the acknowledge level attribute.
     * @see #setAcknowledgeLevel
     * @return the value of the start acknowledge flag
     */
    bool isStartAckRequired(void) const;

    /**
     * Return the true if acknowledgement of telecommand execution progress is
     * required. The return value is read from the acknowledge level attribute.
     * @see #setAcknowledgeLevel
     * @return the value of the progress acknowledge flag
     */
    bool isProgressAckRequired(void) const;

    /**
     * Return the true if acknowledgement of telecommand execution completion is
     * required. The return value is read from the acknowledge level attribute.
     * @see #setAcknowledgeLevel
     * @return the value of the completion acknowledge flag
     */
    bool isCompletionAckRequired(void) const;

    /**
     * Perform a class-specific configuration check on the telecommand:
     * verify that the telecommand identifier, telecommand type, the
     * telecommand subtype, the telecommand source, and the packet identifier have a legal value.
     * @return true if the component is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);

};

#endif
