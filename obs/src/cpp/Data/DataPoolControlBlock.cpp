//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DataPoolControlBlock.cpp
//
// Version	1.0
// Date		15.10.03 (Version 1.0)
// Author	R. Totaro
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "DataPoolControlBlock.h"

DataPoolControlBlock::DataPoolControlBlock(void) {
    dpu=pNULL;
    dpy=pNULL;
}

void DataPoolControlBlock::setNumberOfInputs(unsigned int n) {
    assert(nInputs<0 && n>0);

    nInputs=n;
    dpu=new TD_DataPoolId[n];
    for (unsigned int i=0;i<n;i++)
        dpu[i]=-1;
}

void DataPoolControlBlock::setNumberOfOutputs(unsigned int n) {
    assert(nOutputs<0 && n>0);

    nOutputs=n;
    dpy=new TD_DataPoolId[n];
    for (unsigned int i=0;i<n;i++)
        dpy[i]=-1;
}

void DataPoolControlBlock::setInputLink(unsigned int i,TD_DataPoolId dpIdentifier) {
    assert(dpu!=pNULL && dpIdentifier>-1 && (int)i<nInputs);

    if ((int)i<nInputs)
        dpu[i]=dpIdentifier;
    else
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_CB);
}

void DataPoolControlBlock::setOutputLink(unsigned int i,TD_DataPoolId dpIdentifier) {
    assert(dpy!=pNULL && dpIdentifier>-1 && (int)i<nOutputs);

    if ((int)i<nOutputs)
        dpy[i]=dpIdentifier;
    else
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_CB);
}

bool DataPoolControlBlock::isObjectConfigured(void) {
    if (!ControlBlock::isObjectConfigured())
        return false;

    for (int i=0;i<nInputs;i++) {
        if (dpu[i]<0)
            return false;
    }

    for (int i=0;i<nOutputs;i++) {
        if (dpy[i]<0)
            return false;
    }

    return true;
}
