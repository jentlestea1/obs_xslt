//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyDataPoolControlBlock.cpp
//
// Version	1.0
// Date		31.10.03 (Version 1.0)
// Author	R. Totaro
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DataPool.h"
#include "DC_DummyDataPoolControlBlock.h"

DC_DummyDataPoolControlBlock::DC_DummyDataPoolControlBlock(void) {
    setNumberOfInputs(3);
    setNumberOfOutputs(2);
    setNumberOfStates(1);
    setNumberOfParameters(2);

    reset();

    setClassId(ID_DUMMYDATAPOOLCONTROLBLOCK);
}

void DC_DummyDataPoolControlBlock::propagateState(void) {
    assert(isObjectConfigured());

    DataPool *pDP=getDataPool();

    x[0]=p[0]*x[0]+pDP->getFloatValue(dpu[0])+
         pDP->getFloatValue(dpu[1])+pDP->getFloatValue(dpu[2]);
}

void DC_DummyDataPoolControlBlock::updateOutput(void) {
    assert(isObjectConfigured());

    DataPool *pDP=getDataPool();

    pDP->setValue(dpy[0],x[0]);
    pDP->setValue(dpy[1],p[1]*x[0]);
}

void DC_DummyDataPoolControlBlock::reset(void) {
    assert(x!=pNULL);

    x[0]=(TD_Float)1.0;
}
