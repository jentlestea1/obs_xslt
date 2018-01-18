//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCasePUSControlDataReporting_1.cpp
//
// Version	1.0
// Date		04.01.04
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telecommand/DC_PUSControlDataReporting.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Data/DC_SampleFullDataPool.h"
#include "../Utilities/TestCaseWithFactories.h"
#include "TestCasePUSControlDataReporting_1.h"

#include <assert.h>
#include <string.h>

TestCasePUSControlDataReporting_1::TestCasePUSControlDataReporting_1(void) :
	TestCaseWithFactories(ID_PUSCONTROLDATAREPORTING*10+1,"TestCasePUSControlDataReporting_1") {
		return;
}

void TestCasePUSControlDataReporting_1::runTestCase(void) {

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

    // Create the telecommand 
    DC_PUSControlDataReporting* pTC = new DC_PUSControlDataReporting();

    // Check the value of the class identifier
    if ( pTC->getClassId() != ID_PUSCONTROLDATAREPORTING )
    {    setTestResult(TEST_FAILURE, "Wrong class identifier");
         return;
    }

    // Check configuration status
    if ( pTC->isObjectConfigured() )
    {    setTestResult(TEST_FAILURE, "Wrong configuration status");
         return;
    }
    
    // Set the number of SIDs and check success
    pTC->setMaxNumberSID(2);
    if ( pTC->getNumberOfRawData()!=(2*sizeof(TD_SID)+1) )
    {    setTestResult(TEST_FAILURE, "Wrong configuration value");
         return;
    }

    // Complete configuration of telecommand and check configuration status
    TD_TelecommandSource tcSource = 1;
    TD_TelecommandId tcId = 2;
    pTC->setSource(tcSource);
    pTC->setSubType(PUS_ST_DATA_REP_ENB_HK);
    pTC->setTelecommandId(tcId);
    pTC->setTimeTag(0);
    if ( !pTC->isObjectConfigured() )
    {    setTestResult(TEST_FAILURE, "Wrong configuration status");
         return;
    }
    
    // set up data structures to hold telecommand raw data
    unsigned int maxNSID = 3;
    TD_SID* temp = new TD_SID[maxNSID+1];
    TD_SID* sid = &temp[1];
    unsigned char* rawData = ((unsigned char*)sid)-1;

    // Load raw data in telecommandand 
    rawData[0]=1;
    sid[0]=sid_a;
    for (unsigned int i=0; i<(1+1*sizeof(TD_SID)); i++)
        pTC->setRawData(i,rawData[i]);
    pTC->setSubType(PUS_ST_DATA_REP_ENB_HK);

    // Check validity
    if ( !pTC->isValid() )
    {    setTestResult(TEST_FAILURE, "Wrong validity status");
         return;
    }

    // Execute telecommand and check success
    TD_ActionOutcome ao = pTC->execute();
    if ( ao!=ACTION_SUCCESS )
    {    setTestResult(TEST_FAILURE, "Wrong action outcome");
         return;
    }
    if ( !pTMP_a->isEnabled() )
    {    setTestResult(TEST_FAILURE, "Wrong enable status");
         return;
    }
    
    // Load raw data in telecommandand and configure telecommand
    rawData[0]=1;
    sid[0]=sid_a;
    for (unsigned int i=0; i<(1+1*sizeof(TD_SID)); i++)
        pTC->setRawData(i,rawData[i]);
    pTC->setSubType(PUS_ST_DATA_REP_DIS_HK);

    // Check validity
    if ( !pTC->isValid() )
    {    setTestResult(TEST_FAILURE, "Wrong validity status");
         return;
    }

    // Execute telecommand and check success
    ao = pTC->execute();
    if ( ao!=ACTION_SUCCESS )
    {    setTestResult(TEST_FAILURE, "Wrong action outcome");
         return;
    }
    if ( pTMP_a->isEnabled() )
    {    setTestResult(TEST_FAILURE, "Wrong enable status");
         return;
    }

    // Load raw data in telecommandand and configure telecommand
    rawData[0]=2;
    sid[0]=sid_a;
    sid[1]=sid_b;
    for (unsigned int i=0; i<(1+2*sizeof(TD_SID)); i++)
        pTC->setRawData(i,rawData[i]);
    pTC->setSubType(PUS_ST_DATA_REP_ENB_HK);

    // Check validity
    if ( !pTC->isValid() )
    {    setTestResult(TEST_FAILURE, "Wrong validity status");
         return;
    }

    // Execute telecommand and check success
    ao = pTC->execute();
    if ( ao!=ACTION_SUCCESS )
    {    setTestResult(TEST_FAILURE, "Wrong action outcome");
         return;
    }
    if ( (!pTMP_a->isEnabled()) || (!pTMP_b->isEnabled()) )
    {    setTestResult(TEST_FAILURE, "Wrong enable status");
         return;
    }

    // Load illegal raw data in telecommandand and configure telecommand
    if (isNonNominalCheckAllowed()) {
        rawData[0]=3;
        sid[0]=sid_a;
        sid[1]=sid_b;
        sid[2]=sid_a;
        for (unsigned int i=0; i<(1+3*sizeof(TD_SID)); i++)
            pTC->setRawData(i,rawData[i]);
        pTC->setSubType(PUS_ST_DATA_REP_ENB_HK);

    // Check validity
        if ( pTC->isValid() || (pTC->getValidityCheckCode()!=VC_TOO_MANY_RAW_DATA) )
        {    setTestResult(TEST_FAILURE, "Wrong validity status");
             return;
        }
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

    // Load raw data in telecommandand and configure telecommand
    rawData[0]=2;
    sid[0]=sid_a+10;
    sid[1]=sid_b;
    for (unsigned int i=0; i<(1+2*sizeof(TD_SID)); i++)
        pTC->setRawData(i,rawData[i]);
    pTC->setSubType(PUS_ST_DATA_REP_DIS_HK);

    // Check validity
    if ( !pTC->isValid() )
    {    setTestResult(TEST_FAILURE, "Wrong validity status");
         return;
    }

    // Execute telecommand and check success
    ao = pTC->execute();
    if ( ao!=ACTION_FAILURE )
    {    setTestResult(TEST_FAILURE, "Wrong action outcome");
         return;
    }

    setTestResult(TEST_SUCCESS,"Test Successful");
    return;
}
