//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyRecoveryAction.h
//
// Version	1.0
// Date		25.06.03 (version 1.0)
// Author	R. Totaro

#ifndef DC_DummyRecoveryActionH
#define DC_DummyRecoveryActionH

#include "../GeneralInclude/BasicTypes.h"
#include "RecoveryAction.h"

/**
 * Recovery action that performs no action and returns a configurable
 * outcome (see <code>setActionOutcome()</code>). This recovery action is
 * used only for testing purposes.
 * @author Roberto Totaro
 * @version 1.0
 */
class DC_DummyRecoveryAction : public RecoveryAction {
private:
	bool             actionCanExecute;
	TD_ActionOutcome actionOutcome;

protected:
	/**
	 * Return <code>actionOutcome</code> without taking any action.
	 * @see #setActionOutcome
	 * @see RecoveryAction#doAction
	 * @return return the outcome code set by the caller
	 */
	virtual TD_ActionOutcome doRecoveryAction(void);

	/**
	 * Return <code>actionCanExecute</code>.
	 * @see #setExecutionFlag
	 * @see RecoveryAction#doAction
     * @return true if the action can be executed, false if the action cannot
     * be executed. 
	 */
	virtual bool canExecute(void);

public:
	/**
	 * Instantiate a dummy recovery action. The class identifier is set,
	 * <code>actionOutcome</code> is initialized to <code>ACTION_SUCCESS</code>
	 * and <code>actionCanExecute</code> to <code>true</code>.
	 */
	DC_DummyRecoveryAction(void);

	/**
	 * Set the action's outcome.
	 * @see #doRecoveryAction
	 * @param nextOutcome the outcome of the action
	 */
	void setActionOutcome(TD_ActionOutcome nextOutcome);

	/**
	 * Set the status of the execution flag.
	 * @see #canExecute
	 * @param canExecute the value returned by <code>canExecute()</code>
	 */
	void setExecutionFlag(bool canExecute);
};
#endif
