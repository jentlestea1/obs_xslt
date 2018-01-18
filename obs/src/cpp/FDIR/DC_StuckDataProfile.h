//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_StuckDataProfile.h
//
// Version	1.1
// Date		07.01.03 (Version 1.0)
//          01.10.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: replaced double and int with TD_Float and TD_Integer

#ifndef DC_StuckDataProfileH
#define DC_StuckDataProfileH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "MonitoringProfile.h"

/**
 * Default component implementing a "stuck data" monitoring profile.
 * This monitoring profile reports a "deviation from profile" if the 
 * value of the monitored variable remains unchanged for more
 * a certain number of consecutive activations. 
 * The number of consecutive activations that the
 * monitored variable must remain unchanged before the monitoring check is
 * detected is called the <i>stuck threshold</i>.
 * The stuck threshold is a settable parameter. Its value must be
 * greater than zero.
 * <p>
 * This type of check only makes sense for monitored variables of
 * integer type. The version of the monitoring check for variables
 * of doble type is therefore implemented as a dummy operation
 * that always returns "deviation from profile has been detected".
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.1
 */

class DC_StuckDataProfile: public MonitoringProfile {

private:
    unsigned int stuckThreshold;
    unsigned int counter;
    TD_Integer previousValue;

protected:

  /**
  * Check whether the monitored value is stuck.
  * If it is, a "devation from profile" is reported.
  * A pseudo-code implementation for this method is as follows: <PRE>
  *   if ( value == previousValue )
  *   {  counter++;
  *      previousValue = value;
  *      if (counter == stuckThreshold)
  *      { counter = 0;
  *        return MON_PROFILE_DEVIATION; 
  *      }
  *      else
  *        return NO_MON_PROFILE_DEVIATION; 
  *   }
  *   else
  *      counter = 0;
  *   previousValue = value;   
  *   return NO_MON_PROFILE_DEVIATION; </PRE>
  * <p>
  * The value of <code>previousValue</code> and <code>counter</code>
  * are initialized by the constructor and by method <code>reset</code>. 
  * Spurious triggerings can occurr either after a reset or after the
  * component is created.
  * @see #reset
  * @see #DC_StuckDataProfile
  * @param value the value of the monitored variable
  * @return true if the monitored variable is stuck, false otherwise
  */
  virtual bool doProfileCheck(TD_Integer value);

  /**
  * Dummy implementation of a monitoring check that always returns "deviation
  * from profile detected".
  * This operation should never be called since stuck data monitoring checks on
  * non-integer variables may give unpredictable results due to numerical
  * precision errors.
  * @param value the value of the monitored variable
  * @return always returns true 
  */
  virtual bool doProfileCheck(TD_Float value);

public:

  /**
  * Instantiate a stuck data profile.
  * The class identifier is set, the stuck threshold is initialized to 0 to 
  * signify that the component is not yet configured, and the component is
  * reset.
  */
  DC_StuckDataProfile(void);

  /**
  * Set the stuck threshold.
  * @see #doProfileCheck
  * @param stuckThreshold the value of the stuck threshold
  */
  void setStuckThreshold(unsigned int stuckThreshold);

  /**
  * Get the stuck thresholde.
  * @see #setStuckThreshold
  * @return the value of the stuck threshold
  */
  unsigned int getStuckThreshold(void) const;

  /**
  * Perform a class-specific configuration check on the monitoring
  * profile: verify that the stuck threshold has a value greater than zero.
  * @return true if the monitoring profile is configured, false otherwise.
  */
  virtual bool isObjectConfigured(void);

  /**
   * Reset the stuck value profile check. With reference to the 
   * implementation of method <code>doProfileCheck(TD_Integer)</code>, a call to
   * this method causes the variable <code>counter</code> to be reset to
   * zero and the variable <code>previousValue</code> to be reset to 
   * PREVIOUS_VALUE_INIT.
   */
   virtual void reset(void);

};

#endif
