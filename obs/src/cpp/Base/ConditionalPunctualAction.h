//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// ConditionalPunctualAction.h
//
// Version	1.0
// Date		17.05.03 (version 1.0)
// Author	A. Pasetti (P&P Software)

#ifndef ConditionalPunctualActionH
#define ConditionalPunctualActionH

#include "../GeneralInclude/BasicTypes.h"
#include "../Base/PunctualAction.h"

/**
 * Punctual action that performs an <i>execution check</i>.
 * An execution check is a check that is performed just before the
 * action associated to the punctual action component are executed.
 * An execution check can have two outcomes: "action can be executed" or
 * "action cannot be executed".
 * This type of punctual action is useful to model punctual actions
 * which should be executed only if certain conditions are met.
 * The execution check can be implemented to verify whether these
 * conditions are met.
 * <p>
 * This is an abstract class because it leaves open the definition of the
 * actions to be performed by the punctual action component and the
 * definition of the concrete execution check.
 * This class only implements the management of the abstract execution
 * check.
 * @todo Add a getExecutionCheckCode to return a code describing the reason for
 * the failure of the execution check.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup Base
 */
class ConditionalPunctualAction : public PunctualAction {

  public:

    /**
     * Instantiate a punctual action. This method returns without taking
     * any action.
     */
    ConditionalPunctualAction(void);

  protected:

    /**
     * Execute the punctual action if the execution check is satisifed.
     * Otherwise, do nothing.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *   if ( canExecute() )
     *      return doConditionalAction();
     *   else
     *      return ACTION_CANNOT_EXECUTE; </PRE>
     * The <CODE>doConditionalAction()</CODE> and <code>canExecute()</code>
     * methods are abstract and encapsulate the
     * implementation of the actions associated to
     * the punctual action, and the implementation of the execution check
     * respectively.
     * Thus, this class enforces the execution check but leaves its definition
     * and the definition of the concrete actions associated to the punctual
     * action component open.
     * @see TD_ActionOutcome
     * @return the outcome code of the punctual action
     */
    virtual TD_ActionOutcome doAction(void);

    /**
     * Encapsulate implementation of the <i>execution check</i>.
     * This method is called by method <CODE>doAction()</CODE> in this same
     * class.
     * @see #doAction
     * @return true if the action can be executed, false if the action cannot
     * be executed.
     */
    virtual bool canExecute(void) = 0;

    /**
     * Encapsulate implementation of the actions associated to the
     * punctual action component.
     * This method is called by method <CODE>doAction()</CODE> in this same
     * class.
     * Note that users of punctual actions do not see method <CODE>doAction()</CODE>,
     * they only see method <CODE>execute()</CODE> defined by the superclass.
     * @see #doAction
     * @return the outcome code of the punctual action
     */
    virtual TD_ActionOutcome doConditionalAction(void) = 0;
};

#endif
