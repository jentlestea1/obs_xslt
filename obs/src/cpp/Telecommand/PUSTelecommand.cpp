//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// PUSTelecommand.cpp
//
// Version	1.0
// Date		4.12.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "PUSTelecommand.h"

TD_PUSPacketId PUSTelecommand::packetId = 0;

static const TD_TelecommandAck acceptanceAck = 1;
static const TD_TelecommandAck startAck = 2;
static const TD_TelecommandAck progressAck = 4;
static const TD_TelecommandAck completionAck = 8;

PUSTelecommand::PUSTelecommand(void) {
    tcId = 0;
    tcType = 0;
    tcSubType = 0;
    tcSource = 0;
    ackLevel = 0;       // all flags set to false
    validityCheckCode = 0;
}

bool PUSTelecommand::isValid(void) {
    return (validityCheckCode==0);
}

TD_CheckCode PUSTelecommand::getValidityCheckCode(void) const {
    return validityCheckCode;
}

void PUSTelecommand::setValidityCheckCode(TD_CheckCode c) {
    validityCheckCode = c;
}


TD_TelecommandId PUSTelecommand::getPacketId(void) {
    return packetId;
}

void PUSTelecommand::setApplicationId(TD_APID apid) {
    assert( apid < (TD_APID)2048 );
    packetId = 2048 + 4096;
    packetId = packetId + apid;
}

TD_TelecommandId PUSTelecommand::getTelecommandId(void) const {
    assert(tcId>0);
    return tcId;
}

void PUSTelecommand::setTelecommandId(TD_TelecommandId tcIdent) {
    assert(tcIdent>0);
    tcId = tcIdent;
}

TD_TelecommandType PUSTelecommand::getType(void) const {
    assert(tcType>0);
    return tcType;
}

void PUSTelecommand::setType(TD_TelecommandType tcTyp) {
    assert(tcTyp>0);
    tcType = tcTyp;
}

TD_TelecommandSubType PUSTelecommand::getSubType(void) const {
    assert(tcSubType>0);
    return tcSubType;
}

void PUSTelecommand::setSubType(TD_TelecommandSubType tcSubTyp) {
    assert(tcSubTyp>0);
    tcSubType = tcSubTyp;
}

TD_TelecommandSource PUSTelecommand::getSource() const {
    assert(tcSource>0);
    return tcSource;
}

void PUSTelecommand::setSource(TD_TelecommandSource tcSrc) {
    assert(tcSrc>0);
    tcSource = tcSrc;
}

void PUSTelecommand::setAcknowledgeLevel(TD_TelecommandAck ackLevel) {
    this->ackLevel = ackLevel;
}

TD_TelecommandAck PUSTelecommand::getAcknowledgeLevel(void) const {
    return ackLevel;
}

bool PUSTelecommand::isStartAckRequired(void) const {
    return ((ackLevel & startAck) > 0);
}

bool PUSTelecommand::isAcceptanceAckRequired(void) const {
    return ((ackLevel & acceptanceAck) > 0);
}

bool PUSTelecommand::isProgressAckRequired(void) const {
    return ((ackLevel & progressAck) > 0);
}

bool PUSTelecommand::isCompletionAckRequired(void) const {
    return ((ackLevel & completionAck) > 0);
}

bool PUSTelecommand::isObjectConfigured(void) {
   return (Telecommand::isObjectConfigured() &&
           (tcType>0) &&
           (tcSubType>0) &&
           (tcSource>0) &&
           (tcId>0) &&
           (packetId>0));
}

