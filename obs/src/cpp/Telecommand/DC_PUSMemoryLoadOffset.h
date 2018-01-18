//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSMemoryLoadOffset.h
//
// Version	1.0
// Date		05.02.04
// Author	A. Pasetti (P&P Software)

#ifndef DC_PUSMemoryLoadOffsetH
#define DC_PUSMemoryLoadOffsetH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSMemoryLoad.h"

/**
 * Class implementing the PUS service to load memory using base plus offset (PUS 
 * service type 6, subtype 1).
 * This class adds to its superclass the implementation of the 
 * <i>raw data load mechanism</i>. Since the amount of data to be loaded will often
 * be large, the fast version of this service is implemented. 
 * The data load mechanism interprets the application data in the telecommand
 * packet and uses them to configure the internal data structure defined by the
 * super class. The interpretation of the application data can result in the
 * detection of inconsistencies or invalid data. These are reported by setting the
 * <i>validity check code</i>. 
 * <p>
 * The PUS leaves some leeway in the definition of the structure of the application
 * data for memory load telecommands. This implementation makes the following 
 * assumptions: <ul>
 * <li>The memory ID field is always present and its type is <code>TD_PUSMemId</code>.</li>
 * <li>The base field is a pointer and is four bytes long.</li>
 * <li>The offset field is an integer of type <code>TD_PUSMemOffset</code>.</li>
 * <li>The number of blocks field is an integer of type <code>TD_PUSNumberMemBlocks</code>.</li>
 * </ul>
 * The implementation of this class assumes type <code>TD_PUSMemId</code> to have size 1
 * (i.e. to be a <code>char</code> or an <code>unsigned char</code>). 
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_PUSMemoryLoadOffset : public PUSMemoryLoad {

  private:
     TD_PUSMemId memId;

  public:

    /**
     * Instantiate a PUS memory load using base offset telecommand.
     * The class identifier and the telecommand subtype are set.
     * The memory block ID is initialized to zero.
     */
    DC_PUSMemoryLoadOffset(void);

    /**
     * Implementation of the raw data load service. This method would normally
     * be called by a telecommand loader to load the application data into the
     * the telecommand component. This method interprets the raw data as they are
     * loaded and uses them to configure the data structure (defined by the
     * super class) that holds the start address, the length, the checksum, 
     * and the memory load data for each block. The application data are constrained
     * to fit within the data structures configured at the level of the superclass.
     * Two such constraints apply:<ul>
     * <li>The number of bytes to be transferred (the value of argument n) must
     * be greater than: 
     * <code>sizeof(TD_PUSMemId)+sizeof(TD_PUSMemData*)+sizeof(TD_PUSNumberMemBlocks)</code>.
     * If this is not the case, the validity check
     * code is set to VC_INCONSISTENT_RAW_DATA.</li>
     * <li>The number of blocks must be less or equal than the maximum number of
     * blocks defined in the super class. If this is not the case, the validity check
     * code is set to VC_TOO_MANY_MEM_BLOCK.</li>
     * <li>The total number of memory data to be loaded must not exceed the maximum
     * value defined in the super class. If this is not the case, the validity check
     * code is set to VC_TOO_MANY_MEM_DATA.</li>
     * <li>The number of bytes to be transferred (the value of argument n) must 
     * be consistent with the number of blocks and of data inferred from the application
     * data. If this is not the case, the validity check
     * code is set to VC_INCONSISTENT_RAW_DATA.</li>
     * </ul>
     * When a constraint is violated, the method returns immediately after setting the
     * value of the validity check code.
     * @param n the number of bytes in the raw data
     * @param d the starting address of the raw data
     */
    virtual void setRawData(unsigned char* d, unsigned int n);

    /**
     * Get the memory block ID.
     * @return the maximum number of blocks
     */
    TD_PUSMemId getMemoryBlockId() const;


};

#endif 
