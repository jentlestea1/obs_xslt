//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSDataReportingPacket.cpp
//
// Version	1.0
// Date		04.11.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../Base/CC_RootObject.h"
#include "../Data/DataPool.h"
#include "../System/ObsClock.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"

#include <string.h>

DC_PUSDataReportingPacket::DC_PUSDataReportingPacket(void) {
    setClassId(ID_PUSDATAREPORTINGPACKET);
    enabled = false;

    defBuffer = pNULL;
    defBufferSize = 0;
    defBufferCounter = 0;

    valBuffer = pNULL;
    valBufferSize = 0;

    indSID = 0;
    indCollectionInterval = sizeof(TD_SID);
    indNPAR1 = indCollectionInterval+sizeof(TD_PUSCollectionInterval);
    indNFA = 0;

    F = pNULL;
    faDescSize = 0;
    FAcounter = 0;

    setType(PUS_TYPE_DATA_REP);
}

TD_PUSCollectionInterval DC_PUSDataReportingPacket::getCollectionInterval() {
    assert( defBuffer!=pNULL );
    TD_PUSCollectionInterval temp;
    memcpy(&temp,defBuffer+indCollectionInterval,sizeof(TD_PUSCollectionInterval));
    return temp;
}

TD_PUSNumberOfParameters DC_PUSDataReportingPacket::getNPAR1() {
    assert( defBuffer!=pNULL );
    TD_PUSNumberOfParameters temp;
    memcpy(&temp,defBuffer+indNPAR1,sizeof(TD_PUSNumberOfParameters));
    return temp;
}

unsigned char DC_PUSDataReportingPacket::getNFA() {
    assert( defBuffer!=pNULL );
    return *(unsigned char*)(defBuffer+indNFA);
}

TD_SID DC_PUSDataReportingPacket::getSID() {
    assert( defBuffer!=pNULL );
    TD_SID temp;
    memcpy(&temp,defBuffer+indSID,sizeof(TD_SID));
    return temp;
}

void DC_PUSDataReportingPacket::setEnabled(bool enabledStatus) {
    enabled = enabledStatus;
}

bool DC_PUSDataReportingPacket::isEnabled() const {
    return enabled;
}

void DC_PUSDataReportingPacket::reset() {
    assert( F!=pNULL );

    for (unsigned int i=0; i<faDescSize; i++)
        if ( F[i].nrep!=0 ) {
             F[i].counter = getCollectionInterval()/F[i].nrep;
             F[i].rep = 0;
        }

    setEnabled(DISABLED);
}

void DC_PUSDataReportingPacket::setDefinitionBuffer(unsigned int i, unsigned char val) {
    assert( isObjectConfigured() );
    assert( i<defBufferSize );

    if ( (i>=defBufferSize) || (FAcounter>=faDescSize) ) {
        getEventRepository()->create(this,EVT_ILLEGAL_PUS_REP_PACKET);
        return;
    }

    defBuffer[i] = val;
    defBufferCounter = i;

    if ( i<(indNPAR1+sizeof(TD_PUSNumberOfParameters)-1) )
        return;

    if ( i==(indNPAR1+sizeof(TD_PUSNumberOfParameters)-1) ) {  // process the NPAR1 field
        F[0].npar = getNPAR1();
        F[0].nrep = 1;
        F[0].counter = getCollectionInterval();
        F[0].rep = 0;
        F[0].ind = i+1;
        F[0].size = 0;
        F[0].val = 0;
        FAcounter = 0;
        return;
    }

    assert( i>(indNPAR1+sizeof(TD_PUSNumberOfParameters)-1) );
    assert( i>=F[0].ind );

    unsigned int j = i-F[0].ind;    // j=0 when the first byte of the first par is processed
    if ( j<getNPAR1()*sizeof(TD_DataPoolId) ) {
        if ( ((j+1)%sizeof(TD_DataPoolId))==0 ) {
            // process the j-th parameter that is sampled only once per collection interval
            TD_DataPoolId id;
            memcpy(&id,(defBuffer+i-sizeof(TD_DataPoolId)+1),sizeof(TD_DataPoolId));
            if ( getDataPool()->isFloat(id) )
                F[0].size += sizeof(TD_Float);
            else
                F[0].size += sizeof(TD_Integer);
        }
        return;
    }

    if ( i==(F[0].ind+F[0].npar*sizeof(TD_DataPoolId)) ) {
        indNFA = i;
        return;
    }

    assert( i>indNFA );

    if ( i==(indNFA+1) ) {
        FAcounter = 1;
        F[1].val = F[0].val+F[0].size*F[0].nrep;
        F[1].ind = i+1+sizeof(TD_PUSNumberOfParameters);
    } else if ( i==(F[FAcounter].ind+F[FAcounter].npar*sizeof(TD_DataPoolId)) )  {
        FAcounter++;        // process the FAcounter-th FA
        assert(FAcounter<faDescSize);
        if ( FAcounter>=faDescSize ) {
            getEventRepository()->create(this,EVT_ILLEGAL_PUS_REP_PACKET);
            return;
        }
        F[FAcounter].val = F[FAcounter-1].val+F[FAcounter-1].size*F[FAcounter-1].nrep;
        F[FAcounter].ind = i+1+sizeof(TD_PUSNumberOfParameters);
    }

    assert(FAcounter>0);

    if ( i==(F[FAcounter].ind-1-sizeof(TD_PUSNumberOfParameters)) ) {  // this is the NREP field of the FA
        F[FAcounter].nrep = val;
        F[FAcounter].rep = 0;
        F[FAcounter].counter = getCollectionInterval()/val;
        F[FAcounter].size = 0;
        return;
    }

    if ( i<(F[FAcounter].ind-1) ) {
        return;
    }

    if ( i==F[FAcounter].ind-1 ) {   // this is end of the NPAR2 field of the FA
        memcpy(&F[FAcounter].npar,(defBuffer+i-sizeof(TD_PUSNumberOfParameters)+1),sizeof(TD_PUSNumberOfParameters));
        return;
    }

    j = i-F[FAcounter].ind;     // j=0 when the first byte of the first par in the FA is processed
    if ( j<F[FAcounter].npar*sizeof(TD_DataPoolId) ) {
        if ( ((j+1)%sizeof(TD_DataPoolId))==0 ) {
            // process the j-th parameter of the FAcounter-th fixed-length array
            TD_DataPoolId id;
            memcpy(&id,(defBuffer+i-sizeof(TD_DataPoolId)+1),sizeof(TD_DataPoolId));
            if ( getDataPool()->isFloat(id) )
                F[FAcounter].size += sizeof(TD_Float);
            else
                F[FAcounter].size += sizeof(TD_Integer);
        }
        return;
    }

    assert(false);
}

unsigned int DC_PUSDataReportingPacket::getDefinitionBufferLength(void) {
    assert( defBuffer!=pNULL );
    return (defBufferCounter+1);
}

unsigned char DC_PUSDataReportingPacket::getDefinitionBuffer(unsigned int i) {
    assert( i<defBufferCounter );
    return defBuffer[i];
}

TD_DataPoolId DC_PUSDataReportingPacket::getParameterId(unsigned int faIndex, unsigned int parPos) {
    assert( faIndex<=FAcounter );
    assert( parPos<F[faIndex].npar );

    TD_DataPoolId temp;
    memcpy(&temp,(defBuffer+F[faIndex].ind+parPos*sizeof(TD_DataPoolId)),sizeof(TD_DataPoolId));

    return temp;
}

void DC_PUSDataReportingPacket::update() {
    assert( isObjectConfigured() );
    assert( (getSubType()==PUS_ST_DATA_REP_PAR_HK_REP) ||
            (getSubType()==PUS_ST_DATA_REP_PAR_DG_REP) );

    if ( !isEnabled() )
        return;

    setTimeTag(getObsClock()->getTime());

    // Copy SID in the first locations of the packet value buffer
    for (unsigned int i=0; i<sizeof(TD_SID); i++)
        valBuffer[i]=defBuffer[i];

    // Write mode field into packet value buffer
    bool dummy = PUS_DATA_REP_MODE;     // use of dummy avoids compiler warning due to PUS_DATA_REP_MODE being a constant
    if ( dummy )
        valBuffer[sizeof(TD_SID)]=0;

    // Compute initial offset in the packet value buffer (the first parameter value
    // is written at location valBufferInitialOffset)
    unsigned short valBufferInitialOffset = sizeof(TD_SID)+(PUS_DATA_REP_MODE?1:0);

    for (unsigned short i=0; i<=FAcounter; i++) {

        if ( F[i].counter==0 )
            F[i].counter = getCollectionInterval()/F[i].nrep;

        F[i].counter--;

        if ( F[i].counter==0 ) {
            unsigned int pos = valBufferInitialOffset+F[i].val+F[i].rep*F[i].size;
            if ( (pos+(F[i].rep+1)*F[i].size)>=valBufferSize ) {   // check if next frame fits in value buffer
                getEventRepository()->create(this,EVT_PUS_DATA_REP_PACKET_TOO_LARGE);
                break;
            }
            for (unsigned char j=0; j<F[i].npar; j++) {
                TD_DataPoolId id = getParameterId(i,j);
                if ( getDataPool()->isFloat(id) ) {
                    TD_Float flTemp = getDataPool()->getFloatValue(id);
                    memcpy(valBuffer+pos,&flTemp,sizeof(TD_Float));
                    assert( pos<valBufferSize );
                    pos += sizeof(TD_Float);
                } else {
                    TD_Integer intTemp = getDataPool()->getIntegerValue(id);
                    memcpy(valBuffer+pos,&intTemp,sizeof(TD_Integer));
                    assert( pos<valBufferSize );
                    pos += sizeof(TD_Integer);
                }
            }

            F[i].rep++;

            if ( F[i].rep==F[i].nrep )
                F[i].rep=0;
        }
    }
}

unsigned int  DC_PUSDataReportingPacket::getNumberOfBytes (void) {
    assert( isObjectConfigured() );
    assert( (getSubType()==PUS_ST_DATA_REP_PAR_HK_REP) ||
            (getSubType()==PUS_ST_DATA_REP_PAR_HK_REP) );

    if ( !isEnabled() )
        return 0;

    if ( F[0].counter!=0 )
        return 0;

    return (sizeof(TD_SID)+(PUS_DATA_REP_MODE?1:0)+F[FAcounter].val+
                                            F[FAcounter].size*F[FAcounter].nrep);
}

unsigned char DC_PUSDataReportingPacket::getUnsignedByte(unsigned int  n) {
    assert( isObjectConfigured() );
    assert( (getSubType()==PUS_ST_DATA_REP_PAR_HK_REP) ||
            (getSubType()==PUS_ST_DATA_REP_PAR_HK_REP) );
    assert( n<valBufferSize );

    return valBuffer[n];
}

unsigned char* DC_PUSDataReportingPacket::getStartAddress(void) {
    assert( valBuffer!=pNULL );
    return valBuffer;
}

bool DC_PUSDataReportingPacket::isFastAcquisitionImplemented(void) {
    return true;
}

void DC_PUSDataReportingPacket::setDefinitionBufferSize(unsigned int size) {
    assert( size>0 );
    assert( defBuffer==pNULL );     // should only be called once

    defBufferSize = size;
    defBuffer = new unsigned char[defBufferSize];
    for (unsigned short i=0; i<defBufferSize; i++)
        defBuffer[i] = 0;
}

unsigned int DC_PUSDataReportingPacket::getDefinitionBufferSize() {
    return defBufferSize;
}

void DC_PUSDataReportingPacket::setValueBufferSize(unsigned int size) {
    assert( size>0 );
    assert( valBuffer==pNULL );     // should only be called once

    valBufferSize = size;
    valBuffer = new unsigned char[valBufferSize];
    for (unsigned int i=0; i<valBufferSize; i++)
        valBuffer[i] = 0;
}

unsigned int DC_PUSDataReportingPacket::getValueBufferSize() {
    return valBufferSize;
}

void DC_PUSDataReportingPacket::setMaxNumberFA(unsigned int n) {
    assert( F==pNULL );     // should only be called once

    // recall F[0] is used to store information about parameters sampled once per collection interval
    faDescSize = (unsigned char)(n+1);
    F = new FaDescType[faDescSize];
    for (unsigned char i=0; i<faDescSize; i++) {
        F[i].counter = 0;
        F[i].ind = 0;
        F[i].npar = 0;
        F[i].nrep = 0;
        F[i].rep = 0;
        F[i].size = 0;
        F[i].val = 0;
    }
}

unsigned int DC_PUSDataReportingPacket::getMaxNumberFA() {
    assert( faDescSize>0 );
    return (faDescSize-1);
}

bool DC_PUSDataReportingPacket::isObjectConfigured(void) {
   return (PUSTelemetryPacket::isObjectConfigured() && F!=pNULL &&
                                        valBuffer!=pNULL && defBuffer!=pNULL);
}
