//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyObsClock.h
//
// Version	1.0
// Date		14.09.02
// Author	     A. Pasetti (P&P Software)

#ifndef DummyObsClockH
#define DummyObsClockH

#include "../GeneralInclude/BasicTypes.h"
#include "ObsClock.h"

/**
 * Dummy OBS Clock component useful for testing purposes or for applications
 * where timing information is not available.
 * This component provides a dummy implementation of the OBS Clock abstract
 * class. It exposes a method <code>setTime</code> through which an external
 * entity can set the on-board time and the on-board cycle. These values are
 * then returned by the standard timing services declared by the OBS Clock
 * abstract base class. No timing synchronization service is implemented.
 * <p>
 * A dummy clock can be useful because the correct configuration of the
 * <code>CC_RootObject</code> class requires the class to be provided with an
 * OBS Clock plug-in component. This dummy component can be used when no "real"
 * OBS Clock component is available (for instance, during testing).
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_DummyObsClock : public ObsClock {

     TD_ObsCycle cycle;
     TD_ObsTime time;

public :

     /**
      * Reset the OBS Clock component and set the class identifier.
      * @see #reset
      */
     DC_DummyObsClock(void);

     /**
      * Return the on-board time last set with <code>setTime</code>.
      * @see #setTime
      * @return the current on-board time
      */
	virtual TD_ObsTime getTime(void);

     /**
      * Return the on-board cycle last set with <code>setTime</code>.
      * @see #setTime
      * @return the current on-board cycle
      */
	virtual TD_ObsCycle getCycle(void);

     /**
      * No synchronization service is implemented: method returns without
      * taking any action.
      */
	virtual void synchronizeWithSystemTime(void);

     /**
      * Reset the OBS clock by resetting the on-board time and cycle to zero.
      */
     virtual void reset(void);

     /**
      * Set the value of the on-board time that will be returned
      * by method <code>getTime</code> and <code>getCycle</code>. The on-board time 
      * value must be zero or a positive number.
      * @see #getTime
      * @param time the on-board time
      */
     void setTime(TD_ObsTime time);

     /**
      * Set the value of the cycle that will be returned
      * by method <code>getCycle</code>. The cycle value 
      * must be zero or a positive numbers.
      * @see #getCycle
      * @param time the on-board time
      * @param cycle the on-board cycle
      */
     void setCycle(TD_ObsCycle cycle);
};

#endif
