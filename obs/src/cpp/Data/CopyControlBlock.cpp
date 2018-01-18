//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// CopyControlBlock.cpp
//
// Version	1.0
// Date	    16.10.03 (Version 1.0)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "CopyControlBlock.h"

CopyControlBlock::CopyControlBlock(void) {
    u=pNULL;
    y=pNULL;
}

void CopyControlBlock::setNumberOfInputs(unsigned int n) {
    assert(nInputs<0);
    assert(n>0);

    nInputs=n;
    u=new TD_Float[n];
    for (unsigned int i=0;i<n;i++)
        u[i]=(TD_Float)0.0;
}

void CopyControlBlock::setNumberOfOutputs(unsigned int n) {
    assert(nOutputs<0);
    assert(n>0);

    nOutputs=n;
    y=new TD_Float[n];
    for (unsigned int i=0;i<n;i++)
        y[i]=(TD_Float)0.0;
}

void CopyControlBlock::setInput(unsigned int i,TD_Float newValue) {
    assert(u!=pNULL && (int)i<nInputs);

    if ((int)i<nInputs)
        u[i]=newValue;
    else
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_CB);
}

void CopyControlBlock::setOutput(unsigned int i,TD_Float newValue) {
    assert(y!=pNULL && (int)i<nInputs);

    if ((int)i<nOutputs)
        y[i]=newValue;
    else
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_CB);
}

TD_Float CopyControlBlock::getInput(unsigned int i) const {
    assert(u!=pNULL && (int)i<nInputs);

    return u[i];
}

TD_Float CopyControlBlock::getOutput(unsigned int i) const {
    assert(y!=pNULL && (int)i<nOutputs);

    return y[i];
}

void CopyControlBlock::reset(void) {
    assert(x!=pNULL && u!=pNULL);

    // Reset the state variables
    ControlBlock::reset();

    for (int i=0;i<nInputs;i++)
        u[i]=(TD_Float)0.0;
}

