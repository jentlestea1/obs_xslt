//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyPointerControlBlock_1.cpp
//
// Version	1.0
// Date		16.10.03 (Version 1.0)
// Author	R. Totaro
//
// Change Record:

#include <math.h>
#include <float.h>

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Data/ControlBlock.h"
#include "../Data/DC_DummyPointerControlBlock.h"
#include "TestCaseDummyPointerControlBlock_1.h"

TestCaseDummyPointerControlBlock_1::TestCaseDummyPointerControlBlock_1(void) :
	TestCaseWithEvtCheck(ID_DUMMYPOINTERCONTROLBLOCK*10+1,
                         "TestCaseDummyPointerControlBlock_1") {
	return;
}

void TestCaseDummyPointerControlBlock_1::runTestCase(void) {
    const unsigned int           nEvt         =getNumberOfEvents();
	const unsigned int           numStates    =1;
	const unsigned int           numInputs    =3;
	const unsigned int           numOutputs   =2;
	const unsigned int           numParameters=2;
    const TD_Float               testInputs[] ={(TD_Float)0.3,(TD_Float)0.04,(TD_Float)0.005};
	DC_DummyPointerControlBlock *pDCB         =new DC_DummyPointerControlBlock;
    TD_Float                     inputs[numInputs];
    TD_Float                     outputs[numOutputs];

	// Verify the correctness of the class identifier
    if (pDCB->getClassId()!=ID_DUMMYPOINTERCONTROLBLOCK) {
		setTestResult(TEST_FAILURE,"Wrong class identifier");
		return;
	}

    // Verify that the numbers of inputs, outputs, states and parameters are correct
	if (pDCB->getNumberOfInputs()!=numInputs) {
		setTestResult(TEST_FAILURE,"Wrong number of inputs");
		return;
	}

	if (pDCB->getNumberOfOutputs()!=numOutputs) {
		setTestResult(TEST_FAILURE,"Wrong number of outputs");
		return;
	}

	if (pDCB->getNumberOfStates()!=numStates) {
		setTestResult(TEST_FAILURE,"Wrong number of states");
		return;
	}

	if (pDCB->getNumberOfParameters()!=numParameters) {
		setTestResult(TEST_FAILURE,"Wrong number of parameters");
		return;
	}

    // Link inputs and outputs and verify its configuration status
    for (unsigned int i=0;i<numInputs;i++) {
        if (pDCB->isObjectConfigured()) {
            setTestResult(TEST_FAILURE,"Wrong configuration status");
            return;
        }

        pDCB->setInputLink(i,&inputs[i]);
    }

    for (unsigned int i=0;i<numOutputs;i++) {
        if (pDCB->isObjectConfigured()) {
            setTestResult(TEST_FAILURE,"Wrong configuration status");
            return;
        }

        pDCB->setOutputLink(i,&outputs[i]);
    }

    if (!pDCB->isObjectConfigured()) {
        setTestResult(TEST_FAILURE,"Wrong configuration status");
        return;
    }

    // Reset the control block
    pDCB->reset();

	// Verify that the default state was correctly set
	// Don't forget to take into account rounding errors:
	// this is not a problem on a Windows PC, but it might
	// be on other platforms.
	if (fabsf((float(pDCB->getState(0)-(TD_Float)1.0)))>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Wrong initial state");
		return;
	}

    // Set the parameters and verify their values
    for (int i=0;i<numParameters;i++) {
        pDCB->setParameter(i,(TD_Float)2.0);

        if (fabsf((float)(pDCB->getParameter(i)-(TD_Float)2.0))>=FLT_EPSILON) {
            setTestResult(TEST_FAILURE,"Wrong parameter value");
            return;
        }
    }

	// Now we propagate the inputs and verify that the state
	// and outputs are properly updated
    for (int i=0;i<numInputs;i++)
        inputs[i]=testInputs[i];

	pDCB->propagate();

	if (fabsf((float)(pDCB->getState(0)-(TD_Float)2.345))>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Error in state update");
		return;		
	}

	if (fabsf((float)(outputs[0]-(TD_Float)2.345))>=FLT_EPSILON ||
		fabsf((float)(outputs[1]-(TD_Float)4.690))>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Error in output update");
		return;
	}

    // Set the state and verify its value
    pDCB->setState(0,(TD_Float)4.0);

    if (fabsf((float)(pDCB->getState(0)-(TD_Float)4.0))>=FLT_EPSILON) {
        setTestResult(TEST_FAILURE,"Wrong state value");
        return;
    }

    if (isNonNominalCheckAllowed()) {
        // Try to link input and output with an out-of-range
        // index and verify that the correct event is generated
        pDCB->setInputLink(numInputs,&inputs[0]);
	    if (!verifyLatestEvent(nEvt+1,EVT_ILLEGAL_CB))
		    return;

        pDCB->setOutputLink(numOutputs,&outputs[0]);
	    if (!verifyLatestEvent(nEvt+2,EVT_ILLEGAL_CB))
		    return;

        // Try to set state and parameter values with an out-of-range
        // index and verify that the correct event is generated
        pDCB->setState(numStates,(TD_Float)0.0);
	    if (!verifyLatestEvent(nEvt+3,EVT_ILLEGAL_CB))
		    return;

        pDCB->setParameter(numParameters,(TD_Float)0.0);
	    if (!verifyLatestEvent(nEvt+4,EVT_ILLEGAL_CB))
		    return;
    }

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
