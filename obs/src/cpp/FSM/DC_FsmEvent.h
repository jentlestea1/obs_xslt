//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_FsmEvent.h
//
// Version	1.0
// Date		01.10.02
// Author	A. Pasetti (P&P Software)

#ifndef DC_FsmEventH
#define DC_FsmEventH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/PunctualAction.h"

/**
 * Base class from which all FsmEvents are derived.
 * An FsmEvent is a <i>punctual action</i> that, when it is executed, causes
 * an FSM to attempt a state transition.
 * The FSM upon which the FsmEvent acts is called the <i>target FSM</i>.
 * The FSM state to which the transition is commanded is called the <i>target
 * state</i>.
 * Both the target FSM and target state are encapsulated in the FsmEvent
 * object as configuration parameters.
 * This class encapsulate the following FsmEvent execution logic: when the
 * event is executed, a state
 * transition request to the target state is made to the target FSM.
 * Other FsmEvent execution logic would in principle be possible.
 * For instance, the state transition request might be not just to a certain
 * target state but from a given starting state to a given target state.
 * Alternative execution logic can be implemented by subclassing this class
 * and overriding its <CODE>doAction</CODE> method.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup FSM
 */
class DC_FsmEvent : public PunctualAction {

  private:
   CC_FSM* pTargetFsm;
   TD_FsmStateIndex targetState;

  public:

    /**
     * Instantiate an FsmEvent object. Set the class identifier and initialize
     * the target FSM and the target state.
     * The target FSM and the target state are initialized to illegal values
     * to signify that the FsmEvent is not
     * yet configured.
     */
    DC_FsmEvent(void);

    /**
     * Setter method for the target FSM.
     * This is an initialization method.
     * <p>
     * @param pTargetFsm the target FSM
     */
    void setTargetFsm(CC_FSM* pTargetFsm);

    /**
     * Setter method for the target state.
     * The target state is specified as an index that must lie in the range
     * [0,N-1] where N is the total number of states in the target FSM.
     * <p>
     * This is an initialization method.
     * <p>
     * @see #isObjectConfigured
     * @param targetState the target state
     */
    void setTargetState(TD_FsmStateIndex targetState);

    /**
     * Getter method for the target FSM.
     * <p>
     * @return the target FSM
     */
    CC_FSM* getTargetFsm(void) const;

    /**
     * Getter method for the target state.
     * <p>
     * @see #setTargetState
     * @return the target state
     */
    TD_FsmStateIndex getTargetState(void) const;

    /**
     * Perform a class-specific configuration check on a FsmEvent object:
     * verify that the target FSM has been
     * loaded, that the target state has been loaded, and that the loaded
     * target state has a legal value.
     * The legality of the target state is checked by verifying that its
     * value lies in the range [0,N-1] where N is the total
     * number of states in the target FSM.
     * <p>
     */
    virtual bool isObjectConfigured(void);

  protected:

    /**
     * Execute the FsmEvent: lodge a request to the target FSM to perform a
     * state transition to the target state.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *   targetFsm.makeTransitionRequest(targetState);
     *   return ACTION_SUCCESS; </PRE>
     * The method assumes that the FsmEvent is correctly configured and that
     * a target FSM and target state have
     * been loaded.
     * No check is made about the current state of the FSM.
     * Applications that wish to implement a more complex execution logic
     * should override this method.
     * Only one return value can be returned by this implementation
     * signifiying a successful outcome to execution
     * of the puncutal action.
     * <p>
     * @see PunctualAction#execute
     * @return the SUCCESS code for the FsmEvent punctual action
     */
    virtual TD_ActionOutcome doAction(void);

};

#endif
