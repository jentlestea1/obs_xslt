//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_CyclingPunctualActionModeManager.cpp
//
// Version	1.0
// Date		24.01.04
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../Base/DC_CyclingPunctualActionModeManager.h"
#include "../Base/ModeManager.h"

DC_CyclingPunctualActionModeManager::DC_CyclingPunctualActionModeManager(void) {
    setClassId(ID_CYCLINGPUNCTUALACTIONMODEMANAGER);
}

void DC_CyclingPunctualActionModeManager::update(void) {
    if (getCurrentMode()<(getNumberOfModes()-1))
        setMode(getCurrentMode()+1);
    else
        setMode(0);
}

