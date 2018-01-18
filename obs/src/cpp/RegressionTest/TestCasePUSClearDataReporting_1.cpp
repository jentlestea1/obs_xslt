//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCasePUSClearDataReporting_1.cpp
//
// Version	1.0
// Date		04.01.04
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telecommand/DC_PUSClearDataReporting.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Telemetry/DC_PUSTelemetryModeManager.h"
#include "../Data/DC_SampleFullDataPool.h"
#include "../Utilities/TestCasePUSFull.h"
#include "TestCasePUSClearDataReporting_1.h"

#include <assert.h>
#include <string.h>

TestCasePUSClearDataReporting_1::TestCasePUSClearDataReporting_1(void) :
	TestCasePUSFull(ID_PUSCLEARDATAREPORTING*10+1,"TestCasePUSClearDataReporting_1") {
		return;
}

void TestCasePUSClearDataReporting_1::runTestCase(void) {

    // Recover the packet factory
    CC_TelemetryPacketFactory* pFct = CC_TelemetryPacketFactory::getInstance();

    // Recover the PUS telemetry mode manager 
    DC_PUSTelemetryModeManager* pTMM = getTelemetryModeManager();

    // Allocate the two telemetry packets
    unsigned short defPacketSize = PUS_DRP_DEF_BUF_SIZE_SMALL-2;
    unsigned int valBufferSize = PUS_DRP_VAL_BUF_SIZE_SMALL-2;
    DC_PUSDataReportingPacket* pTMP_a = pFct->allocatePUSDataReportingPacket(defPacketSize,valBufferSize,0);
    DC_PUSDataReportingPacket* pTMP_b = pFct->allocatePUSDataReportingPacket(defPacketSize,valBufferSize,0);
    if ( (pTMP_a==pNULL) || (pTMP_b==pNULL) )
    {	setTestResult(TEST_FAILURE,"Failure to allocate telemetry packets");
     	return;
    }

    // Construct the packet
    TD_SID sid_a = 121;
    TD_SID sid_b = 131;
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

    assert(offset<defPacketSize);

    // Configure the two packets and check that they are configured
    pTMP_a->setSubType(PUS_ST_DATA_REP_PAR_HK_REP);
    pTMP_a->setTimeTag(0);
    if ( !pTMP_a->isObjectConfigured() )
    {	setTestResult(TEST_FAILURE,"Wrong configuration status");
     	return;
    }
    pTMP_b->setSubType(PUS_ST_DATA_REP_PAR_HK_REP);
    pTMP_b->setTimeTag(0);
    if ( !pTMP_b->isObjectConfigured() )
    {	setTestResult(TEST_FAILURE,"Wrong configuration status");
     	return;
    }

    // Load the packet definitions for the first TM packet
    for (unsigned short i=0; i<offset; i++) 
        pTMP_a->setDefinitionBuffer(i,packet[i]);

    // Load the packet definitions for the second TM packet
    memcpy(packet,&sid_b,sizeof(TD_SID));
    for (unsigned short i=0; i<offset; i++) 
        pTMP_b->setDefinitionBuffer(i,packet[i]);

    // Load the second packet in the TM mode manager and check success
    pTMM->loadPacket(pTMP_b);
    if ( !pTMM->isSIDLoaded(sid_b) )
    {    setTestResult(TEST_FAILURE, "TM packet is not loaded");
         return;
    }

    // Create the telecommand 
    DC_PUSClearDataReporting* pTC = new DC_PUSClearDataReporting();

    // Check the value of the class identifier
    if ( pTC->getClassId() != ID_PUSCLEARDATAREPORTING )
    {    setTestResult(TEST_FAILURE, "Wrong class identifier");
         return;
    }

    // Check configuration status
    if ( pTC->isObjectConfigured() )
    {    setTestResult(TEST_FAILURE, "Wrong configuration status");
         return;
    }
    
    // Set the maximum number of SIDs and check success
    pTC->setMaxNumberSID(2);            // Check this in test case for control data reporting
    if ( pTC->getNumberOfRawData()!=(2*sizeof(TD_SID)+1) )
    {    setTestResult(TEST_FAILURE, "Wrong configuration value");
         return;
    }

    // Load TM mode manager and check success
    pTC->setPUSTelemetryModeManager(pTMM);
    if ( pTC->getPUSTelemetryModeManager()!=pTMM )
    {    setTestResult(TEST_FAILURE, "Wrong configuration value");
         return;
    }

    // Complete configuration of telecommand and check configuration status
    TD_TelecommandSource tcSource = 1;
    TD_TelecommandId tcId = 2;
    pTC->setSource(tcSource);
    pTC->setSubType(PUS_ST_DATA_REP_CLR_HK);
    pTC->setTelecommandId(tcId);
    pTC->setTimeTag(0);
    if ( !pTC->isObjectConfigured() )
    {    setTestResult(TEST_FAILURE, "Wrong configuration status");
         return;
    }
    
    // set up data structures to hold telecommand raw data
    unsigned int maxNSID = 2;
    TD_SID* temp = new TD_SID[maxNSID+1];
    TD_SID* sid = &temp[1];
    unsigned char* rawData = ((unsigned char*)sid)-1;

    // Load raw data in telecommandand 
    rawData[0]=2;
    sid[0]=sid_a;
    sid[1]=sid_b;
    for (unsigned int i=0; i<(1+2*sizeof(TD_SID)); i++)
        pTC->setRawData(i,rawData[i]);

    // Check validity
    if ( !pTC->isValid() )
    {    setTestResult(TEST_FAILURE, "Wrong validity status");
         return;
    }

    // Execute telecommand and check success
    if ( !pTMP_a->isInUse() )
    {    setTestResult(TEST_FAILURE, "Wrong enable status");
         return;
    }
    if ( !pTMP_b->isInUse() )
    {    setTestResult(TEST_FAILURE, "Wrong enable status");
         return;
    }
    if ( !pTMM->isSIDLoaded(sid_b) )
    {    setTestResult(TEST_FAILURE, "Wrong load status");
         return;
    }

    TD_ActionOutcome ao = pTC->execute();
    if ( ao!=ACTION_SUCCESS )
    {    setTestResult(TEST_FAILURE, "Wrong action outcome");
         return;
    }
    if ( pTMP_a->isInUse() )
    {    setTestResult(TEST_FAILURE, "Wrong enable status");
         return;
    }
    if ( pTMP_b->isInUse() )
    {    setTestResult(TEST_FAILURE, "Wrong enable status");
         return;
    }
    if ( pTMM->isSIDLoaded(sid_b) )
    {    setTestResult(TEST_FAILURE, "Wrong enable status");
         return;
    }
    
    // Execute telecommand again and check that now it fails
    ao = pTC->execute();
    if ( ao!=ACTION_FAILURE )
    {    setTestResult(TEST_FAILURE, "Wrong action outcome");
         return;
    }

    // Try to load too many SIDs and check validity 
    rawData[0]=3;
    sid[0]=sid_a;
    sid[1]=sid_b;
    for (unsigned int i=0; i<(1+2*sizeof(TD_SID)); i++)
        pTC->setRawData(i,rawData[i]);

    // Check validity
    if ( pTC->isValid() || pTC->getValidityCheckCode()!=VC_TOO_MANY_SIDS )
    {    setTestResult(TEST_FAILURE, "Wrong validity status");
         return;
    }

    // Try to load too many raw data and check validity 
    if (isNonNominalCheckAllowed()) {
      rawData[0]=2;
        sid[0]=sid_a;
        sid[1]=sid_b;
        for (unsigned int i=0; i<(2+2*sizeof(TD_SID)); i++)
            pTC->setRawData(i,rawData[i]);

        // Check validity
        if ( pTC->isValid() || pTC->getValidityCheckCode()!=VC_TOO_MANY_RAW_DATA )
        {    setTestResult(TEST_FAILURE, "Wrong validity status");
             return;
        }
    }

    // Try to load an inconsistent number of raw data and check validity 
    rawData[0]=2;
    sid[0]=sid_a;
    sid[1]=sid_b;
    for (unsigned int i=0; i<(2*sizeof(TD_SID)); i++)
        pTC->setRawData(i,rawData[i]);

    // Check validity
    if ( pTC->isValid() || pTC->getValidityCheckCode()!=VC_INCONSISTENT_RAW_DATA )
    {    setTestResult(TEST_FAILURE, "Wrong validity status");
         return;
    }

    setTestResult(TEST_SUCCESS,"Test Successful");
    return;
}
