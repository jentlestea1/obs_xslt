//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_UnstableFsmState.h
//
// Version	1.1
// Date		02.10.02 (Version 1.0)
//          25.02.03 (Version 1.1)
// Author	A. Pasetti (P&P Software)
//
// Change Record:
//   Version 1.1: fixed errors in CcDoc references

#ifndef DC_UnstableFsmStateH
#define DC_UnstableFsmStateH

#include "FsmState.h"

/**
 * FsmState that takes no action and exits immediately. This state is
 * useful as a placeholder state. The actions
 * associated to the FsmState are implemented as dummy actions that return
 * without doing anything. The checks associated to the FsmState are implemented
 * to always return: "state can be entered", "state can be exited", and
 * "continued action has terminated". This means that this state
 * is an unstable state that will be immediately exited.
 * @see CC_FSM
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.1
 */
class DC_UnstableFsmState : public FsmState {

  public:

    /**
     * Instantiate the FsmState and set its class identifier.
     */
    DC_UnstableFsmState(void);

    /**
     * This method returns without doing anything.
     * @see FsmState#doContinue
     */
    virtual void doContinue(void);

    /**
     * This method always returns "state has terminated".
     * @see FsmState#doContinue
     * @return always return true
     */
    virtual bool isFinished(void);

};

#endif
