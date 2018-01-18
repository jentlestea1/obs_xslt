//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_FdirCheck.h
//
// Version	1.0
// Date		11.06.03 (version 1.0)
// Author	A. Pasetti (P&P Software)

#ifndef DC_FdirCheckH
#define DC_FdirCheckH

#include "../GeneralInclude/BasicTypes.h"
#include "../Base/PunctualAction.h"
#include "../FDIR/RecoveryAction.h"

/**
 * Encapsulation of a failure detection and isolation check and of its
 * associated recovery action. A FDIR (fault detection, isolation
 * and recovery) check usually consists of two parts. A check that
 * determines the existence of a fault and isolates its cause (the
 * <i>failure detection and isolation check</i> or FDI check), and a
 * a <i>recovery action</i> to counteract the fault. This component
 * encapsulates a complete FDIR check and allows both the
 * FDI check and the recovery action to be executed
 * as a single action.
 * <p>
 * This component assumes that the FDI check check is encapsulated
 * in a component of type <code>PunctualAction</code>.
 * and that the recovery action is encapsulated in a component of type
 * <code>RecoveryAction</code>.
 * <p>
 * This component is offered as a form of <i>punctual action</i> (it
 * is derived from the base class <code>PunctualAction</code>). Its
 * associated action consists in the execution of the FDI check
 * and, if this returns with a failure code, in
 * the subsequent and immediate execution of the associated recovery
 * action. Note that there is no conditional execution check associated to an
 * FDIR check: the FDI check is always executed when the <code>FdirCheck</code>
 * component is executed. If it is desired to have the FDIR check executed only
 * if certain conditions hold, the conditional execution check can be built
 * into the FDI check (this is typically done by implementing the FDI check
 * as a subclass of <code>ConditionalPunctualAction</code>).
 * @todo change the name of this class to: DC_FdirAction (remember to update
 * the comments to reflect the change of class name)
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup FDIR
 */
class DC_FdirCheck : public PunctualAction {
private:
	RecoveryAction* pRecoveryAction;
    PunctualAction* pFdiCheck;

protected:
    /**
     * Execute the FDI check and, if this returns a failure code, execute
     * the recovery action.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *   outcome = pFdiCheck->execute();
     *   if ( outcome == ACTION_FAILURE )
     *      outcome = pRecoveryAction->execute();
     *   return outcome; </PRE>
     * Note that the outcome code returned by this punctual action is either
     * the return code of the FDI check or of the recovery action, whichever
     * is executed last.
     * @see TD_ActionOutcome
     * @return the outcome code of the last recovery action to be executed
     * or ACTION_CANNOT_EXECUTE if no action can be executed
     */
    virtual TD_ActionOutcome doAction(void);

public:
    /**
     * Instantiate an FDIR check. The recovery action and FDI check are
     * left undefined to signify that the component is not yet configured.
     */
    DC_FdirCheck(void);

    /**
     * Set the FDI check.
     * @see #doAction
     * @param pFdiCheck the FDI check component
     */
    void setFdiCheck(PunctualAction* pFdiCheck);

    /**
     * Get the FDI check.
     * @see #doAction
     * @return the FDI check component
     */
    PunctualAction* getFdiCheck(void);

    /**
     * Set the recovery action.
     * @see #doAction
     * @param pRecoveryAction the recovery action
     */
    void setRecoveryAction(RecoveryAction* pRecoveryAction);

    /**
     * Get the recovery action.
     * @see #doAction
     * @return the recovery action
     */
    RecoveryAction* getRecoveryAction(void);

    /**
     * Perform a class-specific configuration check on the FDIR check:
	 * verify that the recovery action and FDI check have been set.
     * @return true if the FDIR check is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);
};
#endif
