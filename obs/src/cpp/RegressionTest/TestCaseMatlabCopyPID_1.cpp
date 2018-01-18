//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseMatlabCopyPID_1.cpp
//
// Version	1.1
// Date		30.05.03 (Version 1.0)
//          14.10.03 (Version 1.1)
// Author	R. Totaro
//
// Change Record:
//   Version 1.1: Updated to reflect the new structure of the ControlBlock class

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_MatlabCopyPID.h"
#include "../Data/ControlBlock.h"
#include "TestCaseMatlabCopyPID_1.h"

TestCaseMatlabCopyPID_1::TestCaseMatlabCopyPID_1(void) :
	TestCaseGenericSetUp(ID_MATLABCOPYPID*10+1,"TestCaseMatlabCopyPID_1") {
	return;
}

void TestCaseMatlabCopyPID_1::runTestCase(void) {
	const unsigned int numParams=3;
    DC_MatlabCopyPID  *pMPID    =new DC_MatlabCopyPID;

	// Verify correctness of class identifier
    if (pMPID->getClassId()!=ID_MATLABCOPYPID) {
		setTestResult(TEST_FAILURE,"Wrong class identifier");
		return;
	}

	// A newly created DC_MatlabCopyPID shall be configured
	if (!pMPID->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Newly created control block is not configured");
		return;
	}

	// Verify the correctness of the number of parameters
	if (pMPID->getNumberOfParameters()!=numParams) {
		setTestResult(TEST_FAILURE,"Wrong number of parameters");
		return;
	}

#ifdef HAVE_SIMULINK
	// Initialize the model's parameters
	const TD_Float defaultParameters[]={(TD_Float)-1.0,(TD_Float)1.0,(TD_Float)1.0};

	for (unsigned int i=0;i<numParams;i++)
        pMPID->setParameter(i,defaultParameters[i]);

	// The following array contains the expected output values. These
	// are correct if and only if the initial value of Kp, Ki and Kd
	// (see pid.c and DC_MatlabCopyPID.cpp) are, respectively, -1.0, 1.0
	// and 1.0. The value of the time step shall be 0.25.
	const TD_Float  expectedResults[]={(TD_Float)3.0,(TD_Float)-0.75,
                                       (TD_Float)3.0,(TD_Float)-1.0,(TD_Float)0.25};
	const TD_Float *pRes             =expectedResults;

	// Set the input to a fixed value and verify that
	// the model is invoked and properly working.
	// Initially the parameters are left at their default
	// values (see pid.c and DC_MatlabCopyPID.cpp).
    pMPID->setInput(0,(TD_Float)1.0);

	pMPID->propagate();
	if (fabsf(pMPID->getOutput(0)-*pRes++)>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Control block returned wrong value");
		return;
	}

	pMPID->propagate();
	if (fabsf(pMPID->getOutput(0)-*pRes++)>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Control block returned wrong value");
		return;
	}

	// Let's reset the model and verify that we get the right output
	// value after a propagate.
	pMPID->reset();
	pMPID->propagate();
	if (fabsf(pMPID->getOutput(0)-*pRes++)>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Control block reset failed");
		return;
	}

	// We now reset the model and set the value of Kd to 0.0f
	pMPID->reset();
	pMPID->setParameter(2,(TD_Float)0.0);
	pMPID->propagate();
	if (fabsf(pMPID->getOutput(0)-*pRes++)>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Failed to set the D gain");
		return;
	}

	// We do the same with Kp
	pMPID->reset();
	pMPID->setParameter(0,(TD_Float)0.0);
	pMPID->propagate();
	pMPID->propagate();
	if (fabsf(pMPID->getOutput(0)-*pRes++)>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Failed to set the P gain");
		return;
	}
#else
    // This is done to prevent the test coverage results from
    // degrading when Simulink is not available. These two calls
    // become a no-op.
    pMPID->propagate();
    pMPID->reset();
#endif

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
