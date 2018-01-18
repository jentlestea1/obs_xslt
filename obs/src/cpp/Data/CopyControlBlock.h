//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// CopyControlBlock.h
//
// Version	1.0
// Date		16.10.03 (Version 1.0)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:

#ifndef CopyControlBlockH
#define CopyControlBlockH

#include "ControlBlock.h"

/**
 * Base class for copy control blocks. 
 * A <i>copy control block</i> is a control block that implements a copy link to its
 * inputs and outputs. It adds to its <code>ControlBlock</code> base class
 * the following attributes:<ul>
 * <li>The <i>input buffers</i>: internal data structure where the values of the
 * control block inputs are copied at the beginning of a propagation cycle. The
 * state propagation and output update services read the value of the inputs from
 * the input buffers.</li>
 * <li>The <i>output buffers</i>: internal data structure where the values of the
 * control block outputs are written by the output update service. These values
 * are intended to be copied to the external output destination locations.</li>
 * </ul>
 * The input and output buffers are implemented as arrays. They are declared 
 * <code>protected</code> to give concrete subclasses ready access to them.
 * <p>
 * This class adds services to copy the input values from their external locations
 * to the internal input buffers and to copy the output values from the internal
 * output buffers to their external destinations. 
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.0
 * @ingroup Data
 */
class CopyControlBlock : public ControlBlock {
protected:
    /**
     * Array to hold the input buffer.
     * u[i] holds the i-th state variable with i lying in the interval [0,N-1] where N
     * is the number of inputs.
     * @see ControlBlock#setNumberOfInputs
     * @see #setInput
     * @see #getInput
     */
    TD_Float *u;

    /**
     * Array to hold the output buffer.
     * y[i] holds the i-th output variable with i lying in the interval [0,N-1] where N
     * is the number of outputs.
     * @see ControlBlock#setNumberOfOutputs
     * @see #setOutput
     * @see #getOutput
     */
    TD_Float *y;

    /**
     * Set the number of inputs. This method causes the memory for the input buffer
     * to be allocated. The number of inputs must be non-negative. The input values
     * are initialized to zero. This is an initialization method:  it shall be called
     * only once.
     * @param n the number of inputs
     */
    virtual void setNumberOfInputs(unsigned int n);

    /**
     * Set the number of outputs. This method causes the memory for the output buffer
     * to be allocated. The number of outputs must be non-negative. The output values
     * are initialized to zero. This is an initialization method:  it shall be called
     * only once.
     * @param n the number of outputs
     */
    virtual void setNumberOfOutputs(unsigned int n);

public:
    /**
     * Instantiate a copy control block. The input and output buffers are initialized to 
     * illegal values to signify that the control block is not yet configured.
     */
    CopyControlBlock(void);

    /**
     * Return the value of the i-th input. The argument i must lie
     * in the interval [0,n-1] where n is the number of inputs.
     * No check is performed on the legality of the index i.
     * @return the value of the i-th input variable
     * @param i the index of the input variable
     */
    TD_Float getInput(unsigned int i) const;

    /**
     * Return the value of the i-th output. The argument i must lie
     * in the interval [0,n-1] where n is the number of outputs.
     * No check is performed on the legality of the index i.
     * @return the value of the i-th output variable
     * @param i the index of the output variable
     */
    TD_Float getOutput(unsigned int i) const;

    /**
     * Set the value of the i-th input. The argument i must lie
     * in the interval [0,n-1] where n is the number of inputs.
     * Illegal argument values trigger the generation of an event report EVT_ILLEGAL_CB.
     * @param newValue the new value of the i-th input variable
     * @param i the index of the input variable
     */
    void setInput(unsigned int i,TD_Float newValue);

    /**
     * Set the value of the i-th output. The argument i must lie
     * in the interval [0,n-1] where n is the number of outputs.
     * Illegal argument values trigger the generation of an event report EVT_ILLEGAL_CB.
     * This method should not normally be used since the output is computed internally by
     * propagating the input and the state. It is provided for convenience only
     * for non-nominal situations.
     * @param newValue the new value of the i-th output variable
     * @param i the index of the output variable
     */
    void setOutput(unsigned int i,TD_Float newValue);

    /**
     * Reset the control block bringing its state and input and output buffers to the values
     * they had when the configuration process of the control block was terminated. 
     * A pseudocode implementation of this method is as follows:<pre>
     *      ControlBlock::reset();  // call method in super class to reset the state
     *      reset the input buffers to zero;
     *      reset the output buffers to zero;</pre>
     */
    virtual void reset(void);
};
#endif


