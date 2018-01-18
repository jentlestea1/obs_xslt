//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyModeManager.h
//
// Version	1.0
// Date		23.02.03
// Author	A. Pasetti (P&P Software)

#ifndef DC_DummyModeManagerH
#define DC_DummyModeManagerH

#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "ModeManager.h"

/**
 * Dummy mode manager to be used for testing purposes.
 * This mode manager does not define any strategies.
 * Its implementation of the update service consists in cycling through
 * all possible operational modes.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_DummyModeManager : public ModeManager {

  public:

    /**
     * Instantiate a dummy mode manager. This constructor sets the
     * class identifier and then returns.
     */
    DC_DummyModeManager(void);

    /**
     * Cycle through the operational mode. Let N be the number of modes
     * and C be the current mode. If C is smaller than (N-1), then this
     * method returns C+1. Otherwise it returns 0.
     * @see ModeManager#Update
     * @return returns the update operational mode
     */
    virtual void update(void);

  protected:

    /**
     * This method returns without taking any action. No action is
     * required because this implementation of a mode manager does not
     * use any internal data structures.
     */
    virtual void allocateMemory(TD_Mode numberOfModes);
};

#endif
