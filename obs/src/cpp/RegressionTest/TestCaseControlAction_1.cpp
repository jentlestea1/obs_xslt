//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseControlAction_1.cpp
//
// Version	1.0
// Date		16.10.03 (Version 1.3)
// Author	A. Pasetti, R. Totaro
//
// Change Record:

#include "../Data/ControlBlock.h"
#include "TestCaseControlAction_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_ControlAction.h"
#include "../Data/DC_DummyCopyControlBlock.h"


TestCaseControlAction_1::TestCaseControlAction_1(void) :
	TestCaseGenericSetUp(ID_CONTROLACTION*10+1,
						 "TestCaseControlAction_1") {
}

void TestCaseControlAction_1::runTestCase(void) {
	DC_ControlAction *pAct=new DC_ControlAction;

	// Verify correctness of the class identifier
	if (pAct->getClassId()!=ID_CONTROLACTION) {
		setTestResult(TEST_FAILURE,"Wrong class identifier");
		return;
	}

    // Check that component is not configured
    if (pAct->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Wrong configuration status");
		return;
	}

    // Create and configure a dummy control block
	DC_DummyCopyControlBlock *pDCB         =new DC_DummyCopyControlBlock;
	const unsigned int        numInputs    =3;
    const TD_Float            inputValues[]={(TD_Float)0.3,(TD_Float)0.04,(TD_Float)0.05};

    // Set control block inputs
	for (int i=0;i<numInputs;i++)
		pDCB->setInput(i,inputValues[i]);

    // Load the control block and check success of load operations
    pAct->setTargetControlBlock(pDCB);
    if (pAct->getTargetControlBlock()!=pDCB) {
		setTestResult(TEST_FAILURE,"Loaded control block is wrong");
		return;
	}

    // Check that component is configured
    if (!pAct->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Wrong configuration status");
		return;
	}

    // Check the execution request (as a result of an execution request
    // the value of the first element of the state should change)
    TD_Float initialState=pDCB->getState(0);

    pAct->execute();
    if (pDCB->getState(0)==initialState) {
		setTestResult(TEST_FAILURE,"Execution request failure");
		return;
	}

    // Check the reset request (as a result of a reset request, the 
    // value of the first element of the state should go back to its 
    // old value
    pAct->reset();
    if (pDCB->getState(0)!=initialState) {
		setTestResult(TEST_FAILURE,"Reset request failure");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
