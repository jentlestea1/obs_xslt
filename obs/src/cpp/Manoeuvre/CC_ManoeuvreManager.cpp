//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// CC_ManoeuvreManager.cpp
//
// Version	1.1
// Date		09.05.03
// Author	A. Pasetti (P&P Software), R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Base/CC_RootObject.h"
#include "CC_ManoeuvreManager.h"

CC_ManoeuvreManager::CC_ManoeuvreManager(void) {
    pManList = pNULL;
    manListSize = 0;
    manCounter = 0;
    setClassId(ID_MANOEUVREMANAGER);
}

void CC_ManoeuvreManager::reset(void) {
    assert( pManList != pNULL );
    for (unsigned int i=0; i<manListSize; i++)
        if (pManList[i] != pNULL)
            abort(pManList[i]);
    assert( manCounter == 0);
}

void CC_ManoeuvreManager::setPendingManoeuvreListSize(const unsigned int listSize) {
    assert( manListSize == 0);      // should not be called more than once
    assert( listSize > 0 );
    manListSize = listSize;
    pManList = new Manoeuvre*[manListSize];

    for (unsigned int i=0; i<manListSize; i++)
        pManList[i] = pNULL;
}

unsigned int CC_ManoeuvreManager::getPendingManoeuvreListSize(void) {
    assert( manListSize > 0 );
    return manListSize;
}

void CC_ManoeuvreManager::load(Manoeuvre* pManoeuvre) {
    assert ( isObjectConfigured() );

    // Check whether list of pending manoeuvres is full
    if ( manCounter == manListSize ) {
        CC_RootObject::getEventRepository()->create(pManoeuvre,EVT_MAN_LIST_FULL);
        return;
    }

    // Insert manoeuvre in the list of pending manoeuvres
	for (unsigned int i=0; i<manListSize; i++) {
        if (pManList[i] == pNULL) {
            pManList[i] = pManoeuvre;
            manCounter++;
            CC_RootObject::getEventRepository()->create(pManoeuvre,EVT_MAN_LOADED);
            return;
        }
	}

    // This point shall never be reached
    assert(false);
}

void CC_ManoeuvreManager::unload(Manoeuvre* pManoeuvre) {
    assert ( isObjectConfigured() );
    assert ( pManoeuvre != pNULL );
    assert ( manCounter > 0 );
    assert ( pManoeuvre->isInUse() );
    assert ( !pManoeuvre->isExecuting() );

    // Remove manoeuvre from the list of pending telecommands
    for (unsigned int i=0; i<manListSize; i++) {
        if (pManList[i] == pManoeuvre) {
            pManoeuvre->setInUse(MAN_NOT_IN_USE);
            pManList[i] = pNULL;
            manCounter--;
            CC_RootObject::getEventRepository()->create(pManoeuvre,EVT_MAN_UNLOADED);
            return;
        }
    }

    // This point shall never be reached
    assert(false);
}

unsigned int CC_ManoeuvreManager::getPendingManoeuvres(void) {
    assert(isObjectConfigured());
    return manCounter;
}

void CC_ManoeuvreManager::abort(Manoeuvre* pManoeuvre) {
    assert(isObjectConfigured() && pManoeuvre!=pNULL);

    for (unsigned int i=0; i<manListSize; i++) {
        if (pManList[i] == pManoeuvre) {
            pManoeuvre->abort();
            pManoeuvre->setInUse(MAN_NOT_IN_USE);
            pManList[i] = pNULL;
            manCounter--;
            CC_RootObject::getEventRepository()->create(pManoeuvre,EVT_MAN_UNLOADED);
            return;
        }
    }

    // This point shall never be reached
    assert(false);
}

void CC_ManoeuvreManager::activate(void) {
    assert(isObjectConfigured());

    for (unsigned int i=0;i<manListSize;i++) {
        Manoeuvre *pM=pManList[i];

		if (pM!=pNULL) {
			if (!pM->isExecuting()) {
				if (pM->canStart()) {
					pM->initialize();
					pM->doContinue();
				}
			}
			else if (pM->isFinished()) {
				pM->terminate();
				unload(pM);
			}
			else if (pM->canContinue()) {
				pM->doContinue();
			}
			else {
				pM->abort();
				unload(pM);
			}
		}
    }
}

bool CC_ManoeuvreManager::isObjectConfigured(void) {
   return (CC_RootObject::isObjectConfigured() && manListSize>0);
}
