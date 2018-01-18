//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_ByteArrayTelemetryStream.cpp
//
// Version	1.0
// Date		04.03.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/TelemetryPacket.h"
#include "DC_ByteArrayTelemetryStream.h"

DC_ByteArrayTelemetryStream::DC_ByteArrayTelemetryStream(void) {
    size = 0;
    tmData = pNULL;
    writeCounter = 0;
    setClassId(ID_BYTEARRAYTELEMETRYSTREAM);
}

void DC_ByteArrayTelemetryStream::reset(void) {
    assert(size>0 && tmData!=pNULL);
    writeCounter = 0;
}

void DC_ByteArrayTelemetryStream::flush(void) {
    reset();
}

unsigned int DC_ByteArrayTelemetryStream::getCapacity(void) {
    assert( size > 0 );
    return size;
}

void DC_ByteArrayTelemetryStream::setCapacity(unsigned int n) {
    assert( n > 0 );
    size = n;
}

void DC_ByteArrayTelemetryStream::setStartingAddress(unsigned char* pAddress) {
    assert( pAddress != pNULL );
    tmData = pAddress;
}

unsigned char* DC_ByteArrayTelemetryStream::getStartingAddress(void) const {
    assert( tmData != pNULL );
    return tmData;
}

bool DC_ByteArrayTelemetryStream::doesPacketFit(TelemetryPacket* pItem) {
    assert( isObjectConfigured() );
    return (pItem->getNumberOfBytes() <= (size-writeCounter) );
}

void DC_ByteArrayTelemetryStream::write(TelemetryPacket* pItem) {
    assert( isObjectConfigured() );
    unsigned int base = writeCounter;
    for (unsigned int i=0; i<pItem->getNumberOfBytes(); i++) {
        if ( (i+base)>=size )
            break;
        tmData[base+i] = pItem->getUnsignedByte(i);
        writeCounter++;
    }
}

bool DC_ByteArrayTelemetryStream::isObjectConfigured(void) {
    return (TelemetryStream::isObjectConfigured() && size>0 && tmData!=pNULL);
}

