//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSDefineDataReporting.cpp
//
// Version	1.0
// Date		4.01.04
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_PUSDefineDataReporting.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Telemetry/DC_PUSTelemetryModeManager.h"
#include "../Data/DataPool.h"

DC_PUSDefineDataReporting::DC_PUSDefineDataReporting(void) {
    setClassId(ID_PUSDEFINEDATAREPORTING);
    setType(PUS_TYPE_DATA_REP);

    data = pNULL;
    maxNumberData = 0;
    numberData = 0;
}

TD_ActionOutcome DC_PUSDefineDataReporting::doAction(void) {
    assert( (getSubType()==PUS_ST_DATA_REP_NEW_HK) ||
            (getSubType()==PUS_ST_DATA_REP_NEW_DG) );
    assert( isObjectConfigured() );

    CC_TelemetryPacketFactory* pFct = CC_TelemetryPacketFactory::getInstance();

    // Retrieve the number of parameters that are sampled only once per cycle
    unsigned short pos = sizeof(TD_SID)+sizeof(TD_PUSCollectionInterval);
    TD_PUSNumberOfParameters NPAR1 = *(TD_PUSNumberOfParameters*)(data+pos);
    pos += sizeof(TD_PUSNumberOfParameters);      // position of first parameter


    // Define variable to hold the length of the packet value buffer
    unsigned short val = 0;

    // Process the parameters that are sampled once per interval
    TD_DataPoolId id;
    while ( pos<NPAR1*sizeof(TD_PUSNumberOfParameters) ) {
           id = *(TD_PUSNumberOfParameters*)(data+pos);
           if (getDataPool()->isFloat(id) )
                val += sizeof(TD_Float);
           else
                val += sizeof(TD_Integer);
     }   

    // Retrieve the number of fixed-length arrays
    pos += NPAR1*sizeof(TD_DataPoolId);
    TD_PUSNumberOfParameters NFA = *(TD_PUSNumberOfParameters*)(data+pos);
    pos += sizeof(TD_PUSNumberOfParameters);

    // Process the fixed-length arrays
    TD_PUSNumberOfParameters NPAR = 0;
    for (unsigned int i=0; i<NFA; i++) {
        pos += sizeof(unsigned short);
        NPAR = *(TD_PUSNumberOfParameters*)(data+pos);
        pos += sizeof(TD_PUSNumberOfParameters);

        // Process the i-th fixed-length array
        for (unsigned int i=0; i<NPAR; i++) {
           id = *(TD_PUSNumberOfParameters*)(data+pos);
           if (getDataPool()->isFloat(id) )
                val += sizeof(TD_Float);
           else
                val += sizeof(TD_Integer);
        }
    }

    // Retrieve the telemetry packet from the dynamic factory
    DC_PUSDataReportingPacket* pPck = pFct->allocatePUSDataReportingPacket(numberData,val,NFA);
    if ( pPck==pNULL )
        return PACKET_NOT_FOUND;

    // Check consistency: the value of pos must be the same as the total number of application data
    if ( pos!=numberData )
        return APP_DATA_INCONSISTENT;

    // Load the application data in the telemetry packet
    for (unsigned int i=0; i<numberData; i++)
        pPck->setDefinitionBuffer(i,data[i]);

    // Load the telemetry packet in the telemetry mode manager
    if ( pTmModeManager->isFull() ) {
        pPck->setInUse(NOT_IN_USE);
        return PUS_MODE_MAN_FULL;
    } else
        pTmModeManager->loadPacket(pPck);
    
    return ACTION_SUCCESS;
}

void DC_PUSDefineDataReporting::setNumberOfRawData(unsigned int max) {
    assert( max>0 );
    assert( data==pNULL );

    maxNumberData = max;
    data = new unsigned char[maxNumberData];
    for (unsigned int i=0; i<maxNumberData; i++)
        data[i] = 0;
}

unsigned int DC_PUSDefineDataReporting::getNumberOfRawData() {
    return maxNumberData;
}

void DC_PUSDefineDataReporting::setRawData(unsigned char* d, unsigned int n) {
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

unsigned int DC_PUSDefineDataReporting::getNumberOfApplicationData(void) const {
    return numberData;
}

void DC_PUSDefineDataReporting::setPUSTelemetryModeManager(DC_PUSTelemetryModeManager* pTmModeManager) {
    assert( pTmModeManager!=pNULL );
    this->pTmModeManager = pTmModeManager;
}


DC_PUSTelemetryModeManager* DC_PUSDefineDataReporting::getPUSTelemetryModeManager() const {
    return pTmModeManager;
}

bool DC_PUSDefineDataReporting::isObjectConfigured(void) {
   return (PUSTelecommand::isObjectConfigured() && data!=pNULL &&
                                                                pTmModeManager!=pNULL);
}
