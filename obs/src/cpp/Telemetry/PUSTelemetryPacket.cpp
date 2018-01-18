//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// PUSTelemetryPacket.cpp
//
// Version	1.0
// Date		4.12.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../System/ObsClock.h"
#include "TelemetryPacket.h"
#include "PUSTelemetryPacket.h"

TD_PUSPacketId PUSTelemetryPacket::packetId = 0;
TD_TelemetryDestination PUSTelemetryPacket::defaultDestination = 0;
ObsClock* PUSTelemetryPacket::pObsClock = pNULL;

PUSTelemetryPacket::PUSTelemetryPacket(void) {
    type = 0;
    subType = 0;
    timeTag = -1;
    dest = defaultDestination;
}

TD_PUSPacketId PUSTelemetryPacket::getPacketId(void) {
    return packetId;
}

void PUSTelemetryPacket::setApplicationId(TD_APID apid) {
    assert( apid < (TD_APID)2048 );
    packetId = 2048;
    packetId = packetId + apid;
}

void PUSTelemetryPacket::setDefaultDestination(TD_TelemetryDestination defDest) {
    assert( defDest > 0 );
    defaultDestination = defDest;
}

TD_TelemetryDestination PUSTelemetryPacket::getDefaultDestination() {
    return defaultDestination;
}


TD_TelemetryType PUSTelemetryPacket::getType(void) const {
    assert( type>0 );
    return type;
}

void PUSTelemetryPacket::setType(TD_TelemetryType tmType) {
    assert( tmType>0 );
    type = tmType;
}

TD_TelemetrySubType PUSTelemetryPacket::getSubType(void) const {
    assert( subType>0 );
    return subType;
}

void PUSTelemetryPacket::setSubType(TD_TelemetrySubType tmSubType) {
    assert( tmSubType>0 );
    subType = tmSubType;
}

TD_ObsTime PUSTelemetryPacket::getTimeTag(void) const {
    assert( timeTag>= 0 );
    return timeTag;
}

void PUSTelemetryPacket::setTimeTag(TD_ObsTime tTag) {
    assert( tTag>=0 );
    timeTag = tTag;
}

TD_TelemetryDestination PUSTelemetryPacket::getDestination(void) const {
    assert( dest>0 );
    return dest;
}

void PUSTelemetryPacket::setDestination(TD_TelemetryDestination tmDest) {
    assert( tmDest>0 );
    dest = tmDest;
}

ObsClock* PUSTelemetryPacket::getObsClock(void) {
   assert (pObsClock != pNULL );
   return pObsClock;
}

void PUSTelemetryPacket::setObsClock(ObsClock* pClock) {
   assert (pClock != pNULL );
   pObsClock = pClock;
}

bool PUSTelemetryPacket::isObjectConfigured(void) {
   return ( TelemetryPacket::isObjectConfigured() &&
           (type>0) &&
           (subType>0) &&
           (dest>0) &&
           (packetId>0) &&
           (pObsClock!=pNULL) &&
           (timeTag>=0) );
}
