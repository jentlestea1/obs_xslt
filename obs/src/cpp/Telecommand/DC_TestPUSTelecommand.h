//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_TestPUSTelecommand.h
//
// Version	1.0
// Date		05.01.04
// Author	A. Pasetti (P&P Software)

#ifndef DC_TestPUSTelecommandH
#define DC_TestPUSTelecommandH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTelecommand.h"

/**
 * Telecommand that can be used as part of an end-to-end PUS test scenario to 
 * simulate a PUS telecommand.
 * This telecommand consists of an <i>execution counter</i> that is incremented 
 * by one every time the telecommand is executed. 
 * The telecommand additionally offers methods to change the return value of its
 * execution check and of its validity check and to set the values of
 * validity and execution check codes. These are useful to 
 * simulate telecommands whose
 * execution check returns "telecommand cannot executed" or whose
 * validity check returns "telecommand not valid". 
 * Similarly, it is possible to set the return value of the execution method to
 * either ACTION_SUCCESS or ACTION_FAILURE.
 * <p>
 * The initial values of the execution counter, of the
 * validity and execution check return values, of the execution return value, 
 * and of the validity and
 * execution check codes are defined in the telecommand application data that
 * are loaded when the telecommand is configured through the <i>raw data load service</i>.
 * <p>
 * The type and subtype of the telecommand are set to PUS_TYPE_TEST and
 * PUS_ST_TC_TEST, respectively.
 * <p>
 * The application data associated to this telecommand are assumed to consist
 * of 6 bytes which are interpreted as follows:<ul>
 * <li>Byte 0: the initial value of the execution counter</li>
 * <li>Byte 1: the initial value of the execution check value</li>
 * <li>Byte 2: the initial value of the validity check value</li>
 * <li>Byte 3: the initial value of the execution check code</li>
 * <li>Byte 4: the initial value of the validity check code</li>
 * <li>Byte 5: the value of the execution outcome return value (ACTION_FAILURE if 1,
 * ACTION_SUCCESS otherwise)</li>
 * </ul>
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_TestPUSTelecommand : public PUSTelecommand {

  private:
    unsigned char executionCounter; 
    bool executionCheckValue;
    bool validityCheckValue;
    bool executionSuccess;
    TD_CheckCode executionCheckCode;
    TD_CheckCode validityCheckCode;
    unsigned int lasti;


  protected:

    /**
     * Increment the execution counter by one and return the execution outcome code 
     * set in the application data.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *      if (exectionCounter<255)
     *          executionCounter++;
     *      else
     *          executionCounter=0;
     *      if (executionSuccess)
     *          return ACTION_SUCCESS;
     *      else
     *          return ACTION_FAILURE;</PRE>
     * The vlaue of the internal flag <code>executionSuccess</code> is read from
     * the telecommand application data. 
     * @see PunctualAction#execute
     * @return the execution outcome code (either ACTION_SUCCESS or ACTION_FAILURE
     * depending on the value byte 6 of the application data)
     */
    virtual TD_ActionOutcome doAction(void);

  public:

    /**
     * Instantiate a test telecommand.
     * The class identifier is set. The telecommand type and subtype are set
     * the values indicated in the class comment. All other internal variables 
     * are set to dummy values. 
     */
    DC_TestPUSTelecommand(void);

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
     * when the telecommand application data are loaded. Its value
     * can additionally be changed with method <code>setExecutionCheckValue</code>
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
     * when the telecommand application data are loaded. Its value
     * can be changed with method <code>setValidityCheckValue</code>
     * @see #setValidityCheckValue
     * @see CC_TelecommandManager#load
     * @return the value of the internal variable <code>setExecutionCheckValue</code>
     */
    virtual bool isValid(void);

    /**
     * Return the validity check code for the telecommand.
     * This implementation returns a user-defined value that is initialized
     * when the telecommand application data are loaded and that can be 
     * set with method
     * <code>setValidityCheckCode</code>.
     * @see #setValidityCheckCode
     * @return the validity check code
     */
    virtual TD_CheckCode getValidityCheckCode(void) const;

    /**
     * Return the execution check code for the telecommand.
     * This implementation returns a user-defined value that is initialized
     * when the telecommand application data are loaded and that can be set with method
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

    /**
     * Set the action outcome returned by method <code>doAction</code>.
     * The possible values are foreseen ACTION_SUCCESS or ACTION_FAILURE.
     * The former is used if the value set with this method is true. Otherwise
     * the latter is used.
     * @see #doAction
     * @param executionSuccess if true, then the action outcome is forced to
     * ACTION_SUCCESS, otherwise  it is forced to ACTION_FAILURE
     */
    void setActionOutcome(bool executionSuccess);

    /**
     * Get the action outcome returned by method <code>doAction</code>.
     * If the return value is true, then action outcome is ACTION_SUCCESS.
     * Otherwise it ACTION_FAILURE.
     * @see #setActionOutcome
     * @return a flag indicating which value of action outcome is returned by
     * method <code>doAction</code>
     */
    bool getActionOutcome();

    /**
     * Implementation of the raw data load service. This method would normally
     * be called by a telecommand loader to load the application data into the
     * the telecommand component. This method interprets the raw data as they are
     * loaded and uses them to initialize the internal variables of the telecommand
     * component. The expected layout of the application data is specified
     * in the class comment. 
     * @see #getNumberOfRawData
     * @param i the index of the raw telecommand data
     * @param d the raw data
     */
    virtual void setRawData(unsigned int i, unsigned char d);

    /**
     * Return the number of raw data bytes that can be loaded with the
     * raw telecommand data load service.
     * Since the size of the application data for this telecommand is fixed and equal
     * to six,
     * this method always returns the value of six.
     * @see #setRawData
     * @return alwys returns the value 6
     */
    virtual unsigned int getNumberOfRawData(void) const;

};

#endif 
