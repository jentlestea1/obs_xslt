//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// CC_PunctualActionManager.h
//
// Version	1.0
// Date		18.09.03
// Author	A. Pasetti (P&P Software)

#ifndef CC_PunctualActionManagerH
#define CC_PunctualActionManagerH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "PunctualActionModeManager.h"

/**
 * This class encapsulates a punctual action manager.
 * The punctual action manager is responsible for controlling the execution
 * of a list of punctual actions.
 * The punctual actions are encapsulated in instances of <code>PunctualAction</code>
 * components.
 * The punctual actions to be executed are provided by a <i>punctual action
 * mode manager</i> that is loaded as a plug-in component in the punctual
 * action manager.
 * <p>
 * When the punctual action manager is activated, it asks its mode manager
 * for the list of punctual actions to be executed and executes them in
 * sequence.
 * <p>
 * @see PunctualAction
 * @see PunctualActionModeManager
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup FunctionalityManagers
 */
class CC_PunctualActionManager : public CC_RootObject {
private:
    PunctualActionModeManager *pModeManager;

public:
    /**
     * Instantiate a punctual action manager.
     * The class identifier is set.
     */
    CC_PunctualActionManager(void);

    /**
     * Load the punctual action mode manager.
     * @param pModeManager the telemetry mode manager
     */
    void setPunctualActionModeManager(PunctualActionModeManager *pModeManager);

    /**
     * Get the punctual action mode manager.
     * @return the punctual action mode manager
     */
    PunctualActionModeManager *getPunctualActionModeManager(void) const;

    /**
     * Execute the punctual actions supplied by the mode manager.
     * A pseudocode implementation for this method is as follows: <PRE>
     *      for (all pItem items provided by the puntual action mode manager)
     *          pItem->execute(); </PRE>
     * Note that the outcome of the punctual action (i.e. the return
     * value of the <code>execute</code> method) is disregarded.
     */
    void activate(void);

    /**
     * Perform a class-specific configuration check on the punctual action
     * manager: verify that the punctual action mode manager
     * has been loaded.
     * @return true if the punctual action manager is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);
};

#endif
