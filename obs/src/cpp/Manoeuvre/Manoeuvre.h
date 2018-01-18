//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// Manoeuvre.h
//
// Version	1.0
// Date		10.04.03
// Author	A. Pasetti (P&P Software)

#ifndef ManoeuvreH
#define ManoeuvreH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"

/**
 * Base class from which all manoeuvre classes are derived.
 * A manoeuvre is primarily characterized by its ability to encapsulate
 * an action that takes place over a period of time. In this sense, it
 * is opposed to a <i>punctual action</i> which instead encapsulates
 * an action that takes place "in one shot".
 * More specifically, manoeuvres are
 * characterized by three types of <i>actions</i> and three
 * types of <i>checks</i> which they can
 * perform. The actions are:<ul>
 * <li>An <i>initialization action</i> that is executed once when the
 * manoeuvre first becomes due for execution.</li>
 * <li>A <i>continuation action</i> that is executed repeatedly until the
 * manoeuvre has terminated execution.</li>
 * <li>A <i>termination action</i> that is executed once when the manoeuvre
 * has terminated execution.</li>
 * </ul>
 * An <i>activation step counter</i> is associated to the continuation
 * action. This is initialized to zero when the manoeuvre starts execution
 * and is incremented by one every time the continuation action is advanced
 * by a step (i.e. every time method <code>doInternalContinue</code> is
 * executed). This counter helps other components keep track of the progress
 * of the manoeuvre.
 * <p>
 * The three checks that are associated to a manoeuvre are:<ul>
 * <li>A <i>start check</i> to be performed just before launching
 * execution of a manoeuvre. It verifies whether the manoeuvre is
 * ready to start execution.</li>
 * <li>A <i>continuation check</i> to be performed while the manoeuvre
 * is executing to verify whether continuation can be continued
 * or whether the manoeuvre should be aborted. </li>
 * <li>A <i>termination check</i> to be performed before terminating
 * execution of the manoeuvre. It checks whether the manoeuvre has
 * terminated its execution and whether it should be terminated.
 * </ul>
 * This class is abstract. Concrete manoeuvre actions and manoeuvre
 * checks are defined by subclasses. This class provides either default
 * trivial implementations or leaves the implementation of the actions
 * and checks undefined.
 * <p>
 * Execution of a manoeuvre as defined here must respect certain
 * constraints (e.g. a start check should be performed before
 * starting execution of a manoeuvre, a termination action should
 * be performed before terminating execution of a manoeuvre, etc).
 * Manoeuvres are defined here as low-level components that cannot
 * take responsibility for their own execution. They are intended
 * to be <i>loaded</i> into some other component that is then
 * responsible for calling their methods in the correct sequence
 * and in compliance with the constraints defined by the present
 * interface. This class implements assertions that, to some
 * extent, ensure that the manoeuvre is used correctly but
 * responsibility for correct usage lies with the component managing
 * a manoeuvre.
 * In the OBS Framework, manoeuvres are normally loaded in the
 * <i>manoeuvre manager</i> (instance of class <code>CC_ManoeuvreManager</code>)
 * which then becomes responsible for their execution.
 * <p>
 * This class additionally manages three boolean flags: <i>isExecuting</i>,
 * <i>inUse</i>, and <i>isSuspended</i>.
 * Flag isExecuting is set to true immediately after the execution of
 * the manoeuvre starts and is reset
 * to false when execution has terminated or the manoeuvre is aborted.
 * This flag is useful for external entities that wish to check whether
 * a manoeuvre is actually executing.
 * <p>
 * Manoeuvres are intended to be used by some other components. Since they have
 * an internal state, they cannot normally be used by more than one component at
 * a time. Flag inUse helps prevent this type of conflict. The component that
 * uses the manoeuvre should set it when it starts using it and should reset it
 * when it finishes using it. Normally, the management of the inUse flag is done
 * jointly by the manoeuvre factory component (instance of class <code>CC_ManoeuvreFactory</code>)
 * and by the manoeuvre manager.
 * <p>
 * Flag isSuspended is set to true to signify that execution of the manoeuvre
 * should be temporarily suspended ("the manoeuvre is held"). Execution
 * resumes when the flag is reset to false. When a manoeuvre is suspended,
 * its continuation action is not performed but this is the only
 * effect of suspension: the other two actions and all three checks remain
 * unaffected. However, when a manoeuvre terminates or aborts, its
 * isSuspended flag is set to false.
 * <p>
 * Certain changes in the execution state of a manoeuvre should be
 * recorded through event reports. This class is responsible for
 * creating event reports in the following cases: <ul>
 * <li>The manoeuvre is suspended or resumed (its isSuspended flag changes
 * value)</li>
 * <li>The manoeuvre starts and terminates execution (its isExecuting
 * flag changes value)</li>
 * <li>The manoeuvre is aborted</li>
 * </ul>
 * Manoeuvres can be <i>disabled</i> and <i>enabled</i>.
 * When a manoeuvre is disabled, its start check is guaranteed to
 * return: "manoeuvre cannot start". This class is responsible
 * for the management of the enable status and for ensuring that
 * this constraint is respected. Note that this means that changes
 * in the enable status of a manoeuvre have no effect upon
 * manoeuvres that are already executiong.
 * @see CC_ManoeuvreFactory
 * @see CC_ManoeuvreManager
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup Manoeuvre
 */
class Manoeuvre: public CC_RootObject {

private:
    bool executing;
    bool inUse;
    bool enabled;
    bool suspended;
    unsigned int activationStepCounter;

protected:

  /**
  * Encapsulate the implementation of the continuation actions to be carried
  * out by the manoeure.
  * This method is called by method <CODE>doContinue()</CODE> in this same class.
  * <p>
  * @see #doContinue
  */
  virtual void doInternalContinue(void) = 0;

  /**
  * Encapsulate the implementation of the actions to be carried out by the
  * manoeure after it is aborted.
  * This method is called by method <CODE>abort()</CODE> in this same class.
  * This class offers a default implementation that returns without taking
  * any actions.
  * @see #abort
  */
  virtual void internalAbort(void);

  /**
  * Encapsulate the implementation of the termination actions associated to
  * this manoeuvre.
  * This method is called by method <CODE>terminate()</CODE> in this same class.
  * This class offers a default implementation that returns without taking
  * any action.
  * @see #terminate
  */
  virtual void internalTerminate(void);

  /**
  * Encapsulate the implementation of the start check associated to
  * this manoeuvre.
  * This method is called by method <CODE>canStart()</CODE> in this same class.
  * This class offers a default implementation that returns "manoeuvre
  * can start".
  * @see #canStart
  * @return true if the manoeuvre can start execution, false otherwise
  */
  virtual bool internalCanStart(void);

public:

  /**
  * Instantiate a manoeuvre object.
  * The enabled status of the manoeuvre is initialized to "enabled".
  * The isExecuting, isInUse and isSuspended flags are initialized to false.
  * The activation step counter is initialized to zero.
  */
  Manoeuvre(void);

  /**
  * Perform the start check for the manoeuvre: return true if the manoeuvre is
  * ready to start execution.
  * This method should be called only on a manoeuvre that is already in used
  * but that is not yet executing.
  * Execution of a manoeuvre should be initiated only when this check has been
  * performed and has returned: "manoeuvre ready to start".
  * If a manoeuvre is disabled, the check always returns: "manoeuvre cannot
  * start". Otherwise, a manouvre-specific check is performed.
  * A pseudo-code implementation for this method is as follows: <PRE>
  *   if ( !isEnabled() )
  *     return MAN_CANNOT_START;
  *   else
  *     return internalCanStart(); </PRE>
  * The <CODE>internalCanStart()</CODE> method is virtual and encapsulates
  * the implementation of the manoeuvre-specific part of the start check.
  * @see CC_ManoeuvreManager#activate
  * @return true if the manoeuvre is ready to start
  */
  virtual bool canStart(void);

  /**
  * Perform the initialization action associated to this manoeuvre.
  * This method should be called on a manoeuvre that is alredy in use but
  * not yet executing. It should be called immediately before the execution of the
  * manoeuvre is initiated. It should be called only when the execution check
  * returns "manoeuvre can start".
  * This class offers a default implementation that returns without doing anything.
  * <p>
  * @see CC_ManoeuvreManager#activate
  * @see #canStart
  */
  virtual void initialize(void);

  /**
  * Perform the continuation check for the manoeuvre: return true if the
  * manoeuvre can safely continue execution.
  * A manoeuvre that whose continuation check returns "cannot continue
  * execution" should normally be aborted (method <code>abort</code>).
  * This class offers a default implementation that returns "manoeuvre can
  * continue".
  * <p>
  * This method should only be called on a manoeuvre that is in use and
  * that is already executing.
  * @see CC_ManoeuvreManager#activate
  * @see #abort
  * @return true if the manoeuvre can continue execution
  */
  virtual bool canContinue(void);

  /**
   * Return the continuation check code for the manoeuvre.
   * The continuation check code allows a manoeuvre to make information available about
   * the reasons for the failure of the continuation check. The return value of this
   * method is only valid if the continuation check has returned "manoeuvre cannot
   * continue" (ie. if method <code>canContinue</code> has returned false). This class
   * provides a default implementation that returns zero.
   * @see #canContinue
   * @return the continuation check code
   */
  virtual TD_CheckCode getContinuationCheckCode(void) const;

 /**
  * Advance the execution of the manoeuvre.
  * Manoeuvres execute over a prolonged period of time.
  * This method is intended to be called to advance the execution of the
  * manoeuvre.
  * The implementation provided by this class is responsible for managing the
  * isExecuting flag, for managing the activation step counter, and for
  * creating an event report when the status of
  * the flag changes from "not executing" to "executing" (this signals the
  * beginning of the execution of the manoeuvre).
  * Execution of the manoeuvre is advanced only if the manoeuvre is not
  * suspended.
  * A pseudo-code implementation for this method is as follows: <PRE>
  *   if ( !isExecuting ) {
  *     activationStepCounter = 0;
  *     isExecuting=true;
  *     createEventReport(EVT_MAN_STARTED);
  *   }
  *   if ( !isSuspended() ) {
  *     activationStepCounter++;
  *     doInternalContinue();
  *   } </PRE>
  * The <CODE>doInternalContinue()</CODE> method is virtual and encapsulates
  * the implementation of the actions to be performed by the manoeuvre. This
  * method is only called if the manoeuvre is not suspended.
  * The <CODE>isExecuting</CODE> flag is initialized to false by the constructor
  * and is reset to false when the manoeuvre has finished execution or is aborted.
  * Note that the activation
  * step counter is implemented as an unsigned integer and there is no protection
  * against overflow. This puts an upper ceiling on the number of activation
  * steps of a manoeuvre.
  * The <code>manId</code> parameter in the pseudo-code is a manoeuvre identifier.
  * This class uses the <i>class identifier</i> of the manoeuvre component as
  * manoeuvre identifier.
  * <p>
  * This method should only be called on a manoeuvre that is already in use.
  * @see TD_EventType
  * @see CC_ManoeuvreManager#activate
  */
  void doContinue(void);

  /**
  * Abort execution of a running manoeuvre.
  * If the manoeuvre is not currently executing (if the isExecuting flag is
  * false), no action is taken. Otherwise, its execution status is changed
  * to "not executing", an event reporting the abort operation is created, and
  * the abort operations are executed.
  * The manoeuvre is forced into "not suspended" status (its isSuspended flag
  * is set to false).
  * <p>
  * In general, a manoeuvre may be aborted either as a result of an autonomous
  * decision of an external entity or because the manoeuvre itself declares that
  * it is unable to continue execution (i.e. its <CODE>canContinue</CODE> method
  * returns false) in which case the manoeuvre must be aborted.
  * After being aborted, a manoeuvre should be de-scheduled and should no
  * longer be considered for execution.
  * A pseudo-code implementation for this method is as follows: <PRE>
  *   isSuspended = false;
  *   if ( !isExecuting )
  *     return;
  *   else {
  *     isExecuting = false;
  *     createEventReport(EVT_MAN_ABORTED);
  *     internalAbort(void);
  *   } </PRE>
  * The <CODE>internalAbort()</CODE> method is intended to be overridden by
  * subclasses to specify concrete actions to be taken by a manoeuvre that is
  * aborted. These would typically be clean-up actions that bring the
  * internal state of the manoeuvre to some pre-defined and consistent state.
  * @see TD_EventType
  * @see #canContinue
  * @see CC_ManoeuvreManager#activate
  * @see CC_ManoeuvreManager#abort
  */
  void abort(void);

  /**
  * Perform the termination actions associated to this manoeuvre.
  * This method is intended to be called when a manoeuvre has terminated
  * execution nominally (after its <code>isFinished</code> method returns true).
  * It can be used to implement any clean-up actions that is required at the end
  * of a manoeuvre's execution.
  * The manoeuvre is forced into "not suspended" status (its isSuspended flag
  * is set to false).
  * The implementation in this class is responsible for resetting the
  * isExecuting and isSuspended flags and for creating an event report recording the termination of
  * the manoeuvre. A pseudo-code implementation for this method is as follows: <PRE>
  *   isSuspended = false;
  *   isExecuting = false;
  *   createEventReport(EVT_MAN_TERMINATED);
  *   internalTerminate(); </PRE>
  * The <CODE>internalTerminate()</CODE> method can be overridden by concrete
  * subclasses to implement their own termination actions.
  * <p>
  * This method should only be called on a manoeuvre that is in use and
  * that is already executing.
  * @see TD_EventType
  * @see #doContinue
  * @see CC_ManoeuvreManager#activate
  */
  void terminate(void);

  /**
  * Perform the termination check for the manoeuvre: return true if the manoeuvre
  * has terminated executing its allotted actions.
  * After this method returns "manoeuvre has terminated", the termination
  * action should be executed.
  * @see CC_ManoeuvreManager#activate
  * @return true if the manoeuvre has terminated execution
  */
  virtual bool isFinished(void) = 0;

  /**
  * Set the value of the inUse flag.
  * @see TD_EventType
  * @see CC_ManoeuvreManager#load
  * @param newInUse the new value of the inUse flag
  */
  void setInUse(bool newInUse);

  /**
  * Return the value of the inUse flag.
  * @return the value of the inUse flag
  */
  bool isInUse(void) const;

  /**
  * Set the value of the isSuspended flag. If the requested value of the
  * flag is different from the current value (indicating a change in the
  * state of the manoevre), this is recorded through an even report.
  * A pseudo-code implementation for this method is as follows: <PRE>
  *   if ( isSuspended and !newIsSuspended )      // manoeuvre is resumed
  *     createEventReport(EVT_MAN_RESUMED);
  *   else if ( !isSuspended and newIsSuspended )
  *     createEventReport(EVT_MAN_SUSPENDED);
  *   isSuspended = newIsSuspended; </PRE>
  * @see TD_EventType
  * @see #doContinue
  * @param newIsSuspended the new value of the isSuspended flag
  */
  void setIsSuspended(bool newIsSuspended);

  /**
  * Return the value of the isSuspended flag.
  * @return the value of the isSuspended flag
  */
  bool isSuspended(void) const;

  /**
  * Return the value of the isExecuting flag.
  * @return the value of the isExecuting flag.
  */
  bool isExecuting(void) const;

  /**
  * Set the enable status of the manoeuvre.
  * @param isEnabled if true, then the manoeuvre is enabled; if false, then
  * the manoeuvre is disabled
  */
  void setEnabled(bool isEnabled);

  /**
  * Check the enable status of the manoeuvre profile.
  * @return true if the manoeuvre is enabled, false otherwise
  */
  bool isEnabled(void) const;

  /**
  * Return the value of the activation step counter.
  * @see #doContinue
  * @return the current value of the activation step counter
  */
  unsigned int getActivationStepCounter(void) const;

};

#endif

