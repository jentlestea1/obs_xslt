//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSDumpMemoryAbsolute.h
//
// Version	1.0
// Date		05.01.04
// Author	A. Pasetti (P&P Software)

#ifndef DC_PUSDumpMemoryAbsoluteH
#define DC_PUSDumpMemoryAbsoluteH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSDumpMemory.h"

/**
 * PUS telecommand to set up a memory dump with absolute addresses.
 * This class encapsulates the PUS service type 6, subtype 5.
 * This class adds to its base class the implementation of the execution
 * action. Execution of this telecommand consists in retrieving a free telemetry packet
 * of type <code>DC_PUSMemoryDumpAbsolute</code> from the telemetry packet factory, 
 * configuring it with the application
 * data and sending it to the telemetry manager for immediate dispatch. The telemetry 
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
 * telemetry manager (the return value of <code>doAction</code>
 * is TM_MAN_QUEUE_FULL)   </li>
 * <li>The internal structure of the application data was found to be 
 * inconsistent (the return value of <code>doAction</code>
 * is APP_DATA_INCONSISTENT)   </li>
 * </ul> . 
 * No event reports are generated in case of failure as it is assumed that
 * this is done by the calling client.
 * @see DC_PUSMemoryDumpOffset
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_PUSDumpMemoryAbsolute : public PUSDumpMemory {

  protected:

    /**
     * Use the application data to configure and load a memory dump telemetry packet
     * with base plus offset.
     * This method queries the dynamic telemetry packet factory for a new
     * memory dump packet. If it obtains it, it interprets the application data and 
     * configures the memory dump packet. The following operations are performed on
     * the memory dump packet:<ul>
     * <li>The number of blocks is defined </li>
     * <li>If a memory dump with base plus offset is required, the base address is
     * set</li>
     * <li>Each memory block is configured with its start address and length</li>
     * </ul>
     * After being configured, the telemetry packet is loaded in the immediate
     * dispatch queue of the telemetry manager.
     * This method can return a failure code. See the class comment for details.
     * @see PunctualAction#execute
     * @return action outcome code (see class comment)
     */
    virtual TD_ActionOutcome doAction(void);

  public:

    /**
     * Instantiate a PUS memory dump with absolute addresses telecommand.
     * The class identifier is set. The telecommand subtype attribute
     * is set to PUS_ST_TC_DMP_ABS. 
     */
    DC_PUSDumpMemoryAbsolute(void);


};

#endif 
