//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_BasicPUSTmStream.cpp
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
#include "DC_BasicPUSTmStream.h"

#include <string.h>

DC_BasicPUSTmStream::DC_BasicPUSTmStream(void) {
    size = 0;
    tmData = pNULL;
    writeCounter = 0;
    packetSequenceControl = 0xC0;   
    nAdditionalBytes = 11+sizeof(TD_ObsTime);
    setClassId(ID_BASICPUSTMSTREAM);
}

void DC_BasicPUSTmStream::reset(void) {
    assert(size>0 && tmData!=pNULL);
    writeCounter = 1;
    tmData[0]=0;
}

void DC_BasicPUSTmStream::flush(void) {
    reset();
}

unsigned int DC_BasicPUSTmStream::getCapacity(void) {
    assert( size > 0 );
    return size;
}

void DC_BasicPUSTmStream::setCapacity(unsigned int n) {
    assert( n > 0 );
    size = n;
}

void DC_BasicPUSTmStream::setStartAddress(unsigned char* pAddress) {
    assert( pAddress != pNULL );
    tmData = pAddress;
    reset();
}

unsigned char* DC_BasicPUSTmStream::getStartAddress(void) const {
    assert( tmData != pNULL );
    return tmData;
}

unsigned int DC_BasicPUSTmStream::getPacketCounter(void) const {
    assert( tmData!=pNULL );
    return tmData[0];
}

unsigned int DC_BasicPUSTmStream::getWriteCounter(void) const {
    return writeCounter;
}

unsigned int DC_BasicPUSTmStream::getSequenceCounter(void) const {
    return (packetSequenceControl%0x40);
}

bool DC_BasicPUSTmStream::doesPacketFit(TelemetryPacket* pItem) {
    assert( isObjectConfigured() );
    
    if (pItem->getNumberOfBytes()==0)
        return true;

    return ( (pItem->getNumberOfBytes()+nAdditionalBytes) <= (size-writeCounter) );
}

void DC_BasicPUSTmStream::write(TelemetryPacket* pItem) {
    assert( isObjectConfigured() );
    unsigned int nTmData = pItem->getNumberOfBytes();

    // Increment packet sequence counter
    if ( packetSequenceControl==0xFF )
        packetSequenceControl = 0xC0;
    else
        packetSequenceControl++;

    // Check if the packet fits in the telemetry write area
    if ( (writeCounter+nTmData+nAdditionalBytes)>getCapacity() ) {
        CC_RootObject::getEventRepository()->create(this,EVT_TM_STREAM_END);
        return;
    }

    assert(sizeof(TD_PUSPacketId)==2);

    // Write packet header
    TD_PUSPacketId t1 = PUSTelemetryPacket::getPacketId();
    unsigned short t3 = (unsigned short)(nAdditionalBytes-6+nTmData);
    memcpy(tmData+writeCounter,&t1,2);
    memcpy(tmData+writeCounter+2,&packetSequenceControl,2);
    memcpy(tmData+writeCounter+4,&t3,2);
    writeCounter = writeCounter+6;

    // Write packet data field
    assert(sizeof(TD_TelemetryType)==1);
    assert(sizeof(TD_TelemetrySubType)==1);
    tmData[writeCounter] = 0x10;
    tmData[writeCounter+1] = pItem->getType();
    tmData[writeCounter+2] = pItem->getSubType();

    TD_ObsTime obsTimeTag = pItem->getTimeTag();
    memcpy(tmData+writeCounter+3,&obsTimeTag,sizeof(TD_ObsTime));

    writeCounter = writeCounter+3+sizeof(TD_ObsTime);

    if (pItem->isFastAcquisitionImplemented()) {
        unsigned char* s = pItem->getStartAddress();
        for (unsigned int j=0; j<nTmData; j++) 
            tmData[writeCounter+j] = s[j];
    } else
        for (unsigned int i=0; i<nTmData; i++) {
            tmData[writeCounter+i] = pItem->getUnsignedByte(i);
        }
    writeCounter = writeCounter+nTmData;

    // Write the packet error control field
    tmData[writeCounter] = 0;
    tmData[writeCounter+1] = 0;
    writeCounter = writeCounter+2;

    // Update the packet counter
    tmData[0]++;

}

bool DC_BasicPUSTmStream::isObjectConfigured(void) {
    return ( TelemetryStream::isObjectConfigured() && 
             size>0 && 
             tmData!=pNULL );
}

