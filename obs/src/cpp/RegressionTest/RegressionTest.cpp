//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// RegressionTest.cpp
//
// Version	1.0
// Date		13.09.02
// Author   A. Pasetti (P&P Software)

#include "../Utilities/TestSuite.h"
#include "../Utilities/TestUtilities.h"

#include "TestCaseBasicDatabase_1.h"
#include "TestCaseBasicDataPool_1.h"
#include "TestCaseBasicPUSTcLoader_1.h"
#include "TestCaseBasicPUSTmStream_1.h"
#include "TestCaseBasicReconfigurer_1.h"
#include "TestCaseByteArrayTelemetryStream_1.h"
#include "TestCaseChecksum_1.h"
#include "TestCaseControlAction_1.h"
#include "TestCaseControlList_1.h"
#include "TestCaseCycleDataItem16TmStream_1.h"
#include "TestCaseCyclingPunctualActionModeManager_1.h"
#include "TestCaseCyclingTelemetryModeManager_1.h"
#include "TestCaseDataItem_1.h"
#include "TestCaseDataItem16TmWord_1.h"
#include "TestCaseDataPoolMonitor_1.h"
#include "TestCaseDeltaProfile_1.h"
#include "TestCaseDummyConditionalPunctualAction_1.h"
#include "TestCaseDummyConfigurableManoeuvre_1.h"
#include "TestCaseDummyCopyControlBlock_1.h"
#include "TestCaseDummyCriticalTelecommand_1.h"
#include "TestCaseDummyCriticalTelecommand_2.h"
#include "TestCaseDummyDatabase_1.h"
#include "TestCaseDummyDataItemControlBlock_1.h"
#include "TestCaseDummyDataPool_1.h"
#include "TestCaseDummyDataPoolControlBlock_1.h"
#include "TestCaseDummyFsmState_1.h"
#include "TestCaseDummyManoeuvre_1.h"
#include "TestCaseDummyModeManager_1.h"
#include "TestCaseDummyObsClock_1.h"
#include "TestCaseDummyPointerControlBlock_1.h"
#include "TestCaseDummyPunctualAction_1.h"
#include "TestCaseDummyPUSTelecommand_1.h"
#include "TestCaseDummyPUSTelemetryPacket_1.h"
#include "TestCaseDummyTelecommand_1.h"
#include "TestCaseDummyTelecommandLoader_1.h"
#include "TestCaseDummyTelemetryPacket_1.h"
#include "TestCaseDummyTelemetryStream_1.h"
#include "TestCaseDummyTracer_1.h"
#include "TestCaseEvent_1.h"
#include "TestCaseEventRepository_1.h"
#include "TestCaseEventRepository_2.h"
#include "TestCaseEventRepository_3.h"
#include "TestCaseFdirCheck_1.h"
#include "TestCaseFileTelemetryStream_1.h"
#include "TestCaseFileTelemetryStream_2.h"
#include "TestCaseForbiddenValueProfile_1.h"
#include "TestCaseFromFsmEvent_1.h"
#include "TestCaseFsmEvent_1.h"
#include "TestCaseFSM_1.h"
#include "TestCaseFSM_2.h"
#include "TestCaseFSM_3.h"
#include "TestCaseInRangeProfile_1.h"
#include "TestCaseIntStack_1.h"
#include "TestCaseManoeuvreManager_1.h"
#include "TestCaseManoeuvreManager_2.h"
#include "TestCaseManoeuvreManager_3.h"
#include "TestCaseManoeuvrePunctualAction_1.h"
#include "TestCaseMatlabCopyPID_1.h"
#include "TestCaseMatlabDataItemPID_1.h"
#include "TestCaseMatlabDataPoolPID_1.h"
#include "TestCaseMatlabPointerPID_1.h"
#include "TestCaseNestedFsmActivator_1.h"
#include "TestCaseNestedFsmActivatorWithEndState_1.h"
#include "TestCaseNestedFsmActivatorWithExitCheck_1.h"
#include "TestCaseNullProfile_1.h"
#include "TestCaseOutOfRangeProfile_1.h"
#include "TestCaseProfileList_1.h"
#include "TestCasePUSClearDataReporting_1.h"
#include "TestCasePUSControlDataReporting_1.h"
#include "TestCasePUSDataReportingPacket_1.h"
#include "TestCasePUSDataReportingPacket_2.h"
#include "TestCasePUSDataReportingPacket_3.h"
#include "TestCasePUSEventRepository_1.h"
#include "TestCasePUSMemoryDumpOffset_1.h"
#include "TestCasePUSMemoryLoadAbsolute_1.h"
#include "TestCasePUSMemoryLoadOffset_1.h"
#include "TestCasePUSMemoryLoadOffset_2.h"
#include "TestCasePUSTelemetryModeManager_1.h"
#include "TestCasePunctualActionManager_1.h"
#include "TestCaseRawDataItem_1.h"
#include "TestCaseRecoveryAction_1.h"
#include "TestCaseRootObject_1.h"
#include "TestCaseRootObject_2.h"
#include "TestCaseRootObject_3.h"
#include "TestCaseRootObjectStack_1.h"
#include "TestCaseSampleFullDataPool_1.h"
#include "TestCaseSampleMonitoredDataPool_1.h"
#include "TestCaseSampleR1Database_1.h"
#include "TestCaseSampleR2Database_1.h"
#include "TestCaseSampleR3Database_1.h"
#include "TestCaseSimpleChangeProfile_1.h"
#include "TestCaseSimplePunctualActionModeManager_1.h"
#include "TestCaseSimpleTelemetryModeManager_1.h"
#include "TestCaseStuckDataProfile_1.h"
#include "TestCaseTelecommandManager_1.h"
#include "TestCaseTelecommandManager_2.h"
#include "TestCaseTelecommandManager_3.h"
#include "TestCaseTelemetryManager_1.h"
#include "TestCaseTelemetryManager_2.h"
#include "TestCaseTestPUSConfigurableManoeuvre_1.h"
#include "TestCaseTestTracer_1.h"
#include "TestCaseUnstableFsmState_1.h"
#include "../GeneralInclude/TestCompilerSwitches.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"

int main(int argc, char* argv[]) {

    // Open output file (only on MS_HOST)
	FILE* out=pNULL;
#ifdef MS_HOST
    if( (out  = fopen("RegressionTestReport.html","w")) == pNULL )
       printf( "\nThe file 'RegressionTestReport.html' could not be opened\n" );
	else
       printf( "\nThe file 'RegressionTestReport.html' was successfully opened\n" );
#endif

    printf( "\nBegin regression test ...\n" );

	// Create and load a test suite (NB: The TestCaseRootObject_3 must be the
    // the first test case to run because it tests the system configuration
    // service)
	TestSuite testSuite(out);

    testSuite.loadTestCase(new TestCaseRootObject_3);
	testSuite.loadTestCase(new TestCaseBasicDatabase_1);
	testSuite.loadTestCase(new TestCaseBasicDataPool_1);
	testSuite.loadTestCase(new TestCaseBasicPUSTcLoader_1);
	testSuite.loadTestCase(new TestCaseBasicPUSTmStream_1);
	testSuite.loadTestCase(new TestCaseBasicReconfigurer_1);
	testSuite.loadTestCase(new TestCaseByteArrayTelemetryStream_1);
	testSuite.loadTestCase(new TestCaseChecksum_1);
	testSuite.loadTestCase(new TestCaseControlAction_1);
	testSuite.loadTestCase(new TestCaseControlList_1);
	testSuite.loadTestCase(new TestCaseCycleDataItem16TmStream_1);
	testSuite.loadTestCase(new TestCaseCyclingTelemetryModeManager_1);
	testSuite.loadTestCase(new TestCaseCyclingPunctualActionModeManager_1);
	testSuite.loadTestCase(new TestCaseDataItem_1);
	testSuite.loadTestCase(new TestCaseDataItem16TmWord_1);
	testSuite.loadTestCase(new TestCaseDataPoolMonitor_1);
	testSuite.loadTestCase(new TestCaseDeltaProfile_1);
	testSuite.loadTestCase(new TestCaseDummyConditionalPunctualAction_1);
	testSuite.loadTestCase(new TestCaseDummyConfigurableManoeuvre_1);
	testSuite.loadTestCase(new TestCaseDummyCopyControlBlock_1);
	testSuite.loadTestCase(new TestCaseDummyCriticalTelecommand_1);
	testSuite.loadTestCase(new TestCaseDummyCriticalTelecommand_2);
	testSuite.loadTestCase(new TestCaseDummyDatabase_1);
	testSuite.loadTestCase(new TestCaseDummyDataItemControlBlock_1);
	testSuite.loadTestCase(new TestCaseDummyDataPool_1);
	testSuite.loadTestCase(new TestCaseDummyDataPoolControlBlock_1);
	testSuite.loadTestCase(new TestCaseDummyFsmState_1);
	testSuite.loadTestCase(new TestCaseDummyManoeuvre_1);
	testSuite.loadTestCase(new TestCaseDummyModeManager_1);
	testSuite.loadTestCase(new TestCaseDummyObsClock_1);
	testSuite.loadTestCase(new TestCaseDummyPointerControlBlock_1);
	testSuite.loadTestCase(new TestCaseDummyPunctualAction_1);
	testSuite.loadTestCase(new TestCaseDummyPUSTelecommand_1);
	testSuite.loadTestCase(new TestCaseDummyPUSTelemetryPacket_1);
	testSuite.loadTestCase(new TestCaseDummyTelecommand_1);
	testSuite.loadTestCase(new TestCaseDummyTelecommandLoader_1);
	testSuite.loadTestCase(new TestCaseDummyTelemetryPacket_1);
	testSuite.loadTestCase(new TestCaseDummyTelemetryStream_1);
	testSuite.loadTestCase(new TestCaseDummyTracer_1);
	testSuite.loadTestCase(new TestCaseFsmEvent_1);
	testSuite.loadTestCase(new TestCaseEvent_1);
	testSuite.loadTestCase(new TestCaseEventRepository_1);
	testSuite.loadTestCase(new TestCaseEventRepository_2);
	testSuite.loadTestCase(new TestCaseEventRepository_3);
	testSuite.loadTestCase(new TestCaseFdirCheck_1);
#ifdef MS_HOST
	testSuite.loadTestCase(new TestCaseFileTelemetryStream_1);
#endif
	testSuite.loadTestCase(new TestCaseFileTelemetryStream_2);
	testSuite.loadTestCase(new TestCaseForbiddenValueProfile_1);
	testSuite.loadTestCase(new TestCaseFromFsmEvent_1);
	testSuite.loadTestCase(new TestCaseFSM_1);
	testSuite.loadTestCase(new TestCaseFSM_2);
	testSuite.loadTestCase(new TestCaseFSM_3);
    testSuite.loadTestCase(new TestCaseNestedFsmActivator_1);
	testSuite.loadTestCase(new TestCaseNestedFsmActivatorWithEndState_1);
	testSuite.loadTestCase(new TestCaseNestedFsmActivatorWithExitCheck_1);
	testSuite.loadTestCase(new TestCaseIntStack_1);
	testSuite.loadTestCase(new TestCaseInRangeProfile_1);
	testSuite.loadTestCase(new TestCaseManoeuvreManager_1);
	testSuite.loadTestCase(new TestCaseManoeuvreManager_2);
	testSuite.loadTestCase(new TestCaseManoeuvreManager_3);
	testSuite.loadTestCase(new TestCaseManoeuvrePunctualAction_1);
	testSuite.loadTestCase(new TestCaseMatlabCopyPID_1);
	testSuite.loadTestCase(new TestCaseMatlabDataPoolPID_1);
	testSuite.loadTestCase(new TestCaseMatlabDataItemPID_1);
	testSuite.loadTestCase(new TestCaseMatlabPointerPID_1);
	testSuite.loadTestCase(new TestCaseNullProfile_1);
	testSuite.loadTestCase(new TestCaseOutOfRangeProfile_1);
	testSuite.loadTestCase(new TestCaseProfileList_1);
	testSuite.loadTestCase(new TestCasePunctualActionManager_1);
	testSuite.loadTestCase(new TestCasePUSClearDataReporting_1);
	testSuite.loadTestCase(new TestCasePUSControlDataReporting_1);
	testSuite.loadTestCase(new TestCasePUSDataReportingPacket_1);
    testSuite.loadTestCase(new TestCasePUSDataReportingPacket_2);
    testSuite.loadTestCase(new TestCasePUSDataReportingPacket_3);
    testSuite.loadTestCase(new TestCasePUSEventRepository_1);
    testSuite.loadTestCase(new TestCasePUSMemoryDumpOffset_1);
    testSuite.loadTestCase(new TestCasePUSMemoryLoadAbsolute_1);
    testSuite.loadTestCase(new TestCasePUSMemoryLoadOffset_1);
    testSuite.loadTestCase(new TestCasePUSMemoryLoadOffset_2);
    testSuite.loadTestCase(new TestCasePUSTelemetryModeManager_1);
	testSuite.loadTestCase(new TestCaseRecoveryAction_1);
	testSuite.loadTestCase(new TestCaseRawDataItem_1);
    testSuite.loadTestCase(new TestCaseRootObject_1);
	testSuite.loadTestCase(new TestCaseRootObject_2);
	testSuite.loadTestCase(new TestCaseRootObjectStack_1);
	testSuite.loadTestCase(new TestCaseSampleFullDataPool_1);
	testSuite.loadTestCase(new TestCaseSampleMonitoredDataPool_1);
	testSuite.loadTestCase(new TestCaseSampleR1Database_1);
	testSuite.loadTestCase(new TestCaseSampleR2Database_1);
	testSuite.loadTestCase(new TestCaseSampleR3Database_1);
    testSuite.loadTestCase(new TestCaseSimpleChangeProfile_1);
	testSuite.loadTestCase(new TestCaseSimplePunctualActionModeManager_1);
	testSuite.loadTestCase(new TestCaseSimpleTelemetryModeManager_1);
	testSuite.loadTestCase(new TestCaseStuckDataProfile_1);
	testSuite.loadTestCase(new TestCaseTelecommandManager_1);
	testSuite.loadTestCase(new TestCaseTelecommandManager_2);
	testSuite.loadTestCase(new TestCaseTelecommandManager_3);
    testSuite.loadTestCase(new TestCaseTelemetryManager_1);
    testSuite.loadTestCase(new TestCaseTelemetryManager_2);
	testSuite.loadTestCase(new TestCaseTestPUSConfigurableManoeuvre_1);
	testSuite.loadTestCase(new TestCaseTestTracer_1);
	testSuite.loadTestCase(new TestCaseUnstableFsmState_1);

	// Run the test suite -- this causes all test cases in
	// the test suite to be run in sequence
	testSuite.runTestSuite();

    printf( "\nRegression test ended...\n" );

	// close output file
#ifdef MS_HOST
	fclose(out);
#endif
	return 0;

}

