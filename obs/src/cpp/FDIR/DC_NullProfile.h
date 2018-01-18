//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_NullProfile.h
//
// Version	1.1
// Date		07.01.03 (Version 1.0)
//          01.10.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: replaced double and int with TD_Float and TD_Integer

#ifndef DC_NullProfileH
#define DC_NullProfileH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "MonitoringProfile.h"

/**
 * Default component implementing a "null monitoring profile".
 * A null monitoring profile always reports "no deviation from profile".
 * This profile is typically useful as a placeholder where a component of type
 * <code>MonitoringProfile</code> is needed to complete the configuration of a component
 * but where there is no need to perform any profile monitoring check.
 * It is similarly useful where a variable must formally be subjected to 
 * profile monitoring but its value in fact not subject to any limitation.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */

class DC_NullProfile: public MonitoringProfile {

protected:

  /**
  * Always return "no deviation from profile"
  * @param value the value of the monitored variable
  * @return alway returns false 
  */
  virtual bool doProfileCheck(TD_Integer value);

  /**
  * Always return "no deviation from profile"
  * @param value the value of the monitored variable
  * @return alway returns false 
  */
  virtual bool doProfileCheck(TD_Float value);

public:

  /**
  * Instantiate a null monitoring profile.
  * The class identifier is set.
  */
  DC_NullProfile(void);

};

#endif
