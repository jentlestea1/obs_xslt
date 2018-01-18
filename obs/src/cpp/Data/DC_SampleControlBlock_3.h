  
//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_SampleControlBlock_3.h
//
// This file was automatically generated by an XSL program

#ifndef DC_SampleControlBlock_3H
#define DC_SampleControlBlock_3H

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Data/DataPoolControlBlock.h"

/**
 * Sample control block number 3. This control block has one input 
 * (the speed of reaction wheel 3), one output (the torque of 
 * reaction wheel 3), and one parameter (the gain K3).
 * <p>
 * This is a stub class. It provides dummy implementations for some of the virtual
 * methods of its superclass. 
 * This class was automatically generated by an XSL program that processes the
 * XML-based <i>target application model</i>. The XSL program  
 * searches the application model for all "ControlBlock" elements
 * which have a "Custom" subelement that indicates that a custom control block
 * class must be created. For each such element a class header file is created.
 * @todo Modify the generator meta-component generateRecoveryAction to generate the code
 * that sets the class identifier and to treat the default attributes in the custom recovery action description.
 * @author Automatically Generated Class
 * @version 1.0
 */
class DC_SampleControlBlock_3 : public DataPoolControlBlock {

  public: 
  
    /**
     * Stub constructor that sets the number of inputs, of outputs, of states and of parameters.
     * The number of inputs is set to 1.
     * The number of outputs is set to 1.
     * The number of parameters is set to 1.
     * The number of states is set to zero. Developers may have to change this value to reflect
     * their desired implementation of this class.
     */
    DC_SampleControlBlock_3(void);
    
    /**
     * This is a stub method that must be completed by the application developer.
     * This stub provides a default implementation that returns without doing anything.
     */
    virtual void propagateState(void);

    /**
     * This is a stub method that must be completed by the application developer.
     * This stub provides a default implementation that returns without doing anything.
     */
    virtual void updateOutput(void);
 
    /**
     * This is a stub method that must be completed by the application developer.
     * This stub provides a default implementation that returns without doing anything.
     */
    virtual void reset(void);

};
            
#endif
             