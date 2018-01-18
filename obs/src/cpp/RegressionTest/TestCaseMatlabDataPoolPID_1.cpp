//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseMatlabDataPoolPID_1.cpp
//
// Version	1.0
// Date		29.10.03 (Version 1.0)
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_BasicDataPool.h"
#include "../Data/DC_MatlabDataPoolPID.h"
#include "../Data/ControlBlock.h"
#include "TestCaseMatlabDataPoolPID_1.h"

TestCaseMatlabDataPoolPID_1::TestCaseMatlabDataPoolPID_1(void) :
	TestCaseGenericSetUp(ID_MATLABDATAPOOLPID*10+1,"TestCaseMatlabDataPoolPID_1") {
	return;
}

void TestCaseMatlabDataPoolPID_1::runTestCase(void) {
	const unsigned int    numParams=3;
    const TD_DataPoolId   inputId  =0;
    const TD_DataPoolId   outputId =sizeof(TD_Float);
    DC_BasicDataPool     *pDataPool=new DC_BasicDataPool;
    DC_MatlabDataPoolPID *pMPID    =new DC_MatlabDataPoolPID;

    // Initialize the data pool
    pDataPool->setDataPoolSize(2*sizeof(TD_Float));
    CC_RootObject::setDataPool(pDataPool);

	// Verify correctness of class identifier
    if (pMPID->getClassId()!=ID_MATLABDATAPOOLPID) {
		setTestResult(TEST_FAILURE,"Wrong class identifier");
		return;
	}

	// A newly created DC_MatlabDataPoolPID shall not be configured
	if (pMPID->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Newly created control block is not configured");
		return;
	}

    // Link the input and verify the block is not yet configured
    pMPID->setInputLink(0,inputId);
	if (pMPID->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Wrong configuration status");
		return;
	}

    // Link the output and verify the block is now configured
    pMPID->setOutputLink(0,outputId);
	if (!pMPID->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Failed to configure the control block");
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
	// (see pid.c and DC_MatlabDataPoolPID.cpp) are, respectively, -1.0, 1.0
	// and 1.0. The value of the time step shall be 0.25.
	const TD_Float  expectedResults[]={(TD_Float)3.0,(TD_Float)-0.75,
                                       (TD_Float)3.0,(TD_Float)-1.0,(TD_Float)0.25};
	const TD_Float *pRes             =expectedResults;

	// Set the input to a fixed value and verify that
	// the model is invoked and properly working.
	// Initially the parameters are left at their default
	// values (see pid.c and DC_MatlabDataPoolPID.cpp).
    pDataPool->setValue(inputId,(TD_Float)1.0);

	pMPID->propagate();
	if (fabsf(pDataPool->getFloatValue(outputId)-*pRes++)>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Control block returned wrong value");
		return;
	}

	pMPID->propagate();
	if (fabsf(pDataPool->getFloatValue(outputId)-*pRes++)>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Control block returned wrong value");
		return;
	}

	// Let's reset the model and verify that we get the right output
	// value after a propagate.
	pMPID->reset();
	pMPID->propagate();
	if (fabsf(pDataPool->getFloatValue(outputId)-*pRes++)>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Control block reset failed");
		return;
	}

	// We now reset the model and set the value of Kd to 0.0f
	pMPID->reset();
	pMPID->setParameter(2,(TD_Float)0.0);
	pMPID->propagate();
	if (fabsf(pDataPool->getFloatValue(outputId)-*pRes++)>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"Failed to set the D gain");
		return;
	}

	// We do the same with Kp
	pMPID->reset();
	pMPID->setParameter(0,(TD_Float)0.0);
	pMPID->propagate();
	pMPID->propagate();
	if (fabsf(pDataPool->getFloatValue(outputId)-*pRes++)>=FLT_EPSILON) {
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
