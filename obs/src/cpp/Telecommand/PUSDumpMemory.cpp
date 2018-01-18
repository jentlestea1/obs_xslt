//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// PUSDumpMemory.cpp
//
// Version	1.0
// Date		4.01.04
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "PUSDumpMemory.h"
#include "../Telemetry/CC_TelemetryManager.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Telemetry/DC_PUSMemoryDumpOffset.h"
#include "../Telemetry/DC_PUSMemoryDumpAbsolute.h"
#include "../Data/DataPool.h"

PUSDumpMemory::PUSDumpMemory(void) {
    setType(PUS_TYPE_MEM);

    data = pNULL;
    maxNumberData = 0;
    numberData = 0;
    pTmManager = pNULL;
}

void PUSDumpMemory::setNumberOfRawData(unsigned int max) {
    assert( max>0 );
    assert( data==pNULL );

    maxNumberData = max;
    data = new unsigned char[maxNumberData];
    for (unsigned int i=0; i<maxNumberData; i++)
        data[i] = 0;
}

unsigned int PUSDumpMemory::getNumberOfRawData() {
    return maxNumberData;
}

void PUSDumpMemory::setRawData(unsigned char* d, unsigned int n) {
    assert( data!=pNULL );

    if ( n>maxNumberData ) {
        setValidityCheckCode(VC_TOO_MANY_RAW_DATA);
        return;
    } 

    numberData = n;
    for (unsigned int i=0; i<numberData; i++)
        data[i] = d[i];

    setValidityCheckCode(0);
    return;
}

unsigned int PUSDumpMemory::getNumberOfApplicationData(void) const {
    return numberData;
}

void PUSDumpMemory::setTelemetryManager(CC_TelemetryManager* pTmManager) {
    assert( pTmManager!=pNULL );
    this->pTmManager = pTmManager;
}

CC_TelemetryManager* PUSDumpMemory::getTelemetryManager() const {
    return pTmManager;
}

bool PUSDumpMemory::isObjectConfigured(void) {
   return (PUSTelecommand::isObjectConfigured() && data!=pNULL &&
                                                                pTmManager!=pNULL);
}
