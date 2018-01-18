//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyPunctualAction.h
//
// Version	1.1
// Date		01.10.02 (Version 1.0)
//          30.09.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: Added an activation counter and its getter method

#ifndef DC_DummyPunctualActionH
#define DC_DummyPunctualActionH

#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "PunctualAction.h"

/**
 * Dummy punctual action that does not perform any action and always
 * returns "action successful".
 * This punctual action may be useful for testing purposes.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.1
 */
class DC_DummyPunctualAction : public PunctualAction {
private:
    unsigned int counter;

public:
    /**
     * Instantiate a dummy punctual action.
     */
    DC_DummyPunctualAction(void);

    /**
     * Return the value of the activation counter.
     * @see #doAction
     * @return the value of the activation counter
     */
    unsigned int getActivationCounter(void) const;

protected:
    /**
     * This method increments the activation counter and returns a code
     * of "action successful".
     * @see PunctualAction#execute
     * @return always returns an "action successful" code
     */
    virtual TD_ActionOutcome doAction(void);
};

#endif
