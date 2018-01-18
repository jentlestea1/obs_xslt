//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_Event_inl.h
//
// Version	1.0
// Date		13.10.03
// Author	A. Pasetti (P&P Software)

#ifndef DC_Event_INL
#define DC_Event_INL

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "DC_Event.h"

inline DC_Event::DC_Event() {
}

inline TD_ObsTime DC_Event::getTimeStamp() const {
	assert ( timeStamp >= 0 );
	return timeStamp;
}

inline TD_EventType DC_Event::getEventType() const {
	assert ( evtType > 0 );
	return evtType;
}

inline void DC_Event::setTimeStamp(TD_ObsTime timeStamp) {
	assert ( timeStamp >= 0 );
	this->timeStamp = timeStamp;
}

inline void DC_Event::setEventType(TD_EventType eventType) {
	assert ( eventType > 0 );
	evtType = eventType;
}

#endif
