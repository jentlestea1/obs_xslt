//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// CC_TelecommandManager.cpp
//
// Version	1.0
// Date	    4.12.02 (Version 1.0)
// Author	A. Pasetti (P&P Software)
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Base/CC_RootObject.h"
#include "../System/ObsClock.h"
#include "CC_TelecommandManager.h"
#include "TelecommandLoader.h"

CC_TelecommandManager::CC_TelecommandManager(void) {
    pTcList   =pNULL;
    tcListSize=0;
    pTcLoader =pNULL;
    tcCounter =0;
    setClassId(ID_TELECOMMANDMANAGER);
}

void CC_TelecommandManager::reset(void) {
    assert(pTcList!=pNULL);

    for (unsigned int i=0; i<tcListSize; i++) {
        if (pTcList[i]!=pNULL) {
            CC_RootObject::getEventRepository()->create(pTcList[i],EVT_TC_ABORTED);
            pTcLoader->release(pTcList[i]);
            pTcList[i]=pNULL;
        }
    }

    tcCounter=0;
}

void CC_TelecommandManager::setPendingTelecommandListSize(unsigned int listSize) {
    assert(tcListSize==0);      // should not be called more than once
    assert(listSize>0);

    tcListSize=listSize;
    pTcList=new Telecommand*[tcListSize];

    for (unsigned int i=0;i<tcListSize;i++)
        pTcList[i]=pNULL;
}

unsigned int CC_TelecommandManager::getPendingTelecommandListSize(void) {
    assert(tcListSize>0);

    return tcListSize;
}

void CC_TelecommandManager::load(Telecommand *pTelecommand) {
    assert (isObjectConfigured());
    assert (pTelecommand!=pNULL);

    if (!pTelecommand->isValid()) {
        CC_RootObject::getEventRepository()->create(pTelecommand,EVT_TC_NOT_VALID);
        pTcLoader->release(pTelecommand);
        return;
    }

    // Check whether list of pending telecommands is full
    if (tcCounter==tcListSize) {
        CC_RootObject::getEventRepository()->create(pTelecommand,EVT_TC_LIST_FULL);
        pTcLoader->release(pTelecommand);
        return;
    }

    // Try to insert telecommand in the list of pending telecommands
    for (unsigned int i=0;i<tcListSize;i++) {
        if (!pTcList[i]) {
            pTcList[i]=pTelecommand;
            CC_RootObject::getEventRepository()->create(pTelecommand,EVT_TC_LOADED);
            tcCounter++;
            return;
        }
    }

    assert(false);  // this should never be reached
}

unsigned int CC_TelecommandManager::getPendingTelecommands(void) {
    assert(isObjectConfigured());

    return tcCounter;
}

Telecommand* CC_TelecommandManager::getPendingTelecommand(unsigned int i) {
    assert(isObjectConfigured());
    assert(i<tcListSize);

    return pTcList[i];
}

void CC_TelecommandManager::abort(Telecommand *pTelecommand) {
    assert(isObjectConfigured() && (pTelecommand!=pNULL));

    for (unsigned int i=0;i<tcListSize;i++) {
        if (pTcList[i]==pTelecommand) {
            CC_RootObject::getEventRepository()->create(pTelecommand,EVT_TC_ABORTED);
            pTcLoader->release(pTcList[i]);
            pTcList[i]=pNULL;
            tcCounter--;
            return;
        }
    }
}

void CC_TelecommandManager::abort(TD_TelecommandId telecomandId) {
    assert(isObjectConfigured() && telecomandId>0);

    for (unsigned int i=0;i<tcListSize;i++) {
        if (pTcList[i]->getTelecommandId()==telecomandId) {
            CC_RootObject::getEventRepository()->create(pTcList[i],EVT_TC_ABORTED);
            pTcLoader->release(pTcList[i]);
            pTcList[i]=pNULL;
            tcCounter--;
        }
    }
}

void CC_TelecommandManager::setTelecommandLoader(TelecommandLoader *pTcLoader) {
    assert(pTcLoader!=pNULL);

    this->pTcLoader=pTcLoader;
}

TelecommandLoader *CC_TelecommandManager::getTelecommandLoader(void) {
    assert(pTcLoader!=pNULL);

    return pTcLoader;
}

void CC_TelecommandManager::setObsClock(ObsClock *pObsClock) {
    assert(pObsClock!=pNULL);

    this->pObsClock=pObsClock;
}

ObsClock *CC_TelecommandManager::getObsClock(void) {
    assert(pObsClock!=pNULL);

    return pObsClock;
}

void CC_TelecommandManager::activate(void) {
    assert(isObjectConfigured());
    TD_ActionOutcome tcOutcome;

    for (unsigned int i=0;i<tcListSize;i++) {
        if (pTcList[i]!=pNULL && pTcList[i]->getTimeTag()<=pObsClock->getTime()) {
            if (pTcList[i]->canExecute()) {
                tcOutcome = pTcList[i]->execute();
                if (tcOutcome != ACTION_SUCCESS)
                    CC_RootObject::getEventRepository()->create(pTcList[i],EVT_TC_EXEC_FAIL);
                else
                    CC_RootObject::getEventRepository()->create(pTcList[i],EVT_TC_EXEC_SUCC);
            } else
                CC_RootObject::getEventRepository()->create(pTcList[i],EVT_TC_EXEC_CHECK_FAIL);

            pTcLoader->release(pTcList[i]);
            pTcList[i]=pNULL;
            tcCounter--;
        }
    }
}

bool CC_TelecommandManager::isObjectConfigured(void) {
    return (CC_RootObject::isObjectConfigured() &&
            pTcLoader!=pNULL && pObsClock!=pNULL && tcListSize!=pNULL);
}
