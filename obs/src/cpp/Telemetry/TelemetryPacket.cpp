//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TelemetryPacket.cpp
//
// Version	1.0
// Date		4.12.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "TelemetryPacket.h"

TelemetryPacket::TelemetryPacket(void) {
    inUse = false;
}

bool TelemetryPacket::isValid(void) {
	return VALID;
}

TD_TelemetryType TelemetryPacket::getType(void) const {
    return (TD_TelemetryType)(getClassId()%256);
}

void TelemetryPacket::setType(TD_TelemetryType tmType) {
    return;
}

TD_TelemetrySubType TelemetryPacket::getSubType(void) const {
    return 0;
}

void TelemetryPacket::setSubType(TD_TelemetrySubType tcSubType) {
    return;
}

TD_ObsTime TelemetryPacket::getTimeTag(void) const {
    return 0;
}

void TelemetryPacket::setTimeTag(TD_ObsTime timeTag) {
    return;
}

TD_TelemetryDestination TelemetryPacket::getDestination(void) const {
    return 0;
}

void TelemetryPacket::setDestination(TD_TelemetryDestination tmDest) {
    return;
}

void TelemetryPacket::setInUse(bool newInUse) {
    inUse = newInUse;
}

bool TelemetryPacket::isInUse(void) const {
    return inUse;
}

unsigned char* TelemetryPacket::getStartAddress(void) {
    return pNULL;
}

bool TelemetryPacket::isFastAcquisitionImplemented(void) {
    return false;
}

