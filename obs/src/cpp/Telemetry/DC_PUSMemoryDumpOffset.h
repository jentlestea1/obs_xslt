//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSMemoryDumpOffset.h
//
// Version	1.0
// Date		01.12.02
// Author	A. Pasetti (P&P Software)

#ifndef DC_PUSMemoryDumpOffsetH
#define DC_PUSMemoryDumpOffsetH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Telemetry/PUSMemoryDump.h"

/**
 * PUS telemetry packet implementing the memory dump service using base plus offset 
 * (type 6, subtype 4).
 * This class adds to its superclass the modelling of the base address and the 
 * implementation of the <i>data update service</i>.
 * @todo construct a test case for this class.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_PUSMemoryDumpOffset : public PUSMemoryDump {

  private:
      TD_PUSMemData* base;

  public:

    /**
     * Instantiate a PUS memory dump with offset telemetry packet.
     * The class identifier is set. The telemetry subtype attribute
     * is set to PUS_ST_TM_DMP_OFF. The base address is initialized to zero.
     */
    DC_PUSMemoryDumpOffset(void);

    /**
     * Set the base address for the dump packet.
     * Only values greater than zero are legal.
     * @see #update
     * @param base the base address
     */
    void setBaseAddress(TD_PUSMemData* base);

    /**
     * Get the base address for the dump packet.
     * @see #setBaseAddress
     * @return the base address
     */
    TD_PUSMemData* getBaseAddress();

    /**
     * Implement the <i>data update service</i> for the PUS memory dump with offset telemetry packet.
     * The memory locations to be dumped are stored in the <code>block</code> data structure
     * defined in the superclass. The memory dump data are collected and stored in the
     * <i>dump buffer</i> which is also defined in the superclass. Both the <code>block</code>
     * and <i>dump buffer</i> structures are declared <code>protected</code> in the superclass
     * and can therefore be directly accessed here. This method uses the data in the 
     * <code>block</code> structure and the value of the base address to construct and image of the
     * telemetry packet and store it in the <i>dump buffer</i>. 
     * <p>
     * This method relies on the data in the <code>block</code> data structure to be consistent with
     * the value of the base address. In particular, the following must be ensured: <ul>
     * <li>The value of the base address must be smaller than all the <code>startAddress</code>
     * fields of the <code>block</code> data structure.</li>
     * <li>The offset field is computed as the difference between the value of the <code>startAddress</code>
     * field of the <code>block</code> data structure and the value of the base address. The result
     * must be expressible as an integer of type <code>TD_PUSMemOffset</code>.</li>
     * </ul>
     * Compliance with the above conditions is not checked at run time (but violation may result in
     * in a run-time exception). As they are collected, the memory dump data are stored in the
     * <i>dump buffer</i> defined by the superclass. A check is made that there is no overflow.
     * If this is found to be the case, then the method returns after generating event report
     * EVT_PUS_TOO_MANY_MEM_DATA. In this case, no memory dump data are collected.
     */
    virtual void update(void);

};

#endif
