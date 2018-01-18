//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyCriticalTelecommand.h
//
// Version	1.0
// Date		17.06.03
// Author	R. Totaro

#ifndef DC_DummyCriticalTelecommandH
#define DC_DummyCriticalTelecommandH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "CriticalTelecommand.h"

/**
 * Dummy telecommand that increments a counter every time it is 
 * executed. This telecommand is useful for testing purposes.
 * The telecommand maintains an <i>execution counter</i> that is initialized 
 * to zero when the telecommand object is first instantiated and is 
 * incremented by one every time the telecommand receives an <code>execute</code>
 * request. There is no way to reset the execution counter.
 * <p>
 * The telecommand offers a method to change the return value of its
 * execution check and of its validity check. These are useful to 
 * simulate telecommands whose
 * execution check returns "telecommand cannot executed" or whose
 * validity check returns "telecommand not valid".
 * @author Roberto Totaro
 * @version 1.0
 */
class DC_DummyCriticalTelecommand : public CriticalTelecommand {
private:
	unsigned int numberOfExecutions;
	bool         imageValid;

protected:
	/**
	 * Increments <code>numberOfExecutions</code> and returns a code
	 * of "action successful".
	 * @see #getNumberOfExecutions
	 * @see CriticalTelecommand#doAction
	 * @return always returns a "telecommand successfully executed" code
	 */
	virtual TD_ActionOutcome doCriticalAction(void);

public:
	/**
	 * Instantiate a dummy telecommand.
	 * The execution counter is set to zero.
	 * The telecommand is configured to have an execution check that returns:
	 * "telecommand can executed" and a validity check that returns:
	 * "telecommand is valid".
	 */
	DC_DummyCriticalTelecommand(void);

	/**
	 * Getter method for <code>numberOfExecutions</code>. Used only for
	 * testing purposes.
	 * @see #doCriticalAction
	 * @return the number of times doCriticalAction() has been called
	 */
	unsigned int getNumberOfExecutions(void);

	/**
	 * The base class default implementation is overridden in order
	 * to be able to thoroughly test <code>canExecute()</code>. This method
	 * returns the value of the <code>imageValid</code> member variable.
	 * @see CriticalTelecommand#canExecute
	 * @see #setImageValidity
	 * @return the value of imageValid
	 */
    virtual bool isImageValid(void);

	/**
	 * Setter method for <code>imageValid</code>. Used only for testing purposes.
	 * @see #isImageValid
	 * @param isValid new value of imageValid
	 */
	void setImageValidity(bool isValid);
};

#endif 
