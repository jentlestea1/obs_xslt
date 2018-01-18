//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_SimpleTelemetryModeManager.cpp
//
// Version	1.0
// Date		24.02.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_SimpleTelemetryModeManager.h"

DC_SimpleTelemetryModeManager::DC_SimpleTelemetryModeManager(void) {
    setClassId(ID_SIMPLETELEMETRYMODEMANAGER);
    setNumberOfModes(1);
    setDefaultMode(0);
}

void DC_SimpleTelemetryModeManager::update(void) {
    return;
}
