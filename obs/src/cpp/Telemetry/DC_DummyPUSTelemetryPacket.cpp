//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyPUSTelemetryPacket.cpp
//
// Version	1.0
// Date		04.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "DC_DummyPUSTelemetryPacket.h"

DC_DummyPUSTelemetryPacket::DC_DummyPUSTelemetryPacket(void) {
    setClassId(ID_DUMMYPUSTELEMETRYPACKET);
    item = 0;
    setType(TEST_TM_TYPE);
    setSubType(TEST_TM_SUBTYPE);
    setTimeTag(TEST_TM_TIMETAG);
}

unsigned char DC_DummyPUSTelemetryPacket::getUnsignedByte(unsigned int n) {
	return item;
}

unsigned int DC_DummyPUSTelemetryPacket::getNumberOfBytes(void) {
    return 1;
}

void DC_DummyPUSTelemetryPacket::update(void) {
    if ( item < 255 )
        item++;
    else
        item = 0;
}

void DC_DummyPUSTelemetryPacket::setValue(unsigned char value) {
    item = value;
}
