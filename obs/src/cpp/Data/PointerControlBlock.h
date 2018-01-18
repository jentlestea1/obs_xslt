//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// PointerControlBlock.h
//
// Version	1.0
// Date		11.10.03 (Version 1.0)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:

#ifndef PointerControlBlockH
#define PointerControlBlockH

#include "ControlBlock.h"

/**
 * Base class for pointer control blocks. 
 * A <i>pointer control block</i> is a control block that is linked to its inputs
 * and outputs through pointers. It adds to its <code>ControlBlock</code> base class
 * the following attributes:<ul>
 * <li>The <i>input pointers</i>: the pointers to the external locations from which the input
 * values are loaded.</li>
 * <li>The <i>output pointers</i>: the pointers to the external locations to which the output
 * values are written.</li>
 * </ul>
 * This class adds services to set up the link between the block inputs and outputs and the
 * external locations from which the inputs are read and to which the outputs are written.
 * <p>
 * This class deviates from the project-specific coding rule PR3.1.
 * Use of pointers to a variable of primitive type is necessary to fulfill
 * the function of the class.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.0
 * @ingroup Data
 */
class PointerControlBlock : public ControlBlock {
protected:
    /**
     * Array of input pointers.
     * pU[i] holds the pointer to the i-th input variable with i lying in the 
     * interval [0,N-1] where N is the number of inputs.
     * @see #setInputLink
     */
    TD_Float **pU;

    /**
     * Array of output pointers.
     * pY[i] holds the pointer to the i-th output variable with i lying in the 
     * interval [0,N-1] where N is the number of outputs.
     * @see #setOutputLink
     */
    TD_Float **pY;

    /**
     * Set the number of inputs. This method causes the memory for the array holding
     * the input pointers to be allocated. This is an initialization method:  it shall
     * be called only once.
     * @param n the number of inputs
     */
    virtual void setNumberOfInputs(unsigned int n);

    /**
     * Set the number of outputs. This method causes the memory for the array holding
     * the output pointers to be allocated. This is an initialization method:  it shall
     * be called only once.
     * @param n the number of outputs
     */
    virtual void setNumberOfOutputs(unsigned int n);

public:
    /**
     * Instantiate a pointer control block. The input pointers and output pointers are
     * initialized to illegal values to signify that the component is not yet configured.
     */
    PointerControlBlock(void);

    /**
     * Set the i-th input pointer. This method sets the pointer to the location from which the
     * the i-th input should be read. The argument i must lie in the interval [0,n-1] where
     * n is the number of inputs.
     * Illegal argument values trigger the generation of an event report EVT_ILLEGAL_CB.
     * @param i the index of the input 
     * @param pInput the pointer to the external input location
     */
    void setInputLink(unsigned int i,TD_Float *pInput);

    /**
     * Set the i-th output pointer. This method sets the pointer to the location to which the
     * the i-th output should be written. The argument i must lie in the interval [0,n-1]
     * where n is the number of outputs.
     * Illegal argument values trigger the generation of an event report EVT_ILLEGAL_CB.
     * @param i the index of the output 
     * @param pOutput the pointer to the external output location
     */
    void setOutputLink(unsigned int i,TD_Float *pOutput);

    /**
     * Perform a class-specific configuration check on a pointer control block. 
     * It is checked that the input and output pointers have been loaded.
     */
    virtual bool isObjectConfigured(void);
};
#endif
