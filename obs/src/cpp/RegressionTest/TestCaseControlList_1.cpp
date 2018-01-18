//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseControlList_1.cpp
//
// Version	1.2
// Date		11.10.03 (Version 1.0)
//          14.10.03 (Version 1.1)
//          16.10.03 (Version 1.2)
// Author	R. Totaro
//
// Change Record:
//
// Change Record:
//   Version 1.1: Updated to reflect the new structure of the ControlBlock class
//   Version 1.2: Now using DC_DummyCopyControlBlock instead of DC_DummyControlBlock

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/ControlBlock.h"
#include "../Data/DC_DummyCopyControlBlock.h"
#include "../Data/DC_ControlList.h"
#include "TestCaseControlList_1.h"

#include <math.h>
#include <float.h>

TestCaseControlList_1::TestCaseControlList_1(void) :
	TestCaseWithEvtCheck(ID_CONTROLLIST*10+1,"TestCaseControlList_1") {
	return;
}

void TestCaseControlList_1::runTestCase(void) {
	DC_ControlList           *pCL          =new DC_ControlList;
    const unsigned int        nEvt         =getNumberOfEvents();
	const unsigned int        listSize     =2;
	const unsigned int        numInputs    =3;
	const unsigned int        numOutputs   =2;
	const unsigned int        numParameters=2;
	DC_DummyCopyControlBlock *pDCB[listSize];

	// Create and initialize the control blocks needed to
	// test the DC_ControlList class
    for (unsigned int i=0;i<listSize;i++) {
        pDCB[i]=new DC_DummyCopyControlBlock;

        // Initialize input, output and parameters
        for (unsigned int t=0;t<numInputs;t++)
            pDCB[i]->setInput(t,(TD_Float)1.0);

        for (unsigned int t=0;t<numOutputs;t++)
            pDCB[i]->setOutput(t,(TD_Float)0.0);

        for (unsigned int t=0;t<numParameters;t++)
            pDCB[i]->setParameter(t,(TD_Float)1.0);
    }

	// Verify the correctness of the class id
	if (pCL->getClassId()!=ID_CONTROLLIST) {
		setTestResult(TEST_FAILURE,"Wrong class identifier");
		return;
	}

	// A new object shall not be configured
	if (pCL->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Newly created object already configured");
		return;
	}

	// Set the list size and verify it is reported correctly
	pCL->setListSize(listSize);
	if (pCL->getListSize()!=listSize) {
		setTestResult(TEST_FAILURE,"getListSize() failed");
		return;
	}

	// Load and get the control blocks
	for (unsigned int i=0;i<listSize;i++) {
	    // The object is fully configured only when all the control blocks are loaded!
	    if (pCL->isObjectConfigured()) {
		    setTestResult(TEST_FAILURE,"Wrong configuration status");
		    return;
	    }

		pCL->setControlBlock(i,pDCB[i]);

		if (pCL->getControlBlock(i)!=pDCB[i]) {
			setTestResult(TEST_FAILURE,"setControlBlock() failed");
			return;
		}
	}

	// Only now it is configured. Let's check it.
	if (!pCL->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Object not configured");
		return;
	}

    // Verify that setControlBlock() generates an error report
	// when invoked with an invalid index
    if (isNonNominalCheckAllowed()) {
    	pCL->setControlBlock(listSize,pDCB[0]);
        if (!verifyLatestEvent(nEvt+1,EVT_ILLEGAL_CL)) {
		    setTestResult(TEST_FAILURE,"Failure of non-nominal behaviour check");
		    return;
        }
    }

    // Let's invoke execute() and verify that it returns the correct code
    if (pCL->execute()!=ACTION_SUCCESS) {
		setTestResult(TEST_FAILURE,"Wrong execution return code");
		return;
    }

    // The control block's outputs should have been updated
    for (unsigned int i=0;i<listSize;i++) {
        if (fabsf((float)pDCB[i]->getOutput(0))<=FLT_EPSILON) {
            setTestResult(TEST_FAILURE,"Control block's propagate() not invoked");
            return;
        }
    }

    // Reset the control list and verify the the control blocks'
    // states are set to their default value
	pCL->reset();
    for (unsigned int i=0;i<listSize;i++) {
        if (fabsf((float)(pCL->getControlBlock(i)->getState(0)-1.0f))>=FLT_EPSILON) {
            setTestResult(TEST_FAILURE,"Reset failed");
            return;
        }
    }

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
