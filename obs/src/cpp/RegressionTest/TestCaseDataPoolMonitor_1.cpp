//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDataPoolMonitor_1.cpp
//
// Version	1.0
// Date		30.10.03 (Version 1.0)
// Author	R. Totaro
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../System/DC_DummyObsClock.h"
#include "../FDIR/DC_OutOfRangeProfile.h"
#include "../FDIR/DC_NullRecoveryAction.h"
#include "../Data/DC_SampleFullDataPool.h"
#include "../Data/DC_DataPoolMonitor.h"
#include "TestCaseDataPoolMonitor_1.h"

TestCaseDataPoolMonitor_1::TestCaseDataPoolMonitor_1(void) :
	TestCaseWithEvtCheck(ID_DATAPOOLMONITOR*10+1,"TestCaseDataPoolMonitor_1") {
	return;
}

void TestCaseDataPoolMonitor_1::runTestCase(void) {
    const unsigned int nEvt=getNumberOfEvents();

    // Create and initialize the data pool
    TD_DataPoolId          id;
    RecoveryAction        *pAction=new DC_NullRecoveryAction;
    DC_SampleFullDataPool *pDP    =new DC_SampleFullDataPool;

    pDP->setObsClock(new DC_DummyObsClock);

    for (id=pDP->firstIdentifier();!pDP->isLastIdentifier();id=pDP->nextIdentifier()) {
        DC_OutOfRangeProfile *pProfile=new DC_OutOfRangeProfile;

        pProfile->setLowerBound((TD_Float)0.0);
        pProfile->setUpperBound((TD_Float)2.0);
        pDP->setMonitoringProfile(id,pProfile);

        pDP->setRecoveryAction(id,pAction);

        if (pDP->isFloat(id))
            pDP->setValue(id,(TD_Float)1.0);
        else
            pDP->setValue(id,(TD_Integer)1);
    }

    // Link the data pool to the root object
    CC_RootObject::setDataPool(pDP);

    // Create the object under test
    DC_DataPoolMonitor *pDPM=new DC_DataPoolMonitor;

	// Verify correctness of the class identifier
	if (pDPM->getClassId()!=ID_DATAPOOLMONITOR) {
		setTestResult(TEST_FAILURE,"Wrong class identifier");
		return;
	}

    // Execute the data pool check and verify that the data are still valid
    pDPM->execute();
    for (id=pDP->firstIdentifier();!pDP->isLastIdentifier();id=pDP->nextIdentifier()) {
        if (!pDP->isValid(id)) {
		    setTestResult(TEST_FAILURE,"Wrong validity status");
		    return;
        }
    }

    // Verify that no recovery action was executed
    if (getNumberOfEvents()!=nEvt+1) {
		setTestResult(TEST_FAILURE,"Wrong number of events");
		return;
    }

    // Set the values out of the allowed range and verify that their
    // validity flags are properly changed and that the recovery
    // actions are executed.
    unsigned int evtOffset=2;

    for (id=pDP->firstIdentifier();!pDP->isLastIdentifier();id=pDP->nextIdentifier()) {
        if (pDP->isFloat(id))
            pDP->setValue(id,(TD_Float)3.0);
        else
            pDP->setValue(id,(TD_Integer)3);
    }

    pDPM->execute();

    // The execution of a recovery action should lead to two events being generated in
    // the event repository. It is checked that for each item in the repository, the
    // corresponding event was generated.
    for (id=pDP->firstIdentifier();!pDP->isLastIdentifier();id=pDP->nextIdentifier()) {
        if (pDP->isValid(id)) {
		    setTestResult(TEST_FAILURE,"Failed to change the validity status");
		    return;
        }

        // Terminate when the oldest event in the repository has been processed
        if ((getNumberOfEvents()-(nEvt+evtOffset))>=getEventRepositorySize())
            break;

        if (verifySpecificEvent(nEvt+evtOffset,EVT_PUNCTUAL_ACTION_EXEC)) {
		    setTestResult(TEST_FAILURE,"Recovery action not executed");
		    return;
        }

        evtOffset+=2;
    }

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
