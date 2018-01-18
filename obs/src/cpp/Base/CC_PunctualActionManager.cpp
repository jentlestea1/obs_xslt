//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// CC_PunctualActionManager.cpp
//
// Version  1.0
// Date	    29.09.03
// Author   R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "PunctualActionModeManager.h"
#include "CC_PunctualActionManager.h"

CC_PunctualActionManager::CC_PunctualActionManager(void) {
    pModeManager=pNULL;
    setClassId(ID_PUNCTUALACTIONMANAGER);
}

void CC_PunctualActionManager::setPunctualActionModeManager(PunctualActionModeManager *pModeManager) {
    assert(pModeManager);

    this->pModeManager=pModeManager;
}

PunctualActionModeManager *CC_PunctualActionManager::getPunctualActionModeManager(void) const {
    return pModeManager;
}

void CC_PunctualActionManager::activate(void) {
    assert(pModeManager);

    for (pModeManager->first();!pModeManager->isIterationFinished();pModeManager->next())
        pModeManager->getIterationPunctualAction()->execute();
}

bool CC_PunctualActionManager::isObjectConfigured(void) {
    return (pModeManager!=pNULL);
}
