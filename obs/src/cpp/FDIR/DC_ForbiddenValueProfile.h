//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_ForbiddenValueProfile.h
//
// Version	1.1
// Date		04.01.03 (Version 1.0)
//          01.10.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: replaced double and int with TD_Float and TD_Integer

#ifndef DC_ForbiddenValueProfileH
#define DC_ForbiddenValueProfileH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "MonitoringProfile.h"

/**
 * Default component implementing a forbidden value monitoring profile.
 * This monitoring profile reports a "deviation from profile" if the 
 * value of the monitored variable is equal to a pre-specified 
 * <i>forbidden value</i>. The forbidden value is a settable parameter. 
 * <p>
 * This type of check only makes sense for monitored variables of
 * integer type. The version of the monitoring check for variables
 * of doble type is therefore implemented as a dummy operation
 * that always returns "deviation from profile has been detected".
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.1
 */

class DC_ForbiddenValueProfile: public MonitoringProfile {

private:
    TD_Integer forbiddenValue;

protected:

  /**
  * Check whether the monitored value is equal to the forbidden value.
  * If it is, a "devation from profile" is reported.
  * A pseudo-code implementation for this method is as follows: <PRE>
  *   if ( value == forbiddenValue )
  *     return MON_PROFILE_DEVIATION;
  *   return NO_MON_PROFILE_DEVIATION; </PRE>
  * <p>
  * @param value the value of the monitored variable
  * @return true if the monitored variable is equal to the forbidden value,
  * false otherwise
  */
  virtual bool doProfileCheck(TD_Integer value);

  /**
  * Dummy implementation of a monitoring check that always returns "deviation
  * from profile detected".
  * This operation should never be called since a forbidden value monitoring 
  * check on
  * non-integer variables may give unpredictable results due to numerical
  * precision errors.
  * @param value the value of the monitored variable
  * @return always returns true 
  */
  virtual bool doProfileCheck(TD_Float value);

public:

  /**
  * Instantiate a forbidden value profile.
  * The class identifier is set and the forbidden value is initialized to zero.
  */
  DC_ForbiddenValueProfile(void);

  /**
  * Set the forbidden value against which the monitoring check is performed.
  * The forbidden value can be modified dynamically.
  * @see #doProfileCheck
  * @param forbiddenValue the forbidden value 
  */
  void setForbiddenValue(TD_Integer forbiddenValue);

  /**
  * Get the forbidden value.
  * @see #setForbiddenValue
  * @return the value of the reference value
  */
  TD_Integer getForbiddenValue(void) const;

};

#endif
