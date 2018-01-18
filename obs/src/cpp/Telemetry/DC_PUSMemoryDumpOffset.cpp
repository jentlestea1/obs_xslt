//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSMemoryDumpOffset.cpp
//
// Version	1.0
// Date		04.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Utilities/Checksum.h"
#include "../Telecommand/PUSTelecommand.h"
#include "../Telemetry/PUSTelemetryPacket.h"
#include "../Telemetry/DC_PUSMemoryDumpOffset.h"

#include <string.h>

DC_PUSMemoryDumpOffset::DC_PUSMemoryDumpOffset(void) {
    setClassId(ID_PUSMEMORYDUMPOFFSET);
    setSubType(PUS_ST_TM_DMP_OFF);
    base = pNULL;
}

void DC_PUSMemoryDumpOffset::setBaseAddress(TD_PUSMemData* base) {
    assert( base!=0 );
    this->base = base;
}

TD_PUSMemData* DC_PUSMemoryDumpOffset::getBaseAddress() {
    return base;
}

void DC_PUSMemoryDumpOffset::update(void) {
    assert( base!=pNULL );
    assert( memId!=0 );
    assert( isObjectConfigured() );
        
    // compute the number of bytes in the packet. Compute first the size of the
    // fixed part of the packet and then the size of each block.
    unsigned int fixedLength = sizeof(TD_PUSMemId)+sizeof(TD_PUSMemData*)+sizeof(TD_PUSNumberMemBlocks);
    unsigned int blockLength = 0;

    for (TD_PUSNumberMemBlocks i=0; i<numberBlocks; i++) {
        blockLength = blockLength + sizeof(TD_PUSMemOffset)+sizeof(TD_PUSMemLength)+sizeof(unsigned short);
        blockLength = blockLength + block[i].length*sizeof(TD_PUSMemData);
    }

    tmPacketSize = blockLength+fixedLength;
    if (tmPacketSize>maxNumberData) {
        getEventRepository()->create(this,EVT_PUS_TOO_MANY_MEM_DATA);
        return;
    }

    unsigned int offset = 0;
    memcpy(data+offset,&memId,sizeof(TD_PUSMemId));
    offset = offset + sizeof(TD_PUSMemId);
    memcpy(data+offset,&base,sizeof(TD_PUSMemData*));
    offset = offset + sizeof(TD_PUSMemData*);
    memcpy(data+offset,&numberBlocks,sizeof(TD_PUSNumberMemBlocks));
    offset = offset + sizeof(TD_PUSNumberMemBlocks);

    assert( numberBlocks<maxNumberBlocks );

    for (TD_PUSNumberMemBlocks i=0; i<numberBlocks; i++)  {
        TD_PUSMemOffset moTemp = (TD_PUSMemOffset)(block[i].startAddress-base);
        memcpy(data+offset,&moTemp,sizeof(TD_PUSMemOffset));
        offset = offset + sizeof(TD_PUSMemOffset);
        memcpy(data+offset,&block[i].length,sizeof(TD_PUSMemLength));
        offset = offset + sizeof(TD_PUSMemLength);

        unsigned char* start = (unsigned char*)(block[i].startAddress);
        unsigned int nBytes = (block[i].length)*sizeof(TD_PUSMemData);
        memcpy(data+offset,start,nBytes);
        offset = offset + nBytes;

        unsigned short checksum;
        if ( isChecksumFlagSet() ) 
            checksum = doChecksum(start,nBytes);
        else
            checksum = 0;
        memcpy(data+offset,&checksum,sizeof(unsigned short));
        offset = offset+sizeof(unsigned short);
    }
}