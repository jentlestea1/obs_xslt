//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// ObsClock.h
//
// Version	1.0
// Date		12.09.02
// Author	A. Pasetti (P&P Software)

#ifndef ObsClockH
#define ObsClockH

#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"

/**
 * Abstract class representing the interface to an <i>OBS Clock Component</i> that can
 * provide timing-related information and services to the application.
 * OBS Clock Components can provide two types of timing information
 * and one service. The timing information are: the <i>on-board time</i>
 * and the <i>on-board cycle</i>. The service is the <i>timing synchronization
 * service</i>.
 * <p>
 * The <i>on-board time</i> is a time measurement provided by some external
 * source. The <i>on-board cycle</i> assumes that the application is running
 * cyclically and it represents the number of cycle from some arbitrary point
 * (for instance, the time of creation of the OBS clock component, or the time
 * it was last reset).
 * <p>
 * The <i>timing synchronization service</i> is an application-dependent service
 * to synchronize the on-board time maintained by the OBS clock component.
 * @todo create a PUSObsClock class derived from this class to implement 
 * PUS-specific timing services
 * @todo spilt the setTime method into two setter methods 
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class ObsClock : public CC_RootObject {

public :

     /**
      * Return the current on-board time.
      * @return the current on-board time
      */
	virtual TD_ObsTime getTime(void) = 0;

     /**
      * Return the current on-board cycle.
      * @return the current on-board cycle
      */
	virtual TD_ObsCycle getCycle(void) = 0;

     /**
      * Implement the timing synchronization service.
      */
	virtual void synchronizeWithSystemTime(void) = 0;

     /**
      * Reset the OBS clock.
      */
     virtual void reset(void) = 0;
};

#endif
