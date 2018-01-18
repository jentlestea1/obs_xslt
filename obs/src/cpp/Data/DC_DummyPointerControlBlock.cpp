//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyPointerControlBlock.cpp
//
// Version	1.1
// Date		16.10.03 (Version 1.1)
// Author	R. Totaro
//
// Change Record:
//   Version 1.1: Removed reset() from class constructor.
//                Added missing assert()s.

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_DummyPointerControlBlock.h"

DC_DummyPointerControlBlock::DC_DummyPointerControlBlock(void) {
    setNumberOfInputs(3);
    setNumberOfOutputs(2);
    setNumberOfStates(1);
    setNumberOfParameters(2);

    reset();

    setClassId(ID_DUMMYPOINTERCONTROLBLOCK);
}

void DC_DummyPointerControlBlock::propagateState(void) {
    assert(isObjectConfigured());

    x[0]=p[0]*x[0]+*pU[0]+*pU[1]+*pU[2];
}

void DC_DummyPointerControlBlock::updateOutput(void) {
    assert(isObjectConfigured());

    *pY[0]=x[0];
    *pY[1]=p[1]*x[0];
}

void DC_DummyPointerControlBlock::reset(void) {
    assert(x!=pNULL);

    x[0]=(TD_Float)1.0;
}

