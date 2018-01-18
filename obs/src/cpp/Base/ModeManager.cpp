//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// ModeManager.cpp
//
// Version	1.0
// Date		13.04.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "ModeManager.h"

ModeManager::ModeManager(void) {
    enabledStatus = pNULL;
    transitionsEnabled = ENABLED;
    numberOfModes = 0;
    currentMode = -1;
    defaultMode = -1;
}

void ModeManager::setMode(TD_Mode newMode) {
    assert( (newMode >= 0) && (newMode < numberOfModes) );
    assert(isObjectConfigured());

    if (newMode==currentMode)
        return;

    if (isTransitionEnabled() && isTransitionEnabled(newMode)) {
        currentMode=newMode;
        CC_RootObject::getEventRepository()->create(this,EVT_MOD_TRANS_PERFORMED);
    }
    else
        CC_RootObject::getEventRepository()->create(this,EVT_MOD_TRANS_INHIBITED);
}

void ModeManager::setNumberOfModes(TD_Mode nOfModes) {
    assert(numberOfModes == 0);  // should be called only once
    assert(nOfModes > 0);

    numberOfModes = nOfModes;
    enabledStatus = new bool[numberOfModes];
    for (TD_Mode i=0; i<numberOfModes; i++)
        enabledStatus[i] = ENABLED;
    allocateMemory(numberOfModes);
}

void ModeManager::setDefaultMode(TD_Mode defMode) {
    assert( (defMode >= 0) && (defMode < numberOfModes) );
    if ( (defMode >= 0) && (defMode < numberOfModes) )
        defaultMode = defMode;
    else
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_MM);
}

void ModeManager::reset(void) {
    assert( isObjectConfigured() );
    currentMode = defaultMode;
    for (int i=0; i<numberOfModes; i++)
        enabledStatus[i] = ENABLED;
    transitionsEnabled = ENABLED;
}

void ModeManager::setTransitionEnableStatus(bool enabled) {
    assert( isObjectConfigured() );
    transitionsEnabled = enabled;
}

void ModeManager::setTransitionEnableStatus(TD_Mode toMode, bool enabled) {
    assert( isObjectConfigured() );
    assert( (toMode >= 0) && (toMode < numberOfModes) );
    if ( (toMode >= 0) && (toMode < numberOfModes) )
        enabledStatus[toMode] = enabled;
    else
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_MM);
}

bool ModeManager::isObjectConfigured(void) {
    return (CC_RootObject::isObjectConfigured() &&
            numberOfModes>0 && defaultMode>=0);
}
