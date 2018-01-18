//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_CyclingPunctualActionModeManager.h
//
// Version	1.0
// Date		23.01.04
// Author	A. Pasetti (P&P Software)

#ifndef DC_CyclingPunctualActionModeManagerH
#define DC_CyclingPunctualActionModeManagerH

#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "PunctualActionListModeManager.h"

/**
 * Punctual action mode manager that cycles through the lists of punctual actions.
 * This class extends the base class <code>PunctualActionListModeManager</code> 
 * by adding to it an implementation for the <i>update mechanism</i> that
 * cycles through all the operational modes defined for the mode manager.
 * </p>
 * An initialization sequence for this class consists of the following
 * steps (to be performed in the order given): <ul>
 * <li>Set the number of modes through method <code>setNumberOfModes</code></li>
 * <li>Set the default mode <code>setDefaultMode</code></li>
 * <li>Set the lengths of the lists through method
 * <code>setListLength</code></li>
 * <li>Load the individual items through method <code>setListItem</code></li>
 * <li>Reset the component by calling method <code>reset</code></li>
 * </ul>
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_CyclingPunctualActionModeManager : public PunctualActionListModeManager {

  public:

    /**
     * Instantiate a cycling punctual action mode manager. This constructor sets the
     * class identifier and then returns.
     */
    DC_CyclingPunctualActionModeManager(void);

    /**
     * Cycle through the operational modes. Let N be the number of modes
     * and C be the current mode. If C is smaller than (N-1), then this
     * method updates the operationa mode to: (C+1). Otherwise it updates it
	 * to 0.
     * @see ModeManager#update
     */
    virtual void update(void);

};

#endif
