//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// FsmState_inl.h
//
// Version	1.0
// Date		12.10.02
// Author	A. Pasetti (P&P Software)

#ifndef FsmState_INL
#define FsmState_INL

inline void FsmState::setNextState(FsmState* pState) {
    pNextState = pState;
}

inline FsmState* FsmState::getNextState(void) const {
    return pNextState;
}

#endif
