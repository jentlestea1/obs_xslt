//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSEventRepository.cpp
//
// Version	1.0
// Date	    13.11.03 (version 1.0)
// Author	A. Pasetti (P&P Software)
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../System/ObsClock.h"
#include "../Telecommand/PUSTelecommand.h"
#include "../Telemetry/DC_PUSTcVerificationPacket.h"
#include "../Telemetry/CC_TelemetryManager.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Manoeuvre/PUSTcManoeuvre.h"
#include "DC_EventRepository.h"
#include "DC_PUSEventRepository.h"

DC_PUSEventRepository::DC_PUSEventRepository(void) {
    setClassId(ID_PUSEVENTREPOSITORY);
}

void DC_PUSEventRepository::create(PUSTelecommand* originator, TD_EventType eventId) {
    assert( originator!=pNULL);
    assert( eventId>0 );

    // Only process event if event creation is enabled
    if (!isEnabled() || !isEnabled(eventId))
        return;

    DC_PUSTcVerificationPacket* pTcVerificationPacket;
    pTcVerificationPacket = CC_TelemetryPacketFactory::getInstance()->allocatePUSTcVerificationPacket();
    if ( pTcVerificationPacket==pNULL ) {
        DC_EventRepository::create((CC_RootObject*)originator,EVT_TM_PCK_ALLOC_FAILURE);
        DC_EventRepository::create((CC_RootObject*)originator,eventId);
        return;
    }

    TD_CheckCode errCode = 0;

    switch (eventId) {

        case EVT_TC_LOADED:       // telecommand acceptance -- success
            if ( originator->isAcceptanceAckRequired() ) {
                pTcVerificationPacket->setTelecommandId(originator->getTelecommandId());
                pTcVerificationPacket->setSubType(PUS_ST_TC_VER_ACC_SC);
                pTcVerificationPacket->setTimeTag(DC_PUSTcVerificationPacket::getObsClock()->getTime());
                pTmManager->sendTelemetryPacket(pTcVerificationPacket);
            } else
                pTcVerificationPacket->setInUse(NOT_IN_USE);
            break;

        case EVT_TC_NOT_VALID:       // telecommand acceptance -- failure
            pTcVerificationPacket->setTelecommandId(originator->getTelecommandId());
            pTcVerificationPacket->setSubType(PUS_ST_TC_VER_ACC_FL);
            pTcVerificationPacket->setTimeTag(DC_PUSTcVerificationPacket::getObsClock()->getTime());
            errCode = originator->getValidityCheckCode();
            if (errCode!=0)
                pTcVerificationPacket->setErrorCode(errCode);
            else
                pTcVerificationPacket->setErrorCode(EVT_TC_NOT_VALID);
            pTmManager->sendTelemetryPacket(pTcVerificationPacket);
            break;

        case EVT_TC_LIST_FULL:       // telecommand acceptance -- failure
            pTcVerificationPacket->setTelecommandId(originator->getTelecommandId());
            pTcVerificationPacket->setSubType(PUS_ST_TC_VER_ACC_FL);
            pTcVerificationPacket->setErrorCode(EVT_TC_LIST_FULL);
            pTcVerificationPacket->setTimeTag(DC_PUSTcVerificationPacket::getObsClock()->getTime());
            pTmManager->sendTelemetryPacket(pTcVerificationPacket);
            break;

        case EVT_TC_EXEC_CHECK_FAIL:       // telecommand execution start -- failure
            pTcVerificationPacket->setTelecommandId(originator->getTelecommandId());
            pTcVerificationPacket->setSubType(PUS_ST_TC_EXE_STR_FL);
            pTcVerificationPacket->setTimeTag(DC_PUSTcVerificationPacket::getObsClock()->getTime());
            errCode = originator->getExecutionCheckCode();
            if (errCode!=0)
                pTcVerificationPacket->setErrorCode(errCode);
            else
                pTcVerificationPacket->setErrorCode(EVT_TC_EXEC_CHECK_FAIL);
            pTmManager->sendTelemetryPacket(pTcVerificationPacket);
            break;

        case EVT_TC_ABORTED:       // telecommand execution start -- failure
            pTcVerificationPacket->setTelecommandId(originator->getTelecommandId());
            pTcVerificationPacket->setSubType(PUS_ST_TC_EXE_STR_FL);
            pTcVerificationPacket->setErrorCode(EVT_TC_ABORTED);
            pTcVerificationPacket->setTimeTag(DC_PUSTcVerificationPacket::getObsClock()->getTime());
            pTmManager->sendTelemetryPacket(pTcVerificationPacket);
            break;

        case EVT_TC_EXEC_FAIL:       // telecommand completion -- failure
            pTcVerificationPacket->setTelecommandId(originator->getTelecommandId());
            pTcVerificationPacket->setSubType(PUS_ST_TC_EXE_END_FL);
            pTcVerificationPacket->setTimeTag(DC_PUSTcVerificationPacket::getObsClock()->getTime());
            errCode = (TD_CheckCode)originator->getLastOutcome();
            pTcVerificationPacket->setErrorCode(errCode);
            pTmManager->sendTelemetryPacket(pTcVerificationPacket);
            break;

        case EVT_TC_EXEC_SUCC:       // telecommand completion -- success
            if ( originator->isCompletionAckRequired() ) {
                pTcVerificationPacket->setTelecommandId(originator->getTelecommandId());
                pTcVerificationPacket->setSubType(PUS_ST_TC_EXE_END_SC);
                pTcVerificationPacket->setTimeTag(DC_PUSTcVerificationPacket::getObsClock()->getTime());
                pTmManager->sendTelemetryPacket(pTcVerificationPacket);
            } else
                pTcVerificationPacket->setInUse(NOT_IN_USE);
            break;

        default:
            assert(false);  // should never be reached
    }
    DC_EventRepository::create((CC_RootObject*)originator,eventId);
}

void DC_PUSEventRepository::create(PUSTcManoeuvre* originator, TD_EventType eventId) {
    assert( originator!=pNULL);
    assert( eventId>0 );

    TD_CheckCode errCode = 0;

    // Only process event if event creation is enabled
    if (!isEnabled() || !isEnabled(eventId))
        return;

    DC_PUSTcVerificationPacket* pTcVerificationPacket;
    pTcVerificationPacket = CC_TelemetryPacketFactory::getInstance()->allocatePUSTcVerificationPacket();
    if ( pTcVerificationPacket==pNULL ) {
        DC_EventRepository::create((CC_RootObject*)originator,EVT_TM_PCK_ALLOC_FAILURE);
        DC_EventRepository::create((CC_RootObject*)originator,eventId);
        return;
    }

    switch (eventId) {

        case EVT_MAN_STARTED:       // telecommand execution start -- success
            if ( originator->isStartAckRequired() ) {
                pTcVerificationPacket->setTelecommandId(originator->getTelecommandId());
                pTcVerificationPacket->setSubType(PUS_ST_TC_EXE_STR_SC);
                pTcVerificationPacket->setTimeTag(DC_PUSTcVerificationPacket::getObsClock()->getTime());
                pTmManager->sendTelemetryPacket(pTcVerificationPacket);
            } else
                pTcVerificationPacket->setInUse(NOT_IN_USE);
            break;

        case EVT_MAN_LIST_FULL:       // telecommand execution start -- failure
            pTcVerificationPacket->setTelecommandId(originator->getTelecommandId());
            pTcVerificationPacket->setSubType(PUS_ST_TC_EXE_STR_FL);
            pTcVerificationPacket->setErrorCode(EVT_MAN_LIST_FULL);
            pTcVerificationPacket->setTimeTag(DC_PUSTcVerificationPacket::getObsClock()->getTime());
            pTmManager->sendTelemetryPacket(pTcVerificationPacket);
            break;

        case EVT_MAN_PROGRESS:       // telecommand execution progress -- success
            if ( originator->isProgressAckRequired() ) {
                pTcVerificationPacket->setTelecommandId(originator->getTelecommandId());
                pTcVerificationPacket->setSubType(PUS_ST_TC_EXE_PRO_SC);
                pTcVerificationPacket->setTimeTag(DC_PUSTcVerificationPacket::getObsClock()->getTime());
                pTmManager->sendTelemetryPacket(pTcVerificationPacket);
            } else
                pTcVerificationPacket->setInUse(NOT_IN_USE);
            break;

        case EVT_MAN_ABORTED:       // telecommand execution progress -- failure
            pTcVerificationPacket->setTelecommandId(originator->getTelecommandId());
            pTcVerificationPacket->setSubType(PUS_ST_TC_EXE_PRO_FL);
            pTcVerificationPacket->setTimeTag(DC_PUSTcVerificationPacket::getObsClock()->getTime());
            errCode = originator->getContinuationCheckCode();
            if (errCode!=0)
                pTcVerificationPacket->setErrorCode(errCode);
            else
                pTcVerificationPacket->setErrorCode(EVT_MAN_ABORTED);
            pTmManager->sendTelemetryPacket(pTcVerificationPacket);
            break;

        case EVT_MAN_TERMINATED:       // telecommand execution completion -- success
            if ( originator->isCompletionAckRequired() ) {
                pTcVerificationPacket->setTelecommandId(originator->getTelecommandId());
                pTcVerificationPacket->setSubType(PUS_ST_TC_EXE_END_SC);
                pTcVerificationPacket->setTimeTag(DC_PUSTcVerificationPacket::getObsClock()->getTime());
                pTmManager->sendTelemetryPacket(pTcVerificationPacket);
            } else
                pTcVerificationPacket->setInUse(NOT_IN_USE);
            break;

        default:
            assert(false);  // should never be reached
    }
    DC_EventRepository::create((CC_RootObject*)originator,eventId);
}

void DC_PUSEventRepository::create(CC_RootObject* originator, TD_EventType eventId) {
    DC_EventRepository::create(originator, eventId);
}

void DC_PUSEventRepository::setTelemetryManager(CC_TelemetryManager* pTmMng) {
    assert( pTmMng!=pNULL );
    pTmManager = pTmMng;
}

CC_TelemetryManager* DC_PUSEventRepository::getTelemetryManager() const {
    assert( pTmManager!=pNULL );
    return pTmManager;
}

bool DC_PUSEventRepository::isObjectConfigured(void) {
   return (DC_EventRepository::isObjectConfigured() && pTmManager!=pNULL);
}

