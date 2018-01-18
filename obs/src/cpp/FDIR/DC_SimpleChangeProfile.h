//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_SimpleChangeProfile.h
//
// Version	1.1
// Date		04.01.03 (Version 1.0)
//          01.10.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: replaced double and int with TD_Float and TD_Integer

#ifndef DC_SimpleChangeProfileH
#define DC_SimpleChangeProfileH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "MonitoringProfile.h"

/**
 * Default component implementing a simple change monitoring profile.
 * This monitoring profile reports a "deviation from profile" if the 
 * value of the monitored variable is different
 * from a fixed reference value. 
 * The reference value is a settable parameter.
 * <p>
 * This type of check only makes sense for monitored variables of
 * integer type. The version of the monitoring check for variables
 * of doble type is therefore implemented as a dummy operation
 * that always returns "deviation from profile has been detected".
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.1
 */

class DC_SimpleChangeProfile: public MonitoringProfile {

private:
    TD_Integer referenceValue;

protected:

  /**
  * Check whether the monitored value is different from the reference value.
  * If it is, a "devation from profile" is reported.
  * A pseudo-code implementation for this method is as follows: <PRE>
  *   if ( value != refValue )
  *     return MON_PROFILE_DEVIATION;
  *   return NO_MON_PROFILE_DEVIATION; </PRE>
  * <p>
  * @param value the value of the monitored variable
  * @return true if the monitored variable is different from the reference value,
  * false otherwise
  */
  virtual bool doProfileCheck(TD_Integer value);

  /**
  * Dummy implementation of a monitoring check that always returns "deviation
  * from profile detected".
  * This operation should never be called since simple monitoring check on
  * non-integer variables may give unpredictable results due to numerical
  * precision errors.
  * @param value the value of the monitored variable
  * @return always returns true 
  */
  virtual bool doProfileCheck(TD_Float value);

public:

  /**
  * Instantiate a simple change profile.
  * The class identifier is set and the reference value is initialized to zero.
  */
  DC_SimpleChangeProfile(void);

  /**
  * Set the reference value against which the monitoring check is performed.
  * The reference value can be modified dynamically.
  * @see #doProfileCheck
  * @param refValue the value of the reference value
  */
  void setReferenceValue(TD_Integer refValue);

  /**
  * Get the reference value.
  * @see #setReferenceValue
  * @return the value of the reference value
  */
  TD_Integer getReferenceValue(void) const;

};

#endif
