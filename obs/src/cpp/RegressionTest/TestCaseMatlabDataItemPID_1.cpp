//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseMatlabDataItemPID_1.cpp
//
// Version	1.0
// Date		29.10.03 (Version 1.0)
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_DataItem.h"
#include "../Data/ControlBlock.h"
#include "../Data/DC_MatlabDataItemPID.h"
#include "TestCaseMatlabDataItemPID_1.h"

TestCaseMatlabDataItemPID_1::TestCaseMatlabDataItemPID_1(void) :
	TestCaseGenericSetUp(ID_MATLABDATAITEMPID*10+1,"TestCaseMatlabDataItemPID_1") {
	return;
}

void TestCaseMatlabDataItemPID_1::runTestCase(void) {
    TD_Float              input;
    TD_Float              output;
	const unsigned int    numParams=3;
    DC_DataItem          *pInput   =new DC_DataItem(&input);
    DC_DataItem          *pOutput  =new DC_DataItem(&output);
    DC_MatlabDataItemPID *pMPID    =new DC_MatlabDataItemPID;

	// Verify correctness of class identifier
    if (pMPID->getClassId()!=ID_MATLABDATAITEMPID) {
		setTestResult(TEST_FAILURE,"Wrong class identifier");
		return;
	}

	// A newly created DC_MatlabDataItemPID shall not be configured
	if (pMPID->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Newly created control block is not configured");
		return;
	}

    // Link the input and verify the block is not yet configured
    pMPID->setInputLink(0,pInput);
	if (pMPID->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Wrong configuration status");
		return;
	}

    // Link the output and verify the block is now configured
    pMPID->setOutputLink(0,pOutput);
	if (!pMPID->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"failed to configure the control block");
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
	// (see pid.c and DC_MatlabDataItemPID.cpp) are, respectively, -1.0, 1.0
	// and 1.0. The value of the time step shall be 0.25.
	const TD_Float  expectedResults[]={(TD_Float)3.0,(TD_Float)-0.75,
                                       (TD_Float)3.0,(TD_Float)-1.0,(TD_Float)0.25};
	const TD_Float *pRes             =expectedResults;

	// Set the input to a fixed value and verify that
	// the model is invoked and properly working.
	// Initially the parameters are left at their default
	// values (see pid.c and DC_MatlabDataItemPID.cpp).
    input=(TD_Float)1.0;

    // This is only to avoid an annoying warning
    output=(TD_Float)0.0;

	pMPID->propagate();
	if (fabsf(output-*pRes++)>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Control block returned wrong value");
		return;
	}

	pMPID->propagate();
	if (fabsf(output-*pRes++)>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Control block returned wrong value");
		return;
	}

	// Let's reset the model and verify that we get the right output
	// value after a propagate.
	pMPID->reset();
	pMPID->propagate();
	if (fabsf(output-*pRes++)>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Control block reset failed");
		return;
	}

	// We now reset the model and set the value of Kd to 0.0f
	pMPID->reset();
	pMPID->setParameter(2,(TD_Float)0.0);
	pMPID->propagate();
	if (fabsf(output-*pRes++)>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Failed to set the D gain");
		return;
	}

	// We do the same with Kp
	pMPID->reset();
	pMPID->setParameter(0,(TD_Float)0.0);
	pMPID->propagate();
	pMPID->propagate();
	if (fabsf(output-*pRes++)>=FLT_EPSILON) {
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
