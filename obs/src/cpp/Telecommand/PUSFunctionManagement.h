//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// PUSFunctionManagement.h
//
// Version	1.0
// Date		05.12.03
// Author	A. Pasetti (P&P Software)

#ifndef PUSFunctionManagementH
#define PUSFunctionManagementH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTelecommand.h"

/**
 * PUS telecommand to implementing the PUS function management service (PUS service
 * number 8). This is an abstract class since the function implementation service
 * is application specific. This class defines a PUS telecommand with type equal to
 * 8 and subtype equal to 1. No other attributes or services are added to those provided
 * by the <code>PUSTelecommand</code> superclass. 
 * <p>
 * The function management service defines a mechanism for passing parameters to the
 * function that the telecommand manages. This mechanism is already covered by the
 * <i>raw data load</i> mechanism defined by the <code>PUSTelecommand</code> superclass.
 * @todo Can a generic way be found to handle the execution of some action as a function
 * of the "function ID field" in the telecommand packet?
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class PUSFunctionManagement : public PUSTelecommand {

  public:
    /**
     * Instantiate a function management telecommand.
     * The telecommand type is set to PUS_TYPE_TC_FNC and the telecommand subtype is set 
     * to PUS_ST_TC_FNC_PER.
     * @see PUS_TYPE_TC_FNC
     * @see PUS_ST_TC_FNC_PER
     */
    PUSFunctionManagement(void);

};

#endif 
