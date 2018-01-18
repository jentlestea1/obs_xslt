//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyConditionalPunctualAction.h
//
// Version	1.0
// Date		04.06.03
// Author	R. Totaro

#ifndef DC_DummyConditionalPunctualActionH
#define DC_DummyConditionalPunctualActionH

#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "ConditionalPunctualAction.h"

/**
 * Dummy conditional punctual action that does not perform any action
 * and always returns "action successful".
 * A setter method allows the return value of the execution check to
 * be set by the user.
 * This punctual action is used for testing purposes.
 * @author Roberto Totaro
 * @version 1.0
 */
class DC_DummyConditionalPunctualAction : public ConditionalPunctualAction {

  private:
	bool executionFlag;

  public:

	/**
	* Instantiate a dummy conditional punctual action.
	*/
	DC_DummyConditionalPunctualAction(void);

	/**
	 * Set the return value of <code>canExecute</code>. This method
	 * was implemented only for testing purposes.
	 * @see ConditionalPunctualAction#canExecute
	 * @param newState the new value of <code>executionFlag</code>
	 */
	void setExecutionFlag(bool newState);

  protected:

	/**
	 * Perform a dummy execution test. The result of the test can
	 * be forced by calling <code>setExecutionFlag</code>.
	 * @see ConditionalPunctualAction#setExecutionFlag
	 * @see ConditionalPunctualAction#doAction
	 * @see PunctualAction#execute
	 * @return returns the value of <code>executionFlag</code>
	 */
	virtual bool canExecute(void);

	/**
	 * This method does not do anything.
	 * @see ConditionalPunctualAction#doAction
	 * @see PunctualAction#execute
	 * @return always returns an <code>ACTION_SUCCESS</code> code
	 */
	virtual TD_ActionOutcome doConditionalAction(void);
};
#endif
