//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TelemetryListModeManager.cpp
//
// Version	1.0
// Date		24.01.04
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Base/ModeManager.h"
#include "TelemetryListModeManager.h"

TelemetryListModeManager::TelemetryListModeManager(void) {
    counter = 0;
	list = pNULL;
	listLength = pNULL;
    iterationListIndex = 0;
}

void TelemetryListModeManager::allocateMemory(TD_Mode numberOfModes) {
    assert( numberOfModes > 0);
    assert( list == pNULL );

    list = new TelemetryPacket**[numberOfModes];
    for (TD_Mode i=0; i<numberOfModes; i++)
        list[i] = pNULL;

    listLength = new unsigned int[numberOfModes];
    for (TD_Mode i=0; i<numberOfModes; i++)
        listLength[i] = 0;
}

void TelemetryListModeManager::setListLength(unsigned int n, unsigned int length) {
    assert( listLength != pNULL );
    assert( list != pNULL );
    assert( n<(unsigned int)getNumberOfModes() );
    assert( length>0 );

    listLength[n] = length;
    list[n] = new TelemetryPacket*[length];
    for (unsigned int i=0; i<length; i++)
        list[n][i] = pNULL;
}

void TelemetryListModeManager::setListItem(unsigned int n, unsigned int pos, TelemetryPacket* pItem) {
    assert( n<(unsigned int)getNumberOfModes() );
    assert( listLength != pNULL );
    assert( listLength[n] > 0 );
    assert( pos<listLength[n] );
    assert( pItem != pNULL );

    if ( (pos<listLength[n]) && (n<(unsigned int)getNumberOfModes()) )
        list[n][pos] = pItem;
    else
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_MM);
}

void TelemetryListModeManager::first(void) {
    assert( isObjectConfigured() );
    counter = 0;
    iterationListIndex = getCurrentMode();
}

void TelemetryListModeManager::next(void) {
    assert( isObjectConfigured() );
    counter++;
}

bool TelemetryListModeManager::isIterationFinished(void) {
    assert( isObjectConfigured() );
    return( counter == listLength[iterationListIndex] );
}

TelemetryPacket* TelemetryListModeManager::getIterationTelemetryPacket(void) {
    assert( isObjectConfigured() );
    if (counter>=listLength[iterationListIndex])
        counter = listLength[iterationListIndex]-1;
    return list[iterationListIndex][counter];
}

bool TelemetryListModeManager::isObjectConfigured(void) {
    if (!TelemetryModeManager::isObjectConfigured() || list==pNULL || listLength==pNULL)
        return NOT_CONFIGURED;

    for (TD_Mode i=0; i<getNumberOfModes(); i++) {
        if ( listLength[i] == pNULL )
            return NOT_CONFIGURED;
    }

    for (TD_Mode i=0; i<getNumberOfModes(); i++) {
        for (unsigned int j=0; j<listLength[i]; j++) {
            if ( list[i][j] == pNULL )
                return NOT_CONFIGURED;
        }
    }

    return CONFIGURED;
}

