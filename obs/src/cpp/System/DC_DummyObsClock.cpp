//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyObsClock.cpp
//
// Version  1.0
// Date	    14.09.02
// Author   A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_DummyObsClock.h"

DC_DummyObsClock::DC_DummyObsClock(void) {
     reset();
     setClassId(ID_DUMMYOBSCLOCK);
}

TD_ObsTime DC_DummyObsClock::getTime(void) {
     return time;
}

TD_ObsCycle DC_DummyObsClock::getCycle(void) {
     return cycle;
}

void DC_DummyObsClock::setTime(TD_ObsTime time) {
     assert( time>= 0 );
     this->time = time;
}

void DC_DummyObsClock::setCycle(TD_ObsCycle cycle) {
     assert( cycle>=0 );
     this->cycle = cycle;
}

void DC_DummyObsClock::reset(void) {
     time = 0;
     cycle = 0;
}

void DC_DummyObsClock::synchronizeWithSystemTime(void) {
     return;
}
