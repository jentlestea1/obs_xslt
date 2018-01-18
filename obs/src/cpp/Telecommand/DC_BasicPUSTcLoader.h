//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_BasicPUSTcLoader.h
//
// Version	1.0
// Date		11.01.04
// Author	A. Pasetti (P&P Software)

#ifndef DC_BasicPUSTcLoaderH
#define DC_BasicPUSTcLoaderH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "TelecommandLoader.h"

/**
 * Telecommand loader for PUS telecommands that implements only basic
 * functionalities and checks.
 * This telecommand loader can handle one or more raw telecommand packets.
 * At the time it is activated, it assumes the packets to be placed in a
 * dedicated memory area (the <i>telecommand load area</i>) and assumes 
 * their layout to comply with the layout for telecommand packets stipulated
 * by the PUS. The packets are assumed to be placed in the telecommand area
 * in sequence, one after the other. The layout of the telecommand load area
 * is therefore assumed to be as follows. The first byte represents the
 * number of telecommand packets. Successive bytes represent the telecommand
 * packets stored in sequence and without gaps in between successive packets.
 * <p>
 * When the telecommand loader is 
 * activated, it accesses the telecommand load area and processes the 
 * telecommand packets one by one. For each packet, it retrieves the
 * telecommand type and subtype. It then asks the <i>telecommand 
 * factory</i> for a telecommand component of matching type, it configures 
 * it with the data in the telecommand load area, and finally loads the
 * newly configured component in the
 * telecommand manager. 
 * <p>
 * In a typical usage scenario, this component would be activated periodically
 * to process any telecommand packets that have been received in the previous
 * period. In an alternative scenario, the component is activated by an 
 * interrupt handler when reception of a new telecommand packet has been 
 * detected. Note however that the processing of a telecommand packet by
 * this component can be time-consuming and hence this alternative scenario
 * only is feasible if the time between successive telecommand interrupts
 * is sufficiently long.
 * <p>
 * This telecommand loader is configured with the starting address of
 * the telecommand load area (method <code>setTcLoadAreaStart</code>),
 * with the maximum length of a telecommand packet (method
 * <code>setMaxTcLength</code>), and with the maximum number of telecommand
 * packets that can be placed in the telecommand load area (method
 * <code>setMaxNumberOfTc</code>).
 * All configuration parameters can be changed dynamically. 
 * <p>
 * This telecommand loader does not perform any consistency or validity
 * checks on the raw telecommand data other than verifying that the length
 * of the telecommand packet is less than the maximum value set with method
 * <code>setMaxTcLength</code> and that the number of telecommands is less than
 * the maximum set with method <code>setMaxNumberOfTc</code>. 
 * @todo The implementation of method "activate" must be updated every time a new
 * PUS telecommand class is added to the framework
 * @see PUSTelecommand
 * @see CC_TelecommandManager
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_BasicPUSTcLoader : public TelecommandLoader {

  private:
    unsigned char* tcArea;              // start address of telecommand area
    unsigned int maxTcDataPacketLength;    // max length in bytes of TC packet data field
    unsigned int maxNumberOfTc;         // max number of telecommand packets 

  public:

    /**
     * Instantiate a basic PUS telecommand loader. The class identifier
     * is set. The start address of the telecommand area, the maximum
     * length of the telecommand packets, and the maximum number of telecommand
     * packets are initialized
     * to illegal values to signify that the component is not yet configured.
     */
    DC_BasicPUSTcLoader(void);

    /**
     * Retrieve the raw telecommand packet data, create and configure a telecommand 
     * component for each telecommand packet,
     * and load them in the telecommand manager.
     * The raw telecommand packet data are assumed to consist of an array of
     * bytes stored in the telecommand load area. Their layout is assumed to 
     * conform with the PUS telecommand packet layout.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *      pTcFct = ...    // retrieve telecommand factory
     *      for each tc packet in the tc load area {
     *          if (APID of TC telecommand does not match APID of this application)
     *              continue;
     *          tcType = ...    // read telecommand type from data in telecommand area
     *          tcSubType = ... // read telecommand subtype from data in telecommand area
     *          if (tcType=TYPE_1 and tcSubType=SUBTYPE_a) {
     *            ... // retrieve TC component of matching type and subtype from pTcFct
     *            ... // configure the TC component
     *            ... // load TC packet data into TC component
     *            getTelecommandManager()->load(...);  // load telecommand component
     *          }
     *          if (tcType=TYPE_2 and tcSubType=SUBTYPE_b) {
     *            ... // retrieve TC component of matching type and subtype from pTcFct
     *            ... // configure the TC component
     *            ... // load TC packet data into TC component
     *            getTelecommandManager()->load(...);  // load telecommand component
     *           }
     *           ...
     *       }    </PRE>
     * The loading of telecommand packet data into the TC component is done using
     * the <i>raw data load service</i>. Depending on the telecommand type, either the
     * fast or the safe version of the service is used.
     * The check on APID is performed by comparing the packet ID field in the telecommand packet
     * with the packet ID of the telecommand components as returned by method <code>getPacketId</code>.
     * If the two values do not match, it is assumed that the telecommand packet is intended for
     * some other application and it is simply ignored.
     * <p>
     * For simplicity, the pseudo-code above does not consider error cases.
     * Error cases result in the generation of an error report and in the
     * immediate return of the method.
     * The following error cases are handled: <ul>
     * <li> The number of telecommand packets in the telecommand load area is greater
     * than the maximum value set when the telecommand loader is configured
     * (event report EVT_TOO_MANY_TC_PCKT)</li>
     * <li> The telecommand factory does not return any telecommand component
     * (event report EVT_NO_TC_AVAIL)</li>
     * <li> The telecommand type has an unexpected type 
     * (event report EVT_UNKNOWN_TC_TYPE)</li>
     * <li> The telecommand length exceeds the maximum value set when the telecommand
     * loader is configured
     * (event report EVT_TC_TOO_LONG)</li>
     * </ul>
     * The current implementation can handle the following telecommands: <ul>
     * <li>PUS Test Telecommand (instance of class
     * <code>DC_TestPUSTelecommand</code>)</li>
     * <li>PUS Control Data Reporting Telecommand (instance of class
     * <code>DC_PUSControlDataReporting</code>)</li>
     * <li>PUS Define Data Reporting Telecommand (instance of class
     * <code>DC_PUSDefineDataReporting</code>)</li>
     * </ul>
     * In accordance with the PUS, this method assumes what follows:<ul>
     * <li>the packet ID is located at offset: (startAddress+0)</li>
     * <li>the packet sequence control is located at offset: (startAddress+2)</li>
     * <li>the telecommand type field is located in a telecommand packet at offset: (startAddress+7)</li>
     * <li>the acknowledge bits are located in the least significant four bits of the
     * byte at offset: (startAddress+6)</li>
     * <li>the telecommand subtype is located at offset: (startAddress+8)</li>
     * <li>the packet length field is assumed to be located at offset: (startAddress+4)</li>
     * <li>the packet source ID has a length of <code>sizeof(TD_TelecommandSource)</code></li>
     * <li>the packet error control field is assumed to be 2-byte wide but is ignored. Error checking
     * is assumed to have already been performed upstream</li>
     * </ul>
     */
    virtual void activate(void);

    /**
     * Change the status of the telecommand to "not in use".
     * A pseudo-code implementation for this method is as follows: <pre>
     *      pTelecommand->setInUse(NOT_IN_USE); </pre>
     * @param pTelecommand the telecommand whose resources must be released
     */
    virtual void release(Telecommand* pTelecommand);

    /**
     * Set the start address of the telecommand load area.
     * @param startAddress the start address
     */
    void setTcLoadAreaStart(unsigned char* startAddress);

    /**
     * Set the maximum length of a telecommand packet in number of bytes.
     * The value set here is the total length of the packet including its
     * header. Only values greater than 6 are legal (a PUS header is 6 bytes
     * long).
     * @param maxTcLength the maximum length of a telecommand packet
     */
    void setMaxTcLength(unsigned int maxTcLength);

    /**
     * Getter method for the maximum length of the a telecommand packet.
     * @return the maximum length of a telecommand packet
     */
    unsigned int getMaxTcLength(void) const;

    /**
     * Set the maximum number of telecommand packets that can be handled by this
     * component in an activation cycle.
     * @param max the maximum number of telecommands
     */
    void setMaxNumberOfTc(unsigned int max);

    /**
     * Getter method for the maximum number of telecommand packets that can be handled by this
     * component in an activation cycle.
     * @return the maximum number of telecommands
     */
    unsigned int getMaxNumberOfTc(void) const;

    /**
     * Perform a class-specific configuration check on the telecommand
     * loader: verify that the start address of the telecommand load area, 
     * the maximum length of the telecommand packet have been set, and
     * the maximum number of telecommand packets have been set.
     * @return true if the telecommand loader is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);
};

#endif
