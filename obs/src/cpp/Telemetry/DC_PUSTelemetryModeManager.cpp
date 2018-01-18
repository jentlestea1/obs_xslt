//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSTelemetryModeManager.cpp
//
// Version	1.0
// Date		24.01.04
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../Telemetry/DC_PUSTelemetryModeManager.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"
#include "../Base/ModeManager.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"

DC_PUSTelemetryModeManager::DC_PUSTelemetryModeManager(void) {
    setClassId(ID_PUSTELEMETRYMODEMANAGER);
    setNumberOfModes(1);
    setDefaultMode(0);

    counter = 0;
	list = pNULL;
	listLength = 0;
    iterationCounter = 0;
}

void DC_PUSTelemetryModeManager::allocateMemory(TD_Mode numberOfModes) {
    return;
}

void DC_PUSTelemetryModeManager::update(void) {
    return;
}

void DC_PUSTelemetryModeManager::setMaxNumberOfPackets(unsigned int n) {
    assert( listLength == 0 );
    assert( n>0 );

    listLength = n;
    list = new DC_PUSDataReportingPacket*[listLength];
    for (unsigned int i=0; i<listLength; i++)
        list[i] = pNULL;
}


void DC_PUSTelemetryModeManager::loadPacket(DC_PUSDataReportingPacket* pItem) {
    assert( list!=pNULL );
    assert( pItem != pNULL );

    for (unsigned int i=0; i<listLength; i++) 
        if ( list[i]==pNULL ) {
            list[i]=pItem;
            assert(counter<listLength);
            counter++;
            return;
        }
    
    assert(counter==listLength);
    CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_MM);
    return;
}

bool DC_PUSTelemetryModeManager::isFull() const {
    return (counter==listLength);
}

unsigned int DC_PUSTelemetryModeManager::getNumberOfPackets() const {
    return counter;
}

unsigned int DC_PUSTelemetryModeManager::getMaxNumberOfPackets() const {
    return listLength;
}

void DC_PUSTelemetryModeManager::unloadPacket(TD_SID sid) {
    assert( list!=pNULL );

    for (unsigned int i=0; i<listLength; i++)  {
        if ( list[i]==pNULL )
            continue;
        if ( list[i]->getSID()==sid ) {
            list[i]=pNULL;
            counter--;
            return;
        }
    }
    
    CC_RootObject::getEventRepository()->create(this,EVT_SID_NOT_FOUND);
    return;
}

bool DC_PUSTelemetryModeManager::isSIDLoaded(TD_SID sid) const {
    assert( list!=pNULL );

    for (unsigned int i=0; i<listLength; i++) {
        if ( list[i]==pNULL )
            continue;
        if ( list[i]->getSID()==sid ) 
            return true;
    }
    
    return false;
}

void DC_PUSTelemetryModeManager::first(void) {
    assert( isObjectConfigured() );
    iterationCounter = 0;
    while ( (iterationCounter<listLength) && (list[iterationCounter]==pNULL) )
        iterationCounter++;
}

void DC_PUSTelemetryModeManager::next(void) {
    assert( isObjectConfigured() );
    iterationCounter++;
    while ( (iterationCounter<listLength) && (list[iterationCounter]==pNULL) )
        iterationCounter++;
}

bool DC_PUSTelemetryModeManager::isIterationFinished(void) {
    assert( isObjectConfigured() );
    assert( iterationCounter<=listLength );
    return( iterationCounter == listLength );
}

TelemetryPacket* DC_PUSTelemetryModeManager::getIterationTelemetryPacket(void) {
    assert( isObjectConfigured() );
    assert( iterationCounter<listLength );
    return list[iterationCounter];
}

bool DC_PUSTelemetryModeManager::isObjectConfigured(void) {
    if (!TelemetryModeManager::isObjectConfigured() || list==pNULL )
        return NOT_CONFIGURED;

    return CONFIGURED;
}

