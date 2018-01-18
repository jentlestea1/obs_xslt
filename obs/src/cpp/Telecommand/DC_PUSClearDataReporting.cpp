//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSClearDataReporting.cpp
//
// Version	1.0
// Date		4.01.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_PUSClearDataReporting.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Telemetry/CC_TelemetryManager.h"
#include "../Telemetry/DC_PUSTelemetryModeManager.h"

DC_PUSClearDataReporting::DC_PUSClearDataReporting(void) {
   setClassId(ID_PUSCLEARDATAREPORTING);
   setType(PUS_TYPE_DATA_REP);
   sid = pNULL;
   sidOverlay = pNULL;
   nsid = 0;
   maxNsid = 0;
   lasti = 0;

   pTmModeManager = pNULL;
}

void DC_PUSClearDataReporting::setMaxNumberSID(unsigned char max) {
    assert( max>0 );
    assert( maxNsid==0 );   // can only be called once

    maxNsid = max;
    sid = new TD_SID[maxNsid];
    sidOverlay = (unsigned char*)sid;
    for (unsigned int i=0; i<maxNsid; i++)
        sid[i] = 0;
}

void DC_PUSClearDataReporting::setRawData(unsigned int i, unsigned char d) {
    assert( i<=maxNsid*sizeof(TD_SID) );
    assert( (i==0) || (i==(lasti+1)) );    // check that i argument increments by 1 in each call

    lasti = i;
    if (i==0) {
        setValidityCheckCode(VC_INCONSISTENT_RAW_DATA);
        nsid = d;
        if (nsid>maxNsid)
            setValidityCheckCode(VC_TOO_MANY_SIDS);
        return;
    }

    if ( i<nsid*sizeof(TD_SID) && (getValidityCheckCode()==VC_INCONSISTENT_RAW_DATA) ) {
        sidOverlay[i-1] = d;
        return;
    }

    if ( i==nsid*sizeof(TD_SID) && (getValidityCheckCode()==VC_INCONSISTENT_RAW_DATA) ) {
        setValidityCheckCode(0);
        sidOverlay[i-1] = d;
        return;
    }

    if ( i>=(maxNsid*sizeof(TD_SID)+1) ) {
        setValidityCheckCode(VC_TOO_MANY_RAW_DATA);
        return;
    }

}

unsigned int DC_PUSClearDataReporting::getNumberOfRawData(void) const {
    return maxNsid*sizeof(TD_SID)+1;
}

TD_ActionOutcome DC_PUSClearDataReporting::doAction(void) {
    assert( (getSubType()==PUS_ST_DATA_REP_CLR_HK) ||
            (getSubType()==PUS_ST_DATA_REP_CLR_DG) );

    CC_TelemetryPacketFactory* pFct = CC_TelemetryPacketFactory::getInstance();
    TD_ActionOutcome outcome=ACTION_SUCCESS;

    for (unsigned int i=0; i<nsid; i++) {
        DC_PUSDataReportingPacket* pPck = pFct->getPUSDataReportingPacket(sid[i]);
        if ( pPck==pNULL ) 
            outcome = ACTION_FAILURE;
        else 
            pPck->setInUse(NOT_IN_USE);

        if ( pTmModeManager->isSIDLoaded(sid[i]) )
            pTmModeManager->unloadPacket(sid[i]);
     }
    
    return outcome;
}

void DC_PUSClearDataReporting::setPUSTelemetryModeManager(DC_PUSTelemetryModeManager* pTmModeManager) {
    assert( pTmModeManager!=pNULL );
    this->pTmModeManager = pTmModeManager;
}


DC_PUSTelemetryModeManager* DC_PUSClearDataReporting::getPUSTelemetryModeManager() const {
    return pTmModeManager;
}

bool DC_PUSClearDataReporting::isObjectConfigured(void) {
   return (PUSTelecommand::isObjectConfigured() && maxNsid!=0 && pTmModeManager!=pNULL);
}
