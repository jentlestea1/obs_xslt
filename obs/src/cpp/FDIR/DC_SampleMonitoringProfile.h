  
//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_SampleMonitoringProfile.h
//
// This file was automatically generated by an XSL program

#ifndef DC_SampleMonitoringProfileH
#define DC_SampleMonitoringProfileH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../FDIR/MonitoringProfile.h"

/**
 * Sample application-specific monitoring profile.
 * <p>
 * This is a stub class. It provides dummy implementations for some of the virtual
 * methods of its superclass. 
 * This class was automatically generated by an XSL program that processes the
 * XML-based <i>target application model</i>. The XSL program searches 
 * the  searches the application model for all "MonitoringProfile" elements
 * which have a "Custom" subelement that indicates that a custom recovery action
 * class must be created. For each such element a class header file is created.
 * The base class of the generated class is assumed to be the class in the
 * "type" attribute of the MonitoringProfile element. 
 * The information in the application model is used to decide which virtual methods
 * should be overridden.
 * @todo Modify the generator meta-component generateMonitoringProfile to generate the code
 * that sets the class identifier and to treat the default attributes in the custom monitoring profile description.
 * @author Automatically Generated Class
 * @version 1.0
 */
class DC_SampleMonitoringProfile : public MonitoringProfile {

  public: 
  
    /**
     * Stub constructor that returns without taking any action.
     */
    DC_SampleMonitoringProfile(void);
    
    /**
     * This is a stub method that must be completed by the application developer.
     * This stub provides a default implementation that always returns false (no deviation from
     * profile).
     * @return always return false 
     */
    virtual bool doProfileCheck(TD_Float value);

    /**
     * This is a stub method that must be completed by the application developer.
     * This stub provides a default implementation that always returns false (no deviation from
     * profile).
     * @return always return false 
     */
    virtual bool doProfileCheck(TD_Integer value);
};
            
#endif
             