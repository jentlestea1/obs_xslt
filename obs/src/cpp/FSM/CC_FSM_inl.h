//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// CC_FSM_inl.h
//
// Version	1.0
// Date		13.10.02
// Author	A. Pasetti (P&P Software)

#ifndef CC_FSM_INL
#define CC_FSM_INL

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "CC_FSM.h"

inline FsmState* CC_FSM::getState(TD_FsmStateIndex i) const {
	assert( numberOfStates > 0 );
	assert( (i < numberOfStates ) && (pState[i] != pNULL) );
	return pState[i];
}

inline TD_FsmStateIndex CC_FSM::getCurrentState() const {
	assert( numberOfStates > 0 );
	return currentState;
}

inline bool CC_FSM::isTransitionEnabled(TD_FsmStateIndex toState) const {
	assert( toState < numberOfStates );
	assert( toState >= 0 );
	return transitionEnabled[toState];
}

inline bool CC_FSM::isTransitionEnabled() const {
	return allTransitionEnabled;
}

#endif
