//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// CriticalTelecommand.h
//
// Version	1.0
// Date		20.06.03 
// Author	A. Pasetti (P&P Software), R. Totaro

#ifndef CriticalTelecommandH
#define CriticalTelecommandH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Telecommand/Telecommand.h"

/**
 * Base class for telecommands with a potentially high criticality
 * level.
 * This is an abstract class. Concrete telecommands are obtained by
 * deriving this class.
 * <p>
 * This class adds to the basic functionalities defined by its base
 * class the possibility of marking a telecommand as <i>critical</i>.
 * Telecommands that are marked critical are executed according to an
 * "arm-fire" protocol. The basic idea is that the first time the
 * telecommand receives an execute request, it does not take any
 * action but it sets an internal status to "armed". The actual
 * execution of the telecommand only occurs when the second execute
 * request is received. The two execution requests must not occur too
 * far from each other in time and they must be made with exactly the
 * same set of parameters. The precise implementation of the "arm-fire"
 * mechanism is described below.
 * <p>
 * The telecommand can be in one of two states: <ul>
 * <li><i>NotArmed</i>: the telecommand is not armed</li>
 * <li><i>Armed</i>: the telecommand has been armed and is now ready
 * to execute</li>
 * </ul>
 * The arm status is maintained by the execution check (see comment
 * of method <code>canExecute</code>).
 * <p>
 * The telecommand maintains a <i>maximum armed duration</i>. Its
 * value represents the maximum time that can elapse between the
 * time when the "arm" command was received and the time when the
 * "fire" command is received. If the "fire" command is received after
 * this interval as elapsed, then an event report
 * is created to record the fact.
 * <p>
 * The telecommand defines an <i>image store</i> service and an
 * <i>image validity</i> check. Their purpose is to allow to verify that
 * telecommand parameters at the time the "arm" command is received
 * are the same as when the "fire" command is received. The image
 * store service allows the current values of the telecommand parameters
 * to be stored in some internal data structure. The image validity check
 * allows the current values of the telecomand parameters to be compared
 * with the values that were stored in the last call to the image store
 * service.
 * <p>
 * The criticality level of the telecommand can be set by the user.
 * The criticality level can have two values: <i>not critical</i> and
 * <i>critical</i>. If the telecommand is marked not critical, then
 * it behaves exactly as an instance of its super class.
 * <p>
 * This implementation of the "arm-fire" mechanism stores the information
 * about the arm status and about the telecommand parameters into the
 * telecommand component itself. Note in particular that the standard
 * telecommand manager provided by the OBS Framework (<code>CC_TelecommandManager</code>),
 * is not aware of whether a given telecommand is critical or not.
 * It is therefore the responsibility of the user to ensure that the
 * same component is loaded into the telecommand manager when the telecommand
 * is received the first time ("arm command") and when it is received the
 * second time ("fire command").
 * @see CC_TelecommandManager
 * @author Alessandro Pasetti
 * @author Roberto Totaro
 * @version 1.0
 * @ingroup Telecommand
 */
class CriticalTelecommand : public Telecommand {
private:
	TD_ObsTime maxArmedDuration;
    TD_ObsTime timeWhenArmed;
    ObsClock* pObsClock;
    bool isTcCritical;
    bool isTcArmed;

protected:

    /**
     * Encapsulate the implementation of the action associated with this critical
     * telecommand. This method verifies if the telecommand is armed and, if so,
	 * calls <code>doCriticalAction</code>, which implements the actual telecommand
	 * functionality. A non-critical telecommand is executed immediately (i.e. the
	 * arm-fire mechanism is disabled). A pseudo-code implementation of this method
	 * is as follows:
	 * <pre>
	 *    if (TC is armed or it is not critical) {
	 *       Disarm the TC
	 *       Set the "time when armed" to an invalid value
	 *       return doCriticalAction();
	 *    }
	 *    else {
	 *       Arm the TC
	 *       Save the current OBS time as "time when armed"
	 *       Add an EVT_CRIT_TC_ARMED event to the log
	 *       return ACTION_SUCCESS;
	 *    }
	 * </pre>
	 * <p>
     * This method is called by <code>PunctualAction::execute()</code>.
     * <p>
     * @see PunctualAction#execute
	 * @see #doCriticalAction
     * @return the outcome code of the telecommand action
     */
    virtual TD_ActionOutcome doAction(void);

    /**
     * A derived class shall provide a concrete implementation of this
	 * method, which performs the actual critical telecommand action.
	 * <code>doCriticalAction()</code> is invoked only the second time a
	 * specific critical telecommand is received (the first time, the telecommand
	 * is armed).
	 * <p>
     * This method is called by <code>doAction()</code>.
     * <p>
	 * @see #doAction
     * @return the outcome code of the telecommand action
     */
    virtual TD_ActionOutcome doCriticalAction(void) = 0;

public:
    /**
     * Instantiate a critical telecommand.
     * The arm status is set to "not armed". The maximum armed duration is set
     * to an illegal value to signify that the component is
     * not yet configured. The criticality level is set to "not critical".
     */
    CriticalTelecommand(void);

	/**
	 * Reverts the telecommand to its original state (i.e. isTcCritical=CRITICAL,
	 * isTcArmed=NOT_ARMED, timeWhenArmed=-1, maxArmedDuration=-1, pObsClock=pNULL).
	 */
	void reset(void);

    /**
     * Return the criticality level of the telecommand.
     * @return true if the telecommand is critical, false otherwise
     */
    bool isCritical(void);

    /**
     * Set the criticality level. This method would normally be called during
     * the component initialization phase (probably by the constructor of
     * the concrete telecommand class).
     * @param isCritical if true, the telecommand is marked "critical",
     * otherwise it is marked "not critical"
     */
    void setCriticalityLevel(bool isCritical);

    /**
     * Return the arm status of the telecommand. If the criticality level
     * of the telecommand is "not critical", this method always returns
     * "not armed".
     * @return true if the telecommand is armed, false otherwise
     */
    bool isArmed(void);

    /**
     * Execute the image validity check.
     * This class provides a default implementation that returns "image
     * is valid".
     * @see #canExecute
     * @return true if the telecommand is valid, false otherwise
     */
    virtual bool isImageValid(void);

    /**
     * Implement the image store service.
     * This class provides a default implementation that returns without
     * doing anything.
     * @see #canExecute
     */
    virtual void storeImage(void);

    /**
     * Set the maximum armed duration.
     * @param t the maximum armed duration
     * @see #canExecute
     */
    void setMaxArmedDuration(TD_ObsTime t);

    /**
     * Get the maximum armed duration.
     * @return the maximum armed duration
     */
    TD_ObsTime getMaxArmedDuration(void);

    /**
     * Get the value of the on-board time when the telecommand was last armed.
     * If the telecommand was never armed, a value of zero is returned.
     * @return the on-board time when the telecommand was last armed
     */
    TD_ObsTime getTimeWhenArmed(void);

    /**
     * Load the OBS Clock component. Critical telecommands need access to the
     * on-board clock to time-stamp the reception of an "arm" command.
     * @param pObsClock the OBS Clock component.
     */
    void setObsClock(ObsClock* pObsClock);

    /**
     * Return the OBS Clock component.
     * @see #setObsClock
     * @return the OBS Clock component.
     */
    ObsClock* getObsClock(void) const;

    /**
     * Perform the execution check on the telecommand.
     * A pseudo-code implementation of this method is as follows:
	 * <pre>
	 *    if (TC is critical and armed) {
	 *       if (TC has timed-out) {
	 *          Add an EVT_CRIT_TC_TIMEOUT event to the log
	 *          return false;
	 *       }
	 *
	 *       if (TC image is not valid) {
	 *          Add an EVT_CRIT_TC_IMG_INV event to the log
	 *          return false;
	 *       }
	 *    }
	 *
	 *    return true;
 	 * </pre>
     * @see CC_TelecommandManager#activate
     * @return true if the telecommand can execute, false otherwise
     */
    virtual bool canExecute(void);

    /**
     * Perform a class-specific configuration check on the telecommand:
     * verify that the maximum armed duration has a legal value and that
     * the on-board clock component has been loaded.
     * @return true if the component is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);
};

#endif
