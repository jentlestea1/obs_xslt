//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DataItemControlBlock.cpp
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
#include "DataItemControlBlock.h"

DataItemControlBlock::DataItemControlBlock(void) {
    pDIU=pNULL;
    pDIY=pNULL;
}

void DataItemControlBlock::setNumberOfInputs(unsigned int n) {
    assert(nInputs<0 && n>0);

    nInputs=n;
    pDIU=new DC_DataItem*[n];
    for (unsigned int i=0;i<n;i++)
        pDIU[i]=pNULL;
}

void DataItemControlBlock::setNumberOfOutputs(unsigned int n) {
    assert(nOutputs<0 && n>0);

    nOutputs=n;
    pDIY=new DC_DataItem*[n];
    for (unsigned int i=0;i<n;i++)
        pDIY[i]=pNULL;
}

void DataItemControlBlock::setInputLink(unsigned int i,DC_DataItem *pDataItem) {
    assert(pDIU!=pNULL && pDataItem!=pNULL && (int)i<nInputs);

    if ((int)i<nInputs)
        pDIU[i]=pDataItem;
    else
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_CB);
}

void DataItemControlBlock::setOutputLink(unsigned int i,DC_DataItem *pDataItem) {
    assert(pDIY!=pNULL && pDataItem!=pNULL && (int)i<nOutputs);

    if ((int)i<nOutputs)
        pDIY[i]=pDataItem;
    else
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_CB);
}

bool DataItemControlBlock::isObjectConfigured(void) {
    if (!ControlBlock::isObjectConfigured())
        return false;

    for (int i=0;i<nInputs;i++) {
        if (pDIU[i]==pNULL)
            return false;
    }

    for (int i=0;i<nOutputs;i++) {
        if (pDIY[i]==pNULL)
            return false;
    }

    return true;
}
