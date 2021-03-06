  
  
//
// Copyright 2003 P&P Software GmbH - All Rights Reserved
//
// DC_MatlabPointerPID.cpp
//
// This is an automatically generated file

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_DataItem.h"
#include "../Data/DataPool.h"
#include "DC_MatlabPointerPID.h"

unsigned int DC_MatlabPointerPID::numberOfInstances=0;

DC_MatlabPointerPID::DC_MatlabPointerPID() {
    // The Simulink model is NOT reentrant, thus we
    // can only have one instance of this object
    assert(numberOfInstances==0);
    numberOfInstances++;

    numberOfInputs=1;
    numberOfOutputs=1;
    numberOfParameters=3;

#ifdef HAVE_SIMULINK
    modelStep         =PID_step;
    modelInitialize   =PID_init;

    modelInputs       =new real_T*[numberOfInputs];
    modelOutputs      =new real_T*[numberOfOutputs];
    modelParameters   =new real_T*[numberOfParameters];

    modelInputs[0]    =&Input;
    modelOutputs[0]   =&Output;
    modelParameters[1-1]=&;
    modelParameters[2-1]=&;
    modelParameters[3-1]=&;
#endif

    setNumberOfStates(0);
    setNumberOfInputs(numberOfInputs);
    setNumberOfOutputs(numberOfOutputs);
    setNumberOfParameters(numberOfParameters);

    setClassId(ID_MATLABPOINTERPID);

    // Initialize the Simulink model
    reset();
}

void DC_MatlabPointerPID::propagateState() {
#ifdef HAVE_SIMULINK
    for (unsigned int i=0; i<numberOfParameters; i++)
        *modelParameters[i]=(real_T)p[i];

    for (unsigned int i=0; i<numberOfInputs; i++)
        *modelInputs[i]=(real_T)*pU[i];
#endif
}

void DC_MatlabPointerPID::updateOutput() {
#ifdef HAVE_SIMULINK
    modelStep();

    for (unsigned int i=0;i<numberOfOutputs;i++)
        *pY[i]=(TD_Float)*modelOutputs[i];
#endif
}

void DC_MatlabPointerPID::reset() {
#ifdef HAVE_SIMULINK
        modelInitialize(1);
#endif
}
