//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// PUSTcManoeuvre.cpp
//
// Version	1.0
// Date		10.11.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "PUSTcManoeuvre.h"

PUSTcManoeuvre::PUSTcManoeuvre(void) {
    progressAck = false;
    completionAck = false;
    startAck = false;
    tcId = 0;
}

void PUSTcManoeuvre::generateProgressEvent(void) {
    CC_RootObject::getEventRepository()->create(this,EVT_MAN_PROGRESS);
}

bool PUSTcManoeuvre::isStartAckRequired(void) const {
    return startAck;
}

bool PUSTcManoeuvre::isProgressAckRequired(void) const {
    return progressAck;
}

bool PUSTcManoeuvre::isCompletionAckRequired(void) const {
    return completionAck;
}

void PUSTcManoeuvre::setStartAckFlag(bool startAckFlag) {
    startAck = startAckFlag;
}

void PUSTcManoeuvre::setCompletionAckFlag(bool completionAckFlag) {
    completionAck = completionAckFlag;
}

void PUSTcManoeuvre::setProgressAckFlag(bool progressAckFlag) {
    progressAck = progressAckFlag;
}

TD_TelecommandId PUSTcManoeuvre::getTelecommandId(void) const {
    return tcId;
}

void PUSTcManoeuvre::setTelecommandId(TD_TelecommandId tcIdentifier) {
    assert( tcIdentifier>0 );
    tcId = tcIdentifier;
}
