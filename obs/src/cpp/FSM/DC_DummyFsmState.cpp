//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyFsmState.cpp
//
// Version	1.0
// Date		02.10.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_DummyFsmState.h"

DC_DummyFsmState::DC_DummyFsmState(void) {
   setClassId(ID_DUMMYFSMSTATE);
}

void DC_DummyFsmState::doContinue(void) {
   return;
}

