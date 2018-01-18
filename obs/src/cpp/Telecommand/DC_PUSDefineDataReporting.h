//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSDefineDataReporting.h
//
// Version	1.0
// Date		05.01.04
// Author	A. Pasetti (P&P Software)

#ifndef DC_PUSDefineDataReportingH
#define DC_PUSDefineDataReportingH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTelecommand.h"

/**
 * PUS telecommand to define the housekeeping and diagnostic 
 * data reporting telemetry packets.
 * This class encapsulates the following subtypes of PUS service number 3:<ul>
 * <li>Subtype 1: define new housekeeping parameter report </li>
 * <li>Subtype 2: define new diagnostic parameter report </li>
 * </ul>
 * This class defines an internal buffer to store the application data 
 * that define the telemetry packet. The maximum size of this buffer is
 * a configuration parameter that must be set at application initialization 
 * time (method <code>setNumberOfRawData</code>). 
 * <p>
 * During normal operation, configuration is performed using the <i>raw
 * data load service</i>. Since in most cases the amount of data to be loaded
 * can be large, the more efficient (but less safe) implementation of this service
 * is used.
 * <p>
 * This telecommand implements a <i>validity check</i> that returns "telecommand
 * not valid" in case an attempt is made to load more application data than fit
 * into the telecommand component.
 * <p>
 * Execution of this telecommand consists in retrieving a free data reporting telemetry packet
 * from the telemetry packet factory, configuring it with the application
 * data and loading it in the PUS telemetry mode manager. The PUS telemetry mode
 * manager is loaded as a plug-in component at configuration time. Execution can have 
 * two outcomes. 
 * The telecommand
 * can have a successful outcome (the return value of <code>doAction</code>
 * is ACTION_SUCCESS) or it can fail for the following reasons:
 * <ul>
 * <li>No free packet could be found in the
 * telemetry packet factory (the return value of <code>doAction</code>
 * is PACKET_NOT_FOUND)   </li>
 * <li>The packet could not be loaded in the
 * telemetry mode manager (the return value of <code>doAction</code>
 * is PUS_MODE_MAN_FULL)   </li>
 * <li>The internal structure of the application data was found to be 
 * inconsistent (the return value of <code>doAction</code>
 * is APP_DATA_INCONSISTENT)   </li>
 * </ul> . 
 * No event reports are generated in case of failure as it is assumed that
 * this is done by the calling client.
 * <p>
 * Note that this class does not try to interpret its application data. It simply passes
 * them on as unformatted raw data to the data reporting telemetry packet.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_PUSDefineDataReporting : public PUSTelecommand {

  private:
    unsigned char* data;
    unsigned int maxNumberData;
    unsigned int numberData;
    DC_PUSTelemetryModeManager* pTmModeManager;

  protected:

    /**
     * Use the application data to configure and load a data reporting telemetry packet.
     * This method queries the dynamic telemetry packet factory for a new
     * data reporting packet. If it obtains it, it loads it with the application
     * data and then loads it in the PUS telemetry mode manager.
     * If either of these two operations fails, the method returns with a
     * failure code (see class comment).
     * <p>
     * In order to retrieve a free packet from the telemetry packet factory 
     * with the appropriate characteristics, this method has to extract the
     * following data from the application data: <ul>
     * <li>The number of fixed-length arrays</li>
     * <li>The size of the packet value buffer</li>
     * </ul>
     * The above figures are computed by processing the content of the application
     * data. The computation makes certain assumptions about the structure of the
     * application data. The assumptions are the same as are made in class
     * <code>DC_PUSDataReportingPacket</code>.
     * Some consistency checks are performed during the processing of the
     * application data. If these fail, then the method returns with a failure
     * code (see class comment). The consistency check will catch situations where
     * the number of fixed-length arrays or the number of parameters defined by
     * the application data is not consistent with the length of the application
     * data as defined when calling method <code>setRawData</code>.
     * @see PunctualAction#execute
     * @return action outcome code (see class comment)
     */
    virtual TD_ActionOutcome doAction(void);

  public:

    /**
     * Instantiate a define data reporting PUS telecommand.
     * The class identifier is set.
     * The values of the internal data structure that is used to hold the telecommand
     * application data is initialized to illegal values to signify that the telecommand
     * is not yet configured. The telecommand type is set to PUS_TYPE_DATA_REP.
     */
    DC_PUSDefineDataReporting(void);

    /**
     * Set the maximum size of the application data array. The maximum size is specified as the
     * maximum number of bytes of the application data. 
     * This is an initialization method that should only be called once.
     * A call to this method causes the internal data structures of the
     * telecommand to be allocated and initialized. Only positive values of the method argument
     * are legal.
     * @param max the maximum size of the application data in number of bytes
     */
    void setNumberOfRawData(unsigned int max);

    /**
     * Get the maximum size (in number of bytes) of the application data array. 
     * @see #setNumberOfRawData
     * @return the maximum size of the application data in number of bytes
     */
    virtual unsigned int getNumberOfRawData(void);

    /**
     * Implementation of the raw data load service. 
     * This method copies the argument array into an internal array. The number of
     * bytes n in the argument array must be less than the maximum value set
     * with method <code>setNumberOfRawData</code>. 
     * If an attempt is made to load a greater number of raw data, then the telecommand
     * is declared to be invalid with validity check code equal to VC_TOO_MANY_RAW_DATA. 
     * @param d the array holding the raw data
     * @param n the number of items in array d
     */
    virtual void setRawData(unsigned char* d, unsigned int n);

    /**
     * Return the number of application data bytes that were loaded with the
     * last call to method <code>setRawData</code>. The number returned by this
     * method is the same as the value of the argument n in the call to method
     * <code>setRawData</code>.
     * @see #setRawData
     * @return the number of application data bytes in the currently loaded packet
     */
    virtual unsigned int getNumberOfApplicationData(void) const;

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
     * check that the maximum number of raw data has been set and that the
     * PUS telemetry mode manager has been loaded.
     * @return true if the telecommand is configured, false otherwise
     */
    virtual bool isObjectConfigured(void);

};

#endif 
