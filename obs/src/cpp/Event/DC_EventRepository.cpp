//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_EventRepository.cpp
//
// Version	1.1
// Date	    13.09.03 (version 1.0)
//          03.12.03 (version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: The class was almost completely re-implemented.

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../System/ObsClock.h"
#include "DC_Event.h"
#include "DC_EventRepository.h"

DC_EventRepository::DC_EventRepository(void) {
    setClassId(ID_EVENTREPOSITORY);

    counter      =0;
    listSize     =0;
    pList        =pNULL;
    pObsClock    =pNULL;
    globalEnabled=ENABLED;

    for (int i=0;i<=LAST_EVENT_TYPE;i++)
        selectiveEnabled[i]=ENABLED;

    reset();
}

void DC_EventRepository::setRepositorySize(unsigned int repositorySize) {
    assert(listSize==0 && repositorySize>0);

    pList   =new DC_Event*[repositorySize];
    listSize=repositorySize;

    for (unsigned int i=0;i<repositorySize;i++)
        pList[i]=pNULL;

    createEventDataStructure();
}

void DC_EventRepository::createEventDataStructure(void) {
    assert(pList!=pNULL);

    for (unsigned int i=0;i<listSize;i++) {
        pList[i]=new DC_Event;
        assert(pList[i]);
    }
}

void DC_EventRepository::create(CC_RootObject *originator,TD_EventType eventId) {
    assert(isObjectConfigured() &&
           originator!=pNULL && eventId>0 && eventId<=LAST_EVENT_TYPE);

    // Only create event if creation is enabled
    if (isEnabled() && isEnabled(eventId)) {
        pList[counter%listSize]->setEventType(eventId);
        pList[counter%listSize]->setTimeStamp(pObsClock->getTime());

        counter++;
    }
}

void DC_EventRepository::latest(void) {
    eventPointer=(counter>0?counter-1:0);
    iterationCounter=(counter>=listSize?listSize:counter);
}

void DC_EventRepository::previous(void) {
    if (iterationCounter>0) {
        iterationCounter--;
        eventPointer--;
    }
}

void DC_EventRepository::reset(void) {
    eventPointer    =0;
    iterationCounter=0;
}

bool DC_EventRepository::isObjectConfigured(void) {
    return (CC_RootObject::isObjectConfigured() && pList!=pNULL && pObsClock!=pNULL);
}
