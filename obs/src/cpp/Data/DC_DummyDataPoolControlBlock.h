//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyDataPoolControlBlock.h
//
// Version	1.0
// Date		31.10.03 (Version 1.0)
// Author	R. Totaro
//
// Change Record:

#ifndef DC_DummyDataPoolControlBlockH
#define DC_DummyDataPoolControlBlockH

#include "DataPoolControlBlock.h"

/**
 * Dummy data pool control block useful for testing purposes.
 * This control block has three inputs, two outputs, one state and
 * two parameters.
 * The <i>state propagation function</i> is as follows:<PRE>
 *      x[0](k+1) = p[0]*x[0](k) + u[0](k) + u[1](k) + u[2](k);</PRE>
 * The <i>output update function</i> is as follows:<PRE>
 *      y[0](k) = x[0](k);
 *      y[1](k) = p[1]*x[0](k);</PRE>
 * @author Roberto Totaro
 * @version 1.0
 */
class DC_DummyDataPoolControlBlock : public DataPoolControlBlock {
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
     * state and two parameters, and set the class identifier. The reset method
     * is called to initialize the internal state of the control block.
     */
    DC_DummyDataPoolControlBlock(void);

    /**
     * Reset the control block by setting the state value to 1.0.
     */
    virtual void reset(void);
};
#endif
