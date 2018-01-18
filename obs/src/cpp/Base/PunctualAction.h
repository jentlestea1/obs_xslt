//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// PunctualAction.h
//
// Version	1.0
// Date		01.10.03 (version 1.0)
// Author	A. Pasetti (P&P Software)
//
// Change Record:

#ifndef PunctualActionH
#define PunctualActionH

#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"

/**
 * Base class from which all classes encapsulating punctual actions are
 * derived.
 * A <i>punctual action</i> is an action that is executed in one-shot mode,
 * namely an action that is activated
 * once and executes to completion during its single activation.
 * <p>
 * Punctual actions can be enabled and disabled.
 * Execution of a punctual action that is disabled has no effect.
 * <p>
 * Execution of a punctual action has an <i>outcome</i>.
 * The outcome of the execution of a punctual action is represented by the
 * value returned by the execution method. This value is internally saved
 * and punctual actions can be interrogated for their <i>last outcome</i>.
 * This is the outcome produced by the last execution of the punctual
 * action.
 * <p>
 * Execution of a punctual action is recorded through an event report.
 * The event records the fact that the punctual action was executed
 * (or that it was not executed because it was disabled).
 * <p>
 * This is an abstract class because the actions to be associated to the
 * punctual action must be specified by the subclasses.
 * The management of the enable status is however done in this class.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup Base
 */
class PunctualAction : public CC_RootObject {

  private:
   bool enabledStatus;
   TD_ActionOutcome lastOutcome;

  public:

    /**
     * Instantiate a punctual action. The enable status of the action is
     * initialized to "enabled". The last outcome is initialized to
     * ACTION_RESET.
     */
    PunctualAction(void);

    /**
     * Execute the punctual action if the punctual action is enabled,
     * otherwise do nothing. An event report is created to record the fact.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *   outcomeCode = ACTION_DISABLED;
     *   if ( isEnabled() ) {
     *      outcomeCode = doAction();
     *      createEventReport(EVT_PUNCTUAL_ACTION_EXEC);
     *   } else
     *      createEventReport(EVT_PUNCTUAL_ACTION_DIS);
     *   lastOutcome = outcomeCode;
     *   return outcomeCode;   </PRE>
     * The <CODE>doAction()</CODE> method is abstract and encapsulates the
     * implementation of the actions associated to
     * the punctual action.
     * Thus, this class enforces the check on the enabled status of the
     * punctual action and the
     * recording of the action outcome but delegates implementation of the
     * action to the derived classes.
     * <p>
     * This method implements the <i>trigger</i> or <i>execute</i> basic
     * operations for all framework components
     * that are instantiated from classes derived from
     * <CODE>PunctualAction</CODE>.
     * <p>
     * @see TD_ActionOutcome
     * @see TD_EventType
     * @return the outcome code of the punctual action that encodes the
     * results of the execution of the action
     * (success, failure, etc)
     */
    TD_ActionOutcome execute(void);

    /**
     * Set the enable status of the punctual action.
     * When the action is disabled, a call to method <CODE>execute()</CODE>
     * has no effect.
     * @param isEnabled if true, then the action is enabled; if false, then
     * the action is disabled
     */
    void setEnabled(bool isEnabled);

    /**
     * Check the enable status of the punctual action.
     * <p>
     * @return true if the punctual is enabled, false otherwise
     */
    bool isEnabled(void) const;

    /**
     * Get the <i>last outcome</i> of the punctual action. The last outcome
     * of the punctual action is the return value of method <code>execute</code>
     * the last time it was called. After component
     * instantiation or after a call to <code>resetLastOutcome</code>,
     * this method returns ACTION_RESET
     * @see #resetLastOutcome
     * @see TD_ActionOutcome
     * @see #execute
     * @return the last outcome of the punctual action
     */
    TD_ActionOutcome getLastOutcome(void) const;

    /**
     * Reset the value of the last outcome to ACTION_RESET.
     * @see #getLastOutcome
     * @see TD_ActionOutcome
     */
    void resetLastOutcome(void);

  protected:

    /**
     * Encapsulate implementation of the action associated to this punctual
     * action object.
     * This method is called by method <CODE>execute()</CODE> in this same
     * class.
     * Users of punctual actions do not see method <CODE>doAction()</CODE>,
     * they only see method <CODE>execute()</CODE>.
     * <p>
     * @see #execute
     * @return the outcome code of the punctual action that encodes the
     * results of the execution of the action
     * (success, failure, etc)
     */
    virtual TD_ActionOutcome doAction(void) = 0;

};

#endif
