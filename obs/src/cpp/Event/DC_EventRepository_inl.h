//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_EventRepository_inl.h
//
// Version	1.1
// Date	    13.09.03 (version 1.0)
//          03.12.03 (version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: The class was almost completely re-implemented.

#ifndef DC_EventRepository_INL
#define DC_EventRepository_INL

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "DC_Event.h"

inline unsigned int DC_EventRepository::getCounter(void) const {
    return counter;
}

inline unsigned int DC_EventRepository::getRepositorySize(void) const {
    return listSize;
}

inline void DC_EventRepository::setEnabled(bool isEnabled) {
    globalEnabled=isEnabled;
}

inline void DC_EventRepository::setEnabled(TD_EventType eventType,bool isEnabled) {
    assert(eventType>0 && eventType<=LAST_EVENT_TYPE);

    selectiveEnabled[eventType]=isEnabled;
}

inline bool DC_EventRepository::isEnabled(void) const {
    return globalEnabled;
}

inline bool DC_EventRepository::isEnabled(TD_EventType eventType) const {
    assert(eventType>0 && eventType<=LAST_EVENT_TYPE);

    return selectiveEnabled[eventType];
}

inline bool DC_EventRepository::isIterationFinished(void) const {
    return (iterationCounter==0);
}

inline TD_EventType DC_EventRepository::getEventType(void) const {
    assert(pList!=pNULL);

    return pList[eventPointer%listSize]->getEventType();
}

inline TD_ObsTime DC_EventRepository::getTimeStamp(void) const {
    assert(pList!=pNULL);

    return pList[eventPointer%listSize]->getTimeStamp();
}

inline ObsClock *DC_EventRepository::getObsClock(void) const {
    assert(pObsClock!=pNULL);

    return pObsClock;
}

inline void DC_EventRepository::setObsClock(ObsClock *pClock) {
    assert(pClock!=pNULL);

    pObsClock=pClock;
}

#endif
