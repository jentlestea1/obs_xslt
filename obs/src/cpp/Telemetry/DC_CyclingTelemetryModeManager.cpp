//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_CyclingTelemetryModeManager.cpp
//
// Version	1.0
// Date		24.02.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../Telemetry/DC_CyclingTelemetryModeManager.h"
#include "../Base/ModeManager.h"

DC_CyclingTelemetryModeManager::DC_CyclingTelemetryModeManager(void) {
    setClassId(ID_CYCLINGTELEMETRYMODEMANAGER);
}

void DC_CyclingTelemetryModeManager::update(void) {
    if (getCurrentMode()<(getNumberOfModes()-1))
        setMode(getCurrentMode()+1);
    else
        setMode(0);
}

