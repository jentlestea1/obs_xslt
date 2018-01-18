//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCasePUSEventRepository_1.cpp
//
// Version	1.0
// Date		04.02.04
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../System/DC_DummyObsClock.h"
#include "../Event/DC_PUSEventRepository.h"
#include "../Manoeuvre/CC_ManoeuvreFactory.h"
#include "../Manoeuvre/DC_DummyConfigurableManoeuvre.h"
#include "../Telemetry/CC_TelemetryManager.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Telecommand/CC_TelecommandFactory.h"
#include "../Telecommand/CC_TelecommandManager.h"
#include "../Telecommand/DC_TestPUSTelecommand.h"
#include "../Telecommand/DC_BasicPUSTcLoader.h"
#include "../Telemetry/DC_PUSTcVerificationPacket.h"
#include "../Data/DC_SampleFullDataPool.h"
#include "../Utilities/TestCasePUSFull.h"
#include "TestCasePUSEventRepository_1.h"


TestCasePUSEventRepository_1::TestCasePUSEventRepository_1(void) :
	TestCasePUSFull(ID_PUSEVENTREPOSITORY*10+1,"TestCasePUSEventRepository_1") {
		return;
}

void TestCasePUSEventRepository_1::runTestCase(void) {

    unsigned int nEvt;
    const TD_TelecommandId tcId_1 = 121;
    const TD_TelecommandId tcId_2 = 122;

    CC_TelecommandFactory* pTCF = CC_TelecommandFactory::getInstance();
    if ( pTCF->getNumberTestPUSTelecommand()!=0 )
    {	setTestResult(TEST_FAILURE,"Wrong number of telecommands");
    	return;
    }
    if ( pTCF->getCapacityTestPUSTelecommand()<1 )
    {	setTestResult(TEST_FAILURE,"Insufficient TC factory capacity");
    	return;
    }
    DC_TestPUSTelecommand* pTC = pTCF->allocateTestPUSTelecommand();
    pTC->setTelecommandId(tcId_1);

    CC_ManoeuvreFactory* pMF = CC_ManoeuvreFactory::getInstance();
    if ( pMF->getNumberTestPUSConfigurableManoeuvre()!=0 )
    {	setTestResult(TEST_FAILURE,"Wrong number of manoeuvres");
    	return;
    }
    if ( pMF->getCapacityTestPUSConfigurableManoeuvre()<1 )
    {	setTestResult(TEST_FAILURE,"Insufficient manoeuvre factory capacity");
    	return;
    }
    DC_TestPUSConfigurableManoeuvre* pMan = pMF->allocateTestPUSConfigurableManoeuvre();
    pMan->setTelecommandId(tcId_2);

    DC_PUSEventRepository* pEvtRep = getEventRepository();

    // Check the correctness of the class identifier
    if ( (pEvtRep->getClassId() != ID_PUSEVENTREPOSITORY) )
    {	setTestResult(TEST_FAILURE,"Wrong class identifier");
        return;
    }

    // Flush telemetry manager to make sure that there are no pending packets in the
    // immediate dispatch queu
    pEvtRep->getTelemetryManager()->activate();

    // Make repeated call to the create method for telecommands and check success
    const TD_CheckCode VAL_CODE = 100;
    const TD_CheckCode EXEC_CODE = 101;
    const TD_CheckCode CONT_CODE = 102;

    nEvt = getNumberOfEvents();
    pTC->setAcknowledgeLevel(1);            // acceptance acknowledge flag is set
    pEvtRep->create(pTC,EVT_TC_LOADED);
    if ( !checkTmPacket(pEvtRep,PUS_ST_TC_VER_ACC_SC,tcId_1,getObsClock()->getTime(),0) )
    {	setTestResult(TEST_FAILURE,"Wrong packet configuration");
        return;
    }
    if ( !verifyLatestEvent(nEvt+1,EVT_TC_LOADED) )
        return;

    pTC->setAcknowledgeLevel(0);            // acceptance acknowledge flag is reset
    pEvtRep->create(pTC,EVT_TC_LOADED);
    if ( !checkNoTmPacket(pEvtRep) )
    {	setTestResult(TEST_FAILURE,"Unexpected packet");
        return;
    }

    pTC->setValidityCheckCode(0);
    pEvtRep->create(pTC,EVT_TC_NOT_VALID);
    if ( !checkTmPacket(pEvtRep,PUS_ST_TC_VER_ACC_FL,tcId_1,getObsClock()->getTime(),EVT_TC_NOT_VALID) )
    {	setTestResult(TEST_FAILURE,"Wrong packet configuration");
        return;
    }

    pTC->setValidityCheckCode(VAL_CODE);
    pEvtRep->create(pTC,EVT_TC_NOT_VALID);
    if ( !checkTmPacket(pEvtRep,PUS_ST_TC_VER_ACC_FL,tcId_1,getObsClock()->getTime(),VAL_CODE) )
    {	setTestResult(TEST_FAILURE,"Wrong packet configuration");
        return;
    }

    pEvtRep->create(pTC,EVT_TC_LIST_FULL);
    if ( !checkTmPacket(pEvtRep,PUS_ST_TC_VER_ACC_FL,tcId_1,getObsClock()->getTime(),EVT_TC_LIST_FULL) )
    {	setTestResult(TEST_FAILURE,"Wrong packet configuration");
        return;
    }

    nEvt = getNumberOfEvents();
    pMan->setStartAckFlag(true);
    pEvtRep->create(pMan,EVT_MAN_STARTED);
    if ( !checkTmPacket(pEvtRep,PUS_ST_TC_EXE_STR_SC,tcId_2,getObsClock()->getTime(),0) )
    {	setTestResult(TEST_FAILURE,"Wrong packet configuration");
        return;
    }
    if ( !verifyLatestEvent(nEvt+1,EVT_MAN_STARTED) )
        return;

    pMan->setStartAckFlag(false);
    pEvtRep->create(pMan,EVT_MAN_STARTED);
    if ( !checkNoTmPacket(pEvtRep) )
    {	setTestResult(TEST_FAILURE,"Unexpected packet");
        return;
    }

    pEvtRep->create(pMan,EVT_MAN_LIST_FULL);
    if ( !checkTmPacket(pEvtRep,PUS_ST_TC_EXE_STR_FL,tcId_2,getObsClock()->getTime(),EVT_MAN_LIST_FULL) )
    {	setTestResult(TEST_FAILURE,"Wrong packet configuration");
        return;
    }

    pTC->setExecutionCheckCode(0);
    pEvtRep->create(pTC,EVT_TC_EXEC_CHECK_FAIL);
    if ( !checkTmPacket(pEvtRep,PUS_ST_TC_EXE_STR_FL,tcId_1,getObsClock()->getTime(),EVT_TC_EXEC_CHECK_FAIL) )
    {	setTestResult(TEST_FAILURE,"Wrong packet configuration");
        return;
    }

    pTC->setExecutionCheckCode(EXEC_CODE);
    pEvtRep->create(pTC,EVT_TC_EXEC_CHECK_FAIL);
    if ( !checkTmPacket(pEvtRep,PUS_ST_TC_EXE_STR_FL,tcId_1,getObsClock()->getTime(),EXEC_CODE) )
    {	setTestResult(TEST_FAILURE,"Wrong packet configuration");
        return;
    }

    pEvtRep->create(pTC,EVT_TC_ABORTED);
    if ( !checkTmPacket(pEvtRep,PUS_ST_TC_EXE_STR_FL,tcId_1,getObsClock()->getTime(),EVT_TC_ABORTED) )
    {	setTestResult(TEST_FAILURE,"Wrong packet configuration");
        return;
    }

    pMan->setProgressAckFlag(true);
    pEvtRep->create(pMan,EVT_MAN_PROGRESS);
    if ( !checkTmPacket(pEvtRep,PUS_ST_TC_EXE_PRO_SC,tcId_2,getObsClock()->getTime(),0) )
    {	setTestResult(TEST_FAILURE,"Wrong packet configuration");
        return;
    }

    pMan->setProgressAckFlag(false);
    pEvtRep->create(pMan,EVT_MAN_PROGRESS);
    if ( !checkNoTmPacket(pEvtRep) )
    {	setTestResult(TEST_FAILURE,"Unexpected packet");
        return;
    }

    pTC->setAcknowledgeLevel(8);        // set completion acknowledge flag
    pEvtRep->create(pTC,EVT_TC_EXEC_SUCC);
    if ( !checkTmPacket(pEvtRep,PUS_ST_TC_EXE_END_SC,tcId_1,getObsClock()->getTime(),0) )
    {	setTestResult(TEST_FAILURE,"Wrong packet configuration");
        return;
    }

    pTC->setAcknowledgeLevel(0);        // reset acknowledge flags
    pEvtRep->create(pTC,EVT_TC_EXEC_SUCC);
    if ( !checkNoTmPacket(pEvtRep) )
    {	setTestResult(TEST_FAILURE,"Unexpected packet");
        return;
    }

    pTC->setActionOutcome(true);
    pEvtRep->create(pTC,EVT_TC_EXEC_FAIL);
    if ( !checkTmPacket(pEvtRep,PUS_ST_TC_EXE_END_FL,tcId_1,getObsClock()->getTime(),
                                                                            (TD_CheckCode)ACTION_SUCCESS) )
    {	setTestResult(TEST_FAILURE,"Wrong packet configuration");
        return;
    }

    pMan->setContinuationCheckCode(0);
    pEvtRep->create(pMan,EVT_MAN_ABORTED);
    if ( !checkTmPacket(pEvtRep,PUS_ST_TC_EXE_PRO_FL,tcId_2,getObsClock()->getTime(),EVT_MAN_ABORTED) )
    {	setTestResult(TEST_FAILURE,"Wrong packet configuration");
        return;
    }

    pMan->setContinuationCheckCode(CONT_CODE);
    pEvtRep->create(pMan,EVT_MAN_ABORTED);
    if ( !checkTmPacket(pEvtRep,PUS_ST_TC_EXE_PRO_FL,tcId_2,getObsClock()->getTime(),CONT_CODE) )
    {	setTestResult(TEST_FAILURE,"Wrong packet configuration");
        return;
    }

    pMan->setCompletionAckFlag(true);
    pEvtRep->create(pMan,EVT_MAN_TERMINATED);
    if ( !checkTmPacket(pEvtRep,PUS_ST_TC_EXE_END_SC,tcId_2,getObsClock()->getTime(),0) )
    {	setTestResult(TEST_FAILURE,"Wrong packet configuration");
        return;
    }

    pMan->setCompletionAckFlag(false);
    pEvtRep->create(pMan,EVT_MAN_TERMINATED);
    if ( !checkNoTmPacket(pEvtRep) )
    {	setTestResult(TEST_FAILURE,"Wrong packet configuration");
        return;
    }

    // Force a situation where the telemetry packet factory in the 
    // PUS event repository runs out of telemetry packets and check that correct event is generated
    CC_TelemetryPacketFactory* pTMF = CC_TelemetryPacketFactory::getInstance();
    while ( pTMF->isFreePUSTcVerificationPacket() )
        pEvtRep->create(pMan,EVT_MAN_ABORTED);
    nEvt = getNumberOfEvents();
    pEvtRep->create(pMan,EVT_MAN_TERMINATED);
    if ( getNumberOfEvents()!=nEvt+2 )
    {	setTestResult(TEST_FAILURE,"Wrong number of events");
        return;
    }
    if (!verifySpecificEvent(nEvt+1,EVT_TM_PCK_ALLOC_FAILURE))
        return;

    // If this point is reached, the test was successful
    setTestResult(TEST_SUCCESS,"Test Successful");
    return;
}

bool TestCasePUSEventRepository_1::checkTmPacket(
                        DC_PUSEventRepository* pEvtRep, TD_TelemetrySubType tmSubType,
                        TD_TelecommandId tcId, TD_ObsTime tt, TD_CheckCode errCode) {

    CC_TelemetryManager* pTMM = pEvtRep->getTelemetryManager();
    TelemetryPacket* pTemp = pTMM->getImmediateQueueEntry(0);
    if ( pTemp == pNULL )
        return false;

    if ( pTemp->getClassId()!=ID_PUSTCVERIFICATIONPACKET )
        return false;

    DC_PUSTcVerificationPacket* pTM = (DC_PUSTcVerificationPacket*)pTemp;

    if ( pTM->getSubType()!=tmSubType )
        return false;

    if ( pTM->getTelecommandId()!=tcId )
        return false;

    if ( pTM->getTimeTag()!=tt )
        return false;

    if ( pTM->getType()!=PUS_TYPE_TC_VER )
        return false;

    if ( errCode!=0 )
        if ( pTM->getErrorCode()!=errCode )
            return false;

    // Flush telemetry manager
    pTMM->activate();

    return true;
}

bool TestCasePUSEventRepository_1::checkNoTmPacket(DC_PUSEventRepository* pEvtRep) {

    CC_TelemetryManager* pTMM = pEvtRep->getTelemetryManager();
    TelemetryPacket* pTemp = pTMM->getImmediateQueueEntry(0);
    if ( pTemp == pNULL )
        return true;
    else
        return false;
}
