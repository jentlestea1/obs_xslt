//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// ControlBlock_inl.h
//
// Version	1.0
// Date		11.10.03 (Version 1.0)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:

#ifndef ControlBlock_INL
#define ControlBlock_INL

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"

inline TD_Float ControlBlock::getState(unsigned int i) const {
    assert(x!=pNULL && (int)i<nStates);

    return x[i];
}

inline TD_Float ControlBlock::getParameter(unsigned int i) const {
    assert(p!=pNULL && (int)i<nParameters);

    return p[i];
}

inline int ControlBlock::getNumberOfOutputs(void) const {
    assert(nOutputs>-1);

    return nOutputs;
}

inline int ControlBlock::getNumberOfInputs(void) const {
    assert(nInputs>-1);

    return nInputs;
}

inline int ControlBlock::getNumberOfStates(void) const {
    assert(nStates>-1);

    return nStates;
}

inline int ControlBlock::getNumberOfParameters(void) const {
    assert(nParameters>-1);

    return nParameters;
}

#endif
