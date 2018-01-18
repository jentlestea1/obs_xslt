//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyPUSTelemetryPacket.cpp
//
// Version	1.0
// Date		04.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Telecommand/PUSTelecommand.h"
#include "../Telemetry/PUSTelemetryPacket.h"
#include "../Telemetry/DC_PUSTcVerificationPacket.h"

#include <string.h>

DC_PUSTcVerificationPacket::DC_PUSTcVerificationPacket(void) {
    setClassId(ID_PUSTCVERIFICATIONPACKET);
    packetLengthSuccess = sizeof(TD_PUSPacketId)+sizeof(TD_TelecommandId);
    packetLengthFailure = sizeof(TD_PUSPacketId)+sizeof(TD_TelecommandId)+sizeof(TD_CheckCode);
    tmByte = new unsigned char[packetLengthFailure];
    setType(PUS_TYPE_TC_VER);

    // The PUS packet identifier, the telecommand identifier and the error
    // code are stored in the tmByte array

    // set the PUS packet identifier
    TD_PUSPacketId pidTemp = PUSTelecommand::getPacketId();
    memcpy(tmByte,&pidTemp,sizeof(TD_PUSPacketId));

    // initialize the telecommand identifier
    TD_TelecommandId tcidTemp = 0;
    memcpy(tmByte+sizeof(TD_PUSPacketId),&tcidTemp,sizeof(TD_TelecommandId));

    // initialize the error code
    TD_CheckCode ccTemp = 0;
    memcpy(tmByte+sizeof(TD_PUSPacketId)+sizeof(TD_TelecommandId),&ccTemp,sizeof(TD_CheckCode));
}

unsigned int DC_PUSTcVerificationPacket::getNumberOfBytes(void) {
    assert( getSubType()!=0 );

    TD_TelecommandSubType tcSubType = getSubType();
    if ( ( tcSubType == PUS_ST_TC_VER_ACC_SC) ||
         ( tcSubType == PUS_ST_TC_EXE_STR_SC) ||
         ( tcSubType == PUS_ST_TC_EXE_PRO_SC) ||
         ( tcSubType == PUS_ST_TC_EXE_END_SC) )
         return packetLengthSuccess;
    else
         return packetLengthFailure;
}

TD_CheckCode DC_PUSTcVerificationPacket::getErrorCode() {
    TD_CheckCode temp;
    memcpy(&temp,tmByte+sizeof(TD_PUSPacketId)+sizeof(TD_TelecommandId),sizeof(TD_CheckCode));
    return temp;
}

void DC_PUSTcVerificationPacket::setErrorCode(TD_CheckCode errCode) {
    assert( errCode>0 );
    memcpy(tmByte+sizeof(TD_PUSPacketId)+sizeof(TD_TelecommandId),&errCode,sizeof(TD_CheckCode));
}

TD_TelecommandId DC_PUSTcVerificationPacket::getTelecommandId() {
    TD_TelecommandId temp;
    memcpy(&temp,tmByte+sizeof(TD_PUSPacketId),sizeof(TD_TelecommandId));
    return temp;
}

void DC_PUSTcVerificationPacket::setTelecommandId(TD_TelecommandId tcId) {
    assert( tcId>0 );
    memcpy(tmByte+sizeof(TD_PUSPacketId),&tcId,sizeof(TD_TelecommandId));
}

void DC_PUSTcVerificationPacket::update(void) {
    return;
}

unsigned char DC_PUSTcVerificationPacket::getUnsignedByte(unsigned int n) {
    return tmByte[n];
}
