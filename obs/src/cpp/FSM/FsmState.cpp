//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// FsmState.cpp
//
// Version	1.0
// Date		02.10.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"
#include "FsmState.h"

FsmState::FsmState(void) {
   pNextState = pNULL;
}

bool FsmState::canEnter(void) {
   return true;
}

void FsmState::doInit(void) {
   return;
}

bool FsmState::canExit(void) {
   return true;
}

void FsmState::doExit(void) {
   return;
}

bool FsmState::isFinished(void) {
   return false;
}
