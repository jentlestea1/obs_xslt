//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_TestPUSConfigurableManoeuvre.h
//
// Version	1.0
// Date		11.02.04
// Author	A. Pasetti (P&P Software)

#ifndef DC_TestPUSConfigurableManoeuvreH
#define DC_TestPUSConfigurableManoeuvreH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTcManoeuvre.h"

/**
 * Test implementation of the <code>PUSManoeuvre</code> abstract class
 * to be used for testing purposes. This class implements some simple
 * forms of manoeuvre actions and it allows the return values of the
 * manoeuvre checks to be configured by the user.
 * <p>
 * This class associates three counters to each of the three actions
 * (<i>initialization action</i>, <i>continuation action</i>, and
 * <i>termination action</i>) that characterize a manoeuvre.
 * The counters are initialized to zero
 * by the constructor and are incremented by one every time the
 * action is executed. Execution of the continuation action also causes
 * the <i>progress event generation service</i> to be called.
 * The return value of the three checks (<i>start check</i>,
 * <i>continuation check</i>, and <i>termination check</i>) associated
 * to the manoeuvres can be set be the user. The value of the continuation
 * check code can also be set by the user.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_TestPUSConfigurableManoeuvre: public PUSTcManoeuvre {

private:
    int initializationActionCounter;
    int continuationActionCounter;
    int terminationActionCounter;
    bool startCheck;
    bool continuationCheck;
    bool terminationCheck;
    TD_CheckCode continuationCheckCode;

protected:

  /**
  * Increment the continuation action counter by one and call the 
  * <i>progress event generation service</i>. A pseudo-code implementation
  * of this method is as follows:<pre>
  *     continuationActionCounter++;
  *     generateProgressEvent();</pre>
  * @see PUSManoeuvre#generateProgressEvent
  * @see Manoeuvre#doContinue
  */
  virtual void doInternalContinue(void);

  /**
  * Increment the termination action counter by one.
  * @see Manoeuvre#terminate
  */
  virtual void internalTerminate(void);

public:

  /**
  * Instantiate a test PUS configurable manoeuvre object.
  * The counters are initialized to zero; the return values of the start,
  * continuation and termination check are initialized to false; and the class
  * identified is set.
  */
  DC_TestPUSConfigurableManoeuvre(void);

  /**
  * Return the value of the start check flag.
  * The value of the start check flag can be set by the user through method
  * <code>setCheckStatus</code>.
  * @see #setCheckStatus
  * @return true if the manoeuvre is ready to start
  */
  virtual bool canStart(void);

  /**
  * Increment the initialization action counter by one.
  */
  virtual void initialize(void);

  /**
  * Return the value of the continuation check flag.
  * The value of the continuation check flag can be set by the user through method
  * <code>setCheckStatus</code>.
  * @see #setCheckStatus
  * @return true if the manoeuvre can continue execution
  */
  virtual bool canContinue(void);

  /**
  * Return the value of the termination check flag.
  * The value of the termination check flag can be set by the user through method
  * <code>setCheckStatus</code>.
  * @see #setCheckStatus
  * @return true if the manoeuvre has terminated execution
  */
  virtual bool isFinished(void);

  /**
  * Set the value of the start check.
  * The value set with this method is the value returned by the start check method.
  * @see #canStart
  * @param startCheck the return value of the start check
  */
  void setStartCheckStatus(bool startCheck);

  /**
  * Set the value of the continuation check.
  * The value set with this method is the value returned by the continuation check method.
  * @see #canContinue
  * @param continuationCheck the return value of the continuation check
  */
  void setContinuationCheckStatus(bool continuationCheck);

  /**
  * Set the value of the continuation check code.
  * The value set with this method is the value returned by method <code>getContinuationCheckCode</code>.
  * @see #canContinue
  * @param continuationCheckCode the return value of the continuation check
  */
  void setContinuationCheckCode(TD_CheckCode continuationCheckCode);

  /**
  * Get the value of the continuation check code.
  * In this class, the value of the continuation check code can be set by the user.
  * @see #setContinuationCheckCode
  * return the return value of the continuation check
  */
  virtual TD_CheckCode getContinuationCheckCode() const;

  /**
  * Set the value of the termination check.
  * The value set with this method is the value returned by the termination check methods.
  * @see #isFinished
  * @param terminationCheck the return value of the termination check
  */
  void setTerminationCheckStatus(bool terminationCheck);

  /**
  * Getter method for the initialization action counter.
  * @see #initialize
  * @return the initialization action counter
  */
  int getInitializationActionCounter(void);

  /**
  * Getter method for the continuation action counter.
  * @see #doInternalContinue
  * @return the continuation action counter
  */
  int getContinuationActionCounter(void);

  /**
  * Getter method for the termination action counter.
  * @see #internalTerminate
  * @return the termination action counter
  */
  int getTerminationActionCounter(void);

};

#endif

