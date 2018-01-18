//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyConfigurableFsmState.h
//
// Version	1.1
// Date		12.10.02 (Version 1.0)
//          25.o2.03 (Version 1.1)
// Author	A. Pasetti (P&P Software)
//
// Change Record:
//   Version 1.1: fixed errors in CcDoc references

#ifndef DC_DummyConfigurableFsmStateH
#define DC_DummyConfigurableFsmStateH

#include "FsmState.h"

/**
 * Dummy configurable FsmState useful for testing purposes. It represents an
 * FsmState with simple actions and configurable check results.
 * The actions
 * associated to the FsmState consist in the incrementation of three counters:
 * the <i>activation counter</i>, <i>initialization counter</i> and the
 * <i>termination counter</i>.
 * The checks associated to the FsmState are implemented
 * to return user-defined values.
 * @see CC_FSM
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.1
 */
class DC_DummyConfigurableFsmState : public FsmState {

  private:
   unsigned int activationCounter;
   unsigned int initializationCounter;
   unsigned int exitCounter;
   bool initializationCheck;
   bool exitCheck;
   bool terminationCheck;

  public:

    /**
     * Instantiate a dummy FsmState object, initialize all the action counters
     * to zero, the initialization and exit check to true, and the termination
     * check to false.
     */
    DC_DummyConfigurableFsmState(void);

    /**
     * Implement dummy continued action: the method increments the activation
     * counter by 1 returns.
     * <p>
     * @see FsmState#doContinue
     */
    virtual void doContinue(void);

    /**
     * Return the value set by the user with the last call to
     * <code>setInitializationCheckValue</code>
     * <p>
     * @see CC_FSM#activate
     * @see setInitializationCheckValue
     * @return true if the continued action associated to this state has been
     * terminated, false otherwise
     */
    virtual bool canEnter(void);

    /**
     * Implement dummy initialization action: the method increments the
     * initialization counter by 1 returns.
     * <p>
     * @see FsmState#doInit
     */
    virtual void doInit(void);

    /**
     * Return the value set by the user with the last call to
     * <code>setExitCheckValue</code>
     * <p>
     * @see CC_FSM#activate
     * @see #setExitCheckValue
     * @return true if the continued action associated to this state has been
     * terminated, false otherwise
     */
    virtual bool canExit(void);

    /**
     * Implement dummy exit action: the method increments the exit
     * counter by 1 returns.
     * <p>
     * @see FsmState#doExit
     */
    virtual void doExit(void);

    /**
     * Return the value set by the user with the last call to
     * <code>setTerminationCheckValue</code>
     * <p>
     * @see CC_FSM#activate
     * @see #setTerminationCheckValue
     * @return true if the continued action associated to this state has been
     * terminated, false otherwise
     */
    virtual bool isFinished(void);

    /**
     * Return the value of the activation counter.
     * @return the value of the activation counter
     */
    unsigned int getActivationCounter(void);

    /**
     * Return the value of the initialization counter.
     * @return the value of the initialization counter
     */
    unsigned int getInitializationCounter(void);

    /**
     * Return the value of the exit counter.
     * @return the value of the exit counter
     */
    unsigned int getExitCounter(void);

    /**
     * Set the return value of the initialization check.
     * @return the value that shall be returned by the next call to the
     * initialization check
     */
    void setInitializationCheckValue(bool value);

    /**
     * Set the return value of the exit check.
     * @return the value that shall be returned by the next call to the
     * exit check
     */
    void setExitCheckValue(bool value);

    /**
     * Set the return value of the termination check.
     * @return the value that shall be returned by the next call to the
     * termination check
     */
    void setTerminationCheckValue(bool value);

};

#endif
