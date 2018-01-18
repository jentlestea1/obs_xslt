//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_ManoeuvrePunctualAction.cpp
//
// Version	1.0
// Date		19.05.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Manoeuvre/CC_ManoeuvreManager.h"
#include "DC_ManoeuvrePunctualAction.h"

DC_ManoeuvrePunctualAction::DC_ManoeuvrePunctualAction(void) {
   pManoeuvre = pNULL;
   pManoeuvreManager = pNULL;
   setClassId(ID_MANOEUVREPUNCTUALACTION);
}

TD_ActionOutcome DC_ManoeuvrePunctualAction::doAction(void) {
   assert(pManoeuvre!=pNULL && pManoeuvreManager!=pNULL);

   pManoeuvreManager->load(pManoeuvre);

   return ACTION_SUCCESS;
}

void DC_ManoeuvrePunctualAction::setManoeuvreManager(CC_ManoeuvreManager* pManMan) {
    assert( pManMan!=pNULL );
    pManoeuvreManager = pManMan;
}

CC_ManoeuvreManager* DC_ManoeuvrePunctualAction::getManoeuvreManager(void) const {
    return pManoeuvreManager;
}

void DC_ManoeuvrePunctualAction::setManoeuvre(Manoeuvre* pMan) {
    assert( pMan!=pNULL );
    pManoeuvre = pMan;
}

Manoeuvre* DC_ManoeuvrePunctualAction::getManoeuvre(void) const {
    return pManoeuvre;
}

bool DC_ManoeuvrePunctualAction::isObjectConfigured(void) {
    return (PunctualAction::isObjectConfigured() &&
            pManoeuvre!=pNULL && pManoeuvreManager!=pNULL);
}

