//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_CycleDataItem16TmStream.cpp
//
// Version	1.1
// Date		04.12.02 (Version 1.0)
//          04.03.03 (Version 1.1)
// Author	A. Pasetti (P&P Software)
//
// Change Record:
//   Version 1.1: Changed implementation of method "flush" to be
//                equivalent to a call to method "reset".

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_RawDataItem.h"
#include "../Telemetry/TelemetryPacket.h"
#include "DC_CycleDataItem16TmStream.h"

DC_CycleDataItem16TmStream::DC_CycleDataItem16TmStream(void) {
    nDataItems = 0;
    writeCounter = 0;
    setClassId(ID_CYCLEDATAITEM16TMSTREAM);
}

void DC_CycleDataItem16TmStream::reset(void) {
    assert(nDataItems>0 && pDataItem!=pNULL);
    writeCounter = 0;
}

void DC_CycleDataItem16TmStream::flush(void) {
    reset();
}

unsigned int DC_CycleDataItem16TmStream::getCapacity(void) {
    assert(nDataItems>0 && pDataItem!=pNULL);
    return nDataItems;
}

void DC_CycleDataItem16TmStream::setNumberOfDataItems(unsigned int n) {
    assert( nDataItems == 0 );        // should only be called once
    assert( n > 0 );

    if (nDataItems == 0) {
        nDataItems = n;
        pDataItem = new DC_RawDataItem*[nDataItems];
        for (unsigned int i=0; i<nDataItems; i++)
            pDataItem[i] = pNULL;
        reset();
    }
}

void DC_CycleDataItem16TmStream::setDataItem(unsigned int index, DC_RawDataItem* pDI) {
    assert(nDataItems>0 && index<nDataItems);
    assert(pDI!=pNULL);
    pDataItem[index] = pDI;
}

bool DC_CycleDataItem16TmStream::doesPacketFit(TelemetryPacket* pPacket) {
    assert( isObjectConfigured() );
    return ( pPacket->getNumberOfBytes() <= 2*(nDataItems-writeCounter) );
}

void DC_CycleDataItem16TmStream::write(TelemetryPacket* pItem) {
    assert( isObjectConfigured() );
    unsigned short tmValue;
    unsigned short temp;
    for (unsigned int i=0; i<(pItem->getNumberOfBytes()-1);i=i+2) {
        if ( writeCounter < nDataItems) {
            tmValue = (unsigned short)pItem->getUnsignedByte(i);
            temp = ((unsigned short)pItem->getUnsignedByte(i+1))<<8;
            tmValue = tmValue + temp;
            pDataItem[writeCounter]->setUnsignedShort(tmValue);
            writeCounter++;
        } else
            break;
    }
}

bool DC_CycleDataItem16TmStream::isObjectConfigured(void) {
    if (!TelemetryStream::isObjectConfigured() || nDataItems==0)
        return NOT_CONFIGURED;

    for (unsigned int i=0; i<nDataItems; i++) {
        if ( pDataItem[i] == pNULL )
            return NOT_CONFIGURED;
    }

    return CONFIGURED;
}

