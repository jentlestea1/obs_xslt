//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_SimplePunctualActionModeManager.cpp
//
// Version	1.0
// Date		29.09.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_SimplePunctualActionModeManager.h"

DC_SimplePunctualActionModeManager::DC_SimplePunctualActionModeManager(void) {
    setClassId(ID_SIMPLEPUNCTUALACTIONMODEMANAGER);
    setNumberOfModes(1);
    setDefaultMode(0);
}

void DC_SimplePunctualActionModeManager::update(void) {
}
