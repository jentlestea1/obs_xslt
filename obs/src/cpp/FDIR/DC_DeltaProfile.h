//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DeltaProfile.h
//
// Version	1.1
// Date		07.01.03 (Version 1.0)
//          01.10.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: replaced double and int with TD_Float and TD_Integer

#ifndef DC_DeltaProfileH
#define DC_DeltaProfileH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "MonitoringProfile.h"

/**
 * Default component implementing a "stuck data" monitoring profile.
 * This monitoring profile reports a "deviation from profile" if the 
 * value of the monitored variable undergoes a change in between two 
 * successive checks greater than a certain threshold. 
 * The threshold is called the <i>delta threshold</i>.
 * The delta threshold is a settable parameter. Its value must be
 * greater than zero. 
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.1
 */

class DC_DeltaProfile: public MonitoringProfile {

private:
    TD_Float deltaThreshold;
    TD_Float previousValue;
    bool notFirst;

protected:

  /**
  * Version of method <CODE>doProfileCheck()</CODE> for monitored variables 
  * of type integer. The check is performed by using the "TD_Float" version
  * of <code>doProfileCheck</code>.
  * A pseudo-code implementation for this method is as follows: <PRE>
  *   return doProfileCheck( (TD_Float)value ); </PRE>
  * @see #doProfileCheck
  */
  virtual bool doProfileCheck(TD_Integer value);

  /**
  * Check whether the monitored value differs from its value at the previous
  * activation by more than the delta threshold.
  * If it does, a "deviation from profile" is reported.
  * A pseudo-code implementation for this method is as follows: <PRE>
  *   if ( ( abs(value-previousValue) > deltaThreshold ) && notFirst )
  *   {  previousValue = value;
  *      return MON_PROFILE_DEVIATION; 
  *   }
  *   notFirst = true;
  *   previousValue = value;   
  *   return NO_MON_PROFILE_DEVIATION; </PRE>
  * <p>
  * The value of the <code>notFirst</code> flag is initialized to 
  * 'false' by the constructor and by the reset operation. 
  * @see #reset
  * @see #DC_DeltaProfile
  * @param value the value of the monitored variable
  * @return true if the monitored variable is stuck, false otherwise
  */
  virtual bool doProfileCheck(TD_Float value);

public:

  /**
  * Instantiate a delta monitoring profile.
  * The class identifier is set, the delta threshold is initialized to 0 to 
  * signify that the component is not yet configured, and the component is
  * reset.
  */
  DC_DeltaProfile(void);

  /**
  * Set the delta threshold.
  * @see #doProfileCheck
  * @param deltaThreshold the value of the delta threshold
  */
  void setDeltaThreshold(TD_Float deltaThreshold);

  /**
  * Get the delta threshold.
  * @see #doProfileCheck
  * @return the value of the delta threshold
  */
  TD_Float getDeltaThreshold(void);

  /**
  * Perform a class-specific configuration check on the monitoring
  * profile: verify that the delta threshold has a value greater than zero.
  * @return true if the monitoring profile is configured, false otherwise.
  */
  virtual bool isObjectConfigured(void);

  /**
   * Reset the delta monitoring profile check. With reference to the 
   * implementation of method <code>doProfileCheck(TD_Integer)</code>, a call to
   * this method causes the flag <code>notFirst</code> to be reset to 
   * 'false'.
   */
   virtual void reset(void);

};

#endif
