  
//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_SBY_PostSepFsmState.h
//
// This file was automatically generated by an XSL program

#ifndef DC_SBY_PostSepFsmStateH
#define DC_SBY_PostSepFsmStateH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../FSM/FsmState.h"

/**
 * Sample FsmState application class. FsmState component for the SBY postseparation mode.
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
class DC_SBY_PostSepFsmState : public FsmState {

  public: 
  
    /**
     * Stub constructor that returns without taking any action.
     */
    DC_SBY_PostSepFsmState(void);
    
    
    /**
     * Perform actions to be done upon detection of separation.
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
     * Perform action to be done just before exiting the this mode.
     * <p>
     * This is a stub method that must be completed by the application developer.
     * This stub provides a default implementation that calls the <code>doExit</code> 
     * method of the superclass.
     */
    virtual void doExit(void);
    
    /**
     * Terminate when count-down is finished.
     * <p>
     * This is a stub method that must be completed by the application developer.
     * This stub provides a default implementation that calls the <code>isFinished</code> 
     * method of the superclass.
     * @return true if the continuation action of this state has terminated, false otherwise
     */
    virtual bool isFinished(void);
    
};
            
#endif
             