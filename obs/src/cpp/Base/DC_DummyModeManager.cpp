//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyModeManager.cpp
//
// Version	1.0
// Date		24.02.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_DummyModeManager.h"
#include "ModeManager.h"

DC_DummyModeManager::DC_DummyModeManager(void) {
    setClassId(ID_DUMMYMODEMANAGER);
}

void DC_DummyModeManager::update(void) {
    if (getCurrentMode()<(getNumberOfModes()-1))
        setMode(getCurrentMode()+1);
    else
        setMode(0);
}

void DC_DummyModeManager::allocateMemory(TD_Mode n) {
    return;
}
