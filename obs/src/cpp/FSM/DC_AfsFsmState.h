  
//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_AfsFsmState.h
//
// This file was automatically generated by an XSL program

#ifndef DC_AfsFsmStateH
#define DC_AfsFsmStateH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../FSM/FsmState.h"

/**
 * Sample application class. FsmState component representing the AFS state of the 
 * FDIR FSM.
 * <p>
 * This is a stub class. It provides dummy implementations for some of the virtual
 * methods of its superclass. 
 * This class was automatically generated by an XSL program that processes the
 * XML-based <i>target application model</i>. The XSL program  
 * searches the application model for all "FsmState" elements
 * which have a "Custom" subelement that indicates that a custom FsmState
 * class must be created. For each such element a class header file is created.
 * The base class of the generated class is assumed to be the class in the
 * "type" attribute of the FsmState element. 
 * The information in the application model is used to decide which virtual methods
 * should be overridden.
 * @todo Modify the generator meta-component generateRecoveryAction to generate the code
 * that sets the class identifier and to treat the default attributes in the custom recovery action description.
 * @author Automatically Generated Class
 * @version 1.0
 */
class DC_AfsFsmState : public FsmState {

  public: 
  
    /**
     * Stub constructor that returns without taking any action.
     */
    DC_AfsFsmState(void);
    
    
    /**
     * Disable all reconfigurations; disable all telecommands to change the enable/disable status 
     * of the reconfiguration managers.
     * <p>
     * This is a stub method that must be completed by the application developer.
     * This stub provides a default implementation that calls the <code>doInit</code> 
     * method of the superclass.
     */
    virtual void doInit(void);
    
    /**
     * Dummy implementation that returns without taking any action. There is no continuation
     * action associated to this class.
     */
    virtual void doContinue(void);
          
    /**
     * Enable all reconfigurations; enable all telecommands to change the enable/disable status 
     * of the reconfiguration managers.
     * <p>
     * This is a stub method that must be completed by the application developer.
     * This stub provides a default implementation that calls the <code>doExit</code> 
     * method of the superclass.
     */
    virtual void doExit(void);
    
};
            
#endif
             