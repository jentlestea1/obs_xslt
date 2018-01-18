//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// ModeManager.h
//
// Version	1.0
// Date		13.04.03 
// Author	A. Pasetti (P&P Software)
//
// Change Record:

#ifndef ModeManagerH
#define ModeManagerH

#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"

/**
 * Base class from which all classes encapsulating mode managers are
 * derived.
 * Conceptually, a mode manager is characterized by:<ul>
 * <li>A set of <i>operational modes</i> of which, at any given time,
 * one and only one is the <i>current operational mode</i>,</li>
 * <li>A set of <i>strategies</i>,</li>
 * <li>For each strategy, a set of <i>implementations</i> of which,
 * at any given time, one and only one is the <i>current implementation</i>,
 * and</li>
 * <li>An <i>update mechanism</i> for controlling the change in the current
 * operational mode.</li>
 * </ul>
 * This is an abstract class because it only defines the management of
 * the operational mode. All other aspects listed above are defined and/or
 * implemented by subclasses.
 * <p>
 * Changes in operational mode are recorded through an event report.
 * It is possible to selectively disable transitions to certain
 * operational modes or to disable all mode transitions.
 * <p>
 * An initialization sequence for this class consists of the following
 * steps: <ul>
 * <li>Set the number of modes with method <code>setNumberOfModes</code></li>
 * <li>Set the default mode with method <code>setDefaultMode</code></li>
 * <li>Reset the component by calling method <code>reset</code></li>
 * </ul>
 * The above operations must be performed in the order given.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup Base
 * @ingroup ModeManagement
 */
class ModeManager : public CC_RootObject {

  private:
   bool* enabledStatus;    // this is an array
   bool transitionsEnabled;
   TD_Mode numberOfModes;
   TD_Mode currentMode;
   TD_Mode defaultMode;

  public:

    /**
     * Instantiate a mode manager. The number of modes, the current
     * mode, and the default mode are set to illegal values to signify
     * that the component is not yet initialized.
     */
    ModeManager(void);

    /**
     * Execute the <i>update operation</i> for the mode manager.
     * This method is declared abstract because the update mechanism is
     * application-specific and must be defined by concrete subclasses.
     * A pseudo-code implementation for a typical implementation of this
     * method takes the following form: <PRE>
     *   newMode = . . .    // compute new operational mode;
     *   setMode(newMode);</PRE>
     * Thus, the method computes the new mode and then uses the
     * <code>setMode</code> method to attempt a mode update. Note that
     * it is this latter method that is responsible for enforcing
     * the mode transition inhibitions and for reporting mode changes
     * as events.
     * <p>
     * This method implements the <i>update</i> basic
     * operation of mode managers.
     * @see #setMode
     */
    virtual void update(void) = 0;

    /**
     * Set the number of modes of the mode manager.
     * This is an initialization method. It should only be called once.
     * Successive calls have no effect. The number of modes should be
     * greater than zero.
     * <p>
     * A pseudo-code implementation for this method is as follows: <PRE>
     *      . . .    // allocate memory for internal data structures
     *      allocateMemory(numberOfModes); </PRE>
     * Concrete mode managers will normally use some internal data
     * structure to hold mode-related information. The memory for this
     * data structure must be allocated when the component is initialized.
     * The call to the protected and abstract method <code>allocateMemory</code>
     * can be used for this purpose.
     * <p>
     * This is an initialization method. It should be called only once. Only
     * positive number of modes are legal.
     * @see allocateMemory
     * @param numberOfModes the number of modes
     */
    void setNumberOfModes(TD_Mode numberOfModes);

    /**
     * Set the default mode of the mode manager.
     * The default mode of the mode manager is its operational mode at the
     * end of the configuration process or after a
     * call to method <code>rest</code>. The default mode argument must lie in the
     * interval [0,N-1] where N is the total number of modes. If an illegal
     * default mode is used, then the method generates an event report of type
     * EVT_ILLEGAL_MM and returns without taking any action.
     * @param defaultMode the default mode
     */
    void setDefaultMode(TD_Mode defaultMode);

    /**
     * Enable/disable all mode transitions.
     * When mode transitions are disabled, the current operational mode is
     * never changed.
     * @see #update
     * @param enabled the transition are disabled if false, enabled if true
     */
    void setTransitionEnableStatus(bool enabled);

    /**
     * Enable/disable transitions to the toMode-th operational mode.
     * The toMode argument must lie in the
     * interval [0,N-1] where N is the total number of modes. If an illegal
     * default mode is used, then the method generates an event report of type
     * EVT_ILLEGAL_MM and returns without taking any action.
     * @see #update
     * @param toMode the operational mode to which transitions are enabled/disabled
     * @param enabled the transition is disabled if false, enabled if true
     */
    void setTransitionEnableStatus(TD_Mode toMode, bool enabled);

    /**
     * Check whether mode transitions are enabled.
     * @see #setTransitionEnableStatus
     * @return true if mode transitions are enabled, false otherwise
     */
    inline bool isTransitionEnabled(void) const;

    /**
     * Check whether transitions to the argument target mode are enabled.
     * @see #setTransitionEnableStatus
     * @param toMode the target mode
     * @return true if a transition into the target mode is enabled
     */
    inline bool isTransitionEnabled(TD_Mode toMode) const;

    /**
     * Return the current operational mode.
     * @return the current mode
     */
    inline TD_Mode getCurrentMode(void) const;

    /**
     * Return the number of operational mode.
     * @return the number of operational modes
     */
    inline TD_Mode getNumberOfModes(void) const;

    /**
     * Enable all mode transitions and set the operational mode to the default
     * mode. This method is declared virtual so as to allow concrete mode managers
     * to define more specific reset operations.
     */
    virtual void reset(void);

    /**
     * Perform a class-specific configuration check on a mode manager: verify
     * that the number of modes and the default modes have legal values.
     * @return true if the object is configured, false otherwise
     */
    virtual bool isObjectConfigured(void);

  protected:

    /**
     * Change the operational mode the mode manager.
     * This method is responsible for managing the event reporting
     * mechanism and the mode transition inhibition mechanism.
     * All mode changes should occurr through this method. This in
     * particular applies to changes commanded by implementations of
     * method <code>update</code> in derived classes.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *   if (newMode != currentMode)
     *      if (isTransitionEnabled() && isTransitionEnabled(newMode))
     *        currentMode = newMode;
     *        createEventReport(EVT_MOD_TRANS_PERFORMED);
     *      else
     *        createEventReport(EVT_MOD_TRANS_INHIBITED);</PRE>
     * where <code>currentMode</code> is the operational mode at the
     * time the method is called and <code>instanceId</code> is the
     * instance identifier of the mode manager component.
     * @see #update
     * @see TD_EventType
     * @see CC_RootObject
     * @param newMode the new operational mode
     */
    void setMode(TD_Mode newMode);

    /**
     * Allocate the memory for the internal data structures whose size
     * depends on the number of modes.
     * @see #setNumberOfModes
     * @param numberOfModes the number of modes
     */
    virtual void allocateMemory(TD_Mode numberOfModes) = 0;

};

#include "ModeManager_inl.h"

#endif



