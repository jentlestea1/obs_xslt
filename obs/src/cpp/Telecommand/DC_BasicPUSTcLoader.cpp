//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_BasicPUSTcLoader.cpp
//
// Version	1.0
// Date		4.01.04
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Event/DC_EventRepository.h"
#include "CC_TelecommandFactory.h"
#include "CC_TelecommandManager.h"
#include "DC_BasicPUSTcLoader.h"
#include "DC_PUSControlDataReporting.h"
#include "DC_PUSDefineDataReporting.h"

#include <string.h>

DC_BasicPUSTcLoader::DC_BasicPUSTcLoader(void) {
    setClassId(ID_BASICPUSTCLOADER);
    tcArea = pNULL;
    maxTcDataPacketLength = 0;
    maxNumberOfTc = 0;
}

void DC_BasicPUSTcLoader::activate(void) {
    assert( tcArea!=pNULL );
    assert( maxTcDataPacketLength>0 );
    assert( maxNumberOfTc>0 );

    CC_TelecommandFactory* pFct = CC_TelecommandFactory::getInstance();

    unsigned char* startTcPacket = tcArea+1;
    unsigned char numberOfTc = *(unsigned char*)tcArea;
    if (numberOfTc>maxNumberOfTc) {
        getEventRepository()->create(this,EVT_TOO_MANY_TC_PCKT);
        return;
    }

    for (unsigned char j=0; j<numberOfTc; j++) {

      assert(sizeof(TD_TelecommandType)==1);
      assert(sizeof(TD_TelecommandSubType)==1);

      unsigned short tcPacketID;
      unsigned short tcPacketSeqControl;
      unsigned short tcDataPacketLength;
      TD_TelecommandSource tcSource;

      memcpy(&tcPacketID,startTcPacket,2);
      memcpy(&tcPacketSeqControl,startTcPacket+2,2);
      memcpy(&tcDataPacketLength,startTcPacket+4,2);
      unsigned char tcAcknowledge = *(startTcPacket+6);
      TD_TelecommandType tcType = *(TD_TelecommandType*)(startTcPacket+7);
      TD_TelecommandSubType tcSubType = *(TD_TelecommandType*)(startTcPacket+8);
      memcpy(&tcSource,startTcPacket+9,sizeof(TD_TelecommandSource));

      unsigned short appDataLength = tcDataPacketLength-5-sizeof(TD_TelecommandSource);
      unsigned char* applicationDataStart = (startTcPacket+9+sizeof(TD_TelecommandSource));
      bool fastRawDataLoad = false;

      if (tcPacketID!=PUSTelecommand::getPacketId()) {
          startTcPacket = startTcPacket + tcDataPacketLength + 6;
          continue;
      }

      if (tcDataPacketLength>maxTcDataPacketLength) {
        getEventRepository()->create(this,EVT_TC_TOO_LONG);
        return;
      }
    
      PUSTelecommand* pTC = pNULL;

      if ( (tcType==PUS_TYPE_DATA_REP) && 
        ((tcSubType==PUS_ST_DATA_REP_NEW_HK)||(tcSubType==PUS_ST_DATA_REP_NEW_HK)) )  {
          pTC = pFct->allocatePUSDefineDataReporting(appDataLength);
       } else if ( (tcType==PUS_TYPE_DATA_REP) && 
        ((tcSubType==PUS_ST_DATA_REP_ENB_HK)||(tcSubType==PUS_ST_DATA_REP_ENB_DG)||
         (tcSubType==PUS_ST_DATA_REP_DIS_HK)||(tcSubType==PUS_ST_DATA_REP_DIS_HK)) ){
          unsigned char nsid = applicationDataStart[0];
          pTC = pFct->allocatePUSControlDataReporting(nsid);
          fastRawDataLoad = true;
       } else if ( tcType==PUS_TYPE_TEST ){
          pTC = pFct->allocateTestPUSTelecommand();
       } else {
          getEventRepository()->create(this,EVT_UNKNOWN_TC_TYPE);
          startTcPacket = startTcPacket + tcDataPacketLength + 6;
          continue;
       }

       if ( pTC==pNULL) {
          getEventRepository()->create(this,EVT_NO_TC_AVAIL);
          startTcPacket = startTcPacket + tcDataPacketLength + 6;
          continue;
       }

       pTC->setTelecommandId(tcPacketSeqControl);
       pTC->setType(tcType);
       pTC->setSubType(tcSubType);
       pTC->setSource(tcSource);
       pTC->setAcknowledgeLevel(tcAcknowledge);

       if (fastRawDataLoad) 
          pTC->setRawData(applicationDataStart,appDataLength);
       else
          for (unsigned int i=0; i<appDataLength; i++)
              pTC->setRawData(i,*(applicationDataStart+i));

       getTelecommandManager()->load(pTC);
       startTcPacket = startTcPacket + tcDataPacketLength + 6;
    }
}

void DC_BasicPUSTcLoader::release(Telecommand* pTc) {
    assert( tcArea!=pNULL );
    assert( maxTcDataPacketLength>0 );
    assert( maxNumberOfTc>0 );
    assert( pTc!=pNULL );
    pTc->setInUse(NOT_IN_USE);
}

void DC_BasicPUSTcLoader::setTcLoadAreaStart(unsigned char* startAddress) {
    assert( startAddress!=pNULL );
    tcArea = startAddress;
}

void DC_BasicPUSTcLoader::setMaxTcLength(unsigned int maxTcLength) {
    assert( maxTcLength>6);
    maxTcDataPacketLength = maxTcLength-6;
}

unsigned int DC_BasicPUSTcLoader::getMaxTcLength(void) const {
    return (maxTcDataPacketLength+6);
}

void DC_BasicPUSTcLoader::setMaxNumberOfTc(unsigned int max) {
    assert( max>0);
    maxNumberOfTc = max;
}

unsigned int DC_BasicPUSTcLoader::getMaxNumberOfTc(void) const {
    return maxNumberOfTc;
}

bool DC_BasicPUSTcLoader::isObjectConfigured(void) {
   // Check configuration of super object
   if ( !TelecommandLoader::isObjectConfigured() || 
        (tcArea==pNULL) || 
        (maxTcDataPacketLength==0) ||
        (maxNumberOfTc==0) )
       return NOT_CONFIGURED;

   return CONFIGURED;
}
