//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSMemoryDumpAbsolute.cpp
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
#include "../Telemetry/DC_PUSMemoryDumpAbsolute.h"

#include <string.h>

DC_PUSMemoryDumpAbsolute::DC_PUSMemoryDumpAbsolute(void) {
    setClassId(ID_PUSMEMORYDUMPABSOLUTE);
    setSubType(PUS_ST_TM_DMP_ABS);
}

void DC_PUSMemoryDumpAbsolute::update(void) {
    assert( memId!=0 );
    assert( isObjectConfigured() );
        
    unsigned int offset = 0;
    memcpy(data+offset,&memId,sizeof(TD_PUSMemId));
    offset = offset + sizeof(TD_PUSMemId);
    memcpy(data+offset,&numberBlocks,sizeof(TD_PUSNumberMemBlocks));
    offset = offset + sizeof(TD_PUSNumberMemBlocks);

    assert( numberBlocks<maxNumberBlocks );

    for (TD_PUSNumberMemBlocks i=0; i<numberBlocks; i++)  {
        memcpy(data+offset,&block[i].startAddress,sizeof(TD_PUSMemData*));
        offset = offset + sizeof(TD_PUSMemData*);
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
        assert(sizeof(unsigned short)==2);
    }
}