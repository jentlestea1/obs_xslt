//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyDataItemControlBlock.cpp
//
// Version	1.0
// Date		30.10.03 (Version 1.0)
// Author	R. Totaro
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_DataItem.h"
#include "DC_DummyDataItemControlBlock.h"

DC_DummyDataItemControlBlock::DC_DummyDataItemControlBlock(void) {
    setNumberOfInputs(3);
    setNumberOfOutputs(2);
    setNumberOfStates(1);
    setNumberOfParameters(2);

    reset();

    setClassId(ID_DUMMYDATAITEMCONTROLBLOCK);
}

void DC_DummyDataItemControlBlock::propagateState(void) {
    assert(isObjectConfigured());

    x[0]=p[0]*x[0]+pDIU[0]->getFloatValue()+
         pDIU[1]->getFloatValue()+pDIU[2]->getFloatValue();
}

void DC_DummyDataItemControlBlock::updateOutput(void) {
    assert(isObjectConfigured());

    pDIY[0]->setValue(x[0]);
    pDIY[1]->setValue(p[1]*x[0]);
}

void DC_DummyDataItemControlBlock::reset(void) {
    assert(x!=pNULL);

    x[0]=(TD_Float)1.0;
}
