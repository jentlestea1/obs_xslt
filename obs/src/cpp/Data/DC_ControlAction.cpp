//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_ControlAction.cpp
//
// Version	1.0
// Date		28.07.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Base/ConditionalPunctualAction.h"
#include "ControlBlock.h"
#include "DC_ControlAction.h"

DC_ControlAction::DC_ControlAction(void) {
    setClassId(ID_CONTROLACTION);
    pTargetControlBlock = pNULL;
}

TD_ActionOutcome DC_ControlAction::doConditionalAction(void) {
    assert( pTargetControlBlock != pNULL );
    pTargetControlBlock->propagate();
    return ACTION_SUCCESS;
}

bool DC_ControlAction::canExecute(void) {
    return true;
}

void DC_ControlAction::setTargetControlBlock(ControlBlock* pBlock) {
    assert( pBlock != pNULL );
    pTargetControlBlock = pBlock;
}

ControlBlock* DC_ControlAction::getTargetControlBlock(void) {
    return pTargetControlBlock;
}

void DC_ControlAction::reset(void) {
    assert( pTargetControlBlock != pNULL );
    pTargetControlBlock->reset();
}

bool DC_ControlAction::isObjectConfigured(void) {
   return (ConditionalPunctualAction::isObjectConfigured() && pTargetControlBlock!=pNULL);
}
