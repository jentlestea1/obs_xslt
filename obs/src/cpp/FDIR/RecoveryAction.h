//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// RecoveryAction.h
//
// Version	1.0
// Date		11.06.03 (version 1.0)
// Author	A. Pasetti (P&P Software)

#ifndef RecoveryActionH
#define RecoveryActionH

#include "../GeneralInclude/BasicTypes.h"
#include "../Base/ConditionalPunctualAction.h"

/**
 * Punctual action that performs a <i>recovery action</i>.
 * A recovery action is an action that is executed in response to the
 * detection of a failure. Recovery actions are implemented as a
 * form of <i>punctual action</i>. They add to their base class
 * the <i>next recovery action</i> attribute and the <i>execution
 * check</i>.
 * <p>
 * Recovery actions can be linked in sequential
 * chains. The client only sees one single recovery action (the one
 * at the head of the chain) but its execution can lead to all actions
 * in the chain being executed in sequence. The <i>next recovery action</i>
 * attribute holds the pointer to the next recovery action in the
 * chain.
 * <p>
 * The execution check is performed before executing the recovery
 * action. Its implementation is left open and concrete subclasses
 * can use it to define the conditions under which the execution of
 * the recovery action is allowed.
 * <p>
 * This is an abstract class because it leaves open the definition of
 * actual actions to be performed by the recovery action component
 * and the definition of the execution check open.
 * This class only implements the management of the next recovery
 * action.
 * <p>
 * Punctual actions return an <i>outcome</i>. The outcome of a
 * recovery action R is the outcome of the last recovery action in
 * the chain of recovery actions that has R as its first item.
 * <p>
 * <i>Implementation Note:</i> This could in principle be implemented
 * as a subclass of <code>ConditionalPunctualAction</code>. This is
 * not done because class a failure of the execution check in
 * class <code>ConditionalPunctualAction</code> simply leads
 * to an immediate termination of the punctual action. In the case
 * of the <code>RecoveryAction</code> class, instead, a failure
 * of the execution check leads to an attempt to execute the next
 * recovery action.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup FDIR
 */
class RecoveryAction : public PunctualAction {
private:
	RecoveryAction* pNextRecoveryAction;

public:

	/**
	 * Instantiate a recovery action. The <i>next recovery action</i> is
	 * set to null.
	 */
	RecoveryAction(void);

	/**
	 * Set the next recovery action.
	 * @see #doAction
	 * @param pNextRecoveryAction the next recovery action
	 */
	void setNextRecoveryAction(RecoveryAction* pNextRecoveryAction);

	/**
	 * Get the next recovery action. If no recovery action has been chained
     * to this one, then a value of pNULL is returned.
	 * @see #doAction
	 * @return the next recovery action
	 */
	RecoveryAction* getNextRecoveryAction(void);

protected:

	/**
	 * Execute the recovery action if the execution check is satisfied
	 * and pass on the execute request to the next recovery action
	 * (if one is defined).
	 * A pseudo-code implementation for this method is as follows: <PRE>
	 *   outcome = ACTION_CANNOT_EXECUTE;
	 *   if ( canExecute() )
	 *      outcome = doRecoveryAction()
	 *   if ( nextRecoveryAction != pNULL)
	 *      outcome = nextRecoveryAction->execute();
	 *   return outcome; </PRE>
	 * The <CODE>doRecoveryAction()</CODE> method is abstract and encapsulates
	 * the implementation of the actions associated to this recovery action.
	 * Thus, this class enforces the handing over of execution requests
	 * from one recovery action
	 * to the next but it leaves the definition of the
	 * specific recovery actions to concrete subclasses.
	 * @see #setNextRecoveryAction
	 * @see TD_ActionOutcome
	 * @return the outcome code of the last recovery action to be executed
	 * or ACTION_CANNOT_EXECUTE if no action can be executed
	 */
	virtual TD_ActionOutcome doAction(void);

	/**
	 * Encapsulate implementation of the <i>execution check</i>.
	 * This method is called by method <CODE>doAction()</CODE> in this same
	 * class. This class provides a default implementation that always
	 * returns "can execute".
	 * @see #doAction
	 * @return true if the action can be executed, false if the action cannot
	 * be executed.
	 */
	virtual bool canExecute(void);

	/**
	 * Encapsulate implementation of the concrete recovery actions associated
	 * to this component.
	 * This method is called by method <CODE>doAction()</CODE> in this same
	 * class.
	 * @see #doAction
	 * @return the outcome code of the punctual action
	 */
	virtual TD_ActionOutcome doRecoveryAction(void) = 0;
};
#endif
