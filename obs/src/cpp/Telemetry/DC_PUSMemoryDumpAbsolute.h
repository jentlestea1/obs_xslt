//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSMemoryDumpAbsolute.h
//
// Version	1.0
// Date		01.03.04
// Author	A. Pasetti (P&P Software)

#ifndef DC_PUSMemoryDumpAbsoluteH
#define DC_PUSMemoryDumpAbsoluteH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Telemetry/PUSMemoryDump.h"

/**
 * PUS telemetry packet implementing the memory dump service using absolute addresses 
 * (type 6, subtype 6).
 * This class adds to its superclass the 
 * implementation of the <i>data update service</i>.
 * @todo construct a test case for this class.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_PUSMemoryDumpAbsolute : public PUSMemoryDump {

  public:

    /**
     * Instantiate a PUS memory dump with absolute addresses telemetry packet.
     * The class identifier is set. The telemetry subtype attribute
     * is set to PUS_ST_TM_DMP_ABS. 
     */
    DC_PUSMemoryDumpAbsolute(void);

    /**
     * Implement the <i>data update service</i> for the PUS memory dump with absolute addresses packet.
     * The memory locations to be dumped are stored in the <code>block</code> data structure
     * defined in the superclass. The memory dump data are collected and stored in the
     * <i>dump buffer</i> which is also defined in the superclass. Both the <code>block</code>
     * and <i>dump buffer</i> structures are declared <code>protected</code> in the superclass
     * and can therefore be directly accessed here. This method uses the data in the 
     * <code>block</code> structure and the value of the base address to construct and image of the
     * telemetry packet and store it in the <i>dump buffer</i>. 
     */
    virtual void update(void);

};

#endif
