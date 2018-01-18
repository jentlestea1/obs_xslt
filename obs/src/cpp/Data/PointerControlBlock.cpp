//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// PointerControlBlock.cpp
//
// Version	1.1
// Date		15.10.03 (Version 1.0)
//          16.10.03 (Version 1.1)
// Author	R. Totaro
//
// Change Record:
//   Version 1.1: Fixed the behaviour of isObjectConfigured()

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "PointerControlBlock.h"

PointerControlBlock::PointerControlBlock(void) {
    pU=pNULL;
    pY=pNULL;
}

void PointerControlBlock::setNumberOfInputs(unsigned int n) {
    assert(nInputs<0);
    assert(n>0);

    nInputs=n;
    pU=new TD_Float*[n];
    for (unsigned int i=0;i<n;i++)
        pU[i]=pNULL;
}

void PointerControlBlock::setNumberOfOutputs(unsigned int n) {
    assert(nOutputs<0);
    assert(n>0);

    nOutputs=n;
    pY=new TD_Float*[n];
    for (unsigned int i=0;i<n;i++)
        pY[i]=pNULL;
}

void PointerControlBlock::setInputLink(unsigned int i,TD_Float *pInput) {
    assert(pU!=pNULL && pInput!=pNULL && (int)i<nInputs);

    if ((int)i<nInputs)
        pU[i]=pInput;
    else
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_CB);
}

void PointerControlBlock::setOutputLink(unsigned int i,TD_Float *pOutput) {
    assert(pY!=pNULL && pOutput!=pNULL && (int)i<nOutputs);

    if ((int)i<nOutputs)
        pY[i]=pOutput;
    else
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_CB);
}

bool PointerControlBlock::isObjectConfigured(void) {
    if (!ControlBlock::isObjectConfigured())
        return false;

    for (int i=0;i<nInputs;i++)
        if (pU[i]==pNULL)
            return false;

    for (int i=0;i<nOutputs;i++)
        if (pY[i]==pNULL)
            return false;

    return true;
}
