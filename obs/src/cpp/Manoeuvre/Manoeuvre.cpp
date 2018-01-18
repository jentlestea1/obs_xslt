//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// Manoeuvre.cpp
//
// Version	1.0
// Date		10.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "Manoeuvre.h"

Manoeuvre::Manoeuvre(void) {
    enabled = ENABLED;
    inUse = MAN_NOT_IN_USE;
    executing = MAN_NOT_EXECUTING;
    suspended = MAN_NOT_SUSPENDED;
    activationStepCounter = 0;
}

void Manoeuvre::internalAbort(void) {
    return;
}

void Manoeuvre::internalTerminate(void) {
    return;
}

bool Manoeuvre::internalCanStart(void) {
    return MAN_CAN_START;
}

bool Manoeuvre::canStart(void) {
    assert( !executing );

    if ( !isEnabled() )
      return MAN_CANNOT_START;
    else
      return internalCanStart();
}

void Manoeuvre::initialize(void) {
   assert( !executing );
   return;
}

bool Manoeuvre::canContinue(void) {
   assert( executing );
   return MAN_CAN_CONTINUE;
}

TD_CheckCode Manoeuvre::getContinuationCheckCode(void) const {
   return 0;
}

void Manoeuvre::doContinue(void) {

   if ( !executing ) {
      executing = true;
      activationStepCounter = 0;
      CC_RootObject::getEventRepository()->create(this,EVT_MAN_STARTED);
   }

   if ( !isSuspended() ) {
      activationStepCounter++;
      doInternalContinue();
  }
}

void Manoeuvre::abort(void) {
    suspended = false;

    if (executing) {
        executing = false;
        CC_RootObject::getEventRepository()->create(this,EVT_MAN_ABORTED);
        internalAbort();
    }
}

void Manoeuvre::terminate(void) {
    assert( executing );
    suspended = false;
    executing = false;
    CC_RootObject::getEventRepository()->create(this,EVT_MAN_TERMINATED);
    internalTerminate();
}

void Manoeuvre::setInUse(bool newInUse) {
    inUse = newInUse;
}

bool Manoeuvre::isInUse(void) const {
	return inUse;
}

void Manoeuvre::setIsSuspended(bool newIsSuspended) {
	if ( suspended && !newIsSuspended )
		CC_RootObject::getEventRepository()->create(this,EVT_MAN_RESUMED);
	else if ( !suspended && newIsSuspended )
		CC_RootObject::getEventRepository()->create(this,EVT_MAN_SUSPENDED);
	suspended = newIsSuspended;
}

bool Manoeuvre::isSuspended(void) const {
	return suspended;
}

bool Manoeuvre::isExecuting(void) const {
	return executing;
}

void Manoeuvre::setEnabled(bool enabledStatus) {
	enabled = enabledStatus;
}

bool Manoeuvre::isEnabled(void) const {
	return enabled;
}

unsigned int Manoeuvre::getActivationStepCounter(void) const {
    return activationStepCounter;
}
