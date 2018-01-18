  
  
//
// Copyright 2003 P&P Software GmbH - All Rights Reserved
//
// DC_MatlabDataItemPID.cpp
//
// This is an automatically generated file

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_DataItem.h"
#include "../Data/DataPool.h"
#include "DC_MatlabDataItemPID.h"

unsigned int DC_MatlabDataItemPID::numberOfInstances=0;

DC_MatlabDataItemPID::DC_MatlabDataItemPID() {
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

    setClassId(ID_MATLABDATAITEMPID);

    // Initialize the Simulink model
    reset();
}

void DC_MatlabDataItemPID::propagateState() {
#ifdef HAVE_SIMULINK
    for (unsigned int i=0; i<numberOfParameters; i++)
        *modelParameters[i]=(real_T)p[i];

    for (unsigned int i=0; i<numberOfInputs; i++)
        *modelInputs[i]=(real_T)pDIU[i]->getFloatValue();
#endif
}

void DC_MatlabDataItemPID::updateOutput() {
#ifdef HAVE_SIMULINK
    modelStep();

    for (unsigned int i=0;i<numberOfOutputs;i++)
        pDIY[i]->setFloatValue((TD_Float)*modelOutputs[i]);
#endif
}

void DC_MatlabDataItemPID::reset() {
#ifdef HAVE_SIMULINK
        modelInitialize(1);
#endif
}
