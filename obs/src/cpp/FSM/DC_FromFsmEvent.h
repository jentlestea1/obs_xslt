//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_FromFsmEvent.h
//
// Version	1.0
// Date		18.01.03
// Author	A. Pasetti (P&P Software)

#ifndef DC_FromFsmEventH
#define DC_FromFsmEventH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/PunctualAction.h"
#include "DC_FsmEvent.h"

/**
* Default component encapsulating an FsmEvent that requests a transition in
* the target FSM between two states.
* The two states across which the transition is attempted are the
* <i>starting state</i> and the <i>target state</i>.
* Both are configuration parameters for the FsmEvent.
* When the FsmEvent is fired, it checks whether the target FSM is in the
* starting state and, if it is, it
* makes a request for a transition to the target state.
* If the target FSM is not in the starting state, no action is taken.
* <p>
* @author Alessandro Pasetti (P&P Software GmbH)
* @version 1.0
*/
class DC_FromFsmEvent : public DC_FsmEvent {

  private:
   TD_FsmStateIndex startingState;

  public:

   /**
    * Instantiate an FromFsmEvent object. Set the class identifier and
    * initialize the starting state.
    * The starting state is initialized to an illegal values to signify that
    * the FromFsmEvent is not yet configured.
    */
    DC_FromFsmEvent(void);

   /**
    * Setter method for the starting state.
    * The starting state is expressed as an integer that should be in the
    * range [0,N-1] where N is the total number of states in the target FSM.
    * This is an initialization method.
    * <p>
    * @param startingState the starting state
    */
    void setStartingState(TD_FsmStateIndex startingState);

   /**
    * Getter method for the starting state.
    * <p>
    * @return the starting state
    */
    TD_FsmStateIndex getStartingState(void) const;

   /**
    * Perform a class-specific configuration check on a repository object:
    * verify that the starting state has been
    * loaded and that it has a legal value.
    * The legality of the starting state is checked by verifying that its
    * value lies in the range [0,N-1] where N is the total
    * number of states in the target FSM.
    * <p>
    */
    virtual bool isObjectConfigured(void);

  protected:

   /**
    * Execute the FsmEvent: lodge a request to the target FSM to perform a
    * state transition from the
    * starting state to the target state.
    * The request is only lodged if the FSM is in the starting state.
    * A pseudo-code implementation for this method is as follows: <PRE>
    *   if (targetFsm.getCurrentState() eq startingState)
    *       targetFsm.makeTransitionRequest(targetState);
    *       return ACTION_SUCCESS;
    *   else
    *       return ACTION_FAILURE; </PRE>
    * <p>
    * @return the ACTION_SUCCESS code if the transition request was lodged,
    * the ACTION_FAILURE code if it was not
    */
    virtual TD_ActionOutcome doAction(void);

};

#endif
