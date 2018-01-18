//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// RangeProfile.h
//
// Version	1.1
// Date		16.01.03 (Version 1.0)
//          01.10.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: replaced double and int with TD_Float and TD_Integer

#ifndef RangeProfileH
#define RangeProfileH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "MonitoringProfile.h"

/**
 * Base class for monitoring profile components that
 * build a monitoring check as a function of a range interval. 
 * The range interval is
 * characterized by a <i>lower bound</i> and by an <i>upper bound</i>
 * and takes the following form: [lowerBound, upperBound].
 * The lower and upper bounds are settable parameter. The upper bound
 * is constrained to be greater than the lower bound.
 * <p>
 * This class is abstract because it does not define any specific
 * monitoring checks. It only provides the services to define the
 * range interval
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */

class RangeProfile: public MonitoringProfile {

private:
    TD_Float lowerBound;
    TD_Float upperBound;

protected:

 /**
  * Version of method <CODE>doProfileCheck()</CODE> for monitored variables 
  * of type TD_Integer. The check is performed by using the "TD_Float" version
  * of <code>doProfileCheck</code>.
  * A pseudo-code implementation for this method is as follows: <PRE>
  *   return doProfileCheck( (TD_Float)value ); </PRE>
  * @see #doProfileCheck
  */
  virtual bool doProfileCheck(TD_Integer value);

 /**
  * This method shall be implemented by the derived classes.
  */
  virtual bool doProfileCheck(TD_Float value) = 0;

public:

 /**
  * Instantiate an range monitoring profile.
  * The lower and upper values are both set
  * to zero to signify that the component is not yet configured.
  */
  RangeProfile(void);

 /**
  * Set the lower bound.
  * @param lowerBound the value of the lower bound
  */
  void setLowerBound(TD_Float lowerBound);

 /**
  * Set the upper bound.
  * @param upperBound the value of the lower bound
  */
  void setUpperBound(TD_Float upperBound);

 /**
  * Get the lower bound.
  * @return the value of the lower bound
  */
  inline TD_Float getLowerBound(void) const;

 /**
  * Get the upper bound.
  * @return the value of the lower bound
  */
  inline TD_Float getUpperBound(void) const;

 /**
  * Perform a class-specific configuration check on the range monitoring
  * profile: verify that the lower bound is smaller than the upper bound.
  * @return true if the monitoring profile is configured, false otherwise.
  */
  virtual bool isObjectConfigured(void);

};

#include "RangeProfile_inl.h"

#endif



