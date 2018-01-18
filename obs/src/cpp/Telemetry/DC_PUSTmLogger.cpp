//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSTmLogger.cpp
//
// Version	1.0
// Date		04.02.04 (Version 1.0)
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"
#include "../Telemetry/TelemetryPacket.h"
#include "../Telemetry/PUSTelemetryPacket.h"
#include "DC_PUSTmLogger.h"

DC_PUSTmLogger::DC_PUSTmLogger(void) {
    tmBuffer = pNULL;
    maxData = 0;
    counter = 0;
    capacity = 0;
    setClassId(ID_PUSTMLOGGER);
}

void DC_PUSTmLogger::setBufferCapacity(unsigned int n) {
    assert( n>0 );
    assert( tmBuffer==pNULL );

    capacity = n;
    tmBuffer = new TmPacket[capacity];

    for (unsigned int i=0; i<capacity; i++) {
        tmBuffer[i].data = pNULL;
        tmBuffer[i].nData = 0;
        tmBuffer[i].subType = 0;
        tmBuffer[i].timeTag = 0;
        tmBuffer[i].type = 0;
    }
}

unsigned int DC_PUSTmLogger::getBufferCapacity() const {
    return capacity;
}

void DC_PUSTmLogger::setMaxPacketLength(unsigned int n) {
    assert( n>0 );
    assert( tmBuffer!=pNULL );
    assert( maxData==0 ); 

    maxData = n;
    
    for (unsigned int i=0; i<capacity; i++) {
        tmBuffer[i].data = new unsigned char[maxData];
        for (unsigned int j=0; j<maxData; j++)
            tmBuffer[i].data[j]=0;
    }
}

unsigned int DC_PUSTmLogger::getMaxPacketLength() const {
    return maxData;
}

unsigned int DC_PUSTmLogger::getPacketCounter(void) const {
    return counter;
}

bool DC_PUSTmLogger::doesPacketFit(TelemetryPacket* pItem) {
    assert( isObjectConfigured() );
    
    if (pItem->getNumberOfBytes()<maxData)
        return true;
    else
        return false;
}

void DC_PUSTmLogger::write(TelemetryPacket* pItem) {
    assert( isObjectConfigured() );

    unsigned int pos = counter%capacity;

    // Check packet length
    unsigned int n = maxData;
    if (pItem->getNumberOfBytes()<maxData)
        n = pItem->getNumberOfBytes();

    tmBuffer[pos].type = pItem->getType();
    tmBuffer[pos].subType = pItem->getSubType();
    tmBuffer[pos].nData = pItem->getNumberOfBytes();
    tmBuffer[pos].timeTag = pItem->getTimeTag();
    
    if (pItem->isFastAcquisitionImplemented()) {
        unsigned char* s = pItem->getStartAddress();
        for (unsigned int j=0; j<n; j++) 
            tmBuffer[pos].data[j] = s[j];
    } else
        for (unsigned int i=0; i<n; i++) 
            tmBuffer[pos].data[i] = pItem->getUnsignedByte(i);
        
    // Update the packet counter
    counter++;

}

bool DC_PUSTmLogger::isObjectConfigured(void) {
    return ( TelemetryStream::isObjectConfigured() && 
             maxData>0 && 
             tmBuffer!=pNULL );
}

