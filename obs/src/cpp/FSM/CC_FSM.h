//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// CC_FSM.h
//
// Version  1.0
// Date	    02.10.03 
// Author   A. Pasetti (P&P Software)
//
// Change Record:

#ifndef CC_FSMH
#define CC_FSMH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "FsmState.h"

/**
 * This class encapsulates a finite state machine or FSM.
 * This class implements the <CODE>FSM</CODE> core component.
 * <p>
 * The FSM is responsible for controlling the transition among the states of
 * the finite state machine and
 * for controlling the execution of the actions associated to these states.
 * The states associated to the FSM are loaded into the FSM during the object
 * configuration.
 * The states associated to the FSM are represented by objects of type
 * <CODE>FsmState</CODE>.
 * The states associated to the FSM are referred to using integers in the
 * range [0,N-1] where N is the total
 * number of states in the FSM.
 * The 0-th state is by convention the initial state of the FSM.
 * The <i>current state</i> is the state that is active at a particular point
 * in time.
 * <p>
 * The FMS is intended to be periodically <i>activated</i> by an external
 * entity (perhaps a scheduler).
 * When it is activated, the FSM executes the actions associated to the
 * current state and, if appropriate,
 * it performs a state transition.
 * State transitions can be either <i>autonomous</i> or they can be
 * <i>requested</i>.
 * An autonomous state transition takes place when the current state declares
 * it has terminated all its
 * actions (its <CODE>isFinished</CODE> method returns true) and it has a
 * non-null next state.
 * In that case, the FSM performs a transition to the next state offered by
 * the current state.
 * A requested state transition is started when an outside entity (typically,
 * an FsmEvent object) calls method
 * <CODE>makeTransitionRequest</CODE>.
 * State transitions take place only when the FSM is activated.
 * Thus, calls to <code>makeTransitionRequest</code> should really be seen as requests for
 * transitions that are buffered and
 * executed when the FSM is activated.
 * If several such state transition requests are made, only the last one will
 * be executed.
 * A transition - either requested or autonomous - takes place only if all
 * the following conditions are
 * satisfied: the transition is enabled, the exit check for the current state
 * returns "exit OK", the entry
 * check for the target state returns "entry OK".
 * <p>
 * Enabling or disabling of state transitions can be done only in the sense
 * of enabling/disabling the transitions <i>into</i> a particular state or
 * of disabling transitions <i>tout court</i>. That is,
 * it is not possible to enable/disable transitions <i>between</i> particular
 * states.
 * <p>
 * State transitions can be disabled at two levels.
 * It is possible to disable all transitions into a certain target state or
 * it is possible to disable transitions between
 * two specific states.
 * <p>
 * The FSM creates event reports to record the following occurrences: a state
 * transition has been performed.
 * <p>
 * The initialization sequence of an FSM is as follows: <ul>
 * <li>The number of states is set by calling <code>setNumberOfStates</code></li>
 * <li>The states are loaded by repeatedly calling <code>setState</code></li>
 * <li>The current state is set to its initial default value by calling
 * <code>reset</code></li>
 * </ul>
 * In all cases, the <i>event originator</i> is the FSM component itself.
 * <p>
 * The initialization sequence must be performed following the order given above.
 * The FSM object is intended to be used "as is" and without changes.
 * All its methods are accordingly declared to be final (i.e. non-virtual).
 * @see FsmState
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup FSM
 */
class CC_FSM : public CC_RootObject {

  private:
   TD_FsmStateIndex numberOfStates;
   bool allTransitionEnabled;       // enable/disable all state transitions
   bool* transitionEnabled;         // if transitionEnabled[i] is true, then
                                    // transitions into the i-th state are enabled.
   FsmState** pState;               // state[i] is the pointer to the i-th state
                                    // of the FSM
   FsmState* pCurrentState;         // currently active state of the FSM
   TD_FsmStateIndex currentState;   // index of the currently active state

   // If a state transition request was made, this variable stores the index
   // of the last target state to have been requested. If no state transition
   // was requested, this variable has a negative value.
   TD_FsmStateIndex requestedTargetState;

   // This variable is an array. nextState[i] holds the index of the next
   // state associated to the i-th state. This array is loaded when a reset()
   // is performed. It is useful to speed up execution of an autonomous state
   // transition.
   TD_FsmStateIndex* pNextState;

  protected:

    /**
     * Try to perform a state transtion from the current state to the target
     * state.
     * The transition is performed if all the following conditions are
     * satisfied: the transition is enabled, the exit check for the current
     * state returns "exit OK", the entry
     * check for the target state returns "entry OK".
     * If a transition is performed, an event report is created to record the
     * fact.
     * Event reports are also created when the state transition fails.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *   if (!isTransitionEnabled())
     *   {  createEventReport(EVT_FSM_ALL_TRANSITION_DISABLED);
     *      return;
     *   }
     *   if (!isTransitionEnabled(targetState))
     *   {  createEventReport(EVT_FSM_TRANSITION_DISABLED);
     *      return;
     *   }
     *   if (!currentState.canExit())
     *   {  createEventReport(EVT_FSM_EXIT_FAILED);
     *      return;
     *   }
     *   if (!targetState.canEnter())
     *   {  createEventReport(EVT_FSM_ENTER_FAILED)
     *      return;
     *   }
     *   currentState.doExit();
     *   currentState=targetState;
     *   currentState.doInit();
     *   createEventReport(EVT_FSM_TRANSITION);
     *   return; </PRE>
     * The index <code>targetState</code> should denote a legal state (ie. it should
     * lie in the interval [0,N-1] where N is the total number of states). No check
     * on its legality is performed.
     * @see #activate
     * @param targetState the target state
     */
    void tryTransition(TD_FsmStateIndex targetState);

  public:

    /**
     * Instantiate a finite state machine (FSM).
     * The number of states is initialized to an illegal value to signify
     * that the finite state machine is not yet configured.
     */
    CC_FSM(void);

    /**
     * Bring the FSM to its initial state (ie the state with index 0) and
     * enable all state transitions.
     * Unless the method is called just after the FSM was instantiated, a
     * termination action is performed on the state in which the FSM is at the
     * time the method is called. The initialization action is performed on the
     * initial state.
     * Finally, a call to this method causes the <code>nextState</code> array
     * to be loaded. Element <code>nextState[i]</code> holds the index of the next
     * state associated to the i-th state. This array is useful to speed up
     * execution of an autonomous state transition (see method <code>activate</code>
     * in this class). When an autonomous state transition is executed, the
     * FSM asks the <code>currentState</code> for its associated
     * <code>nextState</code> and makes a transition to this <code>nextState</code>.
     * The transition however can be done efficiently only if the target state
     * is specified through its index. The <code>nextState</code> array makes
     * precisely this information available. Note that, as a consequence,
     * changes to the <code>nextState</code> associated to a given state
     * become active only after the FSM has been reset.
     * <p>
     * The execution time of this method grows quadratically with the number
     * of states in the FSM.
     * <p>
     * A pseudo-code implementation for this method is as follows: <PRE>
     *   for (all states in the FSM)
     *      transitionEnabled[i] = ENABLED;
     *   for (all states in the FSM)
     *      nextState[i] = index of ( state[i].getNextState() );
     *   if (!initialization)
     *      currentState.doExit();
     *   currentState=initialState;
     *   currentState.doInit(); </PRE>
     * Note that no exit check is performed on the <code>currentState</code>
     * and no entry check is performed on the initial state.
     * @todo the implementation of this method is not robust against any of the
     * states having been loaded with an illegal nextState. It is not clear
     * whether this kind of robustness should be built into the method since
     * an illegal nextState would typically be the result of a configuration
     * error and the framework classes are not requierd to be robust against
     * configuration errors (but there should at least be an assertion-level
     * protection).
     * @see #activate
     */
   void reset(void);

    /**
     * Perform a class-specific configuration check on an FSM object: verify
     * that the number of states
     * has a legal value and that all FsmState objects have been loaded.
     */
    virtual bool isObjectConfigured(void);

    /**
     * Set the number of states to be managed by the FSM.
     * The FSM maintains an internal data structure where all FsmState
     * objects are held.
     * This method causes memory for this data structure to be allocated and
     * the data structure to be
     * initialized.
     * The number of states must be greater than zero.
     * <p>
     * This is an initialization method. It should only be called once.
     * <p>
     * @param numberOfStates the number of states to be managed by the FSM
     */
    void setNumberOfStates(TD_FsmStateIndex numberOfStates);

    /**
     * Get the number of states to be managed by the FSM.
     * If the number of states has not yet been set, a negative value is
     * returned.
     * <p>
     * @return the number of states managed by the FSM
     */
    TD_FsmStateIndex getNumberOfStates(void) const;

    /**
     * Load the i-th state into the FSM.
     * The state to be loaded is seen as an instance of the abstract class
     * <code>FsmState</code>.
     * The index <code>i</code> should denote a legal state (ie. it should
     * lie in the interval [0,N-1] where N is the total number of states). If
     * an illegal value of i is used, then the method generates an event report
     * of type EVT_ILLEGAL_ST and returns without taking any action.
     * @see #setNumberOfStates
     * @param i the state to be loaded
     * @param state the FsmState object to be loaded
     */
    void setState(TD_FsmStateIndex i, FsmState* state);

    /**
     * Get the FsmState associated to the i-th state of the FSM.
     * The index <code>i</code> should denote a legal state (ie. it should
     * lie in the interval [0,N-1] where N is the total number of states). No check
     * on its legality is performed.
     * @see #setState
     * @param i the state indicator
     * @return the FsmState associated to the i-th state
     */
    inline FsmState* getState(TD_FsmStateIndex i) const;

    /**
     * Get the current state.
     * @return the current state of the FSM
     */
    inline TD_FsmStateIndex getCurrentState(void) const;

    /**
     * Enable/disable all state transitions.
     * Both requested and autonomous transitions are disabled.
     * <p>
     * @see #activate
     * @param enabled the transition are disabled if false, enabled if true
     */
    void setTransitionEnableStatus(bool enabled);

    /**
     * Enable/disable transitions to the <code>toState</code>-th state.
     * Both requested and autonomous transitions are disabled.
     * The index <code>toState</code> should denote a legal state (ie. it should
     * lie in the interval [0,N-1] where N is the total number of states). If
     * an illegal value is used, then the method generates an event report
     * of type EVT_ILLEGAL_ST and returns without taking any action.
     * @see #activate
     * @param toState the state into which transitions are enabled/disabled
     * @param enabled the transition is disabled if false, enabled if true
     */
    void setTransitionEnableStatus(TD_FsmStateIndex toState, bool enabled);

    /**
     * Check whether state transitions are enabled.
     * @see #setTransitionEnableStatus
     * @return true if state transitions are enabled, false otherwise
     */
    inline bool isTransitionEnabled(void) const;

    /**
     * Check whether a transition from the current state to the argument
     * target state is enabled.
     * The index <code>toState</code> should denote a legal state (ie. it should
     * lie in the interval [0,N-1] where N is the total number of states). No check
     * on its legality is performed.
     * @see #activate
     * @param toState the target state
     * @return true if a transition from the current into the target state is
     * enabled
     */
    inline bool isTransitionEnabled(TD_FsmStateIndex toState) const;

    /**
     * Lodge a request for a transition to the argument target state.
     * The transition will be considered for execution at the next activation
     * of the FSM.
     * If a previous transition request had already been done, it is lost.
     * Only the last request is preserved and will be considered at
     * activation time.
     * The index <code>targetState</code> should denote a legal state (ie. it should
     * lie in the interval [0,N-1] where N is the total number of states). If
     * an illegal value is used, then the method generates an event report
     * of type EVT_ILLEGAL_ST and returns without taking any action.
     * @see #activate
     * @param targetState the target state for the requested transition
     */
    void makeTransitionRequest(TD_FsmStateIndex targetState);

    /**
     * Activate the FSM: execute the actions associated to the current state
     * and perform a state transition
     * if required.
     * An event report is created when a state transition takes place.
     * This method would typically be called by an external scheduler.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *   if (transition request pending)   // request lodged to make transition
     *                                     // to some targetState
     *   {  tryTransition(targetState);
     *      currentState.doContinue();
     *      return;
     *   }
     *   if ( (currentState.isFinished()) &&
     *         (currentState.getNextState()!=pNULL) )
     *      tryTransition(currentState.getNextState());
     *   currentState.doContinue();
     *   return; </PRE>
     * @see #tryTransition
     */
    void activate(void);
};

#include "CC_FSM_inl.h"

#endif


