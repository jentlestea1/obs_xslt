//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyTelemetryPacket.cpp
//
// Version	1.0
// Date		04.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "DC_DummyTelemetryPacket.h"

DC_DummyTelemetryPacket::DC_DummyTelemetryPacket(void) {
    setClassId(ID_DUMMYTELEMETRYITEM);
    item = pNULL;
    nOfBytes = 0;
    validStatus = VALID;

    // Dummy calls to setter methods
    setDestination((TD_TelemetryDestination)1);
    setTimeTag((TD_ObsTime)1);
    setType((TD_TelemetryType)1);
    setSubType((TD_TelemetrySubType)1);
}

unsigned char DC_DummyTelemetryPacket::getUnsignedByte(unsigned int n) {
    assert( (item!=pNULL) && (n<nOfBytes) );
	return item[n];
}

void DC_DummyTelemetryPacket::setValidStatus(bool validStatus) {
	this->validStatus = validStatus;
}

bool DC_DummyTelemetryPacket::isValid(void) {
	return validStatus;
}

unsigned int DC_DummyTelemetryPacket::getNumberOfBytes(void) {
    return nOfBytes;
}

void DC_DummyTelemetryPacket::update(void) {
    assert( item!=pNULL );
    for (unsigned int i=0; i<nOfBytes; i++) {
        if ( item[i] < 255 )
            item[i]++;
        else
            item[i] = 0;
    }
}

void DC_DummyTelemetryPacket::setValue(unsigned int n, unsigned char value) {
    assert( (item!=pNULL) && (n<nOfBytes) );
    item[n] = value;
}

void DC_DummyTelemetryPacket::setNumberOfBytes(unsigned int n) {
    assert( item==pNULL );
    nOfBytes = n;
    item = new unsigned char[nOfBytes];
    for (unsigned int i=0; i<nOfBytes; i++)
        item[i] = 0;
}

bool DC_DummyTelemetryPacket::isObjectConfigured() {
    return ( TelemetryPacket::isObjectConfigured() && (item!=pNULL) );
}
