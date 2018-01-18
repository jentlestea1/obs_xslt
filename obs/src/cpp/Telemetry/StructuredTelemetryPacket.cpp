//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// StructuredTelemetryPacket.cpp
//
// Version	1.1
// Date		23.02.03 (version 1.0)
// Author	A. Pasetti (P&P Software)
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "StructuredTelemetryPacket.h"

StructuredTelemetryPacket::StructuredTelemetryPacket(void) {
	pByteBuffer = pNULL;
	pShortBuffer = pNULL;
	pIntBuffer = pNULL;
	numberOfBytes = 0;
}

void StructuredTelemetryPacket::setNumberOfBytes(unsigned int n) {
	assert( numberOfBytes == 0 );  // should not be called more than once
	assert( n  > 0 );

    if (numberOfBytes == 0) {
	    numberOfBytes = n;
        unsigned int nToBeAssigned;
        if ((n%sizeof(unsigned int)) == 0)
            nToBeAssigned = n/sizeof(unsigned int);
        else
            nToBeAssigned = n/sizeof(unsigned int) + 1;

	    pIntBuffer = new unsigned int[nToBeAssigned];

	    assert( pIntBuffer != pNULL );

        pByteBuffer = (unsigned char*)pIntBuffer;
	    pShortBuffer = (unsigned short*)pIntBuffer;
    }
}

unsigned int StructuredTelemetryPacket::getNumberOfBytes(void) {
	return numberOfBytes;
}

unsigned char StructuredTelemetryPacket::getUnsignedByte(unsigned int n) {
    assert( n<numberOfBytes );
    assert( numberOfBytes > 0 );
    return pByteBuffer[n];
}

void StructuredTelemetryPacket::setUnsignedByte(unsigned int index, unsigned char d) {
    assert( (numberOfBytes > 0) && (index < numberOfBytes) );
    pByteBuffer[index] = d;
}

void StructuredTelemetryPacket::setUnsignedShort(unsigned int index, unsigned short d) {
    assert( (numberOfBytes > 0) && ( sizeof(unsigned short)*(index+1) <= numberOfBytes) );
    pShortBuffer[index] = d;
}

void StructuredTelemetryPacket::setUnsignedInt(unsigned int index, unsigned int d) {
    assert( (numberOfBytes > 0) && ( sizeof(unsigned int)*(index+1) <= numberOfBytes) );
    pIntBuffer[index] = d;
}

unsigned short StructuredTelemetryPacket::getUnsignedShort(unsigned int index) {
    assert( sizeof(unsigned short)*(index+1)<=getNumberOfBytes() );
    assert( numberOfBytes > 0 );

    return pShortBuffer[index];
}

unsigned int StructuredTelemetryPacket::getUnsignedInt(unsigned int index) {
    assert( sizeof(unsigned int)*(index+1)<=getNumberOfBytes() );
    assert( numberOfBytes > 0 );

    return pIntBuffer[index];
}

bool StructuredTelemetryPacket::isObjectConfigured(void) {
    return (TelemetryPacket::isObjectConfigured() &&
            numberOfBytes>0 && pByteBuffer!=pNULL);
}
