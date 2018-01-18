//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_SimplePunctualActionModeManager.h
//
// Version	1.0
// Date		18.09.03
// Author	A. Pasetti (P&P Software)

#ifndef DC_SimplePunctualActionModeManagerH
#define DC_SimplePunctualActionModeManagerH

#include "PunctualActionListModeManager.h"

/**
 * Punctual action mode manager with a single and fixed mode.
 * This mode manager has a trivial implementation of the update
 * service that returns without taking any action. It should be 
 * used when the punctual action manager operates upon a fixed
 * list of punctual actions.
 * <p>
 * An initialization sequence for this class consists of the following
 * steps (to be performed in the order given here): <ul>
 * <li>Set the length of the single punctual action list through method
 * <code>setListLength</code></li>
 * <li>Load the individual punctual actions items through successive
 * calles to method <code>setListPunctualAction</code></li>
 * <li>Reset the component by calling method <code>reset</code></li>
 * </ul>
 * @see PunctualAction
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_SimplePunctualActionModeManager : public PunctualActionListModeManager {
public:
    /**
     * Instantiate a punctual action mode manager. This constructor sets the
     * class identifier and it configures its superclass to manage only
     * one single mode. A pseudo-code implementation is as follows: <PRE>
     *      setClassId(ID_SIMPLEPUNCTUALACTIONMODEMANAGER);
     *      setNumberOfModes(1);
     *      setDefaultMode(0);  </PRE>
     */
    DC_SimplePunctualActionModeManager(void);

    /**
     * Since this is a fixed-mode mode manager, this method returns without
     * taking any action.
     */
    virtual void update(void);
};

#endif
