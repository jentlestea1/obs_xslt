//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyTelecommand.h
//
// Version	1.0
// Date		05.12.02
// Author	A. Pasetti (P&P Software)

#ifndef DC_DummyTelecommandH
#define DC_DummyTelecommandH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "Telecommand.h"

/**
 * Dummy telecommand that increments a counter every time it is 
 * executed. This telecommand is useful for testing purposes.
 * The telecommand maintains an <i>execution counter</i> that is initialized 
 * to zero when the telecommand object is first instantiated and is 
 * incremented by one every time the telecommand receives an <code>execute</code>
 * request. There is no way to reset the execution counter.
 * <p>
 * The telecommand offer methods to change the return value of its
 * execution check and of its validity check and to set the values of
 * validity and execution check codes. These are useful to 
 * simulate telecommands whose
 * execution check returns "telecommand cannot executed" or whose
 * validity check returns "telecommand not valid".
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_DummyTelecommand : public Telecommand {

  private:
    unsigned int executionCounter; 
    bool executionCheckValue;
    bool validityCheckValue;
    TD_CheckCode executionCheckCode;
    TD_CheckCode validityCheckCode;

  protected:

    /**
     * Increment the execution counter by one and return a code of "action successful".
     * Note that there is no protection against
     * an overflow in the value of the execution counter.
     * @see PunctualAction#execute
     * @return always returns a "telecommand successfully executed" code
     */
    virtual TD_ActionOutcome doAction(void);

  public:

    /**
     * Instantiate a dummy telecommand.
     * The execution counter is set to zero.
     * The telecommand is configured to have an execution check that returns:
     * "telecommand can be executed" and a validity check that returns:
     * "telecommand is valid". The validity and execution check codes are
     * initialized to zero.
     */
    DC_DummyTelecommand(void);

    /**
     * Getter method for the execution counter.
     * @return the execution counter
     */
    unsigned int getExecutionCounter(void);

    /**
     * Execute the execution check on the telecommand.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *      return executionCheckValue; </PRE>
     * The internal variable <code>executionCheckValue</code> is initialized
     * to <code>TC_CANNOT_EXECUTE</code> by the constructor but its value
     * can be changed with method <code>setExecutionCheckValue</code>
     * @see #setExecutionCheckValue
     * @see CC_TelecommandManager#activate
     * @return the value of the internal variable <code>setExecutionCheckValue</code>
     */
    virtual bool canExecute(void);

    /**
     * Execute the validity check on the telecommand.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *      return validityCheckValue; </PRE>
     * The internal variable <code>validityCheckValue</code> is initialized
     * to <code>VALID</code> by the constructor but its value
     * can be changed with method <code>setValidityCheckValue</code>
     * @see #setValidityCheckValue
     * @see CC_TelecommandManager#load
     * @return the value of the internal variable <code>setExecutionCheckValue</code>
     */
    virtual bool isValid(void);

    /**
     * Return the validity check code for the telecommand.
     * This implementation returns a user-defined value that is set with method
     * <code>setValidityCheckCode</code>.
     * @see #setValidityCheckCode
     * @return the validity check code
     */
    virtual TD_CheckCode getValidityCheckCode(void) const;

    /**
     * Return the execution check code for the telecommand.
     * This implementation returns a user-defined value that is set with method
     * <code>setExecutionCheckCode</code>.
     * @see #setExecutionCheckCode
     * @return the validity check code
     */
    virtual TD_CheckCode getExecutionCheckCode(void) const;

    /**
     * Set the return value of the execution check.
     * This is a setter method for the internal variable <code>executionCheckValue</code>
     * which defines the return value of the execution check implemented by this
     * telecommand.
     * @see #canExecute
     * @param executionCheckValue the value of the internal variable <code>setExecutionCheckValue</code>
     */
    void setExecutionCheckValue(bool executionCheckValue);

    /**
     * Set the return value of the validity check.
     * This is a setter method for the internal variable <code>validityCheckValue</code>
     * which defines the return value of the validity check implemented by this
     * telecommand.
     * @see #isValid
     * @param validityCheckValue the value of the internal variable <code>setExecutionCheckValue</code>
     */
    void setValidityCheckValue(bool validityCheckValue);

    /**
     * Set the value of the validity check code.
     * This is a setter method for an internal variable 
     * which defines the return value of method <code>getValidityCheckCode</code>.
     * @see #getValidityCheckCode
     * @param validityCheckCode the value of the validity check code
     */
    void setValidityCheckCode(TD_CheckCode validityCheckCode);

    /**
     * Set the value of the execution check code.
     * This is a setter method for an internal variable 
     * which defines the return value of method <code>getExecutionCheckCode</code>.
     * @see #getExecutionCheckCode
     * @param executionCheckCode the value of the validity check code
     */
    void setExecutionCheckCode(TD_CheckCode executionCheckCode);
};

#endif 
