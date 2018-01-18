//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCasePUSFull.cpp
//
// Version	1.0
// Date		13.01.04
// Author	A. Pasetti (P&P Software)

#include "TestCasePUSFull.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../System/DC_DummyObsClock.h"
#include "../Event/DC_PUSEventRepository.h"
#include "../Data/DC_DummyDataPool.h"
#include "../Data/DC_DummyDatabase.h"
#include "../Manoeuvre/CC_ManoeuvreManager.h"
#include "../Telemetry/CC_TelemetryManager.h"
#include "../Telemetry/DC_PUSTelemetryModeManager.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"
#include "../Telemetry/DC_PUSTmLogger.h"
#include "../Telemetry/TelemetryPacket.h"
#include "../Telecommand/CC_TelecommandManager.h"
#include "../Telecommand/DC_BasicPUSTcLoader.h"
#include "../Telecommand/TelecommandLoader.h"
#include "../Telecommand/PUSTelecommand.h"

#include <string.h>
#include <assert.h>

bool TestCasePUSFull::firstActivation = true;

CC_TelemetryManager* TestCasePUSFull::pTmManager = pNULL;
DC_PUSTelemetryModeManager* TestCasePUSFull::pTmModeMan = pNULL;
CC_TelecommandManager* TestCasePUSFull::pTcManager = pNULL;
CC_ManoeuvreManager* TestCasePUSFull::pManManager = pNULL;
DC_PUSTmLogger* TestCasePUSFull::pTmLogger = pNULL;
DC_BasicPUSTcLoader* TestCasePUSFull::pTcLoader = pNULL;
DC_PUSEventRepository* TestCasePUSFull::pEvtRep = pNULL;
DC_DummyObsClock* TestCasePUSFull::pObsClock = pNULL;

unsigned char TestCasePUSFull::tcCommandArea[TC_COMMAND_AREA_MAX_N_TC*TC_COMMAND_AREA_MAX_TC_LEN];

TestCasePUSFull::TestCasePUSFull(int testId, char* testName):
     TestCaseWithFactories(testId,testName) {
     return;
}

bool TestCasePUSFull::setUpTestCase(void) {

   if (!TestCaseWithFactories::setUpTestCase()) 
       return INITIALIZATION_FAILURE;

   if (firstActivation) {

      // Create the components
      pTmManager = new CC_TelemetryManager();
      pTmModeMan = new DC_PUSTelemetryModeManager();
      pTcManager = new CC_TelecommandManager();
      pManManager = new CC_ManoeuvreManager();
      pTmLogger = new DC_PUSTmLogger();
      pTcLoader = new DC_BasicPUSTcLoader();
      pEvtRep = new DC_PUSEventRepository();
      pObsClock = new DC_DummyObsClock();

     // Configure the non-changeable part of the tc manager
     if ( pTcManager->isObjectConfigured() )
        return false;
     pTcManager->setPendingTelecommandListSize(TC_MAN_PEND_TC_LIST_SIZE);

     // Configure the non-changeable part of the tm mode manager
     if ( pTmModeMan->isObjectConfigured() )
        return false;
     pTmModeMan->setMaxNumberOfPackets(TM_MODE_MAN_MAX_N_PACKETS);

     // Configure the non-changeable part of the tm manager
     if ( pTmManager->isObjectConfigured() )
        return false;
     pTmManager->setImmediateQueueSize(TM_MAN_IMMEDIATE_QUEUE);

     // Configure the non-changeable part of the manoeuvre manager
     if ( pManManager->isObjectConfigured() )
        return false;
     pManManager->setPendingManoeuvreListSize(MAN_MAN_PENDING_MAN_LIST_SIZE);

     // Configure the non-changeable part of the tc loader
     if ( pTcLoader->isObjectConfigured() )
        return false;

     // Configure the non-changeable part of the tm stream
     if ( pTmLogger->isObjectConfigured() )
        return false;
     pTmLogger->setBufferCapacity(TM_LOGGER_BUFFER_CAPACITY);
     pTmLogger->setMaxPacketLength(TM_LOGGER_MAX_TM_LENGTH);
     if ( !pTmLogger->isObjectConfigured() )
         return false;

      // Configure the non-changeable part of the evt repository
      if ( pEvtRep->isObjectConfigured() )
        return false;
      pEvtRep->setRepositorySize(PUS_EVT_REP_SIZE);

     firstActivation = false;
   }

   // Configure the updatable part of the tc manager
   pTcManager->setObsClock(getObsClock());
   pTcManager->setTelecommandLoader(pTcLoader);
   if ( !pTcManager->isObjectConfigured() )
        return false;

   // Configure the updatable part of the tm mode manager
   pTmModeMan->reset();
   if ( !pTmModeMan->isObjectConfigured() )
        return false;

   // Configure the updatable part of the tm manager
   pTmManager->setTelemetryStream(pTmLogger);
   pTmManager->setTelemetryModeManager(pTmModeMan);
   if ( !pTmManager->isObjectConfigured() )
        return false;

   // Configure the updatable part of the manoeuvre manager
   if ( !pManManager->isObjectConfigured() )
        return false;

   // Configure the updatable part of the tc loader
   pTcLoader->setMaxNumberOfTc(TC_COMMAND_AREA_MAX_N_TC);
   pTcLoader->setMaxTcLength(TC_COMMAND_AREA_MAX_TC_LEN);
   pTcLoader->setTcLoadAreaStart(tcCommandArea);
   pTcLoader->setTelecommandManager(pTcManager);
   if ( !pTcLoader->isObjectConfigured() )
        return false;

    // Configure the updatable part of the evt repository
    pEvtRep->setObsClock(getObsClock());
    pEvtRep->setTelemetryManager(pTmManager);
    if ( !pEvtRep->isObjectConfigured() )
        return false;

    // Swap the event repository
    pOldEvtRep = CC_RootObject::getEventRepository();
    CC_RootObject::setEventRepository(pEvtRep);

    // Reset the telecommand load area
    resetCommandLoadArea();

    // Clear the mode manager of any packets that were loaded in previous tests  
    for (pTmModeMan->first(); !pTmModeMan->isIterationFinished(); pTmModeMan->next()) {
        TelemetryPacket* pTP = pTmModeMan->getIterationTelemetryPacket();

        if (pTP->getClassId()!=ID_PUSDATAREPORTINGPACKET)

            return INITIALIZATION_FAILURE;

        else

            pTmModeMan->unloadPacket( ((DC_PUSDataReportingPacket*)pTP)->getSID());

    }


    // Flush the functionality managers
    pTcManager->activate();
    pTmManager->activate();
    pTmManager->activate();

    return INITIALIZATION_SUCCESS;
}

bool TestCasePUSFull::shutDownTestCase(void) {
     
   // restore the event repository
   CC_RootObject::setEventRepository(pOldEvtRep);

   return SHUTDOWN_SUCCESS;
}

CC_TelecommandManager* TestCasePUSFull::getTelecommandManager(void) const {
    return pTcManager;
}

CC_TelemetryManager* TestCasePUSFull::getTelemetryManager(void) const {
    return pTmManager;
}

DC_PUSTelemetryModeManager* TestCasePUSFull::getTelemetryModeManager(void) const {
    return pTmModeMan;
}

CC_ManoeuvreManager* TestCasePUSFull::getManoeuvreManager(void) const {
   return pManManager;
}

DC_BasicPUSTcLoader* TestCasePUSFull::getTcLoader(void) const {
    return pTcLoader;
}

DC_PUSTmLogger* TestCasePUSFull::getTmStream(void) const {
    return pTmLogger;
}

DC_DummyObsClock* TestCasePUSFull::getObsClock(void) const {
    return pObsClock;
}

DC_PUSEventRepository* TestCasePUSFull::getEventRepository(void) const {
    return pEvtRep;
}

void TestCasePUSFull::resetCommandLoadArea(void) {
    tcCmdPos = 1;
    tcCommandArea[0] = 0;
}

void TestCasePUSFull::writeTcHeader(unsigned short length, unsigned short packetSeqControl) {
    TD_PUSPacketId id = PUSTelecommand::getPacketId();
    assert(sizeof(TD_PUSPacketId)==2);
    memcpy(tcCommandArea+tcCmdPos,&id,2);
    memcpy(tcCommandArea+tcCmdPos+2,&packetSeqControl,2);
    memcpy(tcCommandArea+tcCmdPos+4,&length,2);
    tcCmdPos = tcCmdPos+6;
}

bool TestCasePUSFull::writeTestPUSTelecommand(
                        unsigned char ackField, unsigned int execCounter, bool execCheckVal,
                        bool valCheckVal, TD_CheckCode execCheckCode,
                        TD_CheckCode valCheckCode, bool execOutcome,
                        unsigned short packetSeqControl) {

    // Check that TC packet fits in command load area
    unsigned short appDataLength = 6;
    unsigned short packetLength = 11+sizeof(TD_TelecommandSource)+appDataLength;
    if ( (tcCmdPos+packetLength)>TC_COMMAND_AREA_MAX_N_TC*TC_COMMAND_AREA_MAX_TC_LEN )
        return false;

    // Write TC packet header
    writeTcHeader(packetLength-6,packetSeqControl);

    // Write packet data field header
    *(unsigned char*)(tcCommandArea+tcCmdPos) = ackField;
    *(unsigned char*)(tcCommandArea+tcCmdPos+1) = PUS_TYPE_TEST;
    *(unsigned char*)(tcCommandArea+tcCmdPos+2) = PUS_ST_TC_TEST;
    TD_TelecommandSource tcSrc = DEF_PUS_TC_SOURCE;
    memcpy(tcCommandArea+tcCmdPos+3,&tcSrc,sizeof(TD_TelecommandSource));
    tcCmdPos = tcCmdPos+3+sizeof(TD_TelecommandSource);

    // Write application data
    *(unsigned char*)(tcCommandArea+tcCmdPos) = (unsigned char)execCounter;
    *(unsigned char*)(tcCommandArea+tcCmdPos+1) = execCheckVal;
    *(unsigned char*)(tcCommandArea+tcCmdPos+2) = valCheckVal;
    *(unsigned char*)(tcCommandArea+tcCmdPos+3) = (unsigned char)execCheckCode;
    *(unsigned char*)(tcCommandArea+tcCmdPos+4) = (unsigned char)valCheckCode;
    *(unsigned char*)(tcCommandArea+tcCmdPos+5) = execOutcome;
    tcCmdPos = tcCmdPos+6;

    // Write packet error control bytes
    *(unsigned char*)(tcCommandArea+tcCmdPos) = 0;
    *(unsigned char*)(tcCommandArea+tcCmdPos+1) = 0;
    tcCmdPos = tcCmdPos+2;

    return true;
}

bool TestCasePUSFull::writePUSDataReportingControl(
                unsigned char ackField, unsigned char NSID, TD_SID* sid,
                TD_TelecommandSubType tcSubType, unsigned short packetSeqControl) {

    // Check that TC packet fits in command load area
    unsigned short appDataLength = 1+NSID*sizeof(TD_SID);
    unsigned short packetLength = 11+sizeof(TD_TelecommandSource)+appDataLength;
    if ( (tcCmdPos+packetLength)>TC_COMMAND_AREA_MAX_N_TC*TC_COMMAND_AREA_MAX_TC_LEN )
        return false;

    // Write TC packet header
    writeTcHeader(packetLength-6,packetSeqControl);

    // Write packet data field header
    *(unsigned char*)(tcCommandArea+tcCmdPos) = ackField;
    *(unsigned char*)(tcCommandArea+tcCmdPos+1) = PUS_TYPE_DATA_REP;
    *(unsigned char*)(tcCommandArea+tcCmdPos+2) = tcSubType;
    TD_TelecommandSource tcSrc = DEF_PUS_TC_SOURCE;
    memcpy(tcCommandArea+tcCmdPos+3,&tcSrc,sizeof(TD_TelecommandSource));
    tcCmdPos = tcCmdPos+3+sizeof(TD_TelecommandSource);

    // Write application data
    *(unsigned char*)(tcCommandArea+tcCmdPos) = (unsigned char)NSID;
    tcCmdPos++;
    for (unsigned char i=0; i<NSID; i++) {
        memcpy(tcCommandArea+tcCmdPos,&sid[i],sizeof(TD_SID));
        tcCmdPos = tcCmdPos + sizeof(TD_SID);
    }

    // Write packet error control bytes
    *(unsigned char*)(tcCommandArea+tcCmdPos) = 0;
    *(unsigned char*)(tcCommandArea+tcCmdPos+1) = 0;
    tcCmdPos = tcCmdPos+2;

    return true;
}

bool TestCasePUSFull::writePUSDefineDataReporting(
                unsigned char ackField, TD_PUSCollectionInterval collectionInterval, TD_SID sid,
                TD_DataPoolId par, unsigned short packetSeqControl, TD_TelecommandSubType tcSubType) {

    // Check that TC packet fits in command load area
    unsigned short appDataLength = sizeof(TD_SID)+sizeof(TD_PUSCollectionInterval)+
                                 sizeof(TD_PUSNumberOfParameters)+sizeof(TD_DataPoolId);
    unsigned short packetLength = 11+sizeof(TD_TelecommandSource)+appDataLength;
    if ( (tcCmdPos+packetLength)>TC_COMMAND_AREA_MAX_N_TC*TC_COMMAND_AREA_MAX_TC_LEN )
        return false;

    // Write TC packet header
    writeTcHeader(packetLength-6,packetSeqControl);

    // Write packet data field header
    *(unsigned char*)(tcCommandArea+tcCmdPos) = ackField;
    *(unsigned char*)(tcCommandArea+tcCmdPos+1) = PUS_TYPE_DATA_REP;
    *(unsigned char*)(tcCommandArea+tcCmdPos+2) = tcSubType;
    TD_TelecommandSource tcSrc = DEF_PUS_TC_SOURCE;
    memcpy(tcCommandArea+tcCmdPos+3,&tcSrc,sizeof(TD_TelecommandSource));
    tcCmdPos = tcCmdPos+3+sizeof(TD_TelecommandSource);

    // Write application data
    memcpy(tcCommandArea+tcCmdPos,&sid,sizeof(TD_SID));
    tcCmdPos = tcCmdPos+sizeof(TD_SID);

    memcpy(tcCommandArea+tcCmdPos,&collectionInterval,sizeof(TD_PUSCollectionInterval));
    tcCmdPos = tcCmdPos+sizeof(TD_PUSCollectionInterval);

    TD_PUSNumberOfParameters npTemp = 1;
    memcpy(tcCommandArea+tcCmdPos,&npTemp,sizeof(TD_PUSNumberOfParameters));
    tcCmdPos = tcCmdPos+sizeof(TD_PUSNumberOfParameters);

    memcpy(tcCommandArea+tcCmdPos,&par,sizeof(TD_DataPoolId));
    tcCmdPos = tcCmdPos+sizeof(TD_DataPoolId);

    // Write packet error control bytes
    *(unsigned char*)(tcCommandArea+tcCmdPos) = 0;
    *(unsigned char*)(tcCommandArea+tcCmdPos+1) = 0;
    tcCmdPos = tcCmdPos+2;

    return true;
}

