//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_NestedFsmActivatorWithEndState.h
//
// Version	1.1
// Date		31.05.03 (Version 1.0)
//          23.06.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: The class is now derived from DC_NestedFsmActivator. It used
//                to be derived from FsmState.

#ifndef DC_NestedFsmActivatorWithEndStateH
#define DC_NestedFsmActivatorWithEndStateH

#include "DC_NestedFsmActivator.h"

/**
 * FsmState that activates an FSM. This FsmState is useful to
 * implement "nested FSM" where one outer FSM controls one or more
 * "inner" FSMs. In this case, to each FsmState of the outer FSM,
 * one of the inner FSMs is associated. The task of the FsmStates is
 * to activate their associated FSMs. This class can be used to implement
 * one of these FsmStates.
 * <p>
 * A <code>DC_NestedFsmActivatorWithEndState</code> is configured with two parameters:
 * the <i>target FSM</i> and the <i>target state index</i>. The target
 * FSM is the FSM that the FsmState controls and must periodically
 * activate. The <i>continuation action</i> of an <code>DC_NestedFsmActivatorWithEndState</code>
 * consists in activating the target FSM.
 * <p>
 * The FsmState activates the target FSM until it has reached the
 * target state. At that point, the FsmState terminates. In other
 * words, the <i>termination check</i> of an <code>DC_NestedFsmActivator</code>
 * returns "terminated" when the taregt FSM has reached the target state.
 * <p>
 * The <i>initialization action</i> of the <code>DC_NestedFsmActivatorWithEndState</code>
 * is implemented to reset the target FSM.
 *
 * @see CC_FSM
 * @see DC_NestedFsmActivator
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @author R. Totaro
 * @version 1.1
 */
class DC_NestedFsmActivatorWithEndState : public DC_NestedFsmActivator {
private:
	TD_FsmStateIndex targetState;

public:

	/**
	 * Set the class identifier. The target state is initialized to an illegal
	 * value to signify that the object is not yet configured.
	 */
	DC_NestedFsmActivatorWithEndState(void);

	/**
	 * Set the target state index.
	 * @see #isFinished
	 */
	void setTargetState(TD_FsmStateIndex targetState);

	/**
	 * Get the target state index.
	 * @see #isFinished
	 */
	TD_FsmStateIndex getTargetState(void);

	/**
	 * Return true if the target FSM has reached the target state.
	 * @see FsmState#isFinished
	 * @return true if the target FSM has reached the target state
	 */
	virtual bool isFinished(void);

	/**
	 * Perform a class-specific configuration check: verify that the base
	 * class is configured and that the target state has been loaded.
	 * @return true if the object is configured, false otherwise.
	 */
	virtual bool isObjectConfigured(void);
};
#endif
