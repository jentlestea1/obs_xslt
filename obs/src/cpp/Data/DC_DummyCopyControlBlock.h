//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyCopyControlBlock.cpp
//
// Version	1.2
// Date	    11.04.03 (Version 1.0)
//          14.10.03 (Version 1.1)
//          16.10.03 (Version 1.2)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: Updated to reflect the new structure of the ControlBlock class
//   Version 1.2: The class is now derived from CopyControlBlock

#ifndef DC_DummyCopyControlBlockH
#define DC_DummyCopyControlBlockH

#include "CopyControlBlock.h"

/**
 * Dummy control block useful for testing purposes.
 * This control block has three inputs, two outputs, one state and
 * two parameters.
 * The <i>state propagation function</i> is as follows:<PRE>
 *      x[0](k+1) = p[0]*x[0](k) + u[0](k) + u[1](k) + u[2](k);</PRE>
 * The <i>output update function</i> is as follows:<PRE>
 *      y[0](k) = x[0](k);
 *      y[1](k) = p[1]*x[0](k);</PRE>
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.2
 */
class DC_DummyCopyControlBlock : public CopyControlBlock {
protected:
    /**
     * Implement the state propagation function. 
     * @see ControlBlock#propagate
     */
    virtual void propagateState(void);

    /**
     * Implement the output update function. 
     * @see ControlBlock#propagate
     */
    virtual void updateOutput(void);

public:
    /**
     * Configure the control block to have three inputs, two outputs, one
     * state and two parameters, set the class identifier and call the 
     * reset service to initialize the internal state of the control block.
     */
    DC_DummyCopyControlBlock(void);

    /**
     * Reset the control block by setting the state values to 1.0 and the inputs to 0.0.
     */
    virtual void reset(void);
};
#endif
