//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyCopyControlBlock.cpp
//
// Version	1.3
// Date	    11.04.03 (Version 1.0)
//          14.10.03 (Version 1.1)
//          16.10.03 (Version 1.2 & 1.3)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: Updated to reflect the new structure of the ControlBlock class
//   Version 1.2: The class is now derived from CopyControlBlock
//   Version 1.3: Added missing assert()s

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_DummyCopyControlBlock.h"

DC_DummyCopyControlBlock::DC_DummyCopyControlBlock(void) {
    setNumberOfInputs(3);
    setNumberOfOutputs(2);
    setNumberOfStates(1);
    setNumberOfParameters(2);

    reset();

    setClassId(ID_DUMMYCOPYCONTROLBLOCK);
}

void DC_DummyCopyControlBlock::propagateState(void) {
    assert(isObjectConfigured());

    x[0]=p[0]*x[0]+u[0]+u[1]+u[2];
}

void DC_DummyCopyControlBlock::updateOutput(void) {
    assert(isObjectConfigured());

    y[0]=x[0];
    y[1]=p[1]*x[0];
}

void DC_DummyCopyControlBlock::reset(void) {
    assert(isObjectConfigured());

    CopyControlBlock::reset();

    x[0]=(TD_Float)1.0;
}

