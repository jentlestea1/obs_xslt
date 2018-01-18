//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseBasicPUSTcLoader_1.cpp
//
// Version	1.0
// Date		04.02.04
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telecommand/CC_TelecommandFactory.h"
#include "../Telecommand/CC_TelecommandManager.h"
#include "../Telecommand/DC_TestPUSTelecommand.h"
#include "../Telecommand/DC_BasicPUSTcLoader.h"
#include "../Data/DC_SampleFullDataPool.h"
#include "../Utilities/TestCasePUSFull.h"
#include "TestCaseBasicPUSTcLoader_1.h"

#include <string.h>
#include <assert.h>

TestCaseBasicPUSTcLoader_1::TestCaseBasicPUSTcLoader_1(void) :
	TestCasePUSFull(ID_BASICPUSTCLOADER*10+1,"TestCaseBasicPUSTcLoader_1") {
		return;
}

void TestCaseBasicPUSTcLoader_1::runTestCase(void) {

    const unsigned int TC_AREA_SIZE = 85;
    tcArea = new unsigned char[TC_AREA_SIZE];
    CC_TelecommandFactory* pTCF = CC_TelecommandFactory::getInstance();
    if ( pTCF->getNumberTestPUSTelecommand()!=0 )
    {	setTestResult(TEST_FAILURE,"Wrong number of telecommands");
    	return;
    }
    if ( pTCF->getCapacityTestPUSTelecommand()<3 )
    {	setTestResult(TEST_FAILURE,"Insufficient TC factory capacity");
    	return;
    }
    unsigned int nEvt;
    CC_TelecommandManager* pTCM = getTelecommandManager();
    pTCL = getTcLoader();

    // Check the correctness of the class identifier
    if ( (pTCL->getClassId() != ID_BASICPUSTCLOADER) )
    {	setTestResult(TEST_FAILURE,"Wrong class identifier");
        return;
    }

    // Set the start address of the telecommand load area
    pTCL->setTcLoadAreaStart(tcArea);

    // Set max number of TCs
    const unsigned int MAX_NUMBER_OF_TC = 4;
    pTCL->setMaxNumberOfTc(MAX_NUMBER_OF_TC);
    if ( pTCL->getMaxNumberOfTc()!=MAX_NUMBER_OF_TC)
    {	setTestResult(TEST_FAILURE,"Wrong configuration value");
        return;
    }

    // Set max length of TCs
    const unsigned int MAX_TC_LENGTH = 20;
    pTCL->setMaxTcLength(MAX_TC_LENGTH);
    if ( pTCL->getMaxTcLength()!=MAX_TC_LENGTH)
    {	setTestResult(TEST_FAILURE,"Wrong configuration value");
        return;
    }

    // Load one telecommand image
    unsigned short tcID = 11;
    TD_TelecommandSource tcSource = 13;
    unsigned int start = 0;
    *(tcArea+start) = 1;    // number of telecommands
    start++;
    writeTcHeader(start,PUSTelecommand::getPacketId(),tcID,11+sizeof(TD_TelecommandSource),
                    0xA,PUS_TYPE_TEST,PUS_ST_TC_TEST,tcSource);
    start = start+9+sizeof(TD_TelecommandSource);
    writeTcData(start,3,false,true,1,2,0);
    start = start+8;
    pTCL->activate();

    // Check the number of loaded telecommands
    if ( pTCM->getPendingTelecommands()!=1 )
    {	setTestResult(TEST_FAILURE,"Wrong number of pending TCs");
        return;
    }

    // Check the configuration of the loaded telecommand
    Telecommand* pTC = pTCM->getPendingTelecommand(0);
    if ( pTC==pNULL )
    {	setTestResult(TEST_FAILURE,"No loaded telecommand");
        return;
    }
    if ( pTC->getClassId()!=ID_TESTPUSTELECOMMAND )
    {	setTestResult(TEST_FAILURE,"Wrong loaded telecommand");
        return;
    }
    if ( checkTcConfig( (DC_TestPUSTelecommand*)pTC, 
                        PUSTelecommand::getPacketId(), tcID,
                        0xA, tcSource, 3, false, false, 1, 2, 0) )
    {	setTestResult(TEST_FAILURE,"Wrong telecommand configuration");
        return;
    }

    // Check the "in use" status
    if ( !pTC->isInUse() )
    {	setTestResult(TEST_FAILURE,"Wrong in_use status");
        return;
    }
    pTCM->activate();
    if ( pTC->isInUse() )
    {	setTestResult(TEST_FAILURE,"Wrong in_use status");
        return;
    }

    // Write two TC packets to the tc load area of which the second is not intended for the TC loader
    *(tcArea) = 2;    // number of telecommands
    start = 1;

    writeTcHeader(start,PUSTelecommand::getPacketId()+1,tcID,11+sizeof(TD_TelecommandSource),
                    0xA,PUS_TYPE_TEST,PUS_ST_TC_TEST,tcSource);
    start = start+9+sizeof(TD_TelecommandSource);
    writeTcData(start,3,false,true,1,2,0);
    start = start+8;

    writeTcHeader(start,PUSTelecommand::getPacketId(),tcID,11+sizeof(TD_TelecommandSource),
                    0xA,PUS_TYPE_TEST,PUS_ST_TC_TEST,tcSource);
    start = start+9+sizeof(TD_TelecommandSource);
    writeTcData(start,3,false,true,1,2,0);
    start = start+8;
    pTCL->activate();

    // Check the number of loaded telecommands
    if ( pTCM->getPendingTelecommands()!=1 )
    {	setTestResult(TEST_FAILURE,"Wrong number of pending TCs");
        return;
    }

    // Write three TC packets to the tc load area 
    *(tcArea) = 3;    // number of telecommands
    start = 1;

    writeTcHeader(start,PUSTelecommand::getPacketId(),tcID,11+sizeof(TD_TelecommandSource),
                    0xB,PUS_TYPE_TEST,PUS_ST_TC_TEST,tcSource);
    start = start+9+sizeof(TD_TelecommandSource);
    writeTcData(start,7,true,true,1,1,1);
    start = start+8;

    writeTcHeader(start,PUSTelecommand::getPacketId(),tcID,11+sizeof(TD_TelecommandSource),
                    0xC,PUS_TYPE_TEST,PUS_ST_TC_TEST,tcSource);
    start = start+9+sizeof(TD_TelecommandSource);
    writeTcData(start,17,false,true,2,2,0);
    start = start+8;

    writeTcHeader(start,PUSTelecommand::getPacketId(),tcID,11+sizeof(TD_TelecommandSource),
                    0xD,PUS_TYPE_TEST,PUS_ST_TC_TEST,tcSource);
    start = start+9+sizeof(TD_TelecommandSource);
    writeTcData(start,27,true,true,3,3,1);
    start = start+8;
    pTCL->activate();

    // Check the number of loaded telecommands
    if ( pTCM->getPendingTelecommands()!=3 )
    {	setTestResult(TEST_FAILURE,"Wrong number of pending TCs");
        return;
    }

    // Check the configuration of the first telecommand
    Telecommand* pTCa = pTCM->getPendingTelecommand(0);
    if ( pTC==pNULL )
    {	setTestResult(TEST_FAILURE,"No loaded telecommand");
        return;
    }
    if ( pTC->getClassId()!=ID_TESTPUSTELECOMMAND )
    {	setTestResult(TEST_FAILURE,"Wrong loaded telecommand");
        return;
    }
    if ( checkTcConfig( (DC_TestPUSTelecommand*)pTC, 
                        PUSTelecommand::getPacketId(), tcID,
                        0xB, tcSource, 7,true,true,1,1,1) )
    {	setTestResult(TEST_FAILURE,"Wrong telecommand configuration");
        return;
    }

    // Check the configuration of the second telecommand
    Telecommand* pTCb = pTCM->getPendingTelecommand(1);
    if ( pTC==pNULL )
    {	setTestResult(TEST_FAILURE,"No loaded telecommand");
        return;
    }
    if ( pTC->getClassId()!=ID_TESTPUSTELECOMMAND )
    {	setTestResult(TEST_FAILURE,"Wrong loaded telecommand");
        return;
    }
    if ( checkTcConfig( (DC_TestPUSTelecommand*)pTC, 
                        PUSTelecommand::getPacketId(), tcID,
                        0xC, tcSource, 17,false,false,2,2,0) )
    {	setTestResult(TEST_FAILURE,"Wrong telecommand configuration");
        return;
    }

    // Check the configuration of the third telecommand
    Telecommand* pTCc = pTCM->getPendingTelecommand(2);
    if ( pTC==pNULL )
    {	setTestResult(TEST_FAILURE,"No loaded telecommand");
        return;
    }
    if ( pTC->getClassId()!=ID_TESTPUSTELECOMMAND )
    {	setTestResult(TEST_FAILURE,"Wrong loaded telecommand");
        return;
    }
    if ( checkTcConfig( (DC_TestPUSTelecommand*)pTC, 
                        PUSTelecommand::getPacketId(), tcID,
                        0xD, tcSource, 27,true,false,3,3,1) )
    {	setTestResult(TEST_FAILURE,"Wrong telecommand configuration");
        return;
    }

    // Check the "in use" status
    if ( !pTCa->isInUse() || !pTCb->isInUse() || !pTCc->isInUse() )
    {	setTestResult(TEST_FAILURE,"Wrong in_use status");
        return;
    }
    pTCM->activate();
    if ( pTCa->isInUse() || pTCb->isInUse() || pTCc->isInUse() )
    {	setTestResult(TEST_FAILURE,"Wrong in_use status");
        return;
    }

    // Write a TC packets that is too long
    *(tcArea) = 1;    // number of telecommands
    start = 1;

    writeTcHeader(start,PUSTelecommand::getPacketId(),tcID,MAX_TC_LENGTH+1,
                    0xA,PUS_TYPE_TEST,PUS_ST_TC_TEST,tcSource);
    start = start+9+sizeof(TD_TelecommandSource);
    writeTcData(start,3,false,true,1,2,0);
    start = start+8;
    nEvt = getNumberOfEvents();
    pTCL->activate();

    // Check the number of loaded telecommands
    if ( pTCM->getPendingTelecommands()!=0 )
    {	setTestResult(TEST_FAILURE,"Wrong number of pending TCs");
        return;
    }

    // Check correct event generation and flush the TC manager
    if ( !verifyLatestEvent(nEvt+1,EVT_TC_TOO_LONG) )
    {	setTestResult(TEST_FAILURE,"Wrong event report type");
        return;
    }
    nEvt++;
    pTCM->activate();

    // Write two TC packets of which the first one has a type not recongnized by the TC loader
    *(tcArea) = 2;    // number of telecommands
    start = 1;

    writeTcHeader(start,PUSTelecommand::getPacketId(),tcID,11+sizeof(TD_TelecommandSource),
                    0xA,PUS_TYPE_TEST+1,PUS_ST_TC_TEST,tcSource);
    start = start+9+sizeof(TD_TelecommandSource);
    writeTcData(start,3,false,true,1,2,0);
    start = start+8;

    writeTcHeader(start,PUSTelecommand::getPacketId(),tcID,11+sizeof(TD_TelecommandSource),
                    0xA,PUS_TYPE_TEST,PUS_ST_TC_TEST,tcSource);
    start = start+9+sizeof(TD_TelecommandSource);
    writeTcData(start,3,false,true,1,2,0);
    start = start+8;

    nEvt = getNumberOfEvents();
    pTCL->activate();

    // Check the number of loaded telecommands
    if ( pTCM->getPendingTelecommands()!=1 )
    {	setTestResult(TEST_FAILURE,"Wrong number of pending TCs");
        return;
    }

    // Check correct event generation 
    if ( !verifySpecificEvent(nEvt+1,EVT_UNKNOWN_TC_TYPE) )
    {	setTestResult(TEST_FAILURE,"Wrong event report type");
        return;
    }
    pTCM->activate();       // flush the TC manager

    // Write more TC packets that allowed
    *(tcArea) = MAX_NUMBER_OF_TC+1;    // number of telecommands

    nEvt = getNumberOfEvents();
    pTCL->activate();

    // Check the number of loaded telecommands
    if ( pTCM->getPendingTelecommands()!=0 )
    {	setTestResult(TEST_FAILURE,"Wrong number of pending TCs");
        return;
    }

    // Check correct event generation 
    if ( !verifyLatestEvent(nEvt+1,EVT_TOO_MANY_TC_PCKT) )
    {	setTestResult(TEST_FAILURE,"Wrong event report type");
        return;
    }
    pTCM->activate();       // flush the TC manager

    // Write four TC packets to the tc load area 
    *(tcArea) = 4;    // number of telecommands
    start = 1;

    writeTcHeader(start,PUSTelecommand::getPacketId(),tcID,11+sizeof(TD_TelecommandSource),
                    0xB,PUS_TYPE_TEST,PUS_ST_TC_TEST,tcSource);
    start = start+9+sizeof(TD_TelecommandSource);
    writeTcData(start,7,true,true,1,1,1);
    start = start+8;

    writeTcHeader(start,PUSTelecommand::getPacketId(),tcID,11+sizeof(TD_TelecommandSource),
                    0xC,PUS_TYPE_TEST,PUS_ST_TC_TEST,tcSource);
    start = start+9+sizeof(TD_TelecommandSource);
    writeTcData(start,17,false,true,2,2,0);
    start = start+8;

    writeTcHeader(start,PUSTelecommand::getPacketId(),tcID,11+sizeof(TD_TelecommandSource),
                    0xD,PUS_TYPE_TEST,PUS_ST_TC_TEST,tcSource);
    start = start+9+sizeof(TD_TelecommandSource);
    writeTcData(start,27,true,true,3,3,1);
    start = start+8;

    writeTcHeader(start,PUSTelecommand::getPacketId(),tcID,11+sizeof(TD_TelecommandSource),
                    0xD,PUS_TYPE_TEST,PUS_ST_TC_TEST,tcSource);
    start = start+9+sizeof(TD_TelecommandSource);
    writeTcData(start,27,true,true,3,3,1);
    start = start+8;
    nEvt = getNumberOfEvents();
    pTCL->activate();

    // Check the number of loaded telecommands
    if ( pTCM->getPendingTelecommands()!=3 )
    {	setTestResult(TEST_FAILURE,"Wrong number of pending TCs");
        return;
    }

    // Check correct event generation (NB: one event is created whenever a TC is 
    // successufully loaded in the TC manager)
    if ( !verifyLatestEvent(nEvt+4,EVT_NO_TC_AVAIL) )
    {	setTestResult(TEST_FAILURE,"Wrong event report type");
        return;
    }
    pTCM->activate();       // flush the TC manager

    // If this point is reached, the test was successful
    setTestResult(TEST_SUCCESS,"Test Successful");
    return;
}

void TestCaseBasicPUSTcLoader_1::writeTcHeader(unsigned int start, unsigned short packetId, unsigned short packetSeqControl,
                       unsigned short packetLength, unsigned char ackField, unsigned char tcType,
                       unsigned char tcSubType, TD_TelecommandSource tcSource) {
    
    assert(sizeof(unsigned short)==2);
    assert(sizeof(unsigned char)==1);
    memcpy((tcArea+start),&packetId,2);
    memcpy((tcArea+start+2),&packetSeqControl,2);
    memcpy((tcArea+start+4),&packetLength,2);
    memcpy((tcArea+start+6),&ackField,1);
    memcpy((tcArea+start+7),&tcType,1);
    memcpy((tcArea+start+8),&tcSubType,1);
    memcpy((tcArea+start+9),&tcSource,sizeof(TD_TelecommandSource));
}

void TestCaseBasicPUSTcLoader_1::writeTcData(
                        unsigned int start, unsigned int execCounter, bool execCheckVal,
                        bool valCheckVal, TD_CheckCode execCheckCode,
                        TD_CheckCode valCheckCode, bool execOutcome) {

    *(unsigned char*)(tcArea+start) = (unsigned char)execCounter;
    *(unsigned char*)(tcArea+start+1) = execCheckVal;
    *(unsigned char*)(tcArea+start+2) = valCheckVal;
    *(unsigned char*)(tcArea+start+3) = (unsigned char)execCheckCode;
    *(unsigned char*)(tcArea+start+4) = (unsigned char)valCheckCode;
    *(unsigned char*)(tcArea+start+5) = execOutcome;
}

bool TestCaseBasicPUSTcLoader_1::checkTcConfig(DC_TestPUSTelecommand* pTC, 
                        unsigned short packetID, unsigned short packetSeqControl,
                        unsigned char ackField, TD_TelecommandSource tcSource,
                        unsigned int execCounter, bool execCheckVal,
                        bool valCheckVal, TD_CheckCode execCheckCode,
                        TD_CheckCode valCheckCode, bool execOutcome) {

    if ( pTC->getPacketId()!=packetID )
        return false;

    if ( pTC->getTelecommandId()!=packetSeqControl )
        return false;

    if ( pTC->isAcceptanceAckRequired() && !(ackField&1) )
        return false;

    if ( pTC->isStartAckRequired() && !(ackField&2) )
        return false;

    if ( pTC->isProgressAckRequired() && !(ackField&4) )
        return false;

    if ( pTC->isCompletionAckRequired() && !(ackField&8) )
        return false;

    if ( pTC->getSource()!=tcSource )
        return false;

    if ( pTC->getExecutionCounter() != execCounter )
        return false;

    if ( pTC->canExecute() && !execCheckVal )
        return false;

    if ( pTC->isValid() && !valCheckVal )
        return false;

    if ( pTC->getExecutionCheckCode() != execCheckCode )
        return false;

    if ( pTC->getValidityCheckCode() != valCheckCode )
        return false;

    if ( (pTC->execute()== ACTION_SUCCESS) && !execOutcome )
        return false;

    return true;
}

