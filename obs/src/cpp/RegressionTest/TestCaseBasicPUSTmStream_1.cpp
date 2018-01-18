//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseBasicPUSTmStream_1.cpp
//
// Version	1.0
// Date		04.02.04
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Telemetry/DC_DummyPUSTelemetryPacket.h"
#include "../Telemetry/DC_BasicPUSTmStream.h"
#include "../Data/DC_SampleFullDataPool.h"
#include "../Utilities/TestCasePUSFull.h"
#include "TestCaseBasicPUSTmStream_1.h"

#include <string.h>
#include <assert.h>

TestCaseBasicPUSTmStream_1::TestCaseBasicPUSTmStream_1(void) :
	TestCaseWithFactories(ID_BASICPUSTMSTREAM*10+1,"TestCaseBasicPUSTmStream_1") {
		return;
}

void TestCaseBasicPUSTmStream_1::runTestCase(void) {

    const unsigned int TM_AREA_SIZE = 50;
    tmArea = new unsigned char[TM_AREA_SIZE];
    CC_TelemetryPacketFactory* pTCF = CC_TelemetryPacketFactory::getInstance();
    if ( (pTCF->getCapacityDummyPUSTelemetryPacket()-
            pTCF->getNumberDummyPUSTelemetryPacket())==0 )
    {	setTestResult(TEST_FAILURE,"No more available TM packets");
    	return;
    }
    pTM = pTCF->allocateDummyPUSTelemetryPacket();
    unsigned int nEvt = getNumberOfEvents();
    pTMS = new DC_BasicPUSTmStream();;

    // Check the correctness of the class identifier
    if ( (pTMS->getClassId() != ID_BASICPUSTMSTREAM) )
    {	setTestResult(TEST_FAILURE,"Wrong class identifier");
        return;
    }

    // Check that tm stream is initially not configured
    if ( pTMS->isObjectConfigured() )
    {	setTestResult(TEST_FAILURE,"Wrong configuration status");
        return;
    }

    // Set stream capacity and check success
    pTMS->setCapacity(TM_AREA_SIZE);
    if ( pTMS->getCapacity()!=TM_AREA_SIZE )
    {	setTestResult(TEST_FAILURE,"Wrong stream capacity");
        return;
    }

    // Set the start address of the telemetry write area and check success
    pTMS->setStartAddress(tmArea);
    if ( pTMS->getStartAddress()!=tmArea )
    {	setTestResult(TEST_FAILURE,"Wrong tm write area address");
        return;
    }

    // Check that tm stream is configured
    if ( !pTMS->isObjectConfigured() )
    {	setTestResult(TEST_FAILURE,"Wrong configuration status");
        return;
    }

    // Check initial value of packet counter
    if ( pTMS->getPacketCounter()!=0 )
    {	setTestResult(TEST_FAILURE,"Wrong packet counter value");
        return;
    }

    // Get initial value of sequence counter
    unsigned int seqCounter = pTMS->getSequenceCounter();

    // Configure the TM packet and write it to the TM stream
    unsigned char value = 10;
    pTM->setValue(value);
    pTMS->write(pTM);
    if ( !checkTmImage(1, value) )
    {	setTestResult(TEST_FAILURE,"Incorrect packet image");
        return;
    }

    // Check the value of the packet counter
    if ( pTMS->getPacketCounter()!=1 )
    {	setTestResult(TEST_FAILURE,"Wrong packet counter value");
        return;
    }

    // Check the value of the sequence counter
    if ( pTMS->getSequenceCounter()!=seqCounter+1 )
    {	setTestResult(TEST_FAILURE,"Wrong sequence counter value");
        return;
    }
    
    // Compute maximum number of packets that fit in the telemetry area
    unsigned int maxNPackets = (TM_AREA_SIZE-1)/(pTM->getNumberOfBytes()+11+sizeof(TD_ObsTime));

    // Fill up the telemetry write area
    for (unsigned int i=1; i<(maxNPackets+1); i++)
        pTMS->write(pTM);

    // Check that the correct event was generated
    if ( !verifyLatestEvent(nEvt+1,EVT_TM_STREAM_END) )
        return;

    // Check the value of the packet counter
    if ( pTMS->getPacketCounter()!=maxNPackets )
    {	setTestResult(TEST_FAILURE,"Wrong packet counter value");
        return;
    }

    // Check the value of the sequence counter
    if ( pTMS->getSequenceCounter()!=seqCounter+maxNPackets+1 )
    {	setTestResult(TEST_FAILURE,"Wrong sequence counter value");
        return;
    }

    // Reset stream and check success
    pTMS->reset();
    if ( pTMS->getPacketCounter()!=0 )
    {	setTestResult(TEST_FAILURE,"Wrong packet counter value");
        return;
    }

    // Write operation should now succeed
    pTMS->write(pTM);
    if ( pTMS->getPacketCounter()!=1 )
    {	setTestResult(TEST_FAILURE,"Wrong packet counter value");
        return;
    }
    if ( getNumberOfEvents()!=nEvt+1 )
    {	setTestResult(TEST_FAILURE,"Wrong number of events");
        return;
    }

    // Fill up again the telemetry write area
    for (unsigned int i=1; i<(maxNPackets+1); i++)
        pTMS->write(pTM);

    // Flush stream and check success
    pTMS->flush();
    if ( pTMS->getPacketCounter()!=0 )
    {	setTestResult(TEST_FAILURE,"Wrong packet counter value");
        return;
    }

    // Write operation should now succeed
    pTMS->write(pTM);
    if ( pTMS->getPacketCounter()!=1 )
    {	setTestResult(TEST_FAILURE,"Wrong packet counter value");
        return;
    }
    if ( getNumberOfEvents()!=nEvt+2 )
    {	setTestResult(TEST_FAILURE,"Wrong number of events");
        return;
    }

    setTestResult(TEST_SUCCESS,"Test Successful");
    return;
}

bool TestCaseBasicPUSTmStream_1::checkTmImage(unsigned int start, unsigned char value) {

    unsigned short usTemp = 0;
    unsigned char ucTemp = 0;
    TD_ObsTime otTemp = 0;
    assert(sizeof(unsigned short)==2);

    memcpy(&usTemp,tmArea+start,2);
    if ( usTemp!=pTM->getPacketId() ) {
        setTestResult(TEST_FAILURE,"Bytes 0 and 1 of header are wrong");
        return false;
    }

    memcpy(&usTemp,tmArea+start+2,2);
    if ( usTemp!=0xC0+pTMS->getSequenceCounter() ) {
        setTestResult(TEST_FAILURE,"Bytes 2 and 3 of header are wrong");
        return false;
    }

    memcpy(&usTemp,tmArea+start+4,2);
    if ( usTemp!=3+sizeof(TD_ObsTime)+pTM->getNumberOfBytes()+2 ) {
        setTestResult(TEST_FAILURE,"Bytes 4 and 5 of header are wrong");
        return false;
    }

    memcpy(&ucTemp,tmArea+start+6,1);
    if ( ucTemp!=0x10 ) {
        setTestResult(TEST_FAILURE,"Byte 1 of data field is wrong");
        return false;
    }

    memcpy(&ucTemp,tmArea+start+7,1);
    if ( ucTemp!=pTM->getType() ) {
        setTestResult(TEST_FAILURE,"Byte 2 of data field is wrong");
        return false;
    }

    memcpy(&ucTemp,tmArea+start+8,1);
    if ( ucTemp!=pTM->getSubType() ) {
        setTestResult(TEST_FAILURE,"Byte 3 of data field is wrong");
        return false;
    }

    memcpy(&otTemp,tmArea+start+9,sizeof(TD_ObsTime));
    if ( otTemp!=pTM->getTimeTag() ) {
        setTestResult(TEST_FAILURE,"Time field is wrong");
        return false;
    }

    memcpy(&ucTemp,tmArea+start+9+sizeof(TD_ObsTime),1);
    if ( usTemp!=value ) {
        setTestResult(TEST_FAILURE,"Application data field is wrong");
        return false;
    }

    memcpy(&usTemp,tmArea+start+9+sizeof(TD_ObsTime)+1,2);
    if ( usTemp!=(unsigned short)0 ) {
        setTestResult(TEST_FAILURE,"Error control field is wrong");
        return false;
    }

    return true;
}

