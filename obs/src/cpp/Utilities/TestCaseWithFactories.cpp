//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseWithFactories.cpp
//
// Version	1.0
// Date		13.04.03
// Author	A. Pasetti (P&P Software)

#include "TestCaseWithFactories.h"
#include "TestCase.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Data/DC_DummyDataPool.h"
#include "../Event/DC_EventRepository.h"
#include "../Data/DC_DummyDatabase.h"
#include "../Manoeuvre/DC_DummyManoeuvre.h"
#include "../Manoeuvre/DC_DummyConfigurableManoeuvre.h"
#include "../Manoeuvre/CC_ManoeuvreFactory.h"
#include "../Telemetry/PUSTelemetryPacket.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Telemetry/DC_PUSTcVerificationPacket.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"
#include "../Telemetry/DC_DummyPUSTelemetryPacket.h"
#include "../Telemetry/DC_PUSMemoryDumpOffset.h"
#include "../Telemetry/DC_PUSMemoryDumpAbsolute.h"
#include "../Telecommand/DC_PUSMemoryLoadOffset.h"
#include "../Telecommand/DC_PUSMemoryLoadAbsolute.h"
#include "../Telecommand/DC_PUSDumpMemoryOffset.h"
#include "../Telecommand/DC_PUSDumpMemoryAbsolute.h"
#include "../Telecommand/CC_TelecommandFactory.h"
#include "../Telecommand/DC_DummyTelecommand.h"
#include "../Telecommand/DC_DummyPUSTelecommand.h"
#include "../Telecommand/PUSTelecommand.h"

bool TestCaseWithFactories::firstActivation = true;

DC_DummyPUSTelemetryPacket* TestCaseWithFactories::pTmDum1 = pNULL;
DC_DummyPUSTelemetryPacket* TestCaseWithFactories::pTmDum2 = pNULL;
DC_PUSTcVerificationPacket* TestCaseWithFactories::pTmTVP1 = pNULL;
DC_PUSDataReportingPacket* TestCaseWithFactories::pTmDRP1 = pNULL;
DC_PUSDataReportingPacket* TestCaseWithFactories::pTmDRP2 = pNULL;
DC_PUSMemoryDumpOffset* TestCaseWithFactories::pTmMDO = pNULL;
DC_PUSMemoryDumpAbsolute* TestCaseWithFactories::pTmMDA = pNULL;

DC_DummyConfigurableManoeuvre* TestCaseWithFactories::pManCD = pNULL;
DC_TestPUSConfigurableManoeuvre* TestCaseWithFactories::pManTP = pNULL;
DC_DummyManoeuvre* TestCaseWithFactories::pManDum = pNULL;

DC_DummyPUSTelecommand* TestCaseWithFactories::pTcPDum = pNULL;
DC_DummyTelecommand* TestCaseWithFactories::pTcDum1 = pNULL;
DC_DummyTelecommand* TestCaseWithFactories::pTcDum2 = pNULL;
DC_PUSControlDataReporting* TestCaseWithFactories::pTcCDR = pNULL;
DC_PUSDefineDataReporting* TestCaseWithFactories::pTcDDR = pNULL;
DC_TestPUSTelecommand* TestCaseWithFactories::pTcTPT1 = pNULL;
DC_TestPUSTelecommand* TestCaseWithFactories::pTcTPT2 = pNULL;
DC_TestPUSTelecommand* TestCaseWithFactories::pTcTPT3 = pNULL;
DC_PUSDumpMemoryOffset* TestCaseWithFactories::pTcDMO = pNULL;
DC_PUSDumpMemoryAbsolute* TestCaseWithFactories::pTcDMA = pNULL;
DC_PUSMemoryLoadOffset* TestCaseWithFactories::pTcMLO = pNULL;
DC_PUSMemoryLoadAbsolute* TestCaseWithFactories::pTcMLA1 = pNULL;
DC_PUSMemoryLoadAbsolute* TestCaseWithFactories::pTcMLA2 = pNULL;


TestCaseWithFactories::TestCaseWithFactories(int testId, char* testName):
     TestCaseWithEvtCheck(testId,testName) {
     return;
}

bool TestCaseWithFactories::setUpTestCase(void) {

   if (!TestCaseWithEvtCheck::setUpTestCase()) 
       return INITIALIZATION_FAILURE;

   if (firstActivation) {

     // Instantiate the items to go into the factories
     pTmDum1 = new DC_DummyPUSTelemetryPacket();
     pTmDum2 = new DC_DummyPUSTelemetryPacket();
     pTmTVP1 = new DC_PUSTcVerificationPacket();
     pTmDRP1 = new DC_PUSDataReportingPacket();
     pTmDRP2 = new DC_PUSDataReportingPacket();
     pTmMDO = new DC_PUSMemoryDumpOffset();
     pTmMDA = new DC_PUSMemoryDumpAbsolute();

     pManCD = new DC_DummyConfigurableManoeuvre();
     pManTP = new DC_TestPUSConfigurableManoeuvre();
     pManDum = new DC_DummyManoeuvre();

     pTcPDum = new DC_DummyPUSTelecommand();
     pTcDum1 = new DC_DummyTelecommand();
     pTcDum2 = new DC_DummyTelecommand();
     pTcCDR = new DC_PUSControlDataReporting();
     pTcDDR = new DC_PUSDefineDataReporting();
     pTcTPT1 = new DC_TestPUSTelecommand();
     pTcTPT2 = new DC_TestPUSTelecommand();
     pTcTPT3 = new DC_TestPUSTelecommand();
     pTcDMO = new DC_PUSDumpMemoryOffset();
     pTcDMA = new DC_PUSDumpMemoryAbsolute();
     pTcMLO = new DC_PUSMemoryLoadOffset();
     pTcMLA1 = new DC_PUSMemoryLoadAbsolute();
     pTcMLA2 = new DC_PUSMemoryLoadAbsolute();

     // Load the telemetry packet factory
     CC_TelemetryPacketFactory* pTmFct = CC_TelemetryPacketFactory::getInstance();
     pTmFct->setTelemetryPacket(0, pTmDum1);
     pTmFct->setTelemetryPacket(1, pTmDum2);
     pTmFct->setTelemetryPacket(0, pTmTVP1);

     pTmDRP1->setMaxNumberFA(0);
     pTmDRP1->setDefinitionBufferSize(PUS_DRP_DEF_BUF_SIZE_SMALL);
     pTmDRP1->setValueBufferSize(PUS_DRP_VAL_BUF_SIZE_SMALL);
     pTmFct->setTelemetryPacket(0, pTmDRP1);

     pTmDRP2->setMaxNumberFA(PUS_DRP_MAX_FA);
     pTmDRP2->setDefinitionBufferSize(PUS_DRP_DEF_BUF_SIZE_LARGE);
     pTmDRP2->setValueBufferSize(PUS_DRP_VAL_BUF_SIZE_LARGE);
     pTmFct->setTelemetryPacket(1, pTmDRP2);

     pTmMDO->setDumpBufferSize(PUS_MEM_BUFFER_LENGTH);
     pTmMDO->setMaxNumberBlocks(PUS_NUMBER_MEM_BLOCKS);
     pTmFct->setTelemetryPacket(0, pTmMDO);

     pTmMDA->setDumpBufferSize(PUS_MEM_BUFFER_LENGTH);
     pTmMDA->setMaxNumberBlocks(PUS_NUMBER_MEM_BLOCKS);
     pTmFct->setTelemetryPacket(0, pTmMDA);

     // Load the manoeuvre factory
     CC_ManoeuvreFactory* pManFct = CC_ManoeuvreFactory::getInstance();
     pManFct->setManoeuvre(0, pManCD);
     pManFct->setManoeuvre(0, pManTP);
     pManFct->setManoeuvre(0, pManDum);

     // Load the telecommand factory
     CC_TelecommandFactory* pTcFct = CC_TelecommandFactory::getInstance();
     pTcFct->setTelecommand(0, pTcDum1);
     pTcFct->setTelecommand(1, pTcDum2);
     pTcFct->setTelecommand(0, pTcPDum);
     pTcFct->setTelecommand(0, pTcCDR);
     pTcFct->setTelecommand(0, pTcDDR);
     pTcFct->setTelecommand(0, pTcTPT1);
     pTcFct->setTelecommand(1, pTcTPT2);
     pTcFct->setTelecommand(2, pTcTPT3);

     pTcDMO->setNumberOfRawData(PUS_MEM_BUFFER_LENGTH);
     pTcFct->setTelecommand(0, pTcDMO);

     pTcDMA->setNumberOfRawData(PUS_MEM_BUFFER_LENGTH);
     pTcFct->setTelecommand(0, pTcDMA);

     pTcMLA1->setMaxNumberBlocks(PUS_NUMBER_MEM_BLOCKS);
     pTcMLA1->setMaxNumberData(PUS_MEM_BUFFER_LENGTH);
     pTcFct->setTelecommand(0, pTcMLA1);

     pTcMLA2->setMaxNumberBlocks(PUS_NUMBER_MEM_BLOCKS);
     pTcMLA2->setMaxNumberData(PUS_MEM_BUFFER_LENGTH);
     pTcFct->setTelecommand(1, pTcMLA2);

     pTcMLO->setMaxNumberBlocks(PUS_NUMBER_MEM_BLOCKS);
     pTcMLO->setMaxNumberData(PUS_MEM_BUFFER_LENGTH);
     pTcFct->setTelecommand(0, pTcMLO);

     // Check factory configuration
     if ( !pTmFct->isObjectConfigured() ) {
         setTestResult(false,"TM Factory is not configured");
         return INITIALIZATION_FAILURE;
     }
     if ( !pManFct->isObjectConfigured() ) {
         setTestResult(false,"Manoeuvre Factory is not configured");
         return INITIALIZATION_FAILURE;
     }
     if ( !pTcFct->isObjectConfigured() ) {
         setTestResult(false,"TC Factory is not configured");
         return INITIALIZATION_FAILURE;
     }

     firstActivation = false;
   }

   return INITIALIZATION_SUCCESS;
}

bool TestCaseWithFactories::shutDownTestCase(void) {
     
     // Mark all items loaded in the factories as "not in use"
     pTmDum1->setInUse(NOT_IN_USE);
     pTmDum2->setInUse(NOT_IN_USE);
     pTmTVP1->setInUse(NOT_IN_USE);
     pTmDRP1->setInUse(NOT_IN_USE);
     pTmDRP2->setInUse(NOT_IN_USE);
     pTmMDO->setInUse(NOT_IN_USE);
     pTmMDA->setInUse(NOT_IN_USE);

     pManCD->setInUse(NOT_IN_USE);
     pManDum->setInUse(NOT_IN_USE);
     pManTP->setInUse(NOT_IN_USE);

     pTcDum1->setInUse(NOT_IN_USE);
     pTcDum2->setInUse(NOT_IN_USE);
     pTcPDum->setInUse(NOT_IN_USE);
     pTcCDR->setInUse(NOT_IN_USE);
     pTcDDR->setInUse(NOT_IN_USE);
     pTcTPT1->setInUse(NOT_IN_USE);
     pTcTPT2->setInUse(NOT_IN_USE);
     pTcTPT3->setInUse(NOT_IN_USE);
     pTcDMO->setInUse(NOT_IN_USE);
     pTcDMA->setInUse(NOT_IN_USE);
     pTcMLA1->setInUse(NOT_IN_USE);
     pTcMLA2->setInUse(NOT_IN_USE);
     pTcMLO->setInUse(NOT_IN_USE);

     if (!TestCaseWithEvtCheck::shutDownTestCase()) 
       return SHUTDOWN_FAILURE;
     else
       return SHUTDOWN_SUCCESS;
}
