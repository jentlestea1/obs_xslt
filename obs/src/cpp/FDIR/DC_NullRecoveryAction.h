//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_NullRecoveryAction.h
//
// Version	1.0
// Date		11.06.03 (version 1.0)
// Author	A. Pasetti (P&P Software)

#ifndef NullRecoveryActionH
#define NullRecoveryActionH

#include "../GeneralInclude/BasicTypes.h"
#include "RecoveryAction.h"

/**
 * Recovery action that performs no action.
 * This recovery action is useful as a "placeholder" where a component
 * of type <code>RecoveryAction</code> is required but where no
 * concrete recovery actions are defined.
 * <p>
 * Note that there is no preclusion to linking non-null recovery
 * actions to a null recovery action.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_NullRecoveryAction : public RecoveryAction {

  public:

    /**
     * Instantiate a null recovery action. The class identifier is set.
     */
    DC_NullRecoveryAction(void);

  protected:

    /**
     * Return without taking any action.
     * @see RecoveryAction#doAction
     * @return always return the outcome code ACTION_SUCCESS
     */
    virtual TD_ActionOutcome doRecoveryAction(void);

};

#endif
