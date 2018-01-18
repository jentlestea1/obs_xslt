//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// ConditionalPunctualAction.cpp
//
// Version	1.0
// Date		17.05.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/ConditionalPunctualAction.h"

ConditionalPunctualAction::ConditionalPunctualAction(void) {
}

TD_ActionOutcome ConditionalPunctualAction::doAction(void) {
    if (canExecute())
        return doConditionalAction();
    else
        return ACTION_CANNOT_EXECUTE;
}

