//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// ControlBlock.cpp
//
// Version	1.0
// Date	    11.04.03 (Version 1.0)
// Author	A. Pasetti (P&P Software), R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "ControlBlock.h"

ControlBlock::ControlBlock(void) {
    x          =pNULL;
    p          =pNULL;
    nInputs    =-1;
    nOutputs   =-1;
    nStates    =-1;
    nParameters=-1;
}

void ControlBlock::setNumberOfStates(unsigned int n) {
    assert(nStates<0);

    nStates=n;
    x=new TD_Float[n];
    for (unsigned int i=0;i<n;i++)
        x[i]=(TD_Float)0.0;
}

void ControlBlock::setNumberOfParameters(unsigned int n) {
    assert(nParameters<0);

    nParameters=n;
    p=new TD_Float[n];
    for (unsigned int i=0;i<n;i++)
        p[i]=(TD_Float)0.0;
}

void ControlBlock::setState(unsigned int i,TD_Float newValue) {
    assert(x!=pNULL && (int)i<nStates);

    if ((int)i<nStates)
        x[i]=newValue;
    else
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_CB);
}

void ControlBlock::setParameter(unsigned int i,TD_Float newValue) {
    assert(p!=pNULL && (int)i<nParameters);

    if ((int)i<nParameters)
        p[i]=newValue;
    else
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_CB);
}

void ControlBlock::propagate(void) {
    assert(isObjectConfigured());

    propagateState();
    updateOutput();
}

void ControlBlock::reset(void) {
    assert(x!=pNULL);

    for (int i=0;i<nStates;i++)
        x[i]=(TD_Float)0.0;
}

bool ControlBlock::isObjectConfigured(void) {
    return (CC_RootObject::isObjectConfigured() &&
            nInputs!=-1 && nOutputs!=-1 && nStates!=-1 && nParameters!=-1);
}

