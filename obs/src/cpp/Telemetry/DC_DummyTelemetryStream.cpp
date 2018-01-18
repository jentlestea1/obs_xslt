//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyTelemetryStream.cpp
//
// Version	1.0
// Date		04.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_DummyTelemetryStream.h"

DC_DummyTelemetryStream::DC_DummyTelemetryStream(void) {
    setClassId(ID_DUMMYTELEMETRYSTREAM);
}

void DC_DummyTelemetryStream::write(TelemetryPacket *tmItem) {
    return;
}
