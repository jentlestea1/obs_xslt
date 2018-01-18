//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_NestedFsmActivator.h
//
// Version	1.0
// Date		31.05.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)
//
// Change Record:

#ifndef DC_NestedFsmActivatorH
#define DC_NestedFsmActivatorH

#include "FsmState.h"
#include "CC_FSM.h"

/**
 * FsmState that activates an FSM. This FsmState is useful to
 * implement "nested FSM" where one outer FSM controls one or more
 * "inner" FSMs. In this case, to each FsmState of the outer FSM,
 * one of the inner FSMs is associated. The task of the FsmStates is
 * activate their associated FSMs. This class can be used to implement
 * one of these FsmStates.
 * <p>
 * A <code>DC_NestedFsmActivator</code> is configured with one parameter:
 * the <i>target FSM</i>. The target FSM is the FSM that the FsmState controls
 * and must periodically activate. The <i>continuation action</i> of an
 * <code>DC_NestedFsmActivator</code> consists in activating the target FSM.
 * <p>
 * The <i>initialization action</i> of the <code>DC_NestedFsmActivator</code>
 * is implemented to reset the target FSM.
 * <p>
 * All other actions and checks associated to the <code>DC_NestedFsmActivator</code>
 * have their default implementations as defined in the base class <code>FsmState</code>.
 * @see CC_FSM
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_NestedFsmActivator : public FsmState {
private:
	CC_FSM *pTargetFsm;

public:

	/**
	 * Set the class identifier.
	 */
	DC_NestedFsmActivator(void);

	/**
	 * Set the target FSM.
	 * @see #doContinue
	 */
	void setTargetFsm(CC_FSM *pTargetFsm);

	/**
	 * Get the target FSM.
	 * @see #doContinue
	 */
	CC_FSM *getTargetFsm(void);

	/**
	 * Activate the target FSM.
	 * @see FsmState#doContinue
	 */
	virtual void doContinue(void);

	/**
	 * Reset the target FSM.
	 * @see FsmState#doInit
	 */
	virtual void doInit(void);

	/**
	 * Perform a class-specific configuration check:
	 * verify that the target FSM has been loaded.
	 * @return true if the object is configured, false otherwise.
	 */
	virtual bool isObjectConfigured(void);
};
#endif
