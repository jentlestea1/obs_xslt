//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// PunctualAction.cpp
//
// Version	1.0
// Date		01.10.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "PunctualAction.h"

PunctualAction::PunctualAction(void) {
    enabledStatus = ENABLED;
    lastOutcome = ACTION_RESET;
}

TD_ActionOutcome PunctualAction::execute(void) {
    TD_ActionOutcome outcomeCode = ACTION_DISABLED;

    if ( isEnabled() ) {
        outcomeCode = doAction();
        CC_RootObject::getEventRepository()->create(this, EVT_PUNCTUAL_ACTION_EXEC );
    } else
        CC_RootObject::getEventRepository()->create(this, EVT_PUNCTUAL_ACTION_DIS );

    lastOutcome = outcomeCode;
    return outcomeCode;
}

void PunctualAction::setEnabled(bool isEnabled) {
    enabledStatus = isEnabled;
}

bool PunctualAction::isEnabled(void) const {
    return enabledStatus;
}

TD_ActionOutcome PunctualAction::getLastOutcome(void) const {
    return lastOutcome;
}

void PunctualAction::resetLastOutcome(void) {
    lastOutcome = ACTION_RESET;
}
