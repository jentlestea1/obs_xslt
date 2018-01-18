//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// PUSDumpMemory.h
//
// Version	1.0
// Date		05.01.04
// Author	A. Pasetti (P&P Software)

#ifndef PUSDumpMemoryH
#define PUSDumpMemoryH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTelecommand.h"

/**
 * Base class for PUS telecommands to set up a memory dump either with base plus offset or absolute address.
 * This class encapsulates the commonalities for the following subtypes of PUS service number 6:<ul>
 * <li>Subtype 3: dump memory using base plus offset</li>
 * <li>Subtype 5: dump memory using absolute addresses</li>
 * </ul>
 * This class defines an internal buffer to store the application data 
 * that define the telemetry packet. The maximum size of this buffer is
 * a configuration parameter that must be set at application initialization 
 * time (method <code>setNumberOfRawData</code>). This and other internal data structured
 * are declared <code>protected</code> in order to facilitate the implementation of
 * concrete subclasses.
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
 * No implementation for the execution action of this telecommand is provided. This
 * depends on whether the memory dump is of the "absolute address" or the "base address
 * plus offset" type and must therefore be provided by the concrete subclasses.
 * <p>
 * The PUS leaves some leeway in the definition of the structure of the application
 * data for memory dump telecommands. This implementation makes the same
 * assumptions as defined in the class comment of class <code>PUS_MemoryDump</code>.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class PUSDumpMemory : public PUSTelecommand {

  protected:

    /**
     * The buffer where the application data are stored
     */
    unsigned char* data;
    
    /**
     * The size in number of bytes of the <code>data</code> buffer
     */
    unsigned int maxNumberData;

    /**
     * The size in the number of bytes of the currently loaded application data
     */
    unsigned int numberData;

    /**
     * The telemetry manager
     */
    CC_TelemetryManager* pTmManager;

  public:

    /**
     * Instantiate a memory dump PUS telecommand.
     * The values of the internal data structure that is used to hold the telecommand
     * application data is initialized to illegal values to signify that the telecommand
     * is not yet configured. The telecommand type is set to PUS_TYPE_MEM.
     */
    PUSDumpMemory(void);

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
     * Get the maximum size of the application data array. 
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
     * Load the telemetry manager.
     * @see #doAction
     * @param pTmManager the PUS telemetry mode manager
     */
    void setTelemetryManager(CC_TelemetryManager* pTmManager);

    /**
     * Getter method for the telemetry manager.
     * @see #setTelemetryManager
     * @return the telemetry manager
     */
    CC_TelemetryManager* getTelemetryManager() const;

    /**
     * Perform a class-specific configuration check on the telecommand:
     * check that the maximum number of raw data has been set and that the
     * telemetry manager has been loaded.
     * @return true if the telecommand is configured, false otherwise
     */
    virtual bool isObjectConfigured(void);

};

#endif 
