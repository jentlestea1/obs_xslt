//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// Telecommand.cpp
//
// Version	1.0
// Date		4.12.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "Telecommand.h"

Telecommand::Telecommand(void) {
    timeTag = -1;
    inUse = false;
}

bool Telecommand::isValid(void) {
    assert( isObjectConfigured() );
    return VALID;
}

TD_CheckCode Telecommand::getValidityCheckCode(void) const {
    return 0;
}

bool Telecommand::canExecute(void) {
    assert( isObjectConfigured() );
    return TC_CAN_EXECUTE;
}

TD_CheckCode Telecommand::getExecutionCheckCode(void) const {
    return 0;
}

TD_TelecommandId Telecommand::getTelecommandId(void) const {
    return getInstanceId();
}

void Telecommand::setTelecommandId(TD_TelecommandId tcId) {
    return;
}

TD_TelecommandType Telecommand::getType(void) const {
    return (TD_TelecommandType)(getClassId()%256);
}

void Telecommand::setType(TD_TelecommandType tcType) {
    return;
}

TD_TelecommandSubType Telecommand::getSubType(void) const {
    return 0;
}

void Telecommand::setSubType(TD_TelecommandSubType tcSubType) {
    return;
}

TD_TelecommandSource Telecommand::getSource(void) const {
    return 0;
}

void Telecommand::setSource(TD_TelecommandSource tcSource) {
    return;
}

TD_ObsTime Telecommand::getTimeTag(void) const {
    return timeTag;
}

void Telecommand::setTimeTag(TD_ObsTime timeTag) {
    this->timeTag = timeTag;
}

void Telecommand::setRawData(unsigned int i, unsigned char d) {
    assert( false );
    return;
}

void Telecommand::setRawData(unsigned char* d, unsigned int i) {
	assert( false );
	return;
}

unsigned int Telecommand::getNumberOfRawData(void) const {
    return 0;
}

void setRawData(unsigned char* d, unsigned int i) {
    assert(false);
    return;
}

void Telecommand::setInUse(bool newInUse) {
    inUse = newInUse;
}

bool Telecommand::isInUse(void) const {
    return inUse;
}

void Telecommand::setAcknowledgeLevel(TD_TelecommandAck ackLevel) {
    return;
}

TD_TelecommandAck Telecommand::getAcknowledgeLevel(void) const {
    return 0;
}

bool Telecommand::isObjectConfigured(void) {
   return (PunctualAction::isObjectConfigured() && timeTag>=0);
}

