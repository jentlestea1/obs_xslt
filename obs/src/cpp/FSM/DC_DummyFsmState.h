//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyFsmState.h
//
// Version	1.1
// Date		02.10.02 (Version 1.0)
//          25.02.03 (Version 1.1)
// Author	A. Pasetti (P&P Software)
//
// Change Record:
//   Version 1.1: fixed errors in CcDoc references

#ifndef DC_DummyFsmStateH
#define DC_DummyFsmStateH

#include "FsmState.h"

/**
 * Dummy FsmState useful for testing purposes and to represent FsmStates to
 * which no actions and no checks are associated. The actions
 * associated to the FsmState are implemented as dummy actions that return
 * without doing anything. The checks associated to the FsmState are implemented
 * to always return: "state can be entered", "state can be exited", and
 * "continued action has not yet terminated". This means that this state
 * is a stable state that will not be exited unless a state change is
 * commanded to the FSM.
 * @see CC_FSM
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.1
 */
class DC_DummyFsmState : public FsmState {

  public:

    /**
     * Instantiate a dummy FsmState object and initialize the activation counter
     * to zero.
     */
    DC_DummyFsmState(void);

    /**
     * Implement dummy continued action: the method increments the activation
     * counter by 1 returns.
     * <p>
     * @see FsmState#doContinue
     */
    virtual void doContinue(void);

};

#endif
