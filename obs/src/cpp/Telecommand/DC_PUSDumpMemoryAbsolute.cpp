//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSDumpMemoryAbsolute.cpp
//
// Version	1.0
// Date		4.01.04
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_PUSDumpMemoryAbsolute.h"
#include "../Telemetry/CC_TelemetryManager.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Telemetry/DC_PUSMemoryDumpOffset.h"
#include "../Telemetry/DC_PUSMemoryDumpAbsolute.h"
#include "../Data/DataPool.h"

#include <string.h>

DC_PUSDumpMemoryAbsolute::DC_PUSDumpMemoryAbsolute(void) {
    setClassId(ID_PUSDUMPMEMORYABSOLUTE);
    setSubType(PUS_ST_TC_DMP_ABS);
}

TD_ActionOutcome DC_PUSDumpMemoryAbsolute::doAction(void) {
    assert( isObjectConfigured() );

    CC_TelemetryPacketFactory* pFct = CC_TelemetryPacketFactory::getInstance();
    unsigned int offset;

    // recover the number of blocks
    offset = sizeof(TD_PUSMemId)+sizeof(TD_PUSMemData*);
    TD_PUSNumberMemBlocks numberBlocks;
    memcpy(&numberBlocks,data+offset,sizeof(TD_PUSNumberMemBlocks));

    // compute the length of the fixed part of the telemetry packet
    unsigned int fixedLength;
    fixedLength = sizeof(TD_PUSMemId)+sizeof(TD_PUSNumberMemBlocks);
    
    // compute the length of the data part of the telemetry packet
    unsigned int t = fixedLength+sizeof(TD_PUSMemData*);
    unsigned int dataLength = 0;
    for (TD_PUSNumberMemBlocks i=0; i<numberBlocks; i++) {
        TD_PUSMemLength blockLength;
        memcpy(&blockLength,data+t,sizeof(TD_PUSMemLength));
        dataLength = dataLength+blockLength;
        t = t+sizeof(TD_PUSMemData*);
    }

    // compute the total length of the telemery packet
    unsigned int packetLength = fixedLength+dataLength+
                             numberBlocks*(sizeof(TD_PUSMemData*)+sizeof(TD_PUSMemLength)+sizeof(unsigned short));

    // performa a consistency check: the number of blocks must be consistent with the
    // length of the application data
    if ( numberData!=(fixedLength+numberBlocks*(sizeof(TD_PUSMemData*)+sizeof(TD_PUSMemLength))) )
        return APP_DATA_INCONSISTENT;

    // recover the telemetry packet from the telemetry factory
    DC_PUSMemoryDumpOffset* pPck = pFct->allocatePUSMemoryDumpOffset(numberBlocks,packetLength);
    if ( pPck==pNULL )
        return PACKET_NOT_FOUND;

    //configure the telemetry packet
    pPck->setNumberBlocks(numberBlocks);
    offset = sizeof(TD_PUSMemId)+sizeof(TD_PUSMemData*)+sizeof(TD_PUSNumberMemBlocks);
    for (TD_PUSNumberMemBlocks i=0; i<numberBlocks; i++) {
        TD_PUSMemData* startAddress;
        memcpy(&startAddress,data+offset,sizeof(TD_PUSMemData*));
        offset = offset + sizeof(TD_PUSMemData*);
        TD_PUSMemLength blockLength;
        memcpy(&blockLength,data+offset,sizeof(TD_PUSMemLength));
        offset = offset + sizeof(TD_PUSMemLength);
        pPck->defineBlock(i,startAddress,blockLength);
    }

    // Load the telemetry packet in the telemetry manager
    if ( !pTmManager->isImmediateQueueFull() ) {
        pPck->setInUse(NOT_IN_USE);    
        return TM_MAN_QUEUE_FULL;
    } else
        pTmManager->sendTelemetryPacket(pPck);
    
    return ACTION_SUCCESS;
}

