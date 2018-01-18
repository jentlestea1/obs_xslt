//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyPUSTelecommand.h
//
// Version	1.0
// Date		05.12.02
// Author	A. Pasetti (P&P Software)

#ifndef DC_DummyPUSTelecommandH
#define DC_DummyPUSTelecommandH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTelecommand.h"

/**
 * Dummy PUS telecommand that increments a counter every time it is 
 * executed. This telecommand is useful for testing purposes.
 * The values of the telecommand packet attributes are initialized 
 * to: <ul>
 * <li>The telecommand identifier is set to TEST_TC_ID</li>
 * <li>The telecommand type is set to TEST_TC_TYPE</li>
 * <li>The telecommand subtype is set to TEST_TC_SUBTYPE</li>
 * <li>The telecommand source is set to TEST_TC_SOURCE</li>
 * <li>The telecommand acknowledge level is set to indicate "no acknoledge is required"</li>
 * </ul>
 * The constants are defined in file <code>TestConstants.h</code>.
 * Note that the APID of the process
 * receiving the telecommands does not need to be set because it is
 * a static field that should be set during the test set up process.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_DummyPUSTelecommand : public PUSTelecommand {

  private:
    unsigned int executionCounter; 

  protected:

    /**
     * Increment the execution counter by one and return a code of "action successful".
     * @see PunctualAction#execute
     * @return always returns a "telecommand successfully executed" code
     */
    virtual TD_ActionOutcome doAction(void);

  public:

    /**
     * Instantiate a dummy PUS telecommand.
     * The execution counter is set to zero. The class identifier is set.
     * The values of the telecommand packet attributes are initialized 
     * as described in the class comment.
     */
    DC_DummyPUSTelecommand(void);

    /**
     * Getter method for the execution counter.
     * @return the execution counter
     */
    unsigned int getExecutionCounter(void);
 };

#endif 
