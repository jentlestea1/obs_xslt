//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_OutOfRangeProfile.h
//
// Version	1.1
// Date		16.01.03 (Version 1.0)
//          01.10.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: replaced double and int with TD_Float and TD_Integer

#ifndef DC_OutOfRangeProfileH
#define DC_OutOfRangeProfileH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "RangeProfile.h"

/**
 * Default component implementing an "out of range" monitoring profile.
 * This monitoring profile reports a "deviation from profile" if the 
 * value of the monitored variable lies outside a predefined
 * range interval [lowerBound, upperBound].  
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.1
 */

class DC_OutOfRangeProfile: public RangeProfile {

protected:

  /**
  * Check whether the monitored value is outside the range.
  * If it is, a "devation from profile" is reported.
  * A pseudo-code implementation for this method is as follows: <PRE>
  *   if ( ( value<lowerBound) || (value>upperBound) )
  *      return MON_PROFILE_DEVIATION; 
  *   else
  *      return NO_MON_PROFILE_DEVIATION; </PRE>
  * <p>
  * @param value the value of the monitored variable
  * @return true if the monitored variable lies within the range, false otherwise
  */
  virtual bool doProfileCheck(TD_Float value);

public:

  /**
  * Instantiate an in-range monitoring profile.
  * The class identifier is set. 
  */
  DC_OutOfRangeProfile(void);

};

#endif
