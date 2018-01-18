//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// FsmState.h
//
// Version	1.0
// Date		25.02.03 
// Author	A. Pasetti (P&P Software)
//
//
// Change Record:

#ifndef FsmStateH
#define FsmStateH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"

/**
 * Base class from which all FsmState classes are derived.
 * An FsmState class encapsulates a state of an finite state machine (FSM).
 * <p>
 * This is an abstract class that declares abstract methods to implement: the
 * actions associated to the
 * FsmState and the checks associated to the FsmState.
 * Concrete methods are also defined to implement configuration operations.
 * <p>
 * An FsmState can execute three types of actions.
 * An <i>initialization action</i> that is a punctual action performed
 * immediately after the state is entered.
 * A <i>continuation action</i> that is an action performed every time the
 * state is activated.
 * A <i>termination action</i> that is a punctual action that is performed
 * immediately before the state is exited.
 * This class provides default implementation for the initialization and
 * termination actions that do not do anything.
 * <p>
 * An FsmState performs three types of checks.
 * An <i>initialization check</i> that checks whether the state can be
 * entered.
 * A <i>exit check</i> that checks whether the state can be exited.
 * A <i>termination check</i> that checks whether the state has terminated
 * execution and is ready to perform
 * an autonomous state transition.
 * This class provides default implementations for the initialization and
 * exit checks that always return true (check is passed).
 * <p>
 * An FsmState holds a reference to a <i>next state</i>.
 * This represents the state to which the current state wants to perform an
 * autonomous transition after it
 * has performed all its actions.
 * FsmStates however are "passive" objects and state transitions are under
 * the control of the FSM.
 * This class provides a default implementation that returns a null pointer
 * for the next state signifying that
 * there is no next state.
 * @see CC_FSM
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup FSM
 */
class FsmState : public CC_RootObject {

  private:
   FsmState* pNextState;

  public:

    /**
     * Instantiate an FsmState object.
     * The next state is initialized to pNULL.
     */
    FsmState(void);

    /**
     * Perform the entry check and return false if a transition into this
     * state would put the system
     * in an inconsistent or otherwise undesirable condition.
     * Note that the ultimate decision as to whether the state is entered or
     * not lies with the FSM that could
     * decide to ignore the return value of canEnter().
     * This class provides a default implementation that returns true (state
     * can be entered).
     * @see CC_FSM#activate
     * @return true if the state can be safely entered.
     */
    virtual bool canEnter(void);

    /**
     * Perform the initialization action associated to the FsmState.
     * This method is intended to be called by the FSM immediately after the
     * state has been entered.
     * This class provides a default implementation that returns without
     * doing anything.
     * @see CC_FSM#activate
     */
    virtual void doInit(void);

    /**
     * Perform the exit check and return false if performing a transition out
     * of the this state would leave
     * the system in an inconsistent or otherwise undesirable condition.
     * Note that the ultimate decision as to whether the state is exited or
     * not lies with the FSM that could
     * decide to ignore the return value of canExit().
     * This class provides a default implementation that returns true (state
     * can be exited).
     * @see CC_FSM#activate
     * @return true if the manoeuvre can continue execution
     */
    virtual bool canExit(void);

    /**
     * Perform the continued action associated to this state.
     * This method is intended to be called by the FSM every time it is
     * activated when this state is the
     * current state.
     * @see CC_FSM#activate
     */
    virtual void doContinue(void) = 0;

    /**
     * Perform the exit action associated to this state.
     * This method is intended to be called by the FSM object just before it
     * exits this state.
     * This class provides a default implementation that returns without
     * doing anything.
     * @see CC_FSM#activate
     */
    virtual void doExit(void);

    /**
     * Perform a termination check and return true if the continued action
     * associated to this state has
     * been completed and an autonomous transition to a next state should be
     * performed.
     * This class provides a default implementation that always returns "not
     * terminated".
     * @see CC_FSM#activate
     * @return true if the continued action associated to this state has been
     * terminated, false otherwise
     */
    virtual bool isFinished(void);

    /**
     * Set the next state associated to this state.
     * This method would normally be called only once during the application
     * initialization phase.
     * However, it is not formally classified as an <i>initialization
     * method</i> in order to leave the option
     * open to FsmState objects to dynamically set their next state on the
     * basis of their termination status.
     * @param pNextState the next state associated to the current state
     */
    inline void setNextState(FsmState* pNextState);

    /**
     * Return the next state associated to this state.
     * If no next state is associated to this state, then the method return
     * pNULL.
     * @return the next state associated to the current state
     */
    inline FsmState* getNextState(void) const;

};

#include "FsmState_inl.h"

#endif


