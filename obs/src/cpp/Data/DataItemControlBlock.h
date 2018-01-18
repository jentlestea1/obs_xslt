//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DataItemControlBlock.h
//
// Version	1.0
// Date		11.10.03 (Version 1.0)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:

#ifndef DataItemControlBlockH
#define DataItemControlBlockH

#include "ControlBlock.h"

/**
 * Base class for data item control blocks. 
 * A <i>data item control block</i> is a control block that takes its inputs from and writes
 * its outputs to <i>data items</i> (instances of class <code>DC_DataItem</code>). The data
 * items are loaded as part of the control block configuration. This class therefore adds 
 * the following attributes to its <code>ControlBlock</code> base class:<ul>
 * <li>The <i>input data items</i>: the data items from which the input values are read.</li>
 * <li>The <i>output data items</i>: the data items to which the output values are written.</li>
 * </ul>
 * This class adds services to set up the link between the block inputs and outputs and the
 * data items from which the inputs are read and to which the outputs are written.
 * @see DC_DataItem
 * @author Alessandro Pasetti, Roberto Totaro
 * @version 1.0
 * @ingroup Data
 */
class DataItemControlBlock : public ControlBlock {
protected:
    /**
     * Array of input data items.
     * Element pDIU[i] holds the pointer to the data item that provides the i-th input variable.
     * The integer i must lie in the 
     * interval [0,N-1] where N is the number of inputs.
     * @see #setInputLink
     */
    DC_DataItem **pDIU;

    /**
     * Array of output data items.
     * Element pDIY[i] holds the pointer to the data item to which the i-th output variable is written.
     * The integer i must lie in the 
     * interval [0,N-1] where N is the number of outputs.
     * @see #setOutputLink
     */
    DC_DataItem **pDIY;

    /**
     * Set the number of inputs. This method causes the memory for the array holding
     * the input data items to be allocated.
     * @param n the number of inputs
     */
    virtual void setNumberOfInputs(unsigned int n);

    /**
     * Set the number of outputs. This method causes the memory for the array holding
     * the output data items to be allocated.
     * @param n the number of outputs
     */
    virtual void setNumberOfOutputs(unsigned int n);

public:
    /**
     * Instantiate a data item control block. The input data items and output data items are
     * initialized to illegal values to signify that the component is not yet configured.
     */
    DataItemControlBlock();

    /**
     * Load the data item for the i-th input. The argument i must lie in the 
     * interval [0,N-1] where N is the number of inputs.
     * An illegal value for argument i triggers the generation of an event report 
     * EVT_ILLEGAL_CB. 
     * @param i the index of the input 
     * @param pDataItem the data item 
     */
    void setInputLink(unsigned int i, DC_DataItem* pDataItem);

    /**
     * Load the data item for the i-th output. The argument i must lie in the 
     * interval [0,N-1] where N is the number of outputs.
     * An illegal value for argument i triggers the generation of an event report 
     * EVT_ILLEGAL_CB. 
     * @param i the index of the output 
     * @param pDataItem the data item 
     */
    void setOutputLink(unsigned int i, DC_DataItem* pDataItem);

    /**
     * Perform a class-specific configuration check on a pointer control block. 
     * It is checked that the input and output data items have been loaded.
     */
    virtual bool isObjectConfigured(void);
};
#endif
