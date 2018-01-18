//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSClearDataReporting.h
//
// Version	1.0
// Date		05.02.04
// Author	A. Pasetti (P&P Software)

#ifndef DC_PUSClearDataReportingH
#define DC_PUSClearDataReportingH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTelecommand.h"

/**
 * PUS telecommand to clear one or more housekeeping and diagnostic 
 * data reporting telemetry packets.
 * This class encapsulates the following subtypes of PUS service number 3:<ul>
 * <li>Subtype 3: clear housekeeping parameter report definition</li>
 * <li>Subtype 4: clear diagnostic parameter report definition</li>
 * </ul>
 * A parameter report definition is cleared by performing the following actions:<ul>
 * <li>The telemetry packet that encapsulates the parameter report is marked
 * "not in use".</li>
 * <li>The telemetry packet is unloaded from the PUS telemetry mode manager.</li>
 * </ul>
 * This class is configured at initialization time by performing the following
 * actions: <ul>
 * <li>The maximum 
 * number of SIDs that can be handled by a single instance of the telecommand
 * is set through method <code>setMaxNumberSID</code>. A call to this
 * method initializes the internal data structures that are used to hold the
 * application data of the telecommand.</li>
 * <li>The PUS telemetry mode manager is loaded as a plug-in component.</li>
 * </ul>
 * During normal operation, configuration is performed using the <i>raw
 * data load service</i>.
 * <p>
 * This telecommand implements a <i>validity check</i> that returns "telecommand
 * not valid" in case an attempt is made to load more application data than fit
 * into the telecommand component or in case the application data are internally
 * inconsistent.
 * <p>
 * Execution of this telecommand can have two outcomes. The telecommand
 * can either have a successful outcome (the return value of <code>doAction</code>
 * is ACTION_SUCCESS) or it can fail (the return value of <code>doAction</code>
 * is ACTION_FAILURE). A failure is declared if any of the SIDs provided to 
 * the telecommand do not correspond to a data reporting packet that is
 * currently in use.
 * <p>
 * The PUS specifies that the first item in the application data of this
 * telecommand is the NSID field. The type of this field is not mandated by the 
 * standard. This class assumes it to be of type <code>unsigned char</code>.
 * The standard also allows this field to be omitted. This class however
 * requires this field to be always present.
 * @todo This class can only take one telemetry mode manager
 * as configuration parameters. If we assume that the same applications can have several
 * telemetry managers (maybe to manage telemetry packets with different levels of RT
 * priority), then it would be necessary to modify this class to accept several
 * telemetry mode managers.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_PUSClearDataReporting : public PUSTelecommand {

  private:
    TD_SID* sid;
    unsigned char* sidOverlay;
    unsigned char maxNsid;
    unsigned char nsid;
    unsigned int lasti;
    DC_PUSTelemetryModeManager* pTmModeManager;

  protected:

    /**
     * Clear the data reporting packets. A data reporting packet is cleared
     * by setting its "in use" status to "packet not in use" and by unloading it
     * from the PUS telemetry mode manager (if it is loaded). This deactivates
     * the telemetry packet and allows the telemetry packet factory to reclaim it and make it
     * available to other clients.
     * A pseudo-code implementation for this method is as follows:<pre>
     *      for (all SIDs stored in the telecommand) {
     *          retrieve data reporting packet from telemetry packet factory;
     *          if (no packet is returned by the factory )
     *              outcome=FAIL;
     *          set status of packet to "not in use"
     *          if (packet is loaded in PUS telemetry mode manager)
     *              unload packet from PUS telemetry mode manager
     *      }
     *      if (outcome==FAIL)
     *          return ACTION_FAILURE;
     *      else
     *          return ACTION_SUCCESS; </pre>
     * The telecommand is configured with a list of SIDs. The data reporting
     * packets are retrieved from the telemetry packet factory (instance of class
     * <code>CC_TelemetryPacketFactory</code>) using their SID. 
     * The "in use" status of the packets is controlled through their
     * <code>setInUse</code> method.
     * @see TelemetryPacket#setInUse
     * @see CC_TelemetryPacketFactory
     * @see DC_PUSTelemetryModeManager
     * @see PunctualAction#execute
     * @return always returns a "telecommand successfully executed" code
     */
    virtual TD_ActionOutcome doAction(void);

  public:

    /**
     * Instantiate a clear data reporting PUS telecommand.
     * The class identifier is set.
     * The values of the internal data structure that is used to hold the telecommand
     * application data is initialized to illegal values to signify that the telecommand
     * is not yet configured. The telecommand type is set to PUS_TYPE_DATA_REP.
     */
    DC_PUSClearDataReporting(void);

    /**
     * Set the maximum number of SIDs that can be processed by this telecommand.
     * This is an initialization method that should only be called once.
     * A call to this method causes the internal data structures where the SIDs are
     * held to be allocated and initialized. Only positive values of the method argument
     * are legal.
     * @param max the maximum number of SIDs
     */
    void setMaxNumberSID(unsigned char max);

    /**
     * Implementation of the raw data load service. This method would normally
     * be called by a telecommand loader to load the application data into the
     * the telecommand component. This method interprets the raw data as they are
     * loaded and uses them to construct the sequence of SIDs of the data reporting
     * packets that have to be cleared. This method assumes that the
     * raw data are loaded in sequence starting from the first one (i.e. the value 
     * of i in the first call is zero and succesive calls use values of i that 
     * are incremented by one at each call). The value of i is also constrained to 
     * lie in the range [0,N] where N is computed as follows: <pre>
     *      N = M*sizeof(TD_SID)  </pre>
     * where M is the maximum number of SIDs defined by method <code>setMaxNumberSID</code>.
     * If the number of SIDs in the telecommand packet exceeds the maximum defined
     * with method <code>setMaxNumberSID</code>, the telecommand
     * is declared to be invalid with validity check code equal to VC_TOO_MANY_SIDS. 
     * If an attempt is made to load a greater number of raw data, the telecommand
     * is declared to be invalid with validity check code equal to VC_TOO_MANY_RAW_DATA. 
     * Finally, the total number of loaded raw data T
     * must be consistent with the number of SIDs (the first byte in the telecommand
     * packet). If this
     * is not the case, then the telecommand is declared invalid with validity check code
     * equal to VC_INCONSISTENT_RAW_DATA.
     * @see #getNumberOfRawData
     * @param i the index of the raw telecommand data
     * @param d the raw data
     */
    virtual void setRawData(unsigned int i, unsigned char d);

    /**
     * Return the number of raw data bytes that can be loaded with the
     * raw telecommand data load service.
     * The value returned by this class is equal to: <code>M*sizeof(TD_SID)+1</code>
     * where M is the maximum number of SIDs defined by method <code>setMaxNumberSID</code>.
     * @see #setRawData
     * @return the number of raw data bytes to be loaded with the raw
     * data load service
     */
    virtual unsigned int getNumberOfRawData(void) const;

    /**
     * Load the PUS telemetry mode manager.
     * @see #doAction
     * @param pTmModeManager the PUS telemetry mode manager
     */
    void setPUSTelemetryModeManager(DC_PUSTelemetryModeManager* pTmModeManager);

    /**
     * Getter method for the PUS telemetry mode manager.
     * @see #setPUSTelemetryModeManager
     * @return the PUS telemetry mode manager
     */
    DC_PUSTelemetryModeManager* getPUSTelemetryModeManager() const;

    /**
     * Perform a class-specific configuration check on the telecommand:
     * check that the maximum number of SIDs that can be processed by the telecommand 
     * has been set and that the telemetry manager and telemetry mode manager
     * have been loaded.
     * @return true if the telecommand is configured, false otherwise
     */
    virtual bool isObjectConfigured(void);

};

#endif 
