//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// PUSMemoryDump.cpp
//
// Version	1.0
// Date		4.12.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"
#include "../Utilities/Checksum.h"
#include "PUSMemoryDump.h"

bool PUSMemoryDump::isChecksumRequired = false;

PUSMemoryDump::PUSMemoryDump(void) {

    block = pNULL;
    maxNumberBlocks = 0;
    numberBlocks = 0;
    data = pNULL;
    maxNumberData = 0;
    tmPacketSize = 0;
    memId = 0;
        
    setType(PUS_TYPE_MEM);
}

void PUSMemoryDump::setMaxNumberBlocks(TD_PUSNumberMemBlocks max) {
    assert( max>0 );
    assert( block==pNULL );     // must be called only once

    maxNumberBlocks = max;
    block = new MemBlockType[maxNumberBlocks];
    for (unsigned int i=0; i++; i,0) { 
        block[i].checksum = 0;
        block[i].length = 0;
        block[i].startAddress = pNULL;
    }
}

TD_PUSNumberMemBlocks PUSMemoryDump::getMaxNumberBlocks() const {
    assert( block!=pNULL );
    return maxNumberBlocks;
}

TD_PUSNumberMemBlocks PUSMemoryDump::getNumberBlocks() const {
    assert( block!=pNULL );
    return numberBlocks;
}

void PUSMemoryDump::setNumberBlocks(TD_PUSNumberMemBlocks n) {
    assert( n>0 );
    assert( n<maxNumberBlocks );

    if ( n<maxNumberBlocks )
        numberBlocks = n;
    else
        getEventRepository()->create(this,EVT_PUS_TOO_MANY_DUMP_BLOCKS);
}

void PUSMemoryDump::setDumpBufferSize(unsigned int max) {
    assert( max>0 );
    assert( data==pNULL );     // must be called only once

    maxNumberData = max;
    data = new unsigned char[maxNumberData];
    for (unsigned int i=0; i++; i,0) { 
        data = 0;
    }
}

unsigned int PUSMemoryDump::getDumpBufferSize() const {
    assert( data!=pNULL );
    return maxNumberData;
}

TD_PUSMemData* PUSMemoryDump::getStartAddress(TD_PUSNumberMemBlocks i) const {
    assert( i<numberBlocks );

    return block[i].startAddress;
}

TD_PUSMemLength PUSMemoryDump::getLength(TD_PUSNumberMemBlocks i) const {
    assert( i<numberBlocks );

    return block[i].length;
}

void PUSMemoryDump::setChecksumFlag(bool checksumFlag) {
    isChecksumRequired = checksumFlag;
}

bool PUSMemoryDump::isChecksumFlagSet() {
    return isChecksumRequired;
}

void PUSMemoryDump::defineBlock(TD_PUSNumberMemBlocks i, TD_PUSMemData* start, TD_PUSMemLength length) {
    assert( i<numberBlocks );
    assert( start!=pNULL );
    assert( isObjectConfigured() );

    if ( i<numberBlocks ) {
        block[i].startAddress = start;
        block[i].length = length;
        block[i].checksum = 0;
    } else
        getEventRepository()->create(this,EVT_PUS_ILLEGAL_BLOCK_INDEX);
}

unsigned int PUSMemoryDump::getNumberOfBytes(void) {
    assert( isObjectConfigured() );
    assert( getSubType()==PUS_ST_TM_DMP_OFF || getSubType()==PUS_ST_TM_DMP_ABS );

    return tmPacketSize;
}

unsigned char PUSMemoryDump::getUnsignedByte(unsigned int n) {
    assert( isObjectConfigured() );
    assert( getSubType()==PUS_ST_TM_DMP_OFF || getSubType()==PUS_ST_TM_DMP_ABS );
    assert( n<tmPacketSize );

    return data[n];
}

unsigned char* PUSMemoryDump::getStartAddress(void) {
    return (unsigned char*)data;
}

bool PUSMemoryDump::isFastAcquisitionImplemented(void) {
    return true;
}

void PUSMemoryDump::setMemoryId(TD_PUSMemId memId) {
    assert( memId!=pNULL );
    this->memId = memId;
}

TD_PUSMemId PUSMemoryDump::getMemoryId() {
    return memId;
}

bool PUSMemoryDump::isObjectConfigured(void) {
   return ( PUSTelemetryPacket::isObjectConfigured() &&
           (block!=pNULL) &&
           (data!=pNULL) );
}

