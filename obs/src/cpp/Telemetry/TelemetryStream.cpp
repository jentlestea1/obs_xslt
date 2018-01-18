//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TelemetryStream.cpp
//
// Version	1.0
// Date		4.12.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"
#include "TelemetryStream.h"

TelemetryStream::TelemetryStream(void) {
}

void TelemetryStream::reset(void) {
}

void TelemetryStream::flush(void) {
}

unsigned int TelemetryStream::getCapacity(void) {
    return MAX_INT;
}

bool TelemetryStream::doesPacketFit(TelemetryPacket* pTmPacket) {
    return true;
}
