//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_NestedFsmActivatorWithExitCheck.h
//
// Version	1.0
// Date		04.07.03 (Version 1.0)
// Author	A. Pasetti, R. Totaro
//
// Change Record:

#ifndef DC_NestedFsmActivatorWithExitCheckH
#define DC_NestedFsmActivatorWithExitCheckH

#include "DC_NestedFsmActivator.h"

/**
 * FsmState that activates an FSM. This FsmState is useful to
 * implement "nested FSM" where one outer FSM controls one or more
 * "inner" FSMs. In this case, to each FsmState of the outer FSM,
 * one of the inner FSMs is associated. The task of the FsmStates is
 * activate their associated FSMs. This class can be used to implement
 * one of these FsmStates.
 * <p>
 * A <code>DC_NestedFsmActivatorWithExitCheck</code> is configured with two parameters:
 * the <i>target FSM</i> and the <i>target state index</i>. The target
 * FSM is the FSM that the FsmState controls and must periodically
 * activate. The <i>continuation action</i> of an <code>DC_NestedFsmActivatorWithExitCheck</code>
 * consists in activating the target FSM.
 * The FsmState thus implemented by an
 * <code>DC_NestedFsmActivatorWithExitCheck</code> is a stable state that,
 * barring any external action, never terminates.
 * <p>
 * This state performs an <i>exit check</i> that consists in verifying whether
 * the target FSM has reached the <i>target state</i> passed as to the
 * state as a configuration parameter.
 * <p>
 * The <i>initialization action</i> of the <code>DC_NestedFsmActivatorWithEndState</code>
 * is implemented to reset the target FSM.
 * @see CC_FSM
 * @see DC_NestedFsmActivator
 * @author Alessandro Pasetti
 * @author R. Totaro
 * @version 1.0
 */
class DC_NestedFsmActivatorWithExitCheck : public DC_NestedFsmActivator {
private:
	TD_FsmStateIndex targetState;

public:

	/**
	 * Set the class identifier. The target state is initialized to an illegal
	 * value to signify that the object is not yet configured.
	 */
	DC_NestedFsmActivatorWithExitCheck(void);

	/**
	 * Set the target state index.
	 * @see #canExit
	 */
	void setTargetState(TD_FsmStateIndex targetState);

	/**
	 * Get the target state index.
	 * @see #canExit
	 */
	TD_FsmStateIndex getTargetState(void);

	/**
	 * Return true (state can be exited) if the target FSM has reached
     * the target state.
	 * @see FsmState#canExit
	 * @return true if the target FSM has reached the target state
	 */
	virtual bool canExit(void);

	/**
	 * Perform a class-specific configuration check: verify that the base
	 * class is configured and that the target state has been loaded.
	 * @return true if the object is configured, false otherwise.
	 */
	virtual bool isObjectConfigured(void);
};
#endif
