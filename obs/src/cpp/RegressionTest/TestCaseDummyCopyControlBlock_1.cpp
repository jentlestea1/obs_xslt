//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyCopyControlBlock_1.h
//
// Version	1.0
// Date		16.10.03 
// Author	R. Totaro
//
// Change Record:

#include <math.h>
#include <float.h>

#include "TestCaseDummyCopyControlBlock_1.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../Data/ControlBlock.h"
#include "../Data/DC_DummyCopyControlBlock.h"

TestCaseDummyCopyControlBlock_1::TestCaseDummyCopyControlBlock_1(void) :
	TestCaseWithEvtCheck(ID_DUMMYCOPYCONTROLBLOCK*10+1,"TestCaseDummyCopyControlBlock_1") {
	return;
}

void TestCaseDummyCopyControlBlock_1::runTestCase(void) {
    const unsigned int        nEvt         =getNumberOfEvents();
	const unsigned int        numStates    =1;
	const unsigned int        numInputs    =3;
	const unsigned int        numOutputs   =2;
	const unsigned int        numParameters=2;
    const TD_Float            testInputs[] ={(TD_Float)0.3,(TD_Float)0.04,(TD_Float)0.005};
	DC_DummyCopyControlBlock *pDCB;

	// Create a new control block and verify the correctness
	// of its class identifier
	pDCB=new DC_DummyCopyControlBlock;

    if (pDCB->getClassId()!=ID_DUMMYCOPYCONTROLBLOCK) {
		setTestResult(TEST_FAILURE,"Wrong class identifier");
		return;
	}

	//  Verify that a newly created control block is configured
	if (!pDCB->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Newly created control block is not configured");
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

	// Verify that the default state was correctly set
	// Don't forget to take into account rounding errors:
	// this is not a problem on a Windows PC, but it might
	// be on other platforms.
	if (fabsf((float)(pDCB->getState(0)-(TD_Float)1.0))>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Wrong initial state");
		return;
	}

    // Verify that the inputs' initial values are correctly set
    for (int i=0;i<numInputs;i++) {
        if (fabsf((float)(pDCB->getInput(i)-(TD_Float)0.0))>=FLT_EPSILON) {
            setTestResult(TEST_FAILURE,"Wrong input value");
            return;
        }
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
        pDCB->setInput(i,testInputs[i]);

	pDCB->propagate();

	if (fabsf((float)(pDCB->getState(0)-(TD_Float)2.345))>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Error in state update");
		return;		
	}

	if (fabsf((float)(pDCB->getOutput(0)-(TD_Float)2.345))>=FLT_EPSILON ||
		fabsf((float)(pDCB->getOutput(1)-(TD_Float)4.690))>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Error in output update");
		return;
	}

    // Set the outputs and verify their values
    for (int i=0;i<numOutputs;i++) {
        pDCB->setOutput(i,(TD_Float)3.0);

        if (fabsf((float)(pDCB->getOutput(i)-(TD_Float)3.0))>=FLT_EPSILON) {
            setTestResult(TEST_FAILURE,"Wrong output value");
            return;
        }
    }

    // Set the state and verify its value
    pDCB->setState(0,(TD_Float)4.0);

    if (fabsf((float)(pDCB->getState(0)-(TD_Float)4.0))>=FLT_EPSILON) {
        setTestResult(TEST_FAILURE,"Wrong state value");
        return;
    }

    // Try to set state, output, input and parameter values with an out-of-range
    // index and verify that the correct event is generated
    if (isNonNominalCheckAllowed()) {
        pDCB->setState(numStates,(TD_Float)0.0);
	    if (!verifyLatestEvent(nEvt+1,EVT_ILLEGAL_CB))
		    return;

        pDCB->setOutput(numOutputs,(TD_Float)0.0);
	    if (!verifyLatestEvent(nEvt+2,EVT_ILLEGAL_CB))
		    return;

        pDCB->setInput(numInputs,(TD_Float)0.0);
	    if (!verifyLatestEvent(nEvt+3,EVT_ILLEGAL_CB))
		    return;

        pDCB->setParameter(numParameters,(TD_Float)0.0);
	    if (!verifyLatestEvent(nEvt+4,EVT_ILLEGAL_CB))
		    return;
    }

    // Reset the control block and verify the the state is
	// set to the default value
	pDCB->reset();
	if (fabsf((float)(pDCB->getState(0)-(TD_Float)1.0))>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Reset failed");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
