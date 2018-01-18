//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// CC_TelemetryManager.cpp
//
// Version	1.0
// Date		03.03.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Base/CC_RootObject.h"
#include "CC_TelemetryPacketFactory.h"
#include "CC_TelemetryManager.h"
#include "TelemetryStream.h"
#include "TelemetryPacket.h"

CC_TelemetryManager::CC_TelemetryManager(void) {
    pTmStream = pNULL;
    pTmModeManager = pNULL;
    packetQueueSize = -1;
    pPacketQueue = pNULL;
    setClassId(ID_TELEMETRYMANAGER);
}

void CC_TelemetryManager::setTelemetryModeManager(TelemetryModeManager* pTmModeManager) {
    assert( pTmModeManager != pNULL );
    this->pTmModeManager = pTmModeManager;
}

TelemetryModeManager* CC_TelemetryManager::getTelemetryModeManager(void) const {
    assert( pTmModeManager != pNULL );
    return pTmModeManager;
}

void CC_TelemetryManager::setTelemetryStream(TelemetryStream* pTmStream) {
    assert( pTmStream != pNULL );
    this->pTmStream = pTmStream;
}

TelemetryStream* CC_TelemetryManager::getTelemetryStream(void) const {
    assert( pTmStream != pNULL );
    return pTmStream;
}

void CC_TelemetryManager::setImmediateQueueSize(unsigned int size) {
    assert(packetQueueSize==-1);        // must be called only once
    packetQueueSize = size;
    pPacketQueue = new TelemetryPacket*[packetQueueSize];
    for (int i=0; i<packetQueueSize; i++)
        pPacketQueue[i] = pNULL;
}

unsigned int CC_TelemetryManager::getImmediateQueueSize() {
    return (unsigned int)packetQueueSize;
}

TelemetryPacket* CC_TelemetryManager::getImmediateQueueEntry(unsigned int i) {
    assert( pPacketQueue!=pNULL );
    assert( (int)i<packetQueueSize );
    return pPacketQueue[i];
}

bool CC_TelemetryManager::isImmediateQueueFull() {
    if (packetQueueSize==0)
        return true;
    else
        return ( pPacketQueue[packetQueueSize-1]!=pNULL );
}

void CC_TelemetryManager::activate(void) {
    assert( pTmModeManager != pNULL );
    assert( pTmStream != pNULL);
    assert( packetQueueSize>=0 );

    TelemetryPacket* pTmPacket;

    for (int i=0; i<packetQueueSize; i++ ) {

        if ( pPacketQueue[i]!=pNULL) {
            pTmPacket = pPacketQueue[i];
            pPacketQueue[i]=pNULL;
        } else
            break;

        pTmPacket->update();

        if ( !pTmPacket->isValid() ) {
            CC_RootObject::getEventRepository()->create(this,EVT_TM_ITEM_NOT_VALID);
            pTmPacket->setInUse(false);
            continue;
        }

        if ( !pTmStream->doesPacketFit(pTmPacket) ) {
            CC_RootObject::getEventRepository()->create(this,EVT_TOO_MANY_TM_BYTES);
            pTmPacket->setInUse(false);
            break;
        }

        pTmStream->write(pTmPacket);
        pTmPacket->setInUse(false);
    }

    for (pTmModeManager->first();
                !pTmModeManager->isIterationFinished();
                        pTmModeManager->next()) {

        pTmPacket = pTmModeManager->getIterationTelemetryPacket();
        pTmPacket->update();

        if ( !pTmPacket->isValid() ) {
            CC_RootObject::getEventRepository()->create(this,EVT_TM_ITEM_NOT_VALID);
            continue;
        }

        if ( !pTmStream->doesPacketFit(pTmPacket) ) {
            CC_RootObject::getEventRepository()->create(this,EVT_TOO_MANY_TM_BYTES);
            break;
        }

        pTmStream->write(pTmPacket);
    }

    pTmStream->flush();
}

void CC_TelemetryManager::sendTelemetryPacket(TelemetryPacket* pTmPacket) {
    assert( pPacketQueue!=pNULL );

    for (int i=0; i<packetQueueSize; i++)
        if ( pPacketQueue[i]==pNULL ) {
            pPacketQueue[i]=pTmPacket;
            return;
        }

    getEventRepository()->create(this,EVT_TM_QUEUE_FULL);
    return;
}

void CC_TelemetryManager::unloadTelemetryPacket(TelemetryPacket* pTmPacket) {
    assert( pPacketQueue!=pNULL );
    assert( pTmPacket!=pNULL );

    for (int i=0; i<packetQueueSize; i++)
        if ( pPacketQueue[i]==pTmPacket ) {
            pPacketQueue[i]=pNULL;
            return;
        }

    return;
}

unsigned int CC_TelemetryManager::getImmediateQueueLoaded() {
    assert( pPacketQueue!=pNULL );

    unsigned int counter = 0;
    for (int i=0; i<packetQueueSize; i++)
        if ( pPacketQueue[i]!=pNULL ) {
            counter++;
        }
    return counter;
}


bool CC_TelemetryManager::isObjectConfigured(void) {
    return (CC_RootObject::isObjectConfigured() &&
            pTmModeManager!=pNULL && pTmStream!=pNULL &&
            packetQueueSize!=-1 );
}
