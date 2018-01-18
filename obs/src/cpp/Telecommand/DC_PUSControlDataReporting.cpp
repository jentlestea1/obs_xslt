//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSControlDataReporting.cpp
//
// Version	1.0
// Date		4.01.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_PUSControlDataReporting.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"

DC_PUSControlDataReporting::DC_PUSControlDataReporting(void) {
   setClassId(ID_PUSCONTROLDATAREPORTING);
   setType(PUS_TYPE_DATA_REP);
   sid = pNULL;
   sidOverlay = pNULL;
   nsid = 0;
   maxNsid = 0;
   lasti = 0;
}

void DC_PUSControlDataReporting::setMaxNumberSID(unsigned char max) {
    assert( max>0 );
    assert( maxNsid==0 );   // can only be called once

    maxNsid = max;
    sid = new TD_SID[maxNsid];
    sidOverlay = (unsigned char*)sid;
    for (unsigned int i=0; i<maxNsid; i++)
        sid[i] = 0;
}

unsigned int DC_PUSControlDataReporting::getMaxNumberSID() {
    return (unsigned int) maxNsid;
}

void DC_PUSControlDataReporting::setRawData(unsigned int i, unsigned char d) {
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

unsigned int DC_PUSControlDataReporting::getNumberOfRawData(void) const {
    return maxNsid*sizeof(TD_SID)+1;
}

TD_ActionOutcome DC_PUSControlDataReporting::doAction(void) {
    assert( (getSubType()==PUS_ST_DATA_REP_ENB_HK) ||
            (getSubType()==PUS_ST_DATA_REP_ENB_DG) ||
            (getSubType()==PUS_ST_DATA_REP_DIS_HK) ||
            (getSubType()==PUS_ST_DATA_REP_DIS_DG) );

    CC_TelemetryPacketFactory* pFct = CC_TelemetryPacketFactory::getInstance();
    TD_ActionOutcome outcome = ACTION_SUCCESS;

    for (unsigned int i=0; i<nsid; i++) {
        DC_PUSDataReportingPacket* pPck = pFct->getPUSDataReportingPacket(sid[i]);
        if ( pPck==pNULL ) {
            outcome = ACTION_FAILURE;
            continue;
        }
        if ( (getSubType()==PUS_ST_DATA_REP_ENB_HK) ||
            (getSubType()==PUS_ST_DATA_REP_ENB_DG) ) 
            pPck->setEnabled(ENABLED);
         else
            pPck->setEnabled(DISABLED);
     }
    
    return outcome;
}

bool DC_PUSControlDataReporting::isObjectConfigured(void) {
   return (PUSTelecommand::isObjectConfigured() && maxNsid!=0);
}
