//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// ModeManager_inl.h
//
// Version	1.0
// Date		23.02.03
// Author	A. Pasetti (P&P Software)

#ifndef ModeManager_INL
#define ModeManager_INL

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"

inline TD_Mode ModeManager::getCurrentMode(void) const {
    assert(numberOfModes > 0); 
    assert(currentMode >= 0);
    assert(currentMode < numberOfModes);
    return currentMode;
}

inline bool ModeManager::isTransitionEnabled(TD_Mode toMode) const {
    assert( toMode < numberOfModes );
    assert( toMode >= 0 );
    return enabledStatus[toMode];
}

inline bool ModeManager::isTransitionEnabled(void) const {
    return transitionsEnabled;
}

inline TD_Mode ModeManager::getNumberOfModes(void) const {
    return numberOfModes;
}

#endif
