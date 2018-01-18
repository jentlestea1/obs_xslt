//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_ControlAction.h
//
// Version	1.0
// Date		28.07.03 (version 1.0)
// Author	A. Pasetti (P&P Software)

#ifndef DC_ControlActionH
#define DC_ControlActionH

#include "../GeneralInclude/BasicTypes.h"
#include "../Base/ConditionalPunctualAction.h"
#include "../Data/ControlBlock.h"

/**
 * Encapsulation of the conditional propagation of a <i>control block</i>.
 * A control action has a settable attribute called <i>target control block</i>.
 * A control action is implemented
 * as a <i>conditional punctual action</i> whose
 * <i>execution action</i> consists in sending a propagation request to
 * the target control block. This class assumes that the target control block
 * is already fully configured.
 * <p>
 * Control actions offer a <i>reset service</i>. A call to the reset service
 * causes the target control block to be reset.
 * <p>
 * This class implements a default <i>execution check</i> that always returns
 * "can execute". This means that, if the control action is enabled, then its
 * execution will always result in the target control block receiving a propagation
 * request. Subclasses can of course implement different execution checks.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @ingroup Data
 * @version 1.0
 */
class DC_ControlAction : public ConditionalPunctualAction {

  private:
    ControlBlock* pTargetControlBlock;

  protected:

    /**
     * Encapsulate an <i>execution check</i> that always returns
     * "control action can execute".
     * @see ConditionalPunctualAction#doAction
     * @return always returns true.
     */
    virtual bool canExecute(void);

    /**
     * Send a propagate request to the target control block. This
     * method always returns: "ACTION_SUCCESS"
     * @see ConditionalPunctualAction#doAction
     * @return the outcome code of the punctual action
     */
    virtual TD_ActionOutcome doConditionalAction(void);

  public:

    /**
     * Instantiate a control action. This method sets the class identifier and
     * initializes the target control block to an illegal value to signify
     * that the component is not yet configured.
     */
    DC_ControlAction(void);

    /**
     * Load the target control block.
     * @param pBlock the target control block to be loaded
     */
    void setTargetControlBlock(ControlBlock* pBlock);

    /**
     * Return the currently loaded target control block.
     * @return the target control block that is currently loaded
     */
    ControlBlock* getTargetControlBlock(void);

    /**
     * Reset the target control block.
     */
    void reset(void);

    /**
     * Perform a class-specific configuration check on a control action. It is
     * verified that the target control block has been loaded.
     */
    virtual bool isObjectConfigured(void);

};

#endif
