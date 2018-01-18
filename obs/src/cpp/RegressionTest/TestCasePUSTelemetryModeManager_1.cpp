//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCasePUSTelemetryModeManager_1.cpp
//
// Version	1.0
// Date		04.01.04
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_PUSTelemetryModeManager.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Utilities/TestCaseWithFactories.h"
#include "TestCasePUSTelemetryModeManager_1.h"

#include <string.h>

TestCasePUSTelemetryModeManager_1::TestCasePUSTelemetryModeManager_1(void) :
	TestCasePUSFull(ID_PUSTELEMETRYMODEMANAGER*10+1,"TestCasePUSTelemetryModeManager_1") {
		return;
}

void TestCasePUSTelemetryModeManager_1::runTestCase(void) {

    // Retrieve the packet factory
    CC_TelemetryPacketFactory* pFct = CC_TelemetryPacketFactory::getInstance();

    // Allocate the two telemetry packets
    unsigned short defPacketSize = PUS_DRP_DEF_BUF_SIZE_SMALL-2;
    unsigned int valBufferSize = PUS_DRP_VAL_BUF_SIZE_SMALL-2;
    DC_PUSDataReportingPacket* pTMP_a = pFct->allocatePUSDataReportingPacket(defPacketSize,valBufferSize,0);
    DC_PUSDataReportingPacket* pTMP_b = pFct->allocatePUSDataReportingPacket(defPacketSize,valBufferSize,0);

    // Construct the packet
    TD_SID sid_a = 12;
    TD_SID sid_b = 13;
    TD_PUSCollectionInterval collectionInterval = 1;
    TD_PUSNumberOfParameters NPAR1 = 1;
    TD_DataPoolId par1 = 1;

    unsigned char* packet = new unsigned char[defPacketSize];
    unsigned int offset = 0;
    memcpy(packet+offset,&sid_a,sizeof(TD_SID));
    offset += sizeof(TD_SID);
    memcpy(packet+offset,&collectionInterval,sizeof(TD_PUSCollectionInterval));
    offset += sizeof(TD_PUSCollectionInterval);
    memcpy(packet+offset,&NPAR1,sizeof(TD_PUSNumberOfParameters));
    offset += sizeof(TD_PUSNumberOfParameters);
    memcpy(packet+offset,&par1,sizeof(TD_DataPoolId));
    offset += sizeof(TD_DataPoolId);

    // Configure the two packets and check that they are configured
    pTMP_a->setSubType(PUS_ST_DATA_REP_PAR_HK_REP);
    if ( !pTMP_a->isObjectConfigured() )
    {	setTestResult(TEST_FAILURE,"Wrong configuration status");
     	return;
    }
    pTMP_b->setSubType(PUS_ST_DATA_REP_PAR_HK_REP);
    if ( !pTMP_b->isObjectConfigured() )
    {	setTestResult(TEST_FAILURE,"Wrong configuration status");
     	return;
    }

    // Load the packet definitions for the first TM packet
    for (unsigned short j=0; j<offset; j++) 
        pTMP_a->setDefinitionBuffer(j,packet[j]);

    // Load the packet definitions for the second TM packet
    memcpy(packet,&sid_b,sizeof(TD_SID));
    for (unsigned short j=0; j<offset; j++) 
        pTMP_b->setDefinitionBuffer(j,packet[j]);

    // Retrieve the mode manager
    DC_PUSTelemetryModeManager* pMM = getTelemetryModeManager();

    // Check the value of the class identifier
    if ( pMM->getClassId() != ID_PUSTELEMETRYMODEMANAGER )
    {    setTestResult(TEST_FAILURE, "Wrong class identifier");
         return;
    }

    // Check that the number of packets is correct
    if ( pMM->getMaxNumberOfPackets()!=TM_MODE_MAN_MAX_N_PACKETS )
    {    setTestResult(TEST_FAILURE, "Wrong max number of TM packets");
         return;
    }

    // Terminate configuration of mode manager and check configuration status
    pMM->reset();
    if ( !pMM->isObjectConfigured() )
    {    setTestResult(TEST_FAILURE, "Wrong configuration status");
         return;
    }
    
    // Load packets and check success
    pMM->loadPacket(pTMP_a);
    pMM->loadPacket(pTMP_b);
    if ( pMM->getNumberOfPackets()!=2 )
    {    setTestResult(TEST_FAILURE, "Wrong number of packets");
         return;
    }

    // Load the packet SID_B till the mode manager is full
    for (unsigned int j=2; j<TM_MODE_MAN_MAX_N_PACKETS; j++)
        pMM->loadPacket(pTMP_b);

    // Check that mode manager is full
    if ( !pMM->isFull() )
    {    setTestResult(TEST_FAILURE, "Wrong full status");
         return;
    }

    // Attempt to load a further packet and check failure
    unsigned int nEvt = getNumberOfEvents();
    pMM->loadPacket(pTMP_a);
    if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_MM) )
        return;

    // Unload all SID_B packets but one
    for (unsigned int j=2; j<TM_MODE_MAN_MAX_N_PACKETS; j++)
        pMM->unloadPacket(sid_b);

    // Check iterator
    DC_PUSDataReportingPacket* pItem;
    unsigned int i=0;
    bool sid_a_found=false;
    bool sid_b_found=false;
    for (pMM->first(); !pMM->isIterationFinished(); pMM->next()) {
        pItem=(DC_PUSDataReportingPacket*)pMM->getIterationTelemetryPacket();
        i++;

        if ( pItem->getSID()==pTMP_a->getSID() && !sid_a_found ) {
            sid_a_found = true;
            continue;
        }

        if ( pItem->getSID()==pTMP_b->getSID() && !sid_b_found ) {
            sid_b_found = true;
            continue;
        }

        setTestResult(TEST_FAILURE, "Wrong iteration number");
        return;
    }
    if (!sid_a_found || !sid_b_found || (i!=2) )
    {    setTestResult(TEST_FAILURE, "Wrong iteration number");
         return;
    }
    
    // Check packet presence 
    if ( !pMM->isSIDLoaded(pTMP_a->getSID()) )
    {    setTestResult(TEST_FAILURE, "Wrong presence check result");
         return;
    }
    if ( pMM->isSIDLoaded(pTMP_a->getSID()+2) )
    {    setTestResult(TEST_FAILURE, "Wrong presence check result");
         return;
    }

    // Unload packet and check success
    pMM->unloadPacket(pTMP_b->getSID());
    if ( pMM->getNumberOfPackets()!=1 )
    {    setTestResult(TEST_FAILURE, "Wrong number of packets");
         return;
    }
    if ( pMM->isFull() )
    {    setTestResult(TEST_FAILURE, "Wrong full status");
         return;
    }

    // Attempt to unload non-existent packet and check failure
    nEvt = getNumberOfEvents();
    pMM->unloadPacket(sid_b+2);
    if ( !verifyLatestEvent(nEvt+1,EVT_SID_NOT_FOUND) )
        return;
      
    // Check iterator
    i = 0;
    sid_a_found=false;
    for (pMM->first(); !pMM->isIterationFinished(); pMM->next()) {
        pItem=(DC_PUSDataReportingPacket*)pMM->getIterationTelemetryPacket();
        i++;

        if ( pItem->getSID()==pTMP_a->getSID() && !sid_a_found ) {
            sid_a_found = true;
            continue;
        }

        setTestResult(TEST_FAILURE, "Wrong iteration number");
        return;
    }
    if (!sid_a_found || (i!=1) )
    {    setTestResult(TEST_FAILURE, "Wrong iteration number");
         return;
    }

    // Reload packet SID_B and unload packet SID_A and check success
    pMM->loadPacket(pTMP_b);
    pMM->unloadPacket(pTMP_a->getSID());
    if ( pMM->getNumberOfPackets()!=1 )
    {    setTestResult(TEST_FAILURE, "Wrong number of packets");
         return;
    }
    if ( pMM->isFull() )
    {    setTestResult(TEST_FAILURE, "Wrong full status");
         return;
    }

    // Check iterator
    i = 0;
    sid_b_found=false;
    for (pMM->first(); !pMM->isIterationFinished(); pMM->next()) {
        pItem=(DC_PUSDataReportingPacket*)pMM->getIterationTelemetryPacket();
        i++;

        if ( pItem->getSID()==pTMP_b->getSID() && !sid_b_found ) {
            sid_b_found = true;
            continue;
        }

        setTestResult(TEST_FAILURE, "Wrong iteration number");
        return;
    }
    if (!sid_b_found || (i!=1) )
    {    setTestResult(TEST_FAILURE, "Wrong iteration number");
         return;
    }   
    
    // Unload the last remaining packet and check success
    pMM->unloadPacket(pTMP_b->getSID());
    if ( pMM->getNumberOfPackets()!=0 )
    {    setTestResult(TEST_FAILURE, "Wrong number of packets");
         return;
    }
    if ( pMM->isFull() )
    {    setTestResult(TEST_FAILURE, "Wrong full status");
         return;
    }

    // Check iterator
    bool flag = false;
    for (pMM->first(); !pMM->isIterationFinished(); pMM->next()) {
        flag = true;
    }
    if (flag)
    {   setTestResult(TEST_FAILURE, "Wrong iteration number");
        return;
    }
  
    setTestResult(TEST_SUCCESS,"Test Successful");
    return;
}
