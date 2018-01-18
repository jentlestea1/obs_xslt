//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSTcVerificationPacket.h
//
// Version	1.0
// Date		01.12.02
// Author	A. Pasetti (P&P Software)

#ifndef DC_PUSTcVerificationPacketH
#define DC_PUSTcVerificationPacketH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Telemetry/PUSTelemetryPacket.h"

/**
 * PUS telemetry packet implementing the telecommand verification service.
 * This class can model any of the telecommand verification service
 * packets. The value of the subtype attribute determines which packet is
 * being modeled.
 * <p>
 * This class is intended to be used by a component that monitors
 * the execution status of a telecommand. Upon detecting a change in
 * the execution status of a telecommand, this component configures an
 * instance of <code>PUSTcVerificationPacket</code> in accordance with the
 * detected state of the telecommand execution. The <code>PUSTcVerificationPacket</code>
 * instance should then be loaded into the <i>telementry manager</i> for immediate
 * dispatch to the telemetry channel.
 * <p>
 * A telemetry packet of type <code>PUSTcVerificationPacket</code> can contain two or
 * three fields. It contains two fields if it reports a telecommand success. It contains three fields
 * if it reports a telecommand failure. The two fields that are always present are
 * the packet identifier of the telecommand and the packet sequence control of the telecommand.
 * The third field is a single error code that conveys information about the reason of
 * the telecommand failure.
 * @todo construct a test case for this class.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_PUSTcVerificationPacket : public PUSTelemetryPacket {

  private:
    unsigned int packetLengthSuccess;
    unsigned int packetLengthFailure;
    unsigned char* tmByte;

  public:

    /**
     * Instantiate a PUS Telecommand Verification telemetry packet.
     * The class identifier is set. The telemetry type attributes
     * is set to PUS_TYPE_TC_VER. The error code is set to zero.
     */
    DC_PUSTcVerificationPacket(void);

    /**
     * Return the number of bytes managed by this telemetry packet.
     * The number of bytes is computed as follows. If the telemetry packet
     * is being used to report a successful telecommand execution, then its
     * number of bytes is given by: <pre>
     *      sizeof(TD_PUSPacketId)+sizeof(TD_TelecommandId) </pre>
     * If the telemetry packet
     * is being used to report a successful telecommand execution, then its
     * number of bytes is given by: <pre>
     *      sizeof(TD_PUSPacketId)+sizeof(TD_TelecommandId)+sizeof(TD_CheckCode) </pre>
     * Note that <code>TD_CheckCode</code> is the type of the error code field.
     * @see #setErrorCode
     * @return number of bytes in this telemetry packet
     */
    virtual unsigned int getNumberOfBytes(void);

    /**
     * Implement the  <i>data acquisition service</i> for the PUS telecommand verification
     * packet. The bytes associated to this telemetry packet are returned according to the
     * following algorithm: <pre>
     *      if ( (subtype == PUS_ST_TC_VER_ACC_SC) ||
     *           (subtype == PUS_ST_TC_EXE_STR_SC) ||
     *           (subtype == PUS_ST_TC_EXE_PRO_SC) ||
     *           (subtype == PUS_ST_TC_EXE_END_SC) ) {
     *          return TC packet ID;
     *          return TC packet sequence control;
     *       } else {
     *          return TC packet ID;
     *          return TC packet sequence control;
     *          return error code;
     *       } </pre>
     * The TC packet ID, TC packet sequence control, and the error code are transferred byte
     * by byte starting from the byte with the highest address.
     * @return value of n-th telemetry byte
     * @param n the telemetry byte to be returned (starting with byte 0)
     */
    virtual unsigned char getUnsignedByte(unsigned int n);

    /**
     * Return the error code that describes the reason for the telecommand failure.
     * This field is only meaningful when the telemetry packet is being used to
     * describe a telecommand failure. The default value of the error code is zero.
     * @return the error code
     */
    TD_CheckCode getErrorCode();

    /**
     * Set the error code that describes the reason for the telecommand failure.
     * @see #getErrorCode
     * @param errCode the error code
     */
    void setErrorCode(TD_CheckCode errCode);

    /**
     * Return the identifier of the telecommand for which the execution verification
     * report is constructed.
     * @return the telecommand identifier
     */
    TD_TelecommandId getTelecommandId();

    /**
     * Set the identifier of the telecommand for which the execution verification
     * report is constructed.
     * @param tcId the telecommand identifier
     */
    void setTelecommandId(TD_TelecommandId tcId);

    /**
     * Implement the <i>data update service</i> for the PUS telecommand verification packet.
     * This type of packet is configured dynamically by the component that monitors the
     * execution status of the telecommands. Its update service is therefore implemented
     * as a dummy method that returns without taking any action.
     */
    virtual void update(void);

};

#endif
