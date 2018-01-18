//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseManoeuvreManager_2.cpp
//
// Version	1.0
// Date		08.05.03
// Author	R. Totaro

#include "TestCaseManoeuvreManager_2.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../Manoeuvre/DC_DummyConfigurableManoeuvre.h"
#include "../Manoeuvre/CC_ManoeuvreManager.h"

static const int nMan=5;
static const int maxActivations=100;
static const struct {
	unsigned int continueToFalse;
	unsigned int finishedToTrue;
} manoeuvreStateChange[nMan]={
	{ 5,4},  // Manouvre finishes after 4 calls to doContinue()
	{ 4,3},  // Manouvre finishes after 3 calls to doContinue()
	{ 6,7},  // Continuation flag set to false after 6 calls to doContinue()
	{10,9},  // Manouvre finishes after 9 calls to doContinue()
	{ 8,9}   // Continuation flag set to false after 6 calls to doContinue()
};
static const struct {
	int          activation;
	TD_EventType eventType;
	unsigned int offset;
} expectedEvent[nMan]={
	{ 4,EVT_MAN_TERMINATED,2*nMan+1},
	{ 5,EVT_MAN_TERMINATED,2*nMan+3},
	{ 7,EVT_MAN_ABORTED,   2*nMan+5},
	{ 9,EVT_MAN_ABORTED,   2*nMan+7},
	{10,EVT_MAN_TERMINATED,2*nMan+9}
};

TestCaseManoeuvreManager_2::TestCaseManoeuvreManager_2(void) :
	TestCaseWithEvtCheck(ID_MANOEUVREMANAGER*10+2,"TestCaseManoeuvreManager_2") {
	return;
}

void TestCaseManoeuvreManager_2::runTestCase(void) {
    CC_ManoeuvreManager           *pMM =new CC_ManoeuvreManager();
    const unsigned int             nEvt=this->getNumberOfEvents();
	DC_DummyConfigurableManoeuvre *pDCM[nMan];

	// Initialize the manoeuvre manager
	pMM->setPendingManoeuvreListSize(nMan);

	// Allocate, load and set the start and continuation flag of the nMan manoeuvres
	for (int i=0;i<nMan;i++) {
		pDCM[i]=new DC_DummyConfigurableManoeuvre();
        pDCM[i]->setInUse(true);
		pMM->load(pDCM[i]);
        pDCM[i]->setStartCheckStatus(MAN_CAN_START);
        pDCM[i]->setContinuationCheckStatus(MAN_CAN_CONTINUE);
        pDCM[i]->setTerminationCheckStatus(MAN_HAS_NOT_TERMINATED);
	}

	// Invoke once the activate method and verify that the manoeuvres
	// have been initialized and that doContinue() has been called.
	pMM->activate();
	for (int i=0;i<nMan;i++) {
		if (pDCM[i]->getInitializationActionCounter()!=1) {
			setTestResult(TEST_FAILURE,"Failed to initialize the manoeuvres");
			return;
		}

		if (pDCM[i]->getContinuationActionCounter()!=1) {
			setTestResult(TEST_FAILURE,"Failed to call doContinue()");
			return;
		}
	}

	// Now let's loop until all the manoeuvres have finished or the
	// maximum number of activations has been reached.
	// The initial value is 1: pMM->activate() has already been called once.
	int activationCalls=1;

	do {
		// Update the manoeuvres' status
		for (int i=0;i<nMan;i++) {
			if (pDCM[i]->isInUse()) {
				unsigned int n=pDCM[i]->getContinuationActionCounter();

				pDCM[i]->setStartCheckStatus(MAN_CAN_START);
				pDCM[i]->setContinuationCheckStatus((n<manoeuvreStateChange[i].continueToFalse));
				pDCM[i]->setTerminationCheckStatus((n>=manoeuvreStateChange[i].finishedToTrue));
			}
		}

		pMM->activate();
		activationCalls++;

		for (int i=0;i<nMan;i++) {
			// Verify that all the manoeuvres in use have been scheduled
			if (pDCM[i]->isInUse()) {
				if (pDCM[i]->getContinuationActionCounter()!=activationCalls) {
					setTestResult(TEST_FAILURE,"Failed to call doContinue()");
					return;
				}
			}

			// Now we verify that the manoeuvre has been terminated/aborted
			// (depending on its status) and unloaded from the manoeuvre manager.
			// The easiest way to do this is to look in the event repository for
			// the corresponding events.
			if (expectedEvent[i].activation==activationCalls &&
				(!verifySpecificEvent(nEvt+expectedEvent[i].offset,
									  expectedEvent[i].eventType) ||
				 !verifyLatestEvent(nEvt+expectedEvent[i].offset+1,
									EVT_MAN_UNLOADED))) {
				return;
			}
		}
	} while (pMM->getPendingManoeuvres()>0 && activationCalls<maxActivations);

	if (activationCalls==maxActivations) {
		setTestResult(TEST_FAILURE,"Maximum number of activations reached");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
